# 0 "/app/subjects/bzip2/blocksort.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/bzip2/blocksort.c"
# 22 "/app/subjects/bzip2/blocksort.c"
# 1 "/app/subjects/bzip2/bzlib_private.h" 1
# 25 "/app/subjects/bzip2/bzlib_private.h"
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



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
# 3 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 2
# 26 "/app/subjects/bzip2/bzlib_private.h" 2


# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 29 "/app/subjects/bzip2/bzlib_private.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 30 "/app/subjects/bzip2/bzlib_private.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 31 "/app/subjects/bzip2/bzlib_private.h" 2


# 1 "/app/subjects/bzip2/bzlib.h" 1
# 48 "/app/subjects/bzip2/bzlib.h"
typedef
   struct {
      char *next_in;
      unsigned int avail_in;
      unsigned int total_in_lo32;
      unsigned int total_in_hi32;

      char *next_out;
      unsigned int avail_out;
      unsigned int total_out_lo32;
      unsigned int total_out_hi32;

      void *state;

      void *(*bzalloc)(void *,int,int);
      void (*bzfree)(void *,void *);
      void *opaque;
   }
   bz_stream;
# 75 "/app/subjects/bzip2/bzlib.h"
# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 76 "/app/subjects/bzip2/bzlib.h" 2
# 105 "/app/subjects/bzip2/bzlib.h"
extern int BZ2_bzCompressInit (
      bz_stream* strm,
      int blockSize100k,
      int verbosity,
      int workFactor
   );

extern int BZ2_bzCompress (
      bz_stream* strm,
      int action
   );

extern int BZ2_bzCompressEnd (
      bz_stream* strm
   );

extern int BZ2_bzDecompressInit (
      bz_stream *strm,
      int verbosity,
      int small
   );

extern int BZ2_bzDecompress (
      bz_stream* strm
   );

extern int BZ2_bzDecompressEnd (
      bz_stream *strm
   );
# 142 "/app/subjects/bzip2/bzlib.h"
typedef void BZFILE;

extern BZFILE* BZ2_bzReadOpen (
      int* bzerror,
      FILE* f,
      int verbosity,
      int small,
      void* unused,
      int nUnused
   );

extern void BZ2_bzReadClose (
      int* bzerror,
      BZFILE* b
   );

extern void BZ2_bzReadGetUnused (
      int* bzerror,
      BZFILE* b,
      void** unused,
      int* nUnused
   );

extern int BZ2_bzRead (
      int* bzerror,
      BZFILE* b,
      void* buf,
      int len
   );

extern BZFILE* BZ2_bzWriteOpen (
      int* bzerror,
      FILE* f,
      int blockSize100k,
      int verbosity,
      int workFactor
   );

extern void BZ2_bzWrite (
      int* bzerror,
      BZFILE* b,
      void* buf,
      int len
   );

extern void BZ2_bzWriteClose (
      int* bzerror,
      BZFILE* b,
      int abandon,
      unsigned int* nbytes_in,
      unsigned int* nbytes_out
   );

extern void BZ2_bzWriteClose64 (
      int* bzerror,
      BZFILE* b,
      int abandon,
      unsigned int* nbytes_in_lo32,
      unsigned int* nbytes_in_hi32,
      unsigned int* nbytes_out_lo32,
      unsigned int* nbytes_out_hi32
   );





extern int BZ2_bzBuffToBuffCompress (
      char* dest,
      unsigned int* destLen,
      char* source,
      unsigned int sourceLen,
      int blockSize100k,
      int verbosity,
      int workFactor
   );

extern int BZ2_bzBuffToBuffDecompress (
      char* dest,
      unsigned int* destLen,
      char* source,
      unsigned int sourceLen,
      int small,
      int verbosity
   );
# 238 "/app/subjects/bzip2/bzlib.h"
extern const char * BZ2_bzlibVersion (
      void
   );


extern BZFILE * BZ2_bzopen (
      const char *path,
      const char *mode
   );

extern BZFILE * BZ2_bzdopen (
      int fd,
      const char *mode
   );

extern int BZ2_bzread (
      BZFILE* b,
      void* buf,
      int len
   );

extern int BZ2_bzwrite (
      BZFILE* b,
      void* buf,
      int len
   );

extern int BZ2_bzflush (
      BZFILE* b
   );

extern void BZ2_bzclose (
      BZFILE* b
   );

extern const char * BZ2_bzerror (
      BZFILE *b,
      int *errnum
   );
# 34 "/app/subjects/bzip2/bzlib_private.h" 2





typedef char Char;
typedef unsigned char Bool;
typedef unsigned char UChar;
typedef int Int32;
typedef unsigned int UInt32;
typedef short Int16;
typedef unsigned short UInt16;
# 56 "/app/subjects/bzip2/bzlib_private.h"
extern void BZ2_bz__AssertH__fail ( int errcode );
# 129 "/app/subjects/bzip2/bzlib_private.h"
extern Int32 BZ2_rNums[512];
# 153 "/app/subjects/bzip2/bzlib_private.h"
extern UInt32 BZ2_crc32Table[256];
# 194 "/app/subjects/bzip2/bzlib_private.h"
typedef
   struct {

      bz_stream* strm;



      Int32 mode;
      Int32 state;


      UInt32 avail_in_expect;


      UInt32* arr1;
      UInt32* arr2;
      UInt32* ftab;
      Int32 origPtr;


      UInt32* ptr;
      UChar* block;
      UInt16* mtfv;
      UChar* zbits;


      Int32 workFactor;


      UInt32 state_in_ch;
      Int32 state_in_len;
      Int32 rNToGo; Int32 rTPos;


      Int32 nblock;
      Int32 nblockMAX;
      Int32 numZ;
      Int32 state_out_pos;


      Int32 nInUse;
      Bool inUse[256];
      UChar unseqToSeq[256];


      UInt32 bsBuff;
      Int32 bsLive;


      UInt32 blockCRC;
      UInt32 combinedCRC;


      Int32 verbosity;
      Int32 blockNo;
      Int32 blockSize100k;


      Int32 nMTF;
      Int32 mtfFreq [258];
      UChar selector [(2 + (900000 / 50))];
      UChar selectorMtf[(2 + (900000 / 50))];

      UChar len [6][258];
      Int32 code [6][258];
      Int32 rfreq [6][258];

      UInt32 len_pack[258][4];

   }
   EState;





extern void
BZ2_blockSort ( EState* );

extern void
BZ2_compressBlock ( EState*, Bool );

extern void
BZ2_bsInitWrite ( EState* );

extern void
BZ2_hbAssignCodes ( Int32*, UChar*, Int32, Int32, Int32 );

extern void
BZ2_hbMakeCodeLengths ( UChar*, Int32*, Int32, Int32 );
# 345 "/app/subjects/bzip2/bzlib_private.h"
typedef
   struct {

      bz_stream* strm;


      Int32 state;


      UChar state_out_ch;
      Int32 state_out_len;
      Bool blockRandomised;
      Int32 rNToGo; Int32 rTPos;


      UInt32 bsBuff;
      Int32 bsLive;


      Int32 blockSize100k;
      Bool smallDecompress;
      Int32 currBlockNo;
      Int32 verbosity;


      Int32 origPtr;
      UInt32 tPos;
      Int32 k0;
      Int32 unzftab[256];
      Int32 nblock_used;
      Int32 cftab[257];
      Int32 cftabCopy[257];


      UInt32 *tt;


      UInt16 *ll16;
      UChar *ll4;


      UInt32 storedBlockCRC;
      UInt32 storedCombinedCRC;
      UInt32 calculatedBlockCRC;
      UInt32 calculatedCombinedCRC;


      Int32 nInUse;
      Bool inUse[256];
      Bool inUse16[16];
      UChar seqToUnseq[256];


      UChar mtfa [4096];
      Int32 mtfbase[256 / 16];
      UChar selector [(2 + (900000 / 50))];
      UChar selectorMtf[(2 + (900000 / 50))];
      UChar len [6][258];

      Int32 limit [6][258];
      Int32 base [6][258];
      Int32 perm [6][258];
      Int32 minLens[6];


      Int32 save_i;
      Int32 save_j;
      Int32 save_t;
      Int32 save_alphaSize;
      Int32 save_nGroups;
      Int32 save_nSelectors;
      Int32 save_EOB;
      Int32 save_groupNo;
      Int32 save_groupPos;
      Int32 save_nextSym;
      Int32 save_nblockMAX;
      Int32 save_nblock;
      Int32 save_es;
      Int32 save_N;
      Int32 save_curr;
      Int32 save_zt;
      Int32 save_zn;
      Int32 save_zvec;
      Int32 save_zj;
      Int32 save_gSel;
      Int32 save_gMinlen;
      Int32* save_gLimit;
      Int32* save_gBase;
      Int32* save_gPerm;

   }
   DState;
# 482 "/app/subjects/bzip2/bzlib_private.h"
extern Int32
BZ2_indexIntoF ( Int32, Int32* );

extern Int32
BZ2_decompress ( DState* );

extern void
BZ2_hbCreateDecodeTables ( Int32*, Int32*, Int32*, UChar*,
                           Int32, Int32, Int32 );
# 23 "/app/subjects/bzip2/blocksort.c" 2







static

void fallbackSimpleSort ( UInt32* fmap,
                          UInt32* eclass,
                          Int32 lo,
                          Int32 hi )
{
   Int32 i, j, tmp;
   UInt32 ec_tmp;

   if (lo == hi) return;

   if (hi - lo > 3) {
      for ( i = hi-4; i >= lo; i-- ) {
         tmp = fmap[i];
         ec_tmp = eclass[tmp];
         for ( j = i+4; j <= hi && ec_tmp > eclass[fmap[j]]; j += 4 )
            fmap[j-4] = fmap[j];
         fmap[j-4] = tmp;
      }
   }

   for ( i = hi-1; i >= lo; i-- ) {
      tmp = fmap[i];
      ec_tmp = eclass[tmp];
      for ( j = i+1; j <= hi && ec_tmp > eclass[fmap[j]]; j++ )
         fmap[j-1] = fmap[j];
      fmap[j-1] = tmp;
   }
}
# 92 "/app/subjects/bzip2/blocksort.c"
static
void fallbackQSort3 ( UInt32* fmap,
                      UInt32* eclass,
                      Int32 loSt,
                      Int32 hiSt )
{
   Int32 unLo, unHi, ltLo, gtHi, n, m;
   Int32 sp, lo, hi;
   UInt32 med, r, r3;
   Int32 stackLo[100];
   Int32 stackHi[100];

   r = 0;

   sp = 0;
   { stackLo[sp] = loSt; stackHi[sp] = hiSt; sp++; };

   while (sp > 0) {

      { if (!(sp < 100 - 1)) BZ2_bz__AssertH__fail ( 1004 ); };

      { sp--; lo = stackLo[sp]; hi = stackHi[sp]; };
      if (hi - lo < 10) {
         fallbackSimpleSort ( fmap, eclass, lo, hi );
         continue;
      }
# 126 "/app/subjects/bzip2/blocksort.c"
      r = ((r * 7621) + 1) % 32768;
      r3 = r % 3;
      if (r3 == 0) med = eclass[fmap[lo]]; else
      if (r3 == 1) med = eclass[fmap[(lo+hi)>>1]]; else
                   med = eclass[fmap[hi]];

      unLo = ltLo = lo;
      unHi = gtHi = hi;

      while (1) {
         while (1) {
            if (unLo > unHi) break;
            n = (Int32)eclass[fmap[unLo]] - (Int32)med;
            if (n == 0) {
               { Int32 zztmp = fmap[unLo]; fmap[unLo] = fmap[ltLo]; fmap[ltLo] = zztmp; };
               ltLo++; unLo++;
               continue;
            };
            if (n > 0) break;
            unLo++;
         }
         while (1) {
            if (unLo > unHi) break;
            n = (Int32)eclass[fmap[unHi]] - (Int32)med;
            if (n == 0) {
               { Int32 zztmp = fmap[unHi]; fmap[unHi] = fmap[gtHi]; fmap[gtHi] = zztmp; };
               gtHi--; unHi--;
               continue;
            };
            if (n < 0) break;
            unHi--;
         }
         if (unLo > unHi) break;
         { Int32 zztmp = fmap[unLo]; fmap[unLo] = fmap[unHi]; fmap[unHi] = zztmp; }; unLo++; unHi--;
      }

      ;

      if (gtHi < ltLo) continue;

      n = ((ltLo-lo) < (unLo-ltLo)) ? (ltLo-lo) : (unLo-ltLo); { Int32 yyp1 = (lo); Int32 yyp2 = (unLo-n); Int32 yyn = (n); while (yyn > 0) { { Int32 zztmp = fmap[yyp1]; fmap[yyp1] = fmap[yyp2]; fmap[yyp2] = zztmp; }; yyp1++; yyp2++; yyn--; } };
      m = ((hi-gtHi) < (gtHi-unHi)) ? (hi-gtHi) : (gtHi-unHi); { Int32 yyp1 = (unLo); Int32 yyp2 = (hi-m+1); Int32 yyn = (m); while (yyn > 0) { { Int32 zztmp = fmap[yyp1]; fmap[yyp1] = fmap[yyp2]; fmap[yyp2] = zztmp; }; yyp1++; yyp2++; yyn--; } };

      n = lo + unLo - ltLo - 1;
      m = hi - (gtHi - unHi) + 1;

      if (n - lo > hi - m) {
         { stackLo[sp] = lo; stackHi[sp] = n; sp++; };
         { stackLo[sp] = m; stackHi[sp] = hi; sp++; };
      } else {
         { stackLo[sp] = m; stackHi[sp] = hi; sp++; };
         { stackLo[sp] = lo; stackHi[sp] = n; sp++; };
      }
   }
}
# 211 "/app/subjects/bzip2/blocksort.c"
static
void fallbackSort ( UInt32* fmap,
                    UInt32* eclass,
                    UInt32* bhtab,
                    Int32 nblock,
                    Int32 verb )
{
   Int32 ftab[257];
   Int32 ftabCopy[256];
   Int32 H, i, j, k, l, r, cc, cc1;
   Int32 nNotDone;
   Int32 nBhtab;
   UChar* eclass8 = (UChar*)eclass;





   if (verb >= 4)
      fprintf(stderr,"        bucket sorting ...\n");
   for (i = 0; i < 257; i++) ftab[i] = 0;
   for (i = 0; i < nblock; i++) ftab[eclass8[i]]++;
   for (i = 0; i < 256; i++) ftabCopy[i] = ftab[i];
   for (i = 1; i < 257; i++) ftab[i] += ftab[i-1];

   for (i = 0; i < nblock; i++) {
      j = eclass8[i];
      k = ftab[j] - 1;
      ftab[j] = k;
      fmap[k] = i;
   }

   nBhtab = 2 + (nblock / 32);
   for (i = 0; i < nBhtab; i++) bhtab[i] = 0;
   for (i = 0; i < 256; i++) bhtab[(ftab[i]) >> 5] |= ((UInt32)1 << ((ftab[i]) & 31));
# 254 "/app/subjects/bzip2/blocksort.c"
   for (i = 0; i < 32; i++) {
      bhtab[(nblock + 2*i) >> 5] |= ((UInt32)1 << ((nblock + 2*i) & 31));
      bhtab[(nblock + 2*i + 1) >> 5] &= ~((UInt32)1 << ((nblock + 2*i + 1) & 31));
   }


   H = 1;
   while (1) {

      if (verb >= 4)
         fprintf(stderr,"        depth %6d has ",H);

      j = 0;
      for (i = 0; i < nblock; i++) {
         if ((bhtab[(i) >> 5] & ((UInt32)1 << ((i) & 31)))) j = i;
         k = fmap[i] - H; if (k < 0) k += nblock;
         eclass[k] = j;
      }

      nNotDone = 0;
      r = -1;
      while (1) {


         k = r + 1;
         while ((bhtab[(k) >> 5] & ((UInt32)1 << ((k) & 31))) && ((k) & 0x01f)) k++;
         if ((bhtab[(k) >> 5] & ((UInt32)1 << ((k) & 31)))) {
            while (bhtab[(k) >> 5] == 0xffffffff) k += 32;
            while ((bhtab[(k) >> 5] & ((UInt32)1 << ((k) & 31)))) k++;
         }
         l = k - 1;
         if (l >= nblock) break;
         while (!(bhtab[(k) >> 5] & ((UInt32)1 << ((k) & 31))) && ((k) & 0x01f)) k++;
         if (!(bhtab[(k) >> 5] & ((UInt32)1 << ((k) & 31)))) {
            while (bhtab[(k) >> 5] == 0x00000000) k += 32;
            while (!(bhtab[(k) >> 5] & ((UInt32)1 << ((k) & 31)))) k++;
         }
         r = k - 1;
         if (r >= nblock) break;


         if (r > l) {
            nNotDone += (r - l + 1);
            fallbackQSort3 ( fmap, eclass, l, r );


            cc = -1;
            for (i = l; i <= r; i++) {
               cc1 = eclass[fmap[i]];
               if (cc != cc1) { bhtab[(i) >> 5] |= ((UInt32)1 << ((i) & 31)); cc = cc1; };
            }
         }
      }

      if (verb >= 4)
         fprintf(stderr,"%6d unresolved strings\n",nNotDone);

      H *= 2;
      if (H > nblock || nNotDone == 0) break;
   }






   if (verb >= 4)
      fprintf(stderr,"        reconstructing block ...\n");
   j = 0;
   for (i = 0; i < nblock; i++) {
      while (ftabCopy[j] == 0) j++;
      ftabCopy[j]--;
      eclass8[fmap[i]] = (UChar)j;
   }
   { if (!(j < 256)) BZ2_bz__AssertH__fail ( 1005 ); };
}
# 345 "/app/subjects/bzip2/blocksort.c"
static

Bool mainGtU ( UInt32 i1,
               UInt32 i2,
               UChar* block,
               UInt16* quadrant,
               UInt32 nblock,
               Int32* budget )
{
   Int32 k;
   UChar c1, c2;
   UInt16 s1, s2;

   ;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   c1 = block[i1]; c2 = block[i2];
   if (c1 != c2) return (c1 > c2);
   i1++; i2++;

   k = nblock + 8;

   do {

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      c1 = block[i1]; c2 = block[i2];
      if (c1 != c2) return (c1 > c2);
      s1 = quadrant[i1]; s2 = quadrant[i2];
      if (s1 != s2) return (s1 > s2);
      i1++; i2++;

      if (i1 >= nblock) i1 -= nblock;
      if (i2 >= nblock) i2 -= nblock;

      k -= 8;
      (*budget)--;
   }
      while (k >= 0);

   return ((Bool)0);
}
# 479 "/app/subjects/bzip2/blocksort.c"
static
Int32 incs[14] = { 1, 4, 13, 40, 121, 364, 1093, 3280,
                   9841, 29524, 88573, 265720,
                   797161, 2391484 };

static
void mainSimpleSort ( UInt32* ptr,
                      UChar* block,
                      UInt16* quadrant,
                      Int32 nblock,
                      Int32 lo,
                      Int32 hi,
                      Int32 d,
                      Int32* budget )
{
   Int32 i, j, h, bigN, hp;
   UInt32 v;

   bigN = hi - lo + 1;
   if (bigN < 2) return;

   hp = 0;
   while (incs[hp] < bigN) hp++;
   hp--;

   for (; hp >= 0; hp--) {
      h = incs[hp];

      i = lo + h;
      while (((Bool)1)) {


         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU (
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;


         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU (
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;


         if (i > hi) break;
         v = ptr[i];
         j = i;
         while ( mainGtU (
                    ptr[j-h]+d, v+d, block, quadrant, nblock, budget
                 ) ) {
            ptr[j] = ptr[j-h];
            j = j - h;
            if (j <= (lo + h - 1)) break;
         }
         ptr[j] = v;
         i++;

         if (*budget < 0) return;
      }
   }
}
# 581 "/app/subjects/bzip2/blocksort.c"
static

UChar mmed3 ( UChar a, UChar b, UChar c )
{
   UChar t;
   if (a > b) { t = a; a = b; b = t; };
   if (b > c) {
      b = c;
      if (a > b) b = a;
   }
   return b;
}
# 620 "/app/subjects/bzip2/blocksort.c"
static
void mainQSort3 ( UInt32* ptr,
                  UChar* block,
                  UInt16* quadrant,
                  Int32 nblock,
                  Int32 loSt,
                  Int32 hiSt,
                  Int32 dSt,
                  Int32* budget )
{
   Int32 unLo, unHi, ltLo, gtHi, n, m, med;
   Int32 sp, lo, hi, d;

   Int32 stackLo[100];
   Int32 stackHi[100];
   Int32 stackD [100];

   Int32 nextLo[3];
   Int32 nextHi[3];
   Int32 nextD [3];

   sp = 0;
   { stackLo[sp] = loSt; stackHi[sp] = hiSt; stackD [sp] = dSt; sp++; };

   while (sp > 0) {

      { if (!(sp < 100 - 2)) BZ2_bz__AssertH__fail ( 1001 ); };

      { sp--; lo = stackLo[sp]; hi = stackHi[sp]; d = stackD [sp]; };
      if (hi - lo < 20 ||
          d > (2 + 12)) {
         mainSimpleSort ( ptr, block, quadrant, nblock, lo, hi, d, budget );
         if (*budget < 0) return;
         continue;
      }

      med = (Int32)
            mmed3 ( block[ptr[ lo ]+d],
                    block[ptr[ hi ]+d],
                    block[ptr[ (lo+hi)>>1 ]+d] );

      unLo = ltLo = lo;
      unHi = gtHi = hi;

      while (((Bool)1)) {
         while (((Bool)1)) {
            if (unLo > unHi) break;
            n = ((Int32)block[ptr[unLo]+d]) - med;
            if (n == 0) {
               { Int32 zztmp = ptr[unLo]; ptr[unLo] = ptr[ltLo]; ptr[ltLo] = zztmp; };
               ltLo++; unLo++; continue;
            };
            if (n > 0) break;
            unLo++;
         }
         while (((Bool)1)) {
            if (unLo > unHi) break;
            n = ((Int32)block[ptr[unHi]+d]) - med;
            if (n == 0) {
               { Int32 zztmp = ptr[unHi]; ptr[unHi] = ptr[gtHi]; ptr[gtHi] = zztmp; };
               gtHi--; unHi--; continue;
            };
            if (n < 0) break;
            unHi--;
         }
         if (unLo > unHi) break;
         { Int32 zztmp = ptr[unLo]; ptr[unLo] = ptr[unHi]; ptr[unHi] = zztmp; }; unLo++; unHi--;
      }

      ;

      if (gtHi < ltLo) {
         { stackLo[sp] = lo; stackHi[sp] = hi; stackD [sp] = d+1; sp++; };
         continue;
      }

      n = ((ltLo-lo) < (unLo-ltLo)) ? (ltLo-lo) : (unLo-ltLo); { Int32 yyp1 = (lo); Int32 yyp2 = (unLo-n); Int32 yyn = (n); while (yyn > 0) { { Int32 zztmp = ptr[yyp1]; ptr[yyp1] = ptr[yyp2]; ptr[yyp2] = zztmp; }; yyp1++; yyp2++; yyn--; } };
      m = ((hi-gtHi) < (gtHi-unHi)) ? (hi-gtHi) : (gtHi-unHi); { Int32 yyp1 = (unLo); Int32 yyp2 = (hi-m+1); Int32 yyn = (m); while (yyn > 0) { { Int32 zztmp = ptr[yyp1]; ptr[yyp1] = ptr[yyp2]; ptr[yyp2] = zztmp; }; yyp1++; yyp2++; yyn--; } };

      n = lo + unLo - ltLo - 1;
      m = hi - (gtHi - unHi) + 1;

      nextLo[0] = lo; nextHi[0] = n; nextD[0] = d;
      nextLo[1] = m; nextHi[1] = hi; nextD[1] = d;
      nextLo[2] = n+1; nextHi[2] = m-1; nextD[2] = d+1;

      if ((nextHi[0]-nextLo[0]) < (nextHi[1]-nextLo[1])) { Int32 tz; tz = nextLo[0]; nextLo[0] = nextLo[1]; nextLo[1] = tz; tz = nextHi[0]; nextHi[0] = nextHi[1]; nextHi[1] = tz; tz = nextD [0]; nextD [0] = nextD [1]; nextD [1] = tz; };
      if ((nextHi[1]-nextLo[1]) < (nextHi[2]-nextLo[2])) { Int32 tz; tz = nextLo[1]; nextLo[1] = nextLo[2]; nextLo[2] = tz; tz = nextHi[1]; nextHi[1] = nextHi[2]; nextHi[2] = tz; tz = nextD [1]; nextD [1] = nextD [2]; nextD [2] = tz; };
      if ((nextHi[0]-nextLo[0]) < (nextHi[1]-nextLo[1])) { Int32 tz; tz = nextLo[0]; nextLo[0] = nextLo[1]; nextLo[1] = tz; tz = nextHi[0]; nextHi[0] = nextHi[1]; nextHi[1] = tz; tz = nextD [0]; nextD [0] = nextD [1]; nextD [1] = tz; };

      ;
      ;

      { stackLo[sp] = nextLo[0]; stackHi[sp] = nextHi[0]; stackD [sp] = nextD[0]; sp++; };
      { stackLo[sp] = nextLo[1]; stackHi[sp] = nextHi[1]; stackD [sp] = nextD[1]; sp++; };
      { stackLo[sp] = nextLo[2]; stackHi[sp] = nextHi[2]; stackD [sp] = nextD[2]; sp++; };
   }
}
# 750 "/app/subjects/bzip2/blocksort.c"
static
void mainSort ( UInt32* ptr,
                UChar* block,
                UInt16* quadrant,
                UInt32* ftab,
                Int32 nblock,
                Int32 verb,
                Int32* budget )
{
   Int32 i, j, k, ss, sb;
   Int32 runningOrder[256];
   Bool bigDone[256];
   Int32 copyStart[256];
   Int32 copyEnd [256];
   UChar c1;
   Int32 numQSorted;
   UInt16 s;
   if (verb >= 4) fprintf(stderr,"        main sort initialise ...\n");


   for (i = 65536; i >= 0; i--) ftab[i] = 0;

   j = block[0] << 8;
   i = nblock-1;
   for (; i >= 3; i -= 4) {
      quadrant[i] = 0;
      j = (j >> 8) | ( ((UInt16)block[i]) << 8);
      ftab[j]++;
      quadrant[i-1] = 0;
      j = (j >> 8) | ( ((UInt16)block[i-1]) << 8);
      ftab[j]++;
      quadrant[i-2] = 0;
      j = (j >> 8) | ( ((UInt16)block[i-2]) << 8);
      ftab[j]++;
      quadrant[i-3] = 0;
      j = (j >> 8) | ( ((UInt16)block[i-3]) << 8);
      ftab[j]++;
   }
   for (; i >= 0; i--) {
      quadrant[i] = 0;
      j = (j >> 8) | ( ((UInt16)block[i]) << 8);
      ftab[j]++;
   }


   for (i = 0; i < (2 + 12 + 18 + 2); i++) {
      block [nblock+i] = block[i];
      quadrant[nblock+i] = 0;
   }

   if (verb >= 4) fprintf(stderr,"        bucket sorting ...\n");


   for (i = 1; i <= 65536; i++) ftab[i] += ftab[i-1];

   s = block[0] << 8;
   i = nblock-1;
   for (; i >= 3; i -= 4) {
      s = (s >> 8) | (block[i] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i;
      s = (s >> 8) | (block[i-1] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i-1;
      s = (s >> 8) | (block[i-2] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i-2;
      s = (s >> 8) | (block[i-3] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i-3;
   }
   for (; i >= 0; i--) {
      s = (s >> 8) | (block[i] << 8);
      j = ftab[s] -1;
      ftab[s] = j;
      ptr[j] = i;
   }






   for (i = 0; i <= 255; i++) {
      bigDone [i] = ((Bool)0);
      runningOrder[i] = i;
   }

   {
      Int32 vv;
      Int32 h = 1;
      do h = 3 * h + 1; while (h <= 256);
      do {
         h = h / 3;
         for (i = h; i <= 255; i++) {
            vv = runningOrder[i];
            j = i;
            while ( (ftab[((runningOrder[j-h])+1) << 8] - ftab[(runningOrder[j-h]) << 8]) > (ftab[((vv)+1) << 8] - ftab[(vv) << 8]) ) {
               runningOrder[j] = runningOrder[j-h];
               j = j - h;
               if (j <= (h - 1)) goto zero;
            }
            zero:
            runningOrder[j] = vv;
         }
      } while (h != 1);
   }





   numQSorted = 0;

   for (i = 0; i <= 255; i++) {







      ss = runningOrder[i];
# 886 "/app/subjects/bzip2/blocksort.c"
      for (j = 0; j <= 255; j++) {
         if (j != ss) {
            sb = (ss << 8) + j;
            if ( ! (ftab[sb] & (1 << 21)) ) {
               Int32 lo = ftab[sb] & (~((1 << 21)));
               Int32 hi = (ftab[sb+1] & (~((1 << 21)))) - 1;
               if (hi > lo) {
                  if (verb >= 4)
                     fprintf(stderr,"        qsort [0x%x, 0x%x]   " "done %d   this %d\n",ss,j,numQSorted,hi - lo + 1)

                                                                ;
                  mainQSort3 (
                     ptr, block, quadrant, nblock,
                     lo, hi, 2, budget
                  );
                  numQSorted += (hi - lo + 1);
                  if (*budget < 0) return;
               }
            }
            ftab[sb] |= (1 << 21);
         }
      }

      { if (!(!bigDone[ss])) BZ2_bz__AssertH__fail ( 1006 ); };
# 918 "/app/subjects/bzip2/blocksort.c"
      {
         for (j = 0; j <= 255; j++) {
            copyStart[j] = ftab[(j << 8) + ss] & (~((1 << 21)));
            copyEnd [j] = (ftab[(j << 8) + ss + 1] & (~((1 << 21)))) - 1;
         }
         for (j = ftab[ss << 8] & (~((1 << 21))); j < copyStart[ss]; j++) {
            k = ptr[j]-1; if (k < 0) k += nblock;
            c1 = block[k];
            if (!bigDone[c1])
               ptr[ copyStart[c1]++ ] = k;
         }
         for (j = (ftab[(ss+1) << 8] & (~((1 << 21)))) - 1; j > copyEnd[ss]; j--) {
            k = ptr[j]-1; if (k < 0) k += nblock;
            c1 = block[k];
            if (!bigDone[c1])
               ptr[ copyEnd[c1]-- ] = k;
         }
      }

      { if (!((copyStart[ss]-1 == copyEnd[ss]) || (copyStart[ss] == 0 && copyEnd[ss] == nblock-1))) BZ2_bz__AssertH__fail ( 1007 ); }
# 946 "/app/subjects/bzip2/blocksort.c"
      for (j = 0; j <= 255; j++) ftab[(j << 8) + ss] |= (1 << 21);
# 987 "/app/subjects/bzip2/blocksort.c"
      bigDone[ss] = ((Bool)1);

      if (i < 255) {
         Int32 bbStart = ftab[ss << 8] & (~((1 << 21)));
         Int32 bbSize = (ftab[(ss+1) << 8] & (~((1 << 21)))) - bbStart;
         Int32 shifts = 0;

         while ((bbSize >> shifts) > 65534) shifts++;

         for (j = bbSize-1; j >= 0; j--) {
            Int32 a2update = ptr[bbStart + j];
            UInt16 qVal = (UInt16)(j >> shifts);
            quadrant[a2update] = qVal;
            if (a2update < (2 + 12 + 18 + 2))
               quadrant[a2update + nblock] = qVal;
         }
         { if (!(((bbSize-1) >> shifts) <= 65535)) BZ2_bz__AssertH__fail ( 1002 ); };
      }

   }

   if (verb >= 4)
      fprintf(stderr,"        %d pointers, %d sorted, %d scanned\n",nblock,numQSorted,nblock - numQSorted)
                                                          ;
}
# 1031 "/app/subjects/bzip2/blocksort.c"
void BZ2_blockSort ( EState* s )
{
   UInt32* ptr = s->ptr;
   UChar* block = s->block;
   UInt32* ftab = s->ftab;
   Int32 nblock = s->nblock;
   Int32 verb = s->verbosity;
   Int32 wfact = s->workFactor;
   UInt16* quadrant;
   Int32 budget;
   Int32 budgetInit;
   Int32 i;

   if (nblock < 10000) {
      fallbackSort ( s->arr1, s->arr2, ftab, nblock, verb );
   } else {





      i = nblock+(2 + 12 + 18 + 2);
      if (i & 1) i++;
      quadrant = (UInt16*)(&(block[i]));
# 1063 "/app/subjects/bzip2/blocksort.c"
      if (wfact < 1 ) wfact = 1;
      if (wfact > 100) wfact = 100;
      budgetInit = nblock * ((wfact-1) / 3);
      budget = budgetInit;

      mainSort ( ptr, block, quadrant, ftab, nblock, verb, &budget );
      if (verb >= 3)
         fprintf(stderr,"      %d work, %d block, ratio %5.2f\n",budgetInit - budget,nblock,(float)(budgetInit - budget) / (float)(nblock==0 ? 1 : nblock))



                                                     ;
      if (budget < 0) {
         if (verb >= 2)
            fprintf(stderr,"    too repetitive; using fallback" " sorting algorithm\n")
                                               ;
         fallbackSort ( s->arr1, s->arr2, ftab, nblock, verb );
      }
   }

   s->origPtr = -1;
   for (i = 0; i < s->nblock; i++)
      if (ptr[i] == 0)
         { s->origPtr = i; break; };

   { if (!(s->origPtr != -1)) BZ2_bz__AssertH__fail ( 1003 ); };
}
