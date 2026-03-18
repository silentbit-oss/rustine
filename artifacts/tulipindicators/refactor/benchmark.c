#include <assert.h>
#include <benchmark.c>
#include <candles.h>
#include <ctype.h>
#include <indicators.h>
#include <math.h>
#include <minmax.h>
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
int bestof = 1;
int fails = 0;
double in[5][4000];
double out[3][4000];
double outref[3][4000];
double outstream1[3][4000];
double outstreamall[3][4000];
tc_result *outcnd = 0;
int ind_offset;
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
    helper_generate_inputs_1(&i, open, high, low, close, volume);
  }

  volume[0] = 0;
}

typedef int (*run_fun)(const ti_indicator_info *info, double *options, int goal);
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

void simple_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
}

void fast_slow_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}

void alma_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.5;
  options[2] = 1;
}

void bbands_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1.0;
}

void ce_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void copp_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 11;
  options[1] = 14;
  options[2] = period;
}

void kc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.77;
}

void kst_option_setter(double period, double *options, int ti)
{
  (void) ti;
  for (int i = 0; i < 4; i += 1)
  {
    options[i + 4] = (options[i] = period + ((period / 4.) * i));
  }

}

void macd_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = period + 1;
}

void mama_option_setter(double period, double *options, int ti)
{
  (void) ti;
  (void) period;
  options[0] = 0.5;
  options[1] = 0.05;
}

void pfe_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 5;
}

void posc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void ppo_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}

void psar_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 1 / period;
  options[1] = options[0] * 10;
}

void rmi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void rmta_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1 - (2. / (period + 1));
}

void rvi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 10;
}

void smi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 25;
  options[2] = 3;
}

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

void stochrsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period;
  options[2] = period;
  options[3] = 1;
}

void tsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void ultosc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period * 2;
  options[2] = period * 4;
}

void vidya_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = .2;
}

double stochrsi_output_adjust(double a)
{
  return a * 0.01;
}

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
int bestof = 1;
int fails = 0;
double in[5][4000];
double out[3][4000];
double outref[3][4000];
double outstream1[3][4000];
double outstreamall[3][4000];
tc_result *outcnd = 0;
int ind_offset;
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

typedef int (*run_fun)(const ti_indicator_info *info, double *options, int goal);
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

void simple_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
}

void fast_slow_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}

void alma_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.5;
  options[2] = 1;
}

void bbands_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1.0;
}

void ce_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void copp_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 11;
  options[1] = 14;
  options[2] = period;
}

void kc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 0.77;
}

void kst_option_setter(double period, double *options, int ti)
{
  (void) ti;
  for (int i = 0; i < 4; i += 1)
  {
    options[i + 4] = (options[i] = period + ((period / 4.) * i));
  }

}

void macd_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = period + 1;
}

void mama_option_setter(double period, double *options, int ti)
{
  (void) ti;
  (void) period;
  options[0] = 0.5;
  options[1] = 0.05;
}

void pfe_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 5;
}

void posc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void ppo_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
}

void psar_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = 1 / period;
  options[1] = options[0] * 10;
}

void rmi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void rmta_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 1 - (2. / (period + 1));
}

void rvi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 10;
}

void smi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 25;
  options[2] = 3;
}

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

void stochrsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period;
  options[2] = period;
  options[3] = 1;
}

void tsi_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = 3;
}

void ultosc_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period * 2;
  options[2] = period * 4;
}

void vidya_option_setter(double period, double *options, int ti)
{
  (void) ti;
  options[0] = period;
  options[1] = period + 10;
  options[2] = .2;
}

double stochrsi_output_adjust(double a)
{
  return a * 0.01;
}

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
  }

  if (log)
  {
    fprintf(log, ",\n    \"%s\" => array(\"elapsed\" => %d, \"performance\" => %d)", name, best_e, best_p);
  }
}

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

void helper_generate_inputs_1(int * const i_ref, double * const open, double * const high, double * const low, double * const close, double * const volume)
{
  int i = *i_ref;
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
  *i_ref = i;
}

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

