static const char *csv_errors[] = {"success", "error parsing data while strict checking enabled", "memory exhausted while increasing buffer size", "data size too large", "invalid status code"}
/*** DEPENDENCIES:
***/


int event_idx
/*** DEPENDENCIES:
***/


size_t row
/*** DEPENDENCIES:
***/


size_t col
/*** DEPENDENCIES:
***/


struct event *event_ptr
/*** DEPENDENCIES:
struct event
{
  int event_type;
  int retval;
  size_t size;
  char *data;
}
----------------------------
***/


