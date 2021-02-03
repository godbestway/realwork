/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: connPutPerflowMsg.proto */

#ifndef PROTOBUF_C_connPutPerflowMsg_2eproto__INCLUDED
#define PROTOBUF_C_connPutPerflowMsg_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "ConnState.pb-c.h"

typedef struct _ConnPutPerflowMsg ConnPutPerflowMsg;


/* --- enums --- */


/* --- messages --- */

struct  _ConnPutPerflowMsg
{
  ProtobufCMessage base;
  ConnState *state;
};
#define CONN_PUT_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_put_perflow_msg__descriptor) \
    , NULL }


/* ConnPutPerflowMsg methods */
void   conn_put_perflow_msg__init
                     (ConnPutPerflowMsg         *message);
size_t conn_put_perflow_msg__get_packed_size
                     (const ConnPutPerflowMsg   *message);
size_t conn_put_perflow_msg__pack
                     (const ConnPutPerflowMsg   *message,
                      uint8_t             *out);
size_t conn_put_perflow_msg__pack_to_buffer
                     (const ConnPutPerflowMsg   *message,
                      ProtobufCBuffer     *buffer);
ConnPutPerflowMsg *
       conn_put_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   conn_put_perflow_msg__free_unpacked
                     (ConnPutPerflowMsg *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ConnPutPerflowMsg_Closure)
                 (const ConnPutPerflowMsg *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor conn_put_perflow_msg__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_connPutPerflowMsg_2eproto__INCLUDED */
