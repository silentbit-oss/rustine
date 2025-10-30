void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


static void gz_reset(gz_statep state)
{
  state->x.have = 0;
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
    state->how = 0;
  }
  else
    state->reset = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->x.pos = 0;
  state->strm.avail_in = 0;
}


/*** DEPENDENCIES:
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


// hint:  ['mode_idx_ref is a mutable refrence to unsigned int', 'state_ref is a mutable refrence to gz_statep']
gzFile helper_gz_open_1(unsigned int * const mode_idx_ref, gz_statep * const state_ref, const char * const mode)
{
  unsigned int mode_idx = *mode_idx_ref;
  gz_statep state = *state_ref;
  if ((mode[mode_idx] >= '0') && (mode[mode_idx] <= '9'))
  {
    state->level = mode[mode_idx] - '0';
  }
  else
    switch (mode[mode_idx])
  {
    case 'r':
    {
      state->mode = 7247;
      break;
    }

    case '+':
    {
      free(state);
      return 0;
    }

    case 'b':
    {
      break;
    }

    case 'f':
    {
      state->strategy = 1;
      break;
    }

    case 'h':
    {
      state->strategy = 2;
      break;
    }

    case 'R':
    {
      state->strategy = 3;
      break;
    }

    case 'F':
    {
      state->strategy = 4;
      break;
    }

    case 'T':
    {
      state->direct = 1;
      break;
    }

    default:
    {
      ;
    }

  }

  mode_idx += 1;
  *mode_idx_ref = mode_idx;
  *state_ref = state;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


static gzFile gz_open(const void *path, int fd, const char *mode)
{
  unsigned int mode_idx = 0;
  gz_statep state;
  z_size_t len;
  int oflag;
  if (path == 0)
  {
    return 0;
  }
  state = (gz_statep) malloc(sizeof(gz_state));
  if (state == 0)
  {
    return 0;
  }
  state->size = 0;
  state->want = 8192;
  state->msg = 0;
  state->mode = 0;
  state->level = -1;
  state->strategy = 0;
  state->direct = 0;
  while (mode[mode_idx])
  {
    helper_gz_open_1(&mode_idx, &state, mode);
  }

  if (state->mode == 0)
  {
    free(state);
    return 0;
  }
  if (state->mode == 7247)
  {
    if (state->direct)
    {
      free(state);
      return 0;
    }
    state->direct = 1;
  }
  len = strlen((const char *) path);
  state->path = (char *) malloc(len + 1);
  if (state->path == 0)
  {
    free(state);
    return 0;
  }
  (void) snprintf(state->path, len + 1, "%s", (const char *) path);
  oflag = (state->mode == 7247) ? (O_RDONLY) : ((O_WRONLY | O_CREAT) | ((state->mode == 31153) ? (O_TRUNC) : (O_APPEND)));
  state->fd = (fd > (-1)) ? (fd) : (open((const char *) path, oflag, 0666));
  if (state->fd == (-1))
  {
    free(state->path);
    free(state);
    return 0;
  }
  if (state->mode == 1)
  {
    lseek(state->fd, 0, 2);
    state->mode = 31153;
  }
  if (state->mode == 7247)
  {
    state->start = lseek(state->fd, 0, 1);
    if (state->start == (-1))
    {
      state->start = 0;
    }
  }
  gz_reset(state);
  return (gzFile) state;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
static void gz_reset(gz_statep state)
{
  state->x.have = 0;
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
    state->how = 0;
  }
  else
    state->reset = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->x.pos = 0;
  state->strm.avail_in = 0;
}


----------------------------
typedef gz_state *gz_statep
----------------------------
typedef size_t z_size_t
----------------------------
gzFile helper_gz_open_1(unsigned int * const mode_idx_ref, gz_statep * const state_ref, const char * const mode)
{
  unsigned int mode_idx = *mode_idx_ref;
  gz_statep state = *state_ref;
  if ((mode[mode_idx] >= '0') && (mode[mode_idx] <= '9'))
  {
    state->level = mode[mode_idx] - '0';
  }
  else
    switch (mode[mode_idx])
  {
    case 'r':
    {
      state->mode = 7247;
      break;
    }

    case '+':
    {
      free(state);
      return 0;
    }

    case 'b':
    {
      break;
    }

    case 'f':
    {
      state->strategy = 1;
      break;
    }

    case 'h':
    {
      state->strategy = 2;
      break;
    }

    case 'R':
    {
      state->strategy = 3;
      break;
    }

    case 'F':
    {
      state->strategy = 4;
      break;
    }

    case 'T':
    {
      state->direct = 1;
      break;
    }

    default:
    {
      ;
    }

  }

  mode_idx += 1;
  *mode_idx_ref = mode_idx;
  *state_ref = state;
}


----------------------------
***/


gzFile gzopen(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}


/*** DEPENDENCIES:
static gzFile gz_open(const void *path, int fd, const char *mode)
{
  unsigned int mode_idx = 0;
  gz_statep state;
  z_size_t len;
  int oflag;
  if (path == 0)
  {
    return 0;
  }
  state = (gz_statep) malloc(sizeof(gz_state));
  if (state == 0)
  {
    return 0;
  }
  state->size = 0;
  state->want = 8192;
  state->msg = 0;
  state->mode = 0;
  state->level = -1;
  state->strategy = 0;
  state->direct = 0;
  while (mode[mode_idx])
  {
    helper_gz_open_1(&mode_idx, &state, mode);
  }

  if (state->mode == 0)
  {
    free(state);
    return 0;
  }
  if (state->mode == 7247)
  {
    if (state->direct)
    {
      free(state);
      return 0;
    }
    state->direct = 1;
  }
  len = strlen((const char *) path);
  state->path = (char *) malloc(len + 1);
  if (state->path == 0)
  {
    free(state);
    return 0;
  }
  (void) snprintf(state->path, len + 1, "%s", (const char *) path);
  oflag = (state->mode == 7247) ? (O_RDONLY) : ((O_WRONLY | O_CREAT) | ((state->mode == 31153) ? (O_TRUNC) : (O_APPEND)));
  state->fd = (fd > (-1)) ? (fd) : (open((const char *) path, oflag, 0666));
  if (state->fd == (-1))
  {
    free(state->path);
    free(state);
    return 0;
  }
  if (state->mode == 1)
  {
    lseek(state->fd, 0, 2);
    state->mode = 31153;
  }
  if (state->mode == 7247)
  {
    state->start = lseek(state->fd, 0, 1);
    if (state->start == (-1))
    {
      state->start = 0;
    }
  }
  gz_reset(state);
  return (gzFile) state;
}


----------------------------
***/


gzFile gzopen64(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}


/*** DEPENDENCIES:
static gzFile gz_open(const void *path, int fd, const char *mode)
{
  unsigned int mode_idx = 0;
  gz_statep state;
  z_size_t len;
  int oflag;
  if (path == 0)
  {
    return 0;
  }
  state = (gz_statep) malloc(sizeof(gz_state));
  if (state == 0)
  {
    return 0;
  }
  state->size = 0;
  state->want = 8192;
  state->msg = 0;
  state->mode = 0;
  state->level = -1;
  state->strategy = 0;
  state->direct = 0;
  while (mode[mode_idx])
  {
    helper_gz_open_1(&mode_idx, &state, mode);
  }

  if (state->mode == 0)
  {
    free(state);
    return 0;
  }
  if (state->mode == 7247)
  {
    if (state->direct)
    {
      free(state);
      return 0;
    }
    state->direct = 1;
  }
  len = strlen((const char *) path);
  state->path = (char *) malloc(len + 1);
  if (state->path == 0)
  {
    free(state);
    return 0;
  }
  (void) snprintf(state->path, len + 1, "%s", (const char *) path);
  oflag = (state->mode == 7247) ? (O_RDONLY) : ((O_WRONLY | O_CREAT) | ((state->mode == 31153) ? (O_TRUNC) : (O_APPEND)));
  state->fd = (fd > (-1)) ? (fd) : (open((const char *) path, oflag, 0666));
  if (state->fd == (-1))
  {
    free(state->path);
    free(state);
    return 0;
  }
  if (state->mode == 1)
  {
    lseek(state->fd, 0, 2);
    state->mode = 31153;
  }
  if (state->mode == 7247)
  {
    state->start = lseek(state->fd, 0, 1);
    if (state->start == (-1))
    {
      state->start = 0;
    }
  }
  gz_reset(state);
  return (gzFile) state;
}


----------------------------
***/


gzFile gzdopen(int fd, const char *mode)
{
  char *path;
  unsigned int path_idx = 0;
  gzFile gz;
  if ((fd == (-1)) || ((path_idx = (char *) malloc(7 + (3 * (sizeof(int))))) == 0))
  {
    return 0;
  }
  (void) snprintf(path, 7 + (3 * (sizeof(int))), "<fd:%d>", fd);
  gz = gz_open(path, fd, mode);
  free(path);
  return gz;
}


/*** DEPENDENCIES:
static gzFile gz_open(const void *path, int fd, const char *mode)
{
  unsigned int mode_idx = 0;
  gz_statep state;
  z_size_t len;
  int oflag;
  if (path == 0)
  {
    return 0;
  }
  state = (gz_statep) malloc(sizeof(gz_state));
  if (state == 0)
  {
    return 0;
  }
  state->size = 0;
  state->want = 8192;
  state->msg = 0;
  state->mode = 0;
  state->level = -1;
  state->strategy = 0;
  state->direct = 0;
  while (mode[mode_idx])
  {
    helper_gz_open_1(&mode_idx, &state, mode);
  }

  if (state->mode == 0)
  {
    free(state);
    return 0;
  }
  if (state->mode == 7247)
  {
    if (state->direct)
    {
      free(state);
      return 0;
    }
    state->direct = 1;
  }
  len = strlen((const char *) path);
  state->path = (char *) malloc(len + 1);
  if (state->path == 0)
  {
    free(state);
    return 0;
  }
  (void) snprintf(state->path, len + 1, "%s", (const char *) path);
  oflag = (state->mode == 7247) ? (O_RDONLY) : ((O_WRONLY | O_CREAT) | ((state->mode == 31153) ? (O_TRUNC) : (O_APPEND)));
  state->fd = (fd > (-1)) ? (fd) : (open((const char *) path, oflag, 0666));
  if (state->fd == (-1))
  {
    free(state->path);
    free(state);
    return 0;
  }
  if (state->mode == 1)
  {
    lseek(state->fd, 0, 2);
    state->mode = 31153;
  }
  if (state->mode == 7247)
  {
    state->start = lseek(state->fd, 0, 1);
    if (state->start == (-1))
    {
      state->start = 0;
    }
  }
  gz_reset(state);
  return (gzFile) state;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


// hint:  ['ret_ref is a mutable refrence to off_t', 'state_ref is a mutable refrence to gz_statep']
off_t helper_gzseek64_1(off_t * const ret_ref, gz_statep * const state_ref, off_t offset)
{
  off_t ret = *ret_ref;
  gz_statep state = *state_ref;
  ret = lseek(state->fd, offset - ((off_t) state->x.have), 1);
  if (ret == (-1))
  {
    return -1;
  }
  state->x.have = 0;
  state->eof = 0;
  state->past = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->strm.avail_in = 0;
  state->x.pos += offset;
  return state->x.pos;
  *ret_ref = ret;
  *state_ref = state;
}


/*** DEPENDENCIES:
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


int gzrewind(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (lseek(state->fd, state->start, 0) == (-1))
  {
    return -1;
  }
  gz_reset(state);
  return 0;
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
static void gz_reset(gz_statep state)
{
  state->x.have = 0;
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
    state->how = 0;
  }
  else
    state->reset = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->x.pos = 0;
  state->strm.avail_in = 0;
}


----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


off_t gzseek64(gzFile file, off_t offset, int whence)
{
  unsigned n;
  off_t ret;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if ((whence != 0) && (whence != 1))
  {
    return -1;
  }
  if (whence == 0)
  {
    offset -= state->x.pos;
  }
  else
    if (state->seek)
  {
    offset += state->skip;
  }
  state->seek = 0;
  if (((state->mode == 7247) && (state->how == 1)) && ((state->x.pos + offset) >= 0))
  {
    helper_gzseek64_1(&ret, &state, offset);
  }
  if (offset < 0)
  {
    if (state->mode != 7247)
    {
      return -1;
    }
    offset += state->x.pos;
    if (offset < 0)
    {
      return -1;
    }
    if (gzrewind(file) == (-1))
    {
      return -1;
    }
  }
  if (state->mode == 7247)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > offset)) ? ((unsigned) offset) : (state->x.have);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    offset -= n;
  }
  if (offset)
  {
    state->seek = 1;
    state->skip = offset;
  }
  return state->x.pos + offset;
}


/*** DEPENDENCIES:
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
off_t helper_gzseek64_1(off_t * const ret_ref, gz_statep * const state_ref, off_t offset)
{
  off_t ret = *ret_ref;
  gz_statep state = *state_ref;
  ret = lseek(state->fd, offset - ((off_t) state->x.have), 1);
  if (ret == (-1))
  {
    return -1;
  }
  state->x.have = 0;
  state->eof = 0;
  state->past = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->strm.avail_in = 0;
  state->x.pos += offset;
  return state->x.pos;
  *ret_ref = ret;
  *state_ref = state;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
int gzrewind(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (lseek(state->fd, state->start, 0) == (-1))
  {
    return -1;
  }
  gz_reset(state);
  return 0;
}


----------------------------
***/


off_t gzseek(gzFile file, off_t offset, int whence)
{
  off_t ret;
  ret = gzseek64(file, (off_t) offset, whence);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
off_t gzseek64(gzFile file, off_t offset, int whence)
{
  unsigned n;
  off_t ret;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if ((whence != 0) && (whence != 1))
  {
    return -1;
  }
  if (whence == 0)
  {
    offset -= state->x.pos;
  }
  else
    if (state->seek)
  {
    offset += state->skip;
  }
  state->seek = 0;
  if (((state->mode == 7247) && (state->how == 1)) && ((state->x.pos + offset) >= 0))
  {
    helper_gzseek64_1(&ret, &state, offset);
  }
  if (offset < 0)
  {
    if (state->mode != 7247)
    {
      return -1;
    }
    offset += state->x.pos;
    if (offset < 0)
    {
      return -1;
    }
    if (gzrewind(file) == (-1))
    {
      return -1;
    }
  }
  if (state->mode == 7247)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > offset)) ? ((unsigned) offset) : (state->x.have);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    offset -= n;
  }
  if (offset)
  {
    state->seek = 1;
    state->skip = offset;
  }
  return state->x.pos + offset;
}


----------------------------
***/


off_t gztell64(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  return state->x.pos + ((state->seek) ? (state->skip) : (0));
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


off_t gztell(gzFile file)
{
  off_t ret;
  ret = gztell64(file);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}


/*** DEPENDENCIES:
off_t gztell64(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  return state->x.pos + ((state->seek) ? (state->skip) : (0));
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


off_t gzoffset64(gzFile file)
{
  off_t offset;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  offset = lseek(state->fd, 0, 1);
  if (offset == (-1))
  {
    return -1;
  }
  if (state->mode == 7247)
  {
    offset -= state->strm.avail_in;
  }
  return offset;
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


off_t gzoffset(gzFile file)
{
  off_t ret;
  ret = gzoffset64(file);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}


/*** DEPENDENCIES:
off_t gzoffset64(gzFile file)
{
  off_t offset;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  offset = lseek(state->fd, 0, 1);
  if (offset == (-1))
  {
    return -1;
  }
  if (state->mode == 7247)
  {
    offset -= state->strm.avail_in;
  }
  return offset;
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


int gzbuffer(gzFile file, unsigned size)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if (state->size != 0)
  {
    return -1;
  }
  if ((size << 1) < size)
  {
    return -1;
  }
  if (size < 8)
  {
    size = 8;
  }
  state->want = size;
  return 0;
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


int gzeof(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return 0;
  }
  return (state->mode == 7247) ? (state->past) : (0);
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


const char *gzerror(gzFile file, int *errnum)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return 0;
  }
  if (errnum != 0)
  {
    *errnum = state->err;
  }
  return (state->err == (-4)) ? ("out of memory") : ((state->msg == 0) ? ("") : (state->msg));
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


void gzclearerr(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return;
  }
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
  }
  gz_error(state, 0, 0);
}


/*** DEPENDENCIES:
void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state
----------------------------
typedef gz_state *gz_statep
----------------------------
***/


