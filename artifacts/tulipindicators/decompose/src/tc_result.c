struct tc_result
{
  int progress;
  int space;
  int count;
  int pattern_count;
  tc_hit *hits;
}
/*** DEPENDENCIES:
typedef struct tc_hit
{
  int index;
  tc_set patterns;
} tc_hit
----------------------------
***/


