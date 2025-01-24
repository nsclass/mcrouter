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

namespace cpp2 carbon.test.thrift
namespace py3 carbon.test.thrift

struct TestRequest {
  1: carbon.IOBufKey key
  2: bool dummy2
  3: bool testBool
  4: carbon.ui8 testChar
  5: byte testInt8
  6: i16 testInt16
  7: i32 testInt32
  8: i64 testInt64
  9: carbon.ui8 testUInt8
  10: carbon.ui16 testUInt16
  11: carbon.ui32 testUInt32
  12: carbon.ui64 testUInt64
  13: float testFloat
  14: double testDouble
  15: string testShortString
  16: string testLongString
  17: carbon.IOBuf testIobuf
  19: list<string> testList
  20: optional string testOptionalString
  21: optional carbon.IOBuf testOptionalIobuf
  22: bool dummy22
  23: bool dummy23
  24: list<list<carbon.ui64>> testNestedVec
  25: string_to_string_std_unordered_map testUMap
  26: double_to_double_std_map testMap
  27: string_to_list_carbon_ui16_std_map testComplexMap
  28: string_std_unordered_set testUSet
  29: carbon_ui64_std_set testSet
  30: optional bool testOptionalBool
  31: string dummy31
  32: list<carbon.IOBuf> testIOBufList
  33: string_to_string_folly_F14FastMap testF14FastMap
  34: string_to_string_folly_F14NodeMap testF14NodeMap
  35: string_to_string_folly_F14ValueMap testF14ValueMap
  36: string_to_string_folly_F14VectorMap testF14VectorMap
  37: string_folly_F14FastSet testF14FastSet
  38: string_folly_F14NodeSet testF14NodeSet
  39: string_folly_F14ValueSet testF14ValueSet
  40: string_folly_F14VectorSet testF14VectorSet
  41: optional string testOptionalKeywordString
  42: optional carbon.IOBuf testOptionalKeywordIobuf
  43: optional bool testOptionalKeywordBool
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
,
cpp.noncomparable
)
struct TestReply {
  1: carbon_result.Result result
  2: i32 valInt32
  3: i64 valInt64
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
struct TestRequestStringKey {
  1: carbon.StringKey key
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
struct TestReplyStringKey {
  1: carbon_result.Result result
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
struct TestOptionalBool {
  1: optional bool optionalBool
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
union TestUnion {
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
struct TestF14Containers {
  1: string_to_i64_folly_F14FastMap fastMap
  2: string_to_i64_folly_F14NodeMap nodeMap
  3: string_to_i64_folly_F14ValueMap valueMap
  4: string_to_i64_folly_F14VectorMap vectorMap
  5: i64_folly_F14FastSet fastSet
  6: i64_folly_F14FastSet nodeSet
  7: i64_folly_F14FastSet valueSet
  8: i64_folly_F14FastSet vectorSet
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct TestStdContainers {
  1: string_to_i64_std_unordered_map fastMap
  2: string_to_i64_std_unordered_map nodeMap
  3: string_to_i64_std_unordered_map valueMap
  4: string_to_i64_std_unordered_map vectorMap
  5: i64_std_unordered_set fastSet
  6: i64_std_unordered_set nodeSet
  7: i64_std_unordered_set valueSet
  8: i64_std_unordered_set vectorSet
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
@cpp.EnumType{type = cpp.EnumUnderlyingType.U32}
enum EnumUInt32 {
  AAA = 0,
  BBB = 1,
  CCC = 2
}

@cpp.EnumType{type = cpp.EnumUnderlyingType.U16}
enum EnumUInt16 {
  AAA = 0,
  BBB = 1,
  CCC = 2
}

@cpp.EnumType{type = cpp.EnumUnderlyingType.U8}
enum EnumUInt8 {
  AAA = 0,
  BBB = 1,
  CCC = 2
}


enum EnumInt32 {
  AAA = 0,
  BBB = 1,
  CCC = 2
}

@cpp.EnumType{type = cpp.EnumUnderlyingType.I16}
enum EnumInt16 {
  AAA = 0,
  BBB = 1,
  CCC = 2
}

@cpp.EnumType{type = cpp.EnumUnderlyingType.I8}
enum EnumInt8 {
  AAA = 0,
  BBB = 1,
  CCC = 2
}

struct StructWithEnumUInt32 {
  1: EnumUInt32 testEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithEnumUInt16 {
  1: EnumUInt16 testEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithEnumUInt8 {
  1: EnumUInt8 testEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithEnumInt32 {
  1: EnumInt32 testEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithEnumInt16 {
  1: EnumInt16 testEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithEnumInt8 {
  1: EnumInt8 testEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithOptionalEnumUInt32 {
  1: optional EnumUInt32 testEnum
  2: optional EnumUInt32 testEmptyEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithOptionalEnumUInt16 {
  1: optional EnumUInt16 testEnum
  2: optional EnumUInt16 testEmptyEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithOptionalEnumUInt8 {
  1: optional EnumUInt8 testEnum
  2: optional EnumUInt8 testEmptyEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithOptionalEnumInt32 {
  1: optional EnumInt32 testEnum
  2: optional EnumInt32 testEmptyEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithOptionalEnumInt16 {
  1: optional EnumInt16 testEnum
  2: optional EnumInt16 testEmptyEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")
struct StructWithOptionalEnumInt8 {
  1: optional EnumInt8 testEnum
  2: optional EnumInt8 testEmptyEnum
}(cpp.methods = "
  template <class V>
  void visitFields(V&& v);
  template <class V>
  void visitFields(V&& v) const;

  template <class Writer>
  void serialize(Writer&& writer) const;

  void deserialize(carbon::CarbonProtocolReader& reader);

")

@cpp.Type{name = "std::unordered_map<std::string, std::string>"}
typedef map<string, string> string_to_string_std_unordered_map
@cpp.Type{name = "std::map<double, double>"}
typedef map<double, double> double_to_double_std_map
@cpp.Type{name = "std::map<std::string, std::vector<uint16_t>>"}
typedef map<string, list<carbon.ui16>> string_to_list_carbon_ui16_std_map
@cpp.Type{name = "std::unordered_set<std::string>"}
typedef set<string> string_std_unordered_set
@cpp.Type{name = "std::set<uint64_t>"}
typedef set<carbon.ui64> carbon_ui64_std_set
@cpp.Type{name = "folly::F14FastMap<std::string, std::string>"}
typedef map<string, string> string_to_string_folly_F14FastMap
@cpp.Type{name = "folly::F14NodeMap<std::string, std::string>"}
typedef map<string, string> string_to_string_folly_F14NodeMap
@cpp.Type{name = "folly::F14ValueMap<std::string, std::string>"}
typedef map<string, string> string_to_string_folly_F14ValueMap
@cpp.Type{name = "folly::F14VectorMap<std::string, std::string>"}
typedef map<string, string> string_to_string_folly_F14VectorMap
@cpp.Type{name = "folly::F14FastSet<std::string>"}
typedef set<string> string_folly_F14FastSet
@cpp.Type{name = "folly::F14NodeSet<std::string>"}
typedef set<string> string_folly_F14NodeSet
@cpp.Type{name = "folly::F14ValueSet<std::string>"}
typedef set<string> string_folly_F14ValueSet
@cpp.Type{name = "folly::F14VectorSet<std::string>"}
typedef set<string> string_folly_F14VectorSet
@cpp.Type{name = "folly::F14FastMap<std::string, int64_t>"}
typedef map<string, i64> string_to_i64_folly_F14FastMap
@cpp.Type{name = "folly::F14NodeMap<std::string, int64_t>"}
typedef map<string, i64> string_to_i64_folly_F14NodeMap
@cpp.Type{name = "folly::F14ValueMap<std::string, int64_t>"}
typedef map<string, i64> string_to_i64_folly_F14ValueMap
@cpp.Type{name = "folly::F14VectorMap<std::string, int64_t>"}
typedef map<string, i64> string_to_i64_folly_F14VectorMap
@cpp.Type{name = "folly::F14FastSet<int64_t>"}
typedef set<i64> i64_folly_F14FastSet
@cpp.Type{name = "std::unordered_map<std::string, int64_t>"}
typedef map<string, i64> string_to_i64_std_unordered_map
@cpp.Type{name = "std::unordered_set<int64_t>"}
typedef set<i64> i64_std_unordered_set