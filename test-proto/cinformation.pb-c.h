/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: cinformation.proto */

#ifndef PROTOBUF_C_cinformation_2eproto__INCLUDED
#define PROTOBUF_C_cinformation_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "student.pb-c.h"

typedef struct _Cinformation Cinformation;


/* --- enums --- */


/* --- messages --- */

struct  _Cinformation
{
  ProtobufCMessage base;
  uint32_t personnum;
  char *content;
  Student *student;
  Cinformation *cinfo;
};
#define CINFORMATION__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&cinformation__descriptor) \
    , 0, NULL, NULL, NULL }


/* Cinformation methods */
void   cinformation__init
                     (Cinformation         *message);
size_t cinformation__get_packed_size
                     (const Cinformation   *message);
size_t cinformation__pack
                     (const Cinformation   *message,
                      uint8_t             *out);
size_t cinformation__pack_to_buffer
                     (const Cinformation   *message,
                      ProtobufCBuffer     *buffer);
Cinformation *
       cinformation__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   cinformation__free_unpacked
                     (Cinformation *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Cinformation_Closure)
                 (const Cinformation *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor cinformation__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_cinformation_2eproto__INCLUDED */
