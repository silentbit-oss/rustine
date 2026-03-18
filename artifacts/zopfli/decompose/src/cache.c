void ZopfliInitCache(size_t blocksize, ZopfliLongestMatchCache *lmc)
{
  size_t i;
  lmc->length = (unsigned short *) malloc((sizeof(unsigned short)) * blocksize);
  lmc->dist = (unsigned short *) malloc((sizeof(unsigned short)) * blocksize);
  lmc->sublen = (unsigned char *) malloc((8 * 3) * blocksize);
  if (lmc->sublen == 0)
  {
    fprintf(stderr, "Error: Out of memory. Tried allocating %lu bytes of memory.\n", (((unsigned long) 8) * 3) * blocksize);
    exit(1);
  }
  for (i = 0; i < blocksize; i += 1)
    lmc->length[i] = 1;

  for (i = 0; i < blocksize; i += 1)
    lmc->dist[i] = 0;

  for (i = 0; i < ((8 * blocksize) * 3); i += 1)
    lmc->sublen[i] = 0;

}


/*** DEPENDENCIES:
typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache
----------------------------
***/


void ZopfliCleanCache(ZopfliLongestMatchCache *lmc)
{
  free(lmc->length);
  free(lmc->dist);
  free(lmc->sublen);
}


/*** DEPENDENCIES:
typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache
----------------------------
***/


unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length)
{
  unsigned char *cache;
  unsigned int cache_idx = 0;
  cache_idx = &lmc->sublen[(8 * pos) * 3];
  (void) length;
  if ((cache[1 + cache_idx] == 0) && (cache[2 + cache_idx] == 0))
  {
    return 0;
  }
  return cache[((8 - 1) * 3) + cache_idx] + 3;
}


/*** DEPENDENCIES:
typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache
----------------------------
***/


void ZopfliSublenToCache(const unsigned short *sublen, size_t pos, size_t length, ZopfliLongestMatchCache *lmc)
{
  size_t i;
  size_t j = 0;
  unsigned bestlength = 0;
  unsigned char *cache;
  unsigned int cache_idx = 0;
  cache_idx = &lmc->sublen[(8 * pos) * 3];
  if (length < 3)
  {
    return;
  }
  for (i = 3; i <= length; i += 1)
  {
    if ((i == length) || (sublen[i] != sublen[i + 1]))
    {
      cache[(j * 3) + cache_idx] = i - 3;
      cache[((j * 3) + 1) + cache_idx] = sublen[i] % 256;
      cache[((j * 3) + 2) + cache_idx] = (sublen[i] >> 8) % 256;
      bestlength = i;
      j += 1;
      if (j >= 8)
      {
        break;
      }
    }
  }

  if (j < 8)
  {
    assert(bestlength == length);
    cache[((8 - 1) * 3) + cache_idx] = bestlength - 3;
  }
  else
  {
    assert(bestlength <= length);
  }
  assert(bestlength == ZopfliMaxCachedSublen(lmc, pos, length));
}


/*** DEPENDENCIES:
typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache
----------------------------
unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length)
{
  unsigned char *cache;
  unsigned int cache_idx = 0;
  cache_idx = &lmc->sublen[(8 * pos) * 3];
  (void) length;
  if ((cache[1 + cache_idx] == 0) && (cache[2 + cache_idx] == 0))
  {
    return 0;
  }
  return cache[((8 - 1) * 3) + cache_idx] + 3;
}


----------------------------
***/


void ZopfliCacheToSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length, unsigned short *sublen)
{
  size_t i;
  size_t j;
  unsigned maxlength = ZopfliMaxCachedSublen(lmc, pos, length);
  unsigned prevlength = 0;
  unsigned char *cache;
  unsigned int cache_idx = 0;
  if (length < 3)
  {
    return;
  }
  cache_idx = &lmc->sublen[(8 * pos) * 3];
  for (j = 0; j < 8; j += 1)
  {
    unsigned length = cache[(j * 3) + cache_idx] + 3;
    unsigned dist = cache[((j * 3) + 1) + cache_idx] + (256 * cache[((j * 3) + 2) + cache_idx]);
    for (i = prevlength; i <= length; i += 1)
    {
      sublen[i] = dist;
    }

    if (length == maxlength)
    {
      break;
    }
    prevlength = length + 1;
  }

}


/*** DEPENDENCIES:
typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache
----------------------------
unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length)
{
  unsigned char *cache;
  unsigned int cache_idx = 0;
  cache_idx = &lmc->sublen[(8 * pos) * 3];
  (void) length;
  if ((cache[1 + cache_idx] == 0) && (cache[2 + cache_idx] == 0))
  {
    return 0;
  }
  return cache[((8 - 1) * 3) + cache_idx] + 3;
}


----------------------------
***/


