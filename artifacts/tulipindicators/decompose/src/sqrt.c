int ti_sqrt_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_sqrt(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *in1 = inputs[0];
  (void) options;
  double *output = outputs[0];
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[i] = sqrt(in1[i]);
  }

  return 0;
}


/*** DEPENDENCIES:
***/


