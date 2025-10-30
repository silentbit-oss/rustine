#include <limits.h>
#include <png.h>
#include <pngconf.h>
#include <pngdebug.h>
#include <pngerror.c>
#include <pnginfo.h>
#include <pnglibconf.h>
#include <pngpriv.h>
#include <pngstruct.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <unistd.h>
#include <zconf.h>
#include <zlib.h>

typedef struct png_incomplete png_double;
typedef png_double *png_doublep;
typedef const png_double *png_const_doublep;
typedef png_double **png_doublepp;
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
extern float png_get_pixel_aspect_ratio(png_const_structrp png_ptr, png_const_inforp info_ptr);
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
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} png_compression_buffer;
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} *png_compression_bufferp;
struct png_struct_def
{
  png_error_ptr error_fn;
  png_error_ptr warning_fn;
  png_voidp error_ptr;
  png_rw_ptr write_data_fn;
  png_rw_ptr read_data_fn;
  png_voidp io_ptr;
  png_uint_32 mode;
  png_uint_32 flags;
  png_uint_32 transformations;
  png_uint_32 zowner;
  z_stream zstream;
  png_compression_bufferp zbuffer_list;
  uInt zbuffer_size;
  int zlib_level;
  int zlib_method;
  int zlib_window_bits;
  int zlib_mem_level;
  int zlib_strategy;
  int zlib_set_level;
  int zlib_set_method;
  int zlib_set_window_bits;
  int zlib_set_mem_level;
  int zlib_set_strategy;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 num_rows;
  png_uint_32 usr_width;
  size_t rowbytes;
  png_uint_32 iwidth;
  png_uint_32 row_number;
  png_uint_32 chunk_name;
  png_bytep prev_row;
  png_bytep row_buf;
  png_bytep try_row;
  png_bytep tst_row;
  size_t info_rowbytes;
  png_uint_32 idat_size;
  png_uint_32 crc;
  png_colorp palette;
  png_uint_16 num_palette;
  int num_palette_max;
  png_uint_16 num_trans;
  png_byte compression;
  png_byte filter;
  png_byte interlaced;
  png_byte pass;
  png_byte do_filter;
  png_byte color_type;
  png_byte bit_depth;
  png_byte usr_bit_depth;
  png_byte pixel_depth;
  png_byte channels;
  png_byte usr_channels;
  png_byte sig_bytes;
  png_byte maximum_pixel_depth;
  png_byte transformed_pixel_depth;
  png_byte zstream_start;
  png_byte background_gamma_type;
  png_fixed_point background_gamma;
  png_color_16 background;
  png_flush_ptr output_flush_fn;
  png_uint_32 flush_dist;
  png_uint_32 flush_rows;
  png_color_8 sig_bit;
  png_bytep trans_alpha;
  png_color_16 trans_color;
  png_read_status_ptr read_row_fn;
  png_write_status_ptr write_row_fn;
  png_uint_32 free_me;
  int unknown_default;
  unsigned int num_chunk_list;
  png_bytep chunk_list;
  png_bytep big_row_buf;
  png_byte compression_type;
  png_uint_32 user_width_max;
  png_uint_32 user_height_max;
  png_uint_32 user_chunk_cache_max;
  png_alloc_size_t user_chunk_malloc_max;
  png_unknown_chunk unknown_chunk;
  size_t old_big_row_buf_size;
  png_bytep read_buffer;
  png_alloc_size_t read_buffer_size;
  uInt IDAT_read_size;
  png_uint_32 io_state;
  png_bytep big_prev_row;
  void (*read_filter[5 - 1])(png_row_infop row_info, png_bytep row, png_const_bytep prev_row);
};
struct png_info_def
{
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 valid;
  size_t rowbytes;
  png_colorp palette;
  png_uint_16 num_palette;
  png_uint_16 num_trans;
  png_byte bit_depth;
  png_byte color_type;
  png_byte compression_type;
  png_byte filter_type;
  png_byte interlace_type;
  png_byte channels;
  png_byte pixel_depth;
  png_byte spare_byte;
  png_byte signature[8];
  png_color_8 sig_bit;
  png_bytep trans_alpha;
  png_color_16 trans_color;
  png_color_16 background;
  png_uint_16p hist;
  png_uint_32 free_me;
  png_unknown_chunkp unknown_chunks;
  int unknown_chunks_num;
  png_bytepp row_pointers;
};
typedef const png_uint_16p *png_const_uint_16pp;
extern void png_zstream_error(png_structrp png_ptr, int ret);
extern void png_free_buffer_list(png_structrp png_ptr, png_compression_bufferp *list);
extern int png_user_version_check(png_structrp png_ptr, png_const_charp user_png_ver);
extern png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size);
extern png_voidp png_malloc_array(png_const_structrp png_ptr, int nelements, size_t element_size);
extern png_voidp png_realloc_array(png_const_structrp png_ptr, png_const_voidp array, int old_elements, int add_elements, size_t element_size);
extern png_structp png_create_png_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn);
extern void png_destroy_png_struct(png_structrp png_ptr);
extern void png_free_jmpbuf(png_structrp png_ptr);
extern voidpf png_zalloc(voidpf png_ptr, uInt items, uInt size);
extern void png_zfree(voidpf png_ptr, voidpf ptr);
extern void png_default_read_data(png_structp png_ptr, png_bytep data, size_t length);
extern void png_default_write_data(png_structp png_ptr, png_bytep data, size_t length);
extern void png_default_flush(png_structp png_ptr);
extern void png_reset_crc(png_structrp png_ptr);
extern void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length);
extern void png_read_sig(png_structrp png_ptr, png_inforp info_ptr);
extern png_uint_32 png_read_chunk_header(png_structrp png_ptr);
extern void png_read_data(png_structrp png_ptr, png_bytep data, size_t length);
extern void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length);
extern int png_crc_finish(png_structrp png_ptr, png_uint_32 skip);
extern int png_crc_error(png_structrp png_ptr);
extern void png_calculate_crc(png_structrp png_ptr, png_const_bytep ptr, size_t length);
extern void png_flush(png_structrp png_ptr);
extern void png_write_IHDR(png_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int compression_method, int filter_method, int interlace_method);
extern void png_write_PLTE(png_structrp png_ptr, png_const_colorp palette, png_uint_32 num_pal);
extern void png_compress_IDAT(png_structrp png_ptr, png_const_bytep row_data, png_alloc_size_t row_data_length, int flush);
extern void png_write_IEND(png_structrp png_ptr);
extern void png_write_sBIT(png_structrp png_ptr, png_const_color_8p sbit, int color_type);
extern void png_write_tRNS(png_structrp png_ptr, png_const_bytep trans, png_const_color_16p values, int number, int color_type);
extern void png_write_bKGD(png_structrp png_ptr, png_const_color_16p values, int color_type);
extern void png_write_hIST(png_structrp png_ptr, png_const_uint_16p hist, int num_hist);
extern void png_write_finish_row(png_structrp png_ptr);
extern void png_write_start_row(png_structrp png_ptr);
extern void png_combine_row(png_const_structrp png_ptr, png_bytep row, int display);
extern void png_do_read_interlace(png_row_infop row_info, png_bytep row, int pass, png_uint_32 transformations);
extern void png_do_write_interlace(png_row_infop row_info, png_bytep row, int pass);
extern void png_read_filter_row(png_structrp pp, png_row_infop row_info, png_bytep row, png_const_bytep prev_row, int filter);
extern void png_write_find_filter(png_structrp png_ptr, png_row_infop row_info);
extern void png_read_IDAT_data(png_structrp png_ptr, png_bytep output, png_alloc_size_t avail_out);
extern void png_read_finish_IDAT(png_structrp png_ptr);
extern void png_read_finish_row(png_structrp png_ptr);
extern void png_read_start_row(png_structrp png_ptr);
extern int png_zlib_inflate(png_structrp png_ptr, int flush);
extern void png_read_transform_info(png_structrp png_ptr, png_inforp info_ptr);
extern void png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_IEND(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_bKGD(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_hIST(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_sBIT(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_check_chunk_name(png_const_structrp png_ptr, png_uint_32 chunk_name);
extern void png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 chunk_length);
extern void png_handle_unknown(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length, int keep);
extern int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name);
extern void png_do_read_transformations(png_structrp png_ptr, png_row_infop row_info);
extern void png_init_read_transformations(png_structrp png_ptr);
extern void png_check_IHDR(png_const_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type);
extern void png_do_check_palette_indexes(png_structrp png_ptr, png_row_infop row_info);
extern size_t png_safecat(png_charp buffer, size_t bufsize, size_t pos, png_const_charp string);
extern png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number);
typedef char png_warning_parameters[8][32];
extern void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string);
extern void png_warning_parameter_unsigned(png_warning_parameters p, int number, int format, png_alloc_size_t value);
extern void png_warning_parameter_signed(png_warning_parameters p, int number, int format, png_int_32 value);
extern void png_formatted_warning(png_const_structrp png_ptr, png_warning_parameters p, png_const_charp message);
extern void png_app_warning(png_const_structrp png_ptr, png_const_charp message);
extern void png_app_error(png_const_structrp png_ptr, png_const_charp message);
extern void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error);
extern png_uint_32 png_check_keyword(png_structrp png_ptr, png_const_charp key, png_bytep new_key);
static void png_default_error(png_const_structrp png_ptr, png_const_charp error_message);
static void png_default_warning(png_const_structrp png_ptr, png_const_charp warning_message);
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}

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

png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number)
{
  int count = 0;
  int mincount = 1;
  int output = 0;
  end -= 1;
  *end = '\0';
  while ((end > start) && ((number != 0) || (count < mincount)))
  {
    helper_png_format_number_1(&end, &number, &count, &mincount, &output, start, format);
  }

  return end;
}

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

void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string)
{
  if ((number > 0) && (number <= 8))
  {
    (void) png_safecat(p[number - 1], sizeof(p[number - 1]), 0, string);
  }
}

void png_warning_parameter_unsigned(png_warning_parameters p, int number, int format, png_alloc_size_t value)
{
  char buffer[24];
  png_warning_parameter(p, number, png_format_number(buffer, buffer + (sizeof(buffer)), format, value));
}

void png_warning_parameter_signed(png_warning_parameters p, int number, int format, png_int_32 value)
{
  png_alloc_size_t u;
  png_charp str;
  char buffer[24];
  u = (png_alloc_size_t) value;
  if (value < 0)
  {
    u = (~u) + 1;
  }
  str = png_format_number(buffer, buffer + (sizeof(buffer)), format, u);
  if ((value < 0) && (str > buffer))
  {
    str -= 1;
    *str = '-';
  }
  png_warning_parameter(p, number, str);
}

void png_formatted_warning(png_const_structrp png_ptr, png_warning_parameters p, png_const_charp message)
{
  size_t i = 0;
  char msg[192];
  while ((i < ((sizeof(msg)) - 1)) && ((*message) != '\0'))
  {
    if (((p != 0) && ((*message) == '@')) && (message[1] != '\0'))
    {
      message += 1;
      int parameter_char = *message;
      static const char valid_parameters[] = "123456789";
      int parameter = 0;
      while ((valid_parameters[parameter] != parameter_char) && (valid_parameters[parameter] != '\0'))
      {
        parameter += 1;
      }

      if (parameter < 8)
      {
        png_const_charp parm = p[parameter];
        png_const_charp pend = p[parameter] + (sizeof(p[parameter]));
        while (((i < ((sizeof(msg)) - 1)) && ((*parm) != '\0')) && (parm < pend))
        {
          msg[i] = *parm;
          parm += 1;
          i += 1;
        }

        message += 1;
        continue;
      }
    }
    msg[i] = *message;
    message += 1;
    i += 1;
  }

  msg[i] = '\0';
  png_warning(png_ptr, msg);
}

void png_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_warning(png_ptr, error_message);
    }
    else
      png_warning(png_ptr, error_message);
  }
  else
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_error(png_ptr, error_message);
    }
    else
      png_error(png_ptr, error_message);
  }
}

void png_app_warning(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x200000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}

void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}

static const char png_digit[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static void png_format_buffer(png_const_structrp png_ptr, png_charp buffer, png_const_charp error_message)
{
  png_uint_32 chunk_name = png_ptr->chunk_name;
  int iout = 0;
  int ishift = 24;
  while (ishift >= 0)
  {
    int c = ((int) (chunk_name >> ishift)) & 0xff;
    ishift -= 8;
    if ((((c < 65) || (c > 122)) || ((c > 90) && (c < 97))) != 0)
    {
      buffer[iout] = 0x5b;
      iout += 1;
      buffer[iout] = png_digit[(c & 0xf0) >> 4];
      iout += 1;
      buffer[iout] = png_digit[c & 0x0f];
      iout += 1;
      buffer[iout] = 0x5d;
      iout += 1;
    }
    else
    {
      buffer[iout] = (char) c;
      iout += 1;
    }
  }

  if (error_message == 0)
  {
    buffer[iout] = '\0';
  }
  else
  {
    int iin = 0;
    buffer[iout] = ':';
    iout += 1;
    buffer[iout] = ' ';
    iout += 1;
    while ((iin < (196 - 1)) && (error_message[iin] != '\0'))
    {
      buffer[iout] = error_message[iin];
      iin += 1;
      iout += 1;
    }

    buffer[iout] = '\0';
  }
}

void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_error(png_ptr, error_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
  }
}

void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}

void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    png_chunk_warning(png_ptr, error_message);
  }
  else
    png_chunk_error(png_ptr, error_message);
}

void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error)
{
  if ((png_ptr->mode & 0x8000U) != 0)
  {
    if (error < 2)
    {
      png_chunk_warning(png_ptr, message);
    }
    else
      png_chunk_benign_error(png_ptr, message);
  }
  else
    if ((png_ptr->mode & 0x8000U) == 0)
  {
    if (error < 1)
    {
      png_app_warning(png_ptr, message);
    }
    else
      png_app_error(png_ptr, message);
  }
}

static void png_default_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  {
    fprintf(stderr, "libpng error: %s", (error_message) ? (error_message) : ("undefined"));
    fprintf(stderr, "\n");
  }
  png_longjmp(png_ptr, 1);
}

void png_longjmp(png_const_structrp png_ptr, int val)
{
  (void) png_ptr;
  (void) val;
  abort();
}

static void png_default_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  {
    fprintf(stderr, "libpng warning: %s", warning_message);
    fprintf(stderr, "\n");
  }
  (void) png_ptr;
}

void png_set_error_fn(png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->error_ptr = error_ptr;
  png_ptr->error_fn = error_fn;
  png_ptr->warning_fn = warning_fn;
}

png_voidp png_get_error_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return (png_voidp) png_ptr->error_ptr;
}


typedef struct png_incomplete png_double;
typedef png_double *png_doublep;
typedef const png_double *png_const_doublep;
typedef png_double **png_doublepp;
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
extern float png_get_pixel_aspect_ratio(png_const_structrp png_ptr, png_const_inforp info_ptr);
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
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} png_compression_buffer;
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} *png_compression_bufferp;
struct png_struct_def
{
  png_error_ptr error_fn;
  png_error_ptr warning_fn;
  png_voidp error_ptr;
  png_rw_ptr write_data_fn;
  png_rw_ptr read_data_fn;
  png_voidp io_ptr;
  png_uint_32 mode;
  png_uint_32 flags;
  png_uint_32 transformations;
  png_uint_32 zowner;
  z_stream zstream;
  png_compression_bufferp zbuffer_list;
  uInt zbuffer_size;
  int zlib_level;
  int zlib_method;
  int zlib_window_bits;
  int zlib_mem_level;
  int zlib_strategy;
  int zlib_set_level;
  int zlib_set_method;
  int zlib_set_window_bits;
  int zlib_set_mem_level;
  int zlib_set_strategy;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 num_rows;
  png_uint_32 usr_width;
  size_t rowbytes;
  png_uint_32 iwidth;
  png_uint_32 row_number;
  png_uint_32 chunk_name;
  png_bytep prev_row;
  png_bytep row_buf;
  png_bytep try_row;
  png_bytep tst_row;
  size_t info_rowbytes;
  png_uint_32 idat_size;
  png_uint_32 crc;
  png_colorp palette;
  png_uint_16 num_palette;
  int num_palette_max;
  png_uint_16 num_trans;
  png_byte compression;
  png_byte filter;
  png_byte interlaced;
  png_byte pass;
  png_byte do_filter;
  png_byte color_type;
  png_byte bit_depth;
  png_byte usr_bit_depth;
  png_byte pixel_depth;
  png_byte channels;
  png_byte usr_channels;
  png_byte sig_bytes;
  png_byte maximum_pixel_depth;
  png_byte transformed_pixel_depth;
  png_byte zstream_start;
  png_byte background_gamma_type;
  png_fixed_point background_gamma;
  png_color_16 background;
  png_flush_ptr output_flush_fn;
  png_uint_32 flush_dist;
  png_uint_32 flush_rows;
  png_color_8 sig_bit;
  png_bytep trans_alpha;
  png_color_16 trans_color;
  png_read_status_ptr read_row_fn;
  png_write_status_ptr write_row_fn;
  png_uint_32 free_me;
  int unknown_default;
  unsigned int num_chunk_list;
  png_bytep chunk_list;
  png_bytep big_row_buf;
  png_byte compression_type;
  png_uint_32 user_width_max;
  png_uint_32 user_height_max;
  png_uint_32 user_chunk_cache_max;
  png_alloc_size_t user_chunk_malloc_max;
  png_unknown_chunk unknown_chunk;
  size_t old_big_row_buf_size;
  png_bytep read_buffer;
  png_alloc_size_t read_buffer_size;
  uInt IDAT_read_size;
  png_uint_32 io_state;
  png_bytep big_prev_row;
  void (*read_filter[5 - 1])(png_row_infop row_info, png_bytep row, png_const_bytep prev_row);
};
struct png_info_def
{
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 valid;
  size_t rowbytes;
  png_colorp palette;
  png_uint_16 num_palette;
  png_uint_16 num_trans;
  png_byte bit_depth;
  png_byte color_type;
  png_byte compression_type;
  png_byte filter_type;
  png_byte interlace_type;
  png_byte channels;
  png_byte pixel_depth;
  png_byte spare_byte;
  png_byte signature[8];
  png_color_8 sig_bit;
  png_bytep trans_alpha;
  png_color_16 trans_color;
  png_color_16 background;
  png_uint_16p hist;
  png_uint_32 free_me;
  png_unknown_chunkp unknown_chunks;
  int unknown_chunks_num;
  png_bytepp row_pointers;
};
typedef const png_uint_16p *png_const_uint_16pp;
extern void png_zstream_error(png_structrp png_ptr, int ret);
extern void png_free_buffer_list(png_structrp png_ptr, png_compression_bufferp *list);
extern int png_user_version_check(png_structrp png_ptr, png_const_charp user_png_ver);
extern png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size);
extern png_voidp png_malloc_array(png_const_structrp png_ptr, int nelements, size_t element_size);
extern png_voidp png_realloc_array(png_const_structrp png_ptr, png_const_voidp array, int old_elements, int add_elements, size_t element_size);
extern png_structp png_create_png_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn);
extern void png_destroy_png_struct(png_structrp png_ptr);
extern void png_free_jmpbuf(png_structrp png_ptr);
extern voidpf png_zalloc(voidpf png_ptr, uInt items, uInt size);
extern void png_zfree(voidpf png_ptr, voidpf ptr);
extern void png_default_read_data(png_structp png_ptr, png_bytep data, size_t length);
extern void png_default_write_data(png_structp png_ptr, png_bytep data, size_t length);
extern void png_default_flush(png_structp png_ptr);
extern void png_reset_crc(png_structrp png_ptr);
extern void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length);
extern void png_read_sig(png_structrp png_ptr, png_inforp info_ptr);
extern png_uint_32 png_read_chunk_header(png_structrp png_ptr);
extern void png_read_data(png_structrp png_ptr, png_bytep data, size_t length);
extern void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length);
extern int png_crc_finish(png_structrp png_ptr, png_uint_32 skip);
extern int png_crc_error(png_structrp png_ptr);
extern void png_calculate_crc(png_structrp png_ptr, png_const_bytep ptr, size_t length);
extern void png_flush(png_structrp png_ptr);
extern void png_write_IHDR(png_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int compression_method, int filter_method, int interlace_method);
extern void png_write_PLTE(png_structrp png_ptr, png_const_colorp palette, png_uint_32 num_pal);
extern void png_compress_IDAT(png_structrp png_ptr, png_const_bytep row_data, png_alloc_size_t row_data_length, int flush);
extern void png_write_IEND(png_structrp png_ptr);
extern void png_write_sBIT(png_structrp png_ptr, png_const_color_8p sbit, int color_type);
extern void png_write_tRNS(png_structrp png_ptr, png_const_bytep trans, png_const_color_16p values, int number, int color_type);
extern void png_write_bKGD(png_structrp png_ptr, png_const_color_16p values, int color_type);
extern void png_write_hIST(png_structrp png_ptr, png_const_uint_16p hist, int num_hist);
extern void png_write_finish_row(png_structrp png_ptr);
extern void png_write_start_row(png_structrp png_ptr);
extern void png_combine_row(png_const_structrp png_ptr, png_bytep row, int display);
extern void png_do_read_interlace(png_row_infop row_info, png_bytep row, int pass, png_uint_32 transformations);
extern void png_do_write_interlace(png_row_infop row_info, png_bytep row, int pass);
extern void png_read_filter_row(png_structrp pp, png_row_infop row_info, png_bytep row, png_const_bytep prev_row, int filter);
extern void png_write_find_filter(png_structrp png_ptr, png_row_infop row_info);
extern void png_read_IDAT_data(png_structrp png_ptr, png_bytep output, png_alloc_size_t avail_out);
extern void png_read_finish_IDAT(png_structrp png_ptr);
extern void png_read_finish_row(png_structrp png_ptr);
extern void png_read_start_row(png_structrp png_ptr);
extern int png_zlib_inflate(png_structrp png_ptr, int flush);
extern void png_read_transform_info(png_structrp png_ptr, png_inforp info_ptr);
extern void png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_IEND(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_bKGD(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_hIST(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_sBIT(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length);
extern void png_check_chunk_name(png_const_structrp png_ptr, png_uint_32 chunk_name);
extern void png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 chunk_length);
extern void png_handle_unknown(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length, int keep);
extern int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name);
extern void png_do_read_transformations(png_structrp png_ptr, png_row_infop row_info);
extern void png_init_read_transformations(png_structrp png_ptr);
extern void png_check_IHDR(png_const_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type);
extern void png_do_check_palette_indexes(png_structrp png_ptr, png_row_infop row_info);
extern size_t png_safecat(png_charp buffer, size_t bufsize, size_t pos, png_const_charp string);
extern png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number);
typedef char png_warning_parameters[8][32];
extern void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string);
extern void png_warning_parameter_unsigned(png_warning_parameters p, int number, int format, png_alloc_size_t value);
extern void png_warning_parameter_signed(png_warning_parameters p, int number, int format, png_int_32 value);
extern void png_formatted_warning(png_const_structrp png_ptr, png_warning_parameters p, png_const_charp message);
extern void png_app_warning(png_const_structrp png_ptr, png_const_charp message);
extern void png_app_error(png_const_structrp png_ptr, png_const_charp message);
extern void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error);
extern png_uint_32 png_check_keyword(png_structrp png_ptr, png_const_charp key, png_bytep new_key);
static void png_default_error(png_const_structrp png_ptr, png_const_charp error_message);
static void png_default_warning(png_const_structrp png_ptr, png_const_charp warning_message);
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}

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

png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number)
{
  int count = 0;
  int mincount = 1;
  int output = 0;
  end -= 1;
  *end = '\0';
  while ((end > start) && ((number != 0) || (count < mincount)))
  {
    static const char digits[] = "0123456789ABCDEF";
    switch (format)
    {
      case 5:
        mincount = 5;
        if ((output != 0) || ((number % 10) != 0))
      {
        end -= 1;
        *end = digits[number % 10];
        output = 1;
      }
        number /= 10;
        break;

      case 2:
        mincount = 2;

      case 1:
        end -= 1;
        *end = digits[number % 10];
        number /= 10;
        break;

      case 4:
        mincount = 2;

      case 3:
        end -= 1;
        *end = digits[number & 0xf];
        number >>= 4;
        break;

      default:
        number = 0;
        break;

    }

    count += 1;
    if (((format == 5) && (count == 5)) && (end > start))
    {
      if (output != 0)
      {
        end -= 1;
        *end = '.';
      }
      else
        if (number == 0)
      {
        end -= 1;
        *end = '0';
      }
    }
  }

  return end;
}

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

void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string)
{
  if ((number > 0) && (number <= 8))
  {
    (void) png_safecat(p[number - 1], sizeof(p[number - 1]), 0, string);
  }
}

void png_warning_parameter_unsigned(png_warning_parameters p, int number, int format, png_alloc_size_t value)
{
  char buffer[24];
  png_warning_parameter(p, number, png_format_number(buffer, buffer + (sizeof(buffer)), format, value));
}

void png_warning_parameter_signed(png_warning_parameters p, int number, int format, png_int_32 value)
{
  png_alloc_size_t u;
  png_charp str;
  char buffer[24];
  u = (png_alloc_size_t) value;
  if (value < 0)
  {
    u = (~u) + 1;
  }
  str = png_format_number(buffer, buffer + (sizeof(buffer)), format, u);
  if ((value < 0) && (str > buffer))
  {
    str -= 1;
    *str = '-';
  }
  png_warning_parameter(p, number, str);
}

void png_formatted_warning(png_const_structrp png_ptr, png_warning_parameters p, png_const_charp message)
{
  size_t i = 0;
  char msg[192];
  while ((i < ((sizeof(msg)) - 1)) && ((*message) != '\0'))
  {
    if (((p != 0) && ((*message) == '@')) && (message[1] != '\0'))
    {
      message += 1;
      int parameter_char = *message;
      static const char valid_parameters[] = "123456789";
      int parameter = 0;
      while ((valid_parameters[parameter] != parameter_char) && (valid_parameters[parameter] != '\0'))
      {
        parameter += 1;
      }

      if (parameter < 8)
      {
        png_const_charp parm = p[parameter];
        png_const_charp pend = p[parameter] + (sizeof(p[parameter]));
        while (((i < ((sizeof(msg)) - 1)) && ((*parm) != '\0')) && (parm < pend))
        {
          msg[i] = *parm;
          parm += 1;
          i += 1;
        }

        message += 1;
        continue;
      }
    }
    msg[i] = *message;
    message += 1;
    i += 1;
  }

  msg[i] = '\0';
  png_warning(png_ptr, msg);
}

void png_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_warning(png_ptr, error_message);
    }
    else
      png_warning(png_ptr, error_message);
  }
  else
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_error(png_ptr, error_message);
    }
    else
      png_error(png_ptr, error_message);
  }
}

void png_app_warning(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x200000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}

void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}

static const char png_digit[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
static void png_format_buffer(png_const_structrp png_ptr, png_charp buffer, png_const_charp error_message)
{
  png_uint_32 chunk_name = png_ptr->chunk_name;
  int iout = 0;
  int ishift = 24;
  while (ishift >= 0)
  {
    int c = ((int) (chunk_name >> ishift)) & 0xff;
    ishift -= 8;
    if ((((c < 65) || (c > 122)) || ((c > 90) && (c < 97))) != 0)
    {
      buffer[iout] = 0x5b;
      iout += 1;
      buffer[iout] = png_digit[(c & 0xf0) >> 4];
      iout += 1;
      buffer[iout] = png_digit[c & 0x0f];
      iout += 1;
      buffer[iout] = 0x5d;
      iout += 1;
    }
    else
    {
      buffer[iout] = (char) c;
      iout += 1;
    }
  }

  if (error_message == 0)
  {
    buffer[iout] = '\0';
  }
  else
  {
    int iin = 0;
    buffer[iout] = ':';
    iout += 1;
    buffer[iout] = ' ';
    iout += 1;
    while ((iin < (196 - 1)) && (error_message[iin] != '\0'))
    {
      buffer[iout] = error_message[iin];
      iin += 1;
      iout += 1;
    }

    buffer[iout] = '\0';
  }
}

void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_error(png_ptr, error_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
  }
}

void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}

void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    png_chunk_warning(png_ptr, error_message);
  }
  else
    png_chunk_error(png_ptr, error_message);
}

void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error)
{
  if ((png_ptr->mode & 0x8000U) != 0)
  {
    if (error < 2)
    {
      png_chunk_warning(png_ptr, message);
    }
    else
      png_chunk_benign_error(png_ptr, message);
  }
  else
    if ((png_ptr->mode & 0x8000U) == 0)
  {
    if (error < 1)
    {
      png_app_warning(png_ptr, message);
    }
    else
      png_app_error(png_ptr, message);
  }
}

static void png_default_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  {
    fprintf(stderr, "libpng error: %s", (error_message) ? (error_message) : ("undefined"));
    fprintf(stderr, "\n");
  }
  png_longjmp(png_ptr, 1);
}

void png_longjmp(png_const_structrp png_ptr, int val)
{
  (void) png_ptr;
  (void) val;
  abort();
}

static void png_default_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  {
    fprintf(stderr, "libpng warning: %s", warning_message);
    fprintf(stderr, "\n");
  }
  (void) png_ptr;
}

void png_set_error_fn(png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->error_ptr = error_ptr;
  png_ptr->error_fn = error_fn;
  png_ptr->warning_fn = warning_fn;
}

png_voidp png_get_error_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return (png_voidp) png_ptr->error_ptr;
}

void helper_png_format_number_1(png_charp * const end_ref, png_alloc_size_t * const number_ref, int * const count_ref, int * const mincount_ref, int * const output_ref, png_const_charp start, int format)
{
  png_charp end = *end_ref;
  png_alloc_size_t number = *number_ref;
  int count = *count_ref;
  int mincount = *mincount_ref;
  int output = *output_ref;
  static const char digits[] = "0123456789ABCDEF";
  switch (format)
  {
    case 5:
    {
      mincount = 5;
      if ((output != 0) || ((number % 10) != 0))
      {
        end -= 1;
        *end = digits[number % 10];
        output = 1;
      }
      number /= 10;
      break;
    }

    case 2:
    {
      mincount = 2;
    }

    case 1:
    {
      end -= 1;
      *end = digits[number % 10];
      number /= 10;
      break;
    }

    case 4:
    {
      mincount = 2;
    }

    case 3:
    {
      end -= 1;
      *end = digits[number & 0xf];
      number >>= 4;
      break;
    }

    default:
    {
      number = 0;
      break;
    }

  }

  count += 1;
  if (((format == 5) && (count == 5)) && (end > start))
  {
    if (output != 0)
    {
      end -= 1;
      *end = '.';
    }
    else
      if (number == 0)
    {
      end -= 1;
      *end = '0';
    }
  }
  *end_ref = end;
  *number_ref = number;
  *count_ref = count;
  *mincount_ref = mincount;
  *output_ref = output;
}

