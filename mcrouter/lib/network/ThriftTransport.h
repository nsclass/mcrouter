/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <chrono>
#include <memory>
#include <type_traits>

#include <folly/Conv.h>
#include <folly/Range.h>
#include <folly/io/async/AsyncTransport.h>
#include <folly/io/async/VirtualEventBase.h>
#include <thrift/lib/cpp2/async/RequestCallback.h>
#include <thrift/lib/cpp2/async/RequestChannel.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>

#include "mcrouter/lib/Reply.h"
#include "mcrouter/lib/mc/protocol.h"
#include "mcrouter/lib/network/ConnectionOptions.h"
#include "mcrouter/lib/network/RpcStatsContext.h"
#include "mcrouter/lib/network/SecurityOptions.h"
#include "mcrouter/lib/network/SocketUtil.h"
#include "mcrouter/lib/network/Transport.h"

namespace facebook {
namespace memcache {

/**
 * Represents a Thrift Transport.
 * The concrete thrift transport class is generated by carbon compiler.
 */
class ThriftTransportBase : public Transport,
                            private folly::AsyncSocket::ConnectCallback,
                            private apache::thrift::CloseCallback {
 public:
  ThriftTransportBase(folly::EventBase& eventBase, ConnectionOptions options);
  virtual ~ThriftTransportBase() override = default;

  static constexpr folly::StringPiece name() {
    return "ThriftTransport";
  }

  static constexpr bool isCompatible(mc_protocol_t protocol) {
    return protocol == mc_thrift_protocol;
  }

  void closeNow() override final;

  void setConnectionStatusCallbacks(
      ConnectionStatusCallbacks callbacks) override final;

  void setRequestStatusCallbacks(
      RequestStatusCallbacks callbacks) override final;

  void setAuthorizationCallbacks(
      AuthorizationCallbacks callbacks) override final;

  void setThrottle(size_t maxInflight, size_t maxPending) override final;

  RequestQueueStats getRequestQueueStats() const override final;

  void updateTimeoutsIfShorter(
      std::chrono::milliseconds /* connectTimeout */,
      std::chrono::milliseconds /* writeTimeout */) override final;

  const folly::AsyncTransportWrapper* getTransport() const override final;

  double getRetransmitsPerKb() override final;

 protected:
  folly::EventBase& eventBase_;
  const ConnectionOptions connectionOptions_;
  std::shared_ptr<apache::thrift::RocketClientChannel> channel_;

  // Callbacks
  ConnectionStatusCallbacks connectionCallbacks_;
  RequestStatusCallbacks requestCallbacks_;
  AuthorizationCallbacks authorizationCallbacks_;

  // Throttle options (disabled by default).
  size_t maxInflight_{0};
  size_t maxPending_{0};

  // Data about the connection
  ConnectionState connectionState_{ConnectionState::Down};
  bool connectionTimedOut_{false};

  template <class ThriftClient>
  std::optional<ThriftClient> createThriftClient();

  /**
   * Resets the client pointer.
   * Will only be called after draining the request queue.
   */
  virtual void resetClient() = 0;

  template <class F>
  auto sendSyncImpl(F&& sendFunc);

 private:
  // AsyncSocket::ConnectCallback overrides
  void connectSuccess() noexcept final;
  void connectErr(const folly::AsyncSocketException& ex) noexcept final;

  // thrift::CloseCallback overrides
  void channelClosed() override final;

  /**
   * Create a channel and trigger connection opening.
   * Returns either a valid RocketClientChannel, or nullptr in case of error.
   */
  apache::thrift::RocketClientChannel::Ptr createChannel();

  /**
   * Creates a new socket and initiates a connection.
   * Returns either valid connection (or possibly connected) socket, or nullptr
   * in case of error.
   */
  folly::AsyncTransportWrapper::UniquePtr getConnectingSocket();
};

template <class RouterInfo>
class ThriftTransport : public ThriftTransportBase {
 public:
  ThriftTransport(folly::VirtualEventBase& eventBase, ConnectionOptions options)
      : ThriftTransportBase(eventBase.getEventBase(), std::move(options)) {}
  ~ThriftTransport() override = default;

  template <class Request>
  ReplyT<Request> sendSync(
      const Request& /* request */,
      std::chrono::milliseconds /* timeout */,
      RpcStatsContext* /* rpcContext */ = nullptr) {
    throw std::logic_error(folly::to<std::string>(
        "Router ", RouterInfo::name, " does not support thrift transport"));
  }

  void resetClient() override final {}

  void setFlushList(FlushList* /* flushList */) override final {}
};

class ThriftTransportUtil {
 public:
  static inline const std::string kLoadHeader = "load";
  static inline const std::string kDefaultLoadCounter = "default";

  ThriftTransportUtil() = default;
  virtual ~ThriftTransportUtil() = default;

#ifndef LIBMC_FBTRACE_DISABLE
  void traceRequest(
      const carbon::MessageCommon& request,
      apache::thrift::RpcOptions& opts);

  template <class Response>
  void traceResponse(
      const carbon::MessageCommon& request,
      folly::Try<apache::thrift::RpcResponseComplete<Response>>& response);
#endif

  static apache::thrift::RpcOptions getRpcOptions(
      std::chrono::milliseconds timeout);

 private:
#ifndef LIBMC_FBTRACE_DISABLE
  void FOLLY_NOINLINE traceRequestImpl(
      const carbon::MessageCommon& request,
      apache::thrift::RpcOptions& opts);

  void FOLLY_NOINLINE traceResponseImpl(
      carbon::MessageCommon& response,
      const std::map<std::string, std::string>& responseHeaders);
#endif
};

template <class RouterInfo>
class ThriftTransportMethods : public ThriftTransportUtil {
 public:
  ThriftTransportMethods() = default;
  virtual ~ThriftTransportMethods() override = default;
};

} // namespace memcache
} // namespace facebook

#include "mcrouter/lib/network/ThriftTransport-inl.h"
