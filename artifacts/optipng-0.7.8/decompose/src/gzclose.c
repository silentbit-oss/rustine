int gzclose(gzFile file)
{
  return gzclose_r(file);
}


/*** DEPENDENCIES:
int gzclose_r(gzFile file)
{
  int ret;
  int err;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 7247)
  {
    return -2;
  }
  if (state->size)
  {
    inflateEnd(&state->strm);
    free(state->out);
    free(state->in);
  }
  err = (state->err == (-5)) ? (-5) : (0);
  gz_error(state, 0, 0);
  free(state->path);
  ret = close(state->fd);
  free(state);
  return (ret) ? (-1) : (err);
}


----------------------------
typedef struct gzFile_s *gzFile
----------------------------
***/


