typedef struct ContextBlockSplitter
{
  size_t alphabet_size_;
  size_t num_contexts_;
  size_t max_block_types_;
  size_t min_block_size_;
  double split_threshold_;
  size_t num_blocks_;
  BlockSplit *split_;
  HistogramLiteral *histograms_;
  size_t *histograms_size_;
  size_t target_block_size_;
  size_t block_size_;
  size_t curr_histogram_ix_;
  size_t last_histogram_ix_[2];
  double last_entropy_[2 * 13];
  size_t merge_last_count_;
} ContextBlockSplitter
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
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


