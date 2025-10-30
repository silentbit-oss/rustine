typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
/*** DEPENDENCIES:
typedef struct PosData
{
  size_t pos;
  int distance_cache[4];
  float costdiff;
  float cost;
} PosData
----------------------------
***/


