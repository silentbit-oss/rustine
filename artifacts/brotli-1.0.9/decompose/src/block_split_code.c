typedef struct BlockSplitCode
{
  BlockTypeCodeCalculator type_code_calculator;
  uint8_t type_depths[256 + 2];
  uint16_t type_bits[256 + 2];
  uint8_t length_depths[26];
  uint16_t length_bits[26];
} BlockSplitCode
/*** DEPENDENCIES:
typedef struct BlockTypeCodeCalculator
{
  size_t last_type;
  size_t second_last_type;
} BlockTypeCodeCalculator
----------------------------
***/


