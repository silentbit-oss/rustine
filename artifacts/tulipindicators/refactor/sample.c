#include <assert.h>
#include <ctype.h>
#include <indicators.h>
#include <math.h>
#include <sample.c>
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
double out[5][15];
const char *datet[] = {"2005-11-01", "2005-11-02", "2005-11-03", "2005-11-04", "2005-11-07", "2005-11-08", "2005-11-09", "2005-11-10", "2005-11-11", "2005-11-14", "2005-11-15", "2005-11-16", "2005-11-17", "2005-11-18", "2005-11-21"};
double date[] = {51101, 51102, 51103, 51104, 51107, 51108, 51109, 51110, 51111, 51114, 51115, 51116, 51117, 51118, 51121};
double open[] = {81.85, 81.2, 81.55, 82.91, 83.1, 83.41, 82.71, 82.7, 84.2, 84.25, 84.03, 85.45, 86.18, 88, 87.6};
double high[] = {82.15, 81.89, 83.03, 83.3, 83.85, 83.9, 83.33, 84.3, 84.84, 85, 85.9, 86.58, 86.98, 88, 87.87};
double low[] = {81.29, 80.64, 81.31, 82.65, 83.07, 83.11, 82.49, 82.3, 84.15, 84.11, 84.03, 85.39, 85.76, 87.17, 87.01};
double close[] = {81.59, 81.06, 82.87, 83, 83.61, 83.15, 82.84, 83.99, 84.55, 84.36, 85.53, 86.54, 86.89, 87.77, 87.29};
double volume[] = {5653100, 6447400, 7690900, 3831400, 4455100, 3798000, 3936200, 4732000, 4841300, 3915300, 6830800, 6694100, 5293600, 7985800, 4807900};
double alternative[] = {.2, .3, .4, .3, .5, .7, .75, .9, .9, 1, 1, .2, .1, -.1, -.5};
int main(int argc, char **argv)
{
  const ti_indicator_info *info = ti_indicators;
  unsigned int info_idx = 0;
  if (argc < 2)
  {
    printf("No indicator given.\n");
    printf("Example:\n");
    printf("\tsample ma 5");
    return 1;
  }
  if (strcmp(argv[1], "--version") == 0)
  {
    printf("TI VERSION: %s, TI BUILD: %d\n", "0.9.2", 1746800254);
    return 0;
  }
  if (strcmp(argv[1], "--list") == 0)
  {
    helper_main_2(info, info_idx);
  }
  info_idx = ti_find_indicator(argv[1]);
  if (!(&info[info_idx]))
  {
    printf("Couldn't find indicator: %s\n", argv[1]);
    return 1;
  }
  const double *inputs[] = {0, 0, 0, 0, 0};
  double *outputs[] = {out[0], out[1], out[2], out[3], out[4]};
  int o = 0;
  int h = 0;
  int l = 0;
  int c = 0;
  int r = 0;
  int r2 = 0;
  int v = 0;
  int a = 0;
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    helper_main_1(&o, &h, &l, &c, &r, &r2, &v, &j, info, inputs);
  }

  const char *alts[] = {"acos", "asin", "atan", "cosh", "sinh", "tanh", "todeg", 0};
  {
    const char **alt = alts;
    unsigned int alt_idx = 0;
    while (alt[alt_idx])
    {
      if (strcmp(*(&alt[alt_idx]), info->name) == 0)
      {
        r = 0;
        a = 1;
        for (j = 0; j < info->inputs; j += 1)
        {
          inputs[j] = alternative;
        }

        break;
      }
      alt_idx += 1;
    }

  }
  double options[10];
  {
    int i;
    for (i = 0; i < info->options; i += 1)
    {
      if (argc < (3 + i))
      {
        printf("*ERROR NOT ENOUGH OPTIONS*\n");
        for (int k = 1; k < argc; k += 1)
        {
          printf("%s ", argv[k]);
        }

        printf("\n");
        return 1;
      }
      options[i] = atof(argv[2 + i]);
    }

  }
  int start = info->start(options);
  const int ret = info->indicator(15, inputs, options, outputs);
  if (ret == 0)
  {
    helper_main_3(info, o, h, l, c, r, r2, v, a, start);
  }
  else
  {
    if (ret == 1)
    {
      printf("*ERROR INVALID OPTION*\n");
      for (int i = 1; i < argc; i += 1)
      {
        printf("%s ", argv[i]);
      }

      printf("\n");
    }
    else
    {
      printf("*ERROR*\n");
    }
    return 1;
  }
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
double out[5][15];
const char *datet[] = {"2005-11-01", "2005-11-02", "2005-11-03", "2005-11-04", "2005-11-07", "2005-11-08", "2005-11-09", "2005-11-10", "2005-11-11", "2005-11-14", "2005-11-15", "2005-11-16", "2005-11-17", "2005-11-18", "2005-11-21"};
double date[] = {51101, 51102, 51103, 51104, 51107, 51108, 51109, 51110, 51111, 51114, 51115, 51116, 51117, 51118, 51121};
double open[] = {81.85, 81.2, 81.55, 82.91, 83.1, 83.41, 82.71, 82.7, 84.2, 84.25, 84.03, 85.45, 86.18, 88, 87.6};
double high[] = {82.15, 81.89, 83.03, 83.3, 83.85, 83.9, 83.33, 84.3, 84.84, 85, 85.9, 86.58, 86.98, 88, 87.87};
double low[] = {81.29, 80.64, 81.31, 82.65, 83.07, 83.11, 82.49, 82.3, 84.15, 84.11, 84.03, 85.39, 85.76, 87.17, 87.01};
double close[] = {81.59, 81.06, 82.87, 83, 83.61, 83.15, 82.84, 83.99, 84.55, 84.36, 85.53, 86.54, 86.89, 87.77, 87.29};
double volume[] = {5653100, 6447400, 7690900, 3831400, 4455100, 3798000, 3936200, 4732000, 4841300, 3915300, 6830800, 6694100, 5293600, 7985800, 4807900};
double alternative[] = {.2, .3, .4, .3, .5, .7, .75, .9, .9, 1, 1, .2, .1, -.1, -.5};
int main(int argc, char **argv)
{
  const ti_indicator_info *info = ti_indicators;
  unsigned int info_idx = 0;
  if (argc < 2)
  {
    printf("No indicator given.\n");
    printf("Example:\n");
    printf("\tsample ma 5");
    return 1;
  }
  if (strcmp(argv[1], "--version") == 0)
  {
    printf("TI VERSION: %s, TI BUILD: %d\n", "0.9.2", 1746800254);
    return 0;
  }
  if (strcmp(argv[1], "--list") == 0)
  {
    do
    {
      if (info->type == 1)
      {
        printf("type overlay ");
      }
      else
        if (info->type == 2)
      {
        printf("type indicator ");
      }
      else
        if (info->type == 3)
      {
        printf("type math ");
      }
      else
        if (info->type == 4)
      {
        printf("type simple ");
      }
      else
        printf("type unknown ");
      printf("name %s ", info->name);
      printf("full_name {%s} ", info->full_name);
      int i;
      printf("inputs {");
      for (i = 0; i < info->inputs; i += 1)
      {
        printf("%s%s", (i) ? (" ") : (""), info->input_names[i]);
      }

      printf("} ");
      printf("options {");
      for (i = 0; i < info->options; i += 1)
      {
        printf("%s{%s}", (i) ? (" ") : (""), info->option_names[i]);
      }

      printf("} ");
      printf("outputs {");
      for (i = 0; i < info->outputs; i += 1)
      {
        printf("%s{%s}", (i) ? (" ") : (""), info->output_names[i]);
      }

      printf("}");
      printf("\n");
    }
    while ((++(&info[info_idx]))->name);
    return 0;
  }
  info_idx = ti_find_indicator(argv[1]);
  if (!(&info[info_idx]))
  {
    printf("Couldn't find indicator: %s\n", argv[1]);
    return 1;
  }
  const double *inputs[] = {0, 0, 0, 0, 0};
  double *outputs[] = {out[0], out[1], out[2], out[3], out[4]};
  int o = 0;
  int h = 0;
  int l = 0;
  int c = 0;
  int r = 0;
  int r2 = 0;
  int v = 0;
  int a = 0;
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    if (strcmp(info->input_names[j], "open") == 0)
    {
      inputs[j] = open;
      o = 1;
    }
    else
      if (strcmp(info->input_names[j], "high") == 0)
    {
      inputs[j] = high;
      h = 1;
    }
    else
      if (strcmp(info->input_names[j], "low") == 0)
    {
      inputs[j] = low;
      l = 1;
    }
    else
      if (strcmp(info->input_names[j], "close") == 0)
    {
      inputs[j] = close;
      c = 1;
    }
    else
      if (strcmp(info->input_names[j], "volume") == 0)
    {
      inputs[j] = volume;
      v = 1;
    }
    else
      if (strcmp(info->input_names[j], "real") == 0)
    {
      if (!r)
      {
        inputs[j] = close;
        r = 1;
      }
      else
      {
        inputs[j] = open;
        r2 = 1;
      }
    }
    else
    {
      assert(0);
    }
    ;
  }

  const char *alts[] = {"acos", "asin", "atan", "cosh", "sinh", "tanh", "todeg", 0};
  {
    const char **alt = alts;
    unsigned int alt_idx = 0;
    while (alt[alt_idx])
    {
      if (strcmp(*(&alt[alt_idx]), info->name) == 0)
      {
        r = 0;
        a = 1;
        for (j = 0; j < info->inputs; j += 1)
        {
          inputs[j] = alternative;
        }

        break;
      }
      alt_idx += 1;
    }

  }
  double options[10];
  {
    int i;
    for (i = 0; i < info->options; i += 1)
    {
      if (argc < (3 + i))
      {
        printf("*ERROR NOT ENOUGH OPTIONS*\n");
        for (int k = 1; k < argc; k += 1)
        {
          printf("%s ", argv[k]);
        }

        printf("\n");
        return 1;
      }
      options[i] = atof(argv[2 + i]);
    }

  }
  int start = info->start(options);
  const int ret = info->indicator(15, inputs, options, outputs);
  if (ret == 0)
  {
    int i;
    int k;
    int bad = 0;
    printf("date        ");
    if (o)
    {
      printf(" open   ");
    }
    if (h)
    {
      printf(" high   ");
    }
    if (l)
    {
      printf(" low    ");
    }
    if (c)
    {
      printf(" close  ");
    }
    if (v)
    {
      printf(" volume ");
    }
    if (r)
    {
      printf(" input  ");
    }
    if (r2)
    {
      printf(" input2  ");
    }
    if (a)
    {
      printf(" input  ");
    }
    for (i = 0; i < info->outputs; i += 1)
    {
      printf(" %s", info->output_names[i]);
    }

    printf("\n");
    for (i = 0; i < 15; i += 1)
    {
      printf("%s", datet[i]);
      if (o)
      {
        printf(" %8.2f", open[i]);
      }
      if (h)
      {
        printf(" %8.2f", high[i]);
      }
      if (l)
      {
        printf(" %8.2f", low[i]);
      }
      if (c)
      {
        printf(" %8.2f", close[i]);
      }
      if (v)
      {
        printf(" %8.0f", volume[i]);
      }
      if (r)
      {
        printf(" %8.2f", close[i]);
      }
      if (r2)
      {
        printf(" %8.2f", open[i]);
      }
      if (a)
      {
        printf(" %8.2f", alternative[i]);
      }
      if (i >= start)
      {
        for (k = 0; k < info->outputs; k += 1)
        {
          if (out[k][i - start] != out[k][i - start])
          {
            bad = 1;
          }
          printf(" %8.3f", out[k][i - start]);
        }

      }
      printf("\n");
    }

    if (bad)
    {
      printf("\nERROR NaN in outputs (%s).\n", info->name);
      return 1;
    }
    return 0;
  }
  else
  {
    if (ret == 1)
    {
      printf("*ERROR INVALID OPTION*\n");
      for (int i = 1; i < argc; i += 1)
      {
        printf("%s ", argv[i]);
      }

      printf("\n");
    }
    else
    {
      printf("*ERROR*\n");
    }
    return 1;
  }
}

void helper_main_1(int * const o_ref, int * const h_ref, int * const l_ref, int * const c_ref, int * const r_ref, int * const r2_ref, int * const v_ref, int * const j_ref, const ti_indicator_info * const info, const double *inputs[])
{
  int o = *o_ref;
  int h = *h_ref;
  int l = *l_ref;
  int c = *c_ref;
  int r = *r_ref;
  int r2 = *r2_ref;
  int v = *v_ref;
  int j = *j_ref;
  if (strcmp(info->input_names[j], "open") == 0)
  {
    inputs[j] = open;
    o = 1;
  }
  else
    if (strcmp(info->input_names[j], "high") == 0)
  {
    inputs[j] = high;
    h = 1;
  }
  else
    if (strcmp(info->input_names[j], "low") == 0)
  {
    inputs[j] = low;
    l = 1;
  }
  else
    if (strcmp(info->input_names[j], "close") == 0)
  {
    inputs[j] = close;
    c = 1;
  }
  else
    if (strcmp(info->input_names[j], "volume") == 0)
  {
    inputs[j] = volume;
    v = 1;
  }
  else
    if (strcmp(info->input_names[j], "real") == 0)
  {
    if (!r)
    {
      inputs[j] = close;
      r = 1;
    }
    else
    {
      inputs[j] = open;
      r2 = 1;
    }
  }
  else
  {
    assert(0);
  }
  ;
  *o_ref = o;
  *h_ref = h;
  *l_ref = l;
  *c_ref = c;
  *r_ref = r;
  *r2_ref = r2;
  *v_ref = v;
  *j_ref = j;
}

int helper_main_2(const ti_indicator_info * const info, unsigned int info_idx)
{
  do
  {
    if (info->type == 1)
    {
      printf("type overlay ");
    }
    else
      if (info->type == 2)
    {
      printf("type indicator ");
    }
    else
      if (info->type == 3)
    {
      printf("type math ");
    }
    else
      if (info->type == 4)
    {
      printf("type simple ");
    }
    else
      printf("type unknown ");
    printf("name %s ", info->name);
    printf("full_name {%s} ", info->full_name);
    int i;
    printf("inputs {");
    for (i = 0; i < info->inputs; i += 1)
    {
      printf("%s%s", (i) ? (" ") : (""), info->input_names[i]);
    }

    printf("} ");
    printf("options {");
    for (i = 0; i < info->options; i += 1)
    {
      printf("%s{%s}", (i) ? (" ") : (""), info->option_names[i]);
    }

    printf("} ");
    printf("outputs {");
    for (i = 0; i < info->outputs; i += 1)
    {
      printf("%s{%s}", (i) ? (" ") : (""), info->output_names[i]);
    }

    printf("}");
    printf("\n");
  }
  while ((++(&info[info_idx]))->name);
  return 0;
}

int helper_main_3(const ti_indicator_info * const info, int o, int h, int l, int c, int r, int r2, int v, int a, int start)
{
  int i;
  int k;
  int bad = 0;
  printf("date        ");
  if (o)
  {
    printf(" open   ");
  }
  if (h)
  {
    printf(" high   ");
  }
  if (l)
  {
    printf(" low    ");
  }
  if (c)
  {
    printf(" close  ");
  }
  if (v)
  {
    printf(" volume ");
  }
  if (r)
  {
    printf(" input  ");
  }
  if (r2)
  {
    printf(" input2  ");
  }
  if (a)
  {
    printf(" input  ");
  }
  for (i = 0; i < info->outputs; i += 1)
  {
    printf(" %s", info->output_names[i]);
  }

  printf("\n");
  for (i = 0; i < 15; i += 1)
  {
    helper_helper_main_3_1(&k, &bad, info, o, h, l, c, r, r2, v, a, start, i);
  }

  if (bad)
  {
    printf("\nERROR NaN in outputs (%s).\n", info->name);
    return 1;
  }
  return 0;
}

void helper_helper_main_3_1(int * const k_ref, int * const bad_ref, const ti_indicator_info * const info, int o, int h, int l, int c, int r, int r2, int v, int a, int start, int i)
{
  int k = *k_ref;
  int bad = *bad_ref;
  printf("%s", datet[i]);
  if (o)
  {
    printf(" %8.2f", open[i]);
  }
  if (h)
  {
    printf(" %8.2f", high[i]);
  }
  if (l)
  {
    printf(" %8.2f", low[i]);
  }
  if (c)
  {
    printf(" %8.2f", close[i]);
  }
  if (v)
  {
    printf(" %8.0f", volume[i]);
  }
  if (r)
  {
    printf(" %8.2f", close[i]);
  }
  if (r2)
  {
    printf(" %8.2f", open[i]);
  }
  if (a)
  {
    printf(" %8.2f", alternative[i]);
  }
  if (i >= start)
  {
    for (k = 0; k < info->outputs; k += 1)
    {
      if (out[k][i - start] != out[k][i - start])
      {
        bad = 1;
      }
      printf(" %8.3f", out[k][i - start]);
    }

  }
  printf("\n");
  *k_ref = k;
  *bad_ref = bad;
}

