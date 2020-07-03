// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GetLeaderAddressBean.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "GetLeaderAddressBean.pb.h"

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

const ::google::protobuf::Descriptor* ReqGetLeaderAddress_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  ReqGetLeaderAddress_reflection_ = NULL;
const ::google::protobuf::Descriptor* RspGetLeaderAddress_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  RspGetLeaderAddress_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_GetLeaderAddressBean_2eproto() {
  protobuf_AddDesc_GetLeaderAddressBean_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "GetLeaderAddressBean.proto");
  GOOGLE_CHECK(file != NULL);
  ReqGetLeaderAddress_descriptor_ = file->message_type(0);
  static const int ReqGetLeaderAddress_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGetLeaderAddress, identifier_),
  };
  ReqGetLeaderAddress_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      ReqGetLeaderAddress_descriptor_,
      ReqGetLeaderAddress::default_instance_,
      ReqGetLeaderAddress_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGetLeaderAddress, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(ReqGetLeaderAddress, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(ReqGetLeaderAddress));
  RspGetLeaderAddress_descriptor_ = file->message_type(1);
  static const int RspGetLeaderAddress_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RspGetLeaderAddress, leaderip_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RspGetLeaderAddress, leaderport_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RspGetLeaderAddress, bpxid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RspGetLeaderAddress, leaderid_),
  };
  RspGetLeaderAddress_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      RspGetLeaderAddress_descriptor_,
      RspGetLeaderAddress::default_instance_,
      RspGetLeaderAddress_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RspGetLeaderAddress, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(RspGetLeaderAddress, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(RspGetLeaderAddress));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_GetLeaderAddressBean_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    ReqGetLeaderAddress_descriptor_, &ReqGetLeaderAddress::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    RspGetLeaderAddress_descriptor_, &RspGetLeaderAddress::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_GetLeaderAddressBean_2eproto() {
  delete ReqGetLeaderAddress::default_instance_;
  delete ReqGetLeaderAddress_reflection_;
  delete RspGetLeaderAddress::default_instance_;
  delete RspGetLeaderAddress_reflection_;
}

void protobuf_AddDesc_GetLeaderAddressBean_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\032GetLeaderAddressBean.proto\022\024com.arges."
    "file.proto\"+\n\023ReqGetLeaderAddress\022\024\n\nide"
    "ntifier\030\001 \001(\t:\000\"f\n\023RspGetLeaderAddress\022\022"
    "\n\010leaderip\030\001 \002(\t:\000\022\026\n\nleaderport\030\002 \002(\005:\002"
    "-1\022\017\n\005bpxid\030\003 \001(\t:\000\022\022\n\010leaderid\030\004 \001(\t:\000", 199);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "GetLeaderAddressBean.proto", &protobuf_RegisterTypes);
  ReqGetLeaderAddress::default_instance_ = new ReqGetLeaderAddress();
  RspGetLeaderAddress::default_instance_ = new RspGetLeaderAddress();
  ReqGetLeaderAddress::default_instance_->InitAsDefaultInstance();
  RspGetLeaderAddress::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_GetLeaderAddressBean_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_GetLeaderAddressBean_2eproto {
  StaticDescriptorInitializer_GetLeaderAddressBean_2eproto() {
    protobuf_AddDesc_GetLeaderAddressBean_2eproto();
  }
} static_descriptor_initializer_GetLeaderAddressBean_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int ReqGetLeaderAddress::kIdentifierFieldNumber;
#endif  // !_MSC_VER

ReqGetLeaderAddress::ReqGetLeaderAddress()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:com.arges.file.proto.ReqGetLeaderAddress)
}

void ReqGetLeaderAddress::InitAsDefaultInstance() {
}

ReqGetLeaderAddress::ReqGetLeaderAddress(const ReqGetLeaderAddress& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:com.arges.file.proto.ReqGetLeaderAddress)
}

void ReqGetLeaderAddress::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  identifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

ReqGetLeaderAddress::~ReqGetLeaderAddress() {
  // @@protoc_insertion_point(destructor:com.arges.file.proto.ReqGetLeaderAddress)
  SharedDtor();
}

void ReqGetLeaderAddress::SharedDtor() {
  if (identifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete identifier_;
  }
  if (this != default_instance_) {
  }
}

void ReqGetLeaderAddress::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* ReqGetLeaderAddress::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ReqGetLeaderAddress_descriptor_;
}

const ReqGetLeaderAddress& ReqGetLeaderAddress::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GetLeaderAddressBean_2eproto();
  return *default_instance_;
}

ReqGetLeaderAddress* ReqGetLeaderAddress::default_instance_ = NULL;

ReqGetLeaderAddress* ReqGetLeaderAddress::New() const {
  return new ReqGetLeaderAddress;
}

void ReqGetLeaderAddress::Clear() {
  if (has_identifier()) {
    if (identifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      identifier_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool ReqGetLeaderAddress::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:com.arges.file.proto.ReqGetLeaderAddress)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string identifier = 1 [default = ""];
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_identifier()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->identifier().data(), this->identifier().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "identifier");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:com.arges.file.proto.ReqGetLeaderAddress)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:com.arges.file.proto.ReqGetLeaderAddress)
  return false;
#undef DO_
}

void ReqGetLeaderAddress::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:com.arges.file.proto.ReqGetLeaderAddress)
  // optional string identifier = 1 [default = ""];
  if (has_identifier()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->identifier().data(), this->identifier().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "identifier");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->identifier(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:com.arges.file.proto.ReqGetLeaderAddress)
}

::google::protobuf::uint8* ReqGetLeaderAddress::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.arges.file.proto.ReqGetLeaderAddress)
  // optional string identifier = 1 [default = ""];
  if (has_identifier()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->identifier().data(), this->identifier().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "identifier");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->identifier(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.arges.file.proto.ReqGetLeaderAddress)
  return target;
}

int ReqGetLeaderAddress::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string identifier = 1 [default = ""];
    if (has_identifier()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->identifier());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void ReqGetLeaderAddress::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const ReqGetLeaderAddress* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const ReqGetLeaderAddress*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void ReqGetLeaderAddress::MergeFrom(const ReqGetLeaderAddress& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_identifier()) {
      set_identifier(from.identifier());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void ReqGetLeaderAddress::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ReqGetLeaderAddress::CopyFrom(const ReqGetLeaderAddress& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ReqGetLeaderAddress::IsInitialized() const {

  return true;
}

void ReqGetLeaderAddress::Swap(ReqGetLeaderAddress* other) {
  if (other != this) {
    std::swap(identifier_, other->identifier_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata ReqGetLeaderAddress::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = ReqGetLeaderAddress_descriptor_;
  metadata.reflection = ReqGetLeaderAddress_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int RspGetLeaderAddress::kLeaderipFieldNumber;
const int RspGetLeaderAddress::kLeaderportFieldNumber;
const int RspGetLeaderAddress::kBpxidFieldNumber;
const int RspGetLeaderAddress::kLeaderidFieldNumber;
#endif  // !_MSC_VER

RspGetLeaderAddress::RspGetLeaderAddress()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:com.arges.file.proto.RspGetLeaderAddress)
}

void RspGetLeaderAddress::InitAsDefaultInstance() {
}

RspGetLeaderAddress::RspGetLeaderAddress(const RspGetLeaderAddress& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:com.arges.file.proto.RspGetLeaderAddress)
}

void RspGetLeaderAddress::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  leaderip_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  leaderport_ = -1;
  bpxid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  leaderid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

RspGetLeaderAddress::~RspGetLeaderAddress() {
  // @@protoc_insertion_point(destructor:com.arges.file.proto.RspGetLeaderAddress)
  SharedDtor();
}

void RspGetLeaderAddress::SharedDtor() {
  if (leaderip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete leaderip_;
  }
  if (bpxid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete bpxid_;
  }
  if (leaderid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete leaderid_;
  }
  if (this != default_instance_) {
  }
}

void RspGetLeaderAddress::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* RspGetLeaderAddress::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RspGetLeaderAddress_descriptor_;
}

const RspGetLeaderAddress& RspGetLeaderAddress::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_GetLeaderAddressBean_2eproto();
  return *default_instance_;
}

RspGetLeaderAddress* RspGetLeaderAddress::default_instance_ = NULL;

RspGetLeaderAddress* RspGetLeaderAddress::New() const {
  return new RspGetLeaderAddress;
}

void RspGetLeaderAddress::Clear() {
  if (_has_bits_[0 / 32] & 15) {
    if (has_leaderip()) {
      if (leaderip_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        leaderip_->clear();
      }
    }
    leaderport_ = -1;
    if (has_bpxid()) {
      if (bpxid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        bpxid_->clear();
      }
    }
    if (has_leaderid()) {
      if (leaderid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        leaderid_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool RspGetLeaderAddress::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:com.arges.file.proto.RspGetLeaderAddress)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string leaderip = 1 [default = ""];
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_leaderip()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->leaderip().data(), this->leaderip().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "leaderip");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_leaderport;
        break;
      }

      // required int32 leaderport = 2 [default = -1];
      case 2: {
        if (tag == 16) {
         parse_leaderport:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &leaderport_)));
          set_has_leaderport();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_bpxid;
        break;
      }

      // optional string bpxid = 3 [default = ""];
      case 3: {
        if (tag == 26) {
         parse_bpxid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_bpxid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->bpxid().data(), this->bpxid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "bpxid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_leaderid;
        break;
      }

      // optional string leaderid = 4 [default = ""];
      case 4: {
        if (tag == 34) {
         parse_leaderid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_leaderid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->leaderid().data(), this->leaderid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "leaderid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:com.arges.file.proto.RspGetLeaderAddress)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:com.arges.file.proto.RspGetLeaderAddress)
  return false;
#undef DO_
}

void RspGetLeaderAddress::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:com.arges.file.proto.RspGetLeaderAddress)
  // required string leaderip = 1 [default = ""];
  if (has_leaderip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->leaderip().data(), this->leaderip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "leaderip");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->leaderip(), output);
  }

  // required int32 leaderport = 2 [default = -1];
  if (has_leaderport()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->leaderport(), output);
  }

  // optional string bpxid = 3 [default = ""];
  if (has_bpxid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->bpxid().data(), this->bpxid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "bpxid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->bpxid(), output);
  }

  // optional string leaderid = 4 [default = ""];
  if (has_leaderid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->leaderid().data(), this->leaderid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "leaderid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->leaderid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:com.arges.file.proto.RspGetLeaderAddress)
}

::google::protobuf::uint8* RspGetLeaderAddress::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.arges.file.proto.RspGetLeaderAddress)
  // required string leaderip = 1 [default = ""];
  if (has_leaderip()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->leaderip().data(), this->leaderip().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "leaderip");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->leaderip(), target);
  }

  // required int32 leaderport = 2 [default = -1];
  if (has_leaderport()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->leaderport(), target);
  }

  // optional string bpxid = 3 [default = ""];
  if (has_bpxid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->bpxid().data(), this->bpxid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "bpxid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->bpxid(), target);
  }

  // optional string leaderid = 4 [default = ""];
  if (has_leaderid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->leaderid().data(), this->leaderid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "leaderid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->leaderid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.arges.file.proto.RspGetLeaderAddress)
  return target;
}

int RspGetLeaderAddress::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string leaderip = 1 [default = ""];
    if (has_leaderip()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->leaderip());
    }

    // required int32 leaderport = 2 [default = -1];
    if (has_leaderport()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->leaderport());
    }

    // optional string bpxid = 3 [default = ""];
    if (has_bpxid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->bpxid());
    }

    // optional string leaderid = 4 [default = ""];
    if (has_leaderid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->leaderid());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void RspGetLeaderAddress::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const RspGetLeaderAddress* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const RspGetLeaderAddress*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void RspGetLeaderAddress::MergeFrom(const RspGetLeaderAddress& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_leaderip()) {
      set_leaderip(from.leaderip());
    }
    if (from.has_leaderport()) {
      set_leaderport(from.leaderport());
    }
    if (from.has_bpxid()) {
      set_bpxid(from.bpxid());
    }
    if (from.has_leaderid()) {
      set_leaderid(from.leaderid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void RspGetLeaderAddress::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RspGetLeaderAddress::CopyFrom(const RspGetLeaderAddress& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RspGetLeaderAddress::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void RspGetLeaderAddress::Swap(RspGetLeaderAddress* other) {
  if (other != this) {
    std::swap(leaderip_, other->leaderip_);
    std::swap(leaderport_, other->leaderport_);
    std::swap(bpxid_, other->bpxid_);
    std::swap(leaderid_, other->leaderid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata RspGetLeaderAddress::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = RspGetLeaderAddress_descriptor_;
  metadata.reflection = RspGetLeaderAddress_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace file
}  // namespace arges
}  // namespace com

// @@protoc_insertion_point(global_scope)