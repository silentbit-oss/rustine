const char *zlibVersion(void)
{
  return "1.3-optipng";
}


/*** DEPENDENCIES:
***/


uLong zlibCompileFlags(void)
{
  uLong flags;
  flags = 0;
  switch ((int) (sizeof(uInt)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1;
      break;
    }

    case 8:
    {
      flags += 2;
      break;
    }

    default:
    {
      flags += 3;
    }

  }

  switch ((int) (sizeof(uLong)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1 << 2;
      break;
    }

    case 8:
    {
      flags += 2 << 2;
      break;
    }

    default:
    {
      flags += 3 << 2;
    }

  }

  switch ((int) (sizeof(voidpf)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1 << 4;
      break;
    }

    case 8:
    {
      flags += 2 << 4;
      break;
    }

    default:
    {
      flags += 3 << 4;
    }

  }

  switch ((int) (sizeof(off_t)))
  {
    case 2:
    {
      break;
    }

    case 4:
    {
      flags += 1 << 6;
      break;
    }

    case 8:
    {
      flags += 2 << 6;
      break;
    }

    default:
    {
      flags += 3 << 6;
    }

  }

  flags += 1L << 16;
  flags += 1L << 17;
  return flags;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
***/


const char *zError(int err)
{
  return z_errmsg[2 - err];
}


/*** DEPENDENCIES:
extern const char * const z_errmsg[10]
----------------------------
***/


voidpf zcalloc(voidpf opaque, unsigned items, unsigned size)
{
  (void) opaque;
  return ((sizeof(uInt)) > 2) ? ((voidpf) malloc(items * size)) : ((voidpf) calloc(items, size));
}


/*** DEPENDENCIES:
typedef void *voidpf
----------------------------
typedef void *voidp
----------------------------
***/


void zcfree(voidpf opaque, voidpf ptr)
{
  (void) opaque;
  free(ptr);
}


/*** DEPENDENCIES:
typedef void *voidpf
----------------------------
typedef void *voidp
----------------------------
***/


