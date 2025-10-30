int ti_bbands_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_bbands(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *lower = outputs[0];
  unsigned int lower_idx = 0;
  double *middle = outputs[1];
  unsigned int middle_idx = 0;
  double *upper = outputs[2];
  unsigned int upper_idx = 0;
  const int period = (int) options[0];
  const double stddev = options[1];
  const double scale = 1.0 / period;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_bbands_start(options))
  {
    return 0;
  }
  double sum = 0;
  double sum2 = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i];
    sum2 += input[i] * input[i];
  }

  double sd = sqrt((sum2 * scale) - ((sum * scale) * (sum * scale)));
  middle[middle_idx] = sum * scale;
  lower[lower_idx] = middle[middle_idx] - (stddev * sd);
  lower_idx += 1;
  upper[upper_idx] = middle[middle_idx] + (stddev * sd);
  upper_idx += 1;
  middle_idx += 1;
  for (i = period; i < size; i += 1)
  {
    sum += input[i];
    sum2 += input[i] * input[i];
    sum -= input[i - period];
    sum2 -= input[i - period] * input[i - period];
    sd = sqrt((sum2 * scale) - ((sum * scale) * (sum * scale)));
    middle[middle_idx] = sum * scale;
    upper[upper_idx] = middle[middle_idx] + (stddev * sd);
    upper_idx += 1;
    lower[lower_idx] = middle[middle_idx] - (stddev * sd);
    lower_idx += 1;
    ++(&middle[middle_idx]);
  }

  assert(((&lower[lower_idx]) - outputs[0]) == (size - ti_bbands_start(options)));
  assert(((&middle[middle_idx]) - outputs[1]) == (size - ti_bbands_start(options)));
  assert(((&upper[upper_idx]) - outputs[2]) == (size - ti_bbands_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_bbands_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


