int pnm_is_valid(const pnm_struct *pnm_ptr)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int height = pnm_ptr->height;
  unsigned int maxval = pnm_ptr->maxval;
  if ((((depth == 0) || (width == 0)) || (height == 0)) || (maxval == 0))
  {
    return 0;
  }
  switch (format)
  {
    case PNM_P1:

    case PNM_P4:
    {
      return ((depth == 1) && (maxval == 1)) ? (1) : (0);
    }

    case PNM_P2:

    case PNM_P5:
    {
      return (depth == 1) ? (1) : (0);
    }

    case PNM_P3:

    case PNM_P6:
    {
      return (depth == 3) ? (1) : (0);
    }

    case PNM_P7:
    {
      return 1;
    }

    default:
    {
      return 0;
    }

  }

}


/*** DEPENDENCIES:
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct
----------------------------
***/


size_t pnm_raw_sample_size(const pnm_struct *pnm_ptr)
{
  unsigned int maxval = pnm_ptr->maxval;
  if (maxval == 0)
  {
    errno = EINVAL;
  }
  if (maxval <= 0xffU)
  {
    return 1;
  }
  else
    if (maxval <= 0xffffU)
  {
    return 2;
  }
  else
    if (maxval <= 0xffffffU)
  {
    return 3;
  }
  else
    if (maxval <= 0xffffffffU)
  {
    return 4;
  }
  else
  {
    errno = EINVAL;
    return 0;
  }
}


/*** DEPENDENCIES:
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct
----------------------------
***/


size_t pnm_mem_size(const pnm_struct *pnm_ptr, size_t sample_size, unsigned int num_rows)
{
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  if (((sample_size == 0) || (depth == 0)) || (width == 0))
  {
    errno = EINVAL;
    return 0;
  }
  if (num_rows > (((((size_t) (-1)) / sample_size) / depth) / width))
  {
    errno = ERANGE;
    return 0;
  }
  return ((sample_size * depth) * width) * num_rows;
}


/*** DEPENDENCIES:
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct
----------------------------
***/


