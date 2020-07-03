// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ResponseRpcBean.proto

#ifndef PROTOBUF_ResponseRpcBean_2eproto__INCLUDED
#define PROTOBUF_ResponseRpcBean_2eproto__INCLUDED

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
void  protobuf_AddDesc_ResponseRpcBean_2eproto();
void protobuf_AssignDesc_ResponseRpcBean_2eproto();
void protobuf_ShutdownFile_ResponseRpcBean_2eproto();

class ResponseVoteRpc;

// ===================================================================

class ResponseVoteRpc : public ::google::protobuf::Message {
 public:
  ResponseVoteRpc();
  virtual ~ResponseVoteRpc();

  ResponseVoteRpc(const ResponseVoteRpc& from);

  inline ResponseVoteRpc& operator=(const ResponseVoteRpc& from) {
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
  static const ResponseVoteRpc& default_instance();

  void Swap(ResponseVoteRpc* other);

  // implements Message ----------------------------------------------

  ResponseVoteRpc* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ResponseVoteRpc& from);
  void MergeFrom(const ResponseVoteRpc& from);
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

  // optional string term = 1 [default = ""];
  inline bool has_term() const;
  inline void clear_term();
  static const int kTermFieldNumber = 1;
  inline const ::std::string& term() const;
  inline void set_term(const ::std::string& value);
  inline void set_term(const char* value);
  inline void set_term(const char* value, size_t size);
  inline ::std::string* mutable_term();
  inline ::std::string* release_term();
  inline void set_allocated_term(::std::string* term);

  // optional string srcIdentifier = 2 [default = ""];
  inline bool has_srcidentifier() const;
  inline void clear_srcidentifier();
  static const int kSrcIdentifierFieldNumber = 2;
  inline const ::std::string& srcidentifier() const;
  inline void set_srcidentifier(const ::std::string& value);
  inline void set_srcidentifier(const char* value);
  inline void set_srcidentifier(const char* value, size_t size);
  inline ::std::string* mutable_srcidentifier();
  inline ::std::string* release_srcidentifier();
  inline void set_allocated_srcidentifier(::std::string* srcidentifier);

  // optional string desIdentifier = 3 [default = ""];
  inline bool has_desidentifier() const;
  inline void clear_desidentifier();
  static const int kDesIdentifierFieldNumber = 3;
  inline const ::std::string& desidentifier() const;
  inline void set_desidentifier(const ::std::string& value);
  inline void set_desidentifier(const char* value);
  inline void set_desidentifier(const char* value, size_t size);
  inline ::std::string* mutable_desidentifier();
  inline ::std::string* release_desidentifier();
  inline void set_allocated_desidentifier(::std::string* desidentifier);

  // @@protoc_insertion_point(class_scope:com.arges.file.proto.ResponseVoteRpc)
 private:
  inline void set_has_term();
  inline void clear_has_term();
  inline void set_has_srcidentifier();
  inline void clear_has_srcidentifier();
  inline void set_has_desidentifier();
  inline void clear_has_desidentifier();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* term_;
  ::std::string* srcidentifier_;
  ::std::string* desidentifier_;
  friend void  protobuf_AddDesc_ResponseRpcBean_2eproto();
  friend void protobuf_AssignDesc_ResponseRpcBean_2eproto();
  friend void protobuf_ShutdownFile_ResponseRpcBean_2eproto();

  void InitAsDefaultInstance();
  static ResponseVoteRpc* default_instance_;
};
// ===================================================================


// ===================================================================

// ResponseVoteRpc

// optional string term = 1 [default = ""];
inline bool ResponseVoteRpc::has_term() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ResponseVoteRpc::set_has_term() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ResponseVoteRpc::clear_has_term() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ResponseVoteRpc::clear_term() {
  if (term_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_->clear();
  }
  clear_has_term();
}
inline const ::std::string& ResponseVoteRpc::term() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ResponseVoteRpc.term)
  return *term_;
}
inline void ResponseVoteRpc::set_term(const ::std::string& value) {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  term_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ResponseVoteRpc.term)
}
inline void ResponseVoteRpc::set_term(const char* value) {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  term_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ResponseVoteRpc.term)
}
inline void ResponseVoteRpc::set_term(const char* value, size_t size) {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  term_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ResponseVoteRpc.term)
}
inline ::std::string* ResponseVoteRpc::mutable_term() {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ResponseVoteRpc.term)
  return term_;
}
inline ::std::string* ResponseVoteRpc::release_term() {
  clear_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = term_;
    term_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResponseVoteRpc::set_allocated_term(::std::string* term) {
  if (term_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete term_;
  }
  if (term) {
    set_has_term();
    term_ = term;
  } else {
    clear_has_term();
    term_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ResponseVoteRpc.term)
}

// optional string srcIdentifier = 2 [default = ""];
inline bool ResponseVoteRpc::has_srcidentifier() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ResponseVoteRpc::set_has_srcidentifier() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ResponseVoteRpc::clear_has_srcidentifier() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ResponseVoteRpc::clear_srcidentifier() {
  if (srcidentifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    srcidentifier_->clear();
  }
  clear_has_srcidentifier();
}
inline const ::std::string& ResponseVoteRpc::srcidentifier() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ResponseVoteRpc.srcIdentifier)
  return *srcidentifier_;
}
inline void ResponseVoteRpc::set_srcidentifier(const ::std::string& value) {
  set_has_srcidentifier();
  if (srcidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    srcidentifier_ = new ::std::string;
  }
  srcidentifier_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ResponseVoteRpc.srcIdentifier)
}
inline void ResponseVoteRpc::set_srcidentifier(const char* value) {
  set_has_srcidentifier();
  if (srcidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    srcidentifier_ = new ::std::string;
  }
  srcidentifier_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ResponseVoteRpc.srcIdentifier)
}
inline void ResponseVoteRpc::set_srcidentifier(const char* value, size_t size) {
  set_has_srcidentifier();
  if (srcidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    srcidentifier_ = new ::std::string;
  }
  srcidentifier_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ResponseVoteRpc.srcIdentifier)
}
inline ::std::string* ResponseVoteRpc::mutable_srcidentifier() {
  set_has_srcidentifier();
  if (srcidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    srcidentifier_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ResponseVoteRpc.srcIdentifier)
  return srcidentifier_;
}
inline ::std::string* ResponseVoteRpc::release_srcidentifier() {
  clear_has_srcidentifier();
  if (srcidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = srcidentifier_;
    srcidentifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResponseVoteRpc::set_allocated_srcidentifier(::std::string* srcidentifier) {
  if (srcidentifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete srcidentifier_;
  }
  if (srcidentifier) {
    set_has_srcidentifier();
    srcidentifier_ = srcidentifier;
  } else {
    clear_has_srcidentifier();
    srcidentifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ResponseVoteRpc.srcIdentifier)
}

// optional string desIdentifier = 3 [default = ""];
inline bool ResponseVoteRpc::has_desidentifier() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ResponseVoteRpc::set_has_desidentifier() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ResponseVoteRpc::clear_has_desidentifier() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ResponseVoteRpc::clear_desidentifier() {
  if (desidentifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desidentifier_->clear();
  }
  clear_has_desidentifier();
}
inline const ::std::string& ResponseVoteRpc::desidentifier() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ResponseVoteRpc.desIdentifier)
  return *desidentifier_;
}
inline void ResponseVoteRpc::set_desidentifier(const ::std::string& value) {
  set_has_desidentifier();
  if (desidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desidentifier_ = new ::std::string;
  }
  desidentifier_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ResponseVoteRpc.desIdentifier)
}
inline void ResponseVoteRpc::set_desidentifier(const char* value) {
  set_has_desidentifier();
  if (desidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desidentifier_ = new ::std::string;
  }
  desidentifier_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ResponseVoteRpc.desIdentifier)
}
inline void ResponseVoteRpc::set_desidentifier(const char* value, size_t size) {
  set_has_desidentifier();
  if (desidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desidentifier_ = new ::std::string;
  }
  desidentifier_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ResponseVoteRpc.desIdentifier)
}
inline ::std::string* ResponseVoteRpc::mutable_desidentifier() {
  set_has_desidentifier();
  if (desidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    desidentifier_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ResponseVoteRpc.desIdentifier)
  return desidentifier_;
}
inline ::std::string* ResponseVoteRpc::release_desidentifier() {
  clear_has_desidentifier();
  if (desidentifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = desidentifier_;
    desidentifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ResponseVoteRpc::set_allocated_desidentifier(::std::string* desidentifier) {
  if (desidentifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete desidentifier_;
  }
  if (desidentifier) {
    set_has_desidentifier();
    desidentifier_ = desidentifier;
  } else {
    clear_has_desidentifier();
    desidentifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ResponseVoteRpc.desIdentifier)
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

#endif  // PROTOBUF_ResponseRpcBean_2eproto__INCLUDED