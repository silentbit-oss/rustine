#include <alloca.h>
#include <arg-nonnull.h>
#include <assert.h>
#include <attribute.h>
#include <basename-lgpl.h>
#include <closein.h>
#include <closeout.h>
#include <config.h>
#include <configmake.h>
#include <dev-ino.h>
#include <dirent.h>
#include <dirname.h>
#include <errno.h>
#include <error.h>
#include <exitfail.h>
#include <fcntl.h>
#include <filename.h>
#include <getopt.h>
#include <gettext.h>
#include <idx.h>
#include <intprops-internal.h>
#include <intprops.h>
#include <inttostr.h>
#include <inttypes.h>
#include <libintl.h>
#include <limits.h>
#include <locale.h>
#include <minmax.h>
#include <openat.h>
#include <param.h>
#include <pathmax.h>
#include <progname.h>
#include <propername.h>
#include <quote.h>
#include <quotearg.h>
#include <root-dev-ino.h>
#include <same-inode.h>
#include <stat-macros.h>
#include <stat.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdckdint.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysmacros.h>
#include <system.h>
#include <time.h>
#include <timespec.h>
#include <types.h>
#include <unistd.h>
#include <unlocked-io.h>
#include <verify.h>
#include <version-etc.h>
#include <version.h>
#include <xalloc.h>
#include <xgetcwd.h>

#pragma GCC diagnostic ignored "-Wtype-limits"
extern const char *Version;
enum 
{
  EXIT_TIMEDOUT = 124,
  EXIT_CANCELED = 125,
  EXIT_CANNOT_INVOKE = 126,
  EXIT_ENOENT = 127
};
extern volatile int exit_failure;
inline static void initialize_exit_failure(int status)
{
  if (status != 1)
  {
    exit_failure = status;
  }
}

enum 
{
  O_PATHSEARCH = O_SEARCH
};
enum 
{
  NOT_AN_INODE_NUMBER = 0
};
enum 
{
  TIMESPEC_HZ = 1000000000
};
enum 
{
  LOG10_TIMESPEC_HZ = 9
};
enum 
{
  TIMESPEC_RESOLUTION = TIMESPEC_HZ
};
enum 
{
  LOG10_TIMESPEC_RESOLUTION = LOG10_TIMESPEC_HZ
};
inline struct timespec make_timespec(time_t s, long int ns)
{
  return (struct timespec){.tv_sec = s, .tv_nsec = ns};
}

inline int timespec_cmp(struct timespec a, struct timespec b)
{
  return (2 * ((a.tv_sec > b.tv_sec) - (a.tv_sec < b.tv_sec))) + ((a.tv_nsec > b.tv_nsec) - (a.tv_nsec < b.tv_nsec));
}

inline int timespec_sign(struct timespec a)
{
  return ((a.tv_sec > 0) - (a.tv_sec < 0)) + ((!a.tv_sec) & (!(!a.tv_nsec)));
}

struct timespec timespec_add(struct timespec, struct timespec);
struct timespec timespec_sub(struct timespec, struct timespec);
struct timespec dtotimespec(double);
inline double timespectod(struct timespec a)
{
  return a.tv_sec + (a.tv_nsec / 1e9);
}

long int gettime_res(void);
struct timespec current_timespec(void);
void gettime(struct timespec *);
int settime(const struct timespec *);
inline static unsigned char to_uchar(char ch)
{
  return ch;
}

static const char *pgettext_aux(const char *domain, const char *msg_ctxt_id, const char *msgid, int category)
{
  const char *translation = dcgettext(domain, msg_ctxt_id, category);
  if (translation == msg_ctxt_id)
  {
    return msgid;
  }
  else
    return translation;
}

static const char *npgettext_aux(const char *domain, const char *msg_ctxt_id, const char *msgid, const char *msgid_plural, unsigned long int n, int category)
{
  const char *translation = dcngettext(domain, msg_ctxt_id, msgid_plural, n, category);
  if ((translation == msg_ctxt_id) || (translation == msgid_plural))
  {
    return (n == 1) ? (msgid) : (msgid_plural);
  }
  else
    return translation;
}

static const char *dcpgettext_expr(const char *domain, const char *msgctxt, const char *msgid, int category)
{
  size_t msgctxt_len = strlen(msgctxt) + 1;
  size_t msgid_len = strlen(msgid) + 1;
  const char *translation;
  unsigned int translation_idx = 0;
  char buf[1024];
  char *msg_ctxt_id = ((msgctxt_len + msgid_len) <= (sizeof(buf))) ? (buf) : ((char *) malloc(msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)
  {
    int found_translation;
    memcpy(msg_ctxt_id, msgctxt, msgctxt_len - 1);
    msg_ctxt_id[msgctxt_len - 1] = '\004';
    memcpy(msg_ctxt_id + msgctxt_len, msgid, msgid_len);
    translation_idx = dcgettext(domain, msg_ctxt_id, category);
    found_translation = (&translation[translation_idx]) != msg_ctxt_id;
    if (msg_ctxt_id != buf)
    {
      free(msg_ctxt_id);
    }
    if (found_translation)
    {
      return translation;
    }
  }
  return msgid;
}

static const char *dcnpgettext_expr(const char *domain, const char *msgctxt, const char *msgid, const char *msgid_plural, unsigned long int n, int category)
{
  size_t msgctxt_len = strlen(msgctxt) + 1;
  size_t msgid_len = strlen(msgid) + 1;
  const char *translation;
  unsigned int translation_idx = 0;
  char buf[1024];
  char *msg_ctxt_id = ((msgctxt_len + msgid_len) <= (sizeof(buf))) ? (buf) : ((char *) malloc(msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)
  {
    int found_translation;
    memcpy(msg_ctxt_id, msgctxt, msgctxt_len - 1);
    msg_ctxt_id[msgctxt_len - 1] = '\004';
    memcpy(msg_ctxt_id + msgctxt_len, msgid, msgid_len);
    translation_idx = dcngettext(domain, msg_ctxt_id, msgid_plural, n, category);
    found_translation = !(((&translation[translation_idx]) == msg_ctxt_id) || ((&translation[translation_idx]) == msgid_plural));
    if (msg_ctxt_id != buf)
    {
      free(msg_ctxt_id);
    }
    if (found_translation)
    {
      return translation;
    }
  }
  return (n == 1) ? (msgid) : (msgid_plural);
}

inline static unsigned long int select_plural(uintmax_t n)
{
  enum 
  {
    PLURAL_REDUCER = 1000000
  };
  return (n <= 18446744073709551615UL) ? (n) : ((n % PLURAL_REDUCER) + PLURAL_REDUCER);
}

typedef ptrdiff_t idx_t;
_Noreturn void xalloc_die(void);
void *xmalloc(size_t s);
void *ximalloc(idx_t s);
void *xinmalloc(idx_t n, idx_t s);
void *xzalloc(size_t s);
void *xizalloc(idx_t s);
void *xcalloc(size_t n, size_t s);
void *xicalloc(idx_t n, idx_t s);
void *xrealloc(void *p, size_t s);
void *xirealloc(void *p, idx_t s);
void *xreallocarray(void *p, size_t n, size_t s);
void *xireallocarray(void *p, idx_t n, idx_t s);
void *x2realloc(void *p, size_t *ps);
void *x2nrealloc(void *p, size_t *pn, size_t s);
void *xpalloc(void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s);
void *xmemdup(const void *p, size_t s);
void *ximemdup(const void *p, idx_t s);
char *ximemdup0(const void *p, idx_t s);
char *xstrdup(const char *str);
void *xnmalloc(size_t n, size_t s);
inline void *xnrealloc(void *p, size_t n, size_t s);
inline void *xnrealloc(void *p, size_t n, size_t s)
{
  return xreallocarray(p, n, s);
}

char *xcharalloc(size_t n);
inline bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}

extern char *last_component(const char *filename);
extern size_t base_len(const char *filename);
char *base_name(const char *file);
char *dir_name(const char *file);
char *mdir_name(const char *file);
size_t dir_len(const char *file);
bool strip_trailing_slashes(char *file);
_Noreturn void openat_restore_fail(int);
_Noreturn void openat_save_fail(int);
inline int chownat(int fd, const char *file, uid_t owner, gid_t group)
{
  return fchownat(fd, file, owner, group, 0);
}

inline int lchownat(int fd, const char *file, uid_t owner, gid_t group)
{
  return fchownat(fd, file, owner, group, AT_SYMLINK_NOFOLLOW);
}

inline int chmodat(int fd, const char *file, mode_t mode)
{
  return fchmodat(fd, file, mode, 0);
}

inline int lchmodat(int fd, const char *file, mode_t mode)
{
  return fchmodat(fd, file, mode, AT_SYMLINK_NOFOLLOW);
}

inline static bool dot_or_dotdot(const char *file_name)
{
  if (file_name[0] == '.')
  {
    char sep = file_name[(file_name[1] == '.') + 1];
    return (!sep) || (sep == '/');
  }
  else
    return 0;
}

inline static const struct dirent *readdir_ignoring_dot_and_dotdot(DIR *dirp)
{
  while (1)
  {
    const struct dirent *dp = readdir(dirp);
    if ((dp == ((void *) 0)) || (!dot_or_dotdot(dp->d_name)))
    {
      return dp;
    }
  }

}

enum 
{
  DS_UNKNOWN = -2,
  DS_EMPTY = -1,
  DS_NONEMPTY = 0
};
inline static int directory_status(int fd_cwd, const char *dir)
{
  DIR *dirp;
  unsigned int dirp_idx = 0;
  bool no_direntries;
  int saved_errno;
  int fd = openat(fd_cwd, dir, (((O_RDONLY | O_DIRECTORY) | O_NOCTTY) | O_NOFOLLOW) | O_NONBLOCK);
  if (fd < 0)
  {
    return errno;
  }
  dirp_idx = fdopendir(fd);
  if ((&dirp[dirp_idx]) == ((void *) 0))
  {
    saved_errno = errno;
    close(fd);
    return saved_errno;
  }
  errno = 0;
  no_direntries = !readdir_ignoring_dot_and_dotdot(dirp);
  saved_errno = errno;
  closedir(dirp);
  return (no_direntries && (saved_errno == 0)) ? (DS_EMPTY) : (saved_errno);
}

enum 
{
  GETOPT_HELP_CHAR = (-128) - 2,
  GETOPT_VERSION_CHAR = (-128) - 3
};
void close_stdin_set_file_name(const char *file);
void close_stdin(void);
void close_stdout_set_file_name(const char *file);
void close_stdout_set_ignore_EPIPE(bool ignore);
void close_stdout(void);
extern const char version_etc_copyright[];
extern void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors);
extern void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors);
extern void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors);
extern void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...);
extern void unused__emit_bug_reporting_address(void);
extern const char *proper_name(const char *name);
extern const char *proper_name_utf8(const char *name_ascii, const char *name_utf8);
extern const char *proper_name_lite(const char *name_ascii, const char *name_utf8);
extern const char *program_name;
extern void set_program_name(const char *argv0);
static size_t gcd(size_t u, size_t v)
{
  do
  {
    size_t t = u % v;
    u = v;
    v = t;
  }
  while (v);
  return u;
}

inline static size_t lcm(size_t u, size_t v)
{
  return u * (v / gcd(u, v));
}

inline static void *ptr_align(const void *ptr, size_t alignment)
{
  const char *p0 = ptr;
  const char *p1 = (p0 + alignment) - 1;
  return (void *) (p1 - (((size_t) p1) % alignment));
}

inline static bool is_nul(const void *buf, size_t length)
{
  const unsigned char *p = buf;
  unsigned int p_idx = 0;
  unsigned char word;
  if (!length)
  {
    return 1;
  }
  while (__builtin_expect(length & ((sizeof(word)) - 1), 0))
  {
    if (p[p_idx])
    {
      return 0;
    }
    p_idx += 1;
    length -= 1;
    if (!length)
    {
      return 1;
    }
  }

  for (;;)
  {
    memcpy(&word, p, sizeof(word));
    if (word)
    {
      return 0;
    }
    p_idx += sizeof(word);
    length -= sizeof(word);
    if (!length)
    {
      return 1;
    }
    if (__builtin_expect(length & 15, 0) == 0)
    {
      break;
    }
  }

  return memcmp(buf, p, length) == 0;
}

inline static void emit_stdin_note(void)
{
  fputs_unlocked(gettext("\nWith no FILE, or when FILE is -, read standard input.\n"), stdout);
}

inline static void emit_mandatory_arg_note(void)
{
  fputs_unlocked(gettext("\nMandatory arguments to long options are mandatory for short options too.\n"), stdout);
}

inline static void emit_size_note(void)
{
  fputs_unlocked(gettext("\nThe SIZE argument is an integer and optional unit (example: 10K is 10*1024).\nUnits are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\nBinary prefixes can be used, too: KiB=K, MiB=M, and so on.\n"), stdout);
}

inline static void emit_blocksize_note(const char *program)
{
  printf(gettext("\nDisplay values are in units of the first available SIZE from --block-size,\nand the %s_BLOCK_SIZE, BLOCK_SIZE and BLOCKSIZE environment variables.\nOtherwise, units default to 1024 bytes (or 512 if POSIXLY_CORRECT is set).\n"), program);
}

inline static void emit_update_parameters_note(void)
{
  fputs_unlocked(gettext("\nUPDATE controls which existing files in the destination are replaced.\n'all' is the default operation when an --update option is not specified,\nand results in all existing files in the destination being replaced.\n'none' is like the --no-clobber option, in that no files in the\ndestination are replaced, and skipped files do not induce a failure.\n'none-fail' also ensures no files are replaced in the destination,\nbut any skipped files are diagnosed and induce a failure.\n'older' is the default operation when --update is specified, and results\nin files being replaced if they're older than the corresponding source file.\n"), stdout);
}

inline static void emit_backup_suffix_note(void)
{
  fputs_unlocked(gettext("\nThe backup suffix is '~', unless set with --suffix or SIMPLE_BACKUP_SUFFIX.\nThe version control method may be selected via the --backup option or through\nthe VERSION_CONTROL environment variable.  Here are the values:\n\n"), stdout);
  fputs_unlocked(gettext("  none, off       never make backups (even if --backup is given)\n  numbered, t     make numbered backups\n  existing, nil   numbered if numbered backups exist, simple otherwise\n  simple, never   always make simple backups\n"), stdout);
}

inline static void emit_symlink_recurse_options(const char *default_opt)
{
  printf(gettext("\nThe following options modify how a hierarchy is traversed when the -R\noption is also specified.  If more than one is specified, only the final\none takes effect. '%s' is the default.\n\n  -H                     if a command line argument is a symbolic link\n                         to a directory, traverse it\n  -L                     traverse every symbolic link to a directory\n                         encountered\n  -P                     do not traverse any symbolic links\n\n"), default_opt);
}

inline static void emit_exec_status(const char *program)
{
  printf(gettext("\nExit status:\n  125  if the %s command itself fails\n  126  if COMMAND is found but cannot be invoked\n  127  if COMMAND cannot be found\n  -    the exit status of COMMAND otherwise\n"), program);
}

inline static void emit_ancillary_info(const char *program)
{
  const struct infomap
  {
    const char *program;
    const char *node;
  } infomap[] = {{"[", "test invocation"}, {"coreutils", "Multi-call invocation"}, {"sha224sum", "sha2 utilities"}, {"sha256sum", "sha2 utilities"}, {"sha384sum", "sha2 utilities"}, {"sha512sum", "sha2 utilities"}, {(void *) 0, (void *) 0}};
  unsigned int node_idx = 0;
  const char *node = program;
  unsigned int node_idx = 0;
  const struct infomap *map_prog = infomap;
  unsigned int map_prog_idx = 0;
  while (map_prog->program && (!(strcmp(program, map_prog->program) == 0)))
  {
    map_prog_idx += 1;
  }

  if (map_prog->node)
  {
    node_idx = map_prog->node_idx;
  }
  printf(gettext("\n%s online help: <%s>\n"), "GNU coreutils", "https://www.gnu.org/software/coreutils/");
  const char *lc_messages = setlocale(LC_MESSAGES, (void *) 0);
  if (lc_messages && strncmp(lc_messages, "en_", (sizeof("en_")) - 1))
  {
    fputs_unlocked(gettext("Report any translation bugs to <https://translationproject.org/team/>\n"), stdout);
  }
  const char *url_program = (strcmp(program, "[") == 0) ? ("test") : (program);
  printf(gettext("Full documentation <%s%s>\n"), "https://www.gnu.org/software/coreutils/", url_program);
  printf(gettext("or available locally via: info '(coreutils) %s%s'\n"), node, ((&node[node_idx]) == program) ? (" invocation") : (""));
}

char *imaxtostr(intmax_t, char *);
char *inttostr(int, char *);
char *offtostr(off_t, char *);
char *uinttostr(unsigned int, char *);
char *umaxtostr(uintmax_t, char *);
inline static char *timetostr(time_t t, char *buf)
{
  return (!(((time_t) 0) < ((time_t) (-1)))) ? (imaxtostr(t, buf)) : (umaxtostr(t, buf));
}

inline static char *bad_cast(const char *s)
{
  return (char *) s;
}

inline static bool usable_st_size(const struct stat *sb)
{
  return ((S_ISREG(sb->st_mode) || S_ISLNK(sb->st_mode)) || S_TYPEISSHM(sb)) || S_TYPEISTMO(sb);
}

_Noreturn void usage(int status);
inline static void write_error(void)
{
  int saved_errno = errno;
  fflush_unlocked(stdout);
  fpurge(stdout);
  clearerr_unlocked(stdout);
  error(1, saved_errno, gettext("write error"));
}

inline static char *stzncpy(char *dest, const char *src, size_t len)
{
  unsigned int src_idx = 0;
  unsigned int dest_idx = 0;
  size_t i;
  for (i = 0; (i < len) && src[src_idx]; i += 1)
  {
    dest[dest_idx] = src[src_idx];
    src_idx += 1;
    dest_idx += 1;
  }

  dest[dest_idx] = 0;
  return dest;
}

inline static bool is_ENOTSUP(int err)
{
  return (err == EOPNOTSUPP) || ((ENOTSUP != EOPNOTSUPP) && (err == ENOTSUP));
}

enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
};
enum quoting_flags
{
  QA_ELIDE_NULL_BYTES = 0x01,
  QA_ELIDE_OUTER_QUOTES = 0x02,
  QA_SPLIT_TRIGRAPHS = 0x04
};
extern const char * const quoting_style_args[];
extern const enum quoting_style quoting_style_vals[];
struct quoting_options;
struct quoting_options *clone_quoting_options(struct quoting_options *o);
enum quoting_style get_quoting_style(const struct quoting_options *o);
void set_quoting_style(struct quoting_options *o, enum quoting_style s);
int set_char_quoting(struct quoting_options *o, char c, int i);
int set_quoting_flags(struct quoting_options *o, int i);
void set_custom_quoting(struct quoting_options *o, const char *left_quote, const char *right_quote);
size_t quotearg_buffer(char *buffer, size_t buffersize, const char *arg, size_t argsize, const struct quoting_options *o);
char *quotearg_alloc(const char *arg, size_t argsize, const struct quoting_options *o);
char *quotearg_alloc_mem(const char *arg, size_t argsize, size_t *size, const struct quoting_options *o);
char *quotearg_n(int n, const char *arg);
char *quotearg(const char *arg);
char *quotearg_n_mem(int n, const char *arg, size_t argsize);
char *quotearg_mem(const char *arg, size_t argsize);
char *quotearg_n_style(int n, enum quoting_style s, const char *arg);
char *quotearg_n_style_mem(int n, enum quoting_style s, const char *arg, size_t argsize);
char *quotearg_style(enum quoting_style s, const char *arg);
char *quotearg_style_mem(enum quoting_style s, const char *arg, size_t argsize);
char *quotearg_char(const char *arg, char ch);
char *quotearg_char_mem(const char *arg, size_t argsize, char ch);
char *quotearg_colon(const char *arg);
char *quotearg_colon_mem(const char *arg, size_t argsize);
char *quotearg_n_style_colon(int n, enum quoting_style s, const char *arg);
char *quotearg_n_custom(int n, const char *left_quote, const char *right_quote, const char *arg);
char *quotearg_n_custom_mem(int n, const char *left_quote, const char *right_quote, const char *arg, size_t argsize);
char *quotearg_custom(const char *left_quote, const char *right_quote, const char *arg);
char *quotearg_custom_mem(const char *left_quote, const char *right_quote, const char *arg, size_t argsize);
void quotearg_free(void);
extern struct quoting_options quote_quoting_options;
const char *quote_n_mem(int n, const char *arg, size_t argsize);
const char *quote_mem(const char *arg, size_t argsize);
const char *quote_n(int n, const char *arg);
const char *quote(const char *arg);
struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
};
struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i);
extern char *xgetcwd(void);
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
};
static const struct option longopts[] = {{"logical", no_argument, (void *) 0, 'L'}, {"physical", no_argument, (void *) 0, 'P'}, {"help", no_argument, (void *) 0, GETOPT_HELP_CHAR}, {"version", no_argument, (void *) 0, GETOPT_VERSION_CHAR}, {(void *) 0, 0, (void *) 0, 0}};
void usage(int status)
{
  if (status != 0)
  {
    do
    {
      fprintf(stderr, gettext("Try '%s --help' for more information.\n"), program_name);
    }
    while (0);
  }
  else
  {
    printf(gettext("Usage: %s [OPTION]...\n"), program_name);
    fputs_unlocked(gettext("Print the full filename of the current working directory.\n\n"), stdout);
    fputs_unlocked(gettext("  -L, --logical   use PWD from environment, even if it contains symlinks\n"), stdout);
    fputs_unlocked(gettext("  -P, --physical  resolve all symlinks\n"), stdout);
    fputs_unlocked(gettext("      --help        display this help and exit\n"), stdout);
    fputs_unlocked(gettext("      --version     output version information and exit\n"), stdout);
    fputs_unlocked(gettext("\nIf no option is specified, -P is assumed.\n"), stdout);
    printf(gettext("\nYour shell may have its own version of %s, which usually supersedes\nthe version described here.  Please refer to your shell's documentation\nfor details about the options it supports.\n"), "pwd");
    emit_ancillary_info("pwd");
  }
  exit(status);
}

static void file_name_free(struct file_name *p)
{
  free(p->buf);
  free(p);
}

static struct file_name *file_name_init(void)
{
  struct file_name *p = xmalloc(sizeof(*p));
  p->n_alloc = ((2 * 8192) < (32 * 1024)) ? (2 * 8192) : (32 * 1024);
  p->buf = xmalloc(p->n_alloc);
  p->start = p->buf + (p->n_alloc - 1);
  p->start[0] = '\0';
  return p;
}

static void file_name_prepend(struct file_name *p, const char *s, size_t s_len)
{
  size_t n_free = p->start - p->buf;
  if (n_free < (1 + s_len))
  {
    size_t half = (p->n_alloc + 1) + s_len;
    char *q = xnmalloc(2, half);
    size_t n_used = p->n_alloc - n_free;
    p->start = (q + (2 * half)) - n_used;
    memcpy(p->start, p->buf + n_free, n_used);
    free(p->buf);
    p->buf = q;
    p->n_alloc = 2 * half;
  }
  p->start -= 1 + s_len;
  p->start[0] = '/';
  memcpy(p->start + 1, s, s_len);
}

static char *nth_parent(size_t n)
{
  char *buf = xnmalloc(3, n);
  char *p = buf;
  unsigned int p_idx = 0;
  for (size_t i = 0; i < n; i += 1)
  {
    memcpy(p, "../", 3);
    p_idx += 3;
  }

  p[(-1) + p_idx] = '\0';
  return buf;
}

static void find_dir_entry(struct stat *dot_sb, struct file_name *file_name, size_t parent_height)
{
  DIR *dirp;
  unsigned int dirp_idx = 0;
  int fd;
  struct stat parent_sb;
  bool use_lstat;
  bool found;
  dirp_idx = opendir("..");
  if ((&dirp[dirp_idx]) == ((void *) 0))
  {
    error(1, errno, gettext("cannot open directory %s"), quote(nth_parent(parent_height)));
  }
  fd = dirfd(dirp);
  if (((0 <= fd) ? (fchdir(fd)) : (chdir(".."))) < 0)
  {
    error(1, errno, gettext("failed to chdir to %s"), quote(nth_parent(parent_height)));
  }
  if (((0 <= fd) ? (fstat(fd, &parent_sb)) : (stat(".", &parent_sb))) < 0)
  {
    error(1, errno, gettext("failed to stat %s"), quote(nth_parent(parent_height)));
  }
  use_lstat = parent_sb.st_dev != dot_sb->st_dev;
  found = 0;
  while (1)
  {
    helper_find_dir_entry_1(&dirp_idx, &found, dot_sb, file_name, dirp, use_lstat);
  }

  if (((&dirp[dirp_idx]) == ((void *) 0)) || (closedir(dirp) != 0))
  {
    error(1, errno, gettext("reading directory %s"), quote(nth_parent(parent_height)));
  }
  if (!found)
  {
    error(1, 0, gettext("couldn't find directory entry in %s with matching i-node"), quote(nth_parent(parent_height)));
  }
  *dot_sb = parent_sb;
}

static void robust_getcwd(struct file_name *file_name)
{
  size_t height = 1;
  struct dev_ino dev_ino_buf;
  struct dev_ino *root_dev_ino = get_root_dev_ino(&dev_ino_buf);
  struct stat dot_sb;
  if (root_dev_ino == ((void *) 0))
  {
    error(1, errno, gettext("failed to get attributes of %s"), quotearg_style(shell_escape_always_quoting_style, "/"));
  }
  if (stat(".", &dot_sb) < 0)
  {
    error(1, errno, gettext("failed to stat %s"), quotearg_style(shell_escape_always_quoting_style, "."));
  }
  while (1)
  {
    if (!(((&dot_sb)->st_dev ^ root_dev_ino->st_dev) | ((&dot_sb)->st_ino ^ root_dev_ino->st_ino)))
    {
      break;
    }
    find_dir_entry(&dot_sb, file_name, height);
    height += 1;
  }

  if (file_name->start[0] == '\0')
  {
    file_name_prepend(file_name, "", 0);
  }
}

static char *logical_getcwd(void)
{
  struct stat st1;
  struct stat st2;
  char *wd = getenv("PWD");
  char *p;
  unsigned int p_idx = 0;
  if ((!wd) || (wd[0] != '/'))
  {
    return (void *) 0;
  }
  p_idx = wd;
  while (p_idx = strstr(p_idx, "/."))
  {
    if (((!p[2 + p_idx]) || (p[2 + p_idx] == '/')) || ((p[2 + p_idx] == '.') && ((!p[3 + p_idx]) || (p[3 + p_idx] == '/'))))
    {
      return (void *) 0;
    }
    p_idx += 1;
  }

  if (((stat(wd, &st1) == 0) && (stat(".", &st2) == 0)) && psame_inode(&st1, &st2))
  {
    return wd;
  }
  return (void *) 0;
}

int main(int argc, char **argv)
{
  char *wd;
  unsigned int wd_idx = 0;
  bool logical = getenv("POSIXLY_CORRECT") != ((void *) 0);
  ;
  set_program_name(argv[0]);
  setlocale(LC_ALL, "");
  bindtextdomain("coreutils", "/usr/local/share/locale");
  textdomain("coreutils");
  atexit(close_stdout);
  while (1)
  {
    helper_main_1(&logical, argc, argv);
  }

  if (optind < argc)
  {
    error(0, 0, gettext("ignoring non-option arguments"));
  }
  if (logical)
  {
    wd_idx = logical_getcwd();
    if (wd)
    {
      puts(wd);
      return 0;
    }
  }
  wd_idx = xgetcwd();
  if ((&wd[wd_idx]) != ((void *) 0))
  {
    puts(wd);
    free(wd);
  }
  else
  {
    struct file_name *file_name = file_name_init();
    robust_getcwd(file_name);
    puts(file_name->start);
    file_name_free(file_name);
  }
  return 0;
}

void helper_find_dir_entry_1(unsigned int * const dirp_idx_ref, bool * const found_ref, struct stat * const dot_sb, struct file_name * const file_name, DIR * const dirp, bool use_lstat)
{
  unsigned int dirp_idx = *dirp_idx_ref;
  bool found = *found_ref;
  const struct dirent *dp;
  unsigned int dp_idx = 0;
  struct stat ent_sb;
  ino_t ino;
  errno = 0;
  if ((dp_idx = readdir_ignoring_dot_and_dotdot(dirp)) == ((void *) 0))
  {
    if (errno)
    {
      int e = errno;
      closedir(dirp);
      errno = e;
      dirp_idx = (void *) 0;
    }
    break;
  }
  ino = dp->d_ino;
  if ((ino == NOT_AN_INODE_NUMBER) || use_lstat)
  {
    if (lstat(dp->d_name, &ent_sb) < 0)
    {
      continue;
    }
    ino = ent_sb.st_ino;
  }
  if (ino != dot_sb->st_ino)
  {
    continue;
  }
  if ((!use_lstat) || (ent_sb.st_dev == dot_sb->st_dev))
  {
    file_name_prepend(file_name, dp->d_name, strlen(dp->d_name));
    found = 1;
    break;
  }
  *dirp_idx_ref = dirp_idx;
  *found_ref = found;
}

void helper_main_1(bool * const logical_ref, int argc, char ** const argv)
{
  bool logical = *logical_ref;
  int c = getopt_long(argc, argv, "LP", longopts, (void *) 0);
  if (c == (-1))
  {
    break;
  }
  switch (c)
  {
    case 'L':
    {
      logical = 1;
      break;
    }

    case 'P':
    {
      logical = 0;
      break;
    }

    case GETOPT_HELP_CHAR:
    {
      usage(0);
      break;
      ;
    }

    case GETOPT_VERSION_CHAR:
    {
      version_etc(stdout, "pwd", "GNU coreutils", Version, proper_name_lite("Jim Meyering", "Jim Meyering"), (char *) ((void *) 0));
      exit(0);
      break;
      ;
    }

    default:
    {
      usage(1);
    }

  }

  *logical_ref = logical;
}

