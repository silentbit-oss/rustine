# 0 "/app/subjects/bzip2/bzlib.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/bzip2/bzlib.c"
# 31 "/app/subjects/bzip2/bzlib.c"
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
# 32 "/app/subjects/bzip2/bzlib.c" 2
# 1 "/app/subjects/bzip2/bz_version.h" 1
# 33 "/app/subjects/bzip2/bzlib.c" 2
# 42 "/app/subjects/bzip2/bzlib.c"
void BZ2_bz__AssertH__fail ( int errcode )
{
   fprintf(stderr,
      "\n\nbzip2/libbzip2: internal error number %d.\n"
      "This is a bug in bzip2/libbzip2, %s.\n"
      "Please report it at: https://gitlab.com/bzip2/bzip2/-/issues\n"
      "If this happened when you were using some program which uses\n"
      "libbzip2 as a component, you should also report this bug to\n"
      "the author(s) of that program.\n"
      "Please make an effort to report this bug;\n"
      "timely and accurate bug reports eventually lead to higher\n"
      "quality software.  Thanks.\n\n",
      errcode,
      BZ2_bzlibVersion()
   );

   if (errcode == 1007) {
   fprintf(stderr,
      "\n*** A special note about internal error number 1007 ***\n"
      "\n"
      "Experience suggests that a common cause of i.e. 1007\n"
      "is unreliable memory or other hardware.  The 1007 assertion\n"
      "just happens to cross-check the results of huge numbers of\n"
      "memory reads/writes, and so acts (unintendedly) as a stress\n"
      "test of your memory system.\n"
      "\n"
      "I suggest the following: try compressing the file again,\n"
      "possibly monitoring progress in detail with the -vv flag.\n"
      "\n"
      "* If the error cannot be reproduced, and/or happens at different\n"
      "  points in compression, you may have a flaky memory system.\n"
      "  Try a memory-test program.  I have used Memtest86\n"
      "  (www.memtest86.com).  At the time of writing it is free (GPLd).\n"
      "  Memtest86 tests memory much more thorougly than your BIOSs\n"
      "  power-on test, and may find failures that the BIOS doesn't.\n"
      "\n"
      "* If the error can be repeatably reproduced, this is a bug in\n"
      "  bzip2, and I would very much like to hear about it.  Please\n"
      "  let me know, and, ideally, save a copy of the file causing the\n"
      "  problem -- without which I will be unable to investigate it.\n"
      "\n"
   );
   }

   exit(3);
}




static
int bz_config_ok ( void )
{
   if (sizeof(int) != 4) return 0;
   if (sizeof(short) != 2) return 0;
   if (sizeof(char) != 1) return 0;
   return 1;
}



static
void* default_bzalloc ( void* opaque, Int32 items, Int32 size )
{
   void* v = malloc ( items * size );
   return v;
}

static
void default_bzfree ( void* opaque, void* addr )
{
   if (addr != 0) free ( addr );
}



static
void prepare_new_block ( EState* s )
{
   Int32 i;
   s->nblock = 0;
   s->numZ = 0;
   s->state_out_pos = 0;
   { s->blockCRC = 0xffffffffL; };
   for (i = 0; i < 256; i++) s->inUse[i] = ((Bool)0);
   s->blockNo++;
}



static
void init_RL ( EState* s )
{
   s->state_in_ch = 256;
   s->state_in_len = 0;
}


static
Bool isempty_RL ( EState* s )
{
   if (s->state_in_ch < 256 && s->state_in_len > 0)
      return ((Bool)0); else
      return ((Bool)1);
}



int BZ2_bzCompressInit
                    ( bz_stream* strm,
                     int blockSize100k,
                     int verbosity,
                     int workFactor )
{
   Int32 n;
   EState* s;

   if (!bz_config_ok()) return (-9);

   if (strm == 0 ||
       blockSize100k < 1 || blockSize100k > 9 ||
       workFactor < 0 || workFactor > 250)
     return (-2);

   if (workFactor == 0) workFactor = 30;
   if (strm->bzalloc == 0) strm->bzalloc = default_bzalloc;
   if (strm->bzfree == 0) strm->bzfree = default_bzfree;

   s = (strm->bzalloc)(strm->opaque,(sizeof(EState)),1);
   if (s == 0) return (-3);
   s->strm = strm;

   s->arr1 = 0;
   s->arr2 = 0;
   s->ftab = 0;

   n = 100000 * blockSize100k;
   s->arr1 = (strm->bzalloc)(strm->opaque,(n * sizeof(UInt32)),1);
   s->arr2 = (strm->bzalloc)(strm->opaque,((n+(2 + 12 + 18 + 2)) * sizeof(UInt32)),1);
   s->ftab = (strm->bzalloc)(strm->opaque,(65537 * sizeof(UInt32)),1);

   if (s->arr1 == 0 || s->arr2 == 0 || s->ftab == 0) {
      if (s->arr1 != 0) (strm->bzfree)(strm->opaque,(s->arr1));
      if (s->arr2 != 0) (strm->bzfree)(strm->opaque,(s->arr2));
      if (s->ftab != 0) (strm->bzfree)(strm->opaque,(s->ftab));
      if (s != 0) (strm->bzfree)(strm->opaque,(s));
      return (-3);
   }

   s->blockNo = 0;
   s->state = 2;
   s->mode = 2;
   s->combinedCRC = 0;
   s->blockSize100k = blockSize100k;
   s->nblockMAX = 100000 * blockSize100k - 19;
   s->verbosity = verbosity;
   s->workFactor = workFactor;

   s->block = (UChar*)s->arr2;
   s->mtfv = (UInt16*)s->arr1;
   s->zbits = 0;
   s->ptr = (UInt32*)s->arr1;

   strm->state = s;
   strm->total_in_lo32 = 0;
   strm->total_in_hi32 = 0;
   strm->total_out_lo32 = 0;
   strm->total_out_hi32 = 0;
   init_RL ( s );
   prepare_new_block ( s );
   return 0;
}



static
void add_pair_to_block ( EState* s )
{
   Int32 i;
   UChar ch = (UChar)(s->state_in_ch);
   for (i = 0; i < s->state_in_len; i++) {
      { s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar)ch)]; };
   }
   s->inUse[s->state_in_ch] = ((Bool)1);
   switch (s->state_in_len) {
      case 1:
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         break;
      case 2:
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         break;
      case 3:
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         break;
      default:
         s->inUse[s->state_in_len-4] = ((Bool)1);
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = (UChar)ch; s->nblock++;
         s->block[s->nblock] = ((UChar)(s->state_in_len-4));
         s->nblock++;
         break;
   }
}



static
void flush_RL ( EState* s )
{
   if (s->state_in_ch < 256) add_pair_to_block ( s );
   init_RL ( s );
}
# 290 "/app/subjects/bzip2/bzlib.c"
static
Bool copy_input_until_stop ( EState* s )
{
   Bool progress_in = ((Bool)0);

   if (s->mode == 2) {


      while (((Bool)1)) {

         if (s->nblock >= s->nblockMAX) break;

         if (s->strm->avail_in == 0) break;
         progress_in = ((Bool)1);
         { UInt32 zchh = (UInt32)((UInt32)(*((UChar*)(s->strm->next_in)))); if (zchh != s->state_in_ch && s->state_in_len == 1) { UChar ch = (UChar)(s->state_in_ch); { s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar)ch)]; }; s->inUse[s->state_in_ch] = ((Bool)1); s->block[s->nblock] = (UChar)ch; s->nblock++; s->state_in_ch = zchh; } else if (zchh != s->state_in_ch || s->state_in_len == 255) { if (s->state_in_ch < 256) add_pair_to_block ( s ); s->state_in_ch = zchh; s->state_in_len = 1; } else { s->state_in_len++; } };
         s->strm->next_in++;
         s->strm->avail_in--;
         s->strm->total_in_lo32++;
         if (s->strm->total_in_lo32 == 0) s->strm->total_in_hi32++;
      }

   } else {


      while (((Bool)1)) {

         if (s->nblock >= s->nblockMAX) break;

         if (s->strm->avail_in == 0) break;

         if (s->avail_in_expect == 0) break;
         progress_in = ((Bool)1);
         { UInt32 zchh = (UInt32)((UInt32)(*((UChar*)(s->strm->next_in)))); if (zchh != s->state_in_ch && s->state_in_len == 1) { UChar ch = (UChar)(s->state_in_ch); { s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar)ch)]; }; s->inUse[s->state_in_ch] = ((Bool)1); s->block[s->nblock] = (UChar)ch; s->nblock++; s->state_in_ch = zchh; } else if (zchh != s->state_in_ch || s->state_in_len == 255) { if (s->state_in_ch < 256) add_pair_to_block ( s ); s->state_in_ch = zchh; s->state_in_len = 1; } else { s->state_in_len++; } };
         s->strm->next_in++;
         s->strm->avail_in--;
         s->strm->total_in_lo32++;
         if (s->strm->total_in_lo32 == 0) s->strm->total_in_hi32++;
         s->avail_in_expect--;
      }
   }
   return progress_in;
}



static
Bool copy_output_until_stop ( EState* s )
{
   Bool progress_out = ((Bool)0);

   while (((Bool)1)) {


      if (s->strm->avail_out == 0) break;


      if (s->state_out_pos >= s->numZ) break;

      progress_out = ((Bool)1);
      *(s->strm->next_out) = s->zbits[s->state_out_pos];
      s->state_out_pos++;
      s->strm->avail_out--;
      s->strm->next_out++;
      s->strm->total_out_lo32++;
      if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
   }

   return progress_out;
}



static
Bool handle_compress ( bz_stream* strm )
{
   Bool progress_in = ((Bool)0);
   Bool progress_out = ((Bool)0);
   EState* s = strm->state;

   while (((Bool)1)) {

      if (s->state == 1) {
         progress_out |= copy_output_until_stop ( s );
         if (s->state_out_pos < s->numZ) break;
         if (s->mode == 4 &&
             s->avail_in_expect == 0 &&
             isempty_RL(s)) break;
         prepare_new_block ( s );
         s->state = 2;
         if (s->mode == 3 &&
             s->avail_in_expect == 0 &&
             isempty_RL(s)) break;
      }

      if (s->state == 2) {
         progress_in |= copy_input_until_stop ( s );
         if (s->mode != 2 && s->avail_in_expect == 0) {
            flush_RL ( s );
            BZ2_compressBlock ( s, (Bool)(s->mode == 4) );
            s->state = 1;
         }
         else
         if (s->nblock >= s->nblockMAX) {
            BZ2_compressBlock ( s, ((Bool)0) );
            s->state = 1;
         }
         else
         if (s->strm->avail_in == 0) {
            break;
         }
      }

   }

   return progress_in || progress_out;
}



int BZ2_bzCompress ( bz_stream *strm, int action )
{
   Bool progress;
   EState* s;
   if (strm == 0) return (-2);
   s = strm->state;
   if (s == 0) return (-2);
   if (s->strm != strm) return (-2);

   preswitch:
   switch (s->mode) {

      case 1:
         return (-1);

      case 2:
         if (action == 0) {
            progress = handle_compress ( strm );
            return progress ? 1 : (-2);
         }
         else
         if (action == 1) {
            s->avail_in_expect = strm->avail_in;
            s->mode = 3;
            goto preswitch;
         }
         else
         if (action == 2) {
            s->avail_in_expect = strm->avail_in;
            s->mode = 4;
            goto preswitch;
         }
         else
            return (-2);

      case 3:
         if (action != 1) return (-1);
         if (s->avail_in_expect != s->strm->avail_in)
            return (-1);
         progress = handle_compress ( strm );
         if (s->avail_in_expect > 0 || !isempty_RL(s) ||
             s->state_out_pos < s->numZ) return 2;
         s->mode = 2;
         return 1;

      case 4:
         if (action != 2) return (-1);
         if (s->avail_in_expect != s->strm->avail_in)
            return (-1);
         progress = handle_compress ( strm );
         if (!progress) return (-1);
         if (s->avail_in_expect > 0 || !isempty_RL(s) ||
             s->state_out_pos < s->numZ) return 3;
         s->mode = 1;
         return 4;
   }
   return 0;
}



int BZ2_bzCompressEnd ( bz_stream *strm )
{
   EState* s;
   if (strm == 0) return (-2);
   s = strm->state;
   if (s == 0) return (-2);
   if (s->strm != strm) return (-2);

   if (s->arr1 != 0) (strm->bzfree)(strm->opaque,(s->arr1));
   if (s->arr2 != 0) (strm->bzfree)(strm->opaque,(s->arr2));
   if (s->ftab != 0) (strm->bzfree)(strm->opaque,(s->ftab));
   (strm->bzfree)(strm->opaque,(strm->state));

   strm->state = 0;

   return 0;
}







int BZ2_bzDecompressInit
                     ( bz_stream* strm,
                       int verbosity,
                       int small )
{
   DState* s;

   if (!bz_config_ok()) return (-9);

   if (strm == 0) return (-2);
   if (small != 0 && small != 1) return (-2);
   if (verbosity < 0 || verbosity > 4) return (-2);

   if (strm->bzalloc == 0) strm->bzalloc = default_bzalloc;
   if (strm->bzfree == 0) strm->bzfree = default_bzfree;

   s = (strm->bzalloc)(strm->opaque,(sizeof(DState)),1);
   if (s == 0) return (-3);
   s->strm = strm;
   strm->state = s;
   s->state = 10;
   s->bsLive = 0;
   s->bsBuff = 0;
   s->calculatedCombinedCRC = 0;
   strm->total_in_lo32 = 0;
   strm->total_in_hi32 = 0;
   strm->total_out_lo32 = 0;
   strm->total_out_hi32 = 0;
   s->smallDecompress = (Bool)small;
   s->ll4 = 0;
   s->ll16 = 0;
   s->tt = 0;
   s->currBlockNo = 0;
   s->verbosity = verbosity;

   return 0;
}






static
Bool unRLE_obuf_to_output_FAST ( DState* s )
{
   UChar k1;

   if (s->blockRandomised) {

      while (((Bool)1)) {

         while (((Bool)1)) {
            if (s->strm->avail_out == 0) return ((Bool)0);
            if (s->state_out_len == 0) break;
            *( (UChar*)(s->strm->next_out) ) = s->state_out_ch;
            { s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar)s->state_out_ch)]; };
            s->state_out_len--;
            s->strm->next_out++;
            s->strm->avail_out--;
            s->strm->total_out_lo32++;
            if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
         }


         if (s->nblock_used == s->save_nblock+1) return ((Bool)0);


         if (s->nblock_used > s->save_nblock+1)
            return ((Bool)1);

         s->state_out_len = 1;
         s->state_out_ch = s->k0;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->tPos = s->tt[s->tPos]; k1 = (UChar)(s->tPos & 0xff); s->tPos >>= 8;; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         s->state_out_len = 2;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->tPos = s->tt[s->tPos]; k1 = (UChar)(s->tPos & 0xff); s->tPos >>= 8;; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         s->state_out_len = 3;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->tPos = s->tt[s->tPos]; k1 = (UChar)(s->tPos & 0xff); s->tPos >>= 8;; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->tPos = s->tt[s->tPos]; k1 = (UChar)(s->tPos & 0xff); s->tPos >>= 8;; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         s->state_out_len = ((Int32)k1) + 4;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->tPos = s->tt[s->tPos]; s->k0 = (UChar)(s->tPos & 0xff); s->tPos >>= 8;; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         s->k0 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
      }

   } else {


      UInt32 c_calculatedBlockCRC = s->calculatedBlockCRC;
      UChar c_state_out_ch = s->state_out_ch;
      Int32 c_state_out_len = s->state_out_len;
      Int32 c_nblock_used = s->nblock_used;
      Int32 c_k0 = s->k0;
      UInt32* c_tt = s->tt;
      UInt32 c_tPos = s->tPos;
      char* cs_next_out = s->strm->next_out;
      unsigned int cs_avail_out = s->strm->avail_out;
      Int32 ro_blockSize100k = s->blockSize100k;


      UInt32 avail_out_INIT = cs_avail_out;
      Int32 s_save_nblockPP = s->save_nblock+1;
      unsigned int total_out_lo32_old;

      while (((Bool)1)) {


         if (c_state_out_len > 0) {
            while (((Bool)1)) {
               if (cs_avail_out == 0) goto return_notr;
               if (c_state_out_len == 1) break;
               *( (UChar*)(cs_next_out) ) = c_state_out_ch;
               { c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ BZ2_crc32Table[(c_calculatedBlockCRC >> 24) ^ ((UChar)c_state_out_ch)]; };
               c_state_out_len--;
               cs_next_out++;
               cs_avail_out--;
            }
            s_state_out_len_eq_one:
            {
               if (cs_avail_out == 0) {
                  c_state_out_len = 1; goto return_notr;
               };
               *( (UChar*)(cs_next_out) ) = c_state_out_ch;
               { c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ BZ2_crc32Table[(c_calculatedBlockCRC >> 24) ^ ((UChar)c_state_out_ch)]; };
               cs_next_out++;
               cs_avail_out--;
            }
         }

         if (c_nblock_used > s_save_nblockPP)
            return ((Bool)1);


         if (c_nblock_used == s_save_nblockPP) {
            c_state_out_len = 0; goto return_notr;
         };
         c_state_out_ch = c_k0;
         if (c_tPos >= (UInt32)100000 * (UInt32)ro_blockSize100k) return ((Bool)1); c_tPos = c_tt[c_tPos]; k1 = (UChar)(c_tPos & 0xff); c_tPos >>= 8;; c_nblock_used++;
         if (k1 != c_k0) {
            c_k0 = k1; goto s_state_out_len_eq_one;
         };
         if (c_nblock_used == s_save_nblockPP)
            goto s_state_out_len_eq_one;

         c_state_out_len = 2;
         if (c_tPos >= (UInt32)100000 * (UInt32)ro_blockSize100k) return ((Bool)1); c_tPos = c_tt[c_tPos]; k1 = (UChar)(c_tPos & 0xff); c_tPos >>= 8;; c_nblock_used++;
         if (c_nblock_used == s_save_nblockPP) continue;
         if (k1 != c_k0) { c_k0 = k1; continue; };

         c_state_out_len = 3;
         if (c_tPos >= (UInt32)100000 * (UInt32)ro_blockSize100k) return ((Bool)1); c_tPos = c_tt[c_tPos]; k1 = (UChar)(c_tPos & 0xff); c_tPos >>= 8;; c_nblock_used++;
         if (c_nblock_used == s_save_nblockPP) continue;
         if (k1 != c_k0) { c_k0 = k1; continue; };

         if (c_tPos >= (UInt32)100000 * (UInt32)ro_blockSize100k) return ((Bool)1); c_tPos = c_tt[c_tPos]; k1 = (UChar)(c_tPos & 0xff); c_tPos >>= 8;; c_nblock_used++;
         c_state_out_len = ((Int32)k1) + 4;
         if (c_tPos >= (UInt32)100000 * (UInt32)ro_blockSize100k) return ((Bool)1); c_tPos = c_tt[c_tPos]; c_k0 = (UChar)(c_tPos & 0xff); c_tPos >>= 8;; c_nblock_used++;
      }

      return_notr:
      total_out_lo32_old = s->strm->total_out_lo32;
      s->strm->total_out_lo32 += (avail_out_INIT - cs_avail_out);
      if (s->strm->total_out_lo32 < total_out_lo32_old)
         s->strm->total_out_hi32++;


      s->calculatedBlockCRC = c_calculatedBlockCRC;
      s->state_out_ch = c_state_out_ch;
      s->state_out_len = c_state_out_len;
      s->nblock_used = c_nblock_used;
      s->k0 = c_k0;
      s->tt = c_tt;
      s->tPos = c_tPos;
      s->strm->next_out = cs_next_out;
      s->strm->avail_out = cs_avail_out;

   }
   return ((Bool)0);
}




 Int32 BZ2_indexIntoF ( Int32 indx, Int32 *cftab )
{
   Int32 nb, na, mid;
   nb = 0;
   na = 256;
   do {
      mid = (nb + na) >> 1;
      if (indx >= cftab[mid]) nb = mid; else na = mid;
   }
   while (na - nb != 1);
   return nb;
}






static
Bool unRLE_obuf_to_output_SMALL ( DState* s )
{
   UChar k1;

   if (s->blockRandomised) {

      while (((Bool)1)) {

         while (((Bool)1)) {
            if (s->strm->avail_out == 0) return ((Bool)0);
            if (s->state_out_len == 0) break;
            *( (UChar*)(s->strm->next_out) ) = s->state_out_ch;
            { s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar)s->state_out_ch)]; };
            s->state_out_len--;
            s->strm->next_out++;
            s->strm->avail_out--;
            s->strm->total_out_lo32++;
            if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
         }


         if (s->nblock_used == s->save_nblock+1) return ((Bool)0);


         if (s->nblock_used > s->save_nblock+1)
            return ((Bool)1);

         s->state_out_len = 1;
         s->state_out_ch = s->k0;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         s->state_out_len = 2;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         s->state_out_len = 3;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         k1 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
         s->state_out_len = ((Int32)k1) + 4;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->k0 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; if (s->rNToGo == 0) { s->rNToGo = BZ2_rNums[s->rTPos]; s->rTPos++; if (s->rTPos == 512) s->rTPos = 0; } s->rNToGo--;;
         s->k0 ^= ((s->rNToGo == 1) ? 1 : 0); s->nblock_used++;
      }

   } else {

      while (((Bool)1)) {

         while (((Bool)1)) {
            if (s->strm->avail_out == 0) return ((Bool)0);
            if (s->state_out_len == 0) break;
            *( (UChar*)(s->strm->next_out) ) = s->state_out_ch;
            { s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar)s->state_out_ch)]; };
            s->state_out_len--;
            s->strm->next_out++;
            s->strm->avail_out--;
            s->strm->total_out_lo32++;
            if (s->strm->total_out_lo32 == 0) s->strm->total_out_hi32++;
         }


         if (s->nblock_used == s->save_nblock+1) return ((Bool)0);


         if (s->nblock_used > s->save_nblock+1)
            return ((Bool)1);

         s->state_out_len = 1;
         s->state_out_ch = s->k0;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         s->state_out_len = 2;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         s->state_out_len = 3;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; s->nblock_used++;
         if (s->nblock_used == s->save_nblock+1) continue;
         if (k1 != s->k0) { s->k0 = k1; continue; };

         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); k1 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; s->nblock_used++;
         s->state_out_len = ((Int32)k1) + 4;
         if (s->tPos >= (UInt32)100000 * (UInt32)s->blockSize100k) return ((Bool)1); s->k0 = BZ2_indexIntoF ( s->tPos, s->cftab ); s->tPos = (((UInt32)s->ll16[s->tPos]) | (((((UInt32)(s->ll4[(s->tPos) >> 1])) >> (((s->tPos) << 2) & 0x4)) & 0xF) << 16));; s->nblock_used++;
      }

   }
}



int BZ2_bzDecompress ( bz_stream *strm )
{
   Bool corrupt;
   DState* s;
   if (strm == 0) return (-2);
   s = strm->state;
   if (s == 0) return (-2);
   if (s->strm != strm) return (-2);

   while (((Bool)1)) {
      if (s->state == 1) return (-1);
      if (s->state == 2) {
         if (s->smallDecompress)
            corrupt = unRLE_obuf_to_output_SMALL ( s ); else
            corrupt = unRLE_obuf_to_output_FAST ( s );
         if (corrupt) return (-4);
         if (s->nblock_used == s->save_nblock+1 && s->state_out_len == 0) {
            { s->calculatedBlockCRC = ~(s->calculatedBlockCRC); };
            if (s->verbosity >= 3)
               fprintf(stderr," {0x%08x, 0x%08x}",s->storedBlockCRC,s->calculatedBlockCRC)
                                                 ;
            if (s->verbosity >= 2) fprintf(stderr,"]");
            if (s->calculatedBlockCRC != s->storedBlockCRC)
               return (-4);
            s->calculatedCombinedCRC
               = (s->calculatedCombinedCRC << 1) |
                    (s->calculatedCombinedCRC >> 31);
            s->calculatedCombinedCRC ^= s->calculatedBlockCRC;
            s->state = 14;
         } else {
            return 0;
         }
      }
      if (s->state >= 10) {
         Int32 r = BZ2_decompress ( s );
         if (r == 4) {
            if (s->verbosity >= 3)
               fprintf(stderr,"\n    combined CRCs: stored = 0x%08x, computed = 0x%08x",s->storedCombinedCRC,s->calculatedCombinedCRC)
                                                                          ;
            if (s->calculatedCombinedCRC != s->storedCombinedCRC)
               return (-4);
            return r;
         }
         if (s->state != 2) return r;
      }
   }

   { if (!(0)) BZ2_bz__AssertH__fail ( 6001 ); };

   return 0;
}



int BZ2_bzDecompressEnd ( bz_stream *strm )
{
   DState* s;
   if (strm == 0) return (-2);
   s = strm->state;
   if (s == 0) return (-2);
   if (s->strm != strm) return (-2);

   if (s->tt != 0) (strm->bzfree)(strm->opaque,(s->tt));
   if (s->ll16 != 0) (strm->bzfree)(strm->opaque,(s->ll16));
   if (s->ll4 != 0) (strm->bzfree)(strm->opaque,(s->ll4));

   (strm->bzfree)(strm->opaque,(strm->state));
   strm->state = 0;

   return 0;
}
# 894 "/app/subjects/bzip2/bzlib.c"
typedef
   struct {
      FILE* handle;
      Char buf[5000];
      Int32 bufN;
      Bool writing;
      bz_stream strm;
      Int32 lastErr;
      Bool initialisedOk;
   }
   bzFile;



static Bool myfeof ( FILE* f )
{
   Int32 c = fgetc ( f );
   if (c == EOF) return ((Bool)1);
   ungetc ( c, f );
   return ((Bool)0);
}



BZFILE* BZ2_bzWriteOpen
                    ( int* bzerror,
                      FILE* f,
                      int blockSize100k,
                      int verbosity,
                      int workFactor )
{
   Int32 ret;
   bzFile* bzf = 0;

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };

   if (f == 0 ||
       (blockSize100k < 1 || blockSize100k > 9) ||
       (workFactor < 0 || workFactor > 250) ||
       (verbosity < 0 || verbosity > 4))
      { { if (bzerror != 0) *bzerror = (-2); if (bzf != 0) bzf->lastErr = (-2); }; return 0; };

   if (ferror(f))
      { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return 0; };

   bzf = malloc ( sizeof(bzFile) );
   if (bzf == 0)
      { { if (bzerror != 0) *bzerror = (-3); if (bzf != 0) bzf->lastErr = (-3); }; return 0; };

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };
   bzf->initialisedOk = ((Bool)0);
   bzf->bufN = 0;
   bzf->handle = f;
   bzf->writing = ((Bool)1);
   bzf->strm.bzalloc = 0;
   bzf->strm.bzfree = 0;
   bzf->strm.opaque = 0;

   if (workFactor == 0) workFactor = 30;
   ret = BZ2_bzCompressInit ( &(bzf->strm), blockSize100k,
                              verbosity, workFactor );
   if (ret != 0)
      { { if (bzerror != 0) *bzerror = ret; if (bzf != 0) bzf->lastErr = ret; }; free(bzf); return 0; };

   bzf->strm.avail_in = 0;
   bzf->initialisedOk = ((Bool)1);
   return bzf;
}




void BZ2_bzWrite
             ( int* bzerror,
               BZFILE* b,
               void* buf,
               int len )
{
   Int32 n, n2, ret;
   bzFile* bzf = (bzFile*)b;

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };
   if (bzf == 0 || buf == 0 || len < 0)
      { { if (bzerror != 0) *bzerror = (-2); if (bzf != 0) bzf->lastErr = (-2); }; return; };
   if (!(bzf->writing))
      { { if (bzerror != 0) *bzerror = (-1); if (bzf != 0) bzf->lastErr = (-1); }; return; };
   if (ferror(bzf->handle))
      { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return; };

   if (len == 0)
      { { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; }; return; };

   bzf->strm.avail_in = len;
   bzf->strm.next_in = buf;

   while (((Bool)1)) {
      bzf->strm.avail_out = 5000;
      bzf->strm.next_out = bzf->buf;
      ret = BZ2_bzCompress ( &(bzf->strm), 0 );
      if (ret != 1)
         { { if (bzerror != 0) *bzerror = ret; if (bzf != 0) bzf->lastErr = ret; }; return; };

      if (bzf->strm.avail_out < 5000) {
         n = 5000 - bzf->strm.avail_out;
         n2 = fwrite ( (void*)(bzf->buf), sizeof(UChar),
                       n, bzf->handle );
         if (n != n2 || ferror(bzf->handle))
            { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return; };
      }

      if (bzf->strm.avail_in == 0)
         { { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; }; return; };
   }
}



void BZ2_bzWriteClose
                  ( int* bzerror,
                    BZFILE* b,
                    int abandon,
                    unsigned int* nbytes_in,
                    unsigned int* nbytes_out )
{
   BZ2_bzWriteClose64 ( bzerror, b, abandon,
                        nbytes_in, 0, nbytes_out, 0 );
}


void BZ2_bzWriteClose64
                  ( int* bzerror,
                    BZFILE* b,
                    int abandon,
                    unsigned int* nbytes_in_lo32,
                    unsigned int* nbytes_in_hi32,
                    unsigned int* nbytes_out_lo32,
                    unsigned int* nbytes_out_hi32 )
{
   Int32 n, n2, ret;
   bzFile* bzf = (bzFile*)b;

   if (bzf == 0)
      { { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; }; return; };
   if (!(bzf->writing))
      { { if (bzerror != 0) *bzerror = (-1); if (bzf != 0) bzf->lastErr = (-1); }; return; };
   if (ferror(bzf->handle))
      { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return; };

   if (nbytes_in_lo32 != 0) *nbytes_in_lo32 = 0;
   if (nbytes_in_hi32 != 0) *nbytes_in_hi32 = 0;
   if (nbytes_out_lo32 != 0) *nbytes_out_lo32 = 0;
   if (nbytes_out_hi32 != 0) *nbytes_out_hi32 = 0;

   if ((!abandon) && bzf->lastErr == 0) {
      while (((Bool)1)) {
         bzf->strm.avail_out = 5000;
         bzf->strm.next_out = bzf->buf;
         ret = BZ2_bzCompress ( &(bzf->strm), 2 );
         if (ret != 3 && ret != 4)
            { { if (bzerror != 0) *bzerror = ret; if (bzf != 0) bzf->lastErr = ret; }; return; };

         if (bzf->strm.avail_out < 5000) {
            n = 5000 - bzf->strm.avail_out;
            n2 = fwrite ( (void*)(bzf->buf), sizeof(UChar),
                          n, bzf->handle );
            if (n != n2 || ferror(bzf->handle))
               { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return; };
         }

         if (ret == 4) break;
      }
   }

   if ( !abandon && !ferror ( bzf->handle ) ) {
      fflush ( bzf->handle );
      if (ferror(bzf->handle))
         { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return; };
   }

   if (nbytes_in_lo32 != 0)
      *nbytes_in_lo32 = bzf->strm.total_in_lo32;
   if (nbytes_in_hi32 != 0)
      *nbytes_in_hi32 = bzf->strm.total_in_hi32;
   if (nbytes_out_lo32 != 0)
      *nbytes_out_lo32 = bzf->strm.total_out_lo32;
   if (nbytes_out_hi32 != 0)
      *nbytes_out_hi32 = bzf->strm.total_out_hi32;

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };
   BZ2_bzCompressEnd ( &(bzf->strm) );
   free ( bzf );
}



BZFILE* BZ2_bzReadOpen
                   ( int* bzerror,
                     FILE* f,
                     int verbosity,
                     int small,
                     void* unused,
                     int nUnused )
{
   bzFile* bzf = 0;
   int ret;

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };

   if (f == 0 ||
       (small != 0 && small != 1) ||
       (verbosity < 0 || verbosity > 4) ||
       (unused == 0 && nUnused != 0) ||
       (unused != 0 && (nUnused < 0 || nUnused > 5000)))
      { { if (bzerror != 0) *bzerror = (-2); if (bzf != 0) bzf->lastErr = (-2); }; return 0; };

   if (ferror(f))
      { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return 0; };

   bzf = malloc ( sizeof(bzFile) );
   if (bzf == 0)
      { { if (bzerror != 0) *bzerror = (-3); if (bzf != 0) bzf->lastErr = (-3); }; return 0; };

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };

   bzf->initialisedOk = ((Bool)0);
   bzf->handle = f;
   bzf->bufN = 0;
   bzf->writing = ((Bool)0);
   bzf->strm.bzalloc = 0;
   bzf->strm.bzfree = 0;
   bzf->strm.opaque = 0;

   while (nUnused > 0) {
      bzf->buf[bzf->bufN] = *((UChar*)(unused)); bzf->bufN++;
      unused = ((void*)( 1 + ((UChar*)(unused)) ));
      nUnused--;
   }

   ret = BZ2_bzDecompressInit ( &(bzf->strm), verbosity, small );
   if (ret != 0)
      { { if (bzerror != 0) *bzerror = ret; if (bzf != 0) bzf->lastErr = ret; }; free(bzf); return 0; };

   bzf->strm.avail_in = bzf->bufN;
   bzf->strm.next_in = bzf->buf;

   bzf->initialisedOk = ((Bool)1);
   return bzf;
}



void BZ2_bzReadClose ( int *bzerror, BZFILE *b )
{
   bzFile* bzf = (bzFile*)b;

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };
   if (bzf == 0)
      { { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; }; return; };

   if (bzf->writing)
      { { if (bzerror != 0) *bzerror = (-1); if (bzf != 0) bzf->lastErr = (-1); }; return; };

   if (bzf->initialisedOk)
      (void)BZ2_bzDecompressEnd ( &(bzf->strm) );
   free ( bzf );
}



int BZ2_bzRead
           ( int* bzerror,
             BZFILE* b,
             void* buf,
             int len )
{
   Int32 n, ret;
   bzFile* bzf = (bzFile*)b;

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };

   if (bzf == 0 || buf == 0 || len < 0)
      { { if (bzerror != 0) *bzerror = (-2); if (bzf != 0) bzf->lastErr = (-2); }; return 0; };

   if (bzf->writing)
      { { if (bzerror != 0) *bzerror = (-1); if (bzf != 0) bzf->lastErr = (-1); }; return 0; };

   if (len == 0)
      { { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; }; return 0; };

   bzf->strm.avail_out = len;
   bzf->strm.next_out = buf;

   while (((Bool)1)) {

      if (ferror(bzf->handle))
         { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return 0; };

      if (bzf->strm.avail_in == 0 && !myfeof(bzf->handle)) {
         n = fread ( bzf->buf, sizeof(UChar),
                     5000, bzf->handle );
         if (ferror(bzf->handle))
            { { if (bzerror != 0) *bzerror = (-6); if (bzf != 0) bzf->lastErr = (-6); }; return 0; };
         bzf->bufN = n;
         bzf->strm.avail_in = bzf->bufN;
         bzf->strm.next_in = bzf->buf;
      }

      ret = BZ2_bzDecompress ( &(bzf->strm) );

      if (ret != 0 && ret != 4)
         { { if (bzerror != 0) *bzerror = ret; if (bzf != 0) bzf->lastErr = ret; }; return 0; };

      if (ret == 0 && myfeof(bzf->handle) &&
          bzf->strm.avail_in == 0 && bzf->strm.avail_out > 0)
         { { if (bzerror != 0) *bzerror = (-7); if (bzf != 0) bzf->lastErr = (-7); }; return 0; };

      if (ret == 4)
         { { if (bzerror != 0) *bzerror = 4; if (bzf != 0) bzf->lastErr = 4; };
           return len - bzf->strm.avail_out; };
      if (bzf->strm.avail_out == 0)
         { { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; }; return len; };

   }

   return 0;
}



void BZ2_bzReadGetUnused
                     ( int* bzerror,
                       BZFILE* b,
                       void** unused,
                       int* nUnused )
{
   bzFile* bzf = (bzFile*)b;
   if (bzf == 0)
      { { if (bzerror != 0) *bzerror = (-2); if (bzf != 0) bzf->lastErr = (-2); }; return; };
   if (bzf->lastErr != 4)
      { { if (bzerror != 0) *bzerror = (-1); if (bzf != 0) bzf->lastErr = (-1); }; return; };
   if (unused == 0 || nUnused == 0)
      { { if (bzerror != 0) *bzerror = (-2); if (bzf != 0) bzf->lastErr = (-2); }; return; };

   { if (bzerror != 0) *bzerror = 0; if (bzf != 0) bzf->lastErr = 0; };
   *nUnused = bzf->strm.avail_in;
   *unused = bzf->strm.next_in;
}
# 1249 "/app/subjects/bzip2/bzlib.c"
int BZ2_bzBuffToBuffCompress
                         ( char* dest,
                           unsigned int* destLen,
                           char* source,
                           unsigned int sourceLen,
                           int blockSize100k,
                           int verbosity,
                           int workFactor )
{
   bz_stream strm;
   int ret;

   if (dest == 0 || destLen == 0 ||
       source == 0 ||
       blockSize100k < 1 || blockSize100k > 9 ||
       verbosity < 0 || verbosity > 4 ||
       workFactor < 0 || workFactor > 250)
      return (-2);

   if (workFactor == 0) workFactor = 30;
   strm.bzalloc = 0;
   strm.bzfree = 0;
   strm.opaque = 0;
   ret = BZ2_bzCompressInit ( &strm, blockSize100k,
                              verbosity, workFactor );
   if (ret != 0) return ret;

   strm.next_in = source;
   strm.next_out = dest;
   strm.avail_in = sourceLen;
   strm.avail_out = *destLen;

   ret = BZ2_bzCompress ( &strm, 2 );
   if (ret == 3) goto output_overflow;
   if (ret != 4) goto errhandler;


   *destLen -= strm.avail_out;
   BZ2_bzCompressEnd ( &strm );
   return 0;

   output_overflow:
   BZ2_bzCompressEnd ( &strm );
   return (-8);

   errhandler:
   BZ2_bzCompressEnd ( &strm );
   return ret;
}



int BZ2_bzBuffToBuffDecompress
                           ( char* dest,
                             unsigned int* destLen,
                             char* source,
                             unsigned int sourceLen,
                             int small,
                             int verbosity )
{
   bz_stream strm;
   int ret;

   if (dest == 0 || destLen == 0 ||
       source == 0 ||
       (small != 0 && small != 1) ||
       verbosity < 0 || verbosity > 4)
          return (-2);

   strm.bzalloc = 0;
   strm.bzfree = 0;
   strm.opaque = 0;
   ret = BZ2_bzDecompressInit ( &strm, verbosity, small );
   if (ret != 0) return ret;

   strm.next_in = source;
   strm.next_out = dest;
   strm.avail_in = sourceLen;
   strm.avail_out = *destLen;

   ret = BZ2_bzDecompress ( &strm );
   if (ret == 0) goto output_overflow_or_eof;
   if (ret != 4) goto errhandler;


   *destLen -= strm.avail_out;
   BZ2_bzDecompressEnd ( &strm );
   return 0;

   output_overflow_or_eof:
   if (strm.avail_out > 0) {
      BZ2_bzDecompressEnd ( &strm );
      return (-7);
   } else {
      BZ2_bzDecompressEnd ( &strm );
      return (-8);
   };

   errhandler:
   BZ2_bzDecompressEnd ( &strm );
   return ret;
}
# 1368 "/app/subjects/bzip2/bzlib.c"
const char * BZ2_bzlibVersion(void)
{
   return "1.1.0";
}
# 1384 "/app/subjects/bzip2/bzlib.c"
static
BZFILE * bzopen_or_bzdopen
               ( const char *path,
                 int fd,
                 const char *mode,
                 int open_mode)
{
   int bzerr;
   char unused[5000];
   int blockSize100k = 9;
   int writing = 0;
   char mode2[10] = "";
   FILE *fp = 0;
   BZFILE *bzfp = 0;
   int verbosity = 0;
   int workFactor = 30;
   int smallMode = 0;
   int nUnused = 0;

   if (mode == 0) return 0;
   while (*mode) {
      switch (*mode) {
      case 'r':
         writing = 0; break;
      case 'w':
         writing = 1; break;
      case 's':
         smallMode = 1; break;
      default:
         if (isdigit((int)(*mode))) {
            blockSize100k = *mode-0x30;
         }
      }
      mode++;
   }

   strcat(mode2, writing ? "wb" : "rb" );



   if(open_mode == 0) {
      strcat (mode2, writing ? "e" : "e" );
   }

   if (open_mode==0) {
      if (path==0 || strcmp(path,"")==0) {
        fp = (writing ? stdout : stdin);
        ;
      } else {
        fp = fopen(path,mode2);
      }
   } else {



      fp = fdopen(fd,mode2);

   }
   if (fp == 0) return 0;

   if (writing) {

      if (blockSize100k < 1) blockSize100k = 1;
      if (blockSize100k > 9) blockSize100k = 9;
      bzfp = BZ2_bzWriteOpen(&bzerr,fp,blockSize100k,
                             verbosity,workFactor);
   } else {
      bzfp = BZ2_bzReadOpen(&bzerr,fp,verbosity,smallMode,
                            unused,nUnused);
   }
   if (bzfp == 0) {
      if (fp != stdin && fp != stdout) fclose(fp);
      return 0;
   }
   return bzfp;
}
# 1468 "/app/subjects/bzip2/bzlib.c"
BZFILE * BZ2_bzopen
               ( const char *path,
                 const char *mode )
{
   return bzopen_or_bzdopen(path,-1,mode, 0);
}



BZFILE * BZ2_bzdopen
               ( int fd,
                 const char *mode )
{
   return bzopen_or_bzdopen(0,fd,mode, 1);
}



int BZ2_bzread (BZFILE* b, void* buf, int len )
{
   int bzerr, nread;
   if (((bzFile*)b)->lastErr == 4) return 0;
   nread = BZ2_bzRead(&bzerr,b,buf,len);
   if (bzerr == 0 || bzerr == 4) {
      return nread;
   } else {
      return -1;
   }
}



int BZ2_bzwrite (BZFILE* b, void* buf, int len )
{
   int bzerr;

   BZ2_bzWrite(&bzerr,b,buf,len);
   if(bzerr == 0){
      return len;
   }else{
      return -1;
   }
}



int BZ2_bzflush (BZFILE *b)
{

   return 0;
}



void BZ2_bzclose (BZFILE* b)
{
   int bzerr;
   FILE *fp;

   if (b==0) {return;}
   fp = ((bzFile *)b)->handle;
   if(((bzFile*)b)->writing){
      BZ2_bzWriteClose(&bzerr,b,0,0,0);
      if(bzerr != 0){
         BZ2_bzWriteClose(0,b,1,0,0);
      }
   }else{
      BZ2_bzReadClose(&bzerr,b);
   }
   if(fp!=stdin && fp!=stdout){
      fclose(fp);
   }
}






static const char *bzerrorstrings[] = {
       "OK"
      ,"SEQUENCE_ERROR"
      ,"PARAM_ERROR"
      ,"MEM_ERROR"
      ,"DATA_ERROR"
      ,"DATA_ERROR_MAGIC"
      ,"IO_ERROR"
      ,"UNEXPECTED_EOF"
      ,"OUTBUFF_FULL"
      ,"CONFIG_ERROR"
      ,"???"
      ,"???"
      ,"???"
      ,"???"
      ,"???"
      ,"???"
};


const char * BZ2_bzerror (BZFILE *b, int *errnum)
{
   int err = ((bzFile *)b)->lastErr;

   if(err>0) err = 0;
   *errnum = err;
   return bzerrorstrings[err*-1];
}
