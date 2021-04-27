/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: myConnMessage.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "myConnMessage.pb-c.h"
void   my_conn_message__init
                     (MyConnMessage         *message)
{
  static const MyConnMessage init_value = MY_CONN_MESSAGE__INIT;
  *message = init_value;
}
size_t my_conn_message__get_packed_size
                     (const MyConnMessage *message)
{
  assert(message->base.descriptor == &my_conn_message__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t my_conn_message__pack
                     (const MyConnMessage *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &my_conn_message__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t my_conn_message__pack_to_buffer
                     (const MyConnMessage *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &my_conn_message__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
MyConnMessage *
       my_conn_message__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (MyConnMessage *)
     protobuf_c_message_unpack (&my_conn_message__descriptor,
                                allocator, len, data);
}
void   my_conn_message__free_unpacked
                     (MyConnMessage *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &my_conn_message__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   conn_syn__init
                     (ConnSyn         *message)
{
  static const ConnSyn init_value = CONN_SYN__INIT;
  *message = init_value;
}
size_t conn_syn__get_packed_size
                     (const ConnSyn *message)
{
  assert(message->base.descriptor == &conn_syn__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t conn_syn__pack
                     (const ConnSyn *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &conn_syn__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t conn_syn__pack_to_buffer
                     (const ConnSyn *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &conn_syn__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnSyn *
       conn_syn__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnSyn *)
     protobuf_c_message_unpack (&conn_syn__descriptor,
                                allocator, len, data);
}
void   conn_syn__free_unpacked
                     (ConnSyn *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &conn_syn__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   conn_get_perflow_msg__init
                     (ConnGetPerflowMsg         *message)
{
  static const ConnGetPerflowMsg init_value = CONN_GET_PERFLOW_MSG__INIT;
  *message = init_value;
}
size_t conn_get_perflow_msg__get_packed_size
                     (const ConnGetPerflowMsg *message)
{
  assert(message->base.descriptor == &conn_get_perflow_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t conn_get_perflow_msg__pack
                     (const ConnGetPerflowMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &conn_get_perflow_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t conn_get_perflow_msg__pack_to_buffer
                     (const ConnGetPerflowMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &conn_get_perflow_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnGetPerflowMsg *
       conn_get_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnGetPerflowMsg *)
     protobuf_c_message_unpack (&conn_get_perflow_msg__descriptor,
                                allocator, len, data);
}
void   conn_get_perflow_msg__free_unpacked
                     (ConnGetPerflowMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &conn_get_perflow_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   conn_get_perflow_ack_msg__init
                     (ConnGetPerflowAckMsg         *message)
{
  static const ConnGetPerflowAckMsg init_value = CONN_GET_PERFLOW_ACK_MSG__INIT;
  *message = init_value;
}
size_t conn_get_perflow_ack_msg__get_packed_size
                     (const ConnGetPerflowAckMsg *message)
{
  assert(message->base.descriptor == &conn_get_perflow_ack_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t conn_get_perflow_ack_msg__pack
                     (const ConnGetPerflowAckMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &conn_get_perflow_ack_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t conn_get_perflow_ack_msg__pack_to_buffer
                     (const ConnGetPerflowAckMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &conn_get_perflow_ack_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnGetPerflowAckMsg *
       conn_get_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnGetPerflowAckMsg *)
     protobuf_c_message_unpack (&conn_get_perflow_ack_msg__descriptor,
                                allocator, len, data);
}
void   conn_get_perflow_ack_msg__free_unpacked
                     (ConnGetPerflowAckMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &conn_get_perflow_ack_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   conn_state__init
                     (ConnState         *message)
{
  static const ConnState init_value = CONN_STATE__INIT;
  *message = init_value;
}
size_t conn_state__get_packed_size
                     (const ConnState *message)
{
  assert(message->base.descriptor == &conn_state__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t conn_state__pack
                     (const ConnState *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &conn_state__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t conn_state__pack_to_buffer
                     (const ConnState *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &conn_state__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnState *
       conn_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnState *)
     protobuf_c_message_unpack (&conn_state__descriptor,
                                allocator, len, data);
}
void   conn_state__free_unpacked
                     (ConnState *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &conn_state__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   conn_put_perflow_msg__init
                     (ConnPutPerflowMsg         *message)
{
  static const ConnPutPerflowMsg init_value = CONN_PUT_PERFLOW_MSG__INIT;
  *message = init_value;
}
size_t conn_put_perflow_msg__get_packed_size
                     (const ConnPutPerflowMsg *message)
{
  assert(message->base.descriptor == &conn_put_perflow_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t conn_put_perflow_msg__pack
                     (const ConnPutPerflowMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &conn_put_perflow_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t conn_put_perflow_msg__pack_to_buffer
                     (const ConnPutPerflowMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &conn_put_perflow_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnPutPerflowMsg *
       conn_put_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnPutPerflowMsg *)
     protobuf_c_message_unpack (&conn_put_perflow_msg__descriptor,
                                allocator, len, data);
}
void   conn_put_perflow_msg__free_unpacked
                     (ConnPutPerflowMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &conn_put_perflow_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   conn_put_perflow_ack_msg__init
                     (ConnPutPerflowAckMsg         *message)
{
  static const ConnPutPerflowAckMsg init_value = CONN_PUT_PERFLOW_ACK_MSG__INIT;
  *message = init_value;
}
size_t conn_put_perflow_ack_msg__get_packed_size
                     (const ConnPutPerflowAckMsg *message)
{
  assert(message->base.descriptor == &conn_put_perflow_ack_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t conn_put_perflow_ack_msg__pack
                     (const ConnPutPerflowAckMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &conn_put_perflow_ack_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t conn_put_perflow_ack_msg__pack_to_buffer
                     (const ConnPutPerflowAckMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &conn_put_perflow_ack_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ConnPutPerflowAckMsg *
       conn_put_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ConnPutPerflowAckMsg *)
     protobuf_c_message_unpack (&conn_put_perflow_ack_msg__descriptor,
                                allocator, len, data);
}
void   conn_put_perflow_ack_msg__free_unpacked
                     (ConnPutPerflowAckMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &conn_put_perflow_ack_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   unlock_msg__init
                     (UnlockMsg         *message)
{
  static const UnlockMsg init_value = UNLOCK_MSG__INIT;
  *message = init_value;
}
size_t unlock_msg__get_packed_size
                     (const UnlockMsg *message)
{
  assert(message->base.descriptor == &unlock_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t unlock_msg__pack
                     (const UnlockMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &unlock_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t unlock_msg__pack_to_buffer
                     (const UnlockMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &unlock_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
UnlockMsg *
       unlock_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (UnlockMsg *)
     protobuf_c_message_unpack (&unlock_msg__descriptor,
                                allocator, len, data);
}
void   unlock_msg__free_unpacked
                     (UnlockMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &unlock_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCEnumValue my_conn_message__data_type__enum_values_by_number[7] =
{
  { "SynType", "MY_CONN_MESSAGE__DATA_TYPE__SynType", 1 },
  { "ConnGetPerflowMsgType", "MY_CONN_MESSAGE__DATA_TYPE__ConnGetPerflowMsgType", 2 },
  { "ConnGetPerflowAckMsgType", "MY_CONN_MESSAGE__DATA_TYPE__ConnGetPerflowAckMsgType", 3 },
  { "ConnStateType", "MY_CONN_MESSAGE__DATA_TYPE__ConnStateType", 4 },
  { "ConnPutPerflowMsgType", "MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowMsgType", 5 },
  { "ConnPutPerflowAckMsgType", "MY_CONN_MESSAGE__DATA_TYPE__ConnPutPerflowAckMsgType", 6 },
  { "UnlockMsgType", "MY_CONN_MESSAGE__DATA_TYPE__UnlockMsgType", 7 },
};
static const ProtobufCIntRange my_conn_message__data_type__value_ranges[] = {
{1, 0},{0, 7}
};
static const ProtobufCEnumValueIndex my_conn_message__data_type__enum_values_by_name[7] =
{
  { "ConnGetPerflowAckMsgType", 2 },
  { "ConnGetPerflowMsgType", 1 },
  { "ConnPutPerflowAckMsgType", 5 },
  { "ConnPutPerflowMsgType", 4 },
  { "ConnStateType", 3 },
  { "SynType", 0 },
  { "UnlockMsgType", 6 },
};
const ProtobufCEnumDescriptor my_conn_message__data_type__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "MyConnMessage.DataType",
  "DataType",
  "MyConnMessage__DataType",
  "",
  7,
  my_conn_message__data_type__enum_values_by_number,
  7,
  my_conn_message__data_type__enum_values_by_name,
  1,
  my_conn_message__data_type__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor my_conn_message__field_descriptors[8] =
{
  {
    "data_type",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(MyConnMessage, data_type),
    &my_conn_message__data_type__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "connsyn",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, connsyn),
    &conn_syn__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "connGetPerflowMsg",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, conngetperflowmsg),
    &conn_get_perflow_msg__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "connGetPerflowAckMsg",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, conngetperflowackmsg),
    &conn_get_perflow_ack_msg__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "connState",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, connstate),
    &conn_state__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "connPutPerflowMsg",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, connputperflowmsg),
    &conn_put_perflow_msg__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "connPutPerflowAckMsg",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, connputperflowackmsg),
    &conn_put_perflow_ack_msg__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "unlockMsg",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(MyConnMessage, message_case),
    offsetof(MyConnMessage, unlockmsg),
    &unlock_msg__descriptor,
    NULL,
    0 | PROTOBUF_C_FIELD_FLAG_ONEOF,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned my_conn_message__field_indices_by_name[] = {
  3,   /* field[3] = connGetPerflowAckMsg */
  2,   /* field[2] = connGetPerflowMsg */
  6,   /* field[6] = connPutPerflowAckMsg */
  5,   /* field[5] = connPutPerflowMsg */
  4,   /* field[4] = connState */
  1,   /* field[1] = connsyn */
  0,   /* field[0] = data_type */
  7,   /* field[7] = unlockMsg */
};
static const ProtobufCIntRange my_conn_message__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 8 }
};
const ProtobufCMessageDescriptor my_conn_message__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "MyConnMessage",
  "MyConnMessage",
  "MyConnMessage",
  "",
  sizeof(MyConnMessage),
  8,
  my_conn_message__field_descriptors,
  my_conn_message__field_indices_by_name,
  1,  my_conn_message__number_ranges,
  (ProtobufCMessageInit) my_conn_message__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor conn_syn__field_descriptors[2] =
{
  {
    "host",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ConnSyn, host),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "pid",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnSyn, has_pid),
    offsetof(ConnSyn, pid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_syn__field_indices_by_name[] = {
  0,   /* field[0] = host */
  1,   /* field[1] = pid */
};
static const ProtobufCIntRange conn_syn__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor conn_syn__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnSyn",
  "ConnSyn",
  "ConnSyn",
  "",
  sizeof(ConnSyn),
  2,
  conn_syn__field_descriptors,
  conn_syn__field_indices_by_name,
  1,  conn_syn__number_ranges,
  (ProtobufCMessageInit) conn_syn__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor conn_get_perflow_msg__field_descriptors[3] =
{
  {
    "hw_proto",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnGetPerflowMsg, has_hw_proto),
    offsetof(ConnGetPerflowMsg, hw_proto),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "proto",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnGetPerflowMsg, has_proto),
    offsetof(ConnGetPerflowMsg, proto),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "mode",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnGetPerflowMsg, has_mode),
    offsetof(ConnGetPerflowMsg, mode),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_get_perflow_msg__field_indices_by_name[] = {
  0,   /* field[0] = hw_proto */
  2,   /* field[2] = mode */
  1,   /* field[1] = proto */
};
static const ProtobufCIntRange conn_get_perflow_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor conn_get_perflow_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnGetPerflowMsg",
  "ConnGetPerflowMsg",
  "ConnGetPerflowMsg",
  "",
  sizeof(ConnGetPerflowMsg),
  3,
  conn_get_perflow_msg__field_descriptors,
  conn_get_perflow_msg__field_indices_by_name,
  1,  conn_get_perflow_msg__number_ranges,
  (ProtobufCMessageInit) conn_get_perflow_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor conn_get_perflow_ack_msg__field_descriptors[1] =
{
  {
    "count",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnGetPerflowAckMsg, has_count),
    offsetof(ConnGetPerflowAckMsg, count),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_get_perflow_ack_msg__field_indices_by_name[] = {
  0,   /* field[0] = count */
};
static const ProtobufCIntRange conn_get_perflow_ack_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor conn_get_perflow_ack_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnGetPerflowAckMsg",
  "ConnGetPerflowAckMsg",
  "ConnGetPerflowAckMsg",
  "",
  sizeof(ConnGetPerflowAckMsg),
  1,
  conn_get_perflow_ack_msg__field_descriptors,
  conn_get_perflow_ack_msg__field_indices_by_name,
  1,  conn_get_perflow_ack_msg__number_ranges,
  (ProtobufCMessageInit) conn_get_perflow_ack_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor conn_state__field_descriptors[11] =
{
  {
    "ether_dst",
    1,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, n_ether_dst),
    offsetof(ConnState, ether_dst),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "ether_src",
    2,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, n_ether_src),
    offsetof(ConnState, ether_src),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "s_ip",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, has_s_ip),
    offsetof(ConnState, s_ip),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "d_ip",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, has_d_ip),
    offsetof(ConnState, d_ip),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "s_port",
    5,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, has_s_port),
    offsetof(ConnState, s_port),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "d_port",
    6,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, has_d_port),
    offsetof(ConnState, d_port),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "hw_proto",
    7,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnState, has_hw_proto),
    offsetof(ConnState, hw_proto),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "proto",
    8,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_INT32,
    offsetof(ConnState, has_proto),
    offsetof(ConnState, proto),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cxid",
    9,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED64,
    offsetof(ConnState, has_cxid),
    offsetof(ConnState, cxid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "hash",
    10,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, has_hash),
    offsetof(ConnState, hash),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "nat_hash",
    11,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnState, has_nat_hash),
    offsetof(ConnState, nat_hash),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_state__field_indices_by_name[] = {
  8,   /* field[8] = cxid */
  3,   /* field[3] = d_ip */
  5,   /* field[5] = d_port */
  0,   /* field[0] = ether_dst */
  1,   /* field[1] = ether_src */
  9,   /* field[9] = hash */
  6,   /* field[6] = hw_proto */
  10,   /* field[10] = nat_hash */
  7,   /* field[7] = proto */
  2,   /* field[2] = s_ip */
  4,   /* field[4] = s_port */
};
static const ProtobufCIntRange conn_state__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 11 }
};
const ProtobufCMessageDescriptor conn_state__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnState",
  "ConnState",
  "ConnState",
  "",
  sizeof(ConnState),
  11,
  conn_state__field_descriptors,
  conn_state__field_indices_by_name,
  1,  conn_state__number_ranges,
  (ProtobufCMessageInit) conn_state__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor conn_put_perflow_msg__field_descriptors[1] =
{
  {
    "state",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(ConnPutPerflowMsg, state),
    &conn_state__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_put_perflow_msg__field_indices_by_name[] = {
  0,   /* field[0] = state */
};
static const ProtobufCIntRange conn_put_perflow_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor conn_put_perflow_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnPutPerflowMsg",
  "ConnPutPerflowMsg",
  "ConnPutPerflowMsg",
  "",
  sizeof(ConnPutPerflowMsg),
  1,
  conn_put_perflow_msg__field_descriptors,
  conn_put_perflow_msg__field_indices_by_name,
  1,  conn_put_perflow_msg__number_ranges,
  (ProtobufCMessageInit) conn_put_perflow_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue conn_put_perflow_ack_msg__fw_state__enum_values_by_number[2] =
{
  { "OPEN", "CONN_PUT_PERFLOW_ACK_MSG__FW_STATE__OPEN", 1 },
  { "CLOSED", "CONN_PUT_PERFLOW_ACK_MSG__FW_STATE__CLOSED", 2 },
};
static const ProtobufCIntRange conn_put_perflow_ack_msg__fw_state__value_ranges[] = {
{1, 0},{0, 2}
};
static const ProtobufCEnumValueIndex conn_put_perflow_ack_msg__fw_state__enum_values_by_name[2] =
{
  { "CLOSED", 1 },
  { "OPEN", 0 },
};
const ProtobufCEnumDescriptor conn_put_perflow_ack_msg__fw_state__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "ConnPutPerflowAckMsg.fwState",
  "fwState",
  "ConnPutPerflowAckMsg__FwState",
  "",
  2,
  conn_put_perflow_ack_msg__fw_state__enum_values_by_number,
  2,
  conn_put_perflow_ack_msg__fw_state__enum_values_by_name,
  1,
  conn_put_perflow_ack_msg__fw_state__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
static const ProtobufCFieldDescriptor conn_put_perflow_ack_msg__field_descriptors[4] =
{
  {
    "hash",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnPutPerflowAckMsg, has_hash),
    offsetof(ConnPutPerflowAckMsg, hash),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "cxid",
    2,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnPutPerflowAckMsg, has_cxid),
    offsetof(ConnPutPerflowAckMsg, cxid),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "fwstate",
    3,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_ENUM,
    offsetof(ConnPutPerflowAckMsg, has_fwstate),
    offsetof(ConnPutPerflowAckMsg, fwstate),
    &conn_put_perflow_ack_msg__fw_state__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "nat_hash",
    4,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_FIXED32,
    offsetof(ConnPutPerflowAckMsg, has_nat_hash),
    offsetof(ConnPutPerflowAckMsg, nat_hash),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_put_perflow_ack_msg__field_indices_by_name[] = {
  1,   /* field[1] = cxid */
  2,   /* field[2] = fwstate */
  0,   /* field[0] = hash */
  3,   /* field[3] = nat_hash */
};
static const ProtobufCIntRange conn_put_perflow_ack_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 4 }
};
const ProtobufCMessageDescriptor conn_put_perflow_ack_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnPutPerflowAckMsg",
  "ConnPutPerflowAckMsg",
  "ConnPutPerflowAckMsg",
  "",
  sizeof(ConnPutPerflowAckMsg),
  4,
  conn_put_perflow_ack_msg__field_descriptors,
  conn_put_perflow_ack_msg__field_indices_by_name,
  1,  conn_put_perflow_ack_msg__number_ranges,
  (ProtobufCMessageInit) conn_put_perflow_ack_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
#define unlock_msg__field_descriptors NULL
#define unlock_msg__field_indices_by_name NULL
#define unlock_msg__number_ranges NULL
const ProtobufCMessageDescriptor unlock_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "UnlockMsg",
  "UnlockMsg",
  "UnlockMsg",
  "",
  sizeof(UnlockMsg),
  0,
  unlock_msg__field_descriptors,
  unlock_msg__field_indices_by_name,
  0,  unlock_msg__number_ranges,
  (ProtobufCMessageInit) unlock_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
