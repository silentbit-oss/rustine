int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  const char *fmt;
  unsigned int fmt_idx = 0;
  unsigned int marker;
  int result;
  if (sig_size < 12)
  {
    return -1;
  }
  if (((sig[0] == 0xff) && (sig[1] == 0xd8)) && (sig[2] == 0xff))
  {
    marker = 0xff00U | sig[3];
    if (((marker >= 0xffc0U) && (marker <= 0xffcfU)) || ((marker >= 0xffdaU) && (marker <= 0xfffeU)))
    {
      fmt_idx = "JPEG";
      result = 1;
    }
    else
      return 0;
  }
  else
    if ((memcmp(sig, jpeg_sig_jp2, 12) == 0) || (memcmp(sig, jpeg_sig_jpc, 4) == 0))
  {
    fmt_idx = "JPEG-2000";
    result = 2;
  }
  else
    if ((memcmp(sig, jpeg_sig_jng, 8) == 0) || (memcmp(sig, jpeg_sig_jng_jhdr, 8) == 0))
  {
    fmt_idx = "JNG";
    result = 3;
  }
  else
    return 0;
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = &fmt[fmt_idx];
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = &fmt[fmt_idx];
  }
  return result;
}


/*** DEPENDENCIES:
typedef const char **png_const_charpp
----------------------------
typedef unsigned char png_byte
----------------------------
static const png_byte jpeg_sig_jpc[4] = {0xff, 0x4f, 0xff, 0x51}
----------------------------
static const png_byte jpeg_sig_jng[8] = {0x8b, 0x4a, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a}
----------------------------
typedef const char *png_const_charp
----------------------------
static const png_byte jpeg_sig_jng_jhdr[8] = {0x00, 0x00, 0x00, 0x1a, 0x4a, 0x48, 0x44, 0x52}
----------------------------
typedef png_byte *png_bytep
----------------------------
static const png_byte jpeg_sig_jp2[12] = {0x00, 0x00, 0x00, 0x0c, 0x6a, 0x50, 0x20, 0x20, 0x0d, 0x0a, 0x87, 0x0a}
----------------------------
***/


int pngx_read_jpeg(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  png_byte buf[12];
  int sig_code;
  if (fread(buf, 12, 1, stream) != 1)
  {
    return 0;
  }
  sig_code = pngx_sig_is_jpeg(buf, 12, 0, 0);
  switch (sig_code)
  {
    case 1:
    {
      png_error(png_ptr, "JPEG decoding is not supported");
      break;
    }

    case 2:
    {
      png_error(png_ptr, "JPEG-2000 decoding is not supported");
      break;
    }

    case 3:
    {
      png_error(png_ptr, "JNG (JPEG) decoding is not supported");
      break;
    }

  }

  if (info_ptr == 0)
  {
    return 0;
  }
  return 0;
}


/*** DEPENDENCIES:
int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  const char *fmt;
  unsigned int fmt_idx = 0;
  unsigned int marker;
  int result;
  if (sig_size < 12)
  {
    return -1;
  }
  if (((sig[0] == 0xff) && (sig[1] == 0xd8)) && (sig[2] == 0xff))
  {
    marker = 0xff00U | sig[3];
    if (((marker >= 0xffc0U) && (marker <= 0xffcfU)) || ((marker >= 0xffdaU) && (marker <= 0xfffeU)))
    {
      fmt_idx = "JPEG";
      result = 1;
    }
    else
      return 0;
  }
  else
    if ((memcmp(sig, jpeg_sig_jp2, 12) == 0) || (memcmp(sig, jpeg_sig_jpc, 4) == 0))
  {
    fmt_idx = "JPEG-2000";
    result = 2;
  }
  else
    if ((memcmp(sig, jpeg_sig_jng, 8) == 0) || (memcmp(sig, jpeg_sig_jng_jhdr, 8) == 0))
  {
    fmt_idx = "JNG";
    result = 3;
  }
  else
    return 0;
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = &fmt[fmt_idx];
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = &fmt[fmt_idx];
  }
  return result;
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
***/


