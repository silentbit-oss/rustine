inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


/*** DEPENDENCIES:
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
***/


inline static double ClusterCostDiff(size_t size_a, size_t size_b)
{
  size_t size_c = size_a + size_b;
  return ((((double) size_a) * FastLog2(size_a)) + (((double) size_b) * FastLog2(size_b))) - (((double) size_c) * FastLog2(size_c));
}


/*** DEPENDENCIES:
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
***/


// hint:  ['num_pairs_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_BrotliHistogramCombineLiteral_1_1(size_t * const num_pairs_ref, size_t * const i_ref, HistogramPair * const pairs, uint32_t best_idx1, uint32_t best_idx2)
{
  size_t num_pairs = *num_pairs_ref;
  size_t i = *i_ref;
  size_t copy_to_idx = 0;
  for (i = 0; i < num_pairs; i += 1)
  {
    HistogramPair *p = &pairs[i];
    if ((((p->idx1 == best_idx1) || (p->idx2 == best_idx1)) || (p->idx1 == best_idx2)) || (p->idx2 == best_idx2))
    {
      continue;
    }
    if (HistogramPairIsLess(&pairs[0], p))
    {
      HistogramPair front = pairs[0];
      pairs[0] = *p;
      pairs[copy_to_idx] = front;
    }
    else
    {
      pairs[copy_to_idx] = *p;
    }
    copy_to_idx += 1;
  }

  num_pairs = copy_to_idx;
  *num_pairs_ref = num_pairs;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


----------------------------
***/


// hint:  ['num_pairs_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_BrotliHistogramCombineCommand_1_1(size_t * const num_pairs_ref, size_t * const i_ref, HistogramPair * const pairs, uint32_t best_idx1, uint32_t best_idx2)
{
  size_t num_pairs = *num_pairs_ref;
  size_t i = *i_ref;
  size_t copy_to_idx = 0;
  for (i = 0; i < num_pairs; i += 1)
  {
    HistogramPair *p = &pairs[i];
    if ((((p->idx1 == best_idx1) || (p->idx2 == best_idx1)) || (p->idx1 == best_idx2)) || (p->idx2 == best_idx2))
    {
      continue;
    }
    if (HistogramPairIsLess(&pairs[0], p))
    {
      HistogramPair front = pairs[0];
      pairs[0] = *p;
      pairs[copy_to_idx] = front;
    }
    else
    {
      pairs[copy_to_idx] = *p;
    }
    copy_to_idx += 1;
  }

  num_pairs = copy_to_idx;
  *num_pairs_ref = num_pairs;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


----------------------------
***/


// hint:  ['num_pairs_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t']
void helper_helper_BrotliHistogramCombineDistance_1_1(size_t * const num_pairs_ref, size_t * const i_ref, HistogramPair * const pairs, uint32_t best_idx1, uint32_t best_idx2)
{
  size_t num_pairs = *num_pairs_ref;
  size_t i = *i_ref;
  size_t copy_to_idx = 0;
  for (i = 0; i < num_pairs; i += 1)
  {
    HistogramPair *p = &pairs[i];
    if ((((p->idx1 == best_idx1) || (p->idx2 == best_idx1)) || (p->idx1 == best_idx2)) || (p->idx2 == best_idx2))
    {
      continue;
    }
    if (HistogramPairIsLess(&pairs[0], p))
    {
      HistogramPair front = pairs[0];
      pairs[0] = *p;
      pairs[copy_to_idx] = front;
    }
    else
    {
      pairs[copy_to_idx] = *p;
    }
    copy_to_idx += 1;
  }

  num_pairs = copy_to_idx;
  *num_pairs_ref = num_pairs;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


----------------------------
***/


void BrotliCompareAndPushToQueueDistance(const HistogramDistance *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramDistance combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramDistance(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostDistance(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


/*** DEPENDENCIES:
inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
inline static double ClusterCostDiff(size_t size_a, size_t size_b)
{
  size_t size_c = size_a + size_b;
  return ((((double) size_a) * FastLog2(size_a)) + (((double) size_b) * FastLog2(size_b))) - (((double) size_c) * FastLog2(size_c));
}


----------------------------
inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


----------------------------
double BrotliPopulationCostDistance(const HistogramDistance *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeDistance();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostDistance_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostDistance_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
inline static void HistogramAddHistogramDistance(HistogramDistance *self, const HistogramDistance *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 544; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
***/


// hint:  ['num_clusters_ref is a mutable refrence to size_t', 'cost_diff_threshold_ref is a mutable refrence to double', 'min_cluster_size_ref is a mutable refrence to size_t', 'num_pairs_ref is a mutable refrence to size_t']
void helper_BrotliHistogramCombineDistance_1(size_t * const num_clusters_ref, double * const cost_diff_threshold_ref, size_t * const min_cluster_size_ref, size_t * const num_pairs_ref, HistogramDistance * const out, uint32_t * const cluster_size, uint32_t * const symbols, uint32_t * const clusters, HistogramPair * const pairs, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  size_t num_clusters = *num_clusters_ref;
  double cost_diff_threshold = *cost_diff_threshold_ref;
  size_t min_cluster_size = *min_cluster_size_ref;
  size_t num_pairs = *num_pairs_ref;
  uint32_t best_idx1;
  uint32_t best_idx2;
  size_t i;
  if (pairs[0].cost_diff >= cost_diff_threshold)
  {
    cost_diff_threshold = 1e99;
    min_cluster_size = max_clusters;
    continue;
  }
  best_idx1 = pairs[0].idx1;
  best_idx2 = pairs[0].idx2;
  HistogramAddHistogramDistance(&out[best_idx1], &out[best_idx2]);
  out[best_idx1].bit_cost_ = pairs[0].cost_combo;
  cluster_size[best_idx1] += cluster_size[best_idx2];
  for (i = 0; i < symbols_size; i += 1)
  {
    if (symbols[i] == best_idx2)
    {
      symbols[i] = best_idx1;
    }
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    if (clusters[i] == best_idx2)
    {
      memmove(&clusters[i], &clusters[i + 1], ((num_clusters - i) - 1) * (sizeof(clusters[0])));
      break;
    }
  }

  num_clusters -= 1;
  {
    helper_helper_BrotliHistogramCombineDistance_1_1(&num_pairs, &i, pairs, best_idx1, best_idx2);
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    BrotliCompareAndPushToQueueDistance(out, cluster_size, best_idx1, clusters[i], max_num_pairs, &pairs[0], &num_pairs);
  }

  *num_clusters_ref = num_clusters;
  *cost_diff_threshold_ref = cost_diff_threshold;
  *min_cluster_size_ref = min_cluster_size;
  *num_pairs_ref = num_pairs;
}


/*** DEPENDENCIES:
void BrotliCompareAndPushToQueueDistance(const HistogramDistance *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramDistance combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramDistance(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostDistance(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
inline static void HistogramAddHistogramDistance(HistogramDistance *self, const HistogramDistance *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 544; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
void helper_helper_BrotliHistogramCombineDistance_1_1(size_t * const num_pairs_ref, size_t * const i_ref, HistogramPair * const pairs, uint32_t best_idx1, uint32_t best_idx2)
{
  size_t num_pairs = *num_pairs_ref;
  size_t i = *i_ref;
  size_t copy_to_idx = 0;
  for (i = 0; i < num_pairs; i += 1)
  {
    HistogramPair *p = &pairs[i];
    if ((((p->idx1 == best_idx1) || (p->idx2 == best_idx1)) || (p->idx1 == best_idx2)) || (p->idx2 == best_idx2))
    {
      continue;
    }
    if (HistogramPairIsLess(&pairs[0], p))
    {
      HistogramPair front = pairs[0];
      pairs[0] = *p;
      pairs[copy_to_idx] = front;
    }
    else
    {
      pairs[copy_to_idx] = *p;
    }
    copy_to_idx += 1;
  }

  num_pairs = copy_to_idx;
  *num_pairs_ref = num_pairs;
  *i_ref = i;
}


----------------------------
***/


size_t BrotliHistogramCombineDistance(HistogramDistance *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueDistance(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineDistance_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


/*** DEPENDENCIES:
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
void BrotliCompareAndPushToQueueDistance(const HistogramDistance *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramDistance combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramDistance(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostDistance(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
void helper_BrotliHistogramCombineDistance_1(size_t * const num_clusters_ref, double * const cost_diff_threshold_ref, size_t * const min_cluster_size_ref, size_t * const num_pairs_ref, HistogramDistance * const out, uint32_t * const cluster_size, uint32_t * const symbols, uint32_t * const clusters, HistogramPair * const pairs, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  size_t num_clusters = *num_clusters_ref;
  double cost_diff_threshold = *cost_diff_threshold_ref;
  size_t min_cluster_size = *min_cluster_size_ref;
  size_t num_pairs = *num_pairs_ref;
  uint32_t best_idx1;
  uint32_t best_idx2;
  size_t i;
  if (pairs[0].cost_diff >= cost_diff_threshold)
  {
    cost_diff_threshold = 1e99;
    min_cluster_size = max_clusters;
    continue;
  }
  best_idx1 = pairs[0].idx1;
  best_idx2 = pairs[0].idx2;
  HistogramAddHistogramDistance(&out[best_idx1], &out[best_idx2]);
  out[best_idx1].bit_cost_ = pairs[0].cost_combo;
  cluster_size[best_idx1] += cluster_size[best_idx2];
  for (i = 0; i < symbols_size; i += 1)
  {
    if (symbols[i] == best_idx2)
    {
      symbols[i] = best_idx1;
    }
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    if (clusters[i] == best_idx2)
    {
      memmove(&clusters[i], &clusters[i + 1], ((num_clusters - i) - 1) * (sizeof(clusters[0])));
      break;
    }
  }

  num_clusters -= 1;
  {
    helper_helper_BrotliHistogramCombineDistance_1_1(&num_pairs, &i, pairs, best_idx1, best_idx2);
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    BrotliCompareAndPushToQueueDistance(out, cluster_size, best_idx1, clusters[i], max_num_pairs, &pairs[0], &num_pairs);
  }

  *num_clusters_ref = num_clusters;
  *cost_diff_threshold_ref = cost_diff_threshold;
  *min_cluster_size_ref = min_cluster_size;
  *num_pairs_ref = num_pairs;
}


----------------------------
***/


// hint:  ['num_clusters_ref is a mutable refrence to size_t', 'pairs_capacity_ref is a mutable refrence to size_t', 'pairs_idx_ref is a mutable refrence to unsigned int']
void helper_BrotliClusterHistogramsDistance_1(size_t * const num_clusters_ref, size_t * const pairs_capacity_ref, unsigned int * const pairs_idx_ref, MemoryManager * const m, const size_t in_size, size_t max_histograms, HistogramDistance * const out, uint32_t * const histogram_symbols, uint32_t * const cluster_size, uint32_t * const clusters, HistogramPair * const pairs)
{
  size_t num_clusters = *num_clusters_ref;
  size_t pairs_capacity = *pairs_capacity_ref;
  unsigned int pairs_idx = *pairs_idx_ref;
  size_t max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  {
    if (pairs_capacity < (max_num_pairs + 1))
    {
      size_t _new_size = (pairs_capacity == 0) ? (max_num_pairs + 1) : (pairs_capacity);
      HistogramPair *new_array;
      unsigned int new_array_idx = 0;
      while (_new_size < (max_num_pairs + 1))
        _new_size *= 2;

      new_array_idx = (_new_size > 0) ? ((HistogramPair *) BrotliAllocate(m, _new_size * (sizeof(HistogramPair)))) : (0);
      if (((!(!(!0))) && (!(!(!0)))) && (pairs_capacity != 0))
      {
        memcpy(new_array, pairs, pairs_capacity * (sizeof(HistogramPair)));
      }
      {
        BrotliFree(m, pairs);
        pairs_idx = 0;
      }
      ;
      pairs_idx = &new_array[new_array_idx];
      pairs_capacity = _new_size;
    }
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_clusters = BrotliHistogramCombineDistance(out, cluster_size, histogram_symbols, clusters, pairs, num_clusters, in_size, max_histograms, max_num_pairs);
  *num_clusters_ref = num_clusters;
  *pairs_capacity_ref = pairs_capacity;
  *pairs_idx_ref = pairs_idx;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
size_t BrotliHistogramCombineDistance(HistogramDistance *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueDistance(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineDistance_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


size_t BrotliHistogramReindexDistance(MemoryManager *m, HistogramDistance *out, uint32_t *symbols, size_t length)
{
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index = (length > 0) ? ((uint32_t *) BrotliAllocate(m, length * (sizeof(uint32_t)))) : (0);
  unsigned int new_index_idx = 0;
  uint32_t next_index;
  HistogramDistance *tmp;
  unsigned int tmp_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  for (i = 0; i < length; i += 1)
  {
    new_index[i + new_index_idx] = kInvalidIndex;
  }

  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == kInvalidIndex)
    {
      new_index[symbols[i] + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  tmp_idx = (next_index > 0) ? ((HistogramDistance *) BrotliAllocate(m, next_index * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == next_index)
    {
      tmp[next_index + tmp_idx] = out[symbols[i]];
      next_index += 1;
    }
    symbols[i] = new_index[symbols[i] + new_index_idx];
  }

  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  for (i = 0; i < next_index; i += 1)
  {
    out[i] = tmp[i + tmp_idx];
  }

  {
    BrotliFree(m, tmp);
    tmp_idx = 0;
  }
  ;
  return next_index;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


double BrotliHistogramBitCostDistanceDistance(const HistogramDistance *histogram, const HistogramDistance *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramDistance tmp = *histogram;
    HistogramAddHistogramDistance(&tmp, candidate);
    return BrotliPopulationCostDistance(&tmp) - candidate->bit_cost_;
  }
}


/*** DEPENDENCIES:
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
double BrotliPopulationCostDistance(const HistogramDistance *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeDistance();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostDistance_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostDistance_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
inline static void HistogramAddHistogramDistance(HistogramDistance *self, const HistogramDistance *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 544; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
***/


void BrotliHistogramRemapDistance(const HistogramDistance *in, size_t in_size, const uint32_t *clusters, size_t num_clusters, HistogramDistance *out, uint32_t *symbols)
{
  size_t i;
  for (i = 0; i < in_size; i += 1)
  {
    uint32_t best_out = (i == 0) ? (symbols[0]) : (symbols[i - 1]);
    double best_bits = BrotliHistogramBitCostDistanceDistance(&in[i], &out[best_out]);
    size_t j;
    for (j = 0; j < num_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceDistance(&in[i], &out[clusters[j]]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j];
      }
    }

    symbols[i] = best_out;
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    HistogramClearDistance(&out[clusters[i]]);
  }

  for (i = 0; i < in_size; i += 1)
  {
    HistogramAddHistogramDistance(&out[symbols[i]], &in[i]);
  }

}


/*** DEPENDENCIES:
inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
double BrotliHistogramBitCostDistanceDistance(const HistogramDistance *histogram, const HistogramDistance *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramDistance tmp = *histogram;
    HistogramAddHistogramDistance(&tmp, candidate);
    return BrotliPopulationCostDistance(&tmp) - candidate->bit_cost_;
  }
}


----------------------------
inline static void HistogramAddHistogramDistance(HistogramDistance *self, const HistogramDistance *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 544; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
***/


void BrotliClusterHistogramsDistance(MemoryManager *m, const HistogramDistance *in, const size_t in_size, size_t max_histograms, HistogramDistance *out, size_t *out_size, uint32_t *histogram_symbols)
{
  uint32_t *cluster_size = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  uint32_t *clusters = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int clusters_idx = 0;
  size_t num_clusters = 0;
  const size_t max_input_histograms = 64;
  size_t pairs_capacity = (max_input_histograms * max_input_histograms) / 2;
  HistogramPair *pairs = ((pairs_capacity + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (pairs_capacity + 1) * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t i;
  if ((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < in_size; i += 1)
  {
    cluster_size[i + cluster_size_idx] = 1;
  }

  for (i = 0; i < in_size; i += 1)
  {
    out[i] = in[i];
    out[i].bit_cost_ = BrotliPopulationCostDistance(&in[i]);
    histogram_symbols[i] = (uint32_t) i;
  }

  for (i = 0; i < in_size; i += max_input_histograms)
  {
    size_t num_to_combine = brotli_min_size_t(in_size - i, max_input_histograms);
    size_t num_new_clusters;
    size_t j;
    for (j = 0; j < num_to_combine; j += 1)
    {
      clusters[(num_clusters + j) + clusters_idx] = (uint32_t) (i + j);
    }

    num_new_clusters = BrotliHistogramCombineDistance(out, cluster_size, &histogram_symbols[i], &clusters[num_clusters + clusters_idx], pairs, num_to_combine, num_to_combine, max_histograms, pairs_capacity);
    num_clusters += num_new_clusters;
  }

  {
    helper_BrotliClusterHistogramsDistance_1(&num_clusters, &pairs_capacity, &pairs_idx, m, in_size, max_histograms, out, histogram_symbols, cluster_size, clusters, pairs);
  }
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  BrotliHistogramRemapDistance(in, in_size, clusters, num_clusters, out, histogram_symbols);
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  *out_size = BrotliHistogramReindexDistance(m, out, histogram_symbols, in_size);
  if (!(!0))
  {
    return;
  }
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void helper_BrotliClusterHistogramsDistance_1(size_t * const num_clusters_ref, size_t * const pairs_capacity_ref, unsigned int * const pairs_idx_ref, MemoryManager * const m, const size_t in_size, size_t max_histograms, HistogramDistance * const out, uint32_t * const histogram_symbols, uint32_t * const cluster_size, uint32_t * const clusters, HistogramPair * const pairs)
{
  size_t num_clusters = *num_clusters_ref;
  size_t pairs_capacity = *pairs_capacity_ref;
  unsigned int pairs_idx = *pairs_idx_ref;
  size_t max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  {
    if (pairs_capacity < (max_num_pairs + 1))
    {
      size_t _new_size = (pairs_capacity == 0) ? (max_num_pairs + 1) : (pairs_capacity);
      HistogramPair *new_array;
      unsigned int new_array_idx = 0;
      while (_new_size < (max_num_pairs + 1))
        _new_size *= 2;

      new_array_idx = (_new_size > 0) ? ((HistogramPair *) BrotliAllocate(m, _new_size * (sizeof(HistogramPair)))) : (0);
      if (((!(!(!0))) && (!(!(!0)))) && (pairs_capacity != 0))
      {
        memcpy(new_array, pairs, pairs_capacity * (sizeof(HistogramPair)));
      }
      {
        BrotliFree(m, pairs);
        pairs_idx = 0;
      }
      ;
      pairs_idx = &new_array[new_array_idx];
      pairs_capacity = _new_size;
    }
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_clusters = BrotliHistogramCombineDistance(out, cluster_size, histogram_symbols, clusters, pairs, num_clusters, in_size, max_histograms, max_num_pairs);
  *num_clusters_ref = num_clusters;
  *pairs_capacity_ref = pairs_capacity;
  *pairs_idx_ref = pairs_idx;
}


----------------------------
size_t BrotliHistogramReindexDistance(MemoryManager *m, HistogramDistance *out, uint32_t *symbols, size_t length)
{
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index = (length > 0) ? ((uint32_t *) BrotliAllocate(m, length * (sizeof(uint32_t)))) : (0);
  unsigned int new_index_idx = 0;
  uint32_t next_index;
  HistogramDistance *tmp;
  unsigned int tmp_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  for (i = 0; i < length; i += 1)
  {
    new_index[i + new_index_idx] = kInvalidIndex;
  }

  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == kInvalidIndex)
    {
      new_index[symbols[i] + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  tmp_idx = (next_index > 0) ? ((HistogramDistance *) BrotliAllocate(m, next_index * (sizeof(HistogramDistance)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == next_index)
    {
      tmp[next_index + tmp_idx] = out[symbols[i]];
      next_index += 1;
    }
    symbols[i] = new_index[symbols[i] + new_index_idx];
  }

  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  for (i = 0; i < next_index; i += 1)
  {
    out[i] = tmp[i + tmp_idx];
  }

  {
    BrotliFree(m, tmp);
    tmp_idx = 0;
  }
  ;
  return next_index;
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
double BrotliPopulationCostDistance(const HistogramDistance *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeDistance();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostDistance_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostDistance_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
size_t BrotliHistogramCombineDistance(HistogramDistance *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueDistance(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineDistance_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
void BrotliHistogramRemapDistance(const HistogramDistance *in, size_t in_size, const uint32_t *clusters, size_t num_clusters, HistogramDistance *out, uint32_t *symbols)
{
  size_t i;
  for (i = 0; i < in_size; i += 1)
  {
    uint32_t best_out = (i == 0) ? (symbols[0]) : (symbols[i - 1]);
    double best_bits = BrotliHistogramBitCostDistanceDistance(&in[i], &out[best_out]);
    size_t j;
    for (j = 0; j < num_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceDistance(&in[i], &out[clusters[j]]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j];
      }
    }

    symbols[i] = best_out;
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    HistogramClearDistance(&out[clusters[i]]);
  }

  for (i = 0; i < in_size; i += 1)
  {
    HistogramAddHistogramDistance(&out[symbols[i]], &in[i]);
  }

}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliCompareAndPushToQueueCommand(const HistogramCommand *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramCommand combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramCommand(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostCommand(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


----------------------------
inline static double ClusterCostDiff(size_t size_a, size_t size_b)
{
  size_t size_c = size_a + size_b;
  return ((((double) size_a) * FastLog2(size_a)) + (((double) size_b) * FastLog2(size_b))) - (((double) size_c) * FastLog2(size_c));
}


----------------------------
inline static void HistogramAddHistogramCommand(HistogramCommand *self, const HistogramCommand *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 704; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
double BrotliPopulationCostCommand(const HistogramCommand *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeCommand();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostCommand_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostCommand_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
***/


// hint:  ['num_clusters_ref is a mutable refrence to size_t', 'cost_diff_threshold_ref is a mutable refrence to double', 'min_cluster_size_ref is a mutable refrence to size_t', 'num_pairs_ref is a mutable refrence to size_t']
void helper_BrotliHistogramCombineCommand_1(size_t * const num_clusters_ref, double * const cost_diff_threshold_ref, size_t * const min_cluster_size_ref, size_t * const num_pairs_ref, HistogramCommand * const out, uint32_t * const cluster_size, uint32_t * const symbols, uint32_t * const clusters, HistogramPair * const pairs, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  size_t num_clusters = *num_clusters_ref;
  double cost_diff_threshold = *cost_diff_threshold_ref;
  size_t min_cluster_size = *min_cluster_size_ref;
  size_t num_pairs = *num_pairs_ref;
  uint32_t best_idx1;
  uint32_t best_idx2;
  size_t i;
  if (pairs[0].cost_diff >= cost_diff_threshold)
  {
    cost_diff_threshold = 1e99;
    min_cluster_size = max_clusters;
    continue;
  }
  best_idx1 = pairs[0].idx1;
  best_idx2 = pairs[0].idx2;
  HistogramAddHistogramCommand(&out[best_idx1], &out[best_idx2]);
  out[best_idx1].bit_cost_ = pairs[0].cost_combo;
  cluster_size[best_idx1] += cluster_size[best_idx2];
  for (i = 0; i < symbols_size; i += 1)
  {
    if (symbols[i] == best_idx2)
    {
      symbols[i] = best_idx1;
    }
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    if (clusters[i] == best_idx2)
    {
      memmove(&clusters[i], &clusters[i + 1], ((num_clusters - i) - 1) * (sizeof(clusters[0])));
      break;
    }
  }

  num_clusters -= 1;
  {
    helper_helper_BrotliHistogramCombineCommand_1_1(&num_pairs, &i, pairs, best_idx1, best_idx2);
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    BrotliCompareAndPushToQueueCommand(out, cluster_size, best_idx1, clusters[i], max_num_pairs, &pairs[0], &num_pairs);
  }

  *num_clusters_ref = num_clusters;
  *cost_diff_threshold_ref = cost_diff_threshold;
  *min_cluster_size_ref = min_cluster_size;
  *num_pairs_ref = num_pairs;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
void helper_helper_BrotliHistogramCombineCommand_1_1(size_t * const num_pairs_ref, size_t * const i_ref, HistogramPair * const pairs, uint32_t best_idx1, uint32_t best_idx2)
{
  size_t num_pairs = *num_pairs_ref;
  size_t i = *i_ref;
  size_t copy_to_idx = 0;
  for (i = 0; i < num_pairs; i += 1)
  {
    HistogramPair *p = &pairs[i];
    if ((((p->idx1 == best_idx1) || (p->idx2 == best_idx1)) || (p->idx1 == best_idx2)) || (p->idx2 == best_idx2))
    {
      continue;
    }
    if (HistogramPairIsLess(&pairs[0], p))
    {
      HistogramPair front = pairs[0];
      pairs[0] = *p;
      pairs[copy_to_idx] = front;
    }
    else
    {
      pairs[copy_to_idx] = *p;
    }
    copy_to_idx += 1;
  }

  num_pairs = copy_to_idx;
  *num_pairs_ref = num_pairs;
  *i_ref = i;
}


----------------------------
inline static void HistogramAddHistogramCommand(HistogramCommand *self, const HistogramCommand *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 704; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
void BrotliCompareAndPushToQueueCommand(const HistogramCommand *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramCommand combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramCommand(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostCommand(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


----------------------------
***/


size_t BrotliHistogramCombineCommand(HistogramCommand *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueCommand(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineCommand_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


/*** DEPENDENCIES:
void helper_BrotliHistogramCombineCommand_1(size_t * const num_clusters_ref, double * const cost_diff_threshold_ref, size_t * const min_cluster_size_ref, size_t * const num_pairs_ref, HistogramCommand * const out, uint32_t * const cluster_size, uint32_t * const symbols, uint32_t * const clusters, HistogramPair * const pairs, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  size_t num_clusters = *num_clusters_ref;
  double cost_diff_threshold = *cost_diff_threshold_ref;
  size_t min_cluster_size = *min_cluster_size_ref;
  size_t num_pairs = *num_pairs_ref;
  uint32_t best_idx1;
  uint32_t best_idx2;
  size_t i;
  if (pairs[0].cost_diff >= cost_diff_threshold)
  {
    cost_diff_threshold = 1e99;
    min_cluster_size = max_clusters;
    continue;
  }
  best_idx1 = pairs[0].idx1;
  best_idx2 = pairs[0].idx2;
  HistogramAddHistogramCommand(&out[best_idx1], &out[best_idx2]);
  out[best_idx1].bit_cost_ = pairs[0].cost_combo;
  cluster_size[best_idx1] += cluster_size[best_idx2];
  for (i = 0; i < symbols_size; i += 1)
  {
    if (symbols[i] == best_idx2)
    {
      symbols[i] = best_idx1;
    }
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    if (clusters[i] == best_idx2)
    {
      memmove(&clusters[i], &clusters[i + 1], ((num_clusters - i) - 1) * (sizeof(clusters[0])));
      break;
    }
  }

  num_clusters -= 1;
  {
    helper_helper_BrotliHistogramCombineCommand_1_1(&num_pairs, &i, pairs, best_idx1, best_idx2);
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    BrotliCompareAndPushToQueueCommand(out, cluster_size, best_idx1, clusters[i], max_num_pairs, &pairs[0], &num_pairs);
  }

  *num_clusters_ref = num_clusters;
  *cost_diff_threshold_ref = cost_diff_threshold;
  *min_cluster_size_ref = min_cluster_size;
  *num_pairs_ref = num_pairs;
}


----------------------------
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
void BrotliCompareAndPushToQueueCommand(const HistogramCommand *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramCommand combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramCommand(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostCommand(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


----------------------------
***/


double BrotliHistogramBitCostDistanceCommand(const HistogramCommand *histogram, const HistogramCommand *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramCommand tmp = *histogram;
    HistogramAddHistogramCommand(&tmp, candidate);
    return BrotliPopulationCostCommand(&tmp) - candidate->bit_cost_;
  }
}


/*** DEPENDENCIES:
inline static void HistogramAddHistogramCommand(HistogramCommand *self, const HistogramCommand *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 704; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
double BrotliPopulationCostCommand(const HistogramCommand *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeCommand();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostCommand_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostCommand_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
***/


void BrotliCompareAndPushToQueueLiteral(const HistogramLiteral *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramLiteral combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramLiteral(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostLiteral(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


/*** DEPENDENCIES:
inline static void HistogramAddHistogramLiteral(HistogramLiteral *self, const HistogramLiteral *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 256; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
inline static int HistogramPairIsLess(const HistogramPair *p1, const HistogramPair *p2)
{
  if (p1->cost_diff != p2->cost_diff)
  {
    return (!(!(p1->cost_diff > p2->cost_diff))) ? (1) : (0);
  }
  return (!(!((p1->idx2 - p1->idx1) > (p2->idx2 - p2->idx1)))) ? (1) : (0);
}


----------------------------
inline static double ClusterCostDiff(size_t size_a, size_t size_b)
{
  size_t size_c = size_a + size_b;
  return ((((double) size_a) * FastLog2(size_a)) + (((double) size_b) * FastLog2(size_b))) - (((double) size_c) * FastLog2(size_c));
}


----------------------------
double BrotliPopulationCostLiteral(const HistogramLiteral *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeLiteral();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostLiteral_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostLiteral_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


// hint:  ['num_clusters_ref is a mutable refrence to size_t', 'cost_diff_threshold_ref is a mutable refrence to double', 'min_cluster_size_ref is a mutable refrence to size_t', 'num_pairs_ref is a mutable refrence to size_t']
void helper_BrotliHistogramCombineLiteral_1(size_t * const num_clusters_ref, double * const cost_diff_threshold_ref, size_t * const min_cluster_size_ref, size_t * const num_pairs_ref, HistogramLiteral * const out, uint32_t * const cluster_size, uint32_t * const symbols, uint32_t * const clusters, HistogramPair * const pairs, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  size_t num_clusters = *num_clusters_ref;
  double cost_diff_threshold = *cost_diff_threshold_ref;
  size_t min_cluster_size = *min_cluster_size_ref;
  size_t num_pairs = *num_pairs_ref;
  uint32_t best_idx1;
  uint32_t best_idx2;
  size_t i;
  if (pairs[0].cost_diff >= cost_diff_threshold)
  {
    cost_diff_threshold = 1e99;
    min_cluster_size = max_clusters;
    continue;
  }
  best_idx1 = pairs[0].idx1;
  best_idx2 = pairs[0].idx2;
  HistogramAddHistogramLiteral(&out[best_idx1], &out[best_idx2]);
  out[best_idx1].bit_cost_ = pairs[0].cost_combo;
  cluster_size[best_idx1] += cluster_size[best_idx2];
  for (i = 0; i < symbols_size; i += 1)
  {
    if (symbols[i] == best_idx2)
    {
      symbols[i] = best_idx1;
    }
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    if (clusters[i] == best_idx2)
    {
      memmove(&clusters[i], &clusters[i + 1], ((num_clusters - i) - 1) * (sizeof(clusters[0])));
      break;
    }
  }

  num_clusters -= 1;
  {
    helper_helper_BrotliHistogramCombineLiteral_1_1(&num_pairs, &i, pairs, best_idx1, best_idx2);
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    BrotliCompareAndPushToQueueLiteral(out, cluster_size, best_idx1, clusters[i], max_num_pairs, &pairs[0], &num_pairs);
  }

  *num_clusters_ref = num_clusters;
  *cost_diff_threshold_ref = cost_diff_threshold;
  *min_cluster_size_ref = min_cluster_size;
  *num_pairs_ref = num_pairs;
}


/*** DEPENDENCIES:
inline static void HistogramAddHistogramLiteral(HistogramLiteral *self, const HistogramLiteral *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 256; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
void BrotliCompareAndPushToQueueLiteral(const HistogramLiteral *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramLiteral combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramLiteral(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostLiteral(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void helper_helper_BrotliHistogramCombineLiteral_1_1(size_t * const num_pairs_ref, size_t * const i_ref, HistogramPair * const pairs, uint32_t best_idx1, uint32_t best_idx2)
{
  size_t num_pairs = *num_pairs_ref;
  size_t i = *i_ref;
  size_t copy_to_idx = 0;
  for (i = 0; i < num_pairs; i += 1)
  {
    HistogramPair *p = &pairs[i];
    if ((((p->idx1 == best_idx1) || (p->idx2 == best_idx1)) || (p->idx1 == best_idx2)) || (p->idx2 == best_idx2))
    {
      continue;
    }
    if (HistogramPairIsLess(&pairs[0], p))
    {
      HistogramPair front = pairs[0];
      pairs[0] = *p;
      pairs[copy_to_idx] = front;
    }
    else
    {
      pairs[copy_to_idx] = *p;
    }
    copy_to_idx += 1;
  }

  num_pairs = copy_to_idx;
  *num_pairs_ref = num_pairs;
  *i_ref = i;
}


----------------------------
***/


size_t BrotliHistogramCombineLiteral(HistogramLiteral *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueLiteral(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineLiteral_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


/*** DEPENDENCIES:
void helper_BrotliHistogramCombineLiteral_1(size_t * const num_clusters_ref, double * const cost_diff_threshold_ref, size_t * const min_cluster_size_ref, size_t * const num_pairs_ref, HistogramLiteral * const out, uint32_t * const cluster_size, uint32_t * const symbols, uint32_t * const clusters, HistogramPair * const pairs, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  size_t num_clusters = *num_clusters_ref;
  double cost_diff_threshold = *cost_diff_threshold_ref;
  size_t min_cluster_size = *min_cluster_size_ref;
  size_t num_pairs = *num_pairs_ref;
  uint32_t best_idx1;
  uint32_t best_idx2;
  size_t i;
  if (pairs[0].cost_diff >= cost_diff_threshold)
  {
    cost_diff_threshold = 1e99;
    min_cluster_size = max_clusters;
    continue;
  }
  best_idx1 = pairs[0].idx1;
  best_idx2 = pairs[0].idx2;
  HistogramAddHistogramLiteral(&out[best_idx1], &out[best_idx2]);
  out[best_idx1].bit_cost_ = pairs[0].cost_combo;
  cluster_size[best_idx1] += cluster_size[best_idx2];
  for (i = 0; i < symbols_size; i += 1)
  {
    if (symbols[i] == best_idx2)
    {
      symbols[i] = best_idx1;
    }
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    if (clusters[i] == best_idx2)
    {
      memmove(&clusters[i], &clusters[i + 1], ((num_clusters - i) - 1) * (sizeof(clusters[0])));
      break;
    }
  }

  num_clusters -= 1;
  {
    helper_helper_BrotliHistogramCombineLiteral_1_1(&num_pairs, &i, pairs, best_idx1, best_idx2);
  }
  for (i = 0; i < num_clusters; i += 1)
  {
    BrotliCompareAndPushToQueueLiteral(out, cluster_size, best_idx1, clusters[i], max_num_pairs, &pairs[0], &num_pairs);
  }

  *num_clusters_ref = num_clusters;
  *cost_diff_threshold_ref = cost_diff_threshold;
  *min_cluster_size_ref = min_cluster_size;
  *num_pairs_ref = num_pairs;
}


----------------------------
void BrotliCompareAndPushToQueueLiteral(const HistogramLiteral *out, const uint32_t *cluster_size, uint32_t idx1, uint32_t idx2, size_t max_num_pairs, HistogramPair *pairs, size_t *num_pairs)
{
  int is_good_pair = 0;
  HistogramPair p;
  p.idx1 = (p.idx2 = 0);
  p.cost_diff = (p.cost_combo = 0);
  if (idx1 == idx2)
  {
    return;
  }
  if (idx2 < idx1)
  {
    uint32_t t = idx2;
    idx2 = idx1;
    idx1 = t;
  }
  p.idx1 = idx1;
  p.idx2 = idx2;
  p.cost_diff = 0.5 * ClusterCostDiff(cluster_size[idx1], cluster_size[idx2]);
  p.cost_diff -= out[idx1].bit_cost_;
  p.cost_diff -= out[idx2].bit_cost_;
  if (out[idx1].total_count_ == 0)
  {
    p.cost_combo = out[idx2].bit_cost_;
    is_good_pair = 1;
  }
  else
    if (out[idx2].total_count_ == 0)
  {
    p.cost_combo = out[idx1].bit_cost_;
    is_good_pair = 1;
  }
  else
  {
    double threshold = ((*num_pairs) == 0) ? (1e99) : (brotli_max_double(0.0, pairs[0].cost_diff));
    HistogramLiteral combo = out[idx1];
    double cost_combo;
    HistogramAddHistogramLiteral(&combo, &out[idx2]);
    cost_combo = BrotliPopulationCostLiteral(&combo);
    if (cost_combo < (threshold - p.cost_diff))
    {
      p.cost_combo = cost_combo;
      is_good_pair = 1;
    }
  }
  if (is_good_pair)
  {
    p.cost_diff += p.cost_combo;
    if (((*num_pairs) > 0) && HistogramPairIsLess(&pairs[0], &p))
    {
      if ((*num_pairs) < max_num_pairs)
      {
        pairs[*num_pairs] = pairs[0];
        *num_pairs += 1;
      }
      pairs[0] = p;
    }
    else
      if ((*num_pairs) < max_num_pairs)
    {
      pairs[*num_pairs] = p;
      *num_pairs += 1;
    }
  }
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


double BrotliHistogramBitCostDistanceLiteral(const HistogramLiteral *histogram, const HistogramLiteral *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramLiteral tmp = *histogram;
    HistogramAddHistogramLiteral(&tmp, candidate);
    return BrotliPopulationCostLiteral(&tmp) - candidate->bit_cost_;
  }
}


/*** DEPENDENCIES:
double BrotliPopulationCostLiteral(const HistogramLiteral *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeLiteral();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostLiteral_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostLiteral_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static void HistogramAddHistogramLiteral(HistogramLiteral *self, const HistogramLiteral *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 256; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
***/


size_t BrotliHistogramReindexLiteral(MemoryManager *m, HistogramLiteral *out, uint32_t *symbols, size_t length)
{
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index = (length > 0) ? ((uint32_t *) BrotliAllocate(m, length * (sizeof(uint32_t)))) : (0);
  unsigned int new_index_idx = 0;
  uint32_t next_index;
  HistogramLiteral *tmp;
  unsigned int tmp_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  for (i = 0; i < length; i += 1)
  {
    new_index[i + new_index_idx] = kInvalidIndex;
  }

  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == kInvalidIndex)
    {
      new_index[symbols[i] + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  tmp_idx = (next_index > 0) ? ((HistogramLiteral *) BrotliAllocate(m, next_index * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == next_index)
    {
      tmp[next_index + tmp_idx] = out[symbols[i]];
      next_index += 1;
    }
    symbols[i] = new_index[symbols[i] + new_index_idx];
  }

  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  for (i = 0; i < next_index; i += 1)
  {
    out[i] = tmp[i + tmp_idx];
  }

  {
    BrotliFree(m, tmp);
    tmp_idx = 0;
  }
  ;
  return next_index;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


void BrotliHistogramRemapLiteral(const HistogramLiteral *in, size_t in_size, const uint32_t *clusters, size_t num_clusters, HistogramLiteral *out, uint32_t *symbols)
{
  size_t i;
  for (i = 0; i < in_size; i += 1)
  {
    uint32_t best_out = (i == 0) ? (symbols[0]) : (symbols[i - 1]);
    double best_bits = BrotliHistogramBitCostDistanceLiteral(&in[i], &out[best_out]);
    size_t j;
    for (j = 0; j < num_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceLiteral(&in[i], &out[clusters[j]]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j];
      }
    }

    symbols[i] = best_out;
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    HistogramClearLiteral(&out[clusters[i]]);
  }

  for (i = 0; i < in_size; i += 1)
  {
    HistogramAddHistogramLiteral(&out[symbols[i]], &in[i]);
  }

}


/*** DEPENDENCIES:
inline static void HistogramAddHistogramLiteral(HistogramLiteral *self, const HistogramLiteral *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 256; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
double BrotliHistogramBitCostDistanceLiteral(const HistogramLiteral *histogram, const HistogramLiteral *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramLiteral tmp = *histogram;
    HistogramAddHistogramLiteral(&tmp, candidate);
    return BrotliPopulationCostLiteral(&tmp) - candidate->bit_cost_;
  }
}


----------------------------
***/


// hint:  ['num_clusters_ref is a mutable refrence to size_t', 'pairs_capacity_ref is a mutable refrence to size_t', 'pairs_idx_ref is a mutable refrence to unsigned int']
void helper_BrotliClusterHistogramsLiteral_1(size_t * const num_clusters_ref, size_t * const pairs_capacity_ref, unsigned int * const pairs_idx_ref, MemoryManager * const m, const size_t in_size, size_t max_histograms, HistogramLiteral * const out, uint32_t * const histogram_symbols, uint32_t * const cluster_size, uint32_t * const clusters, HistogramPair * const pairs)
{
  size_t num_clusters = *num_clusters_ref;
  size_t pairs_capacity = *pairs_capacity_ref;
  unsigned int pairs_idx = *pairs_idx_ref;
  size_t max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  {
    if (pairs_capacity < (max_num_pairs + 1))
    {
      size_t _new_size = (pairs_capacity == 0) ? (max_num_pairs + 1) : (pairs_capacity);
      HistogramPair *new_array;
      unsigned int new_array_idx = 0;
      while (_new_size < (max_num_pairs + 1))
        _new_size *= 2;

      new_array_idx = (_new_size > 0) ? ((HistogramPair *) BrotliAllocate(m, _new_size * (sizeof(HistogramPair)))) : (0);
      if (((!(!(!0))) && (!(!(!0)))) && (pairs_capacity != 0))
      {
        memcpy(new_array, pairs, pairs_capacity * (sizeof(HistogramPair)));
      }
      {
        BrotliFree(m, pairs);
        pairs_idx = 0;
      }
      ;
      pairs_idx = &new_array[new_array_idx];
      pairs_capacity = _new_size;
    }
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_clusters = BrotliHistogramCombineLiteral(out, cluster_size, histogram_symbols, clusters, pairs, num_clusters, in_size, max_histograms, max_num_pairs);
  *num_clusters_ref = num_clusters;
  *pairs_capacity_ref = pairs_capacity;
  *pairs_idx_ref = pairs_idx;
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
size_t BrotliHistogramCombineLiteral(HistogramLiteral *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueLiteral(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineLiteral_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliClusterHistogramsLiteral(MemoryManager *m, const HistogramLiteral *in, const size_t in_size, size_t max_histograms, HistogramLiteral *out, size_t *out_size, uint32_t *histogram_symbols)
{
  uint32_t *cluster_size = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  uint32_t *clusters = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int clusters_idx = 0;
  size_t num_clusters = 0;
  const size_t max_input_histograms = 64;
  size_t pairs_capacity = (max_input_histograms * max_input_histograms) / 2;
  HistogramPair *pairs = ((pairs_capacity + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (pairs_capacity + 1) * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t i;
  if ((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < in_size; i += 1)
  {
    cluster_size[i + cluster_size_idx] = 1;
  }

  for (i = 0; i < in_size; i += 1)
  {
    out[i] = in[i];
    out[i].bit_cost_ = BrotliPopulationCostLiteral(&in[i]);
    histogram_symbols[i] = (uint32_t) i;
  }

  for (i = 0; i < in_size; i += max_input_histograms)
  {
    size_t num_to_combine = brotli_min_size_t(in_size - i, max_input_histograms);
    size_t num_new_clusters;
    size_t j;
    for (j = 0; j < num_to_combine; j += 1)
    {
      clusters[(num_clusters + j) + clusters_idx] = (uint32_t) (i + j);
    }

    num_new_clusters = BrotliHistogramCombineLiteral(out, cluster_size, &histogram_symbols[i], &clusters[num_clusters + clusters_idx], pairs, num_to_combine, num_to_combine, max_histograms, pairs_capacity);
    num_clusters += num_new_clusters;
  }

  {
    helper_BrotliClusterHistogramsLiteral_1(&num_clusters, &pairs_capacity, &pairs_idx, m, in_size, max_histograms, out, histogram_symbols, cluster_size, clusters, pairs);
  }
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  BrotliHistogramRemapLiteral(in, in_size, clusters, num_clusters, out, histogram_symbols);
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  *out_size = BrotliHistogramReindexLiteral(m, out, histogram_symbols, in_size);
  if (!(!0))
  {
    return;
  }
}


/*** DEPENDENCIES:
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
size_t BrotliHistogramReindexLiteral(MemoryManager *m, HistogramLiteral *out, uint32_t *symbols, size_t length)
{
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index = (length > 0) ? ((uint32_t *) BrotliAllocate(m, length * (sizeof(uint32_t)))) : (0);
  unsigned int new_index_idx = 0;
  uint32_t next_index;
  HistogramLiteral *tmp;
  unsigned int tmp_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  for (i = 0; i < length; i += 1)
  {
    new_index[i + new_index_idx] = kInvalidIndex;
  }

  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == kInvalidIndex)
    {
      new_index[symbols[i] + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  tmp_idx = (next_index > 0) ? ((HistogramLiteral *) BrotliAllocate(m, next_index * (sizeof(HistogramLiteral)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == next_index)
    {
      tmp[next_index + tmp_idx] = out[symbols[i]];
      next_index += 1;
    }
    symbols[i] = new_index[symbols[i] + new_index_idx];
  }

  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  for (i = 0; i < next_index; i += 1)
  {
    out[i] = tmp[i + tmp_idx];
  }

  {
    BrotliFree(m, tmp);
    tmp_idx = 0;
  }
  ;
  return next_index;
}


----------------------------
void BrotliHistogramRemapLiteral(const HistogramLiteral *in, size_t in_size, const uint32_t *clusters, size_t num_clusters, HistogramLiteral *out, uint32_t *symbols)
{
  size_t i;
  for (i = 0; i < in_size; i += 1)
  {
    uint32_t best_out = (i == 0) ? (symbols[0]) : (symbols[i - 1]);
    double best_bits = BrotliHistogramBitCostDistanceLiteral(&in[i], &out[best_out]);
    size_t j;
    for (j = 0; j < num_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceLiteral(&in[i], &out[clusters[j]]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j];
      }
    }

    symbols[i] = best_out;
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    HistogramClearLiteral(&out[clusters[i]]);
  }

  for (i = 0; i < in_size; i += 1)
  {
    HistogramAddHistogramLiteral(&out[symbols[i]], &in[i]);
  }

}


----------------------------
void helper_BrotliClusterHistogramsLiteral_1(size_t * const num_clusters_ref, size_t * const pairs_capacity_ref, unsigned int * const pairs_idx_ref, MemoryManager * const m, const size_t in_size, size_t max_histograms, HistogramLiteral * const out, uint32_t * const histogram_symbols, uint32_t * const cluster_size, uint32_t * const clusters, HistogramPair * const pairs)
{
  size_t num_clusters = *num_clusters_ref;
  size_t pairs_capacity = *pairs_capacity_ref;
  unsigned int pairs_idx = *pairs_idx_ref;
  size_t max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  {
    if (pairs_capacity < (max_num_pairs + 1))
    {
      size_t _new_size = (pairs_capacity == 0) ? (max_num_pairs + 1) : (pairs_capacity);
      HistogramPair *new_array;
      unsigned int new_array_idx = 0;
      while (_new_size < (max_num_pairs + 1))
        _new_size *= 2;

      new_array_idx = (_new_size > 0) ? ((HistogramPair *) BrotliAllocate(m, _new_size * (sizeof(HistogramPair)))) : (0);
      if (((!(!(!0))) && (!(!(!0)))) && (pairs_capacity != 0))
      {
        memcpy(new_array, pairs, pairs_capacity * (sizeof(HistogramPair)));
      }
      {
        BrotliFree(m, pairs);
        pairs_idx = 0;
      }
      ;
      pairs_idx = &new_array[new_array_idx];
      pairs_capacity = _new_size;
    }
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_clusters = BrotliHistogramCombineLiteral(out, cluster_size, histogram_symbols, clusters, pairs, num_clusters, in_size, max_histograms, max_num_pairs);
  *num_clusters_ref = num_clusters;
  *pairs_capacity_ref = pairs_capacity;
  *pairs_idx_ref = pairs_idx;
}


----------------------------
size_t BrotliHistogramCombineLiteral(HistogramLiteral *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueLiteral(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineLiteral_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
double BrotliPopulationCostLiteral(const HistogramLiteral *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeLiteral();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostLiteral_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostLiteral_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliHistogramRemapCommand(const HistogramCommand *in, size_t in_size, const uint32_t *clusters, size_t num_clusters, HistogramCommand *out, uint32_t *symbols)
{
  size_t i;
  for (i = 0; i < in_size; i += 1)
  {
    uint32_t best_out = (i == 0) ? (symbols[0]) : (symbols[i - 1]);
    double best_bits = BrotliHistogramBitCostDistanceCommand(&in[i], &out[best_out]);
    size_t j;
    for (j = 0; j < num_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceCommand(&in[i], &out[clusters[j]]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j];
      }
    }

    symbols[i] = best_out;
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    HistogramClearCommand(&out[clusters[i]]);
  }

  for (i = 0; i < in_size; i += 1)
  {
    HistogramAddHistogramCommand(&out[symbols[i]], &in[i]);
  }

}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
double BrotliHistogramBitCostDistanceCommand(const HistogramCommand *histogram, const HistogramCommand *candidate)
{
  if (histogram->total_count_ == 0)
  {
    return 0.0;
  }
  else
  {
    HistogramCommand tmp = *histogram;
    HistogramAddHistogramCommand(&tmp, candidate);
    return BrotliPopulationCostCommand(&tmp) - candidate->bit_cost_;
  }
}


----------------------------
inline static void HistogramAddHistogramCommand(HistogramCommand *self, const HistogramCommand *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 704; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


----------------------------
***/


size_t BrotliHistogramReindexCommand(MemoryManager *m, HistogramCommand *out, uint32_t *symbols, size_t length)
{
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index = (length > 0) ? ((uint32_t *) BrotliAllocate(m, length * (sizeof(uint32_t)))) : (0);
  unsigned int new_index_idx = 0;
  uint32_t next_index;
  HistogramCommand *tmp;
  unsigned int tmp_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  for (i = 0; i < length; i += 1)
  {
    new_index[i + new_index_idx] = kInvalidIndex;
  }

  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == kInvalidIndex)
    {
      new_index[symbols[i] + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  tmp_idx = (next_index > 0) ? ((HistogramCommand *) BrotliAllocate(m, next_index * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == next_index)
    {
      tmp[next_index + tmp_idx] = out[symbols[i]];
      next_index += 1;
    }
    symbols[i] = new_index[symbols[i] + new_index_idx];
  }

  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  for (i = 0; i < next_index; i += 1)
  {
    out[i] = tmp[i + tmp_idx];
  }

  {
    BrotliFree(m, tmp);
    tmp_idx = 0;
  }
  ;
  return next_index;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


// hint:  ['num_clusters_ref is a mutable refrence to size_t', 'pairs_capacity_ref is a mutable refrence to size_t', 'pairs_idx_ref is a mutable refrence to unsigned int']
void helper_BrotliClusterHistogramsCommand_1(size_t * const num_clusters_ref, size_t * const pairs_capacity_ref, unsigned int * const pairs_idx_ref, MemoryManager * const m, const size_t in_size, size_t max_histograms, HistogramCommand * const out, uint32_t * const histogram_symbols, uint32_t * const cluster_size, uint32_t * const clusters, HistogramPair * const pairs)
{
  size_t num_clusters = *num_clusters_ref;
  size_t pairs_capacity = *pairs_capacity_ref;
  unsigned int pairs_idx = *pairs_idx_ref;
  size_t max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  {
    if (pairs_capacity < (max_num_pairs + 1))
    {
      size_t _new_size = (pairs_capacity == 0) ? (max_num_pairs + 1) : (pairs_capacity);
      HistogramPair *new_array;
      unsigned int new_array_idx = 0;
      while (_new_size < (max_num_pairs + 1))
        _new_size *= 2;

      new_array_idx = (_new_size > 0) ? ((HistogramPair *) BrotliAllocate(m, _new_size * (sizeof(HistogramPair)))) : (0);
      if (((!(!(!0))) && (!(!(!0)))) && (pairs_capacity != 0))
      {
        memcpy(new_array, pairs, pairs_capacity * (sizeof(HistogramPair)));
      }
      {
        BrotliFree(m, pairs);
        pairs_idx = 0;
      }
      ;
      pairs_idx = &new_array[new_array_idx];
      pairs_capacity = _new_size;
    }
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_clusters = BrotliHistogramCombineCommand(out, cluster_size, histogram_symbols, clusters, pairs, num_clusters, in_size, max_histograms, max_num_pairs);
  *num_clusters_ref = num_clusters;
  *pairs_capacity_ref = pairs_capacity;
  *pairs_idx_ref = pairs_idx;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
size_t BrotliHistogramCombineCommand(HistogramCommand *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueCommand(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineCommand_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliClusterHistogramsCommand(MemoryManager *m, const HistogramCommand *in, const size_t in_size, size_t max_histograms, HistogramCommand *out, size_t *out_size, uint32_t *histogram_symbols)
{
  uint32_t *cluster_size = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int cluster_size_idx = 0;
  uint32_t *clusters = (in_size > 0) ? ((uint32_t *) BrotliAllocate(m, in_size * (sizeof(uint32_t)))) : (0);
  unsigned int clusters_idx = 0;
  size_t num_clusters = 0;
  const size_t max_input_histograms = 64;
  size_t pairs_capacity = (max_input_histograms * max_input_histograms) / 2;
  HistogramPair *pairs = ((pairs_capacity + 1) > 0) ? ((HistogramPair *) BrotliAllocate(m, (pairs_capacity + 1) * (sizeof(HistogramPair)))) : (0);
  unsigned int pairs_idx = 0;
  size_t i;
  if ((((!(!0)) || (!(!0))) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; i < in_size; i += 1)
  {
    cluster_size[i + cluster_size_idx] = 1;
  }

  for (i = 0; i < in_size; i += 1)
  {
    out[i] = in[i];
    out[i].bit_cost_ = BrotliPopulationCostCommand(&in[i]);
    histogram_symbols[i] = (uint32_t) i;
  }

  for (i = 0; i < in_size; i += max_input_histograms)
  {
    size_t num_to_combine = brotli_min_size_t(in_size - i, max_input_histograms);
    size_t num_new_clusters;
    size_t j;
    for (j = 0; j < num_to_combine; j += 1)
    {
      clusters[(num_clusters + j) + clusters_idx] = (uint32_t) (i + j);
    }

    num_new_clusters = BrotliHistogramCombineCommand(out, cluster_size, &histogram_symbols[i], &clusters[num_clusters + clusters_idx], pairs, num_to_combine, num_to_combine, max_histograms, pairs_capacity);
    num_clusters += num_new_clusters;
  }

  {
    helper_BrotliClusterHistogramsCommand_1(&num_clusters, &pairs_capacity, &pairs_idx, m, in_size, max_histograms, out, histogram_symbols, cluster_size, clusters, pairs);
  }
  {
    BrotliFree(m, pairs);
    pairs_idx = 0;
  }
  ;
  {
    BrotliFree(m, cluster_size);
    cluster_size_idx = 0;
  }
  ;
  BrotliHistogramRemapCommand(in, in_size, clusters, num_clusters, out, histogram_symbols);
  {
    BrotliFree(m, clusters);
    clusters_idx = 0;
  }
  ;
  *out_size = BrotliHistogramReindexCommand(m, out, histogram_symbols, in_size);
  if (!(!0))
  {
    return;
  }
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


----------------------------
size_t BrotliHistogramCombineCommand(HistogramCommand *out, uint32_t *cluster_size, uint32_t *symbols, uint32_t *clusters, HistogramPair *pairs, size_t num_clusters, size_t symbols_size, size_t max_clusters, size_t max_num_pairs)
{
  double cost_diff_threshold = 0.0;
  size_t min_cluster_size = 1;
  size_t num_pairs = 0;
  {
    size_t idx1;
    for (idx1 = 0; idx1 < num_clusters; idx1 += 1)
    {
      size_t idx2;
      for (idx2 = idx1 + 1; idx2 < num_clusters; idx2 += 1)
      {
        BrotliCompareAndPushToQueueCommand(out, cluster_size, clusters[idx1], clusters[idx2], max_num_pairs, &pairs[0], &num_pairs);
      }

    }

  }
  while (num_clusters > min_cluster_size)
  {
    helper_BrotliHistogramCombineCommand_1(&num_clusters, &cost_diff_threshold, &min_cluster_size, &num_pairs, out, cluster_size, symbols, clusters, pairs, symbols_size, max_clusters, max_num_pairs);
  }

  return num_clusters;
}


----------------------------
typedef struct HistogramPair
{
  uint32_t idx1;
  uint32_t idx2;
  double cost_combo;
  double cost_diff;
} HistogramPair
----------------------------
typedef enum 
{
  COMMAND_COMPRESS,
  COMMAND_DECOMPRESS,
  COMMAND_HELP,
  COMMAND_INVALID,
  COMMAND_TEST_INTEGRITY,
  COMMAND_NOOP,
  COMMAND_VERSION
} Command
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
void helper_BrotliClusterHistogramsCommand_1(size_t * const num_clusters_ref, size_t * const pairs_capacity_ref, unsigned int * const pairs_idx_ref, MemoryManager * const m, const size_t in_size, size_t max_histograms, HistogramCommand * const out, uint32_t * const histogram_symbols, uint32_t * const cluster_size, uint32_t * const clusters, HistogramPair * const pairs)
{
  size_t num_clusters = *num_clusters_ref;
  size_t pairs_capacity = *pairs_capacity_ref;
  unsigned int pairs_idx = *pairs_idx_ref;
  size_t max_num_pairs = brotli_min_size_t(64 * num_clusters, (num_clusters / 2) * num_clusters);
  {
    if (pairs_capacity < (max_num_pairs + 1))
    {
      size_t _new_size = (pairs_capacity == 0) ? (max_num_pairs + 1) : (pairs_capacity);
      HistogramPair *new_array;
      unsigned int new_array_idx = 0;
      while (_new_size < (max_num_pairs + 1))
        _new_size *= 2;

      new_array_idx = (_new_size > 0) ? ((HistogramPair *) BrotliAllocate(m, _new_size * (sizeof(HistogramPair)))) : (0);
      if (((!(!(!0))) && (!(!(!0)))) && (pairs_capacity != 0))
      {
        memcpy(new_array, pairs, pairs_capacity * (sizeof(HistogramPair)));
      }
      {
        BrotliFree(m, pairs);
        pairs_idx = 0;
      }
      ;
      pairs_idx = &new_array[new_array_idx];
      pairs_capacity = _new_size;
    }
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_clusters = BrotliHistogramCombineCommand(out, cluster_size, histogram_symbols, clusters, pairs, num_clusters, in_size, max_histograms, max_num_pairs);
  *num_clusters_ref = num_clusters;
  *pairs_capacity_ref = pairs_capacity;
  *pairs_idx_ref = pairs_idx;
}


----------------------------
size_t BrotliHistogramReindexCommand(MemoryManager *m, HistogramCommand *out, uint32_t *symbols, size_t length)
{
  static const uint32_t kInvalidIndex = ~((uint32_t) 0);
  uint32_t *new_index = (length > 0) ? ((uint32_t *) BrotliAllocate(m, length * (sizeof(uint32_t)))) : (0);
  unsigned int new_index_idx = 0;
  uint32_t next_index;
  HistogramCommand *tmp;
  unsigned int tmp_idx = 0;
  size_t i;
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  for (i = 0; i < length; i += 1)
  {
    new_index[i + new_index_idx] = kInvalidIndex;
  }

  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == kInvalidIndex)
    {
      new_index[symbols[i] + new_index_idx] = next_index;
      next_index += 1;
    }
  }

  tmp_idx = (next_index > 0) ? ((HistogramCommand *) BrotliAllocate(m, next_index * (sizeof(HistogramCommand)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return 0;
  }
  next_index = 0;
  for (i = 0; i < length; i += 1)
  {
    if (new_index[symbols[i] + new_index_idx] == next_index)
    {
      tmp[next_index + tmp_idx] = out[symbols[i]];
      next_index += 1;
    }
    symbols[i] = new_index[symbols[i] + new_index_idx];
  }

  {
    BrotliFree(m, new_index);
    new_index_idx = 0;
  }
  ;
  for (i = 0; i < next_index; i += 1)
  {
    out[i] = tmp[i + tmp_idx];
  }

  {
    BrotliFree(m, tmp);
    tmp_idx = 0;
  }
  ;
  return next_index;
}


----------------------------
void BrotliHistogramRemapCommand(const HistogramCommand *in, size_t in_size, const uint32_t *clusters, size_t num_clusters, HistogramCommand *out, uint32_t *symbols)
{
  size_t i;
  for (i = 0; i < in_size; i += 1)
  {
    uint32_t best_out = (i == 0) ? (symbols[0]) : (symbols[i - 1]);
    double best_bits = BrotliHistogramBitCostDistanceCommand(&in[i], &out[best_out]);
    size_t j;
    for (j = 0; j < num_clusters; j += 1)
    {
      const double cur_bits = BrotliHistogramBitCostDistanceCommand(&in[i], &out[clusters[j]]);
      if (cur_bits < best_bits)
      {
        best_bits = cur_bits;
        best_out = clusters[j];
      }
    }

    symbols[i] = best_out;
  }

  for (i = 0; i < num_clusters; i += 1)
  {
    HistogramClearCommand(&out[clusters[i]]);
  }

  for (i = 0; i < in_size; i += 1)
  {
    HistogramAddHistogramCommand(&out[symbols[i]], &in[i]);
  }

}


----------------------------
double BrotliPopulationCostCommand(const HistogramCommand *histogram)
{
  static const double kOneSymbolHistogramCost = 12;
  static const double kTwoSymbolHistogramCost = 20;
  static const double kThreeSymbolHistogramCost = 28;
  static const double kFourSymbolHistogramCost = 37;
  const size_t data_size = HistogramDataSizeCommand();
  int count = 0;
  size_t s[5];
  double bits = 0.0;
  size_t i;
  if (histogram->total_count_ == 0)
  {
    return kOneSymbolHistogramCost;
  }
  for (i = 0; i < data_size; i += 1)
  {
    if (histogram->data_[i] > 0)
    {
      s[count] = i;
      count += 1;
      if (count > 4)
      {
        break;
      }
    }
  }

  if (count == 1)
  {
    return kOneSymbolHistogramCost;
  }
  if (count == 2)
  {
    return kTwoSymbolHistogramCost + ((double) histogram->total_count_);
  }
  if (count == 3)
  {
    const uint32_t histo0 = histogram->data_[s[0]];
    const uint32_t histo1 = histogram->data_[s[1]];
    const uint32_t histo2 = histogram->data_[s[2]];
    const uint32_t histomax = brotli_max_uint32_t(histo0, brotli_max_uint32_t(histo1, histo2));
    return (kThreeSymbolHistogramCost + (2 * ((histo0 + histo1) + histo2))) - histomax;
  }
  if (count == 4)
  {
    helper_BrotliPopulationCostCommand_1(&i, histogram, kFourSymbolHistogramCost, s);
  }
  {
    helper_BrotliPopulationCostCommand_2(&bits, &i, histogram, data_size);
  }
  return bits;
}


----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


