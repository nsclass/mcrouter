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
  2: i64_6019 shardId
  3: i64_6019 deadlineMs
  4: string message
  5: EnumUInt32 priority
  6: i64_6019 beforeLatencyUs
  7: i64_6019 afterLatencyUs
  8: i32_3782 clientVersion
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
  2: i64_6019 shardId
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

// The following were automatically generated and may benefit from renaming.
typedef i32 (cpp.type = "uint32_t") i32_3782
typedef i64 (cpp.type = "uint64_t") i64_6019
