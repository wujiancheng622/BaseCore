// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: BMSAcceptBPX.proto

#ifndef PROTOBUF_BMSAcceptBPX_2eproto__INCLUDED
#define PROTOBUF_BMSAcceptBPX_2eproto__INCLUDED

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
namespace bmsbpx {
namespace proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_BMSAcceptBPX_2eproto();
void protobuf_AssignDesc_BMSAcceptBPX_2eproto();
void protobuf_ShutdownFile_BMSAcceptBPX_2eproto();

class BMSAcceptBPX;

// ===================================================================

class BMSAcceptBPX : public ::google::protobuf::Message {
 public:
  BMSAcceptBPX();
  virtual ~BMSAcceptBPX();

  BMSAcceptBPX(const BMSAcceptBPX& from);

  inline BMSAcceptBPX& operator=(const BMSAcceptBPX& from) {
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
  static const BMSAcceptBPX& default_instance();

  void Swap(BMSAcceptBPX* other);

  // implements Message ----------------------------------------------

  BMSAcceptBPX* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const BMSAcceptBPX& from);
  void MergeFrom(const BMSAcceptBPX& from);
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

  // required int64 hHandle = 41;
  inline bool has_hhandle() const;
  inline void clear_hhandle();
  static const int kHHandleFieldNumber = 41;
  inline ::google::protobuf::int64 hhandle() const;
  inline void set_hhandle(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:com.arges.bmsbpx.proto.BMSAcceptBPX)
 private:
  inline void set_has_hhandle();
  inline void clear_has_hhandle();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 hhandle_;
  friend void  protobuf_AddDesc_BMSAcceptBPX_2eproto();
  friend void protobuf_AssignDesc_BMSAcceptBPX_2eproto();
  friend void protobuf_ShutdownFile_BMSAcceptBPX_2eproto();

  void InitAsDefaultInstance();
  static BMSAcceptBPX* default_instance_;
};
// ===================================================================


// ===================================================================

// BMSAcceptBPX

// required int64 hHandle = 41;
inline bool BMSAcceptBPX::has_hhandle() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void BMSAcceptBPX::set_has_hhandle() {
  _has_bits_[0] |= 0x00000001u;
}
inline void BMSAcceptBPX::clear_has_hhandle() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void BMSAcceptBPX::clear_hhandle() {
  hhandle_ = GOOGLE_LONGLONG(0);
  clear_has_hhandle();
}
inline ::google::protobuf::int64 BMSAcceptBPX::hhandle() const {
  // @@protoc_insertion_point(field_get:com.arges.bmsbpx.proto.BMSAcceptBPX.hHandle)
  return hhandle_;
}
inline void BMSAcceptBPX::set_hhandle(::google::protobuf::int64 value) {
  set_has_hhandle();
  hhandle_ = value;
  // @@protoc_insertion_point(field_set:com.arges.bmsbpx.proto.BMSAcceptBPX.hHandle)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace bmsbpx
}  // namespace arges
}  // namespace com

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_BMSAcceptBPX_2eproto__INCLUDED
