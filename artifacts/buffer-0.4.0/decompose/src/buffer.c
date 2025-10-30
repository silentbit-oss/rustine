buffer_t *buffer_new_with_size(size_t n)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = n;
  self->data = (self->alloc = calloc(n + 1, 1));
  return self;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


/*** DEPENDENCIES:
buffer_t *buffer_new_with_size(size_t n)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = n;
  self->data = (self->alloc = calloc(n + 1, 1));
  return self;
}


----------------------------
***/


buffer_t *buffer_new_with_string_length(char *str, size_t len)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = len;
  self->data = (self->alloc = str);
  return self;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


buffer_t *buffer_new_with_string(char *str)
{
  return buffer_new_with_string_length(str, strlen(str));
}


/*** DEPENDENCIES:
buffer_t *buffer_new_with_string_length(char *str, size_t len)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = len;
  self->data = (self->alloc = str);
  return self;
}


----------------------------
***/


size_t buffer_size(buffer_t *self)
{
  return self->len;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


int buffer_equals(buffer_t *self, buffer_t *other)
{
  return 0 == strcmp(self->data, other->data);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


ssize_t buffer_indexof(buffer_t *self, char *str)
{
  char *sub = strstr(self->data, str);
  if (!sub)
  {
    return -1;
  }
  return sub - self->data;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


void buffer_fill(buffer_t *self, int c)
{
  memset(self->data, c, self->len);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


void buffer_trim_left(buffer_t *self)
{
  int c;
  while ((c = *self->data) && isspace(c))
  {
    self->data += 1;
  }

}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


void buffer_print(buffer_t *self)
{
  size_t len = self->len;
  printf("\n ");
  for (int i = 0; i < len; i += 1)
  {
    printf(" %02x", self->alloc[i]);
    if (((i + 1) % 8) == 0)
    {
      printf("\n ");
    }
  }

  printf("\n");
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


int buffer_resize(buffer_t *self, size_t n)
{
  n = (n + (1024 - 1)) & (~(1024 - 1));
  self->len = n;
  self->alloc = (self->data = realloc(self->alloc, n + 1));
  if (!self->alloc)
  {
    return -1;
  }
  self->alloc[n] = '\0';
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
buffer_t *buffer_new_with_size(size_t n)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = n;
  self->data = (self->alloc = calloc(n + 1, 1));
  return self;
}


----------------------------
***/


int buffer_prepend(buffer_t *self, char *str)
{
  size_t len = strlen(str);
  size_t prev = strlen(self->data);
  size_t needed = len + prev;
  if (self->len > needed)
  {
    goto move;
  }
  int ret = buffer_resize(self, needed);
  if ((-1) == ret)
  {
    return -1;
  }
  move:
  memmove(self->data + len, self->data, len + 1);

  memcpy(self->data, str, len);
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
int buffer_resize(buffer_t *self, size_t n)
{
  n = (n + (1024 - 1)) & (~(1024 - 1));
  self->len = n;
  self->alloc = (self->data = realloc(self->alloc, n + 1));
  if (!self->alloc)
  {
    return -1;
  }
  self->alloc[n] = '\0';
  return 0;
}


----------------------------
***/


int buffer_append_n(buffer_t *self, const char *str, size_t len)
{
  size_t prev = strlen(self->data);
  size_t needed = len + prev;
  if (self->len > needed)
  {
    strncat(self->data, str, len);
    return 0;
  }
  int ret = buffer_resize(self, needed);
  if ((-1) == ret)
  {
    return -1;
  }
  strncat(self->data, str, len);
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
int buffer_resize(buffer_t *self, size_t n)
{
  n = (n + (1024 - 1)) & (~(1024 - 1));
  self->len = n;
  self->alloc = (self->data = realloc(self->alloc, n + 1));
  if (!self->alloc)
  {
    return -1;
  }
  self->alloc[n] = '\0';
  return 0;
}


----------------------------
***/


int buffer_append(buffer_t *self, const char *str)
{
  return buffer_append_n(self, str, strlen(str));
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
int buffer_append_n(buffer_t *self, const char *str, size_t len)
{
  size_t prev = strlen(self->data);
  size_t needed = len + prev;
  if (self->len > needed)
  {
    strncat(self->data, str, len);
    return 0;
  }
  int ret = buffer_resize(self, needed);
  if ((-1) == ret)
  {
    return -1;
  }
  strncat(self->data, str, len);
  return 0;
}


----------------------------
***/


buffer_t *buffer_slice(buffer_t *buf, size_t from, ssize_t to)
{
  size_t len = strlen(buf->data);
  if (to < from)
  {
    return 0;
  }
  if (to < 0)
  {
    to = len - (~to);
  }
  if (to > len)
  {
    to = len;
  }
  size_t n = to - from;
  buffer_t *self = buffer_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
buffer_t *buffer_new_with_size(size_t n)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = n;
  self->data = (self->alloc = calloc(n + 1, 1));
  return self;
}


----------------------------
***/


ssize_t buffer_compact(buffer_t *self)
{
  size_t len = buffer_length(self);
  size_t rem = self->len - len;
  char *buf = calloc(len + 1, 1);
  if (!buf)
  {
    return -1;
  }
  memcpy(buf, self->data, len);
  free(self->alloc);
  self->len = len;
  self->data = (self->alloc = buf);
  return rem;
}


/*** DEPENDENCIES:
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


void buffer_clear(buffer_t *self)
{
  buffer_fill(self, 0);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_fill(buffer_t *self, int c)
{
  memset(self->data, c, self->len);
}


----------------------------
***/


void buffer_trim_right(buffer_t *self)
{
  int c;
  size_t i = buffer_length(self) - 1;
  while ((c = self->data[i]) && isspace(c))
  {
    self->data[i] = 0;
    i -= 1;
  }

}


/*** DEPENDENCIES:
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


int buffer_appendf(buffer_t *self, const char *format, ...)
{
  va_list ap;
  va_list tmpa;
  char *dst = 0;
  unsigned int dst_idx = 0;
  int length = 0;
  int required = 0;
  int bytes = 0;
  __builtin_va_start(ap);
  length = buffer_length(self);
  va_copy(tmpa, ap);
  required = vsnprintf(0, 0, format, tmpa);
  ;
  if ((-1) == buffer_resize(self, length + required))
  {
    ;
    return -1;
  }
  dst_idx = self->data + length;
  bytes = vsnprintf(dst, 1 + required, format, ap);
  ;
  return (bytes < 0) ? (-1) : (0);
}


/*** DEPENDENCIES:
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
int buffer_resize(buffer_t *self, size_t n)
{
  n = (n + (1024 - 1)) & (~(1024 - 1));
  self->len = n;
  self->alloc = (self->data = realloc(self->alloc, n + 1));
  if (!self->alloc)
  {
    return -1;
  }
  self->alloc[n] = '\0';
  return 0;
}


----------------------------
***/


void buffer_trim(buffer_t *self)
{
  buffer_trim_left(self);
  buffer_trim_right(self);
}


/*** DEPENDENCIES:
void buffer_trim_right(buffer_t *self)
{
  int c;
  size_t i = buffer_length(self) - 1;
  while ((c = self->data[i]) && isspace(c))
  {
    self->data[i] = 0;
    i -= 1;
  }

}


----------------------------
void buffer_trim_left(buffer_t *self)
{
  int c;
  while ((c = *self->data) && isspace(c))
  {
    self->data += 1;
  }

}


----------------------------
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
***/


