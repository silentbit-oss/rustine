inline static int NextTableBitSize(const uint16_t * const count, int len, int root_bits)
{
  int left = 1 << (len - root_bits);
  while (len < 15)
  {
    left -= count[len];
    if (left <= 0)
    {
      break;
    }
    len += 1;
    left <<= 1;
  }

  return len - root_bits;
}


/*** DEPENDENCIES:
***/


// hint:  ['symbol_ref is a mutable refrence to int', 'bits_ref is a mutable refrence to int']
void helper_helper_BrotliBuildCodeLengthsHuffmanTable_2_1(int * const symbol_ref, int * const bits_ref, uint16_t * const count, int offset[5 + 1])
{
  int symbol = *symbol_ref;
  int bits = *bits_ref;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  *symbol_ref = symbol;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
***/


// hint:  ['symbol_ref is a mutable refrence to int']
void helper_helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1_1(int * const symbol_ref, const uint8_t * const code_lengths, int sorted[17 + 1], int offset[5 + 1])
{
  int symbol = *symbol_ref;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  *symbol_ref = symbol;
}


/*** DEPENDENCIES:
***/


inline static uint64_t BrotliReverseBits(uint64_t num)
{
  return kReverseBits[num];
}


/*** DEPENDENCIES:
static uint8_t kReverseBits[1 << 8] = {0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, 0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, 0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, 0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF}
----------------------------
***/


inline static void ReplicateValue(HuffmanCode *table, int step, int end, HuffmanCode code)
{
  do
  {
    end -= step;
    table[end] = code;
  }
  while (end > 0);
}


/*** DEPENDENCIES:
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


// hint:  ['symbol_ref is a mutable refrence to int']
void helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1(int * const symbol_ref, const uint8_t * const code_lengths, int sorted[17 + 1], int offset[5 + 1])
{
  int symbol = *symbol_ref;
  if ((6 & 1) != 0)
  {
    {
      symbol -= 1;
      sorted[offset[code_lengths[symbol]]--] = symbol;
    }
    ;
  }
  if ((6 & 2) != 0)
  {
    {
      symbol -= 1;
      sorted[offset[code_lengths[symbol]]--] = symbol;
    }
    ;
    {
      symbol -= 1;
      sorted[offset[code_lengths[symbol]]--] = symbol;
    }
    ;
  }
  if ((6 & 4) != 0)
  {
    helper_helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1_1(&symbol, code_lengths, sorted, offset);
  }
  *symbol_ref = symbol;
}


/*** DEPENDENCIES:
void helper_helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1_1(int * const symbol_ref, const uint8_t * const code_lengths, int sorted[17 + 1], int offset[5 + 1])
{
  int symbol = *symbol_ref;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  {
    symbol -= 1;
    sorted[offset[code_lengths[symbol]]--] = symbol;
  }
  ;
  *symbol_ref = symbol;
}


----------------------------
***/


// hint:  ['symbol_ref is a mutable refrence to int']
void helper_BrotliBuildCodeLengthsHuffmanTable_1(int * const symbol_ref, const uint8_t * const code_lengths, int sorted[17 + 1], int offset[5 + 1])
{
  int symbol = *symbol_ref;
  {
    helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1(&symbol, code_lengths, sorted, offset);
  }
  ;
  *symbol_ref = symbol;
}


/*** DEPENDENCIES:
void helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1(int * const symbol_ref, const uint8_t * const code_lengths, int sorted[17 + 1], int offset[5 + 1])
{
  int symbol = *symbol_ref;
  if ((6 & 1) != 0)
  {
    {
      symbol -= 1;
      sorted[offset[code_lengths[symbol]]--] = symbol;
    }
    ;
  }
  if ((6 & 2) != 0)
  {
    {
      symbol -= 1;
      sorted[offset[code_lengths[symbol]]--] = symbol;
    }
    ;
    {
      symbol -= 1;
      sorted[offset[code_lengths[symbol]]--] = symbol;
    }
    ;
  }
  if ((6 & 4) != 0)
  {
    helper_helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1_1(&symbol, code_lengths, sorted, offset);
  }
  *symbol_ref = symbol;
}


----------------------------
***/


// hint:  ['symbol_ref is a mutable refrence to int', 'bits_ref is a mutable refrence to int']
void helper_BrotliBuildCodeLengthsHuffmanTable_2(int * const symbol_ref, int * const bits_ref, uint16_t * const count, int offset[5 + 1])
{
  int symbol = *symbol_ref;
  int bits = *bits_ref;
  if ((5 & 1) != 0)
  {
    {
      symbol += count[bits];
      offset[bits] = symbol;
      bits += 1;
    }
    ;
  }
  if ((5 & 2) != 0)
  {
    {
      symbol += count[bits];
      offset[bits] = symbol;
      bits += 1;
    }
    ;
    {
      symbol += count[bits];
      offset[bits] = symbol;
      bits += 1;
    }
    ;
  }
  if ((5 & 4) != 0)
  {
    helper_helper_BrotliBuildCodeLengthsHuffmanTable_2_1(&symbol, &bits, count, offset);
  }
  *symbol_ref = symbol;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
void helper_helper_BrotliBuildCodeLengthsHuffmanTable_2_1(int * const symbol_ref, int * const bits_ref, uint16_t * const count, int offset[5 + 1])
{
  int symbol = *symbol_ref;
  int bits = *bits_ref;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  {
    symbol += count[bits];
    offset[bits] = symbol;
    bits += 1;
  }
  ;
  *symbol_ref = symbol;
  *bits_ref = bits;
}


----------------------------
***/


// hint:  ['code_ref is a mutable refrence to HuffmanCode', 'table_idx_ref is a mutable refrence to unsigned int', 'symbol_ref is a mutable refrence to int', 'key_ref is a mutable refrence to uint64_t', 'sub_key_ref is a mutable refrence to uint64_t', 'table_bits_ref is a mutable refrence to int', 'table_size_ref is a mutable refrence to int', 'total_size_ref is a mutable refrence to int']
void helper_helper_BrotliBuildHuffmanTable_1_1(HuffmanCode * const code_ref, unsigned int * const table_idx_ref, int * const symbol_ref, uint64_t * const key_ref, uint64_t * const sub_key_ref, int * const table_bits_ref, int * const table_size_ref, int * const total_size_ref, HuffmanCode * const root_table, int root_bits, const uint16_t * const symbol_lists, uint16_t * const count, HuffmanCode * const table, uint64_t key_step, int len, uint64_t sub_key_step, int step)
{
  HuffmanCode code = *code_ref;
  unsigned int table_idx = *table_idx_ref;
  int symbol = *symbol_ref;
  uint64_t key = *key_ref;
  uint64_t sub_key = *sub_key_ref;
  int table_bits = *table_bits_ref;
  int table_size = *table_size_ref;
  int total_size = *total_size_ref;
  if (sub_key == ((((uint64_t) 1) << ((8 - 1) + 0)) << 1U))
  {
    table_idx += table_size;
    table_bits = NextTableBitSize(count, len, root_bits);
    table_size = 1 << table_bits;
    total_size += table_size;
    sub_key = BrotliReverseBits(key);
    key += key_step;
    root_table[sub_key] = ConstructHuffmanCode((uint8_t) (table_bits + root_bits), (uint16_t) (((size_t) ((&table[table_idx]) - root_table)) - sub_key));
    sub_key = 0;
  }
  symbol = symbol_lists[symbol];
  code = ConstructHuffmanCode((uint8_t) (len - root_bits), (uint16_t) symbol);
  ReplicateValue(&table[BrotliReverseBits(sub_key) + table_idx], step, table_size, code);
  sub_key += sub_key_step;
  *code_ref = code;
  *table_idx_ref = table_idx;
  *symbol_ref = symbol;
  *key_ref = key;
  *sub_key_ref = sub_key;
  *table_bits_ref = table_bits;
  *table_size_ref = table_size;
  *total_size_ref = total_size;
}


/*** DEPENDENCIES:
inline static HuffmanCode ConstructHuffmanCode(const uint8_t bits, const uint16_t value)
{
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}


----------------------------
inline static void ReplicateValue(HuffmanCode *table, int step, int end, HuffmanCode code)
{
  do
  {
    end -= step;
    table[end] = code;
  }
  while (end > 0);
}


----------------------------
inline static uint64_t BrotliReverseBits(uint64_t num)
{
  return kReverseBits[num];
}


----------------------------
inline static int NextTableBitSize(const uint16_t * const count, int len, int root_bits)
{
  int left = 1 << (len - root_bits);
  while (len < 15)
  {
    left -= count[len];
    if (left <= 0)
    {
      break;
    }
    len += 1;
    left <<= 1;
  }

  return len - root_bits;
}


----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


// hint:  ['code_ref is a mutable refrence to HuffmanCode', 'table_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to int', 'symbol_ref is a mutable refrence to int', 'key_ref is a mutable refrence to uint64_t', 'sub_key_ref is a mutable refrence to uint64_t', 'sub_key_step_ref is a mutable refrence to uint64_t', 'step_ref is a mutable refrence to int', 'table_bits_ref is a mutable refrence to int', 'table_size_ref is a mutable refrence to int', 'total_size_ref is a mutable refrence to int']
void helper_BrotliBuildHuffmanTable_1(HuffmanCode * const code_ref, unsigned int * const table_idx_ref, int * const len_ref, int * const symbol_ref, uint64_t * const key_ref, uint64_t * const sub_key_ref, uint64_t * const sub_key_step_ref, int * const step_ref, int * const table_bits_ref, int * const table_size_ref, int * const total_size_ref, HuffmanCode * const root_table, int root_bits, const uint16_t * const symbol_lists, uint16_t * const count, HuffmanCode * const table, uint64_t key_step)
{
  HuffmanCode code = *code_ref;
  unsigned int table_idx = *table_idx_ref;
  int len = *len_ref;
  int symbol = *symbol_ref;
  uint64_t key = *key_ref;
  uint64_t sub_key = *sub_key_ref;
  uint64_t sub_key_step = *sub_key_step_ref;
  int step = *step_ref;
  int table_bits = *table_bits_ref;
  int table_size = *table_size_ref;
  int total_size = *total_size_ref;
  symbol = len - (15 + 1);
  for (; count[len] != 0; count[len] -= 1)
  {
    helper_helper_BrotliBuildHuffmanTable_1_1(&code, &table_idx, &symbol, &key, &sub_key, &table_bits, &table_size, &total_size, root_table, root_bits, symbol_lists, count, table, key_step, len, sub_key_step, step);
  }

  step <<= 1;
  sub_key_step >>= 1;
  *code_ref = code;
  *table_idx_ref = table_idx;
  *len_ref = len;
  *symbol_ref = symbol;
  *key_ref = key;
  *sub_key_ref = sub_key;
  *sub_key_step_ref = sub_key_step;
  *step_ref = step;
  *table_bits_ref = table_bits;
  *table_size_ref = table_size;
  *total_size_ref = total_size;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
void helper_helper_BrotliBuildHuffmanTable_1_1(HuffmanCode * const code_ref, unsigned int * const table_idx_ref, int * const symbol_ref, uint64_t * const key_ref, uint64_t * const sub_key_ref, int * const table_bits_ref, int * const table_size_ref, int * const total_size_ref, HuffmanCode * const root_table, int root_bits, const uint16_t * const symbol_lists, uint16_t * const count, HuffmanCode * const table, uint64_t key_step, int len, uint64_t sub_key_step, int step)
{
  HuffmanCode code = *code_ref;
  unsigned int table_idx = *table_idx_ref;
  int symbol = *symbol_ref;
  uint64_t key = *key_ref;
  uint64_t sub_key = *sub_key_ref;
  int table_bits = *table_bits_ref;
  int table_size = *table_size_ref;
  int total_size = *total_size_ref;
  if (sub_key == ((((uint64_t) 1) << ((8 - 1) + 0)) << 1U))
  {
    table_idx += table_size;
    table_bits = NextTableBitSize(count, len, root_bits);
    table_size = 1 << table_bits;
    total_size += table_size;
    sub_key = BrotliReverseBits(key);
    key += key_step;
    root_table[sub_key] = ConstructHuffmanCode((uint8_t) (table_bits + root_bits), (uint16_t) (((size_t) ((&table[table_idx]) - root_table)) - sub_key));
    sub_key = 0;
  }
  symbol = symbol_lists[symbol];
  code = ConstructHuffmanCode((uint8_t) (len - root_bits), (uint16_t) symbol);
  ReplicateValue(&table[BrotliReverseBits(sub_key) + table_idx], step, table_size, code);
  sub_key += sub_key_step;
  *code_ref = code;
  *table_idx_ref = table_idx;
  *symbol_ref = symbol;
  *key_ref = key;
  *sub_key_ref = sub_key;
  *table_bits_ref = table_bits;
  *table_size_ref = table_size;
  *total_size_ref = total_size;
}


----------------------------
***/


// hint:  ['table_size_ref is a mutable refrence to uint32_t']
void helper_BrotliBuildSimpleHuffmanTable_1(uint32_t * const table_size_ref, HuffmanCode * const table, uint16_t * const val)
{
  uint32_t table_size = *table_size_ref;
  int i;
  int k;
  for (i = 0; i < 3; i += 1)
  {
    for (k = i + 1; k < 4; k += 1)
    {
      if (val[k] < val[i])
      {
        uint16_t t = val[k];
        val[k] = val[i];
        val[i] = t;
      }
    }

  }

  table[0] = ConstructHuffmanCode(2, val[0]);
  table[2] = ConstructHuffmanCode(2, val[1]);
  table[1] = ConstructHuffmanCode(2, val[2]);
  table[3] = ConstructHuffmanCode(2, val[3]);
  table_size = 4;
  break;
  *table_size_ref = table_size;
}


/*** DEPENDENCIES:
inline static HuffmanCode ConstructHuffmanCode(const uint8_t bits, const uint16_t value)
{
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}


----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


// hint:  ['table_size_ref is a mutable refrence to uint32_t']
void helper_BrotliBuildSimpleHuffmanTable_2(uint32_t * const table_size_ref, HuffmanCode * const table, uint16_t * const val)
{
  uint32_t table_size = *table_size_ref;
  if (val[3] < val[2])
  {
    uint16_t t = val[3];
    val[3] = val[2];
    val[2] = t;
  }
  table[0] = ConstructHuffmanCode(1, val[0]);
  table[1] = ConstructHuffmanCode(2, val[1]);
  table[2] = ConstructHuffmanCode(1, val[0]);
  table[3] = ConstructHuffmanCode(3, val[2]);
  table[4] = ConstructHuffmanCode(1, val[0]);
  table[5] = ConstructHuffmanCode(2, val[1]);
  table[6] = ConstructHuffmanCode(1, val[0]);
  table[7] = ConstructHuffmanCode(3, val[3]);
  table_size = 8;
  break;
  *table_size_ref = table_size;
}


/*** DEPENDENCIES:
inline static HuffmanCode ConstructHuffmanCode(const uint8_t bits, const uint16_t value)
{
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}


----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


uint32_t BrotliBuildSimpleHuffmanTable(HuffmanCode *table, int root_bits, uint16_t *val, uint32_t num_symbols)
{
  uint32_t table_size = 1;
  const uint32_t goal_size = 1U << root_bits;
  switch (num_symbols)
  {
    case 0:
    {
      table[0] = ConstructHuffmanCode(0, val[0]);
      break;
    }

    case 1:
    {
      if (val[1] > val[0])
      {
        table[0] = ConstructHuffmanCode(1, val[0]);
        table[1] = ConstructHuffmanCode(1, val[1]);
      }
      else
      {
        table[0] = ConstructHuffmanCode(1, val[1]);
        table[1] = ConstructHuffmanCode(1, val[0]);
      }
      table_size = 2;
      break;
    }

    case 2:
    {
      table[0] = ConstructHuffmanCode(1, val[0]);
      table[2] = ConstructHuffmanCode(1, val[0]);
      if (val[2] > val[1])
      {
        table[1] = ConstructHuffmanCode(2, val[1]);
        table[3] = ConstructHuffmanCode(2, val[2]);
      }
      else
      {
        table[1] = ConstructHuffmanCode(2, val[2]);
        table[3] = ConstructHuffmanCode(2, val[1]);
      }
      table_size = 4;
      break;
    }

    case 3:
    {
      helper_BrotliBuildSimpleHuffmanTable_1(&table_size, table, val);
    }

    case 4:
    {
      helper_BrotliBuildSimpleHuffmanTable_2(&table_size, table, val);
    }

  }

  while (table_size != goal_size)
  {
    memcpy(&table[table_size], &table[0], ((size_t) table_size) * (sizeof(table[0])));
    table_size <<= 1;
  }

  return goal_size;
}


/*** DEPENDENCIES:
inline static HuffmanCode ConstructHuffmanCode(const uint8_t bits, const uint16_t value)
{
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}


----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
void helper_BrotliBuildSimpleHuffmanTable_1(uint32_t * const table_size_ref, HuffmanCode * const table, uint16_t * const val)
{
  uint32_t table_size = *table_size_ref;
  int i;
  int k;
  for (i = 0; i < 3; i += 1)
  {
    for (k = i + 1; k < 4; k += 1)
    {
      if (val[k] < val[i])
      {
        uint16_t t = val[k];
        val[k] = val[i];
        val[i] = t;
      }
    }

  }

  table[0] = ConstructHuffmanCode(2, val[0]);
  table[2] = ConstructHuffmanCode(2, val[1]);
  table[1] = ConstructHuffmanCode(2, val[2]);
  table[3] = ConstructHuffmanCode(2, val[3]);
  table_size = 4;
  break;
  *table_size_ref = table_size;
}


----------------------------
void helper_BrotliBuildSimpleHuffmanTable_2(uint32_t * const table_size_ref, HuffmanCode * const table, uint16_t * const val)
{
  uint32_t table_size = *table_size_ref;
  if (val[3] < val[2])
  {
    uint16_t t = val[3];
    val[3] = val[2];
    val[2] = t;
  }
  table[0] = ConstructHuffmanCode(1, val[0]);
  table[1] = ConstructHuffmanCode(2, val[1]);
  table[2] = ConstructHuffmanCode(1, val[0]);
  table[3] = ConstructHuffmanCode(3, val[2]);
  table[4] = ConstructHuffmanCode(1, val[0]);
  table[5] = ConstructHuffmanCode(2, val[1]);
  table[6] = ConstructHuffmanCode(1, val[0]);
  table[7] = ConstructHuffmanCode(3, val[3]);
  table_size = 8;
  break;
  *table_size_ref = table_size;
}


----------------------------
***/


uint32_t BrotliBuildHuffmanTable(HuffmanCode *root_table, int root_bits, const uint16_t * const symbol_lists, uint16_t *count)
{
  HuffmanCode code;
  HuffmanCode *table;
  unsigned int table_idx = 0;
  int len;
  int symbol;
  uint64_t key;
  uint64_t key_step;
  uint64_t sub_key;
  uint64_t sub_key_step;
  int step;
  int table_bits;
  int table_size;
  int total_size;
  int max_length = -1;
  int bits;
  int bits_count;
  ;
  ;
  while (symbol_lists[max_length] == 0xFFFF)
    max_length--;

  max_length -= 1;
  max_length += 15 + 1;
  table_idx = root_table;
  table_bits = root_bits;
  table_size = 1 << table_bits;
  total_size = table_size;
  if (table_bits > max_length)
  {
    table_bits = max_length;
    table_size = 1 << table_bits;
  }
  key = 0;
  key_step = ((uint64_t) 1) << ((8 - 1) + 0);
  bits = 1;
  step = 2;
  do
  {
    symbol = bits - (15 + 1);
    for (bits_count = count[bits]; bits_count != 0; bits_count -= 1)
    {
      symbol = symbol_lists[symbol];
      code = ConstructHuffmanCode((uint8_t) bits, (uint16_t) symbol);
      ReplicateValue(&table[BrotliReverseBits(key) + table_idx], step, table_size, code);
      key += key_step;
    }

    step <<= 1;
    key_step >>= 1;
  }
  while ((++bits) <= table_bits);
  while (total_size != table_size)
  {
    memcpy(&table[table_size + table_idx], &table[0 + table_idx], ((size_t) table_size) * (sizeof(table[0 + table_idx])));
    table_size <<= 1;
  }

  key_step = (((uint64_t) 1) << ((8 - 1) + 0)) >> (root_bits - 1);
  sub_key = (((uint64_t) 1) << ((8 - 1) + 0)) << 1;
  sub_key_step = ((uint64_t) 1) << ((8 - 1) + 0);
  for (len = root_bits + 1, step = 2; len <= max_length; len += 1)
  {
    helper_BrotliBuildHuffmanTable_1(&code, &table_idx, &len, &symbol, &key, &sub_key, &sub_key_step, &step, &table_bits, &table_size, &total_size, root_table, root_bits, symbol_lists, count, table, key_step);
  }

  return (uint32_t) total_size;
}


/*** DEPENDENCIES:
inline static HuffmanCode ConstructHuffmanCode(const uint8_t bits, const uint16_t value)
{
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}


----------------------------
inline static void ReplicateValue(HuffmanCode *table, int step, int end, HuffmanCode code)
{
  do
  {
    end -= step;
    table[end] = code;
  }
  while (end > 0);
}


----------------------------
inline static uint64_t BrotliReverseBits(uint64_t num)
{
  return kReverseBits[num];
}


----------------------------
void helper_BrotliBuildHuffmanTable_1(HuffmanCode * const code_ref, unsigned int * const table_idx_ref, int * const len_ref, int * const symbol_ref, uint64_t * const key_ref, uint64_t * const sub_key_ref, uint64_t * const sub_key_step_ref, int * const step_ref, int * const table_bits_ref, int * const table_size_ref, int * const total_size_ref, HuffmanCode * const root_table, int root_bits, const uint16_t * const symbol_lists, uint16_t * const count, HuffmanCode * const table, uint64_t key_step)
{
  HuffmanCode code = *code_ref;
  unsigned int table_idx = *table_idx_ref;
  int len = *len_ref;
  int symbol = *symbol_ref;
  uint64_t key = *key_ref;
  uint64_t sub_key = *sub_key_ref;
  uint64_t sub_key_step = *sub_key_step_ref;
  int step = *step_ref;
  int table_bits = *table_bits_ref;
  int table_size = *table_size_ref;
  int total_size = *total_size_ref;
  symbol = len - (15 + 1);
  for (; count[len] != 0; count[len] -= 1)
  {
    helper_helper_BrotliBuildHuffmanTable_1_1(&code, &table_idx, &symbol, &key, &sub_key, &table_bits, &table_size, &total_size, root_table, root_bits, symbol_lists, count, table, key_step, len, sub_key_step, step);
  }

  step <<= 1;
  sub_key_step >>= 1;
  *code_ref = code;
  *table_idx_ref = table_idx;
  *len_ref = len;
  *symbol_ref = symbol;
  *key_ref = key;
  *sub_key_ref = sub_key;
  *sub_key_step_ref = sub_key_step;
  *step_ref = step;
  *table_bits_ref = table_bits;
  *table_size_ref = table_size;
  *total_size_ref = total_size;
}


----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


void BrotliBuildCodeLengthsHuffmanTable(HuffmanCode *table, const uint8_t * const code_lengths, uint16_t *count)
{
  HuffmanCode code;
  int symbol;
  uint64_t key;
  uint64_t key_step;
  int step;
  int table_size;
  int sorted[17 + 1];
  int offset[5 + 1];
  int bits;
  int bits_count;
  ;
  symbol = -1;
  bits = 1;
  {
    helper_BrotliBuildCodeLengthsHuffmanTable_2(&symbol, &bits, count, offset);
  }
  ;
  offset[0] = (17 + 1) - 1;
  symbol = 17 + 1;
  do
  {
    helper_BrotliBuildCodeLengthsHuffmanTable_1(&symbol, code_lengths, sorted, offset);
  }
  while (symbol != 0);
  table_size = 1 << 5;
  if (offset[0] == 0)
  {
    code = ConstructHuffmanCode(0, (uint16_t) sorted[0]);
    for (key = 0; key < ((uint64_t) table_size); key += 1)
    {
      table[key] = code;
    }

    return;
  }
  key = 0;
  key_step = ((uint64_t) 1) << ((8 - 1) + 0);
  symbol = 0;
  bits = 1;
  step = 2;
  do
  {
    for (bits_count = count[bits]; bits_count != 0; bits_count -= 1)
    {
      code = ConstructHuffmanCode((uint8_t) bits, (uint16_t) sorted[symbol]);
      symbol += 1;
      ReplicateValue(&table[BrotliReverseBits(key)], step, table_size, code);
      key += key_step;
    }

    step <<= 1;
    key_step >>= 1;
  }
  while ((++bits) <= 5);
}


/*** DEPENDENCIES:
inline static HuffmanCode ConstructHuffmanCode(const uint8_t bits, const uint16_t value)
{
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}


----------------------------
void helper_BrotliBuildCodeLengthsHuffmanTable_1(int * const symbol_ref, const uint8_t * const code_lengths, int sorted[17 + 1], int offset[5 + 1])
{
  int symbol = *symbol_ref;
  {
    helper_helper_BrotliBuildCodeLengthsHuffmanTable_1_1(&symbol, code_lengths, sorted, offset);
  }
  ;
  *symbol_ref = symbol;
}


----------------------------
inline static void ReplicateValue(HuffmanCode *table, int step, int end, HuffmanCode code)
{
  do
  {
    end -= step;
    table[end] = code;
  }
  while (end > 0);
}


----------------------------
inline static uint64_t BrotliReverseBits(uint64_t num)
{
  return kReverseBits[num];
}


----------------------------
void helper_BrotliBuildCodeLengthsHuffmanTable_2(int * const symbol_ref, int * const bits_ref, uint16_t * const count, int offset[5 + 1])
{
  int symbol = *symbol_ref;
  int bits = *bits_ref;
  if ((5 & 1) != 0)
  {
    {
      symbol += count[bits];
      offset[bits] = symbol;
      bits += 1;
    }
    ;
  }
  if ((5 & 2) != 0)
  {
    {
      symbol += count[bits];
      offset[bits] = symbol;
      bits += 1;
    }
    ;
    {
      symbol += count[bits];
      offset[bits] = symbol;
      bits += 1;
    }
    ;
  }
  if ((5 & 4) != 0)
  {
    helper_helper_BrotliBuildCodeLengthsHuffmanTable_2_1(&symbol, &bits, count, offset);
  }
  *symbol_ref = symbol;
  *bits_ref = bits;
}


----------------------------
typedef struct 
{
  uint8_t bits;
  uint16_t value;
} HuffmanCode
----------------------------
***/


