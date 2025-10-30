inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}


/*** DEPENDENCIES:
***/


inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


/*** DEPENDENCIES:
***/


inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


/*** DEPENDENCIES:
***/


inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}


/*** DEPENDENCIES:
***/


inline static void BrotliRBit(void)
{
}


/*** DEPENDENCIES:
***/


inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


// hint:  ['max_distance_ref is a mutable refrence to uint32_t', 'result_ref is a mutable refrence to BrotliDistanceCodeLimit']
BrotliDistanceCodeLimit helper_BrotliCalculateDistanceCodeLimit_1(uint32_t * const max_distance_ref, BrotliDistanceCodeLimit * const result_ref, uint32_t npostfix, uint32_t ndirect)
{
  uint32_t max_distance = *max_distance_ref;
  BrotliDistanceCodeLimit result = *result_ref;
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
  *max_distance_ref = max_distance;
  *result_ref = result;
}


/*** DEPENDENCIES:
typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit
----------------------------
***/


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
    helper_BrotliCalculateDistanceCodeLimit_1(&max_distance, &result, npostfix, ndirect);
  }
}


/*** DEPENDENCIES:
BrotliDistanceCodeLimit helper_BrotliCalculateDistanceCodeLimit_1(uint32_t * const max_distance_ref, BrotliDistanceCodeLimit * const result_ref, uint32_t npostfix, uint32_t ndirect)
{
  uint32_t max_distance = *max_distance_ref;
  BrotliDistanceCodeLimit result = *result_ref;
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
  *max_distance_ref = max_distance;
  *result_ref = result;
}


----------------------------
typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit
----------------------------
***/


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


/*** DEPENDENCIES:
inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}


----------------------------
inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
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
void BrotliDefaultFreeFunc(void *opaque, void *address)
{
  (void) opaque;
  free(address);
}


----------------------------
inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void *BrotliDefaultAllocFunc(void *opaque, size_t size)
{
  (void) opaque;
  return malloc(size);
}


----------------------------
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}


----------------------------
inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}


----------------------------
inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void BrotliRBit(void)
{
}


----------------------------
inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}


----------------------------
***/


