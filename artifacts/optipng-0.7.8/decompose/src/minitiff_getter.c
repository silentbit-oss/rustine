struct minitiff_getter
{
  unsigned int (*get_ushort)(const unsigned char *buf_ptr);
  unsigned long (*get_ulong)(const unsigned char *buf_ptr);
}
/*** DEPENDENCIES:
***/


