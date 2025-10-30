inline struct timespec make_timespec(time_t s, long int ns)
{
  return (struct timespec){.tv_sec = s, .tv_nsec = ns};
}


/*** DEPENDENCIES:
***/


inline int timespec_cmp(struct timespec a, struct timespec b)
{
  return (2 * ((a.tv_sec > b.tv_sec) - (a.tv_sec < b.tv_sec))) + ((a.tv_nsec > b.tv_nsec) - (a.tv_nsec < b.tv_nsec));
}


/*** DEPENDENCIES:
***/


inline int timespec_sign(struct timespec a)
{
  return ((a.tv_sec > 0) - (a.tv_sec < 0)) + ((!a.tv_sec) & (!(!a.tv_nsec)));
}


/*** DEPENDENCIES:
***/


inline double timespectod(struct timespec a)
{
  return a.tv_sec + (a.tv_nsec / 1e9);
}


/*** DEPENDENCIES:
***/


inline static unsigned char to_uchar(char ch)
{
  return ch;
}


/*** DEPENDENCIES:
***/


inline static unsigned long int select_plural(uintmax_t n)
{
  enum 
  {
    PLURAL_REDUCER = 1000000
  };
  return (n <= 18446744073709551615UL) ? (n) : ((n % PLURAL_REDUCER) + PLURAL_REDUCER);
}


/*** DEPENDENCIES:
***/


inline bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}


/*** DEPENDENCIES:
***/


inline int chownat(int fd, const char *file, uid_t owner, gid_t group)
{
  return fchownat(fd, file, owner, group, 0);
}


/*** DEPENDENCIES:
***/


inline int lchownat(int fd, const char *file, uid_t owner, gid_t group)
{
  return fchownat(fd, file, owner, group, AT_SYMLINK_NOFOLLOW);
}


/*** DEPENDENCIES:
***/


inline int chmodat(int fd, const char *file, mode_t mode)
{
  return fchmodat(fd, file, mode, 0);
}


/*** DEPENDENCIES:
***/


inline int lchmodat(int fd, const char *file, mode_t mode)
{
  return fchmodat(fd, file, mode, AT_SYMLINK_NOFOLLOW);
}


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


inline static void *ptr_align(const void *ptr, size_t alignment)
{
  const char *p0 = ptr;
  const char *p1 = (p0 + alignment) - 1;
  return (void *) (p1 - (((size_t) p1) % alignment));
}


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


inline static void emit_stdin_note(void)
{
  fputs_unlocked(gettext("\nWith no FILE, or when FILE is -, read standard input.\n"), stdout);
}


/*** DEPENDENCIES:
***/


inline static void emit_mandatory_arg_note(void)
{
  fputs_unlocked(gettext("\nMandatory arguments to long options are mandatory for short options too.\n"), stdout);
}


/*** DEPENDENCIES:
***/


inline static void emit_size_note(void)
{
  fputs_unlocked(gettext("\nThe SIZE argument is an integer and optional unit (example: 10K is 10*1024).\nUnits are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\nBinary prefixes can be used, too: KiB=K, MiB=M, and so on.\n"), stdout);
}


/*** DEPENDENCIES:
***/


inline static void emit_blocksize_note(const char *program)
{
  printf(gettext("\nDisplay values are in units of the first available SIZE from --block-size,\nand the %s_BLOCK_SIZE, BLOCK_SIZE and BLOCKSIZE environment variables.\nOtherwise, units default to 1024 bytes (or 512 if POSIXLY_CORRECT is set).\n"), program);
}


/*** DEPENDENCIES:
***/


inline static void emit_update_parameters_note(void)
{
  fputs_unlocked(gettext("\nUPDATE controls which existing files in the destination are replaced.\n'all' is the default operation when an --update option is not specified,\nand results in all existing files in the destination being replaced.\n'none' is like the --no-clobber option, in that no files in the\ndestination are replaced, and skipped files do not induce a failure.\n'none-fail' also ensures no files are replaced in the destination,\nbut any skipped files are diagnosed and induce a failure.\n'older' is the default operation when --update is specified, and results\nin files being replaced if they're older than the corresponding source file.\n"), stdout);
}


/*** DEPENDENCIES:
***/


inline static void emit_backup_suffix_note(void)
{
  fputs_unlocked(gettext("\nThe backup suffix is '~', unless set with --suffix or SIMPLE_BACKUP_SUFFIX.\nThe version control method may be selected via the --backup option or through\nthe VERSION_CONTROL environment variable.  Here are the values:\n\n"), stdout);
  fputs_unlocked(gettext("  none, off       never make backups (even if --backup is given)\n  numbered, t     make numbered backups\n  existing, nil   numbered if numbered backups exist, simple otherwise\n  simple, never   always make simple backups\n"), stdout);
}


/*** DEPENDENCIES:
***/


inline static void emit_symlink_recurse_options(const char *default_opt)
{
  printf(gettext("\nThe following options modify how a hierarchy is traversed when the -R\noption is also specified.  If more than one is specified, only the final\none takes effect. '%s' is the default.\n\n  -H                     if a command line argument is a symbolic link\n                         to a directory, traverse it\n  -L                     traverse every symbolic link to a directory\n                         encountered\n  -P                     do not traverse any symbolic links\n\n"), default_opt);
}


/*** DEPENDENCIES:
***/


inline static void emit_exec_status(const char *program)
{
  printf(gettext("\nExit status:\n  125  if the %s command itself fails\n  126  if COMMAND is found but cannot be invoked\n  127  if COMMAND cannot be found\n  -    the exit status of COMMAND otherwise\n"), program);
}


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


inline static char *timetostr(time_t t, char *buf)
{
  return (!(((time_t) 0) < ((time_t) (-1)))) ? (imaxtostr(t, buf)) : (umaxtostr(t, buf));
}


/*** DEPENDENCIES:
***/


inline static char *bad_cast(const char *s)
{
  return (char *) s;
}


/*** DEPENDENCIES:
***/


inline static bool usable_st_size(const struct stat *sb)
{
  return ((S_ISREG(sb->st_mode) || S_ISLNK(sb->st_mode)) || S_TYPEISSHM(sb)) || S_TYPEISTMO(sb);
}


/*** DEPENDENCIES:
***/


inline static void write_error(void)
{
  int saved_errno = errno;
  fflush_unlocked(stdout);
  fpurge(stdout);
  clearerr_unlocked(stdout);
  error(1, saved_errno, gettext("write error"));
}


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
***/


inline static bool is_ENOTSUP(int err)
{
  return (err == EOPNOTSUPP) || ((ENOTSUP != EOPNOTSUPP) && (err == ENOTSUP));
}


/*** DEPENDENCIES:
***/


inline static void initialize_exit_failure(int status)
{
  if (status != 1)
  {
    exit_failure = status;
  }
}


/*** DEPENDENCIES:
extern volatile int exit_failure
----------------------------
***/


inline void *xnrealloc(void *p, size_t n, size_t s)
{
  return xreallocarray(p, n, s);
}


/*** DEPENDENCIES:
void *xreallocarray(void *p, size_t n, size_t s)
{
  void *r = reallocarray(p, n, s);
  if ((!r) && ((!p) || (n && s)))
  {
    xalloc_die();
  }
  return r;
}


----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
***/


inline static size_t lcm(size_t u, size_t v)
{
  return u * (v / gcd(u, v));
}


/*** DEPENDENCIES:
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


----------------------------
***/


static void file_name_free(struct file_name *p)
{
  free(p->buf);
  free(p);
}


/*** DEPENDENCIES:
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
***/


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


/*** DEPENDENCIES:
void *xnmalloc(size_t n, size_t s)
{
  return xreallocarray(0, n, s);
}


----------------------------
***/


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


/*** DEPENDENCIES:
inline bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}


----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
extern const char *program_name
----------------------------
***/


static struct file_name *file_name_init(void)
{
  struct file_name *p = xmalloc(sizeof(*p));
  p->n_alloc = ((2 * 8192) < (32 * 1024)) ? (2 * 8192) : (32 * 1024);
  p->buf = xmalloc(p->n_alloc);
  p->start = p->buf + (p->n_alloc - 1);
  p->start[0] = '\0';
  return p;
}


/*** DEPENDENCIES:
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
void *xmalloc(size_t s)
{
  return check_nonnull(malloc(s));
}


----------------------------
***/


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


/*** DEPENDENCIES:
void *xnmalloc(size_t n, size_t s)
{
  return xreallocarray(0, n, s);
}


----------------------------
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
***/


// hint:  ['dirp_idx_ref is a mutable refrence to unsigned int', 'found_ref is a mutable refrence to bool']
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


/*** DEPENDENCIES:
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


----------------------------
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
const char *quote(const char *arg)
{
  return quote_n(0, arg);
}


----------------------------
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


----------------------------
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


----------------------------
***/


// hint:  ['logical_ref is a mutable refrence to bool']
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


/*** DEPENDENCIES:
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


----------------------------
void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...)
{
  va_list authors;
  __builtin_va_start(authors);
  version_etc_va(stream, command_name, package, version, authors);
  ;
}


----------------------------
extern const char *Version
----------------------------
const char *proper_name_lite(const char *name_ascii, const char *name_utf8)
{
  const char *translation = gettext(name_ascii);
  return (translation != name_ascii) ? (translation) : ((c_strcasecmp(locale_charset(), "UTF-8") == 0) ? (name_utf8) : (name_ascii));
}


----------------------------
static const struct option longopts[] = {{"logical", no_argument, (void *) 0, 'L'}, {"physical", no_argument, (void *) 0, 'P'}, {"help", no_argument, (void *) 0, GETOPT_HELP_CHAR}, {"version", no_argument, (void *) 0, GETOPT_VERSION_CHAR}, {(void *) 0, 0, (void *) 0, 0}}
----------------------------
***/


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


/*** DEPENDENCIES:
struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
}
----------------------------
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


----------------------------
struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i)
{
  struct stat statbuf;
  if (lstat("/", &statbuf))
  {
    return (void *) 0;
  }
  root_d_i->st_ino = statbuf.st_ino;
  root_d_i->st_dev = statbuf.st_dev;
  return root_d_i;
}


----------------------------
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


----------------------------
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
char *quotearg_style(enum quoting_style s, const char *arg)
{
  return quotearg_n_style(0, s, arg);
}


----------------------------
***/


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


/*** DEPENDENCIES:
static void file_name_free(struct file_name *p)
{
  free(p->buf);
  free(p);
}


----------------------------
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


----------------------------
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
void close_stdout(void)
{
  if ((close_stream(stdout) != 0) && (!(ignore_EPIPE && (errno == EPIPE))))
  {
    const char *write_error = gettext("write error");
    if (file_name)
    {
      error(0, errno, "%s: %s", quotearg_colon(file_name), write_error);
    }
    else
      error(0, errno, "%s", write_error);
    _exit(exit_failure);
  }
  if ((!SANITIZE_ADDRESS) && (close_stream(stderr) != 0))
  {
    _exit(exit_failure);
  }
}


----------------------------
static struct file_name *file_name_init(void)
{
  struct file_name *p = xmalloc(sizeof(*p));
  p->n_alloc = ((2 * 8192) < (32 * 1024)) ? (2 * 8192) : (32 * 1024);
  p->buf = xmalloc(p->n_alloc);
  p->start = p->buf + (p->n_alloc - 1);
  p->start[0] = '\0';
  return p;
}


----------------------------
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


----------------------------
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


----------------------------
void set_program_name(const char *argv0)
{
  unsigned int argv0_idx = 0;
  const char *slash;
  unsigned int slash_idx = 0;
  const char *base;
  unsigned int base_idx = 0;
  if ((&argv0[argv0_idx]) == 0)
  {
    fputs("A NULL argv[0] was passed through an exec system call.\n", stderr);
    abort();
  }
  slash_idx = strrchr(argv0, '/');
  base_idx = ((&slash[slash_idx]) != 0) ? ((&slash[slash_idx]) + 1) : (argv0);
  if ((((&base[base_idx]) - (&argv0[argv0_idx])) >= 7) && (strncmp((&base[base_idx]) - 7, "/.libs/", 7) == 0))
  {
    argv0_idx = &base[base_idx];
    if (strncmp(base, "lt-", 3) == 0)
    {
      argv0_idx = (&base[base_idx]) + 3;
      program_invocation_short_name = (char *) argv0;
    }
  }
  program_name = &argv0[argv0_idx];
  program_invocation_name = (char *) argv0;
}


----------------------------
char *xgetcwd(void)
{
  char *cwd = getcwd(0, 0);
  if ((!cwd) && (errno == ENOMEM))
  {
    xalloc_die();
  }
  return cwd;
}


----------------------------
***/


