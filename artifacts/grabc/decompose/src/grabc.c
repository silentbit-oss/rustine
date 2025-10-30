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


/*** DEPENDENCIES:
***/


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


/*** DEPENDENCIES:
static int g_debug = 0
----------------------------
***/


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


/*** DEPENDENCIES:
pub type Display = _XDisplay;
----------------------------
pub type Window = XID;
----------------------------
pub fn XTranslateCoordinates(
        arg1: *mut Display,
        arg2: Window,
        arg3: Window,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut std::os::raw::c_int,
        arg7: *mut std::os::raw::c_int,
        arg8: *mut Window,
    ) -> std::os::raw::c_int;
----------------------------
***/


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


/*** DEPENDENCIES:
pub type Display = _XDisplay;
----------------------------
pub struct XErrorEvent {
    pub type_: std::os::raw::c_int,
    pub display: *mut Display,
    pub resourceid: XID,
    pub serial: std::os::raw::c_ulong,
    pub error_code: std::os::raw::c_uchar,
    pub request_code: std::os::raw::c_uchar,
    pub minor_code: std::os::raw::c_uchar,
}
----------------------------
***/


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


/*** DEPENDENCIES:
static Cursor g_cross_cursor = (Cursor) 0
----------------------------
pub type Display = _XDisplay;
----------------------------
pub fn XCreateFontCursor(arg1: *mut Display, arg2: std::os::raw::c_uint) -> Cursor;
----------------------------
***/


static void upgrab_mouse(Display *display)
{
  if (g_window_id != ((Window) 0))
  {
    XUngrabPointer(display, CurrentTime);
  }
}


/*** DEPENDENCIES:
static Window g_window_id = (Window) 0
----------------------------
pub type Display = _XDisplay;
----------------------------
pub fn XUngrabPointer(arg1: *mut Display, arg2: Time) -> std::os::raw::c_int;
----------------------------
***/


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


/*** DEPENDENCIES:
static int g_x = 1
----------------------------
static int g_y = 1
----------------------------
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


----------------------------
static int g_loc_specified = 0
----------------------------
pub type XEvent = _XEvent;
----------------------------
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


----------------------------
static Window g_window_id = (Window) 0
----------------------------
pub type Display = _XDisplay;
----------------------------
pub type Window = XID;
----------------------------
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


----------------------------
pub type Cursor = XID;
----------------------------
pub fn XWindowEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_long,
        arg4: *mut XEvent,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XUngrabPointer(arg1: *mut Display, arg2: Time) -> std::os::raw::c_int;
----------------------------
pub fn XRootWindow(arg1: *mut Display, arg2: std::os::raw::c_int) -> Window;
----------------------------
pub fn XGrabPointer(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: Window,
        arg8: Cursor,
        arg9: Time,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XAllowEvents(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: Time,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XDefaultScreen(arg1: *mut Display) -> std::os::raw::c_int;
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
pub type Display = _XDisplay;
----------------------------
pub struct XColor {
    pub pixel: std::os::raw::c_ulong,
    pub red: std::os::raw::c_ushort,
    pub green: std::os::raw::c_ushort,
    pub blue: std::os::raw::c_ushort,
    pub flags: std::os::raw::c_char,
    pub pad: std::os::raw::c_char,
}
----------------------------
pub type Window = XID;
----------------------------
None
----------------------------
pub fn XGetImage(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_ulong,
        arg8: std::os::raw::c_int,
    ) -> *mut XImage;
----------------------------
pub fn XRootWindow(arg1: *mut Display, arg2: std::os::raw::c_int) -> Window;
----------------------------
pub fn XDefaultScreen(arg1: *mut Display) -> std::os::raw::c_int;
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
pub type XEvent = _XEvent;
----------------------------
static Window g_window_id = (Window) 0
----------------------------
pub type Display = _XDisplay;
----------------------------
pub type Window = XID;
----------------------------
pub type Cursor = XID;
----------------------------
pub fn XAllowEvents(
        arg1: *mut Display,
        arg2: std::os::raw::c_int,
        arg3: Time,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XGrabPointer(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_uint,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: Window,
        arg8: Cursor,
        arg9: Time,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XWindowEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_long,
        arg4: *mut XEvent,
    ) -> std::os::raw::c_int;
----------------------------
***/


// hint:  ['status_ref is a mutable refrence to int', 'r_ref is a mutable refrence to int', 'g_ref is a mutable refrence to int', 'b_ref is a mutable refrence to int']
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


/*** DEPENDENCIES:
pub type Window = XID;
----------------------------
static int g_print_in_rgb = 0
----------------------------
static int g_print_all_16_bits = 0
----------------------------
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


----------------------------
pub struct XWindowAttributes {
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub depth: std::os::raw::c_int,
    pub visual: *mut Visual,
    pub root: Window,
    pub class: std::os::raw::c_int,
    pub bit_gravity: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub backing_planes: std::os::raw::c_ulong,
    pub backing_pixel: std::os::raw::c_ulong,
    pub save_under: std::os::raw::c_int,
    pub colormap: Colormap,
    pub map_installed: std::os::raw::c_int,
    pub map_state: std::os::raw::c_int,
    pub all_event_masks: std::os::raw::c_long,
    pub your_event_mask: std::os::raw::c_long,
    pub do_not_propagate_mask: std::os::raw::c_long,
    pub override_redirect: std::os::raw::c_int,
    pub screen: *mut Screen,
}
----------------------------
pub type Display = _XDisplay;
----------------------------
pub struct XColor {
    pub pixel: std::os::raw::c_ulong,
    pub red: std::os::raw::c_ushort,
    pub green: std::os::raw::c_ushort,
    pub blue: std::os::raw::c_ushort,
    pub flags: std::os::raw::c_char,
    pub pad: std::os::raw::c_char,
}
----------------------------
pub fn XQueryColor(
        arg1: *mut Display,
        arg2: Colormap,
        arg3: *mut XColor,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XGetWindowAttributes(
        arg1: *mut Display,
        arg2: Window,
        arg3: *mut XWindowAttributes,
    ) -> std::os::raw::c_int;
----------------------------
***/


// hint:  ['display_idx_ref is a mutable refrence to unsigned int', 'rc_ref is a mutable refrence to int', 'i_ref is a mutable refrence to int', 'option_idx_ref is a mutable refrence to unsigned int']
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


/*** DEPENDENCIES:
static int g_x = 1
----------------------------
static int g_y = 1
----------------------------
static int g_print_in_hex = 1
----------------------------
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


----------------------------
static int g_debug = 0
----------------------------
static unsigned int g_height = 0
----------------------------
static int g_print_in_rgb = 0
----------------------------
static int g_loc_specified = 0
----------------------------
static int g_print_all_16_bits = 0
----------------------------
static unsigned int g_width = 0
----------------------------
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


----------------------------
static Window g_window_id = (Window) 0
----------------------------
pub type Display = _XDisplay;
----------------------------
pub type Window = XID;
----------------------------
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


----------------------------
pub fn XOpenDisplay(arg1: *const std::os::raw::c_char) -> *mut Display;
----------------------------
pub fn XParseGeometry(
        arg1: *const std::os::raw::c_char,
        arg2: *mut std::os::raw::c_int,
        arg3: *mut std::os::raw::c_int,
        arg4: *mut std::os::raw::c_uint,
        arg5: *mut std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
pub type Window = XID;
----------------------------
static int g_loc_specified = 0
----------------------------
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


----------------------------
pub struct XWindowAttributes {
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub depth: std::os::raw::c_int,
    pub visual: *mut Visual,
    pub root: Window,
    pub class: std::os::raw::c_int,
    pub bit_gravity: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub backing_planes: std::os::raw::c_ulong,
    pub backing_pixel: std::os::raw::c_ulong,
    pub save_under: std::os::raw::c_int,
    pub colormap: Colormap,
    pub map_installed: std::os::raw::c_int,
    pub map_state: std::os::raw::c_int,
    pub all_event_masks: std::os::raw::c_long,
    pub your_event_mask: std::os::raw::c_long,
    pub do_not_propagate_mask: std::os::raw::c_long,
    pub override_redirect: std::os::raw::c_int,
    pub screen: *mut Screen,
}
----------------------------
static Window g_window_id = (Window) 0
----------------------------
pub type Display = _XDisplay;
----------------------------
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


----------------------------
pub struct XColor {
    pub pixel: std::os::raw::c_ulong,
    pub red: std::os::raw::c_ushort,
    pub green: std::os::raw::c_ushort,
    pub blue: std::os::raw::c_ushort,
    pub flags: std::os::raw::c_char,
    pub pad: std::os::raw::c_char,
}
----------------------------
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


----------------------------
pub fn XSetErrorHandler(arg1: XErrorHandler) -> XErrorHandler;
----------------------------
pub fn XOpenDisplay(arg1: *const std::os::raw::c_char) -> *mut Display;
----------------------------
***/


