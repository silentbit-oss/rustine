#ifndef LIBTREE_H
#define LIBTREE_H

#define ET_EXEC 2
#define ET_DYN 3

#define PT_NULL 0
#define PT_LOAD 1
#define PT_DYNAMIC 2

#define DT_NULL 0
#define DT_NEEDED 1
#define DT_STRTAB 5
#define DT_SONAME 14
#define DT_RPATH 15
#define DT_RUNPATH 29

#define BITS32 1
#define BITS64 2

#define ERR_INVALID_MAGIC 11
#define ERR_INVALID_CLASS 12
#define ERR_INVALID_DATA 13
#define ERR_INVALID_HEADER 14
#define ERR_INVALID_BITS 15
#define ERR_INVALID_ENDIANNESS 16
#define ERR_NO_EXEC_OR_DYN 17
#define ERR_INVALID_PHOFF 18
#define ERR_INVALID_PROG_HEADER 19
#define ERR_CANT_STAT 20
#define ERR_INVALID_DYNAMIC_SECTION 21
#define ERR_INVALID_DYNAMIC_ARRAY_ENTRY 22
#define ERR_NO_STRTAB 23
#define ERR_INVALID_SONAME 24
#define ERR_INVALID_RPATH 25
#define ERR_INVALID_RUNPATH 26
#define ERR_INVALID_NEEDED 27
#define ERR_DEPENDENCY_NOT_FOUND 28
#define ERR_NO_PT_LOAD 29
#define ERR_VADDRS_NOT_ORDERED 30
#define ERR_COULD_NOT_OPEN_FILE 31
#define ERR_INCOMPATIBLE_ISA 32

// don't judge me.
#define LIGHT_HORIZONTAL "\xe2\x94\x80"
#define LIGHT_QUADRUPLE_DASH_VERTICAL "\xe2\x94\x8a"
#define LIGHT_UP_AND_RIGHT "\xe2\x94\x94"
#define LIGHT_VERTICAL "\xe2\x94\x82"
#define LIGHT_VERTICAL_AND_RIGHT "\xe2\x94\x9c"

#define JUST_INDENT "    "
#define LIGHT_VERTICAL_WITH_INDENT LIGHT_VERTICAL "   "

#define SMALL_VEC_SIZE 16
#define MAX_RECURSION_DEPTH 32
#define MAX_PATH_LENGTH 4096


#define REGULAR_RED "\033[0;31m"
#define BOLD_RED "\033[1;31m"
#define CLEAR "\033[0m"
#define BOLD_YELLOW "\033[33m"
#define BOLD_CYAN "\033[1;36m"
#define REGULAR_CYAN "\033[0;36m"
#define REGULAR_MAGENTA "\033[0;35m"
#define REGULAR_BLUE "\033[0;34m"
#define BRIGHT_BLACK "\033[0;90m"
#define REGULAR "\033[0m"


#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>  /* for dev_t, ino_t */
#include <sys/stat.h>   /* for struct stat */

#ifdef __cplusplus
extern "C" {
#endif

/* constants */
#define SMALL_VEC_SIZE 16
#define MAX_RECURSION_DEPTH 32

/* Utility functions */
void utoa(char *str, size_t v);
int host_is_little_endian(void);
int is_ascending_order(uint64_t *v, size_t n);

/* small vector for uint64_t */
struct small_vec_u64_t {
uint64_t buf[SMALL_VEC_SIZE];
uint64_t *p;
size_t n;
size_t capacity;
};
void small_vec_u64_init(struct small_vec_u64_t *v);
void small_vec_u64_append(struct small_vec_u64_t *v, uint64_t val);
void small_vec_u64_free(struct small_vec_u64_t *v);

/* string table */
struct string_table_t {
char *arr;
size_t n;
size_t capacity;
};
void string_table_store(struct string_table_t *t, const char *str);
void string_table_maybe_grow(struct string_table_t *t, size_t n);

/* exclude list check */
int is_in_exclude_list(const char *soname);

/* visited files tracking */
struct visited_file_t {
dev_t st_dev;
ino_t st_ino;
};
struct visited_file_array_t {
struct visited_file_t *arr;
size_t n;
size_t capacity;
};
int visited_files_contains(struct visited_file_array_t *files, struct stat *needle);
void visited_files_append(struct visited_file_array_t *files, struct stat *new);

/* enums and structs for recursion */
enum how_t {
INPUT,
DIRECT,
RPATH,
LD_LIBRARY_PATH,
RUNPATH,
LD_SO_CONF,
DEFAULT
};
struct found_t {
enum how_t how;
size_t depth;
};
struct compat_t {
char any;
uint8_t class;
uint16_t machine;
};

/* main state */
struct libtree_state_t {
int verbosity;
int path;
int color;
char *ld_conf_file;
unsigned long max_depth;
struct string_table_t string_table;
struct visited_file_array_t visited;
char *PLATFORM;
char *LIB;
char *OSNAME;
char *OSREL;
size_t rpath_offsets[MAX_RECURSION_DEPTH];
size_t ld_library_path_offset;
size_t default_paths_offset;
size_t ld_so_conf_offset;
char found_all_needed[MAX_RECURSION_DEPTH];
};

/* state management */
void libtree_state_init(struct libtree_state_t *s);
void libtree_state_free(struct libtree_state_t *s);

/* config parsing */
int parse_ld_config_file(struct string_table_t *t, const char *path);
void parse_ld_library_path(struct libtree_state_t *s);
void set_default_paths(struct libtree_state_t *s);

/* recursion and printing */
void tree_preamble(const struct libtree_state_t *s, size_t depth);
int recurse(char *current_file, size_t depth, struct libtree_state_t *s,
struct compat_t compat, struct found_t reason);
int interpolate_variables(struct libtree_state_t *s, size_t src, const char *ORIGIN);

#ifdef __cplusplus
}
#endif

#endif /* LIBTREE_H */

