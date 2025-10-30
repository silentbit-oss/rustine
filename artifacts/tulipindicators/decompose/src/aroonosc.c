int ti_aroonosc_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'maxi_ref is a mutable refrence to int', 'mini_ref is a mutable refrence to int', 'max_ref is a mutable refrence to double', 'min_ref is a mutable refrence to double', 'j_ref is a mutable refrence to int']
void helper_ti_aroonosc_1(unsigned int * const output_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, int * const j_ref, const double * const high, const double * const low, double * const output, const double scale, int trail, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  int j = *j_ref;
  double bar = high[i];
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
  output[output_idx] = (maxi - mini) * scale;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *j_ref = j;
}


/*** DEPENDENCIES:
***/


int ti_aroonosc(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  double *output = outputs[0];
  unsigned int output_idx = 0;
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
  int i;
  int j;
  for (i = period; i < size; i += 1, trail += 1)
  {
    helper_ti_aroonosc_1(&output_idx, &maxi, &mini, &max, &min, &j, high, low, output, scale, trail, i);
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_aroonosc_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void helper_ti_aroonosc_1(unsigned int * const output_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, int * const j_ref, const double * const high, const double * const low, double * const output, const double scale, int trail, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  int j = *j_ref;
  double bar = high[i];
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
  output[output_idx] = (maxi - mini) * scale;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *j_ref = j;
}


----------------------------
int ti_aroon_start(const double *options)
{
  return (int) options[0];
}


----------------------------
int ti_aroonosc_start(const double *options)
{
  return (int) options[0];
}


----------------------------
***/


