#include <assert.h>
#include <close-stream.h>
#include <closeout.c>
#include <closeout.h>
#include <config.h>
#include <errno.h>
#include <error.h>
#include <exitfail.h>
#include <gettext.h>
#include <libintl.h>
#include <quotearg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void close_stdout_set_file_name(const char *file);
void close_stdout_set_ignore_EPIPE(bool ignore);
void close_stdout(void);
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

int close_stream(FILE *stream);
extern volatile int exit_failure;
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
};
enum quoting_flags
{
  QA_ELIDE_NULL_BYTES = 0x01,
  QA_ELIDE_OUTER_QUOTES = 0x02,
  QA_SPLIT_TRIGRAPHS = 0x04
};
extern const char * const quoting_style_args[];
extern const enum quoting_style quoting_style_vals[];
struct quoting_options;
struct quoting_options *clone_quoting_options(struct quoting_options *o);
enum quoting_style get_quoting_style(const struct quoting_options *o);
void set_quoting_style(struct quoting_options *o, enum quoting_style s);
int set_char_quoting(struct quoting_options *o, char c, int i);
int set_quoting_flags(struct quoting_options *o, int i);
void set_custom_quoting(struct quoting_options *o, const char *left_quote, const char *right_quote);
size_t quotearg_buffer(char *buffer, size_t buffersize, const char *arg, size_t argsize, const struct quoting_options *o);
char *quotearg_alloc(const char *arg, size_t argsize, const struct quoting_options *o);
char *quotearg_alloc_mem(const char *arg, size_t argsize, size_t *size, const struct quoting_options *o);
char *quotearg_n(int n, const char *arg);
char *quotearg(const char *arg);
char *quotearg_n_mem(int n, const char *arg, size_t argsize);
char *quotearg_mem(const char *arg, size_t argsize);
char *quotearg_n_style(int n, enum quoting_style s, const char *arg);
char *quotearg_n_style_mem(int n, enum quoting_style s, const char *arg, size_t argsize);
char *quotearg_style(enum quoting_style s, const char *arg);
char *quotearg_style_mem(enum quoting_style s, const char *arg, size_t argsize);
char *quotearg_char(const char *arg, char ch);
char *quotearg_char_mem(const char *arg, size_t argsize, char ch);
char *quotearg_colon(const char *arg);
char *quotearg_colon_mem(const char *arg, size_t argsize);
char *quotearg_n_style_colon(int n, enum quoting_style s, const char *arg);
char *quotearg_n_custom(int n, const char *left_quote, const char *right_quote, const char *arg);
char *quotearg_n_custom_mem(int n, const char *left_quote, const char *right_quote, const char *arg, size_t argsize);
char *quotearg_custom(const char *left_quote, const char *right_quote, const char *arg);
char *quotearg_custom_mem(const char *left_quote, const char *right_quote, const char *arg, size_t argsize);
void quotearg_free(void);
enum 
{
  SANITIZE_ADDRESS = 0
};
static const char *file_name;
void close_stdout_set_file_name(const char *file)
{
  file_name = file;
}

static bool ignore_EPIPE;
void close_stdout_set_ignore_EPIPE(bool ignore)
{
  ignore_EPIPE = ignore;
}

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


void close_stdout_set_file_name(const char *file);
void close_stdout_set_ignore_EPIPE(bool ignore);
void close_stdout(void);
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

int close_stream(FILE *stream);
extern volatile int exit_failure;
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
};
enum quoting_flags
{
  QA_ELIDE_NULL_BYTES = 0x01,
  QA_ELIDE_OUTER_QUOTES = 0x02,
  QA_SPLIT_TRIGRAPHS = 0x04
};
extern const char * const quoting_style_args[];
extern const enum quoting_style quoting_style_vals[];
struct quoting_options;
struct quoting_options *clone_quoting_options(struct quoting_options *o);
enum quoting_style get_quoting_style(const struct quoting_options *o);
void set_quoting_style(struct quoting_options *o, enum quoting_style s);
int set_char_quoting(struct quoting_options *o, char c, int i);
int set_quoting_flags(struct quoting_options *o, int i);
void set_custom_quoting(struct quoting_options *o, const char *left_quote, const char *right_quote);
size_t quotearg_buffer(char *buffer, size_t buffersize, const char *arg, size_t argsize, const struct quoting_options *o);
char *quotearg_alloc(const char *arg, size_t argsize, const struct quoting_options *o);
char *quotearg_alloc_mem(const char *arg, size_t argsize, size_t *size, const struct quoting_options *o);
char *quotearg_n(int n, const char *arg);
char *quotearg(const char *arg);
char *quotearg_n_mem(int n, const char *arg, size_t argsize);
char *quotearg_mem(const char *arg, size_t argsize);
char *quotearg_n_style(int n, enum quoting_style s, const char *arg);
char *quotearg_n_style_mem(int n, enum quoting_style s, const char *arg, size_t argsize);
char *quotearg_style(enum quoting_style s, const char *arg);
char *quotearg_style_mem(enum quoting_style s, const char *arg, size_t argsize);
char *quotearg_char(const char *arg, char ch);
char *quotearg_char_mem(const char *arg, size_t argsize, char ch);
char *quotearg_colon(const char *arg);
char *quotearg_colon_mem(const char *arg, size_t argsize);
char *quotearg_n_style_colon(int n, enum quoting_style s, const char *arg);
char *quotearg_n_custom(int n, const char *left_quote, const char *right_quote, const char *arg);
char *quotearg_n_custom_mem(int n, const char *left_quote, const char *right_quote, const char *arg, size_t argsize);
char *quotearg_custom(const char *left_quote, const char *right_quote, const char *arg);
char *quotearg_custom_mem(const char *left_quote, const char *right_quote, const char *arg, size_t argsize);
void quotearg_free(void);
enum 
{
  SANITIZE_ADDRESS = 0
};
static const char *file_name;
void close_stdout_set_file_name(const char *file)
{
  file_name = file;
}

static bool ignore_EPIPE;
void close_stdout_set_ignore_EPIPE(bool ignore)
{
  ignore_EPIPE = ignore;
}

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

