/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: actionPutPerflowAckMsg.proto */

#ifndef PROTOBUF_C_actionPutPerflowAckMsg_2eproto__INCLUDED
#define PROTOBUF_C_actionPutPerflowAckMsg_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _ActionPutPerflowAckMsg ActionPutPerflowAckMsg;


/* --- enums --- */


/* --- messages --- */

struct  _ActionPutPerflowAckMsg
{
  ProtobufCMessage base;
  uint32_t hash;
};
#define ACTION_PUT_PERFLOW_ACK_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_put_perflow_ack_msg__descriptor) \
    , 0 }


/* ActionPutPerflowAckMsg methods */
void   action_put_perflow_ack_msg__init
                     (ActionPutPerflowAckMsg         *message);
size_t action_put_perflow_ack_msg__get_packed_size
                     (const ActionPutPerflowAckMsg   *message);
size_t action_put_perflow_ack_msg__pack
                     (const ActionPutPerflowAckMsg   *message,
                      uint8_t             *out);
size_t action_put_perflow_ack_msg__pack_to_buffer
                     (const ActionPutPerflowAckMsg   *message,
                      ProtobufCBuffer     *buffer);
ActionPutPerflowAckMsg *
       action_put_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   action_put_perflow_ack_msg__free_unpacked
                     (ActionPutPerflowAckMsg *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ActionPutPerflowAckMsg_Closure)
                 (const ActionPutPerflowAckMsg *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor action_put_perflow_ack_msg__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_actionPutPerflowAckMsg_2eproto__INCLUDED */
