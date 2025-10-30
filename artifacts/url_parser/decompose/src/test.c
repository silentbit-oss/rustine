inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}


/*** DEPENDENCIES:
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


----------------------------
***/


inline char *url_get_hash(const char *url)
{
  return url_get_fragment(url);
}


/*** DEPENDENCIES:
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


----------------------------
***/


int main(void)
{
  char *gh_url = "git://git@github.com:jwerle/url.h.git";
  char *url = "http://user:pass@subdomain.host.com:8080/p/%C3%A5/t/h?qu%C3%ABry=strin%C4%9F&foo=bar=yuk&key%23%26%3D=%25&lol#h%C3%a6sh";
  url_data_t *parsed = url_parse(url);
  url_data_t *gh_parsed = url_parse(gh_url);
  assert(parsed);
  assert(gh_parsed);
  url_data_inspect(parsed);
  url_data_inspect(gh_parsed);
  assert(parsed->whole_url);
  assert(parsed->protocol);
  assert(parsed->userinfo);
  assert(parsed->host);
  assert(parsed->port);
  assert(parsed->path);
  assert(parsed->query);
  assert(parsed->fragment);
  assert(gh_parsed->whole_url);
  assert(gh_parsed->protocol);
  assert(gh_parsed->userinfo);
  assert(gh_parsed->host);
  assert(gh_parsed->path);
  assert(url_is_protocol("http"));
  assert(url_is_protocol("https"));
  assert(url_is_protocol("git"));
  assert(url_is_protocol("ssh"));
  assert(url_is_protocol("sftp"));
  assert(url_is_protocol("ftp"));
  assert(url_is_protocol("javascript"));
  do
  {
    char *s = url_get_protocol(url);
    assert(s);
    assert(strcmp("http", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_userinfo(url);
    assert(s);
    assert(strcmp("user:pass", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_hostname(url);
    assert(s);
    assert(strcmp("subdomain.host.com", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_path(url);
    assert(s);
    assert(strcmp("/p/\xc3\xa5/t/h", s) == 0);
    free(s);
  }
  while (0);
  assert(strcmp("strin\xc4\x9f", url_get_query_value(parsed, "qu\xc3\xabry")) == 0);
  assert(strcmp("bar=yuk", url_get_query_value(parsed, "foo")) == 0);
  assert(strcmp("%", url_get_query_value(parsed, "key#&=")) == 0);
  assert(strcmp("", url_get_query_value(parsed, "lol")) == 0);
  do
  {
    char *s = url_get_fragment(url);
    assert(s);
    assert(strcmp("hæsh", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_port(url);
    assert(s);
    assert(strcmp("8080", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_protocol(gh_url);
    assert(s);
    assert(strcmp("git", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_hostname(gh_url);
    assert(s);
    assert(strcmp("github.com", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_userinfo(gh_url);
    assert(s);
    assert(strcmp("git", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_path(gh_url);
    assert(s);
    assert(strcmp("jwerle/url.h.git", s) == 0);
    free(s);
  }
  while (0);
  url_free(parsed);
  url_free(gh_parsed);
  return 0;
}


/*** DEPENDENCIES:
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


----------------------------
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
} url_data_t
----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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
    helper_url_parse_2(&p_idx, &hostname_end_idx, data, p, p_end, is_ssh, hostname_end);
  }
  else
  {
    helper_url_parse_1(&p_idx, &hostname_end_idx, data, p, is_ssh, hostname_end);
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}


----------------------------
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


----------------------------
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


----------------------------
***/


inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}


/*** DEPENDENCIES:
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


----------------------------
***/


inline char *url_get_hash(const char *url)
{
  return url_get_fragment(url);
}


/*** DEPENDENCIES:
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


----------------------------
***/


int main(void)
{
  char *gh_url = "git://git@github.com:jwerle/url.h.git";
  char *url = "http://user:pass@subdomain.host.com:8080/p/%C3%A5/t/h?qu%C3%ABry=strin%C4%9F&foo=bar=yuk&key%23%26%3D=%25&lol#h%C3%a6sh";
  url_data_t *parsed = url_parse(url);
  url_data_t *gh_parsed = url_parse(gh_url);
  assert(parsed);
  assert(gh_parsed);
  url_data_inspect(parsed);
  url_data_inspect(gh_parsed);
  assert(parsed->whole_url);
  assert(parsed->protocol);
  assert(parsed->userinfo);
  assert(parsed->host);
  assert(parsed->port);
  assert(parsed->path);
  assert(parsed->query);
  assert(parsed->fragment);
  assert(gh_parsed->whole_url);
  assert(gh_parsed->protocol);
  assert(gh_parsed->userinfo);
  assert(gh_parsed->host);
  assert(gh_parsed->path);
  assert(url_is_protocol("http"));
  assert(url_is_protocol("https"));
  assert(url_is_protocol("git"));
  assert(url_is_protocol("ssh"));
  assert(url_is_protocol("sftp"));
  assert(url_is_protocol("ftp"));
  assert(url_is_protocol("javascript"));
  do
  {
    char *s = url_get_protocol(url);
    assert(s);
    assert(strcmp("http", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_userinfo(url);
    assert(s);
    assert(strcmp("user:pass", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_hostname(url);
    assert(s);
    assert(strcmp("subdomain.host.com", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_path(url);
    assert(s);
    assert(strcmp("/p/\xc3\xa5/t/h", s) == 0);
    free(s);
  }
  while (0);
  assert(strcmp("strin\xc4\x9f", url_get_query_value(parsed, "qu\xc3\xabry")) == 0);
  assert(strcmp("bar=yuk", url_get_query_value(parsed, "foo")) == 0);
  assert(strcmp("%", url_get_query_value(parsed, "key#&=")) == 0);
  assert(strcmp("", url_get_query_value(parsed, "lol")) == 0);
  do
  {
    char *s = url_get_fragment(url);
    assert(s);
    assert(strcmp("hæsh", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_port(url);
    assert(s);
    assert(strcmp("8080", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_protocol(gh_url);
    assert(s);
    assert(strcmp("git", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_hostname(gh_url);
    assert(s);
    assert(strcmp("github.com", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_userinfo(gh_url);
    assert(s);
    assert(strcmp("git", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_path(gh_url);
    assert(s);
    assert(strcmp("jwerle/url.h.git", s) == 0);
    free(s);
  }
  while (0);
  url_free(parsed);
  url_free(gh_parsed);
  return 0;
}


/*** DEPENDENCIES:
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


----------------------------
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
} url_data_t
----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 190, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 197, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 205, p);
      goto error;
    }
    while (0);
  }
  p_idx += 1;
  if (((&p[p_idx]) >= p_end) || (p[p_idx] != '/'))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 209, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 215, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 225, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 295, p);
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
        fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 332, p);
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


----------------------------
***/


inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}


/*** DEPENDENCIES:
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


----------------------------
***/


inline char *url_get_hash(const char *url)
{
  return url_get_fragment(url);
}


/*** DEPENDENCIES:
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


----------------------------
***/


int main(void)
{
  char *gh_url = "git://git@github.com:jwerle/url.h.git";
  char *url = "http://user:pass@subdomain.host.com:8080/p/%C3%A5/t/h?qu%C3%ABry=strin%C4%9F&foo=bar=yuk&key%23%26%3D=%25&lol#h%C3%a6sh";
  url_data_t *parsed = url_parse(url);
  url_data_t *gh_parsed = url_parse(gh_url);
  assert(parsed);
  assert(gh_parsed);
  url_data_inspect(parsed);
  url_data_inspect(gh_parsed);
  assert(parsed->whole_url);
  assert(parsed->protocol);
  assert(parsed->userinfo);
  assert(parsed->host);
  assert(parsed->port);
  assert(parsed->path);
  assert(parsed->query);
  assert(parsed->fragment);
  assert(gh_parsed->whole_url);
  assert(gh_parsed->protocol);
  assert(gh_parsed->userinfo);
  assert(gh_parsed->host);
  assert(gh_parsed->path);
  assert(url_is_protocol("http"));
  assert(url_is_protocol("https"));
  assert(url_is_protocol("git"));
  assert(url_is_protocol("ssh"));
  assert(url_is_protocol("sftp"));
  assert(url_is_protocol("ftp"));
  assert(url_is_protocol("javascript"));
  do
  {
    char *s = url_get_protocol(url);
    assert(s);
    assert(strcmp("http", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_userinfo(url);
    assert(s);
    assert(strcmp("user:pass", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_hostname(url);
    assert(s);
    assert(strcmp("subdomain.host.com", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_path(url);
    assert(s);
    assert(strcmp("/p/\xc3\xa5/t/h", s) == 0);
    free(s);
  }
  while (0);
  assert(strcmp("strin\xc4\x9f", url_get_query_value(parsed, "qu\xc3\xabry")) == 0);
  assert(strcmp("bar=yuk", url_get_query_value(parsed, "foo")) == 0);
  assert(strcmp("%", url_get_query_value(parsed, "key#&=")) == 0);
  assert(strcmp("", url_get_query_value(parsed, "lol")) == 0);
  do
  {
    char *s = url_get_fragment(url);
    assert(s);
    assert(strcmp("hæsh", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_port(url);
    assert(s);
    assert(strcmp("8080", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_protocol(gh_url);
    assert(s);
    assert(strcmp("git", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_hostname(gh_url);
    assert(s);
    assert(strcmp("github.com", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_userinfo(gh_url);
    assert(s);
    assert(strcmp("git", s) == 0);
    free(s);
  }
  while (0);
  do
  {
    char *s = url_get_path(gh_url);
    assert(s);
    assert(strcmp("jwerle/url.h.git", s) == 0);
    free(s);
  }
  while (0);
  url_free(parsed);
  url_free(gh_parsed);
  return 0;
}


/*** DEPENDENCIES:
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


----------------------------
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
} url_data_t
----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
inline char *url_get_protocol(const char *url)
{
  return url_get_scheme(url);
}


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 190, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 197, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 205, p);
      goto error;
    }
    while (0);
  }
  p_idx += 1;
  if (((&p[p_idx]) >= p_end) || (p[p_idx] != '/'))
  {
    do
    {
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 209, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 215, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 225, p);
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
      fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 295, p);
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
        fprintf(stderr, "ERROR %s Line %u! p=«%s»\n", "/c2rust_final/subjects/url_parser/url.c", 332, p);
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


----------------------------
***/


