/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: actionPutPerflowAckMsg.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "actionPutPerflowAckMsg.pb-c.h"
void   action_put_perflow_ack_msg__init
                     (ActionPutPerflowAckMsg         *message)
{
  static const ActionPutPerflowAckMsg init_value = ACTION_PUT_PERFLOW_ACK_MSG__INIT;
  *message = init_value;
}
size_t action_put_perflow_ack_msg__get_packed_size
                     (const ActionPutPerflowAckMsg *message)
{
  assert(message->base.descriptor == &action_put_perflow_ack_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t action_put_perflow_ack_msg__pack
                     (const ActionPutPerflowAckMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &action_put_perflow_ack_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t action_put_perflow_ack_msg__pack_to_buffer
                     (const ActionPutPerflowAckMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &action_put_perflow_ack_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ActionPutPerflowAckMsg *
       action_put_perflow_ack_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ActionPutPerflowAckMsg *)
     protobuf_c_message_unpack (&action_put_perflow_ack_msg__descriptor,
                                allocator, len, data);
}
void   action_put_perflow_ack_msg__free_unpacked
                     (ActionPutPerflowAckMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &action_put_perflow_ack_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor action_put_perflow_ack_msg__field_descriptors[1] =
{
  {
    "hash",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FIXED32,
    0,   /* quantifier_offset */
    offsetof(ActionPutPerflowAckMsg, hash),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned action_put_perflow_ack_msg__field_indices_by_name[] = {
  0,   /* field[0] = hash */
};
static const ProtobufCIntRange action_put_perflow_ack_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor action_put_perflow_ack_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ActionPutPerflowAckMsg",
  "ActionPutPerflowAckMsg",
  "ActionPutPerflowAckMsg",
  "",
  sizeof(ActionPutPerflowAckMsg),
  1,
  action_put_perflow_ack_msg__field_descriptors,
  action_put_perflow_ack_msg__field_indices_by_name,
  1,  action_put_perflow_ack_msg__number_ranges,
  (ProtobufCMessageInit) action_put_perflow_ack_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};