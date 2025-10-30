#include <limits.h>
#include <png.h>
#include <pngconf.h>
#include <pngdebug.h>
#include <pnginfo.h>
#include <pnglibconf.h>
#include <pngpriv.h>
#include <pngrutil.c>
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
png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if (uval > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "PNG unsigned integer out of range");
  }
  return uval;
}

png_uint_32 png_get_uint_32(png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  return uval;
}

png_int_32 png_get_int_32(png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if ((uval & 0x80000000) == 0)
  {
    return (png_int_32) uval;
  }
  uval = (uval ^ 0xffffffff) + 1;
  if ((uval & 0x80000000) == 0)
  {
    return -((png_int_32) uval);
  }
  return 0;
}

png_uint_16 png_get_uint_16(png_const_bytep buf)
{
  unsigned int val = (((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)));
  return (png_uint_16) val;
}

void png_read_sig(png_structrp png_ptr, png_inforp info_ptr)
{
  size_t num_checked;
  size_t num_to_check;
  if (png_ptr->sig_bytes >= 8)
  {
    return;
  }
  num_checked = png_ptr->sig_bytes;
  num_to_check = 8 - num_checked;
  png_ptr->io_state = 0x0001 | 0x0010;
  png_read_data(png_ptr, &info_ptr->signature[num_checked], num_to_check);
  png_ptr->sig_bytes = 8;
  if (png_sig_cmp(info_ptr->signature, num_checked, num_to_check) != 0)
  {
    if ((num_checked < 4) && png_sig_cmp(info_ptr->signature, num_checked, num_to_check - 4))
    {
      png_error(png_ptr, "Not a PNG file");
    }
    else
      png_error(png_ptr, "PNG file corrupted by ASCII conversion");
  }
  if (num_checked < 3)
  {
    png_ptr->mode |= 0x1000U;
  }
}

png_uint_32 png_read_chunk_header(png_structrp png_ptr)
{
  png_byte buf[8];
  png_uint_32 length;
  png_ptr->io_state = 0x0001 | 0x0020;
  png_read_data(png_ptr, buf, 8);
  length = png_get_uint_31(png_ptr, buf);
  png_ptr->chunk_name = (((((png_uint_32) (0xff & (buf + 4)[0])) << 24) | (((png_uint_32) (0xff & (buf + 4)[1])) << 16)) | (((png_uint_32) (0xff & (buf + 4)[2])) << 8)) | (((png_uint_32) (0xff & (buf + 4)[3])) << 0);
  (void) 0;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_check_chunk_name(png_ptr, png_ptr->chunk_name);
  png_check_chunk_length(png_ptr, length);
  png_ptr->io_state = 0x0001 | 0x0040;
  return length;
}

void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}

int png_crc_finish(png_structrp png_ptr, png_uint_32 skip)
{
  while (skip > 0)
  {
    png_uint_32 len;
    png_byte tmpbuf[1024];
    len = sizeof(tmpbuf);
    if (len > skip)
    {
      len = skip;
    }
    skip -= len;
    png_crc_read(png_ptr, tmpbuf, len);
  }

  if (png_crc_error(png_ptr) != 0)
  {
    if (((1 & (png_ptr->chunk_name >> 29)) != 0) ? ((png_ptr->flags & 0x0200U) == 0) : ((png_ptr->flags & 0x0400U) != 0))
    {
      png_chunk_warning(png_ptr, "CRC error");
    }
    else
      png_chunk_error(png_ptr, "CRC error");
    return 1;
  }
  return 0;
}

int png_crc_error(png_structrp png_ptr)
{
  png_byte crc_bytes[4];
  png_uint_32 crc;
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
  png_ptr->io_state = 0x0001 | 0x0080;
  png_read_data(png_ptr, crc_bytes, 4);
  if (need_crc != 0)
  {
    crc = (((((png_uint_32) (*crc_bytes)) << 24) + (((png_uint_32) (*(crc_bytes + 1))) << 16)) + (((png_uint_32) (*(crc_bytes + 2))) << 8)) + ((png_uint_32) (*(crc_bytes + 3)));
    return (int) (crc != png_ptr->crc);
  }
  else
    return 0;
}

static png_bytep png_read_buffer(png_structrp png_ptr, png_alloc_size_t new_size, int warn)
{
  png_bytep buffer = png_ptr->read_buffer;
  if ((buffer != 0) && (new_size > png_ptr->read_buffer_size))
  {
    png_ptr->read_buffer = 0;
    png_ptr->read_buffer_size = 0;
    png_free(png_ptr, buffer);
    buffer = 0;
  }
  if (buffer == 0)
  {
    buffer = png_malloc_base(png_ptr, new_size);
    if (buffer != 0)
    {
      memset(buffer, 0, new_size);
      png_ptr->read_buffer = buffer;
      png_ptr->read_buffer_size = new_size;
    }
    else
      if (warn < 2)
    {
      if (warn != 0)
      {
        png_chunk_warning(png_ptr, "insufficient memory to read chunk");
      }
      else
        png_chunk_error(png_ptr, "insufficient memory to read chunk");
    }
  }
  return buffer;
}

static int png_inflate_claim(png_structrp png_ptr, png_uint_32 owner)
{
  if (png_ptr->zowner != 0)
  {
    char msg[64];
    (void) ((((char *) msg)[0] = (char) ((png_ptr->zowner >> 24) & 0xff), ((char *) msg)[1] = (char) ((png_ptr->zowner >> 16) & 0xff), ((char *) msg)[2] = (char) ((png_ptr->zowner >> 8) & 0xff), ((char *) msg)[3] = (char) (png_ptr->zowner & 0xff)));
    (void) png_safecat(msg, sizeof(msg), 4, " using zstream");
    png_chunk_warning(png_ptr, msg);
    png_ptr->zowner = 0;
  }
  {
    int ret;
    int window_bits = 0;
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zstream.next_out = 0;
    png_ptr->zstream.avail_out = 0;
    if ((png_ptr->flags & 0x0002U) != 0)
    {
      ret = inflateReset2(&png_ptr->zstream, window_bits);
    }
    else
    {
      ret = inflateInit2_(&png_ptr->zstream, window_bits, "1.3-optipng", (int) (sizeof(z_stream)));
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

int png_zlib_inflate(png_structrp png_ptr, int flush)
{
  if (png_ptr->zstream_start && (png_ptr->zstream.avail_in > 0))
  {
    if (((*png_ptr->zstream.next_in) >> 4) > 7)
    {
      png_ptr->zstream.msg = "invalid window size (libpng)";
      return -3;
    }
    png_ptr->zstream_start = 0;
  }
  return inflate(&png_ptr->zstream, flush);
}

void png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte buf[13];
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int interlace_type;
  (void) 0;
  if ((png_ptr->mode & 0x01) != 0)
  {
    png_chunk_error(png_ptr, "out of place");
  }
  if (length != 13)
  {
    png_chunk_error(png_ptr, "invalid");
  }
  png_ptr->mode |= 0x01;
  png_crc_read(png_ptr, buf, 13);
  png_crc_finish(png_ptr, 0);
  width = png_get_uint_31(png_ptr, buf);
  height = png_get_uint_31(png_ptr, buf + 4);
  bit_depth = buf[8];
  color_type = buf[9];
  compression_type = buf[10];
  filter_type = buf[11];
  interlace_type = buf[12];
  png_ptr->width = width;
  png_ptr->height = height;
  png_ptr->bit_depth = (png_byte) bit_depth;
  png_ptr->interlaced = (png_byte) interlace_type;
  png_ptr->color_type = (png_byte) color_type;
  png_ptr->compression_type = (png_byte) compression_type;
  switch (png_ptr->color_type)
  {
    default:

    case 0:

    case 2 | 1:
    {
      png_ptr->channels = 1;
      break;
    }

    case 2:
    {
      png_ptr->channels = 3;
      break;
    }

    case 4:
    {
      png_ptr->channels = 2;
      break;
    }

    case 2 | 4:
    {
      png_ptr->channels = 4;
      break;
    }

  }

  png_ptr->pixel_depth = (png_byte) (png_ptr->bit_depth * png_ptr->channels);
  png_ptr->rowbytes = (png_ptr->pixel_depth >= 8) ? (((size_t) png_ptr->width) * (((size_t) png_ptr->pixel_depth) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) png_ptr->pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}

void png_handle_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_color palette[256];
  int max_palette_length;
  int num;
  int i;
  png_colorp pal_ptr;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x02) != 0)
  {
    png_chunk_error(png_ptr, "duplicate");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  png_ptr->mode |= 0x02;
  if ((png_ptr->color_type & 2) == 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "ignored in grayscale PNG");
    return;
  }
  if ((length > (3 * 256)) || (length % 3))
  {
    png_crc_finish(png_ptr, length);
    if (png_ptr->color_type != (2 | 1))
    {
      png_chunk_benign_error(png_ptr, "invalid");
    }
    else
      png_chunk_error(png_ptr, "invalid");
    return;
  }
  num = ((int) length) / 3;
  if (png_ptr->color_type == (2 | 1))
  {
    max_palette_length = 1 << png_ptr->bit_depth;
  }
  else
    max_palette_length = 256;
  if (num > max_palette_length)
  {
    num = max_palette_length;
  }
  for (i = 0, pal_ptr = palette; i < num; i += 1, pal_ptr += 1)
  {
    png_byte buf[3];
    png_crc_read(png_ptr, buf, 3);
    pal_ptr->red = buf[0];
    pal_ptr->green = buf[1];
    pal_ptr->blue = buf[2];
  }

  {
    png_crc_finish(png_ptr, (png_uint_32) (length - (((unsigned int) num) * 3)));
  }
  png_set_PLTE(png_ptr, info_ptr, palette, num);
  if ((png_ptr->num_trans > 0) || ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0)))
  {
    png_ptr->num_trans = 0;
    if (info_ptr != 0)
    {
      info_ptr->num_trans = 0;
    }
    png_chunk_benign_error(png_ptr, "tRNS must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_chunk_benign_error(png_ptr, "hIST must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_chunk_benign_error(png_ptr, "bKGD must be after");
  }
}

void png_handle_IEND(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  (void) 0;
  if (((png_ptr->mode & 0x01) == 0) || ((png_ptr->mode & 0x04U) == 0))
  {
    png_chunk_error(png_ptr, "out of place");
  }
  png_ptr->mode |= 0x08 | 0x10U;
  png_crc_finish(png_ptr, length);
  if (length != 0)
  {
    png_chunk_benign_error(png_ptr, "invalid");
  }
  (void) info_ptr;
}

void png_handle_sBIT(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  unsigned int i;
  png_byte sample_depth;
  png_byte buf[4];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & (0x04U | 0x02)) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0002U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 3;
    sample_depth = 8;
  }
  else
  {
    truelen = png_ptr->channels;
    sample_depth = png_ptr->bit_depth;
  }
  if ((length != truelen) || (length > 4))
  {
    png_chunk_benign_error(png_ptr, "invalid");
    png_crc_finish(png_ptr, length);
    return;
  }
  buf[0] = (buf[1] = (buf[2] = (buf[3] = sample_depth)));
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  for (i = 0; i < truelen; i += 1)
  {
    if ((buf[i] == 0) || (buf[i] > sample_depth))
    {
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
  }

  if ((png_ptr->color_type & 2) != 0)
  {
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[1];
    png_ptr->sig_bit.blue = buf[2];
    png_ptr->sig_bit.alpha = buf[3];
  }
  else
  {
    png_ptr->sig_bit.gray = buf[0];
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[0];
    png_ptr->sig_bit.blue = buf[0];
    png_ptr->sig_bit.alpha = buf[1];
  }
  png_set_sBIT(png_ptr, info_ptr, &png_ptr->sig_bit);
}

void png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == 0)
  {
    png_byte buf[2];
    if (length != 2)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, 2);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }
  else
    if (png_ptr->color_type == 2)
  {
    png_byte buf[6];
    if (length != 6)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, length);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    png_ptr->trans_color.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    png_ptr->trans_color.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
  }
  else
    if (png_ptr->color_type == (2 | 1))
  {
    if ((png_ptr->mode & 0x02) == 0)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
    }
    if (((length > ((unsigned int) png_ptr->num_palette)) || (length > ((unsigned int) 256))) || (length == 0))
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, readbuf, length);
    png_ptr->num_trans = (png_uint_16) length;
  }
  else
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid with alpha channel");
    return;
  }
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    png_ptr->num_trans = 0;
    return;
  }
  png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans, &png_ptr->trans_color);
}

void png_handle_bKGD(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  png_byte buf[6];
  png_color_16 background;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->color_type == (2 | 1)) && ((png_ptr->mode & 0x02) == 0)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 1;
  }
  else
    if ((png_ptr->color_type & 2) != 0)
  {
    truelen = 6;
  }
  else
    truelen = 2;
  if (length != truelen)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    background.index = buf[0];
    if ((info_ptr != 0) && (info_ptr->num_palette != 0))
    {
      if (buf[0] >= info_ptr->num_palette)
      {
        png_chunk_benign_error(png_ptr, "invalid index");
        return;
      }
      background.red = (png_uint_16) png_ptr->palette[buf[0]].red;
      background.green = (png_uint_16) png_ptr->palette[buf[0]].green;
      background.blue = (png_uint_16) png_ptr->palette[buf[0]].blue;
    }
    else
      background.red = (background.green = (background.blue = 0));
    background.gray = 0;
  }
  else
    if ((png_ptr->color_type & 2) == 0)
  {
    if (png_ptr->bit_depth <= 8)
    {
      if ((buf[0] != 0) || (buf[1] >= ((unsigned int) (1 << png_ptr->bit_depth))))
      {
        png_chunk_benign_error(png_ptr, "invalid gray level");
        return;
      }
    }
    background.index = 0;
    background.red = (background.green = (background.blue = (background.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)))))));
  }
  else
  {
    if (png_ptr->bit_depth <= 8)
    {
      if (((buf[0] != 0) || (buf[2] != 0)) || (buf[4] != 0))
      {
        png_chunk_benign_error(png_ptr, "invalid color");
        return;
      }
    }
    background.index = 0;
    background.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    background.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    background.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
    background.gray = 0;
  }
  png_set_bKGD(png_ptr, info_ptr, &background);
}

void png_handle_hIST(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int num;
  unsigned int i;
  png_uint_16 readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->mode & 0x02) == 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  num = length / 2;
  if (((length != (num * 2)) || (num != ((unsigned int) png_ptr->num_palette))) || (num > ((unsigned int) 256)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  for (i = 0; i < num; i += 1)
  {
    png_byte buf[2];
    png_crc_read(png_ptr, buf, 2);
    readbuf[i] = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }

  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  png_set_hIST(png_ptr, info_ptr, readbuf);
}

static int png_cache_unknown_chunk(png_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (size_t) (-1);
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
    png_ptr->unknown_chunk.data = 0;
  }
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (length <= limit)
  {
    (void) (((void) ((((char *) png_ptr->unknown_chunk.name)[0] = (char) ((png_ptr->chunk_name >> 24) & 0xff), ((char *) png_ptr->unknown_chunk.name)[1] = (char) ((png_ptr->chunk_name >> 16) & 0xff), ((char *) png_ptr->unknown_chunk.name)[2] = (char) ((png_ptr->chunk_name >> 8) & 0xff), ((char *) png_ptr->unknown_chunk.name)[3] = (char) (png_ptr->chunk_name & 0xff))), ((char *) png_ptr->unknown_chunk.name)[4] = 0));
    png_ptr->unknown_chunk.size = (size_t) length;
    png_ptr->unknown_chunk.location = (png_byte) png_ptr->mode;
    if (length == 0)
    {
      png_ptr->unknown_chunk.data = 0;
    }
    else
    {
      png_ptr->unknown_chunk.data = png_malloc_warn(png_ptr, length);
    }
  }
  if ((png_ptr->unknown_chunk.data == 0) && (length > 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "unknown chunk exceeds memory limits");
    return 0;
  }
  else
  {
    if (length > 0)
    {
      png_crc_read(png_ptr, png_ptr->unknown_chunk.data, length);
    }
    png_crc_finish(png_ptr, 0);
    return 1;
  }
}

void png_handle_unknown(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length, int keep)
{
  int handled = 0;
  (void) 0;
  {
    if (keep == 0)
    {
      keep = png_ptr->unknown_default;
    }
    if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
    {
      if (png_cache_unknown_chunk(png_ptr, length) == 0)
      {
        keep = 1;
      }
    }
    else
      png_crc_finish(png_ptr, length);
  }
  if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
  {
    switch (png_ptr->user_chunk_cache_max)
    {
      case 2:
      {
        png_ptr->user_chunk_cache_max = 1;
        png_chunk_benign_error(png_ptr, "no space in chunk cache");
      }

      case 1:
      {
        break;
      }

      default:
      {
        png_ptr->user_chunk_cache_max -= 1;
      }

      case 0:
      {
        png_set_unknown_chunks(png_ptr, info_ptr, &png_ptr->unknown_chunk, 1);
        handled = 1;
        break;
      }

    }

  }
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
  }
  png_ptr->unknown_chunk.data = 0;
  if ((handled == 0) && (!(1 & (png_ptr->chunk_name >> 29))))
  {
    png_chunk_error(png_ptr, "unhandled critical chunk");
  }
}

void png_check_chunk_name(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  int i;
  png_uint_32 cn = chunk_name;
  (void) 0;
  for (i = 1; i <= 4; i += 1)
  {
    int c = cn & 0xff;
    if (((c < 65) || (c > 122)) || ((c > 90) && (c < 97)))
    {
      png_chunk_error(png_ptr, "invalid chunk type");
    }
    cn >>= 8;
  }

}

void png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (png_uint_32) 0x7fffffffL;
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (png_ptr->chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_alloc_size_t idat_limit = (png_uint_32) 0x7fffffffL;
    size_t row_factor = (((((size_t) png_ptr->width) * ((size_t) png_ptr->channels)) * ((png_ptr->bit_depth > 8) ? (2) : (1))) + 1) + ((png_ptr->interlaced) ? (6) : (0));
    if (png_ptr->height > (((png_uint_32) (-1)) / row_factor))
    {
      idat_limit = (png_uint_32) 0x7fffffffL;
    }
    else
      idat_limit = png_ptr->height * row_factor;
    row_factor = (row_factor > 32566) ? (32566) : (row_factor);
    idat_limit += 6 + (5 * ((idat_limit / row_factor) + 1));
    idat_limit = (idat_limit < ((png_uint_32) 0x7fffffffL)) ? (idat_limit) : ((png_uint_32) 0x7fffffffL);
    limit = (limit < idat_limit) ? (idat_limit) : (limit);
  }
  if (length > limit)
  {
    (void) 0;
    png_benign_error(png_ptr, "chunk data is too large");
  }
}

void png_combine_row(png_const_structrp png_ptr, png_bytep dp, int display)
{
  unsigned int pixel_depth = png_ptr->transformed_pixel_depth;
  png_const_bytep sp = png_ptr->row_buf + 1;
  png_alloc_size_t row_width = png_ptr->width;
  unsigned int pass = png_ptr->pass;
  png_bytep end_ptr = 0;
  png_byte end_byte = 0;
  unsigned int end_mask;
  (void) 0;
  if (pixel_depth == 0)
  {
    png_error(png_ptr, "internal row logic error");
  }
  if ((png_ptr->info_rowbytes != 0) && (png_ptr->info_rowbytes != ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))))
  {
    png_error(png_ptr, "internal row size calculation error");
  }
  if (row_width == 0)
  {
    png_error(png_ptr, "internal row width error");
  }
  end_mask = (pixel_depth * row_width) & 7;
  if (end_mask != 0)
  {
    end_ptr = (dp + ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))) - 1;
    end_byte = *end_ptr;
    end_mask = 0xff >> end_mask;
  }
  if ((((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0)) && (pass < 6)) && ((display == 0) || ((display == 1) && ((pass & 1) != 0))))
  {
    helper_png_combine_row_1(&dp, &pixel_depth, &sp, &row_width, png_ptr, display, pass);
  }
  else
    memcpy(dp, sp, (pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3));
  if (end_ptr != 0)
  {
    *end_ptr = (png_byte) ((end_byte & end_mask) | ((*end_ptr) & (~end_mask)));
  }
}

void png_do_read_interlace(png_row_infop row_info, png_bytep row, int pass, png_uint_32 transformations)
{
  static const unsigned int png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  (void) 0;
  if ((row != 0) && (row_info != 0))
  {
    helper_png_do_read_interlace_1(&row_info, row, pass, png_pass_inc);
  }
  (void) transformations;
}

static void png_read_filter_row_sub(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp = row + bpp;
  (void) prev_row;
  for (i = bpp; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*(rp - bpp)))) & 0xff);
    rp += 1;
  }

}

static void png_read_filter_row_up(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*pp))) & 0xff);
    pp += 1;
    rp += 1;
  }

}

static void png_read_filter_row_avg(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  size_t istop = row_info->rowbytes - bpp;
  for (i = 0; i < bpp; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) (*pp)) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) ((*pp) + (*(rp - bpp)))) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

}

static void png_read_filter_row_paeth_1byte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  png_bytep rp_end = row + row_info->rowbytes;
  int a;
  int c;
  c = *prev_row;
  prev_row += 1;
  a = (*row) + c;
  *row = (png_byte) a;
  row += 1;
  while (row < rp_end)
  {
    helper_png_read_filter_row_paeth_1byte_pixel_1(&row, &prev_row, &a, &c);
  }

}

static void png_read_filter_row_paeth_multibyte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp_end = row + bpp;
  while (row < rp_end)
  {
    int a = (*row) + (*prev_row);
    prev_row += 1;
    *row = (png_byte) a;
    row += 1;
  }

  rp_end = rp_end + (row_info->rowbytes - bpp);
  while (row < rp_end)
  {
    helper_png_read_filter_row_paeth_multibyte_pixel_1(&row, &prev_row, bpp);
  }

}

static void png_init_filter_functions(png_structrp pp)
{
  unsigned int bpp = (pp->pixel_depth + 7) >> 3;
  pp->read_filter[1 - 1] = png_read_filter_row_sub;
  pp->read_filter[2 - 1] = png_read_filter_row_up;
  pp->read_filter[3 - 1] = png_read_filter_row_avg;
  if (bpp == 1)
  {
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_1byte_pixel;
  }
  else
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_multibyte_pixel;
}

void png_read_filter_row(png_structrp pp, png_row_infop row_info, png_bytep row, png_const_bytep prev_row, int filter)
{
  if ((filter > 0) && (filter < 5))
  {
    if (pp->read_filter[0] == 0)
    {
      png_init_filter_functions(pp);
    }
    pp->read_filter[filter - 1](row_info, row, prev_row);
  }
}

void png_read_IDAT_data(png_structrp png_ptr, png_bytep output, png_alloc_size_t avail_out)
{
  png_ptr->zstream.next_out = output;
  png_ptr->zstream.avail_out = 0;
  if (output == 0)
  {
    avail_out = 0;
  }
  do
  {
    helper_png_read_IDAT_data_1(&png_ptr, &avail_out, output);
  }
  while (avail_out > 0);
  if (avail_out > 0)
  {
    if (output != 0)
    {
      png_error(png_ptr, "Not enough image data");
    }
    else
      png_chunk_benign_error(png_ptr, "Too much image data");
  }
}

void png_read_finish_IDAT(png_structrp png_ptr)
{
  if ((png_ptr->flags & 0x0008U) == 0)
  {
    png_read_IDAT_data(png_ptr, 0, 0);
    png_ptr->zstream.next_out = 0;
    if ((png_ptr->flags & 0x0008U) == 0)
    {
      png_ptr->mode |= 0x08;
      png_ptr->flags |= 0x0008U;
    }
  }
  if (png_ptr->zowner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zowner = 0;
    (void) png_crc_finish(png_ptr, png_ptr->idat_size);
  }
}

void png_read_finish_row(png_structrp png_ptr)
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
    memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
    do
    {
      png_ptr->pass += 1;
      if (png_ptr->pass >= 7)
      {
        break;
      }
      png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
      if ((png_ptr->transformations & 0x0002U) == 0)
      {
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
      }
      else
        break;
    }
    while ((png_ptr->num_rows == 0) || (png_ptr->iwidth == 0));
    if (png_ptr->pass < 7)
    {
      return;
    }
  }
  png_read_finish_IDAT(png_ptr);
}

void png_read_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  unsigned int max_pixel_depth;
  size_t row_bytes;
  (void) 0;
  png_init_read_transformations(png_ptr);
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
    }
    else
      png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = png_ptr->width;
  }
  max_pixel_depth = (unsigned int) png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) max_pixel_depth;
  png_ptr->transformed_pixel_depth = 0;
  row_bytes = (png_ptr->width + 7) & (~((png_uint_32) 7));
  row_bytes = (((max_pixel_depth >= 8) ? (((size_t) row_bytes) * (((size_t) max_pixel_depth) >> 3)) : (((((size_t) row_bytes) * ((size_t) max_pixel_depth)) + 7) >> 3)) + 1) + ((max_pixel_depth + 7) >> 3U);
  if ((row_bytes + 48) > png_ptr->old_big_row_buf_size)
  {
    helper_png_read_start_row_1(&png_ptr, row_bytes);
  }
  if (png_ptr->rowbytes > (((size_t) (-1)) - 1))
  {
    png_error(png_ptr, "Row has too many bytes to allocate in memory");
  }
  memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  if (png_ptr->read_buffer != 0)
  {
    png_bytep buffer = png_ptr->read_buffer;
    png_ptr->read_buffer_size = 0;
    png_ptr->read_buffer = 0;
    png_free(png_ptr, buffer);
  }
  if (png_inflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) != 0)
  {
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  png_ptr->flags |= 0x0040U;
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
png_uint_32 png_get_uint_31(png_const_structrp png_ptr, png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if (uval > ((png_uint_32) 0x7fffffffL))
  {
    png_error(png_ptr, "PNG unsigned integer out of range");
  }
  return uval;
}

png_uint_32 png_get_uint_32(png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  return uval;
}

png_int_32 png_get_int_32(png_const_bytep buf)
{
  png_uint_32 uval = (((((png_uint_32) (*buf)) << 24) + (((png_uint_32) (*(buf + 1))) << 16)) + (((png_uint_32) (*(buf + 2))) << 8)) + ((png_uint_32) (*(buf + 3)));
  if ((uval & 0x80000000) == 0)
  {
    return (png_int_32) uval;
  }
  uval = (uval ^ 0xffffffff) + 1;
  if ((uval & 0x80000000) == 0)
  {
    return -((png_int_32) uval);
  }
  return 0;
}

png_uint_16 png_get_uint_16(png_const_bytep buf)
{
  unsigned int val = (((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)));
  return (png_uint_16) val;
}

void png_read_sig(png_structrp png_ptr, png_inforp info_ptr)
{
  size_t num_checked;
  size_t num_to_check;
  if (png_ptr->sig_bytes >= 8)
  {
    return;
  }
  num_checked = png_ptr->sig_bytes;
  num_to_check = 8 - num_checked;
  png_ptr->io_state = 0x0001 | 0x0010;
  png_read_data(png_ptr, &info_ptr->signature[num_checked], num_to_check);
  png_ptr->sig_bytes = 8;
  if (png_sig_cmp(info_ptr->signature, num_checked, num_to_check) != 0)
  {
    if ((num_checked < 4) && png_sig_cmp(info_ptr->signature, num_checked, num_to_check - 4))
    {
      png_error(png_ptr, "Not a PNG file");
    }
    else
      png_error(png_ptr, "PNG file corrupted by ASCII conversion");
  }
  if (num_checked < 3)
  {
    png_ptr->mode |= 0x1000U;
  }
}

png_uint_32 png_read_chunk_header(png_structrp png_ptr)
{
  png_byte buf[8];
  png_uint_32 length;
  png_ptr->io_state = 0x0001 | 0x0020;
  png_read_data(png_ptr, buf, 8);
  length = png_get_uint_31(png_ptr, buf);
  png_ptr->chunk_name = (((((png_uint_32) (0xff & (buf + 4)[0])) << 24) | (((png_uint_32) (0xff & (buf + 4)[1])) << 16)) | (((png_uint_32) (0xff & (buf + 4)[2])) << 8)) | (((png_uint_32) (0xff & (buf + 4)[3])) << 0);
  (void) 0;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_check_chunk_name(png_ptr, png_ptr->chunk_name);
  png_check_chunk_length(png_ptr, length);
  png_ptr->io_state = 0x0001 | 0x0040;
  return length;
}

void png_crc_read(png_structrp png_ptr, png_bytep buf, png_uint_32 length)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_read_data(png_ptr, buf, length);
  png_calculate_crc(png_ptr, buf, length);
}

int png_crc_finish(png_structrp png_ptr, png_uint_32 skip)
{
  while (skip > 0)
  {
    png_uint_32 len;
    png_byte tmpbuf[1024];
    len = sizeof(tmpbuf);
    if (len > skip)
    {
      len = skip;
    }
    skip -= len;
    png_crc_read(png_ptr, tmpbuf, len);
  }

  if (png_crc_error(png_ptr) != 0)
  {
    if (((1 & (png_ptr->chunk_name >> 29)) != 0) ? ((png_ptr->flags & 0x0200U) == 0) : ((png_ptr->flags & 0x0400U) != 0))
    {
      png_chunk_warning(png_ptr, "CRC error");
    }
    else
      png_chunk_error(png_ptr, "CRC error");
    return 1;
  }
  return 0;
}

int png_crc_error(png_structrp png_ptr)
{
  png_byte crc_bytes[4];
  png_uint_32 crc;
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
  png_ptr->io_state = 0x0001 | 0x0080;
  png_read_data(png_ptr, crc_bytes, 4);
  if (need_crc != 0)
  {
    crc = (((((png_uint_32) (*crc_bytes)) << 24) + (((png_uint_32) (*(crc_bytes + 1))) << 16)) + (((png_uint_32) (*(crc_bytes + 2))) << 8)) + ((png_uint_32) (*(crc_bytes + 3)));
    return (int) (crc != png_ptr->crc);
  }
  else
    return 0;
}

static png_bytep png_read_buffer(png_structrp png_ptr, png_alloc_size_t new_size, int warn)
{
  png_bytep buffer = png_ptr->read_buffer;
  if ((buffer != 0) && (new_size > png_ptr->read_buffer_size))
  {
    png_ptr->read_buffer = 0;
    png_ptr->read_buffer_size = 0;
    png_free(png_ptr, buffer);
    buffer = 0;
  }
  if (buffer == 0)
  {
    buffer = png_malloc_base(png_ptr, new_size);
    if (buffer != 0)
    {
      memset(buffer, 0, new_size);
      png_ptr->read_buffer = buffer;
      png_ptr->read_buffer_size = new_size;
    }
    else
      if (warn < 2)
    {
      if (warn != 0)
      {
        png_chunk_warning(png_ptr, "insufficient memory to read chunk");
      }
      else
        png_chunk_error(png_ptr, "insufficient memory to read chunk");
    }
  }
  return buffer;
}

static int png_inflate_claim(png_structrp png_ptr, png_uint_32 owner)
{
  if (png_ptr->zowner != 0)
  {
    char msg[64];
    (void) ((((char *) msg)[0] = (char) ((png_ptr->zowner >> 24) & 0xff), ((char *) msg)[1] = (char) ((png_ptr->zowner >> 16) & 0xff), ((char *) msg)[2] = (char) ((png_ptr->zowner >> 8) & 0xff), ((char *) msg)[3] = (char) (png_ptr->zowner & 0xff)));
    (void) png_safecat(msg, sizeof(msg), 4, " using zstream");
    png_chunk_warning(png_ptr, msg);
    png_ptr->zowner = 0;
  }
  {
    int ret;
    int window_bits = 0;
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zstream.next_out = 0;
    png_ptr->zstream.avail_out = 0;
    if ((png_ptr->flags & 0x0002U) != 0)
    {
      ret = inflateReset2(&png_ptr->zstream, window_bits);
    }
    else
    {
      ret = inflateInit2_(&png_ptr->zstream, window_bits, "1.3-optipng", (int) (sizeof(z_stream)));
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

int png_zlib_inflate(png_structrp png_ptr, int flush)
{
  if (png_ptr->zstream_start && (png_ptr->zstream.avail_in > 0))
  {
    if (((*png_ptr->zstream.next_in) >> 4) > 7)
    {
      png_ptr->zstream.msg = "invalid window size (libpng)";
      return -3;
    }
    png_ptr->zstream_start = 0;
  }
  return inflate(&png_ptr->zstream, flush);
}

void png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte buf[13];
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int interlace_type;
  (void) 0;
  if ((png_ptr->mode & 0x01) != 0)
  {
    png_chunk_error(png_ptr, "out of place");
  }
  if (length != 13)
  {
    png_chunk_error(png_ptr, "invalid");
  }
  png_ptr->mode |= 0x01;
  png_crc_read(png_ptr, buf, 13);
  png_crc_finish(png_ptr, 0);
  width = png_get_uint_31(png_ptr, buf);
  height = png_get_uint_31(png_ptr, buf + 4);
  bit_depth = buf[8];
  color_type = buf[9];
  compression_type = buf[10];
  filter_type = buf[11];
  interlace_type = buf[12];
  png_ptr->width = width;
  png_ptr->height = height;
  png_ptr->bit_depth = (png_byte) bit_depth;
  png_ptr->interlaced = (png_byte) interlace_type;
  png_ptr->color_type = (png_byte) color_type;
  png_ptr->compression_type = (png_byte) compression_type;
  switch (png_ptr->color_type)
  {
    default:

    case 0:

    case 2 | 1:
      png_ptr->channels = 1;
      break;

    case 2:
      png_ptr->channels = 3;
      break;

    case 4:
      png_ptr->channels = 2;
      break;

    case 2 | 4:
      png_ptr->channels = 4;
      break;

  }

  png_ptr->pixel_depth = (png_byte) (png_ptr->bit_depth * png_ptr->channels);
  png_ptr->rowbytes = (png_ptr->pixel_depth >= 8) ? (((size_t) png_ptr->width) * (((size_t) png_ptr->pixel_depth) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) png_ptr->pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}

void png_handle_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_color palette[256];
  int max_palette_length;
  int num;
  int i;
  png_colorp pal_ptr;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x02) != 0)
  {
    png_chunk_error(png_ptr, "duplicate");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  png_ptr->mode |= 0x02;
  if ((png_ptr->color_type & 2) == 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "ignored in grayscale PNG");
    return;
  }
  if ((length > (3 * 256)) || (length % 3))
  {
    png_crc_finish(png_ptr, length);
    if (png_ptr->color_type != (2 | 1))
    {
      png_chunk_benign_error(png_ptr, "invalid");
    }
    else
      png_chunk_error(png_ptr, "invalid");
    return;
  }
  num = ((int) length) / 3;
  if (png_ptr->color_type == (2 | 1))
  {
    max_palette_length = 1 << png_ptr->bit_depth;
  }
  else
    max_palette_length = 256;
  if (num > max_palette_length)
  {
    num = max_palette_length;
  }
  for (i = 0, pal_ptr = palette; i < num; i += 1, pal_ptr += 1)
  {
    png_byte buf[3];
    png_crc_read(png_ptr, buf, 3);
    pal_ptr->red = buf[0];
    pal_ptr->green = buf[1];
    pal_ptr->blue = buf[2];
  }

  {
    png_crc_finish(png_ptr, (png_uint_32) (length - (((unsigned int) num) * 3)));
  }
  png_set_PLTE(png_ptr, info_ptr, palette, num);
  if ((png_ptr->num_trans > 0) || ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0)))
  {
    png_ptr->num_trans = 0;
    if (info_ptr != 0)
    {
      info_ptr->num_trans = 0;
    }
    png_chunk_benign_error(png_ptr, "tRNS must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_chunk_benign_error(png_ptr, "hIST must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_chunk_benign_error(png_ptr, "bKGD must be after");
  }
}

void png_handle_IEND(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  (void) 0;
  if (((png_ptr->mode & 0x01) == 0) || ((png_ptr->mode & 0x04U) == 0))
  {
    png_chunk_error(png_ptr, "out of place");
  }
  png_ptr->mode |= 0x08 | 0x10U;
  png_crc_finish(png_ptr, length);
  if (length != 0)
  {
    png_chunk_benign_error(png_ptr, "invalid");
  }
  (void) info_ptr;
}

void png_handle_sBIT(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  unsigned int i;
  png_byte sample_depth;
  png_byte buf[4];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & (0x04U | 0x02)) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0002U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 3;
    sample_depth = 8;
  }
  else
  {
    truelen = png_ptr->channels;
    sample_depth = png_ptr->bit_depth;
  }
  if ((length != truelen) || (length > 4))
  {
    png_chunk_benign_error(png_ptr, "invalid");
    png_crc_finish(png_ptr, length);
    return;
  }
  buf[0] = (buf[1] = (buf[2] = (buf[3] = sample_depth)));
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  for (i = 0; i < truelen; i += 1)
  {
    if ((buf[i] == 0) || (buf[i] > sample_depth))
    {
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
  }

  if ((png_ptr->color_type & 2) != 0)
  {
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[1];
    png_ptr->sig_bit.blue = buf[2];
    png_ptr->sig_bit.alpha = buf[3];
  }
  else
  {
    png_ptr->sig_bit.gray = buf[0];
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[0];
    png_ptr->sig_bit.blue = buf[0];
    png_ptr->sig_bit.alpha = buf[1];
  }
  png_set_sBIT(png_ptr, info_ptr, &png_ptr->sig_bit);
}

void png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == 0)
  {
    png_byte buf[2];
    if (length != 2)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, 2);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }
  else
    if (png_ptr->color_type == 2)
  {
    png_byte buf[6];
    if (length != 6)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, length);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    png_ptr->trans_color.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    png_ptr->trans_color.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
  }
  else
    if (png_ptr->color_type == (2 | 1))
  {
    if ((png_ptr->mode & 0x02) == 0)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
    }
    if (((length > ((unsigned int) png_ptr->num_palette)) || (length > ((unsigned int) 256))) || (length == 0))
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, readbuf, length);
    png_ptr->num_trans = (png_uint_16) length;
  }
  else
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid with alpha channel");
    return;
  }
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    png_ptr->num_trans = 0;
    return;
  }
  png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans, &png_ptr->trans_color);
}

void png_handle_bKGD(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  png_byte buf[6];
  png_color_16 background;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->color_type == (2 | 1)) && ((png_ptr->mode & 0x02) == 0)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 1;
  }
  else
    if ((png_ptr->color_type & 2) != 0)
  {
    truelen = 6;
  }
  else
    truelen = 2;
  if (length != truelen)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    background.index = buf[0];
    if ((info_ptr != 0) && (info_ptr->num_palette != 0))
    {
      if (buf[0] >= info_ptr->num_palette)
      {
        png_chunk_benign_error(png_ptr, "invalid index");
        return;
      }
      background.red = (png_uint_16) png_ptr->palette[buf[0]].red;
      background.green = (png_uint_16) png_ptr->palette[buf[0]].green;
      background.blue = (png_uint_16) png_ptr->palette[buf[0]].blue;
    }
    else
      background.red = (background.green = (background.blue = 0));
    background.gray = 0;
  }
  else
    if ((png_ptr->color_type & 2) == 0)
  {
    if (png_ptr->bit_depth <= 8)
    {
      if ((buf[0] != 0) || (buf[1] >= ((unsigned int) (1 << png_ptr->bit_depth))))
      {
        png_chunk_benign_error(png_ptr, "invalid gray level");
        return;
      }
    }
    background.index = 0;
    background.red = (background.green = (background.blue = (background.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)))))));
  }
  else
  {
    if (png_ptr->bit_depth <= 8)
    {
      if (((buf[0] != 0) || (buf[2] != 0)) || (buf[4] != 0))
      {
        png_chunk_benign_error(png_ptr, "invalid color");
        return;
      }
    }
    background.index = 0;
    background.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    background.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    background.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
    background.gray = 0;
  }
  png_set_bKGD(png_ptr, info_ptr, &background);
}

void png_handle_hIST(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int num;
  unsigned int i;
  png_uint_16 readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->mode & 0x02) == 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  num = length / 2;
  if (((length != (num * 2)) || (num != ((unsigned int) png_ptr->num_palette))) || (num > ((unsigned int) 256)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  for (i = 0; i < num; i += 1)
  {
    png_byte buf[2];
    png_crc_read(png_ptr, buf, 2);
    readbuf[i] = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }

  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  png_set_hIST(png_ptr, info_ptr, readbuf);
}

static int png_cache_unknown_chunk(png_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (size_t) (-1);
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
    png_ptr->unknown_chunk.data = 0;
  }
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (length <= limit)
  {
    (void) (((void) ((((char *) png_ptr->unknown_chunk.name)[0] = (char) ((png_ptr->chunk_name >> 24) & 0xff), ((char *) png_ptr->unknown_chunk.name)[1] = (char) ((png_ptr->chunk_name >> 16) & 0xff), ((char *) png_ptr->unknown_chunk.name)[2] = (char) ((png_ptr->chunk_name >> 8) & 0xff), ((char *) png_ptr->unknown_chunk.name)[3] = (char) (png_ptr->chunk_name & 0xff))), ((char *) png_ptr->unknown_chunk.name)[4] = 0));
    png_ptr->unknown_chunk.size = (size_t) length;
    png_ptr->unknown_chunk.location = (png_byte) png_ptr->mode;
    if (length == 0)
    {
      png_ptr->unknown_chunk.data = 0;
    }
    else
    {
      png_ptr->unknown_chunk.data = png_malloc_warn(png_ptr, length);
    }
  }
  if ((png_ptr->unknown_chunk.data == 0) && (length > 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "unknown chunk exceeds memory limits");
    return 0;
  }
  else
  {
    if (length > 0)
    {
      png_crc_read(png_ptr, png_ptr->unknown_chunk.data, length);
    }
    png_crc_finish(png_ptr, 0);
    return 1;
  }
}

void png_handle_unknown(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length, int keep)
{
  int handled = 0;
  (void) 0;
  {
    if (keep == 0)
    {
      keep = png_ptr->unknown_default;
    }
    if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
    {
      if (png_cache_unknown_chunk(png_ptr, length) == 0)
      {
        keep = 1;
      }
    }
    else
      png_crc_finish(png_ptr, length);
  }
  if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
  {
    switch (png_ptr->user_chunk_cache_max)
    {
      case 2:
        png_ptr->user_chunk_cache_max = 1;
        png_chunk_benign_error(png_ptr, "no space in chunk cache");

      case 1:
        break;

      default:
        png_ptr->user_chunk_cache_max -= 1;

      case 0:
        png_set_unknown_chunks(png_ptr, info_ptr, &png_ptr->unknown_chunk, 1);
        handled = 1;
        break;

    }

  }
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
  }
  png_ptr->unknown_chunk.data = 0;
  if ((handled == 0) && (!(1 & (png_ptr->chunk_name >> 29))))
  {
    png_chunk_error(png_ptr, "unhandled critical chunk");
  }
}

void png_check_chunk_name(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  int i;
  png_uint_32 cn = chunk_name;
  (void) 0;
  for (i = 1; i <= 4; i += 1)
  {
    int c = cn & 0xff;
    if (((c < 65) || (c > 122)) || ((c > 90) && (c < 97)))
    {
      png_chunk_error(png_ptr, "invalid chunk type");
    }
    cn >>= 8;
  }

}

void png_check_chunk_length(png_const_structrp png_ptr, png_uint_32 length)
{
  png_alloc_size_t limit = (png_uint_32) 0x7fffffffL;
  if ((png_ptr->user_chunk_malloc_max > 0) && (png_ptr->user_chunk_malloc_max < limit))
  {
    limit = png_ptr->user_chunk_malloc_max;
  }
  if (png_ptr->chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_alloc_size_t idat_limit = (png_uint_32) 0x7fffffffL;
    size_t row_factor = (((((size_t) png_ptr->width) * ((size_t) png_ptr->channels)) * ((png_ptr->bit_depth > 8) ? (2) : (1))) + 1) + ((png_ptr->interlaced) ? (6) : (0));
    if (png_ptr->height > (((png_uint_32) (-1)) / row_factor))
    {
      idat_limit = (png_uint_32) 0x7fffffffL;
    }
    else
      idat_limit = png_ptr->height * row_factor;
    row_factor = (row_factor > 32566) ? (32566) : (row_factor);
    idat_limit += 6 + (5 * ((idat_limit / row_factor) + 1));
    idat_limit = (idat_limit < ((png_uint_32) 0x7fffffffL)) ? (idat_limit) : ((png_uint_32) 0x7fffffffL);
    limit = (limit < idat_limit) ? (idat_limit) : (limit);
  }
  if (length > limit)
  {
    (void) 0;
    png_benign_error(png_ptr, "chunk data is too large");
  }
}

void png_combine_row(png_const_structrp png_ptr, png_bytep dp, int display)
{
  unsigned int pixel_depth = png_ptr->transformed_pixel_depth;
  png_const_bytep sp = png_ptr->row_buf + 1;
  png_alloc_size_t row_width = png_ptr->width;
  unsigned int pass = png_ptr->pass;
  png_bytep end_ptr = 0;
  png_byte end_byte = 0;
  unsigned int end_mask;
  (void) 0;
  if (pixel_depth == 0)
  {
    png_error(png_ptr, "internal row logic error");
  }
  if ((png_ptr->info_rowbytes != 0) && (png_ptr->info_rowbytes != ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))))
  {
    png_error(png_ptr, "internal row size calculation error");
  }
  if (row_width == 0)
  {
    png_error(png_ptr, "internal row width error");
  }
  end_mask = (pixel_depth * row_width) & 7;
  if (end_mask != 0)
  {
    end_ptr = (dp + ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))) - 1;
    end_byte = *end_ptr;
    end_mask = 0xff >> end_mask;
  }
  if ((((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0)) && (pass < 6)) && ((display == 0) || ((display == 1) && ((pass & 1) != 0))))
  {
    if (row_width <= (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))
    {
      return;
    }
    if (pixel_depth < 8)
    {
      static const png_uint_32 row_mask[2][3][6] = {{{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
      static const png_uint_32 display_mask[2][3][3] = {{{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
      png_uint_32 pixels_per_byte = 8 / pixel_depth;
      png_uint_32 mask;
      mask = (display) ? (display_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass >> 1]) : (row_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass]);
      for (;;)
      {
        png_uint_32 m;
        m = mask;
        mask = (m >> 8) | (m << 24);
        m &= 0xff;
        if (m != 0)
        {
          if (m != 0xff)
          {
            *dp = (png_byte) (((*dp) & (~m)) | ((*sp) & m));
          }
          else
            *dp = *sp;
        }
        if (row_width <= pixels_per_byte)
        {
          break;
        }
        row_width -= pixels_per_byte;
        dp += 1;
        sp += 1;
      }

    }
    else
    {
      unsigned int bytes_to_copy;
      unsigned int bytes_to_jump;
      if (pixel_depth & 7)
      {
        png_error(png_ptr, "invalid user transform pixel depth");
      }
      pixel_depth >>= 3;
      row_width *= pixel_depth;
      {
        unsigned int offset = (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7) * pixel_depth;
        row_width -= offset;
        dp += offset;
        sp += offset;
      }
      if (display != 0)
      {
        bytes_to_copy = (1 << ((6 - pass) >> 1)) * pixel_depth;
        if (bytes_to_copy > row_width)
        {
          bytes_to_copy = (unsigned int) row_width;
        }
      }
      else
        bytes_to_copy = pixel_depth;
      bytes_to_jump = (1 << ((7 - pass) >> 1)) * pixel_depth;
      switch (bytes_to_copy)
      {
        case 1:
          for (;;)
        {
          *dp = *sp;
          if (row_width <= bytes_to_jump)
          {
            return;
          }
          dp += bytes_to_jump;
          sp += bytes_to_jump;
          row_width -= bytes_to_jump;
        }


        case 2:
          do
        {
          dp[0] = sp[0];
          dp[1] = sp[1];
          if (row_width <= bytes_to_jump)
          {
            return;
          }
          sp += bytes_to_jump;
          dp += bytes_to_jump;
          row_width -= bytes_to_jump;
        }
        while (row_width > 1);
          *dp = *sp;
          return;

        case 3:
          for (;;)
        {
          dp[0] = sp[0];
          dp[1] = sp[1];
          dp[2] = sp[2];
          if (row_width <= bytes_to_jump)
          {
            return;
          }
          sp += bytes_to_jump;
          dp += bytes_to_jump;
          row_width -= bytes_to_jump;
        }


        default:
          if (((((bytes_to_copy < 16) && ((((png_uint_16) ((size_t) ((const void *) dp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((((png_uint_16) ((size_t) ((const void *) sp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_16))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_16))) == 0))
        {
          if (((((((png_uint_32) ((size_t) ((const void *) dp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0) && ((((png_uint_32) ((size_t) ((const void *) sp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_32))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_32))) == 0))
          {
            png_uint_32p dp32 = (void *) dp;
            png_const_uint_32p sp32 = (const void *) sp;
            size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_32));
            do
            {
              size_t c = bytes_to_copy;
              do
              {
                *dp32 = *sp32;
                sp32 += 1;
                dp32 += 1;
                c -= sizeof(png_uint_32);
              }
              while (c > 0);
              if (row_width <= bytes_to_jump)
              {
                return;
              }
              dp32 += skip;
              sp32 += skip;
              row_width -= bytes_to_jump;
            }
            while (bytes_to_copy <= row_width);
            dp = (png_bytep) dp32;
            sp = (png_const_bytep) sp32;
            do
            {
              *dp = *sp;
              sp += 1;
              dp += 1;
            }
            while ((--row_width) > 0);
            return;
          }
          else
          {
            png_uint_16p dp16 = (void *) dp;
            png_const_uint_16p sp16 = (const void *) sp;
            size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_16));
            do
            {
              size_t c = bytes_to_copy;
              do
              {
                *dp16 = *sp16;
                sp16 += 1;
                dp16 += 1;
                c -= sizeof(png_uint_16);
              }
              while (c > 0);
              if (row_width <= bytes_to_jump)
              {
                return;
              }
              dp16 += skip;
              sp16 += skip;
              row_width -= bytes_to_jump;
            }
            while (bytes_to_copy <= row_width);
            dp = (png_bytep) dp16;
            sp = (png_const_bytep) sp16;
            do
            {
              *dp = *sp;
              sp += 1;
              dp += 1;
            }
            while ((--row_width) > 0);
            return;
          }
        }
          for (;;)
        {
          memcpy(dp, sp, bytes_to_copy);
          if (row_width <= bytes_to_jump)
          {
            return;
          }
          sp += bytes_to_jump;
          dp += bytes_to_jump;
          row_width -= bytes_to_jump;
          if (bytes_to_copy > row_width)
          {
            bytes_to_copy = (unsigned int) row_width;
          }
        }


      }

    }
  }
  else
    memcpy(dp, sp, (pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3));
  if (end_ptr != 0)
  {
    *end_ptr = (png_byte) ((end_byte & end_mask) | ((*end_ptr) & (~end_mask)));
  }
}

void png_do_read_interlace(png_row_infop row_info, png_bytep row, int pass, png_uint_32 transformations)
{
  static const unsigned int png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  (void) 0;
  if ((row != 0) && (row_info != 0))
  {
    png_uint_32 final_width;
    final_width = row_info->width * png_pass_inc[pass];
    switch (row_info->pixel_depth)
    {
      case 1:
      {
        png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 3));
        png_bytep dp = row + ((size_t) ((final_width - 1) >> 3));
        unsigned int sshift;
        unsigned int dshift;
        unsigned int s_start;
        unsigned int s_end;
        int s_inc;
        int jstop = (int) png_pass_inc[pass];
        png_byte v;
        png_uint_32 i;
        int j;
        {
          sshift = 7 - ((row_info->width + 7) & 0x07);
          dshift = 7 - ((final_width + 7) & 0x07);
          s_start = 0;
          s_end = 7;
          s_inc = 1;
        }
        for (i = 0; i < row_info->width; i += 1)
        {
          v = (png_byte) (((*sp) >> sshift) & 0x01);
          for (j = 0; j < jstop; j += 1)
          {
            unsigned int tmp = (*dp) & (0x7f7f >> (7 - dshift));
            tmp |= (unsigned int) (v << dshift);
            *dp = (png_byte) (tmp & 0xff);
            if (dshift == s_end)
            {
              dshift = s_start;
              dp -= 1;
            }
            else
              dshift = (unsigned int) (((int) dshift) + s_inc);
          }

          if (sshift == s_end)
          {
            sshift = s_start;
            sp -= 1;
          }
          else
            sshift = (unsigned int) (((int) sshift) + s_inc);
        }

        break;
      }

      case 2:
      {
        png_bytep sp = row + ((png_uint_32) ((row_info->width - 1) >> 2));
        png_bytep dp = row + ((png_uint_32) ((final_width - 1) >> 2));
        unsigned int sshift;
        unsigned int dshift;
        unsigned int s_start;
        unsigned int s_end;
        int s_inc;
        int jstop = (int) png_pass_inc[pass];
        png_uint_32 i;
        {
          sshift = (3 - ((row_info->width + 3) & 0x03)) << 1;
          dshift = (3 - ((final_width + 3) & 0x03)) << 1;
          s_start = 0;
          s_end = 6;
          s_inc = 2;
        }
        for (i = 0; i < row_info->width; i += 1)
        {
          png_byte v;
          int j;
          v = (png_byte) (((*sp) >> sshift) & 0x03);
          for (j = 0; j < jstop; j += 1)
          {
            unsigned int tmp = (*dp) & (0x3f3f >> (6 - dshift));
            tmp |= (unsigned int) (v << dshift);
            *dp = (png_byte) (tmp & 0xff);
            if (dshift == s_end)
            {
              dshift = s_start;
              dp -= 1;
            }
            else
              dshift = (unsigned int) (((int) dshift) + s_inc);
          }

          if (sshift == s_end)
          {
            sshift = s_start;
            sp -= 1;
          }
          else
            sshift = (unsigned int) (((int) sshift) + s_inc);
        }

        break;
      }

      case 4:
      {
        png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 1));
        png_bytep dp = row + ((size_t) ((final_width - 1) >> 1));
        unsigned int sshift;
        unsigned int dshift;
        unsigned int s_start;
        unsigned int s_end;
        int s_inc;
        png_uint_32 i;
        int jstop = (int) png_pass_inc[pass];
        {
          sshift = (1 - ((row_info->width + 1) & 0x01)) << 2;
          dshift = (1 - ((final_width + 1) & 0x01)) << 2;
          s_start = 0;
          s_end = 4;
          s_inc = 4;
        }
        for (i = 0; i < row_info->width; i += 1)
        {
          png_byte v = (png_byte) (((*sp) >> sshift) & 0x0f);
          int j;
          for (j = 0; j < jstop; j += 1)
          {
            unsigned int tmp = (*dp) & (0xf0f >> (4 - dshift));
            tmp |= (unsigned int) (v << dshift);
            *dp = (png_byte) (tmp & 0xff);
            if (dshift == s_end)
            {
              dshift = s_start;
              dp -= 1;
            }
            else
              dshift = (unsigned int) (((int) dshift) + s_inc);
          }

          if (sshift == s_end)
          {
            sshift = s_start;
            sp -= 1;
          }
          else
            sshift = (unsigned int) (((int) sshift) + s_inc);
        }

        break;
      }

      default:
      {
        size_t pixel_bytes = row_info->pixel_depth >> 3;
        png_bytep sp = row + (((size_t) (row_info->width - 1)) * pixel_bytes);
        png_bytep dp = row + (((size_t) (final_width - 1)) * pixel_bytes);
        int jstop = (int) png_pass_inc[pass];
        png_uint_32 i;
        for (i = 0; i < row_info->width; i += 1)
        {
          png_byte v[8];
          int j;
          memcpy(v, sp, pixel_bytes);
          for (j = 0; j < jstop; j += 1)
          {
            memcpy(dp, v, pixel_bytes);
            dp -= pixel_bytes;
          }

          sp -= pixel_bytes;
        }

        break;
      }

    }

    row_info->width = final_width;
    row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) final_width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) final_width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  }
  (void) transformations;
}

static void png_read_filter_row_sub(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp = row + bpp;
  (void) prev_row;
  for (i = bpp; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*(rp - bpp)))) & 0xff);
    rp += 1;
  }

}

static void png_read_filter_row_up(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  size_t istop = row_info->rowbytes;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + ((int) (*pp))) & 0xff);
    pp += 1;
    rp += 1;
  }

}

static void png_read_filter_row_avg(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  size_t i;
  png_bytep rp = row;
  png_const_bytep pp = prev_row;
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  size_t istop = row_info->rowbytes - bpp;
  for (i = 0; i < bpp; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) (*pp)) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

  for (i = 0; i < istop; i += 1)
  {
    *rp = (png_byte) ((((int) (*rp)) + (((int) ((*pp) + (*(rp - bpp)))) / 2)) & 0xff);
    pp += 1;
    rp += 1;
  }

}

static void png_read_filter_row_paeth_1byte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  png_bytep rp_end = row + row_info->rowbytes;
  int a;
  int c;
  c = *prev_row;
  prev_row += 1;
  a = (*row) + c;
  *row = (png_byte) a;
  row += 1;
  while (row < rp_end)
  {
    int b;
    int pa;
    int pb;
    int pc;
    int p;
    a &= 0xff;
    b = *prev_row;
    prev_row += 1;
    p = b - c;
    pc = a - c;
    pa = (p < 0) ? (-p) : (p);
    pb = (pc < 0) ? (-pc) : (pc);
    pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
    if (pb < pa)
    {
      pa = pb;
      a = b;
    }
    if (pc < pa)
    {
      a = c;
    }
    c = b;
    a += *row;
    *row = (png_byte) a;
    row += 1;
  }

}

static void png_read_filter_row_paeth_multibyte_pixel(png_row_infop row_info, png_bytep row, png_const_bytep prev_row)
{
  unsigned int bpp = (row_info->pixel_depth + 7) >> 3;
  png_bytep rp_end = row + bpp;
  while (row < rp_end)
  {
    int a = (*row) + (*prev_row);
    prev_row += 1;
    *row = (png_byte) a;
    row += 1;
  }

  rp_end = rp_end + (row_info->rowbytes - bpp);
  while (row < rp_end)
  {
    int a;
    int b;
    int c;
    int pa;
    int pb;
    int pc;
    int p;
    c = *(prev_row - bpp);
    a = *(row - bpp);
    b = *prev_row;
    prev_row += 1;
    p = b - c;
    pc = a - c;
    pa = (p < 0) ? (-p) : (p);
    pb = (pc < 0) ? (-pc) : (pc);
    pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
    if (pb < pa)
    {
      pa = pb;
      a = b;
    }
    if (pc < pa)
    {
      a = c;
    }
    a += *row;
    *row = (png_byte) a;
    row += 1;
  }

}

static void png_init_filter_functions(png_structrp pp)
{
  unsigned int bpp = (pp->pixel_depth + 7) >> 3;
  pp->read_filter[1 - 1] = png_read_filter_row_sub;
  pp->read_filter[2 - 1] = png_read_filter_row_up;
  pp->read_filter[3 - 1] = png_read_filter_row_avg;
  if (bpp == 1)
  {
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_1byte_pixel;
  }
  else
    pp->read_filter[4 - 1] = png_read_filter_row_paeth_multibyte_pixel;
}

void png_read_filter_row(png_structrp pp, png_row_infop row_info, png_bytep row, png_const_bytep prev_row, int filter)
{
  if ((filter > 0) && (filter < 5))
  {
    if (pp->read_filter[0] == 0)
    {
      png_init_filter_functions(pp);
    }
    pp->read_filter[filter - 1](row_info, row, prev_row);
  }
}

void png_read_IDAT_data(png_structrp png_ptr, png_bytep output, png_alloc_size_t avail_out)
{
  png_ptr->zstream.next_out = output;
  png_ptr->zstream.avail_out = 0;
  if (output == 0)
  {
    avail_out = 0;
  }
  do
  {
    int ret;
    png_byte tmpbuf[1024];
    if (png_ptr->zstream.avail_in == 0)
    {
      uInt avail_in;
      png_bytep buffer;
      while (png_ptr->idat_size == 0)
      {
        png_crc_finish(png_ptr, 0);
        png_ptr->idat_size = png_read_chunk_header(png_ptr);
        if (png_ptr->chunk_name != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
        {
          png_error(png_ptr, "Not enough image data");
        }
      }

      avail_in = png_ptr->IDAT_read_size;
      if (avail_in > png_ptr->idat_size)
      {
        avail_in = (uInt) png_ptr->idat_size;
      }
      buffer = png_read_buffer(png_ptr, avail_in, 0);
      png_crc_read(png_ptr, buffer, avail_in);
      png_ptr->idat_size -= avail_in;
      png_ptr->zstream.next_in = buffer;
      png_ptr->zstream.avail_in = avail_in;
    }
    if (output != 0)
    {
      uInt out = (uInt) (-1);
      if (out > avail_out)
      {
        out = (uInt) avail_out;
      }
      avail_out -= out;
      png_ptr->zstream.avail_out = out;
    }
    else
    {
      png_ptr->zstream.next_out = tmpbuf;
      png_ptr->zstream.avail_out = sizeof(tmpbuf);
    }
    ret = png_zlib_inflate(png_ptr, 0);
    if (output != 0)
    {
      avail_out += png_ptr->zstream.avail_out;
    }
    else
      avail_out += (sizeof(tmpbuf)) - png_ptr->zstream.avail_out;
    png_ptr->zstream.avail_out = 0;
    if (ret == 1)
    {
      png_ptr->zstream.next_out = 0;
      png_ptr->mode |= 0x08;
      png_ptr->flags |= 0x0008U;
      if ((png_ptr->zstream.avail_in > 0) || (png_ptr->idat_size > 0))
      {
        png_chunk_benign_error(png_ptr, "Extra compressed data");
      }
      break;
    }
    if (ret != 0)
    {
      png_zstream_error(png_ptr, ret);
      if (output != 0)
      {
        png_chunk_error(png_ptr, png_ptr->zstream.msg);
      }
      else
      {
        png_chunk_benign_error(png_ptr, png_ptr->zstream.msg);
        return;
      }
    }
  }
  while (avail_out > 0);
  if (avail_out > 0)
  {
    if (output != 0)
    {
      png_error(png_ptr, "Not enough image data");
    }
    else
      png_chunk_benign_error(png_ptr, "Too much image data");
  }
}

void png_read_finish_IDAT(png_structrp png_ptr)
{
  if ((png_ptr->flags & 0x0008U) == 0)
  {
    png_read_IDAT_data(png_ptr, 0, 0);
    png_ptr->zstream.next_out = 0;
    if ((png_ptr->flags & 0x0008U) == 0)
    {
      png_ptr->mode |= 0x08;
      png_ptr->flags |= 0x0008U;
    }
  }
  if (png_ptr->zowner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zowner = 0;
    (void) png_crc_finish(png_ptr, png_ptr->idat_size);
  }
}

void png_read_finish_row(png_structrp png_ptr)
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
    memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
    do
    {
      png_ptr->pass += 1;
      if (png_ptr->pass >= 7)
      {
        break;
      }
      png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
      if ((png_ptr->transformations & 0x0002U) == 0)
      {
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
      }
      else
        break;
    }
    while ((png_ptr->num_rows == 0) || (png_ptr->iwidth == 0));
    if (png_ptr->pass < 7)
    {
      return;
    }
  }
  png_read_finish_IDAT(png_ptr);
}

void png_read_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  unsigned int max_pixel_depth;
  size_t row_bytes;
  (void) 0;
  png_init_read_transformations(png_ptr);
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
    }
    else
      png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = png_ptr->width;
  }
  max_pixel_depth = (unsigned int) png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) max_pixel_depth;
  png_ptr->transformed_pixel_depth = 0;
  row_bytes = (png_ptr->width + 7) & (~((png_uint_32) 7));
  row_bytes = (((max_pixel_depth >= 8) ? (((size_t) row_bytes) * (((size_t) max_pixel_depth) >> 3)) : (((((size_t) row_bytes) * ((size_t) max_pixel_depth)) + 7) >> 3)) + 1) + ((max_pixel_depth + 7) >> 3U);
  if ((row_bytes + 48) > png_ptr->old_big_row_buf_size)
  {
    png_free(png_ptr, png_ptr->big_row_buf);
    png_free(png_ptr, png_ptr->big_prev_row);
    if (png_ptr->interlaced != 0)
    {
      png_ptr->big_row_buf = (png_bytep) png_calloc(png_ptr, row_bytes + 48);
    }
    else
      png_ptr->big_row_buf = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
    png_ptr->big_prev_row = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
    {
      png_bytep temp = png_ptr->big_row_buf + 32;
      size_t extra = ((size_t) temp) & 0x0f;
      png_ptr->row_buf = (temp - extra) - 1;
      temp = png_ptr->big_prev_row + 32;
      extra = ((size_t) temp) & 0x0f;
      png_ptr->prev_row = (temp - extra) - 1;
    }
    png_ptr->old_big_row_buf_size = row_bytes + 48;
  }
  if (png_ptr->rowbytes > (((size_t) (-1)) - 1))
  {
    png_error(png_ptr, "Row has too many bytes to allocate in memory");
  }
  memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  if (png_ptr->read_buffer != 0)
  {
    png_bytep buffer = png_ptr->read_buffer;
    png_ptr->read_buffer_size = 0;
    png_ptr->read_buffer = 0;
    png_free(png_ptr, buffer);
  }
  if (png_inflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) != 0)
  {
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  png_ptr->flags |= 0x0040U;
}

void helper_png_combine_row_1(png_bytep * const dp_ref, unsigned int * const pixel_depth_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, png_const_structrp png_ptr, int display, unsigned int pass)
{
  png_bytep dp = *dp_ref;
  unsigned int pixel_depth = *pixel_depth_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  if (row_width <= (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7))
  {
    return;
  }
  if (pixel_depth < 8)
  {
    helper_helper_png_combine_row_1_1(&dp, &sp, &row_width, display, pass, pixel_depth);
  }
  else
  {
    helper_helper_png_combine_row_1_2(&dp, &pixel_depth, &sp, &row_width, png_ptr, display, pass);
  }
  *dp_ref = dp;
  *pixel_depth_ref = pixel_depth;
  *sp_ref = sp;
  *row_width_ref = row_width;
}

void helper_png_do_read_interlace_1(png_row_infop * const row_info_ref, png_bytep row, int pass, static const unsigned int png_pass_inc[7])
{
  png_row_infop row_info = *row_info_ref;
  png_uint_32 final_width;
  final_width = row_info->width * png_pass_inc[pass];
  switch (row_info->pixel_depth)
  {
    case 1:
    {
      helper_helper_png_do_read_interlace_1_3(row, pass, png_pass_inc, row_info, final_width);
    }

    case 2:
    {
      helper_helper_png_do_read_interlace_1_4(row, pass, png_pass_inc, row_info, final_width);
    }

    case 4:
    {
      helper_helper_png_do_read_interlace_1_2(row, pass, png_pass_inc, row_info, final_width);
    }

    default:
    {
      helper_helper_png_do_read_interlace_1_1(row, pass, png_pass_inc, row_info, final_width);
    }

  }

  row_info->width = final_width;
  row_info->rowbytes = (row_info->pixel_depth >= 8) ? (((size_t) final_width) * (((size_t) row_info->pixel_depth) >> 3)) : (((((size_t) final_width) * ((size_t) row_info->pixel_depth)) + 7) >> 3);
  *row_info_ref = row_info;
}

void helper_png_read_filter_row_paeth_1byte_pixel_1(png_bytep * const row_ref, png_const_bytep * const prev_row_ref, int * const a_ref, int * const c_ref)
{
  png_bytep row = *row_ref;
  png_const_bytep prev_row = *prev_row_ref;
  int a = *a_ref;
  int c = *c_ref;
  int b;
  int pa;
  int pb;
  int pc;
  int p;
  a &= 0xff;
  b = *prev_row;
  prev_row += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  if (pb < pa)
  {
    pa = pb;
    a = b;
  }
  if (pc < pa)
  {
    a = c;
  }
  c = b;
  a += *row;
  *row = (png_byte) a;
  row += 1;
  *row_ref = row;
  *prev_row_ref = prev_row;
  *a_ref = a;
  *c_ref = c;
}

void helper_png_read_filter_row_paeth_multibyte_pixel_1(png_bytep * const row_ref, png_const_bytep * const prev_row_ref, unsigned int bpp)
{
  png_bytep row = *row_ref;
  png_const_bytep prev_row = *prev_row_ref;
  int a;
  int b;
  int c;
  int pa;
  int pb;
  int pc;
  int p;
  c = *(prev_row - bpp);
  a = *(row - bpp);
  b = *prev_row;
  prev_row += 1;
  p = b - c;
  pc = a - c;
  pa = (p < 0) ? (-p) : (p);
  pb = (pc < 0) ? (-pc) : (pc);
  pc = ((p + pc) < 0) ? (-(p + pc)) : (p + pc);
  if (pb < pa)
  {
    pa = pb;
    a = b;
  }
  if (pc < pa)
  {
    a = c;
  }
  a += *row;
  *row = (png_byte) a;
  row += 1;
  *row_ref = row;
  *prev_row_ref = prev_row;
}

void helper_png_read_IDAT_data_1(png_structrp * const png_ptr_ref, png_alloc_size_t * const avail_out_ref, png_bytep output)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_alloc_size_t avail_out = *avail_out_ref;
  int ret;
  png_byte tmpbuf[1024];
  if (png_ptr->zstream.avail_in == 0)
  {
    helper_helper_png_read_IDAT_data_1_1(&png_ptr);
  }
  if (output != 0)
  {
    uInt out = (uInt) (-1);
    if (out > avail_out)
    {
      out = (uInt) avail_out;
    }
    avail_out -= out;
    png_ptr->zstream.avail_out = out;
  }
  else
  {
    png_ptr->zstream.next_out = tmpbuf;
    png_ptr->zstream.avail_out = sizeof(tmpbuf);
  }
  ret = png_zlib_inflate(png_ptr, 0);
  if (output != 0)
  {
    avail_out += png_ptr->zstream.avail_out;
  }
  else
    avail_out += (sizeof(tmpbuf)) - png_ptr->zstream.avail_out;
  png_ptr->zstream.avail_out = 0;
  if (ret == 1)
  {
    png_ptr->zstream.next_out = 0;
    png_ptr->mode |= 0x08;
    png_ptr->flags |= 0x0008U;
    if ((png_ptr->zstream.avail_in > 0) || (png_ptr->idat_size > 0))
    {
      png_chunk_benign_error(png_ptr, "Extra compressed data");
    }
    break;
  }
  if (ret != 0)
  {
    png_zstream_error(png_ptr, ret);
    if (output != 0)
    {
      png_chunk_error(png_ptr, png_ptr->zstream.msg);
    }
    else
    {
      png_chunk_benign_error(png_ptr, png_ptr->zstream.msg);
      return;
    }
  }
  *png_ptr_ref = png_ptr;
  *avail_out_ref = avail_out;
}

void helper_png_read_start_row_1(png_structrp * const png_ptr_ref, size_t row_bytes)
{
  png_structrp png_ptr = *png_ptr_ref;
  png_free(png_ptr, png_ptr->big_row_buf);
  png_free(png_ptr, png_ptr->big_prev_row);
  if (png_ptr->interlaced != 0)
  {
    png_ptr->big_row_buf = (png_bytep) png_calloc(png_ptr, row_bytes + 48);
  }
  else
    png_ptr->big_row_buf = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
  png_ptr->big_prev_row = (png_bytep) png_malloc(png_ptr, row_bytes + 48);
  {
    png_bytep temp = png_ptr->big_row_buf + 32;
    size_t extra = ((size_t) temp) & 0x0f;
    png_ptr->row_buf = (temp - extra) - 1;
    temp = png_ptr->big_prev_row + 32;
    extra = ((size_t) temp) & 0x0f;
    png_ptr->prev_row = (temp - extra) - 1;
  }
  png_ptr->old_big_row_buf_size = row_bytes + 48;
  *png_ptr_ref = png_ptr;
}

void helper_helper_png_combine_row_1_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, int display, unsigned int pass, unsigned int pixel_depth)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  static const png_uint_32 row_mask[2][3][6] = {{{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((0 < 4) ? (0x80088822 >> ((((3 - 0) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 0) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0x80088822 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((2 < 4) ? (0x80088822 >> ((((3 - 2) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 2) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0x80088822 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((4 < 4) ? (0x80088822 >> ((((3 - 4) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 4) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0x80088822 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xaa55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
  static const png_uint_32 display_mask[2][3][3] = {{{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((0) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((0) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((0) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}, {{(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((0 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((1 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((2 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((3 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((4 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((5 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((6 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (1 & 0x1f)) - 1) << (((7 * 1) ^ ((1) ? (8 - 1) : (0))) & 0x1f)) : (0))) * ((1 == 1) ? (0x01010101) : ((1 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((0 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((1 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((2 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((3 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((4 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((5 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((6 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (2 & 0x1f)) - 1) << (((7 * 2) ^ ((1) ? (8 - 2) : (0))) & 0x1f)) : (0))) * ((2 == 1) ? (0x01010101) : ((2 == 2) ? (0x00010001) : (1)))}, {(((((((((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((1 < 4) ? (0xff0fff33 >> ((((3 - 1) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 1) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((3 < 4) ? (0xff0fff33 >> ((((3 - 3) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 3) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1))), (((((((((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 0)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 0)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((0 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0)) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 1)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 1)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((1 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 2)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 2)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((2 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 3)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 3)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((3 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 4)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 4)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((4 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 5)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 5)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((5 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 6)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 6)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((6 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) + ((((5 < 4) ? (0xff0fff33 >> ((((3 - 5) * 8) + (7 - 7)) & 0x1f)) : (0xff55ff00 >> ((((7 - 5) * 8) + (7 - 7)) & 0x1f))) & 1) ? (((1U << (4 & 0x1f)) - 1) << (((7 * 4) ^ ((1) ? (8 - 4) : (0))) & 0x1f)) : (0))) * ((4 == 1) ? (0x01010101) : ((4 == 2) ? (0x00010001) : (1)))}}};
  png_uint_32 pixels_per_byte = 8 / pixel_depth;
  png_uint_32 mask;
  mask = (display) ? (display_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass >> 1]) : (row_mask[1][(pixel_depth == 1) ? (0) : ((pixel_depth == 2) ? (1) : (2))][pass]);
  for (;;)
  {
    png_uint_32 m;
    m = mask;
    mask = (m >> 8) | (m << 24);
    m &= 0xff;
    if (m != 0)
    {
      if (m != 0xff)
      {
        *dp = (png_byte) (((*dp) & (~m)) | ((*sp) & m));
      }
      else
        *dp = *sp;
    }
    if (row_width <= pixels_per_byte)
    {
      break;
    }
    row_width -= pixels_per_byte;
    dp += 1;
    sp += 1;
  }

  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
}

void helper_helper_png_combine_row_1_2(png_bytep * const dp_ref, unsigned int * const pixel_depth_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, png_const_structrp png_ptr, int display, unsigned int pass)
{
  png_bytep dp = *dp_ref;
  unsigned int pixel_depth = *pixel_depth_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  unsigned int bytes_to_copy;
  unsigned int bytes_to_jump;
  if (pixel_depth & 7)
  {
    png_error(png_ptr, "invalid user transform pixel depth");
  }
  pixel_depth >>= 3;
  row_width *= pixel_depth;
  {
    unsigned int offset = (((1 & pass) << (3 - ((pass + 1) >> 1))) & 7) * pixel_depth;
    row_width -= offset;
    dp += offset;
    sp += offset;
  }
  if (display != 0)
  {
    bytes_to_copy = (1 << ((6 - pass) >> 1)) * pixel_depth;
    if (bytes_to_copy > row_width)
    {
      bytes_to_copy = (unsigned int) row_width;
    }
  }
  else
    bytes_to_copy = pixel_depth;
  bytes_to_jump = (1 << ((7 - pass) >> 1)) * pixel_depth;
  switch (bytes_to_copy)
  {
    case 1:
    {
      for (;;)
      {
        *dp = *sp;
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        dp += bytes_to_jump;
        sp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }

    }

    case 2:
    {
      do
      {
        dp[0] = sp[0];
        dp[1] = sp[1];
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        sp += bytes_to_jump;
        dp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }
      while (row_width > 1);
      *dp = *sp;
      return;
    }

    case 3:
    {
      for (;;)
      {
        dp[0] = sp[0];
        dp[1] = sp[1];
        dp[2] = sp[2];
        if (row_width <= bytes_to_jump)
        {
          return;
        }
        sp += bytes_to_jump;
        dp += bytes_to_jump;
        row_width -= bytes_to_jump;
      }

    }

    default:
    {
      helper_helper_helper_png_combine_row_1_2_1(&dp, &sp, &row_width, &bytes_to_copy, bytes_to_jump);
    }

  }

  *dp_ref = dp;
  *pixel_depth_ref = pixel_depth;
  *sp_ref = sp;
  *row_width_ref = row_width;
}

void helper_helper_png_do_read_interlace_1_1(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  size_t pixel_bytes = row_info->pixel_depth >> 3;
  png_bytep sp = row + (((size_t) (row_info->width - 1)) * pixel_bytes);
  png_bytep dp = row + (((size_t) (final_width - 1)) * pixel_bytes);
  int jstop = (int) png_pass_inc[pass];
  png_uint_32 i;
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v[8];
    int j;
    memcpy(v, sp, pixel_bytes);
    for (j = 0; j < jstop; j += 1)
    {
      memcpy(dp, v, pixel_bytes);
      dp -= pixel_bytes;
    }

    sp -= pixel_bytes;
  }

  break;
}

void helper_helper_png_do_read_interlace_1_2(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 1));
  png_bytep dp = row + ((size_t) ((final_width - 1) >> 1));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  png_uint_32 i;
  int jstop = (int) png_pass_inc[pass];
  {
    sshift = (1 - ((row_info->width + 1) & 0x01)) << 2;
    dshift = (1 - ((final_width + 1) & 0x01)) << 2;
    s_start = 0;
    s_end = 4;
    s_inc = 4;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v = (png_byte) (((*sp) >> sshift) & 0x0f);
    int j;
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0xf0f >> (4 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
}

void helper_helper_png_do_read_interlace_1_3(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((size_t) ((row_info->width - 1) >> 3));
  png_bytep dp = row + ((size_t) ((final_width - 1) >> 3));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  int jstop = (int) png_pass_inc[pass];
  png_byte v;
  png_uint_32 i;
  int j;
  {
    sshift = 7 - ((row_info->width + 7) & 0x07);
    dshift = 7 - ((final_width + 7) & 0x07);
    s_start = 0;
    s_end = 7;
    s_inc = 1;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    v = (png_byte) (((*sp) >> sshift) & 0x01);
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0x7f7f >> (7 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
}

void helper_helper_png_do_read_interlace_1_4(png_bytep row, int pass, static const unsigned int png_pass_inc[7], png_row_infop row_info, png_uint_32 final_width)
{
  png_bytep sp = row + ((png_uint_32) ((row_info->width - 1) >> 2));
  png_bytep dp = row + ((png_uint_32) ((final_width - 1) >> 2));
  unsigned int sshift;
  unsigned int dshift;
  unsigned int s_start;
  unsigned int s_end;
  int s_inc;
  int jstop = (int) png_pass_inc[pass];
  png_uint_32 i;
  {
    sshift = (3 - ((row_info->width + 3) & 0x03)) << 1;
    dshift = (3 - ((final_width + 3) & 0x03)) << 1;
    s_start = 0;
    s_end = 6;
    s_inc = 2;
  }
  for (i = 0; i < row_info->width; i += 1)
  {
    png_byte v;
    int j;
    v = (png_byte) (((*sp) >> sshift) & 0x03);
    for (j = 0; j < jstop; j += 1)
    {
      unsigned int tmp = (*dp) & (0x3f3f >> (6 - dshift));
      tmp |= (unsigned int) (v << dshift);
      *dp = (png_byte) (tmp & 0xff);
      if (dshift == s_end)
      {
        dshift = s_start;
        dp -= 1;
      }
      else
        dshift = (unsigned int) (((int) dshift) + s_inc);
    }

    if (sshift == s_end)
    {
      sshift = s_start;
      sp -= 1;
    }
    else
      sshift = (unsigned int) (((int) sshift) + s_inc);
  }

  break;
}

void helper_helper_png_read_IDAT_data_1_1(png_structrp * const png_ptr_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  uInt avail_in;
  png_bytep buffer;
  while (png_ptr->idat_size == 0)
  {
    png_crc_finish(png_ptr, 0);
    png_ptr->idat_size = png_read_chunk_header(png_ptr);
    if (png_ptr->chunk_name != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      png_error(png_ptr, "Not enough image data");
    }
  }

  avail_in = png_ptr->IDAT_read_size;
  if (avail_in > png_ptr->idat_size)
  {
    avail_in = (uInt) png_ptr->idat_size;
  }
  buffer = png_read_buffer(png_ptr, avail_in, 0);
  png_crc_read(png_ptr, buffer, avail_in);
  png_ptr->idat_size -= avail_in;
  png_ptr->zstream.next_in = buffer;
  png_ptr->zstream.avail_in = avail_in;
  *png_ptr_ref = png_ptr;
}

void helper_helper_helper_png_combine_row_1_2_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, unsigned int * const bytes_to_copy_ref, unsigned int bytes_to_jump)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  unsigned int bytes_to_copy = *bytes_to_copy_ref;
  if (((((bytes_to_copy < 16) && ((((png_uint_16) ((size_t) ((const void *) dp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((((png_uint_16) ((size_t) ((const void *) sp))) & ((png_uint_16) ((sizeof(png_uint_16)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_16))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_16))) == 0))
  {
    helper_helper_helper_helper_png_combine_row_1_2_1_1(&dp, &sp, &row_width, bytes_to_jump, bytes_to_copy);
  }
  for (;;)
  {
    memcpy(dp, sp, bytes_to_copy);
    if (row_width <= bytes_to_jump)
    {
      return;
    }
    sp += bytes_to_jump;
    dp += bytes_to_jump;
    row_width -= bytes_to_jump;
    if (bytes_to_copy > row_width)
    {
      bytes_to_copy = (unsigned int) row_width;
    }
  }

  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
  *bytes_to_copy_ref = bytes_to_copy;
}

void helper_helper_helper_helper_png_combine_row_1_2_1_1(png_bytep * const dp_ref, png_const_bytep * const sp_ref, png_alloc_size_t * const row_width_ref, unsigned int bytes_to_jump, unsigned int bytes_to_copy)
{
  png_bytep dp = *dp_ref;
  png_const_bytep sp = *sp_ref;
  png_alloc_size_t row_width = *row_width_ref;
  if (((((((png_uint_32) ((size_t) ((const void *) dp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0) && ((((png_uint_32) ((size_t) ((const void *) sp))) & ((png_uint_32) ((sizeof(png_uint_32)) - 1))) == 0)) && ((bytes_to_copy % (sizeof(png_uint_32))) == 0)) && ((bytes_to_jump % (sizeof(png_uint_32))) == 0))
  {
    png_uint_32p dp32 = (void *) dp;
    png_const_uint_32p sp32 = (const void *) sp;
    size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_32));
    do
    {
      size_t c = bytes_to_copy;
      do
      {
        *dp32 = *sp32;
        sp32 += 1;
        dp32 += 1;
        c -= sizeof(png_uint_32);
      }
      while (c > 0);
      if (row_width <= bytes_to_jump)
      {
        return;
      }
      dp32 += skip;
      sp32 += skip;
      row_width -= bytes_to_jump;
    }
    while (bytes_to_copy <= row_width);
    dp = (png_bytep) dp32;
    sp = (png_const_bytep) sp32;
    do
    {
      *dp = *sp;
      sp += 1;
      dp += 1;
    }
    while ((--row_width) > 0);
    return;
  }
  else
  {
    png_uint_16p dp16 = (void *) dp;
    png_const_uint_16p sp16 = (const void *) sp;
    size_t skip = (bytes_to_jump - bytes_to_copy) / (sizeof(png_uint_16));
    do
    {
      size_t c = bytes_to_copy;
      do
      {
        *dp16 = *sp16;
        sp16 += 1;
        dp16 += 1;
        c -= sizeof(png_uint_16);
      }
      while (c > 0);
      if (row_width <= bytes_to_jump)
      {
        return;
      }
      dp16 += skip;
      sp16 += skip;
      row_width -= bytes_to_jump;
    }
    while (bytes_to_copy <= row_width);
    dp = (png_bytep) dp16;
    sp = (png_const_bytep) sp16;
    do
    {
      *dp = *sp;
      sp += 1;
      dp += 1;
    }
    while ((--row_width) > 0);
    return;
  }
  *dp_ref = dp;
  *sp_ref = sp;
  *row_width_ref = row_width;
}

