#include <assert.h>
#include <candles.h>
#include <fuzzer.c>
#include <indicators.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
double optionsd_small[] = {-20, -2, -1, 0, .7, 1, 2, 3, 4, 5, 6, 7, 8, 10, 20, 100, 999};
double optionsd_large[] = {-5, 0, 1, 2, 5};
double dummy_in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
double dummy_in0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double dummy_ot[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
const int input_size = (sizeof(dummy_in)) / (sizeof(double));
const int sizes[] = {0, 1, 2, 3, 4, 8, 20};
const int sizes_count = (sizeof(sizes)) / (sizeof(int));
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

int errors_cnt = 0;
void check_output(const ti_indicator_info *info, int size, const double * const *inputs, const double *options, double * const *outputs)
{
  const int s = info->start(options);
  int o;
  for (o = 0; o < info->outputs; o += 1)
  {
    helper_check_output_1(info, size, inputs, options, outputs, s, o);
  }

}

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
double optionsd_small[] = {-20, -2, -1, 0, .7, 1, 2, 3, 4, 5, 6, 7, 8, 10, 20, 100, 999};
double optionsd_large[] = {-5, 0, 1, 2, 5};
double dummy_in[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
double dummy_in0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double dummy_ot[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
const int input_size = (sizeof(dummy_in)) / (sizeof(double));
const int sizes[] = {0, 1, 2, 3, 4, 8, 20};
const int sizes_count = (sizeof(sizes)) / (sizeof(int));
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

int errors_cnt = 0;
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
          break;

        case 1:
          if (((op > 4) && (op > ((max * 1.5) + 2))) || ((op < (-4)) && (op < ((min * 0.5) - 3))))
        {
          do
          {
            int k;
            int j;
            printf("\nInputs:");
            for (k = 0; k < input_size; k += 1)
            {
              printf(" %f", inputs[0][k]);
            }

            printf("\nOptions:");
            for (k = 0; k < info->options; k += 1)
            {
              printf(" %f", options[k]);
            }

            for (j = 0; j < info->outputs; j += 1)
            {
              printf("\nOutput[%d]:", j);
              for (k = 0; k < input_size; k += 1)
              {
                printf(" %f", outputs[j][k]);
              }

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

    printf("\r                                                                          \r");
    j = 0;
    do
    {
      options_index[j] = (options_index[j] + 1) % choices;
    }
    while (options_index[j++] == 0);
  }
  while (j <= opt_count);
  assert(.1 > fabs(count - pow(choices, opt_count)));
}

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

void helper_check_output_1(const ti_indicator_info * const info, int size, const double * const * const inputs, const double * const options, double * const * const outputs, const int s, int o)
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
            {
              printf(" %f", inputs[0][k]);
            }

            printf("\nOptions:");
            for (k = 0; k < info->options; k += 1)
            {
              printf(" %f", options[k]);
            }

            for (j = 0; j < info->outputs; j += 1)
            {
              printf("\nOutput[%d]:", j);
              for (k = 0; k < input_size; k += 1)
              {
                printf(" %f", outputs[j][k]);
              }

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

