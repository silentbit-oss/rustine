void banner()
{
  printf("  ______ _    _ __________________ _____  \n");
  printf(" |  ____| |  | |___  /___  /  ____|  __ \\ \n");
  printf(" | |__  | |  | |  / /   / /| |__  | |__) |\n");
  printf(" |  __| | |  | | / /   / / |  __| |  _  / \n");
  printf(" | |    | |__| |/ /__ / /__| |____| | \\ \\ \n");
  printf(" |_|     \\____//_____/_____|______|_|  \\_\\\n\n");
  printf("This program tries each indicator with a lot of options.\n");
  printf("It's good for checking for crashes or assertion failures.\n");
  printf("Use with a memory tool to check for memory errors in ti.\n\n");
}


/*** DEPENDENCIES:
***/


void check_output(const ti_indicator_info *info, int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const int s = info->start(options);
  int o;
  for (o = 0; o < info->outputs; o += 1)
  {
    double max = 0;
    double min = 0;
    int i;
    for (i = 0; i < (size - s); i += 1)
    {
      const double op = outputs[o][i];
      const double in = inputs[0][i + s];
      max = (in > max) ? (in) : (max);
      min = (in < min) ? (in) : (min);
      switch (info->type)
      {
        default:
        {
          break;
        }

        case 1:
        {
          if (((op > 4) && (op > ((max * 1.5) + 2))) || ((op < (-4)) && (op < ((min * 0.5) - 3))))
          {
            do
            {
              int k;
              int j;
              printf("\nInputs:");
              for (k = 0; k < input_size; k += 1)
                printf(" %f", inputs[0][k]);

              printf("\nOptions:");
              for (k = 0; k < info->options; k += 1)
                printf(" %f", options[k]);

              for (j = 0; j < info->outputs; j += 1)
              {
                printf("\nOutput[%d]:", j);
                for (k = 0; k < input_size; k += 1)
                  printf(" %f", outputs[j][k]);

              }

            }
            while (0);
            printf("\nERROR Output is out of range for input: input: %f output: %f\n", in, op);
            errors_cnt += 1;
            assert(0);
          }
          break;
        }

      }

    }

  }

}


/*** DEPENDENCIES:
int errors_cnt = 0
----------------------------
const int input_size = (sizeof(dummy_in)) / (sizeof(double))
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
***/


void helper_helper_stress_indicator_1_1(const ti_indicator_info * const info, const double *inputs[16], double *outputs[16], double options[16], int s)
{
  const int size = sizes[s];
  printf(" %d", size);
  const int r = info->indicator(size, inputs, options, outputs);
  if (r == 0)
  {
    check_output(info, size, inputs, options, outputs);
  }
  if (info->indicator_ref)
  {
    printf(" r");
    const int rr = info->indicator_ref(size, inputs, options, outputs);
    if (rr == 0)
    {
      check_output(info, size, inputs, options, outputs);
    }
  }
  if (info->stream_new)
  {
    ti_stream *stream;
    const int rs = info->stream_new(options, &stream);
    if ((rs == 0) && stream)
    {
      printf(" s");
      int rsc = info->stream_run(stream, size, inputs, outputs);
      if (rsc == 0)
      {
        check_output(info, size, inputs, options, outputs);
      }
      for (int repeat = 0; repeat < 5; repeat += 1)
      {
        rsc = info->stream_run(stream, size, inputs, outputs);
      }

      info->stream_free(stream);
    }
  }
}


/*** DEPENDENCIES:
void check_output(const ti_indicator_info *info, int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const int s = info->start(options);
  int o;
  for (o = 0; o < info->outputs; o += 1)
  {
    double max = 0;
    double min = 0;
    int i;
    for (i = 0; i < (size - s); i += 1)
    {
      const double op = outputs[o][i];
      const double in = inputs[0][i + s];
      max = (in > max) ? (in) : (max);
      min = (in < min) ? (in) : (min);
      switch (info->type)
      {
        default:
        {
          break;
        }

        case 1:
        {
          if (((op > 4) && (op > ((max * 1.5) + 2))) || ((op < (-4)) && (op < ((min * 0.5) - 3))))
          {
            do
            {
              int k;
              int j;
              printf("\nInputs:");
              for (k = 0; k < input_size; k += 1)
                printf(" %f", inputs[0][k]);

              printf("\nOptions:");
              for (k = 0; k < info->options; k += 1)
                printf(" %f", options[k]);

              for (j = 0; j < info->outputs; j += 1)
              {
                printf("\nOutput[%d]:", j);
                for (k = 0; k < input_size; k += 1)
                  printf(" %f", outputs[j][k]);

              }

            }
            while (0);
            printf("\nERROR Output is out of range for input: input: %f output: %f\n", in, op);
            errors_cnt += 1;
            assert(0);
          }
          break;
        }

      }

    }

  }

}


----------------------------
const int sizes[] = {0, 1, 2, 3, 4, 8, 20}
----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
***/


// hint:  ['j_ref is a mutable refrence to int', 'count_ref is a mutable refrence to int']
void helper_stress_indicator_1(int * const j_ref, int * const count_ref, const ti_indicator_info * const info, const int opt_count, const double *inputs[16], const double *inputs0[16], double *outputs[16], int options_index[16 + 1], double options[16], int choices, double * const optionsd, unsigned int optionsd_idx)
{
  int j = *j_ref;
  int count = *count_ref;
  count += 1;
  for (j = 0; j < opt_count; j += 1)
  {
    options[j] = optionsd[options_index[j] + optionsd_idx];
    printf(" %f", options[j]);
  }

  const int rz = info->indicator(input_size, inputs0, options, outputs);
  if (rz == 0)
  {
    check_output(info, input_size, inputs0, options, outputs);
  }
  for (int s = 0; s < sizes_count; s += 1)
  {
    helper_helper_stress_indicator_1_1(info, inputs, outputs, options, s);
  }

  printf("\r                                                                          \r");
  j = 0;
  do
  {
    options_index[j] = (options_index[j] + 1) % choices;
  }
  while (options_index[j++] == 0);
  *j_ref = j;
  *count_ref = count;
}


/*** DEPENDENCIES:
void check_output(const ti_indicator_info *info, int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const int s = info->start(options);
  int o;
  for (o = 0; o < info->outputs; o += 1)
  {
    double max = 0;
    double min = 0;
    int i;
    for (i = 0; i < (size - s); i += 1)
    {
      const double op = outputs[o][i];
      const double in = inputs[0][i + s];
      max = (in > max) ? (in) : (max);
      min = (in < min) ? (in) : (min);
      switch (info->type)
      {
        default:
        {
          break;
        }

        case 1:
        {
          if (((op > 4) && (op > ((max * 1.5) + 2))) || ((op < (-4)) && (op < ((min * 0.5) - 3))))
          {
            do
            {
              int k;
              int j;
              printf("\nInputs:");
              for (k = 0; k < input_size; k += 1)
                printf(" %f", inputs[0][k]);

              printf("\nOptions:");
              for (k = 0; k < info->options; k += 1)
                printf(" %f", options[k]);

              for (j = 0; j < info->outputs; j += 1)
              {
                printf("\nOutput[%d]:", j);
                for (k = 0; k < input_size; k += 1)
                  printf(" %f", outputs[j][k]);

              }

            }
            while (0);
            printf("\nERROR Output is out of range for input: input: %f output: %f\n", in, op);
            errors_cnt += 1;
            assert(0);
          }
          break;
        }

      }

    }

  }

}


----------------------------
const int input_size = (sizeof(dummy_in)) / (sizeof(double))
----------------------------
const int sizes_count = (sizeof(sizes)) / (sizeof(int))
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
void helper_helper_stress_indicator_1_1(const ti_indicator_info * const info, const double *inputs[16], double *outputs[16], double options[16], int s)
{
  const int size = sizes[s];
  printf(" %d", size);
  const int r = info->indicator(size, inputs, options, outputs);
  if (r == 0)
  {
    check_output(info, size, inputs, options, outputs);
  }
  if (info->indicator_ref)
  {
    printf(" r");
    const int rr = info->indicator_ref(size, inputs, options, outputs);
    if (rr == 0)
    {
      check_output(info, size, inputs, options, outputs);
    }
  }
  if (info->stream_new)
  {
    ti_stream *stream;
    const int rs = info->stream_new(options, &stream);
    if ((rs == 0) && stream)
    {
      printf(" s");
      int rsc = info->stream_run(stream, size, inputs, outputs);
      if (rsc == 0)
      {
        check_output(info, size, inputs, options, outputs);
      }
      for (int repeat = 0; repeat < 5; repeat += 1)
      {
        rsc = info->stream_run(stream, size, inputs, outputs);
      }

      info->stream_free(stream);
    }
  }
}


----------------------------
***/


void stress_indicator(const ti_indicator_info *info)
{
  const int opt_count = info->options;
  printf("%s (%s) (%d options)\n", info->name, info->full_name, opt_count);
  const double *inputs[16] = {0};
  const double *inputs0[16] = {0};
  double *outputs[16] = {0};
  int i;
  for (i = 0; i < 16; i += 1)
  {
    inputs[i] = (i < info->inputs) ? (dummy_in) : (0);
    inputs0[i] = (i < info->inputs) ? (dummy_in0) : (0);
    outputs[i] = (i < info->outputs) ? (dummy_ot) : (0);
  }

  int options_index[16 + 1] = {0};
  double options[16];
  int choices;
  double *optionsd;
  unsigned int optionsd_idx = 0;
  if (opt_count <= 4)
  {
    choices = (sizeof(optionsd_small)) / (sizeof(double));
    optionsd_idx = optionsd_small;
  }
  else
  {
    choices = (sizeof(optionsd_large)) / (sizeof(double));
    optionsd_idx = optionsd_large;
  }
  int j;
  int count = 0;
  do
  {
    helper_stress_indicator_1(&j, &count, info, opt_count, inputs, inputs0, outputs, options_index, options, choices, optionsd, optionsd_idx);
  }
  while (j <= opt_count);
  assert(.1 > fabs(count - pow(choices, opt_count)));
}


/*** DEPENDENCIES:
double dummy_in0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
----------------------------
double optionsd_small[] = {-20, -2, -1, 0, .7, 1, 2, 3, 4, 5, 6, 7, 8, 10, 20, 100, 999}
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
double dummy_ot[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
----------------------------
double dummy_in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
----------------------------
void helper_stress_indicator_1(int * const j_ref, int * const count_ref, const ti_indicator_info * const info, const int opt_count, const double *inputs[16], const double *inputs0[16], double *outputs[16], int options_index[16 + 1], double options[16], int choices, double * const optionsd, unsigned int optionsd_idx)
{
  int j = *j_ref;
  int count = *count_ref;
  count += 1;
  for (j = 0; j < opt_count; j += 1)
  {
    options[j] = optionsd[options_index[j] + optionsd_idx];
    printf(" %f", options[j]);
  }

  const int rz = info->indicator(input_size, inputs0, options, outputs);
  if (rz == 0)
  {
    check_output(info, input_size, inputs0, options, outputs);
  }
  for (int s = 0; s < sizes_count; s += 1)
  {
    helper_helper_stress_indicator_1_1(info, inputs, outputs, options, s);
  }

  printf("\r                                                                          \r");
  j = 0;
  do
  {
    options_index[j] = (options_index[j] + 1) % choices;
  }
  while (options_index[j++] == 0);
  *j_ref = j;
  *count_ref = count;
}


----------------------------
double optionsd_large[] = {-5, 0, 1, 2, 5}
----------------------------
***/


void stress_candle(const tc_candle_info *info)
{
  printf("%s (%s)\n", info->name, info->full_name);
  const double *inputs[4] = {dummy_in, dummy_in, dummy_in, dummy_in};
  const double *inputs0[4] = {dummy_in0, dummy_in0, dummy_in0, dummy_in0};
  tc_config config;
  tc_config_set_to_default(&config);
  tc_result *output = tc_result_new();
  for (int s = 0; s < sizes_count; s += 1)
  {
    const int size = sizes[s];
    info->candle(size, inputs, &config, output);
    assert(tc_result_count(output) <= size);
    assert(tc_result_pattern_count(output) <= size);
    for (int i = 0; i < tc_result_count(output); i += 1)
    {
      tc_hit hit = tc_result_get(output, i);
      assert(hit.patterns != ((1L << 26) - 1));
      assert(hit.index >= 0);
      assert(hit.index < size);
    }

    for (int i = 0; i < size; i += 1)
    {
      tc_set patterns = tc_result_at(output, i);
      assert(patterns != ((1L << 26) - 1));
    }

    info->candle(size, inputs0, &config, output);
    assert(tc_result_count(output) <= size);
    assert(tc_result_pattern_count(output) <= size);
  }

  tc_result_free(output);
}


/*** DEPENDENCIES:
int tc_result_pattern_count(const tc_result *result)
{
  return result->pattern_count;
}


----------------------------
tc_result *tc_result_new()
{
  tc_result *k = malloc(sizeof(tc_result));
  if (!k)
  {
    return 0;
  }
  memset(k, 0, sizeof(tc_result));
  return k;
}


----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
typedef uint64_t tc_set
----------------------------
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
double dummy_in0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
----------------------------
tc_hit tc_result_get(const tc_result *result, int index)
{
  if (index < result->count)
  {
    return result->hits[index];
  }
  tc_hit hit = {0};
  return hit;
}


----------------------------
void tc_result_free(tc_result *result)
{
  if (!result)
  {
    return;
  }
  free(result->hits);
  free(result);
}


----------------------------
const int sizes_count = (sizeof(sizes)) / (sizeof(int))
----------------------------
const int sizes[] = {0, 1, 2, 3, 4, 8, 20}
----------------------------
double dummy_in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}
----------------------------
int tc_result_count(const tc_result *result)
{
  return result->count;
}


----------------------------
typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info
----------------------------
tc_set tc_result_at(const tc_result *result, int index)
{
  int imin = 0;
  int imax = result->count - 1;
  if (!imax)
  {
    return 0;
  }
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    assert(i >= 0);
    assert(i < result->count);
    if (index == result->hits[i].index)
    {
      return result->hits[i].patterns;
    }
    else
      if (index > result->hits[i].index)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


----------------------------
void tc_config_set_to_default(tc_config *config)
{
  memcpy(config, tc_config_default(), sizeof(tc_config));
}


----------------------------
***/


int main(int argc, char *argv[])
{
  banner();
  if (argc > 1)
  {
    const ti_indicator_info *ind_info = ti_find_indicator(argv[1]);
    if (ind_info)
    {
      stress_indicator(ind_info);
    }
    const tc_candle_info *cnd_info = tc_find_candle(argv[1]);
    if (cnd_info)
    {
      stress_candle(cnd_info);
    }
  }
  else
  {
    const ti_indicator_info *ind_info = ti_indicators;
    do
    {
      stress_indicator(ind_info);
    }
    while ((++ind_info)->name);
    const tc_candle_info *cnd_info = tc_candles;
    do
    {
      stress_candle(cnd_info);
    }
    while ((++cnd_info)->name);
  }
  printf("\r                                                  \rDone\n");
  return (errors_cnt) ? (1) : (0);
}


/*** DEPENDENCIES:
const tc_candle_info *tc_find_candle(const char *name)
{
  int imin = 0;
  int imax = ((sizeof(tc_candles)) / (sizeof(tc_candle_info))) - 2;
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    const int c = strcmp(name, tc_candles[i].name);
    if (c == 0)
    {
      return tc_candles + i;
    }
    else
      if (c > 0)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


----------------------------
int errors_cnt = 0
----------------------------
void banner()
{
  printf("  ______ _    _ __________________ _____  \n");
  printf(" |  ____| |  | |___  /___  /  ____|  __ \\ \n");
  printf(" | |__  | |  | |  / /   / /| |__  | |__) |\n");
  printf(" |  __| | |  | | / /   / / |  __| |  _  / \n");
  printf(" | |    | |__| |/ /__ / /__| |____| | \\ \\ \n");
  printf(" |_|     \\____//_____/_____|______|_|  \\_\\\n\n");
  printf("This program tries each indicator with a lot of options.\n");
  printf("It's good for checking for crashes or assertion failures.\n");
  printf("Use with a memory tool to check for memory errors in ti.\n\n");
}


----------------------------
extern ti_indicator_info ti_indicators[]
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
void stress_indicator(const ti_indicator_info *info)
{
  const int opt_count = info->options;
  printf("%s (%s) (%d options)\n", info->name, info->full_name, opt_count);
  const double *inputs[16] = {0};
  const double *inputs0[16] = {0};
  double *outputs[16] = {0};
  int i;
  for (i = 0; i < 16; i += 1)
  {
    inputs[i] = (i < info->inputs) ? (dummy_in) : (0);
    inputs0[i] = (i < info->inputs) ? (dummy_in0) : (0);
    outputs[i] = (i < info->outputs) ? (dummy_ot) : (0);
  }

  int options_index[16 + 1] = {0};
  double options[16];
  int choices;
  double *optionsd;
  unsigned int optionsd_idx = 0;
  if (opt_count <= 4)
  {
    choices = (sizeof(optionsd_small)) / (sizeof(double));
    optionsd_idx = optionsd_small;
  }
  else
  {
    choices = (sizeof(optionsd_large)) / (sizeof(double));
    optionsd_idx = optionsd_large;
  }
  int j;
  int count = 0;
  do
  {
    helper_stress_indicator_1(&j, &count, info, opt_count, inputs, inputs0, outputs, options_index, options, choices, optionsd, optionsd_idx);
  }
  while (j <= opt_count);
  assert(.1 > fabs(count - pow(choices, opt_count)));
}


----------------------------
typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info
----------------------------
void stress_candle(const tc_candle_info *info)
{
  printf("%s (%s)\n", info->name, info->full_name);
  const double *inputs[4] = {dummy_in, dummy_in, dummy_in, dummy_in};
  const double *inputs0[4] = {dummy_in0, dummy_in0, dummy_in0, dummy_in0};
  tc_config config;
  tc_config_set_to_default(&config);
  tc_result *output = tc_result_new();
  for (int s = 0; s < sizes_count; s += 1)
  {
    const int size = sizes[s];
    info->candle(size, inputs, &config, output);
    assert(tc_result_count(output) <= size);
    assert(tc_result_pattern_count(output) <= size);
    for (int i = 0; i < tc_result_count(output); i += 1)
    {
      tc_hit hit = tc_result_get(output, i);
      assert(hit.patterns != ((1L << 26) - 1));
      assert(hit.index >= 0);
      assert(hit.index < size);
    }

    for (int i = 0; i < size; i += 1)
    {
      tc_set patterns = tc_result_at(output, i);
      assert(patterns != ((1L << 26) - 1));
    }

    info->candle(size, inputs0, &config, output);
    assert(tc_result_count(output) <= size);
    assert(tc_result_pattern_count(output) <= size);
  }

  tc_result_free(output);
}


----------------------------
const ti_indicator_info *ti_find_indicator(const char *name)
{
  int imin = 0;
  int imax = ((sizeof(ti_indicators)) / (sizeof(ti_indicator_info))) - 2;
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    const int c = strcmp(name, ti_indicators[i].name);
    if (c == 0)
    {
      return ti_indicators + i;
    }
    else
      if (c > 0)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


----------------------------
extern tc_candle_info tc_candles[]
----------------------------
***/


