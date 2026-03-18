typedef struct ti_indicator_info
{
  const char *name;
  const char *full_name;
  ti_indicator_start_function start;
  ti_indicator_function indicator;
  ti_indicator_function indicator_ref;
  int type;
  int inputs;
  int options;
  int outputs;
  const char *input_names[16];
  const char *option_names[16];
  const char *output_names[16];
  ti_indicator_stream_new stream_new;
  ti_indicator_stream_run stream_run;
  ti_indicator_stream_free stream_free;
} ti_indicator_info
/*** DEPENDENCIES:
typedef int (*ti_indicator_start_function)(const double *options)
----------------------------
typedef int (*ti_indicator_stream_run)(ti_stream *stream, int size, const double * const *inputs, double * const *outputs)
----------------------------
typedef int (*ti_indicator_function)(int size, const double * const *inputs, const double *options, double * const *outputs)
----------------------------
typedef void (*ti_indicator_stream_free)(ti_stream *stream)
----------------------------
typedef int (*ti_indicator_stream_new)(const double *options, ti_stream **stream)
----------------------------
***/


