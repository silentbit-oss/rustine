static unsigned long lh_perllike_str_hash(const void *k)
{
  const char *rkey = (const char *) k;
  unsigned int rkey_idx = 0;
  unsigned hashval = 1;
  while (rkey[rkey_idx])
  {
    hashval = (hashval * 33) + rkey[rkey_idx];
    rkey_idx += 1;
  }

  return hashval;
}


/*** DEPENDENCIES:
***/


int lh_char_equal(const void *k1, const void *k2)
{
  return strcmp((const char *) k1, (const char *) k2) == 0;
}


/*** DEPENDENCIES:
***/


int lh_ptr_equal(const void *k1, const void *k2)
{
  return k1 == k2;
}


/*** DEPENDENCIES:
***/


static unsigned long lh_ptr_hash(const void *k)
{
  return (unsigned long) (((((ptrdiff_t) k) * 0x9e370001UL) >> 4) & 18446744073709551615UL);
}


/*** DEPENDENCIES:
***/


// hint:  ['a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
void helper_hashlittle_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  c ^= b;
  c -= (b << 14) | (b >> (32 - 14));
  a ^= c;
  a -= (c << 11) | (c >> (32 - 11));
  b ^= a;
  b -= (a << 25) | (a >> (32 - 25));
  c ^= b;
  c -= (b << 16) | (b >> (32 - 16));
  a ^= c;
  a -= (c << 4) | (c >> (32 - 4));
  b ^= a;
  b -= (a << 14) | (a >> (32 - 14));
  c ^= b;
  c -= (b << 24) | (b >> (32 - 24));
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
***/


// hint:  ['a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
void helper_helper_helper_hashlittle_2_1_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  a -= c;
  a ^= (c << 4) | (c >> (32 - 4));
  c += b;
  b -= a;
  b ^= (a << 6) | (a >> (32 - 6));
  a += c;
  c -= b;
  c ^= (b << 8) | (b >> (32 - 8));
  b += a;
  a -= c;
  a ^= (c << 16) | (c >> (32 - 16));
  c += b;
  b -= a;
  b ^= (a << 19) | (a >> (32 - 19));
  a += c;
  c -= b;
  c ^= (b << 4) | (b >> (32 - 4));
  b += a;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
***/


// hint:  ['a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
void helper_helper_helper_hashlittle_3_1_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  a -= c;
  a ^= (c << 4) | (c >> (32 - 4));
  c += b;
  b -= a;
  b ^= (a << 6) | (a >> (32 - 6));
  a += c;
  c -= b;
  c ^= (b << 8) | (b >> (32 - 8));
  b += a;
  a -= c;
  a ^= (c << 16) | (c >> (32 - 16));
  c += b;
  b -= a;
  b ^= (a << 19) | (a >> (32 - 19));
  a += c;
  c -= b;
  c ^= (b << 4) | (b >> (32 - 4));
  b += a;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
***/


// hint:  ['a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
void helper_helper_helper_hashlittle_4_1_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  a -= c;
  a ^= (c << 4) | (c >> (32 - 4));
  c += b;
  b -= a;
  b ^= (a << 6) | (a >> (32 - 6));
  a += c;
  c -= b;
  c ^= (b << 8) | (b >> (32 - 8));
  b += a;
  a -= c;
  a ^= (c << 16) | (c >> (32 - 16));
  c += b;
  b -= a;
  b ^= (a << 19) | (a >> (32 - 19));
  a += c;
  c -= b;
  c ^= (b << 4) | (b >> (32 - 4));
  b += a;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
***/


void lh_table_free(struct lh_table *t)
{
  struct lh_entry *c;
  unsigned int c_idx = 0;
  if (t->free_fn)
  {
    for (c_idx = t->head; (&c[c_idx]) != 0; c_idx = c_idx->next)
    {
      t->free_fn(c);
    }

  }
  free(t->table);
  free(t);
}


/*** DEPENDENCIES:
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
***/


int lh_table_length(struct lh_table *t)
{
  return t->count;
}


/*** DEPENDENCIES:
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
***/


// hint:  ['length_ref is a mutable refrence to size_t', 'a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t', 'k_idx_ref is a mutable refrence to unsigned int']
void helper_helper_hashlittle_2_1(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, unsigned int * const k_idx_ref, const uint8_t * const k)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  unsigned int k_idx = *k_idx_ref;
  a += k[0 + k_idx];
  a += ((uint32_t) k[1 + k_idx]) << 8;
  a += ((uint32_t) k[2 + k_idx]) << 16;
  a += ((uint32_t) k[3 + k_idx]) << 24;
  b += k[4 + k_idx];
  b += ((uint32_t) k[5 + k_idx]) << 8;
  b += ((uint32_t) k[6 + k_idx]) << 16;
  b += ((uint32_t) k[7 + k_idx]) << 24;
  c += k[8 + k_idx];
  c += ((uint32_t) k[9 + k_idx]) << 8;
  c += ((uint32_t) k[10 + k_idx]) << 16;
  c += ((uint32_t) k[11 + k_idx]) << 24;
  {
    helper_helper_helper_hashlittle_2_1_1(&a, &b, &c);
  }
  ;
  length -= 12;
  k_idx += 12;
  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
  *k_idx_ref = k_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_hashlittle_2_1_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  a -= c;
  a ^= (c << 4) | (c >> (32 - 4));
  c += b;
  b -= a;
  b ^= (a << 6) | (a >> (32 - 6));
  a += c;
  c -= b;
  c ^= (b << 8) | (b >> (32 - 8));
  b += a;
  a -= c;
  a ^= (c << 16) | (c >> (32 - 16));
  c += b;
  b -= a;
  b ^= (a << 19) | (a >> (32 - 19));
  a += c;
  c -= b;
  c ^= (b << 4) | (b >> (32 - 4));
  b += a;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
***/


// hint:  ['length_ref is a mutable refrence to size_t', 'a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
uint32_t helper_hashlittle_2(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, const void * const key)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  const uint8_t *k = (const uint8_t *) key;
  unsigned int k_idx = 0;
  while (length > 12)
  {
    helper_helper_hashlittle_2_1(&length, &a, &b, &c, &k_idx, k);
  }

  switch (length)
  {
    case 12:
    {
      c += ((uint32_t) k[11 + k_idx]) << 24;
    }

    case 11:
    {
      c += ((uint32_t) k[10 + k_idx]) << 16;
    }

    case 10:
    {
      c += ((uint32_t) k[9 + k_idx]) << 8;
    }

    case 9:
    {
      c += k[8 + k_idx];
    }

    case 8:
    {
      b += ((uint32_t) k[7 + k_idx]) << 24;
    }

    case 7:
    {
      b += ((uint32_t) k[6 + k_idx]) << 16;
    }

    case 6:
    {
      b += ((uint32_t) k[5 + k_idx]) << 8;
    }

    case 5:
    {
      b += k[4 + k_idx];
    }

    case 4:
    {
      a += ((uint32_t) k[3 + k_idx]) << 24;
    }

    case 3:
    {
      a += ((uint32_t) k[2 + k_idx]) << 16;
    }

    case 2:
    {
      a += ((uint32_t) k[1 + k_idx]) << 8;
    }

    case 1:
    {
      a += k[0 + k_idx];
      break;
    }

    case 0:
    {
      return c;
    }

  }

  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_hashlittle_2_1(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, unsigned int * const k_idx_ref, const uint8_t * const k)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  unsigned int k_idx = *k_idx_ref;
  a += k[0 + k_idx];
  a += ((uint32_t) k[1 + k_idx]) << 8;
  a += ((uint32_t) k[2 + k_idx]) << 16;
  a += ((uint32_t) k[3 + k_idx]) << 24;
  b += k[4 + k_idx];
  b += ((uint32_t) k[5 + k_idx]) << 8;
  b += ((uint32_t) k[6 + k_idx]) << 16;
  b += ((uint32_t) k[7 + k_idx]) << 24;
  c += k[8 + k_idx];
  c += ((uint32_t) k[9 + k_idx]) << 8;
  c += ((uint32_t) k[10 + k_idx]) << 16;
  c += ((uint32_t) k[11 + k_idx]) << 24;
  {
    helper_helper_helper_hashlittle_2_1_1(&a, &b, &c);
  }
  ;
  length -= 12;
  k_idx += 12;
  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
  *k_idx_ref = k_idx;
}


----------------------------
***/


// hint:  ['length_ref is a mutable refrence to size_t', 'a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t', 'k_idx_ref is a mutable refrence to unsigned int']
void helper_helper_hashlittle_3_1(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, unsigned int * const k_idx_ref, const uint16_t * const k)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  unsigned int k_idx = *k_idx_ref;
  a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
  b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
  c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
  {
    helper_helper_helper_hashlittle_3_1_1(&a, &b, &c);
  }
  ;
  length -= 12;
  k_idx += 6;
  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
  *k_idx_ref = k_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_hashlittle_3_1_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  a -= c;
  a ^= (c << 4) | (c >> (32 - 4));
  c += b;
  b -= a;
  b ^= (a << 6) | (a >> (32 - 6));
  a += c;
  c -= b;
  c ^= (b << 8) | (b >> (32 - 8));
  b += a;
  a -= c;
  a ^= (c << 16) | (c >> (32 - 16));
  c += b;
  b -= a;
  b ^= (a << 19) | (a >> (32 - 19));
  a += c;
  c -= b;
  c ^= (b << 4) | (b >> (32 - 4));
  b += a;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
***/


// hint:  ['length_ref is a mutable refrence to size_t', 'a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
uint32_t helper_hashlittle_3(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, const void * const key)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  const uint16_t *k = (const uint16_t *) key;
  unsigned int k_idx = 0;
  const uint8_t *k8;
  unsigned int k8_idx = 0;
  while (length > 12)
  {
    helper_helper_hashlittle_3_1(&length, &a, &b, &c, &k_idx, k);
  }

  k8_idx = (const uint8_t *) k;
  switch (length)
  {
    case 12:
    {
      c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 11:
    {
      c += ((uint32_t) k8[10 + k8_idx]) << 16;
    }

    case 10:
    {
      c += k[4 + k_idx];
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 9:
    {
      c += k8[8 + k8_idx];
    }

    case 8:
    {
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 7:
    {
      b += ((uint32_t) k8[6 + k8_idx]) << 16;
    }

    case 6:
    {
      b += k[2 + k_idx];
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 5:
    {
      b += k8[4 + k8_idx];
    }

    case 4:
    {
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 3:
    {
      a += ((uint32_t) k8[2 + k8_idx]) << 16;
    }

    case 2:
    {
      a += k[0 + k_idx];
      break;
    }

    case 1:
    {
      a += k8[0 + k8_idx];
      break;
    }

    case 0:
    {
      return c;
    }

  }

  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_hashlittle_3_1(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, unsigned int * const k_idx_ref, const uint16_t * const k)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  unsigned int k_idx = *k_idx_ref;
  a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
  b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
  c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
  {
    helper_helper_helper_hashlittle_3_1_1(&a, &b, &c);
  }
  ;
  length -= 12;
  k_idx += 6;
  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
  *k_idx_ref = k_idx;
}


----------------------------
***/


// hint:  ['length_ref is a mutable refrence to size_t', 'a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t', 'k_idx_ref is a mutable refrence to unsigned int']
void helper_helper_hashlittle_4_1(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, unsigned int * const k_idx_ref, const uint32_t * const k)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  unsigned int k_idx = *k_idx_ref;
  a += k[0 + k_idx];
  b += k[1 + k_idx];
  c += k[2 + k_idx];
  {
    helper_helper_helper_hashlittle_4_1_1(&a, &b, &c);
  }
  ;
  length -= 12;
  k_idx += 3;
  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
  *k_idx_ref = k_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_hashlittle_4_1_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  a -= c;
  a ^= (c << 4) | (c >> (32 - 4));
  c += b;
  b -= a;
  b ^= (a << 6) | (a >> (32 - 6));
  a += c;
  c -= b;
  c ^= (b << 8) | (b >> (32 - 8));
  b += a;
  a -= c;
  a ^= (c << 16) | (c >> (32 - 16));
  c += b;
  b -= a;
  b ^= (a << 19) | (a >> (32 - 19));
  a += c;
  c -= b;
  c ^= (b << 4) | (b >> (32 - 4));
  b += a;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
***/


// hint:  ['length_ref is a mutable refrence to size_t', 'a_ref is a mutable refrence to uint32_t', 'b_ref is a mutable refrence to uint32_t', 'c_ref is a mutable refrence to uint32_t']
uint32_t helper_hashlittle_4(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, const void * const key)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  const uint32_t *k = (const uint32_t *) key;
  unsigned int k_idx = 0;
  while (length > 12)
  {
    helper_helper_hashlittle_4_1(&length, &a, &b, &c, &k_idx, k);
  }

  switch (length)
  {
    case 12:
    {
      c += k[2 + k_idx];
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 11:
    {
      c += k[2 + k_idx] & 0xffffff;
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 10:
    {
      c += k[2 + k_idx] & 0xffff;
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 9:
    {
      c += k[2 + k_idx] & 0xff;
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 8:
    {
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 7:
    {
      b += k[1 + k_idx] & 0xffffff;
      a += k[0 + k_idx];
      break;
    }

    case 6:
    {
      b += k[1 + k_idx] & 0xffff;
      a += k[0 + k_idx];
      break;
    }

    case 5:
    {
      b += k[1 + k_idx] & 0xff;
      a += k[0 + k_idx];
      break;
    }

    case 4:
    {
      a += k[0 + k_idx];
      break;
    }

    case 3:
    {
      a += k[0 + k_idx] & 0xffffff;
      break;
    }

    case 2:
    {
      a += k[0 + k_idx] & 0xffff;
      break;
    }

    case 1:
    {
      a += k[0 + k_idx] & 0xff;
      break;
    }

    case 0:
    {
      return c;
    }

  }

  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_hashlittle_4_1(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, unsigned int * const k_idx_ref, const uint32_t * const k)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  unsigned int k_idx = *k_idx_ref;
  a += k[0 + k_idx];
  b += k[1 + k_idx];
  c += k[2 + k_idx];
  {
    helper_helper_helper_hashlittle_4_1_1(&a, &b, &c);
  }
  ;
  length -= 12;
  k_idx += 3;
  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
  *k_idx_ref = k_idx;
}


----------------------------
***/


struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h)
{
  unsigned long n = h % t->size;
  int count = 0;
  while (count < t->size)
  {
    if (t->table[n].k == ((void *) (-1)))
    {
      return 0;
    }
    if ((t->table[n].k != ((void *) (-2))) && t->equal_fn(t->table[n].k, k))
    {
      return &t->table[n];
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
    count += 1;
  }

  return 0;
}


/*** DEPENDENCIES:
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
***/


struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn)
{
  int i;
  struct lh_table *t;
  unsigned int t_idx = 0;
  assert(size > 0);
  t_idx = (struct lh_table *) calloc(1, sizeof(struct lh_table));
  if (!(&t[t_idx]))
  {
    return 0;
  }
  t->count = 0;
  t->size = size;
  t->table = (struct lh_entry *) calloc(size, sizeof(struct lh_entry));
  if (!t->table)
  {
    free(t);
    return 0;
  }
  t->free_fn = free_fn;
  t->hash_fn = hash_fn;
  t->equal_fn = equal_fn;
  for (i = 0; i < size; i += 1)
  {
    t->table[i].k = (void *) (-1);
  }

  return t;
}


/*** DEPENDENCIES:
typedef void lh_entry_free_fn(struct lh_entry *e)
----------------------------
typedef unsigned long lh_hash_fn(const void *k)
----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
typedef int lh_equal_fn(const void *k1, const void *k2)
----------------------------
***/


struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn)
{
  return lh_table_new(size, free_fn, char_hash_fn, lh_char_equal);
}


/*** DEPENDENCIES:
static lh_hash_fn *char_hash_fn = lh_char_hash
----------------------------
typedef void lh_entry_free_fn(struct lh_entry *e)
----------------------------
struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn)
{
  int i;
  struct lh_table *t;
  unsigned int t_idx = 0;
  assert(size > 0);
  t_idx = (struct lh_table *) calloc(1, sizeof(struct lh_table));
  if (!(&t[t_idx]))
  {
    return 0;
  }
  t->count = 0;
  t->size = size;
  t->table = (struct lh_entry *) calloc(size, sizeof(struct lh_entry));
  if (!t->table)
  {
    free(t);
    return 0;
  }
  t->free_fn = free_fn;
  t->hash_fn = hash_fn;
  t->equal_fn = equal_fn;
  for (i = 0; i < size; i += 1)
  {
    t->table[i].k = (void *) (-1);
  }

  return t;
}


----------------------------
int lh_char_equal(const void *k1, const void *k2)
{
  return strcmp((const char *) k1, (const char *) k2) == 0;
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
***/


struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k)
{
  return lh_table_lookup_entry_w_hash(t, k, lh_get_hash(t, k));
}


/*** DEPENDENCIES:
struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h)
{
  unsigned long n = h % t->size;
  int count = 0;
  while (count < t->size)
  {
    if (t->table[n].k == ((void *) (-1)))
    {
      return 0;
    }
    if ((t->table[n].k != ((void *) (-2))) && t->equal_fn(t->table[n].k, k))
    {
      return &t->table[n];
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
    count += 1;
  }

  return 0;
}


----------------------------
inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
***/


json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (e != 0)
  {
    if (v != 0)
    {
      *v = lh_entry_v(e);
    }
    return 1;
  }
  if (v != 0)
  {
    *v = 0;
  }
  return 0;
}


/*** DEPENDENCIES:
inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k)
{
  return lh_table_lookup_entry_w_hash(t, k, lh_get_hash(t, k));
}


----------------------------
***/


int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e)
{
  ptrdiff_t n = (ptrdiff_t) (e - t->table);
  if (n < 0)
  {
    return -2;
  }
  if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
  {
    return -1;
  }
  t->count -= 1;
  if (t->free_fn)
  {
    t->free_fn(e);
  }
  t->table[n].v = 0;
  t->table[n].k = (void *) (-2);
  if ((t->tail == (&t->table[n])) && (t->head == (&t->table[n])))
  {
    t->head = (t->tail = 0);
  }
  else
    if (t->head == (&t->table[n]))
  {
    t->head->next->prev = 0;
    t->head = t->head->next;
  }
  else
    if (t->tail == (&t->table[n]))
  {
    t->tail->prev->next = 0;
    t->tail = t->tail->prev;
  }
  else
  {
    t->table[n].prev->next = t->table[n].next;
    t->table[n].next->prev = t->table[n].prev;
  }
  t->table[n].next = (t->table[n].prev = 0);
  return 0;
}


/*** DEPENDENCIES:
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
***/


static uint32_t hashlittle(const void *key, size_t length, uint32_t initval)
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  union 
  {
    const void *ptr;
    size_t i;
  } u;
  a = (b = (c = (0xdeadbeef + ((uint32_t) length)) + initval));
  u.ptr = key;
  if (1 && ((u.i & 0x3) == 0))
  {
    helper_hashlittle_4(&length, &a, &b, &c, key);
  }
  else
    if (1 && ((u.i & 0x1) == 0))
  {
    helper_hashlittle_3(&length, &a, &b, &c, key);
  }
  else
  {
    helper_hashlittle_2(&length, &a, &b, &c, key);
  }
  {
    helper_hashlittle_1(&a, &b, &c);
  }
  ;
  return c;
}


/*** DEPENDENCIES:
uint32_t helper_hashlittle_2(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, const void * const key)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  const uint8_t *k = (const uint8_t *) key;
  unsigned int k_idx = 0;
  while (length > 12)
  {
    helper_helper_hashlittle_2_1(&length, &a, &b, &c, &k_idx, k);
  }

  switch (length)
  {
    case 12:
    {
      c += ((uint32_t) k[11 + k_idx]) << 24;
    }

    case 11:
    {
      c += ((uint32_t) k[10 + k_idx]) << 16;
    }

    case 10:
    {
      c += ((uint32_t) k[9 + k_idx]) << 8;
    }

    case 9:
    {
      c += k[8 + k_idx];
    }

    case 8:
    {
      b += ((uint32_t) k[7 + k_idx]) << 24;
    }

    case 7:
    {
      b += ((uint32_t) k[6 + k_idx]) << 16;
    }

    case 6:
    {
      b += ((uint32_t) k[5 + k_idx]) << 8;
    }

    case 5:
    {
      b += k[4 + k_idx];
    }

    case 4:
    {
      a += ((uint32_t) k[3 + k_idx]) << 24;
    }

    case 3:
    {
      a += ((uint32_t) k[2 + k_idx]) << 16;
    }

    case 2:
    {
      a += ((uint32_t) k[1 + k_idx]) << 8;
    }

    case 1:
    {
      a += k[0 + k_idx];
      break;
    }

    case 0:
    {
      return c;
    }

  }

  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
uint32_t helper_hashlittle_3(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, const void * const key)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  const uint16_t *k = (const uint16_t *) key;
  unsigned int k_idx = 0;
  const uint8_t *k8;
  unsigned int k8_idx = 0;
  while (length > 12)
  {
    helper_helper_hashlittle_3_1(&length, &a, &b, &c, &k_idx, k);
  }

  k8_idx = (const uint8_t *) k;
  switch (length)
  {
    case 12:
    {
      c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 11:
    {
      c += ((uint32_t) k8[10 + k8_idx]) << 16;
    }

    case 10:
    {
      c += k[4 + k_idx];
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 9:
    {
      c += k8[8 + k8_idx];
    }

    case 8:
    {
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 7:
    {
      b += ((uint32_t) k8[6 + k8_idx]) << 16;
    }

    case 6:
    {
      b += k[2 + k_idx];
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 5:
    {
      b += k8[4 + k8_idx];
    }

    case 4:
    {
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      break;
    }

    case 3:
    {
      a += ((uint32_t) k8[2 + k8_idx]) << 16;
    }

    case 2:
    {
      a += k[0 + k_idx];
      break;
    }

    case 1:
    {
      a += k8[0 + k8_idx];
      break;
    }

    case 0:
    {
      return c;
    }

  }

  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
void helper_hashlittle_1(uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref)
{
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  c ^= b;
  c -= (b << 14) | (b >> (32 - 14));
  a ^= c;
  a -= (c << 11) | (c >> (32 - 11));
  b ^= a;
  b -= (a << 25) | (a >> (32 - 25));
  c ^= b;
  c -= (b << 16) | (b >> (32 - 16));
  a ^= c;
  a -= (c << 4) | (c >> (32 - 4));
  b ^= a;
  b -= (a << 14) | (a >> (32 - 14));
  c ^= b;
  c -= (b << 24) | (b >> (32 - 24));
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
uint32_t helper_hashlittle_4(size_t * const length_ref, uint32_t * const a_ref, uint32_t * const b_ref, uint32_t * const c_ref, const void * const key)
{
  size_t length = *length_ref;
  uint32_t a = *a_ref;
  uint32_t b = *b_ref;
  uint32_t c = *c_ref;
  const uint32_t *k = (const uint32_t *) key;
  unsigned int k_idx = 0;
  while (length > 12)
  {
    helper_helper_hashlittle_4_1(&length, &a, &b, &c, &k_idx, k);
  }

  switch (length)
  {
    case 12:
    {
      c += k[2 + k_idx];
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 11:
    {
      c += k[2 + k_idx] & 0xffffff;
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 10:
    {
      c += k[2 + k_idx] & 0xffff;
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 9:
    {
      c += k[2 + k_idx] & 0xff;
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 8:
    {
      b += k[1 + k_idx];
      a += k[0 + k_idx];
      break;
    }

    case 7:
    {
      b += k[1 + k_idx] & 0xffffff;
      a += k[0 + k_idx];
      break;
    }

    case 6:
    {
      b += k[1 + k_idx] & 0xffff;
      a += k[0 + k_idx];
      break;
    }

    case 5:
    {
      b += k[1 + k_idx] & 0xff;
      a += k[0 + k_idx];
      break;
    }

    case 4:
    {
      a += k[0 + k_idx];
      break;
    }

    case 3:
    {
      a += k[0 + k_idx] & 0xffffff;
      break;
    }

    case 2:
    {
      a += k[0 + k_idx] & 0xffff;
      break;
    }

    case 1:
    {
      a += k[0 + k_idx] & 0xff;
      break;
    }

    case 0:
    {
      return c;
    }

  }

  *length_ref = length;
  *a_ref = a;
  *b_ref = b;
  *c_ref = c;
}


----------------------------
***/


static unsigned long lh_char_hash(const void *k)
{
  static volatile int random_seed = -1;
  if (random_seed == (-1))
  {
    int seed;
    while ((seed = json_c_get_random_seed()) == (-1))
    {
    }

    (void) __sync_val_compare_and_swap(&random_seed, -1, seed);
  }
  return hashlittle((const char *) k, strlen((const char *) k), (uint32_t) random_seed);
}


/*** DEPENDENCIES:
static uint32_t hashlittle(const void *key, size_t length, uint32_t initval)
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  union 
  {
    const void *ptr;
    size_t i;
  } u;
  a = (b = (c = (0xdeadbeef + ((uint32_t) length)) + initval));
  u.ptr = key;
  if (1 && ((u.i & 0x3) == 0))
  {
    helper_hashlittle_4(&length, &a, &b, &c, key);
  }
  else
    if (1 && ((u.i & 0x1) == 0))
  {
    helper_hashlittle_3(&length, &a, &b, &c, key);
  }
  else
  {
    helper_hashlittle_2(&length, &a, &b, &c, key);
  }
  {
    helper_hashlittle_1(&a, &b, &c);
  }
  ;
  return c;
}


----------------------------
int json_c_get_random_seed(void)
{
  return arc4random();
}


----------------------------
***/


int json_global_set_string_hash(const int h)
{
  switch (h)
  {
    case 0:
    {
      char_hash_fn = lh_char_hash;
      break;
    }

    case 1:
    {
      char_hash_fn = lh_perllike_str_hash;
      break;
    }

    default:
    {
      return -1;
    }

  }

  return 0;
}


/*** DEPENDENCIES:
static unsigned long lh_char_hash(const void *k)
{
  static volatile int random_seed = -1;
  if (random_seed == (-1))
  {
    int seed;
    while ((seed = json_c_get_random_seed()) == (-1))
    {
    }

    (void) __sync_val_compare_and_swap(&random_seed, -1, seed);
  }
  return hashlittle((const char *) k, strlen((const char *) k), (uint32_t) random_seed);
}


----------------------------
static lh_hash_fn *char_hash_fn = lh_char_hash
----------------------------
static unsigned long lh_perllike_str_hash(const void *k)
{
  const char *rkey = (const char *) k;
  unsigned int rkey_idx = 0;
  unsigned hashval = 1;
  while (rkey[rkey_idx])
  {
    hashval = (hashval * 33) + rkey[rkey_idx];
    rkey_idx += 1;
  }

  return hashval;
}


----------------------------
***/


int lh_table_insert(struct lh_table *t, const void *k, const void *v)
{
  return lh_table_insert_w_hash(t, k, v, lh_get_hash(t, k), 0);
}


/*** DEPENDENCIES:
inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}


----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
None
----------------------------
***/


int lh_table_delete(struct lh_table *t, const void *k)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (!e)
  {
    return -1;
  }
  return lh_table_delete_entry(t, e);
}


/*** DEPENDENCIES:
int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e)
{
  ptrdiff_t n = (ptrdiff_t) (e - t->table);
  if (n < 0)
  {
    return -2;
  }
  if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
  {
    return -1;
  }
  t->count -= 1;
  if (t->free_fn)
  {
    t->free_fn(e);
  }
  t->table[n].v = 0;
  t->table[n].k = (void *) (-2);
  if ((t->tail == (&t->table[n])) && (t->head == (&t->table[n])))
  {
    t->head = (t->tail = 0);
  }
  else
    if (t->head == (&t->table[n]))
  {
    t->head->next->prev = 0;
    t->head = t->head->next;
  }
  else
    if (t->tail == (&t->table[n]))
  {
    t->tail->prev->next = 0;
    t->tail = t->tail->prev;
  }
  else
  {
    t->table[n].prev->next = t->table[n].next;
    t->table[n].next->prev = t->table[n].prev;
  }
  t->table[n].next = (t->table[n].prev = 0);
  return 0;
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k)
{
  return lh_table_lookup_entry_w_hash(t, k, lh_get_hash(t, k));
}


----------------------------
***/


struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn)
{
  return lh_table_new(size, free_fn, lh_ptr_hash, lh_ptr_equal);
}


/*** DEPENDENCIES:
typedef void lh_entry_free_fn(struct lh_entry *e)
----------------------------
struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn)
{
  int i;
  struct lh_table *t;
  unsigned int t_idx = 0;
  assert(size > 0);
  t_idx = (struct lh_table *) calloc(1, sizeof(struct lh_table));
  if (!(&t[t_idx]))
  {
    return 0;
  }
  t->count = 0;
  t->size = size;
  t->table = (struct lh_entry *) calloc(size, sizeof(struct lh_entry));
  if (!t->table)
  {
    free(t);
    return 0;
  }
  t->free_fn = free_fn;
  t->hash_fn = hash_fn;
  t->equal_fn = equal_fn;
  for (i = 0; i < size; i += 1)
  {
    t->table[i].k = (void *) (-1);
  }

  return t;
}


----------------------------
int lh_ptr_equal(const void *k1, const void *k2)
{
  return k1 == k2;
}


----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
----------------------------
static unsigned long lh_ptr_hash(const void *k)
{
  return (unsigned long) (((((ptrdiff_t) k) * 0x9e370001UL) >> 4) & 18446744073709551615UL);
}


----------------------------
***/


