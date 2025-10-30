static unsigned syncsearch(unsigned *have, const unsigned char *buf, unsigned len)
{
  unsigned got;
  unsigned next;
  got = *have;
  next = 0;
  while ((next < len) && (got < 4))
  {
    if (((int) buf[next]) == ((got < 2) ? (0) : (0xff)))
    {
      got += 1;
    }
    else
      if (buf[next])
    {
      got = 0;
    }
    else
      got = 4 - got;
    next += 1;
  }

  *have = got;
  return next;
}


/*** DEPENDENCIES:
***/


// hint:  ['next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_3(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->extra)
  {
    do
    {
      while (bits < ((unsigned) state->extra))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    state->offset += ((unsigned) hold) & ((1U << state->extra) - 1);
    do
    {
      hold >>= state->extra;
      bits -= (unsigned) state->extra;
    }
    while (0);
    state->back += state->extra;
  }
  ;
  state->mode = MATCH;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['next_idx_ref is a mutable refrence to unsigned int', 'put_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'left_ref is a mutable refrence to unsigned', 'copy_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_4(unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned * const copy_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned copy = *copy_ref;
  copy = state->length;
  if (copy)
  {
    if (copy > have)
    {
      copy = have;
    }
    if (copy > left)
    {
      copy = left;
    }
    if (copy == 0)
    {
      goto inf_leave;
    }
    memcpy(put, next, copy);
    have -= copy;
    next_idx += copy;
    left -= copy;
    put_idx += copy;
    state->length -= copy;
    break;
  }
  ;
  state->mode = TYPE;
  break;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *copy_ref = copy;
}


/*** DEPENDENCIES:
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_5(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->extra)
  {
    do
    {
      while (bits < ((unsigned) state->extra))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    state->length += ((unsigned) hold) & ((1U << state->extra) - 1);
    do
    {
      hold >>= state->extra;
      bits -= (unsigned) state->extra;
    }
    while (0);
    state->back += state->extra;
  }
  ;
  state->was = state->length;
  state->mode = DIST;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_helper_inflate_1_8_1(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next, static const unsigned short order[19])
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    while (bits < ((unsigned) 3))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  state->lens[order[state->have++]] = (unsigned short) (((unsigned) hold) & ((1U << 3) - 1));
  do
  {
    hold >>= 3;
    bits -= (unsigned) 3;
  }
  while (0);
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['len_ref is a mutable refrence to unsigned']
void helper_inflateSync_1(unsigned * const len_ref, unsigned char buf[4], struct inflate_state * const state)
{
  unsigned len = *len_ref;
  state->mode = SYNC;
  state->hold <<= state->bits & 7;
  state->bits -= state->bits & 7;
  len = 0;
  while (state->bits >= 8)
  {
    buf[len] = (unsigned char) state->hold;
    len += 1;
    state->hold >>= 8;
    state->bits -= 8;
  }

  state->have = 0;
  syncsearch(&state->have, buf, len);
  *len_ref = len;
}


/*** DEPENDENCIES:
static unsigned syncsearch(unsigned *have, const unsigned char *buf, unsigned len)
{
  unsigned got;
  unsigned next;
  got = *have;
  next = 0;
  while ((next < len) && (got < 4))
  {
    if (((int) buf[next]) == ((got < 2) ? (0) : (0xff)))
    {
      got += 1;
    }
    else
      if (buf[next])
    {
      got = 0;
    }
    else
      got = 4 - got;
    next += 1;
  }

  *have = got;
  return next;
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'last_ref is a mutable refrence to code']
void helper_helper_helper_inflate_1_12_1(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  last = here;
  for (;;)
  {
    here = state->distcode[last.val + ((((unsigned) hold) & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
    if (((unsigned) (last.bits + here.bits)) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  do
  {
    hold >>= last.bits;
    bits -= (unsigned) last.bits;
  }
  while (0);
  state->back += last.bits;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


/*** DEPENDENCIES:
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'last_ref is a mutable refrence to code']
void helper_helper_helper_inflate_1_14_1(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  last = here;
  for (;;)
  {
    here = state->lencode[last.val + ((((unsigned) hold) & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
    if (((unsigned) (last.bits + here.bits)) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  do
  {
    hold >>= last.bits;
    bits -= (unsigned) last.bits;
  }
  while (0);
  state->back += last.bits;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


/*** DEPENDENCIES:
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


int inflateEnd(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->window != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state->window);
  }
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  ;
  return 0;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflateResetKeep(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  strm->total_in = (strm->total_out = (state->total = 0));
  strm->msg = 0;
  if (state->wrap)
  {
    strm->adler = state->wrap & 1;
  }
  state->mode = HEAD;
  state->last = 0;
  state->havedict = 0;
  state->flags = -1;
  state->dmax = 32768U;
  state->head = 0;
  state->hold = 0;
  state->bits = 0;
  state->lencode = (state->distcode = (state->next = state->codes));
  state->sane = 1;
  state->back = -1;
  ;
  return 0;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflateReset(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  state->wsize = 0;
  state->whave = 0;
  state->wnext = 0;
  return inflateResetKeep(strm);
}


/*** DEPENDENCIES:
int inflateResetKeep(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  strm->total_in = (strm->total_out = (state->total = 0));
  strm->msg = 0;
  if (state->wrap)
  {
    strm->adler = state->wrap & 1;
  }
  state->mode = HEAD;
  state->last = 0;
  state->havedict = 0;
  state->flags = -1;
  state->dmax = 32768U;
  state->head = 0;
  state->hold = 0;
  state->bits = 0;
  state->lencode = (state->distcode = (state->next = state->codes));
  state->sane = 1;
  state->back = -1;
  ;
  return 0;
}


----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


int inflateReset2(z_streamp strm, int windowBits)
{
  int wrap;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (windowBits < 0)
  {
    if (windowBits < (-15))
    {
      return -2;
    }
    wrap = 0;
    windowBits = -windowBits;
  }
  else
  {
    wrap = (windowBits >> 4) + 5;
  }
  if (windowBits && ((windowBits < 8) || (windowBits > 15)))
  {
    return -2;
  }
  if ((state->window != 0) && (state->wbits != ((unsigned) windowBits)))
  {
    (*strm->zfree)(strm->opaque, (voidpf) state->window);
    state->window = 0;
  }
  state->wrap = wrap;
  state->wbits = (unsigned) windowBits;
  return inflateReset(strm);
}


/*** DEPENDENCIES:
int inflateReset(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  state->wsize = 0;
  state->whave = 0;
  state->wnext = 0;
  return inflateResetKeep(strm);
}


----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size)
{
  int ret;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((version == 0) || (version[0] != "1.3-optipng"[0])) || (stream_size != ((int) (sizeof(z_stream)))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  state_idx = (struct inflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(struct inflate_state));
  if ((&state[state_idx]) == 0)
  {
    return -4;
  }
  ;
  strm->state = (struct internal_state *) state;
  state->strm = strm;
  state->window = 0;
  state->mode = HEAD;
  ret = inflateReset2(strm, windowBits);
  if (ret != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state);
    strm->state = 0;
  }
  return ret;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
int inflateReset2(z_streamp strm, int windowBits)
{
  int wrap;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (windowBits < 0)
  {
    if (windowBits < (-15))
    {
      return -2;
    }
    wrap = 0;
    windowBits = -windowBits;
  }
  else
  {
    wrap = (windowBits >> 4) + 5;
  }
  if (windowBits && ((windowBits < 8) || (windowBits > 15)))
  {
    return -2;
  }
  if ((state->window != 0) && (state->wbits != ((unsigned) windowBits)))
  {
    (*strm->zfree)(strm->opaque, (voidpf) state->window);
    state->window = 0;
  }
  state->wrap = wrap;
  state->wbits = (unsigned) windowBits;
  return inflateReset(strm);
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
void zcfree(voidpf opaque, voidpf ptr)
{
  (void) opaque;
  free(ptr);
}


----------------------------
voidpf zcalloc(voidpf opaque, unsigned items, unsigned size)
{
  (void) opaque;
  return ((sizeof(uInt)) > 2) ? ((voidpf) malloc(items * size)) : ((voidpf) calloc(items, size));
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_13(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, int flush, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->last)
  {
    do
    {
      hold >>= bits & 7;
      bits -= bits & 7;
    }
    while (0);
    state->mode = CHECK;
    break;
  }
  do
  {
    while (bits < ((unsigned) 3))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  state->last = ((unsigned) hold) & ((1U << 1) - 1);
  do
  {
    hold >>= 1;
    bits -= (unsigned) 1;
  }
  while (0);
  switch (((unsigned) hold) & ((1U << 2) - 1))
  {
    case 0:
    {
      ;
      state->mode = STORED;
      break;
    }

    case 1:
    {
      fixedtables(state);
      ;
      state->mode = LEN_;
      if (flush == 6)
      {
        do
        {
          hold >>= 2;
          bits -= (unsigned) 2;
        }
        while (0);
        goto inf_leave;
      }
      break;
    }

    case 2:
    {
      ;
      state->mode = TABLE;
      break;
    }

    case 3:
    {
      strm->msg = (char *) "invalid block type";
      state->mode = BAD;
    }

  }

  do
  {
    hold >>= 2;
    bits -= (unsigned) 2;
  }
  while (0);
  break;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static void fixedtables(struct inflate_state *state)
{
  static const code lenfix[512] = {{96, 7, 0}, {0, 8, 80}, {0, 8, 16}, {20, 8, 115}, {18, 7, 31}, {0, 8, 112}, {0, 8, 48}, {0, 9, 192}, {16, 7, 10}, {0, 8, 96}, {0, 8, 32}, {0, 9, 160}, {0, 8, 0}, {0, 8, 128}, {0, 8, 64}, {0, 9, 224}, {16, 7, 6}, {0, 8, 88}, {0, 8, 24}, {0, 9, 144}, {19, 7, 59}, {0, 8, 120}, {0, 8, 56}, {0, 9, 208}, {17, 7, 17}, {0, 8, 104}, {0, 8, 40}, {0, 9, 176}, {0, 8, 8}, {0, 8, 136}, {0, 8, 72}, {0, 9, 240}, {16, 7, 4}, {0, 8, 84}, {0, 8, 20}, {21, 8, 227}, {19, 7, 43}, {0, 8, 116}, {0, 8, 52}, {0, 9, 200}, {17, 7, 13}, {0, 8, 100}, {0, 8, 36}, {0, 9, 168}, {0, 8, 4}, {0, 8, 132}, {0, 8, 68}, {0, 9, 232}, {16, 7, 8}, {0, 8, 92}, {0, 8, 28}, {0, 9, 152}, {20, 7, 83}, {0, 8, 124}, {0, 8, 60}, {0, 9, 216}, {18, 7, 23}, {0, 8, 108}, {0, 8, 44}, {0, 9, 184}, {0, 8, 12}, {0, 8, 140}, {0, 8, 76}, {0, 9, 248}, {16, 7, 3}, {0, 8, 82}, {0, 8, 18}, {21, 8, 163}, {19, 7, 35}, {0, 8, 114}, {0, 8, 50}, {0, 9, 196}, {17, 7, 11}, {0, 8, 98}, {0, 8, 34}, {0, 9, 164}, {0, 8, 2}, {0, 8, 130}, {0, 8, 66}, {0, 9, 228}, {16, 7, 7}, {0, 8, 90}, {0, 8, 26}, {0, 9, 148}, {20, 7, 67}, {0, 8, 122}, {0, 8, 58}, {0, 9, 212}, {18, 7, 19}, {0, 8, 106}, {0, 8, 42}, {0, 9, 180}, {0, 8, 10}, {0, 8, 138}, {0, 8, 74}, {0, 9, 244}, {16, 7, 5}, {0, 8, 86}, {0, 8, 22}, {64, 8, 0}, {19, 7, 51}, {0, 8, 118}, {0, 8, 54}, {0, 9, 204}, {17, 7, 15}, {0, 8, 102}, {0, 8, 38}, {0, 9, 172}, {0, 8, 6}, {0, 8, 134}, {0, 8, 70}, {0, 9, 236}, {16, 7, 9}, {0, 8, 94}, {0, 8, 30}, {0, 9, 156}, {20, 7, 99}, {0, 8, 126}, {0, 8, 62}, {0, 9, 220}, {18, 7, 27}, {0, 8, 110}, {0, 8, 46}, {0, 9, 188}, {0, 8, 14}, {0, 8, 142}, {0, 8, 78}, {0, 9, 252}, {96, 7, 0}, {0, 8, 81}, {0, 8, 17}, {21, 8, 131}, {18, 7, 31}, {0, 8, 113}, {0, 8, 49}, {0, 9, 194}, {16, 7, 10}, {0, 8, 97}, {0, 8, 33}, {0, 9, 162}, {0, 8, 1}, {0, 8, 129}, {0, 8, 65}, {0, 9, 226}, {16, 7, 6}, {0, 8, 89}, {0, 8, 25}, {0, 9, 146}, {19, 7, 59}, {0, 8, 121}, {0, 8, 57}, {0, 9, 210}, {17, 7, 17}, {0, 8, 105}, {0, 8, 41}, {0, 9, 178}, {0, 8, 9}, {0, 8, 137}, {0, 8, 73}, {0, 9, 242}, {16, 7, 4}, {0, 8, 85}, {0, 8, 21}, {16, 8, 258}, {19, 7, 43}, {0, 8, 117}, {0, 8, 53}, {0, 9, 202}, {17, 7, 13}, {0, 8, 101}, {0, 8, 37}, {0, 9, 170}, {0, 8, 5}, {0, 8, 133}, {0, 8, 69}, {0, 9, 234}, {16, 7, 8}, {0, 8, 93}, {0, 8, 29}, {0, 9, 154}, {20, 7, 83}, {0, 8, 125}, {0, 8, 61}, {0, 9, 218}, {18, 7, 23}, {0, 8, 109}, {0, 8, 45}, {0, 9, 186}, {0, 8, 13}, {0, 8, 141}, {0, 8, 77}, {0, 9, 250}, {16, 7, 3}, {0, 8, 83}, {0, 8, 19}, {21, 8, 195}, {19, 7, 35}, {0, 8, 115}, {0, 8, 51}, {0, 9, 198}, {17, 7, 11}, {0, 8, 99}, {0, 8, 35}, {0, 9, 166}, {0, 8, 3}, {0, 8, 131}, {0, 8, 67}, {0, 9, 230}, {16, 7, 7}, {0, 8, 91}, {0, 8, 27}, {0, 9, 150}, {20, 7, 67}, {0, 8, 123}, {0, 8, 59}, {0, 9, 214}, {18, 7, 19}, {0, 8, 107}, {0, 8, 43}, {0, 9, 182}, {0, 8, 11}, {0, 8, 139}, {0, 8, 75}, {0, 9, 246}, {16, 7, 5}, {0, 8, 87}, {0, 8, 23}, {64, 8, 0}, {19, 7, 51}, {0, 8, 119}, {0, 8, 55}, {0, 9, 206}, {17, 7, 15}, {0, 8, 103}, {0, 8, 39}, {0, 9, 174}, {0, 8, 7}, {0, 8, 135}, {0, 8, 71}, {0, 9, 238}, {16, 7, 9}, {0, 8, 95}, {0, 8, 31}, {0, 9, 158}, {20, 7, 99}, {0, 8, 127}, {0, 8, 63}, {0, 9, 222}, {18, 7, 27}, {0, 8, 111}, {0, 8, 47}, {0, 9, 190}, {0, 8, 15}, {0, 8, 143}, {0, 8, 79}, {0, 9, 254}, {96, 7, 0}, {0, 8, 80}, {0, 8, 16}, {20, 8, 115}, {18, 7, 31}, {0, 8, 112}, {0, 8, 48}, {0, 9, 193}, {16, 7, 10}, {0, 8, 96}, {0, 8, 32}, {0, 9, 161}, {0, 8, 0}, {0, 8, 128}, {0, 8, 64}, {0, 9, 225}, {16, 7, 6}, {0, 8, 88}, {0, 8, 24}, {0, 9, 145}, {19, 7, 59}, {0, 8, 120}, {0, 8, 56}, {0, 9, 209}, {17, 7, 17}, {0, 8, 104}, {0, 8, 40}, {0, 9, 177}, {0, 8, 8}, {0, 8, 136}, {0, 8, 72}, {0, 9, 241}, {16, 7, 4}, {0, 8, 84}, {0, 8, 20}, {21, 8, 227}, {19, 7, 43}, {0, 8, 116}, {0, 8, 52}, {0, 9, 201}, {17, 7, 13}, {0, 8, 100}, {0, 8, 36}, {0, 9, 169}, {0, 8, 4}, {0, 8, 132}, {0, 8, 68}, {0, 9, 233}, {16, 7, 8}, {0, 8, 92}, {0, 8, 28}, {0, 9, 153}, {20, 7, 83}, {0, 8, 124}, {0, 8, 60}, {0, 9, 217}, {18, 7, 23}, {0, 8, 108}, {0, 8, 44}, {0, 9, 185}, {0, 8, 12}, {0, 8, 140}, {0, 8, 76}, {0, 9, 249}, {16, 7, 3}, {0, 8, 82}, {0, 8, 18}, {21, 8, 163}, {19, 7, 35}, {0, 8, 114}, {0, 8, 50}, {0, 9, 197}, {17, 7, 11}, {0, 8, 98}, {0, 8, 34}, {0, 9, 165}, {0, 8, 2}, {0, 8, 130}, {0, 8, 66}, {0, 9, 229}, {16, 7, 7}, {0, 8, 90}, {0, 8, 26}, {0, 9, 149}, {20, 7, 67}, {0, 8, 122}, {0, 8, 58}, {0, 9, 213}, {18, 7, 19}, {0, 8, 106}, {0, 8, 42}, {0, 9, 181}, {0, 8, 10}, {0, 8, 138}, {0, 8, 74}, {0, 9, 245}, {16, 7, 5}, {0, 8, 86}, {0, 8, 22}, {64, 8, 0}, {19, 7, 51}, {0, 8, 118}, {0, 8, 54}, {0, 9, 205}, {17, 7, 15}, {0, 8, 102}, {0, 8, 38}, {0, 9, 173}, {0, 8, 6}, {0, 8, 134}, {0, 8, 70}, {0, 9, 237}, {16, 7, 9}, {0, 8, 94}, {0, 8, 30}, {0, 9, 157}, {20, 7, 99}, {0, 8, 126}, {0, 8, 62}, {0, 9, 221}, {18, 7, 27}, {0, 8, 110}, {0, 8, 46}, {0, 9, 189}, {0, 8, 14}, {0, 8, 142}, {0, 8, 78}, {0, 9, 253}, {96, 7, 0}, {0, 8, 81}, {0, 8, 17}, {21, 8, 131}, {18, 7, 31}, {0, 8, 113}, {0, 8, 49}, {0, 9, 195}, {16, 7, 10}, {0, 8, 97}, {0, 8, 33}, {0, 9, 163}, {0, 8, 1}, {0, 8, 129}, {0, 8, 65}, {0, 9, 227}, {16, 7, 6}, {0, 8, 89}, {0, 8, 25}, {0, 9, 147}, {19, 7, 59}, {0, 8, 121}, {0, 8, 57}, {0, 9, 211}, {17, 7, 17}, {0, 8, 105}, {0, 8, 41}, {0, 9, 179}, {0, 8, 9}, {0, 8, 137}, {0, 8, 73}, {0, 9, 243}, {16, 7, 4}, {0, 8, 85}, {0, 8, 21}, {16, 8, 258}, {19, 7, 43}, {0, 8, 117}, {0, 8, 53}, {0, 9, 203}, {17, 7, 13}, {0, 8, 101}, {0, 8, 37}, {0, 9, 171}, {0, 8, 5}, {0, 8, 133}, {0, 8, 69}, {0, 9, 235}, {16, 7, 8}, {0, 8, 93}, {0, 8, 29}, {0, 9, 155}, {20, 7, 83}, {0, 8, 125}, {0, 8, 61}, {0, 9, 219}, {18, 7, 23}, {0, 8, 109}, {0, 8, 45}, {0, 9, 187}, {0, 8, 13}, {0, 8, 141}, {0, 8, 77}, {0, 9, 251}, {16, 7, 3}, {0, 8, 83}, {0, 8, 19}, {21, 8, 195}, {19, 7, 35}, {0, 8, 115}, {0, 8, 51}, {0, 9, 199}, {17, 7, 11}, {0, 8, 99}, {0, 8, 35}, {0, 9, 167}, {0, 8, 3}, {0, 8, 131}, {0, 8, 67}, {0, 9, 231}, {16, 7, 7}, {0, 8, 91}, {0, 8, 27}, {0, 9, 151}, {20, 7, 67}, {0, 8, 123}, {0, 8, 59}, {0, 9, 215}, {18, 7, 19}, {0, 8, 107}, {0, 8, 43}, {0, 9, 183}, {0, 8, 11}, {0, 8, 139}, {0, 8, 75}, {0, 9, 247}, {16, 7, 5}, {0, 8, 87}, {0, 8, 23}, {64, 8, 0}, {19, 7, 51}, {0, 8, 119}, {0, 8, 55}, {0, 9, 207}, {17, 7, 15}, {0, 8, 103}, {0, 8, 39}, {0, 9, 175}, {0, 8, 7}, {0, 8, 135}, {0, 8, 71}, {0, 9, 239}, {16, 7, 9}, {0, 8, 95}, {0, 8, 31}, {0, 9, 159}, {20, 7, 99}, {0, 8, 127}, {0, 8, 63}, {0, 9, 223}, {18, 7, 27}, {0, 8, 111}, {0, 8, 47}, {0, 9, 191}, {0, 8, 15}, {0, 8, 143}, {0, 8, 79}, {0, 9, 255}};
  static const code distfix[32] = {{16, 5, 1}, {23, 5, 257}, {19, 5, 17}, {27, 5, 4097}, {17, 5, 5}, {25, 5, 1025}, {21, 5, 65}, {29, 5, 16385}, {16, 5, 3}, {24, 5, 513}, {20, 5, 33}, {28, 5, 8193}, {18, 5, 9}, {26, 5, 2049}, {22, 5, 129}, {64, 5, 0}, {16, 5, 2}, {23, 5, 385}, {19, 5, 25}, {27, 5, 6145}, {17, 5, 7}, {25, 5, 1537}, {21, 5, 97}, {29, 5, 24577}, {16, 5, 4}, {24, 5, 769}, {20, 5, 49}, {28, 5, 12289}, {18, 5, 13}, {26, 5, 3073}, {22, 5, 193}, {64, 5, 0}};
  state->lencode = lenfix;
  state->lenbits = 9;
  state->distcode = distfix;
  state->distbits = 5;
}


----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'last_ref is a mutable refrence to code']
void helper_helper_inflate_1_12(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  for (;;)
  {
    here = state->distcode[((unsigned) hold) & ((1U << state->distbits) - 1)];
    if (((unsigned) here.bits) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  if ((here.op & 0xf0) == 0)
  {
    helper_helper_helper_inflate_1_12_1(&next_idx, &have, &hold, &bits, &here, &last, state, next);
  }
  do
  {
    hold >>= here.bits;
    bits -= (unsigned) here.bits;
  }
  while (0);
  state->back += here.bits;
  if (here.op & 64)
  {
    strm->msg = (char *) "invalid distance code";
    state->mode = BAD;
    break;
  }
  state->offset = (unsigned) here.val;
  state->extra = ((unsigned) here.op) & 15;
  state->mode = DISTEXT;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


/*** DEPENDENCIES:
void helper_helper_helper_inflate_1_12_1(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  last = here;
  for (;;)
  {
    here = state->distcode[last.val + ((((unsigned) hold) & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
    if (((unsigned) (last.bits + here.bits)) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  do
  {
    hold >>= last.bits;
    bits -= (unsigned) last.bits;
  }
  while (0);
  state->back += last.bits;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_2(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    while (bits < ((unsigned) 32))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  strm->adler = (state->check = ((((hold >> 24) & 0xff) + ((hold >> 8) & 0xff00)) + ((hold & 0xff00) << 8)) + ((hold & 0xff) << 24));
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  state->mode = DICT;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'copy_ref is a mutable refrence to unsigned', 'len_ref is a mutable refrence to unsigned']
void helper_helper_helper_helper_inflate_1_15_1_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const copy_ref, unsigned * const len_ref, struct inflate_state * const state, const unsigned char * const next, code here)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned copy = *copy_ref;
  unsigned len = *len_ref;
  if (here.val == 16)
  {
    do
    {
      while (bits < ((unsigned) (here.bits + 2)))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    if (state->have == 0)
    {
      strm->msg = (char *) "invalid bit length repeat";
      state->mode = BAD;
      break;
    }
    len = state->lens[state->have - 1];
    copy = 3 + (((unsigned) hold) & ((1U << 2) - 1));
    do
    {
      hold >>= 2;
      bits -= (unsigned) 2;
    }
    while (0);
  }
  else
    if (here.val == 17)
  {
    do
    {
      while (bits < ((unsigned) (here.bits + 3)))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    len = 0;
    copy = 3 + (((unsigned) hold) & ((1U << 3) - 1));
    do
    {
      hold >>= 3;
      bits -= (unsigned) 3;
    }
    while (0);
  }
  else
  {
    do
    {
      while (bits < ((unsigned) (here.bits + 7)))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    len = 0;
    copy = 11 + (((unsigned) hold) & ((1U << 7) - 1));
    do
    {
      hold >>= 7;
      bits -= (unsigned) 7;
    }
    while (0);
  }
  if ((state->have + copy) > (state->nlen + state->ndist))
  {
    strm->msg = (char *) "invalid bit length repeat";
    state->mode = BAD;
    break;
  }
  while (copy--)
  {
    state->lens[state->have++] = (unsigned short) len;
  }

  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *copy_ref = copy;
  *len_ref = len;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'copy_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'len_ref is a mutable refrence to unsigned']
void helper_helper_helper_inflate_1_15_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const copy_ref, code * const here_ref, unsigned * const len_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned copy = *copy_ref;
  code here = *here_ref;
  unsigned len = *len_ref;
  for (;;)
  {
    here = state->lencode[((unsigned) hold) & ((1U << state->lenbits) - 1)];
    if (((unsigned) here.bits) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  if (here.val < 16)
  {
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    state->lens[state->have++] = here.val;
  }
  else
  {
    helper_helper_helper_helper_inflate_1_15_1_1(&strm, &next_idx, &have, &hold, &bits, &copy, &len, state, next, here);
  }
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *copy_ref = copy;
  *here_ref = here;
  *len_ref = len;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_inflate_1_15_1_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const copy_ref, unsigned * const len_ref, struct inflate_state * const state, const unsigned char * const next, code here)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned copy = *copy_ref;
  unsigned len = *len_ref;
  if (here.val == 16)
  {
    do
    {
      while (bits < ((unsigned) (here.bits + 2)))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    if (state->have == 0)
    {
      strm->msg = (char *) "invalid bit length repeat";
      state->mode = BAD;
      break;
    }
    len = state->lens[state->have - 1];
    copy = 3 + (((unsigned) hold) & ((1U << 2) - 1));
    do
    {
      hold >>= 2;
      bits -= (unsigned) 2;
    }
    while (0);
  }
  else
    if (here.val == 17)
  {
    do
    {
      while (bits < ((unsigned) (here.bits + 3)))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    len = 0;
    copy = 3 + (((unsigned) hold) & ((1U << 3) - 1));
    do
    {
      hold >>= 3;
      bits -= (unsigned) 3;
    }
    while (0);
  }
  else
  {
    do
    {
      while (bits < ((unsigned) (here.bits + 7)))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    len = 0;
    copy = 11 + (((unsigned) hold) & ((1U << 7) - 1));
    do
    {
      hold >>= 7;
      bits -= (unsigned) 7;
    }
    while (0);
  }
  if ((state->have + copy) > (state->nlen + state->ndist))
  {
    strm->msg = (char *) "invalid bit length repeat";
    state->mode = BAD;
    break;
  }
  while (copy--)
  {
    state->lens[state->have++] = (unsigned short) len;
  }

  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *copy_ref = copy;
  *len_ref = len;
}


----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'copy_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'len_ref is a mutable refrence to unsigned', 'ret_ref is a mutable refrence to int']
void helper_helper_inflate_1_15(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const copy_ref, code * const here_ref, unsigned * const len_ref, int * const ret_ref, int flush, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned copy = *copy_ref;
  code here = *here_ref;
  unsigned len = *len_ref;
  int ret = *ret_ref;
  while (state->have < (state->nlen + state->ndist))
  {
    helper_helper_helper_inflate_1_15_1(&strm, &next_idx, &have, &hold, &bits, &copy, &here, &len, state, next);
  }

  if (state->mode == BAD)
  {
    break;
  }
  if (state->lens[256] == 0)
  {
    strm->msg = (char *) "invalid code -- missing end-of-block";
    state->mode = BAD;
    break;
  }
  state->next = state->codes;
  state->lencode = (const code *) state->next;
  state->lenbits = 9;
  ret = inflate_table(LENS, state->lens, state->nlen, &state->next, &state->lenbits, state->work);
  if (ret)
  {
    strm->msg = (char *) "invalid literal/lengths set";
    state->mode = BAD;
    break;
  }
  state->distcode = (const code *) state->next;
  state->distbits = 6;
  ret = inflate_table(DISTS, state->lens + state->nlen, state->ndist, &state->next, &state->distbits, state->work);
  if (ret)
  {
    strm->msg = (char *) "invalid distances set";
    state->mode = BAD;
    break;
  }
  ;
  state->mode = LEN_;
  if (flush == 6)
  {
    goto inf_leave;
  }
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *copy_ref = copy;
  *here_ref = here;
  *len_ref = len;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
int inflate_table(codetype type, unsigned short *lens, unsigned codes, code **table, unsigned *bits, unsigned short *work)
{
  unsigned len;
  unsigned sym;
  unsigned min;
  unsigned max;
  unsigned root;
  unsigned curr;
  unsigned drop;
  int left;
  unsigned used;
  unsigned huff;
  unsigned incr;
  unsigned fill;
  unsigned low;
  unsigned mask;
  code here;
  code *next;
  unsigned int next_idx = 0;
  const unsigned short *base;
  unsigned int base_idx = 0;
  const unsigned short *extra;
  unsigned int extra_idx = 0;
  unsigned match;
  unsigned short count[15 + 1];
  unsigned short offs[15 + 1];
  static const unsigned short lbase[31] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
  static const unsigned short lext[31] = {16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 16, 198, 203};
  static const unsigned short dbase[32] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0};
  static const unsigned short dext[32] = {16, 16, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 64, 64};
  for (len = 0; len <= 15; len += 1)
  {
    count[len] = 0;
  }

  for (sym = 0; sym < codes; sym += 1)
  {
    count[lens[sym]] += 1;
  }

  root = *bits;
  for (max = 15; max >= 1; max -= 1)
  {
    if (count[max] != 0)
    {
      break;
    }
  }

  if (root > max)
  {
    root = max;
  }
  if (max == 0)
  {
    here.op = (unsigned char) 64;
    here.bits = (unsigned char) 1;
    here.val = (unsigned short) 0;
    *((*table)++) = here;
    *((*table)++) = here;
    *bits = 1;
    return 0;
  }
  for (min = 1; min < max; min += 1)
  {
    if (count[min] != 0)
    {
      break;
    }
  }

  if (root < min)
  {
    root = min;
  }
  left = 1;
  for (len = 1; len <= 15; len += 1)
  {
    left <<= 1;
    left -= count[len];
    if (left < 0)
    {
      return -1;
    }
  }

  if ((left > 0) && ((type == CODES) || (max != 1)))
  {
    return -1;
  }
  offs[1] = 0;
  for (len = 1; len < 15; len += 1)
  {
    offs[len + 1] = offs[len] + count[len];
  }

  for (sym = 0; sym < codes; sym += 1)
  {
    if (lens[sym] != 0)
    {
      work[offs[lens[sym]]++] = (unsigned short) sym;
    }
  }

  switch (type)
  {
    case CODES:
    {
      base_idx = (extra = &extra[extra_idx + extra_idx]);
      match = 20;
      break;
    }

    case LENS:
    {
      base_idx = lbase;
      extra_idx = lext;
      match = 257;
      break;
    }

    default:
    {
      base_idx = dbase;
      extra_idx = dext;
      match = 0;
    }

  }

  huff = 0;
  sym = 0;
  len = min;
  next_idx = *table;
  curr = root;
  drop = 0;
  low = (unsigned) (-1);
  used = 1U << root;
  mask = used - 1;
  if (((type == LENS) && (used > 852)) || ((type == DISTS) && (used > 592)))
  {
    return 1;
  }
  for (;;)
  {
    helper_inflate_table_1(&len, &sym, &min, &curr, &drop, &left, &used, &huff, &incr, &fill, &low, &here, &next_idx, type, lens, table, work, max, root, mask, next, base, base_idx, extra, extra_idx, match, count);
  }

  if (huff != 0)
  {
    here.op = (unsigned char) 64;
    here.bits = (unsigned char) (len - drop);
    here.val = (unsigned short) 0;
    next[huff + next_idx] = here;
  }
  *table += used;
  *bits = root;
  return 0;
}


----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
void helper_helper_helper_inflate_1_15_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const copy_ref, code * const here_ref, unsigned * const len_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned copy = *copy_ref;
  code here = *here_ref;
  unsigned len = *len_ref;
  for (;;)
  {
    here = state->lencode[((unsigned) hold) & ((1U << state->lenbits) - 1)];
    if (((unsigned) here.bits) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  if (here.val < 16)
  {
    do
    {
      hold >>= here.bits;
      bits -= (unsigned) here.bits;
    }
    while (0);
    state->lens[state->have++] = here.val;
  }
  else
  {
    helper_helper_helper_helper_inflate_1_15_1_1(&strm, &next_idx, &have, &hold, &bits, &copy, &len, state, next, here);
  }
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *copy_ref = copy;
  *here_ref = here;
  *len_ref = len;
}


----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_6(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, int flush, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    hold >>= bits & 7;
    bits -= bits & 7;
  }
  while (0);
  do
  {
    while (bits < ((unsigned) 32))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff))
  {
    strm->msg = (char *) "invalid stored block lengths";
    state->mode = BAD;
    break;
  }
  state->length = ((unsigned) hold) & 0xffff;
  ;
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  state->mode = COPY_;
  if (flush == 6)
  {
    goto inf_leave;
  }
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'ret_ref is a mutable refrence to int']
void helper_helper_inflate_1_8(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, int * const ret_ref, struct inflate_state * const state, const unsigned char * const next, static const unsigned short order[19])
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  int ret = *ret_ref;
  while (state->have < state->ncode)
  {
    helper_helper_helper_inflate_1_8_1(&next_idx, &have, &hold, &bits, state, next, order);
  }

  while (state->have < 19)
  {
    state->lens[order[state->have++]] = 0;
  }

  state->next = state->codes;
  state->lencode = (const code *) state->next;
  state->lenbits = 7;
  ret = inflate_table(CODES, state->lens, 19, &state->next, &state->lenbits, state->work);
  if (ret)
  {
    strm->msg = (char *) "invalid code lengths set";
    state->mode = BAD;
    break;
  }
  ;
  state->have = 0;
  state->mode = CODELENS;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
void helper_helper_helper_inflate_1_8_1(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next, static const unsigned short order[19])
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    while (bits < ((unsigned) 3))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  state->lens[order[state->have++]] = (unsigned short) (((unsigned) hold) & ((1U << 3) - 1));
  do
  {
    hold >>= 3;
    bits -= (unsigned) 3;
  }
  while (0);
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
int inflate_table(codetype type, unsigned short *lens, unsigned codes, code **table, unsigned *bits, unsigned short *work)
{
  unsigned len;
  unsigned sym;
  unsigned min;
  unsigned max;
  unsigned root;
  unsigned curr;
  unsigned drop;
  int left;
  unsigned used;
  unsigned huff;
  unsigned incr;
  unsigned fill;
  unsigned low;
  unsigned mask;
  code here;
  code *next;
  unsigned int next_idx = 0;
  const unsigned short *base;
  unsigned int base_idx = 0;
  const unsigned short *extra;
  unsigned int extra_idx = 0;
  unsigned match;
  unsigned short count[15 + 1];
  unsigned short offs[15 + 1];
  static const unsigned short lbase[31] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
  static const unsigned short lext[31] = {16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 16, 198, 203};
  static const unsigned short dbase[32] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0};
  static const unsigned short dext[32] = {16, 16, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 64, 64};
  for (len = 0; len <= 15; len += 1)
  {
    count[len] = 0;
  }

  for (sym = 0; sym < codes; sym += 1)
  {
    count[lens[sym]] += 1;
  }

  root = *bits;
  for (max = 15; max >= 1; max -= 1)
  {
    if (count[max] != 0)
    {
      break;
    }
  }

  if (root > max)
  {
    root = max;
  }
  if (max == 0)
  {
    here.op = (unsigned char) 64;
    here.bits = (unsigned char) 1;
    here.val = (unsigned short) 0;
    *((*table)++) = here;
    *((*table)++) = here;
    *bits = 1;
    return 0;
  }
  for (min = 1; min < max; min += 1)
  {
    if (count[min] != 0)
    {
      break;
    }
  }

  if (root < min)
  {
    root = min;
  }
  left = 1;
  for (len = 1; len <= 15; len += 1)
  {
    left <<= 1;
    left -= count[len];
    if (left < 0)
    {
      return -1;
    }
  }

  if ((left > 0) && ((type == CODES) || (max != 1)))
  {
    return -1;
  }
  offs[1] = 0;
  for (len = 1; len < 15; len += 1)
  {
    offs[len + 1] = offs[len] + count[len];
  }

  for (sym = 0; sym < codes; sym += 1)
  {
    if (lens[sym] != 0)
    {
      work[offs[lens[sym]]++] = (unsigned short) sym;
    }
  }

  switch (type)
  {
    case CODES:
    {
      base_idx = (extra = &extra[extra_idx + extra_idx]);
      match = 20;
      break;
    }

    case LENS:
    {
      base_idx = lbase;
      extra_idx = lext;
      match = 257;
      break;
    }

    default:
    {
      base_idx = dbase;
      extra_idx = dext;
      match = 0;
    }

  }

  huff = 0;
  sym = 0;
  len = min;
  next_idx = *table;
  curr = root;
  drop = 0;
  low = (unsigned) (-1);
  used = 1U << root;
  mask = used - 1;
  if (((type == LENS) && (used > 852)) || ((type == DISTS) && (used > 592)))
  {
    return 1;
  }
  for (;;)
  {
    helper_inflate_table_1(&len, &sym, &min, &curr, &drop, &left, &used, &huff, &incr, &fill, &low, &here, &next_idx, type, lens, table, work, max, root, mask, next, base, base_idx, extra, extra_idx, match, count);
  }

  if (huff != 0)
  {
    here.op = (unsigned char) 64;
    here.bits = (unsigned char) (len - drop);
    here.val = (unsigned short) 0;
    next[huff + next_idx] = here;
  }
  *table += used;
  *bits = root;
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'copy_ref is a mutable refrence to unsigned', 'from_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_inflate_1_10_1(z_streamp * const strm_ref, unsigned * const copy_ref, unsigned int * const from_idx_ref, struct inflate_state * const state)
{
  z_streamp strm = *strm_ref;
  unsigned copy = *copy_ref;
  unsigned int from_idx = *from_idx_ref;
  copy = state->offset - copy;
  if (copy > state->whave)
  {
    if (state->sane)
    {
      strm->msg = (char *) "invalid distance too far back";
      state->mode = BAD;
      break;
    }
  }
  if (copy > state->wnext)
  {
    copy -= state->wnext;
    from_idx = state->window + (state->wsize - copy);
  }
  else
    from_idx = state->window + (state->wnext - copy);
  if (copy > state->length)
  {
    copy = state->length;
  }
  *strm_ref = strm;
  *copy_ref = copy;
  *from_idx_ref = from_idx;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'put_idx_ref is a mutable refrence to unsigned int', 'left_ref is a mutable refrence to unsigned', 'copy_ref is a mutable refrence to unsigned', 'from_idx_ref is a mutable refrence to unsigned int']
void helper_helper_inflate_1_10(z_streamp * const strm_ref, unsigned int * const put_idx_ref, unsigned * const left_ref, unsigned * const copy_ref, unsigned int * const from_idx_ref, struct inflate_state * const state, unsigned char * const put, unsigned char * const from, unsigned out)
{
  z_streamp strm = *strm_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned left = *left_ref;
  unsigned copy = *copy_ref;
  unsigned int from_idx = *from_idx_ref;
  if (left == 0)
  {
    goto inf_leave;
  }
  copy = out - left;
  if (state->offset > copy)
  {
    helper_helper_helper_inflate_1_10_1(&strm, &copy, &from_idx, state);
  }
  else
  {
    from_idx = (&put[put_idx]) - state->offset;
    copy = state->length;
  }
  if (copy > left)
  {
    copy = left;
  }
  left -= copy;
  state->length -= copy;
  do
  {
    put[put_idx] = from[from_idx];
    from_idx += 1;
    put_idx += 1;
  }
  while (--copy);
  if (state->length == 0)
  {
    state->mode = LEN;
  }
  break;
  *strm_ref = strm;
  *put_idx_ref = put_idx;
  *left_ref = left;
  *copy_ref = copy;
  *from_idx_ref = from_idx;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
void helper_helper_helper_inflate_1_10_1(z_streamp * const strm_ref, unsigned * const copy_ref, unsigned int * const from_idx_ref, struct inflate_state * const state)
{
  z_streamp strm = *strm_ref;
  unsigned copy = *copy_ref;
  unsigned int from_idx = *from_idx_ref;
  copy = state->offset - copy;
  if (copy > state->whave)
  {
    if (state->sane)
    {
      strm->msg = (char *) "invalid distance too far back";
      state->mode = BAD;
      break;
    }
  }
  if (copy > state->wnext)
  {
    copy -= state->wnext;
    from_idx = state->window + (state->wsize - copy);
  }
  else
    from_idx = state->window + (state->wnext - copy);
  if (copy > state->length)
  {
    copy = state->length;
  }
  *strm_ref = strm;
  *copy_ref = copy;
  *from_idx_ref = from_idx;
}


----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'len_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_11(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const len_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned len = *len_ref;
  if (state->wrap == 0)
  {
    state->mode = TYPEDO;
    break;
  }
  do
  {
    while (bits < ((unsigned) 16))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  if ((((((unsigned) hold) & ((1U << 8) - 1)) << 8) + (hold >> 8)) % 31)
  {
    strm->msg = (char *) "incorrect header check";
    state->mode = BAD;
    break;
  }
  if ((((unsigned) hold) & ((1U << 4) - 1)) != 8)
  {
    strm->msg = (char *) "unknown compression method";
    state->mode = BAD;
    break;
  }
  do
  {
    hold >>= 4;
    bits -= (unsigned) 4;
  }
  while (0);
  len = (((unsigned) hold) & ((1U << 4) - 1)) + 8;
  if (state->wbits == 0)
  {
    state->wbits = len;
  }
  if ((len > 15) || (len > state->wbits))
  {
    strm->msg = (char *) "invalid window size";
    state->mode = BAD;
    break;
  }
  state->dmax = 1U << len;
  state->flags = 0;
  ;
  strm->adler = (state->check = adler32(0L, 0, 0));
  state->mode = (hold & 0x200) ? (DICTID) : (TYPE);
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  break;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *len_ref = len;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_9(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    while (bits < ((unsigned) 14))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  state->nlen = (((unsigned) hold) & ((1U << 5) - 1)) + 257;
  do
  {
    hold >>= 5;
    bits -= (unsigned) 5;
  }
  while (0);
  state->ndist = (((unsigned) hold) & ((1U << 5) - 1)) + 1;
  do
  {
    hold >>= 5;
    bits -= (unsigned) 5;
  }
  while (0);
  state->ncode = (((unsigned) hold) & ((1U << 4) - 1)) + 4;
  do
  {
    hold >>= 4;
    bits -= (unsigned) 4;
  }
  while (0);
  if ((state->nlen > 286) || (state->ndist > 30))
  {
    strm->msg = (char *) "too many length or distance symbols";
    state->mode = BAD;
    break;
  }
  ;
  state->have = 0;
  state->mode = LENLENS;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
int helper_helper_inflate_1_1(z_streamp * const strm_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned int next_idx, unsigned int put_idx, unsigned have, unsigned left)
{
  z_streamp strm = *strm_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->havedict == 0)
  {
    do
    {
      strm->next_out = &put[put_idx];
      strm->avail_out = left;
      strm->next_in = &next[next_idx];
      strm->avail_in = have;
      state->hold = hold;
      state->bits = bits;
    }
    while (0);
    return 2;
  }
  strm->adler = (state->check = adler32(0L, 0, 0));
  state->mode = TYPE;
  *strm_ref = strm;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'out_ref is a mutable refrence to unsigned']
void helper_helper_helper_inflate_1_7_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const out_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned int put_idx, unsigned left)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned out = *out_ref;
  do
  {
    while (bits < ((unsigned) 32))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  out -= left;
  strm->total_out += out;
  state->total += out;
  if ((state->wrap & 4) && out)
  {
    strm->adler = (state->check = adler32(state->check, (&put[put_idx]) - out, out));
  }
  out = left;
  if ((state->wrap & 4) && ((((((hold >> 24) & 0xff) + ((hold >> 8) & 0xff00)) + ((hold & 0xff00) << 8)) + ((hold & 0xff) << 24)) != state->check))
  {
    strm->msg = (char *) "incorrect data check";
    state->mode = BAD;
    break;
  }
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  ;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *out_ref = out;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'out_ref is a mutable refrence to unsigned']
void helper_helper_inflate_1_7(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const out_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned int put_idx, unsigned left)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned out = *out_ref;
  if (state->wrap)
  {
    helper_helper_helper_inflate_1_7_1(&strm, &next_idx, &have, &hold, &bits, &out, state, next, put, put_idx, left);
  }
  state->mode = DONE;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *out_ref = out;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
void helper_helper_helper_inflate_1_7_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const out_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned int put_idx, unsigned left)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned out = *out_ref;
  do
  {
    while (bits < ((unsigned) 32))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  out -= left;
  strm->total_out += out;
  state->total += out;
  if ((state->wrap & 4) && out)
  {
    strm->adler = (state->check = adler32(state->check, (&put[put_idx]) - out, out));
  }
  out = left;
  if ((state->wrap & 4) && ((((((hold >> 24) & 0xff) + ((hold >> 8) & 0xff00)) + ((hold & 0xff00) << 8)) + ((hold & 0xff) << 24)) != state->check))
  {
    strm->msg = (char *) "incorrect data check";
    state->mode = BAD;
    break;
  }
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  ;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *out_ref = out;
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'put_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'left_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned']
void helper_helper_helper_inflate_1_14_2(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned out)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    strm->next_out = &put[put_idx];
    strm->avail_out = left;
    strm->next_in = &next[next_idx];
    strm->avail_in = have;
    state->hold = hold;
    state->bits = bits;
  }
  while (0);
  inflate_fast(strm, out);
  do
  {
    put_idx = strm->next_out;
    left = strm->avail_out;
    next_idx = strm->next_in;
    have = strm->avail_in;
    hold = state->hold;
    bits = state->bits;
  }
  while (0);
  if (state->mode == TYPE)
  {
    state->back = -1;
  }
  break;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *hold_ref = hold;
  *bits_ref = bits;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
void inflate_fast(z_streamp strm, unsigned start)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  const unsigned char *in;
  unsigned int in_idx = 0;
  const unsigned char *last;
  unsigned int last_idx = 0;
  unsigned char *out;
  unsigned int out_idx = 0;
  unsigned char *beg;
  unsigned int beg_idx = 0;
  unsigned char *end;
  unsigned int end_idx = 0;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned int window_idx = 0;
  unsigned long hold;
  unsigned bits;
  const code *lcode;
  unsigned int lcode_idx = 0;
  const code *dcode;
  unsigned int dcode_idx = 0;
  unsigned lmask;
  unsigned dmask;
  const code *here;
  unsigned int here_idx = 0;
  unsigned op;
  unsigned len;
  unsigned dist;
  unsigned char *from;
  unsigned int from_idx = 0;
  state_idx = (struct inflate_state *) strm->state_idx;
  in_idx = strm->next_in;
  last_idx = (&in[in_idx]) + (strm->avail_in - 5);
  out_idx = strm->next_out;
  beg_idx = (&out[out_idx]) - (start - strm->avail_out);
  end_idx = (&out[out_idx]) + (strm->avail_out - 257);
  wsize = state->wsize;
  whave = state->whave;
  wnext = state->wnext;
  window_idx = state->window_idx;
  hold = state->hold;
  bits = state->bits;
  lcode_idx = state->lencode;
  dcode_idx = state->distcode;
  lmask = (1U << state->lenbits) - 1;
  dmask = (1U << state->distbits) - 1;
  do
  {
    helper_inflate_fast_1(&strm, &in_idx, &out_idx, &hold, &bits, &here_idx, &op, &len, &dist, &from_idx, state, in, out, beg, beg_idx, wsize, whave, wnext, window, window_idx, lcode, lcode_idx, dcode, dcode_idx, lmask, dmask, here, from);
  }
  while (((&in[in_idx]) < (&last[last_idx])) && ((&out[out_idx]) < (&end[end_idx])));
  len = bits >> 3;
  in_idx -= len;
  bits -= len << 3;
  hold &= (1U << bits) - 1;
  strm->next_in = &in[in_idx];
  strm->next_out = &out[out_idx];
  strm->avail_in = (unsigned) (((&in[in_idx]) < (&last[last_idx])) ? (5 + ((&last[last_idx]) - (&in[in_idx]))) : (5 - ((&in[in_idx]) - (&last[last_idx]))));
  strm->avail_out = (unsigned) (((&out[out_idx]) < (&end[end_idx])) ? (257 + ((&end[end_idx]) - (&out[out_idx]))) : (257 - ((&out[out_idx]) - (&end[end_idx]))));
  state->hold = hold;
  state->bits = bits;
  return;
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'put_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'left_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'last_ref is a mutable refrence to code']
void helper_helper_inflate_1_14(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned out)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  if ((have >= 6) && (left >= 258))
  {
    helper_helper_helper_inflate_1_14_2(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, state, next, put, out);
  }
  state->back = 0;
  for (;;)
  {
    here = state->lencode[((unsigned) hold) & ((1U << state->lenbits) - 1)];
    if (((unsigned) here.bits) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  if (here.op && ((here.op & 0xf0) == 0))
  {
    helper_helper_helper_inflate_1_14_1(&next_idx, &have, &hold, &bits, &here, &last, state, next);
  }
  do
  {
    hold >>= here.bits;
    bits -= (unsigned) here.bits;
  }
  while (0);
  state->back += here.bits;
  state->length = (unsigned) here.val;
  if (((int) here.op) == 0)
  {
    ;
    state->mode = LIT;
    break;
  }
  if (here.op & 32)
  {
    ;
    state->back = -1;
    state->mode = TYPE;
    break;
  }
  if (here.op & 64)
  {
    strm->msg = (char *) "invalid literal/length code";
    state->mode = BAD;
    break;
  }
  state->extra = ((unsigned) here.op) & 15;
  state->mode = LENEXT;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


/*** DEPENDENCIES:
void helper_helper_helper_inflate_1_14_2(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned out)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    strm->next_out = &put[put_idx];
    strm->avail_out = left;
    strm->next_in = &next[next_idx];
    strm->avail_in = have;
    state->hold = hold;
    state->bits = bits;
  }
  while (0);
  inflate_fast(strm, out);
  do
  {
    put_idx = strm->next_out;
    left = strm->avail_out;
    next_idx = strm->next_in;
    have = strm->avail_in;
    hold = state->hold;
    bits = state->bits;
  }
  while (0);
  if (state->mode == TYPE)
  {
    state->back = -1;
  }
  break;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
void helper_helper_helper_inflate_1_14_1(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  last = here;
  for (;;)
  {
    here = state->lencode[last.val + ((((unsigned) hold) & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
    if (((unsigned) (last.bits + here.bits)) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  do
  {
    hold >>= last.bits;
    bits -= (unsigned) last.bits;
  }
  while (0);
  state->back += last.bits;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['strm_ref is a mutable refrence to z_streamp', 'next_idx_ref is a mutable refrence to unsigned int', 'put_idx_ref is a mutable refrence to unsigned int', 'have_ref is a mutable refrence to unsigned', 'left_ref is a mutable refrence to unsigned', 'hold_ref is a mutable refrence to unsigned long', 'bits_ref is a mutable refrence to unsigned', 'out_ref is a mutable refrence to unsigned', 'copy_ref is a mutable refrence to unsigned', 'from_idx_ref is a mutable refrence to unsigned int', 'here_ref is a mutable refrence to code', 'last_ref is a mutable refrence to code', 'len_ref is a mutable refrence to unsigned', 'ret_ref is a mutable refrence to int']
int helper_inflate_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const out_ref, unsigned * const copy_ref, unsigned int * const from_idx_ref, code * const here_ref, code * const last_ref, unsigned * const len_ref, int * const ret_ref, int flush, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned char * const from, static const unsigned short order[19])
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned out = *out_ref;
  unsigned copy = *copy_ref;
  unsigned int from_idx = *from_idx_ref;
  code here = *here_ref;
  code last = *last_ref;
  unsigned len = *len_ref;
  int ret = *ret_ref;
  switch (state->mode)
  {
    case HEAD:
    {
      helper_helper_inflate_1_11(&strm, &next_idx, &have, &hold, &bits, &len, state, next);
    }

    case DICTID:
    {
      helper_helper_inflate_1_2(&strm, &next_idx, &have, &hold, &bits, state, next);
    }

    case DICT:
    {
      helper_helper_inflate_1_1(&strm, &hold, &bits, state, next, put, next_idx, put_idx, have, left);
    }

    case TYPE:
    {
      if ((flush == 5) || (flush == 6))
      {
        goto inf_leave;
      }
    }

    case TYPEDO:
    {
      helper_helper_inflate_1_13(&strm, &next_idx, &have, &hold, &bits, flush, state, next);
    }

    case STORED:
    {
      helper_helper_inflate_1_6(&strm, &next_idx, &have, &hold, &bits, flush, state, next);
    }

    case COPY_:
    {
      state->mode = COPY;
    }

    case COPY:
    {
      helper_helper_inflate_1_4(&next_idx, &put_idx, &have, &left, &copy, state, next, put);
    }

    case TABLE:
    {
      helper_helper_inflate_1_9(&strm, &next_idx, &have, &hold, &bits, state, next);
    }

    case LENLENS:
    {
      helper_helper_inflate_1_8(&strm, &next_idx, &have, &hold, &bits, &ret, state, next, order);
    }

    case CODELENS:
    {
      helper_helper_inflate_1_15(&strm, &next_idx, &have, &hold, &bits, &copy, &here, &len, &ret, flush, state, next);
    }

    case LEN_:
    {
      state->mode = LEN;
    }

    case LEN:
    {
      helper_helper_inflate_1_14(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, &here, &last, state, next, put, out);
    }

    case LENEXT:
    {
      helper_helper_inflate_1_5(&next_idx, &have, &hold, &bits, state, next);
    }

    case DIST:
    {
      helper_helper_inflate_1_12(&strm, &next_idx, &have, &hold, &bits, &here, &last, state, next);
    }

    case DISTEXT:
    {
      helper_helper_inflate_1_3(&next_idx, &have, &hold, &bits, state, next);
    }

    case MATCH:
    {
      helper_helper_inflate_1_10(&strm, &put_idx, &left, &copy, &from_idx, state, put, from, out);
    }

    case LIT:
    {
      if (left == 0)
      {
        goto inf_leave;
      }
      put[put_idx] = (unsigned char) state->length;
      put_idx += 1;
      left -= 1;
      state->mode = LEN;
      break;
    }

    case CHECK:
    {
      helper_helper_inflate_1_7(&strm, &next_idx, &have, &hold, &bits, &out, state, next, put, put_idx, left);
    }

    case DONE:
    {
      ret = 1;
      goto inf_leave;
    }

    case BAD:
    {
      ret = -3;
      goto inf_leave;
    }

    case MEM:
    {
      return -4;
    }

    case SYNC:

    default:
    {
      return -2;
    }

  }

  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *hold_ref = hold;
  *bits_ref = bits;
  *out_ref = out;
  *copy_ref = copy;
  *from_idx_ref = from_idx;
  *here_ref = here;
  *last_ref = last;
  *len_ref = len;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
void helper_helper_inflate_1_13(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, int flush, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->last)
  {
    do
    {
      hold >>= bits & 7;
      bits -= bits & 7;
    }
    while (0);
    state->mode = CHECK;
    break;
  }
  do
  {
    while (bits < ((unsigned) 3))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  state->last = ((unsigned) hold) & ((1U << 1) - 1);
  do
  {
    hold >>= 1;
    bits -= (unsigned) 1;
  }
  while (0);
  switch (((unsigned) hold) & ((1U << 2) - 1))
  {
    case 0:
    {
      ;
      state->mode = STORED;
      break;
    }

    case 1:
    {
      fixedtables(state);
      ;
      state->mode = LEN_;
      if (flush == 6)
      {
        do
        {
          hold >>= 2;
          bits -= (unsigned) 2;
        }
        while (0);
        goto inf_leave;
      }
      break;
    }

    case 2:
    {
      ;
      state->mode = TABLE;
      break;
    }

    case 3:
    {
      strm->msg = (char *) "invalid block type";
      state->mode = BAD;
    }

  }

  do
  {
    hold >>= 2;
    bits -= (unsigned) 2;
  }
  while (0);
  break;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
void helper_helper_inflate_1_12(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  for (;;)
  {
    here = state->distcode[((unsigned) hold) & ((1U << state->distbits) - 1)];
    if (((unsigned) here.bits) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  if ((here.op & 0xf0) == 0)
  {
    helper_helper_helper_inflate_1_12_1(&next_idx, &have, &hold, &bits, &here, &last, state, next);
  }
  do
  {
    hold >>= here.bits;
    bits -= (unsigned) here.bits;
  }
  while (0);
  state->back += here.bits;
  if (here.op & 64)
  {
    strm->msg = (char *) "invalid distance code";
    state->mode = BAD;
    break;
  }
  state->offset = (unsigned) here.val;
  state->extra = ((unsigned) here.op) & 15;
  state->mode = DISTEXT;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


----------------------------
void helper_helper_inflate_1_4(unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned * const copy_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned copy = *copy_ref;
  copy = state->length;
  if (copy)
  {
    if (copy > have)
    {
      copy = have;
    }
    if (copy > left)
    {
      copy = left;
    }
    if (copy == 0)
    {
      goto inf_leave;
    }
    memcpy(put, next, copy);
    have -= copy;
    next_idx += copy;
    left -= copy;
    put_idx += copy;
    state->length -= copy;
    break;
  }
  ;
  state->mode = TYPE;
  break;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *copy_ref = copy;
}


----------------------------
typedef z_stream *z_streamp
----------------------------
void helper_helper_inflate_1_2(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    while (bits < ((unsigned) 32))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  strm->adler = (state->check = ((((hold >> 24) & 0xff) + ((hold >> 8) & 0xff00)) + ((hold & 0xff00) << 8)) + ((hold & 0xff) << 24));
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  state->mode = DICT;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
void helper_helper_inflate_1_15(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const copy_ref, code * const here_ref, unsigned * const len_ref, int * const ret_ref, int flush, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned copy = *copy_ref;
  code here = *here_ref;
  unsigned len = *len_ref;
  int ret = *ret_ref;
  while (state->have < (state->nlen + state->ndist))
  {
    helper_helper_helper_inflate_1_15_1(&strm, &next_idx, &have, &hold, &bits, &copy, &here, &len, state, next);
  }

  if (state->mode == BAD)
  {
    break;
  }
  if (state->lens[256] == 0)
  {
    strm->msg = (char *) "invalid code -- missing end-of-block";
    state->mode = BAD;
    break;
  }
  state->next = state->codes;
  state->lencode = (const code *) state->next;
  state->lenbits = 9;
  ret = inflate_table(LENS, state->lens, state->nlen, &state->next, &state->lenbits, state->work);
  if (ret)
  {
    strm->msg = (char *) "invalid literal/lengths set";
    state->mode = BAD;
    break;
  }
  state->distcode = (const code *) state->next;
  state->distbits = 6;
  ret = inflate_table(DISTS, state->lens + state->nlen, state->ndist, &state->next, &state->distbits, state->work);
  if (ret)
  {
    strm->msg = (char *) "invalid distances set";
    state->mode = BAD;
    break;
  }
  ;
  state->mode = LEN_;
  if (flush == 6)
  {
    goto inf_leave;
  }
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *copy_ref = copy;
  *here_ref = here;
  *len_ref = len;
  *ret_ref = ret;
}


----------------------------
void helper_helper_inflate_1_6(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, int flush, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    hold >>= bits & 7;
    bits -= bits & 7;
  }
  while (0);
  do
  {
    while (bits < ((unsigned) 32))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff))
  {
    strm->msg = (char *) "invalid stored block lengths";
    state->mode = BAD;
    break;
  }
  state->length = ((unsigned) hold) & 0xffff;
  ;
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  state->mode = COPY_;
  if (flush == 6)
  {
    goto inf_leave;
  }
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
void helper_helper_inflate_1_8(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, int * const ret_ref, struct inflate_state * const state, const unsigned char * const next, static const unsigned short order[19])
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  int ret = *ret_ref;
  while (state->have < state->ncode)
  {
    helper_helper_helper_inflate_1_8_1(&next_idx, &have, &hold, &bits, state, next, order);
  }

  while (state->have < 19)
  {
    state->lens[order[state->have++]] = 0;
  }

  state->next = state->codes;
  state->lencode = (const code *) state->next;
  state->lenbits = 7;
  ret = inflate_table(CODES, state->lens, 19, &state->next, &state->lenbits, state->work);
  if (ret)
  {
    strm->msg = (char *) "invalid code lengths set";
    state->mode = BAD;
    break;
  }
  ;
  state->have = 0;
  state->mode = CODELENS;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *ret_ref = ret;
}


----------------------------
void helper_helper_inflate_1_10(z_streamp * const strm_ref, unsigned int * const put_idx_ref, unsigned * const left_ref, unsigned * const copy_ref, unsigned int * const from_idx_ref, struct inflate_state * const state, unsigned char * const put, unsigned char * const from, unsigned out)
{
  z_streamp strm = *strm_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned left = *left_ref;
  unsigned copy = *copy_ref;
  unsigned int from_idx = *from_idx_ref;
  if (left == 0)
  {
    goto inf_leave;
  }
  copy = out - left;
  if (state->offset > copy)
  {
    helper_helper_helper_inflate_1_10_1(&strm, &copy, &from_idx, state);
  }
  else
  {
    from_idx = (&put[put_idx]) - state->offset;
    copy = state->length;
  }
  if (copy > left)
  {
    copy = left;
  }
  left -= copy;
  state->length -= copy;
  do
  {
    put[put_idx] = from[from_idx];
    from_idx += 1;
    put_idx += 1;
  }
  while (--copy);
  if (state->length == 0)
  {
    state->mode = LEN;
  }
  break;
  *strm_ref = strm;
  *put_idx_ref = put_idx;
  *left_ref = left;
  *copy_ref = copy;
  *from_idx_ref = from_idx;
}


----------------------------
void helper_helper_inflate_1_11(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const len_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned len = *len_ref;
  if (state->wrap == 0)
  {
    state->mode = TYPEDO;
    break;
  }
  do
  {
    while (bits < ((unsigned) 16))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  if ((((((unsigned) hold) & ((1U << 8) - 1)) << 8) + (hold >> 8)) % 31)
  {
    strm->msg = (char *) "incorrect header check";
    state->mode = BAD;
    break;
  }
  if ((((unsigned) hold) & ((1U << 4) - 1)) != 8)
  {
    strm->msg = (char *) "unknown compression method";
    state->mode = BAD;
    break;
  }
  do
  {
    hold >>= 4;
    bits -= (unsigned) 4;
  }
  while (0);
  len = (((unsigned) hold) & ((1U << 4) - 1)) + 8;
  if (state->wbits == 0)
  {
    state->wbits = len;
  }
  if ((len > 15) || (len > state->wbits))
  {
    strm->msg = (char *) "invalid window size";
    state->mode = BAD;
    break;
  }
  state->dmax = 1U << len;
  state->flags = 0;
  ;
  strm->adler = (state->check = adler32(0L, 0, 0));
  state->mode = (hold & 0x200) ? (DICTID) : (TYPE);
  do
  {
    hold = 0;
    bits = 0;
  }
  while (0);
  break;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *len_ref = len;
}


----------------------------
void helper_helper_inflate_1_9(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  do
  {
    while (bits < ((unsigned) 14))
    {
      do
      {
        if (have == 0)
        {
          goto inf_leave;
        }
        have -= 1;
        hold += ((unsigned long) next[next_idx]) << bits;
        next_idx += 1;
        bits += 8;
      }
      while (0);
    }

  }
  while (0);
  state->nlen = (((unsigned) hold) & ((1U << 5) - 1)) + 257;
  do
  {
    hold >>= 5;
    bits -= (unsigned) 5;
  }
  while (0);
  state->ndist = (((unsigned) hold) & ((1U << 5) - 1)) + 1;
  do
  {
    hold >>= 5;
    bits -= (unsigned) 5;
  }
  while (0);
  state->ncode = (((unsigned) hold) & ((1U << 4) - 1)) + 4;
  do
  {
    hold >>= 4;
    bits -= (unsigned) 4;
  }
  while (0);
  if ((state->nlen > 286) || (state->ndist > 30))
  {
    strm->msg = (char *) "too many length or distance symbols";
    state->mode = BAD;
    break;
  }
  ;
  state->have = 0;
  state->mode = LENLENS;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
void helper_helper_inflate_1_5(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->extra)
  {
    do
    {
      while (bits < ((unsigned) state->extra))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    state->length += ((unsigned) hold) & ((1U << state->extra) - 1);
    do
    {
      hold >>= state->extra;
      bits -= (unsigned) state->extra;
    }
    while (0);
    state->back += state->extra;
  }
  ;
  state->was = state->length;
  state->mode = DIST;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
int helper_helper_inflate_1_1(z_streamp * const strm_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned int next_idx, unsigned int put_idx, unsigned have, unsigned left)
{
  z_streamp strm = *strm_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->havedict == 0)
  {
    do
    {
      strm->next_out = &put[put_idx];
      strm->avail_out = left;
      strm->next_in = &next[next_idx];
      strm->avail_in = have;
      state->hold = hold;
      state->bits = bits;
    }
    while (0);
    return 2;
  }
  strm->adler = (state->check = adler32(0L, 0, 0));
  state->mode = TYPE;
  *strm_ref = strm;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
void helper_helper_inflate_1_7(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const out_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned int put_idx, unsigned left)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned out = *out_ref;
  if (state->wrap)
  {
    helper_helper_helper_inflate_1_7_1(&strm, &next_idx, &have, &hold, &bits, &out, state, next, put, put_idx, left);
  }
  state->mode = DONE;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
  *out_ref = out;
}


----------------------------
void helper_helper_inflate_1_14(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned long * const hold_ref, unsigned * const bits_ref, code * const here_ref, code * const last_ref, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned out)
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  code here = *here_ref;
  code last = *last_ref;
  if ((have >= 6) && (left >= 258))
  {
    helper_helper_helper_inflate_1_14_2(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, state, next, put, out);
  }
  state->back = 0;
  for (;;)
  {
    here = state->lencode[((unsigned) hold) & ((1U << state->lenbits) - 1)];
    if (((unsigned) here.bits) <= bits)
    {
      break;
    }
    do
    {
      if (have == 0)
      {
        goto inf_leave;
      }
      have -= 1;
      hold += ((unsigned long) next[next_idx]) << bits;
      next_idx += 1;
      bits += 8;
    }
    while (0);
  }

  if (here.op && ((here.op & 0xf0) == 0))
  {
    helper_helper_helper_inflate_1_14_1(&next_idx, &have, &hold, &bits, &here, &last, state, next);
  }
  do
  {
    hold >>= here.bits;
    bits -= (unsigned) here.bits;
  }
  while (0);
  state->back += here.bits;
  state->length = (unsigned) here.val;
  if (((int) here.op) == 0)
  {
    ;
    state->mode = LIT;
    break;
  }
  if (here.op & 32)
  {
    ;
    state->back = -1;
    state->mode = TYPE;
    break;
  }
  if (here.op & 64)
  {
    strm->msg = (char *) "invalid literal/length code";
    state->mode = BAD;
    break;
  }
  state->extra = ((unsigned) here.op) & 15;
  state->mode = LENEXT;
  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_ref = here;
  *last_ref = last;
}


----------------------------
void helper_helper_inflate_1_3(unsigned int * const next_idx_ref, unsigned * const have_ref, unsigned long * const hold_ref, unsigned * const bits_ref, struct inflate_state * const state, const unsigned char * const next)
{
  unsigned int next_idx = *next_idx_ref;
  unsigned have = *have_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  if (state->extra)
  {
    do
    {
      while (bits < ((unsigned) state->extra))
      {
        do
        {
          if (have == 0)
          {
            goto inf_leave;
          }
          have -= 1;
          hold += ((unsigned long) next[next_idx]) << bits;
          next_idx += 1;
          bits += 8;
        }
        while (0);
      }

    }
    while (0);
    state->offset += ((unsigned) hold) & ((1U << state->extra) - 1);
    do
    {
      hold >>= state->extra;
      bits -= (unsigned) state->extra;
    }
    while (0);
    state->back += state->extra;
  }
  ;
  state->mode = MATCH;
  *next_idx_ref = next_idx;
  *have_ref = have;
  *hold_ref = hold;
  *bits_ref = bits;
}


----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


// hint:  ['copy_ref is a mutable refrence to unsigned', 'dist_ref is a mutable refrence to unsigned']
void helper_updatewindow_1(unsigned * const copy_ref, unsigned * const dist_ref, const Bytef * const end, struct inflate_state * const state)
{
  unsigned copy = *copy_ref;
  unsigned dist = *dist_ref;
  dist = state->wsize - state->wnext;
  if (dist > copy)
  {
    dist = copy;
  }
  memcpy(state->window + state->wnext, end - copy, dist);
  copy -= dist;
  if (copy)
  {
    memcpy(state->window, end - copy, copy);
    state->wnext = copy;
    state->whave = state->wsize;
  }
  else
  {
    state->wnext += dist;
    if (state->wnext == state->wsize)
    {
      state->wnext = 0;
    }
    if (state->whave < state->wsize)
    {
      state->whave += dist;
    }
  }
  *copy_ref = copy;
  *dist_ref = dist;
}


/*** DEPENDENCIES:
typedef Byte Bytef
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef unsigned char Byte
----------------------------
***/


static int updatewindow(z_streamp strm, const Bytef *end, unsigned copy)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  unsigned dist;
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->window == 0)
  {
    state->window = (unsigned char *) (*strm->zalloc)(strm->opaque, 1U << state->wbits, sizeof(unsigned char));
    if (state->window == 0)
    {
      return 1;
    }
  }
  if (state->wsize == 0)
  {
    state->wsize = 1U << state->wbits;
    state->wnext = 0;
    state->whave = 0;
  }
  if (copy >= state->wsize)
  {
    memcpy(state->window, end - state->wsize, state->wsize);
    state->wnext = 0;
    state->whave = state->wsize;
  }
  else
  {
    helper_updatewindow_1(&copy, &dist, end, state);
  }
  return 0;
}


/*** DEPENDENCIES:
typedef Byte Bytef
----------------------------
void helper_updatewindow_1(unsigned * const copy_ref, unsigned * const dist_ref, const Bytef * const end, struct inflate_state * const state)
{
  unsigned copy = *copy_ref;
  unsigned dist = *dist_ref;
  dist = state->wsize - state->wnext;
  if (dist > copy)
  {
    dist = copy;
  }
  memcpy(state->window + state->wnext, end - copy, dist);
  copy -= dist;
  if (copy)
  {
    memcpy(state->window, end - copy, copy);
    state->wnext = copy;
    state->whave = state->wsize;
  }
  else
  {
    state->wnext += dist;
    if (state->wnext == state->wsize)
    {
      state->wnext = 0;
    }
    if (state->whave < state->wsize)
    {
      state->whave += dist;
    }
  }
  *copy_ref = copy;
  *dist_ref = dist;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef unsigned char Byte
----------------------------
***/


int inflate(z_streamp strm, int flush)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  const unsigned char *next;
  unsigned int next_idx = 0;
  unsigned char *put;
  unsigned int put_idx = 0;
  unsigned have;
  unsigned left;
  unsigned long hold;
  unsigned bits;
  unsigned in;
  unsigned out;
  unsigned copy;
  unsigned char *from;
  unsigned int from_idx = 0;
  code here;
  code last;
  unsigned len;
  int ret;
  static const unsigned short order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  if ((inflateStateCheck(strm) || (strm->next_out == 0)) || ((strm->next_in == 0) && (strm->avail_in != 0)))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->mode == TYPE)
  {
    state->mode = TYPEDO;
  }
  do
  {
    put_idx = strm->next_out;
    left = strm->avail_out;
    next_idx = strm->next_in;
    have = strm->avail_in;
    hold = state->hold;
    bits = state->bits;
  }
  while (0);
  in = have;
  out = left;
  ret = 0;
  for (;;)
  {
    helper_inflate_1(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, &out, &copy, &from_idx, &here, &last, &len, &ret, flush, state, next, put, from, order);
  }

  inf_leave:
  do
  {
    strm->next_out = &put[put_idx];
    strm->avail_out = left;
    strm->next_in = &next[next_idx];
    strm->avail_in = have;
    state->hold = hold;
    state->bits = bits;
  }
  while (0);

  if (state->wsize || (((out != strm->avail_out) && (state->mode < BAD)) && ((state->mode < CHECK) || (flush != 4))))
  {
    if (updatewindow(strm, strm->next_out, out - strm->avail_out))
    {
      state->mode = MEM;
      return -4;
    }
  }
  in -= strm->avail_in;
  out -= strm->avail_out;
  strm->total_in += in;
  strm->total_out += out;
  state->total += out;
  if ((state->wrap & 4) && out)
  {
    strm->adler = (state->check = adler32(state->check, strm->next_out - out, out));
  }
  strm->data_type = ((((int) state->bits) + ((state->last) ? (64) : (0))) + ((state->mode == TYPE) ? (128) : (0))) + (((state->mode == LEN_) || (state->mode == COPY_)) ? (256) : (0));
  if ((((in == 0) && (out == 0)) || (flush == 4)) && (ret == 0))
  {
    ret = -5;
  }
  return ret;
}


/*** DEPENDENCIES:
uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}


----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
int helper_inflate_1(z_streamp * const strm_ref, unsigned int * const next_idx_ref, unsigned int * const put_idx_ref, unsigned * const have_ref, unsigned * const left_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const out_ref, unsigned * const copy_ref, unsigned int * const from_idx_ref, code * const here_ref, code * const last_ref, unsigned * const len_ref, int * const ret_ref, int flush, struct inflate_state * const state, const unsigned char * const next, unsigned char * const put, unsigned char * const from, static const unsigned short order[19])
{
  z_streamp strm = *strm_ref;
  unsigned int next_idx = *next_idx_ref;
  unsigned int put_idx = *put_idx_ref;
  unsigned have = *have_ref;
  unsigned left = *left_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned out = *out_ref;
  unsigned copy = *copy_ref;
  unsigned int from_idx = *from_idx_ref;
  code here = *here_ref;
  code last = *last_ref;
  unsigned len = *len_ref;
  int ret = *ret_ref;
  switch (state->mode)
  {
    case HEAD:
    {
      helper_helper_inflate_1_11(&strm, &next_idx, &have, &hold, &bits, &len, state, next);
    }

    case DICTID:
    {
      helper_helper_inflate_1_2(&strm, &next_idx, &have, &hold, &bits, state, next);
    }

    case DICT:
    {
      helper_helper_inflate_1_1(&strm, &hold, &bits, state, next, put, next_idx, put_idx, have, left);
    }

    case TYPE:
    {
      if ((flush == 5) || (flush == 6))
      {
        goto inf_leave;
      }
    }

    case TYPEDO:
    {
      helper_helper_inflate_1_13(&strm, &next_idx, &have, &hold, &bits, flush, state, next);
    }

    case STORED:
    {
      helper_helper_inflate_1_6(&strm, &next_idx, &have, &hold, &bits, flush, state, next);
    }

    case COPY_:
    {
      state->mode = COPY;
    }

    case COPY:
    {
      helper_helper_inflate_1_4(&next_idx, &put_idx, &have, &left, &copy, state, next, put);
    }

    case TABLE:
    {
      helper_helper_inflate_1_9(&strm, &next_idx, &have, &hold, &bits, state, next);
    }

    case LENLENS:
    {
      helper_helper_inflate_1_8(&strm, &next_idx, &have, &hold, &bits, &ret, state, next, order);
    }

    case CODELENS:
    {
      helper_helper_inflate_1_15(&strm, &next_idx, &have, &hold, &bits, &copy, &here, &len, &ret, flush, state, next);
    }

    case LEN_:
    {
      state->mode = LEN;
    }

    case LEN:
    {
      helper_helper_inflate_1_14(&strm, &next_idx, &put_idx, &have, &left, &hold, &bits, &here, &last, state, next, put, out);
    }

    case LENEXT:
    {
      helper_helper_inflate_1_5(&next_idx, &have, &hold, &bits, state, next);
    }

    case DIST:
    {
      helper_helper_inflate_1_12(&strm, &next_idx, &have, &hold, &bits, &here, &last, state, next);
    }

    case DISTEXT:
    {
      helper_helper_inflate_1_3(&next_idx, &have, &hold, &bits, state, next);
    }

    case MATCH:
    {
      helper_helper_inflate_1_10(&strm, &put_idx, &left, &copy, &from_idx, state, put, from, out);
    }

    case LIT:
    {
      if (left == 0)
      {
        goto inf_leave;
      }
      put[put_idx] = (unsigned char) state->length;
      put_idx += 1;
      left -= 1;
      state->mode = LEN;
      break;
    }

    case CHECK:
    {
      helper_helper_inflate_1_7(&strm, &next_idx, &have, &hold, &bits, &out, state, next, put, put_idx, left);
    }

    case DONE:
    {
      ret = 1;
      goto inf_leave;
    }

    case BAD:
    {
      ret = -3;
      goto inf_leave;
    }

    case MEM:
    {
      return -4;
    }

    case SYNC:

    default:
    {
      return -2;
    }

  }

  *strm_ref = strm;
  *next_idx_ref = next_idx;
  *put_idx_ref = put_idx;
  *have_ref = have;
  *left_ref = left;
  *hold_ref = hold;
  *bits_ref = bits;
  *out_ref = out;
  *copy_ref = copy;
  *from_idx_ref = from_idx;
  *here_ref = here;
  *last_ref = last;
  *len_ref = len;
  *ret_ref = ret;
}


----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int updatewindow(z_streamp strm, const Bytef *end, unsigned copy)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  unsigned dist;
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->window == 0)
  {
    state->window = (unsigned char *) (*strm->zalloc)(strm->opaque, 1U << state->wbits, sizeof(unsigned char));
    if (state->window == 0)
    {
      return 1;
    }
  }
  if (state->wsize == 0)
  {
    state->wsize = 1U << state->wbits;
    state->wnext = 0;
    state->whave = 0;
  }
  if (copy >= state->wsize)
  {
    memcpy(state->window, end - state->wsize, state->wsize);
    state->wnext = 0;
    state->whave = state->wsize;
  }
  else
  {
    helper_updatewindow_1(&copy, &dist, end, state);
  }
  return 0;
}


----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


int inflateInit_(z_streamp strm, const char *version, int stream_size)
{
  return inflateInit2_(strm, 15, version, stream_size);
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size)
{
  int ret;
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((version == 0) || (version[0] != "1.3-optipng"[0])) || (stream_size != ((int) (sizeof(z_stream)))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  state_idx = (struct inflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(struct inflate_state));
  if ((&state[state_idx]) == 0)
  {
    return -4;
  }
  ;
  strm->state = (struct internal_state *) state;
  state->strm = strm;
  state->window = 0;
  state->mode = HEAD;
  ret = inflateReset2(strm, windowBits);
  if (ret != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state);
    strm->state = 0;
  }
  return ret;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
***/


int inflateCopy(z_streamp dest, z_streamp source)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  struct inflate_state *copy;
  unsigned int copy_idx = 0;
  unsigned char *window;
  unsigned int window_idx = 0;
  unsigned wsize;
  if (inflateStateCheck(source) || (dest == 0))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) source->state_idx;
  copy_idx = (struct inflate_state *) (*source->zalloc)(source->opaque, 1, sizeof(struct inflate_state));
  if ((&copy[copy_idx]) == 0)
  {
    return -4;
  }
  window_idx = 0;
  if (state->window != 0)
  {
    window_idx = (unsigned char *) (*source->zalloc)(source->opaque, 1U << state->wbits, sizeof(unsigned char));
    if ((&window[window_idx]) == 0)
    {
      (*source->zfree)(source->opaque, (voidpf) copy);
      return -4;
    }
  }
  memcpy((voidpf) dest, (voidpf) source, sizeof(z_stream));
  memcpy((voidpf) copy, (voidpf) state, sizeof(struct inflate_state));
  copy->strm = dest;
  if ((state->lencode >= state->codes) && (state->lencode <= ((state->codes + (852 + 592)) - 1)))
  {
    copy->lencode = copy->codes + (state->lencode - state->codes);
    copy->distcode = copy->codes + (state->distcode - state->codes);
  }
  copy->next = copy->codes + (state->next - state->codes);
  if ((&window[window_idx]) != 0)
  {
    wsize = 1U << state->wbits;
    memcpy(window, state->window, wsize);
  }
  copy->window = &window[window_idx];
  dest->state = (struct internal_state *) copy;
  return 0;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflatePrime(z_streamp strm, int bits, int value)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  if (bits == 0)
  {
    return 0;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (bits < 0)
  {
    state->hold = 0;
    state->bits = 0;
    return 0;
  }
  if ((bits > 16) || ((state->bits + ((uInt) bits)) > 32))
  {
    return -2;
  }
  value &= (1L << bits) - 1;
  state->hold += ((unsigned) value) << state->bits;
  state->bits += (uInt) bits;
  return 0;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


long inflateMark(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -(1L << 16);
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  return ((long) (((unsigned long) ((long) state->back)) << 16)) + ((state->mode == COPY) ? (state->length) : ((state->mode == MATCH) ? (state->was - state->length) : (0)));
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflateSyncPoint(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  return (state->mode == STORED) && (state->bits == 0);
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflateUndermine(z_streamp strm, int subvert)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  (void) subvert;
  state->sane = 1;
  return -3;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflateValidate(z_streamp strm, int check)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (check && state->wrap)
  {
    state->wrap |= 4;
  }
  else
    state->wrap &= ~4;
  return 0;
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


unsigned long inflateCodesUsed(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return (unsigned long) (-1);
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  return (unsigned long) (state->next - state->codes);
}


/*** DEPENDENCIES:
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  unsigned long dictid;
  int ret;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if ((state->wrap != 0) && (state->mode != DICT))
  {
    return -2;
  }
  if (state->mode == DICT)
  {
    dictid = adler32(0L, 0, 0);
    dictid = adler32(dictid, dictionary, dictLength);
    if (dictid != state->check)
    {
      return -3;
    }
  }
  ret = updatewindow(strm, dictionary + dictLength, dictLength);
  if (ret)
  {
    state->mode = MEM;
    return -4;
  }
  state->havedict = 1;
  ;
  return 0;
}


/*** DEPENDENCIES:
typedef Byte Bytef
----------------------------
uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}


----------------------------
typedef unsigned int uInt
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
static int updatewindow(z_streamp strm, const Bytef *end, unsigned copy)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  unsigned dist;
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->window == 0)
  {
    state->window = (unsigned char *) (*strm->zalloc)(strm->opaque, 1U << state->wbits, sizeof(unsigned char));
    if (state->window == 0)
    {
      return 1;
    }
  }
  if (state->wsize == 0)
  {
    state->wsize = 1U << state->wbits;
    state->wnext = 0;
    state->whave = 0;
  }
  if (copy >= state->wsize)
  {
    memcpy(state->window, end - state->wsize, state->wsize);
    state->wnext = 0;
    state->whave = state->wsize;
  }
  else
  {
    helper_updatewindow_1(&copy, &dist, end, state);
  }
  return 0;
}


----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef unsigned char Byte
----------------------------
***/


int inflateGetHeader(z_streamp strm, gz_headerp head)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if ((state->wrap & 2) == 0)
  {
    return -2;
  }
  state->head = head;
  head->done = 0;
  return 0;
}


/*** DEPENDENCIES:
typedef struct gz_header_s
{
  int text;
  uLong time;
  int xflags;
  int os;
  Bytef *extra;
  uInt extra_len;
  uInt extra_max;
  Bytef *name;
  uInt name_max;
  Bytef *comment;
  uInt comm_max;
  int hcrc;
  int done;
} gz_header
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef gz_header *gz_headerp
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


int inflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->whave && (dictionary != 0))
  {
    memcpy(dictionary, state->window + state->wnext, state->whave - state->wnext);
    memcpy((dictionary + state->whave) - state->wnext, state->window, state->wnext);
  }
  if (dictLength != 0)
  {
    *dictLength = state->whave;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef Byte Bytef
----------------------------
typedef unsigned int uInt
----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
typedef unsigned char Byte
----------------------------
***/


int inflateSync(z_streamp strm)
{
  unsigned len;
  int flags;
  unsigned long in;
  unsigned long out;
  unsigned char buf[4];
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if ((strm->avail_in == 0) && (state->bits < 8))
  {
    return -5;
  }
  if (state->mode != SYNC)
  {
    helper_inflateSync_1(&len, buf, state);
  }
  len = syncsearch(&state->have, strm->next_in, strm->avail_in);
  strm->avail_in -= len;
  strm->next_in += len;
  strm->total_in += len;
  if (state->have != 4)
  {
    return -3;
  }
  if (state->flags == (-1))
  {
    state->wrap = 0;
  }
  else
    state->wrap &= ~4;
  flags = state->flags;
  in = strm->total_in;
  out = strm->total_out;
  inflateReset(strm);
  strm->total_in = in;
  strm->total_out = out;
  state->flags = flags;
  state->mode = TYPE;
  return 0;
}


/*** DEPENDENCIES:
int inflateReset(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  state->wsize = 0;
  state->whave = 0;
  state->wnext = 0;
  return inflateResetKeep(strm);
}


----------------------------
void helper_inflateSync_1(unsigned * const len_ref, unsigned char buf[4], struct inflate_state * const state)
{
  unsigned len = *len_ref;
  state->mode = SYNC;
  state->hold <<= state->bits & 7;
  state->bits -= state->bits & 7;
  len = 0;
  while (state->bits >= 8)
  {
    buf[len] = (unsigned char) state->hold;
    len += 1;
    state->hold >>= 8;
    state->bits -= 8;
  }

  state->have = 0;
  syncsearch(&state->have, buf, len);
  *len_ref = len;
}


----------------------------
static unsigned syncsearch(unsigned *have, const unsigned char *buf, unsigned len)
{
  unsigned got;
  unsigned next;
  got = *have;
  next = 0;
  while ((next < len) && (got < 4))
  {
    if (((int) buf[next]) == ((got < 2) ? (0) : (0xff)))
    {
      got += 1;
    }
    else
      if (buf[next])
    {
      got = 0;
    }
    else
      got = 4 - got;
    next += 1;
  }

  *have = got;
  return next;
}


----------------------------
static int inflateStateCheck(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (((((&state[state_idx]) == 0) || (state->strm != strm)) || (state->mode < HEAD)) || (state->mode > SYNC))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream
----------------------------
typedef z_stream *z_streamp
----------------------------
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
}
----------------------------
***/


