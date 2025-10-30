void log_vwrite(const char *msg, va_list ap)
{
  char *fmt;
  char *out;
  struct timeval tv;
  if (log_file == 0)
  {
    return;
  }
  if (vasprintf(&fmt, msg, ap) == (-1))
  {
    exit(1);
  }
  if (stravis(&out, fmt, ((0x01 | 0x02) | 0x08) | 0x10) == (-1))
  {
    exit(1);
  }
  gettimeofday(&tv, 0);
  if (fprintf(log_file, "%lld.%06d %s\n", (long long) tv.tv_sec, (int) tv.tv_usec, out) == (-1))
  {
    exit(1);
  }
  fflush(log_file);
  free(out);
  free(fmt);
}


/*** DEPENDENCIES:
static FILE *log_file
----------------------------
int stravis(char **outp, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  int serrno;
  buf_idx = calloc(4, strlen(src) + 1);
  if ((&buf[buf_idx]) == 0)
  {
    return -1;
  }
  len = strvis(buf, src, flag);
  serrno = errno;
  *outp = realloc(buf, len + 1);
  if ((*outp) == 0)
  {
    *outp = &buf[buf_idx];
    errno = serrno;
  }
  return len;
}


----------------------------
***/


void log_add_level(void)
{
  log_level += 1;
}


/*** DEPENDENCIES:
static int log_level
----------------------------
***/


int log_get_level(void)
{
  return log_level;
}


/*** DEPENDENCIES:
static int log_level
----------------------------
***/


void log_close(void)
{
  if (log_file != 0)
  {
    fclose(log_file);
  }
  log_file = 0;
  event_set_log_callback(0);
}


/*** DEPENDENCIES:
static FILE *log_file
----------------------------
***/


static void log_event_cb(int severity, const char *msg)
{
  log_debug("%s", msg);
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
***/


void log_open(const char *name)
{
  char *path;
  if (log_level == 0)
  {
    return;
  }
  log_close();
  xasprintf(&path, "tmux-%s-%ld.log", name, (long) getpid());
  log_file = fopen(path, "a");
  free(path);
  if (log_file == 0)
  {
    return;
  }
  setvbuf(log_file, 0, _IOLBF, 0);
  event_set_log_callback(log_event_cb);
}


/*** DEPENDENCIES:
static FILE *log_file
----------------------------
static int log_level
----------------------------
void log_close(void)
{
  if (log_file != 0)
  {
    fclose(log_file);
  }
  log_file = 0;
  event_set_log_callback(0);
}


----------------------------
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
static void log_event_cb(int severity, const char *msg)
{
  log_debug("%s", msg);
}


----------------------------
***/


void log_toggle(const char *name)
{
  if (log_level == 0)
  {
    log_level = 1;
    log_open(name);
    log_debug("log opened");
  }
  else
  {
    log_debug("log closed");
    log_level = 0;
    log_close();
  }
}


/*** DEPENDENCIES:
void log_close(void)
{
  if (log_file != 0)
  {
    fclose(log_file);
  }
  log_file = 0;
  event_set_log_callback(0);
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
void log_open(const char *name)
{
  char *path;
  if (log_level == 0)
  {
    return;
  }
  log_close();
  xasprintf(&path, "tmux-%s-%ld.log", name, (long) getpid());
  log_file = fopen(path, "a");
  free(path);
  if (log_file == 0)
  {
    return;
  }
  setvbuf(log_file, 0, _IOLBF, 0);
  event_set_log_callback(log_event_cb);
}


----------------------------
static int log_level
----------------------------
***/


