typedef struct buffered_s
{
  mi_output_fun *out;
  void *arg;
  char *buf;
  size_t used;
  size_t count;
} buffered_t
/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
***/


