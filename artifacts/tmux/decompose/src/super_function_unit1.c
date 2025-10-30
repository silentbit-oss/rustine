// element in merge of:  server_client_push_stdout,server_client_stdout_cb
void server_client_push_stdout(struct client *c)
{
  struct msg_stdout_data data;
  size_t sent;
  size_t left;
  left = EVBUFFER_LENGTH(c->stdout_data);
  while (left != 0)
  {
    sent = left;
    if (sent > (sizeof(data.data)))
    {
      sent = sizeof(data.data);
    }
    memcpy(data.data, EVBUFFER_DATA(c->stdout_data), sent);
    data.size = sent;
    if (proc_send(c->peer, MSG_STDOUT, -1, &data, sizeof(data)) != 0)
    {
      break;
    }
    evbuffer_drain(c->stdout_data, sent);
    left = EVBUFFER_LENGTH(c->stdout_data);
    log_debug("%s: client %p, sent %zu, left %zu", __func__, c, sent, left);
  }

  if (left != 0)
  {
    c->references += 1;
    event_once(-1, EV_TIMEOUT, server_client_stdout_cb, c, 0);
    log_debug("%s: client %p, queued", __func__, c);
  }
}


/*** DEPENDENCIES:
struct msg_stdout_data
{
  ssize_t size;
  char data[1024];
}
----------------------------
None
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  server_client_push_stdout,server_client_stdout_cb
static void server_client_stdout_cb(int fd, short events, void *arg)
{
  struct client *c = arg;
  if ((~c->flags) & 0x200)
  {
    server_client_push_stdout(c);
  }
  server_client_unref(c);
}


/*** DEPENDENCIES:
None
----------------------------
void server_client_unref(struct client *c)
{
  log_debug("unref client %p (%d references)", c, c->references);
  c->references -= 1;
  if (c->references == 0)
  {
    event_once(-1, EV_TIMEOUT, server_client_free, c, 0);
  }
}


----------------------------
None
----------------------------
***/


