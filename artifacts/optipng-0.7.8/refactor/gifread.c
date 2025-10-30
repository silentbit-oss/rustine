#include <gifread.c>
#include <gifread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
static void GIFReadNextImage(struct GIFImage *image, FILE *stream);
static void GIFReadImageData(struct GIFImage *image, FILE *stream);
static int GIFReadDataBlock(unsigned char *buffer, FILE *stream);
static void GIFSkipDataBlocks(FILE *stream);
static int LZWGetCode(int code_size, int init_flag, FILE *stream);
static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream);
static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream);
static int GetByte(FILE *stream);
static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream);
static void ErrorAlloc(void);
static void ErrorRead(FILE *stream);
static void DefaultError(const char *message);
static void DefaultWarning(const char *message);
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

void GIFInitImage(struct GIFImage *image, struct GIFScreen *screen, unsigned char **rows)
{
  image->Screen = screen;
  image->Rows = rows;
}

void GIFDestroyImage(struct GIFImage *image)
{
  (void) image;
}

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

static void GIFReadNextImage(struct GIFImage *image, FILE *stream)
{
  struct GIFScreen *screen;
  unsigned int screen_idx = 0;
  unsigned char buffer[9];
  (void) 0;
  ReadBytes(buffer, 9, stream);
  if (image == 0)
  {
    GIFSkipDataBlocks(stream);
    return;
  }
  image->LeftPos = (buffer + 0)[0] + ((buffer + 0)[1] << 8);
  image->TopPos = (buffer + 2)[0] + ((buffer + 2)[1] << 8);
  image->Width = (buffer + 4)[0] + ((buffer + 4)[1] << 8);
  image->Height = (buffer + 6)[0] + ((buffer + 6)[1] << 8);
  image->LocalColorFlag = (buffer[8] & 0x80) ? (1) : (0);
  image->InterlaceFlag = (buffer[8] & 0x40) ? (1) : (0);
  image->SortFlag = (buffer[8] & 0x20) ? (1) : (0);
  image->LocalNumColors = (image->LocalColorFlag) ? (2 << (buffer[8] & 0x07)) : (0);
  if (image->LocalColorFlag)
  {
    (void) 0;
    ReadBytes(image->LocalColorTable, 3 * image->LocalNumColors, stream);
  }
  (void) 0;
  screen_idx = image->Screen;
  if ((((image->Width == 0) || (image->Height == 0)) || ((image->LeftPos + image->Width) > screen->Width)) || ((image->TopPos + image->Height) > screen->Height))
  {
    GIFError("Invalid dimensions in GIF image");
  }
  GIFReadImageData(image, stream);
}

static void GIFReadImageData(struct GIFImage *image, FILE *stream)
{
  int minCodeSize;
  unsigned char **rows;
  unsigned int rows_idx = 0;
  unsigned int width;
  unsigned int height;
  unsigned int interlaced;
  unsigned char *colors;
  unsigned int numColors;
  unsigned int xpos;
  unsigned int ypos;
  int pass;
  int val;
  (void) 0;
  minCodeSize = GetByte(stream);
  if (minCodeSize >= 12)
  {
    GIFError("Invalid LZW code size");
  }
  if (LZWDecodeByte(1, minCodeSize, stream) < 0)
  {
    GIFError("Error decoding GIF image");
  }
  rows_idx = image->Rows;
  if ((&rows[rows_idx]) == 0)
  {
    GIFSkipDataBlocks(stream);
    return;
  }
  width = image->Width;
  height = image->Height;
  interlaced = image->InterlaceFlag;
  GIFGetColorTable(&colors, &numColors, image);
  xpos = (ypos = 0);
  pass = 0;
  while ((val = LZWDecodeByte(0, minCodeSize, stream)) >= 0)
  {
    helper_GIFReadImageData_1(&rows_idx, &xpos, &ypos, &val, rows, width, height, interlaced, numColors, pass);
  }

  fini:
  while (LZWDecodeByte(0, minCodeSize, stream) >= 0)
  {
  }


}

static int DataBlockSize = 0;
static int GIFReadDataBlock(unsigned char *buffer, FILE *stream)
{
  int count;
  count = GetByte(stream);
  DataBlockSize = count;
  if (count > 0)
  {
    ReadBytes(buffer, count, stream);
  }
  return count;
}

static void GIFSkipDataBlocks(FILE *stream)
{
  int count;
  unsigned char buffer[256];
  for (;;)
  {
    count = GetByte(stream);
    if (count > 0)
    {
      ReadBytes(buffer, count, stream);
    }
    else
      return;
  }

}

static int LZWGetCode(int code_size, int init_flag, FILE *stream)
{
  static unsigned char buffer[280];
  static int curbit;
  static int lastbit;
  static int done;
  static int last_byte;
  int count;
  int i;
  int j;
  int ret;
  if (init_flag)
  {
    curbit = 0;
    lastbit = 0;
    last_byte = 2;
    done = 0;
    return 0;
  }
  if ((curbit + code_size) >= lastbit)
  {
    helper_LZWGetCode_1(&curbit, &lastbit, &done, &last_byte, &count, stream, buffer);
  }
  if (code_size && ((((size_t) ((curbit + code_size) - 1)) / 8) >= (sizeof(buffer))))
  {
    GIFError("Malformed GIF (CVE-2023-43907)");
  }
  ret = 0;
  for (i = curbit, j = 0; j < code_size; i += 1, j += 1)
  {
    ret |= ((buffer[i / 8] & (1 << (i % 8))) != 0) << j;
  }

  curbit += code_size;
  return ret;
}

static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream)
{
  static int fresh = 0;
  static int code_size;
  static int set_code_size;
  static int max_code;
  static int max_code_size;
  static int firstcode;
  static int oldcode;
  static int clear_code;
  static int end_code;
  static int table[2][((1 << 12) - 1) + 1];
  static int stack[(((1 << 12) - 1) + 1) * 2];
  static int *sp;
  unsigned int sp_idx = 0;
  int code;
  int incode;
  int i;
  if (init_flag)
  {
    helper_LZWDecodeByte_1(&fresh, &code_size, &set_code_size, &max_code, &max_code_size, &clear_code, &end_code, &sp_idx, &i, input_code_size, stream, table, stack);
  }
  else
    if (fresh)
  {
    fresh = 0;
    do
    {
      firstcode = (oldcode = LZWGetCode(code_size, 0, stream));
    }
    while (firstcode == clear_code);
    return firstcode;
  }
  if ((&sp[sp_idx]) > stack)
  {
    sp_idx -= 1;
    return sp[sp_idx];
  }
  while ((code = LZWGetCode(code_size, 0, stream)) >= 0)
  {
    helper_LZWDecodeByte_2(&code_size, &max_code, &max_code_size, &firstcode, &oldcode, &sp_idx, &code, &incode, &i, stream, set_code_size, clear_code, end_code, table, stack, sp);
  }

  return code;
}

static unsigned char DefaultColorTable[] = {0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 255, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 255, 0};
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

void GIFDestroyExtension(struct GIFExtension *ext)
{
  free(ext->Buffer);
}

static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream)
{
  unsigned char *newBuffer;
  unsigned int newBuffer_idx = 0;
  unsigned int newBufferSize;
  unsigned int offset;
  unsigned int len;
  int count;
  int label;
  label = GetByte(stream);
  (void) 0;
  if (ext == 0)
  {
    GIFSkipDataBlocks(stream);
    return;
  }
  ext->Label = (unsigned char) label;
  offset = 0;
  len = ext->BufferSize;
  for (;;)
  {
    if (len < 255)
    {
      newBufferSize = ext->BufferSize + 1024;
      newBuffer_idx = (unsigned char *) realloc(ext->Buffer, newBufferSize);
      if ((&newBuffer[newBuffer_idx]) == 0)
      {
        ErrorAlloc();
      }
      ext->BufferSize = newBufferSize;
      ext->Buffer = &newBuffer[newBuffer_idx];
      len += 1024;
    }
    count = GIFReadDataBlock(ext->Buffer + offset, stream);
    if (count == 0)
    {
      break;
    }
    offset += count;
    len -= count;
  }

}

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

static int GetByte(FILE *stream)
{
  int ch;
  if ((ch = getc(stream)) == EOF)
  {
    ErrorRead(stream);
  }
  return ch;
}

static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream)
{
  if (fread(buffer, count, 1, stream) != 1)
  {
    ErrorRead(stream);
  }
}

static void ErrorAlloc(void)
{
  GIFError("Out of memory in GIF decoder");
}

static void ErrorRead(FILE *stream)
{
  if (ferror(stream))
  {
    GIFError("Error reading GIF file");
  }
  else
    GIFError("Unexpected end of GIF file");
}

static void DefaultError(const char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(1);
}

static void DefaultWarning(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

void (*GIFError)(const char *message) = DefaultError;
void (*GIFWarning)(const char *message) = DefaultWarning;

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
static void GIFReadNextImage(struct GIFImage *image, FILE *stream);
static void GIFReadImageData(struct GIFImage *image, FILE *stream);
static int GIFReadDataBlock(unsigned char *buffer, FILE *stream);
static void GIFSkipDataBlocks(FILE *stream);
static int LZWGetCode(int code_size, int init_flag, FILE *stream);
static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream);
static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream);
static int GetByte(FILE *stream);
static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream);
static void ErrorAlloc(void);
static void ErrorRead(FILE *stream);
static void DefaultError(const char *message);
static void DefaultWarning(const char *message);
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

void GIFInitImage(struct GIFImage *image, struct GIFScreen *screen, unsigned char **rows)
{
  image->Screen = screen;
  image->Rows = rows;
}

void GIFDestroyImage(struct GIFImage *image)
{
  (void) image;
}

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
        GIFReadNextImage(image, stream);
        return ch;

      case 0x21:
        GIFReadNextExtension(ext, stream);
        return ch;

      case 0x3b:
        return ch;

      default:
        if (!foundBogus)
      {
        GIFWarning("Bogus data in GIF file");
      }
        foundBogus = 1;

    }

  }

}

static void GIFReadNextImage(struct GIFImage *image, FILE *stream)
{
  struct GIFScreen *screen;
  unsigned int screen_idx = 0;
  unsigned char buffer[9];
  (void) 0;
  ReadBytes(buffer, 9, stream);
  if (image == 0)
  {
    GIFSkipDataBlocks(stream);
    return;
  }
  image->LeftPos = (buffer + 0)[0] + ((buffer + 0)[1] << 8);
  image->TopPos = (buffer + 2)[0] + ((buffer + 2)[1] << 8);
  image->Width = (buffer + 4)[0] + ((buffer + 4)[1] << 8);
  image->Height = (buffer + 6)[0] + ((buffer + 6)[1] << 8);
  image->LocalColorFlag = (buffer[8] & 0x80) ? (1) : (0);
  image->InterlaceFlag = (buffer[8] & 0x40) ? (1) : (0);
  image->SortFlag = (buffer[8] & 0x20) ? (1) : (0);
  image->LocalNumColors = (image->LocalColorFlag) ? (2 << (buffer[8] & 0x07)) : (0);
  if (image->LocalColorFlag)
  {
    (void) 0;
    ReadBytes(image->LocalColorTable, 3 * image->LocalNumColors, stream);
  }
  (void) 0;
  screen_idx = image->Screen;
  if ((((image->Width == 0) || (image->Height == 0)) || ((image->LeftPos + image->Width) > screen->Width)) || ((image->TopPos + image->Height) > screen->Height))
  {
    GIFError("Invalid dimensions in GIF image");
  }
  GIFReadImageData(image, stream);
}

static void GIFReadImageData(struct GIFImage *image, FILE *stream)
{
  int minCodeSize;
  unsigned char **rows;
  unsigned int rows_idx = 0;
  unsigned int width;
  unsigned int height;
  unsigned int interlaced;
  unsigned char *colors;
  unsigned int numColors;
  unsigned int xpos;
  unsigned int ypos;
  int pass;
  int val;
  (void) 0;
  minCodeSize = GetByte(stream);
  if (minCodeSize >= 12)
  {
    GIFError("Invalid LZW code size");
  }
  if (LZWDecodeByte(1, minCodeSize, stream) < 0)
  {
    GIFError("Error decoding GIF image");
  }
  rows_idx = image->Rows;
  if ((&rows[rows_idx]) == 0)
  {
    GIFSkipDataBlocks(stream);
    return;
  }
  width = image->Width;
  height = image->Height;
  interlaced = image->InterlaceFlag;
  GIFGetColorTable(&colors, &numColors, image);
  xpos = (ypos = 0);
  pass = 0;
  while ((val = LZWDecodeByte(0, minCodeSize, stream)) >= 0)
  {
    if (((unsigned int) val) >= numColors)
    {
      GIFWarning("Pixel value out of range in GIF image");
      val = numColors - 1;
    }
    rows[ypos + rows_idx][xpos] = (unsigned char) val;
    if ((++xpos) == width)
    {
      xpos = 0;
      ypos += 1;
      if (interlaced)
      {
        switch (pass)
        {
          case 0:

          case 1:
            ypos += 8;
            break;

          case 2:
            ypos += 4;
            break;

          case 3:
            ypos += 2;
            break;

        }

        if (ypos >= height)
        {
          switch (++pass)
          {
            case 1:
              ypos = 4;
              break;

            case 2:
              ypos = 2;
              break;

            case 3:
              ypos = 1;
              break;

            default:
              goto fini;

          }

        }
      }
      else
        ++ypos;
    }
    if (ypos >= height)
    {
      break;
    }
  }

  fini:
  while (LZWDecodeByte(0, minCodeSize, stream) >= 0)
  {
  }


}

static int DataBlockSize = 0;
static int GIFReadDataBlock(unsigned char *buffer, FILE *stream)
{
  int count;
  count = GetByte(stream);
  DataBlockSize = count;
  if (count > 0)
  {
    ReadBytes(buffer, count, stream);
  }
  return count;
}

static void GIFSkipDataBlocks(FILE *stream)
{
  int count;
  unsigned char buffer[256];
  for (;;)
  {
    count = GetByte(stream);
    if (count > 0)
    {
      ReadBytes(buffer, count, stream);
    }
    else
      return;
  }

}

static int LZWGetCode(int code_size, int init_flag, FILE *stream)
{
  static unsigned char buffer[280];
  static int curbit;
  static int lastbit;
  static int done;
  static int last_byte;
  int count;
  int i;
  int j;
  int ret;
  if (init_flag)
  {
    curbit = 0;
    lastbit = 0;
    last_byte = 2;
    done = 0;
    return 0;
  }
  if ((curbit + code_size) >= lastbit)
  {
    if (done)
    {
      if (curbit >= lastbit)
      {
        GIFError("Ran off the end of input bits in LZW decoding");
      }
      return -1;
    }
    buffer[0] = buffer[last_byte - 2];
    buffer[1] = buffer[last_byte - 1];
    if ((count = GIFReadDataBlock(&buffer[2], stream)) == 0)
    {
      done = 1;
    }
    last_byte = 2 + count;
    curbit = (curbit - lastbit) + 16;
    lastbit = (2 + count) * 8;
  }
  if (code_size && ((((size_t) ((curbit + code_size) - 1)) / 8) >= (sizeof(buffer))))
  {
    GIFError("Malformed GIF (CVE-2023-43907)");
  }
  ret = 0;
  for (i = curbit, j = 0; j < code_size; i += 1, j += 1)
  {
    ret |= ((buffer[i / 8] & (1 << (i % 8))) != 0) << j;
  }

  curbit += code_size;
  return ret;
}

static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream)
{
  static int fresh = 0;
  static int code_size;
  static int set_code_size;
  static int max_code;
  static int max_code_size;
  static int firstcode;
  static int oldcode;
  static int clear_code;
  static int end_code;
  static int table[2][((1 << 12) - 1) + 1];
  static int stack[(((1 << 12) - 1) + 1) * 2];
  static int *sp;
  unsigned int sp_idx = 0;
  int code;
  int incode;
  int i;
  if (init_flag)
  {
    fresh = 1;
    set_code_size = input_code_size;
    code_size = set_code_size + 1;
    clear_code = 1 << set_code_size;
    end_code = clear_code + 1;
    max_code_size = 2 * clear_code;
    max_code = clear_code + 2;
    LZWGetCode(0, 1, stream);
    for (i = 0; i < clear_code; i += 1)
    {
      table[0][i] = 0;
      table[1][i] = i;
    }

    for (; i <= ((1 << 12) - 1); i += 1)
    {
      table[0][i] = 0;
      table[1][i] = 0;
    }

    sp_idx = stack;
    return 0;
  }
  else
    if (fresh)
  {
    fresh = 0;
    do
    {
      firstcode = (oldcode = LZWGetCode(code_size, 0, stream));
    }
    while (firstcode == clear_code);
    return firstcode;
  }
  if ((&sp[sp_idx]) > stack)
  {
    sp_idx -= 1;
    return sp[sp_idx];
  }
  while ((code = LZWGetCode(code_size, 0, stream)) >= 0)
  {
    if (code == clear_code)
    {
      for (i = 0; i < clear_code; i += 1)
      {
        table[0][i] = 0;
        table[1][i] = i;
      }

      for (; i <= ((1 << 12) - 1); i += 1)
      {
        table[0][i] = 0;
        table[1][i] = 0;
      }

      code_size = set_code_size + 1;
      max_code_size = 2 * clear_code;
      max_code = clear_code + 2;
      sp_idx = stack;
      firstcode = (oldcode = LZWGetCode(code_size, 0, stream));
      return firstcode;
    }
    else
      if (code == end_code)
    {
      int count;
      unsigned char buffer[260];
      if (DataBlockSize == 0)
      {
        return -2;
      }
      while ((count = GIFReadDataBlock(buffer, stream)) > 0)
      {
      }

      (void) count;
      return -2;
    }
    incode = code;
    if (code >= max_code)
    {
      sp[sp_idx] = firstcode;
      sp_idx += 1;
      code = oldcode;
    }
    while (code >= clear_code)
    {
      sp[sp_idx] = table[1][code];
      sp_idx += 1;
      if ((code == table[0][code]) || (((size_t) ((&sp[sp_idx]) - stack)) >= ((sizeof(stack)) / (sizeof(stack[0])))))
      {
        GIFError("Circular dependency found in LZW table");
      }
      code = table[0][code];
    }

    sp[sp_idx] = (firstcode = table[1][code]);
    sp_idx += 1;
    if ((code = max_code) <= ((1 << 12) - 1))
    {
      table[0][code] = oldcode;
      table[1][code] = firstcode;
      max_code += 1;
      if ((max_code >= max_code_size) && (max_code_size <= ((1 << 12) - 1)))
      {
        max_code_size *= 2;
        code_size += 1;
      }
    }
    oldcode = incode;
    if ((&sp[sp_idx]) > stack)
    {
      sp_idx -= 1;
      return sp[sp_idx];
    }
  }

  return code;
}

static unsigned char DefaultColorTable[] = {0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 255, 255, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255, 255, 0};
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

void GIFDestroyExtension(struct GIFExtension *ext)
{
  free(ext->Buffer);
}

static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream)
{
  unsigned char *newBuffer;
  unsigned int newBuffer_idx = 0;
  unsigned int newBufferSize;
  unsigned int offset;
  unsigned int len;
  int count;
  int label;
  label = GetByte(stream);
  (void) 0;
  if (ext == 0)
  {
    GIFSkipDataBlocks(stream);
    return;
  }
  ext->Label = (unsigned char) label;
  offset = 0;
  len = ext->BufferSize;
  for (;;)
  {
    if (len < 255)
    {
      newBufferSize = ext->BufferSize + 1024;
      newBuffer_idx = (unsigned char *) realloc(ext->Buffer, newBufferSize);
      if ((&newBuffer[newBuffer_idx]) == 0)
      {
        ErrorAlloc();
      }
      ext->BufferSize = newBufferSize;
      ext->Buffer = &newBuffer[newBuffer_idx];
      len += 1024;
    }
    count = GIFReadDataBlock(ext->Buffer + offset, stream);
    if (count == 0)
    {
      break;
    }
    offset += count;
    len -= count;
  }

}

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

static int GetByte(FILE *stream)
{
  int ch;
  if ((ch = getc(stream)) == EOF)
  {
    ErrorRead(stream);
  }
  return ch;
}

static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream)
{
  if (fread(buffer, count, 1, stream) != 1)
  {
    ErrorRead(stream);
  }
}

static void ErrorAlloc(void)
{
  GIFError("Out of memory in GIF decoder");
}

static void ErrorRead(FILE *stream)
{
  if (ferror(stream))
  {
    GIFError("Error reading GIF file");
  }
  else
    GIFError("Unexpected end of GIF file");
}

static void DefaultError(const char *message)
{
  fprintf(stderr, "%s\n", message);
  exit(1);
}

static void DefaultWarning(const char *message)
{
  fprintf(stderr, "%s\n", message);
}

void (*GIFError)(const char *message) = DefaultError;
void (*GIFWarning)(const char *message) = DefaultWarning;
void helper_GIFReadImageData_1(unsigned int * const rows_idx_ref, unsigned int * const xpos_ref, unsigned int * const ypos_ref, int * const val_ref, unsigned char ** const rows, unsigned int width, unsigned int height, unsigned int interlaced, unsigned int numColors, int pass)
{
  unsigned int rows_idx = *rows_idx_ref;
  unsigned int xpos = *xpos_ref;
  unsigned int ypos = *ypos_ref;
  int val = *val_ref;
  if (((unsigned int) val) >= numColors)
  {
    GIFWarning("Pixel value out of range in GIF image");
    val = numColors - 1;
  }
  rows[ypos + rows_idx][xpos] = (unsigned char) val;
  if ((++xpos) == width)
  {
    helper_helper_GIFReadImageData_1_1(&xpos, &ypos, height, interlaced, pass);
  }
  if (ypos >= height)
  {
    break;
  }
  *rows_idx_ref = rows_idx;
  *xpos_ref = xpos;
  *ypos_ref = ypos;
  *val_ref = val;
}

int helper_LZWGetCode_1(static int * const curbit_ref, static int * const lastbit_ref, static int * const done_ref, static int * const last_byte_ref, int * const count_ref, FILE * const stream, static unsigned char buffer[280])
{
  static int curbit = *curbit_ref;
  static int lastbit = *lastbit_ref;
  static int done = *done_ref;
  static int last_byte = *last_byte_ref;
  int count = *count_ref;
  if (done)
  {
    if (curbit >= lastbit)
    {
      GIFError("Ran off the end of input bits in LZW decoding");
    }
    return -1;
  }
  buffer[0] = buffer[last_byte - 2];
  buffer[1] = buffer[last_byte - 1];
  if ((count = GIFReadDataBlock(&buffer[2], stream)) == 0)
  {
    done = 1;
  }
  last_byte = 2 + count;
  curbit = (curbit - lastbit) + 16;
  lastbit = (2 + count) * 8;
  *curbit_ref = curbit;
  *lastbit_ref = lastbit;
  *done_ref = done;
  *last_byte_ref = last_byte;
  *count_ref = count;
}

int helper_LZWDecodeByte_1(static int * const fresh_ref, static int * const code_size_ref, static int * const set_code_size_ref, static int * const max_code_ref, static int * const max_code_size_ref, static int * const clear_code_ref, static int * const end_code_ref, unsigned int * const sp_idx_ref, int * const i_ref, int input_code_size, FILE * const stream, static int table[2][((1 << 12) - 1) + 1], static int stack[(((1 << 12) - 1) + 1) * 2])
{
  static int fresh = *fresh_ref;
  static int code_size = *code_size_ref;
  static int set_code_size = *set_code_size_ref;
  static int max_code = *max_code_ref;
  static int max_code_size = *max_code_size_ref;
  static int clear_code = *clear_code_ref;
  static int end_code = *end_code_ref;
  unsigned int sp_idx = *sp_idx_ref;
  int i = *i_ref;
  fresh = 1;
  set_code_size = input_code_size;
  code_size = set_code_size + 1;
  clear_code = 1 << set_code_size;
  end_code = clear_code + 1;
  max_code_size = 2 * clear_code;
  max_code = clear_code + 2;
  LZWGetCode(0, 1, stream);
  for (i = 0; i < clear_code; i += 1)
  {
    table[0][i] = 0;
    table[1][i] = i;
  }

  for (; i <= ((1 << 12) - 1); i += 1)
  {
    table[0][i] = 0;
    table[1][i] = 0;
  }

  sp_idx = stack;
  return 0;
  *fresh_ref = fresh;
  *code_size_ref = code_size;
  *set_code_size_ref = set_code_size;
  *max_code_ref = max_code;
  *max_code_size_ref = max_code_size;
  *clear_code_ref = clear_code;
  *end_code_ref = end_code;
  *sp_idx_ref = sp_idx;
  *i_ref = i;
}

int helper_LZWDecodeByte_2(static int * const code_size_ref, static int * const max_code_ref, static int * const max_code_size_ref, static int * const firstcode_ref, static int * const oldcode_ref, unsigned int * const sp_idx_ref, int * const code_ref, int * const incode_ref, int * const i_ref, FILE * const stream, static int set_code_size, static int clear_code, static int end_code, static int table[2][((1 << 12) - 1) + 1], static int stack[(((1 << 12) - 1) + 1) * 2], static int * const sp)
{
  static int code_size = *code_size_ref;
  static int max_code = *max_code_ref;
  static int max_code_size = *max_code_size_ref;
  static int firstcode = *firstcode_ref;
  static int oldcode = *oldcode_ref;
  unsigned int sp_idx = *sp_idx_ref;
  int code = *code_ref;
  int incode = *incode_ref;
  int i = *i_ref;
  if (code == clear_code)
  {
    helper_helper_LZWDecodeByte_2_1(&code_size, &max_code, &max_code_size, &firstcode, &sp_idx, &i, stream, set_code_size, clear_code, table, stack, oldcode);
  }
  else
    if (code == end_code)
  {
    int count;
    unsigned char buffer[260];
    if (DataBlockSize == 0)
    {
      return -2;
    }
    while ((count = GIFReadDataBlock(buffer, stream)) > 0)
    {
    }

    (void) count;
    return -2;
  }
  incode = code;
  if (code >= max_code)
  {
    sp[sp_idx] = firstcode;
    sp_idx += 1;
    code = oldcode;
  }
  while (code >= clear_code)
  {
    sp[sp_idx] = table[1][code];
    sp_idx += 1;
    if ((code == table[0][code]) || (((size_t) ((&sp[sp_idx]) - stack)) >= ((sizeof(stack)) / (sizeof(stack[0])))))
    {
      GIFError("Circular dependency found in LZW table");
    }
    code = table[0][code];
  }

  sp[sp_idx] = (firstcode = table[1][code]);
  sp_idx += 1;
  if ((code = max_code) <= ((1 << 12) - 1))
  {
    table[0][code] = oldcode;
    table[1][code] = firstcode;
    max_code += 1;
    if ((max_code >= max_code_size) && (max_code_size <= ((1 << 12) - 1)))
    {
      max_code_size *= 2;
      code_size += 1;
    }
  }
  oldcode = incode;
  if ((&sp[sp_idx]) > stack)
  {
    sp_idx -= 1;
    return sp[sp_idx];
  }
  *code_size_ref = code_size;
  *max_code_ref = max_code;
  *max_code_size_ref = max_code_size;
  *firstcode_ref = firstcode;
  *oldcode_ref = oldcode;
  *sp_idx_ref = sp_idx;
  *code_ref = code;
  *incode_ref = incode;
  *i_ref = i;
}

void helper_helper_GIFReadImageData_1_1(unsigned int * const xpos_ref, unsigned int * const ypos_ref, unsigned int height, unsigned int interlaced, int pass)
{
  unsigned int xpos = *xpos_ref;
  unsigned int ypos = *ypos_ref;
  xpos = 0;
  ypos += 1;
  if (interlaced)
  {
    switch (pass)
    {
      case 0:

      case 1:
      {
        ypos += 8;
        break;
      }

      case 2:
      {
        ypos += 4;
        break;
      }

      case 3:
      {
        ypos += 2;
        break;
      }

    }

    if (ypos >= height)
    {
      switch (++pass)
      {
        case 1:
        {
          ypos = 4;
          break;
        }

        case 2:
        {
          ypos = 2;
          break;
        }

        case 3:
        {
          ypos = 1;
          break;
        }

        default:
        {
          goto fini;
        }

      }

    }
  }
  else
    ++ypos;
  *xpos_ref = xpos;
  *ypos_ref = ypos;
}

int helper_helper_LZWDecodeByte_2_1(static int * const code_size_ref, static int * const max_code_ref, static int * const max_code_size_ref, static int * const firstcode_ref, unsigned int * const sp_idx_ref, int * const i_ref, FILE * const stream, static int set_code_size, static int clear_code, static int table[2][((1 << 12) - 1) + 1], static int stack[(((1 << 12) - 1) + 1) * 2], static int oldcode)
{
  static int code_size = *code_size_ref;
  static int max_code = *max_code_ref;
  static int max_code_size = *max_code_size_ref;
  static int firstcode = *firstcode_ref;
  unsigned int sp_idx = *sp_idx_ref;
  int i = *i_ref;
  for (i = 0; i < clear_code; i += 1)
  {
    table[0][i] = 0;
    table[1][i] = i;
  }

  for (; i <= ((1 << 12) - 1); i += 1)
  {
    table[0][i] = 0;
    table[1][i] = 0;
  }

  code_size = set_code_size + 1;
  max_code_size = 2 * clear_code;
  max_code = clear_code + 2;
  sp_idx = stack;
  firstcode = (oldcode = LZWGetCode(code_size, 0, stream));
  return firstcode;
  *code_size_ref = code_size;
  *max_code_ref = max_code;
  *max_code_size_ref = max_code_size;
  *firstcode_ref = firstcode;
  *sp_idx_ref = sp_idx;
  *i_ref = i;
}

