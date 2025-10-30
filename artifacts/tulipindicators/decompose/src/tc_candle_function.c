typedef int (*tc_candle_function)(int size, const TC_REAL * const *inputs, const tc_config *options, tc_result *output)
/*** DEPENDENCIES:
typedef double TC_REAL
----------------------------
typedef struct tc_config
{
  int period;
  TC_REAL body_none;
  TC_REAL body_short;
  TC_REAL body_long;
  TC_REAL wick_none;
  TC_REAL wick_long;
  TC_REAL near;
} tc_config
----------------------------
struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
----------------------------
***/


