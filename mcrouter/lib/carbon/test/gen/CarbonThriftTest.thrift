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
cpp_include "<mcrouter/lib/carbon/test/Timestamp.h>"

namespace cpp2 carbon.test.thrift
namespace py3 carbon.test.thrift
@cpp.Adapter{name = "carbon::test::TimestampAdapter"}
typedef i64 CustomAdapterTypeI64

@cpp.Adapter{name = "::carbon::test::DummyPairAdapter<::carbon::test::Timestamp,uint32_t>"}
typedef binary (cpp.type = "::folly::IOBuf") CustomAdapterTypeBinary


enum MyEnum {
  A = 0,
  B = 1,
  C = 2
}

union TestUnionThrift {
  1: carbon.ui64 a
  2: carbon.ui32 b
  3: carbon.ui16 c
}(cpp.methods = "
 public:
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

  template <class V>
  void foreachMember(V&& v);

  template <class V>
  void foreachMember(V&& v) const;
")
struct TinyStruct {
  1: i64 foo
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct MyBaseStruct {
  1: i64 baseInt64Member
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct MySimpleStruct {
  @thrift.Mixin
  -1: MyBaseStruct myBaseStruct
  1: i32 int32Member
  2: string stringMember
  3: MyEnum enumMember
  4: list<string> vectorMember
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct ThriftTestRequest {
  @thrift.Mixin
  -2: TinyStruct tinyStruct
  @thrift.Mixin
  -1: MySimpleStruct base
  1: carbon.IOBufKey key
  2: bool testBool
  3: byte testInt8
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
struct ThriftTestReply {
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
struct DummyThriftRequest {
  1: carbon.IOBufKey key
  2: bool testBool
  3: byte testInt8
  4: i16 testInt16
  5: i32 testInt32
  6: i64 testInt64
  7: carbon.ui8 testUInt8
  8: carbon.ui16 testUInt16
  9: carbon.ui32 testUInt32
  10: carbon.ui64 testUInt64
  11: float testFloat
  12: double testDouble
  13: string testShortString
  14: string testLongString
  15: carbon.IOBuf testIobuf
  16: list<string> testList
  17: optional bool testOptionalKeywordBool
  18: optional string testOptionalKeywordString
  19: optional carbon.IOBuf testOptionalKeywordIobuf
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
struct DummyThriftReply {
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
struct CustomRequest {
  1: carbon.IOBufKey key
  2: byte testInt8
  3: Timestamp_i64 timestamp
  4: optional CustomAdapterTypeI64 customAdapterTypeI64
  5: CustomAdapterTypeBinary customAdapterTypeBinary
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
struct CustomReply {
  1: carbon_result.Result result
  2: i32 valInt32
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

@cpp.Adapter{name = "::apache::thrift::IndirectionAdapter<Timestamp>"}
typedef i64 Timestamp_i64