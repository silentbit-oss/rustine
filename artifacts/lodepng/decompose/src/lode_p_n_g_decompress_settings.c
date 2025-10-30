struct LodePNGDecompressSettings
{
  unsigned ignore_adler32;
  unsigned ignore_nlen;
  size_t max_output_size;
  unsigned (*custom_zlib)(unsigned char **, size_t *, const unsigned char *, size_t, const LodePNGDecompressSettings *);
  unsigned (*custom_inflate)(unsigned char **, size_t *, const unsigned char *, size_t, const LodePNGDecompressSettings *);
  const void *custom_context;
}
/*** DEPENDENCIES:
***/


