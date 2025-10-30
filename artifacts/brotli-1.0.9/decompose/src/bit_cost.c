inline static size_t HistogramDataSizeLiteral(void)
{
  return 256;
}


/*** DEPENDENCIES:
***/


inline static size_t HistogramDataSizeCommand(void)
{
  return 704;
}


/*** DEPENDENCIES:
***/


inline static size_t HistogramDataSizeDistance(void)
{
  return 544;
}


/*** DEPENDENCIES:
***/


inline static void HistogramClearLiteral(HistogramLiteral *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


/*** DEPENDENCIES:
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


inline static void HistogramAddLiteral(HistogramLiteral *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


/*** DEPENDENCIES:
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


inline static void HistogramAddVectorLiteral(HistogramLiteral *self, const uint8_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


/*** DEPENDENCIES:
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


inline static void HistogramAddHistogramLiteral(HistogramLiteral *self, const HistogramLiteral *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 256; i += 1)
  {
    self->data_[i] += v->data_[i];
  }

}


/*** DEPENDENCIES:
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


inline static void HistogramClearDistance(HistogramDistance *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
}


/*** DEPENDENCIES:
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


inline static void HistogramAddDistance(HistogramDistance *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
}


/*** DEPENDENCIES:
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


inline static void HistogramAddVectorDistance(HistogramDistance *self, const uint16_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
}


/*** DEPENDENCIES:
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


inline static void HistogramAddHistogramDistance(HistogramDistance *self, const HistogramDistance *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 544; i += 1)
  {
    self->data_[i] += v->data_[i];
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
***/


inline static double ShannonEntropy(const uint32_t *population, size_t size, size_t *total)
{
  unsigned int population_idx = 0;
  size_t sum = 0;
  double retval = 0;
  const uint32_t *population_end = (&population[population_idx]) + size;
  size_t p;
  if (size & 1)
  {
    goto odd_number_of_elements_left;
  }
  while ((&population[population_idx]) < population_end)
  {
    p = population[population_idx];
    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
    odd_number_of_elements_left:
    p = population[population_idx];

    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
  }

  if (sum)
  {
    retval += ((double) sum) * FastLog2(sum);
  }
  *total = sum;
  return retval;
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


inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


/*** DEPENDENCIES:
inline static double ShannonEntropy(const uint32_t *population, size_t size, size_t *total)
{
  unsigned int population_idx = 0;
  size_t sum = 0;
  double retval = 0;
  const uint32_t *population_end = (&population[population_idx]) + size;
  size_t p;
  if (size & 1)
  {
    goto odd_number_of_elements_left;
  }
  while ((&population[population_idx]) < population_end)
  {
    p = population[population_idx];
    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
    odd_number_of_elements_left:
    p = population[population_idx];

    population_idx += 1;
    sum += p;
    retval -= ((double) p) * FastLog2(p);
  }

  if (sum)
  {
    retval += ((double) sum) * FastLog2(sum);
  }
  *total = sum;
  return retval;
}


----------------------------
***/


inline static void ClearHistogramsLiteral(HistogramLiteral *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearLiteral(array + i);

}


/*** DEPENDENCIES:
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
***/


inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
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
***/


inline static void HistogramAddCommand(HistogramCommand *self, size_t val)
{
  self->data_[val] += 1;
  self->total_count_ += 1;
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
***/


inline static void HistogramAddVectorCommand(HistogramCommand *self, const uint16_t *p, size_t n)
{
  unsigned int p_idx = 0;
  self->total_count_ += n;
  n += 1;
  while (--n)
    ++self->data_[*(&p[p_idx])];

  p_idx += 1;
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
***/


inline static void HistogramAddHistogramCommand(HistogramCommand *self, const HistogramCommand *v)
{
  size_t i;
  self->total_count_ += v->total_count_;
  for (i = 0; i < 704; i += 1)
  {
    self->data_[i] += v->data_[i];
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
***/


inline static void ClearHistogramsDistance(HistogramDistance *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearDistance(array + i);

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
***/


// hint:  ['i_ref is a mutable refrence to size_t']
double helper_BrotliPopulationCostLiteral_1(size_t * const i_ref, const HistogramLiteral * const histogram, static const double kFourSymbolHistogramCost, size_t s[5])
{
  size_t i = *i_ref;
  uint32_t histo[4];
  uint32_t h23;
  uint32_t histomax;
  for (i = 0; i < 4; i += 1)
  {
    histo[i] = histogram->data_[s[i]];
  }

  for (i = 0; i < 4; i += 1)
  {
    size_t j;
    for (j = i + 1; j < 4; j += 1)
    {
      if (histo[j] > histo[i])
      {
        {
          uint32_t __brotli_swap_tmp = histo[j];
          histo[j] = histo[i];
          histo[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  h23 = histo[2] + histo[3];
  histomax = brotli_max_uint32_t(h23, histo[0]);
  return ((kFourSymbolHistogramCost + (3 * h23)) + (2 * (histo[0] + histo[1]))) - histomax;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
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


// hint:  ['i_ref is a mutable refrence to size_t']
double helper_BrotliPopulationCostDistance_1(size_t * const i_ref, const HistogramDistance * const histogram, static const double kFourSymbolHistogramCost, size_t s[5])
{
  size_t i = *i_ref;
  uint32_t histo[4];
  uint32_t h23;
  uint32_t histomax;
  for (i = 0; i < 4; i += 1)
  {
    histo[i] = histogram->data_[s[i]];
  }

  for (i = 0; i < 4; i += 1)
  {
    size_t j;
    for (j = i + 1; j < 4; j += 1)
    {
      if (histo[j] > histo[i])
      {
        {
          uint32_t __brotli_swap_tmp = histo[j];
          histo[j] = histo[i];
          histo[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  h23 = histo[2] + histo[3];
  histomax = brotli_max_uint32_t(h23, histo[0]);
  return ((kFourSymbolHistogramCost + (3 * h23)) + (2 * (histo[0] + histo[1]))) - histomax;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
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


// hint:  ['bits_ref is a mutable refrence to double', 'i_ref is a mutable refrence to size_t', 'max_depth_ref is a mutable refrence to size_t']
void helper_helper_BrotliPopulationCostLiteral_2_1(double * const bits_ref, size_t * const i_ref, size_t * const max_depth_ref, const HistogramLiteral * const histogram, const size_t data_size, uint32_t depth_histo[17 + 1], const double log2total)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = *max_depth_ref;
  if (histogram->data_[i] > 0)
  {
    double log2p = log2total - FastLog2(histogram->data_[i]);
    size_t depth = (size_t) (log2p + 0.5);
    bits += histogram->data_[i] * log2p;
    if (depth > 15)
    {
      depth = 15;
    }
    if (depth > max_depth)
    {
      max_depth = depth;
    }
    depth_histo[depth] += 1;
    i += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < data_size) && (histogram->data_[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (i == data_size)
    {
      break;
    }
    if (reps < 3)
    {
      depth_histo[0] += reps;
    }
    else
    {
      reps -= 2;
      while (reps > 0)
      {
        depth_histo[17] += 1;
        bits += 3;
        reps >>= 3;
      }

    }
  }
  *bits_ref = bits;
  *i_ref = i;
  *max_depth_ref = max_depth;
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
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


// hint:  ['bits_ref is a mutable refrence to double', 'i_ref is a mutable refrence to size_t', 'max_depth_ref is a mutable refrence to size_t']
void helper_helper_BrotliPopulationCostDistance_2_1(double * const bits_ref, size_t * const i_ref, size_t * const max_depth_ref, const HistogramDistance * const histogram, const size_t data_size, uint32_t depth_histo[17 + 1], const double log2total)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = *max_depth_ref;
  if (histogram->data_[i] > 0)
  {
    double log2p = log2total - FastLog2(histogram->data_[i]);
    size_t depth = (size_t) (log2p + 0.5);
    bits += histogram->data_[i] * log2p;
    if (depth > 15)
    {
      depth = 15;
    }
    if (depth > max_depth)
    {
      max_depth = depth;
    }
    depth_histo[depth] += 1;
    i += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < data_size) && (histogram->data_[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (i == data_size)
    {
      break;
    }
    if (reps < 3)
    {
      depth_histo[0] += reps;
    }
    else
    {
      reps -= 2;
      while (reps > 0)
      {
        depth_histo[17] += 1;
        bits += 3;
        reps >>= 3;
      }

    }
  }
  *bits_ref = bits;
  *i_ref = i;
  *max_depth_ref = max_depth;
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
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


// hint:  ['bits_ref is a mutable refrence to double', 'i_ref is a mutable refrence to size_t']
void helper_BrotliPopulationCostDistance_2(double * const bits_ref, size_t * const i_ref, const HistogramDistance * const histogram, const size_t data_size)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = 1;
  uint32_t depth_histo[17 + 1] = {0};
  const double log2total = FastLog2(histogram->total_count_);
  for (i = 0; i < data_size;)
  {
    helper_helper_BrotliPopulationCostDistance_2_1(&bits, &i, &max_depth, histogram, data_size, depth_histo, log2total);
  }

  bits += (double) (18 + (2 * max_depth));
  bits += BitsEntropy(depth_histo, 17 + 1);
  *bits_ref = bits;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
void helper_helper_BrotliPopulationCostDistance_2_1(double * const bits_ref, size_t * const i_ref, size_t * const max_depth_ref, const HistogramDistance * const histogram, const size_t data_size, uint32_t depth_histo[17 + 1], const double log2total)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = *max_depth_ref;
  if (histogram->data_[i] > 0)
  {
    double log2p = log2total - FastLog2(histogram->data_[i]);
    size_t depth = (size_t) (log2p + 0.5);
    bits += histogram->data_[i] * log2p;
    if (depth > 15)
    {
      depth = 15;
    }
    if (depth > max_depth)
    {
      max_depth = depth;
    }
    depth_histo[depth] += 1;
    i += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < data_size) && (histogram->data_[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (i == data_size)
    {
      break;
    }
    if (reps < 3)
    {
      depth_histo[0] += reps;
    }
    else
    {
      reps -= 2;
      while (reps > 0)
      {
        depth_histo[17] += 1;
        bits += 3;
        reps >>= 3;
      }

    }
  }
  *bits_ref = bits;
  *i_ref = i;
  *max_depth_ref = max_depth;
}


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
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
***/


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


/*** DEPENDENCIES:
void helper_BrotliPopulationCostDistance_2(double * const bits_ref, size_t * const i_ref, const HistogramDistance * const histogram, const size_t data_size)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = 1;
  uint32_t depth_histo[17 + 1] = {0};
  const double log2total = FastLog2(histogram->total_count_);
  for (i = 0; i < data_size;)
  {
    helper_helper_BrotliPopulationCostDistance_2_1(&bits, &i, &max_depth, histogram, data_size, depth_histo, log2total);
  }

  bits += (double) (18 + (2 * max_depth));
  bits += BitsEntropy(depth_histo, 17 + 1);
  *bits_ref = bits;
  *i_ref = i;
}


----------------------------
double helper_BrotliPopulationCostDistance_1(size_t * const i_ref, const HistogramDistance * const histogram, static const double kFourSymbolHistogramCost, size_t s[5])
{
  size_t i = *i_ref;
  uint32_t histo[4];
  uint32_t h23;
  uint32_t histomax;
  for (i = 0; i < 4; i += 1)
  {
    histo[i] = histogram->data_[s[i]];
  }

  for (i = 0; i < 4; i += 1)
  {
    size_t j;
    for (j = i + 1; j < 4; j += 1)
    {
      if (histo[j] > histo[i])
      {
        {
          uint32_t __brotli_swap_tmp = histo[j];
          histo[j] = histo[i];
          histo[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  h23 = histo[2] + histo[3];
  histomax = brotli_max_uint32_t(h23, histo[0]);
  return ((kFourSymbolHistogramCost + (3 * h23)) + (2 * (histo[0] + histo[1]))) - histomax;
  *i_ref = i;
}


----------------------------
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
typedef struct HistogramDistance
{
  uint32_t data_[544];
  size_t total_count_;
  double bit_cost_;
} HistogramDistance
----------------------------
inline static size_t HistogramDataSizeDistance(void)
{
  return 544;
}


----------------------------
***/


inline static void ClearHistogramsCommand(HistogramCommand *array, size_t length)
{
  size_t i;
  for (i = 0; i < length; i += 1)
    HistogramClearCommand(array + i);

}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
----------------------------
inline static void HistogramClearCommand(HistogramCommand *self)
{
  memset(self->data_, 0, sizeof(self->data_));
  self->total_count_ = 0;
  self->bit_cost_ = HUGE_VAL;
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


// hint:  ['i_ref is a mutable refrence to size_t']
double helper_BrotliPopulationCostCommand_1(size_t * const i_ref, const HistogramCommand * const histogram, static const double kFourSymbolHistogramCost, size_t s[5])
{
  size_t i = *i_ref;
  uint32_t histo[4];
  uint32_t h23;
  uint32_t histomax;
  for (i = 0; i < 4; i += 1)
  {
    histo[i] = histogram->data_[s[i]];
  }

  for (i = 0; i < 4; i += 1)
  {
    size_t j;
    for (j = i + 1; j < 4; j += 1)
    {
      if (histo[j] > histo[i])
      {
        {
          uint32_t __brotli_swap_tmp = histo[j];
          histo[j] = histo[i];
          histo[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  h23 = histo[2] + histo[3];
  histomax = brotli_max_uint32_t(h23, histo[0]);
  return ((kFourSymbolHistogramCost + (3 * h23)) + (2 * (histo[0] + histo[1]))) - histomax;
  *i_ref = i;
}


/*** DEPENDENCIES:
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
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
***/


// hint:  ['bits_ref is a mutable refrence to double', 'i_ref is a mutable refrence to size_t', 'max_depth_ref is a mutable refrence to size_t']
void helper_helper_BrotliPopulationCostCommand_2_1(double * const bits_ref, size_t * const i_ref, size_t * const max_depth_ref, const HistogramCommand * const histogram, const size_t data_size, uint32_t depth_histo[17 + 1], const double log2total)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = *max_depth_ref;
  if (histogram->data_[i] > 0)
  {
    double log2p = log2total - FastLog2(histogram->data_[i]);
    size_t depth = (size_t) (log2p + 0.5);
    bits += histogram->data_[i] * log2p;
    if (depth > 15)
    {
      depth = 15;
    }
    if (depth > max_depth)
    {
      max_depth = depth;
    }
    depth_histo[depth] += 1;
    i += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < data_size) && (histogram->data_[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (i == data_size)
    {
      break;
    }
    if (reps < 3)
    {
      depth_histo[0] += reps;
    }
    else
    {
      reps -= 2;
      while (reps > 0)
      {
        depth_histo[17] += 1;
        bits += 3;
        reps >>= 3;
      }

    }
  }
  *bits_ref = bits;
  *i_ref = i;
  *max_depth_ref = max_depth;
}


/*** DEPENDENCIES:
typedef struct HistogramCommand
{
  uint32_t data_[704];
  size_t total_count_;
  double bit_cost_;
} HistogramCommand
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


// hint:  ['bits_ref is a mutable refrence to double', 'i_ref is a mutable refrence to size_t']
void helper_BrotliPopulationCostCommand_2(double * const bits_ref, size_t * const i_ref, const HistogramCommand * const histogram, const size_t data_size)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = 1;
  uint32_t depth_histo[17 + 1] = {0};
  const double log2total = FastLog2(histogram->total_count_);
  for (i = 0; i < data_size;)
  {
    helper_helper_BrotliPopulationCostCommand_2_1(&bits, &i, &max_depth, histogram, data_size, depth_histo, log2total);
  }

  bits += (double) (18 + (2 * max_depth));
  bits += BitsEntropy(depth_histo, 17 + 1);
  *bits_ref = bits;
  *i_ref = i;
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
inline static double FastLog2(size_t v)
{
  if (v < 256)
  {
    return kBrotliLog2Table[v];
  }
  return log2((double) v);
}


----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


----------------------------
void helper_helper_BrotliPopulationCostCommand_2_1(double * const bits_ref, size_t * const i_ref, size_t * const max_depth_ref, const HistogramCommand * const histogram, const size_t data_size, uint32_t depth_histo[17 + 1], const double log2total)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = *max_depth_ref;
  if (histogram->data_[i] > 0)
  {
    double log2p = log2total - FastLog2(histogram->data_[i]);
    size_t depth = (size_t) (log2p + 0.5);
    bits += histogram->data_[i] * log2p;
    if (depth > 15)
    {
      depth = 15;
    }
    if (depth > max_depth)
    {
      max_depth = depth;
    }
    depth_histo[depth] += 1;
    i += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < data_size) && (histogram->data_[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (i == data_size)
    {
      break;
    }
    if (reps < 3)
    {
      depth_histo[0] += reps;
    }
    else
    {
      reps -= 2;
      while (reps > 0)
      {
        depth_histo[17] += 1;
        bits += 3;
        reps >>= 3;
      }

    }
  }
  *bits_ref = bits;
  *i_ref = i;
  *max_depth_ref = max_depth;
}


----------------------------
***/


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
double helper_BrotliPopulationCostCommand_1(size_t * const i_ref, const HistogramCommand * const histogram, static const double kFourSymbolHistogramCost, size_t s[5])
{
  size_t i = *i_ref;
  uint32_t histo[4];
  uint32_t h23;
  uint32_t histomax;
  for (i = 0; i < 4; i += 1)
  {
    histo[i] = histogram->data_[s[i]];
  }

  for (i = 0; i < 4; i += 1)
  {
    size_t j;
    for (j = i + 1; j < 4; j += 1)
    {
      if (histo[j] > histo[i])
      {
        {
          uint32_t __brotli_swap_tmp = histo[j];
          histo[j] = histo[i];
          histo[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  h23 = histo[2] + histo[3];
  histomax = brotli_max_uint32_t(h23, histo[0]);
  return ((kFourSymbolHistogramCost + (3 * h23)) + (2 * (histo[0] + histo[1]))) - histomax;
  *i_ref = i;
}


----------------------------
inline static size_t HistogramDataSizeCommand(void)
{
  return 704;
}


----------------------------
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
void helper_BrotliPopulationCostCommand_2(double * const bits_ref, size_t * const i_ref, const HistogramCommand * const histogram, const size_t data_size)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = 1;
  uint32_t depth_histo[17 + 1] = {0};
  const double log2total = FastLog2(histogram->total_count_);
  for (i = 0; i < data_size;)
  {
    helper_helper_BrotliPopulationCostCommand_2_1(&bits, &i, &max_depth, histogram, data_size, depth_histo, log2total);
  }

  bits += (double) (18 + (2 * max_depth));
  bits += BitsEntropy(depth_histo, 17 + 1);
  *bits_ref = bits;
  *i_ref = i;
}


----------------------------
***/


// hint:  ['bits_ref is a mutable refrence to double', 'i_ref is a mutable refrence to size_t']
void helper_BrotliPopulationCostLiteral_2(double * const bits_ref, size_t * const i_ref, const HistogramLiteral * const histogram, const size_t data_size)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = 1;
  uint32_t depth_histo[17 + 1] = {0};
  const double log2total = FastLog2(histogram->total_count_);
  for (i = 0; i < data_size;)
  {
    helper_helper_BrotliPopulationCostLiteral_2_1(&bits, &i, &max_depth, histogram, data_size, depth_histo, log2total);
  }

  bits += (double) (18 + (2 * max_depth));
  bits += BitsEntropy(depth_histo, 17 + 1);
  *bits_ref = bits;
  *i_ref = i;
}


/*** DEPENDENCIES:
void helper_helper_BrotliPopulationCostLiteral_2_1(double * const bits_ref, size_t * const i_ref, size_t * const max_depth_ref, const HistogramLiteral * const histogram, const size_t data_size, uint32_t depth_histo[17 + 1], const double log2total)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = *max_depth_ref;
  if (histogram->data_[i] > 0)
  {
    double log2p = log2total - FastLog2(histogram->data_[i]);
    size_t depth = (size_t) (log2p + 0.5);
    bits += histogram->data_[i] * log2p;
    if (depth > 15)
    {
      depth = 15;
    }
    if (depth > max_depth)
    {
      max_depth = depth;
    }
    depth_histo[depth] += 1;
    i += 1;
  }
  else
  {
    uint32_t reps = 1;
    size_t k;
    for (k = i + 1; (k < data_size) && (histogram->data_[k] == 0); k += 1)
    {
      reps += 1;
    }

    i += reps;
    if (i == data_size)
    {
      break;
    }
    if (reps < 3)
    {
      depth_histo[0] += reps;
    }
    else
    {
      reps -= 2;
      while (reps > 0)
      {
        depth_histo[17] += 1;
        bits += 3;
        reps >>= 3;
      }

    }
  }
  *bits_ref = bits;
  *i_ref = i;
  *max_depth_ref = max_depth;
}


----------------------------
inline static double BitsEntropy(const uint32_t *population, size_t size)
{
  size_t sum;
  double retval = ShannonEntropy(population, size, &sum);
  if (retval < sum)
  {
    retval = (double) sum;
  }
  return retval;
}


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
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
***/


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


/*** DEPENDENCIES:
inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}


----------------------------
inline static size_t HistogramDataSizeLiteral(void)
{
  return 256;
}


----------------------------
double helper_BrotliPopulationCostLiteral_1(size_t * const i_ref, const HistogramLiteral * const histogram, static const double kFourSymbolHistogramCost, size_t s[5])
{
  size_t i = *i_ref;
  uint32_t histo[4];
  uint32_t h23;
  uint32_t histomax;
  for (i = 0; i < 4; i += 1)
  {
    histo[i] = histogram->data_[s[i]];
  }

  for (i = 0; i < 4; i += 1)
  {
    size_t j;
    for (j = i + 1; j < 4; j += 1)
    {
      if (histo[j] > histo[i])
      {
        {
          uint32_t __brotli_swap_tmp = histo[j];
          histo[j] = histo[i];
          histo[i] = __brotli_swap_tmp;
        }
        ;
      }
    }

  }

  h23 = histo[2] + histo[3];
  histomax = brotli_max_uint32_t(h23, histo[0]);
  return ((kFourSymbolHistogramCost + (3 * h23)) + (2 * (histo[0] + histo[1]))) - histomax;
  *i_ref = i;
}


----------------------------
typedef struct HistogramLiteral
{
  uint32_t data_[256];
  size_t total_count_;
  double bit_cost_;
} HistogramLiteral
----------------------------
void helper_BrotliPopulationCostLiteral_2(double * const bits_ref, size_t * const i_ref, const HistogramLiteral * const histogram, const size_t data_size)
{
  double bits = *bits_ref;
  size_t i = *i_ref;
  size_t max_depth = 1;
  uint32_t depth_histo[17 + 1] = {0};
  const double log2total = FastLog2(histogram->total_count_);
  for (i = 0; i < data_size;)
  {
    helper_helper_BrotliPopulationCostLiteral_2_1(&bits, &i, &max_depth, histogram, data_size, depth_histo, log2total);
  }

  bits += (double) (18 + (2 * max_depth));
  bits += BitsEntropy(depth_histo, 17 + 1);
  *bits_ref = bits;
  *i_ref = i;
}


----------------------------
***/


