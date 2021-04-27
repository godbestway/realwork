/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: connGetPerflowMsg.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "connGetPerflowMsg.pb-c.h"
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
static const ProtobufCFieldDescriptor conn_get_perflow_msg__field_descriptors[1] =
{
  {
    "key",
    1,
    PROTOBUF_C_LABEL_OPTIONAL,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(ConnGetPerflowMsg, key),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned conn_get_perflow_msg__field_indices_by_name[] = {
  0,   /* field[0] = key */
};
static const ProtobufCIntRange conn_get_perflow_msg__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor conn_get_perflow_msg__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ConnGetPerflowMsg",
  "ConnGetPerflowMsg",
  "ConnGetPerflowMsg",
  "",
  sizeof(ConnGetPerflowMsg),
  1,
  conn_get_perflow_msg__field_descriptors,
  conn_get_perflow_msg__field_indices_by_name,
  1,  conn_get_perflow_msg__number_ranges,
  (ProtobufCMessageInit) conn_get_perflow_msg__init,
  NULL,NULL,NULL    /* reserved[123] */
};
