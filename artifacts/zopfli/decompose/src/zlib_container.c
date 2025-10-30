static unsigned adler32(const unsigned char *data, size_t size)
{
  unsigned int data_idx = 0;
  static const unsigned sums_overflow = 5550;
  unsigned s1 = 1;
  unsigned s2 = 1 >> 16;
  while (size > 0)
  {
    size_t amount = (size > sums_overflow) ? (sums_overflow) : (size);
    size -= amount;
    while (amount > 0)
    {
      s1 += data[data_idx];
      data_idx += 1;
      s2 += s1;
      amount--;
    }

    s1 %= 65521;
    s2 %= 65521;
  }

  return (s2 << 16) | s1;
}


/*** DEPENDENCIES:
***/


void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  unsigned char bitpointer = 0;
  unsigned checksum = adler32(in, (unsigned) insize);
  unsigned cmf = 120;
  unsigned flevel = 3;
  unsigned fdict = 0;
  unsigned cmfflg = ((256 * cmf) + (fdict * 32)) + (flevel * 64);
  unsigned fcheck = 31 - (cmfflg % 31);
  cmfflg += fcheck;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = cmfflg / 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = cmfflg % 256;
    *outsize += 1;
  }
  ;
  ZopfliDeflate(options, 2, 1, in, insize, &bitpointer, out, outsize);
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 24) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = checksum % 256;
    *outsize += 1;
  }
  ;
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %d, Zlib: %d, Compression: %f%% Removed\n", (int) insize, (int) (*outsize), (100.0 * ((double) (insize - (*outsize)))) / ((double) insize));
  }
}


/*** DEPENDENCIES:
static unsigned adler32(const unsigned char *data, size_t size)
{
  unsigned int data_idx = 0;
  static const unsigned sums_overflow = 5550;
  unsigned s1 = 1;
  unsigned s2 = 1 >> 16;
  while (size > 0)
  {
    size_t amount = (size > sums_overflow) ? (sums_overflow) : (size);
    size -= amount;
    while (amount > 0)
    {
      s1 += data[data_idx];
      data_idx += 1;
      s2 += s1;
      amount--;
    }

    s1 %= 65521;
    s2 %= 65521;
  }

  return (s2 << 16) | s1;
}


----------------------------
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t offset = *outsize;
  size_t i = 0;
  do
  {
    int masterfinal = (i + 1000000) >= insize;
    int final2 = final && masterfinal;
    size_t size = (masterfinal) ? (insize - i) : (1000000);
    ZopfliDeflatePart(options, btype, final2, in, i, i + size, bp, out, outsize);
    i += size;
  }
  while (i < insize);
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %lu, Deflate: %lu, Compression: %f%% Removed\n", (unsigned long) insize, (unsigned long) ((*outsize) - offset), (100.0 * ((double) (insize - ((*outsize) - offset)))) / ((double) insize));
  }
}


----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
***/


