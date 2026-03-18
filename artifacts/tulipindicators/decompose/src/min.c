int ti_min_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_min(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_min_start(options))
  {
    return 0;
  }
  int trail = 0;
  int mini = -1;
  double min = input[0];
  int i;
  int j;
  for (i = period - 1; i < size; i += 1, trail += 1)
  {
    double bar = input[i];
    if (mini < trail)
    {
      mini = trail;
      min = input[mini];
      j = trail;
      while ((++j) <= i)
      {
        bar = input[j];
        if (bar <= min)
        {
          min = bar;
          mini = j;
        }
      }

    }
    else
      if (bar <= min)
    {
      mini = i;
      min = bar;
    }
    output[output_idx] = min;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_min_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_min_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


int ti_min_ref(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_min_start(options))
  {
    return 0;
  }
  for (int i = period - 1; i < size; i += 1)
  {
    double min = input[(i - period) + 1];
    for (int j = (i - period) + 2; j <= i; j += 1)
    {
      min = (min < input[j]) ? (min) : (input[j]);
    }

    output[output_idx] = min;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_min_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_min_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


