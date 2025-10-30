# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c"
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 1
# 4902 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
typedef struct __dirstream DIR;
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 4903 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 4936 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 4937 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c" 2



# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/uchar.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wchar.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wctype.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 2
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unitypes.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unitypes.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unitypes.h" 2







typedef uint32_t ucs4_t;
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 2
# 52 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
typedef struct
{
  uint32_t bitmask : 31;
           unsigned int generic : 1;
  union
  {
    const void *table;
    bool (*lookup_fn) (ucs4_t uc, uint32_t bitmask);
  } lookup;
}
uc_general_category_t;





enum
{
  UC_CATEGORY_MASK_L = 0x0000001f,
  UC_CATEGORY_MASK_LC = 0x00000007,
  UC_CATEGORY_MASK_Lu = 0x00000001,
  UC_CATEGORY_MASK_Ll = 0x00000002,
  UC_CATEGORY_MASK_Lt = 0x00000004,
  UC_CATEGORY_MASK_Lm = 0x00000008,
  UC_CATEGORY_MASK_Lo = 0x00000010,
  UC_CATEGORY_MASK_M = 0x000000e0,
  UC_CATEGORY_MASK_Mn = 0x00000020,
  UC_CATEGORY_MASK_Mc = 0x00000040,
  UC_CATEGORY_MASK_Me = 0x00000080,
  UC_CATEGORY_MASK_N = 0x00000700,
  UC_CATEGORY_MASK_Nd = 0x00000100,
  UC_CATEGORY_MASK_Nl = 0x00000200,
  UC_CATEGORY_MASK_No = 0x00000400,
  UC_CATEGORY_MASK_P = 0x0003f800,
  UC_CATEGORY_MASK_Pc = 0x00000800,
  UC_CATEGORY_MASK_Pd = 0x00001000,
  UC_CATEGORY_MASK_Ps = 0x00002000,
  UC_CATEGORY_MASK_Pe = 0x00004000,
  UC_CATEGORY_MASK_Pi = 0x00008000,
  UC_CATEGORY_MASK_Pf = 0x00010000,
  UC_CATEGORY_MASK_Po = 0x00020000,
  UC_CATEGORY_MASK_S = 0x003c0000,
  UC_CATEGORY_MASK_Sm = 0x00040000,
  UC_CATEGORY_MASK_Sc = 0x00080000,
  UC_CATEGORY_MASK_Sk = 0x00100000,
  UC_CATEGORY_MASK_So = 0x00200000,
  UC_CATEGORY_MASK_Z = 0x01c00000,
  UC_CATEGORY_MASK_Zs = 0x00400000,
  UC_CATEGORY_MASK_Zl = 0x00800000,
  UC_CATEGORY_MASK_Zp = 0x01000000,
  UC_CATEGORY_MASK_C = 0x3e000000,
  UC_CATEGORY_MASK_Cc = 0x02000000,
  UC_CATEGORY_MASK_Cf = 0x04000000,
  UC_CATEGORY_MASK_Cs = 0x08000000,
  UC_CATEGORY_MASK_Co = 0x10000000,
  UC_CATEGORY_MASK_Cn = 0x20000000
};


extern const uc_general_category_t UC_CATEGORY_L;
extern const uc_general_category_t UC_CATEGORY_LC;
extern const uc_general_category_t UC_CATEGORY_Lu;
extern const uc_general_category_t UC_CATEGORY_Ll;
extern const uc_general_category_t UC_CATEGORY_Lt;
extern const uc_general_category_t UC_CATEGORY_Lm;
extern const uc_general_category_t UC_CATEGORY_Lo;
extern const uc_general_category_t UC_CATEGORY_M;
extern const uc_general_category_t UC_CATEGORY_Mn;
extern const uc_general_category_t UC_CATEGORY_Mc;
extern const uc_general_category_t UC_CATEGORY_Me;
extern const uc_general_category_t UC_CATEGORY_N;
extern const uc_general_category_t UC_CATEGORY_Nd;
extern const uc_general_category_t UC_CATEGORY_Nl;
extern const uc_general_category_t UC_CATEGORY_No;
extern const uc_general_category_t UC_CATEGORY_P;
extern const uc_general_category_t UC_CATEGORY_Pc;
extern const uc_general_category_t UC_CATEGORY_Pd;
extern const uc_general_category_t UC_CATEGORY_Ps;
extern const uc_general_category_t UC_CATEGORY_Pe;
extern const uc_general_category_t UC_CATEGORY_Pi;
extern const uc_general_category_t UC_CATEGORY_Pf;
extern const uc_general_category_t UC_CATEGORY_Po;
extern const uc_general_category_t UC_CATEGORY_S;
extern const uc_general_category_t UC_CATEGORY_Sm;
extern const uc_general_category_t UC_CATEGORY_Sc;
extern const uc_general_category_t UC_CATEGORY_Sk;
extern const uc_general_category_t UC_CATEGORY_So;
extern const uc_general_category_t UC_CATEGORY_Z;
extern const uc_general_category_t UC_CATEGORY_Zs;
extern const uc_general_category_t UC_CATEGORY_Zl;
extern const uc_general_category_t UC_CATEGORY_Zp;
extern const uc_general_category_t UC_CATEGORY_C;
extern const uc_general_category_t UC_CATEGORY_Cc;
extern const uc_general_category_t UC_CATEGORY_Cf;
extern const uc_general_category_t UC_CATEGORY_Cs;
extern const uc_general_category_t UC_CATEGORY_Co;
extern const uc_general_category_t UC_CATEGORY_Cn;

extern const uc_general_category_t _UC_CATEGORY_NONE;
# 194 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
extern uc_general_category_t
       uc_general_category_or (uc_general_category_t category1,
                               uc_general_category_t category2);




extern uc_general_category_t
       uc_general_category_and (uc_general_category_t category1,
                                uc_general_category_t category2);





extern uc_general_category_t
       uc_general_category_and_not (uc_general_category_t category1,
                                    uc_general_category_t category2);


extern const char *
       uc_general_category_name (uc_general_category_t category)
       ;


extern const char *
       uc_general_category_long_name (uc_general_category_t category)
       ;



extern uc_general_category_t
       uc_general_category_byname (const char *category_name)
       ;


extern uc_general_category_t
       uc_general_category (ucs4_t uc)
       ;




extern bool
       uc_is_general_category (ucs4_t uc, uc_general_category_t category)
       ;

extern bool
       uc_is_general_category_withtable (ucs4_t uc, uint32_t bitmask)
       ;
# 252 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
enum
{
  UC_CCC_NR = 0,
  UC_CCC_OV = 1,
  UC_CCC_NK = 7,
  UC_CCC_KV = 8,
  UC_CCC_VR = 9,
  UC_CCC_ATBL = 200,
  UC_CCC_ATB = 202,
  UC_CCC_ATA = 214,
  UC_CCC_ATAR = 216,
  UC_CCC_BL = 218,
  UC_CCC_B = 220,
  UC_CCC_BR = 222,
  UC_CCC_L = 224,
  UC_CCC_R = 226,
  UC_CCC_AL = 228,
  UC_CCC_A = 230,
  UC_CCC_AR = 232,
  UC_CCC_DB = 233,
  UC_CCC_DA = 234,
  UC_CCC_IS = 240
};


extern int
       uc_combining_class (ucs4_t uc)
       ;


extern const char *
       uc_combining_class_name (int ccc)
       ;


extern const char *
       uc_combining_class_long_name (int ccc)
       ;



extern int
       uc_combining_class_byname (const char *ccc_name)
       ;






enum
{
  UC_BIDI_L,
  UC_BIDI_LRE,
  UC_BIDI_LRO,
  UC_BIDI_R,
  UC_BIDI_AL,
  UC_BIDI_RLE,
  UC_BIDI_RLO,
  UC_BIDI_PDF,
  UC_BIDI_EN,
  UC_BIDI_ES,
  UC_BIDI_ET,
  UC_BIDI_AN,
  UC_BIDI_CS,
  UC_BIDI_NSM,
  UC_BIDI_BN,
  UC_BIDI_B,
  UC_BIDI_S,
  UC_BIDI_WS,
  UC_BIDI_ON,
  UC_BIDI_LRI,
  UC_BIDI_RLI,
  UC_BIDI_FSI,
  UC_BIDI_PDI
};


extern const char *
       uc_bidi_class_name (int bidi_class)
       ;

extern const char *
       uc_bidi_category_name (int category)
       ;


extern const char *
       uc_bidi_class_long_name (int bidi_class)
       ;



extern int
       uc_bidi_class_byname (const char *bidi_class_name)
       ;

extern int
       uc_bidi_category_byname (const char *category_name)
       ;


extern int
       uc_bidi_class (ucs4_t uc)
       ;

extern int
       uc_bidi_category (ucs4_t uc)
       ;


extern bool
       uc_is_bidi_class (ucs4_t uc, int bidi_class)
       ;

extern bool
       uc_is_bidi_category (ucs4_t uc, int category)
       ;
# 381 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
extern int
       uc_decimal_value (ucs4_t uc)
       ;






extern int
       uc_digit_value (ucs4_t uc)
       ;






typedef struct
{
  int numerator;
  int denominator;
}
uc_fraction_t;
extern uc_fraction_t
       uc_numeric_value (ucs4_t uc)
       ;






extern bool
       uc_mirror_char (ucs4_t uc, ucs4_t *puc);
# 437 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
enum
{
  UC_JOINING_TYPE_U,
  UC_JOINING_TYPE_T,
  UC_JOINING_TYPE_C,
  UC_JOINING_TYPE_L,
  UC_JOINING_TYPE_R,
  UC_JOINING_TYPE_D
};


extern const char *
       uc_joining_type_name (int joining_type)
       ;


extern const char *
       uc_joining_type_long_name (int joining_type)
       ;



extern int
       uc_joining_type_byname (const char *joining_type_name)
       ;


extern int
       uc_joining_type (ucs4_t uc)
       ;







enum
{
  UC_JOINING_GROUP_NONE,
  UC_JOINING_GROUP_AIN,
  UC_JOINING_GROUP_ALAPH,
  UC_JOINING_GROUP_ALEF,
  UC_JOINING_GROUP_BEH,
  UC_JOINING_GROUP_BETH,
  UC_JOINING_GROUP_BURUSHASKI_YEH_BARREE,
  UC_JOINING_GROUP_DAL,
  UC_JOINING_GROUP_DALATH_RISH,
  UC_JOINING_GROUP_E,
  UC_JOINING_GROUP_FARSI_YEH,
  UC_JOINING_GROUP_FE,
  UC_JOINING_GROUP_FEH,
  UC_JOINING_GROUP_FINAL_SEMKATH,
  UC_JOINING_GROUP_GAF,
  UC_JOINING_GROUP_GAMAL,
  UC_JOINING_GROUP_HAH,
  UC_JOINING_GROUP_HE,
  UC_JOINING_GROUP_HEH,
  UC_JOINING_GROUP_HEH_GOAL,
  UC_JOINING_GROUP_HETH,
  UC_JOINING_GROUP_KAF,
  UC_JOINING_GROUP_KAPH,
  UC_JOINING_GROUP_KHAPH,
  UC_JOINING_GROUP_KNOTTED_HEH,
  UC_JOINING_GROUP_LAM,
  UC_JOINING_GROUP_LAMADH,
  UC_JOINING_GROUP_MEEM,
  UC_JOINING_GROUP_MIM,
  UC_JOINING_GROUP_NOON,
  UC_JOINING_GROUP_NUN,
  UC_JOINING_GROUP_NYA,
  UC_JOINING_GROUP_PE,
  UC_JOINING_GROUP_QAF,
  UC_JOINING_GROUP_QAPH,
  UC_JOINING_GROUP_REH,
  UC_JOINING_GROUP_REVERSED_PE,
  UC_JOINING_GROUP_SAD,
  UC_JOINING_GROUP_SADHE,
  UC_JOINING_GROUP_SEEN,
  UC_JOINING_GROUP_SEMKATH,
  UC_JOINING_GROUP_SHIN,
  UC_JOINING_GROUP_SWASH_KAF,
  UC_JOINING_GROUP_SYRIAC_WAW,
  UC_JOINING_GROUP_TAH,
  UC_JOINING_GROUP_TAW,
  UC_JOINING_GROUP_TEH_MARBUTA,
  UC_JOINING_GROUP_TEH_MARBUTA_GOAL,
  UC_JOINING_GROUP_TETH,
  UC_JOINING_GROUP_WAW,
  UC_JOINING_GROUP_YEH,
  UC_JOINING_GROUP_YEH_BARREE,
  UC_JOINING_GROUP_YEH_WITH_TAIL,
  UC_JOINING_GROUP_YUDH,
  UC_JOINING_GROUP_YUDH_HE,
  UC_JOINING_GROUP_ZAIN,
  UC_JOINING_GROUP_ZHAIN,
  UC_JOINING_GROUP_ROHINGYA_YEH,
  UC_JOINING_GROUP_STRAIGHT_WAW,
  UC_JOINING_GROUP_MANICHAEAN_ALEPH,
  UC_JOINING_GROUP_MANICHAEAN_BETH,
  UC_JOINING_GROUP_MANICHAEAN_GIMEL,
  UC_JOINING_GROUP_MANICHAEAN_DALETH,
  UC_JOINING_GROUP_MANICHAEAN_WAW,
  UC_JOINING_GROUP_MANICHAEAN_ZAYIN,
  UC_JOINING_GROUP_MANICHAEAN_HETH,
  UC_JOINING_GROUP_MANICHAEAN_TETH,
  UC_JOINING_GROUP_MANICHAEAN_YODH,
  UC_JOINING_GROUP_MANICHAEAN_KAPH,
  UC_JOINING_GROUP_MANICHAEAN_LAMEDH,
  UC_JOINING_GROUP_MANICHAEAN_DHAMEDH,
  UC_JOINING_GROUP_MANICHAEAN_THAMEDH,
  UC_JOINING_GROUP_MANICHAEAN_MEM,
  UC_JOINING_GROUP_MANICHAEAN_NUN,
  UC_JOINING_GROUP_MANICHAEAN_SAMEKH,
  UC_JOINING_GROUP_MANICHAEAN_AYIN,
  UC_JOINING_GROUP_MANICHAEAN_PE,
  UC_JOINING_GROUP_MANICHAEAN_SADHE,
  UC_JOINING_GROUP_MANICHAEAN_QOPH,
  UC_JOINING_GROUP_MANICHAEAN_RESH,
  UC_JOINING_GROUP_MANICHAEAN_TAW,
  UC_JOINING_GROUP_MANICHAEAN_ONE,
  UC_JOINING_GROUP_MANICHAEAN_FIVE,
  UC_JOINING_GROUP_MANICHAEAN_TEN,
  UC_JOINING_GROUP_MANICHAEAN_TWENTY,
  UC_JOINING_GROUP_MANICHAEAN_HUNDRED,
  UC_JOINING_GROUP_AFRICAN_FEH,
  UC_JOINING_GROUP_AFRICAN_QAF,
  UC_JOINING_GROUP_AFRICAN_NOON,
  UC_JOINING_GROUP_MALAYALAM_NGA,
  UC_JOINING_GROUP_MALAYALAM_JA,
  UC_JOINING_GROUP_MALAYALAM_NYA,
  UC_JOINING_GROUP_MALAYALAM_TTA,
  UC_JOINING_GROUP_MALAYALAM_NNA,
  UC_JOINING_GROUP_MALAYALAM_NNNA,
  UC_JOINING_GROUP_MALAYALAM_BHA,
  UC_JOINING_GROUP_MALAYALAM_RA,
  UC_JOINING_GROUP_MALAYALAM_LLA,
  UC_JOINING_GROUP_MALAYALAM_LLLA,
  UC_JOINING_GROUP_MALAYALAM_SSA,
  UC_JOINING_GROUP_HANIFI_ROHINGYA_PA,
  UC_JOINING_GROUP_HANIFI_ROHINGYA_KINNA_YA,
  UC_JOINING_GROUP_THIN_YEH,
  UC_JOINING_GROUP_VERTICAL_TAIL
};


extern const char *
       uc_joining_group_name (int joining_group)
       ;


extern int
       uc_joining_group_byname (const char *joining_group_name)
       ;


extern int
       uc_joining_group (ucs4_t uc)
       ;
# 604 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
typedef struct
{
  bool (*test_fn) (ucs4_t uc);
}
uc_property_t;



extern const uc_property_t UC_PROPERTY_WHITE_SPACE;
extern const uc_property_t UC_PROPERTY_ALPHABETIC;
extern const uc_property_t UC_PROPERTY_OTHER_ALPHABETIC;
extern const uc_property_t UC_PROPERTY_NOT_A_CHARACTER;
extern const uc_property_t UC_PROPERTY_DEFAULT_IGNORABLE_CODE_POINT;
extern const uc_property_t UC_PROPERTY_OTHER_DEFAULT_IGNORABLE_CODE_POINT;
extern const uc_property_t UC_PROPERTY_DEPRECATED;
extern const uc_property_t UC_PROPERTY_LOGICAL_ORDER_EXCEPTION;
extern const uc_property_t UC_PROPERTY_VARIATION_SELECTOR;
extern const uc_property_t UC_PROPERTY_PRIVATE_USE;
extern const uc_property_t UC_PROPERTY_UNASSIGNED_CODE_VALUE;

extern const uc_property_t UC_PROPERTY_UPPERCASE;
extern const uc_property_t UC_PROPERTY_OTHER_UPPERCASE;
extern const uc_property_t UC_PROPERTY_LOWERCASE;
extern const uc_property_t UC_PROPERTY_OTHER_LOWERCASE;
extern const uc_property_t UC_PROPERTY_TITLECASE;
extern const uc_property_t UC_PROPERTY_CASED;
extern const uc_property_t UC_PROPERTY_CASE_IGNORABLE;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_LOWERCASED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_UPPERCASED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_TITLECASED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_CASEFOLDED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_CASEMAPPED;
extern const uc_property_t UC_PROPERTY_SOFT_DOTTED;

extern const uc_property_t UC_PROPERTY_ID_START;
extern const uc_property_t UC_PROPERTY_OTHER_ID_START;
extern const uc_property_t UC_PROPERTY_ID_CONTINUE;
extern const uc_property_t UC_PROPERTY_OTHER_ID_CONTINUE;
extern const uc_property_t UC_PROPERTY_XID_START;
extern const uc_property_t UC_PROPERTY_XID_CONTINUE;
extern const uc_property_t UC_PROPERTY_ID_COMPAT_MATH_START;
extern const uc_property_t UC_PROPERTY_ID_COMPAT_MATH_CONTINUE;
extern const uc_property_t UC_PROPERTY_PATTERN_WHITE_SPACE;
extern const uc_property_t UC_PROPERTY_PATTERN_SYNTAX;

extern const uc_property_t UC_PROPERTY_JOIN_CONTROL;
extern const uc_property_t UC_PROPERTY_GRAPHEME_BASE;
extern const uc_property_t UC_PROPERTY_GRAPHEME_EXTEND;
extern const uc_property_t UC_PROPERTY_OTHER_GRAPHEME_EXTEND;
extern const uc_property_t UC_PROPERTY_GRAPHEME_LINK;

extern const uc_property_t UC_PROPERTY_BIDI_CONTROL;
extern const uc_property_t UC_PROPERTY_BIDI_LEFT_TO_RIGHT;
extern const uc_property_t UC_PROPERTY_BIDI_HEBREW_RIGHT_TO_LEFT;
extern const uc_property_t UC_PROPERTY_BIDI_ARABIC_RIGHT_TO_LEFT;
extern const uc_property_t UC_PROPERTY_BIDI_EUROPEAN_DIGIT;
extern const uc_property_t UC_PROPERTY_BIDI_EUR_NUM_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_EUR_NUM_TERMINATOR;
extern const uc_property_t UC_PROPERTY_BIDI_ARABIC_DIGIT;
extern const uc_property_t UC_PROPERTY_BIDI_COMMON_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_BLOCK_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_SEGMENT_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_WHITESPACE;
extern const uc_property_t UC_PROPERTY_BIDI_NON_SPACING_MARK;
extern const uc_property_t UC_PROPERTY_BIDI_BOUNDARY_NEUTRAL;
extern const uc_property_t UC_PROPERTY_BIDI_PDF;
extern const uc_property_t UC_PROPERTY_BIDI_EMBEDDING_OR_OVERRIDE;
extern const uc_property_t UC_PROPERTY_BIDI_OTHER_NEUTRAL;

extern const uc_property_t UC_PROPERTY_HEX_DIGIT;
extern const uc_property_t UC_PROPERTY_ASCII_HEX_DIGIT;

extern const uc_property_t UC_PROPERTY_IDEOGRAPHIC;
extern const uc_property_t UC_PROPERTY_UNIFIED_IDEOGRAPH;
extern const uc_property_t UC_PROPERTY_RADICAL;
extern const uc_property_t UC_PROPERTY_IDS_UNARY_OPERATOR;
extern const uc_property_t UC_PROPERTY_IDS_BINARY_OPERATOR;
extern const uc_property_t UC_PROPERTY_IDS_TRINARY_OPERATOR;

extern const uc_property_t UC_PROPERTY_EMOJI;
extern const uc_property_t UC_PROPERTY_EMOJI_PRESENTATION;
extern const uc_property_t UC_PROPERTY_EMOJI_MODIFIER;
extern const uc_property_t UC_PROPERTY_EMOJI_MODIFIER_BASE;
extern const uc_property_t UC_PROPERTY_EMOJI_COMPONENT;
extern const uc_property_t UC_PROPERTY_EXTENDED_PICTOGRAPHIC;

extern const uc_property_t UC_PROPERTY_ZERO_WIDTH;
extern const uc_property_t UC_PROPERTY_SPACE;
extern const uc_property_t UC_PROPERTY_NON_BREAK;
extern const uc_property_t UC_PROPERTY_ISO_CONTROL;
extern const uc_property_t UC_PROPERTY_FORMAT_CONTROL;
extern const uc_property_t UC_PROPERTY_PREPENDED_CONCATENATION_MARK;
extern const uc_property_t UC_PROPERTY_DASH;
extern const uc_property_t UC_PROPERTY_HYPHEN;
extern const uc_property_t UC_PROPERTY_PUNCTUATION;
extern const uc_property_t UC_PROPERTY_LINE_SEPARATOR;
extern const uc_property_t UC_PROPERTY_PARAGRAPH_SEPARATOR;
extern const uc_property_t UC_PROPERTY_QUOTATION_MARK;
extern const uc_property_t UC_PROPERTY_SENTENCE_TERMINAL;
extern const uc_property_t UC_PROPERTY_TERMINAL_PUNCTUATION;
extern const uc_property_t UC_PROPERTY_CURRENCY_SYMBOL;
extern const uc_property_t UC_PROPERTY_MATH;
extern const uc_property_t UC_PROPERTY_OTHER_MATH;
extern const uc_property_t UC_PROPERTY_PAIRED_PUNCTUATION;
extern const uc_property_t UC_PROPERTY_LEFT_OF_PAIR;
extern const uc_property_t UC_PROPERTY_COMBINING;
extern const uc_property_t UC_PROPERTY_COMPOSITE;
extern const uc_property_t UC_PROPERTY_DECIMAL_DIGIT;
extern const uc_property_t UC_PROPERTY_NUMERIC;
extern const uc_property_t UC_PROPERTY_DIACRITIC;
extern const uc_property_t UC_PROPERTY_EXTENDER;
extern const uc_property_t UC_PROPERTY_IGNORABLE_CONTROL;
extern const uc_property_t UC_PROPERTY_REGIONAL_INDICATOR;


extern uc_property_t
       uc_property_byname (const char *property_name);





extern bool
       uc_is_property (ucs4_t uc, uc_property_t property);
extern bool uc_is_property_white_space (ucs4_t uc)
       ;
extern bool uc_is_property_alphabetic (ucs4_t uc)
       ;
extern bool uc_is_property_other_alphabetic (ucs4_t uc)
       ;
extern bool uc_is_property_not_a_character (ucs4_t uc)
       ;
extern bool uc_is_property_default_ignorable_code_point (ucs4_t uc)
       ;
extern bool uc_is_property_other_default_ignorable_code_point (ucs4_t uc)
       ;
extern bool uc_is_property_deprecated (ucs4_t uc)
       ;
extern bool uc_is_property_logical_order_exception (ucs4_t uc)
       ;
extern bool uc_is_property_variation_selector (ucs4_t uc)
       ;
extern bool uc_is_property_private_use (ucs4_t uc)
       ;
extern bool uc_is_property_unassigned_code_value (ucs4_t uc)
       ;
extern bool uc_is_property_uppercase (ucs4_t uc)
       ;
extern bool uc_is_property_other_uppercase (ucs4_t uc)
       ;
extern bool uc_is_property_lowercase (ucs4_t uc)
       ;
extern bool uc_is_property_other_lowercase (ucs4_t uc)
       ;
extern bool uc_is_property_titlecase (ucs4_t uc)
       ;
extern bool uc_is_property_cased (ucs4_t uc)
       ;
extern bool uc_is_property_case_ignorable (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_lowercased (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_uppercased (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_titlecased (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_casefolded (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_casemapped (ucs4_t uc)
       ;
extern bool uc_is_property_soft_dotted (ucs4_t uc)
       ;
extern bool uc_is_property_id_start (ucs4_t uc)
       ;
extern bool uc_is_property_other_id_start (ucs4_t uc)
       ;
extern bool uc_is_property_id_continue (ucs4_t uc)
       ;
extern bool uc_is_property_other_id_continue (ucs4_t uc)
       ;
extern bool uc_is_property_xid_start (ucs4_t uc)
       ;
extern bool uc_is_property_xid_continue (ucs4_t uc)
       ;
extern bool uc_is_property_id_compat_math_start (ucs4_t uc)
       ;
extern bool uc_is_property_id_compat_math_continue (ucs4_t uc)
       ;
extern bool uc_is_property_pattern_white_space (ucs4_t uc)
       ;
extern bool uc_is_property_pattern_syntax (ucs4_t uc)
       ;
extern bool uc_is_property_join_control (ucs4_t uc)
       ;
extern bool uc_is_property_grapheme_base (ucs4_t uc)
       ;
extern bool uc_is_property_grapheme_extend (ucs4_t uc)
       ;
extern bool uc_is_property_other_grapheme_extend (ucs4_t uc)
       ;
extern bool uc_is_property_grapheme_link (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_control (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_left_to_right (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_hebrew_right_to_left (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_arabic_right_to_left (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_european_digit (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_eur_num_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_eur_num_terminator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_arabic_digit (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_common_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_block_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_segment_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_whitespace (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_non_spacing_mark (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_boundary_neutral (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_pdf (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_embedding_or_override (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_other_neutral (ucs4_t uc)
       ;
extern bool uc_is_property_hex_digit (ucs4_t uc)
       ;
extern bool uc_is_property_ascii_hex_digit (ucs4_t uc)
       ;
extern bool uc_is_property_ideographic (ucs4_t uc)
       ;
extern bool uc_is_property_unified_ideograph (ucs4_t uc)
       ;
extern bool uc_is_property_radical (ucs4_t uc)
       ;
extern bool uc_is_property_ids_unary_operator (ucs4_t uc)
       ;
extern bool uc_is_property_ids_binary_operator (ucs4_t uc)
       ;
extern bool uc_is_property_ids_trinary_operator (ucs4_t uc)
       ;
extern bool uc_is_property_emoji (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_presentation (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_modifier (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_modifier_base (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_component (ucs4_t uc)
       ;
extern bool uc_is_property_extended_pictographic (ucs4_t uc)
       ;
extern bool uc_is_property_zero_width (ucs4_t uc)
       ;
extern bool uc_is_property_space (ucs4_t uc)
       ;
extern bool uc_is_property_non_break (ucs4_t uc)
       ;
extern bool uc_is_property_iso_control (ucs4_t uc)
       ;
extern bool uc_is_property_format_control (ucs4_t uc)
       ;
extern bool uc_is_property_prepended_concatenation_mark (ucs4_t uc)
       ;
extern bool uc_is_property_dash (ucs4_t uc)
       ;
extern bool uc_is_property_hyphen (ucs4_t uc)
       ;
extern bool uc_is_property_punctuation (ucs4_t uc)
       ;
extern bool uc_is_property_line_separator (ucs4_t uc)
       ;
extern bool uc_is_property_paragraph_separator (ucs4_t uc)
       ;
extern bool uc_is_property_quotation_mark (ucs4_t uc)
       ;
extern bool uc_is_property_sentence_terminal (ucs4_t uc)
       ;
extern bool uc_is_property_terminal_punctuation (ucs4_t uc)
       ;
extern bool uc_is_property_currency_symbol (ucs4_t uc)
       ;
extern bool uc_is_property_math (ucs4_t uc)
       ;
extern bool uc_is_property_other_math (ucs4_t uc)
       ;
extern bool uc_is_property_paired_punctuation (ucs4_t uc)
       ;
extern bool uc_is_property_left_of_pair (ucs4_t uc)
       ;
extern bool uc_is_property_combining (ucs4_t uc)
       ;
extern bool uc_is_property_composite (ucs4_t uc)
       ;
extern bool uc_is_property_decimal_digit (ucs4_t uc)
       ;
extern bool uc_is_property_numeric (ucs4_t uc)
       ;
extern bool uc_is_property_diacritic (ucs4_t uc)
       ;
extern bool uc_is_property_extender (ucs4_t uc)
       ;
extern bool uc_is_property_ignorable_control (ucs4_t uc)
       ;
extern bool uc_is_property_regional_indicator (ucs4_t uc)
       ;
# 934 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
enum
{
  UC_INDIC_CONJUNCT_BREAK_NONE,
  UC_INDIC_CONJUNCT_BREAK_CONSONANT,
  UC_INDIC_CONJUNCT_BREAK_LINKER,
  UC_INDIC_CONJUNCT_BREAK_EXTEND
};


extern const char *
       uc_indic_conjunct_break_name (int indic_conjunct_break)
       ;


extern int
       uc_indic_conjunct_break_byname (const char *indic_conjunct_break_name)
       ;


extern int
       uc_indic_conjunct_break (ucs4_t uc)
       ;





typedef struct
{
  unsigned int code : 21;
  unsigned int start : 1;
  unsigned int end : 1;
}
uc_interval_t;
typedef struct
{
  unsigned int nintervals;
  const uc_interval_t *intervals;
  const char *name;
}
uc_script_t;


extern const uc_script_t *
       uc_script (ucs4_t uc)
       ;


extern const uc_script_t *
       uc_script_byname (const char *script_name)
       ;


extern bool
       uc_is_script (ucs4_t uc, const uc_script_t *script)
       ;


extern void
       uc_all_scripts (const uc_script_t **scripts, size_t *count);





typedef struct
{
  ucs4_t start;
  ucs4_t end;
  const char *name;
}
uc_block_t;


extern const uc_block_t *
       uc_block (ucs4_t uc)
       ;


extern bool
       uc_is_block (ucs4_t uc, const uc_block_t *block)
       ;


extern void
       uc_all_blocks (const uc_block_t **blocks, size_t *count);






extern bool
       uc_is_c_whitespace (ucs4_t uc)
       ;


extern bool
       uc_is_java_whitespace (ucs4_t uc)
       ;

enum
{
  UC_IDENTIFIER_START,
  UC_IDENTIFIER_VALID,
  UC_IDENTIFIER_INVALID,
  UC_IDENTIFIER_IGNORABLE
};



extern int
       uc_c_ident_category (ucs4_t uc)
       ;



extern int
       uc_java_ident_category (ucs4_t uc)
       ;
# 1064 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
extern bool
       uc_is_alnum (ucs4_t uc)
       ;





extern bool
       uc_is_alpha (ucs4_t uc)
       ;


extern bool
       uc_is_cntrl (ucs4_t uc)
       ;


extern bool
       uc_is_digit (ucs4_t uc)
       ;



extern bool
       uc_is_graph (ucs4_t uc)
       ;




extern bool
       uc_is_lower (ucs4_t uc)
       ;


extern bool
       uc_is_print (ucs4_t uc)
       ;



extern bool
       uc_is_punct (ucs4_t uc)
       ;




extern bool
       uc_is_space (ucs4_t uc)
       ;




extern bool
       uc_is_upper (ucs4_t uc)
       ;



extern bool
       uc_is_xdigit (ucs4_t uc)
       ;




extern bool
       uc_is_blank (ucs4_t uc)
       ;
# 36 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 2




int
c32isprint (wint_t wc)
{
# 70 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
  if (wc != WEOF)
    return uc_is_print (wc);
  else
    return 0;
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
}
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c" 2
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c"
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 1
# 4902 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
typedef struct __dirstream DIR;
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 4903 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 4936 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 4937 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c" 2



# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/uchar.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wchar.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wctype.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 2
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unitypes.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unitypes.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unitypes.h" 2







typedef uint32_t ucs4_t;
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h" 2
# 52 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
typedef struct
{
  uint32_t bitmask : 31;
           unsigned int generic : 1;
  union
  {
    const void *table;
    bool (*lookup_fn) (ucs4_t uc, uint32_t bitmask);
  } lookup;
}
uc_general_category_t;





enum
{
  UC_CATEGORY_MASK_L = 0x0000001f,
  UC_CATEGORY_MASK_LC = 0x00000007,
  UC_CATEGORY_MASK_Lu = 0x00000001,
  UC_CATEGORY_MASK_Ll = 0x00000002,
  UC_CATEGORY_MASK_Lt = 0x00000004,
  UC_CATEGORY_MASK_Lm = 0x00000008,
  UC_CATEGORY_MASK_Lo = 0x00000010,
  UC_CATEGORY_MASK_M = 0x000000e0,
  UC_CATEGORY_MASK_Mn = 0x00000020,
  UC_CATEGORY_MASK_Mc = 0x00000040,
  UC_CATEGORY_MASK_Me = 0x00000080,
  UC_CATEGORY_MASK_N = 0x00000700,
  UC_CATEGORY_MASK_Nd = 0x00000100,
  UC_CATEGORY_MASK_Nl = 0x00000200,
  UC_CATEGORY_MASK_No = 0x00000400,
  UC_CATEGORY_MASK_P = 0x0003f800,
  UC_CATEGORY_MASK_Pc = 0x00000800,
  UC_CATEGORY_MASK_Pd = 0x00001000,
  UC_CATEGORY_MASK_Ps = 0x00002000,
  UC_CATEGORY_MASK_Pe = 0x00004000,
  UC_CATEGORY_MASK_Pi = 0x00008000,
  UC_CATEGORY_MASK_Pf = 0x00010000,
  UC_CATEGORY_MASK_Po = 0x00020000,
  UC_CATEGORY_MASK_S = 0x003c0000,
  UC_CATEGORY_MASK_Sm = 0x00040000,
  UC_CATEGORY_MASK_Sc = 0x00080000,
  UC_CATEGORY_MASK_Sk = 0x00100000,
  UC_CATEGORY_MASK_So = 0x00200000,
  UC_CATEGORY_MASK_Z = 0x01c00000,
  UC_CATEGORY_MASK_Zs = 0x00400000,
  UC_CATEGORY_MASK_Zl = 0x00800000,
  UC_CATEGORY_MASK_Zp = 0x01000000,
  UC_CATEGORY_MASK_C = 0x3e000000,
  UC_CATEGORY_MASK_Cc = 0x02000000,
  UC_CATEGORY_MASK_Cf = 0x04000000,
  UC_CATEGORY_MASK_Cs = 0x08000000,
  UC_CATEGORY_MASK_Co = 0x10000000,
  UC_CATEGORY_MASK_Cn = 0x20000000
};


extern const uc_general_category_t UC_CATEGORY_L;
extern const uc_general_category_t UC_CATEGORY_LC;
extern const uc_general_category_t UC_CATEGORY_Lu;
extern const uc_general_category_t UC_CATEGORY_Ll;
extern const uc_general_category_t UC_CATEGORY_Lt;
extern const uc_general_category_t UC_CATEGORY_Lm;
extern const uc_general_category_t UC_CATEGORY_Lo;
extern const uc_general_category_t UC_CATEGORY_M;
extern const uc_general_category_t UC_CATEGORY_Mn;
extern const uc_general_category_t UC_CATEGORY_Mc;
extern const uc_general_category_t UC_CATEGORY_Me;
extern const uc_general_category_t UC_CATEGORY_N;
extern const uc_general_category_t UC_CATEGORY_Nd;
extern const uc_general_category_t UC_CATEGORY_Nl;
extern const uc_general_category_t UC_CATEGORY_No;
extern const uc_general_category_t UC_CATEGORY_P;
extern const uc_general_category_t UC_CATEGORY_Pc;
extern const uc_general_category_t UC_CATEGORY_Pd;
extern const uc_general_category_t UC_CATEGORY_Ps;
extern const uc_general_category_t UC_CATEGORY_Pe;
extern const uc_general_category_t UC_CATEGORY_Pi;
extern const uc_general_category_t UC_CATEGORY_Pf;
extern const uc_general_category_t UC_CATEGORY_Po;
extern const uc_general_category_t UC_CATEGORY_S;
extern const uc_general_category_t UC_CATEGORY_Sm;
extern const uc_general_category_t UC_CATEGORY_Sc;
extern const uc_general_category_t UC_CATEGORY_Sk;
extern const uc_general_category_t UC_CATEGORY_So;
extern const uc_general_category_t UC_CATEGORY_Z;
extern const uc_general_category_t UC_CATEGORY_Zs;
extern const uc_general_category_t UC_CATEGORY_Zl;
extern const uc_general_category_t UC_CATEGORY_Zp;
extern const uc_general_category_t UC_CATEGORY_C;
extern const uc_general_category_t UC_CATEGORY_Cc;
extern const uc_general_category_t UC_CATEGORY_Cf;
extern const uc_general_category_t UC_CATEGORY_Cs;
extern const uc_general_category_t UC_CATEGORY_Co;
extern const uc_general_category_t UC_CATEGORY_Cn;

extern const uc_general_category_t _UC_CATEGORY_NONE;
# 194 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
extern uc_general_category_t
       uc_general_category_or (uc_general_category_t category1,
                               uc_general_category_t category2);




extern uc_general_category_t
       uc_general_category_and (uc_general_category_t category1,
                                uc_general_category_t category2);





extern uc_general_category_t
       uc_general_category_and_not (uc_general_category_t category1,
                                    uc_general_category_t category2);


extern const char *
       uc_general_category_name (uc_general_category_t category)
       ;


extern const char *
       uc_general_category_long_name (uc_general_category_t category)
       ;



extern uc_general_category_t
       uc_general_category_byname (const char *category_name)
       ;


extern uc_general_category_t
       uc_general_category (ucs4_t uc)
       ;




extern bool
       uc_is_general_category (ucs4_t uc, uc_general_category_t category)
       ;

extern bool
       uc_is_general_category_withtable (ucs4_t uc, uint32_t bitmask)
       ;
# 252 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
enum
{
  UC_CCC_NR = 0,
  UC_CCC_OV = 1,
  UC_CCC_NK = 7,
  UC_CCC_KV = 8,
  UC_CCC_VR = 9,
  UC_CCC_ATBL = 200,
  UC_CCC_ATB = 202,
  UC_CCC_ATA = 214,
  UC_CCC_ATAR = 216,
  UC_CCC_BL = 218,
  UC_CCC_B = 220,
  UC_CCC_BR = 222,
  UC_CCC_L = 224,
  UC_CCC_R = 226,
  UC_CCC_AL = 228,
  UC_CCC_A = 230,
  UC_CCC_AR = 232,
  UC_CCC_DB = 233,
  UC_CCC_DA = 234,
  UC_CCC_IS = 240
};


extern int
       uc_combining_class (ucs4_t uc)
       ;


extern const char *
       uc_combining_class_name (int ccc)
       ;


extern const char *
       uc_combining_class_long_name (int ccc)
       ;



extern int
       uc_combining_class_byname (const char *ccc_name)
       ;






enum
{
  UC_BIDI_L,
  UC_BIDI_LRE,
  UC_BIDI_LRO,
  UC_BIDI_R,
  UC_BIDI_AL,
  UC_BIDI_RLE,
  UC_BIDI_RLO,
  UC_BIDI_PDF,
  UC_BIDI_EN,
  UC_BIDI_ES,
  UC_BIDI_ET,
  UC_BIDI_AN,
  UC_BIDI_CS,
  UC_BIDI_NSM,
  UC_BIDI_BN,
  UC_BIDI_B,
  UC_BIDI_S,
  UC_BIDI_WS,
  UC_BIDI_ON,
  UC_BIDI_LRI,
  UC_BIDI_RLI,
  UC_BIDI_FSI,
  UC_BIDI_PDI
};


extern const char *
       uc_bidi_class_name (int bidi_class)
       ;

extern const char *
       uc_bidi_category_name (int category)
       ;


extern const char *
       uc_bidi_class_long_name (int bidi_class)
       ;



extern int
       uc_bidi_class_byname (const char *bidi_class_name)
       ;

extern int
       uc_bidi_category_byname (const char *category_name)
       ;


extern int
       uc_bidi_class (ucs4_t uc)
       ;

extern int
       uc_bidi_category (ucs4_t uc)
       ;


extern bool
       uc_is_bidi_class (ucs4_t uc, int bidi_class)
       ;

extern bool
       uc_is_bidi_category (ucs4_t uc, int category)
       ;
# 381 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
extern int
       uc_decimal_value (ucs4_t uc)
       ;






extern int
       uc_digit_value (ucs4_t uc)
       ;






typedef struct
{
  int numerator;
  int denominator;
}
uc_fraction_t;
extern uc_fraction_t
       uc_numeric_value (ucs4_t uc)
       ;






extern bool
       uc_mirror_char (ucs4_t uc, ucs4_t *puc);
# 437 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
enum
{
  UC_JOINING_TYPE_U,
  UC_JOINING_TYPE_T,
  UC_JOINING_TYPE_C,
  UC_JOINING_TYPE_L,
  UC_JOINING_TYPE_R,
  UC_JOINING_TYPE_D
};


extern const char *
       uc_joining_type_name (int joining_type)
       ;


extern const char *
       uc_joining_type_long_name (int joining_type)
       ;



extern int
       uc_joining_type_byname (const char *joining_type_name)
       ;


extern int
       uc_joining_type (ucs4_t uc)
       ;







enum
{
  UC_JOINING_GROUP_NONE,
  UC_JOINING_GROUP_AIN,
  UC_JOINING_GROUP_ALAPH,
  UC_JOINING_GROUP_ALEF,
  UC_JOINING_GROUP_BEH,
  UC_JOINING_GROUP_BETH,
  UC_JOINING_GROUP_BURUSHASKI_YEH_BARREE,
  UC_JOINING_GROUP_DAL,
  UC_JOINING_GROUP_DALATH_RISH,
  UC_JOINING_GROUP_E,
  UC_JOINING_GROUP_FARSI_YEH,
  UC_JOINING_GROUP_FE,
  UC_JOINING_GROUP_FEH,
  UC_JOINING_GROUP_FINAL_SEMKATH,
  UC_JOINING_GROUP_GAF,
  UC_JOINING_GROUP_GAMAL,
  UC_JOINING_GROUP_HAH,
  UC_JOINING_GROUP_HE,
  UC_JOINING_GROUP_HEH,
  UC_JOINING_GROUP_HEH_GOAL,
  UC_JOINING_GROUP_HETH,
  UC_JOINING_GROUP_KAF,
  UC_JOINING_GROUP_KAPH,
  UC_JOINING_GROUP_KHAPH,
  UC_JOINING_GROUP_KNOTTED_HEH,
  UC_JOINING_GROUP_LAM,
  UC_JOINING_GROUP_LAMADH,
  UC_JOINING_GROUP_MEEM,
  UC_JOINING_GROUP_MIM,
  UC_JOINING_GROUP_NOON,
  UC_JOINING_GROUP_NUN,
  UC_JOINING_GROUP_NYA,
  UC_JOINING_GROUP_PE,
  UC_JOINING_GROUP_QAF,
  UC_JOINING_GROUP_QAPH,
  UC_JOINING_GROUP_REH,
  UC_JOINING_GROUP_REVERSED_PE,
  UC_JOINING_GROUP_SAD,
  UC_JOINING_GROUP_SADHE,
  UC_JOINING_GROUP_SEEN,
  UC_JOINING_GROUP_SEMKATH,
  UC_JOINING_GROUP_SHIN,
  UC_JOINING_GROUP_SWASH_KAF,
  UC_JOINING_GROUP_SYRIAC_WAW,
  UC_JOINING_GROUP_TAH,
  UC_JOINING_GROUP_TAW,
  UC_JOINING_GROUP_TEH_MARBUTA,
  UC_JOINING_GROUP_TEH_MARBUTA_GOAL,
  UC_JOINING_GROUP_TETH,
  UC_JOINING_GROUP_WAW,
  UC_JOINING_GROUP_YEH,
  UC_JOINING_GROUP_YEH_BARREE,
  UC_JOINING_GROUP_YEH_WITH_TAIL,
  UC_JOINING_GROUP_YUDH,
  UC_JOINING_GROUP_YUDH_HE,
  UC_JOINING_GROUP_ZAIN,
  UC_JOINING_GROUP_ZHAIN,
  UC_JOINING_GROUP_ROHINGYA_YEH,
  UC_JOINING_GROUP_STRAIGHT_WAW,
  UC_JOINING_GROUP_MANICHAEAN_ALEPH,
  UC_JOINING_GROUP_MANICHAEAN_BETH,
  UC_JOINING_GROUP_MANICHAEAN_GIMEL,
  UC_JOINING_GROUP_MANICHAEAN_DALETH,
  UC_JOINING_GROUP_MANICHAEAN_WAW,
  UC_JOINING_GROUP_MANICHAEAN_ZAYIN,
  UC_JOINING_GROUP_MANICHAEAN_HETH,
  UC_JOINING_GROUP_MANICHAEAN_TETH,
  UC_JOINING_GROUP_MANICHAEAN_YODH,
  UC_JOINING_GROUP_MANICHAEAN_KAPH,
  UC_JOINING_GROUP_MANICHAEAN_LAMEDH,
  UC_JOINING_GROUP_MANICHAEAN_DHAMEDH,
  UC_JOINING_GROUP_MANICHAEAN_THAMEDH,
  UC_JOINING_GROUP_MANICHAEAN_MEM,
  UC_JOINING_GROUP_MANICHAEAN_NUN,
  UC_JOINING_GROUP_MANICHAEAN_SAMEKH,
  UC_JOINING_GROUP_MANICHAEAN_AYIN,
  UC_JOINING_GROUP_MANICHAEAN_PE,
  UC_JOINING_GROUP_MANICHAEAN_SADHE,
  UC_JOINING_GROUP_MANICHAEAN_QOPH,
  UC_JOINING_GROUP_MANICHAEAN_RESH,
  UC_JOINING_GROUP_MANICHAEAN_TAW,
  UC_JOINING_GROUP_MANICHAEAN_ONE,
  UC_JOINING_GROUP_MANICHAEAN_FIVE,
  UC_JOINING_GROUP_MANICHAEAN_TEN,
  UC_JOINING_GROUP_MANICHAEAN_TWENTY,
  UC_JOINING_GROUP_MANICHAEAN_HUNDRED,
  UC_JOINING_GROUP_AFRICAN_FEH,
  UC_JOINING_GROUP_AFRICAN_QAF,
  UC_JOINING_GROUP_AFRICAN_NOON,
  UC_JOINING_GROUP_MALAYALAM_NGA,
  UC_JOINING_GROUP_MALAYALAM_JA,
  UC_JOINING_GROUP_MALAYALAM_NYA,
  UC_JOINING_GROUP_MALAYALAM_TTA,
  UC_JOINING_GROUP_MALAYALAM_NNA,
  UC_JOINING_GROUP_MALAYALAM_NNNA,
  UC_JOINING_GROUP_MALAYALAM_BHA,
  UC_JOINING_GROUP_MALAYALAM_RA,
  UC_JOINING_GROUP_MALAYALAM_LLA,
  UC_JOINING_GROUP_MALAYALAM_LLLA,
  UC_JOINING_GROUP_MALAYALAM_SSA,
  UC_JOINING_GROUP_HANIFI_ROHINGYA_PA,
  UC_JOINING_GROUP_HANIFI_ROHINGYA_KINNA_YA,
  UC_JOINING_GROUP_THIN_YEH,
  UC_JOINING_GROUP_VERTICAL_TAIL
};


extern const char *
       uc_joining_group_name (int joining_group)
       ;


extern int
       uc_joining_group_byname (const char *joining_group_name)
       ;


extern int
       uc_joining_group (ucs4_t uc)
       ;
# 604 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
typedef struct
{
  bool (*test_fn) (ucs4_t uc);
}
uc_property_t;



extern const uc_property_t UC_PROPERTY_WHITE_SPACE;
extern const uc_property_t UC_PROPERTY_ALPHABETIC;
extern const uc_property_t UC_PROPERTY_OTHER_ALPHABETIC;
extern const uc_property_t UC_PROPERTY_NOT_A_CHARACTER;
extern const uc_property_t UC_PROPERTY_DEFAULT_IGNORABLE_CODE_POINT;
extern const uc_property_t UC_PROPERTY_OTHER_DEFAULT_IGNORABLE_CODE_POINT;
extern const uc_property_t UC_PROPERTY_DEPRECATED;
extern const uc_property_t UC_PROPERTY_LOGICAL_ORDER_EXCEPTION;
extern const uc_property_t UC_PROPERTY_VARIATION_SELECTOR;
extern const uc_property_t UC_PROPERTY_PRIVATE_USE;
extern const uc_property_t UC_PROPERTY_UNASSIGNED_CODE_VALUE;

extern const uc_property_t UC_PROPERTY_UPPERCASE;
extern const uc_property_t UC_PROPERTY_OTHER_UPPERCASE;
extern const uc_property_t UC_PROPERTY_LOWERCASE;
extern const uc_property_t UC_PROPERTY_OTHER_LOWERCASE;
extern const uc_property_t UC_PROPERTY_TITLECASE;
extern const uc_property_t UC_PROPERTY_CASED;
extern const uc_property_t UC_PROPERTY_CASE_IGNORABLE;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_LOWERCASED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_UPPERCASED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_TITLECASED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_CASEFOLDED;
extern const uc_property_t UC_PROPERTY_CHANGES_WHEN_CASEMAPPED;
extern const uc_property_t UC_PROPERTY_SOFT_DOTTED;

extern const uc_property_t UC_PROPERTY_ID_START;
extern const uc_property_t UC_PROPERTY_OTHER_ID_START;
extern const uc_property_t UC_PROPERTY_ID_CONTINUE;
extern const uc_property_t UC_PROPERTY_OTHER_ID_CONTINUE;
extern const uc_property_t UC_PROPERTY_XID_START;
extern const uc_property_t UC_PROPERTY_XID_CONTINUE;
extern const uc_property_t UC_PROPERTY_ID_COMPAT_MATH_START;
extern const uc_property_t UC_PROPERTY_ID_COMPAT_MATH_CONTINUE;
extern const uc_property_t UC_PROPERTY_PATTERN_WHITE_SPACE;
extern const uc_property_t UC_PROPERTY_PATTERN_SYNTAX;

extern const uc_property_t UC_PROPERTY_JOIN_CONTROL;
extern const uc_property_t UC_PROPERTY_GRAPHEME_BASE;
extern const uc_property_t UC_PROPERTY_GRAPHEME_EXTEND;
extern const uc_property_t UC_PROPERTY_OTHER_GRAPHEME_EXTEND;
extern const uc_property_t UC_PROPERTY_GRAPHEME_LINK;

extern const uc_property_t UC_PROPERTY_BIDI_CONTROL;
extern const uc_property_t UC_PROPERTY_BIDI_LEFT_TO_RIGHT;
extern const uc_property_t UC_PROPERTY_BIDI_HEBREW_RIGHT_TO_LEFT;
extern const uc_property_t UC_PROPERTY_BIDI_ARABIC_RIGHT_TO_LEFT;
extern const uc_property_t UC_PROPERTY_BIDI_EUROPEAN_DIGIT;
extern const uc_property_t UC_PROPERTY_BIDI_EUR_NUM_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_EUR_NUM_TERMINATOR;
extern const uc_property_t UC_PROPERTY_BIDI_ARABIC_DIGIT;
extern const uc_property_t UC_PROPERTY_BIDI_COMMON_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_BLOCK_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_SEGMENT_SEPARATOR;
extern const uc_property_t UC_PROPERTY_BIDI_WHITESPACE;
extern const uc_property_t UC_PROPERTY_BIDI_NON_SPACING_MARK;
extern const uc_property_t UC_PROPERTY_BIDI_BOUNDARY_NEUTRAL;
extern const uc_property_t UC_PROPERTY_BIDI_PDF;
extern const uc_property_t UC_PROPERTY_BIDI_EMBEDDING_OR_OVERRIDE;
extern const uc_property_t UC_PROPERTY_BIDI_OTHER_NEUTRAL;

extern const uc_property_t UC_PROPERTY_HEX_DIGIT;
extern const uc_property_t UC_PROPERTY_ASCII_HEX_DIGIT;

extern const uc_property_t UC_PROPERTY_IDEOGRAPHIC;
extern const uc_property_t UC_PROPERTY_UNIFIED_IDEOGRAPH;
extern const uc_property_t UC_PROPERTY_RADICAL;
extern const uc_property_t UC_PROPERTY_IDS_UNARY_OPERATOR;
extern const uc_property_t UC_PROPERTY_IDS_BINARY_OPERATOR;
extern const uc_property_t UC_PROPERTY_IDS_TRINARY_OPERATOR;

extern const uc_property_t UC_PROPERTY_EMOJI;
extern const uc_property_t UC_PROPERTY_EMOJI_PRESENTATION;
extern const uc_property_t UC_PROPERTY_EMOJI_MODIFIER;
extern const uc_property_t UC_PROPERTY_EMOJI_MODIFIER_BASE;
extern const uc_property_t UC_PROPERTY_EMOJI_COMPONENT;
extern const uc_property_t UC_PROPERTY_EXTENDED_PICTOGRAPHIC;

extern const uc_property_t UC_PROPERTY_ZERO_WIDTH;
extern const uc_property_t UC_PROPERTY_SPACE;
extern const uc_property_t UC_PROPERTY_NON_BREAK;
extern const uc_property_t UC_PROPERTY_ISO_CONTROL;
extern const uc_property_t UC_PROPERTY_FORMAT_CONTROL;
extern const uc_property_t UC_PROPERTY_PREPENDED_CONCATENATION_MARK;
extern const uc_property_t UC_PROPERTY_DASH;
extern const uc_property_t UC_PROPERTY_HYPHEN;
extern const uc_property_t UC_PROPERTY_PUNCTUATION;
extern const uc_property_t UC_PROPERTY_LINE_SEPARATOR;
extern const uc_property_t UC_PROPERTY_PARAGRAPH_SEPARATOR;
extern const uc_property_t UC_PROPERTY_QUOTATION_MARK;
extern const uc_property_t UC_PROPERTY_SENTENCE_TERMINAL;
extern const uc_property_t UC_PROPERTY_TERMINAL_PUNCTUATION;
extern const uc_property_t UC_PROPERTY_CURRENCY_SYMBOL;
extern const uc_property_t UC_PROPERTY_MATH;
extern const uc_property_t UC_PROPERTY_OTHER_MATH;
extern const uc_property_t UC_PROPERTY_PAIRED_PUNCTUATION;
extern const uc_property_t UC_PROPERTY_LEFT_OF_PAIR;
extern const uc_property_t UC_PROPERTY_COMBINING;
extern const uc_property_t UC_PROPERTY_COMPOSITE;
extern const uc_property_t UC_PROPERTY_DECIMAL_DIGIT;
extern const uc_property_t UC_PROPERTY_NUMERIC;
extern const uc_property_t UC_PROPERTY_DIACRITIC;
extern const uc_property_t UC_PROPERTY_EXTENDER;
extern const uc_property_t UC_PROPERTY_IGNORABLE_CONTROL;
extern const uc_property_t UC_PROPERTY_REGIONAL_INDICATOR;


extern uc_property_t
       uc_property_byname (const char *property_name);





extern bool
       uc_is_property (ucs4_t uc, uc_property_t property);
extern bool uc_is_property_white_space (ucs4_t uc)
       ;
extern bool uc_is_property_alphabetic (ucs4_t uc)
       ;
extern bool uc_is_property_other_alphabetic (ucs4_t uc)
       ;
extern bool uc_is_property_not_a_character (ucs4_t uc)
       ;
extern bool uc_is_property_default_ignorable_code_point (ucs4_t uc)
       ;
extern bool uc_is_property_other_default_ignorable_code_point (ucs4_t uc)
       ;
extern bool uc_is_property_deprecated (ucs4_t uc)
       ;
extern bool uc_is_property_logical_order_exception (ucs4_t uc)
       ;
extern bool uc_is_property_variation_selector (ucs4_t uc)
       ;
extern bool uc_is_property_private_use (ucs4_t uc)
       ;
extern bool uc_is_property_unassigned_code_value (ucs4_t uc)
       ;
extern bool uc_is_property_uppercase (ucs4_t uc)
       ;
extern bool uc_is_property_other_uppercase (ucs4_t uc)
       ;
extern bool uc_is_property_lowercase (ucs4_t uc)
       ;
extern bool uc_is_property_other_lowercase (ucs4_t uc)
       ;
extern bool uc_is_property_titlecase (ucs4_t uc)
       ;
extern bool uc_is_property_cased (ucs4_t uc)
       ;
extern bool uc_is_property_case_ignorable (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_lowercased (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_uppercased (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_titlecased (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_casefolded (ucs4_t uc)
       ;
extern bool uc_is_property_changes_when_casemapped (ucs4_t uc)
       ;
extern bool uc_is_property_soft_dotted (ucs4_t uc)
       ;
extern bool uc_is_property_id_start (ucs4_t uc)
       ;
extern bool uc_is_property_other_id_start (ucs4_t uc)
       ;
extern bool uc_is_property_id_continue (ucs4_t uc)
       ;
extern bool uc_is_property_other_id_continue (ucs4_t uc)
       ;
extern bool uc_is_property_xid_start (ucs4_t uc)
       ;
extern bool uc_is_property_xid_continue (ucs4_t uc)
       ;
extern bool uc_is_property_id_compat_math_start (ucs4_t uc)
       ;
extern bool uc_is_property_id_compat_math_continue (ucs4_t uc)
       ;
extern bool uc_is_property_pattern_white_space (ucs4_t uc)
       ;
extern bool uc_is_property_pattern_syntax (ucs4_t uc)
       ;
extern bool uc_is_property_join_control (ucs4_t uc)
       ;
extern bool uc_is_property_grapheme_base (ucs4_t uc)
       ;
extern bool uc_is_property_grapheme_extend (ucs4_t uc)
       ;
extern bool uc_is_property_other_grapheme_extend (ucs4_t uc)
       ;
extern bool uc_is_property_grapheme_link (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_control (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_left_to_right (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_hebrew_right_to_left (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_arabic_right_to_left (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_european_digit (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_eur_num_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_eur_num_terminator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_arabic_digit (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_common_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_block_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_segment_separator (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_whitespace (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_non_spacing_mark (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_boundary_neutral (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_pdf (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_embedding_or_override (ucs4_t uc)
       ;
extern bool uc_is_property_bidi_other_neutral (ucs4_t uc)
       ;
extern bool uc_is_property_hex_digit (ucs4_t uc)
       ;
extern bool uc_is_property_ascii_hex_digit (ucs4_t uc)
       ;
extern bool uc_is_property_ideographic (ucs4_t uc)
       ;
extern bool uc_is_property_unified_ideograph (ucs4_t uc)
       ;
extern bool uc_is_property_radical (ucs4_t uc)
       ;
extern bool uc_is_property_ids_unary_operator (ucs4_t uc)
       ;
extern bool uc_is_property_ids_binary_operator (ucs4_t uc)
       ;
extern bool uc_is_property_ids_trinary_operator (ucs4_t uc)
       ;
extern bool uc_is_property_emoji (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_presentation (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_modifier (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_modifier_base (ucs4_t uc)
       ;
extern bool uc_is_property_emoji_component (ucs4_t uc)
       ;
extern bool uc_is_property_extended_pictographic (ucs4_t uc)
       ;
extern bool uc_is_property_zero_width (ucs4_t uc)
       ;
extern bool uc_is_property_space (ucs4_t uc)
       ;
extern bool uc_is_property_non_break (ucs4_t uc)
       ;
extern bool uc_is_property_iso_control (ucs4_t uc)
       ;
extern bool uc_is_property_format_control (ucs4_t uc)
       ;
extern bool uc_is_property_prepended_concatenation_mark (ucs4_t uc)
       ;
extern bool uc_is_property_dash (ucs4_t uc)
       ;
extern bool uc_is_property_hyphen (ucs4_t uc)
       ;
extern bool uc_is_property_punctuation (ucs4_t uc)
       ;
extern bool uc_is_property_line_separator (ucs4_t uc)
       ;
extern bool uc_is_property_paragraph_separator (ucs4_t uc)
       ;
extern bool uc_is_property_quotation_mark (ucs4_t uc)
       ;
extern bool uc_is_property_sentence_terminal (ucs4_t uc)
       ;
extern bool uc_is_property_terminal_punctuation (ucs4_t uc)
       ;
extern bool uc_is_property_currency_symbol (ucs4_t uc)
       ;
extern bool uc_is_property_math (ucs4_t uc)
       ;
extern bool uc_is_property_other_math (ucs4_t uc)
       ;
extern bool uc_is_property_paired_punctuation (ucs4_t uc)
       ;
extern bool uc_is_property_left_of_pair (ucs4_t uc)
       ;
extern bool uc_is_property_combining (ucs4_t uc)
       ;
extern bool uc_is_property_composite (ucs4_t uc)
       ;
extern bool uc_is_property_decimal_digit (ucs4_t uc)
       ;
extern bool uc_is_property_numeric (ucs4_t uc)
       ;
extern bool uc_is_property_diacritic (ucs4_t uc)
       ;
extern bool uc_is_property_extender (ucs4_t uc)
       ;
extern bool uc_is_property_ignorable_control (ucs4_t uc)
       ;
extern bool uc_is_property_regional_indicator (ucs4_t uc)
       ;
# 934 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
enum
{
  UC_INDIC_CONJUNCT_BREAK_NONE,
  UC_INDIC_CONJUNCT_BREAK_CONSONANT,
  UC_INDIC_CONJUNCT_BREAK_LINKER,
  UC_INDIC_CONJUNCT_BREAK_EXTEND
};


extern const char *
       uc_indic_conjunct_break_name (int indic_conjunct_break)
       ;


extern int
       uc_indic_conjunct_break_byname (const char *indic_conjunct_break_name)
       ;


extern int
       uc_indic_conjunct_break (ucs4_t uc)
       ;





typedef struct
{
  unsigned int code : 21;
  unsigned int start : 1;
  unsigned int end : 1;
}
uc_interval_t;
typedef struct
{
  unsigned int nintervals;
  const uc_interval_t *intervals;
  const char *name;
}
uc_script_t;


extern const uc_script_t *
       uc_script (ucs4_t uc)
       ;


extern const uc_script_t *
       uc_script_byname (const char *script_name)
       ;


extern bool
       uc_is_script (ucs4_t uc, const uc_script_t *script)
       ;


extern void
       uc_all_scripts (const uc_script_t **scripts, size_t *count);





typedef struct
{
  ucs4_t start;
  ucs4_t end;
  const char *name;
}
uc_block_t;


extern const uc_block_t *
       uc_block (ucs4_t uc)
       ;


extern bool
       uc_is_block (ucs4_t uc, const uc_block_t *block)
       ;


extern void
       uc_all_blocks (const uc_block_t **blocks, size_t *count);






extern bool
       uc_is_c_whitespace (ucs4_t uc)
       ;


extern bool
       uc_is_java_whitespace (ucs4_t uc)
       ;

enum
{
  UC_IDENTIFIER_START,
  UC_IDENTIFIER_VALID,
  UC_IDENTIFIER_INVALID,
  UC_IDENTIFIER_IGNORABLE
};



extern int
       uc_c_ident_category (ucs4_t uc)
       ;



extern int
       uc_java_ident_category (ucs4_t uc)
       ;
# 1064 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unictype.h"
extern bool
       uc_is_alnum (ucs4_t uc)
       ;





extern bool
       uc_is_alpha (ucs4_t uc)
       ;


extern bool
       uc_is_cntrl (ucs4_t uc)
       ;


extern bool
       uc_is_digit (ucs4_t uc)
       ;



extern bool
       uc_is_graph (ucs4_t uc)
       ;




extern bool
       uc_is_lower (ucs4_t uc)
       ;


extern bool
       uc_is_print (ucs4_t uc)
       ;



extern bool
       uc_is_punct (ucs4_t uc)
       ;




extern bool
       uc_is_space (ucs4_t uc)
       ;




extern bool
       uc_is_upper (ucs4_t uc)
       ;



extern bool
       uc_is_xdigit (ucs4_t uc)
       ;




extern bool
       uc_is_blank (ucs4_t uc)
       ;
# 36 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h" 2




int
c32isprint (wint_t wc)
{
# 70 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
  if (wc != WEOF)
    return uc_is_print (wc);
  else
    return 0;
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32is-impl.h"
}
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c32isprint.c" 2
