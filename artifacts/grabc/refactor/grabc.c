#include <Xatom.h>
#include <Xlib.h>
#include <Xos.h>
#include <Xproto.h>
#include <Xresource.h>
#include <Xutil.h>
#include <_X11_fake_defines.h>
#include <_X11_fake_typedefs.h>
#include <assert.h>
#include <ctype.h>
#include <cursorfont.h>
#include <errno.h>
#include <keysym.h>
#include <math.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
static int g_debug = 0;
static int g_print_in_hex = 1;
static int g_print_in_rgb = 0;
static int g_print_all_16_bits = 0;
static Window g_window_id = (Window) 0;
static int g_loc_specified = 0;
static int g_x = 1;
static int g_y = 1;
static unsigned int g_width = 0;
static unsigned int g_height = 0;
static Cursor g_cross_cursor = (Cursor) 0;
static Window select_window(Display *, int *x, int *y);
static Window findSubWindow(Display *display, Window top_winodw, Window window_to_check, int *x, int *y);
static Window get_window_color(Display *display, XColor *color);
static int MXError(Display *display, XErrorEvent *error);
static void show_usage(void)
{
  char **p;
  unsigned int p_idx = 0;
  static char *options[] = {" -v      - show version info", " -h      - show this usage", " -hex    - print pixel value as Hex on stdout", " -rgb    - print pixel value as RGB on stderr", " -W      - print the Window id at mouse click", " -w id   - window id in hex, use -l +x+y", " -l +x+y - pixel co-ordinate. requires window id", " -d      - show debug messages", " -a      - Print all 16 bits RGB components of color", "           Default is high order 8 bits of components", "Example:", "* Print pixel color in hex on stdout:", "   $ grabc", "* Show usage:", "   $ grabc -h", "* Print Window Id (Note the upper case W):", "   $ grabc -W", "* Print pixel color of Window iwith id 0x13234 at location 10,20", "   $ grabc -w 0x13234 -l +10+20", (char *) 0};
  (void) printf("\n");
  (void) printf("grabc v%s\n", "1.0.2");
  (void) printf("A program to identify a pixel color of an X Window\n");
  (void) printf("by muquit@muquit.com https://www.muquit.com/\n\n");
  (void) printf("Usage: grabc [options]\n");
  (void) printf("Where the options are:\n");
  for (p_idx = options; p[p_idx] != 0; p_idx += 1)
  {
    (void) fprintf(stdout, "%s\n", *(&p[p_idx]));
    (void) fflush(stdout);
  }

}

static void log_debug(const char *fmt, ...)
{
  va_list args;
  if (!g_debug)
  {
    return;
  }
  __builtin_va_start(args);
  (void) fprintf(stderr, "[Debug]: ");
  vfprintf(stderr, fmt, args);
  (void) fprintf(stderr, "\n");
  ;
}

static Cursor get_cross_cursor(Display *display)
{
  if (g_cross_cursor == ((Cursor) 0))
  {
    g_cross_cursor = XCreateFontCursor(display, XC_tcross);
    if (g_cross_cursor == ((Cursor) 0))
    {
      (void) fprintf(stderr, "ERROR: Failed to create Cross Cursor!\n");
      exit(1);
    }
  }
  return g_cross_cursor;
}

static Window grab_mouse(Display *display, Window root_window)
{
  int status;
  Window subwindow;
  XEvent event;
  Cursor target_cursor;
  if (g_window_id != ((Window) 0))
  {
    return g_window_id;
  }
  target_cursor = get_cross_cursor(display);
  status = XGrabPointer(display, root_window, 0, (unsigned int) ButtonPressMask, GrabModeSync, GrabModeAsync, root_window, target_cursor, CurrentTime);
  if (status == GrabSuccess)
  {
    XAllowEvents(display, SyncPointer, CurrentTime);
    XWindowEvent(display, root_window, ButtonPressMask, &event);
    subwindow = event.xbutton.subwindow;
  }
  else
  {
    return root_window;
  }
  return subwindow;
}

static void upgrab_mouse(Display *display)
{
  if (g_window_id != ((Window) 0))
  {
    XUngrabPointer(display, CurrentTime);
  }
}

static Window select_window(Display *display, int *x, int *y)
{
  Cursor target_cursor;
  int status;
  Window target_window;
  Window root_window;
  XEvent event;
  if ((g_window_id != ((Window) 0)) && g_loc_specified)
  {
    log_debug("Returning passing window: %lx", g_window_id);
    *x = g_x;
    *y = g_y;
    return g_window_id;
  }
  target_window = (Window) 0;
  target_cursor = get_cross_cursor(display);
  root_window = XRootWindow(display, XDefaultScreen(display));
  status = XGrabPointer(display, root_window, 0, (unsigned int) ButtonPressMask, GrabModeSync, GrabModeAsync, root_window, target_cursor, CurrentTime);
  if (status == GrabSuccess)
  {
    XAllowEvents(display, SyncPointer, CurrentTime);
    XWindowEvent(display, root_window, ButtonPressMask, &event);
    Window subwindow = event.xbutton.subwindow;
    if (event.type == ButtonPress)
    {
      target_window = findSubWindow(display, root_window, subwindow, &event.xbutton.x, &event.xbutton.y);
      if (target_window == ((Window) 0))
      {
        (void) fprintf(stderr, "ERROR: Failed to get target window, getting root window!\n");
        target_window = root_window;
      }
      if (!g_loc_specified)
      {
        XUngrabPointer(display, CurrentTime);
      }
    }
  }
  else
  {
    (void) fprintf(stderr, "ERROR: Failed to grab mouse pointer!\n");
    exit(1);
  }
  *x = event.xbutton.x;
  *y = event.xbutton.y;
  return target_window;
}

static Window findSubWindow(Display *display, Window top_window, Window window_to_check, int *x, int *y)
{
  int newx;
  int newy;
  Window window;
  if (top_window == ((Window) 0))
  {
    return (Window) 0;
  }
  if (window_to_check == ((Window) 0))
  {
    return (Window) 0;
  }
  window = window_to_check;
  while ((XTranslateCoordinates(display, top_window, window_to_check, *x, *y, &newx, &newy, &window) != 0) && (window != ((Window) 0)))
  {
    if (window != ((Window) 0))
    {
      top_window = window_to_check;
      window_to_check = window;
      *x = newx;
      *y = newy;
    }
  }

  if (window == ((Window) 0))
  {
    window = window_to_check;
  }
  *x = newx;
  *y = newy;
  return window;
}

static Window get_window_color(Display *display, XColor *color)
{
  Window root_window;
  Window target_window;
  XImage *ximage;
  unsigned int ximage_idx = 0;
  int x;
  int y;
  Status status;
  root_window = XRootWindow(display, XDefaultScreen(display));
  target_window = select_window(display, &x, &y);
  log_debug("  Root Window Id: 0x%08lx", root_window);
  log_debug("Target Window Id: 0x%08lx  X,Y: +%d+%d", target_window, x, y);
  if (target_window == ((Window) 0))
  {
    return (Window) 0;
  }
  ximage_idx = XGetImage(display, target_window, x, y, 1, 1, AllPlanes, ZPixmap);
  if ((&ximage[ximage_idx]) == ((XImage *) 0))
  {
    log_debug("Could not get XImage from Window: 0x%08lx", target_window);
    log_debug("Trying to get XImage from root window: 0x%08lx", root_window);
    ximage_idx = XGetImage(display, root_window, x, y, 1, 1, AllPlanes, ZPixmap);
    if ((&ximage[ximage_idx]) == ((XImage *) 0))
    {
      log_debug("Could not get XImage from target or root window");
      return (Window) 0;
    }
    else
    {
      log_debug("OK successfully got XImage from root window");
      target_window = root_window;
    }
  }
  color->pixel = XGetPixel(ximage, 0, 0);
  XDestroyImage(ximage);
  return target_window;
}

static int MXError(Display *display, XErrorEvent *error)
{
  int xerrcode;
  xerrcode = error->error_code;
  if ((xerrcode == BadAlloc) || ((xerrcode == BadAccess) && (error->request_code == 88)))
  {
    return 0;
  }
  else
  {
    switch (error->request_code)
    {
      case X_GetGeometry:
      {
        if (error->error_code == BadDrawable)
        {
          return 0;
        }
        break;
      }

      case X_GetWindowAttributes:

      case X_QueryTree:
      {
        if (error->error_code == BadWindow)
        {
          return 0;
        }
        break;
      }

      case X_QueryColors:
      {
        if (error->error_code == BadValue)
        {
          return 0;
        }
        break;
      }

    }

  }
  return 1;
}

int main(int argc, char **argv)
{
  Display *display;
  unsigned int display_idx = 0;
  int x;
  int y;
  int status;
  XColor color;
  int rc;
  int i;
  int r;
  int g;
  int b;
  Window window_id;
  Window target_window;
  XWindowAttributes window_attributes;
  char *option;
  unsigned int option_idx = 0;
  for (i = 1; i < argc; i += 1)
  {
    helper_main_2(&display_idx, &rc, &i, &option_idx, argc, argv, display, x, y, option);
  }

  if (g_loc_specified && (g_window_id == ((Window) 0)))
  {
    (void) fprintf(stderr, "ERROR: Please specify window id with -w in hex to use this option\n");
    (void) fprintf(stderr, "Use -W option to find the Window Id\n");
    return 1;
  }
  display_idx = XOpenDisplay((char *) 0);
  XSetErrorHandler(MXError);
  if ((&display[display_idx]) == ((Display *) 0))
  {
    (void) fprintf(stderr, "ERROR: Failed to open DISPLAY!\n");
    exit(1);
  }
  target_window = get_window_color(display, &color);
  if (target_window != ((Window) 0))
  {
    helper_main_1(&status, &r, &g, &b, display, color, target_window, window_attributes);
  }
  else
  {
    (void) fprintf(stderr, "ERROR: Failed to grab color!\n");
  }
  return 0;
}

int helper_main_1(int * const status_ref, int * const r_ref, int * const g_ref, int * const b_ref, Display * const display, XColor color, Window target_window, XWindowAttributes window_attributes)
{
  int status = *status_ref;
  int r = *r_ref;
  int g = *g_ref;
  int b = *b_ref;
  status = XGetWindowAttributes(display, target_window, &window_attributes);
  if ((status == 0) || (window_attributes.map_state != IsViewable))
  {
    (void) fprintf(stderr, "ERROR: Could not get Window Attributes\n");
    return 1;
  }
  XQueryColor(display, window_attributes.colormap, &color);
  if (g_print_all_16_bits)
  {
    (void) fprintf(stdout, "#%04x%04x%04x\n", (unsigned int) color.red, (unsigned int) color.green, (unsigned int) color.blue);
    (void) fflush(stdout);
    if (g_print_in_rgb)
    {
      (void) fprintf(stderr, "%d,%d,%d\n", (unsigned int) color.red, (unsigned int) color.green, (unsigned int) color.blue);
    }
  }
  else
  {
    r = color.red >> 8;
    g = color.green >> 8;
    b = color.blue >> 8;
    log_debug("Color: #%02x%02x%02x", r, g, b);
    (void) fprintf(stdout, "#%02x%02x%02x\n", r, g, b);
    (void) fflush(stdout);
    if (g_print_in_rgb)
    {
      (void) fprintf(stderr, "%d,%d,%d\n", r, g, b);
    }
  }
  *status_ref = status;
  *r_ref = r;
  *g_ref = g;
  *b_ref = b;
}

int helper_main_2(unsigned int * const display_idx_ref, int * const rc_ref, int * const i_ref, unsigned int * const option_idx_ref, int argc, char ** const argv, Display * const display, int x, int y, char * const option)
{
  unsigned int display_idx = *display_idx_ref;
  int rc = *rc_ref;
  int i = *i_ref;
  unsigned int option_idx = *option_idx_ref;
  option_idx = argv[i];
  switch (*((&option[option_idx]) + 1))
  {
    case 'a':
    {
      g_print_all_16_bits = 1;
      break;
    }

    case 'd':
    {
      g_debug = 1;
      break;
    }

    case 'h':
    {
      if (strncmp("hex", (&option[option_idx]) + 1, 3) == 0)
      {
        g_print_in_hex = 1;
      }
      else
      {
        show_usage();
        return 1;
      }
      break;
    }

    case 'r':
    {
      if (strncmp("rgb", (&option[option_idx]) + 1, 3) == 0)
      {
        g_print_in_rgb = 1;
      }
      break;
    }

    case 'w':
    {
      if (option[option_idx] == '-')
      {
        i += 1;
        if (i == argc)
        {
          (void) fprintf(stderr, "ERROR: Missing Window id\n");
          return 1;
        }
      }
      g_window_id = (Window) strtol(argv[i], 0, 16);
      break;
    }

    case 'W':
    {
      display_idx = XOpenDisplay((char *) 0);
      if ((&display[display_idx]) == 0)
      {
        (void) fprintf(stderr, "ERROR: Could not open Display\n");
        return 1;
      }
      Window window = select_window(display, &x, &y);
      if (window != ((Window) 0))
      {
        log_debug("Window ID: 0x%08lx", window);
        (void) fprintf(stdout, "0x%lx\n", window);
      }
      return 1;
      break;
    }

    case 'l':
    {
      helper_helper_main_2_1(&rc, &i, argc, argv, option, option_idx);
    }

    case 'v':
    {
      (void) fprintf(stderr, "grabc v%s\n", "1.0.2");
      return 1;
      break;
    }

    default:
    {
      break;
    }

  }

  *display_idx_ref = display_idx;
  *rc_ref = rc;
  *i_ref = i;
  *option_idx_ref = option_idx;
}

int helper_helper_main_2_1(int * const rc_ref, int * const i_ref, int argc, char ** const argv, char * const option, unsigned int option_idx)
{
  int rc = *rc_ref;
  int i = *i_ref;
  if (option[option_idx] == '-')
  {
    i += 1;
    if (i == argc)
    {
      (void) fprintf(stderr, "ERROR: Missing location +x+y\n");
      return 1;
    }
  }
  rc = XParseGeometry(argv[i], &g_x, &g_y, &g_width, &g_height);
  if (rc == 0)
  {
    (void) fprintf(stderr, "ERROR: Could not parse location: %s\n", argv[i]);
    (void) fprintf(stderr, "Example: -l +10+20\n");
    return 1;
  }
  g_loc_specified = 1;
  break;
  *rc_ref = rc;
  *i_ref = i;
}

