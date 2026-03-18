int ti_nvi_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_nvi(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *close = inputs[0];
  const double *volume = inputs[1];
  (void) options;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (size <= ti_nvi_start(options))
  {
    return 0;
  }
  double nvi = 1000;
  output[output_idx] = nvi;
  output_idx += 1;
  int i;
  for (i = 1; i < size; i += 1)
  {
    if (volume[i] < volume[i - 1])
    {
      nvi += ((close[i] - close[i - 1]) / close[i - 1]) * nvi;
    }
    output[output_idx] = nvi;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_nvi_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_nvi_start(const double *options)
{
  (void) options;
  return 0;
}


----------------------------
***/


