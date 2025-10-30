int parse_flags(int argc, char **argv)
{
  int arg_idx;
  int sflags = 0;
  for (arg_idx = 1; arg_idx < argc; arg_idx += 1)
  {
    int jj;
    for (jj = 0; jj < ((int) ((sizeof(format_args)) / (sizeof(format_args[0])))); jj += 1)
    {
      if (strcasecmp(argv[arg_idx], format_args[jj].arg) == 0)
      {
        sflags |= format_args[jj].flag;
        break;
      }
    }

    if (jj == ((sizeof(format_args)) / (sizeof(format_args[0]))))
    {
      printf("Unknown arg: %s\n", argv[arg_idx]);
      exit(1);
    }
  }

  return sflags;
}


/*** DEPENDENCIES:
static struct 
{
  const char *arg;
  int flag;
} format_args[] = {{"plain", 0}, {"spaced", 1 << 0}, {"pretty", 1 << 1}, {"pretty_tab", 1 << 3}}
----------------------------
***/


