#include <assert.h>
#include <config.h>
#include <endian.h>
#include <inttypes.h>
#include <json_config.h>
#include <json_inttypes.h>
#include <json_object.h>
#include <json_types.h>
#include <limits.h>
#include <linkhash.c>
#include <linkhash.h>
#include <printbuf.h>
#include <random_seed.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct printbuf;
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
};
typedef struct json_object_iter json_object_iter;
typedef int json_bool;
typedef struct json_object json_object;
typedef void json_object_delete_fn(struct json_object *jso, void *userdata);
typedef int json_object_to_json_string_fn(struct json_object *jso, struct printbuf *pb, int level, int flags);
typedef enum json_type
{
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
} json_type;
struct printbuf
{
  char *buf;
  int bpos;
  int size;
};
typedef struct printbuf printbuf;
extern struct printbuf *printbuf_new(void);
extern int printbuf_memappend(struct printbuf *p, const char *buf, int size);
extern int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len);
extern int sprintbuf(struct printbuf *p, const char *msg, ...);
extern void printbuf_reset(struct printbuf *p);
extern void printbuf_free(struct printbuf *p);
extern struct json_object *json_object_get(struct json_object *obj);
extern int json_object_put(struct json_object *obj);
extern int json_object_is_type(const struct json_object *obj, enum json_type type);
extern enum json_type json_object_get_type(const struct json_object *obj);
extern const char *json_object_to_json_string(struct json_object *obj);
extern const char *json_object_to_json_string_ext(struct json_object *obj, int flags);
extern const char *json_object_to_json_string_length(struct json_object *obj, int flags, size_t *length);
extern void *json_object_get_userdata(json_object *jso);
extern void json_object_set_userdata(json_object *jso, void *userdata, json_object_delete_fn *user_delete);
extern void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete);
extern json_object_delete_fn json_object_free_userdata;
extern json_object_to_json_string_fn json_object_userdata_to_json_string;
extern struct json_object *json_object_new_object(void);
extern struct lh_table *json_object_get_object(const struct json_object *obj);
extern int json_object_object_length(const struct json_object *obj);
extern size_t json_c_object_sizeof(void);
extern int json_object_object_add(struct json_object *obj, const char *key, struct json_object *val);
extern int json_object_object_add_ex(struct json_object *obj, const char * const key, struct json_object * const val, const unsigned opts);
extern struct json_object *json_object_object_get(const struct json_object *obj, const char *key);
extern int json_object_object_get_ex(const struct json_object *obj, const char *key, struct json_object **value);
extern void json_object_object_del(struct json_object *obj, const char *key);
extern struct json_object *json_object_new_array(void);
extern struct json_object *json_object_new_array_ext(int initial_size);
extern struct array_list *json_object_get_array(const struct json_object *obj);
extern size_t json_object_array_length(const struct json_object *obj);
extern void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern int json_object_array_add(struct json_object *obj, struct json_object *val);
extern int json_object_array_put_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern int json_object_array_insert_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern struct json_object *json_object_array_get_idx(const struct json_object *obj, size_t idx);
extern int json_object_array_del_idx(struct json_object *obj, size_t idx, size_t count);
extern int json_object_array_shrink(struct json_object *jso, int empty_slots);
extern struct json_object *json_object_new_boolean(json_bool b);
extern json_bool json_object_get_boolean(const struct json_object *obj);
extern int json_object_set_boolean(struct json_object *obj, json_bool new_value);
extern struct json_object *json_object_new_int(int32_t i);
extern struct json_object *json_object_new_int64(int64_t i);
extern struct json_object *json_object_new_uint64(uint64_t i);
extern int32_t json_object_get_int(const struct json_object *obj);
extern int json_object_set_int(struct json_object *obj, int new_value);
extern int json_object_int_inc(struct json_object *obj, int64_t val);
extern int64_t json_object_get_int64(const struct json_object *obj);
extern uint64_t json_object_get_uint64(const struct json_object *obj);
extern int json_object_set_int64(struct json_object *obj, int64_t new_value);
extern int json_object_set_uint64(struct json_object *obj, uint64_t new_value);
extern struct json_object *json_object_new_double(double d);
extern struct json_object *json_object_new_double_s(double d, const char *ds);
extern int json_c_set_serialization_double_format(const char *double_format, int global_or_thread);
extern int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags);
extern double json_object_get_double(const struct json_object *obj);
extern int json_object_set_double(struct json_object *obj, double new_value);
extern struct json_object *json_object_new_string(const char *s);
extern struct json_object *json_object_new_string_len(const char *s, const int len);
extern const char *json_object_get_string(struct json_object *obj);
extern int json_object_get_string_len(const struct json_object *obj);
extern int json_object_set_string(json_object *obj, const char *new_value);
extern int json_object_set_string_len(json_object *obj, const char *new_value, int len);
extern struct json_object *json_object_new_null(void);
extern int json_object_equal(struct json_object *obj1, struct json_object *obj2);
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst);
extern json_c_shallow_copy_fn json_c_shallow_copy_default;
extern int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy);
int json_global_set_string_hash(const int h);
struct lh_entry;
typedef void lh_entry_free_fn(struct lh_entry *e);
typedef unsigned long lh_hash_fn(const void *k);
typedef int lh_equal_fn(const void *k1, const void *k2);
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
};
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
};
typedef struct lh_table lh_table;
extern struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn);
extern struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn);
extern struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn);
extern void lh_table_free(struct lh_table *t);
extern int lh_table_insert(struct lh_table *t, const void *k, const void *v);
extern int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts);
extern struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k);
extern struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h);
extern json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v);
extern int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e);
extern int lh_table_delete(struct lh_table *t, const void *k);
extern int lh_table_length(struct lh_table *t);
int lh_table_resize(struct lh_table *t, int new_size);
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}

inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}

inline static void *lh_entry_k(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->k));
}

inline static int lh_entry_k_is_constant(const struct lh_entry *e)
{
  return e->k_is_constant;
}

inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}

inline static void lh_entry_set_val(struct lh_entry *e, void *newval)
{
  e->v = newval;
}

inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}

inline static struct lh_entry *lh_entry_prev(const struct lh_entry *e)
{
  return e->prev;
}

extern int json_c_get_random_seed(void);
static unsigned long lh_char_hash(const void *k);
static unsigned long lh_perllike_str_hash(const void *k);
static lh_hash_fn *char_hash_fn = lh_char_hash;
int lh_char_equal(const void *k1, const void *k2);
int lh_ptr_equal(const void *k1, const void *k2);
int json_global_set_string_hash(const int h)
{
  switch (h)
  {
    case 0:
      char_hash_fn = lh_char_hash;
      break;

    case 1:
      char_hash_fn = lh_perllike_str_hash;
      break;

    default:
      return -1;

  }

  return 0;
}

static unsigned long lh_ptr_hash(const void *k)
{
  return (unsigned long) (((((ptrdiff_t) k) * 0x9e370001UL) >> 4) & 18446744073709551615UL);
}

int lh_ptr_equal(const void *k1, const void *k2)
{
  return k1 == k2;
}

static uint32_t hashlittle(const void *key, size_t length, uint32_t initval)
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  union 
  {
    const void *ptr;
    size_t i;
  } u;
  a = (b = (c = (0xdeadbeef + ((uint32_t) length)) + initval));
  u.ptr = key;
  if (1 && ((u.i & 0x3) == 0))
  {
    const uint32_t *k = (const uint32_t *) key;
    unsigned int k_idx = 0;
    while (length > 12)
    {
      a += k[0 + k_idx];
      b += k[1 + k_idx];
      c += k[2 + k_idx];
      {
        a -= c;
        a ^= (c << 4) | (c >> (32 - 4));
        c += b;
        b -= a;
        b ^= (a << 6) | (a >> (32 - 6));
        a += c;
        c -= b;
        c ^= (b << 8) | (b >> (32 - 8));
        b += a;
        a -= c;
        a ^= (c << 16) | (c >> (32 - 16));
        c += b;
        b -= a;
        b ^= (a << 19) | (a >> (32 - 19));
        a += c;
        c -= b;
        c ^= (b << 4) | (b >> (32 - 4));
        b += a;
      }
      ;
      length -= 12;
      k_idx += 3;
    }

    switch (length)
    {
      case 12:
        c += k[2 + k_idx];
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 11:
        c += k[2 + k_idx] & 0xffffff;
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 10:
        c += k[2 + k_idx] & 0xffff;
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 9:
        c += k[2 + k_idx] & 0xff;
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 8:
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 7:
        b += k[1 + k_idx] & 0xffffff;
        a += k[0 + k_idx];
        break;

      case 6:
        b += k[1 + k_idx] & 0xffff;
        a += k[0 + k_idx];
        break;

      case 5:
        b += k[1 + k_idx] & 0xff;
        a += k[0 + k_idx];
        break;

      case 4:
        a += k[0 + k_idx];
        break;

      case 3:
        a += k[0 + k_idx] & 0xffffff;
        break;

      case 2:
        a += k[0 + k_idx] & 0xffff;
        break;

      case 1:
        a += k[0 + k_idx] & 0xff;
        break;

      case 0:
        return c;

    }

  }
  else
    if (1 && ((u.i & 0x1) == 0))
  {
    const uint16_t *k = (const uint16_t *) key;
    unsigned int k_idx = 0;
    const uint8_t *k8;
    unsigned int k8_idx = 0;
    while (length > 12)
    {
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
      {
        a -= c;
        a ^= (c << 4) | (c >> (32 - 4));
        c += b;
        b -= a;
        b ^= (a << 6) | (a >> (32 - 6));
        a += c;
        c -= b;
        c ^= (b << 8) | (b >> (32 - 8));
        b += a;
        a -= c;
        a ^= (c << 16) | (c >> (32 - 16));
        c += b;
        b -= a;
        b ^= (a << 19) | (a >> (32 - 19));
        a += c;
        c -= b;
        c ^= (b << 4) | (b >> (32 - 4));
        b += a;
      }
      ;
      length -= 12;
      k_idx += 6;
    }

    k8_idx = (const uint8_t *) k;
    switch (length)
    {
      case 12:
        c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
        b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 11:
        c += ((uint32_t) k8[10 + k8_idx]) << 16;

      case 10:
        c += k[4 + k_idx];
        b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 9:
        c += k8[8 + k8_idx];

      case 8:
        b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 7:
        b += ((uint32_t) k8[6 + k8_idx]) << 16;

      case 6:
        b += k[2 + k_idx];
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 5:
        b += k8[4 + k8_idx];

      case 4:
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 3:
        a += ((uint32_t) k8[2 + k8_idx]) << 16;

      case 2:
        a += k[0 + k_idx];
        break;

      case 1:
        a += k8[0 + k8_idx];
        break;

      case 0:
        return c;

    }

  }
  else
  {
    const uint8_t *k = (const uint8_t *) key;
    unsigned int k_idx = 0;
    while (length > 12)
    {
      a += k[0 + k_idx];
      a += ((uint32_t) k[1 + k_idx]) << 8;
      a += ((uint32_t) k[2 + k_idx]) << 16;
      a += ((uint32_t) k[3 + k_idx]) << 24;
      b += k[4 + k_idx];
      b += ((uint32_t) k[5 + k_idx]) << 8;
      b += ((uint32_t) k[6 + k_idx]) << 16;
      b += ((uint32_t) k[7 + k_idx]) << 24;
      c += k[8 + k_idx];
      c += ((uint32_t) k[9 + k_idx]) << 8;
      c += ((uint32_t) k[10 + k_idx]) << 16;
      c += ((uint32_t) k[11 + k_idx]) << 24;
      {
        a -= c;
        a ^= (c << 4) | (c >> (32 - 4));
        c += b;
        b -= a;
        b ^= (a << 6) | (a >> (32 - 6));
        a += c;
        c -= b;
        c ^= (b << 8) | (b >> (32 - 8));
        b += a;
        a -= c;
        a ^= (c << 16) | (c >> (32 - 16));
        c += b;
        b -= a;
        b ^= (a << 19) | (a >> (32 - 19));
        a += c;
        c -= b;
        c ^= (b << 4) | (b >> (32 - 4));
        b += a;
      }
      ;
      length -= 12;
      k_idx += 12;
    }

    switch (length)
    {
      case 12:
        c += ((uint32_t) k[11 + k_idx]) << 24;

      case 11:
        c += ((uint32_t) k[10 + k_idx]) << 16;

      case 10:
        c += ((uint32_t) k[9 + k_idx]) << 8;

      case 9:
        c += k[8 + k_idx];

      case 8:
        b += ((uint32_t) k[7 + k_idx]) << 24;

      case 7:
        b += ((uint32_t) k[6 + k_idx]) << 16;

      case 6:
        b += ((uint32_t) k[5 + k_idx]) << 8;

      case 5:
        b += k[4 + k_idx];

      case 4:
        a += ((uint32_t) k[3 + k_idx]) << 24;

      case 3:
        a += ((uint32_t) k[2 + k_idx]) << 16;

      case 2:
        a += ((uint32_t) k[1 + k_idx]) << 8;

      case 1:
        a += k[0 + k_idx];
        break;

      case 0:
        return c;

    }

  }
  {
    c ^= b;
    c -= (b << 14) | (b >> (32 - 14));
    a ^= c;
    a -= (c << 11) | (c >> (32 - 11));
    b ^= a;
    b -= (a << 25) | (a >> (32 - 25));
    c ^= b;
    c -= (b << 16) | (b >> (32 - 16));
    a ^= c;
    a -= (c << 4) | (c >> (32 - 4));
    b ^= a;
    b -= (a << 14) | (a >> (32 - 14));
    c ^= b;
    c -= (b << 24) | (b >> (32 - 24));
  }
  ;
  return c;
}

static unsigned long lh_perllike_str_hash(const void *k)
{
  const char *rkey = (const char *) k;
  unsigned int rkey_idx = 0;
  unsigned hashval = 1;
  while (rkey[rkey_idx])
  {
    hashval = (hashval * 33) + rkey[rkey_idx];
    rkey_idx += 1;
  }

  return hashval;
}

static unsigned long lh_char_hash(const void *k)
{
  static volatile int random_seed = -1;
  if (random_seed == (-1))
  {
    int seed;
    while ((seed = json_c_get_random_seed()) == (-1))
    {
    }

    (void) __sync_val_compare_and_swap(&random_seed, -1, seed);
  }
  return hashlittle((const char *) k, strlen((const char *) k), (uint32_t) random_seed);
}

int lh_char_equal(const void *k1, const void *k2)
{
  return strcmp((const char *) k1, (const char *) k2) == 0;
}

struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn)
{
  int i;
  struct lh_table *t;
  unsigned int t_idx = 0;
  assert(size > 0);
  t_idx = (struct lh_table *) calloc(1, sizeof(struct lh_table));
  if (!(&t[t_idx]))
  {
    return 0;
  }
  t->count = 0;
  t->size = size;
  t->table = (struct lh_entry *) calloc(size, sizeof(struct lh_entry));
  if (!t->table)
  {
    free(t);
    return 0;
  }
  t->free_fn = free_fn;
  t->hash_fn = hash_fn;
  t->equal_fn = equal_fn;
  for (i = 0; i < size; i += 1)
  {
    t->table[i].k = (void *) (-1);
  }

  return t;
}

struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn)
{
  return lh_table_new(size, free_fn, char_hash_fn, lh_char_equal);
}

struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn)
{
  return lh_table_new(size, free_fn, lh_ptr_hash, lh_ptr_equal);
}

int lh_table_resize(struct lh_table *t, int new_size)
{
  struct lh_table *new_t;
  unsigned int new_t_idx = 0;
  struct lh_entry *ent;
  unsigned int ent_idx = 0;
  new_t_idx = lh_table_new(new_size, 0, t->hash_fn, t->equal_fn);
  if ((&new_t[new_t_idx]) == 0)
  {
    return -1;
  }
  for (ent_idx = t->head; (&ent[ent_idx]) != 0; ent_idx = ent_idx->next)
  {
    unsigned long h = lh_get_hash(new_t, ent->k);
    unsigned int opts = 0;
    if (ent->k_is_constant)
    {
      opts = 1 << 2;
    }
    if (lh_table_insert_w_hash(new_t, ent->k, ent->v, h, opts) != 0)
    {
      lh_table_free(new_t);
      return -1;
    }
  }

  free(t->table);
  t->table = new_t->table;
  t->size = new_size;
  t->head = new_t->head;
  t->tail = new_t->tail;
  free(new_t);
  return 0;
}

void lh_table_free(struct lh_table *t)
{
  struct lh_entry *c;
  unsigned int c_idx = 0;
  if (t->free_fn)
  {
    for (c_idx = t->head; (&c[c_idx]) != 0; c_idx = c_idx->next)
    {
      t->free_fn(c);
    }

  }
  free(t->table);
  free(t);
}

int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts)
{
  unsigned long n;
  if (t->count >= (t->size * 0.66))
  {
    int new_size = (t->size > (2147483647 / 2)) ? (2147483647) : (t->size * 2);
    if ((t->size == 2147483647) || (lh_table_resize(t, new_size) != 0))
    {
      return -1;
    }
  }
  n = h % t->size;
  while (1)
  {
    if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
    {
      break;
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
  }

  t->table[n].k = k;
  t->table[n].k_is_constant = opts & (1 << 2);
  t->table[n].v = v;
  t->count += 1;
  if (t->head == 0)
  {
    t->head = (t->tail = &t->table[n]);
    t->table[n].next = (t->table[n].prev = 0);
  }
  else
  {
    t->tail->next = &t->table[n];
    t->table[n].prev = t->tail;
    t->table[n].next = 0;
    t->tail = &t->table[n];
  }
  return 0;
}

int lh_table_insert(struct lh_table *t, const void *k, const void *v)
{
  return lh_table_insert_w_hash(t, k, v, lh_get_hash(t, k), 0);
}

struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h)
{
  unsigned long n = h % t->size;
  int count = 0;
  while (count < t->size)
  {
    if (t->table[n].k == ((void *) (-1)))
    {
      return 0;
    }
    if ((t->table[n].k != ((void *) (-2))) && t->equal_fn(t->table[n].k, k))
    {
      return &t->table[n];
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
    count += 1;
  }

  return 0;
}

struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k)
{
  return lh_table_lookup_entry_w_hash(t, k, lh_get_hash(t, k));
}

json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (e != 0)
  {
    if (v != 0)
    {
      *v = lh_entry_v(e);
    }
    return 1;
  }
  if (v != 0)
  {
    *v = 0;
  }
  return 0;
}

int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e)
{
  ptrdiff_t n = (ptrdiff_t) (e - t->table);
  if (n < 0)
  {
    return -2;
  }
  if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
  {
    return -1;
  }
  t->count -= 1;
  if (t->free_fn)
  {
    t->free_fn(e);
  }
  t->table[n].v = 0;
  t->table[n].k = (void *) (-2);
  if ((t->tail == (&t->table[n])) && (t->head == (&t->table[n])))
  {
    t->head = (t->tail = 0);
  }
  else
    if (t->head == (&t->table[n]))
  {
    t->head->next->prev = 0;
    t->head = t->head->next;
  }
  else
    if (t->tail == (&t->table[n]))
  {
    t->tail->prev->next = 0;
    t->tail = t->tail->prev;
  }
  else
  {
    t->table[n].prev->next = t->table[n].next;
    t->table[n].next->prev = t->table[n].prev;
  }
  t->table[n].next = (t->table[n].prev = 0);
  return 0;
}

int lh_table_delete(struct lh_table *t, const void *k)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (!e)
  {
    return -1;
  }
  return lh_table_delete_entry(t, e);
}

int lh_table_length(struct lh_table *t)
{
  return t->count;
}


struct printbuf;
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
};
typedef struct json_object_iter json_object_iter;
typedef int json_bool;
typedef struct json_object json_object;
typedef void json_object_delete_fn(struct json_object *jso, void *userdata);
typedef int json_object_to_json_string_fn(struct json_object *jso, struct printbuf *pb, int level, int flags);
typedef enum json_type
{
  json_type_null,
  json_type_boolean,
  json_type_double,
  json_type_int,
  json_type_object,
  json_type_array,
  json_type_string
} json_type;
struct printbuf
{
  char *buf;
  int bpos;
  int size;
};
typedef struct printbuf printbuf;
extern struct printbuf *printbuf_new(void);
extern int printbuf_memappend(struct printbuf *p, const char *buf, int size);
extern int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len);
extern int sprintbuf(struct printbuf *p, const char *msg, ...);
extern void printbuf_reset(struct printbuf *p);
extern void printbuf_free(struct printbuf *p);
extern struct json_object *json_object_get(struct json_object *obj);
extern int json_object_put(struct json_object *obj);
extern int json_object_is_type(const struct json_object *obj, enum json_type type);
extern enum json_type json_object_get_type(const struct json_object *obj);
extern const char *json_object_to_json_string(struct json_object *obj);
extern const char *json_object_to_json_string_ext(struct json_object *obj, int flags);
extern const char *json_object_to_json_string_length(struct json_object *obj, int flags, size_t *length);
extern void *json_object_get_userdata(json_object *jso);
extern void json_object_set_userdata(json_object *jso, void *userdata, json_object_delete_fn *user_delete);
extern void json_object_set_serializer(json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete);
extern json_object_delete_fn json_object_free_userdata;
extern json_object_to_json_string_fn json_object_userdata_to_json_string;
extern struct json_object *json_object_new_object(void);
extern struct lh_table *json_object_get_object(const struct json_object *obj);
extern int json_object_object_length(const struct json_object *obj);
extern size_t json_c_object_sizeof(void);
extern int json_object_object_add(struct json_object *obj, const char *key, struct json_object *val);
extern int json_object_object_add_ex(struct json_object *obj, const char * const key, struct json_object * const val, const unsigned opts);
extern struct json_object *json_object_object_get(const struct json_object *obj, const char *key);
extern int json_object_object_get_ex(const struct json_object *obj, const char *key, struct json_object **value);
extern void json_object_object_del(struct json_object *obj, const char *key);
extern struct json_object *json_object_new_array(void);
extern struct json_object *json_object_new_array_ext(int initial_size);
extern struct array_list *json_object_get_array(const struct json_object *obj);
extern size_t json_object_array_length(const struct json_object *obj);
extern void json_object_array_sort(struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern struct json_object *json_object_array_bsearch(const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *));
extern int json_object_array_add(struct json_object *obj, struct json_object *val);
extern int json_object_array_put_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern int json_object_array_insert_idx(struct json_object *obj, size_t idx, struct json_object *val);
extern struct json_object *json_object_array_get_idx(const struct json_object *obj, size_t idx);
extern int json_object_array_del_idx(struct json_object *obj, size_t idx, size_t count);
extern int json_object_array_shrink(struct json_object *jso, int empty_slots);
extern struct json_object *json_object_new_boolean(json_bool b);
extern json_bool json_object_get_boolean(const struct json_object *obj);
extern int json_object_set_boolean(struct json_object *obj, json_bool new_value);
extern struct json_object *json_object_new_int(int32_t i);
extern struct json_object *json_object_new_int64(int64_t i);
extern struct json_object *json_object_new_uint64(uint64_t i);
extern int32_t json_object_get_int(const struct json_object *obj);
extern int json_object_set_int(struct json_object *obj, int new_value);
extern int json_object_int_inc(struct json_object *obj, int64_t val);
extern int64_t json_object_get_int64(const struct json_object *obj);
extern uint64_t json_object_get_uint64(const struct json_object *obj);
extern int json_object_set_int64(struct json_object *obj, int64_t new_value);
extern int json_object_set_uint64(struct json_object *obj, uint64_t new_value);
extern struct json_object *json_object_new_double(double d);
extern struct json_object *json_object_new_double_s(double d, const char *ds);
extern int json_c_set_serialization_double_format(const char *double_format, int global_or_thread);
extern int json_object_double_to_json_string(struct json_object *jso, struct printbuf *pb, int level, int flags);
extern double json_object_get_double(const struct json_object *obj);
extern int json_object_set_double(struct json_object *obj, double new_value);
extern struct json_object *json_object_new_string(const char *s);
extern struct json_object *json_object_new_string_len(const char *s, const int len);
extern const char *json_object_get_string(struct json_object *obj);
extern int json_object_get_string_len(const struct json_object *obj);
extern int json_object_set_string(json_object *obj, const char *new_value);
extern int json_object_set_string_len(json_object *obj, const char *new_value, int len);
extern struct json_object *json_object_new_null(void);
extern int json_object_equal(struct json_object *obj1, struct json_object *obj2);
typedef int json_c_shallow_copy_fn(json_object *src, json_object *parent, const char *key, size_t index, json_object **dst);
extern json_c_shallow_copy_fn json_c_shallow_copy_default;
extern int json_object_deep_copy(struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy);
int json_global_set_string_hash(const int h);
struct lh_entry;
typedef void lh_entry_free_fn(struct lh_entry *e);
typedef unsigned long lh_hash_fn(const void *k);
typedef int lh_equal_fn(const void *k1, const void *k2);
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
};
struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
};
typedef struct lh_table lh_table;
extern struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn);
extern struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn);
extern struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn);
extern void lh_table_free(struct lh_table *t);
extern int lh_table_insert(struct lh_table *t, const void *k, const void *v);
extern int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts);
extern struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k);
extern struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h);
extern json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v);
extern int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e);
extern int lh_table_delete(struct lh_table *t, const void *k);
extern int lh_table_length(struct lh_table *t);
int lh_table_resize(struct lh_table *t, int new_size);
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}

inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}

inline static void *lh_entry_k(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->k));
}

inline static int lh_entry_k_is_constant(const struct lh_entry *e)
{
  return e->k_is_constant;
}

inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}

inline static void lh_entry_set_val(struct lh_entry *e, void *newval)
{
  e->v = newval;
}

inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}

inline static struct lh_entry *lh_entry_prev(const struct lh_entry *e)
{
  return e->prev;
}

extern int json_c_get_random_seed(void);
static unsigned long lh_char_hash(const void *k);
static unsigned long lh_perllike_str_hash(const void *k);
static lh_hash_fn *char_hash_fn = lh_char_hash;
int lh_char_equal(const void *k1, const void *k2);
int lh_ptr_equal(const void *k1, const void *k2);
int json_global_set_string_hash(const int h)
{
  switch (h)
  {
    case 0:
      char_hash_fn = lh_char_hash;
      break;

    case 1:
      char_hash_fn = lh_perllike_str_hash;
      break;

    default:
      return -1;

  }

  return 0;
}

static unsigned long lh_ptr_hash(const void *k)
{
  return (unsigned long) (((((ptrdiff_t) k) * 0x9e370001UL) >> 4) & 18446744073709551615UL);
}

int lh_ptr_equal(const void *k1, const void *k2)
{
  return k1 == k2;
}

static uint32_t hashlittle(const void *key, size_t length, uint32_t initval)
{
  uint32_t a;
  uint32_t b;
  uint32_t c;
  union 
  {
    const void *ptr;
    size_t i;
  } u;
  a = (b = (c = (0xdeadbeef + ((uint32_t) length)) + initval));
  u.ptr = key;
  if (1 && ((u.i & 0x3) == 0))
  {
    const uint32_t *k = (const uint32_t *) key;
    unsigned int k_idx = 0;
    while (length > 12)
    {
      a += k[0 + k_idx];
      b += k[1 + k_idx];
      c += k[2 + k_idx];
      {
        a -= c;
        a ^= (c << 4) | (c >> (32 - 4));
        c += b;
        b -= a;
        b ^= (a << 6) | (a >> (32 - 6));
        a += c;
        c -= b;
        c ^= (b << 8) | (b >> (32 - 8));
        b += a;
        a -= c;
        a ^= (c << 16) | (c >> (32 - 16));
        c += b;
        b -= a;
        b ^= (a << 19) | (a >> (32 - 19));
        a += c;
        c -= b;
        c ^= (b << 4) | (b >> (32 - 4));
        b += a;
      }
      ;
      length -= 12;
      k_idx += 3;
    }

    switch (length)
    {
      case 12:
        c += k[2 + k_idx];
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 11:
        c += k[2 + k_idx] & 0xffffff;
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 10:
        c += k[2 + k_idx] & 0xffff;
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 9:
        c += k[2 + k_idx] & 0xff;
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 8:
        b += k[1 + k_idx];
        a += k[0 + k_idx];
        break;

      case 7:
        b += k[1 + k_idx] & 0xffffff;
        a += k[0 + k_idx];
        break;

      case 6:
        b += k[1 + k_idx] & 0xffff;
        a += k[0 + k_idx];
        break;

      case 5:
        b += k[1 + k_idx] & 0xff;
        a += k[0 + k_idx];
        break;

      case 4:
        a += k[0 + k_idx];
        break;

      case 3:
        a += k[0 + k_idx] & 0xffffff;
        break;

      case 2:
        a += k[0 + k_idx] & 0xffff;
        break;

      case 1:
        a += k[0 + k_idx] & 0xff;
        break;

      case 0:
        return c;

    }

  }
  else
    if (1 && ((u.i & 0x1) == 0))
  {
    const uint16_t *k = (const uint16_t *) key;
    unsigned int k_idx = 0;
    const uint8_t *k8;
    unsigned int k8_idx = 0;
    while (length > 12)
    {
      a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
      b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
      c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
      {
        a -= c;
        a ^= (c << 4) | (c >> (32 - 4));
        c += b;
        b -= a;
        b ^= (a << 6) | (a >> (32 - 6));
        a += c;
        c -= b;
        c ^= (b << 8) | (b >> (32 - 8));
        b += a;
        a -= c;
        a ^= (c << 16) | (c >> (32 - 16));
        c += b;
        b -= a;
        b ^= (a << 19) | (a >> (32 - 19));
        a += c;
        c -= b;
        c ^= (b << 4) | (b >> (32 - 4));
        b += a;
      }
      ;
      length -= 12;
      k_idx += 6;
    }

    k8_idx = (const uint8_t *) k;
    switch (length)
    {
      case 12:
        c += k[4 + k_idx] + (((uint32_t) k[5 + k_idx]) << 16);
        b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 11:
        c += ((uint32_t) k8[10 + k8_idx]) << 16;

      case 10:
        c += k[4 + k_idx];
        b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 9:
        c += k8[8 + k8_idx];

      case 8:
        b += k[2 + k_idx] + (((uint32_t) k[3 + k_idx]) << 16);
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 7:
        b += ((uint32_t) k8[6 + k8_idx]) << 16;

      case 6:
        b += k[2 + k_idx];
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 5:
        b += k8[4 + k8_idx];

      case 4:
        a += k[0 + k_idx] + (((uint32_t) k[1 + k_idx]) << 16);
        break;

      case 3:
        a += ((uint32_t) k8[2 + k8_idx]) << 16;

      case 2:
        a += k[0 + k_idx];
        break;

      case 1:
        a += k8[0 + k8_idx];
        break;

      case 0:
        return c;

    }

  }
  else
  {
    const uint8_t *k = (const uint8_t *) key;
    unsigned int k_idx = 0;
    while (length > 12)
    {
      a += k[0 + k_idx];
      a += ((uint32_t) k[1 + k_idx]) << 8;
      a += ((uint32_t) k[2 + k_idx]) << 16;
      a += ((uint32_t) k[3 + k_idx]) << 24;
      b += k[4 + k_idx];
      b += ((uint32_t) k[5 + k_idx]) << 8;
      b += ((uint32_t) k[6 + k_idx]) << 16;
      b += ((uint32_t) k[7 + k_idx]) << 24;
      c += k[8 + k_idx];
      c += ((uint32_t) k[9 + k_idx]) << 8;
      c += ((uint32_t) k[10 + k_idx]) << 16;
      c += ((uint32_t) k[11 + k_idx]) << 24;
      {
        a -= c;
        a ^= (c << 4) | (c >> (32 - 4));
        c += b;
        b -= a;
        b ^= (a << 6) | (a >> (32 - 6));
        a += c;
        c -= b;
        c ^= (b << 8) | (b >> (32 - 8));
        b += a;
        a -= c;
        a ^= (c << 16) | (c >> (32 - 16));
        c += b;
        b -= a;
        b ^= (a << 19) | (a >> (32 - 19));
        a += c;
        c -= b;
        c ^= (b << 4) | (b >> (32 - 4));
        b += a;
      }
      ;
      length -= 12;
      k_idx += 12;
    }

    switch (length)
    {
      case 12:
        c += ((uint32_t) k[11 + k_idx]) << 24;

      case 11:
        c += ((uint32_t) k[10 + k_idx]) << 16;

      case 10:
        c += ((uint32_t) k[9 + k_idx]) << 8;

      case 9:
        c += k[8 + k_idx];

      case 8:
        b += ((uint32_t) k[7 + k_idx]) << 24;

      case 7:
        b += ((uint32_t) k[6 + k_idx]) << 16;

      case 6:
        b += ((uint32_t) k[5 + k_idx]) << 8;

      case 5:
        b += k[4 + k_idx];

      case 4:
        a += ((uint32_t) k[3 + k_idx]) << 24;

      case 3:
        a += ((uint32_t) k[2 + k_idx]) << 16;

      case 2:
        a += ((uint32_t) k[1 + k_idx]) << 8;

      case 1:
        a += k[0 + k_idx];
        break;

      case 0:
        return c;

    }

  }
  {
    c ^= b;
    c -= (b << 14) | (b >> (32 - 14));
    a ^= c;
    a -= (c << 11) | (c >> (32 - 11));
    b ^= a;
    b -= (a << 25) | (a >> (32 - 25));
    c ^= b;
    c -= (b << 16) | (b >> (32 - 16));
    a ^= c;
    a -= (c << 4) | (c >> (32 - 4));
    b ^= a;
    b -= (a << 14) | (a >> (32 - 14));
    c ^= b;
    c -= (b << 24) | (b >> (32 - 24));
  }
  ;
  return c;
}

static unsigned long lh_perllike_str_hash(const void *k)
{
  const char *rkey = (const char *) k;
  unsigned int rkey_idx = 0;
  unsigned hashval = 1;
  while (rkey[rkey_idx])
  {
    hashval = (hashval * 33) + rkey[rkey_idx];
    rkey_idx += 1;
  }

  return hashval;
}

static unsigned long lh_char_hash(const void *k)
{
  static volatile int random_seed = -1;
  if (random_seed == (-1))
  {
    int seed;
    while ((seed = json_c_get_random_seed()) == (-1))
    {
    }

    (void) __sync_val_compare_and_swap(&random_seed, -1, seed);
  }
  return hashlittle((const char *) k, strlen((const char *) k), (uint32_t) random_seed);
}

int lh_char_equal(const void *k1, const void *k2)
{
  return strcmp((const char *) k1, (const char *) k2) == 0;
}

struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn)
{
  int i;
  struct lh_table *t;
  unsigned int t_idx = 0;
  assert(size > 0);
  t_idx = (struct lh_table *) calloc(1, sizeof(struct lh_table));
  if (!(&t[t_idx]))
  {
    return 0;
  }
  t->count = 0;
  t->size = size;
  t->table = (struct lh_entry *) calloc(size, sizeof(struct lh_entry));
  if (!t->table)
  {
    free(t);
    return 0;
  }
  t->free_fn = free_fn;
  t->hash_fn = hash_fn;
  t->equal_fn = equal_fn;
  for (i = 0; i < size; i += 1)
  {
    t->table[i].k = (void *) (-1);
  }

  return t;
}

struct lh_table *lh_kchar_table_new(int size, lh_entry_free_fn *free_fn)
{
  return lh_table_new(size, free_fn, char_hash_fn, lh_char_equal);
}

struct lh_table *lh_kptr_table_new(int size, lh_entry_free_fn *free_fn)
{
  return lh_table_new(size, free_fn, lh_ptr_hash, lh_ptr_equal);
}

int lh_table_resize(struct lh_table *t, int new_size)
{
  struct lh_table *new_t;
  unsigned int new_t_idx = 0;
  struct lh_entry *ent;
  unsigned int ent_idx = 0;
  new_t_idx = lh_table_new(new_size, 0, t->hash_fn, t->equal_fn);
  if ((&new_t[new_t_idx]) == 0)
  {
    return -1;
  }
  for (ent_idx = t->head; (&ent[ent_idx]) != 0; ent_idx = ent_idx->next)
  {
    unsigned long h = lh_get_hash(new_t, ent->k);
    unsigned int opts = 0;
    if (ent->k_is_constant)
    {
      opts = 1 << 2;
    }
    if (lh_table_insert_w_hash(new_t, ent->k, ent->v, h, opts) != 0)
    {
      lh_table_free(new_t);
      return -1;
    }
  }

  free(t->table);
  t->table = new_t->table;
  t->size = new_size;
  t->head = new_t->head;
  t->tail = new_t->tail;
  free(new_t);
  return 0;
}

void lh_table_free(struct lh_table *t)
{
  struct lh_entry *c;
  unsigned int c_idx = 0;
  if (t->free_fn)
  {
    for (c_idx = t->head; (&c[c_idx]) != 0; c_idx = c_idx->next)
    {
      t->free_fn(c);
    }

  }
  free(t->table);
  free(t);
}

int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts)
{
  unsigned long n;
  if (t->count >= (t->size * 0.66))
  {
    int new_size = (t->size > (2147483647 / 2)) ? (2147483647) : (t->size * 2);
    if ((t->size == 2147483647) || (lh_table_resize(t, new_size) != 0))
    {
      return -1;
    }
  }
  n = h % t->size;
  while (1)
  {
    if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
    {
      break;
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
  }

  t->table[n].k = k;
  t->table[n].k_is_constant = opts & (1 << 2);
  t->table[n].v = v;
  t->count += 1;
  if (t->head == 0)
  {
    t->head = (t->tail = &t->table[n]);
    t->table[n].next = (t->table[n].prev = 0);
  }
  else
  {
    t->tail->next = &t->table[n];
    t->table[n].prev = t->tail;
    t->table[n].next = 0;
    t->tail = &t->table[n];
  }
  return 0;
}

int lh_table_insert(struct lh_table *t, const void *k, const void *v)
{
  return lh_table_insert_w_hash(t, k, v, lh_get_hash(t, k), 0);
}

struct lh_entry *lh_table_lookup_entry_w_hash(struct lh_table *t, const void *k, const unsigned long h)
{
  unsigned long n = h % t->size;
  int count = 0;
  while (count < t->size)
  {
    if (t->table[n].k == ((void *) (-1)))
    {
      return 0;
    }
    if ((t->table[n].k != ((void *) (-2))) && t->equal_fn(t->table[n].k, k))
    {
      return &t->table[n];
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
    count += 1;
  }

  return 0;
}

struct lh_entry *lh_table_lookup_entry(struct lh_table *t, const void *k)
{
  return lh_table_lookup_entry_w_hash(t, k, lh_get_hash(t, k));
}

json_bool lh_table_lookup_ex(struct lh_table *t, const void *k, void **v)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (e != 0)
  {
    if (v != 0)
    {
      *v = lh_entry_v(e);
    }
    return 1;
  }
  if (v != 0)
  {
    *v = 0;
  }
  return 0;
}

int lh_table_delete_entry(struct lh_table *t, struct lh_entry *e)
{
  ptrdiff_t n = (ptrdiff_t) (e - t->table);
  if (n < 0)
  {
    return -2;
  }
  if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
  {
    return -1;
  }
  t->count -= 1;
  if (t->free_fn)
  {
    t->free_fn(e);
  }
  t->table[n].v = 0;
  t->table[n].k = (void *) (-2);
  if ((t->tail == (&t->table[n])) && (t->head == (&t->table[n])))
  {
    t->head = (t->tail = 0);
  }
  else
    if (t->head == (&t->table[n]))
  {
    t->head->next->prev = 0;
    t->head = t->head->next;
  }
  else
    if (t->tail == (&t->table[n]))
  {
    t->tail->prev->next = 0;
    t->tail = t->tail->prev;
  }
  else
  {
    t->table[n].prev->next = t->table[n].next;
    t->table[n].next->prev = t->table[n].prev;
  }
  t->table[n].next = (t->table[n].prev = 0);
  return 0;
}

int lh_table_delete(struct lh_table *t, const void *k)
{
  struct lh_entry *e = lh_table_lookup_entry(t, k);
  if (!e)
  {
    return -1;
  }
  return lh_table_delete_entry(t, e);
}

int lh_table_length(struct lh_table *t)
{
  return t->count;
}

