/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: ActionState.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "ActionState.pb-c.h"
void   action_state__init
                     (ActionState         *message)
{
  static const ActionState init_value = ACTION_STATE__INIT;
  *message = init_value;
}
size_t action_state__get_packed_size
                     (const ActionState *message)
{
  assert(message->base.descriptor == &action_state__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t action_state__pack
                     (const ActionState *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &action_state__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t action_state__pack_to_buffer
                     (const ActionState *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &action_state__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ActionState *
       action_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ActionState *)
     protobuf_c_message_unpack (&action_state__descriptor,
                                allocator, len, data);
}
void   action_state__free_unpacked
                     (ActionState *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &action_state__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor action_state__field_descriptors[1] =
{
  {
    "data",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(ActionState, data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned action_state__field_indices_by_name[] = {
  0,   /* field[0] = data */
};
static const ProtobufCIntRange action_state__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor action_state__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ActionState",
  "ActionState",
  "ActionState",
  "",
  sizeof(ActionState),
  1,
  action_state__field_descriptors,
  action_state__field_indices_by_name,
  1,  action_state__number_ranges,
  (ProtobufCMessageInit) action_state__init,
  NULL,NULL,NULL    /* reserved[123] */
};
