#include <assert.h>
#include <config.h>
#include <gettext.h>
#include <libintl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unlocked-io.h>
#include <version-etc.c>
#include <version-etc.h>

extern const char version_etc_copyright[];
extern void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors);
extern void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors);
extern void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors);
extern void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...);
extern void emit_bug_reporting_address(void);
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

enum 
{
  COPYRIGHT_YEAR = 2024
};
void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors)
{
  if (command_name)
  {
    fprintf(stream, "%s (%s) %s\n", command_name, package, version);
  }
  else
    fprintf(stream, "%s %s\n", package, version);
  fprintf(stream, version_etc_copyright, gettext("(C)"), COPYRIGHT_YEAR);
  fputs_unlocked("\n", stream);
  fprintf(stream, gettext("License GPLv3+: GNU GPL version 3 or later <%s>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n"), "https://gnu.org/licenses/gpl.html");
  fputs_unlocked("\n", stream);
  switch (n_authors)
  {
    case 0:
    {
      break;
    }

    case 1:
    {
      fprintf(stream, gettext("Written by %s.\n"), authors[0]);
      break;
    }

    case 2:
    {
      fprintf(stream, gettext("Written by %s and %s.\n"), authors[0], authors[1]);
      break;
    }

    case 3:
    {
      fprintf(stream, gettext("Written by %s, %s, and %s.\n"), authors[0], authors[1], authors[2]);
      break;
    }

    case 4:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\nand %s.\n"), authors[0], authors[1], authors[2], authors[3]);
      break;
    }

    case 5:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4]);
      break;
    }

    case 6:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5]);
      break;
    }

    case 7:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6]);
      break;
    }

    case 8:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, %s,\nand %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6], authors[7]);
      break;
    }

    case 9:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6], authors[7], authors[8]);
      break;
    }

    default:
    {
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, %s, and others.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6], authors[7], authors[8]);
      break;
    }

  }

}

void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors)
{
  size_t n_authors;
  for (n_authors = 0; authors[n_authors]; n_authors += 1)
  {
    ;
  }

  version_etc_arn(stream, command_name, package, version, authors, n_authors);
}

void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors)
{
  size_t n_authors;
  const char *authtab[10];
  for (n_authors = 0; (n_authors < 10) && ((authtab[n_authors] = __builtin_va_arg(authors)) != 0); n_authors += 1)
  {
    ;
  }

  version_etc_arn(stream, command_name, package, version, authtab, n_authors);
}

void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...)
{
  va_list authors;
  __builtin_va_start(authors);
  version_etc_va(stream, command_name, package, version, authors);
  ;
}

void emit_bug_reporting_address(void)
{
  fputs_unlocked("\n", stdout);
  printf(gettext("Report bugs to: %s\n"), "bug-coreutils@gnu.org");
  printf(gettext("%s home page: <%s>\n"), "GNU coreutils", "https://www.gnu.org/software/coreutils/");
  printf(gettext("General help using GNU software: <%s>\n"), "https://www.gnu.org/gethelp/");
}


extern const char version_etc_copyright[];
extern void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors);
extern void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors);
extern void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors);
extern void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...);
extern void emit_bug_reporting_address(void);
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

enum 
{
  COPYRIGHT_YEAR = 2024
};
void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors)
{
  if (command_name)
  {
    fprintf(stream, "%s (%s) %s\n", command_name, package, version);
  }
  else
    fprintf(stream, "%s %s\n", package, version);
  fprintf(stream, version_etc_copyright, gettext("(C)"), COPYRIGHT_YEAR);
  fputs_unlocked("\n", stream);
  fprintf(stream, gettext("License GPLv3+: GNU GPL version 3 or later <%s>.\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n"), "https://gnu.org/licenses/gpl.html");
  fputs_unlocked("\n", stream);
  switch (n_authors)
  {
    case 0:
      break;

    case 1:
      fprintf(stream, gettext("Written by %s.\n"), authors[0]);
      break;

    case 2:
      fprintf(stream, gettext("Written by %s and %s.\n"), authors[0], authors[1]);
      break;

    case 3:
      fprintf(stream, gettext("Written by %s, %s, and %s.\n"), authors[0], authors[1], authors[2]);
      break;

    case 4:
      fprintf(stream, gettext("Written by %s, %s, %s,\nand %s.\n"), authors[0], authors[1], authors[2], authors[3]);
      break;

    case 5:
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4]);
      break;

    case 6:
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5]);
      break;

    case 7:
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6]);
      break;

    case 8:
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, %s,\nand %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6], authors[7]);
      break;

    case 9:
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, and %s.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6], authors[7], authors[8]);
      break;

    default:
      fprintf(stream, gettext("Written by %s, %s, %s,\n%s, %s, %s, %s,\n%s, %s, and others.\n"), authors[0], authors[1], authors[2], authors[3], authors[4], authors[5], authors[6], authors[7], authors[8]);
      break;

  }

}

void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors)
{
  size_t n_authors;
  for (n_authors = 0; authors[n_authors]; n_authors += 1)
  {
    ;
  }

  version_etc_arn(stream, command_name, package, version, authors, n_authors);
}

void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors)
{
  size_t n_authors;
  const char *authtab[10];
  for (n_authors = 0; (n_authors < 10) && ((authtab[n_authors] = __builtin_va_arg(authors)) != 0); n_authors += 1)
  {
    ;
  }

  version_etc_arn(stream, command_name, package, version, authtab, n_authors);
}

void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...)
{
  va_list authors;
  __builtin_va_start(authors);
  version_etc_va(stream, command_name, package, version, authors);
  ;
}

void emit_bug_reporting_address(void)
{
  fputs_unlocked("\n", stdout);
  printf(gettext("Report bugs to: %s\n"), "bug-coreutils@gnu.org");
  printf(gettext("%s home page: <%s>\n"), "GNU coreutils", "https://www.gnu.org/software/coreutils/");
  printf(gettext("General help using GNU software: <%s>\n"), "https://www.gnu.org/gethelp/");
}

