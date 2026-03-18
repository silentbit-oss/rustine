# 0 "/app/subjects/bzip2/bzip2.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/bzip2/bzip2.c"
# 26 "/app/subjects/bzip2/bzip2.c"
# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 2
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
# 3 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 27 "/app/subjects/bzip2/bzip2.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 28 "/app/subjects/bzip2/bzip2.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 29 "/app/subjects/bzip2/bzip2.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/signal.h" 1
# 30 "/app/subjects/bzip2/bzip2.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/math.h" 1
# 31 "/app/subjects/bzip2/bzip2.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/errno.h" 1
# 32 "/app/subjects/bzip2/bzip2.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 33 "/app/subjects/bzip2/bzip2.c" 2
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
# 34 "/app/subjects/bzip2/bzip2.c" 2
# 144 "/app/subjects/bzip2/bzip2.c"
typedef char Char;
typedef unsigned char Bool;
typedef unsigned char UChar;
typedef int Int32;
typedef unsigned int UInt32;
typedef short Int16;
typedef unsigned short UInt16;
# 159 "/app/subjects/bzip2/bzip2.c"
typedef int IntNative;






Int32 verbosity;
Bool keepInputFiles, smallMode, deleteOutputOnInterrupt;
Bool forceOverwrite, testFailsExist, unzFailsExist, noisy;
Int32 numFileNames, numFilesProcessed, blockSize100k;
Int32 exitValue;
# 182 "/app/subjects/bzip2/bzip2.c"
Int32 opMode;
Int32 srcMode;



Int32 longestFileName;
Char inName [1034];
Char outName[1034];
Char tmpName[1034];
Char *progName;
Char progNameReally[1034];
FILE *outputHandleJustInCase;
Int32 workFactor;

static void panic ( const Char* ) ;
static void ioError ( void ) ;
static void outOfMemory ( void ) ;
static void configError ( void ) ;
static void crcError ( void ) ;
static void cleanUpAndFail ( Int32 ) ;
static void compressedStreamEOF ( void ) ;

static void copyFileName ( Char*, Char* );
static void* myMalloc ( Int32 );
static void applySavedFileAttrToOutputFile ( IntNative fd );
# 215 "/app/subjects/bzip2/bzip2.c"
typedef
   struct { UChar b[8]; }
   UInt64;


static
void uInt64_from_UInt32s ( UInt64* n, UInt32 lo32, UInt32 hi32 )
{
   n->b[7] = (UChar)((hi32 >> 24) & 0xFF);
   n->b[6] = (UChar)((hi32 >> 16) & 0xFF);
   n->b[5] = (UChar)((hi32 >> 8) & 0xFF);
   n->b[4] = (UChar) (hi32 & 0xFF);
   n->b[3] = (UChar)((lo32 >> 24) & 0xFF);
   n->b[2] = (UChar)((lo32 >> 16) & 0xFF);
   n->b[1] = (UChar)((lo32 >> 8) & 0xFF);
   n->b[0] = (UChar) (lo32 & 0xFF);
}


static
double uInt64_to_double ( UInt64* n )
{
   Int32 i;
   double base = 1.0;
   double sum = 0.0;
   for (i = 0; i < 8; i++) {
      sum += base * (double)(n->b[i]);
      base *= 256.0;
   }
   return sum;
}


static
Bool uInt64_isZero ( UInt64* n )
{
   Int32 i;
   for (i = 0; i < 8; i++)
      if (n->b[i] != 0) return 0;
   return 1;
}



static
Int32 uInt64_qrm10 ( UInt64* n )
{
   UInt32 rem, tmp;
   Int32 i;
   rem = 0;
   for (i = 7; i >= 0; i--) {
      tmp = rem * 256 + n->b[i];
      n->b[i] = tmp / 10;
      rem = tmp % 10;
   }
   return rem;
}





static
void uInt64_toAscii ( char* outbuf, UInt64* n )
{
   Int32 i, q;
   UChar buf[32];
   Int32 nBuf = 0;
   UInt64 n_copy = *n;
   do {
      q = uInt64_qrm10 ( &n_copy );
      buf[nBuf] = q + '0';
      nBuf++;
   } while (!uInt64_isZero(&n_copy));
   outbuf[nBuf] = 0;
   for (i = 0; i < nBuf; i++)
      outbuf[i] = buf[nBuf-i-1];
}







static
Bool myfeof ( FILE* f )
{
   Int32 c = fgetc ( f );
   if (c == EOF) return ((Bool)1);
   ungetc ( c, f );
   return ((Bool)0);
}



static
void compressStream ( FILE *stream, FILE *zStream )
{
   BZFILE* bzf = 0;
   UChar ibuf[5000];
   Int32 nIbuf;
   UInt32 nbytes_in_lo32, nbytes_in_hi32;
   UInt32 nbytes_out_lo32, nbytes_out_hi32;
   Int32 bzerr, bzerr_dummy, ret;

   SET_BINARY_MODE(stream);
   SET_BINARY_MODE(zStream);

   if (ferror(stream)) goto errhandler_io;
   if (ferror(zStream)) goto errhandler_io;

   bzf = BZ2_bzWriteOpen ( &bzerr, zStream,
                           blockSize100k, verbosity, workFactor );
   if (bzerr != 0) goto errhandler;

   if (verbosity >= 2) fprintf ( stderr, "\n" );

   while (((Bool)1)) {

      if (myfeof(stream)) break;
      nIbuf = fread ( ibuf, sizeof(UChar), 5000, stream );
      if (ferror(stream)) goto errhandler_io;
      if (nIbuf > 0) BZ2_bzWrite ( &bzerr, bzf, (void*)ibuf, nIbuf );
      if (bzerr != 0) goto errhandler;

   }

   BZ2_bzWriteClose64 ( &bzerr, bzf, 0,
                        &nbytes_in_lo32, &nbytes_in_hi32,
                        &nbytes_out_lo32, &nbytes_out_hi32 );
   if (bzerr != 0) goto errhandler;

   if (ferror(zStream)) goto errhandler_io;
   ret = fflush ( zStream );
   if (ret == EOF) goto errhandler_io;
   if (zStream != stdout) {
      Int32 fd = fileno ( zStream );
      if (fd < 0) goto errhandler_io;
      applySavedFileAttrToOutputFile ( fd );
      ret = fclose ( zStream );
      outputHandleJustInCase = 0;
      if (ret == EOF) goto errhandler_io;
   }
   outputHandleJustInCase = 0;
   if (ferror(stream)) goto errhandler_io;
   ret = fclose ( stream );
   if (ret == EOF) goto errhandler_io;

   if (verbosity >= 1) {
      if (nbytes_in_lo32 == 0 && nbytes_in_hi32 == 0) {
         fprintf ( stderr, " no data compressed.\n");
      } else {
         Char buf_nin[32], buf_nout[32];
         UInt64 nbytes_in, nbytes_out;
         double nbytes_in_d, nbytes_out_d;
         uInt64_from_UInt32s ( &nbytes_in,
            nbytes_in_lo32, nbytes_in_hi32 );
         uInt64_from_UInt32s ( &nbytes_out,
            nbytes_out_lo32, nbytes_out_hi32 );
         nbytes_in_d = uInt64_to_double ( &nbytes_in );
         nbytes_out_d = uInt64_to_double ( &nbytes_out );
         uInt64_toAscii ( buf_nin, &nbytes_in );
         uInt64_toAscii ( buf_nout, &nbytes_out );
         fprintf ( stderr, "%6.3f:1, %6.3f bits/byte, "
            "%5.2f%% saved, %s in, %s out.\n",
            nbytes_in_d / nbytes_out_d,
            (8.0 * nbytes_out_d) / nbytes_in_d,
            100.0 * (1.0 - nbytes_out_d / nbytes_in_d),
            buf_nin,
            buf_nout
         );
      }
   }

   return;

errhandler:
   BZ2_bzWriteClose64 ( &bzerr_dummy, bzf, 1,
                        &nbytes_in_lo32, &nbytes_in_hi32,
                        &nbytes_out_lo32, &nbytes_out_hi32 );
   switch (bzerr) {
      case (-9):
         configError(); break;
      case (-3):
         outOfMemory (); break;
      case (-6):
         errhandler_io:
         ioError(); break;
      default:
         panic ( "compress:unexpected error" );
   }

   panic ( "compress:end" );

}




static
Bool uncompressStream ( FILE *zStream, FILE *stream )
{
   BZFILE* bzf = 0;
   Int32 bzerr, bzerr_dummy, ret, nread, streamNo, i;
   UChar obuf[5000];
   UChar unused[5000];
   Int32 nUnused;
   void* unusedTmpV;
   UChar* unusedTmp;

   nUnused = 0;
   streamNo = 0;

   SET_BINARY_MODE(stream);
   SET_BINARY_MODE(zStream);

   if (ferror(stream)) goto errhandler_io;
   if (ferror(zStream)) goto errhandler_io;

   while (((Bool)1)) {

      bzf = BZ2_bzReadOpen (
               &bzerr, zStream, verbosity,
               (int)smallMode, unused, nUnused
            );
      if (bzf == 0 || bzerr != 0) goto errhandler;
      streamNo++;

      while (bzerr == 0) {
         nread = BZ2_bzRead ( &bzerr, bzf, obuf, 5000 );
         if (bzerr == (-5)) goto trycat;
         if ((bzerr == 0 || bzerr == 4) && nread > 0)
            fwrite ( obuf, sizeof(UChar), nread, stream );
         if (ferror(stream)) goto errhandler_io;
      }
      if (bzerr != 4) goto errhandler;

      BZ2_bzReadGetUnused ( &bzerr, bzf, &unusedTmpV, &nUnused );
      if (bzerr != 0) panic ( "decompress:bzReadGetUnused" );

      unusedTmp = (UChar*)unusedTmpV;
      for (i = 0; i < nUnused; i++) unused[i] = unusedTmp[i];

      BZ2_bzReadClose ( &bzerr, bzf );
      if (bzerr != 0) panic ( "decompress:bzReadGetUnused" );

      if (nUnused == 0 && myfeof(zStream)) break;
   }

closeok:
   if (ferror(zStream)) goto errhandler_io;
   if (stream != stdout) {
      Int32 fd = fileno ( stream );
      if (fd < 0) goto errhandler_io;
      applySavedFileAttrToOutputFile ( fd );
   }
   ret = fclose ( zStream );
   if (ret == EOF) goto errhandler_io;

   if (ferror(stream)) goto errhandler_io;
   ret = fflush ( stream );
   if (ret != 0) goto errhandler_io;
   if (stream != stdout) {
      ret = fclose ( stream );
      outputHandleJustInCase = 0;
      if (ret == EOF) goto errhandler_io;
   }
   outputHandleJustInCase = 0;
   if (verbosity >= 2) fprintf ( stderr, "\n    " );
   return ((Bool)1);

trycat:
   if (forceOverwrite) {
      rewind(zStream);
      while (((Bool)1)) {
         if (myfeof(zStream)) break;
         nread = fread ( obuf, sizeof(UChar), 5000, zStream );
         if (ferror(zStream)) goto errhandler_io;
         if (nread > 0) fwrite ( obuf, sizeof(UChar), nread, stream );
         if (ferror(stream)) goto errhandler_io;
      }
      goto closeok;
   }

errhandler:
   BZ2_bzReadClose ( &bzerr_dummy, bzf );
   switch (bzerr) {
      case (-9):
         configError(); break;
      case (-6):
         errhandler_io:
         ioError(); break;
      case (-4):
         crcError();
      case (-3):
         outOfMemory();
      case (-7):
         compressedStreamEOF();
      case (-5):
         if (zStream != stdin) fclose(zStream);
         if (stream != stdout) fclose(stream);
         if (streamNo == 1) {
            return ((Bool)0);
         } else {
            if (noisy)
            fprintf ( stderr,
                      "\n%s: %s: trailing garbage after EOF ignored\n",
                      progName, inName );
            return ((Bool)1);
         }
      default:
         panic ( "decompress:unexpected error" );
   }

   panic ( "decompress:end" );
   return ((Bool)1);
}



static
Bool testStream ( FILE *zStream )
{
   BZFILE* bzf = 0;
   Int32 bzerr, bzerr_dummy, ret, streamNo, i;
   UChar obuf[5000];
   UChar unused[5000];
   Int32 nUnused;
   void* unusedTmpV;
   UChar* unusedTmp;

   nUnused = 0;
   streamNo = 0;

   SET_BINARY_MODE(zStream);
   if (ferror(zStream)) goto errhandler_io;

   while (((Bool)1)) {

      bzf = BZ2_bzReadOpen (
               &bzerr, zStream, verbosity,
               (int)smallMode, unused, nUnused
            );
      if (bzf == 0 || bzerr != 0) goto errhandler;
      streamNo++;

      while (bzerr == 0) {
         BZ2_bzRead ( &bzerr, bzf, obuf, 5000 );
         if (bzerr == (-5)) goto errhandler;
      }
      if (bzerr != 4) goto errhandler;

      BZ2_bzReadGetUnused ( &bzerr, bzf, &unusedTmpV, &nUnused );
      if (bzerr != 0) panic ( "test:bzReadGetUnused" );

      unusedTmp = (UChar*)unusedTmpV;
      for (i = 0; i < nUnused; i++) unused[i] = unusedTmp[i];

      BZ2_bzReadClose ( &bzerr, bzf );
      if (bzerr != 0) panic ( "test:bzReadGetUnused" );
      if (nUnused == 0 && myfeof(zStream)) break;

   }

   if (ferror(zStream)) goto errhandler_io;
   ret = fclose ( zStream );
   if (ret == EOF) goto errhandler_io;

   if (verbosity >= 2) fprintf ( stderr, "\n    " );
   return ((Bool)1);

errhandler:
   BZ2_bzReadClose ( &bzerr_dummy, bzf );
   if (verbosity == 0)
      fprintf ( stderr, "%s: %s: ", progName, inName );
   switch (bzerr) {
      case (-9):
         configError(); break;
      case (-6):
         errhandler_io:
         ioError(); break;
      case (-4):
         fprintf ( stderr,
                   "data integrity (CRC) error in data\n" );
         return ((Bool)0);
      case (-3):
         outOfMemory();
      case (-7):
         fprintf ( stderr,
                   "file ends unexpectedly\n" );
         return ((Bool)0);
      case (-5):
         if (zStream != stdin) fclose(zStream);
         if (streamNo == 1) {
          fprintf ( stderr,
                    "bad magic number (file not created by bzip2)\n" );
            return ((Bool)0);
         } else {
            if (noisy)
            fprintf ( stderr,
                      "trailing garbage after EOF ignored\n" );
            return ((Bool)1);
         }
      default:
         panic ( "test:unexpected error" );
   }

   panic ( "test:end" );
   return ((Bool)1);
}







static
void setExit ( Int32 v )
{
   if (v > exitValue) exitValue = v;
}



static
void cadvise ( void )
{
   if (noisy)
   fprintf (
      stderr,
      "\nIt is possible that the compressed file(s) have become corrupted.\n"
        "You can use the -tvv option to test integrity of such files.\n\n"
        "You can use the `bzip2recover' program to attempt to recover\n"
        "data from undamaged sections of corrupted files.\n\n"
    );
}



static
void showFileNames ( void )
{
   if (noisy)
   fprintf (
      stderr,
      "\tInput file = %s, output file = %s\n",
      inName, outName
   );
}



static
void cleanUpAndFail ( Int32 ec )
{
   IntNative retVal;
   struct MY_STAT statBuf;

   if ( srcMode == 3
        && opMode != 3
        && deleteOutputOnInterrupt ) {






      retVal = MY_STAT ( inName, &statBuf );
      if (retVal == 0) {
         if (noisy)
            fprintf ( stderr,
                      "%s: Deleting output file %s, if it exists.\n",
                      progName, outName );
         if (outputHandleJustInCase != 0)
            fclose ( outputHandleJustInCase );
         retVal = remove ( outName );
         if (retVal != 0)
            fprintf ( stderr,
                      "%s: WARNING: deletion of output file "
                      "(apparently) failed.\n",
                      progName );
      } else {
         fprintf ( stderr,
                   "%s: WARNING: deletion of output file suppressed\n",
                    progName );
         fprintf ( stderr,
                   "%s:    since input file no longer exists.  Output file\n",
                   progName );
         fprintf ( stderr,
                   "%s:    `%s' may be incomplete.\n",
                   progName, outName );
         fprintf ( stderr,
                   "%s:    I suggest doing an integrity test (bzip2 -tv)"
                   " of it.\n",
                   progName );
      }
   }

   if (noisy && numFileNames > 0 && numFilesProcessed < numFileNames) {
      fprintf ( stderr,
                "%s: WARNING: some files have not been processed:\n"
                "%s:    %d specified on command line, %d not processed yet.\n\n",
                progName, progName,
                numFileNames, numFileNames - numFilesProcessed );
   }
   setExit(ec);
   exit(exitValue);
}



static
void panic ( const Char* s )
{
   fprintf ( stderr,
             "\n%s: PANIC -- internal consistency error:\n"
             "\t%s\n"
             "\tThis is a BUG.  Please report it at:\n"
             "\thttps://gitlab.com/bzip2/bzip2/-/issues\n",
             progName, s );
   showFileNames();
   cleanUpAndFail( 3 );
}



static
void crcError ( void )
{
   fprintf ( stderr,
             "\n%s: Data integrity error when decompressing.\n",
             progName );
   showFileNames();
   cadvise();
   cleanUpAndFail( 2 );
}



static
void compressedStreamEOF ( void )
{
   if (noisy) {
      fprintf ( stderr,
         "\n%s: Compressed file ends unexpectedly;\n\t"
         "perhaps it is corrupted?  *Possible* reason follows.\n",
         progName );
      perror ( progName );
      showFileNames();
      cadvise();
   }
   cleanUpAndFail( 2 );
}



static
void ioError ( void )
{
   fprintf ( stderr,
             "\n%s: I/O or other error, bailing out.  "
             "Possible reason follows.\n",
             progName );
   perror ( progName );
   showFileNames();
   cleanUpAndFail( 1 );
}



static
void mySignalCatcher ( IntNative n )
{
   fprintf ( stderr,
             "\n%s: Control-C or similar caught, quitting.\n",
             progName );
   cleanUpAndFail(1);
}



static
void mySIGSEGVorSIGBUScatcher ( IntNative n )
{
   const char *msg;
   if (opMode == 1)
      msg = ": Caught a SIGSEGV or SIGBUS whilst compressing.\n"
      "\n"
      "   Possible causes are (most likely first):\n"
      "   (1) This computer has unreliable memory or cache hardware\n"
      "       (a surprisingly common problem; try a different machine.)\n"
      "   (2) A bug in the compiler used to create this executable\n"
      "       (unlikely, if you didn't compile bzip2 yourself.)\n"
      "   (3) A real bug in bzip2 -- I hope this should never be the case.\n"
      "   The user's manual, Section 4.3, has more info on (1) and (2).\n"
      "   \n"
      "   If you suspect this is a bug in bzip2, or are unsure about (1)\n"
      "   or (2), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n"
      "   Section 4.3 of the user's manual describes the info a useful\n"
      "   bug report should have.  If the manual is available on your\n"
      "   system, please try and read it before mailing me.  If you don't\n"
      "   have the manual or can't be bothered to read it, mail me anyway.\n"
      "\n";
   else
      msg = ": Caught a SIGSEGV or SIGBUS whilst decompressing.\n"
      "\n"
      "   Possible causes are (most likely first):\n"
      "   (1) The compressed data is corrupted, and bzip2's usual checks\n"
      "       failed to detect this.  Try bzip2 -tvv my_file.bz2.\n"
      "   (2) This computer has unreliable memory or cache hardware\n"
      "       (a surprisingly common problem; try a different machine.)\n"
      "   (3) A bug in the compiler used to create this executable\n"
      "       (unlikely, if you didn't compile bzip2 yourself.)\n"
      "   (4) A real bug in bzip2 -- I hope this should never be the case.\n"
      "   The user's manual, Section 4.3, has more info on (2) and (3).\n"
      "   \n"
      "   If you suspect this is a bug in bzip2, or are unsure about (2)\n"
      "   or (3), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n"
      "   Section 4.3 of the user's manual describes the info a useful\n"
      "   bug report should have.  If the manual is available on your\n"
      "   system, please try and read it before mailing me.  If you don't\n"
      "   have the manual or can't be bothered to read it, mail me anyway.\n"
      "\n";
   write ( STDERR_FILENO, "\n", 1 );
   write ( STDERR_FILENO, progName, strlen ( progName ) );
   write ( STDERR_FILENO, msg, strlen ( msg ) );

   msg = "\tInput file = ";
   write ( STDERR_FILENO, msg, strlen (msg) );
   write ( STDERR_FILENO, inName, strlen (inName) );
   write ( STDERR_FILENO, "\n", 1 );
   msg = "\tOutput file = ";
   write ( STDERR_FILENO, msg, strlen (msg) );
   write ( STDERR_FILENO, outName, strlen (outName) );
   write ( STDERR_FILENO, "\n", 1 );




   if (opMode == 1) setExit(3); else setExit(2);
   _exit(exitValue);
}



static
void outOfMemory ( void )
{
   fprintf ( stderr,
             "\n%s: couldn't allocate enough memory\n",
             progName );
   showFileNames();
   cleanUpAndFail(1);
}



static
void configError ( void )
{
   fprintf ( stderr,
             "bzip2: I'm not configured correctly for this platform!\n"
             "\tI require Int32, Int16 and Char to have sizes\n"
             "\tof 4, 2 and 1 bytes to run properly, and they don't.\n"
             "\tProbably you can fix this by defining them correctly,\n"
             "\tand recompiling.  Bye!\n" );
   setExit(3);
   exit(exitValue);
}
# 898 "/app/subjects/bzip2/bzip2.c"
static
void pad ( Char *s )
{
   Int32 i;
   if ( (Int32)strlen(s) >= longestFileName ) return;
   for (i = 1; i <= longestFileName - (Int32)strlen(s); i++)
      fprintf ( stderr, " " );
}



static
void copyFileName ( Char* to, Char* from )
{
   if ( strlen(from) > 1034 -10 ) {
      fprintf (
         stderr,
         "bzip2: file name\n`%s'\n"
         "is suspiciously (more than %d chars) long.\n"
         "Try using a reasonable file name instead.  Sorry! :-)\n",
         from, 1034 -10
      );
      setExit(1);
      exit(exitValue);
   }

  strncpy(to,from,1034 -10);
  to[1034 -10]='\0';
}



static
Bool fileExists ( Char* name )
{
   FILE *tmp = fopen ( name, "rb" );
   Bool exists = (tmp != 0);
   if (tmp != 0) fclose ( tmp );
   return exists;
}
# 950 "/app/subjects/bzip2/bzip2.c"
static
FILE* fopen_output_safely ( Char* name, const char* mode )
{
# 962 "/app/subjects/bzip2/bzip2.c"
   return fopen(name, mode);

}






static
Bool notAStandardFile ( Char* name )
{
   IntNative i;
   struct MY_STAT statBuf;

   i = MY_LSTAT ( name, &statBuf );
   if (i != 0) return ((Bool)1);
   if (MY_S_ISREG(statBuf.st_mode)) return ((Bool)0);
   return ((Bool)1);
}






static
Int32 countHardLinks ( Char* name )
{
   IntNative i;
   struct MY_STAT statBuf;

   i = MY_LSTAT ( name, &statBuf );
   if (i != 0) return 0;
   return (statBuf.st_nlink - 1);
}
# 1028 "/app/subjects/bzip2/bzip2.c"
static
void saveInputFileMetaInfo ( Char *srcName )
{






}


static
void applySavedTimeInfoToOutputFile ( Char *dstName )
{
# 1053 "/app/subjects/bzip2/bzip2.c"
}

static
void applySavedFileAttrToOutputFile ( IntNative fd )
{
# 1069 "/app/subjects/bzip2/bzip2.c"
}



static
Bool containsDubiousChars ( Char* name )
{
# 1085 "/app/subjects/bzip2/bzip2.c"
   for (; *name != '\0'; name++)
      if (*name == '?' || *name == '*') return ((Bool)1);
   return ((Bool)0);

}





const Char* zSuffix[4]
   = { ".bz2", ".bz", ".tbz2", ".tbz" };
const Char* unzSuffix[4]
   = { "", "", ".tar", ".tar" };

static
Bool hasSuffix ( Char* s, const Char* suffix )
{
   Int32 ns = strlen(s);
   Int32 nx = strlen(suffix);
   if (ns < nx) return ((Bool)0);
   if (strcmp(s + ns - nx, suffix) == 0) return ((Bool)1);
   return ((Bool)0);
}

static
Bool mapSuffix ( Char* name,
                 const Char* oldSuffix,
                 const Char* newSuffix )
{
   if (!hasSuffix(name,oldSuffix)) return ((Bool)0);
   name[strlen(name)-strlen(oldSuffix)] = 0;
   strcat ( name, newSuffix );
   return ((Bool)1);
}



static
void compress ( Char *name )
{
   FILE *inStr;
   FILE *outStr;
   Int32 n, i;
   struct MY_STAT statBuf;

   deleteOutputOnInterrupt = ((Bool)0);

   if (name == 0 && srcMode != 1)
      panic ( "compress: bad modes\n" );

   switch (srcMode) {
      case 1:
         copyFileName ( inName, (Char*)"(stdin)" );
         copyFileName ( outName, (Char*)"(stdout)" );
         break;
      case 3:
         copyFileName ( inName, name );
         copyFileName ( outName, name );
         strcat ( outName, ".bz2" );
         break;
      case 2:
         copyFileName ( inName, name );
         copyFileName ( outName, (Char*)"(stdout)" );
         break;
   }

   if ( srcMode != 1 && containsDubiousChars ( inName ) ) {
      if (noisy)
      fprintf ( stderr, "%s: There are no files matching `%s'.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode != 1 && !fileExists ( inName ) ) {
      fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                progName, inName, strerror(errno) );
      setExit(1);
      return;
   }
   for (i = 0; i < 4; i++) {
      if (hasSuffix(inName, zSuffix[i])) {
         if (noisy)
         fprintf ( stderr,
                   "%s: Input file %s already has %s suffix.\n",
                   progName, inName, zSuffix[i] );
         setExit(1);
         return;
      }
   }
   if ( srcMode == 3 || srcMode == 2 ) {
      MY_STAT(inName, &statBuf);
      if ( MY_S_ISDIR(statBuf.st_mode) ) {
         fprintf( stderr,
                  "%s: Input file %s is a directory.\n",
                  progName,inName);
         setExit(1);
         return;
      }
   }
   if ( srcMode == 3 && !forceOverwrite && notAStandardFile ( inName )) {
      if (noisy)
      fprintf ( stderr, "%s: Input file %s is not a normal file.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode == 3 && fileExists ( outName ) ) {
      if (forceOverwrite) {
         remove(outName);
      } else {
         fprintf ( stderr, "%s: Output file %s already exists.\n",
            progName, outName );
         setExit(1);
         return;
      }
   }
   if ( srcMode == 3 && !forceOverwrite &&
        (n=countHardLinks ( inName )) > 0) {
      fprintf ( stderr, "%s: Input file %s has %d other link%s.\n",
                progName, inName, n, n > 1 ? "s" : "" );
      setExit(1);
      return;
   }

   if ( srcMode == 3 ) {


      saveInputFileMetaInfo ( inName );
   }

   switch ( srcMode ) {

      case 1:
         inStr = stdin;
         outStr = stdout;
         if ( isatty ( fileno ( stdout ) ) ) {
            fprintf ( stderr,
                      "%s: I won't write compressed data to a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            setExit(1);
            return;
         };
         break;

      case 2:
         inStr = fopen ( inName, "rb" );
         outStr = stdout;
         if ( isatty ( fileno ( stdout ) ) ) {
            fprintf ( stderr,
                      "%s: I won't write compressed data to a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            if ( inStr != 0 ) fclose ( inStr );
            setExit(1);
            return;
         };
         if ( inStr == 0 ) {
            fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                      progName, inName, strerror(errno) );
            setExit(1);
            return;
         };
         break;

      case 3:
         inStr = fopen ( inName, "rb" );
         outStr = fopen_output_safely ( outName, "wb" );
         if ( outStr == 0) {
            fprintf ( stderr, "%s: Can't create output file %s: %s.\n",
                      progName, outName, strerror(errno) );
            if ( inStr != 0 ) fclose ( inStr );
            setExit(1);
            return;
         }
         if ( inStr == 0 ) {
            fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                      progName, inName, strerror(errno) );
            if ( outStr != 0 ) fclose ( outStr );
            setExit(1);
            return;
         };
         break;

      default:
         panic ( "compress: bad srcMode" );
         break;
   }

   if (verbosity >= 1) {
      fprintf ( stderr, "  %s: ", inName );
      pad ( inName );
      fflush ( stderr );
   }


   outputHandleJustInCase = outStr;
   deleteOutputOnInterrupt = ((Bool)1);
   compressStream ( inStr, outStr );
   outputHandleJustInCase = 0;


   if ( srcMode == 3 ) {
      applySavedTimeInfoToOutputFile ( outName );
      deleteOutputOnInterrupt = ((Bool)0);
      if ( !keepInputFiles ) {
         IntNative retVal = remove ( inName );
         { if ((retVal) != 0) ioError(); };
      }
   }

   deleteOutputOnInterrupt = ((Bool)0);
}



static
void uncompress ( Char *name )
{
   FILE *inStr;
   FILE *outStr;
   Int32 n, i;
   Bool magicNumberOK;
   Bool cantGuess;
   struct MY_STAT statBuf;

   deleteOutputOnInterrupt = ((Bool)0);

   if (name == 0 && srcMode != 1)
      panic ( "uncompress: bad modes\n" );

   cantGuess = ((Bool)0);
   switch (srcMode) {
      case 1:
         copyFileName ( inName, (Char*)"(stdin)" );
         copyFileName ( outName, (Char*)"(stdout)" );
         break;
      case 3:
         copyFileName ( inName, name );
         copyFileName ( outName, name );
         for (i = 0; i < 4; i++)
            if (mapSuffix(outName,zSuffix[i],unzSuffix[i]))
               goto zzz;
         cantGuess = ((Bool)1);
         strcat ( outName, ".out" );
         break;
      case 2:
         copyFileName ( inName, name );
         copyFileName ( outName, (Char*)"(stdout)" );
         break;
   }

   zzz:
   if ( srcMode != 1 && containsDubiousChars ( inName ) ) {
      if (noisy)
      fprintf ( stderr, "%s: There are no files matching `%s'.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode != 1 && !fileExists ( inName ) ) {
      fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                progName, inName, strerror(errno) );
      setExit(1);
      return;
   }
   if ( srcMode == 3 || srcMode == 2 ) {
      MY_STAT(inName, &statBuf);
      if ( MY_S_ISDIR(statBuf.st_mode) ) {
         fprintf( stderr,
                  "%s: Input file %s is a directory.\n",
                  progName,inName);
         setExit(1);
         return;
      }
   }
   if ( srcMode == 3 && !forceOverwrite && notAStandardFile ( inName )) {
      if (noisy)
      fprintf ( stderr, "%s: Input file %s is not a normal file.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( cantGuess ) {
      if (noisy)
      fprintf ( stderr,
                "%s: Can't guess original name for %s -- using %s\n",
                progName, inName, outName );

   }
   if ( srcMode == 3 && fileExists ( outName ) ) {
      if (forceOverwrite) {
         remove(outName);
      } else {
         fprintf ( stderr, "%s: Output file %s already exists.\n",
                     progName, outName );
         setExit(1);
         return;
      }
   }
   if ( srcMode == 3 && !forceOverwrite &&
        (n=countHardLinks ( inName ) ) > 0) {
      fprintf ( stderr, "%s: Input file %s has %d other link%s.\n",
                progName, inName, n, n > 1 ? "s" : "" );
      setExit(1);
      return;
   }

   if ( srcMode == 3 ) {


      saveInputFileMetaInfo ( inName );
   }

   switch ( srcMode ) {

      case 1:
         inStr = stdin;
         outStr = stdout;
         if ( isatty ( fileno ( stdin ) ) ) {
            fprintf ( stderr,
                      "%s: I won't read compressed data from a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            setExit(1);
            return;
         };
         break;

      case 2:
         inStr = fopen ( inName, "rb" );
         outStr = stdout;
         if ( inStr == 0 ) {
            fprintf ( stderr, "%s: Can't open input file %s:%s.\n",
                      progName, inName, strerror(errno) );
            if ( inStr != 0 ) fclose ( inStr );
            setExit(1);
            return;
         };
         break;

      case 3:
         inStr = fopen ( inName, "rb" );
         outStr = fopen_output_safely ( outName, "wb" );
         if ( outStr == 0) {
            fprintf ( stderr, "%s: Can't create output file %s: %s.\n",
                      progName, outName, strerror(errno) );
            if ( inStr != 0 ) fclose ( inStr );
            setExit(1);
            return;
         }
         if ( inStr == 0 ) {
            fprintf ( stderr, "%s: Can't open input file %s: %s.\n",
                      progName, inName, strerror(errno) );
            if ( outStr != 0 ) fclose ( outStr );
            setExit(1);
            return;
         };
         break;

      default:
         panic ( "uncompress: bad srcMode" );
         break;
   }

   if (verbosity >= 1) {
      fprintf ( stderr, "  %s: ", inName );
      pad ( inName );
      fflush ( stderr );
   }


   outputHandleJustInCase = outStr;
   deleteOutputOnInterrupt = ((Bool)1);
   magicNumberOK = uncompressStream ( inStr, outStr );
   outputHandleJustInCase = 0;


   if ( magicNumberOK ) {
      if ( srcMode == 3 ) {
         applySavedTimeInfoToOutputFile ( outName );
         deleteOutputOnInterrupt = ((Bool)0);
         if ( !keepInputFiles ) {
            IntNative retVal = remove ( inName );
            { if ((retVal) != 0) ioError(); };
         }
      }
   } else {
      unzFailsExist = ((Bool)1);
      deleteOutputOnInterrupt = ((Bool)0);
      if ( srcMode == 3 ) {
         IntNative retVal = remove ( outName );
         { if ((retVal) != 0) ioError(); };
      }
   }
   deleteOutputOnInterrupt = ((Bool)0);

   if ( magicNumberOK ) {
      if (verbosity >= 1)
         fprintf ( stderr, "done\n" );
   } else {
      setExit(2);
      if (verbosity >= 1)
         fprintf ( stderr, "not a bzip2 file.\n" ); else
         fprintf ( stderr,
                   "%s: %s is not a bzip2 file.\n",
                   progName, inName );
   }

}



static
void testf ( Char *name )
{
   FILE *inStr;
   Bool allOK;
   struct MY_STAT statBuf;

   deleteOutputOnInterrupt = ((Bool)0);

   if (name == 0 && srcMode != 1)
      panic ( "testf: bad modes\n" );

   copyFileName ( outName, (Char*)"(none)" );
   switch (srcMode) {
      case 1: copyFileName ( inName, (Char*)"(stdin)" ); break;
      case 3: copyFileName ( inName, name ); break;
      case 2: copyFileName ( inName, name ); break;
   }

   if ( srcMode != 1 && containsDubiousChars ( inName ) ) {
      if (noisy)
      fprintf ( stderr, "%s: There are no files matching `%s'.\n",
                progName, inName );
      setExit(1);
      return;
   }
   if ( srcMode != 1 && !fileExists ( inName ) ) {
      fprintf ( stderr, "%s: Can't open input %s: %s.\n",
                progName, inName, strerror(errno) );
      setExit(1);
      return;
   }
   if ( srcMode != 1 ) {
      MY_STAT(inName, &statBuf);
      if ( MY_S_ISDIR(statBuf.st_mode) ) {
         fprintf( stderr,
                  "%s: Input file %s is a directory.\n",
                  progName,inName);
         setExit(1);
         return;
      }
   }

   switch ( srcMode ) {

      case 1:
         if ( isatty ( fileno ( stdin ) ) ) {
            fprintf ( stderr,
                      "%s: I won't read compressed data from a terminal.\n",
                      progName );
            fprintf ( stderr, "%s: For help, type: `%s --help'.\n",
                              progName, progName );
            setExit(1);
            return;
         };
         inStr = stdin;
         break;

      case 2: case 3:
         inStr = fopen ( inName, "rb" );
         if ( inStr == 0 ) {
            fprintf ( stderr, "%s: Can't open input file %s:%s.\n",
                      progName, inName, strerror(errno) );
            setExit(1);
            return;
         };
         break;

      default:
         panic ( "testf: bad srcMode" );
         break;
   }

   if (verbosity >= 1) {
      fprintf ( stderr, "  %s: ", inName );
      pad ( inName );
      fflush ( stderr );
   }


   outputHandleJustInCase = 0;
   allOK = testStream ( inStr );

   if (allOK && verbosity >= 1) fprintf ( stderr, "ok\n" );
   if (!allOK) testFailsExist = ((Bool)1);
}



static
void license ( void )
{
   fprintf ( stdout,

    "bzip2, a block-sorting file compressor.  "
    "Version %s.\n"
    "   \n"
    "   Copyright (C) 1996-2010 by Julian Seward.\n"
    "   \n"
    "   This program is free software; you can redistribute it and/or modify\n"
    "   it under the terms set out in the LICENSE file, which is included\n"
    "   in the bzip2-1.0.6 source distribution.\n"
    "   \n"
    "   This program is distributed in the hope that it will be useful,\n"
    "   but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
    "   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
    "   LICENSE file for more details.\n"
    "   \n",
    BZ2_bzlibVersion()
   );
}



static
void usage ( Char *fullProgName )
{
   fprintf (
      stderr,
      "bzip2, a block-sorting file compressor.  "
      "Version %s.\n"
      "\n   usage: %s [flags and input files in any order]\n"
      "\n"
      "   -h --help           print this message\n"
      "   -d --decompress     force decompression\n"
      "   -z --compress       force compression\n"
      "   -k --keep           keep (don't delete) input files\n"
      "   -f --force          overwrite existing output files\n"
      "   -t --test           test compressed file integrity\n"
      "   -c --stdout         output to standard out\n"
      "   -q --quiet          suppress noncritical error messages\n"
      "   -v --verbose        be verbose (a 2nd -v gives more)\n"
      "   -L --license        display software version & license\n"
      "   -V --version        display software version & license\n"
      "   -s --small          use less memory (at most 2500k)\n"
      "   -1 .. -9            set block size to 100k .. 900k\n"
      "   --fast              alias for -1\n"
      "   --best              alias for -9\n"
      "\n"
      "   If invoked as `bzip2', default action is to compress.\n"
      "              as `bunzip2',  default action is to decompress.\n"
      "              as `bzcat', default action is to decompress to stdout.\n"
      "\n"
      "   If no file names are given, bzip2 compresses or decompresses\n"
      "   from standard input to standard output.  You can combine\n"
      "   short flags, so `-v -4' means the same as -v4 or -4v, &c.\n"



      ,

      BZ2_bzlibVersion(),
      fullProgName
   );
}



static
void redundant ( Char* flag )
{
   fprintf (
      stderr,
      "%s: %s is redundant in versions 0.9.5 and above\n",
      progName, flag );
}
# 1685 "/app/subjects/bzip2/bzip2.c"
typedef
   struct zzzz {
      Char *name;
      struct zzzz *link;
   }
   Cell;



static
void *myMalloc ( Int32 n )
{
   void* p;

   p = malloc ( (size_t)n );
   if (p == 0) outOfMemory ();
   return p;
}



static
Cell *mkCell ( void )
{
   Cell *c;

   c = (Cell*) myMalloc ( sizeof ( Cell ) );
   c->name = 0;
   c->link = 0;
   return c;
}



static
Cell *snocString ( Cell *root, Char *name )
{
   if (root == 0) {
      Cell *tmp = mkCell();
      tmp->name = (Char*) myMalloc ( 5 + strlen(name) );
      strcpy ( tmp->name, name );
      return tmp;
   } else {
      Cell *tmp = root;
      while (tmp->link != 0) tmp = tmp->link;
      tmp->link = snocString ( tmp->link, name );
      return root;
   }
}



static
void addFlagsFromEnvVar ( Cell** argList, Char* varName )
{
   Int32 i, j, k;
   Char *envbase, *p;

   envbase = getenv(varName);
   if (envbase != 0) {
      p = envbase;
      i = 0;
      while (((Bool)1)) {
         if (p[i] == 0) break;
         p += i;
         i = 0;
         while (isspace((Int32)(p[0]))) p++;
         while (p[i] != 0 && !isspace((Int32)(p[i]))) i++;
         if (i > 0) {
            k = i; if (k > 1034 -10) k = 1034 -10;
            for (j = 0; j < k; j++) tmpName[j] = p[j];
            tmpName[k] = 0;
            APPEND_FLAG(*argList, tmpName);
         }
      }
   }
}





IntNative main ( IntNative argc, Char *argv[] )
{
   Int32 i, j;
   Char *tmp;
   Cell *argList;
   Cell *aa;
   Bool decode;


   if (sizeof(Int32) != 4 || sizeof(UInt32) != 4 ||
       sizeof(Int16) != 2 || sizeof(UInt16) != 2 ||
       sizeof(Char) != 1 || sizeof(UChar) != 1)
      configError();


   outputHandleJustInCase = 0;
   smallMode = ((Bool)0);
   keepInputFiles = ((Bool)0);
   forceOverwrite = ((Bool)0);
   noisy = ((Bool)1);
   verbosity = 0;
   blockSize100k = 9;
   testFailsExist = ((Bool)0);
   unzFailsExist = ((Bool)0);
   numFileNames = 0;
   numFilesProcessed = 0;
   workFactor = 30;
   deleteOutputOnInterrupt = ((Bool)0);
   exitValue = 0;
   i = j = 0;


   signal (SIGSEGV, mySIGSEGVorSIGBUScatcher);






   copyFileName ( inName, (Char*)"(none)" );
   copyFileName ( outName, (Char*)"(none)" );

   copyFileName ( progNameReally, argv[0] );
   progName = &progNameReally[0];
   for (tmp = &progNameReally[0]; *tmp != '\0'; tmp++)
      if (*tmp == PATH_SEP) progName = tmp + 1;





   argList = 0;
   addFlagsFromEnvVar ( &argList, (Char*)"BZIP2" );
   addFlagsFromEnvVar ( &argList, (Char*)"BZIP" );
   for (i = 1; i <= argc-1; i++)
      APPEND_FILESPEC(argList, argv[i]);



   longestFileName = 7;
   numFileNames = 0;
   decode = ((Bool)1);
   for (aa = argList; aa != 0; aa = aa->link) {
      if ((strcmp(aa->name, ("--"))==0)) { decode = ((Bool)0); continue; }
      if (aa->name[0] == '-' && decode) continue;
      numFileNames++;
      if (longestFileName < (Int32)strlen(aa->name) )
         longestFileName = (Int32)strlen(aa->name);
   }



   if (numFileNames == 0)
      srcMode = 1; else srcMode = 3;




   opMode = 1;

   if ( (strstr ( progName, "unzip" ) != 0) ||
        (strstr ( progName, "UNZIP" ) != 0) )
      opMode = 2;

   if ( (strstr ( progName, "z2cat" ) != 0) ||
        (strstr ( progName, "Z2CAT" ) != 0) ||
        (strstr ( progName, "zcat" ) != 0) ||
        (strstr ( progName, "ZCAT" ) != 0) ) {
      opMode = 2;
      srcMode = (numFileNames == 0) ? 1 : 2;
   }



   for (aa = argList; aa != 0; aa = aa->link) {
      if ((strcmp(aa->name, ("--"))==0)) break;
      if (aa->name[0] == '-' && aa->name[1] != '-') {
         for (j = 1; aa->name[j] != '\0'; j++) {
            switch (aa->name[j]) {
               case 'c': srcMode = 2; break;
               case 'd': opMode = 2; break;
               case 'z': opMode = 1; break;
               case 'f': forceOverwrite = ((Bool)1); break;
               case 't': opMode = 3; break;
               case 'k': keepInputFiles = ((Bool)1); break;
               case 's': smallMode = ((Bool)1); break;
               case 'q': noisy = ((Bool)0); break;
               case '1': blockSize100k = 1; break;
               case '2': blockSize100k = 2; break;
               case '3': blockSize100k = 3; break;
               case '4': blockSize100k = 4; break;
               case '5': blockSize100k = 5; break;
               case '6': blockSize100k = 6; break;
               case '7': blockSize100k = 7; break;
               case '8': blockSize100k = 8; break;
               case '9': blockSize100k = 9; break;
               case 'V':
               case 'L': license();
                         exit ( 0 );
                         break;
               case 'v': verbosity++; break;
               case 'h': usage ( progName );
                         exit ( 0 );
                         break;
               default: fprintf ( stderr, "%s: Bad flag `%s'\n",
                                   progName, aa->name );
                         usage ( progName );
                         exit ( 1 );
                         break;
            }
         }
      }
   }


   for (aa = argList; aa != 0; aa = aa->link) {
      if ((strcmp(aa->name, ("--"))==0)) break;
      if ((strcmp(aa->name, ("--stdout"))==0)) srcMode = 2; else
      if ((strcmp(aa->name, ("--decompress"))==0)) opMode = 2; else
      if ((strcmp(aa->name, ("--compress"))==0)) opMode = 1; else
      if ((strcmp(aa->name, ("--force"))==0)) forceOverwrite = ((Bool)1); else
      if ((strcmp(aa->name, ("--test"))==0)) opMode = 3; else
      if ((strcmp(aa->name, ("--keep"))==0)) keepInputFiles = ((Bool)1); else
      if ((strcmp(aa->name, ("--small"))==0)) smallMode = ((Bool)1); else
      if ((strcmp(aa->name, ("--quiet"))==0)) noisy = ((Bool)0); else
      if ((strcmp(aa->name, ("--version"))==0)) { license(); exit ( 0 ); } else
      if ((strcmp(aa->name, ("--license"))==0)) { license(); exit ( 0 ); } else
      if ((strcmp(aa->name, ("--exponential"))==0)) workFactor = 1; else
      if ((strcmp(aa->name, ("--repetitive-best"))==0)) redundant(aa->name); else
      if ((strcmp(aa->name, ("--repetitive-fast"))==0)) redundant(aa->name); else
      if ((strcmp(aa->name, ("--fast"))==0)) blockSize100k = 1; else
      if ((strcmp(aa->name, ("--best"))==0)) blockSize100k = 9; else
      if ((strcmp(aa->name, ("--verbose"))==0)) verbosity++; else
      if ((strcmp(aa->name, ("--help"))==0)) { usage ( progName ); exit ( 0 ); }
         else
         if (strncmp ( aa->name, "--", 2) == 0) {
            fprintf ( stderr, "%s: Bad flag `%s'\n", progName, aa->name );
            usage ( progName );
            exit ( 1 );
         }
   }

   if (verbosity > 4) verbosity = 4;
   if (opMode == 1 && smallMode && blockSize100k > 2)
      blockSize100k = 2;

   if (opMode == 3 && srcMode == 2) {
      fprintf ( stderr, "%s: -c and -t cannot be used together.\n",
                progName );
      exit ( 1 );
   }

   if (srcMode == 2 && numFileNames == 0)
      srcMode = 1;

   if (opMode != 1) blockSize100k = 0;

   if (srcMode == 3) {
      signal (SIGINT, mySignalCatcher);
      signal (SIGTERM, mySignalCatcher);



   }

   if (opMode == 1) {
      if (srcMode == 1) {
         compress ( 0 );
      } else {
         decode = ((Bool)1);
         for (aa = argList; aa != 0; aa = aa->link) {
            if ((strcmp(aa->name, ("--"))==0)) { decode = ((Bool)0); continue; }
            if (aa->name[0] == '-' && decode) continue;
            numFilesProcessed++;
            compress ( aa->name );
         }
      }
   }
   else

   if (opMode == 2) {
      unzFailsExist = ((Bool)0);
      if (srcMode == 1) {
         uncompress ( 0 );
      } else {
         decode = ((Bool)1);
         for (aa = argList; aa != 0; aa = aa->link) {
            if ((strcmp(aa->name, ("--"))==0)) { decode = ((Bool)0); continue; }
            if (aa->name[0] == '-' && decode) continue;
            numFilesProcessed++;
            uncompress ( aa->name );
         }
      }
      if (unzFailsExist) {
         setExit(2);
         exit(exitValue);
      }
   }

   else {
      testFailsExist = ((Bool)0);
      if (srcMode == 1) {
         testf ( 0 );
      } else {
         decode = ((Bool)1);
         for (aa = argList; aa != 0; aa = aa->link) {
            if ((strcmp(aa->name, ("--"))==0)) { decode = ((Bool)0); continue; }
            if (aa->name[0] == '-' && decode) continue;
            numFilesProcessed++;
            testf ( aa->name );
         }
      }
      if (testFailsExist) {
         if (noisy) {
            fprintf ( stderr,
              "\n"
              "You can use the `bzip2recover' program to attempt to recover\n"
              "data from undamaged sections of corrupted files.\n\n"
            );
         }
         setExit(2);
         exit(exitValue);
      }
   }




   aa = argList;
   while (aa != 0) {
      Cell* aa2 = aa->link;
      if (aa->name != 0) free(aa->name);
      free(aa);
      aa = aa2;
   }

   return exitValue;
}
