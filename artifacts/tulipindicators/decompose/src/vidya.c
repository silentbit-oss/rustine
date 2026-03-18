int ti_vidya_start(const double *options)
{
  return ((int) options[1]) - 2;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'short_sum_ref is a mutable refrence to double', 'short_sum2_ref is a mutable refrence to double', 'long_sum_ref is a mutable refrence to double', 'long_sum2_ref is a mutable refrence to double', 'val_ref is a mutable refrence to double']
void helper_ti_vidya_1(unsigned int * const output_idx_ref, double * const short_sum_ref, double * const short_sum2_ref, double * const long_sum_ref, double * const long_sum2_ref, double * const val_ref, const double * const input, const int short_period, const int long_period, const double alpha, double * const output, const double short_div, const double long_div, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double short_sum = *short_sum_ref;
  double short_sum2 = *short_sum2_ref;
  double long_sum = *long_sum_ref;
  double long_sum2 = *long_sum2_ref;
  double val = *val_ref;
  long_sum += input[i];
  long_sum2 += input[i] * input[i];
  short_sum += input[i];
  short_sum2 += input[i] * input[i];
  long_sum -= input[i - long_period];
  long_sum2 -= input[i - long_period] * input[i - long_period];
  short_sum -= input[i - short_period];
  short_sum2 -= input[i - short_period] * input[i - short_period];
  {
    double short_stddev = sqrt((short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div)));
    double long_stddev = sqrt((long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div)));
    double k = short_stddev / long_stddev;
    if (k != k)
    {
      k = 0;
    }
    k *= alpha;
    val = ((input[i] - val) * k) + val;
    output[output_idx] = val;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *short_sum_ref = short_sum;
  *short_sum2_ref = short_sum2;
  *long_sum_ref = long_sum;
  *long_sum2_ref = long_sum2;
  *val_ref = val;
}


/*** DEPENDENCIES:
***/


int ti_vidya(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int short_period = (int) options[0];
  const int long_period = (int) options[1];
  const double alpha = options[2];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double short_div = 1.0 / short_period;
  const double long_div = 1.0 / long_period;
  if (short_period < 1)
  {
    return 1;
  }
  if (long_period < short_period)
  {
    return 1;
  }
  if (long_period < 2)
  {
    return 1;
  }
  if ((alpha < 0.0) || (alpha > 1.0))
  {
    return 1;
  }
  if (size <= ti_vidya_start(options))
  {
    return 0;
  }
  double short_sum = 0;
  double short_sum2 = 0;
  double long_sum = 0;
  double long_sum2 = 0;
  int i;
  for (i = 0; i < long_period; i += 1)
  {
    long_sum += input[i];
    long_sum2 += input[i] * input[i];
    if (i >= (long_period - short_period))
    {
      short_sum += input[i];
      short_sum2 += input[i] * input[i];
    }
  }

  double val = input[long_period - 2];
  output[output_idx] = val;
  output_idx += 1;
  if ((long_period - 1) < size)
  {
    double short_stddev = sqrt((short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div)));
    double long_stddev = sqrt((long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div)));
    double k = short_stddev / long_stddev;
    if (k != k)
    {
      k = 0;
    }
    k *= alpha;
    val = ((input[long_period - 1] - val) * k) + val;
    output[output_idx] = val;
    output_idx += 1;
  }
  for (i = long_period; i < size; i += 1)
  {
    helper_ti_vidya_1(&output_idx, &short_sum, &short_sum2, &long_sum, &long_sum2, &val, input, short_period, long_period, alpha, output, short_div, long_div, i);
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_vidya_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_vidya_start(const double *options)
{
  return ((int) options[1]) - 2;
}


----------------------------
void helper_ti_vidya_1(unsigned int * const output_idx_ref, double * const short_sum_ref, double * const short_sum2_ref, double * const long_sum_ref, double * const long_sum2_ref, double * const val_ref, const double * const input, const int short_period, const int long_period, const double alpha, double * const output, const double short_div, const double long_div, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double short_sum = *short_sum_ref;
  double short_sum2 = *short_sum2_ref;
  double long_sum = *long_sum_ref;
  double long_sum2 = *long_sum2_ref;
  double val = *val_ref;
  long_sum += input[i];
  long_sum2 += input[i] * input[i];
  short_sum += input[i];
  short_sum2 += input[i] * input[i];
  long_sum -= input[i - long_period];
  long_sum2 -= input[i - long_period] * input[i - long_period];
  short_sum -= input[i - short_period];
  short_sum2 -= input[i - short_period] * input[i - short_period];
  {
    double short_stddev = sqrt((short_sum2 * short_div) - ((short_sum * short_div) * (short_sum * short_div)));
    double long_stddev = sqrt((long_sum2 * long_div) - ((long_sum * long_div) * (long_sum * long_div)));
    double k = short_stddev / long_stddev;
    if (k != k)
    {
      k = 0;
    }
    k *= alpha;
    val = ((input[i] - val) * k) + val;
    output[output_idx] = val;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *short_sum_ref = short_sum;
  *short_sum2_ref = short_sum2;
  *long_sum_ref = long_sum;
  *long_sum2_ref = long_sum2;
  *val_ref = val;
}


----------------------------
***/


