static int tty_acs_cmp(const void *key, const void *value)
{
  const struct tty_acs_entry *entry = value;
  u_char ch;
  ch = *((u_char *) key);
  return ch - entry->key;
}


/*** DEPENDENCIES:
struct tty_acs_entry
{
  u_char key;
  const char *string;
}
----------------------------
None
----------------------------
***/


int tty_acs_needed(struct tty *tty)
{
  if (tty == 0)
  {
    return 0;
  }
  if (tty_term_has(tty->term, TTYC_U8) && (tty_term_number(tty->term, TTYC_U8) == 0))
  {
    return 1;
  }
  if (tty->flags & 0x8)
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
int tty_term_number(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return 0;
  }
  if (term->codes[code].type != TTYCODE_NUMBER)
  {
    fatalx("not a number: %d", code);
  }
  return term->codes[code].value.number;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
None
----------------------------
***/


const char *tty_acs_get(struct tty *tty, u_char ch)
{
  struct tty_acs_entry *entry;
  unsigned int entry_idx = 0;
  if (tty_acs_needed(tty))
  {
    if (tty->term->acs[ch][0] == '\0')
    {
      return 0;
    }
    return &tty->term->acs[ch][0];
  }
  entry_idx = bsearch(&ch, tty_acs_table, (sizeof(tty_acs_table)) / (sizeof(tty_acs_table[0])), sizeof(tty_acs_table[0]), tty_acs_cmp);
  if ((&entry[entry_idx]) == 0)
  {
    return 0;
  }
  return entry->string;
}


/*** DEPENDENCIES:
static const struct tty_acs_entry tty_acs_table[] = {{'+', "\342\206\222"}, {',', "\342\206\220"}, {'-', "\342\206\221"}, {'.', "\342\206\223"}, {'0', "\342\226\256"}, {'`', "\342\227\206"}, {'a', "\342\226\222"}, {'f', "\302\260"}, {'g', "\302\261"}, {'h', "\342\226\222"}, {'i', "\342\230\203"}, {'j', "\342\224\230"}, {'k', "\342\224\220"}, {'l', "\342\224\214"}, {'m', "\342\224\224"}, {'n', "\342\224\274"}, {'o', "\342\216\272"}, {'p', "\342\216\273"}, {'q', "\342\224\200"}, {'r', "\342\216\274"}, {'s', "\342\216\275"}, {'t', "\342\224\234"}, {'u', "\342\224\244"}, {'v', "\342\224\264"}, {'w', "\342\224\254"}, {'x', "\342\224\202"}, {'y', "\342\211\244"}, {'z', "\342\211\245"}, {'{', "\317\200"}, {'|', "\342\211\240"}, {'}', "\302\243"}, {'~', "\302\267"}}
----------------------------
struct tty_acs_entry
{
  u_char key;
  const char *string;
}
----------------------------
static int tty_acs_cmp(const void *key, const void *value)
{
  const struct tty_acs_entry *entry = value;
  u_char ch;
  ch = *((u_char *) key);
  return ch - entry->key;
}


----------------------------
int tty_acs_needed(struct tty *tty)
{
  if (tty == 0)
  {
    return 0;
  }
  if (tty_term_has(tty->term, TTYC_U8) && (tty_term_number(tty->term, TTYC_U8) == 0))
  {
    return 1;
  }
  if (tty->flags & 0x8)
  {
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


