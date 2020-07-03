// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: DataType.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "DataType.pb.h"

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

const ::google::protobuf::EnumDescriptor* DATA_TYPE_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_DataType_2eproto() {
  protobuf_AddDesc_DataType_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "DataType.proto");
  GOOGLE_CHECK(file != NULL);
  DATA_TYPE_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_DataType_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_DataType_2eproto() {
}

void protobuf_AddDesc_DataType_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016DataType.proto\022\024com.arges.file.proto*\266"
    "A\n\tDATA_TYPE\022\036\n\030REQ_WRITE_WRISTBAND_DATA"
    "\020\200\200@\022\036\n\030RSP_WRITE_WRISTBAND_DATA\020\201\200@\022 \n\032"
    "REQ_SAVE_CAPTURE_FOR_ALARM\020\220\200@\022 \n\032RSP_SA"
    "VE_CAPTURE_FOR_ALARM\020\221\200@\022%\n\037REQ_WRITE_DA"
    "TE_FOR_CAPTUR_MATCH\020\240\200@\022%\n\037RSP_WRITE_DAT"
    "E_FOR_CAPTUR_MATCH\020\241\200@\022\034\n\026REQ_ADD_SCANNE"
    "R_DEVICE\020\260\200@\022\034\n\026RSP_ADD_SCANNER_DEVICE\020\261"
    "\200@\022\037\n\031REQ_UPDATE_SCANNER_DEVICE\020\300\200@\022\037\n\031R"
    "SP_UPDATE_SCANNER_DEVICE\020\301\200@\022\037\n\031REQ_DELE"
    "TE_SCANNER_DEVICE\020\320\200@\022\037\n\031RSP_DELETE_SCAN"
    "NER_DEVICE\020\321\200@\022\035\n\027REQ_ADD_WRISTAND_DEVIC"
    "E\020\340\200@\022\035\n\027RSP_ADD_WRISTAND_DEVICE\020\341\200@\022 \n\032"
    "REQ_DELETE_WRISTAND_DEVICE\020\360\200@\022 \n\032RSP_DE"
    "LETE_WRISTAND_DEVICE\020\361\200@\022\"\n\034REQ_CLEARALL"
    "_WRISTAND_DEVICE\020\200\201@\022\"\n\034RSP_CLEARALL_WRI"
    "STAND_DEVICE\020\201\201@\022\026\n\020REQ_INTO_MEETING\020\220\201@"
    "\022\026\n\020RSP_INTO_MEETING\020\221\201@\022 \n\032REQ_UPDATE_W"
    "RISTAND_DEVICE\020\240\201@\022 \n\032RSP_UPDATE_WRISTAN"
    "D_DEVICE\020\241\201@\022\026\n\020REQ_STOP_MEETING\020\300\201@\022\026\n\020"
    "RSP_STOP_MEETING\020\301\201@\022\030\n\022REQ_DELETE_MEETI"
    "NG\020\320\201@\022\030\n\022RSP_DELETE_MEETING\020\321\201@\022\026\n\020REQ_"
    "KPS_REGISTER\020\200\240@\022\026\n\020RSP_KPS_REGISTER\020\201\240@"
    "\022\030\n\022REQ_KPS_UNREGISTER\020\220\240@\022\030\n\022RSP_KPS_UN"
    "REGISTER\020\221\240@\022\023\n\rREQ_KPS_LOGIN\020\240\240@\022\023\n\rRSP"
    "_KPS_LOGIN\020\241\240@\022\024\n\016REQ_KPS_LOGOUT\020\260\240@\022\024\n\016"
    "RSP_KPS_LOGOUT\020\261\240@\022\024\n\016REQ_KPS_TVWALL\020\300\240@"
    "\022\024\n\016RSP_KPS_TVWALL\020\301\240@\022\025\n\017REQ_TVWALL_PLA"
    "N\020\320\240@\022\025\n\017RSP_TVWALL_PLAN\020\321\240@\022\025\n\017REQ_TVWA"
    "LL_TASK\020\340\240@\022\025\n\017RSP_TVWALL_TASK\020\341\240@\022\024\n\016RE"
    "Q_TVWALL_NEW\020\360\240@\022\024\n\016RSP_TVWALL_NEW\020\361\240@\022\032"
    "\n\024REQ_TVWALL_PLAN_SYNC\020\200\241@\022\032\n\024RSP_TVWALL"
    "_PLAN_SYNC\020\201\241@\022\031\n\023REQ_TVWALL_FUNCTION\020\220\241"
    "@\022\031\n\023RSP_TVWALL_FUNCTION\020\221\241@\022\032\n\024REQ_HM_C"
    "ollectorData\020\200\300@\022\032\n\024RSP_HM_CollectorData"
    "\020\201\300@\022\017\n\tREQ_VIDEO\020\200\340@\022\017\n\tRSP_VIDEO\020\201\340@\022\030"
    "\n\022REQ_VIDEO_PROGRESS\020\220\340@\022\030\n\022RSP_VIDEO_PR"
    "OGRESS\020\221\340@\022\023\n\rREQ_LOGIN_PTZ\020\240\340@\022\023\n\rRSP_L"
    "OGIN_PTZ\020\241\340@\022\026\n\020REQ_LOGINOUT_PTZ\020\260\340@\022\026\n\020"
    "RSP_LOGINOUT_PTZ\020\261\340@\022\025\n\017REQ_FACE_REGONI\020"
    "\200\200A\022\025\n\017RSP_FACE_REGONI\020\201\200A\022\024\n\016REQ_FACE_V"
    "EDIO\020\220\200A\022\024\n\016RSP_FACE_VEDIO\020\221\200A\022(\n\"REQ_IN"
    "SERT_WRISTBAND_TO_REAL_CHART\020\200\240A\022(\n\"RSP_"
    "INSERT_WRISTBAND_TO_REAL_CHART\020\201\240A\022%\n\037RE"
    "Q_INSERT_WRISTBAND_TO_HISTORY\020\220\240A\022%\n\037RSP"
    "_INSERT_WRISTBAND_TO_HISTORY\020\221\240A\022\036\n\030REQ_"
    "INSERT_ACTION_RECORD\020\240\240A\022\036\n\030RSP_INSERT_A"
    "CTION_RECORD\020\241\240A\022%\n\037REQ_SELECT_PICTURE_O"
    "F_WRISTBAND\020\320\240A\022%\n\037RSP_SELECT_PICTURE_OF"
    "_WRISTBAND\020\321\240A\022!\n\033REQ_WRITE_RECORD_OF_VS"
    "QUARE\020\340\240A\022 \n\032REQ_WRITE_SERVER_ROLE_DATA\020"
    "\360\242A\022 \n\032RSP_WRITE_SERVER_ROLE_DATA\020\361\242A\022\036\n"
    "\030REQ_SIGNIN_DATA_OF_PHOTO\020\200\243A\022\036\n\030RSP_SIG"
    "NIN_DATA_OF_PHOTO\020\201\243A\022\037\n\031REQ_SIGNIN_PHOT"
    "O_FOR_REAL\020\220\243A\022\037\n\031RSP_SIGNIN_PHOTO_FOR_R"
    "EAL\020\221\243A\022\026\n\020REQ_HOT_MAP_DATA\020\240\243A\022\026\n\020RSP_H"
    "OT_MAP_DATA\020\241\243A\022 \n\032REQ_UPDATE_DEV_FOR_SC"
    "ANNER\020\200\300A\022 \n\032RSP_UPDATE_DEV_FOR_SCANNER\020"
    "\201\300A\022\033\n\025REQ_DEV_INFO_FROM_DIS\020\220\300A\022\035\n\027RSP_"
    "ADD_DEV_INFO_TO_BMS\020\221\300A\022\033\n\025REQ_TMS_INFO_"
    "FROM_SIS\020\240\300A\022\033\n\025RSP_TMS_INFO_FROM_SIS\020\241\300"
    "A\022&\n REQ_TMS_URL_FROM_DIS_BY_DEV_CODE\020\260\300"
    "A\022&\n RSP_TMS_URL_FROM_DIS_BY_DEV_CODE\020\261\300"
    "A\022\036\n\030REQ_OWNERSHIP_FOR_DEVICE\020\300\300A\022\036\n\030RSP"
    "_OWNERSHIP_FOR_DEVICE\020\301\300A\022\024\n\016REQ_ADD_DEV"
    "ICE\020\320\300A\022\024\n\016RSP_ADD_DEVICE\020\321\300\005\022\027\n\021REQ_MOD"
    "IFY_DEVICE\020\340\300A\022\027\n\021RSP_MODIFY_DEVICE\020\341\300A\022"
    "\027\n\021REQ_DELETE_DEVICE\020\360\300A\022\027\n\021RSP_DELETE_D"
    "EVICE\020\361\300A\022\033\n\025REQ_DISTRIBUTE_DEVICE\020\200\301A\022\033"
    "\n\025RSP_DISTRIBUTE_DEVICE\020\201\301A\022#\n\035REQ_ADD_B"
    "USINESS_ORGANIZATION\020\220\301A\022#\n\035RSP_ADD_BUSI"
    "NESS_ORGANIZATION\020\221\301A\022\'\n!REQ_UPDATE_BUSI"
    "NIESS_ORGANIZATION\020\240\301A\022\'\n!RSP_UPDATE_BUS"
    "INIESS_ORGANIZATION\020\241\301A\022\'\n!REQ_DELETE_BU"
    "SINIESS_ORGANIZATION\020\260\301A\022\'\n!RSP_DELETE_B"
    "USINIESS_ORGANIZATION\020\261\301A\022\032\n\024REPORT_DEVI"
    "CE_MODIFY\020\303\301A\022\036\n\030REQ_BMS_DEV_INFO_FROM_D"
    "C\020\200\340A\022\036\n\030RSP_BMS_DEV_INFO_FROM_DC\020\201\340A\022\030\n"
    "\022REQ_GET_ALARM_PLAN\020\220\340A\022\030\n\022RSP_GET_ALARM"
    "_PLAN\020\221\340A\022\035\n\027REQ_GET_SIGNIN_PIC_CODE\020\240\340A"
    "\022\036\n\030RSP_DEV_INFO_FOR_SIGN_IN\020\241\340A\022\036\n\030REQ_"
    "DMS_DEV_INFO_FROM_DC\020\260\340A\022\036\n\030RSP_DMS_DEV_"
    "INFO_FROM_DC\020\261\340A\022\026\n\020REQ_ORGANIZATION\020\300\340A"
    "\022\026\n\020RSP_ORGANIZATION\020\301\340A\022\035\n\027REQ_ENCODE_C"
    "HANNEL_INFO\020\320\340A\022\035\n\027RSP_ENCODE_CHANNEL_IN"
    "FO\020\321\340A\022\025\n\017REQ_REGION_INFO\020\340\340A\022\025\n\017RSP_REG"
    "ION_INFO\020\341\340A\022\025\n\017REQ_DEVICE_INFO\020\360\340A\022\025\n\017R"
    "SP_DEVICE_INFO\020\361\340A\022#\n\035REQ_SERVICE_INFO_F"
    "OR_REGISTER\020\200\341A\022#\n\035RSP_SERVICE_INFO_FOR_"
    "REGISTER\020\201\341A\022\037\n\031REQ_RECODE_FOR_ATTENDANC"
    "E\020\220\341A\022\037\n\031RSP_RECODE_FOR_ATTENDANCE\020\221\341A\022\025"
    "\n\017REQ_USER_DOMAIN\020\240\341A\022\025\n\017RSP_USER_DOMAIN"
    "\020\241\341A\022\032\n\024REQ_SERVICE_REGISTER\020\260\341A\022\032\n\024RSP_"
    "SERVICE_REGISTER\020\261\341A\022\033\n\025REQ_DOMAIN_FOR_D"
    "EVICE\020\300\341A\022\033\n\025RSP_DOMAIN_FOR_DEVICE\020\301\341A\022\034"
    "\n\026REQ_GET_WRISTUSER_NAME\020\320\341A\022\034\n\026RSP_GET_"
    "WRISTUSER_NAME\020\321\341A\022\032\n\024REQ_GET_MEETING_DA"
    "TA\020\340\341A\022\032\n\024RSP_GET_MEETING_DATA\020\341\341A\022\035\n\027RE"
    "Q_DATA_FOR_RAISE_DUST\020\360\341A\022\035\n\027RSP_DATA_FO"
    "R_RAISE_DUST\020\361\341A\022 \n\032REPORT_DATA_FOR_RAIS"
    "E_DUST\020\363\341A\022\036\n\030REQ_INSERT_SIGNIN_RECORD\020\200"
    "\342A\022\036\n\030RSP_INSERT_SIGNIN_RECORD\020\201\342A\022\037\n\031RE"
    "Q_GET_RECORD_OF_SIGN_IN\020\220\342A\022\037\n\031RSP_GET_R"
    "ECORD_OF_SIGN_IN\020\221\342A\022$\n\036REQ_INSERT_ALARM"
    "_OF_RAISE_DUST\020\240\342A\022$\n\036RSP_INSERT_ALARM_O"
    "F_RAISE_DUST\020\241\342A\022\"\n\034REQ_ALARM_PLAN_OF_RA"
    "ISE_DUST\020\260\342A\022\"\n\034RSP_ALARM_PLAN_OF_RAISE_"
    "DUST\020\261\342A\022\034\n\026REQ_UPDATE_DEVICE_INFO\020\300\342A\022\034"
    "\n\026RSP_UPDATE_DEVICE_INFO\020\301\342A\022\024\n\016REQ_ALAR"
    "M_TYPE\020\320\342A\022\024\n\016RSP_ALARM_TYPE\020\321\342A\022\025\n\017REQ_"
    "ACTION_TYPE\020\340\342A\022\025\n\017RSP_ACTION_TYPE\020\341\342A\022\034"
    "\n\026REQ_GET_WRISTUSER_DATA\020\360\342A\022\034\n\026RSP_GET_"
    "WRISTUSER_DATA\020\361\342A\022\025\n\017REQ_MEETING_ALL\020\200\343"
    "A\022\025\n\017RSP_MEETING_ALL\020\201\343A\022\033\n\025REQ_UPDATE_A"
    "TTENDANCE\020\220\343A\022\033\n\025RSP_UPDATE_ATTENDANCE\020\221"
    "\343A\022\037\n\031REQ_SERVICE_INFO_FROM_SIS\020\200\200B\022\037\n\031R"
    "SP_SERVICE_INFO_FROM_SIS\020\201\200B\022*\n$PUSH_EXC"
    "EPTION_SERVICE_INFO_FROM_SIS\020\220\200B\022%\n\037SUBS"
    "CRIBE_SERVICE_INFO_FROM_SIS\020\221\200B\022\031\n\023REQ_R"
    "EGISTER_TO_SIS\020\240\200B\022\033\n\025RSP_REGISTER_FROM_"
    "SIS\020\241\200B\022\034\n\026REQ_LOGOUT_FOR_SERVICE\020\260\200B\022\034\n"
    "\026RSP_LOGOUT_FOR_SERVICE\020\261\200B\022\033\n\025PUSH_MS_I"
    "NFO_FROM_SIS\020\302\200B\022\026\n\020REQ_SERVICE_INFO\020\320\200B"
    "\022\026\n\020RSP_SERVICE_INFO\020\321\200B\022\030\n\022REQ_SERVICE_"
    "MODIFY\020\340\200B\022\030\n\022RSP_SERVICE_MODIFY\020\341\200B\022!\n\033"
    "REQ_ADD_DEVICE_FROM_BSERVER\020\200\240B\022!\n\033RSP_A"
    "DD_DEVICE_FROM_BSERVER\020\201\240B\022$\n\036REQ_UPDATE"
    "_DEVICE_FROM_BSERVER\020\220\240B\022$\n\036RSP_UPDATE_D"
    "EVICE_FROM_BSERVER\020\221\240B\022$\n\036REQ_DELETE_DEV"
    "ICE_FROM_BSERVER\020\240\240B\022$\n\036RSP_DELETE_DEVIC"
    "E_FROM_BSERVER\020\241\240B\022)\n#REQ_ADD_ALARMTHRES"
    "HOLD_FROM_BSERVER\020\261\240B\022,\n&REQ_UPDATE_ALAR"
    "MTHRESHOLD_FROM_BSERVER\020\262\240B\022,\n&REQ_DELET"
    "E_ALARMTHRESHOLD_FROM_BSERVER\020\263\240B\022\035\n\027REQ"
    "_BMS_TO_LEADER_HEART\020\200\300B\022&\n REQ_LEADER_T"
    "O_FOLLOWER_BROADCAST\020\220\300B\022\031\n\023REQ_REQUESTV"
    "OTE_RPC\020\240\300B\022\031\n\023REQ_RESPONEVOTE_RPC\020\260\300B\022\027"
    "\n\021REQ_ADDDEV_TO_BPX\020\300\300B\022\027\n\021REQ_DELDEV_TO"
    "_BPX\020\320\300B\022\032\n\024REQ_MODIFYDEV_TO_BPX\020\340\300B\022\034\n\026"
    "REQ_OPERATORDEV_TO_BPX\020\360\300B\022\030\n\022REQ_BMS_AC"
    "CEPT_BPX\020\200\301B\022\034\n\026REQ_BPX_CONNECT_TO_BMS\020\220"
    "\301B\022\030\n\022REQ_BMS_ADD_DEVICE\020\240\301B\022\030\n\022REQ_BMS_"
    "DEL_DEVICE\020\260\301B\022\033\n\025REQ_BMS_UPDATE_DEVICE\020"
    "\300\301B\022%\n\037NOTICE_NOISE_THRESHOLD_OF_RAISE\020\322"
    "\301B\022!\n\033REPORT_NOISE_ALARM_OF_RAISE\020\323\301B\022\030\n"
    "\022REQ_CASPROXY_LOGIN\020\200\340B\022\030\n\022RSP_CASPROXY_"
    "LOGIN\020\201\340B\022\031\n\023REQ_CASPROXY_LOGOUT\020\220\340B\022\031\n\023"
    "RSP_CASPROXY_LOGOUT\020\221\340B\022\017\n\tREQ_MEDIA\020\200\200C"
    "\022\017\n\tRSP_MEDIA\020\201\200C\022\034\n\026REQ_CONTROL_FOR_DEV"
    "ICE\020\240\200C\022\034\n\026RSP_CONTROL_FOR_DEVICE\020\241\200C\022\036\n"
    "\030REPORT_STATUS_FOR_DEVICE\020\263\200C\022\034\n\026REQ_ACT"
    "ION_FOR_CAPTURE\020\300\200C\022\034\n\026RSP_ACTION_FOR_CA"
    "PTURE\020\301\200C\022\024\n\016REQ_TOKEN_PAIR\020\320\200C\022\024\n\016RSP_T"
    "OKEN_PAIR\020\321\200C\022\026\n\020REQ_GETWRISTDATA\020\340\200C\022\026\n"
    "\020RSP_GETWRISTDATA\020\341\200C\022!\n\033REPORT_STAT_OF_"
    "MEETING_SHOW\020\343\200C\022\030\n\022REQ_CREATE_CHANNEL\020\360"
    "\200C\022\030\n\022RSP_CREATE_CHANNEL\020\361\200C\022!\n\033REQ_ADD_"
    "ALARM_PLAN_FROM_WEB\020\200\240C\022\037\n\031RSP_ADD_ALARM"
    "_PLAN_TO_WEB\020\201\240C\022$\n\036REQ_UPDATE_ALARM_PLA"
    "N_FROM_WEB\020\220\240C\022\"\n\034RSP_UPDATE_ALARM_PLAN_"
    "TO_WEB\020\221\240C\022$\n\036REQ_DELETE_ALARM_PLAN_FROM"
    "_WEB\020\240\240C\022\"\n\034RSP_DELETE_ALARM_PLAN_TO_WEB"
    "\020\241\240C\022\024\n\016REQ_ALARM_PLAN\020\260\240C\022\024\n\016RSP_ALARM_"
    "PLAN\020\261\240C\022\017\n\tREQ_ALARM\020\340\240C\022\017\n\tRSP_ALARM\020\341"
    "\240C\022\022\n\014REPORT_ALARM\020\343\240C\022\037\n\031REQ_MEETING_NO"
    "TICE_TO_DMS\020\200\241C\022!\n\033RSP_MEETING_NOTICE_FR"
    "OM_DMS\020\201\241C\022#\n\035REQ_RECEIVE_ATTENDANCE_REC"
    "ORD\020\220\241C\022\"\n\034REQ_SHOW_SIGNIN_DATA_HISTORY\020"
    "\240\241C\022\"\n\034RSP_SHOW_SIGNIN_DATA_HISTORY\020\241\241C\022"
    "#\n\035REQ_ISSUED_PLAN_OF_RAISE_DUST\020\260\241C\022!\n\033"
    "NOTICE_SIGN_IN_OF_REAL_TIME\020\302\241C\022\025\n\017REQ_W"
    "HILTE_LIST\020\320\241C\022\025\n\017RSP_WHILTE_LIST\020\321\241C\022\025\n"
    "\017NOTICE_HOST_MAP\020\322\241C\022\035\n\027REQ_WHITE_LIST_C"
    "APITURE\020\340\241C\022\035\n\027RSP_WHITE_LIST_CAPITURE\020\341"
    "\241C\022\030\n\022REQ_WHITE_LIST_DEV\020\360\241C\022\030\n\022RSP_WHIT"
    "E_LIST_DEV\020\361\241C\022\035\n\027REQ_BPX_DATA_DISTRIBUT"
    "E\020\200\242C\022\035\n\027RSP_BPX_DATA_DISTRIBUTE\020\201\242C\022\035\n\027"
    "REQ_BPX_OPERATOR_DEVICE\020\220\242C\022\035\n\027RSP_BPX_O"
    "PERATOR_DEVICE\020\221\242C\022\031\n\023REQ_BPX_DATA_REPOR"
    "T\020\242\242C\022\026\n\020REQ_GET_BOX_INFO\020\260\242C\022\026\n\020RSP_GET"
    "_BOX_INFO\020\261\242C\022\035\n\027NOTICE_MEETING_TO_BDATA"
    "\020\342\241C\022\032\n\024REQ_GET_CLUSTER_DATA\020\200\244C\022\032\n\024RSP_"
    "GET_CLUSTER_DATA\020\201\244C\022%\n\037REQ_ADD_ALARM_TI"
    "METEMPLATE_DATA\020\220\244C\022%\n\037RSP_ADD_ALARM_TIM"
    "ETEMPLATE_DATA\020\221\244C\022(\n\"REQ_UPDATE_ALARM_T"
    "IMETEMPLATE_DATA\020\240\244C\022(\n\"RSP_UPDATE_ALARM"
    "_TIMETEMPLATE_DATA\020\241\244C\022(\n\"REQ_DELETE_ALA"
    "RM_TIMETEMPLATE_DATA\020\260\244C\022(\n\"RSP_DELETE_A"
    "LARM_TIMETEMPLATE_DATA\020\261\244C\022\035\n\027REQ_ADD_VI"
    "DEO_PLAN_DATA\020\300\244C\022\035\n\027RSP_ADD_VIDEO_PLAN_"
    "DATA\020\301\244C\022 \n\032REQ_UPDATE_VIDEO_PLAN_DATA\020\320"
    "\244C\022 \n\032RSP_UPDATE_VIDEO_PLAN_DATA\020\321\244C\022 \n\032"
    "REQ_DELETE_VIDEO_PLAN_DATA\020\340\244C\022 \n\032RSP_DE"
    "LETE_VIDEO_PLAN_DATA\020\341\244C\022&\n REQ_UPDATE_A"
    "LARM_LINK_LEVEL_DATA\020\360\244C\022&\n RSP_UPDATE_A"
    "LARM_LINK_LEVEL_DATA\020\361\244C\022\024\n\016REQ_VIDEO_PL"
    "AN\020\200\245C\022\024\n\016RSP_VIDEO_PLAN\020\201\245C\022\034\n\026INFO_UPD"
    "ATE_VIDEO_PLAN\020\224\245C\022\034\n\026INFO_DELETE_VIDEO_"
    "PLAN\020\244\245C\022\036\n\030NOTICE_VIDEO_PLAN_UPDATE\020\262\245C"
    "\022\036\n\030NOTICE_VIDEO_PLAN_DELETE\020\302\245C\022\034\n\026INFO"
    "_UPDATE_WHITE_USER\020\324\245C\022\034\n\026INFO_DELETE_WH"
    "ITE_USER\020\344\245C\022\033\n\025INFO_CLEAR_WHITE_USER\020\364\245"
    "C\022\027\n\021REQ_LINKAGE_TOKEN\020\200\246C\022\027\n\021RSP_LINKAG"
    "E_TOKEN\020\201\246C\022\024\n\016REQ_HEART_BEAT\020\200\300C\022\024\n\016RSP"
    "_HEART_BEAT\020\201\300C\022\025\n\017REQ_DEVICE_LIST\020\200\340C\022\025"
    "\n\017RSP_DEVICE_LIST\020\201\340C\022\026\n\020REQ_CHANNEL_INF"
    "O\020\220\340C\022\026\n\020RSP_CHANNEL_INFO\020\221\340C\022\025\n\017REQ_PLA"
    "Y_STREAM\020\240\340C\022\025\n\017RSP_PLAY_STREAM\020\241\340C\022\026\n\020R"
    "EQ_QUERY_RECORD\020\260\340C\022\026\n\020RSP_QUERY_RECORD\020"
    "\261\340C\022\030\n\022REQ_RECEIVE_RECORD\020\300\340C\022\030\n\022RSP_REC"
    "EIVE_RECORD\020\301\340C", 8415);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "DataType.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_DataType_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_DataType_2eproto {
  StaticDescriptorInitializer_DataType_2eproto() {
    protobuf_AddDesc_DataType_2eproto();
  }
} static_descriptor_initializer_DataType_2eproto_;
const ::google::protobuf::EnumDescriptor* DATA_TYPE_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return DATA_TYPE_descriptor_;
}
bool DATA_TYPE_IsValid(int value) {
  switch(value) {
    case 90193:
    case 1048576:
    case 1048577:
    case 1048592:
    case 1048593:
    case 1048608:
    case 1048609:
    case 1048624:
    case 1048625:
    case 1048640:
    case 1048641:
    case 1048656:
    case 1048657:
    case 1048672:
    case 1048673:
    case 1048688:
    case 1048689:
    case 1048704:
    case 1048705:
    case 1048720:
    case 1048721:
    case 1048736:
    case 1048737:
    case 1048768:
    case 1048769:
    case 1048784:
    case 1048785:
    case 1052672:
    case 1052673:
    case 1052688:
    case 1052689:
    case 1052704:
    case 1052705:
    case 1052720:
    case 1052721:
    case 1052736:
    case 1052737:
    case 1052752:
    case 1052753:
    case 1052768:
    case 1052769:
    case 1052784:
    case 1052785:
    case 1052800:
    case 1052801:
    case 1052816:
    case 1052817:
    case 1056768:
    case 1056769:
    case 1060864:
    case 1060865:
    case 1060880:
    case 1060881:
    case 1060896:
    case 1060897:
    case 1060912:
    case 1060913:
    case 1064960:
    case 1064961:
    case 1064976:
    case 1064977:
    case 1069056:
    case 1069057:
    case 1069072:
    case 1069073:
    case 1069088:
    case 1069089:
    case 1069136:
    case 1069137:
    case 1069152:
    case 1069424:
    case 1069425:
    case 1069440:
    case 1069441:
    case 1069456:
    case 1069457:
    case 1069472:
    case 1069473:
    case 1073152:
    case 1073153:
    case 1073168:
    case 1073169:
    case 1073184:
    case 1073185:
    case 1073200:
    case 1073201:
    case 1073216:
    case 1073217:
    case 1073232:
    case 1073248:
    case 1073249:
    case 1073264:
    case 1073265:
    case 1073280:
    case 1073281:
    case 1073296:
    case 1073297:
    case 1073312:
    case 1073313:
    case 1073328:
    case 1073329:
    case 1073347:
    case 1077248:
    case 1077249:
    case 1077264:
    case 1077265:
    case 1077280:
    case 1077281:
    case 1077296:
    case 1077297:
    case 1077312:
    case 1077313:
    case 1077328:
    case 1077329:
    case 1077344:
    case 1077345:
    case 1077360:
    case 1077361:
    case 1077376:
    case 1077377:
    case 1077392:
    case 1077393:
    case 1077408:
    case 1077409:
    case 1077424:
    case 1077425:
    case 1077440:
    case 1077441:
    case 1077456:
    case 1077457:
    case 1077472:
    case 1077473:
    case 1077488:
    case 1077489:
    case 1077491:
    case 1077504:
    case 1077505:
    case 1077520:
    case 1077521:
    case 1077536:
    case 1077537:
    case 1077552:
    case 1077553:
    case 1077568:
    case 1077569:
    case 1077584:
    case 1077585:
    case 1077600:
    case 1077601:
    case 1077616:
    case 1077617:
    case 1077632:
    case 1077633:
    case 1077648:
    case 1077649:
    case 1081344:
    case 1081345:
    case 1081360:
    case 1081361:
    case 1081376:
    case 1081377:
    case 1081392:
    case 1081393:
    case 1081410:
    case 1081424:
    case 1081425:
    case 1081440:
    case 1081441:
    case 1085440:
    case 1085441:
    case 1085456:
    case 1085457:
    case 1085472:
    case 1085473:
    case 1085489:
    case 1085490:
    case 1085491:
    case 1089536:
    case 1089552:
    case 1089568:
    case 1089584:
    case 1089600:
    case 1089616:
    case 1089632:
    case 1089648:
    case 1089664:
    case 1089680:
    case 1089696:
    case 1089712:
    case 1089728:
    case 1089746:
    case 1089747:
    case 1093632:
    case 1093633:
    case 1093648:
    case 1093649:
    case 1097728:
    case 1097729:
    case 1097760:
    case 1097761:
    case 1097779:
    case 1097792:
    case 1097793:
    case 1097808:
    case 1097809:
    case 1097824:
    case 1097825:
    case 1097827:
    case 1097840:
    case 1097841:
    case 1101824:
    case 1101825:
    case 1101840:
    case 1101841:
    case 1101856:
    case 1101857:
    case 1101872:
    case 1101873:
    case 1101920:
    case 1101921:
    case 1101923:
    case 1101952:
    case 1101953:
    case 1101968:
    case 1101984:
    case 1101985:
    case 1102000:
    case 1102018:
    case 1102032:
    case 1102033:
    case 1102034:
    case 1102048:
    case 1102049:
    case 1102050:
    case 1102064:
    case 1102065:
    case 1102080:
    case 1102081:
    case 1102096:
    case 1102097:
    case 1102114:
    case 1102128:
    case 1102129:
    case 1102336:
    case 1102337:
    case 1102352:
    case 1102353:
    case 1102368:
    case 1102369:
    case 1102384:
    case 1102385:
    case 1102400:
    case 1102401:
    case 1102416:
    case 1102417:
    case 1102432:
    case 1102433:
    case 1102448:
    case 1102449:
    case 1102464:
    case 1102465:
    case 1102484:
    case 1102500:
    case 1102514:
    case 1102530:
    case 1102548:
    case 1102564:
    case 1102580:
    case 1102592:
    case 1102593:
    case 1105920:
    case 1105921:
    case 1110016:
    case 1110017:
    case 1110032:
    case 1110033:
    case 1110048:
    case 1110049:
    case 1110064:
    case 1110065:
    case 1110080:
    case 1110081:
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