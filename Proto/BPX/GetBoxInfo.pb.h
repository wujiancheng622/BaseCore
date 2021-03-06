// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GetBoxInfo.proto

#ifndef PROTOBUF_GetBoxInfo_2eproto__INCLUDED
#define PROTOBUF_GetBoxInfo_2eproto__INCLUDED

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
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace com {
namespace arges {
namespace file {
namespace proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GetBoxInfo_2eproto();
void protobuf_AssignDesc_GetBoxInfo_2eproto();
void protobuf_ShutdownFile_GetBoxInfo_2eproto();

class ReqGetBoxInfo;
class RspGetBoxInfo;

// ===================================================================

class ReqGetBoxInfo : public ::google::protobuf::Message {
 public:
  ReqGetBoxInfo();
  virtual ~ReqGetBoxInfo();

  ReqGetBoxInfo(const ReqGetBoxInfo& from);

  inline ReqGetBoxInfo& operator=(const ReqGetBoxInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ReqGetBoxInfo& default_instance();

  void Swap(ReqGetBoxInfo* other);

  // implements Message ----------------------------------------------

  ReqGetBoxInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ReqGetBoxInfo& from);
  void MergeFrom(const ReqGetBoxInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string describe = 1 [default = ""];
  inline bool has_describe() const;
  inline void clear_describe();
  static const int kDescribeFieldNumber = 1;
  inline const ::std::string& describe() const;
  inline void set_describe(const ::std::string& value);
  inline void set_describe(const char* value);
  inline void set_describe(const char* value, size_t size);
  inline ::std::string* mutable_describe();
  inline ::std::string* release_describe();
  inline void set_allocated_describe(::std::string* describe);

  // optional int32 requesTtype = 2 [default = -1];
  inline bool has_requesttype() const;
  inline void clear_requesttype();
  static const int kRequesTtypeFieldNumber = 2;
  inline ::google::protobuf::int32 requesttype() const;
  inline void set_requesttype(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:com.arges.file.proto.ReqGetBoxInfo)
 private:
  inline void set_has_describe();
  inline void clear_has_describe();
  inline void set_has_requesttype();
  inline void clear_has_requesttype();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* describe_;
  ::google::protobuf::int32 requesttype_;
  friend void  protobuf_AddDesc_GetBoxInfo_2eproto();
  friend void protobuf_AssignDesc_GetBoxInfo_2eproto();
  friend void protobuf_ShutdownFile_GetBoxInfo_2eproto();

  void InitAsDefaultInstance();
  static ReqGetBoxInfo* default_instance_;
};
// -------------------------------------------------------------------

class RspGetBoxInfo : public ::google::protobuf::Message {
 public:
  RspGetBoxInfo();
  virtual ~RspGetBoxInfo();

  RspGetBoxInfo(const RspGetBoxInfo& from);

  inline RspGetBoxInfo& operator=(const RspGetBoxInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const RspGetBoxInfo& default_instance();

  void Swap(RspGetBoxInfo* other);

  // implements Message ----------------------------------------------

  RspGetBoxInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const RspGetBoxInfo& from);
  void MergeFrom(const RspGetBoxInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string boxid = 1 [default = ""];
  inline bool has_boxid() const;
  inline void clear_boxid();
  static const int kBoxidFieldNumber = 1;
  inline const ::std::string& boxid() const;
  inline void set_boxid(const ::std::string& value);
  inline void set_boxid(const char* value);
  inline void set_boxid(const char* value, size_t size);
  inline ::std::string* mutable_boxid();
  inline ::std::string* release_boxid();
  inline void set_allocated_boxid(::std::string* boxid);

  // optional string resultDescirbe = 2 [default = ""];
  inline bool has_resultdescirbe() const;
  inline void clear_resultdescirbe();
  static const int kResultDescirbeFieldNumber = 2;
  inline const ::std::string& resultdescirbe() const;
  inline void set_resultdescirbe(const ::std::string& value);
  inline void set_resultdescirbe(const char* value);
  inline void set_resultdescirbe(const char* value, size_t size);
  inline ::std::string* mutable_resultdescirbe();
  inline ::std::string* release_resultdescirbe();
  inline void set_allocated_resultdescirbe(::std::string* resultdescirbe);

  // @@protoc_insertion_point(class_scope:com.arges.file.proto.RspGetBoxInfo)
 private:
  inline void set_has_boxid();
  inline void clear_has_boxid();
  inline void set_has_resultdescirbe();
  inline void clear_has_resultdescirbe();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* boxid_;
  ::std::string* resultdescirbe_;
  friend void  protobuf_AddDesc_GetBoxInfo_2eproto();
  friend void protobuf_AssignDesc_GetBoxInfo_2eproto();
  friend void protobuf_ShutdownFile_GetBoxInfo_2eproto();

  void InitAsDefaultInstance();
  static RspGetBoxInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// ReqGetBoxInfo

// optional string describe = 1 [default = ""];
inline bool ReqGetBoxInfo::has_describe() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ReqGetBoxInfo::set_has_describe() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ReqGetBoxInfo::clear_has_describe() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ReqGetBoxInfo::clear_describe() {
  if (describe_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    describe_->clear();
  }
  clear_has_describe();
}
inline const ::std::string& ReqGetBoxInfo::describe() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ReqGetBoxInfo.describe)
  return *describe_;
}
inline void ReqGetBoxInfo::set_describe(const ::std::string& value) {
  set_has_describe();
  if (describe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    describe_ = new ::std::string;
  }
  describe_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ReqGetBoxInfo.describe)
}
inline void ReqGetBoxInfo::set_describe(const char* value) {
  set_has_describe();
  if (describe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    describe_ = new ::std::string;
  }
  describe_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ReqGetBoxInfo.describe)
}
inline void ReqGetBoxInfo::set_describe(const char* value, size_t size) {
  set_has_describe();
  if (describe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    describe_ = new ::std::string;
  }
  describe_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ReqGetBoxInfo.describe)
}
inline ::std::string* ReqGetBoxInfo::mutable_describe() {
  set_has_describe();
  if (describe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    describe_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ReqGetBoxInfo.describe)
  return describe_;
}
inline ::std::string* ReqGetBoxInfo::release_describe() {
  clear_has_describe();
  if (describe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = describe_;
    describe_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ReqGetBoxInfo::set_allocated_describe(::std::string* describe) {
  if (describe_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete describe_;
  }
  if (describe) {
    set_has_describe();
    describe_ = describe;
  } else {
    clear_has_describe();
    describe_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ReqGetBoxInfo.describe)
}

// optional int32 requesTtype = 2 [default = -1];
inline bool ReqGetBoxInfo::has_requesttype() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ReqGetBoxInfo::set_has_requesttype() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ReqGetBoxInfo::clear_has_requesttype() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ReqGetBoxInfo::clear_requesttype() {
  requesttype_ = -1;
  clear_has_requesttype();
}
inline ::google::protobuf::int32 ReqGetBoxInfo::requesttype() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ReqGetBoxInfo.requesTtype)
  return requesttype_;
}
inline void ReqGetBoxInfo::set_requesttype(::google::protobuf::int32 value) {
  set_has_requesttype();
  requesttype_ = value;
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ReqGetBoxInfo.requesTtype)
}

// -------------------------------------------------------------------

// RspGetBoxInfo

// optional string boxid = 1 [default = ""];
inline bool RspGetBoxInfo::has_boxid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void RspGetBoxInfo::set_has_boxid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void RspGetBoxInfo::clear_has_boxid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void RspGetBoxInfo::clear_boxid() {
  if (boxid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    boxid_->clear();
  }
  clear_has_boxid();
}
inline const ::std::string& RspGetBoxInfo::boxid() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.RspGetBoxInfo.boxid)
  return *boxid_;
}
inline void RspGetBoxInfo::set_boxid(const ::std::string& value) {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    boxid_ = new ::std::string;
  }
  boxid_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.RspGetBoxInfo.boxid)
}
inline void RspGetBoxInfo::set_boxid(const char* value) {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    boxid_ = new ::std::string;
  }
  boxid_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.RspGetBoxInfo.boxid)
}
inline void RspGetBoxInfo::set_boxid(const char* value, size_t size) {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    boxid_ = new ::std::string;
  }
  boxid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.RspGetBoxInfo.boxid)
}
inline ::std::string* RspGetBoxInfo::mutable_boxid() {
  set_has_boxid();
  if (boxid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    boxid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.RspGetBoxInfo.boxid)
  return boxid_;
}
inline ::std::string* RspGetBoxInfo::release_boxid() {
  clear_has_boxid();
  if (boxid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = boxid_;
    boxid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void RspGetBoxInfo::set_allocated_boxid(::std::string* boxid) {
  if (boxid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete boxid_;
  }
  if (boxid) {
    set_has_boxid();
    boxid_ = boxid;
  } else {
    clear_has_boxid();
    boxid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.RspGetBoxInfo.boxid)
}

// optional string resultDescirbe = 2 [default = ""];
inline bool RspGetBoxInfo::has_resultdescirbe() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void RspGetBoxInfo::set_has_resultdescirbe() {
  _has_bits_[0] |= 0x00000002u;
}
inline void RspGetBoxInfo::clear_has_resultdescirbe() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void RspGetBoxInfo::clear_resultdescirbe() {
  if (resultdescirbe_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    resultdescirbe_->clear();
  }
  clear_has_resultdescirbe();
}
inline const ::std::string& RspGetBoxInfo::resultdescirbe() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.RspGetBoxInfo.resultDescirbe)
  return *resultdescirbe_;
}
inline void RspGetBoxInfo::set_resultdescirbe(const ::std::string& value) {
  set_has_resultdescirbe();
  if (resultdescirbe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    resultdescirbe_ = new ::std::string;
  }
  resultdescirbe_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.RspGetBoxInfo.resultDescirbe)
}
inline void RspGetBoxInfo::set_resultdescirbe(const char* value) {
  set_has_resultdescirbe();
  if (resultdescirbe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    resultdescirbe_ = new ::std::string;
  }
  resultdescirbe_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.RspGetBoxInfo.resultDescirbe)
}
inline void RspGetBoxInfo::set_resultdescirbe(const char* value, size_t size) {
  set_has_resultdescirbe();
  if (resultdescirbe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    resultdescirbe_ = new ::std::string;
  }
  resultdescirbe_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.RspGetBoxInfo.resultDescirbe)
}
inline ::std::string* RspGetBoxInfo::mutable_resultdescirbe() {
  set_has_resultdescirbe();
  if (resultdescirbe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    resultdescirbe_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.RspGetBoxInfo.resultDescirbe)
  return resultdescirbe_;
}
inline ::std::string* RspGetBoxInfo::release_resultdescirbe() {
  clear_has_resultdescirbe();
  if (resultdescirbe_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = resultdescirbe_;
    resultdescirbe_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void RspGetBoxInfo::set_allocated_resultdescirbe(::std::string* resultdescirbe) {
  if (resultdescirbe_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete resultdescirbe_;
  }
  if (resultdescirbe) {
    set_has_resultdescirbe();
    resultdescirbe_ = resultdescirbe;
  } else {
    clear_has_resultdescirbe();
    resultdescirbe_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.RspGetBoxInfo.resultDescirbe)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace file
}  // namespace arges
}  // namespace com

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GetBoxInfo_2eproto__INCLUDED
