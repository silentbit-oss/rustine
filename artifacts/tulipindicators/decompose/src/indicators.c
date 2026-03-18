const char *ti_version(void)
{
  return "0.9.2";
}


/*** DEPENDENCIES:
***/


long int ti_build(void)
{
  return 1746800254;
}


/*** DEPENDENCIES:
***/


int ti_indicator_count(void)
{
  return 104;
}


/*** DEPENDENCIES:
***/


const ti_indicator_info *ti_find_indicator(const char *name)
{
  int imin = 0;
  int imax = ((sizeof(ti_indicators)) / (sizeof(ti_indicator_info))) - 2;
  while (imax >= imin)
  {
    const int i = imin + ((imax - imin) / 2);
    const int c = strcmp(name, ti_indicators[i].name);
    if (c == 0)
    {
      return ti_indicators + i;
    }
    else
      if (c > 0)
    {
      imin = i + 1;
    }
    else
    {
      imax = i - 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
extern ti_indicator_info ti_indicators[]
----------------------------
***/


int ti_stream_get_progress(ti_stream *stream)
{
  return stream->progress;
}


/*** DEPENDENCIES:
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


int ti_stream_run(ti_stream *stream, int size, const double * const *inputs, double * const *outputs)
{
  return ti_indicators[stream->index].stream_run(stream, size, inputs, outputs);
}


/*** DEPENDENCIES:
extern ti_indicator_info ti_indicators[]
----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


ti_indicator_info *ti_stream_get_info(ti_stream *stream)
{
  return ti_indicators + stream->index;
}


/*** DEPENDENCIES:
extern ti_indicator_info ti_indicators[]
----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


void ti_stream_free(ti_stream *stream)
{
  ti_indicators[stream->index].stream_free(stream);
}


/*** DEPENDENCIES:
extern ti_indicator_info ti_indicators[]
----------------------------
struct ti_stream
{
  int index;
  int progress;
}
----------------------------
***/


