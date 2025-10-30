# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c"







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h" 2
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h"
typedef struct {
  size_t len;
  char *alloc;
  char *data;
} buffer_t;



buffer_t *
buffer_new();

buffer_t *
buffer_new_with_size(size_t n);

buffer_t *
buffer_new_with_string(char *str);

buffer_t *
buffer_new_with_string_length(char *str, size_t len);

buffer_t *
buffer_new_with_copy(char *str);

size_t
buffer_size(buffer_t *self);

size_t
buffer_length(buffer_t *self);

void
buffer_free(buffer_t *self);

int
buffer_prepend(buffer_t *self, char *str);

int
buffer_append(buffer_t *self, const char *str);

int
buffer_appendf(buffer_t *self, const char *format, ...);

int
buffer_append_n(buffer_t *self, const char *str, size_t len);

int
buffer_equals(buffer_t *self, buffer_t *other);

ssize_t
buffer_indexof(buffer_t *self, char *str);

buffer_t *
buffer_slice(buffer_t *self, size_t from, ssize_t to);

ssize_t
buffer_compact(buffer_t *self);

void
buffer_fill(buffer_t *self, int c);

void
buffer_clear(buffer_t *self);

void
buffer_trim_left(buffer_t *self);

void
buffer_trim_right(buffer_t *self);

void
buffer_trim(buffer_t *self);

void
buffer_print(buffer_t *self);
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2

void
equal(char *a, char *b) {
  if (strcmp(a, b)) {
    printf("\n");
    printf("  expected: '%s'\n", a);
    printf("    actual: '%s'\n", b);
    printf("\n");
    exit(1);
  }
}

void
test_buffer_new() {
  buffer_t *buf = buffer_new();
  assert(64 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_new_with_size() {
  buffer_t *buf = buffer_new_with_size(1024);
  assert(1024 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_append() {
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " World"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", (buf->data));
  buffer_free(buf);
}

void
test_buffer_append_n() {
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append_n(buf, "subway", 3));
  assert(0 == buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == buffer_length(buf));
  equal("submarine", (buf->data));
  buffer_free(buf);
}

void
test_buffer_append__grow() {
  buffer_t *buf = buffer_new_with_size(10);
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " tobi"));
  assert(0 == buffer_append(buf, " was"));
  assert(0 == buffer_append(buf, " here"));

  char *str = "Hello tobi was here";
  equal(str, (buf->data));
  assert(1024 == buffer_size(buf));
  assert(strlen(str) == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_prepend() {
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, " World"));
  assert(0 == buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", (buf->data));
  buffer_free(buf);
}

void
test_buffer_slice() {
  buffer_t *buf = buffer_new();
  buffer_append(buf, "Tobi Ferret");

  buffer_t *a = buffer_slice(buf, 2, 8);
  equal("Tobi Ferret", (buf->data));
  equal("bi Fer", (a->data));

  buffer_free(buf);
  buffer_free(a);
}

void
test_buffer_slice__range_error() {
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 10, 2);
  assert(0 == a);
  buffer_free(buf);
}

void
test_buffer_slice__end() {
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");

  buffer_t *a = buffer_slice(buf, 5, -1);
  equal("Tobi Ferret", (buf->data));
  equal("Ferret", (a->data));

  buffer_t *b = buffer_slice(buf, 5, -3);
  equal("Ferr", (b->data));

  buffer_t *c = buffer_slice(buf, 8, -1);
  equal("ret", (c->data));

  buffer_free(buf);
  buffer_free(a);
  buffer_free(b);
  buffer_free(c);
}

void
test_buffer_slice__end_overflow() {
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", (buf->data));
  equal("Ferret", (a->data));
  buffer_free(a);
  buffer_free(buf);
}

void
test_buffer_equals() {
  buffer_t *a = buffer_new_with_copy("Hello");
  buffer_t *b = buffer_new_with_copy("Hello");

  assert(1 == buffer_equals(a, b));

  buffer_append(b, " World");
  assert(0 == buffer_equals(a, b));

  buffer_free(a);
  buffer_free(b);
}

void test_buffer_formatting() {
  buffer_t *buf = buffer_new();
  int result = buffer_appendf(buf, "%d %s", 3, "cow");
  assert(0 == result);
  equal("3 cow", (buf->data));
  result = buffer_appendf(buf, " - 0x%08X", 0xdeadbeef);
  assert(0 == result);
  equal("3 cow - 0xDEADBEEF", (buf->data));
  buffer_free(buf);
}

void
test_buffer_indexof() {
  buffer_t *buf = buffer_new_with_copy("Tobi is a ferret");

  ssize_t i = buffer_indexof(buf, "is");
  assert(5 == i);

  i = buffer_indexof(buf, "a");
  assert(8 == i);

  i = buffer_indexof(buf, "something");
  assert(-1 == i);

  buffer_free(buf);
}

void
test_buffer_fill() {
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));

  buffer_fill(buf, 0);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_clear() {
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));

  buffer_clear(buf);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_trim() {
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim(buf);
  equal("Hello", (buf->data));
  buffer_free(buf);

  buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_left(buf);
  equal("Hello\n\n ", (buf->data));
  buffer_free(buf);

  buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_right(buf);
  equal("  Hello", (buf->data));
  buffer_free(buf);
}

void
test_buffer_compact() {
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim(buf);
  assert(5 == buffer_length(buf));
  assert(10 == buffer_size(buf));

  ssize_t removed = buffer_compact(buf);
  assert(5 == removed);
  assert(5 == buffer_length(buf));
  assert(5 == buffer_size(buf));
  equal("Hello", (buf->data));

  buffer_free(buf);
}

int
main(){
  test_buffer_new();
  test_buffer_new_with_size();
  test_buffer_append();
  test_buffer_append__grow();
  test_buffer_append_n();
  test_buffer_prepend();
  test_buffer_slice();
  test_buffer_slice__range_error();
  test_buffer_slice__end();
  test_buffer_slice__end_overflow();
  test_buffer_equals();
  test_buffer_formatting();
  test_buffer_indexof();
  test_buffer_fill();
  test_buffer_clear();
  test_buffer_trim();
  test_buffer_compact();
  printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
  return 0;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c"







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h" 2
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/buffer.h"
typedef struct {
  size_t len;
  char *alloc;
  char *data;
} buffer_t;



buffer_t *
buffer_new();

buffer_t *
buffer_new_with_size(size_t n);

buffer_t *
buffer_new_with_string(char *str);

buffer_t *
buffer_new_with_string_length(char *str, size_t len);

buffer_t *
buffer_new_with_copy(char *str);

size_t
buffer_size(buffer_t *self);

size_t
buffer_length(buffer_t *self);

void
buffer_free(buffer_t *self);

int
buffer_prepend(buffer_t *self, char *str);

int
buffer_append(buffer_t *self, const char *str);

int
buffer_appendf(buffer_t *self, const char *format, ...);

int
buffer_append_n(buffer_t *self, const char *str, size_t len);

int
buffer_equals(buffer_t *self, buffer_t *other);

ssize_t
buffer_indexof(buffer_t *self, char *str);

buffer_t *
buffer_slice(buffer_t *self, size_t from, ssize_t to);

ssize_t
buffer_compact(buffer_t *self);

void
buffer_fill(buffer_t *self, int c);

void
buffer_clear(buffer_t *self);

void
buffer_trim_left(buffer_t *self);

void
buffer_trim_right(buffer_t *self);

void
buffer_trim(buffer_t *self);

void
buffer_print(buffer_t *self);
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/buffer-0.4.0/test.c" 2

void
equal(char *a, char *b) {
  if (strcmp(a, b)) {
    printf("\n");
    printf("  expected: '%s'\n", a);
    printf("    actual: '%s'\n", b);
    printf("\n");
    exit(1);
  }
}

void
test_buffer_new() {
  buffer_t *buf = buffer_new();
  assert(64 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_new_with_size() {
  buffer_t *buf = buffer_new_with_size(1024);
  assert(1024 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_append() {
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " World"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", (buf->data));
  buffer_free(buf);
}

void
test_buffer_append_n() {
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append_n(buf, "subway", 3));
  assert(0 == buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == buffer_length(buf));
  equal("submarine", (buf->data));
  buffer_free(buf);
}

void
test_buffer_append__grow() {
  buffer_t *buf = buffer_new_with_size(10);
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " tobi"));
  assert(0 == buffer_append(buf, " was"));
  assert(0 == buffer_append(buf, " here"));

  char *str = "Hello tobi was here";
  equal(str, (buf->data));
  assert(1024 == buffer_size(buf));
  assert(strlen(str) == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_prepend() {
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, " World"));
  assert(0 == buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", (buf->data));
  buffer_free(buf);
}

void
test_buffer_slice() {
  buffer_t *buf = buffer_new();
  buffer_append(buf, "Tobi Ferret");

  buffer_t *a = buffer_slice(buf, 2, 8);
  equal("Tobi Ferret", (buf->data));
  equal("bi Fer", (a->data));

  buffer_free(buf);
  buffer_free(a);
}

void
test_buffer_slice__range_error() {
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 10, 2);
  assert(0 == a);
  buffer_free(buf);
}

void
test_buffer_slice__end() {
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");

  buffer_t *a = buffer_slice(buf, 5, -1);
  equal("Tobi Ferret", (buf->data));
  equal("Ferret", (a->data));

  buffer_t *b = buffer_slice(buf, 5, -3);
  equal("Ferr", (b->data));

  buffer_t *c = buffer_slice(buf, 8, -1);
  equal("ret", (c->data));

  buffer_free(buf);
  buffer_free(a);
  buffer_free(b);
  buffer_free(c);
}

void
test_buffer_slice__end_overflow() {
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", (buf->data));
  equal("Ferret", (a->data));
  buffer_free(a);
  buffer_free(buf);
}

void
test_buffer_equals() {
  buffer_t *a = buffer_new_with_copy("Hello");
  buffer_t *b = buffer_new_with_copy("Hello");

  assert(1 == buffer_equals(a, b));

  buffer_append(b, " World");
  assert(0 == buffer_equals(a, b));

  buffer_free(a);
  buffer_free(b);
}

void test_buffer_formatting() {
  buffer_t *buf = buffer_new();
  int result = buffer_appendf(buf, "%d %s", 3, "cow");
  assert(0 == result);
  equal("3 cow", (buf->data));
  result = buffer_appendf(buf, " - 0x%08X", 0xdeadbeef);
  assert(0 == result);
  equal("3 cow - 0xDEADBEEF", (buf->data));
  buffer_free(buf);
}

void
test_buffer_indexof() {
  buffer_t *buf = buffer_new_with_copy("Tobi is a ferret");

  ssize_t i = buffer_indexof(buf, "is");
  assert(5 == i);

  i = buffer_indexof(buf, "a");
  assert(8 == i);

  i = buffer_indexof(buf, "something");
  assert(-1 == i);

  buffer_free(buf);
}

void
test_buffer_fill() {
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));

  buffer_fill(buf, 0);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_clear() {
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));

  buffer_clear(buf);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void
test_buffer_trim() {
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim(buf);
  equal("Hello", (buf->data));
  buffer_free(buf);

  buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_left(buf);
  equal("Hello\n\n ", (buf->data));
  buffer_free(buf);

  buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_right(buf);
  equal("  Hello", (buf->data));
  buffer_free(buf);
}

void
test_buffer_compact() {
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim(buf);
  assert(5 == buffer_length(buf));
  assert(10 == buffer_size(buf));

  ssize_t removed = buffer_compact(buf);
  assert(5 == removed);
  assert(5 == buffer_length(buf));
  assert(5 == buffer_size(buf));
  equal("Hello", (buf->data));

  buffer_free(buf);
}

int
main(){
  test_buffer_new();
  test_buffer_new_with_size();
  test_buffer_append();
  test_buffer_append__grow();
  test_buffer_append_n();
  test_buffer_prepend();
  test_buffer_slice();
  test_buffer_slice__range_error();
  test_buffer_slice__end();
  test_buffer_slice__end_overflow();
  test_buffer_equals();
  test_buffer_formatting();
  test_buffer_indexof();
  test_buffer_fill();
  test_buffer_clear();
  test_buffer_trim();
  test_buffer_compact();
  printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
  return 0;
}
