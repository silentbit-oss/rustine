typedef struct BlockSplitIterator
{
  const BlockSplit *split_;
  size_t idx_;
  size_t type_;
  size_t length_;
} BlockSplitIterator
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
***/


