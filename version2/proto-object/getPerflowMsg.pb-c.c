/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: getPerflowMsg.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "getPerflowMsg.pb-c.h"
void   get_perflow_msg__init
                     (GetPerflowMsg         *message)
{
  static const GetPerflowMsg init_value = GET_PERFLOW_MSG__INIT;
  *message = init_value;
}
size_t get_perflow_msg__get_packed_size
                     (const GetPerflowMsg *message)
{
  assert(message->base.descriptor == &get_perflow_msg__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t get_perflow_msg__pack
                     (const GetPerflowMsg *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &get_perflow_msg__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t get_perflow_msg__pack_to_buffer
                     (const GetPerflowMsg *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &get_perflow_msg__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
GetPerflowMsg *
       get_perflow_msg__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (GetPerflowMsg *)
     protobuf_c_message_unpack (&get_perflow_msg__descriptor,
                                allocator, len, data);
}
void   get_perflow_msg__free_unpacked
                     (GetPerflowMsg *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &get_perflow_msg__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor get_perflow_msg__field_descriptors[1] =
{
  {
    "key",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(GetPerflowMsg, key),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned get_perflow_msg__field_indices_by_name[] = {
  0,   /* field[0] = key */
};
static const ProtobufCIntRange get_perflow_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor get_perflow_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "GetPerflowMsg",
  "GetPerflowMsg",
  "GetPerflowMsg",
  "",
  sizeof(GetPerflowMsg),
  1,
  get_perflow_msg__field_descriptors,
  get_perflow_msg__field_indices_by_name,
  1,  get_perflow_msg__number_ranges,
  (ProtobufCMessageInit) get_perflow_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
