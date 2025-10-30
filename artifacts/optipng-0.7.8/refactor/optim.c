#include <bitset.h>
#include <cexcept.h>
#include <ioutil.h>
#include <limits.h>
#include <opngreduc.h>
#include <optim.c>
#include <optipng.h>
#include <png.h>
#include <pngconf.h>
#include <pnglibconf.h>
#include <pngxtern.h>
#include <pngxutil.h>
#include <proginfo.h>
#include <ratio.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <unistd.h>
#include <zconf.h>
#include <zlib.h>

typedef unsigned int opng_bitset_t;
enum 
{
  OPNG_BITSET_ELT_MIN = 0,
  OPNG_BITSET_ELT_MAX = (int) (((sizeof(opng_bitset_t)) * 8) - 1)
};
unsigned int opng_bitset_count(opng_bitset_t set);
int opng_bitset_find_first(opng_bitset_t set);
int opng_bitset_find_next(opng_bitset_t set, int elt);
int opng_bitset_find_last(opng_bitset_t set);
int opng_bitset_find_prev(opng_bitset_t set, int elt);
int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set);
size_t opng_strformat_bitset_as_rangeset(char *out_buf, size_t out_buf_size, opng_bitset_t bitset);
struct opng_options
{
  int backup;
  int clobber;
  int debug;
  int fix;
  int force;
  int full;
  int preserve;
  int quiet;
  int simulate;
  int verbose;
  const char *out_name;
  const char *dir_name;
  const char *log_name;
  int interlace;
  int nb;
  int nc;
  int np;
  int nz;
  int optim_level;
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int window_bits;
  int snip;
  int strip_all;
};
struct opng_ui
{
  void (*printf_fn)(const char *fmt, ...);
  void (*print_cntrl_fn)(int cntrl_code);
  void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
  void (*panic_fn)(const char *msg);
};
int opng_initialize(const struct opng_options *options, const struct opng_ui *ui);
int opng_optimize(const char *infile_name);
int opng_finalize(void);
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
int pngx_read_image(png_structp png_ptr, png_infop info_ptr, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
void pngx_set_compression_type(png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type(png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type(png_structp png_ptr, png_infop info_ptr, int interlace_type);
typedef png_alloc_size_t pngx_alloc_size_t;
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended(png_structp png_ptr, png_infop info_ptr, pngx_alloc_size_t min_row_size, int filler);
typedef size_t z_size_t;
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;
typedef const void *voidpc;
typedef void *voidpf;
typedef void *voidp;
typedef unsigned z_crc_t;
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);
struct internal_state;
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
} z_stream;
typedef z_stream *z_streamp;
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
} gz_header;
typedef gz_header *gz_headerp;
extern const char *zlibVersion(void);
extern int deflate(z_streamp strm, int flush);
extern int deflateEnd(z_streamp strm);
extern int inflate(z_streamp strm, int flush);
extern int inflateEnd(z_streamp strm);
extern int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int deflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int deflateCopy(z_streamp dest, z_streamp source);
extern int deflateReset(z_streamp strm);
extern int deflateParams(z_streamp strm, int level, int strategy);
extern int deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain);
extern uLong deflateBound(z_streamp strm, uLong sourceLen);
extern int deflatePending(z_streamp strm, unsigned *pending, int *bits);
extern int deflatePrime(z_streamp strm, int bits, int value);
extern int deflateSetHeader(z_streamp strm, gz_headerp head);
extern int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int inflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int inflateSync(z_streamp strm);
extern int inflateCopy(z_streamp dest, z_streamp source);
extern int inflateReset(z_streamp strm);
extern int inflateReset2(z_streamp strm, int windowBits);
extern int inflatePrime(z_streamp strm, int bits, int value);
extern long inflateMark(z_streamp strm);
extern int inflateGetHeader(z_streamp strm, gz_headerp head);
typedef unsigned (*in_func)(void *, unsigned char **);
typedef int (*out_func)(void *, unsigned char *, unsigned);
extern int inflateBack(z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc);
extern int inflateBackEnd(z_streamp strm);
extern uLong zlibCompileFlags(void);
extern int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level);
extern uLong compressBound(uLong sourceLen);
extern int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int uncompress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen);
typedef struct gzFile_s *gzFile;
extern gzFile gzdopen(int fd, const char *mode);
extern int gzbuffer(gzFile file, unsigned size);
extern int gzsetparams(gzFile file, int level, int strategy);
extern int gzread(gzFile file, voidp buf, unsigned len);
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzwrite(gzFile file, voidpc buf, unsigned len);
extern z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzprintf(gzFile file, const char *format, ...);
extern int gzputs(gzFile file, const char *s);
extern char *gzgets(gzFile file, char *buf, int len);
extern int gzputc(gzFile file, int c);
extern int gzgetc(gzFile file);
extern int gzungetc(int c, gzFile file);
extern int gzflush(gzFile file, int flush);
extern int gzrewind(gzFile file);
extern int gzeof(gzFile file);
extern int gzdirect(gzFile file);
extern int gzclose(gzFile file);
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
extern const char *gzerror(gzFile file, int *errnum);
extern void gzclearerr(gzFile file);
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
extern uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len);
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
extern uLong crc32_z(uLong crc, const Bytef *buf, z_size_t len);
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
extern int deflateInit_(z_streamp strm, int level, const char *version, int stream_size);
extern int inflateInit_(z_streamp strm, const char *version, int stream_size);
extern int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size);
extern int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size);
extern int inflateBackInit_(z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size);
struct gzFile_s
{
  unsigned have;
  unsigned char *next;
  off_t pos;
};
extern int gzgetc_(gzFile file);
extern gzFile gzopen(const char *, const char *);
extern off_t gzseek(gzFile, off_t, int);
extern off_t gztell(gzFile);
extern off_t gzoffset(gzFile);
extern uLong adler32_combine(uLong, uLong, off_t);
extern uLong crc32_combine(uLong, uLong, off_t);
extern uLong crc32_combine_gen(off_t);
extern const char *zError(int);
extern int inflateSyncPoint(z_streamp);
extern const z_crc_t *get_crc_table(void);
extern int inflateUndermine(z_streamp, int);
extern int inflateValidate(z_streamp, int);
extern unsigned long inflateCodesUsed(z_streamp);
extern int inflateResetKeep(z_streamp);
extern int deflateResetKeep(z_streamp);
extern int gzvprintf(gzFile file, const char *format, va_list va);
typedef long opng_foffset_t;
typedef unsigned long opng_fsize_t;
opng_foffset_t opng_ftello(FILE *stream);
int opng_fseeko(FILE *stream, opng_foffset_t offset, int whence);
size_t opng_freado(FILE *stream, opng_foffset_t offset, int whence, void *block, size_t blocksize);
size_t opng_fwriteo(FILE *stream, opng_foffset_t offset, int whence, const void *block, size_t blocksize);
int opng_fgetsize(FILE *stream, opng_fsize_t *size);
char *opng_path_replace_dir(char *buffer, size_t bufsize, const char *old_path, const char *new_dirname);
char *opng_path_replace_ext(char *buffer, size_t bufsize, const char *old_path, const char *new_extname);
char *opng_path_make_backup(char *buffer, size_t bufsize, const char *path);
int opng_os_rename(const char *src_path, const char *dest_path, int clobber);
int opng_os_create_dir(const char *dirname);
int opng_os_copy_file_attr(const char *src_path, const char *dest_path);
int opng_os_test_file_access(const char *path, const char *mode);
int opng_os_test_file_equiv(const char *path1, const char *path2);
int opng_os_unlink(const char *path);
struct opng_lratio
{
  long num;
  long denom;
};
struct opng_ulratio
{
  unsigned long num;
  unsigned long denom;
};
int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
int opng_ulratio_to_percent_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t;
struct exception_context
{
  jmp_buf *penv;
  int caught;
  volatile struct 
  {
    opng_status_t etmp;
  } v;
};
struct exception_context the_exception_context[1];
static const struct opng_preset_struct
{
  const char *compr_level;
  const char *mem_level;
  const char *strategy;
  const char *filter;
} k_presets[7 + 1] = {{"", "", "", ""}, {"", "", "", ""}, {"9", "8", "0-", "0,5"}, {"9", "8-9", "0-", "0,5"}, {"9", "8", "0-", "0-"}, {"9", "8-9", "0-", "0-"}, {"1-9", "8", "0-", "0-"}, {"1-9", "8-9", "0-", "0-"}};
static const int k_filter_table[5 + 1] = {0x08, 0x10, 0x20, 0x40, 0x80, (((0x08 | 0x10) | 0x20) | 0x40) | 0x80};
static const png_byte k_sig_PLTE[4] = {0x50, 0x4c, 0x54, 0x45};
static const png_byte k_sig_tRNS[4] = {0x74, 0x52, 0x4e, 0x53};
static const png_byte k_sig_IDAT[4] = {0x49, 0x44, 0x41, 0x54};
static const png_byte k_sig_IEND[4] = {0x49, 0x45, 0x4e, 0x44};
static const png_byte k_sig_bKGD[4] = {0x62, 0x4b, 0x47, 0x44};
static const png_byte k_sig_hIST[4] = {0x68, 0x49, 0x53, 0x54};
static const png_byte k_sig_sBIT[4] = {0x73, 0x42, 0x49, 0x54};
static const png_byte k_sig_dSIG[4] = {0x64, 0x53, 0x49, 0x47};
static const png_byte k_sig_acTL[4] = {0x61, 0x63, 0x54, 0x4c};
static const png_byte k_sig_fcTL[4] = {0x66, 0x63, 0x54, 0x4c};
static const png_byte k_sig_fdAT[4] = {0x66, 0x64, 0x41, 0x54};
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL;
static const char *k_idat_size_max_string = "2GB";
enum 
{
  INPUT_IS_PNG_FILE = 0x0001,
  INPUT_HAS_PNG_DATASTREAM = 0x0002,
  INPUT_HAS_PNG_SIGNATURE = 0x0004,
  INPUT_HAS_DIGITAL_SIGNATURE = 0x0008,
  INPUT_HAS_MULTIPLE_IMAGES = 0x0010,
  INPUT_HAS_APNG = 0x0020,
  INPUT_HAS_STRIPPED_DATA = 0x0040,
  INPUT_HAS_JUNK = 0x0080,
  INPUT_HAS_ERRORS = 0x0100,
  OUTPUT_NEEDS_NEW_FILE = 0x1000,
  OUTPUT_NEEDS_NEW_IDAT = 0x2000,
  OUTPUT_HAS_ERRORS = 0x4000
};
static struct opng_engine_struct
{
  int started;
} s_engine;
static struct opng_process_struct
{
  unsigned int status;
  int num_iterations;
  opng_foffset_t in_datastream_offset;
  opng_fsize_t in_file_size;
  opng_fsize_t out_file_size;
  opng_fsize_t in_idat_size;
  opng_fsize_t out_idat_size;
  opng_fsize_t best_idat_size;
  opng_fsize_t max_idat_size;
  png_uint_32 in_plte_trns_size;
  png_uint_32 out_plte_trns_size;
  png_uint_32 reductions;
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int best_compr_level;
  int best_mem_level;
  int best_strategy;
  int best_filter;
} s_process;
static struct opng_summary_struct
{
  unsigned int file_count;
  unsigned int err_count;
  unsigned int fix_count;
  unsigned int snip_count;
} s_summary;
static struct opng_image_struct
{
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int interlace_type;
  png_bytepp row_pointers;
  png_colorp palette;
  int num_palette;
  png_color_16p background_ptr;
  png_color_16 background;
  png_uint_16p hist;
  png_color_8p sig_bit_ptr;
  png_color_8 sig_bit;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p trans_color_ptr;
  png_color_16 trans_color;
  png_unknown_chunkp unknowns;
  int num_unknowns;
} s_image;
static struct opng_options s_options;
static png_structp s_read_ptr;
static png_infop s_read_info_ptr;
static png_structp s_write_ptr;
static png_infop s_write_info_ptr;
static void (*usr_printf)(const char *fmt, ...);
static void (*usr_print_cntrl)(int cntrl_code);
static void (*usr_progress)(unsigned long num, unsigned long denom);
static void (*usr_panic)(const char *msg);
static void opng_print_fsize_ratio(opng_fsize_t num, opng_fsize_t denom)
{
  char buffer[32];
  struct opng_ulratio ratio;
  int result;
  ratio.num = num;
  ratio.denom = denom;
  result = opng_ulratio_to_factor_string(buffer, sizeof(buffer), &ratio);
  usr_printf("%s%s", buffer, (result > 0) ? ("") : ("..."));
}

static void opng_print_fsize_difference(opng_fsize_t init_size, opng_fsize_t final_size, int show_ratio)
{
  opng_fsize_t difference;
  int sign;
  if (init_size <= final_size)
  {
    sign = 0;
    difference = final_size - init_size;
  }
  else
  {
    sign = 1;
    difference = init_size - final_size;
  }
  if (difference == 0)
  {
    usr_printf("no change");
    return;
  }
  if (difference == 1)
  {
    usr_printf("1 byte");
  }
  else
    usr_printf("%lu bytes", difference);
  if (show_ratio && (init_size > 0))
  {
    usr_printf(" = ");
    opng_print_fsize_ratio(difference, init_size);
  }
  usr_printf((sign == 0) ? (" increase") : (" decrease"));
}

static void opng_print_image_info(int show_dim, int show_depth, int show_type, int show_interlaced)
{
  static const int type_channels[8] = {1, 0, 3, 1, 2, 0, 4, 0};
  int channels;
  int printed;
  printed = 0;
  if (show_dim)
  {
    printed = 1;
    usr_printf("%lux%lu pixels", (unsigned long) s_image.width, (unsigned long) s_image.height);
  }
  if (show_depth)
  {
    if (printed)
    {
      usr_printf(", ");
    }
    printed = 1;
    channels = type_channels[s_image.color_type & 7];
    if (channels != 1)
    {
      usr_printf("%dx%d bits/pixel", channels, s_image.bit_depth);
    }
    else
      if (s_image.bit_depth != 1)
    {
      usr_printf("%d bits/pixel", s_image.bit_depth);
    }
    else
      usr_printf("1 bit/pixel");
  }
  if (show_type)
  {
    helper_opng_print_image_info_1(&printed);
  }
  if (show_interlaced)
  {
    if (s_image.interlace_type != 0)
    {
      if (printed)
      {
        usr_printf(", ");
      }
      usr_printf("interlaced");
    }
  }
}

static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}

static void opng_print_error(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Error: %s\n", msg);
}

static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}

static void opng_warning(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
  }
  opng_print_warning(msg);
}

static void opng_error(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
    if (opng_validate_image(s_read_ptr, s_read_info_ptr))
    {
      opng_print_warning(msg);
      for (;; longjmp(*the_exception_context->penv, 1))
      {
        the_exception_context->v.etmp = OPNG_STATUS_OK;
      }

    }
  }
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_LIBPNG;
  }

}

static void opng_free(void *ptr)
{
  free(ptr);
}

static void opng_check_idat_size(opng_fsize_t size)
{
  if (size > k_idat_size_max)
  {
    opng_throw_error("IDAT sizes larger than the maximum chunk size are currently unsupported");
  }
}

static void opng_set_keep_unknown_chunk(png_structp png_ptr, int keep, png_bytep chunk_type)
{
  png_byte chunk_name[5];
  memcpy(chunk_name, chunk_type, 4);
  chunk_name[4] = 0;
  if (!png_handle_as_unknown(png_ptr, chunk_name))
  {
    png_set_keep_unknown_chunks(png_ptr, keep, chunk_name, 1);
  }
}

static int opng_is_image_chunk(png_bytep chunk_type)
{
  if ((chunk_type[0] & 0x20) == 0)
  {
    return 1;
  }
  if (memcmp(chunk_type, k_sig_tRNS, 4) == 0)
  {
    return 1;
  }
  return 0;
}

static int opng_is_apng_chunk(png_bytep chunk_type)
{
  if (((memcmp(chunk_type, k_sig_acTL, 4) == 0) || (memcmp(chunk_type, k_sig_fcTL, 4) == 0)) || (memcmp(chunk_type, k_sig_fdAT, 4) == 0))
  {
    return 1;
  }
  return 0;
}

static int opng_allow_chunk(png_bytep chunk_type)
{
  if (opng_is_image_chunk(chunk_type))
  {
    return 1;
  }
  if (s_options.strip_all)
  {
    return 0;
  }
  if (memcmp(chunk_type, k_sig_dSIG, 4) == 0)
  {
    return 0;
  }
  if (s_options.snip && opng_is_apng_chunk(chunk_type))
  {
    return 0;
  }
  return 1;
}

static void opng_handle_chunk(png_structp png_ptr, png_bytep chunk_type)
{
  int keep;
  if (opng_is_image_chunk(chunk_type))
  {
    return;
  }
  if (s_options.strip_all)
  {
    s_process.status |= INPUT_HAS_STRIPPED_DATA | INPUT_HAS_JUNK;
    opng_set_keep_unknown_chunk(png_ptr, 1, chunk_type);
    return;
  }
  if (((memcmp(chunk_type, k_sig_bKGD, 4) == 0) || (memcmp(chunk_type, k_sig_hIST, 4) == 0)) || (memcmp(chunk_type, k_sig_sBIT, 4) == 0))
  {
    return;
  }
  keep = 3;
  if (memcmp(chunk_type, k_sig_dSIG, 4) == 0)
  {
    s_process.status |= INPUT_HAS_DIGITAL_SIGNATURE;
  }
  else
    if (opng_is_apng_chunk(chunk_type))
  {
    s_process.status |= INPUT_HAS_APNG;
    if (memcmp(chunk_type, k_sig_fdAT, 4) == 0)
    {
      s_process.status |= INPUT_HAS_MULTIPLE_IMAGES;
    }
    if (s_options.snip)
    {
      s_process.status |= INPUT_HAS_JUNK;
      keep = 1;
    }
  }
  opng_set_keep_unknown_chunk(png_ptr, keep, chunk_type);
}

static void opng_init_read_data(void)
{
}

static void opng_init_write_data(void)
{
  s_process.out_file_size = 0;
  s_process.out_plte_trns_size = 0;
  s_process.out_idat_size = 0;
}

static void opng_read_data(png_structp png_ptr, png_bytep data, size_t length)
{
  FILE *stream = (FILE *) png_get_io_ptr(png_ptr);
  int io_state = png_get_io_state(png_ptr);
  int io_state_loc = io_state & 0x00f0;
  png_bytep chunk_sig;
  if (fread(data, 1, length, stream) != length)
  {
    png_error(png_ptr, "Can't read the input file or unexpected end of file");
  }
  if (s_process.in_file_size == 0)
  {
    helper_opng_read_data_1(png_ptr, length, stream, io_state_loc);
  }
  s_process.in_file_size += length;
  {
    if (!((io_state & 0x0001) && (io_state_loc != 0)))
    {
      usr_panic("Incorrect info in png_ptr->io_state");
    }
  }
  ;
  if (io_state_loc == 0x0020)
  {
    helper_opng_read_data_2(&chunk_sig, png_ptr, data, length);
  }
  else
    if (io_state_loc == 0x0080)
  {
    {
      if (!(length == 4))
      {
        usr_panic("Reading chunk CRC, expecting 4 bytes");
      }
    }
    ;
  }
}

static void opng_write_data(png_structp png_ptr, png_bytep data, size_t length)
{
  static int allow_crt_chunk;
  static int crt_chunk_is_idat;
  static opng_foffset_t crt_idat_offset;
  static opng_fsize_t crt_idat_size;
  static png_uint_32 crt_idat_crc;
  FILE *stream = (FILE *) png_get_io_ptr(png_ptr);
  int io_state = png_get_io_state(png_ptr);
  int io_state_loc = io_state & 0x00f0;
  png_bytep chunk_sig;
  png_byte buf[4];
  {
    if (!((io_state & 0x0002) && (io_state_loc != 0)))
    {
      usr_panic("Incorrect info in png_ptr->io_state");
    }
  }
  ;
  if (io_state_loc == 0x0020)
  {
    helper_opng_write_data_1(&allow_crt_chunk, &crt_chunk_is_idat, &chunk_sig, data, length, stream);
  }
  else
    if (io_state_loc == 0x0080)
  {
    {
      if (!(length == 4))
      {
        usr_panic("Writing chunk CRC, expecting 4 bytes");
      }
    }
    ;
  }
  if (stream == 0)
  {
    return;
  }
  if ((io_state_loc != 0x0010) && (!allow_crt_chunk))
  {
    return;
  }
  switch (io_state_loc)
  {
    case 0x0020:
    {
      helper_opng_write_data_2(&crt_idat_offset, &crt_idat_size, &crt_idat_crc, &io_state, png_ptr, data, length, crt_chunk_is_idat, stream, buf);
    }

    case 0x0040:
    {
      if (crt_chunk_is_idat)
      {
        crt_idat_crc = crc32(crt_idat_crc, data, length);
      }
      break;
    }

    case 0x0080:
    {
      if (crt_chunk_is_idat)
      {
        return;
      }
      break;
    }

  }

  if (fwrite(data, 1, length, stream) != length)
  {
    png_error(png_ptr, "Can't write the output file");
  }
  s_process.out_file_size += length;
}

static void opng_clear_image_info(void)
{
  memset(&s_image, 0, sizeof(s_image));
}

static void opng_load_image_info(png_structp png_ptr, png_infop info_ptr, int load_meta)
{
  memset(&s_image, 0, sizeof(s_image));
  png_get_IHDR(png_ptr, info_ptr, &s_image.width, &s_image.height, &s_image.bit_depth, &s_image.color_type, &s_image.interlace_type, &s_image.compression_type, &s_image.filter_type);
  s_image.row_pointers = png_get_rows(png_ptr, info_ptr);
  png_get_PLTE(png_ptr, info_ptr, &s_image.palette, &s_image.num_palette);
  if (png_get_tRNS(png_ptr, info_ptr, &s_image.trans_alpha, &s_image.num_trans, &s_image.trans_color_ptr))
  {
    if (s_image.trans_color_ptr != 0)
    {
      s_image.trans_color = *s_image.trans_color_ptr;
      s_image.trans_color_ptr = &s_image.trans_color;
    }
  }
  if (!load_meta)
  {
    return;
  }
  if (png_get_bKGD(png_ptr, info_ptr, &s_image.background_ptr))
  {
    s_image.background = *s_image.background_ptr;
    s_image.background_ptr = &s_image.background;
  }
  png_get_hIST(png_ptr, info_ptr, &s_image.hist);
  if (png_get_sBIT(png_ptr, info_ptr, &s_image.sig_bit_ptr))
  {
    s_image.sig_bit = *s_image.sig_bit_ptr;
    s_image.sig_bit_ptr = &s_image.sig_bit;
  }
  s_image.num_unknowns = png_get_unknown_chunks(png_ptr, info_ptr, &s_image.unknowns);
}

static void opng_store_image_info(png_structp png_ptr, png_infop info_ptr, int store_meta)
{
  int i;
  {
    if (!(s_image.row_pointers != 0))
    {
      usr_panic("No info in image");
    }
  }
  ;
  png_set_IHDR(png_ptr, info_ptr, s_image.width, s_image.height, s_image.bit_depth, s_image.color_type, s_image.interlace_type, s_image.compression_type, s_image.filter_type);
  png_set_rows(s_write_ptr, s_write_info_ptr, s_image.row_pointers);
  if (s_image.palette != 0)
  {
    png_set_PLTE(png_ptr, info_ptr, s_image.palette, s_image.num_palette);
  }
  if ((s_image.trans_alpha != 0) || (s_image.trans_color_ptr != 0))
  {
    png_set_tRNS(png_ptr, info_ptr, s_image.trans_alpha, s_image.num_trans, s_image.trans_color_ptr);
  }
  if (!store_meta)
  {
    return;
  }
  if (s_image.background_ptr != 0)
  {
    png_set_bKGD(png_ptr, info_ptr, s_image.background_ptr);
  }
  if (s_image.hist != 0)
  {
    png_set_hIST(png_ptr, info_ptr, s_image.hist);
  }
  if (s_image.sig_bit_ptr != 0)
  {
    png_set_sBIT(png_ptr, info_ptr, s_image.sig_bit_ptr);
  }
  if (s_image.num_unknowns != 0)
  {
    png_set_unknown_chunks(png_ptr, info_ptr, s_image.unknowns, s_image.num_unknowns);
    for (i = 0; i < s_image.num_unknowns; i += 1)
    {
      png_set_unknown_chunk_location(png_ptr, info_ptr, i, s_image.unknowns[i].location);
    }

  }
}

static void opng_destroy_image_info(void)
{
  png_uint_32 i;
  int j;
  if (s_image.row_pointers == 0)
  {
    return;
  }
  for (i = 0; i < s_image.height; i += 1)
  {
    opng_free(s_image.row_pointers[i]);
  }

  opng_free(s_image.row_pointers);
  opng_free(s_image.palette);
  opng_free(s_image.trans_alpha);
  opng_free(s_image.hist);
  for (j = 0; j < s_image.num_unknowns; j += 1)
  {
    opng_free(s_image.unknowns[j].data);
  }

  opng_free(s_image.unknowns);
  memset(&s_image, 0, sizeof(s_image));
}

static void opng_read_file(FILE *infile)
{
  const char *fmt_name;
  unsigned int fmt_name_idx = 0;
  int num_img;
  png_uint_32 reductions;
  volatile opng_status_t status;
  status = OPNG_STATUS_OK;
  {
    helper_opng_read_file_1(&fmt_name_idx, &num_img, infile, fmt_name);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    if (opng_validate_image(s_read_ptr, s_read_info_ptr))
    {
      if (!(status == OPNG_STATUS_OK))
      {
        usr_panic("Mysterious error in validated image file");
      }
    }
    ;
  }
  {
    helper_opng_read_file_2(&reductions, &status, fmt_name);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    png_data_freer(s_read_ptr, s_read_info_ptr, 1, 0xffffU);
    png_destroy_read_struct(&s_read_ptr, &s_read_info_ptr, 0);
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  png_data_freer(s_read_ptr, s_read_info_ptr, 2, 0xffffU);
  png_destroy_read_struct(&s_read_ptr, &s_read_info_ptr, 0);
}

static void opng_write_file(FILE *outfile, int compression_level, int memory_level, int compression_strategy, int filter)
{
  volatile opng_status_t status;
  {
    if (!((((((((compression_level >= 1) && (compression_level <= 9)) && (memory_level >= 1)) && (memory_level <= 9)) && (compression_strategy >= 0)) && (compression_strategy <= 3)) && (filter >= 0)) && (filter <= 5)))
    {
      usr_panic("Invalid encoding parameters");
    }
  }
  ;
  status = OPNG_STATUS_OK;
  {
    helper_opng_write_file_1(outfile, compression_level, memory_level, compression_strategy, filter);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    s_process.out_idat_size = k_idat_size_max + 1;
  }
  png_destroy_write_struct(&s_write_ptr, &s_write_info_ptr);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
}

static void opng_copy_file(FILE *infile, FILE *outfile)
{
  volatile png_bytep buf;
  const png_uint_32 buf_size_incr = 0x1000;
  png_uint_32 buf_size;
  png_uint_32 length;
  png_byte chunk_hdr[8];
  volatile opng_status_t status;
  s_write_ptr = png_create_write_struct("1.6.40", 0, opng_error, opng_warning);
  if (s_write_ptr == 0)
  {
    opng_throw_error("Can't create image encoder");
  }
  opng_init_write_data();
  png_set_write_fn(s_write_ptr, outfile, opng_write_data, 0);
  status = OPNG_STATUS_OK;
  {
    helper_opng_copy_file_1(&buf, &buf_size, &length, infile, buf_size_incr, chunk_hdr);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
  }
  png_free(s_write_ptr, buf);
  png_destroy_write_struct(&s_write_ptr, 0);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
}

static void opng_init_iteration(opng_bitset_t cmdline_set, opng_bitset_t mask_set, const char *preset, opng_bitset_t *output_set)
{
  opng_bitset_t preset_set;
  int check;
  *output_set = cmdline_set & mask_set;
  if (((*output_set) == 0) && (cmdline_set != 0))
  {
    opng_throw_error("Iteration parameter(s) out of range");
  }
  if ((s_options.optim_level >= 0) || ((*output_set) == 0))
  {
    check = opng_strparse_rangeset_to_bitset(&preset_set, preset, mask_set);
    {
      if (!(check == 0))
      {
        usr_panic("[internal] Invalid preset");
      }
    }
    ;
    *output_set |= preset_set & mask_set;
  }
}

static void opng_init_iterations(void)
{
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  opng_bitset_t strategy_singles_set;
  int preset_index;
  int t1;
  int t2;
  if (s_options.full || (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
  {
    s_process.max_idat_size = k_idat_size_max;
  }
  else
  {
    {
      if (!(s_process.in_idat_size > 0))
      {
        usr_panic("No IDAT in input");
      }
    }
    ;
    s_process.max_idat_size = s_process.in_idat_size + s_process.in_plte_trns_size;
  }
  preset_index = s_options.optim_level;
  if (preset_index < 0)
  {
    preset_index = 2;
  }
  else
    if (preset_index > 7)
  {
    preset_index = 7;
  }
  opng_init_iteration(s_options.compr_level_set, (1 << (9 + 1)) - (1 << 1), k_presets[preset_index].compr_level, &compr_level_set);
  opng_init_iteration(s_options.mem_level_set, (1 << (9 + 1)) - (1 << 1), k_presets[preset_index].mem_level, &mem_level_set);
  opng_init_iteration(s_options.strategy_set, (1 << (3 + 1)) - (1 << 0), k_presets[preset_index].strategy, &strategy_set);
  opng_init_iteration(s_options.filter_set, (1 << (5 + 1)) - (1 << 0), k_presets[preset_index].filter, &filter_set);
  if (compr_level_set == 0)
  {
    compr_level_set |= 1U << 9;
  }
  if (mem_level_set == 0)
  {
    mem_level_set |= 1U << 8;
  }
  if ((s_image.bit_depth < 8) || (s_image.palette != 0))
  {
    if (strategy_set == 0)
    {
      strategy_set |= 1U << 0;
    }
    if (filter_set == 0)
    {
      filter_set |= 1U << 0;
    }
  }
  else
  {
    if (strategy_set == 0)
    {
      strategy_set |= 1U << 1;
    }
    if (filter_set == 0)
    {
      filter_set |= 1U << 5;
    }
  }
  s_process.compr_level_set = compr_level_set;
  s_process.mem_level_set = mem_level_set;
  s_process.strategy_set = strategy_set;
  s_process.filter_set = filter_set;
  strategy_singles_set = (1 << 2) | (1 << 3);
  t1 = opng_bitset_count(compr_level_set) * opng_bitset_count(strategy_set & (~strategy_singles_set));
  t2 = opng_bitset_count(strategy_set & strategy_singles_set);
  s_process.num_iterations = ((t1 + t2) * opng_bitset_count(mem_level_set)) * opng_bitset_count(filter_set);
  {
    if (!(s_process.num_iterations > 0))
    {
      usr_panic("Invalid iteration parameters");
    }
  }
  ;
}

static void opng_iterate(void)
{
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int compr_level;
  int mem_level;
  int strategy;
  int filter;
  int counter;
  int line_reused;
  {
    if (!(s_process.num_iterations > 0))
    {
      usr_panic("Iterations not initialized");
    }
  }
  ;
  compr_level_set = s_process.compr_level_set;
  mem_level_set = s_process.mem_level_set;
  strategy_set = s_process.strategy_set;
  filter_set = s_process.filter_set;
  if ((s_process.num_iterations == 1) && (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
  {
    s_process.best_idat_size = 0;
    s_process.best_compr_level = opng_bitset_find_first(compr_level_set);
    s_process.best_mem_level = opng_bitset_find_first(mem_level_set);
    s_process.best_strategy = opng_bitset_find_first(strategy_set);
    s_process.best_filter = opng_bitset_find_first(filter_set);
    return;
  }
  s_process.best_idat_size = k_idat_size_max + 1;
  s_process.best_compr_level = -1;
  s_process.best_mem_level = -1;
  s_process.best_strategy = -1;
  s_process.best_filter = -1;
  usr_printf("\nTrying:\n");
  line_reused = 0;
  counter = 0;
  for (filter = 0; filter <= 5; filter += 1)
  {
    helper_opng_iterate_1(&compr_level_set, &compr_level, &mem_level, &strategy, &counter, &line_reused, mem_level_set, strategy_set, filter_set, filter);
  }

  if (line_reused)
  {
    usr_print_cntrl(-31);
  }
  {
    if (!(counter == s_process.num_iterations))
    {
      usr_panic("Inconsistent iteration counter");
    }
  }
  ;
  usr_progress(counter, s_process.num_iterations);
}

static void opng_finish_iterations(void)
{
  if ((s_process.best_idat_size + s_process.out_plte_trns_size) < (s_process.in_idat_size + s_process.in_plte_trns_size))
  {
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  }
  if (s_process.status & OUTPUT_NEEDS_NEW_IDAT)
  {
    if (s_process.best_idat_size <= k_idat_size_max)
    {
      usr_printf("\nSelecting parameters:\n");
      usr_printf("  zc = %d  zm = %d  zs = %d  f = %d", s_process.best_compr_level, s_process.best_mem_level, s_process.best_strategy, s_process.best_filter);
      if (s_process.best_idat_size > 0)
      {
        usr_printf("\t\tIDAT size = %lu", s_process.best_idat_size);
      }
      usr_printf("\n");
    }
    else
    {
      usr_printf("  zc = *  zm = *  zs = *  f = *\t\tIDAT size > %s\n", k_idat_size_max_string);
    }
  }
}

static void opng_optimize_impl(const char *infile_name)
{
  static FILE *infile;
  unsigned int infile_idx = 0;
  static FILE *outfile;
  unsigned int outfile_idx = 0;
  static const char *infile_name_local;
  unsigned int infile_name_local_idx = 0;
  static const char *outfile_name;
  unsigned int outfile_name_idx = 0;
  static const char *bakfile_name;
  unsigned int bakfile_name_idx = 0;
  static int new_outfile;
  static int has_backup;
  char name_buf[1024];
  char tmp_buf[1024];
  volatile opng_status_t status;
  memset(&s_process, 0, sizeof(s_process));
  if (s_options.force)
  {
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  }
  infile_name_local_idx = infile_name;
  if ((infile_idx = fopen(infile_name_local, "rb")) == 0)
  {
    opng_throw_error("Can't open the input file");
  }
  status = OPNG_STATUS_OK;
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        opng_read_file(infile);
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    {
      if (!(status != OPNG_STATUS_OK))
      {
        usr_panic("opng_read_file should throw errors only");
      }
    }
    ;
  }
  fclose(infile);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  if (s_process.status & INPUT_HAS_ERRORS)
  {
    usr_printf("Recoverable errors found in input.");
    if (s_options.fix)
    {
      usr_printf(" Fixing...\n");
      s_process.status |= OUTPUT_NEEDS_NEW_FILE;
    }
    else
    {
      usr_printf(" Rerun OptiPNG with -fix enabled.\n");
      opng_throw_error("Previous error(s) not fixed");
    }
  }
  if (s_process.status & INPUT_HAS_JUNK)
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
  }
  if (!(s_process.status & INPUT_HAS_PNG_SIGNATURE))
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
  }
  if (s_process.status & INPUT_HAS_PNG_DATASTREAM)
  {
    if (s_options.nz && (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
    {
      usr_printf("IDAT recoding is necessary, but is disabled by the user.\n");
      opng_throw_error("Can't continue");
    }
  }
  else
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  if (s_process.status & INPUT_HAS_DIGITAL_SIGNATURE)
  {
    usr_printf("Digital signature found in input.");
    if (s_options.force)
    {
      usr_printf(" Erasing...\n");
      s_process.status |= OUTPUT_NEEDS_NEW_FILE;
    }
    else
    {
      usr_printf(" Rerun OptiPNG with -force enabled.\n");
      opng_throw_error("Can't optimize digitally-signed files");
    }
  }
  if (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)
  {
    if ((!s_options.snip) && (!(s_process.status & INPUT_IS_PNG_FILE)))
    {
      usr_printf("Conversion to PNG requires snipping. Rerun OptiPNG with -snip enabled.\n");
      opng_throw_error("Incompatible input format");
    }
  }
  if (s_options.snip && (s_process.status & INPUT_HAS_APNG))
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
  }
  if (s_process.status & INPUT_HAS_STRIPPED_DATA)
  {
    usr_printf("Stripping metadata...\n");
  }
  outfile_name_idx = 0;
  if (!(s_process.status & INPUT_IS_PNG_FILE))
  {
    if (opng_path_replace_ext(name_buf, sizeof(name_buf), infile_name_local, ".png") == 0)
    {
      opng_throw_error("Can't create the output file (name too long)");
    }
    outfile_name_idx = name_buf;
  }
  if (s_options.out_name != 0)
  {
    outfile_name_idx = s_options.out_name;
  }
  if (s_options.dir_name != 0)
  {
    const char *tmp_name;
    unsigned int tmp_name_idx = 0;
    if ((&outfile_name[outfile_name_idx]) != 0)
    {
      strcpy(tmp_buf, outfile_name);
      tmp_name_idx = tmp_buf;
    }
    else
      tmp_name_idx = &infile_name_local[infile_name_local_idx];
    if (opng_path_replace_dir(name_buf, sizeof(name_buf), tmp_name, s_options.dir_name) == 0)
    {
      opng_throw_error("Can't create the output file (name too long)");
    }
    outfile_name_idx = name_buf;
  }
  if ((&outfile_name[outfile_name_idx]) == 0)
  {
    outfile_name_idx = &infile_name_local[infile_name_local_idx];
    new_outfile = 0;
  }
  else
  {
    int test_eq = opng_os_test_file_equiv(infile_name_local, outfile_name);
    if (test_eq >= 0)
    {
      new_outfile = test_eq == 0;
    }
    else
    {
      new_outfile = strcmp(infile_name_local, outfile_name) != 0;
    }
  }
  bakfile_name_idx = tmp_buf;
  if (new_outfile)
  {
    if (opng_path_make_backup(tmp_buf, sizeof(tmp_buf), outfile_name) == 0)
    {
      bakfile_name_idx = 0;
    }
  }
  else
  {
    if (opng_path_make_backup(tmp_buf, sizeof(tmp_buf), infile_name_local) == 0)
    {
      bakfile_name_idx = 0;
    }
  }
  if ((&bakfile_name[bakfile_name_idx]) == 0)
  {
    opng_throw_error("Can't create backup file (name too long)");
  }
  if ((!s_options.simulate) && (opng_os_test_file_access(outfile_name, "e") == 0))
  {
    if (((!s_options.backup) && (!s_options.clobber)) && new_outfile)
    {
      usr_printf("The output file exists. Rerun OptiPNG with -backup enabled.\n");
      opng_throw_error("Can't overwrite the output file");
    }
    if ((opng_os_test_file_access(outfile_name, "fw") != 0) || ((!s_options.clobber) && (opng_os_test_file_access(bakfile_name, "e") == 0)))
    {
      usr_printf("A backup file already exists. Rerun OptiPNG with -clobber enabled.\n");
      opng_throw_error("Can't back up the existing output file");
    }
  }
  if (s_process.status & INPUT_HAS_PNG_DATASTREAM)
  {
    usr_printf("Input IDAT size = %lu bytes\n", s_process.in_idat_size);
  }
  usr_printf("Input file size = %lu bytes\n", s_process.in_file_size);
  if ((!s_options.nz) || (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
  {
    opng_init_iterations();
    opng_iterate();
    opng_finish_iterations();
  }
  if (s_process.status & OUTPUT_NEEDS_NEW_IDAT)
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
    opng_check_idat_size(s_process.best_idat_size);
  }
  if (!(s_process.status & OUTPUT_NEEDS_NEW_FILE))
  {
    usr_printf("\n%s is already optimized.\n", infile_name_local);
    if (!new_outfile)
    {
      return;
    }
  }
  if (s_options.simulate)
  {
    usr_printf("\nNo output: simulation mode.\n");
    return;
  }
  if (new_outfile)
  {
    usr_printf("\nOutput file: %s\n", outfile_name);
    if (s_options.dir_name != 0)
    {
      opng_os_create_dir(s_options.dir_name);
    }
    has_backup = 0;
    if (opng_os_test_file_access(outfile_name, "e") == 0)
    {
      if (opng_os_rename(outfile_name, bakfile_name, s_options.clobber) != 0)
      {
        opng_throw_error("Can't back up the output file");
      }
      has_backup = 1;
    }
  }
  else
  {
    if (opng_os_rename(infile_name_local, bakfile_name, s_options.clobber) != 0)
    {
      opng_throw_error("Can't back up the input file");
    }
    has_backup = 1;
  }
  outfile_idx = fopen(outfile_name, "wb");
  {
    helper_opng_optimize_impl_2(&infile_idx, &status, infile, outfile, outfile_idx, infile_name_local, bakfile_name, new_outfile);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    helper_opng_optimize_impl_1(outfile, outfile_idx, infile_name_local, outfile_name, bakfile_name, new_outfile, has_backup, status);
  }
  fclose(outfile);
  if (s_options.preserve)
  {
    opng_os_copy_file_attr((new_outfile) ? (infile_name_local) : (bakfile_name), outfile_name);
  }
  if ((!s_options.backup) && (!new_outfile))
  {
    if (opng_os_unlink(bakfile_name) != 0)
    {
      opng_print_warning("Can't remove the backup file");
    }
  }
  usr_printf("\nOutput IDAT size = %lu bytes", s_process.out_idat_size);
  if (s_process.status & INPUT_HAS_PNG_DATASTREAM)
  {
    usr_printf(" (");
    opng_print_fsize_difference(s_process.in_idat_size, s_process.out_idat_size, 0);
    usr_printf(")");
  }
  usr_printf("\nOutput file size = %lu bytes (", s_process.out_file_size);
  opng_print_fsize_difference(s_process.in_file_size, s_process.out_file_size, 1);
  usr_printf(")\n");
}

int opng_initialize(const struct opng_options *init_options, const struct opng_ui *init_ui)
{
  usr_printf = init_ui->printf_fn;
  usr_print_cntrl = init_ui->print_cntrl_fn;
  usr_progress = init_ui->progress_fn;
  usr_panic = init_ui->panic_fn;
  if ((((usr_printf == 0) || (usr_print_cntrl == 0)) || (usr_progress == 0)) || (usr_panic == 0))
  {
    return -1;
  }
  s_options = *init_options;
  if (s_options.optim_level == 0)
  {
    s_options.nb = (s_options.nc = (s_options.np = 1));
    s_options.nz = 1;
  }
  memset(&s_summary, 0, sizeof(s_summary));
  s_engine.started = 1;
  return 0;
}

int opng_optimize(const char *infile_name)
{
  opng_status_t status;
  volatile int result;
  {
    if (!s_engine.started)
    {
      usr_panic("The OptiPNG engine is not running");
    }
  }
  ;
  usr_printf("** Processing: %s\n", infile_name);
  s_summary.file_count += 1;
  opng_clear_image_info();
  {
    helper_opng_optimize_1(&result, infile_name);
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    {
      if (!(status != OPNG_STATUS_OK))
      {
        usr_panic("opng_optimize_impl should throw errors only");
      }
    }
    ;
    s_summary.err_count += 1;
    result = -1;
  }
  opng_destroy_image_info();
  usr_printf("\n");
  return result;
}

int opng_finalize(void)
{
  if ((s_options.verbose || (s_summary.snip_count > 0)) || (s_summary.err_count > 0))
  {
    usr_printf("** Status report\n");
    usr_printf("%u file(s) have been processed.\n", s_summary.file_count);
    if (s_summary.snip_count > 0)
    {
      usr_printf("%u multi-image file(s) have been snipped.\n", s_summary.snip_count);
    }
    if (s_summary.err_count > 0)
    {
      usr_printf("%u error(s) have been encountered.\n", s_summary.err_count);
      if (s_summary.fix_count > 0)
      {
        usr_printf("%u erroneous file(s) have been fixed.\n", s_summary.fix_count);
      }
    }
  }
  s_engine.started = 0;
  return 0;
}


typedef unsigned int opng_bitset_t;
enum 
{
  OPNG_BITSET_ELT_MIN = 0,
  OPNG_BITSET_ELT_MAX = (int) (((sizeof(opng_bitset_t)) * 8) - 1)
};
unsigned int opng_bitset_count(opng_bitset_t set);
int opng_bitset_find_first(opng_bitset_t set);
int opng_bitset_find_next(opng_bitset_t set, int elt);
int opng_bitset_find_last(opng_bitset_t set);
int opng_bitset_find_prev(opng_bitset_t set, int elt);
int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set);
size_t opng_strformat_bitset_as_rangeset(char *out_buf, size_t out_buf_size, opng_bitset_t bitset);
struct opng_options
{
  int backup;
  int clobber;
  int debug;
  int fix;
  int force;
  int full;
  int preserve;
  int quiet;
  int simulate;
  int verbose;
  const char *out_name;
  const char *dir_name;
  const char *log_name;
  int interlace;
  int nb;
  int nc;
  int np;
  int nz;
  int optim_level;
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int window_bits;
  int snip;
  int strip_all;
};
struct opng_ui
{
  void (*printf_fn)(const char *fmt, ...);
  void (*print_cntrl_fn)(int cntrl_code);
  void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
  void (*panic_fn)(const char *msg);
};
int opng_initialize(const struct opng_options *options, const struct opng_ui *ui);
int opng_optimize(const char *infile_name);
int opng_finalize(void);
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
int pngx_read_image(png_structp png_ptr, png_infop info_ptr, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr);
void pngx_set_compression_type(png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type(png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type(png_structp png_ptr, png_infop info_ptr, int interlace_type);
typedef png_alloc_size_t pngx_alloc_size_t;
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended(png_structp png_ptr, png_infop info_ptr, pngx_alloc_size_t min_row_size, int filler);
typedef size_t z_size_t;
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;
typedef const void *voidpc;
typedef void *voidpf;
typedef void *voidp;
typedef unsigned z_crc_t;
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);
struct internal_state;
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
} z_stream;
typedef z_stream *z_streamp;
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
} gz_header;
typedef gz_header *gz_headerp;
extern const char *zlibVersion(void);
extern int deflate(z_streamp strm, int flush);
extern int deflateEnd(z_streamp strm);
extern int inflate(z_streamp strm, int flush);
extern int inflateEnd(z_streamp strm);
extern int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int deflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int deflateCopy(z_streamp dest, z_streamp source);
extern int deflateReset(z_streamp strm);
extern int deflateParams(z_streamp strm, int level, int strategy);
extern int deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain);
extern uLong deflateBound(z_streamp strm, uLong sourceLen);
extern int deflatePending(z_streamp strm, unsigned *pending, int *bits);
extern int deflatePrime(z_streamp strm, int bits, int value);
extern int deflateSetHeader(z_streamp strm, gz_headerp head);
extern int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int inflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int inflateSync(z_streamp strm);
extern int inflateCopy(z_streamp dest, z_streamp source);
extern int inflateReset(z_streamp strm);
extern int inflateReset2(z_streamp strm, int windowBits);
extern int inflatePrime(z_streamp strm, int bits, int value);
extern long inflateMark(z_streamp strm);
extern int inflateGetHeader(z_streamp strm, gz_headerp head);
typedef unsigned (*in_func)(void *, unsigned char **);
typedef int (*out_func)(void *, unsigned char *, unsigned);
extern int inflateBack(z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc);
extern int inflateBackEnd(z_streamp strm);
extern uLong zlibCompileFlags(void);
extern int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level);
extern uLong compressBound(uLong sourceLen);
extern int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int uncompress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen);
typedef struct gzFile_s *gzFile;
extern gzFile gzdopen(int fd, const char *mode);
extern int gzbuffer(gzFile file, unsigned size);
extern int gzsetparams(gzFile file, int level, int strategy);
extern int gzread(gzFile file, voidp buf, unsigned len);
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzwrite(gzFile file, voidpc buf, unsigned len);
extern z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzprintf(gzFile file, const char *format, ...);
extern int gzputs(gzFile file, const char *s);
extern char *gzgets(gzFile file, char *buf, int len);
extern int gzputc(gzFile file, int c);
extern int gzgetc(gzFile file);
extern int gzungetc(int c, gzFile file);
extern int gzflush(gzFile file, int flush);
extern int gzrewind(gzFile file);
extern int gzeof(gzFile file);
extern int gzdirect(gzFile file);
extern int gzclose(gzFile file);
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
extern const char *gzerror(gzFile file, int *errnum);
extern void gzclearerr(gzFile file);
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
extern uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len);
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
extern uLong crc32_z(uLong crc, const Bytef *buf, z_size_t len);
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
extern int deflateInit_(z_streamp strm, int level, const char *version, int stream_size);
extern int inflateInit_(z_streamp strm, const char *version, int stream_size);
extern int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size);
extern int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size);
extern int inflateBackInit_(z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size);
struct gzFile_s
{
  unsigned have;
  unsigned char *next;
  off_t pos;
};
extern int gzgetc_(gzFile file);
extern gzFile gzopen(const char *, const char *);
extern off_t gzseek(gzFile, off_t, int);
extern off_t gztell(gzFile);
extern off_t gzoffset(gzFile);
extern uLong adler32_combine(uLong, uLong, off_t);
extern uLong crc32_combine(uLong, uLong, off_t);
extern uLong crc32_combine_gen(off_t);
extern const char *zError(int);
extern int inflateSyncPoint(z_streamp);
extern const z_crc_t *get_crc_table(void);
extern int inflateUndermine(z_streamp, int);
extern int inflateValidate(z_streamp, int);
extern unsigned long inflateCodesUsed(z_streamp);
extern int inflateResetKeep(z_streamp);
extern int deflateResetKeep(z_streamp);
extern int gzvprintf(gzFile file, const char *format, va_list va);
typedef long opng_foffset_t;
typedef unsigned long opng_fsize_t;
opng_foffset_t opng_ftello(FILE *stream);
int opng_fseeko(FILE *stream, opng_foffset_t offset, int whence);
size_t opng_freado(FILE *stream, opng_foffset_t offset, int whence, void *block, size_t blocksize);
size_t opng_fwriteo(FILE *stream, opng_foffset_t offset, int whence, const void *block, size_t blocksize);
int opng_fgetsize(FILE *stream, opng_fsize_t *size);
char *opng_path_replace_dir(char *buffer, size_t bufsize, const char *old_path, const char *new_dirname);
char *opng_path_replace_ext(char *buffer, size_t bufsize, const char *old_path, const char *new_extname);
char *opng_path_make_backup(char *buffer, size_t bufsize, const char *path);
int opng_os_rename(const char *src_path, const char *dest_path, int clobber);
int opng_os_create_dir(const char *dirname);
int opng_os_copy_file_attr(const char *src_path, const char *dest_path);
int opng_os_test_file_access(const char *path, const char *mode);
int opng_os_test_file_equiv(const char *path1, const char *path2);
int opng_os_unlink(const char *path);
struct opng_lratio
{
  long num;
  long denom;
};
struct opng_ulratio
{
  unsigned long num;
  unsigned long denom;
};
int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
int opng_ulratio_to_percent_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t;
struct exception_context
{
  jmp_buf *penv;
  int caught;
  volatile struct 
  {
    opng_status_t etmp;
  } v;
};
struct exception_context the_exception_context[1];
static const struct opng_preset_struct
{
  const char *compr_level;
  const char *mem_level;
  const char *strategy;
  const char *filter;
} k_presets[7 + 1] = {{"", "", "", ""}, {"", "", "", ""}, {"9", "8", "0-", "0,5"}, {"9", "8-9", "0-", "0,5"}, {"9", "8", "0-", "0-"}, {"9", "8-9", "0-", "0-"}, {"1-9", "8", "0-", "0-"}, {"1-9", "8-9", "0-", "0-"}};
static const int k_filter_table[5 + 1] = {0x08, 0x10, 0x20, 0x40, 0x80, (((0x08 | 0x10) | 0x20) | 0x40) | 0x80};
static const png_byte k_sig_PLTE[4] = {0x50, 0x4c, 0x54, 0x45};
static const png_byte k_sig_tRNS[4] = {0x74, 0x52, 0x4e, 0x53};
static const png_byte k_sig_IDAT[4] = {0x49, 0x44, 0x41, 0x54};
static const png_byte k_sig_IEND[4] = {0x49, 0x45, 0x4e, 0x44};
static const png_byte k_sig_bKGD[4] = {0x62, 0x4b, 0x47, 0x44};
static const png_byte k_sig_hIST[4] = {0x68, 0x49, 0x53, 0x54};
static const png_byte k_sig_sBIT[4] = {0x73, 0x42, 0x49, 0x54};
static const png_byte k_sig_dSIG[4] = {0x64, 0x53, 0x49, 0x47};
static const png_byte k_sig_acTL[4] = {0x61, 0x63, 0x54, 0x4c};
static const png_byte k_sig_fcTL[4] = {0x66, 0x63, 0x54, 0x4c};
static const png_byte k_sig_fdAT[4] = {0x66, 0x64, 0x41, 0x54};
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL;
static const char *k_idat_size_max_string = "2GB";
enum 
{
  INPUT_IS_PNG_FILE = 0x0001,
  INPUT_HAS_PNG_DATASTREAM = 0x0002,
  INPUT_HAS_PNG_SIGNATURE = 0x0004,
  INPUT_HAS_DIGITAL_SIGNATURE = 0x0008,
  INPUT_HAS_MULTIPLE_IMAGES = 0x0010,
  INPUT_HAS_APNG = 0x0020,
  INPUT_HAS_STRIPPED_DATA = 0x0040,
  INPUT_HAS_JUNK = 0x0080,
  INPUT_HAS_ERRORS = 0x0100,
  OUTPUT_NEEDS_NEW_FILE = 0x1000,
  OUTPUT_NEEDS_NEW_IDAT = 0x2000,
  OUTPUT_HAS_ERRORS = 0x4000
};
static struct opng_engine_struct
{
  int started;
} s_engine;
static struct opng_process_struct
{
  unsigned int status;
  int num_iterations;
  opng_foffset_t in_datastream_offset;
  opng_fsize_t in_file_size;
  opng_fsize_t out_file_size;
  opng_fsize_t in_idat_size;
  opng_fsize_t out_idat_size;
  opng_fsize_t best_idat_size;
  opng_fsize_t max_idat_size;
  png_uint_32 in_plte_trns_size;
  png_uint_32 out_plte_trns_size;
  png_uint_32 reductions;
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int best_compr_level;
  int best_mem_level;
  int best_strategy;
  int best_filter;
} s_process;
static struct opng_summary_struct
{
  unsigned int file_count;
  unsigned int err_count;
  unsigned int fix_count;
  unsigned int snip_count;
} s_summary;
static struct opng_image_struct
{
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int interlace_type;
  png_bytepp row_pointers;
  png_colorp palette;
  int num_palette;
  png_color_16p background_ptr;
  png_color_16 background;
  png_uint_16p hist;
  png_color_8p sig_bit_ptr;
  png_color_8 sig_bit;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p trans_color_ptr;
  png_color_16 trans_color;
  png_unknown_chunkp unknowns;
  int num_unknowns;
} s_image;
static struct opng_options s_options;
static png_structp s_read_ptr;
static png_infop s_read_info_ptr;
static png_structp s_write_ptr;
static png_infop s_write_info_ptr;
static void (*usr_printf)(const char *fmt, ...);
static void (*usr_print_cntrl)(int cntrl_code);
static void (*usr_progress)(unsigned long num, unsigned long denom);
static void (*usr_panic)(const char *msg);
static void opng_print_fsize_ratio(opng_fsize_t num, opng_fsize_t denom)
{
  char buffer[32];
  struct opng_ulratio ratio;
  int result;
  ratio.num = num;
  ratio.denom = denom;
  result = opng_ulratio_to_factor_string(buffer, sizeof(buffer), &ratio);
  usr_printf("%s%s", buffer, (result > 0) ? ("") : ("..."));
}

static void opng_print_fsize_difference(opng_fsize_t init_size, opng_fsize_t final_size, int show_ratio)
{
  opng_fsize_t difference;
  int sign;
  if (init_size <= final_size)
  {
    sign = 0;
    difference = final_size - init_size;
  }
  else
  {
    sign = 1;
    difference = init_size - final_size;
  }
  if (difference == 0)
  {
    usr_printf("no change");
    return;
  }
  if (difference == 1)
  {
    usr_printf("1 byte");
  }
  else
    usr_printf("%lu bytes", difference);
  if (show_ratio && (init_size > 0))
  {
    usr_printf(" = ");
    opng_print_fsize_ratio(difference, init_size);
  }
  usr_printf((sign == 0) ? (" increase") : (" decrease"));
}

static void opng_print_image_info(int show_dim, int show_depth, int show_type, int show_interlaced)
{
  static const int type_channels[8] = {1, 0, 3, 1, 2, 0, 4, 0};
  int channels;
  int printed;
  printed = 0;
  if (show_dim)
  {
    printed = 1;
    usr_printf("%lux%lu pixels", (unsigned long) s_image.width, (unsigned long) s_image.height);
  }
  if (show_depth)
  {
    if (printed)
    {
      usr_printf(", ");
    }
    printed = 1;
    channels = type_channels[s_image.color_type & 7];
    if (channels != 1)
    {
      usr_printf("%dx%d bits/pixel", channels, s_image.bit_depth);
    }
    else
      if (s_image.bit_depth != 1)
    {
      usr_printf("%d bits/pixel", s_image.bit_depth);
    }
    else
      usr_printf("1 bit/pixel");
  }
  if (show_type)
  {
    if (printed)
    {
      usr_printf(", ");
    }
    printed = 1;
    if (s_image.color_type & 1)
    {
      if (s_image.num_palette == 1)
      {
        usr_printf("1 color");
      }
      else
        usr_printf("%d colors", s_image.num_palette);
      if (s_image.num_trans > 0)
      {
        usr_printf(" (%d transparent)", s_image.num_trans);
      }
      usr_printf(" in palette");
    }
    else
    {
      usr_printf((s_image.color_type & 2) ? ("RGB") : ("grayscale"));
      if (s_image.color_type & 4)
      {
        usr_printf("+alpha");
      }
      else
        if (s_image.trans_color_ptr != 0)
      {
        usr_printf("+transparency");
      }
    }
  }
  if (show_interlaced)
  {
    if (s_image.interlace_type != 0)
    {
      if (printed)
      {
        usr_printf(", ");
      }
      usr_printf("interlaced");
    }
  }
}

static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}

static void opng_print_error(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Error: %s\n", msg);
}

static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}

static void opng_warning(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
  }
  opng_print_warning(msg);
}

static void opng_error(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
    if (opng_validate_image(s_read_ptr, s_read_info_ptr))
    {
      opng_print_warning(msg);
      for (;; longjmp(*the_exception_context->penv, 1))
      {
        the_exception_context->v.etmp = OPNG_STATUS_OK;
      }

    }
  }
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_LIBPNG;
  }

}

static void opng_free(void *ptr)
{
  free(ptr);
}

static void opng_check_idat_size(opng_fsize_t size)
{
  if (size > k_idat_size_max)
  {
    opng_throw_error("IDAT sizes larger than the maximum chunk size are currently unsupported");
  }
}

static void opng_set_keep_unknown_chunk(png_structp png_ptr, int keep, png_bytep chunk_type)
{
  png_byte chunk_name[5];
  memcpy(chunk_name, chunk_type, 4);
  chunk_name[4] = 0;
  if (!png_handle_as_unknown(png_ptr, chunk_name))
  {
    png_set_keep_unknown_chunks(png_ptr, keep, chunk_name, 1);
  }
}

static int opng_is_image_chunk(png_bytep chunk_type)
{
  if ((chunk_type[0] & 0x20) == 0)
  {
    return 1;
  }
  if (memcmp(chunk_type, k_sig_tRNS, 4) == 0)
  {
    return 1;
  }
  return 0;
}

static int opng_is_apng_chunk(png_bytep chunk_type)
{
  if (((memcmp(chunk_type, k_sig_acTL, 4) == 0) || (memcmp(chunk_type, k_sig_fcTL, 4) == 0)) || (memcmp(chunk_type, k_sig_fdAT, 4) == 0))
  {
    return 1;
  }
  return 0;
}

static int opng_allow_chunk(png_bytep chunk_type)
{
  if (opng_is_image_chunk(chunk_type))
  {
    return 1;
  }
  if (s_options.strip_all)
  {
    return 0;
  }
  if (memcmp(chunk_type, k_sig_dSIG, 4) == 0)
  {
    return 0;
  }
  if (s_options.snip && opng_is_apng_chunk(chunk_type))
  {
    return 0;
  }
  return 1;
}

static void opng_handle_chunk(png_structp png_ptr, png_bytep chunk_type)
{
  int keep;
  if (opng_is_image_chunk(chunk_type))
  {
    return;
  }
  if (s_options.strip_all)
  {
    s_process.status |= INPUT_HAS_STRIPPED_DATA | INPUT_HAS_JUNK;
    opng_set_keep_unknown_chunk(png_ptr, 1, chunk_type);
    return;
  }
  if (((memcmp(chunk_type, k_sig_bKGD, 4) == 0) || (memcmp(chunk_type, k_sig_hIST, 4) == 0)) || (memcmp(chunk_type, k_sig_sBIT, 4) == 0))
  {
    return;
  }
  keep = 3;
  if (memcmp(chunk_type, k_sig_dSIG, 4) == 0)
  {
    s_process.status |= INPUT_HAS_DIGITAL_SIGNATURE;
  }
  else
    if (opng_is_apng_chunk(chunk_type))
  {
    s_process.status |= INPUT_HAS_APNG;
    if (memcmp(chunk_type, k_sig_fdAT, 4) == 0)
    {
      s_process.status |= INPUT_HAS_MULTIPLE_IMAGES;
    }
    if (s_options.snip)
    {
      s_process.status |= INPUT_HAS_JUNK;
      keep = 1;
    }
  }
  opng_set_keep_unknown_chunk(png_ptr, keep, chunk_type);
}

static void opng_init_read_data(void)
{
}

static void opng_init_write_data(void)
{
  s_process.out_file_size = 0;
  s_process.out_plte_trns_size = 0;
  s_process.out_idat_size = 0;
}

static void opng_read_data(png_structp png_ptr, png_bytep data, size_t length)
{
  FILE *stream = (FILE *) png_get_io_ptr(png_ptr);
  int io_state = png_get_io_state(png_ptr);
  int io_state_loc = io_state & 0x00f0;
  png_bytep chunk_sig;
  if (fread(data, 1, length, stream) != length)
  {
    png_error(png_ptr, "Can't read the input file or unexpected end of file");
  }
  if (s_process.in_file_size == 0)
  {
    {
      if (!(length == 8))
      {
        usr_panic("PNG I/O must start with the first 8 bytes");
      }
    }
    ;
    s_process.in_datastream_offset = opng_ftello(stream) - 8;
    s_process.status |= INPUT_HAS_PNG_DATASTREAM;
    if (io_state_loc == 0x0010)
    {
      s_process.status |= INPUT_HAS_PNG_SIGNATURE;
    }
    if (s_process.in_datastream_offset == 0)
    {
      s_process.status |= INPUT_IS_PNG_FILE;
    }
    else
      if (s_process.in_datastream_offset < 0)
    {
      png_error(png_ptr, "Can't get the file-position indicator in input file");
    }
    s_process.in_file_size = (opng_fsize_t) s_process.in_datastream_offset;
  }
  s_process.in_file_size += length;
  {
    if (!((io_state & 0x0001) && (io_state_loc != 0)))
    {
      usr_panic("Incorrect info in png_ptr->io_state");
    }
  }
  ;
  if (io_state_loc == 0x0020)
  {
    {
      if (!(length == 8))
      {
        usr_panic("Reading chunk header, expecting 8 bytes");
      }
    }
    ;
    chunk_sig = data + 4;
    if (memcmp(chunk_sig, k_sig_IDAT, 4) == 0)
    {
      {
        if (!(png_ptr == s_read_ptr))
        {
          usr_panic("Incorrect I/O handler setup");
        }
      }
      ;
      if (png_get_rows(s_read_ptr, s_read_info_ptr) == 0)
      {
        {
          if (!(s_process.in_idat_size == 0))
          {
            usr_panic("Found IDAT with no rows");
          }
        }
        ;
        if (png_get_image_height(s_read_ptr, s_read_info_ptr) == 0)
        {
          return;
        }
        {
          if (!(pngx_malloc_rows(s_read_ptr, s_read_info_ptr, 0) != 0))
          {
            usr_panic("Failed allocation of image rows; unsafe libpng allocator");
          }
        }
        ;
        png_data_freer(s_read_ptr, s_read_info_ptr, 2, 0x0040U);
      }
      else
      {
        s_process.status |= INPUT_HAS_JUNK;
      }
      s_process.in_idat_size += (((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)));
    }
    else
      if ((memcmp(chunk_sig, k_sig_PLTE, 4) == 0) || (memcmp(chunk_sig, k_sig_tRNS, 4) == 0))
    {
      s_process.in_plte_trns_size += ((((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)))) + 12;
    }
    else
      opng_handle_chunk(png_ptr, chunk_sig);
  }
  else
    if (io_state_loc == 0x0080)
  {
    {
      if (!(length == 4))
      {
        usr_panic("Reading chunk CRC, expecting 4 bytes");
      }
    }
    ;
  }
}

static void opng_write_data(png_structp png_ptr, png_bytep data, size_t length)
{
  static int allow_crt_chunk;
  static int crt_chunk_is_idat;
  static opng_foffset_t crt_idat_offset;
  static opng_fsize_t crt_idat_size;
  static png_uint_32 crt_idat_crc;
  FILE *stream = (FILE *) png_get_io_ptr(png_ptr);
  int io_state = png_get_io_state(png_ptr);
  int io_state_loc = io_state & 0x00f0;
  png_bytep chunk_sig;
  png_byte buf[4];
  {
    if (!((io_state & 0x0002) && (io_state_loc != 0)))
    {
      usr_panic("Incorrect info in png_ptr->io_state");
    }
  }
  ;
  if (io_state_loc == 0x0020)
  {
    {
      if (!(length == 8))
      {
        usr_panic("Writing chunk header, expecting 8 bytes");
      }
    }
    ;
    chunk_sig = data + 4;
    allow_crt_chunk = opng_allow_chunk(chunk_sig);
    if (memcmp(chunk_sig, k_sig_IDAT, 4) == 0)
    {
      crt_chunk_is_idat = 1;
      s_process.out_idat_size += (((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)));
      if (stream == 0)
      {
        if (s_process.out_idat_size > s_process.max_idat_size)
        {
          for (;; longjmp(*the_exception_context->penv, 1))
          {
            the_exception_context->v.etmp = OPNG_STATUS_OK;
          }

        }
      }
    }
    else
    {
      crt_chunk_is_idat = 0;
      if ((memcmp(chunk_sig, k_sig_PLTE, 4) == 0) || (memcmp(chunk_sig, k_sig_tRNS, 4) == 0))
      {
        s_process.out_plte_trns_size += ((((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)))) + 12;
      }
    }
  }
  else
    if (io_state_loc == 0x0080)
  {
    {
      if (!(length == 4))
      {
        usr_panic("Writing chunk CRC, expecting 4 bytes");
      }
    }
    ;
  }
  if (stream == 0)
  {
    return;
  }
  if ((io_state_loc != 0x0010) && (!allow_crt_chunk))
  {
    return;
  }
  switch (io_state_loc)
  {
    case 0x0020:
      if (crt_chunk_is_idat)
    {
      if (crt_idat_offset == 0)
      {
        crt_idat_offset = opng_ftello(stream);
        if (s_process.best_idat_size > 0)
        {
          crt_idat_size = s_process.best_idat_size;
        }
        else
        {
          crt_idat_size = length;
        }
        png_save_uint_32(data, (png_uint_32) crt_idat_size);
        crt_idat_crc = crc32(0, k_sig_IDAT, 4);
      }
      else
      {
        return;
      }
    }
    else
    {
      if (crt_idat_offset != 0)
      {
        png_save_uint_32(buf, crt_idat_crc);
        if (fwrite(buf, 1, 4, stream) != 4)
        {
          io_state = 0;
        }
        s_process.out_file_size += 4;
        if (s_process.out_idat_size != crt_idat_size)
        {
          {
            if (!(s_process.best_idat_size == 0))
            {
              usr_panic("Wrong guess of the output IDAT size");
            }
          }
          ;
          opng_check_idat_size(s_process.out_idat_size);
          png_save_uint_32(buf, (png_uint_32) s_process.out_idat_size);
          if (opng_fwriteo(stream, crt_idat_offset, 0, buf, 4) != 4)
          {
            io_state = 0;
          }
        }
        if (io_state == 0)
        {
          png_error(png_ptr, "Can't finalize IDAT");
        }
        crt_idat_offset = 0;
      }
    }
      break;

    case 0x0040:
      if (crt_chunk_is_idat)
    {
      crt_idat_crc = crc32(crt_idat_crc, data, length);
    }
      break;

    case 0x0080:
      if (crt_chunk_is_idat)
    {
      return;
    }
      break;

  }

  if (fwrite(data, 1, length, stream) != length)
  {
    png_error(png_ptr, "Can't write the output file");
  }
  s_process.out_file_size += length;
}

static void opng_clear_image_info(void)
{
  memset(&s_image, 0, sizeof(s_image));
}

static void opng_load_image_info(png_structp png_ptr, png_infop info_ptr, int load_meta)
{
  memset(&s_image, 0, sizeof(s_image));
  png_get_IHDR(png_ptr, info_ptr, &s_image.width, &s_image.height, &s_image.bit_depth, &s_image.color_type, &s_image.interlace_type, &s_image.compression_type, &s_image.filter_type);
  s_image.row_pointers = png_get_rows(png_ptr, info_ptr);
  png_get_PLTE(png_ptr, info_ptr, &s_image.palette, &s_image.num_palette);
  if (png_get_tRNS(png_ptr, info_ptr, &s_image.trans_alpha, &s_image.num_trans, &s_image.trans_color_ptr))
  {
    if (s_image.trans_color_ptr != 0)
    {
      s_image.trans_color = *s_image.trans_color_ptr;
      s_image.trans_color_ptr = &s_image.trans_color;
    }
  }
  if (!load_meta)
  {
    return;
  }
  if (png_get_bKGD(png_ptr, info_ptr, &s_image.background_ptr))
  {
    s_image.background = *s_image.background_ptr;
    s_image.background_ptr = &s_image.background;
  }
  png_get_hIST(png_ptr, info_ptr, &s_image.hist);
  if (png_get_sBIT(png_ptr, info_ptr, &s_image.sig_bit_ptr))
  {
    s_image.sig_bit = *s_image.sig_bit_ptr;
    s_image.sig_bit_ptr = &s_image.sig_bit;
  }
  s_image.num_unknowns = png_get_unknown_chunks(png_ptr, info_ptr, &s_image.unknowns);
}

static void opng_store_image_info(png_structp png_ptr, png_infop info_ptr, int store_meta)
{
  int i;
  {
    if (!(s_image.row_pointers != 0))
    {
      usr_panic("No info in image");
    }
  }
  ;
  png_set_IHDR(png_ptr, info_ptr, s_image.width, s_image.height, s_image.bit_depth, s_image.color_type, s_image.interlace_type, s_image.compression_type, s_image.filter_type);
  png_set_rows(s_write_ptr, s_write_info_ptr, s_image.row_pointers);
  if (s_image.palette != 0)
  {
    png_set_PLTE(png_ptr, info_ptr, s_image.palette, s_image.num_palette);
  }
  if ((s_image.trans_alpha != 0) || (s_image.trans_color_ptr != 0))
  {
    png_set_tRNS(png_ptr, info_ptr, s_image.trans_alpha, s_image.num_trans, s_image.trans_color_ptr);
  }
  if (!store_meta)
  {
    return;
  }
  if (s_image.background_ptr != 0)
  {
    png_set_bKGD(png_ptr, info_ptr, s_image.background_ptr);
  }
  if (s_image.hist != 0)
  {
    png_set_hIST(png_ptr, info_ptr, s_image.hist);
  }
  if (s_image.sig_bit_ptr != 0)
  {
    png_set_sBIT(png_ptr, info_ptr, s_image.sig_bit_ptr);
  }
  if (s_image.num_unknowns != 0)
  {
    png_set_unknown_chunks(png_ptr, info_ptr, s_image.unknowns, s_image.num_unknowns);
    for (i = 0; i < s_image.num_unknowns; i += 1)
    {
      png_set_unknown_chunk_location(png_ptr, info_ptr, i, s_image.unknowns[i].location);
    }

  }
}

static void opng_destroy_image_info(void)
{
  png_uint_32 i;
  int j;
  if (s_image.row_pointers == 0)
  {
    return;
  }
  for (i = 0; i < s_image.height; i += 1)
  {
    opng_free(s_image.row_pointers[i]);
  }

  opng_free(s_image.row_pointers);
  opng_free(s_image.palette);
  opng_free(s_image.trans_alpha);
  opng_free(s_image.hist);
  for (j = 0; j < s_image.num_unknowns; j += 1)
  {
    opng_free(s_image.unknowns[j].data);
  }

  opng_free(s_image.unknowns);
  memset(&s_image, 0, sizeof(s_image));
}

static void opng_read_file(FILE *infile)
{
  const char *fmt_name;
  unsigned int fmt_name_idx = 0;
  int num_img;
  png_uint_32 reductions;
  volatile opng_status_t status;
  status = OPNG_STATUS_OK;
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        s_read_ptr = png_create_read_struct("1.6.40", 0, opng_error, opng_warning);
        s_read_info_ptr = png_create_info_struct(s_read_ptr);
        if (s_read_info_ptr == 0)
        {
          opng_throw_error("Can't create image decoder");
        }
        png_set_keep_unknown_chunks(s_read_ptr, 3, 0, 0);
        png_set_user_limits(s_read_ptr, (png_uint_32) 0x7fffffffL, (png_uint_32) 0x7fffffffL);
        opng_init_read_data();
        png_set_read_fn(s_read_ptr, infile, opng_read_data);
        fmt_name_idx = 0;
        num_img = pngx_read_image(s_read_ptr, s_read_info_ptr, &(&fmt_name[fmt_name_idx]), 0);
        if (num_img <= 0)
        {
          opng_throw_error("Unrecognized image file format");
        }
        if (num_img > 1)
        {
          s_process.status |= INPUT_HAS_MULTIPLE_IMAGES;
        }
        if ((s_process.status & INPUT_IS_PNG_FILE) && (s_process.status & INPUT_HAS_MULTIPLE_IMAGES))
        {
          fmt_name_idx = (s_process.status & INPUT_HAS_PNG_SIGNATURE) ? ("APNG") : ("APNG datastream");
        }
        {
          if (!((&fmt_name[fmt_name_idx]) != 0))
          {
            usr_panic("No format name from pngxtern");
          }
        }
        ;
        if (s_process.in_file_size == 0)
        {
          if (opng_fgetsize(infile, &s_process.in_file_size) < 0)
          {
            opng_print_warning("Can't get the correct file size");
            s_process.in_file_size = 0;
          }
        }
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    if (opng_validate_image(s_read_ptr, s_read_info_ptr))
    {
      if (!(status == OPNG_STATUS_OK))
      {
        usr_panic("Mysterious error in validated image file");
      }
    }
    ;
  }
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        if (status != OPNG_STATUS_OK)
        {
          for (;; longjmp(*the_exception_context->penv, 1))
          {
            the_exception_context->v.etmp = status;
          }

        }
        if (strcmp(fmt_name, "PNG") != 0)
        {
          usr_printf("Importing %s", fmt_name);
          if (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)
          {
            if (!(s_process.status & INPUT_IS_PNG_FILE))
            {
              usr_printf(" (multi-image or animation)");
            }
            if (s_options.snip)
            {
              usr_printf("; snipping...");
            }
          }
          usr_printf("\n");
        }
        opng_load_image_info(s_read_ptr, s_read_info_ptr, 1);
        opng_print_image_info(1, 1, 1, 1);
        usr_printf("\n");
        reductions = ((((0x0001 | 0x0002) | (((((0x0004 | 0x0008) | 0x0010) | 0x0020) | 0x0040) | 0x0080)) | (0x0100 | 0x0200)) | 0x1000) & (~0x1000);
        if (s_options.nb)
        {
          reductions &= ~(0x0001 | 0x0002);
        }
        if (s_options.nc)
        {
          reductions &= ~(((((0x0004 | 0x0008) | 0x0010) | 0x0020) | 0x0040) | 0x0080);
        }
        if (s_options.np)
        {
          reductions &= ~(0x0100 | 0x0200);
        }
        if (s_options.nz && (s_process.status & INPUT_HAS_PNG_DATASTREAM))
        {
          reductions = 0x0000;
        }
        if (s_process.status & INPUT_HAS_DIGITAL_SIGNATURE)
        {
          reductions = 0x0000;
        }
        if ((((s_process.status & INPUT_IS_PNG_FILE) && (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)) && (reductions != 0x0000)) && (!s_options.snip))
        {
          usr_printf("Can't reliably reduce APNG file; disabling reductions.\n(Did you want to -snip and optimize the first frame?)\n");
          reductions = 0x0000;
        }
        s_process.reductions = opng_reduce_image(s_read_ptr, s_read_info_ptr, reductions);
        if (s_process.reductions != 0x0000)
        {
          opng_load_image_info(s_read_ptr, s_read_info_ptr, 1);
          usr_printf("Reducing image to ");
          opng_print_image_info(0, 1, 1, 0);
          usr_printf("\n");
        }
        if ((s_options.interlace >= 0) && (s_image.interlace_type != s_options.interlace))
        {
          s_image.interlace_type = s_options.interlace;
          s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
        }
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    png_data_freer(s_read_ptr, s_read_info_ptr, 1, 0xffffU);
    png_destroy_read_struct(&s_read_ptr, &s_read_info_ptr, 0);
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  png_data_freer(s_read_ptr, s_read_info_ptr, 2, 0xffffU);
  png_destroy_read_struct(&s_read_ptr, &s_read_info_ptr, 0);
}

static void opng_write_file(FILE *outfile, int compression_level, int memory_level, int compression_strategy, int filter)
{
  volatile opng_status_t status;
  {
    if (!((((((((compression_level >= 1) && (compression_level <= 9)) && (memory_level >= 1)) && (memory_level <= 9)) && (compression_strategy >= 0)) && (compression_strategy <= 3)) && (filter >= 0)) && (filter <= 5)))
    {
      usr_panic("Invalid encoding parameters");
    }
  }
  ;
  status = OPNG_STATUS_OK;
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        s_write_ptr = png_create_write_struct("1.6.40", 0, opng_error, opng_warning);
        s_write_info_ptr = png_create_info_struct(s_write_ptr);
        if (s_write_info_ptr == 0)
        {
          opng_throw_error("Can't create image encoder");
        }
        png_set_compression_level(s_write_ptr, compression_level);
        png_set_compression_mem_level(s_write_ptr, memory_level);
        png_set_compression_strategy(s_write_ptr, compression_strategy);
        png_set_filter(s_write_ptr, 0, k_filter_table[filter]);
        if ((compression_strategy != 2) && (compression_strategy != 3))
        {
          if (s_options.window_bits > 0)
          {
            png_set_compression_window_bits(s_write_ptr, s_options.window_bits);
          }
        }
        else
        {
          png_set_compression_window_bits(s_write_ptr, 9);
        }
        png_set_keep_unknown_chunks(s_write_ptr, 3, 0, 0);
        png_set_user_limits(s_write_ptr, (png_uint_32) 0x7fffffffL, (png_uint_32) 0x7fffffffL);
        opng_store_image_info(s_write_ptr, s_write_info_ptr, outfile != 0);
        opng_init_write_data();
        png_set_write_fn(s_write_ptr, outfile, opng_write_data, 0);
        png_write_png(s_write_ptr, s_write_info_ptr, 0, 0);
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    s_process.out_idat_size = k_idat_size_max + 1;
  }
  png_destroy_write_struct(&s_write_ptr, &s_write_info_ptr);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
}

static void opng_copy_file(FILE *infile, FILE *outfile)
{
  volatile png_bytep buf;
  const png_uint_32 buf_size_incr = 0x1000;
  png_uint_32 buf_size;
  png_uint_32 length;
  png_byte chunk_hdr[8];
  volatile opng_status_t status;
  s_write_ptr = png_create_write_struct("1.6.40", 0, opng_error, opng_warning);
  if (s_write_ptr == 0)
  {
    opng_throw_error("Can't create image encoder");
  }
  opng_init_write_data();
  png_set_write_fn(s_write_ptr, outfile, opng_write_data, 0);
  status = OPNG_STATUS_OK;
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        buf = 0;
        buf_size = 0;
        png_write_sig(s_write_ptr);
        do
        {
          if (fread(chunk_hdr, 8, 1, infile) != 1)
          {
            opng_throw_error("Read error");
          }
          length = (((((png_uint_32) (*chunk_hdr)) << 24) + (((png_uint_32) (*(chunk_hdr + 1))) << 16)) + (((png_uint_32) (*(chunk_hdr + 2))) << 8)) + ((png_uint_32) (*(chunk_hdr + 3)));
          if (length > ((png_uint_32) 0x7fffffffL))
          {
            if ((buf == 0) && (length == 0x89504e47UL))
            {
              continue;
            }
            opng_throw_error("Data error");
          }
          if ((length + 4) > buf_size)
          {
            png_free(s_write_ptr, buf);
            buf_size = (((length + 4) + (buf_size_incr - 1)) / buf_size_incr) * buf_size_incr;
            buf = (png_bytep) png_malloc(s_write_ptr, buf_size);
          }
          if (fread(buf, length + 4, 1, infile) != 1)
          {
            opng_throw_error("Read error");
          }
          png_write_chunk(s_write_ptr, chunk_hdr + 4, buf, length);
        }
        while (memcmp(chunk_hdr + 4, k_sig_IEND, 4) != 0);
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
  }
  png_free(s_write_ptr, buf);
  png_destroy_write_struct(&s_write_ptr, 0);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
}

static void opng_init_iteration(opng_bitset_t cmdline_set, opng_bitset_t mask_set, const char *preset, opng_bitset_t *output_set)
{
  opng_bitset_t preset_set;
  int check;
  *output_set = cmdline_set & mask_set;
  if (((*output_set) == 0) && (cmdline_set != 0))
  {
    opng_throw_error("Iteration parameter(s) out of range");
  }
  if ((s_options.optim_level >= 0) || ((*output_set) == 0))
  {
    check = opng_strparse_rangeset_to_bitset(&preset_set, preset, mask_set);
    {
      if (!(check == 0))
      {
        usr_panic("[internal] Invalid preset");
      }
    }
    ;
    *output_set |= preset_set & mask_set;
  }
}

static void opng_init_iterations(void)
{
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  opng_bitset_t strategy_singles_set;
  int preset_index;
  int t1;
  int t2;
  if (s_options.full || (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
  {
    s_process.max_idat_size = k_idat_size_max;
  }
  else
  {
    {
      if (!(s_process.in_idat_size > 0))
      {
        usr_panic("No IDAT in input");
      }
    }
    ;
    s_process.max_idat_size = s_process.in_idat_size + s_process.in_plte_trns_size;
  }
  preset_index = s_options.optim_level;
  if (preset_index < 0)
  {
    preset_index = 2;
  }
  else
    if (preset_index > 7)
  {
    preset_index = 7;
  }
  opng_init_iteration(s_options.compr_level_set, (1 << (9 + 1)) - (1 << 1), k_presets[preset_index].compr_level, &compr_level_set);
  opng_init_iteration(s_options.mem_level_set, (1 << (9 + 1)) - (1 << 1), k_presets[preset_index].mem_level, &mem_level_set);
  opng_init_iteration(s_options.strategy_set, (1 << (3 + 1)) - (1 << 0), k_presets[preset_index].strategy, &strategy_set);
  opng_init_iteration(s_options.filter_set, (1 << (5 + 1)) - (1 << 0), k_presets[preset_index].filter, &filter_set);
  if (compr_level_set == 0)
  {
    compr_level_set |= 1U << 9;
  }
  if (mem_level_set == 0)
  {
    mem_level_set |= 1U << 8;
  }
  if ((s_image.bit_depth < 8) || (s_image.palette != 0))
  {
    if (strategy_set == 0)
    {
      strategy_set |= 1U << 0;
    }
    if (filter_set == 0)
    {
      filter_set |= 1U << 0;
    }
  }
  else
  {
    if (strategy_set == 0)
    {
      strategy_set |= 1U << 1;
    }
    if (filter_set == 0)
    {
      filter_set |= 1U << 5;
    }
  }
  s_process.compr_level_set = compr_level_set;
  s_process.mem_level_set = mem_level_set;
  s_process.strategy_set = strategy_set;
  s_process.filter_set = filter_set;
  strategy_singles_set = (1 << 2) | (1 << 3);
  t1 = opng_bitset_count(compr_level_set) * opng_bitset_count(strategy_set & (~strategy_singles_set));
  t2 = opng_bitset_count(strategy_set & strategy_singles_set);
  s_process.num_iterations = ((t1 + t2) * opng_bitset_count(mem_level_set)) * opng_bitset_count(filter_set);
  {
    if (!(s_process.num_iterations > 0))
    {
      usr_panic("Invalid iteration parameters");
    }
  }
  ;
}

static void opng_iterate(void)
{
  opng_bitset_t compr_level_set;
  opng_bitset_t mem_level_set;
  opng_bitset_t strategy_set;
  opng_bitset_t filter_set;
  int compr_level;
  int mem_level;
  int strategy;
  int filter;
  int counter;
  int line_reused;
  {
    if (!(s_process.num_iterations > 0))
    {
      usr_panic("Iterations not initialized");
    }
  }
  ;
  compr_level_set = s_process.compr_level_set;
  mem_level_set = s_process.mem_level_set;
  strategy_set = s_process.strategy_set;
  filter_set = s_process.filter_set;
  if ((s_process.num_iterations == 1) && (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
  {
    s_process.best_idat_size = 0;
    s_process.best_compr_level = opng_bitset_find_first(compr_level_set);
    s_process.best_mem_level = opng_bitset_find_first(mem_level_set);
    s_process.best_strategy = opng_bitset_find_first(strategy_set);
    s_process.best_filter = opng_bitset_find_first(filter_set);
    return;
  }
  s_process.best_idat_size = k_idat_size_max + 1;
  s_process.best_compr_level = -1;
  s_process.best_mem_level = -1;
  s_process.best_strategy = -1;
  s_process.best_filter = -1;
  usr_printf("\nTrying:\n");
  line_reused = 0;
  counter = 0;
  for (filter = 0; filter <= 5; filter += 1)
  {
    if (!((filter_set & (1U << filter)) != 0))
    {
      continue;
    }
    for (strategy = 0; strategy <= 3; strategy += 1)
    {
      if (!((strategy_set & (1U << strategy)) != 0))
      {
        continue;
      }
      if (strategy == 2)
      {
        compr_level_set = 0;
        compr_level_set |= 1U << 1;
      }
      else
        if (strategy == 3)
      {
        compr_level_set = 0;
        compr_level_set |= 1U << 9;
      }
      else
      {
        compr_level_set = s_process.compr_level_set;
      }
      for (compr_level = 9; compr_level >= 1; compr_level -= 1)
      {
        if (!((compr_level_set & (1U << compr_level)) != 0))
        {
          continue;
        }
        for (mem_level = 9; mem_level >= 1; mem_level -= 1)
        {
          if (!((mem_level_set & (1U << mem_level)) != 0))
          {
            continue;
          }
          usr_printf("  zc = %d  zm = %d  zs = %d  f = %d", compr_level, mem_level, strategy, filter);
          usr_progress(counter, s_process.num_iterations);
          counter += 1;
          opng_write_file(0, compr_level, mem_level, strategy, filter);
          if (s_process.out_idat_size > k_idat_size_max)
          {
            if (s_options.verbose)
            {
              usr_printf("\t\tIDAT too big\n");
              line_reused = 0;
            }
            else
            {
              usr_print_cntrl('\r');
              line_reused = 1;
            }
            continue;
          }
          usr_printf("\t\tIDAT size = %lu\n", s_process.out_idat_size);
          line_reused = 0;
          if (s_process.best_idat_size < s_process.out_idat_size)
          {
            continue;
          }
          if ((s_process.best_idat_size == s_process.out_idat_size) && ((s_process.best_strategy == 2) || (s_process.best_strategy == 3)))
          {
            continue;
          }
          s_process.best_compr_level = compr_level;
          s_process.best_mem_level = mem_level;
          s_process.best_strategy = strategy;
          s_process.best_filter = filter;
          s_process.best_idat_size = s_process.out_idat_size;
          if (!s_options.full)
          {
            s_process.max_idat_size = s_process.out_idat_size;
          }
        }

      }

    }

  }

  if (line_reused)
  {
    usr_print_cntrl(-31);
  }
  {
    if (!(counter == s_process.num_iterations))
    {
      usr_panic("Inconsistent iteration counter");
    }
  }
  ;
  usr_progress(counter, s_process.num_iterations);
}

static void opng_finish_iterations(void)
{
  if ((s_process.best_idat_size + s_process.out_plte_trns_size) < (s_process.in_idat_size + s_process.in_plte_trns_size))
  {
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  }
  if (s_process.status & OUTPUT_NEEDS_NEW_IDAT)
  {
    if (s_process.best_idat_size <= k_idat_size_max)
    {
      usr_printf("\nSelecting parameters:\n");
      usr_printf("  zc = %d  zm = %d  zs = %d  f = %d", s_process.best_compr_level, s_process.best_mem_level, s_process.best_strategy, s_process.best_filter);
      if (s_process.best_idat_size > 0)
      {
        usr_printf("\t\tIDAT size = %lu", s_process.best_idat_size);
      }
      usr_printf("\n");
    }
    else
    {
      usr_printf("  zc = *  zm = *  zs = *  f = *\t\tIDAT size > %s\n", k_idat_size_max_string);
    }
  }
}

static void opng_optimize_impl(const char *infile_name)
{
  static FILE *infile;
  unsigned int infile_idx = 0;
  static FILE *outfile;
  unsigned int outfile_idx = 0;
  static const char *infile_name_local;
  unsigned int infile_name_local_idx = 0;
  static const char *outfile_name;
  unsigned int outfile_name_idx = 0;
  static const char *bakfile_name;
  unsigned int bakfile_name_idx = 0;
  static int new_outfile;
  static int has_backup;
  char name_buf[1024];
  char tmp_buf[1024];
  volatile opng_status_t status;
  memset(&s_process, 0, sizeof(s_process));
  if (s_options.force)
  {
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  }
  infile_name_local_idx = infile_name;
  if ((infile_idx = fopen(infile_name_local, "rb")) == 0)
  {
    opng_throw_error("Can't open the input file");
  }
  status = OPNG_STATUS_OK;
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        opng_read_file(infile);
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    {
      if (!(status != OPNG_STATUS_OK))
      {
        usr_panic("opng_read_file should throw errors only");
      }
    }
    ;
  }
  fclose(infile);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  if (s_process.status & INPUT_HAS_ERRORS)
  {
    usr_printf("Recoverable errors found in input.");
    if (s_options.fix)
    {
      usr_printf(" Fixing...\n");
      s_process.status |= OUTPUT_NEEDS_NEW_FILE;
    }
    else
    {
      usr_printf(" Rerun OptiPNG with -fix enabled.\n");
      opng_throw_error("Previous error(s) not fixed");
    }
  }
  if (s_process.status & INPUT_HAS_JUNK)
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
  }
  if (!(s_process.status & INPUT_HAS_PNG_SIGNATURE))
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
  }
  if (s_process.status & INPUT_HAS_PNG_DATASTREAM)
  {
    if (s_options.nz && (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
    {
      usr_printf("IDAT recoding is necessary, but is disabled by the user.\n");
      opng_throw_error("Can't continue");
    }
  }
  else
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  if (s_process.status & INPUT_HAS_DIGITAL_SIGNATURE)
  {
    usr_printf("Digital signature found in input.");
    if (s_options.force)
    {
      usr_printf(" Erasing...\n");
      s_process.status |= OUTPUT_NEEDS_NEW_FILE;
    }
    else
    {
      usr_printf(" Rerun OptiPNG with -force enabled.\n");
      opng_throw_error("Can't optimize digitally-signed files");
    }
  }
  if (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)
  {
    if ((!s_options.snip) && (!(s_process.status & INPUT_IS_PNG_FILE)))
    {
      usr_printf("Conversion to PNG requires snipping. Rerun OptiPNG with -snip enabled.\n");
      opng_throw_error("Incompatible input format");
    }
  }
  if (s_options.snip && (s_process.status & INPUT_HAS_APNG))
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
  }
  if (s_process.status & INPUT_HAS_STRIPPED_DATA)
  {
    usr_printf("Stripping metadata...\n");
  }
  outfile_name_idx = 0;
  if (!(s_process.status & INPUT_IS_PNG_FILE))
  {
    if (opng_path_replace_ext(name_buf, sizeof(name_buf), infile_name_local, ".png") == 0)
    {
      opng_throw_error("Can't create the output file (name too long)");
    }
    outfile_name_idx = name_buf;
  }
  if (s_options.out_name != 0)
  {
    outfile_name_idx = s_options.out_name;
  }
  if (s_options.dir_name != 0)
  {
    const char *tmp_name;
    unsigned int tmp_name_idx = 0;
    if ((&outfile_name[outfile_name_idx]) != 0)
    {
      strcpy(tmp_buf, outfile_name);
      tmp_name_idx = tmp_buf;
    }
    else
      tmp_name_idx = &infile_name_local[infile_name_local_idx];
    if (opng_path_replace_dir(name_buf, sizeof(name_buf), tmp_name, s_options.dir_name) == 0)
    {
      opng_throw_error("Can't create the output file (name too long)");
    }
    outfile_name_idx = name_buf;
  }
  if ((&outfile_name[outfile_name_idx]) == 0)
  {
    outfile_name_idx = &infile_name_local[infile_name_local_idx];
    new_outfile = 0;
  }
  else
  {
    int test_eq = opng_os_test_file_equiv(infile_name_local, outfile_name);
    if (test_eq >= 0)
    {
      new_outfile = test_eq == 0;
    }
    else
    {
      new_outfile = strcmp(infile_name_local, outfile_name) != 0;
    }
  }
  bakfile_name_idx = tmp_buf;
  if (new_outfile)
  {
    if (opng_path_make_backup(tmp_buf, sizeof(tmp_buf), outfile_name) == 0)
    {
      bakfile_name_idx = 0;
    }
  }
  else
  {
    if (opng_path_make_backup(tmp_buf, sizeof(tmp_buf), infile_name_local) == 0)
    {
      bakfile_name_idx = 0;
    }
  }
  if ((&bakfile_name[bakfile_name_idx]) == 0)
  {
    opng_throw_error("Can't create backup file (name too long)");
  }
  if ((!s_options.simulate) && (opng_os_test_file_access(outfile_name, "e") == 0))
  {
    if (((!s_options.backup) && (!s_options.clobber)) && new_outfile)
    {
      usr_printf("The output file exists. Rerun OptiPNG with -backup enabled.\n");
      opng_throw_error("Can't overwrite the output file");
    }
    if ((opng_os_test_file_access(outfile_name, "fw") != 0) || ((!s_options.clobber) && (opng_os_test_file_access(bakfile_name, "e") == 0)))
    {
      usr_printf("A backup file already exists. Rerun OptiPNG with -clobber enabled.\n");
      opng_throw_error("Can't back up the existing output file");
    }
  }
  if (s_process.status & INPUT_HAS_PNG_DATASTREAM)
  {
    usr_printf("Input IDAT size = %lu bytes\n", s_process.in_idat_size);
  }
  usr_printf("Input file size = %lu bytes\n", s_process.in_file_size);
  if ((!s_options.nz) || (s_process.status & OUTPUT_NEEDS_NEW_IDAT))
  {
    opng_init_iterations();
    opng_iterate();
    opng_finish_iterations();
  }
  if (s_process.status & OUTPUT_NEEDS_NEW_IDAT)
  {
    s_process.status |= OUTPUT_NEEDS_NEW_FILE;
    opng_check_idat_size(s_process.best_idat_size);
  }
  if (!(s_process.status & OUTPUT_NEEDS_NEW_FILE))
  {
    usr_printf("\n%s is already optimized.\n", infile_name_local);
    if (!new_outfile)
    {
      return;
    }
  }
  if (s_options.simulate)
  {
    usr_printf("\nNo output: simulation mode.\n");
    return;
  }
  if (new_outfile)
  {
    usr_printf("\nOutput file: %s\n", outfile_name);
    if (s_options.dir_name != 0)
    {
      opng_os_create_dir(s_options.dir_name);
    }
    has_backup = 0;
    if (opng_os_test_file_access(outfile_name, "e") == 0)
    {
      if (opng_os_rename(outfile_name, bakfile_name, s_options.clobber) != 0)
      {
        opng_throw_error("Can't back up the output file");
      }
      has_backup = 1;
    }
  }
  else
  {
    if (opng_os_rename(infile_name_local, bakfile_name, s_options.clobber) != 0)
    {
      opng_throw_error("Can't back up the input file");
    }
    has_backup = 1;
  }
  outfile_idx = fopen(outfile_name, "wb");
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        if ((&outfile[outfile_idx]) == 0)
        {
          opng_throw_error("Can't open the output file");
        }
        if (s_process.status & OUTPUT_NEEDS_NEW_IDAT)
        {
          opng_write_file(outfile, s_process.best_compr_level, s_process.best_mem_level, s_process.best_strategy, s_process.best_filter);
        }
        else
        {
          infile_idx = fopen((new_outfile) ? (infile_name_local) : (bakfile_name), "rb");
          if ((&infile[infile_idx]) == 0)
          {
            opng_throw_error("Can't reopen the input file");
          }
          {
            jmp_buf *exception__prev[1];
            jmp_buf exception__env;
            exception__prev[0] = the_exception_context->penv;
            the_exception_context->penv = &exception__env;
            if (setjmp(exception__env) == 0)
            {
              do
              {
                if ((s_process.in_datastream_offset > 0) && (opng_fseeko(infile, s_process.in_datastream_offset, 0) != 0))
                {
                  opng_throw_error("Can't reposition the input file");
                }
                s_process.best_idat_size = s_process.in_idat_size;
                opng_copy_file(infile, outfile);
              }
              while (the_exception_context->caught = 0, the_exception_context->caught);
            }
            else
            {
              the_exception_context->caught = 1;
            }
            the_exception_context->penv = exception__prev[0];
          }
          if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
          {
          }
          else
          {
            {
              if (!(status != OPNG_STATUS_OK))
              {
                usr_panic("opng_copy_file should throw errors only");
              }
            }
            ;
          }
          fclose(infile);
          if (status != OPNG_STATUS_OK)
          {
            for (;; longjmp(*the_exception_context->penv, 1))
            {
              the_exception_context->v.etmp = status;
            }

          }
        }
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    if ((&outfile[outfile_idx]) != 0)
    {
      fclose(outfile);
    }
    if (has_backup)
    {
      if (opng_os_rename(bakfile_name, (new_outfile) ? (outfile_name) : (infile_name_local), 1) != 0)
      {
        opng_print_warning("Can't recover the original file from backup");
      }
    }
    else
    {
      {
        if (!new_outfile)
        {
          usr_panic("Overwrote input with no temporary backup");
        }
      }
      ;
      if (opng_os_unlink(outfile_name) != 0)
      {
        opng_print_warning("Can't remove the broken output file");
      }
    }
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  fclose(outfile);
  if (s_options.preserve)
  {
    opng_os_copy_file_attr((new_outfile) ? (infile_name_local) : (bakfile_name), outfile_name);
  }
  if ((!s_options.backup) && (!new_outfile))
  {
    if (opng_os_unlink(bakfile_name) != 0)
    {
      opng_print_warning("Can't remove the backup file");
    }
  }
  usr_printf("\nOutput IDAT size = %lu bytes", s_process.out_idat_size);
  if (s_process.status & INPUT_HAS_PNG_DATASTREAM)
  {
    usr_printf(" (");
    opng_print_fsize_difference(s_process.in_idat_size, s_process.out_idat_size, 0);
    usr_printf(")");
  }
  usr_printf("\nOutput file size = %lu bytes (", s_process.out_file_size);
  opng_print_fsize_difference(s_process.in_file_size, s_process.out_file_size, 1);
  usr_printf(")\n");
}

int opng_initialize(const struct opng_options *init_options, const struct opng_ui *init_ui)
{
  usr_printf = init_ui->printf_fn;
  usr_print_cntrl = init_ui->print_cntrl_fn;
  usr_progress = init_ui->progress_fn;
  usr_panic = init_ui->panic_fn;
  if ((((usr_printf == 0) || (usr_print_cntrl == 0)) || (usr_progress == 0)) || (usr_panic == 0))
  {
    return -1;
  }
  s_options = *init_options;
  if (s_options.optim_level == 0)
  {
    s_options.nb = (s_options.nc = (s_options.np = 1));
    s_options.nz = 1;
  }
  memset(&s_summary, 0, sizeof(s_summary));
  s_engine.started = 1;
  return 0;
}

int opng_optimize(const char *infile_name)
{
  opng_status_t status;
  volatile int result;
  {
    if (!s_engine.started)
    {
      usr_panic("The OptiPNG engine is not running");
    }
  }
  ;
  usr_printf("** Processing: %s\n", infile_name);
  s_summary.file_count += 1;
  opng_clear_image_info();
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        opng_optimize_impl(infile_name);
        if (s_process.status & INPUT_HAS_ERRORS)
        {
          s_summary.err_count += 1;
          s_summary.fix_count += 1;
        }
        if (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)
        {
          if (s_options.snip)
          {
            s_summary.snip_count += 1;
          }
        }
        result = 0;
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    {
      if (!(status != OPNG_STATUS_OK))
      {
        usr_panic("opng_optimize_impl should throw errors only");
      }
    }
    ;
    s_summary.err_count += 1;
    result = -1;
  }
  opng_destroy_image_info();
  usr_printf("\n");
  return result;
}

int opng_finalize(void)
{
  if ((s_options.verbose || (s_summary.snip_count > 0)) || (s_summary.err_count > 0))
  {
    usr_printf("** Status report\n");
    usr_printf("%u file(s) have been processed.\n", s_summary.file_count);
    if (s_summary.snip_count > 0)
    {
      usr_printf("%u multi-image file(s) have been snipped.\n", s_summary.snip_count);
    }
    if (s_summary.err_count > 0)
    {
      usr_printf("%u error(s) have been encountered.\n", s_summary.err_count);
      if (s_summary.fix_count > 0)
      {
        usr_printf("%u erroneous file(s) have been fixed.\n", s_summary.fix_count);
      }
    }
  }
  s_engine.started = 0;
  return 0;
}

void helper_opng_print_image_info_1(int * const printed_ref)
{
  int printed = *printed_ref;
  if (printed)
  {
    usr_printf(", ");
  }
  printed = 1;
  if (s_image.color_type & 1)
  {
    if (s_image.num_palette == 1)
    {
      usr_printf("1 color");
    }
    else
      usr_printf("%d colors", s_image.num_palette);
    if (s_image.num_trans > 0)
    {
      usr_printf(" (%d transparent)", s_image.num_trans);
    }
    usr_printf(" in palette");
  }
  else
  {
    usr_printf((s_image.color_type & 2) ? ("RGB") : ("grayscale"));
    if (s_image.color_type & 4)
    {
      usr_printf("+alpha");
    }
    else
      if (s_image.trans_color_ptr != 0)
    {
      usr_printf("+transparency");
    }
  }
  *printed_ref = printed;
}

void helper_opng_read_data_1(png_structp png_ptr, size_t length, FILE * const stream, int io_state_loc)
{
  {
    if (!(length == 8))
    {
      usr_panic("PNG I/O must start with the first 8 bytes");
    }
  }
  ;
  s_process.in_datastream_offset = opng_ftello(stream) - 8;
  s_process.status |= INPUT_HAS_PNG_DATASTREAM;
  if (io_state_loc == 0x0010)
  {
    s_process.status |= INPUT_HAS_PNG_SIGNATURE;
  }
  if (s_process.in_datastream_offset == 0)
  {
    s_process.status |= INPUT_IS_PNG_FILE;
  }
  else
    if (s_process.in_datastream_offset < 0)
  {
    png_error(png_ptr, "Can't get the file-position indicator in input file");
  }
  s_process.in_file_size = (opng_fsize_t) s_process.in_datastream_offset;
}

void helper_opng_read_data_2(png_bytep * const chunk_sig_ref, png_structp png_ptr, png_bytep data, size_t length)
{
  png_bytep chunk_sig = *chunk_sig_ref;
  {
    if (!(length == 8))
    {
      usr_panic("Reading chunk header, expecting 8 bytes");
    }
  }
  ;
  chunk_sig = data + 4;
  if (memcmp(chunk_sig, k_sig_IDAT, 4) == 0)
  {
    {
      if (!(png_ptr == s_read_ptr))
      {
        usr_panic("Incorrect I/O handler setup");
      }
    }
    ;
    if (png_get_rows(s_read_ptr, s_read_info_ptr) == 0)
    {
      {
        if (!(s_process.in_idat_size == 0))
        {
          usr_panic("Found IDAT with no rows");
        }
      }
      ;
      if (png_get_image_height(s_read_ptr, s_read_info_ptr) == 0)
      {
        return;
      }
      {
        if (!(pngx_malloc_rows(s_read_ptr, s_read_info_ptr, 0) != 0))
        {
          usr_panic("Failed allocation of image rows; unsafe libpng allocator");
        }
      }
      ;
      png_data_freer(s_read_ptr, s_read_info_ptr, 2, 0x0040U);
    }
    else
    {
      s_process.status |= INPUT_HAS_JUNK;
    }
    s_process.in_idat_size += (((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)));
  }
  else
    if ((memcmp(chunk_sig, k_sig_PLTE, 4) == 0) || (memcmp(chunk_sig, k_sig_tRNS, 4) == 0))
  {
    s_process.in_plte_trns_size += ((((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)))) + 12;
  }
  else
    opng_handle_chunk(png_ptr, chunk_sig);
  *chunk_sig_ref = chunk_sig;
}

void helper_opng_write_data_1(static int * const allow_crt_chunk_ref, static int * const crt_chunk_is_idat_ref, png_bytep * const chunk_sig_ref, png_bytep data, size_t length, FILE * const stream)
{
  static int allow_crt_chunk = *allow_crt_chunk_ref;
  static int crt_chunk_is_idat = *crt_chunk_is_idat_ref;
  png_bytep chunk_sig = *chunk_sig_ref;
  {
    if (!(length == 8))
    {
      usr_panic("Writing chunk header, expecting 8 bytes");
    }
  }
  ;
  chunk_sig = data + 4;
  allow_crt_chunk = opng_allow_chunk(chunk_sig);
  if (memcmp(chunk_sig, k_sig_IDAT, 4) == 0)
  {
    crt_chunk_is_idat = 1;
    s_process.out_idat_size += (((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)));
    if (stream == 0)
    {
      if (s_process.out_idat_size > s_process.max_idat_size)
      {
        for (;; longjmp(*the_exception_context->penv, 1))
        {
          the_exception_context->v.etmp = OPNG_STATUS_OK;
        }

      }
    }
  }
  else
  {
    crt_chunk_is_idat = 0;
    if ((memcmp(chunk_sig, k_sig_PLTE, 4) == 0) || (memcmp(chunk_sig, k_sig_tRNS, 4) == 0))
    {
      s_process.out_plte_trns_size += ((((((png_uint_32) (*data)) << 24) + (((png_uint_32) (*(data + 1))) << 16)) + (((png_uint_32) (*(data + 2))) << 8)) + ((png_uint_32) (*(data + 3)))) + 12;
    }
  }
  *allow_crt_chunk_ref = allow_crt_chunk;
  *crt_chunk_is_idat_ref = crt_chunk_is_idat;
  *chunk_sig_ref = chunk_sig;
}

void helper_opng_write_data_2(static opng_foffset_t * const crt_idat_offset_ref, static opng_fsize_t * const crt_idat_size_ref, static png_uint_32 * const crt_idat_crc_ref, int * const io_state_ref, png_structp png_ptr, png_bytep data, size_t length, static int crt_chunk_is_idat, FILE * const stream, png_byte buf[4])
{
  static opng_foffset_t crt_idat_offset = *crt_idat_offset_ref;
  static opng_fsize_t crt_idat_size = *crt_idat_size_ref;
  static png_uint_32 crt_idat_crc = *crt_idat_crc_ref;
  int io_state = *io_state_ref;
  if (crt_chunk_is_idat)
  {
    if (crt_idat_offset == 0)
    {
      crt_idat_offset = opng_ftello(stream);
      if (s_process.best_idat_size > 0)
      {
        crt_idat_size = s_process.best_idat_size;
      }
      else
      {
        crt_idat_size = length;
      }
      png_save_uint_32(data, (png_uint_32) crt_idat_size);
      crt_idat_crc = crc32(0, k_sig_IDAT, 4);
    }
    else
    {
      return;
    }
  }
  else
  {
    helper_helper_opng_write_data_2_1(&crt_idat_offset, &io_state, png_ptr, stream, buf, crt_idat_size, crt_idat_crc);
  }
  break;
  *crt_idat_offset_ref = crt_idat_offset;
  *crt_idat_size_ref = crt_idat_size;
  *crt_idat_crc_ref = crt_idat_crc;
  *io_state_ref = io_state;
}

void helper_opng_read_file_1(unsigned int * const fmt_name_idx_ref, int * const num_img_ref, FILE * const infile, const char * const fmt_name)
{
  unsigned int fmt_name_idx = *fmt_name_idx_ref;
  int num_img = *num_img_ref;
  jmp_buf *exception__prev[1];
  jmp_buf exception__env;
  exception__prev[0] = the_exception_context->penv;
  the_exception_context->penv = &exception__env;
  if (setjmp(exception__env) == 0)
  {
    helper_helper_opng_read_file_1_1(&fmt_name_idx, &num_img, infile, fmt_name);
  }
  else
  {
    the_exception_context->caught = 1;
  }
  the_exception_context->penv = exception__prev[0];
  *fmt_name_idx_ref = fmt_name_idx;
  *num_img_ref = num_img;
}

void helper_opng_read_file_2(png_uint_32 * const reductions_ref, volatile opng_status_t * const status_ref, const char * const fmt_name)
{
  png_uint_32 reductions = *reductions_ref;
  volatile opng_status_t status = *status_ref;
  jmp_buf *exception__prev[1];
  jmp_buf exception__env;
  exception__prev[0] = the_exception_context->penv;
  the_exception_context->penv = &exception__env;
  if (setjmp(exception__env) == 0)
  {
    helper_helper_opng_read_file_2_1(&reductions, &status, fmt_name);
  }
  else
  {
    the_exception_context->caught = 1;
  }
  the_exception_context->penv = exception__prev[0];
  *reductions_ref = reductions;
  *status_ref = status;
}

void helper_opng_write_file_1(FILE * const outfile, int compression_level, int memory_level, int compression_strategy, int filter)
{
  jmp_buf *exception__prev[1];
  jmp_buf exception__env;
  exception__prev[0] = the_exception_context->penv;
  the_exception_context->penv = &exception__env;
  if (setjmp(exception__env) == 0)
  {
    do
    {
      s_write_ptr = png_create_write_struct("1.6.40", 0, opng_error, opng_warning);
      s_write_info_ptr = png_create_info_struct(s_write_ptr);
      if (s_write_info_ptr == 0)
      {
        opng_throw_error("Can't create image encoder");
      }
      png_set_compression_level(s_write_ptr, compression_level);
      png_set_compression_mem_level(s_write_ptr, memory_level);
      png_set_compression_strategy(s_write_ptr, compression_strategy);
      png_set_filter(s_write_ptr, 0, k_filter_table[filter]);
      if ((compression_strategy != 2) && (compression_strategy != 3))
      {
        if (s_options.window_bits > 0)
        {
          png_set_compression_window_bits(s_write_ptr, s_options.window_bits);
        }
      }
      else
      {
        png_set_compression_window_bits(s_write_ptr, 9);
      }
      png_set_keep_unknown_chunks(s_write_ptr, 3, 0, 0);
      png_set_user_limits(s_write_ptr, (png_uint_32) 0x7fffffffL, (png_uint_32) 0x7fffffffL);
      opng_store_image_info(s_write_ptr, s_write_info_ptr, outfile != 0);
      opng_init_write_data();
      png_set_write_fn(s_write_ptr, outfile, opng_write_data, 0);
      png_write_png(s_write_ptr, s_write_info_ptr, 0, 0);
    }
    while (the_exception_context->caught = 0, the_exception_context->caught);
  }
  else
  {
    the_exception_context->caught = 1;
  }
  the_exception_context->penv = exception__prev[0];
}

void helper_opng_copy_file_1(volatile png_bytep * const buf_ref, png_uint_32 * const buf_size_ref, png_uint_32 * const length_ref, FILE * const infile, const png_uint_32 buf_size_incr, png_byte chunk_hdr[8])
{
  volatile png_bytep buf = *buf_ref;
  png_uint_32 buf_size = *buf_size_ref;
  png_uint_32 length = *length_ref;
  jmp_buf *exception__prev[1];
  jmp_buf exception__env;
  exception__prev[0] = the_exception_context->penv;
  the_exception_context->penv = &exception__env;
  if (setjmp(exception__env) == 0)
  {
    helper_helper_opng_copy_file_1_1(&buf, &buf_size, &length, infile, buf_size_incr, chunk_hdr);
  }
  else
  {
    the_exception_context->caught = 1;
  }
  the_exception_context->penv = exception__prev[0];
  *buf_ref = buf;
  *buf_size_ref = buf_size;
  *length_ref = length;
}

void helper_opng_iterate_1(opng_bitset_t * const compr_level_set_ref, int * const compr_level_ref, int * const mem_level_ref, int * const strategy_ref, int * const counter_ref, int * const line_reused_ref, opng_bitset_t mem_level_set, opng_bitset_t strategy_set, opng_bitset_t filter_set, int filter)
{
  opng_bitset_t compr_level_set = *compr_level_set_ref;
  int compr_level = *compr_level_ref;
  int mem_level = *mem_level_ref;
  int strategy = *strategy_ref;
  int counter = *counter_ref;
  int line_reused = *line_reused_ref;
  if (!((filter_set & (1U << filter)) != 0))
  {
    continue;
  }
  for (strategy = 0; strategy <= 3; strategy += 1)
  {
    helper_helper_opng_iterate_1_1(&compr_level_set, &compr_level, &mem_level, &counter, &line_reused, mem_level_set, strategy_set, filter, strategy);
  }

  *compr_level_set_ref = compr_level_set;
  *compr_level_ref = compr_level;
  *mem_level_ref = mem_level;
  *strategy_ref = strategy;
  *counter_ref = counter;
  *line_reused_ref = line_reused;
}

void helper_opng_optimize_impl_1(static FILE * const outfile, unsigned int outfile_idx, static const char * const infile_name_local, static const char * const outfile_name, static const char * const bakfile_name, static int new_outfile, static int has_backup, volatile opng_status_t status)
{
  if ((&outfile[outfile_idx]) != 0)
  {
    fclose(outfile);
  }
  if (has_backup)
  {
    if (opng_os_rename(bakfile_name, (new_outfile) ? (outfile_name) : (infile_name_local), 1) != 0)
    {
      opng_print_warning("Can't recover the original file from backup");
    }
  }
  else
  {
    {
      if (!new_outfile)
      {
        usr_panic("Overwrote input with no temporary backup");
      }
    }
    ;
    if (opng_os_unlink(outfile_name) != 0)
    {
      opng_print_warning("Can't remove the broken output file");
    }
  }
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = status;
  }

}

void helper_opng_optimize_impl_2(unsigned int * const infile_idx_ref, volatile opng_status_t * const status_ref, static FILE * const infile, static FILE * const outfile, unsigned int outfile_idx, static const char * const infile_name_local, static const char * const bakfile_name, static int new_outfile)
{
  unsigned int infile_idx = *infile_idx_ref;
  volatile opng_status_t status = *status_ref;
  jmp_buf *exception__prev[1];
  jmp_buf exception__env;
  exception__prev[0] = the_exception_context->penv;
  the_exception_context->penv = &exception__env;
  if (setjmp(exception__env) == 0)
  {
    helper_helper_opng_optimize_impl_2_1(&infile_idx, &status, infile, outfile, outfile_idx, infile_name_local, bakfile_name, new_outfile);
  }
  else
  {
    the_exception_context->caught = 1;
  }
  the_exception_context->penv = exception__prev[0];
  *infile_idx_ref = infile_idx;
  *status_ref = status;
}

void helper_opng_optimize_1(volatile int * const result_ref, const char * const infile_name)
{
  volatile int result = *result_ref;
  jmp_buf *exception__prev[1];
  jmp_buf exception__env;
  exception__prev[0] = the_exception_context->penv;
  the_exception_context->penv = &exception__env;
  if (setjmp(exception__env) == 0)
  {
    do
    {
      opng_optimize_impl(infile_name);
      if (s_process.status & INPUT_HAS_ERRORS)
      {
        s_summary.err_count += 1;
        s_summary.fix_count += 1;
      }
      if (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)
      {
        if (s_options.snip)
        {
          s_summary.snip_count += 1;
        }
      }
      result = 0;
    }
    while (the_exception_context->caught = 0, the_exception_context->caught);
  }
  else
  {
    the_exception_context->caught = 1;
  }
  the_exception_context->penv = exception__prev[0];
  *result_ref = result;
}

void helper_helper_opng_write_data_2_1(static opng_foffset_t * const crt_idat_offset_ref, int * const io_state_ref, png_structp png_ptr, FILE * const stream, png_byte buf[4], static opng_fsize_t crt_idat_size, static png_uint_32 crt_idat_crc)
{
  static opng_foffset_t crt_idat_offset = *crt_idat_offset_ref;
  int io_state = *io_state_ref;
  if (crt_idat_offset != 0)
  {
    png_save_uint_32(buf, crt_idat_crc);
    if (fwrite(buf, 1, 4, stream) != 4)
    {
      io_state = 0;
    }
    s_process.out_file_size += 4;
    if (s_process.out_idat_size != crt_idat_size)
    {
      {
        if (!(s_process.best_idat_size == 0))
        {
          usr_panic("Wrong guess of the output IDAT size");
        }
      }
      ;
      opng_check_idat_size(s_process.out_idat_size);
      png_save_uint_32(buf, (png_uint_32) s_process.out_idat_size);
      if (opng_fwriteo(stream, crt_idat_offset, 0, buf, 4) != 4)
      {
        io_state = 0;
      }
    }
    if (io_state == 0)
    {
      png_error(png_ptr, "Can't finalize IDAT");
    }
    crt_idat_offset = 0;
  }
  *crt_idat_offset_ref = crt_idat_offset;
  *io_state_ref = io_state;
}

void helper_helper_opng_read_file_1_1(unsigned int * const fmt_name_idx_ref, int * const num_img_ref, FILE * const infile, const char * const fmt_name)
{
  unsigned int fmt_name_idx = *fmt_name_idx_ref;
  int num_img = *num_img_ref;
  do
  {
    s_read_ptr = png_create_read_struct("1.6.40", 0, opng_error, opng_warning);
    s_read_info_ptr = png_create_info_struct(s_read_ptr);
    if (s_read_info_ptr == 0)
    {
      opng_throw_error("Can't create image decoder");
    }
    png_set_keep_unknown_chunks(s_read_ptr, 3, 0, 0);
    png_set_user_limits(s_read_ptr, (png_uint_32) 0x7fffffffL, (png_uint_32) 0x7fffffffL);
    opng_init_read_data();
    png_set_read_fn(s_read_ptr, infile, opng_read_data);
    fmt_name_idx = 0;
    num_img = pngx_read_image(s_read_ptr, s_read_info_ptr, &(&fmt_name[fmt_name_idx]), 0);
    if (num_img <= 0)
    {
      opng_throw_error("Unrecognized image file format");
    }
    if (num_img > 1)
    {
      s_process.status |= INPUT_HAS_MULTIPLE_IMAGES;
    }
    if ((s_process.status & INPUT_IS_PNG_FILE) && (s_process.status & INPUT_HAS_MULTIPLE_IMAGES))
    {
      fmt_name_idx = (s_process.status & INPUT_HAS_PNG_SIGNATURE) ? ("APNG") : ("APNG datastream");
    }
    {
      if (!((&fmt_name[fmt_name_idx]) != 0))
      {
        usr_panic("No format name from pngxtern");
      }
    }
    ;
    if (s_process.in_file_size == 0)
    {
      if (opng_fgetsize(infile, &s_process.in_file_size) < 0)
      {
        opng_print_warning("Can't get the correct file size");
        s_process.in_file_size = 0;
      }
    }
  }
  while (the_exception_context->caught = 0, the_exception_context->caught);
  *fmt_name_idx_ref = fmt_name_idx;
  *num_img_ref = num_img;
}

void helper_helper_opng_read_file_2_1(png_uint_32 * const reductions_ref, volatile opng_status_t * const status_ref, const char * const fmt_name)
{
  png_uint_32 reductions = *reductions_ref;
  volatile opng_status_t status = *status_ref;
  do
  {
    helper_helper_helper_opng_read_file_2_1_1(&reductions, &status, fmt_name);
  }
  while (the_exception_context->caught = 0, the_exception_context->caught);
  *reductions_ref = reductions;
  *status_ref = status;
}

void helper_helper_opng_copy_file_1_1(volatile png_bytep * const buf_ref, png_uint_32 * const buf_size_ref, png_uint_32 * const length_ref, FILE * const infile, const png_uint_32 buf_size_incr, png_byte chunk_hdr[8])
{
  volatile png_bytep buf = *buf_ref;
  png_uint_32 buf_size = *buf_size_ref;
  png_uint_32 length = *length_ref;
  do
  {
    buf = 0;
    buf_size = 0;
    png_write_sig(s_write_ptr);
    do
    {
      if (fread(chunk_hdr, 8, 1, infile) != 1)
      {
        opng_throw_error("Read error");
      }
      length = (((((png_uint_32) (*chunk_hdr)) << 24) + (((png_uint_32) (*(chunk_hdr + 1))) << 16)) + (((png_uint_32) (*(chunk_hdr + 2))) << 8)) + ((png_uint_32) (*(chunk_hdr + 3)));
      if (length > ((png_uint_32) 0x7fffffffL))
      {
        if ((buf == 0) && (length == 0x89504e47UL))
        {
          continue;
        }
        opng_throw_error("Data error");
      }
      if ((length + 4) > buf_size)
      {
        png_free(s_write_ptr, buf);
        buf_size = (((length + 4) + (buf_size_incr - 1)) / buf_size_incr) * buf_size_incr;
        buf = (png_bytep) png_malloc(s_write_ptr, buf_size);
      }
      if (fread(buf, length + 4, 1, infile) != 1)
      {
        opng_throw_error("Read error");
      }
      png_write_chunk(s_write_ptr, chunk_hdr + 4, buf, length);
    }
    while (memcmp(chunk_hdr + 4, k_sig_IEND, 4) != 0);
  }
  while (the_exception_context->caught = 0, the_exception_context->caught);
  *buf_ref = buf;
  *buf_size_ref = buf_size;
  *length_ref = length;
}

void helper_helper_opng_iterate_1_1(opng_bitset_t * const compr_level_set_ref, int * const compr_level_ref, int * const mem_level_ref, int * const counter_ref, int * const line_reused_ref, opng_bitset_t mem_level_set, opng_bitset_t strategy_set, int filter, int strategy)
{
  opng_bitset_t compr_level_set = *compr_level_set_ref;
  int compr_level = *compr_level_ref;
  int mem_level = *mem_level_ref;
  int counter = *counter_ref;
  int line_reused = *line_reused_ref;
  if (!((strategy_set & (1U << strategy)) != 0))
  {
    continue;
  }
  if (strategy == 2)
  {
    compr_level_set = 0;
    compr_level_set |= 1U << 1;
  }
  else
    if (strategy == 3)
  {
    compr_level_set = 0;
    compr_level_set |= 1U << 9;
  }
  else
  {
    compr_level_set = s_process.compr_level_set;
  }
  for (compr_level = 9; compr_level >= 1; compr_level -= 1)
  {
    helper_helper_helper_opng_iterate_1_1_1(&mem_level, &counter, &line_reused, mem_level_set, filter, strategy, compr_level_set, compr_level);
  }

  *compr_level_set_ref = compr_level_set;
  *compr_level_ref = compr_level;
  *mem_level_ref = mem_level;
  *counter_ref = counter;
  *line_reused_ref = line_reused;
}

void helper_helper_opng_optimize_impl_2_1(unsigned int * const infile_idx_ref, volatile opng_status_t * const status_ref, static FILE * const infile, static FILE * const outfile, unsigned int outfile_idx, static const char * const infile_name_local, static const char * const bakfile_name, static int new_outfile)
{
  unsigned int infile_idx = *infile_idx_ref;
  volatile opng_status_t status = *status_ref;
  do
  {
    helper_helper_helper_opng_optimize_impl_2_1_1(&infile_idx, &status, infile, outfile, outfile_idx, infile_name_local, bakfile_name, new_outfile);
  }
  while (the_exception_context->caught = 0, the_exception_context->caught);
  *infile_idx_ref = infile_idx;
  *status_ref = status;
}

void helper_helper_helper_opng_read_file_2_1_1(png_uint_32 * const reductions_ref, volatile opng_status_t * const status_ref, const char * const fmt_name)
{
  png_uint_32 reductions = *reductions_ref;
  volatile opng_status_t status = *status_ref;
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  if (strcmp(fmt_name, "PNG") != 0)
  {
    usr_printf("Importing %s", fmt_name);
    if (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)
    {
      if (!(s_process.status & INPUT_IS_PNG_FILE))
      {
        usr_printf(" (multi-image or animation)");
      }
      if (s_options.snip)
      {
        usr_printf("; snipping...");
      }
    }
    usr_printf("\n");
  }
  opng_load_image_info(s_read_ptr, s_read_info_ptr, 1);
  opng_print_image_info(1, 1, 1, 1);
  usr_printf("\n");
  reductions = ((((0x0001 | 0x0002) | (((((0x0004 | 0x0008) | 0x0010) | 0x0020) | 0x0040) | 0x0080)) | (0x0100 | 0x0200)) | 0x1000) & (~0x1000);
  if (s_options.nb)
  {
    reductions &= ~(0x0001 | 0x0002);
  }
  if (s_options.nc)
  {
    reductions &= ~(((((0x0004 | 0x0008) | 0x0010) | 0x0020) | 0x0040) | 0x0080);
  }
  if (s_options.np)
  {
    reductions &= ~(0x0100 | 0x0200);
  }
  if (s_options.nz && (s_process.status & INPUT_HAS_PNG_DATASTREAM))
  {
    reductions = 0x0000;
  }
  if (s_process.status & INPUT_HAS_DIGITAL_SIGNATURE)
  {
    reductions = 0x0000;
  }
  if ((((s_process.status & INPUT_IS_PNG_FILE) && (s_process.status & INPUT_HAS_MULTIPLE_IMAGES)) && (reductions != 0x0000)) && (!s_options.snip))
  {
    usr_printf("Can't reliably reduce APNG file; disabling reductions.\n(Did you want to -snip and optimize the first frame?)\n");
    reductions = 0x0000;
  }
  s_process.reductions = opng_reduce_image(s_read_ptr, s_read_info_ptr, reductions);
  if (s_process.reductions != 0x0000)
  {
    opng_load_image_info(s_read_ptr, s_read_info_ptr, 1);
    usr_printf("Reducing image to ");
    opng_print_image_info(0, 1, 1, 0);
    usr_printf("\n");
  }
  if ((s_options.interlace >= 0) && (s_image.interlace_type != s_options.interlace))
  {
    s_image.interlace_type = s_options.interlace;
    s_process.status |= OUTPUT_NEEDS_NEW_IDAT;
  }
  *reductions_ref = reductions;
  *status_ref = status;
}

void helper_helper_helper_opng_iterate_1_1_1(int * const mem_level_ref, int * const counter_ref, int * const line_reused_ref, opng_bitset_t mem_level_set, int filter, int strategy, opng_bitset_t compr_level_set, int compr_level)
{
  int mem_level = *mem_level_ref;
  int counter = *counter_ref;
  int line_reused = *line_reused_ref;
  if (!((compr_level_set & (1U << compr_level)) != 0))
  {
    continue;
  }
  for (mem_level = 9; mem_level >= 1; mem_level -= 1)
  {
    helper_helper_helper_helper_opng_iterate_1_1_1_1(&counter, &line_reused, mem_level_set, filter, strategy, compr_level, mem_level);
  }

  *mem_level_ref = mem_level;
  *counter_ref = counter;
  *line_reused_ref = line_reused;
}

void helper_helper_helper_opng_optimize_impl_2_1_1(unsigned int * const infile_idx_ref, volatile opng_status_t * const status_ref, static FILE * const infile, static FILE * const outfile, unsigned int outfile_idx, static const char * const infile_name_local, static const char * const bakfile_name, static int new_outfile)
{
  unsigned int infile_idx = *infile_idx_ref;
  volatile opng_status_t status = *status_ref;
  if ((&outfile[outfile_idx]) == 0)
  {
    opng_throw_error("Can't open the output file");
  }
  if (s_process.status & OUTPUT_NEEDS_NEW_IDAT)
  {
    opng_write_file(outfile, s_process.best_compr_level, s_process.best_mem_level, s_process.best_strategy, s_process.best_filter);
  }
  else
  {
    helper_helper_helper_helper_opng_optimize_impl_2_1_1_1(&infile_idx, &status, infile, outfile, infile_name_local, bakfile_name, new_outfile);
  }
  *infile_idx_ref = infile_idx;
  *status_ref = status;
}

void helper_helper_helper_helper_opng_iterate_1_1_1_1(int * const counter_ref, int * const line_reused_ref, opng_bitset_t mem_level_set, int filter, int strategy, int compr_level, int mem_level)
{
  int counter = *counter_ref;
  int line_reused = *line_reused_ref;
  if (!((mem_level_set & (1U << mem_level)) != 0))
  {
    continue;
  }
  usr_printf("  zc = %d  zm = %d  zs = %d  f = %d", compr_level, mem_level, strategy, filter);
  usr_progress(counter, s_process.num_iterations);
  counter += 1;
  opng_write_file(0, compr_level, mem_level, strategy, filter);
  if (s_process.out_idat_size > k_idat_size_max)
  {
    if (s_options.verbose)
    {
      usr_printf("\t\tIDAT too big\n");
      line_reused = 0;
    }
    else
    {
      usr_print_cntrl('\r');
      line_reused = 1;
    }
    continue;
  }
  usr_printf("\t\tIDAT size = %lu\n", s_process.out_idat_size);
  line_reused = 0;
  if (s_process.best_idat_size < s_process.out_idat_size)
  {
    continue;
  }
  if ((s_process.best_idat_size == s_process.out_idat_size) && ((s_process.best_strategy == 2) || (s_process.best_strategy == 3)))
  {
    continue;
  }
  s_process.best_compr_level = compr_level;
  s_process.best_mem_level = mem_level;
  s_process.best_strategy = strategy;
  s_process.best_filter = filter;
  s_process.best_idat_size = s_process.out_idat_size;
  if (!s_options.full)
  {
    s_process.max_idat_size = s_process.out_idat_size;
  }
  *counter_ref = counter;
  *line_reused_ref = line_reused;
}

void helper_helper_helper_helper_opng_optimize_impl_2_1_1_1(unsigned int * const infile_idx_ref, volatile opng_status_t * const status_ref, static FILE * const infile, static FILE * const outfile, static const char * const infile_name_local, static const char * const bakfile_name, static int new_outfile)
{
  unsigned int infile_idx = *infile_idx_ref;
  volatile opng_status_t status = *status_ref;
  infile_idx = fopen((new_outfile) ? (infile_name_local) : (bakfile_name), "rb");
  if ((&infile[infile_idx]) == 0)
  {
    opng_throw_error("Can't reopen the input file");
  }
  {
    jmp_buf *exception__prev[1];
    jmp_buf exception__env;
    exception__prev[0] = the_exception_context->penv;
    the_exception_context->penv = &exception__env;
    if (setjmp(exception__env) == 0)
    {
      do
      {
        if ((s_process.in_datastream_offset > 0) && (opng_fseeko(infile, s_process.in_datastream_offset, 0) != 0))
        {
          opng_throw_error("Can't reposition the input file");
        }
        s_process.best_idat_size = s_process.in_idat_size;
        opng_copy_file(infile, outfile);
      }
      while (the_exception_context->caught = 0, the_exception_context->caught);
    }
    else
    {
      the_exception_context->caught = 1;
    }
    the_exception_context->penv = exception__prev[0];
  }
  if ((!the_exception_context->caught) || ((status = the_exception_context->v.etmp, 0)))
  {
  }
  else
  {
    {
      if (!(status != OPNG_STATUS_OK))
      {
        usr_panic("opng_copy_file should throw errors only");
      }
    }
    ;
  }
  fclose(infile);
  if (status != OPNG_STATUS_OK)
  {
    for (;; longjmp(*the_exception_context->penv, 1))
    {
      the_exception_context->v.etmp = status;
    }

  }
  *infile_idx_ref = infile_idx;
  *status_ref = status;
}

