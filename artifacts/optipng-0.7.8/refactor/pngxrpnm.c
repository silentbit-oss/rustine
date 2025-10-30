#include <limits.h>
#include <png.h>
#include <pngconf.h>
#include <pnglibconf.h>
#include <pngxpriv.h>
#include <pngxrpnm.c>
#include <pngxtern.h>
#include <pngxutil.h>
#include <pnmio.h>
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
enum 
{
  PNM_P1 = 1,
  PNM_P2 = 2,
  PNM_P3 = 3,
  PNM_P4 = 4,
  PNM_P5 = 5,
  PNM_P6 = 6,
  PNM_P7 = 7
};
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct;
int pnm_fget_header(pnm_struct *pnm_ptr, FILE *stream);
int pnm_fget_values(const pnm_struct *pnm_ptr, unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fget_bytes(const pnm_struct *pnm_ptr, unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_fput_header(const pnm_struct *pnm_ptr, FILE *stream);
int pnm_fput_values(const pnm_struct *pnm_ptr, const unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fput_bytes(const pnm_struct *pnm_ptr, const unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_is_valid(const pnm_struct *pnm_ptr);
size_t pnm_raw_sample_size(const pnm_struct *pnm_ptr);
size_t pnm_mem_size(const pnm_struct *pnm_ptr, size_t sample_size, unsigned int num_rows);
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
static const char pbm_fmt_name[] = "PBM";
static const char pgm_fmt_name[] = "PGM";
static const char ppm_fmt_name[] = "PPM";
static const char pam_fmt_name[] = "PAM";
static const char pbm_fmt_long_name[] = "Portable Bitmap";
static const char pgm_fmt_long_name[] = "Portable Graymap";
static const char ppm_fmt_long_name[] = "Portable Pixmap";
static const char pam_fmt_long_name[] = "Portable Anymap";
int pngx_sig_is_pnm(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char *fmt_names[] = {pbm_fmt_name, pgm_fmt_name, ppm_fmt_name, pbm_fmt_name, pgm_fmt_name, ppm_fmt_name, pam_fmt_name};
  static const char *fmt_long_names[] = {pbm_fmt_long_name, pgm_fmt_long_name, ppm_fmt_long_name, pbm_fmt_long_name, pgm_fmt_long_name, ppm_fmt_long_name, pam_fmt_long_name};
  if (sig_size < 4)
  {
    return -1;
  }
  if (((sig[0] != 'P') || (sig[1] < '1')) || (sig[1] > '7'))
  {
    return 0;
  }
  if (((((sig[2] != ' ') && (sig[2] != '\t')) && (sig[2] != '\n')) && (sig[2] != '\r')) && (sig[2] != '#'))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = fmt_names[sig[1] - '1'];
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = fmt_long_names[sig[1] - '1'];
  }
  return 1;
}

static int pnm_fpeek_eof(pnm_struct *pnm_ptr, FILE *stream)
{
  int ch;
  if ((pnm_ptr->format >= PNM_P1) && (pnm_ptr->format <= PNM_P3))
  {
    do
    {
      ch = getc(stream);
      if (ch == '#')
      {
        do
        {
          ch = getc(stream);
        }
        while (((ch != EOF) && (ch != '\n')) && (ch != '\r'));
      }
      if (ch == EOF)
      {
        return 1;
      }
    }
    while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
  }
  else
  {
    ch = getc(stream);
    if (ch == EOF)
    {
      return 1;
    }
  }
  ungetc(ch, stream);
  return 0;
}

int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  pnm_struct pnminfo;
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
  unsigned int max_width;
  unsigned int num_samples;
  unsigned int sample_size;
  unsigned int *pnmrow;
  unsigned int pnmrow_idx = 0;
  size_t row_size;
  png_bytepp row_pointers;
  png_color_8 sig_bit;
  unsigned int i;
  unsigned int j;
  int failed;
  int overflow;
  if (pnm_fget_header(&pnminfo, stream) != 1)
  {
    return 0;
  }
  format = pnminfo.format;
  depth = pnminfo.depth;
  width = pnminfo.width;
  height = pnminfo.height;
  maxval = pnminfo.maxval;
  if (format > PNM_P6)
  {
    png_error(png_ptr, "Can't handle PNM formats newer than PPM (\"P6\")");
  }
  max_width = ((sizeof(size_t)) <= (sizeof(unsigned int))) ? ((4294967295U / (sizeof(unsigned int))) / depth) : (4294967295U);
  if (max_width > 0x7fffffffU)
  {
    max_width = 0x7fffffffU;
  }
  if (width > max_width)
  {
    png_error(png_ptr, "Can't handle exceedingly large PNM dimensions");
  }
  sample_size = 1;
  row_size = (num_samples = depth * width);
  if (maxval > 65535)
  {
    png_error(png_ptr, "Can't handle PNM samples larger than 16 bits");
  }
  else
    if (maxval > 255)
  {
    sample_size = 2;
    row_size *= 2;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, (maxval <= 255) ? (8) : (16), (depth == 1) ? (0) : (2), 0, 0, 0);
  for (i = 1, j = 2; (j - 1) < maxval; i += 1, j <<= 1)
  {
  }

  if ((j - 1) != maxval)
  {
    png_warning(png_ptr, "Possibly inexact sample conversion from PNM to PNG");
  }
  else
    if (((i % 8) != 0) && ((depth > 1) || ((8 % i) != 0)))
  {
    sig_bit.red = (sig_bit.green = (sig_bit.blue = (sig_bit.gray = (png_byte) i)));
    sig_bit.alpha = 0;
    png_set_sBIT(png_ptr, info_ptr, &sig_bit);
  }
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, -1);
  if ((format >= PNM_P4) && ((maxval == 255) || (maxval == 65535)))
  {
    pnmrow_idx = 0;
  }
  else
    pnmrow_idx = (unsigned int *) png_malloc(png_ptr, num_samples * (sizeof(unsigned int)));
  failed = 0;
  overflow = 0;
  if ((&pnmrow[pnmrow_idx]) != 0)
  {
    helper_pngx_read_pnm_1(&row_pointers, &i, &j, &failed, &overflow, stream, pnminfo, height, maxval, num_samples, pnmrow, pnmrow_idx);
  }
  else
  {
    for (i = 0; i < height; i += 1)
    {
      if (pnm_fget_bytes(&pnminfo, row_pointers[i], sample_size, 1, stream) <= 0)
      {
        failed = 1;
        break;
      }
    }

  }
  for (; i < height; i += 1)
  {
    memset(row_pointers[i], 0, row_size);
  }

  if ((&pnmrow[pnmrow_idx]) != 0)
  {
    png_free(png_ptr, pnmrow);
  }
  if (overflow)
  {
    png_warning(png_ptr, "Overflow in PNM samples");
  }
  if (failed)
  {
    png_error(png_ptr, "Error in PNM image file");
  }
  else
    if (!pnm_fpeek_eof(&pnminfo, stream))
  {
    png_warning(png_ptr, "Extraneous data found after PNM image");
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
enum 
{
  PNM_P1 = 1,
  PNM_P2 = 2,
  PNM_P3 = 3,
  PNM_P4 = 4,
  PNM_P5 = 5,
  PNM_P6 = 6,
  PNM_P7 = 7
};
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct;
int pnm_fget_header(pnm_struct *pnm_ptr, FILE *stream);
int pnm_fget_values(const pnm_struct *pnm_ptr, unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fget_bytes(const pnm_struct *pnm_ptr, unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_fput_header(const pnm_struct *pnm_ptr, FILE *stream);
int pnm_fput_values(const pnm_struct *pnm_ptr, const unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fput_bytes(const pnm_struct *pnm_ptr, const unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_is_valid(const pnm_struct *pnm_ptr);
size_t pnm_raw_sample_size(const pnm_struct *pnm_ptr);
size_t pnm_mem_size(const pnm_struct *pnm_ptr, size_t sample_size, unsigned int num_rows);
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
static const char pbm_fmt_name[] = "PBM";
static const char pgm_fmt_name[] = "PGM";
static const char ppm_fmt_name[] = "PPM";
static const char pam_fmt_name[] = "PAM";
static const char pbm_fmt_long_name[] = "Portable Bitmap";
static const char pgm_fmt_long_name[] = "Portable Graymap";
static const char ppm_fmt_long_name[] = "Portable Pixmap";
static const char pam_fmt_long_name[] = "Portable Anymap";
int pngx_sig_is_pnm(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char *fmt_names[] = {pbm_fmt_name, pgm_fmt_name, ppm_fmt_name, pbm_fmt_name, pgm_fmt_name, ppm_fmt_name, pam_fmt_name};
  static const char *fmt_long_names[] = {pbm_fmt_long_name, pgm_fmt_long_name, ppm_fmt_long_name, pbm_fmt_long_name, pgm_fmt_long_name, ppm_fmt_long_name, pam_fmt_long_name};
  if (sig_size < 4)
  {
    return -1;
  }
  if (((sig[0] != 'P') || (sig[1] < '1')) || (sig[1] > '7'))
  {
    return 0;
  }
  if (((((sig[2] != ' ') && (sig[2] != '\t')) && (sig[2] != '\n')) && (sig[2] != '\r')) && (sig[2] != '#'))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = fmt_names[sig[1] - '1'];
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = fmt_long_names[sig[1] - '1'];
  }
  return 1;
}

static int pnm_fpeek_eof(pnm_struct *pnm_ptr, FILE *stream)
{
  int ch;
  if ((pnm_ptr->format >= PNM_P1) && (pnm_ptr->format <= PNM_P3))
  {
    do
    {
      ch = getc(stream);
      if (ch == '#')
      {
        do
        {
          ch = getc(stream);
        }
        while (((ch != EOF) && (ch != '\n')) && (ch != '\r'));
      }
      if (ch == EOF)
      {
        return 1;
      }
    }
    while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
  }
  else
  {
    ch = getc(stream);
    if (ch == EOF)
    {
      return 1;
    }
  }
  ungetc(ch, stream);
  return 0;
}

int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  pnm_struct pnminfo;
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
  unsigned int max_width;
  unsigned int num_samples;
  unsigned int sample_size;
  unsigned int *pnmrow;
  unsigned int pnmrow_idx = 0;
  size_t row_size;
  png_bytepp row_pointers;
  png_color_8 sig_bit;
  unsigned int i;
  unsigned int j;
  int failed;
  int overflow;
  if (pnm_fget_header(&pnminfo, stream) != 1)
  {
    return 0;
  }
  format = pnminfo.format;
  depth = pnminfo.depth;
  width = pnminfo.width;
  height = pnminfo.height;
  maxval = pnminfo.maxval;
  if (format > PNM_P6)
  {
    png_error(png_ptr, "Can't handle PNM formats newer than PPM (\"P6\")");
  }
  max_width = ((sizeof(size_t)) <= (sizeof(unsigned int))) ? ((4294967295U / (sizeof(unsigned int))) / depth) : (4294967295U);
  if (max_width > 0x7fffffffU)
  {
    max_width = 0x7fffffffU;
  }
  if (width > max_width)
  {
    png_error(png_ptr, "Can't handle exceedingly large PNM dimensions");
  }
  sample_size = 1;
  row_size = (num_samples = depth * width);
  if (maxval > 65535)
  {
    png_error(png_ptr, "Can't handle PNM samples larger than 16 bits");
  }
  else
    if (maxval > 255)
  {
    sample_size = 2;
    row_size *= 2;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, (maxval <= 255) ? (8) : (16), (depth == 1) ? (0) : (2), 0, 0, 0);
  for (i = 1, j = 2; (j - 1) < maxval; i += 1, j <<= 1)
  {
  }

  if ((j - 1) != maxval)
  {
    png_warning(png_ptr, "Possibly inexact sample conversion from PNM to PNG");
  }
  else
    if (((i % 8) != 0) && ((depth > 1) || ((8 % i) != 0)))
  {
    sig_bit.red = (sig_bit.green = (sig_bit.blue = (sig_bit.gray = (png_byte) i)));
    sig_bit.alpha = 0;
    png_set_sBIT(png_ptr, info_ptr, &sig_bit);
  }
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, -1);
  if ((format >= PNM_P4) && ((maxval == 255) || (maxval == 65535)))
  {
    pnmrow_idx = 0;
  }
  else
    pnmrow_idx = (unsigned int *) png_malloc(png_ptr, num_samples * (sizeof(unsigned int)));
  failed = 0;
  overflow = 0;
  if ((&pnmrow[pnmrow_idx]) != 0)
  {
    for (i = 0; i < height; i += 1)
    {
      if (pnm_fget_values(&pnminfo, pnmrow, 1, stream) <= 0)
      {
        failed = 1;
      }
      if (maxval <= 255)
      {
        for (j = 0; j < num_samples; j += 1)
        {
          unsigned int val = pnmrow[j + pnmrow_idx];
          if (val > maxval)
          {
            val = 255;
            overflow = 1;
          }
          else
            if (maxval != 255)
          {
            val = ((val * 255) + (maxval / 2)) / maxval;
          }
          row_pointers[i][j] = (png_byte) val;
        }

      }
      else
      {
        for (j = 0; j < num_samples; j += 1)
        {
          png_uint_32 val = pnmrow[j + pnmrow_idx];
          if (val > maxval)
          {
            val = 65535;
            overflow = 1;
          }
          else
            if (maxval != 65535)
          {
            val = ((val * 65535) + (maxval / 2)) / maxval;
          }
          row_pointers[i][2 * j] = (png_byte) (val >> 8);
          row_pointers[i][(2 * j) + 1] = (png_byte) (val & 0xff);
        }

      }
      if (failed)
      {
        break;
      }
    }

  }
  else
  {
    for (i = 0; i < height; i += 1)
    {
      if (pnm_fget_bytes(&pnminfo, row_pointers[i], sample_size, 1, stream) <= 0)
      {
        failed = 1;
        break;
      }
    }

  }
  for (; i < height; i += 1)
  {
    memset(row_pointers[i], 0, row_size);
  }

  if ((&pnmrow[pnmrow_idx]) != 0)
  {
    png_free(png_ptr, pnmrow);
  }
  if (overflow)
  {
    png_warning(png_ptr, "Overflow in PNM samples");
  }
  if (failed)
  {
    png_error(png_ptr, "Error in PNM image file");
  }
  else
    if (!pnm_fpeek_eof(&pnminfo, stream))
  {
    png_warning(png_ptr, "Extraneous data found after PNM image");
  }
  return 1;
}

void helper_pngx_read_pnm_1(png_bytepp * const row_pointers_ref, unsigned int * const i_ref, unsigned int * const j_ref, int * const failed_ref, int * const overflow_ref, FILE * const stream, pnm_struct pnminfo, unsigned int height, unsigned int maxval, unsigned int num_samples, unsigned int * const pnmrow, unsigned int pnmrow_idx)
{
  png_bytepp row_pointers = *row_pointers_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  int failed = *failed_ref;
  int overflow = *overflow_ref;
  for (i = 0; i < height; i += 1)
  {
    helper_helper_pngx_read_pnm_1_1(&row_pointers, &i, &j, &failed, &overflow, stream, pnminfo, maxval, num_samples, pnmrow, pnmrow_idx);
  }

  *row_pointers_ref = row_pointers;
  *i_ref = i;
  *j_ref = j;
  *failed_ref = failed;
  *overflow_ref = overflow;
}

void helper_helper_pngx_read_pnm_1_1(png_bytepp * const row_pointers_ref, unsigned int * const i_ref, unsigned int * const j_ref, int * const failed_ref, int * const overflow_ref, FILE * const stream, pnm_struct pnminfo, unsigned int maxval, unsigned int num_samples, unsigned int * const pnmrow, unsigned int pnmrow_idx)
{
  png_bytepp row_pointers = *row_pointers_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  int failed = *failed_ref;
  int overflow = *overflow_ref;
  if (pnm_fget_values(&pnminfo, pnmrow, 1, stream) <= 0)
  {
    failed = 1;
  }
  if (maxval <= 255)
  {
    for (j = 0; j < num_samples; j += 1)
    {
      unsigned int val = pnmrow[j + pnmrow_idx];
      if (val > maxval)
      {
        val = 255;
        overflow = 1;
      }
      else
        if (maxval != 255)
      {
        val = ((val * 255) + (maxval / 2)) / maxval;
      }
      row_pointers[i][j] = (png_byte) val;
    }

  }
  else
  {
    for (j = 0; j < num_samples; j += 1)
    {
      png_uint_32 val = pnmrow[j + pnmrow_idx];
      if (val > maxval)
      {
        val = 65535;
        overflow = 1;
      }
      else
        if (maxval != 65535)
      {
        val = ((val * 65535) + (maxval / 2)) / maxval;
      }
      row_pointers[i][2 * j] = (png_byte) (val >> 8);
      row_pointers[i][(2 * j) + 1] = (png_byte) (val & 0xff);
    }

  }
  if (failed)
  {
    break;
  }
  *row_pointers_ref = row_pointers;
  *i_ref = i;
  *j_ref = j;
  *failed_ref = failed;
  *overflow_ref = overflow;
}

