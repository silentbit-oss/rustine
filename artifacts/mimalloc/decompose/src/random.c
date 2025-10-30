inline static uint32_t rotl(uint32_t x, uint32_t shift)
{
  return (x << shift) | (x >> (32 - shift));
}


/*** DEPENDENCIES:
***/


inline static uint32_t read32(const uint8_t *p, size_t idx32)
{
  const size_t i = 4 * idx32;
  return ((((uint32_t) p[i + 0]) | (((uint32_t) p[i + 1]) << 8)) | (((uint32_t) p[i + 2]) << 16)) | (((uint32_t) p[i + 3]) << 24);
}


/*** DEPENDENCIES:
***/


static bool mi_random_is_initialized(mi_random_ctx_t *ctx)
{
  return (ctx != 0) && (ctx->input[0] != 0);
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
***/


inline static void qround(uint32_t x[16], size_t a, size_t b, size_t c, size_t d)
{
  x[a] += x[b];
  x[d] = rotl(x[d] ^ x[a], 16);
  x[c] += x[d];
  x[b] = rotl(x[b] ^ x[c], 12);
  x[a] += x[b];
  x[d] = rotl(x[d] ^ x[a], 8);
  x[c] += x[d];
  x[b] = rotl(x[b] ^ x[c], 7);
}


/*** DEPENDENCIES:
inline static uint32_t rotl(uint32_t x, uint32_t shift)
{
  return (x << shift) | (x >> (32 - shift));
}


----------------------------
***/


static void chacha_block(mi_random_ctx_t *ctx)
{
  uint32_t x[16];
  for (size_t i = 0; i < 16; i += 1)
  {
    x[i] = ctx->input[i];
  }

  for (size_t i = 0; i < 20; i += 2)
  {
    qround(x, 0, 4, 8, 12);
    qround(x, 1, 5, 9, 13);
    qround(x, 2, 6, 10, 14);
    qround(x, 3, 7, 11, 15);
    qround(x, 0, 5, 10, 15);
    qround(x, 1, 6, 11, 12);
    qround(x, 2, 7, 8, 13);
    qround(x, 3, 4, 9, 14);
  }

  for (size_t i = 0; i < 16; i += 1)
  {
    ctx->output[i] = x[i] + ctx->input[i];
  }

  ctx->output_available = 16;
  ctx->input[12] += 1;
  if (ctx->input[12] == 0)
  {
    ctx->input[13] += 1;
    if (ctx->input[13] == 0)
    {
      ctx->input[14] += 1;
    }
  }
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
inline static void qround(uint32_t x[16], size_t a, size_t b, size_t c, size_t d)
{
  x[a] += x[b];
  x[d] = rotl(x[d] ^ x[a], 16);
  x[c] += x[d];
  x[b] = rotl(x[b] ^ x[c], 12);
  x[a] += x[b];
  x[d] = rotl(x[d] ^ x[a], 8);
  x[c] += x[d];
  x[b] = rotl(x[b] ^ x[c], 7);
}


----------------------------
***/


static uint32_t chacha_next32(mi_random_ctx_t *ctx)
{
  if (ctx->output_available <= 0)
  {
    chacha_block(ctx);
    ctx->output_available = 16;
  }
  const uint32_t x = ctx->output[16 - ctx->output_available];
  ctx->output[16 - ctx->output_available] = 0;
  ctx->output_available -= 1;
  return x;
}


/*** DEPENDENCIES:
static void chacha_block(mi_random_ctx_t *ctx)
{
  uint32_t x[16];
  for (size_t i = 0; i < 16; i += 1)
  {
    x[i] = ctx->input[i];
  }

  for (size_t i = 0; i < 20; i += 2)
  {
    qround(x, 0, 4, 8, 12);
    qround(x, 1, 5, 9, 13);
    qround(x, 2, 6, 10, 14);
    qround(x, 3, 7, 11, 15);
    qround(x, 0, 5, 10, 15);
    qround(x, 1, 6, 11, 12);
    qround(x, 2, 7, 8, 13);
    qround(x, 3, 4, 9, 14);
  }

  for (size_t i = 0; i < 16; i += 1)
  {
    ctx->output[i] = x[i] + ctx->input[i];
  }

  ctx->output_available = 16;
  ctx->input[12] += 1;
  if (ctx->input[12] == 0)
  {
    ctx->input[13] += 1;
    if (ctx->input[13] == 0)
    {
      ctx->input[14] += 1;
    }
  }
}


----------------------------
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
***/


uintptr_t _mi_random_next(mi_random_ctx_t *ctx)
{
  (mi_random_is_initialized(ctx)) ? ((void) 0) : (_mi_assert_fail("mi_random_is_initialized(ctx)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 145, __func__));
  uintptr_t r;
  do
  {
    r = (((uintptr_t) chacha_next32(ctx)) << 32) | chacha_next32(ctx);
  }
  while (r == 0);
  return r;
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
static uint32_t chacha_next32(mi_random_ctx_t *ctx)
{
  if (ctx->output_available <= 0)
  {
    chacha_block(ctx);
    ctx->output_available = 16;
  }
  const uint32_t x = ctx->output[16 - ctx->output_available];
  ctx->output[16 - ctx->output_available] = 0;
  ctx->output_available -= 1;
  return x;
}


----------------------------
static bool mi_random_is_initialized(mi_random_ctx_t *ctx)
{
  return (ctx != 0) && (ctx->input[0] != 0);
}


----------------------------
None
----------------------------
***/


static void chacha_split(mi_random_ctx_t *ctx, uint64_t nonce, mi_random_ctx_t *ctx_new)
{
  memset(ctx_new, 0, sizeof(*ctx_new));
  _mi_memcpy(ctx_new->input, ctx->input, sizeof(ctx_new->input));
  ctx_new->input[12] = 0;
  ctx_new->input[13] = 0;
  ctx_new->input[14] = (uint32_t) nonce;
  ctx_new->input[15] = (uint32_t) (nonce >> 32);
  ((ctx->input[14] != ctx_new->input[14]) || (ctx->input[15] != ctx_new->input[15])) ? ((void) 0) : (_mi_assert_fail("ctx->input[14] != ctx_new->input[14] || ctx->input[15] != ctx_new->input[15]", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 123, __func__));
  chacha_block(ctx_new);
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
static void chacha_block(mi_random_ctx_t *ctx)
{
  uint32_t x[16];
  for (size_t i = 0; i < 16; i += 1)
  {
    x[i] = ctx->input[i];
  }

  for (size_t i = 0; i < 20; i += 2)
  {
    qround(x, 0, 4, 8, 12);
    qround(x, 1, 5, 9, 13);
    qround(x, 2, 6, 10, 14);
    qround(x, 3, 7, 11, 15);
    qround(x, 0, 5, 10, 15);
    qround(x, 1, 6, 11, 12);
    qround(x, 2, 7, 8, 13);
    qround(x, 3, 4, 9, 14);
  }

  for (size_t i = 0; i < 16; i += 1)
  {
    ctx->output[i] = x[i] + ctx->input[i];
  }

  ctx->output_available = 16;
  ctx->input[12] += 1;
  if (ctx->input[12] == 0)
  {
    ctx->input[13] += 1;
    if (ctx->input[13] == 0)
    {
      ctx->input[14] += 1;
    }
  }
}


----------------------------
None
----------------------------
***/


void _mi_random_split(mi_random_ctx_t *ctx, mi_random_ctx_t *ctx_new)
{
  (mi_random_is_initialized(ctx)) ? ((void) 0) : (_mi_assert_fail("mi_random_is_initialized(ctx)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 139, __func__));
  (ctx != ctx_new) ? ((void) 0) : (_mi_assert_fail("ctx != ctx_new", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 140, __func__));
  chacha_split(ctx, (uintptr_t) ctx_new, ctx_new);
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
static bool mi_random_is_initialized(mi_random_ctx_t *ctx)
{
  return (ctx != 0) && (ctx->input[0] != 0);
}


----------------------------
static void chacha_split(mi_random_ctx_t *ctx, uint64_t nonce, mi_random_ctx_t *ctx_new)
{
  memset(ctx_new, 0, sizeof(*ctx_new));
  _mi_memcpy(ctx_new->input, ctx->input, sizeof(ctx_new->input));
  ctx_new->input[12] = 0;
  ctx_new->input[13] = 0;
  ctx_new->input[14] = (uint32_t) nonce;
  ctx_new->input[15] = (uint32_t) (nonce >> 32);
  ((ctx->input[14] != ctx_new->input[14]) || (ctx->input[15] != ctx_new->input[15])) ? ((void) 0) : (_mi_assert_fail("ctx->input[14] != ctx_new->input[14] || ctx->input[15] != ctx_new->input[15]", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 123, __func__));
  chacha_block(ctx_new);
}


----------------------------
None
----------------------------
***/


uintptr_t _mi_os_random_weak(uintptr_t extra_seed)
{
  uintptr_t x = ((uintptr_t) (&_mi_os_random_weak)) ^ extra_seed;
  x ^= _mi_prim_clock_now();
  uintptr_t max = ((x ^ (x >> 17)) & 0x0F) + 1;
  for (uintptr_t i = 0; (i < max) || (x == 0); i += 1, x += 1)
  {
    x = _mi_random_shuffle(x);
  }

  (x != 0) ? ((void) 0) : (_mi_assert_fail("x != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 173, __func__));
  return x;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_random_shuffle(uintptr_t x)
{
  if (x == 0)
  {
    x = 17;
  }
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
  return x;
}


----------------------------
mi_msecs_t _mi_prim_clock_now(void)
{
  return (mi_msecs_t) clock();
}


----------------------------
None
----------------------------
***/


static void chacha_init(mi_random_ctx_t *ctx, const uint8_t key[32], uint64_t nonce)
{
  memset(ctx, 0, sizeof(*ctx));
  for (size_t i = 0; i < 4; i += 1)
  {
    const uint8_t *sigma = (uint8_t *) "expand 32-byte k";
    ctx->input[i] = read32(sigma, i);
  }

  for (size_t i = 0; i < 8; i += 1)
  {
    ctx->input[i + 4] = read32(key, i);
  }

  ctx->input[12] = 0;
  ctx->input[13] = 0;
  ctx->input[14] = (uint32_t) nonce;
  ctx->input[15] = (uint32_t) (nonce >> 32);
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
inline static uint32_t read32(const uint8_t *p, size_t idx32)
{
  const size_t i = 4 * idx32;
  return ((((uint32_t) p[i + 0]) | (((uint32_t) p[i + 1]) << 8)) | (((uint32_t) p[i + 2]) << 16)) | (((uint32_t) p[i + 3]) << 24);
}


----------------------------
***/


static void mi_random_init_ex(mi_random_ctx_t *ctx, bool use_weak)
{
  uint8_t key[32];
  if (use_weak || (!_mi_prim_random_buf(key, sizeof(key))))
  {
    if (!use_weak)
    {
      _mi_warning_message("unable to use secure randomness\n");
    }
    uintptr_t x = _mi_os_random_weak(0);
    for (size_t i = 0; i < 8; i += 1, x += 1)
    {
      x = _mi_random_shuffle(x);
      ((uint32_t *) key)[i] = (uint32_t) x;
    }

    ctx->weak = 1;
  }
  else
  {
    ctx->weak = 0;
  }
  chacha_init(ctx, key, (uintptr_t) ctx);
}


/*** DEPENDENCIES:
bool _mi_prim_random_buf(void *buf, size_t buf_len)
{
  int flags = O_RDONLY;
  int fd = mi_prim_open("/dev/urandom", flags);
  if (fd < 0)
  {
    return 0;
  }
  size_t count = 0;
  while (count < buf_len)
  {
    ssize_t ret = mi_prim_read(fd, ((char *) buf) + count, buf_len - count);
    if (ret <= 0)
    {
      if ((errno != 11) && (errno != EINTR))
      {
        break;
      }
    }
    else
    {
      count += ret;
    }
  }

  mi_prim_close(fd);
  return count == buf_len;
}


----------------------------
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
inline static uintptr_t _mi_random_shuffle(uintptr_t x)
{
  if (x == 0)
  {
    x = 17;
  }
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
  return x;
}


----------------------------
static void chacha_init(mi_random_ctx_t *ctx, const uint8_t key[32], uint64_t nonce)
{
  memset(ctx, 0, sizeof(*ctx));
  for (size_t i = 0; i < 4; i += 1)
  {
    const uint8_t *sigma = (uint8_t *) "expand 32-byte k";
    ctx->input[i] = read32(sigma, i);
  }

  for (size_t i = 0; i < 8; i += 1)
  {
    ctx->input[i + 4] = read32(key, i);
  }

  ctx->input[12] = 0;
  ctx->input[13] = 0;
  ctx->input[14] = (uint32_t) nonce;
  ctx->input[15] = (uint32_t) (nonce >> 32);
}


----------------------------
uintptr_t _mi_os_random_weak(uintptr_t extra_seed)
{
  uintptr_t x = ((uintptr_t) (&_mi_os_random_weak)) ^ extra_seed;
  x ^= _mi_prim_clock_now();
  uintptr_t max = ((x ^ (x >> 17)) & 0x0F) + 1;
  for (uintptr_t i = 0; (i < max) || (x == 0); i += 1, x += 1)
  {
    x = _mi_random_shuffle(x);
  }

  (x != 0) ? ((void) 0) : (_mi_assert_fail("x != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 173, __func__));
  return x;
}


----------------------------
None
----------------------------
***/


void _mi_random_init(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 0);
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
static void mi_random_init_ex(mi_random_ctx_t *ctx, bool use_weak)
{
  uint8_t key[32];
  if (use_weak || (!_mi_prim_random_buf(key, sizeof(key))))
  {
    if (!use_weak)
    {
      _mi_warning_message("unable to use secure randomness\n");
    }
    uintptr_t x = _mi_os_random_weak(0);
    for (size_t i = 0; i < 8; i += 1, x += 1)
    {
      x = _mi_random_shuffle(x);
      ((uint32_t *) key)[i] = (uint32_t) x;
    }

    ctx->weak = 1;
  }
  else
  {
    ctx->weak = 0;
  }
  chacha_init(ctx, key, (uintptr_t) ctx);
}


----------------------------
***/


void _mi_random_reinit_if_weak(mi_random_ctx_t *ctx)
{
  if (ctx->weak)
  {
    _mi_random_init(ctx);
  }
}


/*** DEPENDENCIES:
void _mi_random_init(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 0);
}


----------------------------
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
***/


void _mi_random_init_weak(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 1);
}


/*** DEPENDENCIES:
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
static void mi_random_init_ex(mi_random_ctx_t *ctx, bool use_weak)
{
  uint8_t key[32];
  if (use_weak || (!_mi_prim_random_buf(key, sizeof(key))))
  {
    if (!use_weak)
    {
      _mi_warning_message("unable to use secure randomness\n");
    }
    uintptr_t x = _mi_os_random_weak(0);
    for (size_t i = 0; i < 8; i += 1, x += 1)
    {
      x = _mi_random_shuffle(x);
      ((uint32_t *) key)[i] = (uint32_t) x;
    }

    ctx->weak = 1;
  }
  else
  {
    ctx->weak = 0;
  }
  chacha_init(ctx, key, (uintptr_t) ctx);
}


----------------------------
***/


