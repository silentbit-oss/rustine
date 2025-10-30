int ti_crossover_start(const double *options)
{
  (void) options;
  return 1;
}


/*** DEPENDENCIES:
***/


int ti_crossover(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *a = inputs[0];
  const double *b = inputs[1];
  (void) options;
  double *output = outputs[0];
  unsigned int output_idx = 0;
  int i;
  for (i = 1; i < size; i += 1)
  {
    output[output_idx] = (a[i] > b[i]) && (a[i - 1] <= b[i - 1]);
    output_idx += 1;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


