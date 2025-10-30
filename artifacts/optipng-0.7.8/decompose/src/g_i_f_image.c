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


