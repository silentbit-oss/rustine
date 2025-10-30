struct opng_ui
{
  void (*printf_fn)(const char *fmt, ...);
  void (*print_cntrl_fn)(int cntrl_code);
  void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
  void (*panic_fn)(const char *msg);
}
/*** DEPENDENCIES:
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
***/


