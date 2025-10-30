#include <platform.h>
#include <port.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <types.h>
#include <utf8_util.c>
#include <utf8_util.h>

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

static const double kMinUTF8Ratio = 0.75;
int BrotliIsMostlyUTF8(const uint8_t *data, const size_t pos, const size_t mask, const size_t length, const double min_fraction);
static size_t BrotliParseAsUTF8(int *symbol, const uint8_t *input, size_t size)
{
  if ((input[0] & 0x80) == 0)
  {
    *symbol = input[0];
    if ((*symbol) > 0)
    {
      return 1;
    }
  }
  if (((size > 1u) && ((input[0] & 0xE0) == 0xC0)) && ((input[1] & 0xC0) == 0x80))
  {
    *symbol = ((input[0] & 0x1F) << 6) | (input[1] & 0x3F);
    if ((*symbol) > 0x7F)
    {
      return 2;
    }
  }
  if ((((size > 2u) && ((input[0] & 0xF0) == 0xE0)) && ((input[1] & 0xC0) == 0x80)) && ((input[2] & 0xC0) == 0x80))
  {
    *symbol = (((input[0] & 0x0F) << 12) | ((input[1] & 0x3F) << 6)) | (input[2] & 0x3F);
    if ((*symbol) > 0x7FF)
    {
      return 3;
    }
  }
  if (((((size > 3u) && ((input[0] & 0xF8) == 0xF0)) && ((input[1] & 0xC0) == 0x80)) && ((input[2] & 0xC0) == 0x80)) && ((input[3] & 0xC0) == 0x80))
  {
    *symbol = ((((input[0] & 0x07) << 18) | ((input[1] & 0x3F) << 12)) | ((input[2] & 0x3F) << 6)) | (input[3] & 0x3F);
    if (((*symbol) > 0xFFFF) && ((*symbol) <= 0x10FFFF))
    {
      return 4;
    }
  }
  *symbol = 0x110000 | input[0];
  return 1;
}

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

static const double kMinUTF8Ratio = 0.75;
int BrotliIsMostlyUTF8(const uint8_t *data, const size_t pos, const size_t mask, const size_t length, const double min_fraction);
static size_t BrotliParseAsUTF8(int *symbol, const uint8_t *input, size_t size)
{
  if ((input[0] & 0x80) == 0)
  {
    *symbol = input[0];
    if ((*symbol) > 0)
    {
      return 1;
    }
  }
  if (((size > 1u) && ((input[0] & 0xE0) == 0xC0)) && ((input[1] & 0xC0) == 0x80))
  {
    *symbol = ((input[0] & 0x1F) << 6) | (input[1] & 0x3F);
    if ((*symbol) > 0x7F)
    {
      return 2;
    }
  }
  if ((((size > 2u) && ((input[0] & 0xF0) == 0xE0)) && ((input[1] & 0xC0) == 0x80)) && ((input[2] & 0xC0) == 0x80))
  {
    *symbol = (((input[0] & 0x0F) << 12) | ((input[1] & 0x3F) << 6)) | (input[2] & 0x3F);
    if ((*symbol) > 0x7FF)
    {
      return 3;
    }
  }
  if (((((size > 3u) && ((input[0] & 0xF8) == 0xF0)) && ((input[1] & 0xC0) == 0x80)) && ((input[2] & 0xC0) == 0x80)) && ((input[3] & 0xC0) == 0x80))
  {
    *symbol = ((((input[0] & 0x07) << 18) | ((input[1] & 0x3F) << 12)) | ((input[2] & 0x3F) << 6)) | (input[3] & 0x3F);
    if (((*symbol) > 0xFFFF) && ((*symbol) <= 0x10FFFF))
    {
      return 4;
    }
  }
  *symbol = 0x110000 | input[0];
  return 1;
}

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

