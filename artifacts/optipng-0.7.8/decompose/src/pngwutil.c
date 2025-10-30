void png_save_uint_16(png_bytep buf, unsigned int i)
{
  buf[0] = (png_byte) ((i >> 8) & 0xffU);
  buf[1] = (png_byte) (i & 0xffU);
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


// hint:  ['rp_ref is a mutable refrence to png_bytep', 'dp_ref is a mutable refrence to png_bytep', 'pp_ref is a mutable refrence to png_bytep', 'cp_ref is a mutable refrence to png_bytep', 'lp_ref is a mutable refrence to png_bytep', 'sum_ref is a mutable refrence to size_t', 'v_ref is a mutable refrence to unsigned int']
void helper_png_setup_paeth_row_1(png_bytep * const rp_ref, png_bytep * const dp_ref, png_bytep * const pp_ref, png_bytep * const cp_ref, png_bytep * const lp_ref, size_t * const sum_ref, unsigned int * const v_ref, size_t lmins)
{
  png_bytep rp = *rp_ref;
  png_bytep dp = *dp_ref;
  png_bytep pp = *pp_ref;
  png_bytep cp = *cp_ref;
  png_bytep lp = *lp_ref;
  size_t sum = *sum_ref;
  unsigned int v = *v_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  b = *pp;
  pp += 1;
  c = *cp;
  cp += 1;
  a = *lp;
  lp += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  p = ((pa <= pb) && (pa <= pc)) ? (a) : ((pb <= pc) ? (b) : (c));
  v = (*dp = (png_byte) ((((int) (*rp)) - p) & 0xff));
  rp += 1;
  dp += 1;
  sum += (v < 128) ? (v) : (256 - v);
  if (sum > lmins)
  {
    break;
  }
  *rp_ref = rp;
  *dp_ref = dp;
  *pp_ref = pp;
  *cp_ref = cp;
  *lp_ref = lp;
  *sum_ref = sum;
  *v_ref = v;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


// hint:  ['rp_ref is a mutable refrence to png_bytep', 'dp_ref is a mutable refrence to png_bytep', 'pp_ref is a mutable refrence to png_bytep', 'cp_ref is a mutable refrence to png_bytep', 'lp_ref is a mutable refrence to png_bytep']
void helper_png_setup_paeth_row_only_1(png_bytep * const rp_ref, png_bytep * const dp_ref, png_bytep * const pp_ref, png_bytep * const cp_ref, png_bytep * const lp_ref)
{
  png_bytep rp = *rp_ref;
  png_bytep dp = *dp_ref;
  png_bytep pp = *pp_ref;
  png_bytep cp = *cp_ref;
  png_bytep lp = *lp_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  b = *pp;
  pp += 1;
  c = *cp;
  cp += 1;
  a = *lp;
  lp += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  p = ((pa <= pb) && (pa <= pc)) ? (a) : ((pb <= pc) ? (b) : (c));
  *dp = (png_byte) ((((int) (*rp)) - p) & 0xff);
  rp += 1;
  dp += 1;
  *rp_ref = rp;
  *dp_ref = dp;
  *pp_ref = pp;
  *cp_ref = cp;
  *lp_ref = lp;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


void png_free_buffer_list(png_structrp png_ptr, png_compression_bufferp *listp)
{
  png_compression_bufferp list = *listp;
  if (list != 0)
  {
    *listp = 0;
    do
    {
      png_compression_bufferp next = list->next;
      png_free(png_ptr, list);
      list = next;
    }
    while (list != 0);
  }
}


/*** DEPENDENCIES:
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} png_compression_buffer
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_free(png_const_structrp png_ptr, png_voidp ptr)
{
  if ((png_ptr == 0) || (ptr == 0))
  {
    return;
  }
  free(ptr);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} *png_compression_bufferp
----------------------------
***/


void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
int helper_png_deflate_claim_1(png_structrp * const png_ptr_ref, png_uint_32 owner)
{
  png_structrp png_ptr = *png_ptr_ref;
  char msg[64];
  (void) ((((char *) msg)[0] = (char) ((owner >> 24) & 0xff), ((char *) msg)[1] = (char) ((owner >> 16) & 0xff), ((char *) msg)[2] = (char) ((owner >> 8) & 0xff), ((char *) msg)[3] = (char) (owner & 0xff)));
  msg[4] = ':';
  msg[5] = ' ';
  (void) ((((char *) (msg + 6))[0] = (char) ((png_ptr->zowner >> 24) & 0xff), ((char *) (msg + 6))[1] = (char) ((png_ptr->zowner >> 16) & 0xff), ((char *) (msg + 6))[2] = (char) ((png_ptr->zowner >> 8) & 0xff), ((char *) (msg + 6))[3] = (char) (png_ptr->zowner & 0xff)));
  (void) png_safecat(msg, sizeof(msg), 10, " using zstream");
  png_warning(png_ptr, msg);
  if (png_ptr->zowner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->zstream.msg = "in use by IDAT";
    return -2;
  }
  png_ptr->zowner = 0;
  *png_ptr_ref = png_ptr;
}


/*** DEPENDENCIES:
size_t png_safecat(png_charp buffer, size_t bufsize, size_t pos, png_const_charp string)
{
  if ((buffer != 0) && (pos < bufsize))
  {
    if (string != 0)
    {
      while (((*string) != '\0') && (pos < (bufsize - 1)))
      {
        buffer[pos] = *string;
        string += 1;
        pos += 1;
      }

    }
    buffer[pos] = '\0';
  }
  return pos;
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
int helper_png_deflate_claim_2(png_structrp * const png_ptr_ref, png_uint_32 owner, png_alloc_size_t data_size)
{
  png_structrp png_ptr = *png_ptr_ref;
  int level = png_ptr->zlib_level;
  int method = png_ptr->zlib_method;
  int windowBits = png_ptr->zlib_window_bits;
  int memLevel = png_ptr->zlib_mem_level;
  int strategy;
  int ret;
  if (owner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if ((png_ptr->flags & 0x0001U) != 0)
    {
      strategy = png_ptr->zlib_strategy;
    }
    else
      if (png_ptr->do_filter != 0x08)
    {
      strategy = 1;
    }
    else
      strategy = 0;
  }
  else
  {
    strategy = 0;
  }
  if (data_size <= 16384)
  {
    unsigned int half_window_size = 1U << (windowBits - 1);
    while ((data_size + 262) <= half_window_size)
    {
      half_window_size >>= 1;
      windowBits -= 1;
    }

  }
  if (((png_ptr->flags & 0x0002U) != 0) && (((((png_ptr->zlib_set_level != level) || (png_ptr->zlib_set_method != method)) || (png_ptr->zlib_set_window_bits != windowBits)) || (png_ptr->zlib_set_mem_level != memLevel)) || (png_ptr->zlib_set_strategy != strategy)))
  {
    if (deflateEnd(&png_ptr->zstream) != 0)
    {
      png_warning(png_ptr, "deflateEnd failed (ignored)");
    }
    png_ptr->flags &= ~0x0002U;
  }
  png_ptr->zstream.next_in = 0;
  png_ptr->zstream.avail_in = 0;
  png_ptr->zstream.next_out = 0;
  png_ptr->zstream.avail_out = 0;
  if ((png_ptr->flags & 0x0002U) != 0)
  {
    ret = deflateReset(&png_ptr->zstream);
  }
  else
  {
    ret = deflateInit2_(&png_ptr->zstream, level, method, windowBits, memLevel, strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret == 0)
    {
      png_ptr->flags |= 0x0002U;
    }
  }
  if (ret == 0)
  {
    png_ptr->zowner = owner;
  }
  else
    png_zstream_error(png_ptr, ret);
  return ret;
  *png_ptr_ref = png_ptr;
}


/*** DEPENDENCIES:
void png_zstream_error(png_structrp png_ptr, int ret)
{
  if (png_ptr->zstream.msg == 0)
  {
    switch (ret)
    {
      default:

      case 0:
      {
        png_ptr->zstream.msg = "unexpected zlib return code";
        break;
      }

      case 1:
      {
        png_ptr->zstream.msg = "unexpected end of LZ stream";
        break;
      }

      case 2:
      {
        png_ptr->zstream.msg = "missing LZ dictionary";
        break;
      }

      case -1:
      {
        png_ptr->zstream.msg = "zlib IO error";
        break;
      }

      case -2:
      {
        png_ptr->zstream.msg = "bad parameters to zlib";
        break;
      }

      case -3:
      {
        png_ptr->zstream.msg = "damaged LZ stream";
        break;
      }

      case -4:
      {
        png_ptr->zstream.msg = "insufficient memory";
        break;
      }

      case -5:
      {
        png_ptr->zstream.msg = "truncated";
        break;
      }

      case -6:
      {
        png_ptr->zstream.msg = "unsupported zlib version";
        break;
      }

      case -7:
      {
        png_ptr->zstream.msg = "unexpected zlib return";
        break;
      }

    }

  }
}


----------------------------
typedef size_t png_alloc_size_t
----------------------------
int deflateReset(z_streamp strm)
{
  int ret;
  ret = deflateResetKeep(strm);
  if (ret == 0)
  {
    lm_init(strm->state);
  }
  return ret;
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  int wrap = 1;
  static const char my_version[] = "1.3-optipng";
  if (((version == 0) || (version[0] != my_version[0])) || (stream_size != (sizeof(z_stream))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  if (level == (-1))
  {
    level = 6;
  }
  if (windowBits < 0)
  {
    wrap = 0;
    if (windowBits < (-15))
    {
      return -2;
    }
    windowBits = -windowBits;
  }
  if ((((((((((memLevel < 1) || (memLevel > 9)) || (method != 8)) || (windowBits < 8)) || (windowBits > 15)) || (level < 0)) || (level > 9)) || (strategy < 0)) || (strategy > 4)) || ((windowBits == 8) && (wrap != 1)))
  {
    return -2;
  }
  if (windowBits == 8)
  {
    windowBits = 9;
  }
  s_idx = (deflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(deflate_state));
  if ((&s[s_idx]) == 0)
  {
    return -4;
  }
  strm->state = (struct internal_state *) s;
  s->strm = strm;
  s->status = 42;
  s->wrap = wrap;
  s->gzhead = 0;
  s->w_bits = (uInt) windowBits;
  s->w_size = 1 << s->w_bits;
  s->w_mask = s->w_size - 1;
  s->hash_bits = ((uInt) memLevel) + 7;
  s->hash_size = 1 << s->hash_bits;
  s->hash_mask = s->hash_size - 1;
  s->hash_shift = ((s->hash_bits + 3) - 1) / 3;
  s->window = (Bytef *) (*strm->zalloc)(strm->opaque, s->w_size, 2 * (sizeof(Byte)));
  s->prev = (Posf *) (*strm->zalloc)(strm->opaque, s->w_size, sizeof(Pos));
  s->head = (Posf *) (*strm->zalloc)(strm->opaque, s->hash_size, sizeof(Pos));
  s->high_water = 0;
  s->lit_bufsize = 1 << (memLevel + 6);
  s->pending_buf = (uchf *) (*strm->zalloc)(strm->opaque, s->lit_bufsize, 4);
  s->pending_buf_size = ((ulg) s->lit_bufsize) * 4;
  if ((((s->window == 0) || (s->prev == 0)) || (s->head == 0)) || (s->pending_buf == 0))
  {
    s->status = 666;
    strm->msg = z_errmsg[2 - (-4)];
    deflateEnd(strm);
    return -4;
  }
  s->sym_buf = s->pending_buf + s->lit_bufsize;
  s->sym_end = (s->lit_bufsize - 1) * 3;
  s->level = level;
  s->strategy = strategy;
  s->method = (Byte) method;
  return deflateReset(strm);
}


----------------------------
int deflateEnd(z_streamp strm)
{
  int status;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  status = strm->state->status;
  {
    if (strm->state->pending_buf)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->pending_buf);
    }
  }
  ;
  {
    if (strm->state->head)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->head);
    }
  }
  ;
  {
    if (strm->state->prev)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->prev);
    }
  }
  ;
  {
    if (strm->state->window)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->window);
    }
  }
  ;
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  return (status == 113) ? (-3) : (0);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static int png_deflate_claim(png_structrp png_ptr, png_uint_32 owner, png_alloc_size_t data_size)
{
  if (png_ptr->zowner != 0)
  {
    helper_png_deflate_claim_1(&png_ptr, owner);
  }
  {
    helper_png_deflate_claim_2(&png_ptr, owner, data_size);
  }
}


/*** DEPENDENCIES:
int helper_png_deflate_claim_1(png_structrp * const png_ptr_ref, png_uint_32 owner)
{
  png_structrp png_ptr = *png_ptr_ref;
  char msg[64];
  (void) ((((char *) msg)[0] = (char) ((owner >> 24) & 0xff), ((char *) msg)[1] = (char) ((owner >> 16) & 0xff), ((char *) msg)[2] = (char) ((owner >> 8) & 0xff), ((char *) msg)[3] = (char) (owner & 0xff)));
  msg[4] = ':';
  msg[5] = ' ';
  (void) ((((char *) (msg + 6))[0] = (char) ((png_ptr->zowner >> 24) & 0xff), ((char *) (msg + 6))[1] = (char) ((png_ptr->zowner >> 16) & 0xff), ((char *) (msg + 6))[2] = (char) ((png_ptr->zowner >> 8) & 0xff), ((char *) (msg + 6))[3] = (char) (png_ptr->zowner & 0xff)));
  (void) png_safecat(msg, sizeof(msg), 10, " using zstream");
  png_warning(png_ptr, msg);
  if (png_ptr->zowner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->zstream.msg = "in use by IDAT";
    return -2;
  }
  png_ptr->zowner = 0;
  *png_ptr_ref = png_ptr;
}


----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned int png_uint_32
----------------------------
int helper_png_deflate_claim_2(png_structrp * const png_ptr_ref, png_uint_32 owner, png_alloc_size_t data_size)
{
  png_structrp png_ptr = *png_ptr_ref;
  int level = png_ptr->zlib_level;
  int method = png_ptr->zlib_method;
  int windowBits = png_ptr->zlib_window_bits;
  int memLevel = png_ptr->zlib_mem_level;
  int strategy;
  int ret;
  if (owner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if ((png_ptr->flags & 0x0001U) != 0)
    {
      strategy = png_ptr->zlib_strategy;
    }
    else
      if (png_ptr->do_filter != 0x08)
    {
      strategy = 1;
    }
    else
      strategy = 0;
  }
  else
  {
    strategy = 0;
  }
  if (data_size <= 16384)
  {
    unsigned int half_window_size = 1U << (windowBits - 1);
    while ((data_size + 262) <= half_window_size)
    {
      half_window_size >>= 1;
      windowBits -= 1;
    }

  }
  if (((png_ptr->flags & 0x0002U) != 0) && (((((png_ptr->zlib_set_level != level) || (png_ptr->zlib_set_method != method)) || (png_ptr->zlib_set_window_bits != windowBits)) || (png_ptr->zlib_set_mem_level != memLevel)) || (png_ptr->zlib_set_strategy != strategy)))
  {
    if (deflateEnd(&png_ptr->zstream) != 0)
    {
      png_warning(png_ptr, "deflateEnd failed (ignored)");
    }
    png_ptr->flags &= ~0x0002U;
  }
  png_ptr->zstream.next_in = 0;
  png_ptr->zstream.avail_in = 0;
  png_ptr->zstream.next_out = 0;
  png_ptr->zstream.avail_out = 0;
  if ((png_ptr->flags & 0x0002U) != 0)
  {
    ret = deflateReset(&png_ptr->zstream);
  }
  else
  {
    ret = deflateInit2_(&png_ptr->zstream, level, method, windowBits, memLevel, strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret == 0)
    {
      png_ptr->flags |= 0x0002U;
    }
  }
  if (ret == 0)
  {
    png_ptr->zowner = owner;
  }
  else
    png_zstream_error(png_ptr, ret);
  return ret;
  *png_ptr_ref = png_ptr;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static void optimize_cmf(png_bytep data, png_alloc_size_t data_size)
{
  if (data_size <= 16384)
  {
    unsigned int z_cmf = data[0];
    if (((z_cmf & 0x0f) == 8) && ((z_cmf & 0xf0) <= 0x70))
    {
      unsigned int z_cinfo;
      unsigned int half_z_window_size;
      z_cinfo = z_cmf >> 4;
      half_z_window_size = 1U << (z_cinfo + 7);
      if (data_size <= half_z_window_size)
      {
        unsigned int tmp;
        do
        {
          half_z_window_size >>= 1;
          z_cinfo -= 1;
        }
        while ((z_cinfo > 0) && (data_size <= half_z_window_size));
        z_cmf = (z_cmf & 0x0f) | (z_cinfo << 4);
        data[0] = (png_byte) z_cmf;
        tmp = data[1] & 0xe0;
        tmp += 0x1f - (((z_cmf << 8) + tmp) % 0x1f);
        data[1] = (png_byte) tmp;
      }
    }
  }
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef size_t png_alloc_size_t
----------------------------
***/


void png_write_chunk_end(png_structrp png_ptr)
{
  png_byte buf[4];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0080;
  png_save_uint_32(buf, png_ptr->crc);
  png_write_data(png_ptr, buf, 4);
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr->write_data_fn != 0)
  {
    (*png_ptr->write_data_fn)(png_ptr, (png_bytep) ((void *) ((const void *) data)), length);
  }
  else
    png_error(png_ptr, "Call to NULL write function");
}


----------------------------
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
***/


static void png_write_chunk_header(png_structrp png_ptr, png_uint_32 chunk_name, png_uint_32 length)
{
  png_byte buf[8];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0020;
  png_save_uint_32(buf, length);
  png_save_uint_32(buf + 4, chunk_name);
  png_write_data(png_ptr, buf, 8);
  png_ptr->chunk_name = chunk_name;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_ptr->io_state = 0x0002 | 0x0040;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr->write_data_fn != 0)
  {
    (*png_ptr->write_data_fn)(png_ptr, (png_bytep) ((void *) ((const void *) data)), length);
  }
  else
    png_error(png_ptr, "Call to NULL write function");
}


----------------------------
void png_reset_crc(png_structrp png_ptr)
{
  png_ptr->crc = (png_uint_32) crc32(0, 0, 0);
}


----------------------------
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_calculate_crc(png_structrp png_ptr, png_const_bytep ptr, size_t length)
{
  int need_crc = 1;
  if ((1 & (png_ptr->chunk_name >> 29)) != 0)
  {
    if ((png_ptr->flags & (0x0100U | 0x0200U)) == (0x0100U | 0x0200U))
    {
      need_crc = 0;
    }
  }
  else
  {
    if ((png_ptr->flags & 0x0800U) != 0)
    {
      need_crc = 0;
    }
  }
  if ((need_crc != 0) && (length > 0))
  {
    uLong crc = png_ptr->crc;
    do
    {
      uInt safe_length = (uInt) length;
      if (safe_length == 0)
      {
        safe_length = (uInt) (-1);
      }
      crc = crc32(crc, ptr, safe_length);
      ptr += safe_length;
      length -= safe_length;
    }
    while (length > 0);
    png_ptr->crc = (png_uint_32) crc;
  }
}


----------------------------
***/


void png_write_chunk_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if ((data != 0) && (length > 0))
  {
    png_write_data(png_ptr, data, length);
    png_calculate_crc(png_ptr, data, length);
  }
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr->write_data_fn != 0)
  {
    (*png_ptr->write_data_fn)(png_ptr, (png_bytep) ((void *) ((const void *) data)), length);
  }
  else
    png_error(png_ptr, "Call to NULL write function");
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_calculate_crc(png_structrp png_ptr, png_const_bytep ptr, size_t length)
{
  int need_crc = 1;
  if ((1 & (png_ptr->chunk_name >> 29)) != 0)
  {
    if ((png_ptr->flags & (0x0100U | 0x0200U)) == (0x0100U | 0x0200U))
    {
      need_crc = 0;
    }
  }
  else
  {
    if ((png_ptr->flags & 0x0800U) != 0)
    {
      need_crc = 0;
    }
  }
  if ((need_crc != 0) && (length > 0))
  {
    uLong crc = png_ptr->crc;
    do
    {
      uInt safe_length = (uInt) length;
      if (safe_length == 0)
      {
        safe_length = (uInt) (-1);
      }
      crc = crc32(crc, ptr, safe_length);
      ptr += safe_length;
      length -= safe_length;
    }
    while (length > 0);
    png_ptr->crc = (png_uint_32) crc;
  }
}


----------------------------
***/


static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
void png_write_chunk_end(png_structrp png_ptr)
{
  png_byte buf[4];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0080;
  png_save_uint_32(buf, png_ptr->crc);
  png_write_data(png_ptr, buf, 4);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
static void png_write_chunk_header(png_structrp png_ptr, png_uint_32 chunk_name, png_uint_32 length)
{
  png_byte buf[8];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0020;
  png_save_uint_32(buf, length);
  png_save_uint_32(buf + 4, chunk_name);
  png_write_data(png_ptr, buf, 8);
  png_ptr->chunk_name = chunk_name;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_ptr->io_state = 0x0002 | 0x0040;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
void png_write_chunk_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if ((data != 0) && (length > 0))
  {
    png_write_data(png_ptr, data, length);
    png_calculate_crc(png_ptr, data, length);
  }
}


----------------------------
typedef struct png_struct_def png_struct
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


static png_alloc_size_t png_image_size(png_structrp png_ptr)
{
  png_uint_32 h = png_ptr->height;
  if ((png_ptr->rowbytes < 32768) && (h < 32768))
  {
    if (png_ptr->interlaced != 0)
    {
      png_uint_32 w = png_ptr->width;
      unsigned int pd = png_ptr->pixel_depth;
      png_alloc_size_t cb_base;
      int pass;
      for (cb_base = 0, pass = 0; pass <= 6; pass += 1)
      {
        png_uint_32 pw = (w + (((1 << ((pass > 1) ? ((7 - pass) >> 1) : (3))) - 1) - (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))) >> ((pass > 1) ? ((7 - pass) >> 1) : (3));
        if (pw > 0)
        {
          cb_base += (((pd >= 8) ? (((size_t) pw) * (((size_t) pd) >> 3)) : (((((size_t) pw) * ((size_t) pd)) + 7) >> 3)) + 1) * ((h + (((1 << ((pass > 2) ? ((8 - pass) >> 1) : (3))) - 1) - (((1 & (~pass)) << (3 - (pass >> 1))) & 7))) >> ((pass > 2) ? ((8 - pass) >> 1) : (3)));
        }
      }

      return cb_base;
    }
    else
      return (png_ptr->rowbytes + 1) * h;
  }
  else
    return 0xffffffffU;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
void helper_helper_png_compress_IDAT_1_1(png_structrp * const png_ptr_ref, int flush, int ret)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_bytep data = png_ptr->zbuffer_list->output;
  uInt size = png_ptr->zbuffer_size;
  if (((png_ptr->mode & 0x04U) == 0) && (png_ptr->compression_type == 0))
  {
    optimize_cmf(data, png_image_size(png_ptr));
  }
  if (size > 0)
  {
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), data, size);
  }
  png_ptr->mode |= 0x04U;
  png_ptr->zstream.next_out = data;
  png_ptr->zstream.avail_out = size;
  if ((ret == 0) && (flush != 0))
  {
    continue;
  }
  *png_ptr_ref = png_ptr;
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
typedef unsigned int uInt
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void optimize_cmf(png_bytep data, png_alloc_size_t data_size)
{
  if (data_size <= 16384)
  {
    unsigned int z_cmf = data[0];
    if (((z_cmf & 0x0f) == 8) && ((z_cmf & 0xf0) <= 0x70))
    {
      unsigned int z_cinfo;
      unsigned int half_z_window_size;
      z_cinfo = z_cmf >> 4;
      half_z_window_size = 1U << (z_cinfo + 7);
      if (data_size <= half_z_window_size)
      {
        unsigned int tmp;
        do
        {
          half_z_window_size >>= 1;
          z_cinfo -= 1;
        }
        while ((z_cinfo > 0) && (data_size <= half_z_window_size));
        z_cmf = (z_cmf & 0x0f) | (z_cinfo << 4);
        data[0] = (png_byte) z_cmf;
        tmp = data[1] & 0xe0;
        tmp += 0x1f - (((z_cmf << 8) + tmp) % 0x1f);
        data[1] = (png_byte) tmp;
      }
    }
  }
}


----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
typedef png_byte *png_bytep
----------------------------
static png_alloc_size_t png_image_size(png_structrp png_ptr)
{
  png_uint_32 h = png_ptr->height;
  if ((png_ptr->rowbytes < 32768) && (h < 32768))
  {
    if (png_ptr->interlaced != 0)
    {
      png_uint_32 w = png_ptr->width;
      unsigned int pd = png_ptr->pixel_depth;
      png_alloc_size_t cb_base;
      int pass;
      for (cb_base = 0, pass = 0; pass <= 6; pass += 1)
      {
        png_uint_32 pw = (w + (((1 << ((pass > 1) ? ((7 - pass) >> 1) : (3))) - 1) - (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))) >> ((pass > 1) ? ((7 - pass) >> 1) : (3));
        if (pw > 0)
        {
          cb_base += (((pd >= 8) ? (((size_t) pw) * (((size_t) pd) >> 3)) : (((((size_t) pw) * ((size_t) pd)) + 7) >> 3)) + 1) * ((h + (((1 << ((pass > 2) ? ((8 - pass) >> 1) : (3))) - 1) - (((1 & (~pass)) << (3 - (pass >> 1))) & 7))) >> ((pass > 2) ? ((8 - pass) >> 1) : (3)));
        }
      }

      return cb_base;
    }
    else
      return (png_ptr->rowbytes + 1) * h;
  }
  else
    return 0xffffffffU;
}


----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
void helper_helper_png_compress_IDAT_1_2(png_structrp * const png_ptr_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_bytep data = png_ptr->zbuffer_list->output;
  uInt size = png_ptr->zbuffer_size - png_ptr->zstream.avail_out;
  if (((png_ptr->mode & 0x04U) == 0) && (png_ptr->compression_type == 0))
  {
    optimize_cmf(data, png_image_size(png_ptr));
  }
  if (size > 0)
  {
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), data, size);
  }
  png_ptr->zstream.avail_out = 0;
  png_ptr->zstream.next_out = 0;
  png_ptr->mode |= 0x04U | 0x08;
  png_ptr->zowner = 0;
  return;
  *png_ptr_ref = png_ptr;
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
typedef unsigned int uInt
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void optimize_cmf(png_bytep data, png_alloc_size_t data_size)
{
  if (data_size <= 16384)
  {
    unsigned int z_cmf = data[0];
    if (((z_cmf & 0x0f) == 8) && ((z_cmf & 0xf0) <= 0x70))
    {
      unsigned int z_cinfo;
      unsigned int half_z_window_size;
      z_cinfo = z_cmf >> 4;
      half_z_window_size = 1U << (z_cinfo + 7);
      if (data_size <= half_z_window_size)
      {
        unsigned int tmp;
        do
        {
          half_z_window_size >>= 1;
          z_cinfo -= 1;
        }
        while ((z_cinfo > 0) && (data_size <= half_z_window_size));
        z_cmf = (z_cmf & 0x0f) | (z_cinfo << 4);
        data[0] = (png_byte) z_cmf;
        tmp = data[1] & 0xe0;
        tmp += 0x1f - (((z_cmf << 8) + tmp) % 0x1f);
        data[1] = (png_byte) tmp;
      }
    }
  }
}


----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
typedef png_byte *png_bytep
----------------------------
static png_alloc_size_t png_image_size(png_structrp png_ptr)
{
  png_uint_32 h = png_ptr->height;
  if ((png_ptr->rowbytes < 32768) && (h < 32768))
  {
    if (png_ptr->interlaced != 0)
    {
      png_uint_32 w = png_ptr->width;
      unsigned int pd = png_ptr->pixel_depth;
      png_alloc_size_t cb_base;
      int pass;
      for (cb_base = 0, pass = 0; pass <= 6; pass += 1)
      {
        png_uint_32 pw = (w + (((1 << ((pass > 1) ? ((7 - pass) >> 1) : (3))) - 1) - (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))) >> ((pass > 1) ? ((7 - pass) >> 1) : (3));
        if (pw > 0)
        {
          cb_base += (((pd >= 8) ? (((size_t) pw) * (((size_t) pd) >> 3)) : (((((size_t) pw) * ((size_t) pd)) + 7) >> 3)) + 1) * ((h + (((1 << ((pass > 2) ? ((8 - pass) >> 1) : (3))) - 1) - (((1 & (~pass)) << (3 - (pass >> 1))) & 7))) >> ((pass > 2) ? ((8 - pass) >> 1) : (3)));
        }
      }

      return cb_base;
    }
    else
      return (png_ptr->rowbytes + 1) * h;
  }
  else
    return 0xffffffffU;
}


----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'input_len_ref is a mutable refrence to png_alloc_size_t']
void helper_png_compress_IDAT_1(png_structrp * const png_ptr_ref, png_alloc_size_t * const input_len_ref, int flush)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_alloc_size_t input_len = *input_len_ref;
  int ret;
  uInt avail = (uInt) (-1);
  if (avail > input_len)
  {
    avail = (uInt) input_len;
  }
  png_ptr->zstream.avail_in = avail;
  input_len -= avail;
  ret = deflate(&png_ptr->zstream, (input_len > 0) ? (0) : (flush));
  input_len += png_ptr->zstream.avail_in;
  png_ptr->zstream.avail_in = 0;
  if (png_ptr->zstream.avail_out == 0)
  {
    helper_helper_png_compress_IDAT_1_1(&png_ptr, flush, ret);
  }
  if (ret == 0)
  {
    if (input_len == 0)
    {
      if (flush == 4)
      {
        png_error(png_ptr, "Z_OK on Z_FINISH with output space");
      }
      return;
    }
  }
  else
    if ((ret == 1) && (flush == 4))
  {
    helper_helper_png_compress_IDAT_1_2(&png_ptr);
  }
  else
  {
    png_zstream_error(png_ptr, ret);
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  *png_ptr_ref = png_ptr;
  *input_len_ref = input_len;
}


/*** DEPENDENCIES:
void png_zstream_error(png_structrp png_ptr, int ret)
{
  if (png_ptr->zstream.msg == 0)
  {
    switch (ret)
    {
      default:

      case 0:
      {
        png_ptr->zstream.msg = "unexpected zlib return code";
        break;
      }

      case 1:
      {
        png_ptr->zstream.msg = "unexpected end of LZ stream";
        break;
      }

      case 2:
      {
        png_ptr->zstream.msg = "missing LZ dictionary";
        break;
      }

      case -1:
      {
        png_ptr->zstream.msg = "zlib IO error";
        break;
      }

      case -2:
      {
        png_ptr->zstream.msg = "bad parameters to zlib";
        break;
      }

      case -3:
      {
        png_ptr->zstream.msg = "damaged LZ stream";
        break;
      }

      case -4:
      {
        png_ptr->zstream.msg = "insufficient memory";
        break;
      }

      case -5:
      {
        png_ptr->zstream.msg = "truncated";
        break;
      }

      case -6:
      {
        png_ptr->zstream.msg = "unsupported zlib version";
        break;
      }

      case -7:
      {
        png_ptr->zstream.msg = "unexpected zlib return";
        break;
      }

    }

  }
}


----------------------------
typedef size_t png_alloc_size_t
----------------------------
void helper_helper_png_compress_IDAT_1_1(png_structrp * const png_ptr_ref, int flush, int ret)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_bytep data = png_ptr->zbuffer_list->output;
  uInt size = png_ptr->zbuffer_size;
  if (((png_ptr->mode & 0x04U) == 0) && (png_ptr->compression_type == 0))
  {
    optimize_cmf(data, png_image_size(png_ptr));
  }
  if (size > 0)
  {
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), data, size);
  }
  png_ptr->mode |= 0x04U;
  png_ptr->zstream.next_out = data;
  png_ptr->zstream.avail_out = size;
  if ((ret == 0) && (flush != 0))
  {
    continue;
  }
  *png_ptr_ref = png_ptr;
}


----------------------------
int deflate(z_streamp strm, int flush)
{
  int old_flush;
  deflate_state *s;
  unsigned int s_idx = 0;
  if ((deflateStateCheck(strm) || (flush > 5)) || (flush < 0))
  {
    return -2;
  }
  s_idx = strm->state;
  if (((strm->next_out == 0) || ((strm->avail_in != 0) && (strm->next_in == 0))) || ((s->status == 666) && (flush != 4)))
  {
    return strm->msg = z_errmsg[2 - (-2)], -2;
  }
  if (strm->avail_out == 0)
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  old_flush = s->last_flush;
  s->last_flush = flush;
  if (s->pending != 0)
  {
    flush_pending(strm);
    if (strm->avail_out == 0)
    {
      s->last_flush = -1;
      return 0;
    }
  }
  else
    if (((strm->avail_in == 0) && (((flush * 2) - ((flush > 4) ? (9) : (0))) <= ((old_flush * 2) - ((old_flush > 4) ? (9) : (0))))) && (flush != 4))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 666) && (strm->avail_in != 0))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 42) && (s->wrap == 0))
  {
    s->status = 113;
  }
  if (s->status == 42)
  {
    helper_deflate_1(&strm, s);
  }
  if (((strm->avail_in != 0) || (s->lookahead != 0)) || ((flush != 0) && (s->status != 666)))
  {
    helper_deflate_2(strm, flush, s);
  }
  if (flush != 4)
  {
    return 0;
  }
  if (s->wrap <= 0)
  {
    return 1;
  }
  {
    putShortMSB(s, (uInt) (strm->adler >> 16));
    putShortMSB(s, (uInt) (strm->adler & 0xffff));
  }
  flush_pending(strm);
  if (s->wrap > 0)
  {
    s->wrap = -s->wrap;
  }
  return (s->pending != 0) ? (0) : (1);
}


----------------------------
void helper_helper_png_compress_IDAT_1_2(png_structrp * const png_ptr_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_bytep data = png_ptr->zbuffer_list->output;
  uInt size = png_ptr->zbuffer_size - png_ptr->zstream.avail_out;
  if (((png_ptr->mode & 0x04U) == 0) && (png_ptr->compression_type == 0))
  {
    optimize_cmf(data, png_image_size(png_ptr));
  }
  if (size > 0)
  {
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), data, size);
  }
  png_ptr->zstream.avail_out = 0;
  png_ptr->zstream.next_out = 0;
  png_ptr->mode |= 0x04U | 0x08;
  png_ptr->zowner = 0;
  return;
  *png_ptr_ref = png_ptr;
}


----------------------------
typedef unsigned int uInt
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
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


void png_compress_IDAT(png_structrp png_ptr, png_const_bytep input, png_alloc_size_t input_len, int flush)
{
  if (png_ptr->zowner != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if (png_ptr->zbuffer_list == 0)
    {
      png_ptr->zbuffer_list = png_malloc(png_ptr, offsetof(png_compression_buffer, output) + png_ptr->zbuffer_size);
      png_ptr->zbuffer_list->next = 0;
    }
    else
      png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list->next);
    if (png_deflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), png_image_size(png_ptr)) != 0)
    {
      png_error(png_ptr, png_ptr->zstream.msg);
    }
    png_ptr->zstream.next_out = png_ptr->zbuffer_list->output;
    png_ptr->zstream.avail_out = png_ptr->zbuffer_size;
  }
  png_ptr->zstream.next_in = input;
  png_ptr->zstream.avail_in = 0;
  for (;;)
  {
    helper_png_compress_IDAT_1(&png_ptr, &input_len, flush);
  }

}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


----------------------------
typedef size_t png_alloc_size_t
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
static int png_deflate_claim(png_structrp png_ptr, png_uint_32 owner, png_alloc_size_t data_size)
{
  if (png_ptr->zowner != 0)
  {
    helper_png_deflate_claim_1(&png_ptr, owner);
  }
  {
    helper_png_deflate_claim_2(&png_ptr, owner, data_size);
  }
}


----------------------------
void helper_png_compress_IDAT_1(png_structrp * const png_ptr_ref, png_alloc_size_t * const input_len_ref, int flush)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_alloc_size_t input_len = *input_len_ref;
  int ret;
  uInt avail = (uInt) (-1);
  if (avail > input_len)
  {
    avail = (uInt) input_len;
  }
  png_ptr->zstream.avail_in = avail;
  input_len -= avail;
  ret = deflate(&png_ptr->zstream, (input_len > 0) ? (0) : (flush));
  input_len += png_ptr->zstream.avail_in;
  png_ptr->zstream.avail_in = 0;
  if (png_ptr->zstream.avail_out == 0)
  {
    helper_helper_png_compress_IDAT_1_1(&png_ptr, flush, ret);
  }
  if (ret == 0)
  {
    if (input_len == 0)
    {
      if (flush == 4)
      {
        png_error(png_ptr, "Z_OK on Z_FINISH with output space");
      }
      return;
    }
  }
  else
    if ((ret == 1) && (flush == 4))
  {
    helper_helper_png_compress_IDAT_1_2(&png_ptr);
  }
  else
  {
    png_zstream_error(png_ptr, ret);
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  *png_ptr_ref = png_ptr;
  *input_len_ref = input_len;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_free_buffer_list(png_structrp png_ptr, png_compression_bufferp *listp)
{
  png_compression_bufferp list = *listp;
  if (list != 0)
  {
    *listp = 0;
    do
    {
      png_compression_bufferp next = list->next;
      png_free(png_ptr, list);
      list = next;
    }
    while (list != 0);
  }
}


----------------------------
static png_alloc_size_t png_image_size(png_structrp png_ptr)
{
  png_uint_32 h = png_ptr->height;
  if ((png_ptr->rowbytes < 32768) && (h < 32768))
  {
    if (png_ptr->interlaced != 0)
    {
      png_uint_32 w = png_ptr->width;
      unsigned int pd = png_ptr->pixel_depth;
      png_alloc_size_t cb_base;
      int pass;
      for (cb_base = 0, pass = 0; pass <= 6; pass += 1)
      {
        png_uint_32 pw = (w + (((1 << ((pass > 1) ? ((7 - pass) >> 1) : (3))) - 1) - (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))) >> ((pass > 1) ? ((7 - pass) >> 1) : (3));
        if (pw > 0)
        {
          cb_base += (((pd >= 8) ? (((size_t) pw) * (((size_t) pd) >> 3)) : (((((size_t) pw) * ((size_t) pd)) + 7) >> 3)) + 1) * ((h + (((1 << ((pass > 2) ? ((8 - pass) >> 1) : (3))) - 1) - (((1 & (~pass)) << (3 - (pass >> 1))) & 7))) >> ((pass > 2) ? ((8 - pass) >> 1) : (3)));
        }
      }

      return cb_base;
    }
    else
      return (png_ptr->rowbytes + 1) * h;
  }
  else
    return 0xffffffffU;
}


----------------------------
***/


void png_write_finish_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  (void) 0;
  png_ptr->row_number += 1;
  if (png_ptr->row_number < png_ptr->num_rows)
  {
    return;
  }
  if (png_ptr->interlaced != 0)
  {
    png_ptr->row_number = 0;
    if ((png_ptr->transformations & 0x0002U) != 0)
    {
      png_ptr->pass += 1;
    }
    else
    {
      do
      {
        png_ptr->pass += 1;
        if (png_ptr->pass >= 7)
        {
          break;
        }
        png_ptr->usr_width = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
        if ((png_ptr->transformations & 0x0002U) != 0)
        {
          break;
        }
      }
      while ((png_ptr->usr_width == 0) || (png_ptr->num_rows == 0));
    }
    if (png_ptr->pass < 7)
    {
      if (png_ptr->prev_row != 0)
      {
        memset(png_ptr->prev_row, 0, (((png_ptr->usr_channels * png_ptr->usr_bit_depth) >= 8) ? (((size_t) png_ptr->width) * (((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth)) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth))) + 7) >> 3)) + 1);
      }
      return;
    }
  }
  png_compress_IDAT(png_ptr, 0, 0, 4);
}


/*** DEPENDENCIES:
void png_compress_IDAT(png_structrp png_ptr, png_const_bytep input, png_alloc_size_t input_len, int flush)
{
  if (png_ptr->zowner != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if (png_ptr->zbuffer_list == 0)
    {
      png_ptr->zbuffer_list = png_malloc(png_ptr, offsetof(png_compression_buffer, output) + png_ptr->zbuffer_size);
      png_ptr->zbuffer_list->next = 0;
    }
    else
      png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list->next);
    if (png_deflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), png_image_size(png_ptr)) != 0)
    {
      png_error(png_ptr, png_ptr->zstream.msg);
    }
    png_ptr->zstream.next_out = png_ptr->zbuffer_list->output;
    png_ptr->zstream.avail_out = png_ptr->zbuffer_size;
  }
  png_ptr->zstream.next_in = input;
  png_ptr->zstream.avail_in = 0;
  for (;;)
  {
    helper_png_compress_IDAT_1(&png_ptr, &input_len, flush);
  }

}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
void helper_png_write_start_row_1(png_structrp * const png_ptr_ref, png_alloc_size_t buf_size, png_byte filters)
{
  png_structrp png_ptr = *png_ptr_ref;
  int num_filters = 0;
  png_ptr->try_row = png_malloc(png_ptr, buf_size);
  if (filters & 0x10)
  {
    num_filters += 1;
  }
  if (filters & 0x20)
  {
    num_filters += 1;
  }
  if (filters & 0x40)
  {
    num_filters += 1;
  }
  if (filters & 0x80)
  {
    num_filters += 1;
  }
  if (num_filters > 1)
  {
    png_ptr->tst_row = png_malloc(png_ptr, buf_size);
  }
  *png_ptr_ref = png_ptr;
}


/*** DEPENDENCIES:
png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  png_alloc_size_t buf_size;
  int usr_pixel_depth;
  png_byte filters;
  (void) 0;
  usr_pixel_depth = png_ptr->usr_channels * png_ptr->usr_bit_depth;
  buf_size = ((usr_pixel_depth >= 8) ? (((size_t) png_ptr->width) * (((size_t) usr_pixel_depth) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) usr_pixel_depth)) + 7) >> 3)) + 1;
  png_ptr->transformed_pixel_depth = png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) usr_pixel_depth;
  png_ptr->row_buf = png_malloc(png_ptr, buf_size);
  png_ptr->row_buf[0] = 0;
  filters = png_ptr->do_filter;
  if (png_ptr->height == 1)
  {
    filters &= 0xff & (~((0x20 | 0x40) | 0x80));
  }
  if (png_ptr->width == 1)
  {
    filters &= 0xff & (~((0x10 | 0x40) | 0x80));
  }
  if (filters == 0)
  {
    filters = 0x08;
  }
  png_ptr->do_filter = filters;
  if (((filters & (((0x10 | 0x20) | 0x40) | 0x80)) != 0) && (png_ptr->try_row == 0))
  {
    helper_png_write_start_row_1(&png_ptr, buf_size, filters);
  }
  if ((filters & ((0x40 | 0x20) | 0x80)) != 0)
  {
    png_ptr->prev_row = png_calloc(png_ptr, buf_size);
  }
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
      png_ptr->usr_width = (((png_ptr->width + png_pass_inc[0]) - 1) - png_pass_start[0]) / png_pass_inc[0];
    }
    else
    {
      png_ptr->num_rows = png_ptr->height;
      png_ptr->usr_width = png_ptr->width;
    }
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->usr_width = png_ptr->width;
  }
}


/*** DEPENDENCIES:
png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef unsigned char png_byte
----------------------------
void helper_png_write_start_row_1(png_structrp * const png_ptr_ref, png_alloc_size_t buf_size, png_byte filters)
{
  png_structrp png_ptr = *png_ptr_ref;
  int num_filters = 0;
  png_ptr->try_row = png_malloc(png_ptr, buf_size);
  if (filters & 0x10)
  {
    num_filters += 1;
  }
  if (filters & 0x20)
  {
    num_filters += 1;
  }
  if (filters & 0x40)
  {
    num_filters += 1;
  }
  if (filters & 0x80)
  {
    num_filters += 1;
  }
  if (num_filters > 1)
  {
    png_ptr->tst_row = png_malloc(png_ptr, buf_size);
  }
  *png_ptr_ref = png_ptr;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_voidp png_calloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  ret = png_malloc(png_ptr, size);
  if (ret != 0)
  {
    memset(ret, 0, size);
  }
  return ret;
}


----------------------------
***/


void helper_helper_png_do_write_interlace_1_1(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  size_t pixel_bytes;
  dp = row;
  pixel_bytes = row_info->pixel_depth >> 3;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + (((size_t) i) * pixel_bytes);
    if (dp != sp)
    {
      memcpy(dp, sp, pixel_bytes);
    }
    dp += pixel_bytes;
  }

  break;
}


/*** DEPENDENCIES:
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void helper_helper_png_do_write_interlace_1_2(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  unsigned int shift;
  int d;
  int value;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  dp = row;
  shift = 6;
  d = 0;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + ((size_t) (i >> 2));
    value = ((*sp) >> ((3 - ((int) (i & 0x03))) << 1)) & 0x03;
    d |= value << shift;
    if (shift == 0)
    {
      shift = 6;
      *dp = (png_byte) d;
      dp += 1;
      d = 0;
    }
    else
      shift -= 2;
  }

  if (shift != 6)
  {
    *dp = (png_byte) d;
  }
  break;
}


/*** DEPENDENCIES:
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void helper_helper_png_do_write_interlace_1_3(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  unsigned int shift;
  int d;
  int value;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  dp = row;
  shift = 4;
  d = 0;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + ((size_t) (i >> 1));
    value = ((*sp) >> ((1 - ((int) (i & 0x01))) << 2)) & 0x0f;
    d |= value << shift;
    if (shift == 0)
    {
      shift = 4;
      *dp = (png_byte) d;
      dp += 1;
      d = 0;
    }
    else
      shift -= 4;
  }

  if (shift != 4)
  {
    *dp = (png_byte) d;
  }
  break;
}


/*** DEPENDENCIES:
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void helper_helper_png_do_write_interlace_1_4(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  unsigned int shift;
  int d;
  int value;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  dp = row;
  d = 0;
  shift = 7;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + ((size_t) (i >> 3));
    value = ((int) ((*sp) >> (7 - ((int) (i & 0x07))))) & 0x01;
    d |= value << shift;
    if (shift == 0)
    {
      shift = 7;
      *dp = (png_byte) d;
      dp += 1;
      d = 0;
    }
    else
      shift--;
    shift -= 1;
  }

  if (shift != 7)
  {
    *dp = (png_byte) d;
  }
  break;
}


/*** DEPENDENCIES:
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['row_info_ref is a mutable refrence to png_row_infop']
void helper_png_do_write_interlace_1(png_row_infop * const row_info_ref, png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7])
{
  png_row_infop row_info = *row_info_ref;
  switch (row_info->pixel_depth)
  {
    case 1:
    {
      helper_helper_png_do_write_interlace_1_4(row, pass, png_pass_start, png_pass_inc, row_info);
    }

    case 2:
    {
      helper_helper_png_do_write_interlace_1_2(row, pass, png_pass_start, png_pass_inc, row_info);
    }

    case 4:
    {
      helper_helper_png_do_write_interlace_1_3(row, pass, png_pass_start, png_pass_inc, row_info);
    }

    default:
    {
      helper_helper_png_do_write_interlace_1_1(row, pass, png_pass_start, png_pass_inc, row_info);
    }

  }

  row_info->width = (((row_info->width + png_pass_inc[pass]) - 1) - png_pass_start[pass]) / png_pass_inc[pass];
  row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) row_info->width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) row_info->width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  *row_info_ref = row_info;
}


/*** DEPENDENCIES:
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
void helper_helper_png_do_write_interlace_1_1(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  size_t pixel_bytes;
  dp = row;
  pixel_bytes = row_info->pixel_depth >> 3;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + (((size_t) i) * pixel_bytes);
    if (dp != sp)
    {
      memcpy(dp, sp, pixel_bytes);
    }
    dp += pixel_bytes;
  }

  break;
}


----------------------------
typedef unsigned char png_byte
----------------------------
void helper_helper_png_do_write_interlace_1_2(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  unsigned int shift;
  int d;
  int value;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  dp = row;
  shift = 6;
  d = 0;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + ((size_t) (i >> 2));
    value = ((*sp) >> ((3 - ((int) (i & 0x03))) << 1)) & 0x03;
    d |= value << shift;
    if (shift == 0)
    {
      shift = 6;
      *dp = (png_byte) d;
      dp += 1;
      d = 0;
    }
    else
      shift -= 2;
  }

  if (shift != 6)
  {
    *dp = (png_byte) d;
  }
  break;
}


----------------------------
void helper_helper_png_do_write_interlace_1_3(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  unsigned int shift;
  int d;
  int value;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  dp = row;
  shift = 4;
  d = 0;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + ((size_t) (i >> 1));
    value = ((*sp) >> ((1 - ((int) (i & 0x01))) << 2)) & 0x0f;
    d |= value << shift;
    if (shift == 0)
    {
      shift = 4;
      *dp = (png_byte) d;
      dp += 1;
      d = 0;
    }
    else
      shift -= 4;
  }

  if (shift != 4)
  {
    *dp = (png_byte) d;
  }
  break;
}


----------------------------
void helper_helper_png_do_write_interlace_1_4(png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7], png_row_infop row_info)
{
  png_bytep sp;
  png_bytep dp;
  unsigned int shift;
  int d;
  int value;
  png_uint_32 i;
  png_uint_32 row_width = row_info->width;
  dp = row;
  d = 0;
  shift = 7;
  for (i = png_pass_start[pass]; i < row_width; i += png_pass_inc[pass])
  {
    sp = row + ((size_t) (i >> 3));
    value = ((int) ((*sp) >> (7 - ((int) (i & 0x07))))) & 0x01;
    d |= value << shift;
    if (shift == 0)
    {
      shift = 7;
      *dp = (png_byte) d;
      dp += 1;
      d = 0;
    }
    else
      shift--;
    shift -= 1;
  }

  if (shift != 7)
  {
    *dp = (png_byte) d;
  }
  break;
}


----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void png_do_write_interlace(png_row_infop row_info, png_bytep row, int pass)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  (void) 0;
  if (pass < 6)
  {
    helper_png_do_write_interlace_1(&row_info, row, pass, png_pass_start, png_pass_inc);
  }
}


/*** DEPENDENCIES:
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
typedef unsigned char png_byte
----------------------------
void helper_png_do_write_interlace_1(png_row_infop * const row_info_ref, png_bytep row, int pass, static const png_byte png_pass_start[7], static const png_byte png_pass_inc[7])
{
  png_row_infop row_info = *row_info_ref;
  switch (row_info->pixel_depth)
  {
    case 1:
    {
      helper_helper_png_do_write_interlace_1_4(row, pass, png_pass_start, png_pass_inc, row_info);
    }

    case 2:
    {
      helper_helper_png_do_write_interlace_1_2(row, pass, png_pass_start, png_pass_inc, row_info);
    }

    case 4:
    {
      helper_helper_png_do_write_interlace_1_3(row, pass, png_pass_start, png_pass_inc, row_info);
    }

    default:
    {
      helper_helper_png_do_write_interlace_1_1(row, pass, png_pass_start, png_pass_inc, row_info);
    }

  }

  row_info->width = (((row_info->width + png_pass_inc[pass]) - 1) - png_pass_start[pass]) / png_pass_inc[pass];
  row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) row_info->width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) row_info->width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  *row_info_ref = row_info;
}


----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static size_t png_setup_up_row(png_structrp png_ptr, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  size_t i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 2;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < row_bytes; i += 1, rp += 1, pp += 1, dp += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff));
    sum += (v < 128) ? (v) : (256 - v);
    if (sum > lmins)
    {
      break;
    }
  }

  return sum;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static void png_setup_paeth_row_only(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep cp;
  png_bytep lp;
  size_t i;
  png_ptr->try_row[0] = 4;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff);
    pp += 1;
    rp += 1;
    dp += 1;
  }

  for (lp = png_ptr->row_buf + 1, cp = png_ptr->prev_row + 1; i < row_bytes; i += 1)
  {
    helper_png_setup_paeth_row_only_1(&rp, &dp, &pp, &cp, &lp);
  }

}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void helper_png_setup_paeth_row_only_1(png_bytep * const rp_ref, png_bytep * const dp_ref, png_bytep * const pp_ref, png_bytep * const cp_ref, png_bytep * const lp_ref)
{
  png_bytep rp = *rp_ref;
  png_bytep dp = *dp_ref;
  png_bytep pp = *pp_ref;
  png_bytep cp = *cp_ref;
  png_bytep lp = *lp_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  b = *pp;
  pp += 1;
  c = *cp;
  cp += 1;
  a = *lp;
  lp += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  p = ((pa <= pb) && (pa <= pc)) ? (a) : ((pb <= pc) ? (b) : (c));
  *dp = (png_byte) ((((int) (*rp)) - p) & 0xff);
  rp += 1;
  dp += 1;
  *rp_ref = rp;
  *dp_ref = dp;
  *pp_ref = pp;
  *cp_ref = cp;
  *lp_ref = lp;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_write_filtered_row(png_structrp png_ptr, png_bytep filtered_row, size_t full_row_length)
{
  (void) 0;
  (void) 0;
  png_compress_IDAT(png_ptr, filtered_row, full_row_length, 0);
  if (png_ptr->prev_row != 0)
  {
    png_bytep tptr;
    tptr = png_ptr->prev_row;
    png_ptr->prev_row = png_ptr->row_buf;
    png_ptr->row_buf = tptr;
  }
  png_write_finish_row(png_ptr);
  png_ptr->flush_rows += 1;
  if ((png_ptr->flush_dist > 0) && (png_ptr->flush_rows >= png_ptr->flush_dist))
  {
    png_write_flush(png_ptr);
  }
}


/*** DEPENDENCIES:
void png_write_finish_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  (void) 0;
  png_ptr->row_number += 1;
  if (png_ptr->row_number < png_ptr->num_rows)
  {
    return;
  }
  if (png_ptr->interlaced != 0)
  {
    png_ptr->row_number = 0;
    if ((png_ptr->transformations & 0x0002U) != 0)
    {
      png_ptr->pass += 1;
    }
    else
    {
      do
      {
        png_ptr->pass += 1;
        if (png_ptr->pass >= 7)
        {
          break;
        }
        png_ptr->usr_width = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
        if ((png_ptr->transformations & 0x0002U) != 0)
        {
          break;
        }
      }
      while ((png_ptr->usr_width == 0) || (png_ptr->num_rows == 0));
    }
    if (png_ptr->pass < 7)
    {
      if (png_ptr->prev_row != 0)
      {
        memset(png_ptr->prev_row, 0, (((png_ptr->usr_channels * png_ptr->usr_bit_depth) >= 8) ? (((size_t) png_ptr->width) * (((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth)) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth))) + 7) >> 3)) + 1);
      }
      return;
    }
  }
  png_compress_IDAT(png_ptr, 0, 0, 4);
}


----------------------------
void png_compress_IDAT(png_structrp png_ptr, png_const_bytep input, png_alloc_size_t input_len, int flush)
{
  if (png_ptr->zowner != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if (png_ptr->zbuffer_list == 0)
    {
      png_ptr->zbuffer_list = png_malloc(png_ptr, offsetof(png_compression_buffer, output) + png_ptr->zbuffer_size);
      png_ptr->zbuffer_list->next = 0;
    }
    else
      png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list->next);
    if (png_deflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), png_image_size(png_ptr)) != 0)
    {
      png_error(png_ptr, png_ptr->zstream.msg);
    }
    png_ptr->zstream.next_out = png_ptr->zbuffer_list->output;
    png_ptr->zstream.avail_out = png_ptr->zbuffer_size;
  }
  png_ptr->zstream.next_in = input;
  png_ptr->zstream.avail_in = 0;
  for (;;)
  {
    helper_png_compress_IDAT_1(&png_ptr, &input_len, flush);
  }

}


----------------------------
typedef unsigned char png_byte
----------------------------
void png_write_flush(png_structrp png_ptr)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (png_ptr->row_number >= png_ptr->num_rows)
  {
    return;
  }
  png_compress_IDAT(png_ptr, 0, 0, 2);
  png_ptr->flush_rows = 0;
  png_flush(png_ptr);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_setup_sub_row_only(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep lp;
  size_t i;
  png_ptr->try_row[0] = 1;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1; i < bpp; i += 1, rp += 1, dp += 1)
  {
    *dp = *rp;
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1, rp += 1, lp += 1, dp += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((int) (*lp))) & 0xff);
  }

}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static size_t png_setup_avg_row(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep lp;
  png_uint_32 i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 3;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - (((int) (*pp)) / 2)) & 0xff));
    pp += 1;
    rp += 1;
    dp += 1;
    sum += (v < 128) ? (v) : (256 - v);
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((((int) (*pp)) + ((int) (*lp))) / 2)) & 0xff));
    lp += 1;
    pp += 1;
    rp += 1;
    dp += 1;
    sum += (v < 128) ? (v) : (256 - v);
    if (sum > lmins)
    {
      break;
    }
  }

  return sum;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_setup_avg_row_only(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep lp;
  png_uint_32 i;
  png_ptr->try_row[0] = 3;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - (((int) (*pp)) / 2)) & 0xff);
    pp += 1;
    rp += 1;
    dp += 1;
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((((int) (*pp)) + ((int) (*lp))) / 2)) & 0xff);
    lp += 1;
    pp += 1;
    rp += 1;
    dp += 1;
  }

}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static size_t png_setup_sub_row(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep lp;
  size_t i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 1;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1; i < bpp; i += 1, rp += 1, dp += 1)
  {
    v = (*dp = *rp);
    sum += (v < 128) ? (v) : (256 - v);
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1, rp += 1, lp += 1, dp += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((int) (*lp))) & 0xff));
    sum += (v < 128) ? (v) : (256 - v);
    if (sum > lmins)
    {
      break;
    }
  }

  return sum;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void png_setup_up_row_only(png_structrp png_ptr, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  size_t i;
  png_ptr->try_row[0] = 2;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < row_bytes; i += 1, rp += 1, pp += 1, dp += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff);
  }

}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static size_t png_setup_paeth_row(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep cp;
  png_bytep lp;
  size_t i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 4;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff));
    pp += 1;
    rp += 1;
    dp += 1;
    sum += (v < 128) ? (v) : (256 - v);
  }

  for (lp = png_ptr->row_buf + 1, cp = png_ptr->prev_row + 1; i < row_bytes; i += 1)
  {
    helper_png_setup_paeth_row_1(&rp, &dp, &pp, &cp, &lp, &sum, &v, lmins);
  }

  return sum;
}


/*** DEPENDENCIES:
void helper_png_setup_paeth_row_1(png_bytep * const rp_ref, png_bytep * const dp_ref, png_bytep * const pp_ref, png_bytep * const cp_ref, png_bytep * const lp_ref, size_t * const sum_ref, unsigned int * const v_ref, size_t lmins)
{
  png_bytep rp = *rp_ref;
  png_bytep dp = *dp_ref;
  png_bytep pp = *pp_ref;
  png_bytep cp = *cp_ref;
  png_bytep lp = *lp_ref;
  size_t sum = *sum_ref;
  unsigned int v = *v_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  b = *pp;
  pp += 1;
  c = *cp;
  cp += 1;
  a = *lp;
  lp += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  p = ((pa <= pb) && (pa <= pc)) ? (a) : ((pb <= pc) ? (b) : (c));
  v = (*dp = (png_byte) ((((int) (*rp)) - p) & 0xff));
  rp += 1;
  dp += 1;
  sum += (v < 128) ? (v) : (256 - v);
  if (sum > lmins)
  {
    break;
  }
  *rp_ref = rp;
  *dp_ref = dp;
  *pp_ref = pp;
  *cp_ref = cp;
  *lp_ref = lp;
  *sum_ref = sum;
  *v_ref = v;
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void png_write_find_filter(png_structrp png_ptr, png_row_infop row_info)
{
  unsigned int filter_to_do = png_ptr->do_filter;
  png_bytep row_buf;
  png_bytep best_row;
  png_uint_32 bpp;
  size_t mins;
  size_t row_bytes = row_info->rowbytes;
  (void) 0;
  bpp = (row_info->pixel_depth + 7) >> 3;
  row_buf = png_ptr->row_buf;
  mins = ((size_t) (-1)) - 256;
  best_row = png_ptr->row_buf;
  if ((((size_t) (-1)) / 128) <= row_bytes)
  {
    filter_to_do &= 0U - filter_to_do;
  }
  else
    if (((filter_to_do & 0x08) != 0) && (filter_to_do != 0x08))
  {
    png_bytep rp;
    size_t sum = 0;
    size_t i;
    unsigned int v;
    {
      for (i = 0, rp = row_buf + 1; i < row_bytes; i += 1, rp += 1)
      {
        v = *rp;
        sum += (v < 128) ? (v) : (256 - v);
      }

    }
    mins = sum;
  }
  if (filter_to_do == 0x10)
  {
    png_setup_sub_row_only(png_ptr, bpp, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x10) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_sub_row(png_ptr, bpp, row_bytes, lmins);
    if (sum < mins)
    {
      mins = sum;
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  if (filter_to_do == 0x20)
  {
    png_setup_up_row_only(png_ptr, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x20) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_up_row(png_ptr, row_bytes, lmins);
    if (sum < mins)
    {
      mins = sum;
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  if (filter_to_do == 0x40)
  {
    png_setup_avg_row_only(png_ptr, bpp, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x40) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_avg_row(png_ptr, bpp, row_bytes, lmins);
    if (sum < mins)
    {
      mins = sum;
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  if (filter_to_do == 0x80)
  {
    png_setup_paeth_row_only(png_ptr, bpp, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x80) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_paeth_row(png_ptr, bpp, row_bytes, lmins);
    if (sum < mins)
    {
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  png_write_filtered_row(png_ptr, best_row, row_info->rowbytes + 1);
}


/*** DEPENDENCIES:
static size_t png_setup_up_row(png_structrp png_ptr, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  size_t i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 2;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < row_bytes; i += 1, rp += 1, pp += 1, dp += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff));
    sum += (v < 128) ? (v) : (256 - v);
    if (sum > lmins)
    {
      break;
    }
  }

  return sum;
}


----------------------------
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
typedef png_row_info *png_row_infop
----------------------------
static void png_setup_paeth_row_only(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep cp;
  png_bytep lp;
  size_t i;
  png_ptr->try_row[0] = 4;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff);
    pp += 1;
    rp += 1;
    dp += 1;
  }

  for (lp = png_ptr->row_buf + 1, cp = png_ptr->prev_row + 1; i < row_bytes; i += 1)
  {
    helper_png_setup_paeth_row_only_1(&rp, &dp, &pp, &cp, &lp);
  }

}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
----------------------------
static void png_write_filtered_row(png_structrp png_ptr, png_bytep filtered_row, size_t full_row_length)
{
  (void) 0;
  (void) 0;
  png_compress_IDAT(png_ptr, filtered_row, full_row_length, 0);
  if (png_ptr->prev_row != 0)
  {
    png_bytep tptr;
    tptr = png_ptr->prev_row;
    png_ptr->prev_row = png_ptr->row_buf;
    png_ptr->row_buf = tptr;
  }
  png_write_finish_row(png_ptr);
  png_ptr->flush_rows += 1;
  if ((png_ptr->flush_dist > 0) && (png_ptr->flush_rows >= png_ptr->flush_dist))
  {
    png_write_flush(png_ptr);
  }
}


----------------------------
static void png_setup_sub_row_only(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep lp;
  size_t i;
  png_ptr->try_row[0] = 1;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1; i < bpp; i += 1, rp += 1, dp += 1)
  {
    *dp = *rp;
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1, rp += 1, lp += 1, dp += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((int) (*lp))) & 0xff);
  }

}


----------------------------
static size_t png_setup_avg_row(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep lp;
  png_uint_32 i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 3;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - (((int) (*pp)) / 2)) & 0xff));
    pp += 1;
    rp += 1;
    dp += 1;
    sum += (v < 128) ? (v) : (256 - v);
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((((int) (*pp)) + ((int) (*lp))) / 2)) & 0xff));
    lp += 1;
    pp += 1;
    rp += 1;
    dp += 1;
    sum += (v < 128) ? (v) : (256 - v);
    if (sum > lmins)
    {
      break;
    }
  }

  return sum;
}


----------------------------
static void png_setup_avg_row_only(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep lp;
  png_uint_32 i;
  png_ptr->try_row[0] = 3;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - (((int) (*pp)) / 2)) & 0xff);
    pp += 1;
    rp += 1;
    dp += 1;
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((((int) (*pp)) + ((int) (*lp))) / 2)) & 0xff);
    lp += 1;
    pp += 1;
    rp += 1;
    dp += 1;
  }

}


----------------------------
typedef png_struct *png_structrp
----------------------------
static size_t png_setup_sub_row(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep lp;
  size_t i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 1;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1; i < bpp; i += 1, rp += 1, dp += 1)
  {
    v = (*dp = *rp);
    sum += (v < 128) ? (v) : (256 - v);
  }

  for (lp = png_ptr->row_buf + 1; i < row_bytes; i += 1, rp += 1, lp += 1, dp += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((int) (*lp))) & 0xff));
    sum += (v < 128) ? (v) : (256 - v);
    if (sum > lmins)
    {
      break;
    }
  }

  return sum;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void png_setup_up_row_only(png_structrp png_ptr, size_t row_bytes)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  size_t i;
  png_ptr->try_row[0] = 2;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < row_bytes; i += 1, rp += 1, pp += 1, dp += 1)
  {
    *dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff);
  }

}


----------------------------
typedef png_byte *png_bytep
----------------------------
static size_t png_setup_paeth_row(png_structrp png_ptr, png_uint_32 bpp, size_t row_bytes, size_t lmins)
{
  png_bytep rp;
  png_bytep dp;
  png_bytep pp;
  png_bytep cp;
  png_bytep lp;
  size_t i;
  size_t sum = 0;
  unsigned int v;
  png_ptr->try_row[0] = 4;
  for (i = 0, rp = png_ptr->row_buf + 1, dp = png_ptr->try_row + 1, pp = png_ptr->prev_row + 1; i < bpp; i += 1)
  {
    v = (*dp = (png_byte) ((((int) (*rp)) - ((int) (*pp))) & 0xff));
    pp += 1;
    rp += 1;
    dp += 1;
    sum += (v < 128) ? (v) : (256 - v);
  }

  for (lp = png_ptr->row_buf + 1, cp = png_ptr->prev_row + 1; i < row_bytes; i += 1)
  {
    helper_png_setup_paeth_row_1(&rp, &dp, &pp, &cp, &lp, &sum, &v, lmins);
  }

  return sum;
}


----------------------------
***/


void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_string, png_const_bytep data, size_t length)
{
  png_write_complete_chunk(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), data, length);
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef const png_byte *png_const_bytep
----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_IEND(png_structrp png_ptr)
{
  (void) 0;
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0), 0, 0);
  png_ptr->mode |= 0x10U;
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_sig(png_structrp png_ptr)
{
  png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  png_ptr->io_state = 0x0002 | 0x0010;
  png_write_data(png_ptr, &png_signature[png_ptr->sig_bytes], (size_t) (8 - png_ptr->sig_bytes));
  if (png_ptr->sig_bytes < 3)
  {
    png_ptr->mode |= 0x1000U;
  }
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr->write_data_fn != 0)
  {
    (*png_ptr->write_data_fn)(png_ptr, (png_bytep) ((void *) ((const void *) data)), length);
  }
  else
    png_error(png_ptr, "Call to NULL write function");
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_IHDR(png_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int compression_type, int filter_type, int interlace_type)
{
  png_byte buf[13];
  int is_invalid_depth;
  (void) 0;
  switch (color_type)
  {
    case 0:
    {
      switch (bit_depth)
      {
        case 1:

        case 2:

        case 4:

        case 8:

        case 16:
        {
          png_ptr->channels = 1;
          break;
        }

        default:
        {
          png_error(png_ptr, "Invalid bit depth for grayscale image");
        }

      }

      break;
    }

    case 2:
    {
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
      {
        png_error(png_ptr, "Invalid bit depth for RGB image");
      }
      png_ptr->channels = 3;
      break;
    }

    case 2 | 1:
    {
      switch (bit_depth)
      {
        case 1:

        case 2:

        case 4:

        case 8:
        {
          png_ptr->channels = 1;
          break;
        }

        default:
        {
          png_error(png_ptr, "Invalid bit depth for paletted image");
        }

      }

      break;
    }

    case 4:
    {
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
      {
        png_error(png_ptr, "Invalid bit depth for grayscale+alpha image");
      }
      png_ptr->channels = 2;
      break;
    }

    case 2 | 4:
    {
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
      {
        png_error(png_ptr, "Invalid bit depth for RGBA image");
      }
      png_ptr->channels = 4;
      break;
    }

    default:
    {
      png_error(png_ptr, "Invalid image color type specified");
    }

  }

  if (compression_type != 0)
  {
    png_warning(png_ptr, "Invalid compression type specified");
    compression_type = 0;
  }
  if (filter_type != 0)
  {
    png_warning(png_ptr, "Invalid filter type specified");
    filter_type = 0;
  }
  if ((interlace_type != 0) && (interlace_type != 1))
  {
    png_warning(png_ptr, "Invalid interlace type specified");
    interlace_type = 1;
  }
  png_ptr->bit_depth = (png_byte) bit_depth;
  png_ptr->color_type = (png_byte) color_type;
  png_ptr->interlaced = (png_byte) interlace_type;
  png_ptr->compression_type = (png_byte) compression_type;
  png_ptr->width = width;
  png_ptr->height = height;
  png_ptr->pixel_depth = (png_byte) (bit_depth * png_ptr->channels);
  png_ptr->rowbytes = (png_ptr->pixel_depth >= 8) ? (((size_t) width) * (((size_t) png_ptr->pixel_depth) >> 3)) : (((((size_t) width) * ((size_t) png_ptr->pixel_depth)) + 7) >> 3);
  png_ptr->usr_width = png_ptr->width;
  png_ptr->usr_bit_depth = png_ptr->bit_depth;
  png_ptr->usr_channels = png_ptr->channels;
  png_save_uint_32(buf, width);
  png_save_uint_32(buf + 4, height);
  buf[8] = (png_byte) bit_depth;
  buf[9] = (png_byte) color_type;
  buf[10] = (png_byte) compression_type;
  buf[11] = (png_byte) filter_type;
  buf[12] = (png_byte) interlace_type;
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 72) << 16)) | (((png_uint_32) 68) << 8)) | (((png_uint_32) 82) << 0), buf, 13);
  if (png_ptr->do_filter == 0x00)
  {
    if ((png_ptr->color_type == (2 | 1)) || (png_ptr->bit_depth < 8))
    {
      png_ptr->do_filter = 0x08;
    }
    else
      png_ptr->do_filter = (((0x08 | 0x10) | 0x20) | 0x40) | 0x80;
  }
  png_ptr->mode = 0x01;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


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


void png_write_sBIT(png_structrp png_ptr, png_const_color_8p sbit, int color_type)
{
  png_byte buf[4];
  size_t size;
  (void) 0;
  if ((color_type & 2) != 0)
  {
    png_byte maxbits;
    maxbits = (png_byte) ((color_type == (2 | 1)) ? (8) : (png_ptr->usr_bit_depth));
    if ((((((sbit->red == 0) || (sbit->red > maxbits)) || (sbit->green == 0)) || (sbit->green > maxbits)) || (sbit->blue == 0)) || (sbit->blue > maxbits))
    {
      png_warning(png_ptr, "Invalid sBIT depth specified");
      return;
    }
    buf[0] = sbit->red;
    buf[1] = sbit->green;
    buf[2] = sbit->blue;
    size = 3;
  }
  else
  {
    if ((sbit->gray == 0) || (sbit->gray > png_ptr->usr_bit_depth))
    {
      png_warning(png_ptr, "Invalid sBIT depth specified");
      return;
    }
    buf[0] = sbit->gray;
    size = 1;
  }
  if ((color_type & 4) != 0)
  {
    if ((sbit->alpha == 0) || (sbit->alpha > png_ptr->usr_bit_depth))
    {
      png_warning(png_ptr, "Invalid sBIT depth specified");
      return;
    }
    buf[size] = sbit->alpha;
    size += 1;
  }
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 115) << 24) | (((png_uint_32) 66) << 16)) | (((png_uint_32) 73) << 8)) | (((png_uint_32) 84) << 0), buf, size);
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef const png_color_8 *png_const_color_8p
----------------------------
***/


void png_write_tRNS(png_structrp png_ptr, png_const_bytep trans_alpha, png_const_color_16p tran, int num_trans, int color_type)
{
  png_byte buf[6];
  (void) 0;
  if (color_type == (2 | 1))
  {
    if ((num_trans <= 0) || (num_trans > ((int) png_ptr->num_palette)))
    {
      png_app_warning(png_ptr, "Invalid number of transparent colors specified");
      return;
    }
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0), trans_alpha, (size_t) num_trans);
  }
  else
    if (color_type == 0)
  {
    if (tran->gray >= (1 << png_ptr->bit_depth))
    {
      png_app_warning(png_ptr, "Ignoring attempt to write tRNS chunk out-of-range for bit_depth");
      return;
    }
    png_save_uint_16(buf, tran->gray);
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0), buf, 2);
  }
  else
    if (color_type == 2)
  {
    png_save_uint_16(buf, tran->red);
    png_save_uint_16(buf + 2, tran->green);
    png_save_uint_16(buf + 4, tran->blue);
    if ((png_ptr->bit_depth == 8) && (((buf[0] | buf[2]) | buf[4]) != 0))
    {
      png_app_warning(png_ptr, "Ignoring attempt to write 16-bit tRNS chunk when bit_depth is 8");
      return;
    }
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0), buf, 6);
  }
  else
  {
    png_app_warning(png_ptr, "Can't write tRNS with an alpha channel");
  }
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
void png_save_uint_16(png_bytep buf, unsigned int i)
{
  buf[0] = (png_byte) ((i >> 8) & 0xffU);
  buf[1] = (png_byte) (i & 0xffU);
}


----------------------------
void png_app_warning(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x200000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef const png_color_16 *png_const_color_16p
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
***/


void png_write_bKGD(png_structrp png_ptr, png_const_color_16p back, int color_type)
{
  png_byte buf[6];
  (void) 0;
  if (color_type == (2 | 1))
  {
    if (back->index >= png_ptr->num_palette)
    {
      png_warning(png_ptr, "Invalid background palette index");
      return;
    }
    buf[0] = back->index;
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0), buf, 1);
  }
  else
    if ((color_type & 2) != 0)
  {
    png_save_uint_16(buf, back->red);
    png_save_uint_16(buf + 2, back->green);
    png_save_uint_16(buf + 4, back->blue);
    if ((png_ptr->bit_depth == 8) && (((buf[0] | buf[2]) | buf[4]) != 0))
    {
      png_warning(png_ptr, "Ignoring attempt to write 16-bit bKGD chunk when bit_depth is 8");
      return;
    }
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0), buf, 6);
  }
  else
  {
    if (back->gray >= (1 << png_ptr->bit_depth))
    {
      png_warning(png_ptr, "Ignoring attempt to write bKGD chunk out-of-range for bit_depth");
      return;
    }
    png_save_uint_16(buf, back->gray);
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0), buf, 2);
  }
}


/*** DEPENDENCIES:
void png_save_uint_16(png_bytep buf, unsigned int i)
{
  buf[0] = (png_byte) ((i >> 8) & 0xffU);
  buf[1] = (png_byte) (i & 0xffU);
}


----------------------------
typedef unsigned char png_byte
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
typedef const png_color_16 *png_const_color_16p
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static void png_write_complete_chunk(png_structrp png_ptr, png_uint_32 chunk_name, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (length > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "length exceeds PNG maximum");
  }
  png_write_chunk_header(png_ptr, chunk_name, (png_uint_32) length);
  png_write_chunk_data(png_ptr, data, length);
  png_write_chunk_end(png_ptr);
}


----------------------------
***/


void png_write_hIST(png_structrp png_ptr, png_const_uint_16p hist, int num_hist)
{
  int i;
  png_byte buf[3];
  (void) 0;
  if (num_hist > ((int) png_ptr->num_palette))
  {
    (void) 0;
    png_warning(png_ptr, "Invalid number of histogram entries specified");
    return;
  }
  png_write_chunk_header(png_ptr, (((((png_uint_32) 104) << 24) | (((png_uint_32) 73) << 16)) | (((png_uint_32) 83) << 8)) | (((png_uint_32) 84) << 0), (png_uint_32) (num_hist * 2));
  for (i = 0; i < num_hist; i += 1)
  {
    png_save_uint_16(buf, hist[i]);
    png_write_chunk_data(png_ptr, buf, 2);
  }

  png_write_chunk_end(png_ptr);
}


/*** DEPENDENCIES:
void png_save_uint_16(png_bytep buf, unsigned int i)
{
  buf[0] = (png_byte) ((i >> 8) & 0xffU);
  buf[1] = (png_byte) (i & 0xffU);
}


----------------------------
typedef const png_uint_16 *png_const_uint_16p
----------------------------
void png_write_chunk_end(png_structrp png_ptr)
{
  png_byte buf[4];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0080;
  png_save_uint_32(buf, png_ptr->crc);
  png_write_data(png_ptr, buf, 4);
}


----------------------------
typedef unsigned char png_byte
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
static void png_write_chunk_header(png_structrp png_ptr, png_uint_32 chunk_name, png_uint_32 length)
{
  png_byte buf[8];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0020;
  png_save_uint_32(buf, length);
  png_save_uint_32(buf + 4, chunk_name);
  png_write_data(png_ptr, buf, 8);
  png_ptr->chunk_name = chunk_name;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_ptr->io_state = 0x0002 | 0x0040;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
void png_write_chunk_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if ((data != 0) && (length > 0))
  {
    png_write_data(png_ptr, data, length);
    png_calculate_crc(png_ptr, data, length);
  }
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_PLTE(png_structrp png_ptr, png_const_colorp palette, png_uint_32 num_pal)
{
  png_uint_32 max_palette_length;
  png_uint_32 i;
  png_const_colorp pal_ptr;
  png_byte buf[3];
  (void) 0;
  max_palette_length = (png_ptr->color_type == (2 | 1)) ? (1 << png_ptr->bit_depth) : (256);
  if ((num_pal == 0) || (num_pal > max_palette_length))
  {
    if (png_ptr->color_type == (2 | 1))
    {
      png_error(png_ptr, "Invalid number of colors in palette");
    }
    else
    {
      png_warning(png_ptr, "Invalid number of colors in palette");
      return;
    }
  }
  if ((png_ptr->color_type & 2) == 0)
  {
    png_warning(png_ptr, "Ignoring request to write a PLTE chunk in grayscale PNG");
    return;
  }
  png_ptr->num_palette = (png_uint_16) num_pal;
  (void) 0;
  png_write_chunk_header(png_ptr, (((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0), (png_uint_32) (num_pal * 3));
  for (i = 0, pal_ptr = palette; i < num_pal; i += 1, pal_ptr += 1)
  {
    buf[0] = pal_ptr->red;
    buf[1] = pal_ptr->green;
    buf[2] = pal_ptr->blue;
    png_write_chunk_data(png_ptr, buf, 3);
  }

  png_write_chunk_end(png_ptr);
  png_ptr->mode |= 0x02;
}


/*** DEPENDENCIES:
void png_write_chunk_end(png_structrp png_ptr)
{
  png_byte buf[4];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0080;
  png_save_uint_32(buf, png_ptr->crc);
  png_write_data(png_ptr, buf, 4);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
static void png_write_chunk_header(png_structrp png_ptr, png_uint_32 chunk_name, png_uint_32 length)
{
  png_byte buf[8];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0020;
  png_save_uint_32(buf, length);
  png_save_uint_32(buf + 4, chunk_name);
  png_write_data(png_ptr, buf, 8);
  png_ptr->chunk_name = chunk_name;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_ptr->io_state = 0x0002 | 0x0040;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
void png_write_chunk_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr == 0)
  {
    return;
  }
  if ((data != 0) && (length > 0))
  {
    png_write_data(png_ptr, data, length);
    png_calculate_crc(png_ptr, data, length);
  }
}


----------------------------
typedef const png_color *png_const_colorp
----------------------------
typedef struct png_struct_def png_struct
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


void png_write_chunk_start(png_structrp png_ptr, png_const_bytep chunk_string, png_uint_32 length)
{
  png_write_chunk_header(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), length);
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
static void png_write_chunk_header(png_structrp png_ptr, png_uint_32 chunk_name, png_uint_32 length)
{
  png_byte buf[8];
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_state = 0x0002 | 0x0020;
  png_save_uint_32(buf, length);
  png_save_uint_32(buf + 4, chunk_name);
  png_write_data(png_ptr, buf, 8);
  png_ptr->chunk_name = chunk_name;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_ptr->io_state = 0x0002 | 0x0040;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


