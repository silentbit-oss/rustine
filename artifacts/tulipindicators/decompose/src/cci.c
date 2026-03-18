int ti_cci_start(const double *options)
{
  const int period = (int) options[0];
  return (period - 1) * 2;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to int']
void helper_ti_cci_1(unsigned int * const output_idx_ref, int * const j_ref, const double * const high, const double * const low, const double * const close, const int period, const double scale, double * const output, ti_buffer * const sum, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int j = *j_ref;
  const double today = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
  do
  {
    if (sum->pushes >= sum->size)
    {
      sum->sum -= sum->vals[sum->index];
    }
    sum->sum += today;
    sum->vals[sum->index] = today;
    sum->pushes += 1;
    sum->index = sum->index + 1;
    if (sum->index >= sum->size)
    {
      sum->index = 0;
    }
  }
  while (0);
  const double avg = sum->sum * scale;
  if (i >= ((period * 2) - 2))
  {
    double acc = 0;
    for (j = 0; j < period; j += 1)
    {
      acc += fabs(avg - sum->vals[j]);
    }

    double cci = acc * scale;
    cci *= .015;
    cci = (today - avg) / cci;
    output[output_idx] = cci;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *j_ref = j;
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


int ti_cci(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const int period = (int) options[0];
  const double scale = 1.0 / period;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_cci_start(options))
  {
    return 0;
  }
  double *output = outputs[0];
  unsigned int output_idx = 0;
  ti_buffer *sum = ti_buffer_new(period);
  int i;
  int j;
  for (i = 0; i < size; i += 1)
  {
    helper_ti_cci_1(&output_idx, &j, high, low, close, period, scale, output, sum, i);
  }

  ti_buffer_free(sum);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_cci_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
void helper_ti_cci_1(unsigned int * const output_idx_ref, int * const j_ref, const double * const high, const double * const low, const double * const close, const int period, const double scale, double * const output, ti_buffer * const sum, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int j = *j_ref;
  const double today = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
  do
  {
    if (sum->pushes >= sum->size)
    {
      sum->sum -= sum->vals[sum->index];
    }
    sum->sum += today;
    sum->vals[sum->index] = today;
    sum->pushes += 1;
    sum->index = sum->index + 1;
    if (sum->index >= sum->size)
    {
      sum->index = 0;
    }
  }
  while (0);
  const double avg = sum->sum * scale;
  if (i >= ((period * 2) - 2))
  {
    double acc = 0;
    for (j = 0; j < period; j += 1)
    {
      acc += fabs(avg - sum->vals[j]);
    }

    double cci = acc * scale;
    cci *= .015;
    cci = (today - avg) / cci;
    output[output_idx] = cci;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *j_ref = j;
}


----------------------------
int ti_cci_start(const double *options)
{
  const int period = (int) options[0];
  return (period - 1) * 2;
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


