/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: syn.proto */

#ifndef PROTOBUF_C_syn_2eproto__INCLUDED
#define PROTOBUF_C_syn_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Syn Syn;


/* --- enums --- */


/* --- messages --- */

struct  _Syn
{
  ProtobufCMessage base;
  char *host;
  uint32_t pid;
};
#define SYN__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&syn__descriptor) \
    , NULL, 0 }


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
/* --- per-message closures --- */

typedef void (*Syn_Closure)
                 (const Syn *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor syn__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_syn_2eproto__INCLUDED */
