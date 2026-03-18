void print_array(const double *p, const int size)
{
  int i;
  for (i = 0; i < size; i += 1)
  {
    if (i)
    {
      printf(", ");
    }
    printf("%.1f", p[i]);
  }

  printf("\n");
}


/*** DEPENDENCIES:
***/


int main()
{
  const double data_in[] = {5, 8, 12, 11, 9, 8, 7, 10, 11, 13};
  const int input_length = (sizeof(data_in)) / (sizeof(double));
  printf("We have %d bars of input data.\n", input_length);
  print_array(data_in, input_length);
  const double options[] = {3};
  printf("Our option array is: ");
  print_array(options, (sizeof(options)) / (sizeof(double)));
  const int start = ti_sma_start(options);
  printf("The start amount is: %d\n", start);
  const int output_length = input_length - start;
  double *data_out = malloc(((unsigned int) output_length) * (sizeof(double)));
  assert(data_out != 0);
  printf("The output length is: %d\n", output_length);
  const double *all_inputs[] = {data_in};
  double *all_outputs[] = {data_out};
  int error = ti_sma(input_length, all_inputs, options, all_outputs);
  assert(error == 0);
  printf("The output data is: ");
  print_array(data_out, output_length);
  return 0;
}


/*** DEPENDENCIES:
int ti_sma_start(const double *options)
{
  return ((int) options[0]) - 1;
}


----------------------------
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


----------------------------
void print_array(const double *p, const int size)
{
  int i;
  for (i = 0; i < size; i += 1)
  {
    if (i)
    {
      printf(", ");
    }
    printf("%.1f", p[i]);
  }

  printf("\n");
}


----------------------------
***/


