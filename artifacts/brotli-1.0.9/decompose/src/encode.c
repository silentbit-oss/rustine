size_t BrotliEncoderMaxCompressedSize(size_t input_size)
{
  size_t num_large_blocks = input_size >> 14;
  size_t overhead = ((2 + (4 * num_large_blocks)) + 3) + 1;
  size_t result = input_size + overhead;
  if (input_size == 0)
  {
    return 2;
  }
  return (result < input_size) ? (0) : (result);
}


/*** DEPENDENCIES:
***/


uint32_t BrotliEncoderVersion(void)
{
  return 0x1000009;
}


/*** DEPENDENCIES:
***/


static uint32_t WrapPosition(uint64_t position)
{
  uint32_t result = (uint32_t) position;
  uint64_t gb = position >> 30;
  if (gb > 2)
  {
    result = (result & ((1u << 30) - 1)) | ((((uint32_t) ((gb - 1) & 1)) + 1) << 30);
  }
  return result;
}


/*** DEPENDENCIES:
***/


static size_t HashTableSize(size_t max_table_size, size_t input_size)
{
  size_t htsize = 256;
  while ((htsize < max_table_size) && (htsize < input_size))
  {
    htsize <<= 1;
  }

  return htsize;
}


/*** DEPENDENCIES:
***/


static void EncodeWindowBits(int lgwin, int large_window, uint16_t *last_bytes, uint8_t *last_bytes_bits)
{
  if (large_window)
  {
    *last_bytes = (uint16_t) (((lgwin & 0x3F) << 8) | 0x11);
    *last_bytes_bits = 14;
  }
  else
  {
    if (lgwin == 16)
    {
      *last_bytes = 0;
      *last_bytes_bits = 1;
    }
    else
      if (lgwin == 17)
    {
      *last_bytes = 1;
      *last_bytes_bits = 7;
    }
    else
      if (lgwin > 17)
    {
      *last_bytes = (uint16_t) (((lgwin - 17) << 1) | 0x01);
      *last_bytes_bits = 4;
    }
    else
    {
      *last_bytes = (uint16_t) (((lgwin - 8) << 4) | 0x01);
      *last_bytes_bits = 7;
    }
  }
}


/*** DEPENDENCIES:
***/


static void InitCommandPrefixCodes(uint8_t cmd_depths[128], uint16_t cmd_bits[128], uint8_t cmd_code[512], size_t *cmd_code_numbits)
{
  static const uint8_t kDefaultCommandDepths[128] = {0, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 0, 0, 0, 4, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 0, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 7, 7, 7, 8, 10, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
  static const uint16_t kDefaultCommandBits[128] = {0, 0, 8, 9, 3, 35, 7, 71, 39, 103, 23, 47, 175, 111, 239, 31, 0, 0, 0, 4, 12, 2, 10, 6, 13, 29, 11, 43, 27, 59, 87, 55, 15, 79, 319, 831, 191, 703, 447, 959, 0, 14, 1, 25, 5, 21, 19, 51, 119, 159, 95, 223, 479, 991, 63, 575, 127, 639, 383, 895, 255, 767, 511, 1023, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 59, 7, 39, 23, 55, 30, 1, 17, 9, 25, 5, 0, 8, 4, 12, 2, 10, 6, 21, 13, 29, 3, 19, 11, 15, 47, 31, 95, 63, 127, 255, 767, 2815, 1791, 3839, 511, 2559, 1535, 3583, 1023, 3071, 2047, 4095};
  static const uint8_t kDefaultCommandCode[] = {0xff, 0x77, 0xd5, 0xbf, 0xe7, 0xde, 0xea, 0x9e, 0x51, 0x5d, 0xde, 0xc6, 0x70, 0x57, 0xbc, 0x58, 0x58, 0x58, 0xd8, 0xd8, 0x58, 0xd5, 0xcb, 0x8c, 0xea, 0xe0, 0xc3, 0x87, 0x1f, 0x83, 0xc1, 0x60, 0x1c, 0x67, 0xb2, 0xaa, 0x06, 0x83, 0xc1, 0x60, 0x30, 0x18, 0xcc, 0xa1, 0xce, 0x88, 0x54, 0x94, 0x46, 0xe1, 0xb0, 0xd0, 0x4e, 0xb2, 0xf7, 0x04, 0x00};
  static const size_t kDefaultCommandCodeNumBits = 448;
  memcpy(cmd_depths, kDefaultCommandDepths, sizeof(kDefaultCommandDepths));
  ;
  memcpy(cmd_bits, kDefaultCommandBits, sizeof(kDefaultCommandBits));
  ;
  memcpy(cmd_code, kDefaultCommandCode, sizeof(kDefaultCommandCode));
  ;
  *cmd_code_numbits = kDefaultCommandCodeNumBits;
}


/*** DEPENDENCIES:
***/


// hint:  ['size_ref is a mutable refrence to size_t', 'result_ref is a mutable refrence to size_t', 'offset_ref is a mutable refrence to size_t']
void helper_MakeUncompressedStream_1(size_t * const size_ref, size_t * const result_ref, size_t * const offset_ref, const uint8_t * const input, uint8_t * const output)
{
  size_t size = *size_ref;
  size_t result = *result_ref;
  size_t offset = *offset_ref;
  uint32_t nibbles = 0;
  uint32_t chunk_size;
  uint32_t bits;
  chunk_size = (size > (1u << 24)) ? (1u << 24) : ((uint32_t) size);
  if (chunk_size > (1u << 16))
  {
    nibbles = (chunk_size > (1u << 20)) ? (2) : (1);
  }
  bits = ((nibbles << 1) | ((chunk_size - 1) << 3)) | (1u << (19 + (4 * nibbles)));
  output[result] = (uint8_t) bits;
  result += 1;
  output[result] = (uint8_t) (bits >> 8);
  result += 1;
  output[result] = (uint8_t) (bits >> 16);
  result += 1;
  if (nibbles == 2)
  {
    output[result] = (uint8_t) (bits >> 24);
    result += 1;
  }
  memcpy(&output[result], &input[offset], chunk_size);
  result += chunk_size;
  offset += chunk_size;
  size -= chunk_size;
  *size_ref = size;
  *result_ref = result;
  *offset_ref = offset;
}


/*** DEPENDENCIES:
***/


int BrotliEncoderHasMoreOutput(BrotliEncoderState *s)
{
  return (!(!(s->available_out_ != 0))) ? (1) : (0);
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


inline static void RingBufferInit(RingBuffer *rb)
{
  rb->cur_size_ = 0;
  rb->pos_ = 0;
  rb->data_ = 0;
  rb->buffer_ = 0;
}


/*** DEPENDENCIES:
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
***/


static size_t InputBlockSize(BrotliEncoderState *s)
{
  return ((size_t) 1) << s->params.lgblock;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


static uint64_t UnprocessedInputSize(BrotliEncoderState *s)
{
  return s->input_pos_ - s->last_processed_pos_;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


static void ChooseContextMap(int quality, uint32_t *bigram_histo, size_t *num_literal_contexts, const uint32_t **literal_context_map)
{
  static const uint32_t kStaticContextMapContinuation[64] = {1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const uint32_t kStaticContextMapSimpleUTF8[64] = {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint32_t monogram_histo[3] = {0};
  uint32_t two_prefix_histo[6] = {0};
  size_t total;
  size_t i;
  size_t dummy;
  double entropy[4];
  for (i = 0; i < 9; i += 1)
  {
    monogram_histo[i % 3] += bigram_histo[i];
    two_prefix_histo[i % 6] += bigram_histo[i];
  }

  entropy[1] = ShannonEntropy(monogram_histo, 3, &dummy);
  entropy[2] = ShannonEntropy(two_prefix_histo, 3, &dummy) + ShannonEntropy(two_prefix_histo + 3, 3, &dummy);
  entropy[3] = 0;
  for (i = 0; i < 3; i += 1)
  {
    entropy[3] += ShannonEntropy(bigram_histo + (3 * i), 3, &dummy);
  }

  total = (monogram_histo[0] + monogram_histo[1]) + monogram_histo[2];
  ;
  entropy[0] = 1.0 / ((double) total);
  entropy[1] *= entropy[0];
  entropy[2] *= entropy[0];
  entropy[3] *= entropy[0];
  if (quality < 7)
  {
    entropy[3] = entropy[1] * 10;
  }
  if (((entropy[1] - entropy[2]) < 0.2) && ((entropy[1] - entropy[3]) < 0.2))
  {
    *num_literal_contexts = 1;
  }
  else
    if ((entropy[2] - entropy[3]) < 0.02)
  {
    *num_literal_contexts = 2;
    *literal_context_map = kStaticContextMapSimpleUTF8;
  }
  else
  {
    *num_literal_contexts = 3;
    *literal_context_map = kStaticContextMapContinuation;
  }
}


/*** DEPENDENCIES:
inline static double ShannonEntropy(const uint32_t *population, size_t size, size_t *total)
{
  unsigned int population_idx = 0;
  size_t sum = 0;
  double retval = 0;
  const uint32_t *population_end = (&population[population_idx]) + size;
  size_t p;
  if (size & 1)
  {
    goto odd_number_of_elements_left;
  }
  while ((&population[population_idx]) < population_end)
  {
    p = population[population_idx];
    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
    odd_number_of_elements_left:
    p = population[population_idx];

    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
  }

  if (sum)
  {
    retval += ((double) sum) * FastLog2(sum);
  }
  *total = sum;
  return retval;
}


----------------------------
***/


// hint:  ['total_ref is a mutable refrence to uint32_t']
void helper_helper_ShouldUseComplexStaticContextMap_1_1(uint32_t * const total_ref, const uint8_t * const input, size_t mask, static const uint32_t kStaticContextMapComplexUTF8[64], size_t start_pos, uint32_t combined_histo[32], uint32_t context_histo[13][32], ContextLut utf8_lut)
{
  uint32_t total = *total_ref;
  const size_t stride_end_pos = start_pos + 64;
  uint8_t prev2 = input[start_pos & mask];
  uint8_t prev1 = input[(start_pos + 1) & mask];
  size_t pos;
  for (pos = start_pos + 2; pos < stride_end_pos; pos += 1)
  {
    const uint8_t literal = input[pos & mask];
    const uint8_t context = (uint8_t) kStaticContextMapComplexUTF8[utf8_lut[prev1] | (utf8_lut + 256)[prev2]];
    total += 1;
    combined_histo[literal >> 3] += 1;
    context_histo[context][literal >> 3] += 1;
    prev2 = prev1;
    prev1 = literal;
  }

  *total_ref = total;
}


/*** DEPENDENCIES:
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
typedef const uint8_t *ContextLut
----------------------------
***/


// hint:  ['start_pos_ref is a mutable refrence to size_t']
int helper_ShouldUseComplexStaticContextMap_1(size_t * const start_pos_ref, const uint8_t * const input, size_t length, size_t mask, size_t * const num_literal_contexts, const uint32_t ** const literal_context_map, static const uint32_t kStaticContextMapComplexUTF8[64])
{
  size_t start_pos = *start_pos_ref;
  const size_t end_pos = start_pos + length;
  uint32_t combined_histo[32] = {0};
  uint32_t context_histo[13][32] = {{0}};
  uint32_t total = 0;
  double entropy[3];
  size_t dummy;
  size_t i;
  ContextLut utf8_lut = &_kBrotliContextLookupTable[CONTEXT_UTF8 << 9];
  for (; (start_pos + 64) <= end_pos; start_pos += 4096)
  {
    helper_helper_ShouldUseComplexStaticContextMap_1_1(&total, input, mask, kStaticContextMapComplexUTF8, start_pos, combined_histo, context_histo, utf8_lut);
  }

  entropy[1] = ShannonEntropy(combined_histo, 32, &dummy);
  entropy[2] = 0;
  for (i = 0; i < 13; i += 1)
  {
    entropy[2] += ShannonEntropy(&context_histo[i][0], 32, &dummy);
  }

  entropy[0] = 1.0 / ((double) total);
  entropy[1] *= entropy[0];
  entropy[2] *= entropy[0];
  if ((entropy[2] > 3.0) || ((entropy[1] - entropy[2]) < 0.2))
  {
    return 0;
  }
  else
  {
    *num_literal_contexts = 13;
    *literal_context_map = kStaticContextMapComplexUTF8;
    return 1;
  }
  *start_pos_ref = start_pos;
}


/*** DEPENDENCIES:
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
typedef const uint8_t *ContextLut
----------------------------
inline static double ShannonEntropy(const uint32_t *population, size_t size, size_t *total)
{
  unsigned int population_idx = 0;
  size_t sum = 0;
  double retval = 0;
  const uint32_t *population_end = (&population[population_idx]) + size;
  size_t p;
  if (size & 1)
  {
    goto odd_number_of_elements_left;
  }
  while ((&population[population_idx]) < population_end)
  {
    p = population[population_idx];
    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
    odd_number_of_elements_left:
    p = population[population_idx];

    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
  }

  if (sum)
  {
    retval += ((double) sum) * FastLog2(sum);
  }
  *total = sum;
  return retval;
}


----------------------------
void helper_helper_ShouldUseComplexStaticContextMap_1_1(uint32_t * const total_ref, const uint8_t * const input, size_t mask, static const uint32_t kStaticContextMapComplexUTF8[64], size_t start_pos, uint32_t combined_histo[32], uint32_t context_histo[13][32], ContextLut utf8_lut)
{
  uint32_t total = *total_ref;
  const size_t stride_end_pos = start_pos + 64;
  uint8_t prev2 = input[start_pos & mask];
  uint8_t prev1 = input[(start_pos + 1) & mask];
  size_t pos;
  for (pos = start_pos + 2; pos < stride_end_pos; pos += 1)
  {
    const uint8_t literal = input[pos & mask];
    const uint8_t context = (uint8_t) kStaticContextMapComplexUTF8[utf8_lut[prev1] | (utf8_lut + 256)[prev2]];
    total += 1;
    combined_histo[literal >> 3] += 1;
    context_histo[context][literal >> 3] += 1;
    prev2 = prev1;
    prev1 = literal;
  }

  *total_ref = total;
}


----------------------------
***/


static int ShouldUseComplexStaticContextMap(const uint8_t *input, size_t start_pos, size_t length, size_t mask, int quality, size_t size_hint, size_t *num_literal_contexts, const uint32_t **literal_context_map)
{
  static const uint32_t kStaticContextMapComplexUTF8[64] = {11, 11, 12, 12, 0, 0, 0, 0, 1, 1, 9, 9, 2, 2, 2, 2, 1, 1, 1, 1, 8, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2, 8, 4, 4, 4, 8, 7, 4, 4, 8, 0, 0, 0, 3, 3, 3, 3, 5, 5, 10, 5, 5, 5, 10, 5, 6, 6, 6, 6, 6, 6, 6, 6};
  (void) quality;
  if (size_hint < (1 << 20))
  {
    return 0;
  }
  else
  {
    helper_ShouldUseComplexStaticContextMap_1(&start_pos, input, length, mask, num_literal_contexts, literal_context_map, kStaticContextMapComplexUTF8);
  }
}


/*** DEPENDENCIES:
int helper_ShouldUseComplexStaticContextMap_1(size_t * const start_pos_ref, const uint8_t * const input, size_t length, size_t mask, size_t * const num_literal_contexts, const uint32_t ** const literal_context_map, static const uint32_t kStaticContextMapComplexUTF8[64])
{
  size_t start_pos = *start_pos_ref;
  const size_t end_pos = start_pos + length;
  uint32_t combined_histo[32] = {0};
  uint32_t context_histo[13][32] = {{0}};
  uint32_t total = 0;
  double entropy[3];
  size_t dummy;
  size_t i;
  ContextLut utf8_lut = &_kBrotliContextLookupTable[CONTEXT_UTF8 << 9];
  for (; (start_pos + 64) <= end_pos; start_pos += 4096)
  {
    helper_helper_ShouldUseComplexStaticContextMap_1_1(&total, input, mask, kStaticContextMapComplexUTF8, start_pos, combined_histo, context_histo, utf8_lut);
  }

  entropy[1] = ShannonEntropy(combined_histo, 32, &dummy);
  entropy[2] = 0;
  for (i = 0; i < 13; i += 1)
  {
    entropy[2] += ShannonEntropy(&context_histo[i][0], 32, &dummy);
  }

  entropy[0] = 1.0 / ((double) total);
  entropy[1] *= entropy[0];
  entropy[2] *= entropy[0];
  if ((entropy[2] > 3.0) || ((entropy[1] - entropy[2]) < 0.2))
  {
    return 0;
  }
  else
  {
    *num_literal_contexts = 13;
    *literal_context_map = kStaticContextMapComplexUTF8;
    return 1;
  }
  *start_pos_ref = start_pos;
}


----------------------------
***/


static size_t MakeUncompressedStream(const uint8_t *input, size_t input_size, uint8_t *output)
{
  size_t size = input_size;
  size_t result = 0;
  size_t offset = 0;
  if (input_size == 0)
  {
    output[0] = 6;
    return 1;
  }
  output[result] = 0x21;
  result += 1;
  output[result] = 0x03;
  result += 1;
  while (size > 0)
  {
    helper_MakeUncompressedStream_1(&size, &result, &offset, input, output);
  }

  output[result++] = 3;
  return result;
}


/*** DEPENDENCIES:
void helper_MakeUncompressedStream_1(size_t * const size_ref, size_t * const result_ref, size_t * const offset_ref, const uint8_t * const input, uint8_t * const output)
{
  size_t size = *size_ref;
  size_t result = *result_ref;
  size_t offset = *offset_ref;
  uint32_t nibbles = 0;
  uint32_t chunk_size;
  uint32_t bits;
  chunk_size = (size > (1u << 24)) ? (1u << 24) : ((uint32_t) size);
  if (chunk_size > (1u << 16))
  {
    nibbles = (chunk_size > (1u << 20)) ? (2) : (1);
  }
  bits = ((nibbles << 1) | ((chunk_size - 1) << 3)) | (1u << (19 + (4 * nibbles)));
  output[result] = (uint8_t) bits;
  result += 1;
  output[result] = (uint8_t) (bits >> 8);
  result += 1;
  output[result] = (uint8_t) (bits >> 16);
  result += 1;
  if (nibbles == 2)
  {
    output[result] = (uint8_t) (bits >> 24);
    result += 1;
  }
  memcpy(&output[result], &input[offset], chunk_size);
  result += chunk_size;
  offset += chunk_size;
  size -= chunk_size;
  *size_ref = size;
  *result_ref = result;
  *offset_ref = offset;
}


----------------------------
***/


static void InjectBytePaddingBlock(BrotliEncoderState *s)
{
  uint32_t seal = s->last_bytes_;
  size_t seal_bits = s->last_bytes_bits_;
  uint8_t *destination;
  unsigned int destination_idx = 0;
  s->last_bytes_ = 0;
  s->last_bytes_bits_ = 0;
  seal |= 0x6u << seal_bits;
  seal_bits += 6;
  if (s->next_out_)
  {
    destination_idx = s->next_out_ + s->available_out_;
  }
  else
  {
    destination_idx = s->tiny_buf_.u8;
    s->next_out_ = &destination[destination_idx];
  }
  destination[0 + destination_idx] = (uint8_t) seal;
  if (seal_bits > 8)
  {
    destination[1 + destination_idx] = (uint8_t) (seal >> 8);
  }
  if (seal_bits > 16)
  {
    destination[2 + destination_idx] = (uint8_t) (seal >> 16);
  }
  s->available_out_ += (seal_bits + 7) >> 3;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


static void CheckFlushComplete(BrotliEncoderState *s)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->available_out_ == 0))
  {
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    s->next_out_ = 0;
  }
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


int BrotliEncoderSetParameter(BrotliEncoderState *state, BrotliEncoderParameter p, uint32_t value)
{
  if (state->is_initialized_)
  {
    return 0;
  }
  switch (p)
  {
    case BROTLI_PARAM_MODE:
    {
      state->params.mode = (BrotliEncoderMode) value;
      return 1;
    }

    case BROTLI_PARAM_QUALITY:
    {
      state->params.quality = (int) value;
      return 1;
    }

    case BROTLI_PARAM_LGWIN:
    {
      state->params.lgwin = (int) value;
      return 1;
    }

    case BROTLI_PARAM_LGBLOCK:
    {
      state->params.lgblock = (int) value;
      return 1;
    }

    case BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING:
    {
      if ((value != 0) && (value != 1))
      {
        return 0;
      }
      state->params.disable_literal_context_modeling = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    case BROTLI_PARAM_SIZE_HINT:
    {
      state->params.size_hint = value;
      return 1;
    }

    case BROTLI_PARAM_LARGE_WINDOW:
    {
      state->params.large_window = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    case BROTLI_PARAM_NPOSTFIX:
    {
      state->params.dist.distance_postfix_bits = value;
      return 1;
    }

    case BROTLI_PARAM_NDIRECT:
    {
      state->params.dist.num_direct_distance_codes = value;
      return 1;
    }

    case BROTLI_PARAM_STREAM_OFFSET:
    {
      if (value > (1u << 30))
      {
        return 0;
      }
      state->params.stream_offset = value;
      return 1;
    }

    default:
    {
      return 0;
    }

  }

}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
typedef enum BrotliEncoderParameter
{
  BROTLI_PARAM_MODE = 0,
  BROTLI_PARAM_QUALITY = 1,
  BROTLI_PARAM_LGWIN = 2,
  BROTLI_PARAM_LGBLOCK = 3,
  BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING = 4,
  BROTLI_PARAM_SIZE_HINT = 5,
  BROTLI_PARAM_LARGE_WINDOW = 6,
  BROTLI_PARAM_NPOSTFIX = 7,
  BROTLI_PARAM_NDIRECT = 8,
  BROTLI_PARAM_STREAM_OFFSET = 9
} BrotliEncoderParameter
----------------------------
***/


int BrotliEncoderIsFinished(BrotliEncoderState *s)
{
  return (!(!((s->stream_state_ == BROTLI_STREAM_FINISHED) && (!BrotliEncoderHasMoreOutput(s))))) ? (1) : (0);
}


/*** DEPENDENCIES:
int BrotliEncoderHasMoreOutput(BrotliEncoderState *s)
{
  return (!(!(s->available_out_ != 0))) ? (1) : (0);
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


inline static void RingBufferWriteTail(const uint8_t *bytes, size_t n, RingBuffer *rb)
{
  const size_t masked_pos = rb->pos_ & rb->mask_;
  if (__builtin_expect(masked_pos < rb->tail_size_, 0))
  {
    const size_t p = rb->size_ + masked_pos;
    memcpy(&rb->buffer_[p], bytes, brotli_min_size_t(n, rb->tail_size_ - masked_pos));
  }
}


/*** DEPENDENCIES:
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


static void DecideOverLiteralContextModeling(const uint8_t *input, size_t start_pos, size_t length, size_t mask, int quality, size_t size_hint, size_t *num_literal_contexts, const uint32_t **literal_context_map)
{
  if ((quality < 5) || (length < 64))
  {
    return;
  }
  else
    if (ShouldUseComplexStaticContextMap(input, start_pos, length, mask, quality, size_hint, num_literal_contexts, literal_context_map))
  {
  }
  else
  {
    const size_t end_pos = start_pos + length;
    uint32_t bigram_prefix_histo[9] = {0};
    for (; (start_pos + 64) <= end_pos; start_pos += 4096)
    {
      static const int lut[4] = {0, 0, 1, 2};
      const size_t stride_end_pos = start_pos + 64;
      int prev = lut[input[start_pos & mask] >> 6] * 3;
      size_t pos;
      for (pos = start_pos + 1; pos < stride_end_pos; pos += 1)
      {
        const uint8_t literal = input[pos & mask];
        bigram_prefix_histo[prev + lut[literal >> 6]] += 1;
        prev = lut[literal >> 6] * 3;
      }

    }

    ChooseContextMap(quality, &bigram_prefix_histo[0], num_literal_contexts, literal_context_map);
  }
}


/*** DEPENDENCIES:
static int ShouldUseComplexStaticContextMap(const uint8_t *input, size_t start_pos, size_t length, size_t mask, int quality, size_t size_hint, size_t *num_literal_contexts, const uint32_t **literal_context_map)
{
  static const uint32_t kStaticContextMapComplexUTF8[64] = {11, 11, 12, 12, 0, 0, 0, 0, 1, 1, 9, 9, 2, 2, 2, 2, 1, 1, 1, 1, 8, 3, 3, 3, 1, 1, 1, 1, 2, 2, 2, 2, 8, 4, 4, 4, 8, 7, 4, 4, 8, 0, 0, 0, 3, 3, 3, 3, 5, 5, 10, 5, 5, 5, 10, 5, 6, 6, 6, 6, 6, 6, 6, 6};
  (void) quality;
  if (size_hint < (1 << 20))
  {
    return 0;
  }
  else
  {
    helper_ShouldUseComplexStaticContextMap_1(&start_pos, input, length, mask, num_literal_contexts, literal_context_map, kStaticContextMapComplexUTF8);
  }
}


----------------------------
static void ChooseContextMap(int quality, uint32_t *bigram_histo, size_t *num_literal_contexts, const uint32_t **literal_context_map)
{
  static const uint32_t kStaticContextMapContinuation[64] = {1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  static const uint32_t kStaticContextMapSimpleUTF8[64] = {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  uint32_t monogram_histo[3] = {0};
  uint32_t two_prefix_histo[6] = {0};
  size_t total;
  size_t i;
  size_t dummy;
  double entropy[4];
  for (i = 0; i < 9; i += 1)
  {
    monogram_histo[i % 3] += bigram_histo[i];
    two_prefix_histo[i % 6] += bigram_histo[i];
  }

  entropy[1] = ShannonEntropy(monogram_histo, 3, &dummy);
  entropy[2] = ShannonEntropy(two_prefix_histo, 3, &dummy) + ShannonEntropy(two_prefix_histo + 3, 3, &dummy);
  entropy[3] = 0;
  for (i = 0; i < 3; i += 1)
  {
    entropy[3] += ShannonEntropy(bigram_histo + (3 * i), 3, &dummy);
  }

  total = (monogram_histo[0] + monogram_histo[1]) + monogram_histo[2];
  ;
  entropy[0] = 1.0 / ((double) total);
  entropy[1] *= entropy[0];
  entropy[2] *= entropy[0];
  entropy[3] *= entropy[0];
  if (quality < 7)
  {
    entropy[3] = entropy[1] * 10;
  }
  if (((entropy[1] - entropy[2]) < 0.2) && ((entropy[1] - entropy[3]) < 0.2))
  {
    *num_literal_contexts = 1;
  }
  else
    if ((entropy[2] - entropy[3]) < 0.02)
  {
    *num_literal_contexts = 2;
    *literal_context_map = kStaticContextMapSimpleUTF8;
  }
  else
  {
    *num_literal_contexts = 3;
    *literal_context_map = kStaticContextMapContinuation;
  }
}


----------------------------
***/


static void ChooseDistanceParams(BrotliEncoderParams *params)
{
  uint32_t distance_postfix_bits = 0;
  uint32_t num_direct_distance_codes = 0;
  if (params->quality >= 4)
  {
    uint32_t ndirect_msb;
    if (params->mode == BROTLI_MODE_FONT)
    {
      distance_postfix_bits = 1;
      num_direct_distance_codes = 12;
    }
    else
    {
      distance_postfix_bits = params->dist.distance_postfix_bits;
      num_direct_distance_codes = params->dist.num_direct_distance_codes;
    }
    ndirect_msb = (num_direct_distance_codes >> distance_postfix_bits) & 0x0F;
    if (((distance_postfix_bits > 3) || (num_direct_distance_codes > 120)) || ((ndirect_msb << distance_postfix_bits) != num_direct_distance_codes))
    {
      distance_postfix_bits = 0;
      num_direct_distance_codes = 0;
    }
  }
  BrotliInitDistanceParams(params, distance_postfix_bits, num_direct_distance_codes);
}


/*** DEPENDENCIES:
void BrotliInitDistanceParams(BrotliEncoderParams *params, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceParams *dist_params = &params->dist;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  uint32_t max_distance;
  dist_params->distance_postfix_bits = npostfix;
  dist_params->num_direct_distance_codes = ndirect;
  alphabet_size_max = (16 + ndirect) + (24U << (npostfix + 1));
  alphabet_size_limit = alphabet_size_max;
  max_distance = (ndirect + (1U << ((24U + npostfix) + 2))) - (1U << (npostfix + 2));
  if (params->large_window)
  {
    BrotliDistanceCodeLimit limit = BrotliCalculateDistanceCodeLimit(0x7FFFFFFC, npostfix, ndirect);
    alphabet_size_max = (16 + ndirect) + (62U << (npostfix + 1));
    alphabet_size_limit = limit.max_alphabet_size;
    max_distance = limit.max_distance;
  }
  dist_params->alphabet_size_max = alphabet_size_max;
  dist_params->alphabet_size_limit = alphabet_size_limit;
  dist_params->max_distance = max_distance;
}


----------------------------
None
----------------------------
***/


static void BrotliEncoderInitParams(BrotliEncoderParams *params)
{
  params->mode = BROTLI_MODE_GENERIC;
  params->large_window = 0;
  params->quality = 11;
  params->lgwin = 22;
  params->lgblock = 0;
  params->stream_offset = 0;
  params->size_hint = 0;
  params->disable_literal_context_modeling = 0;
  BrotliInitEncoderDictionary(&params->dictionary);
  params->dist.distance_postfix_bits = 0;
  params->dist.num_direct_distance_codes = 0;
  params->dist.alphabet_size_max = (16 + 0) + (24U << (0 + 1));
  params->dist.alphabet_size_limit = params->dist.alphabet_size_max;
  params->dist.max_distance = 0x3FFFFFC;
}


/*** DEPENDENCIES:
void BrotliInitEncoderDictionary(BrotliEncoderDictionary *dict)
{
  dict->words = BrotliGetDictionary();
  dict->num_transforms = (uint32_t) BrotliGetTransforms()->num_transforms;
  dict->hash_table_words = kStaticDictionaryHashWords;
  dict->hash_table_lengths = kStaticDictionaryHashLengths;
  dict->buckets = kStaticDictionaryBuckets;
  dict->dict_words = kStaticDictionaryWords;
  dict->cutoffTransformsCount = kCutoffTransformsCount;
  dict->cutoffTransforms = kCutoffTransforms;
}


----------------------------
None
----------------------------
***/


static int UpdateLastProcessedPos(BrotliEncoderState *s)
{
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint32_t wrapped_input_pos = WrapPosition(s->input_pos_);
  s->last_processed_pos_ = s->input_pos_;
  return (!(!(wrapped_input_pos < wrapped_last_processed_pos))) ? (1) : (0);
}


/*** DEPENDENCIES:
static uint32_t WrapPosition(uint64_t position)
{
  uint32_t result = (uint32_t) position;
  uint64_t gb = position >> 30;
  if (gb > 2)
  {
    result = (result & ((1u << 30) - 1)) | ((((uint32_t) ((gb - 1) & 1)) + 1) << 30);
  }
  return result;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


static size_t WriteMetadataHeader(BrotliEncoderState *s, const size_t block_size, uint8_t *header)
{
  size_t storage_ix;
  storage_ix = s->last_bytes_bits_;
  header[0] = (uint8_t) s->last_bytes_;
  header[1] = (uint8_t) (s->last_bytes_ >> 8);
  s->last_bytes_ = 0;
  s->last_bytes_bits_ = 0;
  BrotliWriteBits(1, 0, &storage_ix, header);
  BrotliWriteBits(2, 3, &storage_ix, header);
  BrotliWriteBits(1, 0, &storage_ix, header);
  if (block_size == 0)
  {
    BrotliWriteBits(2, 0, &storage_ix, header);
  }
  else
  {
    uint32_t nbits = (block_size == 1) ? (0) : (Log2FloorNonZero(((uint32_t) block_size) - 1) + 1);
    uint32_t nbytes = (nbits + 7) / 8;
    BrotliWriteBits(2, nbytes, &storage_ix, header);
    BrotliWriteBits(8 * nbytes, block_size - 1, &storage_ix, header);
  }
  return (storage_ix + 7u) >> 3;
}


/*** DEPENDENCIES:
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
inline static uint32_t Log2FloorNonZero(size_t n)
{
  return 31u ^ ((uint32_t) __builtin_clz((uint32_t) n));
}


----------------------------
***/


static int InjectFlushOrPushOutput(BrotliEncoderState *s, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->last_bytes_bits_ != 0))
  {
    InjectBytePaddingBlock(s);
    return 1;
  }
  if ((s->available_out_ != 0) && ((*available_out) != 0))
  {
    size_t copy_output_size = brotli_min_size_t(s->available_out_, *available_out);
    memcpy(*next_out, s->next_out_, copy_output_size);
    *next_out += copy_output_size;
    *available_out -= copy_output_size;
    s->next_out_ += copy_output_size;
    s->available_out_ -= copy_output_size;
    s->total_out_ += copy_output_size;
    if (total_out)
    {
      *total_out = s->total_out_;
    }
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static void InjectBytePaddingBlock(BrotliEncoderState *s)
{
  uint32_t seal = s->last_bytes_;
  size_t seal_bits = s->last_bytes_bits_;
  uint8_t *destination;
  unsigned int destination_idx = 0;
  s->last_bytes_ = 0;
  s->last_bytes_bits_ = 0;
  seal |= 0x6u << seal_bits;
  seal_bits += 6;
  if (s->next_out_)
  {
    destination_idx = s->next_out_ + s->available_out_;
  }
  else
  {
    destination_idx = s->tiny_buf_.u8;
    s->next_out_ = &destination[destination_idx];
  }
  destination[0 + destination_idx] = (uint8_t) seal;
  if (seal_bits > 8)
  {
    destination[1 + destination_idx] = (uint8_t) (seal >> 8);
  }
  if (seal_bits > 16)
  {
    destination[2 + destination_idx] = (uint8_t) (seal >> 16);
  }
  s->available_out_ += (seal_bits + 7) >> 3;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


static ContextType ChooseContextMode(const BrotliEncoderParams *params, const uint8_t *data, const size_t pos, const size_t mask, const size_t length)
{
  if ((params->quality >= 10) && (!BrotliIsMostlyUTF8(data, pos, mask, length, kMinUTF8Ratio)))
  {
    return CONTEXT_SIGNED;
  }
  return CONTEXT_UTF8;
}


/*** DEPENDENCIES:
static const double kMinUTF8Ratio = 0.75
----------------------------
int BrotliIsMostlyUTF8(const uint8_t *data, const size_t pos, const size_t mask, const size_t length, const double min_fraction)
{
  size_t size_utf8 = 0;
  size_t i = 0;
  while (i < length)
  {
    int symbol;
    size_t bytes_read = BrotliParseAsUTF8(&symbol, &data[(pos + i) & mask], length - i);
    i += bytes_read;
    if (symbol < 0x110000)
    {
      size_utf8 += bytes_read;
    }
  }

  return (!(!(((double) size_utf8) > (min_fraction * ((double) length))))) ? (1) : (0);
}


----------------------------
None
----------------------------
***/


static void ExtendLastCommand(BrotliEncoderState *s, uint32_t *bytes, uint32_t *wrapped_last_processed_pos)
{
  Command *last_command = &s->commands_[s->num_commands_ - 1];
  const uint8_t *data = s->ringbuffer_.buffer_;
  const uint32_t mask = s->ringbuffer_.mask_;
  uint64_t max_backward_distance = (((uint64_t) 1) << s->params.lgwin) - 16;
  uint64_t last_copy_len = last_command->copy_len_ & 0x1FFFFFF;
  uint64_t last_processed_pos = s->last_processed_pos_ - last_copy_len;
  uint64_t max_distance = (last_processed_pos < max_backward_distance) ? (last_processed_pos) : (max_backward_distance);
  uint64_t cmd_dist = (uint64_t) s->dist_cache_[0];
  uint32_t distance_code = CommandRestoreDistanceCode(last_command, &s->params.dist);
  if ((distance_code < 16) || ((distance_code - (16 - 1)) == cmd_dist))
  {
    if (cmd_dist <= max_distance)
    {
      while (((*bytes) != 0) && (data[(*wrapped_last_processed_pos) & mask] == data[((*wrapped_last_processed_pos) - cmd_dist) & mask]))
      {
        last_command->copy_len_ += 1;
        *bytes -= 1;
        *wrapped_last_processed_pos += 1;
      }

    }
    else
    {
    }
    GetLengthCode(last_command->insert_len_, (size_t) (((int) (last_command->copy_len_ & 0x1FFFFFF)) + ((int) (last_command->copy_len_ >> 25))), (!(!((last_command->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &last_command->cmd_prefix_);
  }
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
inline static void GetLengthCode(size_t insertlen, size_t copylen, int use_last_distance, uint16_t *code)
{
  uint16_t inscode = GetInsertLengthCode(insertlen);
  uint16_t copycode = GetCopyLengthCode(copylen);
  *code = CombineLengthCodes(inscode, copycode, use_last_distance);
}


----------------------------
inline static uint32_t CommandRestoreDistanceCode(const Command *self, const BrotliDistanceParams *dist)
{
  if ((self->dist_prefix_ & 0x3FFu) < (16 + dist->num_direct_distance_codes))
  {
    return self->dist_prefix_ & 0x3FFu;
  }
  else
  {
    uint32_t dcode = self->dist_prefix_ & 0x3FFu;
    uint32_t nbits = self->dist_prefix_ >> 10;
    uint32_t extra = self->dist_extra_;
    uint32_t postfix_mask = (1U << dist->distance_postfix_bits) - 1U;
    uint32_t hcode = ((dcode - dist->num_direct_distance_codes) - 16) >> dist->distance_postfix_bits;
    uint32_t lcode = ((dcode - dist->num_direct_distance_codes) - 16) & postfix_mask;
    uint32_t offset = ((2U + (hcode & 1U)) << nbits) - 4U;
    return ((((offset + extra) << dist->distance_postfix_bits) + lcode) + dist->num_direct_distance_codes) + 16;
  }
}


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
***/


static uint8_t *GetBrotliStorage(BrotliEncoderState *s, size_t size)
{
  MemoryManager *m = &s->memory_manager_;
  if (s->storage_size_ < size)
  {
    {
      BrotliFree(m, s->storage_);
      s->storage_ = 0;
    }
    ;
    s->storage_ = (size > 0) ? ((uint8_t *) BrotliAllocate(m, size * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return 0;
    }
    s->storage_size_ = size;
  }
  return s->storage_;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


void helper_WriteMetaBlockInternal_1(MemoryManager * const m, const uint8_t * const data, const size_t mask, const size_t bytes, const int is_last, ContextType literal_context_mode, const BrotliEncoderParams * const params, const uint8_t prev_byte, const uint8_t prev_byte2, const size_t num_commands, Command * const commands, size_t * const storage_ix, uint8_t * const storage, const uint32_t wrapped_last_flush_pos, ContextLut literal_context_lut, BrotliEncoderParams block_params)
{
  MetaBlockSplit mb;
  InitMetaBlockSplit(&mb);
  if (params->quality < 10)
  {
    size_t num_literal_contexts = 1;
    const uint32_t *literal_context_map = 0;
    if (!params->disable_literal_context_modeling)
    {
      DecideOverLiteralContextModeling(data, wrapped_last_flush_pos, bytes, mask, params->quality, params->size_hint, &num_literal_contexts, &literal_context_map);
    }
    BrotliBuildMetaBlockGreedy(m, data, wrapped_last_flush_pos, mask, prev_byte, prev_byte2, literal_context_lut, num_literal_contexts, literal_context_map, commands, num_commands, &mb);
    if (!(!0))
    {
      return;
    }
  }
  else
  {
    BrotliBuildMetaBlock(m, data, wrapped_last_flush_pos, mask, &block_params, prev_byte, prev_byte2, commands, num_commands, literal_context_mode, &mb);
    if (!(!0))
    {
      return;
    }
  }
  if (params->quality >= 4)
  {
    BrotliOptimizeHistograms(block_params.dist.alphabet_size_limit, &mb);
  }
  BrotliStoreMetaBlock(m, data, wrapped_last_flush_pos, bytes, mask, prev_byte, prev_byte2, is_last, &block_params, literal_context_mode, commands, num_commands, &mb, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  DestroyMetaBlockSplit(m, &mb);
}


/*** DEPENDENCIES:
inline static void InitMetaBlockSplit(MetaBlockSplit *mb)
{
  BrotliInitBlockSplit(&mb->literal_split);
  BrotliInitBlockSplit(&mb->command_split);
  BrotliInitBlockSplit(&mb->distance_split);
  mb->literal_context_map = 0;
  mb->literal_context_map_size = 0;
  mb->distance_context_map = 0;
  mb->distance_context_map_size = 0;
  mb->literal_histograms = 0;
  mb->literal_histograms_size = 0;
  mb->command_histograms = 0;
  mb->command_histograms_size = 0;
  mb->distance_histograms = 0;
  mb->distance_histograms_size = 0;
}


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
static void DecideOverLiteralContextModeling(const uint8_t *input, size_t start_pos, size_t length, size_t mask, int quality, size_t size_hint, size_t *num_literal_contexts, const uint32_t **literal_context_map)
{
  if ((quality < 5) || (length < 64))
  {
    return;
  }
  else
    if (ShouldUseComplexStaticContextMap(input, start_pos, length, mask, quality, size_hint, num_literal_contexts, literal_context_map))
  {
  }
  else
  {
    const size_t end_pos = start_pos + length;
    uint32_t bigram_prefix_histo[9] = {0};
    for (; (start_pos + 64) <= end_pos; start_pos += 4096)
    {
      static const int lut[4] = {0, 0, 1, 2};
      const size_t stride_end_pos = start_pos + 64;
      int prev = lut[input[start_pos & mask] >> 6] * 3;
      size_t pos;
      for (pos = start_pos + 1; pos < stride_end_pos; pos += 1)
      {
        const uint8_t literal = input[pos & mask];
        bigram_prefix_histo[prev + lut[literal >> 6]] += 1;
        prev = lut[literal >> 6] * 3;
      }

    }

    ChooseContextMap(quality, &bigram_prefix_histo[0], num_literal_contexts, literal_context_map);
  }
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
inline static void DestroyMetaBlockSplit(MemoryManager *m, MetaBlockSplit *mb)
{
  BrotliDestroyBlockSplit(m, &mb->literal_split);
  BrotliDestroyBlockSplit(m, &mb->command_split);
  BrotliDestroyBlockSplit(m, &mb->distance_split);
  {
    BrotliFree(m, mb->literal_context_map);
    mb->literal_context_map = 0;
  }
  ;
  {
    BrotliFree(m, mb->distance_context_map);
    mb->distance_context_map = 0;
  }
  ;
  {
    BrotliFree(m, mb->literal_histograms);
    mb->literal_histograms = 0;
  }
  ;
  {
    BrotliFree(m, mb->command_histograms);
    mb->command_histograms = 0;
  }
  ;
  {
    BrotliFree(m, mb->distance_histograms);
    mb->distance_histograms = 0;
  }
  ;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliStoreMetaBlock(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, int is_last, const BrotliEncoderParams *params, ContextType literal_context_mode, const Command *commands, size_t n_commands, const MetaBlockSplit *mb, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  uint32_t num_effective_distance_symbols = params->dist.alphabet_size_limit;
  HuffmanTree *tree;
  unsigned int tree_idx = 0;
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  BlockEncoder literal_enc;
  BlockEncoder command_enc;
  BlockEncoder distance_enc;
  const BrotliDistanceParams *dist = &params->dist;
  ;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  tree_idx = (((2 * 704) + 1) > 0) ? ((HuffmanTree *) BrotliAllocate(m, ((2 * 704) + 1) * (sizeof(HuffmanTree)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitBlockEncoder(&literal_enc, 256, mb->literal_split.num_types, mb->literal_split.types, mb->literal_split.lengths, mb->literal_split.num_blocks);
  InitBlockEncoder(&command_enc, 704, mb->command_split.num_types, mb->command_split.types, mb->command_split.lengths, mb->command_split.num_blocks);
  InitBlockEncoder(&distance_enc, num_effective_distance_symbols, mb->distance_split.num_types, mb->distance_split.types, mb->distance_split.lengths, mb->distance_split.num_blocks);
  BuildAndStoreBlockSwitchEntropyCodes(&literal_enc, tree, storage_ix, storage);
  BuildAndStoreBlockSwitchEntropyCodes(&command_enc, tree, storage_ix, storage);
  BuildAndStoreBlockSwitchEntropyCodes(&distance_enc, tree, storage_ix, storage);
  BrotliWriteBits(2, dist->distance_postfix_bits, storage_ix, storage);
  BrotliWriteBits(4, dist->num_direct_distance_codes >> dist->distance_postfix_bits, storage_ix, storage);
  for (i = 0; i < mb->literal_split.num_types; i += 1)
  {
    BrotliWriteBits(2, literal_context_mode, storage_ix, storage);
  }

  if (mb->literal_context_map_size == 0)
  {
    StoreTrivialContextMap(mb->literal_histograms_size, 6, tree, storage_ix, storage);
  }
  else
  {
    EncodeContextMap(m, mb->literal_context_map, mb->literal_context_map_size, mb->literal_histograms_size, tree, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  if (mb->distance_context_map_size == 0)
  {
    StoreTrivialContextMap(mb->distance_histograms_size, 2, tree, storage_ix, storage);
  }
  else
  {
    EncodeContextMap(m, mb->distance_context_map, mb->distance_context_map_size, mb->distance_histograms_size, tree, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  BuildAndStoreEntropyCodesLiteral(m, &literal_enc, mb->literal_histograms, mb->literal_histograms_size, 256, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreEntropyCodesCommand(m, &command_enc, mb->command_histograms, mb->command_histograms_size, 704, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreEntropyCodesDistance(m, &distance_enc, mb->distance_histograms, mb->distance_histograms_size, num_distance_symbols, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, tree);
    tree_idx = 0;
  }
  ;
  for (i = 0; i < n_commands; i += 1)
  {
    helper_BrotliStoreMetaBlock_1(&prev_byte, &prev_byte2, &pos, input, mask, commands, mb, storage_ix, storage, i, literal_context_lut, literal_enc, command_enc, distance_enc);
  }

  CleanupBlockEncoder(m, &distance_enc);
  CleanupBlockEncoder(m, &command_enc);
  CleanupBlockEncoder(m, &literal_enc);
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


----------------------------
void BrotliBuildMetaBlockGreedy(MemoryManager *m, const uint8_t *ringbuffer, size_t pos, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, ContextLut literal_context_lut, size_t num_contexts, const uint32_t *static_context_map, const Command *commands, size_t n_commands, MetaBlockSplit *mb)
{
  if (num_contexts == 1)
  {
    BrotliBuildMetaBlockGreedyInternal(m, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_lut, 1, 0, commands, n_commands, mb);
  }
  else
  {
    BrotliBuildMetaBlockGreedyInternal(m, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_lut, num_contexts, static_context_map, commands, n_commands, mb);
  }
}


----------------------------
void BrotliBuildMetaBlock(MemoryManager *m, const uint8_t *ringbuffer, const size_t pos, const size_t mask, BrotliEncoderParams *params, uint8_t prev_byte, uint8_t prev_byte2, Command *cmds, size_t num_commands, ContextType literal_context_mode, MetaBlockSplit *mb)
{
  static const size_t kMaxNumberOfHistograms = 256;
  HistogramDistance *distance_histograms;
  unsigned int distance_histograms_idx = 0;
  HistogramLiteral *literal_histograms;
  unsigned int literal_histograms_idx = 0;
  ContextType *literal_context_modes = 0;
  unsigned int literal_context_modes_idx = 0;
  size_t literal_histograms_size;
  size_t distance_histograms_size;
  size_t i;
  size_t literal_context_multiplier = 1;
  uint32_t npostfix;
  uint32_t ndirect_msb = 0;
  int check_orig = 1;
  double best_dist_cost = 1e99;
  BrotliEncoderParams orig_params = *params;
  BrotliEncoderParams new_params = *params;
  for (npostfix = 0; npostfix <= 3; npostfix += 1)
  {
    helper_BrotliBuildMetaBlock_1(&ndirect_msb, &check_orig, &best_dist_cost, params, cmds, num_commands, npostfix, orig_params, new_params);
  }

  if (check_orig)
  {
    double dist_cost;
    ComputeDistanceCost(cmds, num_commands, &orig_params.dist, &orig_params.dist, &dist_cost);
    if (dist_cost < best_dist_cost)
    {
      params->dist = orig_params.dist;
    }
  }
  RecomputeDistancePrefixes(cmds, num_commands, &orig_params.dist, &params->dist);
  BrotliSplitBlock(m, cmds, num_commands, ringbuffer, pos, mask, params, &mb->literal_split, &mb->command_split, &mb->distance_split);
  if (!(!0))
  {
    return;
  }
  if (!params->disable_literal_context_modeling)
  {
    literal_context_multiplier = 1 << 6;
    literal_context_modes_idx = (mb->literal_split.num_types > 0) ? ((ContextType *) BrotliAllocate(m, mb->literal_split.num_types * (sizeof(ContextType)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
    for (i = 0; i < mb->literal_split.num_types; i += 1)
    {
      literal_context_modes[i + literal_context_modes_idx] = literal_context_mode;
    }

  }
  literal_histograms_size = mb->literal_split.num_types * literal_context_multiplier;
  literal_histograms_idx = (literal_histograms_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, literal_histograms_size * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsLiteral(literal_histograms, literal_histograms_size);
  distance_histograms_size = mb->distance_split.num_types << 2;
  distance_histograms_idx = (distance_histograms_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, distance_histograms_size * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsDistance(distance_histograms, distance_histograms_size);
  ;
  mb->command_histograms_size = mb->command_split.num_types;
  mb->command_histograms = (mb->command_histograms_size > 0) ? ((HistogramCommand *) BrotliAllocate(m, mb->command_histograms_size * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsCommand(mb->command_histograms, mb->command_histograms_size);
  BrotliBuildHistogramsWithContext(cmds, num_commands, &mb->literal_split, &mb->command_split, &mb->distance_split, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_modes, literal_histograms, mb->command_histograms, distance_histograms);
  {
    BrotliFree(m, literal_context_modes);
    literal_context_modes_idx = 0;
  }
  ;
  ;
  mb->literal_context_map_size = mb->literal_split.num_types << 6;
  mb->literal_context_map = (mb->literal_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->literal_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ;
  mb->literal_histograms_size = mb->literal_context_map_size;
  mb->literal_histograms = (mb->literal_histograms_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, mb->literal_histograms_size * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliClusterHistogramsLiteral(m, literal_histograms, literal_histograms_size, kMaxNumberOfHistograms, mb->literal_histograms, &mb->literal_histograms_size, mb->literal_context_map);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, literal_histograms);
    literal_histograms_idx = 0;
  }
  ;
  if (params->disable_literal_context_modeling)
  {
    for (i = mb->literal_split.num_types; i != 0;)
    {
      size_t j = 0;
      i -= 1;
      for (; j < (1 << 6); j += 1)
      {
        mb->literal_context_map[(i << 6) + j] = mb->literal_context_map[i];
      }

    }

  }
  ;
  mb->distance_context_map_size = mb->distance_split.num_types << 2;
  mb->distance_context_map = (mb->distance_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->distance_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ;
  mb->distance_histograms_size = mb->distance_context_map_size;
  mb->distance_histograms = (mb->distance_histograms_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, mb->distance_histograms_size * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliClusterHistogramsDistance(m, distance_histograms, mb->distance_context_map_size, kMaxNumberOfHistograms, mb->distance_histograms, &mb->distance_histograms_size, mb->distance_context_map);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, distance_histograms);
    distance_histograms_idx = 0;
  }
  ;
}


----------------------------
void BrotliOptimizeHistograms(uint32_t num_distance_codes, MetaBlockSplit *mb)
{
  uint8_t good_for_rle[704];
  size_t i;
  for (i = 0; i < mb->literal_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(256, mb->literal_histograms[i].data_, good_for_rle);
  }

  for (i = 0; i < mb->command_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(704, mb->command_histograms[i].data_, good_for_rle);
  }

  for (i = 0; i < mb->distance_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(num_distance_codes, mb->distance_histograms[i].data_, good_for_rle);
  }

}


----------------------------
None
----------------------------
***/


static void WriteMetaBlockInternal(MemoryManager *m, const uint8_t *data, const size_t mask, const uint64_t last_flush_pos, const size_t bytes, const int is_last, ContextType literal_context_mode, const BrotliEncoderParams *params, const uint8_t prev_byte, const uint8_t prev_byte2, const size_t num_literals, const size_t num_commands, Command *commands, const int *saved_dist_cache, int *dist_cache, size_t *storage_ix, uint8_t *storage)
{
  const uint32_t wrapped_last_flush_pos = WrapPosition(last_flush_pos);
  uint16_t last_bytes;
  uint8_t last_bytes_bits;
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  BrotliEncoderParams block_params = *params;
  if (bytes == 0)
  {
    BrotliWriteBits(2, 3, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
    return;
  }
  if (!ShouldCompress(data, mask, last_flush_pos, bytes, num_literals, num_commands))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    BrotliStoreUncompressedMetaBlock(is_last, data, wrapped_last_flush_pos, mask, bytes, storage_ix, storage);
    return;
  }
  ;
  last_bytes = (uint16_t) ((storage[1] << 8) | storage[0]);
  last_bytes_bits = (uint8_t) (*storage_ix);
  if (params->quality <= 2)
  {
    BrotliStoreMetaBlockFast(m, data, wrapped_last_flush_pos, bytes, mask, is_last, params, commands, num_commands, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  else
    if (params->quality < 4)
  {
    BrotliStoreMetaBlockTrivial(m, data, wrapped_last_flush_pos, bytes, mask, is_last, params, commands, num_commands, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  else
  {
    helper_WriteMetaBlockInternal_1(m, data, mask, bytes, is_last, literal_context_mode, params, prev_byte, prev_byte2, num_commands, commands, storage_ix, storage, wrapped_last_flush_pos, literal_context_lut, block_params);
  }
  if ((bytes + 4) < ((*storage_ix) >> 3))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    storage[0] = (uint8_t) last_bytes;
    storage[1] = (uint8_t) (last_bytes >> 8);
    *storage_ix = last_bytes_bits;
    BrotliStoreUncompressedMetaBlock(is_last, data, wrapped_last_flush_pos, mask, bytes, storage_ix, storage);
  }
}


/*** DEPENDENCIES:
void BrotliStoreMetaBlockFast(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, int is_last, const BrotliEncoderParams *params, const Command *commands, size_t n_commands, size_t *storage_ix, uint8_t *storage)
{
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  uint32_t distance_alphabet_bits = Log2FloorNonZero(num_distance_symbols - 1) + 1;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  BrotliWriteBits(13, 0, storage_ix, storage);
  if (n_commands <= 128)
  {
    helper_BrotliStoreMetaBlockFast_1(&mask, m, input, start_pos, commands, n_commands, storage_ix, storage);
  }
  else
  {
    helper_BrotliStoreMetaBlockFast_2(m, input, start_pos, mask, commands, n_commands, storage_ix, storage, distance_alphabet_bits);
  }
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


----------------------------
static int ShouldCompress(const uint8_t *input, size_t input_size, size_t num_literals)
{
  double corpus_size = (double) input_size;
  if (((double) num_literals) < (0.98 * corpus_size))
  {
    return 1;
  }
  else
  {
    uint32_t literal_histo[256] = {0};
    const double max_total_bit_cost = ((corpus_size * 8) * 0.98) / 43;
    size_t i;
    for (i = 0; i < input_size; i += 43)
    {
      literal_histo[input[i]] += 1;
    }

    return (!(!(BitsEntropy(literal_histo, 256) < max_total_bit_cost))) ? (1) : (0);
  }
}


----------------------------
void BrotliStoreMetaBlockTrivial(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, int is_last, const BrotliEncoderParams *params, const Command *commands, size_t n_commands, size_t *storage_ix, uint8_t *storage)
{
  HistogramLiteral lit_histo;
  HistogramCommand cmd_histo;
  HistogramDistance dist_histo;
  uint8_t lit_depth[256];
  uint16_t lit_bits[256];
  uint8_t cmd_depth[704];
  uint16_t cmd_bits[704];
  uint8_t dist_depth[(16 + 0) + (62U << (0 + 1))];
  uint16_t dist_bits[(16 + 0) + (62U << (0 + 1))];
  HuffmanTree *tree;
  unsigned int tree_idx = 0;
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  HistogramClearLiteral(&lit_histo);
  HistogramClearCommand(&cmd_histo);
  HistogramClearDistance(&dist_histo);
  BuildHistograms(input, start_pos, mask, commands, n_commands, &lit_histo, &cmd_histo, &dist_histo);
  BrotliWriteBits(13, 0, storage_ix, storage);
  tree_idx = (((2 * 704) + 1) > 0) ? ((HuffmanTree *) BrotliAllocate(m, ((2 * 704) + 1) * (sizeof(HuffmanTree)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BuildAndStoreHuffmanTree(lit_histo.data_, 256, 256, tree, lit_depth, lit_bits, storage_ix, storage);
  BuildAndStoreHuffmanTree(cmd_histo.data_, 704, 704, tree, cmd_depth, cmd_bits, storage_ix, storage);
  BuildAndStoreHuffmanTree(dist_histo.data_, (16 + 0) + (62U << (0 + 1)), num_distance_symbols, tree, dist_depth, dist_bits, storage_ix, storage);
  {
    BrotliFree(m, tree);
    tree_idx = 0;
  }
  ;
  StoreDataWithHuffmanCodes(input, start_pos, mask, commands, n_commands, lit_depth, lit_bits, cmd_depth, cmd_bits, dist_depth, dist_bits, storage_ix, storage);
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


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
void BrotliStoreUncompressedMetaBlock(int is_final_block, const uint8_t * restrict input, size_t position, size_t mask, size_t len, size_t * restrict storage_ix, uint8_t * restrict storage)
{
  size_t masked_pos = position & mask;
  BrotliStoreUncompressedMetaBlockHeader(len, storage_ix, storage);
  JumpToByteBoundary(storage_ix, storage);
  if ((masked_pos + len) > (mask + 1))
  {
    size_t len1 = (mask + 1) - masked_pos;
    memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len1);
    *storage_ix += len1 << 3;
    len -= len1;
    masked_pos = 0;
  }
  memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len);
  *storage_ix += len << 3;
  BrotliWriteBitsPrepareStorage(*storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    JumpToByteBoundary(storage_ix, storage);
  }
}


----------------------------
void helper_WriteMetaBlockInternal_1(MemoryManager * const m, const uint8_t * const data, const size_t mask, const size_t bytes, const int is_last, ContextType literal_context_mode, const BrotliEncoderParams * const params, const uint8_t prev_byte, const uint8_t prev_byte2, const size_t num_commands, Command * const commands, size_t * const storage_ix, uint8_t * const storage, const uint32_t wrapped_last_flush_pos, ContextLut literal_context_lut, BrotliEncoderParams block_params)
{
  MetaBlockSplit mb;
  InitMetaBlockSplit(&mb);
  if (params->quality < 10)
  {
    size_t num_literal_contexts = 1;
    const uint32_t *literal_context_map = 0;
    if (!params->disable_literal_context_modeling)
    {
      DecideOverLiteralContextModeling(data, wrapped_last_flush_pos, bytes, mask, params->quality, params->size_hint, &num_literal_contexts, &literal_context_map);
    }
    BrotliBuildMetaBlockGreedy(m, data, wrapped_last_flush_pos, mask, prev_byte, prev_byte2, literal_context_lut, num_literal_contexts, literal_context_map, commands, num_commands, &mb);
    if (!(!0))
    {
      return;
    }
  }
  else
  {
    BrotliBuildMetaBlock(m, data, wrapped_last_flush_pos, mask, &block_params, prev_byte, prev_byte2, commands, num_commands, literal_context_mode, &mb);
    if (!(!0))
    {
      return;
    }
  }
  if (params->quality >= 4)
  {
    BrotliOptimizeHistograms(block_params.dist.alphabet_size_limit, &mb);
  }
  BrotliStoreMetaBlock(m, data, wrapped_last_flush_pos, bytes, mask, prev_byte, prev_byte2, is_last, &block_params, literal_context_mode, commands, num_commands, &mb, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  DestroyMetaBlockSplit(m, &mb);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
static uint32_t WrapPosition(uint64_t position)
{
  uint32_t result = (uint32_t) position;
  uint64_t gb = position >> 30;
  if (gb > 2)
  {
    result = (result & ((1u << 30) - 1)) | ((((uint32_t) ((gb - 1) & 1)) + 1) << 30);
  }
  return result;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
None
----------------------------
***/


int helper_EncodeData_3(BrotliEncoderState * const s, const int is_last, size_t * const out_size, uint8_t ** const output, uint8_t * const data, unsigned int data_idx, uint32_t mask, MemoryManager * const m, ContextType literal_context_mode)
{
  const uint32_t metablock_size = (uint32_t) (s->input_pos_ - s->last_flush_pos_);
  uint8_t *storage = GetBrotliStorage(s, (2 * metablock_size) + 503);
  unsigned int storage_idx = 0;
  size_t storage_ix = s->last_bytes_bits_;
  if (!(!0))
  {
    return 0;
  }
  storage[0 + storage_idx] = (uint8_t) s->last_bytes_;
  storage[1 + storage_idx] = (uint8_t) (s->last_bytes_ >> 8);
  WriteMetaBlockInternal(m, data, mask, s->last_flush_pos_, metablock_size, is_last, literal_context_mode, &s->params, s->prev_byte_, s->prev_byte2_, s->num_literals_, s->num_commands_, s->commands_, s->saved_dist_cache_, s->dist_cache_, &storage_ix, storage);
  if (!(!0))
  {
    return 0;
  }
  s->last_bytes_ = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  s->last_bytes_bits_ = storage_ix & 7u;
  s->last_flush_pos_ = s->input_pos_;
  if (UpdateLastProcessedPos(s))
  {
    HasherReset(&s->hasher_);
  }
  if (s->last_flush_pos_ > 0)
  {
    s->prev_byte_ = data[((((uint32_t) s->last_flush_pos_) - 1) & mask) + data_idx];
  }
  if (s->last_flush_pos_ > 1)
  {
    s->prev_byte2_ = data[(((uint32_t) (s->last_flush_pos_ - 2)) & mask) + data_idx];
  }
  s->num_commands_ = 0;
  s->num_literals_ = 0;
  memcpy(s->saved_dist_cache_, s->dist_cache_, sizeof(s->saved_dist_cache_));
  *output = &storage[0 + storage_idx];
  *out_size = storage_ix >> 3;
  return 1;
}


/*** DEPENDENCIES:
static uint8_t *GetBrotliStorage(BrotliEncoderState *s, size_t size)
{
  MemoryManager *m = &s->memory_manager_;
  if (s->storage_size_ < size)
  {
    {
      BrotliFree(m, s->storage_);
      s->storage_ = 0;
    }
    ;
    s->storage_ = (size > 0) ? ((uint8_t *) BrotliAllocate(m, size * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return 0;
    }
    s->storage_size_ = size;
  }
  return s->storage_;
}


----------------------------
inline static void HasherReset(Hasher *hasher)
{
  hasher->common.is_prepared_ = 0;
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
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int UpdateLastProcessedPos(BrotliEncoderState *s)
{
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint32_t wrapped_input_pos = WrapPosition(s->input_pos_);
  s->last_processed_pos_ = s->input_pos_;
  return (!(!(wrapped_input_pos < wrapped_last_processed_pos))) ? (1) : (0);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void WriteMetaBlockInternal(MemoryManager *m, const uint8_t *data, const size_t mask, const uint64_t last_flush_pos, const size_t bytes, const int is_last, ContextType literal_context_mode, const BrotliEncoderParams *params, const uint8_t prev_byte, const uint8_t prev_byte2, const size_t num_literals, const size_t num_commands, Command *commands, const int *saved_dist_cache, int *dist_cache, size_t *storage_ix, uint8_t *storage)
{
  const uint32_t wrapped_last_flush_pos = WrapPosition(last_flush_pos);
  uint16_t last_bytes;
  uint8_t last_bytes_bits;
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  BrotliEncoderParams block_params = *params;
  if (bytes == 0)
  {
    BrotliWriteBits(2, 3, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
    return;
  }
  if (!ShouldCompress(data, mask, last_flush_pos, bytes, num_literals, num_commands))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    BrotliStoreUncompressedMetaBlock(is_last, data, wrapped_last_flush_pos, mask, bytes, storage_ix, storage);
    return;
  }
  ;
  last_bytes = (uint16_t) ((storage[1] << 8) | storage[0]);
  last_bytes_bits = (uint8_t) (*storage_ix);
  if (params->quality <= 2)
  {
    BrotliStoreMetaBlockFast(m, data, wrapped_last_flush_pos, bytes, mask, is_last, params, commands, num_commands, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  else
    if (params->quality < 4)
  {
    BrotliStoreMetaBlockTrivial(m, data, wrapped_last_flush_pos, bytes, mask, is_last, params, commands, num_commands, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  else
  {
    helper_WriteMetaBlockInternal_1(m, data, mask, bytes, is_last, literal_context_mode, params, prev_byte, prev_byte2, num_commands, commands, storage_ix, storage, wrapped_last_flush_pos, literal_context_lut, block_params);
  }
  if ((bytes + 4) < ((*storage_ix) >> 3))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    storage[0] = (uint8_t) last_bytes;
    storage[1] = (uint8_t) (last_bytes >> 8);
    *storage_ix = last_bytes_bits;
    BrotliStoreUncompressedMetaBlock(is_last, data, wrapped_last_flush_pos, mask, bytes, storage_ix, storage);
  }
}


----------------------------
***/


int helper_EncodeData_1(BrotliEncoderState * const s, const int is_last, const int force_flush, size_t * const out_size)
{
  const size_t max_length = MaxMetablockSize(&s->params);
  const size_t max_literals = max_length / 8;
  const size_t max_commands = max_length / 8;
  const size_t processed_bytes = (size_t) (s->input_pos_ - s->last_flush_pos_);
  const int next_input_fits_metablock = (!(!((processed_bytes + InputBlockSize(s)) <= max_length))) ? (1) : (0);
  const int should_flush = (!(!((s->params.quality < 4) && ((s->num_literals_ + s->num_commands_) >= 0x2FFF)))) ? (1) : (0);
  if ((((((!is_last) && (!force_flush)) && (!should_flush)) && next_input_fits_metablock) && (s->num_literals_ < max_literals)) && (s->num_commands_ < max_commands))
  {
    if (UpdateLastProcessedPos(s))
    {
      HasherReset(&s->hasher_);
    }
    *out_size = 0;
    return 1;
  }
}


/*** DEPENDENCIES:
inline static size_t MaxMetablockSize(const BrotliEncoderParams *params)
{
  int bits = brotli_min_int(ComputeRbBits(params), 24);
  return ((size_t) 1) << bits;
}


----------------------------
static size_t InputBlockSize(BrotliEncoderState *s)
{
  return ((size_t) 1) << s->params.lgblock;
}


----------------------------
inline static void HasherReset(Hasher *hasher)
{
  hasher->common.is_prepared_ = 0;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int UpdateLastProcessedPos(BrotliEncoderState *s)
{
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint32_t wrapped_input_pos = WrapPosition(s->input_pos_);
  s->last_processed_pos_ = s->input_pos_;
  return (!(!(wrapped_input_pos < wrapped_last_processed_pos))) ? (1) : (0);
}


----------------------------
***/


int helper_EncodeData_2(BrotliEncoderState * const s, uint32_t bytes, MemoryManager * const m)
{
  size_t newsize = (s->num_commands_ + (bytes / 2)) + 1;
  if (newsize > s->cmd_alloc_size_)
  {
    Command *new_commands;
    unsigned int new_commands_idx = 0;
    newsize += (bytes / 4) + 16;
    s->cmd_alloc_size_ = newsize;
    new_commands_idx = (newsize > 0) ? ((Command *) BrotliAllocate(m, newsize * (sizeof(Command)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return 0;
    }
    if (s->commands_)
    {
      memcpy(new_commands, s->commands_, (sizeof(Command)) * s->num_commands_);
      {
        BrotliFree(m, s->commands_);
        s->commands_ = 0;
      }
      ;
    }
    s->commands_ = &new_commands[new_commands_idx];
  }
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


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
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


static int *GetHashTable(BrotliEncoderState *s, int quality, size_t input_size, size_t *table_size)
{
  MemoryManager *m = &s->memory_manager_;
  const size_t max_table_size = MaxHashTableSize(quality);
  size_t htsize = HashTableSize(max_table_size, input_size);
  int *table;
  unsigned int table_idx = 0;
  ;
  if (quality == 0)
  {
    if ((htsize & 0xAAAAA) == 0)
    {
      htsize <<= 1;
    }
  }
  if (htsize <= ((sizeof(s->small_table_)) / (sizeof(s->small_table_[0]))))
  {
    table_idx = s->small_table_;
  }
  else
  {
    if (htsize > s->large_table_size_)
    {
      s->large_table_size_ = htsize;
      {
        BrotliFree(m, s->large_table_);
        s->large_table_ = 0;
      }
      ;
      s->large_table_ = (htsize > 0) ? ((int *) BrotliAllocate(m, htsize * (sizeof(int)))) : (0);
      if ((!(!0)) || (!(!0)))
      {
        return 0;
      }
    }
    table_idx = s->large_table_;
  }
  *table_size = htsize;
  memset(table, 0, htsize * (sizeof(*(&table[table_idx]))));
  return table;
}


/*** DEPENDENCIES:
static size_t HashTableSize(size_t max_table_size, size_t input_size)
{
  size_t htsize = 256;
  while ((htsize < max_table_size) && (htsize < input_size))
  {
    htsize <<= 1;
  }

  return htsize;
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
inline static size_t MaxHashTableSize(int quality)
{
  return (quality == 0) ? (1 << 15) : (1 << 17);
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


int helper_EncodeData_4(BrotliEncoderState * const s, const int is_last, size_t * const out_size, uint8_t ** const output, const uint64_t delta, uint32_t bytes, uint32_t wrapped_last_processed_pos, uint8_t * const data, unsigned int data_idx, uint32_t mask, MemoryManager * const m)
{
  uint8_t *storage;
  unsigned int storage_idx = 0;
  size_t storage_ix = s->last_bytes_bits_;
  size_t table_size;
  int *table;
  unsigned int table_idx = 0;
  if ((delta == 0) && (!is_last))
  {
    *out_size = 0;
    return 1;
  }
  storage_idx = GetBrotliStorage(s, (2 * bytes) + 503);
  if (!(!0))
  {
    return 0;
  }
  storage[0 + storage_idx] = (uint8_t) s->last_bytes_;
  storage[1 + storage_idx] = (uint8_t) (s->last_bytes_ >> 8);
  table_idx = GetHashTable(s, s->params.quality, bytes, &table_size);
  if (!(!0))
  {
    return 0;
  }
  if (s->params.quality == 0)
  {
    BrotliCompressFragmentFast(m, &data[(wrapped_last_processed_pos & mask) + data_idx], bytes, is_last, table, table_size, s->cmd_depths_, s->cmd_bits_, &s->cmd_code_numbits_, s->cmd_code_, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCompressFragmentTwoPass(m, &data[(wrapped_last_processed_pos & mask) + data_idx], bytes, is_last, s->command_buf_, s->literal_buf_, table, table_size, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  s->last_bytes_ = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  s->last_bytes_bits_ = storage_ix & 7u;
  UpdateLastProcessedPos(s);
  *output = &storage[0 + storage_idx];
  *out_size = storage_ix >> 3;
  return 1;
}


/*** DEPENDENCIES:
static uint8_t *GetBrotliStorage(BrotliEncoderState *s, size_t size)
{
  MemoryManager *m = &s->memory_manager_;
  if (s->storage_size_ < size)
  {
    {
      BrotliFree(m, s->storage_);
      s->storage_ = 0;
    }
    ;
    s->storage_ = (size > 0) ? ((uint8_t *) BrotliAllocate(m, size * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return 0;
    }
    s->storage_size_ = size;
  }
  return s->storage_;
}


----------------------------
void BrotliCompressFragmentTwoPass(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_size, size_t *storage_ix, uint8_t *storage)
{
  const size_t initial_storage_ix = *storage_ix;
  const size_t table_bits = Log2FloorNonZero(table_size);
  switch (table_bits)
  {
    case 8:
    {
      BrotliCompressFragmentTwoPassImpl8(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 9:
    {
      BrotliCompressFragmentTwoPassImpl9(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 10:
    {
      BrotliCompressFragmentTwoPassImpl10(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 11:
    {
      BrotliCompressFragmentTwoPassImpl11(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 12:
    {
      BrotliCompressFragmentTwoPassImpl12(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 13:
    {
      BrotliCompressFragmentTwoPassImpl13(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 14:
    {
      BrotliCompressFragmentTwoPassImpl14(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 15:
    {
      BrotliCompressFragmentTwoPassImpl15(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 16:
    {
      BrotliCompressFragmentTwoPassImpl16(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 17:
    {
      BrotliCompressFragmentTwoPassImpl17(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    default:
    {
      ;
      break;
    }

  }

  if (((*storage_ix) - initial_storage_ix) > (31 + (input_size << 3)))
  {
    RewindBitPosition(initial_storage_ix, storage_ix, storage);
    EmitUncompressedMetaBlock(input, input_size, storage_ix, storage);
  }
  if (is_last)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
  }
}


----------------------------
static int *GetHashTable(BrotliEncoderState *s, int quality, size_t input_size, size_t *table_size)
{
  MemoryManager *m = &s->memory_manager_;
  const size_t max_table_size = MaxHashTableSize(quality);
  size_t htsize = HashTableSize(max_table_size, input_size);
  int *table;
  unsigned int table_idx = 0;
  ;
  if (quality == 0)
  {
    if ((htsize & 0xAAAAA) == 0)
    {
      htsize <<= 1;
    }
  }
  if (htsize <= ((sizeof(s->small_table_)) / (sizeof(s->small_table_[0]))))
  {
    table_idx = s->small_table_;
  }
  else
  {
    if (htsize > s->large_table_size_)
    {
      s->large_table_size_ = htsize;
      {
        BrotliFree(m, s->large_table_);
        s->large_table_ = 0;
      }
      ;
      s->large_table_ = (htsize > 0) ? ((int *) BrotliAllocate(m, htsize * (sizeof(int)))) : (0);
      if ((!(!0)) || (!(!0)))
      {
        return 0;
      }
    }
    table_idx = s->large_table_;
  }
  *table_size = htsize;
  memset(table, 0, htsize * (sizeof(*(&table[table_idx]))));
  return table;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int UpdateLastProcessedPos(BrotliEncoderState *s)
{
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint32_t wrapped_input_pos = WrapPosition(s->input_pos_);
  s->last_processed_pos_ = s->input_pos_;
  return (!(!(wrapped_input_pos < wrapped_last_processed_pos))) ? (1) : (0);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliCompressFragmentFast(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_size, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  const size_t initial_storage_ix = *storage_ix;
  const size_t table_bits = Log2FloorNonZero(table_size);
  if (input_size == 0)
  {
    ;
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
    return;
  }
  switch (table_bits)
  {
    case 9:
    {
      BrotliCompressFragmentFastImpl9(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 11:
    {
      BrotliCompressFragmentFastImpl11(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 13:
    {
      BrotliCompressFragmentFastImpl13(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 15:
    {
      BrotliCompressFragmentFastImpl15(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    default:
    {
      ;
      break;
    }

  }

  if (((*storage_ix) - initial_storage_ix) > (31 + (input_size << 3)))
  {
    EmitUncompressedMetaBlock(input, input + input_size, initial_storage_ix, storage_ix, storage);
  }
  if (is_last)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
  }
}


----------------------------
***/


static int EncodeData(BrotliEncoderState *s, const int is_last, const int force_flush, size_t *out_size, uint8_t **output)
{
  const uint64_t delta = UnprocessedInputSize(s);
  uint32_t bytes = (uint32_t) delta;
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint8_t *data;
  unsigned int data_idx = 0;
  uint32_t mask;
  MemoryManager *m = &s->memory_manager_;
  ContextType literal_context_mode;
  ContextLut literal_context_lut;
  data_idx = s->ringbuffer_.buffer_;
  mask = s->ringbuffer_.mask_;
  if (s->is_last_block_emitted_)
  {
    return 0;
  }
  if (is_last)
  {
    s->is_last_block_emitted_ = 1;
  }
  if (delta > InputBlockSize(s))
  {
    return 0;
  }
  if ((s->params.quality == 1) && (!s->command_buf_))
  {
    s->command_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint32_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint32_t)))) : (0);
    s->literal_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint8_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
  }
  if ((s->params.quality == 0) || (s->params.quality == 1))
  {
    helper_EncodeData_4(s, is_last, out_size, output, delta, bytes, wrapped_last_processed_pos, data, data_idx, mask, m);
  }
  {
    helper_EncodeData_2(s, bytes, m);
  }
  InitOrStitchToPreviousBlock(m, &s->hasher_, data, mask, &s->params, wrapped_last_processed_pos, bytes, is_last);
  literal_context_mode = ChooseContextMode(&s->params, data, WrapPosition(s->last_flush_pos_), mask, (size_t) (s->input_pos_ - s->last_flush_pos_));
  literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  if (!(!0))
  {
    return 0;
  }
  if (s->num_commands_ && (s->last_insert_len_ == 0))
  {
    ExtendLastCommand(s, &bytes, &wrapped_last_processed_pos);
  }
  if (s->params.quality == 10)
  {
    ;
    BrotliCreateZopfliBackwardReferences(m, bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
    if (!(!0))
    {
      return 0;
    }
  }
  else
    if (s->params.quality == 11)
  {
    ;
    BrotliCreateHqZopfliBackwardReferences(m, bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCreateBackwardReferences(bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
  }
  {
    helper_EncodeData_1(s, is_last, force_flush, out_size);
  }
  if (s->last_insert_len_ > 0)
  {
    InitInsertCommand(&s->commands_[s->num_commands_++], s->last_insert_len_);
    s->num_literals_ += s->last_insert_len_;
    s->last_insert_len_ = 0;
  }
  if ((!is_last) && (s->input_pos_ == s->last_flush_pos_))
  {
    *out_size = 0;
    return 1;
  }
  ;
  ;
  ;
  {
    helper_EncodeData_3(s, is_last, out_size, output, data, data_idx, mask, m, literal_context_mode);
  }
}


/*** DEPENDENCIES:
static ContextType ChooseContextMode(const BrotliEncoderParams *params, const uint8_t *data, const size_t pos, const size_t mask, const size_t length)
{
  if ((params->quality >= 10) && (!BrotliIsMostlyUTF8(data, pos, mask, length, kMinUTF8Ratio)))
  {
    return CONTEXT_SIGNED;
  }
  return CONTEXT_UTF8;
}


----------------------------
static void ExtendLastCommand(BrotliEncoderState *s, uint32_t *bytes, uint32_t *wrapped_last_processed_pos)
{
  Command *last_command = &s->commands_[s->num_commands_ - 1];
  const uint8_t *data = s->ringbuffer_.buffer_;
  const uint32_t mask = s->ringbuffer_.mask_;
  uint64_t max_backward_distance = (((uint64_t) 1) << s->params.lgwin) - 16;
  uint64_t last_copy_len = last_command->copy_len_ & 0x1FFFFFF;
  uint64_t last_processed_pos = s->last_processed_pos_ - last_copy_len;
  uint64_t max_distance = (last_processed_pos < max_backward_distance) ? (last_processed_pos) : (max_backward_distance);
  uint64_t cmd_dist = (uint64_t) s->dist_cache_[0];
  uint32_t distance_code = CommandRestoreDistanceCode(last_command, &s->params.dist);
  if ((distance_code < 16) || ((distance_code - (16 - 1)) == cmd_dist))
  {
    if (cmd_dist <= max_distance)
    {
      while (((*bytes) != 0) && (data[(*wrapped_last_processed_pos) & mask] == data[((*wrapped_last_processed_pos) - cmd_dist) & mask]))
      {
        last_command->copy_len_ += 1;
        *bytes -= 1;
        *wrapped_last_processed_pos += 1;
      }

    }
    else
    {
    }
    GetLengthCode(last_command->insert_len_, (size_t) (((int) (last_command->copy_len_ & 0x1FFFFFF)) + ((int) (last_command->copy_len_ >> 25))), (!(!((last_command->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &last_command->cmd_prefix_);
  }
}


----------------------------
int helper_EncodeData_3(BrotliEncoderState * const s, const int is_last, size_t * const out_size, uint8_t ** const output, uint8_t * const data, unsigned int data_idx, uint32_t mask, MemoryManager * const m, ContextType literal_context_mode)
{
  const uint32_t metablock_size = (uint32_t) (s->input_pos_ - s->last_flush_pos_);
  uint8_t *storage = GetBrotliStorage(s, (2 * metablock_size) + 503);
  unsigned int storage_idx = 0;
  size_t storage_ix = s->last_bytes_bits_;
  if (!(!0))
  {
    return 0;
  }
  storage[0 + storage_idx] = (uint8_t) s->last_bytes_;
  storage[1 + storage_idx] = (uint8_t) (s->last_bytes_ >> 8);
  WriteMetaBlockInternal(m, data, mask, s->last_flush_pos_, metablock_size, is_last, literal_context_mode, &s->params, s->prev_byte_, s->prev_byte2_, s->num_literals_, s->num_commands_, s->commands_, s->saved_dist_cache_, s->dist_cache_, &storage_ix, storage);
  if (!(!0))
  {
    return 0;
  }
  s->last_bytes_ = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  s->last_bytes_bits_ = storage_ix & 7u;
  s->last_flush_pos_ = s->input_pos_;
  if (UpdateLastProcessedPos(s))
  {
    HasherReset(&s->hasher_);
  }
  if (s->last_flush_pos_ > 0)
  {
    s->prev_byte_ = data[((((uint32_t) s->last_flush_pos_) - 1) & mask) + data_idx];
  }
  if (s->last_flush_pos_ > 1)
  {
    s->prev_byte2_ = data[(((uint32_t) (s->last_flush_pos_ - 2)) & mask) + data_idx];
  }
  s->num_commands_ = 0;
  s->num_literals_ = 0;
  memcpy(s->saved_dist_cache_, s->dist_cache_, sizeof(s->saved_dist_cache_));
  *output = &storage[0 + storage_idx];
  *out_size = storage_ix >> 3;
  return 1;
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
int helper_EncodeData_1(BrotliEncoderState * const s, const int is_last, const int force_flush, size_t * const out_size)
{
  const size_t max_length = MaxMetablockSize(&s->params);
  const size_t max_literals = max_length / 8;
  const size_t max_commands = max_length / 8;
  const size_t processed_bytes = (size_t) (s->input_pos_ - s->last_flush_pos_);
  const int next_input_fits_metablock = (!(!((processed_bytes + InputBlockSize(s)) <= max_length))) ? (1) : (0);
  const int should_flush = (!(!((s->params.quality < 4) && ((s->num_literals_ + s->num_commands_) >= 0x2FFF)))) ? (1) : (0);
  if ((((((!is_last) && (!force_flush)) && (!should_flush)) && next_input_fits_metablock) && (s->num_literals_ < max_literals)) && (s->num_commands_ < max_commands))
  {
    if (UpdateLastProcessedPos(s))
    {
      HasherReset(&s->hasher_);
    }
    *out_size = 0;
    return 1;
  }
}


----------------------------
void BrotliCreateZopfliBackwardReferences(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  ZopfliNode *nodes = ((num_bytes + 1) > 0) ? ((ZopfliNode *) BrotliAllocate(m, (num_bytes + 1) * (sizeof(ZopfliNode)))) : (0);
  unsigned int nodes_idx = 0;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliInitZopfliNodes(nodes, num_bytes + 1);
  *num_commands += BrotliZopfliComputeShortestPath(m, num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, dist_cache, hasher, nodes);
  if (!(!0))
  {
    return;
  }
  BrotliZopfliCreateCommands(num_bytes, position, nodes, dist_cache, last_insert_len, params, commands, num_literals);
  {
    BrotliFree(m, nodes);
    nodes_idx = 0;
  }
  ;
}


----------------------------
inline static void InitInsertCommand(Command *self, size_t insertlen)
{
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = 4 << 25;
  self->dist_extra_ = 0;
  self->dist_prefix_ = 16;
  GetLengthCode(insertlen, 4, 0, &self->cmd_prefix_);
}


----------------------------
static size_t InputBlockSize(BrotliEncoderState *s)
{
  return ((size_t) 1) << s->params.lgblock;
}


----------------------------
static uint64_t UnprocessedInputSize(BrotliEncoderState *s)
{
  return s->input_pos_ - s->last_processed_pos_;
}


----------------------------
inline static void InitOrStitchToPreviousBlock(MemoryManager *m, Hasher *hasher, const uint8_t *data, size_t mask, BrotliEncoderParams *params, size_t position, size_t input_size, int is_last)
{
  HasherSetup(m, hasher, params, data, position, input_size, is_last);
  if (!(!0))
  {
    return;
  }
  switch (hasher->common.params.type)
  {
    case 2:
    {
      StitchToPreviousBlockH2(&hasher->privat._H2, input_size, position, data, mask);
      break;
    }

    case 3:
    {
      StitchToPreviousBlockH3(&hasher->privat._H3, input_size, position, data, mask);
      break;
    }

    case 4:
    {
      StitchToPreviousBlockH4(&hasher->privat._H4, input_size, position, data, mask);
      break;
    }

    case 5:
    {
      StitchToPreviousBlockH5(&hasher->privat._H5, input_size, position, data, mask);
      break;
    }

    case 6:
    {
      StitchToPreviousBlockH6(&hasher->privat._H6, input_size, position, data, mask);
      break;
    }

    case 40:
    {
      StitchToPreviousBlockH40(&hasher->privat._H40, input_size, position, data, mask);
      break;
    }

    case 41:
    {
      StitchToPreviousBlockH41(&hasher->privat._H41, input_size, position, data, mask);
      break;
    }

    case 42:
    {
      StitchToPreviousBlockH42(&hasher->privat._H42, input_size, position, data, mask);
      break;
    }

    case 54:
    {
      StitchToPreviousBlockH54(&hasher->privat._H54, input_size, position, data, mask);
      break;
    }

    case 35:
    {
      StitchToPreviousBlockH35(&hasher->privat._H35, input_size, position, data, mask);
      break;
    }

    case 55:
    {
      StitchToPreviousBlockH55(&hasher->privat._H55, input_size, position, data, mask);
      break;
    }

    case 65:
    {
      StitchToPreviousBlockH65(&hasher->privat._H65, input_size, position, data, mask);
      break;
    }

    case 10:
    {
      StitchToPreviousBlockH10(&hasher->privat._H10, input_size, position, data, mask);
      break;
    }

    default:
    {
      break;
    }

  }

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
void BrotliCreateHqZopfliBackwardReferences(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  uint32_t *num_matches = (num_bytes > 0) ? ((uint32_t *) BrotliAllocate(m, num_bytes * (sizeof(uint32_t)))) : (0);
  unsigned int num_matches_idx = 0;
  size_t matches_size = 4 * num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH10()) ? (((position + num_bytes) - StoreLookaheadH10()) + 1) : (position);
  size_t cur_match_pos = 0;
  size_t i;
  size_t orig_num_literals;
  size_t orig_last_insert_len;
  int orig_dist_cache[4];
  size_t orig_num_commands;
  ZopfliCostModel model;
  ZopfliNode *nodes;
  unsigned int nodes_idx = 0;
  BackwardMatch *matches = (matches_size > 0) ? ((BackwardMatch *) BrotliAllocate(m, matches_size * (sizeof(BackwardMatch)))) : (0);
  unsigned int matches_idx = 0;
  size_t gap = 0;
  size_t shadow_matches = 0;
  (void) literal_context_lut;
  if (((!(!0)) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; ((i + HashTypeLengthH10()) - 1) < num_bytes; i += 1)
  {
    helper_BrotliCreateHqZopfliBackwardReferences_1(&num_matches_idx, &matches_size, &cur_match_pos, &i, &matches_idx, m, num_bytes, position, ringbuffer, ringbuffer_mask, params, hasher, stream_offset, max_backward_limit, num_matches, store_end, matches, gap, shadow_matches);
  }

  orig_num_literals = *num_literals;
  orig_last_insert_len = *last_insert_len;
  memcpy(orig_dist_cache, dist_cache, 4 * (sizeof(dist_cache[0])));
  orig_num_commands = *num_commands;
  nodes_idx = ((num_bytes + 1) > 0) ? ((ZopfliNode *) BrotliAllocate(m, (num_bytes + 1) * (sizeof(ZopfliNode)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitZopfliCostModel(m, &model, &params->dist, num_bytes);
  if (!(!0))
  {
    return;
  }
  for (i = 0; i < 2; i += 1)
  {
    BrotliInitZopfliNodes(nodes, num_bytes + 1);
    if (i == 0)
    {
      ZopfliCostModelSetFromLiteralCosts(&model, position, ringbuffer, ringbuffer_mask);
    }
    else
    {
      ZopfliCostModelSetFromCommands(&model, position, ringbuffer, ringbuffer_mask, commands, (*num_commands) - orig_num_commands, orig_last_insert_len);
    }
    *num_commands = orig_num_commands;
    *num_literals = orig_num_literals;
    *last_insert_len = orig_last_insert_len;
    memcpy(dist_cache, orig_dist_cache, 4 * (sizeof(dist_cache[0])));
    *num_commands += ZopfliIterate(num_bytes, position, ringbuffer, ringbuffer_mask, params, gap, dist_cache, &model, num_matches, matches, nodes);
    BrotliZopfliCreateCommands(num_bytes, position, nodes, dist_cache, last_insert_len, params, commands, num_literals);
  }

  CleanupZopfliCostModel(m, &model);
  {
    BrotliFree(m, nodes);
    nodes_idx = 0;
  }
  ;
  {
    BrotliFree(m, matches);
    matches_idx = 0;
  }
  ;
  {
    BrotliFree(m, num_matches);
    num_matches_idx = 0;
  }
  ;
}


----------------------------
int helper_EncodeData_2(BrotliEncoderState * const s, uint32_t bytes, MemoryManager * const m)
{
  size_t newsize = (s->num_commands_ + (bytes / 2)) + 1;
  if (newsize > s->cmd_alloc_size_)
  {
    Command *new_commands;
    unsigned int new_commands_idx = 0;
    newsize += (bytes / 4) + 16;
    s->cmd_alloc_size_ = newsize;
    new_commands_idx = (newsize > 0) ? ((Command *) BrotliAllocate(m, newsize * (sizeof(Command)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return 0;
    }
    if (s->commands_)
    {
      memcpy(new_commands, s->commands_, (sizeof(Command)) * s->num_commands_);
      {
        BrotliFree(m, s->commands_);
        s->commands_ = 0;
      }
      ;
    }
    s->commands_ = &new_commands[new_commands_idx];
  }
}


----------------------------
void BrotliCreateBackwardReferences(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  switch (params->hasher.type)
  {
    case 2:
    {
      CreateBackwardReferencesNH2(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 3:
    {
      CreateBackwardReferencesNH3(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 4:
    {
      CreateBackwardReferencesNH4(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 5:
    {
      CreateBackwardReferencesNH5(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 6:
    {
      CreateBackwardReferencesNH6(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 40:
    {
      CreateBackwardReferencesNH40(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 41:
    {
      CreateBackwardReferencesNH41(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 42:
    {
      CreateBackwardReferencesNH42(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 54:
    {
      CreateBackwardReferencesNH54(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 35:
    {
      CreateBackwardReferencesNH35(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 55:
    {
      CreateBackwardReferencesNH55(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    case 65:
    {
      CreateBackwardReferencesNH65(num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, hasher, dist_cache, last_insert_len, commands, num_commands, num_literals);
      return;
    }

    default:
    {
      break;
    }

  }

}


----------------------------
static const size_t kCompressFragmentTwoPassBlockSize = 1 << 17
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
int helper_EncodeData_4(BrotliEncoderState * const s, const int is_last, size_t * const out_size, uint8_t ** const output, const uint64_t delta, uint32_t bytes, uint32_t wrapped_last_processed_pos, uint8_t * const data, unsigned int data_idx, uint32_t mask, MemoryManager * const m)
{
  uint8_t *storage;
  unsigned int storage_idx = 0;
  size_t storage_ix = s->last_bytes_bits_;
  size_t table_size;
  int *table;
  unsigned int table_idx = 0;
  if ((delta == 0) && (!is_last))
  {
    *out_size = 0;
    return 1;
  }
  storage_idx = GetBrotliStorage(s, (2 * bytes) + 503);
  if (!(!0))
  {
    return 0;
  }
  storage[0 + storage_idx] = (uint8_t) s->last_bytes_;
  storage[1 + storage_idx] = (uint8_t) (s->last_bytes_ >> 8);
  table_idx = GetHashTable(s, s->params.quality, bytes, &table_size);
  if (!(!0))
  {
    return 0;
  }
  if (s->params.quality == 0)
  {
    BrotliCompressFragmentFast(m, &data[(wrapped_last_processed_pos & mask) + data_idx], bytes, is_last, table, table_size, s->cmd_depths_, s->cmd_bits_, &s->cmd_code_numbits_, s->cmd_code_, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCompressFragmentTwoPass(m, &data[(wrapped_last_processed_pos & mask) + data_idx], bytes, is_last, s->command_buf_, s->literal_buf_, table, table_size, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  s->last_bytes_ = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  s->last_bytes_bits_ = storage_ix & 7u;
  UpdateLastProcessedPos(s);
  *output = &storage[0 + storage_idx];
  *out_size = storage_ix >> 3;
  return 1;
}


----------------------------
extern const uint8_t _kBrotliContextLookupTable[2048]
----------------------------
static uint32_t WrapPosition(uint64_t position)
{
  uint32_t result = (uint32_t) position;
  uint64_t gb = position >> 30;
  if (gb > 2)
  {
    result = (result & ((1u << 30) - 1)) | ((((uint32_t) ((gb - 1) & 1)) + 1) << 30);
  }
  return result;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void helper_helper_ProcessMetadata_1_1(BrotliEncoderState * const s, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out)
{
  if (s->remaining_metadata_bytes_ == 0)
  {
    s->remaining_metadata_bytes_ = ~((uint32_t) 0);
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    break;
  }
  if (*available_out)
  {
    uint32_t copy = (uint32_t) brotli_min_size_t(s->remaining_metadata_bytes_, *available_out);
    memcpy(*next_out, *next_in, copy);
    *next_in += copy;
    *available_in -= copy;
    s->remaining_metadata_bytes_ -= copy;
    *next_out += copy;
    *available_out -= copy;
  }
  else
  {
    uint32_t copy = brotli_min_uint32_t(s->remaining_metadata_bytes_, 16);
    s->next_out_ = s->tiny_buf_.u8;
    memcpy(s->next_out_, *next_in, copy);
    *next_in += copy;
    *available_in -= copy;
    s->remaining_metadata_bytes_ -= copy;
    s->available_out_ = copy;
  }
  continue;
}


/*** DEPENDENCIES:
inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


int helper_ProcessMetadata_1(BrotliEncoderState * const s, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out)
{
  if (InjectFlushOrPushOutput(s, available_out, next_out, total_out))
  {
    continue;
  }
  if (s->available_out_ != 0)
  {
    break;
  }
  if (s->input_pos_ != s->last_flush_pos_)
  {
    int result = EncodeData(s, 0, 1, &s->available_out_, &s->next_out_);
    if (!result)
    {
      return 0;
    }
    continue;
  }
  if (s->stream_state_ == BROTLI_STREAM_METADATA_HEAD)
  {
    s->next_out_ = s->tiny_buf_.u8;
    s->available_out_ = WriteMetadataHeader(s, s->remaining_metadata_bytes_, s->next_out_);
    s->stream_state_ = BROTLI_STREAM_METADATA_BODY;
    continue;
  }
  else
  {
    helper_helper_ProcessMetadata_1_1(s, available_in, next_in, available_out, next_out);
  }
}


/*** DEPENDENCIES:
static size_t WriteMetadataHeader(BrotliEncoderState *s, const size_t block_size, uint8_t *header)
{
  size_t storage_ix;
  storage_ix = s->last_bytes_bits_;
  header[0] = (uint8_t) s->last_bytes_;
  header[1] = (uint8_t) (s->last_bytes_ >> 8);
  s->last_bytes_ = 0;
  s->last_bytes_bits_ = 0;
  BrotliWriteBits(1, 0, &storage_ix, header);
  BrotliWriteBits(2, 3, &storage_ix, header);
  BrotliWriteBits(1, 0, &storage_ix, header);
  if (block_size == 0)
  {
    BrotliWriteBits(2, 0, &storage_ix, header);
  }
  else
  {
    uint32_t nbits = (block_size == 1) ? (0) : (Log2FloorNonZero(((uint32_t) block_size) - 1) + 1);
    uint32_t nbytes = (nbits + 7) / 8;
    BrotliWriteBits(2, nbytes, &storage_ix, header);
    BrotliWriteBits(8 * nbytes, block_size - 1, &storage_ix, header);
  }
  return (storage_ix + 7u) >> 3;
}


----------------------------
static int InjectFlushOrPushOutput(BrotliEncoderState *s, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->last_bytes_bits_ != 0))
  {
    InjectBytePaddingBlock(s);
    return 1;
  }
  if ((s->available_out_ != 0) && ((*available_out) != 0))
  {
    size_t copy_output_size = brotli_min_size_t(s->available_out_, *available_out);
    memcpy(*next_out, s->next_out_, copy_output_size);
    *next_out += copy_output_size;
    *available_out -= copy_output_size;
    s->next_out_ += copy_output_size;
    s->available_out_ -= copy_output_size;
    s->total_out_ += copy_output_size;
    if (total_out)
    {
      *total_out = s->total_out_;
    }
    return 1;
  }
  return 0;
}


----------------------------
static int EncodeData(BrotliEncoderState *s, const int is_last, const int force_flush, size_t *out_size, uint8_t **output)
{
  const uint64_t delta = UnprocessedInputSize(s);
  uint32_t bytes = (uint32_t) delta;
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint8_t *data;
  unsigned int data_idx = 0;
  uint32_t mask;
  MemoryManager *m = &s->memory_manager_;
  ContextType literal_context_mode;
  ContextLut literal_context_lut;
  data_idx = s->ringbuffer_.buffer_;
  mask = s->ringbuffer_.mask_;
  if (s->is_last_block_emitted_)
  {
    return 0;
  }
  if (is_last)
  {
    s->is_last_block_emitted_ = 1;
  }
  if (delta > InputBlockSize(s))
  {
    return 0;
  }
  if ((s->params.quality == 1) && (!s->command_buf_))
  {
    s->command_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint32_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint32_t)))) : (0);
    s->literal_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint8_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
  }
  if ((s->params.quality == 0) || (s->params.quality == 1))
  {
    helper_EncodeData_4(s, is_last, out_size, output, delta, bytes, wrapped_last_processed_pos, data, data_idx, mask, m);
  }
  {
    helper_EncodeData_2(s, bytes, m);
  }
  InitOrStitchToPreviousBlock(m, &s->hasher_, data, mask, &s->params, wrapped_last_processed_pos, bytes, is_last);
  literal_context_mode = ChooseContextMode(&s->params, data, WrapPosition(s->last_flush_pos_), mask, (size_t) (s->input_pos_ - s->last_flush_pos_));
  literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  if (!(!0))
  {
    return 0;
  }
  if (s->num_commands_ && (s->last_insert_len_ == 0))
  {
    ExtendLastCommand(s, &bytes, &wrapped_last_processed_pos);
  }
  if (s->params.quality == 10)
  {
    ;
    BrotliCreateZopfliBackwardReferences(m, bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
    if (!(!0))
    {
      return 0;
    }
  }
  else
    if (s->params.quality == 11)
  {
    ;
    BrotliCreateHqZopfliBackwardReferences(m, bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCreateBackwardReferences(bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
  }
  {
    helper_EncodeData_1(s, is_last, force_flush, out_size);
  }
  if (s->last_insert_len_ > 0)
  {
    InitInsertCommand(&s->commands_[s->num_commands_++], s->last_insert_len_);
    s->num_literals_ += s->last_insert_len_;
    s->last_insert_len_ = 0;
  }
  if ((!is_last) && (s->input_pos_ == s->last_flush_pos_))
  {
    *out_size = 0;
    return 1;
  }
  ;
  ;
  ;
  {
    helper_EncodeData_3(s, is_last, out_size, output, data, data_idx, mask, m, literal_context_mode);
  }
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
void helper_helper_ProcessMetadata_1_1(BrotliEncoderState * const s, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out)
{
  if (s->remaining_metadata_bytes_ == 0)
  {
    s->remaining_metadata_bytes_ = ~((uint32_t) 0);
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    break;
  }
  if (*available_out)
  {
    uint32_t copy = (uint32_t) brotli_min_size_t(s->remaining_metadata_bytes_, *available_out);
    memcpy(*next_out, *next_in, copy);
    *next_in += copy;
    *available_in -= copy;
    s->remaining_metadata_bytes_ -= copy;
    *next_out += copy;
    *available_out -= copy;
  }
  else
  {
    uint32_t copy = brotli_min_uint32_t(s->remaining_metadata_bytes_, 16);
    s->next_out_ = s->tiny_buf_.u8;
    memcpy(s->next_out_, *next_in, copy);
    *next_in += copy;
    *available_in -= copy;
    s->remaining_metadata_bytes_ -= copy;
    s->available_out_ = copy;
  }
  continue;
}


----------------------------
***/


static int ProcessMetadata(BrotliEncoderState *s, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if ((*available_in) > (1u << 24))
  {
    return 0;
  }
  if (s->stream_state_ == BROTLI_STREAM_PROCESSING)
  {
    s->remaining_metadata_bytes_ = (uint32_t) (*available_in);
    s->stream_state_ = BROTLI_STREAM_METADATA_HEAD;
  }
  if ((s->stream_state_ != BROTLI_STREAM_METADATA_HEAD) && (s->stream_state_ != BROTLI_STREAM_METADATA_BODY))
  {
    return 0;
  }
  while (1)
  {
    helper_ProcessMetadata_1(s, available_in, next_in, available_out, next_out, total_out);
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
int helper_ProcessMetadata_1(BrotliEncoderState * const s, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out)
{
  if (InjectFlushOrPushOutput(s, available_out, next_out, total_out))
  {
    continue;
  }
  if (s->available_out_ != 0)
  {
    break;
  }
  if (s->input_pos_ != s->last_flush_pos_)
  {
    int result = EncodeData(s, 0, 1, &s->available_out_, &s->next_out_);
    if (!result)
    {
      return 0;
    }
    continue;
  }
  if (s->stream_state_ == BROTLI_STREAM_METADATA_HEAD)
  {
    s->next_out_ = s->tiny_buf_.u8;
    s->available_out_ = WriteMetadataHeader(s, s->remaining_metadata_bytes_, s->next_out_);
    s->stream_state_ = BROTLI_STREAM_METADATA_BODY;
    continue;
  }
  else
  {
    helper_helper_ProcessMetadata_1_1(s, available_in, next_in, available_out, next_out);
  }
}


----------------------------
***/


static void UpdateSizeHint(BrotliEncoderState *s, size_t available_in)
{
  if (s->params.size_hint == 0)
  {
    uint64_t delta = UnprocessedInputSize(s);
    uint64_t tail = available_in;
    uint32_t limit = 1u << 30;
    uint32_t total;
    if (((delta >= limit) || (tail >= limit)) || ((delta + tail) >= limit))
    {
      total = limit;
    }
    else
    {
      total = (uint32_t) (delta + tail);
    }
    s->params.size_hint = total;
  }
}


/*** DEPENDENCIES:
static uint64_t UnprocessedInputSize(BrotliEncoderState *s)
{
  return s->input_pos_ - s->last_processed_pos_;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


const uint8_t *BrotliEncoderTakeOutput(BrotliEncoderState *s, size_t *size)
{
  size_t consumed_size = s->available_out_;
  uint8_t *result = s->next_out_;
  unsigned int result_idx = 0;
  if (*size)
  {
    consumed_size = brotli_min_size_t(*size, s->available_out_);
  }
  if (consumed_size)
  {
    s->next_out_ += consumed_size;
    s->available_out_ -= consumed_size;
    s->total_out_ += consumed_size;
    CheckFlushComplete(s);
    *size = consumed_size;
  }
  else
  {
    *size = 0;
    result_idx = 0;
  }
  return result;
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static void CheckFlushComplete(BrotliEncoderState *s)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->available_out_ == 0))
  {
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    s->next_out_ = 0;
  }
}


----------------------------
***/


inline static void RingBufferSetup(const BrotliEncoderParams *params, RingBuffer *rb)
{
  int window_bits = ComputeRbBits(params);
  int tail_bits = params->lgblock;
  *((uint32_t *) (&rb->size_)) = 1u << window_bits;
  *((uint32_t *) (&rb->mask_)) = (1u << window_bits) - 1;
  *((uint32_t *) (&rb->tail_size_)) = 1u << tail_bits;
  *((uint32_t *) (&rb->total_size_)) = rb->size_ + rb->tail_size_;
}


/*** DEPENDENCIES:
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
inline static int ComputeRbBits(const BrotliEncoderParams *params)
{
  return 1 + brotli_max_int(params->lgwin, params->lgblock);
}


----------------------------
None
----------------------------
***/


inline static void RingBufferFree(MemoryManager *m, RingBuffer *rb)
{
  {
    BrotliFree(m, rb->data_);
    rb->data_ = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
***/


static size_t RemainingInputBlockSize(BrotliEncoderState *s)
{
  const uint64_t delta = UnprocessedInputSize(s);
  size_t block_size = InputBlockSize(s);
  if (delta >= block_size)
  {
    return 0;
  }
  return block_size - ((size_t) delta);
}


/*** DEPENDENCIES:
static uint64_t UnprocessedInputSize(BrotliEncoderState *s)
{
  return s->input_pos_ - s->last_processed_pos_;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static size_t InputBlockSize(BrotliEncoderState *s)
{
  return ((size_t) 1) << s->params.lgblock;
}


----------------------------
***/


static void BrotliEncoderInitState(BrotliEncoderState *s)
{
  BrotliEncoderInitParams(&s->params);
  s->input_pos_ = 0;
  s->num_commands_ = 0;
  s->num_literals_ = 0;
  s->last_insert_len_ = 0;
  s->last_flush_pos_ = 0;
  s->last_processed_pos_ = 0;
  s->prev_byte_ = 0;
  s->prev_byte2_ = 0;
  s->storage_size_ = 0;
  s->storage_ = 0;
  HasherInit(&s->hasher_);
  s->large_table_ = 0;
  s->large_table_size_ = 0;
  s->cmd_code_numbits_ = 0;
  s->command_buf_ = 0;
  s->literal_buf_ = 0;
  s->next_out_ = 0;
  s->available_out_ = 0;
  s->total_out_ = 0;
  s->stream_state_ = BROTLI_STREAM_PROCESSING;
  s->is_last_block_emitted_ = 0;
  s->is_initialized_ = 0;
  RingBufferInit(&s->ringbuffer_);
  s->commands_ = 0;
  s->cmd_alloc_size_ = 0;
  s->dist_cache_[0] = 4;
  s->dist_cache_[1] = 11;
  s->dist_cache_[2] = 15;
  s->dist_cache_[3] = 16;
  memcpy(s->saved_dist_cache_, s->dist_cache_, sizeof(s->saved_dist_cache_));
}


/*** DEPENDENCIES:
static void BrotliEncoderInitParams(BrotliEncoderParams *params)
{
  params->mode = BROTLI_MODE_GENERIC;
  params->large_window = 0;
  params->quality = 11;
  params->lgwin = 22;
  params->lgblock = 0;
  params->stream_offset = 0;
  params->size_hint = 0;
  params->disable_literal_context_modeling = 0;
  BrotliInitEncoderDictionary(&params->dictionary);
  params->dist.distance_postfix_bits = 0;
  params->dist.num_direct_distance_codes = 0;
  params->dist.alphabet_size_max = (16 + 0) + (24U << (0 + 1));
  params->dist.alphabet_size_limit = params->dist.alphabet_size_max;
  params->dist.max_distance = 0x3FFFFFC;
}


----------------------------
inline static void HasherInit(Hasher *hasher)
{
  hasher->common.extra = 0;
}


----------------------------
inline static void RingBufferInit(RingBuffer *rb)
{
  rb->cur_size_ = 0;
  rb->pos_ = 0;
  rb->data_ = 0;
  rb->buffer_ = 0;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
***/


BrotliEncoderState *BrotliEncoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  BrotliEncoderState *state = 0;
  unsigned int state_idx = 0;
  if ((!alloc_func) && (!free_func))
  {
    state_idx = (BrotliEncoderState *) malloc(sizeof(BrotliEncoderState));
  }
  else
    if (alloc_func && free_func)
  {
    state_idx = (BrotliEncoderState *) alloc_func(opaque, sizeof(BrotliEncoderState));
  }
  if ((&state[state_idx]) == 0)
  {
    return 0;
  }
  BrotliInitMemoryManager(&state->memory_manager_, alloc_func, free_func, opaque);
  BrotliEncoderInitState(state);
  return state;
}


/*** DEPENDENCIES:
static void BrotliEncoderInitState(BrotliEncoderState *s)
{
  BrotliEncoderInitParams(&s->params);
  s->input_pos_ = 0;
  s->num_commands_ = 0;
  s->num_literals_ = 0;
  s->last_insert_len_ = 0;
  s->last_flush_pos_ = 0;
  s->last_processed_pos_ = 0;
  s->prev_byte_ = 0;
  s->prev_byte2_ = 0;
  s->storage_size_ = 0;
  s->storage_ = 0;
  HasherInit(&s->hasher_);
  s->large_table_ = 0;
  s->large_table_size_ = 0;
  s->cmd_code_numbits_ = 0;
  s->command_buf_ = 0;
  s->literal_buf_ = 0;
  s->next_out_ = 0;
  s->available_out_ = 0;
  s->total_out_ = 0;
  s->stream_state_ = BROTLI_STREAM_PROCESSING;
  s->is_last_block_emitted_ = 0;
  s->is_initialized_ = 0;
  RingBufferInit(&s->ringbuffer_);
  s->commands_ = 0;
  s->cmd_alloc_size_ = 0;
  s->dist_cache_[0] = 4;
  s->dist_cache_[1] = 11;
  s->dist_cache_[2] = 15;
  s->dist_cache_[3] = 16;
  memcpy(s->saved_dist_cache_, s->dist_cache_, sizeof(s->saved_dist_cache_));
}


----------------------------
typedef void (*brotli_free_func)(void *opaque, void *address)
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
typedef void *(*brotli_alloc_func)(void *opaque, size_t size)
----------------------------
void BrotliInitMemoryManager(MemoryManager *m, brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  if (!alloc_func)
  {
    m->alloc_func = BrotliDefaultAllocFunc;
    m->free_func = BrotliDefaultFreeFunc;
    m->opaque = 0;
  }
  else
  {
    m->alloc_func = alloc_func;
    m->free_func = free_func;
    m->opaque = opaque;
  }
}


----------------------------
***/


int helper_helper_BrotliEncoderCompressStream_1_1(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, size_t remaining_block_size)
{
  if ((remaining_block_size == 0) || (op != BROTLI_OPERATION_PROCESS))
  {
    int is_last = (!(!(((*available_in) == 0) && (op == BROTLI_OPERATION_FINISH)))) ? (1) : (0);
    int force_flush = (!(!(((*available_in) == 0) && (op == BROTLI_OPERATION_FLUSH)))) ? (1) : (0);
    int result;
    if ((!is_last) && (s->flint_ == 0))
    {
      s->flint_ = BROTLI_FLINT_WAITING_FOR_FLUSHING;
      force_flush = 1;
    }
    UpdateSizeHint(s, *available_in);
    result = EncodeData(s, is_last, force_flush, &s->available_out_, &s->next_out_);
    if (!result)
    {
      return 0;
    }
    if (force_flush)
    {
      s->stream_state_ = BROTLI_STREAM_FLUSH_REQUESTED;
    }
    if (is_last)
    {
      s->stream_state_ = BROTLI_STREAM_FINISHED;
    }
    continue;
  }
}


/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int EncodeData(BrotliEncoderState *s, const int is_last, const int force_flush, size_t *out_size, uint8_t **output)
{
  const uint64_t delta = UnprocessedInputSize(s);
  uint32_t bytes = (uint32_t) delta;
  uint32_t wrapped_last_processed_pos = WrapPosition(s->last_processed_pos_);
  uint8_t *data;
  unsigned int data_idx = 0;
  uint32_t mask;
  MemoryManager *m = &s->memory_manager_;
  ContextType literal_context_mode;
  ContextLut literal_context_lut;
  data_idx = s->ringbuffer_.buffer_;
  mask = s->ringbuffer_.mask_;
  if (s->is_last_block_emitted_)
  {
    return 0;
  }
  if (is_last)
  {
    s->is_last_block_emitted_ = 1;
  }
  if (delta > InputBlockSize(s))
  {
    return 0;
  }
  if ((s->params.quality == 1) && (!s->command_buf_))
  {
    s->command_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint32_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint32_t)))) : (0);
    s->literal_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint8_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
  }
  if ((s->params.quality == 0) || (s->params.quality == 1))
  {
    helper_EncodeData_4(s, is_last, out_size, output, delta, bytes, wrapped_last_processed_pos, data, data_idx, mask, m);
  }
  {
    helper_EncodeData_2(s, bytes, m);
  }
  InitOrStitchToPreviousBlock(m, &s->hasher_, data, mask, &s->params, wrapped_last_processed_pos, bytes, is_last);
  literal_context_mode = ChooseContextMode(&s->params, data, WrapPosition(s->last_flush_pos_), mask, (size_t) (s->input_pos_ - s->last_flush_pos_));
  literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  if (!(!0))
  {
    return 0;
  }
  if (s->num_commands_ && (s->last_insert_len_ == 0))
  {
    ExtendLastCommand(s, &bytes, &wrapped_last_processed_pos);
  }
  if (s->params.quality == 10)
  {
    ;
    BrotliCreateZopfliBackwardReferences(m, bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
    if (!(!0))
    {
      return 0;
    }
  }
  else
    if (s->params.quality == 11)
  {
    ;
    BrotliCreateHqZopfliBackwardReferences(m, bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCreateBackwardReferences(bytes, wrapped_last_processed_pos, data, mask, literal_context_lut, &s->params, &s->hasher_, s->dist_cache_, &s->last_insert_len_, &s->commands_[s->num_commands_], &s->num_commands_, &s->num_literals_);
  }
  {
    helper_EncodeData_1(s, is_last, force_flush, out_size);
  }
  if (s->last_insert_len_ > 0)
  {
    InitInsertCommand(&s->commands_[s->num_commands_++], s->last_insert_len_);
    s->num_literals_ += s->last_insert_len_;
    s->last_insert_len_ = 0;
  }
  if ((!is_last) && (s->input_pos_ == s->last_flush_pos_))
  {
    *out_size = 0;
    return 1;
  }
  ;
  ;
  ;
  {
    helper_EncodeData_3(s, is_last, out_size, output, data, data_idx, mask, m, literal_context_mode);
  }
}


----------------------------
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation
----------------------------
static void UpdateSizeHint(BrotliEncoderState *s, size_t available_in)
{
  if (s->params.size_hint == 0)
  {
    uint64_t delta = UnprocessedInputSize(s);
    uint64_t tail = available_in;
    uint32_t limit = 1u << 30;
    uint32_t total;
    if (((delta >= limit) || (tail >= limit)) || ((delta + tail) >= limit))
    {
      total = limit;
    }
    else
    {
      total = (uint32_t) (delta + tail);
    }
    s->params.size_hint = total;
  }
}


----------------------------
***/


inline static void RingBufferInitBuffer(MemoryManager *m, const uint32_t buflen, RingBuffer *rb)
{
  static const size_t kSlackForEightByteHashingEverywhere = 7;
  uint8_t *new_data = (((2 + buflen) + kSlackForEightByteHashingEverywhere) > 0) ? ((uint8_t *) BrotliAllocate(m, ((2 + buflen) + kSlackForEightByteHashingEverywhere) * (sizeof(uint8_t)))) : (0);
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  if (rb->data_)
  {
    memcpy(new_data, rb->data_, (2 + rb->cur_size_) + kSlackForEightByteHashingEverywhere);
    {
      BrotliFree(m, rb->data_);
      rb->data_ = 0;
    }
    ;
  }
  rb->data_ = new_data;
  rb->cur_size_ = buflen;
  rb->buffer_ = rb->data_ + 2;
  rb->buffer_[-2] = (rb->buffer_[-1] = 0);
  for (i = 0; i < kSlackForEightByteHashingEverywhere; i += 1)
  {
    rb->buffer_[rb->cur_size_ + i] = 0;
  }

}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
***/


inline static void RingBufferWrite(MemoryManager *m, const uint8_t *bytes, size_t n, RingBuffer *rb)
{
  if ((rb->pos_ == 0) && (n < rb->tail_size_))
  {
    rb->pos_ = (uint32_t) n;
    RingBufferInitBuffer(m, rb->pos_, rb);
    if (!(!0))
    {
      return;
    }
    memcpy(rb->buffer_, bytes, n);
    return;
  }
  if (rb->cur_size_ < rb->total_size_)
  {
    RingBufferInitBuffer(m, rb->total_size_, rb);
    if (!(!0))
    {
      return;
    }
    rb->buffer_[rb->size_ - 2] = 0;
    rb->buffer_[rb->size_ - 1] = 0;
    rb->buffer_[rb->size_] = 241;
  }
  {
    const size_t masked_pos = rb->pos_ & rb->mask_;
    RingBufferWriteTail(bytes, n, rb);
    if (__builtin_expect(!(!((masked_pos + n) <= rb->size_)), 1))
    {
      memcpy(&rb->buffer_[masked_pos], bytes, n);
    }
    else
    {
      memcpy(&rb->buffer_[masked_pos], bytes, brotli_min_size_t(n, rb->total_size_ - masked_pos));
      memcpy(&rb->buffer_[0], bytes + (rb->size_ - masked_pos), n - (rb->size_ - masked_pos));
    }
  }
  {
    int not_first_lap = (rb->pos_ & (1u << 31)) != 0;
    uint32_t rb_pos_mask = (1u << 31) - 1;
    rb->buffer_[-2] = rb->buffer_[rb->size_ - 2];
    rb->buffer_[-1] = rb->buffer_[rb->size_ - 1];
    rb->pos_ = (rb->pos_ & rb_pos_mask) + ((uint32_t) (n & rb_pos_mask));
    if (not_first_lap)
    {
      rb->pos_ |= 1u << 31;
    }
  }
}


/*** DEPENDENCIES:
inline static void RingBufferInitBuffer(MemoryManager *m, const uint32_t buflen, RingBuffer *rb)
{
  static const size_t kSlackForEightByteHashingEverywhere = 7;
  uint8_t *new_data = (((2 + buflen) + kSlackForEightByteHashingEverywhere) > 0) ? ((uint8_t *) BrotliAllocate(m, ((2 + buflen) + kSlackForEightByteHashingEverywhere) * (sizeof(uint8_t)))) : (0);
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  if (rb->data_)
  {
    memcpy(new_data, rb->data_, (2 + rb->cur_size_) + kSlackForEightByteHashingEverywhere);
    {
      BrotliFree(m, rb->data_);
      rb->data_ = 0;
    }
    ;
  }
  rb->data_ = new_data;
  rb->cur_size_ = buflen;
  rb->buffer_ = rb->data_ + 2;
  rb->buffer_[-2] = (rb->buffer_[-1] = 0);
  for (i = 0; i < kSlackForEightByteHashingEverywhere; i += 1)
  {
    rb->buffer_[rb->cur_size_ + i] = 0;
  }

}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
inline static void RingBufferWriteTail(const uint8_t *bytes, size_t n, RingBuffer *rb)
{
  const size_t masked_pos = rb->pos_ & rb->mask_;
  if (__builtin_expect(masked_pos < rb->tail_size_, 0))
  {
    const size_t p = rb->size_ + masked_pos;
    memcpy(&rb->buffer_[p], bytes, brotli_min_size_t(n, rb->tail_size_ - masked_pos));
  }
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


static void CopyInputToRingBuffer(BrotliEncoderState *s, const size_t input_size, const uint8_t *input_buffer)
{
  RingBuffer *ringbuffer_ = &s->ringbuffer_;
  MemoryManager *m = &s->memory_manager_;
  RingBufferWrite(m, input_buffer, input_size, ringbuffer_);
  if (!(!0))
  {
    return;
  }
  s->input_pos_ += input_size;
  if (ringbuffer_->pos_ <= ringbuffer_->mask_)
  {
    memset(ringbuffer_->buffer_ + ringbuffer_->pos_, 0, 7);
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
typedef struct RingBuffer
{
  const uint32_t size_;
  const uint32_t mask_;
  const uint32_t tail_size_;
  const uint32_t total_size_;
  uint32_t cur_size_;
  uint32_t pos_;
  uint8_t *data_;
  uint8_t *buffer_;
} RingBuffer
----------------------------
inline static void RingBufferWrite(MemoryManager *m, const uint8_t *bytes, size_t n, RingBuffer *rb)
{
  if ((rb->pos_ == 0) && (n < rb->tail_size_))
  {
    rb->pos_ = (uint32_t) n;
    RingBufferInitBuffer(m, rb->pos_, rb);
    if (!(!0))
    {
      return;
    }
    memcpy(rb->buffer_, bytes, n);
    return;
  }
  if (rb->cur_size_ < rb->total_size_)
  {
    RingBufferInitBuffer(m, rb->total_size_, rb);
    if (!(!0))
    {
      return;
    }
    rb->buffer_[rb->size_ - 2] = 0;
    rb->buffer_[rb->size_ - 1] = 0;
    rb->buffer_[rb->size_] = 241;
  }
  {
    const size_t masked_pos = rb->pos_ & rb->mask_;
    RingBufferWriteTail(bytes, n, rb);
    if (__builtin_expect(!(!((masked_pos + n) <= rb->size_)), 1))
    {
      memcpy(&rb->buffer_[masked_pos], bytes, n);
    }
    else
    {
      memcpy(&rb->buffer_[masked_pos], bytes, brotli_min_size_t(n, rb->total_size_ - masked_pos));
      memcpy(&rb->buffer_[0], bytes + (rb->size_ - masked_pos), n - (rb->size_ - masked_pos));
    }
  }
  {
    int not_first_lap = (rb->pos_ & (1u << 31)) != 0;
    uint32_t rb_pos_mask = (1u << 31) - 1;
    rb->buffer_[-2] = rb->buffer_[rb->size_ - 2];
    rb->buffer_[-1] = rb->buffer_[rb->size_ - 1];
    rb->pos_ = (rb->pos_ & rb_pos_mask) + ((uint32_t) (n & rb_pos_mask));
    if (not_first_lap)
    {
      rb->pos_ |= 1u << 31;
    }
  }
}


----------------------------
***/


int helper_BrotliEncoderCompressStream_1(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out)
{
  size_t remaining_block_size = RemainingInputBlockSize(s);
  if ((s->flint_ >= 0) && (remaining_block_size > ((size_t) s->flint_)))
  {
    remaining_block_size = (size_t) s->flint_;
  }
  if ((remaining_block_size != 0) && ((*available_in) != 0))
  {
    size_t copy_input_size = brotli_min_size_t(remaining_block_size, *available_in);
    CopyInputToRingBuffer(s, copy_input_size, *next_in);
    *next_in += copy_input_size;
    *available_in -= copy_input_size;
    if (s->flint_ > 0)
    {
      s->flint_ = (int8_t) (s->flint_ - ((int) copy_input_size));
    }
    continue;
  }
  if (InjectFlushOrPushOutput(s, available_out, next_out, total_out))
  {
    if (s->flint_ == BROTLI_FLINT_WAITING_FOR_FLUSHING)
    {
      CheckFlushComplete(s);
      if (s->stream_state_ == BROTLI_STREAM_PROCESSING)
      {
        s->flint_ = BROTLI_FLINT_DONE;
      }
    }
    continue;
  }
  if ((s->available_out_ == 0) && (s->stream_state_ == BROTLI_STREAM_PROCESSING))
  {
    helper_helper_BrotliEncoderCompressStream_1_1(s, op, available_in, remaining_block_size);
  }
  break;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
int helper_helper_BrotliEncoderCompressStream_1_1(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, size_t remaining_block_size)
{
  if ((remaining_block_size == 0) || (op != BROTLI_OPERATION_PROCESS))
  {
    int is_last = (!(!(((*available_in) == 0) && (op == BROTLI_OPERATION_FINISH)))) ? (1) : (0);
    int force_flush = (!(!(((*available_in) == 0) && (op == BROTLI_OPERATION_FLUSH)))) ? (1) : (0);
    int result;
    if ((!is_last) && (s->flint_ == 0))
    {
      s->flint_ = BROTLI_FLINT_WAITING_FOR_FLUSHING;
      force_flush = 1;
    }
    UpdateSizeHint(s, *available_in);
    result = EncodeData(s, is_last, force_flush, &s->available_out_, &s->next_out_);
    if (!result)
    {
      return 0;
    }
    if (force_flush)
    {
      s->stream_state_ = BROTLI_STREAM_FLUSH_REQUESTED;
    }
    if (is_last)
    {
      s->stream_state_ = BROTLI_STREAM_FINISHED;
    }
    continue;
  }
}


----------------------------
static size_t RemainingInputBlockSize(BrotliEncoderState *s)
{
  const uint64_t delta = UnprocessedInputSize(s);
  size_t block_size = InputBlockSize(s);
  if (delta >= block_size)
  {
    return 0;
  }
  return block_size - ((size_t) delta);
}


----------------------------
static int InjectFlushOrPushOutput(BrotliEncoderState *s, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->last_bytes_bits_ != 0))
  {
    InjectBytePaddingBlock(s);
    return 1;
  }
  if ((s->available_out_ != 0) && ((*available_out) != 0))
  {
    size_t copy_output_size = brotli_min_size_t(s->available_out_, *available_out);
    memcpy(*next_out, s->next_out_, copy_output_size);
    *next_out += copy_output_size;
    *available_out -= copy_output_size;
    s->next_out_ += copy_output_size;
    s->available_out_ -= copy_output_size;
    s->total_out_ += copy_output_size;
    if (total_out)
    {
      *total_out = s->total_out_;
    }
    return 1;
  }
  return 0;
}


----------------------------
static void CopyInputToRingBuffer(BrotliEncoderState *s, const size_t input_size, const uint8_t *input_buffer)
{
  RingBuffer *ringbuffer_ = &s->ringbuffer_;
  MemoryManager *m = &s->memory_manager_;
  RingBufferWrite(m, input_buffer, input_size, ringbuffer_);
  if (!(!0))
  {
    return;
  }
  s->input_pos_ += input_size;
  if (ringbuffer_->pos_ <= ringbuffer_->mask_)
  {
    memset(ringbuffer_->buffer_ + ringbuffer_->pos_, 0, 7);
  }
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static void CheckFlushComplete(BrotliEncoderState *s)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->available_out_ == 0))
  {
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    s->next_out_ = 0;
  }
}


----------------------------
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation
----------------------------
***/


static int EnsureInitialized(BrotliEncoderState *s)
{
  if (!(!0))
  {
    return 0;
  }
  if (s->is_initialized_)
  {
    return 1;
  }
  s->last_bytes_bits_ = 0;
  s->last_bytes_ = 0;
  s->flint_ = BROTLI_FLINT_DONE;
  s->remaining_metadata_bytes_ = ~((uint32_t) 0);
  SanitizeParams(&s->params);
  s->params.lgblock = ComputeLgBlock(&s->params);
  ChooseDistanceParams(&s->params);
  if (s->params.stream_offset != 0)
  {
    s->flint_ = BROTLI_FLINT_NEEDS_2_BYTES;
    s->dist_cache_[0] = -16;
    s->dist_cache_[1] = -16;
    s->dist_cache_[2] = -16;
    s->dist_cache_[3] = -16;
    memcpy(s->saved_dist_cache_, s->dist_cache_, sizeof(s->saved_dist_cache_));
  }
  RingBufferSetup(&s->params, &s->ringbuffer_);
  {
    int lgwin = s->params.lgwin;
    if ((s->params.quality == 0) || (s->params.quality == 1))
    {
      lgwin = brotli_max_int(lgwin, 18);
    }
    if (s->params.stream_offset == 0)
    {
      EncodeWindowBits(lgwin, s->params.large_window, &s->last_bytes_, &s->last_bytes_bits_);
    }
    else
    {
      s->params.stream_offset = brotli_min_size_t(s->params.stream_offset, (((size_t) 1) << lgwin) - 16);
    }
  }
  if (s->params.quality == 0)
  {
    InitCommandPrefixCodes(s->cmd_depths_, s->cmd_bits_, s->cmd_code_, &s->cmd_code_numbits_);
  }
  s->is_initialized_ = 1;
  return 1;
}


/*** DEPENDENCIES:
inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static int ComputeLgBlock(const BrotliEncoderParams *params)
{
  int lgblock = params->lgblock;
  if ((params->quality == 0) || (params->quality == 1))
  {
    lgblock = params->lgwin;
  }
  else
    if (params->quality < 4)
  {
    lgblock = 14;
  }
  else
    if (lgblock == 0)
  {
    lgblock = 16;
    if ((params->quality >= 9) && (params->lgwin > lgblock))
    {
      lgblock = brotli_min_int(18, params->lgwin);
    }
  }
  else
  {
    lgblock = brotli_min_int(24, brotli_max_int(16, lgblock));
  }
  return lgblock;
}


----------------------------
static void EncodeWindowBits(int lgwin, int large_window, uint16_t *last_bytes, uint8_t *last_bytes_bits)
{
  if (large_window)
  {
    *last_bytes = (uint16_t) (((lgwin & 0x3F) << 8) | 0x11);
    *last_bytes_bits = 14;
  }
  else
  {
    if (lgwin == 16)
    {
      *last_bytes = 0;
      *last_bytes_bits = 1;
    }
    else
      if (lgwin == 17)
    {
      *last_bytes = 1;
      *last_bytes_bits = 7;
    }
    else
      if (lgwin > 17)
    {
      *last_bytes = (uint16_t) (((lgwin - 17) << 1) | 0x01);
      *last_bytes_bits = 4;
    }
    else
    {
      *last_bytes = (uint16_t) (((lgwin - 8) << 4) | 0x01);
      *last_bytes_bits = 7;
    }
  }
}


----------------------------
inline static void SanitizeParams(BrotliEncoderParams *params)
{
  params->quality = brotli_min_int(11, brotli_max_int(0, params->quality));
  if (params->quality <= 2)
  {
    params->large_window = 0;
  }
  if (params->lgwin < 10)
  {
    params->lgwin = 10;
  }
  else
  {
    int max_lgwin = (params->large_window) ? (30) : (24);
    if (params->lgwin > max_lgwin)
    {
      params->lgwin = max_lgwin;
    }
  }
}


----------------------------
inline static void RingBufferSetup(const BrotliEncoderParams *params, RingBuffer *rb)
{
  int window_bits = ComputeRbBits(params);
  int tail_bits = params->lgblock;
  *((uint32_t *) (&rb->size_)) = 1u << window_bits;
  *((uint32_t *) (&rb->mask_)) = (1u << window_bits) - 1;
  *((uint32_t *) (&rb->tail_size_)) = 1u << tail_bits;
  *((uint32_t *) (&rb->total_size_)) = rb->size_ + rb->tail_size_;
}


----------------------------
static void InitCommandPrefixCodes(uint8_t cmd_depths[128], uint16_t cmd_bits[128], uint8_t cmd_code[512], size_t *cmd_code_numbits)
{
  static const uint8_t kDefaultCommandDepths[128] = {0, 4, 4, 5, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 0, 0, 0, 4, 4, 4, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 10, 10, 10, 10, 10, 10, 0, 4, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 7, 7, 7, 8, 10, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};
  static const uint16_t kDefaultCommandBits[128] = {0, 0, 8, 9, 3, 35, 7, 71, 39, 103, 23, 47, 175, 111, 239, 31, 0, 0, 0, 4, 12, 2, 10, 6, 13, 29, 11, 43, 27, 59, 87, 55, 15, 79, 319, 831, 191, 703, 447, 959, 0, 14, 1, 25, 5, 21, 19, 51, 119, 159, 95, 223, 479, 991, 63, 575, 127, 639, 383, 895, 255, 767, 511, 1023, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 27, 59, 7, 39, 23, 55, 30, 1, 17, 9, 25, 5, 0, 8, 4, 12, 2, 10, 6, 21, 13, 29, 3, 19, 11, 15, 47, 31, 95, 63, 127, 255, 767, 2815, 1791, 3839, 511, 2559, 1535, 3583, 1023, 3071, 2047, 4095};
  static const uint8_t kDefaultCommandCode[] = {0xff, 0x77, 0xd5, 0xbf, 0xe7, 0xde, 0xea, 0x9e, 0x51, 0x5d, 0xde, 0xc6, 0x70, 0x57, 0xbc, 0x58, 0x58, 0x58, 0xd8, 0xd8, 0x58, 0xd5, 0xcb, 0x8c, 0xea, 0xe0, 0xc3, 0x87, 0x1f, 0x83, 0xc1, 0x60, 0x1c, 0x67, 0xb2, 0xaa, 0x06, 0x83, 0xc1, 0x60, 0x30, 0x18, 0xcc, 0xa1, 0xce, 0x88, 0x54, 0x94, 0x46, 0xe1, 0xb0, 0xd0, 0x4e, 0xb2, 0xf7, 0x04, 0x00};
  static const size_t kDefaultCommandCodeNumBits = 448;
  memcpy(cmd_depths, kDefaultCommandDepths, sizeof(kDefaultCommandDepths));
  ;
  memcpy(cmd_bits, kDefaultCommandBits, sizeof(kDefaultCommandBits));
  ;
  memcpy(cmd_code, kDefaultCommandCode, sizeof(kDefaultCommandCode));
  ;
  *cmd_code_numbits = kDefaultCommandCodeNumBits;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static void ChooseDistanceParams(BrotliEncoderParams *params)
{
  uint32_t distance_postfix_bits = 0;
  uint32_t num_direct_distance_codes = 0;
  if (params->quality >= 4)
  {
    uint32_t ndirect_msb;
    if (params->mode == BROTLI_MODE_FONT)
    {
      distance_postfix_bits = 1;
      num_direct_distance_codes = 12;
    }
    else
    {
      distance_postfix_bits = params->dist.distance_postfix_bits;
      num_direct_distance_codes = params->dist.num_direct_distance_codes;
    }
    ndirect_msb = (num_direct_distance_codes >> distance_postfix_bits) & 0x0F;
    if (((distance_postfix_bits > 3) || (num_direct_distance_codes > 120)) || ((ndirect_msb << distance_postfix_bits) != num_direct_distance_codes))
    {
      distance_postfix_bits = 0;
      num_direct_distance_codes = 0;
    }
  }
  BrotliInitDistanceParams(params, distance_postfix_bits, num_direct_distance_codes);
}


----------------------------
***/


int helper_helper_BrotliEncoderCompressStreamFast_2_1(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out, const size_t block_size_limit, uint32_t * const command_buf, uint8_t * const literal_buf, MemoryManager * const m)
{
  size_t block_size = brotli_min_size_t(block_size_limit, *available_in);
  int is_last = ((*available_in) == block_size) && (op == BROTLI_OPERATION_FINISH);
  int force_flush = ((*available_in) == block_size) && (op == BROTLI_OPERATION_FLUSH);
  size_t max_out_size = (2 * block_size) + 503;
  int inplace = 1;
  uint8_t *storage = 0;
  unsigned int storage_idx = 0;
  size_t storage_ix = s->last_bytes_bits_;
  size_t table_size;
  int *table;
  unsigned int table_idx = 0;
  if (force_flush && (block_size == 0))
  {
    s->stream_state_ = BROTLI_STREAM_FLUSH_REQUESTED;
    continue;
  }
  if (max_out_size <= (*available_out))
  {
    storage_idx = *next_out;
  }
  else
  {
    inplace = 0;
    storage_idx = GetBrotliStorage(s, max_out_size);
    if (!(!0))
    {
      return 0;
    }
  }
  storage[0 + storage_idx] = (uint8_t) s->last_bytes_;
  storage[1 + storage_idx] = (uint8_t) (s->last_bytes_ >> 8);
  table_idx = GetHashTable(s, s->params.quality, block_size, &table_size);
  if (!(!0))
  {
    return 0;
  }
  if (s->params.quality == 0)
  {
    BrotliCompressFragmentFast(m, *next_in, block_size, is_last, table, table_size, s->cmd_depths_, s->cmd_bits_, &s->cmd_code_numbits_, s->cmd_code_, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCompressFragmentTwoPass(m, *next_in, block_size, is_last, command_buf, literal_buf, table, table_size, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  if (block_size != 0)
  {
    *next_in += block_size;
    *available_in -= block_size;
  }
  if (inplace)
  {
    size_t out_bytes = storage_ix >> 3;
    ;
    ;
    *next_out += out_bytes;
    *available_out -= out_bytes;
    s->total_out_ += out_bytes;
    if (total_out)
    {
      *total_out = s->total_out_;
    }
  }
  else
  {
    size_t out_bytes = storage_ix >> 3;
    s->next_out_ = &storage[storage_idx];
    s->available_out_ = out_bytes;
  }
  s->last_bytes_ = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  s->last_bytes_bits_ = storage_ix & 7u;
  if (force_flush)
  {
    s->stream_state_ = BROTLI_STREAM_FLUSH_REQUESTED;
  }
  if (is_last)
  {
    s->stream_state_ = BROTLI_STREAM_FINISHED;
  }
  continue;
}


/*** DEPENDENCIES:
static uint8_t *GetBrotliStorage(BrotliEncoderState *s, size_t size)
{
  MemoryManager *m = &s->memory_manager_;
  if (s->storage_size_ < size)
  {
    {
      BrotliFree(m, s->storage_);
      s->storage_ = 0;
    }
    ;
    s->storage_ = (size > 0) ? ((uint8_t *) BrotliAllocate(m, size * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return 0;
    }
    s->storage_size_ = size;
  }
  return s->storage_;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void BrotliCompressFragmentTwoPass(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, uint32_t *command_buf, uint8_t *literal_buf, int *table, size_t table_size, size_t *storage_ix, uint8_t *storage)
{
  const size_t initial_storage_ix = *storage_ix;
  const size_t table_bits = Log2FloorNonZero(table_size);
  switch (table_bits)
  {
    case 8:
    {
      BrotliCompressFragmentTwoPassImpl8(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 9:
    {
      BrotliCompressFragmentTwoPassImpl9(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 10:
    {
      BrotliCompressFragmentTwoPassImpl10(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 11:
    {
      BrotliCompressFragmentTwoPassImpl11(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 12:
    {
      BrotliCompressFragmentTwoPassImpl12(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 13:
    {
      BrotliCompressFragmentTwoPassImpl13(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 14:
    {
      BrotliCompressFragmentTwoPassImpl14(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 15:
    {
      BrotliCompressFragmentTwoPassImpl15(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 16:
    {
      BrotliCompressFragmentTwoPassImpl16(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    case 17:
    {
      BrotliCompressFragmentTwoPassImpl17(m, input, input_size, is_last, command_buf, literal_buf, table, storage_ix, storage);
      break;
    }

    default:
    {
      ;
      break;
    }

  }

  if (((*storage_ix) - initial_storage_ix) > (31 + (input_size << 3)))
  {
    RewindBitPosition(initial_storage_ix, storage_ix, storage);
    EmitUncompressedMetaBlock(input, input_size, storage_ix, storage);
  }
  if (is_last)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
  }
}


----------------------------
static int *GetHashTable(BrotliEncoderState *s, int quality, size_t input_size, size_t *table_size)
{
  MemoryManager *m = &s->memory_manager_;
  const size_t max_table_size = MaxHashTableSize(quality);
  size_t htsize = HashTableSize(max_table_size, input_size);
  int *table;
  unsigned int table_idx = 0;
  ;
  if (quality == 0)
  {
    if ((htsize & 0xAAAAA) == 0)
    {
      htsize <<= 1;
    }
  }
  if (htsize <= ((sizeof(s->small_table_)) / (sizeof(s->small_table_[0]))))
  {
    table_idx = s->small_table_;
  }
  else
  {
    if (htsize > s->large_table_size_)
    {
      s->large_table_size_ = htsize;
      {
        BrotliFree(m, s->large_table_);
        s->large_table_ = 0;
      }
      ;
      s->large_table_ = (htsize > 0) ? ((int *) BrotliAllocate(m, htsize * (sizeof(int)))) : (0);
      if ((!(!0)) || (!(!0)))
      {
        return 0;
      }
    }
    table_idx = s->large_table_;
  }
  *table_size = htsize;
  memset(table, 0, htsize * (sizeof(*(&table[table_idx]))));
  return table;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliCompressFragmentFast(MemoryManager *m, const uint8_t *input, size_t input_size, int is_last, int *table, size_t table_size, uint8_t cmd_depth[128], uint16_t cmd_bits[128], size_t *cmd_code_numbits, uint8_t *cmd_code, size_t *storage_ix, uint8_t *storage)
{
  const size_t initial_storage_ix = *storage_ix;
  const size_t table_bits = Log2FloorNonZero(table_size);
  if (input_size == 0)
  {
    ;
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
    return;
  }
  switch (table_bits)
  {
    case 9:
    {
      BrotliCompressFragmentFastImpl9(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 11:
    {
      BrotliCompressFragmentFastImpl11(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 13:
    {
      BrotliCompressFragmentFastImpl13(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    case 15:
    {
      BrotliCompressFragmentFastImpl15(m, input, input_size, is_last, table, cmd_depth, cmd_bits, cmd_code_numbits, cmd_code, storage_ix, storage);
      break;
    }

    default:
    {
      ;
      break;
    }

  }

  if (((*storage_ix) - initial_storage_ix) > (31 + (input_size << 3)))
  {
    EmitUncompressedMetaBlock(input, input + input_size, initial_storage_ix, storage_ix, storage);
  }
  if (is_last)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    *storage_ix = ((*storage_ix) + 7u) & (~7u);
  }
}


----------------------------
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation
----------------------------
***/


int helper_BrotliEncoderCompressStreamFast_2(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out, const size_t block_size_limit, uint32_t * const command_buf, uint8_t * const literal_buf, MemoryManager * const m)
{
  if (InjectFlushOrPushOutput(s, available_out, next_out, total_out))
  {
    continue;
  }
  if (((s->available_out_ == 0) && (s->stream_state_ == BROTLI_STREAM_PROCESSING)) && (((*available_in) != 0) || (op != BROTLI_OPERATION_PROCESS)))
  {
    helper_helper_BrotliEncoderCompressStreamFast_2_1(s, op, available_in, next_in, available_out, next_out, total_out, block_size_limit, command_buf, literal_buf, m);
  }
  break;
}


/*** DEPENDENCIES:
static int InjectFlushOrPushOutput(BrotliEncoderState *s, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->last_bytes_bits_ != 0))
  {
    InjectBytePaddingBlock(s);
    return 1;
  }
  if ((s->available_out_ != 0) && ((*available_out) != 0))
  {
    size_t copy_output_size = brotli_min_size_t(s->available_out_, *available_out);
    memcpy(*next_out, s->next_out_, copy_output_size);
    *next_out += copy_output_size;
    *available_out -= copy_output_size;
    s->next_out_ += copy_output_size;
    s->available_out_ -= copy_output_size;
    s->total_out_ += copy_output_size;
    if (total_out)
    {
      *total_out = s->total_out_;
    }
    return 1;
  }
  return 0;
}


----------------------------
int helper_helper_BrotliEncoderCompressStreamFast_2_1(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out, const size_t block_size_limit, uint32_t * const command_buf, uint8_t * const literal_buf, MemoryManager * const m)
{
  size_t block_size = brotli_min_size_t(block_size_limit, *available_in);
  int is_last = ((*available_in) == block_size) && (op == BROTLI_OPERATION_FINISH);
  int force_flush = ((*available_in) == block_size) && (op == BROTLI_OPERATION_FLUSH);
  size_t max_out_size = (2 * block_size) + 503;
  int inplace = 1;
  uint8_t *storage = 0;
  unsigned int storage_idx = 0;
  size_t storage_ix = s->last_bytes_bits_;
  size_t table_size;
  int *table;
  unsigned int table_idx = 0;
  if (force_flush && (block_size == 0))
  {
    s->stream_state_ = BROTLI_STREAM_FLUSH_REQUESTED;
    continue;
  }
  if (max_out_size <= (*available_out))
  {
    storage_idx = *next_out;
  }
  else
  {
    inplace = 0;
    storage_idx = GetBrotliStorage(s, max_out_size);
    if (!(!0))
    {
      return 0;
    }
  }
  storage[0 + storage_idx] = (uint8_t) s->last_bytes_;
  storage[1 + storage_idx] = (uint8_t) (s->last_bytes_ >> 8);
  table_idx = GetHashTable(s, s->params.quality, block_size, &table_size);
  if (!(!0))
  {
    return 0;
  }
  if (s->params.quality == 0)
  {
    BrotliCompressFragmentFast(m, *next_in, block_size, is_last, table, table_size, s->cmd_depths_, s->cmd_bits_, &s->cmd_code_numbits_, s->cmd_code_, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  else
  {
    BrotliCompressFragmentTwoPass(m, *next_in, block_size, is_last, command_buf, literal_buf, table, table_size, &storage_ix, storage);
    if (!(!0))
    {
      return 0;
    }
  }
  if (block_size != 0)
  {
    *next_in += block_size;
    *available_in -= block_size;
  }
  if (inplace)
  {
    size_t out_bytes = storage_ix >> 3;
    ;
    ;
    *next_out += out_bytes;
    *available_out -= out_bytes;
    s->total_out_ += out_bytes;
    if (total_out)
    {
      *total_out = s->total_out_;
    }
  }
  else
  {
    size_t out_bytes = storage_ix >> 3;
    s->next_out_ = &storage[storage_idx];
    s->available_out_ = out_bytes;
  }
  s->last_bytes_ = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  s->last_bytes_bits_ = storage_ix & 7u;
  if (force_flush)
  {
    s->stream_state_ = BROTLI_STREAM_FLUSH_REQUESTED;
  }
  if (is_last)
  {
    s->stream_state_ = BROTLI_STREAM_FINISHED;
  }
  continue;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation
----------------------------
***/


// hint:  ['tmp_command_buf_idx_ref is a mutable refrence to unsigned int', 'command_buf_idx_ref is a mutable refrence to unsigned int', 'tmp_literal_buf_idx_ref is a mutable refrence to unsigned int', 'literal_buf_idx_ref is a mutable refrence to unsigned int']
int helper_BrotliEncoderCompressStreamFast_1(unsigned int * const tmp_command_buf_idx_ref, unsigned int * const command_buf_idx_ref, unsigned int * const tmp_literal_buf_idx_ref, unsigned int * const literal_buf_idx_ref, BrotliEncoderState * const s, const size_t buf_size, uint32_t * const tmp_command_buf, uint8_t * const tmp_literal_buf, MemoryManager * const m)
{
  unsigned int tmp_command_buf_idx = *tmp_command_buf_idx_ref;
  unsigned int command_buf_idx = *command_buf_idx_ref;
  unsigned int tmp_literal_buf_idx = *tmp_literal_buf_idx_ref;
  unsigned int literal_buf_idx = *literal_buf_idx_ref;
  if ((!s->command_buf_) && (buf_size == kCompressFragmentTwoPassBlockSize))
  {
    s->command_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint32_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint32_t)))) : (0);
    s->literal_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint8_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
  }
  if (s->command_buf_)
  {
    command_buf_idx = s->command_buf_;
    literal_buf_idx = s->literal_buf_;
  }
  else
  {
    tmp_command_buf_idx = (buf_size > 0) ? ((uint32_t *) BrotliAllocate(m, buf_size * (sizeof(uint32_t)))) : (0);
    tmp_literal_buf_idx = (buf_size > 0) ? ((uint8_t *) BrotliAllocate(m, buf_size * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
    command_buf_idx = &tmp_command_buf[tmp_command_buf_idx];
    literal_buf_idx = &tmp_literal_buf[tmp_literal_buf_idx];
  }
  *tmp_command_buf_idx_ref = tmp_command_buf_idx;
  *command_buf_idx_ref = command_buf_idx;
  *tmp_literal_buf_idx_ref = tmp_literal_buf_idx;
  *literal_buf_idx_ref = literal_buf_idx;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static const size_t kCompressFragmentTwoPassBlockSize = 1 << 17
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
***/


static int BrotliEncoderCompressStreamFast(BrotliEncoderState *s, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  const size_t block_size_limit = ((size_t) 1) << s->params.lgwin;
  const size_t buf_size = brotli_min_size_t(kCompressFragmentTwoPassBlockSize, brotli_min_size_t(*available_in, block_size_limit));
  uint32_t *tmp_command_buf = 0;
  unsigned int tmp_command_buf_idx = 0;
  uint32_t *command_buf = 0;
  unsigned int command_buf_idx = 0;
  uint8_t *tmp_literal_buf = 0;
  unsigned int tmp_literal_buf_idx = 0;
  uint8_t *literal_buf = 0;
  unsigned int literal_buf_idx = 0;
  MemoryManager *m = &s->memory_manager_;
  if ((s->params.quality != 0) && (s->params.quality != 1))
  {
    return 0;
  }
  if (s->params.quality == 1)
  {
    helper_BrotliEncoderCompressStreamFast_1(&tmp_command_buf_idx, &command_buf_idx, &tmp_literal_buf_idx, &literal_buf_idx, s, buf_size, tmp_command_buf, tmp_literal_buf, m);
  }
  while (1)
  {
    helper_BrotliEncoderCompressStreamFast_2(s, op, available_in, next_in, available_out, next_out, total_out, block_size_limit, command_buf, literal_buf, m);
  }

  {
    BrotliFree(m, tmp_command_buf);
    tmp_command_buf_idx = 0;
  }
  ;
  {
    BrotliFree(m, tmp_literal_buf);
    tmp_literal_buf_idx = 0;
  }
  ;
  CheckFlushComplete(s);
  return 1;
}


/*** DEPENDENCIES:
static const size_t kCompressFragmentTwoPassBlockSize = 1 << 17
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
int helper_BrotliEncoderCompressStreamFast_2(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out, const size_t block_size_limit, uint32_t * const command_buf, uint8_t * const literal_buf, MemoryManager * const m)
{
  if (InjectFlushOrPushOutput(s, available_out, next_out, total_out))
  {
    continue;
  }
  if (((s->available_out_ == 0) && (s->stream_state_ == BROTLI_STREAM_PROCESSING)) && (((*available_in) != 0) || (op != BROTLI_OPERATION_PROCESS)))
  {
    helper_helper_BrotliEncoderCompressStreamFast_2_1(s, op, available_in, next_in, available_out, next_out, total_out, block_size_limit, command_buf, literal_buf, m);
  }
  break;
}


----------------------------
int helper_BrotliEncoderCompressStreamFast_1(unsigned int * const tmp_command_buf_idx_ref, unsigned int * const command_buf_idx_ref, unsigned int * const tmp_literal_buf_idx_ref, unsigned int * const literal_buf_idx_ref, BrotliEncoderState * const s, const size_t buf_size, uint32_t * const tmp_command_buf, uint8_t * const tmp_literal_buf, MemoryManager * const m)
{
  unsigned int tmp_command_buf_idx = *tmp_command_buf_idx_ref;
  unsigned int command_buf_idx = *command_buf_idx_ref;
  unsigned int tmp_literal_buf_idx = *tmp_literal_buf_idx_ref;
  unsigned int literal_buf_idx = *literal_buf_idx_ref;
  if ((!s->command_buf_) && (buf_size == kCompressFragmentTwoPassBlockSize))
  {
    s->command_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint32_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint32_t)))) : (0);
    s->literal_buf_ = (kCompressFragmentTwoPassBlockSize > 0) ? ((uint8_t *) BrotliAllocate(m, kCompressFragmentTwoPassBlockSize * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
  }
  if (s->command_buf_)
  {
    command_buf_idx = s->command_buf_;
    literal_buf_idx = s->literal_buf_;
  }
  else
  {
    tmp_command_buf_idx = (buf_size > 0) ? ((uint32_t *) BrotliAllocate(m, buf_size * (sizeof(uint32_t)))) : (0);
    tmp_literal_buf_idx = (buf_size > 0) ? ((uint8_t *) BrotliAllocate(m, buf_size * (sizeof(uint8_t)))) : (0);
    if (((!(!0)) || (!(!0))) || (!(!0)))
    {
      return 0;
    }
    command_buf_idx = &tmp_command_buf[tmp_command_buf_idx];
    literal_buf_idx = &tmp_literal_buf[tmp_literal_buf_idx];
  }
  *tmp_command_buf_idx_ref = tmp_command_buf_idx;
  *command_buf_idx_ref = command_buf_idx;
  *tmp_literal_buf_idx_ref = tmp_literal_buf_idx;
  *literal_buf_idx_ref = literal_buf_idx;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
static void CheckFlushComplete(BrotliEncoderState *s)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->available_out_ == 0))
  {
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    s->next_out_ = 0;
  }
}


----------------------------
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation
----------------------------
***/


int BrotliEncoderCompressStream(BrotliEncoderState *s, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if (!EnsureInitialized(s))
  {
    return 0;
  }
  if (s->remaining_metadata_bytes_ != (~((uint32_t) 0)))
  {
    if ((*available_in) != s->remaining_metadata_bytes_)
    {
      return 0;
    }
    if (op != BROTLI_OPERATION_EMIT_METADATA)
    {
      return 0;
    }
  }
  if (op == BROTLI_OPERATION_EMIT_METADATA)
  {
    UpdateSizeHint(s, 0);
    return ProcessMetadata(s, available_in, next_in, available_out, next_out, total_out);
  }
  if ((s->stream_state_ == BROTLI_STREAM_METADATA_HEAD) || (s->stream_state_ == BROTLI_STREAM_METADATA_BODY))
  {
    return 0;
  }
  if ((s->stream_state_ != BROTLI_STREAM_PROCESSING) && ((*available_in) != 0))
  {
    return 0;
  }
  if ((s->params.quality == 0) || (s->params.quality == 1))
  {
    return BrotliEncoderCompressStreamFast(s, op, available_in, next_in, available_out, next_out, total_out);
  }
  while (1)
  {
    helper_BrotliEncoderCompressStream_1(s, op, available_in, next_in, available_out, next_out, total_out);
  }

  CheckFlushComplete(s);
  return 1;
}


/*** DEPENDENCIES:
int helper_BrotliEncoderCompressStream_1(BrotliEncoderState * const s, BrotliEncoderOperation op, size_t * const available_in, const uint8_t ** const next_in, size_t * const available_out, uint8_t ** const next_out, size_t * const total_out)
{
  size_t remaining_block_size = RemainingInputBlockSize(s);
  if ((s->flint_ >= 0) && (remaining_block_size > ((size_t) s->flint_)))
  {
    remaining_block_size = (size_t) s->flint_;
  }
  if ((remaining_block_size != 0) && ((*available_in) != 0))
  {
    size_t copy_input_size = brotli_min_size_t(remaining_block_size, *available_in);
    CopyInputToRingBuffer(s, copy_input_size, *next_in);
    *next_in += copy_input_size;
    *available_in -= copy_input_size;
    if (s->flint_ > 0)
    {
      s->flint_ = (int8_t) (s->flint_ - ((int) copy_input_size));
    }
    continue;
  }
  if (InjectFlushOrPushOutput(s, available_out, next_out, total_out))
  {
    if (s->flint_ == BROTLI_FLINT_WAITING_FOR_FLUSHING)
    {
      CheckFlushComplete(s);
      if (s->stream_state_ == BROTLI_STREAM_PROCESSING)
      {
        s->flint_ = BROTLI_FLINT_DONE;
      }
    }
    continue;
  }
  if ((s->available_out_ == 0) && (s->stream_state_ == BROTLI_STREAM_PROCESSING))
  {
    helper_helper_BrotliEncoderCompressStream_1_1(s, op, available_in, remaining_block_size);
  }
  break;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int EnsureInitialized(BrotliEncoderState *s)
{
  if (!(!0))
  {
    return 0;
  }
  if (s->is_initialized_)
  {
    return 1;
  }
  s->last_bytes_bits_ = 0;
  s->last_bytes_ = 0;
  s->flint_ = BROTLI_FLINT_DONE;
  s->remaining_metadata_bytes_ = ~((uint32_t) 0);
  SanitizeParams(&s->params);
  s->params.lgblock = ComputeLgBlock(&s->params);
  ChooseDistanceParams(&s->params);
  if (s->params.stream_offset != 0)
  {
    s->flint_ = BROTLI_FLINT_NEEDS_2_BYTES;
    s->dist_cache_[0] = -16;
    s->dist_cache_[1] = -16;
    s->dist_cache_[2] = -16;
    s->dist_cache_[3] = -16;
    memcpy(s->saved_dist_cache_, s->dist_cache_, sizeof(s->saved_dist_cache_));
  }
  RingBufferSetup(&s->params, &s->ringbuffer_);
  {
    int lgwin = s->params.lgwin;
    if ((s->params.quality == 0) || (s->params.quality == 1))
    {
      lgwin = brotli_max_int(lgwin, 18);
    }
    if (s->params.stream_offset == 0)
    {
      EncodeWindowBits(lgwin, s->params.large_window, &s->last_bytes_, &s->last_bytes_bits_);
    }
    else
    {
      s->params.stream_offset = brotli_min_size_t(s->params.stream_offset, (((size_t) 1) << lgwin) - 16);
    }
  }
  if (s->params.quality == 0)
  {
    InitCommandPrefixCodes(s->cmd_depths_, s->cmd_bits_, s->cmd_code_, &s->cmd_code_numbits_);
  }
  s->is_initialized_ = 1;
  return 1;
}


----------------------------
static void UpdateSizeHint(BrotliEncoderState *s, size_t available_in)
{
  if (s->params.size_hint == 0)
  {
    uint64_t delta = UnprocessedInputSize(s);
    uint64_t tail = available_in;
    uint32_t limit = 1u << 30;
    uint32_t total;
    if (((delta >= limit) || (tail >= limit)) || ((delta + tail) >= limit))
    {
      total = limit;
    }
    else
    {
      total = (uint32_t) (delta + tail);
    }
    s->params.size_hint = total;
  }
}


----------------------------
static int BrotliEncoderCompressStreamFast(BrotliEncoderState *s, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  const size_t block_size_limit = ((size_t) 1) << s->params.lgwin;
  const size_t buf_size = brotli_min_size_t(kCompressFragmentTwoPassBlockSize, brotli_min_size_t(*available_in, block_size_limit));
  uint32_t *tmp_command_buf = 0;
  unsigned int tmp_command_buf_idx = 0;
  uint32_t *command_buf = 0;
  unsigned int command_buf_idx = 0;
  uint8_t *tmp_literal_buf = 0;
  unsigned int tmp_literal_buf_idx = 0;
  uint8_t *literal_buf = 0;
  unsigned int literal_buf_idx = 0;
  MemoryManager *m = &s->memory_manager_;
  if ((s->params.quality != 0) && (s->params.quality != 1))
  {
    return 0;
  }
  if (s->params.quality == 1)
  {
    helper_BrotliEncoderCompressStreamFast_1(&tmp_command_buf_idx, &command_buf_idx, &tmp_literal_buf_idx, &literal_buf_idx, s, buf_size, tmp_command_buf, tmp_literal_buf, m);
  }
  while (1)
  {
    helper_BrotliEncoderCompressStreamFast_2(s, op, available_in, next_in, available_out, next_out, total_out, block_size_limit, command_buf, literal_buf, m);
  }

  {
    BrotliFree(m, tmp_command_buf);
    tmp_command_buf_idx = 0;
  }
  ;
  {
    BrotliFree(m, tmp_literal_buf);
    tmp_literal_buf_idx = 0;
  }
  ;
  CheckFlushComplete(s);
  return 1;
}


----------------------------
static void CheckFlushComplete(BrotliEncoderState *s)
{
  if ((s->stream_state_ == BROTLI_STREAM_FLUSH_REQUESTED) && (s->available_out_ == 0))
  {
    s->stream_state_ = BROTLI_STREAM_PROCESSING;
    s->next_out_ = 0;
  }
}


----------------------------
static int ProcessMetadata(BrotliEncoderState *s, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if ((*available_in) > (1u << 24))
  {
    return 0;
  }
  if (s->stream_state_ == BROTLI_STREAM_PROCESSING)
  {
    s->remaining_metadata_bytes_ = (uint32_t) (*available_in);
    s->stream_state_ = BROTLI_STREAM_METADATA_HEAD;
  }
  if ((s->stream_state_ != BROTLI_STREAM_METADATA_HEAD) && (s->stream_state_ != BROTLI_STREAM_METADATA_BODY))
  {
    return 0;
  }
  while (1)
  {
    helper_ProcessMetadata_1(s, available_in, next_in, available_out, next_out, total_out);
  }

  return 1;
}


----------------------------
typedef enum BrotliEncoderOperation
{
  BROTLI_OPERATION_PROCESS = 0,
  BROTLI_OPERATION_FLUSH = 1,
  BROTLI_OPERATION_FINISH = 2,
  BROTLI_OPERATION_EMIT_METADATA = 3
} BrotliEncoderOperation
----------------------------
***/


static void BrotliEncoderCleanupState(BrotliEncoderState *s)
{
  MemoryManager *m = &s->memory_manager_;
  if (!(!0))
  {
    BrotliWipeOutMemoryManager(m);
    return;
  }
  {
    BrotliFree(m, s->storage_);
    s->storage_ = 0;
  }
  ;
  {
    BrotliFree(m, s->commands_);
    s->commands_ = 0;
  }
  ;
  RingBufferFree(m, &s->ringbuffer_);
  DestroyHasher(m, &s->hasher_);
  {
    BrotliFree(m, s->large_table_);
    s->large_table_ = 0;
  }
  ;
  {
    BrotliFree(m, s->command_buf_);
    s->command_buf_ = 0;
  }
  ;
  {
    BrotliFree(m, s->literal_buf_);
    s->literal_buf_ = 0;
  }
  ;
}


/*** DEPENDENCIES:
void BrotliWipeOutMemoryManager(MemoryManager *m)
{
  (void) m;
}


----------------------------
inline static void DestroyHasher(MemoryManager *m, Hasher *hasher)
{
  if (hasher->common.extra == 0)
  {
    return;
  }
  {
    BrotliFree(m, hasher->common.extra);
    hasher->common.extra = 0;
  }
  ;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
inline static void RingBufferFree(MemoryManager *m, RingBuffer *rb)
{
  {
    BrotliFree(m, rb->data_);
    rb->data_ = 0;
  }
  ;
}


----------------------------
***/


void BrotliEncoderDestroyInstance(BrotliEncoderState *state)
{
  if (!state)
  {
    return;
  }
  else
  {
    MemoryManager *m = &state->memory_manager_;
    brotli_free_func free_func = m->free_func;
    void *opaque = m->opaque;
    BrotliEncoderCleanupState(state);
    free_func(opaque, state);
  }
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static void BrotliEncoderCleanupState(BrotliEncoderState *s)
{
  MemoryManager *m = &s->memory_manager_;
  if (!(!0))
  {
    BrotliWipeOutMemoryManager(m);
    return;
  }
  {
    BrotliFree(m, s->storage_);
    s->storage_ = 0;
  }
  ;
  {
    BrotliFree(m, s->commands_);
    s->commands_ = 0;
  }
  ;
  RingBufferFree(m, &s->ringbuffer_);
  DestroyHasher(m, &s->hasher_);
  {
    BrotliFree(m, s->large_table_);
    s->large_table_ = 0;
  }
  ;
  {
    BrotliFree(m, s->command_buf_);
    s->command_buf_ = 0;
  }
  ;
  {
    BrotliFree(m, s->literal_buf_);
    s->literal_buf_ = 0;
  }
  ;
}


----------------------------
typedef void (*brotli_free_func)(void *opaque, void *address)
----------------------------
***/


// hint:  ['commands_idx_ref is a mutable refrence to unsigned int', 'cmd_alloc_size_ref is a mutable refrence to size_t']
void helper_helper_helper_BrotliCompressBufferQuality10_1_2_1(unsigned int * const commands_idx_ref, size_t * const cmd_alloc_size_ref, MemoryManager * const m, Command * const commands, size_t num_commands, size_t new_cmd_alloc_size)
{
  unsigned int commands_idx = *commands_idx_ref;
  size_t cmd_alloc_size = *cmd_alloc_size_ref;
  Command *new_commands = (new_cmd_alloc_size > 0) ? ((Command *) BrotliAllocate(m, new_cmd_alloc_size * (sizeof(Command)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    goto oom;
  }
  cmd_alloc_size = new_cmd_alloc_size;
  if (commands)
  {
    memcpy(new_commands, commands, (sizeof(Command)) * num_commands);
    {
      BrotliFree(m, commands);
      commands_idx = 0;
    }
    ;
  }
  commands_idx = new_commands;
  *commands_idx_ref = commands_idx;
  *cmd_alloc_size_ref = cmd_alloc_size;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


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
***/


int helper_BrotliEncoderCompress_1(int quality, int lgwin, BrotliEncoderMode mode, size_t input_size, const uint8_t * const input_buffer, size_t * const encoded_size, uint8_t * const encoded_buffer, BrotliEncoderState * const s, size_t max_out_size)
{
  size_t available_in = input_size;
  const uint8_t *next_in = input_buffer;
  size_t available_out = *encoded_size;
  uint8_t *next_out = encoded_buffer;
  size_t total_out = 0;
  int result = 0;
  BrotliEncoderSetParameter(s, BROTLI_PARAM_QUALITY, (uint32_t) quality);
  BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, (uint32_t) lgwin);
  BrotliEncoderSetParameter(s, BROTLI_PARAM_MODE, (uint32_t) mode);
  BrotliEncoderSetParameter(s, BROTLI_PARAM_SIZE_HINT, (uint32_t) input_size);
  if (lgwin > 24)
  {
    BrotliEncoderSetParameter(s, BROTLI_PARAM_LARGE_WINDOW, 1);
  }
  result = BrotliEncoderCompressStream(s, BROTLI_OPERATION_FINISH, &available_in, &next_in, &available_out, &next_out, &total_out);
  if (!BrotliEncoderIsFinished(s))
  {
    result = 0;
  }
  *encoded_size = total_out;
  BrotliEncoderDestroyInstance(s);
  if ((!result) || (max_out_size && ((*encoded_size) > max_out_size)))
  {
    goto fallback;
  }
  return 1;
}


/*** DEPENDENCIES:
int BrotliEncoderIsFinished(BrotliEncoderState *s)
{
  return (!(!((s->stream_state_ == BROTLI_STREAM_FINISHED) && (!BrotliEncoderHasMoreOutput(s))))) ? (1) : (0);
}


----------------------------
typedef enum BrotliEncoderMode
{
  BROTLI_MODE_GENERIC = 0,
  BROTLI_MODE_TEXT = 1,
  BROTLI_MODE_FONT = 2
} BrotliEncoderMode
----------------------------
int BrotliEncoderCompressStream(BrotliEncoderState *s, BrotliEncoderOperation op, size_t *available_in, const uint8_t **next_in, size_t *available_out, uint8_t **next_out, size_t *total_out)
{
  if (!EnsureInitialized(s))
  {
    return 0;
  }
  if (s->remaining_metadata_bytes_ != (~((uint32_t) 0)))
  {
    if ((*available_in) != s->remaining_metadata_bytes_)
    {
      return 0;
    }
    if (op != BROTLI_OPERATION_EMIT_METADATA)
    {
      return 0;
    }
  }
  if (op == BROTLI_OPERATION_EMIT_METADATA)
  {
    UpdateSizeHint(s, 0);
    return ProcessMetadata(s, available_in, next_in, available_out, next_out, total_out);
  }
  if ((s->stream_state_ == BROTLI_STREAM_METADATA_HEAD) || (s->stream_state_ == BROTLI_STREAM_METADATA_BODY))
  {
    return 0;
  }
  if ((s->stream_state_ != BROTLI_STREAM_PROCESSING) && ((*available_in) != 0))
  {
    return 0;
  }
  if ((s->params.quality == 0) || (s->params.quality == 1))
  {
    return BrotliEncoderCompressStreamFast(s, op, available_in, next_in, available_out, next_out, total_out);
  }
  while (1)
  {
    helper_BrotliEncoderCompressStream_1(s, op, available_in, next_in, available_out, next_out, total_out);
  }

  CheckFlushComplete(s);
  return 1;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
int BrotliEncoderSetParameter(BrotliEncoderState *state, BrotliEncoderParameter p, uint32_t value)
{
  if (state->is_initialized_)
  {
    return 0;
  }
  switch (p)
  {
    case BROTLI_PARAM_MODE:
    {
      state->params.mode = (BrotliEncoderMode) value;
      return 1;
    }

    case BROTLI_PARAM_QUALITY:
    {
      state->params.quality = (int) value;
      return 1;
    }

    case BROTLI_PARAM_LGWIN:
    {
      state->params.lgwin = (int) value;
      return 1;
    }

    case BROTLI_PARAM_LGBLOCK:
    {
      state->params.lgblock = (int) value;
      return 1;
    }

    case BROTLI_PARAM_DISABLE_LITERAL_CONTEXT_MODELING:
    {
      if ((value != 0) && (value != 1))
      {
        return 0;
      }
      state->params.disable_literal_context_modeling = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    case BROTLI_PARAM_SIZE_HINT:
    {
      state->params.size_hint = value;
      return 1;
    }

    case BROTLI_PARAM_LARGE_WINDOW:
    {
      state->params.large_window = (!(!(!(!value)))) ? (1) : (0);
      return 1;
    }

    case BROTLI_PARAM_NPOSTFIX:
    {
      state->params.dist.distance_postfix_bits = value;
      return 1;
    }

    case BROTLI_PARAM_NDIRECT:
    {
      state->params.dist.num_direct_distance_codes = value;
      return 1;
    }

    case BROTLI_PARAM_STREAM_OFFSET:
    {
      if (value > (1u << 30))
      {
        return 0;
      }
      state->params.stream_offset = value;
      return 1;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
void BrotliEncoderDestroyInstance(BrotliEncoderState *state)
{
  if (!state)
  {
    return;
  }
  else
  {
    MemoryManager *m = &state->memory_manager_;
    brotli_free_func free_func = m->free_func;
    void *opaque = m->opaque;
    BrotliEncoderCleanupState(state);
    free_func(opaque, state);
  }
}


----------------------------
***/


// hint:  ['storage_idx_ref is a mutable refrence to unsigned int', 'storage_ix_ref is a mutable refrence to size_t']
void helper_helper_BrotliCompressBufferQuality10_1_1(unsigned int * const storage_idx_ref, size_t * const storage_ix_ref, const uint8_t * const input_buffer, MemoryManager * const m, const size_t mask, int dist_cache[4], int saved_dist_cache[4], BrotliEncoderParams params, uint16_t last_bytes, uint8_t last_bytes_bits, size_t metablock_start, uint8_t prev_byte, uint8_t prev_byte2, Command * const commands, size_t num_commands, size_t metablock_size, int is_last, uint8_t * const storage, ContextType literal_context_mode)
{
  unsigned int storage_idx = *storage_idx_ref;
  size_t storage_ix = *storage_ix_ref;
  MetaBlockSplit mb;
  BrotliEncoderParams block_params = params;
  InitMetaBlockSplit(&mb);
  BrotliBuildMetaBlock(m, input_buffer, metablock_start, mask, &block_params, prev_byte, prev_byte2, commands, num_commands, literal_context_mode, &mb);
  if (!(!0))
  {
    goto oom;
  }
  {
    BrotliOptimizeHistograms(block_params.dist.alphabet_size_limit, &mb);
  }
  storage_idx = (((2 * metablock_size) + 503) > 0) ? ((uint8_t *) BrotliAllocate(m, ((2 * metablock_size) + 503) * (sizeof(uint8_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    goto oom;
  }
  storage[0 + storage_idx] = (uint8_t) last_bytes;
  storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
  BrotliStoreMetaBlock(m, input_buffer, metablock_start, metablock_size, mask, prev_byte, prev_byte2, is_last, &block_params, literal_context_mode, commands, num_commands, &mb, &storage_ix, storage);
  if (!(!0))
  {
    goto oom;
  }
  if ((metablock_size + 4) < (storage_ix >> 3))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    storage[0 + storage_idx] = (uint8_t) last_bytes;
    storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
    storage_ix = last_bytes_bits;
    BrotliStoreUncompressedMetaBlock(is_last, input_buffer, metablock_start, mask, metablock_size, &storage_ix, storage);
  }
  DestroyMetaBlockSplit(m, &mb);
  *storage_idx_ref = storage_idx;
  *storage_ix_ref = storage_ix;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
inline static void InitMetaBlockSplit(MetaBlockSplit *mb)
{
  BrotliInitBlockSplit(&mb->literal_split);
  BrotliInitBlockSplit(&mb->command_split);
  BrotliInitBlockSplit(&mb->distance_split);
  mb->literal_context_map = 0;
  mb->literal_context_map_size = 0;
  mb->distance_context_map = 0;
  mb->distance_context_map_size = 0;
  mb->literal_histograms = 0;
  mb->literal_histograms_size = 0;
  mb->command_histograms = 0;
  mb->command_histograms_size = 0;
  mb->distance_histograms = 0;
  mb->distance_histograms_size = 0;
}


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
void BrotliStoreUncompressedMetaBlock(int is_final_block, const uint8_t * restrict input, size_t position, size_t mask, size_t len, size_t * restrict storage_ix, uint8_t * restrict storage)
{
  size_t masked_pos = position & mask;
  BrotliStoreUncompressedMetaBlockHeader(len, storage_ix, storage);
  JumpToByteBoundary(storage_ix, storage);
  if ((masked_pos + len) > (mask + 1))
  {
    size_t len1 = (mask + 1) - masked_pos;
    memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len1);
    *storage_ix += len1 << 3;
    len -= len1;
    masked_pos = 0;
  }
  memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len);
  *storage_ix += len << 3;
  BrotliWriteBitsPrepareStorage(*storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    JumpToByteBoundary(storage_ix, storage);
  }
}


----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
inline static void DestroyMetaBlockSplit(MemoryManager *m, MetaBlockSplit *mb)
{
  BrotliDestroyBlockSplit(m, &mb->literal_split);
  BrotliDestroyBlockSplit(m, &mb->command_split);
  BrotliDestroyBlockSplit(m, &mb->distance_split);
  {
    BrotliFree(m, mb->literal_context_map);
    mb->literal_context_map = 0;
  }
  ;
  {
    BrotliFree(m, mb->distance_context_map);
    mb->distance_context_map = 0;
  }
  ;
  {
    BrotliFree(m, mb->literal_histograms);
    mb->literal_histograms = 0;
  }
  ;
  {
    BrotliFree(m, mb->command_histograms);
    mb->command_histograms = 0;
  }
  ;
  {
    BrotliFree(m, mb->distance_histograms);
    mb->distance_histograms = 0;
  }
  ;
}


----------------------------
void BrotliStoreMetaBlock(MemoryManager *m, const uint8_t *input, size_t start_pos, size_t length, size_t mask, uint8_t prev_byte, uint8_t prev_byte2, int is_last, const BrotliEncoderParams *params, ContextType literal_context_mode, const Command *commands, size_t n_commands, const MetaBlockSplit *mb, size_t *storage_ix, uint8_t *storage)
{
  size_t pos = start_pos;
  size_t i;
  uint32_t num_distance_symbols = params->dist.alphabet_size_max;
  uint32_t num_effective_distance_symbols = params->dist.alphabet_size_limit;
  HuffmanTree *tree;
  unsigned int tree_idx = 0;
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  BlockEncoder literal_enc;
  BlockEncoder command_enc;
  BlockEncoder distance_enc;
  const BrotliDistanceParams *dist = &params->dist;
  ;
  StoreCompressedMetaBlockHeader(is_last, length, storage_ix, storage);
  tree_idx = (((2 * 704) + 1) > 0) ? ((HuffmanTree *) BrotliAllocate(m, ((2 * 704) + 1) * (sizeof(HuffmanTree)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitBlockEncoder(&literal_enc, 256, mb->literal_split.num_types, mb->literal_split.types, mb->literal_split.lengths, mb->literal_split.num_blocks);
  InitBlockEncoder(&command_enc, 704, mb->command_split.num_types, mb->command_split.types, mb->command_split.lengths, mb->command_split.num_blocks);
  InitBlockEncoder(&distance_enc, num_effective_distance_symbols, mb->distance_split.num_types, mb->distance_split.types, mb->distance_split.lengths, mb->distance_split.num_blocks);
  BuildAndStoreBlockSwitchEntropyCodes(&literal_enc, tree, storage_ix, storage);
  BuildAndStoreBlockSwitchEntropyCodes(&command_enc, tree, storage_ix, storage);
  BuildAndStoreBlockSwitchEntropyCodes(&distance_enc, tree, storage_ix, storage);
  BrotliWriteBits(2, dist->distance_postfix_bits, storage_ix, storage);
  BrotliWriteBits(4, dist->num_direct_distance_codes >> dist->distance_postfix_bits, storage_ix, storage);
  for (i = 0; i < mb->literal_split.num_types; i += 1)
  {
    BrotliWriteBits(2, literal_context_mode, storage_ix, storage);
  }

  if (mb->literal_context_map_size == 0)
  {
    StoreTrivialContextMap(mb->literal_histograms_size, 6, tree, storage_ix, storage);
  }
  else
  {
    EncodeContextMap(m, mb->literal_context_map, mb->literal_context_map_size, mb->literal_histograms_size, tree, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  if (mb->distance_context_map_size == 0)
  {
    StoreTrivialContextMap(mb->distance_histograms_size, 2, tree, storage_ix, storage);
  }
  else
  {
    EncodeContextMap(m, mb->distance_context_map, mb->distance_context_map_size, mb->distance_histograms_size, tree, storage_ix, storage);
    if (!(!0))
    {
      return;
    }
  }
  BuildAndStoreEntropyCodesLiteral(m, &literal_enc, mb->literal_histograms, mb->literal_histograms_size, 256, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreEntropyCodesCommand(m, &command_enc, mb->command_histograms, mb->command_histograms_size, 704, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  BuildAndStoreEntropyCodesDistance(m, &distance_enc, mb->distance_histograms, mb->distance_histograms_size, num_distance_symbols, tree, storage_ix, storage);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, tree);
    tree_idx = 0;
  }
  ;
  for (i = 0; i < n_commands; i += 1)
  {
    helper_BrotliStoreMetaBlock_1(&prev_byte, &prev_byte2, &pos, input, mask, commands, mb, storage_ix, storage, i, literal_context_lut, literal_enc, command_enc, distance_enc);
  }

  CleanupBlockEncoder(m, &distance_enc);
  CleanupBlockEncoder(m, &command_enc);
  CleanupBlockEncoder(m, &literal_enc);
  if (is_last)
  {
    JumpToByteBoundary(storage_ix, storage);
  }
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliBuildMetaBlock(MemoryManager *m, const uint8_t *ringbuffer, const size_t pos, const size_t mask, BrotliEncoderParams *params, uint8_t prev_byte, uint8_t prev_byte2, Command *cmds, size_t num_commands, ContextType literal_context_mode, MetaBlockSplit *mb)
{
  static const size_t kMaxNumberOfHistograms = 256;
  HistogramDistance *distance_histograms;
  unsigned int distance_histograms_idx = 0;
  HistogramLiteral *literal_histograms;
  unsigned int literal_histograms_idx = 0;
  ContextType *literal_context_modes = 0;
  unsigned int literal_context_modes_idx = 0;
  size_t literal_histograms_size;
  size_t distance_histograms_size;
  size_t i;
  size_t literal_context_multiplier = 1;
  uint32_t npostfix;
  uint32_t ndirect_msb = 0;
  int check_orig = 1;
  double best_dist_cost = 1e99;
  BrotliEncoderParams orig_params = *params;
  BrotliEncoderParams new_params = *params;
  for (npostfix = 0; npostfix <= 3; npostfix += 1)
  {
    helper_BrotliBuildMetaBlock_1(&ndirect_msb, &check_orig, &best_dist_cost, params, cmds, num_commands, npostfix, orig_params, new_params);
  }

  if (check_orig)
  {
    double dist_cost;
    ComputeDistanceCost(cmds, num_commands, &orig_params.dist, &orig_params.dist, &dist_cost);
    if (dist_cost < best_dist_cost)
    {
      params->dist = orig_params.dist;
    }
  }
  RecomputeDistancePrefixes(cmds, num_commands, &orig_params.dist, &params->dist);
  BrotliSplitBlock(m, cmds, num_commands, ringbuffer, pos, mask, params, &mb->literal_split, &mb->command_split, &mb->distance_split);
  if (!(!0))
  {
    return;
  }
  if (!params->disable_literal_context_modeling)
  {
    literal_context_multiplier = 1 << 6;
    literal_context_modes_idx = (mb->literal_split.num_types > 0) ? ((ContextType *) BrotliAllocate(m, mb->literal_split.num_types * (sizeof(ContextType)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      return;
    }
    for (i = 0; i < mb->literal_split.num_types; i += 1)
    {
      literal_context_modes[i + literal_context_modes_idx] = literal_context_mode;
    }

  }
  literal_histograms_size = mb->literal_split.num_types * literal_context_multiplier;
  literal_histograms_idx = (literal_histograms_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, literal_histograms_size * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsLiteral(literal_histograms, literal_histograms_size);
  distance_histograms_size = mb->distance_split.num_types << 2;
  distance_histograms_idx = (distance_histograms_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, distance_histograms_size * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsDistance(distance_histograms, distance_histograms_size);
  ;
  mb->command_histograms_size = mb->command_split.num_types;
  mb->command_histograms = (mb->command_histograms_size > 0) ? ((HistogramCommand *) BrotliAllocate(m, mb->command_histograms_size * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ClearHistogramsCommand(mb->command_histograms, mb->command_histograms_size);
  BrotliBuildHistogramsWithContext(cmds, num_commands, &mb->literal_split, &mb->command_split, &mb->distance_split, ringbuffer, pos, mask, prev_byte, prev_byte2, literal_context_modes, literal_histograms, mb->command_histograms, distance_histograms);
  {
    BrotliFree(m, literal_context_modes);
    literal_context_modes_idx = 0;
  }
  ;
  ;
  mb->literal_context_map_size = mb->literal_split.num_types << 6;
  mb->literal_context_map = (mb->literal_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->literal_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ;
  mb->literal_histograms_size = mb->literal_context_map_size;
  mb->literal_histograms = (mb->literal_histograms_size > 0) ? ((HistogramLiteral *) BrotliAllocate(m, mb->literal_histograms_size * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliClusterHistogramsLiteral(m, literal_histograms, literal_histograms_size, kMaxNumberOfHistograms, mb->literal_histograms, &mb->literal_histograms_size, mb->literal_context_map);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, literal_histograms);
    literal_histograms_idx = 0;
  }
  ;
  if (params->disable_literal_context_modeling)
  {
    for (i = mb->literal_split.num_types; i != 0;)
    {
      size_t j = 0;
      i -= 1;
      for (; j < (1 << 6); j += 1)
      {
        mb->literal_context_map[(i << 6) + j] = mb->literal_context_map[i];
      }

    }

  }
  ;
  mb->distance_context_map_size = mb->distance_split.num_types << 2;
  mb->distance_context_map = (mb->distance_context_map_size > 0) ? ((uint32_t *) BrotliAllocate(m, mb->distance_context_map_size * (sizeof(uint32_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  ;
  mb->distance_histograms_size = mb->distance_context_map_size;
  mb->distance_histograms = (mb->distance_histograms_size > 0) ? ((HistogramDistance *) BrotliAllocate(m, mb->distance_histograms_size * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliClusterHistogramsDistance(m, distance_histograms, mb->distance_context_map_size, kMaxNumberOfHistograms, mb->distance_histograms, &mb->distance_histograms_size, mb->distance_context_map);
  if (!(!0))
  {
    return;
  }
  {
    BrotliFree(m, distance_histograms);
    distance_histograms_idx = 0;
  }
  ;
}


----------------------------
void BrotliOptimizeHistograms(uint32_t num_distance_codes, MetaBlockSplit *mb)
{
  uint8_t good_for_rle[704];
  size_t i;
  for (i = 0; i < mb->literal_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(256, mb->literal_histograms[i].data_, good_for_rle);
  }

  for (i = 0; i < mb->command_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(704, mb->command_histograms[i].data_, good_for_rle);
  }

  for (i = 0; i < mb->distance_histograms_size; i += 1)
  {
    BrotliOptimizeHuffmanCountsForRle(num_distance_codes, mb->distance_histograms[i].data_, good_for_rle);
  }

}


----------------------------
None
----------------------------
***/


// hint:  ['commands_idx_ref is a mutable refrence to unsigned int', 'num_commands_ref is a mutable refrence to size_t', 'metablock_size_ref is a mutable refrence to size_t', 'cmd_alloc_size_ref is a mutable refrence to size_t', 'block_start_ref is a mutable refrence to size_t']
void helper_helper_BrotliCompressBufferQuality10_1_2(unsigned int * const commands_idx_ref, size_t * const num_commands_ref, size_t * const metablock_size_ref, size_t * const cmd_alloc_size_ref, size_t * const block_start_ref, const uint8_t * const input_buffer, MemoryManager * const m, const size_t mask, int dist_cache[4], BrotliEncoderParams params, size_t max_block_size, const size_t max_literals_per_metablock, const size_t max_commands_per_metablock, Hasher hasher, const size_t metablock_end, const size_t expected_num_commands, Command * const commands, size_t last_insert_len, size_t num_literals, ContextLut literal_context_lut)
{
  unsigned int commands_idx = *commands_idx_ref;
  size_t num_commands = *num_commands_ref;
  size_t metablock_size = *metablock_size_ref;
  size_t cmd_alloc_size = *cmd_alloc_size_ref;
  size_t block_start = *block_start_ref;
  size_t block_size = brotli_min_size_t(metablock_end - block_start, max_block_size);
  ZopfliNode *nodes = ((block_size + 1) > 0) ? ((ZopfliNode *) BrotliAllocate(m, (block_size + 1) * (sizeof(ZopfliNode)))) : (0);
  unsigned int nodes_idx = 0;
  size_t path_size;
  size_t new_cmd_alloc_size;
  if ((!(!0)) || (!(!0)))
  {
    goto oom;
  }
  BrotliInitZopfliNodes(nodes, block_size + 1);
  StitchToPreviousBlockH10(&hasher.privat._H10, block_size, block_start, input_buffer, mask);
  path_size = BrotliZopfliComputeShortestPath(m, block_size, block_start, input_buffer, mask, literal_context_lut, &params, dist_cache, &hasher, nodes);
  if (!(!0))
  {
    goto oom;
  }
  new_cmd_alloc_size = brotli_max_size_t(expected_num_commands, (num_commands + path_size) + 1);
  if (cmd_alloc_size != new_cmd_alloc_size)
  {
    helper_helper_helper_BrotliCompressBufferQuality10_1_2_1(&commands_idx, &cmd_alloc_size, m, commands, num_commands, new_cmd_alloc_size);
  }
  BrotliZopfliCreateCommands(block_size, block_start, &nodes[0 + nodes_idx], dist_cache, &last_insert_len, &params, &commands[num_commands + commands_idx], &num_literals);
  num_commands += path_size;
  block_start += block_size;
  metablock_size += block_size;
  {
    BrotliFree(m, nodes);
    nodes_idx = 0;
  }
  ;
  if ((num_literals > max_literals_per_metablock) || (num_commands > max_commands_per_metablock))
  {
    break;
  }
  *commands_idx_ref = commands_idx;
  *num_commands_ref = num_commands;
  *metablock_size_ref = metablock_size;
  *cmd_alloc_size_ref = cmd_alloc_size;
  *block_start_ref = block_start;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void helper_helper_helper_BrotliCompressBufferQuality10_1_2_1(unsigned int * const commands_idx_ref, size_t * const cmd_alloc_size_ref, MemoryManager * const m, Command * const commands, size_t num_commands, size_t new_cmd_alloc_size)
{
  unsigned int commands_idx = *commands_idx_ref;
  size_t cmd_alloc_size = *cmd_alloc_size_ref;
  Command *new_commands = (new_cmd_alloc_size > 0) ? ((Command *) BrotliAllocate(m, new_cmd_alloc_size * (sizeof(Command)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    goto oom;
  }
  cmd_alloc_size = new_cmd_alloc_size;
  if (commands)
  {
    memcpy(new_commands, commands, (sizeof(Command)) * num_commands);
    {
      BrotliFree(m, commands);
      commands_idx = 0;
    }
    ;
  }
  commands_idx = new_commands;
  *commands_idx_ref = commands_idx;
  *cmd_alloc_size_ref = cmd_alloc_size;
}


----------------------------
void BrotliInitZopfliNodes(ZopfliNode *array, size_t length)
{
  ZopfliNode stub;
  size_t i;
  stub.length = 1;
  stub.distance = 0;
  stub.dcode_insert_length = 0;
  stub.u.cost = kInfinity;
  for (i = 0; i < length; i += 1)
    array[i] = stub;

}


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
void BrotliZopfliCreateCommands(const size_t num_bytes, const size_t block_start, const ZopfliNode *nodes, int *dist_cache, size_t *last_insert_len, const BrotliEncoderParams *params, Command *commands, size_t *num_literals)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  size_t pos = 0;
  uint32_t offset = nodes[0].u.next;
  size_t i;
  size_t gap = 0;
  for (i = 0; offset != (~((uint32_t) 0)); i += 1)
  {
    const ZopfliNode *next = &nodes[pos + offset];
    size_t copy_length = ZopfliNodeCopyLength(next);
    size_t insert_length = next->dcode_insert_length & 0x7FFFFFF;
    pos += insert_length;
    offset = next->u.next;
    if (i == 0)
    {
      insert_length += *last_insert_len;
      *last_insert_len = 0;
    }
    {
      size_t distance = ZopfliNodeCopyDistance(next);
      size_t len_code = ZopfliNodeLengthCode(next);
      size_t dictionary_start = brotli_min_size_t((block_start + pos) + stream_offset, max_backward_limit);
      int is_dictionary = (!(!(distance > (dictionary_start + gap)))) ? (1) : (0);
      size_t dist_code = ZopfliNodeDistanceCode(next);
      InitCommand(&commands[i], &params->dist, insert_length, copy_length, ((int) len_code) - ((int) copy_length), dist_code);
      if ((!is_dictionary) && (dist_code > 0))
      {
        dist_cache[3] = dist_cache[2];
        dist_cache[2] = dist_cache[1];
        dist_cache[1] = dist_cache[0];
        dist_cache[0] = (int) distance;
      }
    }
    *num_literals += insert_length;
    pos += copy_length;
  }

  *last_insert_len += num_bytes - pos;
}


----------------------------
size_t BrotliZopfliComputeShortestPath(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, const int *dist_cache, Hasher *hasher, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  ZopfliCostModel model;
  StartPosQueue queue;
  BackwardMatch matches[2 * (128 + 64)];
  const size_t store_end = (num_bytes >= StoreLookaheadH10()) ? (((position + num_bytes) - StoreLookaheadH10()) + 1) : (position);
  size_t i;
  size_t gap = 0;
  size_t lz_matches_offset = 0;
  (void) literal_context_lut;
  nodes[0].length = 0;
  nodes[0].u.cost = 0;
  InitZopfliCostModel(m, &model, &params->dist, num_bytes);
  if (!(!0))
  {
    return 0;
  }
  ZopfliCostModelSetFromLiteralCosts(&model, position, ringbuffer, ringbuffer_mask);
  InitStartPosQueue(&queue);
  for (i = 0; ((i + HashTypeLengthH10()) - 1) < num_bytes; i += 1)
  {
    helper_BrotliZopfliComputeShortestPath_1(&i, num_bytes, position, ringbuffer, ringbuffer_mask, params, dist_cache, hasher, nodes, stream_offset, max_backward_limit, max_zopfli_len, model, queue, matches, store_end, gap, lz_matches_offset);
  }

  CleanupZopfliCostModel(m, &model);
  return ComputeShortestPathFromNodes(num_bytes, nodes);
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
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static void StitchToPreviousBlockH10(H10 * restrict self, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  if ((num_bytes >= (HashTypeLengthH10() - 1)) && (position >= 128))
  {
    const size_t i_start = (position - 128) + 1;
    const size_t i_end = brotli_min_size_t(position, i_start + num_bytes);
    size_t i;
    for (i = i_start; i < i_end; i += 1)
    {
      const size_t max_backward = self->window_mask_ - brotli_max_size_t(16 - 1, position - i);
      StoreAndFindMatchesH10(self, ringbuffer, i, ringbuffer_mask, 128, max_backward, 0, 0);
    }

  }
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


// hint:  ['encoded_buffer_idx_ref is a mutable refrence to unsigned int', 'ok_ref is a mutable refrence to int', 'total_out_size_ref is a mutable refrence to size_t', 'last_bytes_ref is a mutable refrence to uint16_t', 'last_bytes_bits_ref is a mutable refrence to uint8_t', 'metablock_start_ref is a mutable refrence to size_t', 'prev_byte_ref is a mutable refrence to uint8_t', 'prev_byte2_ref is a mutable refrence to uint8_t']
void helper_BrotliCompressBufferQuality10_1(unsigned int * const encoded_buffer_idx_ref, int * const ok_ref, size_t * const total_out_size_ref, uint16_t * const last_bytes_ref, uint8_t * const last_bytes_bits_ref, size_t * const metablock_start_ref, uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, size_t input_size, const uint8_t * const input_buffer, uint8_t * const encoded_buffer, MemoryManager * const m, const size_t mask, int dist_cache[4], int saved_dist_cache[4], const size_t max_out_size, BrotliEncoderParams params, size_t max_block_size, const size_t max_metablock_size, const size_t max_literals_per_metablock, const size_t max_commands_per_metablock, Hasher hasher)
{
  unsigned int encoded_buffer_idx = *encoded_buffer_idx_ref;
  int ok = *ok_ref;
  size_t total_out_size = *total_out_size_ref;
  uint16_t last_bytes = *last_bytes_ref;
  uint8_t last_bytes_bits = *last_bytes_bits_ref;
  size_t metablock_start = *metablock_start_ref;
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  const size_t metablock_end = brotli_min_size_t(input_size, metablock_start + max_metablock_size);
  const size_t expected_num_commands = ((metablock_end - metablock_start) / 12) + 16;
  Command *commands = 0;
  unsigned int commands_idx = 0;
  size_t num_commands = 0;
  size_t last_insert_len = 0;
  size_t num_literals = 0;
  size_t metablock_size = 0;
  size_t cmd_alloc_size = 0;
  int is_last;
  uint8_t *storage;
  unsigned int storage_idx = 0;
  size_t storage_ix;
  ContextType literal_context_mode = ChooseContextMode(&params, input_buffer, metablock_start, mask, metablock_end - metablock_start);
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  size_t block_start;
  for (block_start = metablock_start; block_start < metablock_end;)
  {
    helper_helper_BrotliCompressBufferQuality10_1_2(&commands_idx, &num_commands, &metablock_size, &cmd_alloc_size, &block_start, input_buffer, m, mask, dist_cache, params, max_block_size, max_literals_per_metablock, max_commands_per_metablock, hasher, metablock_end, expected_num_commands, commands, last_insert_len, num_literals, literal_context_lut);
  }

  if (last_insert_len > 0)
  {
    InitInsertCommand(&commands[num_commands + commands_idx], last_insert_len);
    num_commands += 1;
    num_literals += last_insert_len;
  }
  is_last = (!(!((metablock_start + metablock_size) == input_size))) ? (1) : (0);
  storage_idx = 0;
  storage_ix = last_bytes_bits;
  if (metablock_size == 0)
  {
    storage_idx = (16 > 0) ? ((uint8_t *) BrotliAllocate(m, 16 * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      goto oom;
    }
    storage[0 + storage_idx] = (uint8_t) last_bytes;
    storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
    BrotliWriteBits(2, 3, &storage_ix, storage);
    storage_ix = (storage_ix + 7u) & (~7u);
  }
  else
    if (!ShouldCompress(input_buffer, mask, metablock_start, metablock_size, num_literals, num_commands))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    storage_idx = ((metablock_size + 16) > 0) ? ((uint8_t *) BrotliAllocate(m, (metablock_size + 16) * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      goto oom;
    }
    storage[0 + storage_idx] = (uint8_t) last_bytes;
    storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
    BrotliStoreUncompressedMetaBlock(is_last, input_buffer, metablock_start, mask, metablock_size, &storage_ix, storage);
  }
  else
  {
    helper_helper_BrotliCompressBufferQuality10_1_1(&storage_idx, &storage_ix, input_buffer, m, mask, dist_cache, saved_dist_cache, params, last_bytes, last_bytes_bits, metablock_start, prev_byte, prev_byte2, commands, num_commands, metablock_size, is_last, storage, literal_context_mode);
  }
  last_bytes = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  last_bytes_bits = storage_ix & 7u;
  metablock_start += metablock_size;
  if (metablock_start < input_size)
  {
    prev_byte = input_buffer[metablock_start - 1];
    prev_byte2 = input_buffer[metablock_start - 2];
  }
  memcpy(saved_dist_cache, dist_cache, 4 * (sizeof(dist_cache[0])));
  {
    const size_t out_size = storage_ix >> 3;
    total_out_size += out_size;
    if (total_out_size <= max_out_size)
    {
      memcpy(encoded_buffer, storage, out_size);
      encoded_buffer_idx += out_size;
    }
    else
    {
      ok = 0;
    }
  }
  {
    BrotliFree(m, storage);
    storage_idx = 0;
  }
  ;
  {
    BrotliFree(m, commands);
    commands_idx = 0;
  }
  ;
  *encoded_buffer_idx_ref = encoded_buffer_idx;
  *ok_ref = ok;
  *total_out_size_ref = total_out_size;
  *last_bytes_ref = last_bytes;
  *last_bytes_bits_ref = last_bytes_bits;
  *metablock_start_ref = metablock_start;
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
}


/*** DEPENDENCIES:
inline static void InitInsertCommand(Command *self, size_t insertlen)
{
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = 4 << 25;
  self->dist_extra_ = 0;
  self->dist_prefix_ = 16;
  GetLengthCode(insertlen, 4, 0, &self->cmd_prefix_);
}


----------------------------
static ContextType ChooseContextMode(const BrotliEncoderParams *params, const uint8_t *data, const size_t pos, const size_t mask, const size_t length)
{
  if ((params->quality >= 10) && (!BrotliIsMostlyUTF8(data, pos, mask, length, kMinUTF8Ratio)))
  {
    return CONTEXT_SIGNED;
  }
  return CONTEXT_UTF8;
}


----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
static int ShouldCompress(const uint8_t *input, size_t input_size, size_t num_literals)
{
  double corpus_size = (double) input_size;
  if (((double) num_literals) < (0.98 * corpus_size))
  {
    return 1;
  }
  else
  {
    uint32_t literal_histo[256] = {0};
    const double max_total_bit_cost = ((corpus_size * 8) * 0.98) / 43;
    size_t i;
    for (i = 0; i < input_size; i += 43)
    {
      literal_histo[input[i]] += 1;
    }

    return (!(!(BitsEntropy(literal_histo, 256) < max_total_bit_cost))) ? (1) : (0);
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


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
void helper_helper_BrotliCompressBufferQuality10_1_1(unsigned int * const storage_idx_ref, size_t * const storage_ix_ref, const uint8_t * const input_buffer, MemoryManager * const m, const size_t mask, int dist_cache[4], int saved_dist_cache[4], BrotliEncoderParams params, uint16_t last_bytes, uint8_t last_bytes_bits, size_t metablock_start, uint8_t prev_byte, uint8_t prev_byte2, Command * const commands, size_t num_commands, size_t metablock_size, int is_last, uint8_t * const storage, ContextType literal_context_mode)
{
  unsigned int storage_idx = *storage_idx_ref;
  size_t storage_ix = *storage_ix_ref;
  MetaBlockSplit mb;
  BrotliEncoderParams block_params = params;
  InitMetaBlockSplit(&mb);
  BrotliBuildMetaBlock(m, input_buffer, metablock_start, mask, &block_params, prev_byte, prev_byte2, commands, num_commands, literal_context_mode, &mb);
  if (!(!0))
  {
    goto oom;
  }
  {
    BrotliOptimizeHistograms(block_params.dist.alphabet_size_limit, &mb);
  }
  storage_idx = (((2 * metablock_size) + 503) > 0) ? ((uint8_t *) BrotliAllocate(m, ((2 * metablock_size) + 503) * (sizeof(uint8_t)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    goto oom;
  }
  storage[0 + storage_idx] = (uint8_t) last_bytes;
  storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
  BrotliStoreMetaBlock(m, input_buffer, metablock_start, metablock_size, mask, prev_byte, prev_byte2, is_last, &block_params, literal_context_mode, commands, num_commands, &mb, &storage_ix, storage);
  if (!(!0))
  {
    goto oom;
  }
  if ((metablock_size + 4) < (storage_ix >> 3))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    storage[0 + storage_idx] = (uint8_t) last_bytes;
    storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
    storage_ix = last_bytes_bits;
    BrotliStoreUncompressedMetaBlock(is_last, input_buffer, metablock_start, mask, metablock_size, &storage_ix, storage);
  }
  DestroyMetaBlockSplit(m, &mb);
  *storage_idx_ref = storage_idx;
  *storage_ix_ref = storage_ix;
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
extern const uint8_t _kBrotliContextLookupTable[2048]
----------------------------
void BrotliStoreUncompressedMetaBlock(int is_final_block, const uint8_t * restrict input, size_t position, size_t mask, size_t len, size_t * restrict storage_ix, uint8_t * restrict storage)
{
  size_t masked_pos = position & mask;
  BrotliStoreUncompressedMetaBlockHeader(len, storage_ix, storage);
  JumpToByteBoundary(storage_ix, storage);
  if ((masked_pos + len) > (mask + 1))
  {
    size_t len1 = (mask + 1) - masked_pos;
    memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len1);
    *storage_ix += len1 << 3;
    len -= len1;
    masked_pos = 0;
  }
  memcpy(&storage[(*storage_ix) >> 3], &input[masked_pos], len);
  *storage_ix += len << 3;
  BrotliWriteBitsPrepareStorage(*storage_ix, storage);
  if (is_final_block)
  {
    BrotliWriteBits(1, 1, storage_ix, storage);
    BrotliWriteBits(1, 1, storage_ix, storage);
    JumpToByteBoundary(storage_ix, storage);
  }
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef enum ContextType
{
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
inline static void BrotliWriteBits(size_t n_bits, uint64_t bits, size_t * restrict pos, uint8_t * restrict array)
{
  ;
  ;
  ;
  {
    uint8_t *p = &array[(*pos) >> 3];
    uint64_t v = (uint64_t) (*p);
    v |= bits << ((*pos) & 7);
    BrotliUnalignedWrite64(p, v);
    *pos += n_bits;
  }
}


----------------------------
void helper_helper_BrotliCompressBufferQuality10_1_2(unsigned int * const commands_idx_ref, size_t * const num_commands_ref, size_t * const metablock_size_ref, size_t * const cmd_alloc_size_ref, size_t * const block_start_ref, const uint8_t * const input_buffer, MemoryManager * const m, const size_t mask, int dist_cache[4], BrotliEncoderParams params, size_t max_block_size, const size_t max_literals_per_metablock, const size_t max_commands_per_metablock, Hasher hasher, const size_t metablock_end, const size_t expected_num_commands, Command * const commands, size_t last_insert_len, size_t num_literals, ContextLut literal_context_lut)
{
  unsigned int commands_idx = *commands_idx_ref;
  size_t num_commands = *num_commands_ref;
  size_t metablock_size = *metablock_size_ref;
  size_t cmd_alloc_size = *cmd_alloc_size_ref;
  size_t block_start = *block_start_ref;
  size_t block_size = brotli_min_size_t(metablock_end - block_start, max_block_size);
  ZopfliNode *nodes = ((block_size + 1) > 0) ? ((ZopfliNode *) BrotliAllocate(m, (block_size + 1) * (sizeof(ZopfliNode)))) : (0);
  unsigned int nodes_idx = 0;
  size_t path_size;
  size_t new_cmd_alloc_size;
  if ((!(!0)) || (!(!0)))
  {
    goto oom;
  }
  BrotliInitZopfliNodes(nodes, block_size + 1);
  StitchToPreviousBlockH10(&hasher.privat._H10, block_size, block_start, input_buffer, mask);
  path_size = BrotliZopfliComputeShortestPath(m, block_size, block_start, input_buffer, mask, literal_context_lut, &params, dist_cache, &hasher, nodes);
  if (!(!0))
  {
    goto oom;
  }
  new_cmd_alloc_size = brotli_max_size_t(expected_num_commands, (num_commands + path_size) + 1);
  if (cmd_alloc_size != new_cmd_alloc_size)
  {
    helper_helper_helper_BrotliCompressBufferQuality10_1_2_1(&commands_idx, &cmd_alloc_size, m, commands, num_commands, new_cmd_alloc_size);
  }
  BrotliZopfliCreateCommands(block_size, block_start, &nodes[0 + nodes_idx], dist_cache, &last_insert_len, &params, &commands[num_commands + commands_idx], &num_literals);
  num_commands += path_size;
  block_start += block_size;
  metablock_size += block_size;
  {
    BrotliFree(m, nodes);
    nodes_idx = 0;
  }
  ;
  if ((num_literals > max_literals_per_metablock) || (num_commands > max_commands_per_metablock))
  {
    break;
  }
  *commands_idx_ref = commands_idx;
  *num_commands_ref = num_commands;
  *metablock_size_ref = metablock_size;
  *cmd_alloc_size_ref = cmd_alloc_size;
  *block_start_ref = block_start;
}


----------------------------
None
----------------------------
***/


static int BrotliCompressBufferQuality10(int lgwin, size_t input_size, const uint8_t *input_buffer, size_t *encoded_size, uint8_t *encoded_buffer)
{
  unsigned int encoded_buffer_idx = 0;
  MemoryManager memory_manager;
  MemoryManager *m = &memory_manager;
  const size_t mask = (~((size_t) 0)) >> 1;
  int dist_cache[4] = {4, 11, 15, 16};
  int saved_dist_cache[4] = {4, 11, 15, 16};
  int ok = 1;
  const size_t max_out_size = *encoded_size;
  size_t total_out_size = 0;
  uint16_t last_bytes;
  uint8_t last_bytes_bits;
  const size_t hasher_eff_size = brotli_min_size_t(input_size, ((((size_t) 1) << lgwin) - 16) + 16);
  BrotliEncoderParams params;
  const int lgmetablock = brotli_min_int(24, lgwin + 1);
  size_t max_block_size;
  const size_t max_metablock_size = ((size_t) 1) << lgmetablock;
  const size_t max_literals_per_metablock = max_metablock_size / 8;
  const size_t max_commands_per_metablock = max_metablock_size / 8;
  size_t metablock_start = 0;
  uint8_t prev_byte = 0;
  uint8_t prev_byte2 = 0;
  Hasher hasher;
  HasherInit(&hasher);
  BrotliEncoderInitParams(&params);
  params.quality = 10;
  params.lgwin = lgwin;
  if (lgwin > 24)
  {
    params.large_window = 1;
  }
  SanitizeParams(&params);
  params.lgblock = ComputeLgBlock(&params);
  ChooseDistanceParams(&params);
  max_block_size = ((size_t) 1) << params.lgblock;
  BrotliInitMemoryManager(m, 0, 0, 0);
  ;
  EncodeWindowBits(lgwin, params.large_window, &last_bytes, &last_bytes_bits);
  InitOrStitchToPreviousBlock(m, &hasher, input_buffer, mask, &params, 0, hasher_eff_size, 1);
  if (!(!0))
  {
    goto oom;
  }
  while (ok && (metablock_start < input_size))
  {
    helper_BrotliCompressBufferQuality10_1(&encoded_buffer_idx, &ok, &total_out_size, &last_bytes, &last_bytes_bits, &metablock_start, &prev_byte, &prev_byte2, input_size, input_buffer, encoded_buffer, m, mask, dist_cache, saved_dist_cache, max_out_size, params, max_block_size, max_metablock_size, max_literals_per_metablock, max_commands_per_metablock, hasher);
  }

  *encoded_size = total_out_size;
  DestroyHasher(m, &hasher);
  return ok;
  oom:
  BrotliWipeOutMemoryManager(m);

  return 0;
}


/*** DEPENDENCIES:
void BrotliWipeOutMemoryManager(MemoryManager *m)
{
  (void) m;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static int ComputeLgBlock(const BrotliEncoderParams *params)
{
  int lgblock = params->lgblock;
  if ((params->quality == 0) || (params->quality == 1))
  {
    lgblock = params->lgwin;
  }
  else
    if (params->quality < 4)
  {
    lgblock = 14;
  }
  else
    if (lgblock == 0)
  {
    lgblock = 16;
    if ((params->quality >= 9) && (params->lgwin > lgblock))
    {
      lgblock = brotli_min_int(18, params->lgwin);
    }
  }
  else
  {
    lgblock = brotli_min_int(24, brotli_max_int(16, lgblock));
  }
  return lgblock;
}


----------------------------
static void BrotliEncoderInitParams(BrotliEncoderParams *params)
{
  params->mode = BROTLI_MODE_GENERIC;
  params->large_window = 0;
  params->quality = 11;
  params->lgwin = 22;
  params->lgblock = 0;
  params->stream_offset = 0;
  params->size_hint = 0;
  params->disable_literal_context_modeling = 0;
  BrotliInitEncoderDictionary(&params->dictionary);
  params->dist.distance_postfix_bits = 0;
  params->dist.num_direct_distance_codes = 0;
  params->dist.alphabet_size_max = (16 + 0) + (24U << (0 + 1));
  params->dist.alphabet_size_limit = params->dist.alphabet_size_max;
  params->dist.max_distance = 0x3FFFFFC;
}


----------------------------
inline static void InitOrStitchToPreviousBlock(MemoryManager *m, Hasher *hasher, const uint8_t *data, size_t mask, BrotliEncoderParams *params, size_t position, size_t input_size, int is_last)
{
  HasherSetup(m, hasher, params, data, position, input_size, is_last);
  if (!(!0))
  {
    return;
  }
  switch (hasher->common.params.type)
  {
    case 2:
    {
      StitchToPreviousBlockH2(&hasher->privat._H2, input_size, position, data, mask);
      break;
    }

    case 3:
    {
      StitchToPreviousBlockH3(&hasher->privat._H3, input_size, position, data, mask);
      break;
    }

    case 4:
    {
      StitchToPreviousBlockH4(&hasher->privat._H4, input_size, position, data, mask);
      break;
    }

    case 5:
    {
      StitchToPreviousBlockH5(&hasher->privat._H5, input_size, position, data, mask);
      break;
    }

    case 6:
    {
      StitchToPreviousBlockH6(&hasher->privat._H6, input_size, position, data, mask);
      break;
    }

    case 40:
    {
      StitchToPreviousBlockH40(&hasher->privat._H40, input_size, position, data, mask);
      break;
    }

    case 41:
    {
      StitchToPreviousBlockH41(&hasher->privat._H41, input_size, position, data, mask);
      break;
    }

    case 42:
    {
      StitchToPreviousBlockH42(&hasher->privat._H42, input_size, position, data, mask);
      break;
    }

    case 54:
    {
      StitchToPreviousBlockH54(&hasher->privat._H54, input_size, position, data, mask);
      break;
    }

    case 35:
    {
      StitchToPreviousBlockH35(&hasher->privat._H35, input_size, position, data, mask);
      break;
    }

    case 55:
    {
      StitchToPreviousBlockH55(&hasher->privat._H55, input_size, position, data, mask);
      break;
    }

    case 65:
    {
      StitchToPreviousBlockH65(&hasher->privat._H65, input_size, position, data, mask);
      break;
    }

    case 10:
    {
      StitchToPreviousBlockH10(&hasher->privat._H10, input_size, position, data, mask);
      break;
    }

    default:
    {
      break;
    }

  }

}


----------------------------
inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static void EncodeWindowBits(int lgwin, int large_window, uint16_t *last_bytes, uint8_t *last_bytes_bits)
{
  if (large_window)
  {
    *last_bytes = (uint16_t) (((lgwin & 0x3F) << 8) | 0x11);
    *last_bytes_bits = 14;
  }
  else
  {
    if (lgwin == 16)
    {
      *last_bytes = 0;
      *last_bytes_bits = 1;
    }
    else
      if (lgwin == 17)
    {
      *last_bytes = 1;
      *last_bytes_bits = 7;
    }
    else
      if (lgwin > 17)
    {
      *last_bytes = (uint16_t) (((lgwin - 17) << 1) | 0x01);
      *last_bytes_bits = 4;
    }
    else
    {
      *last_bytes = (uint16_t) (((lgwin - 8) << 4) | 0x01);
      *last_bytes_bits = 7;
    }
  }
}


----------------------------
inline static void DestroyHasher(MemoryManager *m, Hasher *hasher)
{
  if (hasher->common.extra == 0)
  {
    return;
  }
  {
    BrotliFree(m, hasher->common.extra);
    hasher->common.extra = 0;
  }
  ;
}


----------------------------
inline static void SanitizeParams(BrotliEncoderParams *params)
{
  params->quality = brotli_min_int(11, brotli_max_int(0, params->quality));
  if (params->quality <= 2)
  {
    params->large_window = 0;
  }
  if (params->lgwin < 10)
  {
    params->lgwin = 10;
  }
  else
  {
    int max_lgwin = (params->large_window) ? (30) : (24);
    if (params->lgwin > max_lgwin)
    {
      params->lgwin = max_lgwin;
    }
  }
}


----------------------------
inline static void HasherInit(Hasher *hasher)
{
  hasher->common.extra = 0;
}


----------------------------
void helper_BrotliCompressBufferQuality10_1(unsigned int * const encoded_buffer_idx_ref, int * const ok_ref, size_t * const total_out_size_ref, uint16_t * const last_bytes_ref, uint8_t * const last_bytes_bits_ref, size_t * const metablock_start_ref, uint8_t * const prev_byte_ref, uint8_t * const prev_byte2_ref, size_t input_size, const uint8_t * const input_buffer, uint8_t * const encoded_buffer, MemoryManager * const m, const size_t mask, int dist_cache[4], int saved_dist_cache[4], const size_t max_out_size, BrotliEncoderParams params, size_t max_block_size, const size_t max_metablock_size, const size_t max_literals_per_metablock, const size_t max_commands_per_metablock, Hasher hasher)
{
  unsigned int encoded_buffer_idx = *encoded_buffer_idx_ref;
  int ok = *ok_ref;
  size_t total_out_size = *total_out_size_ref;
  uint16_t last_bytes = *last_bytes_ref;
  uint8_t last_bytes_bits = *last_bytes_bits_ref;
  size_t metablock_start = *metablock_start_ref;
  uint8_t prev_byte = *prev_byte_ref;
  uint8_t prev_byte2 = *prev_byte2_ref;
  const size_t metablock_end = brotli_min_size_t(input_size, metablock_start + max_metablock_size);
  const size_t expected_num_commands = ((metablock_end - metablock_start) / 12) + 16;
  Command *commands = 0;
  unsigned int commands_idx = 0;
  size_t num_commands = 0;
  size_t last_insert_len = 0;
  size_t num_literals = 0;
  size_t metablock_size = 0;
  size_t cmd_alloc_size = 0;
  int is_last;
  uint8_t *storage;
  unsigned int storage_idx = 0;
  size_t storage_ix;
  ContextType literal_context_mode = ChooseContextMode(&params, input_buffer, metablock_start, mask, metablock_end - metablock_start);
  ContextLut literal_context_lut = &_kBrotliContextLookupTable[literal_context_mode << 9];
  size_t block_start;
  for (block_start = metablock_start; block_start < metablock_end;)
  {
    helper_helper_BrotliCompressBufferQuality10_1_2(&commands_idx, &num_commands, &metablock_size, &cmd_alloc_size, &block_start, input_buffer, m, mask, dist_cache, params, max_block_size, max_literals_per_metablock, max_commands_per_metablock, hasher, metablock_end, expected_num_commands, commands, last_insert_len, num_literals, literal_context_lut);
  }

  if (last_insert_len > 0)
  {
    InitInsertCommand(&commands[num_commands + commands_idx], last_insert_len);
    num_commands += 1;
    num_literals += last_insert_len;
  }
  is_last = (!(!((metablock_start + metablock_size) == input_size))) ? (1) : (0);
  storage_idx = 0;
  storage_ix = last_bytes_bits;
  if (metablock_size == 0)
  {
    storage_idx = (16 > 0) ? ((uint8_t *) BrotliAllocate(m, 16 * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      goto oom;
    }
    storage[0 + storage_idx] = (uint8_t) last_bytes;
    storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
    BrotliWriteBits(2, 3, &storage_ix, storage);
    storage_ix = (storage_ix + 7u) & (~7u);
  }
  else
    if (!ShouldCompress(input_buffer, mask, metablock_start, metablock_size, num_literals, num_commands))
  {
    memcpy(dist_cache, saved_dist_cache, 4 * (sizeof(dist_cache[0])));
    storage_idx = ((metablock_size + 16) > 0) ? ((uint8_t *) BrotliAllocate(m, (metablock_size + 16) * (sizeof(uint8_t)))) : (0);
    if ((!(!0)) || (!(!0)))
    {
      goto oom;
    }
    storage[0 + storage_idx] = (uint8_t) last_bytes;
    storage[1 + storage_idx] = (uint8_t) (last_bytes >> 8);
    BrotliStoreUncompressedMetaBlock(is_last, input_buffer, metablock_start, mask, metablock_size, &storage_ix, storage);
  }
  else
  {
    helper_helper_BrotliCompressBufferQuality10_1_1(&storage_idx, &storage_ix, input_buffer, m, mask, dist_cache, saved_dist_cache, params, last_bytes, last_bytes_bits, metablock_start, prev_byte, prev_byte2, commands, num_commands, metablock_size, is_last, storage, literal_context_mode);
  }
  last_bytes = (uint16_t) storage[(storage_ix >> 3) + storage_idx];
  last_bytes_bits = storage_ix & 7u;
  metablock_start += metablock_size;
  if (metablock_start < input_size)
  {
    prev_byte = input_buffer[metablock_start - 1];
    prev_byte2 = input_buffer[metablock_start - 2];
  }
  memcpy(saved_dist_cache, dist_cache, 4 * (sizeof(dist_cache[0])));
  {
    const size_t out_size = storage_ix >> 3;
    total_out_size += out_size;
    if (total_out_size <= max_out_size)
    {
      memcpy(encoded_buffer, storage, out_size);
      encoded_buffer_idx += out_size;
    }
    else
    {
      ok = 0;
    }
  }
  {
    BrotliFree(m, storage);
    storage_idx = 0;
  }
  ;
  {
    BrotliFree(m, commands);
    commands_idx = 0;
  }
  ;
  *encoded_buffer_idx_ref = encoded_buffer_idx;
  *ok_ref = ok;
  *total_out_size_ref = total_out_size;
  *last_bytes_ref = last_bytes;
  *last_bytes_bits_ref = last_bytes_bits;
  *metablock_start_ref = metablock_start;
  *prev_byte_ref = prev_byte;
  *prev_byte2_ref = prev_byte2;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliInitMemoryManager(MemoryManager *m, brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  if (!alloc_func)
  {
    m->alloc_func = BrotliDefaultAllocFunc;
    m->free_func = BrotliDefaultFreeFunc;
    m->opaque = 0;
  }
  else
  {
    m->alloc_func = alloc_func;
    m->free_func = free_func;
    m->opaque = opaque;
  }
}


----------------------------
static void ChooseDistanceParams(BrotliEncoderParams *params)
{
  uint32_t distance_postfix_bits = 0;
  uint32_t num_direct_distance_codes = 0;
  if (params->quality >= 4)
  {
    uint32_t ndirect_msb;
    if (params->mode == BROTLI_MODE_FONT)
    {
      distance_postfix_bits = 1;
      num_direct_distance_codes = 12;
    }
    else
    {
      distance_postfix_bits = params->dist.distance_postfix_bits;
      num_direct_distance_codes = params->dist.num_direct_distance_codes;
    }
    ndirect_msb = (num_direct_distance_codes >> distance_postfix_bits) & 0x0F;
    if (((distance_postfix_bits > 3) || (num_direct_distance_codes > 120)) || ((ndirect_msb << distance_postfix_bits) != num_direct_distance_codes))
    {
      distance_postfix_bits = 0;
      num_direct_distance_codes = 0;
    }
  }
  BrotliInitDistanceParams(params, distance_postfix_bits, num_direct_distance_codes);
}


----------------------------
None
----------------------------
***/


int BrotliEncoderCompress(int quality, int lgwin, BrotliEncoderMode mode, size_t input_size, const uint8_t *input_buffer, size_t *encoded_size, uint8_t *encoded_buffer)
{
  BrotliEncoderState *s;
  unsigned int s_idx = 0;
  size_t out_size = *encoded_size;
  const uint8_t *input_start = input_buffer;
  uint8_t *output_start = encoded_buffer;
  size_t max_out_size = BrotliEncoderMaxCompressedSize(input_size);
  if (out_size == 0)
  {
    return 0;
  }
  if (input_size == 0)
  {
    *encoded_size = 1;
    *encoded_buffer = 6;
    return 1;
  }
  if (quality == 10)
  {
    const int lg_win = brotli_min_int(30, brotli_max_int(16, lgwin));
    int ok = BrotliCompressBufferQuality10(lg_win, input_size, input_buffer, encoded_size, encoded_buffer);
    if ((!ok) || (max_out_size && ((*encoded_size) > max_out_size)))
    {
      goto fallback;
    }
    return 1;
  }
  s_idx = BrotliEncoderCreateInstance(0, 0, 0);
  if (!(&s[s_idx]))
  {
    return 0;
  }
  else
  {
    helper_BrotliEncoderCompress_1(quality, lgwin, mode, input_size, input_buffer, encoded_size, encoded_buffer, s, max_out_size);
  }
  fallback:
  *encoded_size = 0;

  if (!max_out_size)
  {
    return 0;
  }
  if (out_size >= max_out_size)
  {
    *encoded_size = MakeUncompressedStream(input_start, input_size, output_start);
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
size_t BrotliEncoderMaxCompressedSize(size_t input_size)
{
  size_t num_large_blocks = input_size >> 14;
  size_t overhead = ((2 + (4 * num_large_blocks)) + 3) + 1;
  size_t result = input_size + overhead;
  if (input_size == 0)
  {
    return 2;
  }
  return (result < input_size) ? (0) : (result);
}


----------------------------
BrotliEncoderState *BrotliEncoderCreateInstance(brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  BrotliEncoderState *state = 0;
  unsigned int state_idx = 0;
  if ((!alloc_func) && (!free_func))
  {
    state_idx = (BrotliEncoderState *) malloc(sizeof(BrotliEncoderState));
  }
  else
    if (alloc_func && free_func)
  {
    state_idx = (BrotliEncoderState *) alloc_func(opaque, sizeof(BrotliEncoderState));
  }
  if ((&state[state_idx]) == 0)
  {
    return 0;
  }
  BrotliInitMemoryManager(&state->memory_manager_, alloc_func, free_func, opaque);
  BrotliEncoderInitState(state);
  return state;
}


----------------------------
typedef enum BrotliEncoderMode
{
  BROTLI_MODE_GENERIC = 0,
  BROTLI_MODE_TEXT = 1,
  BROTLI_MODE_FONT = 2
} BrotliEncoderMode
----------------------------
inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
int helper_BrotliEncoderCompress_1(int quality, int lgwin, BrotliEncoderMode mode, size_t input_size, const uint8_t * const input_buffer, size_t * const encoded_size, uint8_t * const encoded_buffer, BrotliEncoderState * const s, size_t max_out_size)
{
  size_t available_in = input_size;
  const uint8_t *next_in = input_buffer;
  size_t available_out = *encoded_size;
  uint8_t *next_out = encoded_buffer;
  size_t total_out = 0;
  int result = 0;
  BrotliEncoderSetParameter(s, BROTLI_PARAM_QUALITY, (uint32_t) quality);
  BrotliEncoderSetParameter(s, BROTLI_PARAM_LGWIN, (uint32_t) lgwin);
  BrotliEncoderSetParameter(s, BROTLI_PARAM_MODE, (uint32_t) mode);
  BrotliEncoderSetParameter(s, BROTLI_PARAM_SIZE_HINT, (uint32_t) input_size);
  if (lgwin > 24)
  {
    BrotliEncoderSetParameter(s, BROTLI_PARAM_LARGE_WINDOW, 1);
  }
  result = BrotliEncoderCompressStream(s, BROTLI_OPERATION_FINISH, &available_in, &next_in, &available_out, &next_out, &total_out);
  if (!BrotliEncoderIsFinished(s))
  {
    result = 0;
  }
  *encoded_size = total_out;
  BrotliEncoderDestroyInstance(s);
  if ((!result) || (max_out_size && ((*encoded_size) > max_out_size)))
  {
    goto fallback;
  }
  return 1;
}


----------------------------
typedef struct BrotliEncoderStateStruct BrotliEncoderState
----------------------------
static int BrotliCompressBufferQuality10(int lgwin, size_t input_size, const uint8_t *input_buffer, size_t *encoded_size, uint8_t *encoded_buffer)
{
  unsigned int encoded_buffer_idx = 0;
  MemoryManager memory_manager;
  MemoryManager *m = &memory_manager;
  const size_t mask = (~((size_t) 0)) >> 1;
  int dist_cache[4] = {4, 11, 15, 16};
  int saved_dist_cache[4] = {4, 11, 15, 16};
  int ok = 1;
  const size_t max_out_size = *encoded_size;
  size_t total_out_size = 0;
  uint16_t last_bytes;
  uint8_t last_bytes_bits;
  const size_t hasher_eff_size = brotli_min_size_t(input_size, ((((size_t) 1) << lgwin) - 16) + 16);
  BrotliEncoderParams params;
  const int lgmetablock = brotli_min_int(24, lgwin + 1);
  size_t max_block_size;
  const size_t max_metablock_size = ((size_t) 1) << lgmetablock;
  const size_t max_literals_per_metablock = max_metablock_size / 8;
  const size_t max_commands_per_metablock = max_metablock_size / 8;
  size_t metablock_start = 0;
  uint8_t prev_byte = 0;
  uint8_t prev_byte2 = 0;
  Hasher hasher;
  HasherInit(&hasher);
  BrotliEncoderInitParams(&params);
  params.quality = 10;
  params.lgwin = lgwin;
  if (lgwin > 24)
  {
    params.large_window = 1;
  }
  SanitizeParams(&params);
  params.lgblock = ComputeLgBlock(&params);
  ChooseDistanceParams(&params);
  max_block_size = ((size_t) 1) << params.lgblock;
  BrotliInitMemoryManager(m, 0, 0, 0);
  ;
  EncodeWindowBits(lgwin, params.large_window, &last_bytes, &last_bytes_bits);
  InitOrStitchToPreviousBlock(m, &hasher, input_buffer, mask, &params, 0, hasher_eff_size, 1);
  if (!(!0))
  {
    goto oom;
  }
  while (ok && (metablock_start < input_size))
  {
    helper_BrotliCompressBufferQuality10_1(&encoded_buffer_idx, &ok, &total_out_size, &last_bytes, &last_bytes_bits, &metablock_start, &prev_byte, &prev_byte2, input_size, input_buffer, encoded_buffer, m, mask, dist_cache, saved_dist_cache, max_out_size, params, max_block_size, max_metablock_size, max_literals_per_metablock, max_commands_per_metablock, hasher);
  }

  *encoded_size = total_out_size;
  DestroyHasher(m, &hasher);
  return ok;
  oom:
  BrotliWipeOutMemoryManager(m);

  return 0;
}


----------------------------
static size_t MakeUncompressedStream(const uint8_t *input, size_t input_size, uint8_t *output)
{
  size_t size = input_size;
  size_t result = 0;
  size_t offset = 0;
  if (input_size == 0)
  {
    output[0] = 6;
    return 1;
  }
  output[result] = 0x21;
  result += 1;
  output[result] = 0x03;
  result += 1;
  while (size > 0)
  {
    helper_MakeUncompressedStream_1(&size, &result, &offset, input, output);
  }

  output[result++] = 3;
  return result;
}


----------------------------
***/


