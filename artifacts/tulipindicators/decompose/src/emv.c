int ti_emv_start(const double *options)
{
  (void) options;
  return 1;
}


/*** DEPENDENCIES:
***/


int ti_emv(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *volume = inputs[2];
  (void) options;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (size <= ti_emv_start(options))
  {
    return 0;
  }
  double last = (high[0] + low[0]) * 0.5;
  int i;
  for (i = 1; i < size; i += 1)
  {
    double hl = (high[i] + low[i]) * 0.5;
    double br = (volume[i] / 10000.0) / (high[i] - low[i]);
    output[output_idx] = (hl - last) / br;
    output_idx += 1;
    last = hl;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_emv_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_emv_start(const double *options)
{
  (void) options;
  return 1;
}


----------------------------
***/


