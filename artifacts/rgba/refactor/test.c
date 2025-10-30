#include <assert.h>
#include <rgba.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
  double r;
  double g;
  double b;
  double a;
} rgba_t;
rgba_t rgba_new(uint32_t rgba);
uint32_t rgba_from_string(const char *str, short *ok);
void rgba_to_string(rgba_t rgba, char *buf, size_t len);
void rgba_inspect(uint32_t rgba);
void test_named()
{
  short ok;
  int32_t val = rgba_from_string("olive", &ok);
  assert(ok);
  assert(0x808000FF == val);
}

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

