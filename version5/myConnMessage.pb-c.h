/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: myConnMessage.proto */

#ifndef PROTOBUF_C_myConnMessage_2eproto__INCLUDED
#define PROTOBUF_C_myConnMessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _MyConnMessage MyConnMessage;
typedef struct _ConnSyn ConnSyn;
typedef struct _ConnGetPerflowMsg ConnGetPerflowMsg;
typedef struct _ConnGetPerflowAckMsg ConnGetPerflowAckMsg;
typedef struct _ConnState ConnState;
typedef struct _ConnPutPerflowMsg ConnPutPerflowMsg;
typedef struct _ConnPutPerflowAckMsg ConnPutPerflowAckMsg;


/* --- enums --- */

typedef enum _MyConnMessage__DataType {
  MY_CONN_MESSAGE__DATA_TYPE__SynType = 1,
  MY_CONN_MESSAGE__DATA_TYPE__ConnGetPerflowMsgType = 2,
  MY_CONN_MESSAGE__DATA_TYPE__ConnGetPerflowAckMsgType = 3,
  MY_CONN_MESSAGE__DATA_TYPE__ConnStateType = 4,
  MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowMsgType = 5,
  MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowAckMsgType = 6
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_CONN_MESSAGE__DATA_TYPE)
} MyConnMessage__DataType;

/* --- messages --- */

typedef enum {
  MY_CONN_MESSAGE__MESSAGE__NOT_SET = 0,
  MY_CONN_MESSAGE__MESSAGE_CONNSYN = 2,
  MY_CONN_MESSAGE__MESSAGE_CONN_GET_PERFLOW_MSG = 3,
  MY_CONN_MESSAGE__MESSAGE_CONN_GET_PERFLOW_ACK_MSG = 4,
  MY_CONN_MESSAGE__MESSAGE_CONN_STATE = 5,
  MY_CONN_MESSAGE__MESSAGE_CONN_PUT_PERFLOW_MSG = 6,
  MY_CONN_MESSAGE__MESSAGE_CONN_PUT_PERFLOW_ACK_MSG = 7
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_CONN_MESSAGE__MESSAGE)
} MyConnMessage__MessageCase;

struct  _MyConnMessage
{
  ProtobufCMessage base;
  MyConnMessage__DataType data_type;
  MyConnMessage__MessageCase message_case;
  union {
    ConnSyn *connsyn;
    ConnGetPerflowMsg *conngetperflowmsg;
    ConnGetPerflowAckMsg *conngetperflowackmsg;
    ConnState *connstate;
    ConnPutPerflowMsg *connputperflowmsg;
    ConnPutPerflowAckMsg *connputperflowackmsg;
  };
};
#define MY_CONN_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&my_conn_message__descriptor) \
    , MY_CONN_MESSAGE__DATA_TYPE__SynType, MY_CONN_MESSAGE__MESSAGE__NOT_SET, {0} }


struct  _ConnSyn
{
  ProtobufCMessage base;
  char *host;
  protobuf_c_boolean has_pid;
  uint32_t pid;
};
#define CONN_SYN__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_syn__descriptor) \
    , NULL, 0, 0 }


struct  _ConnGetPerflowMsg
{
  ProtobufCMessage base;
  protobuf_c_boolean has_hw_proto;
  int32_t hw_proto;
  protobuf_c_boolean has_proto;
  int32_t proto;
};
#define CONN_GET_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_get_perflow_msg__descriptor) \
    , 0, 0, 0, 0 }


struct  _ConnGetPerflowAckMsg
{
  ProtobufCMessage base;
  protobuf_c_boolean has_count;
  uint32_t count;
};
#define CONN_GET_PERFLOW_ACK_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_get_perflow_ack_msg__descriptor) \
    , 0, 0 }


struct  _ConnState
{
  ProtobufCMessage base;
  size_t n_ether_dst;
  uint32_t *ether_dst;
  size_t n_ether_src;
  uint32_t *ether_src;
  protobuf_c_boolean has_s_ip;
  uint32_t s_ip;
  protobuf_c_boolean has_d_ip;
  uint32_t d_ip;
  protobuf_c_boolean has_s_port;
  uint32_t s_port;
  protobuf_c_boolean has_d_port;
  uint32_t d_port;
  protobuf_c_boolean has_hw_proto;
  int32_t hw_proto;
  protobuf_c_boolean has_proto;
  int32_t proto;
  protobuf_c_boolean has_cxid;
  uint64_t cxid;
  protobuf_c_boolean has_hash;
  uint32_t hash;
  protobuf_c_boolean has_nat_hash;
  uint32_t nat_hash;
};
#define CONN_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_state__descriptor) \
    , 0,NULL, 0,NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }


struct  _ConnPutPerflowMsg
{
  ProtobufCMessage base;
  ConnState *state;
};
#define CONN_PUT_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_put_perflow_msg__descriptor) \
    , NULL }


struct  _ConnPutPerflowAckMsg
{
  ProtobufCMessage base;
  protobuf_c_boolean has_hash;
  uint32_t hash;
  protobuf_c_boolean has_cxid;
  uint32_t cxid;
};
#define CONN_PUT_PERFLOW_ACK_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_put_perflow_ack_msg__descriptor) \
    , 0, 0, 0, 0 }


/* MyConnMessage methods */
void   my_conn_message__init
                     (MyConnMessage         *message);
size_t my_conn_message__get_packed_size
                     (const MyConnMessage   *message);
size_t my_conn_message__pack
                     (const MyConnMessage   *message,
                      uint8_t             *out);
size_t my_conn_message__pack_to_buffer
                     (const MyConnMessage   *message,
                      ProtobufCBuffer     *buffer);
MyConnMessage *
       my_conn_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   my_conn_message__free_unpacked
                     (MyConnMessage *message,
                      ProtobufCAllocator *allocator);
/* ConnSyn methods */
void   conn_syn__init
                     (ConnSyn         *message);
size_t conn_syn__get_packed_size
                     (const ConnSyn   *message);
size_t conn_syn__pack
                     (const ConnSyn   *message,
                      uint8_t             *out);
size_t conn_syn__pack_to_buffer
                     (const ConnSyn   *message,
                      ProtobufCBuffer     *buffer);
ConnSyn *
       conn_syn__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   conn_syn__free_unpacked
                     (ConnSyn *message,
                      ProtobufCAllocator *allocator);
/* ConnGetPerflowMsg methods */
void   conn_get_perflow_msg__init
                     (ConnGetPerflowMsg         *message);
size_t conn_get_perflow_msg__get_packed_size
                     (const ConnGetPerflowMsg   *message);
size_t conn_get_perflow_msg__pack
                     (const ConnGetPerflowMsg   *message,
                      uint8_t             *out);
size_t conn_get_perflow_msg__pack_to_buffer
                     (const ConnGetPerflowMsg   *message,
                      ProtobufCBuffer     *buffer);
ConnGetPerflowMsg *
       conn_get_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   conn_get_perflow_msg__free_unpacked
                     (ConnGetPerflowMsg *message,
                      ProtobufCAllocator *allocator);
/* ConnGetPerflowAckMsg methods */
void   conn_get_perflow_ack_msg__init
                     (ConnGetPerflowAckMsg         *message);
size_t conn_get_perflow_ack_msg__get_packed_size
                     (const ConnGetPerflowAckMsg   *message);
size_t conn_get_perflow_ack_msg__pack
                     (const ConnGetPerflowAckMsg   *message,
                      uint8_t             *out);
size_t conn_get_perflow_ack_msg__pack_to_buffer
                     (const ConnGetPerflowAckMsg   *message,
                      ProtobufCBuffer     *buffer);
ConnGetPerflowAckMsg *
       conn_get_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   conn_get_perflow_ack_msg__free_unpacked
                     (ConnGetPerflowAckMsg *message,
                      ProtobufCAllocator *allocator);
/* ConnState methods */
void   conn_state__init
                     (ConnState         *message);
size_t conn_state__get_packed_size
                     (const ConnState   *message);
size_t conn_state__pack
                     (const ConnState   *message,
                      uint8_t             *out);
size_t conn_state__pack_to_buffer
                     (const ConnState   *message,
                      ProtobufCBuffer     *buffer);
ConnState *
       conn_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   conn_state__free_unpacked
                     (ConnState *message,
                      ProtobufCAllocator *allocator);
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
/* ConnPutPerflowAckMsg methods */
void   conn_put_perflow_ack_msg__init
                     (ConnPutPerflowAckMsg         *message);
size_t conn_put_perflow_ack_msg__get_packed_size
                     (const ConnPutPerflowAckMsg   *message);
size_t conn_put_perflow_ack_msg__pack
                     (const ConnPutPerflowAckMsg   *message,
                      uint8_t             *out);
size_t conn_put_perflow_ack_msg__pack_to_buffer
                     (const ConnPutPerflowAckMsg   *message,
                      ProtobufCBuffer     *buffer);
ConnPutPerflowAckMsg *
       conn_put_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   conn_put_perflow_ack_msg__free_unpacked
                     (ConnPutPerflowAckMsg *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*MyConnMessage_Closure)
                 (const MyConnMessage *message,
                  void *closure_data);
typedef void (*ConnSyn_Closure)
                 (const ConnSyn *message,
                  void *closure_data);
typedef void (*ConnGetPerflowMsg_Closure)
                 (const ConnGetPerflowMsg *message,
                  void *closure_data);
typedef void (*ConnGetPerflowAckMsg_Closure)
                 (const ConnGetPerflowAckMsg *message,
                  void *closure_data);
typedef void (*ConnState_Closure)
                 (const ConnState *message,
                  void *closure_data);
typedef void (*ConnPutPerflowMsg_Closure)
                 (const ConnPutPerflowMsg *message,
                  void *closure_data);
typedef void (*ConnPutPerflowAckMsg_Closure)
                 (const ConnPutPerflowAckMsg *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor my_conn_message__descriptor;
extern const ProtobufCEnumDescriptor    my_conn_message__data_type__descriptor;
extern const ProtobufCMessageDescriptor conn_syn__descriptor;
extern const ProtobufCMessageDescriptor conn_get_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor conn_get_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor conn_state__descriptor;
extern const ProtobufCMessageDescriptor conn_put_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor conn_put_perflow_ack_msg__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_myConnMessage_2eproto__INCLUDED */