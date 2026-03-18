# 0 "/app/subjects/bzip2/compress.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/bzip2/compress.c"
# 29 "/app/subjects/bzip2/compress.c"
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
# 30 "/app/subjects/bzip2/compress.c" 2







void BZ2_bsInitWrite ( EState* s )
{
   s->bsLive = 0;
   s->bsBuff = 0;
}



static
void bsFinishWrite ( EState* s )
{
   while (s->bsLive > 0) {
      s->zbits[s->numZ] = (UChar)(s->bsBuff >> 24);
      s->numZ++;
      s->bsBuff <<= 8;
      s->bsLive -= 8;
   }
}
# 71 "/app/subjects/bzip2/compress.c"
static

void bsW ( EState* s, Int32 n, UInt32 v )
{
   { while (s->bsLive >= 8) { s->zbits[s->numZ] = (UChar)(s->bsBuff >> 24); s->numZ++; s->bsBuff <<= 8; s->bsLive -= 8; } };
   s->bsBuff |= (v << (32 - s->bsLive - n));
   s->bsLive += n;
}



static
void bsPutUInt32 ( EState* s, UInt32 u )
{
   bsW ( s, 8, (u >> 24) & 0xffL );
   bsW ( s, 8, (u >> 16) & 0xffL );
   bsW ( s, 8, (u >> 8) & 0xffL );
   bsW ( s, 8, u & 0xffL );
}



static
void bsPutUChar ( EState* s, UChar c )
{
   bsW( s, 8, (UInt32)c );
}







static
void makeMaps_e ( EState* s )
{
   Int32 i;
   s->nInUse = 0;
   for (i = 0; i < 256; i++)
      if (s->inUse[i]) {
         s->unseqToSeq[i] = s->nInUse;
         s->nInUse++;
      }
}



static
void generateMTFValues ( EState* s )
{
   UChar yy[256];
   Int32 i, j;
   Int32 zPend;
   Int32 wr;
   Int32 EOB;
# 150 "/app/subjects/bzip2/compress.c"
   UInt32* ptr = s->ptr;
   UChar* block = s->block;
   UInt16* mtfv = s->mtfv;

   makeMaps_e ( s );
   EOB = s->nInUse+1;

   for (i = 0; i <= EOB; i++) s->mtfFreq[i] = 0;

   wr = 0;
   zPend = 0;
   for (i = 0; i < s->nInUse; i++) yy[i] = (UChar) i;

   for (i = 0; i < s->nblock; i++) {
      UChar ll_i;
      ;
      j = ptr[i]-1; if (j < 0) j += s->nblock;
      ll_i = s->unseqToSeq[block[j]];
      ;

      if (yy[0] == ll_i) {
         zPend++;
      } else {

         if (zPend > 0) {
            zPend--;
            while (((Bool)1)) {
               if (zPend & 1) {
                  mtfv[wr] = 1; wr++;
                  s->mtfFreq[1]++;
               } else {
                  mtfv[wr] = 0; wr++;
                  s->mtfFreq[0]++;
               }
               if (zPend < 2) break;
               zPend = (zPend - 2) / 2;
            };
            zPend = 0;
         }
         {
            register UChar rtmp;
            register UChar* ryy_j;
            register UChar rll_i;
            rtmp = yy[1];
            yy[1] = yy[0];
            ryy_j = &(yy[1]);
            rll_i = ll_i;
            while ( rll_i != rtmp ) {
               register UChar rtmp2;
               ryy_j++;
               rtmp2 = rtmp;
               rtmp = *ryy_j;
               *ryy_j = rtmp2;
            };
            yy[0] = rtmp;
            j = ryy_j - &(yy[0]);
            mtfv[wr] = j+1; wr++; s->mtfFreq[j+1]++;
         }

      }
   }

   if (zPend > 0) {
      zPend--;
      while (((Bool)1)) {
         if (zPend & 1) {
            mtfv[wr] = 1; wr++;
            s->mtfFreq[1]++;
         } else {
            mtfv[wr] = 0; wr++;
            s->mtfFreq[0]++;
         }
         if (zPend < 2) break;
         zPend = (zPend - 2) / 2;
      };
      zPend = 0;
   }

   mtfv[wr] = EOB; wr++; s->mtfFreq[EOB]++;

   s->nMTF = wr;
}






static
void sendMTFValues ( EState* s )
{
   Int32 v, t, i, j, gs, ge, totc, bt, bc, iter;
   Int32 nSelectors, alphaSize, minLen, maxLen, selCtr;
   Int32 nGroups, nBytes;
# 256 "/app/subjects/bzip2/compress.c"
   UInt16 cost[6];
   Int32 fave[6];

   UInt16* mtfv = s->mtfv;

   if (s->verbosity >= 3)
      fprintf(stderr,"      %d in block, %d after MTF & 1-2 coding, " "%d+2 syms in use\n",s->nblock,s->nMTF,s->nInUse)

                                               ;

   alphaSize = s->nInUse+2;
   for (t = 0; t < 6; t++)
      for (v = 0; v < alphaSize; v++)
         s->len[t][v] = 15;


   { if (!(s->nMTF > 0)) BZ2_bz__AssertH__fail ( 3001 ); };
   if (s->nMTF < 200) nGroups = 2; else
   if (s->nMTF < 600) nGroups = 3; else
   if (s->nMTF < 1200) nGroups = 4; else
   if (s->nMTF < 2400) nGroups = 5; else
                       nGroups = 6;


   {
      Int32 nPart, remF, tFreq, aFreq;

      nPart = nGroups;
      remF = s->nMTF;
      gs = 0;
      while (nPart > 0) {
         tFreq = remF / nPart;
         ge = gs-1;
         aFreq = 0;
         while (aFreq < tFreq && ge < alphaSize-1) {
            ge++;
            aFreq += s->mtfFreq[ge];
         }

         if (ge > gs
             && nPart != nGroups && nPart != 1
             && ((nGroups-nPart) % 2 == 1)) {
            aFreq -= s->mtfFreq[ge];
            ge--;
         }

         if (s->verbosity >= 3)
            fprintf(stderr,"      initial group %d, [%d .. %d], " "has %d syms (%4.1f%%)\n",nPart,gs,ge,aFreq,(100.0 * (float)aFreq) / (float)(s->nMTF))


                                                                 ;

         for (v = 0; v < alphaSize; v++)
            if (v >= gs && v <= ge)
               s->len[nPart-1][v] = 0; else
               s->len[nPart-1][v] = 15;

         nPart--;
         gs = ge+1;
         remF -= aFreq;
      }
   }




   for (iter = 0; iter < 4; iter++) {

      for (t = 0; t < nGroups; t++) fave[t] = 0;

      for (t = 0; t < nGroups; t++)
         for (v = 0; v < alphaSize; v++)
            s->rfreq[t][v] = 0;





      if (nGroups == 6) {
         for (v = 0; v < alphaSize; v++) {
            s->len_pack[v][0] = (s->len[1][v] << 16) | s->len[0][v];
            s->len_pack[v][1] = (s->len[3][v] << 16) | s->len[2][v];
            s->len_pack[v][2] = (s->len[5][v] << 16) | s->len[4][v];
         }
      }

      nSelectors = 0;
      totc = 0;
      gs = 0;
      while (((Bool)1)) {


         if (gs >= s->nMTF) break;
         ge = gs + 50 - 1;
         if (ge >= s->nMTF) ge = s->nMTF-1;





         for (t = 0; t < nGroups; t++) cost[t] = 0;

         if (nGroups == 6 && 50 == ge-gs+1) {

            register UInt32 cost01, cost23, cost45;
            register UInt16 icv;
            cost01 = cost23 = cost45 = 0;







            icv = mtfv[gs+(0)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(1)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(2)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(3)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(4)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(5)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(6)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(7)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(8)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(9)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(10)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(11)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(12)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(13)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(14)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(15)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(16)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(17)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(18)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(19)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(20)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(21)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(22)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(23)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(24)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(25)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(26)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(27)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(28)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(29)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(30)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(31)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(32)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(33)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(34)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(35)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(36)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(37)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(38)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(39)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(40)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(41)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(42)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(43)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(44)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;
            icv = mtfv[gs+(45)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(46)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(47)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(48)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];; icv = mtfv[gs+(49)]; cost01 += s->len_pack[icv][0]; cost23 += s->len_pack[icv][1]; cost45 += s->len_pack[icv][2];;



            cost[0] = cost01 & 0xffff; cost[1] = cost01 >> 16;
            cost[2] = cost23 & 0xffff; cost[3] = cost23 >> 16;
            cost[4] = cost45 & 0xffff; cost[5] = cost45 >> 16;

         } else {

            for (i = gs; i <= ge; i++) {
               UInt16 icv = mtfv[i];
               for (t = 0; t < nGroups; t++) cost[t] += s->len[t][icv];
            }
         }





         bc = 999999999; bt = -1;
         for (t = 0; t < nGroups; t++)
            if (cost[t] < bc) { bc = cost[t]; bt = t; };
         totc += bc;
         fave[bt]++;
         s->selector[nSelectors] = bt;
         nSelectors++;




         if (nGroups == 6 && 50 == ge-gs+1) {




            s->rfreq[bt][ mtfv[gs+(0)] ]++; s->rfreq[bt][ mtfv[gs+(1)] ]++; s->rfreq[bt][ mtfv[gs+(2)] ]++; s->rfreq[bt][ mtfv[gs+(3)] ]++; s->rfreq[bt][ mtfv[gs+(4)] ]++;
            s->rfreq[bt][ mtfv[gs+(5)] ]++; s->rfreq[bt][ mtfv[gs+(6)] ]++; s->rfreq[bt][ mtfv[gs+(7)] ]++; s->rfreq[bt][ mtfv[gs+(8)] ]++; s->rfreq[bt][ mtfv[gs+(9)] ]++;
            s->rfreq[bt][ mtfv[gs+(10)] ]++; s->rfreq[bt][ mtfv[gs+(11)] ]++; s->rfreq[bt][ mtfv[gs+(12)] ]++; s->rfreq[bt][ mtfv[gs+(13)] ]++; s->rfreq[bt][ mtfv[gs+(14)] ]++;
            s->rfreq[bt][ mtfv[gs+(15)] ]++; s->rfreq[bt][ mtfv[gs+(16)] ]++; s->rfreq[bt][ mtfv[gs+(17)] ]++; s->rfreq[bt][ mtfv[gs+(18)] ]++; s->rfreq[bt][ mtfv[gs+(19)] ]++;
            s->rfreq[bt][ mtfv[gs+(20)] ]++; s->rfreq[bt][ mtfv[gs+(21)] ]++; s->rfreq[bt][ mtfv[gs+(22)] ]++; s->rfreq[bt][ mtfv[gs+(23)] ]++; s->rfreq[bt][ mtfv[gs+(24)] ]++;
            s->rfreq[bt][ mtfv[gs+(25)] ]++; s->rfreq[bt][ mtfv[gs+(26)] ]++; s->rfreq[bt][ mtfv[gs+(27)] ]++; s->rfreq[bt][ mtfv[gs+(28)] ]++; s->rfreq[bt][ mtfv[gs+(29)] ]++;
            s->rfreq[bt][ mtfv[gs+(30)] ]++; s->rfreq[bt][ mtfv[gs+(31)] ]++; s->rfreq[bt][ mtfv[gs+(32)] ]++; s->rfreq[bt][ mtfv[gs+(33)] ]++; s->rfreq[bt][ mtfv[gs+(34)] ]++;
            s->rfreq[bt][ mtfv[gs+(35)] ]++; s->rfreq[bt][ mtfv[gs+(36)] ]++; s->rfreq[bt][ mtfv[gs+(37)] ]++; s->rfreq[bt][ mtfv[gs+(38)] ]++; s->rfreq[bt][ mtfv[gs+(39)] ]++;
            s->rfreq[bt][ mtfv[gs+(40)] ]++; s->rfreq[bt][ mtfv[gs+(41)] ]++; s->rfreq[bt][ mtfv[gs+(42)] ]++; s->rfreq[bt][ mtfv[gs+(43)] ]++; s->rfreq[bt][ mtfv[gs+(44)] ]++;
            s->rfreq[bt][ mtfv[gs+(45)] ]++; s->rfreq[bt][ mtfv[gs+(46)] ]++; s->rfreq[bt][ mtfv[gs+(47)] ]++; s->rfreq[bt][ mtfv[gs+(48)] ]++; s->rfreq[bt][ mtfv[gs+(49)] ]++;



         } else {

            for (i = gs; i <= ge; i++)
               s->rfreq[bt][ mtfv[i] ]++;
         }

         gs = ge+1;
      }
      if (s->verbosity >= 3) {
         fprintf(stderr,"      pass %d: size is %d, grp uses are ",iter+1,totc/8)
                                   ;
         for (t = 0; t < nGroups; t++)
            fprintf(stderr,"%d ",fave[t]);
         fprintf(stderr,"\n");
      }






      for (t = 0; t < nGroups; t++)
         BZ2_hbMakeCodeLengths ( &(s->len[t][0]), &(s->rfreq[t][0]),
                                 alphaSize, 17 );
   }


   { if (!(nGroups < 8)) BZ2_bz__AssertH__fail ( 3002 ); };
   { if (!(nSelectors < 32768 && nSelectors <= (2 + (900000 / 50)))) BZ2_bz__AssertH__fail ( 3003 ); }

                  ;



   {
      UChar pos[6], ll_i, tmp2, tmp;
      for (i = 0; i < nGroups; i++) pos[i] = i;
      for (i = 0; i < nSelectors; i++) {
         ll_i = s->selector[i];
         j = 0;
         tmp = pos[j];
         while ( ll_i != tmp ) {
            j++;
            tmp2 = tmp;
            tmp = pos[j];
            pos[j] = tmp2;
         };
         pos[0] = tmp;
         s->selectorMtf[i] = j;
      }
   };


   for (t = 0; t < nGroups; t++) {
      minLen = 32;
      maxLen = 0;
      for (i = 0; i < alphaSize; i++) {
         if (s->len[t][i] > maxLen) maxLen = s->len[t][i];
         if (s->len[t][i] < minLen) minLen = s->len[t][i];
      }
      { if (!(!(maxLen > 17 ))) BZ2_bz__AssertH__fail ( 3004 ); };
      { if (!(!(minLen < 1))) BZ2_bz__AssertH__fail ( 3005 ); };
      BZ2_hbAssignCodes ( &(s->code[t][0]), &(s->len[t][0]),
                          minLen, maxLen, alphaSize );
   }


   {
      Bool inUse16[16];
      for (i = 0; i < 16; i++) {
          inUse16[i] = ((Bool)0);
          for (j = 0; j < 16; j++)
             if (s->inUse[i * 16 + j]) inUse16[i] = ((Bool)1);
      }

      nBytes = s->numZ;
      for (i = 0; i < 16; i++)
         if (inUse16[i]) bsW(s,1,1); else bsW(s,1,0);

      for (i = 0; i < 16; i++)
         if (inUse16[i])
            for (j = 0; j < 16; j++) {
               if (s->inUse[i * 16 + j]) bsW(s,1,1); else bsW(s,1,0);
            }

      if (s->verbosity >= 3)
         fprintf(stderr,"      bytes: mapping %d, ",s->numZ-nBytes);
   }


   nBytes = s->numZ;
   bsW ( s, 3, nGroups );
   bsW ( s, 15, nSelectors );
   for (i = 0; i < nSelectors; i++) {
      for (j = 0; j < s->selectorMtf[i]; j++) bsW(s,1,1);
      bsW(s,1,0);
   }
   if (s->verbosity >= 3)
      fprintf(stderr,"selectors %d, ",s->numZ-nBytes);


   nBytes = s->numZ;

   for (t = 0; t < nGroups; t++) {
      Int32 curr = s->len[t][0];
      bsW ( s, 5, curr );
      for (i = 0; i < alphaSize; i++) {
         while (curr < s->len[t][i]) { bsW(s,2,2); curr++; };
         while (curr > s->len[t][i]) { bsW(s,2,3); curr--; };
         bsW ( s, 1, 0 );
      }
   }

   if (s->verbosity >= 3)
      fprintf(stderr,"code lengths %d, ",s->numZ-nBytes);


   nBytes = s->numZ;
   selCtr = 0;
   gs = 0;
   while (((Bool)1)) {
      if (gs >= s->nMTF) break;
      ge = gs + 50 - 1;
      if (ge >= s->nMTF) ge = s->nMTF-1;
      { if (!(s->selector[selCtr] < nGroups)) BZ2_bz__AssertH__fail ( 3006 ); };

      if (nGroups == 6 && 50 == ge-gs+1) {

            UInt16 mtfv_i;
            UChar* s_len_sel_selCtr
               = &(s->len[s->selector[selCtr]][0]);
            Int32* s_code_sel_selCtr
               = &(s->code[s->selector[selCtr]][0]);







            mtfv_i = mtfv[gs+(0)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(1)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(2)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(3)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(4)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(5)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(6)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(7)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(8)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(9)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(10)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(11)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(12)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(13)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(14)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(15)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(16)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(17)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(18)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(19)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(20)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(21)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(22)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(23)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(24)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(25)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(26)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(27)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(28)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(29)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(30)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(31)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(32)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(33)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(34)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(35)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(36)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(37)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(38)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(39)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(40)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(41)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(42)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(43)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(44)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );
            mtfv_i = mtfv[gs+(45)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(46)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(47)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(48)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] ); mtfv_i = mtfv[gs+(49)]; bsW ( s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i] );



      } else {

         for (i = gs; i <= ge; i++) {
            bsW ( s,
                  s->len [s->selector[selCtr]] [mtfv[i]],
                  s->code [s->selector[selCtr]] [mtfv[i]] );
         }
      }

      gs = ge+1;
      selCtr++;
   }
   { if (!(selCtr == nSelectors)) BZ2_bz__AssertH__fail ( 3007 ); };

   if (s->verbosity >= 3)
      fprintf(stderr,"codes %d\n",s->numZ-nBytes);
}



void BZ2_compressBlock ( EState* s, Bool is_last_block )
{
   if (s->nblock > 0) {

      { s->blockCRC = ~(s->blockCRC); };
      s->combinedCRC = (s->combinedCRC << 1) | (s->combinedCRC >> 31);
      s->combinedCRC ^= s->blockCRC;
      if (s->blockNo > 1) s->numZ = 0;

      if (s->verbosity >= 2)
         fprintf(stderr,"    block %d: crc = 0x%08x, " "combined CRC = 0x%08x, size = %d\n",s->blockNo,s->blockCRC,s->combinedCRC,s->nblock)

                                                                       ;

      BZ2_blockSort ( s );
   }

   s->zbits = (UChar*) (&((UChar*)s->arr2)[s->nblock]);


   if (s->blockNo == 1) {
      BZ2_bsInitWrite ( s );
      bsPutUChar ( s, 0x42 );
      bsPutUChar ( s, 0x5a );
      bsPutUChar ( s, 0x68 );
      bsPutUChar ( s, (UChar)(0x30 + s->blockSize100k) );
   }

   if (s->nblock > 0) {

      bsPutUChar ( s, 0x31 ); bsPutUChar ( s, 0x41 );
      bsPutUChar ( s, 0x59 ); bsPutUChar ( s, 0x26 );
      bsPutUChar ( s, 0x53 ); bsPutUChar ( s, 0x59 );


      bsPutUInt32 ( s, s->blockCRC );
# 647 "/app/subjects/bzip2/compress.c"
      bsW(s,1,0);

      bsW ( s, 24, s->origPtr );
      generateMTFValues ( s );
      sendMTFValues ( s );
   }



   if (is_last_block) {

      bsPutUChar ( s, 0x17 ); bsPutUChar ( s, 0x72 );
      bsPutUChar ( s, 0x45 ); bsPutUChar ( s, 0x38 );
      bsPutUChar ( s, 0x50 ); bsPutUChar ( s, 0x90 );
      bsPutUInt32 ( s, s->combinedCRC );
      if (s->verbosity >= 2)
         fprintf(stderr,"    final combined CRC = 0x%08x\n   ",s->combinedCRC);
      bsFinishWrite ( s );
   }
}
