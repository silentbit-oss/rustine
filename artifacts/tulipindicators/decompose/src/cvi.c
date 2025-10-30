int ti_cvi_start(const double *options)
{
  const int n = (int) options[0];
  return (n * 2) - 1;
}


/*** DEPENDENCIES:
***/


int ti_cvi(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_cvi_start(options))
  {
    return 0;
  }
  const double per = 2 / (((double) period) + 1);
  ti_buffer *lag = ti_buffer_new(period);
  double val = high[0] - low[0];
  int i;
  for (i = 1; i < ((period * 2) - 1); i += 1)
  {
    val = (((high[i] - low[i]) - val) * per) + val;
    do
    {
      lag->vals[lag->index] = val;
      lag->index = lag->index + 1;
      if (lag->index >= lag->size)
      {
        lag->index = 0;
      }
    }
    while (0);
  }

  for (i = (period * 2) - 1; i < size; i += 1)
  {
    val = (((high[i] - low[i]) - val) * per) + val;
    const double old = lag->vals[lag->index];
    output[output_idx] = (100.0 * (val - old)) / old;
    output_idx += 1;
    do
    {
      lag->vals[lag->index] = val;
      lag->index = lag->index + 1;
      if (lag->index >= lag->size)
        lag->index = 0;
    }
    while (0);
  }

  ti_buffer_free(lag);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_cvi_start(options)));
  return 0;
}


/*** DEPENDENCIES:
ti_buffer *ti_buffer_new(int size)
{
  const int s = ((int) (sizeof(ti_buffer))) + ((size - 1) * ((int) (sizeof(double))));
  ti_buffer *ret = (ti_buffer *) malloc((unsigned int) s);
  ret->size = size;
  ret->pushes = 0;
  ret->index = 0;
  ret->sum = 0;
  return ret;
}


----------------------------
int ti_cvi_start(const double *options)
{
  const int n = (int) options[0];
  return (n * 2) - 1;
}


----------------------------
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer
----------------------------
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
***/


