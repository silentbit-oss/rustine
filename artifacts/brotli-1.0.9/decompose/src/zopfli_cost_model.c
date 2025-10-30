typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
/*** DEPENDENCIES:
***/


