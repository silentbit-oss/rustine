int ti_ao_start(const double *options)
{
  (void) options;
  return 33;
}


/*** DEPENDENCIES:
***/


int ti_ao(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const int period = 34;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (size <= ti_ao_start(options))
  {
    return 0;
  }
  double sum34 = 0;
  double sum5 = 0;
  const double per34 = 1.0 / 34.0;
  const double per5 = 1.0 / 5.0;
  int i;
  for (i = 0; i < 34; i += 1)
  {
    double hl = 0.5 * (high[i] + low[i]);
    sum34 += hl;
    if (i >= 29)
    {
      sum5 += hl;
    }
  }

  output[output_idx] = (per5 * sum5) - (per34 * sum34);
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    double hl = 0.5 * (high[i] + low[i]);
    sum34 += hl;
    sum5 += hl;
    sum34 -= 0.5 * (high[i - 34] + low[i - 34]);
    sum5 -= 0.5 * (high[i - 5] + low[i - 5]);
    output[output_idx] = (per5 * sum5) - (per34 * sum34);
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_ao_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_ao_start(const double *options)
{
  (void) options;
  return 33;
}


----------------------------
***/


