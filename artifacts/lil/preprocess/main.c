# 0 "/app/subjects/lil/main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/lil/main.c"
# 26 "/app/subjects/lil/main.c"
# 1 "/app/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/unistd.h" 2
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
# 3 "/app/pipeline/preprocess/fake_libc_include/unistd.h" 2
# 27 "/app/subjects/lil/main.c" 2





# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 33 "/app/subjects/lil/main.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 34 "/app/subjects/lil/main.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 35 "/app/subjects/lil/main.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/time.h" 1
# 36 "/app/subjects/lil/main.c" 2
# 1 "/app/subjects/lil/lil.h" 1
# 66 "/app/subjects/lil/lil.h"
# 1 "/app/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 67 "/app/subjects/lil/lil.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/inttypes.h" 1
# 68 "/app/subjects/lil/lil.h" 2
typedef int64_t lilint_t;





typedef struct _lil_value_t* lil_value_t;
typedef struct _lil_func_t* lil_func_t;
typedef struct _lil_var_t* lil_var_t;
typedef struct _lil_env_t* lil_env_t;
typedef struct _lil_list_t* lil_list_t;
typedef struct _lil_t* lil_t;
typedef lil_value_t (*lil_func_proc_t)(lil_t lil, size_t argc, lil_value_t* argv);
typedef void (*lil_exit_callback_proc_t)(lil_t lil, lil_value_t arg);
typedef void (*lil_write_callback_proc_t)(lil_t lil, const char* msg);
typedef char* (*lil_read_callback_proc_t)(lil_t lil, const char* name);
typedef char* (*lil_source_callback_proc_t)(lil_t lil, const char* name);
typedef void (*lil_store_callback_proc_t)(lil_t lil, const char* name, const char* data);
typedef void (*lil_error_callback_proc_t)(lil_t lil, size_t pos, const char* msg);
typedef int (*lil_setvar_callback_proc_t)(lil_t lil, const char* name, lil_value_t* value);
typedef int (*lil_getvar_callback_proc_t)(lil_t lil, const char* name, lil_value_t* value);
typedef void (*lil_callback_proc_t)(void);

 lil_t lil_new(void);
 void lil_free(lil_t lil);

 int lil_register(lil_t lil, const char* name, lil_func_proc_t proc);

 lil_value_t lil_parse(lil_t lil, const char* code, size_t codelen, int funclevel);
 lil_value_t lil_parse_value(lil_t lil, lil_value_t val, int funclevel);
 lil_value_t lil_call(lil_t lil, const char* funcname, size_t argc, lil_value_t* argv);

 void lil_callback(lil_t lil, int cb, lil_callback_proc_t proc);

 void lil_set_error(lil_t lil, const char* msg);
 void lil_set_error_at(lil_t lil, size_t pos, const char* msg);
 int lil_error(lil_t lil, const char** msg, size_t* pos);

 const char* lil_to_string(lil_value_t val);
 double lil_to_double(lil_value_t val);
 lilint_t lil_to_integer(lil_value_t val);
 int lil_to_boolean(lil_value_t val);

 lil_value_t lil_alloc_string(const char* str);
 lil_value_t lil_alloc_double(double num);
 lil_value_t lil_alloc_integer(lilint_t num);
 void lil_free_value(lil_value_t val);

 lil_value_t lil_clone_value(lil_value_t src);
 int lil_append_char(lil_value_t val, char ch);
 int lil_append_string(lil_value_t val, const char* s);
 int lil_append_val(lil_value_t val, lil_value_t v);

 lil_list_t lil_alloc_list(void);
 void lil_free_list(lil_list_t list);
 void lil_list_append(lil_list_t list, lil_value_t val);
 size_t lil_list_size(lil_list_t list);
 lil_value_t lil_list_get(lil_list_t list, size_t index);
 lil_value_t lil_list_to_value(lil_list_t list, int do_escape);

 lil_list_t lil_subst_to_list(lil_t lil, lil_value_t code);
 lil_value_t lil_subst_to_value(lil_t lil, lil_value_t code);

 lil_env_t lil_alloc_env(lil_env_t parent);
 void lil_free_env(lil_env_t env);
 lil_env_t lil_push_env(lil_t lil);
 void lil_pop_env(lil_t lil);

 lil_var_t lil_set_var(lil_t lil, const char* name, lil_value_t val, int local);
 lil_value_t lil_get_var(lil_t lil, const char* name);
 lil_value_t lil_get_var_or(lil_t lil, const char* name, lil_value_t defvalue);

 lil_value_t lil_eval_expr(lil_t lil, lil_value_t code);
 lil_value_t lil_unused_name(lil_t lil, const char* part);

 lil_value_t lil_arg(lil_value_t* argv, size_t index);

 void lil_set_data(lil_t lil, void* data);
 void* lil_get_data(lil_t lil);

 char* lil_embedded(lil_t lil, const char* code, unsigned int flags);
 void lil_freemem(void* ptr);

 void lil_write(lil_t lil, const char* msg);
# 37 "/app/subjects/lil/main.c" 2

static int running = 1;
static int exit_code = 0;

static void do_exit(lil_t lil, lil_value_t val)
{
    running = 0;
    exit_code = (int)lil_to_integer(val);
}

static char* do_system(size_t argc, char** argv)
{



    char* cmd = 0;
    int cmdlen = 0;
    size_t i;
    FILE* p;
    for (i=0; i<argc; i++) {
        size_t len = strlen(argv[i]);
        if (i != 0) {
            cmd = realloc(cmd, cmdlen + 1);
            cmd[cmdlen++] = ' ';
        }
        cmd = realloc(cmd, cmdlen + len);
        memcpy(cmd + cmdlen, argv[i], len);
        cmdlen += len;
    }
    cmd = realloc(cmd, cmdlen + 1);
    cmd[cmdlen] = 0;
    p = popen(cmd, "r");
    free(cmd);
    if (p) {
        char* retval = 0;
        size_t size = 0;
        char buff[1024];
        ssize_t bytes;
        while ((bytes = fread(buff, 1, 1024, p))) {
            retval = realloc(retval, size + bytes);
            memcpy(retval + size, buff, bytes);
            size += bytes;
        }
        retval = realloc(retval, size + 1);
        retval[size] = 0;
        pclose(p);
        return retval;
    } else {
        return 0;
    }

}

static lil_value_t fnc_writechar(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (!argc) return 0;
    printf("%c", (char)lil_to_integer(argv[0]));
    return 0;
}

static lil_value_t fnc_system(lil_t lil, size_t argc, lil_value_t* argv)
{
    const char** sargv = malloc(sizeof(char*)*(argc + 1));
    lil_value_t r = 0;
    char* rv;
    size_t i;
    if (argc == 0) return 0;
    for (i=0; i<argc; i++)
        sargv[i] = lil_to_string(argv[i]);
    sargv[argc] = 0;
    rv = do_system(argc, (char**)sargv);
    if (rv) {
        r = lil_alloc_string(rv);
        free(rv);
    }
    free(sargv);
    return r;
}

static lil_value_t fnc_readline(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t len = 0, size = 64;
    char* buffer = malloc(size);
    signed char ch;
    lil_value_t retval;
    for (;;) {
        ch = fgetc(stdin);
        if (ch == EOF) break;
        if (ch == '\r') continue;
        if (ch == '\n') break;
        if (len < size) {
            size += 64;
            buffer = realloc(buffer, size);
        }
        buffer[len++] = ch;
    }
    buffer = realloc(buffer, len + 1);
    buffer[len] = 0;
    retval = lil_alloc_string(buffer);
    free(buffer);
    return retval;
}

static int repl(void)
{
    char buffer[16384];
    lil_t lil = lil_new();
    lil_register(lil, "writechar", fnc_writechar);
    lil_register(lil, "system", fnc_system);
    lil_register(lil, "readline", fnc_readline);
    printf("Little Interpreted Language Interactive Shell\n");
    lil_callback(lil, 0, (lil_callback_proc_t)do_exit);
    while (running) {
        lil_value_t result;
        const char* strres;
        const char* err_msg;
        size_t pos;
        buffer[0] = 0;
        printf("# ");
        if (!fgets(buffer, 16384, stdin)) break;
        result = lil_parse(lil, buffer, 0, 0);
        strres = lil_to_string(result);
        if (strres[0])
            printf("%s\n", strres);
        lil_free_value(result);
        if (lil_error(lil, &err_msg, &pos)) {
            printf("error at %i: %s\n", (int)pos, err_msg);
        }
    }
    lil_free(lil);
    return exit_code;
}

static int nonint(int argc, const char* argv[])
{
    lil_t lil = lil_new();
    const char* filename = argv[1];
    const char* err_msg;
    size_t pos;
    lil_list_t arglist = lil_alloc_list();
    lil_value_t args, result;
    char* tmpcode;
    int i;
    lil_register(lil, "writechar", fnc_writechar);
    lil_register(lil, "system", fnc_system);
    for (i=2; i<argc; i++) {
        lil_list_append(arglist, lil_alloc_string(argv[i]));
    }
    args = lil_list_to_value(arglist, 1);
    lil_free_list(arglist);
    lil_set_var(lil, "argv", args, 0);
    lil_free_value(args);
    tmpcode = malloc(strlen(filename) + 256);
    sprintf(tmpcode, "set __lilmain:code__ [read {%s}]\nif [streq $__lilmain:code__ ''] {print There is no code in the file or the file does not exist} {eval $__lilmain:code__}\n", filename);
    result = lil_parse(lil, tmpcode, 0, 1);
    free(tmpcode);
    lil_free_value(result);
    if (lil_error(lil, &err_msg, &pos)) {
        fprintf(stderr, "lil: error at %i: %s\n", (int)pos, err_msg);
    }
    lil_free(lil);
    return exit_code;
}

int main(int argc, const char* argv[])
{
    if (argc < 2) return repl();
    else return nonint(argc, argv);
}
