int ti_mfi_start(const double *options)
{
  return (int) options[0];
}


/*** DEPENDENCIES:
***/


void helper_helper_ti_mfi_1_1(ti_buffer * const up, ti_buffer * const down, const double bar)
{
  do
  {
    if (up->pushes >= up->size)
    {
      up->sum -= up->vals[up->index];
    }
    up->sum += bar;
    up->vals[up->index] = bar;
    up->pushes += 1;
    up->index = up->index + 1;
    if (up->index >= up->size)
    {
      up->index = 0;
    }
  }
  while (0);
  do
  {
    if (down->pushes >= down->size)
    {
      down->sum -= down->vals[down->index];
    }
    down->sum += 0.0;
    down->vals[down->index] = 0.0;
    down->pushes += 1;
    down->index = down->index + 1;
    if (down->index >= down->size)
    {
      down->index = 0;
    }
  }
  while (0);
}


/*** DEPENDENCIES:
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer
----------------------------
***/


void helper_helper_ti_mfi_1_2(ti_buffer * const up, ti_buffer * const down, const double bar)
{
  do
  {
    if (down->pushes >= down->size)
    {
      down->sum -= down->vals[down->index];
    }
    down->sum += bar;
    down->vals[down->index] = bar;
    down->pushes += 1;
    down->index = down->index + 1;
    if (down->index >= down->size)
    {
      down->index = 0;
    }
  }
  while (0);
  do
  {
    if (up->pushes >= up->size)
    {
      up->sum -= up->vals[up->index];
    }
    up->sum += 0.0;
    up->vals[up->index] = 0.0;
    up->pushes += 1;
    up->index = up->index + 1;
    if (up->index >= up->size)
    {
      up->index = 0;
    }
  }
  while (0);
}


/*** DEPENDENCIES:
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer
----------------------------
***/


void helper_helper_ti_mfi_1_3(ti_buffer * const up, ti_buffer * const down)
{
  do
  {
    if (up->pushes >= up->size)
    {
      up->sum -= up->vals[up->index];
    }
    up->sum += 0.0;
    up->vals[up->index] = 0.0;
    up->pushes += 1;
    up->index = up->index + 1;
    if (up->index >= up->size)
    {
      up->index = 0;
    }
  }
  while (0);
  do
  {
    if (down->pushes >= down->size)
    {
      down->sum -= down->vals[down->index];
    }
    down->sum += 0.0;
    down->vals[down->index] = 0.0;
    down->pushes += 1;
    down->index = down->index + 1;
    if (down->index >= down->size)
    {
      down->index = 0;
    }
  }
  while (0);
}


/*** DEPENDENCIES:
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer
----------------------------
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'ytyp_ref is a mutable refrence to double']
void helper_ti_mfi_1(unsigned int * const output_idx_ref, double * const ytyp_ref, const double * const high, const double * const low, const double * const close, const double * const volume, const int period, double * const output, int i, ti_buffer * const up, ti_buffer * const down)
{
  unsigned int output_idx = *output_idx_ref;
  double ytyp = *ytyp_ref;
  const double typ = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
  const double bar = typ * volume[i];
  if (typ > ytyp)
  {
    helper_helper_ti_mfi_1_1(up, down, bar);
  }
  else
    if (typ < ytyp)
  {
    helper_helper_ti_mfi_1_2(up, down, bar);
  }
  else
  {
    helper_helper_ti_mfi_1_3(up, down);
  }
  ytyp = typ;
  if (i >= period)
  {
    output[output_idx] = (up->sum / (up->sum + down->sum)) * 100.0;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *ytyp_ref = ytyp;
}


/*** DEPENDENCIES:
void helper_helper_ti_mfi_1_1(ti_buffer * const up, ti_buffer * const down, const double bar)
{
  do
  {
    if (up->pushes >= up->size)
    {
      up->sum -= up->vals[up->index];
    }
    up->sum += bar;
    up->vals[up->index] = bar;
    up->pushes += 1;
    up->index = up->index + 1;
    if (up->index >= up->size)
    {
      up->index = 0;
    }
  }
  while (0);
  do
  {
    if (down->pushes >= down->size)
    {
      down->sum -= down->vals[down->index];
    }
    down->sum += 0.0;
    down->vals[down->index] = 0.0;
    down->pushes += 1;
    down->index = down->index + 1;
    if (down->index >= down->size)
    {
      down->index = 0;
    }
  }
  while (0);
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
void helper_helper_ti_mfi_1_3(ti_buffer * const up, ti_buffer * const down)
{
  do
  {
    if (up->pushes >= up->size)
    {
      up->sum -= up->vals[up->index];
    }
    up->sum += 0.0;
    up->vals[up->index] = 0.0;
    up->pushes += 1;
    up->index = up->index + 1;
    if (up->index >= up->size)
    {
      up->index = 0;
    }
  }
  while (0);
  do
  {
    if (down->pushes >= down->size)
    {
      down->sum -= down->vals[down->index];
    }
    down->sum += 0.0;
    down->vals[down->index] = 0.0;
    down->pushes += 1;
    down->index = down->index + 1;
    if (down->index >= down->size)
    {
      down->index = 0;
    }
  }
  while (0);
}


----------------------------
void helper_helper_ti_mfi_1_2(ti_buffer * const up, ti_buffer * const down, const double bar)
{
  do
  {
    if (down->pushes >= down->size)
    {
      down->sum -= down->vals[down->index];
    }
    down->sum += bar;
    down->vals[down->index] = bar;
    down->pushes += 1;
    down->index = down->index + 1;
    if (down->index >= down->size)
    {
      down->index = 0;
    }
  }
  while (0);
  do
  {
    if (up->pushes >= up->size)
    {
      up->sum -= up->vals[up->index];
    }
    up->sum += 0.0;
    up->vals[up->index] = 0.0;
    up->pushes += 1;
    up->index = up->index + 1;
    if (up->index >= up->size)
    {
      up->index = 0;
    }
  }
  while (0);
}


----------------------------
***/


int ti_mfi(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const double *volume = inputs[3];
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_mfi_start(options))
  {
    return 0;
  }
  double *output = outputs[0];
  unsigned int output_idx = 0;
  double ytyp = ((high[0] + low[0]) + close[0]) * (1.0 / 3.0);
  int i;
  ti_buffer *up = ti_buffer_new(period);
  ti_buffer *down = ti_buffer_new(period);
  for (i = 1; i < size; i += 1)
  {
    helper_ti_mfi_1(&output_idx, &ytyp, high, low, close, volume, period, output, i, up, down);
  }

  ti_buffer_free(up);
  ti_buffer_free(down);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_mfi_start(options)));
  return 0;
}


/*** DEPENDENCIES:
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
int ti_mfi_start(const double *options)
{
  return (int) options[0];
}


----------------------------
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
void helper_ti_mfi_1(unsigned int * const output_idx_ref, double * const ytyp_ref, const double * const high, const double * const low, const double * const close, const double * const volume, const int period, double * const output, int i, ti_buffer * const up, ti_buffer * const down)
{
  unsigned int output_idx = *output_idx_ref;
  double ytyp = *ytyp_ref;
  const double typ = ((high[i] + low[i]) + close[i]) * (1.0 / 3.0);
  const double bar = typ * volume[i];
  if (typ > ytyp)
  {
    helper_helper_ti_mfi_1_1(up, down, bar);
  }
  else
    if (typ < ytyp)
  {
    helper_helper_ti_mfi_1_2(up, down, bar);
  }
  else
  {
    helper_helper_ti_mfi_1_3(up, down);
  }
  ytyp = typ;
  if (i >= period)
  {
    output[output_idx] = (up->sum / (up->sum + down->sum)) * 100.0;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *ytyp_ref = ytyp;
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
***/


