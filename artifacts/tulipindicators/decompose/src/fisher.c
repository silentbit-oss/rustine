int ti_fisher_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['signal_idx_ref is a mutable refrence to unsigned int', 'maxi_ref is a mutable refrence to int', 'mini_ref is a mutable refrence to int', 'max_ref is a mutable refrence to double', 'min_ref is a mutable refrence to double', 'val1_ref is a mutable refrence to double', 'bar_ref is a mutable refrence to double', 'fish_ref is a mutable refrence to double', 'j_ref is a mutable refrence to int']
void helper_ti_fisher_1(unsigned int * const signal_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const val1_ref, double * const bar_ref, double * const fish_ref, int * const j_ref, const double * const high, const double * const low, double * const fisher, double * const signal, int trail, int i)
{
  unsigned int signal_idx = *signal_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double val1 = *val1_ref;
  double bar = *bar_ref;
  double fish = *fish_ref;
  int j = *j_ref;
  bar = 0.5 * (high[i] + low[i]);
  if (maxi < trail)
  {
    maxi = trail;
    max = 0.5 * (high[maxi] + low[maxi]);
    j = trail;
    while ((++j) <= i)
    {
      bar = 0.5 * (high[j] + low[j]);
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
  bar = 0.5 * (high[i] + low[i]);
  if (mini < trail)
  {
    mini = trail;
    min = 0.5 * (high[mini] + low[mini]);
    j = trail;
    while ((++j) <= i)
    {
      bar = 0.5 * (high[j] + low[j]);
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
  double mm = max - min;
  if (mm == 0.0)
  {
    mm = 0.001;
  }
  val1 = ((0.33 * 2.0) * ((((0.5 * (high[i] + low[i])) - min) / mm) - 0.5)) + (0.67 * val1);
  if (val1 > 0.99)
  {
    val1 = .999;
  }
  if (val1 < (-0.99))
  {
    val1 = -.999;
  }
  signal[signal_idx] = fish;
  signal_idx += 1;
  fish = (0.5 * log((1.0 + val1) / (1.0 - val1))) + (0.5 * fish);
  *(fisher++) = fish;
  *signal_idx_ref = signal_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *val1_ref = val1;
  *bar_ref = bar;
  *fish_ref = fish;
  *j_ref = j;
}


/*** DEPENDENCIES:
***/


int ti_fisher(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  double *fisher = outputs[0];
  double *signal = outputs[1];
  unsigned int signal_idx = 0;
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_fisher_start(options))
  {
    return 0;
  }
  int trail = 0;
  int maxi = -1;
  int mini = -1;
  double max = 0.5 * (high[0] + low[0]);
  double min = 0.5 * (high[0] + low[0]);
  double val1 = 0.0;
  double bar;
  double fish = 0.0;
  int i;
  int j;
  for (i = period - 1; i < size; i += 1, trail += 1)
  {
    helper_ti_fisher_1(&signal_idx, &maxi, &mini, &max, &min, &val1, &bar, &fish, &j, high, low, fisher, signal, trail, i);
  }

  assert((fisher - outputs[0]) == (size - ti_fisher_start(options)));
  assert(((&signal[signal_idx]) - outputs[1]) == (size - ti_fisher_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_fisher_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
void helper_ti_fisher_1(unsigned int * const signal_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const val1_ref, double * const bar_ref, double * const fish_ref, int * const j_ref, const double * const high, const double * const low, double * const fisher, double * const signal, int trail, int i)
{
  unsigned int signal_idx = *signal_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double val1 = *val1_ref;
  double bar = *bar_ref;
  double fish = *fish_ref;
  int j = *j_ref;
  bar = 0.5 * (high[i] + low[i]);
  if (maxi < trail)
  {
    maxi = trail;
    max = 0.5 * (high[maxi] + low[maxi]);
    j = trail;
    while ((++j) <= i)
    {
      bar = 0.5 * (high[j] + low[j]);
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
  bar = 0.5 * (high[i] + low[i]);
  if (mini < trail)
  {
    mini = trail;
    min = 0.5 * (high[mini] + low[mini]);
    j = trail;
    while ((++j) <= i)
    {
      bar = 0.5 * (high[j] + low[j]);
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
  double mm = max - min;
  if (mm == 0.0)
  {
    mm = 0.001;
  }
  val1 = ((0.33 * 2.0) * ((((0.5 * (high[i] + low[i])) - min) / mm) - 0.5)) + (0.67 * val1);
  if (val1 > 0.99)
  {
    val1 = .999;
  }
  if (val1 < (-0.99))
  {
    val1 = -.999;
  }
  signal[signal_idx] = fish;
  signal_idx += 1;
  fish = (0.5 * log((1.0 + val1) / (1.0 - val1))) + (0.5 * fish);
  *(fisher++) = fish;
  *signal_idx_ref = signal_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *val1_ref = val1;
  *bar_ref = bar;
  *fish_ref = fish;
  *j_ref = j;
}


----------------------------
***/


