typedef struct ZopfliNode
{
  uint32_t length;
  uint32_t distance;
  uint32_t dcode_insert_length;
  union 
  {
    float cost;
    uint32_t next;
    uint32_t shortcut;
  } u;
} ZopfliNode
/*** DEPENDENCIES:
***/


