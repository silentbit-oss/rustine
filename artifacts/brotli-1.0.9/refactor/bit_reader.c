#include <bit_reader.c>
#include <bit_reader.h>
#include <constants.h>
#include <platform.h>
#include <port.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <types.h>

typedef void *(*brotli_alloc_func)(void *opaque, size_t size);
typedef void (*brotli_free_func)(void *opaque, void *address);
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}

inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}

inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}

inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}

inline static void BrotliRBit(void)
{
}

inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}

inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}

inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}

inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}

inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}

inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}

inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}

void *BrotliDefaultAllocFunc(void *opaque, size_t size);
void BrotliDefaultFreeFunc(void *opaque, void *address);
inline static void BrotliSuppressUnusedFunctions(void)
{
  (void) (&BrotliSuppressUnusedFunctions);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliRBit);
  (void) (&brotli_min_double);
  (void) (&brotli_max_double);
  (void) (&brotli_min_float);
  (void) (&brotli_max_float);
  (void) (&brotli_min_int);
  (void) (&brotli_max_int);
  (void) (&brotli_min_size_t);
  (void) (&brotli_max_size_t);
  (void) (&brotli_min_uint32_t);
  (void) (&brotli_max_uint32_t);
  (void) (&brotli_min_uint8_t);
  (void) (&brotli_max_uint8_t);
  (void) (&BrotliDefaultAllocFunc);
  (void) (&BrotliDefaultFreeFunc);
}

typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    uint32_t forbidden_distance = max_distance + 1;
    uint32_t offset = (forbidden_distance - ndirect) - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;
    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;
    offset = (offset >> npostfix) + 4;
    tmp = offset / 2;
    while (tmp != 0)
    {
      ndistbits += 1;
      tmp = tmp >> 1;
    }

    ndistbits -= 1;
    half = (offset >> ndistbits) & 1;
    group = ((ndistbits - 1) << 1) | half;
    if (group == 0)
    {
      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }
    group -= 1;
    ndistbits = (group >> 1) + 1;
    extra = (1u << ndistbits) - 1;
    start = (1u << (ndistbits + 1)) - 4;
    start += (group & 1) << ndistbits;
    result.max_alphabet_size = ((((group << npostfix) | postfix) + ndirect) + 16) + 1;
    result.max_distance = ((((start + extra) << npostfix) + postfix) + ndirect) + 1;
    return result;
  }
}

typedef struct 
{
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26];
extern const uint32_t kBrotliBitMask[33];
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

typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader;
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReaderState;
void BrotliInitBitReader(BrotliBitReader * const br);
int BrotliWarmupBitReader(BrotliBitReader * const br);
int BrotliSafeReadBits32Slow(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val);
inline static void BrotliBitReaderSaveState(BrotliBitReader * const from, BrotliBitReaderState *to)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

inline static void BrotliBitReaderRestoreState(BrotliBitReader * const to, BrotliBitReaderState *from)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}

inline static size_t BrotliGetRemainingBytes(BrotliBitReader *br)
{
  static const size_t kCap = ((size_t) 1) << 30;
  if (br->avail_in > kCap)
  {
    return kCap;
  }
  return br->avail_in + (BrotliGetAvailableBits(br) >> 3);
}

inline static int BrotliCheckInputAmount(BrotliBitReader * const br, size_t num)
{
  return (!(!(br->avail_in >= num))) ? (1) : (0);
}

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

inline static void BrotliFillBitWindow16(BrotliBitReader * const br)
{
  BrotliFillBitWindow(br, 17);
}

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

inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}

inline static uint32_t BrotliGet16BitsUnmasked(BrotliBitReader * const br)
{
  BrotliFillBitWindow(br, 16);
  return (uint32_t) BrotliGetBitsUnmasked(br);
}

inline static uint32_t BrotliGetBits(BrotliBitReader * const br, uint32_t n_bits)
{
  BrotliFillBitWindow(br, n_bits);
  return ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
}

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

inline static void BrotliDropBits(BrotliBitReader * const br, uint32_t n_bits)
{
  br->bit_pos_ += n_bits;
}

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

inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}

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

const uint32_t kBrotliBitMask[33] = {0x00000000, 0x00000001, 0x00000003, 0x00000007, 0x0000000F, 0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF, 0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF, 0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF, 0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF, 0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF, 0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF, 0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF};
void BrotliInitBitReader(BrotliBitReader * const br)
{
  br->val_ = 0;
  br->bit_pos_ = (sizeof(br->val_)) << 3;
}

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


typedef void *(*brotli_alloc_func)(void *opaque, size_t size);
typedef void (*brotli_free_func)(void *opaque, void *address);
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}

inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}

inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}

inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}

inline static void BrotliRBit(void)
{
}

inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}

inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}

inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}

inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}

inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}

inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}

inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}

void *BrotliDefaultAllocFunc(void *opaque, size_t size);
void BrotliDefaultFreeFunc(void *opaque, void *address);
inline static void BrotliSuppressUnusedFunctions(void)
{
  (void) (&BrotliSuppressUnusedFunctions);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliRBit);
  (void) (&brotli_min_double);
  (void) (&brotli_max_double);
  (void) (&brotli_min_float);
  (void) (&brotli_max_float);
  (void) (&brotli_min_int);
  (void) (&brotli_max_int);
  (void) (&brotli_min_size_t);
  (void) (&brotli_max_size_t);
  (void) (&brotli_min_uint32_t);
  (void) (&brotli_max_uint32_t);
  (void) (&brotli_min_uint8_t);
  (void) (&brotli_max_uint8_t);
  (void) (&BrotliDefaultAllocFunc);
  (void) (&BrotliDefaultFreeFunc);
}

typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    uint32_t forbidden_distance = max_distance + 1;
    uint32_t offset = (forbidden_distance - ndirect) - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;
    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;
    offset = (offset >> npostfix) + 4;
    tmp = offset / 2;
    while (tmp != 0)
    {
      ndistbits += 1;
      tmp = tmp >> 1;
    }

    ndistbits -= 1;
    half = (offset >> ndistbits) & 1;
    group = ((ndistbits - 1) << 1) | half;
    if (group == 0)
    {
      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }
    group -= 1;
    ndistbits = (group >> 1) + 1;
    extra = (1u << ndistbits) - 1;
    start = (1u << (ndistbits + 1)) - 4;
    start += (group & 1) << ndistbits;
    result.max_alphabet_size = ((((group << npostfix) | postfix) + ndirect) + 16) + 1;
    result.max_distance = ((((start + extra) << npostfix) + postfix) + ndirect) + 1;
    return result;
  }
}

typedef struct 
{
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26];
extern const uint32_t kBrotliBitMask[33];
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

typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReader;
typedef struct 
{
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t *next_in;
  size_t avail_in;
} BrotliBitReaderState;
void BrotliInitBitReader(BrotliBitReader * const br);
int BrotliWarmupBitReader(BrotliBitReader * const br);
int BrotliSafeReadBits32Slow(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val);
inline static void BrotliBitReaderSaveState(BrotliBitReader * const from, BrotliBitReaderState *to)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

inline static void BrotliBitReaderRestoreState(BrotliBitReader * const to, BrotliBitReaderState *from)
{
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

inline static uint32_t BrotliGetAvailableBits(const BrotliBitReader *br)
{
  return ((1) ? (64) : (32)) - br->bit_pos_;
}

inline static size_t BrotliGetRemainingBytes(BrotliBitReader *br)
{
  static const size_t kCap = ((size_t) 1) << 30;
  if (br->avail_in > kCap)
  {
    return kCap;
  }
  return br->avail_in + (BrotliGetAvailableBits(br) >> 3);
}

inline static int BrotliCheckInputAmount(BrotliBitReader * const br, size_t num)
{
  return (!(!(br->avail_in >= num))) ? (1) : (0);
}

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

inline static void BrotliFillBitWindow16(BrotliBitReader * const br)
{
  BrotliFillBitWindow(br, 17);
}

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

inline static uint64_t BrotliGetBitsUnmasked(BrotliBitReader * const br)
{
  return br->val_ >> br->bit_pos_;
}

inline static uint32_t BrotliGet16BitsUnmasked(BrotliBitReader * const br)
{
  BrotliFillBitWindow(br, 16);
  return (uint32_t) BrotliGetBitsUnmasked(br);
}

inline static uint32_t BrotliGetBits(BrotliBitReader * const br, uint32_t n_bits)
{
  BrotliFillBitWindow(br, n_bits);
  return ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
}

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

inline static void BrotliDropBits(BrotliBitReader * const br, uint32_t n_bits)
{
  br->bit_pos_ += n_bits;
}

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

inline static void BrotliTakeBits(BrotliBitReader * const br, uint32_t n_bits, uint32_t *val)
{
  *val = ((uint32_t) BrotliGetBitsUnmasked(br)) & BitMask(n_bits);
  ;
  BrotliDropBits(br, n_bits);
}

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

const uint32_t kBrotliBitMask[33] = {0x00000000, 0x00000001, 0x00000003, 0x00000007, 0x0000000F, 0x0000001F, 0x0000003F, 0x0000007F, 0x000000FF, 0x000001FF, 0x000003FF, 0x000007FF, 0x00000FFF, 0x00001FFF, 0x00003FFF, 0x00007FFF, 0x0000FFFF, 0x0001FFFF, 0x0003FFFF, 0x0007FFFF, 0x000FFFFF, 0x001FFFFF, 0x003FFFFF, 0x007FFFFF, 0x00FFFFFF, 0x01FFFFFF, 0x03FFFFFF, 0x07FFFFFF, 0x0FFFFFFF, 0x1FFFFFFF, 0x3FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFF};
void BrotliInitBitReader(BrotliBitReader * const br)
{
  br->val_ = 0;
  br->bit_pos_ = (sizeof(br->val_)) << 3;
}

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

