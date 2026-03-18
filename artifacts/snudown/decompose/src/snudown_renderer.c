struct snudown_renderer
{
  struct sd_markdown *main_renderer;
  struct sd_markdown *toc_renderer;
  struct module_state *state;
  struct module_state *toc_state;
}
/*** DEPENDENCIES:
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
}
----------------------------
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
}
----------------------------
***/


