/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: actionGetPerflowMsg.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "actionGetPerflowMsg.pb-c.h"
void   action_get_perflow_msg__init
                     (ActionGetPerflowMsg         *message)
{
  static const ActionGetPerflowMsg init_value = ACTION_GET_PERFLOW_MSG__INIT;
  *message = init_value;
}
size_t action_get_perflow_msg__get_packed_size
                     (const ActionGetPerflowMsg *message)
{
  assert(message->base.descriptor == &action_get_perflow_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t action_get_perflow_msg__pack
                     (const ActionGetPerflowMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &action_get_perflow_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t action_get_perflow_msg__pack_to_buffer
                     (const ActionGetPerflowMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &action_get_perflow_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ActionGetPerflowMsg *
       action_get_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ActionGetPerflowMsg *)
     protobuf_c_message_unpack (&action_get_perflow_msg__descriptor,
                                allocator, len, data);
}
void   action_get_perflow_msg__free_unpacked
                     (ActionGetPerflowMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &action_get_perflow_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor action_get_perflow_msg__field_descriptors[1] =
{
  {
    "key",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ActionGetPerflowMsg, key),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned action_get_perflow_msg__field_indices_by_name[] = {
  0,   /* field[0] = key */
};
static const ProtobufCIntRange action_get_perflow_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor action_get_perflow_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ActionGetPerflowMsg",
  "ActionGetPerflowMsg",
  "ActionGetPerflowMsg",
  "",
  sizeof(ActionGetPerflowMsg),
  1,
  action_get_perflow_msg__field_descriptors,
  action_get_perflow_msg__field_indices_by_name,
  1,  action_get_perflow_msg__number_ranges,
  (ProtobufCMessageInit) action_get_perflow_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};