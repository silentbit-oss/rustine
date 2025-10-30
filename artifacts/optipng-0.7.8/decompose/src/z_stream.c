typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
typedef void *voidp
----------------------------
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size)
----------------------------
typedef void (*free_func)(voidpf opaque, voidpf address)
----------------------------
typedef unsigned int uInt
----------------------------
typedef void *voidpf
----------------------------
typedef unsigned char Byte
----------------------------
***/


