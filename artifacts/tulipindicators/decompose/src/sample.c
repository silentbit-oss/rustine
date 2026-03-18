int helper_main_2(const ti_indicator_info * const info, unsigned int info_idx)
{
  do
  {
    if (info->type == 1)
    {
      printf("type overlay ");
    }
    else
      if (info->type == 2)
    {
      printf("type indicator ");
    }
    else
      if (info->type == 3)
    {
      printf("type math ");
    }
    else
      if (info->type == 4)
    {
      printf("type simple ");
    }
    else
      printf("type unknown ");
    printf("name %s ", info->name);
    printf("full_name {%s} ", info->full_name);
    int i;
    printf("inputs {");
    for (i = 0; i < info->inputs; i += 1)
      printf("%s%s", (i) ? (" ") : (""), info->input_names[i]);

    printf("} ");
    printf("options {");
    for (i = 0; i < info->options; i += 1)
      printf("%s{%s}", (i) ? (" ") : (""), info->option_names[i]);

    printf("} ");
    printf("outputs {");
    for (i = 0; i < info->outputs; i += 1)
      printf("%s{%s}", (i) ? (" ") : (""), info->output_names[i]);

    printf("}");
    printf("\n");
  }
  while ((++(&info[info_idx]))->name);
  return 0;
}


/*** DEPENDENCIES:
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
***/


// hint:  ['k_ref is a mutable refrence to int', 'bad_ref is a mutable refrence to int']
void helper_helper_main_3_1(int * const k_ref, int * const bad_ref, const ti_indicator_info * const info, int o, int h, int l, int c, int r, int r2, int v, int a, int start, int i)
{
  int k = *k_ref;
  int bad = *bad_ref;
  printf("%s", datet[i]);
  if (o)
  {
    printf(" %8.2f", open[i]);
  }
  if (h)
  {
    printf(" %8.2f", high[i]);
  }
  if (l)
  {
    printf(" %8.2f", low[i]);
  }
  if (c)
  {
    printf(" %8.2f", close[i]);
  }
  if (v)
  {
    printf(" %8.0f", volume[i]);
  }
  if (r)
  {
    printf(" %8.2f", close[i]);
  }
  if (r2)
  {
    printf(" %8.2f", open[i]);
  }
  if (a)
  {
    printf(" %8.2f", alternative[i]);
  }
  if (i >= start)
  {
    for (k = 0; k < info->outputs; k += 1)
    {
      if (out[k][i - start] != out[k][i - start])
      {
        bad = 1;
      }
      printf(" %8.3f", out[k][i - start]);
    }

  }
  printf("\n");
  *k_ref = k;
  *bad_ref = bad;
}


/*** DEPENDENCIES:
double high[] = {82.15, 81.89, 83.03, 83.3, 83.85, 83.9, 83.33, 84.3, 84.84, 85, 85.9, 86.58, 86.98, 88, 87.87}
----------------------------
double volume[] = {5653100, 6447400, 7690900, 3831400, 4455100, 3798000, 3936200, 4732000, 4841300, 3915300, 6830800, 6694100, 5293600, 7985800, 4807900}
----------------------------
double close[] = {81.59, 81.06, 82.87, 83, 83.61, 83.15, 82.84, 83.99, 84.55, 84.36, 85.53, 86.54, 86.89, 87.77, 87.29}
----------------------------
const char *datet[] = {"2005-11-01", "2005-11-02", "2005-11-03", "2005-11-04", "2005-11-07", "2005-11-08", "2005-11-09", "2005-11-10", "2005-11-11", "2005-11-14", "2005-11-15", "2005-11-16", "2005-11-17", "2005-11-18", "2005-11-21"}
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
double out[3][4000]
----------------------------
double open[] = {81.85, 81.2, 81.55, 82.91, 83.1, 83.41, 82.71, 82.7, 84.2, 84.25, 84.03, 85.45, 86.18, 88, 87.6}
----------------------------
double alternative[] = {.2, .3, .4, .3, .5, .7, .75, .9, .9, 1, 1, .2, .1, -.1, -.5}
----------------------------
double low[] = {81.29, 80.64, 81.31, 82.65, 83.07, 83.11, 82.49, 82.3, 84.15, 84.11, 84.03, 85.39, 85.76, 87.17, 87.01}
----------------------------
***/


int helper_main_3(const ti_indicator_info * const info, int o, int h, int l, int c, int r, int r2, int v, int a, int start)
{
  int i;
  int k;
  int bad = 0;
  printf("date        ");
  if (o)
  {
    printf(" open   ");
  }
  if (h)
  {
    printf(" high   ");
  }
  if (l)
  {
    printf(" low    ");
  }
  if (c)
  {
    printf(" close  ");
  }
  if (v)
  {
    printf(" volume ");
  }
  if (r)
  {
    printf(" input  ");
  }
  if (r2)
  {
    printf(" input2  ");
  }
  if (a)
  {
    printf(" input  ");
  }
  for (i = 0; i < info->outputs; i += 1)
    printf(" %s", info->output_names[i]);

  printf("\n");
  for (i = 0; i < 15; i += 1)
  {
    helper_helper_main_3_1(&k, &bad, info, o, h, l, c, r, r2, v, a, start, i);
  }

  if (bad)
  {
    printf("\nERROR NaN in outputs (%s).\n", info->name);
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
void helper_helper_main_3_1(int * const k_ref, int * const bad_ref, const ti_indicator_info * const info, int o, int h, int l, int c, int r, int r2, int v, int a, int start, int i)
{
  int k = *k_ref;
  int bad = *bad_ref;
  printf("%s", datet[i]);
  if (o)
  {
    printf(" %8.2f", open[i]);
  }
  if (h)
  {
    printf(" %8.2f", high[i]);
  }
  if (l)
  {
    printf(" %8.2f", low[i]);
  }
  if (c)
  {
    printf(" %8.2f", close[i]);
  }
  if (v)
  {
    printf(" %8.0f", volume[i]);
  }
  if (r)
  {
    printf(" %8.2f", close[i]);
  }
  if (r2)
  {
    printf(" %8.2f", open[i]);
  }
  if (a)
  {
    printf(" %8.2f", alternative[i]);
  }
  if (i >= start)
  {
    for (k = 0; k < info->outputs; k += 1)
    {
      if (out[k][i - start] != out[k][i - start])
      {
        bad = 1;
      }
      printf(" %8.3f", out[k][i - start]);
    }

  }
  printf("\n");
  *k_ref = k;
  *bad_ref = bad;
}


----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
***/


// hint:  ['o_ref is a mutable refrence to int', 'h_ref is a mutable refrence to int', 'l_ref is a mutable refrence to int', 'c_ref is a mutable refrence to int', 'r_ref is a mutable refrence to int', 'r2_ref is a mutable refrence to int', 'v_ref is a mutable refrence to int', 'j_ref is a mutable refrence to int']
void helper_main_1(int * const o_ref, int * const h_ref, int * const l_ref, int * const c_ref, int * const r_ref, int * const r2_ref, int * const v_ref, int * const j_ref, const ti_indicator_info * const info, const double *inputs[])
{
  int o = *o_ref;
  int h = *h_ref;
  int l = *l_ref;
  int c = *c_ref;
  int r = *r_ref;
  int r2 = *r2_ref;
  int v = *v_ref;
  int j = *j_ref;
  if (strcmp(info->input_names[j], "open") == 0)
  {
    inputs[j] = open;
    o = 1;
  }
  else
    if (strcmp(info->input_names[j], "high") == 0)
  {
    inputs[j] = high;
    h = 1;
  }
  else
    if (strcmp(info->input_names[j], "low") == 0)
  {
    inputs[j] = low;
    l = 1;
  }
  else
    if (strcmp(info->input_names[j], "close") == 0)
  {
    inputs[j] = close;
    c = 1;
  }
  else
    if (strcmp(info->input_names[j], "volume") == 0)
  {
    inputs[j] = volume;
    v = 1;
  }
  else
    if (strcmp(info->input_names[j], "real") == 0)
  {
    if (!r)
    {
      inputs[j] = close;
      r = 1;
    }
    else
    {
      inputs[j] = open;
      r2 = 1;
    }
  }
  else
  {
    assert(0);
  }
  ;
  *o_ref = o;
  *h_ref = h;
  *l_ref = l;
  *c_ref = c;
  *r_ref = r;
  *r2_ref = r2;
  *v_ref = v;
  *j_ref = j;
}


/*** DEPENDENCIES:
double high[] = {82.15, 81.89, 83.03, 83.3, 83.85, 83.9, 83.33, 84.3, 84.84, 85, 85.9, 86.58, 86.98, 88, 87.87}
----------------------------
double volume[] = {5653100, 6447400, 7690900, 3831400, 4455100, 3798000, 3936200, 4732000, 4841300, 3915300, 6830800, 6694100, 5293600, 7985800, 4807900}
----------------------------
double close[] = {81.59, 81.06, 82.87, 83, 83.61, 83.15, 82.84, 83.99, 84.55, 84.36, 85.53, 86.54, 86.89, 87.77, 87.29}
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
double open[] = {81.85, 81.2, 81.55, 82.91, 83.1, 83.41, 82.71, 82.7, 84.2, 84.25, 84.03, 85.45, 86.18, 88, 87.6}
----------------------------
double low[] = {81.29, 80.64, 81.31, 82.65, 83.07, 83.11, 82.49, 82.3, 84.15, 84.11, 84.03, 85.39, 85.76, 87.17, 87.01}
----------------------------
***/


int main(int argc, char **argv)
{
  const ti_indicator_info *info = ti_indicators;
  unsigned int info_idx = 0;
  if (argc < 2)
  {
    printf("No indicator given.\n");
    printf("Example:\n");
    printf("\tsample ma 5");
    return 1;
  }
  if (strcmp(argv[1], "--version") == 0)
  {
    printf("TI VERSION: %s, TI BUILD: %d\n", "0.9.2", 1746800254);
    return 0;
  }
  if (strcmp(argv[1], "--list") == 0)
  {
    helper_main_2(info, info_idx);
  }
  info_idx = ti_find_indicator(argv[1]);
  if (!(&info[info_idx]))
  {
    printf("Couldn't find indicator: %s\n", argv[1]);
    return 1;
  }
  const double *inputs[] = {0, 0, 0, 0, 0};
  double *outputs[] = {out[0], out[1], out[2], out[3], out[4]};
  int o = 0;
  int h = 0;
  int l = 0;
  int c = 0;
  int r = 0;
  int r2 = 0;
  int v = 0;
  int a = 0;
  int j;
  for (j = 0; j < info->inputs; j += 1)
  {
    helper_main_1(&o, &h, &l, &c, &r, &r2, &v, &j, info, inputs);
  }

  const char *alts[] = {"acos", "asin", "atan", "cosh", "sinh", "tanh", "todeg", 0};
  {
    const char **alt = alts;
    unsigned int alt_idx = 0;
    while (alt[alt_idx])
    {
      if (strcmp(*(&alt[alt_idx]), info->name) == 0)
      {
        r = 0;
        a = 1;
        for (j = 0; j < info->inputs; j += 1)
          inputs[j] = alternative;

        break;
      }
      alt_idx += 1;
    }

  }
  double options[10];
  {
    int i;
    for (i = 0; i < info->options; i += 1)
    {
      if (argc < (3 + i))
      {
        printf("*ERROR NOT ENOUGH OPTIONS*\n");
        for (int k = 1; k < argc; k += 1)
        {
          printf("%s ", argv[k]);
        }

        printf("\n");
        return 1;
      }
      options[i] = atof(argv[2 + i]);
    }

  }
  int start = info->start(options);
  const int ret = info->indicator(15, inputs, options, outputs);
  if (ret == 0)
  {
    helper_main_3(info, o, h, l, c, r, r2, v, a, start);
  }
  else
  {
    if (ret == 1)
    {
      printf("*ERROR INVALID OPTION*\n");
      for (int i = 1; i < argc; i += 1)
      {
        printf("%s ", argv[i]);
      }

      printf("\n");
    }
    else
    {
      printf("*ERROR*\n");
    }
    return 1;
  }
}


/*** DEPENDENCIES:
int helper_main_3(const ti_indicator_info * const info, int o, int h, int l, int c, int r, int r2, int v, int a, int start)
{
  int i;
  int k;
  int bad = 0;
  printf("date        ");
  if (o)
  {
    printf(" open   ");
  }
  if (h)
  {
    printf(" high   ");
  }
  if (l)
  {
    printf(" low    ");
  }
  if (c)
  {
    printf(" close  ");
  }
  if (v)
  {
    printf(" volume ");
  }
  if (r)
  {
    printf(" input  ");
  }
  if (r2)
  {
    printf(" input2  ");
  }
  if (a)
  {
    printf(" input  ");
  }
  for (i = 0; i < info->outputs; i += 1)
    printf(" %s", info->output_names[i]);

  printf("\n");
  for (i = 0; i < 15; i += 1)
  {
    helper_helper_main_3_1(&k, &bad, info, o, h, l, c, r, r2, v, a, start, i);
  }

  if (bad)
  {
    printf("\nERROR NaN in outputs (%s).\n", info->name);
    return 1;
  }
  return 0;
}


----------------------------
extern ti_indicator_info ti_indicators[]
----------------------------
typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
----------------------------
double out[3][4000]
----------------------------
void helper_main_1(int * const o_ref, int * const h_ref, int * const l_ref, int * const c_ref, int * const r_ref, int * const r2_ref, int * const v_ref, int * const j_ref, const ti_indicator_info * const info, const double *inputs[])
{
  int o = *o_ref;
  int h = *h_ref;
  int l = *l_ref;
  int c = *c_ref;
  int r = *r_ref;
  int r2 = *r2_ref;
  int v = *v_ref;
  int j = *j_ref;
  if (strcmp(info->input_names[j], "open") == 0)
  {
    inputs[j] = open;
    o = 1;
  }
  else
    if (strcmp(info->input_names[j], "high") == 0)
  {
    inputs[j] = high;
    h = 1;
  }
  else
    if (strcmp(info->input_names[j], "low") == 0)
  {
    inputs[j] = low;
    l = 1;
  }
  else
    if (strcmp(info->input_names[j], "close") == 0)
  {
    inputs[j] = close;
    c = 1;
  }
  else
    if (strcmp(info->input_names[j], "volume") == 0)
  {
    inputs[j] = volume;
    v = 1;
  }
  else
    if (strcmp(info->input_names[j], "real") == 0)
  {
    if (!r)
    {
      inputs[j] = close;
      r = 1;
    }
    else
    {
      inputs[j] = open;
      r2 = 1;
    }
  }
  else
  {
    assert(0);
  }
  ;
  *o_ref = o;
  *h_ref = h;
  *l_ref = l;
  *c_ref = c;
  *r_ref = r;
  *r2_ref = r2;
  *v_ref = v;
  *j_ref = j;
}


----------------------------
int helper_main_2(const ti_indicator_info * const info, unsigned int info_idx)
{
  do
  {
    if (info->type == 1)
    {
      printf("type overlay ");
    }
    else
      if (info->type == 2)
    {
      printf("type indicator ");
    }
    else
      if (info->type == 3)
    {
      printf("type math ");
    }
    else
      if (info->type == 4)
    {
      printf("type simple ");
    }
    else
      printf("type unknown ");
    printf("name %s ", info->name);
    printf("full_name {%s} ", info->full_name);
    int i;
    printf("inputs {");
    for (i = 0; i < info->inputs; i += 1)
      printf("%s%s", (i) ? (" ") : (""), info->input_names[i]);

    printf("} ");
    printf("options {");
    for (i = 0; i < info->options; i += 1)
      printf("%s{%s}", (i) ? (" ") : (""), info->option_names[i]);

    printf("} ");
    printf("outputs {");
    for (i = 0; i < info->outputs; i += 1)
      printf("%s{%s}", (i) ? (" ") : (""), info->output_names[i]);

    printf("}");
    printf("\n");
  }
  while ((++(&info[info_idx]))->name);
  return 0;
}


----------------------------
const ti_indicator_info *ti_find_indicator(const char *name)
{
  int imin = 0;
  int imax = ((sizeof(ti_indicators)) / (sizeof(ti_indicator_info))) - 2;
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    const int c = strcmp(name, ti_indicators[i].name);
    if (c == 0)
    {
      return ti_indicators + i;
    }
    else
      if (c > 0)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


----------------------------
double alternative[] = {.2, .3, .4, .3, .5, .7, .75, .9, .9, 1, 1, .2, .1, -.1, -.5}
----------------------------
***/


