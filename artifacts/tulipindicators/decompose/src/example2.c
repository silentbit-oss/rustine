int main()
{
  printf("This program is an example of looping through\n");
  printf("each of the available indicators.\n\n");
  const ti_indicator_info *info = ti_indicators;
  unsigned int info_idx = 0;
  while (info->name != 0)
  {
    int i;
    printf("%s (%s) has type %d with: %d inputs, %d options, %d outputs.\n", info->name, info->full_name, info->type, info->inputs, info->options, info->outputs);
    printf("   inputs: ");
    for (i = 0; i < info->inputs; i += 1)
      printf("%s%s", (i) ? (", ") : (""), info->input_names[i]);

    printf("\n");
    printf("   options: ");
    for (i = 0; i < info->options; i += 1)
      printf("%s%s", (i) ? (", ") : (""), info->option_names[i]);

    printf("\n");
    printf("   outputs: ");
    for (i = 0; i < info->outputs; i += 1)
      printf("%s%s", (i) ? (", ") : (""), info->output_names[i]);

    printf("\n");
    printf("\n");
    info_idx += 1;
  }

  return 0;
}


/*** DEPENDENCIES:
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
***/


