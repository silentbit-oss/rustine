void mc_set_debug(int debug)
{
  _debug = debug;
}


/*** DEPENDENCIES:
static int _debug = 0
----------------------------
***/


int mc_get_debug(void)
{
  return _debug;
}


/*** DEPENDENCIES:
static int _debug = 0
----------------------------
***/


extern void mc_set_syslog(int syslog)
{
  _syslog = syslog;
}


/*** DEPENDENCIES:
static int _syslog = 0
----------------------------
***/


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


/*** DEPENDENCIES:
static int _syslog = 0
----------------------------
***/


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


/*** DEPENDENCIES:
static int _syslog = 0
----------------------------
***/


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


/*** DEPENDENCIES:
static int _syslog = 0
----------------------------
static int _debug = 0
----------------------------
***/


