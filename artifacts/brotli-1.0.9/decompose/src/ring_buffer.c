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
/*** DEPENDENCIES:
***/


