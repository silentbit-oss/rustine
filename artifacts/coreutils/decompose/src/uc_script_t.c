typedef struct 
{
  unsigned int nintervals;
  const uc_interval_t *intervals;
  const char *name;
} uc_script_t
/*** DEPENDENCIES:
typedef struct 
{
  unsigned int code : 21;
  unsigned int start : 1;
  unsigned int end : 1;
} uc_interval_t
----------------------------
***/


