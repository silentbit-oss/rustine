int ti_hma_start(const double *options)
{
  const int period = (int) options[0];
  const int periodsqrt = (int) sqrt(period);
  return (period + periodsqrt) - 2;
}


/*** DEPENDENCIES:
***/


// hint:  ['output_idx_ref is a mutable refrence to unsigned int', 'sum_ref is a mutable refrence to double', 'weight_sum_ref is a mutable refrence to double', 'sum2_ref is a mutable refrence to double', 'weight_sum2_ref is a mutable refrence to double', 'sumsqrt_ref is a mutable refrence to double', 'weight_sumsqrt_ref is a mutable refrence to double']
void helper_ti_hma_1(unsigned int * const output_idx_ref, double * const sum_ref, double * const weight_sum_ref, double * const sum2_ref, double * const weight_sum2_ref, double * const sumsqrt_ref, double * const weight_sumsqrt_ref, const double * const input, const int period, double * const output, const int period2, const int periodsqrt, const double weights, const double weights2, const double weightssqrt, int i, ti_buffer * const buff)
{
  unsigned int output_idx = *output_idx_ref;
  double sum = *sum_ref;
  double weight_sum = *weight_sum_ref;
  double sum2 = *sum2_ref;
  double weight_sum2 = *weight_sum2_ref;
  double sumsqrt = *sumsqrt_ref;
  double weight_sumsqrt = *weight_sumsqrt_ref;
  weight_sum += input[i] * period;
  sum += input[i];
  weight_sum2 += input[i] * period2;
  sum2 += input[i];
  const double wma = weight_sum / weights;
  const double wma2 = weight_sum2 / weights2;
  const double diff = (2 * wma2) - wma;
  weight_sumsqrt += diff * periodsqrt;
  sumsqrt += diff;
  do
  {
    buff->vals[buff->index] = diff;
    buff->index = buff->index + 1;
    if (buff->index >= buff->size)
    {
      buff->index = 0;
    }
  }
  while (0);
  if (i >= ((period - 1) + (periodsqrt - 1)))
  {
    output[output_idx] = weight_sumsqrt / weightssqrt;
    output_idx += 1;
    weight_sumsqrt -= sumsqrt;
    sumsqrt -= buff->vals[(((buff->index + buff->size) - 1) + 1) % buff->size];
  }
  else
  {
    weight_sumsqrt -= sumsqrt;
  }
  weight_sum -= sum;
  sum -= input[(i - period) + 1];
  weight_sum2 -= sum2;
  sum2 -= input[(i - period2) + 1];
  *output_idx_ref = output_idx;
  *sum_ref = sum;
  *weight_sum_ref = weight_sum;
  *sum2_ref = sum2;
  *weight_sum2_ref = weight_sum2;
  *sumsqrt_ref = sumsqrt;
  *weight_sumsqrt_ref = weight_sumsqrt;
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


int ti_hma(int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const double *input = inputs[0];
  const int period = (int) options[0];
  double *output = outputs[0];
  unsigned int output_idx = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size <= ti_hma_start(options))
  {
    return 0;
  }
  const int period2 = (int) (period / 2);
  const int periodsqrt = (int) sqrt(period);
  const double weights = (period * (period + 1)) / 2;
  const double weights2 = (period2 * (period2 + 1)) / 2;
  const double weightssqrt = (periodsqrt * (periodsqrt + 1)) / 2;
  double sum = 0;
  double weight_sum = 0;
  double sum2 = 0;
  double weight_sum2 = 0;
  double sumsqrt = 0;
  double weight_sumsqrt = 0;
  int i;
  for (i = 0; i < (period - 1); i += 1)
  {
    weight_sum += input[i] * (i + 1);
    sum += input[i];
    if (i >= (period - period2))
    {
      weight_sum2 += input[i] * ((i + 1) - (period - period2));
      sum2 += input[i];
    }
  }

  ti_buffer *buff = ti_buffer_new(periodsqrt);
  for (i = period - 1; i < size; i += 1)
  {
    helper_ti_hma_1(&output_idx, &sum, &weight_sum, &sum2, &weight_sum2, &sumsqrt, &weight_sumsqrt, input, period, output, period2, periodsqrt, weights, weights2, weightssqrt, i, buff);
  }

  ti_buffer_free(buff);
  assert(((&output[output_idx]) - outputs[0]) == (size - ti_hma_start(options)));
  return 0;
}


/*** DEPENDENCIES:
int ti_hma_start(const double *options)
{
  const int period = (int) options[0];
  const int periodsqrt = (int) sqrt(period);
  return (period + periodsqrt) - 2;
}


----------------------------
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
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
void helper_ti_hma_1(unsigned int * const output_idx_ref, double * const sum_ref, double * const weight_sum_ref, double * const sum2_ref, double * const weight_sum2_ref, double * const sumsqrt_ref, double * const weight_sumsqrt_ref, const double * const input, const int period, double * const output, const int period2, const int periodsqrt, const double weights, const double weights2, const double weightssqrt, int i, ti_buffer * const buff)
{
  unsigned int output_idx = *output_idx_ref;
  double sum = *sum_ref;
  double weight_sum = *weight_sum_ref;
  double sum2 = *sum2_ref;
  double weight_sum2 = *weight_sum2_ref;
  double sumsqrt = *sumsqrt_ref;
  double weight_sumsqrt = *weight_sumsqrt_ref;
  weight_sum += input[i] * period;
  sum += input[i];
  weight_sum2 += input[i] * period2;
  sum2 += input[i];
  const double wma = weight_sum / weights;
  const double wma2 = weight_sum2 / weights2;
  const double diff = (2 * wma2) - wma;
  weight_sumsqrt += diff * periodsqrt;
  sumsqrt += diff;
  do
  {
    buff->vals[buff->index] = diff;
    buff->index = buff->index + 1;
    if (buff->index >= buff->size)
    {
      buff->index = 0;
    }
  }
  while (0);
  if (i >= ((period - 1) + (periodsqrt - 1)))
  {
    output[output_idx] = weight_sumsqrt / weightssqrt;
    output_idx += 1;
    weight_sumsqrt -= sumsqrt;
    sumsqrt -= buff->vals[(((buff->index + buff->size) - 1) + 1) % buff->size];
  }
  else
  {
    weight_sumsqrt -= sumsqrt;
  }
  weight_sum -= sum;
  sum -= input[(i - period) + 1];
  weight_sum2 -= sum2;
  sum2 -= input[(i - period2) + 1];
  *output_idx_ref = output_idx;
  *sum_ref = sum;
  *weight_sum_ref = weight_sum;
  *sum2_ref = sum2;
  *weight_sum2_ref = weight_sum2;
  *sumsqrt_ref = sumsqrt;
  *weight_sumsqrt_ref = weight_sumsqrt;
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


