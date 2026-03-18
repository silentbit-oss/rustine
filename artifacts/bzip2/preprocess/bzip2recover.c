# 0 "/app/subjects/bzip2/bzip2recover.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/bzip2/bzip2recover.c"
# 30 "/app/subjects/bzip2/bzip2recover.c"
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
# 31 "/app/subjects/bzip2/bzip2recover.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/errno.h" 1
# 32 "/app/subjects/bzip2/bzip2recover.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 33 "/app/subjects/bzip2/bzip2recover.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 34 "/app/subjects/bzip2/bzip2recover.c" 2
# 46 "/app/subjects/bzip2/bzip2recover.c"
   typedef unsigned long long int MaybeUInt64;
# 58 "/app/subjects/bzip2/bzip2recover.c"
typedef unsigned int UInt32;
typedef int Int32;
typedef unsigned char UChar;
typedef char Char;
typedef unsigned char Bool;






Char inFileName[2000];
Char outFileName[2000];
Char progName[2000];

MaybeUInt64 bytesOut = 0;
MaybeUInt64 bytesIn = 0;
# 92 "/app/subjects/bzip2/bzip2recover.c"
static void readError ( void )
{
   fprintf ( stderr,
             "%s: I/O error reading `%s', possible reason follows.\n",
            progName, inFileName );
   perror ( progName );
   fprintf ( stderr, "%s: warning: output file(s) may be incomplete.\n",
             progName );
   exit ( 1 );
}



static void writeError ( void )
{
   fprintf ( stderr,
             "%s: I/O error reading `%s', possible reason follows.\n",
            progName, inFileName );
   perror ( progName );
   fprintf ( stderr, "%s: warning: output file(s) may be incomplete.\n",
             progName );
   exit ( 1 );
}



static void mallocFail ( Int32 n )
{
   fprintf ( stderr,
             "%s: malloc failed on request for %d bytes.\n",
            progName, n );
   fprintf ( stderr, "%s: warning: output file(s) may be incomplete.\n",
             progName );
   exit ( 1 );
}



static void tooManyBlocks ( Int32 max_handled_blocks )
{
   fprintf ( stderr,
             "%s: `%s' appears to contain more than %d blocks\n",
            progName, inFileName, max_handled_blocks );
   fprintf ( stderr,
             "%s: and cannot be handled.  To fix, increase\n",
             progName );
   fprintf ( stderr,
             "%s: BZ_MAX_HANDLED_BLOCKS in bzip2recover.c, and recompile.\n",
             progName );
   exit ( 1 );
}







typedef
   struct {
      FILE* handle;
      Int32 buffer;
      Int32 buffLive;
      Char mode;
   }
   BitStream;



static BitStream* bsOpenReadStream ( FILE* stream )
{
   BitStream *bs = malloc ( sizeof(BitStream) );
   if (bs == 0) mallocFail ( sizeof(BitStream) );
   bs->handle = stream;
   bs->buffer = 0;
   bs->buffLive = 0;
   bs->mode = 'r';
   return bs;
}



static BitStream* bsOpenWriteStream ( FILE* stream )
{
   BitStream *bs = malloc ( sizeof(BitStream) );
   if (bs == 0) mallocFail ( sizeof(BitStream) );
   bs->handle = stream;
   bs->buffer = 0;
   bs->buffLive = 0;
   bs->mode = 'w';
   return bs;
}



static void bsPutBit ( BitStream* bs, Int32 bit )
{
   if (bs->buffLive == 8) {
      Int32 retVal = putc ( (UChar) bs->buffer, bs->handle );
      if (retVal == EOF) writeError();
      bytesOut++;
      bs->buffLive = 1;
      bs->buffer = bit & 0x1;
   } else {
      bs->buffer = ( (bs->buffer << 1) | (bit & 0x1) );
      bs->buffLive++;
   };
}






static Int32 bsGetBit ( BitStream* bs )
{
   if (bs->buffLive > 0) {
      bs->buffLive --;
      return ( ((bs->buffer) >> (bs->buffLive)) & 0x1 );
   } else {
      Int32 retVal = getc ( bs->handle );
      if ( retVal == EOF ) {
         if (errno != 0) readError();
         return 2;
      }
      bs->buffLive = 7;
      bs->buffer = retVal;
      return ( ((bs->buffer) >> 7) & 0x1 );
   }
}



static void bsClose ( BitStream* bs )
{
   Int32 retVal;

   if ( bs->mode == 'w' ) {
      while ( bs->buffLive < 8 ) {
         bs->buffLive++;
         bs->buffer <<= 1;
      };
      retVal = putc ( (UChar) (bs->buffer), bs->handle );
      if (retVal == EOF) writeError();
      bytesOut++;
      retVal = fflush ( bs->handle );
      if (retVal == EOF) writeError();
   }
   retVal = fclose ( bs->handle );
   if (retVal == EOF) {
      if (bs->mode == 'w') writeError(); else readError();
   }
   free ( bs );
}



static void bsPutUChar ( BitStream* bs, UChar c )
{
   Int32 i;
   for (i = 7; i >= 0; i--)
      bsPutBit ( bs, (((UInt32) c) >> i) & 0x1 );
}



static void bsPutUInt32 ( BitStream* bs, UInt32 c )
{
   Int32 i;

   for (i = 31; i >= 0; i--)
      bsPutBit ( bs, (c >> i) & 0x1 );
}



static Bool endsInBz2 ( Char* name )
{
   Int32 n = strlen ( name );
   if (n <= 4) return ((Bool)0);
   return
      (name[n-4] == '.' &&
       name[n-3] == 'b' &&
       name[n-2] == 'z' &&
       name[n-1] == '2');
}





static
FILE* fopen_output_safely ( Char* name, const char* mode )
{
# 295 "/app/subjects/bzip2/bzip2recover.c"
   return fopen(name, mode);

}
# 324 "/app/subjects/bzip2/bzip2recover.c"
MaybeUInt64 bStart [50000];
MaybeUInt64 bEnd [50000];
MaybeUInt64 rbStart[50000];
MaybeUInt64 rbEnd [50000];

Int32 main ( Int32 argc, Char** argv )
{
   FILE* inFile;
   FILE* outFile;
   BitStream* bsIn, *bsWr;
   Int32 b, wrBlock, currBlock, rbCtr;
   MaybeUInt64 bitsRead;

   UInt32 buffHi, buffLo, blockCRC;
   Char* p;

   strncpy ( progName, argv[0], 2000 -1);
   progName[2000 -1]='\0';
   inFileName[0] = outFileName[0] = 0;

   fprintf ( stderr,
             "bzip2recover 1.0.6: extracts blocks from damaged .bz2 files.\n" );

   if (argc != 2) {
      fprintf ( stderr, "%s: usage is `%s damaged_file_name'.\n",
                        progName, progName );
      switch (sizeof(MaybeUInt64)) {
         case 8:
            fprintf(stderr,
                    "\trestrictions on size of recovered file: None\n");
            break;
         case 4:
            fprintf(stderr,
                    "\trestrictions on size of recovered file: 512 MB\n");
            fprintf(stderr,
                    "\tto circumvent, recompile with MaybeUInt64 as an\n"
                    "\tunsigned 64-bit int.\n");
            break;
         default:
            fprintf(stderr,
                    "\tsizeof(MaybeUInt64) is not 4 or 8 -- "
                    "configuration error.\n");
            break;
      }
      exit(1);
   }

   if (strlen(argv[1]) >= 2000 -20) {
      fprintf ( stderr,
                "%s: supplied filename is suspiciously (>= %d chars) long.  Bye!\n",
                progName, (int)strlen(argv[1]) );
      exit(1);
   }

   strcpy ( inFileName, argv[1] );

   inFile = fopen ( inFileName, "rb" );
   if (inFile == 0) {
      fprintf ( stderr, "%s: can't read `%s'\n", progName, inFileName );
      exit(1);
   }

   bsIn = bsOpenReadStream ( inFile );
   fprintf ( stderr, "%s: searching for block boundaries ...\n", progName );

   bitsRead = 0;
   buffHi = buffLo = 0;
   currBlock = 0;
   bStart[currBlock] = 0;

   rbCtr = 0;

   while (((Bool)1)) {
      b = bsGetBit ( bsIn );
      bitsRead++;
      if (b == 2) {
         if (bitsRead >= bStart[currBlock] &&
            (bitsRead - bStart[currBlock]) >= 40) {
            bEnd[currBlock] = bitsRead-1;
            if (currBlock > 0)
               fprintf ( stderr, "   block %d runs from " "%Lu"
                                 " to " "%Lu" " (incomplete)\n",
                         currBlock, bStart[currBlock], bEnd[currBlock] );
         } else
            currBlock--;
         break;
      }
      buffHi = (buffHi << 1) | (buffLo >> 31);
      buffLo = (buffLo << 1) | (b & 1);
      if ( ( (buffHi & 0x0000ffff) == 0x00003141UL
             && buffLo == 0x59265359UL)
           ||
           ( (buffHi & 0x0000ffff) == 0x00001772UL
             && buffLo == 0x45385090UL)
         ) {
         if (bitsRead > 49) {
            bEnd[currBlock] = bitsRead-49;
         } else {
            bEnd[currBlock] = 0;
         }
         if (currBlock > 0 &&
             (bEnd[currBlock] - bStart[currBlock]) >= 130) {
            fprintf ( stderr, "   block %d runs from " "%Lu"
                              " to " "%Lu" "\n",
                      rbCtr+1, bStart[currBlock], bEnd[currBlock] );
            rbStart[rbCtr] = bStart[currBlock];
            rbEnd[rbCtr] = bEnd[currBlock];
            rbCtr++;
         }
         if (currBlock >= 50000)
            tooManyBlocks(50000);
         currBlock++;

         bStart[currBlock] = bitsRead;
      }
   }

   bsClose ( bsIn );



   if (rbCtr < 1) {
      fprintf ( stderr,
                "%s: sorry, I couldn't find any block boundaries.\n",
                progName );
      exit(1);
   };

   fprintf ( stderr, "%s: splitting into blocks\n", progName );

   inFile = fopen ( inFileName, "rb" );
   if (inFile == 0) {
      fprintf ( stderr, "%s: can't open `%s'\n", progName, inFileName );
      exit(1);
   }
   bsIn = bsOpenReadStream ( inFile );


   blockCRC = 0; bsWr = 0;

   bitsRead = 0;
   outFile = 0;
   wrBlock = 0;
   while (((Bool)1)) {
      b = bsGetBit(bsIn);
      if (b == 2) break;
      buffHi = (buffHi << 1) | (buffLo >> 31);
      buffLo = (buffLo << 1) | (b & 1);
      if (bitsRead == 47+rbStart[wrBlock])
         blockCRC = (buffHi << 16) | (buffLo >> 16);

      if (outFile != 0 && bitsRead >= rbStart[wrBlock]
                          && bitsRead <= rbEnd[wrBlock]) {
         bsPutBit ( bsWr, b );
      }

      bitsRead++;

      if (bitsRead == rbEnd[wrBlock]+1) {
         if (outFile != 0) {
            bsPutUChar ( bsWr, 0x17 ); bsPutUChar ( bsWr, 0x72 );
            bsPutUChar ( bsWr, 0x45 ); bsPutUChar ( bsWr, 0x38 );
            bsPutUChar ( bsWr, 0x50 ); bsPutUChar ( bsWr, 0x90 );
            bsPutUInt32 ( bsWr, blockCRC );
            bsClose ( bsWr );
            outFile = 0;
         }
         if (wrBlock >= rbCtr) break;
         wrBlock++;
      } else
      if (bitsRead == rbStart[wrBlock]) {


         Char* split;
         Int32 ofs, k;
         for (k = 0; k < 2000; k++)
            outFileName[k] = 0;
         strcpy (outFileName, inFileName);
         split = strrchr (outFileName, '/');
         if (split == 0) {
            split = outFileName;
         } else {
            ++split;
         }

         ofs = split - outFileName;
         sprintf (split, "rec%5d", wrBlock+1);
         for (p = split; *p != 0; p++) if (*p == ' ') *p = '0';
         strcat (outFileName, inFileName + ofs);

         if ( !endsInBz2(outFileName)) strcat ( outFileName, ".bz2" );

         fprintf ( stderr, "   writing block %d to `%s' ...\n",
                           wrBlock+1, outFileName );

         outFile = fopen_output_safely ( outFileName, "wb" );
         if (outFile == 0) {
            fprintf ( stderr, "%s: can't write `%s'\n",
                      progName, outFileName );
            exit(1);
         }
         bsWr = bsOpenWriteStream ( outFile );
         bsPutUChar ( bsWr, 0x42 );
         bsPutUChar ( bsWr, 0x5a );
         bsPutUChar ( bsWr, 0x68 );
         bsPutUChar ( bsWr, 0x30 + 9 );
         bsPutUChar ( bsWr, 0x31 ); bsPutUChar ( bsWr, 0x41 );
         bsPutUChar ( bsWr, 0x59 ); bsPutUChar ( bsWr, 0x26 );
         bsPutUChar ( bsWr, 0x53 ); bsPutUChar ( bsWr, 0x59 );
      }
   }

   fprintf ( stderr, "%s: finished\n", progName );
   return 0;
}
