void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols)
{
  size_t *bl_count = (size_t *) malloc((sizeof(size_t)) * (maxbits + 1));
  size_t *next_code = (size_t *) malloc((sizeof(size_t)) * (maxbits + 1));
  unsigned bits;
  unsigned i;
  unsigned code;
  for (i = 0; i < n; i += 1)
  {
    symbols[i] = 0;
  }

  for (bits = 0; bits <= maxbits; bits += 1)
  {
    bl_count[bits] = 0;
  }

  for (i = 0; i < n; i += 1)
  {
    assert(lengths[i] <= maxbits);
    bl_count[lengths[i]] += 1;
  }

  code = 0;
  bl_count[0] = 0;
  for (bits = 1; bits <= maxbits; bits += 1)
  {
    code = (code + bl_count[bits - 1]) << 1;
    next_code[bits] = code;
  }

  for (i = 0; i < n; i += 1)
  {
    unsigned len = lengths[i];
    if (len != 0)
    {
      symbols[i] = next_code[len];
      next_code[len] += 1;
    }
  }

  free(bl_count);
  free(next_code);
}


/*** DEPENDENCIES:
***/


void ZopfliCalculateEntropy(const size_t *count, size_t n, double *bitlengths)
{
  static const double kInvLog2 = 1.4426950408889;
  unsigned sum = 0;
  unsigned i;
  double log2sum;
  for (i = 0; i < n; i += 1)
  {
    sum += count[i];
  }

  log2sum = ((sum == 0) ? (log(n)) : (log(sum))) * kInvLog2;
  for (i = 0; i < n; i += 1)
  {
    if (count[i] == 0)
    {
      bitlengths[i] = log2sum;
    }
    else
      bitlengths[i] = log2sum - (log(count[i]) * kInvLog2);
    if ((bitlengths[i] < 0) && (bitlengths[i] > (-1e-5)))
    {
      bitlengths[i] = 0;
    }
    assert(bitlengths[i] >= 0);
  }

}


/*** DEPENDENCIES:
***/


void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths)
{
  int error = ZopfliLengthLimitedCodeLengths(count, n, maxbits, bitlengths);
  (void) error;
  assert(!error);
}


/*** DEPENDENCIES:
int ZopfliLengthLimitedCodeLengths(const size_t *frequencies, int n, int maxbits, unsigned *bitlengths)
{
  NodePool pool;
  int i;
  int numsymbols = 0;
  int numBoundaryPMRuns;
  Node *nodes;
  unsigned int nodes_idx = 0;
  Node *(*lists)[2];
  unsigned int lists_idx = 0;
  Node *leaves = (Node *) malloc(n * (sizeof(*leaves)));
  for (i = 0; i < n; i += 1)
  {
    bitlengths[i] = 0;
  }

  for (i = 0; i < n; i += 1)
  {
    if (frequencies[i])
    {
      leaves[numsymbols].weight = frequencies[i];
      leaves[numsymbols].count = i;
      numsymbols += 1;
    }
  }

  if ((1 << maxbits) < numsymbols)
  {
    free(leaves);
    return 1;
  }
  if (numsymbols == 0)
  {
    free(leaves);
    return 0;
  }
  if (numsymbols == 1)
  {
    bitlengths[leaves[0].count] = 1;
    free(leaves);
    return 0;
  }
  if (numsymbols == 2)
  {
    bitlengths[leaves[0].count] += 1;
    bitlengths[leaves[1].count] += 1;
    free(leaves);
    return 0;
  }
  for (i = 0; i < numsymbols; i += 1)
  {
    if (leaves[i].weight >= (((size_t) 1) << (((sizeof(leaves[0].weight)) * 8) - 9)))
    {
      free(leaves);
      return 1;
    }
    leaves[i].weight = (leaves[i].weight << 9) | leaves[i].count;
  }

  qsort(leaves, numsymbols, sizeof(Node), LeafComparator);
  for (i = 0; i < numsymbols; i += 1)
  {
    leaves[i].weight >>= 9;
  }

  if ((numsymbols - 1) < maxbits)
  {
    maxbits = numsymbols - 1;
  }
  nodes_idx = (Node *) malloc(((maxbits * 2) * numsymbols) * (sizeof(Node)));
  pool.next = &nodes[nodes_idx];
  lists_idx = (Node *(*)[2]) malloc(maxbits * (sizeof(*lists_idx)));
  InitLists(&pool, leaves, maxbits, lists);
  numBoundaryPMRuns = (2 * numsymbols) - 4;
  for (i = 0; i < (numBoundaryPMRuns - 1); i += 1)
  {
    BoundaryPM(lists, leaves, numsymbols, &pool, maxbits - 1);
  }

  BoundaryPMFinal(lists, leaves, numsymbols, &pool, maxbits - 1);
  ExtractBitLengths(lists[(maxbits - 1) + lists_idx][1], leaves, bitlengths);
  free(lists);
  free(leaves);
  free(nodes);
  return 0;
}


----------------------------
***/


