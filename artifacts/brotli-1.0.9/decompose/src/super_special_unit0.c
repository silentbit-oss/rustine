// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H2
{
  HasherCommon *common;
  uint32_t *buckets_;
} H2
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H41
{
  uint16_t free_slot_idx[1];
  size_t max_hops;
  void *extra;
  HasherCommon *common;
} H41
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H35
{
  H3 ha;
  HROLLING_FAST hb;
  HasherCommon hb_common;
  void *extra;
  HasherCommon *common;
  int fresh;
  const BrotliEncoderParams *params;
} H35
/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H4
{
  HasherCommon *common;
  uint32_t *buckets_;
} H4
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H42
{
  uint16_t free_slot_idx[512];
  size_t max_hops;
  void *extra;
  HasherCommon *common;
} H42
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct 
{
  void *extra;
  size_t dict_num_lookups;
  size_t dict_num_matches;
  BrotliHasherParams params;
  int is_prepared_;
} HasherCommon
/*** DEPENDENCIES:
typedef struct BrotliHasherParams
{
  int type;
  int bucket_bits;
  int block_bits;
  int hash_len;
  int num_last_distances_to_check;
} BrotliHasherParams
----------------------------
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct 
{
  HasherCommon common;
  union 
  {
    H2 _H2;
    H3 _H3;
    H4 _H4;
    H5 _H5;
    H6 _H6;
    H40 _H40;
    H41 _H41;
    H42 _H42;
    H54 _H54;
    H35 _H35;
    H55 _H55;
    H65 _H65;
    H10 _H10;
  } privat;
} Hasher
/*** DEPENDENCIES:
typedef struct H10
{
  size_t window_mask_;
  uint32_t *buckets_;
  uint32_t invalid_pos_;
  uint32_t *forest_;
} H10
----------------------------
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H40
{
  uint16_t free_slot_idx[1];
  size_t max_hops;
  void *extra;
  HasherCommon *common;
} H40
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H5
{
  size_t bucket_size_;
  size_t block_size_;
  int hash_shift_;
  uint32_t block_mask_;
  int block_bits_;
  int num_last_distances_to_check_;
  HasherCommon *common_;
  uint16_t *num_;
  uint32_t *buckets_;
} H5
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H6
{
  size_t bucket_size_;
  size_t block_size_;
  int hash_shift_;
  uint64_t hash_mask_;
  uint32_t block_mask_;
  int block_bits_;
  int num_last_distances_to_check_;
  HasherCommon *common_;
  uint16_t *num_;
  uint32_t *buckets_;
} H6
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H65
{
  H6 ha;
  HROLLING hb;
  HasherCommon hb_common;
  void *extra;
  HasherCommon *common;
  int fresh;
  const BrotliEncoderParams *params;
} H65
/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct BrotliEncoderParams
{
  BrotliEncoderMode mode;
  int quality;
  int lgwin;
  int lgblock;
  size_t stream_offset;
  size_t size_hint;
  int disable_literal_context_modeling;
  int large_window;
  BrotliHasherParams hasher;
  BrotliDistanceParams dist;
  BrotliEncoderDictionary dictionary;
} BrotliEncoderParams
/*** DEPENDENCIES:
typedef enum BrotliEncoderMode
{
  BROTLI_MODE_GENERIC = 0,
  BROTLI_MODE_TEXT = 1,
  BROTLI_MODE_FONT = 2
} BrotliEncoderMode
----------------------------
typedef struct BrotliHasherParams
{
  int type;
  int bucket_bits;
  int block_bits;
  int hash_len;
  int num_last_distances_to_check;
} BrotliHasherParams
----------------------------
typedef struct BrotliDistanceParams
{
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  size_t max_distance;
} BrotliDistanceParams
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
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H3
{
  HasherCommon *common;
  uint32_t *buckets_;
} H3
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H55
{
  H54 ha;
  HROLLING_FAST hb;
  HasherCommon hb_common;
  void *extra;
  HasherCommon *common;
  int fresh;
  const BrotliEncoderParams *params;
} H55
/*** DEPENDENCIES:
typedef struct HROLLING
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING
----------------------------
typedef struct HROLLING_FAST
{
  uint32_t state;
  uint32_t *table;
  size_t next_ix;
  uint32_t chunk_len;
  uint32_t factor;
  uint32_t factor_remove;
} HROLLING_FAST
----------------------------
None
----------------------------
***/


// element in merge of:  H2,H41,H35,H4,H42,HasherCommon,Hasher,H40,H5,H6,H65,BrotliEncoderParams,H3,H55,H54
typedef struct H54
{
  HasherCommon *common;
  uint32_t *buckets_;
} H54
/*** DEPENDENCIES:
None
----------------------------
***/


