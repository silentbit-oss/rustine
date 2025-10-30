struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
/*** DEPENDENCIES:
typedef struct 
{
  const char *key;
  void *value;
} ht_entry
----------------------------
***/


static uint64_t hash_key(const char *key)
{
  uint64_t hash = 14695981039346656037UL;
  for (const char *p = key; p[p_idx]; p_idx += 1)
  {
    hash ^= (uint64_t) ((unsigned char) p[p_idx]);
    hash *= 1099511628211UL;
  }

  unsigned int p_idx = 0;
  return hash;
}


/*** DEPENDENCIES:
***/


ht *ht_create(void)
{
  ht *table = malloc(sizeof(ht));
  if (table == 0)
  {
    return 0;
  }
  table->length = 0;
  table->capacity = 16;
  table->entries = calloc(table->capacity, sizeof(ht_entry));
  if (table->entries == 0)
  {
    free(table);
    return 0;
  }
  return table;
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
***/


void ht_destroy(ht *table)
{
  for (size_t i = 0; i < table->capacity; i += 1)
  {
    free((void *) table->entries[i].key);
  }

  free(table->entries);
  free(table);
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
***/


size_t ht_length(ht *table)
{
  return table->length;
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
***/


void *ht_get(ht *table, const char *key)
{
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (table->capacity - 1)));
  while (table->entries[index].key != 0)
  {
    if (strcmp(key, table->entries[index].key) == 0)
    {
      return table->entries[index].value;
    }
    index += 1;
    if (index >= table->capacity)
    {
      index = 0;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
static uint64_t hash_key(const char *key)
{
  uint64_t hash = 14695981039346656037UL;
  for (const char *p = key; p[p_idx]; p_idx += 1)
  {
    hash ^= (uint64_t) ((unsigned char) p[p_idx]);
    hash *= 1099511628211UL;
  }

  unsigned int p_idx = 0;
  return hash;
}


----------------------------
***/


hti ht_iterator(ht *table)
{
  hti it;
  it._table = table;
  it._index = 0;
  return it;
}


/*** DEPENDENCIES:
typedef struct 
{
  const char *key;
  void *value;
  ht *_table;
  size_t _index;
} hti
----------------------------
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
***/


static const char *ht_set_entry(ht_entry *entries, size_t capacity, const char *key, void *value, size_t *plength)
{
  unsigned int key_idx = 0;
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (capacity - 1)));
  while (entries[index].key != 0)
  {
    if (strcmp(key, entries[index].key) == 0)
    {
      entries[index].value = value;
      return entries[index].key;
    }
    index += 1;
    if (index >= capacity)
    {
      index = 0;
    }
  }

  if (plength != 0)
  {
    key_idx = strdup(key_idx);
    if ((&key[key_idx]) == 0)
    {
      return 0;
    }
    *plength += 1;
  }
  entries[index].key = (char *) key;
  entries[index].value = value;
  return key;
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
typedef struct 
{
  const char *key;
  void *value;
} ht_entry
----------------------------
static uint64_t hash_key(const char *key)
{
  uint64_t hash = 14695981039346656037UL;
  for (const char *p = key; p[p_idx]; p_idx += 1)
  {
    hash ^= (uint64_t) ((unsigned char) p[p_idx]);
    hash *= 1099511628211UL;
  }

  unsigned int p_idx = 0;
  return hash;
}


----------------------------
***/


static bool ht_expand(ht *table)
{
  size_t new_capacity = table->capacity * 2;
  if (new_capacity < table->capacity)
  {
    return 0;
  }
  ht_entry *new_entries = calloc(new_capacity, sizeof(ht_entry));
  if (new_entries == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < table->capacity; i += 1)
  {
    ht_entry entry = table->entries[i];
    if (entry.key != 0)
    {
      ht_set_entry(new_entries, new_capacity, entry.key, entry.value, 0);
    }
  }

  free(table->entries);
  table->entries = new_entries;
  table->capacity = new_capacity;
  return 1;
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
static const char *ht_set_entry(ht_entry *entries, size_t capacity, const char *key, void *value, size_t *plength)
{
  unsigned int key_idx = 0;
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (capacity - 1)));
  while (entries[index].key != 0)
  {
    if (strcmp(key, entries[index].key) == 0)
    {
      entries[index].value = value;
      return entries[index].key;
    }
    index += 1;
    if (index >= capacity)
    {
      index = 0;
    }
  }

  if (plength != 0)
  {
    key_idx = strdup(key_idx);
    if ((&key[key_idx]) == 0)
    {
      return 0;
    }
    *plength += 1;
  }
  entries[index].key = (char *) key;
  entries[index].value = value;
  return key;
}


----------------------------
typedef struct 
{
  const char *key;
  void *value;
} ht_entry
----------------------------
***/


const char *ht_set(ht *table, const char *key, void *value)
{
  assert(value != 0);
  if (value == 0)
  {
    return 0;
  }
  if (table->length >= (table->capacity / 2))
  {
    if (!ht_expand(table))
    {
      return 0;
    }
  }
  return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
static const char *ht_set_entry(ht_entry *entries, size_t capacity, const char *key, void *value, size_t *plength)
{
  unsigned int key_idx = 0;
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (capacity - 1)));
  while (entries[index].key != 0)
  {
    if (strcmp(key, entries[index].key) == 0)
    {
      entries[index].value = value;
      return entries[index].key;
    }
    index += 1;
    if (index >= capacity)
    {
      index = 0;
    }
  }

  if (plength != 0)
  {
    key_idx = strdup(key_idx);
    if ((&key[key_idx]) == 0)
    {
      return 0;
    }
    *plength += 1;
  }
  entries[index].key = (char *) key;
  entries[index].value = value;
  return key;
}


----------------------------
static bool ht_expand(ht *table)
{
  size_t new_capacity = table->capacity * 2;
  if (new_capacity < table->capacity)
  {
    return 0;
  }
  ht_entry *new_entries = calloc(new_capacity, sizeof(ht_entry));
  if (new_entries == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < table->capacity; i += 1)
  {
    ht_entry entry = table->entries[i];
    if (entry.key != 0)
    {
      ht_set_entry(new_entries, new_capacity, entry.key, entry.value, 0);
    }
  }

  free(table->entries);
  table->entries = new_entries;
  table->capacity = new_capacity;
  return 1;
}


----------------------------
***/


bool ht_next(hti *it)
{
  ht *table = it->_table;
  while (it->_index < table->capacity)
  {
    size_t i = it->_index;
    it->_index += 1;
    if (table->entries[i].key != 0)
    {
      ht_entry entry = table->entries[i];
      it->key = entry.key;
      it->value = entry.value;
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  const char *key;
  void *value;
  ht *_table;
  size_t _index;
} hti
----------------------------
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
typedef struct 
{
  const char *key;
  void *value;
} ht_entry
----------------------------
***/


