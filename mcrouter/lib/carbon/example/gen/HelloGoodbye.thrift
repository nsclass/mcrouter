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
include "mcrouter/lib/carbon/carbon.thrift"
include "mcrouter/lib/carbon/carbon_result.thrift"
include "thrift/annotation/cpp.thrift"
include "thrift/annotation/thrift.thrift"
include "mcrouter/lib/network/gen/Common.thrift"

cpp_include "<mcrouter/lib/carbon/CarbonProtocolReader.h>"

namespace cpp2 hellogoodbye.thrift
namespace py3 hellogoodbye.thrift

@cpp.EnumType{type = cpp.EnumUnderlyingType.U32}
enum EnumUInt32 {
  HIGH = 0,
  URGENT = 1,
  YESTERDAY = 2
}

struct HelloRequest {
  1: carbon.IOBufKey key
  2: carbon.ui64 shardId
  3: carbon.ui64 deadlineMs
  4: string message
  5: EnumUInt32 priority
  6: carbon.ui64 beforeLatencyUs
  7: carbon.ui64 afterLatencyUs
  8: carbon.ui32 clientVersion
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

",
cpp.virtual
)
struct HelloReply {
  1: carbon_result.Result result
  2: string message
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

",
cpp.virtual
)
struct GoodbyeRequest {
  1: carbon.IOBufKey key
  2: carbon.ui64 shardId
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

",
cpp.virtual
)
struct GoodbyeReply {
  1: carbon_result.Result result
  2: string message
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

",
cpp.virtual
)

