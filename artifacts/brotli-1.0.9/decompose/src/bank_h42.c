typedef struct BankH42
{
  SlotH42 slots[1 << 9];
} BankH42
/*** DEPENDENCIES:
typedef struct SlotH42
{
  uint16_t delta;
  uint16_t next;
} SlotH42
----------------------------
None
----------------------------
***/


