int ti_rsi_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


int ti_rsi(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double per = 1.0 / ((double) period);
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_rsi_start(options))
  {
    return 0;
  }
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
  output[output_idx] = 100.0 * (smooth_up / (smooth_up + smooth_down));
  output_idx += 1;
  for (i = period + 1; i < size; i += 1)
  {
    const double upward = (input[i] > input[i - 1]) ? (input[i] - input[i - 1]) : (0);
    const double downward = (input[i] < input[i - 1]) ? (input[i - 1] - input[i]) : (0);
    smooth_up = ((upward - smooth_up) * per) + smooth_up;
    smooth_down = ((downward - smooth_down) * per) + smooth_down;
    output[output_idx] = 100.0 * (smooth_up / (smooth_up + smooth_down));
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_rsi_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_rsi_start(const double *options)
{
  return (int) options[0];
}


----------------------------
***/


