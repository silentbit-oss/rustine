int ti_di_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['atr_ref is a mutable refrence to double', 'dmup_ref is a mutable refrence to double', 'dmdown_ref is a mutable refrence to double']
void helper_ti_di_1(double * const atr_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, const double * const close, int i)
{
  double atr = *atr_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
  double truerange;
  do
  {
    const double l = low[i];
    const double h = high[i];
    const double c = close[i - 1];
    const double ych = fabs(h - c);
    const double ycl = fabs(l - c);
    double v = h - l;
    if (ych > v)
    {
      v = ych;
    }
    if (ycl > v)
    {
      v = ycl;
    }
    truerange = v;
  }
  while (0);
  atr += truerange;
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
  *atr_ref = atr;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


/*** DEPENDENCIES:
***/


// hint:  ['plus_di_idx_ref is a mutable refrence to unsigned int', 'minus_di_idx_ref is a mutable refrence to unsigned int', 'atr_ref is a mutable refrence to double', 'dmup_ref is a mutable refrence to double', 'dmdown_ref is a mutable refrence to double']
void helper_ti_di_2(unsigned int * const plus_di_idx_ref, unsigned int * const minus_di_idx_ref, double * const atr_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, const double * const close, double * const plus_di, double * const minus_di, const double per, int i)
{
  unsigned int plus_di_idx = *plus_di_idx_ref;
  unsigned int minus_di_idx = *minus_di_idx_ref;
  double atr = *atr_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
  double truerange;
  do
  {
    const double l = low[i];
    const double h = high[i];
    const double c = close[i - 1];
    const double ych = fabs(h - c);
    const double ycl = fabs(l - c);
    double v = h - l;
    if (ych > v)
    {
      v = ych;
    }
    if (ycl > v)
    {
      v = ycl;
    }
    truerange = v;
  }
  while (0);
  atr = (atr * per) + truerange;
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
  plus_di[plus_di_idx] = (100.0 * dmup) / atr;
  plus_di_idx += 1;
  *((&minus_di[minus_di_idx])++) = (100.0 * dmdown) / atr;
  *plus_di_idx_ref = plus_di_idx;
  *minus_di_idx_ref = minus_di_idx;
  *atr_ref = atr;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


/*** DEPENDENCIES:
***/


int ti_di(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const int period = (int) options[0];
  double *plus_di = outputs[0];
  unsigned int plus_di_idx = 0;
  double *minus_di = outputs[1];
  unsigned int minus_di_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_di_start(options))
  {
    return 0;
  }
  const double per = (((double) period) - 1) / ((double) period);
  double atr = 0;
  double dmup = 0;
  double dmdown = 0;
  int i;
  for (i = 1; i < period; i += 1)
  {
    helper_ti_di_1(&atr, &dmup, &dmdown, high, low, close, i);
  }

  plus_di[plus_di_idx] = (100.0 * dmup) / atr;
  plus_di_idx += 1;
  minus_di[minus_di_idx] = (100.0 * dmdown) / atr;
  minus_di_idx += 1;
  for (i = period; i < size; i += 1)
  {
    helper_ti_di_2(&plus_di_idx, &minus_di_idx, &atr, &dmup, &dmdown, high, low, close, plus_di, minus_di, per, i);
  }

  assert(((&plus_di[plus_di_idx]) - outputs[0]) == (size - ti_di_start(options)));
  assert(((&minus_di[minus_di_idx]) - outputs[1]) == (size - ti_di_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void helper_ti_di_1(double * const atr_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, const double * const close, int i)
{
  double atr = *atr_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
  double truerange;
  do
  {
    const double l = low[i];
    const double h = high[i];
    const double c = close[i - 1];
    const double ych = fabs(h - c);
    const double ycl = fabs(l - c);
    double v = h - l;
    if (ych > v)
    {
      v = ych;
    }
    if (ycl > v)
    {
      v = ycl;
    }
    truerange = v;
  }
  while (0);
  atr += truerange;
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
  *atr_ref = atr;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


----------------------------
int ti_di_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
void helper_ti_di_2(unsigned int * const plus_di_idx_ref, unsigned int * const minus_di_idx_ref, double * const atr_ref, double * const dmup_ref, double * const dmdown_ref, const double * const high, const double * const low, const double * const close, double * const plus_di, double * const minus_di, const double per, int i)
{
  unsigned int plus_di_idx = *plus_di_idx_ref;
  unsigned int minus_di_idx = *minus_di_idx_ref;
  double atr = *atr_ref;
  double dmup = *dmup_ref;
  double dmdown = *dmdown_ref;
  double truerange;
  do
  {
    const double l = low[i];
    const double h = high[i];
    const double c = close[i - 1];
    const double ych = fabs(h - c);
    const double ycl = fabs(l - c);
    double v = h - l;
    if (ych > v)
    {
      v = ych;
    }
    if (ycl > v)
    {
      v = ycl;
    }
    truerange = v;
  }
  while (0);
  atr = (atr * per) + truerange;
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
  plus_di[plus_di_idx] = (100.0 * dmup) / atr;
  plus_di_idx += 1;
  *((&minus_di[minus_di_idx])++) = (100.0 * dmdown) / atr;
  *plus_di_idx_ref = plus_di_idx;
  *minus_di_idx_ref = minus_di_idx;
  *atr_ref = atr;
  *dmup_ref = dmup;
  *dmdown_ref = dmdown;
}


----------------------------
***/


