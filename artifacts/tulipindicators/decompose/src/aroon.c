int ti_aroon_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


// hint:  ['adown_idx_ref is a mutable refrence to unsigned int', 'maxi_ref is a mutable refrence to int', 'mini_ref is a mutable refrence to int', 'max_ref is a mutable refrence to double', 'min_ref is a mutable refrence to double', 'bar_ref is a mutable refrence to double', 'j_ref is a mutable refrence to int']
void helper_ti_aroon_1(unsigned int * const adown_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const bar_ref, int * const j_ref, const double * const high, const double * const low, double * const adown, double * const aup, const int period, const double scale, int trail, int i)
{
  unsigned int adown_idx = *adown_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double bar = *bar_ref;
  int j = *j_ref;
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
  adown[adown_idx] = (((double) period) - (i - mini)) * scale;
  adown_idx += 1;
  *(aup++) = (((double) period) - (i - maxi)) * scale;
  *adown_idx_ref = adown_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *bar_ref = bar;
  *j_ref = j;
}


/*** DEPENDENCIES:
***/


int ti_aroon(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  double *adown = outputs[0];
  unsigned int adown_idx = 0;
  double *aup = outputs[1];
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_aroon_start(options))
  {
    return 0;
  }
  const double scale = 100.0 / period;
  int trail = 0;
  int maxi = -1;
  int mini = -1;
  double max = high[0];
  double min = low[0];
  double bar;
  int i;
  int j;
  for (i = period; i < size; i += 1, trail += 1)
  {
    helper_ti_aroon_1(&adown_idx, &maxi, &mini, &max, &min, &bar, &j, high, low, adown, aup, period, scale, trail, i);
  }

  assert(((&adown[adown_idx]) - outputs[0]) == (size - ti_aroon_start(options)));
  assert((aup - outputs[1]) == (size - ti_aroon_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_aroon_start(const double *options)
{
  return (int) options[0];
}


----------------------------
void helper_ti_aroon_1(unsigned int * const adown_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const bar_ref, int * const j_ref, const double * const high, const double * const low, double * const adown, double * const aup, const int period, const double scale, int trail, int i)
{
  unsigned int adown_idx = *adown_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double bar = *bar_ref;
  int j = *j_ref;
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
  adown[adown_idx] = (((double) period) - (i - mini)) * scale;
  adown_idx += 1;
  *(aup++) = (((double) period) - (i - maxi)) * scale;
  *adown_idx_ref = adown_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *bar_ref = bar;
  *j_ref = j;
}


----------------------------
***/


