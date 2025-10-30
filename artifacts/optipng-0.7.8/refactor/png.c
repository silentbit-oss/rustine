#include <limits.h>
#include <png.c>
#include <png.h>
#include <pngconf.h>
#include <pngdebug.h>
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
typedef png_libpng_version_1_6_40 Your_png_h_is_not_version_1_6_40;
void png_set_sig_bytes(png_structrp png_ptr, int num_bytes)
{
  unsigned int nb = (unsigned int) num_bytes;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (num_bytes < 0)
  {
    nb = 0;
  }
  if (nb > 8)
  {
    png_error(png_ptr, "Too many bytes for PNG signature");
  }
  png_ptr->sig_bytes = (png_byte) nb;
}

int png_sig_cmp(png_const_bytep sig, size_t start, size_t num_to_check)
{
  png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  if (num_to_check > 8)
  {
    num_to_check = 8;
  }
  else
    if (num_to_check < 1)
  {
    return -1;
  }
  if (start > 7)
  {
    return -1;
  }
  if ((start + num_to_check) > 8)
  {
    num_to_check = 8 - start;
  }
  return (int) memcmp(&sig[start], &png_signature[start], num_to_check);
}

voidpf png_zalloc(voidpf png_ptr, uInt items, uInt size)
{
  png_alloc_size_t num_bytes = size;
  if (png_ptr == 0)
  {
    return 0;
  }
  if (items >= ((~((png_alloc_size_t) 0)) / size))
  {
    png_warning(png_ptr, "Potential overflow in png_zalloc()");
    return 0;
  }
  num_bytes *= items;
  return png_malloc_warn(png_ptr, num_bytes);
}

void png_zfree(voidpf png_ptr, voidpf ptr)
{
  png_free(png_ptr, ptr);
}

void png_reset_crc(png_structrp png_ptr)
{
  png_ptr->crc = (png_uint_32) crc32(0, 0, 0);
}

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

int png_user_version_check(png_structrp png_ptr, png_const_charp user_png_ver)
{
  if (user_png_ver != 0)
  {
    int i = -1;
    int found_dots = 0;
    do
    {
      i += 1;
      if (user_png_ver[i] != "1.6.40"[i])
      {
        png_ptr->flags |= 0x20000U;
      }
      if (user_png_ver[i] == '.')
      {
        found_dots += 1;
      }
    }
    while (((found_dots < 2) && (user_png_ver[i] != 0)) && ("1.6.40"[i] != 0));
  }
  else
    png_ptr->flags |= 0x20000U;
  if ((png_ptr->flags & 0x20000U) != 0)
  {
    size_t pos = 0;
    char m[128];
    pos = png_safecat(m, sizeof(m), pos, "Application built with libpng-");
    pos = png_safecat(m, sizeof(m), pos, user_png_ver);
    pos = png_safecat(m, sizeof(m), pos, " but running with ");
    pos = png_safecat(m, sizeof(m), pos, "1.6.40");
    (void) pos;
    png_warning(png_ptr, m);
    return 0;
  }
  return 1;
}

png_structp png_create_png_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn)
{
  png_struct create_struct;
  memset(&create_struct, 0, sizeof(create_struct));
  create_struct.user_width_max = 1000000;
  create_struct.user_height_max = 1000000;
  create_struct.user_chunk_cache_max = 1000;
  create_struct.user_chunk_malloc_max = 8000000;
  (void) mem_ptr;
  (void) malloc_fn;
  (void) free_fn;
  png_set_error_fn(&create_struct, error_ptr, error_fn, warn_fn);
  {
    if (png_user_version_check(&create_struct, user_png_ver) != 0)
    {
      png_structrp png_ptr = png_malloc_warn(&create_struct, sizeof(*png_ptr));
      if (png_ptr != 0)
      {
        create_struct.zstream.zalloc = png_zalloc;
        create_struct.zstream.zfree = png_zfree;
        create_struct.zstream.opaque = png_ptr;
        *png_ptr = create_struct;
        return png_ptr;
      }
    }
  }
  return 0;
}

png_infop png_create_info_struct(png_const_structrp png_ptr)
{
  png_inforp info_ptr;
  (void) 0;
  if (png_ptr == 0)
  {
    return 0;
  }
  info_ptr = png_malloc_base(png_ptr, sizeof(*info_ptr));
  if (info_ptr != 0)
  {
    memset(info_ptr, 0, sizeof(*info_ptr));
  }
  return info_ptr;
}

void png_destroy_info_struct(png_const_structrp png_ptr, png_infopp info_ptr_ptr)
{
  png_inforp info_ptr = 0;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (info_ptr_ptr != 0)
  {
    info_ptr = *info_ptr_ptr;
  }
  if (info_ptr != 0)
  {
    *info_ptr_ptr = 0;
    png_free_data(png_ptr, info_ptr, 0xffffU, -1);
    memset(info_ptr, 0, sizeof(*info_ptr));
    png_free(png_ptr, info_ptr);
  }
}

void png_info_init_3(png_infopp ptr_ptr, size_t png_info_struct_size)
{
  png_inforp info_ptr = *ptr_ptr;
  (void) 0;
  if (info_ptr == 0)
  {
    return;
  }
  if ((sizeof(png_info)) > png_info_struct_size)
  {
    *ptr_ptr = 0;
    free(info_ptr);
    info_ptr = png_malloc_base(0, sizeof(*info_ptr));
    if (info_ptr == 0)
    {
      return;
    }
    *ptr_ptr = info_ptr;
  }
  memset(info_ptr, 0, sizeof(*info_ptr));
}

void png_data_freer(png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (freer == 1)
  {
    info_ptr->free_me |= mask;
  }
  else
    if (freer == 2)
  {
    info_ptr->free_me &= ~mask;
  }
  else
    png_error(png_ptr, "Unknown freer parameter in png_data_freer");
}

void png_free_data(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 mask, int num)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (((mask & 0x2000U) & info_ptr->free_me) != 0)
  {
    info_ptr->valid &= ~0x0010U;
    png_free(png_ptr, info_ptr->trans_alpha);
    info_ptr->trans_alpha = 0;
    info_ptr->num_trans = 0;
  }
  if ((info_ptr->unknown_chunks != 0) && (((mask & 0x0200U) & info_ptr->free_me) != 0))
  {
    if (num != (-1))
    {
      png_free(png_ptr, info_ptr->unknown_chunks[num].data);
      info_ptr->unknown_chunks[num].data = 0;
    }
    else
    {
      int i;
      for (i = 0; i < info_ptr->unknown_chunks_num; i += 1)
      {
        png_free(png_ptr, info_ptr->unknown_chunks[i].data);
      }

      png_free(png_ptr, info_ptr->unknown_chunks);
      info_ptr->unknown_chunks = 0;
      info_ptr->unknown_chunks_num = 0;
    }
  }
  if (((mask & 0x0008U) & info_ptr->free_me) != 0)
  {
    png_free(png_ptr, info_ptr->hist);
    info_ptr->hist = 0;
    info_ptr->valid &= ~0x0040U;
  }
  if (((mask & 0x1000U) & info_ptr->free_me) != 0)
  {
    png_free(png_ptr, info_ptr->palette);
    info_ptr->palette = 0;
    info_ptr->valid &= ~0x0008U;
    info_ptr->num_palette = 0;
  }
  if (((mask & 0x0040U) & info_ptr->free_me) != 0)
  {
    if (info_ptr->row_pointers != 0)
    {
      png_uint_32 row;
      for (row = 0; row < info_ptr->height; row += 1)
      {
        png_free(png_ptr, info_ptr->row_pointers[row]);
      }

      png_free(png_ptr, info_ptr->row_pointers);
      info_ptr->row_pointers = 0;
    }
    info_ptr->valid &= ~0x8000U;
  }
  if (num != (-1))
  {
    mask &= ~0x4220U;
  }
  info_ptr->free_me &= ~mask;
}

png_voidp png_get_io_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return png_ptr->io_ptr;
}

void png_init_io(png_structrp png_ptr, png_FILE_p fp)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = (png_voidp) fp;
}

void png_save_int_32(png_bytep buf, png_int_32 i)
{
  png_save_uint_32(buf, (png_uint_32) i);
}

png_const_charp png_get_copyright(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "\nlibpng version 1.6.40\nCopyright (c) 2018-2023 Cosmin Truta\nCopyright (c) 1998-2002,2004,2006-2018 Glenn Randers-Pehrson\nCopyright (c) 1996-1997 Andreas Dilger\nCopyright (c) 1995-1996 Guy Eric Schalnat, Group 42, Inc.\n";
}

png_const_charp png_get_libpng_ver(png_const_structrp png_ptr)
{
  return png_get_header_ver(png_ptr);
}

png_const_charp png_get_header_ver(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "1.6.40";
}

png_const_charp png_get_header_version(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return " libpng version 1.6.40 - June 21, 2023\n\n";
}

int png_handle_as_unknown(png_const_structrp png_ptr, png_const_bytep chunk_name)
{
  png_const_bytep p;
  png_const_bytep p_end;
  if (((png_ptr == 0) || (chunk_name == 0)) || (png_ptr->num_chunk_list == 0))
  {
    return 0;
  }
  p_end = png_ptr->chunk_list;
  p = p_end + (png_ptr->num_chunk_list * 5);
  do
  {
    p -= 5;
    if (memcmp(chunk_name, p, 4) == 0)
    {
      return p[4];
    }
  }
  while (p > p_end);
  return 0;
}

int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  png_byte chunk_string[5];
  (void) (((void) ((((char *) chunk_string)[0] = (char) ((chunk_name >> 24) & 0xff), ((char *) chunk_string)[1] = (char) ((chunk_name >> 16) & 0xff), ((char *) chunk_string)[2] = (char) ((chunk_name >> 8) & 0xff), ((char *) chunk_string)[3] = (char) (chunk_name & 0xff))), ((char *) chunk_string)[4] = 0));
  return png_handle_as_unknown(png_ptr, chunk_string);
}

int png_reset_zstream(png_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return -2;
  }
  return inflateReset(&png_ptr->zstream);
}

png_uint_32 png_access_version_number(void)
{
  return (png_uint_32) 10640;
}

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

static int png_gt(size_t a, size_t b)
{
  return a > b;
}

void png_check_IHDR(png_const_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type)
{
  int error = 0;
  if (width == 0)
  {
    png_warning(png_ptr, "Image width is zero in IHDR");
    error = 1;
  }
  if (width > ((png_uint_32) 0x7fffffffL))
  {
    png_warning(png_ptr, "Invalid image width in IHDR");
    error = 1;
  }
  if (png_gt((width + 7) & (~7U), (((((size_t) (-1)) - 48) - 1) / 8) - 1))
  {
    png_warning(png_ptr, "Image width is too large for this architecture");
    error = 1;
  }
  if (width > png_ptr->user_width_max)
  {
    png_warning(png_ptr, "Image width exceeds user limit in IHDR");
    error = 1;
  }
  if (height == 0)
  {
    png_warning(png_ptr, "Image height is zero in IHDR");
    error = 1;
  }
  if (height > ((png_uint_32) 0x7fffffffL))
  {
    png_warning(png_ptr, "Invalid image height in IHDR");
    error = 1;
  }
  if (height > png_ptr->user_height_max)
  {
    png_warning(png_ptr, "Image height exceeds user limit in IHDR");
    error = 1;
  }
  if (((((bit_depth != 1) && (bit_depth != 2)) && (bit_depth != 4)) && (bit_depth != 8)) && (bit_depth != 16))
  {
    png_warning(png_ptr, "Invalid bit depth in IHDR");
    error = 1;
  }
  if ((((color_type < 0) || (color_type == 1)) || (color_type == 5)) || (color_type > 6))
  {
    png_warning(png_ptr, "Invalid color type in IHDR");
    error = 1;
  }
  if (((color_type == (2 | 1)) && (bit_depth > 8)) || ((((color_type == 2) || (color_type == 4)) || (color_type == (2 | 4))) && (bit_depth < 8)))
  {
    png_warning(png_ptr, "Invalid color type/bit depth combination in IHDR");
    error = 1;
  }
  if (interlace_type >= 2)
  {
    png_warning(png_ptr, "Unknown interlace method in IHDR");
    error = 1;
  }
  if (compression_type != 0)
  {
    png_warning(png_ptr, "Unknown compression method in IHDR");
    error = 1;
  }
  if (filter_type != 0)
  {
    png_warning(png_ptr, "Unknown filter method in IHDR");
    error = 1;
  }
  if (error == 1)
  {
    png_error(png_ptr, "Invalid IHDR data");
  }
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
typedef png_libpng_version_1_6_40 Your_png_h_is_not_version_1_6_40;
void png_set_sig_bytes(png_structrp png_ptr, int num_bytes)
{
  unsigned int nb = (unsigned int) num_bytes;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (num_bytes < 0)
  {
    nb = 0;
  }
  if (nb > 8)
  {
    png_error(png_ptr, "Too many bytes for PNG signature");
  }
  png_ptr->sig_bytes = (png_byte) nb;
}

int png_sig_cmp(png_const_bytep sig, size_t start, size_t num_to_check)
{
  png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  if (num_to_check > 8)
  {
    num_to_check = 8;
  }
  else
    if (num_to_check < 1)
  {
    return -1;
  }
  if (start > 7)
  {
    return -1;
  }
  if ((start + num_to_check) > 8)
  {
    num_to_check = 8 - start;
  }
  return (int) memcmp(&sig[start], &png_signature[start], num_to_check);
}

voidpf png_zalloc(voidpf png_ptr, uInt items, uInt size)
{
  png_alloc_size_t num_bytes = size;
  if (png_ptr == 0)
  {
    return 0;
  }
  if (items >= ((~((png_alloc_size_t) 0)) / size))
  {
    png_warning(png_ptr, "Potential overflow in png_zalloc()");
    return 0;
  }
  num_bytes *= items;
  return png_malloc_warn(png_ptr, num_bytes);
}

void png_zfree(voidpf png_ptr, voidpf ptr)
{
  png_free(png_ptr, ptr);
}

void png_reset_crc(png_structrp png_ptr)
{
  png_ptr->crc = (png_uint_32) crc32(0, 0, 0);
}

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

int png_user_version_check(png_structrp png_ptr, png_const_charp user_png_ver)
{
  if (user_png_ver != 0)
  {
    int i = -1;
    int found_dots = 0;
    do
    {
      i += 1;
      if (user_png_ver[i] != "1.6.40"[i])
      {
        png_ptr->flags |= 0x20000U;
      }
      if (user_png_ver[i] == '.')
      {
        found_dots += 1;
      }
    }
    while (((found_dots < 2) && (user_png_ver[i] != 0)) && ("1.6.40"[i] != 0));
  }
  else
    png_ptr->flags |= 0x20000U;
  if ((png_ptr->flags & 0x20000U) != 0)
  {
    size_t pos = 0;
    char m[128];
    pos = png_safecat(m, sizeof(m), pos, "Application built with libpng-");
    pos = png_safecat(m, sizeof(m), pos, user_png_ver);
    pos = png_safecat(m, sizeof(m), pos, " but running with ");
    pos = png_safecat(m, sizeof(m), pos, "1.6.40");
    (void) pos;
    png_warning(png_ptr, m);
    return 0;
  }
  return 1;
}

png_structp png_create_png_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn)
{
  png_struct create_struct;
  memset(&create_struct, 0, sizeof(create_struct));
  create_struct.user_width_max = 1000000;
  create_struct.user_height_max = 1000000;
  create_struct.user_chunk_cache_max = 1000;
  create_struct.user_chunk_malloc_max = 8000000;
  (void) mem_ptr;
  (void) malloc_fn;
  (void) free_fn;
  png_set_error_fn(&create_struct, error_ptr, error_fn, warn_fn);
  {
    if (png_user_version_check(&create_struct, user_png_ver) != 0)
    {
      png_structrp png_ptr = png_malloc_warn(&create_struct, sizeof(*png_ptr));
      if (png_ptr != 0)
      {
        create_struct.zstream.zalloc = png_zalloc;
        create_struct.zstream.zfree = png_zfree;
        create_struct.zstream.opaque = png_ptr;
        *png_ptr = create_struct;
        return png_ptr;
      }
    }
  }
  return 0;
}

png_infop png_create_info_struct(png_const_structrp png_ptr)
{
  png_inforp info_ptr;
  (void) 0;
  if (png_ptr == 0)
  {
    return 0;
  }
  info_ptr = png_malloc_base(png_ptr, sizeof(*info_ptr));
  if (info_ptr != 0)
  {
    memset(info_ptr, 0, sizeof(*info_ptr));
  }
  return info_ptr;
}

void png_destroy_info_struct(png_const_structrp png_ptr, png_infopp info_ptr_ptr)
{
  png_inforp info_ptr = 0;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (info_ptr_ptr != 0)
  {
    info_ptr = *info_ptr_ptr;
  }
  if (info_ptr != 0)
  {
    *info_ptr_ptr = 0;
    png_free_data(png_ptr, info_ptr, 0xffffU, -1);
    memset(info_ptr, 0, sizeof(*info_ptr));
    png_free(png_ptr, info_ptr);
  }
}

void png_info_init_3(png_infopp ptr_ptr, size_t png_info_struct_size)
{
  png_inforp info_ptr = *ptr_ptr;
  (void) 0;
  if (info_ptr == 0)
  {
    return;
  }
  if ((sizeof(png_info)) > png_info_struct_size)
  {
    *ptr_ptr = 0;
    free(info_ptr);
    info_ptr = png_malloc_base(0, sizeof(*info_ptr));
    if (info_ptr == 0)
    {
      return;
    }
    *ptr_ptr = info_ptr;
  }
  memset(info_ptr, 0, sizeof(*info_ptr));
}

void png_data_freer(png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (freer == 1)
  {
    info_ptr->free_me |= mask;
  }
  else
    if (freer == 2)
  {
    info_ptr->free_me &= ~mask;
  }
  else
    png_error(png_ptr, "Unknown freer parameter in png_data_freer");
}

void png_free_data(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 mask, int num)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (((mask & 0x2000U) & info_ptr->free_me) != 0)
  {
    info_ptr->valid &= ~0x0010U;
    png_free(png_ptr, info_ptr->trans_alpha);
    info_ptr->trans_alpha = 0;
    info_ptr->num_trans = 0;
  }
  if ((info_ptr->unknown_chunks != 0) && (((mask & 0x0200U) & info_ptr->free_me) != 0))
  {
    if (num != (-1))
    {
      png_free(png_ptr, info_ptr->unknown_chunks[num].data);
      info_ptr->unknown_chunks[num].data = 0;
    }
    else
    {
      int i;
      for (i = 0; i < info_ptr->unknown_chunks_num; i += 1)
      {
        png_free(png_ptr, info_ptr->unknown_chunks[i].data);
      }

      png_free(png_ptr, info_ptr->unknown_chunks);
      info_ptr->unknown_chunks = 0;
      info_ptr->unknown_chunks_num = 0;
    }
  }
  if (((mask & 0x0008U) & info_ptr->free_me) != 0)
  {
    png_free(png_ptr, info_ptr->hist);
    info_ptr->hist = 0;
    info_ptr->valid &= ~0x0040U;
  }
  if (((mask & 0x1000U) & info_ptr->free_me) != 0)
  {
    png_free(png_ptr, info_ptr->palette);
    info_ptr->palette = 0;
    info_ptr->valid &= ~0x0008U;
    info_ptr->num_palette = 0;
  }
  if (((mask & 0x0040U) & info_ptr->free_me) != 0)
  {
    if (info_ptr->row_pointers != 0)
    {
      png_uint_32 row;
      for (row = 0; row < info_ptr->height; row += 1)
      {
        png_free(png_ptr, info_ptr->row_pointers[row]);
      }

      png_free(png_ptr, info_ptr->row_pointers);
      info_ptr->row_pointers = 0;
    }
    info_ptr->valid &= ~0x8000U;
  }
  if (num != (-1))
  {
    mask &= ~0x4220U;
  }
  info_ptr->free_me &= ~mask;
}

png_voidp png_get_io_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return png_ptr->io_ptr;
}

void png_init_io(png_structrp png_ptr, png_FILE_p fp)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = (png_voidp) fp;
}

void png_save_int_32(png_bytep buf, png_int_32 i)
{
  png_save_uint_32(buf, (png_uint_32) i);
}

png_const_charp png_get_copyright(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "\nlibpng version 1.6.40\nCopyright (c) 2018-2023 Cosmin Truta\nCopyright (c) 1998-2002,2004,2006-2018 Glenn Randers-Pehrson\nCopyright (c) 1996-1997 Andreas Dilger\nCopyright (c) 1995-1996 Guy Eric Schalnat, Group 42, Inc.\n";
}

png_const_charp png_get_libpng_ver(png_const_structrp png_ptr)
{
  return png_get_header_ver(png_ptr);
}

png_const_charp png_get_header_ver(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "1.6.40";
}

png_const_charp png_get_header_version(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return " libpng version 1.6.40 - June 21, 2023\n\n";
}

int png_handle_as_unknown(png_const_structrp png_ptr, png_const_bytep chunk_name)
{
  png_const_bytep p;
  png_const_bytep p_end;
  if (((png_ptr == 0) || (chunk_name == 0)) || (png_ptr->num_chunk_list == 0))
  {
    return 0;
  }
  p_end = png_ptr->chunk_list;
  p = p_end + (png_ptr->num_chunk_list * 5);
  do
  {
    p -= 5;
    if (memcmp(chunk_name, p, 4) == 0)
    {
      return p[4];
    }
  }
  while (p > p_end);
  return 0;
}

int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  png_byte chunk_string[5];
  (void) (((void) ((((char *) chunk_string)[0] = (char) ((chunk_name >> 24) & 0xff), ((char *) chunk_string)[1] = (char) ((chunk_name >> 16) & 0xff), ((char *) chunk_string)[2] = (char) ((chunk_name >> 8) & 0xff), ((char *) chunk_string)[3] = (char) (chunk_name & 0xff))), ((char *) chunk_string)[4] = 0));
  return png_handle_as_unknown(png_ptr, chunk_string);
}

int png_reset_zstream(png_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return -2;
  }
  return inflateReset(&png_ptr->zstream);
}

png_uint_32 png_access_version_number(void)
{
  return (png_uint_32) 10640;
}

void png_zstream_error(png_structrp png_ptr, int ret)
{
  if (png_ptr->zstream.msg == 0)
  {
    switch (ret)
    {
      default:

      case 0:
        png_ptr->zstream.msg = "unexpected zlib return code";
        break;

      case 1:
        png_ptr->zstream.msg = "unexpected end of LZ stream";
        break;

      case 2:
        png_ptr->zstream.msg = "missing LZ dictionary";
        break;

      case -1:
        png_ptr->zstream.msg = "zlib IO error";
        break;

      case -2:
        png_ptr->zstream.msg = "bad parameters to zlib";
        break;

      case -3:
        png_ptr->zstream.msg = "damaged LZ stream";
        break;

      case -4:
        png_ptr->zstream.msg = "insufficient memory";
        break;

      case -5:
        png_ptr->zstream.msg = "truncated";
        break;

      case -6:
        png_ptr->zstream.msg = "unsupported zlib version";
        break;

      case -7:
        png_ptr->zstream.msg = "unexpected zlib return";
        break;

    }

  }
}

static int png_gt(size_t a, size_t b)
{
  return a > b;
}

void png_check_IHDR(png_const_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type)
{
  int error = 0;
  if (width == 0)
  {
    png_warning(png_ptr, "Image width is zero in IHDR");
    error = 1;
  }
  if (width > ((png_uint_32) 0x7fffffffL))
  {
    png_warning(png_ptr, "Invalid image width in IHDR");
    error = 1;
  }
  if (png_gt((width + 7) & (~7U), (((((size_t) (-1)) - 48) - 1) / 8) - 1))
  {
    png_warning(png_ptr, "Image width is too large for this architecture");
    error = 1;
  }
  if (width > png_ptr->user_width_max)
  {
    png_warning(png_ptr, "Image width exceeds user limit in IHDR");
    error = 1;
  }
  if (height == 0)
  {
    png_warning(png_ptr, "Image height is zero in IHDR");
    error = 1;
  }
  if (height > ((png_uint_32) 0x7fffffffL))
  {
    png_warning(png_ptr, "Invalid image height in IHDR");
    error = 1;
  }
  if (height > png_ptr->user_height_max)
  {
    png_warning(png_ptr, "Image height exceeds user limit in IHDR");
    error = 1;
  }
  if (((((bit_depth != 1) && (bit_depth != 2)) && (bit_depth != 4)) && (bit_depth != 8)) && (bit_depth != 16))
  {
    png_warning(png_ptr, "Invalid bit depth in IHDR");
    error = 1;
  }
  if ((((color_type < 0) || (color_type == 1)) || (color_type == 5)) || (color_type > 6))
  {
    png_warning(png_ptr, "Invalid color type in IHDR");
    error = 1;
  }
  if (((color_type == (2 | 1)) && (bit_depth > 8)) || ((((color_type == 2) || (color_type == 4)) || (color_type == (2 | 4))) && (bit_depth < 8)))
  {
    png_warning(png_ptr, "Invalid color type/bit depth combination in IHDR");
    error = 1;
  }
  if (interlace_type >= 2)
  {
    png_warning(png_ptr, "Unknown interlace method in IHDR");
    error = 1;
  }
  if (compression_type != 0)
  {
    png_warning(png_ptr, "Unknown compression method in IHDR");
    error = 1;
  }
  if (filter_type != 0)
  {
    png_warning(png_ptr, "Unknown filter method in IHDR");
    error = 1;
  }
  if (error == 1)
  {
    png_error(png_ptr, "Invalid IHDR data");
  }
}

