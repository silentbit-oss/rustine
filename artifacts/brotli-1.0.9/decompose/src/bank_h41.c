typedef struct BankH41
{
  SlotH41 slots[1 << 16];
} BankH41
/*** DEPENDENCIES:
typedef struct SlotH41
{
  uint16_t delta;
  uint16_t next;
} SlotH41
----------------------------
None
----------------------------
***/


