#include <assert.h>
#include <limits.h>
#include <opngreduc.c>
#include <opngreduc.h>
#include <png.h>
#include <pngconf.h>
#include <pnglibconf.h>
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
int opng_validate_image(png_structp png_ptr, png_infop info_ptr);
png_uint_32 opng_reduce_image(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions);
int opng_validate_image(png_structp png_ptr, png_infop info_ptr)
{
  (void) 0;
  if (png_get_bit_depth(png_ptr, info_ptr) == 0)
  {
    return 0;
  }
  if (png_get_color_type(png_ptr, info_ptr) & 1)
  {
    if (!png_get_valid(png_ptr, info_ptr, 0x0008U))
    {
      return 0;
    }
  }
  if (!png_get_valid(png_ptr, info_ptr, 0x8000U))
  {
    return 0;
  }
  return 1;
}

static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
}

static void opng_realloc_PLTE(png_structp png_ptr, png_infop info_ptr, int num_palette)
{
  png_color buffer[256];
  png_colorp palette;
  int src_num_palette;
  png_bytep buffer_ptr;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p background;
  (void) 0;
  assert(num_palette > 0);
  src_num_palette = 0;
  png_get_PLTE(png_ptr, info_ptr, &palette, &src_num_palette);
  if (num_palette == src_num_palette)
  {
    return;
  }
  memcpy(buffer, palette, num_palette * (sizeof(png_color)));
  if (num_palette > src_num_palette)
  {
    memset(buffer + src_num_palette, 0, (num_palette - src_num_palette) * (sizeof(png_color)));
  }
  png_set_PLTE(png_ptr, info_ptr, buffer, num_palette);
  if (num_palette < src_num_palette)
  {
    if (png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0) && (num_trans > num_palette))
    {
      buffer_ptr = (png_bytep) ((png_voidp) buffer);
      png_warning(png_ptr, "Too many alpha values in tRNS");
      num_trans = num_palette;
      memcpy(buffer_ptr, trans_alpha, (size_t) num_trans);
      png_set_tRNS(png_ptr, info_ptr, buffer_ptr, num_trans, 0);
    }
    if (png_get_bKGD(png_ptr, info_ptr, &background) && (background->index >= num_palette))
    {
      png_warning(png_ptr, "Invalid color index in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
  }
}

static void opng_realloc_tRNS(png_structp png_ptr, png_infop info_ptr, int num_trans)
{
  png_byte buffer[256];
  png_bytep trans_alpha;
  int src_num_trans;
  (void) 0;
  assert(num_trans > 0);
  src_num_trans = 0;
  png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &src_num_trans, 0);
  if (num_trans == src_num_trans)
  {
    return;
  }
  memcpy(buffer, trans_alpha, (size_t) num_trans);
  if (num_trans > src_num_trans)
  {
    memset(buffer + src_num_trans, 0, num_trans - src_num_trans);
  }
  png_set_tRNS(png_ptr, info_ptr, buffer, num_trans, 0);
}

static void opng_get_alpha_row(png_row_infop row_info_ptr, png_color_16p trans_color, png_bytep row, png_bytep alpha_row)
{
  png_bytep sample_ptr;
  png_uint_32 width;
  int color_type;
  int bit_depth;
  int channels;
  png_byte trans_red;
  png_byte trans_green;
  png_byte trans_blue;
  png_byte trans_gray;
  png_uint_32 i;
  width = row_info_ptr->width;
  color_type = row_info_ptr->color_type;
  bit_depth = row_info_ptr->bit_depth;
  channels = row_info_ptr->channels;
  assert(!(color_type & 1));
  assert(bit_depth == 8);
  if (!(color_type & 4))
  {
    helper_opng_get_alpha_row_1(&alpha_row, &sample_ptr, &trans_red, &trans_green, &trans_blue, &trans_gray, &i, trans_color, row, width, color_type, channels);
  }
  assert(channels > 1);
  sample_ptr = row + (channels - 1);
  for (i = 0; i < width; i += 1, sample_ptr += channels, alpha_row += 1)
  {
    *alpha_row = *sample_ptr;
  }

}

static png_uint_32 opng_analyze_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep component_ptr;
  png_uint_32 height;
  png_uint_32 width;
  int bit_depth;
  int color_type;
  int byte_depth;
  int channels;
  int sample_size;
  int offset_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  if (bit_depth < 8)
  {
    return 0x0000;
  }
  if (color_type & 1)
  {
    return 0x0000;
  }
  byte_depth = bit_depth / 8;
  channels = png_get_channels(png_ptr, info_ptr);
  sample_size = channels * byte_depth;
  offset_alpha = (channels - 1) * byte_depth;
  reductions &= (0x0001 | 0x0004) | 0x0008;
  if (bit_depth <= 8)
  {
    reductions &= ~0x0001;
  }
  if (!(color_type & 2))
  {
    reductions &= ~0x0004;
  }
  if (!(color_type & 4))
  {
    reductions &= ~0x0008;
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      if (((((background->red % 257) != 0) || ((background->green % 257) != 0)) || ((background->blue % 257) != 0)) || ((background->gray % 257) != 0))
      {
        reductions &= ~0x0001;
      }
    }
    if (reductions & 0x0004)
    {
      if ((background->red != background->green) || (background->red != background->blue))
      {
        reductions &= ~0x0004;
      }
    }
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_analyze_bits_1(&reductions, &component_ptr, &j, row_ptr, width, bit_depth, channels, sample_size, offset_alpha);
  }

  return reductions;
}

static png_uint_32 opng_reduce_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep src_ptr;
  png_bytep dest_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int src_byte_depth;
  int dest_byte_depth;
  int src_color_type;
  int dest_color_type;
  int src_channels;
  int dest_channels;
  int src_sample_size;
  int dest_sample_size;
  int tran_tbl[8];
  png_color_16p trans_color;
  png_color_16p background;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  reductions = opng_analyze_bits(png_ptr, info_ptr, reductions);
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &src_color_type, &interlace_type, &compression_type, &filter_type);
  assert(src_bit_depth >= 8);
  if (reductions & 0x0001)
  {
    assert(src_bit_depth == 16);
    dest_bit_depth = 8;
  }
  else
    dest_bit_depth = src_bit_depth;
  src_byte_depth = src_bit_depth / 8;
  dest_byte_depth = dest_bit_depth / 8;
  dest_color_type = src_color_type;
  if (reductions & 0x0004)
  {
    assert(src_color_type & 2);
    dest_color_type &= ~2;
  }
  if (reductions & 0x0008)
  {
    assert(src_color_type & 4);
    dest_color_type &= ~4;
  }
  src_channels = png_get_channels(png_ptr, info_ptr);
  dest_channels = ((dest_color_type & 2) ? (3) : (1)) + ((dest_color_type & 4) ? (1) : (0));
  src_sample_size = src_channels * src_byte_depth;
  dest_sample_size = dest_channels * dest_byte_depth;
  for (k = 0; k < (4 * dest_byte_depth); k += 1)
  {
    tran_tbl[k] = (k * src_bit_depth) / dest_bit_depth;
  }

  if ((reductions & 0x0004) && (dest_color_type & 4))
  {
    tran_tbl[dest_byte_depth] = tran_tbl[3 * dest_byte_depth];
    if (dest_byte_depth == 2)
    {
      tran_tbl[dest_byte_depth + 1] = tran_tbl[(3 * dest_byte_depth) + 1];
    }
  }
  assert(src_sample_size > dest_sample_size);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_ptr = (dest_ptr = *row_ptr);
    for (j = 0; j < width; j += 1)
    {
      for (k = 0; k < dest_sample_size; k += 1)
      {
        dest_ptr[k] = src_ptr[tran_tbl[k]];
      }

      src_ptr += src_sample_size;
      dest_ptr += dest_sample_size;
    }

  }

  if (png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color))
  {
    helper_opng_reduce_bits_1(&trans_color, png_ptr, info_ptr, reductions);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      background->red &= 255;
      background->green &= 255;
      background->blue &= 255;
      background->gray &= 255;
    }
    if (reductions & 0x0004)
    {
      background->gray = background->red;
    }
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    helper_opng_reduce_bits_2(&sig_bits, reductions);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, dest_color_type, interlace_type, compression_type, filter_type);
  return reductions;
}

static png_uint_32 opng_reduce_palette_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_bytepp row_ptr;
  png_bytep src_sample_ptr;
  png_bytep dest_sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  unsigned int src_mask_init;
  unsigned int src_mask;
  unsigned int src_shift;
  unsigned int dest_shift;
  unsigned int sample;
  unsigned int dest_buf;
  png_colorp palette;
  int num_palette;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  if (!(reductions & 0x0002))
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (color_type != (2 | 1))
  {
    return 0x0000;
  }
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    num_palette = 0;
  }
  result = 0x0000;
  if (num_palette > (1 << src_bit_depth))
  {
    png_warning(png_ptr, "Too many colors in PLTE");
    num_palette = 1 << src_bit_depth;
    opng_realloc_PLTE(png_ptr, info_ptr, num_palette);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (1 << src_bit_depth));
    result |= 0x2000;
  }
  if (num_palette > 16)
  {
    return result;
  }
  else
    if (num_palette > 4)
  {
    dest_bit_depth = 4;
  }
  else
    if (num_palette > 2)
  {
    dest_bit_depth = 2;
  }
  else
  {
    assert(num_palette > 0);
    dest_bit_depth = 1;
  }
  if (src_bit_depth <= dest_bit_depth)
  {
    assert(src_bit_depth == dest_bit_depth);
    return result;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (src_bit_depth == 8)
  {
    helper_opng_reduce_palette_bits_1(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &dest_shift, &dest_buf, &i, &j, width, height, dest_bit_depth);
  }
  else
  {
    helper_opng_reduce_palette_bits_2(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &src_mask_init, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &i, &j, width, height, src_bit_depth, dest_bit_depth);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, color_type, interlace_type, compression_type, filter_type);
  result |= 0x0002;
  return result;
}

static png_uint_32 opng_reduce_to_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_row_info row_info;
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_bytep alpha_row;
  png_uint_32 height;
  png_uint_32 width;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int channels;
  png_color palette[256];
  png_byte trans_alpha[256];
  png_color_16p trans_color;
  int num_palette;
  int num_trans;
  int index;
  unsigned int gray;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int alpha;
  unsigned int prev_gray;
  unsigned int prev_red;
  unsigned int prev_green;
  unsigned int prev_blue;
  unsigned int prev_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (src_bit_depth != 8)
  {
    return 0x0000;
  }
  assert(!(color_type & 1));
  row_ptr = png_get_rows(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);
  alpha_row = (png_bytep) png_malloc(png_ptr, width);
  row_info.width = width;
  row_info.rowbytes = 0;
  row_info.color_type = (png_byte) color_type;
  row_info.bit_depth = (png_byte) src_bit_depth;
  row_info.channels = (png_byte) channels;
  row_info.pixel_depth = 0;
  num_palette = (num_trans = 0);
  trans_color = 0;
  png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color);
  prev_gray = (prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1)))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_reduce_to_palette_1(&sample_ptr, &gray, &red, &green, &blue, &alpha, &prev_gray, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, &j, row_info, row_ptr, alpha_row, height, width, color_type, channels, palette, trans_alpha, trans_color, num_palette, num_trans, index);
  }

  if ((num_palette >= 0) && png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (color_type & 2)
    {
      red = background->red;
      green = background->green;
      blue = background->blue;
    }
    else
      red = (green = (blue = background->gray));
    if (((red > 255) || (green > 255)) || (blue > 255))
    {
      png_warning(png_ptr, "Invalid colors in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
    else
    {
      opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, (unsigned int) (-1), &index);
      if (index >= 0)
      {
        background->index = (png_byte) index;
      }
    }
  }
  if (num_palette >= 0)
  {
    assert((num_palette > 0) && (num_palette <= 256));
    assert((num_trans >= 0) && (num_trans <= num_palette));
    if (num_palette <= 2)
    {
      dest_bit_depth = 1;
    }
    else
      if (num_palette <= 4)
    {
      dest_bit_depth = 2;
    }
    else
      if (num_palette <= 16)
    {
      dest_bit_depth = 4;
    }
    else
      dest_bit_depth = 8;
    if (((channels * 8) == dest_bit_depth) || (((((((3 * num_palette) + num_trans) * 8) / ((channels * 8) - dest_bit_depth)) / width) / height) >= 1))
    {
      num_palette = -1;
    }
  }
  if (num_palette < 0)
  {
    png_free(png_ptr, alpha_row);
    return 0x0000;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  index = -1;
  prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_reduce_to_palette_2(&row_ptr, &sample_ptr, &index, &gray, &red, &green, &blue, &alpha, &prev_gray, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, row_info, alpha_row, width, color_type, channels, palette, trans_alpha, trans_color, num_palette, num_trans);
  }

  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, interlace_type, compression_type, filter_type);
  png_set_PLTE(png_ptr, info_ptr, palette, num_palette);
  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, trans_alpha, num_trans, 0);
  }
  png_free(png_ptr, alpha_row);
  result = 0x0010;
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
  }
  return result;
}

static void opng_analyze_sample_usage(png_structp png_ptr, png_infop info_ptr, png_bytep usage_map)
{
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int init_shift;
  int init_mask;
  int shift;
  int mask;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  height = png_get_image_height(png_ptr, info_ptr);
  width = png_get_image_width(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  memset(usage_map, 0, 256);
  if (bit_depth == 8)
  {
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      for (j = 0, sample_ptr = *row_ptr; j < width; j += 1, sample_ptr += 1)
      {
        usage_map[*sample_ptr] = 1;
      }

    }

  }
  else
  {
    helper_opng_analyze_sample_usage_1(&usage_map, &row_ptr, &sample_ptr, &init_shift, &init_mask, &shift, &mask, &i, &j, width, height, bit_depth);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    usage_map[background->index] = 1;
  }
}

static png_uint_32 opng_reduce_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_colorp palette;
  png_bytep trans_alpha;
  png_bytepp row_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int num_palette;
  int num_trans;
  int last_color_index;
  int last_trans_index;
  png_byte crt_trans_value;
  png_byte last_trans_value;
  png_byte is_used[256];
  png_color_16 gray_trans;
  int is_gray;
  png_color_16p background;
  png_uint_16p hist;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  result = 0x0000;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    palette = 0;
    num_palette = 0;
  }
  if (!png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0))
  {
    trans_alpha = 0;
    num_trans = 0;
  }
  else
    assert((trans_alpha != 0) && (num_trans > 0));
  opng_analyze_sample_usage(png_ptr, info_ptr, is_used);
  is_gray = (reductions & 0x0080) && (bit_depth == 8);
  last_color_index = (last_trans_index = -1);
  for (k = 0; k < 256; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    last_color_index = k;
    if ((k < num_trans) && (trans_alpha[k] < 255))
    {
      last_trans_index = k;
    }
    if (is_gray)
    {
      if ((palette[k].red != palette[k].green) || (palette[k].red != palette[k].blue))
      {
        is_gray = 0;
      }
    }
  }

  assert(last_color_index >= 0);
  assert(last_color_index >= last_trans_index);
  if (last_color_index >= num_palette)
  {
    png_warning(png_ptr, "Too few colors in PLTE");
    opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (last_color_index + 1));
    result |= 0x2000;
  }
  if (num_trans > num_palette)
  {
    png_warning(png_ptr, "Too many alpha values in tRNS");
    result |= 0x2000;
  }
  if (is_gray && (last_trans_index >= 0))
  {
    helper_opng_reduce_palette_1(&crt_trans_value, &last_trans_value, &gray_trans, &is_gray, &k, palette, trans_alpha, last_color_index, last_trans_index, is_used);
  }
  if ((num_trans > 0) && (last_trans_index < 0))
  {
    num_trans = 0;
    png_free_data(png_ptr, info_ptr, 0x2000U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0010U);
    result |= 0x0200;
  }
  if (reductions & 0x0200)
  {
    if (num_palette != (last_color_index + 1))
    {
      opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
      png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
      assert(num_palette == (last_color_index + 1));
      result |= 0x0200;
    }
    if ((num_trans > 0) && (num_trans != (last_trans_index + 1)))
    {
      opng_realloc_tRNS(png_ptr, info_ptr, last_trans_index + 1);
      png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0);
      assert(num_trans == (last_trans_index + 1));
      result |= 0x0200;
    }
  }
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  }
  if ((bit_depth < 8) || (!is_gray))
  {
    return result;
  }
  for (i = 0; i < height; i += 1)
  {
    for (j = 0; j < width; j += 1)
    {
      row_ptr[i][j] = palette[row_ptr[i][j]].red;
    }

  }

  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, 0, 0, &gray_trans);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    background->gray = palette[background->index].red;
  }
  if (png_get_hIST(png_ptr, info_ptr, &hist))
  {
    png_free_data(png_ptr, info_ptr, 0x0008U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0040U);
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 0, interlace_type, compression_type, filter_type);
  png_free_data(png_ptr, info_ptr, 0x1000U, -1);
  png_set_invalid(png_ptr, info_ptr, 0x0008U);
  return 0x0080;
}

png_uint_32 opng_reduce_image(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  int color_type;
  (void) 0;
  if (!opng_validate_image(png_ptr, info_ptr))
  {
    png_warning(png_ptr, "Image reduction requires the presence of all critical information");
    return 0x0000;
  }
  color_type = png_get_color_type(png_ptr, info_ptr);
  result = opng_reduce_bits(png_ptr, info_ptr, reductions);
  if ((color_type == (2 | 1)) && (reductions & ((0x0080 | 0x0200) | 0x0002)))
  {
    result |= opng_reduce_palette(png_ptr, info_ptr, reductions);
  }
  if ((((color_type & (~4)) == 0) && (reductions & 0x0040)) || (((color_type & (~4)) == 2) && (reductions & 0x0010)))
  {
    if (!(result & 0x0080))
    {
      result |= opng_reduce_to_palette(png_ptr, info_ptr, reductions);
    }
  }
  return result;
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
int opng_validate_image(png_structp png_ptr, png_infop info_ptr);
png_uint_32 opng_reduce_image(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions);
int opng_validate_image(png_structp png_ptr, png_infop info_ptr)
{
  (void) 0;
  if (png_get_bit_depth(png_ptr, info_ptr) == 0)
  {
    return 0;
  }
  if (png_get_color_type(png_ptr, info_ptr) & 1)
  {
    if (!png_get_valid(png_ptr, info_ptr, 0x0008U))
    {
      return 0;
    }
  }
  if (!png_get_valid(png_ptr, info_ptr, 0x8000U))
  {
    return 0;
  }
  return 1;
}

static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
}

static void opng_realloc_PLTE(png_structp png_ptr, png_infop info_ptr, int num_palette)
{
  png_color buffer[256];
  png_colorp palette;
  int src_num_palette;
  png_bytep buffer_ptr;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p background;
  (void) 0;
  assert(num_palette > 0);
  src_num_palette = 0;
  png_get_PLTE(png_ptr, info_ptr, &palette, &src_num_palette);
  if (num_palette == src_num_palette)
  {
    return;
  }
  memcpy(buffer, palette, num_palette * (sizeof(png_color)));
  if (num_palette > src_num_palette)
  {
    memset(buffer + src_num_palette, 0, (num_palette - src_num_palette) * (sizeof(png_color)));
  }
  png_set_PLTE(png_ptr, info_ptr, buffer, num_palette);
  if (num_palette < src_num_palette)
  {
    if (png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0) && (num_trans > num_palette))
    {
      buffer_ptr = (png_bytep) ((png_voidp) buffer);
      png_warning(png_ptr, "Too many alpha values in tRNS");
      num_trans = num_palette;
      memcpy(buffer_ptr, trans_alpha, (size_t) num_trans);
      png_set_tRNS(png_ptr, info_ptr, buffer_ptr, num_trans, 0);
    }
    if (png_get_bKGD(png_ptr, info_ptr, &background) && (background->index >= num_palette))
    {
      png_warning(png_ptr, "Invalid color index in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
  }
}

static void opng_realloc_tRNS(png_structp png_ptr, png_infop info_ptr, int num_trans)
{
  png_byte buffer[256];
  png_bytep trans_alpha;
  int src_num_trans;
  (void) 0;
  assert(num_trans > 0);
  src_num_trans = 0;
  png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &src_num_trans, 0);
  if (num_trans == src_num_trans)
  {
    return;
  }
  memcpy(buffer, trans_alpha, (size_t) num_trans);
  if (num_trans > src_num_trans)
  {
    memset(buffer + src_num_trans, 0, num_trans - src_num_trans);
  }
  png_set_tRNS(png_ptr, info_ptr, buffer, num_trans, 0);
}

static void opng_get_alpha_row(png_row_infop row_info_ptr, png_color_16p trans_color, png_bytep row, png_bytep alpha_row)
{
  png_bytep sample_ptr;
  png_uint_32 width;
  int color_type;
  int bit_depth;
  int channels;
  png_byte trans_red;
  png_byte trans_green;
  png_byte trans_blue;
  png_byte trans_gray;
  png_uint_32 i;
  width = row_info_ptr->width;
  color_type = row_info_ptr->color_type;
  bit_depth = row_info_ptr->bit_depth;
  channels = row_info_ptr->channels;
  assert(!(color_type & 1));
  assert(bit_depth == 8);
  if (!(color_type & 4))
  {
    if (trans_color == 0)
    {
      memset(alpha_row, 255, (size_t) width);
      return;
    }
    if (color_type == 2)
    {
      assert(channels == 3);
      trans_red = (png_byte) trans_color->red;
      trans_green = (png_byte) trans_color->green;
      trans_blue = (png_byte) trans_color->blue;
      sample_ptr = row;
      for (i = 0; i < width; i += 1, sample_ptr += 3)
      {
        alpha_row[i] = (png_byte) ((((sample_ptr[0] == trans_red) && (sample_ptr[1] == trans_green)) && (sample_ptr[2] == trans_blue)) ? (0) : (255));
      }

    }
    else
    {
      assert(color_type == 0);
      assert(channels == 1);
      trans_gray = (png_byte) trans_color->gray;
      for (i = 0; i < width; i += 1)
      {
        alpha_row[i] = (png_byte) ((row[i] == trans_gray) ? (0) : (255));
      }

    }
    return;
  }
  assert(channels > 1);
  sample_ptr = row + (channels - 1);
  for (i = 0; i < width; i += 1, sample_ptr += channels, alpha_row += 1)
  {
    *alpha_row = *sample_ptr;
  }

}

static png_uint_32 opng_analyze_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep component_ptr;
  png_uint_32 height;
  png_uint_32 width;
  int bit_depth;
  int color_type;
  int byte_depth;
  int channels;
  int sample_size;
  int offset_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  if (bit_depth < 8)
  {
    return 0x0000;
  }
  if (color_type & 1)
  {
    return 0x0000;
  }
  byte_depth = bit_depth / 8;
  channels = png_get_channels(png_ptr, info_ptr);
  sample_size = channels * byte_depth;
  offset_alpha = (channels - 1) * byte_depth;
  reductions &= (0x0001 | 0x0004) | 0x0008;
  if (bit_depth <= 8)
  {
    reductions &= ~0x0001;
  }
  if (!(color_type & 2))
  {
    reductions &= ~0x0004;
  }
  if (!(color_type & 4))
  {
    reductions &= ~0x0008;
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      if (((((background->red % 257) != 0) || ((background->green % 257) != 0)) || ((background->blue % 257) != 0)) || ((background->gray % 257) != 0))
      {
        reductions &= ~0x0001;
      }
    }
    if (reductions & 0x0004)
    {
      if ((background->red != background->green) || (background->red != background->blue))
      {
        reductions &= ~0x0004;
      }
    }
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    if (reductions == 0x0000)
    {
      return 0x0000;
    }
    if (reductions & 0x0001)
    {
      component_ptr = *row_ptr;
      for (j = 0; j < (channels * width); j += 1, component_ptr += 2)
      {
        if (component_ptr[0] != component_ptr[1])
        {
          reductions &= ~0x0001;
          break;
        }
      }

    }
    if (bit_depth == 8)
    {
      if (reductions & 0x0004)
      {
        component_ptr = *row_ptr;
        for (j = 0; j < width; j += 1, component_ptr += sample_size)
        {
          if ((component_ptr[0] != component_ptr[1]) || (component_ptr[0] != component_ptr[2]))
          {
            reductions &= ~0x0004;
            break;
          }
        }

      }
      if (reductions & 0x0008)
      {
        component_ptr = (*row_ptr) + offset_alpha;
        for (j = 0; j < width; j += 1, component_ptr += sample_size)
        {
          if (component_ptr[0] != 255)
          {
            reductions &= ~0x0008;
            break;
          }
        }

      }
    }
    else
    {
      if (reductions & 0x0004)
      {
        component_ptr = *row_ptr;
        for (j = 0; j < width; j += 1, component_ptr += sample_size)
        {
          if ((((component_ptr[0] != component_ptr[2]) || (component_ptr[0] != component_ptr[4])) || (component_ptr[1] != component_ptr[3])) || (component_ptr[1] != component_ptr[5]))
          {
            reductions &= ~0x0004;
            break;
          }
        }

      }
      if (reductions & 0x0008)
      {
        component_ptr = (*row_ptr) + offset_alpha;
        for (j = 0; j < width; j += 1, component_ptr += sample_size)
        {
          if ((component_ptr[0] != 255) || (component_ptr[1] != 255))
          {
            reductions &= ~0x0008;
            break;
          }
        }

      }
    }
  }

  return reductions;
}

static png_uint_32 opng_reduce_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep src_ptr;
  png_bytep dest_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int src_byte_depth;
  int dest_byte_depth;
  int src_color_type;
  int dest_color_type;
  int src_channels;
  int dest_channels;
  int src_sample_size;
  int dest_sample_size;
  int tran_tbl[8];
  png_color_16p trans_color;
  png_color_16p background;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  reductions = opng_analyze_bits(png_ptr, info_ptr, reductions);
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &src_color_type, &interlace_type, &compression_type, &filter_type);
  assert(src_bit_depth >= 8);
  if (reductions & 0x0001)
  {
    assert(src_bit_depth == 16);
    dest_bit_depth = 8;
  }
  else
    dest_bit_depth = src_bit_depth;
  src_byte_depth = src_bit_depth / 8;
  dest_byte_depth = dest_bit_depth / 8;
  dest_color_type = src_color_type;
  if (reductions & 0x0004)
  {
    assert(src_color_type & 2);
    dest_color_type &= ~2;
  }
  if (reductions & 0x0008)
  {
    assert(src_color_type & 4);
    dest_color_type &= ~4;
  }
  src_channels = png_get_channels(png_ptr, info_ptr);
  dest_channels = ((dest_color_type & 2) ? (3) : (1)) + ((dest_color_type & 4) ? (1) : (0));
  src_sample_size = src_channels * src_byte_depth;
  dest_sample_size = dest_channels * dest_byte_depth;
  for (k = 0; k < (4 * dest_byte_depth); k += 1)
  {
    tran_tbl[k] = (k * src_bit_depth) / dest_bit_depth;
  }

  if ((reductions & 0x0004) && (dest_color_type & 4))
  {
    tran_tbl[dest_byte_depth] = tran_tbl[3 * dest_byte_depth];
    if (dest_byte_depth == 2)
    {
      tran_tbl[dest_byte_depth + 1] = tran_tbl[(3 * dest_byte_depth) + 1];
    }
  }
  assert(src_sample_size > dest_sample_size);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_ptr = (dest_ptr = *row_ptr);
    for (j = 0; j < width; j += 1)
    {
      for (k = 0; k < dest_sample_size; k += 1)
      {
        dest_ptr[k] = src_ptr[tran_tbl[k]];
      }

      src_ptr += src_sample_size;
      dest_ptr += dest_sample_size;
    }

  }

  if (png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color))
  {
    if (reductions & 0x0001)
    {
      if (((((trans_color->red % 257) == 0) && ((trans_color->green % 257) == 0)) && ((trans_color->blue % 257) == 0)) && ((trans_color->gray % 257) == 0))
      {
        trans_color->red &= 255;
        trans_color->green &= 255;
        trans_color->blue &= 255;
        trans_color->gray &= 255;
      }
      else
      {
        png_free_data(png_ptr, info_ptr, 0x2000U, -1);
        png_set_invalid(png_ptr, info_ptr, 0x0010U);
      }
    }
    if (reductions & 0x0004)
    {
      if ((trans_color->red == trans_color->green) || (trans_color->red == trans_color->blue))
      {
        trans_color->gray = trans_color->red;
      }
      else
      {
        png_free_data(png_ptr, info_ptr, 0x2000U, -1);
        png_set_invalid(png_ptr, info_ptr, 0x0010U);
      }
    }
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      background->red &= 255;
      background->green &= 255;
      background->blue &= 255;
      background->gray &= 255;
    }
    if (reductions & 0x0004)
    {
      background->gray = background->red;
    }
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    if (reductions & 0x0001)
    {
      if (sig_bits->red > 8)
      {
        sig_bits->red = 8;
      }
      if (sig_bits->green > 8)
      {
        sig_bits->green = 8;
      }
      if (sig_bits->blue > 8)
      {
        sig_bits->blue = 8;
      }
      if (sig_bits->gray > 8)
      {
        sig_bits->gray = 8;
      }
      if (sig_bits->alpha > 8)
      {
        sig_bits->alpha = 8;
      }
    }
    if (reductions & 0x0004)
    {
      png_byte max_sig_bits = sig_bits->red;
      if (max_sig_bits < sig_bits->green)
      {
        max_sig_bits = sig_bits->green;
      }
      if (max_sig_bits < sig_bits->blue)
      {
        max_sig_bits = sig_bits->blue;
      }
      sig_bits->gray = max_sig_bits;
    }
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, dest_color_type, interlace_type, compression_type, filter_type);
  return reductions;
}

static png_uint_32 opng_reduce_palette_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_bytepp row_ptr;
  png_bytep src_sample_ptr;
  png_bytep dest_sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  unsigned int src_mask_init;
  unsigned int src_mask;
  unsigned int src_shift;
  unsigned int dest_shift;
  unsigned int sample;
  unsigned int dest_buf;
  png_colorp palette;
  int num_palette;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  if (!(reductions & 0x0002))
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (color_type != (2 | 1))
  {
    return 0x0000;
  }
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    num_palette = 0;
  }
  result = 0x0000;
  if (num_palette > (1 << src_bit_depth))
  {
    png_warning(png_ptr, "Too many colors in PLTE");
    num_palette = 1 << src_bit_depth;
    opng_realloc_PLTE(png_ptr, info_ptr, num_palette);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (1 << src_bit_depth));
    result |= 0x2000;
  }
  if (num_palette > 16)
  {
    return result;
  }
  else
    if (num_palette > 4)
  {
    dest_bit_depth = 4;
  }
  else
    if (num_palette > 2)
  {
    dest_bit_depth = 2;
  }
  else
  {
    assert(num_palette > 0);
    dest_bit_depth = 1;
  }
  if (src_bit_depth <= dest_bit_depth)
  {
    assert(src_bit_depth == dest_bit_depth);
    return result;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (src_bit_depth == 8)
  {
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      src_sample_ptr = (dest_sample_ptr = *row_ptr);
      dest_shift = 8;
      dest_buf = 0;
      for (j = 0; j < width; j += 1)
      {
        dest_shift -= dest_bit_depth;
        if (dest_shift > 0)
        {
          dest_buf |= (*src_sample_ptr) << dest_shift;
        }
        else
        {
          *dest_sample_ptr = (png_byte) (dest_buf | (*src_sample_ptr));
          dest_sample_ptr += 1;
          dest_shift = 8;
          dest_buf = 0;
        }
        src_sample_ptr += 1;
      }

      if (dest_shift != 0)
      {
        *dest_sample_ptr = (png_byte) dest_buf;
      }
    }

  }
  else
  {
    src_mask_init = (1 << (8 + src_bit_depth)) - (1 << 8);
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      src_sample_ptr = (dest_sample_ptr = *row_ptr);
      src_shift = (dest_shift = 8);
      src_mask = src_mask_init;
      dest_buf = 0;
      for (j = 0; j < width; j += 1)
      {
        src_shift -= src_bit_depth;
        src_mask >>= src_bit_depth;
        sample = ((*src_sample_ptr) & src_mask) >> src_shift;
        dest_shift -= dest_bit_depth;
        if (dest_shift > 0)
        {
          dest_buf |= sample << dest_shift;
        }
        else
        {
          *dest_sample_ptr = (png_byte) (dest_buf | sample);
          dest_sample_ptr += 1;
          dest_shift = 8;
          dest_buf = 0;
        }
        if (src_shift == 0)
        {
          src_shift = 8;
          src_mask = src_mask_init;
          src_sample_ptr += 1;
        }
      }

      if (dest_shift != 0)
      {
        *dest_sample_ptr = (png_byte) dest_buf;
      }
    }

  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, color_type, interlace_type, compression_type, filter_type);
  result |= 0x0002;
  return result;
}

static png_uint_32 opng_reduce_to_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_row_info row_info;
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_bytep alpha_row;
  png_uint_32 height;
  png_uint_32 width;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int channels;
  png_color palette[256];
  png_byte trans_alpha[256];
  png_color_16p trans_color;
  int num_palette;
  int num_trans;
  int index;
  unsigned int gray;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int alpha;
  unsigned int prev_gray;
  unsigned int prev_red;
  unsigned int prev_green;
  unsigned int prev_blue;
  unsigned int prev_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (src_bit_depth != 8)
  {
    return 0x0000;
  }
  assert(!(color_type & 1));
  row_ptr = png_get_rows(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);
  alpha_row = (png_bytep) png_malloc(png_ptr, width);
  row_info.width = width;
  row_info.rowbytes = 0;
  row_info.color_type = (png_byte) color_type;
  row_info.bit_depth = (png_byte) src_bit_depth;
  row_info.channels = (png_byte) channels;
  row_info.pixel_depth = 0;
  num_palette = (num_trans = 0);
  trans_color = 0;
  png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color);
  prev_gray = (prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1)))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    sample_ptr = *row_ptr;
    opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
    if (color_type & 2)
    {
      for (j = 0; j < width; j += 1, sample_ptr += channels)
      {
        red = sample_ptr[0];
        green = sample_ptr[1];
        blue = sample_ptr[2];
        alpha = alpha_row[j];
        if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
        {
          prev_red = red;
          prev_green = green;
          prev_blue = blue;
          prev_alpha = alpha;
          if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) < 0)
          {
            assert(num_palette < 0);
            i = height;
            break;
          }
        }
      }

    }
    else
    {
      for (j = 0; j < width; j += 1, sample_ptr += channels)
      {
        gray = sample_ptr[0];
        alpha = alpha_row[j];
        if ((gray != prev_gray) || (alpha != prev_alpha))
        {
          prev_gray = gray;
          prev_alpha = alpha;
          if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) < 0)
          {
            assert(num_palette < 0);
            i = height;
            break;
          }
        }
      }

    }
  }

  if ((num_palette >= 0) && png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (color_type & 2)
    {
      red = background->red;
      green = background->green;
      blue = background->blue;
    }
    else
      red = (green = (blue = background->gray));
    if (((red > 255) || (green > 255)) || (blue > 255))
    {
      png_warning(png_ptr, "Invalid colors in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
    else
    {
      opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, (unsigned int) (-1), &index);
      if (index >= 0)
      {
        background->index = (png_byte) index;
      }
    }
  }
  if (num_palette >= 0)
  {
    assert((num_palette > 0) && (num_palette <= 256));
    assert((num_trans >= 0) && (num_trans <= num_palette));
    if (num_palette <= 2)
    {
      dest_bit_depth = 1;
    }
    else
      if (num_palette <= 4)
    {
      dest_bit_depth = 2;
    }
    else
      if (num_palette <= 16)
    {
      dest_bit_depth = 4;
    }
    else
      dest_bit_depth = 8;
    if (((channels * 8) == dest_bit_depth) || (((((((3 * num_palette) + num_trans) * 8) / ((channels * 8) - dest_bit_depth)) / width) / height) >= 1))
    {
      num_palette = -1;
    }
  }
  if (num_palette < 0)
  {
    png_free(png_ptr, alpha_row);
    return 0x0000;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  index = -1;
  prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    sample_ptr = *row_ptr;
    opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
    if (color_type & 2)
    {
      for (j = 0; j < width; j += 1, sample_ptr += channels)
      {
        red = sample_ptr[0];
        green = sample_ptr[1];
        blue = sample_ptr[2];
        alpha = alpha_row[j];
        if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
        {
          prev_red = red;
          prev_green = green;
          prev_blue = blue;
          prev_alpha = alpha;
          if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) != 0)
          {
            index = -1;
          }
        }
        assert(index >= 0);
        (*row_ptr)[j] = (png_byte) index;
      }

    }
    else
    {
      for (j = 0; j < width; j += 1, sample_ptr += channels)
      {
        gray = sample_ptr[0];
        alpha = alpha_row[j];
        if ((gray != prev_gray) || (alpha != prev_alpha))
        {
          prev_gray = gray;
          prev_alpha = alpha;
          if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) != 0)
          {
            index = -1;
          }
        }
        assert(index >= 0);
        (*row_ptr)[j] = (png_byte) index;
      }

    }
  }

  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, interlace_type, compression_type, filter_type);
  png_set_PLTE(png_ptr, info_ptr, palette, num_palette);
  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, trans_alpha, num_trans, 0);
  }
  png_free(png_ptr, alpha_row);
  result = 0x0010;
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
  }
  return result;
}

static void opng_analyze_sample_usage(png_structp png_ptr, png_infop info_ptr, png_bytep usage_map)
{
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int init_shift;
  int init_mask;
  int shift;
  int mask;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  height = png_get_image_height(png_ptr, info_ptr);
  width = png_get_image_width(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  memset(usage_map, 0, 256);
  if (bit_depth == 8)
  {
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      for (j = 0, sample_ptr = *row_ptr; j < width; j += 1, sample_ptr += 1)
      {
        usage_map[*sample_ptr] = 1;
      }

    }

  }
  else
  {
    assert(bit_depth < 8);
    init_shift = 8 - bit_depth;
    init_mask = (1 << 8) - (1 << init_shift);
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      for (j = 0, sample_ptr = *row_ptr; j < width; sample_ptr += 1)
      {
        mask = init_mask;
        shift = init_shift;
        do
        {
          usage_map[((*sample_ptr) & mask) >> shift] = 1;
          mask >>= bit_depth;
          shift -= bit_depth;
          j += 1;
        }
        while ((mask > 0) && (j < width));
      }

    }

  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    usage_map[background->index] = 1;
  }
}

static png_uint_32 opng_reduce_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_colorp palette;
  png_bytep trans_alpha;
  png_bytepp row_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int num_palette;
  int num_trans;
  int last_color_index;
  int last_trans_index;
  png_byte crt_trans_value;
  png_byte last_trans_value;
  png_byte is_used[256];
  png_color_16 gray_trans;
  int is_gray;
  png_color_16p background;
  png_uint_16p hist;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  result = 0x0000;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    palette = 0;
    num_palette = 0;
  }
  if (!png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0))
  {
    trans_alpha = 0;
    num_trans = 0;
  }
  else
    assert((trans_alpha != 0) && (num_trans > 0));
  opng_analyze_sample_usage(png_ptr, info_ptr, is_used);
  is_gray = (reductions & 0x0080) && (bit_depth == 8);
  last_color_index = (last_trans_index = -1);
  for (k = 0; k < 256; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    last_color_index = k;
    if ((k < num_trans) && (trans_alpha[k] < 255))
    {
      last_trans_index = k;
    }
    if (is_gray)
    {
      if ((palette[k].red != palette[k].green) || (palette[k].red != palette[k].blue))
      {
        is_gray = 0;
      }
    }
  }

  assert(last_color_index >= 0);
  assert(last_color_index >= last_trans_index);
  if (last_color_index >= num_palette)
  {
    png_warning(png_ptr, "Too few colors in PLTE");
    opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (last_color_index + 1));
    result |= 0x2000;
  }
  if (num_trans > num_palette)
  {
    png_warning(png_ptr, "Too many alpha values in tRNS");
    result |= 0x2000;
  }
  if (is_gray && (last_trans_index >= 0))
  {
    gray_trans.gray = palette[last_trans_index].red;
    last_trans_value = trans_alpha[last_trans_index];
    for (k = 0; k <= last_color_index; k += 1)
    {
      if (!is_used[k])
      {
        continue;
      }
      if (k <= last_trans_index)
      {
        crt_trans_value = trans_alpha[k];
        if ((crt_trans_value < 255) && (palette[k].red != gray_trans.gray))
        {
          is_gray = 0;
          break;
        }
      }
      else
        crt_trans_value = 255;
      if ((palette[k].red == gray_trans.gray) && (crt_trans_value != last_trans_value))
      {
        is_gray = 0;
        break;
      }
    }

  }
  if ((num_trans > 0) && (last_trans_index < 0))
  {
    num_trans = 0;
    png_free_data(png_ptr, info_ptr, 0x2000U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0010U);
    result |= 0x0200;
  }
  if (reductions & 0x0200)
  {
    if (num_palette != (last_color_index + 1))
    {
      opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
      png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
      assert(num_palette == (last_color_index + 1));
      result |= 0x0200;
    }
    if ((num_trans > 0) && (num_trans != (last_trans_index + 1)))
    {
      opng_realloc_tRNS(png_ptr, info_ptr, last_trans_index + 1);
      png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0);
      assert(num_trans == (last_trans_index + 1));
      result |= 0x0200;
    }
  }
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  }
  if ((bit_depth < 8) || (!is_gray))
  {
    return result;
  }
  for (i = 0; i < height; i += 1)
  {
    for (j = 0; j < width; j += 1)
    {
      row_ptr[i][j] = palette[row_ptr[i][j]].red;
    }

  }

  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, 0, 0, &gray_trans);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    background->gray = palette[background->index].red;
  }
  if (png_get_hIST(png_ptr, info_ptr, &hist))
  {
    png_free_data(png_ptr, info_ptr, 0x0008U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0040U);
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 0, interlace_type, compression_type, filter_type);
  png_free_data(png_ptr, info_ptr, 0x1000U, -1);
  png_set_invalid(png_ptr, info_ptr, 0x0008U);
  return 0x0080;
}

png_uint_32 opng_reduce_image(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  int color_type;
  (void) 0;
  if (!opng_validate_image(png_ptr, info_ptr))
  {
    png_warning(png_ptr, "Image reduction requires the presence of all critical information");
    return 0x0000;
  }
  color_type = png_get_color_type(png_ptr, info_ptr);
  result = opng_reduce_bits(png_ptr, info_ptr, reductions);
  if ((color_type == (2 | 1)) && (reductions & ((0x0080 | 0x0200) | 0x0002)))
  {
    result |= opng_reduce_palette(png_ptr, info_ptr, reductions);
  }
  if ((((color_type & (~4)) == 0) && (reductions & 0x0040)) || (((color_type & (~4)) == 2) && (reductions & 0x0010)))
  {
    if (!(result & 0x0080))
    {
      result |= opng_reduce_to_palette(png_ptr, info_ptr, reductions);
    }
  }
  return result;
}

void helper_opng_get_alpha_row_1(png_bytep * const alpha_row_ref, png_bytep * const sample_ptr_ref, png_byte * const trans_red_ref, png_byte * const trans_green_ref, png_byte * const trans_blue_ref, png_byte * const trans_gray_ref, png_uint_32 * const i_ref, png_color_16p trans_color, png_bytep row, png_uint_32 width, int color_type, int channels)
{
  png_bytep alpha_row = *alpha_row_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  png_byte trans_red = *trans_red_ref;
  png_byte trans_green = *trans_green_ref;
  png_byte trans_blue = *trans_blue_ref;
  png_byte trans_gray = *trans_gray_ref;
  png_uint_32 i = *i_ref;
  if (trans_color == 0)
  {
    memset(alpha_row, 255, (size_t) width);
    return;
  }
  if (color_type == 2)
  {
    assert(channels == 3);
    trans_red = (png_byte) trans_color->red;
    trans_green = (png_byte) trans_color->green;
    trans_blue = (png_byte) trans_color->blue;
    sample_ptr = row;
    for (i = 0; i < width; i += 1, sample_ptr += 3)
    {
      alpha_row[i] = (png_byte) ((((sample_ptr[0] == trans_red) && (sample_ptr[1] == trans_green)) && (sample_ptr[2] == trans_blue)) ? (0) : (255));
    }

  }
  else
  {
    assert(color_type == 0);
    assert(channels == 1);
    trans_gray = (png_byte) trans_color->gray;
    for (i = 0; i < width; i += 1)
    {
      alpha_row[i] = (png_byte) ((row[i] == trans_gray) ? (0) : (255));
    }

  }
  return;
  *alpha_row_ref = alpha_row;
  *sample_ptr_ref = sample_ptr;
  *trans_red_ref = trans_red;
  *trans_green_ref = trans_green;
  *trans_blue_ref = trans_blue;
  *trans_gray_ref = trans_gray;
  *i_ref = i;
}

png_uint_32 helper_opng_analyze_bits_1(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int bit_depth, int channels, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  if (reductions & 0x0001)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < (channels * width); j += 1, component_ptr += 2)
    {
      if (component_ptr[0] != component_ptr[1])
      {
        reductions &= ~0x0001;
        break;
      }
    }

  }
  if (bit_depth == 8)
  {
    helper_helper_opng_analyze_bits_1_1(&reductions, &component_ptr, &j, row_ptr, width, sample_size, offset_alpha);
  }
  else
  {
    helper_helper_opng_analyze_bits_1_2(&reductions, &component_ptr, &j, row_ptr, width, sample_size, offset_alpha);
  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}

void helper_opng_reduce_bits_1(png_color_16p * const trans_color_ref, png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_color_16p trans_color = *trans_color_ref;
  if (reductions & 0x0001)
  {
    if (((((trans_color->red % 257) == 0) && ((trans_color->green % 257) == 0)) && ((trans_color->blue % 257) == 0)) && ((trans_color->gray % 257) == 0))
    {
      trans_color->red &= 255;
      trans_color->green &= 255;
      trans_color->blue &= 255;
      trans_color->gray &= 255;
    }
    else
    {
      png_free_data(png_ptr, info_ptr, 0x2000U, -1);
      png_set_invalid(png_ptr, info_ptr, 0x0010U);
    }
  }
  if (reductions & 0x0004)
  {
    if ((trans_color->red == trans_color->green) || (trans_color->red == trans_color->blue))
    {
      trans_color->gray = trans_color->red;
    }
    else
    {
      png_free_data(png_ptr, info_ptr, 0x2000U, -1);
      png_set_invalid(png_ptr, info_ptr, 0x0010U);
    }
  }
  *trans_color_ref = trans_color;
}

void helper_opng_reduce_bits_2(png_color_8p * const sig_bits_ref, png_uint_32 reductions)
{
  png_color_8p sig_bits = *sig_bits_ref;
  if (reductions & 0x0001)
  {
    if (sig_bits->red > 8)
    {
      sig_bits->red = 8;
    }
    if (sig_bits->green > 8)
    {
      sig_bits->green = 8;
    }
    if (sig_bits->blue > 8)
    {
      sig_bits->blue = 8;
    }
    if (sig_bits->gray > 8)
    {
      sig_bits->gray = 8;
    }
    if (sig_bits->alpha > 8)
    {
      sig_bits->alpha = 8;
    }
  }
  if (reductions & 0x0004)
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  *sig_bits_ref = sig_bits;
}

void helper_opng_reduce_palette_bits_1(png_bytepp * const row_ptr_ref, png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const dest_shift_ref, unsigned int * const dest_buf_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int dest_bit_depth)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_sample_ptr = (dest_sample_ptr = *row_ptr);
    dest_shift = 8;
    dest_buf = 0;
    for (j = 0; j < width; j += 1)
    {
      dest_shift -= dest_bit_depth;
      if (dest_shift > 0)
      {
        dest_buf |= (*src_sample_ptr) << dest_shift;
      }
      else
      {
        *dest_sample_ptr = (png_byte) (dest_buf | (*src_sample_ptr));
        dest_sample_ptr += 1;
        dest_shift = 8;
        dest_buf = 0;
      }
      src_sample_ptr += 1;
    }

    if (dest_shift != 0)
    {
      *dest_sample_ptr = (png_byte) dest_buf;
    }
  }

  *row_ptr_ref = row_ptr;
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *dest_shift_ref = dest_shift;
  *dest_buf_ref = dest_buf;
  *i_ref = i;
  *j_ref = j;
}

void helper_opng_reduce_palette_bits_2(png_bytepp * const row_ptr_ref, png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_init_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int src_bit_depth, int dest_bit_depth)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask_init = *src_mask_init_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  src_mask_init = (1 << (8 + src_bit_depth)) - (1 << 8);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_helper_opng_reduce_palette_bits_2_1(&src_sample_ptr, &dest_sample_ptr, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &j, width, src_bit_depth, dest_bit_depth, row_ptr, src_mask_init);
  }

  *row_ptr_ref = row_ptr;
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_init_ref = src_mask_init;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
  *i_ref = i;
  *j_ref = j;
}

void helper_opng_reduce_to_palette_1(png_bytep * const sample_ptr_ref, unsigned int * const gray_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_gray_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_row_info row_info, png_bytepp row_ptr, png_bytep alpha_row, png_uint_32 height, png_uint_32 width, int color_type, int channels, png_color palette[256], png_byte trans_alpha[256], png_color_16p trans_color, int num_palette, int num_trans, int index)
{
  png_bytep sample_ptr = *sample_ptr_ref;
  unsigned int gray = *gray_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_gray = *prev_gray_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  sample_ptr = *row_ptr;
  opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
  if (color_type & 2)
  {
    helper_helper_opng_reduce_to_palette_1_1(&sample_ptr, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, &j, alpha_row, height, width, channels, palette, trans_alpha, num_palette, num_trans, index);
  }
  else
  {
    for (j = 0; j < width; j += 1, sample_ptr += channels)
    {
      gray = sample_ptr[0];
      alpha = alpha_row[j];
      if ((gray != prev_gray) || (alpha != prev_alpha))
      {
        prev_gray = gray;
        prev_alpha = alpha;
        if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) < 0)
        {
          assert(num_palette < 0);
          i = height;
          break;
        }
      }
    }

  }
  *sample_ptr_ref = sample_ptr;
  *gray_ref = gray;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_gray_ref = prev_gray;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
  *j_ref = j;
}

void helper_opng_reduce_to_palette_2(png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const index_ref, unsigned int * const gray_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_gray_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_row_info row_info, png_bytep alpha_row, png_uint_32 width, int color_type, int channels, png_color palette[256], png_byte trans_alpha[256], png_color_16p trans_color, int num_palette, int num_trans)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int index = *index_ref;
  unsigned int gray = *gray_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_gray = *prev_gray_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  sample_ptr = *row_ptr;
  opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
  if (color_type & 2)
  {
    helper_helper_opng_reduce_to_palette_2_1(&row_ptr, &sample_ptr, &index, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, alpha_row, width, channels, palette, trans_alpha, num_palette, num_trans);
  }
  else
  {
    for (j = 0; j < width; j += 1, sample_ptr += channels)
    {
      gray = sample_ptr[0];
      alpha = alpha_row[j];
      if ((gray != prev_gray) || (alpha != prev_alpha))
      {
        prev_gray = gray;
        prev_alpha = alpha;
        if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) != 0)
        {
          index = -1;
        }
      }
      assert(index >= 0);
      (*row_ptr)[j] = (png_byte) index;
    }

  }
  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *index_ref = index;
  *gray_ref = gray;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_gray_ref = prev_gray;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}

void helper_opng_analyze_sample_usage_1(png_bytep * const usage_map_ref, png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const init_shift_ref, int * const init_mask_ref, int * const shift_ref, int * const mask_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int bit_depth)
{
  png_bytep usage_map = *usage_map_ref;
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int init_shift = *init_shift_ref;
  int init_mask = *init_mask_ref;
  int shift = *shift_ref;
  int mask = *mask_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  assert(bit_depth < 8);
  init_shift = 8 - bit_depth;
  init_mask = (1 << 8) - (1 << init_shift);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    for (j = 0, sample_ptr = *row_ptr; j < width; sample_ptr += 1)
    {
      mask = init_mask;
      shift = init_shift;
      do
      {
        usage_map[((*sample_ptr) & mask) >> shift] = 1;
        mask >>= bit_depth;
        shift -= bit_depth;
        j += 1;
      }
      while ((mask > 0) && (j < width));
    }

  }

  *usage_map_ref = usage_map;
  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *init_shift_ref = init_shift;
  *init_mask_ref = init_mask;
  *shift_ref = shift;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}

void helper_opng_reduce_palette_1(png_byte * const crt_trans_value_ref, png_byte * const last_trans_value_ref, png_color_16 * const gray_trans_ref, int * const is_gray_ref, int * const k_ref, png_colorp palette, png_bytep trans_alpha, int last_color_index, int last_trans_index, png_byte is_used[256])
{
  png_byte crt_trans_value = *crt_trans_value_ref;
  png_byte last_trans_value = *last_trans_value_ref;
  png_color_16 gray_trans = *gray_trans_ref;
  int is_gray = *is_gray_ref;
  int k = *k_ref;
  gray_trans.gray = palette[last_trans_index].red;
  last_trans_value = trans_alpha[last_trans_index];
  for (k = 0; k <= last_color_index; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    if (k <= last_trans_index)
    {
      crt_trans_value = trans_alpha[k];
      if ((crt_trans_value < 255) && (palette[k].red != gray_trans.gray))
      {
        is_gray = 0;
        break;
      }
    }
    else
      crt_trans_value = 255;
    if ((palette[k].red == gray_trans.gray) && (crt_trans_value != last_trans_value))
    {
      is_gray = 0;
      break;
    }
  }

  *crt_trans_value_ref = crt_trans_value;
  *last_trans_value_ref = last_trans_value;
  *gray_trans_ref = gray_trans;
  *is_gray_ref = is_gray;
  *k_ref = k;
}

void helper_helper_opng_analyze_bits_1_1(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions & 0x0004)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((component_ptr[0] != component_ptr[1]) || (component_ptr[0] != component_ptr[2]))
      {
        reductions &= ~0x0004;
        break;
      }
    }

  }
  if (reductions & 0x0008)
  {
    component_ptr = (*row_ptr) + offset_alpha;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if (component_ptr[0] != 255)
      {
        reductions &= ~0x0008;
        break;
      }
    }

  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}

void helper_helper_opng_analyze_bits_1_2(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions & 0x0004)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((((component_ptr[0] != component_ptr[2]) || (component_ptr[0] != component_ptr[4])) || (component_ptr[1] != component_ptr[3])) || (component_ptr[1] != component_ptr[5]))
      {
        reductions &= ~0x0004;
        break;
      }
    }

  }
  if (reductions & 0x0008)
  {
    component_ptr = (*row_ptr) + offset_alpha;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((component_ptr[0] != 255) || (component_ptr[1] != 255))
      {
        reductions &= ~0x0008;
        break;
      }
    }

  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}

void helper_helper_opng_reduce_palette_bits_2_1(png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, png_uint_32 * const j_ref, png_uint_32 width, int src_bit_depth, int dest_bit_depth, png_bytepp row_ptr, unsigned int src_mask_init)
{
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 j = *j_ref;
  src_sample_ptr = (dest_sample_ptr = *row_ptr);
  src_shift = (dest_shift = 8);
  src_mask = src_mask_init;
  dest_buf = 0;
  for (j = 0; j < width; j += 1)
  {
    helper_helper_helper_opng_reduce_palette_bits_2_1_1(&src_sample_ptr, &dest_sample_ptr, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, src_bit_depth, dest_bit_depth, src_mask_init);
  }

  if (dest_shift != 0)
  {
    *dest_sample_ptr = (png_byte) dest_buf;
  }
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
  *j_ref = j;
}

void helper_helper_opng_reduce_to_palette_1_1(png_bytep * const sample_ptr_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_uint_32 height, png_uint_32 width, int channels, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, int index)
{
  png_bytep sample_ptr = *sample_ptr_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  for (j = 0; j < width; j += 1, sample_ptr += channels)
  {
    helper_helper_helper_opng_reduce_to_palette_1_1_1(&red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, alpha_row, height, palette, trans_alpha, num_palette, num_trans, index, sample_ptr, j);
  }

  *sample_ptr_ref = sample_ptr;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
  *j_ref = j;
}

void helper_helper_opng_reduce_to_palette_2_1(png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const index_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_uint_32 width, int channels, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int index = *index_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  for (j = 0; j < width; j += 1, sample_ptr += channels)
  {
    helper_helper_helper_opng_reduce_to_palette_2_1_1(&row_ptr, &index, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, alpha_row, palette, trans_alpha, num_palette, num_trans, sample_ptr);
  }

  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *index_ref = index;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}

void helper_helper_helper_opng_reduce_palette_bits_2_1_1(png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, int src_bit_depth, int dest_bit_depth, unsigned int src_mask_init)
{
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  src_shift -= src_bit_depth;
  src_mask >>= src_bit_depth;
  sample = ((*src_sample_ptr) & src_mask) >> src_shift;
  dest_shift -= dest_bit_depth;
  if (dest_shift > 0)
  {
    dest_buf |= sample << dest_shift;
  }
  else
  {
    *dest_sample_ptr = (png_byte) (dest_buf | sample);
    dest_sample_ptr += 1;
    dest_shift = 8;
    dest_buf = 0;
  }
  if (src_shift == 0)
  {
    src_shift = 8;
    src_mask = src_mask_init;
    src_sample_ptr += 1;
  }
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
}

void helper_helper_helper_opng_reduce_to_palette_1_1_1(unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_bytep alpha_row, png_uint_32 height, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, int index, png_bytep sample_ptr, png_uint_32 j)
{
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  red = sample_ptr[0];
  green = sample_ptr[1];
  blue = sample_ptr[2];
  alpha = alpha_row[j];
  if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
  {
    prev_red = red;
    prev_green = green;
    prev_blue = blue;
    prev_alpha = alpha;
    if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) < 0)
    {
      assert(num_palette < 0);
      i = height;
      break;
    }
  }
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
}

void helper_helper_helper_opng_reduce_to_palette_2_1_1(png_bytepp * const row_ptr_ref, int * const index_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, png_bytep sample_ptr)
{
  png_bytepp row_ptr = *row_ptr_ref;
  int index = *index_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  red = sample_ptr[0];
  green = sample_ptr[1];
  blue = sample_ptr[2];
  alpha = alpha_row[j];
  if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
  {
    prev_red = red;
    prev_green = green;
    prev_blue = blue;
    prev_alpha = alpha;
    if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) != 0)
    {
      index = -1;
    }
  }
  assert(index >= 0);
  (*row_ptr)[j] = (png_byte) index;
  *row_ptr_ref = row_ptr;
  *index_ref = index;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}

