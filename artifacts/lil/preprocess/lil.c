# 0 "/app/subjects/lil/lil.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/lil/lil.c"
# 25 "/app/subjects/lil/lil.c"
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
# 26 "/app/subjects/lil/lil.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 27 "/app/subjects/lil/lil.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 28 "/app/subjects/lil/lil.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 29 "/app/subjects/lil/lil.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/math.h" 1
# 30 "/app/subjects/lil/lil.c" 2
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
# 31 "/app/subjects/lil/lil.c" 2
# 61 "/app/subjects/lil/lil.c"
struct hashentry_t
{
    char* k;
    void* v;
};

struct hashcell_t
{
    struct hashentry_t* e;
    size_t c;
};

typedef struct _hashmap_t
{
    struct hashcell_t cell[256];
} hashmap_t;

struct _lil_value_t
{
    size_t l;



    char* d;
};

struct _lil_var_t
{
    char* n;
    char* w;
    struct _lil_env_t* env;
    lil_value_t v;
};

struct _lil_env_t
{
    struct _lil_env_t* parent;
    lil_func_t func;
    lil_value_t catcher_for;
    lil_var_t* var;
    size_t vars;
    hashmap_t varmap;
    lil_value_t retval;
    int retval_set;
    int breakrun;
};

struct _lil_list_t
{
    lil_value_t* v;
    size_t c;
    size_t cap;
};

struct _lil_func_t
{
    char* name;
    lil_value_t code;
    lil_list_t argnames;
    lil_func_proc_t proc;
};

struct _lil_t
{
    const char* code;
    const char* rootcode;
    size_t clen;
    size_t head;
    int ignoreeol;
    lil_func_t* cmd;
    size_t cmds;
    size_t syscmds;
    hashmap_t cmdmap;
    char* catcher;
    int in_catcher;
    char* dollarprefix;
    lil_env_t env;
    lil_env_t rootenv;
    lil_env_t downenv;
    lil_value_t empty;
    int error;
    size_t err_head;
    char* err_msg;
    lil_callback_proc_t callback[8];
    size_t parse_depth;
    void* data;
    char* embed;
    size_t embedlen;
};

typedef struct _expreval_t
{
    const char* code;
    size_t len, head;
    lilint_t ival;
    double dval;
    int type;
    int error;
} expreval_t;

static lil_value_t next_word(lil_t lil);
static void register_stdcmds(lil_t lil);
# 173 "/app/subjects/lil/lil.c"
static char* strclone(const char* s)
{
    size_t len = strlen(s) + 1;
    char* ns = malloc(len);
    if (!ns) return 0;
    memcpy(ns, s, len);
    return ns;
}

static unsigned long hm_hash(const char* key)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

static void hm_init(hashmap_t* hm)
{
    memset(hm, 0, sizeof(hashmap_t));
}

static void hm_destroy(hashmap_t* hm)
{
    size_t i, j;
    for (i=0; i<256; i++) {
        for (j=0; j<hm->cell[i].c; j++)
            free(hm->cell[i].e[j].k);
        free(hm->cell[i].e);
    }
}

static void hm_put(hashmap_t* hm, const char* key, void* value)
{
    struct hashcell_t* cell = hm->cell + (hm_hash(key) & 0xFF);
    size_t i;
    for (i=0; i<cell->c; i++)
        if (!strcmp(key, cell->e[i].k)) {
            cell->e[i].v = value;
            return;
        }
    cell->e = realloc(cell->e, sizeof(struct hashentry_t)*(cell->c + 1));
    cell->e[cell->c].k = strclone(key);
    cell->e[cell->c].v = value;
    cell->c++;
}

static void* hm_get(hashmap_t* hm, const char* key)
{
    struct hashcell_t* cell = hm->cell + (hm_hash(key) & 0xFF);
    size_t i;
    for (i = 0; i<cell->c; i++)
        if (!strcmp(key, cell->e[i].k))
            return cell->e[i].v;
    return 0;
}

static int hm_has(hashmap_t* hm, const char* key)
{
    struct hashcell_t* cell = hm->cell + (hm_hash(key) & 0xFF);
    size_t i;
    for (i = 0; i < cell->c; i++)
        if (!strcmp(key, cell->e[i].k))
            return 1;
    return 0;
}
# 270 "/app/subjects/lil/lil.c"
static lil_value_t alloc_value_len(const char* str, size_t len)
{



    lil_value_t val = calloc(1, sizeof(struct _lil_value_t));

    if (!val) return 0;
    if (str) {
        val->l = len;



        val->d = malloc(len + 1);
        if (!val->d) {
            free(val);
            return 0;
        }

        memcpy(val->d, str, len);
        val->d[len] = 0;
    } else {
        val->l = 0;




        val->d = 0;

    }
    return val;
}

static lil_value_t alloc_value(const char* str)
{
    return alloc_value_len(str, str ? strlen(str) : 0);
}

lil_value_t lil_clone_value(lil_value_t src)
{
    lil_value_t val;
    if (!src) return 0;



    val = calloc(1, sizeof(struct _lil_value_t));

    if (!val) return 0;
    val->l = src->l;
    if (src->l) {



        val->d = malloc(val->l + 1);
        if (!val->d) {
            free(val);
            return 0;
        }

        memcpy(val->d, src->d, val->l + 1);
    } else {




        val->d = 0;

    }
    return val;
}

int lil_append_char(lil_value_t val, char ch)
{





    char* new = realloc(val->d, val->l + 2);
    if (!new) return 0;
    new[val->l++] = ch;
    new[val->l] = 0;
    val->d = new;

    return 1;
}

int lil_append_string_len(lil_value_t val, const char* s, size_t len)
{

    char* new;

    if (!s || !s[0]) return 1;




    new = realloc(val->d, val->l + len + 1);
    if (!new) return 0;
    memcpy(new + val->l, s, len + 1);
    val->d = new;

    val->l += len;
    return 1;
}

int lil_append_string(lil_value_t val, const char* s)
{
    return lil_append_string_len(val, s, strlen(s));
}

int lil_append_val(lil_value_t val, lil_value_t v)
{

    char* new;

    if (!v || !v->l) return 1;




    new = realloc(val->d, val->l + v->l + 1);
    if (!new) return 0;
    memcpy(new + val->l, v->d, v->l + 1);
    val->d = new;

    val->l += v->l;
    return 1;
}

void lil_free_value(lil_value_t val)
{
    if (!val) return;



    free(val->d);
    free(val);

}

lil_list_t lil_alloc_list(void)
{
    lil_list_t list;




    list = calloc(1, sizeof(struct _lil_list_t));
    list->v = 0;
    return list;
}

void lil_free_list(lil_list_t list)
{
    size_t i;
    if (!list) return;
    for (i = 0; i<list->c; i++) lil_free_value(list->v[i]);
# 436 "/app/subjects/lil/lil.c"
    free(list->v);
    free(list);

}

void lil_list_append(lil_list_t list, lil_value_t val)
{
    if (list->c == list->cap) {
        size_t cap = list->cap ? (list->cap + list->cap / 2) : 32;
        lil_value_t* nv = realloc(list->v, sizeof(lil_value_t)*cap);
        if (!nv) return;
        list->cap = cap;
        list->v = nv;
    }
    list->v[list->c++] = val;
}

size_t lil_list_size(lil_list_t list)
{
    return list->c;
}

lil_value_t lil_list_get(lil_list_t list, size_t index)
{
    return index >= list->c ? 0 : list->v[index];
}

static int needs_escape(const char* str)
{
    size_t i;
    if (!str || !str[0]) return 1;
    for (i=0; str[i]; i++)
        if (ispunct(str[i]) || isspace(str[i])) return 1;
    return 0;
}

lil_value_t lil_list_to_value(lil_list_t list, int do_escape)
{
    lil_value_t val = alloc_value(0);
    size_t i, j;
    for (i=0; i<list->c; i++) {
        int escape = do_escape ? needs_escape(lil_to_string(list->v[i])) : 0;
        if (i) lil_append_char(val, ' ');
        if (escape) {
            lil_append_char(val, '{');
            for (j=0; j < list->v[i]->l; j++) {
                if (list->v[i]->d[j] == '{')
                    lil_append_string(val, "}\"\\o\"{");
                else if (list->v[i]->d[j] == '}')
                    lil_append_string(val, "}\"\\c\"{");
                else lil_append_char(val, list->v[i]->d[j]);
            }
            lil_append_char(val, '}');
        } else lil_append_val(val, list->v[i]);
    }
    return val;
}

lil_env_t lil_alloc_env(lil_env_t parent)
{
    lil_env_t env;
# 517 "/app/subjects/lil/lil.c"
    env = calloc(1, sizeof(struct _lil_env_t));
    env->parent = parent;
    return env;
}

void lil_free_env(lil_env_t env)
{
    size_t i;
    if (!env) return;
    lil_free_value(env->retval);
# 541 "/app/subjects/lil/lil.c"
    hm_destroy(&env->varmap);
    for (i=0; i<env->vars; i++) {
        free(env->var[i]->n);
        lil_free_value(env->var[i]->v);
        free(env->var[i]->w);
        free(env->var[i]);
    }
    free(env->var);
    free(env);

}

static lil_var_t lil_find_local_var(lil_t lil, lil_env_t env, const char* name)
{
# 566 "/app/subjects/lil/lil.c"
    return hm_get(&env->varmap, name);

}

static lil_var_t lil_find_var(lil_t lil, lil_env_t env, const char* name)
{
    lil_var_t r = lil_find_local_var(lil, env, name);
    return r ? r : (env == lil->rootenv ? 0 : lil_find_var(lil, lil->rootenv, name));
}

static lil_func_t find_cmd(lil_t lil, const char* name)
{
# 589 "/app/subjects/lil/lil.c"
    return hm_get(&lil->cmdmap, name);

}

static lil_func_t add_func(lil_t lil, const char* name)
{
    lil_func_t cmd;
    lil_func_t* ncmd;
    cmd = find_cmd(lil, name);
    if (cmd) {
        if (cmd->argnames) lil_free_list(cmd->argnames);
        lil_free_value(cmd->code);
        cmd->argnames = 0;
        cmd->code = 0;
        cmd->proc = 0;
        return cmd;
    }
    cmd = calloc(1, sizeof(struct _lil_func_t));
    cmd->name = strclone(name);
    ncmd = realloc(lil->cmd, sizeof(lil_func_t)*(lil->cmds + 1));
    if (!ncmd) {
        free(cmd);
        return 0;
    }
    lil->cmd = ncmd;
    ncmd[lil->cmds++] = cmd;
    hm_put(&lil->cmdmap, name, cmd);
    return cmd;
}

static void del_func(lil_t lil, lil_func_t cmd)
{
    size_t i, index = lil->cmds;
    for (i=0; i < lil->cmds; i++)
        if (lil->cmd[i] == cmd) {
            index = i;
            break;
        }
    if (index == lil->cmds) return;
    hm_put(&lil->cmdmap, cmd->name, 0);
    if (cmd->argnames) lil_free_list(cmd->argnames);
    lil_free_value(cmd->code);
    free(cmd->name);
    free(cmd);
    lil->cmds--;
    for (i=index; i < lil->cmds; i++) lil->cmd[i] = lil->cmd[i + 1];
}

int lil_register(lil_t lil, const char* name, lil_func_proc_t proc)
{
    lil_func_t cmd = add_func(lil, name);
    if (!cmd) return 0;
    cmd->proc = proc;
    return 1;
}

lil_var_t lil_set_var(lil_t lil, const char* name, lil_value_t val, int local)
{
    lil_var_t* nvar;
    lil_env_t env = local == 0 ? lil->rootenv : lil->env;
    int freeval = 0;
    if (!name[0]) return 0;
    if (local != 2) {
        lil_var_t var = lil_find_var(lil, env, name);
        if (local == 3 && var && var->env == lil->rootenv && var->env != env)
            var = 0;
        if (((!var && env == lil->rootenv) || (var && var->env == lil->rootenv)) && lil->callback[6]) {
            lil_setvar_callback_proc_t proc = (lil_setvar_callback_proc_t)lil->callback[6];
            lil_value_t newval = val;
            int r = proc(lil, name, &newval);
            if (r < 0) return 0;
            if (r) {
                val = newval;
                freeval = 1;
            }
        }
        if (var) {
            lil_free_value(var->v);
            var->v = freeval ? val : lil_clone_value(val);
            if (var->w) {
                lil_env_t save_env;
                save_env = lil->env;
                lil->env = var->env;
                lil_free_value(lil_parse(lil, var->w, 0, 1));
                lil->env = save_env;
            }
            return var;
        }
    }

    nvar = realloc(env->var, sizeof(lil_var_t)*(env->vars + 1));
    if (!nvar) {

        return 0;
    }
    env->var = nvar;
    nvar[env->vars] = calloc(1, sizeof(struct _lil_var_t));
    nvar[env->vars]->n = strclone(name);
    nvar[env->vars]->w = 0;
    nvar[env->vars]->env = env;
    nvar[env->vars]->v = freeval ? val : lil_clone_value(val);
    hm_put(&env->varmap, name, nvar[env->vars]);
    return nvar[env->vars++];
}

lil_value_t lil_get_var(lil_t lil, const char* name)
{
    return lil_get_var_or(lil, name, lil->empty);
}

lil_value_t lil_get_var_or(lil_t lil, const char* name, lil_value_t defvalue)
{
    lil_var_t var = lil_find_var(lil, lil->env, name);
    lil_value_t retval = var ? var->v : defvalue;
    if (lil->callback[7] && (!var || var->env == lil->rootenv)) {
        lil_getvar_callback_proc_t proc = (lil_getvar_callback_proc_t)lil->callback[7];
        lil_value_t newretval = retval;
        if (proc(lil, name, &newretval))
            retval = newretval;
    }
    return retval;
}

lil_env_t lil_push_env(lil_t lil)
{
    lil_env_t env = lil_alloc_env(lil->env);
    lil->env = env;
    return env;
}

void lil_pop_env(lil_t lil)
{
    if (lil->env->parent) {
        lil_env_t next = lil->env->parent;
        lil_free_env(lil->env);
        lil->env = next;
    }
}

lil_t lil_new(void)
{
    lil_t lil = calloc(1, sizeof(struct _lil_t));
    lil->rootenv = lil->env = lil_alloc_env(0);
    lil->empty = alloc_value(0);
    lil->dollarprefix = strclone("set ");
    hm_init(&lil->cmdmap);
    register_stdcmds(lil);
    return lil;
}

static int islilspecial(char ch)
{
    return ch == '$' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '"' || ch == '\'' || ch == ';';
}

static int ateol(lil_t lil)
{
    return !(lil->ignoreeol) && (lil->code[lil->head] == '\n' || lil->code[lil->head] == '\r' || lil->code[lil->head] == ';');
}

static void skip_spaces(lil_t lil)
{
    while (lil->head < lil->clen) {
        if (lil->code[lil->head] == '#') {
            if (lil->code[lil->head + 1] == '#' && lil->code[lil->head + 2] != '#') {
                lil->head += 2;
                while (lil->head < lil->clen) {
                    if ((lil->code[lil->head] == '#') && (lil->code[lil->head + 1] == '#') && (lil->code[lil->head + 2] != '#')) {
                        lil->head += 2;
                        break;
                    }
                    lil->head++;
                }
            } else {
                while (lil->head < lil->clen && !ateol(lil)) lil->head++;
            }
        } else if (lil->code[lil->head] == '\\' && (lil->code[lil->head + 1] == '\r' || lil->code[lil->head + 1] == '\n')) {
            lil->head++;
            while (lil->head < lil->clen && ateol(lil)) lil->head++;
        } else if (lil->code[lil->head] == '\r' || lil->code[lil->head] == '\n') {
            if (lil->ignoreeol) lil->head++;
            else break;
        } else if (isspace(lil->code[lil->head]))
            lil->head++;
        else break;
    }
}

static lil_value_t get_bracketpart(lil_t lil)
{
    size_t cnt = 1;
    lil_value_t val, cmd = alloc_value(0);
    lil->head++;
    while (lil->head < lil->clen) {
        if (lil->code[lil->head] == '[') {
            lil->head++;
            cnt++;
            lil_append_char(cmd, '[');
        } else if (lil->code[lil->head] == ']') {
            lil->head++;
            if (--cnt == 0) break;
            else lil_append_char(cmd, ']');
        } else {
            lil_append_char(cmd, lil->code[lil->head++]);
        }
    }
    val = lil_parse_value(lil, cmd, 0);
    lil_free_value(cmd);
    return val;
}

static lil_value_t get_dollarpart(lil_t lil)
{
    lil_value_t val, name, tmp;
    lil->head++;
    name = next_word(lil);
    tmp = alloc_value(lil->dollarprefix);
    lil_append_val(tmp, name);
    lil_free_value(name);
    val = lil_parse_value(lil, tmp, 0);
    lil_free_value(tmp);
    return val;
}

static lil_value_t next_word(lil_t lil)
{
    lil_value_t val;
    size_t start;
    skip_spaces(lil);
    if (lil->code[lil->head] == '$') {
        val = get_dollarpart(lil);
    } else if (lil->code[lil->head] == '{') {
        size_t cnt = 1;
        lil->head++;
        val = alloc_value(0);
        while (lil->head < lil->clen) {
            if (lil->code[lil->head] == '{') {
                lil->head++;
                cnt++;
                lil_append_char(val, '{');
            } else if (lil->code[lil->head] == '}') {
                lil->head++;
                if (--cnt == 0) break;
                else lil_append_char(val, '}');
            } else {
                lil_append_char(val, lil->code[lil->head++]);
            }
        }
    } else if (lil->code[lil->head] == '[') {
        val = get_bracketpart(lil);
    } else if (lil->code[lil->head] == '"' || lil->code[lil->head] == '\'') {
        char sc = lil->code[lil->head++];
        val = alloc_value(0);
        while (lil->head < lil->clen) {
            if (lil->code[lil->head] == '[' || lil->code[lil->head] == '$') {
                lil_value_t tmp = lil->code[lil->head] == '$' ? get_dollarpart(lil) : get_bracketpart(lil);
                lil_append_val(val, tmp);
                lil_free_value(tmp);
                lil->head--;
            } else if (lil->code[lil->head] == '\\') {
                lil->head++;
                switch (lil->code[lil->head]) {
                    case 'b': lil_append_char(val, '\b'); break;
                    case 't': lil_append_char(val, '\t'); break;
                    case 'n': lil_append_char(val, '\n'); break;
                    case 'v': lil_append_char(val, '\v'); break;
                    case 'f': lil_append_char(val, '\f'); break;
                    case 'r': lil_append_char(val, '\r'); break;
                    case '0': lil_append_char(val, 0); break;
                    case 'a': lil_append_char(val, '\a'); break;
                    case 'c': lil_append_char(val, '}'); break;
                    case 'o': lil_append_char(val, '{'); break;
                    default: lil_append_char(val, lil->code[lil->head]); break;
                }
            } else if (lil->code[lil->head] == sc) {
                lil->head++;
                break;
            } else {
                lil_append_char(val, lil->code[lil->head]);
            }
            lil->head++;
        }
    } else {
        start = lil->head;
        while (lil->head < lil->clen && !isspace(lil->code[lil->head]) && !islilspecial(lil->code[lil->head])) {
            lil->head++;
        }
        val = alloc_value_len(lil->code + start, lil->head - start);
    }
    return val ? val : alloc_value(0);
}

static lil_list_t substitute(lil_t lil)
{
    lil_list_t words = lil_alloc_list();

    skip_spaces(lil);
    while (lil->head < lil->clen && !ateol(lil) && !lil->error) {
        lil_value_t w = alloc_value(0);
        do {
            size_t head = lil->head;
            lil_value_t wp = next_word(lil);
            if (head == lil->head) {
                lil_free_value(w);
                lil_free_value(wp);
                lil_free_list(words);
                return 0;
            }
            lil_append_val(w, wp);
            lil_free_value(wp);
        } while (lil->head < lil->clen && !ateol(lil) && !isspace(lil->code[lil->head]) && !lil->error);
        skip_spaces(lil);

        lil_list_append(words, w);
    }

    return words;
}

lil_list_t lil_subst_to_list(lil_t lil, lil_value_t code)
{
    const char* save_code = lil->code;
    size_t save_clen = lil->clen;
    size_t save_head = lil->head;
    int save_igeol = lil->ignoreeol;
    lil_list_t words;
    lil->code = lil_to_string(code);
    lil->clen = code->l;
    lil->head = 0;
    lil->ignoreeol = 1;
    words = substitute(lil);
    if (!words) words = lil_alloc_list();
    lil->code = save_code;
    lil->clen = save_clen;
    lil->head = save_head;
    lil->ignoreeol = save_igeol;
    return words;
}

lil_value_t lil_subst_to_value(lil_t lil, lil_value_t code)
{
    lil_list_t words = lil_subst_to_list(lil, code);
    lil_value_t val;
    val = lil_list_to_value(words, 0);
    lil_free_list(words);
    return val;
}

lil_value_t lil_parse(lil_t lil, const char* code, size_t codelen, int funclevel)
{
    const char* save_code = lil->code;
    size_t save_clen = lil->clen;
    size_t save_head = lil->head;
    lil_value_t val = 0;
    lil_list_t words = 0;
    if (!save_code) lil->rootcode = code;
    lil->code = code;
    lil->clen = codelen ? codelen : strlen(code);
    lil->head = 0;
    skip_spaces(lil);
    lil->parse_depth++;






    if (lil->parse_depth == 1) lil->error = 0;
    if (funclevel) lil->env->breakrun = 0;
    while (lil->head < lil->clen && !lil->error) {
        if (words) lil_free_list(words);
        if (val) lil_free_value(val);
        val = 0;

        words = substitute(lil);
        if (!words || lil->error) goto cleanup;

        if (words->c) {
            lil_func_t cmd = find_cmd(lil, lil_to_string(words->v[0]));
            if (!cmd) {
                if (words->v[0]->l) {
                    if (lil->catcher) {
                        if (lil->in_catcher < 16384) {
                            lil_value_t args;
                            lil->in_catcher++;
                            lil_push_env(lil);
                            lil->env->catcher_for = words->v[0];
                            args = lil_list_to_value(words, 1);
                            lil_set_var(lil, "args", args, 2);
                            lil_free_value(args);
                            val = lil_parse(lil, lil->catcher, 0, 1);
                            lil_pop_env(lil);
                            lil->in_catcher--;
                        } else {
                            char* msg = malloc(words->v[0]->l + 64);
                            sprintf(msg, "catcher limit reached while trying to call unknown function %s", words->v[0]->d);
                            lil_set_error_at(lil, lil->head, msg);
                            free(msg);
                            goto cleanup;
                        }
                    } else {
                        char* msg = malloc(words->v[0]->l + 32);
                        sprintf(msg, "unknown function %s", words->v[0]->d);
                        lil_set_error_at(lil, lil->head, msg);
                        free(msg);
                        goto cleanup;
                    }
                }
            }
            if (cmd) {
                if (cmd->proc) {
                    size_t shead = lil->head;
                    val = cmd->proc(lil, words->c - 1, words->v + 1);
                    if (lil->error == 2) {
                        lil->error = 1;
                        lil->err_head = shead;
                    }
                } else {
                    lil_push_env(lil);
                    lil->env->func = cmd;
                    if (cmd->argnames->c == 1 && !strcmp(lil_to_string(cmd->argnames->v[0]), "args")) {
                        lil_value_t args = lil_list_to_value(words, 1);
                        lil_set_var(lil, "args", args, 2);
                        lil_free_value(args);
                    } else {
                        size_t i;
                        for (i=0; i<cmd->argnames->c; i++) {
                            lil_set_var(lil, lil_to_string(cmd->argnames->v[i]), i < words->c - 1 ? words->v[i + 1] : lil->empty, 2);
                        }
                    }
                    val = lil_parse_value(lil, cmd->code, 1);
                    lil_pop_env(lil);
                }
            }
        }

        if (lil->env->breakrun) goto cleanup;

        skip_spaces(lil);
        while (ateol(lil)) lil->head++;
        skip_spaces(lil);
    }
cleanup:
    if (lil->error && lil->callback[5] && lil->parse_depth == 1) {
        lil_error_callback_proc_t proc = (lil_error_callback_proc_t)lil->callback[5];
        proc(lil, lil->err_head, lil->err_msg);
    }
    if (words) lil_free_list(words);
    lil->code = save_code;
    lil->clen = save_clen;
    lil->head = save_head;
    if (funclevel && lil->env->retval_set) {
        if (val) lil_free_value(val);
        val = lil->env->retval;
        lil->env->retval = 0;
        lil->env->retval_set = 0;
        lil->env->breakrun = 0;
    }
    lil->parse_depth--;
    return val ? val : alloc_value(0);
}

lil_value_t lil_parse_value(lil_t lil, lil_value_t val, int funclevel)
{
    if (!val || !val->d || !val->l) return alloc_value(0);
    return lil_parse(lil, val->d, val->l, funclevel);
}

 lil_value_t lil_call(lil_t lil, const char* funcname, size_t argc, lil_value_t* argv)
{
    lil_func_t cmd = find_cmd(lil, funcname);
    lil_value_t r = 0;
    if (cmd) {
        if (cmd->proc)
            r = cmd->proc(lil, argc, argv);
        else {
            size_t i;
            lil_push_env(lil);
            lil->env->func = cmd;
            if (cmd->argnames->c == 1 && !strcmp(lil_to_string(cmd->argnames->v[0]), "args")) {
                lil_list_t args = lil_alloc_list();
                lil_value_t argsval;
                for (i=0; i<argc; i++)
                    lil_list_append(args, lil_clone_value(argv[i]));
                argsval = lil_list_to_value(args, 0);
                lil_set_var(lil, "args", argsval, 2);
                lil_free_value(argsval);
                lil_free_list(args);
            } else {
                for (i=0; i<cmd->argnames->c; i++)
                    lil_set_var(lil, lil_to_string(cmd->argnames->v[i]), i < argc ? argv[i] : 0, 2);
            }
            r = lil_parse_value(lil, cmd->code, 1);
            lil_pop_env(lil);
        }
    }
    return r;
}

void lil_callback(lil_t lil, int cb, lil_callback_proc_t proc)
{
    if (cb < 0 || cb > 8) return;
    lil->callback[cb] = proc;
}

void lil_set_error(lil_t lil, const char* msg)
{
    if (lil->error) return;
    free(lil->err_msg);
    lil->error = 2;
    lil->err_head = 0;
    lil->err_msg = strclone(msg ? msg : "");
}

void lil_set_error_at(lil_t lil, size_t pos, const char* msg)
{
    if (lil->error) return;
    free(lil->err_msg);
    lil->error = 1;
    lil->err_head = pos;
    lil->err_msg = strclone(msg ? msg : "");
}

int lil_error(lil_t lil, const char** msg, size_t* pos)
{
    if (!lil->error) return 0;
    *msg = lil->err_msg;
    *pos = lil->err_head;
    lil->error = 0;
    return 1;
}
# 1129 "/app/subjects/lil/lil.c"
static void ee_expr(expreval_t* ee);

static int ee_invalidpunct(int ch)
{
    return ispunct(ch) && ch != '!' && ch != '~' && ch != '(' && ch != ')' && ch != '-' && ch != '+';
}

static void ee_skip_spaces(expreval_t* ee)
{
    while (ee->head < ee->len && isspace(ee->code[ee->head])) ee->head++;
}

static void ee_numeric_element(expreval_t* ee)
{
    lilint_t fpart = 0, fpartlen = 1;
    ee->type = 0;
    ee_skip_spaces(ee);
    ee->ival = 0;
    ee->dval = 0;
    while (ee->head < ee->len) {
        if (ee->code[ee->head] == '.') {
            if (ee->type == 1) break;
            ee->type = 1;
            ee->head++;
        } else if (!isdigit(ee->code[ee->head])) break;
        if (ee->type == 0)
            ee->ival = ee->ival*10 + (ee->code[ee->head] - '0');
        else {
            fpart = fpart*10 + (ee->code[ee->head] - '0');
            fpartlen *= 10;
        }
        ee->head++;
    }
    if (ee->type == 1)
        ee->dval = ee->ival + (double)fpart/(double)fpartlen;
}

static void ee_element(expreval_t* ee)
{
    if (isdigit(ee->code[ee->head])) {
        ee_numeric_element(ee);
        return;
    }




    ee->type = 0;
    ee->ival = 1;
    ee->error = 4;
}

static void ee_paren(expreval_t* ee)
{
    ee_skip_spaces(ee);
    if (ee->code[ee->head] == '(') {
        ee->head++;
        ee_expr(ee);
        ee_skip_spaces(ee);
        if (ee->code[ee->head] == ')') ee->head++;
        else ee->error = 1;
    } else ee_element(ee);
}

static void ee_unary(expreval_t* ee)
{
    ee_skip_spaces(ee);
    if (ee->head < ee->len && !ee->error &&
        (ee->code[ee->head] == '-' ||
         ee->code[ee->head] == '+' ||
         ee->code[ee->head] == '~' ||
         ee->code[ee->head] == '!')) {
        char op = ee->code[ee->head++];
        ee_unary(ee);
        if (ee->error) return;
        switch (op) {
        case '-':
            switch (ee->type) {
            case 1:
                ee->dval = -ee->dval;
                break;
            case 0:
                ee->ival = -ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case '+':

            break;
        case '~':
            switch (ee->type) {
            case 1:
                ee->ival = ~((lilint_t)ee->dval);
                ee->type = 0;
                break;
            case 0:
                ee->ival = ~ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case '!':
            switch (ee->type) {
            case 1:
                ee->dval = !ee->dval;
                break;
            case 0:
                ee->ival = !ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        }
    } else {
        ee_paren(ee);
    }
}

static void ee_muldiv(expreval_t* ee)
{
    ee_unary(ee);
    if (ee->error) return;
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error && !ee_invalidpunct(ee->code[ee->head + 1]) &&
        (ee->code[ee->head] == '*' ||
         ee->code[ee->head] == '/' ||
         ee->code[ee->head] == '\\' ||
         ee->code[ee->head] == '%')) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;

        switch (ee->code[ee->head]) {
        case '*':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->dval = ee->dval*odval;
                    break;
                case 0:
                    ee->dval = ee->ival*odval;
                    ee->type = 1;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->dval = ee->dval*oival;
                    ee->type = 1;
                    break;
                case 0:
                    ee->ival = ee->ival*oival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case '%':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    if (ee->dval == 0.0) {
                        ee->error = 3;
                    } else {
                        ee->dval = fmod(odval, ee->dval);
                    }
                    break;
                case 0:
                    if (ee->ival == 0) {
                        ee->error = 3;
                    } else {
                        ee->dval = fmod(odval, ee->ival);
                    }
                    ee->type = 1;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    if (ee->dval == 0.0) {
                        ee->error = 3;
                    } else {
                        ee->dval = fmod(oival, ee->dval);
                    }
                    break;
                case 0:
                    if (ee->ival == 0) {
                        ee->error = 3;
                    } else {
                        ee->ival = oival%ee->ival;
                    }
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            }
            break;
        case '/':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    if (ee->dval == 0.0) {
                        ee->error = 3;
                    } else {
                        ee->dval = odval/ee->dval;
                    }
                    break;
                case 0:
                    if (ee->ival == 0) {
                        ee->error = 3;
                    } else {
                        ee->dval = odval/(double)ee->ival;
                    }
                    ee->type = 1;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    if (ee->dval == 0.0) {
                        ee->error = 3;
                    } else {
                        ee->dval = (double)oival/ee->dval;
                    }
                    break;
                case 0:
                    if (ee->ival == 0) {
                        ee->error = 3;
                    } else {
                        ee->dval = (double)oival/(double)ee->ival;
                    }
                    ee->type = 1;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            }
            break;
        case '\\':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    if (ee->dval == 0.0) {
                        ee->error = 3;
                    } else {
                        ee->ival = (lilint_t)(odval/ee->dval);
                    }
                    ee->type = 0;
                    break;
                case 0:
                    if (ee->ival == 0) {
                        ee->error = 3;
                    } else {
                        ee->ival = (lilint_t)(odval/(double)ee->ival);
                    }
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_unary(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    if (ee->dval == 0.0) {
                        ee->error = 3;
                    } else {
                        ee->ival = (lilint_t)((double)oival/ee->dval);
                    }
                    ee->type = 0;
                    break;
                case 0:
                    if (ee->ival == 0) {
                        ee->error = 3;
                    } else {
                        ee->ival = oival/ee->ival;
                    }
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_addsub(expreval_t* ee)
{
    ee_muldiv(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error && !ee_invalidpunct(ee->code[ee->head + 1]) &&
        (ee->code[ee->head] == '+' ||
         ee->code[ee->head] == '-')) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;

        switch (ee->code[ee->head]) {
        case '+':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_muldiv(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->dval = ee->dval+odval;
                    break;
                case 0:
                    ee->dval = ee->ival+odval;
                    ee->type = 1;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_muldiv(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->dval = ee->dval+oival;
                    ee->type = 1;
                    break;
                case 0:
                    ee->ival = ee->ival+oival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case '-':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_muldiv(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->dval = odval-ee->dval;
                    break;
                case 0:
                    ee->dval = odval-ee->ival;
                    ee->type = 1;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_muldiv(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->dval = (double)oival-ee->dval;
                    ee->type = 1;
                    break;
                case 0:
                    ee->ival = oival-ee->ival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_shift(expreval_t* ee)
{
    ee_addsub(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        ((ee->code[ee->head] == '<' && ee->code[ee->head + 1] == '<') ||
         (ee->code[ee->head] == '>' && ee->code[ee->head + 1] == '>'))) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        ee->head++;

        switch (ee->code[ee->head]) {
        case '<':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_addsub(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (lilint_t)odval << (lilint_t)ee->dval;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (lilint_t)odval << ee->ival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_addsub(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = oival << (lilint_t)ee->dval;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = oival << ee->ival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case '>':
            switch (ee->type) {
            case 1:
                ee->head++;
                ee_addsub(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (lilint_t)odval >> (lilint_t)ee->dval;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (lilint_t)odval >> ee->ival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee->head++;
                ee_addsub(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = oival >> (lilint_t)ee->dval;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = oival >> ee->ival;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_compare(expreval_t* ee)
{
    ee_shift(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        ((ee->code[ee->head] == '<' && !ee_invalidpunct(ee->code[ee->head + 1])) ||
         (ee->code[ee->head] == '>' && !ee_invalidpunct(ee->code[ee->head + 1])) ||
         (ee->code[ee->head] == '<' && ee->code[ee->head + 1] == '=') ||
         (ee->code[ee->head] == '>' && ee->code[ee->head + 1] == '='))) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        int op = 4;
        if (ee->code[ee->head] == '<' && !ee_invalidpunct(ee->code[ee->head + 1])) op = 1;
        else if (ee->code[ee->head] == '>' && !ee_invalidpunct(ee->code[ee->head + 1])) op = 2;
        else if (ee->code[ee->head] == '<' && ee->code[ee->head + 1] == '=') op = 3;

        ee->head += op > 2 ? 2 : 1;

        switch (op) {
        case 1:
            switch (ee->type) {
            case 1:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (odval < ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (odval < ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (oival < ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (oival < ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 2:
            switch (ee->type) {
            case 1:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (odval > ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (odval > ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (oival > ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (oival > ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 3:
            switch (ee->type) {
            case 1:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (odval <= ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (odval <= ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (oival <= ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (oival <= ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 4:
            switch (ee->type) {
            case 1:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (odval >= ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (odval >= ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee_shift(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (oival >= ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (oival >= ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_equals(expreval_t* ee)
{
    ee_compare(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        ((ee->code[ee->head] == '=' && ee->code[ee->head + 1] == '=') ||
         (ee->code[ee->head] == '!' && ee->code[ee->head + 1] == '='))) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        int op = ee->code[ee->head] == '=' ? 1 : 2;
        ee->head += 2;

        switch (op) {
        case 1:
            switch (ee->type) {
            case 1:
                ee_compare(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (odval == ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (odval == ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee_compare(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (oival == ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (oival == ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 2:
            switch (ee->type) {
            case 1:
                ee_compare(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (odval != ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (odval != ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            case 0:
                ee_compare(ee);
                if (ee->error) return;
                switch (ee->type) {
                case 1:
                    ee->ival = (oival != ee->dval)?1:0;
                    ee->type = 0;
                    break;
                case 0:
                    ee->ival = (oival != ee->ival)?1:0;
                    break;
                default:
                    ee->error = 2;
                    break;
                }
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_bitand(expreval_t* ee)
{
    ee_equals(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        (ee->code[ee->head] == '&' && !ee_invalidpunct(ee->code[ee->head + 1]))) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        ee->head++;

        switch (ee->type) {
        case 1:
            ee_equals(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = (lilint_t)odval & (lilint_t)ee->dval;
                ee->type = 0;
                break;
            case 0:
                ee->ival = (lilint_t)odval & ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 0:
            ee_equals(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = oival & (lilint_t)ee->dval;
                ee->type = 0;
                break;
            case 0:
                ee->ival = oival & ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        default:
            ee->error = 2;
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_bitor(expreval_t* ee)
{
    ee_bitand(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        (ee->code[ee->head] == '|' && !ee_invalidpunct(ee->code[ee->head + 1]))) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        ee->head++;

        switch (ee->type) {
        case 1:
            ee_bitand(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = (lilint_t)odval | (lilint_t)ee->dval;
                ee->type = 0;
                break;
            case 0:
                ee->ival = (lilint_t)odval | ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 0:
            ee_bitand(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = oival | (lilint_t)ee->dval;
                ee->type = 0;
                break;
            case 0:
                ee->ival = oival | ee->ival;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        default:
            ee->error = 2;
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_logand(expreval_t* ee)
{
    ee_bitor(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        (ee->code[ee->head] == '&' && ee->code[ee->head + 1] == '&')) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        ee->head += 2;

        switch (ee->type) {
        case 1:
            ee_bitor(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = (odval && ee->dval)?1:0;
                ee->type = 0;
                break;
            case 0:
                ee->ival = (odval && ee->ival)?1:0;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 0:
            ee_bitor(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = (oival && ee->dval)?1:0;
                ee->type = 0;
                break;
            case 0:
                ee->ival = (oival && ee->ival)?1:0;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        default:
            ee->error = 2;
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_logor(expreval_t* ee)
{
    ee_logand(ee);
    ee_skip_spaces(ee);
    while (ee->head < ee->len && !ee->error &&
        (ee->code[ee->head] == '|' && ee->code[ee->head + 1] == '|')) {
        double odval = ee->dval;
        lilint_t oival = ee->ival;
        ee->head += 2;

        switch (ee->type) {
        case 1:
            ee_logand(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = (odval || ee->dval)?1:0;
                ee->type = 0;
                break;
            case 0:
                ee->ival = (odval || ee->ival)?1:0;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        case 0:
            ee_logand(ee);
            if (ee->error) return;
            switch (ee->type) {
            case 1:
                ee->ival = (oival || ee->dval)?1:0;
                ee->type = 0;
                break;
            case 0:
                ee->ival = (oival || ee->ival)?1:0;
                break;
            default:
                ee->error = 2;
                break;
            }
            break;
        default:
            ee->error = 2;
            break;
        }

        ee_skip_spaces(ee);
    }
}

static void ee_expr(expreval_t* ee)
{
    ee_logor(ee);


    if (ee->error == 4) {
        ee->error = 0;
        ee->ival = 1;
    }
}

lil_value_t lil_eval_expr(lil_t lil, lil_value_t code)
{
    expreval_t ee;
    code = lil_subst_to_value(lil, code);
    if (lil->error) return 0;
    ee.code = lil_to_string(code);


    if (!ee.code[0]) {
        lil_free_value(code);
        return lil_alloc_integer(0);
    }
    ee.head = 0;
    ee.len = code->l;
    ee.ival = 0;
    ee.dval = 0;
    ee.type = 0;
    ee.error = 0;
    ee_expr(&ee);
    lil_free_value(code);
    if (ee.error) {
        switch (ee.error) {
        case 3:
            lil_set_error(lil, "division by zero in expression");
            break;
        case 2:
            lil_set_error(lil, "mixing invalid types in expression");
            break;
        case 1:
            lil_set_error(lil, "expression syntax error");
            break;
        }
        return 0;
    }
    if (ee.type == 0)
        return lil_alloc_integer(ee.ival);
    else
        return lil_alloc_double(ee.dval);
}

lil_value_t lil_unused_name(lil_t lil, const char* part)
{
    char* name = malloc(strlen(part) + 64);
    lil_value_t val;
    size_t i;
    for (i=0; i<(size_t)-1; i++) {
        sprintf(name, "!!un!%s!%09u!nu!!", part, (unsigned int)i);
        if (find_cmd(lil, name)) continue;
        if (lil_find_var(lil, lil->env, name)) continue;
        val = lil_alloc_string(name);
        free(name);
        return val;
    }
    return 0;
}

lil_value_t lil_arg(lil_value_t* argv, size_t index)
{
    return argv ? argv[index] : 0;
}

const char* lil_to_string(lil_value_t val)
{
    return (val && val->l) ? val->d : "";
}

double lil_to_double(lil_value_t val)
{
    return atof(lil_to_string(val));
}

lilint_t lil_to_integer(lil_value_t val)
{
    return (lilint_t)atoll(lil_to_string(val));
}

int lil_to_boolean(lil_value_t val)
{
    const char* s = lil_to_string(val);
    size_t i, dots = 0;
    if (!s[0]) {return 0;}
    for (i=0; s[i]; i++) {
        if (s[i] != '0' && s[i] != '.') return 1;
        if (s[i] == '.') {
            if (dots) return 1;
            dots = 1;
        }
    }
    return 0;
}

lil_value_t lil_alloc_string(const char* str)
{
    return alloc_value(str);
}

lil_value_t lil_alloc_string_len(const char* str, size_t len)
{
    return alloc_value_len(str, len);
}

lil_value_t lil_alloc_double(double num)
{
    char buff[128];
    sprintf(buff, "%f", num);
    return alloc_value(buff);
}

lil_value_t lil_alloc_integer(lilint_t num)
{
    char buff[128];
    sprintf(buff, "%""i", num);
    return alloc_value(buff);
}

void lil_free(lil_t lil)
{
    size_t i;
    if (!lil) return;
    free(lil->err_msg);
    lil_free_value(lil->empty);
    while (lil->env) {
        lil_env_t next = lil->env->parent;
        lil_free_env(lil->env);
        lil->env = next;
    }
    for (i=0; i<lil->cmds; i++) {
        if (lil->cmd[i]->argnames)
            lil_free_list(lil->cmd[i]->argnames);
        lil_free_value(lil->cmd[i]->code);
        free(lil->cmd[i]->name);
        free(lil->cmd[i]);
    }
    hm_destroy(&lil->cmdmap);
    free(lil->cmd);
    free(lil->dollarprefix);
    free(lil->catcher);
    free(lil);
}

 void lil_set_data(lil_t lil, void* data)
{
    lil->data = data;
}

 void* lil_get_data(lil_t lil)
{
    return lil->data;
}

static void fnc_embed_write(lil_t lil, const char* msg)
{
    size_t len = strlen(msg) + 1;
    lil->embed = realloc(lil->embed, lil->embedlen + len);
    memcpy(lil->embed + lil->embedlen, msg, len);
    lil->embedlen += len - 1;
}

char* lil_embedded(lil_t lil, const char* code, unsigned int flags)
{
    char* prev_embed = lil->embed;
    size_t prev_embedlen = lil->embedlen;
    lil_callback_proc_t prev_write = lil->callback[1];
    char* lilcode = 0;
    size_t lilcodelen = 0;
    char* cont = 0;
    size_t contlen = 0;
    size_t head = 0, codelen = strlen(code);
    char* result;

    lil->callback[1] = (lil_callback_proc_t)fnc_embed_write;
    lil->embed = 0;
    lil->embedlen = 0;

    while (head < codelen) {
        if (head < codelen - 4 &&
            code[head] == '<' &&
            code[head + 1] == '?' &&
            code[head + 2] == 'l' &&
            code[head + 3] == 'i' &&
            code[head + 4] == 'l') {
            head += 5;
            if (contlen) {
                lilcode = realloc(lilcode, lilcodelen + contlen + 10);
                memcpy(lilcode + lilcodelen, "\nwrite {", 8);
                memcpy(lilcode + lilcodelen + 8, cont, contlen);
                lilcode[lilcodelen + contlen + 8] = '}';
                lilcode[lilcodelen + contlen + 9] = '\n';
                lilcodelen += contlen + 10;
                free(cont);
                cont = 0;
                contlen = 0;
            }
            while (head < codelen) {
                if (head < codelen - 1 && code[head] == '?' && code[head + 1] == '>') {
                    head += 2;
                    break;
                }
                lilcode = realloc(lilcode, lilcodelen + 1);
                lilcode[lilcodelen++] = code[head++];
            }
            lilcode = realloc(lilcode, lilcodelen + 1);
            lilcode[lilcodelen++] = '\n';
        } else {
            if (code[head] == '{' || code[head] == '}') {
                cont = realloc(cont, contlen + 6);
                cont[contlen++] = '}';
                cont[contlen++] = '"';
                cont[contlen++] = '\\';
                if (code[head] == '{')
                    cont[contlen++] = 'o';
                else
                    cont[contlen++] = 'c';
                cont[contlen++] = '"';
                cont[contlen++] = '{';
                head++;
            } else {
                cont = realloc(cont, contlen + 1);
                cont[contlen++] = code[head++];
            }
        }
    }
    if (contlen) {
        lilcode = realloc(lilcode, lilcodelen + contlen + 10);
        memcpy(lilcode + lilcodelen, "\nwrite {", 8);
        memcpy(lilcode + lilcodelen + 8, cont, contlen);
        lilcode[lilcodelen + contlen + 8] = '}';
        lilcode[lilcodelen + contlen + 9] = '\n';
        lilcodelen += contlen + 10;
        free(cont);
    }

    lilcode = realloc(lilcode, lilcodelen + 1);
    lilcode[lilcodelen] = 0;
    lil_free_value(lil_parse(lil, lilcode, 0, 1));
    free(lilcode);
    result = lil->embed ? lil->embed : strclone("");

    lil->embed = prev_embed;
    lil->embedlen = prev_embedlen;
    lil->callback[1] = prev_write;

    return result;
}

void lil_freemem(void* ptr)
{
    free(ptr);
}

void lil_write(lil_t lil, const char* msg)
{
    if (lil->callback[1]) {
        lil_write_callback_proc_t proc = (lil_write_callback_proc_t)lil->callback[1];
        proc(lil, msg);
    } else printf("%s", msg);
}

static lil_value_t fnc_reflect(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_func_t func;
    const char* type;
    size_t i;
    lil_value_t r;
    if (!argc) return 0;
    type = lil_to_string(argv[0]);
    if (!strcmp(type, "version")) {
        return lil_alloc_string("0.1");
    }
    if (!strcmp(type, "args")) {
        if (argc < 2) return 0;
        func = find_cmd(lil, lil_to_string(argv[1]));
        if (!func || !func->argnames) return 0;
        return lil_list_to_value(func->argnames, 1);
    }
    if (!strcmp(type, "body")) {
        if (argc < 2) return 0;
        func = find_cmd(lil, lil_to_string(argv[1]));
        if (!func || func->proc) return 0;
        return lil_clone_value(func->code);
    }
    if (!strcmp(type, "func-count")) {
        return lil_alloc_integer(lil->cmds);
    }
    if (!strcmp(type, "funcs")) {
        lil_list_t funcs = lil_alloc_list();
        for (i=0; i<lil->cmds; i++)
            lil_list_append(funcs, lil_alloc_string(lil->cmd[i]->name));
        r = lil_list_to_value(funcs, 1);
        lil_free_list(funcs);
        return r;
    }
    if (!strcmp(type, "vars")) {
        lil_list_t vars = lil_alloc_list();
        lil_env_t env = lil->env;
        while (env) {
            for (i=0; i<env->vars; i++)
                lil_list_append(vars, lil_alloc_string(env->var[i]->n));
            env = env->parent;
        }
        r = lil_list_to_value(vars, 1);
        lil_free_list(vars);
        return r;
    }
    if (!strcmp(type, "globals")) {
        lil_list_t vars = lil_alloc_list();
        for (i=0; i<lil->rootenv->vars; i++)
            lil_list_append(vars, lil_alloc_string(lil->rootenv->var[i]->n));
        r = lil_list_to_value(vars, 1);
        lil_free_list(vars);
        return r;
    }
    if (!strcmp(type, "has-func")) {
        const char* target;
        if (argc == 1) return 0;
        target = lil_to_string(argv[1]);
        return hm_has(&lil->cmdmap, target) ? lil_alloc_string("1") : 0;
    }
    if (!strcmp(type, "has-var")) {
        const char* target;
        lil_env_t env = lil->env;
        if (argc == 1) return 0;
        target = lil_to_string(argv[1]);
        while (env) {
            if (hm_has(&env->varmap, target)) return lil_alloc_string("1");
            env = env->parent;
        }
        return 0;
    }
    if (!strcmp(type, "has-global")) {
        const char* target;
        if (argc == 1) return 0;
        target = lil_to_string(argv[1]);
        for (i=0; i<lil->rootenv->vars; i++)
            if (!strcmp(target, lil->rootenv->var[i]->n)) return lil_alloc_string("1");
        return 0;
    }
    if (!strcmp(type, "error")) {
        return lil->err_msg ? lil_alloc_string(lil->err_msg) : 0;
    }
    if (!strcmp(type, "dollar-prefix")) {
        lil_value_t r;
        if (argc == 1) return lil_alloc_string(lil->dollarprefix);
        r = lil_alloc_string(lil->dollarprefix);
        free(lil->dollarprefix);
        lil->dollarprefix = strclone(lil_to_string(argv[1]));
        return r;
    }
    if (!strcmp(type, "this")) {
        lil_env_t env = lil->env;
        while (env != lil->rootenv && !env->catcher_for && !env->func) env = env->parent;
        if (env->catcher_for) return lil_alloc_string(lil->catcher);
        if (env == lil->rootenv) return lil_alloc_string(lil->rootcode);
        return env->func ? env->func->code : 0;
    }
    if (!strcmp(type, "name")) {
        lil_env_t env = lil->env;
        while (env != lil->rootenv && !env->catcher_for && !env->func) env = env->parent;
        if (env->catcher_for) return env->catcher_for;
        if (env == lil->rootenv) return 0;
        return env->func ? lil_alloc_string(env->func->name) : 0;
    }
    return 0;
}

static lil_value_t fnc_func(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t name;
    lil_func_t cmd;
    lil_list_t fargs;
    if (argc < 1) return 0;
    if (argc >= 3) {
        name = lil_clone_value(argv[0]);
        fargs = lil_subst_to_list(lil, argv[1]);
        cmd = add_func(lil, lil_to_string(argv[0]));
        cmd->argnames = fargs;
        cmd->code = lil_clone_value(argv[2]);
    } else {
        name = lil_unused_name(lil, "anonymous-function");
        if (argc < 2) {
            lil_value_t tmp = lil_alloc_string("args");
            fargs = lil_subst_to_list(lil, tmp);
            lil_free_value(tmp);
            cmd = add_func(lil, lil_to_string(name));
            cmd->argnames = fargs;
            cmd->code = lil_clone_value(argv[0]);
        } else {
            fargs = lil_subst_to_list(lil, argv[0]);
            cmd = add_func(lil, lil_to_string(name));
            cmd->argnames = fargs;
            cmd->code = lil_clone_value(argv[1]);
        }
    }
    return name;
}

static lil_value_t fnc_rename(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t r;
    lil_func_t func;
    const char* oldname;
    const char* newname;
    if (argc < 2) return 0;
    oldname = lil_to_string(argv[0]);
    newname = lil_to_string(argv[1]);
    func = find_cmd(lil, oldname);
    if (!func) {
        char* msg = malloc(24 + strlen(oldname));
        sprintf(msg, "unknown function '%s'", oldname);
        lil_set_error_at(lil, lil->head, msg);
        free(msg);
        return 0;
    }
    r = lil_alloc_string(func->name);
    if (newname[0]) {
        hm_put(&lil->cmdmap, oldname, 0);
        hm_put(&lil->cmdmap, newname, func);
        free(func->name);
        func->name = strclone(newname);
    } else {
        del_func(lil, func);
    }
    return r;
}

static lil_value_t fnc_unusedname(lil_t lil, size_t argc, lil_value_t* argv)
{
    return lil_unused_name(lil, argc > 0 ? lil_to_string(argv[0]) : "unusedname");
}

static lil_value_t fnc_quote(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t r;
    size_t i;
    if (argc < 1) return 0;
    r = alloc_value(0);
    for (i=0; i<argc; i++) {
        if (i) lil_append_char(r, ' ');
        lil_append_val(r, argv[i]);
    }
    return r;
}

static lil_value_t fnc_set(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t i = 0;
    lil_var_t var = 0;
    int access = 1;
    if (!argc) return 0;
    if (!strcmp(lil_to_string(argv[0]), "global")) {
        i = 1;
        access = 0;
    }
    while (i < argc) {
        if (argc == i + 1) return lil_clone_value(lil_get_var(lil, lil_to_string(argv[i])));
        var = lil_set_var(lil, lil_to_string(argv[i]), argv[i + 1], access);
        i += 2;
    }
    return var ? lil_clone_value(var->v) : 0;
}

static lil_value_t fnc_local(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t i;
    for (i=0; i<argc; i++) {
        const char* varname = lil_to_string(argv[i]);
        if (!lil_find_local_var(lil, lil->env, varname))
            lil_set_var(lil, varname, lil->empty, 2);
    }
    return 0;
}

static lil_value_t fnc_write(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t i;
    lil_value_t msg = lil_alloc_string(0);
    for (i=0; i<argc; i++) {
        if (i) lil_append_char(msg, ' ');
        lil_append_val(msg, argv[i]);
    }
    lil_write(lil, lil_to_string(msg));
    lil_free_value(msg);
    return 0;
}

static lil_value_t fnc_print(lil_t lil, size_t argc, lil_value_t* argv)
{
    fnc_write(lil, argc, argv);
    lil_write(lil, "\n");
    return 0;
}

static lil_value_t fnc_eval(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc == 1) return lil_parse_value(lil, argv[0], 0);
    if (argc > 1) {
        lil_value_t val = alloc_value(0), r;
        size_t i;
        for (i=0; i<argc; i++) {
            if (i) lil_append_char(val, ' ');
            lil_append_val(val, argv[i]);
        }
        r = lil_parse_value(lil, val, 0);
        lil_free_value(val);
        return r;
    }
    return 0;
}

static lil_value_t fnc_topeval(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_env_t thisenv = lil->env;
    lil_env_t thisdownenv = lil->downenv;
    lil_value_t r;
    lil->env = lil->rootenv;
    lil->downenv = thisenv;
    r = fnc_eval(lil, argc, argv);
    lil->downenv = thisdownenv;
    lil->env = thisenv;
    return r;
}

static lil_value_t fnc_upeval(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_env_t thisenv = lil->env;
    lil_env_t thisdownenv = lil->downenv;
    lil_value_t r;
    if (lil->rootenv == thisenv) return fnc_eval(lil, argc, argv);
    lil->env = thisenv->parent;
    lil->downenv = thisenv;
    r = fnc_eval(lil, argc, argv);
    lil->env = thisenv;
    lil->downenv = thisdownenv;
    return r;
}

static lil_value_t fnc_downeval(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t r;
    lil_env_t upenv = lil->env;
    lil_env_t downenv = lil->downenv;
    if (!downenv) return fnc_eval(lil, argc, argv);
    lil->downenv = 0;
    lil->env = downenv;
    r = fnc_eval(lil, argc, argv);
    lil->downenv = downenv;
    lil->env = upenv;
    return r;
}

static lil_value_t fnc_enveval(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t r;
    lil_list_t invars = 0;
    lil_list_t outvars = 0;
    lil_value_t* varvalues = 0;
    int codeindex;
    size_t i;
    if (argc < 1) return 0;
    if (argc == 1) codeindex = 0;
    else if (argc >= 2) {
        invars = lil_subst_to_list(lil, argv[0]);
        varvalues = malloc(sizeof(lil_value_t)*lil_list_size(invars));
        for (i=0; i<lil_list_size(invars); i++)
            varvalues[i] = lil_clone_value(lil_get_var(lil, lil_to_string(lil_list_get(invars, i))));
        if (argc > 2) {
            codeindex = 2;
            outvars = lil_subst_to_list(lil, argv[1]);
        } else {
            codeindex = 1;
        }
    }
    lil_push_env(lil);
    if (invars) {
        for (i=0; i<lil_list_size(invars); i++) {
            lil_set_var(lil, lil_to_string(lil_list_get(invars, i)), varvalues[i], 2);
            lil_free_value(varvalues[i]);
        }
    }
    r = lil_parse_value(lil, argv[codeindex], 0);
    if (invars || outvars) {
        if (outvars) {
            varvalues = realloc(varvalues, sizeof(lil_value_t)*lil_list_size(outvars));
            for (i=0; i<lil_list_size(outvars); i++)
                varvalues[i] = lil_clone_value(lil_get_var(lil, lil_to_string(lil_list_get(outvars, i))));
        } else {
            for (i=0; i<lil_list_size(invars); i++)
                varvalues[i] = lil_clone_value(lil_get_var(lil, lil_to_string(lil_list_get(invars, i))));
        }
    }
    lil_pop_env(lil);
    if (invars) {
        if (outvars) {
            for (i=0; i<lil_list_size(outvars); i++) {
                lil_set_var(lil, lil_to_string(lil_list_get(outvars, i)), varvalues[i], 1);
                lil_free_value(varvalues[i]);
            }
        } else {
            for (i=0; i<lil_list_size(invars); i++) {
                lil_set_var(lil, lil_to_string(lil_list_get(invars, i)), varvalues[i], 1);
                lil_free_value(varvalues[i]);
            }
        }
        lil_free_list(invars);
        if (outvars) lil_free_list(outvars);
        free(varvalues);
    }
    return r;
}

static lil_value_t fnc_jaileval(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t i;
    lil_t sublil;
    lil_value_t r;
    size_t base = 0;
    if (!argc) return 0;
    if (!strcmp(lil_to_string(argv[0]), "clean")) {
        base = 1;
        if (argc == 1) return 0;
    }
    sublil = lil_new();
    if (base != 1) {
        for (i=lil->syscmds; i<lil->cmds; i++) {
            lil_func_t fnc = lil->cmd[i];
            if (!fnc->proc) continue;
            lil_register(sublil, fnc->name, fnc->proc);
        }
    }
    r = lil_parse_value(sublil, argv[base], 1);
    lil_free(sublil);
    return r;
}

static lil_value_t fnc_count(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    char buff[64];
    if (!argc) return alloc_value("0");
    list = lil_subst_to_list(lil, argv[0]);
    sprintf(buff, "%u", (unsigned int)list->c);
    lil_free_list(list);
    return alloc_value(buff);
}

static lil_value_t fnc_index(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    size_t index;
    lil_value_t r;
    if (argc < 2) return 0;
    list = lil_subst_to_list(lil, argv[0]);
    index = (size_t)lil_to_integer(argv[1]);
    if (index >= list->c)
        r = 0;
    else
        r = lil_clone_value(list->v[index]);
    lil_free_list(list);
    return r;
}

static lil_value_t fnc_indexof(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    size_t index;
    lil_value_t r = 0;
    if (argc < 2) return 0;
    list = lil_subst_to_list(lil, argv[0]);
    for (index = 0; index < list->c; index++)
        if (!strcmp(lil_to_string(list->v[index]), lil_to_string(argv[1]))) {
            r = lil_alloc_integer(index);
            break;
        }
    lil_free_list(list);
    return r;
}

static lil_value_t fnc_append(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    lil_value_t r;
    size_t i, base = 1;
    int access = 1;
    const char* varname;
    if (argc < 2) return 0;
    varname = lil_to_string(argv[0]);
    if (!strcmp(varname, "global")) {
        if (argc < 3) return 0;
        varname = lil_to_string(argv[1]);
        base = 2;
        access = 0;
    }
    list = lil_subst_to_list(lil, lil_get_var(lil, varname));
    for (i=base; i<argc; i++)
        lil_list_append(list, lil_clone_value(argv[i]));
    r = lil_list_to_value(list, 1);
    lil_free_list(list);
    lil_set_var(lil, varname, r, access);
    return r;
}

static lil_value_t fnc_slice(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list, slice;
    size_t i;
    lilint_t from, to;
    lil_value_t r;
    if (argc < 1) return 0;
    if (argc < 2) return lil_clone_value(argv[0]);
    from = lil_to_integer(argv[1]);
    if (from < 0) from = 0;
    list = lil_subst_to_list(lil, argv[0]);
    to = argc > 2 ? lil_to_integer(argv[2]) : (lilint_t)list->c;
    if (to > (lilint_t)list->c) to = list->c;
    if (to < from) to = from;
    slice = lil_alloc_list();
    for (i=(size_t)from; i<(size_t)to; i++)
        lil_list_append(slice, lil_clone_value(list->v[i]));
    lil_free_list(list);
    r = lil_list_to_value(slice, 1);
    lil_free_list(slice);
    return r;
}

static lil_value_t fnc_filter(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list, filtered;
    size_t i;
    lil_value_t r;
    const char* varname = "x";
    int base = 0;
    if (argc < 1) return 0;
    if (argc < 2) return lil_clone_value(argv[0]);
    if (argc > 2) {
        base = 1;
        varname = lil_to_string(argv[0]);
    }
    list = lil_subst_to_list(lil, argv[base]);
    filtered = lil_alloc_list();
    for (i=0; i<list->c && !lil->env->breakrun; i++) {
        lil_set_var(lil, varname, list->v[i], 3);
        r = lil_eval_expr(lil, argv[base + 1]);
        if (lil_to_boolean(r))
            lil_list_append(filtered, lil_clone_value(list->v[i]));
        lil_free_value(r);
    }
    lil_free_list(list);
    r = lil_list_to_value(filtered, 1);
    lil_free_list(filtered);
    return r;
}

static lil_value_t fnc_list(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list = lil_alloc_list();
    lil_value_t r;
    size_t i;
    for (i=0; i<argc; i++)
        lil_list_append(list, lil_clone_value(argv[i]));
    r = lil_list_to_value(list, 1);
    lil_free_list(list);
    return r;
}

static lil_value_t fnc_subst(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc < 1) return 0;
    return lil_subst_to_value(lil, argv[0]);
}

static lil_value_t fnc_concat(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    lil_value_t r, tmp;
    size_t i;
    if (argc < 1) return 0;
    r = lil_alloc_string("");
    for (i=0; i<argc; i++) {
        list = lil_subst_to_list(lil, argv[i]);
        tmp = lil_list_to_value(list, 1);
        lil_free_list(list);
        lil_append_val(r, tmp);
        lil_free_value(tmp);
    }
    return r;
}

static lil_value_t fnc_foreach(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list, rlist;
    lil_value_t r;
    size_t i, listidx = 0, codeidx = 1;
    const char* varname = "i";
    if (argc < 2) return 0;
    if (argc >= 3) {
        varname = lil_to_string(argv[0]);
        listidx = 1;
        codeidx = 2;
    }
    rlist = lil_alloc_list();
    list = lil_subst_to_list(lil, argv[listidx]);
    for (i=0; i<list->c; i++) {
        lil_value_t rv;
        lil_set_var(lil, varname, list->v[i], 3);
        rv = lil_parse_value(lil, argv[codeidx], 0);
        if (rv->l) lil_list_append(rlist, rv);
        else lil_free_value(rv);
        if (lil->env->breakrun || lil->error) break;
    }
    r = lil_list_to_value(rlist, 1);
    lil_free_list(list);
    lil_free_list(rlist);
    return r;
}

static lil_value_t fnc_return(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil->env->breakrun = 1;
    lil_free_value(lil->env->retval);
    lil->env->retval = argc < 1 ? 0 : lil_clone_value(argv[0]);
    lil->env->retval_set = 1;
    return argc < 1 ? 0 : lil_clone_value(argv[0]);
}

static lil_value_t fnc_result(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc > 0) {
        lil_free_value(lil->env->retval);
        lil->env->retval = lil_clone_value(argv[0]);
        lil->env->retval_set = 1;
    }
    return lil->env->retval_set ? lil_clone_value(lil->env->retval) : 0;
}

static lil_value_t fnc_expr(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc == 1) return lil_eval_expr(lil, argv[0]);
    if (argc > 1) {
        lil_value_t val = alloc_value(0), r;
        size_t i;
        for (i=0; i<argc; i++) {
            if (i) lil_append_char(val, ' ');
            lil_append_val(val, argv[i]);
        }
        r = lil_eval_expr(lil, val);
        lil_free_value(val);
        return r;
    }
    return 0;
}

static lil_value_t real_inc(lil_t lil, const char* varname, float v)
{
    lil_value_t pv = lil_get_var(lil, varname);
    double dv = lil_to_double(pv) + v;
    if (fmod(dv, 1))
        pv = lil_alloc_double(dv);
    else
        pv = lil_alloc_integer((lilint_t)dv);
    lil_set_var(lil, varname, pv, 1);
    return pv;
}

static lil_value_t fnc_inc(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc < 1) return 0;
    return real_inc(lil, lil_to_string(argv[0]), argc > 1 ? lil_to_double(argv[1]) : 1);
}

static lil_value_t fnc_dec(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc < 1) return 0;
    return real_inc(lil, lil_to_string(argv[0]), -(argc > 1 ? lil_to_double(argv[1]) : 1));
}

static lil_value_t fnc_read(lil_t lil, size_t argc, lil_value_t* argv)
{
    FILE* f;
    size_t size;
    char* buffer;
    lil_value_t r;
    if (argc < 1) return 0;
    if (lil->callback[2]) {
        lil_read_callback_proc_t proc = (lil_read_callback_proc_t) lil->callback[2];
        buffer = proc(lil, lil_to_string(argv[0]));
    } else {
        f = fopen(lil_to_string(argv[0]), "rb");
        if (!f) return 0;
        fseek(f, 0, 2);
        size = ftell(f);
        fseek(f, 0, 0);
        buffer = malloc(size + 1);
        fread(buffer, 1, size, f);
        buffer[size] = 0;
        fclose(f);
    }
    r = lil_alloc_string(buffer);
    free(buffer);
    return r;
}

static lil_value_t fnc_store(lil_t lil, size_t argc, lil_value_t* argv)
{
    FILE* f;
    const char* buffer;
    if (argc < 2) return 0;
    if (lil->callback[3]) {
        lil_store_callback_proc_t proc = (lil_store_callback_proc_t)lil->callback[3];
        proc(lil, lil_to_string(argv[0]), lil_to_string(argv[1]));
    } else {
        f = fopen(lil_to_string(argv[0]), "wb");
        if (!f) return 0;
        buffer = lil_to_string(argv[1]);
        fwrite(buffer, 1, strlen(buffer), f);
        fclose(f);
    }
    return lil_clone_value(argv[1]);
}

static lil_value_t fnc_if(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t val, r = 0;
    int base = 0, not = 0, v;
    if (argc < 1) return 0;
    if (!strcmp(lil_to_string(argv[0]), "not")) base = not = 1;
    if (argc < (size_t)base + 2) return 0;
    val = lil_eval_expr(lil, argv[base]);
    if (!val || lil->error) return 0;
    v = lil_to_boolean(val);
    if (not) v = !v;
    if (v) {
        r = lil_parse_value(lil, argv[base + 1], 0);
    } else if (argc > (size_t)base + 2) {
        r = lil_parse_value(lil, argv[base + 2], 0);
    }
    lil_free_value(val);
    return r;
}

static lil_value_t fnc_while(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t val, r = 0;
    int base = 0, not = 0, v;
    if (argc < 1) return 0;
    if (!strcmp(lil_to_string(argv[0]), "not")) base = not = 1;
    if (argc < (size_t)base + 2) return 0;
    while (!lil->error && !lil->env->breakrun) {
        val = lil_eval_expr(lil, argv[base]);
        if (!val || lil->error) return 0;
        v = lil_to_boolean(val);
        if (not) v = !v;
        if (!v) {
            lil_free_value(val);
            break;
        }
        if (r) lil_free_value(r);
        r = lil_parse_value(lil, argv[base + 1], 0);
        lil_free_value(val);
    }
    return r;
}

static lil_value_t fnc_for(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t val, r = 0;
    if (argc < 4) return 0;
    lil_free_value(lil_parse_value(lil, argv[0], 0));
    while (!lil->error && !lil->env->breakrun) {
        val = lil_eval_expr(lil, argv[1]);
        if (!val || lil->error) return 0;
        if (!lil_to_boolean(val)) {
            lil_free_value(val);
            break;
        }
        if (r) lil_free_value(r);
        r = lil_parse_value(lil, argv[3], 0);
        lil_free_value(val);
        lil_free_value(lil_parse_value(lil, argv[2], 0));
    }
    return r;
}


static lil_value_t fnc_char(lil_t lil, size_t argc, lil_value_t* argv)
{
    char s[2];
    if (!argc) return 0;
    s[0] = (char)lil_to_integer(argv[0]);
    s[1] = 0;
    return lil_alloc_string(s);
}

static lil_value_t fnc_charat(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t index;
    char chstr[2];
    const char* str;
    if (argc < 2) return 0;
    str = lil_to_string(argv[0]);
    index = (size_t)lil_to_integer(argv[1]);
    if (index >= strlen(str)) return 0;
    chstr[0] = str[index];
    chstr[1] = 0;
    return lil_alloc_string(chstr);
}

static lil_value_t fnc_codeat(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t index;
    const char* str;
    if (argc < 2) return 0;
    str = lil_to_string(argv[0]);
    index = (size_t)lil_to_integer(argv[1]);
    if (index >= strlen(str)) return 0;
    return lil_alloc_integer(str[index]);
}

static lil_value_t fnc_substr(lil_t lil, size_t argc, lil_value_t* argv)
{
    const char* str;
    lil_value_t r;
    size_t start, end, i, slen;
    if (argc < 2) return 0;
    str = lil_to_string(argv[0]);
    if (!str[0]) return 0;
    slen = strlen(str);
    start = (size_t)atoll(lil_to_string(argv[1]));
    end = argc > 2 ? (size_t)atoll(lil_to_string(argv[2])) : slen;
    if (end > slen) end = slen;
    if (start >= end) return 0;
    r = lil_alloc_string("");
    for (i=start; i<end; i++)
        lil_append_char(r, str[i]);
    return r;
}

static lil_value_t fnc_strpos(lil_t lil, size_t argc, lil_value_t* argv)
{
    const char* hay;
    const char* str;
    size_t min = 0;
    if (argc < 2) return lil_alloc_integer(-1);
    hay = lil_to_string(argv[0]);
    if (argc > 2) {
        min = (size_t)atoll(lil_to_string(argv[2]));
        if (min >= strlen(hay)) return lil_alloc_integer(-1);
    }
    str = strstr(hay + min, lil_to_string(argv[1]));
    if (!str) return lil_alloc_integer(-1);
    return lil_alloc_integer(str - hay);
}

static lil_value_t fnc_length(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t i, total = 0;
    for (i=0; i<argc; i++) {
        if (i) total++;
        total += strlen(lil_to_string(argv[i]));
    }
    return lil_alloc_integer((lilint_t)total);
}

static lil_value_t real_trim(const char* str, const char* chars, int left, int right)
{
    int base = 0;
    lil_value_t r = 0;
    if (left) {
        while (str[base] && strchr(chars, str[base])) base++;
        if (!right) r = lil_alloc_string(str[base] ? str + base : 0);
    }
    if (right) {
        size_t len;
        char* s;
        s = strclone(str + base);
        len = strlen(s);
        while (len && strchr(chars, s[len - 1])) len--;
        s[len] = 0;
        r = lil_alloc_string(s);
        free(s);
    }
    return r;
}

static lil_value_t fnc_trim(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (!argc) return 0;
    return real_trim(lil_to_string(argv[0]), argc < 2 ? " \f\n\r\t\v" : lil_to_string(argv[1]), 1, 1);
}

static lil_value_t fnc_ltrim(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (!argc) return 0;
    return real_trim(lil_to_string(argv[0]), argc < 2 ? " \f\n\r\t\v" : lil_to_string(argv[1]), 1, 0);
}

static lil_value_t fnc_rtrim(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (!argc) return 0;
    return real_trim(lil_to_string(argv[0]), argc < 2 ? " \f\n\r\t\v" : lil_to_string(argv[1]), 0, 1);
}

static lil_value_t fnc_strcmp(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc < 2) return 0;
    return lil_alloc_integer(strcmp(lil_to_string(argv[0]), lil_to_string(argv[1])));
}

static lil_value_t fnc_streq(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc < 2) return 0;
    return lil_alloc_integer(strcmp(lil_to_string(argv[0]), lil_to_string(argv[1]))?0:1);
}

static lil_value_t fnc_repstr(lil_t lil, size_t argc, lil_value_t* argv)
{
    const char* from;
    const char* to;
    char* src;
    const char* sub;
    size_t idx;
    size_t fromlen;
    size_t tolen;
    size_t srclen;
    lil_value_t r;
    if (argc < 1) return 0;
    if (argc < 3) return lil_clone_value(argv[0]);
    from = lil_to_string(argv[1]);
    to = lil_to_string(argv[2]);
    if (!from[0]) return 0;
    src = strclone(lil_to_string(argv[0]));
    srclen = strlen(src);
    fromlen = strlen(from);
    tolen = strlen(to);
    while ((sub = strstr(src, from))) {
        char* newsrc = malloc(srclen - fromlen + tolen + 1);
        idx = sub - src;
        if (idx) memcpy(newsrc, src, idx);
        memcpy(newsrc + idx, to, tolen);
        memcpy(newsrc + idx + tolen, src + idx + fromlen, srclen - idx - fromlen);
        srclen = srclen - fromlen + tolen;
        free(src);
        src = newsrc;
        src[srclen] = 0;
    }
    r = lil_alloc_string(src);
    free(src);
    return r;
}

static lil_value_t fnc_split(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    const char* sep = " ";
    size_t i;
    lil_value_t val;
    const char* str;
    if (argc == 0) return 0;
    if (argc > 1) {
        sep = lil_to_string(argv[1]);
        if (!sep || !sep[0]) return lil_clone_value(argv[0]);
    }
    val = lil_alloc_string("");
    str = lil_to_string(argv[0]);
    list = lil_alloc_list();
    for (i=0; str[i]; i++) {
        if (strchr(sep, str[i])) {
            lil_list_append(list, val);
            val = lil_alloc_string("");
        } else {
            lil_append_char(val, str[i]);
        }
    }
    lil_list_append(list, val);
    val = lil_list_to_value(list, 1);
    lil_free_list(list);
    return val;
}

static lil_value_t fnc_try(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_value_t r;
    if (argc < 1) return 0;
    if (lil->error) return 0;
    r = lil_parse_value(lil, argv[0], 0);
    if (lil->error) {
        lil->error = 0;
        lil_free_value(r);
        if (argc > 1) r = lil_parse_value(lil, argv[1], 0);
        else r = 0;
    }
    return r;
}

static lil_value_t fnc_error(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_set_error(lil, argc > 0 ? lil_to_string(argv[0]) : 0);
    return 0;
}

static lil_value_t fnc_exit(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (lil->callback[0]) {
        lil_exit_callback_proc_t proc = (lil_exit_callback_proc_t)lil->callback[0];
        proc(lil, argc > 0 ? argv[0] : 0);
    }
    return 0;
}

static lil_value_t fnc_source(lil_t lil, size_t argc, lil_value_t* argv)
{
    FILE* f;
    size_t size;
    char* buffer;
    lil_value_t r;
    if (argc < 1) return 0;
    if (lil->callback[4]) {
        lil_source_callback_proc_t proc = (lil_source_callback_proc_t)lil->callback[4];
        buffer = proc(lil, lil_to_string(argv[0]));
    } else if (lil->callback[2]) {
        lil_read_callback_proc_t proc = (lil_read_callback_proc_t)lil->callback[2];
        buffer = proc(lil, lil_to_string(argv[0]));
    } else {
        f = fopen(lil_to_string(argv[0]), "rb");
        if (!f) return 0;
        fseek(f, 0, 2);
        size = ftell(f);
        fseek(f, 0, 0);
        buffer = malloc(size + 1);
        fread(buffer, 1, size, f);
        buffer[size] = 0;
        fclose(f);
    }
    r = lil_parse(lil, buffer, 0, 0);
    free(buffer);
    return r;
}

static lil_value_t fnc_lmap(lil_t lil, size_t argc, lil_value_t* argv)
{
    lil_list_t list;
    size_t i;
    if (argc < 2) return 0;
    list = lil_subst_to_list(lil, argv[0]);
    for (i=1; i<argc; i++)
        lil_set_var(lil, lil_to_string(argv[i]), lil_list_get(list, i - 1), 1);
    lil_free_list(list);
    return 0;
}

static lil_value_t fnc_rand(lil_t lil, size_t argc, lil_value_t* argv)
{
    return lil_alloc_double(rand()/(double)32767);
}

static lil_value_t fnc_catcher(lil_t lil, size_t argc, lil_value_t* argv)
{
    if (argc == 0) {
        return lil_alloc_string(lil->catcher);
    } else {
        const char* catcher = lil_to_string(argv[0]);
        free(lil->catcher);
        lil->catcher = catcher[0] ? strclone(catcher) : 0;
    }
    return 0;
}

static lil_value_t fnc_watch(lil_t lil, size_t argc, lil_value_t* argv)
{
    size_t i;
    const char* wcode;
    if (argc < 2) return 0;
    wcode = lil_to_string(argv[argc - 1]);
    for (i=0; i + 1 < argc; i++) {
        const char* vname = lil_to_string(argv[i]);
        lil_var_t v;
        if (!vname[0]) continue;
        v = lil_find_var(lil, lil->env, lil_to_string(argv[i]));
        if (!v) v = lil_set_var(lil, vname, 0, 2);
        free(v->w);
        v->w = wcode[0] ? strclone(wcode) : 0;
    }
    return 0;
}

static void register_stdcmds(lil_t lil)
{
    lil_register(lil, "reflect", fnc_reflect);
    lil_register(lil, "func", fnc_func);
    lil_register(lil, "rename", fnc_rename);
    lil_register(lil, "unusedname", fnc_unusedname);
    lil_register(lil, "quote", fnc_quote);
    lil_register(lil, "set", fnc_set);
    lil_register(lil, "local", fnc_local);
    lil_register(lil, "write", fnc_write);
    lil_register(lil, "print", fnc_print);
    lil_register(lil, "eval", fnc_eval);
    lil_register(lil, "topeval", fnc_topeval);
    lil_register(lil, "upeval", fnc_upeval);
    lil_register(lil, "downeval", fnc_downeval);
    lil_register(lil, "enveval", fnc_enveval);
    lil_register(lil, "jaileval", fnc_jaileval);
    lil_register(lil, "count", fnc_count);
    lil_register(lil, "index", fnc_index);
    lil_register(lil, "indexof", fnc_indexof);
    lil_register(lil, "filter", fnc_filter);
    lil_register(lil, "list", fnc_list);
    lil_register(lil, "append", fnc_append);
    lil_register(lil, "slice", fnc_slice);
    lil_register(lil, "subst", fnc_subst);
    lil_register(lil, "concat", fnc_concat);
    lil_register(lil, "foreach", fnc_foreach);
    lil_register(lil, "return", fnc_return);
    lil_register(lil, "result", fnc_result);
    lil_register(lil, "expr", fnc_expr);
    lil_register(lil, "inc", fnc_inc);
    lil_register(lil, "dec", fnc_dec);
    lil_register(lil, "read", fnc_read);
    lil_register(lil, "store", fnc_store);
    lil_register(lil, "if", fnc_if);
    lil_register(lil, "while", fnc_while);
    lil_register(lil, "for", fnc_for);
    lil_register(lil, "char", fnc_char);
    lil_register(lil, "charat", fnc_charat);
    lil_register(lil, "codeat", fnc_codeat);
    lil_register(lil, "substr", fnc_substr);
    lil_register(lil, "strpos", fnc_strpos);
    lil_register(lil, "length", fnc_length);
    lil_register(lil, "trim", fnc_trim);
    lil_register(lil, "ltrim", fnc_ltrim);
    lil_register(lil, "rtrim", fnc_rtrim);
    lil_register(lil, "strcmp", fnc_strcmp);
    lil_register(lil, "streq", fnc_streq);
    lil_register(lil, "repstr", fnc_repstr);
    lil_register(lil, "split", fnc_split);
    lil_register(lil, "try", fnc_try);
    lil_register(lil, "error", fnc_error);
    lil_register(lil, "exit", fnc_exit);
    lil_register(lil, "source", fnc_source);
    lil_register(lil, "lmap", fnc_lmap);
    lil_register(lil, "rand", fnc_rand);
    lil_register(lil, "catcher", fnc_catcher);
    lil_register(lil, "watch", fnc_watch);
    lil->syscmds = lil->cmds;
}
