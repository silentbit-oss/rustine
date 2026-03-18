int ti_vhf_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'maxi_ref is a mutable refrence to int', 'mini_ref is a mutable refrence to int', 'max_ref is a mutable refrence to double', 'min_ref is a mutable refrence to double', 'bar_ref is a mutable refrence to double', 'sum_ref is a mutable refrence to double', 'j_ref is a mutable refrence to int', 'yc_ref is a mutable refrence to double', 'c_ref is a mutable refrence to double']
void helper_ti_vhf_1(unsigned int * const output_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const bar_ref, double * const sum_ref, int * const j_ref, double * const yc_ref, double * const c_ref, const double * const in, const int period, double * const output, int trail, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double bar = *bar_ref;
  double sum = *sum_ref;
  int j = *j_ref;
  double yc = *yc_ref;
  double c = *c_ref;
  c = in[i];
  sum += fabs(c - yc);
  yc = c;
  if (i > period)
  {
    sum -= fabs(in[i - period] - in[(i - period) - 1]);
  }
  bar = c;
  if (maxi < trail)
  {
    maxi = trail;
    max = in[maxi];
    j = trail;
    while ((++j) <= i)
    {
      bar = in[j];
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
  bar = c;
  if (mini < trail)
  {
    mini = trail;
    min = in[mini];
    j = trail;
    while ((++j) <= i)
    {
      bar = in[j];
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
  output[output_idx] = fabs(max - min) / sum;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *bar_ref = bar;
  *sum_ref = sum;
  *j_ref = j;
  *yc_ref = yc;
  *c_ref = c;
}


/*** DEPENDENCIES:
***/


int ti_vhf(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *in = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_vhf_start(options))
  {
    return 0;
  }
  int trail = 1;
  int maxi = -1;
  int mini = -1;
  double max = in[0];
  double min = in[0];
  double bar;
  double sum = 0;
  int i;
  int j;
  double yc = in[0];
  double c;
  for (i = 1; i < period; i += 1)
  {
    c = in[i];
    sum += fabs(c - yc);
    yc = c;
  }

  for (i = period; i < size; i += 1, trail += 1)
  {
    helper_ti_vhf_1(&output_idx, &maxi, &mini, &max, &min, &bar, &sum, &j, &yc, &c, in, period, output, trail, i);
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_vhf_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void helper_ti_vhf_1(unsigned int * const output_idx_ref, int * const maxi_ref, int * const mini_ref, double * const max_ref, double * const min_ref, double * const bar_ref, double * const sum_ref, int * const j_ref, double * const yc_ref, double * const c_ref, const double * const in, const int period, double * const output, int trail, int i)
{
  unsigned int output_idx = *output_idx_ref;
  int maxi = *maxi_ref;
  int mini = *mini_ref;
  double max = *max_ref;
  double min = *min_ref;
  double bar = *bar_ref;
  double sum = *sum_ref;
  int j = *j_ref;
  double yc = *yc_ref;
  double c = *c_ref;
  c = in[i];
  sum += fabs(c - yc);
  yc = c;
  if (i > period)
  {
    sum -= fabs(in[i - period] - in[(i - period) - 1]);
  }
  bar = c;
  if (maxi < trail)
  {
    maxi = trail;
    max = in[maxi];
    j = trail;
    while ((++j) <= i)
    {
      bar = in[j];
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
  bar = c;
  if (mini < trail)
  {
    mini = trail;
    min = in[mini];
    j = trail;
    while ((++j) <= i)
    {
      bar = in[j];
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
  output[output_idx] = fabs(max - min) / sum;
  output_idx += 1;
  *output_idx_ref = output_idx;
  *maxi_ref = maxi;
  *mini_ref = mini;
  *max_ref = max;
  *min_ref = min;
  *bar_ref = bar;
  *sum_ref = sum;
  *j_ref = j;
  *yc_ref = yc;
  *c_ref = c;
}


----------------------------
int ti_vhf_start(const double *options)
{
  return (int) options[0];
}


----------------------------
***/


