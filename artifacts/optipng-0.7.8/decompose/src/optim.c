static void opng_free(void *ptr)
{
  free(ptr);
}


/*** DEPENDENCIES:
***/


static void opng_init_read_data(void)
{
}


/*** DEPENDENCIES:
***/


static void opng_init_write_data(void)
{
  s_process.out_file_size = 0;
  s_process.out_plte_trns_size = 0;
  s_process.out_idat_size = 0;
}


/*** DEPENDENCIES:
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
} s_process
----------------------------
***/


static void opng_clear_image_info(void)
{
  memset(&s_image, 0, sizeof(s_image));
}


/*** DEPENDENCIES:
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
} s_image
----------------------------
***/


static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}


/*** DEPENDENCIES:
static void (*usr_print_cntrl)(int cntrl_code)
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
***/


static void opng_print_error(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Error: %s\n", msg);
}


/*** DEPENDENCIES:
static void (*usr_print_cntrl)(int cntrl_code)
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
***/


// hint:  ['printed_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
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
} s_image
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
***/


static void opng_warning(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
  }
  opng_print_warning(msg);
}


/*** DEPENDENCIES:
static png_structp s_read_ptr
----------------------------
typedef png_struct *png_structp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef const char *png_const_charp
----------------------------
static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}


----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
static png_structp s_read_ptr
----------------------------
typedef png_struct *png_structp
----------------------------
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


----------------------------
static void opng_print_error(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Error: %s\n", msg);
}


----------------------------
static png_infop s_read_info_ptr
----------------------------
struct exception_context the_exception_context[1]
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef const char *png_const_charp
----------------------------
static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}


----------------------------
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
} s_process
----------------------------
***/


static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


/*** DEPENDENCIES:
struct exception_context the_exception_context[1]
----------------------------
static void opng_print_error(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Error: %s\n", msg);
}


----------------------------
typedef const char *png_const_charp
----------------------------
***/


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


/*** DEPENDENCIES:
opng_foffset_t opng_ftello(FILE *stream)
{
  return (opng_foffset_t) ftell(stream);
}


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
typedef png_struct *png_structp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
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
} s_process
----------------------------
***/


static int opng_is_apng_chunk(png_bytep chunk_type)
{
  if (((memcmp(chunk_type, k_sig_acTL, 4) == 0) || (memcmp(chunk_type, k_sig_fcTL, 4) == 0)) || (memcmp(chunk_type, k_sig_fdAT, 4) == 0))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
static const png_byte k_sig_acTL[4] = {0x61, 0x63, 0x54, 0x4c}
----------------------------
static const png_byte k_sig_fdAT[4] = {0x66, 0x64, 0x41, 0x54}
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte *png_bytep
----------------------------
static const png_byte k_sig_fcTL[4] = {0x66, 0x63, 0x54, 0x4c}
----------------------------
***/


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


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
static const png_byte k_sig_tRNS[4] = {0x74, 0x52, 0x4e, 0x53}
----------------------------
***/


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


/*** DEPENDENCIES:
void png_set_keep_unknown_chunks(png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks_in)
{
  png_bytep new_list;
  unsigned int num_chunks;
  unsigned int old_num_chunks;
  if (png_ptr == 0)
  {
    return;
  }
  if ((keep < 0) || (keep >= 4))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: invalid keep");
    return;
  }
  if (num_chunks_in <= 0)
  {
    png_ptr->unknown_default = keep;
    if (num_chunks_in == 0)
    {
      return;
    }
  }
  if (num_chunks_in < 0)
  {
    static const png_byte chunks_to_ignore[] = {98, 75, 71, 68, '\0', 99, 72, 82, 77, '\0', 101, 88, 73, 102, '\0', 103, 65, 77, 65, '\0', 104, 73, 83, 84, '\0', 105, 67, 67, 80, '\0', 105, 84, 88, 116, '\0', 111, 70, 70, 115, '\0', 112, 67, 65, 76, '\0', 112, 72, 89, 115, '\0', 115, 66, 73, 84, '\0', 115, 67, 65, 76, '\0', 115, 80, 76, 84, '\0', 115, 84, 69, 82, '\0', 115, 82, 71, 66, '\0', 116, 69, 88, 116, '\0', 116, 73, 77, 69, '\0', 122, 84, 88, 116, '\0'};
    chunk_list = chunks_to_ignore;
    num_chunks = ((unsigned int) (sizeof(chunks_to_ignore))) / 5U;
  }
  else
  {
    if (chunk_list == 0)
    {
      png_app_error(png_ptr, "png_set_keep_unknown_chunks: no chunk list");
      return;
    }
    num_chunks = (unsigned int) num_chunks_in;
  }
  old_num_chunks = png_ptr->num_chunk_list;
  if (png_ptr->chunk_list == 0)
  {
    old_num_chunks = 0;
  }
  if ((num_chunks + old_num_chunks) > (4294967295U / 5))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: too many chunks");
    return;
  }
  if (keep != 0)
  {
    new_list = png_malloc(png_ptr, 5 * (num_chunks + old_num_chunks));
    if (old_num_chunks > 0)
    {
      memcpy(new_list, png_ptr->chunk_list, 5 * old_num_chunks);
    }
  }
  else
    if (old_num_chunks > 0)
  {
    new_list = png_ptr->chunk_list;
  }
  else
    new_list = 0;
  if (new_list != 0)
  {
    helper_png_set_keep_unknown_chunks_1(&new_list, &num_chunks, &old_num_chunks, png_ptr, keep, chunk_list);
  }
  else
    num_chunks = 0;
  png_ptr->num_chunk_list = num_chunks;
  if (png_ptr->chunk_list != new_list)
  {
    if (png_ptr->chunk_list != 0)
    {
      png_free(png_ptr, png_ptr->chunk_list);
    }
    png_ptr->chunk_list = new_list;
  }
}


----------------------------
typedef png_struct *png_structp
----------------------------
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


----------------------------
typedef unsigned char png_byte
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


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


/*** DEPENDENCIES:
static const png_byte k_sig_fdAT[4] = {0x66, 0x64, 0x41, 0x54}
----------------------------
typedef png_struct *png_structp
----------------------------
static const png_byte k_sig_sBIT[4] = {0x73, 0x42, 0x49, 0x54}
----------------------------
static const png_byte k_sig_hIST[4] = {0x68, 0x49, 0x53, 0x54}
----------------------------
typedef unsigned char png_byte
----------------------------
static struct opng_options s_options
----------------------------
static int opng_is_apng_chunk(png_bytep chunk_type)
{
  if (((memcmp(chunk_type, k_sig_acTL, 4) == 0) || (memcmp(chunk_type, k_sig_fcTL, 4) == 0)) || (memcmp(chunk_type, k_sig_fdAT, 4) == 0))
  {
    return 1;
  }
  return 0;
}


----------------------------
static const png_byte k_sig_bKGD[4] = {0x62, 0x4b, 0x47, 0x44}
----------------------------
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


----------------------------
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


----------------------------
static const png_byte k_sig_dSIG[4] = {0x64, 0x53, 0x49, 0x47}
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
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
} s_process
----------------------------
***/


// hint:  ['chunk_sig_ref is a mutable refrence to png_bytep']
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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
static png_structp s_read_ptr
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
static const png_byte k_sig_PLTE[4] = {0x50, 0x4c, 0x54, 0x45}
----------------------------
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


----------------------------
static png_infop s_read_info_ptr
----------------------------
static const png_byte k_sig_IDAT[4] = {0x49, 0x44, 0x41, 0x54}
----------------------------
static const png_byte k_sig_tRNS[4] = {0x74, 0x52, 0x4e, 0x53}
----------------------------
png_uint_32 png_get_image_height(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->height;
  }
  return 0;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
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


----------------------------
typedef png_byte *png_bytep
----------------------------
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler)
{
  return pngx_malloc_rows_extended(png_ptr, info_ptr, 0, filler);
}


----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
png_voidp png_get_io_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return png_ptr->io_ptr;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_uint_32 png_get_io_state(png_const_structrp png_ptr)
{
  return png_ptr->io_state;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
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


----------------------------
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


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['fmt_name_idx_ref is a mutable refrence to unsigned int', 'num_img_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
static void opng_warning(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
  }
  opng_print_warning(msg);
}


----------------------------
void png_set_keep_unknown_chunks(png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks_in)
{
  png_bytep new_list;
  unsigned int num_chunks;
  unsigned int old_num_chunks;
  if (png_ptr == 0)
  {
    return;
  }
  if ((keep < 0) || (keep >= 4))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: invalid keep");
    return;
  }
  if (num_chunks_in <= 0)
  {
    png_ptr->unknown_default = keep;
    if (num_chunks_in == 0)
    {
      return;
    }
  }
  if (num_chunks_in < 0)
  {
    static const png_byte chunks_to_ignore[] = {98, 75, 71, 68, '\0', 99, 72, 82, 77, '\0', 101, 88, 73, 102, '\0', 103, 65, 77, 65, '\0', 104, 73, 83, 84, '\0', 105, 67, 67, 80, '\0', 105, 84, 88, 116, '\0', 111, 70, 70, 115, '\0', 112, 67, 65, 76, '\0', 112, 72, 89, 115, '\0', 115, 66, 73, 84, '\0', 115, 67, 65, 76, '\0', 115, 80, 76, 84, '\0', 115, 84, 69, 82, '\0', 115, 82, 71, 66, '\0', 116, 69, 88, 116, '\0', 116, 73, 77, 69, '\0', 122, 84, 88, 116, '\0'};
    chunk_list = chunks_to_ignore;
    num_chunks = ((unsigned int) (sizeof(chunks_to_ignore))) / 5U;
  }
  else
  {
    if (chunk_list == 0)
    {
      png_app_error(png_ptr, "png_set_keep_unknown_chunks: no chunk list");
      return;
    }
    num_chunks = (unsigned int) num_chunks_in;
  }
  old_num_chunks = png_ptr->num_chunk_list;
  if (png_ptr->chunk_list == 0)
  {
    old_num_chunks = 0;
  }
  if ((num_chunks + old_num_chunks) > (4294967295U / 5))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: too many chunks");
    return;
  }
  if (keep != 0)
  {
    new_list = png_malloc(png_ptr, 5 * (num_chunks + old_num_chunks));
    if (old_num_chunks > 0)
    {
      memcpy(new_list, png_ptr->chunk_list, 5 * old_num_chunks);
    }
  }
  else
    if (old_num_chunks > 0)
  {
    new_list = png_ptr->chunk_list;
  }
  else
    new_list = 0;
  if (new_list != 0)
  {
    helper_png_set_keep_unknown_chunks_1(&new_list, &num_chunks, &old_num_chunks, png_ptr, keep, chunk_list);
  }
  else
    num_chunks = 0;
  png_ptr->num_chunk_list = num_chunks;
  if (png_ptr->chunk_list != new_list)
  {
    if (png_ptr->chunk_list != 0)
    {
      png_free(png_ptr, png_ptr->chunk_list);
    }
    png_ptr->chunk_list = new_list;
  }
}


----------------------------
static png_structp s_read_ptr
----------------------------
void png_set_user_limits(png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->user_width_max = user_width_max;
  png_ptr->user_height_max = user_height_max;
}


----------------------------
static void opng_init_read_data(void)
{
}


----------------------------
png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
{
  png_structp png_ptr = png_create_png_struct(user_png_ver, error_ptr, error_fn, warn_fn, 0, 0, 0);
  if (png_ptr != 0)
  {
    png_ptr->mode = 0x8000U;
    png_ptr->IDAT_read_size = 8192;
    png_ptr->flags |= 0x100000U;
    png_ptr->flags |= 0x200000U;
    png_set_read_fn(png_ptr, 0, 0);
  }
  return png_ptr;
}


----------------------------
int opng_fgetsize(FILE *stream, opng_fsize_t *size)
{
  struct stat sbuf;
  if (fstat(fileno(stream), &sbuf) != 0)
  {
    return -1;
  }
  if (sbuf.st_size < 0)
  {
    return -1;
  }
  *size = (opng_fsize_t) sbuf.st_size;
  return 0;
}


----------------------------
static png_infop s_read_info_ptr
----------------------------
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


----------------------------
struct exception_context the_exception_context[1]
----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
int pngx_read_image(png_structp png_ptr, png_infop info_ptr, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  png_byte sig[128];
  size_t num;
  int (*read_fn)(png_structp, png_infop, FILE *);
  unsigned int read_fn_idx = 0;
  FILE *stream;
  unsigned int stream_idx = 0;
  fpos_t fpos;
  int result;
  stream_idx = (FILE *) png_get_io_ptr(png_ptr);
  if (fgetpos(stream, &fpos) != 0)
  {
    png_error(png_ptr, "Can't ftell in input file stream");
  }
  num = fread(sig, 1, sizeof(sig), stream);
  if (fsetpos(stream, &fpos) != 0)
  {
    png_error(png_ptr, "Can't fseek in input file stream");
  }
  if (pngx_sig_is_png(png_ptr, sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    png_read_png(png_ptr, info_ptr, 0, 0);
    if (getc(stream) != EOF)
    {
      png_warning(png_ptr, "Extraneous data found after IEND");
      fseek(stream, 0, 2);
    }
    return 1;
  }
  if (pngx_sig_is_bmp(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_bmp;
  }
  else
    if (pngx_sig_is_gif(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_gif;
  }
  else
    if (pngx_sig_is_jpeg(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_jpeg;
  }
  else
    if (pngx_sig_is_pnm(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_pnm;
  }
  else
    if (pngx_sig_is_tiff(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_tiff;
  }
  else
    return 0;
  result = read_fn(png_ptr, info_ptr, stream);
  if (result <= 0)
  {
    if (fsetpos(stream, &fpos) != 0)
    {
      png_error(png_ptr, "Can't fseek in input file stream");
    }
  }
  return result;
}


----------------------------
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


----------------------------
static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}


----------------------------
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


----------------------------
void png_set_read_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (read_data_fn != 0)
  {
    png_ptr->read_data_fn = read_data_fn;
  }
  else
    png_ptr->read_data_fn = png_default_read_data;
  if (png_ptr->write_data_fn != 0)
  {
    png_ptr->write_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
  png_ptr->output_flush_fn = 0;
}


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['fmt_name_idx_ref is a mutable refrence to unsigned int', 'num_img_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
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


----------------------------
struct exception_context the_exception_context[1]
----------------------------
***/


static void opng_check_idat_size(opng_fsize_t size)
{
  if (size > k_idat_size_max)
  {
    opng_throw_error("IDAT sizes larger than the maximum chunk size are currently unsupported");
  }
}


/*** DEPENDENCIES:
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL
----------------------------
typedef unsigned long opng_fsize_t
----------------------------
***/


// hint:  ['crt_idat_offset_ref is a mutable refrence to opng_foffset_t', 'io_state_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
static void opng_check_idat_size(opng_fsize_t size)
{
  if (size > k_idat_size_max)
  {
    opng_throw_error("IDAT sizes larger than the maximum chunk size are currently unsupported");
  }
}


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
typedef long opng_foffset_t
----------------------------
size_t opng_fwriteo(FILE *stream, opng_foffset_t offset, int whence, const void *block, size_t blocksize)
{
  fpos_t pos;
  size_t result;
  if ((fgetpos(stream, &pos) != 0) || (fflush(stream) != 0))
  {
    return 0;
  }
  if (opng_fseeko(stream, offset, whence) == 0)
  {
    result = fwrite(block, 1, blocksize, stream);
  }
  else
    result = 0;
  if (fflush(stream) != 0)
  {
    result = 0;
  }
  if (fsetpos(stream, &pos) != 0)
  {
    result = 0;
  }
  return result;
}


----------------------------
typedef unsigned long opng_fsize_t
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
----------------------------
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['crt_idat_offset_ref is a mutable refrence to opng_foffset_t', 'crt_idat_size_ref is a mutable refrence to opng_fsize_t', 'crt_idat_crc_ref is a mutable refrence to png_uint_32', 'io_state_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
opng_foffset_t opng_ftello(FILE *stream)
{
  return (opng_foffset_t) ftell(stream);
}


----------------------------
typedef long opng_foffset_t
----------------------------
typedef unsigned long opng_fsize_t
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
static const png_byte k_sig_IDAT[4] = {0x49, 0x44, 0x41, 0x54}
----------------------------
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
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


----------------------------
unsigned long crc32(unsigned long crc, const unsigned char *buf, uInt len)
{
  return crc32_z(crc, buf, len);
}


----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
static int opng_is_apng_chunk(png_bytep chunk_type)
{
  if (((memcmp(chunk_type, k_sig_acTL, 4) == 0) || (memcmp(chunk_type, k_sig_fcTL, 4) == 0)) || (memcmp(chunk_type, k_sig_fdAT, 4) == 0))
  {
    return 1;
  }
  return 0;
}


----------------------------
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


----------------------------
typedef unsigned char png_byte
----------------------------
static struct opng_options s_options
----------------------------
static const png_byte k_sig_dSIG[4] = {0x64, 0x53, 0x49, 0x47}
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['allow_crt_chunk_ref is a mutable refrence to int', 'crt_chunk_is_idat_ref is a mutable refrence to int', 'chunk_sig_ref is a mutable refrence to png_bytep']
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


/*** DEPENDENCIES:
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


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
typedef unsigned char png_byte
----------------------------
static const png_byte k_sig_PLTE[4] = {0x50, 0x4c, 0x54, 0x45}
----------------------------
struct exception_context the_exception_context[1]
----------------------------
static const png_byte k_sig_IDAT[4] = {0x49, 0x44, 0x41, 0x54}
----------------------------
static const png_byte k_sig_tRNS[4] = {0x74, 0x52, 0x4e, 0x53}
----------------------------
typedef png_byte *png_bytep
----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
typedef long opng_foffset_t
----------------------------
typedef unsigned long opng_fsize_t
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
----------------------------
png_voidp png_get_io_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return png_ptr->io_ptr;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
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


----------------------------
png_uint_32 png_get_io_state(png_const_structrp png_ptr)
{
  return png_ptr->io_state;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
unsigned long crc32(unsigned long crc, const unsigned char *buf, uInt len)
{
  return crc32_z(crc, buf, len);
}


----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
void png_set_rows(png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((info_ptr->row_pointers != 0) && (info_ptr->row_pointers != row_pointers))
  {
    png_free_data(png_ptr, info_ptr, 0x0040U, 0);
  }
  info_ptr->row_pointers = row_pointers;
  if (row_pointers != 0)
  {
    info_ptr->valid |= 0x8000U;
  }
}


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
void png_set_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_16p background)
{
  (void) 0;
  if (((png_ptr == 0) || (info_ptr == 0)) || (background == 0))
  {
    return;
  }
  info_ptr->background = *background;
  info_ptr->valid |= 0x0020U;
}


----------------------------
static png_structp s_write_ptr
----------------------------
void png_set_unknown_chunk_location(png_const_structrp png_ptr, png_inforp info_ptr, int chunk, int location)
{
  if ((((png_ptr != 0) && (info_ptr != 0)) && (chunk >= 0)) && (chunk < info_ptr->unknown_chunks_num))
  {
    if ((location & ((0x01 | 0x02) | 0x08)) == 0)
    {
      png_app_error(png_ptr, "invalid unknown chunk location");
      if ((((unsigned int) location) & 0x04U) != 0)
      {
        location = 0x08;
      }
      else
        location = 0x01;
    }
    info_ptr->unknown_chunks[chunk].location = check_location(png_ptr, location);
  }
}


----------------------------
typedef png_struct *png_structp
----------------------------
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
} s_image
----------------------------
void png_set_IHDR(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  info_ptr->width = width;
  info_ptr->height = height;
  info_ptr->bit_depth = (png_byte) bit_depth;
  info_ptr->color_type = (png_byte) color_type;
  info_ptr->compression_type = (png_byte) compression_type;
  info_ptr->filter_type = (png_byte) filter_type;
  info_ptr->interlace_type = (png_byte) interlace_type;
  png_check_IHDR(png_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, info_ptr->color_type, info_ptr->interlace_type, info_ptr->compression_type, info_ptr->filter_type);
  if (info_ptr->color_type == (2 | 1))
  {
    info_ptr->channels = 1;
  }
  else
    if ((info_ptr->color_type & 2) != 0)
  {
    info_ptr->channels = 3;
  }
  else
    info_ptr->channels = 1;
  if ((info_ptr->color_type & 4) != 0)
  {
    info_ptr->channels += 1;
  }
  info_ptr->pixel_depth = (png_byte) (info_ptr->channels * info_ptr->bit_depth);
  info_ptr->rowbytes = (info_ptr->pixel_depth >= 8) ? (((size_t) width) * (((size_t) info_ptr->pixel_depth) >> 3)) : (((((size_t) width) * ((size_t) info_ptr->pixel_depth)) + 7) >> 3);
}


----------------------------
void png_set_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit)
{
  (void) 0;
  if (((png_ptr == 0) || (info_ptr == 0)) || (sig_bit == 0))
  {
    return;
  }
  info_ptr->sig_bit = *sig_bit;
  info_ptr->valid |= 0x0002U;
}


----------------------------
static png_infop s_write_info_ptr
----------------------------
void png_set_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette)
{
  png_uint_32 max_palette_length;
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  max_palette_length = (info_ptr->color_type == (2 | 1)) ? (1 << info_ptr->bit_depth) : (256);
  if ((num_palette < 0) || (num_palette > ((int) max_palette_length)))
  {
    if (info_ptr->color_type == (2 | 1))
    {
      png_error(png_ptr, "Invalid palette length");
    }
    else
    {
      png_warning(png_ptr, "Invalid palette length");
      return;
    }
  }
  if (((num_palette > 0) && (palette == 0)) || (num_palette == 0))
  {
    png_error(png_ptr, "Invalid palette");
  }
  png_free_data(png_ptr, info_ptr, 0x1000U, 0);
  png_ptr->palette = png_calloc(png_ptr, 256 * (sizeof(png_color)));
  if (num_palette > 0)
  {
    memcpy(png_ptr->palette, palette, ((unsigned int) num_palette) * (sizeof(png_color)));
  }
  info_ptr->palette = png_ptr->palette;
  info_ptr->num_palette = (png_ptr->num_palette = (png_uint_16) num_palette);
  info_ptr->free_me |= 0x1000U;
  info_ptr->valid |= 0x0008U;
}


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_set_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)
{
  png_unknown_chunkp np;
  if ((((png_ptr == 0) || (info_ptr == 0)) || (num_unknowns <= 0)) || (unknowns == 0))
  {
    return;
  }
  np = png_realloc_array(png_ptr, info_ptr->unknown_chunks, info_ptr->unknown_chunks_num, num_unknowns, sizeof(*np));
  if (np == 0)
  {
    png_chunk_report(png_ptr, "too many unknown chunks", 1);
    return;
  }
  png_free(png_ptr, info_ptr->unknown_chunks);
  info_ptr->unknown_chunks = np;
  info_ptr->free_me |= 0x0200U;
  np += info_ptr->unknown_chunks_num;
  for (; num_unknowns > 0; num_unknowns -= 1, unknowns += 1)
  {
    memcpy(np->name, unknowns->name, sizeof(np->name));
    np->name[(sizeof(np->name)) - 1] = '\0';
    np->location = check_location(png_ptr, unknowns->location);
    if (unknowns->size == 0)
    {
      np->data = 0;
      np->size = 0;
    }
    else
    {
      np->data = png_malloc_base(png_ptr, unknowns->size);
      if (np->data == 0)
      {
        png_chunk_report(png_ptr, "unknown chunk: out of memory", 1);
        continue;
      }
      memcpy(np->data, unknowns->data, unknowns->size);
      np->size = unknowns->size;
    }
    np += 1;
    info_ptr->unknown_chunks_num += 1;
  }

}


----------------------------
void png_set_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (trans_alpha != 0)
  {
    png_free_data(png_ptr, info_ptr, 0x2000U, 0);
    if ((num_trans > 0) && (num_trans <= 256))
    {
      info_ptr->trans_alpha = png_malloc(png_ptr, 256);
      memcpy(info_ptr->trans_alpha, trans_alpha, (size_t) num_trans);
      info_ptr->free_me |= 0x2000U;
      info_ptr->valid |= 0x0010U;
    }
    png_ptr->trans_alpha = info_ptr->trans_alpha;
  }
  if (trans_color != 0)
  {
    if (info_ptr->bit_depth < 16)
    {
      int sample_max = (1 << info_ptr->bit_depth) - 1;
      if (((info_ptr->color_type == 0) && (trans_color->gray > sample_max)) || ((info_ptr->color_type == 2) && (((trans_color->red > sample_max) || (trans_color->green > sample_max)) || (trans_color->blue > sample_max))))
      {
        png_warning(png_ptr, "tRNS chunk has out-of-range samples for bit_depth");
      }
    }
    info_ptr->trans_color = *trans_color;
    if (num_trans == 0)
    {
      num_trans = 1;
    }
  }
  info_ptr->num_trans = (png_uint_16) num_trans;
  if (num_trans != 0)
  {
    info_ptr->free_me |= 0x2000U;
    info_ptr->valid |= 0x0010U;
  }
}


----------------------------
void png_set_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist)
{
  int i;
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((info_ptr->num_palette == 0) || (info_ptr->num_palette > 256))
  {
    png_warning(png_ptr, "Invalid palette size, hIST allocation skipped");
    return;
  }
  png_free_data(png_ptr, info_ptr, 0x0008U, 0);
  info_ptr->hist = png_malloc_warn(png_ptr, 256 * (sizeof(png_uint_16)));
  if (info_ptr->hist == 0)
  {
    png_warning(png_ptr, "Insufficient memory for hIST chunk data");
    return;
  }
  for (i = 0; i < info_ptr->num_palette; i += 1)
  {
    info_ptr->hist[i] = hist[i];
  }

  info_ptr->free_me |= 0x0008U;
  info_ptr->valid |= 0x0040U;
}


----------------------------
***/


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


/*** DEPENDENCIES:
static void opng_warning(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
  }
  opng_print_warning(msg);
}


----------------------------
static struct opng_options s_options
----------------------------
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


----------------------------
static png_infop s_write_info_ptr
----------------------------
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


----------------------------
void png_set_filter(png_structrp png_ptr, int method, int filters)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (method == 0)
  {
    helper_png_set_filter_1(&png_ptr, &filters);
  }
  else
    png_error(png_ptr, "Unknown custom filter method");
}


----------------------------
static void opng_init_write_data(void)
{
  s_process.out_file_size = 0;
  s_process.out_plte_trns_size = 0;
  s_process.out_idat_size = 0;
}


----------------------------
void png_set_compression_level(png_structrp png_ptr, int level)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->zlib_level = level;
}


----------------------------
void png_set_compression_window_bits(png_structrp png_ptr, int window_bits)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (window_bits > 15)
  {
    png_warning(png_ptr, "Only compression windows <= 32k supported by PNG");
    window_bits = 15;
  }
  else
    if (window_bits < 8)
  {
    png_warning(png_ptr, "Only compression windows >= 256 supported by PNG");
    window_bits = 8;
  }
  png_ptr->zlib_window_bits = window_bits;
}


----------------------------
static png_structp s_write_ptr
----------------------------
void png_set_user_limits(png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->user_width_max = user_width_max;
  png_ptr->user_height_max = user_height_max;
}


----------------------------
void png_set_compression_mem_level(png_structrp png_ptr, int mem_level)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->zlib_mem_level = mem_level;
}


----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
void png_set_write_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (write_data_fn != 0)
  {
    png_ptr->write_data_fn = write_data_fn;
  }
  else
    png_ptr->write_data_fn = png_default_write_data;
  if (output_flush_fn != 0)
  {
    png_ptr->output_flush_fn = output_flush_fn;
  }
  else
    png_ptr->output_flush_fn = png_default_flush;
  if (png_ptr->read_data_fn != 0)
  {
    png_ptr->read_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
}


----------------------------
png_structp png_create_write_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
{
  png_structrp png_ptr = png_create_png_struct(user_png_ver, error_ptr, error_fn, warn_fn, 0, 0, 0);
  if (png_ptr != 0)
  {
    png_ptr->zbuffer_size = 8192;
    png_ptr->zlib_strategy = 1;
    png_ptr->zlib_level = -1;
    png_ptr->zlib_mem_level = 8;
    png_ptr->zlib_window_bits = 15;
    png_ptr->zlib_method = 8;
    png_ptr->flags |= 0x200000U;
    png_set_write_fn(png_ptr, 0, 0, 0);
  }
  return png_ptr;
}


----------------------------
void png_write_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, voidp params)
{
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((info_ptr->valid & 0x8000U) == 0)
  {
    png_app_error(png_ptr, "no rows for png_write_image to write");
    return;
  }
  png_write_info(png_ptr, info_ptr);
  if ((transforms & 0x0020) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_MONO not supported");
  }
  if ((transforms & 0x0040) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SHIFT not supported");
  }
  if ((transforms & 0x0004) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKING not supported");
  }
  if ((transforms & 0x0100) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ALPHA not supported");
  }
  if ((transforms & (0x1000 | 0x0800)) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_STRIP_FILLER not supported");
  }
  if ((transforms & 0x0080) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_BGR not supported");
  }
  if ((transforms & 0x0200) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ENDIAN not supported");
  }
  if ((transforms & 0x0008) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKSWAP not supported");
  }
  if ((transforms & 0x0400) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_ALPHA not supported");
  }
  png_write_image(png_ptr, info_ptr->row_pointers);
  png_write_end(png_ptr, info_ptr);
  (void) params;
}


----------------------------
static const int k_filter_table[5 + 1] = {0x08, 0x10, 0x20, 0x40, 0x80, (((0x08 | 0x10) | 0x20) | 0x40) | 0x80}
----------------------------
void png_set_keep_unknown_chunks(png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks_in)
{
  png_bytep new_list;
  unsigned int num_chunks;
  unsigned int old_num_chunks;
  if (png_ptr == 0)
  {
    return;
  }
  if ((keep < 0) || (keep >= 4))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: invalid keep");
    return;
  }
  if (num_chunks_in <= 0)
  {
    png_ptr->unknown_default = keep;
    if (num_chunks_in == 0)
    {
      return;
    }
  }
  if (num_chunks_in < 0)
  {
    static const png_byte chunks_to_ignore[] = {98, 75, 71, 68, '\0', 99, 72, 82, 77, '\0', 101, 88, 73, 102, '\0', 103, 65, 77, 65, '\0', 104, 73, 83, 84, '\0', 105, 67, 67, 80, '\0', 105, 84, 88, 116, '\0', 111, 70, 70, 115, '\0', 112, 67, 65, 76, '\0', 112, 72, 89, 115, '\0', 115, 66, 73, 84, '\0', 115, 67, 65, 76, '\0', 115, 80, 76, 84, '\0', 115, 84, 69, 82, '\0', 115, 82, 71, 66, '\0', 116, 69, 88, 116, '\0', 116, 73, 77, 69, '\0', 122, 84, 88, 116, '\0'};
    chunk_list = chunks_to_ignore;
    num_chunks = ((unsigned int) (sizeof(chunks_to_ignore))) / 5U;
  }
  else
  {
    if (chunk_list == 0)
    {
      png_app_error(png_ptr, "png_set_keep_unknown_chunks: no chunk list");
      return;
    }
    num_chunks = (unsigned int) num_chunks_in;
  }
  old_num_chunks = png_ptr->num_chunk_list;
  if (png_ptr->chunk_list == 0)
  {
    old_num_chunks = 0;
  }
  if ((num_chunks + old_num_chunks) > (4294967295U / 5))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: too many chunks");
    return;
  }
  if (keep != 0)
  {
    new_list = png_malloc(png_ptr, 5 * (num_chunks + old_num_chunks));
    if (old_num_chunks > 0)
    {
      memcpy(new_list, png_ptr->chunk_list, 5 * old_num_chunks);
    }
  }
  else
    if (old_num_chunks > 0)
  {
    new_list = png_ptr->chunk_list;
  }
  else
    new_list = 0;
  if (new_list != 0)
  {
    helper_png_set_keep_unknown_chunks_1(&new_list, &num_chunks, &old_num_chunks, png_ptr, keep, chunk_list);
  }
  else
    num_chunks = 0;
  png_ptr->num_chunk_list = num_chunks;
  if (png_ptr->chunk_list != new_list)
  {
    if (png_ptr->chunk_list != 0)
    {
      png_free(png_ptr, png_ptr->chunk_list);
    }
    png_ptr->chunk_list = new_list;
  }
}


----------------------------
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


----------------------------
void png_set_compression_strategy(png_structrp png_ptr, int strategy)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->flags |= 0x0001U;
  png_ptr->zlib_strategy = strategy;
}


----------------------------
struct exception_context the_exception_context[1]
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
static png_structp s_write_ptr
----------------------------
void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr)
{
  (void) 0;
  if (png_ptr_ptr != 0)
  {
    png_structrp png_ptr = *png_ptr_ptr;
    if (png_ptr != 0)
    {
      png_destroy_info_struct(png_ptr, info_ptr_ptr);
      *png_ptr_ptr = 0;
      png_write_destroy(png_ptr);
      png_destroy_png_struct(png_ptr);
    }
  }
}


----------------------------
struct exception_context the_exception_context[1]
----------------------------
static png_infop s_write_info_ptr
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL
----------------------------
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


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['counter_ref is a mutable refrence to int', 'line_reused_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
static void (*usr_progress)(unsigned long num, unsigned long denom)
----------------------------
static struct opng_options s_options
----------------------------
typedef unsigned int opng_bitset_t
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL
----------------------------
static void (*usr_print_cntrl)(int cntrl_code)
----------------------------
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


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['mem_level_ref is a mutable refrence to int', 'counter_ref is a mutable refrence to int', 'line_reused_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
typedef unsigned int opng_bitset_t
----------------------------
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


----------------------------
***/


// hint:  ['compr_level_set_ref is a mutable refrence to opng_bitset_t', 'compr_level_ref is a mutable refrence to int', 'mem_level_ref is a mutable refrence to int', 'counter_ref is a mutable refrence to int', 'line_reused_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
typedef unsigned int opng_bitset_t
----------------------------
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


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['compr_level_set_ref is a mutable refrence to opng_bitset_t', 'compr_level_ref is a mutable refrence to int', 'mem_level_ref is a mutable refrence to int', 'strategy_ref is a mutable refrence to int', 'counter_ref is a mutable refrence to int', 'line_reused_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
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


----------------------------
typedef unsigned int opng_bitset_t
----------------------------
***/


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


/*** DEPENDENCIES:
struct opng_ulratio
{
  unsigned long num;
  unsigned long denom;
}
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio)
{
  opng_uxlong_impl_t num = ratio->num;
  opng_uxlong_impl_t denom = ratio->denom;
  return opng_sprint_uratio_impl(buffer, buffer_size, num, denom, 0);
}


----------------------------
typedef unsigned long opng_fsize_t
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
typedef unsigned long opng_fsize_t
----------------------------
***/


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


/*** DEPENDENCIES:
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
} s_image
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
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
} s_image
----------------------------
static void opng_free(void *ptr)
{
  free(ptr);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
***/


// hint:  ['buf_ref is a mutable refrence to png_bytep', 'buf_size_ref is a mutable refrence to png_uint_32', 'length_ref is a mutable refrence to png_uint_32']
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


/*** DEPENDENCIES:
png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


----------------------------
static png_structp s_write_ptr
----------------------------
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


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
struct exception_context the_exception_context[1]
----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
void png_free(png_const_structrp png_ptr, png_voidp ptr)
{
  if ((png_ptr == 0) || (ptr == 0))
  {
    return;
  }
  free(ptr);
}


----------------------------
static const png_byte k_sig_IEND[4] = {0x49, 0x45, 0x4e, 0x44}
----------------------------
typedef png_byte *png_bytep
----------------------------
void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_string, png_const_bytep data, size_t length)
{
  png_write_complete_chunk(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), data, length);
}


----------------------------
***/


// hint:  ['buf_ref is a mutable refrence to png_bytep', 'buf_size_ref is a mutable refrence to png_uint_32', 'length_ref is a mutable refrence to png_uint_32']
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


/*** DEPENDENCIES:
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


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
struct exception_context the_exception_context[1]
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


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


/*** DEPENDENCIES:
static void opng_warning(png_structp png_ptr, png_const_charp msg)
{
  if (png_ptr == s_read_ptr)
  {
    s_process.status |= INPUT_HAS_ERRORS | OUTPUT_NEEDS_NEW_IDAT;
  }
  opng_print_warning(msg);
}


----------------------------
static png_structp s_write_ptr
----------------------------
void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr)
{
  (void) 0;
  if (png_ptr_ptr != 0)
  {
    png_structrp png_ptr = *png_ptr_ptr;
    if (png_ptr != 0)
    {
      png_destroy_info_struct(png_ptr, info_ptr_ptr);
      *png_ptr_ptr = 0;
      png_write_destroy(png_ptr);
      png_destroy_png_struct(png_ptr);
    }
  }
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
png_structp png_create_write_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
{
  png_structrp png_ptr = png_create_png_struct(user_png_ver, error_ptr, error_fn, warn_fn, 0, 0, 0);
  if (png_ptr != 0)
  {
    png_ptr->zbuffer_size = 8192;
    png_ptr->zlib_strategy = 1;
    png_ptr->zlib_level = -1;
    png_ptr->zlib_mem_level = 8;
    png_ptr->zlib_window_bits = 15;
    png_ptr->zlib_method = 8;
    png_ptr->flags |= 0x200000U;
    png_set_write_fn(png_ptr, 0, 0, 0);
  }
  return png_ptr;
}


----------------------------
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


----------------------------
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


----------------------------
struct exception_context the_exception_context[1]
----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
void png_set_write_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (write_data_fn != 0)
  {
    png_ptr->write_data_fn = write_data_fn;
  }
  else
    png_ptr->write_data_fn = png_default_write_data;
  if (output_flush_fn != 0)
  {
    png_ptr->output_flush_fn = output_flush_fn;
  }
  else
    png_ptr->output_flush_fn = png_default_flush;
  if (png_ptr->read_data_fn != 0)
  {
    png_ptr->read_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
}


----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
void png_free(png_const_structrp png_ptr, png_voidp ptr)
{
  if ((png_ptr == 0) || (ptr == 0))
  {
    return;
  }
  free(ptr);
}


----------------------------
static void opng_init_write_data(void)
{
  s_process.out_file_size = 0;
  s_process.out_plte_trns_size = 0;
  s_process.out_idat_size = 0;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
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


----------------------------
***/


// hint:  ['infile_idx_ref is a mutable refrence to unsigned int', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
int opng_fseeko(FILE *stream, opng_foffset_t offset, int whence)
{
  return fseek(stream, (long) offset, whence);
}


----------------------------
struct exception_context the_exception_context[1]
----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['infile_idx_ref is a mutable refrence to unsigned int', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
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


----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
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
} s_process
----------------------------
***/


// hint:  ['infile_idx_ref is a mutable refrence to unsigned int', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
struct exception_context the_exception_context[1]
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
***/


// hint:  ['infile_idx_ref is a mutable refrence to unsigned int', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
struct exception_context the_exception_context[1]
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
static struct opng_options s_options
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
static struct opng_engine_struct
{
  int started;
} s_engine
----------------------------
static struct opng_summary_struct
{
  unsigned int file_count;
  unsigned int err_count;
  unsigned int fix_count;
  unsigned int snip_count;
} s_summary
----------------------------
***/


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


/*** DEPENDENCIES:
static const char *k_idat_size_max_string = "2GB"
----------------------------
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
png_uint_32 png_get_tRNS(png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color)
{
  png_uint_32 retval = 0;
  if (((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0010U) != 0))
  {
    (void) 0;
    if (info_ptr->color_type == (2 | 1))
    {
      if (trans_alpha != 0)
      {
        *trans_alpha = info_ptr->trans_alpha;
        retval |= 0x0010U;
      }
      if (trans_color != 0)
      {
        *trans_color = &info_ptr->trans_color;
      }
    }
    else
    {
      if (trans_color != 0)
      {
        *trans_color = &info_ptr->trans_color;
        retval |= 0x0010U;
      }
      if (trans_alpha != 0)
      {
        *trans_alpha = 0;
      }
    }
    if (num_trans != 0)
    {
      *num_trans = info_ptr->num_trans;
      retval |= 0x0010U;
    }
  }
  return retval;
}


----------------------------
typedef png_struct *png_structp
----------------------------
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
} s_image
----------------------------
typedef struct png_info_def png_info
----------------------------
png_uint_32 png_get_IHDR(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_type, int *compression_type, int *filter_type)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return 0;
  }
  if (width != 0)
  {
    *width = info_ptr->width;
  }
  if (height != 0)
  {
    *height = info_ptr->height;
  }
  if (bit_depth != 0)
  {
    *bit_depth = info_ptr->bit_depth;
  }
  if (color_type != 0)
  {
    *color_type = info_ptr->color_type;
  }
  if (compression_type != 0)
  {
    *compression_type = info_ptr->compression_type;
  }
  if (filter_type != 0)
  {
    *filter_type = info_ptr->filter_type;
  }
  if (interlace_type != 0)
  {
    *interlace_type = info_ptr->interlace_type;
  }
  png_check_IHDR(png_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, info_ptr->color_type, info_ptr->interlace_type, info_ptr->compression_type, info_ptr->filter_type);
  return 1;
}


----------------------------
typedef png_info *png_infop
----------------------------
int png_get_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_unknown_chunkpp unknowns)
{
  if (((png_ptr != 0) && (info_ptr != 0)) && (unknowns != 0))
  {
    *unknowns = info_ptr->unknown_chunks;
    return info_ptr->unknown_chunks_num;
  }
  return 0;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_uint_32 png_get_PLTE(png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette)
{
  (void) 0;
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0008U) != 0)) && (palette != 0))
  {
    *palette = info_ptr->palette;
    *num_palette = info_ptr->num_palette;
    (void) 0;
    return 0x0008U;
  }
  return 0;
}


----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
png_uint_32 png_get_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_color_16p *background)
{
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0020U) != 0)) && (background != 0))
  {
    (void) 0;
    *background = &info_ptr->background;
    return 0x0020U;
  }
  return 0;
}


----------------------------
png_uint_32 png_get_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit)
{
  (void) 0;
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0002U) != 0)) && (sig_bit != 0))
  {
    *sig_bit = &info_ptr->sig_bit;
    return 0x0002U;
  }
  return 0;
}


----------------------------
png_uint_32 png_get_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist)
{
  (void) 0;
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0040U) != 0)) && (hist != 0))
  {
    *hist = info_ptr->hist;
    return 0x0040U;
  }
  return 0;
}


----------------------------
***/


// hint:  ['reductions_ref is a mutable refrence to png_uint_32', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
static png_structp s_read_ptr
----------------------------
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
} s_image
----------------------------
typedef unsigned int png_uint_32
----------------------------
static struct opng_options s_options
----------------------------
static png_infop s_read_info_ptr
----------------------------
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


----------------------------
struct exception_context the_exception_context[1]
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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
} s_process
----------------------------
***/


// hint:  ['reductions_ref is a mutable refrence to png_uint_32', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
struct exception_context the_exception_context[1]
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
***/


// hint:  ['reductions_ref is a mutable refrence to png_uint_32', 'status_ref is a mutable refrence to opng_status_t']
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


/*** DEPENDENCIES:
struct exception_context the_exception_context[1]
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
static struct opng_options s_options
----------------------------
typedef unsigned int opng_bitset_t
----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set)
{
  opng_bitset_t result;
  const char *ptr;
  unsigned int ptr_idx = 0;
  int state;
  int num;
  int num1;
  int num2;
  int err_invalid;
  int err_range;
  result = 0U;
  ptr_idx = rangeset_str;
  state = 0;
  err_invalid = (err_range = 0);
  num1 = (num2 = -1);
  for (;;)
  {
    helper_opng_strparse_rangeset_to_bitset_1(&result, &ptr_idx, &state, &num, &num1, &num2, &err_invalid, &err_range, mask_set, ptr);
  }

  {
    while (isspace(*(&ptr[ptr_idx])))
    {
      ptr_idx += 1;
    }

  }
  ;
  if (ptr[ptr_idx] != '\0')
  {
    err_invalid = 1;
  }
  if (err_invalid)
  {
    *out_set = 0U;
    return -1;
  }
  else
    if (err_range)
  {
    *out_set = ~0U;
    return -1;
  }
  else
  {
    *out_set = result;
    return 0;
  }
}


----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
static void (*usr_progress)(unsigned long num, unsigned long denom)
----------------------------
typedef unsigned int opng_bitset_t
----------------------------
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


----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL
----------------------------
static void (*usr_print_cntrl)(int cntrl_code)
----------------------------
int opng_bitset_find_first(opng_bitset_t set)
{
  int i;
  for (i = 0; i <= OPNG_BITSET_ELT_MAX; i += 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}


----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr)
{
  png_structrp png_ptr = 0;
  (void) 0;
  if (png_ptr_ptr != 0)
  {
    png_ptr = *png_ptr_ptr;
  }
  if (png_ptr == 0)
  {
    return;
  }
  png_destroy_info_struct(png_ptr, end_info_ptr_ptr);
  png_destroy_info_struct(png_ptr, info_ptr_ptr);
  *png_ptr_ptr = 0;
  png_read_destroy(png_ptr);
  png_destroy_png_struct(png_ptr);
}


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
static png_structp s_read_ptr
----------------------------
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


----------------------------
typedef unsigned int png_uint_32
----------------------------
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


----------------------------
static png_infop s_read_info_ptr
----------------------------
struct exception_context the_exception_context[1]
----------------------------
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


----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
struct exception_context the_exception_context[1]
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
int opng_os_rename(const char *src_path, const char *dest_path, int clobber)
{
  if (!clobber)
  {
    if (access(dest_path, 0) >= 0)
    {
      return -1;
    }
  }
  return rename(src_path, dest_path);
}


----------------------------
static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}


----------------------------
int opng_os_unlink(const char *path)
{
  return unlink(path);
}


----------------------------
***/


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


/*** DEPENDENCIES:
static const struct opng_preset_struct
{
  const char *compr_level;
  const char *mem_level;
  const char *strategy;
  const char *filter;
} k_presets[7 + 1] = {{"", "", "", ""}, {"", "", "", ""}, {"9", "8", "0-", "0,5"}, {"9", "8-9", "0-", "0,5"}, {"9", "8", "0-", "0-"}, {"9", "8-9", "0-", "0-"}, {"1-9", "8", "0-", "0-"}, {"1-9", "8-9", "0-", "0-"}}
----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
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
} s_image
----------------------------
static struct opng_options s_options
----------------------------
typedef unsigned int opng_bitset_t
----------------------------
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


----------------------------
static const opng_fsize_t k_idat_size_max = (png_uint_32) 0x7fffffffL
----------------------------
unsigned int opng_bitset_count(opng_bitset_t set)
{
  unsigned int result;
  result = 0;
  while (set != 0)
  {
    set &= set - 1;
    result += 1;
  }

  return result;
}


----------------------------
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
} s_process
----------------------------
***/


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


/*** DEPENDENCIES:
char *opng_path_make_backup(char *buffer, size_t bufsize, const char *path)
{
  static const char bak_extname[] = ".bak";
  if ((strlen(path) + (sizeof(bak_extname))) > bufsize)
  {
    return 0;
  }
  strcpy(buffer, path);
  strcat(buffer, bak_extname);
  return buffer;
}


----------------------------
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


----------------------------
static struct opng_options s_options
----------------------------
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


----------------------------
int opng_os_test_file_equiv(const char *path1, const char *path2)
{
  struct stat sbuf1;
  struct stat sbuf2;
  if ((stat(path1, &sbuf1) != 0) || (stat(path2, &sbuf2) != 0))
  {
    return -1;
  }
  if ((sbuf1.st_dev == sbuf2.st_dev) && (sbuf1.st_ino == sbuf2.st_ino))
  {
    return (sbuf1.st_ino != 0) ? (1) : (-1);
  }
  else
  {
    return 0;
  }
}


----------------------------
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


----------------------------
int opng_os_unlink(const char *path)
{
  return unlink(path);
}


----------------------------
static void (*usr_panic)(const char *msg)
----------------------------
char *opng_path_replace_ext(char *buffer, size_t bufsize, const char *old_path, const char *new_extname)
{
  unsigned int new_extname_idx = 0;
  size_t i;
  size_t pos;
  if (new_extname[0 + new_extname_idx] != '.')
  {
    return 0;
  }
  for (i = 0, pos = (size_t) (-1); old_path[i] != '\0'; i += 1)
  {
    if (i >= bufsize)
    {
      return 0;
    }
    if ((buffer[i] = old_path[i]) == '.')
    {
      pos = i;
    }
  }

  if (i > pos)
  {
    i = pos;
  }
  for (;; i += 1, new_extname_idx += 1)
  {
    if (i >= bufsize)
    {
      return 0;
    }
    if ((buffer[i] = new_extname[new_extname_idx]) == '\0')
    {
      return buffer;
    }
  }

}


----------------------------
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


----------------------------
int opng_os_create_dir(const char *dirname)
{
  if (dirname[0] == '\0')
  {
    return 0;
  }
  {
    struct stat sbuf;
    if (stat(dirname, &sbuf) == 0)
    {
      return (sbuf.st_mode & S_IFDIR) ? (0) : (-1);
    }
    return mkdir(dirname, 0777);
  }
}


----------------------------
char *opng_path_replace_dir(char *buffer, size_t bufsize, const char *old_path, const char *new_dirname)
{
  const char *path;
  unsigned int path_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  size_t dirlen;
  path_idx = old_path;
  for (;;)
  {
    ptr_idx = strpbrk(path, "/");
    if ((&ptr[ptr_idx]) == 0)
    {
      break;
    }
    path_idx = (&ptr[ptr_idx]) + 1;
  }

  dirlen = strlen(new_dirname);
  if (((dirlen + strlen(path)) + 2) >= bufsize)
  {
    return 0;
  }
  if (dirlen > 0)
  {
    strcpy(buffer, new_dirname);
    {
      if (strchr("/", buffer[dirlen - 1]) == 0)
      {
        buffer[dirlen] = '/';
        dirlen += 1;
      }
    }
  }
  strcpy(buffer + dirlen, path);
  return buffer;
}


----------------------------
int opng_os_copy_file_attr(const char *src_path, const char *dest_path)
{
  struct stat sbuf;
  int result;
  if (stat(src_path, &sbuf) != 0)
  {
    return -1;
  }
  result = 0;
  if (chown(dest_path, sbuf.st_uid, sbuf.st_gid) != 0)
  {
  }
  if (chmod(dest_path, sbuf.st_mode) != 0)
  {
    result = -1;
  }
  {
    struct utimbuf utbuf;
    utbuf.actime = sbuf.st_atime;
    utbuf.modtime = sbuf.st_mtime;
    if (utime(dest_path, &utbuf) != 0)
    {
      result = -1;
    }
  }
  return result;
}


----------------------------
static void opng_throw_error(png_const_charp msg)
{
  opng_print_error(msg);
  for (;; longjmp(*the_exception_context->penv, 1))
  {
    the_exception_context->v.etmp = OPNG_STATUS_ERR_OPTIPNG;
  }

}


----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
static void opng_check_idat_size(opng_fsize_t size)
{
  if (size > k_idat_size_max)
  {
    opng_throw_error("IDAT sizes larger than the maximum chunk size are currently unsupported");
  }
}


----------------------------
int opng_os_test_file_access(const char *path, const char *mode)
{
  int faccess;
  int freg;
  faccess = (freg = 0);
  if (strchr(mode, 'f') != 0)
  {
    freg = 1;
  }
  if (strchr(mode, 'r') != 0)
  {
    faccess |= 4;
  }
  if (strchr(mode, 'w') != 0)
  {
    faccess |= 2;
  }
  if (strchr(mode, 'x') != 0)
  {
    faccess |= 1;
  }
  if ((faccess == 0) && (!freg))
  {
    if (strchr(mode, 'e') == 0)
    {
      return 0;
    }
  }
  {
    struct stat sbuf;
    if (stat(path, &sbuf) != 0)
    {
      return -1;
    }
    if (freg && ((sbuf.st_mode & S_IFREG) != S_IFREG))
    {
      return -1;
    }
    if (faccess == 0)
    {
      return 0;
    }
    return access(path, faccess);
  }
}


----------------------------
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


----------------------------
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
} s_process
----------------------------
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


----------------------------
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


----------------------------
struct exception_context the_exception_context[1]
----------------------------
int opng_os_rename(const char *src_path, const char *dest_path, int clobber)
{
  if (!clobber)
  {
    if (access(dest_path, 0) >= 0)
    {
      return -1;
    }
  }
  return rename(src_path, dest_path);
}


----------------------------
static void opng_print_warning(const char *msg)
{
  usr_print_cntrl('\v');
  usr_printf("Warning: %s\n", msg);
}


----------------------------
***/


// hint:  ['result_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
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


----------------------------
static struct opng_options s_options
----------------------------
struct exception_context the_exception_context[1]
----------------------------
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
} s_process
----------------------------
static struct opng_summary_struct
{
  unsigned int file_count;
  unsigned int err_count;
  unsigned int fix_count;
  unsigned int snip_count;
} s_summary
----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
struct opng_ui
{
  void (*printf_fn)(const char *fmt, ...);
  void (*print_cntrl_fn)(int cntrl_code);
  void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
  void (*panic_fn)(const char *msg);
}
----------------------------
static void (*usr_progress)(unsigned long num, unsigned long denom)
----------------------------
static struct opng_options s_options
----------------------------
static struct opng_engine_struct
{
  int started;
} s_engine
----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
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
}
----------------------------
static void (*usr_print_cntrl)(int cntrl_code)
----------------------------
static struct opng_summary_struct
{
  unsigned int file_count;
  unsigned int err_count;
  unsigned int fix_count;
  unsigned int snip_count;
} s_summary
----------------------------
***/


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


/*** DEPENDENCIES:
static void (*usr_panic)(const char *msg)
----------------------------
static void opng_clear_image_info(void)
{
  memset(&s_image, 0, sizeof(s_image));
}


----------------------------
static struct opng_engine_struct
{
  int started;
} s_engine
----------------------------
struct exception_context the_exception_context[1]
----------------------------
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


----------------------------
static void (*usr_printf)(const char *fmt, ...)
----------------------------
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
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


----------------------------
static struct opng_summary_struct
{
  unsigned int file_count;
  unsigned int err_count;
  unsigned int fix_count;
  unsigned int snip_count;
} s_summary
----------------------------
***/


