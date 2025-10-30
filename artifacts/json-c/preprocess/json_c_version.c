# 0 "/app/subjects/json-c/json_c_version.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/json-c/json_c_version.c"






# 1 "/app/subjects/json-c/build/config.h" 1
# 8 "/app/subjects/json-c/json_c_version.c" 2

# 1 "/app/subjects/json-c/json_c_version.h" 1
# 38 "/app/subjects/json-c/json_c_version.h"
extern const char *json_c_version(void);
# 49 "/app/subjects/json-c/json_c_version.h"
extern int json_c_version_num(void);
# 10 "/app/subjects/json-c/json_c_version.c" 2

const char *json_c_version(void)
{
 return "0.18.99";
}

int json_c_version_num(void)
{
 return ((0 << 16) | (18 << 8) | 99);
}
