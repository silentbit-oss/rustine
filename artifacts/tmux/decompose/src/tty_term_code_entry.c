struct tty_term_code_entry
{
  enum tty_code_type type;
  const char *name;
}
/*** DEPENDENCIES:
enum tty_code_type
{
  TTYCODE_NONE = 0,
  TTYCODE_STRING,
  TTYCODE_NUMBER,
  TTYCODE_FLAG
}
----------------------------
None
----------------------------
***/


