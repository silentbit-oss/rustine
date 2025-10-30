void png_default_read_data(png_structp png_ptr, png_bytep data, size_t length)
{
  size_t check;
  if (png_ptr == 0)
  {
    return;
  }
  check = fread(data, 1, length, png_ptr->io_ptr);
  if (check != length)
  {
    png_error(png_ptr, "Read Error");
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


void png_set_read_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (read_data_fn != 0)
  {
    png_ptr->read_data_fn = read_data_fn;
  }
  else
    png_ptr->read_data_fn = png_default_read_data;
  if (png_ptr->write_data_fn != 0)
  {
    png_ptr->write_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
  png_ptr->output_flush_fn = 0;
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
void png_default_read_data(png_structp png_ptr, png_bytep data, size_t length)
{
  size_t check;
  if (png_ptr == 0)
  {
    return;
  }
  check = fread(data, 1, length, png_ptr->io_ptr);
  if (check != length)
  {
    png_error(png_ptr, "Read Error");
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef void *png_voidp
----------------------------
***/


void png_read_data(png_structrp png_ptr, png_bytep data, size_t length)
{
  (void) 0;
  if (png_ptr->read_data_fn != 0)
  {
    (*png_ptr->read_data_fn)(png_ptr, data, length);
  }
  else
    png_error(png_ptr, "Call to NULL read function");
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
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


