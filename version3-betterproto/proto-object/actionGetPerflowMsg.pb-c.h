/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: actionGetPerflowMsg.proto */

#ifndef PROTOBUF_C_actionGetPerflowMsg_2eproto__INCLUDED
#define PROTOBUF_C_actionGetPerflowMsg_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _ActionGetPerflowMsg ActionGetPerflowMsg;


/* --- enums --- */


/* --- messages --- */

struct  _ActionGetPerflowMsg
{
  ProtobufCMessage base;
  char *key;
};
#define ACTION_GET_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_get_perflow_msg__descriptor) \
    , NULL }


/* ActionGetPerflowMsg methods */
void   action_get_perflow_msg__init
                     (ActionGetPerflowMsg         *message);
size_t action_get_perflow_msg__get_packed_size
                     (const ActionGetPerflowMsg   *message);
size_t action_get_perflow_msg__pack
                     (const ActionGetPerflowMsg   *message,
                      uint8_t             *out);
size_t action_get_perflow_msg__pack_to_buffer
                     (const ActionGetPerflowMsg   *message,
                      ProtobufCBuffer     *buffer);
ActionGetPerflowMsg *
       action_get_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   action_get_perflow_msg__free_unpacked
                     (ActionGetPerflowMsg *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ActionGetPerflowMsg_Closure)
                 (const ActionGetPerflowMsg *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor action_get_perflow_msg__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_actionGetPerflowMsg_2eproto__INCLUDED */
