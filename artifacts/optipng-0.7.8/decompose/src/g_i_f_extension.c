struct GIFExtension
{
  struct GIFScreen *Screen;
  unsigned char *Buffer;
  unsigned int BufferSize;
  unsigned char Label;
}
/*** DEPENDENCIES:
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
***/


