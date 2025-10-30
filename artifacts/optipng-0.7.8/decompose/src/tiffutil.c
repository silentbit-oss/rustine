static void default_error_handler(const char *msg)
{
  fprintf(stderr, "minitiff: error: %s\n", msg);
  exit(1);
}


/*** DEPENDENCIES:
***/


static void default_warning_handler(const char *msg)
{
  fprintf(stderr, "minitiff: warning: %s\n", msg);
}


/*** DEPENDENCIES:
***/


void minitiff_init_info(struct minitiff_info *info_ptr)
{
  memset(info_ptr, 0, sizeof(*info_ptr));
  info_ptr->photometric = (unsigned int) (-1);
}


/*** DEPENDENCIES:
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
***/


void minitiff_destroy_info(struct minitiff_info *info_ptr)
{
  if (info_ptr->strip_offsets != 0)
  {
    free(info_ptr->strip_offsets);
  }
}


/*** DEPENDENCIES:
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
***/


void minitiff_error(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->error_handler != 0)
  {
    info_ptr->error_handler(msg);
  }
  else
    default_error_handler(msg);
  abort();
}


/*** DEPENDENCIES:
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
static void default_error_handler(const char *msg)
{
  fprintf(stderr, "minitiff: error: %s\n", msg);
  exit(1);
}


----------------------------
***/


void minitiff_validate_info(const struct minitiff_info *info_ptr)
{
  if ((info_ptr->width == 0) || (info_ptr->height == 0))
  {
    minitiff_error(info_ptr, "Invalid image dimensions in TIFF file");
  }
  if ((info_ptr->bits_per_sample == 0) || (info_ptr->samples_per_pixel == 0))
  {
    minitiff_error(info_ptr, "Invalid pixel info in TIFF file");
  }
  if ((info_ptr->strip_offsets == 0) || (info_ptr->rows_per_strip == 0))
  {
    minitiff_error(info_ptr, "Invalid strip info in TIFF file");
  }
  if (info_ptr->compression != MINITIFF_COMPRESSION_NONE)
  {
    minitiff_error(info_ptr, "Unsupported compression method in TIFF file");
  }
  if (info_ptr->photometric >= MINITIFF_PHOTOMETRIC_PALETTE)
  {
    minitiff_error(info_ptr, "Unsupported photometric interpretation in TIFF file");
  }
}


/*** DEPENDENCIES:
void minitiff_error(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->error_handler != 0)
  {
    info_ptr->error_handler(msg);
  }
  else
    default_error_handler(msg);
  abort();
}


----------------------------
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
***/


void minitiff_warning(const struct minitiff_info *info_ptr, const char *msg)
{
  if (info_ptr->warning_handler != 0)
  {
    info_ptr->warning_handler(msg);
  }
  else
    default_warning_handler(msg);
}


/*** DEPENDENCIES:
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
static void default_warning_handler(const char *msg)
{
  fprintf(stderr, "minitiff: warning: %s\n", msg);
}


----------------------------
***/


