// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ModuleType.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "ModuleType.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace com {
namespace arges {
namespace file {
namespace proto {

namespace {

const ::google::protobuf::EnumDescriptor* MODULE_TYPE_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_ModuleType_2eproto() {
  protobuf_AddDesc_ModuleType_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "ModuleType.proto");
  GOOGLE_CHECK(file != NULL);
  MODULE_TYPE_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_ModuleType_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_ModuleType_2eproto() {
}

void protobuf_AddDesc_ModuleType_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020ModuleType.proto\022\024com.arges.file.proto"
    "*\336\006\n\013MODULE_TYPE\022\020\n\014WEB_C_SERVER\020d\022\020\n\014WE"
    "B_N_SERVER\020e\022\020\n\014WEB_F_SERVER\020f\022\020\n\014WEB_B_"
    "SERVER\020g\022\026\n\022WEB_N_SERVER_VALUE\020h\022\020\n\014C_TM"
    "S_SERVER\020\005\022\021\n\014C_ETS_SERVER\020\311\001\022\020\n\013C_DC_SE"
    "RVER\020\312\001\022\021\n\014C_DIS_SERVER\020\313\001\022\033\n\026C_DISCOVEY"
    "PROXY_SERVER\020\314\001\022\020\n\014C_DPX_SERVER\020\031\022\025\n\020C_V"
    "SQUARE_SERVER\020\316\001\022\021\n\014C_SIS_SERVER\020\317\001\022\021\n\014C"
    "_CMS_SERVER\020\320\001\022\024\n\017C_CSD_DC_SERVER\020\321\001\022\024\n\017"
    "C_CONSUL_SERVER\020\322\001\022\024\n\017C_CLIENT_SERVER\020\323\001"
    "\022\021\n\014C_BMS_SERVER\020\324\001\022\021\n\014C_BPX_SERVER\020\325\001\022\020"
    "\n\014C_VMS_SERVER\020\003\022\023\n\016C_KEYPX_SERVER\020\327\001\022\026\n"
    "\021C_CASPROXY_SERVER\020\330\001\022\020\n\014C_DMS_SERVER\020\002\022"
    "\022\n\rC_CSPX_SERVER\020\332\001\022\021\n\rC_DRPX_SERVER\020\006\022\020"
    "\n\014C_ATP_SERVER\020\025\022\020\n\014C_ATS_SERVER\020\020\022\020\n\014C_"
    "TPX_SERVER\020\010\022\021\n\014C_MTU_SERVER\020\333\001\022\021\n\014C_CLS"
    "_SERVER\020\334\001\022\020\n\014C_AML_SERVER\020\021\022\020\n\014C_VSS_SE"
    "RVER\020\001\022\020\n\014C_MTS_SERVER\020\000\022\021\n\rC_ALKG_SERVE"
    "R\020\023\022\022\n\016C_AWALL_SERVER\020\027\022\020\n\014C_AMS_SERVER\020"
    "\022\022\020\n\014C_SCS_SERVER\020 \022\020\n\014C_MGW_SERVER\020\033\022\020\n"
    "\014C_APL_SERVER\020\017\022\024\n\017C_ACTION_SERVER\020\345\001\022\014\n"
    "\007C_BDATA\020\346\001\022\026\n\021C_FACECALL_SERVER\020\347\001\022\n\n\005C"
    "_IOT\020\361\001\022\020\n\013C_CS_CLIENT\020\254\002", 905);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "ModuleType.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_ModuleType_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_ModuleType_2eproto {
  StaticDescriptorInitializer_ModuleType_2eproto() {
    protobuf_AddDesc_ModuleType_2eproto();
  }
} static_descriptor_initializer_ModuleType_2eproto_;
const ::google::protobuf::EnumDescriptor* MODULE_TYPE_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MODULE_TYPE_descriptor_;
}
bool MODULE_TYPE_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 5:
    case 6:
    case 8:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 21:
    case 23:
    case 25:
    case 27:
    case 32:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 201:
    case 202:
    case 203:
    case 204:
    case 206:
    case 207:
    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
    case 213:
    case 215:
    case 216:
    case 218:
    case 219:
    case 220:
    case 229:
    case 230:
    case 231:
    case 241:
    case 300:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace file
}  // namespace arges
}  // namespace com

// @@protoc_insertion_point(global_scope)
