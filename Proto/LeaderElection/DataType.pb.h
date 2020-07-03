// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataType.proto

#ifndef PROTOBUF_DataType_2eproto__INCLUDED
#define PROTOBUF_DataType_2eproto__INCLUDED

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
void  protobuf_AddDesc_DataType_2eproto();
void protobuf_AssignDesc_DataType_2eproto();
void protobuf_ShutdownFile_DataType_2eproto();


enum DATA_TYPE {
  REQ_WRITE_WRISTBAND_DATA = 1048576,
  RSP_WRITE_WRISTBAND_DATA = 1048577,
  REQ_SAVE_CAPTURE_FOR_ALARM = 1048592,
  RSP_SAVE_CAPTURE_FOR_ALARM = 1048593,
  REQ_WRITE_DATE_FOR_CAPTUR_MATCH = 1048608,
  RSP_WRITE_DATE_FOR_CAPTUR_MATCH = 1048609,
  REQ_ADD_SCANNER_DEVICE = 1048624,
  RSP_ADD_SCANNER_DEVICE = 1048625,
  REQ_UPDATE_SCANNER_DEVICE = 1048640,
  RSP_UPDATE_SCANNER_DEVICE = 1048641,
  REQ_DELETE_SCANNER_DEVICE = 1048656,
  RSP_DELETE_SCANNER_DEVICE = 1048657,
  REQ_ADD_WRISTAND_DEVICE = 1048672,
  RSP_ADD_WRISTAND_DEVICE = 1048673,
  REQ_DELETE_WRISTAND_DEVICE = 1048688,
  RSP_DELETE_WRISTAND_DEVICE = 1048689,
  REQ_CLEARALL_WRISTAND_DEVICE = 1048704,
  RSP_CLEARALL_WRISTAND_DEVICE = 1048705,
  RSP_ETS_NSERVER_WRISTAND_DATA = 1048720,
  REQ_GET_CLUSTER_NUM = 1048736,
  RSP_GET_CLUSTER_NUM = 1048737,
  REQ_GET_TVWALL_PLAN = 1048752,
  RSP_GET_TVWALL_PLAN = 1048753,
  REQ_RUN_TVWALL_PLAN = 1048768,
  REQ_STOP_TVWALL_PLAN = 1048784,
  REQ_RECEIVE_TVWALL_PLAN = 1048800,
  REQ_KPS_REGISTER = 1052672,
  RSP_KPS_REGISTER = 1052673,
  REQ_KPS_UNREGISTER = 1052688,
  RSP_KPS_UNREGISTER = 1052689,
  REQ_KPS_LOGIN = 1052704,
  RSP_KPS_LOGIN = 1052705,
  REQ_KPS_LOGOUT = 1052720,
  RSP_KPS_LOGOUT = 1052721,
  REQ_KPS_TVWALL = 1052736,
  RSP_KPS_TVWALL = 1052737,
  REQ_HM_CollectorData = 1056768,
  RSP_HM_CollectorData = 1056769,
  REQ_VIDEO = 1060864,
  RSP_VIDEO = 1060865,
  REQ_VIDEO_PROGRESS = 1060880,
  RSP_VIDEO_PROGRESS = 1060881,
  REQ_LOGIN_PTZ = 1060896,
  RSP_LOGIN_PTZ = 1060897,
  REQ_LOGINOUT_PTZ = 1060912,
  RSP_LOGINOUT_PTZ = 1060913,
  REQ_FACE_REGONI = 1064960,
  RSP_FACE_REGONI = 1064961,
  REQ_FACE_VEDIO = 1064976,
  RSP_FACE_VEDIO = 1064977,
  REQ_INSERT_WRISTBAND_TO_REAL_CHART = 1069056,
  REQ_INSERT_WRISTBAND_TO_HISTORY = 1069072,
  REQ_INSERT_ACTION_RECORD = 1069088,
  REQ_SELECT_RECORD_OF_SIGN_IN_BY_HISTORY = 1069104,
  REQ_SELECT_RECORD_OF_WRIST_REAL = 1069120,
  REQ_SELECT_PICTURE_OF_WRISTBAND = 1069136,
  RSP_SELECT_PICTURE_OF_WRISTBAND = 1069137,
  REQ_WRITE_RECORD_OF_VSQUARE = 1069152,
  REQ_OPR_TABLE_FOR_WRIST_HISTORY = 1069168,
  REQ_INSERT_SIGNIN_RECORD = 1069184,
  REQ_SELECT_SERVERID_BY_DEV_CODE = 1069200,
  RSP_SELECT_SERVERID_BY_DEV_CODE = 1069201,
  REQ_OPR_DEVICE_OF_UNDISTRIBUTED_ALARM = 1069216,
  REQ_OPR_DEVICE_OF_UNDISTRIBUTED_ENCODE = 1069232,
  REQ_OPR_SERVER_TABLE = 1069248,
  REQ_SELECT_ALL_SERVER_DATA = 1069264,
  RSP_SELECT_ALL_SERVER_DATA = 1069265,
  REQ_SELECT_ALL_UNDISTRIBUTED_ALARM_DEV = 1069280,
  RSP_SELECT_ALL_UNDISTRIBUTED_ALARM_DEV = 1069537,
  REQ_SELECT_ALL_UNDISTRIBUTED_ENCODE_DEV = 1069296,
  RSP_SELECT_ALL_UNDISTRIBUTED_ENCODE_DEV = 1069297,
  REQ_INSERT_DISTRIBUTED_INTO_UNDISTRIBUTED_ALARM = 1072912,
  REQ_INSERT_DISTRIBUTED_INTO_UNDISTRIBUTED_ENCODE = 1072928,
  REQ_INSERT_SERVERID_DEVICE_TO_ALARM = 1072944,
  REQ_INSERT_SERVERID_DEVICE_TO_ENCODE = 1072960,
  REQ_DELETE_DEVICE_BY_ALARM_SERVERID = 1072976,
  REQ_DELETE_DEVICE_BY_ENCODE_SERVERID = 1072992,
  REQ_UPDATE_DEV_FOR_SCANNER = 1073152,
  RSP_UPDATE_DEV_FOR_SCANNER = 1073153,
  REQ_DEV_INFO_FROM_DIS = 1073168,
  RSP_ADD_DEV_INFO_TO_BMS = 1073169,
  REQ_TMS_INFO_FROM_SIS = 1073184,
  RSP_TMS_INFO_FROM_SIS = 1073185,
  REQ_TMS_URL_FROM_DIS_BY_DEV_CODE = 1073200,
  RSP_TMS_URL_FROM_DIS_BY_DEV_CODE = 1073201,
  REQ_BMS_DEV_INFO_FROM_DC = 1077248,
  RSP_BMS_DEV_INFO_FROM_DC = 1077249,
  REQ_GET_ALARM_PLAN = 1077264,
  RSP_GET_ALARM_PLAN = 1077265,
  REQ_GET_SIGNIN_PIC_CODE = 1077280,
  RSP_DEV_INFO_FOR_SIGN_IN = 1077281,
  REQ_DMS_DEV_INFO_FROM_DC = 1077296,
  RSP_DMS_DEV_INFO_FROM_DC = 1077297,
  REQ_MYSQL_SERIVCE_MODIFY = 1077312,
  RSP_MYSQL_SERIVCE_MODIFY = 1077313,
  REQ_DEV_REGISTER_SERVER_INFO = 1077328,
  RSP_DEV_REGISTER_SERVER_INFO = 1077329,
  REQ_INSERT_ATTENDANCE_RECORD = 1077344,
  RSP_INSERT_ATTENDANCE_RECORD = 1077345,
  REQ_SERVICE_INFO_FROM_SIS = 1081344,
  RSP_SERVICE_INFO_FROM_SIS = 1081345,
  PUSH_EXCEPTION_SERVICE_INFO_FROM_SIS = 1081360,
  SUBSCRIBE_SERVICE_INFO_FROM_SIS = 1081361,
  REQ_REGISTER_TO_SIS = 1081376,
  RSP_REGISTER_FROM_SIS = 1081377,
  REQ_LOGOUT_FOR_SERVICE = 1081392,
  RSP_LOGOUT_FOR_SERVICE = 1081393,
  PUSH_MS_INFO_FROM_SIS = 1081410,
  REQ_ADD_DEVICE_FROM_BSERVER = 1085440,
  RSP_ADD_DEVICE_FROM_BSERVER = 1085441,
  REQ_UPDATE_DEVICE_FROM_BSERVER = 1085456,
  RSP_UPDATE_DEVICE_FROM_BSERVER = 1085457,
  REQ_DELETE_DEVICE_FROM_BSERVER = 1085472,
  RSP_DELETE_DEVICE_FROM_BSERVER = 1085473,
  REQ_BMS_TO_LEADER_HEART = 1089536,
  REQ_LEADER_TO_FOLLOWER_BROADCAST = 1089552,
  REQ_REQUESTVOTE_RPC = 1089568,
  REQ_RESPONEVOTE_RPC = 1089584,
  REQ_ADDDEV_TO_BPX = 1089600,
  REQ_DELDEV_TO_BPX = 1089616,
  REQ_MODIFYDEV_TO_BPX = 1089632,
  REQ_OPERATORDEV_TO_BPX = 1089648,
  REQ_BMS_ACCEPT_BPX = 1089664,
  REQ_BPX_CONNECT_TO_BMS = 1089680,
  REQ_BMS_ADD_DEVICE = 1089696,
  REQ_BMS_DEL_DEVICE = 1089712,
  REQ_BMS_UPDATE_DEVICE = 1089728,
  REQ_BMS_ADD_DEVICE_FROM_DIS = 1089744,
  REQ_BMS_UPDATE_DEVICE_FROM_DIS = 1089760,
  REQ_BPX_ASKFOR_BMS_FROM_LEADER = 1089776,
  REQ_LEADER_NOTICE_SIS = 1089792,
  REQ_LEADER_NOTIFY_BMS_GETDEV_FROM_DIS = 1089793,
  REQ_BMSBPXHEART = 1089794,
  REQ_BPX_DEVICE_STATUS_REPORT = 1089795,
  REQ_BPX_DEVICE_ALARM_REPORT = 1089796,
  REQ_ADD_SERVER = 1089797,
  REQ_DELETE_SERVER = 1089798,
  REQ_CASPROXY_LOGIN = 1093632,
  RSP_CASPROXY_LOGIN = 1093633,
  REQ_CASPROXY_LOGOUT = 1093648,
  RSP_CASPROXY_LOGOUT = 1093649
};
bool DATA_TYPE_IsValid(int value);
const DATA_TYPE DATA_TYPE_MIN = REQ_WRITE_WRISTBAND_DATA;
const DATA_TYPE DATA_TYPE_MAX = RSP_CASPROXY_LOGOUT;
const int DATA_TYPE_ARRAYSIZE = DATA_TYPE_MAX + 1;

const ::google::protobuf::EnumDescriptor* DATA_TYPE_descriptor();
inline const ::std::string& DATA_TYPE_Name(DATA_TYPE value) {
  return ::google::protobuf::internal::NameOfEnum(
    DATA_TYPE_descriptor(), value);
}
inline bool DATA_TYPE_Parse(
    const ::std::string& name, DATA_TYPE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DATA_TYPE>(
    DATA_TYPE_descriptor(), name, value);
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

template <> struct is_proto_enum< ::com::arges::file::proto::DATA_TYPE> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::com::arges::file::proto::DATA_TYPE>() {
  return ::com::arges::file::proto::DATA_TYPE_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_DataType_2eproto__INCLUDED