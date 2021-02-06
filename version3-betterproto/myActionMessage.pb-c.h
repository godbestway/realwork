/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: myActionMessage.proto */

#ifndef PROTOBUF_C_myActionMessage_2eproto__INCLUDED
#define PROTOBUF_C_myActionMessage_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1000000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003003 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _MyActionMessage MyActionMessage;
typedef struct _ActionSyn ActionSyn;
typedef struct _ActionGetPerflowMsg ActionGetPerflowMsg;
typedef struct _ActionGetPerflowAckMsg ActionGetPerflowAckMsg;
typedef struct _ActionState ActionState;
typedef struct _ActionPutPerflowMsg ActionPutPerflowMsg;
typedef struct _ActionPutPerflowAckMsg ActionPutPerflowAckMsg;


/* --- enums --- */

typedef enum _MyActionMessage__DataType {
  MY_ACTION_MESSAGE__DATA_TYPE__SynType = 1,
  MY_ACTION_MESSAGE__DATA_TYPE__ActionGetPerflowMsgType = 2,
  MY_ACTION_MESSAGE__DATA_TYPE__ActionGetPerflowAckMsgType = 3,
  MY_ACTION_MESSAGE__DATA_TYPE__ActionStateType = 4,
  MY_ACTION_MESSAGE__DATA_TYPE__ActionPutPerflowMsgType = 5,
  MY_ACTION_MESSAGE__DATA_TYPE__ActionPutPerflowAckMsgType = 6
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_ACTION_MESSAGE__DATA_TYPE)
} MyActionMessage__DataType;

/* --- messages --- */

typedef enum {
  MY_ACTION_MESSAGE__MESSAGE__NOT_SET = 0,
  MY_ACTION_MESSAGE__MESSAGE_ACTIONSYN = 2,
  MY_ACTION_MESSAGE__MESSAGE_ACTION_GET_PERFLOW_MSG = 3,
  MY_ACTION_MESSAGE__MESSAGE_ACTION_GET_PERFLOW_ACK_MSG = 4,
  MY_ACTION_MESSAGE__MESSAGE_ACTION_STATE = 5,
  MY_ACTION_MESSAGE__MESSAGE_ACTION_PUT_PERFLOW_MSG = 6,
  MY_ACTION_MESSAGE__MESSAGE_ACTION_PUT_PERFLOW_ACK_MSG = 7
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(MY_ACTION_MESSAGE__MESSAGE)
} MyActionMessage__MessageCase;

struct  _MyActionMessage
{
  ProtobufCMessage base;
  MyActionMessage__DataType data_type;
  MyActionMessage__MessageCase message_case;
  union {
    ActionSyn *actionsyn;
    ActionGetPerflowMsg *actiongetperflowmsg;
    ActionGetPerflowAckMsg *actiongetperflowackmsg;
    ActionState *actionstate;
    ActionPutPerflowMsg *actionputperflowmsg;
    ActionPutPerflowAckMsg *actionputperflowackmsg;
  };
};
#define MY_ACTION_MESSAGE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&my_action_message__descriptor) \
    , MY_ACTION_MESSAGE__DATA_TYPE__SynType, MY_ACTION_MESSAGE__MESSAGE__NOT_SET, {0} }


struct  _ActionSyn
{
  ProtobufCMessage base;
  char *host;
  protobuf_c_boolean has_pid;
  uint32_t pid;
};
#define ACTION_SYN__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_syn__descriptor) \
    , NULL, 0, 0 }


struct  _ActionGetPerflowMsg
{
  ProtobufCMessage base;
  protobuf_c_boolean has_hw_proto;
  int32_t hw_proto;
  protobuf_c_boolean has_proto;
  int32_t proto;
};
#define ACTION_GET_PERFLOW_MSG__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_get_perflow_msg__descriptor) \
    , 0, 0, 0, 0 }


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


/* MyActionMessage methods */
void   my_action_message__init
                     (MyActionMessage         *message);
size_t my_action_message__get_packed_size
                     (const MyActionMessage   *message);
size_t my_action_message__pack
                     (const MyActionMessage   *message,
                      uint8_t             *out);
size_t my_action_message__pack_to_buffer
                     (const MyActionMessage   *message,
                      ProtobufCBuffer     *buffer);
MyActionMessage *
       my_action_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   my_action_message__free_unpacked
                     (MyActionMessage *message,
                      ProtobufCAllocator *allocator);
/* ActionSyn methods */
void   action_syn__init
                     (ActionSyn         *message);
size_t action_syn__get_packed_size
                     (const ActionSyn   *message);
size_t action_syn__pack
                     (const ActionSyn   *message,
                      uint8_t             *out);
size_t action_syn__pack_to_buffer
                     (const ActionSyn   *message,
                      ProtobufCBuffer     *buffer);
ActionSyn *
       action_syn__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   action_syn__free_unpacked
                     (ActionSyn *message,
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

typedef void (*MyActionMessage_Closure)
                 (const MyActionMessage *message,
                  void *closure_data);
typedef void (*ActionSyn_Closure)
                 (const ActionSyn *message,
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

extern const ProtobufCMessageDescriptor my_action_message__descriptor;
extern const ProtobufCEnumDescriptor    my_action_message__data_type__descriptor;
extern const ProtobufCMessageDescriptor action_syn__descriptor;
extern const ProtobufCMessageDescriptor action_get_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor action_get_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor action_state__descriptor;
extern const ProtobufCMessageDescriptor action_put_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor action_put_perflow_ack_msg__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_myActionMessage_2eproto__INCLUDED */