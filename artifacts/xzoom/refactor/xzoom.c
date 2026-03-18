#include <Xatom.h>
#include <Xlib.h>
#include <Xutil.h>
#include <_X11_fake_defines.h>
#include <_X11_fake_typedefs.h>
#include <cursorfont.h>
#include <keysym.h>
#include <scale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>

typedef struct XErrorEvent XErrorEvent;
typedef struct XWindowAttributes XWindowAttributes;
typedef struct Window Window;
typedef struct Cursor Cursor;
typedef struct Display Display;
typedef struct Screen Screen;
typedef struct Status Status;
typedef struct XColor XColor;
typedef struct XEvent XEvent;
typedef struct XGCValues XGCValues;
typedef struct _XGC *GC;
typedef struct _XImage XImage;
typedef struct XSetWindowAttributes XSetWindowAttributes;
typedef struct XTextProperty XTextProperty;
typedef struct XSizeHints XSizeHints;
typedef unsigned long Atom;
Display *dpy;
Screen *scr;
Window win;
Atom wm_delete_window;
Atom wm_protocols;
Atom wm_dock;
Atom wm_windowtype;
Status status;
GC gc;
Cursor when_button;
Cursor crosshair;
char *progname;
int set_title;
int xgrab;
int ygrab;
int magx = 2;
int magy = 2;
int flipxy = False;
int flipx = False;
int flipy = False;
int xzoom_flag = False;
int yzoom_flag = False;
int gridx = False;
int gridy = False;
int width[2] = {0, 256};
int height[2] = {0, 256};
unsigned depth = 0;
XImage *ximage[2];
int created_images = False;
int delays[5] = {200000, 100000, 50000, 10000, 0};
int delay_index = 0;
int delay = 200000;
void timeout_func(int signum)
{
  set_title = True;
  signum = signum;
}

void allocate_images(void)
{
  int i;
  for (i = 0; i < 2; i += 1)
  {
    char *data;
    unsigned int data_idx = 0;
    data_idx = malloc(((BitmapUnit(dpy) / 8) * width[i]) * height[i]);
    ximage[i] = XCreateImage(dpy, DefaultVisualOfScreen(scr), DefaultDepthOfScreen(scr), ZPixmap, 0, data, width[i], height[i], 32, 0);
    if (ximage[i] == 0)
    {
      perror("XCreateImage");
      exit(-1);
    }
  }

  created_images = True;
}

void destroy_images(void)
{
  int i;
  if (!created_images)
  {
    return;
  }
  for (i = 0; i < 2; i += 1)
  {
    free(ximage[i]->data);
    ximage[i]->data = 0;
    XDestroyImage(ximage[i]);
  }

  created_images = False;
}

void Usage(void)
{
  fprintf(stderr, "Usage: %s [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-dock\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next '+' or '-' only change width scaling\nh: Next '+' or '-' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n", progname);
  exit(1);
}

void resize(int new_width, int new_height)
{
  destroy_images();
  if (flipxy)
  {
    height[0] = ((new_width + magx) - 1) / magx;
    width[0] = ((new_height + magy) - 1) / magy;
  }
  else
  {
    width[0] = ((new_width + magx) - 1) / magx;
    height[0] = ((new_height + magy) - 1) / magy;
  }
  if (width[0] < 1)
  {
    width[0] = 1;
  }
  if (width[0] > WidthOfScreen(scr))
  {
    width[0] = WidthOfScreen(scr);
  }
  if (height[0] < 1)
  {
    height[0] = 1;
  }
  if (height[0] > HeightOfScreen(scr))
  {
    height[0] = HeightOfScreen(scr);
  }
  if (flipxy)
  {
    width[1] = magx * height[0];
    height[1] = magy * width[0];
  }
  else
  {
    width[1] = magx * width[0];
    height[1] = magy * height[0];
  }
  allocate_images();
  if (width[1] > new_width)
  {
    width[1] = new_width;
  }
  if (height[1] > new_height)
  {
    height[1] = new_height;
  }
}

void scale8(void)
{
  {
    helper_scale8_1();
  }
}

void scale16(void)
{
  {
    helper_scale16_1();
  }
}

void scale32(void)
{
  {
    helper_scale32_1();
  }
}

void xzoom(int buttonpressed)
{
  char title[80];
  XGetSubImage(dpy, RootWindowOfScreen(scr), xgrab, ygrab, width[0], height[0], AllPlanes, ZPixmap, ximage[0], 0, 0);
  if (depth == 8)
  {
    scale8();
  }
  else
    if (depth <= (8 * (sizeof(short))))
  {
    scale16();
  }
  else
    if (depth <= (8 * (sizeof(int))))
  {
    scale32();
  }
  XPutImage(dpy, win, gc, ximage[1], 0, 0, 0, 0, width[1], height[1]);
  if (set_title)
  {
    if ((((magx == magy) && (!flipx)) && (!flipy)) && (!flipxy))
    {
      sprintf(title, "%s x%d", progname, magx);
    }
    else
      sprintf(title, "%s X %s%d%s Y %s%d", progname, (flipx) ? ("-") : (""), magx, (flipxy) ? (" <=>") : (";"), (flipy) ? ("-") : (""), magy);
    XChangeProperty(dpy, win, XA_WM_NAME, XA_STRING, 8, PropModeReplace, (unsigned char *) title, strlen(title));
    set_title = False;
  }
  XSync(dpy, 0);
}

int main(int argc, char **argv)
{
  unsigned int argv_idx = 0;
  XSetWindowAttributes xswa;
  XEvent event;
  XTextProperty str;
  XSizeHints *sizeh = 0;
  unsigned int sizeh_idx = 0;
  XClassHint * ch;
  int buttonpressed = False;
  int visible = False;
  int scroll = 1;
  char title[80];
  XGCValues gcv;
  char *dpyname = 0;
  unsigned int dpyname_idx = 0;
  int source_geom_mask = NoValue;
  int dest_geom_mask = NoValue;
  int copy_from_src_mask;
  int xpos = 0;
  int ypos = 0;
  int isdock = 0;
  atexit(destroy_images);
  progname = strrchr(argv[0 + argv_idx], '/');
  if (progname)
  {
    progname += 1;
  }
  else
    progname = argv[0 + argv_idx];
  while ((--argc) > 0)
  {
    helper_main_1(&argc, &argv_idx, &dpyname_idx, &source_geom_mask, &dest_geom_mask, &isdock, argv, xpos, ypos);
  }

  if (!(dpy = XOpenDisplay(dpyname)))
  {
    perror("Cannot open display");
    exit(-1);
  }
  copy_from_src_mask = NoValue;
  if (source_geom_mask & WidthValue)
  {
    if (flipxy)
    {
      height[1] = magy * width[0];
      copy_from_src_mask |= HeightValue;
    }
    else
    {
      width[1] = magx * width[0];
      copy_from_src_mask |= WidthValue;
    }
  }
  if (source_geom_mask & HeightValue)
  {
    if (flipxy)
    {
      width[1] = magx * height[0];
      copy_from_src_mask |= WidthValue;
    }
    else
    {
      height[1] = magy * height[0];
      copy_from_src_mask |= HeightValue;
    }
  }
  if (copy_from_src_mask & dest_geom_mask)
  {
    fprintf(stderr, "Conflicting dimensions between source and dest geometry\n");
    Usage();
  }
  scr = DefaultScreenOfDisplay(dpy);
  depth = DefaultDepthOfScreen(scr);
  if (depth < 8)
  {
    fprintf(stderr, "%s: need at least 8 bits/pixel\n", progname);
    exit(1);
  }
  if (source_geom_mask & XNegative)
  {
    xgrab += WidthOfScreen(scr);
  }
  if (source_geom_mask & YNegative)
  {
    ygrab += HeightOfScreen(scr);
  }
  if (dest_geom_mask & XNegative)
  {
    xpos += WidthOfScreen(scr);
  }
  if (dest_geom_mask & YNegative)
  {
    ypos += HeightOfScreen(scr);
  }
  printf("=%dx%d+%d+%d\n", width[1], height[1], xpos, ypos);
  xswa.event_mask = (ButtonPressMask | ButtonReleaseMask) | ButtonMotionMask;
  xswa.event_mask |= StructureNotifyMask;
  xswa.event_mask |= KeyPressMask | KeyReleaseMask;
  xswa.event_mask |= VisibilityChangeMask;
  xswa.background_pixel = BlackPixelOfScreen(scr);
  win = XCreateWindow(dpy, RootWindowOfScreen(scr), xpos, ypos, width[1], height[1], 0, DefaultDepthOfScreen(scr), InputOutput, DefaultVisualOfScreen(scr), CWEventMask | CWBackPixel, &xswa);
  XChangeProperty(dpy, win, XA_WM_ICON_NAME, XA_STRING, 8, PropModeReplace, (unsigned char *) progname, strlen(progname));
  if (!isdock)
  {
    sizeh_idx = XAllocSizeHints();
    sizeh->flags = PMaxSize | PMinSize;
    sizeh->min_width = (sizeh->max_width = width[1]);
    sizeh->min_height = (sizeh->max_height = height[1]);
  }
  XStringListToTextProperty(&progname, 1, &str);
  ch = XAllocClassHint();
  ch->res_class = progname;
  ch->res_name = progname;
  XSetWMProperties(dpy, win, &str, &str, 0, 0, sizeh, 0, ch);
  if (isdock)
  {
    wm_windowtype = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", False);
    wm_dock = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_DOCK", False);
    XChangeProperty(dpy, win, wm_windowtype, XA_ATOM, 32, PropModeReplace, (unsigned char *) (&wm_dock), 1);
  }
  wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  wm_protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
  status = XSetWMProtocols(dpy, win, &wm_delete_window, 1);
  set_title = True;
  status = XMapWindow(dpy, win);
  gcv.plane_mask = AllPlanes;
  gcv.subwindow_mode = IncludeInferiors;
  gcv.function = GXcopy;
  gcv.foreground = WhitePixelOfScreen(scr);
  gcv.background = BlackPixelOfScreen(scr);
  gc = XCreateGC(dpy, RootWindowOfScreen(scr), (((GCFunction | GCPlaneMask) | GCSubwindowMode) | GCForeground) | GCBackground, &gcv);
  resize(width[1], height[1]);
  when_button = XCreateFontCursor(dpy, XC_ul_angle);
  crosshair = XCreateFontCursor(dpy, XC_crosshair);
  XDefineCursor(dpy, win, crosshair);
  for (;;)
  {
    helper_main_2(&buttonpressed, &visible, &scroll, event, title);
  }

}

void helper_scale8_1()
{
  int i;
  int j;
  int k;
  j = (flipxy) ? (width[0] - 1) : (height[0] - 1);
  do
  {
    helper_helper_scale8_1_1(&i, &k, j);
  }
  while ((--j) >= 0);
}

void helper_scale16_1()
{
  int i;
  int j;
  int k;
  j = (flipxy) ? (width[0] - 1) : (height[0] - 1);
  do
  {
    helper_helper_scale16_1_1(&i, &k, j);
  }
  while ((--j) >= 0);
}

void helper_scale32_1()
{
  int i;
  int j;
  int k;
  j = (flipxy) ? (width[0] - 1) : (height[0] - 1);
  do
  {
    helper_helper_scale32_1_1(&i, &k, j);
  }
  while ((--j) >= 0);
}

void helper_main_1(int * const argc_ref, unsigned int * const argv_idx_ref, unsigned int * const dpyname_idx_ref, int * const source_geom_mask_ref, int * const dest_geom_mask_ref, int * const isdock_ref, char ** const argv, int xpos, int ypos)
{
  int argc = *argc_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int dpyname_idx = *dpyname_idx_ref;
  int source_geom_mask = *source_geom_mask_ref;
  int dest_geom_mask = *dest_geom_mask_ref;
  int isdock = *isdock_ref;
  argv_idx += 1;
  if (argv[0 + argv_idx][0] == '=')
  {
    dest_geom_mask = XParseGeometry(argv[0 + argv_idx], &xpos, &ypos, &width[1], &height[1]);
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-mag"))
  {
    helper_helper_main_1_1(&argc, &argv_idx, argv);
  }
  if (!strcmp(argv[0 + argv_idx], "-x"))
  {
    flipx = True;
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-y"))
  {
    flipy = True;
    continue;
  }
  if ((!strcmp(argv[0 + argv_idx], "-z")) || (!strcmp(argv[0 + argv_idx], "-xy")))
  {
    flipxy = True;
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-source"))
  {
    argv_idx += 1;
    argc -= 1;
    if (argc < 1)
    {
      Usage();
    }
    source_geom_mask = XParseGeometry(argv[0 + argv_idx], &xgrab, &ygrab, &width[0], &height[0]);
    continue;
  }
  if ((!strcmp(argv[0 + argv_idx], "-dest")) || (!strcmp(argv[0 + argv_idx], "-geometry")))
  {
    argv_idx += 1;
    argc -= 1;
    if (argc < 1)
    {
      Usage();
    }
    dest_geom_mask = XParseGeometry(argv[0 + argv_idx], &xpos, &ypos, &width[1], &height[1]);
    continue;
  }
  if ((!strcmp(argv[0 + argv_idx], "-d")) || (!strcmp(argv[0 + argv_idx], "-display")))
  {
    argv_idx += 1;
    argc -= 1;
    if (argc < 1)
    {
      Usage();
    }
    dpyname_idx = argv[0 + argv_idx];
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-delay"))
  {
    argv_idx += 1;
    argc -= 1;
    if (argc < 1)
    {
      Usage();
    }
    if (sscanf(argv[0 + argv_idx], "%u", &delay) != 1)
    {
      Usage();
    }
    delay *= 1000;
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-dock"))
  {
    isdock = 1;
    continue;
  }
  Usage();
  *argc_ref = argc;
  *argv_idx_ref = argv_idx;
  *dpyname_idx_ref = dpyname_idx;
  *source_geom_mask_ref = source_geom_mask;
  *dest_geom_mask_ref = dest_geom_mask;
  *isdock_ref = isdock;
}

void helper_main_2(int * const buttonpressed_ref, int * const visible_ref, int * const scroll_ref, XEvent event, char title[80])
{
  int buttonpressed = *buttonpressed_ref;
  int visible = *visible_ref;
  int scroll = *scroll_ref;
  while (XPending(dpy))
  {
    helper_helper_main_2_1(&buttonpressed, &visible, &scroll, event, title);
  }

  if (visible)
  {
    xzoom(buttonpressed);
  }
  if ((!buttonpressed) && (delay > 0))
  {
    usleep(delay);
  }
  *buttonpressed_ref = buttonpressed;
  *visible_ref = visible;
  *scroll_ref = scroll;
}

void helper_helper_scale8_1_1(int * const i_ref, int * const k_ref, int j)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned char *p1;
  unsigned int p1_idx = 0;
  unsigned char *p2;
  unsigned int p2_idx = 0;
  int p2step;
  unsigned char *p1_save;
  unsigned int p1_save_idx = 0;
  p1_idx = (unsigned char *) (&ximage[1]->data[((ximage[1]->xoffset + 0) * (sizeof(unsigned char))) + ((j * magy) * ximage[1]->bytes_per_line)]);
  p1_save_idx = &p1[p1_idx];
  p2_idx = (unsigned char *) (&ximage[0]->data[((ximage[0]->xoffset + 0) * (sizeof(unsigned char))) + (((flipy) ? ((height[0] - 1) - j) : (j)) * ximage[0]->bytes_per_line)]);
  if (flipxy)
  {
    helper_helper_helper_scale8_1_1_1(&i, &k, &p1_idx, &p2_idx, &p2step, j, p1, p2);
  }
  else
    if (flipx)
  {
    p2_idx += width[0];
    i = width[0];
    do
    {
      p2_idx -= 1;
      unsigned char c = p2[p2_idx];
      k = magx;
      do
      {
        p1[p1_idx] = c;
        p1_idx += 1;
      }
      while ((--k) > 0);
    }
    while ((--i) > 0);
  }
  else
  {
    i = width[0];
    do
    {
      unsigned char c = p2[p2_idx];
      p2_idx += 1;
      k = magx;
      do
      {
        p1[p1_idx] = c;
        p1_idx += 1;
      }
      while ((--k) > 0);
    }
    while ((--i) > 0);
  }
  if (gridy && (magx >= 2))
  {
    p1_idx = (&p1_save[p1_save_idx]) - 1;
    i = magx;
    k = (flipxy) ? (height[0]) : (width[0]);
    do
    {
      p1_idx += i;
      p1[p1_idx] ^= ~((unsigned char) 0);
    }
    while ((--k) > 0);
  }
  if (magy > 1)
  {
    helper_helper_helper_scale8_1_1_2(&i, &k, &p1_idx, &p2_idx, &p2step, p1, p2, p1_save, p1_save_idx);
  }
  *i_ref = i;
  *k_ref = k;
}

void helper_helper_scale16_1_1(int * const i_ref, int * const k_ref, int j)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned short *p1;
  unsigned int p1_idx = 0;
  unsigned short *p2;
  unsigned int p2_idx = 0;
  int p2step;
  unsigned short *p1_save;
  unsigned int p1_save_idx = 0;
  p1_idx = (unsigned short *) (&ximage[1]->data[((ximage[1]->xoffset + 0) * (sizeof(unsigned short))) + ((j * magy) * ximage[1]->bytes_per_line)]);
  p1_save_idx = &p1[p1_idx];
  p2_idx = (unsigned short *) (&ximage[0]->data[((ximage[0]->xoffset + 0) * (sizeof(unsigned short))) + (((flipy) ? ((height[0] - 1) - j) : (j)) * ximage[0]->bytes_per_line)]);
  if (flipxy)
  {
    helper_helper_helper_scale16_1_1_1(&i, &k, &p1_idx, &p2_idx, &p2step, j, p1, p2);
  }
  else
    if (flipx)
  {
    p2_idx += width[0];
    i = width[0];
    do
    {
      p2_idx -= 1;
      unsigned short c = p2[p2_idx];
      k = magx;
      do
      {
        p1[p1_idx] = c;
        p1_idx += 1;
      }
      while ((--k) > 0);
    }
    while ((--i) > 0);
  }
  else
  {
    i = width[0];
    do
    {
      unsigned short c = p2[p2_idx];
      p2_idx += 1;
      k = magx;
      do
      {
        p1[p1_idx] = c;
        p1_idx += 1;
      }
      while ((--k) > 0);
    }
    while ((--i) > 0);
  }
  if (gridy && (magx >= 2))
  {
    p1_idx = (&p1_save[p1_save_idx]) - 1;
    i = magx;
    k = (flipxy) ? (height[0]) : (width[0]);
    do
    {
      p1_idx += i;
      p1[p1_idx] ^= ~((unsigned short) 0);
    }
    while ((--k) > 0);
  }
  if (magy > 1)
  {
    helper_helper_helper_scale16_1_1_2(&i, &k, &p1_idx, &p2_idx, &p2step, p1, p2, p1_save, p1_save_idx);
  }
  *i_ref = i;
  *k_ref = k;
}

void helper_helper_scale32_1_1(int * const i_ref, int * const k_ref, int j)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int *p1;
  unsigned int p1_idx = 0;
  unsigned int *p2;
  unsigned int p2_idx = 0;
  int p2step;
  unsigned int *p1_save;
  unsigned int p1_save_idx = 0;
  p1_idx = (unsigned int *) (&ximage[1]->data[((ximage[1]->xoffset + 0) * (sizeof(unsigned int))) + ((j * magy) * ximage[1]->bytes_per_line)]);
  p1_save_idx = &p1[p1_idx];
  p2_idx = (unsigned int *) (&ximage[0]->data[((ximage[0]->xoffset + 0) * (sizeof(unsigned int))) + (((flipy) ? ((height[0] - 1) - j) : (j)) * ximage[0]->bytes_per_line)]);
  if (flipxy)
  {
    helper_helper_helper_scale32_1_1_1(&i, &k, &p1_idx, &p2_idx, &p2step, j, p1, p2);
  }
  else
    if (flipx)
  {
    p2_idx += width[0];
    i = width[0];
    do
    {
      p2_idx -= 1;
      unsigned int c = p2[p2_idx];
      k = magx;
      do
      {
        p1[p1_idx] = c;
        p1_idx += 1;
      }
      while ((--k) > 0);
    }
    while ((--i) > 0);
  }
  else
  {
    i = width[0];
    do
    {
      unsigned int c = p2[p2_idx];
      p2_idx += 1;
      k = magx;
      do
      {
        p1[p1_idx] = c;
        p1_idx += 1;
      }
      while ((--k) > 0);
    }
    while ((--i) > 0);
  }
  if (gridy && (magx >= 2))
  {
    p1_idx = (&p1_save[p1_save_idx]) - 1;
    i = magx;
    k = (flipxy) ? (height[0]) : (width[0]);
    do
    {
      p1_idx += i;
      p1[p1_idx] ^= ~((unsigned int) 0);
    }
    while ((--k) > 0);
  }
  if (magy > 1)
  {
    helper_helper_helper_scale32_1_1_2(&i, &k, &p1_idx, &p2_idx, &p2step, p1, p2, p1_save, p1_save_idx);
  }
  *i_ref = i;
  *k_ref = k;
}

void helper_helper_main_1_1(int * const argc_ref, unsigned int * const argv_idx_ref, char ** const argv)
{
  int argc = *argc_ref;
  unsigned int argv_idx = *argv_idx_ref;
  argv_idx += 1;
  argc -= 1;
  magx = (argc > 0) ? (atoi(argv[0 + argv_idx])) : (-1);
  if (magx <= 0)
  {
    Usage();
  }
  magy = (argc > 1) ? (atoi(argv[1 + argv_idx])) : (-1);
  if (magy <= 0)
  {
    magy = magx;
  }
  else
  {
    argv_idx += 1;
    argc -= 1;
  }
  continue;
  *argc_ref = argc;
  *argv_idx_ref = argv_idx;
}

void helper_helper_main_2_1(int * const buttonpressed_ref, int * const visible_ref, int * const scroll_ref, XEvent event, char title[80])
{
  int buttonpressed = *buttonpressed_ref;
  int visible = *visible_ref;
  int scroll = *scroll_ref;
  XNextEvent(dpy, &event);
  switch (event.type)
  {
    case ClientMessage:
    {
      if ((event.xclient.message_type == wm_protocols) && (event.xclient.data.l[0] == wm_delete_window))
      {
        exit(0);
      }
      break;
    }

    case ConfigureNotify:
    {
      if ((event.xconfigure.width != width[1]) || (event.xconfigure.height != height[1]))
      {
        resize(event.xconfigure.width, event.xconfigure.height);
      }
      break;
    }

    case ReparentNotify:
    {
      break;
    }

    case VisibilityNotify:
    {
      visible = event.xvisibility.state != VisibilityFullyObscured;
      break;
    }

    case KeyRelease:
    {
      switch (XKeycodeToKeysym(dpy, event.xkey.keycode, 0))
      {
        case XK_Control_L:

        case XK_Control_R:
        {
          scroll = 1;
          break;
        }

      }

      break;
    }

    case KeyPress:
    {
      helper_helper_helper_main_2_1_1(&scroll, event, title);
    }

    case ButtonPress:
    {
      xgrab = event.xbutton.x_root;
      ygrab = event.xbutton.y_root;
      XDefineCursor(dpy, win, when_button);
      buttonpressed = True;
      break;
    }

    case ButtonRelease:
    {
      XDefineCursor(dpy, win, crosshair);
      buttonpressed = False;
      break;
    }

    case MotionNotify:
    {
      if (buttonpressed)
      {
        xgrab = event.xmotion.x_root;
        ygrab = event.xmotion.y_root;
      }
      break;
    }

  }

  if (xgrab < 0)
  {
    xgrab = 0;
  }
  if (xgrab > (WidthOfScreen(scr) - width[0]))
  {
    xgrab = WidthOfScreen(scr) - width[0];
  }
  if (ygrab < 0)
  {
    ygrab = 0;
  }
  if (ygrab > (HeightOfScreen(scr) - height[0]))
  {
    ygrab = HeightOfScreen(scr) - height[0];
  }
  *buttonpressed_ref = buttonpressed;
  *visible_ref = visible;
  *scroll_ref = scroll;
}

void helper_helper_helper_scale8_1_1_1(int * const i_ref, int * const k_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const p2step_ref, int j, unsigned char * const p1, unsigned char * const p2)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int p2step = *p2step_ref;
  p2_idx = (unsigned char *) (&ximage[0]->data[((ximage[0]->xoffset + ((flipy) ? (j) : ((width[0] - 1) - j))) * (sizeof(unsigned char))) + (0 * ximage[0]->bytes_per_line)]);
  p2step = ximage[0]->bytes_per_line / (sizeof(unsigned char));
  if (flipx)
  {
    p2_idx += p2step * (height[0] - 1);
    p2step = -p2step;
  }
  i = height[0];
  do
  {
    unsigned char c = p2[p2_idx];
    p2_idx += p2step;
    k = magx;
    do
    {
      p1[p1_idx] = c;
      p1_idx += 1;
    }
    while ((--k) > 0);
  }
  while ((--i) > 0);
  *i_ref = i;
  *k_ref = k;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *p2step_ref = p2step;
}

void helper_helper_helper_scale8_1_1_2(int * const i_ref, int * const k_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const p2step_ref, unsigned char * const p1, unsigned char * const p2, unsigned char * const p1_save, unsigned int p1_save_idx)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int p2step = *p2step_ref;
  p1_idx = &p1_save[p1_save_idx];
  p2_idx = &p1[p1_idx];
  p2step = ximage[1]->bytes_per_line / (sizeof(unsigned char));
  i = width[1] * (sizeof(unsigned char));
  k = magy - 1;
  do
  {
    p2_idx += p2step;
    memcpy(p2, p1, i);
  }
  while ((--k) > 0);
  if (gridx && (magy >= 2))
  {
    k = width[1];
    do
    {
      p2[p2_idx] ^= ~((unsigned char) 0);
      p2_idx += 1;
    }
    while ((--k) > 0);
  }
  *i_ref = i;
  *k_ref = k;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *p2step_ref = p2step;
}

void helper_helper_helper_scale16_1_1_1(int * const i_ref, int * const k_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const p2step_ref, int j, unsigned short * const p1, unsigned short * const p2)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int p2step = *p2step_ref;
  p2_idx = (unsigned short *) (&ximage[0]->data[((ximage[0]->xoffset + ((flipy) ? (j) : ((width[0] - 1) - j))) * (sizeof(unsigned short))) + (0 * ximage[0]->bytes_per_line)]);
  p2step = ximage[0]->bytes_per_line / (sizeof(unsigned short));
  if (flipx)
  {
    p2_idx += p2step * (height[0] - 1);
    p2step = -p2step;
  }
  i = height[0];
  do
  {
    unsigned short c = p2[p2_idx];
    p2_idx += p2step;
    k = magx;
    do
    {
      p1[p1_idx] = c;
      p1_idx += 1;
    }
    while ((--k) > 0);
  }
  while ((--i) > 0);
  *i_ref = i;
  *k_ref = k;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *p2step_ref = p2step;
}

void helper_helper_helper_scale16_1_1_2(int * const i_ref, int * const k_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const p2step_ref, unsigned short * const p1, unsigned short * const p2, unsigned short * const p1_save, unsigned int p1_save_idx)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int p2step = *p2step_ref;
  p1_idx = &p1_save[p1_save_idx];
  p2_idx = &p1[p1_idx];
  p2step = ximage[1]->bytes_per_line / (sizeof(unsigned short));
  i = width[1] * (sizeof(unsigned short));
  k = magy - 1;
  do
  {
    p2_idx += p2step;
    memcpy(p2, p1, i);
  }
  while ((--k) > 0);
  if (gridx && (magy >= 2))
  {
    k = width[1];
    do
    {
      p2[p2_idx] ^= ~((unsigned short) 0);
      p2_idx += 1;
    }
    while ((--k) > 0);
  }
  *i_ref = i;
  *k_ref = k;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *p2step_ref = p2step;
}

void helper_helper_helper_scale32_1_1_1(int * const i_ref, int * const k_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const p2step_ref, int j, unsigned int * const p1, unsigned int * const p2)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int p2step = *p2step_ref;
  p2_idx = (unsigned int *) (&ximage[0]->data[((ximage[0]->xoffset + ((flipy) ? (j) : ((width[0] - 1) - j))) * (sizeof(unsigned int))) + (0 * ximage[0]->bytes_per_line)]);
  p2step = ximage[0]->bytes_per_line / (sizeof(unsigned int));
  if (flipx)
  {
    p2_idx += p2step * (height[0] - 1);
    p2step = -p2step;
  }
  i = height[0];
  do
  {
    unsigned int c = p2[p2_idx];
    p2_idx += p2step;
    k = magx;
    do
    {
      p1[p1_idx] = c;
      p1_idx += 1;
    }
    while ((--k) > 0);
  }
  while ((--i) > 0);
  *i_ref = i;
  *k_ref = k;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *p2step_ref = p2step;
}

void helper_helper_helper_scale32_1_1_2(int * const i_ref, int * const k_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const p2step_ref, unsigned int * const p1, unsigned int * const p2, unsigned int * const p1_save, unsigned int p1_save_idx)
{
  int i = *i_ref;
  int k = *k_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int p2step = *p2step_ref;
  p1_idx = &p1_save[p1_save_idx];
  p2_idx = &p1[p1_idx];
  p2step = ximage[1]->bytes_per_line / (sizeof(unsigned int));
  i = width[1] * (sizeof(unsigned int));
  k = magy - 1;
  do
  {
    p2_idx += p2step;
    memcpy(p2, p1, i);
  }
  while ((--k) > 0);
  if (gridx && (magy >= 2))
  {
    k = width[1];
    do
    {
      p2[p2_idx] ^= ~((unsigned int) 0);
      p2_idx += 1;
    }
    while ((--k) > 0);
  }
  *i_ref = i;
  *k_ref = k;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *p2step_ref = p2step;
}

void helper_helper_helper_main_2_1_1(int * const scroll_ref, XEvent event, char title[80])
{
  int scroll = *scroll_ref;
  switch (XKeycodeToKeysym(dpy, event.xkey.keycode, 0))
  {
    case XK_Control_L:

    case XK_Control_R:
    {
      scroll = 10;
      break;
    }

    case '+':

    case '=':

    case XK_KP_Add:
    {
      if (!yzoom_flag)
      {
        magx += 1;
      }
      if (!xzoom_flag)
      {
        magy += 1;
      }
      xzoom_flag = (yzoom_flag = False);
      resize(width[1], height[1]);
      set_title = True;
      break;
    }

    case '-':

    case XK_KP_Subtract:
    {
      helper_helper_helper_helper_main_2_1_1_1();
    }

    case XK_Left:

    case XK_KP_Left:
    {
      if (flipxy)
      {
        if (flipx)
        {
          ygrab += scroll;
        }
        else
          ygrab -= scroll;
      }
      else
        if (flipx)
      {
        xgrab += scroll;
      }
      else
        xgrab -= scroll;
      break;
    }

    case XK_Right:

    case XK_KP_Right:
    {
      if (flipxy)
      {
        if (flipx)
        {
          ygrab -= scroll;
        }
        else
          ygrab += scroll;
      }
      else
        if (flipx)
      {
        xgrab -= scroll;
      }
      else
        xgrab += scroll;
      break;
    }

    case XK_Up:

    case XK_KP_Up:
    {
      if (flipxy)
      {
        if (flipy)
        {
          xgrab -= scroll;
        }
        else
          xgrab += scroll;
      }
      else
        if (flipy)
      {
        ygrab += scroll;
      }
      else
        ygrab -= scroll;
      break;
    }

    case XK_Down:

    case XK_KP_Down:
    {
      if (flipxy)
      {
        if (flipy)
        {
          xgrab += scroll;
        }
        else
          xgrab -= scroll;
      }
      else
        if (flipy)
      {
        ygrab -= scroll;
      }
      else
        ygrab += scroll;
      break;
    }

    case 'x':
    {
      flipx = !flipx;
      set_title = True;
      break;
    }

    case 'y':
    {
      flipy = !flipy;
      set_title = True;
      break;
    }

    case 'z':
    {
      if ((flipx ^ flipy) ^ flipxy)
      {
        flipx = !flipx;
        flipy = !flipy;
      }
      flipxy = !flipxy;
      resize(width[1], height[1]);
      set_title = True;
      break;
    }

    case 'w':
    {
      xzoom_flag = True;
      yzoom_flag = False;
      break;
    }

    case 'h':
    {
      yzoom_flag = True;
      xzoom_flag = False;
      break;
    }

    case 'g':
    {
      gridx = !gridx;
      gridy = !gridy;
      break;
    }

    case 'd':
    {
      if ((++delay_index) >= 5)
      {
        delay_index = 0;
      }
      delay = delays[delay_index];
      sprintf(title, "delay = %d ms", delay / 1000);
      XChangeProperty(dpy, win, XA_WM_NAME, XA_STRING, 8, PropModeReplace, (unsigned char *) title, strlen(title));
      signal(SIGALRM, timeout_func);
      alarm(2);
      break;
    }

    case 'q':
    {
      exit(0);
      break;
    }

  }

  break;
  *scroll_ref = scroll;
}

void helper_helper_helper_helper_main_2_1_1_1()
{
  if (!yzoom_flag)
  {
    magx -= 1;
  }
  if (!xzoom_flag)
  {
    magy -= 1;
  }
  xzoom_flag = (yzoom_flag = False);
  if (magx < 1)
  {
    magx = 1;
  }
  if (magy < 1)
  {
    magy = 1;
  }
  resize(width[1], height[1]);
  set_title = True;
  break;
}

