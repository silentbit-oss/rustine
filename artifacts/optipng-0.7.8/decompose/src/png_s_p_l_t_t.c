typedef struct png_sPLT_struct
{
  png_charp name;
  png_byte depth;
  png_sPLT_entryp entries;
  png_int_32 nentries;
} png_sPLT_t
/*** DEPENDENCIES:
typedef char *png_charp
----------------------------
typedef int png_int_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef struct png_sPLT_entry_struct
{
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 alpha;
  png_uint_16 frequency;
} png_sPLT_entry
----------------------------
typedef png_sPLT_entry *png_sPLT_entryp
----------------------------
***/


