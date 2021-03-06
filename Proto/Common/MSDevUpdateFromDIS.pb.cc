// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MSDevUpdateFromDIS.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "MSDevUpdateFromDIS.pb.h"

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

const ::google::protobuf::Descriptor* MSDevUpdateFromDIS_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MSDevUpdateFromDIS_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_MSDevUpdateFromDIS_2eproto() {
  protobuf_AddDesc_MSDevUpdateFromDIS_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "MSDevUpdateFromDIS.proto");
  GOOGLE_CHECK(file != NULL);
  MSDevUpdateFromDIS_descriptor_ = file->message_type(0);
  static const int MSDevUpdateFromDIS_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, deviceid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, operation_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, respurl_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, order_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, mstype_),
  };
  MSDevUpdateFromDIS_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      MSDevUpdateFromDIS_descriptor_,
      MSDevUpdateFromDIS::default_instance_,
      MSDevUpdateFromDIS_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MSDevUpdateFromDIS, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(MSDevUpdateFromDIS));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_MSDevUpdateFromDIS_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    MSDevUpdateFromDIS_descriptor_, &MSDevUpdateFromDIS::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_MSDevUpdateFromDIS_2eproto() {
  delete MSDevUpdateFromDIS::default_instance_;
  delete MSDevUpdateFromDIS_reflection_;
}

void protobuf_AddDesc_MSDevUpdateFromDIS_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030MSDevUpdateFromDIS.proto\022\024com.arges.fi"
    "le.proto\"w\n\022MSDevUpdateFromDIS\022\020\n\010device"
    "Id\030\001 \003(\t\022\025\n\toperation\030\002 \002(\005:\002-1\022\021\n\007respu"
    "rl\030\003 \002(\t:\000\022\021\n\005order\030\004 \001(\005:\002-1\022\022\n\006mstype\030"
    "\005 \002(\005:\002-1", 169);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "MSDevUpdateFromDIS.proto", &protobuf_RegisterTypes);
  MSDevUpdateFromDIS::default_instance_ = new MSDevUpdateFromDIS();
  MSDevUpdateFromDIS::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_MSDevUpdateFromDIS_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_MSDevUpdateFromDIS_2eproto {
  StaticDescriptorInitializer_MSDevUpdateFromDIS_2eproto() {
    protobuf_AddDesc_MSDevUpdateFromDIS_2eproto();
  }
} static_descriptor_initializer_MSDevUpdateFromDIS_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int MSDevUpdateFromDIS::kDeviceIdFieldNumber;
const int MSDevUpdateFromDIS::kOperationFieldNumber;
const int MSDevUpdateFromDIS::kRespurlFieldNumber;
const int MSDevUpdateFromDIS::kOrderFieldNumber;
const int MSDevUpdateFromDIS::kMstypeFieldNumber;
#endif  // !_MSC_VER

MSDevUpdateFromDIS::MSDevUpdateFromDIS()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:com.arges.file.proto.MSDevUpdateFromDIS)
}

void MSDevUpdateFromDIS::InitAsDefaultInstance() {
}

MSDevUpdateFromDIS::MSDevUpdateFromDIS(const MSDevUpdateFromDIS& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:com.arges.file.proto.MSDevUpdateFromDIS)
}

void MSDevUpdateFromDIS::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  operation_ = -1;
  respurl_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  order_ = -1;
  mstype_ = -1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

MSDevUpdateFromDIS::~MSDevUpdateFromDIS() {
  // @@protoc_insertion_point(destructor:com.arges.file.proto.MSDevUpdateFromDIS)
  SharedDtor();
}

void MSDevUpdateFromDIS::SharedDtor() {
  if (respurl_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete respurl_;
  }
  if (this != default_instance_) {
  }
}

void MSDevUpdateFromDIS::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MSDevUpdateFromDIS::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MSDevUpdateFromDIS_descriptor_;
}

const MSDevUpdateFromDIS& MSDevUpdateFromDIS::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_MSDevUpdateFromDIS_2eproto();
  return *default_instance_;
}

MSDevUpdateFromDIS* MSDevUpdateFromDIS::default_instance_ = NULL;

MSDevUpdateFromDIS* MSDevUpdateFromDIS::New() const {
  return new MSDevUpdateFromDIS;
}

void MSDevUpdateFromDIS::Clear() {
  if (_has_bits_[0 / 32] & 30) {
    operation_ = -1;
    if (has_respurl()) {
      if (respurl_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        respurl_->clear();
      }
    }
    order_ = -1;
    mstype_ = -1;
  }
  deviceid_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool MSDevUpdateFromDIS::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:com.arges.file.proto.MSDevUpdateFromDIS)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated string deviceId = 1;
      case 1: {
        if (tag == 10) {
         parse_deviceId:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_deviceid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->deviceid(this->deviceid_size() - 1).data(),
            this->deviceid(this->deviceid_size() - 1).length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "deviceid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_deviceId;
        if (input->ExpectTag(16)) goto parse_operation;
        break;
      }

      // required int32 operation = 2 [default = -1];
      case 2: {
        if (tag == 16) {
         parse_operation:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &operation_)));
          set_has_operation();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_respurl;
        break;
      }

      // required string respurl = 3 [default = ""];
      case 3: {
        if (tag == 26) {
         parse_respurl:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_respurl()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->respurl().data(), this->respurl().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "respurl");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_order;
        break;
      }

      // optional int32 order = 4 [default = -1];
      case 4: {
        if (tag == 32) {
         parse_order:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &order_)));
          set_has_order();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_mstype;
        break;
      }

      // required int32 mstype = 5 [default = -1];
      case 5: {
        if (tag == 40) {
         parse_mstype:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &mstype_)));
          set_has_mstype();
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
  // @@protoc_insertion_point(parse_success:com.arges.file.proto.MSDevUpdateFromDIS)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:com.arges.file.proto.MSDevUpdateFromDIS)
  return false;
#undef DO_
}

void MSDevUpdateFromDIS::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:com.arges.file.proto.MSDevUpdateFromDIS)
  // repeated string deviceId = 1;
  for (int i = 0; i < this->deviceid_size(); i++) {
  ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
    this->deviceid(i).data(), this->deviceid(i).length(),
    ::google::protobuf::internal::WireFormat::SERIALIZE,
    "deviceid");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->deviceid(i), output);
  }

  // required int32 operation = 2 [default = -1];
  if (has_operation()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->operation(), output);
  }

  // required string respurl = 3 [default = ""];
  if (has_respurl()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->respurl().data(), this->respurl().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "respurl");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->respurl(), output);
  }

  // optional int32 order = 4 [default = -1];
  if (has_order()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(4, this->order(), output);
  }

  // required int32 mstype = 5 [default = -1];
  if (has_mstype()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(5, this->mstype(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:com.arges.file.proto.MSDevUpdateFromDIS)
}

::google::protobuf::uint8* MSDevUpdateFromDIS::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:com.arges.file.proto.MSDevUpdateFromDIS)
  // repeated string deviceId = 1;
  for (int i = 0; i < this->deviceid_size(); i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->deviceid(i).data(), this->deviceid(i).length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "deviceid");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(1, this->deviceid(i), target);
  }

  // required int32 operation = 2 [default = -1];
  if (has_operation()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->operation(), target);
  }

  // required string respurl = 3 [default = ""];
  if (has_respurl()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->respurl().data(), this->respurl().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "respurl");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->respurl(), target);
  }

  // optional int32 order = 4 [default = -1];
  if (has_order()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(4, this->order(), target);
  }

  // required int32 mstype = 5 [default = -1];
  if (has_mstype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(5, this->mstype(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:com.arges.file.proto.MSDevUpdateFromDIS)
  return target;
}

int MSDevUpdateFromDIS::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    // required int32 operation = 2 [default = -1];
    if (has_operation()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->operation());
    }

    // required string respurl = 3 [default = ""];
    if (has_respurl()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->respurl());
    }

    // optional int32 order = 4 [default = -1];
    if (has_order()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->order());
    }

    // required int32 mstype = 5 [default = -1];
    if (has_mstype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->mstype());
    }

  }
  // repeated string deviceId = 1;
  total_size += 1 * this->deviceid_size();
  for (int i = 0; i < this->deviceid_size(); i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->deviceid(i));
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

void MSDevUpdateFromDIS::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const MSDevUpdateFromDIS* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const MSDevUpdateFromDIS*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MSDevUpdateFromDIS::MergeFrom(const MSDevUpdateFromDIS& from) {
  GOOGLE_CHECK_NE(&from, this);
  deviceid_.MergeFrom(from.deviceid_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_operation()) {
      set_operation(from.operation());
    }
    if (from.has_respurl()) {
      set_respurl(from.respurl());
    }
    if (from.has_order()) {
      set_order(from.order());
    }
    if (from.has_mstype()) {
      set_mstype(from.mstype());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void MSDevUpdateFromDIS::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MSDevUpdateFromDIS::CopyFrom(const MSDevUpdateFromDIS& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MSDevUpdateFromDIS::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000016) != 0x00000016) return false;

  return true;
}

void MSDevUpdateFromDIS::Swap(MSDevUpdateFromDIS* other) {
  if (other != this) {
    deviceid_.Swap(&other->deviceid_);
    std::swap(operation_, other->operation_);
    std::swap(respurl_, other->respurl_);
    std::swap(order_, other->order_);
    std::swap(mstype_, other->mstype_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata MSDevUpdateFromDIS::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MSDevUpdateFromDIS_descriptor_;
  metadata.reflection = MSDevUpdateFromDIS_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace file
}  // namespace arges
}  // namespace com

// @@protoc_insertion_point(global_scope)
