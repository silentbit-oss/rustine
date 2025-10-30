int ti_mass_start(const double *options)
{
  int sum_p = ((int) options[0]) - 1;
  return 16 + sum_p;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'ema_ref is a mutable refrence to double', 'ema2_ref is a mutable refrence to double']
void helper_ti_mass_1(unsigned int * const output_idx_ref, double * const ema_ref, double * const ema2_ref, const double * const high, const double * const low, const int period, double * const output, const double per, const double per1, ti_buffer * const sum, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double ema = *ema_ref;
  double ema2 = *ema2_ref;
  double hl = high[i] - low[i];
  ema = (ema * per1) + (hl * per);
  if (i == 8)
  {
    ema2 = ema;
  }
  if (i >= 8)
  {
    ema2 = (ema2 * per1) + (ema * per);
    if (i >= 16)
    {
      do
      {
        if (sum->pushes >= sum->size)
        {
          sum->sum -= sum->vals[sum->index];
        }
        sum->sum += ema / ema2;
        sum->vals[sum->index] = ema / ema2;
        sum->pushes += 1;
        sum->index = sum->index + 1;
        if (sum->index >= sum->size)
        {
          sum->index = 0;
        }
      }
      while (0);
      if (i >= ((16 + period) - 1))
      {
        output[output_idx] = sum->sum;
        output_idx += 1;
      }
    }
  }
  *output_idx_ref = output_idx;
  *ema_ref = ema;
  *ema2_ref = ema2;
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


int ti_mass(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_mass_start(options))
  {
    return 0;
  }
  const double per = 2 / (9.0 + 1);
  const double per1 = 1.0 - per;
  double ema = high[0] - low[0];
  double ema2 = ema;
  ti_buffer *sum = ti_buffer_new(period);
  int i;
  for (i = 0; i < size; i += 1)
  {
    helper_ti_mass_1(&output_idx, &ema, &ema2, high, low, period, output, per, per1, sum, i);
  }

  ti_buffer_free(sum);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_mass_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
void helper_ti_mass_1(unsigned int * const output_idx_ref, double * const ema_ref, double * const ema2_ref, const double * const high, const double * const low, const int period, double * const output, const double per, const double per1, ti_buffer * const sum, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double ema = *ema_ref;
  double ema2 = *ema2_ref;
  double hl = high[i] - low[i];
  ema = (ema * per1) + (hl * per);
  if (i == 8)
  {
    ema2 = ema;
  }
  if (i >= 8)
  {
    ema2 = (ema2 * per1) + (ema * per);
    if (i >= 16)
    {
      do
      {
        if (sum->pushes >= sum->size)
        {
          sum->sum -= sum->vals[sum->index];
        }
        sum->sum += ema / ema2;
        sum->vals[sum->index] = ema / ema2;
        sum->pushes += 1;
        sum->index = sum->index + 1;
        if (sum->index >= sum->size)
        {
          sum->index = 0;
        }
      }
      while (0);
      if (i >= ((16 + period) - 1))
      {
        output[output_idx] = sum->sum;
        output_idx += 1;
      }
    }
  }
  *output_idx_ref = output_idx;
  *ema_ref = ema;
  *ema2_ref = ema2;
}


----------------------------
int ti_mass_start(const double *options)
{
  int sum_p = ((int) options[0]) - 1;
  return 16 + sum_p;
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


