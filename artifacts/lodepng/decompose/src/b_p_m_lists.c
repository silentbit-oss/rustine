typedef struct BPMLists
{
  unsigned memsize;
  BPMNode *memory;
  unsigned numfree;
  unsigned nextfree;
  BPMNode **freelist;
  unsigned listsize;
  BPMNode **chains0;
  BPMNode **chains1;
} BPMLists
/*** DEPENDENCIES:
typedef struct BPMNode
{
  int weight;
  unsigned index;
  struct BPMNode *tail;
  int in_use;
} BPMNode
----------------------------
***/


