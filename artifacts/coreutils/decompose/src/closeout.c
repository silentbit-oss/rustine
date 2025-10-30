static const char *pgettext_aux(const char *domain, const char *msg_ctxt_id, const char *msgid, int category)
{
  const char *translation = dcgettext(domain, msg_ctxt_id, category);
  if (translation == msg_ctxt_id)
  {
    return msgid;
  }
  else
    return translation;
}


/*** DEPENDENCIES:
***/


static const char *npgettext_aux(const char *domain, const char *msg_ctxt_id, const char *msgid, const char *msgid_plural, unsigned long int n, int category)
{
  const char *translation = dcngettext(domain, msg_ctxt_id, msgid_plural, n, category);
  if ((translation == msg_ctxt_id) || (translation == msgid_plural))
  {
    return (n == 1) ? (msgid) : (msgid_plural);
  }
  else
    return translation;
}


/*** DEPENDENCIES:
***/


static const char *dcpgettext_expr(const char *domain, const char *msgctxt, const char *msgid, int category)
{
  size_t msgctxt_len = strlen(msgctxt) + 1;
  size_t msgid_len = strlen(msgid) + 1;
  const char *translation;
  unsigned int translation_idx = 0;
  char buf[1024];
  char *msg_ctxt_id = ((msgctxt_len + msgid_len) <= (sizeof(buf))) ? (buf) : ((char *) malloc(msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)
  {
    int found_translation;
    memcpy(msg_ctxt_id, msgctxt, msgctxt_len - 1);
    msg_ctxt_id[msgctxt_len - 1] = '\004';
    memcpy(msg_ctxt_id + msgctxt_len, msgid, msgid_len);
    translation_idx = dcgettext(domain, msg_ctxt_id, category);
    found_translation = (&translation[translation_idx]) != msg_ctxt_id;
    if (msg_ctxt_id != buf)
    {
      free(msg_ctxt_id);
    }
    if (found_translation)
    {
      return translation;
    }
  }
  return msgid;
}


/*** DEPENDENCIES:
***/


static const char *dcnpgettext_expr(const char *domain, const char *msgctxt, const char *msgid, const char *msgid_plural, unsigned long int n, int category)
{
  size_t msgctxt_len = strlen(msgctxt) + 1;
  size_t msgid_len = strlen(msgid) + 1;
  const char *translation;
  unsigned int translation_idx = 0;
  char buf[1024];
  char *msg_ctxt_id = ((msgctxt_len + msgid_len) <= (sizeof(buf))) ? (buf) : ((char *) malloc(msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)
  {
    int found_translation;
    memcpy(msg_ctxt_id, msgctxt, msgctxt_len - 1);
    msg_ctxt_id[msgctxt_len - 1] = '\004';
    memcpy(msg_ctxt_id + msgctxt_len, msgid, msgid_len);
    translation_idx = dcngettext(domain, msg_ctxt_id, msgid_plural, n, category);
    found_translation = !(((&translation[translation_idx]) == msg_ctxt_id) || ((&translation[translation_idx]) == msgid_plural));
    if (msg_ctxt_id != buf)
    {
      free(msg_ctxt_id);
    }
    if (found_translation)
    {
      return translation;
    }
  }
  return (n == 1) ? (msgid) : (msgid_plural);
}


/*** DEPENDENCIES:
***/


void close_stdout_set_file_name(const char *file)
{
  file_name = file;
}


/*** DEPENDENCIES:
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
***/


void close_stdout_set_ignore_EPIPE(bool ignore)
{
  ignore_EPIPE = ignore;
}


/*** DEPENDENCIES:
static bool ignore_EPIPE
----------------------------
***/


void close_stdout(void)
{
  if ((close_stream(stdout) != 0) && (!(ignore_EPIPE && (errno == EPIPE))))
  {
    const char *write_error = gettext("write error");
    if (file_name)
    {
      error(0, errno, "%s: %s", quotearg_colon(file_name), write_error);
    }
    else
      error(0, errno, "%s", write_error);
    _exit(exit_failure);
  }
  if ((!SANITIZE_ADDRESS) && (close_stream(stderr) != 0))
  {
    _exit(exit_failure);
  }
}


/*** DEPENDENCIES:
static bool ignore_EPIPE
----------------------------
extern volatile int exit_failure
----------------------------
int close_stream(FILE *stream)
{
  const bool some_pending = __fpending(stream) != 0;
  const bool prev_fail = ferror_unlocked(stream) != 0;
  const bool fclose_fail = fclose(stream) != 0;
  if (prev_fail || (fclose_fail && (some_pending || (errno != EBADF))))
  {
    if (!fclose_fail)
    {
      errno = 0;
    }
    return EOF;
  }
  return 0;
}


----------------------------
char *quotearg_colon(const char *arg)
{
  return quotearg_char(arg, ':');
}


----------------------------
struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
}
----------------------------
***/


