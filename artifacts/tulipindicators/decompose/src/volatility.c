int ti_volatility_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


int ti_volatility(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const int period = (int) options[0];
  const double scale = 1.0 / period;
  const double annual = sqrt(252);
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_volatility_start(options))
  {
    return 0;
  }
  double sum = 0;
  double sum2 = 0;
  int i;
  for (i = 1; i <= period; i += 1)
  {
    const double c = (input[i] / input[i - 1]) - 1.0;
    sum += c;
    sum2 += c * c;
  }

  output[output_idx] = sqrt((sum2 * scale) - ((sum * scale) * (sum * scale))) * annual;
  output_idx += 1;
  for (i = period + 1; i < size; i += 1)
  {
    const double c = (input[i] / input[i - 1]) - 1.0;
    sum += c;
    sum2 += c * c;
    const double cp = (input[i - period] / input[(i - period) - 1]) - 1.0;
    sum -= cp;
    sum2 -= cp * cp;
    output[output_idx] = sqrt((sum2 * scale) - ((sum * scale) * (sum * scale))) * annual;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_volatility_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_volatility_start(const double *options)
{
  return (int) options[0];
}


----------------------------
***/


