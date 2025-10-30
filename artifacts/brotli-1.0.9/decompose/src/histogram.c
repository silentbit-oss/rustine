static void BlockSplitIteratorNext(BlockSplitIterator *self)
{
  if (self->length_ == 0)
  {
    self->idx_ += 1;
    self->type_ = self->split_->types[self->idx_];
    self->length_ = self->split_->lengths[self->idx_];
  }
  self->length_ -= 1;
}


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
typedef struct BlockSplitIterator
{
  const BlockSplit *split_;
  size_t idx_;
  size_t type_;
  size_t length_;
} BlockSplitIterator
----------------------------
***/


// hint:  ['prev_byte_ref is a mutable refrence to uint8_t', 'prev_byte2_ref is a mutable refrence to uint8_t', 'pos_ref is a mutable refrence to size_t']
void helper_BrotliBuildHistogramsWithContext_1(uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, size_t * const pos_ref, const Command * const cmds, const uint8_t * const ringbuffer, size_t mask, const ContextType * const context_modes, HistogramLiteral * const literal_histograms, HistogramCommand * const insert_and_copy_histograms, HistogramDistance * const copy_dist_histograms, BlockSplitIterator literal_it, BlockSplitIterator insert_and_copy_it, BlockSplitIterator dist_it, size_t i)
{
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  size_t pos = *pos_ref;
  const Command *cmd = &cmds[i];
  size_t j;
  BlockSplitIteratorNext(&insert_and_copy_it);
  HistogramAddCommand(&insert_and_copy_histograms[insert_and_copy_it.type_], cmd->cmd_prefix_);
  for (j = cmd->insert_len_; j != 0; j -= 1)
  {
    size_t context;
    BlockSplitIteratorNext(&literal_it);
    context = literal_it.type_;
    if (context_modes)
    {
      ContextLut lut = &_kBrotliContextLookupTable[context_modes[context] << 9];
      context = (context << 6) + (lut[prev_byte] | (lut + 256)[prev_byte2]);
    }
    HistogramAddLiteral(&literal_histograms[context], ringbuffer[pos & mask]);
    prev_byte2 = prev_byte;
    prev_byte = ringbuffer[pos & mask];
    pos += 1;
  }

  pos += CommandCopyLen(cmd);
  if (CommandCopyLen(cmd))
  {
    prev_byte2 = ringbuffer[(pos - 2) & mask];
    prev_byte = ringbuffer[(pos - 1) & mask];
    if (cmd->cmd_prefix_ >= 128)
    {
      size_t context;
      BlockSplitIteratorNext(&dist_it);
      context = (dist_it.type_ << 2) + CommandDistanceContext(cmd);
      HistogramAddDistance(&copy_dist_histograms[context], cmd->dist_prefix_ & 0x3FF);
    }
  }
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
  *pos_ref = pos;
}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
}


----------------------------
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
extern const uint8_t _kBrotliContextLookupTable[2048]
----------------------------
typedef struct BlockSplitIterator
{
  const BlockSplit *split_;
  size_t idx_;
  size_t type_;
  size_t length_;
} BlockSplitIterator
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
typedef const uint8_t *ContextLut
----------------------------
inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
static void BlockSplitIteratorNext(BlockSplitIterator *self)
{
  if (self->length_ == 0)
  {
    self->idx_ += 1;
    self->type_ = self->split_->types[self->idx_];
    self->length_ = self->split_->lengths[self->idx_];
  }
  self->length_ -= 1;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static uint32_t CommandDistanceContext(const Command *self)
{
  uint32_t r = self->cmd_prefix_ >> 6;
  uint32_t c = self->cmd_prefix_ & 7;
  if (((((r == 0) || (r == 2)) || (r == 4)) || (r == 7)) && (c <= 2))
  {
    return c;
  }
  return 3;
}


----------------------------
inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


----------------------------
***/


static void InitBlockSplitIterator(BlockSplitIterator *self, const BlockSplit *split)
{
  self->split_ = split;
  self->idx_ = 0;
  self->type_ = 0;
  self->length_ = (split->lengths) ? (split->lengths[0]) : (0);
}


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
typedef struct BlockSplitIterator
{
  const BlockSplit *split_;
  size_t idx_;
  size_t type_;
  size_t length_;
} BlockSplitIterator
----------------------------
***/


void BrotliBuildHistogramsWithContext(const Command *cmds, const size_t num_commands, const BlockSplit *literal_split, const BlockSplit *insert_and_copy_split, const BlockSplit *dist_split, const uint8_t *ringbuffer, size_t start_pos, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, const ContextType *context_modes, HistogramLiteral *literal_histograms, HistogramCommand *insert_and_copy_histograms, HistogramDistance *copy_dist_histograms)
{
  size_t pos = start_pos;
  BlockSplitIterator literal_it;
  BlockSplitIterator insert_and_copy_it;
  BlockSplitIterator dist_it;
  size_t i;
  InitBlockSplitIterator(&literal_it, literal_split);
  InitBlockSplitIterator(&insert_and_copy_it, insert_and_copy_split);
  InitBlockSplitIterator(&dist_it, dist_split);
  for (i = 0; i < num_commands; i += 1)
  {
    helper_BrotliBuildHistogramsWithContext_1(&prev_byte, &prev_byte2, &pos, cmds, ringbuffer, mask, context_modes, literal_histograms, insert_and_copy_histograms, copy_dist_histograms, literal_it, insert_and_copy_it, dist_it, i);
  }

}


/*** DEPENDENCIES:
void helper_BrotliBuildHistogramsWithContext_1(uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, size_t * const pos_ref, const Command * const cmds, const uint8_t * const ringbuffer, size_t mask, const ContextType * const context_modes, HistogramLiteral * const literal_histograms, HistogramCommand * const insert_and_copy_histograms, HistogramDistance * const copy_dist_histograms, BlockSplitIterator literal_it, BlockSplitIterator insert_and_copy_it, BlockSplitIterator dist_it, size_t i)
{
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  size_t pos = *pos_ref;
  const Command *cmd = &cmds[i];
  size_t j;
  BlockSplitIteratorNext(&insert_and_copy_it);
  HistogramAddCommand(&insert_and_copy_histograms[insert_and_copy_it.type_], cmd->cmd_prefix_);
  for (j = cmd->insert_len_; j != 0; j -= 1)
  {
    size_t context;
    BlockSplitIteratorNext(&literal_it);
    context = literal_it.type_;
    if (context_modes)
    {
      ContextLut lut = &_kBrotliContextLookupTable[context_modes[context] << 9];
      context = (context << 6) + (lut[prev_byte] | (lut + 256)[prev_byte2]);
    }
    HistogramAddLiteral(&literal_histograms[context], ringbuffer[pos & mask]);
    prev_byte2 = prev_byte;
    prev_byte = ringbuffer[pos & mask];
    pos += 1;
  }

  pos += CommandCopyLen(cmd);
  if (CommandCopyLen(cmd))
  {
    prev_byte2 = ringbuffer[(pos - 2) & mask];
    prev_byte = ringbuffer[(pos - 1) & mask];
    if (cmd->cmd_prefix_ >= 128)
    {
      size_t context;
      BlockSplitIteratorNext(&dist_it);
      context = (dist_it.type_ << 2) + CommandDistanceContext(cmd);
      HistogramAddDistance(&copy_dist_histograms[context], cmd->dist_prefix_ & 0x3FF);
    }
  }
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
  *pos_ref = pos;
}


----------------------------
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
static void InitBlockSplitIterator(BlockSplitIterator *self, const BlockSplit *split)
{
  self->split_ = split;
  self->idx_ = 0;
  self->type_ = 0;
  self->length_ = (split->lengths) ? (split->lengths[0]) : (0);
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef struct BlockSplitIterator
{
  const BlockSplit *split_;
  size_t idx_;
  size_t type_;
  size_t length_;
} BlockSplitIterator
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


