void test_named()
{
  short ok;
  int32_t val = rgba_from_string("olive", &ok);
  assert(ok);
  assert(0x808000FF == val);
}


/*** DEPENDENCIES:
uint32_t rgba_from_string(const char *str, short *ok)
{
  unsigned int str_idx = 0;
  if ('#' == str[0 + str_idx])
  {
    str_idx += 1;
    return rgba_from_hex_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgba"))
  {
    return rgba_from_rgba_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgb"))
  {
    return rgba_from_rgb_string(str, ok);
  }
  return rgba_from_name_string(str, ok);
}


----------------------------
***/


void test_rgb()
{
  short ok;
  int32_t val = rgba_from_string("rgb(255, 30   , 0)", &ok);
  assert(ok);
  assert(0xff1e00ff == val);
  val = rgba_from_string("rgb(0,0,0)", &ok);
  assert(ok);
  assert(0x000000ff == val);
}


/*** DEPENDENCIES:
uint32_t rgba_from_string(const char *str, short *ok)
{
  unsigned int str_idx = 0;
  if ('#' == str[0 + str_idx])
  {
    str_idx += 1;
    return rgba_from_hex_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgba"))
  {
    return rgba_from_rgba_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgb"))
  {
    return rgba_from_rgb_string(str, ok);
  }
  return rgba_from_name_string(str, ok);
}


----------------------------
***/


void test_rgba()
{
  short ok;
  int32_t val = rgba_from_string("rgba(255, 30   , 0, .5)", &ok);
  assert(ok);
  assert(0xff1e007f == val);
  val = rgba_from_string("rgba(0,0,0, 1)", &ok);
  assert(ok);
  assert(0x000000ff == val);
}


/*** DEPENDENCIES:
uint32_t rgba_from_string(const char *str, short *ok)
{
  unsigned int str_idx = 0;
  if ('#' == str[0 + str_idx])
  {
    str_idx += 1;
    return rgba_from_hex_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgba"))
  {
    return rgba_from_rgba_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgb"))
  {
    return rgba_from_rgb_string(str, ok);
  }
  return rgba_from_name_string(str, ok);
}


----------------------------
***/


void test_hex()
{
  short ok;
  int32_t val = rgba_from_string("#ff1e00", &ok);
  assert(ok);
  assert(0xff1e00ff == val);
  val = rgba_from_string("#ffffff", &ok);
  assert(ok);
  assert(0xffffffff == val);
  val = rgba_from_string("#ffcc00", &ok);
  assert(ok);
  assert(0xffcc00ff == val);
  val = rgba_from_string("#fco", &ok);
  assert(ok);
  assert(0xffcc00ff == val);
}


/*** DEPENDENCIES:
uint32_t rgba_from_string(const char *str, short *ok)
{
  unsigned int str_idx = 0;
  if ('#' == str[0 + str_idx])
  {
    str_idx += 1;
    return rgba_from_hex_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgba"))
  {
    return rgba_from_rgba_string(str, ok);
  }
  if ((&str[str_idx]) == strstr(str, "rgb"))
  {
    return rgba_from_rgb_string(str, ok);
  }
  return rgba_from_name_string(str, ok);
}


----------------------------
***/


void test_to_string()
{
  char buf[256];
  rgba_t color = rgba_new(0xffcc00ff);
  rgba_to_string(color, buf, 256);
  assert(0 == strcmp("#ffcc00", buf));
  color = rgba_new(0xffcc0050);
  rgba_to_string(color, buf, 256);
  assert(0 == strcmp("rgba(255, 204, 0, 0.31)", buf));
}


/*** DEPENDENCIES:
void rgba_to_string(rgba_t rgba, char *buf, size_t len)
{
  if (1 == rgba.a)
  {
    snprintf(buf, len, "#%.2x%.2x%.2x", (int) (rgba.r * 255), (int) (rgba.g * 255), (int) (rgba.b * 255));
  }
  else
  {
    snprintf(buf, len, "rgba(%d, %d, %d, %.2f)", (int) (rgba.r * 255), (int) (rgba.g * 255), (int) (rgba.b * 255), rgba.a);
  }
}


----------------------------
typedef struct 
{
  double r;
  double g;
  double b;
  double a;
} rgba_t
----------------------------
rgba_t rgba_new(uint32_t rgba)
{
  rgba_t color;
  color.r = ((double) (rgba >> 24)) / 255;
  color.g = ((double) ((rgba >> 16) & 0xff)) / 255;
  color.b = ((double) ((rgba >> 8) & 0xff)) / 255;
  color.a = ((double) (rgba & 0xff)) / 255;
  return color;
}


----------------------------
***/


int main(int argc, char **argv)
{
  test_named();
  test_rgb();
  test_rgba();
  test_hex();
  test_to_string();
  printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
  return 0;
}


/*** DEPENDENCIES:
void test_to_string()
{
  char buf[256];
  rgba_t color = rgba_new(0xffcc00ff);
  rgba_to_string(color, buf, 256);
  assert(0 == strcmp("#ffcc00", buf));
  color = rgba_new(0xffcc0050);
  rgba_to_string(color, buf, 256);
  assert(0 == strcmp("rgba(255, 204, 0, 0.31)", buf));
}


----------------------------
void test_rgba()
{
  short ok;
  int32_t val = rgba_from_string("rgba(255, 30   , 0, .5)", &ok);
  assert(ok);
  assert(0xff1e007f == val);
  val = rgba_from_string("rgba(0,0,0, 1)", &ok);
  assert(ok);
  assert(0x000000ff == val);
}


----------------------------
void test_rgb()
{
  short ok;
  int32_t val = rgba_from_string("rgb(255, 30   , 0)", &ok);
  assert(ok);
  assert(0xff1e00ff == val);
  val = rgba_from_string("rgb(0,0,0)", &ok);
  assert(ok);
  assert(0x000000ff == val);
}


----------------------------
void test_named()
{
  short ok;
  int32_t val = rgba_from_string("olive", &ok);
  assert(ok);
  assert(0x808000FF == val);
}


----------------------------
void test_hex()
{
  short ok;
  int32_t val = rgba_from_string("#ff1e00", &ok);
  assert(ok);
  assert(0xff1e00ff == val);
  val = rgba_from_string("#ffffff", &ok);
  assert(ok);
  assert(0xffffffff == val);
  val = rgba_from_string("#ffcc00", &ok);
  assert(ok);
  assert(0xffcc00ff == val);
  val = rgba_from_string("#fco", &ok);
  assert(ok);
  assert(0xffcc00ff == val);
}


----------------------------
***/


