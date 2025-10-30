// element in merge of:  options_table_entry,options,options_entry
struct options_table_entry
{
  const char *name;
  enum options_table_type type;
  enum options_table_scope scope;
  u_int minimum;
  u_int maximum;
  const char **choices;
  const char *default_str;
  long long default_num;
  const char *separator;
  const char *style;
}
/*** DEPENDENCIES:
enum options_table_type
{
  OPTIONS_TABLE_STRING,
  OPTIONS_TABLE_NUMBER,
  OPTIONS_TABLE_KEY,
  OPTIONS_TABLE_COLOUR,
  OPTIONS_TABLE_ATTRIBUTES,
  OPTIONS_TABLE_FLAG,
  OPTIONS_TABLE_CHOICE,
  OPTIONS_TABLE_STYLE,
  OPTIONS_TABLE_ARRAY
}
----------------------------
enum options_table_scope
{
  OPTIONS_TABLE_NONE,
  OPTIONS_TABLE_SERVER,
  OPTIONS_TABLE_SESSION,
  OPTIONS_TABLE_WINDOW
}
----------------------------
None
----------------------------
***/


// element in merge of:  options_table_entry,options,options_entry
struct options
{
  struct options_tree
  {
    struct options_entry *rbh_root;
  } tree;
  struct options *parent;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  options_table_entry,options,options_entry
struct options_entry
{
  struct options *owner;
  const char *name;
  const struct options_table_entry *tableentry;
  union 
  {
    char *string;
    long long number;
    struct grid_cell style;
    struct 
    {
      const char **array;
      u_int arraysize;
    };
  };
  struct 
  {
    struct options_entry *rbe_left;
    struct options_entry *rbe_right;
    struct options_entry *rbe_parent;
    int rbe_color;
  } entry;
}
/*** DEPENDENCIES:
None
----------------------------
***/


