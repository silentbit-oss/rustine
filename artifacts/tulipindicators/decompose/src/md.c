int ti_md_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_md(int size, const double * const *inputs, const double *options, double * const *outputs)
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
  if (size <= ti_md_start(options))
  {
    return 0;
  }
  double sum = 0;
  int i;
  int j;
  for (i = 0; i < size; i += 1)
  {
    const double today = input[i];
    sum += today;
    if (i >= period)
    {
      sum -= input[i - period];
    }
    const double avg = sum * scale;
    if (i >= (period - 1))
    {
      double acc = 0;
      for (j = 0; j < period; j += 1)
      {
        acc += fabs(avg - input[i - j]);
      }

      output[output_idx] = acc * scale;
      output_idx += 1;
    }
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_md_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_md_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


