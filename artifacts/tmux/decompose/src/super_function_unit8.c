// element in merge of:  alerts_reset,alerts_timer,alerts_queue
static void alerts_reset(struct window *w)
{
  struct timeval tv;
  if (!event_initialized(&w->alerts_timer))
  {
    evtimer_set(&w->alerts_timer, alerts_timer, w);
  }
  w->flags &= ~0x8;
  event_del(&w->alerts_timer);
  timerclear(&tv);
  tv.tv_sec = options_get_number(w->options, "monitor-silence");
  log_debug("@%u alerts timer reset %u", w->id, (u_int) tv.tv_sec);
  if (tv.tv_sec != 0)
  {
    event_add(&w->alerts_timer, &tv);
  }
}


/*** DEPENDENCIES:
None
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


// element in merge of:  alerts_reset,alerts_timer,alerts_queue
static void alerts_timer(int fd, short events, void *arg)
{
  struct window *w = arg;
  log_debug("@%u alerts timer expired", w->id);
  alerts_queue(w, 0x8);
}


/*** DEPENDENCIES:
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


// element in merge of:  alerts_reset,alerts_timer,alerts_queue
void alerts_queue(struct window *w, int flags)
{
  alerts_reset(w);
  if ((w->flags & flags) != flags)
  {
    w->flags |= flags;
    log_debug("@%u alerts flags added %#x", w->id, flags);
  }
  if (alerts_enabled(w, flags))
  {
    if (!w->alerts_queued)
    {
      w->alerts_queued = 1;
      do
      {
        w->alerts_entry.tqe_next = 0;
        w->alerts_entry.tqe_prev = (&alerts_list)->tqh_last;
        *(&alerts_list)->tqh_last = w;
        (&alerts_list)->tqh_last = &w->alerts_entry.tqe_next;
      }
      while (0);
      window_add_ref(w, __func__);
    }
    if (!alerts_fired)
    {
      log_debug("alerts check queued (by @%u)", w->id);
      event_once(-1, EV_TIMEOUT, alerts_callback, 0, 0);
      alerts_fired = 1;
    }
  }
}


/*** DEPENDENCIES:
static struct 
{
  struct window *tqh_first;
  struct window **tqh_last;
} alerts_list = {0, &alerts_list.tqh_first}
----------------------------
static void alerts_callback(int fd, short events, void *arg)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window *w1;
  unsigned int w1_idx = 0;
  int alerts;
  for (w_idx = (&alerts_list)->tqh_first; ((&w[w_idx]) != 0) && ((w1_idx = w->alerts_entry.tqe_next, 1)); w_idx = &w1[w1_idx])
  {
    alerts = alerts_check_all(w);
    log_debug("@%u alerts check, alerts %#x", w->id, alerts);
    w->alerts_queued = 0;
    do
    {
      if (w->alerts_entry.tqe_next != 0)
      {
        w->alerts_entry.tqe_next->alerts_entry.tqe_prev = w->alerts_entry.tqe_prev;
      }
      else
        (&alerts_list)->tqh_last = w->alerts_entry.tqe_prev;
      *w->alerts_entry.tqe_prev = w->alerts_entry.tqe_next;
      ;
      ;
    }
    while (0);
    w->flags &= ~((0x1 | 0x2) | 0x8);
    window_remove_ref(w, __func__);
  }

  alerts_fired = 0;
}


----------------------------
None
----------------------------
static int alerts_enabled(struct window *w, int flags)
{
  if (flags & 0x1)
  {
    if (options_get_number(w->options, "monitor-bell"))
    {
      return 1;
    }
  }
  if (flags & 0x2)
  {
    if (options_get_number(w->options, "monitor-activity"))
    {
      return 1;
    }
  }
  if (flags & 0x8)
  {
    if (options_get_number(w->options, "monitor-silence") != 0)
    {
      return 1;
    }
  }
  return 0;
}


----------------------------
void window_add_ref(struct window *w, const char *from)
{
  w->references += 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
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
static int alerts_fired
----------------------------
None
----------------------------
***/


