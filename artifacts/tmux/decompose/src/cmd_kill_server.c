static enum cmd_retval cmd_kill_server_exec(struct cmd *self, struct cmdq_item *item)
{
  if (self->entry == (&cmd_kill_server_entry))
  {
    kill(getpid(), SIGTERM);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
extern const struct cmd_entry cmd_kill_server_entry
----------------------------
None
----------------------------
***/


