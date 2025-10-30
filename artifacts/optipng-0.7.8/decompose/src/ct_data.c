typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data
/*** DEPENDENCIES:
typedef unsigned short ush
----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
***/


