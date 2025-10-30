int ti_marketfi_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_marketfi(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *volume = inputs[2];
  (void) options;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (size <= ti_marketfi_start(options))
  {
    return 0;
  }
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[output_idx] = (high[i] - low[i]) / volume[i];
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_marketfi_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_marketfi_start(const double *options)
{
  (void) options;
  return 0;
}


----------------------------
***/


