inline static uint32_t BitMask(uint32_t n)
{
  if ((!(!__builtin_constant_p(n))) || (!(!0)))
  {
    return ~(0xFFFFFFFFu << n);
  }
  else
  {
    return kBrotliBitMask[n];
  }
}


/*** DEPENDENCIES:
extern const uint32_t kBrotliBitMask[33]
----------------------------
***/


void BrotliInitBitReader(BrotliBitReader * const br)
{
  br->val_ = 0;
  br->bit_pos_ = (sizeof(br->val_)) << 3;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static int BrotliCheckInputAmount(BrotliBitReader * const br, size_t num)
{
  return (!(!(br->avail_in >= num))) ? (1) : (0);
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static int BrotliPullByte(BrotliBitReader * const br)
{
  if (br->avail_in == 0)
  {
    return 0;
  }
  br->val_ >>= 8;
  br->val_ |= ((uint64_t) (*br->next_in)) << 56;
  br->bit_pos_ -= 8;
  br->avail_in -= 1;
  br->next_in += 1;
  return 1;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static void BrotliDropBits(BrotliBitReader * const br, uint32_t n_bits)
{
  br->bit_pos_ += n_bits;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static void BrotliBitReaderSaveState(BrotliBitReader * const from, BrotliBitReaderState *to)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReaderState
----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static void BrotliBitReaderRestoreState(BrotliBitReader * const to, BrotliBitReaderState *from)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReaderState
----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static size_t BrotliGetRemainingBytes(BrotliBitReader *br)
{
  static const size_t kCap = ((size_t) 1) << 30;
  if (br->avail_in > kCap)
  {
    return kCap;
  }
  return br->avail_in + (BrotliGetAvailableBits(br) >> 3);
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static void BrotliFillBitWindow(BrotliBitReader * const br, uint32_t n_bits)
{
  if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 8))
  {
    if (br->bit_pos_ >= 56)
    {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  }
  else
    if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 16))
  {
    if (br->bit_pos_ >= 48)
    {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  }
  else
  {
    if (br->bit_pos_ >= 32)
    {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t) BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t)) >> 1;
      br->next_in += (sizeof(uint64_t)) >> 1;
    }
  }
}


/*** DEPENDENCIES:
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


inline static void BrotliFillBitWindow16(BrotliBitReader * const br)
{
  BrotliFillBitWindow(br, 17);
}


/*** DEPENDENCIES:
inline static void BrotliFillBitWindow(BrotliBitReader * const br, uint32_t n_bits)
{
  if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 8))
  {
    if (br->bit_pos_ >= 56)
    {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  }
  else
    if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 16))
  {
    if (br->bit_pos_ >= 48)
    {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  }
  else
  {
    if (br->bit_pos_ >= 32)
    {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t) BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t)) >> 1;
      br->next_in += (sizeof(uint64_t)) >> 1;
    }
  }
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static void BrotliBitReaderUnload(BrotliBitReader *br)
{
  uint32_t unused_bytes = BrotliGetAvailableBits(br) >> 3;
  uint32_t unused_bits = unused_bytes << 3;
  br->avail_in += unused_bytes;
  br->next_in -= unused_bytes;
  if (unused_bits == ((sizeof(br->val_)) << 3))
  {
    br->val_ = 0;
  }
  else
  {
    br->val_ <<= unused_bits;
  }
  br->bit_pos_ += unused_bits;
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}


/*** DEPENDENCIES:
inline static void BrotliDropBits(BrotliBitReader * const br, uint32_t n_bits)
{
  br->bit_pos_ += n_bits;
}


----------------------------
inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}


----------------------------
inline static uint32_t BitMask(uint32_t n)
{
  if ((!(!__builtin_constant_p(n))) || (!(!0)))
  {
    return ~(0xFFFFFFFFu << n);
  }
  else
  {
    return kBrotliBitMask[n];
  }
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static int BrotliSafeReadBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  ;
  while (BrotliGetAvailableBits(br) < n_bits)
  {
    if (!BrotliPullByte(br))
    {
      return 0;
    }
  }

  BrotliTakeBits(br, n_bits, val);
  return 1;
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}


----------------------------
inline static int BrotliPullByte(BrotliBitReader * const br)
{
  if (br->avail_in == 0)
  {
    return 0;
  }
  br->val_ >>= 8;
  br->val_ |= ((uint64_t) (*br->next_in)) << 56;
  br->bit_pos_ -= 8;
  br->avail_in -= 1;
  br->next_in += 1;
  return 1;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


int BrotliSafeReadBits32Slow(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  uint32_t low_val;
  uint32_t high_val;
  BrotliBitReaderState memento;
  ;
  ;
  BrotliBitReaderSaveState(br, &memento);
  if ((!BrotliSafeReadBits(br, 16, &low_val)) || (!BrotliSafeReadBits(br, n_bits - 16, &high_val)))
  {
    BrotliBitReaderRestoreState(br, &memento);
    return 0;
  }
  *val = low_val | (high_val << 16);
  return 1;
}


/*** DEPENDENCIES:
inline static int BrotliSafeReadBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  ;
  while (BrotliGetAvailableBits(br) < n_bits)
  {
    if (!BrotliPullByte(br))
    {
      return 0;
    }
  }

  BrotliTakeBits(br, n_bits, val);
  return 1;
}


----------------------------
inline static void BrotliBitReaderRestoreState(BrotliBitReader * const to, BrotliBitReaderState *from)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReaderState
----------------------------
inline static void BrotliBitReaderSaveState(BrotliBitReader * const from, BrotliBitReaderState *to)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}


----------------------------
***/


inline static int BrotliSafeReadBits32(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  ;
  if (1 || (n_bits <= 24))
  {
    while (BrotliGetAvailableBits(br) < n_bits)
    {
      if (!BrotliPullByte(br))
      {
        return 0;
      }
    }

    BrotliTakeBits(br, n_bits, val);
    return 1;
  }
  else
  {
    return BrotliSafeReadBits32Slow(br, n_bits, val);
  }
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
int BrotliSafeReadBits32Slow(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  uint32_t low_val;
  uint32_t high_val;
  BrotliBitReaderState memento;
  ;
  ;
  BrotliBitReaderSaveState(br, &memento);
  if ((!BrotliSafeReadBits(br, 16, &low_val)) || (!BrotliSafeReadBits(br, n_bits - 16, &high_val)))
  {
    BrotliBitReaderRestoreState(br, &memento);
    return 0;
  }
  *val = low_val | (high_val << 16);
  return 1;
}


----------------------------
inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}


----------------------------
inline static int BrotliPullByte(BrotliBitReader * const br)
{
  if (br->avail_in == 0)
  {
    return 0;
  }
  br->val_ >>= 8;
  br->val_ |= ((uint64_t) (*br->next_in)) << 56;
  br->bit_pos_ -= 8;
  br->avail_in -= 1;
  br->next_in += 1;
  return 1;
}


----------------------------
***/


int BrotliWarmupBitReader(BrotliBitReader * const br)
{
  size_t aligned_read_mask = ((sizeof(br->val_)) >> 1) - 1;
  if (!(!(!0)))
  {
    aligned_read_mask = 0;
  }
  if (BrotliGetAvailableBits(br) == 0)
  {
    if (!BrotliPullByte(br))
    {
      return 0;
    }
  }
  while ((((size_t) br->next_in) & aligned_read_mask) != 0)
  {
    if (!BrotliPullByte(br))
    {
      return 1;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
inline static int BrotliPullByte(BrotliBitReader * const br)
{
  if (br->avail_in == 0)
  {
    return 0;
  }
  br->val_ >>= 8;
  br->val_ |= ((uint64_t) (*br->next_in)) << 56;
  br->bit_pos_ -= 8;
  br->avail_in -= 1;
  br->next_in += 1;
  return 1;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static uint32_t BrotliGet16BitsUnmasked(BrotliBitReader * const br)
{
  BrotliFillBitWindow(br, 16);
  return (uint32_t) BrotliGetBitsUnmasked(br);
}


/*** DEPENDENCIES:
inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}


----------------------------
inline static void BrotliFillBitWindow(BrotliBitReader * const br, uint32_t n_bits)
{
  if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 8))
  {
    if (br->bit_pos_ >= 56)
    {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  }
  else
    if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 16))
  {
    if (br->bit_pos_ >= 48)
    {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  }
  else
  {
    if (br->bit_pos_ >= 32)
    {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t) BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t)) >> 1;
      br->next_in += (sizeof(uint64_t)) >> 1;
    }
  }
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static uint32_t BrotliReadBits24(BrotliBitReader * const br, uint32_t n_bits)
{
  ;
  if (1 || (n_bits <= 16))
  {
    uint32_t val;
    BrotliFillBitWindow(br, n_bits);
    BrotliTakeBits(br, n_bits, &val);
    return val;
  }
  else
  {
    uint32_t low_val;
    uint32_t high_val;
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, 16, &low_val);
    BrotliFillBitWindow(br, 8);
    BrotliTakeBits(br, n_bits - 16, &high_val);
    return low_val | (high_val << 16);
  }
}


/*** DEPENDENCIES:
inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}


----------------------------
inline static void BrotliFillBitWindow(BrotliBitReader * const br, uint32_t n_bits)
{
  if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 8))
  {
    if (br->bit_pos_ >= 56)
    {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  }
  else
    if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 16))
  {
    if (br->bit_pos_ >= 48)
    {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  }
  else
  {
    if (br->bit_pos_ >= 32)
    {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t) BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t)) >> 1;
      br->next_in += (sizeof(uint64_t)) >> 1;
    }
  }
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static uint32_t BrotliReadBits32(BrotliBitReader * const br, uint32_t n_bits)
{
  ;
  if (1 || (n_bits <= 16))
  {
    uint32_t val;
    BrotliFillBitWindow(br, n_bits);
    BrotliTakeBits(br, n_bits, &val);
    return val;
  }
  else
  {
    uint32_t low_val;
    uint32_t high_val;
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, 16, &low_val);
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, n_bits - 16, &high_val);
    return low_val | (high_val << 16);
  }
}


/*** DEPENDENCIES:
inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}


----------------------------
inline static void BrotliFillBitWindow(BrotliBitReader * const br, uint32_t n_bits)
{
  if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 8))
  {
    if (br->bit_pos_ >= 56)
    {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  }
  else
    if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 16))
  {
    if (br->bit_pos_ >= 48)
    {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  }
  else
  {
    if (br->bit_pos_ >= 32)
    {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t) BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t)) >> 1;
      br->next_in += (sizeof(uint64_t)) >> 1;
    }
  }
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static int BrotliJumpToByteBoundary(BrotliBitReader *br)
{
  uint32_t pad_bits_count = BrotliGetAvailableBits(br) & 0x7;
  uint32_t pad_bits = 0;
  if (pad_bits_count != 0)
  {
    BrotliTakeBits(br, pad_bits_count, &pad_bits);
  }
  return (!(!(pad_bits == 0))) ? (1) : (0);
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static uint32_t BrotliGetBits(BrotliBitReader * const br, uint32_t n_bits)
{
  BrotliFillBitWindow(br, n_bits);
  return ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
}


/*** DEPENDENCIES:
inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}


----------------------------
inline static uint32_t BitMask(uint32_t n)
{
  if ((!(!__builtin_constant_p(n))) || (!(!0)))
  {
    return ~(0xFFFFFFFFu << n);
  }
  else
  {
    return kBrotliBitMask[n];
  }
}


----------------------------
inline static void BrotliFillBitWindow(BrotliBitReader * const br, uint32_t n_bits)
{
  if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 8))
  {
    if (br->bit_pos_ >= 56)
    {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  }
  else
    if (((!(!(!0))) && (!(!__builtin_constant_p(n_bits)))) && (n_bits <= 16))
  {
    if (br->bit_pos_ >= 48)
    {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  }
  else
  {
    if (br->bit_pos_ >= 32)
    {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t) BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t)) >> 1;
      br->next_in += (sizeof(uint64_t)) >> 1;
    }
  }
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


inline static int BrotliSafeGetBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  while (BrotliGetAvailableBits(br) < n_bits)
  {
    if (!BrotliPullByte(br))
    {
      return 0;
    }
  }

  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  return 1;
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}


----------------------------
inline static int BrotliPullByte(BrotliBitReader * const br)
{
  if (br->avail_in == 0)
  {
    return 0;
  }
  br->val_ >>= 8;
  br->val_ |= ((uint64_t) (*br->next_in)) << 56;
  br->bit_pos_ -= 8;
  br->avail_in -= 1;
  br->next_in += 1;
  return 1;
}


----------------------------
inline static uint32_t BitMask(uint32_t n)
{
  if ((!(!__builtin_constant_p(n))) || (!(!0)))
  {
    return ~(0xFFFFFFFFu << n);
  }
  else
  {
    return kBrotliBitMask[n];
  }
}


----------------------------
***/


inline static void BrotliCopyBytes(uint8_t *dest, BrotliBitReader *br, size_t num)
{
  unsigned int dest_idx = 0;
  while ((BrotliGetAvailableBits(br) >= 8) && (num > 0))
  {
    dest[dest_idx] = (uint8_t) BrotliGetBitsUnmasked(br);
    BrotliDropBits(br, 8);
    dest_idx += 1;
    num -= 1;
  }

  memcpy(dest, br->next_in, num);
  br->avail_in -= num;
  br->next_in += num;
}


/*** DEPENDENCIES:
inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}


----------------------------
inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}


----------------------------
inline static void BrotliDropBits(BrotliBitReader * const br, uint32_t n_bits)
{
  br->bit_pos_ += n_bits;
}


----------------------------
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader
----------------------------
***/


