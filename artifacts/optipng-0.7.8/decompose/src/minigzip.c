void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


/*** DEPENDENCIES:
static char *prog
----------------------------
***/


void gz_compress(FILE *in, gzFile out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = (int) fread(buf, 1, sizeof(buf), in);
    if (ferror(in))
    {
      perror("fread");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    if (gzwrite(out, buf, (unsigned) len) != len)
    {
      error(gzerror(out, &err));
    }
  }

  fclose(in);
  if (gzclose(out) != 0)
  {
    error("failed gzclose");
  }
}


/*** DEPENDENCIES:
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
int gzwrite(gzFile file, voidpc buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -3, "requested length does not fit in int");
    return 0;
  }
  return (int) gz_write(state, buf, len);
}


----------------------------
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


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
int gzclose(gzFile file)
{
  return gzclose_r(file);
}


----------------------------
***/


void file_compress(char *file, char *mode)
{
  char outfile[1024];
  FILE *in;
  unsigned int in_idx = 0;
  gzFile out;
  if ((strlen(file) + strlen(".gz")) >= (sizeof(outfile)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(outfile, sizeof(outfile), "%s%s", file, ".gz");
  in_idx = fopen(file, "rb");
  if ((&in[in_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  out = gzopen(outfile, mode);
  if (out == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, outfile);
    exit(1);
  }
  gz_compress(in, out);
  unlink(file);
}


/*** DEPENDENCIES:
typedef struct gzFile_s *gzFile
----------------------------
void gz_compress(FILE *in, gzFile out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = (int) fread(buf, 1, sizeof(buf), in);
    if (ferror(in))
    {
      perror("fread");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    if (gzwrite(out, buf, (unsigned) len) != len)
    {
      error(gzerror(out, &err));
    }
  }

  fclose(in);
  if (gzclose(out) != 0)
  {
    error("failed gzclose");
  }
}


----------------------------
static char *prog
----------------------------
gzFile gzopen(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}


----------------------------
***/


void gz_uncompress(gzFile in, FILE *out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = gzread(in, buf, sizeof(buf));
    if (len < 0)
    {
      error(gzerror(in, &err));
    }
    if (len == 0)
    {
      break;
    }
    if (((int) fwrite(buf, 1, (unsigned) len, out)) != len)
    {
      error("failed fwrite");
    }
  }

  if (fclose(out))
  {
    error("failed fclose");
  }
  if (gzclose(in) != 0)
  {
    error("failed gzclose");
  }
}


/*** DEPENDENCIES:
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
int gzread(gzFile file, voidp buf, unsigned len)
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
  if (((int) len) < 0)
  {
    gz_error(state, -2, "request does not fit in an int");
    return -1;
  }
  len = (unsigned) gz_read(state, buf, len);
  if (((len == 0) && (state->err != 0)) && (state->err != (-5)))
  {
    return -1;
  }
  return (int) len;
}


----------------------------
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


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
int gzclose(gzFile file)
{
  return gzclose_r(file);
}


----------------------------
***/


void file_uncompress(char *file)
{
  char buf[1024];
  char *infile;
  unsigned int infile_idx = 0;
  char *outfile;
  unsigned int outfile_idx = 0;
  FILE *out;
  unsigned int out_idx = 0;
  gzFile in;
  z_size_t len = strlen(file);
  if ((len + strlen(".gz")) >= (sizeof(buf)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(buf, sizeof(buf), "%s", file);
  if ((len > ((sizeof(".gz")) - 1)) && (strcmp((file + len) - ((sizeof(".gz")) - 1), ".gz") == 0))
  {
    infile_idx = file;
    outfile_idx = buf;
    outfile[(len - 3) + outfile_idx] = '\0';
  }
  else
  {
    outfile_idx = file;
    infile_idx = buf;
    snprintf(buf + len, (sizeof(buf)) - len, "%s", ".gz");
  }
  in = gzopen(infile, "rb");
  if (in == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, infile);
    exit(1);
  }
  out_idx = fopen(outfile, "wb");
  if ((&out[out_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  gz_uncompress(in, out);
  unlink(infile);
}


/*** DEPENDENCIES:
static char *prog
----------------------------
gzFile gzopen(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef struct gzFile_s *gzFile
----------------------------
void gz_uncompress(gzFile in, FILE *out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = gzread(in, buf, sizeof(buf));
    if (len < 0)
    {
      error(gzerror(in, &err));
    }
    if (len == 0)
    {
      break;
    }
    if (((int) fwrite(buf, 1, (unsigned) len, out)) != len)
    {
      error("failed fwrite");
    }
  }

  if (fclose(out))
  {
    error("failed fclose");
  }
  if (gzclose(in) != 0)
  {
    error("failed gzclose");
  }
}


----------------------------
***/


int main(int argc, char *argv[])
{
  int copyout = 0;
  int uncompr = 0;
  gzFile file;
  char *bname;
  unsigned int bname_idx = 0;
  char outmode[20];
  snprintf(outmode, sizeof(outmode), "%s", "wb6 ");
  prog = argv[0];
  bname_idx = strrchr(argv[0], '/');
  if (bname)
  {
    bname_idx += 1;
  }
  else
    bname_idx = argv[0];
  argc--, argv++;
  argv += 1;
  argc -= 1;
  if (!strcmp(bname, "gunzip"))
  {
    uncompr = 1;
  }
  else
    if (!strcmp(bname, "zcat"))
  {
    copyout = (uncompr = 1);
  }
  while (argc > 0)
  {
    if (strcmp(*argv, "-c") == 0)
    {
      copyout = 1;
    }
    else
      if (strcmp(*argv, "-d") == 0)
    {
      uncompr = 1;
    }
    else
      if (strcmp(*argv, "-f") == 0)
    {
      outmode[3] = 'f';
    }
    else
      if (strcmp(*argv, "-h") == 0)
    {
      outmode[3] = 'h';
    }
    else
      if (strcmp(*argv, "-r") == 0)
    {
      outmode[3] = 'R';
    }
    else
      if (((((*argv)[0] == '-') && ((*argv)[1] >= '1')) && ((*argv)[1] <= '9')) && ((*argv)[2] == 0))
    {
      outmode[2] = (*argv)[1];
    }
    else
      break;
    argc--, argv++;
    argv += 1;
    argc -= 1;
  }

  if (outmode[3] == ' ')
  {
    outmode[3] = 0;
  }
  if (argc == 0)
  {
    ;
    ;
    if (uncompr)
    {
      file = gzdopen(fileno(stdin), "rb");
      if (file == 0)
      {
        error("can't gzdopen stdin");
      }
      gz_uncompress(file, stdout);
    }
    else
    {
      file = gzdopen(fileno(stdout), outmode);
      if (file == 0)
      {
        error("can't gzdopen stdout");
      }
      gz_compress(stdin, file);
    }
  }
  else
  {
    if (copyout)
    {
      ;
    }
    do
    {
      if (uncompr)
      {
        if (copyout)
        {
          file = gzopen(*argv, "rb");
          if (file == 0)
          {
            fprintf(stderr, "%s: can't gzopen %s\n", prog, *argv);
          }
          else
            gz_uncompress(file, stdout);
        }
        else
        {
          file_uncompress(*argv);
        }
      }
      else
      {
        if (copyout)
        {
          FILE *in = fopen(*argv, "rb");
          if (in == 0)
          {
            perror(*argv);
          }
          else
          {
            file = gzdopen(fileno(stdout), outmode);
            if (file == 0)
            {
              error("can't gzdopen stdout");
            }
            gz_compress(in, file);
          }
        }
        else
        {
          file_compress(*argv, outmode);
        }
      }
    }
    while (argv++, --argc);
  }
  return 0;
}


/*** DEPENDENCIES:
static char *prog
----------------------------
gzFile gzopen(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}


----------------------------
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}


----------------------------
void file_compress(char *file, char *mode)
{
  char outfile[1024];
  FILE *in;
  unsigned int in_idx = 0;
  gzFile out;
  if ((strlen(file) + strlen(".gz")) >= (sizeof(outfile)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(outfile, sizeof(outfile), "%s%s", file, ".gz");
  in_idx = fopen(file, "rb");
  if ((&in[in_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  out = gzopen(outfile, mode);
  if (out == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, outfile);
    exit(1);
  }
  gz_compress(in, out);
  unlink(file);
}


----------------------------
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


----------------------------
void gz_compress(FILE *in, gzFile out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = (int) fread(buf, 1, sizeof(buf), in);
    if (ferror(in))
    {
      perror("fread");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    if (gzwrite(out, buf, (unsigned) len) != len)
    {
      error(gzerror(out, &err));
    }
  }

  fclose(in);
  if (gzclose(out) != 0)
  {
    error("failed gzclose");
  }
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
void gz_uncompress(gzFile in, FILE *out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = gzread(in, buf, sizeof(buf));
    if (len < 0)
    {
      error(gzerror(in, &err));
    }
    if (len == 0)
    {
      break;
    }
    if (((int) fwrite(buf, 1, (unsigned) len, out)) != len)
    {
      error("failed fwrite");
    }
  }

  if (fclose(out))
  {
    error("failed fclose");
  }
  if (gzclose(in) != 0)
  {
    error("failed gzclose");
  }
}


----------------------------
void file_uncompress(char *file)
{
  char buf[1024];
  char *infile;
  unsigned int infile_idx = 0;
  char *outfile;
  unsigned int outfile_idx = 0;
  FILE *out;
  unsigned int out_idx = 0;
  gzFile in;
  z_size_t len = strlen(file);
  if ((len + strlen(".gz")) >= (sizeof(buf)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(buf, sizeof(buf), "%s", file);
  if ((len > ((sizeof(".gz")) - 1)) && (strcmp((file + len) - ((sizeof(".gz")) - 1), ".gz") == 0))
  {
    infile_idx = file;
    outfile_idx = buf;
    outfile[(len - 3) + outfile_idx] = '\0';
  }
  else
  {
    outfile_idx = file;
    infile_idx = buf;
    snprintf(buf + len, (sizeof(buf)) - len, "%s", ".gz");
  }
  in = gzopen(infile, "rb");
  if (in == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, infile);
    exit(1);
  }
  out_idx = fopen(outfile, "wb");
  if ((&out[out_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  gz_uncompress(in, out);
  unlink(infile);
}


----------------------------
***/


