typedef struct LodePNGEncoderSettings
{
  LodePNGCompressSettings zlibsettings;
  unsigned auto_convert;
  unsigned filter_palette_zero;
  LodePNGFilterStrategy filter_strategy;
  const unsigned char *predefined_filters;
  unsigned force_palette;
  unsigned add_id;
  unsigned text_compression;
} LodePNGEncoderSettings
/*** DEPENDENCIES:
struct LodePNGCompressSettings
{
  unsigned btype;
  unsigned use_lz77;
  unsigned windowsize;
  unsigned minmatch;
  unsigned nicematch;
  unsigned lazymatching;
  unsigned (*custom_zlib)(unsigned char **, size_t *, const unsigned char *, size_t, const LodePNGCompressSettings *);
  unsigned (*custom_deflate)(unsigned char **, size_t *, const unsigned char *, size_t, const LodePNGCompressSettings *);
  const void *custom_context;
}
----------------------------
typedef enum LodePNGFilterStrategy
{
  LFS_ZERO = 0,
  LFS_ONE = 1,
  LFS_TWO = 2,
  LFS_THREE = 3,
  LFS_FOUR = 4,
  LFS_MINSUM,
  LFS_ENTROPY,
  LFS_BRUTE_FORCE,
  LFS_PREDEFINED
} LodePNGFilterStrategy
----------------------------
***/


