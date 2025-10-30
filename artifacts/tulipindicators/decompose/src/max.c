int ti_max_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_max(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_max_start(options))
  {
    return 0;
  }
  int trail = 0;
  int maxi = -1;
  double max = input[0];
  int i;
  int j;
  for (i = period - 1; i < size; i += 1, trail += 1)
  {
    double bar = input[i];
    if (maxi < trail)
    {
      maxi = trail;
      max = input[maxi];
      j = trail;
      while ((++j) <= i)
      {
        bar = input[j];
        if (bar >= max)
        {
          max = bar;
          maxi = j;
        }
      }

    }
    else
      if (bar >= max)
    {
      maxi = i;
      max = bar;
    }
    output[output_idx] = max;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_max_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_max_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


int ti_max_ref(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_max_start(options))
  {
    return 0;
  }
  for (int i = period - 1; i < size; i += 1)
  {
    double max = input[(i - period) + 1];
    for (int j = (i - period) + 2; j <= i; j += 1)
    {
      max = (max > input[j]) ? (max) : (input[j]);
    }

    output[output_idx] = max;
    output_idx += 1;
  }

  return 0;
}


/*** DEPENDENCIES:
int ti_max_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


