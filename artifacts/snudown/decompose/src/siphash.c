// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_5(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_helper_siphash_nocase_7_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_helper_siphash_nocase_7_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t', 'm_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_7(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref, uint64_t * const m_ref, const uint8_t * const in, unsigned int in_idx)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  uint64_t m = *m_ref;
  m = ((((((((uint64_t) tolower(in[0 + in_idx])) | (((uint64_t) tolower(in[1 + in_idx])) << 8)) | (((uint64_t) tolower(in[2 + in_idx])) << 16)) | (((uint64_t) tolower(in[3 + in_idx])) << 24)) | (((uint64_t) tolower(in[4 + in_idx])) << 32)) | (((uint64_t) tolower(in[5 + in_idx])) << 40)) | (((uint64_t) tolower(in[6 + in_idx])) << 48)) | (((uint64_t) tolower(in[7 + in_idx])) << 56);
  v3 ^= m;
  do
  {
    helper_helper_siphash_nocase_7_1(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_helper_siphash_nocase_7_2(&v0, &v1, &v2, &v3);
  }
  while (0);
  v0 ^= m;
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
  *m_ref = m;
}


/*** DEPENDENCIES:
void helper_helper_siphash_nocase_7_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_helper_siphash_nocase_7_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_6(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_3(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_nocase_4(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k)
{
  unsigned int in_idx = 0;
  uint64_t hash;
  uint8_t *out = (uint8_t *) (&hash);
  uint64_t v0 = 0x736f6d6570736575ULL;
  uint64_t v1 = 0x646f72616e646f6dULL;
  uint64_t v2 = 0x6c7967656e657261ULL;
  uint64_t v3 = 0x7465646279746573ULL;
  uint64_t k0 = ((((((((uint64_t) k[0]) | (((uint64_t) k[1]) << 8)) | (((uint64_t) k[2]) << 16)) | (((uint64_t) k[3]) << 24)) | (((uint64_t) k[4]) << 32)) | (((uint64_t) k[5]) << 40)) | (((uint64_t) k[6]) << 48)) | (((uint64_t) k[7]) << 56);
  uint64_t k1 = ((((((((uint64_t) (k + 8)[0]) | (((uint64_t) (k + 8)[1]) << 8)) | (((uint64_t) (k + 8)[2]) << 16)) | (((uint64_t) (k + 8)[3]) << 24)) | (((uint64_t) (k + 8)[4]) << 32)) | (((uint64_t) (k + 8)[5]) << 40)) | (((uint64_t) (k + 8)[6]) << 48)) | (((uint64_t) (k + 8)[7]) << 56);
  uint64_t m;
  const uint8_t *end = ((&in[in_idx]) + inlen) - (inlen % (sizeof(uint64_t)));
  const int left = inlen & 7;
  uint64_t b = ((uint64_t) inlen) << 56;
  v3 ^= k1;
  v2 ^= k0;
  v1 ^= k1;
  v0 ^= k0;
  for (; (&in[in_idx]) != end; in_idx += 8)
  {
    helper_siphash_nocase_7(&v0, &v1, &v2, &v3, &m, in, in_idx);
  }

  switch (left)
  {
    case 7:
    {
      b |= ((uint64_t) tolower(in[6 + in_idx])) << 48;
    }

    case 6:
    {
      b |= ((uint64_t) tolower(in[5 + in_idx])) << 40;
    }

    case 5:
    {
      b |= ((uint64_t) tolower(in[4 + in_idx])) << 32;
    }

    case 4:
    {
      b |= ((uint64_t) tolower(in[3 + in_idx])) << 24;
    }

    case 3:
    {
      b |= ((uint64_t) tolower(in[2 + in_idx])) << 16;
    }

    case 2:
    {
      b |= ((uint64_t) tolower(in[1 + in_idx])) << 8;
    }

    case 1:
    {
      b |= (uint64_t) tolower(in[0 + in_idx]);
      break;
    }

    case 0:
    {
      break;
    }

  }

  v3 ^= b;
  do
  {
    helper_siphash_nocase_1(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_nocase_2(&v0, &v1, &v2, &v3);
  }
  while (0);
  v0 ^= b;
  v2 ^= 0xff;
  do
  {
    helper_siphash_nocase_3(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_nocase_4(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_nocase_5(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_nocase_6(&v0, &v1, &v2, &v3);
  }
  while (0);
  b = ((v0 ^ v1) ^ v2) ^ v3;
  out[0] = (uint8_t) ((uint32_t) b);
  out[1] = (uint8_t) (((uint32_t) b) >> 8);
  out[2] = (uint8_t) (((uint32_t) b) >> 16);
  out[3] = (uint8_t) (((uint32_t) b) >> 24);
  ;
  (out + 4)[0] = (uint8_t) ((uint32_t) (b >> 32));
  (out + 4)[1] = (uint8_t) (((uint32_t) (b >> 32)) >> 8);
  (out + 4)[2] = (uint8_t) (((uint32_t) (b >> 32)) >> 16);
  (out + 4)[3] = (uint8_t) (((uint32_t) (b >> 32)) >> 24);
  ;
  ;
  return hash;
}


/*** DEPENDENCIES:
void helper_siphash_nocase_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_nocase_5(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_nocase_7(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref, uint64_t * const m_ref, const uint8_t * const in, unsigned int in_idx)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  uint64_t m = *m_ref;
  m = ((((((((uint64_t) tolower(in[0 + in_idx])) | (((uint64_t) tolower(in[1 + in_idx])) << 8)) | (((uint64_t) tolower(in[2 + in_idx])) << 16)) | (((uint64_t) tolower(in[3 + in_idx])) << 24)) | (((uint64_t) tolower(in[4 + in_idx])) << 32)) | (((uint64_t) tolower(in[5 + in_idx])) << 40)) | (((uint64_t) tolower(in[6 + in_idx])) << 48)) | (((uint64_t) tolower(in[7 + in_idx])) << 56);
  v3 ^= m;
  do
  {
    helper_helper_siphash_nocase_7_1(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_helper_siphash_nocase_7_2(&v0, &v1, &v2, &v3);
  }
  while (0);
  v0 ^= m;
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
  *m_ref = m;
}


----------------------------
void helper_siphash_nocase_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_nocase_6(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_nocase_3(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_nocase_4(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_3(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_4(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_5(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_siphash_6(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_helper_siphash_7_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t']
void helper_helper_siphash_7_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


/*** DEPENDENCIES:
***/


// hint:  ['v0_ref is a mutable refrence to uint64_t', 'v1_ref is a mutable refrence to uint64_t', 'v2_ref is a mutable refrence to uint64_t', 'v3_ref is a mutable refrence to uint64_t', 'm_ref is a mutable refrence to uint64_t']
void helper_siphash_7(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref, uint64_t * const m_ref, const uint8_t * const in, unsigned int in_idx)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  uint64_t m = *m_ref;
  m = ((((((((uint64_t) in[0 + in_idx]) | (((uint64_t) in[1 + in_idx]) << 8)) | (((uint64_t) in[2 + in_idx]) << 16)) | (((uint64_t) in[3 + in_idx]) << 24)) | (((uint64_t) in[4 + in_idx]) << 32)) | (((uint64_t) in[5 + in_idx]) << 40)) | (((uint64_t) in[6 + in_idx]) << 48)) | (((uint64_t) in[7 + in_idx]) << 56);
  v3 ^= m;
  do
  {
    helper_helper_siphash_7_1(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_helper_siphash_7_2(&v0, &v1, &v2, &v3);
  }
  while (0);
  v0 ^= m;
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
  *m_ref = m;
}


/*** DEPENDENCIES:
void helper_helper_siphash_7_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_helper_siphash_7_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
***/


uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k)
{
  unsigned int in_idx = 0;
  uint64_t hash;
  uint8_t *out = (uint8_t *) (&hash);
  uint64_t v0 = 0x736f6d6570736575ULL;
  uint64_t v1 = 0x646f72616e646f6dULL;
  uint64_t v2 = 0x6c7967656e657261ULL;
  uint64_t v3 = 0x7465646279746573ULL;
  uint64_t k0 = ((((((((uint64_t) k[0]) | (((uint64_t) k[1]) << 8)) | (((uint64_t) k[2]) << 16)) | (((uint64_t) k[3]) << 24)) | (((uint64_t) k[4]) << 32)) | (((uint64_t) k[5]) << 40)) | (((uint64_t) k[6]) << 48)) | (((uint64_t) k[7]) << 56);
  uint64_t k1 = ((((((((uint64_t) (k + 8)[0]) | (((uint64_t) (k + 8)[1]) << 8)) | (((uint64_t) (k + 8)[2]) << 16)) | (((uint64_t) (k + 8)[3]) << 24)) | (((uint64_t) (k + 8)[4]) << 32)) | (((uint64_t) (k + 8)[5]) << 40)) | (((uint64_t) (k + 8)[6]) << 48)) | (((uint64_t) (k + 8)[7]) << 56);
  uint64_t m;
  const uint8_t *end = ((&in[in_idx]) + inlen) - (inlen % (sizeof(uint64_t)));
  const int left = inlen & 7;
  uint64_t b = ((uint64_t) inlen) << 56;
  v3 ^= k1;
  v2 ^= k0;
  v1 ^= k1;
  v0 ^= k0;
  for (; (&in[in_idx]) != end; in_idx += 8)
  {
    helper_siphash_7(&v0, &v1, &v2, &v3, &m, in, in_idx);
  }

  switch (left)
  {
    case 7:
    {
      b |= ((uint64_t) in[6 + in_idx]) << 48;
    }

    case 6:
    {
      b |= ((uint64_t) in[5 + in_idx]) << 40;
    }

    case 5:
    {
      b |= ((uint64_t) in[4 + in_idx]) << 32;
    }

    case 4:
    {
      b |= ((uint64_t) in[3 + in_idx]) << 24;
    }

    case 3:
    {
      b |= ((uint64_t) in[2 + in_idx]) << 16;
    }

    case 2:
    {
      b |= ((uint64_t) in[1 + in_idx]) << 8;
    }

    case 1:
    {
      b |= (uint64_t) in[0 + in_idx];
      break;
    }

    case 0:
    {
      break;
    }

  }

  v3 ^= b;
  do
  {
    helper_siphash_1(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_2(&v0, &v1, &v2, &v3);
  }
  while (0);
  v0 ^= b;
  v2 ^= 0xff;
  do
  {
    helper_siphash_3(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_4(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_5(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_siphash_6(&v0, &v1, &v2, &v3);
  }
  while (0);
  b = ((v0 ^ v1) ^ v2) ^ v3;
  out[0] = (uint8_t) ((uint32_t) b);
  out[1] = (uint8_t) (((uint32_t) b) >> 8);
  out[2] = (uint8_t) (((uint32_t) b) >> 16);
  out[3] = (uint8_t) (((uint32_t) b) >> 24);
  ;
  (out + 4)[0] = (uint8_t) ((uint32_t) (b >> 32));
  (out + 4)[1] = (uint8_t) (((uint32_t) (b >> 32)) >> 8);
  (out + 4)[2] = (uint8_t) (((uint32_t) (b >> 32)) >> 16);
  (out + 4)[3] = (uint8_t) (((uint32_t) (b >> 32)) >> 24);
  ;
  ;
  return hash;
}


/*** DEPENDENCIES:
void helper_siphash_3(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_2(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_4(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_5(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_7(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref, uint64_t * const m_ref, const uint8_t * const in, unsigned int in_idx)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  uint64_t m = *m_ref;
  m = ((((((((uint64_t) in[0 + in_idx]) | (((uint64_t) in[1 + in_idx]) << 8)) | (((uint64_t) in[2 + in_idx]) << 16)) | (((uint64_t) in[3 + in_idx]) << 24)) | (((uint64_t) in[4 + in_idx]) << 32)) | (((uint64_t) in[5 + in_idx]) << 40)) | (((uint64_t) in[6 + in_idx]) << 48)) | (((uint64_t) in[7 + in_idx]) << 56);
  v3 ^= m;
  do
  {
    helper_helper_siphash_7_1(&v0, &v1, &v2, &v3);
  }
  while (0);
  do
  {
    helper_helper_siphash_7_2(&v0, &v1, &v2, &v3);
  }
  while (0);
  v0 ^= m;
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
  *m_ref = m;
}


----------------------------
void helper_siphash_6(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
void helper_siphash_1(uint64_t * const v0_ref, uint64_t * const v1_ref, uint64_t * const v2_ref, uint64_t * const v3_ref)
{
  uint64_t v0 = *v0_ref;
  uint64_t v1 = *v1_ref;
  uint64_t v2 = *v2_ref;
  uint64_t v3 = *v3_ref;
  v0 += v1;
  v1 = (uint64_t) ((v1 << 13) | (v1 >> (64 - 13)));
  v1 ^= v0;
  v0 = (uint64_t) ((v0 << 32) | (v0 >> (64 - 32)));
  v2 += v3;
  v3 = (uint64_t) ((v3 << 16) | (v3 >> (64 - 16)));
  v3 ^= v2;
  v0 += v3;
  v3 = (uint64_t) ((v3 << 21) | (v3 >> (64 - 21)));
  v3 ^= v0;
  v2 += v1;
  v1 = (uint64_t) ((v1 << 17) | (v1 >> (64 - 17)));
  v1 ^= v2;
  v2 = (uint64_t) ((v2 << 32) | (v2 >> (64 - 32)));
  *v0_ref = v0;
  *v1_ref = v1;
  *v2_ref = v2;
  *v3_ref = v3;
}


----------------------------
***/


