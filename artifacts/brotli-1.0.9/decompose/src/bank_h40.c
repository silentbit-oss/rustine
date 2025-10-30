typedef struct BankH40
{
  SlotH40 slots[1 << 16];
} BankH40
/*** DEPENDENCIES:
typedef struct SlotH40
{
  uint16_t delta;
  uint16_t next;
} SlotH40
----------------------------
None
----------------------------
***/


