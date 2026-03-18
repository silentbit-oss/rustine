int ti_wad_start(const double *options)
{
  (void) options;
  return 1;
}


/*** DEPENDENCIES:
***/


int ti_wad(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  (void) options;
  if (size <= ti_wad_start(options))
  {
    return 0;
  }
  double *output = outputs[0];
  unsigned int output_idx = 0;
  double sum = 0;
  double yc = close[0];
  int i;
  for (i = 1; i < size; i += 1)
  {
    const double c = close[i];
    if (c > yc)
    {
      sum += c - ((yc < low[i]) ? (yc) : (low[i]));
    }
    else
      if (c < yc)
    {
      sum += c - ((yc > high[i]) ? (yc) : (high[i]));
    }
    else
    {
    }
    output[output_idx] = sum;
    output_idx += 1;
    yc = close[i];
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_wad_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_wad_start(const double *options)
{
  (void) options;
  return 1;
}


----------------------------
***/


