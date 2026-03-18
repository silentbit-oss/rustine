void simple_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
}


/*** DEPENDENCIES:
***/


void fast_slow_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}


/*** DEPENDENCIES:
***/


void alma_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.5;
  options[2] = 1;
}


/*** DEPENDENCIES:
***/


void bbands_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1.0;
}


/*** DEPENDENCIES:
***/


void ce_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}


/*** DEPENDENCIES:
***/


void copp_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 11;
  options[1] = 14;
  options[2] = period;
}


/*** DEPENDENCIES:
***/


void kc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.77;
}


/*** DEPENDENCIES:
***/


void kst_option_setter(double period, double *options, int ti)
{
  (void) ti;
  for (int i = 0; i < 4; i += 1)
  {
    options[i + 4] = (options[i] = period + ((period / 4.) * i));
  }

}


/*** DEPENDENCIES:
***/


void macd_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = period + 1;
}


/*** DEPENDENCIES:
***/


void mama_option_setter(double period, double *options, int ti)
{
  (void) ti;
  (void) period;
  options[0] = 0.5;
  options[1] = 0.05;
}


/*** DEPENDENCIES:
***/


void pfe_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 5;
}


/*** DEPENDENCIES:
***/


void posc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}


/*** DEPENDENCIES:
***/


void ppo_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}


/*** DEPENDENCIES:
***/


void psar_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 1 / period;
  options[1] = options[0] * 10;
}


/*** DEPENDENCIES:
***/


void rmi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}


/*** DEPENDENCIES:
***/


void rmta_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1 - (2. / (period + 1));
}


/*** DEPENDENCIES:
***/


void rvi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 10;
}


/*** DEPENDENCIES:
***/


void smi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 25;
  options[2] = 3;
}


/*** DEPENDENCIES:
***/


void stoch_option_setter(double period, double *options, int ti)
{
  if (ti)
  {
    options[0] = period;
    options[1] = 3;
    options[2] = 4;
  }
  else
  {
  }
}


/*** DEPENDENCIES:
***/


void stochrsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period;
  options[2] = period;
  options[3] = 1;
}


/*** DEPENDENCIES:
***/


void tsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}


/*** DEPENDENCIES:
***/


void ultosc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period * 2;
  options[2] = period * 4;
}


/*** DEPENDENCIES:
***/


void vidya_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = .2;
}


/*** DEPENDENCIES:
***/


double stochrsi_output_adjust(double a)
{
  return a * 0.01;
}


/*** DEPENDENCIES:
***/


void generate_inputs()
{
  double *open = in[0];
  double *high = in[1];
  double *low = in[2];
  double *close = in[3];
  double *volume = in[4];
  open[0] = 100;
  srand(22);
  int i;
  for (i = 0; i < 4000; i += 1)
  {
    const double diff1 = (((((double) rand()) / 32767) - .5) + .01) * 2.5;
    const double diff2 = (((((double) rand()) / 32767) - .5) + .01) * 2.5;
    const double diff3 = (((double) rand()) / 32767) * 0.5;
    const double diff4 = (((double) rand()) / 32767) * 0.5;
    const double vol = ((((double) rand()) / 32767) * 10000) + 500;
    if (i)
    {
      open[i] = open[i - 1] + diff1;
    }
    close[i] = open[i] + diff2;
    high[i] = (open[i] > close[i]) ? (open[i] + diff3) : (close[i] + diff3);
    low[i] = (open[i] < close[i]) ? (open[i] - diff4) : (close[i] - diff4);
    volume[i] = vol;
    assert(open[i] <= high[i]);
    assert(close[i] <= high[i]);
    assert(open[i] >= low[i]);
    assert(close[i] >= low[i]);
    assert(high[i] >= low[i]);
    assert(high[i] >= open[i]);
    assert(high[i] >= close[i]);
    assert(low[i] <= low[i]);
    assert(low[i] <= open[i]);
    assert(low[i] <= close[i]);
  }

  volume[0] = 0;
}


/*** DEPENDENCIES:
double in[5][4000]
----------------------------
***/


// hint:  ['best_e_ref is a mutable refrence to int', 'best_p_ref is a mutable refrence to int']
void helper_bench_run_1(int * const best_e_ref, int * const best_p_ref, const ti_indicator_info * const info, const void * const run_info, const char * const name, double options[], void (* const options_setter)(double period, double *options, int ti), double * const options)
{
  int best_e = *best_e_ref;
  int best_p = *best_p_ref;
  printf("Benchmark %25s-%-16s ", info->name, name);
  int i;
  int period;
  int iterations = 0;
  const clock_t start = clock();
  fun(run_info, 0, 1);
  for (i = 0; i < 1; i += 1)
  {
    for (period = 4; period <= 150; period += 1)
    {
      if (options_setter)
      {
        options_setter(period, options, info == run_info);
      }
      else
        options[0] = period;
      const int ret = fun(run_info, options, 0);
      if (ret)
      {
        return;
      }
      iterations += 1;
    }

  }

  fun(run_info, 0, 2);
  const int elapsed = ((clock() - start) * 1000) / CLOCKS_PER_SEC;
  const int performance = (elapsed == 0) ? (0) : (((iterations * 4000) / elapsed) / 1000);
  if (elapsed)
  {
    printf("\t%5dms\t%5dmfps\n", elapsed, performance);
  }
  else
    printf("\n");
  best_e = (elapsed < best_e) ? (elapsed) : (best_e);
  best_p = (performance > best_p) ? (performance) : (best_p);
  *best_e_ref = best_e;
  *best_p_ref = best_p;
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
***/


void ti_setup(const ti_indicator_info *info, double **inputs)
{
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    if (strcmp(info->input_names[j], "open") == 0)
    {
      inputs[j] = in[0];
    }
    else
      if (strcmp(info->input_names[j], "high") == 0)
    {
      inputs[j] = in[1];
    }
    else
      if (strcmp(info->input_names[j], "low") == 0)
    {
      inputs[j] = in[2];
    }
    else
      if (strcmp(info->input_names[j], "close") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "real") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "volume") == 0)
    {
      inputs[j] = in[4];
    }
    else
    {
      assert(0);
    }
    ;
  }

}


/*** DEPENDENCIES:
double in[5][4000]
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


int run_ti(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {out[0], out[1], out[2], out[3], out[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    const int ret = info->indicator(4000, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      printf("   *ERROR* (%d)\n", ret);
      printf("options:\n");
      int i;
      for (i = 0; i < info->options; i += 1)
      {
        printf("%d = %f\n", i, options[i]);
      }

      return 1;
    }
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
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
int ind_offset
----------------------------
void ti_setup(const ti_indicator_info *info, double **inputs)
{
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    if (strcmp(info->input_names[j], "open") == 0)
    {
      inputs[j] = in[0];
    }
    else
      if (strcmp(info->input_names[j], "high") == 0)
    {
      inputs[j] = in[1];
    }
    else
      if (strcmp(info->input_names[j], "low") == 0)
    {
      inputs[j] = in[2];
    }
    else
      if (strcmp(info->input_names[j], "close") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "real") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "volume") == 0)
    {
      inputs[j] = in[4];
    }
    else
    {
      assert(0);
    }
    ;
  }

}


----------------------------
double out[3][4000]
----------------------------
***/


int run_ti_ref(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {outref[0], outref[1], outref[2], outref[3], outref[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    const int ret = info->indicator_ref(4000, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      printf("   *ERROR* (%d)\n", ret);
      printf("options:\n");
      int i;
      for (i = 0; i < info->options; i += 1)
      {
        printf("%d = %f\n", i, options[i]);
      }

      return 1;
    }
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


/*** DEPENDENCIES:
double outref[3][4000]
----------------------------
int ind_offset
----------------------------
void ti_setup(const ti_indicator_info *info, double **inputs)
{
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    if (strcmp(info->input_names[j], "open") == 0)
    {
      inputs[j] = in[0];
    }
    else
      if (strcmp(info->input_names[j], "high") == 0)
    {
      inputs[j] = in[1];
    }
    else
      if (strcmp(info->input_names[j], "low") == 0)
    {
      inputs[j] = in[2];
    }
    else
      if (strcmp(info->input_names[j], "close") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "real") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "volume") == 0)
    {
      inputs[j] = in[4];
    }
    else
    {
      assert(0);
    }
    ;
  }

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


void check_outputs(const ti_indicator_info *info, const char *what, double compare[3][4000])
{
  int remap[] = {0, 1, 2, 3, 4};
  int nanok = 0;
  if (strcmp(info->name, "asin") == 0)
  {
    nanok = 1;
  }
  if (strcmp(info->name, "acos") == 0)
  {
    nanok = 1;
  }
  int i;
  int j;
  for (j = 0; j < info->outputs; j += 1)
  {
    int end = 4000 - ind_offset;
    if (remap[j] == (-1))
    {
      continue;
    }
    for (i = 0; i < end; i += 1)
    {
      double a = out[j][((4000 - 1) - i) - ind_offset];
      double b = compare[j][((4000 - 1) - i) - ind_offset];
      double diff = fabs(a - b);
      if ((diff > 0.0001) || ((!nanok) && (diff != diff)))
      {
        fails += 1;
        printf("Results disagree.\n");
        printf("    series         (diff)   ti   %s\n", what);
        printf("    series %d, %4d (%f) %.5f %.5f\n", j, i, diff, a, b);
        break;
      }
    }

  }

}


/*** DEPENDENCIES:
int fails = 0
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
int ind_offset
----------------------------
double out[3][4000]
----------------------------
***/


int run_ti_streamall(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {outstreamall[0], outstreamall[1], outstreamall[2], outstreamall[3], outstreamall[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    ti_stream *stream;
    const int sret = info->stream_new(options, &stream);
    assert(stream);
    assert(sret == 0);
    const int ret = info->stream_run(stream, 4000, (const double * const *) inputs, outputs);
    info->stream_free(stream);
    if (ret != 0)
    {
      printf("   *ERROR* (%d)\n", ret);
      printf("options:\n");
      int i;
      for (i = 0; i < info->options; i += 1)
      {
        printf("%d = %f\n", i, options[i]);
      }

      return 1;
    }
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


/*** DEPENDENCIES:
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
double outstreamall[3][4000]
----------------------------
void ti_setup(const ti_indicator_info *info, double **inputs)
{
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    if (strcmp(info->input_names[j], "open") == 0)
    {
      inputs[j] = in[0];
    }
    else
      if (strcmp(info->input_names[j], "high") == 0)
    {
      inputs[j] = in[1];
    }
    else
      if (strcmp(info->input_names[j], "low") == 0)
    {
      inputs[j] = in[2];
    }
    else
      if (strcmp(info->input_names[j], "close") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "real") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "volume") == 0)
    {
      inputs[j] = in[4];
    }
    else
    {
      assert(0);
    }
    ;
  }

}


----------------------------
int ind_offset
----------------------------
***/


void bench_run_candle(FILE *log, const tc_candle_info *info)
{
  const char *name = "ti";
  tc_set pattern = info->pattern;
  int best_e = 1e9;
  int best_p = -1e9;
  int best;
  for (best = 0; best < bestof; best += 1)
  {
    printf("Benchmark %25s-%-16s ", info->name, name);
    int i;
    int period;
    int iterations = 0;
    const clock_t start = clock();
    const double *inputs[4] = {in[0], in[1], in[2], in[3]};
    tc_config config;
    tc_config_set_to_default(&config);
    for (i = 0; i < 1; i += 1)
    {
      for (period = 4; period <= 150; period += 1)
      {
        const int ret = tc_run(pattern, 4000, inputs, &config, outcnd);
        if (ret)
        {
          return;
        }
        iterations += 1;
      }

    }

    const int elapsed = ((clock() - start) * 1000) / CLOCKS_PER_SEC;
    const int performance = (elapsed == 0) ? (0) : (((iterations * 4000) / elapsed) / 1000);
    if (elapsed)
    {
      printf("\t%5dms\t%5dmfps\n", elapsed, performance);
    }
    else
      printf("\n");
    best_e = (elapsed < best_e) ? (elapsed) : (best_e);
    best_p = (performance > best_p) ? (performance) : (best_p);
  }

  if (log)
  {
    fprintf(log, ",\n    \"%s\" => array(\"elapsed\" => %d, \"performance\" => %d)", name, best_e, best_p);
  }
}


/*** DEPENDENCIES:
int bestof = 1
----------------------------
tc_result *outcnd = 0
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
typedef uint64_t tc_set
----------------------------
double in[5][4000]
----------------------------
typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info
----------------------------
void tc_config_set_to_default(tc_config *config)
{
  memcpy(config, tc_config_default(), sizeof(tc_config));
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
***/


void bench_candle(FILE *log, const tc_candle_info *info)
{
  outcnd = tc_result_new();
  assert(outcnd);
  if (info)
  {
    if (log)
    {
      fprintf(log, ",\n  \"%s\" => array(\n", info->name);
    }
    if (log)
    {
      fprintf(log, "    \"name\" => \"%s\"", info->full_name);
    }
    bench_run_candle(log, info);
    tc_result_free(outcnd);
  }
  if (log)
  {
    fprintf(log, "\n  )");
  }
  printf("\n");
}


/*** DEPENDENCIES:
tc_result *outcnd = 0
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
void bench_run_candle(FILE *log, const tc_candle_info *info)
{
  const char *name = "ti";
  tc_set pattern = info->pattern;
  int best_e = 1e9;
  int best_p = -1e9;
  int best;
  for (best = 0; best < bestof; best += 1)
  {
    printf("Benchmark %25s-%-16s ", info->name, name);
    int i;
    int period;
    int iterations = 0;
    const clock_t start = clock();
    const double *inputs[4] = {in[0], in[1], in[2], in[3]};
    tc_config config;
    tc_config_set_to_default(&config);
    for (i = 0; i < 1; i += 1)
    {
      for (period = 4; period <= 150; period += 1)
      {
        const int ret = tc_run(pattern, 4000, inputs, &config, outcnd);
        if (ret)
        {
          return;
        }
        iterations += 1;
      }

    }

    const int elapsed = ((clock() - start) * 1000) / CLOCKS_PER_SEC;
    const int performance = (elapsed == 0) ? (0) : (((iterations * 4000) / elapsed) / 1000);
    if (elapsed)
    {
      printf("\t%5dms\t%5dmfps\n", elapsed, performance);
    }
    else
      printf("\n");
    best_e = (elapsed < best_e) ? (elapsed) : (best_e);
    best_p = (performance > best_p) ? (performance) : (best_p);
  }

  if (log)
  {
    fprintf(log, ",\n    \"%s\" => array(\"elapsed\" => %d, \"performance\" => %d)", name, best_e, best_p);
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
typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info
----------------------------
***/


int run_ti_stream1(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {outstream1[0], outstream1[1], outstream1[2], outstream1[3], outstream1[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    double *ins[5] = {0};
    double *outs[5] = {0};
    ti_stream *stream;
    const int sret = info->stream_new(options, &stream);
    assert(stream);
    assert(sret == 0);
    for (int i = 0; i < 4000; i += 1)
    {
      for (unsigned int j = 0; j < ((sizeof(inputs)) / (sizeof(double *))); j += 1)
      {
        ins[j] = inputs[j] + i;
      }

      int k = ti_stream_get_progress(stream);
      if (k < 0)
      {
        k = 0;
      }
      for (unsigned int j = 0; j < ((sizeof(outputs)) / (sizeof(double *))); j += 1)
      {
        outs[j] = outstream1[j] + k;
      }

      const int ret = info->stream_run(stream, 1, (const double * const *) ins, outs);
      if (ret != 0)
      {
        printf("   *ERROR* (%d)\n", ret);
        printf("options:\n");
        for (int j = 0; j < info->options; j += 1)
        {
          printf("%d = %f\n", j, options[j]);
        }

        return 1;
      }
    }

    info->stream_free(stream);
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


/*** DEPENDENCIES:
double outstream1[3][4000]
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
void ti_setup(const ti_indicator_info *info, double **inputs)
{
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    if (strcmp(info->input_names[j], "open") == 0)
    {
      inputs[j] = in[0];
    }
    else
      if (strcmp(info->input_names[j], "high") == 0)
    {
      inputs[j] = in[1];
    }
    else
      if (strcmp(info->input_names[j], "low") == 0)
    {
      inputs[j] = in[2];
    }
    else
      if (strcmp(info->input_names[j], "close") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "real") == 0)
    {
      inputs[j] = in[3];
    }
    else
      if (strcmp(info->input_names[j], "volume") == 0)
    {
      inputs[j] = in[4];
    }
    else
    {
      assert(0);
    }
    ;
  }

}


----------------------------
int ti_stream_get_progress(ti_stream *stream)
{
  return stream->progress;
}


----------------------------
int ind_offset
----------------------------
***/


void bench_run(FILE *log, const ti_indicator_info *info, const void *run_info, run_fun fun, const char *name)
{
  double options[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  void (*options_setter)(double period, double *options, int ti) = 0;
  unsigned int options_setter_idx = 0;
  if (strcmp(info->name, "alma") == 0)
  {
    options_setter_idx = alma_option_setter;
  }
  if (strcmp(info->name, "adosc") == 0)
  {
    options_setter_idx = fast_slow_option_setter;
  }
  if (strcmp(info->name, "apo") == 0)
  {
    options_setter_idx = ppo_option_setter;
  }
  if (strcmp(info->name, "bbands") == 0)
  {
    options_setter_idx = bbands_option_setter;
  }
  if (strcmp(info->name, "copp") == 0)
  {
    options_setter_idx = copp_option_setter;
  }
  if (strcmp(info->name, "kc") == 0)
  {
    options_setter_idx = kc_option_setter;
  }
  if (strcmp(info->name, "kst") == 0)
  {
    options_setter_idx = kst_option_setter;
  }
  if (strcmp(info->name, "kvo") == 0)
  {
    options_setter_idx = fast_slow_option_setter;
  }
  if (strcmp(info->name, "macd") == 0)
  {
    options_setter_idx = macd_option_setter;
  }
  if (strcmp(info->name, "mama") == 0)
  {
    options_setter_idx = mama_option_setter;
  }
  if (strcmp(info->name, "pfe") == 0)
  {
    options_setter_idx = pfe_option_setter;
  }
  if (strcmp(info->name, "posc") == 0)
  {
    options_setter_idx = posc_option_setter;
  }
  if (strcmp(info->name, "ppo") == 0)
  {
    options_setter_idx = ppo_option_setter;
  }
  if (strcmp(info->name, "psar") == 0)
  {
    options_setter_idx = psar_option_setter;
  }
  if (strcmp(info->name, "rvi") == 0)
  {
    options_setter_idx = rvi_option_setter;
  }
  if (strcmp(info->name, "rmi") == 0)
  {
    options_setter_idx = rmi_option_setter;
  }
  if (strcmp(info->name, "rmta") == 0)
  {
    options_setter_idx = rmta_option_setter;
  }
  if (strcmp(info->name, "smi") == 0)
  {
    options_setter_idx = smi_option_setter;
  }
  if (strcmp(info->name, "stoch") == 0)
  {
    options_setter_idx = stoch_option_setter;
  }
  if (strcmp(info->name, "stochrsi") == 0)
  {
    options_setter_idx = stochrsi_option_setter;
  }
  if (strcmp(info->name, "ultosc") == 0)
  {
    options_setter_idx = ultosc_option_setter;
  }
  if (strcmp(info->name, "vidya") == 0)
  {
    options_setter_idx = vidya_option_setter;
  }
  if (strcmp(info->name, "vosc") == 0)
  {
    options_setter_idx = fast_slow_option_setter;
  }
  int best_e = 1e9;
  int best_p = -1e9;
  int best;
  for (best = 0; best < bestof; best += 1)
  {
    helper_bench_run_1(&best_e, &best_p, info, run_info, name, options, options_setter, options);
  }

  if (log)
  {
    fprintf(log, ",\n    \"%s\" => array(\"elapsed\" => %d, \"performance\" => %d)", name, best_e, best_p);
  }
}


/*** DEPENDENCIES:
void alma_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.5;
  options[2] = 1;
}


----------------------------
void macd_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = period + 1;
}


----------------------------
void helper_bench_run_1(int * const best_e_ref, int * const best_p_ref, const ti_indicator_info * const info, const void * const run_info, const char * const name, double options[], void (* const options_setter)(double period, double *options, int ti), double * const options)
{
  int best_e = *best_e_ref;
  int best_p = *best_p_ref;
  printf("Benchmark %25s-%-16s ", info->name, name);
  int i;
  int period;
  int iterations = 0;
  const clock_t start = clock();
  fun(run_info, 0, 1);
  for (i = 0; i < 1; i += 1)
  {
    for (period = 4; period <= 150; period += 1)
    {
      if (options_setter)
      {
        options_setter(period, options, info == run_info);
      }
      else
        options[0] = period;
      const int ret = fun(run_info, options, 0);
      if (ret)
      {
        return;
      }
      iterations += 1;
    }

  }

  fun(run_info, 0, 2);
  const int elapsed = ((clock() - start) * 1000) / CLOCKS_PER_SEC;
  const int performance = (elapsed == 0) ? (0) : (((iterations * 4000) / elapsed) / 1000);
  if (elapsed)
  {
    printf("\t%5dms\t%5dmfps\n", elapsed, performance);
  }
  else
    printf("\n");
  best_e = (elapsed < best_e) ? (elapsed) : (best_e);
  best_p = (performance > best_p) ? (performance) : (best_p);
  *best_e_ref = best_e;
  *best_p_ref = best_p;
}


----------------------------
void smi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 25;
  options[2] = 3;
}


----------------------------
void vidya_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = .2;
}


----------------------------
int bestof = 1
----------------------------
void kc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.77;
}


----------------------------
void ppo_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}


----------------------------
void copp_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 11;
  options[1] = 14;
  options[2] = period;
}


----------------------------
void posc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}


----------------------------
void rvi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 10;
}


----------------------------
void mama_option_setter(double period, double *options, int ti)
{
  (void) ti;
  (void) period;
  options[0] = 0.5;
  options[1] = 0.05;
}


----------------------------
void bbands_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1.0;
}


----------------------------
void stochrsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period;
  options[2] = period;
  options[3] = 1;
}


----------------------------
void stoch_option_setter(double period, double *options, int ti)
{
  if (ti)
  {
    options[0] = period;
    options[1] = 3;
    options[2] = 4;
  }
  else
  {
  }
}


----------------------------
typedef int (*run_fun)(const ti_indicator_info *info, double *options, int goal)
----------------------------
void rmta_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1 - (2. / (period + 1));
}


----------------------------
void kst_option_setter(double period, double *options, int ti)
{
  (void) ti;
  for (int i = 0; i < 4; i += 1)
  {
    options[i + 4] = (options[i] = period + ((period / 4.) * i));
  }

}


----------------------------
void psar_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 1 / period;
  options[1] = options[0] * 10;
}


----------------------------
void pfe_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 5;
}


----------------------------
void rmi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}


----------------------------
void ultosc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period * 2;
  options[2] = period * 4;
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
void fast_slow_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}


----------------------------
***/


void bench_indicator(FILE *log, const ti_indicator_info *info)
{
  {
    int i;
    for (i = 0; i < 3; i += 1)
    {
      memset(out[i], 0xF1, sizeof(out[i]));
      memset(outref[i], 0xF2, sizeof(outref[i]));
      memset(outstream1[i], 0xF3, sizeof(outstream1[i]));
      memset(outstreamall[i], 0xF4, sizeof(outstreamall[i]));
    }

  }
  if (info)
  {
    if (log)
    {
      fprintf(log, ",\n  \"%s\" => array(\n", info->name);
    }
    if (log)
    {
      fprintf(log, "    \"name\" => \"%s\"", info->full_name);
    }
    bench_run(log, info, info, run_ti, "ti");
  }
  if (info && info->indicator_ref)
  {
    bench_run(log, info, info, run_ti_ref, "ti_ref");
    check_outputs(info, "ref", outref);
  }
  if (info && info->stream_new)
  {
    bench_run(log, info, info, run_ti_stream1, "ti_stream1");
    check_outputs(info, "stream1", outstream1);
    bench_run(log, info, info, run_ti_streamall, "ti_streamall");
    check_outputs(info, "streamall", outstreamall);
  }
  if (log)
  {
    fprintf(log, "\n  )");
  }
  printf("\n");
}


/*** DEPENDENCIES:
double outstream1[3][4000]
----------------------------
double outref[3][4000]
----------------------------
int run_ti_streamall(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {outstreamall[0], outstreamall[1], outstreamall[2], outstreamall[3], outstreamall[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    ti_stream *stream;
    const int sret = info->stream_new(options, &stream);
    assert(stream);
    assert(sret == 0);
    const int ret = info->stream_run(stream, 4000, (const double * const *) inputs, outputs);
    info->stream_free(stream);
    if (ret != 0)
    {
      printf("   *ERROR* (%d)\n", ret);
      printf("options:\n");
      int i;
      for (i = 0; i < info->options; i += 1)
      {
        printf("%d = %f\n", i, options[i]);
      }

      return 1;
    }
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


----------------------------
void bench_run(FILE *log, const ti_indicator_info *info, const void *run_info, run_fun fun, const char *name)
{
  double options[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  void (*options_setter)(double period, double *options, int ti) = 0;
  unsigned int options_setter_idx = 0;
  if (strcmp(info->name, "alma") == 0)
  {
    options_setter_idx = alma_option_setter;
  }
  if (strcmp(info->name, "adosc") == 0)
  {
    options_setter_idx = fast_slow_option_setter;
  }
  if (strcmp(info->name, "apo") == 0)
  {
    options_setter_idx = ppo_option_setter;
  }
  if (strcmp(info->name, "bbands") == 0)
  {
    options_setter_idx = bbands_option_setter;
  }
  if (strcmp(info->name, "copp") == 0)
  {
    options_setter_idx = copp_option_setter;
  }
  if (strcmp(info->name, "kc") == 0)
  {
    options_setter_idx = kc_option_setter;
  }
  if (strcmp(info->name, "kst") == 0)
  {
    options_setter_idx = kst_option_setter;
  }
  if (strcmp(info->name, "kvo") == 0)
  {
    options_setter_idx = fast_slow_option_setter;
  }
  if (strcmp(info->name, "macd") == 0)
  {
    options_setter_idx = macd_option_setter;
  }
  if (strcmp(info->name, "mama") == 0)
  {
    options_setter_idx = mama_option_setter;
  }
  if (strcmp(info->name, "pfe") == 0)
  {
    options_setter_idx = pfe_option_setter;
  }
  if (strcmp(info->name, "posc") == 0)
  {
    options_setter_idx = posc_option_setter;
  }
  if (strcmp(info->name, "ppo") == 0)
  {
    options_setter_idx = ppo_option_setter;
  }
  if (strcmp(info->name, "psar") == 0)
  {
    options_setter_idx = psar_option_setter;
  }
  if (strcmp(info->name, "rvi") == 0)
  {
    options_setter_idx = rvi_option_setter;
  }
  if (strcmp(info->name, "rmi") == 0)
  {
    options_setter_idx = rmi_option_setter;
  }
  if (strcmp(info->name, "rmta") == 0)
  {
    options_setter_idx = rmta_option_setter;
  }
  if (strcmp(info->name, "smi") == 0)
  {
    options_setter_idx = smi_option_setter;
  }
  if (strcmp(info->name, "stoch") == 0)
  {
    options_setter_idx = stoch_option_setter;
  }
  if (strcmp(info->name, "stochrsi") == 0)
  {
    options_setter_idx = stochrsi_option_setter;
  }
  if (strcmp(info->name, "ultosc") == 0)
  {
    options_setter_idx = ultosc_option_setter;
  }
  if (strcmp(info->name, "vidya") == 0)
  {
    options_setter_idx = vidya_option_setter;
  }
  if (strcmp(info->name, "vosc") == 0)
  {
    options_setter_idx = fast_slow_option_setter;
  }
  int best_e = 1e9;
  int best_p = -1e9;
  int best;
  for (best = 0; best < bestof; best += 1)
  {
    helper_bench_run_1(&best_e, &best_p, info, run_info, name, options, options_setter, options);
  }

  if (log)
  {
    fprintf(log, ",\n    \"%s\" => array(\"elapsed\" => %d, \"performance\" => %d)", name, best_e, best_p);
  }
}


----------------------------
int run_ti_stream1(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {outstream1[0], outstream1[1], outstream1[2], outstream1[3], outstream1[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    double *ins[5] = {0};
    double *outs[5] = {0};
    ti_stream *stream;
    const int sret = info->stream_new(options, &stream);
    assert(stream);
    assert(sret == 0);
    for (int i = 0; i < 4000; i += 1)
    {
      for (unsigned int j = 0; j < ((sizeof(inputs)) / (sizeof(double *))); j += 1)
      {
        ins[j] = inputs[j] + i;
      }

      int k = ti_stream_get_progress(stream);
      if (k < 0)
      {
        k = 0;
      }
      for (unsigned int j = 0; j < ((sizeof(outputs)) / (sizeof(double *))); j += 1)
      {
        outs[j] = outstream1[j] + k;
      }

      const int ret = info->stream_run(stream, 1, (const double * const *) ins, outs);
      if (ret != 0)
      {
        printf("   *ERROR* (%d)\n", ret);
        printf("options:\n");
        for (int j = 0; j < info->options; j += 1)
        {
          printf("%d = %f\n", j, options[j]);
        }

        return 1;
      }
    }

    info->stream_free(stream);
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


----------------------------
double out[3][4000]
----------------------------
double outstreamall[3][4000]
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
void check_outputs(const ti_indicator_info *info, const char *what, double compare[3][4000])
{
  int remap[] = {0, 1, 2, 3, 4};
  int nanok = 0;
  if (strcmp(info->name, "asin") == 0)
  {
    nanok = 1;
  }
  if (strcmp(info->name, "acos") == 0)
  {
    nanok = 1;
  }
  int i;
  int j;
  for (j = 0; j < info->outputs; j += 1)
  {
    int end = 4000 - ind_offset;
    if (remap[j] == (-1))
    {
      continue;
    }
    for (i = 0; i < end; i += 1)
    {
      double a = out[j][((4000 - 1) - i) - ind_offset];
      double b = compare[j][((4000 - 1) - i) - ind_offset];
      double diff = fabs(a - b);
      if ((diff > 0.0001) || ((!nanok) && (diff != diff)))
      {
        fails += 1;
        printf("Results disagree.\n");
        printf("    series         (diff)   ti   %s\n", what);
        printf("    series %d, %4d (%f) %.5f %.5f\n", j, i, diff, a, b);
        break;
      }
    }

  }

}


----------------------------
int run_ti_ref(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {outref[0], outref[1], outref[2], outref[3], outref[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    const int ret = info->indicator_ref(4000, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      printf("   *ERROR* (%d)\n", ret);
      printf("options:\n");
      int i;
      for (i = 0; i < info->options; i += 1)
      {
        printf("%d = %f\n", i, options[i]);
      }

      return 1;
    }
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


----------------------------
int run_ti(const ti_indicator_info *info, double *options, int goal)
{
  static double *inputs[] = {0, 0, 0, 0, 0};
  static double *outputs[] = {out[0], out[1], out[2], out[3], out[4]};
  if (goal == 0)
  {
    ind_offset = info->start(options);
    const int ret = info->indicator(4000, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      printf("   *ERROR* (%d)\n", ret);
      printf("options:\n");
      int i;
      for (i = 0; i < info->options; i += 1)
      {
        printf("%d = %f\n", i, options[i]);
      }

      return 1;
    }
  }
  else
    if (goal == 1)
  {
    ti_setup(info, inputs);
  }
  else
    if (goal == 2)
  {
  }
  else
  {
    assert(0);
  }
  return 0;
}


----------------------------
***/


int main(int argc, char **argv)
{
  printf("Tulip Charts Indicator benchmark.\n");
  printf("Using real size of: %d.\n\n", sizeof(double));
  generate_inputs();
  const ti_indicator_info *ind_info = ti_indicators;
  unsigned int ind_info_idx = 0;
  const tc_candle_info *cnd_info = tc_candles;
  unsigned int cnd_info_idx = 0;
  const int candles_only = (argc > 1) && (!strcmp(argv[1], "tc"));
  if (((argc > 1) && (!isdigit(argv[1][0]))) && (!candles_only))
  {
    if (argc > 2)
    {
      bestof = atoi(argv[2]);
      if (!bestof)
      {
        bestof = 1;
      }
    }
    ind_info_idx = ti_find_indicator(argv[1]);
    if (ind_info)
    {
      bench_indicator(0, ind_info);
    }
    cnd_info_idx = tc_find_candle(argv[1]);
    if (cnd_info)
    {
      bench_candle(0, cnd_info);
    }
  }
  else
  {
    if ((argc > 1) && isdigit(argv[1][0]))
    {
      bestof = atoi(argv[1]);
    }
    FILE *log = fopen("docs/benchmark.php", "w");
    if (!log)
    {
      printf("Couldn't open results file for output. Make sure ./docs/ exists.\n");
      exit(1);
    }
    fprintf(log, "<?php\n");
    fprintf(log, "#GENERATED BY benchmark.c\n");
    fprintf(log, "#DO NOT MODIFY DIRECTLY\n");
    fprintf(log, "$benchmark = array(\n");
    fprintf(log, "  \"worksize\" => %d,", (1 * ((150 - 4) + 1)) * 4000);
    fprintf(log, "  \"bestof\" => %d", bestof);
    if (!candles_only)
    {
      do
      {
        if (strcmp(ind_info->name, "msw") == 0)
        {
          continue;
        }
        bench_indicator(log, ind_info);
      }
      while ((++(&ind_info[ind_info_idx]))->name);
    }
    do
    {
      bench_candle(log, cnd_info);
    }
    while ((++(&cnd_info[cnd_info_idx]))->name);
    const tc_candle_info cnd_all = {.name = "all", .full_name = "All Candle Patterns", .pattern = (1L << 26) - 1};
    bench_candle(log, &cnd_all);
    fprintf(log, ");");
    fclose(log);
  }
  if (!fails)
  {
    printf("All comparisons passed.\n");
  }
  else
  {
    printf("%d comparisons failed.\n", fails);
  }
  return 0;
}


/*** DEPENDENCIES:
int bestof = 1
----------------------------
int fails = 0
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
void bench_candle(FILE *log, const tc_candle_info *info)
{
  outcnd = tc_result_new();
  assert(outcnd);
  if (info)
  {
    if (log)
    {
      fprintf(log, ",\n  \"%s\" => array(\n", info->name);
    }
    if (log)
    {
      fprintf(log, "    \"name\" => \"%s\"", info->full_name);
    }
    bench_run_candle(log, info);
    tc_result_free(outcnd);
  }
  if (log)
  {
    fprintf(log, "\n  )");
  }
  printf("\n");
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
void generate_inputs()
{
  double *open = in[0];
  double *high = in[1];
  double *low = in[2];
  double *close = in[3];
  double *volume = in[4];
  open[0] = 100;
  srand(22);
  int i;
  for (i = 0; i < 4000; i += 1)
  {
    const double diff1 = (((((double) rand()) / 32767) - .5) + .01) * 2.5;
    const double diff2 = (((((double) rand()) / 32767) - .5) + .01) * 2.5;
    const double diff3 = (((double) rand()) / 32767) * 0.5;
    const double diff4 = (((double) rand()) / 32767) * 0.5;
    const double vol = ((((double) rand()) / 32767) * 10000) + 500;
    if (i)
    {
      open[i] = open[i - 1] + diff1;
    }
    close[i] = open[i] + diff2;
    high[i] = (open[i] > close[i]) ? (open[i] + diff3) : (close[i] + diff3);
    low[i] = (open[i] < close[i]) ? (open[i] - diff4) : (close[i] - diff4);
    volume[i] = vol;
    assert(open[i] <= high[i]);
    assert(close[i] <= high[i]);
    assert(open[i] >= low[i]);
    assert(close[i] >= low[i]);
    assert(high[i] >= low[i]);
    assert(high[i] >= open[i]);
    assert(high[i] >= close[i]);
    assert(low[i] <= low[i]);
    assert(low[i] <= open[i]);
    assert(low[i] <= close[i]);
  }

  volume[0] = 0;
}


----------------------------
extern tc_candle_info tc_candles[]
----------------------------
void bench_indicator(FILE *log, const ti_indicator_info *info)
{
  {
    int i;
    for (i = 0; i < 3; i += 1)
    {
      memset(out[i], 0xF1, sizeof(out[i]));
      memset(outref[i], 0xF2, sizeof(outref[i]));
      memset(outstream1[i], 0xF3, sizeof(outstream1[i]));
      memset(outstreamall[i], 0xF4, sizeof(outstreamall[i]));
    }

  }
  if (info)
  {
    if (log)
    {
      fprintf(log, ",\n  \"%s\" => array(\n", info->name);
    }
    if (log)
    {
      fprintf(log, "    \"name\" => \"%s\"", info->full_name);
    }
    bench_run(log, info, info, run_ti, "ti");
  }
  if (info && info->indicator_ref)
  {
    bench_run(log, info, info, run_ti_ref, "ti_ref");
    check_outputs(info, "ref", outref);
  }
  if (info && info->stream_new)
  {
    bench_run(log, info, info, run_ti_stream1, "ti_stream1");
    check_outputs(info, "stream1", outstream1);
    bench_run(log, info, info, run_ti_streamall, "ti_streamall");
    check_outputs(info, "streamall", outstreamall);
  }
  if (log)
  {
    fprintf(log, "\n  )");
  }
  printf("\n");
}


----------------------------
***/


