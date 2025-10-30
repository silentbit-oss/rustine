#include <limits.h>
#include <png.h>
#include <pngconf.h>
#include <pngdebug.h>
#include <pnginfo.h>
#include <pnglibconf.h>
#include <pngpriv.h>
#include <pngstruct.h>
#include <pngwutil.c>
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
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}

void png_save_uint_16(png_bytep buf, unsigned int i)
{
  buf[0] = (png_byte) ((i >> 8) & 0xffU);
  buf[1] = (png_byte) (i & 0xffU);
}

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

void png_write_chunk_start(png_structrp png_ptr, png_const_bytep chunk_string, png_uint_32 length)
{
  png_write_chunk_header(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), length);
}

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

void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_string, png_const_bytep data, size_t length)
{
  png_write_complete_chunk(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), data, length);
}

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

void png_write_IEND(png_structrp png_ptr)
{
  (void) 0;
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0), 0, 0);
  png_ptr->mode |= 0x10U;
}

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

static void png_write_filtered_row(png_structrp png_ptr, png_bytep filtered_row, size_t row_bytes);
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
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}

void png_save_uint_16(png_bytep buf, unsigned int i)
{
  buf[0] = (png_byte) ((i >> 8) & 0xffU);
  buf[1] = (png_byte) (i & 0xffU);
}

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

void png_write_chunk_start(png_structrp png_ptr, png_const_bytep chunk_string, png_uint_32 length)
{
  png_write_chunk_header(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), length);
}

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

void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_string, png_const_bytep data, size_t length)
{
  png_write_complete_chunk(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), data, length);
}

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

static int png_deflate_claim(png_structrp png_ptr, png_uint_32 owner, png_alloc_size_t data_size)
{
  if (png_ptr->zowner != 0)
  {
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
  }
  {
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
  }
}

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

void png_write_IHDR(png_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int compression_type, int filter_type, int interlace_type)
{
  png_byte buf[13];
  int is_invalid_depth;
  (void) 0;
  switch (color_type)
  {
    case 0:
      switch (bit_depth)
    {
      case 1:

      case 2:

      case 4:

      case 8:

      case 16:
        png_ptr->channels = 1;
        break;

      default:
        png_error(png_ptr, "Invalid bit depth for grayscale image");

    }

      break;

    case 2:
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
    {
      png_error(png_ptr, "Invalid bit depth for RGB image");
    }
      png_ptr->channels = 3;
      break;

    case 2 | 1:
      switch (bit_depth)
    {
      case 1:

      case 2:

      case 4:

      case 8:
        png_ptr->channels = 1;
        break;

      default:
        png_error(png_ptr, "Invalid bit depth for paletted image");

    }

      break;

    case 4:
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
    {
      png_error(png_ptr, "Invalid bit depth for grayscale+alpha image");
    }
      png_ptr->channels = 2;
      break;

    case 2 | 4:
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
    {
      png_error(png_ptr, "Invalid bit depth for RGBA image");
    }
      png_ptr->channels = 4;
      break;

    default:
      png_error(png_ptr, "Invalid image color type specified");

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
    }
    else
    {
      png_zstream_error(png_ptr, ret);
      png_error(png_ptr, png_ptr->zstream.msg);
    }
  }

}

void png_write_IEND(png_structrp png_ptr)
{
  (void) 0;
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0), 0, 0);
  png_ptr->mode |= 0x10U;
}

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

void png_do_write_interlace(png_row_infop row_info, png_bytep row, int pass)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  (void) 0;
  if (pass < 6)
  {
    switch (row_info->pixel_depth)
    {
      case 1:
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

      case 2:
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

      case 4:
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

      default:
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

    }

    row_info->width = (((row_info->width + png_pass_inc[pass]) - 1) - png_pass_start[pass]) / png_pass_inc[pass];
    row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) row_info->width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) row_info->width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  }
}

static void png_write_filtered_row(png_structrp png_ptr, png_bytep filtered_row, size_t row_bytes);
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
  }

  return sum;
}

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
  }

}

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

