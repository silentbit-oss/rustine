// hint:  ['i_ref is a mutable refrence to size_t']
void helper_zsetup_1(size_t * const i_ref)
{
  size_t i = *i_ref;
  libzahl_set_up = 1;
  memset(libzahl_pool, 0, sizeof(libzahl_pool));
  memset(libzahl_pool_n, 0, sizeof(libzahl_pool_n));
  memset(libzahl_pool_alloc, 0, sizeof(libzahl_pool_alloc));
  zinit(libzahl_tmp_cmp);
  zinit(libzahl_tmp_str_num);
  zinit(libzahl_tmp_str_mag);
  zinit(libzahl_tmp_str_div);
  zinit(libzahl_tmp_str_rem);
  zinit(libzahl_tmp_gcd_u);
  zinit(libzahl_tmp_gcd_v);
  zinit(libzahl_tmp_sub);
  zinit(libzahl_tmp_modmul);
  zinit(libzahl_tmp_div);
  zinit(libzahl_tmp_mod);
  zinit(libzahl_tmp_pow_b);
  zinit(libzahl_tmp_pow_c);
  zinit(libzahl_tmp_pow_d);
  zinit(libzahl_tmp_modsqr);
  zinit(libzahl_tmp_divmod_a);
  zinit(libzahl_tmp_divmod_b);
  zinit(libzahl_tmp_divmod_d);
  zinit(libzahl_tmp_ptest_x);
  zinit(libzahl_tmp_ptest_a);
  zinit(libzahl_tmp_ptest_d);
  zinit(libzahl_tmp_ptest_n1);
  zinit(libzahl_tmp_ptest_n4);
  ;
  zinit(libzahl_const_1e19), zsetu(libzahl_const_1e19, 10000000000000000000ULL);
  zinit(libzahl_const_1e9), zsetu(libzahl_const_1e9, 1000000000ULL);
  zinit(libzahl_const_1), zsetu(libzahl_const_1, 1);
  zinit(libzahl_const_2), zsetu(libzahl_const_2, 2);
  zinit(libzahl_const_4), zsetu(libzahl_const_4, 4);
  ;
  for (i = 32; i--;)
    zinit(libzahl_tmp_divmod_ds[i]);

  *i_ref = i;
}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_mod
----------------------------
extern z_t libzahl_tmp_ptest_d
----------------------------
extern z_t libzahl_tmp_str_div
----------------------------
extern z_t libzahl_tmp_divmod_d
----------------------------
extern z_t libzahl_tmp_pow_c
----------------------------
extern z_t libzahl_tmp_ptest_a
----------------------------
extern int libzahl_set_up
----------------------------
extern z_t libzahl_tmp_ptest_n4
----------------------------
extern z_t libzahl_tmp_str_num
----------------------------
inline static void zinit(z_t a)
{
  a->alloced = 0;
  a->chars = 0;
}


----------------------------
extern z_t libzahl_tmp_pow_b
----------------------------
extern z_t libzahl_tmp_ptest_x
----------------------------
extern size_t libzahl_pool_n[(sizeof(size_t)) * 8]
----------------------------
extern z_t libzahl_tmp_sub
----------------------------
extern z_t libzahl_const_1
----------------------------
extern z_t libzahl_tmp_modsqr
----------------------------
extern z_t libzahl_tmp_gcd_u
----------------------------
extern z_t libzahl_tmp_ptest_n1
----------------------------
extern z_t libzahl_tmp_str_rem
----------------------------
extern z_t libzahl_tmp_divmod_ds[32]
----------------------------
extern zahl_char_t **libzahl_pool[(sizeof(size_t)) * 8]
----------------------------
extern z_t libzahl_tmp_div
----------------------------
extern z_t libzahl_const_4
----------------------------
extern z_t libzahl_const_1e19
----------------------------
extern z_t libzahl_tmp_cmp
----------------------------
extern z_t libzahl_const_1e9
----------------------------
extern z_t libzahl_tmp_gcd_v
----------------------------
extern z_t libzahl_tmp_pow_d
----------------------------
extern z_t libzahl_tmp_divmod_a
----------------------------
extern size_t libzahl_pool_alloc[(sizeof(size_t)) * 8]
----------------------------
extern z_t libzahl_tmp_str_mag
----------------------------
extern z_t libzahl_tmp_divmod_b
----------------------------
extern z_t libzahl_const_2
----------------------------
void zsetu(z_t a, unsigned long long int b)
{
  if (!b)
  {
    a->sign = 0;
    return;
  }
  do
  {
    if (a->alloced < ((((sizeof(b)) + (sizeof(*a->chars))) - 1) / (sizeof(*a->chars))))
    {
      libzahl_realloc(a, (((sizeof(b)) + (sizeof(*a->chars))) - 1) / (sizeof(*a->chars)));
    }
  }
  while (0);
  a->sign = 1;
  a->used = 0;
  while (b)
  {
    a->chars[a->used++] = (zahl_char_t) b;
    b >>= 32;
  }

}


----------------------------
extern z_t libzahl_tmp_modmul
----------------------------
***/


void zsetup(jmp_buf env)
{
  size_t i;
  *libzahl_jmp_buf = *env;
  if (!libzahl_set_up)
  {
    helper_zsetup_1(&i);
  }
}


/*** DEPENDENCIES:
extern jmp_buf libzahl_jmp_buf
----------------------------
extern int libzahl_set_up
----------------------------
void helper_zsetup_1(size_t * const i_ref)
{
  size_t i = *i_ref;
  libzahl_set_up = 1;
  memset(libzahl_pool, 0, sizeof(libzahl_pool));
  memset(libzahl_pool_n, 0, sizeof(libzahl_pool_n));
  memset(libzahl_pool_alloc, 0, sizeof(libzahl_pool_alloc));
  zinit(libzahl_tmp_cmp);
  zinit(libzahl_tmp_str_num);
  zinit(libzahl_tmp_str_mag);
  zinit(libzahl_tmp_str_div);
  zinit(libzahl_tmp_str_rem);
  zinit(libzahl_tmp_gcd_u);
  zinit(libzahl_tmp_gcd_v);
  zinit(libzahl_tmp_sub);
  zinit(libzahl_tmp_modmul);
  zinit(libzahl_tmp_div);
  zinit(libzahl_tmp_mod);
  zinit(libzahl_tmp_pow_b);
  zinit(libzahl_tmp_pow_c);
  zinit(libzahl_tmp_pow_d);
  zinit(libzahl_tmp_modsqr);
  zinit(libzahl_tmp_divmod_a);
  zinit(libzahl_tmp_divmod_b);
  zinit(libzahl_tmp_divmod_d);
  zinit(libzahl_tmp_ptest_x);
  zinit(libzahl_tmp_ptest_a);
  zinit(libzahl_tmp_ptest_d);
  zinit(libzahl_tmp_ptest_n1);
  zinit(libzahl_tmp_ptest_n4);
  ;
  zinit(libzahl_const_1e19), zsetu(libzahl_const_1e19, 10000000000000000000ULL);
  zinit(libzahl_const_1e9), zsetu(libzahl_const_1e9, 1000000000ULL);
  zinit(libzahl_const_1), zsetu(libzahl_const_1, 1);
  zinit(libzahl_const_2), zsetu(libzahl_const_2, 2);
  zinit(libzahl_const_4), zsetu(libzahl_const_4, 4);
  ;
  for (i = 32; i--;)
    zinit(libzahl_tmp_divmod_ds[i]);

  *i_ref = i;
}


----------------------------
***/


