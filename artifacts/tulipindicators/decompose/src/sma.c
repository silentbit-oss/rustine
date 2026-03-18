int ti_sma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


/*** DEPENDENCIES:
***/


int ti_sma(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  const double scale = 1.0 / period;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_sma_start(options))
  {
    return 0;
  }
  double sum = 0;
  int i;
  for (i = 0; i < period; i += 1)
  {
    sum += input[i];
  }

  output[output_idx] = sum * scale;
  output_idx += 1;
  for (i = period; i < size; i += 1)
  {
    sum += input[i];
    sum -= input[i - period];
    output[output_idx] = sum * scale;
    output_idx += 1;
  }

  assert(((&output[output_idx]) - outputs[0]) == (size - ti_sma_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_sma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
***/


void ti_sma_stream_free(ti_stream *stream)
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


int ti_sma_stream_run(ti_stream *stream_in, int size, const double * const *inputs, double * const *outputs)
{
  ti_stream_sma *stream = (ti_stream_sma *) stream_in;
  int progress = stream->progress;
  const double *real = inputs[0];
  int period = stream->period;
  double *sma = outputs[0];
  unsigned int sma_idx = 0;
  double per = stream->per;
  double sum = stream->sum;
  int buffer_idx = stream->buffer_idx;
  double *buffer = stream->buffer;
  if (progress == ((-period) + 1))
  {
  }
  else
  {
  }
  int i;
  for (i = 0; (progress < 1) && (i < size); i += 1, progress += 1)
  {
    {
      buffer_idx += 1;
      sum += (buffer[buffer_idx] = real[i] * per);
    }
    ;
  }

  if ((i > 0) && (progress == 1))
  {
    sma[sma_idx] = sum;
    sma_idx += 1;
  }
  for (; i < size; i += 1, progress += 1)
  {
    {
      buffer_idx += 1;
      if (buffer_idx == period)
      {
        buffer_idx = 0;
      }
      sum -= buffer[buffer_idx];
      sum += (buffer[buffer_idx] = real[i] * per);
    }
    ;
    sma[sma_idx] = sum;
    sma_idx += 1;
  }

  stream->progress = progress;
  stream->sum = sum;
  stream->buffer_idx = buffer_idx;
  return 0;
}


/*** DEPENDENCIES:
typedef struct ti_stream_sma
{
  int index;
  int progress;
  int period;
  double per;
  double sum;
  int buffer_idx;
  double buffer[];
} ti_stream_sma
----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


int ti_sma_stream_new(const double *options, ti_stream **stream_in)
{
  ti_stream_sma **stream = (ti_stream_sma **) stream_in;
  int period = (int) options[0];
  if (period < 1)
  {
    return 1;
  }
  *stream = malloc((sizeof(ti_stream_sma)) + ((sizeof(double)) * period));
  if (!stream)
  {
    return 2;
  }
  (*stream)->index = 72;
  (*stream)->progress = -ti_sma_start(options);
  (*stream)->period = period;
  (*stream)->per = 1. / period;
  (*stream)->sum = 0.;
  (*stream)->buffer_idx = -1;
  return 0;
}


/*** DEPENDENCIES:
int ti_sma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
typedef struct ti_stream_sma
{
  int index;
  int progress;
  int period;
  double per;
  double sum;
  int buffer_idx;
  double buffer[];
} ti_stream_sma
----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


