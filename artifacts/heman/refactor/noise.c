#include <errno.h>
#include <math.h>
#include <noise.c>
#include <noise.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct osn_context;
int open_simplex_noise(int64_t seed, struct osn_context **ctx);
void open_simplex_noise_free(struct osn_context *ctx);
int open_simplex_noise_init_perm(struct osn_context *ctx, int16_t p[], int nelements);
double open_simplex_noise2(struct osn_context *ctx, double x, double y);
double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z);
double open_simplex_noise4(struct osn_context *ctx, double x, double y, double z, double w);
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
};
static const int8_t gradients2D[] = {5, 2, 2, 5, -5, 2, -2, 5, 5, -2, 2, -5, -5, -2, -2, -5};
static const signed char gradients3D[] = {-11, 4, 4, -4, 11, 4, -4, 4, 11, 11, 4, 4, 4, 11, 4, 4, 4, 11, -11, -4, 4, -4, -11, 4, -4, -4, 11, 11, -4, 4, 4, -11, 4, 4, -4, 11, -11, 4, -4, -4, 11, -4, -4, 4, -11, 11, 4, -4, 4, 11, -4, 4, 4, -11, -11, -4, -4, -4, -11, -4, -4, -4, -11, 11, -4, -4, 4, -11, -4, 4, -4, -11};
static const signed char gradients4D[] = {3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3};
static double extrapolate2(struct osn_context *ctx, int xsb, int ysb, double dx, double dy)
{
  int16_t *perm = ctx->perm;
  int index = perm[(perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E;
  return (gradients2D[index] * dx) + (gradients2D[index + 1] * dy);
}

static double extrapolate3(struct osn_context *ctx, int xsb, int ysb, int zsb, double dx, double dy, double dz)
{
  int16_t *perm = ctx->perm;
  int16_t *permGradIndex3D = ctx->permGradIndex3D;
  int index = permGradIndex3D[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF];
  return ((gradients3D[index] * dx) + (gradients3D[index + 1] * dy)) + (gradients3D[index + 2] * dz);
}

static double extrapolate4(struct osn_context *ctx, int xsb, int ysb, int zsb, int wsb, double dx, double dy, double dz, double dw)
{
  int16_t *perm = ctx->perm;
  int index = perm[(perm[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF] + wsb) & 0xFF] & 0xFC;
  return (((gradients4D[index] * dx) + (gradients4D[index + 1] * dy)) + (gradients4D[index + 2] * dz)) + (gradients4D[index + 3] * dw);
}

inline static int fastFloor(double x)
{
  int xi = (int) x;
  return (x < xi) ? (xi - 1) : (xi);
}

static int allocate_perm(struct osn_context *ctx, int nperm, int ngrad)
{
  if (ctx->perm)
  {
    free(ctx->perm);
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
  }
  ctx->perm = malloc((sizeof(*ctx->perm)) * nperm);
  if (!ctx->perm)
  {
    return -ENOMEM;
  }
  ctx->permGradIndex3D = malloc((sizeof(*ctx->permGradIndex3D)) * ngrad);
  if (!ctx->permGradIndex3D)
  {
    free(ctx->perm);
    return -ENOMEM;
  }
  return 0;
}

int open_simplex_noise_init_perm(struct osn_context *ctx, int16_t p[], int nelements)
{
  int i;
  int rc;
  rc = allocate_perm(ctx, nelements, 256);
  if (rc)
  {
    return rc;
  }
  memcpy(ctx->perm, p, (sizeof(*ctx->perm)) * nelements);
  for (i = 0; i < 256; i += 1)
  {
    ctx->permGradIndex3D[i] = (int16_t) ((ctx->perm[i] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
  }

  return 0;
}

int open_simplex_noise(int64_t seed, struct osn_context **ctx)
{
  int rc;
  int16_t source[256];
  int i;
  int16_t *perm;
  unsigned int perm_idx = 0;
  int16_t *permGradIndex3D;
  unsigned int permGradIndex3D_idx = 0;
  *ctx = malloc(sizeof(*(*ctx)));
  if (!(*ctx))
  {
    return -ENOMEM;
  }
  (*ctx)->perm = 0;
  (*ctx)->permGradIndex3D = 0;
  rc = allocate_perm(*ctx, 256, 256);
  if (rc)
  {
    free(*ctx);
    return rc;
  }
  perm_idx = (*ctx)->perm_idx;
  permGradIndex3D_idx = (*ctx)->permGradIndex3D_idx;
  for (i = 0; i < 256; i += 1)
  {
    source[i] = (int16_t) i;
  }

  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  for (i = 255; i >= 0; i -= 1)
  {
    seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
    int r = (int) ((seed + 31) % (i + 1));
    if (r < 0)
    {
      r += i + 1;
    }
    perm[i + perm_idx] = source[r];
    permGradIndex3D[i + permGradIndex3D_idx] = (short) ((perm[i + perm_idx] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
    source[r] = source[i];
  }

  return 0;
}

void open_simplex_noise_free(struct osn_context *ctx)
{
  if (!ctx)
  {
    return;
  }
  if (ctx->perm)
  {
    free(ctx->perm);
    ctx->perm = 0;
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
    ctx->permGradIndex3D = 0;
  }
  free(ctx);
}

double open_simplex_noise2(struct osn_context *ctx, double x, double y)
{
  double stretchOffset = (x + y) * (-0.211324865405187);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  double squishOffset = (xsb + ysb) * 0.366025403784439;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double inSum = xins + yins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dx_ext;
  double dy_ext;
  int xsv_ext;
  int ysv_ext;
  double value = 0;
  double dx1 = (dx0 - 1) - 0.366025403784439;
  double dy1 = (dy0 - 0) - 0.366025403784439;
  double attn1 = (2 - (dx1 * dx1)) - (dy1 * dy1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
  }
  double dx2 = (dx0 - 0) - 0.366025403784439;
  double dy2 = (dy0 - 1) - 0.366025403784439;
  double attn2 = (2 - (dx2 * dx2)) - (dy2 * dy2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
  }
  if (inSum <= 1)
  {
    helper_open_simplex_noise2_1(&dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xsb, ysb, xins, yins, inSum, dx0, dy0);
  }
  else
  {
    helper_open_simplex_noise2_2(&xsb, &ysb, &dx0, &dy0, &dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xins, yins, inSum);
  }
  double attn0 = (2 - (dx0 * dx0)) - (dy0 * dy0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate2(ctx, xsb, ysb, dx0, dy0);
  }
  double attn_ext = (2 - (dx_ext * dx_ext)) - (dy_ext * dy_ext);
  if (attn_ext > 0)
  {
    attn_ext *= attn_ext;
    value += (attn_ext * attn_ext) * extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
  }
  return value / 47.0;
}

double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z)
{
  double stretchOffset = ((x + y) + z) * ((-1.0) / 6.0);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  double zs = z + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  int zsb = fastFloor(zs);
  double squishOffset = ((xsb + ysb) + zsb) * (1.0 / 3.0);
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double zb = zsb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double zins = zs - zsb;
  double inSum = (xins + yins) + zins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dz0 = z - zb;
  double dx_ext0;
  double dy_ext0;
  double dz_ext0;
  double dx_ext1;
  double dy_ext1;
  double dz_ext1;
  int xsv_ext0;
  int ysv_ext0;
  int zsv_ext0;
  int xsv_ext1;
  int ysv_ext1;
  int zsv_ext1;
  double value = 0;
  if (inSum <= 1)
  {
    helper_open_simplex_noise3_1(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &value, ctx, xsb, ysb, zsb, xins, yins, zins, inSum, dx0, dy0, dz0);
  }
  else
    if (inSum >= 2)
  {
    helper_open_simplex_noise3_2(&dx0, &dy0, &dz0, &dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &value, ctx, xsb, ysb, zsb, xins, yins, zins, inSum);
  }
  else
  {
    helper_open_simplex_noise3_3(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &value, ctx, xsb, ysb, zsb, xins, yins, zins, dx0, dy0, dz0);
  }
  double attn_ext0 = ((2 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0);
  if (attn_ext0 > 0)
  {
    attn_ext0 *= attn_ext0;
    value += (attn_ext0 * attn_ext0) * extrapolate3(ctx, xsv_ext0, ysv_ext0, zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
  }
  double attn_ext1 = ((2 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1);
  if (attn_ext1 > 0)
  {
    attn_ext1 *= attn_ext1;
    value += (attn_ext1 * attn_ext1) * extrapolate3(ctx, xsv_ext1, ysv_ext1, zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
  }
  return value / 103.0;
}

double open_simplex_noise4(struct osn_context *ctx, double x, double y, double z, double w)
{
  double stretchOffset = (((x + y) + z) + w) * (-0.138196601125011);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  double zs = z + stretchOffset;
  double ws = w + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  int zsb = fastFloor(zs);
  int wsb = fastFloor(ws);
  double squishOffset = (((xsb + ysb) + zsb) + wsb) * 0.309016994374947;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double zb = zsb + squishOffset;
  double wb = wsb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double zins = zs - zsb;
  double wins = ws - wsb;
  double inSum = ((xins + yins) + zins) + wins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dz0 = z - zb;
  double dw0 = w - wb;
  double dx_ext0;
  double dy_ext0;
  double dz_ext0;
  double dw_ext0;
  double dx_ext1;
  double dy_ext1;
  double dz_ext1;
  double dw_ext1;
  double dx_ext2;
  double dy_ext2;
  double dz_ext2;
  double dw_ext2;
  int xsv_ext0;
  int ysv_ext0;
  int zsv_ext0;
  int wsv_ext0;
  int xsv_ext1;
  int ysv_ext1;
  int zsv_ext1;
  int wsv_ext1;
  int xsv_ext2;
  int ysv_ext2;
  int zsv_ext2;
  int wsv_ext2;
  double value = 0;
  if (inSum <= 1)
  {
    helper_open_simplex_noise4_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &ysv_ext2, &zsv_ext2, &wsv_ext2, &value, ctx, xsb, ysb, zsb, wsb, xins, yins, zins, wins, inSum, dx0, dy0, dz0, dw0, wsv_ext1, xsv_ext2);
  }
  else
    if (inSum >= 3)
  {
    helper_open_simplex_noise4_2(&dx0, &dy0, &dz0, &dw0, &dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &ysv_ext2, &zsv_ext2, &wsv_ext2, &value, ctx, xsb, ysb, zsb, wsb, xins, yins, zins, wins, inSum, wsv_ext1, xsv_ext2);
  }
  else
    if (inSum <= 2)
  {
    helper_open_simplex_noise4_4(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, &value, ctx, xsb, ysb, zsb, wsb, xins, yins, zins, wins, inSum, dx0, dy0, dz0, dw0);
  }
  else
  {
    helper_open_simplex_noise4_3(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, &value, ctx, xsb, ysb, zsb, wsb, xins, yins, zins, wins, inSum, dx0, dy0, dz0, dw0);
  }
  double attn_ext0 = (((2 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0)) - (dw_ext0 * dw_ext0);
  if (attn_ext0 > 0)
  {
    attn_ext0 *= attn_ext0;
    value += (attn_ext0 * attn_ext0) * extrapolate4(ctx, xsv_ext0, ysv_ext0, zsv_ext0, wsv_ext0, dx_ext0, dy_ext0, dz_ext0, dw_ext0);
  }
  double attn_ext1 = (((2 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1)) - (dw_ext1 * dw_ext1);
  if (attn_ext1 > 0)
  {
    attn_ext1 *= attn_ext1;
    value += (attn_ext1 * attn_ext1) * extrapolate4(ctx, xsv_ext1, ysv_ext1, zsv_ext1, wsv_ext1, dx_ext1, dy_ext1, dz_ext1, dw_ext1);
  }
  double attn_ext2 = (((2 - (dx_ext2 * dx_ext2)) - (dy_ext2 * dy_ext2)) - (dz_ext2 * dz_ext2)) - (dw_ext2 * dw_ext2);
  if (attn_ext2 > 0)
  {
    attn_ext2 *= attn_ext2;
    value += (attn_ext2 * attn_ext2) * extrapolate4(ctx, xsv_ext2, ysv_ext2, zsv_ext2, wsv_ext2, dx_ext2, dy_ext2, dz_ext2, dw_ext2);
  }
  return value / 30.0;
}


struct osn_context;
int open_simplex_noise(int64_t seed, struct osn_context **ctx);
void open_simplex_noise_free(struct osn_context *ctx);
int open_simplex_noise_init_perm(struct osn_context *ctx, int16_t p[], int nelements);
double open_simplex_noise2(struct osn_context *ctx, double x, double y);
double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z);
double open_simplex_noise4(struct osn_context *ctx, double x, double y, double z, double w);
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
};
static const int8_t gradients2D[] = {5, 2, 2, 5, -5, 2, -2, 5, 5, -2, 2, -5, -5, -2, -2, -5};
static const signed char gradients3D[] = {-11, 4, 4, -4, 11, 4, -4, 4, 11, 11, 4, 4, 4, 11, 4, 4, 4, 11, -11, -4, 4, -4, -11, 4, -4, -4, 11, 11, -4, 4, 4, -11, 4, 4, -4, 11, -11, 4, -4, -4, 11, -4, -4, 4, -11, 11, 4, -4, 4, 11, -4, 4, 4, -11, -11, -4, -4, -4, -11, -4, -4, -4, -11, 11, -4, -4, 4, -11, -4, 4, -4, -11};
static const signed char gradients4D[] = {3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3};
static double extrapolate2(struct osn_context *ctx, int xsb, int ysb, double dx, double dy)
{
  int16_t *perm = ctx->perm;
  int index = perm[(perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E;
  return (gradients2D[index] * dx) + (gradients2D[index + 1] * dy);
}

static double extrapolate3(struct osn_context *ctx, int xsb, int ysb, int zsb, double dx, double dy, double dz)
{
  int16_t *perm = ctx->perm;
  int16_t *permGradIndex3D = ctx->permGradIndex3D;
  int index = permGradIndex3D[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF];
  return ((gradients3D[index] * dx) + (gradients3D[index + 1] * dy)) + (gradients3D[index + 2] * dz);
}

static double extrapolate4(struct osn_context *ctx, int xsb, int ysb, int zsb, int wsb, double dx, double dy, double dz, double dw)
{
  int16_t *perm = ctx->perm;
  int index = perm[(perm[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF] + wsb) & 0xFF] & 0xFC;
  return (((gradients4D[index] * dx) + (gradients4D[index + 1] * dy)) + (gradients4D[index + 2] * dz)) + (gradients4D[index + 3] * dw);
}

inline static int fastFloor(double x)
{
  int xi = (int) x;
  return (x < xi) ? (xi - 1) : (xi);
}

static int allocate_perm(struct osn_context *ctx, int nperm, int ngrad)
{
  if (ctx->perm)
  {
    free(ctx->perm);
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
  }
  ctx->perm = malloc((sizeof(*ctx->perm)) * nperm);
  if (!ctx->perm)
  {
    return -ENOMEM;
  }
  ctx->permGradIndex3D = malloc((sizeof(*ctx->permGradIndex3D)) * ngrad);
  if (!ctx->permGradIndex3D)
  {
    free(ctx->perm);
    return -ENOMEM;
  }
  return 0;
}

int open_simplex_noise_init_perm(struct osn_context *ctx, int16_t p[], int nelements)
{
  int i;
  int rc;
  rc = allocate_perm(ctx, nelements, 256);
  if (rc)
  {
    return rc;
  }
  memcpy(ctx->perm, p, (sizeof(*ctx->perm)) * nelements);
  for (i = 0; i < 256; i += 1)
  {
    ctx->permGradIndex3D[i] = (int16_t) ((ctx->perm[i] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
  }

  return 0;
}

int open_simplex_noise(int64_t seed, struct osn_context **ctx)
{
  int rc;
  int16_t source[256];
  int i;
  int16_t *perm;
  unsigned int perm_idx = 0;
  int16_t *permGradIndex3D;
  unsigned int permGradIndex3D_idx = 0;
  *ctx = malloc(sizeof(*(*ctx)));
  if (!(*ctx))
  {
    return -ENOMEM;
  }
  (*ctx)->perm = 0;
  (*ctx)->permGradIndex3D = 0;
  rc = allocate_perm(*ctx, 256, 256);
  if (rc)
  {
    free(*ctx);
    return rc;
  }
  perm_idx = (*ctx)->perm_idx;
  permGradIndex3D_idx = (*ctx)->permGradIndex3D_idx;
  for (i = 0; i < 256; i += 1)
  {
    source[i] = (int16_t) i;
  }

  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  for (i = 255; i >= 0; i -= 1)
  {
    seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
    int r = (int) ((seed + 31) % (i + 1));
    if (r < 0)
    {
      r += i + 1;
    }
    perm[i + perm_idx] = source[r];
    permGradIndex3D[i + permGradIndex3D_idx] = (short) ((perm[i + perm_idx] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
    source[r] = source[i];
  }

  return 0;
}

void open_simplex_noise_free(struct osn_context *ctx)
{
  if (!ctx)
  {
    return;
  }
  if (ctx->perm)
  {
    free(ctx->perm);
    ctx->perm = 0;
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
    ctx->permGradIndex3D = 0;
  }
  free(ctx);
}

double open_simplex_noise2(struct osn_context *ctx, double x, double y)
{
  double stretchOffset = (x + y) * (-0.211324865405187);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  double squishOffset = (xsb + ysb) * 0.366025403784439;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double inSum = xins + yins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dx_ext;
  double dy_ext;
  int xsv_ext;
  int ysv_ext;
  double value = 0;
  double dx1 = (dx0 - 1) - 0.366025403784439;
  double dy1 = (dy0 - 0) - 0.366025403784439;
  double attn1 = (2 - (dx1 * dx1)) - (dy1 * dy1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
  }
  double dx2 = (dx0 - 0) - 0.366025403784439;
  double dy2 = (dy0 - 1) - 0.366025403784439;
  double attn2 = (2 - (dx2 * dx2)) - (dy2 * dy2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
  }
  if (inSum <= 1)
  {
    double zins = 1 - inSum;
    if ((zins > xins) || (zins > yins))
    {
      if (xins > yins)
      {
        xsv_ext = xsb + 1;
        ysv_ext = ysb - 1;
        dx_ext = dx0 - 1;
        dy_ext = dy0 + 1;
      }
      else
      {
        xsv_ext = xsb - 1;
        ysv_ext = ysb + 1;
        dx_ext = dx0 + 1;
        dy_ext = dy0 - 1;
      }
    }
    else
    {
      xsv_ext = xsb + 1;
      ysv_ext = ysb + 1;
      dx_ext = (dx0 - 1) - (2 * 0.366025403784439);
      dy_ext = (dy0 - 1) - (2 * 0.366025403784439);
    }
  }
  else
  {
    double zins = 2 - inSum;
    if ((zins < xins) || (zins < yins))
    {
      if (xins > yins)
      {
        xsv_ext = xsb + 2;
        ysv_ext = ysb + 0;
        dx_ext = (dx0 - 2) - (2 * 0.366025403784439);
        dy_ext = (dy0 + 0) - (2 * 0.366025403784439);
      }
      else
      {
        xsv_ext = xsb + 0;
        ysv_ext = ysb + 2;
        dx_ext = (dx0 + 0) - (2 * 0.366025403784439);
        dy_ext = (dy0 - 2) - (2 * 0.366025403784439);
      }
    }
    else
    {
      dx_ext = dx0;
      dy_ext = dy0;
      xsv_ext = xsb;
      ysv_ext = ysb;
    }
    xsb += 1;
    ysb += 1;
    dx0 = (dx0 - 1) - (2 * 0.366025403784439);
    dy0 = (dy0 - 1) - (2 * 0.366025403784439);
  }
  double attn0 = (2 - (dx0 * dx0)) - (dy0 * dy0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate2(ctx, xsb, ysb, dx0, dy0);
  }
  double attn_ext = (2 - (dx_ext * dx_ext)) - (dy_ext * dy_ext);
  if (attn_ext > 0)
  {
    attn_ext *= attn_ext;
    value += (attn_ext * attn_ext) * extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
  }
  return value / 47.0;
}

double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z)
{
  double stretchOffset = ((x + y) + z) * ((-1.0) / 6.0);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  double zs = z + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  int zsb = fastFloor(zs);
  double squishOffset = ((xsb + ysb) + zsb) * (1.0 / 3.0);
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double zb = zsb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double zins = zs - zsb;
  double inSum = (xins + yins) + zins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dz0 = z - zb;
  double dx_ext0;
  double dy_ext0;
  double dz_ext0;
  double dx_ext1;
  double dy_ext1;
  double dz_ext1;
  int xsv_ext0;
  int ysv_ext0;
  int zsv_ext0;
  int xsv_ext1;
  int ysv_ext1;
  int zsv_ext1;
  double value = 0;
  if (inSum <= 1)
  {
    int8_t aPoint = 0x01;
    double aScore = xins;
    int8_t bPoint = 0x02;
    double bScore = yins;
    if ((aScore >= bScore) && (zins > bScore))
    {
      bScore = zins;
      bPoint = 0x04;
    }
    else
      if ((aScore < bScore) && (zins > aScore))
    {
      aScore = zins;
      aPoint = 0x04;
    }
    double wins = 1 - inSum;
    if ((wins > aScore) || (wins > bScore))
    {
      int8_t c = (bScore > aScore) ? (bPoint) : (aPoint);
      if ((c & 0x01) == 0)
      {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = xsb;
        dx_ext0 = dx0 + 1;
        dx_ext1 = dx0;
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = xsb + 1);
        dx_ext0 = (dx_ext1 = dx0 - 1);
      }
      if ((c & 0x02) == 0)
      {
        ysv_ext0 = (ysv_ext1 = ysb);
        dy_ext0 = (dy_ext1 = dy0);
        if ((c & 0x01) == 0)
        {
          ysv_ext1 -= 1;
          dy_ext1 += 1;
        }
        else
        {
          ysv_ext0 -= 1;
          dy_ext0 += 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = ysb + 1);
        dy_ext0 = (dy_ext1 = dy0 - 1);
      }
      if ((c & 0x04) == 0)
      {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb - 1;
        dz_ext0 = dz0;
        dz_ext1 = dz0 + 1;
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = zsb + 1);
        dz_ext0 = (dz_ext1 = dz0 - 1);
      }
    }
    else
    {
      int8_t c = (int8_t) (aPoint | bPoint);
      if ((c & 0x01) == 0)
      {
        xsv_ext0 = xsb;
        xsv_ext1 = xsb - 1;
        dx_ext0 = dx0 - (2 * (1.0 / 3.0));
        dx_ext1 = (dx0 + 1) - (1.0 / 3.0);
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = xsb + 1);
        dx_ext0 = (dx0 - 1) - (2 * (1.0 / 3.0));
        dx_ext1 = (dx0 - 1) - (1.0 / 3.0);
      }
      if ((c & 0x02) == 0)
      {
        ysv_ext0 = ysb;
        ysv_ext1 = ysb - 1;
        dy_ext0 = dy0 - (2 * (1.0 / 3.0));
        dy_ext1 = (dy0 + 1) - (1.0 / 3.0);
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = ysb + 1);
        dy_ext0 = (dy0 - 1) - (2 * (1.0 / 3.0));
        dy_ext1 = (dy0 - 1) - (1.0 / 3.0);
      }
      if ((c & 0x04) == 0)
      {
        zsv_ext0 = zsb;
        zsv_ext1 = zsb - 1;
        dz_ext0 = dz0 - (2 * (1.0 / 3.0));
        dz_ext1 = (dz0 + 1) - (1.0 / 3.0);
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = zsb + 1);
        dz_ext0 = (dz0 - 1) - (2 * (1.0 / 3.0));
        dz_ext1 = (dz0 - 1) - (1.0 / 3.0);
      }
    }
    double attn0 = ((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0);
    if (attn0 > 0)
    {
      attn0 *= attn0;
      value += (attn0 * attn0) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 0, dx0, dy0, dz0);
    }
    double dx1 = (dx0 - 1) - (1.0 / 3.0);
    double dy1 = (dy0 - 0) - (1.0 / 3.0);
    double dz1 = (dz0 - 0) - (1.0 / 3.0);
    double attn1 = ((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
    }
    double dx2 = (dx0 - 0) - (1.0 / 3.0);
    double dy2 = (dy0 - 1) - (1.0 / 3.0);
    double dz2 = dz1;
    double attn2 = ((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
    }
    double dx3 = dx2;
    double dy3 = dy1;
    double dz3 = (dz0 - 1) - (1.0 / 3.0);
    double attn3 = ((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
    }
  }
  else
    if (inSum >= 2)
  {
    int8_t aPoint = 0x06;
    double aScore = xins;
    int8_t bPoint = 0x05;
    double bScore = yins;
    if ((aScore <= bScore) && (zins < bScore))
    {
      bScore = zins;
      bPoint = 0x03;
    }
    else
      if ((aScore > bScore) && (zins < aScore))
    {
      aScore = zins;
      aPoint = 0x03;
    }
    double wins = 3 - inSum;
    if ((wins < aScore) || (wins < bScore))
    {
      int8_t c = (bScore < aScore) ? (bPoint) : (aPoint);
      if ((c & 0x01) != 0)
      {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 2) - (3 * (1.0 / 3.0));
        dx_ext1 = (dx0 - 1) - (3 * (1.0 / 3.0));
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = xsb);
        dx_ext0 = (dx_ext1 = dx0 - (3 * (1.0 / 3.0)));
      }
      if ((c & 0x02) != 0)
      {
        ysv_ext0 = (ysv_ext1 = ysb + 1);
        dy_ext0 = (dy_ext1 = (dy0 - 1) - (3 * (1.0 / 3.0)));
        if ((c & 0x01) != 0)
        {
          ysv_ext1 += 1;
          dy_ext1 -= 1;
        }
        else
        {
          ysv_ext0 += 1;
          dy_ext0 -= 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = ysb);
        dy_ext0 = (dy_ext1 = dy0 - (3 * (1.0 / 3.0)));
      }
      if ((c & 0x04) != 0)
      {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 2;
        dz_ext0 = (dz0 - 1) - (3 * (1.0 / 3.0));
        dz_ext1 = (dz0 - 2) - (3 * (1.0 / 3.0));
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = zsb);
        dz_ext0 = (dz_ext1 = dz0 - (3 * (1.0 / 3.0)));
      }
    }
    else
    {
      int8_t c = (int8_t) (aPoint & bPoint);
      if ((c & 0x01) != 0)
      {
        xsv_ext0 = xsb + 1;
        xsv_ext1 = xsb + 2;
        dx_ext0 = (dx0 - 1) - (1.0 / 3.0);
        dx_ext1 = (dx0 - 2) - (2 * (1.0 / 3.0));
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = xsb);
        dx_ext0 = dx0 - (1.0 / 3.0);
        dx_ext1 = dx0 - (2 * (1.0 / 3.0));
      }
      if ((c & 0x02) != 0)
      {
        ysv_ext0 = ysb + 1;
        ysv_ext1 = ysb + 2;
        dy_ext0 = (dy0 - 1) - (1.0 / 3.0);
        dy_ext1 = (dy0 - 2) - (2 * (1.0 / 3.0));
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = ysb);
        dy_ext0 = dy0 - (1.0 / 3.0);
        dy_ext1 = dy0 - (2 * (1.0 / 3.0));
      }
      if ((c & 0x04) != 0)
      {
        zsv_ext0 = zsb + 1;
        zsv_ext1 = zsb + 2;
        dz_ext0 = (dz0 - 1) - (1.0 / 3.0);
        dz_ext1 = (dz0 - 2) - (2 * (1.0 / 3.0));
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = zsb);
        dz_ext0 = dz0 - (1.0 / 3.0);
        dz_ext1 = dz0 - (2 * (1.0 / 3.0));
      }
    }
    double dx3 = (dx0 - 1) - (2 * (1.0 / 3.0));
    double dy3 = (dy0 - 1) - (2 * (1.0 / 3.0));
    double dz3 = (dz0 - 0) - (2 * (1.0 / 3.0));
    double attn3 = ((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 0, dx3, dy3, dz3);
    }
    double dx2 = dx3;
    double dy2 = (dy0 - 0) - (2 * (1.0 / 3.0));
    double dz2 = (dz0 - 1) - (2 * (1.0 / 3.0));
    double attn2 = ((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 1, dx2, dy2, dz2);
    }
    double dx1 = (dx0 - 0) - (2 * (1.0 / 3.0));
    double dy1 = dy3;
    double dz1 = dz2;
    double attn1 = ((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 1, dx1, dy1, dz1);
    }
    dx0 = (dx0 - 1) - (3 * (1.0 / 3.0));
    dy0 = (dy0 - 1) - (3 * (1.0 / 3.0));
    dz0 = (dz0 - 1) - (3 * (1.0 / 3.0));
    double attn0 = ((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0);
    if (attn0 > 0)
    {
      attn0 *= attn0;
      value += (attn0 * attn0) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 1, dx0, dy0, dz0);
    }
  }
  else
  {
    double aScore;
    int8_t aPoint;
    int aIsFurtherSide;
    double bScore;
    int8_t bPoint;
    int bIsFurtherSide;
    double p1 = xins + yins;
    if (p1 > 1)
    {
      aScore = p1 - 1;
      aPoint = 0x03;
      aIsFurtherSide = 1;
    }
    else
    {
      aScore = 1 - p1;
      aPoint = 0x04;
      aIsFurtherSide = 0;
    }
    double p2 = xins + zins;
    if (p2 > 1)
    {
      bScore = p2 - 1;
      bPoint = 0x05;
      bIsFurtherSide = 1;
    }
    else
    {
      bScore = 1 - p2;
      bPoint = 0x02;
      bIsFurtherSide = 0;
    }
    double p3 = yins + zins;
    if (p3 > 1)
    {
      double score = p3 - 1;
      if ((aScore <= bScore) && (aScore < score))
      {
        aScore = score;
        aPoint = 0x06;
        aIsFurtherSide = 1;
      }
      else
        if ((aScore > bScore) && (bScore < score))
      {
        bScore = score;
        bPoint = 0x06;
        bIsFurtherSide = 1;
      }
    }
    else
    {
      double score = 1 - p3;
      if ((aScore <= bScore) && (aScore < score))
      {
        aScore = score;
        aPoint = 0x01;
        aIsFurtherSide = 0;
      }
      else
        if ((aScore > bScore) && (bScore < score))
      {
        bScore = score;
        bPoint = 0x01;
        bIsFurtherSide = 0;
      }
    }
    if (aIsFurtherSide == bIsFurtherSide)
    {
      if (aIsFurtherSide)
      {
        dx_ext0 = (dx0 - 1) - (3 * (1.0 / 3.0));
        dy_ext0 = (dy0 - 1) - (3 * (1.0 / 3.0));
        dz_ext0 = (dz0 - 1) - (3 * (1.0 / 3.0));
        xsv_ext0 = xsb + 1;
        ysv_ext0 = ysb + 1;
        zsv_ext0 = zsb + 1;
        int8_t c = (int8_t) (aPoint & bPoint);
        if ((c & 0x01) != 0)
        {
          dx_ext1 = (dx0 - 2) - (2 * (1.0 / 3.0));
          dy_ext1 = dy0 - (2 * (1.0 / 3.0));
          dz_ext1 = dz0 - (2 * (1.0 / 3.0));
          xsv_ext1 = xsb + 2;
          ysv_ext1 = ysb;
          zsv_ext1 = zsb;
        }
        else
          if ((c & 0x02) != 0)
        {
          dx_ext1 = dx0 - (2 * (1.0 / 3.0));
          dy_ext1 = (dy0 - 2) - (2 * (1.0 / 3.0));
          dz_ext1 = dz0 - (2 * (1.0 / 3.0));
          xsv_ext1 = xsb;
          ysv_ext1 = ysb + 2;
          zsv_ext1 = zsb;
        }
        else
        {
          dx_ext1 = dx0 - (2 * (1.0 / 3.0));
          dy_ext1 = dy0 - (2 * (1.0 / 3.0));
          dz_ext1 = (dz0 - 2) - (2 * (1.0 / 3.0));
          xsv_ext1 = xsb;
          ysv_ext1 = ysb;
          zsv_ext1 = zsb + 2;
        }
      }
      else
      {
        dx_ext0 = dx0;
        dy_ext0 = dy0;
        dz_ext0 = dz0;
        xsv_ext0 = xsb;
        ysv_ext0 = ysb;
        zsv_ext0 = zsb;
        int8_t c = (int8_t) (aPoint | bPoint);
        if ((c & 0x01) == 0)
        {
          dx_ext1 = (dx0 + 1) - (1.0 / 3.0);
          dy_ext1 = (dy0 - 1) - (1.0 / 3.0);
          dz_ext1 = (dz0 - 1) - (1.0 / 3.0);
          xsv_ext1 = xsb - 1;
          ysv_ext1 = ysb + 1;
          zsv_ext1 = zsb + 1;
        }
        else
          if ((c & 0x02) == 0)
        {
          dx_ext1 = (dx0 - 1) - (1.0 / 3.0);
          dy_ext1 = (dy0 + 1) - (1.0 / 3.0);
          dz_ext1 = (dz0 - 1) - (1.0 / 3.0);
          xsv_ext1 = xsb + 1;
          ysv_ext1 = ysb - 1;
          zsv_ext1 = zsb + 1;
        }
        else
        {
          dx_ext1 = (dx0 - 1) - (1.0 / 3.0);
          dy_ext1 = (dy0 - 1) - (1.0 / 3.0);
          dz_ext1 = (dz0 + 1) - (1.0 / 3.0);
          xsv_ext1 = xsb + 1;
          ysv_ext1 = ysb + 1;
          zsv_ext1 = zsb - 1;
        }
      }
    }
    else
    {
      int8_t c1;
      int8_t c2;
      if (aIsFurtherSide)
      {
        c1 = aPoint;
        c2 = bPoint;
      }
      else
      {
        c1 = bPoint;
        c2 = aPoint;
      }
      if ((c1 & 0x01) == 0)
      {
        dx_ext0 = (dx0 + 1) - (1.0 / 3.0);
        dy_ext0 = (dy0 - 1) - (1.0 / 3.0);
        dz_ext0 = (dz0 - 1) - (1.0 / 3.0);
        xsv_ext0 = xsb - 1;
        ysv_ext0 = ysb + 1;
        zsv_ext0 = zsb + 1;
      }
      else
        if ((c1 & 0x02) == 0)
      {
        dx_ext0 = (dx0 - 1) - (1.0 / 3.0);
        dy_ext0 = (dy0 + 1) - (1.0 / 3.0);
        dz_ext0 = (dz0 - 1) - (1.0 / 3.0);
        xsv_ext0 = xsb + 1;
        ysv_ext0 = ysb - 1;
        zsv_ext0 = zsb + 1;
      }
      else
      {
        dx_ext0 = (dx0 - 1) - (1.0 / 3.0);
        dy_ext0 = (dy0 - 1) - (1.0 / 3.0);
        dz_ext0 = (dz0 + 1) - (1.0 / 3.0);
        xsv_ext0 = xsb + 1;
        ysv_ext0 = ysb + 1;
        zsv_ext0 = zsb - 1;
      }
      dx_ext1 = dx0 - (2 * (1.0 / 3.0));
      dy_ext1 = dy0 - (2 * (1.0 / 3.0));
      dz_ext1 = dz0 - (2 * (1.0 / 3.0));
      xsv_ext1 = xsb;
      ysv_ext1 = ysb;
      zsv_ext1 = zsb;
      if ((c2 & 0x01) != 0)
      {
        dx_ext1 -= 2;
        xsv_ext1 += 2;
      }
      else
        if ((c2 & 0x02) != 0)
      {
        dy_ext1 -= 2;
        ysv_ext1 += 2;
      }
      else
      {
        dz_ext1 -= 2;
        zsv_ext1 += 2;
      }
    }
    double dx1 = (dx0 - 1) - (1.0 / 3.0);
    double dy1 = (dy0 - 0) - (1.0 / 3.0);
    double dz1 = (dz0 - 0) - (1.0 / 3.0);
    double attn1 = ((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
    }
    double dx2 = (dx0 - 0) - (1.0 / 3.0);
    double dy2 = (dy0 - 1) - (1.0 / 3.0);
    double dz2 = dz1;
    double attn2 = ((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
    }
    double dx3 = dx2;
    double dy3 = dy1;
    double dz3 = (dz0 - 1) - (1.0 / 3.0);
    double attn3 = ((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
    }
    double dx4 = (dx0 - 1) - (2 * (1.0 / 3.0));
    double dy4 = (dy0 - 1) - (2 * (1.0 / 3.0));
    double dz4 = (dz0 - 0) - (2 * (1.0 / 3.0));
    double attn4 = ((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4);
    if (attn4 > 0)
    {
      attn4 *= attn4;
      value += (attn4 * attn4) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 0, dx4, dy4, dz4);
    }
    double dx5 = dx4;
    double dy5 = (dy0 - 0) - (2 * (1.0 / 3.0));
    double dz5 = (dz0 - 1) - (2 * (1.0 / 3.0));
    double attn5 = ((2 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5);
    if (attn5 > 0)
    {
      attn5 *= attn5;
      value += (attn5 * attn5) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 1, dx5, dy5, dz5);
    }
    double dx6 = (dx0 - 0) - (2 * (1.0 / 3.0));
    double dy6 = dy4;
    double dz6 = dz5;
    double attn6 = ((2 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6);
    if (attn6 > 0)
    {
      attn6 *= attn6;
      value += (attn6 * attn6) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 1, dx6, dy6, dz6);
    }
  }
  double attn_ext0 = ((2 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0);
  if (attn_ext0 > 0)
  {
    attn_ext0 *= attn_ext0;
    value += (attn_ext0 * attn_ext0) * extrapolate3(ctx, xsv_ext0, ysv_ext0, zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
  }
  double attn_ext1 = ((2 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1);
  if (attn_ext1 > 0)
  {
    attn_ext1 *= attn_ext1;
    value += (attn_ext1 * attn_ext1) * extrapolate3(ctx, xsv_ext1, ysv_ext1, zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
  }
  return value / 103.0;
}

double open_simplex_noise4(struct osn_context *ctx, double x, double y, double z, double w)
{
  double stretchOffset = (((x + y) + z) + w) * (-0.138196601125011);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  double zs = z + stretchOffset;
  double ws = w + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  int zsb = fastFloor(zs);
  int wsb = fastFloor(ws);
  double squishOffset = (((xsb + ysb) + zsb) + wsb) * 0.309016994374947;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double zb = zsb + squishOffset;
  double wb = wsb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double zins = zs - zsb;
  double wins = ws - wsb;
  double inSum = ((xins + yins) + zins) + wins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dz0 = z - zb;
  double dw0 = w - wb;
  double dx_ext0;
  double dy_ext0;
  double dz_ext0;
  double dw_ext0;
  double dx_ext1;
  double dy_ext1;
  double dz_ext1;
  double dw_ext1;
  double dx_ext2;
  double dy_ext2;
  double dz_ext2;
  double dw_ext2;
  int xsv_ext0;
  int ysv_ext0;
  int zsv_ext0;
  int wsv_ext0;
  int xsv_ext1;
  int ysv_ext1;
  int zsv_ext1;
  int wsv_ext1;
  int xsv_ext2;
  int ysv_ext2;
  int zsv_ext2;
  int wsv_ext2;
  double value = 0;
  if (inSum <= 1)
  {
    int8_t aPoint = 0x01;
    double aScore = xins;
    int8_t bPoint = 0x02;
    double bScore = yins;
    if ((aScore >= bScore) && (zins > bScore))
    {
      bScore = zins;
      bPoint = 0x04;
    }
    else
      if ((aScore < bScore) && (zins > aScore))
    {
      aScore = zins;
      aPoint = 0x04;
    }
    if ((aScore >= bScore) && (wins > bScore))
    {
      bScore = wins;
      bPoint = 0x08;
    }
    else
      if ((aScore < bScore) && (wins > aScore))
    {
      aScore = wins;
      aPoint = 0x08;
    }
    double uins = 1 - inSum;
    if ((uins > aScore) || (uins > bScore))
    {
      int8_t c = (bScore > aScore) ? (bPoint) : (aPoint);
      if ((c & 0x01) == 0)
      {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = (xsv_ext2 = xsb);
        dx_ext0 = dx0 + 1;
        dx_ext1 = (dx_ext2 = dx0);
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb + 1));
        dx_ext0 = (dx_ext1 = (dx_ext2 = dx0 - 1));
      }
      if ((c & 0x02) == 0)
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
        dy_ext0 = (dy_ext1 = (dy_ext2 = dy0));
        if ((c & 0x01) == 0x01)
        {
          ysv_ext0 -= 1;
          dy_ext0 += 1;
        }
        else
        {
          ysv_ext1 -= 1;
          dy_ext1 += 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
        dy_ext0 = (dy_ext1 = (dy_ext2 = dy0 - 1));
      }
      if ((c & 0x04) == 0)
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
        dz_ext0 = (dz_ext1 = (dz_ext2 = dz0));
        if ((c & 0x03) != 0)
        {
          if ((c & 0x03) == 0x03)
          {
            zsv_ext0 -= 1;
            dz_ext0 += 1;
          }
          else
          {
            zsv_ext1 -= 1;
            dz_ext1 += 1;
          }
        }
        else
        {
          zsv_ext2 -= 1;
          dz_ext2 += 1;
        }
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
        dz_ext0 = (dz_ext1 = (dz_ext2 = dz0 - 1));
      }
      if ((c & 0x08) == 0)
      {
        wsv_ext0 = (wsv_ext1 = wsb);
        wsv_ext2 = wsb - 1;
        dw_ext0 = (dw_ext1 = dw0);
        dw_ext2 = dw0 + 1;
      }
      else
      {
        wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb + 1));
        dw_ext0 = (dw_ext1 = (dw_ext2 = dw0 - 1));
      }
    }
    else
    {
      int8_t c = (int8_t) (aPoint | bPoint);
      if ((c & 0x01) == 0)
      {
        xsv_ext0 = (xsv_ext2 = xsb);
        xsv_ext1 = xsb - 1;
        dx_ext0 = dx0 - (2 * 0.309016994374947);
        dx_ext1 = (dx0 + 1) - 0.309016994374947;
        dx_ext2 = dx0 - 0.309016994374947;
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb + 1));
        dx_ext0 = (dx0 - 1) - (2 * 0.309016994374947);
        dx_ext1 = (dx_ext2 = (dx0 - 1) - 0.309016994374947);
      }
      if ((c & 0x02) == 0)
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
        dy_ext0 = dy0 - (2 * 0.309016994374947);
        dy_ext1 = (dy_ext2 = dy0 - 0.309016994374947);
        if ((c & 0x01) == 0x01)
        {
          ysv_ext1 -= 1;
          dy_ext1 += 1;
        }
        else
        {
          ysv_ext2 -= 1;
          dy_ext2 += 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
        dy_ext0 = (dy0 - 1) - (2 * 0.309016994374947);
        dy_ext1 = (dy_ext2 = (dy0 - 1) - 0.309016994374947);
      }
      if ((c & 0x04) == 0)
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
        dz_ext0 = dz0 - (2 * 0.309016994374947);
        dz_ext1 = (dz_ext2 = dz0 - 0.309016994374947);
        if ((c & 0x03) == 0x03)
        {
          zsv_ext1 -= 1;
          dz_ext1 += 1;
        }
        else
        {
          zsv_ext2 -= 1;
          dz_ext2 += 1;
        }
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
        dz_ext0 = (dz0 - 1) - (2 * 0.309016994374947);
        dz_ext1 = (dz_ext2 = (dz0 - 1) - 0.309016994374947);
      }
      if ((c & 0x08) == 0)
      {
        wsv_ext0 = (wsv_ext1 = wsb);
        wsv_ext2 = wsb - 1;
        dw_ext0 = dw0 - (2 * 0.309016994374947);
        dw_ext1 = dw0 - 0.309016994374947;
        dw_ext2 = (dw0 + 1) - 0.309016994374947;
      }
      else
      {
        wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb + 1));
        dw_ext0 = (dw0 - 1) - (2 * 0.309016994374947);
        dw_ext1 = (dw_ext2 = (dw0 - 1) - 0.309016994374947);
      }
    }
    double attn0 = (((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0)) - (dw0 * dw0);
    if (attn0 > 0)
    {
      attn0 *= attn0;
      value += (attn0 * attn0) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 0, dx0, dy0, dz0, dw0);
    }
    double dx1 = (dx0 - 1) - 0.309016994374947;
    double dy1 = (dy0 - 0) - 0.309016994374947;
    double dz1 = (dz0 - 0) - 0.309016994374947;
    double dw1 = (dw0 - 0) - 0.309016994374947;
    double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
    }
    double dx2 = (dx0 - 0) - 0.309016994374947;
    double dy2 = (dy0 - 1) - 0.309016994374947;
    double dz2 = dz1;
    double dw2 = dw1;
    double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
    }
    double dx3 = dx2;
    double dy3 = dy1;
    double dz3 = (dz0 - 1) - 0.309016994374947;
    double dw3 = dw1;
    double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
    }
    double dx4 = dx2;
    double dy4 = dy1;
    double dz4 = dz1;
    double dw4 = (dw0 - 1) - 0.309016994374947;
    double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
    if (attn4 > 0)
    {
      attn4 *= attn4;
      value += (attn4 * attn4) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
    }
  }
  else
    if (inSum >= 3)
  {
    int8_t aPoint = 0x0E;
    double aScore = xins;
    int8_t bPoint = 0x0D;
    double bScore = yins;
    if ((aScore <= bScore) && (zins < bScore))
    {
      bScore = zins;
      bPoint = 0x0B;
    }
    else
      if ((aScore > bScore) && (zins < aScore))
    {
      aScore = zins;
      aPoint = 0x0B;
    }
    if ((aScore <= bScore) && (wins < bScore))
    {
      bScore = wins;
      bPoint = 0x07;
    }
    else
      if ((aScore > bScore) && (wins < aScore))
    {
      aScore = wins;
      aPoint = 0x07;
    }
    double uins = 4 - inSum;
    if ((uins < aScore) || (uins < bScore))
    {
      int8_t c = (bScore < aScore) ? (bPoint) : (aPoint);
      if ((c & 0x01) != 0)
      {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = (xsv_ext2 = xsb + 1);
        dx_ext0 = (dx0 - 2) - (4 * 0.309016994374947);
        dx_ext1 = (dx_ext2 = (dx0 - 1) - (4 * 0.309016994374947));
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb));
        dx_ext0 = (dx_ext1 = (dx_ext2 = dx0 - (4 * 0.309016994374947)));
      }
      if ((c & 0x02) != 0)
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
        dy_ext0 = (dy_ext1 = (dy_ext2 = (dy0 - 1) - (4 * 0.309016994374947)));
        if ((c & 0x01) != 0)
        {
          ysv_ext1 += 1;
          dy_ext1 -= 1;
        }
        else
        {
          ysv_ext0 += 1;
          dy_ext0 -= 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
        dy_ext0 = (dy_ext1 = (dy_ext2 = dy0 - (4 * 0.309016994374947)));
      }
      if ((c & 0x04) != 0)
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
        dz_ext0 = (dz_ext1 = (dz_ext2 = (dz0 - 1) - (4 * 0.309016994374947)));
        if ((c & 0x03) != 0x03)
        {
          if ((c & 0x03) == 0)
          {
            zsv_ext0 += 1;
            dz_ext0 -= 1;
          }
          else
          {
            zsv_ext1 += 1;
            dz_ext1 -= 1;
          }
        }
        else
        {
          zsv_ext2 += 1;
          dz_ext2 -= 1;
        }
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
        dz_ext0 = (dz_ext1 = (dz_ext2 = dz0 - (4 * 0.309016994374947)));
      }
      if ((c & 0x08) != 0)
      {
        wsv_ext0 = (wsv_ext1 = wsb + 1);
        wsv_ext2 = wsb + 2;
        dw_ext0 = (dw_ext1 = (dw0 - 1) - (4 * 0.309016994374947));
        dw_ext2 = (dw0 - 2) - (4 * 0.309016994374947);
      }
      else
      {
        wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb));
        dw_ext0 = (dw_ext1 = (dw_ext2 = dw0 - (4 * 0.309016994374947)));
      }
    }
    else
    {
      int8_t c = (int8_t) (aPoint & bPoint);
      if ((c & 0x01) != 0)
      {
        xsv_ext0 = (xsv_ext2 = xsb + 1);
        xsv_ext1 = xsb + 2;
        dx_ext0 = (dx0 - 1) - (2 * 0.309016994374947);
        dx_ext1 = (dx0 - 2) - (3 * 0.309016994374947);
        dx_ext2 = (dx0 - 1) - (3 * 0.309016994374947);
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb));
        dx_ext0 = dx0 - (2 * 0.309016994374947);
        dx_ext1 = (dx_ext2 = dx0 - (3 * 0.309016994374947));
      }
      if ((c & 0x02) != 0)
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
        dy_ext0 = (dy0 - 1) - (2 * 0.309016994374947);
        dy_ext1 = (dy_ext2 = (dy0 - 1) - (3 * 0.309016994374947));
        if ((c & 0x01) != 0)
        {
          ysv_ext2 += 1;
          dy_ext2 -= 1;
        }
        else
        {
          ysv_ext1 += 1;
          dy_ext1 -= 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
        dy_ext0 = dy0 - (2 * 0.309016994374947);
        dy_ext1 = (dy_ext2 = dy0 - (3 * 0.309016994374947));
      }
      if ((c & 0x04) != 0)
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
        dz_ext0 = (dz0 - 1) - (2 * 0.309016994374947);
        dz_ext1 = (dz_ext2 = (dz0 - 1) - (3 * 0.309016994374947));
        if ((c & 0x03) != 0)
        {
          zsv_ext2 += 1;
          dz_ext2 -= 1;
        }
        else
        {
          zsv_ext1 += 1;
          dz_ext1 -= 1;
        }
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
        dz_ext0 = dz0 - (2 * 0.309016994374947);
        dz_ext1 = (dz_ext2 = dz0 - (3 * 0.309016994374947));
      }
      if ((c & 0x08) != 0)
      {
        wsv_ext0 = (wsv_ext1 = wsb + 1);
        wsv_ext2 = wsb + 2;
        dw_ext0 = (dw0 - 1) - (2 * 0.309016994374947);
        dw_ext1 = (dw0 - 1) - (3 * 0.309016994374947);
        dw_ext2 = (dw0 - 2) - (3 * 0.309016994374947);
      }
      else
      {
        wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb));
        dw_ext0 = dw0 - (2 * 0.309016994374947);
        dw_ext1 = (dw_ext2 = dw0 - (3 * 0.309016994374947));
      }
    }
    double dx4 = (dx0 - 1) - (3 * 0.309016994374947);
    double dy4 = (dy0 - 1) - (3 * 0.309016994374947);
    double dz4 = (dz0 - 1) - (3 * 0.309016994374947);
    double dw4 = dw0 - (3 * 0.309016994374947);
    double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
    if (attn4 > 0)
    {
      attn4 *= attn4;
      value += (attn4 * attn4) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
    }
    double dx3 = dx4;
    double dy3 = dy4;
    double dz3 = dz0 - (3 * 0.309016994374947);
    double dw3 = (dw0 - 1) - (3 * 0.309016994374947);
    double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
    }
    double dx2 = dx4;
    double dy2 = dy0 - (3 * 0.309016994374947);
    double dz2 = dz4;
    double dw2 = dw3;
    double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
    }
    double dx1 = dx0 - (3 * 0.309016994374947);
    double dz1 = dz4;
    double dy1 = dy4;
    double dw1 = dw3;
    double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
    }
    dx0 = (dx0 - 1) - (4 * 0.309016994374947);
    dy0 = (dy0 - 1) - (4 * 0.309016994374947);
    dz0 = (dz0 - 1) - (4 * 0.309016994374947);
    dw0 = (dw0 - 1) - (4 * 0.309016994374947);
    double attn0 = (((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0)) - (dw0 * dw0);
    if (attn0 > 0)
    {
      attn0 *= attn0;
      value += (attn0 * attn0) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 1, dx0, dy0, dz0, dw0);
    }
  }
  else
    if (inSum <= 2)
  {
    double aScore;
    int8_t aPoint;
    int aIsBiggerSide = 1;
    double bScore;
    int8_t bPoint;
    int bIsBiggerSide = 1;
    if ((xins + yins) > (zins + wins))
    {
      aScore = xins + yins;
      aPoint = 0x03;
    }
    else
    {
      aScore = zins + wins;
      aPoint = 0x0C;
    }
    if ((xins + zins) > (yins + wins))
    {
      bScore = xins + zins;
      bPoint = 0x05;
    }
    else
    {
      bScore = yins + wins;
      bPoint = 0x0A;
    }
    if ((xins + wins) > (yins + zins))
    {
      double score = xins + wins;
      if ((aScore >= bScore) && (score > bScore))
      {
        bScore = score;
        bPoint = 0x09;
      }
      else
        if ((aScore < bScore) && (score > aScore))
      {
        aScore = score;
        aPoint = 0x09;
      }
    }
    else
    {
      double score = yins + zins;
      if ((aScore >= bScore) && (score > bScore))
      {
        bScore = score;
        bPoint = 0x06;
      }
      else
        if ((aScore < bScore) && (score > aScore))
      {
        aScore = score;
        aPoint = 0x06;
      }
    }
    double p1 = (2 - inSum) + xins;
    if ((aScore >= bScore) && (p1 > bScore))
    {
      bScore = p1;
      bPoint = 0x01;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore < bScore) && (p1 > aScore))
    {
      aScore = p1;
      aPoint = 0x01;
      aIsBiggerSide = 0;
    }
    double p2 = (2 - inSum) + yins;
    if ((aScore >= bScore) && (p2 > bScore))
    {
      bScore = p2;
      bPoint = 0x02;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore < bScore) && (p2 > aScore))
    {
      aScore = p2;
      aPoint = 0x02;
      aIsBiggerSide = 0;
    }
    double p3 = (2 - inSum) + zins;
    if ((aScore >= bScore) && (p3 > bScore))
    {
      bScore = p3;
      bPoint = 0x04;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore < bScore) && (p3 > aScore))
    {
      aScore = p3;
      aPoint = 0x04;
      aIsBiggerSide = 0;
    }
    double p4 = (2 - inSum) + wins;
    if ((aScore >= bScore) && (p4 > bScore))
    {
      bScore = p4;
      bPoint = 0x08;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore < bScore) && (p4 > aScore))
    {
      aScore = p4;
      aPoint = 0x08;
      aIsBiggerSide = 0;
    }
    if (aIsBiggerSide == bIsBiggerSide)
    {
      if (aIsBiggerSide)
      {
        int8_t c1 = (int8_t) (aPoint | bPoint);
        int8_t c2 = (int8_t) (aPoint & bPoint);
        if ((c1 & 0x01) == 0)
        {
          xsv_ext0 = xsb;
          xsv_ext1 = xsb - 1;
          dx_ext0 = dx0 - (3 * 0.309016994374947);
          dx_ext1 = (dx0 + 1) - (2 * 0.309016994374947);
        }
        else
        {
          xsv_ext0 = (xsv_ext1 = xsb + 1);
          dx_ext0 = (dx0 - 1) - (3 * 0.309016994374947);
          dx_ext1 = (dx0 - 1) - (2 * 0.309016994374947);
        }
        if ((c1 & 0x02) == 0)
        {
          ysv_ext0 = ysb;
          ysv_ext1 = ysb - 1;
          dy_ext0 = dy0 - (3 * 0.309016994374947);
          dy_ext1 = (dy0 + 1) - (2 * 0.309016994374947);
        }
        else
        {
          ysv_ext0 = (ysv_ext1 = ysb + 1);
          dy_ext0 = (dy0 - 1) - (3 * 0.309016994374947);
          dy_ext1 = (dy0 - 1) - (2 * 0.309016994374947);
        }
        if ((c1 & 0x04) == 0)
        {
          zsv_ext0 = zsb;
          zsv_ext1 = zsb - 1;
          dz_ext0 = dz0 - (3 * 0.309016994374947);
          dz_ext1 = (dz0 + 1) - (2 * 0.309016994374947);
        }
        else
        {
          zsv_ext0 = (zsv_ext1 = zsb + 1);
          dz_ext0 = (dz0 - 1) - (3 * 0.309016994374947);
          dz_ext1 = (dz0 - 1) - (2 * 0.309016994374947);
        }
        if ((c1 & 0x08) == 0)
        {
          wsv_ext0 = wsb;
          wsv_ext1 = wsb - 1;
          dw_ext0 = dw0 - (3 * 0.309016994374947);
          dw_ext1 = (dw0 + 1) - (2 * 0.309016994374947);
        }
        else
        {
          wsv_ext0 = (wsv_ext1 = wsb + 1);
          dw_ext0 = (dw0 - 1) - (3 * 0.309016994374947);
          dw_ext1 = (dw0 - 1) - (2 * 0.309016994374947);
        }
        xsv_ext2 = xsb;
        ysv_ext2 = ysb;
        zsv_ext2 = zsb;
        wsv_ext2 = wsb;
        dx_ext2 = dx0 - (2 * 0.309016994374947);
        dy_ext2 = dy0 - (2 * 0.309016994374947);
        dz_ext2 = dz0 - (2 * 0.309016994374947);
        dw_ext2 = dw0 - (2 * 0.309016994374947);
        if ((c2 & 0x01) != 0)
        {
          xsv_ext2 += 2;
          dx_ext2 -= 2;
        }
        else
          if ((c2 & 0x02) != 0)
        {
          ysv_ext2 += 2;
          dy_ext2 -= 2;
        }
        else
          if ((c2 & 0x04) != 0)
        {
          zsv_ext2 += 2;
          dz_ext2 -= 2;
        }
        else
        {
          wsv_ext2 += 2;
          dw_ext2 -= 2;
        }
      }
      else
      {
        xsv_ext2 = xsb;
        ysv_ext2 = ysb;
        zsv_ext2 = zsb;
        wsv_ext2 = wsb;
        dx_ext2 = dx0;
        dy_ext2 = dy0;
        dz_ext2 = dz0;
        dw_ext2 = dw0;
        int8_t c = (int8_t) (aPoint | bPoint);
        if ((c & 0x01) == 0)
        {
          xsv_ext0 = xsb - 1;
          xsv_ext1 = xsb;
          dx_ext0 = (dx0 + 1) - 0.309016994374947;
          dx_ext1 = dx0 - 0.309016994374947;
        }
        else
        {
          xsv_ext0 = (xsv_ext1 = xsb + 1);
          dx_ext0 = (dx_ext1 = (dx0 - 1) - 0.309016994374947);
        }
        if ((c & 0x02) == 0)
        {
          ysv_ext0 = (ysv_ext1 = ysb);
          dy_ext0 = (dy_ext1 = dy0 - 0.309016994374947);
          if ((c & 0x01) == 0x01)
          {
            ysv_ext0 -= 1;
            dy_ext0 += 1;
          }
          else
          {
            ysv_ext1 -= 1;
            dy_ext1 += 1;
          }
        }
        else
        {
          ysv_ext0 = (ysv_ext1 = ysb + 1);
          dy_ext0 = (dy_ext1 = (dy0 - 1) - 0.309016994374947);
        }
        if ((c & 0x04) == 0)
        {
          zsv_ext0 = (zsv_ext1 = zsb);
          dz_ext0 = (dz_ext1 = dz0 - 0.309016994374947);
          if ((c & 0x03) == 0x03)
          {
            zsv_ext0 -= 1;
            dz_ext0 += 1;
          }
          else
          {
            zsv_ext1 -= 1;
            dz_ext1 += 1;
          }
        }
        else
        {
          zsv_ext0 = (zsv_ext1 = zsb + 1);
          dz_ext0 = (dz_ext1 = (dz0 - 1) - 0.309016994374947);
        }
        if ((c & 0x08) == 0)
        {
          wsv_ext0 = wsb;
          wsv_ext1 = wsb - 1;
          dw_ext0 = dw0 - 0.309016994374947;
          dw_ext1 = (dw0 + 1) - 0.309016994374947;
        }
        else
        {
          wsv_ext0 = (wsv_ext1 = wsb + 1);
          dw_ext0 = (dw_ext1 = (dw0 - 1) - 0.309016994374947);
        }
      }
    }
    else
    {
      int8_t c1;
      int8_t c2;
      if (aIsBiggerSide)
      {
        c1 = aPoint;
        c2 = bPoint;
      }
      else
      {
        c1 = bPoint;
        c2 = aPoint;
      }
      if ((c1 & 0x01) == 0)
      {
        xsv_ext0 = xsb - 1;
        xsv_ext1 = xsb;
        dx_ext0 = (dx0 + 1) - 0.309016994374947;
        dx_ext1 = dx0 - 0.309016994374947;
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = xsb + 1);
        dx_ext0 = (dx_ext1 = (dx0 - 1) - 0.309016994374947);
      }
      if ((c1 & 0x02) == 0)
      {
        ysv_ext0 = (ysv_ext1 = ysb);
        dy_ext0 = (dy_ext1 = dy0 - 0.309016994374947);
        if ((c1 & 0x01) == 0x01)
        {
          ysv_ext0 -= 1;
          dy_ext0 += 1;
        }
        else
        {
          ysv_ext1 -= 1;
          dy_ext1 += 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = ysb + 1);
        dy_ext0 = (dy_ext1 = (dy0 - 1) - 0.309016994374947);
      }
      if ((c1 & 0x04) == 0)
      {
        zsv_ext0 = (zsv_ext1 = zsb);
        dz_ext0 = (dz_ext1 = dz0 - 0.309016994374947);
        if ((c1 & 0x03) == 0x03)
        {
          zsv_ext0 -= 1;
          dz_ext0 += 1;
        }
        else
        {
          zsv_ext1 -= 1;
          dz_ext1 += 1;
        }
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = zsb + 1);
        dz_ext0 = (dz_ext1 = (dz0 - 1) - 0.309016994374947);
      }
      if ((c1 & 0x08) == 0)
      {
        wsv_ext0 = wsb;
        wsv_ext1 = wsb - 1;
        dw_ext0 = dw0 - 0.309016994374947;
        dw_ext1 = (dw0 + 1) - 0.309016994374947;
      }
      else
      {
        wsv_ext0 = (wsv_ext1 = wsb + 1);
        dw_ext0 = (dw_ext1 = (dw0 - 1) - 0.309016994374947);
      }
      xsv_ext2 = xsb;
      ysv_ext2 = ysb;
      zsv_ext2 = zsb;
      wsv_ext2 = wsb;
      dx_ext2 = dx0 - (2 * 0.309016994374947);
      dy_ext2 = dy0 - (2 * 0.309016994374947);
      dz_ext2 = dz0 - (2 * 0.309016994374947);
      dw_ext2 = dw0 - (2 * 0.309016994374947);
      if ((c2 & 0x01) != 0)
      {
        xsv_ext2 += 2;
        dx_ext2 -= 2;
      }
      else
        if ((c2 & 0x02) != 0)
      {
        ysv_ext2 += 2;
        dy_ext2 -= 2;
      }
      else
        if ((c2 & 0x04) != 0)
      {
        zsv_ext2 += 2;
        dz_ext2 -= 2;
      }
      else
      {
        wsv_ext2 += 2;
        dw_ext2 -= 2;
      }
    }
    double dx1 = (dx0 - 1) - 0.309016994374947;
    double dy1 = (dy0 - 0) - 0.309016994374947;
    double dz1 = (dz0 - 0) - 0.309016994374947;
    double dw1 = (dw0 - 0) - 0.309016994374947;
    double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
    }
    double dx2 = (dx0 - 0) - 0.309016994374947;
    double dy2 = (dy0 - 1) - 0.309016994374947;
    double dz2 = dz1;
    double dw2 = dw1;
    double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
    }
    double dx3 = dx2;
    double dy3 = dy1;
    double dz3 = (dz0 - 1) - 0.309016994374947;
    double dw3 = dw1;
    double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
    }
    double dx4 = dx2;
    double dy4 = dy1;
    double dz4 = dz1;
    double dw4 = (dw0 - 1) - 0.309016994374947;
    double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
    if (attn4 > 0)
    {
      attn4 *= attn4;
      value += (attn4 * attn4) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
    }
    double dx5 = (dx0 - 1) - (2 * 0.309016994374947);
    double dy5 = (dy0 - 1) - (2 * 0.309016994374947);
    double dz5 = (dz0 - 0) - (2 * 0.309016994374947);
    double dw5 = (dw0 - 0) - (2 * 0.309016994374947);
    double attn5 = (((2 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5)) - (dw5 * dw5);
    if (attn5 > 0)
    {
      attn5 *= attn5;
      value += (attn5 * attn5) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
    }
    double dx6 = (dx0 - 1) - (2 * 0.309016994374947);
    double dy6 = (dy0 - 0) - (2 * 0.309016994374947);
    double dz6 = (dz0 - 1) - (2 * 0.309016994374947);
    double dw6 = (dw0 - 0) - (2 * 0.309016994374947);
    double attn6 = (((2 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6)) - (dw6 * dw6);
    if (attn6 > 0)
    {
      attn6 *= attn6;
      value += (attn6 * attn6) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
    }
    double dx7 = (dx0 - 1) - (2 * 0.309016994374947);
    double dy7 = (dy0 - 0) - (2 * 0.309016994374947);
    double dz7 = (dz0 - 0) - (2 * 0.309016994374947);
    double dw7 = (dw0 - 1) - (2 * 0.309016994374947);
    double attn7 = (((2 - (dx7 * dx7)) - (dy7 * dy7)) - (dz7 * dz7)) - (dw7 * dw7);
    if (attn7 > 0)
    {
      attn7 *= attn7;
      value += (attn7 * attn7) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
    }
    double dx8 = (dx0 - 0) - (2 * 0.309016994374947);
    double dy8 = (dy0 - 1) - (2 * 0.309016994374947);
    double dz8 = (dz0 - 1) - (2 * 0.309016994374947);
    double dw8 = (dw0 - 0) - (2 * 0.309016994374947);
    double attn8 = (((2 - (dx8 * dx8)) - (dy8 * dy8)) - (dz8 * dz8)) - (dw8 * dw8);
    if (attn8 > 0)
    {
      attn8 *= attn8;
      value += (attn8 * attn8) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
    }
    double dx9 = (dx0 - 0) - (2 * 0.309016994374947);
    double dy9 = (dy0 - 1) - (2 * 0.309016994374947);
    double dz9 = (dz0 - 0) - (2 * 0.309016994374947);
    double dw9 = (dw0 - 1) - (2 * 0.309016994374947);
    double attn9 = (((2 - (dx9 * dx9)) - (dy9 * dy9)) - (dz9 * dz9)) - (dw9 * dw9);
    if (attn9 > 0)
    {
      attn9 *= attn9;
      value += (attn9 * attn9) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
    }
    double dx10 = (dx0 - 0) - (2 * 0.309016994374947);
    double dy10 = (dy0 - 0) - (2 * 0.309016994374947);
    double dz10 = (dz0 - 1) - (2 * 0.309016994374947);
    double dw10 = (dw0 - 1) - (2 * 0.309016994374947);
    double attn10 = (((2 - (dx10 * dx10)) - (dy10 * dy10)) - (dz10 * dz10)) - (dw10 * dw10);
    if (attn10 > 0)
    {
      attn10 *= attn10;
      value += (attn10 * attn10) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 1, dx10, dy10, dz10, dw10);
    }
  }
  else
  {
    double aScore;
    int8_t aPoint;
    int aIsBiggerSide = 1;
    double bScore;
    int8_t bPoint;
    int bIsBiggerSide = 1;
    if ((xins + yins) < (zins + wins))
    {
      aScore = xins + yins;
      aPoint = 0x0C;
    }
    else
    {
      aScore = zins + wins;
      aPoint = 0x03;
    }
    if ((xins + zins) < (yins + wins))
    {
      bScore = xins + zins;
      bPoint = 0x0A;
    }
    else
    {
      bScore = yins + wins;
      bPoint = 0x05;
    }
    if ((xins + wins) < (yins + zins))
    {
      double score = xins + wins;
      if ((aScore <= bScore) && (score < bScore))
      {
        bScore = score;
        bPoint = 0x06;
      }
      else
        if ((aScore > bScore) && (score < aScore))
      {
        aScore = score;
        aPoint = 0x06;
      }
    }
    else
    {
      double score = yins + zins;
      if ((aScore <= bScore) && (score < bScore))
      {
        bScore = score;
        bPoint = 0x09;
      }
      else
        if ((aScore > bScore) && (score < aScore))
      {
        aScore = score;
        aPoint = 0x09;
      }
    }
    double p1 = (3 - inSum) + xins;
    if ((aScore <= bScore) && (p1 < bScore))
    {
      bScore = p1;
      bPoint = 0x0E;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore > bScore) && (p1 < aScore))
    {
      aScore = p1;
      aPoint = 0x0E;
      aIsBiggerSide = 0;
    }
    double p2 = (3 - inSum) + yins;
    if ((aScore <= bScore) && (p2 < bScore))
    {
      bScore = p2;
      bPoint = 0x0D;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore > bScore) && (p2 < aScore))
    {
      aScore = p2;
      aPoint = 0x0D;
      aIsBiggerSide = 0;
    }
    double p3 = (3 - inSum) + zins;
    if ((aScore <= bScore) && (p3 < bScore))
    {
      bScore = p3;
      bPoint = 0x0B;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore > bScore) && (p3 < aScore))
    {
      aScore = p3;
      aPoint = 0x0B;
      aIsBiggerSide = 0;
    }
    double p4 = (3 - inSum) + wins;
    if ((aScore <= bScore) && (p4 < bScore))
    {
      bScore = p4;
      bPoint = 0x07;
      bIsBiggerSide = 0;
    }
    else
      if ((aScore > bScore) && (p4 < aScore))
    {
      aScore = p4;
      aPoint = 0x07;
      aIsBiggerSide = 0;
    }
    if (aIsBiggerSide == bIsBiggerSide)
    {
      if (aIsBiggerSide)
      {
        int8_t c1 = (int8_t) (aPoint & bPoint);
        int8_t c2 = (int8_t) (aPoint | bPoint);
        xsv_ext0 = (xsv_ext1 = xsb);
        ysv_ext0 = (ysv_ext1 = ysb);
        zsv_ext0 = (zsv_ext1 = zsb);
        wsv_ext0 = (wsv_ext1 = wsb);
        dx_ext0 = dx0 - 0.309016994374947;
        dy_ext0 = dy0 - 0.309016994374947;
        dz_ext0 = dz0 - 0.309016994374947;
        dw_ext0 = dw0 - 0.309016994374947;
        dx_ext1 = dx0 - (2 * 0.309016994374947);
        dy_ext1 = dy0 - (2 * 0.309016994374947);
        dz_ext1 = dz0 - (2 * 0.309016994374947);
        dw_ext1 = dw0 - (2 * 0.309016994374947);
        if ((c1 & 0x01) != 0)
        {
          xsv_ext0 += 1;
          dx_ext0 -= 1;
          xsv_ext1 += 2;
          dx_ext1 -= 2;
        }
        else
          if ((c1 & 0x02) != 0)
        {
          ysv_ext0 += 1;
          dy_ext0 -= 1;
          ysv_ext1 += 2;
          dy_ext1 -= 2;
        }
        else
          if ((c1 & 0x04) != 0)
        {
          zsv_ext0 += 1;
          dz_ext0 -= 1;
          zsv_ext1 += 2;
          dz_ext1 -= 2;
        }
        else
        {
          wsv_ext0 += 1;
          dw_ext0 -= 1;
          wsv_ext1 += 2;
          dw_ext1 -= 2;
        }
        xsv_ext2 = xsb + 1;
        ysv_ext2 = ysb + 1;
        zsv_ext2 = zsb + 1;
        wsv_ext2 = wsb + 1;
        dx_ext2 = (dx0 - 1) - (2 * 0.309016994374947);
        dy_ext2 = (dy0 - 1) - (2 * 0.309016994374947);
        dz_ext2 = (dz0 - 1) - (2 * 0.309016994374947);
        dw_ext2 = (dw0 - 1) - (2 * 0.309016994374947);
        if ((c2 & 0x01) == 0)
        {
          xsv_ext2 -= 2;
          dx_ext2 += 2;
        }
        else
          if ((c2 & 0x02) == 0)
        {
          ysv_ext2 -= 2;
          dy_ext2 += 2;
        }
        else
          if ((c2 & 0x04) == 0)
        {
          zsv_ext2 -= 2;
          dz_ext2 += 2;
        }
        else
        {
          wsv_ext2 -= 2;
          dw_ext2 += 2;
        }
      }
      else
      {
        xsv_ext2 = xsb + 1;
        ysv_ext2 = ysb + 1;
        zsv_ext2 = zsb + 1;
        wsv_ext2 = wsb + 1;
        dx_ext2 = (dx0 - 1) - (4 * 0.309016994374947);
        dy_ext2 = (dy0 - 1) - (4 * 0.309016994374947);
        dz_ext2 = (dz0 - 1) - (4 * 0.309016994374947);
        dw_ext2 = (dw0 - 1) - (4 * 0.309016994374947);
        int8_t c = (int8_t) (aPoint & bPoint);
        if ((c & 0x01) != 0)
        {
          xsv_ext0 = xsb + 2;
          xsv_ext1 = xsb + 1;
          dx_ext0 = (dx0 - 2) - (3 * 0.309016994374947);
          dx_ext1 = (dx0 - 1) - (3 * 0.309016994374947);
        }
        else
        {
          xsv_ext0 = (xsv_ext1 = xsb);
          dx_ext0 = (dx_ext1 = dx0 - (3 * 0.309016994374947));
        }
        if ((c & 0x02) != 0)
        {
          ysv_ext0 = (ysv_ext1 = ysb + 1);
          dy_ext0 = (dy_ext1 = (dy0 - 1) - (3 * 0.309016994374947));
          if ((c & 0x01) == 0)
          {
            ysv_ext0 += 1;
            dy_ext0 -= 1;
          }
          else
          {
            ysv_ext1 += 1;
            dy_ext1 -= 1;
          }
        }
        else
        {
          ysv_ext0 = (ysv_ext1 = ysb);
          dy_ext0 = (dy_ext1 = dy0 - (3 * 0.309016994374947));
        }
        if ((c & 0x04) != 0)
        {
          zsv_ext0 = (zsv_ext1 = zsb + 1);
          dz_ext0 = (dz_ext1 = (dz0 - 1) - (3 * 0.309016994374947));
          if ((c & 0x03) == 0)
          {
            zsv_ext0 += 1;
            dz_ext0 -= 1;
          }
          else
          {
            zsv_ext1 += 1;
            dz_ext1 -= 1;
          }
        }
        else
        {
          zsv_ext0 = (zsv_ext1 = zsb);
          dz_ext0 = (dz_ext1 = dz0 - (3 * 0.309016994374947));
        }
        if ((c & 0x08) != 0)
        {
          wsv_ext0 = wsb + 1;
          wsv_ext1 = wsb + 2;
          dw_ext0 = (dw0 - 1) - (3 * 0.309016994374947);
          dw_ext1 = (dw0 - 2) - (3 * 0.309016994374947);
        }
        else
        {
          wsv_ext0 = (wsv_ext1 = wsb);
          dw_ext0 = (dw_ext1 = dw0 - (3 * 0.309016994374947));
        }
      }
    }
    else
    {
      int8_t c1;
      int8_t c2;
      if (aIsBiggerSide)
      {
        c1 = aPoint;
        c2 = bPoint;
      }
      else
      {
        c1 = bPoint;
        c2 = aPoint;
      }
      if ((c1 & 0x01) != 0)
      {
        xsv_ext0 = xsb + 2;
        xsv_ext1 = xsb + 1;
        dx_ext0 = (dx0 - 2) - (3 * 0.309016994374947);
        dx_ext1 = (dx0 - 1) - (3 * 0.309016994374947);
      }
      else
      {
        xsv_ext0 = (xsv_ext1 = xsb);
        dx_ext0 = (dx_ext1 = dx0 - (3 * 0.309016994374947));
      }
      if ((c1 & 0x02) != 0)
      {
        ysv_ext0 = (ysv_ext1 = ysb + 1);
        dy_ext0 = (dy_ext1 = (dy0 - 1) - (3 * 0.309016994374947));
        if ((c1 & 0x01) == 0)
        {
          ysv_ext0 += 1;
          dy_ext0 -= 1;
        }
        else
        {
          ysv_ext1 += 1;
          dy_ext1 -= 1;
        }
      }
      else
      {
        ysv_ext0 = (ysv_ext1 = ysb);
        dy_ext0 = (dy_ext1 = dy0 - (3 * 0.309016994374947));
      }
      if ((c1 & 0x04) != 0)
      {
        zsv_ext0 = (zsv_ext1 = zsb + 1);
        dz_ext0 = (dz_ext1 = (dz0 - 1) - (3 * 0.309016994374947));
        if ((c1 & 0x03) == 0)
        {
          zsv_ext0 += 1;
          dz_ext0 -= 1;
        }
        else
        {
          zsv_ext1 += 1;
          dz_ext1 -= 1;
        }
      }
      else
      {
        zsv_ext0 = (zsv_ext1 = zsb);
        dz_ext0 = (dz_ext1 = dz0 - (3 * 0.309016994374947));
      }
      if ((c1 & 0x08) != 0)
      {
        wsv_ext0 = wsb + 1;
        wsv_ext1 = wsb + 2;
        dw_ext0 = (dw0 - 1) - (3 * 0.309016994374947);
        dw_ext1 = (dw0 - 2) - (3 * 0.309016994374947);
      }
      else
      {
        wsv_ext0 = (wsv_ext1 = wsb);
        dw_ext0 = (dw_ext1 = dw0 - (3 * 0.309016994374947));
      }
      xsv_ext2 = xsb + 1;
      ysv_ext2 = ysb + 1;
      zsv_ext2 = zsb + 1;
      wsv_ext2 = wsb + 1;
      dx_ext2 = (dx0 - 1) - (2 * 0.309016994374947);
      dy_ext2 = (dy0 - 1) - (2 * 0.309016994374947);
      dz_ext2 = (dz0 - 1) - (2 * 0.309016994374947);
      dw_ext2 = (dw0 - 1) - (2 * 0.309016994374947);
      if ((c2 & 0x01) == 0)
      {
        xsv_ext2 -= 2;
        dx_ext2 += 2;
      }
      else
        if ((c2 & 0x02) == 0)
      {
        ysv_ext2 -= 2;
        dy_ext2 += 2;
      }
      else
        if ((c2 & 0x04) == 0)
      {
        zsv_ext2 -= 2;
        dz_ext2 += 2;
      }
      else
      {
        wsv_ext2 -= 2;
        dw_ext2 += 2;
      }
    }
    double dx4 = (dx0 - 1) - (3 * 0.309016994374947);
    double dy4 = (dy0 - 1) - (3 * 0.309016994374947);
    double dz4 = (dz0 - 1) - (3 * 0.309016994374947);
    double dw4 = dw0 - (3 * 0.309016994374947);
    double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
    if (attn4 > 0)
    {
      attn4 *= attn4;
      value += (attn4 * attn4) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
    }
    double dx3 = dx4;
    double dy3 = dy4;
    double dz3 = dz0 - (3 * 0.309016994374947);
    double dw3 = (dw0 - 1) - (3 * 0.309016994374947);
    double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
    if (attn3 > 0)
    {
      attn3 *= attn3;
      value += (attn3 * attn3) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
    }
    double dx2 = dx4;
    double dy2 = dy0 - (3 * 0.309016994374947);
    double dz2 = dz4;
    double dw2 = dw3;
    double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
    if (attn2 > 0)
    {
      attn2 *= attn2;
      value += (attn2 * attn2) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
    }
    double dx1 = dx0 - (3 * 0.309016994374947);
    double dz1 = dz4;
    double dy1 = dy4;
    double dw1 = dw3;
    double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
    if (attn1 > 0)
    {
      attn1 *= attn1;
      value += (attn1 * attn1) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
    }
    double dx5 = (dx0 - 1) - (2 * 0.309016994374947);
    double dy5 = (dy0 - 1) - (2 * 0.309016994374947);
    double dz5 = (dz0 - 0) - (2 * 0.309016994374947);
    double dw5 = (dw0 - 0) - (2 * 0.309016994374947);
    double attn5 = (((2 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5)) - (dw5 * dw5);
    if (attn5 > 0)
    {
      attn5 *= attn5;
      value += (attn5 * attn5) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
    }
    double dx6 = (dx0 - 1) - (2 * 0.309016994374947);
    double dy6 = (dy0 - 0) - (2 * 0.309016994374947);
    double dz6 = (dz0 - 1) - (2 * 0.309016994374947);
    double dw6 = (dw0 - 0) - (2 * 0.309016994374947);
    double attn6 = (((2 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6)) - (dw6 * dw6);
    if (attn6 > 0)
    {
      attn6 *= attn6;
      value += (attn6 * attn6) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
    }
    double dx7 = (dx0 - 1) - (2 * 0.309016994374947);
    double dy7 = (dy0 - 0) - (2 * 0.309016994374947);
    double dz7 = (dz0 - 0) - (2 * 0.309016994374947);
    double dw7 = (dw0 - 1) - (2 * 0.309016994374947);
    double attn7 = (((2 - (dx7 * dx7)) - (dy7 * dy7)) - (dz7 * dz7)) - (dw7 * dw7);
    if (attn7 > 0)
    {
      attn7 *= attn7;
      value += (attn7 * attn7) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
    }
    double dx8 = (dx0 - 0) - (2 * 0.309016994374947);
    double dy8 = (dy0 - 1) - (2 * 0.309016994374947);
    double dz8 = (dz0 - 1) - (2 * 0.309016994374947);
    double dw8 = (dw0 - 0) - (2 * 0.309016994374947);
    double attn8 = (((2 - (dx8 * dx8)) - (dy8 * dy8)) - (dz8 * dz8)) - (dw8 * dw8);
    if (attn8 > 0)
    {
      attn8 *= attn8;
      value += (attn8 * attn8) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
    }
    double dx9 = (dx0 - 0) - (2 * 0.309016994374947);
    double dy9 = (dy0 - 1) - (2 * 0.309016994374947);
    double dz9 = (dz0 - 0) - (2 * 0.309016994374947);
    double dw9 = (dw0 - 1) - (2 * 0.309016994374947);
    double attn9 = (((2 - (dx9 * dx9)) - (dy9 * dy9)) - (dz9 * dz9)) - (dw9 * dw9);
    if (attn9 > 0)
    {
      attn9 *= attn9;
      value += (attn9 * attn9) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
    }
    double dx10 = (dx0 - 0) - (2 * 0.309016994374947);
    double dy10 = (dy0 - 0) - (2 * 0.309016994374947);
    double dz10 = (dz0 - 1) - (2 * 0.309016994374947);
    double dw10 = (dw0 - 1) - (2 * 0.309016994374947);
    double attn10 = (((2 - (dx10 * dx10)) - (dy10 * dy10)) - (dz10 * dz10)) - (dw10 * dw10);
    if (attn10 > 0)
    {
      attn10 *= attn10;
      value += (attn10 * attn10) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 1, dx10, dy10, dz10, dw10);
    }
  }
  double attn_ext0 = (((2 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0)) - (dw_ext0 * dw_ext0);
  if (attn_ext0 > 0)
  {
    attn_ext0 *= attn_ext0;
    value += (attn_ext0 * attn_ext0) * extrapolate4(ctx, xsv_ext0, ysv_ext0, zsv_ext0, wsv_ext0, dx_ext0, dy_ext0, dz_ext0, dw_ext0);
  }
  double attn_ext1 = (((2 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1)) - (dw_ext1 * dw_ext1);
  if (attn_ext1 > 0)
  {
    attn_ext1 *= attn_ext1;
    value += (attn_ext1 * attn_ext1) * extrapolate4(ctx, xsv_ext1, ysv_ext1, zsv_ext1, wsv_ext1, dx_ext1, dy_ext1, dz_ext1, dw_ext1);
  }
  double attn_ext2 = (((2 - (dx_ext2 * dx_ext2)) - (dy_ext2 * dy_ext2)) - (dz_ext2 * dz_ext2)) - (dw_ext2 * dw_ext2);
  if (attn_ext2 > 0)
  {
    attn_ext2 *= attn_ext2;
    value += (attn_ext2 * attn_ext2) * extrapolate4(ctx, xsv_ext2, ysv_ext2, zsv_ext2, wsv_ext2, dx_ext2, dy_ext2, dz_ext2, dw_ext2);
  }
  return value / 30.0;
}

void helper_open_simplex_noise2_1(double * const dx_ext_ref, double * const dy_ext_ref, int * const xsv_ext_ref, int * const ysv_ext_ref, int xsb, int ysb, double xins, double yins, double inSum, double dx0, double dy0)
{
  double dx_ext = *dx_ext_ref;
  double dy_ext = *dy_ext_ref;
  int xsv_ext = *xsv_ext_ref;
  int ysv_ext = *ysv_ext_ref;
  double zins = 1 - inSum;
  if ((zins > xins) || (zins > yins))
  {
    if (xins > yins)
    {
      xsv_ext = xsb + 1;
      ysv_ext = ysb - 1;
      dx_ext = dx0 - 1;
      dy_ext = dy0 + 1;
    }
    else
    {
      xsv_ext = xsb - 1;
      ysv_ext = ysb + 1;
      dx_ext = dx0 + 1;
      dy_ext = dy0 - 1;
    }
  }
  else
  {
    xsv_ext = xsb + 1;
    ysv_ext = ysb + 1;
    dx_ext = (dx0 - 1) - (2 * 0.366025403784439);
    dy_ext = (dy0 - 1) - (2 * 0.366025403784439);
  }
  *dx_ext_ref = dx_ext;
  *dy_ext_ref = dy_ext;
  *xsv_ext_ref = xsv_ext;
  *ysv_ext_ref = ysv_ext;
}

void helper_open_simplex_noise2_2(int * const xsb_ref, int * const ysb_ref, double * const dx0_ref, double * const dy0_ref, double * const dx_ext_ref, double * const dy_ext_ref, int * const xsv_ext_ref, int * const ysv_ext_ref, double xins, double yins, double inSum)
{
  int xsb = *xsb_ref;
  int ysb = *ysb_ref;
  double dx0 = *dx0_ref;
  double dy0 = *dy0_ref;
  double dx_ext = *dx_ext_ref;
  double dy_ext = *dy_ext_ref;
  int xsv_ext = *xsv_ext_ref;
  int ysv_ext = *ysv_ext_ref;
  double zins = 2 - inSum;
  if ((zins < xins) || (zins < yins))
  {
    if (xins > yins)
    {
      xsv_ext = xsb + 2;
      ysv_ext = ysb + 0;
      dx_ext = (dx0 - 2) - (2 * 0.366025403784439);
      dy_ext = (dy0 + 0) - (2 * 0.366025403784439);
    }
    else
    {
      xsv_ext = xsb + 0;
      ysv_ext = ysb + 2;
      dx_ext = (dx0 + 0) - (2 * 0.366025403784439);
      dy_ext = (dy0 - 2) - (2 * 0.366025403784439);
    }
  }
  else
  {
    dx_ext = dx0;
    dy_ext = dy0;
    xsv_ext = xsb;
    ysv_ext = ysb;
  }
  xsb += 1;
  ysb += 1;
  dx0 = (dx0 - 1) - (2 * 0.366025403784439);
  dy0 = (dy0 - 1) - (2 * 0.366025403784439);
  *xsb_ref = xsb;
  *ysb_ref = ysb;
  *dx0_ref = dx0;
  *dy0_ref = dy0;
  *dx_ext_ref = dx_ext;
  *dy_ext_ref = dy_ext;
  *xsv_ext_ref = xsv_ext;
  *ysv_ext_ref = ysv_ext;
}

void helper_open_simplex_noise3_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, double xins, double yins, double zins, double inSum, double dx0, double dy0, double dz0)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  double value = *value_ref;
  int8_t aPoint = 0x01;
  double aScore = xins;
  int8_t bPoint = 0x02;
  double bScore = yins;
  if ((aScore >= bScore) && (zins > bScore))
  {
    bScore = zins;
    bPoint = 0x04;
  }
  else
    if ((aScore < bScore) && (zins > aScore))
  {
    aScore = zins;
    aPoint = 0x04;
  }
  double wins = 1 - inSum;
  if ((wins > aScore) || (wins > bScore))
  {
    helper_helper_open_simplex_noise3_1_1(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, aScore, bPoint, bScore);
  }
  else
  {
    helper_helper_open_simplex_noise3_1_2(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, bPoint);
  }
  double attn0 = ((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 0, dx0, dy0, dz0);
  }
  double dx1 = (dx0 - 1) - (1.0 / 3.0);
  double dy1 = (dy0 - 0) - (1.0 / 3.0);
  double dz1 = (dz0 - 0) - (1.0 / 3.0);
  double attn1 = ((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
  }
  double dx2 = (dx0 - 0) - (1.0 / 3.0);
  double dy2 = (dy0 - 1) - (1.0 / 3.0);
  double dz2 = dz1;
  double attn2 = ((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
  }
  double dx3 = dx2;
  double dy3 = dy1;
  double dz3 = (dz0 - 1) - (1.0 / 3.0);
  double attn3 = ((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *value_ref = value;
}

void helper_open_simplex_noise3_2(double * const dx0_ref, double * const dy0_ref, double * const dz0_ref, double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, double xins, double yins, double zins, double inSum)
{
  double dx0 = *dx0_ref;
  double dy0 = *dy0_ref;
  double dz0 = *dz0_ref;
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  double value = *value_ref;
  int8_t aPoint = 0x06;
  double aScore = xins;
  int8_t bPoint = 0x05;
  double bScore = yins;
  if ((aScore <= bScore) && (zins < bScore))
  {
    bScore = zins;
    bPoint = 0x03;
  }
  else
    if ((aScore > bScore) && (zins < aScore))
  {
    aScore = zins;
    aPoint = 0x03;
  }
  double wins = 3 - inSum;
  if ((wins < aScore) || (wins < bScore))
  {
    helper_helper_open_simplex_noise3_2_1(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, aScore, bPoint, bScore);
  }
  else
  {
    helper_helper_open_simplex_noise3_2_2(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, bPoint);
  }
  double dx3 = (dx0 - 1) - (2 * (1.0 / 3.0));
  double dy3 = (dy0 - 1) - (2 * (1.0 / 3.0));
  double dz3 = (dz0 - 0) - (2 * (1.0 / 3.0));
  double attn3 = ((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 0, dx3, dy3, dz3);
  }
  double dx2 = dx3;
  double dy2 = (dy0 - 0) - (2 * (1.0 / 3.0));
  double dz2 = (dz0 - 1) - (2 * (1.0 / 3.0));
  double attn2 = ((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 1, dx2, dy2, dz2);
  }
  double dx1 = (dx0 - 0) - (2 * (1.0 / 3.0));
  double dy1 = dy3;
  double dz1 = dz2;
  double attn1 = ((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 1, dx1, dy1, dz1);
  }
  dx0 = (dx0 - 1) - (3 * (1.0 / 3.0));
  dy0 = (dy0 - 1) - (3 * (1.0 / 3.0));
  dz0 = (dz0 - 1) - (3 * (1.0 / 3.0));
  double attn0 = ((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 1, dx0, dy0, dz0);
  }
  *dx0_ref = dx0;
  *dy0_ref = dy0;
  *dz0_ref = dz0;
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *value_ref = value;
}

void helper_open_simplex_noise3_3(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, double xins, double yins, double zins, double dx0, double dy0, double dz0)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  double value = *value_ref;
  double aScore;
  int8_t aPoint;
  int aIsFurtherSide;
  double bScore;
  int8_t bPoint;
  int bIsFurtherSide;
  double p1 = xins + yins;
  if (p1 > 1)
  {
    aScore = p1 - 1;
    aPoint = 0x03;
    aIsFurtherSide = 1;
  }
  else
  {
    aScore = 1 - p1;
    aPoint = 0x04;
    aIsFurtherSide = 0;
  }
  double p2 = xins + zins;
  if (p2 > 1)
  {
    bScore = p2 - 1;
    bPoint = 0x05;
    bIsFurtherSide = 1;
  }
  else
  {
    bScore = 1 - p2;
    bPoint = 0x02;
    bIsFurtherSide = 0;
  }
  double p3 = yins + zins;
  if (p3 > 1)
  {
    double score = p3 - 1;
    if ((aScore <= bScore) && (aScore < score))
    {
      aScore = score;
      aPoint = 0x06;
      aIsFurtherSide = 1;
    }
    else
      if ((aScore > bScore) && (bScore < score))
    {
      bScore = score;
      bPoint = 0x06;
      bIsFurtherSide = 1;
    }
  }
  else
  {
    double score = 1 - p3;
    if ((aScore <= bScore) && (aScore < score))
    {
      aScore = score;
      aPoint = 0x01;
      aIsFurtherSide = 0;
    }
    else
      if ((aScore > bScore) && (bScore < score))
    {
      bScore = score;
      bPoint = 0x01;
      bIsFurtherSide = 0;
    }
  }
  if (aIsFurtherSide == bIsFurtherSide)
  {
    helper_helper_open_simplex_noise3_3_2(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, aIsFurtherSide, bPoint);
  }
  else
  {
    helper_helper_open_simplex_noise3_3_1(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, aIsFurtherSide, bPoint);
  }
  double dx1 = (dx0 - 1) - (1.0 / 3.0);
  double dy1 = (dy0 - 0) - (1.0 / 3.0);
  double dz1 = (dz0 - 0) - (1.0 / 3.0);
  double attn1 = ((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 0, dx1, dy1, dz1);
  }
  double dx2 = (dx0 - 0) - (1.0 / 3.0);
  double dy2 = (dy0 - 1) - (1.0 / 3.0);
  double dz2 = dz1;
  double attn2 = ((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 0, dx2, dy2, dz2);
  }
  double dx3 = dx2;
  double dy3 = dy1;
  double dz3 = (dz0 - 1) - (1.0 / 3.0);
  double attn3 = ((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate3(ctx, xsb + 0, ysb + 0, zsb + 1, dx3, dy3, dz3);
  }
  double dx4 = (dx0 - 1) - (2 * (1.0 / 3.0));
  double dy4 = (dy0 - 1) - (2 * (1.0 / 3.0));
  double dz4 = (dz0 - 0) - (2 * (1.0 / 3.0));
  double attn4 = ((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4);
  if (attn4 > 0)
  {
    attn4 *= attn4;
    value += (attn4 * attn4) * extrapolate3(ctx, xsb + 1, ysb + 1, zsb + 0, dx4, dy4, dz4);
  }
  double dx5 = dx4;
  double dy5 = (dy0 - 0) - (2 * (1.0 / 3.0));
  double dz5 = (dz0 - 1) - (2 * (1.0 / 3.0));
  double attn5 = ((2 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5);
  if (attn5 > 0)
  {
    attn5 *= attn5;
    value += (attn5 * attn5) * extrapolate3(ctx, xsb + 1, ysb + 0, zsb + 1, dx5, dy5, dz5);
  }
  double dx6 = (dx0 - 0) - (2 * (1.0 / 3.0));
  double dy6 = dy4;
  double dz6 = dz5;
  double attn6 = ((2 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6);
  if (attn6 > 0)
  {
    attn6 *= attn6;
    value += (attn6 * attn6) * extrapolate3(ctx, xsb + 0, ysb + 1, zsb + 1, dx6, dy6, dz6);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *value_ref = value;
}

void helper_open_simplex_noise4_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, int wsb, double xins, double yins, double zins, double wins, double inSum, double dx0, double dy0, double dz0, double dw0, int wsv_ext1, int xsv_ext2)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  double value = *value_ref;
  int8_t aPoint = 0x01;
  double aScore = xins;
  int8_t bPoint = 0x02;
  double bScore = yins;
  if ((aScore >= bScore) && (zins > bScore))
  {
    bScore = zins;
    bPoint = 0x04;
  }
  else
    if ((aScore < bScore) && (zins > aScore))
  {
    aScore = zins;
    aPoint = 0x04;
  }
  if ((aScore >= bScore) && (wins > bScore))
  {
    bScore = wins;
    bPoint = 0x08;
  }
  else
    if ((aScore < bScore) && (wins > aScore))
  {
    aScore = wins;
    aPoint = 0x08;
  }
  double uins = 1 - inSum;
  if ((uins > aScore) || (uins > bScore))
  {
    helper_helper_open_simplex_noise4_1_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, wsv_ext1, xsv_ext2, dw_ext1, dx_ext2, dy_ext2, ysv_ext2, aPoint, aScore, bPoint, bScore);
  }
  else
  {
    helper_helper_open_simplex_noise4_1_2(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, wsv_ext1, xsv_ext2, aPoint, bPoint);
  }
  double attn0 = (((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0)) - (dw0 * dw0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 0, dx0, dy0, dz0, dw0);
  }
  double dx1 = (dx0 - 1) - 0.309016994374947;
  double dy1 = (dy0 - 0) - 0.309016994374947;
  double dz1 = (dz0 - 0) - 0.309016994374947;
  double dw1 = (dw0 - 0) - 0.309016994374947;
  double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
  }
  double dx2 = (dx0 - 0) - 0.309016994374947;
  double dy2 = (dy0 - 1) - 0.309016994374947;
  double dz2 = dz1;
  double dw2 = dw1;
  double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
  }
  double dx3 = dx2;
  double dy3 = dy1;
  double dz3 = (dz0 - 1) - 0.309016994374947;
  double dw3 = dw1;
  double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
  }
  double dx4 = dx2;
  double dy4 = dy1;
  double dz4 = dz1;
  double dw4 = (dw0 - 1) - 0.309016994374947;
  double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
  if (attn4 > 0)
  {
    attn4 *= attn4;
    value += (attn4 * attn4) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
  *value_ref = value;
}

void helper_open_simplex_noise4_2(double * const dx0_ref, double * const dy0_ref, double * const dz0_ref, double * const dw0_ref, double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, int wsb, double xins, double yins, double zins, double wins, double inSum, int wsv_ext1, int xsv_ext2)
{
  double dx0 = *dx0_ref;
  double dy0 = *dy0_ref;
  double dz0 = *dz0_ref;
  double dw0 = *dw0_ref;
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  double value = *value_ref;
  int8_t aPoint = 0x0E;
  double aScore = xins;
  int8_t bPoint = 0x0D;
  double bScore = yins;
  if ((aScore <= bScore) && (zins < bScore))
  {
    bScore = zins;
    bPoint = 0x0B;
  }
  else
    if ((aScore > bScore) && (zins < aScore))
  {
    aScore = zins;
    aPoint = 0x0B;
  }
  if ((aScore <= bScore) && (wins < bScore))
  {
    bScore = wins;
    bPoint = 0x07;
  }
  else
    if ((aScore > bScore) && (wins < aScore))
  {
    aScore = wins;
    aPoint = 0x07;
  }
  double uins = 4 - inSum;
  if ((uins < aScore) || (uins < bScore))
  {
    helper_helper_open_simplex_noise4_2_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, wsv_ext1, xsv_ext2, dx0, dy0, dz0, dw0, dw_ext1, dx_ext2, dy_ext2, ysv_ext2, aPoint, aScore, bPoint, bScore);
  }
  else
  {
    helper_helper_open_simplex_noise4_2_2(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, wsv_ext1, xsv_ext2, dx0, dy0, dz0, dw0, aPoint, bPoint);
  }
  double dx4 = (dx0 - 1) - (3 * 0.309016994374947);
  double dy4 = (dy0 - 1) - (3 * 0.309016994374947);
  double dz4 = (dz0 - 1) - (3 * 0.309016994374947);
  double dw4 = dw0 - (3 * 0.309016994374947);
  double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
  if (attn4 > 0)
  {
    attn4 *= attn4;
    value += (attn4 * attn4) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
  }
  double dx3 = dx4;
  double dy3 = dy4;
  double dz3 = dz0 - (3 * 0.309016994374947);
  double dw3 = (dw0 - 1) - (3 * 0.309016994374947);
  double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
  }
  double dx2 = dx4;
  double dy2 = dy0 - (3 * 0.309016994374947);
  double dz2 = dz4;
  double dw2 = dw3;
  double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
  }
  double dx1 = dx0 - (3 * 0.309016994374947);
  double dz1 = dz4;
  double dy1 = dy4;
  double dw1 = dw3;
  double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
  }
  dx0 = (dx0 - 1) - (4 * 0.309016994374947);
  dy0 = (dy0 - 1) - (4 * 0.309016994374947);
  dz0 = (dz0 - 1) - (4 * 0.309016994374947);
  dw0 = (dw0 - 1) - (4 * 0.309016994374947);
  double attn0 = (((2 - (dx0 * dx0)) - (dy0 * dy0)) - (dz0 * dz0)) - (dw0 * dw0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 1, dx0, dy0, dz0, dw0);
  }
  *dx0_ref = dx0;
  *dy0_ref = dy0;
  *dz0_ref = dz0;
  *dw0_ref = dw0;
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
  *value_ref = value;
}

void helper_open_simplex_noise4_3(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, int wsb, double xins, double yins, double zins, double wins, double inSum, double dx0, double dy0, double dz0, double dw0)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  double value = *value_ref;
  double aScore;
  int8_t aPoint;
  int aIsBiggerSide = 1;
  double bScore;
  int8_t bPoint;
  int bIsBiggerSide = 1;
  if ((xins + yins) < (zins + wins))
  {
    aScore = xins + yins;
    aPoint = 0x0C;
  }
  else
  {
    aScore = zins + wins;
    aPoint = 0x03;
  }
  if ((xins + zins) < (yins + wins))
  {
    bScore = xins + zins;
    bPoint = 0x0A;
  }
  else
  {
    bScore = yins + wins;
    bPoint = 0x05;
  }
  if ((xins + wins) < (yins + zins))
  {
    double score = xins + wins;
    if ((aScore <= bScore) && (score < bScore))
    {
      bScore = score;
      bPoint = 0x06;
    }
    else
      if ((aScore > bScore) && (score < aScore))
    {
      aScore = score;
      aPoint = 0x06;
    }
  }
  else
  {
    double score = yins + zins;
    if ((aScore <= bScore) && (score < bScore))
    {
      bScore = score;
      bPoint = 0x09;
    }
    else
      if ((aScore > bScore) && (score < aScore))
    {
      aScore = score;
      aPoint = 0x09;
    }
  }
  double p1 = (3 - inSum) + xins;
  if ((aScore <= bScore) && (p1 < bScore))
  {
    bScore = p1;
    bPoint = 0x0E;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore > bScore) && (p1 < aScore))
  {
    aScore = p1;
    aPoint = 0x0E;
    aIsBiggerSide = 0;
  }
  double p2 = (3 - inSum) + yins;
  if ((aScore <= bScore) && (p2 < bScore))
  {
    bScore = p2;
    bPoint = 0x0D;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore > bScore) && (p2 < aScore))
  {
    aScore = p2;
    aPoint = 0x0D;
    aIsBiggerSide = 0;
  }
  double p3 = (3 - inSum) + zins;
  if ((aScore <= bScore) && (p3 < bScore))
  {
    bScore = p3;
    bPoint = 0x0B;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore > bScore) && (p3 < aScore))
  {
    aScore = p3;
    aPoint = 0x0B;
    aIsBiggerSide = 0;
  }
  double p4 = (3 - inSum) + wins;
  if ((aScore <= bScore) && (p4 < bScore))
  {
    bScore = p4;
    bPoint = 0x07;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore > bScore) && (p4 < aScore))
  {
    aScore = p4;
    aPoint = 0x07;
    aIsBiggerSide = 0;
  }
  if (aIsBiggerSide == bIsBiggerSide)
  {
    helper_helper_open_simplex_noise4_3_2(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, aIsBiggerSide, bPoint);
  }
  else
  {
    helper_helper_open_simplex_noise4_3_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, aIsBiggerSide, bPoint);
  }
  double dx4 = (dx0 - 1) - (3 * 0.309016994374947);
  double dy4 = (dy0 - 1) - (3 * 0.309016994374947);
  double dz4 = (dz0 - 1) - (3 * 0.309016994374947);
  double dw4 = dw0 - (3 * 0.309016994374947);
  double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
  if (attn4 > 0)
  {
    attn4 *= attn4;
    value += (attn4 * attn4) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
  }
  double dx3 = dx4;
  double dy3 = dy4;
  double dz3 = dz0 - (3 * 0.309016994374947);
  double dw3 = (dw0 - 1) - (3 * 0.309016994374947);
  double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
  }
  double dx2 = dx4;
  double dy2 = dy0 - (3 * 0.309016994374947);
  double dz2 = dz4;
  double dw2 = dw3;
  double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
  }
  double dx1 = dx0 - (3 * 0.309016994374947);
  double dz1 = dz4;
  double dy1 = dy4;
  double dw1 = dw3;
  double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
  }
  double dx5 = (dx0 - 1) - (2 * 0.309016994374947);
  double dy5 = (dy0 - 1) - (2 * 0.309016994374947);
  double dz5 = (dz0 - 0) - (2 * 0.309016994374947);
  double dw5 = (dw0 - 0) - (2 * 0.309016994374947);
  double attn5 = (((2 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5)) - (dw5 * dw5);
  if (attn5 > 0)
  {
    attn5 *= attn5;
    value += (attn5 * attn5) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
  }
  double dx6 = (dx0 - 1) - (2 * 0.309016994374947);
  double dy6 = (dy0 - 0) - (2 * 0.309016994374947);
  double dz6 = (dz0 - 1) - (2 * 0.309016994374947);
  double dw6 = (dw0 - 0) - (2 * 0.309016994374947);
  double attn6 = (((2 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6)) - (dw6 * dw6);
  if (attn6 > 0)
  {
    attn6 *= attn6;
    value += (attn6 * attn6) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
  }
  double dx7 = (dx0 - 1) - (2 * 0.309016994374947);
  double dy7 = (dy0 - 0) - (2 * 0.309016994374947);
  double dz7 = (dz0 - 0) - (2 * 0.309016994374947);
  double dw7 = (dw0 - 1) - (2 * 0.309016994374947);
  double attn7 = (((2 - (dx7 * dx7)) - (dy7 * dy7)) - (dz7 * dz7)) - (dw7 * dw7);
  if (attn7 > 0)
  {
    attn7 *= attn7;
    value += (attn7 * attn7) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
  }
  double dx8 = (dx0 - 0) - (2 * 0.309016994374947);
  double dy8 = (dy0 - 1) - (2 * 0.309016994374947);
  double dz8 = (dz0 - 1) - (2 * 0.309016994374947);
  double dw8 = (dw0 - 0) - (2 * 0.309016994374947);
  double attn8 = (((2 - (dx8 * dx8)) - (dy8 * dy8)) - (dz8 * dz8)) - (dw8 * dw8);
  if (attn8 > 0)
  {
    attn8 *= attn8;
    value += (attn8 * attn8) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
  }
  double dx9 = (dx0 - 0) - (2 * 0.309016994374947);
  double dy9 = (dy0 - 1) - (2 * 0.309016994374947);
  double dz9 = (dz0 - 0) - (2 * 0.309016994374947);
  double dw9 = (dw0 - 1) - (2 * 0.309016994374947);
  double attn9 = (((2 - (dx9 * dx9)) - (dy9 * dy9)) - (dz9 * dz9)) - (dw9 * dw9);
  if (attn9 > 0)
  {
    attn9 *= attn9;
    value += (attn9 * attn9) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
  }
  double dx10 = (dx0 - 0) - (2 * 0.309016994374947);
  double dy10 = (dy0 - 0) - (2 * 0.309016994374947);
  double dz10 = (dz0 - 1) - (2 * 0.309016994374947);
  double dw10 = (dw0 - 1) - (2 * 0.309016994374947);
  double attn10 = (((2 - (dx10 * dx10)) - (dy10 * dy10)) - (dz10 * dz10)) - (dw10 * dw10);
  if (attn10 > 0)
  {
    attn10 *= attn10;
    value += (attn10 * attn10) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 1, dx10, dy10, dz10, dw10);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
  *value_ref = value;
}

void helper_open_simplex_noise4_4(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, double * const value_ref, struct osn_context * const ctx, int xsb, int ysb, int zsb, int wsb, double xins, double yins, double zins, double wins, double inSum, double dx0, double dy0, double dz0, double dw0)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  double value = *value_ref;
  double aScore;
  int8_t aPoint;
  int aIsBiggerSide = 1;
  double bScore;
  int8_t bPoint;
  int bIsBiggerSide = 1;
  if ((xins + yins) > (zins + wins))
  {
    aScore = xins + yins;
    aPoint = 0x03;
  }
  else
  {
    aScore = zins + wins;
    aPoint = 0x0C;
  }
  if ((xins + zins) > (yins + wins))
  {
    bScore = xins + zins;
    bPoint = 0x05;
  }
  else
  {
    bScore = yins + wins;
    bPoint = 0x0A;
  }
  if ((xins + wins) > (yins + zins))
  {
    double score = xins + wins;
    if ((aScore >= bScore) && (score > bScore))
    {
      bScore = score;
      bPoint = 0x09;
    }
    else
      if ((aScore < bScore) && (score > aScore))
    {
      aScore = score;
      aPoint = 0x09;
    }
  }
  else
  {
    double score = yins + zins;
    if ((aScore >= bScore) && (score > bScore))
    {
      bScore = score;
      bPoint = 0x06;
    }
    else
      if ((aScore < bScore) && (score > aScore))
    {
      aScore = score;
      aPoint = 0x06;
    }
  }
  double p1 = (2 - inSum) + xins;
  if ((aScore >= bScore) && (p1 > bScore))
  {
    bScore = p1;
    bPoint = 0x01;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore < bScore) && (p1 > aScore))
  {
    aScore = p1;
    aPoint = 0x01;
    aIsBiggerSide = 0;
  }
  double p2 = (2 - inSum) + yins;
  if ((aScore >= bScore) && (p2 > bScore))
  {
    bScore = p2;
    bPoint = 0x02;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore < bScore) && (p2 > aScore))
  {
    aScore = p2;
    aPoint = 0x02;
    aIsBiggerSide = 0;
  }
  double p3 = (2 - inSum) + zins;
  if ((aScore >= bScore) && (p3 > bScore))
  {
    bScore = p3;
    bPoint = 0x04;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore < bScore) && (p3 > aScore))
  {
    aScore = p3;
    aPoint = 0x04;
    aIsBiggerSide = 0;
  }
  double p4 = (2 - inSum) + wins;
  if ((aScore >= bScore) && (p4 > bScore))
  {
    bScore = p4;
    bPoint = 0x08;
    bIsBiggerSide = 0;
  }
  else
    if ((aScore < bScore) && (p4 > aScore))
  {
    aScore = p4;
    aPoint = 0x08;
    aIsBiggerSide = 0;
  }
  if (aIsBiggerSide == bIsBiggerSide)
  {
    helper_helper_open_simplex_noise4_4_2(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, aIsBiggerSide, bPoint);
  }
  else
  {
    helper_helper_open_simplex_noise4_4_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, aIsBiggerSide, bPoint);
  }
  double dx1 = (dx0 - 1) - 0.309016994374947;
  double dy1 = (dy0 - 0) - 0.309016994374947;
  double dz1 = (dz0 - 0) - 0.309016994374947;
  double dw1 = (dw0 - 0) - 0.309016994374947;
  double attn1 = (((2 - (dx1 * dx1)) - (dy1 * dy1)) - (dz1 * dz1)) - (dw1 * dw1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
  }
  double dx2 = (dx0 - 0) - 0.309016994374947;
  double dy2 = (dy0 - 1) - 0.309016994374947;
  double dz2 = dz1;
  double dw2 = dw1;
  double attn2 = (((2 - (dx2 * dx2)) - (dy2 * dy2)) - (dz2 * dz2)) - (dw2 * dw2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
  }
  double dx3 = dx2;
  double dy3 = dy1;
  double dz3 = (dz0 - 1) - 0.309016994374947;
  double dw3 = dw1;
  double attn3 = (((2 - (dx3 * dx3)) - (dy3 * dy3)) - (dz3 * dz3)) - (dw3 * dw3);
  if (attn3 > 0)
  {
    attn3 *= attn3;
    value += (attn3 * attn3) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
  }
  double dx4 = dx2;
  double dy4 = dy1;
  double dz4 = dz1;
  double dw4 = (dw0 - 1) - 0.309016994374947;
  double attn4 = (((2 - (dx4 * dx4)) - (dy4 * dy4)) - (dz4 * dz4)) - (dw4 * dw4);
  if (attn4 > 0)
  {
    attn4 *= attn4;
    value += (attn4 * attn4) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
  }
  double dx5 = (dx0 - 1) - (2 * 0.309016994374947);
  double dy5 = (dy0 - 1) - (2 * 0.309016994374947);
  double dz5 = (dz0 - 0) - (2 * 0.309016994374947);
  double dw5 = (dw0 - 0) - (2 * 0.309016994374947);
  double attn5 = (((2 - (dx5 * dx5)) - (dy5 * dy5)) - (dz5 * dz5)) - (dw5 * dw5);
  if (attn5 > 0)
  {
    attn5 *= attn5;
    value += (attn5 * attn5) * extrapolate4(ctx, xsb + 1, ysb + 1, zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
  }
  double dx6 = (dx0 - 1) - (2 * 0.309016994374947);
  double dy6 = (dy0 - 0) - (2 * 0.309016994374947);
  double dz6 = (dz0 - 1) - (2 * 0.309016994374947);
  double dw6 = (dw0 - 0) - (2 * 0.309016994374947);
  double attn6 = (((2 - (dx6 * dx6)) - (dy6 * dy6)) - (dz6 * dz6)) - (dw6 * dw6);
  if (attn6 > 0)
  {
    attn6 *= attn6;
    value += (attn6 * attn6) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
  }
  double dx7 = (dx0 - 1) - (2 * 0.309016994374947);
  double dy7 = (dy0 - 0) - (2 * 0.309016994374947);
  double dz7 = (dz0 - 0) - (2 * 0.309016994374947);
  double dw7 = (dw0 - 1) - (2 * 0.309016994374947);
  double attn7 = (((2 - (dx7 * dx7)) - (dy7 * dy7)) - (dz7 * dz7)) - (dw7 * dw7);
  if (attn7 > 0)
  {
    attn7 *= attn7;
    value += (attn7 * attn7) * extrapolate4(ctx, xsb + 1, ysb + 0, zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
  }
  double dx8 = (dx0 - 0) - (2 * 0.309016994374947);
  double dy8 = (dy0 - 1) - (2 * 0.309016994374947);
  double dz8 = (dz0 - 1) - (2 * 0.309016994374947);
  double dw8 = (dw0 - 0) - (2 * 0.309016994374947);
  double attn8 = (((2 - (dx8 * dx8)) - (dy8 * dy8)) - (dz8 * dz8)) - (dw8 * dw8);
  if (attn8 > 0)
  {
    attn8 *= attn8;
    value += (attn8 * attn8) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
  }
  double dx9 = (dx0 - 0) - (2 * 0.309016994374947);
  double dy9 = (dy0 - 1) - (2 * 0.309016994374947);
  double dz9 = (dz0 - 0) - (2 * 0.309016994374947);
  double dw9 = (dw0 - 1) - (2 * 0.309016994374947);
  double attn9 = (((2 - (dx9 * dx9)) - (dy9 * dy9)) - (dz9 * dz9)) - (dw9 * dw9);
  if (attn9 > 0)
  {
    attn9 *= attn9;
    value += (attn9 * attn9) * extrapolate4(ctx, xsb + 0, ysb + 1, zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
  }
  double dx10 = (dx0 - 0) - (2 * 0.309016994374947);
  double dy10 = (dy0 - 0) - (2 * 0.309016994374947);
  double dz10 = (dz0 - 1) - (2 * 0.309016994374947);
  double dw10 = (dw0 - 1) - (2 * 0.309016994374947);
  double attn10 = (((2 - (dx10 * dx10)) - (dy10 * dy10)) - (dz10 * dz10)) - (dw10 * dw10);
  if (attn10 > 0)
  {
    attn10 *= attn10;
    value += (attn10 * attn10) * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1, wsb + 1, dx10, dy10, dz10, dw10);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
  *value_ref = value;
}

void helper_helper_open_simplex_noise3_1_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, double aScore, int8_t bPoint, double bScore)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int8_t c = (bScore > aScore) ? (bPoint) : (aPoint);
  if ((c & 0x01) == 0)
  {
    xsv_ext0 = xsb - 1;
    xsv_ext1 = xsb;
    dx_ext0 = dx0 + 1;
    dx_ext1 = dx0;
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb + 1);
    dx_ext0 = (dx_ext1 = dx0 - 1);
  }
  if ((c & 0x02) == 0)
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = (dy_ext1 = dy0);
    if ((c & 0x01) == 0)
    {
      ysv_ext1 -= 1;
      dy_ext1 += 1;
    }
    else
    {
      ysv_ext0 -= 1;
      dy_ext0 += 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy_ext1 = dy0 - 1);
  }
  if ((c & 0x04) == 0)
  {
    zsv_ext0 = zsb;
    zsv_ext1 = zsb - 1;
    dz_ext0 = dz0;
    dz_ext1 = dz0 + 1;
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz_ext1 = dz0 - 1);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_open_simplex_noise3_1_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int8_t c = (int8_t) (aPoint | bPoint);
  if ((c & 0x01) == 0)
  {
    xsv_ext0 = xsb;
    xsv_ext1 = xsb - 1;
    dx_ext0 = dx0 - (2 * (1.0 / 3.0));
    dx_ext1 = (dx0 + 1) - (1.0 / 3.0);
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb + 1);
    dx_ext0 = (dx0 - 1) - (2 * (1.0 / 3.0));
    dx_ext1 = (dx0 - 1) - (1.0 / 3.0);
  }
  if ((c & 0x02) == 0)
  {
    ysv_ext0 = ysb;
    ysv_ext1 = ysb - 1;
    dy_ext0 = dy0 - (2 * (1.0 / 3.0));
    dy_ext1 = (dy0 + 1) - (1.0 / 3.0);
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy0 - 1) - (2 * (1.0 / 3.0));
    dy_ext1 = (dy0 - 1) - (1.0 / 3.0);
  }
  if ((c & 0x04) == 0)
  {
    zsv_ext0 = zsb;
    zsv_ext1 = zsb - 1;
    dz_ext0 = dz0 - (2 * (1.0 / 3.0));
    dz_ext1 = (dz0 + 1) - (1.0 / 3.0);
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz0 - 1) - (2 * (1.0 / 3.0));
    dz_ext1 = (dz0 - 1) - (1.0 / 3.0);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_open_simplex_noise3_2_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, double aScore, int8_t bPoint, double bScore)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int8_t c = (bScore < aScore) ? (bPoint) : (aPoint);
  if ((c & 0x01) != 0)
  {
    xsv_ext0 = xsb + 2;
    xsv_ext1 = xsb + 1;
    dx_ext0 = (dx0 - 2) - (3 * (1.0 / 3.0));
    dx_ext1 = (dx0 - 1) - (3 * (1.0 / 3.0));
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb);
    dx_ext0 = (dx_ext1 = dx0 - (3 * (1.0 / 3.0)));
  }
  if ((c & 0x02) != 0)
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy_ext1 = (dy0 - 1) - (3 * (1.0 / 3.0)));
    if ((c & 0x01) != 0)
    {
      ysv_ext1 += 1;
      dy_ext1 -= 1;
    }
    else
    {
      ysv_ext0 += 1;
      dy_ext0 -= 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = (dy_ext1 = dy0 - (3 * (1.0 / 3.0)));
  }
  if ((c & 0x04) != 0)
  {
    zsv_ext0 = zsb + 1;
    zsv_ext1 = zsb + 2;
    dz_ext0 = (dz0 - 1) - (3 * (1.0 / 3.0));
    dz_ext1 = (dz0 - 2) - (3 * (1.0 / 3.0));
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb);
    dz_ext0 = (dz_ext1 = dz0 - (3 * (1.0 / 3.0)));
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_open_simplex_noise3_2_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int8_t c = (int8_t) (aPoint & bPoint);
  if ((c & 0x01) != 0)
  {
    xsv_ext0 = xsb + 1;
    xsv_ext1 = xsb + 2;
    dx_ext0 = (dx0 - 1) - (1.0 / 3.0);
    dx_ext1 = (dx0 - 2) - (2 * (1.0 / 3.0));
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb);
    dx_ext0 = dx0 - (1.0 / 3.0);
    dx_ext1 = dx0 - (2 * (1.0 / 3.0));
  }
  if ((c & 0x02) != 0)
  {
    ysv_ext0 = ysb + 1;
    ysv_ext1 = ysb + 2;
    dy_ext0 = (dy0 - 1) - (1.0 / 3.0);
    dy_ext1 = (dy0 - 2) - (2 * (1.0 / 3.0));
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = dy0 - (1.0 / 3.0);
    dy_ext1 = dy0 - (2 * (1.0 / 3.0));
  }
  if ((c & 0x04) != 0)
  {
    zsv_ext0 = zsb + 1;
    zsv_ext1 = zsb + 2;
    dz_ext0 = (dz0 - 1) - (1.0 / 3.0);
    dz_ext1 = (dz0 - 2) - (2 * (1.0 / 3.0));
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb);
    dz_ext0 = dz0 - (1.0 / 3.0);
    dz_ext1 = dz0 - (2 * (1.0 / 3.0));
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_open_simplex_noise3_3_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, int aIsFurtherSide, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int8_t c1;
  int8_t c2;
  if (aIsFurtherSide)
  {
    c1 = aPoint;
    c2 = bPoint;
  }
  else
  {
    c1 = bPoint;
    c2 = aPoint;
  }
  if ((c1 & 0x01) == 0)
  {
    dx_ext0 = (dx0 + 1) - (1.0 / 3.0);
    dy_ext0 = (dy0 - 1) - (1.0 / 3.0);
    dz_ext0 = (dz0 - 1) - (1.0 / 3.0);
    xsv_ext0 = xsb - 1;
    ysv_ext0 = ysb + 1;
    zsv_ext0 = zsb + 1;
  }
  else
    if ((c1 & 0x02) == 0)
  {
    dx_ext0 = (dx0 - 1) - (1.0 / 3.0);
    dy_ext0 = (dy0 + 1) - (1.0 / 3.0);
    dz_ext0 = (dz0 - 1) - (1.0 / 3.0);
    xsv_ext0 = xsb + 1;
    ysv_ext0 = ysb - 1;
    zsv_ext0 = zsb + 1;
  }
  else
  {
    dx_ext0 = (dx0 - 1) - (1.0 / 3.0);
    dy_ext0 = (dy0 - 1) - (1.0 / 3.0);
    dz_ext0 = (dz0 + 1) - (1.0 / 3.0);
    xsv_ext0 = xsb + 1;
    ysv_ext0 = ysb + 1;
    zsv_ext0 = zsb - 1;
  }
  dx_ext1 = dx0 - (2 * (1.0 / 3.0));
  dy_ext1 = dy0 - (2 * (1.0 / 3.0));
  dz_ext1 = dz0 - (2 * (1.0 / 3.0));
  xsv_ext1 = xsb;
  ysv_ext1 = ysb;
  zsv_ext1 = zsb;
  if ((c2 & 0x01) != 0)
  {
    dx_ext1 -= 2;
    xsv_ext1 += 2;
  }
  else
    if ((c2 & 0x02) != 0)
  {
    dy_ext1 -= 2;
    ysv_ext1 += 2;
  }
  else
  {
    dz_ext1 -= 2;
    zsv_ext1 += 2;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_open_simplex_noise3_3_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, int aIsFurtherSide, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  if (aIsFurtherSide)
  {
    helper_helper_helper_open_simplex_noise3_3_2_1(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, bPoint);
  }
  else
  {
    helper_helper_helper_open_simplex_noise3_3_2_2(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, xsb, ysb, zsb, dx0, dy0, dz0, aPoint, bPoint);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_open_simplex_noise4_1_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int wsv_ext1, int xsv_ext2, double dw_ext1, double dx_ext2, double dy_ext2, int ysv_ext2, int8_t aPoint, double aScore, int8_t bPoint, double bScore)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c = (bScore > aScore) ? (bPoint) : (aPoint);
  if ((c & 0x01) == 0)
  {
    xsv_ext0 = xsb - 1;
    xsv_ext1 = (xsv_ext2 = xsb);
    dx_ext0 = dx0 + 1;
    dx_ext1 = (dx_ext2 = dx0);
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb + 1));
    dx_ext0 = (dx_ext1 = (dx_ext2 = dx0 - 1));
  }
  if ((c & 0x02) == 0)
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
    dy_ext0 = (dy_ext1 = (dy_ext2 = dy0));
    if ((c & 0x01) == 0x01)
    {
      ysv_ext0 -= 1;
      dy_ext0 += 1;
    }
    else
    {
      ysv_ext1 -= 1;
      dy_ext1 += 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
    dy_ext0 = (dy_ext1 = (dy_ext2 = dy0 - 1));
  }
  if ((c & 0x04) == 0)
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
    dz_ext0 = (dz_ext1 = (dz_ext2 = dz0));
    if ((c & 0x03) != 0)
    {
      if ((c & 0x03) == 0x03)
      {
        zsv_ext0 -= 1;
        dz_ext0 += 1;
      }
      else
      {
        zsv_ext1 -= 1;
        dz_ext1 += 1;
      }
    }
    else
    {
      zsv_ext2 -= 1;
      dz_ext2 += 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
    dz_ext0 = (dz_ext1 = (dz_ext2 = dz0 - 1));
  }
  if ((c & 0x08) == 0)
  {
    wsv_ext0 = (wsv_ext1 = wsb);
    wsv_ext2 = wsb - 1;
    dw_ext0 = (dw_ext1 = dw0);
    dw_ext2 = dw0 + 1;
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb + 1));
    dw_ext0 = (dw_ext1 = (dw_ext2 = dw0 - 1));
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_1_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int wsv_ext1, int xsv_ext2, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c = (int8_t) (aPoint | bPoint);
  if ((c & 0x01) == 0)
  {
    xsv_ext0 = (xsv_ext2 = xsb);
    xsv_ext1 = xsb - 1;
    dx_ext0 = dx0 - (2 * 0.309016994374947);
    dx_ext1 = (dx0 + 1) - 0.309016994374947;
    dx_ext2 = dx0 - 0.309016994374947;
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb + 1));
    dx_ext0 = (dx0 - 1) - (2 * 0.309016994374947);
    dx_ext1 = (dx_ext2 = (dx0 - 1) - 0.309016994374947);
  }
  if ((c & 0x02) == 0)
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
    dy_ext0 = dy0 - (2 * 0.309016994374947);
    dy_ext1 = (dy_ext2 = dy0 - 0.309016994374947);
    if ((c & 0x01) == 0x01)
    {
      ysv_ext1 -= 1;
      dy_ext1 += 1;
    }
    else
    {
      ysv_ext2 -= 1;
      dy_ext2 += 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
    dy_ext0 = (dy0 - 1) - (2 * 0.309016994374947);
    dy_ext1 = (dy_ext2 = (dy0 - 1) - 0.309016994374947);
  }
  if ((c & 0x04) == 0)
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
    dz_ext0 = dz0 - (2 * 0.309016994374947);
    dz_ext1 = (dz_ext2 = dz0 - 0.309016994374947);
    if ((c & 0x03) == 0x03)
    {
      zsv_ext1 -= 1;
      dz_ext1 += 1;
    }
    else
    {
      zsv_ext2 -= 1;
      dz_ext2 += 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
    dz_ext0 = (dz0 - 1) - (2 * 0.309016994374947);
    dz_ext1 = (dz_ext2 = (dz0 - 1) - 0.309016994374947);
  }
  if ((c & 0x08) == 0)
  {
    wsv_ext0 = (wsv_ext1 = wsb);
    wsv_ext2 = wsb - 1;
    dw_ext0 = dw0 - (2 * 0.309016994374947);
    dw_ext1 = dw0 - 0.309016994374947;
    dw_ext2 = (dw0 + 1) - 0.309016994374947;
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb + 1));
    dw_ext0 = (dw0 - 1) - (2 * 0.309016994374947);
    dw_ext1 = (dw_ext2 = (dw0 - 1) - 0.309016994374947);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_2_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, int wsv_ext1, int xsv_ext2, double dx0, double dy0, double dz0, double dw0, double dw_ext1, double dx_ext2, double dy_ext2, int ysv_ext2, int8_t aPoint, double aScore, int8_t bPoint, double bScore)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c = (bScore < aScore) ? (bPoint) : (aPoint);
  if ((c & 0x01) != 0)
  {
    xsv_ext0 = xsb + 2;
    xsv_ext1 = (xsv_ext2 = xsb + 1);
    dx_ext0 = (dx0 - 2) - (4 * 0.309016994374947);
    dx_ext1 = (dx_ext2 = (dx0 - 1) - (4 * 0.309016994374947));
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb));
    dx_ext0 = (dx_ext1 = (dx_ext2 = dx0 - (4 * 0.309016994374947)));
  }
  if ((c & 0x02) != 0)
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
    dy_ext0 = (dy_ext1 = (dy_ext2 = (dy0 - 1) - (4 * 0.309016994374947)));
    if ((c & 0x01) != 0)
    {
      ysv_ext1 += 1;
      dy_ext1 -= 1;
    }
    else
    {
      ysv_ext0 += 1;
      dy_ext0 -= 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
    dy_ext0 = (dy_ext1 = (dy_ext2 = dy0 - (4 * 0.309016994374947)));
  }
  if ((c & 0x04) != 0)
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
    dz_ext0 = (dz_ext1 = (dz_ext2 = (dz0 - 1) - (4 * 0.309016994374947)));
    if ((c & 0x03) != 0x03)
    {
      if ((c & 0x03) == 0)
      {
        zsv_ext0 += 1;
        dz_ext0 -= 1;
      }
      else
      {
        zsv_ext1 += 1;
        dz_ext1 -= 1;
      }
    }
    else
    {
      zsv_ext2 += 1;
      dz_ext2 -= 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
    dz_ext0 = (dz_ext1 = (dz_ext2 = dz0 - (4 * 0.309016994374947)));
  }
  if ((c & 0x08) != 0)
  {
    wsv_ext0 = (wsv_ext1 = wsb + 1);
    wsv_ext2 = wsb + 2;
    dw_ext0 = (dw_ext1 = (dw0 - 1) - (4 * 0.309016994374947));
    dw_ext2 = (dw0 - 2) - (4 * 0.309016994374947);
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb));
    dw_ext0 = (dw_ext1 = (dw_ext2 = dw0 - (4 * 0.309016994374947)));
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_2_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, int wsv_ext1, int xsv_ext2, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c = (int8_t) (aPoint & bPoint);
  if ((c & 0x01) != 0)
  {
    xsv_ext0 = (xsv_ext2 = xsb + 1);
    xsv_ext1 = xsb + 2;
    dx_ext0 = (dx0 - 1) - (2 * 0.309016994374947);
    dx_ext1 = (dx0 - 2) - (3 * 0.309016994374947);
    dx_ext2 = (dx0 - 1) - (3 * 0.309016994374947);
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = (xsv_ext2 = xsb));
    dx_ext0 = dx0 - (2 * 0.309016994374947);
    dx_ext1 = (dx_ext2 = dx0 - (3 * 0.309016994374947));
  }
  if ((c & 0x02) != 0)
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb + 1));
    dy_ext0 = (dy0 - 1) - (2 * 0.309016994374947);
    dy_ext1 = (dy_ext2 = (dy0 - 1) - (3 * 0.309016994374947));
    if ((c & 0x01) != 0)
    {
      ysv_ext2 += 1;
      dy_ext2 -= 1;
    }
    else
    {
      ysv_ext1 += 1;
      dy_ext1 -= 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = (ysv_ext2 = ysb));
    dy_ext0 = dy0 - (2 * 0.309016994374947);
    dy_ext1 = (dy_ext2 = dy0 - (3 * 0.309016994374947));
  }
  if ((c & 0x04) != 0)
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb + 1));
    dz_ext0 = (dz0 - 1) - (2 * 0.309016994374947);
    dz_ext1 = (dz_ext2 = (dz0 - 1) - (3 * 0.309016994374947));
    if ((c & 0x03) != 0)
    {
      zsv_ext2 += 1;
      dz_ext2 -= 1;
    }
    else
    {
      zsv_ext1 += 1;
      dz_ext1 -= 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = (zsv_ext2 = zsb));
    dz_ext0 = dz0 - (2 * 0.309016994374947);
    dz_ext1 = (dz_ext2 = dz0 - (3 * 0.309016994374947));
  }
  if ((c & 0x08) != 0)
  {
    wsv_ext0 = (wsv_ext1 = wsb + 1);
    wsv_ext2 = wsb + 2;
    dw_ext0 = (dw0 - 1) - (2 * 0.309016994374947);
    dw_ext1 = (dw0 - 1) - (3 * 0.309016994374947);
    dw_ext2 = (dw0 - 2) - (3 * 0.309016994374947);
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = (wsv_ext2 = wsb));
    dw_ext0 = dw0 - (2 * 0.309016994374947);
    dw_ext1 = (dw_ext2 = dw0 - (3 * 0.309016994374947));
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_3_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int aIsBiggerSide, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c1;
  int8_t c2;
  if (aIsBiggerSide)
  {
    c1 = aPoint;
    c2 = bPoint;
  }
  else
  {
    c1 = bPoint;
    c2 = aPoint;
  }
  if ((c1 & 0x01) != 0)
  {
    xsv_ext0 = xsb + 2;
    xsv_ext1 = xsb + 1;
    dx_ext0 = (dx0 - 2) - (3 * 0.309016994374947);
    dx_ext1 = (dx0 - 1) - (3 * 0.309016994374947);
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb);
    dx_ext0 = (dx_ext1 = dx0 - (3 * 0.309016994374947));
  }
  if ((c1 & 0x02) != 0)
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy_ext1 = (dy0 - 1) - (3 * 0.309016994374947));
    if ((c1 & 0x01) == 0)
    {
      ysv_ext0 += 1;
      dy_ext0 -= 1;
    }
    else
    {
      ysv_ext1 += 1;
      dy_ext1 -= 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = (dy_ext1 = dy0 - (3 * 0.309016994374947));
  }
  if ((c1 & 0x04) != 0)
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz_ext1 = (dz0 - 1) - (3 * 0.309016994374947));
    if ((c1 & 0x03) == 0)
    {
      zsv_ext0 += 1;
      dz_ext0 -= 1;
    }
    else
    {
      zsv_ext1 += 1;
      dz_ext1 -= 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb);
    dz_ext0 = (dz_ext1 = dz0 - (3 * 0.309016994374947));
  }
  if ((c1 & 0x08) != 0)
  {
    wsv_ext0 = wsb + 1;
    wsv_ext1 = wsb + 2;
    dw_ext0 = (dw0 - 1) - (3 * 0.309016994374947);
    dw_ext1 = (dw0 - 2) - (3 * 0.309016994374947);
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = wsb);
    dw_ext0 = (dw_ext1 = dw0 - (3 * 0.309016994374947));
  }
  xsv_ext2 = xsb + 1;
  ysv_ext2 = ysb + 1;
  zsv_ext2 = zsb + 1;
  wsv_ext2 = wsb + 1;
  dx_ext2 = (dx0 - 1) - (2 * 0.309016994374947);
  dy_ext2 = (dy0 - 1) - (2 * 0.309016994374947);
  dz_ext2 = (dz0 - 1) - (2 * 0.309016994374947);
  dw_ext2 = (dw0 - 1) - (2 * 0.309016994374947);
  if ((c2 & 0x01) == 0)
  {
    xsv_ext2 -= 2;
    dx_ext2 += 2;
  }
  else
    if ((c2 & 0x02) == 0)
  {
    ysv_ext2 -= 2;
    dy_ext2 += 2;
  }
  else
    if ((c2 & 0x04) == 0)
  {
    zsv_ext2 -= 2;
    dz_ext2 += 2;
  }
  else
  {
    wsv_ext2 -= 2;
    dw_ext2 += 2;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_3_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int aIsBiggerSide, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  if (aIsBiggerSide)
  {
    helper_helper_helper_open_simplex_noise4_3_2_2(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, bPoint);
  }
  else
  {
    helper_helper_helper_open_simplex_noise4_3_2_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, bPoint);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_4_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int aIsBiggerSide, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c1;
  int8_t c2;
  if (aIsBiggerSide)
  {
    c1 = aPoint;
    c2 = bPoint;
  }
  else
  {
    c1 = bPoint;
    c2 = aPoint;
  }
  if ((c1 & 0x01) == 0)
  {
    xsv_ext0 = xsb - 1;
    xsv_ext1 = xsb;
    dx_ext0 = (dx0 + 1) - 0.309016994374947;
    dx_ext1 = dx0 - 0.309016994374947;
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb + 1);
    dx_ext0 = (dx_ext1 = (dx0 - 1) - 0.309016994374947);
  }
  if ((c1 & 0x02) == 0)
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = (dy_ext1 = dy0 - 0.309016994374947);
    if ((c1 & 0x01) == 0x01)
    {
      ysv_ext0 -= 1;
      dy_ext0 += 1;
    }
    else
    {
      ysv_ext1 -= 1;
      dy_ext1 += 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy_ext1 = (dy0 - 1) - 0.309016994374947);
  }
  if ((c1 & 0x04) == 0)
  {
    zsv_ext0 = (zsv_ext1 = zsb);
    dz_ext0 = (dz_ext1 = dz0 - 0.309016994374947);
    if ((c1 & 0x03) == 0x03)
    {
      zsv_ext0 -= 1;
      dz_ext0 += 1;
    }
    else
    {
      zsv_ext1 -= 1;
      dz_ext1 += 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz_ext1 = (dz0 - 1) - 0.309016994374947);
  }
  if ((c1 & 0x08) == 0)
  {
    wsv_ext0 = wsb;
    wsv_ext1 = wsb - 1;
    dw_ext0 = dw0 - 0.309016994374947;
    dw_ext1 = (dw0 + 1) - 0.309016994374947;
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = wsb + 1);
    dw_ext0 = (dw_ext1 = (dw0 - 1) - 0.309016994374947);
  }
  xsv_ext2 = xsb;
  ysv_ext2 = ysb;
  zsv_ext2 = zsb;
  wsv_ext2 = wsb;
  dx_ext2 = dx0 - (2 * 0.309016994374947);
  dy_ext2 = dy0 - (2 * 0.309016994374947);
  dz_ext2 = dz0 - (2 * 0.309016994374947);
  dw_ext2 = dw0 - (2 * 0.309016994374947);
  if ((c2 & 0x01) != 0)
  {
    xsv_ext2 += 2;
    dx_ext2 -= 2;
  }
  else
    if ((c2 & 0x02) != 0)
  {
    ysv_ext2 += 2;
    dy_ext2 -= 2;
  }
  else
    if ((c2 & 0x04) != 0)
  {
    zsv_ext2 += 2;
    dz_ext2 -= 2;
  }
  else
  {
    wsv_ext2 += 2;
    dw_ext2 -= 2;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_open_simplex_noise4_4_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int aIsBiggerSide, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  if (aIsBiggerSide)
  {
    helper_helper_helper_open_simplex_noise4_4_2_2(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, bPoint);
  }
  else
  {
    helper_helper_helper_open_simplex_noise4_4_2_1(&dx_ext0, &dy_ext0, &dz_ext0, &dw_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &dw_ext1, &dx_ext2, &dy_ext2, &dz_ext2, &dw_ext2, &xsv_ext0, &ysv_ext0, &zsv_ext0, &wsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &wsv_ext1, &xsv_ext2, &ysv_ext2, &zsv_ext2, &wsv_ext2, xsb, ysb, zsb, wsb, dx0, dy0, dz0, dw0, aPoint, bPoint);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_helper_open_simplex_noise3_3_2_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  dx_ext0 = (dx0 - 1) - (3 * (1.0 / 3.0));
  dy_ext0 = (dy0 - 1) - (3 * (1.0 / 3.0));
  dz_ext0 = (dz0 - 1) - (3 * (1.0 / 3.0));
  xsv_ext0 = xsb + 1;
  ysv_ext0 = ysb + 1;
  zsv_ext0 = zsb + 1;
  int8_t c = (int8_t) (aPoint & bPoint);
  if ((c & 0x01) != 0)
  {
    dx_ext1 = (dx0 - 2) - (2 * (1.0 / 3.0));
    dy_ext1 = dy0 - (2 * (1.0 / 3.0));
    dz_ext1 = dz0 - (2 * (1.0 / 3.0));
    xsv_ext1 = xsb + 2;
    ysv_ext1 = ysb;
    zsv_ext1 = zsb;
  }
  else
    if ((c & 0x02) != 0)
  {
    dx_ext1 = dx0 - (2 * (1.0 / 3.0));
    dy_ext1 = (dy0 - 2) - (2 * (1.0 / 3.0));
    dz_ext1 = dz0 - (2 * (1.0 / 3.0));
    xsv_ext1 = xsb;
    ysv_ext1 = ysb + 2;
    zsv_ext1 = zsb;
  }
  else
  {
    dx_ext1 = dx0 - (2 * (1.0 / 3.0));
    dy_ext1 = dy0 - (2 * (1.0 / 3.0));
    dz_ext1 = (dz0 - 2) - (2 * (1.0 / 3.0));
    xsv_ext1 = xsb;
    ysv_ext1 = ysb;
    zsv_ext1 = zsb + 2;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_helper_open_simplex_noise3_3_2_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int xsb, int ysb, int zsb, double dx0, double dy0, double dz0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  dx_ext0 = dx0;
  dy_ext0 = dy0;
  dz_ext0 = dz0;
  xsv_ext0 = xsb;
  ysv_ext0 = ysb;
  zsv_ext0 = zsb;
  int8_t c = (int8_t) (aPoint | bPoint);
  if ((c & 0x01) == 0)
  {
    dx_ext1 = (dx0 + 1) - (1.0 / 3.0);
    dy_ext1 = (dy0 - 1) - (1.0 / 3.0);
    dz_ext1 = (dz0 - 1) - (1.0 / 3.0);
    xsv_ext1 = xsb - 1;
    ysv_ext1 = ysb + 1;
    zsv_ext1 = zsb + 1;
  }
  else
    if ((c & 0x02) == 0)
  {
    dx_ext1 = (dx0 - 1) - (1.0 / 3.0);
    dy_ext1 = (dy0 + 1) - (1.0 / 3.0);
    dz_ext1 = (dz0 - 1) - (1.0 / 3.0);
    xsv_ext1 = xsb + 1;
    ysv_ext1 = ysb - 1;
    zsv_ext1 = zsb + 1;
  }
  else
  {
    dx_ext1 = (dx0 - 1) - (1.0 / 3.0);
    dy_ext1 = (dy0 - 1) - (1.0 / 3.0);
    dz_ext1 = (dz0 + 1) - (1.0 / 3.0);
    xsv_ext1 = xsb + 1;
    ysv_ext1 = ysb + 1;
    zsv_ext1 = zsb - 1;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
}

void helper_helper_helper_open_simplex_noise4_3_2_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  xsv_ext2 = xsb + 1;
  ysv_ext2 = ysb + 1;
  zsv_ext2 = zsb + 1;
  wsv_ext2 = wsb + 1;
  dx_ext2 = (dx0 - 1) - (4 * 0.309016994374947);
  dy_ext2 = (dy0 - 1) - (4 * 0.309016994374947);
  dz_ext2 = (dz0 - 1) - (4 * 0.309016994374947);
  dw_ext2 = (dw0 - 1) - (4 * 0.309016994374947);
  int8_t c = (int8_t) (aPoint & bPoint);
  if ((c & 0x01) != 0)
  {
    xsv_ext0 = xsb + 2;
    xsv_ext1 = xsb + 1;
    dx_ext0 = (dx0 - 2) - (3 * 0.309016994374947);
    dx_ext1 = (dx0 - 1) - (3 * 0.309016994374947);
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb);
    dx_ext0 = (dx_ext1 = dx0 - (3 * 0.309016994374947));
  }
  if ((c & 0x02) != 0)
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy_ext1 = (dy0 - 1) - (3 * 0.309016994374947));
    if ((c & 0x01) == 0)
    {
      ysv_ext0 += 1;
      dy_ext0 -= 1;
    }
    else
    {
      ysv_ext1 += 1;
      dy_ext1 -= 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = (dy_ext1 = dy0 - (3 * 0.309016994374947));
  }
  if ((c & 0x04) != 0)
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz_ext1 = (dz0 - 1) - (3 * 0.309016994374947));
    if ((c & 0x03) == 0)
    {
      zsv_ext0 += 1;
      dz_ext0 -= 1;
    }
    else
    {
      zsv_ext1 += 1;
      dz_ext1 -= 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb);
    dz_ext0 = (dz_ext1 = dz0 - (3 * 0.309016994374947));
  }
  if ((c & 0x08) != 0)
  {
    wsv_ext0 = wsb + 1;
    wsv_ext1 = wsb + 2;
    dw_ext0 = (dw0 - 1) - (3 * 0.309016994374947);
    dw_ext1 = (dw0 - 2) - (3 * 0.309016994374947);
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = wsb);
    dw_ext0 = (dw_ext1 = dw0 - (3 * 0.309016994374947));
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_helper_open_simplex_noise4_3_2_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c1 = (int8_t) (aPoint & bPoint);
  int8_t c2 = (int8_t) (aPoint | bPoint);
  xsv_ext0 = (xsv_ext1 = xsb);
  ysv_ext0 = (ysv_ext1 = ysb);
  zsv_ext0 = (zsv_ext1 = zsb);
  wsv_ext0 = (wsv_ext1 = wsb);
  dx_ext0 = dx0 - 0.309016994374947;
  dy_ext0 = dy0 - 0.309016994374947;
  dz_ext0 = dz0 - 0.309016994374947;
  dw_ext0 = dw0 - 0.309016994374947;
  dx_ext1 = dx0 - (2 * 0.309016994374947);
  dy_ext1 = dy0 - (2 * 0.309016994374947);
  dz_ext1 = dz0 - (2 * 0.309016994374947);
  dw_ext1 = dw0 - (2 * 0.309016994374947);
  if ((c1 & 0x01) != 0)
  {
    xsv_ext0 += 1;
    dx_ext0 -= 1;
    xsv_ext1 += 2;
    dx_ext1 -= 2;
  }
  else
    if ((c1 & 0x02) != 0)
  {
    ysv_ext0 += 1;
    dy_ext0 -= 1;
    ysv_ext1 += 2;
    dy_ext1 -= 2;
  }
  else
    if ((c1 & 0x04) != 0)
  {
    zsv_ext0 += 1;
    dz_ext0 -= 1;
    zsv_ext1 += 2;
    dz_ext1 -= 2;
  }
  else
  {
    wsv_ext0 += 1;
    dw_ext0 -= 1;
    wsv_ext1 += 2;
    dw_ext1 -= 2;
  }
  xsv_ext2 = xsb + 1;
  ysv_ext2 = ysb + 1;
  zsv_ext2 = zsb + 1;
  wsv_ext2 = wsb + 1;
  dx_ext2 = (dx0 - 1) - (2 * 0.309016994374947);
  dy_ext2 = (dy0 - 1) - (2 * 0.309016994374947);
  dz_ext2 = (dz0 - 1) - (2 * 0.309016994374947);
  dw_ext2 = (dw0 - 1) - (2 * 0.309016994374947);
  if ((c2 & 0x01) == 0)
  {
    xsv_ext2 -= 2;
    dx_ext2 += 2;
  }
  else
    if ((c2 & 0x02) == 0)
  {
    ysv_ext2 -= 2;
    dy_ext2 += 2;
  }
  else
    if ((c2 & 0x04) == 0)
  {
    zsv_ext2 -= 2;
    dz_ext2 += 2;
  }
  else
  {
    wsv_ext2 -= 2;
    dw_ext2 += 2;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_helper_open_simplex_noise4_4_2_1(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  xsv_ext2 = xsb;
  ysv_ext2 = ysb;
  zsv_ext2 = zsb;
  wsv_ext2 = wsb;
  dx_ext2 = dx0;
  dy_ext2 = dy0;
  dz_ext2 = dz0;
  dw_ext2 = dw0;
  int8_t c = (int8_t) (aPoint | bPoint);
  if ((c & 0x01) == 0)
  {
    xsv_ext0 = xsb - 1;
    xsv_ext1 = xsb;
    dx_ext0 = (dx0 + 1) - 0.309016994374947;
    dx_ext1 = dx0 - 0.309016994374947;
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb + 1);
    dx_ext0 = (dx_ext1 = (dx0 - 1) - 0.309016994374947);
  }
  if ((c & 0x02) == 0)
  {
    ysv_ext0 = (ysv_ext1 = ysb);
    dy_ext0 = (dy_ext1 = dy0 - 0.309016994374947);
    if ((c & 0x01) == 0x01)
    {
      ysv_ext0 -= 1;
      dy_ext0 += 1;
    }
    else
    {
      ysv_ext1 -= 1;
      dy_ext1 += 1;
    }
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy_ext1 = (dy0 - 1) - 0.309016994374947);
  }
  if ((c & 0x04) == 0)
  {
    zsv_ext0 = (zsv_ext1 = zsb);
    dz_ext0 = (dz_ext1 = dz0 - 0.309016994374947);
    if ((c & 0x03) == 0x03)
    {
      zsv_ext0 -= 1;
      dz_ext0 += 1;
    }
    else
    {
      zsv_ext1 -= 1;
      dz_ext1 += 1;
    }
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz_ext1 = (dz0 - 1) - 0.309016994374947);
  }
  if ((c & 0x08) == 0)
  {
    wsv_ext0 = wsb;
    wsv_ext1 = wsb - 1;
    dw_ext0 = dw0 - 0.309016994374947;
    dw_ext1 = (dw0 + 1) - 0.309016994374947;
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = wsb + 1);
    dw_ext0 = (dw_ext1 = (dw0 - 1) - 0.309016994374947);
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

void helper_helper_helper_open_simplex_noise4_4_2_2(double * const dx_ext0_ref, double * const dy_ext0_ref, double * const dz_ext0_ref, double * const dw_ext0_ref, double * const dx_ext1_ref, double * const dy_ext1_ref, double * const dz_ext1_ref, double * const dw_ext1_ref, double * const dx_ext2_ref, double * const dy_ext2_ref, double * const dz_ext2_ref, double * const dw_ext2_ref, int * const xsv_ext0_ref, int * const ysv_ext0_ref, int * const zsv_ext0_ref, int * const wsv_ext0_ref, int * const xsv_ext1_ref, int * const ysv_ext1_ref, int * const zsv_ext1_ref, int * const wsv_ext1_ref, int * const xsv_ext2_ref, int * const ysv_ext2_ref, int * const zsv_ext2_ref, int * const wsv_ext2_ref, int xsb, int ysb, int zsb, int wsb, double dx0, double dy0, double dz0, double dw0, int8_t aPoint, int8_t bPoint)
{
  double dx_ext0 = *dx_ext0_ref;
  double dy_ext0 = *dy_ext0_ref;
  double dz_ext0 = *dz_ext0_ref;
  double dw_ext0 = *dw_ext0_ref;
  double dx_ext1 = *dx_ext1_ref;
  double dy_ext1 = *dy_ext1_ref;
  double dz_ext1 = *dz_ext1_ref;
  double dw_ext1 = *dw_ext1_ref;
  double dx_ext2 = *dx_ext2_ref;
  double dy_ext2 = *dy_ext2_ref;
  double dz_ext2 = *dz_ext2_ref;
  double dw_ext2 = *dw_ext2_ref;
  int xsv_ext0 = *xsv_ext0_ref;
  int ysv_ext0 = *ysv_ext0_ref;
  int zsv_ext0 = *zsv_ext0_ref;
  int wsv_ext0 = *wsv_ext0_ref;
  int xsv_ext1 = *xsv_ext1_ref;
  int ysv_ext1 = *ysv_ext1_ref;
  int zsv_ext1 = *zsv_ext1_ref;
  int wsv_ext1 = *wsv_ext1_ref;
  int xsv_ext2 = *xsv_ext2_ref;
  int ysv_ext2 = *ysv_ext2_ref;
  int zsv_ext2 = *zsv_ext2_ref;
  int wsv_ext2 = *wsv_ext2_ref;
  int8_t c1 = (int8_t) (aPoint | bPoint);
  int8_t c2 = (int8_t) (aPoint & bPoint);
  if ((c1 & 0x01) == 0)
  {
    xsv_ext0 = xsb;
    xsv_ext1 = xsb - 1;
    dx_ext0 = dx0 - (3 * 0.309016994374947);
    dx_ext1 = (dx0 + 1) - (2 * 0.309016994374947);
  }
  else
  {
    xsv_ext0 = (xsv_ext1 = xsb + 1);
    dx_ext0 = (dx0 - 1) - (3 * 0.309016994374947);
    dx_ext1 = (dx0 - 1) - (2 * 0.309016994374947);
  }
  if ((c1 & 0x02) == 0)
  {
    ysv_ext0 = ysb;
    ysv_ext1 = ysb - 1;
    dy_ext0 = dy0 - (3 * 0.309016994374947);
    dy_ext1 = (dy0 + 1) - (2 * 0.309016994374947);
  }
  else
  {
    ysv_ext0 = (ysv_ext1 = ysb + 1);
    dy_ext0 = (dy0 - 1) - (3 * 0.309016994374947);
    dy_ext1 = (dy0 - 1) - (2 * 0.309016994374947);
  }
  if ((c1 & 0x04) == 0)
  {
    zsv_ext0 = zsb;
    zsv_ext1 = zsb - 1;
    dz_ext0 = dz0 - (3 * 0.309016994374947);
    dz_ext1 = (dz0 + 1) - (2 * 0.309016994374947);
  }
  else
  {
    zsv_ext0 = (zsv_ext1 = zsb + 1);
    dz_ext0 = (dz0 - 1) - (3 * 0.309016994374947);
    dz_ext1 = (dz0 - 1) - (2 * 0.309016994374947);
  }
  if ((c1 & 0x08) == 0)
  {
    wsv_ext0 = wsb;
    wsv_ext1 = wsb - 1;
    dw_ext0 = dw0 - (3 * 0.309016994374947);
    dw_ext1 = (dw0 + 1) - (2 * 0.309016994374947);
  }
  else
  {
    wsv_ext0 = (wsv_ext1 = wsb + 1);
    dw_ext0 = (dw0 - 1) - (3 * 0.309016994374947);
    dw_ext1 = (dw0 - 1) - (2 * 0.309016994374947);
  }
  xsv_ext2 = xsb;
  ysv_ext2 = ysb;
  zsv_ext2 = zsb;
  wsv_ext2 = wsb;
  dx_ext2 = dx0 - (2 * 0.309016994374947);
  dy_ext2 = dy0 - (2 * 0.309016994374947);
  dz_ext2 = dz0 - (2 * 0.309016994374947);
  dw_ext2 = dw0 - (2 * 0.309016994374947);
  if ((c2 & 0x01) != 0)
  {
    xsv_ext2 += 2;
    dx_ext2 -= 2;
  }
  else
    if ((c2 & 0x02) != 0)
  {
    ysv_ext2 += 2;
    dy_ext2 -= 2;
  }
  else
    if ((c2 & 0x04) != 0)
  {
    zsv_ext2 += 2;
    dz_ext2 -= 2;
  }
  else
  {
    wsv_ext2 += 2;
    dw_ext2 -= 2;
  }
  *dx_ext0_ref = dx_ext0;
  *dy_ext0_ref = dy_ext0;
  *dz_ext0_ref = dz_ext0;
  *dw_ext0_ref = dw_ext0;
  *dx_ext1_ref = dx_ext1;
  *dy_ext1_ref = dy_ext1;
  *dz_ext1_ref = dz_ext1;
  *dw_ext1_ref = dw_ext1;
  *dx_ext2_ref = dx_ext2;
  *dy_ext2_ref = dy_ext2;
  *dz_ext2_ref = dz_ext2;
  *dw_ext2_ref = dw_ext2;
  *xsv_ext0_ref = xsv_ext0;
  *ysv_ext0_ref = ysv_ext0;
  *zsv_ext0_ref = zsv_ext0;
  *wsv_ext0_ref = wsv_ext0;
  *xsv_ext1_ref = xsv_ext1;
  *ysv_ext1_ref = ysv_ext1;
  *zsv_ext1_ref = zsv_ext1;
  *wsv_ext1_ref = wsv_ext1;
  *xsv_ext2_ref = xsv_ext2;
  *ysv_ext2_ref = ysv_ext2;
  *zsv_ext2_ref = zsv_ext2;
  *wsv_ext2_ref = wsv_ext2;
}

