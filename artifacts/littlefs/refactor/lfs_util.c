#include <assert.h>
#include <inttypes.h>
#include <lfs_util.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline static uint32_t lfs_max(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t lfs_min(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t lfs_aligndown(uint32_t a, uint32_t alignment)
{
  return a - (a % alignment);
}

inline static uint32_t lfs_alignup(uint32_t a, uint32_t alignment)
{
  return lfs_aligndown((a + alignment) - 1, alignment);
}

inline static uint32_t lfs_npw2(uint32_t a)
{
  return 32 - __builtin_clz(a - 1);
}

inline static uint32_t lfs_ctz(uint32_t a)
{
  return __builtin_ctz(a);
}

inline static uint32_t lfs_popc(uint32_t a)
{
  return __builtin_popcount(a);
}

inline static int lfs_scmp(uint32_t a, uint32_t b)
{
  return (int) ((unsigned) (a - b));
}

inline static uint32_t lfs_fromle32(uint32_t a)
{
  return a;
}

inline static uint32_t lfs_tole32(uint32_t a)
{
  return lfs_fromle32(a);
}

inline static uint32_t lfs_frombe32(uint32_t a)
{
  return __builtin_bswap32(a);
}

inline static uint32_t lfs_tobe32(uint32_t a)
{
  return lfs_frombe32(a);
}

uint32_t lfs_crc(uint32_t crc, const void *buffer, size_t size);
inline static void *lfs_malloc(size_t size)
{
  return malloc(size);
}

inline static void lfs_free(void *p)
{
  free(p);
}

uint32_t lfs_crc(uint32_t crc, const void *buffer, size_t size)
{
  static const uint32_t rtable[16] = {0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c, 0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c};
  const uint8_t *data = buffer;
  for (size_t i = 0; i < size; i += 1)
  {
    crc = (crc >> 4) ^ rtable[(crc ^ (data[i] >> 0)) & 0xf];
    crc = (crc >> 4) ^ rtable[(crc ^ (data[i] >> 4)) & 0xf];
  }

  return crc;
}

