# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 1
# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 65 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
const char* ti_version(void);
long int ti_build(void);
int ti_indicator_count(void);
# 90 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
typedef int (*ti_indicator_start_function)(double const *options);
typedef int (*ti_indicator_function)(int size, double const *const *inputs, double const *options, double *const *outputs);


struct ti_stream; typedef struct ti_stream ti_stream;
typedef int (*ti_indicator_stream_new)(double const *options, ti_stream **stream);
typedef int (*ti_indicator_stream_run)(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
typedef void (*ti_indicator_stream_free)(ti_stream *stream);


typedef struct ti_indicator_info {
    const char *name;
    const char *full_name;
    ti_indicator_start_function start;
    ti_indicator_function indicator;
    ti_indicator_function indicator_ref;
    int type, inputs, options, outputs;
    const char *input_names[16];
    const char *option_names[16];
    const char *output_names[16];
    ti_indicator_stream_new stream_new;
    ti_indicator_stream_run stream_run;
    ti_indicator_stream_free stream_free;
} ti_indicator_info;



extern ti_indicator_info ti_indicators[];



const ti_indicator_info *ti_find_indicator(const char *name);




int ti_stream_run(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
ti_indicator_info *ti_stream_get_info(ti_stream *stream);
int ti_stream_get_progress(ti_stream *stream);
void ti_stream_free(ti_stream *stream);
# 158 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
int ti_abs_start(double const *options);
int ti_abs(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_acos_start(double const *options);
int ti_acos(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ad_start(double const *options);
int ti_ad(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_add_start(double const *options);
int ti_add(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_adosc_start(double const *options);
int ti_adosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_adx_start(double const *options);
int ti_adx(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_adxr_start(double const *options);
int ti_adxr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ao_start(double const *options);
int ti_ao(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_apo_start(double const *options);
int ti_apo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_aroon_start(double const *options);
int ti_aroon(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_aroonosc_start(double const *options);
int ti_aroonosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_asin_start(double const *options);
int ti_asin(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_atan_start(double const *options);
int ti_atan(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_atr_start(double const *options);
int ti_atr(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_atr_ref(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_atr_stream_new(double const *options, ti_stream **stream);
int ti_atr_stream_run(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
void ti_atr_stream_free(ti_stream *stream);







int ti_avgprice_start(double const *options);
int ti_avgprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_bbands_start(double const *options);
int ti_bbands(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_bop_start(double const *options);
int ti_bop(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cci_start(double const *options);
int ti_cci(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ceil_start(double const *options);
int ti_ceil(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cmo_start(double const *options);
int ti_cmo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cos_start(double const *options);
int ti_cos(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cosh_start(double const *options);
int ti_cosh(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_crossany_start(double const *options);
int ti_crossany(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_crossover_start(double const *options);
int ti_crossover(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cvi_start(double const *options);
int ti_cvi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_decay_start(double const *options);
int ti_decay(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dema_start(double const *options);
int ti_dema(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_di_start(double const *options);
int ti_di(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_div_start(double const *options);
int ti_div(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dm_start(double const *options);
int ti_dm(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dpo_start(double const *options);
int ti_dpo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dx_start(double const *options);
int ti_dx(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_edecay_start(double const *options);
int ti_edecay(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ema_start(double const *options);
int ti_ema(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_emv_start(double const *options);
int ti_emv(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_exp_start(double const *options);
int ti_exp(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_fisher_start(double const *options);
int ti_fisher(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_floor_start(double const *options);
int ti_floor(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_fosc_start(double const *options);
int ti_fosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_hma_start(double const *options);
int ti_hma(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_kama_start(double const *options);
int ti_kama(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_kvo_start(double const *options);
int ti_kvo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_lag_start(double const *options);
int ti_lag(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_linreg_start(double const *options);
int ti_linreg(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_linregintercept_start(double const *options);
int ti_linregintercept(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_linregslope_start(double const *options);
int ti_linregslope(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ln_start(double const *options);
int ti_ln(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_log10_start(double const *options);
int ti_log10(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_macd_start(double const *options);
int ti_macd(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_marketfi_start(double const *options);
int ti_marketfi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mass_start(double const *options);
int ti_mass(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_max_start(double const *options);
int ti_max(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_max_ref(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_md_start(double const *options);
int ti_md(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_medprice_start(double const *options);
int ti_medprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mfi_start(double const *options);
int ti_mfi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_min_start(double const *options);
int ti_min(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_min_ref(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mom_start(double const *options);
int ti_mom(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_msw_start(double const *options);
int ti_msw(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mul_start(double const *options);
int ti_mul(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_natr_start(double const *options);
int ti_natr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_nvi_start(double const *options);
int ti_nvi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_obv_start(double const *options);
int ti_obv(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ppo_start(double const *options);
int ti_ppo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_psar_start(double const *options);
int ti_psar(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_pvi_start(double const *options);
int ti_pvi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_qstick_start(double const *options);
int ti_qstick(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_roc_start(double const *options);
int ti_roc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_rocr_start(double const *options);
int ti_rocr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_round_start(double const *options);
int ti_round(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_rsi_start(double const *options);
int ti_rsi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sin_start(double const *options);
int ti_sin(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sinh_start(double const *options);
int ti_sinh(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sma_start(double const *options);
int ti_sma(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_sma_stream_new(double const *options, ti_stream **stream);
int ti_sma_stream_run(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
void ti_sma_stream_free(ti_stream *stream);







int ti_sqrt_start(double const *options);
int ti_sqrt(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stddev_start(double const *options);
int ti_stddev(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stderr_start(double const *options);
int ti_stderr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stoch_start(double const *options);
int ti_stoch(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stochrsi_start(double const *options);
int ti_stochrsi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sub_start(double const *options);
int ti_sub(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sum_start(double const *options);
int ti_sum(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tan_start(double const *options);
int ti_tan(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tanh_start(double const *options);
int ti_tanh(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tema_start(double const *options);
int ti_tema(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_todeg_start(double const *options);
int ti_todeg(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_torad_start(double const *options);
int ti_torad(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tr_start(double const *options);
int ti_tr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_trima_start(double const *options);
int ti_trima(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_trix_start(double const *options);
int ti_trix(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_trunc_start(double const *options);
int ti_trunc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tsf_start(double const *options);
int ti_tsf(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_typprice_start(double const *options);
int ti_typprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ultosc_start(double const *options);
int ti_ultosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_var_start(double const *options);
int ti_var(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vhf_start(double const *options);
int ti_vhf(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vidya_start(double const *options);
int ti_vidya(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_volatility_start(double const *options);
int ti_volatility(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vosc_start(double const *options);
int ti_vosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vwma_start(double const *options);
int ti_vwma(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wad_start(double const *options);
int ti_wad(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wcprice_start(double const *options);
int ti_wcprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wilders_start(double const *options);
int ti_wilders(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_willr_start(double const *options);
int ti_willr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wma_start(double const *options);
int ti_wma(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_zlema_start(double const *options);
int ti_zlema(int size, double const *const *inputs, double const *options, double *const *outputs);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h" 1
# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h" 2
# 62 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
const char* tc_version(void);
long int tc_build(void);
int tc_candle_count(void);





typedef double TC_REAL;
typedef struct tc_result tc_result;

typedef uint64_t tc_set;
# 119 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
typedef struct tc_config {
    int period;

    TC_REAL body_none;
    TC_REAL body_short;
    TC_REAL body_long;

    TC_REAL wick_none;
    TC_REAL wick_long;

    TC_REAL near;

} tc_config;



typedef struct tc_hit {
    int index;
    tc_set patterns;
} tc_hit;



typedef int (*tc_candle_function)(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);



typedef struct tc_candle_info {
    const char *name;
    const char *full_name;
    tc_set pattern;
    tc_candle_function candle;
} tc_candle_info;



extern tc_candle_info tc_candles[];


const tc_candle_info *tc_find_candle(const char *name);


const tc_candle_info *tc_get_info(tc_set pattern);


tc_config const *tc_config_default();
void tc_config_set_to_default(tc_config *config);


tc_result *tc_result_new();
void tc_result_free(tc_result *result);
int tc_result_count(const tc_result *result);
int tc_result_pattern_count(const tc_result *result);

tc_hit tc_result_get(const tc_result *result, int index);
tc_set tc_result_at(const tc_result *result, int index);




int tc_run(tc_set patterns, int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
# 199 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
int tc_abandoned_baby_bear(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_abandoned_baby_bull(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_big_black_candle(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_big_white_candle(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_black_marubozu(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_dragonfly_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_engulfing_bear(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_engulfing_bull(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_evening_doji_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_evening_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_four_price_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_gravestone_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_hammer(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_hanging_man(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_inverted_hammer(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_long_legged_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_marubozu(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_morning_doji_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_morning_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_shooting_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_spinning_top(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_three_black_crows(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_three_white_soldiers(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_white_marubozu(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2


double optionsd_small[] = {-20,-2,-1,0,.7,1,2,3,4,5,6,7,8,10,20,100,999};
double optionsd_large[] = {-5,0,1,2,5};

double dummy_in[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
double dummy_in0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double dummy_ot[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

const int input_size = sizeof(dummy_in) / sizeof(double);
const int sizes[] = {0,1,2,3,4,8,20};
const int sizes_count = sizeof(sizes) / sizeof(int);


void banner() {
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
# 72 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
int errors_cnt = 0;

void check_output(const ti_indicator_info *info, int size, double const *const *inputs, double const * options, double *const *outputs) {

    const int s = info->start(options);

    int o;
    for (o = 0; o < info->outputs; ++o) {

        double max = 0;
        double min = 0;

        int i;
        for (i = 0; i < size - s; ++i) {
            const double op = outputs[o][i];
            const double in = inputs[0][i+s];

            max = in > max ? in : max;
            min = in < min ? in : min;

            switch (info->type) {

                default:
                    break;

                case 1:
                    if ((op > 4 && op > max * 1.5 + 2) || (op < -4 && op < min * 0.5 - 3)) {
                        do { int k, j; printf("\nInputs:"); for (k = 0; k < input_size; ++k) printf(" %f", inputs[0][k]); printf("\nOptions:"); for (k = 0; k < info->options; ++k) printf(" %f", options[k]); for (j = 0; j < info->outputs; ++j) { printf("\nOutput[%d]:", j); for (k = 0; k < input_size; ++k) printf(" %f", outputs[j][k]); } } while (0);
                        printf("\nERROR Output is out of range for input: input: %f output: %f\n", in, op);
                        errors_cnt += 1;
                        assert(0);
                    }
                    break;
            }
        }

    }
}


void stress_indicator(const ti_indicator_info *info) {
    const int opt_count = info->options;
    printf("%s (%s) (%d options)\n", info->name, info->full_name, opt_count);


    const double *inputs[16] = {0};
    const double *inputs0[16] = {0};
    double *outputs[16] = {0};

    int i;
    for (i = 0; i < 16; ++i) {
        inputs[i] = i < info->inputs ? dummy_in : 0;
        inputs0[i] = i < info->inputs ? dummy_in0 : 0;
        outputs[i] = i < info->outputs ? dummy_ot : 0;
    }


    int options_index[16 +1] = {0};
    double options[16];

    int choices;
    double *optionsd;
    if (opt_count <= 4) {
        choices = sizeof(optionsd_small) / sizeof(double);
        optionsd = optionsd_small;
    } else {
        choices = sizeof(optionsd_large) / sizeof(double);
        optionsd = optionsd_large;
    }


    int j, count = 0;
    do {
        ++count;

        for (j = 0; j < opt_count; ++j) {
            options[j] = optionsd[options_index[j]];
            printf(" %f", options[j]);
        }


        const int rz = info->indicator(input_size, inputs0, options, outputs);
        if (rz == 0) check_output(info, input_size, inputs0, options, outputs);


        for (int s = 0; s < sizes_count; ++s) {
            const int size = sizes[s];
            printf(" %d", size);
            const int r = info->indicator(size, inputs, options, outputs);
            if (r == 0) check_output(info, size, inputs, options, outputs);

            if (info->indicator_ref) {
                printf(" r");
                const int rr = info->indicator_ref(size, inputs, options, outputs);
                if (rr == 0) check_output(info, size, inputs, options, outputs);
            }


            if (info->stream_new) {
                ti_stream *stream;
                const int rs = info->stream_new(options, &stream);
                if (rs == 0 && stream) {
                    printf(" s");
                    int rsc = info->stream_run(stream, size, inputs, outputs);
                    if (rsc == 0) check_output(info, size, inputs, options, outputs);


                    for (int repeat = 0; repeat < 5; ++repeat) {
                        rsc = info->stream_run(stream, size, inputs, outputs);


                    }

                    info->stream_free(stream);
                }
            }

        }

        printf("\r                                                                          \r");

        j = 0;
        do {
            options_index[j] = (options_index[j] + 1) % choices;
        } while (options_index[j++] == 0);

    } while (j <= opt_count);

    assert(.1 > fabs(count - (pow(choices, opt_count))));
}


void stress_candle(const tc_candle_info *info) {
    printf("%s (%s)\n", info->name, info->full_name);

    const double *inputs[4] = {dummy_in, dummy_in, dummy_in, dummy_in};
    const double *inputs0[4] = {dummy_in0, dummy_in0, dummy_in0, dummy_in0};

    tc_config config;
    tc_config_set_to_default(&config);

    tc_result *output = tc_result_new();


    for (int s = 0; s < sizes_count; ++s) {
        const int size = sizes[s];

        info->candle(size, inputs, &config, output);
        assert(tc_result_count(output) <= size);
        assert(tc_result_pattern_count(output) <= size);

        for (int i = 0; i < tc_result_count(output); ++i) {
            tc_hit hit = tc_result_get(output, i);
            assert(hit.patterns != ((1L<<26)-1));
            assert(hit.index >= 0);
            assert(hit.index < size);
        }
        for (int i = 0; i < size; ++i) {
            tc_set patterns = tc_result_at(output, i);
            assert(patterns != ((1L<<26)-1));
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

    if (argc > 1) {
        const ti_indicator_info *ind_info = ti_find_indicator(argv[1]);
        if (ind_info) {
            stress_indicator(ind_info);
        }

        const tc_candle_info *cnd_info = tc_find_candle(argv[1]);
        if (cnd_info) {
            stress_candle(cnd_info);
        }
    } else {

        const ti_indicator_info *ind_info = ti_indicators;
        do {
            stress_indicator(ind_info);
        } while ((++ind_info)->name);

        const tc_candle_info *cnd_info = tc_candles;
        do {
            stress_candle(cnd_info);
        } while ((++cnd_info)->name);
    }

    printf("\r                                                  \rDone\n");

    return errors_cnt ? 1 : 0;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 1
# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h" 2
# 65 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
const char* ti_version(void);
long int ti_build(void);
int ti_indicator_count(void);
# 90 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
typedef int (*ti_indicator_start_function)(double const *options);
typedef int (*ti_indicator_function)(int size, double const *const *inputs, double const *options, double *const *outputs);


struct ti_stream; typedef struct ti_stream ti_stream;
typedef int (*ti_indicator_stream_new)(double const *options, ti_stream **stream);
typedef int (*ti_indicator_stream_run)(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
typedef void (*ti_indicator_stream_free)(ti_stream *stream);


typedef struct ti_indicator_info {
    const char *name;
    const char *full_name;
    ti_indicator_start_function start;
    ti_indicator_function indicator;
    ti_indicator_function indicator_ref;
    int type, inputs, options, outputs;
    const char *input_names[16];
    const char *option_names[16];
    const char *output_names[16];
    ti_indicator_stream_new stream_new;
    ti_indicator_stream_run stream_run;
    ti_indicator_stream_free stream_free;
} ti_indicator_info;



extern ti_indicator_info ti_indicators[];



const ti_indicator_info *ti_find_indicator(const char *name);




int ti_stream_run(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
ti_indicator_info *ti_stream_get_info(ti_stream *stream);
int ti_stream_get_progress(ti_stream *stream);
void ti_stream_free(ti_stream *stream);
# 158 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/indicators.h"
int ti_abs_start(double const *options);
int ti_abs(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_acos_start(double const *options);
int ti_acos(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ad_start(double const *options);
int ti_ad(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_add_start(double const *options);
int ti_add(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_adosc_start(double const *options);
int ti_adosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_adx_start(double const *options);
int ti_adx(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_adxr_start(double const *options);
int ti_adxr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ao_start(double const *options);
int ti_ao(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_apo_start(double const *options);
int ti_apo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_aroon_start(double const *options);
int ti_aroon(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_aroonosc_start(double const *options);
int ti_aroonosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_asin_start(double const *options);
int ti_asin(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_atan_start(double const *options);
int ti_atan(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_atr_start(double const *options);
int ti_atr(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_atr_ref(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_atr_stream_new(double const *options, ti_stream **stream);
int ti_atr_stream_run(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
void ti_atr_stream_free(ti_stream *stream);







int ti_avgprice_start(double const *options);
int ti_avgprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_bbands_start(double const *options);
int ti_bbands(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_bop_start(double const *options);
int ti_bop(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cci_start(double const *options);
int ti_cci(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ceil_start(double const *options);
int ti_ceil(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cmo_start(double const *options);
int ti_cmo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cos_start(double const *options);
int ti_cos(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cosh_start(double const *options);
int ti_cosh(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_crossany_start(double const *options);
int ti_crossany(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_crossover_start(double const *options);
int ti_crossover(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_cvi_start(double const *options);
int ti_cvi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_decay_start(double const *options);
int ti_decay(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dema_start(double const *options);
int ti_dema(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_di_start(double const *options);
int ti_di(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_div_start(double const *options);
int ti_div(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dm_start(double const *options);
int ti_dm(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dpo_start(double const *options);
int ti_dpo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_dx_start(double const *options);
int ti_dx(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_edecay_start(double const *options);
int ti_edecay(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ema_start(double const *options);
int ti_ema(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_emv_start(double const *options);
int ti_emv(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_exp_start(double const *options);
int ti_exp(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_fisher_start(double const *options);
int ti_fisher(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_floor_start(double const *options);
int ti_floor(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_fosc_start(double const *options);
int ti_fosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_hma_start(double const *options);
int ti_hma(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_kama_start(double const *options);
int ti_kama(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_kvo_start(double const *options);
int ti_kvo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_lag_start(double const *options);
int ti_lag(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_linreg_start(double const *options);
int ti_linreg(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_linregintercept_start(double const *options);
int ti_linregintercept(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_linregslope_start(double const *options);
int ti_linregslope(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ln_start(double const *options);
int ti_ln(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_log10_start(double const *options);
int ti_log10(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_macd_start(double const *options);
int ti_macd(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_marketfi_start(double const *options);
int ti_marketfi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mass_start(double const *options);
int ti_mass(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_max_start(double const *options);
int ti_max(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_max_ref(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_md_start(double const *options);
int ti_md(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_medprice_start(double const *options);
int ti_medprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mfi_start(double const *options);
int ti_mfi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_min_start(double const *options);
int ti_min(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_min_ref(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mom_start(double const *options);
int ti_mom(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_msw_start(double const *options);
int ti_msw(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_mul_start(double const *options);
int ti_mul(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_natr_start(double const *options);
int ti_natr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_nvi_start(double const *options);
int ti_nvi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_obv_start(double const *options);
int ti_obv(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ppo_start(double const *options);
int ti_ppo(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_psar_start(double const *options);
int ti_psar(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_pvi_start(double const *options);
int ti_pvi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_qstick_start(double const *options);
int ti_qstick(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_roc_start(double const *options);
int ti_roc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_rocr_start(double const *options);
int ti_rocr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_round_start(double const *options);
int ti_round(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_rsi_start(double const *options);
int ti_rsi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sin_start(double const *options);
int ti_sin(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sinh_start(double const *options);
int ti_sinh(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sma_start(double const *options);
int ti_sma(int size, double const *const *inputs, double const *options, double *const *outputs);
int ti_sma_stream_new(double const *options, ti_stream **stream);
int ti_sma_stream_run(ti_stream *stream, int size, double const *const *inputs, double *const *outputs);
void ti_sma_stream_free(ti_stream *stream);







int ti_sqrt_start(double const *options);
int ti_sqrt(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stddev_start(double const *options);
int ti_stddev(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stderr_start(double const *options);
int ti_stderr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stoch_start(double const *options);
int ti_stoch(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_stochrsi_start(double const *options);
int ti_stochrsi(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sub_start(double const *options);
int ti_sub(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_sum_start(double const *options);
int ti_sum(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tan_start(double const *options);
int ti_tan(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tanh_start(double const *options);
int ti_tanh(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tema_start(double const *options);
int ti_tema(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_todeg_start(double const *options);
int ti_todeg(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_torad_start(double const *options);
int ti_torad(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tr_start(double const *options);
int ti_tr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_trima_start(double const *options);
int ti_trima(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_trix_start(double const *options);
int ti_trix(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_trunc_start(double const *options);
int ti_trunc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_tsf_start(double const *options);
int ti_tsf(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_typprice_start(double const *options);
int ti_typprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_ultosc_start(double const *options);
int ti_ultosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_var_start(double const *options);
int ti_var(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vhf_start(double const *options);
int ti_vhf(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vidya_start(double const *options);
int ti_vidya(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_volatility_start(double const *options);
int ti_volatility(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vosc_start(double const *options);
int ti_vosc(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_vwma_start(double const *options);
int ti_vwma(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wad_start(double const *options);
int ti_wad(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wcprice_start(double const *options);
int ti_wcprice(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wilders_start(double const *options);
int ti_wilders(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_willr_start(double const *options);
int ti_willr(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_wma_start(double const *options);
int ti_wma(int size, double const *const *inputs, double const *options, double *const *outputs);







int ti_zlema_start(double const *options);
int ti_zlema(int size, double const *const *inputs, double const *options, double *const *outputs);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h" 1
# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h" 2
# 62 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
const char* tc_version(void);
long int tc_build(void);
int tc_candle_count(void);





typedef double TC_REAL;
typedef struct tc_result tc_result;

typedef uint64_t tc_set;
# 119 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
typedef struct tc_config {
    int period;

    TC_REAL body_none;
    TC_REAL body_short;
    TC_REAL body_long;

    TC_REAL wick_none;
    TC_REAL wick_long;

    TC_REAL near;

} tc_config;



typedef struct tc_hit {
    int index;
    tc_set patterns;
} tc_hit;



typedef int (*tc_candle_function)(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);



typedef struct tc_candle_info {
    const char *name;
    const char *full_name;
    tc_set pattern;
    tc_candle_function candle;
} tc_candle_info;



extern tc_candle_info tc_candles[];


const tc_candle_info *tc_find_candle(const char *name);


const tc_candle_info *tc_get_info(tc_set pattern);


tc_config const *tc_config_default();
void tc_config_set_to_default(tc_config *config);


tc_result *tc_result_new();
void tc_result_free(tc_result *result);
int tc_result_count(const tc_result *result);
int tc_result_pattern_count(const tc_result *result);

tc_hit tc_result_get(const tc_result *result, int index);
tc_set tc_result_at(const tc_result *result, int index);




int tc_run(tc_set patterns, int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
# 199 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/candles.h"
int tc_abandoned_baby_bear(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_abandoned_baby_bull(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_big_black_candle(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_big_white_candle(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_black_marubozu(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_dragonfly_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_engulfing_bear(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_engulfing_bull(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_evening_doji_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_evening_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_four_price_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_gravestone_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_hammer(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_hanging_man(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_inverted_hammer(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_long_legged_doji(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_marubozu(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_morning_doji_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_morning_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_shooting_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_spinning_top(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_star(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_three_black_crows(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_three_white_soldiers(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
int tc_white_marubozu(int size, TC_REAL const *const *inputs, tc_config const *options, tc_result *output);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c" 2


double optionsd_small[] = {-20,-2,-1,0,.7,1,2,3,4,5,6,7,8,10,20,100,999};
double optionsd_large[] = {-5,0,1,2,5};

double dummy_in[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
double dummy_in0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
double dummy_ot[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

const int input_size = sizeof(dummy_in) / sizeof(double);
const int sizes[] = {0,1,2,3,4,8,20};
const int sizes_count = sizeof(sizes) / sizeof(int);


void banner() {
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
# 72 "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/fuzzer.c"
int errors_cnt = 0;

void check_output(const ti_indicator_info *info, int size, double const *const *inputs, double const * options, double *const *outputs) {

    const int s = info->start(options);

    int o;
    for (o = 0; o < info->outputs; ++o) {

        double max = 0;
        double min = 0;

        int i;
        for (i = 0; i < size - s; ++i) {
            const double op = outputs[o][i];
            const double in = inputs[0][i+s];

            max = in > max ? in : max;
            min = in < min ? in : min;

            switch (info->type) {

                default:
                    break;

                case 1:
                    if ((op > 4 && op > max * 1.5 + 2) || (op < -4 && op < min * 0.5 - 3)) {
                        do { int k, j; printf("\nInputs:"); for (k = 0; k < input_size; ++k) printf(" %f", inputs[0][k]); printf("\nOptions:"); for (k = 0; k < info->options; ++k) printf(" %f", options[k]); for (j = 0; j < info->outputs; ++j) { printf("\nOutput[%d]:", j); for (k = 0; k < input_size; ++k) printf(" %f", outputs[j][k]); } } while (0);
                        printf("\nERROR Output is out of range for input: input: %f output: %f\n", in, op);
                        errors_cnt += 1;
                        assert(0);
                    }
                    break;
            }
        }

    }
}


void stress_indicator(const ti_indicator_info *info) {
    const int opt_count = info->options;
    printf("%s (%s) (%d options)\n", info->name, info->full_name, opt_count);


    const double *inputs[16] = {0};
    const double *inputs0[16] = {0};
    double *outputs[16] = {0};

    int i;
    for (i = 0; i < 16; ++i) {
        inputs[i] = i < info->inputs ? dummy_in : 0;
        inputs0[i] = i < info->inputs ? dummy_in0 : 0;
        outputs[i] = i < info->outputs ? dummy_ot : 0;
    }


    int options_index[16 +1] = {0};
    double options[16];

    int choices;
    double *optionsd;
    if (opt_count <= 4) {
        choices = sizeof(optionsd_small) / sizeof(double);
        optionsd = optionsd_small;
    } else {
        choices = sizeof(optionsd_large) / sizeof(double);
        optionsd = optionsd_large;
    }


    int j, count = 0;
    do {
        ++count;

        for (j = 0; j < opt_count; ++j) {
            options[j] = optionsd[options_index[j]];
            printf(" %f", options[j]);
        }


        const int rz = info->indicator(input_size, inputs0, options, outputs);
        if (rz == 0) check_output(info, input_size, inputs0, options, outputs);


        for (int s = 0; s < sizes_count; ++s) {
            const int size = sizes[s];
            printf(" %d", size);
            const int r = info->indicator(size, inputs, options, outputs);
            if (r == 0) check_output(info, size, inputs, options, outputs);

            if (info->indicator_ref) {
                printf(" r");
                const int rr = info->indicator_ref(size, inputs, options, outputs);
                if (rr == 0) check_output(info, size, inputs, options, outputs);
            }


            if (info->stream_new) {
                ti_stream *stream;
                const int rs = info->stream_new(options, &stream);
                if (rs == 0 && stream) {
                    printf(" s");
                    int rsc = info->stream_run(stream, size, inputs, outputs);
                    if (rsc == 0) check_output(info, size, inputs, options, outputs);


                    for (int repeat = 0; repeat < 5; ++repeat) {
                        rsc = info->stream_run(stream, size, inputs, outputs);


                    }

                    info->stream_free(stream);
                }
            }

        }

        printf("\r                                                                          \r");

        j = 0;
        do {
            options_index[j] = (options_index[j] + 1) % choices;
        } while (options_index[j++] == 0);

    } while (j <= opt_count);

    assert(.1 > fabs(count - (pow(choices, opt_count))));
}


void stress_candle(const tc_candle_info *info) {
    printf("%s (%s)\n", info->name, info->full_name);

    const double *inputs[4] = {dummy_in, dummy_in, dummy_in, dummy_in};
    const double *inputs0[4] = {dummy_in0, dummy_in0, dummy_in0, dummy_in0};

    tc_config config;
    tc_config_set_to_default(&config);

    tc_result *output = tc_result_new();


    for (int s = 0; s < sizes_count; ++s) {
        const int size = sizes[s];

        info->candle(size, inputs, &config, output);
        assert(tc_result_count(output) <= size);
        assert(tc_result_pattern_count(output) <= size);

        for (int i = 0; i < tc_result_count(output); ++i) {
            tc_hit hit = tc_result_get(output, i);
            assert(hit.patterns != ((1L<<26)-1));
            assert(hit.index >= 0);
            assert(hit.index < size);
        }
        for (int i = 0; i < size; ++i) {
            tc_set patterns = tc_result_at(output, i);
            assert(patterns != ((1L<<26)-1));
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

    if (argc > 1) {
        const ti_indicator_info *ind_info = ti_find_indicator(argv[1]);
        if (ind_info) {
            stress_indicator(ind_info);
        }

        const tc_candle_info *cnd_info = tc_find_candle(argv[1]);
        if (cnd_info) {
            stress_candle(cnd_info);
        }
    } else {

        const ti_indicator_info *ind_info = ti_indicators;
        do {
            stress_indicator(ind_info);
        } while ((++ind_info)->name);

        const tc_candle_info *cnd_info = tc_candles;
        do {
            stress_candle(cnd_info);
        } while ((++cnd_info)->name);
    }

    printf("\r                                                  \rDone\n");

    return errors_cnt ? 1 : 0;
}
