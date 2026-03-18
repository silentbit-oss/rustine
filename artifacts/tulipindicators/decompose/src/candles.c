const char *tc_version(void)
{
  return "0.9.2";
}


/*** DEPENDENCIES:
***/


long int tc_build(void)
{
  return 1746800254;
}


/*** DEPENDENCIES:
***/


int tc_candle_count(void)
{
  return 26;
}


/*** DEPENDENCIES:
***/


const tc_candle_info *tc_find_candle(const char *name)
{
  int imin = 0;
  int imax = ((sizeof(tc_candles)) / (sizeof(tc_candle_info))) - 2;
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    const int c = strcmp(name, tc_candles[i].name);
    if (c == 0)
    {
      return tc_candles + i;
    }
    else
      if (c > 0)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
extern tc_candle_info tc_candles[]
----------------------------
***/


const tc_config *tc_config_default()
{
  static tc_config default_config = {.period = 10, .body_none = 0.05, .body_short = 0.5, .body_long = 1.4, .wick_none = 0.05, .wick_long = 0.6, .near = 0.3};
  return &default_config;
}


/*** DEPENDENCIES:
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
***/


tc_result *tc_result_new()
{
  tc_result *k = malloc(sizeof(tc_result));
  if (!k)
  {
    return 0;
  }
  memset(k, 0, sizeof(tc_result));
  return k;
}


/*** DEPENDENCIES:
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


void tc_result_free(tc_result *result)
{
  if (!result)
  {
    return;
  }
  free(result->hits);
  free(result);
}


/*** DEPENDENCIES:
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_result_count(const tc_result *result)
{
  return result->count;
}


/*** DEPENDENCIES:
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_result_pattern_count(const tc_result *result)
{
  return result->pattern_count;
}


/*** DEPENDENCIES:
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


tc_set tc_result_at(const tc_result *result, int index)
{
  int imin = 0;
  int imax = result->count - 1;
  if (!imax)
  {
    return 0;
  }
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    assert(i >= 0);
    assert(i < result->count);
    if (index == result->hits[i].index)
    {
      return result->hits[i].patterns;
    }
    else
      if (index > result->hits[i].index)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


static void tc_result_reset(tc_result *result)
{
  result->progress = 0;
  result->count = 0;
  result->pattern_count = 0;
}


/*** DEPENDENCIES:
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


const tc_candle_info *tc_get_info(tc_set pattern)
{
  if (!pattern)
  {
    return 0;
  }
  tc_set k = pattern & (~(pattern - 1));
  int imin = 0;
  int imax = ((sizeof(tc_candles)) / (sizeof(tc_candle_info))) - 2;
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    if (k == tc_candles[i].pattern)
    {
      return tc_candles + i;
    }
    else
      if (k > tc_candles[i].pattern)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
extern tc_candle_info tc_candles[]
----------------------------
typedef uint64_t tc_set
----------------------------
***/


void tc_config_set_to_default(tc_config *config)
{
  memcpy(config, tc_config_default(), sizeof(tc_config));
}


/*** DEPENDENCIES:
const tc_config *tc_config_default()
{
  static tc_config default_config = {.period = 10, .body_none = 0.05, .body_short = 0.5, .body_long = 1.4, .wick_none = 0.05, .wick_long = 0.6, .near = 0.3};
  return &default_config;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
***/


tc_hit tc_result_get(const tc_result *result, int index)
{
  if (index < result->count)
  {
    return result->hits[index];
  }
  tc_hit hit = {0};
  return hit;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_abandoned_baby_bear_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (low[i - 1] >= high[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (high[i] <= low[i - 1])) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 0};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_abandoned_baby_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_abandoned_baby_bear_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_abandoned_baby_bear_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (low[i - 1] >= high[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (high[i] <= low[i - 1])) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 0};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_abandoned_baby_bull_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (high[i - 1] <= low[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (low[i] >= high[i - 1])) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 1};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_abandoned_baby_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_abandoned_baby_bull_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int helper_tc_abandoned_baby_bull_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (high[i - 1] <= low[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (low[i] >= high[i - 1])) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 1};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_big_black_candle_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((open[i] > close[i]) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 2};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_big_black_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_big_black_candle_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_big_black_candle_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((open[i] > close[i]) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 2};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_big_white_candle_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((open[i] < close[i]) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 3};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_big_white_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_big_white_candle_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
int helper_tc_big_white_candle_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((open[i] < close[i]) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 3};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_black_marubozu_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((fabs(open[i] - close[i]) > (options->body_long * avg_body)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] > close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 4};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_black_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_black_marubozu_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
int helper_tc_black_marubozu_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((fabs(open[i] - close[i]) > (options->body_long * avg_body)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] > close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 4};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (fabs(open[i] - close[i]) < (options->body_none * avg_total))
  {
    do
    {
      const tc_hit hit = {i, 1L << 5};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (fabs(open[i] - close[i]) < (options->body_none * avg_total))
  {
    do
    {
      const tc_hit hit = {i, 1L << 5};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_dragonfly_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 6};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_dragonfly_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_dragonfly_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int helper_tc_dragonfly_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 6};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_engulfing_bear_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (open[i] > close[i])) && (open[i - 1] < close[i - 1])) && (close[i] < open[i - 1])) && (open[i] > close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 7};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_engulfing_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_engulfing_bear_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int helper_tc_engulfing_bear_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (open[i] > close[i])) && (open[i - 1] < close[i - 1])) && (close[i] < open[i - 1])) && (open[i] > close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 7};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_engulfing_bull_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (open[i] < close[i])) && (open[i - 1] > close[i - 1])) && (close[i] > open[i - 1])) && (open[i] < close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 8};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_engulfing_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_engulfing_bull_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_engulfing_bull_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (open[i] < close[i])) && (open[i - 1] > close[i - 1])) && (close[i] > open[i - 1])) && (open[i] < close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 8};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_evening_doji_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 9};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_evening_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_evening_doji_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_evening_doji_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 9};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_evening_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 10};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_evening_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_evening_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_evening_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 10};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_four_price_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 11};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_four_price_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_four_price_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_four_price_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 11};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_gravestone_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 12};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_gravestone_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_gravestone_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
int helper_tc_gravestone_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 12};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_hammer_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) <= (low[i - 1] + (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 13};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_hammer_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_hammer_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) <= (low[i - 1] + (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 13};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_hanging_man_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= (high[i - 1] - (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 14};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_hanging_man(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_hanging_man_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
int helper_tc_hanging_man_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= (high[i - 1] - (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 14};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_inverted_hammer_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 15};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_inverted_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_inverted_hammer_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
int helper_tc_inverted_hammer_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 15};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_long_legged_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 16};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_long_legged_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_long_legged_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
int helper_tc_long_legged_doji_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_none * avg_total)) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 16};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_marubozu_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) > (options->body_long * avg_body)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 17};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_marubozu_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
int helper_tc_marubozu_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) > (options->body_long * avg_body)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 17};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_morning_doji_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 18};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_morning_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_morning_doji_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
int helper_tc_morning_doji_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 18};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_morning_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 19};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_morning_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_morning_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int helper_tc_morning_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((i >= 2) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 19};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_shooting_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 20};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_shooting_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_shooting_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int helper_tc_shooting_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((((i >= 1) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 20};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_spinning_top_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_short * avg_body)) && ((high[i] - top) > fabs(open[i] - close[i]))) && ((bottom - low[i]) > fabs(open[i] - close[i])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 21};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_spinning_top(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_spinning_top_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
int helper_tc_spinning_top_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if (((fabs(open[i] - close[i]) < (options->body_short * avg_body)) && ((high[i] - top) > fabs(open[i] - close[i]))) && ((bottom - low[i]) > fabs(open[i] - close[i])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 21};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((i >= 1) && ((low[i] >= high[i - 1]) || (high[i] <= low[i - 1])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 22};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_star_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
int helper_tc_star_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((i >= 1) && ((low[i] >= high[i - 1]) || (high[i] <= low[i - 1])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 22};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_three_black_crows_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((i >= 2) && (open[i - 2] > close[i - 2])) && (open[i - 1] > close[i - 1])) && (open[i] > close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 23};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_three_black_crows(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_three_black_crows_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
int helper_tc_three_black_crows_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((i >= 2) && (open[i - 2] > close[i - 2])) && (open[i - 1] > close[i - 1])) && (open[i] > close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 23};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_three_white_soldiers_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((i >= 2) && (open[i - 2] < close[i - 2])) && (open[i - 1] < close[i - 1])) && (open[i] < close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 24};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


int tc_three_white_soldiers(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_three_white_soldiers_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
int helper_tc_three_white_soldiers_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((i >= 2) && (open[i - 2] < close[i - 2])) && (open[i - 1] < close[i - 1])) && (open[i] < close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 24};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_white_marubozu_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((fabs(open[i] - close[i]) > (options->body_long * avg_body)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] < close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 25};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_white_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_white_marubozu_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
int helper_tc_white_marubozu_1(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((fabs(open[i] - close[i]) > (options->body_long * avg_body)) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] < close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 25};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


int helper_helper_tc_run_1_1(tc_set patterns, int size, const TC_REAL * const * const inputs, const tc_config * const options, tc_result * const output)
{
  if (patterns == (1L << 0))
  {
    return tc_abandoned_baby_bear(size, inputs, options, output);
  }
  if (patterns == (1L << 1))
  {
    return tc_abandoned_baby_bull(size, inputs, options, output);
  }
  if (patterns == (1L << 2))
  {
    return tc_big_black_candle(size, inputs, options, output);
  }
  if (patterns == (1L << 3))
  {
    return tc_big_white_candle(size, inputs, options, output);
  }
  if (patterns == (1L << 4))
  {
    return tc_black_marubozu(size, inputs, options, output);
  }
  if (patterns == (1L << 5))
  {
    return tc_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 6))
  {
    return tc_dragonfly_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 7))
  {
    return tc_engulfing_bear(size, inputs, options, output);
  }
  if (patterns == (1L << 8))
  {
    return tc_engulfing_bull(size, inputs, options, output);
  }
  if (patterns == (1L << 9))
  {
    return tc_evening_doji_star(size, inputs, options, output);
  }
  if (patterns == (1L << 10))
  {
    return tc_evening_star(size, inputs, options, output);
  }
  if (patterns == (1L << 11))
  {
    return tc_four_price_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 12))
  {
    return tc_gravestone_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 13))
  {
    return tc_hammer(size, inputs, options, output);
  }
  if (patterns == (1L << 14))
  {
    return tc_hanging_man(size, inputs, options, output);
  }
  if (patterns == (1L << 15))
  {
    return tc_inverted_hammer(size, inputs, options, output);
  }
  if (patterns == (1L << 16))
  {
    return tc_long_legged_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 17))
  {
    return tc_marubozu(size, inputs, options, output);
  }
  if (patterns == (1L << 18))
  {
    return tc_morning_doji_star(size, inputs, options, output);
  }
  if (patterns == (1L << 19))
  {
    return tc_morning_star(size, inputs, options, output);
  }
  if (patterns == (1L << 20))
  {
    return tc_shooting_star(size, inputs, options, output);
  }
  if (patterns == (1L << 21))
  {
    return tc_spinning_top(size, inputs, options, output);
  }
  if (patterns == (1L << 22))
  {
    return tc_star(size, inputs, options, output);
  }
  if (patterns == (1L << 23))
  {
    return tc_three_black_crows(size, inputs, options, output);
  }
  if (patterns == (1L << 24))
  {
    return tc_three_white_soldiers(size, inputs, options, output);
  }
  if (patterns == (1L << 25))
  {
    return tc_white_marubozu(size, inputs, options, output);
  }
}


/*** DEPENDENCIES:
int tc_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
typedef double TC_REAL
----------------------------
int tc_evening_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_evening_doji_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_inverted_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_inverted_hammer_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_star_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_shooting_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_shooting_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_abandoned_baby_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_abandoned_baby_bear_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_hammer_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_long_legged_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_long_legged_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_black_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_black_marubozu_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_three_white_soldiers(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_three_white_soldiers_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_white_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_white_marubozu_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_morning_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_morning_doji_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_gravestone_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_gravestone_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_engulfing_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_engulfing_bull_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
typedef uint64_t tc_set
----------------------------
int tc_spinning_top(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_spinning_top_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_engulfing_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_engulfing_bear_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_big_white_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_big_white_candle_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_four_price_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_four_price_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_big_black_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_big_black_candle_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_hanging_man(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_hanging_man_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int tc_abandoned_baby_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_abandoned_baby_bull_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_dragonfly_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_dragonfly_doji_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_three_black_crows(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_three_black_crows_1(&avg_body_sum, &avg_total_sum, &i, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_marubozu_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_evening_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_evening_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
int tc_morning_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_morning_star_1(&avg_body_sum, &avg_total_sum, &i, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
***/


int helper_tc_run_1(tc_set patterns, int size, const TC_REAL * const * const inputs, const tc_config * const options, tc_result * const output)
{
  if ((patterns & (patterns - 1)) == 0)
  {
    helper_helper_tc_run_1_1(patterns, size, inputs, options, output);
  }
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
typedef uint64_t tc_set
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
int helper_helper_tc_run_1_1(tc_set patterns, int size, const TC_REAL * const * const inputs, const tc_config * const options, tc_result * const output)
{
  if (patterns == (1L << 0))
  {
    return tc_abandoned_baby_bear(size, inputs, options, output);
  }
  if (patterns == (1L << 1))
  {
    return tc_abandoned_baby_bull(size, inputs, options, output);
  }
  if (patterns == (1L << 2))
  {
    return tc_big_black_candle(size, inputs, options, output);
  }
  if (patterns == (1L << 3))
  {
    return tc_big_white_candle(size, inputs, options, output);
  }
  if (patterns == (1L << 4))
  {
    return tc_black_marubozu(size, inputs, options, output);
  }
  if (patterns == (1L << 5))
  {
    return tc_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 6))
  {
    return tc_dragonfly_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 7))
  {
    return tc_engulfing_bear(size, inputs, options, output);
  }
  if (patterns == (1L << 8))
  {
    return tc_engulfing_bull(size, inputs, options, output);
  }
  if (patterns == (1L << 9))
  {
    return tc_evening_doji_star(size, inputs, options, output);
  }
  if (patterns == (1L << 10))
  {
    return tc_evening_star(size, inputs, options, output);
  }
  if (patterns == (1L << 11))
  {
    return tc_four_price_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 12))
  {
    return tc_gravestone_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 13))
  {
    return tc_hammer(size, inputs, options, output);
  }
  if (patterns == (1L << 14))
  {
    return tc_hanging_man(size, inputs, options, output);
  }
  if (patterns == (1L << 15))
  {
    return tc_inverted_hammer(size, inputs, options, output);
  }
  if (patterns == (1L << 16))
  {
    return tc_long_legged_doji(size, inputs, options, output);
  }
  if (patterns == (1L << 17))
  {
    return tc_marubozu(size, inputs, options, output);
  }
  if (patterns == (1L << 18))
  {
    return tc_morning_doji_star(size, inputs, options, output);
  }
  if (patterns == (1L << 19))
  {
    return tc_morning_star(size, inputs, options, output);
  }
  if (patterns == (1L << 20))
  {
    return tc_shooting_star(size, inputs, options, output);
  }
  if (patterns == (1L << 21))
  {
    return tc_spinning_top(size, inputs, options, output);
  }
  if (patterns == (1L << 22))
  {
    return tc_star(size, inputs, options, output);
  }
  if (patterns == (1L << 23))
  {
    return tc_three_black_crows(size, inputs, options, output);
  }
  if (patterns == (1L << 24))
  {
    return tc_three_white_soldiers(size, inputs, options, output);
  }
  if (patterns == (1L << 25))
  {
    return tc_white_marubozu(size, inputs, options, output);
  }
}


----------------------------
***/


// hint:  ['avg_body_sum_ref is a mutable refrence to TC_REAL', 'avg_total_sum_ref is a mutable refrence to TC_REAL', 'i_ref is a mutable refrence to int']
int helper_tc_run_2(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_set patterns, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((((1L << 0) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (low[i - 1] >= high[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (high[i] <= low[i - 1])) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 0};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 1) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (high[i - 1] <= low[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (low[i] >= high[i - 1])) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 1};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((1L << 2) & patterns) && (open[i] > close[i])) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 2};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((1L << 3) & patterns) && (open[i] < close[i])) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 3};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((1L << 4) & patterns) && (fabs(open[i] - close[i]) > (options->body_long * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] > close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 4};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((1L << 5) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 5};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 6) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 6};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 7) & patterns) && (i >= 1)) && (open[i] > close[i])) && (open[i - 1] < close[i - 1])) && (close[i] < open[i - 1])) && (open[i] > close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 7};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 8) & patterns) && (i >= 1)) && (open[i] < close[i])) && (open[i - 1] > close[i - 1])) && (close[i] > open[i - 1])) && (open[i] < close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 8};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 9) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 9};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 10) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 10};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 11) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 11};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 12) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 12};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 13) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) <= (low[i - 1] + (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 13};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 14) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= (high[i - 1] - (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 14};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 15) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 15};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 16) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 16};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 17) & patterns) && (fabs(open[i] - close[i]) > (options->body_long * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 17};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 18) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 18};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 19) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 19};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 20) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 20};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 21) & patterns) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > fabs(open[i] - close[i]))) && ((bottom - low[i]) > fabs(open[i] - close[i])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 21};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((1L << 22) & patterns) && (i >= 1)) && ((low[i] >= high[i - 1]) || (high[i] <= low[i - 1])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 22};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((1L << 23) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (open[i - 1] > close[i - 1])) && (open[i] > close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 23};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((1L << 24) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (open[i - 1] < close[i - 1])) && (open[i] < close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 24};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((1L << 25) & patterns) && (fabs(open[i] - close[i]) > (options->body_long * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] < close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 25};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
static int tc_result_add(tc_result *result, tc_hit hit)
{
  result->pattern_count += 1;
  if (result->count > 0)
  {
    if (result->hits[result->count - 1].index == hit.index)
    {
      do
      {
        result->hits[result->count - 1].patterns |= hit.patterns;
      }
      while (0);
      return 0;
    }
  }
  if (result->space == 0)
  {
    result->space = 2048;
    result->count = 0;
    result->hits = malloc((sizeof(tc_hit)) * ((unsigned int) result->space));
  }
  else
    if (result->space == result->count)
  {
    result->space *= 2;
    tc_hit *hits = realloc(result->hits, (sizeof(tc_hit)) * ((unsigned int) result->space));
    if (!hits)
    {
      return 2;
    }
    result->hits = hits;
  }
  result->hits[result->count] = hit;
  result->count += 1;
  return 0;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
typedef uint64_t tc_set
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


int tc_run(tc_set patterns, int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  tc_result_reset(output);
  {
    helper_tc_run_1(patterns, size, inputs, options, output);
  }
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_run_2(&avg_body_sum, &avg_total_sum, &i, patterns, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
typedef uint64_t tc_set
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
static void tc_result_reset(tc_result *result)
{
  result->progress = 0;
  result->count = 0;
  result->pattern_count = 0;
}


----------------------------
int helper_tc_run_1(tc_set patterns, int size, const TC_REAL * const * const inputs, const tc_config * const options, tc_result * const output)
{
  if ((patterns & (patterns - 1)) == 0)
  {
    helper_helper_tc_run_1_1(patterns, size, inputs, options, output);
  }
}


----------------------------
int helper_tc_run_2(TC_REAL * const avg_body_sum_ref, TC_REAL * const avg_total_sum_ref, int * const i_ref, tc_set patterns, const tc_config * const options, tc_result * const output, const TC_REAL * const open, const TC_REAL * const high, const TC_REAL * const low, const TC_REAL * const close, const int period, const TC_REAL div)
{
  TC_REAL avg_body_sum = *avg_body_sum_ref;
  TC_REAL avg_total_sum = *avg_total_sum_ref;
  int i = *i_ref;
  const TC_REAL top = (open[i] > close[i]) ? (open[i]) : (close[i]);
  const TC_REAL bottom = (open[i] < close[i]) ? (open[i]) : (close[i]);
  const TC_REAL body = fabs(open[i] - close[i]);
  const TC_REAL total = high[i] - low[i];
  const TC_REAL upper = high[i] - top;
  const TC_REAL lower = bottom - low[i];
  const TC_REAL avg_body = avg_body_sum * div;
  const TC_REAL avg_total = avg_total_sum * div;
  (void) top;
  (void) bottom;
  (void) body;
  (void) total;
  (void) upper;
  (void) lower;
  (void) avg_body;
  (void) avg_total;
  if ((((((((((1L << 0) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (low[i - 1] >= high[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (high[i] <= low[i - 1])) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 0};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 1) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (high[i - 1] <= low[(i - 1) - 1])) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (low[i] >= high[i - 1])) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 1};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((1L << 2) & patterns) && (open[i] > close[i])) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 2};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((1L << 3) & patterns) && (open[i] < close[i])) && (fabs(open[i] - close[i]) > (options->body_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 3};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((1L << 4) & patterns) && (fabs(open[i] - close[i]) > (options->body_long * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] > close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 4};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((1L << 5) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 5};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 6) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 6};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 7) & patterns) && (i >= 1)) && (open[i] > close[i])) && (open[i - 1] < close[i - 1])) && (close[i] < open[i - 1])) && (open[i] > close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 7};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 8) & patterns) && (i >= 1)) && (open[i] < close[i])) && (open[i - 1] > close[i - 1])) && (close[i] > open[i - 1])) && (open[i] < close[i - 1]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 8};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 9) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 9};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 10) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])) >= ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] > close[i])) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] <= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 10};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 11) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 11};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 12) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 12};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 13) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) <= (low[i - 1] + (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 13};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 14) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) > (options->wick_long * avg_body))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= (high[i - 1] - (options->near * avg_total))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 14};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 15) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] > close[i]) ? (open[i]) : (close[i])) <= ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 15};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 16) & patterns) && (fabs(open[i] - close[i]) < (options->body_none * avg_total))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) > (options->wick_long * avg_body)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 16};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 17) & patterns) && (fabs(open[i] - close[i]) > (options->body_long * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total)))
  {
    do
    {
      const tc_hit hit = {i, 1L << 17};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 18) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_none * avg_total))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 18};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((((1L << 19) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (fabs(open[i - 2] - close[i - 2]) > (options->body_long * avg_body))) && (((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])) <= ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1])))) && (fabs(open[i - 1] - close[i - 1]) < (options->body_short * avg_body))) && (open[i] < close[i])) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1])))) && (close[i] >= close[i - 2]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 19};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((((1L << 20) & patterns) && (i >= 1)) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > (options->wick_long * avg_body))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (((open[i] < close[i]) ? (open[i]) : (close[i])) >= ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 20};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if (((((1L << 21) & patterns) && (fabs(open[i] - close[i]) < (options->body_short * avg_body))) && ((high[i] - top) > fabs(open[i] - close[i]))) && ((bottom - low[i]) > fabs(open[i] - close[i])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 21};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((1L << 22) & patterns) && (i >= 1)) && ((low[i] >= high[i - 1]) || (high[i] <= low[i - 1])))
  {
    do
    {
      const tc_hit hit = {i, 1L << 22};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((1L << 23) & patterns) && (i >= 2)) && (open[i - 2] > close[i - 2])) && (open[i - 1] > close[i - 1])) && (open[i] > close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 23};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((((1L << 24) & patterns) && (i >= 2)) && (open[i - 2] < close[i - 2])) && (open[i - 1] < close[i - 1])) && (open[i] < close[i])) && ((open[i - 1] < ((open[(i - 1) - 1] > close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))) && (open[i - 1] > ((open[(i - 1) - 1] < close[(i - 1) - 1]) ? (open[(i - 1) - 1]) : (close[(i - 1) - 1]))))) && ((open[i] < ((open[i - 1] > close[i - 1]) ? (open[i - 1]) : (close[i - 1]))) && (open[i] > ((open[i - 1] < close[i - 1]) ? (open[i - 1]) : (close[i - 1])))))
  {
    do
    {
      const tc_hit hit = {i, 1L << 24};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  if ((((((1L << 25) & patterns) && (fabs(open[i] - close[i]) > (options->body_long * avg_body))) && ((high[i] - top) < (options->wick_none * avg_total))) && ((bottom - low[i]) < (options->wick_none * avg_total))) && (open[i] < close[i]))
  {
    do
    {
      const tc_hit hit = {i, 1L << 25};
      const int r = tc_result_add(output, hit);
      if (r != 0)
      {
        return r;
      }
    }
    while (0);
  }
  avg_body_sum += body;
  avg_body_sum -= fabs(open[i - period] - close[i - period]);
  avg_total_sum += total;
  avg_total_sum -= high[i - period] - low[i - period];
  i += 1;
  *avg_body_sum_ref = avg_body_sum;
  *avg_total_sum_ref = avg_total_sum;
  *i_ref = i;
}


----------------------------
***/


