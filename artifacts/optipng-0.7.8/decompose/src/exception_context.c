struct exception_context
{
  jmp_buf *penv;
  int caught;
  volatile struct 
  {
    opng_status_t etmp;
  } v;
}
/*** DEPENDENCIES:
typedef enum 
{
  OPNG_STATUS_OK = 0,
  OPNG_STATUS_ERR_LIBPNG = -1,
  OPNG_STATUS_ERR_OPTIPNG = -2
} opng_status_t
----------------------------
***/


