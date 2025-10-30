typedef struct BrotliMetablockHeaderArena
{
  BrotliRunningTreeGroupState substate_tree_group;
  BrotliRunningContextMapState substate_context_map;
  BrotliRunningHuffmanState substate_huffman;
  uint32_t sub_loop_counter;
  uint32_t repeat_code_len;
  uint32_t prev_code_len;
  uint32_t symbol;
  uint32_t repeat;
  uint32_t space;
  HuffmanCode table[32];
  uint16_t *symbol_lists;
  uint16_t symbols_lists_array[(15 + 1) + 704];
  int next_symbol[32];
  uint8_t code_length_code_lengths[17 + 1];
  uint16_t code_length_histo[16];
  int htree_index;
  HuffmanCode *next;
  uint32_t context_index;
  uint32_t max_run_length_prefix;
  uint32_t code;
  HuffmanCode context_map_table[646];
} BrotliMetablockHeaderArena
/*** DEPENDENCIES:
typedef enum 
{
  BROTLI_STATE_HUFFMAN_NONE,
  BROTLI_STATE_HUFFMAN_SIMPLE_SIZE,
  BROTLI_STATE_HUFFMAN_SIMPLE_READ,
  BROTLI_STATE_HUFFMAN_SIMPLE_BUILD,
  BROTLI_STATE_HUFFMAN_COMPLEX,
  BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS
} BrotliRunningHuffmanState
----------------------------
typedef enum 
{
  BROTLI_STATE_CONTEXT_MAP_NONE,
  BROTLI_STATE_CONTEXT_MAP_READ_PREFIX,
  BROTLI_STATE_CONTEXT_MAP_HUFFMAN,
  BROTLI_STATE_CONTEXT_MAP_DECODE,
  BROTLI_STATE_CONTEXT_MAP_TRANSFORM
} BrotliRunningContextMapState
----------------------------
typedef enum 
{
  BROTLI_STATE_TREE_GROUP_NONE,
  BROTLI_STATE_TREE_GROUP_LOOP
} BrotliRunningTreeGroupState
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
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


