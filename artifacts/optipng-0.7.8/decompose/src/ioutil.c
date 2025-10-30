opng_foffset_t opng_ftello(FILE *stream)
{
  return (opng_foffset_t) ftell(stream);
}


/*** DEPENDENCIES:
***/


char *opng_path_replace_dir(char *buffer, size_t bufsize, const char *old_path, const char *new_dirname)
{
  const char *path;
  unsigned int path_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  size_t dirlen;
  path_idx = old_path;
  for (;;)
  {
    ptr_idx = strpbrk(path, "/");
    if ((&ptr[ptr_idx]) == 0)
    {
      break;
    }
    path_idx = (&ptr[ptr_idx]) + 1;
  }

  dirlen = strlen(new_dirname);
  if (((dirlen + strlen(path)) + 2) >= bufsize)
  {
    return 0;
  }
  if (dirlen > 0)
  {
    strcpy(buffer, new_dirname);
    {
      if (strchr("/", buffer[dirlen - 1]) == 0)
      {
        buffer[dirlen] = '/';
        dirlen += 1;
      }
    }
  }
  strcpy(buffer + dirlen, path);
  return buffer;
}


/*** DEPENDENCIES:
***/


char *opng_path_replace_ext(char *buffer, size_t bufsize, const char *old_path, const char *new_extname)
{
  unsigned int new_extname_idx = 0;
  size_t i;
  size_t pos;
  if (new_extname[0 + new_extname_idx] != '.')
  {
    return 0;
  }
  for (i = 0, pos = (size_t) (-1); old_path[i] != '\0'; i += 1)
  {
    if (i >= bufsize)
    {
      return 0;
    }
    if ((buffer[i] = old_path[i]) == '.')
    {
      pos = i;
    }
  }

  if (i > pos)
  {
    i = pos;
  }
  for (;; i += 1, new_extname_idx += 1)
  {
    if (i >= bufsize)
    {
      return 0;
    }
    if ((buffer[i] = new_extname[new_extname_idx]) == '\0')
    {
      return buffer;
    }
  }

}


/*** DEPENDENCIES:
***/


char *opng_path_make_backup(char *buffer, size_t bufsize, const char *path)
{
  static const char bak_extname[] = ".bak";
  if ((strlen(path) + (sizeof(bak_extname))) > bufsize)
  {
    return 0;
  }
  strcpy(buffer, path);
  strcat(buffer, bak_extname);
  return buffer;
}


/*** DEPENDENCIES:
***/


int opng_os_rename(const char *src_path, const char *dest_path, int clobber)
{
  if (!clobber)
  {
    if (access(dest_path, 0) >= 0)
    {
      return -1;
    }
  }
  return rename(src_path, dest_path);
}


/*** DEPENDENCIES:
***/


int opng_os_create_dir(const char *dirname)
{
  if (dirname[0] == '\0')
  {
    return 0;
  }
  {
    struct stat sbuf;
    if (stat(dirname, &sbuf) == 0)
    {
      return (sbuf.st_mode & S_IFDIR) ? (0) : (-1);
    }
    return mkdir(dirname, 0777);
  }
}


/*** DEPENDENCIES:
***/


int opng_os_copy_file_attr(const char *src_path, const char *dest_path)
{
  struct stat sbuf;
  int result;
  if (stat(src_path, &sbuf) != 0)
  {
    return -1;
  }
  result = 0;
  if (chown(dest_path, sbuf.st_uid, sbuf.st_gid) != 0)
  {
  }
  if (chmod(dest_path, sbuf.st_mode) != 0)
  {
    result = -1;
  }
  {
    struct utimbuf utbuf;
    utbuf.actime = sbuf.st_atime;
    utbuf.modtime = sbuf.st_mtime;
    if (utime(dest_path, &utbuf) != 0)
    {
      result = -1;
    }
  }
  return result;
}


/*** DEPENDENCIES:
***/


int opng_os_test_file_access(const char *path, const char *mode)
{
  int faccess;
  int freg;
  faccess = (freg = 0);
  if (strchr(mode, 'f') != 0)
  {
    freg = 1;
  }
  if (strchr(mode, 'r') != 0)
  {
    faccess |= 4;
  }
  if (strchr(mode, 'w') != 0)
  {
    faccess |= 2;
  }
  if (strchr(mode, 'x') != 0)
  {
    faccess |= 1;
  }
  if ((faccess == 0) && (!freg))
  {
    if (strchr(mode, 'e') == 0)
    {
      return 0;
    }
  }
  {
    struct stat sbuf;
    if (stat(path, &sbuf) != 0)
    {
      return -1;
    }
    if (freg && ((sbuf.st_mode & S_IFREG) != S_IFREG))
    {
      return -1;
    }
    if (faccess == 0)
    {
      return 0;
    }
    return access(path, faccess);
  }
}


/*** DEPENDENCIES:
***/


int opng_os_test_file_equiv(const char *path1, const char *path2)
{
  struct stat sbuf1;
  struct stat sbuf2;
  if ((stat(path1, &sbuf1) != 0) || (stat(path2, &sbuf2) != 0))
  {
    return -1;
  }
  if ((sbuf1.st_dev == sbuf2.st_dev) && (sbuf1.st_ino == sbuf2.st_ino))
  {
    return (sbuf1.st_ino != 0) ? (1) : (-1);
  }
  else
  {
    return 0;
  }
}


/*** DEPENDENCIES:
***/


int opng_os_unlink(const char *path)
{
  return unlink(path);
}


/*** DEPENDENCIES:
***/


int opng_fseeko(FILE *stream, opng_foffset_t offset, int whence)
{
  return fseek(stream, (long) offset, whence);
}


/*** DEPENDENCIES:
typedef long opng_foffset_t
----------------------------
***/


int opng_fgetsize(FILE *stream, opng_fsize_t *size)
{
  struct stat sbuf;
  if (fstat(fileno(stream), &sbuf) != 0)
  {
    return -1;
  }
  if (sbuf.st_size < 0)
  {
    return -1;
  }
  *size = (opng_fsize_t) sbuf.st_size;
  return 0;
}


/*** DEPENDENCIES:
typedef unsigned long opng_fsize_t
----------------------------
***/


size_t opng_fwriteo(FILE *stream, opng_foffset_t offset, int whence, const void *block, size_t blocksize)
{
  fpos_t pos;
  size_t result;
  if ((fgetpos(stream, &pos) != 0) || (fflush(stream) != 0))
  {
    return 0;
  }
  if (opng_fseeko(stream, offset, whence) == 0)
  {
    result = fwrite(block, 1, blocksize, stream);
  }
  else
    result = 0;
  if (fflush(stream) != 0)
  {
    result = 0;
  }
  if (fsetpos(stream, &pos) != 0)
  {
    result = 0;
  }
  return result;
}


/*** DEPENDENCIES:
typedef long opng_foffset_t
----------------------------
int opng_fseeko(FILE *stream, opng_foffset_t offset, int whence)
{
  return fseek(stream, (long) offset, whence);
}


----------------------------
***/


size_t opng_freado(FILE *stream, opng_foffset_t offset, int whence, void *block, size_t blocksize)
{
  fpos_t pos;
  size_t result;
  if (fgetpos(stream, &pos) != 0)
  {
    return 0;
  }
  if (opng_fseeko(stream, offset, whence) == 0)
  {
    result = fread(block, 1, blocksize, stream);
  }
  else
    result = 0;
  if (fsetpos(stream, &pos) != 0)
  {
    result = 0;
  }
  return result;
}


/*** DEPENDENCIES:
typedef long opng_foffset_t
----------------------------
int opng_fseeko(FILE *stream, opng_foffset_t offset, int whence)
{
  return fseek(stream, (long) offset, whence);
}


----------------------------
***/


