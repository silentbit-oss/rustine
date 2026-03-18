int ti_ln_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_ln(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *in1 = inputs[0];
  (void) options;
  double *output = outputs[0];
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[i] = log(in1[i]);
  }

  return 0;
}


/*** DEPENDENCIES:
***/


