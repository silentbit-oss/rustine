char *_json_c_strerror(int errno_in)
{
  int start_idx;
  char digbuf[20];
  int ii;
  int jj;
  if (!_json_c_strerror_enable)
  {
    _json_c_strerror_enable = (getenv("_JSON_C_STRERROR_ENABLE") == 0) ? (-1) : (1);
  }
  if (_json_c_strerror_enable == (-1))
  {
    return strerror(errno_in);
  }
  for (ii = 0; errno_list[ii].errno_str != ((char *) 0); ii += 1)
  {
    const char *errno_str = errno_list[ii].errno_str;
    if (errno_list[ii].errno_value != errno_in)
    {
      continue;
    }
    for (start_idx = (sizeof("ERRNO=")) - 1, jj = 0; errno_str[jj] != '\0'; jj += 1, start_idx += 1)
    {
      errno_buf[start_idx] = errno_str[jj];
    }

    errno_buf[start_idx] = '\0';
    return errno_buf;
  }

  for (ii = 0; errno_in >= 10; errno_in /= 10, ii += 1)
  {
    digbuf[ii] = "0123456789"[errno_in % 10];
  }

  digbuf[ii] = "0123456789"[errno_in % 10];
  for (start_idx = (sizeof("ERRNO=")) - 1; ii >= 0; ii -= 1, start_idx += 1)
  {
    errno_buf[start_idx] = digbuf[ii];
  }

  errno_buf[start_idx] = '\0';
  return errno_buf;
}


/*** DEPENDENCIES:
static char errno_buf[128] = "ERRNO="
----------------------------
static int _json_c_strerror_enable = 0
----------------------------
static struct 
{
  int errno_value;
  const char *errno_str;
} errno_list[] = {{EPERM, &"undef_EPERM"[6]}, {ENOENT, &"undef_ENOENT"[6]}, {ESRCH, &"undef_ESRCH"[6]}, {EINTR, &"undef_EINTR"[6]}, {EIO, &"undef_EIO"[6]}, {ENXIO, &"undef_ENXIO"[6]}, {E2BIG, &"undef_E2BIG"[6]}, {EBADF, &"undef_EBADF"[6]}, {ECHILD, &"undef_ECHILD"[6]}, {EDEADLK, &"undef_EDEADLK"[6]}, {ENOMEM, &"undef_ENOMEM"[6]}, {EACCES, &"undef_EACCES"[6]}, {EFAULT, &"undef_EFAULT"[6]}, {EBUSY, &"undef_EBUSY"[6]}, {EEXIST, &"undef_EEXIST"[6]}, {EXDEV, &"undef_EXDEV"[6]}, {ENODEV, &"undef_ENODEV"[6]}, {ENOTDIR, &"undef_ENOTDIR"[6]}, {EISDIR, &"undef_EISDIR"[6]}, {EINVAL, &"undef_EINVAL"[6]}, {ENFILE, &"undef_ENFILE"[6]}, {EMFILE, &"undef_EMFILE"[6]}, {ENOTTY, &"undef_ENOTTY"[6]}, {EFBIG, &"undef_EFBIG"[6]}, {ENOSPC, &"undef_ENOSPC"[6]}, {ESPIPE, &"undef_ESPIPE"[6]}, {EROFS, &"undef_EROFS"[6]}, {EMLINK, &"undef_EMLINK"[6]}, {EPIPE, &"undef_EPIPE"[6]}, {EDOM, &"undef_EDOM"[6]}, {ERANGE, &"undef_ERANGE"[6]}, {EAGAIN, &"undef_EAGAIN"[6]}, {0, (char *) 0}}
----------------------------
***/


