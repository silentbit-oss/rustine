void run(const char *name, const char *in, const char *out)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    fprintf(stderr, "(ERROR) Couldn't find indicator %s\n", name);
    return;
  }
  FILE *fin = fopen(in, "r");
  if (!fin)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for input.\n", in);
    return;
  }
  char *line = next_line(fin);
  double options[16];
  double *o = options;
  unsigned int o_idx = 0;
  const char *s = strtok(line, " \n\r");
  unsigned int s_idx = 0;
  if (s)
  {
    do
    {
      o[o_idx] = atof(s);
      o_idx += 1;
    }
    while (s_idx = strtok(0, " \n\r"));
  }
  if (((int) ((&o[o_idx]) - options)) != info->options)
  {
    fprintf(stderr, "(ERROR) Invalid number of options for %s. Expected %d, got %d\n", name, info->options, (int) ((&o[o_idx]) - options));
    return;
  }
  int i;
  double *inputs[16] = {0};
  double *outputs[16] = {0};
  int input_size = 0;
  for (i = 0; i < info->inputs; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 8192);
    input_size = get_array(fin, inputs[i]);
  }

  fclose(fin);
  for (i = 0; i < info->outputs; i += 1)
  {
    outputs[i] = malloc((sizeof(double)) * 8192);
  }

  {
    const int ret = info->indicator(input_size, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      fprintf(stderr, "(ERROR) Return value for %s of %d.\n", name, ret);
      return;
    }
  }
  FILE *fout = fopen(out, "w");
  if (!fout)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for output.\n", out);
    return;
  }
  const int out_size = input_size - info->start(options);
  for (i = 0; i < info->outputs; i += 1)
  {
    fprintf(fout, "{");
    for (int j = 0; j < out_size; j += 1)
    {
      fprintf(fout, "%f%s", outputs[i][j], (j == (out_size - 1)) ? ("") : (","));
    }

    fprintf(fout, "}\n");
  }

  fclose(fout);
  for (i = 0; i < info->inputs; i += 1)
    free(inputs[i]);

  for (i = 0; i < info->outputs; i += 1)
    free(outputs[i]);

}


/*** DEPENDENCIES:
char *next_line(FILE *fp)
{
  static char buf[4096];
  while (fgets(buf, 4096, fp))
  {
    if (buf[0] == '#')
    {
      continue;
    }
    if ((buf[0] == 10) || (buf[0] == 13))
    {
      continue;
    }
    return buf;
  }

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
int get_array(FILE *fp, double *s)
{
  char *line = next_line(fp);
  if (line[0] != '{')
  {
    printf("Bad input\n");
    do
    {
      ltests += 1;
      if (!0)
      {
        lfails += 1;
        printf("%s:%d error \n", "/home/enumclass/Documents/C2RustTranslation/bkp/tulipindicators/smoke.c", 85);
      }
    }
    while (0);
    return 0;
  }
  char *num = strtok(line + 1, ",}\r\n");
  unsigned int num_idx = 0;
  if (!(&num[num_idx]))
  {
    return 0;
  }
  double *inp = s;
  unsigned int inp_idx = 0;
  do
  {
    inp[inp_idx] = atof(num);
    inp_idx += 1;
  }
  while (num_idx = strtok(0, ",}\r\n"));
  return (int) ((&inp[inp_idx]) - s);
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


int main(int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("Usage: cli indicator_name infile outfile\n");
  }
  const char *name = argv[1];
  const char *in = argv[2];
  const char *out = argv[3];
  run(name, in, out);
  return 0;
}


/*** DEPENDENCIES:
void run(const char *name, const char *in, const char *out)
{
  const ti_indicator_info *info = ti_find_indicator(name);
  if (!info)
  {
    fprintf(stderr, "(ERROR) Couldn't find indicator %s\n", name);
    return;
  }
  FILE *fin = fopen(in, "r");
  if (!fin)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for input.\n", in);
    return;
  }
  char *line = next_line(fin);
  double options[16];
  double *o = options;
  unsigned int o_idx = 0;
  const char *s = strtok(line, " \n\r");
  unsigned int s_idx = 0;
  if (s)
  {
    do
    {
      o[o_idx] = atof(s);
      o_idx += 1;
    }
    while (s_idx = strtok(0, " \n\r"));
  }
  if (((int) ((&o[o_idx]) - options)) != info->options)
  {
    fprintf(stderr, "(ERROR) Invalid number of options for %s. Expected %d, got %d\n", name, info->options, (int) ((&o[o_idx]) - options));
    return;
  }
  int i;
  double *inputs[16] = {0};
  double *outputs[16] = {0};
  int input_size = 0;
  for (i = 0; i < info->inputs; i += 1)
  {
    inputs[i] = malloc((sizeof(double)) * 8192);
    input_size = get_array(fin, inputs[i]);
  }

  fclose(fin);
  for (i = 0; i < info->outputs; i += 1)
  {
    outputs[i] = malloc((sizeof(double)) * 8192);
  }

  {
    const int ret = info->indicator(input_size, (const double * const *) inputs, options, outputs);
    if (ret != 0)
    {
      fprintf(stderr, "(ERROR) Return value for %s of %d.\n", name, ret);
      return;
    }
  }
  FILE *fout = fopen(out, "w");
  if (!fout)
  {
    fprintf(stderr, "(ERROR) Couldn't open %s for output.\n", out);
    return;
  }
  const int out_size = input_size - info->start(options);
  for (i = 0; i < info->outputs; i += 1)
  {
    fprintf(fout, "{");
    for (int j = 0; j < out_size; j += 1)
    {
      fprintf(fout, "%f%s", outputs[i][j], (j == (out_size - 1)) ? ("") : (","));
    }

    fprintf(fout, "}\n");
  }

  fclose(fout);
  for (i = 0; i < info->inputs; i += 1)
    free(inputs[i]);

  for (i = 0; i < info->outputs; i += 1)
    free(outputs[i]);

}


----------------------------
***/


