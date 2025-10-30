void png_flush(png_structrp png_ptr)
{
  if (png_ptr->output_flush_fn != 0)
  {
    (*png_ptr->output_flush_fn)(png_ptr);
  }
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_default_flush(png_structp png_ptr)
{
  png_FILE_p io_ptr;
  if (png_ptr == 0)
  {
    return;
  }
  io_ptr = png_ptr->io_ptr;
  fflush(io_ptr);
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef FILE *png_FILE_p
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_default_write_data(png_structp png_ptr, png_bytep data, size_t length)
{
  size_t check;
  if (png_ptr == 0)
  {
    return;
  }
  check = fwrite(data, 1, length, (png_FILE_p) png_ptr->io_ptr);
  if (check != length)
  {
    png_error(png_ptr, "Write Error");
  }
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
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


void png_set_write_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (write_data_fn != 0)
  {
    png_ptr->write_data_fn = write_data_fn;
  }
  else
    png_ptr->write_data_fn = png_default_write_data;
  if (output_flush_fn != 0)
  {
    png_ptr->output_flush_fn = output_flush_fn;
  }
  else
    png_ptr->output_flush_fn = png_default_flush;
  if (png_ptr->read_data_fn != 0)
  {
    png_ptr->read_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
}


/*** DEPENDENCIES:
typedef void *voidp
----------------------------
typedef void (*png_rw_ptr)(png_structp, png_bytep, size_t)
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
void png_default_flush(png_structp png_ptr)
{
  png_FILE_p io_ptr;
  if (png_ptr == 0)
  {
    return;
  }
  io_ptr = png_ptr->io_ptr;
  fflush(io_ptr);
}


----------------------------
typedef unsigned short ush
----------------------------
typedef void (*png_flush_ptr)(png_structp)
----------------------------
typedef png_struct *png_structrp
----------------------------
void png_default_write_data(png_structp png_ptr, png_bytep data, size_t length)
{
  size_t check;
  if (png_ptr == 0)
  {
    return;
  }
  check = fwrite(data, 1, length, (png_FILE_p) png_ptr->io_ptr);
  if (check != length)
  {
    png_error(png_ptr, "Write Error");
  }
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef void *png_voidp
----------------------------
***/


void png_write_data(png_structrp png_ptr, png_const_bytep data, size_t length)
{
  if (png_ptr->write_data_fn != 0)
  {
    (*png_ptr->write_data_fn)(png_ptr, (png_bytep) ((void *) ((const void *) data)), length);
  }
  else
    png_error(png_ptr, "Call to NULL write function");
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


