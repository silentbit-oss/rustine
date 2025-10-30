inline static void utoa(char *str, size_t v)
{
  char *p = str;
  unsigned int p_idx = 0;
  do
  {
    p[p_idx] = '0' + (v % 10);
    p_idx += 1;
    v /= 10;
  }
  while (v > 0);
  size_t len = (&p[p_idx]) - str;
  for (size_t i = 0; i < (len / 2); i += 1)
  {
    char tmp = str[i];
    str[i] = str[(len - i) - 1];
    str[(len - i) - 1] = tmp;
  }

  str[len] = '\0';
}


/*** DEPENDENCIES:
***/


inline static int host_is_little_endian()
{
  int test = 1;
  char *bytes = (char *) (&test);
  return bytes[0] == 1;
}


/*** DEPENDENCIES:
***/


static int is_ascending_order(uint64_t *v, size_t n)
{
  for (size_t j = 1; j < n; j += 1)
    if (v[j - 1] >= v[j])
  {
    return 0;
  }

  return 1;
}


/*** DEPENDENCIES:
***/


static void print_colon_delimited_paths(const char *start, const char *indent)
{
  unsigned int start_idx = 0;
  while (1)
  {
    if (start[start_idx] == '\0')
    {
      break;
    }
    char *next = strchr(start, ':');
    if ((&start[start_idx]) == next)
    {
      start_idx += 1;
      continue;
    }
    fputs(indent, stdout);
    fputs("    ", stdout);
    if (next == 0)
    {
      puts(start);
    }
    else
    {
      fwrite(start, 1, next - (&start[start_idx]), stdout);
      putchar('\n');
    }
    if (next == 0)
    {
      break;
    }
    start_idx = next + 1;
  }

}


/*** DEPENDENCIES:
***/


inline static void small_vec_u64_init(struct small_vec_u64_t *v)
{
  memset(v, 0, sizeof(*v));
  v->p = v->buf;
}


/*** DEPENDENCIES:
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
***/


static void small_vec_u64_append(struct small_vec_u64_t *v, uint64_t val)
{
  if (v->n < 16)
  {
    v->p[v->n++] = val;
    return;
  }
  if (v->n == 16)
  {
    v->capacity = 2 * 16;
    v->p = malloc(v->capacity * (sizeof(uint64_t)));
    if (v->p == 0)
    {
      exit(1);
    }
    memcpy(v->p, v->buf, 16 * (sizeof(uint64_t)));
  }
  else
    if (v->n == v->capacity)
  {
    v->capacity *= 2;
    uint64_t *p = realloc(v->p, v->capacity * (sizeof(uint64_t)));
    if (p == 0)
    {
      exit(1);
    }
    v->p = p;
  }
  v->p[v->n++] = val;
}


/*** DEPENDENCIES:
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
***/


static void small_vec_u64_free(struct small_vec_u64_t *v)
{
  if (v->n <= 16)
  {
    return;
  }
  free(v->p);
  v->p = 0;
}


/*** DEPENDENCIES:
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
***/


static void string_table_maybe_grow(struct string_table_t *t, size_t n)
{
  if ((t->n + n) <= t->capacity)
  {
    return;
  }
  t->capacity = 2 * (t->n + n);
  char *arr = realloc(t->arr, t->capacity * (sizeof(char)));
  if (arr == 0)
  {
    exit(1);
  }
  t->arr = arr;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
***/


static int is_in_exclude_list(char *soname)
{
  char *start = soname;
  char *end = strrchr(start, '\0');
  unsigned int end_idx = 0;
  if (start == (&end[end_idx]))
  {
    return 0;
  }
  end_idx -= 1;
  while (((&end[end_idx]) != start) && (((end[end_idx] >= '0') && (end[end_idx] <= '9')) || (end[end_idx] == '.')))
  {
    end_idx -= 1;
  }

  for (size_t j = 0; j < ((sizeof(exclude_list)) / (sizeof(char *))); j += 1)
  {
    size_t len = strlen(exclude_list[j]);
    if (strncmp(start, exclude_list[j], len) != 0)
    {
      continue;
    }
    return 1;
  }

  return 0;
}


/*** DEPENDENCIES:
const char *exclude_list[] = {"ld-linux-aarch64.so", "ld-linux-armhf.so", "ld-linux-x86-64.so", "ld-linux.so", "ld64.so", "libc.musl-aarch64.so", "libc.musl-armhf.so", "libc.musl-i386.so", "libc.musl-x86_64.so", "libc.so", "libdl.so", "libgcc_s.so", "libm.so", "libstdc++.so"}
----------------------------
***/


static void tree_preamble(struct libtree_state_t *s, size_t depth)
{
  if (depth == 0)
  {
    return;
  }
  for (size_t i = 0; i < (depth - 1); i += 1)
    fputs((s->found_all_needed[i]) ? ("    ") : ("\xe2\x94\x82   "), stdout);

  fputs((s->found_all_needed[depth - 1]) ? ("\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 ") : ("\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 "), stdout);
}


/*** DEPENDENCIES:
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


static void visited_files_append(struct visited_file_array_t *files, struct stat *new)
{
  if (files->n == files->capacity)
  {
    files->capacity *= 2;
    files->arr = realloc(files->arr, files->capacity * (sizeof(struct visited_file_t)));
    if (files->arr == 0)
    {
      exit(1);
    }
  }
  files->arr[files->n].st_dev = new->st_dev;
  files->arr[files->n].st_ino = new->st_ino;
  files->n += 1;
}


/*** DEPENDENCIES:
struct visited_file_array_t
{
  struct visited_file_t *arr;
  size_t n;
  size_t capacity;
}
----------------------------
***/


static void libtree_state_init(struct libtree_state_t *s)
{
  s->string_table.n = 0;
  s->string_table.capacity = 1024;
  s->string_table.arr = malloc(s->string_table.capacity * (sizeof(char)));
  s->visited.n = 0;
  s->visited.capacity = 256;
  s->visited.arr = malloc(s->visited.capacity * (sizeof(struct visited_file_t)));
}


/*** DEPENDENCIES:
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


static void libtree_state_free(struct libtree_state_t *s)
{
  free(s->string_table.arr);
  free(s->visited.arr);
}


/*** DEPENDENCIES:
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


// hint:  ['s_ref is a mutable refrence to ', 'opt_help_ref is a mutable refrence to int', 'opt_version_ref is a mutable refrence to int', 'opt_raw_ref is a mutable refrence to int', 'i_ref is a mutable refrence to int', 'arg_idx_ref is a mutable refrence to unsigned int']
int helper_helper_main_2_1(struct libtree_state_t * const s_ref, int * const opt_help_ref, int * const opt_version_ref, int * const opt_raw_ref, int * const i_ref, unsigned int * const arg_idx_ref, int argc, char ** const argv, unsigned int argv_idx, char * const arg)
{
  struct libtree_state_t s = *s_ref;
  int opt_help = *opt_help_ref;
  int opt_version = *opt_version_ref;
  int opt_raw = *opt_raw_ref;
  int i = *i_ref;
  unsigned int arg_idx = *arg_idx_ref;
  arg_idx += 1;
  if (arg[arg_idx] == '\0')
  {
    opt_raw = 1;
    continue;
  }
  if (strcmp(arg, "version") == 0)
  {
    opt_version = 1;
  }
  else
    if (strcmp(arg, "path") == 0)
  {
    s.path = 1;
  }
  else
    if (strcmp(arg, "verbose") == 0)
  {
    s.verbosity += 1;
  }
  else
    if (strcmp(arg, "help") == 0)
  {
    opt_help = 1;
  }
  else
    if (strcmp(arg, "ldconf") == 0)
  {
    if ((i + 1) == argc)
    {
      fputs("Expected value after `--ldconf`\n", stderr);
      return 1;
    }
    i += 1;
    s.ld_conf_file = argv[i + argv_idx];
  }
  else
    if (strcmp(arg, "max-depth") == 0)
  {
    if ((i + 1) == argc)
    {
      fputs("Expected value after `--max-depth`\n", stderr);
      return 1;
    }
    char *ptr;
    i += 1;
    s.max_depth = strtoul(argv[i + argv_idx], &ptr, 10);
    if (s.max_depth > 32)
      s.max_depth = 32;
  }
  else
  {
    fputs("Unrecognized flag `--", stderr);
    fputs(arg, stderr);
    fputs("`\n", stderr);
    return 1;
  }
  continue;
  *s_ref = s;
  *opt_help_ref = opt_help;
  *opt_version_ref = opt_version;
  *opt_raw_ref = opt_raw;
  *i_ref = i;
  *arg_idx_ref = arg_idx;
}


/*** DEPENDENCIES:
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


static void string_table_store(struct string_table_t *t, const char *str)
{
  size_t n = strlen(str) + 1;
  string_table_maybe_grow(t, n);
  memcpy(t->arr + t->n, str, n);
  t->n += n;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
static void string_table_maybe_grow(struct string_table_t *t, size_t n)
{
  if ((t->n + n) <= t->capacity)
  {
    return;
  }
  t->capacity = 2 * (t->n + n);
  char *arr = realloc(t->arr, t->capacity * (sizeof(char)));
  if (arr == 0)
  {
    exit(1);
  }
  t->arr = arr;
}


----------------------------
***/


static void string_table_copy_from_file(struct string_table_t *t, FILE *fptr)
{
  int c;
  while (((c = getc(fptr)) != '\0') && (c != EOF))
  {
    string_table_maybe_grow(t, 1);
    t->arr[t->n++] = c;
  }

  string_table_maybe_grow(t, 1);
  t->arr[t->n++] = '\0';
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
static void string_table_maybe_grow(struct string_table_t *t, size_t n)
{
  if ((t->n + n) <= t->capacity)
  {
    return;
  }
  t->capacity = 2 * (t->n + n);
  char *arr = realloc(t->arr, t->capacity * (sizeof(char)));
  if (arr == 0)
  {
    exit(1);
  }
  t->arr = arr;
}


----------------------------
***/


static int visited_files_contains(struct visited_file_array_t *files, struct stat *needle)
{
  for (size_t i = 0; i < files->n; i += 1)
  {
    struct visited_file_t *f = &files->arr[i];
    if ((f->st_dev == needle->st_dev) && (f->st_ino == needle->st_ino))
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct visited_file_array_t
{
  struct visited_file_t *arr;
  size_t n;
  size_t capacity;
}
----------------------------
struct visited_file_t
{
  dev_t st_dev;
  ino_t st_ino;
}
----------------------------
***/


static void parse_ld_library_path(struct libtree_state_t *s)
{
  s->ld_library_path_offset = SIZE_MAX;
  char *val = getenv("LD_LIBRARY_PATH");
  if (val == 0)
  {
    return;
  }
  s->ld_library_path_offset = s->string_table.n;
  string_table_store(&s->string_table, val);
  char *search = s->string_table.arr + s->ld_library_path_offset;
  unsigned int search_idx = 0;
  while ((search_idx = strchr(search_idx, ';')) != 0)
    search[search_idx] = ':';

  search_idx += 1;
}


/*** DEPENDENCIES:
static void string_table_store(struct string_table_t *t, const char *str)
{
  size_t n = strlen(str) + 1;
  string_table_maybe_grow(t, n);
  memcpy(t->arr + t->n, str, n);
  t->n += n;
}


----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


static void set_default_paths(struct libtree_state_t *s)
{
  s->default_paths_offset = s->string_table.n;
  string_table_store(&s->string_table, "/lib:/lib64:/usr/lib:/usr/lib64");
}


/*** DEPENDENCIES:
static void string_table_store(struct string_table_t *t, const char *str)
{
  size_t n = strlen(str) + 1;
  string_table_maybe_grow(t, n);
  memcpy(t->arr + t->n, str, n);
  t->n += n;
}


----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


static void apply_exclude_list(size_t *needed_not_found, struct small_vec_u64_t *needed_buf_offsets, struct libtree_state_t *s)
{
  for (size_t i = 0; i < (*needed_not_found);)
  {
    if (is_in_exclude_list(s->string_table.arr + needed_buf_offsets->p[i]))
    {
      size_t tmp = needed_buf_offsets->p[i];
      needed_buf_offsets->p[i] = needed_buf_offsets->p[(*needed_not_found) - 1];
      needed_buf_offsets->p[--(*needed_not_found)] = tmp;
      continue;
    }
    else
    {
      i += 1;
    }
  }

}


/*** DEPENDENCIES:
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static int is_in_exclude_list(char *soname)
{
  char *start = soname;
  char *end = strrchr(start, '\0');
  unsigned int end_idx = 0;
  if (start == (&end[end_idx]))
  {
    return 0;
  }
  end_idx -= 1;
  while (((&end[end_idx]) != start) && (((end[end_idx] >= '0') && (end[end_idx] <= '9')) || (end[end_idx] == '.')))
  {
    end_idx -= 1;
  }

  for (size_t j = 0; j < ((sizeof(exclude_list)) / (sizeof(char *))); j += 1)
  {
    size_t len = strlen(exclude_list[j]);
    if (strncmp(start, exclude_list[j], len) != 0)
    {
      continue;
    }
    return 1;
  }

  return 0;
}


----------------------------
***/


// hint:  ['prev_src_ref is a mutable refrence to size_t', 'curr_src_ref is a mutable refrence to size_t']
void helper_interpolate_variables_1(size_t * const prev_src_ref, size_t * const curr_src_ref, struct libtree_state_t * const s, const char * const ORIGIN, struct string_table_t * const st)
{
  size_t prev_src = *prev_src_ref;
  size_t curr_src = *curr_src_ref;
  char *dollar = strchr(st->arr + curr_src, '$');
  if (dollar == 0)
  {
    break;
  }
  curr_src = dollar - st->arr;
  size_t bytes_to_dollar = curr_src - prev_src;
  curr_src += 1;
  int curly = 0;
  if (st->arr[curr_src] == '{')
  {
    curly = 1;
    curr_src += 1;
  }
  const char *var_val = 0;
  unsigned int var_val_idx = 0;
  if (strncmp(&st->arr[curr_src], "ORIGIN", 6) == 0)
  {
    var_val_idx = ORIGIN;
    curr_src += 6;
  }
  else
    if (strncmp(&st->arr[curr_src], "LIB", 3) == 0)
  {
    var_val_idx = s->LIB;
    curr_src += 3;
  }
  else
    if (strncmp(&st->arr[curr_src], "PLATFORM", 8) == 0)
  {
    var_val_idx = s->PLATFORM;
    curr_src += 8;
  }
  else
    if (strncmp(&st->arr[curr_src], "OSNAME", 6) == 0)
  {
    var_val_idx = s->OSNAME;
    curr_src += 6;
  }
  else
    if (strncmp(&st->arr[curr_src], "OSREL", 5) == 0)
  {
    var_val_idx = s->OSREL;
    curr_src += 5;
  }
  else
  {
    continue;
  }
  if (curly)
  {
    if (st->arr[curr_src] != '}')
    {
      continue;
    }
    curr_src += 1;
  }
  size_t var_len = strlen(var_val);
  string_table_maybe_grow(st, bytes_to_dollar + var_len);
  memcpy(&st->arr[s->string_table.n], &st->arr[prev_src], bytes_to_dollar);
  s->string_table.n += bytes_to_dollar;
  prev_src = curr_src;
  memcpy(&st->arr[s->string_table.n], var_val, var_len);
  s->string_table.n += var_len;
  *prev_src_ref = prev_src;
  *curr_src_ref = curr_src;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static void string_table_maybe_grow(struct string_table_t *t, size_t n)
{
  if ((t->n + n) <= t->capacity)
  {
    return;
  }
  t->capacity = 2 * (t->n + n);
  char *arr = realloc(t->arr, t->capacity * (sizeof(char)));
  if (arr == 0)
  {
    exit(1);
  }
  t->arr = arr;
}


----------------------------
***/


static int interpolate_variables(struct libtree_state_t *s, size_t src, const char *ORIGIN)
{
  size_t prev_src = src;
  size_t curr_src = src;
  struct string_table_t *st = &s->string_table;
  while (1)
  {
    helper_interpolate_variables_1(&prev_src, &curr_src, s, ORIGIN, st);
  }

  if (prev_src != src)
  {
    size_t n = strlen(st->arr + prev_src) + 1;
    string_table_maybe_grow(st, n);
    memcpy(st->arr + st->n, st->arr + prev_src, n);
    st->n += n;
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
void helper_interpolate_variables_1(size_t * const prev_src_ref, size_t * const curr_src_ref, struct libtree_state_t * const s, const char * const ORIGIN, struct string_table_t * const st)
{
  size_t prev_src = *prev_src_ref;
  size_t curr_src = *curr_src_ref;
  char *dollar = strchr(st->arr + curr_src, '$');
  if (dollar == 0)
  {
    break;
  }
  curr_src = dollar - st->arr;
  size_t bytes_to_dollar = curr_src - prev_src;
  curr_src += 1;
  int curly = 0;
  if (st->arr[curr_src] == '{')
  {
    curly = 1;
    curr_src += 1;
  }
  const char *var_val = 0;
  unsigned int var_val_idx = 0;
  if (strncmp(&st->arr[curr_src], "ORIGIN", 6) == 0)
  {
    var_val_idx = ORIGIN;
    curr_src += 6;
  }
  else
    if (strncmp(&st->arr[curr_src], "LIB", 3) == 0)
  {
    var_val_idx = s->LIB;
    curr_src += 3;
  }
  else
    if (strncmp(&st->arr[curr_src], "PLATFORM", 8) == 0)
  {
    var_val_idx = s->PLATFORM;
    curr_src += 8;
  }
  else
    if (strncmp(&st->arr[curr_src], "OSNAME", 6) == 0)
  {
    var_val_idx = s->OSNAME;
    curr_src += 6;
  }
  else
    if (strncmp(&st->arr[curr_src], "OSREL", 5) == 0)
  {
    var_val_idx = s->OSREL;
    curr_src += 5;
  }
  else
  {
    continue;
  }
  if (curly)
  {
    if (st->arr[curr_src] != '}')
    {
      continue;
    }
    curr_src += 1;
  }
  size_t var_len = strlen(var_val);
  string_table_maybe_grow(st, bytes_to_dollar + var_len);
  memcpy(&st->arr[s->string_table.n], &st->arr[prev_src], bytes_to_dollar);
  s->string_table.n += bytes_to_dollar;
  prev_src = curr_src;
  memcpy(&st->arr[s->string_table.n], var_val, var_len);
  s->string_table.n += var_len;
  *prev_src_ref = prev_src;
  *curr_src_ref = curr_src;
}


----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static void string_table_maybe_grow(struct string_table_t *t, size_t n)
{
  if ((t->n + n) <= t->capacity)
  {
    return;
  }
  t->capacity = 2 * (t->n + n);
  char *arr = realloc(t->arr, t->capacity * (sizeof(char)));
  if (arr == 0)
  {
    exit(1);
  }
  t->arr = arr;
}


----------------------------
***/


// hint:  ['no_def_lib_ref is a mutable refrence to int', 'strtab_ref is a mutable refrence to uint64_t', 'rpath_ref is a mutable refrence to uint64_t', 'runpath_ref is a mutable refrence to uint64_t', 'soname_ref is a mutable refrence to uint64_t', 'cont_ref is a mutable refrence to int']
int helper_recurse_1(int * const no_def_lib_ref, uint64_t * const strtab_ref, uint64_t * const rpath_ref, uint64_t * const runpath_ref, uint64_t * const soname_ref, int * const cont_ref, FILE * const fptr, struct compat_t curr_type, struct small_vec_u64_t pt_load_offset, struct small_vec_u64_t pt_load_vaddr, struct small_vec_u64_t needed)
{
  int no_def_lib = *no_def_lib_ref;
  uint64_t strtab = *strtab_ref;
  uint64_t rpath = *rpath_ref;
  uint64_t runpath = *runpath_ref;
  uint64_t soname = *soname_ref;
  int cont = *cont_ref;
  uint64_t d_tag;
  uint64_t d_val;
  if (curr_type.class == 2)
  {
    struct dyn_64_t dyn;
    if (fread(&dyn, sizeof(struct dyn_64_t), 1, fptr) != 1)
    {
      fclose(fptr);
      small_vec_u64_free(&pt_load_offset);
      small_vec_u64_free(&pt_load_vaddr);
      small_vec_u64_free(&needed);
      return 22;
    }
    d_tag = dyn.d_tag;
    d_val = dyn.d_val;
  }
  else
  {
    struct dyn_32_t dyn;
    if (fread(&dyn, sizeof(struct dyn_32_t), 1, fptr) != 1)
    {
      fclose(fptr);
      small_vec_u64_free(&pt_load_offset);
      small_vec_u64_free(&pt_load_vaddr);
      small_vec_u64_free(&needed);
      return 22;
    }
    d_tag = dyn.d_tag;
    d_val = dyn.d_val;
  }
  switch (d_tag)
  {
    case 0:
    {
      cont = 0;
      break;
    }

    case 5:
    {
      strtab = d_val;
      break;
    }

    case 15:
    {
      rpath = d_val;
      break;
    }

    case 29:
    {
      runpath = d_val;
      break;
    }

    case 1:
    {
      small_vec_u64_append(&needed, d_val);
      break;
    }

    case 14:
    {
      soname = d_val;
      break;
    }

    case 0x6ffffffb:
    {
      no_def_lib |= (0x800 & d_val) == 0x800;
      break;
    }

  }

  *no_def_lib_ref = no_def_lib;
  *strtab_ref = strtab;
  *rpath_ref = rpath;
  *runpath_ref = runpath;
  *soname_ref = soname;
  *cont_ref = cont;
}


/*** DEPENDENCIES:
static void small_vec_u64_append(struct small_vec_u64_t *v, uint64_t val)
{
  if (v->n < 16)
  {
    v->p[v->n++] = val;
    return;
  }
  if (v->n == 16)
  {
    v->capacity = 2 * 16;
    v->p = malloc(v->capacity * (sizeof(uint64_t)));
    if (v->p == 0)
    {
      exit(1);
    }
    memcpy(v->p, v->buf, 16 * (sizeof(uint64_t)));
  }
  else
    if (v->n == v->capacity)
  {
    v->capacity *= 2;
    uint64_t *p = realloc(v->p, v->capacity * (sizeof(uint64_t)));
    if (p == 0)
    {
      exit(1);
    }
    v->p = p;
  }
  v->p[v->n++] = val;
}


----------------------------
struct compat_t
{
  char any;
  uint8_t class;
  uint16_t machine;
}
----------------------------
static void small_vec_u64_free(struct small_vec_u64_t *v)
{
  if (v->n <= 16)
  {
    return;
  }
  free(v->p);
  v->p = 0;
}


----------------------------
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
struct dyn_64_t
{
  int64_t d_tag;
  uint64_t d_val;
}
----------------------------
***/


void helper_print_error_1(size_t depth, struct libtree_state_t * const s, char * const indent)
{
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs(" 1. rpath:\n", stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  for (int j = depth; j >= 0; j -= 1)
  {
    if (s->rpath_offsets[j] != SIZE_MAX)
    {
      char num[8];
      utoa(num, j + 1);
      fputs(indent, stdout);
      if (s->color)
      {
        fputs("\033[0;90m", stdout);
      }
      fputs("    depth ", stdout);
      fputs(num, stdout);
      if (s->color)
      {
        fputs("\033[0m", stdout);
      }
      putchar('\n');
      print_colon_delimited_paths(s->string_table.arr + s->rpath_offsets[j], indent);
    }
  }

}


/*** DEPENDENCIES:
inline static void utoa(char *str, size_t v)
{
  char *p = str;
  unsigned int p_idx = 0;
  do
  {
    p[p_idx] = '0' + (v % 10);
    p_idx += 1;
    v /= 10;
  }
  while (v > 0);
  size_t len = (&p[p_idx]) - str;
  for (size_t i = 0; i < (len / 2); i += 1)
  {
    char tmp = str[i];
    str[i] = str[(len - i) - 1];
    str[(len - i) - 1] = tmp;
  }

  str[len] = '\0';
}


----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static void print_colon_delimited_paths(const char *start, const char *indent)
{
  unsigned int start_idx = 0;
  while (1)
  {
    if (start[start_idx] == '\0')
    {
      break;
    }
    char *next = strchr(start, ':');
    if ((&start[start_idx]) == next)
    {
      start_idx += 1;
      continue;
    }
    fputs(indent, stdout);
    fputs("    ", stdout);
    if (next == 0)
    {
      puts(start);
    }
    else
    {
      fwrite(start, 1, next - (&start[start_idx]), stdout);
      putchar('\n');
    }
    if (next == 0)
    {
      break;
    }
    start_idx = next + 1;
  }

}


----------------------------
***/


static void print_error(size_t depth, size_t needed_not_found, struct small_vec_u64_t *needed_buf_offsets, char *runpath, struct libtree_state_t *s, int no_def_lib)
{
  for (size_t i = 0; i < needed_not_found; i += 1)
  {
    s->found_all_needed[depth] = (i + 1) >= needed_not_found;
    tree_preamble(s, depth + 1);
    if (s->color)
    {
      fputs("\033[1;31m", stdout);
    }
    fputs(s->string_table.arr + needed_buf_offsets->p[i], stdout);
    fputs(" not found\n", stdout);
    if (s->color)
    {
      fputs("\033[0m", stdout);
    }
  }

  char *box_vertical = (s->color) ? ("    \033[0;31m\xe2\x94\x8a\033[0m") : ("    \xe2\x94\x8a");
  char *indent = malloc((((sizeof("\xe2\x94\x82   ")) * depth) + strlen(box_vertical)) + 1);
  char *p = indent;
  unsigned int p_idx = 0;
  for (size_t i = 0; i < depth; i += 1)
  {
    if (s->found_all_needed[i])
    {
      int len = (sizeof("    ")) - 1;
      memcpy(p, "    ", len);
      p_idx += len;
    }
    else
    {
      int len = (sizeof("\xe2\x94\x82   ")) - 1;
      memcpy(p, "\xe2\x94\x82   ", len);
      p_idx += len;
    }
  }

  strcpy(p, box_vertical);
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs(" Paths considered in this order:\n", stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  fputs(indent, stdout);
  if (runpath != 0)
  {
    if (s->color)
    {
      fputs("\033[0;90m", stdout);
    }
    fputs(" 1. rpath is skipped because runpath was set\n", stdout);
    if (s->color)
    {
      fputs("\033[0m", stdout);
    }
  }
  else
  {
    helper_print_error_1(depth, s, indent);
  }
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((s->ld_library_path_offset == SIZE_MAX) ? (" 2. LD_LIBRARY_PATH was not set\n") : (" 2. LD_LIBRARY_PATH:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  if (s->ld_library_path_offset != SIZE_MAX)
  {
    print_colon_delimited_paths(s->string_table.arr + s->ld_library_path_offset, indent);
  }
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((runpath == 0) ? (" 3. runpath was not set\n") : (" 3. runpath:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  if (runpath != 0)
  {
    print_colon_delimited_paths(runpath, indent);
  }
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((no_def_lib) ? (" 4. ld config files not considered due to NODEFLIB flag\n") : (" 4. ld config files:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  print_colon_delimited_paths(s->string_table.arr + s->ld_so_conf_offset, indent);
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((no_def_lib) ? (" 5. Standard paths not considered due to NODEFLIB flag\n") : (" 5. Standard paths:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  print_colon_delimited_paths(s->string_table.arr + s->default_paths_offset, indent);
  free(indent);
}


/*** DEPENDENCIES:
void helper_print_error_1(size_t depth, struct libtree_state_t * const s, char * const indent)
{
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs(" 1. rpath:\n", stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  for (int j = depth; j >= 0; j -= 1)
  {
    if (s->rpath_offsets[j] != SIZE_MAX)
    {
      char num[8];
      utoa(num, j + 1);
      fputs(indent, stdout);
      if (s->color)
      {
        fputs("\033[0;90m", stdout);
      }
      fputs("    depth ", stdout);
      fputs(num, stdout);
      if (s->color)
      {
        fputs("\033[0m", stdout);
      }
      putchar('\n');
      print_colon_delimited_paths(s->string_table.arr + s->rpath_offsets[j], indent);
    }
  }

}


----------------------------
static void tree_preamble(struct libtree_state_t *s, size_t depth)
{
  if (depth == 0)
  {
    return;
  }
  for (size_t i = 0; i < (depth - 1); i += 1)
    fputs((s->found_all_needed[i]) ? ("    ") : ("\xe2\x94\x82   "), stdout);

  fputs((s->found_all_needed[depth - 1]) ? ("\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 ") : ("\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 "), stdout);
}


----------------------------
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static void print_colon_delimited_paths(const char *start, const char *indent)
{
  unsigned int start_idx = 0;
  while (1)
  {
    if (start[start_idx] == '\0')
    {
      break;
    }
    char *next = strchr(start, ':');
    if ((&start[start_idx]) == next)
    {
      start_idx += 1;
      continue;
    }
    fputs(indent, stdout);
    fputs("    ", stdout);
    if (next == 0)
    {
      puts(start);
    }
    else
    {
      fwrite(start, 1, next - (&start[start_idx]), stdout);
      putchar('\n');
    }
    if (next == 0)
    {
      break;
    }
    start_idx = next + 1;
  }

}


----------------------------
***/


static void print_line(size_t depth, char *name, char *color_bold, char *color_regular, int highlight, struct found_t reason, struct libtree_state_t *s)
{
  tree_preamble(s, depth);
  char *slash = 0;
  unsigned int slash_idx = 0;
  if ((s->color && highlight) && ((slash_idx = strrchr(name, '/')) != 0))
  {
    fputs(color_regular, stdout);
    fwrite(name, 1, ((&slash[slash_idx]) + 1) - name, stdout);
    fputs(color_bold, stdout);
    fputs((&slash[slash_idx]) + 1, stdout);
  }
  else
  {
    if (s->color)
    {
      fputs(color_bold, stdout);
    }
    fputs(name, stdout);
  }
  if (s->color && highlight)
  {
    fputs("\033[0m \033[33m", stdout);
  }
  else
    putchar(' ');
  switch (reason.how)
  {
    case RPATH:
    {
      if ((reason.depth + 1) >= depth)
      {
        fputs("[rpath]", stdout);
      }
      else
      {
        char num[8];
        utoa(num, reason.depth + 1);
        fputs("[rpath of ", stdout);
        fputs(num, stdout);
        putchar(']');
      }
      break;
    }

    case LD_LIBRARY_PATH:
    {
      fputs("[LD_LIBRARY_PATH]", stdout);
      break;
    }

    case RUNPATH:
    {
      fputs("[runpath]", stdout);
      break;
    }

    case LD_SO_CONF:
    {
      putchar('[');
      char *conf_name = strrchr(s->ld_conf_file, '/');
      conf_name_idx = (conf_name_idx == 0) ? (s->ld_conf_file) : (conf_name_idx + 1);
      fputs(conf_name, stdout);
      putchar(']');
      break;
    }

    unsigned int conf_name_idx = 0;
    case DIRECT:
    {
      fputs("[direct]", stdout);
      break;
    }

    case DEFAULT:
    {
      fputs("[default path]", stdout);
      break;
    }

    default:
    {
      break;
    }

  }

  if (s->color)
  {
    fputs("\033[0m\n", stdout);
  }
  else
    putchar('\n');
}


/*** DEPENDENCIES:
inline static void utoa(char *str, size_t v)
{
  char *p = str;
  unsigned int p_idx = 0;
  do
  {
    p[p_idx] = '0' + (v % 10);
    p_idx += 1;
    v /= 10;
  }
  while (v > 0);
  size_t len = (&p[p_idx]) - str;
  for (size_t i = 0; i < (len / 2); i += 1)
  {
    char tmp = str[i];
    str[i] = str[(len - i) - 1];
    str[(len - i) - 1] = tmp;
  }

  str[len] = '\0';
}


----------------------------
struct found_t
{
  how_t how;
  size_t depth;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static void tree_preamble(struct libtree_state_t *s, size_t depth)
{
  if (depth == 0)
  {
    return;
  }
  for (size_t i = 0; i < (depth - 1); i += 1)
    fputs((s->found_all_needed[i]) ? ("    ") : ("\xe2\x94\x82   "), stdout);

  fputs((s->found_all_needed[depth - 1]) ? ("\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 ") : ("\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 "), stdout);
}


----------------------------
***/


// element in merge of:  check_absolute_paths,check_search_paths,recurse
static int check_absolute_paths(size_t *needed_not_found, struct small_vec_u64_t *needed_buf_offsets, size_t depth, struct libtree_state_t *s, struct compat_t compat)
{
  int exit_code = 0;
  for (size_t i = 0; i < (*needed_not_found);)
  {
    const struct string_table_t *st = &s->string_table;
    if (strchr(st->arr + needed_buf_offsets->p[i], '/') == 0)
    {
      i += 1;
      continue;
    }
    char path[4096];
    size_t len = strlen(st->arr + needed_buf_offsets->p[i]);
    if (len >= 4096)
    {
      continue;
    }
    memcpy(path, st->arr + needed_buf_offsets->p[i], len + 1);
    s->found_all_needed[depth] = (*needed_not_found) <= 1;
    char *err = 0;
    unsigned int err_idx = 0;
    if (path[0] != '/')
    {
      err_idx = " is not absolute";
      exit_code = 28;
    }
    else
    {
      int code = recurse(path, depth + 1, s, compat, (struct found_t){.how = DIRECT});
      if (code == 28)
      {
        exit_code = 28;
      }
      if ((code != 0) && (code != 28))
      {
        err_idx = " not found";
      }
    }
    if (err)
    {
      tree_preamble(s, depth + 1);
      if (s->color)
      {
        fputs("\033[1;31m", stdout);
      }
      fputs(path, stdout);
      fputs(" is not absolute", stdout);
      fputs((s->color) ? ("\033[0m\n") : ("\n"), stdout);
    }
    size_t tmp = needed_buf_offsets->p[i];
    needed_buf_offsets->p[i] = needed_buf_offsets->p[(*needed_not_found) - 1];
    needed_buf_offsets->p[--(*needed_not_found)] = tmp;
  }

  return exit_code;
}


/*** DEPENDENCIES:
static void tree_preamble(struct libtree_state_t *s, size_t depth)
{
  if (depth == 0)
  {
    return;
  }
  for (size_t i = 0; i < (depth - 1); i += 1)
    fputs((s->found_all_needed[i]) ? ("    ") : ("\xe2\x94\x82   "), stdout);

  fputs((s->found_all_needed[depth - 1]) ? ("\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 ") : ("\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 "), stdout);
}


----------------------------
struct compat_t
{
  char any;
  uint8_t class;
  uint16_t machine;
}
----------------------------
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
None
----------------------------
***/


// element in merge of:  check_absolute_paths,check_search_paths,recurse
static int check_search_paths(struct found_t reason, size_t offset, size_t *needed_not_found, struct small_vec_u64_t *needed_buf_offsets, size_t depth, struct libtree_state_t *s, struct compat_t compat)
{
  int exit_code = 0;
  char path[4096];
  char *path_end = path + 4096;
  const struct string_table_t *st = &s->string_table;
  while (st->arr[offset] != '\0')
  {
    offset += 1;
    offset += 1;
    offset += 1;
    offset += 1;
    offset += 1;
    offset += 1;
    offset += 1;
    offset += 1;
    while ((st->arr[offset] == ':') && (st->arr[offset] != '\0'))
      ++offset;

    if (st->arr[offset] == '\0')
      return exit_code;
    char *dest = path;
    while (((st->arr[offset] != '\0') && (st->arr[offset] != ':')) && (dest != path_end))
      *(dest++) = st->arr[offset++];

    if ((dest + 1) >= path_end)
      continue;
    if ((*(dest - 1)) != '/')
      *(dest++) = '/';
    char *search_path_end = dest;
    for (size_t i = 0; i < (*needed_not_found);)
    {
      size_t soname_len = strlen(st->arr + needed_buf_offsets->p[i]);
      if (((search_path_end + soname_len) + 1) >= path_end)
        continue;
      memcpy(search_path_end, st->arr + needed_buf_offsets->p[i], soname_len + 1);
      s->found_all_needed[depth] = (*needed_not_found) <= 1;
      int code = recurse(path, depth + 1, s, compat, reason);
      if (code == 28)
        exit_code = 28;
      if ((code == 0) || (code == 28))
      {
        size_t tmp = needed_buf_offsets->p[i];
        needed_buf_offsets->p[i] = needed_buf_offsets->p[(*needed_not_found) - 1];
        needed_buf_offsets->p[--(*needed_not_found)] = tmp;
      }
      else
      {
        ++i;
      }
    }

  }

  return exit_code;
}


/*** DEPENDENCIES:
struct compat_t
{
  char any;
  uint8_t class;
  uint16_t machine;
}
----------------------------
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
struct found_t
{
  how_t how;
  size_t depth;
}
----------------------------
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
None
----------------------------
***/


// element in merge of:  check_absolute_paths,check_search_paths,recurse
static int recurse(char *current_file, size_t depth, struct libtree_state_t *s, struct compat_t compat, struct found_t reason)
{
  FILE *fptr = fopen(current_file, "rb");
  if (fptr == 0)
  {
    return 31;
  }
  size_t old_buf_size = s->string_table.n;
  char e_ident[16];
  if (fread(&e_ident, 16, 1, fptr) != 1)
  {
    fclose(fptr);
    return 11;
  }
  if ((((e_ident[0] != 0x7f) || (e_ident[1] != 'E')) || (e_ident[2] != 'L')) || (e_ident[3] != 'F'))
  {
    fclose(fptr);
    return 11;
  }
  if ((e_ident[4] != 1) && (e_ident[4] != 2))
  {
    fclose(fptr);
    return 12;
  }
  if ((e_ident[5] != '\x01') && (e_ident[5] != '\x02'))
  {
    fclose(fptr);
    return 13;
  }
  struct compat_t curr_type = {.any = 0, .class = e_ident[4]};
  int is_little_endian = e_ident[5] == '\x01';
  if ((!compat.any) && (compat.class != curr_type.class))
  {
    fclose(fptr);
    return 15;
  }
  if (is_little_endian ^ host_is_little_endian())
  {
    fclose(fptr);
    return 16;
  }
  union 
  {
    struct header_64_t h64;
    struct header_32_t h32;
  } header;
  if (curr_type.class == 2)
  {
    if (fread(&header.h64, sizeof(struct header_64_t), 1, fptr) != 1)
    {
      fclose(fptr);
      return 14;
    }
    if ((header.h64.e_type != 2) && (header.h64.e_type != 3))
    {
      fclose(fptr);
      return 17;
    }
    curr_type.machine = header.h64.e_machine;
    if ((!compat.any) && (compat.machine != curr_type.machine))
    {
      fclose(fptr);
      return 32;
    }
    if (fseek(fptr, header.h64.e_phoff, 0) != 0)
    {
      fclose(fptr);
      return 18;
    }
  }
  else
  {
    if (fread(&header.h32, sizeof(struct header_32_t), 1, fptr) != 1)
    {
      fclose(fptr);
      return 14;
    }
    if ((header.h32.e_type != 2) && (header.h32.e_type != 3))
    {
      fclose(fptr);
      return 17;
    }
    curr_type.machine = header.h32.e_machine;
    if ((!compat.any) && (compat.machine != curr_type.machine))
    {
      fclose(fptr);
      return 32;
    }
    if (fseek(fptr, header.h32.e_phoff, 0) != 0)
    {
      fclose(fptr);
      return 18;
    }
  }
  union 
  {
    struct prog_64_t p64;
    struct prog_32_t p32;
  } prog;
  struct small_vec_u64_t pt_load_offset;
  struct small_vec_u64_t pt_load_vaddr;
  small_vec_u64_init(&pt_load_offset);
  small_vec_u64_init(&pt_load_vaddr);
  uint64_t p_offset = 0xFFFFFFFFFFFFFFFF;
  if (curr_type.class == 2)
  {
    for (uint64_t i = 0; i < header.h64.e_phnum; i += 1)
    {
      if (fread(&prog.p64, sizeof(struct prog_64_t), 1, fptr) != 1)
      {
        fclose(fptr);
        small_vec_u64_free(&pt_load_offset);
        small_vec_u64_free(&pt_load_vaddr);
        return 19;
      }
      if (prog.p64.p_type == 1)
      {
        small_vec_u64_append(&pt_load_offset, prog.p64.p_offset);
        small_vec_u64_append(&pt_load_vaddr, prog.p64.p_vaddr);
      }
      else
        if (prog.p64.p_type == 2)
      {
        p_offset = prog.p64.p_offset;
      }
    }

  }
  else
  {
    for (uint32_t i = 0; i < header.h32.e_phnum; i += 1)
    {
      if (fread(&prog.p32, sizeof(struct prog_32_t), 1, fptr) != 1)
      {
        fclose(fptr);
        small_vec_u64_free(&pt_load_offset);
        small_vec_u64_free(&pt_load_vaddr);
        return 19;
      }
      if (prog.p32.p_type == 1)
      {
        small_vec_u64_append(&pt_load_offset, prog.p32.p_offset);
        small_vec_u64_append(&pt_load_vaddr, prog.p32.p_vaddr);
      }
      else
        if (prog.p32.p_type == 2)
      {
        p_offset = prog.p32.p_offset;
      }
    }

  }
  struct stat finfo;
  if (stat(current_file, &finfo) != 0)
  {
    fclose(fptr);
    small_vec_u64_free(&pt_load_offset);
    small_vec_u64_free(&pt_load_vaddr);
    return 20;
  }
  int seen_before = visited_files_contains(&s->visited, &finfo);
  if (!seen_before)
  {
    visited_files_append(&s->visited, &finfo);
  }
  if (p_offset == 0xFFFFFFFFFFFFFFFF)
  {
    print_line(depth, current_file, "\033[1;36m", "\033[0;36m", 1, reason, s);
    fclose(fptr);
    small_vec_u64_free(&pt_load_offset);
    small_vec_u64_free(&pt_load_vaddr);
    return 0;
  }
  if (pt_load_offset.n == 0)
  {
    fclose(fptr);
    small_vec_u64_free(&pt_load_offset);
    small_vec_u64_free(&pt_load_vaddr);
    return 29;
  }
  if (fseek(fptr, p_offset, 0) != 0)
  {
    fclose(fptr);
    small_vec_u64_free(&pt_load_offset);
    small_vec_u64_free(&pt_load_vaddr);
    return 21;
  }
  int no_def_lib = 0;
  uint64_t strtab = 0xFFFFFFFFFFFFFFFF;
  uint64_t rpath = 0xFFFFFFFFFFFFFFFF;
  uint64_t runpath = 0xFFFFFFFFFFFFFFFF;
  uint64_t soname = 0xFFFFFFFFFFFFFFFF;
  struct small_vec_u64_t needed;
  small_vec_u64_init(&needed);
  for (int cont = 1; cont;)
  {
    helper_recurse_1(&no_def_lib, &strtab, &rpath, &runpath, &soname, &cont, fptr, curr_type, pt_load_offset, pt_load_vaddr, needed);
  }

  if (strtab == 0xFFFFFFFFFFFFFFFF)
  {
    fclose(fptr);
    small_vec_u64_free(&pt_load_offset);
    small_vec_u64_free(&pt_load_vaddr);
    small_vec_u64_free(&needed);
    return 23;
  }
  if (!is_ascending_order(pt_load_vaddr.p, pt_load_vaddr.n))
  {
    fclose(fptr);
    small_vec_u64_free(&pt_load_vaddr);
    small_vec_u64_free(&pt_load_offset);
    small_vec_u64_free(&needed);
    return 30;
  }
  size_t vaddr_idx = 0;
  while (((vaddr_idx + 1) != pt_load_vaddr.n) && (strtab >= pt_load_vaddr.p[vaddr_idx + 1]))
  {
    vaddr_idx += 1;
  }

  uint64_t strtab_offset = (pt_load_offset.p[vaddr_idx] + strtab) - pt_load_vaddr.p[vaddr_idx];
  small_vec_u64_free(&pt_load_vaddr);
  small_vec_u64_free(&pt_load_offset);
  size_t soname_buf_offset = s->string_table.n;
  if (soname != 0xFFFFFFFFFFFFFFFF)
  {
    if (fseek(fptr, strtab_offset + soname, 0) != 0)
    {
      s->string_table.n = old_buf_size;
      fclose(fptr);
      small_vec_u64_free(&needed);
      return 24;
    }
    string_table_copy_from_file(&s->string_table, fptr);
  }
  int in_exclude_list = (soname != 0xFFFFFFFFFFFFFFFF) && is_in_exclude_list(s->string_table.arr + soname_buf_offset);
  int should_recurse = (depth < s->max_depth) && ((((!seen_before) && (!in_exclude_list)) || (((!seen_before) && in_exclude_list) && (s->verbosity >= 2))) || (s->verbosity >= 3));
  if (!should_recurse)
  {
    char *print_name = ((soname == 0xFFFFFFFFFFFFFFFF) || s->path) ? (current_file) : (s->string_table.arr + soname_buf_offset);
    char *bold_color = (in_exclude_list) ? ("\033[0;35m") : ((seen_before) ? ("\033[0;34m") : ("\033[1;36m"));
    char *regular_color = (in_exclude_list) ? ("\033[0;35m") : ((seen_before) ? ("\033[0;34m") : ("\033[0;36m"));
    int highlight = (!seen_before) && (!in_exclude_list);
    print_line(depth, print_name, bold_color, regular_color, highlight, reason, s);
    s->string_table.n = old_buf_size;
    fclose(fptr);
    small_vec_u64_free(&needed);
    return 0;
  }
  char origin[4096];
  char *last_slash = strrchr(current_file, '/');
  if (last_slash != 0)
  {
    size_t bytes = last_slash - current_file;
    memcpy(origin, current_file, bytes);
    origin[bytes] = '\0';
  }
  else
  {
    memcpy(origin, "./", 3);
  }
  if (rpath == 0xFFFFFFFFFFFFFFFF)
  {
    s->rpath_offsets[depth] = SIZE_MAX;
  }
  else
  {
    s->rpath_offsets[depth] = s->string_table.n;
    if (fseek(fptr, strtab_offset + rpath, 0) != 0)
    {
      s->string_table.n = old_buf_size;
      fclose(fptr);
      small_vec_u64_free(&needed);
      return 25;
    }
    string_table_copy_from_file(&s->string_table, fptr);
    size_t curr_buf_size = s->string_table.n;
    if (interpolate_variables(s, s->rpath_offsets[depth], origin))
    {
      s->rpath_offsets[depth] = curr_buf_size;
    }
  }
  size_t runpath_buf_offset = s->string_table.n;
  if (runpath != 0xFFFFFFFFFFFFFFFF)
  {
    if (fseek(fptr, strtab_offset + runpath, 0) != 0)
    {
      s->string_table.n = old_buf_size;
      fclose(fptr);
      small_vec_u64_free(&needed);
      return 26;
    }
    string_table_copy_from_file(&s->string_table, fptr);
    size_t curr_buf_size = s->string_table.n;
    if (interpolate_variables(s, runpath_buf_offset, origin))
    {
      runpath_buf_offset = curr_buf_size;
    }
  }
  struct small_vec_u64_t needed_buf_offsets;
  small_vec_u64_init(&needed_buf_offsets);
  for (size_t i = 0; i < needed.n; i += 1)
  {
    small_vec_u64_append(&needed_buf_offsets, s->string_table.n);
    if (fseek(fptr, strtab_offset + needed.p[i], 0) != 0)
    {
      s->string_table.n = old_buf_size;
      fclose(fptr);
      small_vec_u64_free(&needed_buf_offsets);
      small_vec_u64_free(&needed);
      return 27;
    }
    string_table_copy_from_file(&s->string_table, fptr);
  }

  fclose(fptr);
  char *print_name = ((soname == 0xFFFFFFFFFFFFFFFF) || s->path) ? (current_file) : (s->string_table.arr + soname_buf_offset);
  char *bold_color = (in_exclude_list) ? ("\033[0;35m") : ((seen_before) ? ("\033[0;34m") : ("\033[1;36m"));
  char *regular_color = (in_exclude_list) ? ("\033[0;35m") : ((seen_before) ? ("\033[0;34m") : ("\033[0;36m"));
  int highlight = (!seen_before) && (!in_exclude_list);
  print_line(depth, print_name, bold_color, regular_color, highlight, reason, s);
  int exit_code = 0;
  size_t needed_not_found = needed_buf_offsets.n;
  if (needed_not_found && (s->verbosity == 0))
  {
    apply_exclude_list(&needed_not_found, &needed_buf_offsets, s);
  }
  if (needed_not_found)
  {
    exit_code |= check_absolute_paths(&needed_not_found, &needed_buf_offsets, depth, s, curr_type);
  }
  if (runpath == 0xFFFFFFFFFFFFFFFF)
  {
    for (int j = depth; (j >= 0) && needed_not_found; j -= 1)
    {
      if (s->rpath_offsets[j] == SIZE_MAX)
      {
        continue;
      }
      exit_code |= check_search_paths((struct found_t){.how = RPATH, .depth = j}, s->rpath_offsets[j], &needed_not_found, &needed_buf_offsets, depth, s, curr_type);
    }

  }
  if (needed_not_found && (s->ld_library_path_offset != SIZE_MAX))
  {
    exit_code |= check_search_paths((struct found_t){.how = LD_LIBRARY_PATH}, s->ld_library_path_offset, &needed_not_found, &needed_buf_offsets, depth, s, curr_type);
  }
  if (needed_not_found && (runpath != 0xFFFFFFFFFFFFFFFF))
  {
    exit_code |= check_search_paths((struct found_t){.how = RUNPATH}, runpath_buf_offset, &needed_not_found, &needed_buf_offsets, depth, s, curr_type);
  }
  if (needed_not_found && (!no_def_lib))
  {
    exit_code |= check_search_paths((struct found_t){.how = LD_SO_CONF}, s->ld_so_conf_offset, &needed_not_found, &needed_buf_offsets, depth, s, curr_type);
  }
  if (needed_not_found && (!no_def_lib))
  {
    exit_code |= check_search_paths((struct found_t){.how = DEFAULT}, s->default_paths_offset, &needed_not_found, &needed_buf_offsets, depth, s, curr_type);
  }
  if (needed_not_found)
  {
    print_error(depth, needed_not_found, &needed_buf_offsets, (runpath == 0xFFFFFFFFFFFFFFFF) ? (0) : (s->string_table.arr + runpath_buf_offset), s, no_def_lib);
    s->string_table.n = old_buf_size;
    small_vec_u64_free(&needed_buf_offsets);
    small_vec_u64_free(&needed);
    return 28;
  }
  s->string_table.n = old_buf_size;
  small_vec_u64_free(&needed_buf_offsets);
  small_vec_u64_free(&needed);
  return exit_code;
}


/*** DEPENDENCIES:
static void small_vec_u64_append(struct small_vec_u64_t *v, uint64_t val)
{
  if (v->n < 16)
  {
    v->p[v->n++] = val;
    return;
  }
  if (v->n == 16)
  {
    v->capacity = 2 * 16;
    v->p = malloc(v->capacity * (sizeof(uint64_t)));
    if (v->p == 0)
    {
      exit(1);
    }
    memcpy(v->p, v->buf, 16 * (sizeof(uint64_t)));
  }
  else
    if (v->n == v->capacity)
  {
    v->capacity *= 2;
    uint64_t *p = realloc(v->p, v->capacity * (sizeof(uint64_t)));
    if (p == 0)
    {
      exit(1);
    }
    v->p = p;
  }
  v->p[v->n++] = val;
}


----------------------------
struct header_64_t
{
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint64_t e_entry;
  uint64_t e_phoff;
  uint64_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
}
----------------------------
static void apply_exclude_list(size_t *needed_not_found, struct small_vec_u64_t *needed_buf_offsets, struct libtree_state_t *s)
{
  for (size_t i = 0; i < (*needed_not_found);)
  {
    if (is_in_exclude_list(s->string_table.arr + needed_buf_offsets->p[i]))
    {
      size_t tmp = needed_buf_offsets->p[i];
      needed_buf_offsets->p[i] = needed_buf_offsets->p[(*needed_not_found) - 1];
      needed_buf_offsets->p[--(*needed_not_found)] = tmp;
      continue;
    }
    else
    {
      i += 1;
    }
  }

}


----------------------------
static int interpolate_variables(struct libtree_state_t *s, size_t src, const char *ORIGIN)
{
  size_t prev_src = src;
  size_t curr_src = src;
  struct string_table_t *st = &s->string_table;
  while (1)
  {
    helper_interpolate_variables_1(&prev_src, &curr_src, s, ORIGIN, st);
  }

  if (prev_src != src)
  {
    size_t n = strlen(st->arr + prev_src) + 1;
    string_table_maybe_grow(st, n);
    memcpy(st->arr + st->n, st->arr + prev_src, n);
    st->n += n;
    return 1;
  }
  return 0;
}


----------------------------
static void visited_files_append(struct visited_file_array_t *files, struct stat *new)
{
  if (files->n == files->capacity)
  {
    files->capacity *= 2;
    files->arr = realloc(files->arr, files->capacity * (sizeof(struct visited_file_t)));
    if (files->arr == 0)
    {
      exit(1);
    }
  }
  files->arr[files->n].st_dev = new->st_dev;
  files->arr[files->n].st_ino = new->st_ino;
  files->n += 1;
}


----------------------------
static int is_in_exclude_list(char *soname)
{
  char *start = soname;
  char *end = strrchr(start, '\0');
  unsigned int end_idx = 0;
  if (start == (&end[end_idx]))
  {
    return 0;
  }
  end_idx -= 1;
  while (((&end[end_idx]) != start) && (((end[end_idx] >= '0') && (end[end_idx] <= '9')) || (end[end_idx] == '.')))
  {
    end_idx -= 1;
  }

  for (size_t j = 0; j < ((sizeof(exclude_list)) / (sizeof(char *))); j += 1)
  {
    size_t len = strlen(exclude_list[j]);
    if (strncmp(start, exclude_list[j], len) != 0)
    {
      continue;
    }
    return 1;
  }

  return 0;
}


----------------------------
inline static int host_is_little_endian()
{
  int test = 1;
  char *bytes = (char *) (&test);
  return bytes[0] == 1;
}


----------------------------
struct compat_t
{
  char any;
  uint8_t class;
  uint16_t machine;
}
----------------------------
static void small_vec_u64_free(struct small_vec_u64_t *v)
{
  if (v->n <= 16)
  {
    return;
  }
  free(v->p);
  v->p = 0;
}


----------------------------
int helper_recurse_1(int * const no_def_lib_ref, uint64_t * const strtab_ref, uint64_t * const rpath_ref, uint64_t * const runpath_ref, uint64_t * const soname_ref, int * const cont_ref, FILE * const fptr, struct compat_t curr_type, struct small_vec_u64_t pt_load_offset, struct small_vec_u64_t pt_load_vaddr, struct small_vec_u64_t needed)
{
  int no_def_lib = *no_def_lib_ref;
  uint64_t strtab = *strtab_ref;
  uint64_t rpath = *rpath_ref;
  uint64_t runpath = *runpath_ref;
  uint64_t soname = *soname_ref;
  int cont = *cont_ref;
  uint64_t d_tag;
  uint64_t d_val;
  if (curr_type.class == 2)
  {
    struct dyn_64_t dyn;
    if (fread(&dyn, sizeof(struct dyn_64_t), 1, fptr) != 1)
    {
      fclose(fptr);
      small_vec_u64_free(&pt_load_offset);
      small_vec_u64_free(&pt_load_vaddr);
      small_vec_u64_free(&needed);
      return 22;
    }
    d_tag = dyn.d_tag;
    d_val = dyn.d_val;
  }
  else
  {
    struct dyn_32_t dyn;
    if (fread(&dyn, sizeof(struct dyn_32_t), 1, fptr) != 1)
    {
      fclose(fptr);
      small_vec_u64_free(&pt_load_offset);
      small_vec_u64_free(&pt_load_vaddr);
      small_vec_u64_free(&needed);
      return 22;
    }
    d_tag = dyn.d_tag;
    d_val = dyn.d_val;
  }
  switch (d_tag)
  {
    case 0:
    {
      cont = 0;
      break;
    }

    case 5:
    {
      strtab = d_val;
      break;
    }

    case 15:
    {
      rpath = d_val;
      break;
    }

    case 29:
    {
      runpath = d_val;
      break;
    }

    case 1:
    {
      small_vec_u64_append(&needed, d_val);
      break;
    }

    case 14:
    {
      soname = d_val;
      break;
    }

    case 0x6ffffffb:
    {
      no_def_lib |= (0x800 & d_val) == 0x800;
      break;
    }

  }

  *no_def_lib_ref = no_def_lib;
  *strtab_ref = strtab;
  *rpath_ref = rpath;
  *runpath_ref = runpath;
  *soname_ref = soname;
  *cont_ref = cont;
}


----------------------------
struct prog_64_t
{
  uint32_t p_type;
  uint32_t p_flags;
  uint64_t p_offset;
  uint64_t p_vaddr;
  uint64_t p_paddr;
  uint64_t p_filesz;
  uint64_t p_memsz;
  uint64_t p_align;
}
----------------------------
struct header_32_t
{
  uint16_t e_type;
  uint16_t e_machine;
  uint32_t e_version;
  uint32_t e_entry;
  uint32_t e_phoff;
  uint32_t e_shoff;
  uint32_t e_flags;
  uint16_t e_ehsize;
  uint16_t e_phentsize;
  uint16_t e_phnum;
  uint16_t e_shentsize;
  uint16_t e_shnum;
  uint16_t e_shstrndx;
}
----------------------------
static int visited_files_contains(struct visited_file_array_t *files, struct stat *needle)
{
  for (size_t i = 0; i < files->n; i += 1)
  {
    struct visited_file_t *f = &files->arr[i];
    if ((f->st_dev == needle->st_dev) && (f->st_ino == needle->st_ino))
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
static void print_error(size_t depth, size_t needed_not_found, struct small_vec_u64_t *needed_buf_offsets, char *runpath, struct libtree_state_t *s, int no_def_lib)
{
  for (size_t i = 0; i < needed_not_found; i += 1)
  {
    s->found_all_needed[depth] = (i + 1) >= needed_not_found;
    tree_preamble(s, depth + 1);
    if (s->color)
    {
      fputs("\033[1;31m", stdout);
    }
    fputs(s->string_table.arr + needed_buf_offsets->p[i], stdout);
    fputs(" not found\n", stdout);
    if (s->color)
    {
      fputs("\033[0m", stdout);
    }
  }

  char *box_vertical = (s->color) ? ("    \033[0;31m\xe2\x94\x8a\033[0m") : ("    \xe2\x94\x8a");
  char *indent = malloc((((sizeof("\xe2\x94\x82   ")) * depth) + strlen(box_vertical)) + 1);
  char *p = indent;
  unsigned int p_idx = 0;
  for (size_t i = 0; i < depth; i += 1)
  {
    if (s->found_all_needed[i])
    {
      int len = (sizeof("    ")) - 1;
      memcpy(p, "    ", len);
      p_idx += len;
    }
    else
    {
      int len = (sizeof("\xe2\x94\x82   ")) - 1;
      memcpy(p, "\xe2\x94\x82   ", len);
      p_idx += len;
    }
  }

  strcpy(p, box_vertical);
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs(" Paths considered in this order:\n", stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  fputs(indent, stdout);
  if (runpath != 0)
  {
    if (s->color)
    {
      fputs("\033[0;90m", stdout);
    }
    fputs(" 1. rpath is skipped because runpath was set\n", stdout);
    if (s->color)
    {
      fputs("\033[0m", stdout);
    }
  }
  else
  {
    helper_print_error_1(depth, s, indent);
  }
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((s->ld_library_path_offset == SIZE_MAX) ? (" 2. LD_LIBRARY_PATH was not set\n") : (" 2. LD_LIBRARY_PATH:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  if (s->ld_library_path_offset != SIZE_MAX)
  {
    print_colon_delimited_paths(s->string_table.arr + s->ld_library_path_offset, indent);
  }
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((runpath == 0) ? (" 3. runpath was not set\n") : (" 3. runpath:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  if (runpath != 0)
  {
    print_colon_delimited_paths(runpath, indent);
  }
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((no_def_lib) ? (" 4. ld config files not considered due to NODEFLIB flag\n") : (" 4. ld config files:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  print_colon_delimited_paths(s->string_table.arr + s->ld_so_conf_offset, indent);
  fputs(indent, stdout);
  if (s->color)
  {
    fputs("\033[0;90m", stdout);
  }
  fputs((no_def_lib) ? (" 5. Standard paths not considered due to NODEFLIB flag\n") : (" 5. Standard paths:\n"), stdout);
  if (s->color)
  {
    fputs("\033[0m", stdout);
  }
  print_colon_delimited_paths(s->string_table.arr + s->default_paths_offset, indent);
  free(indent);
}


----------------------------
static void string_table_copy_from_file(struct string_table_t *t, FILE *fptr)
{
  int c;
  while (((c = getc(fptr)) != '\0') && (c != EOF))
  {
    string_table_maybe_grow(t, 1);
    t->arr[t->n++] = c;
  }

  string_table_maybe_grow(t, 1);
  t->arr[t->n++] = '\0';
}


----------------------------
inline static void small_vec_u64_init(struct small_vec_u64_t *v)
{
  memset(v, 0, sizeof(*v));
  v->p = v->buf;
}


----------------------------
struct found_t
{
  how_t how;
  size_t depth;
}
----------------------------
struct small_vec_u64_t
{
  uint64_t buf[16];
  uint64_t *p;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
struct prog_32_t
{
  uint32_t p_type;
  uint32_t p_offset;
  uint32_t p_vaddr;
  uint32_t p_paddr;
  uint32_t p_filesz;
  uint32_t p_memsz;
  uint32_t p_flags;
  uint32_t p_align;
}
----------------------------
static void print_line(size_t depth, char *name, char *color_bold, char *color_regular, int highlight, struct found_t reason, struct libtree_state_t *s)
{
  tree_preamble(s, depth);
  char *slash = 0;
  unsigned int slash_idx = 0;
  if ((s->color && highlight) && ((slash_idx = strrchr(name, '/')) != 0))
  {
    fputs(color_regular, stdout);
    fwrite(name, 1, ((&slash[slash_idx]) + 1) - name, stdout);
    fputs(color_bold, stdout);
    fputs((&slash[slash_idx]) + 1, stdout);
  }
  else
  {
    if (s->color)
    {
      fputs(color_bold, stdout);
    }
    fputs(name, stdout);
  }
  if (s->color && highlight)
  {
    fputs("\033[0m \033[33m", stdout);
  }
  else
    putchar(' ');
  switch (reason.how)
  {
    case RPATH:
    {
      if ((reason.depth + 1) >= depth)
      {
        fputs("[rpath]", stdout);
      }
      else
      {
        char num[8];
        utoa(num, reason.depth + 1);
        fputs("[rpath of ", stdout);
        fputs(num, stdout);
        putchar(']');
      }
      break;
    }

    case LD_LIBRARY_PATH:
    {
      fputs("[LD_LIBRARY_PATH]", stdout);
      break;
    }

    case RUNPATH:
    {
      fputs("[runpath]", stdout);
      break;
    }

    case LD_SO_CONF:
    {
      putchar('[');
      char *conf_name = strrchr(s->ld_conf_file, '/');
      conf_name_idx = (conf_name_idx == 0) ? (s->ld_conf_file) : (conf_name_idx + 1);
      fputs(conf_name, stdout);
      putchar(']');
      break;
    }

    unsigned int conf_name_idx = 0;
    case DIRECT:
    {
      fputs("[direct]", stdout);
      break;
    }

    case DEFAULT:
    {
      fputs("[default path]", stdout);
      break;
    }

    default:
    {
      break;
    }

  }

  if (s->color)
  {
    fputs("\033[0m\n", stdout);
  }
  else
    putchar('\n');
}


----------------------------
static int is_ascending_order(uint64_t *v, size_t n)
{
  for (size_t j = 1; j < n; j += 1)
    if (v[j - 1] >= v[j])
  {
    return 0;
  }

  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['exit_code_ref is a mutable refrence to int']
void helper_print_tree_1(int * const exit_code_ref, char ** const pathv, struct libtree_state_t * const s, int i)
{
  int exit_code = *exit_code_ref;
  int code = recurse(pathv[i], 0, s, (struct compat_t){.any = 1}, (struct found_t){.how = INPUT});
  fflush(stdout);
  if (code != 0)
  {
    exit_code = code;
    fputs("Error [", stderr);
    fputs(pathv[i], stderr);
    fputs("]: ", stderr);
  }
  char *msg = 0;
  unsigned int msg_idx = 0;
  switch (code)
  {
    case 11:
    {
      msg_idx = "Invalid ELF magic bytes\n";
      break;
    }

    case 12:
    {
      msg_idx = "Invalid ELF class\n";
      break;
    }

    case 13:
    {
      msg_idx = "Invalid ELF data\n";
      break;
    }

    case 14:
    {
      msg_idx = "Invalid ELF header\n";
      break;
    }

    case 15:
    {
      msg_idx = "Invalid bits\n";
      break;
    }

    case 16:
    {
      msg_idx = "Invalid endianness\n";
      break;
    }

    case 17:
    {
      msg_idx = "Not an ET_EXEC or ET_DYN ELF file\n";
      break;
    }

    case 18:
    {
      msg_idx = "Invalid ELF program header offset\n";
      break;
    }

    case 19:
    {
      msg_idx = "Invalid ELF program header\n";
      break;
    }

    case 20:
    {
      msg_idx = "Can't stat file\n";
      break;
    }

    case 21:
    {
      msg_idx = "Invalid ELF dynamic section\n";
      break;
    }

    case 22:
    {
      msg_idx = "Invalid ELF dynamic array entry\n";
      break;
    }

    case 23:
    {
      msg_idx = "No ELF string table found\n";
      break;
    }

    case 24:
    {
      msg_idx = "Can't read DT_SONAME\n";
      break;
    }

    case 25:
    {
      msg_idx = "Can't read DT_RPATH\n";
      break;
    }

    case 26:
    {
      msg_idx = "Can't read DT_RUNPATH\n";
      break;
    }

    case 27:
    {
      msg_idx = "Can't read DT_NEEDED\n";
      break;
    }

    case 28:
    {
      msg_idx = "Not all dependencies were found\n";
      break;
    }

    case 29:
    {
      msg_idx = "No PT_LOAD found in ELF file\n";
      break;
    }

    case 30:
    {
      msg_idx = "Virtual addresses are not ordered\n";
      break;
    }

    case 31:
    {
      msg_idx = "Could not open file\n";
      break;
    }

    case 32:
    {
      msg_idx = "Incompatible ISA\n";
      break;
    }

  }

  if ((&msg[msg_idx]) != 0)
  {
    fputs(msg, stderr);
  }
  fflush(stderr);
  *exit_code_ref = exit_code;
}


/*** DEPENDENCIES:
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
None
----------------------------
***/


int helper_main_1(struct libtree_state_t s, int opt_help)
{
  fputs("Show the dynamic dependency tree of ELF files\nUsage: libtree [OPTION]... [--] FILE [FILES]...\n\n  -h, --help     Print help info\n      --version  Print version info\n\nFile names starting with '-', for example '-.so', can be specified as follows:\n  libtree -- -.so\n\nLocating libs options:\n  -p, --path       Show the path of libraries instead of the soname\n  -v               Show libraries skipped by default*\n  -vv              Show dependencies of libraries skipped by default*\n  -vvv             Show dependencies of already encountered libraries\n  --ldconf <path>  Config file for extra search paths [", stdout);
  fputs(s.ld_conf_file, stdout);
  fputs("]\n  --max-depth <n>  Limit library traversal to at most n levels of depth\n\n* For brevity, the following libraries are not shown by default:\n  ", stdout);
  size_t num_excluded = (sizeof(exclude_list)) / (sizeof(char *));
  size_t cursor_x = 3;
  for (size_t j = 0; j < num_excluded; j += 1)
  {
    cursor_x += strlen(exclude_list[j]);
    if (cursor_x > 60)
    {
      cursor_x = 3;
      fputs("\n  ", stdout);
    }
    fputs(exclude_list[j], stdout);
    if ((j + 1) != num_excluded)
    {
      fputs(", ", stdout);
    }
  }

  fputs(".\n\nThe following rpath/runpath substitutions are used:\n", stdout);
  fputs("  PLATFORM       ", stdout);
  fputs(s.PLATFORM, stdout);
  fputs("\n  LIB            ", stdout);
  fputs(s.LIB, stdout);
  fputs("\n  OSNAME         ", stdout);
  fputs(s.OSNAME, stdout);
  fputs("\n  OSREL          ", stdout);
  fputs(s.OSREL, stdout);
  putchar('\n');
  return !opt_help;
}


/*** DEPENDENCIES:
const char *exclude_list[] = {"ld-linux-aarch64.so", "ld-linux-armhf.so", "ld-linux-x86-64.so", "ld-linux.so", "ld64.so", "libc.musl-aarch64.so", "libc.musl-armhf.so", "libc.musl-i386.so", "libc.musl-x86_64.so", "libc.so", "libdl.so", "libgcc_s.so", "libm.so", "libstdc++.so"}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


// hint:  ['argv_idx_ref is a mutable refrence to unsigned int', 's_ref is a mutable refrence to ', 'positional_ref is a mutable refrence to int', 'opt_help_ref is a mutable refrence to int', 'opt_version_ref is a mutable refrence to int', 'opt_raw_ref is a mutable refrence to int', 'i_ref is a mutable refrence to int']
int helper_main_2(unsigned int * const argv_idx_ref, struct libtree_state_t * const s_ref, int * const positional_ref, int * const opt_help_ref, int * const opt_version_ref, int * const opt_raw_ref, int * const i_ref, int argc, char ** const argv)
{
  unsigned int argv_idx = *argv_idx_ref;
  struct libtree_state_t s = *s_ref;
  int positional = *positional_ref;
  int opt_help = *opt_help_ref;
  int opt_version = *opt_version_ref;
  int opt_raw = *opt_raw_ref;
  int i = *i_ref;
  char *arg = argv[i + argv_idx];
  unsigned int arg_idx = 0;
  if ((opt_raw || (arg[arg_idx] != '-')) || (arg[1 + arg_idx] == '\0'))
  {
    argv[positional + argv_idx] = &arg[arg_idx];
    positional += 1;
    continue;
  }
  arg_idx += 1;
  if (arg[arg_idx] == '-')
  {
    helper_helper_main_2_1(&s, &opt_help, &opt_version, &opt_raw, &i, &arg_idx, argc, argv, argv_idx, arg);
  }
  for (; arg[arg_idx] != '\0'; arg_idx += 1)
  {
    switch (arg[arg_idx])
    {
      case 'h':
      {
        opt_help = 1;
        break;
      }

      case 'p':
      {
        s.path = 1;
        break;
      }

      case 'v':
      {
        s.verbosity += 1;
        break;
      }

      default:
      {
        fputs("Unrecognized flag `-", stderr);
        fputs(arg, stderr);
        fputs("`\n", stderr);
        return 1;
      }

    }

  }

  *argv_idx_ref = argv_idx;
  *s_ref = s;
  *positional_ref = positional;
  *opt_help_ref = opt_help;
  *opt_version_ref = opt_version;
  *opt_raw_ref = opt_raw;
  *i_ref = i;
}


/*** DEPENDENCIES:
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
int helper_helper_main_2_1(struct libtree_state_t * const s_ref, int * const opt_help_ref, int * const opt_version_ref, int * const opt_raw_ref, int * const i_ref, unsigned int * const arg_idx_ref, int argc, char ** const argv, unsigned int argv_idx, char * const arg)
{
  struct libtree_state_t s = *s_ref;
  int opt_help = *opt_help_ref;
  int opt_version = *opt_version_ref;
  int opt_raw = *opt_raw_ref;
  int i = *i_ref;
  unsigned int arg_idx = *arg_idx_ref;
  arg_idx += 1;
  if (arg[arg_idx] == '\0')
  {
    opt_raw = 1;
    continue;
  }
  if (strcmp(arg, "version") == 0)
  {
    opt_version = 1;
  }
  else
    if (strcmp(arg, "path") == 0)
  {
    s.path = 1;
  }
  else
    if (strcmp(arg, "verbose") == 0)
  {
    s.verbosity += 1;
  }
  else
    if (strcmp(arg, "help") == 0)
  {
    opt_help = 1;
  }
  else
    if (strcmp(arg, "ldconf") == 0)
  {
    if ((i + 1) == argc)
    {
      fputs("Expected value after `--ldconf`\n", stderr);
      return 1;
    }
    i += 1;
    s.ld_conf_file = argv[i + argv_idx];
  }
  else
    if (strcmp(arg, "max-depth") == 0)
  {
    if ((i + 1) == argc)
    {
      fputs("Expected value after `--max-depth`\n", stderr);
      return 1;
    }
    char *ptr;
    i += 1;
    s.max_depth = strtoul(argv[i + argv_idx], &ptr, 10);
    if (s.max_depth > 32)
      s.max_depth = 32;
  }
  else
  {
    fputs("Unrecognized flag `--", stderr);
    fputs(arg, stderr);
    fputs("`\n", stderr);
    return 1;
  }
  continue;
  *s_ref = s;
  *opt_help_ref = opt_help;
  *opt_version_ref = opt_version;
  *opt_raw_ref = opt_raw;
  *i_ref = i;
  *arg_idx_ref = arg_idx;
}


----------------------------
***/


// element in merge of:  ld_conf_globbing,parse_ld_config_file,helper_helper_parse_ld_config_file_1_1,helper_parse_ld_config_file_1
static int ld_conf_globbing(struct string_table_t *st, char *pattern)
{
  glob_t result;
  memset(&result, 0, sizeof(result));
  int status = glob(pattern, 0, 0, &result);
  switch (status)
  {
    case GLOB_NOSPACE:

    case GLOB_ABORTED:
    {
      globfree(&result);
      return 1;
    }

    case GLOB_NOMATCH:
    {
      globfree(&result);
      return 0;
    }

  }

  int code = 0;
  for (size_t i = 0; i < result.gl_pathc; i += 1)
    code |= parse_ld_config_file(st, result.gl_pathv[i]);

  globfree(&result);
  return code;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
typedef struct 
{
} glob_t
----------------------------
None
----------------------------
***/


// element in merge of:  ld_conf_globbing,parse_ld_config_file,helper_helper_parse_ld_config_file_1_1,helper_parse_ld_config_file_1
static int parse_ld_config_file(struct string_table_t *st, char *path)
{
  FILE *fptr = fopen(path, "r");
  if (fptr == 0)
  {
    return 1;
  }
  int c = 0;
  char line[4096];
  char tmp[4096];
  while (c != EOF)
  {
    helper_parse_ld_config_file_1(&c, st, path, fptr, line, tmp);
  }

  fclose(fptr);
  return 0;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
None
----------------------------
***/


// element in merge of:  ld_conf_globbing,parse_ld_config_file,helper_helper_parse_ld_config_file_1_1,helper_parse_ld_config_file_1
// hint:  ['begin_idx_ref is a mutable refrence to unsigned int']
void helper_helper_parse_ld_config_file_1_1(unsigned int * const begin_idx_ref, struct string_table_t * const st, char * const path, char tmp[4096], char * const begin, char * const end)
{
  unsigned int begin_idx = *begin_idx_ref;
  begin_idx += 8;
  begin_idx += 1;
  begin_idx += 1;
  begin_idx += 1;
  while (isspace(*(&begin[begin_idx])))
    ++(&begin[begin_idx]);

  if (begin[begin_idx] != '/')
  {
    char *wd = strrchr(path, '/');
    unsigned int wd_idx = 0;
    wd_idx = (wd_idx == 0) ? (strrchr(path, '\0')) : (wd_idx);
    size_t wd_len = (&wd[wd_idx]) - path;
    size_t include_len = (end - (&begin[begin_idx])) + 1;
    if (((wd_len + 1) + include_len) >= 4096)
      continue;
    memcpy(tmp, path, wd_len);
    tmp[wd_len] = '/';
    memcpy((tmp + wd_len) + 1, begin, include_len);
    tmp[(wd_len + 1) + include_len] = '\0';
    begin_idx = tmp;
  }
  ld_conf_globbing(st, begin);
  *begin_idx_ref = begin_idx;
}


/*** DEPENDENCIES:
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
None
----------------------------
***/


// element in merge of:  ld_conf_globbing,parse_ld_config_file,helper_helper_parse_ld_config_file_1_1,helper_parse_ld_config_file_1
// hint:  ['c_ref is a mutable refrence to int']
void helper_parse_ld_config_file_1(int * const c_ref, struct string_table_t * const st, char * const path, FILE * const fptr, char line[4096], char tmp[4096])
{
  int c = *c_ref;
  size_t line_len = 0;
  while (((c = getc(fptr)) != '\n') && (c != EOF))
  {
    if (line_len < (4096 - 1))
    {
      line[line_len] = c;
      line_len += 1;
    }
  }

  line[line_len] = '\0';
  char *begin = line;
  unsigned int begin_idx = 0;
  char *end = line + line_len;
  for (; isspace(*(&begin[begin_idx])); begin_idx += 1)
  {
  }

  char *comment = strchr(begin, '#');
  if (comment != 0)
  {
    *comment = '\0';
  }
  while (end != (&begin[begin_idx]))
    if (!isspace(*(--end)))
  {
    break;
  }

  if ((&begin[begin_idx]) == end)
  {
    continue;
  }
  end[1] = '\0';
  if ((strncmp(begin, "include", 7) == 0) && isspace(begin[7 + begin_idx]))
  {
    helper_helper_parse_ld_config_file_1_1(&begin_idx, st, path, tmp, begin, end);
  }
  else
  {
    string_table_store(st, begin);
    st->arr[st->n - 1] = ':';
  }
  *c_ref = c;
}


/*** DEPENDENCIES:
static void string_table_store(struct string_table_t *t, const char *str)
{
  size_t n = strlen(str) + 1;
  string_table_maybe_grow(t, n);
  memcpy(t->arr + t->n, str, n);
  t->n += n;
}


----------------------------
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
None
----------------------------
***/


static void parse_ld_so_conf(struct libtree_state_t *s)
{
  struct string_table_t *st = &s->string_table;
  s->ld_so_conf_offset = st->n;
  parse_ld_config_file(st, s->ld_conf_file);
  if (st->n > s->ld_so_conf_offset)
  {
    st->arr[st->n - 1] = '\0';
  }
  else
  {
    string_table_store(st, "");
  }
}


/*** DEPENDENCIES:
static void string_table_store(struct string_table_t *t, const char *str)
{
  size_t n = strlen(str) + 1;
  string_table_maybe_grow(t, n);
  memcpy(t->arr + t->n, str, n);
  t->n += n;
}


----------------------------
struct string_table_t
{
  char *arr;
  size_t n;
  size_t capacity;
}
----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
None
----------------------------
***/


static int print_tree(int pathc, char **pathv, struct libtree_state_t *s)
{
  libtree_state_init(s);
  parse_ld_so_conf(s);
  parse_ld_library_path(s);
  set_default_paths(s);
  int exit_code = 0;
  for (int i = 0; i < pathc; i += 1)
  {
    helper_print_tree_1(&exit_code, pathv, s, i);
  }

  libtree_state_free(s);
  return exit_code;
}


/*** DEPENDENCIES:
void helper_print_tree_1(int * const exit_code_ref, char ** const pathv, struct libtree_state_t * const s, int i)
{
  int exit_code = *exit_code_ref;
  int code = recurse(pathv[i], 0, s, (struct compat_t){.any = 1}, (struct found_t){.how = INPUT});
  fflush(stdout);
  if (code != 0)
  {
    exit_code = code;
    fputs("Error [", stderr);
    fputs(pathv[i], stderr);
    fputs("]: ", stderr);
  }
  char *msg = 0;
  unsigned int msg_idx = 0;
  switch (code)
  {
    case 11:
    {
      msg_idx = "Invalid ELF magic bytes\n";
      break;
    }

    case 12:
    {
      msg_idx = "Invalid ELF class\n";
      break;
    }

    case 13:
    {
      msg_idx = "Invalid ELF data\n";
      break;
    }

    case 14:
    {
      msg_idx = "Invalid ELF header\n";
      break;
    }

    case 15:
    {
      msg_idx = "Invalid bits\n";
      break;
    }

    case 16:
    {
      msg_idx = "Invalid endianness\n";
      break;
    }

    case 17:
    {
      msg_idx = "Not an ET_EXEC or ET_DYN ELF file\n";
      break;
    }

    case 18:
    {
      msg_idx = "Invalid ELF program header offset\n";
      break;
    }

    case 19:
    {
      msg_idx = "Invalid ELF program header\n";
      break;
    }

    case 20:
    {
      msg_idx = "Can't stat file\n";
      break;
    }

    case 21:
    {
      msg_idx = "Invalid ELF dynamic section\n";
      break;
    }

    case 22:
    {
      msg_idx = "Invalid ELF dynamic array entry\n";
      break;
    }

    case 23:
    {
      msg_idx = "No ELF string table found\n";
      break;
    }

    case 24:
    {
      msg_idx = "Can't read DT_SONAME\n";
      break;
    }

    case 25:
    {
      msg_idx = "Can't read DT_RPATH\n";
      break;
    }

    case 26:
    {
      msg_idx = "Can't read DT_RUNPATH\n";
      break;
    }

    case 27:
    {
      msg_idx = "Can't read DT_NEEDED\n";
      break;
    }

    case 28:
    {
      msg_idx = "Not all dependencies were found\n";
      break;
    }

    case 29:
    {
      msg_idx = "No PT_LOAD found in ELF file\n";
      break;
    }

    case 30:
    {
      msg_idx = "Virtual addresses are not ordered\n";
      break;
    }

    case 31:
    {
      msg_idx = "Could not open file\n";
      break;
    }

    case 32:
    {
      msg_idx = "Incompatible ISA\n";
      break;
    }

  }

  if ((&msg[msg_idx]) != 0)
  {
    fputs(msg, stderr);
  }
  fflush(stderr);
  *exit_code_ref = exit_code;
}


----------------------------
static void parse_ld_so_conf(struct libtree_state_t *s)
{
  struct string_table_t *st = &s->string_table;
  s->ld_so_conf_offset = st->n;
  parse_ld_config_file(st, s->ld_conf_file);
  if (st->n > s->ld_so_conf_offset)
  {
    st->arr[st->n - 1] = '\0';
  }
  else
  {
    string_table_store(st, "");
  }
}


----------------------------
static void libtree_state_free(struct libtree_state_t *s)
{
  free(s->string_table.arr);
  free(s->visited.arr);
}


----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
static void set_default_paths(struct libtree_state_t *s)
{
  s->default_paths_offset = s->string_table.n;
  string_table_store(&s->string_table, "/lib:/lib64:/usr/lib:/usr/lib64");
}


----------------------------
static void libtree_state_init(struct libtree_state_t *s)
{
  s->string_table.n = 0;
  s->string_table.capacity = 1024;
  s->string_table.arr = malloc(s->string_table.capacity * (sizeof(char)));
  s->visited.n = 0;
  s->visited.capacity = 256;
  s->visited.arr = malloc(s->visited.capacity * (sizeof(struct visited_file_t)));
}


----------------------------
static void parse_ld_library_path(struct libtree_state_t *s)
{
  s->ld_library_path_offset = SIZE_MAX;
  char *val = getenv("LD_LIBRARY_PATH");
  if (val == 0)
  {
    return;
  }
  s->ld_library_path_offset = s->string_table.n;
  string_table_store(&s->string_table, val);
  char *search = s->string_table.arr + s->ld_library_path_offset;
  unsigned int search_idx = 0;
  while ((search_idx = strchr(search_idx, ';')) != 0)
    search[search_idx] = ':';

  search_idx += 1;
}


----------------------------
***/


int main(int argc, char **argv)
{
  unsigned int argv_idx = 0;
  struct libtree_state_t s;
  s.color = (getenv("NO_COLOR") == 0) && isatty(STDOUT_FILENO);
  s.verbosity = 0;
  s.path = 0;
  s.max_depth = 32;
  int positional = 1;
  struct utsname uname_val;
  if (uname(&uname_val) != 0)
  {
    return 1;
  }
  s.PLATFORM = uname_val.machine;
  s.OSNAME = uname_val.sysname;
  s.OSREL = uname_val.release;
  s.ld_conf_file = "/etc/ld.so.conf";
  if (strcmp(uname_val.sysname, "FreeBSD") == 0)
  {
    s.ld_conf_file = "/etc/ld-elf.so.conf";
  }
  s.LIB = "lib";
  int opt_help = 0;
  int opt_version = 0;
  int opt_raw = 0;
  for (int i = 1; i < argc; i += 1)
  {
    helper_main_2(&argv_idx, &s, &positional, &opt_help, &opt_version, &opt_raw, &i, argc, argv);
  }

  argv_idx += 1;
  positional -= 1;
  if (opt_help || ((!opt_version) && (positional == 0)))
  {
    helper_main_1(s, opt_help);
  }
  if (opt_version)
  {
    puts("3.1.1");
    return 0;
  }
  return print_tree(positional, argv, &s);
}


/*** DEPENDENCIES:
int helper_main_2(unsigned int * const argv_idx_ref, struct libtree_state_t * const s_ref, int * const positional_ref, int * const opt_help_ref, int * const opt_version_ref, int * const opt_raw_ref, int * const i_ref, int argc, char ** const argv)
{
  unsigned int argv_idx = *argv_idx_ref;
  struct libtree_state_t s = *s_ref;
  int positional = *positional_ref;
  int opt_help = *opt_help_ref;
  int opt_version = *opt_version_ref;
  int opt_raw = *opt_raw_ref;
  int i = *i_ref;
  char *arg = argv[i + argv_idx];
  unsigned int arg_idx = 0;
  if ((opt_raw || (arg[arg_idx] != '-')) || (arg[1 + arg_idx] == '\0'))
  {
    argv[positional + argv_idx] = &arg[arg_idx];
    positional += 1;
    continue;
  }
  arg_idx += 1;
  if (arg[arg_idx] == '-')
  {
    helper_helper_main_2_1(&s, &opt_help, &opt_version, &opt_raw, &i, &arg_idx, argc, argv, argv_idx, arg);
  }
  for (; arg[arg_idx] != '\0'; arg_idx += 1)
  {
    switch (arg[arg_idx])
    {
      case 'h':
      {
        opt_help = 1;
        break;
      }

      case 'p':
      {
        s.path = 1;
        break;
      }

      case 'v':
      {
        s.verbosity += 1;
        break;
      }

      default:
      {
        fputs("Unrecognized flag `-", stderr);
        fputs(arg, stderr);
        fputs("`\n", stderr);
        return 1;
      }

    }

  }

  *argv_idx_ref = argv_idx;
  *s_ref = s;
  *positional_ref = positional;
  *opt_help_ref = opt_help;
  *opt_version_ref = opt_version;
  *opt_raw_ref = opt_raw;
  *i_ref = i;
}


----------------------------
int helper_main_1(struct libtree_state_t s, int opt_help)
{
  fputs("Show the dynamic dependency tree of ELF files\nUsage: libtree [OPTION]... [--] FILE [FILES]...\n\n  -h, --help     Print help info\n      --version  Print version info\n\nFile names starting with '-', for example '-.so', can be specified as follows:\n  libtree -- -.so\n\nLocating libs options:\n  -p, --path       Show the path of libraries instead of the soname\n  -v               Show libraries skipped by default*\n  -vv              Show dependencies of libraries skipped by default*\n  -vvv             Show dependencies of already encountered libraries\n  --ldconf <path>  Config file for extra search paths [", stdout);
  fputs(s.ld_conf_file, stdout);
  fputs("]\n  --max-depth <n>  Limit library traversal to at most n levels of depth\n\n* For brevity, the following libraries are not shown by default:\n  ", stdout);
  size_t num_excluded = (sizeof(exclude_list)) / (sizeof(char *));
  size_t cursor_x = 3;
  for (size_t j = 0; j < num_excluded; j += 1)
  {
    cursor_x += strlen(exclude_list[j]);
    if (cursor_x > 60)
    {
      cursor_x = 3;
      fputs("\n  ", stdout);
    }
    fputs(exclude_list[j], stdout);
    if ((j + 1) != num_excluded)
    {
      fputs(", ", stdout);
    }
  }

  fputs(".\n\nThe following rpath/runpath substitutions are used:\n", stdout);
  fputs("  PLATFORM       ", stdout);
  fputs(s.PLATFORM, stdout);
  fputs("\n  LIB            ", stdout);
  fputs(s.LIB, stdout);
  fputs("\n  OSNAME         ", stdout);
  fputs(s.OSNAME, stdout);
  fputs("\n  OSREL          ", stdout);
  fputs(s.OSREL, stdout);
  putchar('\n');
  return !opt_help;
}


----------------------------
static int print_tree(int pathc, char **pathv, struct libtree_state_t *s)
{
  libtree_state_init(s);
  parse_ld_so_conf(s);
  parse_ld_library_path(s);
  set_default_paths(s);
  int exit_code = 0;
  for (int i = 0; i < pathc; i += 1)
  {
    helper_print_tree_1(&exit_code, pathv, s, i);
  }

  libtree_state_free(s);
  return exit_code;
}


----------------------------
struct libtree_state_t
{
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
  size_t rpath_offsets[32];
  size_t ld_library_path_offset;
  size_t default_paths_offset;
  size_t ld_so_conf_offset;
  char found_all_needed[32];
}
----------------------------
***/


