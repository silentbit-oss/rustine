int ti_decay_start(const double *options)
{
  (void) options;
  return 0;
}


/*** DEPENDENCIES:
***/


int ti_decay(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const int period = (int) options[0];
  const double scale = 1.0 / period;
  output[output_idx] = input[0];
  output_idx += 1;
  int i;
  for (i = 1; i < size; i += 1)
  {
    double d = output[(-1) + output_idx] - scale;
    output[output_idx] = (input[i] > d) ? (input[i]) : (d);
    output_idx += 1;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


