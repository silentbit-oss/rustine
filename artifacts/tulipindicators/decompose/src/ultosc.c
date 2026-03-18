int ti_ultosc_start(const double *options)
{
  return (int) options[2];
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'bp_short_sum_ref is a mutable refrence to double', 'bp_medium_sum_ref is a mutable refrence to double', 'r_short_sum_ref is a mutable refrence to double', 'r_medium_sum_ref is a mutable refrence to double']
void helper_ti_ultosc_1(unsigned int * const output_idx_ref, double * const bp_short_sum_ref, double * const bp_medium_sum_ref, double * const r_short_sum_ref, double * const r_medium_sum_ref, const double * const high, const double * const low, const double * const close, const int short_period, const int medium_period, const int long_period, double * const output, ti_buffer * const bp_buf, ti_buffer * const r_buf, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double bp_short_sum = *bp_short_sum_ref;
  double bp_medium_sum = *bp_medium_sum_ref;
  double r_short_sum = *r_short_sum_ref;
  double r_medium_sum = *r_medium_sum_ref;
  const double true_low = (low[i] < close[i - 1]) ? (low[i]) : (close[i - 1]);
  const double true_high = (high[i] > close[i - 1]) ? (high[i]) : (close[i - 1]);
  const double bp = close[i] - true_low;
  const double r = true_high - true_low;
  bp_short_sum += bp;
  bp_medium_sum += bp;
  r_short_sum += r;
  r_medium_sum += r;
  do
  {
    if (bp_buf->pushes >= bp_buf->size)
    {
      bp_buf->sum -= bp_buf->vals[bp_buf->index];
    }
    bp_buf->sum += bp;
    bp_buf->vals[bp_buf->index] = bp;
    bp_buf->pushes += 1;
    bp_buf->index = bp_buf->index + 1;
    if (bp_buf->index >= bp_buf->size)
    {
      bp_buf->index = 0;
    }
  }
  while (0);
  do
  {
    if (r_buf->pushes >= r_buf->size)
    {
      r_buf->sum -= r_buf->vals[r_buf->index];
    }
    r_buf->sum += r;
    r_buf->vals[r_buf->index] = r;
    r_buf->pushes += 1;
    r_buf->index = r_buf->index + 1;
    if (r_buf->index >= r_buf->size)
    {
      r_buf->index = 0;
    }
  }
  while (0);
  if (i > short_period)
  {
    int short_index = (bp_buf->index - short_period) - 1;
    if (short_index < 0)
    {
      short_index += long_period;
    }
    bp_short_sum -= bp_buf->vals[short_index];
    r_short_sum -= r_buf->vals[short_index];
    if (i > medium_period)
    {
      int medium_index = (bp_buf->index - medium_period) - 1;
      if (medium_index < 0)
      {
        medium_index += long_period;
      }
      bp_medium_sum -= bp_buf->vals[medium_index];
      r_medium_sum -= r_buf->vals[medium_index];
    }
  }
  if (i >= long_period)
  {
    const double first = (4 * bp_short_sum) / r_short_sum;
    const double second = (2 * bp_medium_sum) / r_medium_sum;
    const double third = (1 * bp_buf->sum) / r_buf->sum;
    const double ult = (((first + second) + third) * 100.0) / 7.0;
    output[output_idx] = ult;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *bp_short_sum_ref = bp_short_sum;
  *bp_medium_sum_ref = bp_medium_sum;
  *r_short_sum_ref = r_short_sum;
  *r_medium_sum_ref = r_medium_sum;
}


/*** DEPENDENCIES:
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer
----------------------------
***/


int ti_ultosc(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const int short_period = (int) options[0];
  const int medium_period = (int) options[1];
  const int long_period = (int) options[2];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (short_period < 1)
  {
    return 1;
  }
  if (medium_period < short_period)
  {
    return 1;
  }
  if (long_period < medium_period)
  {
    return 1;
  }
  if (size <= ti_ultosc_start(options))
  {
    return 0;
  }
  ti_buffer *bp_buf = ti_buffer_new(long_period);
  ti_buffer *r_buf = ti_buffer_new(long_period);
  double bp_short_sum = 0;
  double bp_medium_sum = 0;
  double r_short_sum = 0;
  double r_medium_sum = 0;
  int i;
  for (i = 1; i < size; i += 1)
  {
    helper_ti_ultosc_1(&output_idx, &bp_short_sum, &bp_medium_sum, &r_short_sum, &r_medium_sum, high, low, close, short_period, medium_period, long_period, output, bp_buf, r_buf, i);
  }

  ti_buffer_free(bp_buf);
  ti_buffer_free(r_buf);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_ultosc_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
int ti_ultosc_start(const double *options)
{
  return (int) options[2];
}


----------------------------
void helper_ti_ultosc_1(unsigned int * const output_idx_ref, double * const bp_short_sum_ref, double * const bp_medium_sum_ref, double * const r_short_sum_ref, double * const r_medium_sum_ref, const double * const high, const double * const low, const double * const close, const int short_period, const int medium_period, const int long_period, double * const output, ti_buffer * const bp_buf, ti_buffer * const r_buf, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double bp_short_sum = *bp_short_sum_ref;
  double bp_medium_sum = *bp_medium_sum_ref;
  double r_short_sum = *r_short_sum_ref;
  double r_medium_sum = *r_medium_sum_ref;
  const double true_low = (low[i] < close[i - 1]) ? (low[i]) : (close[i - 1]);
  const double true_high = (high[i] > close[i - 1]) ? (high[i]) : (close[i - 1]);
  const double bp = close[i] - true_low;
  const double r = true_high - true_low;
  bp_short_sum += bp;
  bp_medium_sum += bp;
  r_short_sum += r;
  r_medium_sum += r;
  do
  {
    if (bp_buf->pushes >= bp_buf->size)
    {
      bp_buf->sum -= bp_buf->vals[bp_buf->index];
    }
    bp_buf->sum += bp;
    bp_buf->vals[bp_buf->index] = bp;
    bp_buf->pushes += 1;
    bp_buf->index = bp_buf->index + 1;
    if (bp_buf->index >= bp_buf->size)
    {
      bp_buf->index = 0;
    }
  }
  while (0);
  do
  {
    if (r_buf->pushes >= r_buf->size)
    {
      r_buf->sum -= r_buf->vals[r_buf->index];
    }
    r_buf->sum += r;
    r_buf->vals[r_buf->index] = r;
    r_buf->pushes += 1;
    r_buf->index = r_buf->index + 1;
    if (r_buf->index >= r_buf->size)
    {
      r_buf->index = 0;
    }
  }
  while (0);
  if (i > short_period)
  {
    int short_index = (bp_buf->index - short_period) - 1;
    if (short_index < 0)
    {
      short_index += long_period;
    }
    bp_short_sum -= bp_buf->vals[short_index];
    r_short_sum -= r_buf->vals[short_index];
    if (i > medium_period)
    {
      int medium_index = (bp_buf->index - medium_period) - 1;
      if (medium_index < 0)
      {
        medium_index += long_period;
      }
      bp_medium_sum -= bp_buf->vals[medium_index];
      r_medium_sum -= r_buf->vals[medium_index];
    }
  }
  if (i >= long_period)
  {
    const double first = (4 * bp_short_sum) / r_short_sum;
    const double second = (2 * bp_medium_sum) / r_medium_sum;
    const double third = (1 * bp_buf->sum) / r_buf->sum;
    const double ult = (((first + second) + third) * 100.0) / 7.0;
    output[output_idx] = ult;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *bp_short_sum_ref = bp_short_sum;
  *bp_medium_sum_ref = bp_medium_sum;
  *r_short_sum_ref = r_short_sum;
  *r_medium_sum_ref = r_medium_sum;
}


----------------------------
ti_buffer *ti_buffer_new(int size)
{
  const int s = ((int) (sizeof(ti_buffer))) + ((size - 1) * ((int) (sizeof(double))));
  ti_buffer *ret = (ti_buffer *) malloc((unsigned int) s);
  ret->size = size;
  ret->pushes = 0;
  ret->index = 0;
  ret->sum = 0;
  return ret;
}


----------------------------
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer
----------------------------
***/


