/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: information.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "information.pb-c.h"
void   information__init
                     (Information         *message)
{
  static const Information init_value = INFORMATION__INIT;
  *message = init_value;
}
size_t information__get_packed_size
                     (const Information *message)
{
  assert(message->base.descriptor == &information__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t information__pack
                     (const Information *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &information__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t information__pack_to_buffer
                     (const Information *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &information__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Information *
       information__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Information *)
     protobuf_c_message_unpack (&information__descriptor,
                                allocator, len, data);
}
void   information__free_unpacked
                     (Information *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &information__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor information__field_descriptors[2] =
{
  {
    "personnum",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FIXED32,
    0,   /* quantifier_offset */
    offsetof(Information, personnum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "content",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Information, content),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned information__field_indices_by_name[] = {
  1,   /* field[1] = content */
  0,   /* field[0] = personnum */
};
static const ProtobufCIntRange information__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 2 }
};
const ProtobufCMessageDescriptor information__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Information",
  "Information",
  "Information",
  "",
  sizeof(Information),
  2,
  information__field_descriptors,
  information__field_indices_by_name,
  1,  information__number_ranges,
  (ProtobufCMessageInit) information__init,
  NULL,NULL,NULL    /* reserved[123] */
};
