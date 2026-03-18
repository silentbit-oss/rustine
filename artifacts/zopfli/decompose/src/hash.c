void ZopfliAllocHash(size_t window_size, ZopfliHash *h)
{
  h->head = (int *) malloc((sizeof(*h->head)) * 65536);
  h->prev = (unsigned short *) malloc((sizeof(*h->prev)) * window_size);
  h->hashval = (int *) malloc((sizeof(*h->hashval)) * window_size);
  h->same = (unsigned short *) malloc((sizeof(*h->same)) * window_size);
  h->head2 = (int *) malloc((sizeof(*h->head2)) * 65536);
  h->prev2 = (unsigned short *) malloc((sizeof(*h->prev2)) * window_size);
  h->hashval2 = (int *) malloc((sizeof(*h->hashval2)) * window_size);
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
***/


void ZopfliResetHash(size_t window_size, ZopfliHash *h)
{
  size_t i;
  h->val = 0;
  for (i = 0; i < 65536; i += 1)
  {
    h->head[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->prev[i] = i;
    h->hashval[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->same[i] = 0;
  }

  h->val2 = 0;
  for (i = 0; i < 65536; i += 1)
  {
    h->head2[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->prev2[i] = i;
    h->hashval2[i] = -1;
  }

}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
***/


void ZopfliCleanHash(ZopfliHash *h)
{
  free(h->head);
  free(h->prev);
  free(h->hashval);
  free(h->head2);
  free(h->prev2);
  free(h->hashval2);
  free(h->same);
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
***/


static void UpdateHashValue(ZopfliHash *h, unsigned char c)
{
  h->val = ((h->val << 5) ^ c) & 32767;
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
***/


void ZopfliWarmupHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  UpdateHashValue(h, array[pos + 0]);
  if ((pos + 1) < end)
  {
    UpdateHashValue(h, array[pos + 1]);
  }
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
static void UpdateHashValue(ZopfliHash *h, unsigned char c)
{
  h->val = ((h->val << 5) ^ c) & 32767;
}


----------------------------
***/


void ZopfliUpdateHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  unsigned short hpos = pos & (32768 - 1);
  size_t amount = 0;
  UpdateHashValue(h, ((pos + 3) <= end) ? (array[(pos + 3) - 1]) : (0));
  h->hashval[hpos] = h->val;
  if ((h->head[h->val] != (-1)) && (h->hashval[h->head[h->val]] == h->val))
  {
    h->prev[hpos] = h->head[h->val];
  }
  else
    h->prev[hpos] = hpos;
  h->head[h->val] = hpos;
  if (h->same[(pos - 1) & (32768 - 1)] > 1)
  {
    amount = h->same[(pos - 1) & (32768 - 1)] - 1;
  }
  while (((((pos + amount) + 1) < end) && (array[pos] == array[(pos + amount) + 1])) && (amount < ((unsigned short) (-1))))
  {
    amount += 1;
  }

  h->same[hpos] = amount;
  h->val2 = ((h->same[hpos] - 3) & 255) ^ h->val;
  h->hashval2[hpos] = h->val2;
  if ((h->head2[h->val2] != (-1)) && (h->hashval2[h->head2[h->val2]] == h->val2))
  {
    h->prev2[hpos] = h->head2[h->val2];
  }
  else
    h->prev2[hpos] = hpos;
  h->head2[h->val2] = hpos;
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
static void UpdateHashValue(ZopfliHash *h, unsigned char c)
{
  h->val = ((h->val << 5) ^ c) & 32767;
}


----------------------------
***/


