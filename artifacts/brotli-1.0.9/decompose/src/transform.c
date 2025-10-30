static int ToUpperCase(uint8_t *p)
{
  if (p[0] < 0xC0)
  {
    if ((p[0] >= 'a') && (p[0] <= 'z'))
    {
      p[0] ^= 32;
    }
    return 1;
  }
  if (p[0] < 0xE0)
  {
    p[1] ^= 32;
    return 2;
  }
  p[2] ^= 5;
  return 3;
}


/*** DEPENDENCIES:
***/


static int Shift(uint8_t *word, int word_len, uint16_t parameter)
{
  uint32_t scalar = (parameter & 0x7FFFu) + (0x1000000u - (parameter & 0x8000u));
  if (word[0] < 0x80)
  {
    scalar += (uint32_t) word[0];
    word[0] = (uint8_t) (scalar & 0x7Fu);
    return 1;
  }
  else
    if (word[0] < 0xC0)
  {
    return 1;
  }
  else
    if (word[0] < 0xE0)
  {
    if (word_len < 2)
    {
      return 1;
    }
    scalar += (uint32_t) ((word[1] & 0x3Fu) | ((word[0] & 0x1Fu) << 6u));
    word[0] = (uint8_t) (0xC0 | ((scalar >> 6u) & 0x1F));
    word[1] = (uint8_t) ((word[1] & 0xC0) | (scalar & 0x3F));
    return 2;
  }
  else
    if (word[0] < 0xF0)
  {
    if (word_len < 3)
    {
      return word_len;
    }
    scalar += (uint32_t) (((word[2] & 0x3Fu) | ((word[1] & 0x3Fu) << 6u)) | ((word[0] & 0x0Fu) << 12u));
    word[0] = (uint8_t) (0xE0 | ((scalar >> 12u) & 0x0F));
    word[1] = (uint8_t) ((word[1] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[2] = (uint8_t) ((word[2] & 0xC0) | (scalar & 0x3F));
    return 3;
  }
  else
    if (word[0] < 0xF8)
  {
    if (word_len < 4)
    {
      return word_len;
    }
    scalar += (uint32_t) ((((word[3] & 0x3Fu) | ((word[2] & 0x3Fu) << 6u)) | ((word[1] & 0x3Fu) << 12u)) | ((word[0] & 0x07u) << 18u));
    word[0] = (uint8_t) (0xF0 | ((scalar >> 18u) & 0x07));
    word[1] = (uint8_t) ((word[1] & 0xC0) | ((scalar >> 12u) & 0x3F));
    word[2] = (uint8_t) ((word[2] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[3] = (uint8_t) ((word[3] & 0xC0) | (scalar & 0x3F));
    return 4;
  }
  return 1;
}


/*** DEPENDENCIES:
***/


const BrotliTransforms *BrotliGetTransforms(void)
{
  return &kBrotliTransforms;
}


/*** DEPENDENCIES:
static const BrotliTransforms kBrotliTransforms = {sizeof(kPrefixSuffix), (const uint8_t *) kPrefixSuffix, kPrefixSuffixMap, (sizeof(kTransformsData)) / (3 * (sizeof(kTransformsData[0]))), kTransformsData, 0, {0, 12, 27, 23, 42, 63, 56, 48, 59, 64}}
----------------------------
***/


// hint:  ['len_ref is a mutable refrence to int', 'word_idx_ref is a mutable refrence to unsigned int', 'idx_ref is a mutable refrence to int']
void helper_BrotliTransformDictionaryWord_1(int * const len_ref, unsigned int * const word_idx_ref, int * const idx_ref, uint8_t * const dst, const uint8_t * const word, const BrotliTransforms * const transforms, int transform_idx, uint8_t type)
{
  int len = *len_ref;
  unsigned int word_idx = *word_idx_ref;
  int idx = *idx_ref;
  const int t = type;
  int i = 0;
  if (t <= BROTLI_TRANSFORM_OMIT_LAST_9)
  {
    len -= t;
  }
  else
    if ((t >= BROTLI_TRANSFORM_OMIT_FIRST_1) && (t <= BROTLI_TRANSFORM_OMIT_FIRST_9))
  {
    int skip = t - (BROTLI_TRANSFORM_OMIT_FIRST_1 - 1);
    word_idx += skip;
    len -= skip;
  }
  while (i < len)
  {
    dst[idx] = word[i + word_idx];
    i += 1;
    idx += 1;
  }

  if (t == BROTLI_TRANSFORM_UPPERCASE_FIRST)
  {
    ToUpperCase(&dst[idx - len]);
  }
  else
    if (t == BROTLI_TRANSFORM_UPPERCASE_ALL)
  {
    uint8_t *uppercase = &dst[idx - len];
    unsigned int uppercase_idx = 0;
    while (len > 0)
    {
      int step = ToUpperCase(uppercase);
      uppercase_idx += step;
      len -= step;
    }

  }
  else
    if (t == BROTLI_TRANSFORM_SHIFT_FIRST)
  {
    uint16_t param = (uint16_t) (transforms->params[transform_idx * 2] + (transforms->params[(transform_idx * 2) + 1] << 8u));
    Shift(&dst[idx - len], len, param);
  }
  else
    if (t == BROTLI_TRANSFORM_SHIFT_ALL)
  {
    uint16_t param = (uint16_t) (transforms->params[transform_idx * 2] + (transforms->params[(transform_idx * 2) + 1] << 8u));
    uint8_t *shift = &dst[idx - len];
    unsigned int shift_idx = 0;
    while (len > 0)
    {
      int step = Shift(shift, len, param);
      shift_idx += step;
      len -= step;
    }

  }
  *len_ref = len;
  *word_idx_ref = word_idx;
  *idx_ref = idx;
}


/*** DEPENDENCIES:
static int Shift(uint8_t *word, int word_len, uint16_t parameter)
{
  uint32_t scalar = (parameter & 0x7FFFu) + (0x1000000u - (parameter & 0x8000u));
  if (word[0] < 0x80)
  {
    scalar += (uint32_t) word[0];
    word[0] = (uint8_t) (scalar & 0x7Fu);
    return 1;
  }
  else
    if (word[0] < 0xC0)
  {
    return 1;
  }
  else
    if (word[0] < 0xE0)
  {
    if (word_len < 2)
    {
      return 1;
    }
    scalar += (uint32_t) ((word[1] & 0x3Fu) | ((word[0] & 0x1Fu) << 6u));
    word[0] = (uint8_t) (0xC0 | ((scalar >> 6u) & 0x1F));
    word[1] = (uint8_t) ((word[1] & 0xC0) | (scalar & 0x3F));
    return 2;
  }
  else
    if (word[0] < 0xF0)
  {
    if (word_len < 3)
    {
      return word_len;
    }
    scalar += (uint32_t) (((word[2] & 0x3Fu) | ((word[1] & 0x3Fu) << 6u)) | ((word[0] & 0x0Fu) << 12u));
    word[0] = (uint8_t) (0xE0 | ((scalar >> 12u) & 0x0F));
    word[1] = (uint8_t) ((word[1] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[2] = (uint8_t) ((word[2] & 0xC0) | (scalar & 0x3F));
    return 3;
  }
  else
    if (word[0] < 0xF8)
  {
    if (word_len < 4)
    {
      return word_len;
    }
    scalar += (uint32_t) ((((word[3] & 0x3Fu) | ((word[2] & 0x3Fu) << 6u)) | ((word[1] & 0x3Fu) << 12u)) | ((word[0] & 0x07u) << 18u));
    word[0] = (uint8_t) (0xF0 | ((scalar >> 18u) & 0x07));
    word[1] = (uint8_t) ((word[1] & 0xC0) | ((scalar >> 12u) & 0x3F));
    word[2] = (uint8_t) ((word[2] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[3] = (uint8_t) ((word[3] & 0xC0) | (scalar & 0x3F));
    return 4;
  }
  return 1;
}


----------------------------
typedef struct BrotliTransforms
{
  uint16_t prefix_suffix_size;
  const uint8_t *prefix_suffix;
  const uint16_t *prefix_suffix_map;
  uint32_t num_transforms;
  const uint8_t *transforms;
  const uint8_t *params;
  int16_t cutOffTransforms[BROTLI_TRANSFORM_OMIT_LAST_9 + 1];
} BrotliTransforms
----------------------------
static int ToUpperCase(uint8_t *p)
{
  if (p[0] < 0xC0)
  {
    if ((p[0] >= 'a') && (p[0] <= 'z'))
    {
      p[0] ^= 32;
    }
    return 1;
  }
  if (p[0] < 0xE0)
  {
    p[1] ^= 32;
    return 2;
  }
  p[2] ^= 5;
  return 3;
}


----------------------------
***/


int BrotliTransformDictionaryWord(uint8_t *dst, const uint8_t *word, int len, const BrotliTransforms *transforms, int transform_idx)
{
  unsigned int word_idx = 0;
  int idx = 0;
  const uint8_t *prefix = &transforms->prefix_suffix[transforms->prefix_suffix_map[transforms->transforms[(transform_idx * 3) + 0]]];
  unsigned int prefix_idx = 0;
  uint8_t type = transforms->transforms[(transform_idx * 3) + 1];
  const uint8_t *suffix = &transforms->prefix_suffix[transforms->prefix_suffix_map[transforms->transforms[(transform_idx * 3) + 2]]];
  unsigned int suffix_idx = 0;
  {
    int prefix_len = prefix[prefix_idx];
    prefix_idx += 1;
    while (prefix_len--)
    {
      dst[idx++] = *((&prefix[prefix_idx])++);
    }

  }
  {
    helper_BrotliTransformDictionaryWord_1(&len, &word_idx, &idx, dst, word, transforms, transform_idx, type);
  }
  {
    int suffix_len = suffix[suffix_idx];
    suffix_idx += 1;
    while (suffix_len--)
    {
      dst[idx] = suffix[suffix_idx];
      suffix_idx += 1;
      idx += 1;
    }

    return idx;
  }
}


/*** DEPENDENCIES:
void helper_BrotliTransformDictionaryWord_1(int * const len_ref, unsigned int * const word_idx_ref, int * const idx_ref, uint8_t * const dst, const uint8_t * const word, const BrotliTransforms * const transforms, int transform_idx, uint8_t type)
{
  int len = *len_ref;
  unsigned int word_idx = *word_idx_ref;
  int idx = *idx_ref;
  const int t = type;
  int i = 0;
  if (t <= BROTLI_TRANSFORM_OMIT_LAST_9)
  {
    len -= t;
  }
  else
    if ((t >= BROTLI_TRANSFORM_OMIT_FIRST_1) && (t <= BROTLI_TRANSFORM_OMIT_FIRST_9))
  {
    int skip = t - (BROTLI_TRANSFORM_OMIT_FIRST_1 - 1);
    word_idx += skip;
    len -= skip;
  }
  while (i < len)
  {
    dst[idx] = word[i + word_idx];
    i += 1;
    idx += 1;
  }

  if (t == BROTLI_TRANSFORM_UPPERCASE_FIRST)
  {
    ToUpperCase(&dst[idx - len]);
  }
  else
    if (t == BROTLI_TRANSFORM_UPPERCASE_ALL)
  {
    uint8_t *uppercase = &dst[idx - len];
    unsigned int uppercase_idx = 0;
    while (len > 0)
    {
      int step = ToUpperCase(uppercase);
      uppercase_idx += step;
      len -= step;
    }

  }
  else
    if (t == BROTLI_TRANSFORM_SHIFT_FIRST)
  {
    uint16_t param = (uint16_t) (transforms->params[transform_idx * 2] + (transforms->params[(transform_idx * 2) + 1] << 8u));
    Shift(&dst[idx - len], len, param);
  }
  else
    if (t == BROTLI_TRANSFORM_SHIFT_ALL)
  {
    uint16_t param = (uint16_t) (transforms->params[transform_idx * 2] + (transforms->params[(transform_idx * 2) + 1] << 8u));
    uint8_t *shift = &dst[idx - len];
    unsigned int shift_idx = 0;
    while (len > 0)
    {
      int step = Shift(shift, len, param);
      shift_idx += step;
      len -= step;
    }

  }
  *len_ref = len;
  *word_idx_ref = word_idx;
  *idx_ref = idx;
}


----------------------------
typedef struct BrotliTransforms
{
  uint16_t prefix_suffix_size;
  const uint8_t *prefix_suffix;
  const uint16_t *prefix_suffix_map;
  uint32_t num_transforms;
  const uint8_t *transforms;
  const uint8_t *params;
  int16_t cutOffTransforms[BROTLI_TRANSFORM_OMIT_LAST_9 + 1];
} BrotliTransforms
----------------------------
***/


