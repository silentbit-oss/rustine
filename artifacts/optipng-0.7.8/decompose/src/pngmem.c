png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size)
{
  (void) png_ptr;
  if ((size > 0) && (size <= ((size_t) (-1))))
  {
    return malloc((size_t) size);
  }
  else
    return 0;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size)
{
  (void) png_ptr;
  if ((size > 0) && (size <= ((size_t) (-1))))
  {
    return malloc((size_t) size);
  }
  else
    return 0;
}


----------------------------
typedef void *voidp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
typedef void *png_voidp
----------------------------
***/


void png_free(png_const_structrp png_ptr, png_voidp ptr)
{
  if ((png_ptr == 0) || (ptr == 0))
  {
    return;
  }
  free(ptr);
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
typedef void *png_voidp
----------------------------
typedef void *voidp
----------------------------
***/


png_voidp png_malloc_warn(png_const_structrp png_ptr, png_alloc_size_t size)
{
  if (png_ptr != 0)
  {
    png_voidp ret = png_malloc_base(png_ptr, size);
    if (ret != 0)
    {
      return ret;
    }
    png_warning(png_ptr, "Out of memory");
  }
  return 0;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size)
{
  (void) png_ptr;
  if ((size > 0) && (size <= ((size_t) (-1))))
  {
    return malloc((size_t) size);
  }
  else
    return 0;
}


----------------------------
typedef void *voidp
----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef void *png_voidp
----------------------------
***/


png_voidp png_calloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  ret = png_malloc(png_ptr, size);
  if (ret != 0)
  {
    memset(ret, 0, size);
  }
  return ret;
}


/*** DEPENDENCIES:
png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


----------------------------
typedef size_t png_alloc_size_t
----------------------------
typedef void *voidp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef void *png_voidp
----------------------------
***/


static png_voidp png_malloc_array_checked(png_const_structrp png_ptr, int nelements, size_t element_size)
{
  png_alloc_size_t req = (png_alloc_size_t) nelements;
  if (req <= (((size_t) (-1)) / element_size))
  {
    return png_malloc_base(png_ptr, req * element_size);
  }
  return 0;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size)
{
  (void) png_ptr;
  if ((size > 0) && (size <= ((size_t) (-1))))
  {
    return malloc((size_t) size);
  }
  else
    return 0;
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_voidp png_realloc_array(png_const_structrp png_ptr, png_const_voidp old_array, int old_elements, int add_elements, size_t element_size)
{
  if ((((add_elements <= 0) || (element_size == 0)) || (old_elements < 0)) || ((old_array == 0) && (old_elements > 0)))
  {
    png_error(png_ptr, "internal error: array realloc");
  }
  if (add_elements <= (2147483647 - old_elements))
  {
    png_voidp new_array = png_malloc_array_checked(png_ptr, old_elements + add_elements, element_size);
    if (new_array != 0)
    {
      if (old_elements > 0)
      {
        memcpy(new_array, old_array, element_size * ((unsigned) old_elements));
      }
      memset(((char *) new_array) + (element_size * ((unsigned) old_elements)), 0, element_size * ((unsigned) add_elements));
      return new_array;
    }
  }
  return 0;
}


/*** DEPENDENCIES:
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
typedef void *voidp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
static png_voidp png_malloc_array_checked(png_const_structrp png_ptr, int nelements, size_t element_size)
{
  png_alloc_size_t req = (png_alloc_size_t) nelements;
  if (req <= (((size_t) (-1)) / element_size))
  {
    return png_malloc_base(png_ptr, req * element_size);
  }
  return 0;
}


----------------------------
typedef const void *png_const_voidp
----------------------------
typedef void *png_voidp
----------------------------
***/


void png_destroy_png_struct(png_structrp png_ptr)
{
  if (png_ptr != 0)
  {
    png_struct dummy_struct = *png_ptr;
    memset(png_ptr, 0, sizeof(*png_ptr));
    png_free(&dummy_struct, png_ptr);
  }
}


/*** DEPENDENCIES:
void png_free(png_const_structrp png_ptr, png_voidp ptr)
{
  if ((png_ptr == 0) || (ptr == 0))
  {
    return;
  }
  free(ptr);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


png_voidp png_malloc_array(png_const_structrp png_ptr, int nelements, size_t element_size)
{
  if ((nelements <= 0) || (element_size == 0))
  {
    png_error(png_ptr, "internal error: array alloc");
  }
  return png_malloc_array_checked(png_ptr, nelements, element_size);
}


/*** DEPENDENCIES:
static png_voidp png_malloc_array_checked(png_const_structrp png_ptr, int nelements, size_t element_size)
{
  png_alloc_size_t req = (png_alloc_size_t) nelements;
  if (req <= (((size_t) (-1)) / element_size))
  {
    return png_malloc_base(png_ptr, req * element_size);
  }
  return 0;
}


----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


