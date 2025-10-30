# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h" 2
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
struct GIFScreen
{
    unsigned int Width;
    unsigned int Height;
    unsigned int GlobalColorFlag;
    unsigned int ColorResolution;
    unsigned int SortFlag;
    unsigned int GlobalNumColors;
    unsigned int Background;
    unsigned int PixelAspectRatio;
    unsigned char GlobalColorTable[256 * 3];
};




struct GIFImage
{
    struct GIFScreen *Screen;
    unsigned int LeftPos;
    unsigned int TopPos;
    unsigned int Width;
    unsigned int Height;
    unsigned int LocalColorFlag;
    unsigned int InterlaceFlag;
    unsigned int SortFlag;
    unsigned int LocalNumColors;
    unsigned char LocalColorTable[256 * 3];
    unsigned char **Rows;
};




struct GIFExtension
{
    struct GIFScreen *Screen;
    unsigned char *Buffer;
    unsigned int BufferSize;
    unsigned char Label;
};




struct GIFGraphicCtlExt
{
    unsigned int DisposalMethod;
    unsigned int InputFlag;
    unsigned int TransparentFlag;
    unsigned int DelayTime;
    unsigned int Transparent;
};







void GIFReadScreen(struct GIFScreen *screen, FILE *stream);







void GIFInitImage(struct GIFImage *image,
                  struct GIFScreen *screen, unsigned char **rows);





void GIFDestroyImage(struct GIFImage *image);
# 138 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext,
                     FILE *stream);
# 148 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors,
                      struct GIFImage *image);







void GIFInitExtension(struct GIFExtension *ext,
                      struct GIFScreen *screen, unsigned int initBufferSize);





void GIFDestroyExtension(struct GIFExtension *ext);







void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt,
                      struct GIFExtension *ext);






extern void (*GIFError)(const char *message);





extern void (*GIFWarning)(const char *message);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
static void GIFReadNextImage(struct GIFImage *image, FILE *stream);
static void GIFReadImageData(struct GIFImage *image, FILE *stream);
static int GIFReadDataBlock(unsigned char *buffer, FILE *stream);
static void GIFSkipDataBlocks(FILE *stream);
static int LZWGetCode(int code_size, int init_flag, FILE *stream);
static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream);
static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream);

static int GetByte(FILE *stream);
static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream);

static void ErrorAlloc(void);
static void ErrorRead(FILE *stream);
static void DefaultError(const char *message);
static void DefaultWarning(const char *message);





void GIFReadScreen(struct GIFScreen *screen, FILE *stream)
{
    unsigned char buffer[7];

    ((void)0);
    ReadBytes(buffer, 6, stream);
    if (memcmp(buffer, "GIF", 3) != 0)
        GIFError("Not a GIF file");
    if ((memcmp(buffer + 3, "87a", 3) != 0) &&
            (memcmp(buffer + 3, "89a", 3) != 0))
        GIFWarning("Invalid GIF version number, not \"87a\" or \"89a\"");

    ((void)0);
    ReadBytes(buffer, 7, stream);
    screen->Width = ((buffer + 0)[0] + ((buffer + 0)[1] << 8));
    screen->Height = ((buffer + 2)[0] + ((buffer + 2)[1] << 8));
    screen->GlobalColorFlag = (buffer[4] & 0x80) ? 1 : 0;
    screen->ColorResolution = ((buffer[4] & 0x70) >> 3) + 1;
    screen->SortFlag = (buffer[4] & 0x08) ? 1 : 0;
    screen->GlobalNumColors = 2 << (buffer[4] & 0x07);
    screen->Background = buffer[5];
    screen->PixelAspectRatio = buffer[6];

    if (screen->GlobalColorFlag)
    {
        ((void)0);
        ReadBytes(screen->GlobalColorTable, 3 * screen->GlobalNumColors,
                  stream);
    }

    ((void)0);
    if (screen->Width == 0 || screen->Height == 0)
        GIFError("Invalid dimensions in GIF image");
    if (screen->Background > 0)
    {
        if ((screen->GlobalColorFlag &&
                (screen->Background >= screen->GlobalNumColors)) ||
                !screen->GlobalColorFlag)
        {



            screen->Background = 0;
        }
    }
}




void GIFInitImage(struct GIFImage *image,
                  struct GIFScreen *screen, unsigned char **rows)
{
    image->Screen = screen;
    image->Rows = rows;
}




void GIFDestroyImage(struct GIFImage *image)
{
    (void)image;
}




int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext,
                     FILE *stream)
{
    int ch;
    int foundBogus;

    foundBogus = 0;
    for ( ; ; )
    {
        ch = GetByte(stream);
        switch (ch)
        {
        case 0x2c:
            GIFReadNextImage(image, stream);
            return ch;
        case 0x21:
            GIFReadNextExtension(ext, stream);
            return ch;
        case 0x3b:
            return ch;
        default:
            if (!foundBogus)
                GIFWarning("Bogus data in GIF file");
            foundBogus = 1;
        }
    }
}




static void GIFReadNextImage(struct GIFImage *image, FILE *stream)
{
    struct GIFScreen *screen;
    unsigned char buffer[9];

    ((void)0);
    ReadBytes(buffer, 9, stream);
    if (image == 0)
    {
        GIFSkipDataBlocks(stream);
        return;
    }

    image->LeftPos = ((buffer + 0)[0] + ((buffer + 0)[1] << 8));
    image->TopPos = ((buffer + 2)[0] + ((buffer + 2)[1] << 8));
    image->Width = ((buffer + 4)[0] + ((buffer + 4)[1] << 8));
    image->Height = ((buffer + 6)[0] + ((buffer + 6)[1] << 8));
    image->LocalColorFlag = (buffer[8] & 0x80) ? 1 : 0;
    image->InterlaceFlag = (buffer[8] & 0x40) ? 1 : 0;
    image->SortFlag = (buffer[8] & 0x20) ? 1 : 0;
    image->LocalNumColors = image->LocalColorFlag ?
                            (2 << (buffer[8] & 0x07)) : 0;

    if (image->LocalColorFlag)
    {
        ((void)0);
        ReadBytes(image->LocalColorTable, 3 * image->LocalNumColors, stream);
    }

    ((void)0);
    screen = image->Screen;

    if (image->Width == 0 || image->Height == 0 ||
            image->LeftPos + image->Width > screen->Width ||
            image->TopPos + image->Height > screen->Height)
        GIFError("Invalid dimensions in GIF image");

    GIFReadImageData(image, stream);
}

static void GIFReadImageData(struct GIFImage *image, FILE *stream)
{
    int minCodeSize;
    unsigned char **rows;
    unsigned int width, height, interlaced;
    unsigned char *colors;
    unsigned int numColors;
    unsigned int xpos, ypos;
    int pass, val;

    ((void)0);


    minCodeSize = GetByte(stream);
    if (minCodeSize >= 12)
        GIFError("Invalid LZW code size");

    if (LZWDecodeByte(1, minCodeSize, stream) < 0)
        GIFError("Error decoding GIF image");


    rows = image->Rows;
    if (rows == 0)
    {






        GIFSkipDataBlocks(stream);

        return;
    }

    width = image->Width;
    height = image->Height;
    interlaced = image->InterlaceFlag;
    GIFGetColorTable(&colors, &numColors, image);
    xpos = ypos = 0;
    pass = 0;
    while ((val = LZWDecodeByte(0, minCodeSize, stream)) >= 0)
    {
        if ((unsigned int)val >= numColors)
        {
            GIFWarning("Pixel value out of range in GIF image");
            val = numColors - 1;
        }
        rows[ypos][xpos] = (unsigned char)val;
        if (++xpos == width)
        {
            xpos = 0;
            if (interlaced)
            {
                switch (pass)
                {
                case 0:
                case 1:
                    ypos += 8;
                    break;
                case 2:
                    ypos += 4;
                    break;
                case 3:
                    ypos += 2;
                    break;
                }
                if (ypos >= height)
                {
                    switch (++pass)
                    {
                    case 1:
                        ypos = 4;
                        break;
                    case 2:
                        ypos = 2;
                        break;
                    case 3:
                        ypos = 1;
                        break;
                    default:
                        goto fini;
                    }
                }
            }
            else
                ++ypos;
        }
        if (ypos >= height)
            break;
    }
fini:

    while (LZWDecodeByte(0, minCodeSize, stream) >= 0)
    {
    }
}

static int DataBlockSize = 0;

static int GIFReadDataBlock(unsigned char *buffer, FILE *stream)
{
    int count;

    count = GetByte(stream);
    DataBlockSize = count;
    if (count > 0)
        ReadBytes(buffer, count, stream);
    return count;
}

static void GIFSkipDataBlocks(FILE *stream)
{
    int count;
    unsigned char buffer[256];

    for ( ; ; )
    {
        count = GetByte(stream);
        if (count > 0)
            ReadBytes(buffer, count, stream);
        else
            return;
    }
}

static int LZWGetCode(int code_size, int init_flag, FILE *stream)
{
    static unsigned char buffer[280];
    static int curbit, lastbit, done, last_byte;
    int count, i, j, ret;

    if (init_flag)
    {
        curbit = 0;
        lastbit = 0;
        last_byte = 2;
        done = 0;
        return 0;
    }

    if ((curbit + code_size) >= lastbit)
    {
        if (done)
        {
            if (curbit >= lastbit)
                GIFError("Ran off the end of input bits in LZW decoding");
            return -1;
        }
        buffer[0] = buffer[last_byte - 2];
        buffer[1] = buffer[last_byte - 1];

        if ((count = GIFReadDataBlock(&buffer[2], stream)) == 0)
            done = 1;

        last_byte = 2 + count;
        curbit = (curbit - lastbit) + 16;
        lastbit = (2 + count) * 8;
    }

    if (code_size && (size_t)(curbit + code_size - 1) / 8 >= sizeof(buffer))
    {

        GIFError("Malformed GIF (CVE-2023-43907)");
    }

    ret = 0;
    for (i = curbit, j = 0; j < code_size; ++i, ++j)
        ret |= ((buffer[i / 8] & (1 << (i % 8))) != 0) << j;

    curbit += code_size;
    return ret;
}

static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream)
{
    static int fresh = 0;
    static int code_size, set_code_size;
    static int max_code, max_code_size;
    static int firstcode, oldcode;
    static int clear_code, end_code;
    static int table[2][((1 << 12) - 1) + 1];
    static int stack[(((1 << 12) - 1) + 1) * 2], *sp;
    int code, incode;
    int i;

    if (init_flag)
    {
        fresh = 1;
        set_code_size = input_code_size;
        code_size = set_code_size + 1;
        clear_code = 1 << set_code_size;
        end_code = clear_code + 1;
        max_code_size = 2 * clear_code;
        max_code = clear_code + 2;

        LZWGetCode(0, 1, stream);

        for (i = 0; i < clear_code; ++i)
        {
            table[0][i] = 0;
            table[1][i] = i;
        }
        for ( ; i <= ((1 << 12) - 1); ++i)
        {
            table[0][i] = 0;
            table[1][i] = 0;
        }

        sp = stack;
        return 0;
    }
    else if (fresh)
    {
        fresh = 0;
        do
        {
            firstcode = oldcode = LZWGetCode(code_size, 0, stream);
        } while (firstcode == clear_code);
        return firstcode;
    }

    if (sp > stack)
        return *--sp;

    while ((code = LZWGetCode(code_size, 0, stream)) >= 0)
    {
        if (code == clear_code)
        {
            for (i = 0; i < clear_code; ++i)
            {
                table[0][i] = 0;
                table[1][i] = i;
            }
            for ( ; i <= ((1 << 12) - 1); ++i)
            {
                table[0][i] = 0;
                table[1][i] = 0;
            }

            code_size = set_code_size + 1;
            max_code_size = 2 * clear_code;
            max_code = clear_code + 2;
            sp = stack;
            firstcode = oldcode = LZWGetCode(code_size, 0, stream);
            return firstcode;
        }
        else if (code == end_code)
        {
            int count;
            unsigned char buffer[260];

            if (DataBlockSize == 0)
                return -2;

            while ((count = GIFReadDataBlock(buffer, stream)) > 0)
            {
            }





            (void)count;

            return -2;
        }

        incode = code;

        if (code >= max_code)
        {
            *sp++ = firstcode;
            code = oldcode;
        }

        while (code >= clear_code)
        {
            *sp++ = table[1][code];
            if ((code == table[0][code]) ||
                    ((size_t)(sp - stack) >= sizeof(stack) / sizeof(stack[0])))
                GIFError("Circular dependency found in LZW table");
            code = table[0][code];
        }

        *sp++ = firstcode = table[1][code];

        if ((code = max_code) <= ((1 << 12) - 1))
        {
            table[0][code] = oldcode;
            table[1][code] = firstcode;
            ++max_code;
            if ((max_code >= max_code_size) && (max_code_size <= ((1 << 12) - 1)))
            {
                max_code_size *= 2;
                ++code_size;
            }
        }

        oldcode = incode;

        if (sp > stack)
            return *--sp;
    }
    return code;
}
# 522 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
static unsigned char DefaultColorTable[] =
{
      0, 0, 0,
    255, 255, 255,
    255, 0, 0,
      0, 255, 255,
      0, 255, 0,
    255, 0, 255,
      0, 0, 255,
    255, 255, 0,
};





void GIFGetColorTable(unsigned char **colors, unsigned int *numColors,
                      struct GIFImage *image)
{
    struct GIFScreen *screen;

    if (image->LocalColorFlag)
    {
        ((void)0);
        *colors = image->LocalColorTable;
        *numColors = image->LocalNumColors;
        return;
    }

    screen = image->Screen;
    if (screen->GlobalColorFlag)
    {
        ((void)0);
        *colors = screen->GlobalColorTable;
        *numColors = screen->GlobalNumColors;
        return;
    }

    ((void)0);
    *colors = DefaultColorTable;
    *numColors = sizeof(DefaultColorTable) / 3;
}




void GIFInitExtension(struct GIFExtension *ext,
                      struct GIFScreen *screen, unsigned int initBufferSize)
{
    unsigned char *newBuffer;

    ext->Screen = screen;
    if (initBufferSize > 0)
    {
        newBuffer = (unsigned char *)malloc(initBufferSize);
        if (newBuffer == 0)
            ErrorAlloc();
        ext->Buffer = newBuffer;
        ext->BufferSize = initBufferSize;
    }
    else
    {
        ext->Buffer = 0;
        ext->BufferSize = 0;
    }
}




void GIFDestroyExtension(struct GIFExtension *ext)
{
    free(ext->Buffer);
}




static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream)
{
    unsigned char *newBuffer;
    unsigned int newBufferSize;
    unsigned int offset, len;
    int count, label;

    label = GetByte(stream);
    ((void)0);
    if (ext == 0)
    {
        GIFSkipDataBlocks(stream);
        return;
    }
    ext->Label = (unsigned char)label;

    offset = 0;
    len = ext->BufferSize;
    for ( ; ; )
    {
        if (len < 255)
        {
            newBufferSize = ext->BufferSize + 1024;
            newBuffer = (unsigned char *)realloc(ext->Buffer, newBufferSize);
            if (newBuffer == 0)
                ErrorAlloc();
            ext->BufferSize = newBufferSize;
            ext->Buffer = newBuffer;
            len += 1024;
        }
        count = GIFReadDataBlock(ext->Buffer + offset, stream);
        if (count == 0)
            break;
        offset += count;
        len -= count;
    }
}





void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt,
                      struct GIFExtension *ext)
{
    unsigned char *buffer;

    ((void)0);
    if (ext->Label != 0xf9)
    {
        GIFWarning("Not a graphic control extension in GIF file");
        return;
    }
    if (ext->BufferSize < 4)
    {
        GIFWarning("Broken graphic control extension in GIF file");
        return;
    }

    buffer = ext->Buffer;
    graphicExt->DisposalMethod = (buffer[0] >> 2) & 0x07;
    graphicExt->InputFlag = (buffer[0] >> 1) & 0x01;
    graphicExt->TransparentFlag = buffer[0] & 0x01;
    graphicExt->DelayTime = ((buffer + 1)[0] + ((buffer + 1)[1] << 8));
    graphicExt->Transparent = buffer[3];
}




static int GetByte(FILE *stream)
{
    int ch;

    if ((ch = getc(stream)) == EOF)
        ErrorRead(stream);
    return ch;
}




static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream)
{
    if (fread(buffer, count, 1, stream) != 1)
        ErrorRead(stream);
}




static void ErrorAlloc(void)
{
    GIFError("Out of memory in GIF decoder");
}




static void ErrorRead(FILE *stream)
{
    if (ferror(stream))
        GIFError("Error reading GIF file");
    else
        GIFError("Unexpected end of GIF file");
}




static void DefaultError(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}




static void DefaultWarning(const char *message)
{
    fprintf(stderr, "%s\n", message);
}




void (*GIFError)(const char *message) = DefaultError;




void (*GIFWarning)(const char *message) = DefaultWarning;
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h" 2
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
struct GIFScreen
{
    unsigned int Width;
    unsigned int Height;
    unsigned int GlobalColorFlag;
    unsigned int ColorResolution;
    unsigned int SortFlag;
    unsigned int GlobalNumColors;
    unsigned int Background;
    unsigned int PixelAspectRatio;
    unsigned char GlobalColorTable[256 * 3];
};




struct GIFImage
{
    struct GIFScreen *Screen;
    unsigned int LeftPos;
    unsigned int TopPos;
    unsigned int Width;
    unsigned int Height;
    unsigned int LocalColorFlag;
    unsigned int InterlaceFlag;
    unsigned int SortFlag;
    unsigned int LocalNumColors;
    unsigned char LocalColorTable[256 * 3];
    unsigned char **Rows;
};




struct GIFExtension
{
    struct GIFScreen *Screen;
    unsigned char *Buffer;
    unsigned int BufferSize;
    unsigned char Label;
};




struct GIFGraphicCtlExt
{
    unsigned int DisposalMethod;
    unsigned int InputFlag;
    unsigned int TransparentFlag;
    unsigned int DelayTime;
    unsigned int Transparent;
};







void GIFReadScreen(struct GIFScreen *screen, FILE *stream);







void GIFInitImage(struct GIFImage *image,
                  struct GIFScreen *screen, unsigned char **rows);





void GIFDestroyImage(struct GIFImage *image);
# 138 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext,
                     FILE *stream);
# 148 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.h"
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors,
                      struct GIFImage *image);







void GIFInitExtension(struct GIFExtension *ext,
                      struct GIFScreen *screen, unsigned int initBufferSize);





void GIFDestroyExtension(struct GIFExtension *ext);







void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt,
                      struct GIFExtension *ext);






extern void (*GIFError)(const char *message);





extern void (*GIFWarning)(const char *message);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c" 2
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
static void GIFReadNextImage(struct GIFImage *image, FILE *stream);
static void GIFReadImageData(struct GIFImage *image, FILE *stream);
static int GIFReadDataBlock(unsigned char *buffer, FILE *stream);
static void GIFSkipDataBlocks(FILE *stream);
static int LZWGetCode(int code_size, int init_flag, FILE *stream);
static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream);
static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream);

static int GetByte(FILE *stream);
static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream);

static void ErrorAlloc(void);
static void ErrorRead(FILE *stream);
static void DefaultError(const char *message);
static void DefaultWarning(const char *message);





void GIFReadScreen(struct GIFScreen *screen, FILE *stream)
{
    unsigned char buffer[7];

    ((void)0);
    ReadBytes(buffer, 6, stream);
    if (memcmp(buffer, "GIF", 3) != 0)
        GIFError("Not a GIF file");
    if ((memcmp(buffer + 3, "87a", 3) != 0) &&
            (memcmp(buffer + 3, "89a", 3) != 0))
        GIFWarning("Invalid GIF version number, not \"87a\" or \"89a\"");

    ((void)0);
    ReadBytes(buffer, 7, stream);
    screen->Width = ((buffer + 0)[0] + ((buffer + 0)[1] << 8));
    screen->Height = ((buffer + 2)[0] + ((buffer + 2)[1] << 8));
    screen->GlobalColorFlag = (buffer[4] & 0x80) ? 1 : 0;
    screen->ColorResolution = ((buffer[4] & 0x70) >> 3) + 1;
    screen->SortFlag = (buffer[4] & 0x08) ? 1 : 0;
    screen->GlobalNumColors = 2 << (buffer[4] & 0x07);
    screen->Background = buffer[5];
    screen->PixelAspectRatio = buffer[6];

    if (screen->GlobalColorFlag)
    {
        ((void)0);
        ReadBytes(screen->GlobalColorTable, 3 * screen->GlobalNumColors,
                  stream);
    }

    ((void)0);
    if (screen->Width == 0 || screen->Height == 0)
        GIFError("Invalid dimensions in GIF image");
    if (screen->Background > 0)
    {
        if ((screen->GlobalColorFlag &&
                (screen->Background >= screen->GlobalNumColors)) ||
                !screen->GlobalColorFlag)
        {



            screen->Background = 0;
        }
    }
}




void GIFInitImage(struct GIFImage *image,
                  struct GIFScreen *screen, unsigned char **rows)
{
    image->Screen = screen;
    image->Rows = rows;
}




void GIFDestroyImage(struct GIFImage *image)
{
    (void)image;
}




int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext,
                     FILE *stream)
{
    int ch;
    int foundBogus;

    foundBogus = 0;
    for ( ; ; )
    {
        ch = GetByte(stream);
        switch (ch)
        {
        case 0x2c:
            GIFReadNextImage(image, stream);
            return ch;
        case 0x21:
            GIFReadNextExtension(ext, stream);
            return ch;
        case 0x3b:
            return ch;
        default:
            if (!foundBogus)
                GIFWarning("Bogus data in GIF file");
            foundBogus = 1;
        }
    }
}




static void GIFReadNextImage(struct GIFImage *image, FILE *stream)
{
    struct GIFScreen *screen;
    unsigned char buffer[9];

    ((void)0);
    ReadBytes(buffer, 9, stream);
    if (image == 0)
    {
        GIFSkipDataBlocks(stream);
        return;
    }

    image->LeftPos = ((buffer + 0)[0] + ((buffer + 0)[1] << 8));
    image->TopPos = ((buffer + 2)[0] + ((buffer + 2)[1] << 8));
    image->Width = ((buffer + 4)[0] + ((buffer + 4)[1] << 8));
    image->Height = ((buffer + 6)[0] + ((buffer + 6)[1] << 8));
    image->LocalColorFlag = (buffer[8] & 0x80) ? 1 : 0;
    image->InterlaceFlag = (buffer[8] & 0x40) ? 1 : 0;
    image->SortFlag = (buffer[8] & 0x20) ? 1 : 0;
    image->LocalNumColors = image->LocalColorFlag ?
                            (2 << (buffer[8] & 0x07)) : 0;

    if (image->LocalColorFlag)
    {
        ((void)0);
        ReadBytes(image->LocalColorTable, 3 * image->LocalNumColors, stream);
    }

    ((void)0);
    screen = image->Screen;

    if (image->Width == 0 || image->Height == 0 ||
            image->LeftPos + image->Width > screen->Width ||
            image->TopPos + image->Height > screen->Height)
        GIFError("Invalid dimensions in GIF image");

    GIFReadImageData(image, stream);
}

static void GIFReadImageData(struct GIFImage *image, FILE *stream)
{
    int minCodeSize;
    unsigned char **rows;
    unsigned int width, height, interlaced;
    unsigned char *colors;
    unsigned int numColors;
    unsigned int xpos, ypos;
    int pass, val;

    ((void)0);


    minCodeSize = GetByte(stream);
    if (minCodeSize >= 12)
        GIFError("Invalid LZW code size");

    if (LZWDecodeByte(1, minCodeSize, stream) < 0)
        GIFError("Error decoding GIF image");


    rows = image->Rows;
    if (rows == 0)
    {






        GIFSkipDataBlocks(stream);

        return;
    }

    width = image->Width;
    height = image->Height;
    interlaced = image->InterlaceFlag;
    GIFGetColorTable(&colors, &numColors, image);
    xpos = ypos = 0;
    pass = 0;
    while ((val = LZWDecodeByte(0, minCodeSize, stream)) >= 0)
    {
        if ((unsigned int)val >= numColors)
        {
            GIFWarning("Pixel value out of range in GIF image");
            val = numColors - 1;
        }
        rows[ypos][xpos] = (unsigned char)val;
        if (++xpos == width)
        {
            xpos = 0;
            if (interlaced)
            {
                switch (pass)
                {
                case 0:
                case 1:
                    ypos += 8;
                    break;
                case 2:
                    ypos += 4;
                    break;
                case 3:
                    ypos += 2;
                    break;
                }
                if (ypos >= height)
                {
                    switch (++pass)
                    {
                    case 1:
                        ypos = 4;
                        break;
                    case 2:
                        ypos = 2;
                        break;
                    case 3:
                        ypos = 1;
                        break;
                    default:
                        goto fini;
                    }
                }
            }
            else
                ++ypos;
        }
        if (ypos >= height)
            break;
    }
fini:

    while (LZWDecodeByte(0, minCodeSize, stream) >= 0)
    {
    }
}

static int DataBlockSize = 0;

static int GIFReadDataBlock(unsigned char *buffer, FILE *stream)
{
    int count;

    count = GetByte(stream);
    DataBlockSize = count;
    if (count > 0)
        ReadBytes(buffer, count, stream);
    return count;
}

static void GIFSkipDataBlocks(FILE *stream)
{
    int count;
    unsigned char buffer[256];

    for ( ; ; )
    {
        count = GetByte(stream);
        if (count > 0)
            ReadBytes(buffer, count, stream);
        else
            return;
    }
}

static int LZWGetCode(int code_size, int init_flag, FILE *stream)
{
    static unsigned char buffer[280];
    static int curbit, lastbit, done, last_byte;
    int count, i, j, ret;

    if (init_flag)
    {
        curbit = 0;
        lastbit = 0;
        last_byte = 2;
        done = 0;
        return 0;
    }

    if ((curbit + code_size) >= lastbit)
    {
        if (done)
        {
            if (curbit >= lastbit)
                GIFError("Ran off the end of input bits in LZW decoding");
            return -1;
        }
        buffer[0] = buffer[last_byte - 2];
        buffer[1] = buffer[last_byte - 1];

        if ((count = GIFReadDataBlock(&buffer[2], stream)) == 0)
            done = 1;

        last_byte = 2 + count;
        curbit = (curbit - lastbit) + 16;
        lastbit = (2 + count) * 8;
    }

    if (code_size && (size_t)(curbit + code_size - 1) / 8 >= sizeof(buffer))
    {

        GIFError("Malformed GIF (CVE-2023-43907)");
    }

    ret = 0;
    for (i = curbit, j = 0; j < code_size; ++i, ++j)
        ret |= ((buffer[i / 8] & (1 << (i % 8))) != 0) << j;

    curbit += code_size;
    return ret;
}

static int LZWDecodeByte(int init_flag, int input_code_size, FILE *stream)
{
    static int fresh = 0;
    static int code_size, set_code_size;
    static int max_code, max_code_size;
    static int firstcode, oldcode;
    static int clear_code, end_code;
    static int table[2][((1 << 12) - 1) + 1];
    static int stack[(((1 << 12) - 1) + 1) * 2], *sp;
    int code, incode;
    int i;

    if (init_flag)
    {
        fresh = 1;
        set_code_size = input_code_size;
        code_size = set_code_size + 1;
        clear_code = 1 << set_code_size;
        end_code = clear_code + 1;
        max_code_size = 2 * clear_code;
        max_code = clear_code + 2;

        LZWGetCode(0, 1, stream);

        for (i = 0; i < clear_code; ++i)
        {
            table[0][i] = 0;
            table[1][i] = i;
        }
        for ( ; i <= ((1 << 12) - 1); ++i)
        {
            table[0][i] = 0;
            table[1][i] = 0;
        }

        sp = stack;
        return 0;
    }
    else if (fresh)
    {
        fresh = 0;
        do
        {
            firstcode = oldcode = LZWGetCode(code_size, 0, stream);
        } while (firstcode == clear_code);
        return firstcode;
    }

    if (sp > stack)
        return *--sp;

    while ((code = LZWGetCode(code_size, 0, stream)) >= 0)
    {
        if (code == clear_code)
        {
            for (i = 0; i < clear_code; ++i)
            {
                table[0][i] = 0;
                table[1][i] = i;
            }
            for ( ; i <= ((1 << 12) - 1); ++i)
            {
                table[0][i] = 0;
                table[1][i] = 0;
            }

            code_size = set_code_size + 1;
            max_code_size = 2 * clear_code;
            max_code = clear_code + 2;
            sp = stack;
            firstcode = oldcode = LZWGetCode(code_size, 0, stream);
            return firstcode;
        }
        else if (code == end_code)
        {
            int count;
            unsigned char buffer[260];

            if (DataBlockSize == 0)
                return -2;

            while ((count = GIFReadDataBlock(buffer, stream)) > 0)
            {
            }





            (void)count;

            return -2;
        }

        incode = code;

        if (code >= max_code)
        {
            *sp++ = firstcode;
            code = oldcode;
        }

        while (code >= clear_code)
        {
            *sp++ = table[1][code];
            if ((code == table[0][code]) ||
                    ((size_t)(sp - stack) >= sizeof(stack) / sizeof(stack[0])))
                GIFError("Circular dependency found in LZW table");
            code = table[0][code];
        }

        *sp++ = firstcode = table[1][code];

        if ((code = max_code) <= ((1 << 12) - 1))
        {
            table[0][code] = oldcode;
            table[1][code] = firstcode;
            ++max_code;
            if ((max_code >= max_code_size) && (max_code_size <= ((1 << 12) - 1)))
            {
                max_code_size *= 2;
                ++code_size;
            }
        }

        oldcode = incode;

        if (sp > stack)
            return *--sp;
    }
    return code;
}
# 522 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/gifread/gifread.c"
static unsigned char DefaultColorTable[] =
{
      0, 0, 0,
    255, 255, 255,
    255, 0, 0,
      0, 255, 255,
      0, 255, 0,
    255, 0, 255,
      0, 0, 255,
    255, 255, 0,
};





void GIFGetColorTable(unsigned char **colors, unsigned int *numColors,
                      struct GIFImage *image)
{
    struct GIFScreen *screen;

    if (image->LocalColorFlag)
    {
        ((void)0);
        *colors = image->LocalColorTable;
        *numColors = image->LocalNumColors;
        return;
    }

    screen = image->Screen;
    if (screen->GlobalColorFlag)
    {
        ((void)0);
        *colors = screen->GlobalColorTable;
        *numColors = screen->GlobalNumColors;
        return;
    }

    ((void)0);
    *colors = DefaultColorTable;
    *numColors = sizeof(DefaultColorTable) / 3;
}




void GIFInitExtension(struct GIFExtension *ext,
                      struct GIFScreen *screen, unsigned int initBufferSize)
{
    unsigned char *newBuffer;

    ext->Screen = screen;
    if (initBufferSize > 0)
    {
        newBuffer = (unsigned char *)malloc(initBufferSize);
        if (newBuffer == 0)
            ErrorAlloc();
        ext->Buffer = newBuffer;
        ext->BufferSize = initBufferSize;
    }
    else
    {
        ext->Buffer = 0;
        ext->BufferSize = 0;
    }
}




void GIFDestroyExtension(struct GIFExtension *ext)
{
    free(ext->Buffer);
}




static void GIFReadNextExtension(struct GIFExtension *ext, FILE *stream)
{
    unsigned char *newBuffer;
    unsigned int newBufferSize;
    unsigned int offset, len;
    int count, label;

    label = GetByte(stream);
    ((void)0);
    if (ext == 0)
    {
        GIFSkipDataBlocks(stream);
        return;
    }
    ext->Label = (unsigned char)label;

    offset = 0;
    len = ext->BufferSize;
    for ( ; ; )
    {
        if (len < 255)
        {
            newBufferSize = ext->BufferSize + 1024;
            newBuffer = (unsigned char *)realloc(ext->Buffer, newBufferSize);
            if (newBuffer == 0)
                ErrorAlloc();
            ext->BufferSize = newBufferSize;
            ext->Buffer = newBuffer;
            len += 1024;
        }
        count = GIFReadDataBlock(ext->Buffer + offset, stream);
        if (count == 0)
            break;
        offset += count;
        len -= count;
    }
}





void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt,
                      struct GIFExtension *ext)
{
    unsigned char *buffer;

    ((void)0);
    if (ext->Label != 0xf9)
    {
        GIFWarning("Not a graphic control extension in GIF file");
        return;
    }
    if (ext->BufferSize < 4)
    {
        GIFWarning("Broken graphic control extension in GIF file");
        return;
    }

    buffer = ext->Buffer;
    graphicExt->DisposalMethod = (buffer[0] >> 2) & 0x07;
    graphicExt->InputFlag = (buffer[0] >> 1) & 0x01;
    graphicExt->TransparentFlag = buffer[0] & 0x01;
    graphicExt->DelayTime = ((buffer + 1)[0] + ((buffer + 1)[1] << 8));
    graphicExt->Transparent = buffer[3];
}




static int GetByte(FILE *stream)
{
    int ch;

    if ((ch = getc(stream)) == EOF)
        ErrorRead(stream);
    return ch;
}




static void ReadBytes(unsigned char *buffer, unsigned int count, FILE *stream)
{
    if (fread(buffer, count, 1, stream) != 1)
        ErrorRead(stream);
}




static void ErrorAlloc(void)
{
    GIFError("Out of memory in GIF decoder");
}




static void ErrorRead(FILE *stream)
{
    if (ferror(stream))
        GIFError("Error reading GIF file");
    else
        GIFError("Unexpected end of GIF file");
}




static void DefaultError(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}




static void DefaultWarning(const char *message)
{
    fprintf(stderr, "%s\n", message);
}




void (*GIFError)(const char *message) = DefaultError;




void (*GIFWarning)(const char *message) = DefaultWarning;
