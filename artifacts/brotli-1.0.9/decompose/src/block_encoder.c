typedef struct BlockEncoder
{
  size_t histogram_length_;
  size_t num_block_types_;
  const uint8_t *block_types_;
  const uint32_t *block_lengths_;
  size_t num_blocks_;
  BlockSplitCode block_split_code_;
  size_t block_ix_;
  size_t block_len_;
  size_t entropy_ix_;
  uint8_t *depths_;
  uint16_t *bits_;
} BlockEncoder
/*** DEPENDENCIES:
typedef struct BlockSplit
{
  size_t num_types;
  size_t num_blocks;
  uint8_t *types;
  uint32_t *lengths;
  size_t types_alloc_size;
  size_t lengths_alloc_size;
} BlockSplit
----------------------------
typedef struct BlockSplitCode
{
  BlockTypeCodeCalculator type_code_calculator;
  uint8_t type_depths[256 + 2];
  uint16_t type_bits[256 + 2];
  uint8_t length_depths[26];
  uint16_t length_bits[26];
} BlockSplitCode
----------------------------
***/


