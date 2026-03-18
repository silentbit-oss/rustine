int ti_trima_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_trima(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_trima_start(options))
  {
    return 0;
  }
  if (period <= 2)
  {
    return ti_sma(size, inputs, options, outputs);
  }
  double weights = 1 / ((double) ((period % 2) ? (((period / 2) + 1) * ((period / 2) + 1)) : (((period / 2) + 1) * (period / 2))));
  double weight_sum = 0;
  double lead_sum = 0;
  double trail_sum = 0;
  const int lead_period = (period % 2) ? (period / 2) : ((period / 2) - 1);
  const int trail_period = lead_period + 1;
  int i;
  int w = 1;
  for (i = 0; i < (period - 1); i += 1)
  {
    weight_sum += input[i] * w;
    if ((i + 1) > (period - lead_period))
    {
      lead_sum += input[i];
    }
    if ((i + 1) <= trail_period)
    {
      trail_sum += input[i];
    }
    if ((i + 1) < trail_period)
    {
      w += 1;
    }
    if ((i + 1) >= (period - lead_period))
    {
      w -= 1;
    }
  }

  int lsi = ((period - 1) - lead_period) + 1;
  int tsi1 = (((period - 1) - period) + 1) + trail_period;
  int tsi2 = ((period - 1) - period) + 1;
  for (i = period - 1; i < size; i += 1)
  {
    weight_sum += input[i];
    output[output_idx] = weight_sum * weights;
    output_idx += 1;
    lead_sum += input[i];
    weight_sum += lead_sum;
    weight_sum -= trail_sum;
    lead_sum -= input[lsi];
    lsi += 1;
    trail_sum += input[tsi1++];
    trail_sum -= input[tsi2++];
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_trima_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_sma(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double scale = 1.0 / period;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_sma_start(options))
  {
    return 0;
  }
  double sum = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i];
  }

  output[output_idx] = sum * scale;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    sum += input[i];
    sum -= input[i - period];
    output[output_idx] = sum * scale;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_sma_start(options)));
  return 0;
}


----------------------------
int ti_trima_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


