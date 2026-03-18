int ti_dx_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'dmup_ref is a mutable refrence to double', 'dmdown_ref is a mutable refrence to double']
void helper_ti_dx_1(unsigned int * const output_idx_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, double * const output, const double per, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
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
  output[output_idx] = dx;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


/*** DEPENDENCIES:
***/


int ti_dx(int size, const double * const *inputs, const double *options, double * const *outputs)
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
  if (size <= ti_dx_start(options))
  {
    return 0;
  }
  const double per = (((double) period) - 1) / ((double) period);
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

  {
    double di_up = dmup;
    double di_down = dmdown;
    double dm_diff = fabs(di_up - di_down);
    double dm_sum = di_up + di_down;
    double dx = (dm_diff / dm_sum) * 100;
    output[output_idx] = dx;
    output_idx += 1;
  }
  for (i = period; i < size; i += 1)
  {
    helper_ti_dx_1(&output_idx, &dmup, &dmdown, high, low, output, per, i);
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_dx_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_dx_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
void helper_ti_dx_1(unsigned int * const output_idx_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, double * const output, const double per, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
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
  output[output_idx] = dx;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


----------------------------
***/


