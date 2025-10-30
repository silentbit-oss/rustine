static size_t UTF8Position(size_t last, size_t c, size_t clamp)
{
  if (c < 128)
  {
    return 0;
  }
  else
    if (c >= 192)
  {
    return brotli_min_size_t(1, clamp);
  }
  else
  {
    if (last < 0xE0)
    {
      return 0;
    }
    else
    {
      return brotli_min_size_t(2, clamp);
    }
  }
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


static size_t DecideMultiByteStatsLevel(size_t pos, size_t len, size_t mask, const uint8_t *data)
{
  size_t counts[3] = {0};
  size_t max_utf8 = 1;
  size_t last_c = 0;
  size_t i;
  for (i = 0; i < len; i += 1)
  {
    size_t c = data[(pos + i) & mask];
    counts[UTF8Position(last_c, c, 2)] += 1;
    last_c = c;
  }

  if (counts[2] < 500)
  {
    max_utf8 = 1;
  }
  if ((counts[1] + counts[2]) < 25)
  {
    max_utf8 = 0;
  }
  return max_utf8;
}


/*** DEPENDENCIES:
static size_t UTF8Position(size_t last, size_t c, size_t clamp)
{
  if (c < 128)
  {
    return 0;
  }
  else
    if (c >= 192)
  {
    return brotli_min_size_t(1, clamp);
  }
  else
  {
    if (last < 0xE0)
    {
      return 0;
    }
    else
    {
      return brotli_min_size_t(2, clamp);
    }
  }
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t']
void helper_helper_EstimateBitCostsForLiteralsUTF8_1_1(size_t * const i_ref, const uint8_t * const data, float * const cost, const size_t max_utf8, size_t histogram[3][256], size_t in_window_utf8[3], size_t pos, size_t mask)
{
  size_t i = *i_ref;
  size_t c = (i < 1) ? (0) : (data[((pos + i) - 1) & mask]);
  size_t last_c = (i < 2) ? (0) : (data[((pos + i) - 2) & mask]);
  size_t utf8_pos = UTF8Position(last_c, c, max_utf8);
  size_t masked_pos = (pos + i) & mask;
  size_t histo = histogram[utf8_pos][data[masked_pos]];
  double lit_cost;
  if (histo == 0)
  {
    histo = 1;
  }
  lit_cost = FastLog2(in_window_utf8[utf8_pos]) - FastLog2(histo);
  lit_cost += 0.02905;
  if (lit_cost < 1.0)
  {
    lit_cost *= 0.5;
    lit_cost += 0.5;
  }
  if (i < 2000)
  {
    lit_cost += 0.7 - ((((double) (2000 - i)) / 2000.0) * 0.35);
  }
  cost[i] = (float) lit_cost;
  *i_ref = i;
}


/*** DEPENDENCIES:
static size_t UTF8Position(size_t last, size_t c, size_t clamp)
{
  if (c < 128)
  {
    return 0;
  }
  else
    if (c >= 192)
  {
    return brotli_min_size_t(1, clamp);
  }
  else
  {
    if (last < 0xE0)
    {
      return 0;
    }
    else
    {
      return brotli_min_size_t(2, clamp);
    }
  }
}


----------------------------
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
***/


// hint:  ['pos_ref is a mutable refrence to size_t', 'mask_ref is a mutable refrence to size_t', 'window_half_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_EstimateBitCostsForLiteralsUTF8_1(size_t * const pos_ref, size_t * const mask_ref, size_t * const window_half_ref, size_t * const i_ref, size_t len, const uint8_t * const data, float * const cost, const size_t max_utf8, size_t histogram[3][256], size_t in_window_utf8[3])
{
  size_t pos = *pos_ref;
  size_t mask = *mask_ref;
  size_t window_half = *window_half_ref;
  size_t i = *i_ref;
  if (i >= window_half)
  {
    size_t c = (i < (window_half + 1)) ? (0) : (data[(((pos + i) - window_half) - 1) & mask]);
    size_t last_c = (i < (window_half + 2)) ? (0) : (data[(((pos + i) - window_half) - 2) & mask]);
    size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
    histogram[utf8_pos2][data[((pos + i) - window_half) & mask]] -= 1;
    in_window_utf8[utf8_pos2] -= 1;
  }
  if ((i + window_half) < len)
  {
    size_t c = data[(((pos + i) + window_half) - 1) & mask];
    size_t last_c = data[(((pos + i) + window_half) - 2) & mask];
    size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
    histogram[utf8_pos2][data[((pos + i) + window_half) & mask]] += 1;
    in_window_utf8[utf8_pos2] += 1;
  }
  {
    helper_helper_EstimateBitCostsForLiteralsUTF8_1_1(&i, data, cost, max_utf8, histogram, in_window_utf8, pos, mask);
  }
  *pos_ref = pos;
  *mask_ref = mask;
  *window_half_ref = window_half;
  *i_ref = i;
}


/*** DEPENDENCIES:
static size_t UTF8Position(size_t last, size_t c, size_t clamp)
{
  if (c < 128)
  {
    return 0;
  }
  else
    if (c >= 192)
  {
    return brotli_min_size_t(1, clamp);
  }
  else
  {
    if (last < 0xE0)
    {
      return 0;
    }
    else
    {
      return brotli_min_size_t(2, clamp);
    }
  }
}


----------------------------
void helper_helper_EstimateBitCostsForLiteralsUTF8_1_1(size_t * const i_ref, const uint8_t * const data, float * const cost, const size_t max_utf8, size_t histogram[3][256], size_t in_window_utf8[3], size_t pos, size_t mask)
{
  size_t i = *i_ref;
  size_t c = (i < 1) ? (0) : (data[((pos + i) - 1) & mask]);
  size_t last_c = (i < 2) ? (0) : (data[((pos + i) - 2) & mask]);
  size_t utf8_pos = UTF8Position(last_c, c, max_utf8);
  size_t masked_pos = (pos + i) & mask;
  size_t histo = histogram[utf8_pos][data[masked_pos]];
  double lit_cost;
  if (histo == 0)
  {
    histo = 1;
  }
  lit_cost = FastLog2(in_window_utf8[utf8_pos]) - FastLog2(histo);
  lit_cost += 0.02905;
  if (lit_cost < 1.0)
  {
    lit_cost *= 0.5;
    lit_cost += 0.5;
  }
  if (i < 2000)
  {
    lit_cost += 0.7 - ((((double) (2000 - i)) / 2000.0) * 0.35);
  }
  cost[i] = (float) lit_cost;
  *i_ref = i;
}


----------------------------
***/


static void EstimateBitCostsForLiteralsUTF8(size_t pos, size_t len, size_t mask, const uint8_t *data, float *cost)
{
  const size_t max_utf8 = DecideMultiByteStatsLevel(pos, len, mask, data);
  size_t histogram[3][256] = {{0}};
  size_t window_half = 495;
  size_t in_window = brotli_min_size_t(window_half, len);
  size_t in_window_utf8[3] = {0};
  size_t i;
  {
    size_t last_c = 0;
    size_t utf8_pos = 0;
    for (i = 0; i < in_window; i += 1)
    {
      size_t c = data[(pos + i) & mask];
      histogram[utf8_pos][c] += 1;
      in_window_utf8[utf8_pos] += 1;
      utf8_pos = UTF8Position(last_c, c, max_utf8);
      last_c = c;
    }

  }
  for (i = 0; i < len; i += 1)
  {
    helper_EstimateBitCostsForLiteralsUTF8_1(&pos, &mask, &window_half, &i, len, data, cost, max_utf8, histogram, in_window_utf8);
  }

}


/*** DEPENDENCIES:
void helper_EstimateBitCostsForLiteralsUTF8_1(size_t * const pos_ref, size_t * const mask_ref, size_t * const window_half_ref, size_t * const i_ref, size_t len, const uint8_t * const data, float * const cost, const size_t max_utf8, size_t histogram[3][256], size_t in_window_utf8[3])
{
  size_t pos = *pos_ref;
  size_t mask = *mask_ref;
  size_t window_half = *window_half_ref;
  size_t i = *i_ref;
  if (i >= window_half)
  {
    size_t c = (i < (window_half + 1)) ? (0) : (data[(((pos + i) - window_half) - 1) & mask]);
    size_t last_c = (i < (window_half + 2)) ? (0) : (data[(((pos + i) - window_half) - 2) & mask]);
    size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
    histogram[utf8_pos2][data[((pos + i) - window_half) & mask]] -= 1;
    in_window_utf8[utf8_pos2] -= 1;
  }
  if ((i + window_half) < len)
  {
    size_t c = data[(((pos + i) + window_half) - 1) & mask];
    size_t last_c = data[(((pos + i) + window_half) - 2) & mask];
    size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
    histogram[utf8_pos2][data[((pos + i) + window_half) & mask]] += 1;
    in_window_utf8[utf8_pos2] += 1;
  }
  {
    helper_helper_EstimateBitCostsForLiteralsUTF8_1_1(&i, data, cost, max_utf8, histogram, in_window_utf8, pos, mask);
  }
  *pos_ref = pos;
  *mask_ref = mask;
  *window_half_ref = window_half;
  *i_ref = i;
}


----------------------------
static size_t UTF8Position(size_t last, size_t c, size_t clamp)
{
  if (c < 128)
  {
    return 0;
  }
  else
    if (c >= 192)
  {
    return brotli_min_size_t(1, clamp);
  }
  else
  {
    if (last < 0xE0)
    {
      return 0;
    }
    else
    {
      return brotli_min_size_t(2, clamp);
    }
  }
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static size_t DecideMultiByteStatsLevel(size_t pos, size_t len, size_t mask, const uint8_t *data)
{
  size_t counts[3] = {0};
  size_t max_utf8 = 1;
  size_t last_c = 0;
  size_t i;
  for (i = 0; i < len; i += 1)
  {
    size_t c = data[(pos + i) & mask];
    counts[UTF8Position(last_c, c, 2)] += 1;
    last_c = c;
  }

  if (counts[2] < 500)
  {
    max_utf8 = 1;
  }
  if ((counts[1] + counts[2]) < 25)
  {
    max_utf8 = 0;
  }
  return max_utf8;
}


----------------------------
***/


void BrotliEstimateBitCostsForLiterals(size_t pos, size_t len, size_t mask, const uint8_t *data, float *cost)
{
  if (BrotliIsMostlyUTF8(data, pos, mask, len, kMinUTF8Ratio))
  {
    EstimateBitCostsForLiteralsUTF8(pos, len, mask, data, cost);
    return;
  }
  else
  {
    size_t histogram[256] = {0};
    size_t window_half = 2000;
    size_t in_window = brotli_min_size_t(window_half, len);
    size_t i;
    for (i = 0; i < in_window; i += 1)
    {
      histogram[data[(pos + i) & mask]] += 1;
    }

    for (i = 0; i < len; i += 1)
    {
      size_t histo;
      if (i >= window_half)
      {
        histogram[data[((pos + i) - window_half) & mask]] -= 1;
        in_window -= 1;
      }
      if ((i + window_half) < len)
      {
        histogram[data[((pos + i) + window_half) & mask]] += 1;
        in_window += 1;
      }
      histo = histogram[data[(pos + i) & mask]];
      if (histo == 0)
      {
        histo = 1;
      }
      {
        double lit_cost = FastLog2(in_window) - FastLog2(histo);
        lit_cost += 0.029;
        if (lit_cost < 1.0)
        {
          lit_cost *= 0.5;
          lit_cost += 0.5;
        }
        cost[i] = (float) lit_cost;
      }
    }

  }
}


/*** DEPENDENCIES:
static void EstimateBitCostsForLiteralsUTF8(size_t pos, size_t len, size_t mask, const uint8_t *data, float *cost)
{
  const size_t max_utf8 = DecideMultiByteStatsLevel(pos, len, mask, data);
  size_t histogram[3][256] = {{0}};
  size_t window_half = 495;
  size_t in_window = brotli_min_size_t(window_half, len);
  size_t in_window_utf8[3] = {0};
  size_t i;
  {
    size_t last_c = 0;
    size_t utf8_pos = 0;
    for (i = 0; i < in_window; i += 1)
    {
      size_t c = data[(pos + i) & mask];
      histogram[utf8_pos][c] += 1;
      in_window_utf8[utf8_pos] += 1;
      utf8_pos = UTF8Position(last_c, c, max_utf8);
      last_c = c;
    }

  }
  for (i = 0; i < len; i += 1)
  {
    helper_EstimateBitCostsForLiteralsUTF8_1(&pos, &mask, &window_half, &i, len, data, cost, max_utf8, histogram, in_window_utf8);
  }

}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static const double kMinUTF8Ratio = 0.75
----------------------------
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
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


----------------------------
***/


