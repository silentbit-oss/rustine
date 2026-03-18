char *next_line(FILE *fp)
{
  static char buf[4096];
  while (fgets(buf, 4096, fp))
  {
    if (buf[0] == '#')
    {
      continue;
    }
    if ((buf[0] == 10) || (buf[0] == 13))
    {
      continue;
    }
    return buf;
  }

  return 0;
}


/*** DEPENDENCIES:
***/


int get_array(FILE *fp, double *s)
{
  char *line = next_line(fp);
  if (line[0] != '{')
  {
    printf("Bad input\n");
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 85);
      }
    }
    while (0);
    return 0;
  }
  char *num = strtok(line + 1, ",}\r\n");
  unsigned int num_idx = 0;
  if (!(&num[num_idx]))
  {
    return 0;
  }
  double *inp = s;
  unsigned int inp_idx = 0;
  do
  {
    inp[inp_idx] = atof(num);
    inp_idx += 1;
  }
  while (num_idx = strtok(0, ",}\r\n"));
  return (int) ((&inp[inp_idx]) - s);
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
char *next_line(FILE *fp)
{
  static char buf[4096];
  while (fgets(buf, 4096, fp))
  {
    if (buf[0] == '#')
    {
      continue;
    }
    if ((buf[0] == 10) || (buf[0] == 13))
    {
      continue;
    }
    return buf;
  }

  return 0;
}


----------------------------
***/


void compare_arrays(double *a, double *b, int size_a, int size_b)
{
  int i;
  do
  {
    ltests += 1;
    if (size_a != size_b)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 42, size_a, size_b);
    }
  }
  while (0);
  if (size_a != size_b)
  {
    printf("Size mismatch.\n");
  }
  const int f = lfails;
  for (i = 0; i < size_a; i += 1)
  {
    do
    {
      ltests += 1;
      if (fabs(((double) a[i]) - ((double) b[i])) > 0.001)
      {
        lfails += 1;
        printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 50, (double) a[i], (double) b[i]);
      }
    }
    while (0);
  }

  if (lfails != f)
  {
    printf("Expected      Got\n");
    for (i = 0; i < size_a; i += 1)
    {
      printf("%8.3f %8.3f\n", a[i], b[i]);
    }

  }
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
***/


void test_localbuffer()
{
  typedef struct s
  {
    struct 
    {
      double padding;
      int zero[4];
      int offset_a;
      int size_a;
      int index_a;
      int padding_a;
    } buf_info;
    double padding[5];
  } s;
  s stream = {0};
  do
  {
    (&stream)->buf_info.offset_a = (*((&(&stream)->buf_info.offset_a) - 3)) + (*((&(&stream)->buf_info.offset_a) - 4));
    (&stream)->buf_info.size_a = 5;
    (&stream)->buf_info.index_a = -1;
  }
  while (0);
  do
  {
    ltests += 1;
    if (((*(((int *) ((&(&stream)->buf_info) + 1)) - 3)) + (*(((int *) ((&(&stream)->buf_info) + 1)) - 4))) != 5)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 395, (*(((int *) ((&(&stream)->buf_info) + 1)) - 3)) + (*(((int *) ((&(&stream)->buf_info) + 1)) - 4)), 5);
    }
  }
  while (0);
  do
  {
    int idx = (&stream)->buf_info.index_a + 1;
    if (idx == (&stream)->buf_info.size_a)
    {
      idx = 0;
    }
    *((((double *) ((&(&stream)->buf_info) + 1)) + (&stream)->buf_info.offset_a) + idx) = 100;
    (&stream)->buf_info.index_a = idx;
  }
  while (0);
  double get;
  do
  {
    int idx = (&stream)->buf_info.index_a + 0;
    while (idx >= (&stream)->buf_info.size_a)
    {
      idx -= (&stream)->buf_info.size_a;
    }

    while (idx < 0)
    {
      idx += (&stream)->buf_info.size_a;
    }

    get = *((((double *) ((&(&stream)->buf_info) + 1)) + (&stream)->buf_info.offset_a) + idx);
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) get) - ((double) 100)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 400, (double) get, (double) 100);
    }
  }
  while (0);
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int']
void helper_helper_helper_test_ind_name_1_1_1(int * const i_ref, const ti_indicator_info * const info, double *inputs[16], double *outputs[16], int input_size, const int step, ti_stream * const stream, int bar)
{
  int i = *i_ref;
  double *ins[16] = {0};
  double *outs[16] = {0};
  for (i = 0; i < info->inputs; i += 1)
  {
    ins[i] = inputs[i] + bar;
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    int progress = ti_stream_get_progress(stream);
    if (progress < 0)
    {
      progress = 0;
    }
    outs[i] = outputs[i] + progress;
  }

  int stride = step;
  if ((stride + bar) >= input_size)
  {
    stride = input_size - bar;
  }
  const int ret = info->stream_run(stream, stride, (const double * const *) ins, outs);
  do
  {
    ltests += 1;
    if (!(ret == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 222);
    }
  }
  while (0);
  *i_ref = i;
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
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
int ti_stream_get_progress(ti_stream *stream)
{
  return stream->progress;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int']
void helper_helper_test_ind_name_1_1(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size, const int steps[], int step_i)
{
  int i = *i_ref;
  const int step = steps[step_i];
  for (i = 0; i < info->outputs; i += 1)
  {
    memset(outputs[i], 0, (sizeof(double)) * 1024);
  }

  ti_stream *stream = 0;
  const int stream_ret = info->stream_new(options, &stream);
  do
  {
    ltests += 1;
    if (!(stream_ret == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 201);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(stream != 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 202);
    }
  }
  while (0);
  for (int bar = 0; bar < input_size; bar += step)
  {
    helper_helper_helper_test_ind_name_1_1_1(&i, info, inputs, outputs, input_size, step, stream, bar);
  }

  int output_size = input_size - info->start(options);
  if (output_size < 0)
  {
    output_size = 0;
  }
  do
  {
    ltests += 1;
    if (ti_stream_get_progress(stream) != output_size)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 227, ti_stream_get_progress(stream), output_size);
    }
  }
  while (0);
  for (i = 0; i < info->outputs; i += 1)
  {
    compare_arrays(answers[i], outputs[i], answer_size, output_size);
  }

  info->stream_free(stream);
  *i_ref = i;
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
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
void compare_arrays(double *a, double *b, int size_a, int size_b)
{
  int i;
  do
  {
    ltests += 1;
    if (size_a != size_b)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 42, size_a, size_b);
    }
  }
  while (0);
  if (size_a != size_b)
  {
    printf("Size mismatch.\n");
  }
  const int f = lfails;
  for (i = 0; i < size_a; i += 1)
  {
    do
    {
      ltests += 1;
      if (fabs(((double) a[i]) - ((double) b[i])) > 0.001)
      {
        lfails += 1;
        printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 50, (double) a[i], (double) b[i]);
      }
    }
    while (0);
  }

  if (lfails != f)
  {
    printf("Expected      Got\n");
    for (i = 0; i < size_a; i += 1)
    {
      printf("%8.3f %8.3f\n", a[i], b[i]);
    }

  }
}


----------------------------
int ti_stream_get_progress(ti_stream *stream)
{
  return stream->progress;
}


----------------------------
void helper_helper_helper_test_ind_name_1_1_1(int * const i_ref, const ti_indicator_info * const info, double *inputs[16], double *outputs[16], int input_size, const int step, ti_stream * const stream, int bar)
{
  int i = *i_ref;
  double *ins[16] = {0};
  double *outs[16] = {0};
  for (i = 0; i < info->inputs; i += 1)
  {
    ins[i] = inputs[i] + bar;
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    int progress = ti_stream_get_progress(stream);
    if (progress < 0)
    {
      progress = 0;
    }
    outs[i] = outputs[i] + progress;
  }

  int stride = step;
  if ((stride + bar) >= input_size)
  {
    stride = input_size - bar;
  }
  const int ret = info->stream_run(stream, stride, (const double * const *) ins, outs);
  do
  {
    ltests += 1;
    if (!(ret == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 222);
    }
  }
  while (0);
  *i_ref = i;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int']
void helper_test_ind_name_1(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size)
{
  int i = *i_ref;
  const int steps[] = {1, 2, 3, 4, 5, 7, 13, 100, 1024};
  const int step_count = (sizeof(steps)) / (sizeof(int));
  for (int step_i = 0; step_i < step_count; step_i += 1)
  {
    helper_helper_test_ind_name_1_1(&i, info, options, inputs, answers, outputs, input_size, answer_size, steps, step_i);
  }

  *i_ref = i;
}


/*** DEPENDENCIES:
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
void helper_helper_test_ind_name_1_1(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size, const int steps[], int step_i)
{
  int i = *i_ref;
  const int step = steps[step_i];
  for (i = 0; i < info->outputs; i += 1)
  {
    memset(outputs[i], 0, (sizeof(double)) * 1024);
  }

  ti_stream *stream = 0;
  const int stream_ret = info->stream_new(options, &stream);
  do
  {
    ltests += 1;
    if (!(stream_ret == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 201);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(stream != 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 202);
    }
  }
  while (0);
  for (int bar = 0; bar < input_size; bar += step)
  {
    helper_helper_helper_test_ind_name_1_1_1(&i, info, inputs, outputs, input_size, step, stream, bar);
  }

  int output_size = input_size - info->start(options);
  if (output_size < 0)
  {
    output_size = 0;
  }
  do
  {
    ltests += 1;
    if (ti_stream_get_progress(stream) != output_size)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 227, ti_stream_get_progress(stream), output_size);
    }
  }
  while (0);
  for (i = 0; i < info->outputs; i += 1)
  {
    compare_arrays(answers[i], outputs[i], answer_size, output_size);
  }

  info->stream_free(stream);
  *i_ref = i;
}


----------------------------
***/


void helper_test_candles_1(FILE * const fp, int count, tc_result * const output, static char buf[4096])
{
  if (feof(fp))
  {
    break;
  }
  fgets(buf, 4096, fp);
  if ((buf[0] != '!') && ((buf[0] < 'a') || (buf[0] > 'z')))
  {
    break;
  }
  char *name = strtok(buf, " ");
  unsigned int name_idx = 0;
  int negate = 0;
  if (buf[0] == '!')
  {
    negate = 1;
    name_idx += 1;
  }
  const tc_candle_info *info = tc_find_candle(name);
  do
  {
    ltests += 1;
    if (!info)
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 282);
    }
  }
  while (0);
  char *num;
  unsigned int num_idx = 0;
  while (num_idx = strtok(0, " "))
  {
    const int pos = atoi(num);
    if (negate)
    {
      do
      {
        ltests += 1;
        if (!(!(tc_result_at(output, pos) & info->pattern)))
        {
          lfails += 1;
          printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 290);
        }
      }
      while (0);
    }
    else
      do
    {
      ltests += 1;
      if (!(tc_result_at(output, pos) & info->pattern))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 292);
      }
    }
    while (0);
  }

  const int cnd_num = (int) (info - tc_candles);
  if (count)
  {
    tested_cnd[cnd_num] = 1;
  }
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
int tested_cnd[26] = {0}
----------------------------
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
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
static int ltests = 0
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
extern tc_candle_info tc_candles[]
----------------------------
***/


void test_candles(FILE *fp, int count)
{
  double *inputs[16] = {0};
  int input_size = 0;
  for (int i = 0; i < 4; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 1024);
    input_size = get_array(fp, inputs[i]);
  }

  tc_config config;
  tc_config_set_to_default(&config);
  tc_result *output = tc_result_new();
  tc_run((1L << 26) - 1, input_size, (const TC_REAL * const *) inputs, &config, output);
  static char buf[4096];
  do
  {
    helper_test_candles_1(fp, count, output, buf);
  }
  while (1);
  tc_result_free(output);
  free(inputs[0]);
  free(inputs[1]);
  free(inputs[2]);
  free(inputs[3]);
}


/*** DEPENDENCIES:
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
int get_array(FILE *fp, double *s)
{
  char *line = next_line(fp);
  if (line[0] != '{')
  {
    printf("Bad input\n");
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 85);
      }
    }
    while (0);
    return 0;
  }
  char *num = strtok(line + 1, ",}\r\n");
  unsigned int num_idx = 0;
  if (!(&num[num_idx]))
  {
    return 0;
  }
  double *inp = s;
  unsigned int inp_idx = 0;
  do
  {
    inp[inp_idx] = atof(num);
    inp_idx += 1;
  }
  while (num_idx = strtok(0, ",}\r\n"));
  return (int) ((&inp[inp_idx]) - s);
}


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
void helper_test_candles_1(FILE * const fp, int count, tc_result * const output, static char buf[4096])
{
  if (feof(fp))
  {
    break;
  }
  fgets(buf, 4096, fp);
  if ((buf[0] != '!') && ((buf[0] < 'a') || (buf[0] > 'z')))
  {
    break;
  }
  char *name = strtok(buf, " ");
  unsigned int name_idx = 0;
  int negate = 0;
  if (buf[0] == '!')
  {
    negate = 1;
    name_idx += 1;
  }
  const tc_candle_info *info = tc_find_candle(name);
  do
  {
    ltests += 1;
    if (!info)
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 282);
    }
  }
  while (0);
  char *num;
  unsigned int num_idx = 0;
  while (num_idx = strtok(0, " "))
  {
    const int pos = atoi(num);
    if (negate)
    {
      do
      {
        ltests += 1;
        if (!(!(tc_result_at(output, pos) & info->pattern)))
        {
          lfails += 1;
          printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 290);
        }
      }
      while (0);
    }
    else
      do
    {
      ltests += 1;
      if (!(tc_result_at(output, pos) & info->pattern))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 292);
      }
    }
    while (0);
  }

  const int cnd_num = (int) (info - tc_candles);
  if (count)
  {
    tested_cnd[cnd_num] = 1;
  }
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
int tc_run(tc_set patterns, int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
{
  tc_result_reset(output);
  {
    helper_tc_run_1(patterns, size, inputs, options, output);
  }
  const TC_REAL *open = inputs[0];
  const TC_REAL *high = inputs[1];
  const TC_REAL *low = inputs[2];
  const TC_REAL *close = inputs[3];
  const int period = options->period;
  const TC_REAL div = 1.0 / period;
  TC_REAL avg_body_sum = 0;
  TC_REAL avg_total_sum = 0;
  if (period < 1)
  {
    return 1;
  }
  if (size < period)
  {
    return 0;
  }
  int i;
  for (i = 0; i < period; i += 1)
  {
    avg_body_sum += fabs(open[i] - close[i]);
    avg_total_sum += high[i] - low[i];
  }

  while (i < size)
  {
    helper_tc_run_2(&avg_body_sum, &avg_total_sum, &i, patterns, options, output, open, high, low, close, period, div);
  }

  ;
  return 0;
}


----------------------------
void tc_config_set_to_default(tc_config *config)
{
  memcpy(config, tc_config_default(), sizeof(tc_config));
}


----------------------------
***/


void test_ind_name(FILE *fp, const char *name, int count)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    printf("(WARN) Couldn't find indicator %s\n", name);
    printf("---------------------------------------------");
    static char buf[4096];
    while (fgets(buf, 4096, fp) && ((buf[0] == '{') || (buf[0] == '#')))
      ;

    return;
  }
  const int ind_num = (int) (info - ti_indicators);
  if (count)
  {
    tested_ind[ind_num] = 1;
  }
  double options[16];
  double *o = options;
  unsigned int o_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  while (s_idx = strtok(0, " \n\r"))
  {
    o[o_idx] = atof(s);
    o_idx += 1;
  }

  do
  {
    ltests += 1;
    if (((int) ((&o[o_idx]) - options)) != info->options)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 137, (int) ((&o[o_idx]) - options), info->options);
    }
  }
  while (0);
  int i;
  double *inputs[16] = {0};
  double *answers[16] = {0};
  double *outputs[16] = {0};
  int input_size = 0;
  for (i = 0; i < info->inputs; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 1024);
    input_size = get_array(fp, inputs[i]);
  }

  int answer_size = 0;
  for (i = 0; i < info->outputs; i += 1)
  {
    answers[i] = malloc((sizeof(double)) * 1024);
    outputs[i] = malloc((sizeof(double)) * 1024);
    answer_size = get_array(fp, answers[i]);
  }

  {
    const int ret = info->indicator(input_size, (const double * const *) inputs, options, outputs);
    do
    {
      ltests += 1;
      if (!(ret == 0))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 160);
      }
    }
    while (0);
    int output_size = input_size - info->start(options);
    if (output_size < 0)
    {
      output_size = 0;
    }
    for (i = 0; i < info->outputs; i += 1)
    {
      compare_arrays(answers[i], outputs[i], answer_size, output_size);
    }

  }
  if (info->indicator_ref)
  {
    for (i = 0; i < info->outputs; i += 1)
    {
      memset(outputs[i], 0, (sizeof(double)) * 1024);
    }

    const int ret = info->indicator_ref(input_size, (const double * const *) inputs, options, outputs);
    do
    {
      ltests += 1;
      if (!(ret == 0))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 176);
      }
    }
    while (0);
    int output_size = input_size - info->start(options);
    if (output_size < 0)
    {
      output_size = 0;
    }
    for (i = 0; i < info->outputs; i += 1)
    {
      compare_arrays(answers[i], outputs[i], answer_size, output_size);
    }

  }
  if (info->stream_new)
  {
    helper_test_ind_name_1(&i, info, options, inputs, answers, outputs, input_size, answer_size);
  }
  for (i = 0; i < info->inputs; i += 1)
    free(inputs[i]);

  for (i = 0; i < info->outputs; i += 1)
    free(answers[i]);

  for (i = 0; i < info->outputs; i += 1)
    free(outputs[i]);

}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
void helper_test_ind_name_1(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size)
{
  int i = *i_ref;
  const int steps[] = {1, 2, 3, 4, 5, 7, 13, 100, 1024};
  const int step_count = (sizeof(steps)) / (sizeof(int));
  for (int step_i = 0; step_i < step_count; step_i += 1)
  {
    helper_helper_test_ind_name_1_1(&i, info, options, inputs, answers, outputs, input_size, answer_size, steps, step_i);
  }

  *i_ref = i;
}


----------------------------
int tested_ind[104] = {0}
----------------------------
int get_array(FILE *fp, double *s)
{
  char *line = next_line(fp);
  if (line[0] != '{')
  {
    printf("Bad input\n");
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 85);
      }
    }
    while (0);
    return 0;
  }
  char *num = strtok(line + 1, ",}\r\n");
  unsigned int num_idx = 0;
  if (!(&num[num_idx]))
  {
    return 0;
  }
  double *inp = s;
  unsigned int inp_idx = 0;
  do
  {
    inp[inp_idx] = atof(num);
    inp_idx += 1;
  }
  while (num_idx = strtok(0, ",}\r\n"));
  return (int) ((&inp[inp_idx]) - s);
}


----------------------------
static int ltests = 0
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
void compare_arrays(double *a, double *b, int size_a, int size_b)
{
  int i;
  do
  {
    ltests += 1;
    if (size_a != size_b)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 42, size_a, size_b);
    }
  }
  while (0);
  if (size_a != size_b)
  {
    printf("Size mismatch.\n");
  }
  const int f = lfails;
  for (i = 0; i < size_a; i += 1)
  {
    do
    {
      ltests += 1;
      if (fabs(((double) a[i]) - ((double) b[i])) > 0.001)
      {
        lfails += 1;
        printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 50, (double) a[i], (double) b[i]);
      }
    }
    while (0);
  }

  if (lfails != f)
  {
    printf("Expected      Got\n");
    for (i = 0; i < size_a; i += 1)
    {
      printf("%8.3f %8.3f\n", a[i], b[i]);
    }

  }
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
***/


void helper_test_1(int count, FILE * const fp, char * const line, unsigned int line_idx)
{
  if ((line[0 + line_idx] < 'a') || (line[0 + line_idx] > 'z'))
  {
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 326);
      }
    }
    while (0);
    continue;
  }
  char *name = strtok(line, " \n\r");
  if (!strcmp(name, "candle"))
  {
    do
    {
      const int ts = ltests;
      const int fs = lfails;
      const clock_t start = clock();
      printf("\t%-16s", name);
      test_candles(fp, count);
      printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
    }
    while (0);
  }
  else
  {
    do
    {
      const int ts = ltests;
      const int fs = lfails;
      const clock_t start = clock();
      printf("\t%-16s", name);
      test_ind_name(fp, name, count);
      printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
    }
    while (0);
  }
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void test_candles(FILE *fp, int count)
{
  double *inputs[16] = {0};
  int input_size = 0;
  for (int i = 0; i < 4; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 1024);
    input_size = get_array(fp, inputs[i]);
  }

  tc_config config;
  tc_config_set_to_default(&config);
  tc_result *output = tc_result_new();
  tc_run((1L << 26) - 1, input_size, (const TC_REAL * const *) inputs, &config, output);
  static char buf[4096];
  do
  {
    helper_test_candles_1(fp, count, output, buf);
  }
  while (1);
  tc_result_free(output);
  free(inputs[0]);
  free(inputs[1]);
  free(inputs[2]);
  free(inputs[3]);
}


----------------------------
void test_ind_name(FILE *fp, const char *name, int count)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    printf("(WARN) Couldn't find indicator %s\n", name);
    printf("---------------------------------------------");
    static char buf[4096];
    while (fgets(buf, 4096, fp) && ((buf[0] == '{') || (buf[0] == '#')))
      ;

    return;
  }
  const int ind_num = (int) (info - ti_indicators);
  if (count)
  {
    tested_ind[ind_num] = 1;
  }
  double options[16];
  double *o = options;
  unsigned int o_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  while (s_idx = strtok(0, " \n\r"))
  {
    o[o_idx] = atof(s);
    o_idx += 1;
  }

  do
  {
    ltests += 1;
    if (((int) ((&o[o_idx]) - options)) != info->options)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 137, (int) ((&o[o_idx]) - options), info->options);
    }
  }
  while (0);
  int i;
  double *inputs[16] = {0};
  double *answers[16] = {0};
  double *outputs[16] = {0};
  int input_size = 0;
  for (i = 0; i < info->inputs; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 1024);
    input_size = get_array(fp, inputs[i]);
  }

  int answer_size = 0;
  for (i = 0; i < info->outputs; i += 1)
  {
    answers[i] = malloc((sizeof(double)) * 1024);
    outputs[i] = malloc((sizeof(double)) * 1024);
    answer_size = get_array(fp, answers[i]);
  }

  {
    const int ret = info->indicator(input_size, (const double * const *) inputs, options, outputs);
    do
    {
      ltests += 1;
      if (!(ret == 0))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 160);
      }
    }
    while (0);
    int output_size = input_size - info->start(options);
    if (output_size < 0)
    {
      output_size = 0;
    }
    for (i = 0; i < info->outputs; i += 1)
    {
      compare_arrays(answers[i], outputs[i], answer_size, output_size);
    }

  }
  if (info->indicator_ref)
  {
    for (i = 0; i < info->outputs; i += 1)
    {
      memset(outputs[i], 0, (sizeof(double)) * 1024);
    }

    const int ret = info->indicator_ref(input_size, (const double * const *) inputs, options, outputs);
    do
    {
      ltests += 1;
      if (!(ret == 0))
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 176);
      }
    }
    while (0);
    int output_size = input_size - info->start(options);
    if (output_size < 0)
    {
      output_size = 0;
    }
    for (i = 0; i < info->outputs; i += 1)
    {
      compare_arrays(answers[i], outputs[i], answer_size, output_size);
    }

  }
  if (info->stream_new)
  {
    helper_test_ind_name_1(&i, info, options, inputs, answers, outputs, input_size, answer_size);
  }
  for (i = 0; i < info->inputs; i += 1)
    free(inputs[i]);

  for (i = 0; i < info->outputs; i += 1)
    free(answers[i]);

  for (i = 0; i < info->outputs; i += 1)
    free(outputs[i]);

}


----------------------------
***/


void test(const char *fname, int count)
{
  printf("%s:\n", fname);
  FILE *fp = fopen(fname, "r");
  if (!fp)
  {
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 316);
      }
    }
    while (0);
    return;
  }
  char *line;
  unsigned int line_idx = 0;
  while (line_idx = next_line(fp))
  {
    helper_test_1(count, fp, line, line_idx);
  }

  fclose(fp);
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
static int ltests = 0
----------------------------
void helper_test_1(int count, FILE * const fp, char * const line, unsigned int line_idx)
{
  if ((line[0 + line_idx] < 'a') || (line[0 + line_idx] > 'z'))
  {
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 326);
      }
    }
    while (0);
    continue;
  }
  char *name = strtok(line, " \n\r");
  if (!strcmp(name, "candle"))
  {
    do
    {
      const int ts = ltests;
      const int fs = lfails;
      const clock_t start = clock();
      printf("\t%-16s", name);
      test_candles(fp, count);
      printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
    }
    while (0);
  }
  else
  {
    do
    {
      const int ts = ltests;
      const int fs = lfails;
      const clock_t start = clock();
      printf("\t%-16s", name);
      test_ind_name(fp, name, count);
      printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
    }
    while (0);
  }
}


----------------------------
char *next_line(FILE *fp)
{
  static char buf[4096];
  while (fgets(buf, 4096, fp))
  {
    if (buf[0] == '#')
    {
      continue;
    }
    if ((buf[0] == 10) || (buf[0] == 13))
    {
      continue;
    }
    return buf;
  }

  return 0;
}


----------------------------
***/


void test_buffer()
{
  ti_buffer *b = ti_buffer_new(3);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 5.0;
    b->vals[b->index] = 5.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 5.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 360, (double) b->sum, (double) 5.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 5.0;
    b->vals[b->index] = 5.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 10.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 361, (double) b->sum, (double) 10.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 1.0;
    b->vals[b->index] = 1.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 11.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 362, (double) b->sum, (double) 11.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 1.0;
    b->vals[b->index] = 1.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 7.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 363, (double) b->sum, (double) 7.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 3.0;
    b->vals[b->index] = 3.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 5.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 364, (double) b->sum, (double) 5.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 1.0;
    b->vals[b->index] = 1.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 5.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 365, (double) b->sum, (double) 5.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 2.0;
    b->vals[b->index] = 2.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 6.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 366, (double) b->sum, (double) 6.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 3.0;
    b->vals[b->index] = 3.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 6.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 367, (double) b->sum, (double) 6.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + 0) % b->size]) - ((double) 3.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 369, (double) b->vals[(((b->index + b->size) - 1) + 0) % b->size], (double) 3.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + (-1)) % b->size]) - ((double) 2.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 370, (double) b->vals[(((b->index + b->size) - 1) + (-1)) % b->size], (double) 2.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + (-2)) % b->size]) - ((double) 1.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 371, (double) b->vals[(((b->index + b->size) - 1) + (-2)) % b->size], (double) 1.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + (-3)) % b->size]) - ((double) 3.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 372, (double) b->vals[(((b->index + b->size) - 1) + (-3)) % b->size], (double) 3.0);
    }
  }
  while (0);
  ti_buffer_free(b);
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
void ti_buffer_free(ti_buffer *buffer)
{
  free(buffer);
}


----------------------------
static int ltests = 0
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


void test_version()
{
  do
  {
    ltests += 1;
    if (!(strcmp("0.9.2", ti_version()) == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 345);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(1746800254 == ti_build()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 346);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(104 == ti_indicator_count()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 347);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(strcmp("0.9.2", tc_version()) == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 349);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(1746800254 == tc_build()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 350);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(26 == tc_candle_count()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 351);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(strcmp("0.9.2", "0.9.2") == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 353);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (1746800254 != 1746800254)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 354, 1746800254, 1746800254);
    }
  }
  while (0);
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
long int ti_build(void)
{
  return 1746800254;
}


----------------------------
static int ltests = 0
----------------------------
int ti_indicator_count(void)
{
  return 104;
}


----------------------------
int tc_candle_count(void)
{
  return 26;
}


----------------------------
const char *tc_version(void)
{
  return "0.9.2";
}


----------------------------
long int tc_build(void)
{
  return 1746800254;
}


----------------------------
const char *ti_version(void)
{
  return "0.9.2";
}


----------------------------
***/


int main()
{
  printf("TI TEST SUITE\n");
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-16s", "buffer");
    test_buffer();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-16s", "localbuffer");
    test_localbuffer();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  do
  {
    const int ts = ltests;
    const int fs = lfails;
    const clock_t start = clock();
    printf("\t%-16s", "version");
    test_version();
    printf("pass:%2d   fail:%2d   %4dms\n", (ltests - ts) - (lfails - fs), lfails - fs, (int) (((clock() - start) * 1000) / CLOCKS_PER_SEC));
  }
  while (0);
  test("tests/untest.txt", 0);
  test("tests/atoz.txt", 1);
  test("tests/extra.txt", 1);
  test("tests/candles.txt", 1);
  for (int i = 0; i < 104; i += 1)
  {
    if (!tested_ind[i])
    {
      printf("WARNING: no test for %s\n", ti_indicators[i].name);
    }
  }

  for (int i = 0; i < 26; i += 1)
  {
    if (!tested_cnd[i])
    {
      printf("WARNING: no test for %s\n", tc_candles[i].name);
    }
  }

  if (lfails == 0)
  {
    printf("ALL TESTS PASSED (%d/%d)\n", ltests, ltests);
  }
  else
  {
    printf("%d TESTS FAILED (of %d)\n", lfails, ltests);
  }
  return lfails != 0;
}


/*** DEPENDENCIES:
static int lfails = 0
----------------------------
int tested_cnd[26] = {0}
----------------------------
int tested_ind[104] = {0}
----------------------------
void test_buffer()
{
  ti_buffer *b = ti_buffer_new(3);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 5.0;
    b->vals[b->index] = 5.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 5.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 360, (double) b->sum, (double) 5.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 5.0;
    b->vals[b->index] = 5.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 10.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 361, (double) b->sum, (double) 10.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 1.0;
    b->vals[b->index] = 1.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 11.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 362, (double) b->sum, (double) 11.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 1.0;
    b->vals[b->index] = 1.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 7.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 363, (double) b->sum, (double) 7.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 3.0;
    b->vals[b->index] = 3.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 5.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 364, (double) b->sum, (double) 5.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 1.0;
    b->vals[b->index] = 1.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 5.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 365, (double) b->sum, (double) 5.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 2.0;
    b->vals[b->index] = 2.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 6.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 366, (double) b->sum, (double) 6.0);
    }
  }
  while (0);
  do
  {
    if (b->pushes >= b->size)
    {
      b->sum -= b->vals[b->index];
    }
    b->sum += 3.0;
    b->vals[b->index] = 3.0;
    b->pushes += 1;
    b->index = b->index + 1;
    if (b->index >= b->size)
    {
      b->index = 0;
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->sum) - ((double) 6.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 367, (double) b->sum, (double) 6.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + 0) % b->size]) - ((double) 3.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 369, (double) b->vals[(((b->index + b->size) - 1) + 0) % b->size], (double) 3.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + (-1)) % b->size]) - ((double) 2.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 370, (double) b->vals[(((b->index + b->size) - 1) + (-1)) % b->size], (double) 2.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + (-2)) % b->size]) - ((double) 1.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 371, (double) b->vals[(((b->index + b->size) - 1) + (-2)) % b->size], (double) 1.0);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) b->vals[(((b->index + b->size) - 1) + (-3)) % b->size]) - ((double) 3.0)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 372, (double) b->vals[(((b->index + b->size) - 1) + (-3)) % b->size], (double) 3.0);
    }
  }
  while (0);
  ti_buffer_free(b);
}


----------------------------
void test(const char *fname, int count)
{
  printf("%s:\n", fname);
  FILE *fp = fopen(fname, "r");
  if (!fp)
  {
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 316);
      }
    }
    while (0);
    return;
  }
  char *line;
  unsigned int line_idx = 0;
  while (line_idx = next_line(fp))
  {
    helper_test_1(count, fp, line, line_idx);
  }

  fclose(fp);
}


----------------------------
static int ltests = 0
----------------------------
extern ti_indicator_info ti_indicators[]
----------------------------
void test_localbuffer()
{
  typedef struct s
  {
    struct 
    {
      double padding;
      int zero[4];
      int offset_a;
      int size_a;
      int index_a;
      int padding_a;
    } buf_info;
    double padding[5];
  } s;
  s stream = {0};
  do
  {
    (&stream)->buf_info.offset_a = (*((&(&stream)->buf_info.offset_a) - 3)) + (*((&(&stream)->buf_info.offset_a) - 4));
    (&stream)->buf_info.size_a = 5;
    (&stream)->buf_info.index_a = -1;
  }
  while (0);
  do
  {
    ltests += 1;
    if (((*(((int *) ((&(&stream)->buf_info) + 1)) - 3)) + (*(((int *) ((&(&stream)->buf_info) + 1)) - 4))) != 5)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 395, (*(((int *) ((&(&stream)->buf_info) + 1)) - 3)) + (*(((int *) ((&(&stream)->buf_info) + 1)) - 4)), 5);
    }
  }
  while (0);
  do
  {
    int idx = (&stream)->buf_info.index_a + 1;
    if (idx == (&stream)->buf_info.size_a)
    {
      idx = 0;
    }
    *((((double *) ((&(&stream)->buf_info) + 1)) + (&stream)->buf_info.offset_a) + idx) = 100;
    (&stream)->buf_info.index_a = idx;
  }
  while (0);
  double get;
  do
  {
    int idx = (&stream)->buf_info.index_a + 0;
    while (idx >= (&stream)->buf_info.size_a)
    {
      idx -= (&stream)->buf_info.size_a;
    }

    while (idx < 0)
    {
      idx += (&stream)->buf_info.size_a;
    }

    get = *((((double *) ((&(&stream)->buf_info) + 1)) + (&stream)->buf_info.offset_a) + idx);
  }
  while (0);
  do
  {
    ltests += 1;
    if (fabs(((double) get) - ((double) 100)) > 0.001)
    {
      lfails += 1;
      printf("%s:%d (%f != %f)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 400, (double) get, (double) 100);
    }
  }
  while (0);
}


----------------------------
void test_version()
{
  do
  {
    ltests += 1;
    if (!(strcmp("0.9.2", ti_version()) == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 345);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(1746800254 == ti_build()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 346);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(104 == ti_indicator_count()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 347);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(strcmp("0.9.2", tc_version()) == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 349);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(1746800254 == tc_build()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 350);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(26 == tc_candle_count()))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 351);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (!(strcmp("0.9.2", "0.9.2") == 0))
    {
      lfails += 1;
      printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 353);
    }
  }
  while (0);
  do
  {
    ltests += 1;
    if (1746800254 != 1746800254)
    {
      lfails += 1;
      printf("%s:%d (%d != %d)\n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 354, 1746800254, 1746800254);
    }
  }
  while (0);
}


----------------------------
extern tc_candle_info tc_candles[]
----------------------------
***/


