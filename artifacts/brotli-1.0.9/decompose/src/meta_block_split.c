typedef struct MetaBlockSplit
{
  BlockSplit literal_split;
  BlockSplit command_split;
  BlockSplit distance_split;
  uint32_t *literal_context_map;
  size_t literal_context_map_size;
  uint32_t *distance_context_map;
  size_t distance_context_map_size;
  HistogramLiteral *literal_histograms;
  size_t literal_histograms_size;
  HistogramCommand *command_histograms;
  size_t command_histograms_size;
  HistogramDistance *distance_histograms;
  size_t distance_histograms_size;
} MetaBlockSplit
/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
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
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


