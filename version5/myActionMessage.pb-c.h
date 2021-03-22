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
typedef struct _Asset Asset;
typedef struct _ServAsset ServAsset;
typedef struct _OsAsset OsAsset;
typedef struct _Bstring Bstring;


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
typedef enum _ActionState__FwState {
  ACTION_STATE__FW_STATE__OPEN = 1,
  ACTION_STATE__FW_STATE__CLOSED = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(ACTION_STATE__FW_STATE)
} ActionState__FwState;

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
  protobuf_c_boolean has_start_time;
  uint64_t start_time;
  protobuf_c_boolean has_last_pkt_time;
  uint64_t last_pkt_time;
  protobuf_c_boolean has_cxid;
  uint64_t cxid;
  protobuf_c_boolean has_reversed;
  uint32_t reversed;
  protobuf_c_boolean has_af;
  uint32_t af;
  protobuf_c_boolean has_s_total_pkts;
  uint64_t s_total_pkts;
  protobuf_c_boolean has_s_total_bytes;
  uint64_t s_total_bytes;
  protobuf_c_boolean has_d_total_pkts;
  uint64_t d_total_pkts;
  protobuf_c_boolean has_d_total_bytes;
  uint64_t d_total_bytes;
  protobuf_c_boolean has_s_tcpflags;
  uint32_t s_tcpflags;
  protobuf_c_boolean has_pad;
  uint32_t pad;
  protobuf_c_boolean has_d_tcpflags;
  uint32_t d_tcpflags;
  protobuf_c_boolean has_check;
  uint32_t check;
  protobuf_c_boolean has_hash;
  uint32_t hash;
  Asset *c_asset;
  Asset *s_asset;
  protobuf_c_boolean has_fwstate;
  ActionState__FwState fwstate;
  protobuf_c_boolean has_external_ip;
  uint32_t external_ip;
  protobuf_c_boolean has_external_port;
  uint32_t external_port;
  protobuf_c_boolean has_nat_hash;
  uint32_t nat_hash;
};
#define ACTION_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&action_state__descriptor) \
    , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, ACTION_STATE__FW_STATE__OPEN, 0, 0, 0, 0, 0, 0 }


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


struct  _Asset
{
  ProtobufCMessage base;
  protobuf_c_boolean has_first_seen;
  uint64_t first_seen;
  protobuf_c_boolean has_last_seen;
  uint64_t last_seen;
  protobuf_c_boolean has_i_attempts;
  uint32_t i_attempts;
  protobuf_c_boolean has_af;
  uint32_t af;
  protobuf_c_boolean has_vlan;
  uint32_t vlan;
  protobuf_c_boolean has_s_ip;
  uint32_t s_ip;
  ServAsset *services;
  OsAsset *os;
};
#define ASSET__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&asset__descriptor) \
    , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL }


struct  _ServAsset
{
  ProtobufCMessage base;
  protobuf_c_boolean has_first_seen;
  uint64_t first_seen;
  protobuf_c_boolean has_last_seen;
  uint64_t last_seen;
  protobuf_c_boolean has_i_attempts;
  uint32_t i_attempts;
  protobuf_c_boolean has_proto;
  uint32_t proto;
  protobuf_c_boolean has_port;
  uint32_t port;
  protobuf_c_boolean has_ttl;
  uint32_t ttl;
  Bstring *bservice;
  Bstring *bapplication;
  protobuf_c_boolean has_role;
  uint32_t role;
  protobuf_c_boolean has_unknown;
  uint32_t unknown;
};
#define SERV_ASSET__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&serv_asset__descriptor) \
    , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0, 0 }


struct  _OsAsset
{
  ProtobufCMessage base;
  protobuf_c_boolean has_first_seen;
  uint64_t first_seen;
  protobuf_c_boolean has_last_seen;
  uint64_t last_seen;
  protobuf_c_boolean has_i_attempts;
  uint32_t i_attempts;
  Bstring *bvendor;
  Bstring *bos;
  protobuf_c_boolean has_detection;
  uint32_t detection;
  Bstring *raw_fp;
  Bstring *matched_fp;
  char *match_os;
  char *match_desc;
  protobuf_c_boolean has_port;
  uint32_t port;
  protobuf_c_boolean has_mtu;
  uint32_t mtu;
  protobuf_c_boolean has_ttl;
  uint32_t ttl;
  protobuf_c_boolean has_uptime;
  uint32_t uptime;
};
#define OS_ASSET__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&os_asset__descriptor) \
    , 0, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0 }


struct  _Bstring
{
  ProtobufCMessage base;
  protobuf_c_boolean has_mlen;
  uint32_t mlen;
  protobuf_c_boolean has_slen;
  uint32_t slen;
  char *data;
};
#define BSTRING__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&bstring__descriptor) \
    , 0, 0, 0, 0, NULL }


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
/* Asset methods */
void   asset__init
                     (Asset         *message);
size_t asset__get_packed_size
                     (const Asset   *message);
size_t asset__pack
                     (const Asset   *message,
                      uint8_t             *out);
size_t asset__pack_to_buffer
                     (const Asset   *message,
                      ProtobufCBuffer     *buffer);
Asset *
       asset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   asset__free_unpacked
                     (Asset *message,
                      ProtobufCAllocator *allocator);
/* ServAsset methods */
void   serv_asset__init
                     (ServAsset         *message);
size_t serv_asset__get_packed_size
                     (const ServAsset   *message);
size_t serv_asset__pack
                     (const ServAsset   *message,
                      uint8_t             *out);
size_t serv_asset__pack_to_buffer
                     (const ServAsset   *message,
                      ProtobufCBuffer     *buffer);
ServAsset *
       serv_asset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   serv_asset__free_unpacked
                     (ServAsset *message,
                      ProtobufCAllocator *allocator);
/* OsAsset methods */
void   os_asset__init
                     (OsAsset         *message);
size_t os_asset__get_packed_size
                     (const OsAsset   *message);
size_t os_asset__pack
                     (const OsAsset   *message,
                      uint8_t             *out);
size_t os_asset__pack_to_buffer
                     (const OsAsset   *message,
                      ProtobufCBuffer     *buffer);
OsAsset *
       os_asset__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   os_asset__free_unpacked
                     (OsAsset *message,
                      ProtobufCAllocator *allocator);
/* Bstring methods */
void   bstring__init
                     (Bstring         *message);
size_t bstring__get_packed_size
                     (const Bstring   *message);
size_t bstring__pack
                     (const Bstring   *message,
                      uint8_t             *out);
size_t bstring__pack_to_buffer
                     (const Bstring   *message,
                      ProtobufCBuffer     *buffer);
Bstring *
       bstring__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   bstring__free_unpacked
                     (Bstring *message,
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
typedef void (*Asset_Closure)
                 (const Asset *message,
                  void *closure_data);
typedef void (*ServAsset_Closure)
                 (const ServAsset *message,
                  void *closure_data);
typedef void (*OsAsset_Closure)
                 (const OsAsset *message,
                  void *closure_data);
typedef void (*Bstring_Closure)
                 (const Bstring *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor my_action_message__descriptor;
extern const ProtobufCEnumDescriptor    my_action_message__data_type__descriptor;
extern const ProtobufCMessageDescriptor action_syn__descriptor;
extern const ProtobufCMessageDescriptor action_get_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor action_get_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor action_state__descriptor;
extern const ProtobufCEnumDescriptor    action_state__fw_state__descriptor;
extern const ProtobufCMessageDescriptor action_put_perflow_msg__descriptor;
extern const ProtobufCMessageDescriptor action_put_perflow_ack_msg__descriptor;
extern const ProtobufCMessageDescriptor asset__descriptor;
extern const ProtobufCMessageDescriptor serv_asset__descriptor;
extern const ProtobufCMessageDescriptor os_asset__descriptor;
extern const ProtobufCMessageDescriptor bstring__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_myActionMessage_2eproto__INCLUDED */
