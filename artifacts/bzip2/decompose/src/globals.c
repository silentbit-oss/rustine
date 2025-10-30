static const char *bzerrorstrings[] = {"OK", "SEQUENCE_ERROR", "PARAM_ERROR", "MEM_ERROR", "DATA_ERROR", "DATA_ERROR_MAGIC", "IO_ERROR", "UNEXPECTED_EOF", "OUTBUFF_FULL", "CONFIG_ERROR", "???", "???", "???", "???", "???", "???"}
/*** DEPENDENCIES:
***/


FILE *outputHandleJustInCase
/*** DEPENDENCIES:
***/


extern Int32 BZ2_rNums[512]
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


extern UInt32 BZ2_crc32Table[256]
/*** DEPENDENCIES:
typedef unsigned int UInt32
----------------------------
***/


static Int32 incs[14] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161, 2391484}
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 verbosity
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Bool keepInputFiles
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Bool smallMode
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Bool deleteOutputOnInterrupt
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Bool forceOverwrite
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Bool testFailsExist
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Bool unzFailsExist
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Bool noisy
/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
***/


Int32 numFileNames
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 numFilesProcessed
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 blockSize100k
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 exitValue
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 opMode
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 srcMode
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Int32 longestFileName
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


Char inName[1034]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Char outName[1034]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Char tmpName[1034]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Char progName[2000]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Char progNameReally[1034]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Int32 workFactor
/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


const Char *zSuffix[4] = {".bz2", ".bz", ".tbz2", ".tbz"}
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


const Char *unzSuffix[4] = {"", "", ".tar", ".tar"}
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Char inFileName[2000]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


Char outFileName[2000]
/*** DEPENDENCIES:
typedef char Char
----------------------------
***/


MaybeUInt64 bytesOut = 0
/*** DEPENDENCIES:
typedef unsigned long long int MaybeUInt64
----------------------------
***/


MaybeUInt64 bytesIn = 0
/*** DEPENDENCIES:
typedef unsigned long long int MaybeUInt64
----------------------------
***/


MaybeUInt64 bStart[50000]
/*** DEPENDENCIES:
typedef unsigned long long int MaybeUInt64
----------------------------
***/


MaybeUInt64 bEnd[50000]
/*** DEPENDENCIES:
typedef unsigned long long int MaybeUInt64
----------------------------
***/


MaybeUInt64 rbStart[50000]
/*** DEPENDENCIES:
typedef unsigned long long int MaybeUInt64
----------------------------
***/


MaybeUInt64 rbEnd[50000]
/*** DEPENDENCIES:
typedef unsigned long long int MaybeUInt64
----------------------------
***/


