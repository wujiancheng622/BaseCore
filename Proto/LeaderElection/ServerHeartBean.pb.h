// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ServerHeartBean.proto

#ifndef PROTOBUF_ServerHeartBean_2eproto__INCLUDED
#define PROTOBUF_ServerHeartBean_2eproto__INCLUDED

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
void  protobuf_AddDesc_ServerHeartBean_2eproto();
void protobuf_AssignDesc_ServerHeartBean_2eproto();
void protobuf_ShutdownFile_ServerHeartBean_2eproto();

class ServerHeart;

// ===================================================================

class ServerHeart : public ::google::protobuf::Message {
 public:
  ServerHeart();
  virtual ~ServerHeart();

  ServerHeart(const ServerHeart& from);

  inline ServerHeart& operator=(const ServerHeart& from) {
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
  static const ServerHeart& default_instance();

  void Swap(ServerHeart* other);

  // implements Message ----------------------------------------------

  ServerHeart* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ServerHeart& from);
  void MergeFrom(const ServerHeart& from);
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

  // optional string identifier = 2 [default = ""];
  inline bool has_identifier() const;
  inline void clear_identifier();
  static const int kIdentifierFieldNumber = 2;
  inline const ::std::string& identifier() const;
  inline void set_identifier(const ::std::string& value);
  inline void set_identifier(const char* value);
  inline void set_identifier(const char* value, size_t size);
  inline ::std::string* mutable_identifier();
  inline ::std::string* release_identifier();
  inline void set_allocated_identifier(::std::string* identifier);

  // optional string content = 3 [default = ""];
  inline bool has_content() const;
  inline void clear_content();
  static const int kContentFieldNumber = 3;
  inline const ::std::string& content() const;
  inline void set_content(const ::std::string& value);
  inline void set_content(const char* value);
  inline void set_content(const char* value, size_t size);
  inline ::std::string* mutable_content();
  inline ::std::string* release_content();
  inline void set_allocated_content(::std::string* content);

  // @@protoc_insertion_point(class_scope:com.arges.file.proto.ServerHeart)
 private:
  inline void set_has_term();
  inline void clear_has_term();
  inline void set_has_identifier();
  inline void clear_has_identifier();
  inline void set_has_content();
  inline void clear_has_content();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* term_;
  ::std::string* identifier_;
  ::std::string* content_;
  friend void  protobuf_AddDesc_ServerHeartBean_2eproto();
  friend void protobuf_AssignDesc_ServerHeartBean_2eproto();
  friend void protobuf_ShutdownFile_ServerHeartBean_2eproto();

  void InitAsDefaultInstance();
  static ServerHeart* default_instance_;
};
// ===================================================================


// ===================================================================

// ServerHeart

// optional string term = 1 [default = ""];
inline bool ServerHeart::has_term() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ServerHeart::set_has_term() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ServerHeart::clear_has_term() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ServerHeart::clear_term() {
  if (term_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_->clear();
  }
  clear_has_term();
}
inline const ::std::string& ServerHeart::term() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ServerHeart.term)
  return *term_;
}
inline void ServerHeart::set_term(const ::std::string& value) {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  term_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ServerHeart.term)
}
inline void ServerHeart::set_term(const char* value) {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  term_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ServerHeart.term)
}
inline void ServerHeart::set_term(const char* value, size_t size) {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  term_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ServerHeart.term)
}
inline ::std::string* ServerHeart::mutable_term() {
  set_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    term_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ServerHeart.term)
  return term_;
}
inline ::std::string* ServerHeart::release_term() {
  clear_has_term();
  if (term_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = term_;
    term_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ServerHeart::set_allocated_term(::std::string* term) {
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
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ServerHeart.term)
}

// optional string identifier = 2 [default = ""];
inline bool ServerHeart::has_identifier() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ServerHeart::set_has_identifier() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ServerHeart::clear_has_identifier() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ServerHeart::clear_identifier() {
  if (identifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    identifier_->clear();
  }
  clear_has_identifier();
}
inline const ::std::string& ServerHeart::identifier() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ServerHeart.identifier)
  return *identifier_;
}
inline void ServerHeart::set_identifier(const ::std::string& value) {
  set_has_identifier();
  if (identifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    identifier_ = new ::std::string;
  }
  identifier_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ServerHeart.identifier)
}
inline void ServerHeart::set_identifier(const char* value) {
  set_has_identifier();
  if (identifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    identifier_ = new ::std::string;
  }
  identifier_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ServerHeart.identifier)
}
inline void ServerHeart::set_identifier(const char* value, size_t size) {
  set_has_identifier();
  if (identifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    identifier_ = new ::std::string;
  }
  identifier_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ServerHeart.identifier)
}
inline ::std::string* ServerHeart::mutable_identifier() {
  set_has_identifier();
  if (identifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    identifier_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ServerHeart.identifier)
  return identifier_;
}
inline ::std::string* ServerHeart::release_identifier() {
  clear_has_identifier();
  if (identifier_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = identifier_;
    identifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ServerHeart::set_allocated_identifier(::std::string* identifier) {
  if (identifier_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete identifier_;
  }
  if (identifier) {
    set_has_identifier();
    identifier_ = identifier;
  } else {
    clear_has_identifier();
    identifier_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ServerHeart.identifier)
}

// optional string content = 3 [default = ""];
inline bool ServerHeart::has_content() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ServerHeart::set_has_content() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ServerHeart::clear_has_content() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ServerHeart::clear_content() {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_->clear();
  }
  clear_has_content();
}
inline const ::std::string& ServerHeart::content() const {
  // @@protoc_insertion_point(field_get:com.arges.file.proto.ServerHeart.content)
  return *content_;
}
inline void ServerHeart::set_content(const ::std::string& value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(value);
  // @@protoc_insertion_point(field_set:com.arges.file.proto.ServerHeart.content)
}
inline void ServerHeart::set_content(const char* value) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(value);
  // @@protoc_insertion_point(field_set_char:com.arges.file.proto.ServerHeart.content)
}
inline void ServerHeart::set_content(const char* value, size_t size) {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  content_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:com.arges.file.proto.ServerHeart.content)
}
inline ::std::string* ServerHeart::mutable_content() {
  set_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    content_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:com.arges.file.proto.ServerHeart.content)
  return content_;
}
inline ::std::string* ServerHeart::release_content() {
  clear_has_content();
  if (content_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = content_;
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void ServerHeart::set_allocated_content(::std::string* content) {
  if (content_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete content_;
  }
  if (content) {
    set_has_content();
    content_ = content;
  } else {
    clear_has_content();
    content_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:com.arges.file.proto.ServerHeart.content)
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

#endif  // PROTOBUF_ServerHeartBean_2eproto__INCLUDED
