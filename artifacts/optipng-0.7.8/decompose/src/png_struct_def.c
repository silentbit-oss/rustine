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
}
/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef void *voidp
----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef void (*png_rw_ptr)(png_structp, png_bytep, size_t)
----------------------------
typedef void (*png_write_status_ptr)(png_structp, png_uint_32, int)
----------------------------
typedef void (*png_error_ptr)(png_structp, png_const_charp)
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef const png_byte *png_const_bytep
----------------------------
typedef struct png_color_8_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
  png_byte gray;
  png_byte alpha;
} png_color_8
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
typedef unsigned int png_uint_32
----------------------------
typedef png_int_32 png_fixed_point
----------------------------
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} png_compression_buffer
----------------------------
typedef struct png_unknown_chunk_t
{
  png_byte name[5];
  png_byte *data;
  size_t size;
  png_byte location;
} png_unknown_chunk
----------------------------
typedef struct png_compression_buffer
{
  struct png_compression_buffer *next;
  png_byte output[1];
} *png_compression_bufferp
----------------------------
typedef void (*png_flush_ptr)(png_structp)
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef unsigned short png_uint_16
----------------------------
typedef unsigned char png_byte
----------------------------
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
} z_stream
----------------------------
typedef png_color *png_colorp
----------------------------
typedef void *png_voidp
----------------------------
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
typedef unsigned int uInt
----------------------------
typedef unsigned short ush
----------------------------
typedef void (*png_read_status_ptr)(png_structp, png_uint_32, int)
----------------------------
***/


