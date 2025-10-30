typedef struct _expreval_t
{
  const char *code;
  size_t len;
  size_t head;
  lilint_t ival;
  double dval;
  int type;
  int error;
} expreval_t
/*** DEPENDENCIES:
typedef int64_t lilint_t
----------------------------
***/


