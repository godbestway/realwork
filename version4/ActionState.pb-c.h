/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ActionState.proto */

#ifndef PROTOBUF_C_ActionState_2eproto__INCLUDED
#define PROTOBUF_C_ActionState_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _ActionState ActionState;


/* --- enums --- */


/* --- messages --- */

struct  _ActionState
{
  ProtobufCMessage base;
  size_t n_start_time;
  uint64_t *start_time;
  size_t n_last_pkt_time;
  uint64_t *last_pkt_time;
  uint64_t cxid;
  uint32_t reversed;
  uint32_t af;
  uint32_t hw_proto;
  uint32_t proto;
  uint64_t s_total_pkts;
  uint64_t s_total_bytes;
  uint64_t d_total_pkts;
  uint64_t d_total_bytes;
  uint32_t s_tcpflags;
  uint32_t pad;
  uint32_t d_tcpflags;
  uint32_t check;
  uint32_t hash;
};
#define ACTION_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_state__descriptor) \
    , 0,NULL, 0,NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }


/* ActionState methods */
void   action_state__init
                     (ActionState         *message);
size_t action_state__get_packed_size
                     (const ActionState   *message);
size_t action_state__pack
                     (const ActionState   *message,
                      uint8_t             *out);
size_t action_state__pack_to_buffer
                     (const ActionState   *message,
                      ProtobufCBuffer     *buffer);
ActionState *
       action_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   action_state__free_unpacked
                     (ActionState *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ActionState_Closure)
                 (const ActionState *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor action_state__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_ActionState_2eproto__INCLUDED */