#include <assert.h>
#include <candles.h>
#include <cli.c>
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
char *next_line(FILE *fp)
{
  static char buf[131072];
  while (fgets(buf, 131072, fp))
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

void run(const char *name, const char *in, const char *out)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    fprintf(stderr, "(ERROR) Couldn't find indicator %s\n", name);
    return;
  }
  FILE *fin = fopen(in, "r");
  if (!fin)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for input.\n", in);
    return;
  }
  char *line = next_line(fin);
  double options[16];
  double *o = options;
  unsigned int o_idx = 0;
  const char *s = strtok(line, " \n\r");
  unsigned int s_idx = 0;
  if (s)
  {
    do
    {
      o[o_idx] = atof(s);
      o_idx += 1;
    }
    while (s_idx = strtok(0, " \n\r"));
  }
  if (((int) ((&o[o_idx]) - options)) != info->options)
  {
    fprintf(stderr, "(ERROR) Invalid number of options for %s. Expected %d, got %d\n", name, info->options, (int) ((&o[o_idx]) - options));
    return;
  }
  int i;
  double *inputs[16] = {0};
  double *outputs[16] = {0};
  int input_size = 0;
  for (i = 0; i < info->inputs; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 8192);
    input_size = get_array(fin, inputs[i]);
  }

  fclose(fin);
  for (i = 0; i < info->outputs; i += 1)
  {
    outputs[i] = malloc((sizeof(double)) * 8192);
  }

  {
    const int ret = info->indicator(input_size, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      fprintf(stderr, "(ERROR) Return value for %s of %d.\n", name, ret);
      return;
    }
  }
  FILE *fout = fopen(out, "w");
  if (!fout)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for output.\n", out);
    return;
  }
  const int out_size = input_size - info->start(options);
  for (i = 0; i < info->outputs; i += 1)
  {
    fprintf(fout, "{");
    for (int j = 0; j < out_size; j += 1)
    {
      fprintf(fout, "%f%s", outputs[i][j], (j == (out_size - 1)) ? ("") : (","));
    }

    fprintf(fout, "}\n");
  }

  fclose(fout);
  for (i = 0; i < info->inputs; i += 1)
  {
    free(inputs[i]);
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    free(outputs[i]);
  }

}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("Usage: cli indicator_name infile outfile\n");
  }
  const char *name = argv[1];
  const char *in = argv[2];
  const char *out = argv[3];
  run(name, in, out);
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
char *next_line(FILE *fp)
{
  static char buf[131072];
  while (fgets(buf, 131072, fp))
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

void run(const char *name, const char *in, const char *out)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    fprintf(stderr, "(ERROR) Couldn't find indicator %s\n", name);
    return;
  }
  FILE *fin = fopen(in, "r");
  if (!fin)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for input.\n", in);
    return;
  }
  char *line = next_line(fin);
  double options[16];
  double *o = options;
  unsigned int o_idx = 0;
  const char *s = strtok(line, " \n\r");
  unsigned int s_idx = 0;
  if (s)
  {
    do
    {
      o[o_idx] = atof(s);
      o_idx += 1;
    }
    while (s_idx = strtok(0, " \n\r"));
  }
  if (((int) ((&o[o_idx]) - options)) != info->options)
  {
    fprintf(stderr, "(ERROR) Invalid number of options for %s. Expected %d, got %d\n", name, info->options, (int) ((&o[o_idx]) - options));
    return;
  }
  int i;
  double *inputs[16] = {0};
  double *outputs[16] = {0};
  int input_size = 0;
  for (i = 0; i < info->inputs; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 8192);
    input_size = get_array(fin, inputs[i]);
  }

  fclose(fin);
  for (i = 0; i < info->outputs; i += 1)
  {
    outputs[i] = malloc((sizeof(double)) * 8192);
  }

  {
    const int ret = info->indicator(input_size, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      fprintf(stderr, "(ERROR) Return value for %s of %d.\n", name, ret);
      return;
    }
  }
  FILE *fout = fopen(out, "w");
  if (!fout)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for output.\n", out);
    return;
  }
  const int out_size = input_size - info->start(options);
  for (i = 0; i < info->outputs; i += 1)
  {
    fprintf(fout, "{");
    for (int j = 0; j < out_size; j += 1)
    {
      fprintf(fout, "%f%s", outputs[i][j], (j == (out_size - 1)) ? ("") : (","));
    }

    fprintf(fout, "}\n");
  }

  fclose(fout);
  for (i = 0; i < info->inputs; i += 1)
  {
    free(inputs[i]);
  }

  for (i = 0; i < info->outputs; i += 1)
  {
    free(outputs[i]);
  }

}

int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("Usage: cli indicator_name infile outfile\n");
  }
  const char *name = argv[1];
  const char *in = argv[2];
  const char *out = argv[3];
  run(name, in, out);
  return 0;
}

