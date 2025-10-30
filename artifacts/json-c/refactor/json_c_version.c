#include <config.h>
#include <json_c_version.c>
#include <json_c_version.h>
extern const char *json_c_version(void);
extern int json_c_version_num(void);
const char *json_c_version(void)
{
  return "0.18.99";
}

int json_c_version_num(void)
{
  return ((0 << 16) | (18 << 8)) | 99;
}

extern const char *json_c_version(void);
extern int json_c_version_num(void);
const char *json_c_version(void)
{
  return "0.18.99";
}

int json_c_version_num(void)
{
  return ((0 << 16) | (18 << 8)) | 99;
}

