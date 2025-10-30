struct input_param
{
  enum 
  {
    INPUT_MISSING,
    INPUT_NUMBER,
    INPUT_STRING
  } type;
  union 
  {
    int num;
    char *str;
  };
}
/*** DEPENDENCIES:
***/


