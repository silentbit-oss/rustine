int ti_dm_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['plus_dm_idx_ref is a mutable refrence to unsigned int', 'minus_dm_idx_ref is a mutable refrence to unsigned int', 'dmup_ref is a mutable refrence to double', 'dmdown_ref is a mutable refrence to double']
void helper_ti_dm_1(unsigned int * const plus_dm_idx_ref, unsigned int * const minus_dm_idx_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, double * const plus_dm, double * const minus_dm, const double per, int i)
{
  unsigned int plus_dm_idx = *plus_dm_idx_ref;
  unsigned int minus_dm_idx = *minus_dm_idx_ref;
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
  plus_dm[plus_dm_idx] = dmup;
  plus_dm_idx += 1;
  *((&minus_dm[minus_dm_idx])++) = dmdown;
  *plus_dm_idx_ref = plus_dm_idx;
  *minus_dm_idx_ref = minus_dm_idx;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


/*** DEPENDENCIES:
***/


int ti_dm(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const int period = (int) options[0];
  double *plus_dm = outputs[0];
  unsigned int plus_dm_idx = 0;
  double *minus_dm = outputs[1];
  unsigned int minus_dm_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_dm_start(options))
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

  plus_dm[plus_dm_idx] = dmup;
  plus_dm_idx += 1;
  minus_dm[minus_dm_idx] = dmdown;
  minus_dm_idx += 1;
  for (i = period; i < size; i += 1)
  {
    helper_ti_dm_1(&plus_dm_idx, &minus_dm_idx, &dmup, &dmdown, high, low, plus_dm, minus_dm, per, i);
  }

  assert(((&plus_dm[plus_dm_idx]) - outputs[0]) == (size - ti_dm_start(options)));
  assert(((&minus_dm[minus_dm_idx]) - outputs[1]) == (size - ti_dm_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void helper_ti_dm_1(unsigned int * const plus_dm_idx_ref, unsigned int * const minus_dm_idx_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, double * const plus_dm, double * const minus_dm, const double per, int i)
{
  unsigned int plus_dm_idx = *plus_dm_idx_ref;
  unsigned int minus_dm_idx = *minus_dm_idx_ref;
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
  plus_dm[plus_dm_idx] = dmup;
  plus_dm_idx += 1;
  *((&minus_dm[minus_dm_idx])++) = dmdown;
  *plus_dm_idx_ref = plus_dm_idx;
  *minus_dm_idx_ref = minus_dm_idx;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


----------------------------
int ti_dm_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


