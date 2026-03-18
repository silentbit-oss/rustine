int ti_atr_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_atr(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_atr_start(options))
  {
    return 0;
  }
  const double per = 1.0 / ((double) period);
  double sum = 0;
  double truerange;
  sum += high[0] - low[0];
  int i;
  for (i = 1; i < period; i += 1)
  {
    do
    {
      const double l = low[i];
      const double h = high[i];
      const double c = close[i - 1];
      const double ych = fabs(h - c);
      const double ycl = fabs(l - c);
      double v = h - l;
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    sum += truerange;
  }

  double val = sum / period;
  output[output_idx] = val;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    do
    {
      const double l = low[i];
      const double h = high[i];
      const double c = close[i - 1];
      const double ych = fabs(h - c);
      const double ycl = fabs(l - c);
      double v = h - l;
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    val = ((truerange - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_atr_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_atr_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


void ti_atr_stream_free(ti_stream *stream)
{
  free(stream);
}


/*** DEPENDENCIES:
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int']
void helper_ti_atr_stream_run_1(unsigned int * const output_idx_ref, int size, ti_stream_atr * const stream, const double * const high, const double * const low, const double * const close, double * const output, const double per, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double val = stream->last;
  while (i < size)
  {
    double truerange;
    do
    {
      const double ych = fabs(high[i] - stream->last_close);
      const double ycl = fabs(low[i] - stream->last_close);
      double v = high[i] - low[i];
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    val = ((truerange - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
    stream->last_close = close[i];
    stream->progress += 1;
    ++i;
  }

  stream->last = val;
  *output_idx_ref = output_idx;
}


/*** DEPENDENCIES:
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
typedef struct ti_stream_atr
{
  int index;
  int progress;
  int period;
  double sum;
  double last;
  double last_close;
} ti_stream_atr
----------------------------
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to int']
void helper_ti_atr_stream_run_2(unsigned int * const output_idx_ref, int * const i_ref, int size, ti_stream_atr * const stream, const double * const high, const double * const low, const double * const close, double * const output, const double per, const int start)
{
  unsigned int output_idx = *output_idx_ref;
  int i = *i_ref;
  if (stream->progress == start)
  {
    stream->sum = high[0] - low[0];
    stream->last_close = close[0];
    stream->progress += 1;
    i += 1;
  }
  while ((stream->progress <= 0) && (i < size))
  {
    double truerange;
    do
    {
      const double ych = fabs(high[i] - stream->last_close);
      const double ycl = fabs(low[i] - stream->last_close);
      double v = high[i] - low[i];
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    stream->sum += truerange;
    stream->last_close = close[i];
    stream->progress += 1;
    i += 1;
  }

  if (stream->progress == 1)
  {
    const double val = stream->sum * per;
    stream->last = val;
    output[output_idx] = val;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *i_ref = i;
}


/*** DEPENDENCIES:
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
typedef struct ti_stream_atr
{
  int index;
  int progress;
  int period;
  double sum;
  double last;
  double last_close;
} ti_stream_atr
----------------------------
***/


int ti_atr_stream_new(const double *options, ti_stream **stream_in)
{
  ti_stream_atr **stream = (ti_stream_atr **) stream_in;
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  *stream = malloc(sizeof(ti_stream_atr));
  if (!(*stream))
  {
    return 2;
  }
  (*stream)->index = 13;
  (*stream)->progress = -ti_atr_start(options);
  (*stream)->period = period;
  (*stream)->sum = 0.0;
  return 0;
}


/*** DEPENDENCIES:
int ti_atr_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
typedef struct ti_stream_atr
{
  int index;
  int progress;
  int period;
  double sum;
  double last;
  double last_close;
} ti_stream_atr
----------------------------
***/


int ti_atr_stream_run(ti_stream *stream_in, int size, const double * const *inputs, double * const *outputs)
{
  ti_stream_atr *stream = (ti_stream_atr *) stream_in;
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double per = 1.0 / ((double) stream->period);
  const int start = -(stream->period - 1);
  int i = 0;
  if (stream->progress < 1)
  {
    helper_ti_atr_stream_run_2(&output_idx, &i, size, stream, high, low, close, output, per, start);
  }
  if (stream->progress >= 1)
  {
    helper_ti_atr_stream_run_1(&output_idx, size, stream, high, low, close, output, per, i);
  }
  return 0;
}


/*** DEPENDENCIES:
void helper_ti_atr_stream_run_1(unsigned int * const output_idx_ref, int size, ti_stream_atr * const stream, const double * const high, const double * const low, const double * const close, double * const output, const double per, int i)
{
  unsigned int output_idx = *output_idx_ref;
  double val = stream->last;
  while (i < size)
  {
    double truerange;
    do
    {
      const double ych = fabs(high[i] - stream->last_close);
      const double ycl = fabs(low[i] - stream->last_close);
      double v = high[i] - low[i];
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    val = ((truerange - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
    stream->last_close = close[i];
    stream->progress += 1;
    ++i;
  }

  stream->last = val;
  *output_idx_ref = output_idx;
}


----------------------------
typedef struct ti_stream_atr
{
  int index;
  int progress;
  int period;
  double sum;
  double last;
  double last_close;
} ti_stream_atr
----------------------------
void helper_ti_atr_stream_run_2(unsigned int * const output_idx_ref, int * const i_ref, int size, ti_stream_atr * const stream, const double * const high, const double * const low, const double * const close, double * const output, const double per, const int start)
{
  unsigned int output_idx = *output_idx_ref;
  int i = *i_ref;
  if (stream->progress == start)
  {
    stream->sum = high[0] - low[0];
    stream->last_close = close[0];
    stream->progress += 1;
    i += 1;
  }
  while ((stream->progress <= 0) && (i < size))
  {
    double truerange;
    do
    {
      const double ych = fabs(high[i] - stream->last_close);
      const double ycl = fabs(low[i] - stream->last_close);
      double v = high[i] - low[i];
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    stream->sum += truerange;
    stream->last_close = close[i];
    stream->progress += 1;
    i += 1;
  }

  if (stream->progress == 1)
  {
    const double val = stream->sum * per;
    stream->last = val;
    output[output_idx] = val;
    output_idx += 1;
  }
  *output_idx_ref = output_idx;
  *i_ref = i;
}


----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


int ti_atr_ref(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_atr_start(options))
  {
    return 0;
  }
  const int tr_start = ti_tr_start(options);
  const int tr_size = size - tr_start;
  double *truerange = malloc(((unsigned int) tr_size) * (sizeof(double)));
  if (!truerange)
  {
    return 2;
  }
  double *tr_outputs[1] = {truerange};
  const int tr_ret = ti_tr(size, inputs, 0, tr_outputs);
  if (tr_ret != 0)
  {
    free(truerange);
    return tr_ret;
  }
  const double *wilders_inputs[1] = {truerange};
  const int wilders_ret = ti_wilders(tr_size, wilders_inputs, options, outputs);
  free(truerange);
  assert((size - ti_atr_start(options)) == (size - ti_wilders_start(options)));
  return wilders_ret;
}


/*** DEPENDENCIES:
int ti_wilders(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_wilders_start(options))
  {
    return 0;
  }
  const double per = 1.0 / ((double) period);
  double sum = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i];
  }

  double val = sum / period;
  output[output_idx] = val;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    val = ((input[i] - val) * per) + val;
    output[output_idx] = val;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_wilders_start(options)));
  return 0;
}


----------------------------
int ti_atr_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
int ti_tr(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *high = inputs[0];
  const double *low = inputs[1];
  const double *close = inputs[2];
  (void) options;
  double *output = outputs[0];
  double truerange;
  output[0] = high[0] - low[0];
  int i;
  for (i = 1; i < size; i += 1)
  {
    do
    {
      const double l = low[i];
      const double h = high[i];
      const double c = close[i - 1];
      const double ych = fabs(h - c);
      const double ycl = fabs(l - c);
      double v = h - l;
      if (ych > v)
      {
        v = ych;
      }
      if (ycl > v)
      {
        v = ycl;
      }
      truerange = v;
    }
    while (0);
    output[i] = truerange;
  }

  return 0;
}


----------------------------
int ti_wilders_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
int ti_tr_start(const double *options)
{
  (void) options;
  return 0;
}


----------------------------
***/


