// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ModuleType.proto

#ifndef PROTOBUF_ModuleType_2eproto__INCLUDED
#define PROTOBUF_ModuleType_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)

namespace com {
namespace arges {
namespace file {
namespace proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ModuleType_2eproto();
void protobuf_AssignDesc_ModuleType_2eproto();
void protobuf_ShutdownFile_ModuleType_2eproto();


enum MODULE_TYPE {
  WEB_C_SERVER = 100,
  WEB_N_SERVER = 101,
  WEB_F_SERVER = 102,
  WEB_B_SERVER = 103,
  WEB_N_SERVER_VALUE = 104,
  C_TMS_SERVER = 5,
  C_ETS_SERVER = 201,
  C_DC_SERVER = 202,
  C_DIS_SERVER = 203,
  C_DISCOVEYPROXY_SERVER = 204,
  C_DPX_SERVER = 25,
  C_VSQUARE_SERVER = 206,
  C_SIS_SERVER = 207,
  C_CMS_SERVER = 208,
  C_CSD_DC_SERVER = 209,
  C_CONSUL_SERVER = 210,
  C_CLIENT_SERVER = 211,
  C_BMS_SERVER = 212,
  C_BPX_SERVER = 213,
  C_VMS_SERVER = 3,
  C_KEYPX_SERVER = 215,
  C_CASPROXY_SERVER = 216,
  C_DMS_SERVER = 2,
  C_CSPX_SERVER = 218,
  C_DRPX_SERVER = 6,
  C_ATP_SERVER = 21,
  C_ATS_SERVER = 16,
  C_TPX_SERVER = 8,
  C_MTU_SERVER = 219,
  C_CLS_SERVER = 220,
  C_AML_SERVER = 17,
  C_VSS_SERVER = 1,
  C_MTS_SERVER = 0,
  C_ALKG_SERVER = 19,
  C_AWALL_SERVER = 23,
  C_AMS_SERVER = 18,
  C_SCS_SERVER = 32,
  C_MGW_SERVER = 27,
  C_APL_SERVER = 15,
  C_ACTION_SERVER = 229,
  C_BDATA = 230,
  C_FACECALL_SERVER = 231,
  C_IOT = 241,
  C_CS_CLIENT = 300
};
bool MODULE_TYPE_IsValid(int value);
const MODULE_TYPE MODULE_TYPE_MIN = C_MTS_SERVER;
const MODULE_TYPE MODULE_TYPE_MAX = C_CS_CLIENT;
const int MODULE_TYPE_ARRAYSIZE = MODULE_TYPE_MAX + 1;

const ::google::protobuf::EnumDescriptor* MODULE_TYPE_descriptor();
inline const ::std::string& MODULE_TYPE_Name(MODULE_TYPE value) {
  return ::google::protobuf::internal::NameOfEnum(
    MODULE_TYPE_descriptor(), value);
}
inline bool MODULE_TYPE_Parse(
    const ::std::string& name, MODULE_TYPE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MODULE_TYPE>(
    MODULE_TYPE_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace file
}  // namespace arges
}  // namespace com

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::com::arges::file::proto::MODULE_TYPE> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::com::arges::file::proto::MODULE_TYPE>() {
  return ::com::arges::file::proto::MODULE_TYPE_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ModuleType_2eproto__INCLUDED
