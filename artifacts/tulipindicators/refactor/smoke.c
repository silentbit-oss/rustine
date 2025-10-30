#include <assert.h>
#include <buffer.h>
#include <candles.h>
#include <indicators.h>
#include <localbuffer.h>
#include <math.h>
#include <minctest.h>
#include <smoke.c>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *ti_version(void);
long int ti_build(void);
int ti_indicator_count(void);
typedef int (*ti_indicator_start_function)(const double *options);
typedef int (*ti_indicator_function)(int size, const double * const *inputs, const double *options, double * const *outputs);
struct ti_stream;
typedef struct ti_stream ti_stream;
typedef int (*ti_indicator_stream_new)(const double *options, ti_stream **stream);
typedef int (*ti_indicator_stream_run)(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
typedef void (*ti_indicator_stream_free)(ti_stream *stream);
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
} ti_indicator_info;
extern ti_indicator_info ti_indicators[];
const ti_indicator_info *ti_find_indicator(const char *name);
int ti_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
ti_indicator_info *ti_stream_get_info(ti_stream *stream);
int ti_stream_get_progress(ti_stream *stream);
void ti_stream_free(ti_stream *stream);
int ti_abs_start(const double *options);
int ti_abs(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_acos_start(const double *options);
int ti_acos(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ad_start(const double *options);
int ti_ad(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_add_start(const double *options);
int ti_add(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_adosc_start(const double *options);
int ti_adosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_adx_start(const double *options);
int ti_adx(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_adxr_start(const double *options);
int ti_adxr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ao_start(const double *options);
int ti_ao(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_apo_start(const double *options);
int ti_apo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_aroon_start(const double *options);
int ti_aroon(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_aroonosc_start(const double *options);
int ti_aroonosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_asin_start(const double *options);
int ti_asin(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atan_start(const double *options);
int ti_atan(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atr_start(const double *options);
int ti_atr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atr_ref(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atr_stream_new(const double *options, ti_stream **stream);
int ti_atr_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
void ti_atr_stream_free(ti_stream *stream);
int ti_avgprice_start(const double *options);
int ti_avgprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_bbands_start(const double *options);
int ti_bbands(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_bop_start(const double *options);
int ti_bop(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cci_start(const double *options);
int ti_cci(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ceil_start(const double *options);
int ti_ceil(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cmo_start(const double *options);
int ti_cmo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cos_start(const double *options);
int ti_cos(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cosh_start(const double *options);
int ti_cosh(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_crossany_start(const double *options);
int ti_crossany(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_crossover_start(const double *options);
int ti_crossover(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cvi_start(const double *options);
int ti_cvi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_decay_start(const double *options);
int ti_decay(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dema_start(const double *options);
int ti_dema(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_di_start(const double *options);
int ti_di(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_div_start(const double *options);
int ti_div(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dm_start(const double *options);
int ti_dm(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dpo_start(const double *options);
int ti_dpo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dx_start(const double *options);
int ti_dx(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_edecay_start(const double *options);
int ti_edecay(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ema_start(const double *options);
int ti_ema(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_emv_start(const double *options);
int ti_emv(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_exp_start(const double *options);
int ti_exp(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_fisher_start(const double *options);
int ti_fisher(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_floor_start(const double *options);
int ti_floor(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_fosc_start(const double *options);
int ti_fosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_hma_start(const double *options);
int ti_hma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_kama_start(const double *options);
int ti_kama(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_kvo_start(const double *options);
int ti_kvo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_lag_start(const double *options);
int ti_lag(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_linreg_start(const double *options);
int ti_linreg(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_linregintercept_start(const double *options);
int ti_linregintercept(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_linregslope_start(const double *options);
int ti_linregslope(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ln_start(const double *options);
int ti_ln(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_log10_start(const double *options);
int ti_log10(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_macd_start(const double *options);
int ti_macd(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_marketfi_start(const double *options);
int ti_marketfi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mass_start(const double *options);
int ti_mass(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_max_start(const double *options);
int ti_max(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_max_ref(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_md_start(const double *options);
int ti_md(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_medprice_start(const double *options);
int ti_medprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mfi_start(const double *options);
int ti_mfi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_min_start(const double *options);
int ti_min(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_min_ref(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mom_start(const double *options);
int ti_mom(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_msw_start(const double *options);
int ti_msw(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mul_start(const double *options);
int ti_mul(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_natr_start(const double *options);
int ti_natr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_nvi_start(const double *options);
int ti_nvi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_obv_start(const double *options);
int ti_obv(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ppo_start(const double *options);
int ti_ppo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_psar_start(const double *options);
int ti_psar(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_pvi_start(const double *options);
int ti_pvi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_qstick_start(const double *options);
int ti_qstick(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_roc_start(const double *options);
int ti_roc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_rocr_start(const double *options);
int ti_rocr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_round_start(const double *options);
int ti_round(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_rsi_start(const double *options);
int ti_rsi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sin_start(const double *options);
int ti_sin(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sinh_start(const double *options);
int ti_sinh(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sma_start(const double *options);
int ti_sma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sma_stream_new(const double *options, ti_stream **stream);
int ti_sma_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
void ti_sma_stream_free(ti_stream *stream);
int ti_sqrt_start(const double *options);
int ti_sqrt(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stddev_start(const double *options);
int ti_stddev(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stderr_start(const double *options);
int ti_stderr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stoch_start(const double *options);
int ti_stoch(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stochrsi_start(const double *options);
int ti_stochrsi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sub_start(const double *options);
int ti_sub(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sum_start(const double *options);
int ti_sum(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tan_start(const double *options);
int ti_tan(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tanh_start(const double *options);
int ti_tanh(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tema_start(const double *options);
int ti_tema(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_todeg_start(const double *options);
int ti_todeg(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_torad_start(const double *options);
int ti_torad(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tr_start(const double *options);
int ti_tr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_trima_start(const double *options);
int ti_trima(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_trix_start(const double *options);
int ti_trix(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_trunc_start(const double *options);
int ti_trunc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tsf_start(const double *options);
int ti_tsf(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_typprice_start(const double *options);
int ti_typprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ultosc_start(const double *options);
int ti_ultosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_var_start(const double *options);
int ti_var(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vhf_start(const double *options);
int ti_vhf(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vidya_start(const double *options);
int ti_vidya(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_volatility_start(const double *options);
int ti_volatility(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vosc_start(const double *options);
int ti_vosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vwma_start(const double *options);
int ti_vwma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wad_start(const double *options);
int ti_wad(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wcprice_start(const double *options);
int ti_wcprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wilders_start(const double *options);
int ti_wilders(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_willr_start(const double *options);
int ti_willr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wma_start(const double *options);
int ti_wma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_zlema_start(const double *options);
int ti_zlema(int size, const double * const *inputs, const double *options, double * const *outputs);
const char *tc_version(void);
long int tc_build(void);
int tc_candle_count(void);
typedef double TC_REAL;
typedef struct tc_result tc_result;
typedef uint64_t tc_set;
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config;
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit;
typedef int (*tc_candle_function)(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info;
extern tc_candle_info tc_candles[];
const tc_candle_info *tc_find_candle(const char *name);
const tc_candle_info *tc_get_info(tc_set pattern);
const tc_config *tc_config_default();
void tc_config_set_to_default(tc_config *config);
tc_result *tc_result_new();
void tc_result_free(tc_result *result);
int tc_result_count(const tc_result *result);
int tc_result_pattern_count(const tc_result *result);
tc_hit tc_result_get(const tc_result *result, int index);
tc_set tc_result_at(const tc_result *result, int index);
int tc_run(tc_set patterns, int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_abandoned_baby_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_abandoned_baby_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_big_black_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_big_white_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_black_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_dragonfly_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_engulfing_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_engulfing_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_evening_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_evening_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_four_price_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_gravestone_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_hanging_man(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_inverted_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_long_legged_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_morning_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_morning_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_shooting_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_spinning_top(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_three_black_crows(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_three_white_soldiers(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_white_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
static int ltests = 0;
static int lfails = 0;
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer;
ti_buffer *ti_buffer_new(int size);
void ti_buffer_free(ti_buffer *buffer);
int tested_ind[104] = {0};
int tested_cnd[26] = {0};
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

void test_ind_name(FILE *fp, const char *name, int count)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    printf("(WARN) Couldn't find indicator %s\n", name);
    printf("---------------------------------------------");
    static char buf[4096];
    while (fgets(buf, 4096, fp) && ((buf[0] == '{') || (buf[0] == '#')))
    {
      ;
    }

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
    helper_test_ind_name_1(&i, info, options, inputs, answers, outputs, input_size, answer_size);
  }
  if (info->indicator_ref)
  {
    helper_test_ind_name_2(&i, info, options, inputs, answers, outputs, input_size, answer_size);
  }
  if (info->stream_new)
  {
    helper_test_ind_name_3(&i, info, options, inputs, answers, outputs, input_size, answer_size);
  }
  for (i = 0; i < info->inputs; i += 1)
  {
    free(inputs[i]);
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    free(answers[i]);
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    free(outputs[i]);
  }

}

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


const char *ti_version(void);
long int ti_build(void);
int ti_indicator_count(void);
typedef int (*ti_indicator_start_function)(const double *options);
typedef int (*ti_indicator_function)(int size, const double * const *inputs, const double *options, double * const *outputs);
struct ti_stream;
typedef struct ti_stream ti_stream;
typedef int (*ti_indicator_stream_new)(const double *options, ti_stream **stream);
typedef int (*ti_indicator_stream_run)(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
typedef void (*ti_indicator_stream_free)(ti_stream *stream);
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
} ti_indicator_info;
extern ti_indicator_info ti_indicators[];
const ti_indicator_info *ti_find_indicator(const char *name);
int ti_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
ti_indicator_info *ti_stream_get_info(ti_stream *stream);
int ti_stream_get_progress(ti_stream *stream);
void ti_stream_free(ti_stream *stream);
int ti_abs_start(const double *options);
int ti_abs(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_acos_start(const double *options);
int ti_acos(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ad_start(const double *options);
int ti_ad(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_add_start(const double *options);
int ti_add(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_adosc_start(const double *options);
int ti_adosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_adx_start(const double *options);
int ti_adx(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_adxr_start(const double *options);
int ti_adxr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ao_start(const double *options);
int ti_ao(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_apo_start(const double *options);
int ti_apo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_aroon_start(const double *options);
int ti_aroon(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_aroonosc_start(const double *options);
int ti_aroonosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_asin_start(const double *options);
int ti_asin(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atan_start(const double *options);
int ti_atan(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atr_start(const double *options);
int ti_atr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atr_ref(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_atr_stream_new(const double *options, ti_stream **stream);
int ti_atr_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
void ti_atr_stream_free(ti_stream *stream);
int ti_avgprice_start(const double *options);
int ti_avgprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_bbands_start(const double *options);
int ti_bbands(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_bop_start(const double *options);
int ti_bop(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cci_start(const double *options);
int ti_cci(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ceil_start(const double *options);
int ti_ceil(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cmo_start(const double *options);
int ti_cmo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cos_start(const double *options);
int ti_cos(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cosh_start(const double *options);
int ti_cosh(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_crossany_start(const double *options);
int ti_crossany(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_crossover_start(const double *options);
int ti_crossover(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_cvi_start(const double *options);
int ti_cvi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_decay_start(const double *options);
int ti_decay(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dema_start(const double *options);
int ti_dema(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_di_start(const double *options);
int ti_di(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_div_start(const double *options);
int ti_div(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dm_start(const double *options);
int ti_dm(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dpo_start(const double *options);
int ti_dpo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_dx_start(const double *options);
int ti_dx(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_edecay_start(const double *options);
int ti_edecay(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ema_start(const double *options);
int ti_ema(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_emv_start(const double *options);
int ti_emv(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_exp_start(const double *options);
int ti_exp(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_fisher_start(const double *options);
int ti_fisher(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_floor_start(const double *options);
int ti_floor(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_fosc_start(const double *options);
int ti_fosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_hma_start(const double *options);
int ti_hma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_kama_start(const double *options);
int ti_kama(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_kvo_start(const double *options);
int ti_kvo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_lag_start(const double *options);
int ti_lag(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_linreg_start(const double *options);
int ti_linreg(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_linregintercept_start(const double *options);
int ti_linregintercept(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_linregslope_start(const double *options);
int ti_linregslope(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ln_start(const double *options);
int ti_ln(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_log10_start(const double *options);
int ti_log10(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_macd_start(const double *options);
int ti_macd(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_marketfi_start(const double *options);
int ti_marketfi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mass_start(const double *options);
int ti_mass(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_max_start(const double *options);
int ti_max(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_max_ref(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_md_start(const double *options);
int ti_md(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_medprice_start(const double *options);
int ti_medprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mfi_start(const double *options);
int ti_mfi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_min_start(const double *options);
int ti_min(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_min_ref(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mom_start(const double *options);
int ti_mom(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_msw_start(const double *options);
int ti_msw(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_mul_start(const double *options);
int ti_mul(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_natr_start(const double *options);
int ti_natr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_nvi_start(const double *options);
int ti_nvi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_obv_start(const double *options);
int ti_obv(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ppo_start(const double *options);
int ti_ppo(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_psar_start(const double *options);
int ti_psar(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_pvi_start(const double *options);
int ti_pvi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_qstick_start(const double *options);
int ti_qstick(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_roc_start(const double *options);
int ti_roc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_rocr_start(const double *options);
int ti_rocr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_round_start(const double *options);
int ti_round(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_rsi_start(const double *options);
int ti_rsi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sin_start(const double *options);
int ti_sin(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sinh_start(const double *options);
int ti_sinh(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sma_start(const double *options);
int ti_sma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sma_stream_new(const double *options, ti_stream **stream);
int ti_sma_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs);
void ti_sma_stream_free(ti_stream *stream);
int ti_sqrt_start(const double *options);
int ti_sqrt(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stddev_start(const double *options);
int ti_stddev(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stderr_start(const double *options);
int ti_stderr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stoch_start(const double *options);
int ti_stoch(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_stochrsi_start(const double *options);
int ti_stochrsi(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sub_start(const double *options);
int ti_sub(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_sum_start(const double *options);
int ti_sum(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tan_start(const double *options);
int ti_tan(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tanh_start(const double *options);
int ti_tanh(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tema_start(const double *options);
int ti_tema(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_todeg_start(const double *options);
int ti_todeg(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_torad_start(const double *options);
int ti_torad(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tr_start(const double *options);
int ti_tr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_trima_start(const double *options);
int ti_trima(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_trix_start(const double *options);
int ti_trix(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_trunc_start(const double *options);
int ti_trunc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_tsf_start(const double *options);
int ti_tsf(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_typprice_start(const double *options);
int ti_typprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_ultosc_start(const double *options);
int ti_ultosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_var_start(const double *options);
int ti_var(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vhf_start(const double *options);
int ti_vhf(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vidya_start(const double *options);
int ti_vidya(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_volatility_start(const double *options);
int ti_volatility(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vosc_start(const double *options);
int ti_vosc(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_vwma_start(const double *options);
int ti_vwma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wad_start(const double *options);
int ti_wad(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wcprice_start(const double *options);
int ti_wcprice(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wilders_start(const double *options);
int ti_wilders(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_willr_start(const double *options);
int ti_willr(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_wma_start(const double *options);
int ti_wma(int size, const double * const *inputs, const double *options, double * const *outputs);
int ti_zlema_start(const double *options);
int ti_zlema(int size, const double * const *inputs, const double *options, double * const *outputs);
const char *tc_version(void);
long int tc_build(void);
int tc_candle_count(void);
typedef double TC_REAL;
typedef struct tc_result tc_result;
typedef uint64_t tc_set;
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config;
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit;
typedef int (*tc_candle_function)(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info;
extern tc_candle_info tc_candles[];
const tc_candle_info *tc_find_candle(const char *name);
const tc_candle_info *tc_get_info(tc_set pattern);
const tc_config *tc_config_default();
void tc_config_set_to_default(tc_config *config);
tc_result *tc_result_new();
void tc_result_free(tc_result *result);
int tc_result_count(const tc_result *result);
int tc_result_pattern_count(const tc_result *result);
tc_hit tc_result_get(const tc_result *result, int index);
tc_set tc_result_at(const tc_result *result, int index);
int tc_run(tc_set patterns, int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_abandoned_baby_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_abandoned_baby_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_big_black_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_big_white_candle(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_black_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_dragonfly_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_engulfing_bear(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_engulfing_bull(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_evening_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_evening_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_four_price_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_gravestone_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_hanging_man(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_inverted_hammer(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_long_legged_doji(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_morning_doji_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_morning_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_shooting_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_spinning_top(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_star(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_three_black_crows(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_three_white_soldiers(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
int tc_white_marubozu(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output);
static int ltests = 0;
static int lfails = 0;
typedef struct 
{
  int size;
  int pushes;
  int index;
  double sum;
  double vals[1];
} ti_buffer;
ti_buffer *ti_buffer_new(int size);
void ti_buffer_free(ti_buffer *buffer);
int tested_ind[104] = {0};
int tested_cnd[26] = {0};
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

void test_ind_name(FILE *fp, const char *name, int count)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    printf("(WARN) Couldn't find indicator %s\n", name);
    printf("---------------------------------------------");
    static char buf[4096];
    while (fgets(buf, 4096, fp) && ((buf[0] == '{') || (buf[0] == '#')))
    {
      ;
    }

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
    const int steps[] = {1, 2, 3, 4, 5, 7, 13, 100, 1024};
    const int step_count = (sizeof(steps)) / (sizeof(int));
    for (int step_i = 0; step_i < step_count; step_i += 1)
    {
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
    }

  }
  for (i = 0; i < info->inputs; i += 1)
  {
    free(inputs[i]);
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    free(answers[i]);
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    free(outputs[i]);
  }

}

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
  while (1);
  tc_result_free(output);
  free(inputs[0]);
  free(inputs[1]);
  free(inputs[2]);
  free(inputs[3]);
}

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

  fclose(fp);
}

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

void helper_test_ind_name_1(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size)
{
  int i = *i_ref;
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

  *i_ref = i;
}

void helper_test_ind_name_2(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size)
{
  int i = *i_ref;
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

  *i_ref = i;
}

void helper_test_ind_name_3(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size)
{
  int i = *i_ref;
  const int steps[] = {1, 2, 3, 4, 5, 7, 13, 100, 1024};
  const int step_count = (sizeof(steps)) / (sizeof(int));
  for (int step_i = 0; step_i < step_count; step_i += 1)
  {
    helper_helper_test_ind_name_3_1(&i, info, options, inputs, answers, outputs, input_size, answer_size, steps, step_i);
  }

  *i_ref = i;
}

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
    helper_helper_test_candles_1_1(output, negate, info, num);
  }

  const int cnd_num = (int) (info - tc_candles);
  if (count)
  {
    tested_cnd[cnd_num] = 1;
  }
}

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

void helper_helper_test_ind_name_3_1(int * const i_ref, const ti_indicator_info * const info, double options[16], double *inputs[16], double *answers[16], double *outputs[16], int input_size, int answer_size, const int steps[], int step_i)
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
    helper_helper_helper_test_ind_name_3_1_1(&i, info, inputs, outputs, input_size, step, stream, bar);
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

void helper_helper_test_candles_1_1(tc_result * const output, int negate, const tc_candle_info * const info, char * const num)
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

void helper_helper_helper_test_ind_name_3_1_1(int * const i_ref, const ti_indicator_info * const info, double *inputs[16], double *outputs[16], int input_size, const int step, ti_stream * const stream, int bar)
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

