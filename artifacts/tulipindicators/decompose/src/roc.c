int ti_roc_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


int ti_roc(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_roc_start(options))
  {
    return 0;
  }
  int i;
  for (i = period; i < size; i += 1)
  {
    output[output_idx] = (input[i] - input[i - period]) / input[i - period];
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_roc_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_roc_start(const double *options)
{
  return (int) options[0];
}


----------------------------
***/


