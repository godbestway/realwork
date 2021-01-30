/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: myMessage.proto */

#ifndef PROTOBUF_C_myMessage_2eproto__INCLUDED
#define PROTOBUF_C_myMessage_2eproto__INCLUDED

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
typedef struct _ConnGetPerflowMsg ConnGetPerflowMsg;
typedef struct _ConnGetPerflowAckMsg ConnGetPerflowAckMsg;
typedef struct _ConnState ConnState;
typedef struct _ConnPutPerflowMsg ConnPutPerflowMsg;
typedef struct _ConnPutPerflowAckMsg ConnPutPerflowAckMsg;
typedef struct _ActionGetPerflowMsg ActionGetPerflowMsg;
typedef struct _ActionGetPerflowAckMsg ActionGetPerflowAckMsg;
typedef struct _ActionState ActionState;
typedef struct _ActionPutPerflowMsg ActionPutPerflowMsg;
typedef struct _ActionPutPerflowAckMsg ActionPutPerflowAckMsg;


/* --- enums --- */

typedef enum _MyMessage__DataType {
  MY_MESSAGE__DATA_TYPE__SynType = 1,
  MY_MESSAGE__DATA_TYPE__PersonType = 2,
  MY_MESSAGE__DATA_TYPE__ConnGetPerflowMsgType = 3,
  MY_MESSAGE__DATA_TYPE__ConnGetPerflowAckMsgType = 4,
  MY_MESSAGE__DATA_TYPE__ConnStateType = 5,
  MY_MESSAGE__DATA_TYPE__ConnPutPerflowMsgType = 6,
  MY_MESSAGE__DATA_TYPE__ConnPutPerflowAckMsgType = 7,
  MY_MESSAGE__DATA_TYPE__ActionGetPerflowMsgType = 8,
  MY_MESSAGE__DATA_TYPE__ActionGetPerflowAckMsgType = 9,
  MY_MESSAGE__DATA_TYPE__ActionStateType = 10,
  MY_MESSAGE__DATA_TYPE__ActionPutPerflowMsgType = 11,
  MY_MESSAGE__DATA_TYPE__ActionPutPerflowAckMsgType = 12
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_MESSAGE__DATA_TYPE)
} MyMessage__DataType;

/* --- messages --- */

typedef enum {
  MY_MESSAGE__MESSAGE__NOT_SET = 0,
  MY_MESSAGE__MESSAGE_SYN = 2,
  MY_MESSAGE__MESSAGE_PERSON = 3,
  MY_MESSAGE__MESSAGE_CONN_GET_PERFLOW_MSG = 4,
  MY_MESSAGE__MESSAGE_CONN_GET_PERFLOW_ACK_MSG = 5,
  MY_MESSAGE__MESSAGE_CONN_STATE = 6,
  MY_MESSAGE__MESSAGE_CONN_PUT_PERFLOW_MSG = 7,
  MY_MESSAGE__MESSAGE_CONN_PUT_PERFLOW_ACK_MSG = 8,
  MY_MESSAGE__MESSAGE_ACTION_GET_PERFLOW_MSG = 9,
  MY_MESSAGE__MESSAGE_ACTION_GET_PERFLOW_ACK_MSG = 10,
  MY_MESSAGE__MESSAGE_ACTION_STATE = 11,
  MY_MESSAGE__MESSAGE_ACTION_PUT_PERFLOW_MSG = 12,
  MY_MESSAGE__MESSAGE_ACTION_PUT_PERFLOW_ACK_MSG = 13
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
    ConnGetPerflowMsg *conngetperflowmsg;
    ConnGetPerflowAckMsg *conngetperflowackmsg;
    ConnState *connstate;
    ConnPutPerflowMsg *connputperflowmsg;
    ConnPutPerflowAckMsg *connputperflowackmsg;
    ActionGetPerflowMsg *actiongetperflowmsg;
    ActionGetPerflowAckMsg *actiongetperflowackmsg;
    ActionState *actionstate;
    ActionPutPerflowMsg *actionputperflowmsg;
    ActionPutPerflowAckMsg *actionputperflowackmsg;
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


struct  _ConnGetPerflowMsg
{
  ProtobufCMessage base;
  char *key;
};
#define CONN_GET_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_get_perflow_msg__descriptor) \
    , NULL }


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
  protobuf_c_boolean has_data;
  int32_t data;
  protobuf_c_boolean has_cxid;
  uint64_t cxid;
  protobuf_c_boolean has_hash;
  int32_t hash;
};
#define CONN_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&conn_state__descriptor) \
    , 0, 0, 0, 0, 0, 0 }


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


struct  _ActionGetPerflowMsg
{
  ProtobufCMessage base;
  char *key;
};
#define ACTION_GET_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_get_perflow_msg__descriptor) \
    , NULL }


struct  _ActionGetPerflowAckMsg
{
  ProtobufCMessage base;
  protobuf_c_boolean has_count;
  uint32_t count;
};
#define ACTION_GET_PERFLOW_ACK_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_get_perflow_ack_msg__descriptor) \
    , 0, 0 }


struct  _ActionState
{
  ProtobufCMessage base;
  protobuf_c_boolean has_data;
  int32_t data;
  protobuf_c_boolean has_cxid;
  uint64_t cxid;
  protobuf_c_boolean has_hash;
  int32_t hash;
};
#define ACTION_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_state__descriptor) \
    , 0, 0, 0, 0, 0, 0 }


struct  _ActionPutPerflowMsg
{
  ProtobufCMessage base;
  ActionState *state;
};
#define ACTION_PUT_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_put_perflow_msg__descriptor) \
    , NULL }


struct  _ActionPutPerflowAckMsg
{
  ProtobufCMessage base;
  protobuf_c_boolean has_hash;
  uint32_t hash;
  protobuf_c_boolean has_cxid;
  uint32_t cxid;
};
#define ACTION_PUT_PERFLOW_ACK_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_put_perflow_ack_msg__descriptor) \
    , 0, 0, 0, 0 }


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
/* ActionGetPerflowAckMsg methods */
void   action_get_perflow_ack_msg__init
                     (ActionGetPerflowAckMsg         *message);
size_t action_get_perflow_ack_msg__get_packed_size
                     (const ActionGetPerflowAckMsg   *message);
size_t action_get_perflow_ack_msg__pack
                     (const ActionGetPerflowAckMsg   *message,
                      uint8_t             *out);
size_t action_get_perflow_ack_msg__pack_to_buffer
                     (const ActionGetPerflowAckMsg   *message,
                      ProtobufCBuffer     *buffer);
ActionGetPerflowAckMsg *
       action_get_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   action_get_perflow_ack_msg__free_unpacked
                     (ActionGetPerflowAckMsg *message,
                      ProtobufCAllocator *allocator);
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
/* ActionPutPerflowMsg methods */
void   action_put_perflow_msg__init
                     (ActionPutPerflowMsg         *message);
size_t action_put_perflow_msg__get_packed_size
                     (const ActionPutPerflowMsg   *message);
size_t action_put_perflow_msg__pack
                     (const ActionPutPerflowMsg   *message,
                      uint8_t             *out);
size_t action_put_perflow_msg__pack_to_buffer
                     (const ActionPutPerflowMsg   *message,
                      ProtobufCBuffer     *buffer);
ActionPutPerflowMsg *
       action_put_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   action_put_perflow_msg__free_unpacked
                     (ActionPutPerflowMsg *message,
                      ProtobufCAllocator *allocator);
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

typedef void (*MyMessage_Closure)
                 (const MyMessage *message,
                  void *closure_data);
typedef void (*Syn_Closure)
                 (const Syn *message,
                  void *closure_data);
typedef void (*Person_Closure)
                 (const Person *message,
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
typedef void (*ActionGetPerflowMsg_Closure)
                 (const ActionGetPerflowMsg *message,
                  void *closure_data);
typedef void (*ActionGetPerflowAckMsg_Closure)
                 (const ActionGetPerflowAckMsg *message,
                  void *closure_data);
typedef void (*ActionState_Closure)
                 (const ActionState *message,
                  void *closure_data);
typedef void (*ActionPutPerflowMsg_Closure)
                 (const ActionPutPerflowMsg *message,
                  void *closure_data);
typedef void (*ActionPutPerflowAckMsg_Closure)
                 (const ActionPutPerflowAckMsg *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor my_message__descriptor;
extern const ProtobufCEnumDescriptor    my_message__data_type__descriptor;
extern const ProtobufCMessageDescriptor syn__descriptor;
extern const ProtobufCMessageDescriptor person__descriptor;
extern const ProtobufCMessageDescriptor conn_get_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor conn_get_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor conn_state__descriptor;
extern const ProtobufCMessageDescriptor conn_put_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor conn_put_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor action_get_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor action_get_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor action_state__descriptor;
extern const ProtobufCMessageDescriptor action_put_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor action_put_perflow_ack_msg__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_myMessage_2eproto__INCLUDED */