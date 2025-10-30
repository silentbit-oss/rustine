int ti_adxr_start(const double *options)
{
  return (((int) options[0]) - 1) * 3;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'dmup_ref is a mutable refrence to double', 'dmdown_ref is a mutable refrence to double', 'adx_ref is a mutable refrence to double']
void helper_ti_adxr_1(unsigned int * const output_idx_ref, double * const dmup_ref, double * const dmdown_ref, double * const adx_ref, const double * const high, const double * const low, const int period, double * const output, const double per, const double invper, int i, ti_buffer * const adxr, const int first_adxr)
{
  unsigned int output_idx = *output_idx_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
  double adx = *adx_ref;
  double dp;
  double dm;
  do
  {
    dp = high[i] - high[i - 1];
    dm = low[i - 1] - low[i];
    if (dp < 0)
    {
      dp = 0;
    }
    else
      if (dp > dm)
    {
      dm = 0;
    }
    if (dm < 0)
    {
      dm = 0;
    }
    else
      if (dm > dp)
    {
      dp = 0;
    }
  }
  while (0);
  dmup = (dmup * per) + dp;
  dmdown = (dmdown * per) + dm;
  double di_up = dmup;
  double di_down = dmdown;
  double dm_diff = fabs(di_up - di_down);
  double dm_sum = di_up + di_down;
  double dx = (dm_diff / dm_sum) * 100;
  if ((i - period) < (period - 2))
  {
    adx += dx;
  }
  else
    if ((i - period) == (period - 2))
  {
    adx += dx;
    do
    {
      adxr->vals[adxr->index] = adx * invper;
      adxr->index = adxr->index + 1;
      if (adxr->index >= adxr->size)
      {
        adxr->index = 0;
      }
    }
    while (0);
  }
  else
  {
    adx = (adx * per) + dx;
    if (i >= first_adxr)
    {
      output[output_idx] = 0.5 * ((adx * invper) + adxr->vals[(((adxr->index + adxr->size) - 1) + 1) % adxr->size]);
      output_idx += 1;
    }
    do
    {
      adxr->vals[adxr->index] = adx * invper;
      adxr->index = adxr->index + 1;
      if (adxr->index >= adxr->size)
      {
        adxr->index = 0;
      }
    }
    while (0);
  }
  *output_idx_ref = output_idx;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
  *adx_ref = adx;
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


int ti_adxr(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 2)
  {
    return 1;
  }
  if (size <= ti_adxr_start(options))
  {
    return 0;
  }
  const double per = (((double) period) - 1) / ((double) period);
  const double invper = 1.0 / ((double) period);
  double dmup = 0;
  double dmdown = 0;
  int i;
  for (i = 1; i < period; i += 1)
  {
    double dp;
    double dm;
    do
    {
      dp = high[i] - high[i - 1];
      dm = low[i - 1] - low[i];
      if (dp < 0)
      {
        dp = 0;
      }
      else
        if (dp > dm)
      {
        dm = 0;
      }
      if (dm < 0)
      {
        dm = 0;
      }
      else
        if (dm > dp)
      {
        dp = 0;
      }
    }
    while (0);
    dmup += dp;
    dmdown += dm;
  }

  double adx = 0.0;
  {
    double di_up = dmup;
    double di_down = dmdown;
    double dm_diff = fabs(di_up - di_down);
    double dm_sum = di_up + di_down;
    double dx = (dm_diff / dm_sum) * 100;
    adx += dx;
  }
  ti_buffer *adxr = ti_buffer_new(period - 1);
  const int first_adxr = ti_adxr_start(options);
  for (i = period; i < size; i += 1)
  {
    helper_ti_adxr_1(&output_idx, &dmup, &dmdown, &adx, high, low, period, output, per, invper, i, adxr, first_adxr);
  }

  ti_buffer_free(adxr);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_adxr_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
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
int ti_adxr_start(const double *options)
{
  return (((int) options[0]) - 1) * 3;
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
void helper_ti_adxr_1(unsigned int * const output_idx_ref, double * const dmup_ref, double * const dmdown_ref, double * const adx_ref, const double * const high, const double * const low, const int period, double * const output, const double per, const double invper, int i, ti_buffer * const adxr, const int first_adxr)
{
  unsigned int output_idx = *output_idx_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
  double adx = *adx_ref;
  double dp;
  double dm;
  do
  {
    dp = high[i] - high[i - 1];
    dm = low[i - 1] - low[i];
    if (dp < 0)
    {
      dp = 0;
    }
    else
      if (dp > dm)
    {
      dm = 0;
    }
    if (dm < 0)
    {
      dm = 0;
    }
    else
      if (dm > dp)
    {
      dp = 0;
    }
  }
  while (0);
  dmup = (dmup * per) + dp;
  dmdown = (dmdown * per) + dm;
  double di_up = dmup;
  double di_down = dmdown;
  double dm_diff = fabs(di_up - di_down);
  double dm_sum = di_up + di_down;
  double dx = (dm_diff / dm_sum) * 100;
  if ((i - period) < (period - 2))
  {
    adx += dx;
  }
  else
    if ((i - period) == (period - 2))
  {
    adx += dx;
    do
    {
      adxr->vals[adxr->index] = adx * invper;
      adxr->index = adxr->index + 1;
      if (adxr->index >= adxr->size)
      {
        adxr->index = 0;
      }
    }
    while (0);
  }
  else
  {
    adx = (adx * per) + dx;
    if (i >= first_adxr)
    {
      output[output_idx] = 0.5 * ((adx * invper) + adxr->vals[(((adxr->index + adxr->size) - 1) + 1) % adxr->size]);
      output_idx += 1;
    }
    do
    {
      adxr->vals[adxr->index] = adx * invper;
      adxr->index = adxr->index + 1;
      if (adxr->index >= adxr->size)
      {
        adxr->index = 0;
      }
    }
    while (0);
  }
  *output_idx_ref = output_idx;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
  *adx_ref = adx;
}


----------------------------
***/


