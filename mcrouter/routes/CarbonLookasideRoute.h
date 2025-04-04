/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <string>
#include <utility>

#include <folly/Conv.h>
#include <folly/Range.h>
#include <folly/io/IOBuf.h>

#include "mcrouter/CarbonRouterFactory.h"
#include "mcrouter/CarbonRouterInstance.h"
#include "mcrouter/McrouterFiberContext.h"
#include "mcrouter/config.h"
#include "mcrouter/flavor.h"
#include "mcrouter/lib/McResUtil.h"
#include "mcrouter/lib/Reply.h"
#include "mcrouter/lib/RouteHandleTraverser.h"
#include "mcrouter/lib/fbi/cpp/globals.h"
#include "mcrouter/lib/routes/NullRoute.h"
#include "mcrouter/routes/McRouteHandleBuilder.h"

namespace facebook {
namespace memcache {
namespace mcrouter {

struct LeaseSettings {
  bool enableLeases{false}; // Enable or disable leases.
  int32_t initialWaitMs{2}; // Initial wait time of a retry on hot miss.
  int32_t maxWaitMs{500}; // Maximum wait time of a retry on hot miss.
  int32_t numRetries{10}; // Number of retries on a hot miss.
};

std::shared_ptr<CarbonRouterInstance<MemcacheRouterInfo>>
createCarbonLookasideRouter(
    const std::string& persistenceId,
    folly::StringPiece flavorUri,
    std::unordered_map<std::string, std::string> optionOverrides =
        std::unordered_map<std::string, std::string>());

LeaseSettings parseLeaseSettings(const folly::dynamic& json);

/**
 * CarbonLookasideRoute is a route handle that can store replies in memcache
 * with a user defined key. The user controls which replies should be cached.
 * Replies found in memcache will be returned directly without having to
 * traverse further into the routing tree.
 *
 * This behavior is controlled through a user defined class with the following
 * prototype:
 *
 * class CarbonLookasideHelper {
 *    CarbonLookasideHelper(const folly::dynamic* config);
 *
 *    std::string name();
 *
 *    // Tells whether or not we should consider the given request for caching.
 *    template <typename Request>
 *    bool cacheCandidate(const Request& req);
 *
 *   // Constructs a key for a Request.
 *   // Note: Just called for cache candidates.
 *   template <typename Request>
 *   std::string buildKey(const Request& req);
 *
 *    // Whether or not we should cache the reply we received.
 *    // Note:
 *    //  - Just called for cache candidates.
 *    //  - Just called if non-error. Errors are not considered for caching.
 *    template <typename Reply>
 *    bool shouldCacheReply(const Reply& reply);
 *
 *   // Method to do any post processing necessary to replies retrieved
 *   // from cache.
 *   template <typename Reply>
 *   void postProcessCachedReply(Reply& reply);
 * };
 *
 * @tparam RouterInfo            The Router
 * @tparam CarbonLookasideHelper User defined class with helper functions
 */
template <class RouterInfo, class CarbonLookasideHelper>
class CarbonLookasideRoute {
 private:
  using RouteHandleIf = typename RouterInfo::RouteHandleIf;
  using RouteHandlePtr = typename RouterInfo::RouteHandlePtr;

 public:
  std::string routeName() const {
    return folly::sformat(
        "lookaside-cache|name={}|ttl={}{}s|leases={}",
        carbonLookasideHelper_.name(),
        ttl_,
        subSecTTL_ ? "m" : "",
        leaseSettings_.enableLeases ? "true" : "false");
  }

  /**
   * Constructs CarbonLookasideRoute.
   *
   * @param child         The child route handle
   * @param router        A shared_ptr to the CarbonRouterInstance used to
   *                      communicate with memcache. Note: this share_ptr is
   *                      here just to keep the router alive.
   * @param client        The CarbonRouterClient used to communicate with
   *                      memcache.
   * @param prefix        Prefix prepend to memcache keys generated by the
   *                      helper.
   * @param keySplitSize  Tells how many different keys we want to have for
   *                      the same request. Useful for dealing with hot keys.
   * @param ttl           TTL of items stored in memcache by this route handle.
   *                      Defaults to use seconds but can be milliseconds when
   *                      the subSecTTL parameter is configured.
   * @param subSecTTL     TTL specified in ttl parameter is in units of ms.
   *                      The ttl can be {100,200,500}.
   * @param helper        The helper used to build keys and see if we should
   *                      cache a given request. This helper is use-case
   *                      specific.
   * @param leaseSettings The lease settings for memcache leases.
   */
  CarbonLookasideRoute(
      RouteHandlePtr child,
      std::shared_ptr<CarbonRouterInstance<MemcacheRouterInfo>> router,
      CarbonRouterClient<MemcacheRouterInfo>::Pointer client,
      std::string prefix,
      size_t keySplitSize,
      int32_t ttl,
      bool subSecTTL,
      CarbonLookasideHelper helper,
      LeaseSettings leaseSettings)
      : child_(std::move(child)),
        router_(std::move(router)),
        client_(std::move(client)),
        keyPrefix_(std::move(prefix)),
        keySuffix_(buildKeySuffix(keySplitSize)),
        ttl_(ttl),
        subSecTTL_(subSecTTL),
        carbonLookasideHelper_(std::move(helper)),
        leaseSettings_(std::move(leaseSettings)) {
    assert(router_);
    assert(client_);
  }

  template <class Request>
  bool traverse(
      const Request& req,
      const RouteHandleTraverser<RouteHandleIf>& t) const {
    return t(*child_, req);
  }

  template <class Request>
  ReplyT<Request> route(const Request& req) {
    int64_t leaseToken = 0;
    std::string key;
    bool cacheCandidate = carbonLookasideHelper_.cacheCandidate(req);
    if (cacheCandidate) {
      key = buildKey(req);
      if (auto optReply = carbonLookasideGet<Request>(key, leaseToken)) {
        carbonLookasideHelper_.postProcessCachedReply(optReply.value());
        return optReply.value();
      }
    }

    auto reply = child_->route(req);

    if (cacheCandidate && !isErrorResult(*reply.result_ref()) &&
        carbonLookasideHelper_.shouldCacheReply(reply)) {
      carbonLookasideSet(key, reply, leaseToken);
    }
    return reply;
  }

 private:
  const RouteHandlePtr child_;
  const std::shared_ptr<CarbonRouterInstance<MemcacheRouterInfo>> router_;
  const CarbonRouterClient<MemcacheRouterInfo>::Pointer client_;
  const std::string keyPrefix_;
  const std::string keySuffix_;
  const int32_t ttl_;
  const bool subSecTTL_;
  CarbonLookasideHelper carbonLookasideHelper_;
  const LeaseSettings leaseSettings_;

  template <typename Request>
  folly::Optional<ReplyT<Request>> carbonLookasideGet(
      folly::StringPiece key,
      int64_t& leaseToken) {
    if (leaseSettings_.enableLeases) {
      return carbonLookasideLeaseGet<Request>(key, leaseToken);
    }
    return carbonLookasideGet<Request>(key);
  }

  // Build a request to CarbonLookaside to query for key. Successful replies
  // are deserialized.
  template <typename Request>
  folly::Optional<ReplyT<Request>> carbonLookasideGet(folly::StringPiece key) {
    McGetRequest cacheRequest(key);
    folly::Optional<ReplyT<Request>> ret;
    folly::fibers::Baton baton;
    client_->send(
        cacheRequest,
        [&baton, &ret](const McGetRequest&, McGetReply&& cacheReply) {
          if (isHitResult(*cacheReply.result_ref()) &&
              cacheReply.value_ref().has_value()) {
            folly::io::Cursor cur(&cacheReply.value_ref().value());
            carbon::CarbonProtocolReader reader(cur);
            ReplyT<Request> reply;
            reply.deserialize(reader);
            ret.assign(std::move(reply));
          }
          baton.post();
        });
    baton.wait();
    return ret;
  }

  // Build a request using leases to CarbonLookaside to query for key.
  // Successful replies are deserialized.
  template <typename Request>
  folly::Optional<ReplyT<Request>> carbonLookasideLeaseGet(
      folly::StringPiece key,
      int64_t& leaseToken) {
    leaseToken = 0;
    McLeaseGetRequest cacheRequest(key);
    folly::Optional<ReplyT<Request>> ret;
    auto nextInterval = leaseSettings_.initialWaitMs;
    for (int32_t attempt = 0; attempt <= leaseSettings_.numRetries; ++attempt) {
      folly::fibers::Baton sleepBaton;
      if (attempt != 0) {
        sleepBaton.try_wait_for(std::chrono::milliseconds(nextInterval));
        nextInterval = std::min(nextInterval * 2, leaseSettings_.maxWaitMs);
      }
      folly::fibers::Baton baton;
      bool retry = false;
      client_->send(
          cacheRequest,
          [this, &key, &baton, &ret, &retry, &leaseToken](
              const McLeaseGetRequest&, McLeaseGetReply&& cacheReply) {
            retry = false;
            if (isHitResult(*cacheReply.result_ref()) &&
                cacheReply.value_ref().has_value()) {
              folly::io::Cursor cur(&cacheReply.value_ref().value());
              carbon::CarbonProtocolReader reader(cur);
              ReplyT<Request> reply;
              try {
                reply.deserialize(reader);
                ret.assign(std::move(reply));
              } catch (const std::exception&) {
                folly::fibers::addTask(
                    [this,
                     invalidateReq = std::make_shared<McSetRequest>(key)]() {
                      // Deserialization of item threw, invalidate in cache
                      invalidateReq->exptime_ref() = -1;
                      // Best effort cleanup mechanism without blocking the main
                      // send. Return folly::None back to client so that client
                      // will fetch from backend while not increasing error rate
                      client_->send(
                          *invalidateReq.get(),
                          [req = invalidateReq](
                              const McSetRequest&, McSetReply&&) {});
                    });
              }
            } else if (isMissResult(*cacheReply.result_ref())) {
              // Hot miss will retry using an expoential backoff.
              // A miss will return with the lease token set.
              constexpr size_t kLeaseHotMissToken = 1;
              if (*cacheReply.leaseToken_ref() == kLeaseHotMissToken) {
                retry = true;
              } else {
                leaseToken = *cacheReply.leaseToken_ref();
              }
            }
            baton.post();
          });
      baton.wait();
      if (!retry) {
        return ret;
      }
    }
    return ret;
  }

  template <typename Reply>
  folly::IOBuf serializeOffFiber(const Reply& reply) const {
    return folly::fibers::runInMainContext([&reply]() {
      carbon::CarbonQueueAppenderStorage storage;
      carbon::CarbonProtocolWriter writer(storage);
      reply.serialize(writer);
      folly::IOBuf body(folly::IOBuf::CREATE, storage.computeBodySize());
      const auto iovs = storage.getIovecs();
      for (size_t i = 0; i < iovs.second; ++i) {
        const struct iovec* iov = iovs.first + i;
        std::memcpy(body.writableTail(), iov->iov_base, iov->iov_len);
        body.append(iov->iov_len);
      }
      return body;
    });
  }

  template <typename Reply>
  void carbonLookasideSet(
      folly::StringPiece key,
      const Reply& reply,
      int64_t leaseToken) {
    if (leaseSettings_.enableLeases && leaseToken) {
      return carbonLookasideLeaseSet(key, reply, leaseToken);
    }
    return carbonLookasideSet(key, reply);
  }

  // Build a request to memcache to store the serialized reply with the
  // provided key.
  template <typename Reply>
  void carbonLookasideSet(folly::StringPiece key, const Reply& reply) {
    McSetRequest req(key);
    if (subSecTTL_) {
      // ms ttl translates to a 1 second ttl on the server. Sub-second
      // ttl is acheived by appending a time based suffix to the key.
      req.exptime_ref() = 1;
    } else {
      req.exptime_ref() = ttl_;
    }
    req.value_ref() = serializeOffFiber(reply);
    folly::fibers::addTask([this, req = std::move(req)]() {
      folly::fibers::Baton baton;
      client_->send(
          req, [&baton](const McSetRequest&, McSetReply&&) { baton.post(); });
      baton.wait();
    });
  }

  // Build a request using leases to memcache to store the serialized reply
  // with the provided key.
  template <typename Reply>
  void carbonLookasideLeaseSet(
      folly::StringPiece key,
      const Reply& reply,
      const int64_t leaseToken) {
    McLeaseSetRequest req(key);
    if (subSecTTL_) {
      // ms ttl translates to a 1 second ttl on the server. Sub-second
      // ttl is acheived by appending a time based suffix to the key.
      req.exptime_ref() = 1;
    } else {
      req.exptime_ref() = ttl_;
    }
    req.leaseToken_ref() = leaseToken;
    req.value_ref() = serializeOffFiber(reply);
    folly::fibers::addTask([this, req = std::move(req)]() {
      folly::fibers::Baton baton;
      client_->send(req, [&baton](const McLeaseSetRequest&, McLeaseSetReply&&) {
        baton.post();
      });
      baton.wait();
    });
  }

  /**
   * Generates a suffix for sub-second TTL requests.
   * The idea is to return the bucket ID based on the TTL.
   * For example: if the TTL is 50ms, we would generate TTLs based on the
   * following pattern:
   *  -----------------------------
   *  | current_time_ms  | suffix |
   *  -----------------------------
   *  | 0-49             |      0 |
   *  | 50-99            |      1 |
   *  | 100-149          |      2 |
   *  | 150-199          |      3 |
   *  ...
   *  | 950-999          |     19 |
   *  -----------------------------
   */
  size_t getSubSecondTtlKeySuffix() {
    assert(subSecTTL_);

    // Get the milliseconds part of the current time.
    size_t currentMs = (nowUs() / 1000) % 1000;

    return currentMs / ttl_;
  }

  template <typename Request>
  std::string buildKey(const Request& req) {
    if (subSecTTL_) {
      return folly::to<std::string>(
          keyPrefix_,
          carbonLookasideHelper_.buildKey(req),
          keySuffix_,
          ":",
          getSubSecondTtlKeySuffix());
    }
    return folly::to<std::string>(
        keyPrefix_, carbonLookasideHelper_.buildKey(req), keySuffix_);
  }

  static std::string buildKeySuffix(size_t keySplitSize) {
    if (keySplitSize <= 1) {
      return "";
    }
    return folly::to<std::string>(":ks", globals::hostid() % keySplitSize);
  }
};

/**
 * Creates a carbon lookaside route-handle.
 *
 * Sample json format:
 * {
 *   "child": "PoolRoute|A",
 *   "ttl": 10, // 10 seconds
 *   "key_split_size": 3, // we will have 3 different keys for the same request
 *   "prefix": "reg",
 *   "flavor": "web",
 *   "helper_config": {
 *     // configs specific to the helper class.
 *   }
 * }
 */
template <class RouterInfo, class CarbonLookasideHelper>
typename RouterInfo::RouteHandlePtr createCarbonLookasideRoute(
    RouteHandleFactory<typename RouterInfo::RouteHandleIf>& factory,
    const folly::dynamic& json) {
  checkLogic(json.isObject(), "CarbonLookasideRoute is not an object");

  auto jChild = json.get_ptr("child");
  checkLogic(
      jChild != nullptr, "CarbonLookasideRoute: 'child' property is missing");

  auto child = factory.create(*jChild);
  checkLogic(
      child != nullptr,
      "CarbonLookasideRoute: cannot create route handle from 'child'");

  bool subSecTTL = false;
  if (auto jTtlUnit = json.get_ptr("ttl_unit_ms")) {
    checkLogic(
        jTtlUnit->isBool(),
        "CarbonLookasideRoute: 'ttl_unit_ms' is not a bool");
    if (jTtlUnit->getBool()) {
      subSecTTL = true;
    }
  }

  auto jTtl = json.get_ptr("ttl");
  checkLogic(
      jTtl != nullptr, "CarbonLookasideRoute: 'ttl' property is missing");
  checkLogic(jTtl->isInt(), "CarbonLookasideRoute: 'ttl' is not an integer");
  int32_t ttl = jTtl->getInt();

  if (subSecTTL) {
    checkLogic(
        ttl >= 10 && ttl < 1000 && (1000 % ttl == 0),
        "CarbonLookasideRoute: for sub-second ttl, you must use a number "
        "that is >= 10, < 1000, and 1000 must be a multiple of ttl.");
  }

  std::string prefix; // Defaults to no prefix.
  if (auto jPrefix = json.get_ptr("prefix")) {
    checkLogic(
        jPrefix->isString(), "CarbonLookasideRoute: 'prefix' is not a string");
    prefix = jPrefix->getString();
  }

  std::string flavor = "web"; // Defaults to web flavor.
  if (auto jFlavor = json.get_ptr("flavor")) {
    checkLogic(
        jFlavor->isString(), "CarbonLookasideRoute: 'flavor' is not a string");
    flavor = jFlavor->getString();
  }

  std::unordered_map<std::string, std::string> flavorOverrides;
  if (json.get_ptr("flavor_overrides")) {
    checkLogic(
        parse_json_options(json, "flavor_overrides", flavorOverrides),
        "CarbonLookasideRoute: error parsing 'flavor_overrides'");
  }

  size_t keySplitSize = 1;
  if (auto jKeySplitSize = json.get_ptr("key_split_size")) {
    checkLogic(
        jKeySplitSize->isInt() && jKeySplitSize->getInt() > 0,
        "CarbonLookasideRoute: 'key_split_size' must be a positive integer");
    keySplitSize = jKeySplitSize->getInt();
  }

  LeaseSettings leaseSettings = parseLeaseSettings(json);

  auto helperConfig = json.get_ptr("helper_config");
  if (helperConfig) {
    checkLogic(
        helperConfig->isObject(),
        "CarbonLookasideRoute: 'helper_config' is not an object");
  }
  CarbonLookasideHelper helper(helperConfig);

  // Creates a McRouter client to communicate with memcache using the
  // specified flavor information. The route handle owns the router resource
  // via a shared_ptr. The router will survive reconfigurations given that
  // at least one route handle will maintain a reference to it at any one time.
  // It will be cleaned up automatically whenever the last route handle using it
  // is removed.
  auto persistenceId = folly::to<std::string>("CarbonLookasideClient:", flavor);
  auto router =
      createCarbonLookasideRouter(persistenceId, flavor, flavorOverrides);
  if (!router) {
    LOG(ERROR) << "Failed to create router from flavor '" << flavor
               << "' for CarbonLookasideRouter.";
    return child;
  }

  CarbonRouterClient<MemcacheRouterInfo>::Pointer client{nullptr};
  try {
    client = router->createClient(0 /* max_outstanding_requests */);
  } catch (const std::runtime_error& e) {
    LOG(ERROR)
        << "Failed to create client for CarbonLookasideRouter. Exception: "
        << e.what();
    return child;
  }
  return makeRouteHandleWithInfo<
      RouterInfo,
      CarbonLookasideRoute,
      CarbonLookasideHelper>(
      std::move(child),
      std::move(router),
      std::move(client),
      std::move(prefix),
      keySplitSize,
      ttl,
      subSecTTL,
      std::move(helper),
      std::move(leaseSettings));
}

} // namespace mcrouter
} // namespace memcache
} // namespace facebook
