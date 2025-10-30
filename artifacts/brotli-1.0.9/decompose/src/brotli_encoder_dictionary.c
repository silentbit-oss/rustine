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
/*** DEPENDENCIES:
typedef struct BrotliDictionary
{
  uint8_t size_bits_by_length[32];
  uint32_t offsets_by_length[32];
  size_t data_size;
  const uint8_t *data;
} BrotliDictionary
----------------------------
typedef struct DictWord
{
  uint8_t len;
  uint8_t transform;
  uint16_t idx;
} DictWord
----------------------------
***/


