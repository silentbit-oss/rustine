#include <assert.h>
#include <config.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <version-etc-fsf.c>
#include <version-etc.h>

extern const char version_etc_copyright[];
extern void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors);
extern void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors);
extern void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors);
extern void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...);
extern void emit_bug_reporting_address(void);
const char version_etc_copyright[] = "Copyright %s %d Free Software Foundation, Inc.";

extern const char version_etc_copyright[];
extern void version_etc_arn(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors, size_t n_authors);
extern void version_etc_ar(FILE *stream, const char *command_name, const char *package, const char *version, const char * const *authors);
extern void version_etc_va(FILE *stream, const char *command_name, const char *package, const char *version, va_list authors);
extern void version_etc(FILE *stream, const char *command_name, const char *package, const char *version, ...);
extern void emit_bug_reporting_address(void);
const char version_etc_copyright[] = "Copyright %s %d Free Software Foundation, Inc.";
