static void pngx_gif_warning(const char *msg)
{
  png_warning(err_png_ptr, msg);
}


/*** DEPENDENCIES:
static png_structp err_png_ptr = 0
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
static const char gif_fmt_long_name[] = "Graphics Interchange Format"
----------------------------
static const png_byte gif_sig_gif87a[6] = {0x47, 0x49, 0x46, 0x38, 0x37, 0x61}
----------------------------
typedef unsigned char png_byte
----------------------------
static const png_byte gif_sig_gif89a[6] = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61}
----------------------------
typedef const char *png_const_charp
----------------------------
static const char gif_fmt_name[] = "GIF"
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef const char **png_const_charpp
----------------------------
***/


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


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
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
***/


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


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
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
***/


// hint:  ['image_ref is a mutable refrence to ', 'blockCode_ref is a mutable refrence to int', 'transparent_ref is a mutable refrence to unsigned int', 'numImages_ref is a mutable refrence to unsigned int']
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


/*** DEPENDENCIES:
struct GIFExtension
{
  struct GIFScreen *Screen;
  unsigned char *Buffer;
  unsigned int BufferSize;
  unsigned char Label;
}
----------------------------
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


----------------------------
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


----------------------------
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext, FILE *stream)
{
  int ch;
  int foundBogus;
  foundBogus = 0;
  for (;;)
  {
    ch = GetByte(stream);
    switch (ch)
    {
      case 0x2c:
      {
        GIFReadNextImage(image, stream);
        return ch;
      }

      case 0x21:
      {
        GIFReadNextExtension(ext, stream);
        return ch;
      }

      case 0x3b:
      {
        return ch;
      }

      default:
      {
        if (!foundBogus)
        {
          GIFWarning("Bogus data in GIF file");
        }
        foundBogus = 1;
      }

    }

  }

}


----------------------------
typedef png_struct *png_structp
----------------------------
void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt, struct GIFExtension *ext)
{
  unsigned char *buffer;
  unsigned int buffer_idx = 0;
  (void) 0;
  if (ext->Label != 0xf9)
  {
    GIFWarning("Not a graphic control extension in GIF file");
    return;
  }
  if (ext->BufferSize < 4)
  {
    GIFWarning("Broken graphic control extension in GIF file");
    return;
  }
  buffer_idx = ext->Buffer;
  graphicExt->DisposalMethod = (buffer[0 + buffer_idx] >> 2) & 0x07;
  graphicExt->InputFlag = (buffer[0 + buffer_idx] >> 1) & 0x01;
  graphicExt->TransparentFlag = buffer[0 + buffer_idx] & 0x01;
  graphicExt->DelayTime = ((&buffer[buffer_idx]) + 1)[0] + (((&buffer[buffer_idx]) + 1)[1] << 8);
  graphicExt->Transparent = buffer[3 + buffer_idx];
}


----------------------------
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors, struct GIFImage *image)
{
  struct GIFScreen *screen;
  unsigned int screen_idx = 0;
  if (image->LocalColorFlag)
  {
    (void) 0;
    *colors = image->LocalColorTable;
    *numColors = image->LocalNumColors;
    return;
  }
  screen_idx = image->Screen;
  if (screen->GlobalColorFlag)
  {
    (void) 0;
    *colors = screen->GlobalColorTable;
    *numColors = screen->GlobalNumColors;
    return;
  }
  (void) 0;
  *colors = DefaultColorTable;
  *numColors = (sizeof(DefaultColorTable)) / 3;
}


----------------------------
void pngx_set_interlace_type(png_structp png_ptr, png_infop info_ptr, int interlace_type)
{
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int old_interlace_type;
  if (!png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &old_interlace_type, &compression_type, &filter_type))
  {
    return;
  }
  if (interlace_type == old_interlace_type)
  {
    return;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
struct GIFGraphicCtlExt
{
  unsigned int DisposalMethod;
  unsigned int InputFlag;
  unsigned int TransparentFlag;
  unsigned int DelayTime;
  unsigned int Transparent;
}
----------------------------
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
}
----------------------------
***/


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


/*** DEPENDENCIES:
void GIFDestroyImage(struct GIFImage *image)
{
  (void) image;
}


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
void GIFDestroyExtension(struct GIFExtension *ext)
{
  free(ext->Buffer);
}


----------------------------
static png_structp err_png_ptr = 0
----------------------------
***/


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


/*** DEPENDENCIES:
void GIFDestroyExtension(struct GIFExtension *ext)
{
  free(ext->Buffer);
}


----------------------------
typedef png_byte **png_bytepp
----------------------------
extern void (*GIFError)(const char *message)
----------------------------
void GIFDestroyImage(struct GIFImage *image)
{
  (void) image;
}


----------------------------
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


----------------------------
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
}
----------------------------
typedef png_byte *png_bytep
----------------------------
struct GIFExtension
{
  struct GIFScreen *Screen;
  unsigned char *Buffer;
  unsigned int BufferSize;
  unsigned char Label;
}
----------------------------
void GIFInitImage(struct GIFImage *image, struct GIFScreen *screen, unsigned char **rows)
{
  image->Screen = screen;
  image->Rows = rows;
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
----------------------------
void GIFInitExtension(struct GIFExtension *ext, struct GIFScreen *screen, unsigned int initBufferSize)
{
  unsigned char *newBuffer;
  unsigned int newBuffer_idx = 0;
  ext->Screen = screen;
  if (initBufferSize > 0)
  {
    newBuffer_idx = (unsigned char *) malloc(initBufferSize);
    if ((&newBuffer[newBuffer_idx]) == 0)
    {
      ErrorAlloc();
    }
    ext->Buffer = &newBuffer[newBuffer_idx];
    ext->BufferSize = initBufferSize;
  }
  else
  {
    ext->Buffer = 0;
    ext->BufferSize = 0;
  }
}


----------------------------
extern void (*GIFWarning)(const char *message)
----------------------------
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


----------------------------
typedef struct png_info_def png_info
----------------------------
static void pngx_gif_warning(const char *msg)
{
  png_warning(err_png_ptr, msg);
}


----------------------------
typedef unsigned char png_byte
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
void GIFReadScreen(struct GIFScreen *screen, FILE *stream)
{
  unsigned char buffer[7];
  (void) 0;
  ReadBytes(buffer, 6, stream);
  if (memcmp(buffer, "GIF", 3) != 0)
  {
    GIFError("Not a GIF file");
  }
  if ((memcmp(buffer + 3, "87a", 3) != 0) && (memcmp(buffer + 3, "89a", 3) != 0))
  {
    GIFWarning("Invalid GIF version number, not \"87a\" or \"89a\"");
  }
  (void) 0;
  ReadBytes(buffer, 7, stream);
  screen->Width = (buffer + 0)[0] + ((buffer + 0)[1] << 8);
  screen->Height = (buffer + 2)[0] + ((buffer + 2)[1] << 8);
  screen->GlobalColorFlag = (buffer[4] & 0x80) ? (1) : (0);
  screen->ColorResolution = ((buffer[4] & 0x70) >> 3) + 1;
  screen->SortFlag = (buffer[4] & 0x08) ? (1) : (0);
  screen->GlobalNumColors = 2 << (buffer[4] & 0x07);
  screen->Background = buffer[5];
  screen->PixelAspectRatio = buffer[6];
  if (screen->GlobalColorFlag)
  {
    (void) 0;
    ReadBytes(screen->GlobalColorTable, 3 * screen->GlobalNumColors, stream);
  }
  (void) 0;
  if ((screen->Width == 0) || (screen->Height == 0))
  {
    GIFError("Invalid dimensions in GIF image");
  }
  if (screen->Background > 0)
  {
    if ((screen->GlobalColorFlag && (screen->Background >= screen->GlobalNumColors)) || (!screen->GlobalColorFlag))
    {
      screen->Background = 0;
    }
  }
}


----------------------------
typedef png_info *png_infop
----------------------------
static png_structp err_png_ptr = 0
----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler)
{
  return pngx_malloc_rows_extended(png_ptr, info_ptr, 0, filler);
}


----------------------------
struct GIFGraphicCtlExt
{
  unsigned int DisposalMethod;
  unsigned int InputFlag;
  unsigned int TransparentFlag;
  unsigned int DelayTime;
  unsigned int Transparent;
}
----------------------------
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
}
----------------------------
***/


