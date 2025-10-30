#include <assert.h>
#include <binn.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <test_binn.c>

typedef int BOOL;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef void (*binn_mem_free)(void *);
struct binn_struct
{
  int header;
  BOOL allocated;
  BOOL writable;
  BOOL dirty;
  void *pbuf;
  BOOL pre_allocated;
  int alloc_size;
  int used_size;
  int type;
  void *ptr;
  int size;
  int count;
  binn_mem_free freefn;
  union 
  {
    signed char vint8;
    signed short vint16;
    signed int vint32;
    int64 vint64;
    unsigned char vuint8;
    unsigned short vuint16;
    unsigned int vuint32;
    uint64 vuint64;
    signed char vchar;
    unsigned char vuchar;
    signed short vshort;
    unsigned short vushort;
    signed int vint;
    unsigned int vuint;
    float vfloat;
    double vdouble;
    BOOL vbool;
  };
  BOOL disable_int_compression;
};
typedef struct binn_struct binn;
char *binn_version();
void binn_set_alloc_functions(void *(*new_malloc)(size_t), void *(*new_realloc)(void *, size_t), void (*new_free)(void *));
int binn_create_type(int storage_type, int data_type_index);
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type);
int binn_get_write_storage(int type);
int binn_get_read_storage(int type);
BOOL binn_is_container(binn *item);
binn *binn_new(int type, int size, void *buffer);
binn *binn_list();
binn *binn_map();
binn *binn_object();
BOOL binn_create(binn *item, int type, int size, void *buffer);
BOOL binn_create_list(binn *list);
BOOL binn_create_map(binn *map);
BOOL binn_create_object(binn *object);
binn *binn_copy(void *old);
BOOL binn_list_add_new(binn *list, binn *value);
BOOL binn_map_set_new(binn *map, int id, binn *value);
BOOL binn_object_set_new(binn *obj, const char *key, binn *value);
BOOL binn_list_add(binn *list, int type, void *pvalue, int size);
BOOL binn_map_set(binn *map, int id, int type, void *pvalue, int size);
BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size);
void binn_free(binn *item);
void *binn_release(binn *item);
binn *binn_value(int type, void *pvalue, int size, binn_mem_free freefn);
inline static binn *binn_int8(signed char value)
{
  return binn_value(0x21, &value, 0, 0);
}

inline static binn *binn_int16(short value)
{
  return binn_value(0x41, &value, 0, 0);
}

inline static binn *binn_int32(int value)
{
  return binn_value(0x61, &value, 0, 0);
}

inline static binn *binn_int64(int64 value)
{
  return binn_value(0x81, &value, 0, 0);
}

inline static binn *binn_uint8(unsigned char value)
{
  return binn_value(0x20, &value, 0, 0);
}

inline static binn *binn_uint16(unsigned short value)
{
  return binn_value(0x40, &value, 0, 0);
}

inline static binn *binn_uint32(unsigned int value)
{
  return binn_value(0x60, &value, 0, 0);
}

inline static binn *binn_uint64(uint64 value)
{
  return binn_value(0x80, &value, 0, 0);
}

inline static binn *binn_float(float value)
{
  return binn_value(0x62, &value, 0, 0);
}

inline static binn *binn_double(double value)
{
  return binn_value(0x82, &value, 0, 0);
}

inline static binn *binn_bool(BOOL value)
{
  return binn_value(0x80061, &value, 0, 0);
}

inline static binn *binn_null()
{
  return binn_value(0x00, 0, 0, 0);
}

inline static binn *binn_string(char *str, binn_mem_free freefn)
{
  return binn_value(0xA0, str, 0, freefn);
}

inline static binn *binn_blob(void *ptr, int size, binn_mem_free freefn)
{
  return binn_value(0xC0, ptr, size, freefn);
}

void *binn_ptr(void *ptr);
int binn_size(void *ptr);
int binn_type(void *ptr);
int binn_count(void *ptr);
BOOL binn_is_valid(void *ptr, int *ptype, int *pcount, int *psize);
BOOL binn_is_valid_ex(void *ptr, int *ptype, int *pcount, int *psize);
BOOL binn_is_struct(void *ptr);
BOOL binn_load(void *data, binn *item);
binn *binn_open(void *data);
signed char binn_list_int8(void *list, int pos);
short binn_list_int16(void *list, int pos);
int binn_list_int32(void *list, int pos);
int64 binn_list_int64(void *list, int pos);
unsigned char binn_list_uint8(void *list, int pos);
unsigned short binn_list_uint16(void *list, int pos);
unsigned int binn_list_uint32(void *list, int pos);
uint64 binn_list_uint64(void *list, int pos);
float binn_list_float(void *list, int pos);
double binn_list_double(void *list, int pos);
BOOL binn_list_bool(void *list, int pos);
BOOL binn_list_null(void *list, int pos);
char *binn_list_str(void *list, int pos);
void *binn_list_blob(void *list, int pos, int *psize);
void *binn_list_list(void *list, int pos);
void *binn_list_map(void *list, int pos);
void *binn_list_object(void *list, int pos);
signed char binn_map_int8(void *map, int id);
short binn_map_int16(void *map, int id);
int binn_map_int32(void *map, int id);
int64 binn_map_int64(void *map, int id);
unsigned char binn_map_uint8(void *map, int id);
unsigned short binn_map_uint16(void *map, int id);
unsigned int binn_map_uint32(void *map, int id);
uint64 binn_map_uint64(void *map, int id);
float binn_map_float(void *map, int id);
double binn_map_double(void *map, int id);
BOOL binn_map_bool(void *map, int id);
BOOL binn_map_null(void *map, int id);
char *binn_map_str(void *map, int id);
void *binn_map_blob(void *map, int id, int *psize);
void *binn_map_list(void *map, int id);
void *binn_map_map(void *map, int id);
void *binn_map_object(void *map, int id);
signed char binn_object_int8(void *obj, const char *key);
short binn_object_int16(void *obj, const char *key);
int binn_object_int32(void *obj, const char *key);
int64 binn_object_int64(void *obj, const char *key);
unsigned char binn_object_uint8(void *obj, const char *key);
unsigned short binn_object_uint16(void *obj, const char *key);
unsigned int binn_object_uint32(void *obj, const char *key);
uint64 binn_object_uint64(void *obj, const char *key);
float binn_object_float(void *obj, const char *key);
double binn_object_double(void *obj, const char *key);
BOOL binn_object_bool(void *obj, const char *key);
BOOL binn_object_null(void *obj, const char *key);
char *binn_object_str(void *obj, const char *key);
void *binn_object_blob(void *obj, const char *key, int *psize);
void *binn_object_list(void *obj, const char *key);
void *binn_object_map(void *obj, const char *key);
void *binn_object_object(void *obj, const char *key);
binn *binn_list_value(void *list, int pos);
binn *binn_map_value(void *map, int id);
binn *binn_object_value(void *obj, const char *key);
BOOL binn_list_get_value(void *list, int pos, binn *value);
BOOL binn_map_get_value(void *map, int id, binn *value);
BOOL binn_object_get_value(void *obj, const char *key, binn *value);
BOOL binn_list_get(void *list, int pos, int type, void *pvalue, int *psize);
BOOL binn_map_get(void *map, int id, int type, void *pvalue, int *psize);
BOOL binn_object_get(void *obj, const char *key, int type, void *pvalue, int *psize);
void *binn_list_read(void *list, int pos, int *ptype, int *psize);
void *binn_map_read(void *map, int id, int *ptype, int *psize);
void *binn_object_read(void *obj, const char *key, int *ptype, int *psize);
BOOL binn_map_get_pair(void *map, int pos, int *pid, binn *value);
BOOL binn_object_get_pair(void *obj, int pos, char *pkey, binn *value);
binn *binn_map_pair(void *map, int pos, int *pid);
binn *binn_object_pair(void *obj, int pos, char *pkey);
void *binn_map_read_pair(void *ptr, int pos, int *pid, int *ptype, int *psize);
void *binn_object_read_pair(void *ptr, int pos, char *pkey, int *ptype, int *psize);
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter;
BOOL binn_iter_init(binn_iter *iter, void *pbuf, int type);
binn *binn_list_next_value(binn_iter *iter);
binn *binn_map_next_value(binn_iter *iter, int *pid);
binn *binn_object_next_value(binn_iter *iter, char *pkey);
BOOL binn_list_next(binn_iter *iter, binn *value);
BOOL binn_map_next(binn_iter *iter, int *pid, binn *value);
BOOL binn_object_next(binn_iter *iter, char *pkey, binn *value);
void *binn_list_read_next(binn_iter *iter, int *ptype, int *psize);
void *binn_map_read_next(binn_iter *iter, int *pid, int *ptype, int *psize);
void *binn_object_read_next(binn_iter *iter, char *pkey, int *ptype, int *psize);
BOOL binn_set_string(binn *item, char *str, binn_mem_free pfree);
BOOL binn_set_blob(binn *item, void *ptr, int size, binn_mem_free pfree);
inline static BOOL binn_list_add_int8(binn *list, signed char value)
{
  return binn_list_add(list, 0x21, &value, 0);
}

inline static BOOL binn_list_add_int16(binn *list, short value)
{
  return binn_list_add(list, 0x41, &value, 0);
}

inline static BOOL binn_list_add_int32(binn *list, int value)
{
  return binn_list_add(list, 0x61, &value, 0);
}

inline static BOOL binn_list_add_int64(binn *list, int64 value)
{
  return binn_list_add(list, 0x81, &value, 0);
}

inline static BOOL binn_list_add_uint8(binn *list, unsigned char value)
{
  return binn_list_add(list, 0x20, &value, 0);
}

inline static BOOL binn_list_add_uint16(binn *list, unsigned short value)
{
  return binn_list_add(list, 0x40, &value, 0);
}

inline static BOOL binn_list_add_uint32(binn *list, unsigned int value)
{
  return binn_list_add(list, 0x60, &value, 0);
}

inline static BOOL binn_list_add_uint64(binn *list, uint64 value)
{
  return binn_list_add(list, 0x80, &value, 0);
}

inline static BOOL binn_list_add_float(binn *list, float value)
{
  return binn_list_add(list, 0x62, &value, 0);
}

inline static BOOL binn_list_add_double(binn *list, double value)
{
  return binn_list_add(list, 0x82, &value, 0);
}

inline static BOOL binn_list_add_bool(binn *list, BOOL value)
{
  return binn_list_add(list, 0x80061, &value, 0);
}

inline static BOOL binn_list_add_null(binn *list)
{
  return binn_list_add(list, 0x00, 0, 0);
}

inline static BOOL binn_list_add_str(binn *list, char *str)
{
  return binn_list_add(list, 0xA0, str, 0);
}

inline static BOOL binn_list_add_blob(binn *list, void *ptr, int size)
{
  return binn_list_add(list, 0xC0, ptr, size);
}

inline static BOOL binn_list_add_list(binn *list, void *list2)
{
  return binn_list_add(list, 0xE0, binn_ptr(list2), binn_size(list2));
}

inline static BOOL binn_list_add_map(binn *list, void *map)
{
  return binn_list_add(list, 0xE1, binn_ptr(map), binn_size(map));
}

inline static BOOL binn_list_add_object(binn *list, void *obj)
{
  return binn_list_add(list, 0xE2, binn_ptr(obj), binn_size(obj));
}

inline static BOOL binn_list_add_value(binn *list, binn *value)
{
  return binn_list_add(list, value->type, binn_ptr(value), binn_size(value));
}

inline static BOOL binn_map_set_int8(binn *map, int id, signed char value)
{
  return binn_map_set(map, id, 0x21, &value, 0);
}

inline static BOOL binn_map_set_int16(binn *map, int id, short value)
{
  return binn_map_set(map, id, 0x41, &value, 0);
}

inline static BOOL binn_map_set_int32(binn *map, int id, int value)
{
  return binn_map_set(map, id, 0x61, &value, 0);
}

inline static BOOL binn_map_set_int64(binn *map, int id, int64 value)
{
  return binn_map_set(map, id, 0x81, &value, 0);
}

inline static BOOL binn_map_set_uint8(binn *map, int id, unsigned char value)
{
  return binn_map_set(map, id, 0x20, &value, 0);
}

inline static BOOL binn_map_set_uint16(binn *map, int id, unsigned short value)
{
  return binn_map_set(map, id, 0x40, &value, 0);
}

inline static BOOL binn_map_set_uint32(binn *map, int id, unsigned int value)
{
  return binn_map_set(map, id, 0x60, &value, 0);
}

inline static BOOL binn_map_set_uint64(binn *map, int id, uint64 value)
{
  return binn_map_set(map, id, 0x80, &value, 0);
}

inline static BOOL binn_map_set_float(binn *map, int id, float value)
{
  return binn_map_set(map, id, 0x62, &value, 0);
}

inline static BOOL binn_map_set_double(binn *map, int id, double value)
{
  return binn_map_set(map, id, 0x82, &value, 0);
}

inline static BOOL binn_map_set_bool(binn *map, int id, BOOL value)
{
  return binn_map_set(map, id, 0x80061, &value, 0);
}

inline static BOOL binn_map_set_null(binn *map, int id)
{
  return binn_map_set(map, id, 0x00, 0, 0);
}

inline static BOOL binn_map_set_str(binn *map, int id, char *str)
{
  return binn_map_set(map, id, 0xA0, str, 0);
}

inline static BOOL binn_map_set_blob(binn *map, int id, void *ptr, int size)
{
  return binn_map_set(map, id, 0xC0, ptr, size);
}

inline static BOOL binn_map_set_list(binn *map, int id, void *list)
{
  return binn_map_set(map, id, 0xE0, binn_ptr(list), binn_size(list));
}

inline static BOOL binn_map_set_map(binn *map, int id, void *map2)
{
  return binn_map_set(map, id, 0xE1, binn_ptr(map2), binn_size(map2));
}

inline static BOOL binn_map_set_object(binn *map, int id, void *obj)
{
  return binn_map_set(map, id, 0xE2, binn_ptr(obj), binn_size(obj));
}

inline static BOOL binn_map_set_value(binn *map, int id, binn *value)
{
  return binn_map_set(map, id, value->type, binn_ptr(value), binn_size(value));
}

inline static BOOL binn_object_set_int8(binn *obj, const char *key, signed char value)
{
  return binn_object_set(obj, key, 0x21, &value, 0);
}

inline static BOOL binn_object_set_int16(binn *obj, const char *key, short value)
{
  return binn_object_set(obj, key, 0x41, &value, 0);
}

inline static BOOL binn_object_set_int32(binn *obj, const char *key, int value)
{
  return binn_object_set(obj, key, 0x61, &value, 0);
}

inline static BOOL binn_object_set_int64(binn *obj, const char *key, int64 value)
{
  return binn_object_set(obj, key, 0x81, &value, 0);
}

inline static BOOL binn_object_set_uint8(binn *obj, const char *key, unsigned char value)
{
  return binn_object_set(obj, key, 0x20, &value, 0);
}

inline static BOOL binn_object_set_uint16(binn *obj, const char *key, unsigned short value)
{
  return binn_object_set(obj, key, 0x40, &value, 0);
}

inline static BOOL binn_object_set_uint32(binn *obj, const char *key, unsigned int value)
{
  return binn_object_set(obj, key, 0x60, &value, 0);
}

inline static BOOL binn_object_set_uint64(binn *obj, const char *key, uint64 value)
{
  return binn_object_set(obj, key, 0x80, &value, 0);
}

inline static BOOL binn_object_set_float(binn *obj, const char *key, float value)
{
  return binn_object_set(obj, key, 0x62, &value, 0);
}

inline static BOOL binn_object_set_double(binn *obj, const char *key, double value)
{
  return binn_object_set(obj, key, 0x82, &value, 0);
}

inline static BOOL binn_object_set_bool(binn *obj, const char *key, BOOL value)
{
  return binn_object_set(obj, key, 0x80061, &value, 0);
}

inline static BOOL binn_object_set_null(binn *obj, const char *key)
{
  return binn_object_set(obj, key, 0x00, 0, 0);
}

inline static BOOL binn_object_set_str(binn *obj, const char *key, char *str)
{
  return binn_object_set(obj, key, 0xA0, str, 0);
}

inline static BOOL binn_object_set_blob(binn *obj, const char *key, void *ptr, int size)
{
  return binn_object_set(obj, key, 0xC0, ptr, size);
}

inline static BOOL binn_object_set_list(binn *obj, const char *key, void *list)
{
  return binn_object_set(obj, key, 0xE0, binn_ptr(list), binn_size(list));
}

inline static BOOL binn_object_set_map(binn *obj, const char *key, void *map)
{
  return binn_object_set(obj, key, 0xE1, binn_ptr(map), binn_size(map));
}

inline static BOOL binn_object_set_object(binn *obj, const char *key, void *obj2)
{
  return binn_object_set(obj, key, 0xE2, binn_ptr(obj2), binn_size(obj2));
}

inline static BOOL binn_object_set_value(binn *obj, const char *key, binn *value)
{
  return binn_object_set(obj, key, value->type, binn_ptr(value), binn_size(value));
}

inline static BOOL binn_list_get_int8(void *list, int pos, signed char *pvalue)
{
  return binn_list_get(list, pos, 0x21, pvalue, 0);
}

inline static BOOL binn_list_get_int16(void *list, int pos, short *pvalue)
{
  return binn_list_get(list, pos, 0x41, pvalue, 0);
}

inline static BOOL binn_list_get_int32(void *list, int pos, int *pvalue)
{
  return binn_list_get(list, pos, 0x61, pvalue, 0);
}

inline static BOOL binn_list_get_int64(void *list, int pos, int64 *pvalue)
{
  return binn_list_get(list, pos, 0x81, pvalue, 0);
}

inline static BOOL binn_list_get_uint8(void *list, int pos, unsigned char *pvalue)
{
  return binn_list_get(list, pos, 0x20, pvalue, 0);
}

inline static BOOL binn_list_get_uint16(void *list, int pos, unsigned short *pvalue)
{
  return binn_list_get(list, pos, 0x40, pvalue, 0);
}

inline static BOOL binn_list_get_uint32(void *list, int pos, unsigned int *pvalue)
{
  return binn_list_get(list, pos, 0x60, pvalue, 0);
}

inline static BOOL binn_list_get_uint64(void *list, int pos, uint64 *pvalue)
{
  return binn_list_get(list, pos, 0x80, pvalue, 0);
}

inline static BOOL binn_list_get_float(void *list, int pos, float *pvalue)
{
  return binn_list_get(list, pos, 0x62, pvalue, 0);
}

inline static BOOL binn_list_get_double(void *list, int pos, double *pvalue)
{
  return binn_list_get(list, pos, 0x82, pvalue, 0);
}

inline static BOOL binn_list_get_bool(void *list, int pos, BOOL *pvalue)
{
  return binn_list_get(list, pos, 0x80061, pvalue, 0);
}

inline static BOOL binn_list_get_str(void *list, int pos, char **pvalue)
{
  return binn_list_get(list, pos, 0xA0, pvalue, 0);
}

inline static BOOL binn_list_get_blob(void *list, int pos, void **pvalue, int *psize)
{
  return binn_list_get(list, pos, 0xC0, pvalue, psize);
}

inline static BOOL binn_list_get_list(void *list, int pos, void **pvalue)
{
  return binn_list_get(list, pos, 0xE0, pvalue, 0);
}

inline static BOOL binn_list_get_map(void *list, int pos, void **pvalue)
{
  return binn_list_get(list, pos, 0xE1, pvalue, 0);
}

inline static BOOL binn_list_get_object(void *list, int pos, void **pvalue)
{
  return binn_list_get(list, pos, 0xE2, pvalue, 0);
}

inline static BOOL binn_map_get_int8(void *map, int id, signed char *pvalue)
{
  return binn_map_get(map, id, 0x21, pvalue, 0);
}

inline static BOOL binn_map_get_int16(void *map, int id, short *pvalue)
{
  return binn_map_get(map, id, 0x41, pvalue, 0);
}

inline static BOOL binn_map_get_int32(void *map, int id, int *pvalue)
{
  return binn_map_get(map, id, 0x61, pvalue, 0);
}

inline static BOOL binn_map_get_int64(void *map, int id, int64 *pvalue)
{
  return binn_map_get(map, id, 0x81, pvalue, 0);
}

inline static BOOL binn_map_get_uint8(void *map, int id, unsigned char *pvalue)
{
  return binn_map_get(map, id, 0x20, pvalue, 0);
}

inline static BOOL binn_map_get_uint16(void *map, int id, unsigned short *pvalue)
{
  return binn_map_get(map, id, 0x40, pvalue, 0);
}

inline static BOOL binn_map_get_uint32(void *map, int id, unsigned int *pvalue)
{
  return binn_map_get(map, id, 0x60, pvalue, 0);
}

inline static BOOL binn_map_get_uint64(void *map, int id, uint64 *pvalue)
{
  return binn_map_get(map, id, 0x80, pvalue, 0);
}

inline static BOOL binn_map_get_float(void *map, int id, float *pvalue)
{
  return binn_map_get(map, id, 0x62, pvalue, 0);
}

inline static BOOL binn_map_get_double(void *map, int id, double *pvalue)
{
  return binn_map_get(map, id, 0x82, pvalue, 0);
}

inline static BOOL binn_map_get_bool(void *map, int id, BOOL *pvalue)
{
  return binn_map_get(map, id, 0x80061, pvalue, 0);
}

inline static BOOL binn_map_get_str(void *map, int id, char **pvalue)
{
  return binn_map_get(map, id, 0xA0, pvalue, 0);
}

inline static BOOL binn_map_get_blob(void *map, int id, void **pvalue, int *psize)
{
  return binn_map_get(map, id, 0xC0, pvalue, psize);
}

inline static BOOL binn_map_get_list(void *map, int id, void **pvalue)
{
  return binn_map_get(map, id, 0xE0, pvalue, 0);
}

inline static BOOL binn_map_get_map(void *map, int id, void **pvalue)
{
  return binn_map_get(map, id, 0xE1, pvalue, 0);
}

inline static BOOL binn_map_get_object(void *map, int id, void **pvalue)
{
  return binn_map_get(map, id, 0xE2, pvalue, 0);
}

inline static BOOL binn_object_get_int8(void *obj, const char *key, signed char *pvalue)
{
  return binn_object_get(obj, key, 0x21, pvalue, 0);
}

inline static BOOL binn_object_get_int16(void *obj, const char *key, short *pvalue)
{
  return binn_object_get(obj, key, 0x41, pvalue, 0);
}

inline static BOOL binn_object_get_int32(void *obj, const char *key, int *pvalue)
{
  return binn_object_get(obj, key, 0x61, pvalue, 0);
}

inline static BOOL binn_object_get_int64(void *obj, const char *key, int64 *pvalue)
{
  return binn_object_get(obj, key, 0x81, pvalue, 0);
}

inline static BOOL binn_object_get_uint8(void *obj, const char *key, unsigned char *pvalue)
{
  return binn_object_get(obj, key, 0x20, pvalue, 0);
}

inline static BOOL binn_object_get_uint16(void *obj, const char *key, unsigned short *pvalue)
{
  return binn_object_get(obj, key, 0x40, pvalue, 0);
}

inline static BOOL binn_object_get_uint32(void *obj, const char *key, unsigned int *pvalue)
{
  return binn_object_get(obj, key, 0x60, pvalue, 0);
}

inline static BOOL binn_object_get_uint64(void *obj, const char *key, uint64 *pvalue)
{
  return binn_object_get(obj, key, 0x80, pvalue, 0);
}

inline static BOOL binn_object_get_float(void *obj, const char *key, float *pvalue)
{
  return binn_object_get(obj, key, 0x62, pvalue, 0);
}

inline static BOOL binn_object_get_double(void *obj, const char *key, double *pvalue)
{
  return binn_object_get(obj, key, 0x82, pvalue, 0);
}

inline static BOOL binn_object_get_bool(void *obj, const char *key, BOOL *pvalue)
{
  return binn_object_get(obj, key, 0x80061, pvalue, 0);
}

inline static BOOL binn_object_get_str(void *obj, const char *key, char **pvalue)
{
  return binn_object_get(obj, key, 0xA0, pvalue, 0);
}

inline static BOOL binn_object_get_blob(void *obj, const char *key, void **pvalue, int *psize)
{
  return binn_object_get(obj, key, 0xC0, pvalue, psize);
}

inline static BOOL binn_object_get_list(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE0, pvalue, 0);
}

inline static BOOL binn_object_get_map(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE1, pvalue, 0);
}

inline static BOOL binn_object_get_object(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE2, pvalue, 0);
}

BOOL binn_get_int32(binn *value, int *pint);
BOOL binn_get_int64(binn *value, int64 *pint);
BOOL binn_get_double(binn *value, double *pfloat);
BOOL binn_get_bool(binn *value, BOOL *pbool);
char *binn_get_str(binn *value);
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long long int u64;
extern void *(*malloc_fn)(int len);
extern void *(*realloc_fn)(void *ptr, int len);
extern void (*free_fn)(void *ptr);
void test_binn_version()
{
  char *version = binn_version();
  assert(version);
  assert(strcmp(version, "3.0.0") == 0);
}

static void copy_be16(u16 *pdest, u16 *psource);
static void copy_be32(u32 *pdest, u32 *psource);
static void copy_be64(u64 *pdest, u64 *psource);
void test_endianess()
{
  u16 vshort1;
  u16 vshort2;
  u16 vshort3;
  u32 vint1;
  u32 vint2;
  u32 vint3;
  u64 value1;
  u64 value2;
  u64 value3;
  printf("testing endianess... ");
  vshort1 = 0x1122;
  copy_be16(&vshort2, &vshort1);
  assert(vshort2 == 0x2211);
  copy_be16(&vshort3, &vshort2);
  assert(vshort3 == vshort1);
  vshort1 = 0xF123;
  copy_be16(&vshort2, &vshort1);
  assert(vshort2 == 0x23F1);
  copy_be16(&vshort3, &vshort2);
  assert(vshort3 == vshort1);
  vshort1 = 0x0123;
  copy_be16(&vshort2, &vshort1);
  assert(vshort2 == 0x2301);
  copy_be16(&vshort3, &vshort2);
  assert(vshort3 == vshort1);
  vint1 = 0x11223344;
  copy_be32(&vint2, &vint1);
  assert(vint2 == 0x44332211);
  copy_be32(&vint3, &vint2);
  assert(vint3 == vint1);
  vint1 = 0xF1234580;
  copy_be32(&vint2, &vint1);
  assert(vint2 == 0x804523F1);
  copy_be32(&vint3, &vint2);
  assert(vint3 == vint1);
  vint1 = 0x00112233;
  copy_be32(&vint2, &vint1);
  assert(vint2 == 0x33221100);
  copy_be32(&vint3, &vint2);
  assert(vint3 == vint1);
  value1 = 0x1122334455667788;
  copy_be64(&value2, &value1);
  assert(value2 == 0x8877665544332211);
  copy_be64(&value3, &value2);
  assert(value3 == value1);
  printf("OK\n");
}

void *memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}

char *i64toa(int64 value, char *buf, int radix)
{
  switch (radix)
  {
    case 10:
    {
      snprintf(buf, 64, "%lli", value);
      break;
    }

    case 16:
    {
      snprintf(buf, 64, "%llx", value);
      break;
    }

    default:
    {
      buf[0] = 0;
    }

  }

  return buf;
}

void pass_int64(int64 a)
{
  assert(a == 9223372036854775807);
  assert(a > 9223372036854775806);
}

int64 return_int64()
{
  return 9223372036854775807;
}

int64 return_passed_int64(int64 a)
{
  return a;
}

void test_int64()
{
  int64 i64;
  char buf[64];
  printf("testing int64... ");
  pass_int64(9223372036854775807);
  i64 = return_int64();
  assert(i64 == 9223372036854775807);
  i64toa(i64, buf, 10);
  assert(strcmp(buf, "9223372036854775807") == 0);
  i64 = return_passed_int64(-987654321987654321);
  assert(i64 == (-987654321987654321));
  i64toa(i64, buf, 10);
  assert(strcmp(buf, "-987654321987654321") == 0);
  printf("OK\n");
}

BOOL AlmostEqualFloats(float A, float B, int maxUlps)
{
  int aInt;
  int bInt;
  int intDiff;
  assert((maxUlps > 0) && (maxUlps < ((4 * 1024) * 1024)));
  aInt = *((int *) (&A));
  bInt = *((int *) (&B));
  if (aInt < 0)
  {
    aInt = 0x80000000 - aInt;
  }
  if (bInt < 0)
  {
    bInt = 0x80000000 - bInt;
  }
  intDiff = abs(aInt - bInt);
  if (intDiff <= maxUlps)
  {
    return 1;
  }
  return 0;
}

BOOL AlmostEqualDoubles(double a, double b)
{
  double absDiff;
  double maxAbs;
  double absA;
  double absB;
  absDiff = fabs(a - b);
  if (absDiff < 1.0E-150)
  {
    return 1;
  }
  absA = fabs(a);
  absB = fabs(b);
  maxAbs = (absA > absB) ? (absA) : (absB);
  if ((absDiff / maxAbs) < 1.0E-8)
  {
    return 1;
  }
  printf("a=%g b=%g\n", a, b);
  return 0;
}

void test_floating_point_numbers()
{
  char buf[256];
  float f1;
  double d1;
  printf("testing floating point... ");
  f1 = 1.25;
  assert(f1 == 1.25);
  d1 = 1.25;
  assert(d1 == 1.25);
  d1 = 0;
  d1 = f1;
  assert(d1 == 1.25);
  f1 = 0;
  f1 = d1;
  assert(f1 == 1.25);
  d1 = 1.234;
  assert(AlmostEqualDoubles(d1, 1.234) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.234, 2) == 1);
  d1 = 1.2345;
  assert(AlmostEqualDoubles(d1, 1.2345) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.2345, 2) == 1);
  d1 = atof("1.234");
  assert(AlmostEqualDoubles(d1, 1.234) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.234, 2) == 1);
  sprintf(buf, "%g", d1);
  assert(buf[0] != 0);
  assert(strcmp(buf, "1.234") == 0);
  d1 = atof("12.34");
  assert(d1 == 12.34);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 12.34, 2) == 1);
  sprintf(buf, "%g", d1);
  assert(buf[0] != 0);
  assert(strcmp(buf, "12.34") == 0);
  d1 = atof("1.234e25");
  assert(AlmostEqualDoubles(d1, 1.234e25) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.234e25, 2) == 1);
  sprintf(buf, "%g", d1);
  assert(buf[0] != 0);
  printf("OK\n");
}

void print_binn(binn *map)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  int size;
  int i;
  p_idx = binn_ptr(map);
  size = binn_size(map);
  for (i = 0; i < size; i += 1)
  {
    printf("%02x ", p[i + p_idx]);
  }

  puts("");
}

void test1()
{
  static const int fix_size = 512;
  int i;
  int blobsize;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *p2;
  unsigned int p2_idx = 0;
  binn *obj1;
  unsigned int obj1_idx = 0;
  binn *list;
  unsigned int list_idx = 0;
  binn *map;
  unsigned int map_idx = 0;
  binn *obj;
  unsigned int obj_idx = 0;
  binn value;
  char vbyte;
  char *pblob;
  unsigned int pblob_idx = 0;
  signed short vint16;
  unsigned short vuint16;
  signed int vint32;
  unsigned int vuint32;
  signed long long int vint64;
  unsigned long long int vuint64;
  printf("testing binn 1... ");
  assert(CalcAllocation(512, 512) == 512);
  assert(CalcAllocation(510, 512) == 512);
  assert(CalcAllocation(1, 512) == 512);
  assert(CalcAllocation(0, 512) == 512);
  assert(CalcAllocation(513, 512) == 1024);
  assert(CalcAllocation(512 + 256, 512) == 1024);
  assert(CalcAllocation(1025, 512) == 2048);
  assert(CalcAllocation(1025, 1024) == 2048);
  assert(CalcAllocation(2100, 1024) == 4096);
  assert(binn_new(-1, 0, 0) == 0);
  assert(binn_new(0, 0, 0) == 0);
  assert(binn_new(5, 0, 0) == 0);
  assert(binn_new(0xE1, -1, 0) == 0);
  ptr_idx = (char *) (&(&obj1[obj1_idx]));
  assert(binn_new(0xE1, -1, ptr) == 0);
  assert(binn_new(0xE1, 3 - 1, ptr) == 0);
  obj1_idx = binn_new(0xE0, 0, 0);
  assert((&obj1[obj1_idx]) != 0);
  assert(obj1->header == 0x1F22B11F);
  assert(obj1->type == 0xE0);
  assert(obj1->count == 0);
  assert(obj1->pbuf != 0);
  assert(obj1->alloc_size > 9);
  assert(obj1->used_size == 9);
  assert(obj1->pre_allocated == 0);
  binn_free(obj1);
  list_idx = binn_new(0xE0, 0, 0);
  assert((&list[list_idx]) != 0);
  map_idx = binn_new(0xE1, 0, 0);
  assert((&map[map_idx]) != 0);
  obj_idx = binn_new(0xE2, 0, 0);
  assert((&obj[obj_idx]) != 0);
  assert(list->header == 0x1F22B11F);
  assert(list->type == 0xE0);
  assert(list->count == 0);
  assert(list->pbuf != 0);
  assert(list->alloc_size > 9);
  assert(list->used_size == 9);
  assert(list->pre_allocated == 0);
  assert(map->header == 0x1F22B11F);
  assert(map->type == 0xE1);
  assert(map->count == 0);
  assert(map->pbuf != 0);
  assert(map->alloc_size > 9);
  assert(map->used_size == 9);
  assert(map->pre_allocated == 0);
  assert(obj->header == 0x1F22B11F);
  assert(obj->type == 0xE2);
  assert(obj->count == 0);
  assert(obj->pbuf != 0);
  assert(obj->alloc_size > 9);
  assert(obj->used_size == 9);
  assert(obj->pre_allocated == 0);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  obj1_idx = binn_new(0xE2, fix_size, ptr);
  assert((&obj1[obj1_idx]) != 0);
  assert(obj1->header == 0x1F22B11F);
  assert(obj1->type == 0xE2);
  assert(obj1->count == 0);
  assert(obj1->pbuf != 0);
  assert(obj1->alloc_size == fix_size);
  assert(obj1->used_size == 9);
  assert(obj1->pre_allocated == 1);
  assert(binn_map_set(list, 55001, 0x61, &i, 0) == 0);
  assert(binn_object_set(list, "test", 0x61, &i, 0) == 0);
  assert(binn_list_add(map, 0x61, &i, 0) == 0);
  assert(binn_object_set(map, "test", 0x61, &i, 0) == 0);
  assert(binn_list_add(obj, 0x61, &i, 0) == 0);
  assert(binn_map_set(obj, 55001, 0x61, &i, 0) == 0);
  assert(binn_list_add(list, -1, &i, 0) == 0);
  assert(binn_list_add(list, 0x1FFFF, &i, 0) == 0);
  assert(binn_map_set(map, 5501, -1, &i, 0) == 0);
  assert(binn_map_set(map, 5501, 0x1FFFF, &i, 0) == 0);
  assert(binn_object_set(obj, "test", -1, &i, 0) == 0);
  assert(binn_object_set(obj, "test", 0x1FFFF, &i, 0) == 0);
  assert(binn_list_add(list, 0x21, 0, 0) == 0);
  assert(binn_list_add(list, 0x41, 0, 0) == 0);
  assert(binn_list_add(list, 0x61, 0, 0) == 0);
  assert(binn_list_add(list, 0x81, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x21, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x41, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x61, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x81, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x21, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x41, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x61, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x81, 0, 0) == 0);
  assert(binn_list_add(list, 0xC0, 0, -1) == 0);
  assert(binn_list_add(list, 0xC0, 0, 10) == 0);
  assert(binn_map_set(map, 5501, 0xC0, 0, -1) == 0);
  assert(binn_map_set(map, 5501, 0xC0, 0, 10) == 0);
  assert(binn_object_set(obj, "test", 0xC0, 0, -1) == 0);
  assert(binn_object_set(obj, "test", 0xC0, 0, 10) == 0);
  assert(binn_list_add(list, 0xC0, &i, -1) == 0);
  assert(binn_list_add(list, 0xC0, &i, -15) == 0);
  assert(binn_map_set(map, 5501, 0xC0, &i, -1) == 0);
  assert(binn_map_set(map, 5501, 0xC0, &i, -15) == 0);
  assert(binn_object_set(obj, "test", 0xC0, &i, -1) == 0);
  assert(binn_object_set(obj, "test", 0xC0, &i, -15) == 0);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_value(ptr, 0, &value) == 0);
  assert(binn_list_get_value(ptr, 1, &value) == 0);
  assert(binn_list_get_value(ptr, 2, &value) == 0);
  assert(binn_list_get_value(ptr, -1, &value) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_value(ptr, 0, &value) == 0);
  assert(binn_list_get_value(ptr, 1, &value) == 0);
  assert(binn_list_get_value(ptr, 2, &value) == 0);
  assert(binn_list_get_value(ptr, -1, &value) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_value(ptr, 0, &value) == 0);
  assert(binn_list_get_value(ptr, 1, &value) == 0);
  assert(binn_list_get_value(ptr, 2, &value) == 0);
  assert(binn_list_get_value(ptr, -1, &value) == 0);
  i = 0x1234;
  assert(binn_list_add(list, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 1);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 0);
  vbyte = 255;
  vint16 = -32000;
  vuint16 = 65000;
  vint32 = -65000000;
  vuint32 = 65000000;
  vint64 = -6500000000000000;
  vuint64 = 6500000000000000;
  blobsize = 150;
  pblob_idx = malloc(blobsize);
  assert((&pblob[pblob_idx]) != 0);
  memset(pblob, 55, blobsize);
  assert(binn_list_add(list, 0x00, 0, 0) == 1);
  assert(binn_list_add(list, 0x20, &vbyte, 0) == 1);
  assert(binn_list_add(list, 0x41, &vint16, 0) == 1);
  assert(binn_list_add(list, 0x40, &vuint16, 0) == 1);
  assert(binn_list_add(list, 0x61, &vint32, 0) == 1);
  assert(binn_list_add(list, 0x60, &vuint32, 0) == 1);
  assert(binn_list_add(list, 0x81, &vint64, 0) == 1);
  assert(binn_list_add(list, 0x80, &vuint64, 0) == 1);
  assert(binn_list_add(list, 0xA0, "this is the string", 0) == 1);
  assert(binn_list_add(list, 0xC0, pblob, blobsize) == 1);
  assert(binn_map_set(map, 99000, 0x00, 0, 0) == 1);
  assert(binn_map_set(map, 99001, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 99002, 0x41, &vint16, 0) == 1);
  assert(binn_map_set(map, 99003, 0x40, &vuint16, 0) == 1);
  assert(binn_map_set(map, 99004, 0x61, &vint32, 0) == 1);
  assert(binn_map_set(map, 99005, 0x60, &vuint32, 0) == 1);
  assert(binn_map_set(map, 99006, 0x81, &vint64, 0) == 1);
  assert(binn_map_set(map, 99007, 0x80, &vuint64, 0) == 1);
  assert(binn_map_set(map, 99008, 0xA0, "this is the string", 0) == 1);
  assert(binn_map_set(map, 99009, 0xC0, pblob, blobsize) == 1);
  assert(binn_object_set(obj, "key0", 0x00, 0, 0) == 1);
  assert(binn_object_set(obj, "key1", 0x20, &vbyte, 0) == 1);
  assert(binn_object_set(obj, "key2", 0x41, &vint16, 0) == 1);
  assert(binn_object_set(obj, "key3", 0x40, &vuint16, 0) == 1);
  assert(binn_object_set(obj, "key4", 0x61, &vint32, 0) == 1);
  assert(binn_object_set(obj, "key5", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj, "key6", 0x81, &vint64, 0) == 1);
  assert(binn_object_set(obj, "key7", 0x80, &vuint64, 0) == 1);
  assert(binn_object_set(obj, "key8", 0xA0, "this is the string", 0) == 1);
  assert(binn_object_set(obj, "key9", 0xC0, pblob, blobsize) == 1);
  assert(binn_list_add(list, 0xC0, ptr, 0) == 1);
  assert(binn_list_add(list, 0xA0, "", 0) == 1);
  assert(binn_list_add(list, 0xA0, "after the empty items", 0) == 1);
  assert(binn_map_set(map, 0x09, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x3F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x4F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0xFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0xFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0xFFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x7FFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x09, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x3F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x4F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0xFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0xFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0xFFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x7FFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x09, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0x3F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0x4F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0xFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0xFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0xFFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0x7FFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x09, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x3F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x4F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0xFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0xFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0xFFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x7FFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_list_add(obj1, 0x61, &i, 0) == 0);
  assert(binn_map_set(obj1, 55001, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 0);
  assert(binn_object_set(obj1, "key1", 0xA0, "this is the value", 0) == 1);
  assert(binn_object_set(obj1, "key2", 0xA0, "the second value", 0) == 1);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  p2_idx = &ptr[ptr_idx];
  for (i = 0; i < (fix_size - 1); i += 1)
  {
    p2[p2_idx] = 'A';
    p2_idx += 1;
  }

  p2[p2_idx] = '\0';
  assert(strlen(ptr) == (fix_size - 1));
  assert(binn_object_set(obj1, "v2", 0xA0, ptr, 0) == 0);
  assert(binn_object_set(obj, "v2", 0xA0, ptr, 0) == 1);
  assert(binn_object_set(obj, "Key00", 0xA0, "after the big string", 0) == 1);
  free(ptr);
  ptr_idx = 0;
  assert(binn_object_set(obj, "list", 0xE0, binn_ptr(list), binn_size(list)) == 1);
  assert(binn_object_set(obj, "Key10", 0xA0, "after the list", 0) == 1);
  assert(binn_size(0) == 0);
  assert(binn_size(list) == list->size);
  assert(binn_size(map) == map->size);
  assert(binn_size(obj) == obj->size);
  assert(binn_size(obj1) == obj1->size);
  binn_free(list);
  binn_free(map);
  binn_free(obj);
  binn_free(obj1);
  printf("OK\n");
}

void test2(BOOL use_int_compression)
{
  binn *list = 0;
  unsigned int list_idx = 0;
  binn *map = 0;
  unsigned int map_idx = 0;
  binn *obj = 0;
  unsigned int obj_idx = 0;
  binn value;
  BOOL vbool;
  int blobsize;
  char *pblob;
  unsigned int pblob_idx = 0;
  char *pstr;
  unsigned int pstr_idx = 0;
  signed int vint32;
  double vdouble;
  char *str_list = "test list";
  char *str_map = "test map";
  char *str_obj = "test object";
  printf("testing binn 2 (use_int_compression = %d)... ", use_int_compression);
  blobsize = 150;
  pblob_idx = malloc(blobsize);
  assert((&pblob[pblob_idx]) != 0);
  memset(pblob, 55, blobsize);
  assert((&list[list_idx]) == 0);
  assert((&map[map_idx]) == 0);
  assert((&obj[obj_idx]) == 0);
  assert(binn_list_add_int32(list, 123) == 0);
  assert(binn_map_set_int32(map, 1001, 456) == 0);
  assert(binn_object_set_int32(obj, "int", 789) == 0);
  list_idx = binn_list();
  map_idx = binn_map();
  obj_idx = binn_object();
  assert((&list[list_idx]) != 0);
  assert((&map[map_idx]) != 0);
  assert((&obj[obj_idx]) != 0);
  if (use_int_compression == 0)
  {
    list->disable_int_compression = 1;
    map->disable_int_compression = 1;
    obj->disable_int_compression = 1;
  }
  assert(binn_list_add_int32(list, 123) == 1);
  assert(binn_map_set_int32(map, 1001, 456) == 1);
  assert(binn_object_set_int32(obj, "int", 789) == 1);
  assert(list->header == 0x1F22B11F);
  assert(list->type == 0xE0);
  assert(list->count == 1);
  assert(list->pbuf != 0);
  assert(list->alloc_size > 9);
  assert(list->used_size > 9);
  assert(list->pre_allocated == 0);
  assert(map->header == 0x1F22B11F);
  assert(map->type == 0xE1);
  assert(map->count == 1);
  assert(map->pbuf != 0);
  assert(map->alloc_size > 9);
  assert(map->used_size > 9);
  assert(map->pre_allocated == 0);
  assert(obj->header == 0x1F22B11F);
  assert(obj->type == 0xE2);
  assert(obj->count == 1);
  assert(obj->pbuf != 0);
  assert(obj->alloc_size > 9);
  assert(obj->used_size > 9);
  assert(obj->pre_allocated == 0);
  assert(binn_list_add_double(list, 1.23) == 1);
  assert(binn_map_set_double(map, 1002, 4.56) == 1);
  assert(binn_object_set_double(obj, "double", 7.89) == 1);
  assert(list->count == 2);
  assert(map->count == 2);
  assert(obj->count == 2);
  assert(binn_list_add_bool(list, 1) == 1);
  assert(binn_map_set_bool(map, 1003, 1) == 1);
  assert(binn_object_set_bool(obj, "bool", 1) == 1);
  assert(list->count == 3);
  assert(map->count == 3);
  assert(obj->count == 3);
  assert(binn_list_add_str(list, str_list) == 1);
  assert(binn_map_set_str(map, 1004, str_map) == 1);
  assert(binn_object_set_str(obj, "text", str_obj) == 1);
  assert(list->count == 4);
  assert(map->count == 4);
  assert(obj->count == 4);
  assert(binn_list_add_blob(list, pblob, blobsize) == 1);
  assert(binn_map_set_blob(map, 1005, pblob, blobsize) == 1);
  assert(binn_object_set_blob(obj, "blob", pblob, blobsize) == 1);
  assert(list->count == 5);
  assert(map->count == 5);
  assert(obj->count == 5);
  assert(binn_count(list) == 5);
  assert(binn_count(map) == 5);
  assert(binn_count(obj) == 5);
  assert(binn_size(list) == list->size);
  assert(binn_size(map) == map->size);
  assert(binn_size(obj) == obj->size);
  assert(binn_type(list) == 0xE0);
  assert(binn_type(map) == 0xE1);
  assert(binn_type(obj) == 0xE2);
  assert(binn_list_get_value(list, 1, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.allocated == 0);
  if (use_int_compression)
  {
    assert(value.type == 0x20);
    assert(value.ptr != (&value.vuint8));
  }
  else
  {
    assert(value.type == 0x61);
    assert(value.ptr == (&value.vint));
  }
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vint == 123);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1001, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  if (use_int_compression)
  {
    assert(value.type == 0x40);
    assert(value.ptr == (&value.vuint16));
  }
  else
  {
    assert(value.type == 0x61);
    assert(value.ptr == (&value.vint));
  }
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vint == 456);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "int", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  if (use_int_compression)
  {
    assert(value.type == 0x40);
    assert(value.ptr == (&value.vuint16));
  }
  else
  {
    assert(value.type == 0x61);
    assert(value.ptr == (&value.vint));
  }
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vint == 789);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 2, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x82);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vdouble == 1.23);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1002, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x82);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vdouble == 4.56);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "double", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x82);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vdouble == 7.89);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 3, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x80061);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vbool == 1);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1003, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x80061);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vbool == 1);
  assert(binn_object_get_value(obj, "bool", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x80061);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vbool == 1);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 4, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xA0);
  assert(value.ptr != 0);
  assert(value.size == strlen(str_list));
  assert(strcmp(value.ptr, str_list) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1004, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xA0);
  assert(value.size == strlen(str_map));
  assert(strcmp(value.ptr, str_map) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "text", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xA0);
  assert(value.size == strlen(str_obj));
  assert(strcmp(value.ptr, str_obj) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 5, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xC0);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1005, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xC0);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "blob", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xC0);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_int32(list, 1, &vint32) == 1);
  assert(vint32 == 123);
  assert(binn_map_get_int32(map, 1001, &vint32) == 1);
  assert(vint32 == 456);
  assert(binn_object_get_int32(obj, "int", &vint32) == 1);
  assert(vint32 == 789);
  assert(binn_list_get_double(list, 2, &vdouble) == 1);
  assert(vdouble == 1.23);
  assert(binn_map_get_double(map, 1002, &vdouble) == 1);
  assert(vdouble == 4.56);
  assert(binn_object_get_double(obj, "double", &vdouble) == 1);
  assert(vdouble == 7.89);
  assert(binn_list_get_bool(list, 3, &vbool) == 1);
  assert(vbool == 1);
  assert(binn_map_get_bool(map, 1003, &vbool) == 1);
  assert(vbool == 1);
  assert(binn_object_get_bool(obj, "bool", &vbool) == 1);
  assert(vbool == 1);
  assert(binn_list_get_str(list, 4, &(&pstr[pstr_idx])) == 1);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_list) == 0);
  assert(binn_map_get_str(map, 1004, &(&pstr[pstr_idx])) == 1);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_map) == 0);
  assert(binn_object_get_str(obj, "text", &(&pstr[pstr_idx])) == 1);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_obj) == 0);
  value.ptr = 0;
  value.size = 0;
  assert(binn_list_get_blob(list, 5, &value.ptr, &value.size) == 1);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = 0;
  value.size = 0;
  assert(binn_map_get_blob(map, 1005, &value.ptr, &value.size) == 1);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = 0;
  value.size = 0;
  assert(binn_object_get_blob(obj, "blob", &value.ptr, &value.size) == 1);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(binn_list_int32(list, 1) == 123);
  assert(binn_map_int32(map, 1001) == 456);
  assert(binn_object_int32(obj, "int") == 789);
  assert(binn_list_double(list, 2) == 1.23);
  assert(binn_map_double(map, 1002) == 4.56);
  assert(binn_object_double(obj, "double") == 7.89);
  assert(binn_list_bool(list, 3) == 1);
  assert(binn_map_bool(map, 1003) == 1);
  assert(binn_object_bool(obj, "bool") == 1);
  pstr_idx = binn_list_str(list, 4);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_list) == 0);
  pstr_idx = binn_map_str(map, 1004);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_map) == 0);
  pstr_idx = binn_object_str(obj, "text");
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_obj) == 0);
  value.ptr = binn_list_blob(list, 5, &value.size);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = binn_map_blob(map, 1005, &value.size);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = binn_object_blob(obj, "blob", &value.size);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  binn_free(list);
  binn_free(map);
  binn_free(obj);
  printf("OK\n");
}

void test3()
{
  static const int fix_size = 512;
  int i;
  int id;
  int type;
  int count;
  int size;
  int header_size;
  int blobsize;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *p2;
  unsigned int p2_idx = 0;
  char *pstr;
  unsigned int pstr_idx = 0;
  char key[256];
  binn *list;
  unsigned int list_idx = 0;
  binn *map;
  unsigned int map_idx = 0;
  binn *obj;
  unsigned int obj_idx = 0;
  binn *obj1;
  unsigned int obj1_idx = 0;
  binn value;
  char vbyte;
  char *pblob;
  unsigned int pblob_idx = 0;
  signed short vint16;
  signed short *pint16;
  unsigned int pint16_idx = 0;
  unsigned short vuint16;
  unsigned short *puint16;
  unsigned int puint16_idx = 0;
  signed int vint32;
  signed int *pint32;
  unsigned int pint32_idx = 0;
  unsigned int vuint32;
  unsigned int *puint32;
  unsigned int puint32_idx = 0;
  signed long long int vint64;
  signed long long int *pint64;
  unsigned int pint64_idx = 0;
  unsigned long long int vuint64;
  unsigned long long int *puint64;
  unsigned int puint64_idx = 0;
  printf("testing binn 3... ");
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  map_idx = binn_map();
  assert((&map[map_idx]) != 0);
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  assert(list->header == 0x1F22B11F);
  assert(list->type == 0xE0);
  assert(list->count == 0);
  assert(list->pbuf != 0);
  assert(list->alloc_size > 9);
  assert(list->used_size == 9);
  assert(list->pre_allocated == 0);
  assert(map->header == 0x1F22B11F);
  assert(map->type == 0xE1);
  assert(map->count == 0);
  assert(map->pbuf != 0);
  assert(map->alloc_size > 9);
  assert(map->used_size == 9);
  assert(map->pre_allocated == 0);
  assert(obj->header == 0x1F22B11F);
  assert(obj->type == 0xE2);
  assert(obj->count == 0);
  assert(obj->pbuf != 0);
  assert(obj->alloc_size > 9);
  assert(obj->used_size == 9);
  assert(obj->pre_allocated == 0);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  obj1_idx = binn_new(0xE2, fix_size, ptr);
  assert((&obj1[obj1_idx]) != 0);
  assert(obj1->header == 0x1F22B11F);
  assert(obj1->type == 0xE2);
  assert(obj1->count == 0);
  assert(obj1->pbuf != 0);
  assert(obj1->alloc_size == fix_size);
  assert(obj1->used_size == 9);
  assert(obj1->pre_allocated == 1);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_read(ptr, 0, &type, &size) == 0);
  assert(binn_list_read(ptr, 1, &type, &size) == 0);
  assert(binn_list_read(ptr, 2, &type, &size) == 0);
  assert(binn_list_read(ptr, -1, &type, &size) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_map_read(ptr, 0, &type, &size) == 0);
  assert(binn_map_read(ptr, 55001, &type, &size) == 0);
  assert(binn_map_read(ptr, -1, &type, &size) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_object_read(ptr, 0, &type, &size) == 0);
  assert(binn_object_read(ptr, "", &type, &size) == 0);
  assert(binn_object_read(ptr, "test", &type, &size) == 0);
  assert(binn_list_add(list, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 1);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 0);
  vbyte = 255;
  vint16 = -32000;
  vuint16 = 65000;
  vint32 = -65000000;
  vuint32 = 65000000;
  vint64 = -6500000000000000;
  vuint64 = 6500000000000000;
  blobsize = 150;
  pblob_idx = malloc(blobsize);
  assert((&pblob[pblob_idx]) != 0);
  memset(pblob, 55, blobsize);
  assert(binn_list_add(list, 0x00, 0, 0) == 1);
  assert(binn_list_add(list, 0x20, &vbyte, 0) == 1);
  assert(binn_list_add(list, 0x41, &vint16, 0) == 1);
  assert(binn_list_add(list, 0x40, &vuint16, 0) == 1);
  assert(binn_list_add(list, 0x61, &vint32, 0) == 1);
  assert(binn_list_add(list, 0x60, &vuint32, 0) == 1);
  assert(binn_list_add(list, 0x81, &vint64, 0) == 1);
  assert(binn_list_add(list, 0x80, &vuint64, 0) == 1);
  assert(binn_list_add(list, 0xA0, "this is the string", 0) == 1);
  assert(binn_list_add(list, 0xC0, pblob, blobsize) == 1);
  assert(binn_map_set(map, 99000, 0x00, 0, 0) == 1);
  assert(binn_map_set(map, 99001, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 99002, 0x41, &vint16, 0) == 1);
  assert(binn_map_set(map, 99003, 0x40, &vuint16, 0) == 1);
  assert(binn_map_set(map, 99004, 0x61, &vint32, 0) == 1);
  assert(binn_map_set(map, 99005, 0x60, &vuint32, 0) == 1);
  assert(binn_map_set(map, 99006, 0x81, &vint64, 0) == 1);
  assert(binn_map_set(map, 99007, 0x80, &vuint64, 0) == 1);
  assert(binn_map_set(map, 99008, 0xA0, "this is the string", 0) == 1);
  assert(binn_map_set(map, 99009, 0xC0, pblob, blobsize) == 1);
  assert(binn_object_set(obj, "key0", 0x00, 0, 0) == 1);
  assert(binn_object_set(obj, "key1", 0x20, &vbyte, 0) == 1);
  assert(binn_object_set(obj, "key2", 0x41, &vint16, 0) == 1);
  assert(binn_object_set(obj, "key3", 0x40, &vuint16, 0) == 1);
  assert(binn_object_set(obj, "key4", 0x61, &vint32, 0) == 1);
  assert(binn_object_set(obj, "key5", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj, "key6", 0x81, &vint64, 0) == 1);
  assert(binn_object_set(obj, "key7", 0x80, &vuint64, 0) == 1);
  assert(binn_object_set(obj, "key8", 0xA0, "this is the string", 0) == 1);
  assert(binn_object_set(obj, "key9", 0xC0, pblob, blobsize) == 1);
  assert(binn_list_add(list, 0xC0, ptr, 0) == 1);
  assert(binn_list_add(list, 0xA0, "", 0) == 1);
  assert(binn_list_add(list, 0xA0, "after the empty items", 0) == 1);
  assert(binn_list_add(obj1, 0x61, &i, 0) == 0);
  assert(binn_map_set(obj1, 55001, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 0);
  assert(binn_object_set(obj1, "key1", 0xA0, "this is the value", 0) == 1);
  assert(binn_object_set(obj1, "key2", 0xA0, "the second value", 0) == 1);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  p2_idx = &ptr[ptr_idx];
  for (i = 0; i < (fix_size - 1); i += 1)
  {
    p2[p2_idx] = 'A';
    p2_idx += 1;
  }

  p2[p2_idx] = '\0';
  assert(strlen(ptr) == (fix_size - 1));
  assert(binn_object_set(obj1, "v2", 0xA0, ptr, 0) == 0);
  assert(binn_object_set(obj, "v2", 0xA0, ptr, 0) == 1);
  assert(binn_object_set(obj, "Key00", 0xA0, "after the big string", 0) == 1);
  free(ptr);
  ptr_idx = 0;
  assert(binn_object_set(obj, "list", 0xE0, binn_ptr(list), binn_size(list)) == 1);
  assert(binn_object_set(obj, "Key10", 0xA0, "after the list", 0) == 1);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_map_get_pair(ptr, -1, &id, &value) == 0);
  assert(binn_map_get_pair(ptr, 0, &id, &value) == 0);
  assert(binn_map_get_pair(ptr, 1, &id, &value) == 1);
  assert(id == 5501);
  assert(binn_map_get_pair(ptr, 2, &id, &value) == 1);
  assert(id == 99000);
  assert(binn_map_get_pair(ptr, 3, &id, &value) == 1);
  assert(id == 99001);
  assert(binn_map_get_pair(ptr, 10, &id, &value) == 1);
  assert(id == 99008);
  assert(binn_map_get_pair(ptr, 11, &id, &value) == 1);
  assert(id == 99009);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_object_get_pair(ptr, -1, key, &value) == 0);
  assert(binn_object_get_pair(ptr, 0, key, &value) == 0);
  assert(binn_object_get_pair(ptr, 1, key, &value) == 1);
  assert(strcmp(key, "test") == 0);
  assert(binn_object_get_pair(ptr, 2, key, &value) == 1);
  assert(strcmp(key, "key0") == 0);
  assert(binn_object_get_pair(ptr, 3, key, &value) == 1);
  assert(strcmp(key, "key1") == 0);
  assert(binn_object_get_pair(ptr, 10, key, &value) == 1);
  assert(strcmp(key, "key8") == 0);
  assert(binn_object_get_pair(ptr, 11, key, &value) == 1);
  assert(strcmp(key, "key9") == 0);
  ptr_idx = binn_ptr(obj1);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key1", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the value") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key2", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "the second value") == 0);
  type = 0;
  size = 0;
  pint32_idx = binn_object_read(ptr, "test", &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x60);
  assert(pint32[pint32_idx] == vuint32);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(ptr, 2, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0x00);
  type = 0;
  size = 0;
  p2_idx = binn_list_read(ptr, 3, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0x20);
  assert(p2[p2_idx] == vbyte);
  type = 0;
  size = 0;
  pint16_idx = binn_list_read(ptr, 4, &type, &size);
  assert((&pint16[pint16_idx]) != 0);
  assert(type == 0x41);
  assert(pint16[pint16_idx] == vint16);
  type = 0;
  size = 0;
  puint16_idx = binn_list_read(ptr, 5, &type, &size);
  assert((&puint16[puint16_idx]) != 0);
  assert(type == 0x40);
  assert(puint16[puint16_idx] == vuint16);
  type = 0;
  size = 0;
  pint32_idx = binn_list_read(ptr, 6, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  pint32_idx = binn_list_read(ptr, 6, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  puint32_idx = binn_list_read(ptr, 7, &type, &size);
  assert((&puint32[puint32_idx]) != 0);
  assert(type == 0x60);
  assert(puint32[puint32_idx] == vuint32);
  type = 0;
  size = 0;
  pint64_idx = binn_list_read(ptr, 8, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  pint64_idx = binn_list_read(ptr, 8, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  puint64_idx = binn_list_read(ptr, 9, &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(ptr, 10, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_list_read(ptr, 11, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xC0);
  assert(size == blobsize);
  assert(memcmp(p2, pblob, blobsize) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_map_read(ptr, 99000, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0x00);
  type = 0;
  size = 0;
  p2_idx = binn_map_read(ptr, 99001, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0x20);
  assert(p2[p2_idx] == vbyte);
  type = 0;
  size = 0;
  pint16_idx = binn_map_read(ptr, 99002, &type, &size);
  assert((&pint16[pint16_idx]) != 0);
  assert(type == 0x41);
  assert(pint16[pint16_idx] == vint16);
  type = 0;
  size = 0;
  puint16_idx = binn_map_read(ptr, 99003, &type, &size);
  assert((&puint16[puint16_idx]) != 0);
  assert(type == 0x40);
  assert(puint16[puint16_idx] == vuint16);
  type = 0;
  size = 0;
  pint32_idx = binn_map_read(ptr, 99004, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  pint32_idx = binn_map_read(ptr, 99004, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  puint32_idx = binn_map_read(ptr, 99005, &type, &size);
  assert((&puint32[puint32_idx]) != 0);
  assert(type == 0x60);
  assert(puint32[puint32_idx] == vuint32);
  type = 0;
  size = 0;
  pint64_idx = binn_map_read(ptr, 99006, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  pint64_idx = binn_map_read(ptr, 99006, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  puint64_idx = binn_map_read(ptr, 99007, &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_map_read(ptr, 99008, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_map_read(ptr, 99009, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xC0);
  assert(size == blobsize);
  assert(memcmp(p2, pblob, blobsize) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key0", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0x00);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "key1", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0x20);
  assert(p2[p2_idx] == vbyte);
  type = 0;
  size = 0;
  pint16_idx = binn_object_read(ptr, "key2", &type, &size);
  assert((&pint16[pint16_idx]) != 0);
  assert(type == 0x41);
  assert(pint16[pint16_idx] == vint16);
  type = 0;
  size = 0;
  puint16_idx = binn_object_read(ptr, "key3", &type, &size);
  assert((&puint16[puint16_idx]) != 0);
  assert(type == 0x40);
  assert(puint16[puint16_idx] == vuint16);
  type = 0;
  size = 0;
  pint32_idx = binn_object_read(ptr, "key4", &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  pint32_idx = binn_object_read(ptr, "key4", &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  puint32_idx = binn_object_read(ptr, "key5", &type, &size);
  assert((&puint32[puint32_idx]) != 0);
  assert(type == 0x60);
  assert(puint32[puint32_idx] == vuint32);
  type = 0;
  size = 0;
  pint64_idx = binn_object_read(ptr, "key6", &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  pint64_idx = binn_object_read(ptr, "key6", &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  puint64_idx = binn_object_read(ptr, "key7", &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key8", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "key9", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xC0);
  assert(size == blobsize);
  assert(memcmp(p2, pblob, blobsize) == 0);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "v2", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xA0);
  assert(size == (fix_size - 1));
  assert(strlen(p2) == (fix_size - 1));
  assert(p2[0 + p2_idx] == 'A');
  assert(p2[1 + p2_idx] == 'A');
  assert(p2[500 + p2_idx] == 'A');
  assert(p2[(fix_size - 1) + p2_idx] == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key00", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "after the big string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "list", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xE0);
  assert(size > 0);
  type = 0;
  size = 0;
  puint64_idx = binn_list_read(p2, 9, &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 10, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 12, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xC0);
  assert(size == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 13, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size == 0);
  assert(strcmp(pstr, "") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 14, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "after the empty items") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key10", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "after the list") == 0);
  assert(binn_ptr(0) == 0);
  assert(IsValidBinnHeader(0) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  size = 0;
  assert(IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 1);
  assert(type == 0xE2);
  assert(count == 15);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == obj->size);
  assert(binn_is_valid(ptr, &type, &count, &size) == 1);
  assert(type == 0xE2);
  assert(count == 15);
  assert(size > 3);
  assert(size == obj->size);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  size = 0;
  assert(IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 1);
  assert(type == 0xE1);
  assert(count == 11);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == map->size);
  assert(binn_is_valid(ptr, &type, &count, &size) == 1);
  assert(type == 0xE1);
  assert(count == 11);
  assert(size > 3);
  assert(size == map->size);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  size = 0;
  assert(IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 1);
  assert(type == 0xE0);
  assert(count == 14);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == list->size);
  assert(binn_is_valid(ptr, &type, &count, &size) == 1);
  assert(type == 0xE0);
  assert(count == 14);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == list->size);
  assert(binn_size(0) == 0);
  assert(binn_size(list) == list->size);
  assert(binn_size(map) == map->size);
  assert(binn_size(obj) == obj->size);
  assert(binn_size(obj1) == obj1->size);
  binn_free(list);
  binn_free(map);
  binn_free(obj);
  printf("OK\n");
}

void test_invalid_binn()
{
  char buffers[][20] = {{0xE0}, {0xE0, 0x7E}, {0xE0, 0x7E, 0x7F}, {0xE0, 0x7E, 0x7F, 0x12}, {0xE0, 0x7E, 0x7F, 0x12, 0x34}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0x01}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0x7F}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12}, {0xE0, 0x7E, 0xFF, 0x12, 0x34}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0x01}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0x7F}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x8E}, {0xE0, 0x8E, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12}, {0xE0, 0x8E, 0xFF, 0x12, 0x34}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0x01}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0x7F}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
  int count;
  int size;
  int i;
  char *ptr;
  unsigned int ptr_idx = 0;
  puts("testing invalid binn buffers...");
  count = (sizeof(buffers)) / (sizeof(buffers[0]));
  for (i = 0; i < count; i += 1)
  {
    ptr_idx = buffers[i];
    size = strlen(ptr);
    printf("checking invalid binn #%d   size: %d bytes\n", i, size);
    assert(binn_is_valid_ex(ptr, 0, 0, &size) == 0);
  }

  puts("OK");
}

int main()
{
  puts("\nStarting the unit/regression tests...\n");
  printf("sizeof(binn) = %d\n\n", sizeof(binn));
  test_binn_version();
  test_endianess();
  test_int64();
  test_floating_point_numbers();
  test1();
  test2(0);
  test2(1);
  test_binn2();
  test3();
  test_invalid_binn();
  puts("\nAll tests pass! :)\n");
  return 0;
}


typedef int BOOL;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef void (*binn_mem_free)(void *);
struct binn_struct
{
  int header;
  BOOL allocated;
  BOOL writable;
  BOOL dirty;
  void *pbuf;
  BOOL pre_allocated;
  int alloc_size;
  int used_size;
  int type;
  void *ptr;
  int size;
  int count;
  binn_mem_free freefn;
  union 
  {
    signed char vint8;
    signed short vint16;
    signed int vint32;
    int64 vint64;
    unsigned char vuint8;
    unsigned short vuint16;
    unsigned int vuint32;
    uint64 vuint64;
    signed char vchar;
    unsigned char vuchar;
    signed short vshort;
    unsigned short vushort;
    signed int vint;
    unsigned int vuint;
    float vfloat;
    double vdouble;
    BOOL vbool;
  };
  BOOL disable_int_compression;
};
typedef struct binn_struct binn;
char *binn_version();
void binn_set_alloc_functions(void *(*new_malloc)(size_t), void *(*new_realloc)(void *, size_t), void (*new_free)(void *));
int binn_create_type(int storage_type, int data_type_index);
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type);
int binn_get_write_storage(int type);
int binn_get_read_storage(int type);
BOOL binn_is_container(binn *item);
binn *binn_new(int type, int size, void *buffer);
binn *binn_list();
binn *binn_map();
binn *binn_object();
BOOL binn_create(binn *item, int type, int size, void *buffer);
BOOL binn_create_list(binn *list);
BOOL binn_create_map(binn *map);
BOOL binn_create_object(binn *object);
binn *binn_copy(void *old);
BOOL binn_list_add_new(binn *list, binn *value);
BOOL binn_map_set_new(binn *map, int id, binn *value);
BOOL binn_object_set_new(binn *obj, const char *key, binn *value);
BOOL binn_list_add(binn *list, int type, void *pvalue, int size);
BOOL binn_map_set(binn *map, int id, int type, void *pvalue, int size);
BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size);
void binn_free(binn *item);
void *binn_release(binn *item);
binn *binn_value(int type, void *pvalue, int size, binn_mem_free freefn);
inline static binn *binn_int8(signed char value)
{
  return binn_value(0x21, &value, 0, 0);
}

inline static binn *binn_int16(short value)
{
  return binn_value(0x41, &value, 0, 0);
}

inline static binn *binn_int32(int value)
{
  return binn_value(0x61, &value, 0, 0);
}

inline static binn *binn_int64(int64 value)
{
  return binn_value(0x81, &value, 0, 0);
}

inline static binn *binn_uint8(unsigned char value)
{
  return binn_value(0x20, &value, 0, 0);
}

inline static binn *binn_uint16(unsigned short value)
{
  return binn_value(0x40, &value, 0, 0);
}

inline static binn *binn_uint32(unsigned int value)
{
  return binn_value(0x60, &value, 0, 0);
}

inline static binn *binn_uint64(uint64 value)
{
  return binn_value(0x80, &value, 0, 0);
}

inline static binn *binn_float(float value)
{
  return binn_value(0x62, &value, 0, 0);
}

inline static binn *binn_double(double value)
{
  return binn_value(0x82, &value, 0, 0);
}

inline static binn *binn_bool(BOOL value)
{
  return binn_value(0x80061, &value, 0, 0);
}

inline static binn *binn_null()
{
  return binn_value(0x00, 0, 0, 0);
}

inline static binn *binn_string(char *str, binn_mem_free freefn)
{
  return binn_value(0xA0, str, 0, freefn);
}

inline static binn *binn_blob(void *ptr, int size, binn_mem_free freefn)
{
  return binn_value(0xC0, ptr, size, freefn);
}

void *binn_ptr(void *ptr);
int binn_size(void *ptr);
int binn_type(void *ptr);
int binn_count(void *ptr);
BOOL binn_is_valid(void *ptr, int *ptype, int *pcount, int *psize);
BOOL binn_is_valid_ex(void *ptr, int *ptype, int *pcount, int *psize);
BOOL binn_is_struct(void *ptr);
BOOL binn_load(void *data, binn *item);
binn *binn_open(void *data);
signed char binn_list_int8(void *list, int pos);
short binn_list_int16(void *list, int pos);
int binn_list_int32(void *list, int pos);
int64 binn_list_int64(void *list, int pos);
unsigned char binn_list_uint8(void *list, int pos);
unsigned short binn_list_uint16(void *list, int pos);
unsigned int binn_list_uint32(void *list, int pos);
uint64 binn_list_uint64(void *list, int pos);
float binn_list_float(void *list, int pos);
double binn_list_double(void *list, int pos);
BOOL binn_list_bool(void *list, int pos);
BOOL binn_list_null(void *list, int pos);
char *binn_list_str(void *list, int pos);
void *binn_list_blob(void *list, int pos, int *psize);
void *binn_list_list(void *list, int pos);
void *binn_list_map(void *list, int pos);
void *binn_list_object(void *list, int pos);
signed char binn_map_int8(void *map, int id);
short binn_map_int16(void *map, int id);
int binn_map_int32(void *map, int id);
int64 binn_map_int64(void *map, int id);
unsigned char binn_map_uint8(void *map, int id);
unsigned short binn_map_uint16(void *map, int id);
unsigned int binn_map_uint32(void *map, int id);
uint64 binn_map_uint64(void *map, int id);
float binn_map_float(void *map, int id);
double binn_map_double(void *map, int id);
BOOL binn_map_bool(void *map, int id);
BOOL binn_map_null(void *map, int id);
char *binn_map_str(void *map, int id);
void *binn_map_blob(void *map, int id, int *psize);
void *binn_map_list(void *map, int id);
void *binn_map_map(void *map, int id);
void *binn_map_object(void *map, int id);
signed char binn_object_int8(void *obj, const char *key);
short binn_object_int16(void *obj, const char *key);
int binn_object_int32(void *obj, const char *key);
int64 binn_object_int64(void *obj, const char *key);
unsigned char binn_object_uint8(void *obj, const char *key);
unsigned short binn_object_uint16(void *obj, const char *key);
unsigned int binn_object_uint32(void *obj, const char *key);
uint64 binn_object_uint64(void *obj, const char *key);
float binn_object_float(void *obj, const char *key);
double binn_object_double(void *obj, const char *key);
BOOL binn_object_bool(void *obj, const char *key);
BOOL binn_object_null(void *obj, const char *key);
char *binn_object_str(void *obj, const char *key);
void *binn_object_blob(void *obj, const char *key, int *psize);
void *binn_object_list(void *obj, const char *key);
void *binn_object_map(void *obj, const char *key);
void *binn_object_object(void *obj, const char *key);
binn *binn_list_value(void *list, int pos);
binn *binn_map_value(void *map, int id);
binn *binn_object_value(void *obj, const char *key);
BOOL binn_list_get_value(void *list, int pos, binn *value);
BOOL binn_map_get_value(void *map, int id, binn *value);
BOOL binn_object_get_value(void *obj, const char *key, binn *value);
BOOL binn_list_get(void *list, int pos, int type, void *pvalue, int *psize);
BOOL binn_map_get(void *map, int id, int type, void *pvalue, int *psize);
BOOL binn_object_get(void *obj, const char *key, int type, void *pvalue, int *psize);
void *binn_list_read(void *list, int pos, int *ptype, int *psize);
void *binn_map_read(void *map, int id, int *ptype, int *psize);
void *binn_object_read(void *obj, const char *key, int *ptype, int *psize);
BOOL binn_map_get_pair(void *map, int pos, int *pid, binn *value);
BOOL binn_object_get_pair(void *obj, int pos, char *pkey, binn *value);
binn *binn_map_pair(void *map, int pos, int *pid);
binn *binn_object_pair(void *obj, int pos, char *pkey);
void *binn_map_read_pair(void *ptr, int pos, int *pid, int *ptype, int *psize);
void *binn_object_read_pair(void *ptr, int pos, char *pkey, int *ptype, int *psize);
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter;
BOOL binn_iter_init(binn_iter *iter, void *pbuf, int type);
binn *binn_list_next_value(binn_iter *iter);
binn *binn_map_next_value(binn_iter *iter, int *pid);
binn *binn_object_next_value(binn_iter *iter, char *pkey);
BOOL binn_list_next(binn_iter *iter, binn *value);
BOOL binn_map_next(binn_iter *iter, int *pid, binn *value);
BOOL binn_object_next(binn_iter *iter, char *pkey, binn *value);
void *binn_list_read_next(binn_iter *iter, int *ptype, int *psize);
void *binn_map_read_next(binn_iter *iter, int *pid, int *ptype, int *psize);
void *binn_object_read_next(binn_iter *iter, char *pkey, int *ptype, int *psize);
BOOL binn_set_string(binn *item, char *str, binn_mem_free pfree);
BOOL binn_set_blob(binn *item, void *ptr, int size, binn_mem_free pfree);
inline static BOOL binn_list_add_int8(binn *list, signed char value)
{
  return binn_list_add(list, 0x21, &value, 0);
}

inline static BOOL binn_list_add_int16(binn *list, short value)
{
  return binn_list_add(list, 0x41, &value, 0);
}

inline static BOOL binn_list_add_int32(binn *list, int value)
{
  return binn_list_add(list, 0x61, &value, 0);
}

inline static BOOL binn_list_add_int64(binn *list, int64 value)
{
  return binn_list_add(list, 0x81, &value, 0);
}

inline static BOOL binn_list_add_uint8(binn *list, unsigned char value)
{
  return binn_list_add(list, 0x20, &value, 0);
}

inline static BOOL binn_list_add_uint16(binn *list, unsigned short value)
{
  return binn_list_add(list, 0x40, &value, 0);
}

inline static BOOL binn_list_add_uint32(binn *list, unsigned int value)
{
  return binn_list_add(list, 0x60, &value, 0);
}

inline static BOOL binn_list_add_uint64(binn *list, uint64 value)
{
  return binn_list_add(list, 0x80, &value, 0);
}

inline static BOOL binn_list_add_float(binn *list, float value)
{
  return binn_list_add(list, 0x62, &value, 0);
}

inline static BOOL binn_list_add_double(binn *list, double value)
{
  return binn_list_add(list, 0x82, &value, 0);
}

inline static BOOL binn_list_add_bool(binn *list, BOOL value)
{
  return binn_list_add(list, 0x80061, &value, 0);
}

inline static BOOL binn_list_add_null(binn *list)
{
  return binn_list_add(list, 0x00, 0, 0);
}

inline static BOOL binn_list_add_str(binn *list, char *str)
{
  return binn_list_add(list, 0xA0, str, 0);
}

inline static BOOL binn_list_add_blob(binn *list, void *ptr, int size)
{
  return binn_list_add(list, 0xC0, ptr, size);
}

inline static BOOL binn_list_add_list(binn *list, void *list2)
{
  return binn_list_add(list, 0xE0, binn_ptr(list2), binn_size(list2));
}

inline static BOOL binn_list_add_map(binn *list, void *map)
{
  return binn_list_add(list, 0xE1, binn_ptr(map), binn_size(map));
}

inline static BOOL binn_list_add_object(binn *list, void *obj)
{
  return binn_list_add(list, 0xE2, binn_ptr(obj), binn_size(obj));
}

inline static BOOL binn_list_add_value(binn *list, binn *value)
{
  return binn_list_add(list, value->type, binn_ptr(value), binn_size(value));
}

inline static BOOL binn_map_set_int8(binn *map, int id, signed char value)
{
  return binn_map_set(map, id, 0x21, &value, 0);
}

inline static BOOL binn_map_set_int16(binn *map, int id, short value)
{
  return binn_map_set(map, id, 0x41, &value, 0);
}

inline static BOOL binn_map_set_int32(binn *map, int id, int value)
{
  return binn_map_set(map, id, 0x61, &value, 0);
}

inline static BOOL binn_map_set_int64(binn *map, int id, int64 value)
{
  return binn_map_set(map, id, 0x81, &value, 0);
}

inline static BOOL binn_map_set_uint8(binn *map, int id, unsigned char value)
{
  return binn_map_set(map, id, 0x20, &value, 0);
}

inline static BOOL binn_map_set_uint16(binn *map, int id, unsigned short value)
{
  return binn_map_set(map, id, 0x40, &value, 0);
}

inline static BOOL binn_map_set_uint32(binn *map, int id, unsigned int value)
{
  return binn_map_set(map, id, 0x60, &value, 0);
}

inline static BOOL binn_map_set_uint64(binn *map, int id, uint64 value)
{
  return binn_map_set(map, id, 0x80, &value, 0);
}

inline static BOOL binn_map_set_float(binn *map, int id, float value)
{
  return binn_map_set(map, id, 0x62, &value, 0);
}

inline static BOOL binn_map_set_double(binn *map, int id, double value)
{
  return binn_map_set(map, id, 0x82, &value, 0);
}

inline static BOOL binn_map_set_bool(binn *map, int id, BOOL value)
{
  return binn_map_set(map, id, 0x80061, &value, 0);
}

inline static BOOL binn_map_set_null(binn *map, int id)
{
  return binn_map_set(map, id, 0x00, 0, 0);
}

inline static BOOL binn_map_set_str(binn *map, int id, char *str)
{
  return binn_map_set(map, id, 0xA0, str, 0);
}

inline static BOOL binn_map_set_blob(binn *map, int id, void *ptr, int size)
{
  return binn_map_set(map, id, 0xC0, ptr, size);
}

inline static BOOL binn_map_set_list(binn *map, int id, void *list)
{
  return binn_map_set(map, id, 0xE0, binn_ptr(list), binn_size(list));
}

inline static BOOL binn_map_set_map(binn *map, int id, void *map2)
{
  return binn_map_set(map, id, 0xE1, binn_ptr(map2), binn_size(map2));
}

inline static BOOL binn_map_set_object(binn *map, int id, void *obj)
{
  return binn_map_set(map, id, 0xE2, binn_ptr(obj), binn_size(obj));
}

inline static BOOL binn_map_set_value(binn *map, int id, binn *value)
{
  return binn_map_set(map, id, value->type, binn_ptr(value), binn_size(value));
}

inline static BOOL binn_object_set_int8(binn *obj, const char *key, signed char value)
{
  return binn_object_set(obj, key, 0x21, &value, 0);
}

inline static BOOL binn_object_set_int16(binn *obj, const char *key, short value)
{
  return binn_object_set(obj, key, 0x41, &value, 0);
}

inline static BOOL binn_object_set_int32(binn *obj, const char *key, int value)
{
  return binn_object_set(obj, key, 0x61, &value, 0);
}

inline static BOOL binn_object_set_int64(binn *obj, const char *key, int64 value)
{
  return binn_object_set(obj, key, 0x81, &value, 0);
}

inline static BOOL binn_object_set_uint8(binn *obj, const char *key, unsigned char value)
{
  return binn_object_set(obj, key, 0x20, &value, 0);
}

inline static BOOL binn_object_set_uint16(binn *obj, const char *key, unsigned short value)
{
  return binn_object_set(obj, key, 0x40, &value, 0);
}

inline static BOOL binn_object_set_uint32(binn *obj, const char *key, unsigned int value)
{
  return binn_object_set(obj, key, 0x60, &value, 0);
}

inline static BOOL binn_object_set_uint64(binn *obj, const char *key, uint64 value)
{
  return binn_object_set(obj, key, 0x80, &value, 0);
}

inline static BOOL binn_object_set_float(binn *obj, const char *key, float value)
{
  return binn_object_set(obj, key, 0x62, &value, 0);
}

inline static BOOL binn_object_set_double(binn *obj, const char *key, double value)
{
  return binn_object_set(obj, key, 0x82, &value, 0);
}

inline static BOOL binn_object_set_bool(binn *obj, const char *key, BOOL value)
{
  return binn_object_set(obj, key, 0x80061, &value, 0);
}

inline static BOOL binn_object_set_null(binn *obj, const char *key)
{
  return binn_object_set(obj, key, 0x00, 0, 0);
}

inline static BOOL binn_object_set_str(binn *obj, const char *key, char *str)
{
  return binn_object_set(obj, key, 0xA0, str, 0);
}

inline static BOOL binn_object_set_blob(binn *obj, const char *key, void *ptr, int size)
{
  return binn_object_set(obj, key, 0xC0, ptr, size);
}

inline static BOOL binn_object_set_list(binn *obj, const char *key, void *list)
{
  return binn_object_set(obj, key, 0xE0, binn_ptr(list), binn_size(list));
}

inline static BOOL binn_object_set_map(binn *obj, const char *key, void *map)
{
  return binn_object_set(obj, key, 0xE1, binn_ptr(map), binn_size(map));
}

inline static BOOL binn_object_set_object(binn *obj, const char *key, void *obj2)
{
  return binn_object_set(obj, key, 0xE2, binn_ptr(obj2), binn_size(obj2));
}

inline static BOOL binn_object_set_value(binn *obj, const char *key, binn *value)
{
  return binn_object_set(obj, key, value->type, binn_ptr(value), binn_size(value));
}

inline static BOOL binn_list_get_int8(void *list, int pos, signed char *pvalue)
{
  return binn_list_get(list, pos, 0x21, pvalue, 0);
}

inline static BOOL binn_list_get_int16(void *list, int pos, short *pvalue)
{
  return binn_list_get(list, pos, 0x41, pvalue, 0);
}

inline static BOOL binn_list_get_int32(void *list, int pos, int *pvalue)
{
  return binn_list_get(list, pos, 0x61, pvalue, 0);
}

inline static BOOL binn_list_get_int64(void *list, int pos, int64 *pvalue)
{
  return binn_list_get(list, pos, 0x81, pvalue, 0);
}

inline static BOOL binn_list_get_uint8(void *list, int pos, unsigned char *pvalue)
{
  return binn_list_get(list, pos, 0x20, pvalue, 0);
}

inline static BOOL binn_list_get_uint16(void *list, int pos, unsigned short *pvalue)
{
  return binn_list_get(list, pos, 0x40, pvalue, 0);
}

inline static BOOL binn_list_get_uint32(void *list, int pos, unsigned int *pvalue)
{
  return binn_list_get(list, pos, 0x60, pvalue, 0);
}

inline static BOOL binn_list_get_uint64(void *list, int pos, uint64 *pvalue)
{
  return binn_list_get(list, pos, 0x80, pvalue, 0);
}

inline static BOOL binn_list_get_float(void *list, int pos, float *pvalue)
{
  return binn_list_get(list, pos, 0x62, pvalue, 0);
}

inline static BOOL binn_list_get_double(void *list, int pos, double *pvalue)
{
  return binn_list_get(list, pos, 0x82, pvalue, 0);
}

inline static BOOL binn_list_get_bool(void *list, int pos, BOOL *pvalue)
{
  return binn_list_get(list, pos, 0x80061, pvalue, 0);
}

inline static BOOL binn_list_get_str(void *list, int pos, char **pvalue)
{
  return binn_list_get(list, pos, 0xA0, pvalue, 0);
}

inline static BOOL binn_list_get_blob(void *list, int pos, void **pvalue, int *psize)
{
  return binn_list_get(list, pos, 0xC0, pvalue, psize);
}

inline static BOOL binn_list_get_list(void *list, int pos, void **pvalue)
{
  return binn_list_get(list, pos, 0xE0, pvalue, 0);
}

inline static BOOL binn_list_get_map(void *list, int pos, void **pvalue)
{
  return binn_list_get(list, pos, 0xE1, pvalue, 0);
}

inline static BOOL binn_list_get_object(void *list, int pos, void **pvalue)
{
  return binn_list_get(list, pos, 0xE2, pvalue, 0);
}

inline static BOOL binn_map_get_int8(void *map, int id, signed char *pvalue)
{
  return binn_map_get(map, id, 0x21, pvalue, 0);
}

inline static BOOL binn_map_get_int16(void *map, int id, short *pvalue)
{
  return binn_map_get(map, id, 0x41, pvalue, 0);
}

inline static BOOL binn_map_get_int32(void *map, int id, int *pvalue)
{
  return binn_map_get(map, id, 0x61, pvalue, 0);
}

inline static BOOL binn_map_get_int64(void *map, int id, int64 *pvalue)
{
  return binn_map_get(map, id, 0x81, pvalue, 0);
}

inline static BOOL binn_map_get_uint8(void *map, int id, unsigned char *pvalue)
{
  return binn_map_get(map, id, 0x20, pvalue, 0);
}

inline static BOOL binn_map_get_uint16(void *map, int id, unsigned short *pvalue)
{
  return binn_map_get(map, id, 0x40, pvalue, 0);
}

inline static BOOL binn_map_get_uint32(void *map, int id, unsigned int *pvalue)
{
  return binn_map_get(map, id, 0x60, pvalue, 0);
}

inline static BOOL binn_map_get_uint64(void *map, int id, uint64 *pvalue)
{
  return binn_map_get(map, id, 0x80, pvalue, 0);
}

inline static BOOL binn_map_get_float(void *map, int id, float *pvalue)
{
  return binn_map_get(map, id, 0x62, pvalue, 0);
}

inline static BOOL binn_map_get_double(void *map, int id, double *pvalue)
{
  return binn_map_get(map, id, 0x82, pvalue, 0);
}

inline static BOOL binn_map_get_bool(void *map, int id, BOOL *pvalue)
{
  return binn_map_get(map, id, 0x80061, pvalue, 0);
}

inline static BOOL binn_map_get_str(void *map, int id, char **pvalue)
{
  return binn_map_get(map, id, 0xA0, pvalue, 0);
}

inline static BOOL binn_map_get_blob(void *map, int id, void **pvalue, int *psize)
{
  return binn_map_get(map, id, 0xC0, pvalue, psize);
}

inline static BOOL binn_map_get_list(void *map, int id, void **pvalue)
{
  return binn_map_get(map, id, 0xE0, pvalue, 0);
}

inline static BOOL binn_map_get_map(void *map, int id, void **pvalue)
{
  return binn_map_get(map, id, 0xE1, pvalue, 0);
}

inline static BOOL binn_map_get_object(void *map, int id, void **pvalue)
{
  return binn_map_get(map, id, 0xE2, pvalue, 0);
}

inline static BOOL binn_object_get_int8(void *obj, const char *key, signed char *pvalue)
{
  return binn_object_get(obj, key, 0x21, pvalue, 0);
}

inline static BOOL binn_object_get_int16(void *obj, const char *key, short *pvalue)
{
  return binn_object_get(obj, key, 0x41, pvalue, 0);
}

inline static BOOL binn_object_get_int32(void *obj, const char *key, int *pvalue)
{
  return binn_object_get(obj, key, 0x61, pvalue, 0);
}

inline static BOOL binn_object_get_int64(void *obj, const char *key, int64 *pvalue)
{
  return binn_object_get(obj, key, 0x81, pvalue, 0);
}

inline static BOOL binn_object_get_uint8(void *obj, const char *key, unsigned char *pvalue)
{
  return binn_object_get(obj, key, 0x20, pvalue, 0);
}

inline static BOOL binn_object_get_uint16(void *obj, const char *key, unsigned short *pvalue)
{
  return binn_object_get(obj, key, 0x40, pvalue, 0);
}

inline static BOOL binn_object_get_uint32(void *obj, const char *key, unsigned int *pvalue)
{
  return binn_object_get(obj, key, 0x60, pvalue, 0);
}

inline static BOOL binn_object_get_uint64(void *obj, const char *key, uint64 *pvalue)
{
  return binn_object_get(obj, key, 0x80, pvalue, 0);
}

inline static BOOL binn_object_get_float(void *obj, const char *key, float *pvalue)
{
  return binn_object_get(obj, key, 0x62, pvalue, 0);
}

inline static BOOL binn_object_get_double(void *obj, const char *key, double *pvalue)
{
  return binn_object_get(obj, key, 0x82, pvalue, 0);
}

inline static BOOL binn_object_get_bool(void *obj, const char *key, BOOL *pvalue)
{
  return binn_object_get(obj, key, 0x80061, pvalue, 0);
}

inline static BOOL binn_object_get_str(void *obj, const char *key, char **pvalue)
{
  return binn_object_get(obj, key, 0xA0, pvalue, 0);
}

inline static BOOL binn_object_get_blob(void *obj, const char *key, void **pvalue, int *psize)
{
  return binn_object_get(obj, key, 0xC0, pvalue, psize);
}

inline static BOOL binn_object_get_list(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE0, pvalue, 0);
}

inline static BOOL binn_object_get_map(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE1, pvalue, 0);
}

inline static BOOL binn_object_get_object(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE2, pvalue, 0);
}

BOOL binn_get_int32(binn *value, int *pint);
BOOL binn_get_int64(binn *value, int64 *pint);
BOOL binn_get_double(binn *value, double *pfloat);
BOOL binn_get_bool(binn *value, BOOL *pbool);
char *binn_get_str(binn *value);
typedef unsigned short int u16;
typedef unsigned int u32;
typedef unsigned long long int u64;
extern void *(*malloc_fn)(int len);
extern void *(*realloc_fn)(void *ptr, int len);
extern void (*free_fn)(void *ptr);
void test_binn_version()
{
  char *version = binn_version();
  assert(version);
  assert(strcmp(version, "3.0.0") == 0);
}

static void copy_be16(u16 *pdest, u16 *psource);
static void copy_be32(u32 *pdest, u32 *psource);
static void copy_be64(u64 *pdest, u64 *psource);
void test_endianess()
{
  u16 vshort1;
  u16 vshort2;
  u16 vshort3;
  u32 vint1;
  u32 vint2;
  u32 vint3;
  u64 value1;
  u64 value2;
  u64 value3;
  printf("testing endianess... ");
  vshort1 = 0x1122;
  copy_be16(&vshort2, &vshort1);
  assert(vshort2 == 0x2211);
  copy_be16(&vshort3, &vshort2);
  assert(vshort3 == vshort1);
  vshort1 = 0xF123;
  copy_be16(&vshort2, &vshort1);
  assert(vshort2 == 0x23F1);
  copy_be16(&vshort3, &vshort2);
  assert(vshort3 == vshort1);
  vshort1 = 0x0123;
  copy_be16(&vshort2, &vshort1);
  assert(vshort2 == 0x2301);
  copy_be16(&vshort3, &vshort2);
  assert(vshort3 == vshort1);
  vint1 = 0x11223344;
  copy_be32(&vint2, &vint1);
  assert(vint2 == 0x44332211);
  copy_be32(&vint3, &vint2);
  assert(vint3 == vint1);
  vint1 = 0xF1234580;
  copy_be32(&vint2, &vint1);
  assert(vint2 == 0x804523F1);
  copy_be32(&vint3, &vint2);
  assert(vint3 == vint1);
  vint1 = 0x00112233;
  copy_be32(&vint2, &vint1);
  assert(vint2 == 0x33221100);
  copy_be32(&vint3, &vint2);
  assert(vint3 == vint1);
  value1 = 0x1122334455667788;
  copy_be64(&value2, &value1);
  assert(value2 == 0x8877665544332211);
  copy_be64(&value3, &value2);
  assert(value3 == value1);
  printf("OK\n");
}

void *memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}

char *i64toa(int64 value, char *buf, int radix)
{
  switch (radix)
  {
    case 10:
      snprintf(buf, 64, "%lli", value);
      break;

    case 16:
      snprintf(buf, 64, "%llx", value);
      break;

    default:
      buf[0] = 0;

  }

  return buf;
}

void pass_int64(int64 a)
{
  assert(a == 9223372036854775807);
  assert(a > 9223372036854775806);
}

int64 return_int64()
{
  return 9223372036854775807;
}

int64 return_passed_int64(int64 a)
{
  return a;
}

void test_int64()
{
  int64 i64;
  char buf[64];
  printf("testing int64... ");
  pass_int64(9223372036854775807);
  i64 = return_int64();
  assert(i64 == 9223372036854775807);
  i64toa(i64, buf, 10);
  assert(strcmp(buf, "9223372036854775807") == 0);
  i64 = return_passed_int64(-987654321987654321);
  assert(i64 == (-987654321987654321));
  i64toa(i64, buf, 10);
  assert(strcmp(buf, "-987654321987654321") == 0);
  printf("OK\n");
}

BOOL AlmostEqualFloats(float A, float B, int maxUlps)
{
  int aInt;
  int bInt;
  int intDiff;
  assert((maxUlps > 0) && (maxUlps < ((4 * 1024) * 1024)));
  aInt = *((int *) (&A));
  bInt = *((int *) (&B));
  if (aInt < 0)
  {
    aInt = 0x80000000 - aInt;
  }
  if (bInt < 0)
  {
    bInt = 0x80000000 - bInt;
  }
  intDiff = abs(aInt - bInt);
  if (intDiff <= maxUlps)
  {
    return 1;
  }
  return 0;
}

BOOL AlmostEqualDoubles(double a, double b)
{
  double absDiff;
  double maxAbs;
  double absA;
  double absB;
  absDiff = fabs(a - b);
  if (absDiff < 1.0E-150)
  {
    return 1;
  }
  absA = fabs(a);
  absB = fabs(b);
  maxAbs = (absA > absB) ? (absA) : (absB);
  if ((absDiff / maxAbs) < 1.0E-8)
  {
    return 1;
  }
  printf("a=%g b=%g\n", a, b);
  return 0;
}

void test_floating_point_numbers()
{
  char buf[256];
  float f1;
  double d1;
  printf("testing floating point... ");
  f1 = 1.25;
  assert(f1 == 1.25);
  d1 = 1.25;
  assert(d1 == 1.25);
  d1 = 0;
  d1 = f1;
  assert(d1 == 1.25);
  f1 = 0;
  f1 = d1;
  assert(f1 == 1.25);
  d1 = 1.234;
  assert(AlmostEqualDoubles(d1, 1.234) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.234, 2) == 1);
  d1 = 1.2345;
  assert(AlmostEqualDoubles(d1, 1.2345) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.2345, 2) == 1);
  d1 = atof("1.234");
  assert(AlmostEqualDoubles(d1, 1.234) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.234, 2) == 1);
  sprintf(buf, "%g", d1);
  assert(buf[0] != 0);
  assert(strcmp(buf, "1.234") == 0);
  d1 = atof("12.34");
  assert(d1 == 12.34);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 12.34, 2) == 1);
  sprintf(buf, "%g", d1);
  assert(buf[0] != 0);
  assert(strcmp(buf, "12.34") == 0);
  d1 = atof("1.234e25");
  assert(AlmostEqualDoubles(d1, 1.234e25) == 1);
  f1 = d1;
  assert(AlmostEqualFloats(f1, 1.234e25, 2) == 1);
  sprintf(buf, "%g", d1);
  assert(buf[0] != 0);
  printf("OK\n");
}

void print_binn(binn *map)
{
  unsigned char *p;
  unsigned int p_idx = 0;
  int size;
  int i;
  p_idx = binn_ptr(map);
  size = binn_size(map);
  for (i = 0; i < size; i += 1)
  {
    printf("%02x ", p[i + p_idx]);
  }

  puts("");
}

void test1()
{
  static const int fix_size = 512;
  int i;
  int blobsize;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *p2;
  unsigned int p2_idx = 0;
  binn *obj1;
  unsigned int obj1_idx = 0;
  binn *list;
  unsigned int list_idx = 0;
  binn *map;
  unsigned int map_idx = 0;
  binn *obj;
  unsigned int obj_idx = 0;
  binn value;
  char vbyte;
  char *pblob;
  unsigned int pblob_idx = 0;
  signed short vint16;
  unsigned short vuint16;
  signed int vint32;
  unsigned int vuint32;
  signed long long int vint64;
  unsigned long long int vuint64;
  printf("testing binn 1... ");
  assert(CalcAllocation(512, 512) == 512);
  assert(CalcAllocation(510, 512) == 512);
  assert(CalcAllocation(1, 512) == 512);
  assert(CalcAllocation(0, 512) == 512);
  assert(CalcAllocation(513, 512) == 1024);
  assert(CalcAllocation(512 + 256, 512) == 1024);
  assert(CalcAllocation(1025, 512) == 2048);
  assert(CalcAllocation(1025, 1024) == 2048);
  assert(CalcAllocation(2100, 1024) == 4096);
  assert(binn_new(-1, 0, 0) == 0);
  assert(binn_new(0, 0, 0) == 0);
  assert(binn_new(5, 0, 0) == 0);
  assert(binn_new(0xE1, -1, 0) == 0);
  ptr_idx = (char *) (&(&obj1[obj1_idx]));
  assert(binn_new(0xE1, -1, ptr) == 0);
  assert(binn_new(0xE1, 3 - 1, ptr) == 0);
  obj1_idx = binn_new(0xE0, 0, 0);
  assert((&obj1[obj1_idx]) != 0);
  assert(obj1->header == 0x1F22B11F);
  assert(obj1->type == 0xE0);
  assert(obj1->count == 0);
  assert(obj1->pbuf != 0);
  assert(obj1->alloc_size > 9);
  assert(obj1->used_size == 9);
  assert(obj1->pre_allocated == 0);
  binn_free(obj1);
  list_idx = binn_new(0xE0, 0, 0);
  assert((&list[list_idx]) != 0);
  map_idx = binn_new(0xE1, 0, 0);
  assert((&map[map_idx]) != 0);
  obj_idx = binn_new(0xE2, 0, 0);
  assert((&obj[obj_idx]) != 0);
  assert(list->header == 0x1F22B11F);
  assert(list->type == 0xE0);
  assert(list->count == 0);
  assert(list->pbuf != 0);
  assert(list->alloc_size > 9);
  assert(list->used_size == 9);
  assert(list->pre_allocated == 0);
  assert(map->header == 0x1F22B11F);
  assert(map->type == 0xE1);
  assert(map->count == 0);
  assert(map->pbuf != 0);
  assert(map->alloc_size > 9);
  assert(map->used_size == 9);
  assert(map->pre_allocated == 0);
  assert(obj->header == 0x1F22B11F);
  assert(obj->type == 0xE2);
  assert(obj->count == 0);
  assert(obj->pbuf != 0);
  assert(obj->alloc_size > 9);
  assert(obj->used_size == 9);
  assert(obj->pre_allocated == 0);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  obj1_idx = binn_new(0xE2, fix_size, ptr);
  assert((&obj1[obj1_idx]) != 0);
  assert(obj1->header == 0x1F22B11F);
  assert(obj1->type == 0xE2);
  assert(obj1->count == 0);
  assert(obj1->pbuf != 0);
  assert(obj1->alloc_size == fix_size);
  assert(obj1->used_size == 9);
  assert(obj1->pre_allocated == 1);
  assert(binn_map_set(list, 55001, 0x61, &i, 0) == 0);
  assert(binn_object_set(list, "test", 0x61, &i, 0) == 0);
  assert(binn_list_add(map, 0x61, &i, 0) == 0);
  assert(binn_object_set(map, "test", 0x61, &i, 0) == 0);
  assert(binn_list_add(obj, 0x61, &i, 0) == 0);
  assert(binn_map_set(obj, 55001, 0x61, &i, 0) == 0);
  assert(binn_list_add(list, -1, &i, 0) == 0);
  assert(binn_list_add(list, 0x1FFFF, &i, 0) == 0);
  assert(binn_map_set(map, 5501, -1, &i, 0) == 0);
  assert(binn_map_set(map, 5501, 0x1FFFF, &i, 0) == 0);
  assert(binn_object_set(obj, "test", -1, &i, 0) == 0);
  assert(binn_object_set(obj, "test", 0x1FFFF, &i, 0) == 0);
  assert(binn_list_add(list, 0x21, 0, 0) == 0);
  assert(binn_list_add(list, 0x41, 0, 0) == 0);
  assert(binn_list_add(list, 0x61, 0, 0) == 0);
  assert(binn_list_add(list, 0x81, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x21, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x41, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x61, 0, 0) == 0);
  assert(binn_map_set(map, 5501, 0x81, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x21, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x41, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x61, 0, 0) == 0);
  assert(binn_object_set(obj, "test", 0x81, 0, 0) == 0);
  assert(binn_list_add(list, 0xC0, 0, -1) == 0);
  assert(binn_list_add(list, 0xC0, 0, 10) == 0);
  assert(binn_map_set(map, 5501, 0xC0, 0, -1) == 0);
  assert(binn_map_set(map, 5501, 0xC0, 0, 10) == 0);
  assert(binn_object_set(obj, "test", 0xC0, 0, -1) == 0);
  assert(binn_object_set(obj, "test", 0xC0, 0, 10) == 0);
  assert(binn_list_add(list, 0xC0, &i, -1) == 0);
  assert(binn_list_add(list, 0xC0, &i, -15) == 0);
  assert(binn_map_set(map, 5501, 0xC0, &i, -1) == 0);
  assert(binn_map_set(map, 5501, 0xC0, &i, -15) == 0);
  assert(binn_object_set(obj, "test", 0xC0, &i, -1) == 0);
  assert(binn_object_set(obj, "test", 0xC0, &i, -15) == 0);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_value(ptr, 0, &value) == 0);
  assert(binn_list_get_value(ptr, 1, &value) == 0);
  assert(binn_list_get_value(ptr, 2, &value) == 0);
  assert(binn_list_get_value(ptr, -1, &value) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_value(ptr, 0, &value) == 0);
  assert(binn_list_get_value(ptr, 1, &value) == 0);
  assert(binn_list_get_value(ptr, 2, &value) == 0);
  assert(binn_list_get_value(ptr, -1, &value) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_value(ptr, 0, &value) == 0);
  assert(binn_list_get_value(ptr, 1, &value) == 0);
  assert(binn_list_get_value(ptr, 2, &value) == 0);
  assert(binn_list_get_value(ptr, -1, &value) == 0);
  i = 0x1234;
  assert(binn_list_add(list, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 1);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 0);
  vbyte = 255;
  vint16 = -32000;
  vuint16 = 65000;
  vint32 = -65000000;
  vuint32 = 65000000;
  vint64 = -6500000000000000;
  vuint64 = 6500000000000000;
  blobsize = 150;
  pblob_idx = malloc(blobsize);
  assert((&pblob[pblob_idx]) != 0);
  memset(pblob, 55, blobsize);
  assert(binn_list_add(list, 0x00, 0, 0) == 1);
  assert(binn_list_add(list, 0x20, &vbyte, 0) == 1);
  assert(binn_list_add(list, 0x41, &vint16, 0) == 1);
  assert(binn_list_add(list, 0x40, &vuint16, 0) == 1);
  assert(binn_list_add(list, 0x61, &vint32, 0) == 1);
  assert(binn_list_add(list, 0x60, &vuint32, 0) == 1);
  assert(binn_list_add(list, 0x81, &vint64, 0) == 1);
  assert(binn_list_add(list, 0x80, &vuint64, 0) == 1);
  assert(binn_list_add(list, 0xA0, "this is the string", 0) == 1);
  assert(binn_list_add(list, 0xC0, pblob, blobsize) == 1);
  assert(binn_map_set(map, 99000, 0x00, 0, 0) == 1);
  assert(binn_map_set(map, 99001, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 99002, 0x41, &vint16, 0) == 1);
  assert(binn_map_set(map, 99003, 0x40, &vuint16, 0) == 1);
  assert(binn_map_set(map, 99004, 0x61, &vint32, 0) == 1);
  assert(binn_map_set(map, 99005, 0x60, &vuint32, 0) == 1);
  assert(binn_map_set(map, 99006, 0x81, &vint64, 0) == 1);
  assert(binn_map_set(map, 99007, 0x80, &vuint64, 0) == 1);
  assert(binn_map_set(map, 99008, 0xA0, "this is the string", 0) == 1);
  assert(binn_map_set(map, 99009, 0xC0, pblob, blobsize) == 1);
  assert(binn_object_set(obj, "key0", 0x00, 0, 0) == 1);
  assert(binn_object_set(obj, "key1", 0x20, &vbyte, 0) == 1);
  assert(binn_object_set(obj, "key2", 0x41, &vint16, 0) == 1);
  assert(binn_object_set(obj, "key3", 0x40, &vuint16, 0) == 1);
  assert(binn_object_set(obj, "key4", 0x61, &vint32, 0) == 1);
  assert(binn_object_set(obj, "key5", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj, "key6", 0x81, &vint64, 0) == 1);
  assert(binn_object_set(obj, "key7", 0x80, &vuint64, 0) == 1);
  assert(binn_object_set(obj, "key8", 0xA0, "this is the string", 0) == 1);
  assert(binn_object_set(obj, "key9", 0xC0, pblob, blobsize) == 1);
  assert(binn_list_add(list, 0xC0, ptr, 0) == 1);
  assert(binn_list_add(list, 0xA0, "", 0) == 1);
  assert(binn_list_add(list, 0xA0, "after the empty items", 0) == 1);
  assert(binn_map_set(map, 0x09, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x3F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x4F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0xFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0xFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0xFFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x7FFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x09, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x3F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x4F, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0xFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0xFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0xFFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, -0x7FFFFFFF, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 0x09, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0x3F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0x4F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0xFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0xFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0xFFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, 0x7FFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x09, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x3F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x4F, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0xFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0xFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0xFFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_map_set(map, -0x7FFFFFFF, 0x20, &vbyte, 0) == 0);
  assert(binn_list_add(obj1, 0x61, &i, 0) == 0);
  assert(binn_map_set(obj1, 55001, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 0);
  assert(binn_object_set(obj1, "key1", 0xA0, "this is the value", 0) == 1);
  assert(binn_object_set(obj1, "key2", 0xA0, "the second value", 0) == 1);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  p2_idx = &ptr[ptr_idx];
  for (i = 0; i < (fix_size - 1); i += 1)
  {
    p2[p2_idx] = 'A';
    p2_idx += 1;
  }

  p2[p2_idx] = '\0';
  assert(strlen(ptr) == (fix_size - 1));
  assert(binn_object_set(obj1, "v2", 0xA0, ptr, 0) == 0);
  assert(binn_object_set(obj, "v2", 0xA0, ptr, 0) == 1);
  assert(binn_object_set(obj, "Key00", 0xA0, "after the big string", 0) == 1);
  free(ptr);
  ptr_idx = 0;
  assert(binn_object_set(obj, "list", 0xE0, binn_ptr(list), binn_size(list)) == 1);
  assert(binn_object_set(obj, "Key10", 0xA0, "after the list", 0) == 1);
  assert(binn_size(0) == 0);
  assert(binn_size(list) == list->size);
  assert(binn_size(map) == map->size);
  assert(binn_size(obj) == obj->size);
  assert(binn_size(obj1) == obj1->size);
  binn_free(list);
  binn_free(map);
  binn_free(obj);
  binn_free(obj1);
  printf("OK\n");
}

void test2(BOOL use_int_compression)
{
  binn *list = 0;
  unsigned int list_idx = 0;
  binn *map = 0;
  unsigned int map_idx = 0;
  binn *obj = 0;
  unsigned int obj_idx = 0;
  binn value;
  BOOL vbool;
  int blobsize;
  char *pblob;
  unsigned int pblob_idx = 0;
  char *pstr;
  unsigned int pstr_idx = 0;
  signed int vint32;
  double vdouble;
  char *str_list = "test list";
  char *str_map = "test map";
  char *str_obj = "test object";
  printf("testing binn 2 (use_int_compression = %d)... ", use_int_compression);
  blobsize = 150;
  pblob_idx = malloc(blobsize);
  assert((&pblob[pblob_idx]) != 0);
  memset(pblob, 55, blobsize);
  assert((&list[list_idx]) == 0);
  assert((&map[map_idx]) == 0);
  assert((&obj[obj_idx]) == 0);
  assert(binn_list_add_int32(list, 123) == 0);
  assert(binn_map_set_int32(map, 1001, 456) == 0);
  assert(binn_object_set_int32(obj, "int", 789) == 0);
  list_idx = binn_list();
  map_idx = binn_map();
  obj_idx = binn_object();
  assert((&list[list_idx]) != 0);
  assert((&map[map_idx]) != 0);
  assert((&obj[obj_idx]) != 0);
  if (use_int_compression == 0)
  {
    list->disable_int_compression = 1;
    map->disable_int_compression = 1;
    obj->disable_int_compression = 1;
  }
  assert(binn_list_add_int32(list, 123) == 1);
  assert(binn_map_set_int32(map, 1001, 456) == 1);
  assert(binn_object_set_int32(obj, "int", 789) == 1);
  assert(list->header == 0x1F22B11F);
  assert(list->type == 0xE0);
  assert(list->count == 1);
  assert(list->pbuf != 0);
  assert(list->alloc_size > 9);
  assert(list->used_size > 9);
  assert(list->pre_allocated == 0);
  assert(map->header == 0x1F22B11F);
  assert(map->type == 0xE1);
  assert(map->count == 1);
  assert(map->pbuf != 0);
  assert(map->alloc_size > 9);
  assert(map->used_size > 9);
  assert(map->pre_allocated == 0);
  assert(obj->header == 0x1F22B11F);
  assert(obj->type == 0xE2);
  assert(obj->count == 1);
  assert(obj->pbuf != 0);
  assert(obj->alloc_size > 9);
  assert(obj->used_size > 9);
  assert(obj->pre_allocated == 0);
  assert(binn_list_add_double(list, 1.23) == 1);
  assert(binn_map_set_double(map, 1002, 4.56) == 1);
  assert(binn_object_set_double(obj, "double", 7.89) == 1);
  assert(list->count == 2);
  assert(map->count == 2);
  assert(obj->count == 2);
  assert(binn_list_add_bool(list, 1) == 1);
  assert(binn_map_set_bool(map, 1003, 1) == 1);
  assert(binn_object_set_bool(obj, "bool", 1) == 1);
  assert(list->count == 3);
  assert(map->count == 3);
  assert(obj->count == 3);
  assert(binn_list_add_str(list, str_list) == 1);
  assert(binn_map_set_str(map, 1004, str_map) == 1);
  assert(binn_object_set_str(obj, "text", str_obj) == 1);
  assert(list->count == 4);
  assert(map->count == 4);
  assert(obj->count == 4);
  assert(binn_list_add_blob(list, pblob, blobsize) == 1);
  assert(binn_map_set_blob(map, 1005, pblob, blobsize) == 1);
  assert(binn_object_set_blob(obj, "blob", pblob, blobsize) == 1);
  assert(list->count == 5);
  assert(map->count == 5);
  assert(obj->count == 5);
  assert(binn_count(list) == 5);
  assert(binn_count(map) == 5);
  assert(binn_count(obj) == 5);
  assert(binn_size(list) == list->size);
  assert(binn_size(map) == map->size);
  assert(binn_size(obj) == obj->size);
  assert(binn_type(list) == 0xE0);
  assert(binn_type(map) == 0xE1);
  assert(binn_type(obj) == 0xE2);
  assert(binn_list_get_value(list, 1, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.allocated == 0);
  if (use_int_compression)
  {
    assert(value.type == 0x20);
    assert(value.ptr != (&value.vuint8));
  }
  else
  {
    assert(value.type == 0x61);
    assert(value.ptr == (&value.vint));
  }
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vint == 123);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1001, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  if (use_int_compression)
  {
    assert(value.type == 0x40);
    assert(value.ptr == (&value.vuint16));
  }
  else
  {
    assert(value.type == 0x61);
    assert(value.ptr == (&value.vint));
  }
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vint == 456);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "int", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  if (use_int_compression)
  {
    assert(value.type == 0x40);
    assert(value.ptr == (&value.vuint16));
  }
  else
  {
    assert(value.type == 0x61);
    assert(value.ptr == (&value.vint));
  }
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vint == 789);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 2, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x82);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vdouble == 1.23);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1002, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x82);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vdouble == 4.56);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "double", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x82);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vdouble == 7.89);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 3, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x80061);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vbool == 1);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1003, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x80061);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vbool == 1);
  assert(binn_object_get_value(obj, "bool", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0x80061);
  assert(value.ptr == (&value.vint));
  assert(value.size == 0);
  assert(value.count == 0);
  assert(value.vbool == 1);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 4, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xA0);
  assert(value.ptr != 0);
  assert(value.size == strlen(str_list));
  assert(strcmp(value.ptr, str_list) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1004, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xA0);
  assert(value.size == strlen(str_map));
  assert(strcmp(value.ptr, str_map) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "text", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xA0);
  assert(value.size == strlen(str_obj));
  assert(strcmp(value.ptr, str_obj) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_value(list, 5, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xC0);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_map_get_value(map, 1005, &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xC0);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_object_get_value(obj, "blob", &value) == 1);
  assert(value.header == 0x1F22B11F);
  assert(value.writable == 0);
  assert(value.type == 0xC0);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(value.count == 0);
  memset(&value, 0, sizeof(binn));
  assert(binn_list_get_int32(list, 1, &vint32) == 1);
  assert(vint32 == 123);
  assert(binn_map_get_int32(map, 1001, &vint32) == 1);
  assert(vint32 == 456);
  assert(binn_object_get_int32(obj, "int", &vint32) == 1);
  assert(vint32 == 789);
  assert(binn_list_get_double(list, 2, &vdouble) == 1);
  assert(vdouble == 1.23);
  assert(binn_map_get_double(map, 1002, &vdouble) == 1);
  assert(vdouble == 4.56);
  assert(binn_object_get_double(obj, "double", &vdouble) == 1);
  assert(vdouble == 7.89);
  assert(binn_list_get_bool(list, 3, &vbool) == 1);
  assert(vbool == 1);
  assert(binn_map_get_bool(map, 1003, &vbool) == 1);
  assert(vbool == 1);
  assert(binn_object_get_bool(obj, "bool", &vbool) == 1);
  assert(vbool == 1);
  assert(binn_list_get_str(list, 4, &(&pstr[pstr_idx])) == 1);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_list) == 0);
  assert(binn_map_get_str(map, 1004, &(&pstr[pstr_idx])) == 1);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_map) == 0);
  assert(binn_object_get_str(obj, "text", &(&pstr[pstr_idx])) == 1);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_obj) == 0);
  value.ptr = 0;
  value.size = 0;
  assert(binn_list_get_blob(list, 5, &value.ptr, &value.size) == 1);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = 0;
  value.size = 0;
  assert(binn_map_get_blob(map, 1005, &value.ptr, &value.size) == 1);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = 0;
  value.size = 0;
  assert(binn_object_get_blob(obj, "blob", &value.ptr, &value.size) == 1);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  assert(binn_list_int32(list, 1) == 123);
  assert(binn_map_int32(map, 1001) == 456);
  assert(binn_object_int32(obj, "int") == 789);
  assert(binn_list_double(list, 2) == 1.23);
  assert(binn_map_double(map, 1002) == 4.56);
  assert(binn_object_double(obj, "double") == 7.89);
  assert(binn_list_bool(list, 3) == 1);
  assert(binn_map_bool(map, 1003) == 1);
  assert(binn_object_bool(obj, "bool") == 1);
  pstr_idx = binn_list_str(list, 4);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_list) == 0);
  pstr_idx = binn_map_str(map, 1004);
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_map) == 0);
  pstr_idx = binn_object_str(obj, "text");
  assert((&pstr[pstr_idx]) != 0);
  assert(strcmp(pstr, str_obj) == 0);
  value.ptr = binn_list_blob(list, 5, &value.size);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = binn_map_blob(map, 1005, &value.size);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  value.ptr = binn_object_blob(obj, "blob", &value.size);
  assert(value.ptr != 0);
  assert(value.size == blobsize);
  assert(memcmp(value.ptr, pblob, blobsize) == 0);
  binn_free(list);
  binn_free(map);
  binn_free(obj);
  printf("OK\n");
}

void test3()
{
  static const int fix_size = 512;
  int i;
  int id;
  int type;
  int count;
  int size;
  int header_size;
  int blobsize;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *p2;
  unsigned int p2_idx = 0;
  char *pstr;
  unsigned int pstr_idx = 0;
  char key[256];
  binn *list;
  unsigned int list_idx = 0;
  binn *map;
  unsigned int map_idx = 0;
  binn *obj;
  unsigned int obj_idx = 0;
  binn *obj1;
  unsigned int obj1_idx = 0;
  binn value;
  char vbyte;
  char *pblob;
  unsigned int pblob_idx = 0;
  signed short vint16;
  signed short *pint16;
  unsigned int pint16_idx = 0;
  unsigned short vuint16;
  unsigned short *puint16;
  unsigned int puint16_idx = 0;
  signed int vint32;
  signed int *pint32;
  unsigned int pint32_idx = 0;
  unsigned int vuint32;
  unsigned int *puint32;
  unsigned int puint32_idx = 0;
  signed long long int vint64;
  signed long long int *pint64;
  unsigned int pint64_idx = 0;
  unsigned long long int vuint64;
  unsigned long long int *puint64;
  unsigned int puint64_idx = 0;
  printf("testing binn 3... ");
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  map_idx = binn_map();
  assert((&map[map_idx]) != 0);
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  assert(list->header == 0x1F22B11F);
  assert(list->type == 0xE0);
  assert(list->count == 0);
  assert(list->pbuf != 0);
  assert(list->alloc_size > 9);
  assert(list->used_size == 9);
  assert(list->pre_allocated == 0);
  assert(map->header == 0x1F22B11F);
  assert(map->type == 0xE1);
  assert(map->count == 0);
  assert(map->pbuf != 0);
  assert(map->alloc_size > 9);
  assert(map->used_size == 9);
  assert(map->pre_allocated == 0);
  assert(obj->header == 0x1F22B11F);
  assert(obj->type == 0xE2);
  assert(obj->count == 0);
  assert(obj->pbuf != 0);
  assert(obj->alloc_size > 9);
  assert(obj->used_size == 9);
  assert(obj->pre_allocated == 0);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  obj1_idx = binn_new(0xE2, fix_size, ptr);
  assert((&obj1[obj1_idx]) != 0);
  assert(obj1->header == 0x1F22B11F);
  assert(obj1->type == 0xE2);
  assert(obj1->count == 0);
  assert(obj1->pbuf != 0);
  assert(obj1->alloc_size == fix_size);
  assert(obj1->used_size == 9);
  assert(obj1->pre_allocated == 1);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_read(ptr, 0, &type, &size) == 0);
  assert(binn_list_read(ptr, 1, &type, &size) == 0);
  assert(binn_list_read(ptr, 2, &type, &size) == 0);
  assert(binn_list_read(ptr, -1, &type, &size) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_map_read(ptr, 0, &type, &size) == 0);
  assert(binn_map_read(ptr, 55001, &type, &size) == 0);
  assert(binn_map_read(ptr, -1, &type, &size) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_object_read(ptr, 0, &type, &size) == 0);
  assert(binn_object_read(ptr, "", &type, &size) == 0);
  assert(binn_object_read(ptr, "test", &type, &size) == 0);
  assert(binn_list_add(list, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 1);
  assert(binn_map_set(map, 5501, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 1);
  assert(binn_object_set(obj, "test", 0x61, &i, 0) == 0);
  vbyte = 255;
  vint16 = -32000;
  vuint16 = 65000;
  vint32 = -65000000;
  vuint32 = 65000000;
  vint64 = -6500000000000000;
  vuint64 = 6500000000000000;
  blobsize = 150;
  pblob_idx = malloc(blobsize);
  assert((&pblob[pblob_idx]) != 0);
  memset(pblob, 55, blobsize);
  assert(binn_list_add(list, 0x00, 0, 0) == 1);
  assert(binn_list_add(list, 0x20, &vbyte, 0) == 1);
  assert(binn_list_add(list, 0x41, &vint16, 0) == 1);
  assert(binn_list_add(list, 0x40, &vuint16, 0) == 1);
  assert(binn_list_add(list, 0x61, &vint32, 0) == 1);
  assert(binn_list_add(list, 0x60, &vuint32, 0) == 1);
  assert(binn_list_add(list, 0x81, &vint64, 0) == 1);
  assert(binn_list_add(list, 0x80, &vuint64, 0) == 1);
  assert(binn_list_add(list, 0xA0, "this is the string", 0) == 1);
  assert(binn_list_add(list, 0xC0, pblob, blobsize) == 1);
  assert(binn_map_set(map, 99000, 0x00, 0, 0) == 1);
  assert(binn_map_set(map, 99001, 0x20, &vbyte, 0) == 1);
  assert(binn_map_set(map, 99002, 0x41, &vint16, 0) == 1);
  assert(binn_map_set(map, 99003, 0x40, &vuint16, 0) == 1);
  assert(binn_map_set(map, 99004, 0x61, &vint32, 0) == 1);
  assert(binn_map_set(map, 99005, 0x60, &vuint32, 0) == 1);
  assert(binn_map_set(map, 99006, 0x81, &vint64, 0) == 1);
  assert(binn_map_set(map, 99007, 0x80, &vuint64, 0) == 1);
  assert(binn_map_set(map, 99008, 0xA0, "this is the string", 0) == 1);
  assert(binn_map_set(map, 99009, 0xC0, pblob, blobsize) == 1);
  assert(binn_object_set(obj, "key0", 0x00, 0, 0) == 1);
  assert(binn_object_set(obj, "key1", 0x20, &vbyte, 0) == 1);
  assert(binn_object_set(obj, "key2", 0x41, &vint16, 0) == 1);
  assert(binn_object_set(obj, "key3", 0x40, &vuint16, 0) == 1);
  assert(binn_object_set(obj, "key4", 0x61, &vint32, 0) == 1);
  assert(binn_object_set(obj, "key5", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj, "key6", 0x81, &vint64, 0) == 1);
  assert(binn_object_set(obj, "key7", 0x80, &vuint64, 0) == 1);
  assert(binn_object_set(obj, "key8", 0xA0, "this is the string", 0) == 1);
  assert(binn_object_set(obj, "key9", 0xC0, pblob, blobsize) == 1);
  assert(binn_list_add(list, 0xC0, ptr, 0) == 1);
  assert(binn_list_add(list, 0xA0, "", 0) == 1);
  assert(binn_list_add(list, 0xA0, "after the empty items", 0) == 1);
  assert(binn_list_add(obj1, 0x61, &i, 0) == 0);
  assert(binn_map_set(obj1, 55001, 0x61, &i, 0) == 0);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 1);
  assert(binn_object_set(obj1, "test", 0x60, &vuint32, 0) == 0);
  assert(binn_object_set(obj1, "key1", 0xA0, "this is the value", 0) == 1);
  assert(binn_object_set(obj1, "key2", 0xA0, "the second value", 0) == 1);
  ptr_idx = malloc(fix_size);
  assert((&ptr[ptr_idx]) != 0);
  p2_idx = &ptr[ptr_idx];
  for (i = 0; i < (fix_size - 1); i += 1)
  {
    p2[p2_idx] = 'A';
    p2_idx += 1;
  }

  p2[p2_idx] = '\0';
  assert(strlen(ptr) == (fix_size - 1));
  assert(binn_object_set(obj1, "v2", 0xA0, ptr, 0) == 0);
  assert(binn_object_set(obj, "v2", 0xA0, ptr, 0) == 1);
  assert(binn_object_set(obj, "Key00", 0xA0, "after the big string", 0) == 1);
  free(ptr);
  ptr_idx = 0;
  assert(binn_object_set(obj, "list", 0xE0, binn_ptr(list), binn_size(list)) == 1);
  assert(binn_object_set(obj, "Key10", 0xA0, "after the list", 0) == 1);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_map_get_pair(ptr, -1, &id, &value) == 0);
  assert(binn_map_get_pair(ptr, 0, &id, &value) == 0);
  assert(binn_map_get_pair(ptr, 1, &id, &value) == 1);
  assert(id == 5501);
  assert(binn_map_get_pair(ptr, 2, &id, &value) == 1);
  assert(id == 99000);
  assert(binn_map_get_pair(ptr, 3, &id, &value) == 1);
  assert(id == 99001);
  assert(binn_map_get_pair(ptr, 10, &id, &value) == 1);
  assert(id == 99008);
  assert(binn_map_get_pair(ptr, 11, &id, &value) == 1);
  assert(id == 99009);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_object_get_pair(ptr, -1, key, &value) == 0);
  assert(binn_object_get_pair(ptr, 0, key, &value) == 0);
  assert(binn_object_get_pair(ptr, 1, key, &value) == 1);
  assert(strcmp(key, "test") == 0);
  assert(binn_object_get_pair(ptr, 2, key, &value) == 1);
  assert(strcmp(key, "key0") == 0);
  assert(binn_object_get_pair(ptr, 3, key, &value) == 1);
  assert(strcmp(key, "key1") == 0);
  assert(binn_object_get_pair(ptr, 10, key, &value) == 1);
  assert(strcmp(key, "key8") == 0);
  assert(binn_object_get_pair(ptr, 11, key, &value) == 1);
  assert(strcmp(key, "key9") == 0);
  ptr_idx = binn_ptr(obj1);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key1", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the value") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key2", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "the second value") == 0);
  type = 0;
  size = 0;
  pint32_idx = binn_object_read(ptr, "test", &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x60);
  assert(pint32[pint32_idx] == vuint32);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(ptr, 2, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0x00);
  type = 0;
  size = 0;
  p2_idx = binn_list_read(ptr, 3, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0x20);
  assert(p2[p2_idx] == vbyte);
  type = 0;
  size = 0;
  pint16_idx = binn_list_read(ptr, 4, &type, &size);
  assert((&pint16[pint16_idx]) != 0);
  assert(type == 0x41);
  assert(pint16[pint16_idx] == vint16);
  type = 0;
  size = 0;
  puint16_idx = binn_list_read(ptr, 5, &type, &size);
  assert((&puint16[puint16_idx]) != 0);
  assert(type == 0x40);
  assert(puint16[puint16_idx] == vuint16);
  type = 0;
  size = 0;
  pint32_idx = binn_list_read(ptr, 6, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  pint32_idx = binn_list_read(ptr, 6, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  puint32_idx = binn_list_read(ptr, 7, &type, &size);
  assert((&puint32[puint32_idx]) != 0);
  assert(type == 0x60);
  assert(puint32[puint32_idx] == vuint32);
  type = 0;
  size = 0;
  pint64_idx = binn_list_read(ptr, 8, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  pint64_idx = binn_list_read(ptr, 8, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  puint64_idx = binn_list_read(ptr, 9, &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(ptr, 10, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_list_read(ptr, 11, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xC0);
  assert(size == blobsize);
  assert(memcmp(p2, pblob, blobsize) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_map_read(ptr, 99000, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0x00);
  type = 0;
  size = 0;
  p2_idx = binn_map_read(ptr, 99001, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0x20);
  assert(p2[p2_idx] == vbyte);
  type = 0;
  size = 0;
  pint16_idx = binn_map_read(ptr, 99002, &type, &size);
  assert((&pint16[pint16_idx]) != 0);
  assert(type == 0x41);
  assert(pint16[pint16_idx] == vint16);
  type = 0;
  size = 0;
  puint16_idx = binn_map_read(ptr, 99003, &type, &size);
  assert((&puint16[puint16_idx]) != 0);
  assert(type == 0x40);
  assert(puint16[puint16_idx] == vuint16);
  type = 0;
  size = 0;
  pint32_idx = binn_map_read(ptr, 99004, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  pint32_idx = binn_map_read(ptr, 99004, &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  puint32_idx = binn_map_read(ptr, 99005, &type, &size);
  assert((&puint32[puint32_idx]) != 0);
  assert(type == 0x60);
  assert(puint32[puint32_idx] == vuint32);
  type = 0;
  size = 0;
  pint64_idx = binn_map_read(ptr, 99006, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  pint64_idx = binn_map_read(ptr, 99006, &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  puint64_idx = binn_map_read(ptr, 99007, &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_map_read(ptr, 99008, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_map_read(ptr, 99009, &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xC0);
  assert(size == blobsize);
  assert(memcmp(p2, pblob, blobsize) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key0", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0x00);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "key1", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0x20);
  assert(p2[p2_idx] == vbyte);
  type = 0;
  size = 0;
  pint16_idx = binn_object_read(ptr, "key2", &type, &size);
  assert((&pint16[pint16_idx]) != 0);
  assert(type == 0x41);
  assert(pint16[pint16_idx] == vint16);
  type = 0;
  size = 0;
  puint16_idx = binn_object_read(ptr, "key3", &type, &size);
  assert((&puint16[puint16_idx]) != 0);
  assert(type == 0x40);
  assert(puint16[puint16_idx] == vuint16);
  type = 0;
  size = 0;
  pint32_idx = binn_object_read(ptr, "key4", &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  pint32_idx = binn_object_read(ptr, "key4", &type, &size);
  assert((&pint32[pint32_idx]) != 0);
  assert(type == 0x61);
  assert(pint32[pint32_idx] == vint32);
  type = 0;
  size = 0;
  puint32_idx = binn_object_read(ptr, "key5", &type, &size);
  assert((&puint32[puint32_idx]) != 0);
  assert(type == 0x60);
  assert(puint32[puint32_idx] == vuint32);
  type = 0;
  size = 0;
  pint64_idx = binn_object_read(ptr, "key6", &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  pint64_idx = binn_object_read(ptr, "key6", &type, &size);
  assert((&pint64[pint64_idx]) != 0);
  assert(type == 0x81);
  assert(pint64[pint64_idx] == vint64);
  type = 0;
  size = 0;
  puint64_idx = binn_object_read(ptr, "key7", &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key8", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "key9", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xC0);
  assert(size == blobsize);
  assert(memcmp(p2, pblob, blobsize) == 0);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "v2", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xA0);
  assert(size == (fix_size - 1));
  assert(strlen(p2) == (fix_size - 1));
  assert(p2[0 + p2_idx] == 'A');
  assert(p2[1 + p2_idx] == 'A');
  assert(p2[500 + p2_idx] == 'A');
  assert(p2[(fix_size - 1) + p2_idx] == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key00", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "after the big string") == 0);
  type = 0;
  size = 0;
  p2_idx = binn_object_read(ptr, "list", &type, &size);
  assert((&p2[p2_idx]) != 0);
  assert(type == 0xE0);
  assert(size > 0);
  type = 0;
  size = 0;
  puint64_idx = binn_list_read(p2, 9, &type, &size);
  assert((&puint64[puint64_idx]) != 0);
  assert(type == 0x80);
  assert(puint64[puint64_idx] == vuint64);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 10, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "this is the string") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 12, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xC0);
  assert(size == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 13, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size == 0);
  assert(strcmp(pstr, "") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_list_read(p2, 14, &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "after the empty items") == 0);
  type = 0;
  size = 0;
  pstr_idx = binn_object_read(ptr, "key10", &type, &size);
  assert((&pstr[pstr_idx]) != 0);
  assert(type == 0xA0);
  assert(size > 0);
  assert(strcmp(pstr, "after the list") == 0);
  assert(binn_ptr(0) == 0);
  assert(IsValidBinnHeader(0) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  size = 0;
  assert(IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 1);
  assert(type == 0xE2);
  assert(count == 15);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == obj->size);
  assert(binn_is_valid(ptr, &type, &count, &size) == 1);
  assert(type == 0xE2);
  assert(count == 15);
  assert(size > 3);
  assert(size == obj->size);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  size = 0;
  assert(IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 1);
  assert(type == 0xE1);
  assert(count == 11);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == map->size);
  assert(binn_is_valid(ptr, &type, &count, &size) == 1);
  assert(type == 0xE1);
  assert(count == 11);
  assert(size > 3);
  assert(size == map->size);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  size = 0;
  assert(IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 1);
  assert(type == 0xE0);
  assert(count == 14);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == list->size);
  assert(binn_is_valid(ptr, &type, &count, &size) == 1);
  assert(type == 0xE0);
  assert(count == 14);
  assert((header_size >= 3) && (header_size <= 9));
  assert(size > 3);
  assert(size == list->size);
  assert(binn_size(0) == 0);
  assert(binn_size(list) == list->size);
  assert(binn_size(map) == map->size);
  assert(binn_size(obj) == obj->size);
  assert(binn_size(obj1) == obj1->size);
  binn_free(list);
  binn_free(map);
  binn_free(obj);
  printf("OK\n");
}

void test_invalid_binn()
{
  char buffers[][20] = {{0xE0}, {0xE0, 0x7E}, {0xE0, 0x7E, 0x7F}, {0xE0, 0x7E, 0x7F, 0x12}, {0xE0, 0x7E, 0x7F, 0x12, 0x34}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0x01}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0x7F}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01}, {0xE0, 0x7E, 0x7F, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12}, {0xE0, 0x7E, 0xFF, 0x12, 0x34}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0x01}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0x7F}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01}, {0xE0, 0x7E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x8E}, {0xE0, 0x8E, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12}, {0xE0, 0x8E, 0xFF, 0x12, 0x34}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0x01}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0x7F}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0x01}, {0xE0, 0x8E, 0xFF, 0x12, 0x34, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}};
  int count;
  int size;
  int i;
  char *ptr;
  unsigned int ptr_idx = 0;
  puts("testing invalid binn buffers...");
  count = (sizeof(buffers)) / (sizeof(buffers[0]));
  for (i = 0; i < count; i += 1)
  {
    ptr_idx = buffers[i];
    size = strlen(ptr);
    printf("checking invalid binn #%d   size: %d bytes\n", i, size);
    assert(binn_is_valid_ex(ptr, 0, 0, &size) == 0);
  }

  puts("OK");
}

int main()
{
  puts("\nStarting the unit/regression tests...\n");
  printf("sizeof(binn) = %d\n\n", sizeof(binn));
  test_binn_version();
  test_endianess();
  test_int64();
  test_floating_point_numbers();
  test1();
  test2(0);
  test2(1);
  test_binn2();
  test3();
  test_invalid_binn();
  puts("\nAll tests pass! :)\n");
  return 0;
}

