typedef struct BrotliEncoderStateStruct BrotliEncoderState
/*** DEPENDENCIES:
typedef struct BrotliEncoderStateStruct
{
  BrotliEncoderParams params;
  MemoryManager memory_manager_;
  uint64_t input_pos_;
  RingBuffer ringbuffer_;
  size_t cmd_alloc_size_;
  Command *commands_;
  size_t num_commands_;
  size_t num_literals_;
  size_t last_insert_len_;
  uint64_t last_flush_pos_;
  uint64_t last_processed_pos_;
  int dist_cache_[16];
  int saved_dist_cache_[4];
  uint16_t last_bytes_;
  uint8_t last_bytes_bits_;
  int8_t flint_;
  uint8_t prev_byte_;
  uint8_t prev_byte2_;
  size_t storage_size_;
  uint8_t *storage_;
  Hasher hasher_;
  int small_table_[1 << 10];
  int *large_table_;
  size_t large_table_size_;
  uint8_t cmd_depths_[128];
  uint16_t cmd_bits_[128];
  uint8_t cmd_code_[512];
  size_t cmd_code_numbits_;
  uint32_t *command_buf_;
  uint8_t *literal_buf_;
  uint8_t *next_out_;
  size_t available_out_;
  size_t total_out_;
  union 
  {
    uint64_t u64[2];
    uint8_t u8[16];
  } tiny_buf_;
  uint32_t remaining_metadata_bytes_;
  BrotliEncoderStreamState stream_state_;
  int is_last_block_emitted_;
  int is_initialized_;
} BrotliEncoderStateStruct
----------------------------
***/


