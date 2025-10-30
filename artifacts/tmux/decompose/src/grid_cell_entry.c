struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
/*** DEPENDENCIES:
***/


