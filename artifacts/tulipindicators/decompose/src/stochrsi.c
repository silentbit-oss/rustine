int ti_stochrsi_start(const double *options)
{
  return (((int) options[0]) * 2) - 1;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'smooth_up_ref is a mutable refrence to double', 'smooth_down_ref is a mutable refrence to double', 'r_ref is a mutable refrence to double', 'min_ref is a mutable refrence to double', 'max_ref is a mutable refrence to double', 'mini_ref is a mutable refrence to int', 'maxi_ref is a mutable refrence to int']
void helper_ti_stochrsi_1(unsigned int * const output_idx_ref, double * const smooth_up_ref, double * const smooth_down_ref, double * const r_ref, double * const min_ref, double * const max_ref, int * const mini_ref, int * const maxi_ref, const double * const input, const int period, double * const output, const double per, ti_buffer * const rsi, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double smooth_up = *smooth_up_ref;
  double smooth_down = *smooth_down_ref;
  double r = *r_ref;
  double min = *min_ref;
  double max = *max_ref;
  int mini = *mini_ref;
  int maxi = *maxi_ref;
  const double upward = (input[i] > input[i - 1]) ? (input[i] - input[i - 1]) : (0);
  const double downward = (input[i] < input[i - 1]) ? (input[i - 1] - input[i]) : (0);
  smooth_up = ((upward - smooth_up) * per) + smooth_up;
  smooth_down = ((downward - smooth_down) * per) + smooth_down;
  r = 100.0 * (smooth_up / (smooth_up + smooth_down));
  if (r > max)
  {
    max = r;
    maxi = rsi->index;
  }
  else
    if (maxi == rsi->index)
  {
    max = r;
    int j;
    for (j = 0; j < rsi->size; j += 1)
    {
      if (j == rsi->index)
      {
        continue;
      }
      if (rsi->vals[j] > max)
      {
        max = rsi->vals[j];
        maxi = j;
      }
    }

  }
  if (r < min)
  {
    min = r;
    mini = rsi->index;
  }
  else
    if (mini == rsi->index)
  {
    min = r;
    int j;
    for (j = 0; j < rsi->size; j += 1)
    {
      if (j == rsi->index)
      {
        continue;
      }
      if (rsi->vals[j] < min)
      {
        min = rsi->vals[j];
        mini = j;
      }
    }

  }
  do
  {
    rsi->vals[rsi->index] = r;
    rsi->index = rsi->index + 1;
    if (rsi->index >= rsi->size)
    {
      rsi->index = 0;
    }
  }
  while (0);
  if (i > ((period * 2) - 2))
  {
    const double diff = max - min;
    if (diff == 0.0)
    {
      output[output_idx] = 0.0;
      output_idx += 1;
    }
    else
    {
      output[output_idx] = (r - min) / diff;
      output_idx += 1;
    }
  }
  *output_idx_ref = output_idx;
  *smooth_up_ref = smooth_up;
  *smooth_down_ref = smooth_down;
  *r_ref = r;
  *min_ref = min;
  *max_ref = max;
  *mini_ref = mini;
  *maxi_ref = maxi;
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


int ti_stochrsi(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double per = 1.0 / ((double) period);
  if (period < 2)
  {
    return 1;
  }
  if (size <= ti_stochrsi_start(options))
  {
    return 0;
  }
  ti_buffer *rsi = ti_buffer_new(period);
  double smooth_up = 0;
  double smooth_down = 0;
  int i;
  for (i = 1; i <= period; i += 1)
  {
    const double upward = (input[i] > input[i - 1]) ? (input[i] - input[i - 1]) : (0);
    const double downward = (input[i] < input[i - 1]) ? (input[i - 1] - input[i]) : (0);
    smooth_up += upward;
    smooth_down += downward;
  }

  smooth_up /= period;
  smooth_down /= period;
  double r = 100.0 * (smooth_up / (smooth_up + smooth_down));
  do
  {
    if (rsi->pushes >= rsi->size)
    {
      rsi->sum -= rsi->vals[rsi->index];
    }
    rsi->sum += r;
    rsi->vals[rsi->index] = r;
    rsi->pushes += 1;
    rsi->index = rsi->index + 1;
    if (rsi->index >= rsi->size)
    {
      rsi->index = 0;
    }
  }
  while (0);
  double min = r;
  double max = r;
  int mini = 0;
  int maxi = 0;
  for (i = period + 1; i < size; i += 1)
  {
    helper_ti_stochrsi_1(&output_idx, &smooth_up, &smooth_down, &r, &min, &max, &mini, &maxi, input, period, output, per, rsi, i);
  }

  ti_buffer_free(rsi);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_stochrsi_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
int ti_stochrsi_start(const double *options)
{
  return (((int) options[0]) * 2) - 1;
}


----------------------------
void helper_ti_stochrsi_1(unsigned int * const output_idx_ref, double * const smooth_up_ref, double * const smooth_down_ref, double * const r_ref, double * const min_ref, double * const max_ref, int * const mini_ref, int * const maxi_ref, const double * const input, const int period, double * const output, const double per, ti_buffer * const rsi, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double smooth_up = *smooth_up_ref;
  double smooth_down = *smooth_down_ref;
  double r = *r_ref;
  double min = *min_ref;
  double max = *max_ref;
  int mini = *mini_ref;
  int maxi = *maxi_ref;
  const double upward = (input[i] > input[i - 1]) ? (input[i] - input[i - 1]) : (0);
  const double downward = (input[i] < input[i - 1]) ? (input[i - 1] - input[i]) : (0);
  smooth_up = ((upward - smooth_up) * per) + smooth_up;
  smooth_down = ((downward - smooth_down) * per) + smooth_down;
  r = 100.0 * (smooth_up / (smooth_up + smooth_down));
  if (r > max)
  {
    max = r;
    maxi = rsi->index;
  }
  else
    if (maxi == rsi->index)
  {
    max = r;
    int j;
    for (j = 0; j < rsi->size; j += 1)
    {
      if (j == rsi->index)
      {
        continue;
      }
      if (rsi->vals[j] > max)
      {
        max = rsi->vals[j];
        maxi = j;
      }
    }

  }
  if (r < min)
  {
    min = r;
    mini = rsi->index;
  }
  else
    if (mini == rsi->index)
  {
    min = r;
    int j;
    for (j = 0; j < rsi->size; j += 1)
    {
      if (j == rsi->index)
      {
        continue;
      }
      if (rsi->vals[j] < min)
      {
        min = rsi->vals[j];
        mini = j;
      }
    }

  }
  do
  {
    rsi->vals[rsi->index] = r;
    rsi->index = rsi->index + 1;
    if (rsi->index >= rsi->size)
    {
      rsi->index = 0;
    }
  }
  while (0);
  if (i > ((period * 2) - 2))
  {
    const double diff = max - min;
    if (diff == 0.0)
    {
      output[output_idx] = 0.0;
      output_idx += 1;
    }
    else
    {
      output[output_idx] = (r - min) / diff;
      output_idx += 1;
    }
  }
  *output_idx_ref = output_idx;
  *smooth_up_ref = smooth_up;
  *smooth_down_ref = smooth_down;
  *r_ref = r;
  *min_ref = min;
  *max_ref = max;
  *mini_ref = mini;
  *maxi_ref = maxi;
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


