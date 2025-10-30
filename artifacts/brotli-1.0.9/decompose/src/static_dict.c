inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


/*** DEPENDENCIES:
inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


void helper_helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2_1(uint32_t * const matches, const size_t l, const size_t n, const size_t id, const uint8_t * const s, unsigned int s_idx)
{
  AddMatch(id + n, l + 1, l, matches);
  if (s[1 + s_idx] == 'a')
  {
    if (s[2 + s_idx] == ' ')
    {
      AddMatch(id + (28 * n), l + 3, l, matches);
    }
    else
      if (s[2 + s_idx] == 's')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (46 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 't')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (60 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 'n')
    {
      if ((s[3 + s_idx] == 'd') && (s[4 + s_idx] == ' '))
      {
        AddMatch(id + (10 * n), l + 5, l, matches);
      }
    }
  }
  else
    if (s[1 + s_idx] == 'b')
  {
    if ((s[2 + s_idx] == 'y') && (s[3 + s_idx] == ' '))
    {
      AddMatch(id + (38 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'i')
  {
    if (s[2 + s_idx] == 'n')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (16 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 's')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (47 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'f')
  {
    if (s[2 + s_idx] == 'o')
    {
      if ((s[3 + s_idx] == 'r') && (s[4 + s_idx] == ' '))
      {
        AddMatch(id + (25 * n), l + 5, l, matches);
      }
    }
    else
      if (s[2 + s_idx] == 'r')
    {
      if (((s[3 + s_idx] == 'o') && (s[4 + s_idx] == 'm')) && (s[5 + s_idx] == ' '))
      {
        AddMatch(id + (37 * n), l + 6, l, matches);
      }
    }
  }
  else
    if (s[1 + s_idx] == 'o')
  {
    if (s[2 + s_idx] == 'f')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (8 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 'n')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (45 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'n')
  {
    if (((s[2 + s_idx] == 'o') && (s[3 + s_idx] == 't')) && (s[4 + s_idx] == ' '))
    {
      AddMatch(id + (80 * n), l + 5, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 't')
  {
    if (s[2 + s_idx] == 'h')
    {
      if (s[3 + s_idx] == 'e')
      {
        if (s[4 + s_idx] == ' ')
          AddMatch(id + (5 * n), l + 5, l, matches);
      }
      else
        if (s[3 + s_idx] == 'a')
      {
        if ((s[4 + s_idx] == 't') && (s[5 + s_idx] == ' '))
        {
          AddMatch(id + (29 * n), l + 6, l, matches);
        }
      }
    }
    else
      if (s[2 + s_idx] == 'o')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (17 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'w')
  {
    if ((((s[2 + s_idx] == 'i') && (s[3 + s_idx] == 't')) && (s[4 + s_idx] == 'h')) && (s[5 + s_idx] == ' '))
    {
      AddMatch(id + (35 * n), l + 6, l, matches);
    }
  }
}


/*** DEPENDENCIES:
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_BrotliFindAllStaticDictionaryMatches_2(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  if ((((((data[0] == ' ') && (data[1] == 't')) && (data[2] == 'h')) && (data[3] == 'e')) && (data[4] == ' ')) || (((((data[0] == '.') && (data[1] == 'c')) && (data[2] == 'o')) && (data[3] == 'm')) && (data[4] == '/')))
  {
    size_t offset = dictionary->buckets[Hash(&data[5])];
    int end = !offset;
    while (!end)
    {
      DictWord w = dictionary->dict_words[offset];
      offset += 1;
      const size_t l = w.len & 0x1F;
      const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
      const size_t id = w.idx;
      end = !(!(w.len & 0x80));
      w.len = (uint8_t) l;
      if ((w.transform == 0) && IsMatch(dictionary->words, w, &data[5], max_length - 5))
      {
        AddMatch(id + (((data[0] == ' ') ? (41) : (72)) * n), l + 5, l, matches);
        has_found_match = 1;
        if ((l + 5) < max_length)
        {
          const uint8_t *s = &data[l + 5];
          unsigned int s_idx = 0;
          if (data[0] == ' ')
          {
            if ((((((l + 8) < max_length) && (s[0 + s_idx] == ' ')) && (s[1 + s_idx] == 'o')) && (s[2 + s_idx] == 'f')) && (s[3 + s_idx] == ' '))
            {
              AddMatch(id + (62 * n), l + 9, l, matches);
              if ((((((l + 12) < max_length) && (s[4 + s_idx] == 't')) && (s[5 + s_idx] == 'h')) && (s[6 + s_idx] == 'e')) && (s[7 + s_idx] == ' '))
              {
                AddMatch(id + (73 * n), l + 13, l, matches);
              }
            }
          }
        }
      }
    }

  }
  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_2(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, DictWord w, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const int is_all_caps = (!(!(w.transform != BROTLI_TRANSFORM_UPPERCASE_FIRST))) ? (1) : (0);
  const uint8_t *s;
  unsigned int s_idx = 0;
  if (!IsMatch(dictionary->words, w, &data[1], max_length - 1))
  {
    continue;
  }
  AddMatch(id + (((is_all_caps) ? (85) : (30)) * n), l + 1, l, matches);
  has_found_match = 1;
  if ((l + 2) >= max_length)
  {
    continue;
  }
  s_idx = &data[l + 1];
  if (s[0 + s_idx] == ' ')
  {
    AddMatch(id + (((is_all_caps) ? (83) : (15)) * n), l + 2, l, matches);
  }
  else
    if (s[0 + s_idx] == ',')
  {
    if (!is_all_caps)
    {
      AddMatch(id + (109 * n), l + 2, l, matches);
    }
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (111) : (65)) * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '.')
  {
    AddMatch(id + (((is_all_caps) ? (115) : (96)) * n), l + 2, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (117) : (91)) * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '=')
  {
    if (s[1 + s_idx] == '"')
    {
      AddMatch(id + (((is_all_caps) ? (110) : (118)) * n), l + 3, l, matches);
    }
    else
      if (s[1 + s_idx] == '\'')
    {
      AddMatch(id + (((is_all_caps) ? (119) : (120)) * n), l + 3, l, matches);
    }
  }
  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_1(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, int is_space, DictWord w, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const uint8_t *s;
  unsigned int s_idx = 0;
  if (!IsMatch(dictionary->words, w, &data[1], max_length - 1))
  {
    continue;
  }
  AddMatch(id + (((is_space) ? (6) : (32)) * n), l + 1, l, matches);
  has_found_match = 1;
  if ((l + 2) >= max_length)
  {
    continue;
  }
  s_idx = &data[l + 1];
  if (s[0 + s_idx] == ' ')
  {
    AddMatch(id + (((is_space) ? (2) : (77)) * n), l + 2, l, matches);
  }
  else
    if (s[0 + s_idx] == '(')
  {
    AddMatch(id + (((is_space) ? (89) : (67)) * n), l + 2, l, matches);
  }
  else
    if (is_space)
  {
    if (s[0 + s_idx] == ',')
    {
      AddMatch(id + (103 * n), l + 2, l, matches);
      if (s[1 + s_idx] == ' ')
      {
        AddMatch(id + (33 * n), l + 3, l, matches);
      }
    }
    else
      if (s[0 + s_idx] == '.')
    {
      AddMatch(id + (71 * n), l + 2, l, matches);
      if (s[1 + s_idx] == ' ')
      {
        AddMatch(id + (52 * n), l + 3, l, matches);
      }
    }
    else
      if (s[0 + s_idx] == '=')
    {
      if (s[1 + s_idx] == '"')
      {
        AddMatch(id + (81 * n), l + 3, l, matches);
      }
      else
        if (s[1 + s_idx] == '\'')
      {
        AddMatch(id + (98 * n), l + 3, l, matches);
      }
    }
  }
  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int', 'offset_ref is a mutable refrence to size_t', 'end_ref is a mutable refrence to int']
void helper_helper_BrotliFindAllStaticDictionaryMatches_3_1(int * const has_found_match_ref, size_t * const offset_ref, int * const end_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, int is_space)
{
  int has_found_match = *has_found_match_ref;
  size_t offset = *offset_ref;
  int end = *end_ref;
  DictWord w = dictionary->dict_words[offset];
  offset += 1;
  const size_t l = w.len & 0x1F;
  const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
  const size_t id = w.idx;
  end = !(!(w.len & 0x80));
  w.len = (uint8_t) l;
  if (w.transform == 0)
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_1(&has_found_match, dictionary, data, max_length, matches, is_space, w, l, n, id);
  }
  else
    if (is_space)
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_2(&has_found_match, dictionary, data, max_length, matches, w, l, n, id);
  }
  *has_found_match_ref = has_found_match;
  *offset_ref = offset;
  *end_ref = end;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_2(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, DictWord w, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const int is_all_caps = (!(!(w.transform != BROTLI_TRANSFORM_UPPERCASE_FIRST))) ? (1) : (0);
  const uint8_t *s;
  unsigned int s_idx = 0;
  if (!IsMatch(dictionary->words, w, &data[1], max_length - 1))
  {
    continue;
  }
  AddMatch(id + (((is_all_caps) ? (85) : (30)) * n), l + 1, l, matches);
  has_found_match = 1;
  if ((l + 2) >= max_length)
  {
    continue;
  }
  s_idx = &data[l + 1];
  if (s[0 + s_idx] == ' ')
  {
    AddMatch(id + (((is_all_caps) ? (83) : (15)) * n), l + 2, l, matches);
  }
  else
    if (s[0 + s_idx] == ',')
  {
    if (!is_all_caps)
    {
      AddMatch(id + (109 * n), l + 2, l, matches);
    }
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (111) : (65)) * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '.')
  {
    AddMatch(id + (((is_all_caps) ? (115) : (96)) * n), l + 2, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (117) : (91)) * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '=')
  {
    if (s[1 + s_idx] == '"')
    {
      AddMatch(id + (((is_all_caps) ? (110) : (118)) * n), l + 3, l, matches);
    }
    else
      if (s[1 + s_idx] == '\'')
    {
      AddMatch(id + (((is_all_caps) ? (119) : (120)) * n), l + 3, l, matches);
    }
  }
  *has_found_match_ref = has_found_match;
}


----------------------------
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_1(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, int is_space, DictWord w, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const uint8_t *s;
  unsigned int s_idx = 0;
  if (!IsMatch(dictionary->words, w, &data[1], max_length - 1))
  {
    continue;
  }
  AddMatch(id + (((is_space) ? (6) : (32)) * n), l + 1, l, matches);
  has_found_match = 1;
  if ((l + 2) >= max_length)
  {
    continue;
  }
  s_idx = &data[l + 1];
  if (s[0 + s_idx] == ' ')
  {
    AddMatch(id + (((is_space) ? (2) : (77)) * n), l + 2, l, matches);
  }
  else
    if (s[0 + s_idx] == '(')
  {
    AddMatch(id + (((is_space) ? (89) : (67)) * n), l + 2, l, matches);
  }
  else
    if (is_space)
  {
    if (s[0 + s_idx] == ',')
    {
      AddMatch(id + (103 * n), l + 2, l, matches);
      if (s[1 + s_idx] == ' ')
      {
        AddMatch(id + (33 * n), l + 3, l, matches);
      }
    }
    else
      if (s[0 + s_idx] == '.')
    {
      AddMatch(id + (71 * n), l + 2, l, matches);
      if (s[1 + s_idx] == ' ')
      {
        AddMatch(id + (52 * n), l + 3, l, matches);
      }
    }
    else
      if (s[0 + s_idx] == '=')
    {
      if (s[1 + s_idx] == '"')
      {
        AddMatch(id + (81 * n), l + 3, l, matches);
      }
      else
        if (s[1 + s_idx] == '\'')
      {
        AddMatch(id + (98 * n), l + 3, l, matches);
      }
    }
  }
  *has_found_match_ref = has_found_match;
}


----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_BrotliFindAllStaticDictionaryMatches_3(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  int is_space = (!(!(data[0] == ' '))) ? (1) : (0);
  size_t offset = dictionary->buckets[Hash(&data[1])];
  int end = !offset;
  while (!end)
  {
    helper_helper_BrotliFindAllStaticDictionaryMatches_3_1(&has_found_match, &offset, &end, dictionary, data, max_length, matches, is_space);
  }

  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_helper_BrotliFindAllStaticDictionaryMatches_3_1(int * const has_found_match_ref, size_t * const offset_ref, int * const end_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, int is_space)
{
  int has_found_match = *has_found_match_ref;
  size_t offset = *offset_ref;
  int end = *end_ref;
  DictWord w = dictionary->dict_words[offset];
  offset += 1;
  const size_t l = w.len & 0x1F;
  const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
  const size_t id = w.idx;
  end = !(!(w.len & 0x80));
  w.len = (uint8_t) l;
  if (w.transform == 0)
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_1(&has_found_match, dictionary, data, max_length, matches, is_space, w, l, n, id);
  }
  else
    if (is_space)
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_3_1_2(&has_found_match, dictionary, data, max_length, matches, w, l, n, id);
  }
  *has_found_match_ref = has_found_match;
  *offset_ref = offset;
  *end_ref = end;
}


----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_BrotliFindAllStaticDictionaryMatches_1(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  if (((data[1] == ' ') && (((data[0] == 'e') || (data[0] == 's')) || (data[0] == ','))) || ((data[0] == 0xC2) && (data[1] == 0xA0)))
  {
    size_t offset = dictionary->buckets[Hash(&data[2])];
    int end = !offset;
    while (!end)
    {
      DictWord w = dictionary->dict_words[offset];
      offset += 1;
      const size_t l = w.len & 0x1F;
      const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
      const size_t id = w.idx;
      end = !(!(w.len & 0x80));
      w.len = (uint8_t) l;
      if ((w.transform == 0) && IsMatch(dictionary->words, w, &data[2], max_length - 2))
      {
        if (data[0] == 0xC2)
        {
          AddMatch(id + (102 * n), l + 2, l, matches);
          has_found_match = 1;
        }
        else
          if (((l + 2) < max_length) && (data[l + 2] == ' '))
        {
          size_t t = (data[0] == 'e') ? (18) : ((data[0] == 's') ? (7) : (13));
          AddMatch(id + (t * n), l + 3, l, matches);
          has_found_match = 1;
        }
      }
    }

  }
  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
***/


inline static size_t DictMatchLength(const BrotliDictionary *dictionary, const uint8_t *data, size_t id, size_t len, size_t maxlen)
{
  const size_t offset = dictionary->offsets_by_length[len] + (len * id);
  return FindMatchLengthWithLimit(&dictionary->data[offset], data, brotli_min_size_t(len, maxlen));
}


/*** DEPENDENCIES:
inline static size_t FindMatchLengthWithLimit(const uint8_t *s1, const uint8_t *s2, size_t limit)
{
  unsigned int s2_idx = 0;
  size_t matched = 0;
  size_t limit2 = (limit >> 3) + 1;
  while (__builtin_expect(!(!(--limit2)), 1))
  {
    if (__builtin_expect(BrotliUnalignedRead64(s2) == BrotliUnalignedRead64(s1 + matched), 0))
    {
      s2_idx += 8;
      matched += 8;
    }
    else
    {
      uint64_t x = BrotliUnalignedRead64(s2) ^ BrotliUnalignedRead64(s1 + matched);
      size_t matching_bits = (size_t) __builtin_ctzll(x);
      matched += matching_bits >> 3;
      return matched;
    }
  }

  limit = (limit & 7) + 1;
  while (--limit)
  {
    if (__builtin_expect(!(!(s1[matched] == (*(&s2[s2_idx])))), 1))
    {
      s2_idx += 1;
      matched += 1;
    }
    else
    {
      return matched;
    }
  }

  return matched;
}


----------------------------
typedef struct BrotliDictionary
{
  uint8_t size_bits_by_length[32];
  uint32_t offsets_by_length[32];
  size_t data_size;
  const uint8_t *data;
} BrotliDictionary
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t min_length, size_t max_length, uint32_t * const matches, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const size_t matchlen = DictMatchLength(dictionary->words, data, id, l, max_length);
  const uint8_t *s;
  unsigned int s_idx = 0;
  size_t minlen;
  size_t maxlen;
  size_t len;
  if (matchlen == l)
  {
    AddMatch(id, l, l, matches);
    has_found_match = 1;
  }
  if (matchlen >= (l - 1))
  {
    AddMatch(id + (12 * n), l - 1, l, matches);
    if ((((((l + 2) < max_length) && (data[l - 1] == 'i')) && (data[l] == 'n')) && (data[l + 1] == 'g')) && (data[l + 2] == ' '))
    {
      AddMatch(id + (49 * n), l + 3, l, matches);
    }
    has_found_match = 1;
  }
  minlen = min_length;
  if (l > 9)
    minlen = brotli_max_size_t(minlen, l - 9);
  maxlen = brotli_min_size_t(matchlen, l - 2);
  for (len = minlen; len <= maxlen; ++len)
  {
    size_t cut = l - len;
    size_t transform_id = (cut << 2) + ((size_t) ((dictionary->cutoffTransforms >> (cut * 6)) & 0x3F));
    AddMatch(id + (transform_id * n), len, l, matches);
    has_found_match = 1;
  }

  if ((matchlen < l) || ((l + 6) >= max_length))
  {
    continue;
  }
  s_idx = &data[l];
  if (s[0 + s_idx] == ' ')
  {
    helper_helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2_1(matches, l, n, id, s, s_idx);
  }
  else
    if (s[0 + s_idx] == '"')
  {
    AddMatch(id + (19 * n), l + 1, l, matches);
    if (s[1 + s_idx] == '>')
    {
      AddMatch(id + (21 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '.')
  {
    AddMatch(id + (20 * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (31 * n), l + 2, l, matches);
      if ((s[2 + s_idx] == 'T') && (s[3 + s_idx] == 'h'))
      {
        if (s[4 + s_idx] == 'e')
        {
          if (s[5 + s_idx] == ' ')
            AddMatch(id + (43 * n), l + 6, l, matches);
        }
        else
          if (s[4 + s_idx] == 'i')
        {
          if ((s[5 + s_idx] == 's') && (s[6 + s_idx] == ' '))
          {
            AddMatch(id + (75 * n), l + 7, l, matches);
          }
        }
      }
    }
  }
  else
    if (s[0 + s_idx] == ',')
  {
    AddMatch(id + (76 * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (14 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '\n')
  {
    AddMatch(id + (22 * n), l + 1, l, matches);
    if (s[1 + s_idx] == '\t')
    {
      AddMatch(id + (50 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == ']')
  {
    AddMatch(id + (24 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '\'')
  {
    AddMatch(id + (36 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == ':')
  {
    AddMatch(id + (51 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '(')
  {
    AddMatch(id + (57 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '=')
  {
    if (s[1 + s_idx] == '"')
    {
      AddMatch(id + (70 * n), l + 2, l, matches);
    }
    else
      if (s[1 + s_idx] == '\'')
    {
      AddMatch(id + (86 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'a')
  {
    if ((s[1 + s_idx] == 'l') && (s[2 + s_idx] == ' '))
    {
      AddMatch(id + (84 * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'e')
  {
    if (s[1 + s_idx] == 'd')
    {
      if (s[2 + s_idx] == ' ')
        AddMatch(id + (53 * n), l + 3, l, matches);
    }
    else
      if (s[1 + s_idx] == 'r')
    {
      if (s[2 + s_idx] == ' ')
        AddMatch(id + (82 * n), l + 3, l, matches);
    }
    else
      if (s[1 + s_idx] == 's')
    {
      if ((s[2 + s_idx] == 't') && (s[3 + s_idx] == ' '))
      {
        AddMatch(id + (95 * n), l + 4, l, matches);
      }
    }
  }
  else
    if (s[0 + s_idx] == 'f')
  {
    if (((s[1 + s_idx] == 'u') && (s[2 + s_idx] == 'l')) && (s[3 + s_idx] == ' '))
    {
      AddMatch(id + (90 * n), l + 4, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'i')
  {
    if (s[1 + s_idx] == 'v')
    {
      if ((s[2 + s_idx] == 'e') && (s[3 + s_idx] == ' '))
      {
        AddMatch(id + (92 * n), l + 4, l, matches);
      }
    }
    else
      if (s[1 + s_idx] == 'z')
    {
      if ((s[2 + s_idx] == 'e') && (s[3 + s_idx] == ' '))
      {
        AddMatch(id + (100 * n), l + 4, l, matches);
      }
    }
  }
  else
    if (s[0 + s_idx] == 'l')
  {
    if (s[1 + s_idx] == 'e')
    {
      if (((s[2 + s_idx] == 's') && (s[3 + s_idx] == 's')) && (s[4 + s_idx] == ' '))
      {
        AddMatch(id + (93 * n), l + 5, l, matches);
      }
    }
    else
      if (s[1 + s_idx] == 'y')
    {
      if (s[2 + s_idx] == ' ')
        AddMatch(id + (61 * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'o')
  {
    if (((s[1 + s_idx] == 'u') && (s[2 + s_idx] == 's')) && (s[3 + s_idx] == ' '))
    {
      AddMatch(id + (106 * n), l + 4, l, matches);
    }
  }
  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2_1(uint32_t * const matches, const size_t l, const size_t n, const size_t id, const uint8_t * const s, unsigned int s_idx)
{
  AddMatch(id + n, l + 1, l, matches);
  if (s[1 + s_idx] == 'a')
  {
    if (s[2 + s_idx] == ' ')
    {
      AddMatch(id + (28 * n), l + 3, l, matches);
    }
    else
      if (s[2 + s_idx] == 's')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (46 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 't')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (60 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 'n')
    {
      if ((s[3 + s_idx] == 'd') && (s[4 + s_idx] == ' '))
      {
        AddMatch(id + (10 * n), l + 5, l, matches);
      }
    }
  }
  else
    if (s[1 + s_idx] == 'b')
  {
    if ((s[2 + s_idx] == 'y') && (s[3 + s_idx] == ' '))
    {
      AddMatch(id + (38 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'i')
  {
    if (s[2 + s_idx] == 'n')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (16 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 's')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (47 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'f')
  {
    if (s[2 + s_idx] == 'o')
    {
      if ((s[3 + s_idx] == 'r') && (s[4 + s_idx] == ' '))
      {
        AddMatch(id + (25 * n), l + 5, l, matches);
      }
    }
    else
      if (s[2 + s_idx] == 'r')
    {
      if (((s[3 + s_idx] == 'o') && (s[4 + s_idx] == 'm')) && (s[5 + s_idx] == ' '))
      {
        AddMatch(id + (37 * n), l + 6, l, matches);
      }
    }
  }
  else
    if (s[1 + s_idx] == 'o')
  {
    if (s[2 + s_idx] == 'f')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (8 * n), l + 4, l, matches);
    }
    else
      if (s[2 + s_idx] == 'n')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (45 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'n')
  {
    if (((s[2 + s_idx] == 'o') && (s[3 + s_idx] == 't')) && (s[4 + s_idx] == ' '))
    {
      AddMatch(id + (80 * n), l + 5, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 't')
  {
    if (s[2 + s_idx] == 'h')
    {
      if (s[3 + s_idx] == 'e')
      {
        if (s[4 + s_idx] == ' ')
          AddMatch(id + (5 * n), l + 5, l, matches);
      }
      else
        if (s[3 + s_idx] == 'a')
      {
        if ((s[4 + s_idx] == 't') && (s[5 + s_idx] == ' '))
        {
          AddMatch(id + (29 * n), l + 6, l, matches);
        }
      }
    }
    else
      if (s[2 + s_idx] == 'o')
    {
      if (s[3 + s_idx] == ' ')
        AddMatch(id + (17 * n), l + 4, l, matches);
    }
  }
  else
    if (s[1 + s_idx] == 'w')
  {
    if ((((s[2 + s_idx] == 'i') && (s[3 + s_idx] == 't')) && (s[4 + s_idx] == 'h')) && (s[5 + s_idx] == ' '))
    {
      AddMatch(id + (35 * n), l + 6, l, matches);
    }
  }
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t DictMatchLength(const BrotliDictionary *dictionary, const uint8_t *data, size_t id, size_t len, size_t maxlen)
{
  const size_t offset = dictionary->offsets_by_length[len] + (len * id);
  return FindMatchLengthWithLimit(&dictionary->data[offset], data, brotli_min_size_t(len, maxlen));
}


----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_1(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, DictWord w, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const int is_all_caps = (!(!(w.transform != BROTLI_TRANSFORM_UPPERCASE_FIRST))) ? (1) : (0);
  const uint8_t *s;
  unsigned int s_idx = 0;
  if (!IsMatch(dictionary->words, w, data, max_length))
  {
    continue;
  }
  AddMatch(id + (((is_all_caps) ? (44) : (9)) * n), l, l, matches);
  has_found_match = 1;
  if ((l + 1) >= max_length)
  {
    continue;
  }
  s_idx = &data[l];
  if (s[0 + s_idx] == ' ')
  {
    AddMatch(id + (((is_all_caps) ? (68) : (4)) * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '"')
  {
    AddMatch(id + (((is_all_caps) ? (87) : (66)) * n), l + 1, l, matches);
    if (s[1 + s_idx] == '>')
    {
      AddMatch(id + (((is_all_caps) ? (97) : (69)) * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '.')
  {
    AddMatch(id + (((is_all_caps) ? (101) : (79)) * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (114) : (88)) * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == ',')
  {
    AddMatch(id + (((is_all_caps) ? (112) : (99)) * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (107) : (58)) * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '\'')
  {
    AddMatch(id + (((is_all_caps) ? (94) : (74)) * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '(')
  {
    AddMatch(id + (((is_all_caps) ? (113) : (78)) * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '=')
  {
    if (s[1 + s_idx] == '"')
    {
      AddMatch(id + (((is_all_caps) ? (105) : (104)) * n), l + 2, l, matches);
    }
    else
      if (s[1 + s_idx] == '\'')
    {
      AddMatch(id + (((is_all_caps) ? (116) : (108)) * n), l + 2, l, matches);
    }
  }
  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static int IsMatch(const uint8_t *p1, const uint8_t *p2)
{
  return (!(!((BrotliUnalignedRead32(p1) == BrotliUnalignedRead32(p2)) && (p1[4] == p2[4])))) ? (1) : (0);
}


----------------------------
inline static void AddMatch(size_t distance, size_t len, size_t len_code, uint32_t *matches)
{
  uint32_t match = (uint32_t) ((distance << 5) + len_code);
  matches[len] = brotli_min_uint32_t(matches[len], match);
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int', 'offset_ref is a mutable refrence to size_t', 'end_ref is a mutable refrence to int']
void helper_helper_BrotliFindAllStaticDictionaryMatches_4_1(int * const has_found_match_ref, size_t * const offset_ref, int * const end_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t min_length, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  size_t offset = *offset_ref;
  int end = *end_ref;
  DictWord w = dictionary->dict_words[offset];
  offset += 1;
  const size_t l = w.len & 0x1F;
  const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
  const size_t id = w.idx;
  end = !(!(w.len & 0x80));
  w.len = (uint8_t) l;
  if (w.transform == 0)
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2(&has_found_match, dictionary, data, min_length, max_length, matches, l, n, id);
  }
  else
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_1(&has_found_match, dictionary, data, max_length, matches, w, l, n, id);
  }
  *has_found_match_ref = has_found_match;
  *offset_ref = offset;
  *end_ref = end;
}


/*** DEPENDENCIES:
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t min_length, size_t max_length, uint32_t * const matches, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const size_t matchlen = DictMatchLength(dictionary->words, data, id, l, max_length);
  const uint8_t *s;
  unsigned int s_idx = 0;
  size_t minlen;
  size_t maxlen;
  size_t len;
  if (matchlen == l)
  {
    AddMatch(id, l, l, matches);
    has_found_match = 1;
  }
  if (matchlen >= (l - 1))
  {
    AddMatch(id + (12 * n), l - 1, l, matches);
    if ((((((l + 2) < max_length) && (data[l - 1] == 'i')) && (data[l] == 'n')) && (data[l + 1] == 'g')) && (data[l + 2] == ' '))
    {
      AddMatch(id + (49 * n), l + 3, l, matches);
    }
    has_found_match = 1;
  }
  minlen = min_length;
  if (l > 9)
    minlen = brotli_max_size_t(minlen, l - 9);
  maxlen = brotli_min_size_t(matchlen, l - 2);
  for (len = minlen; len <= maxlen; ++len)
  {
    size_t cut = l - len;
    size_t transform_id = (cut << 2) + ((size_t) ((dictionary->cutoffTransforms >> (cut * 6)) & 0x3F));
    AddMatch(id + (transform_id * n), len, l, matches);
    has_found_match = 1;
  }

  if ((matchlen < l) || ((l + 6) >= max_length))
  {
    continue;
  }
  s_idx = &data[l];
  if (s[0 + s_idx] == ' ')
  {
    helper_helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2_1(matches, l, n, id, s, s_idx);
  }
  else
    if (s[0 + s_idx] == '"')
  {
    AddMatch(id + (19 * n), l + 1, l, matches);
    if (s[1 + s_idx] == '>')
    {
      AddMatch(id + (21 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '.')
  {
    AddMatch(id + (20 * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (31 * n), l + 2, l, matches);
      if ((s[2 + s_idx] == 'T') && (s[3 + s_idx] == 'h'))
      {
        if (s[4 + s_idx] == 'e')
        {
          if (s[5 + s_idx] == ' ')
            AddMatch(id + (43 * n), l + 6, l, matches);
        }
        else
          if (s[4 + s_idx] == 'i')
        {
          if ((s[5 + s_idx] == 's') && (s[6 + s_idx] == ' '))
          {
            AddMatch(id + (75 * n), l + 7, l, matches);
          }
        }
      }
    }
  }
  else
    if (s[0 + s_idx] == ',')
  {
    AddMatch(id + (76 * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (14 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '\n')
  {
    AddMatch(id + (22 * n), l + 1, l, matches);
    if (s[1 + s_idx] == '\t')
    {
      AddMatch(id + (50 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == ']')
  {
    AddMatch(id + (24 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '\'')
  {
    AddMatch(id + (36 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == ':')
  {
    AddMatch(id + (51 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '(')
  {
    AddMatch(id + (57 * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '=')
  {
    if (s[1 + s_idx] == '"')
    {
      AddMatch(id + (70 * n), l + 2, l, matches);
    }
    else
      if (s[1 + s_idx] == '\'')
    {
      AddMatch(id + (86 * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'a')
  {
    if ((s[1 + s_idx] == 'l') && (s[2 + s_idx] == ' '))
    {
      AddMatch(id + (84 * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'e')
  {
    if (s[1 + s_idx] == 'd')
    {
      if (s[2 + s_idx] == ' ')
        AddMatch(id + (53 * n), l + 3, l, matches);
    }
    else
      if (s[1 + s_idx] == 'r')
    {
      if (s[2 + s_idx] == ' ')
        AddMatch(id + (82 * n), l + 3, l, matches);
    }
    else
      if (s[1 + s_idx] == 's')
    {
      if ((s[2 + s_idx] == 't') && (s[3 + s_idx] == ' '))
      {
        AddMatch(id + (95 * n), l + 4, l, matches);
      }
    }
  }
  else
    if (s[0 + s_idx] == 'f')
  {
    if (((s[1 + s_idx] == 'u') && (s[2 + s_idx] == 'l')) && (s[3 + s_idx] == ' '))
    {
      AddMatch(id + (90 * n), l + 4, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'i')
  {
    if (s[1 + s_idx] == 'v')
    {
      if ((s[2 + s_idx] == 'e') && (s[3 + s_idx] == ' '))
      {
        AddMatch(id + (92 * n), l + 4, l, matches);
      }
    }
    else
      if (s[1 + s_idx] == 'z')
    {
      if ((s[2 + s_idx] == 'e') && (s[3 + s_idx] == ' '))
      {
        AddMatch(id + (100 * n), l + 4, l, matches);
      }
    }
  }
  else
    if (s[0 + s_idx] == 'l')
  {
    if (s[1 + s_idx] == 'e')
    {
      if (((s[2 + s_idx] == 's') && (s[3 + s_idx] == 's')) && (s[4 + s_idx] == ' '))
      {
        AddMatch(id + (93 * n), l + 5, l, matches);
      }
    }
    else
      if (s[1 + s_idx] == 'y')
    {
      if (s[2 + s_idx] == ' ')
        AddMatch(id + (61 * n), l + 3, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == 'o')
  {
    if (((s[1 + s_idx] == 'u') && (s[2 + s_idx] == 's')) && (s[3 + s_idx] == ' '))
    {
      AddMatch(id + (106 * n), l + 4, l, matches);
    }
  }
  *has_found_match_ref = has_found_match;
}


----------------------------
void helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_1(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches, DictWord w, const size_t l, const size_t n, const size_t id)
{
  int has_found_match = *has_found_match_ref;
  const int is_all_caps = (!(!(w.transform != BROTLI_TRANSFORM_UPPERCASE_FIRST))) ? (1) : (0);
  const uint8_t *s;
  unsigned int s_idx = 0;
  if (!IsMatch(dictionary->words, w, data, max_length))
  {
    continue;
  }
  AddMatch(id + (((is_all_caps) ? (44) : (9)) * n), l, l, matches);
  has_found_match = 1;
  if ((l + 1) >= max_length)
  {
    continue;
  }
  s_idx = &data[l];
  if (s[0 + s_idx] == ' ')
  {
    AddMatch(id + (((is_all_caps) ? (68) : (4)) * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '"')
  {
    AddMatch(id + (((is_all_caps) ? (87) : (66)) * n), l + 1, l, matches);
    if (s[1 + s_idx] == '>')
    {
      AddMatch(id + (((is_all_caps) ? (97) : (69)) * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '.')
  {
    AddMatch(id + (((is_all_caps) ? (101) : (79)) * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (114) : (88)) * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == ',')
  {
    AddMatch(id + (((is_all_caps) ? (112) : (99)) * n), l + 1, l, matches);
    if (s[1 + s_idx] == ' ')
    {
      AddMatch(id + (((is_all_caps) ? (107) : (58)) * n), l + 2, l, matches);
    }
  }
  else
    if (s[0 + s_idx] == '\'')
  {
    AddMatch(id + (((is_all_caps) ? (94) : (74)) * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '(')
  {
    AddMatch(id + (((is_all_caps) ? (113) : (78)) * n), l + 1, l, matches);
  }
  else
    if (s[0 + s_idx] == '=')
  {
    if (s[1 + s_idx] == '"')
    {
      AddMatch(id + (((is_all_caps) ? (105) : (104)) * n), l + 2, l, matches);
    }
    else
      if (s[1 + s_idx] == '\'')
    {
      AddMatch(id + (((is_all_caps) ? (116) : (108)) * n), l + 2, l, matches);
    }
  }
  *has_found_match_ref = has_found_match;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
***/


// hint:  ['has_found_match_ref is a mutable refrence to int']
void helper_BrotliFindAllStaticDictionaryMatches_4(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t min_length, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  size_t offset = dictionary->buckets[Hash(data)];
  int end = !offset;
  while (!end)
  {
    helper_helper_BrotliFindAllStaticDictionaryMatches_4_1(&has_found_match, &offset, &end, dictionary, data, min_length, max_length, matches);
  }

  *has_found_match_ref = has_found_match;
}


/*** DEPENDENCIES:
inline static uint32_t Hash(const uint8_t *p, size_t shift)
{
  const uint64_t h = (BrotliUnalignedRead64(p) << 24) * kHashMul32;
  return (uint32_t) (h >> shift);
}


----------------------------
void helper_helper_BrotliFindAllStaticDictionaryMatches_4_1(int * const has_found_match_ref, size_t * const offset_ref, int * const end_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t min_length, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  size_t offset = *offset_ref;
  int end = *end_ref;
  DictWord w = dictionary->dict_words[offset];
  offset += 1;
  const size_t l = w.len & 0x1F;
  const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
  const size_t id = w.idx;
  end = !(!(w.len & 0x80));
  w.len = (uint8_t) l;
  if (w.transform == 0)
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_2(&has_found_match, dictionary, data, min_length, max_length, matches, l, n, id);
  }
  else
  {
    helper_helper_helper_BrotliFindAllStaticDictionaryMatches_4_1_1(&has_found_match, dictionary, data, max_length, matches, w, l, n, id);
  }
  *has_found_match_ref = has_found_match;
  *offset_ref = offset;
  *end_ref = end;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
***/


int BrotliFindAllStaticDictionaryMatches(const BrotliEncoderDictionary *dictionary, const uint8_t *data, size_t min_length, size_t max_length, uint32_t *matches)
{
  int has_found_match = 0;
  {
    helper_BrotliFindAllStaticDictionaryMatches_4(&has_found_match, dictionary, data, min_length, max_length, matches);
  }
  if ((max_length >= 5) && ((data[0] == ' ') || (data[0] == '.')))
  {
    helper_BrotliFindAllStaticDictionaryMatches_3(&has_found_match, dictionary, data, max_length, matches);
  }
  if (max_length >= 6)
  {
    helper_BrotliFindAllStaticDictionaryMatches_1(&has_found_match, dictionary, data, max_length, matches);
  }
  if (max_length >= 9)
  {
    helper_BrotliFindAllStaticDictionaryMatches_2(&has_found_match, dictionary, data, max_length, matches);
  }
  return has_found_match;
}


/*** DEPENDENCIES:
void helper_BrotliFindAllStaticDictionaryMatches_2(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  if ((((((data[0] == ' ') && (data[1] == 't')) && (data[2] == 'h')) && (data[3] == 'e')) && (data[4] == ' ')) || (((((data[0] == '.') && (data[1] == 'c')) && (data[2] == 'o')) && (data[3] == 'm')) && (data[4] == '/')))
  {
    size_t offset = dictionary->buckets[Hash(&data[5])];
    int end = !offset;
    while (!end)
    {
      DictWord w = dictionary->dict_words[offset];
      offset += 1;
      const size_t l = w.len & 0x1F;
      const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
      const size_t id = w.idx;
      end = !(!(w.len & 0x80));
      w.len = (uint8_t) l;
      if ((w.transform == 0) && IsMatch(dictionary->words, w, &data[5], max_length - 5))
      {
        AddMatch(id + (((data[0] == ' ') ? (41) : (72)) * n), l + 5, l, matches);
        has_found_match = 1;
        if ((l + 5) < max_length)
        {
          const uint8_t *s = &data[l + 5];
          unsigned int s_idx = 0;
          if (data[0] == ' ')
          {
            if ((((((l + 8) < max_length) && (s[0 + s_idx] == ' ')) && (s[1 + s_idx] == 'o')) && (s[2 + s_idx] == 'f')) && (s[3 + s_idx] == ' '))
            {
              AddMatch(id + (62 * n), l + 9, l, matches);
              if ((((((l + 12) < max_length) && (s[4 + s_idx] == 't')) && (s[5 + s_idx] == 'h')) && (s[6 + s_idx] == 'e')) && (s[7 + s_idx] == ' '))
              {
                AddMatch(id + (73 * n), l + 13, l, matches);
              }
            }
          }
        }
      }
    }

  }
  *has_found_match_ref = has_found_match;
}


----------------------------
void helper_BrotliFindAllStaticDictionaryMatches_3(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  int is_space = (!(!(data[0] == ' '))) ? (1) : (0);
  size_t offset = dictionary->buckets[Hash(&data[1])];
  int end = !offset;
  while (!end)
  {
    helper_helper_BrotliFindAllStaticDictionaryMatches_3_1(&has_found_match, &offset, &end, dictionary, data, max_length, matches, is_space);
  }

  *has_found_match_ref = has_found_match;
}


----------------------------
typedef struct BrotliEncoderDictionary
{
  const BrotliDictionary *words;
  uint32_t num_transforms;
  uint32_t cutoffTransformsCount;
  uint64_t cutoffTransforms;
  const uint16_t *hash_table_words;
  const uint8_t *hash_table_lengths;
  const uint16_t *buckets;
  const DictWord *dict_words;
} BrotliEncoderDictionary
----------------------------
void helper_BrotliFindAllStaticDictionaryMatches_1(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  if (((data[1] == ' ') && (((data[0] == 'e') || (data[0] == 's')) || (data[0] == ','))) || ((data[0] == 0xC2) && (data[1] == 0xA0)))
  {
    size_t offset = dictionary->buckets[Hash(&data[2])];
    int end = !offset;
    while (!end)
    {
      DictWord w = dictionary->dict_words[offset];
      offset += 1;
      const size_t l = w.len & 0x1F;
      const size_t n = ((size_t) 1) << dictionary->words->size_bits_by_length[l];
      const size_t id = w.idx;
      end = !(!(w.len & 0x80));
      w.len = (uint8_t) l;
      if ((w.transform == 0) && IsMatch(dictionary->words, w, &data[2], max_length - 2))
      {
        if (data[0] == 0xC2)
        {
          AddMatch(id + (102 * n), l + 2, l, matches);
          has_found_match = 1;
        }
        else
          if (((l + 2) < max_length) && (data[l + 2] == ' '))
        {
          size_t t = (data[0] == 'e') ? (18) : ((data[0] == 's') ? (7) : (13));
          AddMatch(id + (t * n), l + 3, l, matches);
          has_found_match = 1;
        }
      }
    }

  }
  *has_found_match_ref = has_found_match;
}


----------------------------
void helper_BrotliFindAllStaticDictionaryMatches_4(int * const has_found_match_ref, const BrotliEncoderDictionary * const dictionary, const uint8_t * const data, size_t min_length, size_t max_length, uint32_t * const matches)
{
  int has_found_match = *has_found_match_ref;
  size_t offset = dictionary->buckets[Hash(data)];
  int end = !offset;
  while (!end)
  {
    helper_helper_BrotliFindAllStaticDictionaryMatches_4_1(&has_found_match, &offset, &end, dictionary, data, min_length, max_length, matches);
  }

  *has_found_match_ref = has_found_match;
}


----------------------------
***/


