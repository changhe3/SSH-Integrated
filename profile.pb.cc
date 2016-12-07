// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: profile.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "profile.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace ssh_profile {

namespace {

const ::google::protobuf::Descriptor* profile_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  profile_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_profile_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_profile_2eproto() {
  protobuf_AddDesc_profile_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "profile.proto");
  GOOGLE_CHECK(file != NULL);
  profile_descriptor_ = file->message_type(0);
  static const int profile_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, host_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, user_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, port_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, password_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, path_),
  };
  profile_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      profile_descriptor_,
      profile::default_instance_,
      profile_offsets_,
      -1,
      -1,
      -1,
      sizeof(profile),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(profile, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_profile_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      profile_descriptor_, &profile::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_profile_2eproto() {
  delete profile::default_instance_;
  delete profile_reflection_;
}

void protobuf_AddDesc_profile_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_profile_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rprofile.proto\022\013ssh_profile\"S\n\007profile\022"
    "\014\n\004host\030\001 \001(\t\022\014\n\004user\030\002 \001(\t\022\014\n\004port\030\003 \001("
    "\005\022\020\n\010password\030\004 \001(\t\022\014\n\004path\030\020 \001(\tb\006proto"
    "3", 121);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "profile.proto", &protobuf_RegisterTypes);
  profile::default_instance_ = new profile();
  profile::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_profile_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_profile_2eproto {
  StaticDescriptorInitializer_profile_2eproto() {
    protobuf_AddDesc_profile_2eproto();
  }
} static_descriptor_initializer_profile_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int profile::kHostFieldNumber;
const int profile::kUserFieldNumber;
const int profile::kPortFieldNumber;
const int profile::kPasswordFieldNumber;
const int profile::kPathFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

profile::profile()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ssh_profile.profile)
}

void profile::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

profile::profile(const profile& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:ssh_profile.profile)
}

void profile::SharedCtor() {
    _is_default_instance_ = false;
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  host_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  user_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  port_ = 0;
  password_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  path_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

profile::~profile() {
  // @@protoc_insertion_point(destructor:ssh_profile.profile)
  SharedDtor();
}

void profile::SharedDtor() {
  host_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  user_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  password_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  path_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void profile::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* profile::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return profile_descriptor_;
}

const profile& profile::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_profile_2eproto();
  return *default_instance_;
}

profile* profile::default_instance_ = NULL;

profile* profile::New(::google::protobuf::Arena* arena) const {
  profile* n = new profile;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void profile::Clear() {
// @@protoc_insertion_point(message_clear_start:ssh_profile.profile)
  host_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  user_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  port_ = 0;
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool profile::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ssh_profile.profile)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(16383);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string host = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_host()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->host().data(), this->host().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "ssh_profile.profile.host"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_user;
        break;
      }

      // optional string user = 2;
      case 2: {
        if (tag == 18) {
         parse_user:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_user()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->user().data(), this->user().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "ssh_profile.profile.user"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_port;
        break;
      }

      // optional int32 port = 3;
      case 3: {
        if (tag == 24) {
         parse_port:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &port_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_password;
        break;
      }

      // optional string password = 4;
      case 4: {
        if (tag == 34) {
         parse_password:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_password()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->password().data(), this->password().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "ssh_profile.profile.password"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(130)) goto parse_path;
        break;
      }

      // optional string path = 16;
      case 16: {
        if (tag == 130) {
         parse_path:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_path()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->path().data(), this->path().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "ssh_profile.profile.path"));
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
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ssh_profile.profile)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ssh_profile.profile)
  return false;
#undef DO_
}

void profile::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ssh_profile.profile)
  // optional string host = 1;
  if (this->host().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->host().data(), this->host().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.host");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->host(), output);
  }

  // optional string user = 2;
  if (this->user().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->user().data(), this->user().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.user");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->user(), output);
  }

  // optional int32 port = 3;
  if (this->port() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->port(), output);
  }

  // optional string password = 4;
  if (this->password().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->password().data(), this->password().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.password");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      4, this->password(), output);
  }

  // optional string path = 16;
  if (this->path().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.path");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      16, this->path(), output);
  }

  // @@protoc_insertion_point(serialize_end:ssh_profile.profile)
}

::google::protobuf::uint8* profile::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ssh_profile.profile)
  // optional string host = 1;
  if (this->host().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->host().data(), this->host().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.host");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->host(), target);
  }

  // optional string user = 2;
  if (this->user().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->user().data(), this->user().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.user");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->user(), target);
  }

  // optional int32 port = 3;
  if (this->port() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->port(), target);
  }

  // optional string password = 4;
  if (this->password().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->password().data(), this->password().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.password");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->password(), target);
  }

  // optional string path = 16;
  if (this->path().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "ssh_profile.profile.path");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        16, this->path(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:ssh_profile.profile)
  return target;
}

int profile::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:ssh_profile.profile)
  int total_size = 0;

  // optional string host = 1;
  if (this->host().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->host());
  }

  // optional string user = 2;
  if (this->user().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->user());
  }

  // optional int32 port = 3;
  if (this->port() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->port());
  }

  // optional string password = 4;
  if (this->password().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->password());
  }

  // optional string path = 16;
  if (this->path().size() > 0) {
    total_size += 2 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->path());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void profile::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ssh_profile.profile)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const profile* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const profile>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ssh_profile.profile)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ssh_profile.profile)
    MergeFrom(*source);
  }
}

void profile::MergeFrom(const profile& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ssh_profile.profile)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  if (from.host().size() > 0) {

    host_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.host_);
  }
  if (from.user().size() > 0) {

    user_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.user_);
  }
  if (from.port() != 0) {
    set_port(from.port());
  }
  if (from.password().size() > 0) {

    password_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.password_);
  }
  if (from.path().size() > 0) {

    path_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.path_);
  }
}

void profile::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ssh_profile.profile)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void profile::CopyFrom(const profile& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ssh_profile.profile)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool profile::IsInitialized() const {

  return true;
}

void profile::Swap(profile* other) {
  if (other == this) return;
  InternalSwap(other);
}
void profile::InternalSwap(profile* other) {
  host_.Swap(&other->host_);
  user_.Swap(&other->user_);
  std::swap(port_, other->port_);
  password_.Swap(&other->password_);
  path_.Swap(&other->path_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata profile::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = profile_descriptor_;
  metadata.reflection = profile_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// profile

// optional string host = 1;
void profile::clear_host() {
  host_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& profile::host() const {
  // @@protoc_insertion_point(field_get:ssh_profile.profile.host)
  return host_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_host(const ::std::string& value) {
  
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ssh_profile.profile.host)
}
 void profile::set_host(const char* value) {
  
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ssh_profile.profile.host)
}
 void profile::set_host(const char* value, size_t size) {
  
  host_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ssh_profile.profile.host)
}
 ::std::string* profile::mutable_host() {
  
  // @@protoc_insertion_point(field_mutable:ssh_profile.profile.host)
  return host_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* profile::release_host() {
  // @@protoc_insertion_point(field_release:ssh_profile.profile.host)
  
  return host_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_allocated_host(::std::string* host) {
  if (host != NULL) {
    
  } else {
    
  }
  host_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), host);
  // @@protoc_insertion_point(field_set_allocated:ssh_profile.profile.host)
}

// optional string user = 2;
void profile::clear_user() {
  user_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& profile::user() const {
  // @@protoc_insertion_point(field_get:ssh_profile.profile.user)
  return user_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_user(const ::std::string& value) {
  
  user_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ssh_profile.profile.user)
}
 void profile::set_user(const char* value) {
  
  user_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ssh_profile.profile.user)
}
 void profile::set_user(const char* value, size_t size) {
  
  user_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ssh_profile.profile.user)
}
 ::std::string* profile::mutable_user() {
  
  // @@protoc_insertion_point(field_mutable:ssh_profile.profile.user)
  return user_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* profile::release_user() {
  // @@protoc_insertion_point(field_release:ssh_profile.profile.user)
  
  return user_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_allocated_user(::std::string* user) {
  if (user != NULL) {
    
  } else {
    
  }
  user_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), user);
  // @@protoc_insertion_point(field_set_allocated:ssh_profile.profile.user)
}

// optional int32 port = 3;
void profile::clear_port() {
  port_ = 0;
}
 ::google::protobuf::int32 profile::port() const {
  // @@protoc_insertion_point(field_get:ssh_profile.profile.port)
  return port_;
}
 void profile::set_port(::google::protobuf::int32 value) {
  
  port_ = value;
  // @@protoc_insertion_point(field_set:ssh_profile.profile.port)
}

// optional string password = 4;
void profile::clear_password() {
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& profile::password() const {
  // @@protoc_insertion_point(field_get:ssh_profile.profile.password)
  return password_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_password(const ::std::string& value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ssh_profile.profile.password)
}
 void profile::set_password(const char* value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ssh_profile.profile.password)
}
 void profile::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ssh_profile.profile.password)
}
 ::std::string* profile::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:ssh_profile.profile.password)
  return password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* profile::release_password() {
  // @@protoc_insertion_point(field_release:ssh_profile.profile.password)
  
  return password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_allocated_password(::std::string* password) {
  if (password != NULL) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:ssh_profile.profile.password)
}

// optional string path = 16;
void profile::clear_path() {
  path_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 const ::std::string& profile::path() const {
  // @@protoc_insertion_point(field_get:ssh_profile.profile.path)
  return path_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_path(const ::std::string& value) {
  
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:ssh_profile.profile.path)
}
 void profile::set_path(const char* value) {
  
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:ssh_profile.profile.path)
}
 void profile::set_path(const char* value, size_t size) {
  
  path_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:ssh_profile.profile.path)
}
 ::std::string* profile::mutable_path() {
  
  // @@protoc_insertion_point(field_mutable:ssh_profile.profile.path)
  return path_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* profile::release_path() {
  // @@protoc_insertion_point(field_release:ssh_profile.profile.path)
  
  return path_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void profile::set_allocated_path(::std::string* path) {
  if (path != NULL) {
    
  } else {
    
  }
  path_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), path);
  // @@protoc_insertion_point(field_set_allocated:ssh_profile.profile.path)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace ssh_profile

// @@protoc_insertion_point(global_scope)