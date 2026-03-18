#include <bzlib.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
  char *next_in;
  unsigned int avail_in;
  unsigned int total_in_lo32;
  unsigned int total_in_hi32;
  char *next_out;
  unsigned int avail_out;
  unsigned int total_out_lo32;
  unsigned int total_out_hi32;
  void *state;
  void *(*bzalloc)(void *, int, int);
  void (*bzfree)(void *, void *);
  void *opaque;
} bz_stream;
extern int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor);
extern int BZ2_bzCompress(bz_stream *strm, int action);
extern int BZ2_bzCompressEnd(bz_stream *strm);
extern int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small);
extern int BZ2_bzDecompress(bz_stream *strm);
extern int BZ2_bzDecompressEnd(bz_stream *strm);
typedef void BZFILE;
extern BZFILE *BZ2_bzReadOpen(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused);
extern void BZ2_bzReadClose(int *bzerror, BZFILE *b);
extern void BZ2_bzReadGetUnused(int *bzerror, BZFILE *b, void **unused, int *nUnused);
extern int BZ2_bzRead(int *bzerror, BZFILE *b, void *buf, int len);
extern BZFILE *BZ2_bzWriteOpen(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor);
extern void BZ2_bzWrite(int *bzerror, BZFILE *b, void *buf, int len);
extern void BZ2_bzWriteClose(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in, unsigned int *nbytes_out);
extern void BZ2_bzWriteClose64(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32, unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32);
extern int BZ2_bzBuffToBuffCompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int blockSize100k, int verbosity, int workFactor);
extern int BZ2_bzBuffToBuffDecompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int small, int verbosity);
extern const char *BZ2_bzlibVersion(void);
extern BZFILE *BZ2_bzopen(const char *path, const char *mode);
extern BZFILE *BZ2_bzdopen(int fd, const char *mode);
extern int BZ2_bzread(BZFILE *b, void *buf, int len);
extern int BZ2_bzwrite(BZFILE *b, void *buf, int len);
extern int BZ2_bzflush(BZFILE *b);
extern void BZ2_bzclose(BZFILE *b);
extern const char *BZ2_bzerror(BZFILE *b, int *errnum);
typedef char Char;
typedef unsigned char Bool;
typedef unsigned char UChar;
typedef int Int32;
typedef unsigned int UInt32;
typedef short Int16;
typedef unsigned short UInt16;
typedef int IntNative;
Int32 verbosity;
Bool keepInputFiles;
Bool smallMode;
Bool deleteOutputOnInterrupt;
Bool forceOverwrite;
Bool testFailsExist;
Bool unzFailsExist;
Bool noisy;
Int32 numFileNames;
Int32 numFilesProcessed;
Int32 blockSize100k;
Int32 exitValue;
Int32 opMode;
Int32 srcMode;
Int32 longestFileName;
Char inName[1034];
Char outName[1034];
Char tmpName[1034];
Char *progName;
Char progNameReally[1034];
FILE *outputHandleJustInCase;
Int32 workFactor;
static void panic(const Char *);
static void ioError(void);
static void outOfMemory(void);
static void configError(void);
static void crcError(void);
static void cleanUpAndFail(Int32);
static void compressedStreamEOF(void);
static void copyFileName(Char *, Char *);
static void *myMalloc(Int32);
static void applySavedFileAttrToOutputFile(IntNative fd);
typedef struct 
{
  UChar b[8];
} UInt64;
static void uInt64_from_UInt32s(UInt64 *n, UInt32 lo32, UInt32 hi32)
{
  n->b[7] = (UChar) ((hi32 >> 24) & 0xFF);
  n->b[6] = (UChar) ((hi32 >> 16) & 0xFF);
  n->b[5] = (UChar) ((hi32 >> 8) & 0xFF);
  n->b[4] = (UChar) (hi32 & 0xFF);
  n->b[3] = (UChar) ((lo32 >> 24) & 0xFF);
  n->b[2] = (UChar) ((lo32 >> 16) & 0xFF);
  n->b[1] = (UChar) ((lo32 >> 8) & 0xFF);
  n->b[0] = (UChar) (lo32 & 0xFF);
}

static double uInt64_to_double(UInt64 *n)
{
  Int32 i;
  double base = 1.0;
  double sum = 0.0;
  for (i = 0; i < 8; i += 1)
  {
    sum += base * ((double) n->b[i]);
    base *= 256.0;
  }

  return sum;
}

static Bool uInt64_isZero(UInt64 *n)
{
  Int32 i;
  for (i = 0; i < 8; i += 1)
  {
    if (n->b[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}

static Int32 uInt64_qrm10(UInt64 *n)
{
  UInt32 rem;
  UInt32 tmp;
  Int32 i;
  rem = 0;
  for (i = 7; i >= 0; i -= 1)
  {
    tmp = (rem * 256) + n->b[i];
    n->b[i] = tmp / 10;
    rem = tmp % 10;
  }

  return rem;
}

static void uInt64_toAscii(char *outbuf, UInt64 *n)
{
  Int32 i;
  Int32 q;
  UChar buf[32];
  Int32 nBuf = 0;
  UInt64 n_copy = *n;
  do
  {
    q = uInt64_qrm10(&n_copy);
    buf[nBuf] = q + '0';
    nBuf += 1;
  }
  while (!uInt64_isZero(&n_copy));
  outbuf[nBuf] = 0;
  for (i = 0; i < nBuf; i += 1)
  {
    outbuf[i] = buf[(nBuf - i) - 1];
  }

}

static Bool myfeof(FILE *f)
{
  Int32 c = fgetc(f);
  if (c == EOF)
  {
    return (Bool) 1;
  }
  ungetc(c, f);
  return (Bool) 0;
}

static void compressStream(FILE *stream, FILE *zStream)
{
  BZFILE *bzf = 0;
  unsigned int bzf_idx = 0;
  UChar ibuf[5000];
  Int32 nIbuf;
  UInt32 nbytes_in_lo32;
  UInt32 nbytes_in_hi32;
  UInt32 nbytes_out_lo32;
  UInt32 nbytes_out_hi32;
  Int32 bzerr;
  Int32 bzerr_dummy;
  Int32 ret;
  SET_BINARY_MODE(stream);
  SET_BINARY_MODE(zStream);
  if (ferror(stream))
  {
    goto errhandler_io;
  }
  if (ferror(zStream))
  {
    goto errhandler_io;
  }
  bzf_idx = BZ2_bzWriteOpen(&bzerr, zStream, blockSize100k, verbosity, workFactor);
  if (bzerr != 0)
  {
    goto errhandler;
  }
  if (verbosity >= 2)
  {
    fprintf(stderr, "\n");
  }
  while ((Bool) 1)
  {
    if (myfeof(stream))
    {
      break;
    }
    nIbuf = fread(ibuf, sizeof(UChar), 5000, stream);
    if (ferror(stream))
    {
      goto errhandler_io;
    }
    if (nIbuf > 0)
    {
      BZ2_bzWrite(&bzerr, bzf, (void *) ibuf, nIbuf);
    }
    if (bzerr != 0)
    {
      goto errhandler;
    }
  }

  BZ2_bzWriteClose64(&bzerr, bzf, 0, &nbytes_in_lo32, &nbytes_in_hi32, &nbytes_out_lo32, &nbytes_out_hi32);
  if (bzerr != 0)
  {
    goto errhandler;
  }
  if (ferror(zStream))
  {
    goto errhandler_io;
  }
  ret = fflush(zStream);
  if (ret == EOF)
  {
    goto errhandler_io;
  }
  if (zStream != stdout)
  {
    Int32 fd = fileno(zStream);
    if (fd < 0)
    {
      goto errhandler_io;
    }
    applySavedFileAttrToOutputFile(fd);
    ret = fclose(zStream);
    outputHandleJustInCase = 0;
    if (ret == EOF)
    {
      goto errhandler_io;
    }
  }
  outputHandleJustInCase = 0;
  if (ferror(stream))
  {
    goto errhandler_io;
  }
  ret = fclose(stream);
  if (ret == EOF)
  {
    goto errhandler_io;
  }
  if (verbosity >= 1)
  {
    helper_compressStream_1(nbytes_in_lo32, nbytes_in_hi32, nbytes_out_lo32, nbytes_out_hi32);
  }
  return;
  errhandler:
  BZ2_bzWriteClose64(&bzerr_dummy, bzf, 1, &nbytes_in_lo32, &nbytes_in_hi32, &nbytes_out_lo32, &nbytes_out_hi32);

  switch (bzerr)
  {
    case -9:
    {
      configError();
      break;
    }

    case -3:
    {
      outOfMemory();
      break;
    }

    case -6:
    {
      errhandler_io:
      ioError();

      break;
    }

    default:
    {
      panic("compress:unexpected error");
    }

  }

  panic("compress:end");
}

static Bool uncompressStream(FILE *zStream, FILE *stream)
{
  BZFILE *bzf = 0;
  unsigned int bzf_idx = 0;
  Int32 bzerr;
  Int32 bzerr_dummy;
  Int32 ret;
  Int32 nread;
  Int32 streamNo;
  Int32 i;
  UChar obuf[5000];
  UChar unused[5000];
  Int32 nUnused;
  void *unusedTmpV;
  UChar *unusedTmp;
  unsigned int unusedTmp_idx = 0;
  nUnused = 0;
  streamNo = 0;
  SET_BINARY_MODE(stream);
  SET_BINARY_MODE(zStream);
  if (ferror(stream))
  {
    goto errhandler_io;
  }
  if (ferror(zStream))
  {
    goto errhandler_io;
  }
  while ((Bool) 1)
  {
    helper_uncompressStream_2(&bzf_idx, &nread, &streamNo, &i, &unusedTmp_idx, zStream, stream, bzf, bzerr, obuf, unused, nUnused, unusedTmpV, unusedTmp);
  }

  closeok:
  if (ferror(zStream))
  {
    goto errhandler_io;
  }

  if (stream != stdout)
  {
    Int32 fd = fileno(stream);
    if (fd < 0)
    {
      goto errhandler_io;
    }
    applySavedFileAttrToOutputFile(fd);
  }
  ret = fclose(zStream);
  if (ret == EOF)
  {
    goto errhandler_io;
  }
  if (ferror(stream))
  {
    goto errhandler_io;
  }
  ret = fflush(stream);
  if (ret != 0)
  {
    goto errhandler_io;
  }
  if (stream != stdout)
  {
    ret = fclose(stream);
    outputHandleJustInCase = 0;
    if (ret == EOF)
    {
      goto errhandler_io;
    }
  }
  outputHandleJustInCase = 0;
  if (verbosity >= 2)
  {
    fprintf(stderr, "\n    ");
  }
  return (Bool) 1;
  trycat:
  if (forceOverwrite)
  {
    helper_uncompressStream_1(&nread, zStream, stream, obuf);
  }

  errhandler:
  BZ2_bzReadClose(&bzerr_dummy, bzf);

  switch (bzerr)
  {
    case -9:
    {
      configError();
      break;
    }

    case -6:
    {
      errhandler_io:
      ioError();

      break;
    }

    case -4:
    {
      crcError();
    }

    case -3:
    {
      outOfMemory();
    }

    case -7:
    {
      compressedStreamEOF();
    }

    case -5:
    {
      if (zStream != stdin)
      {
        fclose(zStream);
      }
      if (stream != stdout)
      {
        fclose(stream);
      }
      if (streamNo == 1)
      {
        return (Bool) 0;
      }
      else
      {
        if (noisy)
        {
          fprintf(stderr, "\n%s: %s: trailing garbage after EOF ignored\n", progName, inName);
        }
        return (Bool) 1;
      }
    }

    default:
    {
      panic("decompress:unexpected error");
    }

  }

  panic("decompress:end");
  return (Bool) 1;
}

static Bool testStream(FILE *zStream)
{
  BZFILE *bzf = 0;
  unsigned int bzf_idx = 0;
  Int32 bzerr;
  Int32 bzerr_dummy;
  Int32 ret;
  Int32 streamNo;
  Int32 i;
  UChar obuf[5000];
  UChar unused[5000];
  Int32 nUnused;
  void *unusedTmpV;
  UChar *unusedTmp;
  unsigned int unusedTmp_idx = 0;
  nUnused = 0;
  streamNo = 0;
  SET_BINARY_MODE(zStream);
  if (ferror(zStream))
  {
    goto errhandler_io;
  }
  while ((Bool) 1)
  {
    helper_testStream_1(&bzf_idx, &streamNo, &i, &unusedTmp_idx, zStream, bzf, bzerr, obuf, unused, nUnused, unusedTmpV, unusedTmp);
  }

  if (ferror(zStream))
  {
    goto errhandler_io;
  }
  ret = fclose(zStream);
  if (ret == EOF)
  {
    goto errhandler_io;
  }
  if (verbosity >= 2)
  {
    fprintf(stderr, "\n    ");
  }
  return (Bool) 1;
  errhandler:
  BZ2_bzReadClose(&bzerr_dummy, bzf);

  if (verbosity == 0)
  {
    fprintf(stderr, "%s: %s: ", progName, inName);
  }
  switch (bzerr)
  {
    case -9:
    {
      configError();
      break;
    }

    case -6:
    {
      errhandler_io:
      ioError();

      break;
    }

    case -4:
    {
      fprintf(stderr, "data integrity (CRC) error in data\n");
      return (Bool) 0;
    }

    case -3:
    {
      outOfMemory();
    }

    case -7:
    {
      fprintf(stderr, "file ends unexpectedly\n");
      return (Bool) 0;
    }

    case -5:
    {
      if (zStream != stdin)
      {
        fclose(zStream);
      }
      if (streamNo == 1)
      {
        fprintf(stderr, "bad magic number (file not created by bzip2)\n");
        return (Bool) 0;
      }
      else
      {
        if (noisy)
        {
          fprintf(stderr, "trailing garbage after EOF ignored\n");
        }
        return (Bool) 1;
      }
    }

    default:
    {
      panic("test:unexpected error");
    }

  }

  panic("test:end");
  return (Bool) 1;
}

static void setExit(Int32 v)
{
  if (v > exitValue)
  {
    exitValue = v;
  }
}

static void cadvise(void)
{
  if (noisy)
  {
    fprintf(stderr, "\nIt is possible that the compressed file(s) have become corrupted.\nYou can use the -tvv option to test integrity of such files.\n\nYou can use the `bzip2recover' program to attempt to recover\ndata from undamaged sections of corrupted files.\n\n");
  }
}

static void showFileNames(void)
{
  if (noisy)
  {
    fprintf(stderr, "\tInput file = %s, output file = %s\n", inName, outName);
  }
}

static void cleanUpAndFail(Int32 ec)
{
  IntNative retVal;
  struct MY_STAT statBuf;
  if (((srcMode == 3) && (opMode != 3)) && deleteOutputOnInterrupt)
  {
    retVal = MY_STAT(inName, &statBuf);
    if (retVal == 0)
    {
      if (noisy)
      {
        fprintf(stderr, "%s: Deleting output file %s, if it exists.\n", progName, outName);
      }
      if (outputHandleJustInCase != 0)
      {
        fclose(outputHandleJustInCase);
      }
      retVal = remove(outName);
      if (retVal != 0)
      {
        fprintf(stderr, "%s: WARNING: deletion of output file (apparently) failed.\n", progName);
      }
    }
    else
    {
      fprintf(stderr, "%s: WARNING: deletion of output file suppressed\n", progName);
      fprintf(stderr, "%s:    since input file no longer exists.  Output file\n", progName);
      fprintf(stderr, "%s:    `%s' may be incomplete.\n", progName, outName);
      fprintf(stderr, "%s:    I suggest doing an integrity test (bzip2 -tv) of it.\n", progName);
    }
  }
  if ((noisy && (numFileNames > 0)) && (numFilesProcessed < numFileNames))
  {
    fprintf(stderr, "%s: WARNING: some files have not been processed:\n%s:    %d specified on command line, %d not processed yet.\n\n", progName, progName, numFileNames, numFileNames - numFilesProcessed);
  }
  setExit(ec);
  exit(exitValue);
}

static void panic(const Char *s)
{
  fprintf(stderr, "\n%s: PANIC -- internal consistency error:\n\t%s\n\tThis is a BUG.  Please report it at:\n\thttps://gitlab.com/bzip2/bzip2/-/issues\n", progName, s);
  showFileNames();
  cleanUpAndFail(3);
}

static void crcError(void)
{
  fprintf(stderr, "\n%s: Data integrity error when decompressing.\n", progName);
  showFileNames();
  cadvise();
  cleanUpAndFail(2);
}

static void compressedStreamEOF(void)
{
  if (noisy)
  {
    fprintf(stderr, "\n%s: Compressed file ends unexpectedly;\n\tperhaps it is corrupted?  *Possible* reason follows.\n", progName);
    perror(progName);
    showFileNames();
    cadvise();
  }
  cleanUpAndFail(2);
}

static void ioError(void)
{
  fprintf(stderr, "\n%s: I/O or other error, bailing out.  Possible reason follows.\n", progName);
  perror(progName);
  showFileNames();
  cleanUpAndFail(1);
}

static void mySignalCatcher(IntNative n)
{
  fprintf(stderr, "\n%s: Control-C or similar caught, quitting.\n", progName);
  cleanUpAndFail(1);
}

static void mySIGSEGVorSIGBUScatcher(IntNative n)
{
  const char *msg;
  unsigned int msg_idx = 0;
  if (opMode == 1)
  {
    msg_idx = ": Caught a SIGSEGV or SIGBUS whilst compressing.\n\n   Possible causes are (most likely first):\n   (1) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (2) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (3) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (1) and (2).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (1)\n   or (2), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n";
  }
  else
    msg_idx = ": Caught a SIGSEGV or SIGBUS whilst decompressing.\n\n   Possible causes are (most likely first):\n   (1) The compressed data is corrupted, and bzip2's usual checks\n       failed to detect this.  Try bzip2 -tvv my_file.bz2.\n   (2) This computer has unreliable memory or cache hardware\n       (a surprisingly common problem; try a different machine.)\n   (3) A bug in the compiler used to create this executable\n       (unlikely, if you didn't compile bzip2 yourself.)\n   (4) A real bug in bzip2 -- I hope this should never be the case.\n   The user's manual, Section 4.3, has more info on (2) and (3).\n   \n   If you suspect this is a bug in bzip2, or are unsure about (2)\n   or (3), report it at: https://gitlab.com/bzip2/bzip2/-/issues\n   Section 4.3 of the user's manual describes the info a useful\n   bug report should have.  If the manual is available on your\n   system, please try and read it before mailing me.  If you don't\n   have the manual or can't be bothered to read it, mail me anyway.\n\n";
  write(STDERR_FILENO, "\n", 1);
  write(STDERR_FILENO, progName, strlen(progName));
  write(STDERR_FILENO, msg, strlen(msg));
  msg_idx = "\tInput file = ";
  write(STDERR_FILENO, msg, strlen(msg));
  write(STDERR_FILENO, inName, strlen(inName));
  write(STDERR_FILENO, "\n", 1);
  msg_idx = "\tOutput file = ";
  write(STDERR_FILENO, msg, strlen(msg));
  write(STDERR_FILENO, outName, strlen(outName));
  write(STDERR_FILENO, "\n", 1);
  if (opMode == 1)
  {
    setExit(3);
  }
  else
    setExit(2);
  _exit(exitValue);
}

static void outOfMemory(void)
{
  fprintf(stderr, "\n%s: couldn't allocate enough memory\n", progName);
  showFileNames();
  cleanUpAndFail(1);
}

static void configError(void)
{
  fprintf(stderr, "bzip2: I'm not configured correctly for this platform!\n\tI require Int32, Int16 and Char to have sizes\n\tof 4, 2 and 1 bytes to run properly, and they don't.\n\tProbably you can fix this by defining them correctly,\n\tand recompiling.  Bye!\n");
  setExit(3);
  exit(exitValue);
}

static void pad(Char *s)
{
  Int32 i;
  if (((Int32) strlen(s)) >= longestFileName)
  {
    return;
  }
  for (i = 1; i <= (longestFileName - ((Int32) strlen(s))); i += 1)
  {
    fprintf(stderr, " ");
  }

}

static void copyFileName(Char *to, Char *from)
{
  if (strlen(from) > (1034 - 10))
  {
    fprintf(stderr, "bzip2: file name\n`%s'\nis suspiciously (more than %d chars) long.\nTry using a reasonable file name instead.  Sorry! :-)\n", from, 1034 - 10);
    setExit(1);
    exit(exitValue);
  }
  strncpy(to, from, 1034 - 10);
  to[1034 - 10] = '\0';
}

static Bool fileExists(Char *name)
{
  FILE *tmp = fopen(name, "rb");
  Bool exists = tmp != 0;
  if (tmp != 0)
  {
    fclose(tmp);
  }
  return exists;
}

static FILE *fopen_output_safely(Char *name, const char *mode)
{
  return fopen(name, mode);
}

static Bool notAStandardFile(Char *name)
{
  IntNative i;
  struct MY_STAT statBuf;
  i = MY_LSTAT(name, &statBuf);
  if (i != 0)
  {
    return (Bool) 1;
  }
  if (MY_S_ISREG(statBuf.st_mode))
  {
    return (Bool) 0;
  }
  return (Bool) 1;
}

static Int32 countHardLinks(Char *name)
{
  IntNative i;
  struct MY_STAT statBuf;
  i = MY_LSTAT(name, &statBuf);
  if (i != 0)
  {
    return 0;
  }
  return statBuf.st_nlink - 1;
}

static void saveInputFileMetaInfo(Char *srcName)
{
}

static void applySavedTimeInfoToOutputFile(Char *dstName)
{
}

static void applySavedFileAttrToOutputFile(IntNative fd)
{
}

static Bool containsDubiousChars(Char *name)
{
  unsigned int name_idx = 0;
  for (; name[name_idx] != '\0'; name_idx += 1)
  {
    if ((name[name_idx] == '?') || (name[name_idx] == '*'))
    {
      return (Bool) 1;
    }
  }

  return (Bool) 0;
}

const Char *zSuffix[4] = {".bz2", ".bz", ".tbz2", ".tbz"};
const Char *unzSuffix[4] = {"", "", ".tar", ".tar"};
static Bool hasSuffix(Char *s, const Char *suffix)
{
  Int32 ns = strlen(s);
  Int32 nx = strlen(suffix);
  if (ns < nx)
  {
    return (Bool) 0;
  }
  if (strcmp((s + ns) - nx, suffix) == 0)
  {
    return (Bool) 1;
  }
  return (Bool) 0;
}

static Bool mapSuffix(Char *name, const Char *oldSuffix, const Char *newSuffix)
{
  if (!hasSuffix(name, oldSuffix))
  {
    return (Bool) 0;
  }
  name[strlen(name) - strlen(oldSuffix)] = 0;
  strcat(name, newSuffix);
  return (Bool) 1;
}

static void compress(Char *name)
{
  FILE *inStr;
  unsigned int inStr_idx = 0;
  FILE *outStr;
  unsigned int outStr_idx = 0;
  Int32 n;
  Int32 i;
  struct MY_STAT statBuf;
  deleteOutputOnInterrupt = (Bool) 0;
  if ((name == 0) && (srcMode != 1))
  {
    panic("compress: bad modes\n");
  }
  switch (srcMode)
  {
    case 1:
    {
      copyFileName(inName, (Char *) "(stdin)");
      copyFileName(outName, (Char *) "(stdout)");
      break;
    }

    case 3:
    {
      copyFileName(inName, name);
      copyFileName(outName, name);
      strcat(outName, ".bz2");
      break;
    }

    case 2:
    {
      copyFileName(inName, name);
      copyFileName(outName, (Char *) "(stdout)");
      break;
    }

  }

  if ((srcMode != 1) && containsDubiousChars(inName))
  {
    if (noisy)
    {
      fprintf(stderr, "%s: There are no files matching `%s'.\n", progName, inName);
    }
    setExit(1);
    return;
  }
  if ((srcMode != 1) && (!fileExists(inName)))
  {
    fprintf(stderr, "%s: Can't open input file %s: %s.\n", progName, inName, strerror(errno));
    setExit(1);
    return;
  }
  for (i = 0; i < 4; i += 1)
  {
    if (hasSuffix(inName, zSuffix[i]))
    {
      if (noisy)
      {
        fprintf(stderr, "%s: Input file %s already has %s suffix.\n", progName, inName, zSuffix[i]);
      }
      setExit(1);
      return;
    }
  }

  if ((srcMode == 3) || (srcMode == 2))
  {
    MY_STAT(inName, &statBuf);
    if (MY_S_ISDIR(statBuf.st_mode))
    {
      fprintf(stderr, "%s: Input file %s is a directory.\n", progName, inName);
      setExit(1);
      return;
    }
  }
  if (((srcMode == 3) && (!forceOverwrite)) && notAStandardFile(inName))
  {
    if (noisy)
    {
      fprintf(stderr, "%s: Input file %s is not a normal file.\n", progName, inName);
    }
    setExit(1);
    return;
  }
  if ((srcMode == 3) && fileExists(outName))
  {
    if (forceOverwrite)
    {
      remove(outName);
    }
    else
    {
      fprintf(stderr, "%s: Output file %s already exists.\n", progName, outName);
      setExit(1);
      return;
    }
  }
  if (((srcMode == 3) && (!forceOverwrite)) && ((n = countHardLinks(inName)) > 0))
  {
    fprintf(stderr, "%s: Input file %s has %d other link%s.\n", progName, inName, n, (n > 1) ? ("s") : (""));
    setExit(1);
    return;
  }
  if (srcMode == 3)
  {
    saveInputFileMetaInfo(inName);
  }
  switch (srcMode)
  {
    case 1:
    {
      inStr_idx = stdin;
      outStr_idx = stdout;
      if (isatty(fileno(stdout)))
      {
        fprintf(stderr, "%s: I won't write compressed data to a terminal.\n", progName);
        fprintf(stderr, "%s: For help, type: `%s --help'.\n", progName, progName);
        setExit(1);
        return;
      }
      ;
      break;
    }

    case 2:
    {
      helper_compress_1(&inStr_idx, &outStr_idx, inStr);
    }

    case 3:
    {
      helper_compress_2(&inStr_idx, &outStr_idx, inStr, outStr);
    }

    default:
    {
      panic("compress: bad srcMode");
      break;
    }

  }

  if (verbosity >= 1)
  {
    fprintf(stderr, "  %s: ", inName);
    pad(inName);
    fflush(stderr);
  }
  outputHandleJustInCase = &outStr[outStr_idx];
  deleteOutputOnInterrupt = (Bool) 1;
  compressStream(inStr, outStr);
  outputHandleJustInCase = 0;
  if (srcMode == 3)
  {
    applySavedTimeInfoToOutputFile(outName);
    deleteOutputOnInterrupt = (Bool) 0;
    if (!keepInputFiles)
    {
      IntNative retVal = remove(inName);
      {
        if (retVal != 0)
        {
          ioError();
        }
      }
      ;
    }
  }
  deleteOutputOnInterrupt = (Bool) 0;
}

static void uncompress(Char *name)
{
  FILE *inStr;
  unsigned int inStr_idx = 0;
  FILE *outStr;
  unsigned int outStr_idx = 0;
  Int32 n;
  Int32 i;
  Bool magicNumberOK;
  Bool cantGuess;
  struct MY_STAT statBuf;
  deleteOutputOnInterrupt = (Bool) 0;
  if ((name == 0) && (srcMode != 1))
  {
    panic("uncompress: bad modes\n");
  }
  cantGuess = (Bool) 0;
  switch (srcMode)
  {
    case 1:
    {
      copyFileName(inName, (Char *) "(stdin)");
      copyFileName(outName, (Char *) "(stdout)");
      break;
    }

    case 3:
    {
      copyFileName(inName, name);
      copyFileName(outName, name);
      for (i = 0; i < 4; i += 1)
      {
        if (mapSuffix(outName, zSuffix[i], unzSuffix[i]))
        {
          goto zzz;
        }
      }

      cantGuess = (Bool) 1;
      strcat(outName, ".out");
      break;
    }

    case 2:
    {
      copyFileName(inName, name);
      copyFileName(outName, (Char *) "(stdout)");
      break;
    }

  }

  zzz:
  if ((srcMode != 1) && containsDubiousChars(inName))
  {
    if (noisy)
    {
      fprintf(stderr, "%s: There are no files matching `%s'.\n", progName, inName);
    }
    setExit(1);
    return;
  }

  if ((srcMode != 1) && (!fileExists(inName)))
  {
    fprintf(stderr, "%s: Can't open input file %s: %s.\n", progName, inName, strerror(errno));
    setExit(1);
    return;
  }
  if ((srcMode == 3) || (srcMode == 2))
  {
    MY_STAT(inName, &statBuf);
    if (MY_S_ISDIR(statBuf.st_mode))
    {
      fprintf(stderr, "%s: Input file %s is a directory.\n", progName, inName);
      setExit(1);
      return;
    }
  }
  if (((srcMode == 3) && (!forceOverwrite)) && notAStandardFile(inName))
  {
    if (noisy)
    {
      fprintf(stderr, "%s: Input file %s is not a normal file.\n", progName, inName);
    }
    setExit(1);
    return;
  }
  if (cantGuess)
  {
    if (noisy)
    {
      fprintf(stderr, "%s: Can't guess original name for %s -- using %s\n", progName, inName, outName);
    }
  }
  if ((srcMode == 3) && fileExists(outName))
  {
    if (forceOverwrite)
    {
      remove(outName);
    }
    else
    {
      fprintf(stderr, "%s: Output file %s already exists.\n", progName, outName);
      setExit(1);
      return;
    }
  }
  if (((srcMode == 3) && (!forceOverwrite)) && ((n = countHardLinks(inName)) > 0))
  {
    fprintf(stderr, "%s: Input file %s has %d other link%s.\n", progName, inName, n, (n > 1) ? ("s") : (""));
    setExit(1);
    return;
  }
  if (srcMode == 3)
  {
    saveInputFileMetaInfo(inName);
  }
  switch (srcMode)
  {
    case 1:
    {
      inStr_idx = stdin;
      outStr_idx = stdout;
      if (isatty(fileno(stdin)))
      {
        fprintf(stderr, "%s: I won't read compressed data from a terminal.\n", progName);
        fprintf(stderr, "%s: For help, type: `%s --help'.\n", progName, progName);
        setExit(1);
        return;
      }
      ;
      break;
    }

    case 2:
    {
      inStr_idx = fopen(inName, "rb");
      outStr_idx = stdout;
      if ((&inStr[inStr_idx]) == 0)
      {
        fprintf(stderr, "%s: Can't open input file %s:%s.\n", progName, inName, strerror(errno));
        if ((&inStr[inStr_idx]) != 0)
        {
          fclose(inStr);
        }
        setExit(1);
        return;
      }
      ;
      break;
    }

    case 3:
    {
      helper_uncompress_1(&inStr_idx, &outStr_idx, inStr, outStr);
    }

    default:
    {
      panic("uncompress: bad srcMode");
      break;
    }

  }

  if (verbosity >= 1)
  {
    fprintf(stderr, "  %s: ", inName);
    pad(inName);
    fflush(stderr);
  }
  outputHandleJustInCase = &outStr[outStr_idx];
  deleteOutputOnInterrupt = (Bool) 1;
  magicNumberOK = uncompressStream(inStr, outStr);
  outputHandleJustInCase = 0;
  if (magicNumberOK)
  {
    if (srcMode == 3)
    {
      applySavedTimeInfoToOutputFile(outName);
      deleteOutputOnInterrupt = (Bool) 0;
      if (!keepInputFiles)
      {
        IntNative retVal = remove(inName);
        {
          if (retVal != 0)
          {
            ioError();
          }
        }
        ;
      }
    }
  }
  else
  {
    unzFailsExist = (Bool) 1;
    deleteOutputOnInterrupt = (Bool) 0;
    if (srcMode == 3)
    {
      IntNative retVal = remove(outName);
      {
        if (retVal != 0)
        {
          ioError();
        }
      }
      ;
    }
  }
  deleteOutputOnInterrupt = (Bool) 0;
  if (magicNumberOK)
  {
    if (verbosity >= 1)
    {
      fprintf(stderr, "done\n");
    }
  }
  else
  {
    setExit(2);
    if (verbosity >= 1)
    {
      fprintf(stderr, "not a bzip2 file.\n");
    }
    else
      fprintf(stderr, "%s: %s is not a bzip2 file.\n", progName, inName);
  }
}

static void testf(Char *name)
{
  FILE *inStr;
  unsigned int inStr_idx = 0;
  Bool allOK;
  struct MY_STAT statBuf;
  deleteOutputOnInterrupt = (Bool) 0;
  if ((name == 0) && (srcMode != 1))
  {
    panic("testf: bad modes\n");
  }
  copyFileName(outName, (Char *) "(none)");
  switch (srcMode)
  {
    case 1:
    {
      copyFileName(inName, (Char *) "(stdin)");
      break;
    }

    case 3:
    {
      copyFileName(inName, name);
      break;
    }

    case 2:
    {
      copyFileName(inName, name);
      break;
    }

  }

  if ((srcMode != 1) && containsDubiousChars(inName))
  {
    if (noisy)
    {
      fprintf(stderr, "%s: There are no files matching `%s'.\n", progName, inName);
    }
    setExit(1);
    return;
  }
  if ((srcMode != 1) && (!fileExists(inName)))
  {
    fprintf(stderr, "%s: Can't open input %s: %s.\n", progName, inName, strerror(errno));
    setExit(1);
    return;
  }
  if (srcMode != 1)
  {
    MY_STAT(inName, &statBuf);
    if (MY_S_ISDIR(statBuf.st_mode))
    {
      fprintf(stderr, "%s: Input file %s is a directory.\n", progName, inName);
      setExit(1);
      return;
    }
  }
  switch (srcMode)
  {
    case 1:
    {
      if (isatty(fileno(stdin)))
      {
        fprintf(stderr, "%s: I won't read compressed data from a terminal.\n", progName);
        fprintf(stderr, "%s: For help, type: `%s --help'.\n", progName, progName);
        setExit(1);
        return;
      }
      ;
      inStr_idx = stdin;
      break;
    }

    case 2:

    case 3:
    {
      inStr_idx = fopen(inName, "rb");
      if ((&inStr[inStr_idx]) == 0)
      {
        fprintf(stderr, "%s: Can't open input file %s:%s.\n", progName, inName, strerror(errno));
        setExit(1);
        return;
      }
      ;
      break;
    }

    default:
    {
      panic("testf: bad srcMode");
      break;
    }

  }

  if (verbosity >= 1)
  {
    fprintf(stderr, "  %s: ", inName);
    pad(inName);
    fflush(stderr);
  }
  outputHandleJustInCase = 0;
  allOK = testStream(inStr);
  if (allOK && (verbosity >= 1))
  {
    fprintf(stderr, "ok\n");
  }
  if (!allOK)
  {
    testFailsExist = (Bool) 1;
  }
}

static void license(void)
{
  fprintf(stdout, "bzip2, a block-sorting file compressor.  Version %s.\n   \n   Copyright (C) 1996-2010 by Julian Seward.\n   \n   This program is free software; you can redistribute it and/or modify\n   it under the terms set out in the LICENSE file, which is included\n   in the bzip2-1.0.6 source distribution.\n   \n   This program is distributed in the hope that it will be useful,\n   but WITHOUT ANY WARRANTY; without even the implied warranty of\n   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n   LICENSE file for more details.\n   \n", BZ2_bzlibVersion());
}

static void usage(Char *fullProgName)
{
  fprintf(stderr, "bzip2, a block-sorting file compressor.  Version %s.\n\n   usage: %s [flags and input files in any order]\n\n   -h --help           print this message\n   -d --decompress     force decompression\n   -z --compress       force compression\n   -k --keep           keep (don't delete) input files\n   -f --force          overwrite existing output files\n   -t --test           test compressed file integrity\n   -c --stdout         output to standard out\n   -q --quiet          suppress noncritical error messages\n   -v --verbose        be verbose (a 2nd -v gives more)\n   -L --license        display software version & license\n   -V --version        display software version & license\n   -s --small          use less memory (at most 2500k)\n   -1 .. -9            set block size to 100k .. 900k\n   --fast              alias for -1\n   --best              alias for -9\n\n   If invoked as `bzip2', default action is to compress.\n              as `bunzip2',  default action is to decompress.\n              as `bzcat', default action is to decompress to stdout.\n\n   If no file names are given, bzip2 compresses or decompresses\n   from standard input to standard output.  You can combine\n   short flags, so `-v -4' means the same as -v4 or -4v, &c.\n", BZ2_bzlibVersion(), fullProgName);
}

static void redundant(Char *flag)
{
  fprintf(stderr, "%s: %s is redundant in versions 0.9.5 and above\n", progName, flag);
}

typedef struct zzzz
{
  Char *name;
  struct zzzz *link;
} Cell;
static void *myMalloc(Int32 n)
{
  void *p;
  unsigned int p_idx = 0;
  p_idx = malloc((size_t) n);
  if ((&p[p_idx]) == 0)
  {
    outOfMemory();
  }
  return p;
}

static Cell *mkCell(void)
{
  Cell *c;
  unsigned int c_idx = 0;
  c_idx = (Cell *) myMalloc(sizeof(Cell));
  c->name = 0;
  c->link = 0;
  return c;
}

static Cell *snocString(Cell *root, Char *name)
{
  if (root == 0)
  {
    Cell *tmp = mkCell();
    unsigned int tmp_idx = 0;
    tmp->name = (Char *) myMalloc(5 + strlen(name));
    strcpy(tmp->name, name);
    return tmp;
  }
  else
  {
    Cell *tmp = root;
    unsigned int tmp_idx = 0;
    while (tmp->link != 0)
    {
      tmp_idx = tmp_idx->link;
    }

    tmp->link = snocString(tmp->link, name);
    return root;
  }
}

static void addFlagsFromEnvVar(Cell **argList, Char *varName)
{
  Int32 i;
  Int32 j;
  Int32 k;
  Char *envbase;
  unsigned int envbase_idx = 0;
  Char *p;
  unsigned int p_idx = 0;
  envbase_idx = getenv(varName);
  if ((&envbase[envbase_idx]) != 0)
  {
    p_idx = &envbase[envbase_idx];
    i = 0;
    while ((Bool) 1)
    {
      if (p[i + p_idx] == 0)
      {
        break;
      }
      p_idx += i;
      i = 0;
      while (isspace((Int32) p[0 + p_idx]))
      {
        p_idx += 1;
      }

      while ((p[i + p_idx] != 0) && (!isspace((Int32) p[i + p_idx])))
      {
        i += 1;
      }

      if (i > 0)
      {
        k = i;
        if (k > (1034 - 10))
        {
          k = 1034 - 10;
        }
        for (j = 0; j < k; j += 1)
        {
          tmpName[j] = p[j + p_idx];
        }

        tmpName[k] = 0;
        APPEND_FLAG(*argList, tmpName);
      }
    }

  }
}

IntNative main(IntNative argc, Char *argv[])
{
  Int32 i;
  Int32 j;
  Char *tmp;
  unsigned int tmp_idx = 0;
  Cell *argList;
  unsigned int argList_idx = 0;
  Cell *aa;
  unsigned int aa_idx = 0;
  Bool decode;
  if (((((((sizeof(Int32)) != 4) || ((sizeof(UInt32)) != 4)) || ((sizeof(Int16)) != 2)) || ((sizeof(UInt16)) != 2)) || ((sizeof(Char)) != 1)) || ((sizeof(UChar)) != 1))
  {
    configError();
  }
  outputHandleJustInCase = 0;
  smallMode = (Bool) 0;
  keepInputFiles = (Bool) 0;
  forceOverwrite = (Bool) 0;
  noisy = (Bool) 1;
  verbosity = 0;
  blockSize100k = 9;
  testFailsExist = (Bool) 0;
  unzFailsExist = (Bool) 0;
  numFileNames = 0;
  numFilesProcessed = 0;
  workFactor = 30;
  deleteOutputOnInterrupt = (Bool) 0;
  exitValue = 0;
  i = (j = 0);
  signal(SIGSEGV, mySIGSEGVorSIGBUScatcher);
  copyFileName(inName, (Char *) "(none)");
  copyFileName(outName, (Char *) "(none)");
  copyFileName(progNameReally, argv[0]);
  progName = &progNameReally[0];
  for (tmp_idx = &progNameReally[0]; tmp[tmp_idx] != '\0'; tmp_idx += 1)
  {
    if (tmp[tmp_idx] == PATH_SEP)
    {
      progName = (&tmp[tmp_idx]) + 1;
    }
  }

  argList_idx = 0;
  addFlagsFromEnvVar(&(&argList[argList_idx]), (Char *) "BZIP2");
  addFlagsFromEnvVar(&(&argList[argList_idx]), (Char *) "BZIP");
  for (i = 1; i <= (argc - 1); i += 1)
  {
    APPEND_FILESPEC(argList, argv[i]);
  }

  longestFileName = 7;
  numFileNames = 0;
  decode = (Bool) 1;
  for (aa_idx = &argList[argList_idx]; (&aa[aa_idx]) != 0; aa_idx = aa_idx->link)
  {
    if (strcmp(aa->name, "--") == 0)
    {
      decode = (Bool) 0;
      continue;
    }
    if ((aa->name[0] == '-') && decode)
    {
      continue;
    }
    numFileNames += 1;
    if (longestFileName < ((Int32) strlen(aa->name)))
    {
      longestFileName = (Int32) strlen(aa->name);
    }
  }

  if (numFileNames == 0)
  {
    srcMode = 1;
  }
  else
    srcMode = 3;
  opMode = 1;
  if ((strstr(progName, "unzip") != 0) || (strstr(progName, "UNZIP") != 0))
  {
    opMode = 2;
  }
  if ((((strstr(progName, "z2cat") != 0) || (strstr(progName, "Z2CAT") != 0)) || (strstr(progName, "zcat") != 0)) || (strstr(progName, "ZCAT") != 0))
  {
    opMode = 2;
    srcMode = (numFileNames == 0) ? (1) : (2);
  }
  for (aa_idx = &argList[argList_idx]; (&aa[aa_idx]) != 0; aa_idx = aa_idx->link)
  {
    helper_main_5(&j, aa);
  }

  for (aa_idx = &argList[argList_idx]; (&aa[aa_idx]) != 0; aa_idx = aa_idx->link)
  {
    helper_main_4(aa);
  }

  if (verbosity > 4)
  {
    verbosity = 4;
  }
  if (((opMode == 1) && smallMode) && (blockSize100k > 2))
  {
    blockSize100k = 2;
  }
  if ((opMode == 3) && (srcMode == 2))
  {
    fprintf(stderr, "%s: -c and -t cannot be used together.\n", progName);
    exit(1);
  }
  if ((srcMode == 2) && (numFileNames == 0))
  {
    srcMode = 1;
  }
  if (opMode != 1)
  {
    blockSize100k = 0;
  }
  if (srcMode == 3)
  {
    signal(SIGINT, mySignalCatcher);
    signal(SIGTERM, mySignalCatcher);
  }
  if (opMode == 1)
  {
    helper_main_1(&aa_idx, &decode, argList, argList_idx, aa);
  }
  else
    if (opMode == 2)
  {
    helper_main_2(&aa_idx, &decode, argList, argList_idx, aa);
  }
  else
  {
    helper_main_3(&aa_idx, &decode, argList, argList_idx, aa);
  }
  aa_idx = &argList[argList_idx];
  while ((&aa[aa_idx]) != 0)
  {
    Cell *aa2 = aa->link;
    if (aa->name != 0)
    {
      free(aa->name);
    }
    free(aa);
    aa_idx = aa2;
  }

  return exitValue;
}

void helper_compressStream_1(UInt32 nbytes_in_lo32, UInt32 nbytes_in_hi32, UInt32 nbytes_out_lo32, UInt32 nbytes_out_hi32)
{
  if ((nbytes_in_lo32 == 0) && (nbytes_in_hi32 == 0))
  {
    fprintf(stderr, " no data compressed.\n");
  }
  else
  {
    Char buf_nin[32];
    Char buf_nout[32];
    UInt64 nbytes_in;
    UInt64 nbytes_out;
    double nbytes_in_d;
    double nbytes_out_d;
    uInt64_from_UInt32s(&nbytes_in, nbytes_in_lo32, nbytes_in_hi32);
    uInt64_from_UInt32s(&nbytes_out, nbytes_out_lo32, nbytes_out_hi32);
    nbytes_in_d = uInt64_to_double(&nbytes_in);
    nbytes_out_d = uInt64_to_double(&nbytes_out);
    uInt64_toAscii(buf_nin, &nbytes_in);
    uInt64_toAscii(buf_nout, &nbytes_out);
    fprintf(stderr, "%6.3f:1, %6.3f bits/byte, %5.2f%% saved, %s in, %s out.\n", nbytes_in_d / nbytes_out_d, (8.0 * nbytes_out_d) / nbytes_in_d, 100.0 * (1.0 - (nbytes_out_d / nbytes_in_d)), buf_nin, buf_nout);
  }
}

void helper_uncompressStream_1(Int32 * const nread_ref, FILE * const zStream, FILE * const stream, UChar obuf[5000])
{
  Int32 nread = *nread_ref;
  rewind(zStream);
  while ((Bool) 1)
  {
    if (myfeof(zStream))
    {
      break;
    }
    nread = fread(obuf, sizeof(UChar), 5000, zStream);
    if (ferror(zStream))
    {
      goto errhandler_io;
    }
    if (nread > 0)
    {
      fwrite(obuf, sizeof(UChar), nread, stream);
    }
    if (ferror(stream))
    {
      goto errhandler_io;
    }
  }

  goto closeok;
  *nread_ref = nread;
}

void helper_uncompressStream_2(unsigned int * const bzf_idx_ref, Int32 * const nread_ref, Int32 * const streamNo_ref, Int32 * const i_ref, unsigned int * const unusedTmp_idx_ref, FILE * const zStream, FILE * const stream, BZFILE * const bzf, Int32 bzerr, UChar obuf[5000], UChar unused[5000], Int32 nUnused, void * const unusedTmpV, UChar * const unusedTmp)
{
  unsigned int bzf_idx = *bzf_idx_ref;
  Int32 nread = *nread_ref;
  Int32 streamNo = *streamNo_ref;
  Int32 i = *i_ref;
  unsigned int unusedTmp_idx = *unusedTmp_idx_ref;
  bzf_idx = BZ2_bzReadOpen(&bzerr, zStream, verbosity, (int) smallMode, unused, nUnused);
  if (((&bzf[bzf_idx]) == 0) || (bzerr != 0))
  {
    goto errhandler;
  }
  streamNo += 1;
  while (bzerr == 0)
  {
    nread = BZ2_bzRead(&bzerr, bzf, obuf, 5000);
    if (bzerr == (-5))
    {
      goto trycat;
    }
    if (((bzerr == 0) || (bzerr == 4)) && (nread > 0))
    {
      fwrite(obuf, sizeof(UChar), nread, stream);
    }
    if (ferror(stream))
    {
      goto errhandler_io;
    }
  }

  if (bzerr != 4)
  {
    goto errhandler;
  }
  BZ2_bzReadGetUnused(&bzerr, bzf, &unusedTmpV, &nUnused);
  if (bzerr != 0)
  {
    panic("decompress:bzReadGetUnused");
  }
  unusedTmp_idx = (UChar *) unusedTmpV;
  for (i = 0; i < nUnused; i += 1)
  {
    unused[i] = unusedTmp[i + unusedTmp_idx];
  }

  BZ2_bzReadClose(&bzerr, bzf);
  if (bzerr != 0)
  {
    panic("decompress:bzReadGetUnused");
  }
  if ((nUnused == 0) && myfeof(zStream))
  {
    break;
  }
  *bzf_idx_ref = bzf_idx;
  *nread_ref = nread;
  *streamNo_ref = streamNo;
  *i_ref = i;
  *unusedTmp_idx_ref = unusedTmp_idx;
}

void helper_testStream_1(unsigned int * const bzf_idx_ref, Int32 * const streamNo_ref, Int32 * const i_ref, unsigned int * const unusedTmp_idx_ref, FILE * const zStream, BZFILE * const bzf, Int32 bzerr, UChar obuf[5000], UChar unused[5000], Int32 nUnused, void * const unusedTmpV, UChar * const unusedTmp)
{
  unsigned int bzf_idx = *bzf_idx_ref;
  Int32 streamNo = *streamNo_ref;
  Int32 i = *i_ref;
  unsigned int unusedTmp_idx = *unusedTmp_idx_ref;
  bzf_idx = BZ2_bzReadOpen(&bzerr, zStream, verbosity, (int) smallMode, unused, nUnused);
  if (((&bzf[bzf_idx]) == 0) || (bzerr != 0))
  {
    goto errhandler;
  }
  streamNo += 1;
  while (bzerr == 0)
  {
    BZ2_bzRead(&bzerr, bzf, obuf, 5000);
    if (bzerr == (-5))
    {
      goto errhandler;
    }
  }

  if (bzerr != 4)
  {
    goto errhandler;
  }
  BZ2_bzReadGetUnused(&bzerr, bzf, &unusedTmpV, &nUnused);
  if (bzerr != 0)
  {
    panic("test:bzReadGetUnused");
  }
  unusedTmp_idx = (UChar *) unusedTmpV;
  for (i = 0; i < nUnused; i += 1)
  {
    unused[i] = unusedTmp[i + unusedTmp_idx];
  }

  BZ2_bzReadClose(&bzerr, bzf);
  if (bzerr != 0)
  {
    panic("test:bzReadGetUnused");
  }
  if ((nUnused == 0) && myfeof(zStream))
  {
    break;
  }
  *bzf_idx_ref = bzf_idx;
  *streamNo_ref = streamNo;
  *i_ref = i;
  *unusedTmp_idx_ref = unusedTmp_idx;
}

void helper_compress_1(unsigned int * const inStr_idx_ref, unsigned int * const outStr_idx_ref, FILE * const inStr)
{
  unsigned int inStr_idx = *inStr_idx_ref;
  unsigned int outStr_idx = *outStr_idx_ref;
  inStr_idx = fopen(inName, "rb");
  outStr_idx = stdout;
  if (isatty(fileno(stdout)))
  {
    fprintf(stderr, "%s: I won't write compressed data to a terminal.\n", progName);
    fprintf(stderr, "%s: For help, type: `%s --help'.\n", progName, progName);
    if ((&inStr[inStr_idx]) != 0)
    {
      fclose(inStr);
    }
    setExit(1);
    return;
  }
  ;
  if ((&inStr[inStr_idx]) == 0)
  {
    fprintf(stderr, "%s: Can't open input file %s: %s.\n", progName, inName, strerror(errno));
    setExit(1);
    return;
  }
  ;
  break;
  *inStr_idx_ref = inStr_idx;
  *outStr_idx_ref = outStr_idx;
}

void helper_compress_2(unsigned int * const inStr_idx_ref, unsigned int * const outStr_idx_ref, FILE * const inStr, FILE * const outStr)
{
  unsigned int inStr_idx = *inStr_idx_ref;
  unsigned int outStr_idx = *outStr_idx_ref;
  inStr_idx = fopen(inName, "rb");
  outStr_idx = fopen_output_safely(outName, "wb");
  if ((&outStr[outStr_idx]) == 0)
  {
    fprintf(stderr, "%s: Can't create output file %s: %s.\n", progName, outName, strerror(errno));
    if ((&inStr[inStr_idx]) != 0)
    {
      fclose(inStr);
    }
    setExit(1);
    return;
  }
  if ((&inStr[inStr_idx]) == 0)
  {
    fprintf(stderr, "%s: Can't open input file %s: %s.\n", progName, inName, strerror(errno));
    if ((&outStr[outStr_idx]) != 0)
    {
      fclose(outStr);
    }
    setExit(1);
    return;
  }
  ;
  break;
  *inStr_idx_ref = inStr_idx;
  *outStr_idx_ref = outStr_idx;
}

void helper_uncompress_1(unsigned int * const inStr_idx_ref, unsigned int * const outStr_idx_ref, FILE * const inStr, FILE * const outStr)
{
  unsigned int inStr_idx = *inStr_idx_ref;
  unsigned int outStr_idx = *outStr_idx_ref;
  inStr_idx = fopen(inName, "rb");
  outStr_idx = fopen_output_safely(outName, "wb");
  if ((&outStr[outStr_idx]) == 0)
  {
    fprintf(stderr, "%s: Can't create output file %s: %s.\n", progName, outName, strerror(errno));
    if ((&inStr[inStr_idx]) != 0)
    {
      fclose(inStr);
    }
    setExit(1);
    return;
  }
  if ((&inStr[inStr_idx]) == 0)
  {
    fprintf(stderr, "%s: Can't open input file %s: %s.\n", progName, inName, strerror(errno));
    if ((&outStr[outStr_idx]) != 0)
    {
      fclose(outStr);
    }
    setExit(1);
    return;
  }
  ;
  break;
  *inStr_idx_ref = inStr_idx;
  *outStr_idx_ref = outStr_idx;
}

void helper_main_1(unsigned int * const aa_idx_ref, Bool * const decode_ref, Cell * const argList, unsigned int argList_idx, Cell * const aa)
{
  unsigned int aa_idx = *aa_idx_ref;
  Bool decode = *decode_ref;
  if (srcMode == 1)
  {
    compress(0);
  }
  else
  {
    decode = (Bool) 1;
    for (aa_idx = &argList[argList_idx]; (&aa[aa_idx]) != 0; aa_idx = aa_idx->link)
    {
      if (strcmp(aa->name, "--") == 0)
      {
        decode = (Bool) 0;
        continue;
      }
      if ((aa->name[0] == '-') && decode)
      {
        continue;
      }
      numFilesProcessed += 1;
      compress(aa->name);
    }

  }
  *aa_idx_ref = aa_idx;
  *decode_ref = decode;
}

void helper_main_2(unsigned int * const aa_idx_ref, Bool * const decode_ref, Cell * const argList, unsigned int argList_idx, Cell * const aa)
{
  unsigned int aa_idx = *aa_idx_ref;
  Bool decode = *decode_ref;
  unzFailsExist = (Bool) 0;
  if (srcMode == 1)
  {
    uncompress(0);
  }
  else
  {
    decode = (Bool) 1;
    for (aa_idx = &argList[argList_idx]; (&aa[aa_idx]) != 0; aa_idx = aa_idx->link)
    {
      if (strcmp(aa->name, "--") == 0)
      {
        decode = (Bool) 0;
        continue;
      }
      if ((aa->name[0] == '-') && decode)
      {
        continue;
      }
      numFilesProcessed += 1;
      uncompress(aa->name);
    }

  }
  if (unzFailsExist)
  {
    setExit(2);
    exit(exitValue);
  }
  *aa_idx_ref = aa_idx;
  *decode_ref = decode;
}

void helper_main_3(unsigned int * const aa_idx_ref, Bool * const decode_ref, Cell * const argList, unsigned int argList_idx, Cell * const aa)
{
  unsigned int aa_idx = *aa_idx_ref;
  Bool decode = *decode_ref;
  testFailsExist = (Bool) 0;
  if (srcMode == 1)
  {
    testf(0);
  }
  else
  {
    decode = (Bool) 1;
    for (aa_idx = &argList[argList_idx]; (&aa[aa_idx]) != 0; aa_idx = aa_idx->link)
    {
      if (strcmp(aa->name, "--") == 0)
      {
        decode = (Bool) 0;
        continue;
      }
      if ((aa->name[0] == '-') && decode)
      {
        continue;
      }
      numFilesProcessed += 1;
      testf(aa->name);
    }

  }
  if (testFailsExist)
  {
    if (noisy)
    {
      fprintf(stderr, "\nYou can use the `bzip2recover' program to attempt to recover\ndata from undamaged sections of corrupted files.\n\n");
    }
    setExit(2);
    exit(exitValue);
  }
  *aa_idx_ref = aa_idx;
  *decode_ref = decode;
}

void helper_main_4(Cell * const aa)
{
  if (strcmp(aa->name, "--") == 0)
  {
    break;
  }
  if (strcmp(aa->name, "--stdout") == 0)
  {
    srcMode = 2;
  }
  else
    if (strcmp(aa->name, "--decompress") == 0)
  {
    opMode = 2;
  }
  else
    if (strcmp(aa->name, "--compress") == 0)
  {
    opMode = 1;
  }
  else
    if (strcmp(aa->name, "--force") == 0)
  {
    forceOverwrite = (Bool) 1;
  }
  else
    if (strcmp(aa->name, "--test") == 0)
  {
    opMode = 3;
  }
  else
    if (strcmp(aa->name, "--keep") == 0)
  {
    keepInputFiles = (Bool) 1;
  }
  else
    if (strcmp(aa->name, "--small") == 0)
  {
    smallMode = (Bool) 1;
  }
  else
    if (strcmp(aa->name, "--quiet") == 0)
  {
    noisy = (Bool) 0;
  }
  else
    if (strcmp(aa->name, "--version") == 0)
  {
    license();
    exit(0);
  }
  else
    if (strcmp(aa->name, "--license") == 0)
  {
    license();
    exit(0);
  }
  else
    if (strcmp(aa->name, "--exponential") == 0)
  {
    workFactor = 1;
  }
  else
    if (strcmp(aa->name, "--repetitive-best") == 0)
  {
    redundant(aa->name);
  }
  else
    if (strcmp(aa->name, "--repetitive-fast") == 0)
  {
    redundant(aa->name);
  }
  else
    if (strcmp(aa->name, "--fast") == 0)
  {
    blockSize100k = 1;
  }
  else
    if (strcmp(aa->name, "--best") == 0)
  {
    blockSize100k = 9;
  }
  else
    if (strcmp(aa->name, "--verbose") == 0)
  {
    verbosity += 1;
  }
  else
    if (strcmp(aa->name, "--help") == 0)
  {
    usage(progName);
    exit(0);
  }
  else
    if (strncmp(aa->name, "--", 2) == 0)
  {
    fprintf(stderr, "%s: Bad flag `%s'\n", progName, aa->name);
    usage(progName);
    exit(1);
  }
}

void helper_main_5(Int32 * const j_ref, Cell * const aa)
{
  Int32 j = *j_ref;
  if (strcmp(aa->name, "--") == 0)
  {
    break;
  }
  if ((aa->name[0] == '-') && (aa->name[1] != '-'))
  {
    helper_helper_main_5_1(&j, aa);
  }
  *j_ref = j;
}

void helper_helper_main_5_1(Int32 * const j_ref, Cell * const aa)
{
  Int32 j = *j_ref;
  for (j = 1; aa->name[j] != '\0'; j += 1)
  {
    helper_helper_helper_main_5_1_1(aa, j);
  }

  *j_ref = j;
}

void helper_helper_helper_main_5_1_1(Cell * const aa, Int32 j)
{
  switch (aa->name[j])
  {
    case 'c':
    {
      srcMode = 2;
      break;
    }

    case 'd':
    {
      opMode = 2;
      break;
    }

    case 'z':
    {
      opMode = 1;
      break;
    }

    case 'f':
    {
      forceOverwrite = (Bool) 1;
      break;
    }

    case 't':
    {
      opMode = 3;
      break;
    }

    case 'k':
    {
      keepInputFiles = (Bool) 1;
      break;
    }

    case 's':
    {
      smallMode = (Bool) 1;
      break;
    }

    case 'q':
    {
      noisy = (Bool) 0;
      break;
    }

    case '1':
    {
      blockSize100k = 1;
      break;
    }

    case '2':
    {
      blockSize100k = 2;
      break;
    }

    case '3':
    {
      blockSize100k = 3;
      break;
    }

    case '4':
    {
      blockSize100k = 4;
      break;
    }

    case '5':
    {
      blockSize100k = 5;
      break;
    }

    case '6':
    {
      blockSize100k = 6;
      break;
    }

    case '7':
    {
      blockSize100k = 7;
      break;
    }

    case '8':
    {
      blockSize100k = 8;
      break;
    }

    case '9':
    {
      blockSize100k = 9;
      break;
    }

    case 'V':

    case 'L':
    {
      license();
      exit(0);
      break;
    }

    case 'v':
    {
      verbosity += 1;
      break;
    }

    case 'h':
    {
      usage(progName);
      exit(0);
      break;
    }

    default:
    {
      fprintf(stderr, "%s: Bad flag `%s'\n", progName, aa->name);
      usage(progName);
      exit(1);
      break;
    }

  }

}

