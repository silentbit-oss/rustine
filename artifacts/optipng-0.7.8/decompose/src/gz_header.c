typedef struct gz_header_s
{
  int text;
  uLong time;
  int xflags;
  int os;
  Bytef *extra;
  uInt extra_len;
  uInt extra_max;
  Bytef *name;
  uInt name_max;
  Bytef *comment;
  uInt comm_max;
  int hcrc;
  int done;
} gz_header
/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
typedef unsigned int uInt
----------------------------
typedef unsigned char Byte
----------------------------
***/


