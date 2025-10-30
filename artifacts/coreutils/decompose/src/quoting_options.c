struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


