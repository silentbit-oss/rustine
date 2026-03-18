// hint:  ['i_ref is a mutable refrence to size_t']
void helper_zunsetup_1(size_t * const i_ref)
{
  size_t i = *i_ref;
  libzahl_set_up = 0;
  free(libzahl_tmp_cmp->chars);
  free(libzahl_tmp_str_num->chars);
  free(libzahl_tmp_str_mag->chars);
  free(libzahl_tmp_str_div->chars);
  free(libzahl_tmp_str_rem->chars);
  free(libzahl_tmp_gcd_u->chars);
  free(libzahl_tmp_gcd_v->chars);
  free(libzahl_tmp_sub->chars);
  free(libzahl_tmp_modmul->chars);
  free(libzahl_tmp_div->chars);
  free(libzahl_tmp_mod->chars);
  free(libzahl_tmp_pow_b->chars);
  free(libzahl_tmp_pow_c->chars);
  free(libzahl_tmp_pow_d->chars);
  free(libzahl_tmp_modsqr->chars);
  free(libzahl_tmp_divmod_a->chars);
  free(libzahl_tmp_divmod_b->chars);
  free(libzahl_tmp_divmod_d->chars);
  free(libzahl_tmp_ptest_x->chars);
  free(libzahl_tmp_ptest_a->chars);
  free(libzahl_tmp_ptest_d->chars);
  free(libzahl_tmp_ptest_n1->chars);
  free(libzahl_tmp_ptest_n4->chars);
  ;
  free(libzahl_const_1e19->chars);
  free(libzahl_const_1e9->chars);
  free(libzahl_const_1->chars);
  free(libzahl_const_2->chars);
  free(libzahl_const_4->chars);
  ;
  for (i = 32; i--;)
    free(libzahl_tmp_divmod_ds[i]->chars);

  for (i = (sizeof(libzahl_pool)) / (sizeof(*libzahl_pool)); i--;)
  {
    while (libzahl_pool_n[i]--)
      free(libzahl_pool[i][libzahl_pool_n[i]]);

    free(libzahl_pool[i]);
  }

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
extern z_t libzahl_tmp_pow_b
----------------------------
extern z_t libzahl_tmp_ptest_x
----------------------------
extern z_t libzahl_const_1
----------------------------
extern z_t libzahl_tmp_sub
----------------------------
extern size_t libzahl_pool_n[(sizeof(size_t)) * 8]
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
extern z_t libzahl_tmp_str_mag
----------------------------
extern z_t libzahl_tmp_divmod_b
----------------------------
extern z_t libzahl_const_2
----------------------------
extern z_t libzahl_tmp_modmul
----------------------------
***/


void zunsetup(void)
{
  size_t i;
  if (libzahl_set_up)
  {
    helper_zunsetup_1(&i);
  }
}


/*** DEPENDENCIES:
extern int libzahl_set_up
----------------------------
void helper_zunsetup_1(size_t * const i_ref)
{
  size_t i = *i_ref;
  libzahl_set_up = 0;
  free(libzahl_tmp_cmp->chars);
  free(libzahl_tmp_str_num->chars);
  free(libzahl_tmp_str_mag->chars);
  free(libzahl_tmp_str_div->chars);
  free(libzahl_tmp_str_rem->chars);
  free(libzahl_tmp_gcd_u->chars);
  free(libzahl_tmp_gcd_v->chars);
  free(libzahl_tmp_sub->chars);
  free(libzahl_tmp_modmul->chars);
  free(libzahl_tmp_div->chars);
  free(libzahl_tmp_mod->chars);
  free(libzahl_tmp_pow_b->chars);
  free(libzahl_tmp_pow_c->chars);
  free(libzahl_tmp_pow_d->chars);
  free(libzahl_tmp_modsqr->chars);
  free(libzahl_tmp_divmod_a->chars);
  free(libzahl_tmp_divmod_b->chars);
  free(libzahl_tmp_divmod_d->chars);
  free(libzahl_tmp_ptest_x->chars);
  free(libzahl_tmp_ptest_a->chars);
  free(libzahl_tmp_ptest_d->chars);
  free(libzahl_tmp_ptest_n1->chars);
  free(libzahl_tmp_ptest_n4->chars);
  ;
  free(libzahl_const_1e19->chars);
  free(libzahl_const_1e9->chars);
  free(libzahl_const_1->chars);
  free(libzahl_const_2->chars);
  free(libzahl_const_4->chars);
  ;
  for (i = 32; i--;)
    free(libzahl_tmp_divmod_ds[i]->chars);

  for (i = (sizeof(libzahl_pool)) / (sizeof(*libzahl_pool)); i--;)
  {
    while (libzahl_pool_n[i]--)
      free(libzahl_pool[i][libzahl_pool_n[i]]);

    free(libzahl_pool[i]);
  }

  *i_ref = i;
}


----------------------------
***/


