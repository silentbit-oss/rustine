typedef struct 
{
  HuffmanCode **htrees;
  HuffmanCode *codes;
  uint16_t alphabet_size_max;
  uint16_t alphabet_size_limit;
  uint16_t num_htrees;
} HuffmanTreeGroup
/*** DEPENDENCIES:
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


