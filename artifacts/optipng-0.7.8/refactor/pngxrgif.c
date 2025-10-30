#include <gifread.h>
#include <limits.h>
#include <png.h>
#include <pngconf.h>
#include <pnglibconf.h>
#include <pngxpriv.h>
#include <pngxrgif.c>
#include <pngxtern.h>
#include <pngxutil.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
struct GIFScreen
{
  unsigned int Width;
  unsigned int Height;
  unsigned int GlobalColorFlag;
  unsigned int ColorResolution;
  unsigned int SortFlag;
  unsigned int GlobalNumColors;
  unsigned int Background;
  unsigned int PixelAspectRatio;
  unsigned char GlobalColorTable[256 * 3];
};
struct GIFImage
{
  struct GIFScreen *Screen;
  unsigned int LeftPos;
  unsigned int TopPos;
  unsigned int Width;
  unsigned int Height;
  unsigned int LocalColorFlag;
  unsigned int InterlaceFlag;
  unsigned int SortFlag;
  unsigned int LocalNumColors;
  unsigned char LocalColorTable[256 * 3];
  unsigned char **Rows;
};
struct GIFExtension
{
  struct GIFScreen *Screen;
  unsigned char *Buffer;
  unsigned int BufferSize;
  unsigned char Label;
};
struct GIFGraphicCtlExt
{
  unsigned int DisposalMethod;
  unsigned int InputFlag;
  unsigned int TransparentFlag;
  unsigned int DelayTime;
  unsigned int Transparent;
};
void GIFReadScreen(struct GIFScreen *screen, FILE *stream);
void GIFInitImage(struct GIFImage *image, struct GIFScreen *screen, unsigned char **rows);
void GIFDestroyImage(struct GIFImage *image);
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext, FILE *stream);
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors, struct GIFImage *image);
void GIFInitExtension(struct GIFExtension *ext, struct GIFScreen *screen, unsigned int initBufferSize);
void GIFDestroyExtension(struct GIFExtension *ext);
void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt, struct GIFExtension *ext);
extern void (*GIFError)(const char *message);
extern void (*GIFWarning)(const char *message);
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
static const char gif_fmt_name[] = "GIF";
static const char gif_fmt_long_name[] = "Graphics Interchange Format";
static const png_byte gif_sig_gif87a[6] = {0x47, 0x49, 0x46, 0x38, 0x37, 0x61};
static const png_byte gif_sig_gif89a[6] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61};
int pngx_sig_is_gif(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  if (sig_size < (6 + 7))
  {
    return -1;
  }
  if ((memcmp(sig, gif_sig_gif87a, 6) != 0) && (memcmp(sig, gif_sig_gif89a, 6) != 0))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = gif_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = gif_fmt_long_name;
  }
  return 1;
}

static png_structp err_png_ptr;
static struct GIFImage *err_gif_image_ptr;
static struct GIFExtension *err_gif_ext_ptr;
static void pngx_gif_error(const char *msg)
{
  if (err_gif_image_ptr != 0)
  {
    GIFDestroyImage(err_gif_image_ptr);
  }
  if (err_gif_ext_ptr != 0)
  {
    GIFDestroyExtension(err_gif_ext_ptr);
  }
  png_error(err_png_ptr, msg);
}

static void pngx_gif_warning(const char *msg)
{
  png_warning(err_png_ptr, msg);
}

static void pngx_set_gif_palette(png_structp png_ptr, png_infop info_ptr, unsigned char *color_table, unsigned int num_colors)
{
  png_color palette[256];
  unsigned int i;
  (void) 0;
  (void) 0;
  for (i = 0; i < num_colors; i += 1)
  {
    palette[i].red = color_table[3 * i];
    palette[i].green = color_table[(3 * i) + 1];
    palette[i].blue = color_table[(3 * i) + 2];
  }

  png_set_PLTE(png_ptr, info_ptr, palette, (int) num_colors);
}

static void pngx_set_gif_transparent(png_structp png_ptr, png_infop info_ptr, unsigned int transparent)
{
  png_byte trans[256];
  unsigned int i;
  (void) 0;
  for (i = 0; i < transparent; i += 1)
  {
    trans[i] = 255;
  }

  trans[transparent] = 0;
  png_set_tRNS(png_ptr, info_ptr, trans, ((int) transparent) + 1, 0);
}

int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  struct GIFScreen screen;
  struct GIFImage image;
  struct GIFExtension ext;
  struct GIFGraphicCtlExt graphicExt;
  int blockCode;
  unsigned char *colorTable;
  unsigned int numColors;
  unsigned int transparent;
  unsigned int numImages;
  png_uint_32 width;
  png_uint_32 height;
  png_bytepp row_pointers;
  GIFError = pngx_gif_error;
  GIFWarning = pngx_gif_warning;
  err_png_ptr = png_ptr;
  err_gif_image_ptr = 0;
  err_gif_ext_ptr = 0;
  GIFReadScreen(&screen, stream);
  width = screen.Width;
  height = screen.Height;
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, 0, 0, 0);
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, (int) screen.Background);
  GIFInitImage(&image, &screen, row_pointers);
  err_gif_image_ptr = &image;
  GIFInitExtension(&ext, &screen, 256);
  err_gif_ext_ptr = &ext;
  numImages = 0;
  transparent = (unsigned int) (-1);
  for (;;)
  {
    helper_pngx_read_gif_1(&image, &blockCode, &transparent, &numImages, png_ptr, info_ptr, stream, ext, graphicExt, colorTable, numColors);
  }

  if (image.Rows != 0)
  {
    png_error(png_ptr, "No image in GIF file");
  }
  GIFDestroyImage(&image);
  GIFDestroyExtension(&ext);
  return numImages;
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
struct GIFScreen
{
  unsigned int Width;
  unsigned int Height;
  unsigned int GlobalColorFlag;
  unsigned int ColorResolution;
  unsigned int SortFlag;
  unsigned int GlobalNumColors;
  unsigned int Background;
  unsigned int PixelAspectRatio;
  unsigned char GlobalColorTable[256 * 3];
};
struct GIFImage
{
  struct GIFScreen *Screen;
  unsigned int LeftPos;
  unsigned int TopPos;
  unsigned int Width;
  unsigned int Height;
  unsigned int LocalColorFlag;
  unsigned int InterlaceFlag;
  unsigned int SortFlag;
  unsigned int LocalNumColors;
  unsigned char LocalColorTable[256 * 3];
  unsigned char **Rows;
};
struct GIFExtension
{
  struct GIFScreen *Screen;
  unsigned char *Buffer;
  unsigned int BufferSize;
  unsigned char Label;
};
struct GIFGraphicCtlExt
{
  unsigned int DisposalMethod;
  unsigned int InputFlag;
  unsigned int TransparentFlag;
  unsigned int DelayTime;
  unsigned int Transparent;
};
void GIFReadScreen(struct GIFScreen *screen, FILE *stream);
void GIFInitImage(struct GIFImage *image, struct GIFScreen *screen, unsigned char **rows);
void GIFDestroyImage(struct GIFImage *image);
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext, FILE *stream);
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors, struct GIFImage *image);
void GIFInitExtension(struct GIFExtension *ext, struct GIFScreen *screen, unsigned int initBufferSize);
void GIFDestroyExtension(struct GIFExtension *ext);
void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt, struct GIFExtension *ext);
extern void (*GIFError)(const char *message);
extern void (*GIFWarning)(const char *message);
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
static const char gif_fmt_name[] = "GIF";
static const char gif_fmt_long_name[] = "Graphics Interchange Format";
static const png_byte gif_sig_gif87a[6] = {0x47, 0x49, 0x46, 0x38, 0x37, 0x61};
static const png_byte gif_sig_gif89a[6] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61};
int pngx_sig_is_gif(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  if (sig_size < (6 + 7))
  {
    return -1;
  }
  if ((memcmp(sig, gif_sig_gif87a, 6) != 0) && (memcmp(sig, gif_sig_gif89a, 6) != 0))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = gif_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = gif_fmt_long_name;
  }
  return 1;
}

static png_structp err_png_ptr;
static struct GIFImage *err_gif_image_ptr;
static struct GIFExtension *err_gif_ext_ptr;
static void pngx_gif_error(const char *msg)
{
  if (err_gif_image_ptr != 0)
  {
    GIFDestroyImage(err_gif_image_ptr);
  }
  if (err_gif_ext_ptr != 0)
  {
    GIFDestroyExtension(err_gif_ext_ptr);
  }
  png_error(err_png_ptr, msg);
}

static void pngx_gif_warning(const char *msg)
{
  png_warning(err_png_ptr, msg);
}

static void pngx_set_gif_palette(png_structp png_ptr, png_infop info_ptr, unsigned char *color_table, unsigned int num_colors)
{
  png_color palette[256];
  unsigned int i;
  (void) 0;
  (void) 0;
  for (i = 0; i < num_colors; i += 1)
  {
    palette[i].red = color_table[3 * i];
    palette[i].green = color_table[(3 * i) + 1];
    palette[i].blue = color_table[(3 * i) + 2];
  }

  png_set_PLTE(png_ptr, info_ptr, palette, (int) num_colors);
}

static void pngx_set_gif_transparent(png_structp png_ptr, png_infop info_ptr, unsigned int transparent)
{
  png_byte trans[256];
  unsigned int i;
  (void) 0;
  for (i = 0; i < transparent; i += 1)
  {
    trans[i] = 255;
  }

  trans[transparent] = 0;
  png_set_tRNS(png_ptr, info_ptr, trans, ((int) transparent) + 1, 0);
}

int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  struct GIFScreen screen;
  struct GIFImage image;
  struct GIFExtension ext;
  struct GIFGraphicCtlExt graphicExt;
  int blockCode;
  unsigned char *colorTable;
  unsigned int numColors;
  unsigned int transparent;
  unsigned int numImages;
  png_uint_32 width;
  png_uint_32 height;
  png_bytepp row_pointers;
  GIFError = pngx_gif_error;
  GIFWarning = pngx_gif_warning;
  err_png_ptr = png_ptr;
  err_gif_image_ptr = 0;
  err_gif_ext_ptr = 0;
  GIFReadScreen(&screen, stream);
  width = screen.Width;
  height = screen.Height;
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, 0, 0, 0);
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, (int) screen.Background);
  GIFInitImage(&image, &screen, row_pointers);
  err_gif_image_ptr = &image;
  GIFInitExtension(&ext, &screen, 256);
  err_gif_ext_ptr = &ext;
  numImages = 0;
  transparent = (unsigned int) (-1);
  for (;;)
  {
    blockCode = GIFReadNextBlock(&image, &ext, stream);
    if (blockCode == 0x2c)
    {
      if (image.Rows != 0)
      {
        if (image.InterlaceFlag)
        {
          pngx_set_interlace_type(png_ptr, info_ptr, 1);
        }
        GIFGetColorTable(&colorTable, &numColors, &image);
        pngx_set_gif_palette(png_ptr, info_ptr, colorTable, numColors);
        if (transparent < 256)
        {
          pngx_set_gif_transparent(png_ptr, info_ptr, transparent);
        }
        image.Rows = 0;
      }
      numImages += 1;
    }
    else
      if (blockCode == 0x21)
    {
      if (ext.Label == 0xf9)
      {
        GIFGetGraphicCtl(&graphicExt, &ext);
        if ((image.Rows != 0) && graphicExt.TransparentFlag)
        {
          if (transparent >= 256)
          {
            transparent = graphicExt.Transparent;
          }
        }
      }
    }
    else
      if (blockCode == 0x3b)
    {
      break;
    }
  }

  if (image.Rows != 0)
  {
    png_error(png_ptr, "No image in GIF file");
  }
  GIFDestroyImage(&image);
  GIFDestroyExtension(&ext);
  return numImages;
}

void helper_pngx_read_gif_1(struct GIFImage * const image_ref, int * const blockCode_ref, unsigned int * const transparent_ref, unsigned int * const numImages_ref, png_structp png_ptr, png_infop info_ptr, FILE * const stream, struct GIFExtension ext, struct GIFGraphicCtlExt graphicExt, unsigned char * const colorTable, unsigned int numColors)
{
  struct GIFImage image = *image_ref;
  int blockCode = *blockCode_ref;
  unsigned int transparent = *transparent_ref;
  unsigned int numImages = *numImages_ref;
  blockCode = GIFReadNextBlock(&image, &ext, stream);
  if (blockCode == 0x2c)
  {
    if (image.Rows != 0)
    {
      if (image.InterlaceFlag)
      {
        pngx_set_interlace_type(png_ptr, info_ptr, 1);
      }
      GIFGetColorTable(&colorTable, &numColors, &image);
      pngx_set_gif_palette(png_ptr, info_ptr, colorTable, numColors);
      if (transparent < 256)
      {
        pngx_set_gif_transparent(png_ptr, info_ptr, transparent);
      }
      image.Rows = 0;
    }
    numImages += 1;
  }
  else
    if (blockCode == 0x21)
  {
    if (ext.Label == 0xf9)
    {
      GIFGetGraphicCtl(&graphicExt, &ext);
      if ((image.Rows != 0) && graphicExt.TransparentFlag)
      {
        if (transparent >= 256)
        {
          transparent = graphicExt.Transparent;
        }
      }
    }
  }
  else
    if (blockCode == 0x3b)
  {
    break;
  }
  *image_ref = image;
  *blockCode_ref = blockCode;
  *transparent_ref = transparent;
  *numImages_ref = numImages;
}

