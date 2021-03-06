/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: MyMessage.proto */

#ifndef PROTOBUF_C_MyMessage_2eproto__INCLUDED
#define PROTOBUF_C_MyMessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _MyMessage MyMessage;
typedef struct _Syn Syn;
typedef struct _Person Person;


/* --- enums --- */

typedef enum _MyMessage__DataType {
  MY_MESSAGE__DATA_TYPE__SynType = 1,
  MY_MESSAGE__DATA_TYPE__PersonType = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_MESSAGE__DATA_TYPE)
} MyMessage__DataType;

/* --- messages --- */

typedef enum {
  MY_MESSAGE__MESSAGE__NOT_SET = 0,
  MY_MESSAGE__MESSAGE_SYN = 2,
  MY_MESSAGE__MESSAGE_PERSON = 3
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_MESSAGE__MESSAGE)
} MyMessage__MessageCase;

struct  _MyMessage
{
  ProtobufCMessage base;
  MyMessage__DataType data_type;
  MyMessage__MessageCase message_case;
  union {
    Syn *syn;
    Person *person;
  };
};
#define MY_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&my_message__descriptor) \
    , MY_MESSAGE__DATA_TYPE__SynType, MY_MESSAGE__MESSAGE__NOT_SET, {0} }


struct  _Syn
{
  ProtobufCMessage base;
  char *host;
  protobuf_c_boolean has_pid;
  uint32_t pid;
};
#define SYN__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&syn__descriptor) \
    , NULL, 0, 0 }


struct  _Person
{
  ProtobufCMessage base;
  char *name;
  protobuf_c_boolean has_age;
  int32_t age;
  char *address;
};
#define PERSON__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&person__descriptor) \
    , NULL, 0, 0, NULL }


/* MyMessage methods */
void   my_message__init
                     (MyMessage         *message);
size_t my_message__get_packed_size
                     (const MyMessage   *message);
size_t my_message__pack
                     (const MyMessage   *message,
                      uint8_t             *out);
size_t my_message__pack_to_buffer
                     (const MyMessage   *message,
                      ProtobufCBuffer     *buffer);
MyMessage *
       my_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   my_message__free_unpacked
                     (MyMessage *message,
                      ProtobufCAllocator *allocator);
/* Syn methods */
void   syn__init
                     (Syn         *message);
size_t syn__get_packed_size
                     (const Syn   *message);
size_t syn__pack
                     (const Syn   *message,
                      uint8_t             *out);
size_t syn__pack_to_buffer
                     (const Syn   *message,
                      ProtobufCBuffer     *buffer);
Syn *
       syn__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   syn__free_unpacked
                     (Syn *message,
                      ProtobufCAllocator *allocator);
/* Person methods */
void   person__init
                     (Person         *message);
size_t person__get_packed_size
                     (const Person   *message);
size_t person__pack
                     (const Person   *message,
                      uint8_t             *out);
size_t person__pack_to_buffer
                     (const Person   *message,
                      ProtobufCBuffer     *buffer);
Person *
       person__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   person__free_unpacked
                     (Person *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*MyMessage_Closure)
                 (const MyMessage *message,
                  void *closure_data);
typedef void (*Syn_Closure)
                 (const Syn *message,
                  void *closure_data);
typedef void (*Person_Closure)
                 (const Person *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor my_message__descriptor;
extern const ProtobufCEnumDescriptor    my_message__data_type__descriptor;
extern const ProtobufCMessageDescriptor syn__descriptor;
extern const ProtobufCMessageDescriptor person__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_MyMessage_2eproto__INCLUDED */
