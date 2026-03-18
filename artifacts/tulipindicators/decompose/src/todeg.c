int ti_todeg_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_todeg(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *in1 = inputs[0];
  (void) options;
  double *output = outputs[0];
  int i;
  for (i = 0; i < size; i += 1)
  {
    output[i] = in1[i] * (180.0 / 3.14159265358979323846);
  }

  return 0;
}


/*** DEPENDENCIES:
***/


