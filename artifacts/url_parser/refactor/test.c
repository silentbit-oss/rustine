#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <url.h>

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

