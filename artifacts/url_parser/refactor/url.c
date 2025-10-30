#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <url.h>
#include <url_char_category.h>
#include <url_char_category_table.h>

struct url_key_value;
typedef struct url_data
{
  char *whole_url;
  const char *protocol;
  const char *userinfo;
  const char *host;
  const char *port;
  const char *path;
  const struct url_key_value *query;
  const char *fragment;
} url_data_t;
url_data_t *url_parse(const char *url);
char *url_get_scheme(const char *url);
inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}

char *url_get_userinfo(const char *url);
char *url_get_hostname(const char *url);
char *url_get_path(const char *url);
const char *url_get_query_value(const url_data_t *url, const char *key);
char *url_get_fragment(const char *url);
inline char *url_get_hash(const char *url)
{
  return url_get_fragment(url);
}

char *url_get_port(const char *url);
void url_free(url_data_t *data);
bool url_is_protocol(const char *str);
bool url_is_ssh(const char *str);
void url_inspect(const char *url);
void url_data_inspect(const url_data_t *data);
enum Category
{
  Scheme = 0x01,
  Unreserved = 0x02,
  GenDelim = 0x04,
  SubDelim = 0x08,
  PCharSlash = 0x10,
  HexDigit = 0x20,
  Query = 0x40,
  Fragment = 0x40,
  Userinfo = 0x80,
  IPv6Char = 0x100
};
static const unsigned short char_cat[256] = {0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x0d8, 0x000, 0x004, 0x0d8, 0x0d0, 0x0d8, 0x0d8, 0x0d8, 0x0d8, 0x0d8, 0x0d9, 0x0d8, 0x0d3, 0x0d3, 0x054, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1d4, 0x0d8, 0x000, 0x0d8, 0x000, 0x044, 0x054, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x004, 0x000, 0x004, 0x000, 0x0d2, 0x000, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x1ff, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x0df, 0x000, 0x000, 0x000, 0x0d2, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000};
static const char *URL_SCHEMES[] = {"aaa", "aaas", "about", "acap", "acct", "adiumxtra", "afp", "afs", "aim", "apt", "attachment", "aw", "beshare", "bitcoin", "bolo", "callto", "cap", "chrome", "crome-extension", "com-evenbrite-attendee", "cid", "coap", "coaps", "content", "crid", "cvs", "data", "dav", "dict", "lna-playsingle", "dln-playcontainer", "dns", "dtn", "dvb", "ed2k", "facetime", "fax", "feed", "file", "finger", "fish", "ftp", "geo", "gg", "git", "gizmoproject", "go", "gopher", "gtalk", "h323", "hcp", "http", "https", "iax", "icap", "icon", "im", "imap", "info", "ipn", "ipp", "irc", "irc6", "ircs", "iris", "iris.beep", "iris.xpc", "iris.xpcs", "iris.lws", "itms", "jabber", "jar", "jms", "keyparc", "lastfm", "ldap", "ldaps", "magnet", "mailserver", "mailto", "maps", "market", "message", "mid", "mms", "modem", "ms-help", "mssettings-power", "msnim", "msrp", "msrps", "mtqp", "mumble", "mupdate", "mvn", "news", "nfs", "ni", "nih", "nntp", "notes", "oid", "paquelocktoken", "pack", "palm", "paparazzi", "pkcs11", "platform", "pop", "pres", "prospero", "proxy", "psyc", "query", "reload", "res", "resource", "rmi", "rsync", "rtmp", "rtsp", "secondlife", "service", "session", "sftp", "sgn", "shttp", "sieve", "sip", "sips", "skype", "smb", "sms", "snews", "snmp", "soap.beep", "soap.beeps", "soldat", "spotify", "ssh", "steam", "svn", "tag", "teamspeak", "tel", "telnet", "tftp", "things", "thismessage", "tn3270", "tip", "tv", "udp", "unreal", "urn", "ut2004", "vemmi", "ventrilo", "videotex", "view-source", "wais", "webcal", "ws", "wss", "wtai", "wyciwyg", "xcon", "xcon-userid", "xfire", "xmlrpc.beep", "xmlrpc.beeps", "xmpp", "xri", "ymsgr", "javascript", "jdbc", "doi"};
char *strdup(const char *str)
{
  const int n = strlen(str) + 1;
  char *dup = (char *) malloc(n);
  if (dup)
  {
    strcpy(dup, str);
  }
  return dup;
}

struct url_key_value
{
  const char *key;
  const char *value;
};
static int unhex(const char *s)
{
  if (((*s) >= '0') && ((*s) <= '9'))
  {
    return (*s) - '0';
  }
  if (((*s) >= 'A') && ((*s) <= 'F'))
  {
    return ((*s) - 'A') + 10;
  }
  if (((*s) >= 'a') && ((*s) <= 'f'))
  {
    return ((*s) - 'a') + 10;
  }
  return -1;
}

static char *decode_percent(char *s)
{
  char *in = s;
  unsigned int in_idx = 0;
  char *out = s;
  unsigned int out_idx = 0;
  while (in[in_idx])
  {
    if (in[in_idx] == '%')
    {
      in_idx += 1;
      const int high = unhex(in);
      if ((high < 0) || (in[in_idx] == '\0'))
      {
        return 0;
      }
      in_idx += 1;
      const int low = unhex(in);
      if ((low < 0) || (in[in_idx] == '\0'))
      {
        return 0;
      }
      out[out_idx] = (char) ((high * 16u) + low);
      out_idx += 1;
      in_idx += 1;
    }
    else
    {
      out[out_idx] = in[in_idx];
      in_idx += 1;
      out_idx += 1;
    }
  }

  out[out_idx] = '\0';
  return s;
}

static char *scan_part(char *start, enum Category category, char delimiter1, char delimiter2)
{
  char *p = start;
  unsigned int p_idx = 0;
  for (;;)
  {
    if (((p[p_idx] == '\0') || (p[p_idx] == delimiter1)) || (p[p_idx] == delimiter2))
    {
      return p;
    }
    if (char_cat[(unsigned char) p[p_idx]] & category)
    {
      p_idx += 1;
    }
    else
    {
      return 0;
    }
  }

}

static char *scan_decimal_number(char *start)
{
  char *p = start;
  unsigned int p_idx = 0;
  while ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
  {
    p_idx += 1;
  }

  return ((&p[p_idx]) != start) ? (p) : (0);
}

static struct url_key_value *parse_query_string(char *begin, char *end)
{
  unsigned elements = 1;
  for (const char *p = begin; (&p[p_idx]) != end; p_idx += 1)
  {
    if ((p[p_idx] == '&') || (p[p_idx] == ';'))
    {
      elements += 1;
    }
  }

  unsigned int p_idx = 0;
  struct url_key_value *kv = calloc(elements + 1, sizeof(struct url_key_value));
  if (!kv)
  {
    return 0;
  }
  char *p = begin;
  unsigned int p_idx = 0;
  for (unsigned element = 0; (element <= elements) && ((&p[p_idx]) < end); element += 1)
  {
    char *key = p;
    char *kv_end = scan_part(p, Query, '&', ';');
    if (!kv_end)
    {
      do
      {
        fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 153, p);
        goto error;
      }
      while (0);
    }
    *kv_end = '\0';
    char *key_end = scan_part(p, Query, '=', '\0');
    const bool has_value = (*key_end) == '=';
    *key_end = '\0';
    kv[element].key = decode_percent(key);
    if (has_value)
    {
      char *value = key_end + 1;
      kv[element].value = decode_percent(value);
    }
    else
    {
      kv[element].value = key_end;
    }
    p_idx = kv_end + 1;
  }

  return kv;
  error:
  free(kv);

  return 0;
}

url_data_t *url_parse(const char *url)
{
  url_data_t *data = (url_data_t *) calloc(1, sizeof(url_data_t));
  if (!data)
  {
    return 0;
  }
  char *p = strdup(url);
  unsigned int p_idx = 0;
  if (!(&p[p_idx]))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 190, p);
      goto error;
    }
    while (0);
  }
  data->whole_url = &p[p_idx];
  const char * const p_end = (&p[p_idx]) + strlen(p);
  char *protocol_end = scan_part(p, Scheme, ':', '\0');
  if ((!protocol_end) || ((*protocol_end) == '\0'))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 197, p);
      goto error;
    }
    while (0);
  }
  *protocol_end = '\0';
  data->protocol = &p[p_idx];
  const bool is_ssh = url_is_ssh(data->protocol);
  p_idx = protocol_end + 1;
  if (((&p[p_idx]) >= p_end) || (p[p_idx] != '/'))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 205, p);
      goto error;
    }
    while (0);
  }
  p_idx += 1;
  if (((&p[p_idx]) >= p_end) || (p[p_idx] != '/'))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 209, p);
      goto error;
    }
    while (0);
  }
  char * const second_slash = p;
  p_idx += 1;
  if ((&p[p_idx]) >= p_end)
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 215, p);
      goto error;
    }
    while (0);
  }
  char *userinfo_end = scan_part(p, Userinfo, '@', '\0');
  if (userinfo_end && ((*userinfo_end) == '@'))
  {
    *userinfo_end = '\0';
    data->userinfo = &p[p_idx];
    p_idx = userinfo_end + 1;
  }
  if ((&p[p_idx]) >= p_end)
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 225, p);
      goto error;
    }
    while (0);
  }
  char *hostname_end = 0;
  unsigned int hostname_end_idx = 0;
  if (p[p_idx] == '[')
  {
    helper_url_parse_3(&p_idx, &hostname_end_idx, data, p, p_end, is_ssh, hostname_end);
  }
  else
  {
    helper_url_parse_2(&p_idx, &hostname_end_idx, data, p, is_ssh, hostname_end);
  }
  memmove(second_slash, second_slash + 1, (&p[p_idx]) - second_slash);
  if (data->userinfo)
  {
    data->userinfo -= 1;
  }
  data->host -= 1;
  if (data->port)
  {
    data->port -= 1;
  }
  p[(-1) + p_idx] = '\0';
  if (is_ssh && (p[p_idx] == ':'))
  {
    p_idx += 1;
  }
  char *path_end = scan_part(p, PCharSlash, '?', '#');
  if (!path_end)
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 295, p);
      goto error;
    }
    while (0);
  }
  const bool has_query = (*path_end) == '?';
  const bool has_fragment = (*path_end) == '#';
  *path_end = '\0';
  data->path = decode_percent(p);
  p_idx = path_end + 1;
  if (has_query)
  {
    helper_url_parse_1(data, p);
  }
  else
    if (has_fragment)
  {
    char *fragment_end = scan_part(p, Fragment, '\0', '\0');
    if (fragment_end)
    {
      data->fragment = decode_percent(p);
    }
    else
    {
      do
      {
        fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 332, p);
        goto error;
      }
      while (0);
    }
  }
  return data;
  error:
  url_free(data);

  return 0;
}

bool url_is_protocol(const char *str)
{
  const unsigned count = (sizeof(URL_SCHEMES)) / (sizeof(URL_SCHEMES[0]));
  for (unsigned i = 0; i < count; i += 1)
  {
    if (0 == strcmp(URL_SCHEMES[i], str))
    {
      return 1;
    }
  }

  return 0;
}

bool url_is_ssh(const char *str)
{
  if ((0 == strcmp(str, "ssh")) || (0 == strcmp(str, "git")))
  {
    return 1;
  }
  return 0;
}

char *url_get_scheme(const char *url)
{
  char *protocol = (char *) malloc(32);
  if (!protocol)
  {
    return 0;
  }
  sscanf(url, "%[^://]", protocol);
  if (url_is_protocol(protocol))
  {
    return protocol;
  }
  free(protocol);
  return 0;
}

char *url_get_userinfo(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->userinfo) ? (strdup(data->userinfo)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

char *url_get_hostname(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->host) ? (strdup(data->host)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

char *url_get_host(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->host) ? (strdup(data->host)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

char *url_get_pathname(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->path) ? (strdup(data->path)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

char *url_get_path(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->path) ? (strdup(data->path)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

const char *url_get_query_value(const url_data_t *url, const char *key)
{
  if (url->query == 0)
  {
    return 0;
  }
  for (const struct url_key_value *kv = url->query; kv->key; kv_idx += 1)
  {
    if (strcmp(kv->key, key) == 0)
    {
      return kv->value;
    }
  }

  unsigned int kv_idx = 0;
  return 0;
}

char *url_get_fragment(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->fragment) ? (strdup(data->fragment)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

char *url_get_port(const char *url)
{
  do
  {
    url_data_t *data = url_parse(url);
    char *out = (data && data->port) ? (strdup(data->port)) : (0);
    url_free(data);
    return out;
  }
  while (0);
}

void url_inspect(const char *url)
{
  url_data_inspect(url_parse(url));
}

void url_data_inspect(const url_data_t *data)
{
  printf("#url =>\n");
  do
  {
    if (data->protocol)
    {
      printf("    .protocol: \"%s\"\n", data->protocol);
    }
    else
      printf("    .protocol: (NULL)\n");
  }
  while (0);
  do
  {
    if (data->host)
    {
      printf("    .host: \"%s\"\n", data->host);
    }
    else
      printf("    .host: (NULL)\n");
  }
  while (0);
  do
  {
    if (data->userinfo)
    {
      printf("    .userinfo: \"%s\"\n", data->userinfo);
    }
    else
      printf("    .userinfo: (NULL)\n");
  }
  while (0);
  do
  {
    if (data->host)
    {
      printf("    .host: \"%s\"\n", data->host);
    }
    else
      printf("    .host: (NULL)\n");
  }
  while (0);
  do
  {
    if (data->port)
    {
      printf("    .port: \"%s\"\n", data->port);
    }
    else
      printf("    .port: (NULL)\n");
  }
  while (0);
  do
  {
    if (data->path)
    {
      printf("    .path: \"%s\"\n", data->path);
    }
    else
      printf("    .path: (NULL)\n");
  }
  while (0);
  if (data->query)
  {
    for (unsigned nr = 0; data->query[nr].key; nr += 1)
    {
      printf("    .query[%u]: \"%s\" -> ", nr, data->query[nr].key);
      if (data->query[nr].value)
      {
        printf("\"%s\"\n", data->query[nr].value);
      }
      else
        printf("(NULL)\n");
    }

  }
  do
  {
    if (data->fragment)
    {
      printf("    .fragment: \"%s\"\n", data->fragment);
    }
    else
      printf("    .fragment: (NULL)\n");
  }
  while (0);
}

void url_free(url_data_t *data)
{
  if (!data)
  {
    return;
  }
  free(data->whole_url);
  free((void *) data->query);
  free(data);
}

inline extern char *url_get_protocol(const char *url);
inline extern char *url_get_hash(const char *url);
void helper_url_parse_1(url_data_t * const data, char * const p)
{
  char *query_end = scan_part(p, Query, '#', '\0');
  if (query_end)
  {
    const bool has_fragment = (*query_end) == '#';
    *query_end = '\0';
    data->query = parse_query_string(p, query_end);
    if (has_fragment)
    {
      char *fragment_end = scan_part(query_end + 1, Fragment, '\0', '\0');
      if (fragment_end)
      {
        data->fragment = decode_percent(query_end + 1);
      }
      else
      {
        do
        {
          fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 319, p);
          goto error;
        }
        while (0);
      }
    }
  }
  else
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 323, p);
      goto error;
    }
    while (0);
  }
}

void helper_url_parse_2(unsigned int * const p_idx_ref, unsigned int * const hostname_end_idx_ref, url_data_t * const data, char * const p, const bool is_ssh, char * const hostname_end)
{
  unsigned int p_idx = *p_idx_ref;
  unsigned int hostname_end_idx = *hostname_end_idx_ref;
  hostname_end_idx = scan_part(p, Unreserved | SubDelim, ':', '/');
  if (!(&hostname_end[hostname_end_idx]))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 255, p);
      goto error;
    }
    while (0);
  }
  data->host = &p[p_idx];
  if ((!is_ssh) && (hostname_end[hostname_end_idx] == ':'))
  {
    hostname_end[hostname_end_idx] = '\0';
    char *port_end = scan_decimal_number((&hostname_end[hostname_end_idx]) + 1);
    if (port_end)
    {
      data->port = (&hostname_end[hostname_end_idx]) + 1;
      p_idx = port_end;
    }
    else
    {
      do
      {
        fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 267, p);
        goto error;
      }
      while (0);
    }
  }
  else
  {
    p_idx = &hostname_end[hostname_end_idx];
  }
  *p_idx_ref = p_idx;
  *hostname_end_idx_ref = hostname_end_idx;
}

void helper_url_parse_3(unsigned int * const p_idx_ref, unsigned int * const hostname_end_idx_ref, url_data_t * const data, char * const p, const char * const p_end, const bool is_ssh, char * const hostname_end)
{
  unsigned int p_idx = *p_idx_ref;
  unsigned int hostname_end_idx = *hostname_end_idx_ref;
  p_idx += 1;
  hostname_end_idx = scan_part(p, IPv6Char, ']', '\0');
  if (!(&hostname_end[hostname_end_idx]))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 234, p);
      goto error;
    }
    while (0);
  }
  hostname_end[hostname_end_idx] = '\0';
  data->host = &p[p_idx];
  hostname_end_idx += 1;
  if ((((&hostname_end[hostname_end_idx]) < p_end) && (!is_ssh)) && (hostname_end[hostname_end_idx] == ':'))
  {
    char *port_end = scan_decimal_number((&hostname_end[hostname_end_idx]) + 1);
    if (port_end)
    {
      data->port = (&hostname_end[hostname_end_idx]) + 1;
      p_idx = port_end;
    }
    else
    {
      do
      {
        fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/home/enumclass/Documents/C2RustTranslation/bkp/url_parser/url.c", 247, p);
        goto error;
      }
      while (0);
    }
  }
  else
  {
    p_idx = &hostname_end[hostname_end_idx];
  }
  *p_idx_ref = p_idx;
  *hostname_end_idx_ref = hostname_end_idx;
}

