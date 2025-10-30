#include <limits.h>
#include <png.h>
#include <pngconf.h>
#include <pnglibconf.h>
#include <pngxpriv.h>
#include <pngxrbmp.c>
#include <pngxtern.h>
#include <pngxutil.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char png_byte;
typedef short png_int_16;
typedef unsigned short png_uint_16;
typedef int png_int_32;
typedef unsigned int png_uint_32;
typedef size_t png_size_t;
typedef ptrdiff_t png_ptrdiff_t;
typedef size_t png_alloc_size_t;
typedef png_int_32 png_fixed_point;
typedef void *png_voidp;
typedef const void *png_const_voidp;
typedef png_byte *png_bytep;
typedef const png_byte *png_const_bytep;
typedef png_uint_32 *png_uint_32p;
typedef const png_uint_32 *png_const_uint_32p;
typedef png_int_32 *png_int_32p;
typedef const png_int_32 *png_const_int_32p;
typedef png_uint_16 *png_uint_16p;
typedef const png_uint_16 *png_const_uint_16p;
typedef png_int_16 *png_int_16p;
typedef const png_int_16 *png_const_int_16p;
typedef char *png_charp;
typedef const char *png_const_charp;
typedef png_fixed_point *png_fixed_point_p;
typedef const png_fixed_point *png_const_fixed_point_p;
typedef size_t *png_size_tp;
typedef const size_t *png_const_size_tp;
typedef FILE *png_FILE_p;
typedef png_byte **png_bytepp;
typedef png_uint_32 **png_uint_32pp;
typedef png_int_32 **png_int_32pp;
typedef png_uint_16 **png_uint_16pp;
typedef png_int_16 **png_int_16pp;
typedef const char **png_const_charpp;
typedef char **png_charpp;
typedef png_fixed_point **png_fixed_point_pp;
typedef char ***png_charppp;
typedef char *png_libpng_version_1_6_40;
typedef struct png_struct_def png_struct;
typedef const png_struct *png_const_structp;
typedef png_struct *png_structp;
typedef png_struct **png_structpp;
typedef struct png_info_def png_info;
typedef png_info *png_infop;
typedef const png_info *png_const_infop;
typedef png_info **png_infopp;
typedef png_struct *png_structrp;
typedef const png_struct *png_const_structrp;
typedef png_info *png_inforp;
typedef const png_info *png_const_inforp;
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color;
typedef png_color *png_colorp;
typedef const png_color *png_const_colorp;
typedef png_color **png_colorpp;
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16;
typedef png_color_16 *png_color_16p;
typedef const png_color_16 *png_const_color_16p;
typedef png_color_16 **png_color_16pp;
typedef struct png_color_8_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
  png_byte gray;
  png_byte alpha;
} png_color_8;
typedef png_color_8 *png_color_8p;
typedef const png_color_8 *png_const_color_8p;
typedef png_color_8 **png_color_8pp;
typedef struct png_sPLT_entry_struct
{
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 alpha;
  png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry *png_sPLT_entryp;
typedef const png_sPLT_entry *png_const_sPLT_entryp;
typedef png_sPLT_entry **png_sPLT_entrypp;
typedef struct png_sPLT_struct
{
  png_charp name;
  png_byte depth;
  png_sPLT_entryp entries;
  png_int_32 nentries;
} png_sPLT_t;
typedef png_sPLT_t *png_sPLT_tp;
typedef const png_sPLT_t *png_const_sPLT_tp;
typedef png_sPLT_t **png_sPLT_tpp;
typedef struct png_time_struct
{
  png_uint_16 year;
  png_byte month;
  png_byte day;
  png_byte hour;
  png_byte minute;
  png_byte second;
} png_time;
typedef png_time *png_timep;
typedef const png_time *png_const_timep;
typedef png_time **png_timepp;
typedef struct png_unknown_chunk_t
{
  png_byte name[5];
  png_byte *data;
  size_t size;
  png_byte location;
} png_unknown_chunk;
typedef png_unknown_chunk *png_unknown_chunkp;
typedef const png_unknown_chunk *png_const_unknown_chunkp;
typedef png_unknown_chunk **png_unknown_chunkpp;
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info;
typedef png_row_info *png_row_infop;
typedef png_row_info **png_row_infopp;
typedef void (*png_error_ptr)(png_structp, png_const_charp);
typedef void (*png_rw_ptr)(png_structp, png_bytep, size_t);
typedef void (*png_flush_ptr)(png_structp);
typedef void (*png_read_status_ptr)(png_structp, png_uint_32, int);
typedef void (*png_write_status_ptr)(png_structp, png_uint_32, int);
typedef png_voidp (*png_malloc_ptr)(png_structp, png_alloc_size_t);
typedef void (*png_free_ptr)(png_structp, png_voidp);
extern png_uint_32 png_access_version_number(void);
extern void png_set_sig_bytes(png_structrp png_ptr, int num_bytes);
extern int png_sig_cmp(png_const_bytep sig, size_t start, size_t num_to_check);
extern png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
extern png_structp png_create_write_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
extern size_t png_get_compression_buffer_size(png_const_structrp png_ptr);
extern void png_set_compression_buffer_size(png_structrp png_ptr, size_t size);
extern void png_longjmp(png_const_structrp png_ptr, int val);
extern int png_reset_zstream(png_structrp png_ptr);
extern void png_write_sig(png_structrp png_ptr);
extern void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_name, png_const_bytep data, size_t length);
extern void png_write_chunk_start(png_structrp png_ptr, png_const_bytep chunk_name, png_uint_32 length);
extern void png_write_chunk_data(png_structrp png_ptr, png_const_bytep data, size_t length);
extern void png_write_chunk_end(png_structrp png_ptr);
extern png_infop png_create_info_struct(png_const_structrp png_ptr);
extern void png_info_init_3(png_infopp info_ptr, size_t png_info_struct_size);
extern void png_write_info_before_PLTE(png_structrp png_ptr, png_const_inforp info_ptr);
extern void png_write_info(png_structrp png_ptr, png_const_inforp info_ptr);
extern void png_read_info(png_structrp png_ptr, png_inforp info_ptr);
extern int png_set_interlace_handling(png_structrp png_ptr);
extern void png_set_flush(png_structrp png_ptr, int nrows);
extern void png_write_flush(png_structrp png_ptr);
extern void png_start_read_image(png_structrp png_ptr);
extern void png_read_update_info(png_structrp png_ptr, png_inforp info_ptr);
extern void png_read_rows(png_structrp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows);
extern void png_read_row(png_structrp png_ptr, png_bytep row, png_bytep display_row);
extern void png_read_image(png_structrp png_ptr, png_bytepp image);
extern void png_write_row(png_structrp png_ptr, png_const_bytep row);
extern void png_write_rows(png_structrp png_ptr, png_bytepp row, png_uint_32 num_rows);
extern void png_write_image(png_structrp png_ptr, png_bytepp image);
extern void png_write_end(png_structrp png_ptr, png_inforp info_ptr);
extern void png_read_end(png_structrp png_ptr, png_inforp info_ptr);
extern void png_destroy_info_struct(png_const_structrp png_ptr, png_infopp info_ptr_ptr);
extern void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);
extern void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr);
extern void png_set_crc_action(png_structrp png_ptr, int crit_action, int ancil_action);
extern void png_set_filter(png_structrp png_ptr, int method, int filters);
extern void png_set_compression_level(png_structrp png_ptr, int level);
extern void png_set_compression_mem_level(png_structrp png_ptr, int mem_level);
extern void png_set_compression_strategy(png_structrp png_ptr, int strategy);
extern void png_set_compression_window_bits(png_structrp png_ptr, int window_bits);
extern void png_set_compression_method(png_structrp png_ptr, int method);
extern void png_init_io(png_structrp png_ptr, png_FILE_p fp);
extern void png_set_error_fn(png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn);
extern png_voidp png_get_error_ptr(png_const_structrp png_ptr);
extern void png_set_write_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn);
extern void png_set_read_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);
extern png_voidp png_get_io_ptr(png_const_structrp png_ptr);
extern void png_set_read_status_fn(png_structrp png_ptr, png_read_status_ptr read_row_fn);
extern void png_set_write_status_fn(png_structrp png_ptr, png_write_status_ptr write_row_fn);
extern png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size);
extern png_voidp png_calloc(png_const_structrp png_ptr, png_alloc_size_t size);
extern png_voidp png_malloc_warn(png_const_structrp png_ptr, png_alloc_size_t size);
extern void png_free(png_const_structrp png_ptr, png_voidp ptr);
extern void png_free_data(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 free_me, int num);
extern void png_data_freer(png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask);
extern void png_error(png_const_structrp png_ptr, png_const_charp error_message);
extern void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message);
extern void png_warning(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_benign_error(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_set_benign_errors(png_structrp png_ptr, int allowed);
extern png_uint_32 png_get_valid(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag);
extern size_t png_get_rowbytes(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern void png_set_rows(png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers);
extern png_byte png_get_channels(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_image_width(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_image_height(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_bit_depth(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_color_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_filter_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_interlace_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_compression_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_x_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_y_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_fixed_point png_get_pixel_aspect_ratio_fixed(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_x_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_y_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_x_offset_microns(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_y_offset_microns(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_const_bytep png_get_signature(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_color_16p *background);
extern void png_set_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_16p background);
extern png_uint_32 png_get_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist);
extern void png_set_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist);
extern png_uint_32 png_get_IHDR(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method);
extern void png_set_IHDR(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method);
extern png_uint_32 png_get_PLTE(png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette);
extern void png_set_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette);
extern png_uint_32 png_get_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit);
extern void png_set_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit);
extern png_uint_32 png_get_tRNS(png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color);
extern void png_set_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color);
extern void png_set_keep_unknown_chunks(png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks);
extern int png_handle_as_unknown(png_const_structrp png_ptr, png_const_bytep chunk_name);
extern void png_set_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns);
extern void png_set_unknown_chunk_location(png_const_structrp png_ptr, png_inforp info_ptr, int chunk, int location);
extern int png_get_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_unknown_chunkpp entries);
extern void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask);
extern void png_read_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params);
extern void png_write_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params);
extern png_const_charp png_get_copyright(png_const_structrp png_ptr);
extern png_const_charp png_get_header_ver(png_const_structrp png_ptr);
extern png_const_charp png_get_header_version(png_const_structrp png_ptr);
extern png_const_charp png_get_libpng_ver(png_const_structrp png_ptr);
extern void png_set_user_limits(png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max);
extern png_uint_32 png_get_user_width_max(png_const_structrp png_ptr);
extern png_uint_32 png_get_user_height_max(png_const_structrp png_ptr);
extern void png_set_chunk_cache_max(png_structrp png_ptr, png_uint_32 user_chunk_cache_max);
extern png_uint_32 png_get_chunk_cache_max(png_const_structrp png_ptr);
extern void png_set_chunk_malloc_max(png_structrp png_ptr, png_alloc_size_t user_chunk_cache_max);
extern png_alloc_size_t png_get_chunk_malloc_max(png_const_structrp png_ptr);
extern png_uint_32 png_get_io_state(png_const_structrp png_ptr);
extern png_uint_32 png_get_io_chunk_type(png_const_structrp png_ptr);
extern png_uint_32 png_get_uint_32(png_const_bytep buf);
extern png_uint_16 png_get_uint_16(png_const_bytep buf);
extern png_int_32 png_get_int_32(png_const_bytep buf);
extern png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf);
extern void png_save_uint_32(png_bytep buf, png_uint_32 i);
extern void png_save_int_32(png_bytep buf, png_int_32 i);
extern void png_save_uint_16(png_bytep buf, unsigned int i);
extern void png_set_check_for_invalid_index(png_structrp png_ptr, int allowed);
extern int png_get_palette_max(png_const_structp png_ptr, png_const_infop info_ptr);
int pngx_read_image(png_structp png_ptr, png_infop info_ptr, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
void pngx_set_compression_type(png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type(png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type(png_structp png_ptr, png_infop info_ptr, int interlace_type);
typedef png_alloc_size_t pngx_alloc_size_t;
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended(png_structp png_ptr, png_infop info_ptr, pngx_alloc_size_t min_row_size, int filler);
int pngx_sig_is_bmp(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_gif(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_jpeg(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_pnm(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_tiff(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_tiff(png_structp png_ptr, png_infop info_ptr, FILE *stream);
static unsigned int bmp_get_word(png_bytep ptr)
{
  return ((unsigned int) ptr[0]) + (((unsigned int) ptr[1]) << 8);
}

static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}

static void bmp_memset_bytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  memset(ptr + offset, ch, len);
}

static void bmp_memset_halfbytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  if (len == 0)
  {
    return;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    *ptr = (png_byte) (((*ptr) & 0xf0) | (ch & 0x0f));
    ch = ((ch & 0xf0) >> 4) | ((ch & 0x0f) << 4);
    ptr += 1;
    len -= 1;
  }
  memset(ptr, ch, len / 2);
  if (len & 1)
  {
    ptr[len / 2] = (png_byte) (ch & 0xf0);
  }
}

static size_t bmp_fread_bytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  result = fread(ptr + offset, 1, len, stream);
  if (len & 1)
  {
    getc(stream);
  }
  return result;
}

static size_t bmp_fread_halfbytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  int ch;
  if (len == 0)
  {
    return 0;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    for (result = 0; result < (len - 1); result += 2)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      *ptr = (png_byte) (((*ptr) & 0xf0) | ((ch & 0xf0) >> 4));
      ptr += 1;
      *ptr = (png_byte) ((ch & 0x0f) << 4);
    }

  }
  else
  {
    result = fread(ptr, 1, (len + 1) / 2, stream) * 2;
  }
  if (len & 2)
  {
    getc(stream);
  }
  return (result <= len) ? (result) : (len);
}

static void bmp_process_mask(png_uint_32 bmp_mask, png_bytep sig_bit, png_bytep shift_bit)
{
  *sig_bit = (*shift_bit = (png_byte) 0);
  if (bmp_mask == 0)
  {
    return;
  }
  while ((bmp_mask & 1) == 0)
  {
    bmp_mask >>= 1;
    *shift_bit += 1;
  }

  while (bmp_mask != 0)
  {
    if (((bmp_mask & 1) == 0) || ((*sig_bit) >= 8))
    {
      *sig_bit = (png_byte) 0;
      return;
    }
    bmp_mask >>= 1;
    *sig_bit += 1;
  }

}

static size_t bmp_read_rows(png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE *stream)
{
  size_t result;
  png_bytepp crt_row;
  int inc;
  size_t crtn;
  size_t dcrtn;
  size_t endn;
  unsigned int len;
  unsigned int b1;
  unsigned int b2;
  int ch;
  void (*bmp_memset_fn)(png_bytep, size_t, int, size_t);
  unsigned int bmp_memset_fn_idx = 0;
  size_t (*bmp_fread_fn)(png_bytep, size_t, size_t, FILE *);
  unsigned int bmp_fread_fn_idx = 0;
  if (row_size == 0)
  {
    return 0;
  }
  inc = (begin_row <= end_row) ? (1) : (-1);
  crtn = 0;
  result = 0;
  if (compression == 2)
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
    bmp_memset_fn_idx = bmp_memset_halfbytes;
    bmp_fread_fn_idx = bmp_fread_halfbytes;
  }
  else
  {
    endn = row_size;
    bmp_memset_fn_idx = bmp_memset_bytes;
    bmp_fread_fn_idx = bmp_fread_bytes;
  }
  if ((compression == 0) || (compression == 3))
  {
    for (crt_row = begin_row; crt_row != end_row; crt_row += inc)
    {
      crtn = bmp_fread_fn(*crt_row, 0, endn, stream);
      if (crtn != endn)
      {
        break;
      }
      result += 1;
    }

  }
  else
    if ((compression == 1) || (compression == 2))
  {
    helper_bmp_read_rows_1(&result, &crt_row, &crtn, &dcrtn, &endn, &len, &b1, &b2, &ch, begin_row, end_row, row_size, compression, stream, inc);
  }
  else
    return 0;
  for (; crt_row != end_row; crt_row += inc)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crtn = 0;
  }

  return result;
}

static void bmp_to_png_rows(png_bytepp row_pointers, png_uint_32 width, png_uint_32 height, unsigned int pixdepth, png_bytep rgba_sig, png_bytep rgba_shift)
{
  png_bytep src_ptr;
  png_bytep dest_ptr;
  unsigned int rgba_mask[4];
  unsigned int num_samples;
  unsigned int sample;
  unsigned int mask;
  unsigned int wpix;
  png_uint_32 dwpix;
  png_uint_32 x;
  png_uint_32 y;
  unsigned int i;
  if (pixdepth == 24)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y];
      for (x = 0; x < width; x += 1, src_ptr += 3)
      {
        png_byte tmp = src_ptr[0];
        src_ptr[0] = src_ptr[2];
        src_ptr[2] = tmp;
      }

    }

    return;
  }
  num_samples = (rgba_sig[3] != 0) ? (4) : (3);
  for (i = 0; i < num_samples; i += 1)
  {
    rgba_mask[i] = (1U << rgba_sig[i]) - 1;
  }

  if (pixdepth == 16)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y] + ((width - 1) * 2);
      dest_ptr = row_pointers[y] + ((width - 1) * num_samples);
      for (x = 0; x < width; x += 1, src_ptr -= 2, dest_ptr -= num_samples)
      {
        wpix = ((unsigned int) src_ptr[0]) + (((unsigned int) src_ptr[1]) << 8);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (wpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
  else
    if (pixdepth == 32)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = (dest_ptr = row_pointers[y]);
      for (x = 0; x < width; x += 1, src_ptr += 4, dest_ptr += num_samples)
      {
        dwpix = ((((png_uint_32) src_ptr[0]) + (((png_uint_32) src_ptr[1]) << 8)) + (((png_uint_32) src_ptr[2]) << 16)) + (((png_uint_32) src_ptr[3]) << 24);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (dwpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
}

int pngx_sig_is_bmp(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char bmp_fmt_name[] = "BMP";
  static const char os2bmp_fmt_long_name[] = "OS/2 Bitmap";
  static const char winbmp_fmt_long_name[] = "Windows Bitmap";
  png_uint_32 bihsize;
  if (sig_size < (14 + 4))
  {
    return -1;
  }
  if (bmp_get_word(sig) != 0x4d42)
  {
    return 0;
  }
  bihsize = bmp_get_dword(sig + 14);
  if ((bihsize > ((png_uint_32) 0x7fffffffL)) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = bmp_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    if (bihsize == 12)
    {
      *fmt_long_name_ptr = os2bmp_fmt_long_name;
    }
    else
      *fmt_long_name_ptr = winbmp_fmt_long_name;
  }
  return 1;
}

int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  png_byte bfh[14 + 124];
  const png_bytep bih = bfh + 14;
  png_byte rgbq[4];
  png_uint_32 offbits;
  png_uint_32 bihsize;
  png_uint_32 skip;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowsize;
  int topdown;
  unsigned int pixdepth;
  png_uint_32 compression;
  unsigned int palsize;
  unsigned int palnum;
  png_uint_32 rgba_mask[4];
  png_byte rgba_sig[4];
  png_byte rgba_shift[4];
  int bit_depth;
  int color_type;
  png_color palette[256];
  png_color_8 sig_bit;
  png_bytepp row_pointers;
  png_bytepp begin_row;
  png_bytepp end_row;
  unsigned int i;
  size_t y;
  for (i = 0;; i += 1)
  {
    if (fread(bfh, 14 + 4, 1, stream) != 1)
    {
      i += 1;
    }
    else
      if (bmp_get_word(bfh + 0) == 0x4d42)
    {
      break;
    }
    if (fread(bfh, (128 - 14) - 4, 1, stream) != 1)
    {
      i += 1;
    }
    if (i > 0)
    {
      return 0;
    }
  }

  offbits = bmp_get_dword(bfh + 10);
  bihsize = bmp_get_dword(bfh + 14);
  if ((((offbits > ((png_uint_32) 0x7fffffffL)) || (bihsize > ((png_uint_32) 0x7fffffffL))) || (offbits < (bihsize + 14))) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (bihsize > 124)
  {
    skip = bihsize - 124;
    bihsize = 124;
  }
  else
    skip = 0;
  if (fread(bih + 4, bihsize - 4, 1, stream) != 1)
  {
    return 0;
  }
  if (skip > 0)
  {
    if (fseek(stream, (long) skip, 1) != 0)
    {
      return 0;
    }
  }
  skip = (offbits - bihsize) - 14;
  topdown = 0;
  if (bihsize < 40)
  {
    width = bmp_get_word(bih + 4);
    height = bmp_get_word(bih + 6);
    pixdepth = bmp_get_word(bih + 10);
    compression = 0;
    palsize = 3;
  }
  else
  {
    helper_pngx_read_bmp_1(&bihsize, &skip, &width, &height, &topdown, &pixdepth, &compression, &palsize, &i, stream, bih);
  }
  memset(rgba_mask, 0, sizeof(rgba_mask));
  if (pixdepth > 8)
  {
    helper_pngx_read_bmp_3(&compression, png_ptr, bih, bihsize, pixdepth, rgba_mask);
  }
  switch (compression)
  {
    case 0:
    {
      if (((pixdepth > 0) && ((32 % pixdepth) != 0)) && (pixdepth != 24))
      {
        pixdepth = 0;
      }
      break;
    }

    case 1:
    {
      if (pixdepth != 8)
      {
        pixdepth = 0;
      }
      break;
    }

    case 2:
    {
      if (pixdepth != 4)
      {
        pixdepth = 0;
      }
      break;
    }

    case 3:
    {
      if ((pixdepth != 16) && (pixdepth != 32))
      {
        pixdepth = 0;
      }
      break;
    }

    case 4:
    {
      png_error(png_ptr, "JPEG-compressed BMP files are not supported");
      break;
    }

    case 5:
    {
      if (ungetc(getc(stream), stream) == 0)
      {
        png_set_sig_bytes(png_ptr, 8);
      }
      png_set_read_fn(png_ptr, stream, 0);
      png_read_png(png_ptr, info_ptr, 0, 0);
      return 1;
    }

    default:
    {
      png_error(png_ptr, "Unsupported compression method in BMP file");
    }

  }

  if (((width == 0) || (width > ((png_uint_32) 0x7fffffffL))) || (height == 0))
  {
    png_error(png_ptr, "Invalid image dimensions in BMP file");
  }
  if (pixdepth == 0)
  {
    png_error(png_ptr, "Invalid pixel depth in BMP file");
  }
  if (pixdepth <= 8)
  {
    palnum = skip / palsize;
    if (palnum > 256)
    {
      palnum = 256;
    }
    skip -= palsize * palnum;
    rowsize = (((width + (32 / pixdepth)) - 1) / (32 / pixdepth)) * 4;
    bit_depth = pixdepth;
    color_type = (palnum > 0) ? (2 | 1) : (0);
  }
  else
  {
    helper_pngx_read_bmp_2(&rowsize, &palnum, &bit_depth, &color_type, width, pixdepth, rgba_mask);
  }
  if (rowsize == 0)
  {
    png_error(png_ptr, "Can't handle exceedingly large BMP dimensions");
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, 0, 0, 0);
  if (pixdepth > 8)
  {
    for (i = 0; i < 4; i += 1)
    {
      bmp_process_mask(rgba_mask[i], &rgba_sig[i], &rgba_shift[i]);
    }

    if (((rgba_sig[0] == 0) || (rgba_sig[1] == 0)) || (rgba_sig[2] == 0))
    {
      png_error(png_ptr, "Invalid color mask in BMP file");
    }
    if ((((rgba_sig[0] != 8) || (rgba_sig[1] != 8)) || (rgba_sig[2] != 8)) || ((rgba_sig[3] != 0) && (rgba_sig[3] != 8)))
    {
      sig_bit.red = rgba_sig[0];
      sig_bit.green = rgba_sig[1];
      sig_bit.blue = rgba_sig[2];
      sig_bit.alpha = rgba_sig[3];
      png_set_sBIT(png_ptr, info_ptr, &sig_bit);
    }
  }
  if (palnum > 0)
  {
    for (i = 0; i < palnum; i += 1)
    {
      if (fread(rgbq, palsize, 1, stream) != 1)
      {
        break;
      }
      palette[i].red = rgbq[2];
      palette[i].green = rgbq[1];
      palette[i].blue = rgbq[0];
    }

    png_set_PLTE(png_ptr, info_ptr, palette, i);
    if (i != palnum)
    {
      png_error(png_ptr, "Error reading color palette in BMP file");
    }
  }
  row_pointers = pngx_malloc_rows_extended(png_ptr, info_ptr, rowsize, -1);
  if (topdown)
  {
    begin_row = row_pointers;
    end_row = row_pointers + height;
  }
  else
  {
    begin_row = (row_pointers + height) - 1;
    end_row = row_pointers - 1;
  }
  if (skip > 0)
  {
    fseek(stream, (long) skip, 1);
  }
  y = bmp_read_rows(begin_row, end_row, rowsize, compression, stream);
  if (pixdepth > 8)
  {
    bmp_to_png_rows(row_pointers, width, height, pixdepth, rgba_sig, rgba_shift);
  }
  if (y != ((size_t) height))
  {
    png_error(png_ptr, "Error reading BMP file");
  }
  return 1;
}


typedef unsigned char png_byte;
typedef short png_int_16;
typedef unsigned short png_uint_16;
typedef int png_int_32;
typedef unsigned int png_uint_32;
typedef size_t png_size_t;
typedef ptrdiff_t png_ptrdiff_t;
typedef size_t png_alloc_size_t;
typedef png_int_32 png_fixed_point;
typedef void *png_voidp;
typedef const void *png_const_voidp;
typedef png_byte *png_bytep;
typedef const png_byte *png_const_bytep;
typedef png_uint_32 *png_uint_32p;
typedef const png_uint_32 *png_const_uint_32p;
typedef png_int_32 *png_int_32p;
typedef const png_int_32 *png_const_int_32p;
typedef png_uint_16 *png_uint_16p;
typedef const png_uint_16 *png_const_uint_16p;
typedef png_int_16 *png_int_16p;
typedef const png_int_16 *png_const_int_16p;
typedef char *png_charp;
typedef const char *png_const_charp;
typedef png_fixed_point *png_fixed_point_p;
typedef const png_fixed_point *png_const_fixed_point_p;
typedef size_t *png_size_tp;
typedef const size_t *png_const_size_tp;
typedef FILE *png_FILE_p;
typedef png_byte **png_bytepp;
typedef png_uint_32 **png_uint_32pp;
typedef png_int_32 **png_int_32pp;
typedef png_uint_16 **png_uint_16pp;
typedef png_int_16 **png_int_16pp;
typedef const char **png_const_charpp;
typedef char **png_charpp;
typedef png_fixed_point **png_fixed_point_pp;
typedef char ***png_charppp;
typedef char *png_libpng_version_1_6_40;
typedef struct png_struct_def png_struct;
typedef const png_struct *png_const_structp;
typedef png_struct *png_structp;
typedef png_struct **png_structpp;
typedef struct png_info_def png_info;
typedef png_info *png_infop;
typedef const png_info *png_const_infop;
typedef png_info **png_infopp;
typedef png_struct *png_structrp;
typedef const png_struct *png_const_structrp;
typedef png_info *png_inforp;
typedef const png_info *png_const_inforp;
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color;
typedef png_color *png_colorp;
typedef const png_color *png_const_colorp;
typedef png_color **png_colorpp;
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16;
typedef png_color_16 *png_color_16p;
typedef const png_color_16 *png_const_color_16p;
typedef png_color_16 **png_color_16pp;
typedef struct png_color_8_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
  png_byte gray;
  png_byte alpha;
} png_color_8;
typedef png_color_8 *png_color_8p;
typedef const png_color_8 *png_const_color_8p;
typedef png_color_8 **png_color_8pp;
typedef struct png_sPLT_entry_struct
{
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 alpha;
  png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry *png_sPLT_entryp;
typedef const png_sPLT_entry *png_const_sPLT_entryp;
typedef png_sPLT_entry **png_sPLT_entrypp;
typedef struct png_sPLT_struct
{
  png_charp name;
  png_byte depth;
  png_sPLT_entryp entries;
  png_int_32 nentries;
} png_sPLT_t;
typedef png_sPLT_t *png_sPLT_tp;
typedef const png_sPLT_t *png_const_sPLT_tp;
typedef png_sPLT_t **png_sPLT_tpp;
typedef struct png_time_struct
{
  png_uint_16 year;
  png_byte month;
  png_byte day;
  png_byte hour;
  png_byte minute;
  png_byte second;
} png_time;
typedef png_time *png_timep;
typedef const png_time *png_const_timep;
typedef png_time **png_timepp;
typedef struct png_unknown_chunk_t
{
  png_byte name[5];
  png_byte *data;
  size_t size;
  png_byte location;
} png_unknown_chunk;
typedef png_unknown_chunk *png_unknown_chunkp;
typedef const png_unknown_chunk *png_const_unknown_chunkp;
typedef png_unknown_chunk **png_unknown_chunkpp;
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info;
typedef png_row_info *png_row_infop;
typedef png_row_info **png_row_infopp;
typedef void (*png_error_ptr)(png_structp, png_const_charp);
typedef void (*png_rw_ptr)(png_structp, png_bytep, size_t);
typedef void (*png_flush_ptr)(png_structp);
typedef void (*png_read_status_ptr)(png_structp, png_uint_32, int);
typedef void (*png_write_status_ptr)(png_structp, png_uint_32, int);
typedef png_voidp (*png_malloc_ptr)(png_structp, png_alloc_size_t);
typedef void (*png_free_ptr)(png_structp, png_voidp);
extern png_uint_32 png_access_version_number(void);
extern void png_set_sig_bytes(png_structrp png_ptr, int num_bytes);
extern int png_sig_cmp(png_const_bytep sig, size_t start, size_t num_to_check);
extern png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
extern png_structp png_create_write_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn);
extern size_t png_get_compression_buffer_size(png_const_structrp png_ptr);
extern void png_set_compression_buffer_size(png_structrp png_ptr, size_t size);
extern void png_longjmp(png_const_structrp png_ptr, int val);
extern int png_reset_zstream(png_structrp png_ptr);
extern void png_write_sig(png_structrp png_ptr);
extern void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_name, png_const_bytep data, size_t length);
extern void png_write_chunk_start(png_structrp png_ptr, png_const_bytep chunk_name, png_uint_32 length);
extern void png_write_chunk_data(png_structrp png_ptr, png_const_bytep data, size_t length);
extern void png_write_chunk_end(png_structrp png_ptr);
extern png_infop png_create_info_struct(png_const_structrp png_ptr);
extern void png_info_init_3(png_infopp info_ptr, size_t png_info_struct_size);
extern void png_write_info_before_PLTE(png_structrp png_ptr, png_const_inforp info_ptr);
extern void png_write_info(png_structrp png_ptr, png_const_inforp info_ptr);
extern void png_read_info(png_structrp png_ptr, png_inforp info_ptr);
extern int png_set_interlace_handling(png_structrp png_ptr);
extern void png_set_flush(png_structrp png_ptr, int nrows);
extern void png_write_flush(png_structrp png_ptr);
extern void png_start_read_image(png_structrp png_ptr);
extern void png_read_update_info(png_structrp png_ptr, png_inforp info_ptr);
extern void png_read_rows(png_structrp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows);
extern void png_read_row(png_structrp png_ptr, png_bytep row, png_bytep display_row);
extern void png_read_image(png_structrp png_ptr, png_bytepp image);
extern void png_write_row(png_structrp png_ptr, png_const_bytep row);
extern void png_write_rows(png_structrp png_ptr, png_bytepp row, png_uint_32 num_rows);
extern void png_write_image(png_structrp png_ptr, png_bytepp image);
extern void png_write_end(png_structrp png_ptr, png_inforp info_ptr);
extern void png_read_end(png_structrp png_ptr, png_inforp info_ptr);
extern void png_destroy_info_struct(png_const_structrp png_ptr, png_infopp info_ptr_ptr);
extern void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr);
extern void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr);
extern void png_set_crc_action(png_structrp png_ptr, int crit_action, int ancil_action);
extern void png_set_filter(png_structrp png_ptr, int method, int filters);
extern void png_set_compression_level(png_structrp png_ptr, int level);
extern void png_set_compression_mem_level(png_structrp png_ptr, int mem_level);
extern void png_set_compression_strategy(png_structrp png_ptr, int strategy);
extern void png_set_compression_window_bits(png_structrp png_ptr, int window_bits);
extern void png_set_compression_method(png_structrp png_ptr, int method);
extern void png_init_io(png_structrp png_ptr, png_FILE_p fp);
extern void png_set_error_fn(png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn);
extern png_voidp png_get_error_ptr(png_const_structrp png_ptr);
extern void png_set_write_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn);
extern void png_set_read_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn);
extern png_voidp png_get_io_ptr(png_const_structrp png_ptr);
extern void png_set_read_status_fn(png_structrp png_ptr, png_read_status_ptr read_row_fn);
extern void png_set_write_status_fn(png_structrp png_ptr, png_write_status_ptr write_row_fn);
extern png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size);
extern png_voidp png_calloc(png_const_structrp png_ptr, png_alloc_size_t size);
extern png_voidp png_malloc_warn(png_const_structrp png_ptr, png_alloc_size_t size);
extern void png_free(png_const_structrp png_ptr, png_voidp ptr);
extern void png_free_data(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 free_me, int num);
extern void png_data_freer(png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask);
extern void png_error(png_const_structrp png_ptr, png_const_charp error_message);
extern void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message);
extern void png_warning(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_benign_error(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp warning_message);
extern void png_set_benign_errors(png_structrp png_ptr, int allowed);
extern png_uint_32 png_get_valid(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag);
extern size_t png_get_rowbytes(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern void png_set_rows(png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers);
extern png_byte png_get_channels(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_image_width(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_image_height(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_bit_depth(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_color_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_filter_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_interlace_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_byte png_get_compression_type(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_x_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_y_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_fixed_point png_get_pixel_aspect_ratio_fixed(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_x_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_y_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_x_offset_microns(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_int_32 png_get_y_offset_microns(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_const_bytep png_get_signature(png_const_structrp png_ptr, png_const_inforp info_ptr);
extern png_uint_32 png_get_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_color_16p *background);
extern void png_set_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_16p background);
extern png_uint_32 png_get_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist);
extern void png_set_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist);
extern png_uint_32 png_get_IHDR(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method);
extern void png_set_IHDR(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method);
extern png_uint_32 png_get_PLTE(png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette);
extern void png_set_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette);
extern png_uint_32 png_get_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit);
extern void png_set_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit);
extern png_uint_32 png_get_tRNS(png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color);
extern void png_set_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color);
extern void png_set_keep_unknown_chunks(png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks);
extern int png_handle_as_unknown(png_const_structrp png_ptr, png_const_bytep chunk_name);
extern void png_set_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns);
extern void png_set_unknown_chunk_location(png_const_structrp png_ptr, png_inforp info_ptr, int chunk, int location);
extern int png_get_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_unknown_chunkpp entries);
extern void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask);
extern void png_read_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params);
extern void png_write_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params);
extern png_const_charp png_get_copyright(png_const_structrp png_ptr);
extern png_const_charp png_get_header_ver(png_const_structrp png_ptr);
extern png_const_charp png_get_header_version(png_const_structrp png_ptr);
extern png_const_charp png_get_libpng_ver(png_const_structrp png_ptr);
extern void png_set_user_limits(png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max);
extern png_uint_32 png_get_user_width_max(png_const_structrp png_ptr);
extern png_uint_32 png_get_user_height_max(png_const_structrp png_ptr);
extern void png_set_chunk_cache_max(png_structrp png_ptr, png_uint_32 user_chunk_cache_max);
extern png_uint_32 png_get_chunk_cache_max(png_const_structrp png_ptr);
extern void png_set_chunk_malloc_max(png_structrp png_ptr, png_alloc_size_t user_chunk_cache_max);
extern png_alloc_size_t png_get_chunk_malloc_max(png_const_structrp png_ptr);
extern png_uint_32 png_get_io_state(png_const_structrp png_ptr);
extern png_uint_32 png_get_io_chunk_type(png_const_structrp png_ptr);
extern png_uint_32 png_get_uint_32(png_const_bytep buf);
extern png_uint_16 png_get_uint_16(png_const_bytep buf);
extern png_int_32 png_get_int_32(png_const_bytep buf);
extern png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf);
extern void png_save_uint_32(png_bytep buf, png_uint_32 i);
extern void png_save_int_32(png_bytep buf, png_int_32 i);
extern void png_save_uint_16(png_bytep buf, unsigned int i);
extern void png_set_check_for_invalid_index(png_structrp png_ptr, int allowed);
extern int png_get_palette_max(png_const_structp png_ptr, png_const_infop info_ptr);
int pngx_read_image(png_structp png_ptr, png_infop info_ptr, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
void pngx_set_compression_type(png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type(png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type(png_structp png_ptr, png_infop info_ptr, int interlace_type);
typedef png_alloc_size_t pngx_alloc_size_t;
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended(png_structp png_ptr, png_infop info_ptr, pngx_alloc_size_t min_row_size, int filler);
int pngx_sig_is_bmp(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_gif(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_jpeg(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_pnm(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream);
int pngx_sig_is_tiff(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
int pngx_read_tiff(png_structp png_ptr, png_infop info_ptr, FILE *stream);
static unsigned int bmp_get_word(png_bytep ptr)
{
  return ((unsigned int) ptr[0]) + (((unsigned int) ptr[1]) << 8);
}

static png_uint_32 bmp_get_dword(png_bytep ptr)
{
  return ((((png_uint_32) ptr[0]) + (((png_uint_32) ptr[1]) << 8)) + (((png_uint_32) ptr[2]) << 16)) + (((png_uint_32) ptr[3]) << 24);
}

static void bmp_memset_bytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  memset(ptr + offset, ch, len);
}

static void bmp_memset_halfbytes(png_bytep ptr, size_t offset, int ch, size_t len)
{
  if (len == 0)
  {
    return;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    *ptr = (png_byte) (((*ptr) & 0xf0) | (ch & 0x0f));
    ch = ((ch & 0xf0) >> 4) | ((ch & 0x0f) << 4);
    ptr += 1;
    len -= 1;
  }
  memset(ptr, ch, len / 2);
  if (len & 1)
  {
    ptr[len / 2] = (png_byte) (ch & 0xf0);
  }
}

static size_t bmp_fread_bytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  result = fread(ptr + offset, 1, len, stream);
  if (len & 1)
  {
    getc(stream);
  }
  return result;
}

static size_t bmp_fread_halfbytes(png_bytep ptr, size_t offset, size_t len, FILE *stream)
{
  size_t result;
  int ch;
  if (len == 0)
  {
    return 0;
  }
  ptr += offset / 2;
  if (offset & 1)
  {
    for (result = 0; result < (len - 1); result += 2)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      *ptr = (png_byte) (((*ptr) & 0xf0) | ((ch & 0xf0) >> 4));
      ptr += 1;
      *ptr = (png_byte) ((ch & 0x0f) << 4);
    }

  }
  else
  {
    result = fread(ptr, 1, (len + 1) / 2, stream) * 2;
  }
  if (len & 2)
  {
    getc(stream);
  }
  return (result <= len) ? (result) : (len);
}

static void bmp_process_mask(png_uint_32 bmp_mask, png_bytep sig_bit, png_bytep shift_bit)
{
  *sig_bit = (*shift_bit = (png_byte) 0);
  if (bmp_mask == 0)
  {
    return;
  }
  while ((bmp_mask & 1) == 0)
  {
    bmp_mask >>= 1;
    *shift_bit += 1;
  }

  while (bmp_mask != 0)
  {
    if (((bmp_mask & 1) == 0) || ((*sig_bit) >= 8))
    {
      *sig_bit = (png_byte) 0;
      return;
    }
    bmp_mask >>= 1;
    *sig_bit += 1;
  }

}

static size_t bmp_read_rows(png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE *stream)
{
  size_t result;
  png_bytepp crt_row;
  int inc;
  size_t crtn;
  size_t dcrtn;
  size_t endn;
  unsigned int len;
  unsigned int b1;
  unsigned int b2;
  int ch;
  void (*bmp_memset_fn)(png_bytep, size_t, int, size_t);
  unsigned int bmp_memset_fn_idx = 0;
  size_t (*bmp_fread_fn)(png_bytep, size_t, size_t, FILE *);
  unsigned int bmp_fread_fn_idx = 0;
  if (row_size == 0)
  {
    return 0;
  }
  inc = (begin_row <= end_row) ? (1) : (-1);
  crtn = 0;
  result = 0;
  if (compression == 2)
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
    bmp_memset_fn_idx = bmp_memset_halfbytes;
    bmp_fread_fn_idx = bmp_fread_halfbytes;
  }
  else
  {
    endn = row_size;
    bmp_memset_fn_idx = bmp_memset_bytes;
    bmp_fread_fn_idx = bmp_fread_bytes;
  }
  if ((compression == 0) || (compression == 3))
  {
    for (crt_row = begin_row; crt_row != end_row; crt_row += inc)
    {
      crtn = bmp_fread_fn(*crt_row, 0, endn, stream);
      if (crtn != endn)
      {
        break;
      }
      result += 1;
    }

  }
  else
    if ((compression == 1) || (compression == 2))
  {
    if (compression == 1)
    {
      endn = row_size;
    }
    else
    {
      endn = row_size * 2;
      if (endn <= row_size)
      {
        return 0;
      }
    }
    for (crt_row = begin_row; crt_row != end_row;)
    {
      ch = getc(stream);
      b1 = (unsigned int) ch;
      ch = getc(stream);
      b2 = (unsigned int) ch;
      if (ch == EOF)
      {
        break;
      }
      if (b1 == 0)
      {
        if (b2 == 0)
        {
          bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
          crt_row += inc;
          crtn = 0;
          result += 1;
          if (crt_row == end_row)
          {
            ch = getc(stream);
            if ((ch != EOF) && (ch != 0))
            {
              ungetc(ch, stream);
              break;
            }
            getc(stream);
            break;
          }
        }
        else
          if (b2 == 1)
        {
          bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
          crt_row += inc;
          crtn = 0;
          result = (begin_row <= end_row) ? (end_row - begin_row) : (begin_row - end_row);
          break;
        }
        else
          if (b2 == 2)
        {
          ch = getc(stream);
          b1 = (unsigned int) ch;
          ch = getc(stream);
          b2 = (unsigned int) ch;
          if (ch == EOF)
          {
            break;
          }
          dcrtn = (b1 < (endn - crtn)) ? (crtn + b1) : (endn);
          for (; b2 > 0; b2 -= 1)
          {
            bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
            crt_row += inc;
            crtn = 0;
            result += 1;
            if (crt_row == end_row)
            {
              break;
            }
          }

          if (crt_row != end_row)
          {
            bmp_memset_fn(*crt_row, crtn, 0, dcrtn - crtn);
          }
        }
        else
        {
          len = (b2 <= (endn - crtn)) ? (b2) : ((unsigned int) (endn - crtn));
          if (bmp_fread_fn(*crt_row, crtn, len, stream) != len)
          {
            break;
          }
          crtn += len;
        }
      }
      else
      {
        len = (b1 <= (endn - crtn)) ? (b1) : ((unsigned int) (endn - crtn));
        bmp_memset_fn(*crt_row, crtn, (int) b2, len);
        crtn += len;
      }
    }

  }
  else
    return 0;
  for (; crt_row != end_row; crt_row += inc)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crtn = 0;
  }

  return result;
}

static void bmp_to_png_rows(png_bytepp row_pointers, png_uint_32 width, png_uint_32 height, unsigned int pixdepth, png_bytep rgba_sig, png_bytep rgba_shift)
{
  png_bytep src_ptr;
  png_bytep dest_ptr;
  unsigned int rgba_mask[4];
  unsigned int num_samples;
  unsigned int sample;
  unsigned int mask;
  unsigned int wpix;
  png_uint_32 dwpix;
  png_uint_32 x;
  png_uint_32 y;
  unsigned int i;
  if (pixdepth == 24)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y];
      for (x = 0; x < width; x += 1, src_ptr += 3)
      {
        png_byte tmp = src_ptr[0];
        src_ptr[0] = src_ptr[2];
        src_ptr[2] = tmp;
      }

    }

    return;
  }
  num_samples = (rgba_sig[3] != 0) ? (4) : (3);
  for (i = 0; i < num_samples; i += 1)
  {
    rgba_mask[i] = (1U << rgba_sig[i]) - 1;
  }

  if (pixdepth == 16)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = row_pointers[y] + ((width - 1) * 2);
      dest_ptr = row_pointers[y] + ((width - 1) * num_samples);
      for (x = 0; x < width; x += 1, src_ptr -= 2, dest_ptr -= num_samples)
      {
        wpix = ((unsigned int) src_ptr[0]) + (((unsigned int) src_ptr[1]) << 8);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (wpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
  else
    if (pixdepth == 32)
  {
    for (y = 0; y < height; y += 1)
    {
      src_ptr = (dest_ptr = row_pointers[y]);
      for (x = 0; x < width; x += 1, src_ptr += 4, dest_ptr += num_samples)
      {
        dwpix = ((((png_uint_32) src_ptr[0]) + (((png_uint_32) src_ptr[1]) << 8)) + (((png_uint_32) src_ptr[2]) << 16)) + (((png_uint_32) src_ptr[3]) << 24);
        for (i = 0; i < num_samples; i += 1)
        {
          mask = rgba_mask[i];
          sample = (dwpix >> rgba_shift[i]) & mask;
          dest_ptr[i] = (png_byte) (((sample * 255) + (mask / 2)) / mask);
        }

      }

    }

  }
}

int pngx_sig_is_bmp(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char bmp_fmt_name[] = "BMP";
  static const char os2bmp_fmt_long_name[] = "OS/2 Bitmap";
  static const char winbmp_fmt_long_name[] = "Windows Bitmap";
  png_uint_32 bihsize;
  if (sig_size < (14 + 4))
  {
    return -1;
  }
  if (bmp_get_word(sig) != 0x4d42)
  {
    return 0;
  }
  bihsize = bmp_get_dword(sig + 14);
  if ((bihsize > ((png_uint_32) 0x7fffffffL)) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = bmp_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    if (bihsize == 12)
    {
      *fmt_long_name_ptr = os2bmp_fmt_long_name;
    }
    else
      *fmt_long_name_ptr = winbmp_fmt_long_name;
  }
  return 1;
}

int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  png_byte bfh[14 + 124];
  const png_bytep bih = bfh + 14;
  png_byte rgbq[4];
  png_uint_32 offbits;
  png_uint_32 bihsize;
  png_uint_32 skip;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowsize;
  int topdown;
  unsigned int pixdepth;
  png_uint_32 compression;
  unsigned int palsize;
  unsigned int palnum;
  png_uint_32 rgba_mask[4];
  png_byte rgba_sig[4];
  png_byte rgba_shift[4];
  int bit_depth;
  int color_type;
  png_color palette[256];
  png_color_8 sig_bit;
  png_bytepp row_pointers;
  png_bytepp begin_row;
  png_bytepp end_row;
  unsigned int i;
  size_t y;
  for (i = 0;; i += 1)
  {
    if (fread(bfh, 14 + 4, 1, stream) != 1)
    {
      i += 1;
    }
    else
      if (bmp_get_word(bfh + 0) == 0x4d42)
    {
      break;
    }
    if (fread(bfh, (128 - 14) - 4, 1, stream) != 1)
    {
      i += 1;
    }
    if (i > 0)
    {
      return 0;
    }
  }

  offbits = bmp_get_dword(bfh + 10);
  bihsize = bmp_get_dword(bfh + 14);
  if ((((offbits > ((png_uint_32) 0x7fffffffL)) || (bihsize > ((png_uint_32) 0x7fffffffL))) || (offbits < (bihsize + 14))) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (bihsize > 124)
  {
    skip = bihsize - 124;
    bihsize = 124;
  }
  else
    skip = 0;
  if (fread(bih + 4, bihsize - 4, 1, stream) != 1)
  {
    return 0;
  }
  if (skip > 0)
  {
    if (fseek(stream, (long) skip, 1) != 0)
    {
      return 0;
    }
  }
  skip = (offbits - bihsize) - 14;
  topdown = 0;
  if (bihsize < 40)
  {
    width = bmp_get_word(bih + 4);
    height = bmp_get_word(bih + 6);
    pixdepth = bmp_get_word(bih + 10);
    compression = 0;
    palsize = 3;
  }
  else
  {
    width = bmp_get_dword(bih + 4);
    height = bmp_get_dword(bih + 8);
    pixdepth = bmp_get_word(bih + 14);
    compression = bmp_get_dword(bih + 16);
    palsize = 4;
    if (height > ((png_uint_32) 0x7fffffffL))
    {
      height = (((png_uint_32) (-1)) - height) + 1;
      topdown = 1;
    }
    if ((bihsize == 40) && (compression == 3))
    {
      i = (skip <= 16) ? ((unsigned int) skip) : (16);
      if (fread(bih + 40, i, 1, stream) != 1)
      {
        return 0;
      }
      bihsize += i;
      skip -= i;
    }
  }
  memset(rgba_mask, 0, sizeof(rgba_mask));
  if (pixdepth > 8)
  {
    if (compression == 0)
    {
      if (pixdepth == 16)
      {
        compression = 3;
        rgba_mask[0] = 0x7c00;
        rgba_mask[1] = 0x03e0;
        rgba_mask[2] = 0x001f;
      }
      else
      {
        rgba_mask[0] = (png_uint_32) 0x00ff0000L;
        rgba_mask[1] = (png_uint_32) 0x0000ff00L;
        rgba_mask[2] = (png_uint_32) 0x000000ffL;
      }
    }
    else
      if (compression == 3)
    {
      if (bihsize >= (40 + 12))
      {
        rgba_mask[0] = bmp_get_dword(bih + 40);
        rgba_mask[1] = bmp_get_dword(bih + 44);
        rgba_mask[2] = bmp_get_dword(bih + 48);
      }
      else
        png_error(png_ptr, "Missing color mask in BMP file");
    }
    if (bihsize >= (40 + 16))
    {
      rgba_mask[3] = bmp_get_dword(bih + 52);
    }
  }
  switch (compression)
  {
    case 0:
      if (((pixdepth > 0) && ((32 % pixdepth) != 0)) && (pixdepth != 24))
    {
      pixdepth = 0;
    }
      break;

    case 1:
      if (pixdepth != 8)
    {
      pixdepth = 0;
    }
      break;

    case 2:
      if (pixdepth != 4)
    {
      pixdepth = 0;
    }
      break;

    case 3:
      if ((pixdepth != 16) && (pixdepth != 32))
    {
      pixdepth = 0;
    }
      break;

    case 4:
      png_error(png_ptr, "JPEG-compressed BMP files are not supported");
      break;

    case 5:
      if (ungetc(getc(stream), stream) == 0)
    {
      png_set_sig_bytes(png_ptr, 8);
    }
      png_set_read_fn(png_ptr, stream, 0);
      png_read_png(png_ptr, info_ptr, 0, 0);
      return 1;

    default:
      png_error(png_ptr, "Unsupported compression method in BMP file");

  }

  if (((width == 0) || (width > ((png_uint_32) 0x7fffffffL))) || (height == 0))
  {
    png_error(png_ptr, "Invalid image dimensions in BMP file");
  }
  if (pixdepth == 0)
  {
    png_error(png_ptr, "Invalid pixel depth in BMP file");
  }
  if (pixdepth <= 8)
  {
    palnum = skip / palsize;
    if (palnum > 256)
    {
      palnum = 256;
    }
    skip -= palsize * palnum;
    rowsize = (((width + (32 / pixdepth)) - 1) / (32 / pixdepth)) * 4;
    bit_depth = pixdepth;
    color_type = (palnum > 0) ? (2 | 1) : (0);
  }
  else
  {
    palnum = 0;
    bit_depth = 8;
    switch (pixdepth)
    {
      case 16:
        rowsize = ((width * 2) + 3) & (~3);
        break;

      case 24:
        rowsize = ((width * 3) + 3) & (~3);
        break;

      case 32:
        rowsize = width * 4;
        break;

      default:
        bit_depth = 0;
        rowsize = 0;

    }

    if ((rowsize / width) < (pixdepth / 8))
    {
      rowsize = 0;
    }
    color_type = (rgba_mask[3] != 0) ? (2 | 4) : (2);
  }
  if (rowsize == 0)
  {
    png_error(png_ptr, "Can't handle exceedingly large BMP dimensions");
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, 0, 0, 0);
  if (pixdepth > 8)
  {
    for (i = 0; i < 4; i += 1)
    {
      bmp_process_mask(rgba_mask[i], &rgba_sig[i], &rgba_shift[i]);
    }

    if (((rgba_sig[0] == 0) || (rgba_sig[1] == 0)) || (rgba_sig[2] == 0))
    {
      png_error(png_ptr, "Invalid color mask in BMP file");
    }
    if ((((rgba_sig[0] != 8) || (rgba_sig[1] != 8)) || (rgba_sig[2] != 8)) || ((rgba_sig[3] != 0) && (rgba_sig[3] != 8)))
    {
      sig_bit.red = rgba_sig[0];
      sig_bit.green = rgba_sig[1];
      sig_bit.blue = rgba_sig[2];
      sig_bit.alpha = rgba_sig[3];
      png_set_sBIT(png_ptr, info_ptr, &sig_bit);
    }
  }
  if (palnum > 0)
  {
    for (i = 0; i < palnum; i += 1)
    {
      if (fread(rgbq, palsize, 1, stream) != 1)
      {
        break;
      }
      palette[i].red = rgbq[2];
      palette[i].green = rgbq[1];
      palette[i].blue = rgbq[0];
    }

    png_set_PLTE(png_ptr, info_ptr, palette, i);
    if (i != palnum)
    {
      png_error(png_ptr, "Error reading color palette in BMP file");
    }
  }
  row_pointers = pngx_malloc_rows_extended(png_ptr, info_ptr, rowsize, -1);
  if (topdown)
  {
    begin_row = row_pointers;
    end_row = row_pointers + height;
  }
  else
  {
    begin_row = (row_pointers + height) - 1;
    end_row = row_pointers - 1;
  }
  if (skip > 0)
  {
    fseek(stream, (long) skip, 1);
  }
  y = bmp_read_rows(begin_row, end_row, rowsize, compression, stream);
  if (pixdepth > 8)
  {
    bmp_to_png_rows(row_pointers, width, height, pixdepth, rgba_sig, rgba_shift);
  }
  if (y != ((size_t) height))
  {
    png_error(png_ptr, "Error reading BMP file");
  }
  return 1;
}

size_t helper_bmp_read_rows_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, size_t * const endn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, size_t row_size, unsigned int compression, FILE * const stream, int inc)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  size_t endn = *endn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  if (compression == 1)
  {
    endn = row_size;
  }
  else
  {
    endn = row_size * 2;
    if (endn <= row_size)
    {
      return 0;
    }
  }
  for (crt_row = begin_row; crt_row != end_row;)
  {
    helper_helper_bmp_read_rows_1_1(&result, &crt_row, &crtn, &dcrtn, &len, &b1, &b2, &ch, begin_row, end_row, stream, inc, endn);
  }

  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *endn_ref = endn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}

int helper_pngx_read_bmp_1(png_uint_32 * const bihsize_ref, png_uint_32 * const skip_ref, png_uint_32 * const width_ref, png_uint_32 * const height_ref, int * const topdown_ref, unsigned int * const pixdepth_ref, png_uint_32 * const compression_ref, unsigned int * const palsize_ref, unsigned int * const i_ref, FILE * const stream, const png_bytep bih)
{
  png_uint_32 bihsize = *bihsize_ref;
  png_uint_32 skip = *skip_ref;
  png_uint_32 width = *width_ref;
  png_uint_32 height = *height_ref;
  int topdown = *topdown_ref;
  unsigned int pixdepth = *pixdepth_ref;
  png_uint_32 compression = *compression_ref;
  unsigned int palsize = *palsize_ref;
  unsigned int i = *i_ref;
  width = bmp_get_dword(bih + 4);
  height = bmp_get_dword(bih + 8);
  pixdepth = bmp_get_word(bih + 14);
  compression = bmp_get_dword(bih + 16);
  palsize = 4;
  if (height > ((png_uint_32) 0x7fffffffL))
  {
    height = (((png_uint_32) (-1)) - height) + 1;
    topdown = 1;
  }
  if ((bihsize == 40) && (compression == 3))
  {
    i = (skip <= 16) ? ((unsigned int) skip) : (16);
    if (fread(bih + 40, i, 1, stream) != 1)
    {
      return 0;
    }
    bihsize += i;
    skip -= i;
  }
  *bihsize_ref = bihsize;
  *skip_ref = skip;
  *width_ref = width;
  *height_ref = height;
  *topdown_ref = topdown;
  *pixdepth_ref = pixdepth;
  *compression_ref = compression;
  *palsize_ref = palsize;
  *i_ref = i;
}

void helper_pngx_read_bmp_2(png_uint_32 * const rowsize_ref, unsigned int * const palnum_ref, int * const bit_depth_ref, int * const color_type_ref, png_uint_32 width, unsigned int pixdepth, png_uint_32 rgba_mask[4])
{
  png_uint_32 rowsize = *rowsize_ref;
  unsigned int palnum = *palnum_ref;
  int bit_depth = *bit_depth_ref;
  int color_type = *color_type_ref;
  palnum = 0;
  bit_depth = 8;
  switch (pixdepth)
  {
    case 16:
    {
      rowsize = ((width * 2) + 3) & (~3);
      break;
    }

    case 24:
    {
      rowsize = ((width * 3) + 3) & (~3);
      break;
    }

    case 32:
    {
      rowsize = width * 4;
      break;
    }

    default:
    {
      bit_depth = 0;
      rowsize = 0;
    }

  }

  if ((rowsize / width) < (pixdepth / 8))
  {
    rowsize = 0;
  }
  color_type = (rgba_mask[3] != 0) ? (2 | 4) : (2);
  *rowsize_ref = rowsize;
  *palnum_ref = palnum;
  *bit_depth_ref = bit_depth;
  *color_type_ref = color_type;
}

void helper_pngx_read_bmp_3(png_uint_32 * const compression_ref, png_structp png_ptr, const png_bytep bih, png_uint_32 bihsize, unsigned int pixdepth, png_uint_32 rgba_mask[4])
{
  png_uint_32 compression = *compression_ref;
  if (compression == 0)
  {
    if (pixdepth == 16)
    {
      compression = 3;
      rgba_mask[0] = 0x7c00;
      rgba_mask[1] = 0x03e0;
      rgba_mask[2] = 0x001f;
    }
    else
    {
      rgba_mask[0] = (png_uint_32) 0x00ff0000L;
      rgba_mask[1] = (png_uint_32) 0x0000ff00L;
      rgba_mask[2] = (png_uint_32) 0x000000ffL;
    }
  }
  else
    if (compression == 3)
  {
    if (bihsize >= (40 + 12))
    {
      rgba_mask[0] = bmp_get_dword(bih + 40);
      rgba_mask[1] = bmp_get_dword(bih + 44);
      rgba_mask[2] = bmp_get_dword(bih + 48);
    }
    else
      png_error(png_ptr, "Missing color mask in BMP file");
  }
  if (bihsize >= (40 + 16))
  {
    rgba_mask[3] = bmp_get_dword(bih + 52);
  }
  *compression_ref = compression;
}

void helper_helper_bmp_read_rows_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  ch = getc(stream);
  b1 = (unsigned int) ch;
  ch = getc(stream);
  b2 = (unsigned int) ch;
  if (ch == EOF)
  {
    break;
  }
  if (b1 == 0)
  {
    helper_helper_helper_bmp_read_rows_1_1_1(&result, &crt_row, &crtn, &dcrtn, &len, &b1, &b2, &ch, begin_row, end_row, stream, inc, endn);
  }
  else
  {
    len = (b1 <= (endn - crtn)) ? (b1) : ((unsigned int) (endn - crtn));
    bmp_memset_fn(*crt_row, crtn, (int) b2, len);
    crtn += len;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}

void helper_helper_helper_bmp_read_rows_1_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const len_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp begin_row, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int len = *len_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  if (b2 == 0)
  {
    helper_helper_helper_helper_bmp_read_rows_1_1_1_1(&result, &crt_row, &crtn, &ch, end_row, stream, inc, endn);
  }
  else
    if (b2 == 1)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crt_row += inc;
    crtn = 0;
    result = (begin_row <= end_row) ? (end_row - begin_row) : (begin_row - end_row);
    break;
  }
  else
    if (b2 == 2)
  {
    helper_helper_helper_helper_bmp_read_rows_1_1_1_2(&result, &crt_row, &crtn, &dcrtn, &b1, &b2, &ch, end_row, stream, inc, endn);
  }
  else
  {
    len = (b2 <= (endn - crtn)) ? (b2) : ((unsigned int) (endn - crtn));
    if (bmp_fread_fn(*crt_row, crtn, len, stream) != len)
    {
      break;
    }
    crtn += len;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *len_ref = len;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}

void helper_helper_helper_helper_bmp_read_rows_1_1_1_1(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, int * const ch_ref, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  int ch = *ch_ref;
  bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
  crt_row += inc;
  crtn = 0;
  result += 1;
  if (crt_row == end_row)
  {
    ch = getc(stream);
    if ((ch != EOF) && (ch != 0))
    {
      ungetc(ch, stream);
      break;
    }
    getc(stream);
    break;
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *ch_ref = ch;
}

void helper_helper_helper_helper_bmp_read_rows_1_1_1_2(size_t * const result_ref, png_bytepp * const crt_row_ref, size_t * const crtn_ref, size_t * const dcrtn_ref, unsigned int * const b1_ref, unsigned int * const b2_ref, int * const ch_ref, png_bytepp end_row, FILE * const stream, int inc, size_t endn)
{
  size_t result = *result_ref;
  png_bytepp crt_row = *crt_row_ref;
  size_t crtn = *crtn_ref;
  size_t dcrtn = *dcrtn_ref;
  unsigned int b1 = *b1_ref;
  unsigned int b2 = *b2_ref;
  int ch = *ch_ref;
  ch = getc(stream);
  b1 = (unsigned int) ch;
  ch = getc(stream);
  b2 = (unsigned int) ch;
  if (ch == EOF)
  {
    break;
  }
  dcrtn = (b1 < (endn - crtn)) ? (crtn + b1) : (endn);
  for (; b2 > 0; b2 -= 1)
  {
    bmp_memset_fn(*crt_row, crtn, 0, endn - crtn);
    crt_row += inc;
    crtn = 0;
    result += 1;
    if (crt_row == end_row)
    {
      break;
    }
  }

  if (crt_row != end_row)
  {
    bmp_memset_fn(*crt_row, crtn, 0, dcrtn - crtn);
  }
  *result_ref = result;
  *crt_row_ref = crt_row;
  *crtn_ref = crtn;
  *dcrtn_ref = dcrtn;
  *b1_ref = b1;
  *b2_ref = b2;
  *ch_ref = ch;
}

