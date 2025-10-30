typedef struct binn_struct binn
/*** DEPENDENCIES:
struct binn_struct
{
  int header;
  BOOL allocated;
  BOOL writable;
  BOOL dirty;
  void *pbuf;
  BOOL pre_allocated;
  int alloc_size;
  int used_size;
  int type;
  void *ptr;
  int size;
  int count;
  binn_mem_free freefn;
  union 
  {
    signed char vint8;
    signed short vint16;
    signed int vint32;
    int64 vint64;
    unsigned char vuint8;
    unsigned short vuint16;
    unsigned int vuint32;
    uint64 vuint64;
    signed char vchar;
    unsigned char vuchar;
    signed short vshort;
    unsigned short vushort;
    signed int vint;
    unsigned int vuint;
    float vfloat;
    double vdouble;
    BOOL vbool;
  };
  BOOL disable_int_compression;
}
----------------------------
***/


char *binn_version()
{
  return "3.0.0";
}


/*** DEPENDENCIES:
***/


int binn_create_type(int storage_type, int data_type_index)
{
  if (data_type_index < 0)
  {
    return -1;
  }
  if ((storage_type < 0x00) || (storage_type > 0xE0))
  {
    return -1;
  }
  if (data_type_index < 16)
  {
    return storage_type | data_type_index;
  }
  else
    if (data_type_index < 4096)
  {
    storage_type |= 0x10;
    storage_type <<= 8;
    data_type_index >>= 4;
    return storage_type | data_type_index;
  }
  else
    return -1;
}


/*** DEPENDENCIES:
***/


BOOL binn_is_struct(void *ptr)
{
  if (ptr == 0)
  {
    return 0;
  }
  if ((*((unsigned int *) ptr)) == 0x1F22B11F)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}


/*** DEPENDENCIES:
***/


static size_t strlen2(char *str)
{
  if (str == 0)
  {
    return 0;
  }
  return strlen(str);
}


/*** DEPENDENCIES:
***/


static int binn_get_ptr_type(void *ptr)
{
  if (ptr == 0)
  {
    return 0;
  }
  switch (*((unsigned int *) ptr))
  {
    case 0x1F22B11F:
    {
      return 1;
    }

    default:
    {
      return 2;
    }

  }

}


/*** DEPENDENCIES:
***/


static int CalcAllocation(int needed_size, int alloc_size)
{
  int calc_size;
  calc_size = alloc_size;
  while (calc_size < needed_size)
  {
    calc_size <<= 1;
  }

  return calc_size;
}


/*** DEPENDENCIES:
***/


static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


/*** DEPENDENCIES:
***/


static BOOL GetWriteConvertedData(int *ptype, void **ppvalue, int *psize)
{
  int type;
  float f1;
  double d1;
  char pstr[128];
  (void) pstr;
  (void) d1;
  (void) f1;
  type = *ptype;
  if ((*ppvalue) == 0)
  {
    switch (type)
    {
      case 0x00:

      case 0x01:

      case 0x02:
      {
        break;
      }

      case 0xA0:

      case 0xC0:
      {
        if ((*psize) == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  switch (type)
  {
    case 0xA4:

    case 0xA5:
    {
      return 1;
      break;
    }

    case 0xA2:

    case 0xA1:

    case 0xA3:
    {
      return 1;
      break;
    }

    case 0x80061:
    {
      if ((*(*((BOOL **) ppvalue))) == 0)
      {
        type = 0x02;
      }
      else
      {
        type = 0x01;
      }
      *ptype = type;
      break;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
***/


static int int_type(int type)
{
  switch (type)
  {
    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:
    {
      return 11;
    }

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 22;
    }

    default:
    {
      return 0;
    }

  }

}


/*** DEPENDENCIES:
***/


static BOOL copy_raw_value(void *psource, void *pdest, int data_store)
{
  switch (data_store)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pdest) = *((char *) psource);
      break;
    }

    case 0x40:
    {
      *((short *) pdest) = *((short *) psource);
      break;
    }

    case 0x60:
    {
      *((int *) pdest) = *((int *) psource);
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = *((uint64 *) psource);
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pdest) = (char *) psource;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
***/


static BOOL copy_float_value(void *psource, void *pdest, int source_type, int dest_type)
{
  switch (source_type)
  {
    case 0x62:
    {
      *((double *) pdest) = *((float *) psource);
      break;
    }

    case 0x82:
    {
      *((float *) pdest) = (float) (*((double *) psource));
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
***/


BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type)
{
  int storage_type;
  int extra_type;
  BOOL retval = 1;
  again:
  if (long_type < 0)
  {
    goto loc_invalid;
  }
  else
    if (long_type <= 0xff)
  {
    storage_type = long_type & 0xE0;
    extra_type = long_type & 0x0F;
  }
  else
    if (long_type <= 0xffff)
  {
    storage_type = long_type & 0xE000;
    storage_type >>= 8;
    extra_type = long_type & 0x0FFF;
    extra_type >>= 4;
  }
  else
    if (long_type & 0x80000)
  {
    long_type &= 0xffff;
    goto again;
  }
  else
  {
    loc_invalid:
    storage_type = -1;

    extra_type = -1;
    retval = 0;
  }

  if (pstorage_type)
  {
    *pstorage_type = storage_type;
  }
  if (pextra_type)
  {
    *pextra_type = extra_type;
  }
  return retval;
}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
***/


static void check_alloc_functions()
{
  if (malloc_fn == 0)
  {
    malloc_fn = &malloc;
  }
  if (realloc_fn == 0)
  {
    realloc_fn = &realloc;
  }
  if (free_fn == 0)
  {
    free_fn = &free;
  }
}


/*** DEPENDENCIES:
void *(*realloc_fn)(void *ptr, size_t len) = 0
----------------------------
void *(*malloc_fn)(size_t len) = 0
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


/*** DEPENDENCIES:
static void check_alloc_functions()
{
  if (malloc_fn == 0)
  {
    malloc_fn = &malloc;
  }
  if (realloc_fn == 0)
  {
    realloc_fn = &realloc;
  }
  if (free_fn == 0)
  {
    free_fn = &free;
  }
}


----------------------------
void *(*malloc_fn)(size_t len) = 0
----------------------------
***/


static binn *binn_alloc_item()
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (item)
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
    item->allocated = 1;
  }
  return item;
}


/*** DEPENDENCIES:
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


static void *binn_memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = binn_malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}


/*** DEPENDENCIES:
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
***/


binn *binn_value(int type, void *pvalue, int size, binn_mem_free freefn)
{
  int storage_type;
  binn *item = binn_alloc_item();
  if (item)
  {
    item->type = type;
    binn_get_type_info(type, &storage_type, 0);
    switch (storage_type)
    {
      case 0x00:
      {
        break;
      }

      case 0xA0:
      {
        if (size == 0)
        {
          size = strlen((char *) pvalue) + 1;
        }
      }

      case 0xC0:

      case 0xE0:
      {
        if (freefn == ((binn_mem_free) (-1)))
        {
          item->ptr = binn_memdup(pvalue, size);
          if (item->ptr == 0)
          {
            free_fn(item);
            return 0;
          }
          item->freefn = free_fn;
          if (storage_type == 0xA0)
          {
            size -= 1;
          }
        }
        else
        {
          item->ptr = pvalue;
          item->freefn = freefn;
        }
        item->size = size;
        break;
      }

      default:
      {
        item->ptr = &item->vint32;
        copy_raw_value(pvalue, item->ptr, storage_type);
      }

    }

  }
  return item;
}


/*** DEPENDENCIES:
typedef void (*binn_mem_free)(void *)
----------------------------
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type)
{
  int storage_type;
  int extra_type;
  BOOL retval = 1;
  again:
  if (long_type < 0)
  {
    goto loc_invalid;
  }
  else
    if (long_type <= 0xff)
  {
    storage_type = long_type & 0xE0;
    extra_type = long_type & 0x0F;
  }
  else
    if (long_type <= 0xffff)
  {
    storage_type = long_type & 0xE000;
    storage_type >>= 8;
    extra_type = long_type & 0x0FFF;
    extra_type >>= 4;
  }
  else
    if (long_type & 0x80000)
  {
    long_type &= 0xffff;
    goto again;
  }
  else
  {
    loc_invalid:
    storage_type = -1;

    extra_type = -1;
    retval = 0;
  }

  if (pstorage_type)
  {
    *pstorage_type = storage_type;
  }
  if (pextra_type)
  {
    *pextra_type = extra_type;
  }
  return retval;
}


----------------------------
static BOOL copy_raw_value(void *psource, void *pdest, int data_store)
{
  switch (data_store)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pdest) = *((char *) psource);
      break;
    }

    case 0x40:
    {
      *((short *) pdest) = *((short *) psource);
      break;
    }

    case 0x60:
    {
      *((int *) pdest) = *((int *) psource);
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = *((uint64 *) psource);
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pdest) = (char *) psource;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
static binn *binn_alloc_item()
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (item)
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
    item->allocated = 1;
  }
  return item;
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
typedef struct binn_struct binn
----------------------------
static void *binn_memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = binn_malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}


----------------------------
***/


int binn_get_read_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0x80061:

    case 0x01:

    case 0x02:
    {
      return 0x60;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


/*** DEPENDENCIES:
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type)
{
  int storage_type;
  int extra_type;
  BOOL retval = 1;
  again:
  if (long_type < 0)
  {
    goto loc_invalid;
  }
  else
    if (long_type <= 0xff)
  {
    storage_type = long_type & 0xE0;
    extra_type = long_type & 0x0F;
  }
  else
    if (long_type <= 0xffff)
  {
    storage_type = long_type & 0xE000;
    storage_type >>= 8;
    extra_type = long_type & 0x0FFF;
    extra_type >>= 4;
  }
  else
    if (long_type & 0x80000)
  {
    long_type &= 0xffff;
    goto again;
  }
  else
  {
    loc_invalid:
    storage_type = -1;

    extra_type = -1;
    retval = 0;
  }

  if (pstorage_type)
  {
    *pstorage_type = storage_type;
  }
  if (pextra_type)
  {
    *pextra_type = extra_type;
  }
  return retval;
}


----------------------------
***/


static void zero_value(void *pvalue, int type)
{
  switch (binn_get_read_storage(type))
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pvalue) = 0;
      break;
    }

    case 0x40:
    {
      *((short *) pvalue) = 0;
      break;
    }

    case 0x60:
    {
      *((int *) pvalue) = 0;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pvalue) = 0;
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pvalue) = 0;
      break;
    }

  }

}


/*** DEPENDENCIES:
int binn_get_read_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0x80061:

    case 0x01:

    case 0x02:
    {
      return 0x60;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


----------------------------
***/


static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


/*** DEPENDENCIES:
typedef unsigned int u32
----------------------------
***/


static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


/*** DEPENDENCIES:
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
***/


static BOOL binn_save_header(binn *item)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  int int32;
  int size;
  if (item == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + 9;
  size = (item->used_size - 9) + 3;
  if (item->count > 127)
  {
    p_idx -= 4;
    size += 3;
    int32 = item->count | 0x80000000;
    copy_be32((u32 *) p, (u32 *) (&int32));
  }
  else
  {
    p_idx -= 1;
    p[p_idx] = (unsigned char) item->count;
  }
  if (size > 127)
  {
    p_idx -= 4;
    size += 3;
    int32 = size | 0x80000000;
    copy_be32((u32 *) p, (u32 *) (&int32));
  }
  else
  {
    p_idx -= 1;
    p[p_idx] = (unsigned char) size;
  }
  p_idx -= 1;
  p[p_idx] = (unsigned char) item->type;
  item->ptr = &p[p_idx];
  item->size = size;
  (void) byte;
  item->dirty = 0;
  return 1;
}


/*** DEPENDENCIES:
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


/*** DEPENDENCIES:
static BOOL binn_save_header(binn *item)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  int int32;
  int size;
  if (item == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + 9;
  size = (item->used_size - 9) + 3;
  if (item->count > 127)
  {
    p_idx -= 4;
    size += 3;
    int32 = item->count | 0x80000000;
    copy_be32((u32 *) p, (u32 *) (&int32));
  }
  else
  {
    p_idx -= 1;
    p[p_idx] = (unsigned char) item->count;
  }
  if (size > 127)
  {
    p_idx -= 4;
    size += 3;
    int32 = size | 0x80000000;
    copy_be32((u32 *) p, (u32 *) (&int32));
  }
  else
  {
    p_idx -= 1;
    p[p_idx] = (unsigned char) size;
  }
  p_idx -= 1;
  p[p_idx] = (unsigned char) item->type;
  item->ptr = &p[p_idx];
  item->size = size;
  (void) byte;
  item->dirty = 0;
  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static int binn_get_ptr_type(void *ptr)
{
  if (ptr == 0)
  {
    return 0;
  }
  switch (*((unsigned int *) ptr))
  {
    case 0x1F22B11F:
    {
      return 1;
    }

    default:
    {
      return 2;
    }

  }

}


----------------------------
***/


static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


/*** DEPENDENCIES:
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
***/


static void copy_be16(u16 *pdest, u16 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[1];
  dest[1] = source[0];
}


/*** DEPENDENCIES:
typedef unsigned short int u16
----------------------------
***/


static void copy_be64(u64 *pdest, u64 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  int i;
  for (i = 0; i < 8; i += 1)
  {
    dest[i] = source[7 - i];
  }

}


/*** DEPENDENCIES:
typedef unsigned long long int u64
----------------------------
***/


static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
static void copy_be16(u16 *pdest, u16 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[1];
  dest[1] = source[0];
}


----------------------------
static void copy_be64(u64 *pdest, u64 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  int i;
  for (i = 0; i < 8; i += 1)
  {
    dest[i] = source[7 - i];
  }

}


----------------------------
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_list_get_value(void *ptr, int pos, binn *value)
{
  unsigned int ptr_idx = 0;
  int i;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE0)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  if ((pos <= 0) | (pos > count))
  {
    return 0;
  }
  pos -= 1;
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = (&p[p_idx]) + size;
  p_idx += header_size;
  for (i = 0; i < pos; i += 1)
  {
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      return 0;
    }
  }

  return GetValue(p, value);
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


----------------------------
***/


static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
static int int_type(int type)
{
  switch (type)
  {
    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:
    {
      return 11;
    }

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 22;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
typedef unsigned long long int uint64
----------------------------
***/


static BOOL copy_value(void *psource, void *pdest, int source_type, int dest_type, int data_store)
{
  if (type_family(source_type) != type_family(dest_type))
  {
    return 0;
  }
  if ((type_family(source_type) == 0xf2) && (source_type != dest_type))
  {
    return copy_int_value(psource, pdest, source_type, dest_type);
  }
  else
    if ((type_family(source_type) == 0xf3) && (source_type != dest_type))
  {
    return copy_float_value(psource, pdest, source_type, dest_type);
  }
  else
  {
    return copy_raw_value(psource, pdest, data_store);
  }
}


/*** DEPENDENCIES:
static BOOL copy_raw_value(void *psource, void *pdest, int data_store)
{
  switch (data_store)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pdest) = *((char *) psource);
      break;
    }

    case 0x40:
    {
      *((short *) pdest) = *((short *) psource);
      break;
    }

    case 0x60:
    {
      *((int *) pdest) = *((int *) psource);
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = *((uint64 *) psource);
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pdest) = (char *) psource;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
static BOOL copy_float_value(void *psource, void *pdest, int source_type, int dest_type)
{
  switch (source_type)
  {
    case 0x62:
    {
      *((double *) pdest) = *((float *) psource);
      break;
    }

    case 0x82:
    {
      *((float *) pdest) = (float) (*((double *) psource));
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
***/


BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


/*** DEPENDENCIES:
static void zero_value(void *pvalue, int type)
{
  switch (binn_get_read_storage(type))
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pvalue) = 0;
      break;
    }

    case 0x40:
    {
      *((short *) pvalue) = 0;
      break;
    }

    case 0x60:
    {
      *((int *) pvalue) = 0;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pvalue) = 0;
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pvalue) = 0;
      break;
    }

  }

}


----------------------------
BOOL binn_list_get_value(void *ptr, int pos, binn *value)
{
  unsigned int ptr_idx = 0;
  int i;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE0)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  if ((pos <= 0) | (pos > count))
  {
    return 0;
  }
  pos -= 1;
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = (&p[p_idx]) + size;
  p_idx += header_size;
  for (i = 0; i < pos; i += 1)
  {
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      return 0;
    }
  }

  return GetValue(p, value);
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL copy_value(void *psource, void *pdest, int source_type, int dest_type, int data_store)
{
  if (type_family(source_type) != type_family(dest_type))
  {
    return 0;
  }
  if ((type_family(source_type) == 0xf2) && (source_type != dest_type))
  {
    return copy_int_value(psource, pdest, source_type, dest_type);
  }
  else
    if ((type_family(source_type) == 0xf3) && (source_type != dest_type))
  {
    return copy_float_value(psource, pdest, source_type, dest_type);
  }
  else
  {
    return copy_raw_value(psource, pdest, data_store);
  }
}


----------------------------
int binn_get_read_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0x80061:

    case 0x01:

    case 0x02:
    {
      return 0x60;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


----------------------------
***/


static int read_map_id(unsigned char **pp, unsigned char *plimit)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char c;
  unsigned char sign;
  unsigned char type;
  int id;
  int extra_bytes;
  p_idx = *pp;
  c = p[p_idx];
  p_idx += 1;
  if (c & 0x80)
  {
    extra_bytes = ((c & 0x60) >> 5) + 1;
    if (((&p[p_idx]) + extra_bytes) > plimit)
    {
      *pp = (&p[p_idx]) + extra_bytes;
      return 0;
    }
  }
  type = c & 0xE0;
  sign = c & 0x10;
  if ((c & 0x80) == 0)
  {
    sign = c & 0x40;
    id = c & 0x3F;
  }
  else
    if (type == 0x80)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
  }
  else
    if (type == 0xA0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xC0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xE0)
  {
    copy_be32((u32 *) (&id), (u32 *) p);
    p_idx += 4;
  }
  else
  {
    *pp = plimit + 2;
    return 0;
  }
  if (sign)
  {
    id = -id;
  }
  *pp = &p[p_idx];
  return id;
}


/*** DEPENDENCIES:
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
***/


static unsigned char *SearchForID(unsigned char *p, int header_size, int size, int numitems, int id)
{
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  int i;
  int int32;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < numitems; i += 1)
  {
    int32 = read_map_id(&(&p[p_idx]), plimit);
    if ((&p[p_idx]) > (&plimit[plimit_idx]))
    {
      break;
    }
    if (int32 == id)
    {
      return p;
    }
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      break;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
static int read_map_id(unsigned char **pp, unsigned char *plimit)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char c;
  unsigned char sign;
  unsigned char type;
  int id;
  int extra_bytes;
  p_idx = *pp;
  c = p[p_idx];
  p_idx += 1;
  if (c & 0x80)
  {
    extra_bytes = ((c & 0x60) >> 5) + 1;
    if (((&p[p_idx]) + extra_bytes) > plimit)
    {
      *pp = (&p[p_idx]) + extra_bytes;
      return 0;
    }
  }
  type = c & 0xE0;
  sign = c & 0x10;
  if ((c & 0x80) == 0)
  {
    sign = c & 0x40;
    id = c & 0x3F;
  }
  else
    if (type == 0x80)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
  }
  else
    if (type == 0xA0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xC0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xE0)
  {
    copy_be32((u32 *) (&id), (u32 *) p);
    p_idx += 4;
  }
  else
  {
    *pp = plimit + 2;
    return 0;
  }
  if (sign)
  {
    id = -id;
  }
  *pp = &p[p_idx];
  return id;
}


----------------------------
***/


BOOL binn_map_get_value(void *ptr, int id, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE1)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForID(p_idx, header_size, size, count, id);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
static unsigned char *SearchForID(unsigned char *p, int header_size, int size, int numitems, int id)
{
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  int i;
  int int32;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < numitems; i += 1)
  {
    int32 = read_map_id(&(&p[p_idx]), plimit);
    if ((&p[p_idx]) > (&plimit[plimit_idx]))
    {
      break;
    }
    if (int32 == id)
    {
      return p;
    }
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      break;
    }
  }

  return 0;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


----------------------------
***/


BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


/*** DEPENDENCIES:
static void zero_value(void *pvalue, int type)
{
  switch (binn_get_read_storage(type))
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pvalue) = 0;
      break;
    }

    case 0x40:
    {
      *((short *) pvalue) = 0;
      break;
    }

    case 0x60:
    {
      *((int *) pvalue) = 0;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pvalue) = 0;
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pvalue) = 0;
      break;
    }

  }

}


----------------------------
BOOL binn_map_get_value(void *ptr, int id, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE1)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForID(p_idx, header_size, size, count, id);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL copy_value(void *psource, void *pdest, int source_type, int dest_type, int data_store)
{
  if (type_family(source_type) != type_family(dest_type))
  {
    return 0;
  }
  if ((type_family(source_type) == 0xf2) && (source_type != dest_type))
  {
    return copy_int_value(psource, pdest, source_type, dest_type);
  }
  else
    if ((type_family(source_type) == 0xf3) && (source_type != dest_type))
  {
    return copy_float_value(psource, pdest, source_type, dest_type);
  }
  else
  {
    return copy_raw_value(psource, pdest, data_store);
  }
}


----------------------------
int binn_get_read_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0x80061:

    case 0x01:

    case 0x02:
    {
      return 0x60;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


----------------------------
***/


static unsigned char *SearchForKey(unsigned char *p, int header_size, int size, int numitems, const char *key)
{
  unsigned int p_idx = 0;
  unsigned char len;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  int i;
  int keylen;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  keylen = strlen(key);
  for (i = 0; i < numitems; i += 1)
  {
    len = *((unsigned char *) p);
    p_idx += 1;
    if ((&p[p_idx]) > (&plimit[plimit_idx]))
    {
      break;
    }
    if (len > 0)
    {
      if (strncasecmp((char *) p, key, len) == 0)
      {
        if (keylen == len)
        {
          p_idx += len;
          return p;
        }
      }
      p_idx += len;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        break;
      }
    }
    else
      if (len == keylen)
    {
      return p;
    }
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      break;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
***/


BOOL binn_object_get_value(void *ptr, const char *key, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if ((((&ptr[ptr_idx]) == 0) || (key == 0)) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE2)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForKey(p_idx, header_size, size, count, key);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
static unsigned char *SearchForKey(unsigned char *p, int header_size, int size, int numitems, const char *key)
{
  unsigned int p_idx = 0;
  unsigned char len;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  int i;
  int keylen;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  keylen = strlen(key);
  for (i = 0; i < numitems; i += 1)
  {
    len = *((unsigned char *) p);
    p_idx += 1;
    if ((&p[p_idx]) > (&plimit[plimit_idx]))
    {
      break;
    }
    if (len > 0)
    {
      if (strncasecmp((char *) p, key, len) == 0)
      {
        if (keylen == len)
        {
          p_idx += len;
          return p;
        }
      }
      p_idx += len;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        break;
      }
    }
    else
      if (len == keylen)
    {
      return p;
    }
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      break;
    }
  }

  return 0;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


----------------------------
***/


BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


/*** DEPENDENCIES:
static void zero_value(void *pvalue, int type)
{
  switch (binn_get_read_storage(type))
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) pvalue) = 0;
      break;
    }

    case 0x40:
    {
      *((short *) pvalue) = 0;
      break;
    }

    case 0x60:
    {
      *((int *) pvalue) = 0;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pvalue) = 0;
      break;
    }

    case 0xC0:

    case 0xA0:

    case 0xE0:
    {
      *((char **) pvalue) = 0;
      break;
    }

  }

}


----------------------------
BOOL binn_object_get_value(void *ptr, const char *key, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if ((((&ptr[ptr_idx]) == 0) || (key == 0)) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE2)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForKey(p_idx, header_size, size, count, key);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL copy_value(void *psource, void *pdest, int source_type, int dest_type, int data_store)
{
  if (type_family(source_type) != type_family(dest_type))
  {
    return 0;
  }
  if ((type_family(source_type) == 0xf2) && (source_type != dest_type))
  {
    return copy_int_value(psource, pdest, source_type, dest_type);
  }
  else
    if ((type_family(source_type) == 0xf3) && (source_type != dest_type))
  {
    return copy_float_value(psource, pdest, source_type, dest_type);
  }
  else
  {
    return copy_raw_value(psource, pdest, data_store);
  }
}


----------------------------
int binn_get_read_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0x80061:

    case 0x01:

    case 0x02:
    {
      return 0x60;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


----------------------------
***/


BOOL binn_is_valid_ex(void *ptr, int *ptype, int *pcount, int *psize)
{
  int i;
  int type;
  int count;
  int size;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char len;
  void *pbuf;
  unsigned int pbuf_idx = 0;
  pbuf_idx = binn_ptr(ptr);
  if ((&pbuf[pbuf_idx]) == 0)
  {
    return 0;
  }
  if (psize && ((*psize) > 0))
  {
    size = *psize;
  }
  else
  {
    size = 0;
  }
  if (!IsValidBinnHeader(pbuf, &type, &count, &size, &header_size))
  {
    return 0;
  }
  if (psize && ((*psize) > 0))
  {
    if (size != (*psize))
    {
      return 0;
    }
  }
  if (pcount && ((*pcount) > 0))
  {
    if (count != (*pcount))
    {
      return 0;
    }
  }
  if (ptype && ((*ptype) != 0))
  {
    if (type != (*ptype))
    {
      return 0;
    }
  }
  p_idx = (unsigned char *) pbuf;
  base_idx = &p[p_idx];
  plimit_idx = (&p[p_idx]) + size;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    switch (type)
    {
      case 0xE2:
      {
        len = p[p_idx];
        p_idx += 1;
        p_idx += len;
        break;
      }

      case 0xE1:
      {
        read_map_id(&(&p[p_idx]), plimit);
        break;
      }

    }

    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      goto Invalid;
    }
  }

  if (ptype && ((*ptype) == 0))
  {
    *ptype = type;
  }
  if (pcount && ((*pcount) == 0))
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  return 1;
  Invalid:
  return 0;

}


/*** DEPENDENCIES:
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
static int read_map_id(unsigned char **pp, unsigned char *plimit)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char c;
  unsigned char sign;
  unsigned char type;
  int id;
  int extra_bytes;
  p_idx = *pp;
  c = p[p_idx];
  p_idx += 1;
  if (c & 0x80)
  {
    extra_bytes = ((c & 0x60) >> 5) + 1;
    if (((&p[p_idx]) + extra_bytes) > plimit)
    {
      *pp = (&p[p_idx]) + extra_bytes;
      return 0;
    }
  }
  type = c & 0xE0;
  sign = c & 0x10;
  if ((c & 0x80) == 0)
  {
    sign = c & 0x40;
    id = c & 0x3F;
  }
  else
    if (type == 0x80)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
  }
  else
    if (type == 0xA0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xC0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xE0)
  {
    copy_be32((u32 *) (&id), (u32 *) p);
    p_idx += 4;
  }
  else
  {
    *pp = plimit + 2;
    return 0;
  }
  if (sign)
  {
    id = -id;
  }
  *pp = &p[p_idx];
  return id;
}


----------------------------
***/


int64 atoi64(char *str)
{
  unsigned int str_idx = 0;
  int64 retval;
  int is_negative = 0;
  if (str[str_idx] == '-')
  {
    is_negative = 1;
    str_idx += 1;
  }
  retval = 0;
  for (; str[str_idx]; str_idx += 1)
  {
    retval = (10 * retval) + (str[str_idx] - '0');
  }

  if (is_negative)
  {
    retval *= -1;
  }
  return retval;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
***/


int binn_get_write_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0xA6:

    case 0xA7:
    {
      return 0xA0;
    }

    case 0x80061:
    {
      return 0x00;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


/*** DEPENDENCIES:
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type)
{
  int storage_type;
  int extra_type;
  BOOL retval = 1;
  again:
  if (long_type < 0)
  {
    goto loc_invalid;
  }
  else
    if (long_type <= 0xff)
  {
    storage_type = long_type & 0xE0;
    extra_type = long_type & 0x0F;
  }
  else
    if (long_type <= 0xffff)
  {
    storage_type = long_type & 0xE000;
    storage_type >>= 8;
    extra_type = long_type & 0x0FFF;
    extra_type >>= 4;
  }
  else
    if (long_type & 0x80000)
  {
    long_type &= 0xffff;
    goto again;
  }
  else
  {
    loc_invalid:
    storage_type = -1;

    extra_type = -1;
    retval = 0;
  }

  if (pstorage_type)
  {
    *pstorage_type = storage_type;
  }
  if (pextra_type)
  {
    *pextra_type = extra_type;
  }
  return retval;
}


----------------------------
***/


BOOL binn_is_container(binn *item)
{
  if (item == 0)
  {
    return 0;
  }
  switch (item->type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
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
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_create(binn *item, int type, int size, void *pointer)
{
  unsigned int pointer_idx = 0;
  BOOL retval = 0;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      goto loc_exit;
    }

  }

  if ((item == 0) || (size < 0))
  {
    goto loc_exit;
  }
  if (size < 3)
  {
    if (pointer)
    {
      goto loc_exit;
    }
    else
      size = 0;
  }
  memset(item, 0, sizeof(binn));
  if (pointer)
  {
    item->pre_allocated = 1;
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  else
  {
    item->pre_allocated = 0;
    if (size == 0)
    {
      size = 256;
    }
    pointer_idx = binn_malloc(size);
    if ((&pointer[pointer_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  item->header = 0x1F22B11F;
  item->writable = 1;
  item->used_size = 9;
  item->type = type;
  item->dirty = 1;
  retval = 1;
  loc_exit:
  return retval;

}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


binn *binn_new(int type, int size, void *pointer)
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_create(item, type, size, pointer) == 0)
  {
    free_fn(item);
    return 0;
  }
  item->allocated = 1;
  return item;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
BOOL binn_create(binn *item, int type, int size, void *pointer)
{
  unsigned int pointer_idx = 0;
  BOOL retval = 0;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      goto loc_exit;
    }

  }

  if ((item == 0) || (size < 0))
  {
    goto loc_exit;
  }
  if (size < 3)
  {
    if (pointer)
    {
      goto loc_exit;
    }
    else
      size = 0;
  }
  memset(item, 0, sizeof(binn));
  if (pointer)
  {
    item->pre_allocated = 1;
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  else
  {
    item->pre_allocated = 0;
    if (size == 0)
    {
      size = 256;
    }
    pointer_idx = binn_malloc(size);
    if ((&pointer[pointer_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  item->header = 0x1F22B11F;
  item->writable = 1;
  item->used_size = 9;
  item->type = type;
  item->dirty = 1;
  retval = 1;
  loc_exit:
  return retval;

}


----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


binn *binn_list()
{
  return binn_new(0xE0, 0, 0);
}


/*** DEPENDENCIES:
binn *binn_new(int type, int size, void *pointer)
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_create(item, type, size, pointer) == 0)
  {
    free_fn(item);
    return 0;
  }
  item->allocated = 1;
  return item;
}


----------------------------
***/


binn *binn_map()
{
  return binn_new(0xE1, 0, 0);
}


/*** DEPENDENCIES:
binn *binn_new(int type, int size, void *pointer)
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_create(item, type, size, pointer) == 0)
  {
    free_fn(item);
    return 0;
  }
  item->allocated = 1;
  return item;
}


----------------------------
***/


binn *binn_object()
{
  return binn_new(0xE2, 0, 0);
}


/*** DEPENDENCIES:
binn *binn_new(int type, int size, void *pointer)
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_create(item, type, size, pointer) == 0)
  {
    free_fn(item);
    return 0;
  }
  item->allocated = 1;
  return item;
}


----------------------------
***/


BOOL binn_is_valid(void *ptr, int *ptype, int *pcount, int *psize)
{
  if (ptype)
  {
    *ptype = 0;
  }
  if (pcount)
  {
    *pcount = 0;
  }
  if (psize)
  {
    *psize = 0;
  }
  return binn_is_valid_ex(ptr, ptype, pcount, psize);
}


/*** DEPENDENCIES:
BOOL binn_is_valid_ex(void *ptr, int *ptype, int *pcount, int *psize)
{
  int i;
  int type;
  int count;
  int size;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char len;
  void *pbuf;
  unsigned int pbuf_idx = 0;
  pbuf_idx = binn_ptr(ptr);
  if ((&pbuf[pbuf_idx]) == 0)
  {
    return 0;
  }
  if (psize && ((*psize) > 0))
  {
    size = *psize;
  }
  else
  {
    size = 0;
  }
  if (!IsValidBinnHeader(pbuf, &type, &count, &size, &header_size))
  {
    return 0;
  }
  if (psize && ((*psize) > 0))
  {
    if (size != (*psize))
    {
      return 0;
    }
  }
  if (pcount && ((*pcount) > 0))
  {
    if (count != (*pcount))
    {
      return 0;
    }
  }
  if (ptype && ((*ptype) != 0))
  {
    if (type != (*ptype))
    {
      return 0;
    }
  }
  p_idx = (unsigned char *) pbuf;
  base_idx = &p[p_idx];
  plimit_idx = (&p[p_idx]) + size;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    switch (type)
    {
      case 0xE2:
      {
        len = p[p_idx];
        p_idx += 1;
        p_idx += len;
        break;
      }

      case 0xE1:
      {
        read_map_id(&(&p[p_idx]), plimit);
        break;
      }

    }

    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      goto Invalid;
    }
  }

  if (ptype && ((*ptype) == 0))
  {
    *ptype = type;
  }
  if (pcount && ((*pcount) == 0))
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  return 1;
  Invalid:
  return 0;

}


----------------------------
***/


signed char binn_list_int8(void *list, int pos)
{
  signed char value;
  binn_list_get(list, pos, 0x21, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


short binn_list_int16(void *list, int pos)
{
  short value;
  binn_list_get(list, pos, 0x41, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


int binn_list_int32(void *list, int pos)
{
  int value;
  binn_list_get(list, pos, 0x61, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned char binn_list_uint8(void *list, int pos)
{
  unsigned char value;
  binn_list_get(list, pos, 0x20, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned short binn_list_uint16(void *list, int pos)
{
  unsigned short value;
  binn_list_get(list, pos, 0x40, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned int binn_list_uint32(void *list, int pos)
{
  unsigned int value;
  binn_list_get(list, pos, 0x60, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


float binn_list_float(void *list, int pos)
{
  float value;
  binn_list_get(list, pos, 0x62, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


double binn_list_double(void *list, int pos)
{
  double value;
  binn_list_get(list, pos, 0x82, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_list_null(void *list, int pos)
{
  return binn_list_get(list, pos, 0x00, 0, 0);
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


char *binn_list_str(void *list, int pos)
{
  char *value;
  binn_list_get(list, pos, 0xA0, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_list_blob(void *list, int pos, int *psize)
{
  void *value;
  binn_list_get(list, pos, 0xC0, &value, psize);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_list_list(void *list, int pos)
{
  void *value;
  binn_list_get(list, pos, 0xE0, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_list_map(void *list, int pos)
{
  void *value;
  binn_list_get(list, pos, 0xE1, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_list_object(void *list, int pos)
{
  void *value;
  binn_list_get(list, pos, 0xE2, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


signed char binn_map_int8(void *map, int id)
{
  signed char value;
  binn_map_get(map, id, 0x21, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


short binn_map_int16(void *map, int id)
{
  short value;
  binn_map_get(map, id, 0x41, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


int binn_map_int32(void *map, int id)
{
  int value;
  binn_map_get(map, id, 0x61, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned char binn_map_uint8(void *map, int id)
{
  unsigned char value;
  binn_map_get(map, id, 0x20, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned short binn_map_uint16(void *map, int id)
{
  unsigned short value;
  binn_map_get(map, id, 0x40, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned int binn_map_uint32(void *map, int id)
{
  unsigned int value;
  binn_map_get(map, id, 0x60, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


float binn_map_float(void *map, int id)
{
  float value;
  binn_map_get(map, id, 0x62, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


double binn_map_double(void *map, int id)
{
  double value;
  binn_map_get(map, id, 0x82, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_map_null(void *map, int id)
{
  return binn_map_get(map, id, 0x00, 0, 0);
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


char *binn_map_str(void *map, int id)
{
  char *value;
  binn_map_get(map, id, 0xA0, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_map_blob(void *map, int id, int *psize)
{
  void *value;
  binn_map_get(map, id, 0xC0, &value, psize);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_map_list(void *map, int id)
{
  void *value;
  binn_map_get(map, id, 0xE0, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_map_map(void *map, int id)
{
  void *value;
  binn_map_get(map, id, 0xE1, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_map_object(void *map, int id)
{
  void *value;
  binn_map_get(map, id, 0xE2, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


signed char binn_object_int8(void *obj, const char *key)
{
  signed char value;
  binn_object_get(obj, key, 0x21, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


short binn_object_int16(void *obj, const char *key)
{
  short value;
  binn_object_get(obj, key, 0x41, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


int binn_object_int32(void *obj, const char *key)
{
  int value;
  binn_object_get(obj, key, 0x61, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned char binn_object_uint8(void *obj, const char *key)
{
  unsigned char value;
  binn_object_get(obj, key, 0x20, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned short binn_object_uint16(void *obj, const char *key)
{
  unsigned short value;
  binn_object_get(obj, key, 0x40, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


unsigned int binn_object_uint32(void *obj, const char *key)
{
  unsigned int value;
  binn_object_get(obj, key, 0x60, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


float binn_object_float(void *obj, const char *key)
{
  float value;
  binn_object_get(obj, key, 0x62, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


double binn_object_double(void *obj, const char *key)
{
  double value;
  binn_object_get(obj, key, 0x82, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_object_null(void *obj, const char *key)
{
  return binn_object_get(obj, key, 0x00, 0, 0);
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


char *binn_object_str(void *obj, const char *key)
{
  char *value;
  binn_object_get(obj, key, 0xA0, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_object_blob(void *obj, const char *key, int *psize)
{
  void *value;
  binn_object_get(obj, key, 0xC0, &value, psize);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_object_list(void *obj, const char *key)
{
  void *value;
  binn_object_get(obj, key, 0xE0, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_object_map(void *obj, const char *key)
{
  void *value;
  binn_object_get(obj, key, 0xE1, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


void *binn_object_object(void *obj, const char *key)
{
  void *value;
  binn_object_get(obj, key, 0xE2, &value, 0);
  return value;
}


/*** DEPENDENCIES:
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


static int binn_buf_type(void *pbuf)
{
  int type;
  if (!IsValidBinnHeader(pbuf, &type, 0, 0, 0))
  {
    return 0;
  }
  return type;
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
***/


static int binn_buf_count(void *pbuf)
{
  int nitems;
  if (!IsValidBinnHeader(pbuf, 0, &nitems, 0, 0))
  {
    return 0;
  }
  return nitems;
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
***/


static int binn_buf_size(void *pbuf)
{
  int size = 0;
  if (!IsValidBinnHeader(pbuf, 0, 0, &size, 0))
  {
    return 0;
  }
  return size;
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
***/


static BOOL is_integer(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] < '0') || (p[p_idx] > '9'))
    {
      retval = 0;
    }
  }

  return retval;
}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
***/


static BOOL is_float(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  BOOL number_found = 0;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] == '.') || (p[p_idx] == ','))
    {
      if (!number_found)
      {
        retval = 0;
      }
    }
    else
      if ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
    {
      number_found = 1;
    }
    else
    {
      return 0;
    }
  }

  return retval;
}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
***/


static void *compress_int(int *pstorage_type, int *ptype, void *psource)
{
  int storage_type;
  int storage_type2;
  int type;
  int type2 = 0;
  int64 vint = 0;
  uint64 vuint;
  char *pvalue;
  unsigned int pvalue_idx = 0;
  storage_type = *pstorage_type;
  if (storage_type == 0x20)
  {
    return psource;
  }
  type = *ptype;
  switch (type)
  {
    case 0x81:
    {
      vint = *((int64 *) psource);
      goto loc_signed;
    }

    case 0x61:
    {
      vint = *((int *) psource);
      goto loc_signed;
    }

    case 0x41:
    {
      vint = *((short *) psource);
      goto loc_signed;
    }

    case 0x80:
    {
      vuint = *((uint64 *) psource);
      goto loc_positive;
    }

    case 0x60:
    {
      vuint = *((unsigned int *) psource);
      goto loc_positive;
    }

    case 0x40:
    {
      vuint = *((unsigned short *) psource);
      goto loc_positive;
    }

  }

  loc_signed:
  if (vint >= 0)
  {
    vuint = vint;
    goto loc_positive;
  }

  if (vint >= INT8_MIN)
  {
    type2 = 0x21;
  }
  else
    if (vint >= INT16_MIN)
  {
    type2 = 0x41;
  }
  else
    if (vint >= INT32_MIN)
  {
    type2 = 0x61;
  }
  goto loc_exit;
  loc_positive:
  if (vuint <= UINT8_MAX)
  {
    type2 = 0x20;
  }
  else
    if (vuint <= UINT16_MAX)
  {
    type2 = 0x40;
  }
  else
    if (vuint <= UINT32_MAX)
  {
    type2 = 0x60;
  }

  loc_exit:
  pvalue_idx = (char *) psource;

  if (type2 && (type2 != type))
  {
    *ptype = type2;
    storage_type2 = binn_get_write_storage(type2);
    *pstorage_type = storage_type2;
  }
  return pvalue;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
int binn_get_write_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0xA6:

    case 0xA7:
    {
      return 0xA0;
    }

    case 0x80061:
    {
      return 0x00;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


----------------------------
typedef unsigned long long int uint64
----------------------------
***/


static BOOL CheckAllocation(binn *item, int add_size)
{
  int alloc_size;
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((item->used_size + add_size) > item->alloc_size)
  {
    if (item->pre_allocated)
    {
      return 0;
    }
    alloc_size = CalcAllocation(item->used_size + add_size, item->alloc_size);
    ptr_idx = realloc_fn(item->pbuf, alloc_size);
    if ((&ptr[ptr_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &ptr[ptr_idx];
    item->alloc_size = alloc_size;
  }
  return 1;
}


/*** DEPENDENCIES:
void *(*realloc_fn)(void *ptr, size_t len) = 0
----------------------------
static int CalcAllocation(int needed_size, int alloc_size)
{
  int calc_size;
  calc_size = alloc_size;
  while (calc_size < needed_size)
  {
    calc_size <<= 1;
  }

  return calc_size;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


static BOOL AddValue(binn *item, int type, void *pvalue, int size)
{
  unsigned int pvalue_idx = 0;
  int int32;
  int ArgSize;
  int storage_type;
  int extra_type;
  unsigned char *p;
  unsigned int p_idx = 0;
  binn_get_type_info(type, &storage_type, &extra_type);
  if ((&pvalue[pvalue_idx]) == 0)
  {
    switch (storage_type)
    {
      case 0x00:
      {
        break;
      }

      case 0xC0:

      case 0xA0:
      {
        if (size == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  if ((type_family(type) == 0xf2) && (item->disable_int_compression == 0))
  {
    pvalue_idx = compress_int(&storage_type, &type, pvalue_idx);
  }
  switch (storage_type)
  {
    case 0x00:
    {
      size = 0;
      ArgSize = size;
      break;
    }

    case 0x20:
    {
      size = 1;
      ArgSize = size;
      break;
    }

    case 0x40:
    {
      size = 2;
      ArgSize = size;
      break;
    }

    case 0x60:
    {
      size = 4;
      ArgSize = size;
      break;
    }

    case 0x80:
    {
      size = 8;
      ArgSize = size;
      break;
    }

    case 0xC0:
    {
      if (size < 0)
      {
        return 0;
      }
      ArgSize = size + 4;
      break;
    }

    case 0xA0:
    {
      if (size < 0)
      {
        return 0;
      }
      if (size == 0)
      {
        size = strlen2((char *) pvalue);
      }
      ArgSize = size + 5;
      break;
    }

    case 0xE0:
    {
      if (size <= 0)
      {
        return 0;
      }
      ArgSize = size;
      break;
    }

    default:
    {
      return 0;
    }

  }

  ArgSize += 2;
  if (CheckAllocation(item, ArgSize) == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + item->used_size;
  if (storage_type != 0xE0)
  {
    if (type > 255)
    {
      u16 type16 = type;
      copy_be16((u16 *) p, (u16 *) (&type16));
      p_idx += 2;
      item->used_size += 2;
    }
    else
    {
      p[p_idx] = type;
      p_idx += 1;
      item->used_size += 1;
    }
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) p) = *((char *) pvalue);
      item->used_size += 1;
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) p, (u16 *) pvalue);
      item->used_size += 2;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) p, (u32 *) pvalue);
      item->used_size += 4;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) p, (u64 *) pvalue);
      item->used_size += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if (size > 127)
      {
        int32 = size | 0x80000000;
        copy_be32((u32 *) p, (u32 *) (&int32));
        p_idx += 4;
        item->used_size += 4;
      }
      else
      {
        *((unsigned char *) p) = size;
        p_idx += 1;
        item->used_size += 1;
      }
      memcpy(p, pvalue, size);
      if (storage_type == 0xA0)
      {
        p_idx += size;
        *((char *) p) = (char) 0;
        size += 1;
      }
      item->used_size += size;
      break;
    }

    case 0xE0:
    {
      memcpy(p, pvalue, size);
      item->used_size += size;
      break;
    }

  }

  item->dirty = 1;
  return 1;
}


/*** DEPENDENCIES:
static void copy_be16(u16 *pdest, u16 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[1];
  dest[1] = source[0];
}


----------------------------
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
static void copy_be64(u64 *pdest, u64 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  int i;
  for (i = 0; i < 8; i += 1)
  {
    dest[i] = source[7 - i];
  }

}


----------------------------
static void *compress_int(int *pstorage_type, int *ptype, void *psource)
{
  int storage_type;
  int storage_type2;
  int type;
  int type2 = 0;
  int64 vint = 0;
  uint64 vuint;
  char *pvalue;
  unsigned int pvalue_idx = 0;
  storage_type = *pstorage_type;
  if (storage_type == 0x20)
  {
    return psource;
  }
  type = *ptype;
  switch (type)
  {
    case 0x81:
    {
      vint = *((int64 *) psource);
      goto loc_signed;
    }

    case 0x61:
    {
      vint = *((int *) psource);
      goto loc_signed;
    }

    case 0x41:
    {
      vint = *((short *) psource);
      goto loc_signed;
    }

    case 0x80:
    {
      vuint = *((uint64 *) psource);
      goto loc_positive;
    }

    case 0x60:
    {
      vuint = *((unsigned int *) psource);
      goto loc_positive;
    }

    case 0x40:
    {
      vuint = *((unsigned short *) psource);
      goto loc_positive;
    }

  }

  loc_signed:
  if (vint >= 0)
  {
    vuint = vint;
    goto loc_positive;
  }

  if (vint >= INT8_MIN)
  {
    type2 = 0x21;
  }
  else
    if (vint >= INT16_MIN)
  {
    type2 = 0x41;
  }
  else
    if (vint >= INT32_MIN)
  {
    type2 = 0x61;
  }
  goto loc_exit;
  loc_positive:
  if (vuint <= UINT8_MAX)
  {
    type2 = 0x20;
  }
  else
    if (vuint <= UINT16_MAX)
  {
    type2 = 0x40;
  }
  else
    if (vuint <= UINT32_MAX)
  {
    type2 = 0x60;
  }

  loc_exit:
  pvalue_idx = (char *) psource;

  if (type2 && (type2 != type))
  {
    *ptype = type2;
    storage_type2 = binn_get_write_storage(type2);
    *pstorage_type = storage_type2;
  }
  return pvalue;
}


----------------------------
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type)
{
  int storage_type;
  int extra_type;
  BOOL retval = 1;
  again:
  if (long_type < 0)
  {
    goto loc_invalid;
  }
  else
    if (long_type <= 0xff)
  {
    storage_type = long_type & 0xE0;
    extra_type = long_type & 0x0F;
  }
  else
    if (long_type <= 0xffff)
  {
    storage_type = long_type & 0xE000;
    storage_type >>= 8;
    extra_type = long_type & 0x0FFF;
    extra_type >>= 4;
  }
  else
    if (long_type & 0x80000)
  {
    long_type &= 0xffff;
    goto again;
  }
  else
  {
    loc_invalid:
    storage_type = -1;

    extra_type = -1;
    retval = 0;
  }

  if (pstorage_type)
  {
    *pstorage_type = storage_type;
  }
  if (pextra_type)
  {
    *pextra_type = extra_type;
  }
  return retval;
}


----------------------------
typedef unsigned short int u16
----------------------------
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL CheckAllocation(binn *item, int add_size)
{
  int alloc_size;
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((item->used_size + add_size) > item->alloc_size)
  {
    if (item->pre_allocated)
    {
      return 0;
    }
    alloc_size = CalcAllocation(item->used_size + add_size, item->alloc_size);
    ptr_idx = realloc_fn(item->pbuf, alloc_size);
    if ((&ptr[ptr_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &ptr[ptr_idx];
    item->alloc_size = alloc_size;
  }
  return 1;
}


----------------------------
static size_t strlen2(char *str)
{
  if (str == 0)
  {
    return 0;
  }
  return strlen(str);
}


----------------------------
***/


static BOOL binn_list_add_raw(binn *item, int type, void *pvalue, int size)
{
  if (((item == 0) || (item->type != 0xE0)) || (item->writable == 0))
  {
    return 0;
  }
  if (AddValue(item, type, pvalue, size) == 0)
  {
    return 0;
  }
  item->count += 1;
  return 1;
}


/*** DEPENDENCIES:
static BOOL AddValue(binn *item, int type, void *pvalue, int size)
{
  unsigned int pvalue_idx = 0;
  int int32;
  int ArgSize;
  int storage_type;
  int extra_type;
  unsigned char *p;
  unsigned int p_idx = 0;
  binn_get_type_info(type, &storage_type, &extra_type);
  if ((&pvalue[pvalue_idx]) == 0)
  {
    switch (storage_type)
    {
      case 0x00:
      {
        break;
      }

      case 0xC0:

      case 0xA0:
      {
        if (size == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  if ((type_family(type) == 0xf2) && (item->disable_int_compression == 0))
  {
    pvalue_idx = compress_int(&storage_type, &type, pvalue_idx);
  }
  switch (storage_type)
  {
    case 0x00:
    {
      size = 0;
      ArgSize = size;
      break;
    }

    case 0x20:
    {
      size = 1;
      ArgSize = size;
      break;
    }

    case 0x40:
    {
      size = 2;
      ArgSize = size;
      break;
    }

    case 0x60:
    {
      size = 4;
      ArgSize = size;
      break;
    }

    case 0x80:
    {
      size = 8;
      ArgSize = size;
      break;
    }

    case 0xC0:
    {
      if (size < 0)
      {
        return 0;
      }
      ArgSize = size + 4;
      break;
    }

    case 0xA0:
    {
      if (size < 0)
      {
        return 0;
      }
      if (size == 0)
      {
        size = strlen2((char *) pvalue);
      }
      ArgSize = size + 5;
      break;
    }

    case 0xE0:
    {
      if (size <= 0)
      {
        return 0;
      }
      ArgSize = size;
      break;
    }

    default:
    {
      return 0;
    }

  }

  ArgSize += 2;
  if (CheckAllocation(item, ArgSize) == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + item->used_size;
  if (storage_type != 0xE0)
  {
    if (type > 255)
    {
      u16 type16 = type;
      copy_be16((u16 *) p, (u16 *) (&type16));
      p_idx += 2;
      item->used_size += 2;
    }
    else
    {
      p[p_idx] = type;
      p_idx += 1;
      item->used_size += 1;
    }
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) p) = *((char *) pvalue);
      item->used_size += 1;
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) p, (u16 *) pvalue);
      item->used_size += 2;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) p, (u32 *) pvalue);
      item->used_size += 4;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) p, (u64 *) pvalue);
      item->used_size += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if (size > 127)
      {
        int32 = size | 0x80000000;
        copy_be32((u32 *) p, (u32 *) (&int32));
        p_idx += 4;
        item->used_size += 4;
      }
      else
      {
        *((unsigned char *) p) = size;
        p_idx += 1;
        item->used_size += 1;
      }
      memcpy(p, pvalue, size);
      if (storage_type == 0xA0)
      {
        p_idx += size;
        *((char *) p) = (char) 0;
        size += 1;
      }
      item->used_size += size;
      break;
    }

    case 0xE0:
    {
      memcpy(p, pvalue, size);
      item->used_size += size;
      break;
    }

  }

  item->dirty = 1;
  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_list_add(binn *list, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_list_add_raw(list, type, pvalue, size);
}


/*** DEPENDENCIES:
static BOOL GetWriteConvertedData(int *ptype, void **ppvalue, int *psize)
{
  int type;
  float f1;
  double d1;
  char pstr[128];
  (void) pstr;
  (void) d1;
  (void) f1;
  type = *ptype;
  if ((*ppvalue) == 0)
  {
    switch (type)
    {
      case 0x00:

      case 0x01:

      case 0x02:
      {
        break;
      }

      case 0xA0:

      case 0xC0:
      {
        if ((*psize) == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  switch (type)
  {
    case 0xA4:

    case 0xA5:
    {
      return 1;
      break;
    }

    case 0xA2:

    case 0xA1:

    case 0xA3:
    {
      return 1;
      break;
    }

    case 0x80061:
    {
      if ((*(*((BOOL **) ppvalue))) == 0)
      {
        type = 0x02;
      }
      else
      {
        type = 0x01;
      }
      *ptype = type;
      break;
    }

  }

  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL binn_list_add_raw(binn *item, int type, void *pvalue, int size)
{
  if (((item == 0) || (item->type != 0xE0)) || (item->writable == 0))
  {
    return 0;
  }
  if (AddValue(item, type, pvalue, size) == 0)
  {
    return 0;
  }
  item->count += 1;
  return 1;
}


----------------------------
***/


static BOOL binn_map_set_raw(binn *item, int id, int type, void *pvalue, int size)
{
  unsigned char *base;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char sign;
  int id_size;
  if (((item == 0) || (item->type != 0xE1)) || (item->writable == 0))
  {
    return 0;
  }
  p_idx = SearchForID(item->pbuf, 9, item->used_size, item->count, id);
  if (p)
  {
    return 0;
  }
  if (CheckAllocation(item, 5) == 0)
  {
    return 0;
  }
  p_idx = (base = ((unsigned char *) item->pbuf) + item->used_size);
  sign = id < 0;
  if (sign)
  {
    id = -id;
  }
  if (id <= 0x3F)
  {
    p[p_idx] = (sign << 6) | id;
    p_idx += 1;
  }
  else
    if (id <= 0xFFF)
  {
    p[p_idx] = (0x80 | (sign << 4)) | ((id & 0xF00) >> 8);
    p_idx += 1;
    *((&p[p_idx])++) = id & 0xFF;
  }
  else
    if (id <= 0xFFFFF)
  {
    p[p_idx] = (0xA0 | (sign << 4)) | ((id & 0xF0000) >> 16);
    p_idx += 1;
    p[p_idx] = (id & 0xFF00) >> 8;
    p_idx += 1;
    *((&p[p_idx])++) = id & 0xFF;
  }
  else
    if (id <= 0xFFFFFFF)
  {
    p[p_idx] = (0xC0 | (sign << 4)) | ((id & 0xF000000) >> 24);
    p_idx += 1;
    p[p_idx] = (id & 0xFF0000) >> 16;
    p_idx += 1;
    *((&p[p_idx])++) = (id & 0xFF00) >> 8;
    *((&p[p_idx])++) = id & 0xFF;
  }
  else
  {
    p[p_idx] = 0xE0;
    p_idx += 1;
    if (sign)
    {
      id = -id;
    }
    copy_be32((u32 *) p, (u32 *) (&id));
    p_idx += 4;
  }
  id_size = (&p[p_idx]) - base;
  item->used_size += id_size;
  if (AddValue(item, type, pvalue, size) == 0)
  {
    item->used_size -= id_size;
    return 0;
  }
  item->count += 1;
  return 1;
}


/*** DEPENDENCIES:
static void copy_be32(u32 *pdest, u32 *psource)
{
  unsigned char *source = (unsigned char *) psource;
  unsigned char *dest = (unsigned char *) pdest;
  dest[0] = source[3];
  dest[1] = source[2];
  dest[2] = source[1];
  dest[3] = source[0];
}


----------------------------
static unsigned char *SearchForID(unsigned char *p, int header_size, int size, int numitems, int id)
{
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  int i;
  int int32;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < numitems; i += 1)
  {
    int32 = read_map_id(&(&p[p_idx]), plimit);
    if ((&p[p_idx]) > (&plimit[plimit_idx]))
    {
      break;
    }
    if (int32 == id)
    {
      return p;
    }
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      break;
    }
  }

  return 0;
}


----------------------------
static BOOL AddValue(binn *item, int type, void *pvalue, int size)
{
  unsigned int pvalue_idx = 0;
  int int32;
  int ArgSize;
  int storage_type;
  int extra_type;
  unsigned char *p;
  unsigned int p_idx = 0;
  binn_get_type_info(type, &storage_type, &extra_type);
  if ((&pvalue[pvalue_idx]) == 0)
  {
    switch (storage_type)
    {
      case 0x00:
      {
        break;
      }

      case 0xC0:

      case 0xA0:
      {
        if (size == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  if ((type_family(type) == 0xf2) && (item->disable_int_compression == 0))
  {
    pvalue_idx = compress_int(&storage_type, &type, pvalue_idx);
  }
  switch (storage_type)
  {
    case 0x00:
    {
      size = 0;
      ArgSize = size;
      break;
    }

    case 0x20:
    {
      size = 1;
      ArgSize = size;
      break;
    }

    case 0x40:
    {
      size = 2;
      ArgSize = size;
      break;
    }

    case 0x60:
    {
      size = 4;
      ArgSize = size;
      break;
    }

    case 0x80:
    {
      size = 8;
      ArgSize = size;
      break;
    }

    case 0xC0:
    {
      if (size < 0)
      {
        return 0;
      }
      ArgSize = size + 4;
      break;
    }

    case 0xA0:
    {
      if (size < 0)
      {
        return 0;
      }
      if (size == 0)
      {
        size = strlen2((char *) pvalue);
      }
      ArgSize = size + 5;
      break;
    }

    case 0xE0:
    {
      if (size <= 0)
      {
        return 0;
      }
      ArgSize = size;
      break;
    }

    default:
    {
      return 0;
    }

  }

  ArgSize += 2;
  if (CheckAllocation(item, ArgSize) == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + item->used_size;
  if (storage_type != 0xE0)
  {
    if (type > 255)
    {
      u16 type16 = type;
      copy_be16((u16 *) p, (u16 *) (&type16));
      p_idx += 2;
      item->used_size += 2;
    }
    else
    {
      p[p_idx] = type;
      p_idx += 1;
      item->used_size += 1;
    }
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) p) = *((char *) pvalue);
      item->used_size += 1;
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) p, (u16 *) pvalue);
      item->used_size += 2;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) p, (u32 *) pvalue);
      item->used_size += 4;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) p, (u64 *) pvalue);
      item->used_size += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if (size > 127)
      {
        int32 = size | 0x80000000;
        copy_be32((u32 *) p, (u32 *) (&int32));
        p_idx += 4;
        item->used_size += 4;
      }
      else
      {
        *((unsigned char *) p) = size;
        p_idx += 1;
        item->used_size += 1;
      }
      memcpy(p, pvalue, size);
      if (storage_type == 0xA0)
      {
        p_idx += size;
        *((char *) p) = (char) 0;
        size += 1;
      }
      item->used_size += size;
      break;
    }

    case 0xE0:
    {
      memcpy(p, pvalue, size);
      item->used_size += size;
      break;
    }

  }

  item->dirty = 1;
  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL CheckAllocation(binn *item, int add_size)
{
  int alloc_size;
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((item->used_size + add_size) > item->alloc_size)
  {
    if (item->pre_allocated)
    {
      return 0;
    }
    alloc_size = CalcAllocation(item->used_size + add_size, item->alloc_size);
    ptr_idx = realloc_fn(item->pbuf, alloc_size);
    if ((&ptr[ptr_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &ptr[ptr_idx];
    item->alloc_size = alloc_size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_map_set(binn *map, int id, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_map_set_raw(map, id, type, pvalue, size);
}


/*** DEPENDENCIES:
static BOOL binn_map_set_raw(binn *item, int id, int type, void *pvalue, int size)
{
  unsigned char *base;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char sign;
  int id_size;
  if (((item == 0) || (item->type != 0xE1)) || (item->writable == 0))
  {
    return 0;
  }
  p_idx = SearchForID(item->pbuf, 9, item->used_size, item->count, id);
  if (p)
  {
    return 0;
  }
  if (CheckAllocation(item, 5) == 0)
  {
    return 0;
  }
  p_idx = (base = ((unsigned char *) item->pbuf) + item->used_size);
  sign = id < 0;
  if (sign)
  {
    id = -id;
  }
  if (id <= 0x3F)
  {
    p[p_idx] = (sign << 6) | id;
    p_idx += 1;
  }
  else
    if (id <= 0xFFF)
  {
    p[p_idx] = (0x80 | (sign << 4)) | ((id & 0xF00) >> 8);
    p_idx += 1;
    *((&p[p_idx])++) = id & 0xFF;
  }
  else
    if (id <= 0xFFFFF)
  {
    p[p_idx] = (0xA0 | (sign << 4)) | ((id & 0xF0000) >> 16);
    p_idx += 1;
    p[p_idx] = (id & 0xFF00) >> 8;
    p_idx += 1;
    *((&p[p_idx])++) = id & 0xFF;
  }
  else
    if (id <= 0xFFFFFFF)
  {
    p[p_idx] = (0xC0 | (sign << 4)) | ((id & 0xF000000) >> 24);
    p_idx += 1;
    p[p_idx] = (id & 0xFF0000) >> 16;
    p_idx += 1;
    *((&p[p_idx])++) = (id & 0xFF00) >> 8;
    *((&p[p_idx])++) = id & 0xFF;
  }
  else
  {
    p[p_idx] = 0xE0;
    p_idx += 1;
    if (sign)
    {
      id = -id;
    }
    copy_be32((u32 *) p, (u32 *) (&id));
    p_idx += 4;
  }
  id_size = (&p[p_idx]) - base;
  item->used_size += id_size;
  if (AddValue(item, type, pvalue, size) == 0)
  {
    item->used_size -= id_size;
    return 0;
  }
  item->count += 1;
  return 1;
}


----------------------------
static BOOL GetWriteConvertedData(int *ptype, void **ppvalue, int *psize)
{
  int type;
  float f1;
  double d1;
  char pstr[128];
  (void) pstr;
  (void) d1;
  (void) f1;
  type = *ptype;
  if ((*ppvalue) == 0)
  {
    switch (type)
    {
      case 0x00:

      case 0x01:

      case 0x02:
      {
        break;
      }

      case 0xA0:

      case 0xC0:
      {
        if ((*psize) == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  switch (type)
  {
    case 0xA4:

    case 0xA5:
    {
      return 1;
      break;
    }

    case 0xA2:

    case 0xA1:

    case 0xA3:
    {
      return 1;
      break;
    }

    case 0x80061:
    {
      if ((*(*((BOOL **) ppvalue))) == 0)
      {
        type = 0x02;
      }
      else
      {
        type = 0x01;
      }
      *ptype = type;
      break;
    }

  }

  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


static BOOL binn_object_set_raw(binn *item, const char *key, int type, void *pvalue, int size)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char len;
  int int32;
  if (((item == 0) || (item->type != 0xE2)) || (item->writable == 0))
  {
    return 0;
  }
  if (key == 0)
  {
    return 0;
  }
  int32 = strlen(key);
  if (int32 > 255)
  {
    return 0;
  }
  p_idx = SearchForKey(item->pbuf, 9, item->used_size, item->count, key);
  if (p)
  {
    return 0;
  }
  if (CheckAllocation(item, 1 + int32) == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + item->used_size;
  len = int32;
  p[p_idx] = len;
  p_idx += 1;
  memcpy(p, key, int32);
  int32 += 1;
  item->used_size += int32;
  if (AddValue(item, type, pvalue, size) == 0)
  {
    item->used_size -= int32;
    return 0;
  }
  item->count += 1;
  return 1;
}


/*** DEPENDENCIES:
static BOOL AddValue(binn *item, int type, void *pvalue, int size)
{
  unsigned int pvalue_idx = 0;
  int int32;
  int ArgSize;
  int storage_type;
  int extra_type;
  unsigned char *p;
  unsigned int p_idx = 0;
  binn_get_type_info(type, &storage_type, &extra_type);
  if ((&pvalue[pvalue_idx]) == 0)
  {
    switch (storage_type)
    {
      case 0x00:
      {
        break;
      }

      case 0xC0:

      case 0xA0:
      {
        if (size == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  if ((type_family(type) == 0xf2) && (item->disable_int_compression == 0))
  {
    pvalue_idx = compress_int(&storage_type, &type, pvalue_idx);
  }
  switch (storage_type)
  {
    case 0x00:
    {
      size = 0;
      ArgSize = size;
      break;
    }

    case 0x20:
    {
      size = 1;
      ArgSize = size;
      break;
    }

    case 0x40:
    {
      size = 2;
      ArgSize = size;
      break;
    }

    case 0x60:
    {
      size = 4;
      ArgSize = size;
      break;
    }

    case 0x80:
    {
      size = 8;
      ArgSize = size;
      break;
    }

    case 0xC0:
    {
      if (size < 0)
      {
        return 0;
      }
      ArgSize = size + 4;
      break;
    }

    case 0xA0:
    {
      if (size < 0)
      {
        return 0;
      }
      if (size == 0)
      {
        size = strlen2((char *) pvalue);
      }
      ArgSize = size + 5;
      break;
    }

    case 0xE0:
    {
      if (size <= 0)
      {
        return 0;
      }
      ArgSize = size;
      break;
    }

    default:
    {
      return 0;
    }

  }

  ArgSize += 2;
  if (CheckAllocation(item, ArgSize) == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + item->used_size;
  if (storage_type != 0xE0)
  {
    if (type > 255)
    {
      u16 type16 = type;
      copy_be16((u16 *) p, (u16 *) (&type16));
      p_idx += 2;
      item->used_size += 2;
    }
    else
    {
      p[p_idx] = type;
      p_idx += 1;
      item->used_size += 1;
    }
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      *((char *) p) = *((char *) pvalue);
      item->used_size += 1;
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) p, (u16 *) pvalue);
      item->used_size += 2;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) p, (u32 *) pvalue);
      item->used_size += 4;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) p, (u64 *) pvalue);
      item->used_size += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if (size > 127)
      {
        int32 = size | 0x80000000;
        copy_be32((u32 *) p, (u32 *) (&int32));
        p_idx += 4;
        item->used_size += 4;
      }
      else
      {
        *((unsigned char *) p) = size;
        p_idx += 1;
        item->used_size += 1;
      }
      memcpy(p, pvalue, size);
      if (storage_type == 0xA0)
      {
        p_idx += size;
        *((char *) p) = (char) 0;
        size += 1;
      }
      item->used_size += size;
      break;
    }

    case 0xE0:
    {
      memcpy(p, pvalue, size);
      item->used_size += size;
      break;
    }

  }

  item->dirty = 1;
  return 1;
}


----------------------------
static unsigned char *SearchForKey(unsigned char *p, int header_size, int size, int numitems, const char *key)
{
  unsigned int p_idx = 0;
  unsigned char len;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  int i;
  int keylen;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  keylen = strlen(key);
  for (i = 0; i < numitems; i += 1)
  {
    len = *((unsigned char *) p);
    p_idx += 1;
    if ((&p[p_idx]) > (&plimit[plimit_idx]))
    {
      break;
    }
    if (len > 0)
    {
      if (strncasecmp((char *) p, key, len) == 0)
      {
        if (keylen == len)
        {
          p_idx += len;
          return p;
        }
      }
      p_idx += len;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        break;
      }
    }
    else
      if (len == keylen)
    {
      return p;
    }
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      break;
    }
  }

  return 0;
}


----------------------------
static BOOL CheckAllocation(binn *item, int add_size)
{
  int alloc_size;
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((item->used_size + add_size) > item->alloc_size)
  {
    if (item->pre_allocated)
    {
      return 0;
    }
    alloc_size = CalcAllocation(item->used_size + add_size, item->alloc_size);
    ptr_idx = realloc_fn(item->pbuf, alloc_size);
    if ((&ptr[ptr_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &ptr[ptr_idx];
    item->alloc_size = alloc_size;
  }
  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_object_set_raw(obj, key, type, pvalue, size);
}


/*** DEPENDENCIES:
static BOOL GetWriteConvertedData(int *ptype, void **ppvalue, int *psize)
{
  int type;
  float f1;
  double d1;
  char pstr[128];
  (void) pstr;
  (void) d1;
  (void) f1;
  type = *ptype;
  if ((*ppvalue) == 0)
  {
    switch (type)
    {
      case 0x00:

      case 0x01:

      case 0x02:
      {
        break;
      }

      case 0xA0:

      case 0xC0:
      {
        if ((*psize) == 0)
        {
          break;
        }
      }

      default:
      {
        return 0;
      }

    }

  }
  switch (type)
  {
    case 0xA4:

    case 0xA5:
    {
      return 1;
      break;
    }

    case 0xA2:

    case 0xA1:

    case 0xA3:
    {
      return 1;
      break;
    }

    case 0x80061:
    {
      if ((*(*((BOOL **) ppvalue))) == 0)
      {
        type = 0x02;
      }
      else
      {
        type = 0x01;
      }
      *ptype = type;
      break;
    }

  }

  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL binn_object_set_raw(binn *item, const char *key, int type, void *pvalue, int size)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char len;
  int int32;
  if (((item == 0) || (item->type != 0xE2)) || (item->writable == 0))
  {
    return 0;
  }
  if (key == 0)
  {
    return 0;
  }
  int32 = strlen(key);
  if (int32 > 255)
  {
    return 0;
  }
  p_idx = SearchForKey(item->pbuf, 9, item->used_size, item->count, key);
  if (p)
  {
    return 0;
  }
  if (CheckAllocation(item, 1 + int32) == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + item->used_size;
  len = int32;
  p[p_idx] = len;
  p_idx += 1;
  memcpy(p, key, int32);
  int32 += 1;
  item->used_size += int32;
  if (AddValue(item, type, pvalue, size) == 0)
  {
    item->used_size -= int32;
    return 0;
  }
  item->count += 1;
  return 1;
}


----------------------------
***/


BOOL binn_create_list(binn *list)
{
  return binn_create(list, 0xE0, 0, 0);
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
BOOL binn_create(binn *item, int type, int size, void *pointer)
{
  unsigned int pointer_idx = 0;
  BOOL retval = 0;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      goto loc_exit;
    }

  }

  if ((item == 0) || (size < 0))
  {
    goto loc_exit;
  }
  if (size < 3)
  {
    if (pointer)
    {
      goto loc_exit;
    }
    else
      size = 0;
  }
  memset(item, 0, sizeof(binn));
  if (pointer)
  {
    item->pre_allocated = 1;
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  else
  {
    item->pre_allocated = 0;
    if (size == 0)
    {
      size = 256;
    }
    pointer_idx = binn_malloc(size);
    if ((&pointer[pointer_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  item->header = 0x1F22B11F;
  item->writable = 1;
  item->used_size = 9;
  item->type = type;
  item->dirty = 1;
  retval = 1;
  loc_exit:
  return retval;

}


----------------------------
***/


BOOL binn_create_map(binn *map)
{
  return binn_create(map, 0xE1, 0, 0);
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
BOOL binn_create(binn *item, int type, int size, void *pointer)
{
  unsigned int pointer_idx = 0;
  BOOL retval = 0;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      goto loc_exit;
    }

  }

  if ((item == 0) || (size < 0))
  {
    goto loc_exit;
  }
  if (size < 3)
  {
    if (pointer)
    {
      goto loc_exit;
    }
    else
      size = 0;
  }
  memset(item, 0, sizeof(binn));
  if (pointer)
  {
    item->pre_allocated = 1;
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  else
  {
    item->pre_allocated = 0;
    if (size == 0)
    {
      size = 256;
    }
    pointer_idx = binn_malloc(size);
    if ((&pointer[pointer_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  item->header = 0x1F22B11F;
  item->writable = 1;
  item->used_size = 9;
  item->type = type;
  item->dirty = 1;
  retval = 1;
  loc_exit:
  return retval;

}


----------------------------
***/


BOOL binn_create_object(binn *object)
{
  return binn_create(object, 0xE2, 0, 0);
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
BOOL binn_create(binn *item, int type, int size, void *pointer)
{
  unsigned int pointer_idx = 0;
  BOOL retval = 0;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      goto loc_exit;
    }

  }

  if ((item == 0) || (size < 0))
  {
    goto loc_exit;
  }
  if (size < 3)
  {
    if (pointer)
    {
      goto loc_exit;
    }
    else
      size = 0;
  }
  memset(item, 0, sizeof(binn));
  if (pointer)
  {
    item->pre_allocated = 1;
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  else
  {
    item->pre_allocated = 0;
    if (size == 0)
    {
      size = 256;
    }
    pointer_idx = binn_malloc(size);
    if ((&pointer[pointer_idx]) == 0)
    {
      return 0;
    }
    item->pbuf = &pointer[pointer_idx];
    item->alloc_size = size;
  }
  item->header = 0x1F22B11F;
  item->writable = 1;
  item->used_size = 9;
  item->type = type;
  item->dirty = 1;
  retval = 1;
  loc_exit:
  return retval;

}


----------------------------
***/


void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


BOOL binn_load(void *data, binn *value)
{
  if ((data == 0) || (value == 0))
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  if (binn_is_valid(data, &value->type, &value->count, &value->size) == 0)
  {
    return 0;
  }
  value->ptr = data;
  return 1;
}


/*** DEPENDENCIES:
BOOL binn_is_valid(void *ptr, int *ptype, int *pcount, int *psize)
{
  if (ptype)
  {
    *ptype = 0;
  }
  if (pcount)
  {
    *pcount = 0;
  }
  if (psize)
  {
    *psize = 0;
  }
  return binn_is_valid_ex(ptr, ptype, pcount, psize);
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


int64 binn_list_int64(void *list, int pos)
{
  int64 value;
  binn_list_get(list, pos, 0x81, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_list_bool(void *list, int pos)
{
  BOOL value;
  binn_list_get(list, pos, 0x80061, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


int64 binn_map_int64(void *map, int id)
{
  int64 value;
  binn_map_get(map, id, 0x81, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_map_bool(void *map, int id)
{
  BOOL value;
  binn_map_get(map, id, 0x80061, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


int64 binn_object_int64(void *obj, const char *key)
{
  int64 value;
  binn_object_get(obj, key, 0x81, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


BOOL binn_object_bool(void *obj, const char *key)
{
  BOOL value;
  binn_object_get(obj, key, 0x80061, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef int BOOL
----------------------------
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


// hint:  ['int32_ref is a mutable refrence to int', 'id_ref is a mutable refrence to int', 'counter_ref is a mutable refrence to int', 'p_idx_ref is a mutable refrence to unsigned int', 'key_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to unsigned char']
BOOL helper_binn_read_pair_1(int * const int32_ref, int * const id_ref, int * const counter_ref, unsigned int * const p_idx_ref, unsigned int * const key_idx_ref, unsigned char * const len_ref, int pos, int type, unsigned char * const p, unsigned char * const plimit, unsigned int plimit_idx, unsigned char * const base, unsigned int base_idx)
{
  int int32 = *int32_ref;
  int id = *id_ref;
  int counter = *counter_ref;
  unsigned int p_idx = *p_idx_ref;
  unsigned int key_idx = *key_idx_ref;
  unsigned char len = *len_ref;
  switch (type)
  {
    case 0xE1:
    {
      int32 = read_map_id(&(&p[p_idx]), plimit);
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        return 0;
      }
      id = int32;
      break;
    }

    case 0xE2:
    {
      len = *((unsigned char *) p);
      p_idx += 1;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        return 0;
      }
      key_idx = &p[p_idx];
      p_idx += len;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        return 0;
      }
      break;
    }

  }

  counter += 1;
  if (counter == pos)
  {
    goto found;
  }
  p_idx = AdvanceDataPos(p_idx, plimit);
  if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
  {
    return 0;
  }
  *int32_ref = int32;
  *id_ref = id;
  *counter_ref = counter;
  *p_idx_ref = p_idx;
  *key_idx_ref = key_idx;
  *len_ref = len;
}


/*** DEPENDENCIES:
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
static int read_map_id(unsigned char **pp, unsigned char *plimit)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char c;
  unsigned char sign;
  unsigned char type;
  int id;
  int extra_bytes;
  p_idx = *pp;
  c = p[p_idx];
  p_idx += 1;
  if (c & 0x80)
  {
    extra_bytes = ((c & 0x60) >> 5) + 1;
    if (((&p[p_idx]) + extra_bytes) > plimit)
    {
      *pp = (&p[p_idx]) + extra_bytes;
      return 0;
    }
  }
  type = c & 0xE0;
  sign = c & 0x10;
  if ((c & 0x80) == 0)
  {
    sign = c & 0x40;
    id = c & 0x3F;
  }
  else
    if (type == 0x80)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
  }
  else
    if (type == 0xA0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xC0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xE0)
  {
    copy_be32((u32 *) (&id), (u32 *) p);
    p_idx += 4;
  }
  else
  {
    *pp = plimit + 2;
    return 0;
  }
  if (sign)
  {
    id = -id;
  }
  *pp = &p[p_idx];
  return id;
}


----------------------------
***/


static BOOL binn_read_pair(int expected_type, void *ptr, int pos, int *pid, char *pkey, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  int i;
  int int32;
  int id = 0;
  int counter = 0;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char *key = 0;
  unsigned int key_idx = 0;
  unsigned char len = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if ((((type != expected_type) || (count == 0)) || (pos < 1)) || (pos > count))
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    helper_binn_read_pair_1(&int32, &id, &counter, &p_idx, &key_idx, &len, pos, type, p, plimit, plimit_idx, base, base_idx);
  }

  return 0;
  found:
  switch (type)
  {
    case 0xE1:
    {
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }


  return GetValue(p, value);
}


/*** DEPENDENCIES:
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
BOOL helper_binn_read_pair_1(int * const int32_ref, int * const id_ref, int * const counter_ref, unsigned int * const p_idx_ref, unsigned int * const key_idx_ref, unsigned char * const len_ref, int pos, int type, unsigned char * const p, unsigned char * const plimit, unsigned int plimit_idx, unsigned char * const base, unsigned int base_idx)
{
  int int32 = *int32_ref;
  int id = *id_ref;
  int counter = *counter_ref;
  unsigned int p_idx = *p_idx_ref;
  unsigned int key_idx = *key_idx_ref;
  unsigned char len = *len_ref;
  switch (type)
  {
    case 0xE1:
    {
      int32 = read_map_id(&(&p[p_idx]), plimit);
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        return 0;
      }
      id = int32;
      break;
    }

    case 0xE2:
    {
      len = *((unsigned char *) p);
      p_idx += 1;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        return 0;
      }
      key_idx = &p[p_idx];
      p_idx += len;
      if ((&p[p_idx]) > (&plimit[plimit_idx]))
      {
        return 0;
      }
      break;
    }

  }

  counter += 1;
  if (counter == pos)
  {
    goto found;
  }
  p_idx = AdvanceDataPos(p_idx, plimit);
  if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
  {
    return 0;
  }
  *int32_ref = int32;
  *id_ref = id;
  *counter_ref = counter;
  *p_idx_ref = p_idx;
  *key_idx_ref = key_idx;
  *len_ref = len;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


----------------------------
***/


BOOL binn_map_get_pair(void *ptr, int pos, int *pid, binn *value)
{
  return binn_read_pair(0xE1, ptr, pos, pid, 0, value);
}


/*** DEPENDENCIES:
static BOOL binn_read_pair(int expected_type, void *ptr, int pos, int *pid, char *pkey, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  int i;
  int int32;
  int id = 0;
  int counter = 0;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char *key = 0;
  unsigned int key_idx = 0;
  unsigned char len = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if ((((type != expected_type) || (count == 0)) || (pos < 1)) || (pos > count))
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    helper_binn_read_pair_1(&int32, &id, &counter, &p_idx, &key_idx, &len, pos, type, p, plimit, plimit_idx, base, base_idx);
  }

  return 0;
  found:
  switch (type)
  {
    case 0xE1:
    {
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }


  return GetValue(p, value);
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_object_get_pair(void *ptr, int pos, char *pkey, binn *value)
{
  return binn_read_pair(0xE2, ptr, pos, 0, pkey, value);
}


/*** DEPENDENCIES:
static BOOL binn_read_pair(int expected_type, void *ptr, int pos, int *pid, char *pkey, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  int i;
  int int32;
  int id = 0;
  int counter = 0;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char *key = 0;
  unsigned int key_idx = 0;
  unsigned char len = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if ((((type != expected_type) || (count == 0)) || (pos < 1)) || (pos > count))
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    helper_binn_read_pair_1(&int32, &id, &counter, &p_idx, &key_idx, &len, pos, type, p, plimit, plimit_idx, base, base_idx);
  }

  return 0;
  found:
  switch (type)
  {
    case 0xE1:
    {
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }


  return GetValue(p, value);
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


int binn_size(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->size;
    }

    case 2:
    {
      return binn_buf_size(ptr);
    }

    default:
    {
      return 0;
    }

  }

}


/*** DEPENDENCIES:
static BOOL binn_save_header(binn *item)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  int int32;
  int size;
  if (item == 0)
  {
    return 0;
  }
  p_idx = ((unsigned char *) item->pbuf) + 9;
  size = (item->used_size - 9) + 3;
  if (item->count > 127)
  {
    p_idx -= 4;
    size += 3;
    int32 = item->count | 0x80000000;
    copy_be32((u32 *) p, (u32 *) (&int32));
  }
  else
  {
    p_idx -= 1;
    p[p_idx] = (unsigned char) item->count;
  }
  if (size > 127)
  {
    p_idx -= 4;
    size += 3;
    int32 = size | 0x80000000;
    copy_be32((u32 *) p, (u32 *) (&int32));
  }
  else
  {
    p_idx -= 1;
    p[p_idx] = (unsigned char) size;
  }
  p_idx -= 1;
  p[p_idx] = (unsigned char) item->type;
  item->ptr = &p[p_idx];
  item->size = size;
  (void) byte;
  item->dirty = 0;
  return 1;
}


----------------------------
static int binn_buf_size(void *pbuf)
{
  int size = 0;
  if (!IsValidBinnHeader(pbuf, 0, 0, &size, 0))
  {
    return 0;
  }
  return size;
}


----------------------------
typedef struct binn_struct binn
----------------------------
static int binn_get_ptr_type(void *ptr)
{
  if (ptr == 0)
  {
    return 0;
  }
  switch (*((unsigned int *) ptr))
  {
    case 0x1F22B11F:
    {
      return 1;
    }

    default:
    {
      return 2;
    }

  }

}


----------------------------
***/


void binn_set_alloc_functions(void *(*new_malloc)(size_t), void *(*new_realloc)(void *, size_t), void (*new_free)(void *))
{
  malloc_fn = new_malloc;
  realloc_fn = new_realloc;
  free_fn = new_free;
}


/*** DEPENDENCIES:
void *(*realloc_fn)(void *ptr, size_t len) = 0
----------------------------
void *(*malloc_fn)(size_t len) = 0
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


void *binn_release(binn *item)
{
  void *data;
  unsigned int data_idx = 0;
  if (item == 0)
  {
    return 0;
  }
  data_idx = binn_ptr(item);
  if ((&data[data_idx]) > item->pbuf)
  {
    memmove(item->pbuf, data, item->size);
    data_idx = item->pbuf;
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
  return data;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
***/


int binn_type(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      return item->type;
    }

    case 2:
    {
      return binn_buf_type(ptr);
    }

    default:
    {
      return -1;
    }

  }

}


/*** DEPENDENCIES:
static int binn_get_ptr_type(void *ptr)
{
  if (ptr == 0)
  {
    return 0;
  }
  switch (*((unsigned int *) ptr))
  {
    case 0x1F22B11F:
    {
      return 1;
    }

    default:
    {
      return 2;
    }

  }

}


----------------------------
typedef struct binn_struct binn
----------------------------
static int binn_buf_type(void *pbuf)
{
  int type;
  if (!IsValidBinnHeader(pbuf, &type, 0, 0, 0))
  {
    return 0;
  }
  return type;
}


----------------------------
***/


int binn_count(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      return item->count;
    }

    case 2:
    {
      return binn_buf_count(ptr);
    }

    default:
    {
      return -1;
    }

  }

}


/*** DEPENDENCIES:
static int binn_get_ptr_type(void *ptr)
{
  if (ptr == 0)
  {
    return 0;
  }
  switch (*((unsigned int *) ptr))
  {
    case 0x1F22B11F:
    {
      return 1;
    }

    default:
    {
      return 2;
    }

  }

}


----------------------------
typedef struct binn_struct binn
----------------------------
static int binn_buf_count(void *pbuf)
{
  int nitems;
  if (!IsValidBinnHeader(pbuf, 0, &nitems, 0, 0))
  {
    return 0;
  }
  return nitems;
}


----------------------------
***/


uint64 binn_list_uint64(void *list, int pos)
{
  uint64 value;
  binn_list_get(list, pos, 0x80, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
typedef unsigned long long int uint64
----------------------------
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


uint64 binn_map_uint64(void *map, int id)
{
  uint64 value;
  binn_map_get(map, id, 0x80, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
typedef unsigned long long int uint64
----------------------------
BOOL binn_map_get(void *ptr, int id, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_map_get_value(ptr, id, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


uint64 binn_object_uint64(void *obj, const char *key)
{
  uint64 value;
  binn_object_get(obj, key, 0x80, &value, 0);
  return value;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
typedef unsigned long long int uint64
----------------------------
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
***/


static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
binn local_value
----------------------------
int binn_get_read_storage(int type)
{
  int storage_type;
  switch (type)
  {
    case 0x80061:

    case 0x01:

    case 0x02:
    {
      return 0x60;
    }

    default:
    {
      binn_get_type_info(type, &storage_type, 0);
      return storage_type;
    }

  }

}


----------------------------
***/


void *binn_list_read(void *list, int pos, int *ptype, int *psize)
{
  binn value;
  if (binn_list_get_value(list, pos, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
BOOL binn_list_get_value(void *ptr, int pos, binn *value)
{
  unsigned int ptr_idx = 0;
  int i;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE0)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  if ((pos <= 0) | (pos > count))
  {
    return 0;
  }
  pos -= 1;
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = (&p[p_idx]) + size;
  p_idx += header_size;
  for (i = 0; i < pos; i += 1)
  {
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      return 0;
    }
  }

  return GetValue(p, value);
}


----------------------------
***/


void *binn_map_read(void *map, int id, int *ptype, int *psize)
{
  binn value;
  if (binn_map_get_value(map, id, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
BOOL binn_map_get_value(void *ptr, int id, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE1)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForID(p_idx, header_size, size, count, id);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
***/


void *binn_object_read(void *obj, const char *key, int *ptype, int *psize)
{
  binn value;
  if (binn_object_get_value(obj, key, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
BOOL binn_object_get_value(void *ptr, const char *key, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if ((((&ptr[ptr_idx]) == 0) || (key == 0)) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE2)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForKey(p_idx, header_size, size, count, key);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


void *binn_map_read_pair(void *ptr, int pos, int *pid, int *ptype, int *psize)
{
  binn value;
  if (binn_map_get_pair(ptr, pos, pid, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
BOOL binn_map_get_pair(void *ptr, int pos, int *pid, binn *value)
{
  return binn_read_pair(0xE1, ptr, pos, pid, 0, value);
}


----------------------------
***/


void *binn_object_read_pair(void *ptr, int pos, char *pkey, int *ptype, int *psize)
{
  binn value;
  if (binn_object_get_pair(ptr, pos, pkey, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
BOOL binn_object_get_pair(void *ptr, int pos, char *pkey, binn *value)
{
  return binn_read_pair(0xE2, ptr, pos, 0, pkey, value);
}


----------------------------
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


static BOOL binn_read_next_pair(int expected_type, binn_iter *iter, int *pid, char *pkey, binn *value)
{
  int int32;
  int id;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *key;
  unsigned int key_idx = 0;
  unsigned short len;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != expected_type))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  p_idx = iter->pnext;
  switch (expected_type)
  {
    case 0xE1:
    {
      int32 = read_map_id(&(&p[p_idx]), iter->plimit);
      if ((&p[p_idx]) > iter->plimit)
      {
        return 0;
      }
      id = int32;
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      len = *((unsigned char *) p);
      p_idx += 1;
      key_idx = &p[p_idx];
      p_idx += len;
      if ((&p[p_idx]) > iter->plimit)
      {
        return 0;
      }
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }

  iter->pnext = AdvanceDataPos(p, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&p[p_idx])))
  {
    return 0;
  }
  return GetValue(p, value);
}


/*** DEPENDENCIES:
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


----------------------------
static int read_map_id(unsigned char **pp, unsigned char *plimit)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char c;
  unsigned char sign;
  unsigned char type;
  int id;
  int extra_bytes;
  p_idx = *pp;
  c = p[p_idx];
  p_idx += 1;
  if (c & 0x80)
  {
    extra_bytes = ((c & 0x60) >> 5) + 1;
    if (((&p[p_idx]) + extra_bytes) > plimit)
    {
      *pp = (&p[p_idx]) + extra_bytes;
      return 0;
    }
  }
  type = c & 0xE0;
  sign = c & 0x10;
  if ((c & 0x80) == 0)
  {
    sign = c & 0x40;
    id = c & 0x3F;
  }
  else
    if (type == 0x80)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
  }
  else
    if (type == 0xA0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xC0)
  {
    id = c & 0x0F;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | p[p_idx];
    p_idx += 1;
    id = (id << 8) | (*((&p[p_idx])++));
  }
  else
    if (type == 0xE0)
  {
    copy_be32((u32 *) (&id), (u32 *) p);
    p_idx += 4;
  }
  else
  {
    *pp = plimit + 2;
    return 0;
  }
  if (sign)
  {
    id = -id;
  }
  *pp = &p[p_idx];
  return id;
}


----------------------------
***/


BOOL binn_map_next(binn_iter *iter, int *pid, binn *value)
{
  return binn_read_next_pair(0xE1, iter, pid, 0, value);
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL binn_read_next_pair(int expected_type, binn_iter *iter, int *pid, char *pkey, binn *value)
{
  int int32;
  int id;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *key;
  unsigned int key_idx = 0;
  unsigned short len;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != expected_type))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  p_idx = iter->pnext;
  switch (expected_type)
  {
    case 0xE1:
    {
      int32 = read_map_id(&(&p[p_idx]), iter->plimit);
      if ((&p[p_idx]) > iter->plimit)
      {
        return 0;
      }
      id = int32;
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      len = *((unsigned char *) p);
      p_idx += 1;
      key_idx = &p[p_idx];
      p_idx += len;
      if ((&p[p_idx]) > iter->plimit)
      {
        return 0;
      }
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }

  iter->pnext = AdvanceDataPos(p, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&p[p_idx])))
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
***/


BOOL binn_object_next(binn_iter *iter, char *pkey, binn *value)
{
  return binn_read_next_pair(0xE2, iter, 0, pkey, value);
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL binn_read_next_pair(int expected_type, binn_iter *iter, int *pid, char *pkey, binn *value)
{
  int int32;
  int id;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *key;
  unsigned int key_idx = 0;
  unsigned short len;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != expected_type))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  p_idx = iter->pnext;
  switch (expected_type)
  {
    case 0xE1:
    {
      int32 = read_map_id(&(&p[p_idx]), iter->plimit);
      if ((&p[p_idx]) > iter->plimit)
      {
        return 0;
      }
      id = int32;
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      len = *((unsigned char *) p);
      p_idx += 1;
      key_idx = &p[p_idx];
      p_idx += len;
      if ((&p[p_idx]) > iter->plimit)
      {
        return 0;
      }
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }

  iter->pnext = AdvanceDataPos(p, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&p[p_idx])))
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
***/


binn *binn_copy(void *old)
{
  int type;
  int count;
  int size;
  int header_size;
  unsigned char *old_ptr = binn_ptr(old);
  binn *item;
  unsigned int item_idx = 0;
  size = 0;
  if (!IsValidBinnHeader(old_ptr, &type, &count, &size, &header_size))
  {
    return 0;
  }
  item_idx = binn_new(type, (size - header_size) + 9, 0);
  if (item)
  {
    unsigned char *dest;
    unsigned int dest_idx = 0;
    dest_idx = ((unsigned char *) item->pbuf) + 9;
    memcpy(dest, old_ptr + header_size, size - header_size);
    item->used_size = (9 + size) - header_size;
    item->count = count;
  }
  return item;
}


/*** DEPENDENCIES:
binn *binn_new(int type, int size, void *pointer)
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_create(item, type, size, pointer) == 0)
  {
    free_fn(item);
    return 0;
  }
  item->allocated = 1;
  return item;
}


----------------------------
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
***/


BOOL binn_list_add_new(binn *list, binn *value)
{
  BOOL retval;
  retval = binn_list_add_value(list, value);
  if (value)
  {
    free_fn(value);
  }
  return retval;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
typedef int BOOL
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
inline static BOOL binn_list_add_value(binn *list, binn *value)
{
  return binn_list_add(list, value->type, binn_ptr(value), binn_size(value));
}


----------------------------
***/


BOOL binn_map_set_new(binn *map, int id, binn *value)
{
  BOOL retval;
  retval = binn_map_set_value(map, id, value);
  if (value)
  {
    free_fn(value);
  }
  return retval;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
typedef int BOOL
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
inline static BOOL binn_map_set_value(binn *map, int id, binn *value)
{
  return binn_map_set(map, id, value->type, binn_ptr(value), binn_size(value));
}


----------------------------
***/


BOOL binn_object_set_new(binn *obj, const char *key, binn *value)
{
  BOOL retval;
  retval = binn_object_set_value(obj, key, value);
  if (value)
  {
    free_fn(value);
  }
  return retval;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
inline static BOOL binn_object_set_value(binn *obj, const char *key, binn *value)
{
  return binn_object_set(obj, key, value->type, binn_ptr(value), binn_size(value));
}


----------------------------
typedef int BOOL
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


binn *binn_open(void *data)
{
  binn *item;
  unsigned int item_idx = 0;
  item_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_load(data, item) == 0)
  {
    free_fn(item);
    return 0;
  }
  item->allocated = 1;
  return item;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
BOOL binn_load(void *data, binn *value)
{
  if ((data == 0) || (value == 0))
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  if (binn_is_valid(data, &value->type, &value->count, &value->size) == 0)
  {
    return 0;
  }
  value->ptr = data;
  return 1;
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


binn *binn_list_value(void *ptr, int pos)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_list_get_value(ptr, pos, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
BOOL binn_list_get_value(void *ptr, int pos, binn *value)
{
  unsigned int ptr_idx = 0;
  int i;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE0)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  if ((pos <= 0) | (pos > count))
  {
    return 0;
  }
  pos -= 1;
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = (&p[p_idx]) + size;
  p_idx += header_size;
  for (i = 0; i < pos; i += 1)
  {
    p_idx = AdvanceDataPos(p_idx, plimit);
    if (((&p[p_idx]) == 0) || ((&p[p_idx]) < (&base[base_idx])))
    {
      return 0;
    }
  }

  return GetValue(p, value);
}


----------------------------
***/


binn *binn_map_value(void *ptr, int id)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_map_get_value(ptr, id, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
BOOL binn_map_get_value(void *ptr, int id, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE1)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForID(p_idx, header_size, size, count, id);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
***/


binn *binn_object_value(void *ptr, const char *key)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_object_get_value(ptr, key, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
BOOL binn_object_get_value(void *ptr, const char *key, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if ((((&ptr[ptr_idx]) == 0) || (key == 0)) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE2)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForKey(p_idx, header_size, size, count, key);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


binn *binn_map_pair(void *map, int pos, int *pid)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_read_pair(0xE1, map, pos, pid, 0, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
static BOOL binn_read_pair(int expected_type, void *ptr, int pos, int *pid, char *pkey, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  int i;
  int int32;
  int id = 0;
  int counter = 0;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char *key = 0;
  unsigned int key_idx = 0;
  unsigned char len = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if ((((type != expected_type) || (count == 0)) || (pos < 1)) || (pos > count))
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    helper_binn_read_pair_1(&int32, &id, &counter, &p_idx, &key_idx, &len, pos, type, p, plimit, plimit_idx, base, base_idx);
  }

  return 0;
  found:
  switch (type)
  {
    case 0xE1:
    {
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }


  return GetValue(p, value);
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
***/


binn *binn_object_pair(void *obj, int pos, char *pkey)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_read_pair(0xE2, obj, pos, 0, pkey, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
static BOOL binn_read_pair(int expected_type, void *ptr, int pos, int *pid, char *pkey, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  int i;
  int int32;
  int id = 0;
  int counter = 0;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit;
  unsigned int plimit_idx = 0;
  unsigned char *base;
  unsigned int base_idx = 0;
  unsigned char *key = 0;
  unsigned int key_idx = 0;
  unsigned char len = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if ((((type != expected_type) || (count == 0)) || (pos < 1)) || (pos > count))
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  base_idx = &p[p_idx];
  plimit_idx = ((&p[p_idx]) + size) - 1;
  p_idx += header_size;
  for (i = 0; i < count; i += 1)
  {
    helper_binn_read_pair_1(&int32, &id, &counter, &p_idx, &key_idx, &len, pos, type, p, plimit, plimit_idx, base, base_idx);
  }

  return 0;
  found:
  switch (type)
  {
    case 0xE1:
    {
      if (pid)
      {
        *pid = id;
      }
      break;
    }

    case 0xE2:
    {
      if (pkey)
      {
        memcpy(pkey, key, len);
        pkey[len] = 0;
      }
      break;
    }

  }


  return GetValue(p, value);
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
***/


BOOL binn_iter_init(binn_iter *iter, void *ptr, int expected_type)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (iter == 0))
  {
    return 0;
  }
  memset(iter, 0, sizeof(binn_iter));
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != expected_type)
  {
    return 0;
  }
  iter->plimit = (((unsigned char *) ptr) + size) - 1;
  iter->pnext = ((unsigned char *) ptr) + header_size;
  iter->count = count;
  iter->current = 0;
  iter->type = type;
  return 1;
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
static BOOL IsValidBinnHeader(void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize)
{
  unsigned char byte;
  unsigned char *p;
  unsigned int p_idx = 0;
  unsigned char *plimit = 0;
  unsigned int plimit_idx = 0;
  int int32;
  int type;
  int size;
  int count;
  if (pbuf == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) pbuf;
  if (psize && ((*psize) > 0))
  {
    plimit_idx = ((&p[p_idx]) + (*psize)) - 1;
  }
  byte = p[p_idx];
  p_idx += 1;
  if ((byte & 0xE0) != 0xE0)
  {
    return 0;
  }
  if (byte & 0x10)
  {
    return 0;
  }
  type = byte;
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  size = int32;
  if ((&plimit[plimit_idx]) && ((&p[p_idx]) > (&plimit[plimit_idx])))
  {
    return 0;
  }
  int32 = *((unsigned char *) p);
  if (int32 & 0x80)
  {
    if ((&plimit[plimit_idx]) && ((((&p[p_idx]) + (sizeof(int))) - 1) > (&plimit[plimit_idx])))
    {
      return 0;
    }
    copy_be32((u32 *) (&int32), (u32 *) p);
    int32 &= 0x7FFFFFFF;
    p_idx += 4;
  }
  else
  {
    p_idx += 1;
  }
  count = int32;
  if ((size < 3) || (count < 0))
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = type;
  }
  if (pcount)
  {
    *pcount = count;
  }
  if (psize && ((*psize) == 0))
  {
    *psize = size;
  }
  if (pheadersize)
  {
    *pheadersize = (int) ((&p[p_idx]) - ((unsigned char *) pbuf));
  }
  return 1;
}


----------------------------
typedef struct binn_struct binn
----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
***/


BOOL binn_list_next(binn_iter *iter, binn *value)
{
  unsigned char *pnow;
  unsigned int pnow_idx = 0;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != 0xE0))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  pnow_idx = iter->pnext;
  iter->pnext = AdvanceDataPos(pnow, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&pnow[pnow_idx])))
  {
    return 0;
  }
  return GetValue(pnow, value);
}


/*** DEPENDENCIES:
static unsigned char *AdvanceDataPos(unsigned char *p, unsigned char *plimit)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int storage_type;
  int DataSize;
  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    p_idx += 1;
  }
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      p_idx += 1;
      break;
    }

    case 0x40:
    {
      p_idx += 2;
      break;
    }

    case 0x60:
    {
      p_idx += 4;
      break;
    }

    case 0x80:
    {
      p_idx += 8;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      p_idx += DataSize;
      if (storage_type == 0xA0)
      {
        p_idx += 1;
      }
      break;
    }

    case 0xE0:
    {
      if ((&p[p_idx]) > plimit)
      {
        return 0;
      }
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        if ((((&p[p_idx]) + (sizeof(int))) - 1) > plimit)
        {
          return 0;
        }
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
      }
      DataSize -= 1;
      p_idx += DataSize;
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((&p[p_idx]) > plimit)
  {
    return 0;
  }
  return p;
}


----------------------------
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL GetValue(unsigned char *p, binn *value)
{
  unsigned int p_idx = 0;
  unsigned char byte;
  int data_type;
  int storage_type;
  int DataSize;
  void *p2;
  unsigned int p2_idx = 0;
  if (value == 0)
  {
    return 0;
  }
  memset(value, 0, sizeof(binn));
  value->header = 0x1F22B11F;
  p2_idx = &p[p_idx];
  byte = p[p_idx];
  p_idx += 1;
  storage_type = byte & 0xE0;
  if (byte & 0x10)
  {
    data_type = byte << 8;
    byte = p[p_idx];
    p_idx += 1;
    data_type |= byte;
  }
  else
  {
    data_type = byte;
  }
  value->type = data_type;
  switch (storage_type)
  {
    case 0x00:
    {
      break;
    }

    case 0x20:
    {
      value->vuint8 = *((unsigned char *) p);
      value->ptr = &p[p_idx];
      break;
    }

    case 0x40:
    {
      copy_be16((u16 *) (&value->vint16), (u16 *) p);
      value->ptr = &value->vint16;
      break;
    }

    case 0x60:
    {
      copy_be32((u32 *) (&value->vint32), (u32 *) p);
      value->ptr = &value->vint32;
      break;
    }

    case 0x80:
    {
      copy_be64((u64 *) (&value->vint64), (u64 *) p);
      value->ptr = &value->vint64;
      break;
    }

    case 0xC0:

    case 0xA0:
    {
      DataSize = *((unsigned char *) p);
      if (DataSize & 0x80)
      {
        copy_be32((u32 *) (&DataSize), (u32 *) p);
        DataSize &= 0x7FFFFFFF;
        p_idx += 4;
      }
      else
      {
        p_idx += 1;
      }
      value->size = DataSize;
      value->ptr = &p[p_idx];
      break;
    }

    case 0xE0:
    {
      value->ptr = &p2[p2_idx];
      if (IsValidBinnHeader(p2, 0, &value->count, &value->size, 0) == 0)
      {
        return 0;
      }
      break;
    }

    default:
    {
      return 0;
    }

  }

  switch (value->type)
  {
    case 0x01:
    {
      value->type = 0x80061;
      value->vbool = 1;
      value->ptr = &value->vbool;
      break;
    }

    case 0x02:
    {
      value->type = 0x80061;
      value->vbool = 0;
      value->ptr = &value->vbool;
      break;
    }

  }

  return 1;
}


----------------------------
***/


void *binn_list_read_next(binn_iter *iter, int *ptype, int *psize)
{
  binn value;
  if (binn_list_next(iter, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
BOOL binn_list_next(binn_iter *iter, binn *value)
{
  unsigned char *pnow;
  unsigned int pnow_idx = 0;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != 0xE0))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  pnow_idx = iter->pnext;
  iter->pnext = AdvanceDataPos(pnow, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&pnow[pnow_idx])))
  {
    return 0;
  }
  return GetValue(pnow, value);
}


----------------------------
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


void *binn_map_read_next(binn_iter *iter, int *pid, int *ptype, int *psize)
{
  binn value;
  if (binn_map_next(iter, pid, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
BOOL binn_map_next(binn_iter *iter, int *pid, binn *value)
{
  return binn_read_next_pair(0xE1, iter, pid, 0, value);
}


----------------------------
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


void *binn_object_read_next(binn_iter *iter, char *pkey, int *ptype, int *psize)
{
  binn value;
  if (binn_object_next(iter, pkey, &value) == 0)
  {
    return 0;
  }
  if (ptype)
  {
    *ptype = value.type;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return store_value(&value);
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
static void *store_value(binn *value)
{
  memcpy(&local_value, value, sizeof(binn));
  switch (binn_get_read_storage(value->type))
  {
    case 0x00:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return &local_value.vint32;
    }

  }

  return value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
BOOL binn_object_next(binn_iter *iter, char *pkey, binn *value)
{
  return binn_read_next_pair(0xE2, iter, 0, pkey, value);
}


----------------------------
***/


BOOL binn_set_string(binn *item, char *str, binn_mem_free pfree)
{
  if ((item == 0) || (str == 0))
  {
    return 0;
  }
  if (pfree == ((binn_mem_free) (-1)))
  {
    item->ptr = binn_memdup(str, strlen(str) + 1);
    if (item->ptr == 0)
    {
      return 0;
    }
    item->freefn = free_fn;
  }
  else
  {
    item->ptr = str;
    item->freefn = pfree;
  }
  item->type = 0xA0;
  return 1;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
typedef void (*binn_mem_free)(void *)
----------------------------
static void *binn_memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = binn_malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


BOOL binn_set_blob(binn *item, void *ptr, int size, binn_mem_free pfree)
{
  if ((item == 0) || (ptr == 0))
  {
    return 0;
  }
  if (pfree == ((binn_mem_free) (-1)))
  {
    item->ptr = binn_memdup(ptr, size);
    if (item->ptr == 0)
    {
      return 0;
    }
    item->freefn = free_fn;
  }
  else
  {
    item->ptr = ptr;
    item->freefn = pfree;
  }
  item->type = 0xC0;
  item->size = size;
  return 1;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
typedef void (*binn_mem_free)(void *)
----------------------------
static void *binn_memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = binn_malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}


----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


char *binn_get_str(binn *value)
{
  int64 vint;
  char buf[128];
  if (value == 0)
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    if (copy_int_value(value->ptr, &vint, value->type, 0x81) == 0)
    {
      return 0;
    }
    snprintf(buf, sizeof(buf), "%lli", vint);
    goto loc_convert_value;
  }
  switch (value->type)
  {
    case 0x62:
    {
      value->vdouble = value->vfloat;
    }

    case 0x82:
    {
      snprintf(buf, sizeof(buf), "%g", value->vdouble);
      goto loc_convert_value;
    }

    case 0xA0:
    {
      return (char *) value->ptr;
    }

    case 0x80061:
    {
      if (value->vbool)
      {
        strcpy(buf, "true");
      }
      else
        strcpy(buf, "false");
      goto loc_convert_value;
    }

  }

  return 0;
  loc_convert_value:
  value->ptr = strdup(buf);

  if (value->ptr == 0)
  {
    return 0;
  }
  value->freefn = free;
  value->type = 0xA0;
  return (char *) value->ptr;
}


/*** DEPENDENCIES:
typedef struct binn_struct binn
----------------------------
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
typedef long long int int64
----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
***/


binn *binn_list_next_value(binn_iter *iter)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_list_next(iter, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
BOOL binn_list_next(binn_iter *iter, binn *value)
{
  unsigned char *pnow;
  unsigned int pnow_idx = 0;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != 0xE0))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  pnow_idx = iter->pnext;
  iter->pnext = AdvanceDataPos(pnow, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&pnow[pnow_idx])))
  {
    return 0;
  }
  return GetValue(pnow, value);
}


----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
***/


binn *binn_map_next_value(binn_iter *iter, int *pid)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_map_next(iter, pid, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
BOOL binn_map_next(binn_iter *iter, int *pid, binn *value)
{
  return binn_read_next_pair(0xE1, iter, pid, 0, value);
}


----------------------------
***/


binn *binn_object_next_value(binn_iter *iter, char *pkey)
{
  binn *value;
  unsigned int value_idx = 0;
  value_idx = (binn *) binn_malloc(sizeof(binn));
  if (binn_object_next(iter, pkey, value) == 0)
  {
    free_fn(value);
    return 0;
  }
  value->allocated = 1;
  return value;
}


/*** DEPENDENCIES:
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
static void *binn_malloc(int size)
{
  check_alloc_functions();
  return malloc_fn(size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
void (*free_fn)(void *ptr) = 0
----------------------------
BOOL binn_object_next(binn_iter *iter, char *pkey, binn *value)
{
  return binn_read_next_pair(0xE2, iter, 0, pkey, value);
}


----------------------------
***/


BOOL binn_get_int32(binn *value, int *pint)
{
  if ((value == 0) || (pint == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    return copy_int_value(value->ptr, pint, value->type, 0x61);
  }
  switch (value->type)
  {
    case 0x62:
    {
      if ((value->vfloat < INT32_MIN) || (value->vfloat > INT32_MAX))
      {
        return 0;
      }
      *pint = (value->vfloat >= 0.0) ? ((int) (value->vfloat + 0.5)) : (((value->vfloat - ((double) ((int) value->vfloat))) <= (-0.5)) ? ((int) value->vfloat) : ((int) (value->vfloat - 0.5)));
      break;
    }

    case 0x82:
    {
      if ((value->vdouble < INT32_MIN) || (value->vdouble > INT32_MAX))
      {
        return 0;
      }
      *pint = (value->vdouble >= 0.0) ? ((int) (value->vdouble + 0.5)) : (((value->vdouble - ((double) ((int) value->vdouble))) <= (-0.5)) ? ((int) value->vdouble) : ((int) (value->vdouble - 0.5)));
      break;
    }

    case 0xA0:
    {
      if (is_integer((char *) value->ptr))
      {
        *pint = atoi((char *) value->ptr);
      }
      else
        if (is_float((char *) value->ptr))
      {
        *pint = (atof((char *) value->ptr) >= 0.0) ? ((int) (atof((char *) value->ptr) + 0.5)) : (((atof((char *) value->ptr) - ((double) ((int) atof((char *) value->ptr)))) <= (-0.5)) ? ((int) atof((char *) value->ptr)) : ((int) (atof((char *) value->ptr) - 0.5)));
      }
      else
        return 0;
      break;
    }

    case 0x80061:
    {
      *pint = value->vbool;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
static BOOL is_float(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  BOOL number_found = 0;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] == '.') || (p[p_idx] == ','))
    {
      if (!number_found)
      {
        retval = 0;
      }
    }
    else
      if ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
    {
      number_found = 1;
    }
    else
    {
      return 0;
    }
  }

  return retval;
}


----------------------------
static BOOL is_integer(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] < '0') || (p[p_idx] > '9'))
    {
      retval = 0;
    }
  }

  return retval;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_add_value(binn *item, int binn_type, int id, char *name, int type, void *pvalue, int size)
{
  switch (binn_type)
  {
    case 0xE0:
    {
      return binn_list_add(item, type, pvalue, size);
    }

    case 0xE1:
    {
      return binn_map_set(item, id, type, pvalue, size);
    }

    case 0xE2:
    {
      return binn_object_set(item, name, type, pvalue, size);
    }

    default:
    {
      return 0;
    }

  }

}


/*** DEPENDENCIES:
int binn_type(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      return item->type;
    }

    case 2:
    {
      return binn_buf_type(ptr);
    }

    default:
    {
      return -1;
    }

  }

}


----------------------------
BOOL binn_map_set(binn *map, int id, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_map_set_raw(map, id, type, pvalue, size);
}


----------------------------
BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_object_set_raw(obj, key, type, pvalue, size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
BOOL binn_list_add(binn *list, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_list_add_raw(list, type, pvalue, size);
}


----------------------------
***/


static BOOL is_bool_str(char *str, BOOL *pbool)
{
  int64 vint;
  double vdouble;
  if ((str == 0) || (pbool == 0))
  {
    return 0;
  }
  if (strcasecmp(str, "true") == 0)
  {
    goto loc_true;
  }
  if (strcasecmp(str, "yes") == 0)
  {
    goto loc_true;
  }
  if (strcasecmp(str, "on") == 0)
  {
    goto loc_true;
  }
  if (strcasecmp(str, "false") == 0)
  {
    goto loc_false;
  }
  if (strcasecmp(str, "no") == 0)
  {
    goto loc_false;
  }
  if (strcasecmp(str, "off") == 0)
  {
    goto loc_false;
  }
  if (is_integer(str))
  {
    vint = atoi64(str);
    *pbool = (vint != 0) ? (1) : (0);
    return 1;
  }
  else
    if (is_float(str))
  {
    vdouble = atof(str);
    *pbool = (vdouble != 0) ? (1) : (0);
    return 1;
  }
  return 0;
  loc_true:
  *pbool = 1;

  return 1;
  loc_false:
  *pbool = 0;

  return 1;
}


/*** DEPENDENCIES:
int64 atoi64(char *str)
{
  unsigned int str_idx = 0;
  int64 retval;
  int is_negative = 0;
  if (str[str_idx] == '-')
  {
    is_negative = 1;
    str_idx += 1;
  }
  retval = 0;
  for (; str[str_idx]; str_idx += 1)
  {
    retval = (10 * retval) + (str[str_idx] - '0');
  }

  if (is_negative)
  {
    retval *= -1;
  }
  return retval;
}


----------------------------
typedef long long int int64
----------------------------
static BOOL is_float(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  BOOL number_found = 0;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] == '.') || (p[p_idx] == ','))
    {
      if (!number_found)
      {
        retval = 0;
      }
    }
    else
      if ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
    {
      number_found = 1;
    }
    else
    {
      return 0;
    }
  }

  return retval;
}


----------------------------
static BOOL is_integer(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] < '0') || (p[p_idx] > '9'))
    {
      retval = 0;
    }
  }

  return retval;
}


----------------------------
typedef int BOOL
----------------------------
***/


BOOL binn_get_bool(binn *value, BOOL *pbool)
{
  int64 vint;
  if ((value == 0) || (pbool == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    if (copy_int_value(value->ptr, &vint, value->type, 0x81) == 0)
    {
      return 0;
    }
    *pbool = (vint != 0) ? (1) : (0);
    return 1;
  }
  switch (value->type)
  {
    case 0x80061:
    {
      *pbool = value->vbool;
      break;
    }

    case 0x62:
    {
      *pbool = (value->vfloat != 0) ? (1) : (0);
      break;
    }

    case 0x82:
    {
      *pbool = (value->vdouble != 0) ? (1) : (0);
      break;
    }

    case 0xA0:
    {
      return is_bool_str((char *) value->ptr, pbool);
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
typedef long long int int64
----------------------------
typedef struct binn_struct binn
----------------------------
static BOOL is_bool_str(char *str, BOOL *pbool)
{
  int64 vint;
  double vdouble;
  if ((str == 0) || (pbool == 0))
  {
    return 0;
  }
  if (strcasecmp(str, "true") == 0)
  {
    goto loc_true;
  }
  if (strcasecmp(str, "yes") == 0)
  {
    goto loc_true;
  }
  if (strcasecmp(str, "on") == 0)
  {
    goto loc_true;
  }
  if (strcasecmp(str, "false") == 0)
  {
    goto loc_false;
  }
  if (strcasecmp(str, "no") == 0)
  {
    goto loc_false;
  }
  if (strcasecmp(str, "off") == 0)
  {
    goto loc_false;
  }
  if (is_integer(str))
  {
    vint = atoi64(str);
    *pbool = (vint != 0) ? (1) : (0);
    return 1;
  }
  else
    if (is_float(str))
  {
    vdouble = atof(str);
    *pbool = (vdouble != 0) ? (1) : (0);
    return 1;
  }
  return 0;
  loc_true:
  *pbool = 1;

  return 1;
  loc_false:
  *pbool = 0;

  return 1;
}


----------------------------
typedef int BOOL
----------------------------
***/


BOOL binn_get_int64(binn *value, int64 *pint)
{
  if ((value == 0) || (pint == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    return copy_int_value(value->ptr, pint, value->type, 0x81);
  }
  switch (value->type)
  {
    case 0x62:
    {
      if ((value->vfloat < INT64_MIN) || (value->vfloat > INT64_MAX))
      {
        return 0;
      }
      *pint = (value->vfloat >= 0.0) ? ((int) (value->vfloat + 0.5)) : (((value->vfloat - ((double) ((int) value->vfloat))) <= (-0.5)) ? ((int) value->vfloat) : ((int) (value->vfloat - 0.5)));
      break;
    }

    case 0x82:
    {
      if ((value->vdouble < INT64_MIN) || (value->vdouble > INT64_MAX))
      {
        return 0;
      }
      *pint = (value->vdouble >= 0.0) ? ((int) (value->vdouble + 0.5)) : (((value->vdouble - ((double) ((int) value->vdouble))) <= (-0.5)) ? ((int) value->vdouble) : ((int) (value->vdouble - 0.5)));
      break;
    }

    case 0xA0:
    {
      if (is_integer((char *) value->ptr))
      {
        *pint = atoi64((char *) value->ptr);
      }
      else
        if (is_float((char *) value->ptr))
      {
        *pint = (atof((char *) value->ptr) >= 0.0) ? ((int) (atof((char *) value->ptr) + 0.5)) : (((atof((char *) value->ptr) - ((double) ((int) atof((char *) value->ptr)))) <= (-0.5)) ? ((int) atof((char *) value->ptr)) : ((int) (atof((char *) value->ptr) - 0.5)));
      }
      else
        return 0;
      break;
    }

    case 0x80061:
    {
      *pint = value->vbool;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
int64 atoi64(char *str)
{
  unsigned int str_idx = 0;
  int64 retval;
  int is_negative = 0;
  if (str[str_idx] == '-')
  {
    is_negative = 1;
    str_idx += 1;
  }
  retval = 0;
  for (; str[str_idx]; str_idx += 1)
  {
    retval = (10 * retval) + (str[str_idx] - '0');
  }

  if (is_negative)
  {
    retval *= -1;
  }
  return retval;
}


----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
typedef long long int int64
----------------------------
static BOOL is_float(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  BOOL number_found = 0;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] == '.') || (p[p_idx] == ','))
    {
      if (!number_found)
      {
        retval = 0;
      }
    }
    else
      if ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
    {
      number_found = 1;
    }
    else
    {
      return 0;
    }
  }

  return retval;
}


----------------------------
static BOOL is_integer(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] < '0') || (p[p_idx] > '9'))
    {
      retval = 0;
    }
  }

  return retval;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


BOOL binn_get_double(binn *value, double *pfloat)
{
  int64 vint;
  if ((value == 0) || (pfloat == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    if (copy_int_value(value->ptr, &vint, value->type, 0x81) == 0)
    {
      return 0;
    }
    *pfloat = (double) vint;
    return 1;
  }
  switch (value->type)
  {
    case 0x62:
    {
      *pfloat = value->vfloat;
      break;
    }

    case 0x82:
    {
      *pfloat = value->vdouble;
      break;
    }

    case 0xA0:
    {
      if (is_integer((char *) value->ptr))
      {
        *pfloat = (double) atoi64((char *) value->ptr);
      }
      else
        if (is_float((char *) value->ptr))
      {
        *pfloat = atof((char *) value->ptr);
      }
      else
        return 0;
      break;
    }

    case 0x80061:
    {
      *pfloat = value->vbool;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


/*** DEPENDENCIES:
static int type_family(int type)
{
  switch (type)
  {
    case 0xE0:

    case 0xE1:

    case 0xE2:
    {
      return 0xf7;
    }

    case 0x21:

    case 0x41:

    case 0x61:

    case 0x81:

    case 0x20:

    case 0x40:

    case 0x60:

    case 0x80:
    {
      return 0xf2;
    }

    case 0x62:

    case 0x82:

    case 0xA6:

    case 0xA7:
    {
      return 0xf3;
    }

    case 0xA0:

    case 0xB001:

    case 0xB005:

    case 0xB002:

    case 0xB003:

    case 0xB004:
    {
      return 0xf4;
    }

    case 0xC0:

    case 0xD001:

    case 0xD002:

    case 0xD003:

    case 0xD004:
    {
      return 0xf5;
    }

    case 0xA4:

    case 0x83:

    case 0xA2:

    case 0xA3:

    case 0xA1:
    {
      return 0xf4;
    }

    case 0x80061:
    {
      return 0xf6;
    }

    case 0x00:
    {
      return 0xf1;
    }

    default:
    {
      return 0x00;
    }

  }

}


----------------------------
int64 atoi64(char *str)
{
  unsigned int str_idx = 0;
  int64 retval;
  int is_negative = 0;
  if (str[str_idx] == '-')
  {
    is_negative = 1;
    str_idx += 1;
  }
  retval = 0;
  for (; str[str_idx]; str_idx += 1)
  {
    retval = (10 * retval) + (str[str_idx] - '0');
  }

  if (is_negative)
  {
    retval *= -1;
  }
  return retval;
}


----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
typedef long long int int64
----------------------------
static BOOL is_float(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  BOOL number_found = 0;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] == '.') || (p[p_idx] == ','))
    {
      if (!number_found)
      {
        retval = 0;
      }
    }
    else
      if ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
    {
      number_found = 1;
    }
    else
    {
      return 0;
    }
  }

  return retval;
}


----------------------------
static BOOL is_integer(char *p)
{
  unsigned int p_idx = 0;
  BOOL retval;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if (p[p_idx] == '-')
  {
    p_idx += 1;
  }
  if (p[p_idx] == 0)
  {
    return 0;
  }
  retval = 1;
  for (; p[p_idx]; p_idx += 1)
  {
    if ((p[p_idx] < '0') || (p[p_idx] > '9'))
    {
      retval = 0;
    }
  }

  return retval;
}


----------------------------
typedef struct binn_struct binn
----------------------------
***/


