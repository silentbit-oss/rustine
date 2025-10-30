void png_longjmp(png_const_structrp png_ptr, int val)
{
  (void) png_ptr;
  (void) val;
  abort();
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_voidp png_get_error_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return (png_voidp) png_ptr->error_ptr;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


size_t png_safecat(png_charp buffer, size_t bufsize, size_t pos, png_const_charp string)
{
  if ((buffer != 0) && (pos < bufsize))
  {
    if (string != 0)
    {
      while (((*string) != '\0') && (pos < (bufsize - 1)))
      {
        buffer[pos] = *string;
        string += 1;
        pos += 1;
      }

    }
    buffer[pos] = '\0';
  }
  return pos;
}


/*** DEPENDENCIES:
typedef char *png_charp
----------------------------
typedef const char *png_const_charp
----------------------------
***/


static void png_default_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  {
    fprintf(stderr, "libpng warning: %s", warning_message);
    fprintf(stderr, "\n");
  }
  (void) png_ptr;
}


/*** DEPENDENCIES:
typedef const char *png_const_charp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


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


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
----------------------------
static void png_default_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  {
    fprintf(stderr, "libpng warning: %s", warning_message);
    fprintf(stderr, "\n");
  }
  (void) png_ptr;
}


----------------------------
***/


static void png_default_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  {
    fprintf(stderr, "libpng error: %s", (error_message) ? (error_message) : ("undefined"));
    fprintf(stderr, "\n");
  }
  png_longjmp(png_ptr, 1);
}


/*** DEPENDENCIES:
void png_longjmp(png_const_structrp png_ptr, int val)
{
  (void) png_ptr;
  (void) val;
  abort();
}


----------------------------
typedef const char *png_const_charp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


/*** DEPENDENCIES:
static void png_default_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  {
    fprintf(stderr, "libpng error: %s", (error_message) ? (error_message) : ("undefined"));
    fprintf(stderr, "\n");
  }
  png_longjmp(png_ptr, 1);
}


----------------------------
typedef const char *png_const_charp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
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
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
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
***/


void png_set_error_fn(png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->error_ptr = error_ptr;
  png_ptr->error_fn = error_fn;
  png_ptr->warning_fn = warning_fn;
}


/*** DEPENDENCIES:
typedef void *voidp
----------------------------
typedef void (*png_error_ptr)(png_structp, png_const_charp)
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef void *png_voidp
----------------------------
***/


static void png_format_buffer(png_const_structrp png_ptr, png_charp buffer, png_const_charp error_message)
{
  png_uint_32 chunk_name = png_ptr->chunk_name;
  int iout = 0;
  int ishift = 24;
  while (ishift >= 0)
  {
    int c = ((int) (chunk_name >> ishift)) & 0xff;
    ishift -= 8;
    if ((((c < 65) || (c > 122)) || ((c > 90) && (c < 97))) != 0)
    {
      buffer[iout] = 0x5b;
      iout += 1;
      buffer[iout] = png_digit[(c & 0xf0) >> 4];
      iout += 1;
      buffer[iout] = png_digit[c & 0x0f];
      iout += 1;
      buffer[iout] = 0x5d;
      iout += 1;
    }
    else
    {
      buffer[iout] = (char) c;
      iout += 1;
    }
  }

  if (error_message == 0)
  {
    buffer[iout] = '\0';
  }
  else
  {
    int iin = 0;
    buffer[iout] = ':';
    iout += 1;
    buffer[iout] = ' ';
    iout += 1;
    while ((iin < (196 - 1)) && (error_message[iin] != '\0'))
    {
      buffer[iout] = error_message[iin];
      iin += 1;
      iout += 1;
    }

    buffer[iout] = '\0';
  }
}


/*** DEPENDENCIES:
typedef char *png_charp
----------------------------
typedef unsigned int png_uint_32
----------------------------
static const char png_digit[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
----------------------------
***/


void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}


/*** DEPENDENCIES:
static void png_format_buffer(png_const_structrp png_ptr, png_charp buffer, png_const_charp error_message)
{
  png_uint_32 chunk_name = png_ptr->chunk_name;
  int iout = 0;
  int ishift = 24;
  while (ishift >= 0)
  {
    int c = ((int) (chunk_name >> ishift)) & 0xff;
    ishift -= 8;
    if ((((c < 65) || (c > 122)) || ((c > 90) && (c < 97))) != 0)
    {
      buffer[iout] = 0x5b;
      iout += 1;
      buffer[iout] = png_digit[(c & 0xf0) >> 4];
      iout += 1;
      buffer[iout] = png_digit[c & 0x0f];
      iout += 1;
      buffer[iout] = 0x5d;
      iout += 1;
    }
    else
    {
      buffer[iout] = (char) c;
      iout += 1;
    }
  }

  if (error_message == 0)
  {
    buffer[iout] = '\0';
  }
  else
  {
    int iin = 0;
    buffer[iout] = ':';
    iout += 1;
    buffer[iout] = ' ';
    iout += 1;
    while ((iin < (196 - 1)) && (error_message[iin] != '\0'))
    {
      buffer[iout] = error_message[iin];
      iin += 1;
      iout += 1;
    }

    buffer[iout] = '\0';
  }
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
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
***/


void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_error(png_ptr, error_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
  }
}


/*** DEPENDENCIES:
static void png_format_buffer(png_const_structrp png_ptr, png_charp buffer, png_const_charp error_message)
{
  png_uint_32 chunk_name = png_ptr->chunk_name;
  int iout = 0;
  int ishift = 24;
  while (ishift >= 0)
  {
    int c = ((int) (chunk_name >> ishift)) & 0xff;
    ishift -= 8;
    if ((((c < 65) || (c > 122)) || ((c > 90) && (c < 97))) != 0)
    {
      buffer[iout] = 0x5b;
      iout += 1;
      buffer[iout] = png_digit[(c & 0xf0) >> 4];
      iout += 1;
      buffer[iout] = png_digit[c & 0x0f];
      iout += 1;
      buffer[iout] = 0x5d;
      iout += 1;
    }
    else
    {
      buffer[iout] = (char) c;
      iout += 1;
    }
  }

  if (error_message == 0)
  {
    buffer[iout] = '\0';
  }
  else
  {
    int iin = 0;
    buffer[iout] = ':';
    iout += 1;
    buffer[iout] = ' ';
    iout += 1;
    while ((iin < (196 - 1)) && (error_message[iin] != '\0'))
    {
      buffer[iout] = error_message[iin];
      iin += 1;
      iout += 1;
    }

    buffer[iout] = '\0';
  }
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
typedef const char *png_const_charp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    png_chunk_warning(png_ptr, error_message);
  }
  else
    png_chunk_error(png_ptr, error_message);
}


/*** DEPENDENCIES:
void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_error(png_ptr, error_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
  }
}


----------------------------
void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}


----------------------------
typedef const char *png_const_charp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_warning(png_ptr, error_message);
    }
    else
      png_warning(png_ptr, error_message);
  }
  else
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_error(png_ptr, error_message);
    }
    else
      png_error(png_ptr, error_message);
  }
}


/*** DEPENDENCIES:
void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}


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
void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_error(png_ptr, error_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
  }
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
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
***/


void png_app_warning(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x200000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
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
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
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
***/


void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error)
{
  if ((png_ptr->mode & 0x8000U) != 0)
  {
    if (error < 2)
    {
      png_chunk_warning(png_ptr, message);
    }
    else
      png_chunk_benign_error(png_ptr, message);
  }
  else
    if ((png_ptr->mode & 0x8000U) == 0)
  {
    if (error < 1)
    {
      png_app_warning(png_ptr, message);
    }
    else
      png_app_error(png_ptr, message);
  }
}


/*** DEPENDENCIES:
void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}


----------------------------
void png_app_warning(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x200000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}


----------------------------
void png_chunk_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_warning(png_ptr, warning_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, warning_message);
    png_warning(png_ptr, msg);
  }
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
----------------------------
void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    png_chunk_warning(png_ptr, error_message);
  }
  else
    png_chunk_error(png_ptr, error_message);
}


----------------------------
***/


void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string)
{
  if ((number > 0) && (number <= 8))
  {
    (void) png_safecat(p[number - 1], sizeof(p[number - 1]), 0, string);
  }
}


/*** DEPENDENCIES:
typedef char png_warning_parameters[8][32]
----------------------------
typedef const char *png_const_charp
----------------------------
size_t png_safecat(png_charp buffer, size_t bufsize, size_t pos, png_const_charp string)
{
  if ((buffer != 0) && (pos < bufsize))
  {
    if (string != 0)
    {
      while (((*string) != '\0') && (pos < (bufsize - 1)))
      {
        buffer[pos] = *string;
        string += 1;
        pos += 1;
      }

    }
    buffer[pos] = '\0';
  }
  return pos;
}


----------------------------
***/


// hint:  ['end_ref is a mutable refrence to png_charp', 'number_ref is a mutable refrence to png_alloc_size_t', 'count_ref is a mutable refrence to int', 'mincount_ref is a mutable refrence to int', 'output_ref is a mutable refrence to int']
void helper_png_format_number_1(png_charp * const end_ref, png_alloc_size_t * const number_ref, int * const count_ref, int * const mincount_ref, int * const output_ref, png_const_charp start, int format)
{
  png_charp end = *end_ref;
  png_alloc_size_t number = *number_ref;
  int count = *count_ref;
  int mincount = *mincount_ref;
  int output = *output_ref;
  static const char digits[] = "0123456789ABCDEF";
  switch (format)
  {
    case 5:
    {
      mincount = 5;
      if ((output != 0) || ((number % 10) != 0))
      {
        end -= 1;
        *end = digits[number % 10];
        output = 1;
      }
      number /= 10;
      break;
    }

    case 2:
    {
      mincount = 2;
    }

    case 1:
    {
      end -= 1;
      *end = digits[number % 10];
      number /= 10;
      break;
    }

    case 4:
    {
      mincount = 2;
    }

    case 3:
    {
      end -= 1;
      *end = digits[number & 0xf];
      number >>= 4;
      break;
    }

    default:
    {
      number = 0;
      break;
    }

  }

  count += 1;
  if (((format == 5) && (count == 5)) && (end > start))
  {
    if (output != 0)
    {
      end -= 1;
      *end = '.';
    }
    else
      if (number == 0)
    {
      end -= 1;
      *end = '0';
    }
  }
  *end_ref = end;
  *number_ref = number;
  *count_ref = count;
  *mincount_ref = mincount;
  *output_ref = output;
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef char *png_charp
----------------------------
typedef const char *png_const_charp
----------------------------
***/


png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number)
{
  int count = 0;
  int mincount = 1;
  int output = 0;
  end -= 1;
  *end = '\0';
  while ((end > start) && ((number != 0) || (count < mincount)))
  {
    helper_png_format_number_1(&end, &number, &count, &mincount, &output, start, format);
  }

  return end;
}


/*** DEPENDENCIES:
typedef char *png_charp
----------------------------
typedef size_t png_alloc_size_t
----------------------------
void helper_png_format_number_1(png_charp * const end_ref, png_alloc_size_t * const number_ref, int * const count_ref, int * const mincount_ref, int * const output_ref, png_const_charp start, int format)
{
  png_charp end = *end_ref;
  png_alloc_size_t number = *number_ref;
  int count = *count_ref;
  int mincount = *mincount_ref;
  int output = *output_ref;
  static const char digits[] = "0123456789ABCDEF";
  switch (format)
  {
    case 5:
    {
      mincount = 5;
      if ((output != 0) || ((number % 10) != 0))
      {
        end -= 1;
        *end = digits[number % 10];
        output = 1;
      }
      number /= 10;
      break;
    }

    case 2:
    {
      mincount = 2;
    }

    case 1:
    {
      end -= 1;
      *end = digits[number % 10];
      number /= 10;
      break;
    }

    case 4:
    {
      mincount = 2;
    }

    case 3:
    {
      end -= 1;
      *end = digits[number & 0xf];
      number >>= 4;
      break;
    }

    default:
    {
      number = 0;
      break;
    }

  }

  count += 1;
  if (((format == 5) && (count == 5)) && (end > start))
  {
    if (output != 0)
    {
      end -= 1;
      *end = '.';
    }
    else
      if (number == 0)
    {
      end -= 1;
      *end = '0';
    }
  }
  *end_ref = end;
  *number_ref = number;
  *count_ref = count;
  *mincount_ref = mincount;
  *output_ref = output;
}


----------------------------
typedef const char *png_const_charp
----------------------------
***/


void png_warning_parameter_unsigned(png_warning_parameters p, int number, int format, png_alloc_size_t value)
{
  char buffer[24];
  png_warning_parameter(p, number, png_format_number(buffer, buffer + (sizeof(buffer)), format, value));
}


/*** DEPENDENCIES:
typedef char png_warning_parameters[8][32]
----------------------------
typedef size_t png_alloc_size_t
----------------------------
png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number)
{
  int count = 0;
  int mincount = 1;
  int output = 0;
  end -= 1;
  *end = '\0';
  while ((end > start) && ((number != 0) || (count < mincount)))
  {
    helper_png_format_number_1(&end, &number, &count, &mincount, &output, start, format);
  }

  return end;
}


----------------------------
void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string)
{
  if ((number > 0) && (number <= 8))
  {
    (void) png_safecat(p[number - 1], sizeof(p[number - 1]), 0, string);
  }
}


----------------------------
***/


void png_formatted_warning(png_const_structrp png_ptr, png_warning_parameters p, png_const_charp message)
{
  size_t i = 0;
  char msg[192];
  while ((i < ((sizeof(msg)) - 1)) && ((*message) != '\0'))
  {
    if (((p != 0) && ((*message) == '@')) && (message[1] != '\0'))
    {
      message += 1;
      int parameter_char = *message;
      static const char valid_parameters[] = "123456789";
      int parameter = 0;
      while ((valid_parameters[parameter] != parameter_char) && (valid_parameters[parameter] != '\0'))
      {
        parameter += 1;
      }

      if (parameter < 8)
      {
        png_const_charp parm = p[parameter];
        png_const_charp pend = p[parameter] + (sizeof(p[parameter]));
        while (((i < ((sizeof(msg)) - 1)) && ((*parm) != '\0')) && (parm < pend))
        {
          msg[i] = *parm;
          parm += 1;
          i += 1;
        }

        message += 1;
        continue;
      }
    }
    msg[i] = *message;
    message += 1;
    i += 1;
  }

  msg[i] = '\0';
  png_warning(png_ptr, msg);
}


/*** DEPENDENCIES:
typedef char png_warning_parameters[8][32]
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef const char *png_const_charp
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
***/


void png_warning_parameter_signed(png_warning_parameters p, int number, int format, png_int_32 value)
{
  png_alloc_size_t u;
  png_charp str;
  char buffer[24];
  u = (png_alloc_size_t) value;
  if (value < 0)
  {
    u = (~u) + 1;
  }
  str = png_format_number(buffer, buffer + (sizeof(buffer)), format, u);
  if ((value < 0) && (str > buffer))
  {
    str -= 1;
    *str = '-';
  }
  png_warning_parameter(p, number, str);
}


/*** DEPENDENCIES:
typedef char png_warning_parameters[8][32]
----------------------------
typedef size_t png_alloc_size_t
----------------------------
void png_warning_parameter(png_warning_parameters p, int number, png_const_charp string)
{
  if ((number > 0) && (number <= 8))
  {
    (void) png_safecat(p[number - 1], sizeof(p[number - 1]), 0, string);
  }
}


----------------------------
typedef char *png_charp
----------------------------
typedef int png_int_32
----------------------------
png_charp png_format_number(png_const_charp start, png_charp end, int format, png_alloc_size_t number)
{
  int count = 0;
  int mincount = 1;
  int output = 0;
  end -= 1;
  *end = '\0';
  while ((end > start) && ((number != 0) || (count < mincount)))
  {
    helper_png_format_number_1(&end, &number, &count, &mincount, &output, start, format);
  }

  return end;
}


----------------------------
***/


