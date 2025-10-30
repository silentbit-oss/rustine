inline static uint32_t ZopfliNodeCopyLength(const ZopfliNode *self)
{
  return self->length & 0x1FFFFFF;
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
***/


inline static uint32_t ZopfliNodeCopyDistance(const ZopfliNode *self)
{
  return self->distance;
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
***/


static void SetCost(const uint32_t *histogram, size_t histogram_size, int literal_histogram, float *cost)
{
  size_t sum = 0;
  size_t missing_symbol_sum;
  float log2sum;
  float missing_symbol_cost;
  size_t i;
  for (i = 0; i < histogram_size; i += 1)
  {
    sum += histogram[i];
  }

  log2sum = (float) FastLog2(sum);
  missing_symbol_sum = sum;
  if (!literal_histogram)
  {
    for (i = 0; i < histogram_size; i += 1)
    {
      if (histogram[i] == 0)
      {
        missing_symbol_sum += 1;
      }
    }

  }
  missing_symbol_cost = ((float) FastLog2(missing_symbol_sum)) + 2;
  for (i = 0; i < histogram_size; i += 1)
  {
    if (histogram[i] == 0)
    {
      cost[i] = missing_symbol_cost;
      continue;
    }
    cost[i] = log2sum - ((float) FastLog2(histogram[i]));
    if (cost[i] < 1)
    {
      cost[i] = 1;
    }
  }

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


inline static float ZopfliCostModelGetCommandCost(const ZopfliCostModel *self, uint16_t cmdcode)
{
  return self->cost_cmd_[cmdcode];
}


/*** DEPENDENCIES:
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
***/


inline static float ZopfliCostModelGetDistanceCost(const ZopfliCostModel *self, size_t distcode)
{
  return self->cost_dist_[distcode];
}


/*** DEPENDENCIES:
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
***/


inline static float ZopfliCostModelGetLiteralCosts(const ZopfliCostModel *self, size_t from, size_t to)
{
  return self->literal_costs_[to] - self->literal_costs_[from];
}


/*** DEPENDENCIES:
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
***/


inline static float ZopfliCostModelGetMinCostCmd(const ZopfliCostModel *self)
{
  return self->min_cost_cmd_;
}


/*** DEPENDENCIES:
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
***/


inline static void UpdateZopfliNode(ZopfliNode *nodes, size_t pos, size_t start_pos, size_t len, size_t len_code, size_t dist, size_t short_code, float cost)
{
  ZopfliNode *next = &nodes[pos + len];
  next->length = (uint32_t) (len | (((len + 9u) - len_code) << 25));
  next->distance = (uint32_t) dist;
  next->dcode_insert_length = (uint32_t) ((short_code << 27) | (pos - start_pos));
  next->u.cost = cost;
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
***/


inline static void InitStartPosQueue(StartPosQueue *self)
{
  self->idx_ = 0;
}


/*** DEPENDENCIES:
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
***/


static const PosData *StartPosQueueAt(const StartPosQueue *self, size_t k)
{
  return &self->q_[(k - self->idx_) & 7];
}


/*** DEPENDENCIES:
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
***/


static size_t ComputeMinimumCopyLength(const float start_cost, const ZopfliNode *nodes, const size_t num_bytes, const size_t pos)
{
  float min_cost = start_cost;
  size_t len = 2;
  size_t next_len_bucket = 4;
  size_t next_len_offset = 10;
  while (((pos + len) <= num_bytes) && (nodes[pos + len].u.cost <= min_cost))
  {
    len += 1;
    if (len == next_len_offset)
    {
      min_cost += 1.0f;
      next_len_offset += next_len_bucket;
      next_len_bucket *= 2;
    }
  }

  return len;
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
***/


void BrotliInitZopfliNodes(ZopfliNode *array, size_t length)
{
  ZopfliNode stub;
  size_t i;
  stub.length = 1;
  stub.distance = 0;
  stub.dcode_insert_length = 0;
  stub.u.cost = kInfinity;
  for (i = 0; i < length; i += 1)
    array[i] = stub;

}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
static const float kInfinity = 1.7e38f
----------------------------
***/


inline static uint32_t ZopfliNodeLengthCode(const ZopfliNode *self)
{
  const uint32_t modifier = self->length >> 25;
  return (ZopfliNodeCopyLength(self) + 9u) - modifier;
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static uint32_t ZopfliNodeCopyLength(const ZopfliNode *self)
{
  return self->length & 0x1FFFFFF;
}


----------------------------
***/


inline static uint32_t ZopfliNodeDistanceCode(const ZopfliNode *self)
{
  const uint32_t short_code = self->dcode_insert_length >> 27;
  return (short_code == 0) ? ((ZopfliNodeCopyDistance(self) + 16) - 1) : (short_code - 1);
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static uint32_t ZopfliNodeCopyDistance(const ZopfliNode *self)
{
  return self->distance;
}


----------------------------
***/


inline static uint32_t ZopfliNodeCommandLength(const ZopfliNode *self)
{
  return ZopfliNodeCopyLength(self) + (self->dcode_insert_length & 0x7FFFFFF);
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static uint32_t ZopfliNodeCopyLength(const ZopfliNode *self)
{
  return self->length & 0x1FFFFFF;
}


----------------------------
***/


static size_t StartPosQueueSize(const StartPosQueue *self)
{
  return brotli_min_size_t(self->idx_, 8);
}


/*** DEPENDENCIES:
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


static size_t ComputeShortestPathFromNodes(size_t num_bytes, ZopfliNode *nodes)
{
  size_t index = num_bytes;
  size_t num_commands = 0;
  index -= 1;
  index -= 1;
  index -= 1;
  index -= 1;
  while (((nodes[index].dcode_insert_length & 0x7FFFFFF) == 0) && (nodes[index].length == 1))
    --index;

  nodes[index].u.next = ~((uint32_t) 0);
  while (index != 0)
  {
    size_t len = ZopfliNodeCommandLength(&nodes[index]);
    index -= len;
    nodes[index].u.next = (uint32_t) len;
    num_commands++;
  }

  return num_commands;
}


/*** DEPENDENCIES:
inline static uint32_t ZopfliNodeCommandLength(const ZopfliNode *self)
{
  return ZopfliNodeCopyLength(self) + (self->dcode_insert_length & 0x7FFFFFF);
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
***/


// hint:  ['ringbuffer_mask_ref is a mutable refrence to size_t', 'pos_ref is a mutable refrence to size_t']
void helper_ZopfliCostModelSetFromCommands_1(size_t * const ringbuffer_mask_ref, size_t * const pos_ref, const uint8_t * const ringbuffer, const Command * const commands, uint32_t histogram_literal[256], uint32_t histogram_cmd[704], uint32_t histogram_dist[544], size_t i)
{
  size_t ringbuffer_mask = *ringbuffer_mask_ref;
  size_t pos = *pos_ref;
  size_t inslength = commands[i].insert_len_;
  size_t copylength = CommandCopyLen(&commands[i]);
  size_t distcode = commands[i].dist_prefix_ & 0x3FF;
  size_t cmdcode = commands[i].cmd_prefix_;
  size_t j;
  histogram_cmd[cmdcode] += 1;
  if (cmdcode >= 128)
  {
    histogram_dist[distcode] += 1;
  }
  for (j = 0; j < inslength; j += 1)
  {
    histogram_literal[ringbuffer[(pos + j) & ringbuffer_mask]] += 1;
  }

  pos += inslength + copylength;
  *ringbuffer_mask_ref = ringbuffer_mask;
  *pos_ref = pos;
}


/*** DEPENDENCIES:
inline static uint32_t CommandCopyLen(const Command *self)
{
  return self->copy_len_ & 0x1FFFFFF;
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


void BrotliZopfliCreateCommands(const size_t num_bytes, const size_t block_start, const ZopfliNode *nodes, int *dist_cache, size_t *last_insert_len, const BrotliEncoderParams *params, Command *commands, size_t *num_literals)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  size_t pos = 0;
  uint32_t offset = nodes[0].u.next;
  size_t i;
  size_t gap = 0;
  for (i = 0; offset != (~((uint32_t) 0)); i += 1)
  {
    const ZopfliNode *next = &nodes[pos + offset];
    size_t copy_length = ZopfliNodeCopyLength(next);
    size_t insert_length = next->dcode_insert_length & 0x7FFFFFF;
    pos += insert_length;
    offset = next->u.next;
    if (i == 0)
    {
      insert_length += *last_insert_len;
      *last_insert_len = 0;
    }
    {
      size_t distance = ZopfliNodeCopyDistance(next);
      size_t len_code = ZopfliNodeLengthCode(next);
      size_t dictionary_start = brotli_min_size_t((block_start + pos) + stream_offset, max_backward_limit);
      int is_dictionary = (!(!(distance > (dictionary_start + gap)))) ? (1) : (0);
      size_t dist_code = ZopfliNodeDistanceCode(next);
      InitCommand(&commands[i], &params->dist, insert_length, copy_length, ((int) len_code) - ((int) copy_length), dist_code);
      if ((!is_dictionary) && (dist_code > 0))
      {
        dist_cache[3] = dist_cache[2];
        dist_cache[2] = dist_cache[1];
        dist_cache[1] = dist_cache[0];
        dist_cache[0] = (int) distance;
      }
    }
    *num_literals += insert_length;
    pos += copy_length;
  }

  *last_insert_len += num_bytes - pos;
}


/*** DEPENDENCIES:
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
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
inline static uint32_t ZopfliNodeLengthCode(const ZopfliNode *self)
{
  const uint32_t modifier = self->length >> 25;
  return (ZopfliNodeCopyLength(self) + 9u) - modifier;
}


----------------------------
inline static void InitCommand(Command *self, const BrotliDistanceParams *dist, size_t insertlen, size_t copylen, int copylen_code_delta, size_t distance_code)
{
  uint32_t delta = (uint8_t) ((int8_t) copylen_code_delta);
  self->insert_len_ = (uint32_t) insertlen;
  self->copy_len_ = (uint32_t) (copylen | (delta << 25));
  PrefixEncodeCopyDistance(distance_code, dist->num_direct_distance_codes, dist->distance_postfix_bits, &self->dist_prefix_, &self->dist_extra_);
  GetLengthCode(insertlen, (size_t) (((int) copylen) + copylen_code_delta), (!(!((self->dist_prefix_ & 0x3FF) == 0))) ? (1) : (0), &self->cmd_prefix_);
}


----------------------------
inline static uint32_t ZopfliNodeCopyDistance(const ZopfliNode *self)
{
  return self->distance;
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static uint32_t ZopfliNodeDistanceCode(const ZopfliNode *self)
{
  const uint32_t short_code = self->dcode_insert_length >> 27;
  return (short_code == 0) ? ((ZopfliNodeCopyDistance(self) + 16) - 1) : (short_code - 1);
}


----------------------------
inline static uint32_t ZopfliNodeCopyLength(const ZopfliNode *self)
{
  return self->length & 0x1FFFFFF;
}


----------------------------
None
----------------------------
***/


static void CleanupZopfliCostModel(MemoryManager *m, ZopfliCostModel *self)
{
  {
    BrotliFree(m, self->literal_costs_);
    self->literal_costs_ = 0;
  }
  ;
  {
    BrotliFree(m, self->cost_dist_);
    self->cost_dist_ = 0;
  }
  ;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
***/


static void ZopfliCostModelSetFromLiteralCosts(ZopfliCostModel *self, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  float *literal_costs = self->literal_costs_;
  float literal_carry = 0.0;
  float *cost_dist = self->cost_dist_;
  float *cost_cmd = self->cost_cmd_;
  size_t num_bytes = self->num_bytes_;
  size_t i;
  BrotliEstimateBitCostsForLiterals(position, num_bytes, ringbuffer_mask, ringbuffer, &literal_costs[1]);
  literal_costs[0] = 0.0;
  for (i = 0; i < num_bytes; i += 1)
  {
    literal_carry += literal_costs[i + 1];
    literal_costs[i + 1] = literal_costs[i] + literal_carry;
    literal_carry -= literal_costs[i + 1] - literal_costs[i];
  }

  for (i = 0; i < 704; i += 1)
  {
    cost_cmd[i] = (float) FastLog2(11 + ((uint32_t) i));
  }

  for (i = 0; i < self->distance_histogram_size; i += 1)
  {
    cost_dist[i] = (float) FastLog2(20 + ((uint32_t) i));
  }

  self->min_cost_cmd_ = (float) FastLog2(11);
}


/*** DEPENDENCIES:
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
void BrotliEstimateBitCostsForLiterals(size_t pos, size_t len, size_t mask, const uint8_t *data, float *cost)
{
  if (BrotliIsMostlyUTF8(data, pos, mask, len, kMinUTF8Ratio))
  {
    EstimateBitCostsForLiteralsUTF8(pos, len, mask, data, cost);
    return;
  }
  else
  {
    size_t histogram[256] = {0};
    size_t window_half = 2000;
    size_t in_window = brotli_min_size_t(window_half, len);
    size_t i;
    for (i = 0; i < in_window; i += 1)
    {
      histogram[data[(pos + i) & mask]] += 1;
    }

    for (i = 0; i < len; i += 1)
    {
      size_t histo;
      if (i >= window_half)
      {
        histogram[data[((pos + i) - window_half) & mask]] -= 1;
        in_window -= 1;
      }
      if ((i + window_half) < len)
      {
        histogram[data[((pos + i) + window_half) & mask]] += 1;
        in_window += 1;
      }
      histo = histogram[data[(pos + i) & mask]];
      if (histo == 0)
      {
        histo = 1;
      }
      {
        double lit_cost = FastLog2(in_window) - FastLog2(histo);
        lit_cost += 0.029;
        if (lit_cost < 1.0)
        {
          lit_cost *= 0.5;
          lit_cost += 0.5;
        }
        cost[i] = (float) lit_cost;
      }
    }

  }
}


----------------------------
***/


static uint32_t ComputeDistanceShortcut(const size_t block_start, const size_t pos, const size_t max_backward_limit, const size_t gap, const ZopfliNode *nodes)
{
  const size_t clen = ZopfliNodeCopyLength(&nodes[pos]);
  const size_t ilen = nodes[pos].dcode_insert_length & 0x7FFFFFF;
  const size_t dist = ZopfliNodeCopyDistance(&nodes[pos]);
  if (pos == 0)
  {
    return 0;
  }
  else
    if ((((dist + clen) <= ((block_start + pos) + gap)) && (dist <= (max_backward_limit + gap))) && (ZopfliNodeDistanceCode(&nodes[pos]) > 0))
  {
    return (uint32_t) pos;
  }
  else
  {
    return nodes[(pos - clen) - ilen].u.shortcut;
  }
}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static uint32_t ZopfliNodeDistanceCode(const ZopfliNode *self)
{
  const uint32_t short_code = self->dcode_insert_length >> 27;
  return (short_code == 0) ? ((ZopfliNodeCopyDistance(self) + 16) - 1) : (short_code - 1);
}


----------------------------
inline static uint32_t ZopfliNodeCopyDistance(const ZopfliNode *self)
{
  return self->distance;
}


----------------------------
inline static uint32_t ZopfliNodeCopyLength(const ZopfliNode *self)
{
  return self->length & 0x1FFFFFF;
}


----------------------------
***/


static void StartPosQueuePush(StartPosQueue *self, const PosData *posdata)
{
  size_t offset = (~(self->idx_++)) & 7;
  size_t len = StartPosQueueSize(self);
  size_t i;
  PosData *q = self->q_;
  q[offset] = *posdata;
  for (i = 1; i < len; i += 1)
  {
    if (q[offset & 7].costdiff > q[(offset + 1) & 7].costdiff)
    {
      {
        PosData __brotli_swap_tmp = q[offset & 7];
        q[offset & 7] = q[(offset + 1) & 7];
        q[(offset + 1) & 7] = __brotli_swap_tmp;
      }
      ;
    }
    offset += 1;
  }

}


/*** DEPENDENCIES:
static size_t StartPosQueueSize(const StartPosQueue *self)
{
  return brotli_min_size_t(self->idx_, 8);
}


----------------------------
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
typedef struct PosData
{
  size_t pos;
  int distance_cache[4];
  float costdiff;
  float cost;
} PosData
----------------------------
***/


static void ComputeDistanceCache(const size_t pos, const int *starting_dist_cache, const ZopfliNode *nodes, int *dist_cache)
{
  unsigned int starting_dist_cache_idx = 0;
  int idx = 0;
  size_t p = nodes[pos].u.shortcut;
  while ((idx < 4) && (p > 0))
  {
    const size_t ilen = nodes[p].dcode_insert_length & 0x7FFFFFF;
    const size_t clen = ZopfliNodeCopyLength(&nodes[p]);
    const size_t dist = ZopfliNodeCopyDistance(&nodes[p]);
    dist_cache[idx] = (int) dist;
    idx += 1;
    p = nodes[(p - clen) - ilen].u.shortcut;
  }

  for (; idx < 4; idx += 1)
  {
    dist_cache[idx] = starting_dist_cache[starting_dist_cache_idx];
    starting_dist_cache_idx += 1;
  }

}


/*** DEPENDENCIES:
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static uint32_t ZopfliNodeCopyDistance(const ZopfliNode *self)
{
  return self->distance;
}


----------------------------
inline static uint32_t ZopfliNodeCopyLength(const ZopfliNode *self)
{
  return self->length & 0x1FFFFFF;
}


----------------------------
***/


static void EvaluateNode(const size_t block_start, const size_t pos, const size_t max_backward_limit, const size_t gap, const int *starting_dist_cache, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  float node_cost = nodes[pos].u.cost;
  nodes[pos].u.shortcut = ComputeDistanceShortcut(block_start, pos, max_backward_limit, gap, nodes);
  if (node_cost <= ZopfliCostModelGetLiteralCosts(model, 0, pos))
  {
    PosData posdata;
    posdata.pos = pos;
    posdata.cost = node_cost;
    posdata.costdiff = node_cost - ZopfliCostModelGetLiteralCosts(model, 0, pos);
    ComputeDistanceCache(pos, starting_dist_cache, nodes, posdata.distance_cache);
    StartPosQueuePush(queue, &posdata);
  }
}


/*** DEPENDENCIES:
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
static uint32_t ComputeDistanceShortcut(const size_t block_start, const size_t pos, const size_t max_backward_limit, const size_t gap, const ZopfliNode *nodes)
{
  const size_t clen = ZopfliNodeCopyLength(&nodes[pos]);
  const size_t ilen = nodes[pos].dcode_insert_length & 0x7FFFFFF;
  const size_t dist = ZopfliNodeCopyDistance(&nodes[pos]);
  if (pos == 0)
  {
    return 0;
  }
  else
    if ((((dist + clen) <= ((block_start + pos) + gap)) && (dist <= (max_backward_limit + gap))) && (ZopfliNodeDistanceCode(&nodes[pos]) > 0))
  {
    return (uint32_t) pos;
  }
  else
  {
    return nodes[(pos - clen) - ilen].u.shortcut;
  }
}


----------------------------
static void StartPosQueuePush(StartPosQueue *self, const PosData *posdata)
{
  size_t offset = (~(self->idx_++)) & 7;
  size_t len = StartPosQueueSize(self);
  size_t i;
  PosData *q = self->q_;
  q[offset] = *posdata;
  for (i = 1; i < len; i += 1)
  {
    if (q[offset & 7].costdiff > q[(offset + 1) & 7].costdiff)
    {
      {
        PosData __brotli_swap_tmp = q[offset & 7];
        q[offset & 7] = q[(offset + 1) & 7];
        q[(offset + 1) & 7] = __brotli_swap_tmp;
      }
      ;
    }
    offset += 1;
  }

}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static float ZopfliCostModelGetLiteralCosts(const ZopfliCostModel *self, size_t from, size_t to)
{
  return self->literal_costs_[to] - self->literal_costs_[from];
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
static void ComputeDistanceCache(const size_t pos, const int *starting_dist_cache, const ZopfliNode *nodes, int *dist_cache)
{
  unsigned int starting_dist_cache_idx = 0;
  int idx = 0;
  size_t p = nodes[pos].u.shortcut;
  while ((idx < 4) && (p > 0))
  {
    const size_t ilen = nodes[p].dcode_insert_length & 0x7FFFFFF;
    const size_t clen = ZopfliNodeCopyLength(&nodes[p]);
    const size_t dist = ZopfliNodeCopyDistance(&nodes[p]);
    dist_cache[idx] = (int) dist;
    idx += 1;
    p = nodes[(p - clen) - ilen].u.shortcut;
  }

  for (; idx < 4; idx += 1)
  {
    dist_cache[idx] = starting_dist_cache[starting_dist_cache_idx];
    starting_dist_cache_idx += 1;
  }

}


----------------------------
typedef struct PosData
{
  size_t pos;
  int distance_cache[4];
  float costdiff;
  float cost;
} PosData
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'j_ref is a mutable refrence to size_t']
void helper_helper_UpdateNodes_1_1(size_t * const result_ref, size_t * const j_ref, const size_t pos, const BrotliEncoderParams * const params, const size_t num_matches, const BackwardMatch * const matches, const ZopfliCostModel * const model, ZopfliNode * const nodes, const size_t dictionary_start, const size_t max_zopfli_len, size_t min_len, size_t gap, const size_t start, const uint16_t inscode, const float base_cost)
{
  size_t result = *result_ref;
  size_t j = *j_ref;
  size_t len = min_len;
  for (j = 0; j < num_matches; j += 1)
  {
    BackwardMatch match = matches[j];
    size_t dist = match.distance;
    int is_dictionary_match = (!(!(dist > (dictionary_start + gap)))) ? (1) : (0);
    size_t dist_code = (dist + 16) - 1;
    uint16_t dist_symbol;
    uint32_t distextra;
    uint32_t distnumextra;
    float dist_cost;
    size_t max_match_len;
    PrefixEncodeCopyDistance(dist_code, params->dist.num_direct_distance_codes, params->dist.distance_postfix_bits, &dist_symbol, &distextra);
    distnumextra = dist_symbol >> 10;
    dist_cost = (base_cost + ((float) distnumextra)) + ZopfliCostModelGetDistanceCost(model, dist_symbol & 0x3FF);
    max_match_len = BackwardMatchLength(&match);
    if ((len < max_match_len) && (is_dictionary_match || (max_match_len > max_zopfli_len)))
    {
      len = max_match_len;
    }
    for (; len <= max_match_len; len += 1)
    {
      const size_t len_code = (is_dictionary_match) ? (BackwardMatchLengthCode(&match)) : (len);
      const uint16_t copycode = GetCopyLengthCode(len_code);
      const uint16_t cmdcode = CombineLengthCodes(inscode, copycode, 0);
      const float cost = (dist_cost + ((float) GetCopyExtra(copycode))) + ZopfliCostModelGetCommandCost(model, cmdcode);
      if (cost < nodes[pos + len].u.cost)
      {
        UpdateZopfliNode(nodes, pos, start, len, len_code, dist, 0, cost);
        result = brotli_max_size_t(result, len);
      }
    }

  }

  *result_ref = result;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
inline static size_t BackwardMatchLength(const BackwardMatch *self)
{
  return self->length_and_code >> 5;
}


----------------------------
inline static uint32_t GetCopyExtra(uint16_t copycode)
{
  return kBrotliCopyExtra[copycode];
}


----------------------------
inline static uint16_t GetCopyLengthCode(size_t copylen)
{
  if (copylen < 10)
  {
    return (uint16_t) (copylen - 2);
  }
  else
    if (copylen < 134)
  {
    uint32_t nbits = Log2FloorNonZero(copylen - 6) - 1u;
    return (uint16_t) (((nbits << 1) + ((copylen - 6) >> nbits)) + 4);
  }
  else
    if (copylen < 2118)
  {
    return (uint16_t) (Log2FloorNonZero(copylen - 70) + 12);
  }
  else
  {
    return 23u;
  }
}


----------------------------
inline static size_t BackwardMatchLengthCode(const BackwardMatch *self)
{
  size_t code = self->length_and_code & 31;
  return (code) ? (code) : (BackwardMatchLength(self));
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void PrefixEncodeCopyDistance(size_t distance_code, size_t num_direct_codes, size_t postfix_bits, uint16_t *code, uint32_t *extra_bits)
{
  if (distance_code < (16 + num_direct_codes))
  {
    *code = (uint16_t) distance_code;
    *extra_bits = 0;
    return;
  }
  else
  {
    size_t dist = (((size_t) 1) << (postfix_bits + 2u)) + ((distance_code - 16) - num_direct_codes);
    size_t bucket = Log2FloorNonZero(dist) - 1;
    size_t postfix_mask = (1u << postfix_bits) - 1;
    size_t postfix = dist & postfix_mask;
    size_t prefix = (dist >> bucket) & 1;
    size_t offset = (2 + prefix) << bucket;
    size_t nbits = bucket - postfix_bits;
    *code = (uint16_t) ((nbits << 10) | (((16 + num_direct_codes) + (((2 * (nbits - 1)) + prefix) << postfix_bits)) + postfix));
    *extra_bits = (uint32_t) ((dist - offset) >> postfix_bits);
  }
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static float ZopfliCostModelGetDistanceCost(const ZopfliCostModel *self, size_t distcode)
{
  return self->cost_dist_[distcode];
}


----------------------------
inline static uint16_t CombineLengthCodes(uint16_t inscode, uint16_t copycode, int use_last_distance)
{
  uint16_t bits64 = (uint16_t) ((copycode & 0x7u) | ((inscode & 0x7u) << 3u));
  if ((use_last_distance && (inscode < 8u)) && (copycode < 16u))
  {
    return (copycode < 8u) ? (bits64) : (bits64 | 64u);
  }
  else
  {
    uint32_t offset = 2u * ((copycode >> 3u) + (3u * (inscode >> 3u)));
    offset = ((offset << 5u) + 0x40u) + ((0x520D40u >> offset) & 0xC0u);
    return (uint16_t) (offset | bits64);
  }
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static void UpdateZopfliNode(ZopfliNode *nodes, size_t pos, size_t start_pos, size_t len, size_t len_code, size_t dist, size_t short_code, float cost)
{
  ZopfliNode *next = &nodes[pos + len];
  next->length = (uint32_t) (len | (((len + 9u) - len_code) << 25));
  next->distance = (uint32_t) dist;
  next->dcode_insert_length = (uint32_t) ((short_code << 27) | (pos - start_pos));
  next->u.cost = cost;
}


----------------------------
inline static float ZopfliCostModelGetCommandCost(const ZopfliCostModel *self, uint16_t cmdcode)
{
  return self->cost_cmd_[cmdcode];
}


----------------------------
None
----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t', 'best_len_ref is a mutable refrence to size_t']
void helper_helper_UpdateNodes_1_2(size_t * const result_ref, size_t * const best_len_ref, const size_t pos, const uint8_t * const ringbuffer, const size_t ringbuffer_mask, const ZopfliCostModel * const model, ZopfliNode * const nodes, const size_t cur_ix, const size_t cur_ix_masked, const size_t max_distance, const size_t dictionary_start, const size_t max_len, size_t gap, const PosData * const posdata, const size_t start, const uint16_t inscode, const float base_cost, size_t j)
{
  size_t result = *result_ref;
  size_t best_len = *best_len_ref;
  const size_t idx = kDistanceCacheIndex[j];
  const size_t backward = (size_t) (posdata->distance_cache[idx] + kDistanceCacheOffset[j]);
  size_t prev_ix = cur_ix - backward;
  size_t len = 0;
  uint8_t continuation = ringbuffer[cur_ix_masked + best_len];
  if ((cur_ix_masked + best_len) > ringbuffer_mask)
  {
    break;
  }
  if (__builtin_expect(backward > (dictionary_start + gap), 0))
  {
    continue;
  }
  if (backward <= max_distance)
  {
    if (prev_ix >= cur_ix)
    {
      continue;
    }
    prev_ix &= ringbuffer_mask;
    if (((prev_ix + best_len) > ringbuffer_mask) || (continuation != ringbuffer[prev_ix + best_len]))
    {
      continue;
    }
    len = FindMatchLengthWithLimit(&ringbuffer[prev_ix], &ringbuffer[cur_ix_masked], max_len);
  }
  else
  {
    continue;
  }
  {
    const float dist_cost = base_cost + ZopfliCostModelGetDistanceCost(model, j);
    size_t l;
    for (l = best_len + 1; l <= len; l += 1)
    {
      const uint16_t copycode = GetCopyLengthCode(l);
      const uint16_t cmdcode = CombineLengthCodes(inscode, copycode, j == 0);
      const float cost = (((cmdcode < 128) ? (base_cost) : (dist_cost)) + ((float) GetCopyExtra(copycode))) + ZopfliCostModelGetCommandCost(model, cmdcode);
      if (cost < nodes[pos + l].u.cost)
      {
        UpdateZopfliNode(nodes, pos, start, l, l, backward, j + 1, cost);
        result = brotli_max_size_t(result, l);
      }
      best_len = l;
    }

  }
  *result_ref = result;
  *best_len_ref = best_len;
}


/*** DEPENDENCIES:
inline static uint16_t GetCopyLengthCode(size_t copylen)
{
  if (copylen < 10)
  {
    return (uint16_t) (copylen - 2);
  }
  else
    if (copylen < 134)
  {
    uint32_t nbits = Log2FloorNonZero(copylen - 6) - 1u;
    return (uint16_t) (((nbits << 1) + ((copylen - 6) >> nbits)) + 4);
  }
  else
    if (copylen < 2118)
  {
    return (uint16_t) (Log2FloorNonZero(copylen - 70) + 12);
  }
  else
  {
    return 23u;
  }
}


----------------------------
inline static uint32_t GetCopyExtra(uint16_t copycode)
{
  return kBrotliCopyExtra[copycode];
}


----------------------------
static const int kDistanceCacheOffset[] = {0, 0, 0, 0, -1, 1, -2, 2, -3, 3, -1, 1, -2, 2, -3, 3}
----------------------------
typedef struct PosData
{
  size_t pos;
  int distance_cache[4];
  float costdiff;
  float cost;
} PosData
----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static size_t FindMatchLengthWithLimit(const uint8_t *s1, const uint8_t *s2, size_t limit)
{
  unsigned int s2_idx = 0;
  size_t matched = 0;
  size_t limit2 = (limit >> 3) + 1;
  while (__builtin_expect(!(!(--limit2)), 1))
  {
    if (__builtin_expect(BrotliUnalignedRead64(s2) == BrotliUnalignedRead64(s1 + matched), 0))
    {
      s2_idx += 8;
      matched += 8;
    }
    else
    {
      uint64_t x = BrotliUnalignedRead64(s2) ^ BrotliUnalignedRead64(s1 + matched);
      size_t matching_bits = (size_t) __builtin_ctzll(x);
      matched += matching_bits >> 3;
      return matched;
    }
  }

  limit = (limit & 7) + 1;
  while (--limit)
  {
    if (__builtin_expect(!(!(s1[matched] == (*(&s2[s2_idx])))), 1))
    {
      s2_idx += 1;
      matched += 1;
    }
    else
    {
      return matched;
    }
  }

  return matched;
}


----------------------------
static const uint32_t kDistanceCacheIndex[] = {0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1}
----------------------------
inline static float ZopfliCostModelGetDistanceCost(const ZopfliCostModel *self, size_t distcode)
{
  return self->cost_dist_[distcode];
}


----------------------------
inline static uint16_t CombineLengthCodes(uint16_t inscode, uint16_t copycode, int use_last_distance)
{
  uint16_t bits64 = (uint16_t) ((copycode & 0x7u) | ((inscode & 0x7u) << 3u));
  if ((use_last_distance && (inscode < 8u)) && (copycode < 16u))
  {
    return (copycode < 8u) ? (bits64) : (bits64 | 64u);
  }
  else
  {
    uint32_t offset = 2u * ((copycode >> 3u) + (3u * (inscode >> 3u)));
    offset = ((offset << 5u) + 0x40u) + ((0x520D40u >> offset) & 0xC0u);
    return (uint16_t) (offset | bits64);
  }
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static void UpdateZopfliNode(ZopfliNode *nodes, size_t pos, size_t start_pos, size_t len, size_t len_code, size_t dist, size_t short_code, float cost)
{
  ZopfliNode *next = &nodes[pos + len];
  next->length = (uint32_t) (len | (((len + 9u) - len_code) << 25));
  next->distance = (uint32_t) dist;
  next->dcode_insert_length = (uint32_t) ((short_code << 27) | (pos - start_pos));
  next->u.cost = cost;
}


----------------------------
inline static float ZopfliCostModelGetCommandCost(const ZopfliCostModel *self, uint16_t cmdcode)
{
  return self->cost_cmd_[cmdcode];
}


----------------------------
***/


// hint:  ['result_ref is a mutable refrence to size_t']
void helper_UpdateNodes_1(size_t * const result_ref, const size_t pos, const uint8_t * const ringbuffer, const size_t ringbuffer_mask, const BrotliEncoderParams * const params, const size_t num_matches, const BackwardMatch * const matches, const ZopfliCostModel * const model, StartPosQueue * const queue, ZopfliNode * const nodes, const size_t cur_ix, const size_t cur_ix_masked, const size_t max_distance, const size_t dictionary_start, const size_t max_len, const size_t max_zopfli_len, size_t min_len, size_t k, size_t gap)
{
  size_t result = *result_ref;
  const PosData *posdata = StartPosQueueAt(queue, k);
  const size_t start = posdata->pos;
  const uint16_t inscode = GetInsertLengthCode(pos - start);
  const float start_costdiff = posdata->costdiff;
  const float base_cost = (start_costdiff + ((float) GetInsertExtra(inscode))) + ZopfliCostModelGetLiteralCosts(model, 0, pos);
  size_t best_len = min_len - 1;
  size_t j = 0;
  for (; (j < 16) && (best_len < max_len); j += 1)
  {
    helper_helper_UpdateNodes_1_2(&result, &best_len, pos, ringbuffer, ringbuffer_mask, model, nodes, cur_ix, cur_ix_masked, max_distance, dictionary_start, max_len, gap, posdata, start, inscode, base_cost, j);
  }

  if (k >= 2)
  {
    continue;
  }
  {
    helper_helper_UpdateNodes_1_1(&result, &j, pos, params, num_matches, matches, model, nodes, dictionary_start, max_zopfli_len, min_len, gap, start, inscode, base_cost);
  }
  *result_ref = result;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
inline static uint32_t GetInsertExtra(uint16_t inscode)
{
  return kBrotliInsExtra[inscode];
}


----------------------------
void helper_helper_UpdateNodes_1_1(size_t * const result_ref, size_t * const j_ref, const size_t pos, const BrotliEncoderParams * const params, const size_t num_matches, const BackwardMatch * const matches, const ZopfliCostModel * const model, ZopfliNode * const nodes, const size_t dictionary_start, const size_t max_zopfli_len, size_t min_len, size_t gap, const size_t start, const uint16_t inscode, const float base_cost)
{
  size_t result = *result_ref;
  size_t j = *j_ref;
  size_t len = min_len;
  for (j = 0; j < num_matches; j += 1)
  {
    BackwardMatch match = matches[j];
    size_t dist = match.distance;
    int is_dictionary_match = (!(!(dist > (dictionary_start + gap)))) ? (1) : (0);
    size_t dist_code = (dist + 16) - 1;
    uint16_t dist_symbol;
    uint32_t distextra;
    uint32_t distnumextra;
    float dist_cost;
    size_t max_match_len;
    PrefixEncodeCopyDistance(dist_code, params->dist.num_direct_distance_codes, params->dist.distance_postfix_bits, &dist_symbol, &distextra);
    distnumextra = dist_symbol >> 10;
    dist_cost = (base_cost + ((float) distnumextra)) + ZopfliCostModelGetDistanceCost(model, dist_symbol & 0x3FF);
    max_match_len = BackwardMatchLength(&match);
    if ((len < max_match_len) && (is_dictionary_match || (max_match_len > max_zopfli_len)))
    {
      len = max_match_len;
    }
    for (; len <= max_match_len; len += 1)
    {
      const size_t len_code = (is_dictionary_match) ? (BackwardMatchLengthCode(&match)) : (len);
      const uint16_t copycode = GetCopyLengthCode(len_code);
      const uint16_t cmdcode = CombineLengthCodes(inscode, copycode, 0);
      const float cost = (dist_cost + ((float) GetCopyExtra(copycode))) + ZopfliCostModelGetCommandCost(model, cmdcode);
      if (cost < nodes[pos + len].u.cost)
      {
        UpdateZopfliNode(nodes, pos, start, len, len_code, dist, 0, cost);
        result = brotli_max_size_t(result, len);
      }
    }

  }

  *result_ref = result;
  *j_ref = j;
}


----------------------------
static const PosData *StartPosQueueAt(const StartPosQueue *self, size_t k)
{
  return &self->q_[(k - self->idx_) & 7];
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
inline static float ZopfliCostModelGetLiteralCosts(const ZopfliCostModel *self, size_t from, size_t to)
{
  return self->literal_costs_[to] - self->literal_costs_[from];
}


----------------------------
void helper_helper_UpdateNodes_1_2(size_t * const result_ref, size_t * const best_len_ref, const size_t pos, const uint8_t * const ringbuffer, const size_t ringbuffer_mask, const ZopfliCostModel * const model, ZopfliNode * const nodes, const size_t cur_ix, const size_t cur_ix_masked, const size_t max_distance, const size_t dictionary_start, const size_t max_len, size_t gap, const PosData * const posdata, const size_t start, const uint16_t inscode, const float base_cost, size_t j)
{
  size_t result = *result_ref;
  size_t best_len = *best_len_ref;
  const size_t idx = kDistanceCacheIndex[j];
  const size_t backward = (size_t) (posdata->distance_cache[idx] + kDistanceCacheOffset[j]);
  size_t prev_ix = cur_ix - backward;
  size_t len = 0;
  uint8_t continuation = ringbuffer[cur_ix_masked + best_len];
  if ((cur_ix_masked + best_len) > ringbuffer_mask)
  {
    break;
  }
  if (__builtin_expect(backward > (dictionary_start + gap), 0))
  {
    continue;
  }
  if (backward <= max_distance)
  {
    if (prev_ix >= cur_ix)
    {
      continue;
    }
    prev_ix &= ringbuffer_mask;
    if (((prev_ix + best_len) > ringbuffer_mask) || (continuation != ringbuffer[prev_ix + best_len]))
    {
      continue;
    }
    len = FindMatchLengthWithLimit(&ringbuffer[prev_ix], &ringbuffer[cur_ix_masked], max_len);
  }
  else
  {
    continue;
  }
  {
    const float dist_cost = base_cost + ZopfliCostModelGetDistanceCost(model, j);
    size_t l;
    for (l = best_len + 1; l <= len; l += 1)
    {
      const uint16_t copycode = GetCopyLengthCode(l);
      const uint16_t cmdcode = CombineLengthCodes(inscode, copycode, j == 0);
      const float cost = (((cmdcode < 128) ? (base_cost) : (dist_cost)) + ((float) GetCopyExtra(copycode))) + ZopfliCostModelGetCommandCost(model, cmdcode);
      if (cost < nodes[pos + l].u.cost)
      {
        UpdateZopfliNode(nodes, pos, start, l, l, backward, j + 1, cost);
        result = brotli_max_size_t(result, l);
      }
      best_len = l;
    }

  }
  *result_ref = result;
  *best_len_ref = best_len;
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static uint16_t GetInsertLengthCode(size_t insertlen)
{
  if (insertlen < 6)
  {
    return (uint16_t) insertlen;
  }
  else
    if (insertlen < 130)
  {
    uint32_t nbits = Log2FloorNonZero(insertlen - 2) - 1u;
    return (uint16_t) (((nbits << 1) + ((insertlen - 2) >> nbits)) + 2);
  }
  else
    if (insertlen < 2114)
  {
    return (uint16_t) (Log2FloorNonZero(insertlen - 66) + 10);
  }
  else
    if (insertlen < 6210)
  {
    return 21u;
  }
  else
    if (insertlen < 22594)
  {
    return 22u;
  }
  else
  {
    return 23u;
  }
}


----------------------------
typedef struct PosData
{
  size_t pos;
  int distance_cache[4];
  float costdiff;
  float cost;
} PosData
----------------------------
None
----------------------------
***/


static size_t UpdateNodes(const size_t num_bytes, const size_t block_start, const size_t pos, const uint8_t *ringbuffer, const size_t ringbuffer_mask, const BrotliEncoderParams *params, const size_t max_backward_limit, const int *starting_dist_cache, const size_t num_matches, const BackwardMatch *matches, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t cur_ix = block_start + pos;
  const size_t cur_ix_masked = cur_ix & ringbuffer_mask;
  const size_t max_distance = brotli_min_size_t(cur_ix, max_backward_limit);
  const size_t dictionary_start = brotli_min_size_t(cur_ix + stream_offset, max_backward_limit);
  const size_t max_len = num_bytes - pos;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  const size_t max_iters = MaxZopfliCandidates(params);
  size_t min_len;
  size_t result = 0;
  size_t k;
  size_t gap = 0;
  EvaluateNode(block_start + stream_offset, pos, max_backward_limit, gap, starting_dist_cache, model, queue, nodes);
  {
    const PosData *posdata = StartPosQueueAt(queue, 0);
    float min_cost = (posdata->cost + ZopfliCostModelGetMinCostCmd(model)) + ZopfliCostModelGetLiteralCosts(model, posdata->pos, pos);
    min_len = ComputeMinimumCopyLength(min_cost, nodes, num_bytes, pos);
  }
  for (k = 0; (k < max_iters) && (k < StartPosQueueSize(queue)); k += 1)
  {
    helper_UpdateNodes_1(&result, pos, ringbuffer, ringbuffer_mask, params, num_matches, matches, model, queue, nodes, cur_ix, cur_ix_masked, max_distance, dictionary_start, max_len, max_zopfli_len, min_len, k, gap);
  }

  return result;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
static size_t ComputeMinimumCopyLength(const float start_cost, const ZopfliNode *nodes, const size_t num_bytes, const size_t pos)
{
  float min_cost = start_cost;
  size_t len = 2;
  size_t next_len_bucket = 4;
  size_t next_len_offset = 10;
  while (((pos + len) <= num_bytes) && (nodes[pos + len].u.cost <= min_cost))
  {
    len += 1;
    if (len == next_len_offset)
    {
      min_cost += 1.0f;
      next_len_offset += next_len_bucket;
      next_len_bucket *= 2;
    }
  }

  return len;
}


----------------------------
static size_t StartPosQueueSize(const StartPosQueue *self)
{
  return brotli_min_size_t(self->idx_, 8);
}


----------------------------
inline static float ZopfliCostModelGetMinCostCmd(const ZopfliCostModel *self)
{
  return self->min_cost_cmd_;
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
static const PosData *StartPosQueueAt(const StartPosQueue *self, size_t k)
{
  return &self->q_[(k - self->idx_) & 7];
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
static void EvaluateNode(const size_t block_start, const size_t pos, const size_t max_backward_limit, const size_t gap, const int *starting_dist_cache, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  float node_cost = nodes[pos].u.cost;
  nodes[pos].u.shortcut = ComputeDistanceShortcut(block_start, pos, max_backward_limit, gap, nodes);
  if (node_cost <= ZopfliCostModelGetLiteralCosts(model, 0, pos))
  {
    PosData posdata;
    posdata.pos = pos;
    posdata.cost = node_cost;
    posdata.costdiff = node_cost - ZopfliCostModelGetLiteralCosts(model, 0, pos);
    ComputeDistanceCache(pos, starting_dist_cache, nodes, posdata.distance_cache);
    StartPosQueuePush(queue, &posdata);
  }
}


----------------------------
inline static size_t MaxZopfliCandidates(const BrotliEncoderParams *params)
{
  return (params->quality <= 10) ? (1) : (5);
}


----------------------------
inline static float ZopfliCostModelGetLiteralCosts(const ZopfliCostModel *self, size_t from, size_t to)
{
  return self->literal_costs_[to] - self->literal_costs_[from];
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static size_t MaxZopfliLen(const BrotliEncoderParams *params)
{
  return (params->quality <= 10) ? (150) : (325);
}


----------------------------
void helper_UpdateNodes_1(size_t * const result_ref, const size_t pos, const uint8_t * const ringbuffer, const size_t ringbuffer_mask, const BrotliEncoderParams * const params, const size_t num_matches, const BackwardMatch * const matches, const ZopfliCostModel * const model, StartPosQueue * const queue, ZopfliNode * const nodes, const size_t cur_ix, const size_t cur_ix_masked, const size_t max_distance, const size_t dictionary_start, const size_t max_len, const size_t max_zopfli_len, size_t min_len, size_t k, size_t gap)
{
  size_t result = *result_ref;
  const PosData *posdata = StartPosQueueAt(queue, k);
  const size_t start = posdata->pos;
  const uint16_t inscode = GetInsertLengthCode(pos - start);
  const float start_costdiff = posdata->costdiff;
  const float base_cost = (start_costdiff + ((float) GetInsertExtra(inscode))) + ZopfliCostModelGetLiteralCosts(model, 0, pos);
  size_t best_len = min_len - 1;
  size_t j = 0;
  for (; (j < 16) && (best_len < max_len); j += 1)
  {
    helper_helper_UpdateNodes_1_2(&result, &best_len, pos, ringbuffer, ringbuffer_mask, model, nodes, cur_ix, cur_ix_masked, max_distance, dictionary_start, max_len, gap, posdata, start, inscode, base_cost, j);
  }

  if (k >= 2)
  {
    continue;
  }
  {
    helper_helper_UpdateNodes_1_1(&result, &j, pos, params, num_matches, matches, model, nodes, dictionary_start, max_zopfli_len, min_len, gap, start, inscode, base_cost);
  }
  *result_ref = result;
}


----------------------------
typedef struct PosData
{
  size_t pos;
  int distance_cache[4];
  float costdiff;
  float cost;
} PosData
----------------------------
None
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t']
void helper_BrotliZopfliComputeShortestPath_1(size_t * const i_ref, size_t num_bytes, size_t position, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, const int * const dist_cache, Hasher * const hasher, ZopfliNode * const nodes, const size_t stream_offset, const size_t max_backward_limit, const size_t max_zopfli_len, ZopfliCostModel model, StartPosQueue queue, BackwardMatch matches[2 * (128 + 64)], const size_t store_end, size_t gap, size_t lz_matches_offset)
{
  size_t i = *i_ref;
  const size_t pos = position + i;
  const size_t max_distance = brotli_min_size_t(pos, max_backward_limit);
  const size_t dictionary_start = brotli_min_size_t(pos + stream_offset, max_backward_limit);
  size_t skip;
  size_t num_matches;
  num_matches = FindAllMatchesH10(&hasher->privat._H10, &params->dictionary, ringbuffer, ringbuffer_mask, pos, num_bytes - i, max_distance, dictionary_start + gap, params, &matches[lz_matches_offset]);
  if ((num_matches > 0) && (BackwardMatchLength(&matches[num_matches - 1]) > max_zopfli_len))
  {
    matches[0] = matches[num_matches - 1];
    num_matches = 1;
  }
  skip = UpdateNodes(num_bytes, position, i, ringbuffer, ringbuffer_mask, params, max_backward_limit, dist_cache, num_matches, matches, &model, &queue, nodes);
  if (skip < 16384)
  {
    skip = 0;
  }
  if ((num_matches == 1) && (BackwardMatchLength(&matches[0]) > max_zopfli_len))
  {
    skip = brotli_max_size_t(BackwardMatchLength(&matches[0]), skip);
  }
  if (skip > 1)
  {
    StoreRangeH10(&hasher->privat._H10, ringbuffer, ringbuffer_mask, pos + 1, brotli_min_size_t(pos + skip, store_end));
    skip -= 1;
    while (skip)
    {
      i += 1;
      if (((i + HashTypeLengthH10()) - 1) >= num_bytes)
      {
        break;
      }
      EvaluateNode(position + stream_offset, i, max_backward_limit, gap, dist_cache, &model, &queue, nodes);
      skip -= 1;
    }

  }
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
inline static size_t FindAllMatchesH10(H10 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const BrotliEncoderParams *params, BackwardMatch *matches)
{
  unsigned int matches_idx = 0;
  BackwardMatch * const orig_matches = matches;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t best_len = 1;
  const size_t short_match_max_backward = (params->quality != 11) ? (16) : (64);
  size_t stop = cur_ix - short_match_max_backward;
  uint32_t dict_matches[37 + 1];
  size_t i;
  if (cur_ix < short_match_max_backward)
  {
    stop = 0;
  }
  for (i = cur_ix - 1; (i > stop) && (best_len <= 2); i -= 1)
  {
    helper_FindAllMatchesH10_2(&matches_idx, &best_len, data, ring_buffer_mask, cur_ix, max_length, max_backward, matches, cur_ix_masked, i);
  }

  if (best_len < max_length)
  {
    matches_idx = StoreAndFindMatchesH10(self, data, cur_ix, ring_buffer_mask, max_length, max_backward, &best_len, matches_idx);
  }
  for (i = 0; i <= 37; i += 1)
  {
    dict_matches[i] = kInvalidMatch;
  }

  {
    helper_FindAllMatchesH10_1(&matches_idx, dictionary, data, max_length, dictionary_distance, params, matches, cur_ix_masked, best_len, dict_matches);
  }
  return (size_t) ((&matches[matches_idx]) - orig_matches);
}


----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t BackwardMatchLength(const BackwardMatch *self)
{
  return self->length_and_code >> 5;
}


----------------------------
static size_t UpdateNodes(const size_t num_bytes, const size_t block_start, const size_t pos, const uint8_t *ringbuffer, const size_t ringbuffer_mask, const BrotliEncoderParams *params, const size_t max_backward_limit, const int *starting_dist_cache, const size_t num_matches, const BackwardMatch *matches, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t cur_ix = block_start + pos;
  const size_t cur_ix_masked = cur_ix & ringbuffer_mask;
  const size_t max_distance = brotli_min_size_t(cur_ix, max_backward_limit);
  const size_t dictionary_start = brotli_min_size_t(cur_ix + stream_offset, max_backward_limit);
  const size_t max_len = num_bytes - pos;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  const size_t max_iters = MaxZopfliCandidates(params);
  size_t min_len;
  size_t result = 0;
  size_t k;
  size_t gap = 0;
  EvaluateNode(block_start + stream_offset, pos, max_backward_limit, gap, starting_dist_cache, model, queue, nodes);
  {
    const PosData *posdata = StartPosQueueAt(queue, 0);
    float min_cost = (posdata->cost + ZopfliCostModelGetMinCostCmd(model)) + ZopfliCostModelGetLiteralCosts(model, posdata->pos, pos);
    min_len = ComputeMinimumCopyLength(min_cost, nodes, num_bytes, pos);
  }
  for (k = 0; (k < max_iters) && (k < StartPosQueueSize(queue)); k += 1)
  {
    helper_UpdateNodes_1(&result, pos, ringbuffer, ringbuffer_mask, params, num_matches, matches, model, queue, nodes, cur_ix, cur_ix_masked, max_distance, dictionary_start, max_len, max_zopfli_len, min_len, k, gap);
  }

  return result;
}


----------------------------
inline static size_t HashTypeLengthH10(void)
{
  return 4;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static void StoreRangeH10(H10 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i = ix_start;
  size_t j = ix_start;
  if ((ix_start + 63) <= ix_end)
  {
    i = ix_end - 63;
  }
  if ((ix_start + 512) <= i)
  {
    for (; j < i; j += 8)
    {
      StoreH10(self, data, mask, j);
    }

  }
  for (; i < ix_end; i += 1)
  {
    StoreH10(self, data, mask, i);
  }

}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
static void EvaluateNode(const size_t block_start, const size_t pos, const size_t max_backward_limit, const size_t gap, const int *starting_dist_cache, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  float node_cost = nodes[pos].u.cost;
  nodes[pos].u.shortcut = ComputeDistanceShortcut(block_start, pos, max_backward_limit, gap, nodes);
  if (node_cost <= ZopfliCostModelGetLiteralCosts(model, 0, pos))
  {
    PosData posdata;
    posdata.pos = pos;
    posdata.cost = node_cost;
    posdata.costdiff = node_cost - ZopfliCostModelGetLiteralCosts(model, 0, pos);
    ComputeDistanceCache(pos, starting_dist_cache, nodes, posdata.distance_cache);
    StartPosQueuePush(queue, &posdata);
  }
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
None
----------------------------
***/


static void InitZopfliCostModel(MemoryManager *m, ZopfliCostModel *self, const BrotliDistanceParams *dist, size_t num_bytes)
{
  self->num_bytes_ = num_bytes;
  self->literal_costs_ = ((num_bytes + 2) > 0) ? ((float *) BrotliAllocate(m, (num_bytes + 2) * (sizeof(float)))) : (0);
  self->cost_dist_ = (dist->alphabet_size_limit > 0) ? ((float *) BrotliAllocate(m, dist->alphabet_size_limit * (sizeof(float)))) : (0);
  self->distance_histogram_size = dist->alphabet_size_limit;
  if (!(!0))
  {
    return;
  }
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
typedef struct BrotliDistanceParams
{
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t alphabet_size_max;
  uint32_t alphabet_size_limit;
  size_t max_distance;
} BrotliDistanceParams
----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
***/


size_t BrotliZopfliComputeShortestPath(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, const int *dist_cache, Hasher *hasher, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  ZopfliCostModel model;
  StartPosQueue queue;
  BackwardMatch matches[2 * (128 + 64)];
  const size_t store_end = (num_bytes >= StoreLookaheadH10()) ? (((position + num_bytes) - StoreLookaheadH10()) + 1) : (position);
  size_t i;
  size_t gap = 0;
  size_t lz_matches_offset = 0;
  (void) literal_context_lut;
  nodes[0].length = 0;
  nodes[0].u.cost = 0;
  InitZopfliCostModel(m, &model, &params->dist, num_bytes);
  if (!(!0))
  {
    return 0;
  }
  ZopfliCostModelSetFromLiteralCosts(&model, position, ringbuffer, ringbuffer_mask);
  InitStartPosQueue(&queue);
  for (i = 0; ((i + HashTypeLengthH10()) - 1) < num_bytes; i += 1)
  {
    helper_BrotliZopfliComputeShortestPath_1(&i, num_bytes, position, ringbuffer, ringbuffer_mask, params, dist_cache, hasher, nodes, stream_offset, max_backward_limit, max_zopfli_len, model, queue, matches, store_end, gap, lz_matches_offset);
  }

  CleanupZopfliCostModel(m, &model);
  return ComputeShortestPathFromNodes(num_bytes, nodes);
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
static void CleanupZopfliCostModel(MemoryManager *m, ZopfliCostModel *self)
{
  {
    BrotliFree(m, self->literal_costs_);
    self->literal_costs_ = 0;
  }
  ;
  {
    BrotliFree(m, self->cost_dist_);
    self->cost_dist_ = 0;
  }
  ;
}


----------------------------
static void ZopfliCostModelSetFromLiteralCosts(ZopfliCostModel *self, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  float *literal_costs = self->literal_costs_;
  float literal_carry = 0.0;
  float *cost_dist = self->cost_dist_;
  float *cost_cmd = self->cost_cmd_;
  size_t num_bytes = self->num_bytes_;
  size_t i;
  BrotliEstimateBitCostsForLiterals(position, num_bytes, ringbuffer_mask, ringbuffer, &literal_costs[1]);
  literal_costs[0] = 0.0;
  for (i = 0; i < num_bytes; i += 1)
  {
    literal_carry += literal_costs[i + 1];
    literal_costs[i + 1] = literal_costs[i] + literal_carry;
    literal_carry -= literal_costs[i + 1] - literal_costs[i];
  }

  for (i = 0; i < 704; i += 1)
  {
    cost_cmd[i] = (float) FastLog2(11 + ((uint32_t) i));
  }

  for (i = 0; i < self->distance_histogram_size; i += 1)
  {
    cost_dist[i] = (float) FastLog2(20 + ((uint32_t) i));
  }

  self->min_cost_cmd_ = (float) FastLog2(11);
}


----------------------------
void helper_BrotliZopfliComputeShortestPath_1(size_t * const i_ref, size_t num_bytes, size_t position, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, const int * const dist_cache, Hasher * const hasher, ZopfliNode * const nodes, const size_t stream_offset, const size_t max_backward_limit, const size_t max_zopfli_len, ZopfliCostModel model, StartPosQueue queue, BackwardMatch matches[2 * (128 + 64)], const size_t store_end, size_t gap, size_t lz_matches_offset)
{
  size_t i = *i_ref;
  const size_t pos = position + i;
  const size_t max_distance = brotli_min_size_t(pos, max_backward_limit);
  const size_t dictionary_start = brotli_min_size_t(pos + stream_offset, max_backward_limit);
  size_t skip;
  size_t num_matches;
  num_matches = FindAllMatchesH10(&hasher->privat._H10, &params->dictionary, ringbuffer, ringbuffer_mask, pos, num_bytes - i, max_distance, dictionary_start + gap, params, &matches[lz_matches_offset]);
  if ((num_matches > 0) && (BackwardMatchLength(&matches[num_matches - 1]) > max_zopfli_len))
  {
    matches[0] = matches[num_matches - 1];
    num_matches = 1;
  }
  skip = UpdateNodes(num_bytes, position, i, ringbuffer, ringbuffer_mask, params, max_backward_limit, dist_cache, num_matches, matches, &model, &queue, nodes);
  if (skip < 16384)
  {
    skip = 0;
  }
  if ((num_matches == 1) && (BackwardMatchLength(&matches[0]) > max_zopfli_len))
  {
    skip = brotli_max_size_t(BackwardMatchLength(&matches[0]), skip);
  }
  if (skip > 1)
  {
    StoreRangeH10(&hasher->privat._H10, ringbuffer, ringbuffer_mask, pos + 1, brotli_min_size_t(pos + skip, store_end));
    skip -= 1;
    while (skip)
    {
      i += 1;
      if (((i + HashTypeLengthH10()) - 1) >= num_bytes)
      {
        break;
      }
      EvaluateNode(position + stream_offset, i, max_backward_limit, gap, dist_cache, &model, &queue, nodes);
      skip -= 1;
    }

  }
  *i_ref = i;
}


----------------------------
inline static size_t HashTypeLengthH10(void)
{
  return 4;
}


----------------------------
inline static void InitStartPosQueue(StartPosQueue *self)
{
  self->idx_ = 0;
}


----------------------------
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static size_t MaxZopfliLen(const BrotliEncoderParams *params)
{
  return (params->quality <= 10) ? (150) : (325);
}


----------------------------
static size_t ComputeShortestPathFromNodes(size_t num_bytes, ZopfliNode *nodes)
{
  size_t index = num_bytes;
  size_t num_commands = 0;
  index -= 1;
  index -= 1;
  index -= 1;
  index -= 1;
  while (((nodes[index].dcode_insert_length & 0x7FFFFFF) == 0) && (nodes[index].length == 1))
    --index;

  nodes[index].u.next = ~((uint32_t) 0);
  while (index != 0)
  {
    size_t len = ZopfliNodeCommandLength(&nodes[index]);
    index -= len;
    nodes[index].u.next = (uint32_t) len;
    num_commands++;
  }

  return num_commands;
}


----------------------------
inline static size_t StoreLookaheadH10(void)
{
  return 128;
}


----------------------------
static void InitZopfliCostModel(MemoryManager *m, ZopfliCostModel *self, const BrotliDistanceParams *dist, size_t num_bytes)
{
  self->num_bytes_ = num_bytes;
  self->literal_costs_ = ((num_bytes + 2) > 0) ? ((float *) BrotliAllocate(m, (num_bytes + 2) * (sizeof(float)))) : (0);
  self->cost_dist_ = (dist->alphabet_size_limit > 0) ? ((float *) BrotliAllocate(m, dist->alphabet_size_limit * (sizeof(float)))) : (0);
  self->distance_histogram_size = dist->alphabet_size_limit;
  if (!(!0))
  {
    return;
  }
}


----------------------------
None
----------------------------
***/


void BrotliCreateZopfliBackwardReferences(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  ZopfliNode *nodes = ((num_bytes + 1) > 0) ? ((ZopfliNode *) BrotliAllocate(m, (num_bytes + 1) * (sizeof(ZopfliNode)))) : (0);
  unsigned int nodes_idx = 0;
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  BrotliInitZopfliNodes(nodes, num_bytes + 1);
  *num_commands += BrotliZopfliComputeShortestPath(m, num_bytes, position, ringbuffer, ringbuffer_mask, literal_context_lut, params, dist_cache, hasher, nodes);
  if (!(!0))
  {
    return;
  }
  BrotliZopfliCreateCommands(num_bytes, position, nodes, dist_cache, last_insert_len, params, commands, num_literals);
  {
    BrotliFree(m, nodes);
    nodes_idx = 0;
  }
  ;
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
void BrotliInitZopfliNodes(ZopfliNode *array, size_t length)
{
  ZopfliNode stub;
  size_t i;
  stub.length = 1;
  stub.distance = 0;
  stub.dcode_insert_length = 0;
  stub.u.cost = kInfinity;
  for (i = 0; i < length; i += 1)
    array[i] = stub;

}


----------------------------
void BrotliZopfliCreateCommands(const size_t num_bytes, const size_t block_start, const ZopfliNode *nodes, int *dist_cache, size_t *last_insert_len, const BrotliEncoderParams *params, Command *commands, size_t *num_literals)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  size_t pos = 0;
  uint32_t offset = nodes[0].u.next;
  size_t i;
  size_t gap = 0;
  for (i = 0; offset != (~((uint32_t) 0)); i += 1)
  {
    const ZopfliNode *next = &nodes[pos + offset];
    size_t copy_length = ZopfliNodeCopyLength(next);
    size_t insert_length = next->dcode_insert_length & 0x7FFFFFF;
    pos += insert_length;
    offset = next->u.next;
    if (i == 0)
    {
      insert_length += *last_insert_len;
      *last_insert_len = 0;
    }
    {
      size_t distance = ZopfliNodeCopyDistance(next);
      size_t len_code = ZopfliNodeLengthCode(next);
      size_t dictionary_start = brotli_min_size_t((block_start + pos) + stream_offset, max_backward_limit);
      int is_dictionary = (!(!(distance > (dictionary_start + gap)))) ? (1) : (0);
      size_t dist_code = ZopfliNodeDistanceCode(next);
      InitCommand(&commands[i], &params->dist, insert_length, copy_length, ((int) len_code) - ((int) copy_length), dist_code);
      if ((!is_dictionary) && (dist_code > 0))
      {
        dist_cache[3] = dist_cache[2];
        dist_cache[2] = dist_cache[1];
        dist_cache[1] = dist_cache[0];
        dist_cache[0] = (int) distance;
      }
    }
    *num_literals += insert_length;
    pos += copy_length;
  }

  *last_insert_len += num_bytes - pos;
}


----------------------------
size_t BrotliZopfliComputeShortestPath(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, const int *dist_cache, Hasher *hasher, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  ZopfliCostModel model;
  StartPosQueue queue;
  BackwardMatch matches[2 * (128 + 64)];
  const size_t store_end = (num_bytes >= StoreLookaheadH10()) ? (((position + num_bytes) - StoreLookaheadH10()) + 1) : (position);
  size_t i;
  size_t gap = 0;
  size_t lz_matches_offset = 0;
  (void) literal_context_lut;
  nodes[0].length = 0;
  nodes[0].u.cost = 0;
  InitZopfliCostModel(m, &model, &params->dist, num_bytes);
  if (!(!0))
  {
    return 0;
  }
  ZopfliCostModelSetFromLiteralCosts(&model, position, ringbuffer, ringbuffer_mask);
  InitStartPosQueue(&queue);
  for (i = 0; ((i + HashTypeLengthH10()) - 1) < num_bytes; i += 1)
  {
    helper_BrotliZopfliComputeShortestPath_1(&i, num_bytes, position, ringbuffer, ringbuffer_mask, params, dist_cache, hasher, nodes, stream_offset, max_backward_limit, max_zopfli_len, model, queue, matches, store_end, gap, lz_matches_offset);
  }

  CleanupZopfliCostModel(m, &model);
  return ComputeShortestPathFromNodes(num_bytes, nodes);
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
typedef const uint8_t *ContextLut
----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
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
None
----------------------------
***/


static size_t ZopfliIterate(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams *params, const size_t gap, const int *dist_cache, const ZopfliCostModel *model, const uint32_t *num_matches, const BackwardMatch *matches, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  StartPosQueue queue;
  size_t cur_match_pos = 0;
  size_t i;
  nodes[0].length = 0;
  nodes[0].u.cost = 0;
  InitStartPosQueue(&queue);
  for (i = 0; (i + 3) < num_bytes; i += 1)
  {
    size_t skip = UpdateNodes(num_bytes, position, i, ringbuffer, ringbuffer_mask, params, max_backward_limit, dist_cache, num_matches[i], &matches[cur_match_pos], model, &queue, nodes);
    if (skip < 16384)
    {
      skip = 0;
    }
    cur_match_pos += num_matches[i];
    if ((num_matches[i] == 1) && (BackwardMatchLength(&matches[cur_match_pos - 1]) > max_zopfli_len))
    {
      skip = brotli_max_size_t(BackwardMatchLength(&matches[cur_match_pos - 1]), skip);
    }
    if (skip > 1)
    {
      skip -= 1;
      while (skip)
      {
        i += 1;
        if ((i + 3) >= num_bytes)
        {
          break;
        }
        EvaluateNode(position + stream_offset, i, max_backward_limit, gap, dist_cache, model, &queue, nodes);
        cur_match_pos += num_matches[i];
        skip -= 1;
      }

    }
  }

  return ComputeShortestPathFromNodes(num_bytes, nodes);
}


/*** DEPENDENCIES:
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
typedef struct StartPosQueue
{
  PosData q_[8];
  size_t idx_;
} StartPosQueue
----------------------------
inline static size_t BackwardMatchLength(const BackwardMatch *self)
{
  return self->length_and_code >> 5;
}


----------------------------
static size_t UpdateNodes(const size_t num_bytes, const size_t block_start, const size_t pos, const uint8_t *ringbuffer, const size_t ringbuffer_mask, const BrotliEncoderParams *params, const size_t max_backward_limit, const int *starting_dist_cache, const size_t num_matches, const BackwardMatch *matches, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t cur_ix = block_start + pos;
  const size_t cur_ix_masked = cur_ix & ringbuffer_mask;
  const size_t max_distance = brotli_min_size_t(cur_ix, max_backward_limit);
  const size_t dictionary_start = brotli_min_size_t(cur_ix + stream_offset, max_backward_limit);
  const size_t max_len = num_bytes - pos;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  const size_t max_iters = MaxZopfliCandidates(params);
  size_t min_len;
  size_t result = 0;
  size_t k;
  size_t gap = 0;
  EvaluateNode(block_start + stream_offset, pos, max_backward_limit, gap, starting_dist_cache, model, queue, nodes);
  {
    const PosData *posdata = StartPosQueueAt(queue, 0);
    float min_cost = (posdata->cost + ZopfliCostModelGetMinCostCmd(model)) + ZopfliCostModelGetLiteralCosts(model, posdata->pos, pos);
    min_len = ComputeMinimumCopyLength(min_cost, nodes, num_bytes, pos);
  }
  for (k = 0; (k < max_iters) && (k < StartPosQueueSize(queue)); k += 1)
  {
    helper_UpdateNodes_1(&result, pos, ringbuffer, ringbuffer_mask, params, num_matches, matches, model, queue, nodes, cur_ix, cur_ix_masked, max_distance, dictionary_start, max_len, max_zopfli_len, min_len, k, gap);
  }

  return result;
}


----------------------------
inline static void InitStartPosQueue(StartPosQueue *self)
{
  self->idx_ = 0;
}


----------------------------
inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
static void EvaluateNode(const size_t block_start, const size_t pos, const size_t max_backward_limit, const size_t gap, const int *starting_dist_cache, const ZopfliCostModel *model, StartPosQueue *queue, ZopfliNode *nodes)
{
  float node_cost = nodes[pos].u.cost;
  nodes[pos].u.shortcut = ComputeDistanceShortcut(block_start, pos, max_backward_limit, gap, nodes);
  if (node_cost <= ZopfliCostModelGetLiteralCosts(model, 0, pos))
  {
    PosData posdata;
    posdata.pos = pos;
    posdata.cost = node_cost;
    posdata.costdiff = node_cost - ZopfliCostModelGetLiteralCosts(model, 0, pos);
    ComputeDistanceCache(pos, starting_dist_cache, nodes, posdata.distance_cache);
    StartPosQueuePush(queue, &posdata);
  }
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
inline static size_t MaxZopfliLen(const BrotliEncoderParams *params)
{
  return (params->quality <= 10) ? (150) : (325);
}


----------------------------
static size_t ComputeShortestPathFromNodes(size_t num_bytes, ZopfliNode *nodes)
{
  size_t index = num_bytes;
  size_t num_commands = 0;
  index -= 1;
  index -= 1;
  index -= 1;
  index -= 1;
  while (((nodes[index].dcode_insert_length & 0x7FFFFFF) == 0) && (nodes[index].length == 1))
    --index;

  nodes[index].u.next = ~((uint32_t) 0);
  while (index != 0)
  {
    size_t len = ZopfliNodeCommandLength(&nodes[index]);
    index -= len;
    nodes[index].u.next = (uint32_t) len;
    num_commands++;
  }

  return num_commands;
}


----------------------------
None
----------------------------
***/


// hint:  ['matches_size_ref is a mutable refrence to size_t', 'matches_idx_ref is a mutable refrence to unsigned int']
void helper_helper_BrotliCreateHqZopfliBackwardReferences_1_1(size_t * const matches_size_ref, unsigned int * const matches_idx_ref, MemoryManager * const m, BackwardMatch * const matches, size_t shadow_matches, size_t cur_match_pos)
{
  size_t matches_size = *matches_size_ref;
  unsigned int matches_idx = *matches_idx_ref;
  if (matches_size < ((cur_match_pos + 128) + shadow_matches))
  {
    size_t _new_size = (matches_size == 0) ? ((cur_match_pos + 128) + shadow_matches) : (matches_size);
    BackwardMatch *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < ((cur_match_pos + 128) + shadow_matches))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((BackwardMatch *) BrotliAllocate(m, _new_size * (sizeof(BackwardMatch)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (matches_size != 0))
    {
      memcpy(new_array, matches, matches_size * (sizeof(BackwardMatch)));
    }
    {
      BrotliFree(m, matches);
      matches_idx = 0;
    }
    ;
    matches_idx = &new_array[new_array_idx];
    matches_size = _new_size;
  }
  *matches_size_ref = matches_size;
  *matches_idx_ref = matches_idx;
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
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
***/


// hint:  ['num_matches_idx_ref is a mutable refrence to unsigned int', 'matches_size_ref is a mutable refrence to size_t', 'cur_match_pos_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t', 'matches_idx_ref is a mutable refrence to unsigned int']
void helper_BrotliCreateHqZopfliBackwardReferences_1(unsigned int * const num_matches_idx_ref, size_t * const matches_size_ref, size_t * const cur_match_pos_ref, size_t * const i_ref, unsigned int * const matches_idx_ref, MemoryManager * const m, size_t num_bytes, size_t position, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, Hasher * const hasher, const size_t stream_offset, const size_t max_backward_limit, uint32_t * const num_matches, const size_t store_end, BackwardMatch * const matches, size_t gap, size_t shadow_matches)
{
  unsigned int num_matches_idx = *num_matches_idx_ref;
  size_t matches_size = *matches_size_ref;
  size_t cur_match_pos = *cur_match_pos_ref;
  size_t i = *i_ref;
  unsigned int matches_idx = *matches_idx_ref;
  const size_t pos = position + i;
  size_t max_distance = brotli_min_size_t(pos, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(pos + stream_offset, max_backward_limit);
  size_t max_length = num_bytes - i;
  size_t num_found_matches;
  size_t cur_match_end;
  size_t j;
  {
    helper_helper_BrotliCreateHqZopfliBackwardReferences_1_1(&matches_size, &matches_idx, m, matches, shadow_matches, cur_match_pos);
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_found_matches = FindAllMatchesH10(&hasher->privat._H10, &params->dictionary, ringbuffer, ringbuffer_mask, pos, max_length, max_distance, dictionary_start + gap, params, &matches[(cur_match_pos + shadow_matches) + matches_idx]);
  cur_match_end = cur_match_pos + num_found_matches;
  for (j = cur_match_pos; (j + 1) < cur_match_end; j += 1)
  {
    ;
  }

  num_matches[i + num_matches_idx] = (uint32_t) num_found_matches;
  if (num_found_matches > 0)
  {
    const size_t match_len = BackwardMatchLength(&matches[(cur_match_end - 1) + matches_idx]);
    if (match_len > 325)
    {
      const size_t skip = match_len - 1;
      matches[cur_match_pos + matches_idx] = matches[(cur_match_end - 1) + matches_idx];
      cur_match_pos += 1;
      num_matches[i + num_matches_idx] = 1;
      StoreRangeH10(&hasher->privat._H10, ringbuffer, ringbuffer_mask, pos + 1, brotli_min_size_t(pos + match_len, store_end));
      memset(&num_matches[(i + 1) + num_matches_idx], 0, skip * (sizeof(num_matches[0 + num_matches_idx])));
      i += skip;
    }
    else
    {
      cur_match_pos = cur_match_end;
    }
  }
  *num_matches_idx_ref = num_matches_idx;
  *matches_size_ref = matches_size;
  *cur_match_pos_ref = cur_match_pos;
  *i_ref = i;
  *matches_idx_ref = matches_idx;
}


/*** DEPENDENCIES:
inline static size_t FindAllMatchesH10(H10 * restrict self, const BrotliEncoderDictionary *dictionary, const uint8_t * restrict data, const size_t ring_buffer_mask, const size_t cur_ix, const size_t max_length, const size_t max_backward, const size_t dictionary_distance, const BrotliEncoderParams *params, BackwardMatch *matches)
{
  unsigned int matches_idx = 0;
  BackwardMatch * const orig_matches = matches;
  const size_t cur_ix_masked = cur_ix & ring_buffer_mask;
  size_t best_len = 1;
  const size_t short_match_max_backward = (params->quality != 11) ? (16) : (64);
  size_t stop = cur_ix - short_match_max_backward;
  uint32_t dict_matches[37 + 1];
  size_t i;
  if (cur_ix < short_match_max_backward)
  {
    stop = 0;
  }
  for (i = cur_ix - 1; (i > stop) && (best_len <= 2); i -= 1)
  {
    helper_FindAllMatchesH10_2(&matches_idx, &best_len, data, ring_buffer_mask, cur_ix, max_length, max_backward, matches, cur_ix_masked, i);
  }

  if (best_len < max_length)
  {
    matches_idx = StoreAndFindMatchesH10(self, data, cur_ix, ring_buffer_mask, max_length, max_backward, &best_len, matches_idx);
  }
  for (i = 0; i <= 37; i += 1)
  {
    dict_matches[i] = kInvalidMatch;
  }

  {
    helper_FindAllMatchesH10_1(&matches_idx, dictionary, data, max_length, dictionary_distance, params, matches, cur_ix_masked, best_len, dict_matches);
  }
  return (size_t) ((&matches[matches_idx]) - orig_matches);
}


----------------------------
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
----------------------------
inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
inline static size_t BackwardMatchLength(const BackwardMatch *self)
{
  return self->length_and_code >> 5;
}


----------------------------
inline static void StoreRangeH10(H10 * restrict self, const uint8_t * restrict data, const size_t mask, const size_t ix_start, const size_t ix_end)
{
  size_t i = ix_start;
  size_t j = ix_start;
  if ((ix_start + 63) <= ix_end)
  {
    i = ix_end - 63;
  }
  if ((ix_start + 512) <= i)
  {
    for (; j < i; j += 8)
    {
      StoreH10(self, data, mask, j);
    }

  }
  for (; i < ix_end; i += 1)
  {
    StoreH10(self, data, mask, i);
  }

}


----------------------------
void helper_helper_BrotliCreateHqZopfliBackwardReferences_1_1(size_t * const matches_size_ref, unsigned int * const matches_idx_ref, MemoryManager * const m, BackwardMatch * const matches, size_t shadow_matches, size_t cur_match_pos)
{
  size_t matches_size = *matches_size_ref;
  unsigned int matches_idx = *matches_idx_ref;
  if (matches_size < ((cur_match_pos + 128) + shadow_matches))
  {
    size_t _new_size = (matches_size == 0) ? ((cur_match_pos + 128) + shadow_matches) : (matches_size);
    BackwardMatch *new_array;
    unsigned int new_array_idx = 0;
    while (_new_size < ((cur_match_pos + 128) + shadow_matches))
      _new_size *= 2;

    new_array_idx = (_new_size > 0) ? ((BackwardMatch *) BrotliAllocate(m, _new_size * (sizeof(BackwardMatch)))) : (0);
    if (((!(!(!0))) && (!(!(!0)))) && (matches_size != 0))
    {
      memcpy(new_array, matches, matches_size * (sizeof(BackwardMatch)));
    }
    {
      BrotliFree(m, matches);
      matches_idx = 0;
    }
    ;
    matches_idx = &new_array[new_array_idx];
    matches_size = _new_size;
  }
  *matches_size_ref = matches_size;
  *matches_idx_ref = matches_idx;
}


----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
None
----------------------------
***/


static void ZopfliCostModelSetFromCommands(ZopfliCostModel *self, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, const Command *commands, size_t num_commands, size_t last_insert_len)
{
  uint32_t histogram_literal[256];
  uint32_t histogram_cmd[704];
  uint32_t histogram_dist[544];
  float cost_literal[256];
  size_t pos = position - last_insert_len;
  float min_cost_cmd = kInfinity;
  size_t i;
  float *cost_cmd = self->cost_cmd_;
  memset(histogram_literal, 0, sizeof(histogram_literal));
  memset(histogram_cmd, 0, sizeof(histogram_cmd));
  memset(histogram_dist, 0, sizeof(histogram_dist));
  for (i = 0; i < num_commands; i += 1)
  {
    helper_ZopfliCostModelSetFromCommands_1(&ringbuffer_mask, &pos, ringbuffer, commands, histogram_literal, histogram_cmd, histogram_dist, i);
  }

  SetCost(histogram_literal, 256, 1, cost_literal);
  SetCost(histogram_cmd, 704, 0, cost_cmd);
  SetCost(histogram_dist, self->distance_histogram_size, 0, self->cost_dist_);
  for (i = 0; i < 704; i += 1)
  {
    min_cost_cmd = brotli_min_float(min_cost_cmd, cost_cmd[i]);
  }

  self->min_cost_cmd_ = min_cost_cmd;
  {
    float *literal_costs = self->literal_costs_;
    float literal_carry = 0.0;
    size_t num_bytes = self->num_bytes_;
    literal_costs[0] = 0.0;
    for (i = 0; i < num_bytes; i += 1)
    {
      literal_carry += cost_literal[ringbuffer[(position + i) & ringbuffer_mask]];
      literal_costs[i + 1] = literal_costs[i] + literal_carry;
      literal_carry -= literal_costs[i + 1] - literal_costs[i];
    }

  }
}


/*** DEPENDENCIES:
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
static const float kInfinity = 1.7e38f
----------------------------
void helper_ZopfliCostModelSetFromCommands_1(size_t * const ringbuffer_mask_ref, size_t * const pos_ref, const uint8_t * const ringbuffer, const Command * const commands, uint32_t histogram_literal[256], uint32_t histogram_cmd[704], uint32_t histogram_dist[544], size_t i)
{
  size_t ringbuffer_mask = *ringbuffer_mask_ref;
  size_t pos = *pos_ref;
  size_t inslength = commands[i].insert_len_;
  size_t copylength = CommandCopyLen(&commands[i]);
  size_t distcode = commands[i].dist_prefix_ & 0x3FF;
  size_t cmdcode = commands[i].cmd_prefix_;
  size_t j;
  histogram_cmd[cmdcode] += 1;
  if (cmdcode >= 128)
  {
    histogram_dist[distcode] += 1;
  }
  for (j = 0; j < inslength; j += 1)
  {
    histogram_literal[ringbuffer[(pos + j) & ringbuffer_mask]] += 1;
  }

  pos += inslength + copylength;
  *ringbuffer_mask_ref = ringbuffer_mask;
  *pos_ref = pos;
}


----------------------------
inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
static void SetCost(const uint32_t *histogram, size_t histogram_size, int literal_histogram, float *cost)
{
  size_t sum = 0;
  size_t missing_symbol_sum;
  float log2sum;
  float missing_symbol_cost;
  size_t i;
  for (i = 0; i < histogram_size; i += 1)
  {
    sum += histogram[i];
  }

  log2sum = (float) FastLog2(sum);
  missing_symbol_sum = sum;
  if (!literal_histogram)
  {
    for (i = 0; i < histogram_size; i += 1)
    {
      if (histogram[i] == 0)
      {
        missing_symbol_sum += 1;
      }
    }

  }
  missing_symbol_cost = ((float) FastLog2(missing_symbol_sum)) + 2;
  for (i = 0; i < histogram_size; i += 1)
  {
    if (histogram[i] == 0)
    {
      cost[i] = missing_symbol_cost;
      continue;
    }
    cost[i] = log2sum - ((float) FastLog2(histogram[i]));
    if (cost[i] < 1)
    {
      cost[i] = 1;
    }
  }

}


----------------------------
***/


void BrotliCreateHqZopfliBackwardReferences(MemoryManager *m, size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, ContextLut literal_context_lut, const BrotliEncoderParams *params, Hasher *hasher, int *dist_cache, size_t *last_insert_len, Command *commands, size_t *num_commands, size_t *num_literals)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  uint32_t *num_matches = (num_bytes > 0) ? ((uint32_t *) BrotliAllocate(m, num_bytes * (sizeof(uint32_t)))) : (0);
  unsigned int num_matches_idx = 0;
  size_t matches_size = 4 * num_bytes;
  const size_t store_end = (num_bytes >= StoreLookaheadH10()) ? (((position + num_bytes) - StoreLookaheadH10()) + 1) : (position);
  size_t cur_match_pos = 0;
  size_t i;
  size_t orig_num_literals;
  size_t orig_last_insert_len;
  int orig_dist_cache[4];
  size_t orig_num_commands;
  ZopfliCostModel model;
  ZopfliNode *nodes;
  unsigned int nodes_idx = 0;
  BackwardMatch *matches = (matches_size > 0) ? ((BackwardMatch *) BrotliAllocate(m, matches_size * (sizeof(BackwardMatch)))) : (0);
  unsigned int matches_idx = 0;
  size_t gap = 0;
  size_t shadow_matches = 0;
  (void) literal_context_lut;
  if (((!(!0)) || (!(!0))) || (!(!0)))
  {
    return;
  }
  for (i = 0; ((i + HashTypeLengthH10()) - 1) < num_bytes; i += 1)
  {
    helper_BrotliCreateHqZopfliBackwardReferences_1(&num_matches_idx, &matches_size, &cur_match_pos, &i, &matches_idx, m, num_bytes, position, ringbuffer, ringbuffer_mask, params, hasher, stream_offset, max_backward_limit, num_matches, store_end, matches, gap, shadow_matches);
  }

  orig_num_literals = *num_literals;
  orig_last_insert_len = *last_insert_len;
  memcpy(orig_dist_cache, dist_cache, 4 * (sizeof(dist_cache[0])));
  orig_num_commands = *num_commands;
  nodes_idx = ((num_bytes + 1) > 0) ? ((ZopfliNode *) BrotliAllocate(m, (num_bytes + 1) * (sizeof(ZopfliNode)))) : (0);
  if ((!(!0)) || (!(!0)))
  {
    return;
  }
  InitZopfliCostModel(m, &model, &params->dist, num_bytes);
  if (!(!0))
  {
    return;
  }
  for (i = 0; i < 2; i += 1)
  {
    BrotliInitZopfliNodes(nodes, num_bytes + 1);
    if (i == 0)
    {
      ZopfliCostModelSetFromLiteralCosts(&model, position, ringbuffer, ringbuffer_mask);
    }
    else
    {
      ZopfliCostModelSetFromCommands(&model, position, ringbuffer, ringbuffer_mask, commands, (*num_commands) - orig_num_commands, orig_last_insert_len);
    }
    *num_commands = orig_num_commands;
    *num_literals = orig_num_literals;
    *last_insert_len = orig_last_insert_len;
    memcpy(dist_cache, orig_dist_cache, 4 * (sizeof(dist_cache[0])));
    *num_commands += ZopfliIterate(num_bytes, position, ringbuffer, ringbuffer_mask, params, gap, dist_cache, &model, num_matches, matches, nodes);
    BrotliZopfliCreateCommands(num_bytes, position, nodes, dist_cache, last_insert_len, params, commands, num_literals);
  }

  CleanupZopfliCostModel(m, &model);
  {
    BrotliFree(m, nodes);
    nodes_idx = 0;
  }
  ;
  {
    BrotliFree(m, matches);
    matches_idx = 0;
  }
  ;
  {
    BrotliFree(m, num_matches);
    num_matches_idx = 0;
  }
  ;
}


/*** DEPENDENCIES:
void BrotliInitZopfliNodes(ZopfliNode *array, size_t length)
{
  ZopfliNode stub;
  size_t i;
  stub.length = 1;
  stub.distance = 0;
  stub.dcode_insert_length = 0;
  stub.u.cost = kInfinity;
  for (i = 0; i < length; i += 1)
    array[i] = stub;

}


----------------------------
void BrotliZopfliCreateCommands(const size_t num_bytes, const size_t block_start, const ZopfliNode *nodes, int *dist_cache, size_t *last_insert_len, const BrotliEncoderParams *params, Command *commands, size_t *num_literals)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  size_t pos = 0;
  uint32_t offset = nodes[0].u.next;
  size_t i;
  size_t gap = 0;
  for (i = 0; offset != (~((uint32_t) 0)); i += 1)
  {
    const ZopfliNode *next = &nodes[pos + offset];
    size_t copy_length = ZopfliNodeCopyLength(next);
    size_t insert_length = next->dcode_insert_length & 0x7FFFFFF;
    pos += insert_length;
    offset = next->u.next;
    if (i == 0)
    {
      insert_length += *last_insert_len;
      *last_insert_len = 0;
    }
    {
      size_t distance = ZopfliNodeCopyDistance(next);
      size_t len_code = ZopfliNodeLengthCode(next);
      size_t dictionary_start = brotli_min_size_t((block_start + pos) + stream_offset, max_backward_limit);
      int is_dictionary = (!(!(distance > (dictionary_start + gap)))) ? (1) : (0);
      size_t dist_code = ZopfliNodeDistanceCode(next);
      InitCommand(&commands[i], &params->dist, insert_length, copy_length, ((int) len_code) - ((int) copy_length), dist_code);
      if ((!is_dictionary) && (dist_code > 0))
      {
        dist_cache[3] = dist_cache[2];
        dist_cache[2] = dist_cache[1];
        dist_cache[1] = dist_cache[0];
        dist_cache[0] = (int) distance;
      }
    }
    *num_literals += insert_length;
    pos += copy_length;
  }

  *last_insert_len += num_bytes - pos;
}


----------------------------
typedef const uint8_t *ContextLut
----------------------------
static size_t ZopfliIterate(size_t num_bytes, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams *params, const size_t gap, const int *dist_cache, const ZopfliCostModel *model, const uint32_t *num_matches, const BackwardMatch *matches, ZopfliNode *nodes)
{
  const size_t stream_offset = params->stream_offset;
  const size_t max_backward_limit = (((size_t) 1) << params->lgwin) - 16;
  const size_t max_zopfli_len = MaxZopfliLen(params);
  StartPosQueue queue;
  size_t cur_match_pos = 0;
  size_t i;
  nodes[0].length = 0;
  nodes[0].u.cost = 0;
  InitStartPosQueue(&queue);
  for (i = 0; (i + 3) < num_bytes; i += 1)
  {
    size_t skip = UpdateNodes(num_bytes, position, i, ringbuffer, ringbuffer_mask, params, max_backward_limit, dist_cache, num_matches[i], &matches[cur_match_pos], model, &queue, nodes);
    if (skip < 16384)
    {
      skip = 0;
    }
    cur_match_pos += num_matches[i];
    if ((num_matches[i] == 1) && (BackwardMatchLength(&matches[cur_match_pos - 1]) > max_zopfli_len))
    {
      skip = brotli_max_size_t(BackwardMatchLength(&matches[cur_match_pos - 1]), skip);
    }
    if (skip > 1)
    {
      skip -= 1;
      while (skip)
      {
        i += 1;
        if ((i + 3) >= num_bytes)
        {
          break;
        }
        EvaluateNode(position + stream_offset, i, max_backward_limit, gap, dist_cache, model, &queue, nodes);
        cur_match_pos += num_matches[i];
        skip -= 1;
      }

    }
  }

  return ComputeShortestPathFromNodes(num_bytes, nodes);
}


----------------------------
inline static size_t StoreLookaheadH10(void)
{
  return 128;
}


----------------------------
typedef struct BackwardMatch
{
  uint32_t distance;
  uint32_t length_and_code;
} BackwardMatch
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
typedef struct 
{
  int quality;
  int lgwin;
  int verbosity;
  int force_overwrite;
  int junk_source;
  int copy_stat;
  int write_to_stdout;
  int test_integrity;
  int decompress;
  int large_window;
  const char *output_path;
  const char *suffix;
  int not_input_indices[20];
  size_t longest_path_len;
  size_t input_count;
  int argc;
  char **argv;
  char *modified_path;
  int iterator;
  int ignore;
  int iterator_error;
  uint8_t *buffer;
  uint8_t *input;
  uint8_t *output;
  const char *current_input_path;
  const char *current_output_path;
  int64_t input_file_length;
  FILE *fin;
  FILE *fout;
  size_t available_in;
  const uint8_t *next_in;
  size_t available_out;
  uint8_t *next_out;
  size_t total_in;
  size_t total_out;
} Context
----------------------------
static void CleanupZopfliCostModel(MemoryManager *m, ZopfliCostModel *self)
{
  {
    BrotliFree(m, self->literal_costs_);
    self->literal_costs_ = 0;
  }
  ;
  {
    BrotliFree(m, self->cost_dist_);
    self->cost_dist_ = 0;
  }
  ;
}


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
void helper_BrotliCreateHqZopfliBackwardReferences_1(unsigned int * const num_matches_idx_ref, size_t * const matches_size_ref, size_t * const cur_match_pos_ref, size_t * const i_ref, unsigned int * const matches_idx_ref, MemoryManager * const m, size_t num_bytes, size_t position, const uint8_t * const ringbuffer, size_t ringbuffer_mask, const BrotliEncoderParams * const params, Hasher * const hasher, const size_t stream_offset, const size_t max_backward_limit, uint32_t * const num_matches, const size_t store_end, BackwardMatch * const matches, size_t gap, size_t shadow_matches)
{
  unsigned int num_matches_idx = *num_matches_idx_ref;
  size_t matches_size = *matches_size_ref;
  size_t cur_match_pos = *cur_match_pos_ref;
  size_t i = *i_ref;
  unsigned int matches_idx = *matches_idx_ref;
  const size_t pos = position + i;
  size_t max_distance = brotli_min_size_t(pos, max_backward_limit);
  size_t dictionary_start = brotli_min_size_t(pos + stream_offset, max_backward_limit);
  size_t max_length = num_bytes - i;
  size_t num_found_matches;
  size_t cur_match_end;
  size_t j;
  {
    helper_helper_BrotliCreateHqZopfliBackwardReferences_1_1(&matches_size, &matches_idx, m, matches, shadow_matches, cur_match_pos);
  }
  ;
  if (!(!0))
  {
    return;
  }
  num_found_matches = FindAllMatchesH10(&hasher->privat._H10, &params->dictionary, ringbuffer, ringbuffer_mask, pos, max_length, max_distance, dictionary_start + gap, params, &matches[(cur_match_pos + shadow_matches) + matches_idx]);
  cur_match_end = cur_match_pos + num_found_matches;
  for (j = cur_match_pos; (j + 1) < cur_match_end; j += 1)
  {
    ;
  }

  num_matches[i + num_matches_idx] = (uint32_t) num_found_matches;
  if (num_found_matches > 0)
  {
    const size_t match_len = BackwardMatchLength(&matches[(cur_match_end - 1) + matches_idx]);
    if (match_len > 325)
    {
      const size_t skip = match_len - 1;
      matches[cur_match_pos + matches_idx] = matches[(cur_match_end - 1) + matches_idx];
      cur_match_pos += 1;
      num_matches[i + num_matches_idx] = 1;
      StoreRangeH10(&hasher->privat._H10, ringbuffer, ringbuffer_mask, pos + 1, brotli_min_size_t(pos + match_len, store_end));
      memset(&num_matches[(i + 1) + num_matches_idx], 0, skip * (sizeof(num_matches[0 + num_matches_idx])));
      i += skip;
    }
    else
    {
      cur_match_pos = cur_match_end;
    }
  }
  *num_matches_idx_ref = num_matches_idx;
  *matches_size_ref = matches_size;
  *cur_match_pos_ref = cur_match_pos;
  *i_ref = i;
  *matches_idx_ref = matches_idx;
}


----------------------------
typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
----------------------------
void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


----------------------------
typedef struct ZopfliCostModel
{
  float cost_cmd_[704];
  float *cost_dist_;
  uint32_t distance_histogram_size;
  float *literal_costs_;
  float min_cost_cmd_;
  size_t num_bytes_;
} ZopfliCostModel
----------------------------
static void ZopfliCostModelSetFromLiteralCosts(ZopfliCostModel *self, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask)
{
  float *literal_costs = self->literal_costs_;
  float literal_carry = 0.0;
  float *cost_dist = self->cost_dist_;
  float *cost_cmd = self->cost_cmd_;
  size_t num_bytes = self->num_bytes_;
  size_t i;
  BrotliEstimateBitCostsForLiterals(position, num_bytes, ringbuffer_mask, ringbuffer, &literal_costs[1]);
  literal_costs[0] = 0.0;
  for (i = 0; i < num_bytes; i += 1)
  {
    literal_carry += literal_costs[i + 1];
    literal_costs[i + 1] = literal_costs[i] + literal_carry;
    literal_carry -= literal_costs[i + 1] - literal_costs[i];
  }

  for (i = 0; i < 704; i += 1)
  {
    cost_cmd[i] = (float) FastLog2(11 + ((uint32_t) i));
  }

  for (i = 0; i < self->distance_histogram_size; i += 1)
  {
    cost_dist[i] = (float) FastLog2(20 + ((uint32_t) i));
  }

  self->min_cost_cmd_ = (float) FastLog2(11);
}


----------------------------
inline static size_t HashTypeLengthH10(void)
{
  return 4;
}


----------------------------
static void ZopfliCostModelSetFromCommands(ZopfliCostModel *self, size_t position, const uint8_t *ringbuffer, size_t ringbuffer_mask, const Command *commands, size_t num_commands, size_t last_insert_len)
{
  uint32_t histogram_literal[256];
  uint32_t histogram_cmd[704];
  uint32_t histogram_dist[544];
  float cost_literal[256];
  size_t pos = position - last_insert_len;
  float min_cost_cmd = kInfinity;
  size_t i;
  float *cost_cmd = self->cost_cmd_;
  memset(histogram_literal, 0, sizeof(histogram_literal));
  memset(histogram_cmd, 0, sizeof(histogram_cmd));
  memset(histogram_dist, 0, sizeof(histogram_dist));
  for (i = 0; i < num_commands; i += 1)
  {
    helper_ZopfliCostModelSetFromCommands_1(&ringbuffer_mask, &pos, ringbuffer, commands, histogram_literal, histogram_cmd, histogram_dist, i);
  }

  SetCost(histogram_literal, 256, 1, cost_literal);
  SetCost(histogram_cmd, 704, 0, cost_cmd);
  SetCost(histogram_dist, self->distance_histogram_size, 0, self->cost_dist_);
  for (i = 0; i < 704; i += 1)
  {
    min_cost_cmd = brotli_min_float(min_cost_cmd, cost_cmd[i]);
  }

  self->min_cost_cmd_ = min_cost_cmd;
  {
    float *literal_costs = self->literal_costs_;
    float literal_carry = 0.0;
    size_t num_bytes = self->num_bytes_;
    literal_costs[0] = 0.0;
    for (i = 0; i < num_bytes; i += 1)
    {
      literal_carry += cost_literal[ringbuffer[(position + i) & ringbuffer_mask]];
      literal_costs[i + 1] = literal_costs[i] + literal_carry;
      literal_carry -= literal_costs[i + 1] - literal_costs[i];
    }

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
static void InitZopfliCostModel(MemoryManager *m, ZopfliCostModel *self, const BrotliDistanceParams *dist, size_t num_bytes)
{
  self->num_bytes_ = num_bytes;
  self->literal_costs_ = ((num_bytes + 2) > 0) ? ((float *) BrotliAllocate(m, (num_bytes + 2) * (sizeof(float)))) : (0);
  self->cost_dist_ = (dist->alphabet_size_limit > 0) ? ((float *) BrotliAllocate(m, dist->alphabet_size_limit * (sizeof(float)))) : (0);
  self->distance_histogram_size = dist->alphabet_size_limit;
  if (!(!0))
  {
    return;
  }
}


----------------------------
None
----------------------------
***/


