// element in merge of:  server_client_stderr_cb,server_client_push_stderr
static void server_client_stderr_cb(int fd, short events, void *arg)
{
  struct client *c = arg;
  if ((~c->flags) & 0x200)
  {
    server_client_push_stderr(c);
  }
  server_client_unref(c);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


// element in merge of:  server_client_stderr_cb,server_client_push_stderr
void server_client_push_stderr(struct client *c)
{
  struct msg_stderr_data data;
  size_t sent;
  size_t left;
  if (c->stderr_data == c->stdout_data)
  {
    server_client_push_stdout(c);
    return;
  }
  left = EVBUFFER_LENGTH(c->stderr_data);
  while (left != 0)
  {
    sent = left;
    if (sent > (sizeof(data.data)))
    {
      sent = sizeof(data.data);
    }
    memcpy(data.data, EVBUFFER_DATA(c->stderr_data), sent);
    data.size = sent;
    if (proc_send(c->peer, MSG_STDERR, -1, &data, sizeof(data)) != 0)
    {
      break;
    }
    evbuffer_drain(c->stderr_data, sent);
    left = EVBUFFER_LENGTH(c->stderr_data);
    log_debug("%s: client %p, sent %zu, left %zu", __func__, c, sent, left);
  }

  if (left != 0)
  {
    c->references += 1;
    event_once(-1, EV_TIMEOUT, server_client_stderr_cb, c, 0);
    log_debug("%s: client %p, queued", __func__, c);
  }
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
struct msg_stderr_data
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
***/


