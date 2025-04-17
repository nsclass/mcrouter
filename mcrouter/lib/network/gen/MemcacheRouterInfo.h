/*
 *  Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */

/*
 *  THIS FILE IS AUTOGENERATED. DO NOT MODIFY IT; ALL CHANGES WILL BE LOST IN
 *  VAIN.
 *
 *  @generated
 */
#pragma once

#include <chrono>
#include <functional>
#include <unordered_map>

#include <folly/Range.h>

#include <mcrouter/lib/carbon/Stats.h>

#include "mcrouter/lib/network/gen/MemcacheRouteHandleIf.h"
#include "mcrouter/lib/network/gen/MemcacheRouterStats.h"
#include "mcrouter/lib/network/gen/MemcacheRoutingGroups.h"

// Forward declarations
namespace folly {
struct dynamic;
class VirtualEventBase;
} // namespace folly
namespace facebook {
namespace memcache {
namespace thrift {
class Memcache;
} // namespace thrift
} // namespace memcache
} // namespace facebook

namespace facebook {
namespace memcache {
template <class RouteHandleIf>
class RouteHandleFactory;
namespace mcrouter {
template <class RouterInfo>
class ExtraRouteHandleProviderIf;
class ProxyBase;
} // namespace mcrouter
} // namespace memcache
} // namespace facebook

namespace facebook {
namespace memcache {
namespace mcrouter {
class AdditionalProxyRequestLogger;
} // namespace mcrouter
} // namespace memcache
} // namespace facebook

namespace facebook {
namespace memcache {

namespace detail {

using MemcacheRoutableRequests = carbon::List<
    McAddRequest,
    McAppendRequest,
    McCasRequest,
    McDecrRequest,
    McDeleteRequest,
    McFlushAllRequest,
    McFlushReRequest,
    McGatRequest,
    McGatsRequest,
    McGetRequest,
    McGetsRequest,
    McIncrRequest,
    McLeaseGetRequest,
    McLeaseSetRequest,
    McMetagetRequest,
    McPrependRequest,
    McReplaceRequest,
    McSetRequest,
    McTouchRequest>;
using MemcacheRoutableReplies = carbon::List<
    McAddReply,
    McAppendReply,
    McCasReply,
    McDecrReply,
    McDeleteReply,
    McFlushAllReply,
    McFlushReReply,
    McGatReply,
    McGatsReply,
    McGetReply,
    McGetsReply,
    McIncrReply,
    McLeaseGetReply,
    McLeaseSetReply,
    McMetagetReply,
    McPrependReply,
    McReplaceReply,
    McSetReply,
    McTouchReply>;
using MemcacheAllRequests = carbon::List<
    McAddRequest,
    McAppendRequest,
    McCasRequest,
    McDecrRequest,
    McDeleteRequest,
    McExecRequest,
    McFlushAllRequest,
    McFlushReRequest,
    McGatRequest,
    McGatsRequest,
    McGetRequest,
    McGetsRequest,
    McIncrRequest,
    McLeaseGetRequest,
    McLeaseSetRequest,
    McMetagetRequest,
    McPrependRequest,
    McQuitRequest,
    McReplaceRequest,
    McSetRequest,
    McShutdownRequest,
    McStatsRequest,
    McTouchRequest,
    McVersionRequest>;
} // namespace detail

struct MemcacheRouterInfo {
  using RouteHandleIf = MemcacheRouteHandleIf;
  using RouteHandlePtr = std::shared_ptr<RouteHandleIf>;
  using RouteHandleAsyncClient = apache::thrift::Client<facebook::memcache::thrift::Memcache>;

  static constexpr const char* name = "Memcache";
  static constexpr const bool bucketization = true;
  static constexpr const bool useRequestAclChecker = true;
  static constexpr const bool hasMcRefillRoute = false;

  template <class Route>
  using RouteHandle = MemcacheRouteHandle<Route>;
  using RoutableRequests = detail::MemcacheRoutableRequests;
  using RoutableReplies = detail::MemcacheRoutableReplies;
  using AllRequests = detail::MemcacheAllRequests;
  using AdditionalLogger = facebook::memcache::mcrouter::AdditionalProxyRequestLogger;
  using RouterStats = carbon::Stats<MemcacheRouterStatsConfig>;

  using RouteHandleFactoryMap = std::unordered_map<
      folly::StringPiece,
      std::function<RouteHandlePtr(
          facebook::memcache::RouteHandleFactory<RouteHandleIf>&,
          const folly::dynamic&)>,
      folly::Hash>;

  using RouteHandleFactoryMapWithProxy = std::unordered_map<
      folly::StringPiece,
      std::function<RouteHandlePtr(
          facebook::memcache::RouteHandleFactory<RouteHandleIf>&,
          const folly::dynamic&,
          facebook::memcache::mcrouter::ProxyBase&)>,
      folly::Hash>;

  using RouteHandleFactoryMapForWrapper = std::unordered_map<
      folly::StringPiece,
      std::function<RouteHandlePtr(
          RouteHandlePtr,
          facebook::memcache::mcrouter::ProxyBase&,
          const folly::dynamic&,
          facebook::memcache::RouteHandleFactory<RouteHandleIf>&)>,
      folly::Hash>;

  static RouteHandleFactoryMap buildRouteMap();
  static RouteHandleFactoryMapWithProxy buildRouteMapWithProxy();
  static RouteHandleFactoryMapForWrapper buildRouteMapForWrapper();
  static bool isSRLinked();

  static std::unique_ptr<facebook::memcache::mcrouter::
                             ExtraRouteHandleProviderIf<MemcacheRouterInfo>>
  buildExtraProvider();
};
} // namespace memcache
} // namespace facebook

#include "mcrouter/lib/network/gen/MemcacheThriftTransport.h"

#include <cstddef>
#include <memory>
#include <vector>

namespace facebook {
namespace memcache {

class FailoverErrorsSettings;

template <class RouteHandleIf>
class RouteHandleFactory;

namespace mcrouter {

template <
    class RouterInfo,
    typename FailoverPolicyT,
    typename FailoverErrorsSettingsT>
class FailoverRoute;

template <class RouterInfo>
std::shared_ptr<typename RouterInfo::RouteHandleIf> createHashRoute(
    const folly::dynamic& json,
    std::vector<std::shared_ptr<typename RouterInfo::RouteHandleIf>> rh,
    size_t threadId,
    ProxyBase& proxy);

template <class RouterInfo>
typename RouterInfo::RouteHandlePtr makeAllFastestRoute(
    RouteHandleFactory<typename RouterInfo::RouteHandleIf>& factory,
    const folly::dynamic& json);

template <
    class RouterInfo,
    template <class...>
    class RouteHandle,
    class FailoverErrorsSettingsT,
    class... Args>
std::shared_ptr<typename RouterInfo::RouteHandleIf>
makeFailoverRouteWithFailoverErrorSettings(
    const folly::dynamic& json,
    std::vector<std::shared_ptr<typename RouterInfo::RouteHandleIf>> children,
    FailoverErrorsSettingsT failoverErrors,
    const folly::dynamic* jFailoverPolicy,
    Args&&... args);

extern template facebook::memcache::MemcacheRouterInfo::RouteHandlePtr
createHashRoute<facebook::memcache::MemcacheRouterInfo>(
    const folly::dynamic& json,
    std::vector<facebook::memcache::MemcacheRouterInfo::RouteHandlePtr> rh,
    size_t threadId,
    ProxyBase& proxy);

extern template facebook::memcache::MemcacheRouterInfo::RouteHandlePtr
makeAllFastestRoute<facebook::memcache::MemcacheRouterInfo>(
    RouteHandleFactory<facebook::memcache::MemcacheRouterInfo::RouteHandleIf>& factory,
    const folly::dynamic& json);

extern template facebook::memcache::MemcacheRouterInfo::RouteHandlePtr
makeFailoverRouteWithFailoverErrorSettings<
    facebook::memcache::MemcacheRouterInfo,
    FailoverRoute,
    FailoverErrorsSettings>(
    const folly::dynamic& json,
    std::vector<facebook::memcache::MemcacheRouterInfo::RouteHandlePtr> children,
    FailoverErrorsSettings failoverErrors,
    const folly::dynamic* jFailoverPolicy);

} // namespace mcrouter
} // namespace memcache
} // namespace facebook
