/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: bstring.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "bstring.pb-c.h"
void   bstring__init
                     (Bstring         *message)
{
  static const Bstring init_value = BSTRING__INIT;
  *message = init_value;
}
size_t bstring__get_packed_size
                     (const Bstring *message)
{
  assert(message->base.descriptor == &bstring__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t bstring__pack
                     (const Bstring *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &bstring__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t bstring__pack_to_buffer
                     (const Bstring *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &bstring__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Bstring *
       bstring__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Bstring *)
     protobuf_c_message_unpack (&bstring__descriptor,
                                allocator, len, data);
}
void   bstring__free_unpacked
                     (Bstring *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &bstring__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor bstring__field_descriptors[3] =
{
  {
    "mlen",
    1,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FIXED32,
    0,   /* quantifier_offset */
    offsetof(Bstring, mlen),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "slen",
    2,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_FIXED32,
    0,   /* quantifier_offset */
    offsetof(Bstring, slen),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    3,
    PROTOBUF_C_LABEL_REQUIRED,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Bstring, data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned bstring__field_indices_by_name[] = {
  2,   /* field[2] = data */
  0,   /* field[0] = mlen */
  1,   /* field[1] = slen */
};
static const ProtobufCIntRange bstring__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor bstring__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "Bstring",
  "Bstring",
  "Bstring",
  "",
  sizeof(Bstring),
  3,
  bstring__field_descriptors,
  bstring__field_indices_by_name,
  1,  bstring__number_ranges,
  (ProtobufCMessageInit) bstring__init,
  NULL,NULL,NULL    /* reserved[123] */
};
