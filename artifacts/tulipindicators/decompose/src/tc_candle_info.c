typedef struct tc_candle_info
{
  const char *name;
  const char *full_name;
  tc_set pattern;
  tc_candle_function candle;
} tc_candle_info
/*** DEPENDENCIES:
typedef int (*tc_candle_function)(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
----------------------------
typedef uint64_t tc_set
----------------------------
***/


