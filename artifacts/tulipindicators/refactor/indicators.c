#include <assert.h>
#include <indicators.c>
#include <indicators.h>
#include <math.h>
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
const char *ti_version(void)
{
  return "0.9.2";
}

long int ti_build(void)
{
  return 1746800254;
}

int ti_indicator_count(void)
{
  return 104;
}

struct ti_indicator_info ti_indicators[] = {{"abs", "Vector Absolute Value", ti_abs_start, ti_abs, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"abs", 0}, 0, 0, 0}, {"acos", "Vector Arccosine", ti_acos_start, ti_acos, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"acos", 0}, 0, 0, 0}, {"ad", "Accumulation/Distribution Line", ti_ad_start, ti_ad, 0, 2, 4, 0, 1, {"high", "low", "close", "volume", 0}, {"", 0}, {"ad", 0}, 0, 0, 0}, {"add", "Vector Addition", ti_add_start, ti_add, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"add", 0}, 0, 0, 0}, {"adosc", "Accumulation/Distribution Oscillator", ti_adosc_start, ti_adosc, 0, 2, 4, 2, 1, {"high", "low", "close", "volume", 0}, {"short_period", "long_period", 0}, {"adosc", 0}, 0, 0, 0}, {"adx", "Average Directional Movement Index", ti_adx_start, ti_adx, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"adx", 0}, 0, 0, 0}, {"adxr", "Average Directional Movement Rating", ti_adxr_start, ti_adxr, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"adxr", 0}, 0, 0, 0}, {"ao", "Awesome Oscillator", ti_ao_start, ti_ao, 0, 2, 2, 0, 1, {"high", "low", 0}, {"", 0}, {"ao", 0}, 0, 0, 0}, {"apo", "Absolute Price Oscillator", ti_apo_start, ti_apo, 0, 2, 1, 2, 1, {"real", 0}, {"short_period", "long_period", 0}, {"apo", 0}, 0, 0, 0}, {"aroon", "Aroon", ti_aroon_start, ti_aroon, 0, 2, 2, 1, 2, {"high", "low", 0}, {"period", 0}, {"aroon_down", "aroon_up", 0}, 0, 0, 0}, {"aroonosc", "Aroon Oscillator", ti_aroonosc_start, ti_aroonosc, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"aroonosc", 0}, 0, 0, 0}, {"asin", "Vector Arcsine", ti_asin_start, ti_asin, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"asin", 0}, 0, 0, 0}, {"atan", "Vector Arctangent", ti_atan_start, ti_atan, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"atan", 0}, 0, 0, 0}, {"atr", "Average True Range", ti_atr_start, ti_atr, ti_atr_ref, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"atr", 0}, ti_atr_stream_new, ti_atr_stream_run, ti_atr_stream_free}, {"avgprice", "Average Price", ti_avgprice_start, ti_avgprice, 0, 1, 4, 0, 1, {"open", "high", "low", "close", 0}, {"", 0}, {"avgprice", 0}, 0, 0, 0}, {"bbands", "Bollinger Bands", ti_bbands_start, ti_bbands, 0, 1, 1, 2, 3, {"real", 0}, {"period", "stddev", 0}, {"bbands_lower", "bbands_middle", "bbands_upper", 0}, 0, 0, 0}, {"bop", "Balance of Power", ti_bop_start, ti_bop, 0, 2, 4, 0, 1, {"open", "high", "low", "close", 0}, {"", 0}, {"bop", 0}, 0, 0, 0}, {"cci", "Commodity Channel Index", ti_cci_start, ti_cci, 0, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"cci", 0}, 0, 0, 0}, {"ceil", "Vector Ceiling", ti_ceil_start, ti_ceil, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"ceil", 0}, 0, 0, 0}, {"cmo", "Chande Momentum Oscillator", ti_cmo_start, ti_cmo, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"cmo", 0}, 0, 0, 0}, {"cos", "Vector Cosine", ti_cos_start, ti_cos, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"cos", 0}, 0, 0, 0}, {"cosh", "Vector Hyperbolic Cosine", ti_cosh_start, ti_cosh, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"cosh", 0}, 0, 0, 0}, {"crossany", "Crossany", ti_crossany_start, ti_crossany, 0, 3, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"crossany", 0}, 0, 0, 0}, {"crossover", "Crossover", ti_crossover_start, ti_crossover, 0, 3, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"crossover", 0}, 0, 0, 0}, {"cvi", "Chaikins Volatility", ti_cvi_start, ti_cvi, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"cvi", 0}, 0, 0, 0}, {"decay", "Linear Decay", ti_decay_start, ti_decay, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"decay", 0}, 0, 0, 0}, {"dema", "Double Exponential Moving Average", ti_dema_start, ti_dema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"dema", 0}, 0, 0, 0}, {"di", "Directional Indicator", ti_di_start, ti_di, 0, 2, 3, 1, 2, {"high", "low", "close", 0}, {"period", 0}, {"plus_di", "minus_di", 0}, 0, 0, 0}, {"div", "Vector Division", ti_div_start, ti_div, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"div", 0}, 0, 0, 0}, {"dm", "Directional Movement", ti_dm_start, ti_dm, 0, 2, 2, 1, 2, {"high", "low", 0}, {"period", 0}, {"plus_dm", "minus_dm", 0}, 0, 0, 0}, {"dpo", "Detrended Price Oscillator", ti_dpo_start, ti_dpo, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"dpo", 0}, 0, 0, 0}, {"dx", "Directional Movement Index", ti_dx_start, ti_dx, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"dx", 0}, 0, 0, 0}, {"edecay", "Exponential Decay", ti_edecay_start, ti_edecay, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"edecay", 0}, 0, 0, 0}, {"ema", "Exponential Moving Average", ti_ema_start, ti_ema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"ema", 0}, 0, 0, 0}, {"emv", "Ease of Movement", ti_emv_start, ti_emv, 0, 2, 3, 0, 1, {"high", "low", "volume", 0}, {"", 0}, {"emv", 0}, 0, 0, 0}, {"exp", "Vector Exponential", ti_exp_start, ti_exp, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"exp", 0}, 0, 0, 0}, {"fisher", "Fisher Transform", ti_fisher_start, ti_fisher, 0, 2, 2, 1, 2, {"high", "low", 0}, {"period", 0}, {"fisher", "fisher_signal", 0}, 0, 0, 0}, {"floor", "Vector Floor", ti_floor_start, ti_floor, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"floor", 0}, 0, 0, 0}, {"fosc", "Forecast Oscillator", ti_fosc_start, ti_fosc, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"fosc", 0}, 0, 0, 0}, {"hma", "Hull Moving Average", ti_hma_start, ti_hma, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"hma", 0}, 0, 0, 0}, {"kama", "Kaufman Adaptive Moving Average", ti_kama_start, ti_kama, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"kama", 0}, 0, 0, 0}, {"kvo", "Klinger Volume Oscillator", ti_kvo_start, ti_kvo, 0, 2, 4, 2, 1, {"high", "low", "close", "volume", 0}, {"short_period", "long_period", 0}, {"kvo", 0}, 0, 0, 0}, {"lag", "Lag", ti_lag_start, ti_lag, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"lag", 0}, 0, 0, 0}, {"linreg", "Linear Regression", ti_linreg_start, ti_linreg, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"linreg", 0}, 0, 0, 0}, {"linregintercept", "Linear Regression Intercept", ti_linregintercept_start, ti_linregintercept, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"linregintercept", 0}, 0, 0, 0}, {"linregslope", "Linear Regression Slope", ti_linregslope_start, ti_linregslope, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"linregslope", 0}, 0, 0, 0}, {"ln", "Vector Natural Log", ti_ln_start, ti_ln, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"ln", 0}, 0, 0, 0}, {"log10", "Vector Base-10 Log", ti_log10_start, ti_log10, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"log10", 0}, 0, 0, 0}, {"macd", "Moving Average Convergence/Divergence", ti_macd_start, ti_macd, 0, 2, 1, 3, 3, {"real", 0}, {"short_period", "long_period", "signal_period", 0}, {"macd", "macd_signal", "macd_histogram", 0}, 0, 0, 0}, {"marketfi", "Market Facilitation Index", ti_marketfi_start, ti_marketfi, 0, 2, 3, 0, 1, {"high", "low", "volume", 0}, {"", 0}, {"marketfi", 0}, 0, 0, 0}, {"mass", "Mass Index", ti_mass_start, ti_mass, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"mass", 0}, 0, 0, 0}, {"max", "Maximum In Period", ti_max_start, ti_max, ti_max_ref, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"max", 0}, 0, 0, 0}, {"md", "Mean Deviation Over Period", ti_md_start, ti_md, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"md", 0}, 0, 0, 0}, {"medprice", "Median Price", ti_medprice_start, ti_medprice, 0, 1, 2, 0, 1, {"high", "low", 0}, {"", 0}, {"medprice", 0}, 0, 0, 0}, {"mfi", "Money Flow Index", ti_mfi_start, ti_mfi, 0, 2, 4, 1, 1, {"high", "low", "close", "volume", 0}, {"period", 0}, {"mfi", 0}, 0, 0, 0}, {"min", "Minimum In Period", ti_min_start, ti_min, ti_min_ref, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"min", 0}, 0, 0, 0}, {"mom", "Momentum", ti_mom_start, ti_mom, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"mom", 0}, 0, 0, 0}, {"msw", "Mesa Sine Wave", ti_msw_start, ti_msw, 0, 2, 1, 1, 2, {"real", 0}, {"period", 0}, {"msw_sine", "msw_lead", 0}, 0, 0, 0}, {"mul", "Vector Multiplication", ti_mul_start, ti_mul, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"mul", 0}, 0, 0, 0}, {"natr", "Normalized Average True Range", ti_natr_start, ti_natr, 0, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"natr", 0}, 0, 0, 0}, {"nvi", "Negative Volume Index", ti_nvi_start, ti_nvi, 0, 2, 2, 0, 1, {"close", "volume", 0}, {"", 0}, {"nvi", 0}, 0, 0, 0}, {"obv", "On Balance Volume", ti_obv_start, ti_obv, 0, 2, 2, 0, 1, {"close", "volume", 0}, {"", 0}, {"obv", 0}, 0, 0, 0}, {"ppo", "Percentage Price Oscillator", ti_ppo_start, ti_ppo, 0, 2, 1, 2, 1, {"real", 0}, {"short_period", "long_period", 0}, {"ppo", 0}, 0, 0, 0}, {"psar", "Parabolic SAR", ti_psar_start, ti_psar, 0, 1, 2, 2, 1, {"high", "low", 0}, {"acceleration_factor_step", "acceleration_factor_maximum", 0}, {"psar", 0}, 0, 0, 0}, {"pvi", "Positive Volume Index", ti_pvi_start, ti_pvi, 0, 2, 2, 0, 1, {"close", "volume", 0}, {"", 0}, {"pvi", 0}, 0, 0, 0}, {"qstick", "Qstick", ti_qstick_start, ti_qstick, 0, 2, 2, 1, 1, {"open", "close", 0}, {"period", 0}, {"qstick", 0}, 0, 0, 0}, {"roc", "Rate of Change", ti_roc_start, ti_roc, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"roc", 0}, 0, 0, 0}, {"rocr", "Rate of Change Ratio", ti_rocr_start, ti_rocr, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"rocr", 0}, 0, 0, 0}, {"round", "Vector Round", ti_round_start, ti_round, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"round", 0}, 0, 0, 0}, {"rsi", "Relative Strength Index", ti_rsi_start, ti_rsi, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"rsi", 0}, 0, 0, 0}, {"sin", "Vector Sine", ti_sin_start, ti_sin, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"sin", 0}, 0, 0, 0}, {"sinh", "Vector Hyperbolic Sine", ti_sinh_start, ti_sinh, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"sinh", 0}, 0, 0, 0}, {"sma", "Simple Moving Average", ti_sma_start, ti_sma, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"sma", 0}, ti_sma_stream_new, ti_sma_stream_run, ti_sma_stream_free}, {"sqrt", "Vector Square Root", ti_sqrt_start, ti_sqrt, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"sqrt", 0}, 0, 0, 0}, {"stddev", "Standard Deviation Over Period", ti_stddev_start, ti_stddev, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"stddev", 0}, 0, 0, 0}, {"stderr", "Standard Error Over Period", ti_stderr_start, ti_stderr, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"stderr", 0}, 0, 0, 0}, {"stoch", "Stochastic Oscillator", ti_stoch_start, ti_stoch, 0, 2, 3, 3, 2, {"high", "low", "close", 0}, {"k_period", "k_slowing_period", "d_period", 0}, {"stoch_k", "stoch_d", 0}, 0, 0, 0}, {"stochrsi", "Stochastic RSI", ti_stochrsi_start, ti_stochrsi, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"stochrsi", 0}, 0, 0, 0}, {"sub", "Vector Subtraction", ti_sub_start, ti_sub, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"sub", 0}, 0, 0, 0}, {"sum", "Sum Over Period", ti_sum_start, ti_sum, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"sum", 0}, 0, 0, 0}, {"tan", "Vector Tangent", ti_tan_start, ti_tan, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"tan", 0}, 0, 0, 0}, {"tanh", "Vector Hyperbolic Tangent", ti_tanh_start, ti_tanh, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"tanh", 0}, 0, 0, 0}, {"tema", "Triple Exponential Moving Average", ti_tema_start, ti_tema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"tema", 0}, 0, 0, 0}, {"todeg", "Vector Degree Conversion", ti_todeg_start, ti_todeg, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"degrees", 0}, 0, 0, 0}, {"torad", "Vector Radian Conversion", ti_torad_start, ti_torad, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"radians", 0}, 0, 0, 0}, {"tr", "True Range", ti_tr_start, ti_tr, 0, 2, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"tr", 0}, 0, 0, 0}, {"trima", "Triangular Moving Average", ti_trima_start, ti_trima, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"trima", 0}, 0, 0, 0}, {"trix", "Trix", ti_trix_start, ti_trix, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"trix", 0}, 0, 0, 0}, {"trunc", "Vector Truncate", ti_trunc_start, ti_trunc, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"trunc", 0}, 0, 0, 0}, {"tsf", "Time Series Forecast", ti_tsf_start, ti_tsf, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"tsf", 0}, 0, 0, 0}, {"typprice", "Typical Price", ti_typprice_start, ti_typprice, 0, 1, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"typprice", 0}, 0, 0, 0}, {"ultosc", "Ultimate Oscillator", ti_ultosc_start, ti_ultosc, 0, 2, 3, 3, 1, {"high", "low", "close", 0}, {"short_period", "medium_period", "long_period", 0}, {"ultosc", 0}, 0, 0, 0}, {"var", "Variance Over Period", ti_var_start, ti_var, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"var", 0}, 0, 0, 0}, {"vhf", "Vertical Horizontal Filter", ti_vhf_start, ti_vhf, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"vhf", 0}, 0, 0, 0}, {"vidya", "Variable Index Dynamic Average", ti_vidya_start, ti_vidya, 0, 1, 1, 3, 1, {"real", 0}, {"short_period", "long_period", "alpha", 0}, {"vidya", 0}, 0, 0, 0}, {"volatility", "Annualized Historical Volatility", ti_volatility_start, ti_volatility, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"volatility", 0}, 0, 0, 0}, {"vosc", "Volume Oscillator", ti_vosc_start, ti_vosc, 0, 2, 1, 2, 1, {"volume", 0}, {"short_period", "long_period", 0}, {"vosc", 0}, 0, 0, 0}, {"vwma", "Volume Weighted Moving Average", ti_vwma_start, ti_vwma, 0, 1, 2, 1, 1, {"close", "volume", 0}, {"period", 0}, {"vwma", 0}, 0, 0, 0}, {"wad", "Williams Accumulation/Distribution", ti_wad_start, ti_wad, 0, 2, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"wad", 0}, 0, 0, 0}, {"wcprice", "Weighted Close Price", ti_wcprice_start, ti_wcprice, 0, 1, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"wcprice", 0}, 0, 0, 0}, {"wilders", "Wilders Smoothing", ti_wilders_start, ti_wilders, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"wilders", 0}, 0, 0, 0}, {"willr", "Williams %R", ti_willr_start, ti_willr, 0, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"willr", 0}, 0, 0, 0}, {"wma", "Weighted Moving Average", ti_wma_start, ti_wma, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"wma", 0}, 0, 0, 0}, {"zlema", "Zero-Lag Exponential Moving Average", ti_zlema_start, ti_zlema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"zlema", 0}, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0}, {0, 0}, {0, 0}, 0, 0, 0}};
struct ti_stream
{
  int index;
  int progress;
};
int ti_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs)
{
  return ti_indicators[stream->index].stream_run(stream, size, inputs, outputs);
}

ti_indicator_info *ti_stream_get_info(ti_stream *stream)
{
  return ti_indicators + stream->index;
}

int ti_stream_get_progress(ti_stream *stream)
{
  return stream->progress;
}

void ti_stream_free(ti_stream *stream)
{
  ti_indicators[stream->index].stream_free(stream);
}

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
const char *ti_version(void)
{
  return "0.9.2";
}

long int ti_build(void)
{
  return 1746800254;
}

int ti_indicator_count(void)
{
  return 104;
}

struct ti_indicator_info ti_indicators[] = {{"abs", "Vector Absolute Value", ti_abs_start, ti_abs, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"abs", 0}, 0, 0, 0}, {"acos", "Vector Arccosine", ti_acos_start, ti_acos, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"acos", 0}, 0, 0, 0}, {"ad", "Accumulation/Distribution Line", ti_ad_start, ti_ad, 0, 2, 4, 0, 1, {"high", "low", "close", "volume", 0}, {"", 0}, {"ad", 0}, 0, 0, 0}, {"add", "Vector Addition", ti_add_start, ti_add, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"add", 0}, 0, 0, 0}, {"adosc", "Accumulation/Distribution Oscillator", ti_adosc_start, ti_adosc, 0, 2, 4, 2, 1, {"high", "low", "close", "volume", 0}, {"short_period", "long_period", 0}, {"adosc", 0}, 0, 0, 0}, {"adx", "Average Directional Movement Index", ti_adx_start, ti_adx, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"adx", 0}, 0, 0, 0}, {"adxr", "Average Directional Movement Rating", ti_adxr_start, ti_adxr, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"adxr", 0}, 0, 0, 0}, {"ao", "Awesome Oscillator", ti_ao_start, ti_ao, 0, 2, 2, 0, 1, {"high", "low", 0}, {"", 0}, {"ao", 0}, 0, 0, 0}, {"apo", "Absolute Price Oscillator", ti_apo_start, ti_apo, 0, 2, 1, 2, 1, {"real", 0}, {"short_period", "long_period", 0}, {"apo", 0}, 0, 0, 0}, {"aroon", "Aroon", ti_aroon_start, ti_aroon, 0, 2, 2, 1, 2, {"high", "low", 0}, {"period", 0}, {"aroon_down", "aroon_up", 0}, 0, 0, 0}, {"aroonosc", "Aroon Oscillator", ti_aroonosc_start, ti_aroonosc, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"aroonosc", 0}, 0, 0, 0}, {"asin", "Vector Arcsine", ti_asin_start, ti_asin, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"asin", 0}, 0, 0, 0}, {"atan", "Vector Arctangent", ti_atan_start, ti_atan, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"atan", 0}, 0, 0, 0}, {"atr", "Average True Range", ti_atr_start, ti_atr, ti_atr_ref, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"atr", 0}, ti_atr_stream_new, ti_atr_stream_run, ti_atr_stream_free}, {"avgprice", "Average Price", ti_avgprice_start, ti_avgprice, 0, 1, 4, 0, 1, {"open", "high", "low", "close", 0}, {"", 0}, {"avgprice", 0}, 0, 0, 0}, {"bbands", "Bollinger Bands", ti_bbands_start, ti_bbands, 0, 1, 1, 2, 3, {"real", 0}, {"period", "stddev", 0}, {"bbands_lower", "bbands_middle", "bbands_upper", 0}, 0, 0, 0}, {"bop", "Balance of Power", ti_bop_start, ti_bop, 0, 2, 4, 0, 1, {"open", "high", "low", "close", 0}, {"", 0}, {"bop", 0}, 0, 0, 0}, {"cci", "Commodity Channel Index", ti_cci_start, ti_cci, 0, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"cci", 0}, 0, 0, 0}, {"ceil", "Vector Ceiling", ti_ceil_start, ti_ceil, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"ceil", 0}, 0, 0, 0}, {"cmo", "Chande Momentum Oscillator", ti_cmo_start, ti_cmo, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"cmo", 0}, 0, 0, 0}, {"cos", "Vector Cosine", ti_cos_start, ti_cos, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"cos", 0}, 0, 0, 0}, {"cosh", "Vector Hyperbolic Cosine", ti_cosh_start, ti_cosh, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"cosh", 0}, 0, 0, 0}, {"crossany", "Crossany", ti_crossany_start, ti_crossany, 0, 3, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"crossany", 0}, 0, 0, 0}, {"crossover", "Crossover", ti_crossover_start, ti_crossover, 0, 3, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"crossover", 0}, 0, 0, 0}, {"cvi", "Chaikins Volatility", ti_cvi_start, ti_cvi, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"cvi", 0}, 0, 0, 0}, {"decay", "Linear Decay", ti_decay_start, ti_decay, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"decay", 0}, 0, 0, 0}, {"dema", "Double Exponential Moving Average", ti_dema_start, ti_dema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"dema", 0}, 0, 0, 0}, {"di", "Directional Indicator", ti_di_start, ti_di, 0, 2, 3, 1, 2, {"high", "low", "close", 0}, {"period", 0}, {"plus_di", "minus_di", 0}, 0, 0, 0}, {"div", "Vector Division", ti_div_start, ti_div, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"div", 0}, 0, 0, 0}, {"dm", "Directional Movement", ti_dm_start, ti_dm, 0, 2, 2, 1, 2, {"high", "low", 0}, {"period", 0}, {"plus_dm", "minus_dm", 0}, 0, 0, 0}, {"dpo", "Detrended Price Oscillator", ti_dpo_start, ti_dpo, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"dpo", 0}, 0, 0, 0}, {"dx", "Directional Movement Index", ti_dx_start, ti_dx, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"dx", 0}, 0, 0, 0}, {"edecay", "Exponential Decay", ti_edecay_start, ti_edecay, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"edecay", 0}, 0, 0, 0}, {"ema", "Exponential Moving Average", ti_ema_start, ti_ema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"ema", 0}, 0, 0, 0}, {"emv", "Ease of Movement", ti_emv_start, ti_emv, 0, 2, 3, 0, 1, {"high", "low", "volume", 0}, {"", 0}, {"emv", 0}, 0, 0, 0}, {"exp", "Vector Exponential", ti_exp_start, ti_exp, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"exp", 0}, 0, 0, 0}, {"fisher", "Fisher Transform", ti_fisher_start, ti_fisher, 0, 2, 2, 1, 2, {"high", "low", 0}, {"period", 0}, {"fisher", "fisher_signal", 0}, 0, 0, 0}, {"floor", "Vector Floor", ti_floor_start, ti_floor, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"floor", 0}, 0, 0, 0}, {"fosc", "Forecast Oscillator", ti_fosc_start, ti_fosc, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"fosc", 0}, 0, 0, 0}, {"hma", "Hull Moving Average", ti_hma_start, ti_hma, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"hma", 0}, 0, 0, 0}, {"kama", "Kaufman Adaptive Moving Average", ti_kama_start, ti_kama, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"kama", 0}, 0, 0, 0}, {"kvo", "Klinger Volume Oscillator", ti_kvo_start, ti_kvo, 0, 2, 4, 2, 1, {"high", "low", "close", "volume", 0}, {"short_period", "long_period", 0}, {"kvo", 0}, 0, 0, 0}, {"lag", "Lag", ti_lag_start, ti_lag, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"lag", 0}, 0, 0, 0}, {"linreg", "Linear Regression", ti_linreg_start, ti_linreg, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"linreg", 0}, 0, 0, 0}, {"linregintercept", "Linear Regression Intercept", ti_linregintercept_start, ti_linregintercept, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"linregintercept", 0}, 0, 0, 0}, {"linregslope", "Linear Regression Slope", ti_linregslope_start, ti_linregslope, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"linregslope", 0}, 0, 0, 0}, {"ln", "Vector Natural Log", ti_ln_start, ti_ln, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"ln", 0}, 0, 0, 0}, {"log10", "Vector Base-10 Log", ti_log10_start, ti_log10, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"log10", 0}, 0, 0, 0}, {"macd", "Moving Average Convergence/Divergence", ti_macd_start, ti_macd, 0, 2, 1, 3, 3, {"real", 0}, {"short_period", "long_period", "signal_period", 0}, {"macd", "macd_signal", "macd_histogram", 0}, 0, 0, 0}, {"marketfi", "Market Facilitation Index", ti_marketfi_start, ti_marketfi, 0, 2, 3, 0, 1, {"high", "low", "volume", 0}, {"", 0}, {"marketfi", 0}, 0, 0, 0}, {"mass", "Mass Index", ti_mass_start, ti_mass, 0, 2, 2, 1, 1, {"high", "low", 0}, {"period", 0}, {"mass", 0}, 0, 0, 0}, {"max", "Maximum In Period", ti_max_start, ti_max, ti_max_ref, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"max", 0}, 0, 0, 0}, {"md", "Mean Deviation Over Period", ti_md_start, ti_md, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"md", 0}, 0, 0, 0}, {"medprice", "Median Price", ti_medprice_start, ti_medprice, 0, 1, 2, 0, 1, {"high", "low", 0}, {"", 0}, {"medprice", 0}, 0, 0, 0}, {"mfi", "Money Flow Index", ti_mfi_start, ti_mfi, 0, 2, 4, 1, 1, {"high", "low", "close", "volume", 0}, {"period", 0}, {"mfi", 0}, 0, 0, 0}, {"min", "Minimum In Period", ti_min_start, ti_min, ti_min_ref, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"min", 0}, 0, 0, 0}, {"mom", "Momentum", ti_mom_start, ti_mom, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"mom", 0}, 0, 0, 0}, {"msw", "Mesa Sine Wave", ti_msw_start, ti_msw, 0, 2, 1, 1, 2, {"real", 0}, {"period", 0}, {"msw_sine", "msw_lead", 0}, 0, 0, 0}, {"mul", "Vector Multiplication", ti_mul_start, ti_mul, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"mul", 0}, 0, 0, 0}, {"natr", "Normalized Average True Range", ti_natr_start, ti_natr, 0, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"natr", 0}, 0, 0, 0}, {"nvi", "Negative Volume Index", ti_nvi_start, ti_nvi, 0, 2, 2, 0, 1, {"close", "volume", 0}, {"", 0}, {"nvi", 0}, 0, 0, 0}, {"obv", "On Balance Volume", ti_obv_start, ti_obv, 0, 2, 2, 0, 1, {"close", "volume", 0}, {"", 0}, {"obv", 0}, 0, 0, 0}, {"ppo", "Percentage Price Oscillator", ti_ppo_start, ti_ppo, 0, 2, 1, 2, 1, {"real", 0}, {"short_period", "long_period", 0}, {"ppo", 0}, 0, 0, 0}, {"psar", "Parabolic SAR", ti_psar_start, ti_psar, 0, 1, 2, 2, 1, {"high", "low", 0}, {"acceleration_factor_step", "acceleration_factor_maximum", 0}, {"psar", 0}, 0, 0, 0}, {"pvi", "Positive Volume Index", ti_pvi_start, ti_pvi, 0, 2, 2, 0, 1, {"close", "volume", 0}, {"", 0}, {"pvi", 0}, 0, 0, 0}, {"qstick", "Qstick", ti_qstick_start, ti_qstick, 0, 2, 2, 1, 1, {"open", "close", 0}, {"period", 0}, {"qstick", 0}, 0, 0, 0}, {"roc", "Rate of Change", ti_roc_start, ti_roc, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"roc", 0}, 0, 0, 0}, {"rocr", "Rate of Change Ratio", ti_rocr_start, ti_rocr, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"rocr", 0}, 0, 0, 0}, {"round", "Vector Round", ti_round_start, ti_round, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"round", 0}, 0, 0, 0}, {"rsi", "Relative Strength Index", ti_rsi_start, ti_rsi, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"rsi", 0}, 0, 0, 0}, {"sin", "Vector Sine", ti_sin_start, ti_sin, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"sin", 0}, 0, 0, 0}, {"sinh", "Vector Hyperbolic Sine", ti_sinh_start, ti_sinh, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"sinh", 0}, 0, 0, 0}, {"sma", "Simple Moving Average", ti_sma_start, ti_sma, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"sma", 0}, ti_sma_stream_new, ti_sma_stream_run, ti_sma_stream_free}, {"sqrt", "Vector Square Root", ti_sqrt_start, ti_sqrt, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"sqrt", 0}, 0, 0, 0}, {"stddev", "Standard Deviation Over Period", ti_stddev_start, ti_stddev, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"stddev", 0}, 0, 0, 0}, {"stderr", "Standard Error Over Period", ti_stderr_start, ti_stderr, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"stderr", 0}, 0, 0, 0}, {"stoch", "Stochastic Oscillator", ti_stoch_start, ti_stoch, 0, 2, 3, 3, 2, {"high", "low", "close", 0}, {"k_period", "k_slowing_period", "d_period", 0}, {"stoch_k", "stoch_d", 0}, 0, 0, 0}, {"stochrsi", "Stochastic RSI", ti_stochrsi_start, ti_stochrsi, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"stochrsi", 0}, 0, 0, 0}, {"sub", "Vector Subtraction", ti_sub_start, ti_sub, 0, 4, 2, 0, 1, {"real", "real", 0}, {"", 0}, {"sub", 0}, 0, 0, 0}, {"sum", "Sum Over Period", ti_sum_start, ti_sum, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"sum", 0}, 0, 0, 0}, {"tan", "Vector Tangent", ti_tan_start, ti_tan, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"tan", 0}, 0, 0, 0}, {"tanh", "Vector Hyperbolic Tangent", ti_tanh_start, ti_tanh, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"tanh", 0}, 0, 0, 0}, {"tema", "Triple Exponential Moving Average", ti_tema_start, ti_tema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"tema", 0}, 0, 0, 0}, {"todeg", "Vector Degree Conversion", ti_todeg_start, ti_todeg, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"degrees", 0}, 0, 0, 0}, {"torad", "Vector Radian Conversion", ti_torad_start, ti_torad, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"radians", 0}, 0, 0, 0}, {"tr", "True Range", ti_tr_start, ti_tr, 0, 2, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"tr", 0}, 0, 0, 0}, {"trima", "Triangular Moving Average", ti_trima_start, ti_trima, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"trima", 0}, 0, 0, 0}, {"trix", "Trix", ti_trix_start, ti_trix, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"trix", 0}, 0, 0, 0}, {"trunc", "Vector Truncate", ti_trunc_start, ti_trunc, 0, 4, 1, 0, 1, {"real", 0}, {"", 0}, {"trunc", 0}, 0, 0, 0}, {"tsf", "Time Series Forecast", ti_tsf_start, ti_tsf, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"tsf", 0}, 0, 0, 0}, {"typprice", "Typical Price", ti_typprice_start, ti_typprice, 0, 1, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"typprice", 0}, 0, 0, 0}, {"ultosc", "Ultimate Oscillator", ti_ultosc_start, ti_ultosc, 0, 2, 3, 3, 1, {"high", "low", "close", 0}, {"short_period", "medium_period", "long_period", 0}, {"ultosc", 0}, 0, 0, 0}, {"var", "Variance Over Period", ti_var_start, ti_var, 0, 3, 1, 1, 1, {"real", 0}, {"period", 0}, {"var", 0}, 0, 0, 0}, {"vhf", "Vertical Horizontal Filter", ti_vhf_start, ti_vhf, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"vhf", 0}, 0, 0, 0}, {"vidya", "Variable Index Dynamic Average", ti_vidya_start, ti_vidya, 0, 1, 1, 3, 1, {"real", 0}, {"short_period", "long_period", "alpha", 0}, {"vidya", 0}, 0, 0, 0}, {"volatility", "Annualized Historical Volatility", ti_volatility_start, ti_volatility, 0, 2, 1, 1, 1, {"real", 0}, {"period", 0}, {"volatility", 0}, 0, 0, 0}, {"vosc", "Volume Oscillator", ti_vosc_start, ti_vosc, 0, 2, 1, 2, 1, {"volume", 0}, {"short_period", "long_period", 0}, {"vosc", 0}, 0, 0, 0}, {"vwma", "Volume Weighted Moving Average", ti_vwma_start, ti_vwma, 0, 1, 2, 1, 1, {"close", "volume", 0}, {"period", 0}, {"vwma", 0}, 0, 0, 0}, {"wad", "Williams Accumulation/Distribution", ti_wad_start, ti_wad, 0, 2, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"wad", 0}, 0, 0, 0}, {"wcprice", "Weighted Close Price", ti_wcprice_start, ti_wcprice, 0, 1, 3, 0, 1, {"high", "low", "close", 0}, {"", 0}, {"wcprice", 0}, 0, 0, 0}, {"wilders", "Wilders Smoothing", ti_wilders_start, ti_wilders, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"wilders", 0}, 0, 0, 0}, {"willr", "Williams %R", ti_willr_start, ti_willr, 0, 2, 3, 1, 1, {"high", "low", "close", 0}, {"period", 0}, {"willr", 0}, 0, 0, 0}, {"wma", "Weighted Moving Average", ti_wma_start, ti_wma, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"wma", 0}, 0, 0, 0}, {"zlema", "Zero-Lag Exponential Moving Average", ti_zlema_start, ti_zlema, 0, 1, 1, 1, 1, {"real", 0}, {"period", 0}, {"zlema", 0}, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0}, {0, 0}, {0, 0}, 0, 0, 0}};
struct ti_stream
{
  int index;
  int progress;
};
int ti_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs)
{
  return ti_indicators[stream->index].stream_run(stream, size, inputs, outputs);
}

ti_indicator_info *ti_stream_get_info(ti_stream *stream)
{
  return ti_indicators + stream->index;
}

int ti_stream_get_progress(ti_stream *stream)
{
  return stream->progress;
}

void ti_stream_free(ti_stream *stream)
{
  ti_indicators[stream->index].stream_free(stream);
}

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

