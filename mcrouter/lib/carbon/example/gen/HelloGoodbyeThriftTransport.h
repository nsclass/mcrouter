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

#include <exception>
#include <memory>

#include <folly/io/async/AsyncSSLSocket.h>
#include <mcrouter/lib/network/AsyncTlsToPlaintextSocket.h>
#include <mcrouter/lib/network/RpcStatsContext.h>
#include <mcrouter/lib/network/ThriftTransport.h>
#include <mcrouter/McrouterFiberContext.h>
#include <thrift/lib/cpp/TApplicationException.h>
#include <thrift/lib/cpp/transport/TTransportException.h>
#include <thrift/lib/cpp2/async/RequestChannel.h>

#include "mcrouter/lib/carbon/example/gen/gen-cpp2/HelloGoodbyeAsyncClient.h"

namespace facebook {
namespace memcache {

template <>
class ThriftTransportMethods<hellogoodbye::HelloGoodbyeRouterInfo> : public ThriftTransportUtil {
 public:
  ThriftTransportMethods() = default;
  virtual ~ThriftTransportMethods() override = default;

folly::Try<apache::thrift::RpcResponseComplete<hellogoodbye::GoodbyeReply>> sendSyncHelper(
    typename hellogoodbye::HelloGoodbyeRouterInfo::RouteHandleAsyncClient* thriftClient,
    const hellogoodbye::GoodbyeRequest& request,
    apache::thrift::RpcOptions& rpcOptions,
    RpcStatsContext* rpcStatsContext = nullptr) {
  bool needServerLoad = mcrouter::fiber_local<hellogoodbye::HelloGoodbyeRouterInfo>::getThriftServerLoadEnabled();
  if (FOLLY_UNLIKELY(needServerLoad)) {
    rpcOptions.setWriteHeader(kLoadHeader, kDefaultLoadCounter);
  }
  if (FOLLY_UNLIKELY(request.getCryptoAuthToken().has_value())) {
    rpcOptions.setWriteHeader(
        std::string{carbon::MessageCommon::kCryptoAuthTokenHeader}, request.getCryptoAuthToken().value());
  }
  if (FOLLY_UNLIKELY(request.getClientIdentifier().has_value())) {
    rpcOptions.setWriteHeader(
        std::string{carbon::MessageCommon::kClientIdentifierHeader}, request.getClientIdentifier().value());
  }
  rpcOptions.setContextPropMask(0);

#ifndef LIBMC_FBTRACE_DISABLE
  traceRequest(request, rpcOptions);
#endif
  auto reply = thriftClient->sync_complete_goodbye(
      std::move(rpcOptions), request);
  if (rpcStatsContext && reply.hasValue()) {
      auto& stats = reply->responseContext.rpcTransportStats;
      rpcStatsContext->requestBodySize = stats.requestSerializedSizeBytes;
      rpcStatsContext->replySizeBeforeCompression = stats.responseSerializedSizeBytes;
      rpcStatsContext->replySizeAfterCompression = stats.responseWireSizeBytes;
      if (FOLLY_UNLIKELY(needServerLoad && reply->responseContext.serverLoad)) {
        rpcStatsContext->serverLoad = ServerLoad(
            static_cast<int32_t>(*reply->responseContext.serverLoad));
      }
  }
#ifndef LIBMC_FBTRACE_DISABLE
  traceResponse(request, reply);
#endif
  return reply;
}

folly::Try<apache::thrift::RpcResponseComplete<hellogoodbye::HelloReply>> sendSyncHelper(
    typename hellogoodbye::HelloGoodbyeRouterInfo::RouteHandleAsyncClient* thriftClient,
    const hellogoodbye::HelloRequest& request,
    apache::thrift::RpcOptions& rpcOptions,
    RpcStatsContext* rpcStatsContext = nullptr) {
  bool needServerLoad = mcrouter::fiber_local<hellogoodbye::HelloGoodbyeRouterInfo>::getThriftServerLoadEnabled();
  if (FOLLY_UNLIKELY(needServerLoad)) {
    rpcOptions.setWriteHeader(kLoadHeader, kDefaultLoadCounter);
  }
  if (FOLLY_UNLIKELY(request.getCryptoAuthToken().has_value())) {
    rpcOptions.setWriteHeader(
        std::string{carbon::MessageCommon::kCryptoAuthTokenHeader}, request.getCryptoAuthToken().value());
  }
  if (FOLLY_UNLIKELY(request.getClientIdentifier().has_value())) {
    rpcOptions.setWriteHeader(
        std::string{carbon::MessageCommon::kClientIdentifierHeader}, request.getClientIdentifier().value());
  }
  rpcOptions.setContextPropMask(0);

#ifndef LIBMC_FBTRACE_DISABLE
  traceRequest(request, rpcOptions);
#endif
        rpcOptions.setWriteHeader("shardId", folly::to<std::string>(*request.shardId_ref()));
        rpcOptions.setWriteHeader("message", folly::to<std::string>(*request.message_ref()));
        rpcOptions.setWriteHeader("priority", folly::to<std::string>(*request.priority_ref()));
  auto reply = thriftClient->sync_complete_hello(
      std::move(rpcOptions), request);
  if (rpcStatsContext && reply.hasValue()) {
      auto& stats = reply->responseContext.rpcTransportStats;
      rpcStatsContext->requestBodySize = stats.requestSerializedSizeBytes;
      rpcStatsContext->replySizeBeforeCompression = stats.responseSerializedSizeBytes;
      rpcStatsContext->replySizeAfterCompression = stats.responseWireSizeBytes;
      if (FOLLY_UNLIKELY(needServerLoad && reply->responseContext.serverLoad)) {
        rpcStatsContext->serverLoad = ServerLoad(
            static_cast<int32_t>(*reply->responseContext.serverLoad));
      }
  }
#ifndef LIBMC_FBTRACE_DISABLE
  traceResponse(request, reply);
#endif
  return reply;
}

folly::Try<apache::thrift::RpcResponseComplete<McVersionReply>> sendSyncHelper(
    typename hellogoodbye::HelloGoodbyeRouterInfo::RouteHandleAsyncClient* thriftClient,
    const McVersionRequest& request,
    apache::thrift::RpcOptions& rpcOptions,
    RpcStatsContext* rpcStatsContext = nullptr) {
  bool needServerLoad = mcrouter::fiber_local<hellogoodbye::HelloGoodbyeRouterInfo>::getThriftServerLoadEnabled();
  if (FOLLY_UNLIKELY(needServerLoad)) {
    rpcOptions.setWriteHeader(kLoadHeader, kDefaultLoadCounter);
  }
  if (FOLLY_UNLIKELY(request.getCryptoAuthToken().has_value())) {
    rpcOptions.setWriteHeader(
        std::string{carbon::MessageCommon::kCryptoAuthTokenHeader}, request.getCryptoAuthToken().value());
  }
  if (FOLLY_UNLIKELY(request.getClientIdentifier().has_value())) {
    rpcOptions.setWriteHeader(
        std::string{carbon::MessageCommon::kClientIdentifierHeader}, request.getClientIdentifier().value());
  }
  rpcOptions.setContextPropMask(0);

#ifndef LIBMC_FBTRACE_DISABLE
  traceRequest(request, rpcOptions);
#endif
  auto reply = thriftClient->sync_complete_mcVersion(
      std::move(rpcOptions), request);
  if (rpcStatsContext && reply.hasValue()) {
      auto& stats = reply->responseContext.rpcTransportStats;
      rpcStatsContext->requestBodySize = stats.requestSerializedSizeBytes;
      rpcStatsContext->replySizeBeforeCompression = stats.responseSerializedSizeBytes;
      rpcStatsContext->replySizeAfterCompression = stats.responseWireSizeBytes;
      if (FOLLY_UNLIKELY(needServerLoad && reply->responseContext.serverLoad)) {
        rpcStatsContext->serverLoad = ServerLoad(
            static_cast<int32_t>(*reply->responseContext.serverLoad));
      }
  }
#ifndef LIBMC_FBTRACE_DISABLE
  traceResponse(request, reply);
#endif
  return reply;
}

 protected:
  std::optional<apache::thrift::Client<hellogoodbye::thrift::HelloGoodbye>> thriftClient_;
};

template <>
class ThriftTransport<hellogoodbye::HelloGoodbyeRouterInfo> : public ThriftTransportMethods<hellogoodbye::HelloGoodbyeRouterInfo>,
                                       public ThriftTransportBase {
 public:
  ThriftTransport(folly::EventBase& eventBase, ConnectionOptions options)
      : ThriftTransportBase(eventBase, std::move(options)) {}
  ThriftTransport(folly::VirtualEventBase& eventBase, ConnectionOptions options)
      : ThriftTransportBase(eventBase.getEventBase(), std::move(options)) {}
  ~ThriftTransport() {
    resetClient();
  }

  hellogoodbye::GoodbyeReply sendSync(
      const hellogoodbye::GoodbyeRequest& request,
      std::chrono::milliseconds timeout,
      RpcStatsContext* rpcStatsContext = nullptr) {

    return sendSyncImpl([this, &request, timeout, rpcStatsContext] {
      auto* thriftClient = getThriftClient();

      if (connectionOptions_.thriftCompression) {
        // Enable compression for this request type
        apache::thrift::CodecConfig codec;
        codec.zstdConfig_ref() = apache::thrift::ZstdCompressionCodecConfig();
        apache::thrift::CompressionConfig compressionConfig;
        if (connectionOptions_.thriftCompressionThreshold > 0) {
          compressionConfig.compressionSizeLimit_ref() =
              connectionOptions_.thriftCompressionThreshold;
        }
        compressionConfig.codecConfig_ref() = std::move(codec);
        auto* channel = static_cast<apache::thrift::RocketClientChannel*>(thriftClient_->getChannel());
        channel->setDesiredCompressionConfig(std::move(compressionConfig));
      }

      if (FOLLY_LIKELY(thriftClient != nullptr)) {
        auto rpcOptions = getRpcOptions(timeout);
        return sendSyncHelper(thriftClient, request, rpcOptions, rpcStatsContext);
      } else {
        return folly::Try<apache::thrift::RpcResponseComplete<hellogoodbye::GoodbyeReply>>(
            folly::make_exception_wrapper<apache::thrift::transport::TTransportException>(
              apache::thrift::transport::TTransportException::NOT_OPEN,
              "Error creating thrift client."));
      }
    });
  }

  hellogoodbye::HelloReply sendSync(
      const hellogoodbye::HelloRequest& request,
      std::chrono::milliseconds timeout,
      RpcStatsContext* rpcStatsContext = nullptr) {

    return sendSyncImpl([this, &request, timeout, rpcStatsContext] {
      auto* thriftClient = getThriftClient();

      if (connectionOptions_.thriftCompression) {
        // Disable compression for this request type
        apache::thrift::CompressionConfig compressionConfig;
        auto* channel = static_cast<apache::thrift::RocketClientChannel*>(thriftClient_->getChannel());
        channel->setDesiredCompressionConfig(std::move(compressionConfig));
      }

      if (FOLLY_LIKELY(thriftClient != nullptr)) {
        auto rpcOptions = getRpcOptions(timeout);
        return sendSyncHelper(thriftClient, request, rpcOptions, rpcStatsContext);
      } else {
        return folly::Try<apache::thrift::RpcResponseComplete<hellogoodbye::HelloReply>>(
            folly::make_exception_wrapper<apache::thrift::transport::TTransportException>(
              apache::thrift::transport::TTransportException::NOT_OPEN,
              "Error creating thrift client."));
      }
    });
  }

  McVersionReply sendSync(
      const McVersionRequest& request,
      std::chrono::milliseconds timeout,
      RpcStatsContext* rpcStatsContext = nullptr) {

    return sendSyncImpl([this, &request, timeout, rpcStatsContext] {
      auto* thriftClient = getThriftClient();
      if (FOLLY_LIKELY(thriftClient != nullptr)) {
        auto rpcOptions = getRpcOptions(timeout);
        return sendSyncHelper(thriftClient, request, rpcOptions, rpcStatsContext);
      } else {
        return folly::Try<apache::thrift::RpcResponseComplete<McVersionReply>>(
            folly::make_exception_wrapper<apache::thrift::transport::TTransportException>(
              apache::thrift::transport::TTransportException::NOT_OPEN,
              "Error creating thrift client."));
      }
    });
  }

 private:
  apache::thrift::Client<hellogoodbye::thrift::HelloGoodbye>* getThriftClient() {
    if (FOLLY_UNLIKELY(!thriftClient_)) {
      thriftClient_ = createThriftClient<apache::thrift::Client<hellogoodbye::thrift::HelloGoodbye>>();
    }
    if (FOLLY_LIKELY(thriftClient_.has_value())) {
      return &thriftClient_.value();
    }
    return nullptr;
  }

  void resetClient() override final {
    if (thriftClient_) {
      ThriftTransportBase::resetClient();
      thriftClient_.reset();
    }
  }
};

} // namespace memcache
} // namespace facebook