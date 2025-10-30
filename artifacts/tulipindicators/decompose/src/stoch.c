int ti_stoch_start(const double *options)
{
  const int kperiod = (int) options[0];
  const int kslow = (int) options[1];
  const int dperiod = (int) options[2];
  return ((kperiod + kslow) + dperiod) - 3;
}


/*** DEPENDENCIES:
***/


// hint:  ['stoch_idx_ref is a mutable refrence to unsigned int', 'trail_ref is a mutable refrence to int', 'maxi_ref is a mutable refrence to int', 'mini_ref is a mutable refrence to int', 'max_ref is a mutable refrence to double', 'min_ref is a mutable refrence to double', 'bar_ref is a mutable refrence to double', 'j_ref is a mutable refrence to int']
void helper_ti_stoch_1(unsigned int * const stoch_idx_ref, int * const trail_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const bar_ref, int * const j_ref, const double * const high, const double * const low, const double * const close, const int kperiod, const int kslow, const int dperiod, const double kper, const double dper, double * const stoch, double * const stoch_ma, ti_buffer * const k_sum, ti_buffer * const d_sum, int i)
{
  unsigned int stoch_idx = *stoch_idx_ref;
  int trail = *trail_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double bar = *bar_ref;
  int j = *j_ref;
  if (i >= kperiod)
  {
    trail += 1;
  }
  bar = high[i];
  if (maxi < trail)
  {
    maxi = trail;
    max = high[maxi];
    j = trail;
    while ((++j) <= i)
    {
      bar = high[j];
      if (bar >= max)
      {
        max = bar;
        maxi = j;
      }
    }

  }
  else
    if (bar >= max)
  {
    maxi = i;
    max = bar;
  }
  bar = low[i];
  if (mini < trail)
  {
    mini = trail;
    min = low[mini];
    j = trail;
    while ((++j) <= i)
    {
      bar = low[j];
      if (bar <= min)
      {
        min = bar;
        mini = j;
      }
    }

  }
  else
    if (bar <= min)
  {
    mini = i;
    min = bar;
  }
  const double kdiff = max - min;
  const double kfast = (kdiff == 0.0) ? (0.0) : (100 * ((close[i] - min) / kdiff));
  do
  {
    if (k_sum->pushes >= k_sum->size)
    {
      k_sum->sum -= k_sum->vals[k_sum->index];
    }
    k_sum->sum += kfast;
    k_sum->vals[k_sum->index] = kfast;
    k_sum->pushes += 1;
    k_sum->index = k_sum->index + 1;
    if (k_sum->index >= k_sum->size)
    {
      k_sum->index = 0;
    }
  }
  while (0);
  if (i >= (((kperiod - 1) + kslow) - 1))
  {
    const double k = k_sum->sum * kper;
    do
    {
      if (d_sum->pushes >= d_sum->size)
      {
        d_sum->sum -= d_sum->vals[d_sum->index];
      }
      d_sum->sum += k;
      d_sum->vals[d_sum->index] = k;
      d_sum->pushes += 1;
      d_sum->index = d_sum->index + 1;
      if (d_sum->index >= d_sum->size)
      {
        d_sum->index = 0;
      }
    }
    while (0);
    if (i >= (((((kperiod - 1) + kslow) - 1) + dperiod) - 1))
    {
      stoch[stoch_idx] = k;
      stoch_idx += 1;
      *(stoch_ma++) = d_sum->sum * dper;
    }
  }
  *stoch_idx_ref = stoch_idx;
  *trail_ref = trail;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *bar_ref = bar;
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


int ti_stoch(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const int kperiod = (int) options[0];
  const int kslow = (int) options[1];
  const int dperiod = (int) options[2];
  const double kper = 1.0 / kslow;
  const double dper = 1.0 / dperiod;
  double *stoch = outputs[0];
  unsigned int stoch_idx = 0;
  double *stoch_ma = outputs[1];
  if (kperiod < 1)
  {
    return 1;
  }
  if (kslow < 1)
  {
    return 1;
  }
  if (dperiod < 1)
  {
    return 1;
  }
  if (size <= ti_stoch_start(options))
  {
    return 0;
  }
  int trail = 0;
  int maxi = -1;
  int mini = -1;
  double max = high[0];
  double min = low[0];
  double bar;
  ti_buffer *k_sum = ti_buffer_new(kslow);
  ti_buffer *d_sum = ti_buffer_new(dperiod);
  int i;
  int j;
  for (i = 0; i < size; i += 1)
  {
    helper_ti_stoch_1(&stoch_idx, &trail, &maxi, &mini, &max, &min, &bar, &j, high, low, close, kperiod, kslow, dperiod, kper, dper, stoch, stoch_ma, k_sum, d_sum, i);
  }

  ti_buffer_free(k_sum);
  ti_buffer_free(d_sum);
  assert(((&stoch[stoch_idx]) - outputs[0]) == (size - ti_stoch_start(options)));
  assert((stoch_ma - outputs[1]) == (size - ti_stoch_start(options)));
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
int ti_stoch_start(const double *options)
{
  const int kperiod = (int) options[0];
  const int kslow = (int) options[1];
  const int dperiod = (int) options[2];
  return ((kperiod + kslow) + dperiod) - 3;
}


----------------------------
void helper_ti_stoch_1(unsigned int * const stoch_idx_ref, int * const trail_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const bar_ref, int * const j_ref, const double * const high, const double * const low, const double * const close, const int kperiod, const int kslow, const int dperiod, const double kper, const double dper, double * const stoch, double * const stoch_ma, ti_buffer * const k_sum, ti_buffer * const d_sum, int i)
{
  unsigned int stoch_idx = *stoch_idx_ref;
  int trail = *trail_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double bar = *bar_ref;
  int j = *j_ref;
  if (i >= kperiod)
  {
    trail += 1;
  }
  bar = high[i];
  if (maxi < trail)
  {
    maxi = trail;
    max = high[maxi];
    j = trail;
    while ((++j) <= i)
    {
      bar = high[j];
      if (bar >= max)
      {
        max = bar;
        maxi = j;
      }
    }

  }
  else
    if (bar >= max)
  {
    maxi = i;
    max = bar;
  }
  bar = low[i];
  if (mini < trail)
  {
    mini = trail;
    min = low[mini];
    j = trail;
    while ((++j) <= i)
    {
      bar = low[j];
      if (bar <= min)
      {
        min = bar;
        mini = j;
      }
    }

  }
  else
    if (bar <= min)
  {
    mini = i;
    min = bar;
  }
  const double kdiff = max - min;
  const double kfast = (kdiff == 0.0) ? (0.0) : (100 * ((close[i] - min) / kdiff));
  do
  {
    if (k_sum->pushes >= k_sum->size)
    {
      k_sum->sum -= k_sum->vals[k_sum->index];
    }
    k_sum->sum += kfast;
    k_sum->vals[k_sum->index] = kfast;
    k_sum->pushes += 1;
    k_sum->index = k_sum->index + 1;
    if (k_sum->index >= k_sum->size)
    {
      k_sum->index = 0;
    }
  }
  while (0);
  if (i >= (((kperiod - 1) + kslow) - 1))
  {
    const double k = k_sum->sum * kper;
    do
    {
      if (d_sum->pushes >= d_sum->size)
      {
        d_sum->sum -= d_sum->vals[d_sum->index];
      }
      d_sum->sum += k;
      d_sum->vals[d_sum->index] = k;
      d_sum->pushes += 1;
      d_sum->index = d_sum->index + 1;
      if (d_sum->index >= d_sum->size)
      {
        d_sum->index = 0;
      }
    }
    while (0);
    if (i >= (((((kperiod - 1) + kslow) - 1) + dperiod) - 1))
    {
      stoch[stoch_idx] = k;
      stoch_idx += 1;
      *(stoch_ma++) = d_sum->sum * dper;
    }
  }
  *stoch_idx_ref = stoch_idx;
  *trail_ref = trail;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *bar_ref = bar;
  *j_ref = j;
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


