static void tty_add(struct tty *tty, const char *buf, size_t len)
{
  struct client *c = tty->client;
  if (tty->flags & 0x80)
  {
    tty->discarded += len;
    return;
  }
  evbuffer_add(tty->out, buf, len);
  log_debug("%s: %.*s", c->name, (int) len, buf);
  c->written += len;
  if (tty_log_fd != (-1))
  {
    write(tty_log_fd, buf, len);
  }
  if (tty->flags & 0x10)
  {
    event_add(&tty->event_out, 0);
  }
}


/*** DEPENDENCIES:
static int tty_log_fd = -1
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


/*** DEPENDENCIES:
static void tty_add(struct tty *tty, const char *buf, size_t len)
{
  struct client *c = tty->client;
  if (tty->flags & 0x80)
  {
    tty->discarded += len;
    return;
  }
  evbuffer_add(tty->out, buf, len);
  log_debug("%s: %.*s", c->name, (int) len, buf);
  c->written += len;
  if (tty_log_fd != (-1))
  {
    write(tty_log_fd, buf, len);
  }
  if (tty->flags & 0x10)
  {
    event_add(&tty->event_out, 0);
  }
}


----------------------------
None
----------------------------
***/


void tty_putcode_ptr2(struct tty *tty, enum tty_code_code code, const void *a, const void *b)
{
  if ((a != 0) && (b != 0))
  {
    tty_puts(tty, tty_term_ptr2(tty->term, code, a, b));
  }
}


/*** DEPENDENCIES:
const char *tty_term_ptr2(struct tty_term *term, enum tty_code_code code, const void *a, const void *b)
{
  return tparm((char *) tty_term_string(term, code), a, b, 0, 0, 0, 0, 0, 0, 0);
}


----------------------------
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


void tty_cmd_setselection(struct tty *tty, const struct tty_ctx *ctx)
{
  char *buf;
  unsigned int buf_idx = 0;
  size_t off;
  if (!tty_term_has(tty->term, TTYC_MS))
  {
    return;
  }
  off = (4 * ((ctx->num + 2) / 3)) + 1;
  buf_idx = xmalloc(off);
  b64_ntop(ctx->ptr, ctx->num, buf, off);
  tty_putcode_ptr2(tty, TTYC_MS, "", buf);
  free(buf);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
void tty_putcode_ptr2(struct tty *tty, enum tty_code_code code, const void *a, const void *b)
{
  if ((a != 0) && (b != 0))
  {
    tty_puts(tty, tty_term_ptr2(tty->term, code, a, b));
  }
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
None
----------------------------
***/


static int tty_client_ready(struct client *c, struct window_pane *wp)
{
  if ((c->session == 0) || (c->tty.term == 0))
  {
    return 0;
  }
  if (c->flags & (0x8 | 0x40))
  {
    return 0;
  }
  if (c->tty.flags & 0x2)
  {
    return 0;
  }
  if (c->session->curw->window != wp->window)
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
}


----------------------------
int status_at_line(struct client *c)
{
  struct session *s = c->session;
  if (c->flags & 0x800000)
  {
    return -1;
  }
  if (s->statusat != 1)
  {
    return s->statusat;
  }
  return c->tty.sy - status_line_size(s);
}


----------------------------
static int tty_client_ready(struct client *c, struct window_pane *wp)
{
  if ((c->session == 0) || (c->tty.term == 0))
  {
    return 0;
  }
  if (c->flags & (0x8 | 0x40))
  {
    return 0;
  }
  if (c->tty.flags & 0x2)
  {
    return 0;
  }
  if (c->session->curw->window != wp->window)
  {
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


void tty_putcode2(struct tty *tty, enum tty_code_code code, int a, int b)
{
  if ((a < 0) || (b < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string2(tty->term, code, a, b));
}


/*** DEPENDENCIES:
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
const char *tty_term_string2(struct tty_term *term, enum tty_code_code code, int a, int b)
{
  return tparm((char *) tty_term_string(term, code), a, b, 0, 0, 0, 0, 0, 0, 0);
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


/*** DEPENDENCIES:
void tty_putcode2(struct tty *tty, enum tty_code_code code, int a, int b)
{
  if ((a < 0) || (b < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string2(tty->term, code, a, b));
}


----------------------------
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


----------------------------
static void tty_add(struct tty *tty, const char *buf, size_t len)
{
  struct client *c = tty->client;
  if (tty->flags & 0x80)
  {
    tty->discarded += len;
    return;
  }
  evbuffer_add(tty->out, buf, len);
  log_debug("%s: %.*s", c->name, (int) len, buf);
  c->written += len;
  if (tty_log_fd != (-1))
  {
    write(tty_log_fd, buf, len);
  }
  if (tty->flags & 0x10)
  {
    event_add(&tty->event_out, 0);
  }
}


----------------------------
None
----------------------------
***/


void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


/*** DEPENDENCIES:
const char *tty_term_string1(struct tty_term *term, enum tty_code_code code, int a)
{
  return tparm((char *) tty_term_string(term, code), a, 0, 0, 0, 0, 0, 0, 0, 0);
}


----------------------------
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


/*** DEPENDENCIES:
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
const char *tty_term_string(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return "";
  }
  if (term->codes[code].type != TTYCODE_STRING)
  {
    fatalx("not a string: %d", code);
  }
  return term->codes[code].value.string;
}


----------------------------
None
----------------------------
***/


// hint:  ['change_ref is a mutable refrence to int']
void helper_tty_cursor_2(int * const change_ref, struct tty * const tty, u_int cx, struct tty_term * const term, u_int thisx)
{
  int change = *change_ref;
  if ((cx == 0) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    goto out;
  }
  if ((cx == (thisx - 1)) && tty_term_has(term, TTYC_CUB1))
  {
    tty_putcode(tty, TTYC_CUB1);
    goto out;
  }
  if ((cx == (thisx + 1)) && tty_term_has(term, TTYC_CUF1))
  {
    tty_putcode(tty, TTYC_CUF1);
    goto out;
  }
  change = thisx - cx;
  if ((((u_int) abs(change)) > cx) && tty_term_has(term, TTYC_HPA))
  {
    tty_putcode1(tty, TTYC_HPA, cx);
    goto out;
  }
  else
    if ((change > 0) && tty_term_has(term, TTYC_CUB))
  {
    if ((change == 2) && tty_term_has(term, TTYC_CUB1))
    {
      tty_putcode(tty, TTYC_CUB1);
      tty_putcode(tty, TTYC_CUB1);
      goto out;
    }
    tty_putcode1(tty, TTYC_CUB, change);
    goto out;
  }
  else
    if ((change < 0) && tty_term_has(term, TTYC_CUF))
  {
    tty_putcode1(tty, TTYC_CUF, -change);
    goto out;
  }
  *change_ref = change;
}


/*** DEPENDENCIES:
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
***/


// hint:  ['change_ref is a mutable refrence to int']
void helper_tty_cursor_1(int * const change_ref, struct tty * const tty, u_int cy, struct tty_term * const term, u_int thisy)
{
  int change = *change_ref;
  if (((thisy != tty->rupper) && (cy == (thisy - 1))) && tty_term_has(term, TTYC_CUU1))
  {
    tty_putcode(tty, TTYC_CUU1);
    goto out;
  }
  if (((thisy != tty->rlower) && (cy == (thisy + 1))) && tty_term_has(term, TTYC_CUD1))
  {
    tty_putcode(tty, TTYC_CUD1);
    goto out;
  }
  change = thisy - cy;
  if (((((u_int) abs(change)) > cy) || ((change < 0) && ((cy - change) > tty->rlower))) || ((change > 0) && ((cy - change) < tty->rupper)))
  {
    if (tty_term_has(term, TTYC_VPA))
    {
      tty_putcode1(tty, TTYC_VPA, cy);
      goto out;
    }
  }
  else
    if ((change > 0) && tty_term_has(term, TTYC_CUU))
  {
    tty_putcode1(tty, TTYC_CUU, change);
    goto out;
  }
  else
    if ((change < 0) && tty_term_has(term, TTYC_CUD))
  {
    tty_putcode1(tty, TTYC_CUD, -change);
    goto out;
  }
  *change_ref = change;
}


/*** DEPENDENCIES:
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
***/


void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


/*** DEPENDENCIES:
void tty_putcode2(struct tty *tty, enum tty_code_code code, int a, int b)
{
  if ((a < 0) || (b < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string2(tty->term, code, a, b));
}


----------------------------
void helper_tty_cursor_2(int * const change_ref, struct tty * const tty, u_int cx, struct tty_term * const term, u_int thisx)
{
  int change = *change_ref;
  if ((cx == 0) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    goto out;
  }
  if ((cx == (thisx - 1)) && tty_term_has(term, TTYC_CUB1))
  {
    tty_putcode(tty, TTYC_CUB1);
    goto out;
  }
  if ((cx == (thisx + 1)) && tty_term_has(term, TTYC_CUF1))
  {
    tty_putcode(tty, TTYC_CUF1);
    goto out;
  }
  change = thisx - cx;
  if ((((u_int) abs(change)) > cx) && tty_term_has(term, TTYC_HPA))
  {
    tty_putcode1(tty, TTYC_HPA, cx);
    goto out;
  }
  else
    if ((change > 0) && tty_term_has(term, TTYC_CUB))
  {
    if ((change == 2) && tty_term_has(term, TTYC_CUB1))
    {
      tty_putcode(tty, TTYC_CUB1);
      tty_putcode(tty, TTYC_CUB1);
      goto out;
    }
    tty_putcode1(tty, TTYC_CUB, change);
    goto out;
  }
  else
    if ((change < 0) && tty_term_has(term, TTYC_CUF))
  {
    tty_putcode1(tty, TTYC_CUF, -change);
    goto out;
  }
  *change_ref = change;
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
void helper_tty_cursor_1(int * const change_ref, struct tty * const tty, u_int cy, struct tty_term * const term, u_int thisy)
{
  int change = *change_ref;
  if (((thisy != tty->rupper) && (cy == (thisy - 1))) && tty_term_has(term, TTYC_CUU1))
  {
    tty_putcode(tty, TTYC_CUU1);
    goto out;
  }
  if (((thisy != tty->rlower) && (cy == (thisy + 1))) && tty_term_has(term, TTYC_CUD1))
  {
    tty_putcode(tty, TTYC_CUD1);
    goto out;
  }
  change = thisy - cy;
  if (((((u_int) abs(change)) > cy) || ((change < 0) && ((cy - change) > tty->rlower))) || ((change > 0) && ((cy - change) < tty->rupper)))
  {
    if (tty_term_has(term, TTYC_VPA))
    {
      tty_putcode1(tty, TTYC_VPA, cy);
      goto out;
    }
  }
  else
    if ((change > 0) && tty_term_has(term, TTYC_CUU))
  {
    tty_putcode1(tty, TTYC_CUU, change);
    goto out;
  }
  else
    if ((change < 0) && tty_term_has(term, TTYC_CUD))
  {
    tty_putcode1(tty, TTYC_CUD, -change);
    goto out;
  }
  *change_ref = change;
}


----------------------------
None
----------------------------
***/


static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
None
----------------------------
***/


static void tty_cursor_pane_unless_wrap(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  if (((((((!ctx->wrapped) || (!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx)))) || (tty->term->flags & 0x2)) || ((ctx->xoff + cx) != 0)) || ((ctx->yoff + cy) != (tty->cy + 1))) || (tty->cx < tty->sx)) || (tty->cy == tty->rlower))
  {
    tty_cursor_pane(tty, ctx, cx, cy);
  }
  else
    log_debug("%s: will wrap at %u,%u", __func__, tty->cx, tty->cy);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
None
----------------------------
***/


void tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
  tty_add(tty, buf, len);
  if ((tty->cx + width) > tty->sx)
  {
    tty->cx = (tty->cx + width) - tty->sx;
    if (tty->cx <= tty->sx)
    {
      tty->cy += 1;
    }
    else
      tty->cx = (tty->cy = 4294967295U);
  }
  else
    tty->cx += width;
}


/*** DEPENDENCIES:
static void tty_add(struct tty *tty, const char *buf, size_t len)
{
  struct client *c = tty->client;
  if (tty->flags & 0x80)
  {
    tty->discarded += len;
    return;
  }
  evbuffer_add(tty->out, buf, len);
  log_debug("%s: %.*s", c->name, (int) len, buf);
  c->written += len;
  if (tty_log_fd != (-1))
  {
    write(tty_log_fd, buf, len);
  }
  if (tty->flags & 0x10)
  {
    event_add(&tty->event_out, 0);
  }
}


----------------------------
None
----------------------------
***/


void tty_reset(struct tty *tty)
{
  struct grid_cell *gc = &tty->cell;
  if (!grid_cells_equal(gc, &grid_default_cell))
  {
    if ((gc->attr & 0x80) && tty_acs_needed(tty))
    {
      tty_putcode(tty, TTYC_RMACS);
    }
    tty_putcode(tty, TTYC_SGR0);
    memcpy(gc, &grid_default_cell, sizeof(*gc));
  }
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
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
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
int grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
  if ((gca->fg != gcb->fg) || (gca->bg != gcb->bg))
  {
    return 0;
  }
  if ((gca->attr != gcb->attr) || (gca->flags != gcb->flags))
  {
    return 0;
  }
  if (gca->data.width != gcb->data.width)
  {
    return 0;
  }
  if (gca->data.size != gcb->data.size)
  {
    return 0;
  }
  return memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0;
}


----------------------------
None
----------------------------
None
----------------------------
***/


int helper_tty_try_colour_1(struct tty * const tty, int colour, const char * const type)
{
  if ((tty->term_flags & 0x1) || tty_term_has(tty->term, TTYC_RGB))
  {
    goto fallback_256;
  }
  if (tty->term->flags & 0x1)
  {
    if ((*type) == '3')
    {
      if (!tty_term_has(tty->term, TTYC_SETAF))
      {
        goto fallback_256;
      }
      tty_putcode1(tty, TTYC_SETAF, colour & 0xff);
    }
    else
    {
      if (!tty_term_has(tty->term, TTYC_SETAB))
      {
        goto fallback_256;
      }
      tty_putcode1(tty, TTYC_SETAB, colour & 0xff);
    }
    return 0;
  }
  goto fallback_256;
}


/*** DEPENDENCIES:
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
None
----------------------------
***/


void tty_putcode3(struct tty *tty, enum tty_code_code code, int a, int b, int c)
{
  if (((a < 0) || (b < 0)) || (c < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string3(tty->term, code, a, b, c));
}


/*** DEPENDENCIES:
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
const char *tty_term_string3(struct tty_term *term, enum tty_code_code code, int a, int b, int c)
{
  return tparm((char *) tty_term_string(term, code), a, b, c, 0, 0, 0, 0, 0, 0);
}


----------------------------
None
----------------------------
***/


static int tty_try_colour(struct tty *tty, int colour, const char *type)
{
  u_char r;
  u_char g;
  u_char b;
  char s[32];
  if (colour & 0x01000000)
  {
    helper_tty_try_colour_1(tty, colour, type);
  }
  if (colour & 0x02000000)
  {
    if ((*type) == '3')
    {
      if (!tty_term_has(tty->term, TTYC_SETRGBF))
      {
        return -1;
      }
      colour_split_rgb(colour & 0xffffff, &r, &g, &b);
      tty_putcode3(tty, TTYC_SETRGBF, r, g, b);
    }
    else
    {
      if (!tty_term_has(tty->term, TTYC_SETRGBB))
      {
        return -1;
      }
      colour_split_rgb(colour & 0xffffff, &r, &g, &b);
      tty_putcode3(tty, TTYC_SETRGBB, r, g, b);
    }
    return 0;
  }
  return -1;
  fallback_256:
  xsnprintf(s, sizeof(s), "\033[%s;5;%dm", type, colour & 0xff);

  log_debug("%s: 256 colour fallback: %s", tty->client->name, s);
  tty_puts(tty, s);
  return 0;
}


/*** DEPENDENCIES:
int helper_tty_try_colour_1(struct tty * const tty, int colour, const char * const type)
{
  if ((tty->term_flags & 0x1) || tty_term_has(tty->term, TTYC_RGB))
  {
    goto fallback_256;
  }
  if (tty->term->flags & 0x1)
  {
    if ((*type) == '3')
    {
      if (!tty_term_has(tty->term, TTYC_SETAF))
      {
        goto fallback_256;
      }
      tty_putcode1(tty, TTYC_SETAF, colour & 0xff);
    }
    else
    {
      if (!tty_term_has(tty->term, TTYC_SETAB))
      {
        goto fallback_256;
      }
      tty_putcode1(tty, TTYC_SETAB, colour & 0xff);
    }
    return 0;
  }
  goto fallback_256;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
void tty_putcode3(struct tty *tty, enum tty_code_code code, int a, int b, int c)
{
  if (((a < 0) || (b < 0)) || (c < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string3(tty->term, code, a, b, c));
}


----------------------------
void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


static void tty_colours_bg(struct tty *tty, const struct grid_cell *gc)
{
  struct grid_cell *tc = &tty->cell;
  char s[32];
  if ((gc->bg & 0x02000000) || (gc->bg & 0x01000000))
  {
    if (tty_try_colour(tty, gc->bg, "48") == 0)
    {
      goto save_bg;
    }
    return;
  }
  if ((gc->bg >= 90) && (gc->bg <= 97))
  {
    xsnprintf(s, sizeof(s), "\033[%dm", gc->bg + 10);
    tty_puts(tty, s);
    goto save_bg;
  }
  tty_putcode1(tty, TTYC_SETAB, gc->bg);
  save_bg:
  tc->bg = gc->bg;

}


/*** DEPENDENCIES:
static int tty_try_colour(struct tty *tty, int colour, const char *type)
{
  u_char r;
  u_char g;
  u_char b;
  char s[32];
  if (colour & 0x01000000)
  {
    helper_tty_try_colour_1(tty, colour, type);
  }
  if (colour & 0x02000000)
  {
    if ((*type) == '3')
    {
      if (!tty_term_has(tty->term, TTYC_SETRGBF))
      {
        return -1;
      }
      colour_split_rgb(colour & 0xffffff, &r, &g, &b);
      tty_putcode3(tty, TTYC_SETRGBF, r, g, b);
    }
    else
    {
      if (!tty_term_has(tty->term, TTYC_SETRGBB))
      {
        return -1;
      }
      colour_split_rgb(colour & 0xffffff, &r, &g, &b);
      tty_putcode3(tty, TTYC_SETRGBB, r, g, b);
    }
    return 0;
  }
  return -1;
  fallback_256:
  xsnprintf(s, sizeof(s), "\033[%s;5;%dm", type, colour & 0xff);

  log_debug("%s: 256 colour fallback: %s", tty->client->name, s);
  tty_puts(tty, s);
  return 0;
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


static void tty_colours_fg(struct tty *tty, const struct grid_cell *gc)
{
  struct grid_cell *tc = &tty->cell;
  char s[32];
  if ((gc->fg & 0x02000000) || (gc->fg & 0x01000000))
  {
    if (tty_try_colour(tty, gc->fg, "38") == 0)
    {
      goto save_fg;
    }
    return;
  }
  if ((gc->fg >= 90) && (gc->fg <= 97))
  {
    xsnprintf(s, sizeof(s), "\033[%dm", gc->fg);
    tty_puts(tty, s);
    goto save_fg;
  }
  tty_putcode1(tty, TTYC_SETAF, gc->fg);
  save_fg:
  tc->fg = gc->fg;

}


/*** DEPENDENCIES:
static int tty_try_colour(struct tty *tty, int colour, const char *type)
{
  u_char r;
  u_char g;
  u_char b;
  char s[32];
  if (colour & 0x01000000)
  {
    helper_tty_try_colour_1(tty, colour, type);
  }
  if (colour & 0x02000000)
  {
    if ((*type) == '3')
    {
      if (!tty_term_has(tty->term, TTYC_SETRGBF))
      {
        return -1;
      }
      colour_split_rgb(colour & 0xffffff, &r, &g, &b);
      tty_putcode3(tty, TTYC_SETRGBF, r, g, b);
    }
    else
    {
      if (!tty_term_has(tty->term, TTYC_SETRGBB))
      {
        return -1;
      }
      colour_split_rgb(colour & 0xffffff, &r, &g, &b);
      tty_putcode3(tty, TTYC_SETRGBB, r, g, b);
    }
    return 0;
  }
  return -1;
  fallback_256:
  xsnprintf(s, sizeof(s), "\033[%s;5;%dm", type, colour & 0xff);

  log_debug("%s: 256 colour fallback: %s", tty->client->name, s);
  tty_puts(tty, s);
  return 0;
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


static void tty_colours(struct tty *tty, const struct grid_cell *gc)
{
  struct grid_cell *tc = &tty->cell;
  int have_ax;
  if ((gc->fg == tc->fg) && (gc->bg == tc->bg))
  {
    return;
  }
  if ((gc->fg == 8) || (gc->bg == 8))
  {
    have_ax = tty_term_flag(tty->term, TTYC_AX);
    if ((!have_ax) && tty_term_has(tty->term, TTYC_OP))
    {
      tty_reset(tty);
    }
    else
    {
      if ((gc->fg == 8) && (tc->fg != 8))
      {
        if (have_ax)
        {
          tty_puts(tty, "\033[39m");
        }
        else
          if (tc->fg != 7)
        {
          tty_putcode1(tty, TTYC_SETAF, 7);
        }
        tc->fg = 8;
      }
      if ((gc->bg == 8) && (tc->bg != 8))
      {
        if (have_ax)
        {
          tty_puts(tty, "\033[49m");
        }
        else
          if (tc->bg != 0)
        {
          tty_putcode1(tty, TTYC_SETAB, 0);
        }
        tc->bg = 8;
      }
    }
  }
  if ((gc->fg != 8) && (gc->fg != tc->fg))
  {
    tty_colours_fg(tty, gc);
  }
  if ((gc->bg != 8) && (gc->bg != tc->bg))
  {
    tty_colours_bg(tty, gc);
  }
}


/*** DEPENDENCIES:
void tty_reset(struct tty *tty)
{
  struct grid_cell *gc = &tty->cell;
  if (!grid_cells_equal(gc, &grid_default_cell))
  {
    if ((gc->attr & 0x80) && tty_acs_needed(tty))
    {
      tty_putcode(tty, TTYC_RMACS);
    }
    tty_putcode(tty, TTYC_SGR0);
    memcpy(gc, &grid_default_cell, sizeof(*gc));
  }
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
}


----------------------------
static void tty_colours_bg(struct tty *tty, const struct grid_cell *gc)
{
  struct grid_cell *tc = &tty->cell;
  char s[32];
  if ((gc->bg & 0x02000000) || (gc->bg & 0x01000000))
  {
    if (tty_try_colour(tty, gc->bg, "48") == 0)
    {
      goto save_bg;
    }
    return;
  }
  if ((gc->bg >= 90) && (gc->bg <= 97))
  {
    xsnprintf(s, sizeof(s), "\033[%dm", gc->bg + 10);
    tty_puts(tty, s);
    goto save_bg;
  }
  tty_putcode1(tty, TTYC_SETAB, gc->bg);
  save_bg:
  tc->bg = gc->bg;

}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
int tty_term_flag(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return 0;
  }
  if (term->codes[code].type != TTYCODE_FLAG)
  {
    fatalx("not a flag: %d", code);
  }
  return term->codes[code].value.flag;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
static void tty_colours_fg(struct tty *tty, const struct grid_cell *gc)
{
  struct grid_cell *tc = &tty->cell;
  char s[32];
  if ((gc->fg & 0x02000000) || (gc->fg & 0x01000000))
  {
    if (tty_try_colour(tty, gc->fg, "38") == 0)
    {
      goto save_fg;
    }
    return;
  }
  if ((gc->fg >= 90) && (gc->fg <= 97))
  {
    xsnprintf(s, sizeof(s), "\033[%dm", gc->fg);
    tty_puts(tty, s);
    goto save_fg;
  }
  tty_putcode1(tty, TTYC_SETAF, gc->fg);
  save_fg:
  tc->fg = gc->fg;

}


----------------------------
None
----------------------------
***/


static void tty_set_italics(struct tty *tty)
{
  const char *s;
  unsigned int s_idx = 0;
  if (tty_term_has(tty->term, TTYC_SITM))
  {
    s_idx = options_get_string(global_options, "default-terminal");
    if ((strcmp(s, "screen") != 0) && (strncmp(s, "screen-", 7) != 0))
    {
      tty_putcode(tty, TTYC_SITM);
      return;
    }
  }
  tty_putcode(tty, TTYC_SMSO);
}


/*** DEPENDENCIES:
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
***/


static void tty_check_fg(struct tty *tty, const struct window_pane *wp, struct grid_cell *gc)
{
  u_char r;
  u_char g;
  u_char b;
  u_int colours;
  int c;
  if ((~gc->flags) & 0x20)
  {
    c = gc->fg;
    if ((c < 8) && (gc->attr & 0x1))
    {
      c += 90;
    }
    if ((c = window_pane_get_palette(wp, c)) != (-1))
    {
      gc->fg = c;
    }
  }
  if (gc->fg & 0x02000000)
  {
    if (!tty_term_has(tty->term, TTYC_SETRGBF))
    {
      colour_split_rgb(gc->fg, &r, &g, &b);
      gc->fg = colour_find_rgb(r, g, b);
    }
    else
      return;
  }
  if ((tty->term->flags | tty->term_flags) & 0x1)
  {
    colours = 256;
  }
  else
    colours = tty_term_number(tty->term, TTYC_COLORS);
  if (gc->fg & 0x01000000)
  {
    if (colours != 256)
    {
      gc->fg = colour_256to16(gc->fg);
      if (gc->fg & 8)
      {
        gc->fg &= 7;
        if (colours >= 16)
        {
          gc->fg += 90;
        }
        else
          gc->attr |= 0x1;
      }
      else
        gc->attr &= ~0x1;
    }
    return;
  }
  if (((gc->fg >= 90) && (gc->fg <= 97)) && (colours < 16))
  {
    gc->fg -= 90;
    gc->attr |= 0x1;
  }
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
int colour_find_rgb(u_char r, u_char g, u_char b)
{
  static const int q2c[6] = {0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff};
  int qr;
  int qg;
  int qb;
  int cr;
  int cg;
  int cb;
  int d;
  int idx;
  int grey_avg;
  int grey_idx;
  int grey;
  qr = colour_to_6cube(r);
  cr = q2c[qr];
  qg = colour_to_6cube(g);
  cg = q2c[qg];
  qb = colour_to_6cube(b);
  cb = q2c[qb];
  if (((cr == r) && (cg == g)) && (cb == b))
  {
    return (((16 + (36 * qr)) + (6 * qg)) + qb) | 0x01000000;
  }
  grey_avg = ((r + g) + b) / 3;
  if (grey_avg > 238)
  {
    grey_idx = 23;
  }
  else
    grey_idx = (grey_avg - 3) / 10;
  grey = 8 + (10 * grey_idx);
  d = colour_dist_sq(cr, cg, cb, r, g, b);
  if (colour_dist_sq(grey, grey, grey, r, g, b) < d)
  {
    idx = 232 + grey_idx;
  }
  else
    idx = ((16 + (36 * qr)) + (6 * qg)) + qb;
  return idx | 0x01000000;
}


----------------------------
u_char colour_256to16(u_char c)
{
  static const u_char table[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 4, 4, 4, 12, 12, 2, 6, 4, 4, 12, 12, 2, 2, 6, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 5, 4, 4, 12, 12, 3, 8, 4, 4, 12, 12, 2, 2, 6, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 1, 5, 4, 12, 12, 1, 1, 5, 4, 12, 12, 3, 3, 8, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 1, 1, 5, 12, 12, 1, 1, 1, 5, 12, 12, 1, 1, 1, 5, 12, 12, 3, 3, 3, 7, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 11, 11, 11, 11, 7, 12, 10, 10, 10, 10, 10, 14, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 11, 11, 11, 11, 11, 15, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15};
  return table[c];
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
int window_pane_get_palette(const struct window_pane *wp, int c)
{
  int new;
  if ((wp == 0) || (wp->palette == 0))
  {
    return -1;
  }
  new = -1;
  if (c < 8)
  {
    new = wp->palette[c];
  }
  else
    if ((c >= 90) && (c <= 97))
  {
    new = wp->palette[(8 + c) - 90];
  }
  else
    if (c & 0x01000000)
  {
    new = wp->palette[c & (~0x01000000)];
  }
  if (new == 0)
  {
    return -1;
  }
  return new;
}


----------------------------
void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void tty_check_bg(struct tty *tty, const struct window_pane *wp, struct grid_cell *gc)
{
  u_char r;
  u_char g;
  u_char b;
  u_int colours;
  int c;
  if ((~gc->flags) & 0x20)
  {
    if ((c = window_pane_get_palette(wp, gc->bg)) != (-1))
    {
      gc->bg = c;
    }
  }
  if (gc->bg & 0x02000000)
  {
    if (!tty_term_has(tty->term, TTYC_SETRGBB))
    {
      colour_split_rgb(gc->bg, &r, &g, &b);
      gc->bg = colour_find_rgb(r, g, b);
    }
    else
      return;
  }
  if ((tty->term->flags | tty->term_flags) & 0x1)
  {
    colours = 256;
  }
  else
    colours = tty_term_number(tty->term, TTYC_COLORS);
  if (gc->bg & 0x01000000)
  {
    if (colours != 256)
    {
      gc->bg = colour_256to16(gc->bg);
      if (gc->bg & 8)
      {
        gc->bg &= 7;
        if (colours >= 16)
        {
          gc->fg += 90;
        }
      }
    }
    return;
  }
  if (((gc->bg >= 90) && (gc->bg <= 97)) && (colours < 16))
  {
    gc->bg -= 90;
  }
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
int colour_find_rgb(u_char r, u_char g, u_char b)
{
  static const int q2c[6] = {0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff};
  int qr;
  int qg;
  int qb;
  int cr;
  int cg;
  int cb;
  int d;
  int idx;
  int grey_avg;
  int grey_idx;
  int grey;
  qr = colour_to_6cube(r);
  cr = q2c[qr];
  qg = colour_to_6cube(g);
  cg = q2c[qg];
  qb = colour_to_6cube(b);
  cb = q2c[qb];
  if (((cr == r) && (cg == g)) && (cb == b))
  {
    return (((16 + (36 * qr)) + (6 * qg)) + qb) | 0x01000000;
  }
  grey_avg = ((r + g) + b) / 3;
  if (grey_avg > 238)
  {
    grey_idx = 23;
  }
  else
    grey_idx = (grey_avg - 3) / 10;
  grey = 8 + (10 * grey_idx);
  d = colour_dist_sq(cr, cg, cb, r, g, b);
  if (colour_dist_sq(grey, grey, grey, r, g, b) < d)
  {
    idx = 232 + grey_idx;
  }
  else
    idx = ((16 + (36 * qr)) + (6 * qg)) + qb;
  return idx | 0x01000000;
}


----------------------------
u_char colour_256to16(u_char c)
{
  static const u_char table[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 4, 4, 4, 12, 12, 2, 6, 4, 4, 12, 12, 2, 2, 6, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 5, 4, 4, 12, 12, 3, 8, 4, 4, 12, 12, 2, 2, 6, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 1, 5, 4, 12, 12, 1, 1, 5, 4, 12, 12, 3, 3, 8, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 1, 1, 5, 12, 12, 1, 1, 1, 5, 12, 12, 1, 1, 1, 5, 12, 12, 3, 3, 3, 7, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 11, 11, 11, 11, 7, 12, 10, 10, 10, 10, 10, 14, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 11, 11, 11, 11, 11, 15, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15};
  return table[c];
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
int window_pane_get_palette(const struct window_pane *wp, int c)
{
  int new;
  if ((wp == 0) || (wp->palette == 0))
  {
    return -1;
  }
  new = -1;
  if (c < 8)
  {
    new = wp->palette[c];
  }
  else
    if ((c >= 90) && (c <= 97))
  {
    new = wp->palette[(8 + c) - 90];
  }
  else
    if (c & 0x01000000)
  {
    new = wp->palette[c & (~0x01000000)];
  }
  if (new == 0)
  {
    return -1;
  }
  return new;
}


----------------------------
void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void tty_default_colours(struct grid_cell *gc, const struct window_pane *wp)
{
  struct window *w = wp->window;
  struct options *oo = w->options;
  const struct grid_cell *agc;
  unsigned int agc_idx = 0;
  const struct grid_cell *pgc;
  unsigned int pgc_idx = 0;
  const struct grid_cell *wgc;
  unsigned int wgc_idx = 0;
  int c;
  if (w->flags & 0x8000)
  {
    w->flags &= ~0x8000;
    agc_idx = options_get_style(oo, "window-active-style");
    memcpy(&w->active_style, agc, sizeof(w->active_style));
    wgc_idx = options_get_style(oo, "window-style");
    memcpy(&w->style, wgc, sizeof(w->style));
  }
  else
  {
    agc_idx = &w->active_style;
    wgc_idx = &w->style;
  }
  pgc_idx = &wp->colgc;
  if (gc->fg == 8)
  {
    if (pgc->fg != 8)
    {
      gc->fg = pgc->fg;
    }
    else
      if ((wp == w->active) && (agc->fg != 8))
    {
      gc->fg = agc->fg;
    }
    else
      gc->fg = wgc->fg;
    if ((gc->fg != 8) && ((c = window_pane_get_palette(wp, gc->fg)) != (-1)))
    {
      gc->fg = c;
    }
  }
  if (gc->bg == 8)
  {
    if (pgc->bg != 8)
    {
      gc->bg = pgc->bg;
    }
    else
      if ((wp == w->active) && (agc->bg != 8))
    {
      gc->bg = agc->bg;
    }
    else
      gc->bg = wgc->bg;
    if ((gc->bg != 8) && ((c = window_pane_get_palette(wp, gc->bg)) != (-1)))
    {
      gc->bg = c;
    }
  }
}


/*** DEPENDENCIES:
const struct grid_cell *options_get_style(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  return &o->style;
}


----------------------------
None
----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
int window_pane_get_palette(const struct window_pane *wp, int c)
{
  int new;
  if ((wp == 0) || (wp->palette == 0))
  {
    return -1;
  }
  new = -1;
  if (c < 8)
  {
    new = wp->palette[c];
  }
  else
    if ((c >= 90) && (c <= 97))
  {
    new = wp->palette[(8 + c) - 90];
  }
  else
    if (c & 0x01000000)
  {
    new = wp->palette[c & (~0x01000000)];
  }
  if (new == 0)
  {
    return -1;
  }
  return new;
}


----------------------------
None
----------------------------
None
----------------------------
***/


void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


/*** DEPENDENCIES:
void tty_reset(struct tty *tty)
{
  struct grid_cell *gc = &tty->cell;
  if (!grid_cells_equal(gc, &grid_default_cell))
  {
    if ((gc->attr & 0x80) && tty_acs_needed(tty))
    {
      tty_putcode(tty, TTYC_RMACS);
    }
    tty_putcode(tty, TTYC_SGR0);
    memcpy(gc, &grid_default_cell, sizeof(*gc));
  }
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
}


----------------------------
static void tty_colours(struct tty *tty, const struct grid_cell *gc)
{
  struct grid_cell *tc = &tty->cell;
  int have_ax;
  if ((gc->fg == tc->fg) && (gc->bg == tc->bg))
  {
    return;
  }
  if ((gc->fg == 8) || (gc->bg == 8))
  {
    have_ax = tty_term_flag(tty->term, TTYC_AX);
    if ((!have_ax) && tty_term_has(tty->term, TTYC_OP))
    {
      tty_reset(tty);
    }
    else
    {
      if ((gc->fg == 8) && (tc->fg != 8))
      {
        if (have_ax)
        {
          tty_puts(tty, "\033[39m");
        }
        else
          if (tc->fg != 7)
        {
          tty_putcode1(tty, TTYC_SETAF, 7);
        }
        tc->fg = 8;
      }
      if ((gc->bg == 8) && (tc->bg != 8))
      {
        if (have_ax)
        {
          tty_puts(tty, "\033[49m");
        }
        else
          if (tc->bg != 0)
        {
          tty_putcode1(tty, TTYC_SETAB, 0);
        }
        tc->bg = 8;
      }
    }
  }
  if ((gc->fg != 8) && (gc->fg != tc->fg))
  {
    tty_colours_fg(tty, gc);
  }
  if ((gc->bg != 8) && (gc->bg != tc->bg))
  {
    tty_colours_bg(tty, gc);
  }
}


----------------------------
static void tty_set_italics(struct tty *tty)
{
  const char *s;
  unsigned int s_idx = 0;
  if (tty_term_has(tty->term, TTYC_SITM))
  {
    s_idx = options_get_string(global_options, "default-terminal");
    if ((strcmp(s, "screen") != 0) && (strncmp(s, "screen-", 7) != 0))
    {
      tty_putcode(tty, TTYC_SITM);
      return;
    }
  }
  tty_putcode(tty, TTYC_SMSO);
}


----------------------------
static void tty_check_fg(struct tty *tty, const struct window_pane *wp, struct grid_cell *gc)
{
  u_char r;
  u_char g;
  u_char b;
  u_int colours;
  int c;
  if ((~gc->flags) & 0x20)
  {
    c = gc->fg;
    if ((c < 8) && (gc->attr & 0x1))
    {
      c += 90;
    }
    if ((c = window_pane_get_palette(wp, c)) != (-1))
    {
      gc->fg = c;
    }
  }
  if (gc->fg & 0x02000000)
  {
    if (!tty_term_has(tty->term, TTYC_SETRGBF))
    {
      colour_split_rgb(gc->fg, &r, &g, &b);
      gc->fg = colour_find_rgb(r, g, b);
    }
    else
      return;
  }
  if ((tty->term->flags | tty->term_flags) & 0x1)
  {
    colours = 256;
  }
  else
    colours = tty_term_number(tty->term, TTYC_COLORS);
  if (gc->fg & 0x01000000)
  {
    if (colours != 256)
    {
      gc->fg = colour_256to16(gc->fg);
      if (gc->fg & 8)
      {
        gc->fg &= 7;
        if (colours >= 16)
        {
          gc->fg += 90;
        }
        else
          gc->attr |= 0x1;
      }
      else
        gc->attr &= ~0x1;
    }
    return;
  }
  if (((gc->fg >= 90) && (gc->fg <= 97)) && (colours < 16))
  {
    gc->fg -= 90;
    gc->attr |= 0x1;
  }
}


----------------------------
static void tty_check_bg(struct tty *tty, const struct window_pane *wp, struct grid_cell *gc)
{
  u_char r;
  u_char g;
  u_char b;
  u_int colours;
  int c;
  if ((~gc->flags) & 0x20)
  {
    if ((c = window_pane_get_palette(wp, gc->bg)) != (-1))
    {
      gc->bg = c;
    }
  }
  if (gc->bg & 0x02000000)
  {
    if (!tty_term_has(tty->term, TTYC_SETRGBB))
    {
      colour_split_rgb(gc->bg, &r, &g, &b);
      gc->bg = colour_find_rgb(r, g, b);
    }
    else
      return;
  }
  if ((tty->term->flags | tty->term_flags) & 0x1)
  {
    colours = 256;
  }
  else
    colours = tty_term_number(tty->term, TTYC_COLORS);
  if (gc->bg & 0x01000000)
  {
    if (colours != 256)
    {
      gc->bg = colour_256to16(gc->bg);
      if (gc->bg & 8)
      {
        gc->bg &= 7;
        if (colours >= 16)
        {
          gc->fg += 90;
        }
      }
    }
    return;
  }
  if (((gc->bg >= 90) && (gc->bg <= 97)) && (colours < 16))
  {
    gc->bg -= 90;
  }
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
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
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
static void tty_default_colours(struct grid_cell *gc, const struct window_pane *wp)
{
  struct window *w = wp->window;
  struct options *oo = w->options;
  const struct grid_cell *agc;
  unsigned int agc_idx = 0;
  const struct grid_cell *pgc;
  unsigned int pgc_idx = 0;
  const struct grid_cell *wgc;
  unsigned int wgc_idx = 0;
  int c;
  if (w->flags & 0x8000)
  {
    w->flags &= ~0x8000;
    agc_idx = options_get_style(oo, "window-active-style");
    memcpy(&w->active_style, agc, sizeof(w->active_style));
    wgc_idx = options_get_style(oo, "window-style");
    memcpy(&w->style, wgc, sizeof(w->style));
  }
  else
  {
    agc_idx = &w->active_style;
    wgc_idx = &w->style;
  }
  pgc_idx = &wp->colgc;
  if (gc->fg == 8)
  {
    if (pgc->fg != 8)
    {
      gc->fg = pgc->fg;
    }
    else
      if ((wp == w->active) && (agc->fg != 8))
    {
      gc->fg = agc->fg;
    }
    else
      gc->fg = wgc->fg;
    if ((gc->fg != 8) && ((c = window_pane_get_palette(wp, gc->fg)) != (-1)))
    {
      gc->fg = c;
    }
  }
  if (gc->bg == 8)
  {
    if (pgc->bg != 8)
    {
      gc->bg = pgc->bg;
    }
    else
      if ((wp == w->active) && (agc->bg != 8))
    {
      gc->bg = agc->bg;
    }
    else
      gc->bg = wgc->bg;
    if ((gc->bg != 8) && ((c = window_pane_get_palette(wp, gc->bg)) != (-1)))
    {
      gc->bg = c;
    }
  }
}


----------------------------
None
----------------------------
None
----------------------------
***/


void tty_cmd_cells(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);
  tty_attributes(tty, ctx->cell, ctx->wp);
  tty_putn(tty, ctx->ptr, ctx->num, ctx->num);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane_unless_wrap(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  if (((((((!ctx->wrapped) || (!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx)))) || (tty->term->flags & 0x2)) || ((ctx->xoff + cx) != 0)) || ((ctx->yoff + cy) != (tty->cy + 1))) || (tty->cx < tty->sx)) || (tty->cy == tty->rlower))
  {
    tty_cursor_pane(tty, ctx, cx, cy);
  }
  else
    log_debug("%s: will wrap at %u,%u", __func__, tty->cx, tty->cy);
}


----------------------------
void tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
  tty_add(tty, buf, len);
  if ((tty->cx + width) > tty->sx)
  {
    tty->cx = (tty->cx + width) - tty->sx;
    if (tty->cx <= tty->sx)
    {
      tty->cy += 1;
    }
    else
      tty->cx = (tty->cy = 4294967295U);
  }
  else
    tty->cx += width;
}


----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
None
----------------------------
***/


static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
None
----------------------------
***/


static void tty_region(struct tty *tty, u_int rupper, u_int rlower)
{
  if ((tty->rlower == rlower) && (tty->rupper == rupper))
  {
    return;
  }
  if (!tty_term_has(tty->term, TTYC_CSR))
  {
    return;
  }
  tty->rupper = rupper;
  tty->rlower = rlower;
  if (tty->cx >= tty->sx)
  {
    tty_cursor(tty, 0, tty->cy);
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->cx = (tty->cy = 4294967295U);
}


/*** DEPENDENCIES:
void tty_putcode2(struct tty *tty, enum tty_code_code code, int a, int b)
{
  if ((a < 0) || (b < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string2(tty->term, code, a, b));
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
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


static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_region(struct tty *tty, u_int rupper, u_int rlower)
{
  if ((tty->rlower == rlower) && (tty->rupper == rupper))
  {
    return;
  }
  if (!tty_term_has(tty->term, TTYC_CSR))
  {
    return;
  }
  tty->rupper = rupper;
  tty->rlower = rlower;
  if (tty->cx >= tty->sx)
  {
    tty_cursor(tty, 0, tty->cy);
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
None
----------------------------
***/


static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
int tty_term_flag(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return 0;
  }
  if (term->codes[code].type != TTYCODE_FLAG)
  {
    fatalx("not a flag: %d", code);
  }
  return term->codes[code].value.flag;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
static void tty_default_colours(struct grid_cell *gc, const struct window_pane *wp)
{
  struct window *w = wp->window;
  struct options *oo = w->options;
  const struct grid_cell *agc;
  unsigned int agc_idx = 0;
  const struct grid_cell *pgc;
  unsigned int pgc_idx = 0;
  const struct grid_cell *wgc;
  unsigned int wgc_idx = 0;
  int c;
  if (w->flags & 0x8000)
  {
    w->flags &= ~0x8000;
    agc_idx = options_get_style(oo, "window-active-style");
    memcpy(&w->active_style, agc, sizeof(w->active_style));
    wgc_idx = options_get_style(oo, "window-style");
    memcpy(&w->style, wgc, sizeof(w->style));
  }
  else
  {
    agc_idx = &w->active_style;
    wgc_idx = &w->style;
  }
  pgc_idx = &wp->colgc;
  if (gc->fg == 8)
  {
    if (pgc->fg != 8)
    {
      gc->fg = pgc->fg;
    }
    else
      if ((wp == w->active) && (agc->fg != 8))
    {
      gc->fg = agc->fg;
    }
    else
      gc->fg = wgc->fg;
    if ((gc->fg != 8) && ((c = window_pane_get_palette(wp, gc->fg)) != (-1)))
    {
      gc->fg = c;
    }
  }
  if (gc->bg == 8)
  {
    if (pgc->bg != 8)
    {
      gc->bg = pgc->bg;
    }
    else
      if ((wp == w->active) && (agc->bg != 8))
    {
      gc->bg = agc->bg;
    }
    else
      gc->bg = wgc->bg;
    if ((gc->bg != 8) && ((c = window_pane_get_palette(wp, gc->bg)) != (-1)))
    {
      gc->bg = c;
    }
  }
}


----------------------------
None
----------------------------
None
----------------------------
***/


static int tty_large_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  return (ctx->orlower - ctx->orupper) >= (wp->screen->grid->sy / 2);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
None
----------------------------
***/


static void tty_margin(struct tty *tty, u_int rleft, u_int rright)
{
  char s[64];
  if (!(tty->term_type == TTY_VT420))
  {
    return;
  }
  if ((tty->rleft == rleft) && (tty->rright == rright))
  {
    return;
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->rleft = rleft;
  tty->rright = rright;
  if ((rleft == 0) && (rright == (tty->sx - 1)))
  {
    snprintf(s, sizeof(s), "\033[s");
  }
  else
    snprintf(s, sizeof(s), "\033[%u;%us", rleft + 1, rright + 1);
  tty_puts(tty, s);
  tty->cx = (tty->cy = 4294967295U);
}


/*** DEPENDENCIES:
void tty_putcode2(struct tty *tty, enum tty_code_code code, int a, int b)
{
  if ((a < 0) || (b < 0))
  {
    return;
  }
  tty_puts(tty, tty_term_string2(tty->term, code, a, b));
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


/*** DEPENDENCIES:
static void tty_margin(struct tty *tty, u_int rleft, u_int rright)
{
  char s[64];
  if (!(tty->term_type == TTY_VT420))
  {
    return;
  }
  if ((tty->rleft == rleft) && (tty->rright == rright))
  {
    return;
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->rleft = rleft;
  tty->rright = rright;
  if ((rleft == 0) && (rright == (tty->sx - 1)))
  {
    snprintf(s, sizeof(s), "\033[s");
  }
  else
    snprintf(s, sizeof(s), "\033[%u;%us", rleft + 1, rright + 1);
  tty_puts(tty, s);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
None
----------------------------
***/


void tty_putcode_ptr1(struct tty *tty, enum tty_code_code code, const void *a)
{
  if (a != 0)
  {
    tty_puts(tty, tty_term_ptr1(tty->term, code, a));
  }
}


/*** DEPENDENCIES:
const char *tty_term_ptr1(struct tty_term *term, enum tty_code_code code, const void *a)
{
  return tparm((char *) tty_term_string(term, code), a, 0, 0, 0, 0, 0, 0, 0, 0);
}


----------------------------
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


static void tty_force_cursor_colour(struct tty *tty, const char *ccolour)
{
  if ((*ccolour) == '\0')
  {
    tty_putcode(tty, TTYC_CR);
  }
  else
    tty_putcode_ptr1(tty, TTYC_CS, ccolour);
  free(tty->ccolour);
  tty->ccolour = xstrdup(ccolour);
}


/*** DEPENDENCIES:
void tty_putcode_ptr1(struct tty *tty, enum tty_code_code code, const void *a)
{
  if (a != 0)
  {
    tty_puts(tty, tty_term_ptr1(tty->term, code, a));
  }
}


----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
***/


void helper_tty_update_mode_1(struct tty * const tty, int mode)
{
  if (mode & ((0x20 | 0x40) | 0x1000))
  {
    tty_puts(tty, "\033[?1006h");
    if (mode & 0x1000)
    {
      tty_puts(tty, "\033[?1003h");
    }
    else
      if (mode & 0x40)
    {
      tty_puts(tty, "\033[?1002h");
    }
    else
      if (mode & 0x20)
    {
      tty_puts(tty, "\033[?1000h");
    }
  }
  else
  {
    if (tty->mode & 0x1000)
    {
      tty_puts(tty, "\033[?1003l");
    }
    else
      if (tty->mode & 0x40)
    {
      tty_puts(tty, "\033[?1002l");
    }
    else
      if (tty->mode & 0x20)
    {
      tty_puts(tty, "\033[?1000l");
    }
    tty_puts(tty, "\033[?1006l");
  }
}


/*** DEPENDENCIES:
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


void tty_update_mode(struct tty *tty, int mode, struct screen *s)
{
  int changed;
  if ((s != 0) && (strcmp(s->ccolour, tty->ccolour) != 0))
  {
    tty_force_cursor_colour(tty, s->ccolour);
  }
  if (tty->flags & 0x1)
  {
    mode &= ~0x1;
  }
  changed = mode ^ tty->mode;
  if (changed & 0x80)
  {
    if (tty_term_has(tty->term, TTYC_CVVIS))
    {
      tty_putcode(tty, TTYC_CVVIS);
    }
    else
      tty_putcode(tty, TTYC_CNORM);
    changed |= 0x1;
  }
  if (changed & 0x1)
  {
    if (mode & 0x1)
    {
      tty_putcode(tty, TTYC_CNORM);
    }
    else
      tty_putcode(tty, TTYC_CIVIS);
  }
  if ((s != 0) && (tty->cstyle != s->cstyle))
  {
    if (tty_term_has(tty->term, TTYC_SS))
    {
      if ((s->cstyle == 0) && tty_term_has(tty->term, TTYC_SE))
      {
        tty_putcode(tty, TTYC_SE);
      }
      else
        tty_putcode1(tty, TTYC_SS, s->cstyle);
    }
    tty->cstyle = s->cstyle;
  }
  if (changed & ((0x20 | 0x40) | 0x1000))
  {
    helper_tty_update_mode_1(tty, mode);
  }
  if (changed & 0x400)
  {
    if (mode & 0x400)
    {
      tty_puts(tty, "\033[?2004h");
    }
    else
      tty_puts(tty, "\033[?2004l");
  }
  tty->mode = mode;
}


/*** DEPENDENCIES:
static void tty_force_cursor_colour(struct tty *tty, const char *ccolour)
{
  if ((*ccolour) == '\0')
  {
    tty_putcode(tty, TTYC_CR);
  }
  else
    tty_putcode_ptr1(tty, TTYC_CS, ccolour);
  free(tty->ccolour);
  tty->ccolour = xstrdup(ccolour);
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
void helper_tty_update_mode_1(struct tty * const tty, int mode)
{
  if (mode & ((0x20 | 0x40) | 0x1000))
  {
    tty_puts(tty, "\033[?1006h");
    if (mode & 0x1000)
    {
      tty_puts(tty, "\033[?1003h");
    }
    else
      if (mode & 0x40)
    {
      tty_puts(tty, "\033[?1002h");
    }
    else
      if (mode & 0x20)
    {
      tty_puts(tty, "\033[?1000h");
    }
  }
  else
  {
    if (tty->mode & 0x1000)
    {
      tty_puts(tty, "\033[?1003l");
    }
    else
      if (tty->mode & 0x40)
    {
      tty_puts(tty, "\033[?1002l");
    }
    else
      if (tty->mode & 0x20)
    {
      tty_puts(tty, "\033[?1000l");
    }
    tty_puts(tty, "\033[?1006l");
  }
}


----------------------------
None
----------------------------
***/


static void tty_repeat_space(struct tty *tty, u_int n)
{
  static char s[500];
  if ((*s) != ' ')
  {
    memset(s, ' ', sizeof(s));
  }
  while (n > (sizeof(s)))
  {
    tty_putn(tty, s, sizeof(s), sizeof(s));
    n -= sizeof(s);
  }

  if (n != 0)
  {
    tty_putn(tty, s, n, n);
  }
}


/*** DEPENDENCIES:
void tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
  tty_add(tty, buf, len);
  if ((tty->cx + width) > tty->sx)
  {
    tty->cx = (tty->cx + width) - tty->sx;
    if (tty->cx <= tty->sx)
    {
      tty->cy += 1;
    }
    else
      tty->cx = (tty->cy = 4294967295U);
  }
  else
    tty->cx += width;
}


----------------------------
None
----------------------------
***/


static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


/*** DEPENDENCIES:
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
static void tty_repeat_space(struct tty *tty, u_int n)
{
  static char s[500];
  if ((*s) != ' ')
  {
    memset(s, ' ', sizeof(s));
  }
  while (n > (sizeof(s)))
  {
    tty_putn(tty, s, sizeof(s), sizeof(s));
    n -= sizeof(s);
  }

  if (n != 0)
  {
    tty_putn(tty, s, n, n);
  }
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


void tty_region_off(struct tty *tty)
{
  tty_region(tty, 0, tty->sy - 1);
}


/*** DEPENDENCIES:
static void tty_region(struct tty *tty, u_int rupper, u_int rlower)
{
  if ((tty->rlower == rlower) && (tty->rupper == rupper))
  {
    return;
  }
  if (!tty_term_has(tty->term, TTYC_CSR))
  {
    return;
  }
  tty->rupper = rupper;
  tty->rlower = rlower;
  if (tty->cx >= tty->sx)
  {
    tty_cursor(tty, 0, tty->cy);
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
None
----------------------------
***/


static const struct grid_cell *tty_check_codeset(struct tty *tty, const struct grid_cell *gc)
{
  static struct grid_cell new;
  u_int n;
  if ((gc->data.size == 1) && ((*gc->data.data) < 0x7f))
  {
    return gc;
  }
  if (tty->flags & 0x8)
  {
    return gc;
  }
  n = gc->data.width;
  if (n > 9)
  {
    n = 9;
  }
  memcpy(&new, gc, sizeof(new));
  new.data.size = n;
  memset(new.data.data, '_', n);
  return &new;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['gcp_idx_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to u_int', 'ux_ref is a mutable refrence to u_int', 'width_ref is a mutable refrence to u_int', 'len_ref is a mutable refrence to size_t']
void helper_tty_draw_line_1(unsigned int * const gcp_idx_ref, u_int * const j_ref, u_int * const ux_ref, u_int * const width_ref, size_t * const len_ref, struct tty * const tty, const struct window_pane * const wp, struct screen * const s, u_int py, struct grid * const gd, struct grid_cell gc, struct grid_cell last, const struct grid_cell * const gcp, u_int i, char buf[512])
{
  unsigned int gcp_idx = *gcp_idx_ref;
  u_int j = *j_ref;
  u_int ux = *ux_ref;
  u_int width = *width_ref;
  size_t len = *len_ref;
  grid_view_get_cell(gd, i, py, &gc);
  gcp_idx = tty_check_codeset(tty, &gc);
  if ((len != 0) && (((((((gcp->attr & 0x80) || (gcp->flags != last.flags)) || (gcp->attr != last.attr)) || (gcp->fg != last.fg)) || (gcp->bg != last.bg)) || (((ux + width) + gcp->data.width) >= s->grid->sx)) || (((sizeof(buf)) - len) < gcp->data.size)))
  {
    tty_attributes(tty, &last, wp);
    tty_putn(tty, buf, len, width);
    ux += width;
    len = 0;
    width = 0;
  }
  if (gcp->flags & 0x10)
  {
    screen_select_cell(s, &last, gcp);
  }
  else
    memcpy(&last, gcp, sizeof(last));
  if ((ux + gcp->data.width) > s->grid->sx)
  {
    tty_attributes(tty, &last, wp);
    for (j = 0; j < gcp->data.width; j += 1)
    {
      if ((ux + j) > s->grid->sx)
      {
        break;
      }
      tty_putc(tty, ' ');
      ux += 1;
    }

  }
  else
    if (gcp->attr & 0x80)
  {
    tty_attributes(tty, &last, wp);
    for (j = 0; j < gcp->data.size; j += 1)
    {
      tty_putc(tty, gcp->data.data[j]);
    }

    ux += gc.data.width;
  }
  else
  {
    memcpy(buf + len, gcp->data.data, gcp->data.size);
    len += gcp->data.size;
    width += gcp->data.width;
  }
  *gcp_idx_ref = gcp_idx;
  *j_ref = j;
  *ux_ref = ux;
  *width_ref = width;
  *len_ref = len;
}


/*** DEPENDENCIES:
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
void screen_select_cell(struct screen *s, struct grid_cell *dst, const struct grid_cell *src)
{
  if ((!s->sel.flag) || s->sel.hidden)
  {
    return;
  }
  memcpy(dst, &s->sel.cell, sizeof(*dst));
  utf8_copy(&dst->data, &src->data);
  dst->attr = dst->attr & (~0x80);
  dst->attr |= src->attr & 0x80;
  dst->flags = src->flags;
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
void tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
  tty_add(tty, buf, len);
  if ((tty->cx + width) > tty->sx)
  {
    tty->cx = (tty->cx + width) - tty->sx;
    if (tty->cx <= tty->sx)
    {
      tty->cy += 1;
    }
    else
      tty->cx = (tty->cy = 4294967295U);
  }
  else
    tty->cx += width;
}


----------------------------
None
----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
static const struct grid_cell *tty_check_codeset(struct tty *tty, const struct grid_cell *gc)
{
  static struct grid_cell new;
  u_int n;
  if ((gc->data.size == 1) && ((*gc->data.data) < 0x7f))
  {
    return gc;
  }
  if (tty->flags & 0x8)
  {
    return gc;
  }
  n = gc->data.width;
  if (n > 9)
  {
    n = 9;
  }
  memcpy(&new, gc, sizeof(new));
  new.data.size = n;
  memset(new.data.data, '_', n);
  return &new;
}


----------------------------
None
----------------------------
None
----------------------------
***/


void tty_draw_line(struct tty *tty, const struct window_pane *wp, struct screen *s, u_int py, u_int ox, u_int oy)
{
  struct grid *gd = s->grid;
  struct grid_cell gc;
  struct grid_cell last;
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  u_int i;
  u_int j;
  u_int ux;
  u_int sx;
  u_int nx;
  u_int width;
  int flags;
  int cleared = 0;
  char buf[512];
  size_t len;
  size_t old_len;
  flags = tty->flags & 0x1;
  tty->flags |= 0x1;
  tty_update_mode(tty, tty->mode, s);
  tty_region_off(tty);
  tty_margin_off(tty);
  sx = s->grid->sx;
  if (sx > gd->linedata[gd->hsize + py].cellsize)
  {
    sx = gd->linedata[gd->hsize + py].cellsize;
  }
  if (sx > tty->sx)
  {
    sx = tty->sx;
  }
  ux = 0;
  if ((((((wp == 0) || (py == 0)) || ((~gd->linedata[(gd->hsize + py) - 1].flags) & 0x1)) || (ox != 0)) || (tty->cx < tty->sx)) || (s->grid->sx < tty->sx))
  {
    if (((((s->grid->sx < tty->sx) && (ox == 0)) && (sx != s->grid->sx)) && tty_term_has(tty->term, TTYC_EL1)) && (!tty_fake_bce(tty, wp, 8)))
    {
      tty_default_attributes(tty, wp, 8);
      tty_cursor(tty, s->grid->sx - 1, oy + py);
      tty_putcode(tty, TTYC_EL1);
      cleared = 1;
    }
    if (sx != 0)
    {
      tty_cursor(tty, ox, oy + py);
    }
  }
  else
    log_debug("%s: wrapped line %u", __func__, oy + py);
  memcpy(&last, &grid_default_cell, sizeof(last));
  len = 0;
  width = 0;
  for (i = 0; i < sx; i += 1)
  {
    helper_tty_draw_line_1(&gcp_idx, &j, &ux, &width, &len, tty, wp, s, py, gd, gc, last, gcp, i, buf);
  }

  if (len != 0)
  {
    if (grid_cells_equal(&last, &grid_default_cell))
    {
      old_len = len;
      while ((len > 0) && (buf[len - 1] == ' '))
      {
        len -= 1;
        width -= 1;
      }

      log_debug("%s: trimmed %zu spaces", __func__, old_len - len);
    }
    if (len != 0)
    {
      tty_attributes(tty, &last, wp);
      tty_putn(tty, buf, len, width);
      ux += width;
    }
  }
  if ((!cleared) && (ux < s->grid->sx))
  {
    nx = s->grid->sx - ux;
    tty_default_attributes(tty, wp, 8);
    tty_clear_line(tty, wp, oy + py, ox + ux, nx, 8);
  }
  tty->flags = (tty->flags & (~0x1)) | flags;
  tty_update_mode(tty, tty->mode, s);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
void tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
  tty_add(tty, buf, len);
  if ((tty->cx + width) > tty->sx)
  {
    tty->cx = (tty->cx + width) - tty->sx;
    if (tty->cx <= tty->sx)
    {
      tty->cy += 1;
    }
    else
      tty->cx = (tty->cy = 4294967295U);
  }
  else
    tty->cx += width;
}


----------------------------
None
----------------------------
void tty_update_mode(struct tty *tty, int mode, struct screen *s)
{
  int changed;
  if ((s != 0) && (strcmp(s->ccolour, tty->ccolour) != 0))
  {
    tty_force_cursor_colour(tty, s->ccolour);
  }
  if (tty->flags & 0x1)
  {
    mode &= ~0x1;
  }
  changed = mode ^ tty->mode;
  if (changed & 0x80)
  {
    if (tty_term_has(tty->term, TTYC_CVVIS))
    {
      tty_putcode(tty, TTYC_CVVIS);
    }
    else
      tty_putcode(tty, TTYC_CNORM);
    changed |= 0x1;
  }
  if (changed & 0x1)
  {
    if (mode & 0x1)
    {
      tty_putcode(tty, TTYC_CNORM);
    }
    else
      tty_putcode(tty, TTYC_CIVIS);
  }
  if ((s != 0) && (tty->cstyle != s->cstyle))
  {
    if (tty_term_has(tty->term, TTYC_SS))
    {
      if ((s->cstyle == 0) && tty_term_has(tty->term, TTYC_SE))
      {
        tty_putcode(tty, TTYC_SE);
      }
      else
        tty_putcode1(tty, TTYC_SS, s->cstyle);
    }
    tty->cstyle = s->cstyle;
  }
  if (changed & ((0x20 | 0x40) | 0x1000))
  {
    helper_tty_update_mode_1(tty, mode);
  }
  if (changed & 0x400)
  {
    if (mode & 0x400)
    {
      tty_puts(tty, "\033[?2004h");
    }
    else
      tty_puts(tty, "\033[?2004l");
  }
  tty->mode = mode;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
void tty_region_off(struct tty *tty)
{
  tty_region(tty, 0, tty->sy - 1);
}


----------------------------
int grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
  if ((gca->fg != gcb->fg) || (gca->bg != gcb->bg))
  {
    return 0;
  }
  if ((gca->attr != gcb->attr) || (gca->flags != gcb->flags))
  {
    return 0;
  }
  if (gca->data.width != gcb->data.width)
  {
    return 0;
  }
  if (gca->data.size != gcb->data.size)
  {
    return 0;
  }
  return memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0;
}


----------------------------
void helper_tty_draw_line_1(unsigned int * const gcp_idx_ref, u_int * const j_ref, u_int * const ux_ref, u_int * const width_ref, size_t * const len_ref, struct tty * const tty, const struct window_pane * const wp, struct screen * const s, u_int py, struct grid * const gd, struct grid_cell gc, struct grid_cell last, const struct grid_cell * const gcp, u_int i, char buf[512])
{
  unsigned int gcp_idx = *gcp_idx_ref;
  u_int j = *j_ref;
  u_int ux = *ux_ref;
  u_int width = *width_ref;
  size_t len = *len_ref;
  grid_view_get_cell(gd, i, py, &gc);
  gcp_idx = tty_check_codeset(tty, &gc);
  if ((len != 0) && (((((((gcp->attr & 0x80) || (gcp->flags != last.flags)) || (gcp->attr != last.attr)) || (gcp->fg != last.fg)) || (gcp->bg != last.bg)) || (((ux + width) + gcp->data.width) >= s->grid->sx)) || (((sizeof(buf)) - len) < gcp->data.size)))
  {
    tty_attributes(tty, &last, wp);
    tty_putn(tty, buf, len, width);
    ux += width;
    len = 0;
    width = 0;
  }
  if (gcp->flags & 0x10)
  {
    screen_select_cell(s, &last, gcp);
  }
  else
    memcpy(&last, gcp, sizeof(last));
  if ((ux + gcp->data.width) > s->grid->sx)
  {
    tty_attributes(tty, &last, wp);
    for (j = 0; j < gcp->data.width; j += 1)
    {
      if ((ux + j) > s->grid->sx)
      {
        break;
      }
      tty_putc(tty, ' ');
      ux += 1;
    }

  }
  else
    if (gcp->attr & 0x80)
  {
    tty_attributes(tty, &last, wp);
    for (j = 0; j < gcp->data.size; j += 1)
    {
      tty_putc(tty, gcp->data.data[j]);
    }

    ux += gc.data.width;
  }
  else
  {
    memcpy(buf + len, gcp->data.data, gcp->data.size);
    len += gcp->data.size;
    width += gcp->data.width;
  }
  *gcp_idx_ref = gcp_idx;
  *j_ref = j;
  *ux_ref = ux;
  *width_ref = width;
  *len_ref = len;
}


----------------------------
None
----------------------------
***/


void tty_draw_pane(struct tty *tty, const struct window_pane *wp, u_int py, u_int ox, u_int oy)
{
  tty_draw_line(tty, wp, wp->screen, py, ox, oy);
}


/*** DEPENDENCIES:
void tty_draw_line(struct tty *tty, const struct window_pane *wp, struct screen *s, u_int py, u_int ox, u_int oy)
{
  struct grid *gd = s->grid;
  struct grid_cell gc;
  struct grid_cell last;
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  u_int i;
  u_int j;
  u_int ux;
  u_int sx;
  u_int nx;
  u_int width;
  int flags;
  int cleared = 0;
  char buf[512];
  size_t len;
  size_t old_len;
  flags = tty->flags & 0x1;
  tty->flags |= 0x1;
  tty_update_mode(tty, tty->mode, s);
  tty_region_off(tty);
  tty_margin_off(tty);
  sx = s->grid->sx;
  if (sx > gd->linedata[gd->hsize + py].cellsize)
  {
    sx = gd->linedata[gd->hsize + py].cellsize;
  }
  if (sx > tty->sx)
  {
    sx = tty->sx;
  }
  ux = 0;
  if ((((((wp == 0) || (py == 0)) || ((~gd->linedata[(gd->hsize + py) - 1].flags) & 0x1)) || (ox != 0)) || (tty->cx < tty->sx)) || (s->grid->sx < tty->sx))
  {
    if (((((s->grid->sx < tty->sx) && (ox == 0)) && (sx != s->grid->sx)) && tty_term_has(tty->term, TTYC_EL1)) && (!tty_fake_bce(tty, wp, 8)))
    {
      tty_default_attributes(tty, wp, 8);
      tty_cursor(tty, s->grid->sx - 1, oy + py);
      tty_putcode(tty, TTYC_EL1);
      cleared = 1;
    }
    if (sx != 0)
    {
      tty_cursor(tty, ox, oy + py);
    }
  }
  else
    log_debug("%s: wrapped line %u", __func__, oy + py);
  memcpy(&last, &grid_default_cell, sizeof(last));
  len = 0;
  width = 0;
  for (i = 0; i < sx; i += 1)
  {
    helper_tty_draw_line_1(&gcp_idx, &j, &ux, &width, &len, tty, wp, s, py, gd, gc, last, gcp, i, buf);
  }

  if (len != 0)
  {
    if (grid_cells_equal(&last, &grid_default_cell))
    {
      old_len = len;
      while ((len > 0) && (buf[len - 1] == ' '))
      {
        len -= 1;
        width -= 1;
      }

      log_debug("%s: trimmed %zu spaces", __func__, old_len - len);
    }
    if (len != 0)
    {
      tty_attributes(tty, &last, wp);
      tty_putn(tty, buf, len, width);
      ux += width;
    }
  }
  if ((!cleared) && (ux < s->grid->sx))
  {
    nx = s->grid->sx - ux;
    tty_default_attributes(tty, wp, 8);
    tty_clear_line(tty, wp, oy + py, ox + ux, nx, 8);
  }
  tty->flags = (tty->flags & (~0x1)) | flags;
  tty_update_mode(tty, tty->mode, s);
}


----------------------------
None
----------------------------
***/


static void tty_redraw_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  if (tty_large_region(tty, ctx))
  {
    wp->flags |= 0x1;
    return;
  }
  if ((ctx->ocy < ctx->orupper) || (ctx->ocy > ctx->orlower))
  {
    for (i = ctx->ocy; i < s->grid->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
  else
  {
    for (i = ctx->orupper; i <= ctx->orlower; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static int tty_large_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  return (ctx->orlower - ctx->orupper) >= (wp->screen->grid->sy / 2);
}


----------------------------
None
----------------------------
void tty_draw_pane(struct tty *tty, const struct window_pane *wp, u_int py, u_int ox, u_int oy)
{
  tty_draw_line(tty, wp, wp->screen, py, ox, oy);
}


----------------------------
None
----------------------------
***/


static void tty_margin_pane(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_margin(tty, ctx->xoff, (ctx->xoff + ctx->wp->sx) - 1);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_margin(struct tty *tty, u_int rleft, u_int rright)
{
  char s[64];
  if (!(tty->term_type == TTY_VT420))
  {
    return;
  }
  if ((tty->rleft == rleft) && (tty->rright == rright))
  {
    return;
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->rleft = rleft;
  tty->rright = rright;
  if ((rleft == 0) && (rright == (tty->sx - 1)))
  {
    snprintf(s, sizeof(s), "\033[s");
  }
  else
    snprintf(s, sizeof(s), "\033[%u;%us", rleft + 1, rright + 1);
  tty_puts(tty, s);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
None
----------------------------
***/


void tty_cmd_scrollup(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int i;
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) && (!(tty->term_type == TTY_VT420))) || tty_fake_bce(tty, wp, 8)) || (!tty_term_has(tty->term, TTYC_CSR)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_pane(tty, ctx);
  if ((ctx->num == 1) || (!tty_term_has(tty->term, TTYC_INDN)))
  {
    if (!(tty->term_type == TTY_VT420))
    {
      tty_cursor(tty, 0, tty->rlower);
    }
    else
      tty_cursor(tty, tty->rright, tty->rlower);
    for (i = 0; i < ctx->num; i += 1)
    {
      tty_putc(tty, '\n');
    }

  }
  else
  {
    tty_cursor(tty, 0, tty->cy);
    tty_putcode1(tty, TTYC_INDN, ctx->num);
  }
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_redraw_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  if (tty_large_region(tty, ctx))
  {
    wp->flags |= 0x1;
    return;
  }
  if ((ctx->ocy < ctx->orupper) || (ctx->ocy > ctx->orlower))
  {
    for (i = ctx->ocy; i < s->grid->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
  else
  {
    for (i = ctx->orupper; i <= ctx->orlower; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_margin_pane(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_margin(tty, ctx->xoff, (ctx->xoff + ctx->wp->sx) - 1);
}


----------------------------
None
----------------------------
***/


void tty_raw(struct tty *tty, const char *s)
{
  unsigned int s_idx = 0;
  ssize_t n;
  ssize_t slen;
  u_int i;
  slen = strlen(s);
  for (i = 0; i < 5; i += 1)
  {
    n = write(tty->fd, s, slen);
    if (n >= 0)
    {
      s_idx += n;
      slen -= n;
      if (slen == 0)
      {
        break;
      }
    }
    else
      if ((n == (-1)) && (errno != EAGAIN))
    {
      break;
    }
    usleep(100);
  }

}


/*** DEPENDENCIES:
None
----------------------------
***/


void tty_set_size(struct tty *tty, u_int sx, u_int sy)
{
  tty->sx = sx;
  tty->sy = sy;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void tty_stop_tty(struct tty *tty)
{
  struct winsize ws;
  if (!(tty->flags & 0x10))
  {
    return;
  }
  tty->flags &= ~0x10;
  event_del(&tty->timer);
  tty->flags &= ~0x80;
  event_del(&tty->event_in);
  event_del(&tty->event_out);
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) == (-1))
  {
    return;
  }
  if (tcsetattr(tty->fd, TCSANOW, &tty->tio) == (-1))
  {
    return;
  }
  tty_raw(tty, tty_term_string2(tty->term, TTYC_CSR, 0, ws.ws_row - 1));
  if (tty_acs_needed(tty))
  {
    tty_raw(tty, tty_term_string(tty->term, TTYC_RMACS));
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_SGR0));
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMKX));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CLEAR));
  if (tty_term_has(tty->term, TTYC_SS) && (tty->cstyle != 0))
  {
    if (tty_term_has(tty->term, TTYC_SE))
    {
      tty_raw(tty, tty_term_string(tty->term, TTYC_SE));
    }
    else
      tty_raw(tty, tty_term_string1(tty->term, TTYC_SS, 0));
  }
  if (tty->mode & 0x400)
  {
    tty_raw(tty, "\033[?2004l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_CR));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CNORM));
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_raw(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (tty->flags & 0x40)
    {
      tty->flags &= ~0x40;
      tty_raw(tty, "\033[?1004l");
    }
  }
  if (tty->term_type == TTY_VT420)
  {
    tty_raw(tty, "\033[?69l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMCUP));
  setblocking(tty->fd, 1);
}


/*** DEPENDENCIES:
void tty_raw(struct tty *tty, const char *s)
{
  unsigned int s_idx = 0;
  ssize_t n;
  ssize_t slen;
  u_int i;
  slen = strlen(s);
  for (i = 0; i < 5; i += 1)
  {
    n = write(tty->fd, s, slen);
    if (n >= 0)
    {
      s_idx += n;
      slen -= n;
      if (slen == 0)
      {
        break;
      }
    }
    else
      if ((n == (-1)) && (errno != EAGAIN))
    {
      break;
    }
    usleep(100);
  }

}


----------------------------
const char *tty_term_string2(struct tty_term *term, enum tty_code_code code, int a, int b)
{
  return tparm((char *) tty_term_string(term, code), a, b, 0, 0, 0, 0, 0, 0, 0);
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
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
const char *tty_term_string1(struct tty_term *term, enum tty_code_code code, int a)
{
  return tparm((char *) tty_term_string(term, code), a, 0, 0, 0, 0, 0, 0, 0, 0);
}


----------------------------
int tty_term_flag(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return 0;
  }
  if (term->codes[code].type != TTYCODE_FLAG)
  {
    fatalx("not a flag: %d", code);
  }
  return term->codes[code].value.flag;
}


----------------------------
const char *tty_term_string(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return "";
  }
  if (term->codes[code].type != TTYCODE_STRING)
  {
    fatalx("not a string: %d", code);
  }
  return term->codes[code].value.string;
}


----------------------------
void setblocking(int fd, int state)
{
  int mode;
  if ((mode = fcntl(fd, F_GETFL)) != (-1))
  {
    if (!state)
    {
      mode |= O_NONBLOCK;
    }
    else
      mode &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, mode);
  }
}


----------------------------
None
----------------------------
***/


void tty_close(struct tty *tty)
{
  if (event_initialized(&tty->key_timer))
  {
    evtimer_del(&tty->key_timer);
  }
  tty_stop_tty(tty);
  if (tty->flags & 0x20)
  {
    evbuffer_free(tty->in);
    event_del(&tty->event_in);
    evbuffer_free(tty->out);
    event_del(&tty->event_out);
    tty_term_free(tty->term);
    tty_keys_free(tty);
    tty->flags &= ~0x20;
  }
  if (tty->fd != (-1))
  {
    close(tty->fd);
    tty->fd = -1;
  }
}


/*** DEPENDENCIES:
void tty_stop_tty(struct tty *tty)
{
  struct winsize ws;
  if (!(tty->flags & 0x10))
  {
    return;
  }
  tty->flags &= ~0x10;
  event_del(&tty->timer);
  tty->flags &= ~0x80;
  event_del(&tty->event_in);
  event_del(&tty->event_out);
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) == (-1))
  {
    return;
  }
  if (tcsetattr(tty->fd, TCSANOW, &tty->tio) == (-1))
  {
    return;
  }
  tty_raw(tty, tty_term_string2(tty->term, TTYC_CSR, 0, ws.ws_row - 1));
  if (tty_acs_needed(tty))
  {
    tty_raw(tty, tty_term_string(tty->term, TTYC_RMACS));
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_SGR0));
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMKX));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CLEAR));
  if (tty_term_has(tty->term, TTYC_SS) && (tty->cstyle != 0))
  {
    if (tty_term_has(tty->term, TTYC_SE))
    {
      tty_raw(tty, tty_term_string(tty->term, TTYC_SE));
    }
    else
      tty_raw(tty, tty_term_string1(tty->term, TTYC_SS, 0));
  }
  if (tty->mode & 0x400)
  {
    tty_raw(tty, "\033[?2004l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_CR));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CNORM));
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_raw(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (tty->flags & 0x40)
    {
      tty->flags &= ~0x40;
      tty_raw(tty, "\033[?1004l");
    }
  }
  if (tty->term_type == TTY_VT420)
  {
    tty_raw(tty, "\033[?69l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMCUP));
  setblocking(tty->fd, 1);
}


----------------------------
void tty_term_free(struct tty_term *term)
{
  u_int i;
  if ((--term->references) != 0)
  {
    return;
  }
  do
  {
    if (term->entry.le_next != 0)
    {
      term->entry.le_next->entry.le_prev = term->entry.le_prev;
    }
    *term->entry.le_prev = term->entry.le_next;
    ;
    ;
  }
  while (0);
  for (i = 0; i < tty_term_ncodes(); i += 1)
  {
    if (term->codes[i].type == TTYCODE_STRING)
    {
      free(term->codes[i].value.string);
    }
  }

  free(term->codes);
  free(term->name);
  free(term);
}


----------------------------
void tty_keys_free(struct tty *tty)
{
  tty_keys_free1(tty->key_tree);
}


----------------------------
None
----------------------------
***/


void tty_free(struct tty *tty)
{
  tty_close(tty);
  free(tty->ccolour);
  free(tty->term_name);
}


/*** DEPENDENCIES:
void tty_close(struct tty *tty)
{
  if (event_initialized(&tty->key_timer))
  {
    evtimer_del(&tty->key_timer);
  }
  tty_stop_tty(tty);
  if (tty->flags & 0x20)
  {
    evbuffer_free(tty->in);
    event_del(&tty->event_in);
    evbuffer_free(tty->out);
    event_del(&tty->event_out);
    tty_term_free(tty->term);
    tty_keys_free(tty);
    tty->flags &= ~0x20;
  }
  if (tty->fd != (-1))
  {
    close(tty->fd);
    tty->fd = -1;
  }
}


----------------------------
None
----------------------------
***/


void tty_set_type(struct tty *tty, int type)
{
  tty->term_type = type;
  if (tty->term_type == TTY_VT420)
  {
    tty_puts(tty, "\033[?69h");
  }
}


/*** DEPENDENCIES:
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['tio_ref is a mutable refrence to ']
void helper_tty_start_tty_1(struct termios * const tio_ref, struct tty * const tty)
{
  struct termios tio = *tio_ref;
  setblocking(tty->fd, 0);
  event_add(&tty->event_in, 0);
  memcpy(&tio, &tty->tio, sizeof(tio));
  tio.c_iflag &= ~((((((IXON | IXOFF) | ICRNL) | INLCR) | IGNCR) | IMAXBEL) | ISTRIP);
  tio.c_iflag |= IGNBRK;
  tio.c_oflag &= ~(((OPOST | ONLCR) | OCRNL) | ONLRET);
  tio.c_lflag &= ~((((((((IEXTEN | ICANON) | ECHO) | ECHOE) | ECHONL) | ECHOCTL) | 0) | ECHOKE) | ISIG);
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;
  if (tcsetattr(tty->fd, TCSANOW, &tio) == 0)
  {
    tcflush(tty->fd, TCIOFLUSH);
  }
  *tio_ref = tio;
}


/*** DEPENDENCIES:
void setblocking(int fd, int state)
{
  int mode;
  if ((mode = fcntl(fd, F_GETFL)) != (-1))
  {
    if (!state)
    {
      mode |= O_NONBLOCK;
    }
    else
      mode &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, mode);
  }
}


----------------------------
None
----------------------------
***/


void tty_create_log(void)
{
  char name[64];
  xsnprintf(name, sizeof(name), "tmux-out-%ld.log", (long) getpid());
  tty_log_fd = open(name, (O_WRONLY | O_CREAT) | O_TRUNC, 0644);
  if ((tty_log_fd != (-1)) && (fcntl(tty_log_fd, F_SETFD, FD_CLOEXEC) == (-1)))
  {
    fatal("fcntl failed");
  }
}


/*** DEPENDENCIES:
static int tty_log_fd = -1
----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
***/


void tty_set_title(struct tty *tty, const char *title)
{
  if ((!tty_term_has(tty->term, TTYC_TSL)) || (!tty_term_has(tty->term, TTYC_FSL)))
  {
    return;
  }
  tty_putcode(tty, TTYC_TSL);
  tty_puts(tty, title);
  tty_putcode(tty, TTYC_FSL);
}


/*** DEPENDENCIES:
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
***/


static void tty_cell(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  if (((tty->term->flags & 0x2) && (tty->cy == (tty->sy - 1))) && (tty->cx == (tty->sx - 1)))
  {
    return;
  }
  if (gc->flags & 0x4)
  {
    return;
  }
  tty_attributes(tty, gc, wp);
  gcp_idx = tty_check_codeset(tty, gc);
  if (gcp->data.size == 1)
  {
    if (((*gcp->data.data) < 0x20) || ((*gcp->data.data) == 0x7f))
    {
      return;
    }
    tty_putc(tty, *gcp->data.data);
    return;
  }
  tty_putn(tty, gcp->data.data, gcp->data.size, gcp->data.width);
}


/*** DEPENDENCIES:
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
void tty_putn(struct tty *tty, const void *buf, size_t len, u_int width)
{
  tty_add(tty, buf, len);
  if ((tty->cx + width) > tty->sx)
  {
    tty->cx = (tty->cx + width) - tty->sx;
    if (tty->cx <= tty->sx)
    {
      tty->cy += 1;
    }
    else
      tty->cx = (tty->cy = 4294967295U);
  }
  else
    tty->cx += width;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
static const struct grid_cell *tty_check_codeset(struct tty *tty, const struct grid_cell *gc)
{
  static struct grid_cell new;
  u_int n;
  if ((gc->data.size == 1) && ((*gc->data.data) < 0x7f))
  {
    return gc;
  }
  if (tty->flags & 0x8)
  {
    return gc;
  }
  n = gc->data.width;
  if (n > 9)
  {
    n = 9;
  }
  memcpy(&new, gc, sizeof(new));
  new.data.size = n;
  memset(new.data.data, '_', n);
  return &new;
}


----------------------------
None
----------------------------
None
----------------------------
***/


void tty_cmd_cell(struct tty *tty, const struct tty_ctx *ctx)
{
  if (((ctx->xoff + ctx->ocx) > (tty->sx - 1)) && (ctx->ocy == ctx->orlower))
  {
    if ((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))
    {
      tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
    }
    else
      tty_margin_off(tty);
  }
  tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);
  tty_cell(tty, ctx->cell, ctx->wp);
}


/*** DEPENDENCIES:
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane_unless_wrap(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  if (((((((!ctx->wrapped) || (!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx)))) || (tty->term->flags & 0x2)) || ((ctx->xoff + cx) != 0)) || ((ctx->yoff + cy) != (tty->cy + 1))) || (tty->cx < tty->sx)) || (tty->cy == tty->rlower))
  {
    tty_cursor_pane(tty, ctx, cx, cy);
  }
  else
    log_debug("%s: will wrap at %u,%u", __func__, tty->cx, tty->cy);
}


----------------------------
static void tty_cell(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  if (((tty->term->flags & 0x2) && (tty->cy == (tty->sy - 1))) && (tty->cx == (tty->sx - 1)))
  {
    return;
  }
  if (gc->flags & 0x4)
  {
    return;
  }
  tty_attributes(tty, gc, wp);
  gcp_idx = tty_check_codeset(tty, gc);
  if (gcp->data.size == 1)
  {
    if (((*gcp->data.data) < 0x20) || ((*gcp->data.data) == 0x7f))
    {
      return;
    }
    tty_putc(tty, *gcp->data.data);
    return;
  }
  tty_putn(tty, gcp->data.data, gcp->data.size, gcp->data.width);
}


----------------------------
None
----------------------------
***/


static void tty_emulate_repeat(struct tty *tty, enum tty_code_code code, enum tty_code_code code1, u_int n)
{
  if (tty_term_has(tty->term, code))
  {
    tty_putcode1(tty, code, n);
  }
  else
  {
    while ((n--) > 0)
    {
      tty_putcode(tty, code1);
    }

  }
}


/*** DEPENDENCIES:
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
enum tty_code_code
{
  TTYC_AX = 0,
  TTYC_ACSC,
  TTYC_BCE,
  TTYC_BEL,
  TTYC_BLINK,
  TTYC_BOLD,
  TTYC_CIVIS,
  TTYC_CLEAR,
  TTYC_CNORM,
  TTYC_COLORS,
  TTYC_CR,
  TTYC_CS,
  TTYC_CSR,
  TTYC_CUB,
  TTYC_CUB1,
  TTYC_CUD,
  TTYC_CUD1,
  TTYC_CUF,
  TTYC_CUF1,
  TTYC_CUP,
  TTYC_CUU,
  TTYC_CUU1,
  TTYC_CVVIS,
  TTYC_DCH,
  TTYC_DCH1,
  TTYC_DIM,
  TTYC_DL,
  TTYC_DL1,
  TTYC_E3,
  TTYC_ECH,
  TTYC_ED,
  TTYC_EL,
  TTYC_EL1,
  TTYC_ENACS,
  TTYC_FSL,
  TTYC_HOME,
  TTYC_HPA,
  TTYC_ICH,
  TTYC_ICH1,
  TTYC_IL,
  TTYC_IL1,
  TTYC_INDN,
  TTYC_INVIS,
  TTYC_KCBT,
  TTYC_KCUB1,
  TTYC_KCUD1,
  TTYC_KCUF1,
  TTYC_KCUU1,
  TTYC_KDC2,
  TTYC_KDC3,
  TTYC_KDC4,
  TTYC_KDC5,
  TTYC_KDC6,
  TTYC_KDC7,
  TTYC_KDCH1,
  TTYC_KDN2,
  TTYC_KDN3,
  TTYC_KDN4,
  TTYC_KDN5,
  TTYC_KDN6,
  TTYC_KDN7,
  TTYC_KEND,
  TTYC_KEND2,
  TTYC_KEND3,
  TTYC_KEND4,
  TTYC_KEND5,
  TTYC_KEND6,
  TTYC_KEND7,
  TTYC_KF1,
  TTYC_KF10,
  TTYC_KF11,
  TTYC_KF12,
  TTYC_KF13,
  TTYC_KF14,
  TTYC_KF15,
  TTYC_KF16,
  TTYC_KF17,
  TTYC_KF18,
  TTYC_KF19,
  TTYC_KF2,
  TTYC_KF20,
  TTYC_KF21,
  TTYC_KF22,
  TTYC_KF23,
  TTYC_KF24,
  TTYC_KF25,
  TTYC_KF26,
  TTYC_KF27,
  TTYC_KF28,
  TTYC_KF29,
  TTYC_KF3,
  TTYC_KF30,
  TTYC_KF31,
  TTYC_KF32,
  TTYC_KF33,
  TTYC_KF34,
  TTYC_KF35,
  TTYC_KF36,
  TTYC_KF37,
  TTYC_KF38,
  TTYC_KF39,
  TTYC_KF4,
  TTYC_KF40,
  TTYC_KF41,
  TTYC_KF42,
  TTYC_KF43,
  TTYC_KF44,
  TTYC_KF45,
  TTYC_KF46,
  TTYC_KF47,
  TTYC_KF48,
  TTYC_KF49,
  TTYC_KF5,
  TTYC_KF50,
  TTYC_KF51,
  TTYC_KF52,
  TTYC_KF53,
  TTYC_KF54,
  TTYC_KF55,
  TTYC_KF56,
  TTYC_KF57,
  TTYC_KF58,
  TTYC_KF59,
  TTYC_KF6,
  TTYC_KF60,
  TTYC_KF61,
  TTYC_KF62,
  TTYC_KF63,
  TTYC_KF7,
  TTYC_KF8,
  TTYC_KF9,
  TTYC_KHOM2,
  TTYC_KHOM3,
  TTYC_KHOM4,
  TTYC_KHOM5,
  TTYC_KHOM6,
  TTYC_KHOM7,
  TTYC_KHOME,
  TTYC_KIC2,
  TTYC_KIC3,
  TTYC_KIC4,
  TTYC_KIC5,
  TTYC_KIC6,
  TTYC_KIC7,
  TTYC_KICH1,
  TTYC_KIND,
  TTYC_KLFT2,
  TTYC_KLFT3,
  TTYC_KLFT4,
  TTYC_KLFT5,
  TTYC_KLFT6,
  TTYC_KLFT7,
  TTYC_KMOUS,
  TTYC_KNP,
  TTYC_KNXT2,
  TTYC_KNXT3,
  TTYC_KNXT4,
  TTYC_KNXT5,
  TTYC_KNXT6,
  TTYC_KNXT7,
  TTYC_KPP,
  TTYC_KPRV2,
  TTYC_KPRV3,
  TTYC_KPRV4,
  TTYC_KPRV5,
  TTYC_KPRV6,
  TTYC_KPRV7,
  TTYC_KRI,
  TTYC_KRIT2,
  TTYC_KRIT3,
  TTYC_KRIT4,
  TTYC_KRIT5,
  TTYC_KRIT6,
  TTYC_KRIT7,
  TTYC_KUP2,
  TTYC_KUP3,
  TTYC_KUP4,
  TTYC_KUP5,
  TTYC_KUP6,
  TTYC_KUP7,
  TTYC_MS,
  TTYC_OP,
  TTYC_REV,
  TTYC_RGB,
  TTYC_RI,
  TTYC_RMACS,
  TTYC_RMCUP,
  TTYC_RMKX,
  TTYC_SE,
  TTYC_SETAB,
  TTYC_SETAF,
  TTYC_SETRGBB,
  TTYC_SETRGBF,
  TTYC_SGR0,
  TTYC_SITM,
  TTYC_SMACS,
  TTYC_SMCUP,
  TTYC_SMKX,
  TTYC_SMSO,
  TTYC_SMUL,
  TTYC_SMXX,
  TTYC_SS,
  TTYC_TC,
  TTYC_TSL,
  TTYC_U8,
  TTYC_VPA,
  TTYC_XENL,
  TTYC_XT
}
----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
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


void tty_cmd_insertcharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, ctx->bg)) || ((!tty_term_has(tty->term, TTYC_ICH)) && (!tty_term_has(tty->term, TTYC_ICH1))))
  {
    tty_draw_pane(tty, wp, ctx->ocy, ctx->xoff, ctx->yoff);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_ICH, TTYC_ICH1, ctx->num);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_emulate_repeat(struct tty *tty, enum tty_code_code code, enum tty_code_code code1, u_int n)
{
  if (tty_term_has(tty->term, code))
  {
    tty_putcode1(tty, code, n);
  }
  else
  {
    while ((n--) > 0)
    {
      tty_putcode(tty, code1);
    }

  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
void tty_draw_pane(struct tty *tty, const struct window_pane *wp, u_int py, u_int ox, u_int oy)
{
  tty_draw_line(tty, wp, wp->screen, py, ox, oy);
}


----------------------------
None
----------------------------
***/


void tty_cmd_clearline(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int nx;
  u_int py = ctx->yoff + ctx->ocy;
  tty_default_attributes(tty, wp, ctx->bg);
  nx = wp->screen->grid->sx;
  tty_clear_line(tty, wp, py, ctx->xoff, nx, ctx->bg);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
None
----------------------------
***/


static void tty_invalidate(struct tty *tty)
{
  memcpy(&tty->cell, &grid_default_cell, sizeof(tty->cell));
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
  tty->cx = (tty->cy = 4294967295U);
  tty->rupper = (tty->rleft = 4294967295U);
  tty->rlower = (tty->rright = 4294967295U);
  if (tty->flags & 0x10)
  {
    tty_putcode(tty, TTYC_SGR0);
    tty->mode = 0xffffff;
    tty_update_mode(tty, 0x1, 0);
    tty_cursor(tty, 0, 0);
    tty_region_off(tty);
    tty_margin_off(tty);
  }
  else
    tty->mode = 0x1;
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
void tty_update_mode(struct tty *tty, int mode, struct screen *s)
{
  int changed;
  if ((s != 0) && (strcmp(s->ccolour, tty->ccolour) != 0))
  {
    tty_force_cursor_colour(tty, s->ccolour);
  }
  if (tty->flags & 0x1)
  {
    mode &= ~0x1;
  }
  changed = mode ^ tty->mode;
  if (changed & 0x80)
  {
    if (tty_term_has(tty->term, TTYC_CVVIS))
    {
      tty_putcode(tty, TTYC_CVVIS);
    }
    else
      tty_putcode(tty, TTYC_CNORM);
    changed |= 0x1;
  }
  if (changed & 0x1)
  {
    if (mode & 0x1)
    {
      tty_putcode(tty, TTYC_CNORM);
    }
    else
      tty_putcode(tty, TTYC_CIVIS);
  }
  if ((s != 0) && (tty->cstyle != s->cstyle))
  {
    if (tty_term_has(tty->term, TTYC_SS))
    {
      if ((s->cstyle == 0) && tty_term_has(tty->term, TTYC_SE))
      {
        tty_putcode(tty, TTYC_SE);
      }
      else
        tty_putcode1(tty, TTYC_SS, s->cstyle);
    }
    tty->cstyle = s->cstyle;
  }
  if (changed & ((0x20 | 0x40) | 0x1000))
  {
    helper_tty_update_mode_1(tty, mode);
  }
  if (changed & 0x400)
  {
    if (mode & 0x400)
    {
      tty_puts(tty, "\033[?2004h");
    }
    else
      tty_puts(tty, "\033[?2004l");
  }
  tty->mode = mode;
}


----------------------------
void tty_region_off(struct tty *tty)
{
  tty_region(tty, 0, tty->sy - 1);
}


----------------------------
None
----------------------------
***/


void tty_start_tty(struct tty *tty)
{
  struct client *c = tty->client;
  struct termios tio;
  if ((tty->fd != (-1)) && (tcgetattr(tty->fd, &tty->tio) == 0))
  {
    helper_tty_start_tty_1(&tio, tty);
  }
  tty_putcode(tty, TTYC_SMCUP);
  tty_putcode(tty, TTYC_SMKX);
  tty_putcode(tty, TTYC_CLEAR);
  if (tty_acs_needed(tty))
  {
    log_debug("%s: using capabilities for ACS", c->name);
    tty_putcode(tty, TTYC_ENACS);
  }
  else
    log_debug("%s: using UTF-8 for ACS", c->name);
  tty_putcode(tty, TTYC_CNORM);
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_puts(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (options_get_number(global_options, "focus-events"))
    {
      tty->flags |= 0x40;
      tty_puts(tty, "\033[?1004h");
    }
    tty_puts(tty, "\033[c");
  }
  tty->flags |= 0x10;
  tty_invalidate(tty);
  tty_force_cursor_colour(tty, "");
  tty->mouse_drag_flag = 0;
  tty->mouse_drag_update = 0;
  tty->mouse_drag_release = 0;
}


/*** DEPENDENCIES:
static void tty_force_cursor_colour(struct tty *tty, const char *ccolour)
{
  if ((*ccolour) == '\0')
  {
    tty_putcode(tty, TTYC_CR);
  }
  else
    tty_putcode_ptr1(tty, TTYC_CS, ccolour);
  free(tty->ccolour);
  tty->ccolour = xstrdup(ccolour);
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
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
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
int tty_term_flag(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return 0;
  }
  if (term->codes[code].type != TTYCODE_FLAG)
  {
    fatalx("not a flag: %d", code);
  }
  return term->codes[code].value.flag;
}


----------------------------
long long options_get_number(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  return o->number;
}


----------------------------
static void tty_invalidate(struct tty *tty)
{
  memcpy(&tty->cell, &grid_default_cell, sizeof(tty->cell));
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
  tty->cx = (tty->cy = 4294967295U);
  tty->rupper = (tty->rleft = 4294967295U);
  tty->rlower = (tty->rright = 4294967295U);
  if (tty->flags & 0x10)
  {
    tty_putcode(tty, TTYC_SGR0);
    tty->mode = 0xffffff;
    tty_update_mode(tty, 0x1, 0);
    tty_cursor(tty, 0, 0);
    tty_region_off(tty);
    tty_margin_off(tty);
  }
  else
    tty->mode = 0x1;
}


----------------------------
void helper_tty_start_tty_1(struct termios * const tio_ref, struct tty * const tty)
{
  struct termios tio = *tio_ref;
  setblocking(tty->fd, 0);
  event_add(&tty->event_in, 0);
  memcpy(&tio, &tty->tio, sizeof(tio));
  tio.c_iflag &= ~((((((IXON | IXOFF) | ICRNL) | INLCR) | IGNCR) | IMAXBEL) | ISTRIP);
  tio.c_iflag |= IGNBRK;
  tio.c_oflag &= ~(((OPOST | ONLCR) | OCRNL) | ONLRET);
  tio.c_lflag &= ~((((((((IEXTEN | ICANON) | ECHO) | ECHOE) | ECHONL) | ECHOCTL) | 0) | ECHOKE) | ISIG);
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;
  if (tcsetattr(tty->fd, TCSANOW, &tio) == 0)
  {
    tcflush(tty->fd, TCIOFLUSH);
  }
  *tio_ref = tio;
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


void tty_resize(struct tty *tty)
{
  struct client *c = tty->client;
  struct winsize ws;
  u_int sx;
  u_int sy;
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) != (-1))
  {
    sx = ws.ws_col;
    if (sx == 0)
    {
      sx = 80;
    }
    sy = ws.ws_row;
    if (sy == 0)
    {
      sy = 24;
    }
  }
  else
  {
    sx = 80;
    sy = 24;
  }
  log_debug("%s: %s now %ux%u", __func__, c->name, sx, sy);
  tty_set_size(tty, sx, sy);
  tty_invalidate(tty);
}


/*** DEPENDENCIES:
void tty_set_size(struct tty *tty, u_int sx, u_int sy)
{
  tty->sx = sx;
  tty->sy = sy;
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static void tty_invalidate(struct tty *tty)
{
  memcpy(&tty->cell, &grid_default_cell, sizeof(tty->cell));
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
  tty->cx = (tty->cy = 4294967295U);
  tty->rupper = (tty->rleft = 4294967295U);
  tty->rlower = (tty->rright = 4294967295U);
  if (tty->flags & 0x10)
  {
    tty_putcode(tty, TTYC_SGR0);
    tty->mode = 0xffffff;
    tty_update_mode(tty, 0x1, 0);
    tty_cursor(tty, 0, 0);
    tty_region_off(tty);
    tty_margin_off(tty);
  }
  else
    tty->mode = 0x1;
}


----------------------------
None
----------------------------
***/


int tty_init(struct tty *tty, struct client *c, int fd, char *term)
{
  if (!isatty(fd))
  {
    return -1;
  }
  memset(tty, 0, sizeof(*tty));
  if ((term == 0) || ((*term) == '\0'))
  {
    tty->term_name = xstrdup("unknown");
  }
  else
    tty->term_name = xstrdup(term);
  tty->fd = fd;
  tty->client = c;
  tty->cstyle = 0;
  tty->ccolour = xstrdup("");
  tty->flags = 0;
  tty->term_flags = 0;
  tty->term_type = TTY_UNKNOWN;
  return 0;
}


/*** DEPENDENCIES:
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
None
----------------------------
***/


void tty_cmd_rawstring(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_add(tty, ctx->ptr, ctx->num);
  tty_invalidate(tty);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_add(struct tty *tty, const char *buf, size_t len)
{
  struct client *c = tty->client;
  if (tty->flags & 0x80)
  {
    tty->discarded += len;
    return;
  }
  evbuffer_add(tty->out, buf, len);
  log_debug("%s: %.*s", c->name, (int) len, buf);
  c->written += len;
  if (tty_log_fd != (-1))
  {
    write(tty_log_fd, buf, len);
  }
  if (tty->flags & 0x10)
  {
    event_add(&tty->event_out, 0);
  }
}


----------------------------
static void tty_invalidate(struct tty *tty)
{
  memcpy(&tty->cell, &grid_default_cell, sizeof(tty->cell));
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
  tty->cx = (tty->cy = 4294967295U);
  tty->rupper = (tty->rleft = 4294967295U);
  tty->rlower = (tty->rright = 4294967295U);
  if (tty->flags & 0x10)
  {
    tty_putcode(tty, TTYC_SGR0);
    tty->mode = 0xffffff;
    tty_update_mode(tty, 0x1, 0);
    tty_cursor(tty, 0, 0);
    tty_region_off(tty);
    tty_margin_off(tty);
  }
  else
    tty->mode = 0x1;
}


----------------------------
None
----------------------------
***/


static void tty_read_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  struct client *c = tty->client;
  size_t size = EVBUFFER_LENGTH(tty->in);
  int nread;
  nread = evbuffer_read(tty->in, tty->fd, -1);
  if ((nread == 0) || (nread == (-1)))
  {
    event_del(&tty->event_in);
    server_client_lost(tty->client);
    return;
  }
  log_debug("%s: read %d bytes (already %zu)", c->name, nread, size);
  while (tty_keys_next(tty))
  {
    ;
  }

}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


static void tty_timer_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  struct client *c = tty->client;
  struct timeval tv = {.tv_usec = 100000};
  log_debug("%s: %zu discarded", c->name, tty->discarded);
  c->flags |= 0x8;
  c->discarded += tty->discarded;
  if (tty->discarded < (1 + ((tty->sx * tty->sy) / 8)))
  {
    tty->flags &= ~0x80;
    tty_invalidate(tty);
    return;
  }
  tty->discarded = 0;
  evtimer_add(&tty->timer, &tv);
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static void tty_invalidate(struct tty *tty)
{
  memcpy(&tty->cell, &grid_default_cell, sizeof(tty->cell));
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
  tty->cx = (tty->cy = 4294967295U);
  tty->rupper = (tty->rleft = 4294967295U);
  tty->rlower = (tty->rright = 4294967295U);
  if (tty->flags & 0x10)
  {
    tty_putcode(tty, TTYC_SGR0);
    tty->mode = 0xffffff;
    tty_update_mode(tty, 0x1, 0);
    tty_cursor(tty, 0, 0);
    tty_region_off(tty);
    tty_margin_off(tty);
  }
  else
    tty->mode = 0x1;
}


----------------------------
None
----------------------------
***/


static int tty_block_maybe(struct tty *tty)
{
  struct client *c = tty->client;
  size_t size = EVBUFFER_LENGTH(tty->out);
  struct timeval tv = {.tv_usec = 100000};
  if (size < (1 + ((tty->sx * tty->sy) * 8)))
  {
    return 0;
  }
  if (tty->flags & 0x80)
  {
    return 1;
  }
  tty->flags |= 0x80;
  log_debug("%s: can't keep up, %zu discarded", c->name, size);
  evbuffer_drain(tty->out, size);
  c->discarded += size;
  tty->discarded = 0;
  evtimer_add(&tty->timer, &tv);
  return 1;
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


static void tty_write_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  struct client *c = tty->client;
  size_t size = EVBUFFER_LENGTH(tty->out);
  int nwrite;
  nwrite = evbuffer_write(tty->out, tty->fd);
  if (nwrite == (-1))
  {
    return;
  }
  log_debug("%s: wrote %d bytes (of %zu)", c->name, nwrite, size);
  if (c->redraw > 0)
  {
    if (((size_t) nwrite) >= c->redraw)
    {
      c->redraw = 0;
    }
    else
      c->redraw -= nwrite;
    log_debug("%s: waiting for redraw, %zu bytes left", c->name, c->redraw);
  }
  else
    if (tty_block_maybe(tty))
  {
    return;
  }
  if (EVBUFFER_LENGTH(tty->out) != 0)
  {
    event_add(&tty->event_out, 0);
  }
}


/*** DEPENDENCIES:
static int tty_block_maybe(struct tty *tty)
{
  struct client *c = tty->client;
  size_t size = EVBUFFER_LENGTH(tty->out);
  struct timeval tv = {.tv_usec = 100000};
  if (size < (1 + ((tty->sx * tty->sy) * 8)))
  {
    return 0;
  }
  if (tty->flags & 0x80)
  {
    return 1;
  }
  tty->flags |= 0x80;
  log_debug("%s: can't keep up, %zu discarded", c->name, size);
  evbuffer_drain(tty->out, size);
  c->discarded += size;
  tty->discarded = 0;
  evtimer_add(&tty->timer, &tv);
  return 1;
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


int tty_open(struct tty *tty, char **cause)
{
  tty->term = tty_term_find(tty->term_name, tty->fd, cause);
  if (tty->term == 0)
  {
    tty_close(tty);
    return -1;
  }
  tty->flags |= 0x20;
  tty->flags &= ~(((0x1 | 0x2) | 0x80) | 0x4);
  event_set(&tty->event_in, tty->fd, EV_PERSIST | EV_READ, tty_read_callback, tty);
  tty->in = evbuffer_new();
  event_set(&tty->event_out, tty->fd, EV_WRITE, tty_write_callback, tty);
  tty->out = evbuffer_new();
  evtimer_set(&tty->timer, tty_timer_callback, tty);
  tty_start_tty(tty);
  tty_keys_build(tty);
  return 0;
}


/*** DEPENDENCIES:
static void tty_read_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  struct client *c = tty->client;
  size_t size = EVBUFFER_LENGTH(tty->in);
  int nread;
  nread = evbuffer_read(tty->in, tty->fd, -1);
  if ((nread == 0) || (nread == (-1)))
  {
    event_del(&tty->event_in);
    server_client_lost(tty->client);
    return;
  }
  log_debug("%s: read %d bytes (already %zu)", c->name, nread, size);
  while (tty_keys_next(tty))
  {
    ;
  }

}


----------------------------
static void tty_timer_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  struct client *c = tty->client;
  struct timeval tv = {.tv_usec = 100000};
  log_debug("%s: %zu discarded", c->name, tty->discarded);
  c->flags |= 0x8;
  c->discarded += tty->discarded;
  if (tty->discarded < (1 + ((tty->sx * tty->sy) / 8)))
  {
    tty->flags &= ~0x80;
    tty_invalidate(tty);
    return;
  }
  tty->discarded = 0;
  evtimer_add(&tty->timer, &tv);
}


----------------------------
struct tty_term *tty_term_find(char *name, int fd, char **cause)
{
  struct tty_term *term;
  unsigned int term_idx = 0;
  const struct tty_term_code_entry *ent;
  unsigned int ent_idx = 0;
  struct tty_code *code;
  unsigned int code_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  u_int size;
  u_int i;
  int n;
  int error;
  const char *s;
  unsigned int s_idx = 0;
  const char *acs;
  unsigned int acs_idx = 0;
  for (term_idx = (&tty_terms)->lh_first; (&term[term_idx]) != 0; term_idx = term_idx->entry.le_next)
  {
    if (strcmp(term->name, name) == 0)
    {
      term->references += 1;
      return term;
    }
  }

  log_debug("new term: %s", name);
  term_idx = xmalloc(sizeof(*term_idx));
  term->name = xstrdup(name);
  term->references = 1;
  term->flags = 0;
  term->codes = xcalloc(tty_term_ncodes(), sizeof(*term->codes));
  do
  {
    if ((term->entry.le_next = (&tty_terms)->lh_first) != 0)
    {
      (&tty_terms)->lh_first->entry.le_prev = &term->entry.le_next;
    }
    (&tty_terms)->lh_first = &term[term_idx];
    term->entry.le_prev = &(&tty_terms)->lh_first;
  }
  while (0);
  if (setupterm(name, fd, &error) != OK)
  {
    switch (error)
    {
      case 1:
      {
        xasprintf(cause, "can't use hardcopy terminal: %s", name);
        break;
      }

      case 0:
      {
        xasprintf(cause, "missing or unsuitable terminal: %s", name);
        break;
      }

      case -1:
      {
        xasprintf(cause, "can't find terminfo database");
        break;
      }

      default:
      {
        xasprintf(cause, "unknown error");
        break;
      }

    }

    goto error;
  }
  for (i = 0; i < tty_term_ncodes(); i += 1)
  {
    helper_tty_term_find_1(&ent_idx, &code_idx, &n, &s_idx, term, ent, code, i, s);
  }

  o_idx = options_get_only(global_options, "terminal-overrides");
  if (options_array_size(o, &size) != (-1))
  {
    for (i = 0; i < size; i += 1)
    {
      s_idx = options_array_get(o, i);
      if ((&s[s_idx]) != 0)
      {
        tty_term_override(term, s);
      }
    }

  }
  del_curterm(cur_term);
  if (!tty_term_has(term, TTYC_CLEAR))
  {
    xasprintf(cause, "terminal does not support clear");
    goto error;
  }
  if (!tty_term_has(term, TTYC_CUP))
  {
    xasprintf(cause, "terminal does not support cup");
    goto error;
  }
  if ((!tty_term_has(term, TTYC_CUD1)) && (!tty_term_has(term, TTYC_CUD)))
  {
    xasprintf(cause, "terminal does not support cud1 or cud");
    goto error;
  }
  if (tty_term_number(term, TTYC_COLORS) == 256)
  {
    term->flags |= 0x1;
  }
  if (!tty_term_flag(term, TTYC_XENL))
  {
    term->flags |= 0x2;
  }
  memset(term->acs, 0, sizeof(term->acs));
  if (tty_term_has(term, TTYC_ACSC))
  {
    acs_idx = tty_term_string(term, TTYC_ACSC);
  }
  else
    acs_idx = "a#j+k+l+m+n+o-p-q-r-s-t+u+v+w+x|y<z>~.";
  for (; (acs[0 + acs_idx] != '\0') && (acs[1 + acs_idx] != '\0'); acs_idx += 2)
  {
    term->acs[(u_char) acs[0 + acs_idx]][0] = acs[1 + acs_idx];
  }

  if ((tty_term_flag(term, TTYC_XT) && (!tty_term_has(term, TTYC_TSL))) && (!tty_term_has(term, TTYC_FSL)))
  {
    code_idx = &term->codes[TTYC_TSL];
    code->value.string = xstrdup("\033]0;");
    code->type = TTYCODE_STRING;
    code_idx = &term->codes[TTYC_FSL];
    code->value.string = xstrdup("\007");
    code->type = TTYCODE_STRING;
  }
  if (((tty_term_flag(term, TTYC_TC) || tty_term_flag(term, TTYC_RGB)) && (!tty_term_has(term, TTYC_SETRGBF))) && (!tty_term_has(term, TTYC_SETRGBB)))
  {
    code_idx = &term->codes[TTYC_SETRGBF];
    code->value.string = xstrdup("\033[38;2;%p1%d;%p2%d;%p3%dm");
    code->type = TTYCODE_STRING;
    code_idx = &term->codes[TTYC_SETRGBB];
    code->value.string = xstrdup("\033[48;2;%p1%d;%p2%d;%p3%dm");
    code->type = TTYCODE_STRING;
  }
  for (i = 0; i < tty_term_ncodes(); i += 1)
  {
    log_debug("%s%s", name, tty_term_describe(term, i));
  }

  return term;
  error:
  tty_term_free(term);

  return 0;
}


----------------------------
void tty_close(struct tty *tty)
{
  if (event_initialized(&tty->key_timer))
  {
    evtimer_del(&tty->key_timer);
  }
  tty_stop_tty(tty);
  if (tty->flags & 0x20)
  {
    evbuffer_free(tty->in);
    event_del(&tty->event_in);
    evbuffer_free(tty->out);
    event_del(&tty->event_out);
    tty_term_free(tty->term);
    tty_keys_free(tty);
    tty->flags &= ~0x20;
  }
  if (tty->fd != (-1))
  {
    close(tty->fd);
    tty->fd = -1;
  }
}


----------------------------
void tty_keys_build(struct tty *tty)
{
  const struct tty_default_key_raw *tdkr;
  unsigned int tdkr_idx = 0;
  const struct tty_default_key_code *tdkc;
  unsigned int tdkc_idx = 0;
  u_int i;
  u_int size;
  const char *s;
  unsigned int s_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  if (tty->key_tree != 0)
  {
    tty_keys_free(tty);
  }
  tty->key_tree = 0;
  for (i = 0; i < ((sizeof(tty_default_raw_keys)) / (sizeof(tty_default_raw_keys[0]))); i += 1)
  {
    tdkr_idx = &tty_default_raw_keys[i];
    s_idx = tdkr->string;
    if (s[s_idx] != '\0')
    {
      tty_keys_add(tty, s, tdkr->key);
    }
  }

  for (i = 0; i < ((sizeof(tty_default_code_keys)) / (sizeof(tty_default_code_keys[0]))); i += 1)
  {
    tdkc_idx = &tty_default_code_keys[i];
    s_idx = tty_term_string(tty->term, tdkc->code);
    if (s[s_idx] != '\0')
    {
      tty_keys_add(tty, s, tdkc->key);
    }
  }

  o_idx = options_get(global_options, "user-keys");
  if (((&o[o_idx]) != 0) && (options_array_size(o, &size) != (-1)))
  {
    for (i = 0; i < size; i += 1)
    {
      value_idx = options_array_get(o, i);
      if ((&value[value_idx]) != 0)
      {
        tty_keys_add(tty, value, 0x000020000000ULL + i);
      }
    }

  }
}


----------------------------
static void tty_write_callback(int fd, short events, void *data)
{
  struct tty *tty = data;
  struct client *c = tty->client;
  size_t size = EVBUFFER_LENGTH(tty->out);
  int nwrite;
  nwrite = evbuffer_write(tty->out, tty->fd);
  if (nwrite == (-1))
  {
    return;
  }
  log_debug("%s: wrote %d bytes (of %zu)", c->name, nwrite, size);
  if (c->redraw > 0)
  {
    if (((size_t) nwrite) >= c->redraw)
    {
      c->redraw = 0;
    }
    else
      c->redraw -= nwrite;
    log_debug("%s: waiting for redraw, %zu bytes left", c->name, c->redraw);
  }
  else
    if (tty_block_maybe(tty))
  {
    return;
  }
  if (EVBUFFER_LENGTH(tty->out) != 0)
  {
    event_add(&tty->event_out, 0);
  }
}


----------------------------
void tty_start_tty(struct tty *tty)
{
  struct client *c = tty->client;
  struct termios tio;
  if ((tty->fd != (-1)) && (tcgetattr(tty->fd, &tty->tio) == 0))
  {
    helper_tty_start_tty_1(&tio, tty);
  }
  tty_putcode(tty, TTYC_SMCUP);
  tty_putcode(tty, TTYC_SMKX);
  tty_putcode(tty, TTYC_CLEAR);
  if (tty_acs_needed(tty))
  {
    log_debug("%s: using capabilities for ACS", c->name);
    tty_putcode(tty, TTYC_ENACS);
  }
  else
    log_debug("%s: using UTF-8 for ACS", c->name);
  tty_putcode(tty, TTYC_CNORM);
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_puts(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (options_get_number(global_options, "focus-events"))
    {
      tty->flags |= 0x40;
      tty_puts(tty, "\033[?1004h");
    }
    tty_puts(tty, "\033[c");
  }
  tty->flags |= 0x10;
  tty_invalidate(tty);
  tty_force_cursor_colour(tty, "");
  tty->mouse_drag_flag = 0;
  tty->mouse_drag_update = 0;
  tty->mouse_drag_release = 0;
}


----------------------------
None
----------------------------
***/


static void tty_clear_area(struct tty *tty, const struct window_pane *wp, u_int py, u_int ny, u_int px, u_int nx, u_int bg)
{
  u_int yy;
  char tmp[64];
  log_debug("%s: %u,%u at %u,%u", __func__, nx, ny, px, py);
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if ((((px == 0) && ((px + nx) >= tty->sx)) && ((py + ny) >= tty->sy)) && tty_term_has(tty->term, TTYC_ED))
    {
      tty_cursor(tty, 0, py);
      tty_putcode(tty, TTYC_ED);
      return;
    }
    if ((tty->term_type == TTY_VT420) && (bg != 8))
    {
      xsnprintf(tmp, sizeof(tmp), "\033[32;%u;%u;%u;%u$x", py + 1, px + 1, py + ny, px + nx);
      tty_puts(tty, tmp);
      return;
    }
    if (((((px == 0) && ((px + nx) >= tty->sx)) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin_off(tty);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
    if (((((nx > 2) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && (tty->term_type == TTY_VT420)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin(tty, px, (px + nx) - 1);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    tty_clear_line(tty, wp, yy, px, nx, bg);
  }

}


/*** DEPENDENCIES:
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
static void tty_margin(struct tty *tty, u_int rleft, u_int rright)
{
  char s[64];
  if (!(tty->term_type == TTY_VT420))
  {
    return;
  }
  if ((tty->rleft == rleft) && (tty->rright == rright))
  {
    return;
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->rleft = rleft;
  tty->rright = rright;
  if ((rleft == 0) && (rright == (tty->sx - 1)))
  {
    snprintf(s, sizeof(s), "\033[s");
  }
  else
    snprintf(s, sizeof(s), "\033[%u;%us", rleft + 1, rright + 1);
  tty_puts(tty, s);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
static void tty_region(struct tty *tty, u_int rupper, u_int rlower)
{
  if ((tty->rlower == rlower) && (tty->rupper == rupper))
  {
    return;
  }
  if (!tty_term_has(tty->term, TTYC_CSR))
  {
    return;
  }
  tty->rupper = rupper;
  tty->rlower = rlower;
  if (tty->cx >= tty->sx)
  {
    tty_cursor(tty, 0, tty->cy);
  }
  tty_putcode2(tty, TTYC_CSR, tty->rupper, tty->rlower);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


void tty_cmd_clearscreen(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int px;
  u_int py;
  u_int nx;
  u_int ny;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, 0, wp->screen->grid->sy - 1);
  tty_margin_off(tty);
  px = ctx->xoff;
  nx = wp->screen->grid->sx;
  py = ctx->yoff;
  ny = wp->screen->grid->sy;
  tty_clear_area(tty, wp, py, ny, px, nx, ctx->bg);
}


/*** DEPENDENCIES:
static void tty_clear_area(struct tty *tty, const struct window_pane *wp, u_int py, u_int ny, u_int px, u_int nx, u_int bg)
{
  u_int yy;
  char tmp[64];
  log_debug("%s: %u,%u at %u,%u", __func__, nx, ny, px, py);
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if ((((px == 0) && ((px + nx) >= tty->sx)) && ((py + ny) >= tty->sy)) && tty_term_has(tty->term, TTYC_ED))
    {
      tty_cursor(tty, 0, py);
      tty_putcode(tty, TTYC_ED);
      return;
    }
    if ((tty->term_type == TTY_VT420) && (bg != 8))
    {
      xsnprintf(tmp, sizeof(tmp), "\033[32;%u;%u;%u;%u$x", py + 1, px + 1, py + ny, px + nx);
      tty_puts(tty, tmp);
      return;
    }
    if (((((px == 0) && ((px + nx) >= tty->sx)) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin_off(tty);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
    if (((((nx > 2) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && (tty->term_type == TTY_VT420)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin(tty, px, (px + nx) - 1);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    tty_clear_line(tty, wp, yy, px, nx, bg);
  }

}


----------------------------
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
None
----------------------------
***/


void tty_cmd_clearendofline(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int nx;
  u_int py = ctx->yoff + ctx->ocy;
  tty_default_attributes(tty, wp, ctx->bg);
  nx = wp->screen->grid->sx - ctx->ocx;
  tty_clear_line(tty, wp, py, ctx->xoff + ctx->ocx, nx, ctx->bg);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
None
----------------------------
***/


void tty_cmd_clearstartofline(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int py = ctx->yoff + ctx->ocy;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_clear_line(tty, wp, py, ctx->xoff, ctx->ocx + 1, ctx->bg);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
None
----------------------------
***/


void tty_cmd_clearcharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_default_attributes(tty, ctx->wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  if (tty_term_has(tty->term, TTYC_ECH) && (!tty_fake_bce(tty, ctx->wp, 8)))
  {
    tty_putcode1(tty, TTYC_ECH, ctx->num);
  }
  else
    tty_repeat_space(tty, ctx->num);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
void tty_putcode1(struct tty *tty, enum tty_code_code code, int a)
{
  if (a < 0)
  {
    return;
  }
  tty_puts(tty, tty_term_string1(tty->term, code, a));
}


----------------------------
static void tty_repeat_space(struct tty *tty, u_int n)
{
  static char s[500];
  if ((*s) != ' ')
  {
    memset(s, ' ', sizeof(s));
  }
  while (n > (sizeof(s)))
  {
    tty_putn(tty, s, sizeof(s), sizeof(s));
    n -= sizeof(s);
  }

  if (n != 0)
  {
    tty_putn(tty, s, n, n);
  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
None
----------------------------
***/


void tty_cmd_clearstartofscreen(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int px;
  u_int py;
  u_int nx;
  u_int ny;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, 0, wp->screen->grid->sy - 1);
  tty_margin_off(tty);
  px = ctx->xoff;
  nx = wp->screen->grid->sx;
  py = ctx->yoff;
  ny = ctx->ocy - 1;
  tty_clear_area(tty, wp, py, ny, px, nx, ctx->bg);
  px = ctx->xoff;
  nx = ctx->ocx + 1;
  py = ctx->yoff + ctx->ocy;
  tty_clear_line(tty, wp, py, px, nx, ctx->bg);
}


/*** DEPENDENCIES:
static void tty_clear_area(struct tty *tty, const struct window_pane *wp, u_int py, u_int ny, u_int px, u_int nx, u_int bg)
{
  u_int yy;
  char tmp[64];
  log_debug("%s: %u,%u at %u,%u", __func__, nx, ny, px, py);
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if ((((px == 0) && ((px + nx) >= tty->sx)) && ((py + ny) >= tty->sy)) && tty_term_has(tty->term, TTYC_ED))
    {
      tty_cursor(tty, 0, py);
      tty_putcode(tty, TTYC_ED);
      return;
    }
    if ((tty->term_type == TTY_VT420) && (bg != 8))
    {
      xsnprintf(tmp, sizeof(tmp), "\033[32;%u;%u;%u;%u$x", py + 1, px + 1, py + ny, px + nx);
      tty_puts(tty, tmp);
      return;
    }
    if (((((px == 0) && ((px + nx) >= tty->sx)) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin_off(tty);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
    if (((((nx > 2) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && (tty->term_type == TTY_VT420)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin(tty, px, (px + nx) - 1);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    tty_clear_line(tty, wp, yy, px, nx, bg);
  }

}


----------------------------
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
None
----------------------------
***/


void tty_cmd_clearendofscreen(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int px;
  u_int py;
  u_int nx;
  u_int ny;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, 0, wp->screen->grid->sy - 1);
  tty_margin_off(tty);
  px = ctx->xoff;
  nx = wp->screen->grid->sx;
  py = (ctx->yoff + ctx->ocy) + 1;
  ny = (wp->screen->grid->sy - ctx->ocy) - 1;
  tty_clear_area(tty, wp, py, ny, px, nx, ctx->bg);
  px = ctx->xoff + ctx->ocx;
  nx = wp->screen->grid->sx - ctx->ocx;
  py = ctx->yoff + ctx->ocy;
  tty_clear_line(tty, wp, py, px, nx, ctx->bg);
}


/*** DEPENDENCIES:
static void tty_clear_area(struct tty *tty, const struct window_pane *wp, u_int py, u_int ny, u_int px, u_int nx, u_int bg)
{
  u_int yy;
  char tmp[64];
  log_debug("%s: %u,%u at %u,%u", __func__, nx, ny, px, py);
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if ((((px == 0) && ((px + nx) >= tty->sx)) && ((py + ny) >= tty->sy)) && tty_term_has(tty->term, TTYC_ED))
    {
      tty_cursor(tty, 0, py);
      tty_putcode(tty, TTYC_ED);
      return;
    }
    if ((tty->term_type == TTY_VT420) && (bg != 8))
    {
      xsnprintf(tmp, sizeof(tmp), "\033[32;%u;%u;%u;%u$x", py + 1, px + 1, py + ny, px + nx);
      tty_puts(tty, tmp);
      return;
    }
    if (((((px == 0) && ((px + nx) >= tty->sx)) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin_off(tty);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
    if (((((nx > 2) && (ny > 2)) && tty_term_has(tty->term, TTYC_CSR)) && (tty->term_type == TTY_VT420)) && tty_term_has(tty->term, TTYC_INDN))
    {
      tty_region(tty, py, (py + ny) - 1);
      tty_margin(tty, px, (px + nx) - 1);
      tty_putcode1(tty, TTYC_INDN, ny);
      return;
    }
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    tty_clear_line(tty, wp, yy, px, nx, bg);
  }

}


----------------------------
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_clear_line(struct tty *tty, const struct window_pane *wp, u_int py, u_int px, u_int nx, u_int bg)
{
  log_debug("%s: %u at %u,%u", __func__, nx, px, py);
  if (nx == 0)
  {
    return;
  }
  if (!tty_fake_bce(tty, wp, bg))
  {
    if (((px + nx) >= tty->sx) && tty_term_has(tty->term, TTYC_EL))
    {
      tty_cursor(tty, px, py);
      tty_putcode(tty, TTYC_EL);
      return;
    }
    if ((px == 0) && tty_term_has(tty->term, TTYC_EL1))
    {
      tty_cursor(tty, (px + nx) - 1, py);
      tty_putcode(tty, TTYC_EL1);
      return;
    }
    if (tty_term_has(tty->term, TTYC_ECH))
    {
      tty_cursor(tty, px, py);
      tty_putcode1(tty, TTYC_ECH, nx);
      return;
    }
  }
  tty_cursor(tty, px, py);
  tty_repeat_space(tty, nx);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
None
----------------------------
***/


void tty_cmd_deletecharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, ctx->bg)) || ((!tty_term_has(tty->term, TTYC_DCH)) && (!tty_term_has(tty->term, TTYC_DCH1))))
  {
    tty_draw_pane(tty, wp, ctx->ocy, ctx->xoff, ctx->yoff);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_DCH, TTYC_DCH1, ctx->num);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_emulate_repeat(struct tty *tty, enum tty_code_code code, enum tty_code_code code1, u_int n)
{
  if (tty_term_has(tty->term, code))
  {
    tty_putcode1(tty, code, n);
  }
  else
  {
    while ((n--) > 0)
    {
      tty_putcode(tty, code1);
    }

  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
void tty_draw_pane(struct tty *tty, const struct window_pane *wp, u_int py, u_int ox, u_int oy)
{
  tty_draw_line(tty, wp, wp->screen, py, ox, oy);
}


----------------------------
None
----------------------------
***/


void tty_cmd_reverseindex(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (ctx->ocy != ctx->orupper)
  {
    return;
  }
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, 8)) || (!tty_term_has(tty->term, TTYC_CSR))) || (!tty_term_has(tty->term, TTYC_RI)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_off(tty);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->orupper);
  tty_putcode(tty, TTYC_RI);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_redraw_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  if (tty_large_region(tty, ctx))
  {
    wp->flags |= 0x1;
    return;
  }
  if ((ctx->ocy < ctx->orupper) || (ctx->ocy > ctx->orlower))
  {
    for (i = ctx->ocy; i < s->grid->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
  else
  {
    for (i = ctx->orupper; i <= ctx->orlower; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
None
----------------------------
***/


void tty_cmd_deleteline(struct tty *tty, const struct tty_ctx *ctx)
{
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, ctx->wp, ctx->bg)) || (!tty_term_has(tty->term, TTYC_CSR))) || (!tty_term_has(tty->term, TTYC_DL1)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, ctx->wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_off(tty);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_DL, TTYC_DL1, ctx->num);
  tty->cx = (tty->cy = 4294967295U);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_redraw_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  if (tty_large_region(tty, ctx))
  {
    wp->flags |= 0x1;
    return;
  }
  if ((ctx->ocy < ctx->orupper) || (ctx->ocy > ctx->orlower))
  {
    for (i = ctx->ocy; i < s->grid->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
  else
  {
    for (i = ctx->orupper; i <= ctx->orlower; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
}


----------------------------
static void tty_emulate_repeat(struct tty *tty, enum tty_code_code code, enum tty_code_code code1, u_int n)
{
  if (tty_term_has(tty->term, code))
  {
    tty_putcode1(tty, code, n);
  }
  else
  {
    while ((n--) > 0)
    {
      tty_putcode(tty, code1);
    }

  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
None
----------------------------
***/


void tty_cmd_insertline(struct tty *tty, const struct tty_ctx *ctx)
{
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, ctx->wp, ctx->bg)) || (!tty_term_has(tty->term, TTYC_CSR))) || (!tty_term_has(tty->term, TTYC_IL1)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, ctx->wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_off(tty);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_IL, TTYC_IL1, ctx->num);
  tty->cx = (tty->cy = 4294967295U);
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_redraw_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  if (tty_large_region(tty, ctx))
  {
    wp->flags |= 0x1;
    return;
  }
  if ((ctx->ocy < ctx->orupper) || (ctx->ocy > ctx->orlower))
  {
    for (i = ctx->ocy; i < s->grid->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
  else
  {
    for (i = ctx->orupper; i <= ctx->orlower; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
}


----------------------------
static void tty_emulate_repeat(struct tty *tty, enum tty_code_code code, enum tty_code_code code1, u_int n)
{
  if (tty_term_has(tty->term, code))
  {
    tty_putcode1(tty, code, n);
  }
  else
  {
    while ((n--) > 0)
    {
      tty_putcode(tty, code1);
    }

  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
None
----------------------------
***/


void tty_cmd_alignmenttest(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  u_int j;
  tty_attributes(tty, &grid_default_cell, wp);
  tty_region_pane(tty, ctx, 0, s->grid->sy - 1);
  tty_margin_off(tty);
  for (j = 0; j < s->grid->sy; j += 1)
  {
    tty_cursor_pane(tty, ctx, 0, j);
    for (i = 0; i < s->grid->sx; i += 1)
    {
      tty_putc(tty, 'E');
    }

  }

}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
void tty_margin_off(struct tty *tty)
{
  tty_margin(tty, 0, tty->sx - 1);
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
None
----------------------------
None
----------------------------
***/


void tty_cmd_linefeed(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (ctx->ocy != ctx->orlower)
  {
    return;
  }
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) && (!(tty->term_type == TTY_VT420))) || tty_fake_bce(tty, wp, 8)) || (!tty_term_has(tty->term, TTYC_CSR)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_pane(tty, ctx);
  if ((ctx->xoff + ctx->ocx) > tty->rright)
  {
    if (!(tty->term_type == TTY_VT420))
    {
      tty_cursor(tty, 0, ctx->yoff + ctx->ocy);
    }
    else
      tty_cursor(tty, tty->rright, ctx->yoff + ctx->ocy);
  }
  else
    tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_putc(tty, '\n');
}


/*** DEPENDENCIES:
static void tty_default_attributes(struct tty *tty, const struct window_pane *wp, u_int bg)
{
  static struct grid_cell gc;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.bg = bg;
  tty_attributes(tty, &gc, wp);
}


----------------------------
static void tty_region_pane(struct tty *tty, const struct tty_ctx *ctx, u_int rupper, u_int rlower)
{
  tty_region(tty, ctx->yoff + rupper, ctx->yoff + rlower);
}


----------------------------
static int tty_fake_bce(const struct tty *tty, const struct window_pane *wp, u_int bg)
{
  struct grid_cell gc;
  if (tty_term_flag(tty->term, TTYC_BCE))
  {
    return 0;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (wp != 0)
  {
    tty_default_colours(&gc, wp);
  }
  if ((bg != 8) || (gc.bg != 8))
  {
    return 1;
  }
  return 0;
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
int tty_term_has(struct tty_term *term, enum tty_code_code code)
{
  return term->codes[code].type != TTYCODE_NONE;
}


----------------------------
static void tty_redraw_region(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  if (tty_large_region(tty, ctx))
  {
    wp->flags |= 0x1;
    return;
  }
  if ((ctx->ocy < ctx->orupper) || (ctx->ocy > ctx->orlower))
  {
    for (i = ctx->ocy; i < s->grid->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
  else
  {
    for (i = ctx->orupper; i <= ctx->orlower; i += 1)
    {
      tty_draw_pane(tty, wp, i, ctx->xoff, ctx->yoff);
    }

  }
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void tty_cursor_pane(struct tty *tty, const struct tty_ctx *ctx, u_int cx, u_int cy)
{
  tty_cursor(tty, ctx->xoff + cx, ctx->yoff + cy);
}


----------------------------
static void tty_margin_pane(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_margin(tty, ctx->xoff, (ctx->xoff + ctx->wp->sx) - 1);
}


----------------------------
None
----------------------------
***/


