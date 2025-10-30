#include <config.h>
#include <debug.h>
#include <param.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

extern void mc_set_debug(int debug);
extern int mc_get_debug(void);
extern void mc_set_syslog(int syslog);
extern void mc_debug(const char *msg, ...);
extern void mc_error(const char *msg, ...);
extern void mc_info(const char *msg, ...);
static int _syslog = 0;
static int _debug = 0;
void mc_set_debug(int debug)
{
  _debug = debug;
}

int mc_get_debug(void)
{
  return _debug;
}

extern void mc_set_syslog(int syslog)
{
  _syslog = syslog;
}

void mc_debug(const char *msg, ...)
{
  va_list ap;
  if (_debug)
  {
    __builtin_va_start(ap);
    if (_syslog)
    {
      vsyslog(LOG_DEBUG, msg, ap);
    }
    else
      vprintf(msg, ap);
    ;
  }
}

void mc_error(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  if (_syslog)
  {
    vsyslog(LOG_ERR, msg, ap);
  }
  else
    vfprintf(stderr, msg, ap);
  ;
}

void mc_info(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  if (_syslog)
  {
    vsyslog(LOG_INFO, msg, ap);
  }
  else
    vfprintf(stderr, msg, ap);
  ;
}

