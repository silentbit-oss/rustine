void timeout_func(int signum)
{
  set_title = True;
}


/*** DEPENDENCIES:
int set_title
----------------------------
***/


void destroy_images(void)
{
  int i;
  for (i = 0; i < 2; i += 1)
  {
    free(ximage[i]->data);
    ximage[i]->data = 0;
    XDestroyImage(ximage[i]);
  }

}


/*** DEPENDENCIES:
XImage *ximage[2]
----------------------------
***/


void Usage(void)
{
  fprintf(stderr, "Usage: %s [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next '+' or '-' only change width scaling\nh: Next '+' or '-' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n", progname);
  exit(1);
}


/*** DEPENDENCIES:
char *progname
----------------------------
***/


void allocate_images(void)
{
  int i;
  char *data;
  unsigned int data_idx = 0;
  for (i = 0; i < 2; i += 1)
  {
    data_idx = malloc(width[i] * height[i]);
    ximage[i] = XCreateImage(dpy, DefaultVisualOfScreen(scr), DefaultDepthOfScreen(scr), ZPixmap, 0, data, width[i], height[i], 8, width[i]);
    if (ximage[i] == 0)
    {
      perror("XCreateImage");
      exit(-1);
    }
  }

  created_images = True;
}


/*** DEPENDENCIES:
Screen *scr
----------------------------
int width[2] = {0, 256}
----------------------------
Display *dpy
----------------------------
int created_images = False
----------------------------
XImage *ximage[2]
----------------------------
int height[2] = {0, 256}
----------------------------
pub fn XCreateImage(
        arg1: *mut Display,
        arg2: *mut Visual,
        arg3: std::os::raw::c_uint,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_int,
        arg6: *mut std::os::raw::c_char,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_uint,
        arg9: std::os::raw::c_int,
        arg10: std::os::raw::c_int,
    ) -> *mut XImage;
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int', 'k_ref is a mutable refrence to int', 'c_ref is a mutable refrence to char', 'p1_idx_ref is a mutable refrence to unsigned int', 'p2_idx_ref is a mutable refrence to unsigned int']
void helper_helper_main_2_1(int * const i_ref, int * const k_ref, char * const c_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, char * const p1, char * const p2, int j)
{
  int i = *i_ref;
  int k = *k_ref;
  char c = *c_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  p1_idx = &ximage[1]->data[ximage[1]->xoffset + ((j * magy) * ximage[1]->bytes_per_line)];
  p2_idx = &ximage[0]->data[ximage[0]->xoffset + (((flipy) ? ((height[0] - 1) - j) : (j)) * ximage[0]->bytes_per_line)];
  if (flipxy)
  {
    int p2step = ximage[0]->bytes_per_line;
    p2_idx = &ximage[0]->data[ximage[0]->xoffset + ((flipy) ? (j) : ((width[0] - 1) - j))];
    if (flipx)
    {
      p2_idx += p2step * (height[0] - 1);
      p2step = -p2step;
    }
    for (i = height[0]; (--i) >= 0;)
    {
      c = (p1[p1_idx] = p2[p2_idx]);
      p1_idx += 1;
      p2_idx += p2step;
      for (k = magx; (--k) > 0;)
        *((&p1[p1_idx])++) = c;

    }

  }
  else
    if (flipx)
  {
    p2_idx += width[0];
    for (i = width[0]; (--i) >= 0;)
    {
      p2_idx -= 1;
      c = (p1[p1_idx] = p2[p2_idx]);
      p1_idx += 1;
      for (k = magx; (--k) > 0;)
        *((&p1[p1_idx])++) = c;

    }

  }
  else
  {
    for (i = width[0]; (--i) >= 0;)
    {
      c = (p1[p1_idx] = p2[p2_idx]);
      p2_idx += 1;
      p1_idx += 1;
      for (k = magx; (--k) > 0;)
        *((&p1[p1_idx])++) = c;

    }

  }
  p1_idx = &ximage[1]->data[ximage[1]->xoffset + ((j * magy) * ximage[1]->bytes_per_line)];
  p2_idx = (&p1[p1_idx]) + ximage[1]->bytes_per_line;
  for (k = magy; (--k) > 0;)
  {
    memmove(p2, p1, width[1]);
    p2_idx += ximage[1]->bytes_per_line;
  }

  *i_ref = i;
  *k_ref = k;
  *c_ref = c;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
}


/*** DEPENDENCIES:
int width[2] = {0, 256}
----------------------------
int flipy = False
----------------------------
XImage *ximage[2]
----------------------------
int magx = 2
----------------------------
int height[2] = {0, 256}
----------------------------
int magy = 2
----------------------------
int flipxy = False
----------------------------
int flipx = False
----------------------------
***/


void resize(int new_width, int new_height)
{
  if (created_images)
  {
    destroy_images();
  }
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
  if (width[0] > WidthOfScreen(scr))
  {
    width[0] = WidthOfScreen(scr);
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


/*** DEPENDENCIES:
Screen *scr
----------------------------
void destroy_images(void)
{
  int i;
  for (i = 0; i < 2; i += 1)
  {
    free(ximage[i]->data);
    ximage[i]->data = 0;
    XDestroyImage(ximage[i]);
  }

}


----------------------------
int width[2] = {0, 256}
----------------------------
int created_images = False
----------------------------
int magx = 2
----------------------------
int height[2] = {0, 256}
----------------------------
int magy = 2
----------------------------
void allocate_images(void)
{
  int i;
  char *data;
  unsigned int data_idx = 0;
  for (i = 0; i < 2; i += 1)
  {
    data_idx = malloc(width[i] * height[i]);
    ximage[i] = XCreateImage(dpy, DefaultVisualOfScreen(scr), DefaultDepthOfScreen(scr), ZPixmap, 0, data, width[i], height[i], 8, width[i]);
    if (ximage[i] == 0)
    {
      perror("XCreateImage");
      exit(-1);
    }
  }

  created_images = True;
}


----------------------------
int flipxy = False
----------------------------
***/


// hint:  ['argc_ref is a mutable refrence to int', 'argv_idx_ref is a mutable refrence to unsigned int', 'dpyname_idx_ref is a mutable refrence to unsigned int', 'source_geom_mask_ref is a mutable refrence to int', 'dest_geom_mask_ref is a mutable refrence to int']
void helper_main_1(int * const argc_ref, unsigned int * const argv_idx_ref, unsigned int * const dpyname_idx_ref, int * const source_geom_mask_ref, int * const dest_geom_mask_ref, char ** const argv, int xpos, int ypos)
{
  int argc = *argc_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int dpyname_idx = *dpyname_idx_ref;
  int source_geom_mask = *source_geom_mask_ref;
  int dest_geom_mask = *dest_geom_mask_ref;
  argv_idx += 1;
  if (argv[0 + argv_idx][0] == '=')
  {
    dest_geom_mask = XParseGeometry(argv[0 + argv_idx], &xpos, &ypos, &width[1], &height[1]);
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-mag"))
  {
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
  Usage();
  *argc_ref = argc;
  *argv_idx_ref = argv_idx;
  *dpyname_idx_ref = dpyname_idx;
  *source_geom_mask_ref = source_geom_mask;
  *dest_geom_mask_ref = dest_geom_mask;
}


/*** DEPENDENCIES:
int xgrab
----------------------------
int width[2] = {0, 256}
----------------------------
void Usage(void)
{
  fprintf(stderr, "Usage: %s [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next '+' or '-' only change width scaling\nh: Next '+' or '-' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n", progname);
  exit(1);
}


----------------------------
int flipy = False
----------------------------
int delay = 200000
----------------------------
int magx = 2
----------------------------
int height[2] = {0, 256}
----------------------------
int magy = 2
----------------------------
int ygrab
----------------------------
int flipxy = False
----------------------------
int flipx = False
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


// hint:  ['scroll_ref is a mutable refrence to int']
void helper_helper_helper_main_2_2_1(int * const scroll_ref, XEvent event, char title[80])
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

    case XK_Left:
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


/*** DEPENDENCIES:
int width[2] = {0, 256}
----------------------------
Display *dpy
----------------------------
Window win
----------------------------
pub type XEvent = _XEvent;
----------------------------
int delay = 200000
----------------------------
int yzoom_flag = False
----------------------------
int flipx = False
----------------------------
int xgrab
----------------------------
int flipy = False
----------------------------
int delays[5] = {200000, 100000, 50000, 10000, 0}
----------------------------
void timeout_func(int signum)
{
  set_title = True;
}


----------------------------
int set_title
----------------------------
int flipxy = False
----------------------------
int delay_index = 0
----------------------------
int magy = 2
----------------------------
int ygrab
----------------------------
int xzoom_flag = False
----------------------------
int magx = 2
----------------------------
int height[2] = {0, 256}
----------------------------
void resize(int new_width, int new_height)
{
  if (created_images)
  {
    destroy_images();
  }
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
  if (width[0] > WidthOfScreen(scr))
  {
    width[0] = WidthOfScreen(scr);
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


----------------------------
pub fn XChangeProperty(
        arg1: *mut Display,
        arg2: Window,
        arg3: Atom,
        arg4: Atom,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_uchar,
        arg8: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XKeycodeToKeysym(arg1: *mut Display, arg2: KeyCode, arg3: std::os::raw::c_int)
        -> KeySym;
----------------------------
***/


// hint:  ['buttonpressed_ref is a mutable refrence to int', 'unmapped_ref is a mutable refrence to int', 'scroll_ref is a mutable refrence to int']
void helper_helper_main_2_2(int * const buttonpressed_ref, int * const unmapped_ref, int * const scroll_ref, XEvent event, char title[80])
{
  int buttonpressed = *buttonpressed_ref;
  int unmapped = *unmapped_ref;
  int scroll = *scroll_ref;
  switch (event.type)
  {
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

    case MapNotify:
    {
      unmapped = False;
      break;
    }

    case UnmapNotify:
    {
      unmapped = True;
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
      helper_helper_helper_main_2_2_1(&scroll, event, title);
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
  *unmapped_ref = unmapped;
  *scroll_ref = scroll;
}


/*** DEPENDENCIES:
Screen *scr
----------------------------
int xgrab
----------------------------
int width[2] = {0, 256}
----------------------------
Display *dpy
----------------------------
void helper_helper_helper_main_2_2_1(int * const scroll_ref, XEvent event, char title[80])
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

    case XK_Left:
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


----------------------------
Cursor when_button
----------------------------
Window win
----------------------------
pub type XEvent = _XEvent;
----------------------------
int height[2] = {0, 256}
----------------------------
void resize(int new_width, int new_height)
{
  if (created_images)
  {
    destroy_images();
  }
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
  if (width[0] > WidthOfScreen(scr))
  {
    width[0] = WidthOfScreen(scr);
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


----------------------------
Cursor crosshair
----------------------------
int ygrab
----------------------------
pub fn XDefineCursor(arg1: *mut Display, arg2: Window, arg3: Cursor) -> std::os::raw::c_int;
----------------------------
pub fn XKeycodeToKeysym(arg1: *mut Display, arg2: KeyCode, arg3: std::os::raw::c_int)
        -> KeySym;
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int', 'j_ref is a mutable refrence to int', 'k_ref is a mutable refrence to int', 'c_ref is a mutable refrence to char', 'p1_idx_ref is a mutable refrence to unsigned int', 'p2_idx_ref is a mutable refrence to unsigned int', 'buttonpressed_ref is a mutable refrence to int', 'unmapped_ref is a mutable refrence to int', 'scroll_ref is a mutable refrence to int']
void helper_main_2(int * const i_ref, int * const j_ref, int * const k_ref, char * const c_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const buttonpressed_ref, int * const unmapped_ref, int * const scroll_ref, char * const p1, char * const p2, XEvent event, char title[80])
{
  int i = *i_ref;
  int j = *j_ref;
  int k = *k_ref;
  char c = *c_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int buttonpressed = *buttonpressed_ref;
  int unmapped = *unmapped_ref;
  int scroll = *scroll_ref;
  while ((unmapped) ? ((XWindowEvent(dpy, win, (long) (-1), &event), 1)) : (XCheckWindowEvent(dpy, win, (long) (-1), &event)))
  {
    helper_helper_main_2_2(&buttonpressed, &unmapped, &scroll, event, title);
  }

  XGetSubImage(dpy, RootWindowOfScreen(scr), xgrab, ygrab, width[0], height[0], AllPlanes, ZPixmap, ximage[0], 0, 0);
  for (j = (flipxy) ? (width[0]) : (height[0]); (--j) >= 0;)
  {
    helper_helper_main_2_1(&i, &k, &c, &p1_idx, &p2_idx, p1, p2, j);
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
  if ((!buttonpressed) && (delay > 0))
  {
    usleep(delay);
  }
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
  *c_ref = c;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *buttonpressed_ref = buttonpressed;
  *unmapped_ref = unmapped;
  *scroll_ref = scroll;
}


/*** DEPENDENCIES:
Screen *scr
----------------------------
int width[2] = {0, 256}
----------------------------
Display *dpy
----------------------------
Window win
----------------------------
pub type XEvent = _XEvent;
----------------------------
int delay = 200000
----------------------------
int flipx = False
----------------------------
int xgrab
----------------------------
GC gc
----------------------------
int flipy = False
----------------------------
char *progname
----------------------------
int set_title
----------------------------
int flipxy = False
----------------------------
int magy = 2
----------------------------
void helper_helper_main_2_2(int * const buttonpressed_ref, int * const unmapped_ref, int * const scroll_ref, XEvent event, char title[80])
{
  int buttonpressed = *buttonpressed_ref;
  int unmapped = *unmapped_ref;
  int scroll = *scroll_ref;
  switch (event.type)
  {
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

    case MapNotify:
    {
      unmapped = False;
      break;
    }

    case UnmapNotify:
    {
      unmapped = True;
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
      helper_helper_helper_main_2_2_1(&scroll, event, title);
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
  *unmapped_ref = unmapped;
  *scroll_ref = scroll;
}


----------------------------
int ygrab
----------------------------
XImage *ximage[2]
----------------------------
int magx = 2
----------------------------
int height[2] = {0, 256}
----------------------------
void helper_helper_main_2_1(int * const i_ref, int * const k_ref, char * const c_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, char * const p1, char * const p2, int j)
{
  int i = *i_ref;
  int k = *k_ref;
  char c = *c_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  p1_idx = &ximage[1]->data[ximage[1]->xoffset + ((j * magy) * ximage[1]->bytes_per_line)];
  p2_idx = &ximage[0]->data[ximage[0]->xoffset + (((flipy) ? ((height[0] - 1) - j) : (j)) * ximage[0]->bytes_per_line)];
  if (flipxy)
  {
    int p2step = ximage[0]->bytes_per_line;
    p2_idx = &ximage[0]->data[ximage[0]->xoffset + ((flipy) ? (j) : ((width[0] - 1) - j))];
    if (flipx)
    {
      p2_idx += p2step * (height[0] - 1);
      p2step = -p2step;
    }
    for (i = height[0]; (--i) >= 0;)
    {
      c = (p1[p1_idx] = p2[p2_idx]);
      p1_idx += 1;
      p2_idx += p2step;
      for (k = magx; (--k) > 0;)
        *((&p1[p1_idx])++) = c;

    }

  }
  else
    if (flipx)
  {
    p2_idx += width[0];
    for (i = width[0]; (--i) >= 0;)
    {
      p2_idx -= 1;
      c = (p1[p1_idx] = p2[p2_idx]);
      p1_idx += 1;
      for (k = magx; (--k) > 0;)
        *((&p1[p1_idx])++) = c;

    }

  }
  else
  {
    for (i = width[0]; (--i) >= 0;)
    {
      c = (p1[p1_idx] = p2[p2_idx]);
      p2_idx += 1;
      p1_idx += 1;
      for (k = magx; (--k) > 0;)
        *((&p1[p1_idx])++) = c;

    }

  }
  p1_idx = &ximage[1]->data[ximage[1]->xoffset + ((j * magy) * ximage[1]->bytes_per_line)];
  p2_idx = (&p1[p1_idx]) + ximage[1]->bytes_per_line;
  for (k = magy; (--k) > 0;)
  {
    memmove(p2, p1, width[1]);
    p2_idx += ximage[1]->bytes_per_line;
  }

  *i_ref = i;
  *k_ref = k;
  *c_ref = c;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
}


----------------------------
pub fn XPutImage(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: GC,
        arg4: *mut XImage,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: std::os::raw::c_int,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_uint,
        arg10: std::os::raw::c_uint,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XGetSubImage(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_ulong,
        arg8: std::os::raw::c_int,
        arg9: *mut XImage,
        arg10: std::os::raw::c_int,
        arg11: std::os::raw::c_int,
    ) -> *mut XImage;
----------------------------
pub fn XSync(arg1: *mut Display, arg2: std::os::raw::c_int) -> std::os::raw::c_int;
----------------------------
pub fn XCheckWindowEvent(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_long,
        arg4: *mut XEvent,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XChangeProperty(
        arg1: *mut Display,
        arg2: Window,
        arg3: Atom,
        arg4: Atom,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_uchar,
        arg8: std::os::raw::c_int,
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


int main(int argc, char **argv)
{
  unsigned int argv_idx = 0;
  struct XSetWindowAttributes xswa;
  int i;
  int j;
  int k;
  char c;
  char *p1;
  unsigned int p1_idx = 0;
  char *p2;
  unsigned int p2_idx = 0;
  XEvent event;
  int buttonpressed = False;
  int unmapped = True;
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
  progname = strrchr(argv[0 + argv_idx], '/');
  if (progname)
  {
    progname += 1;
  }
  else
    progname = argv[0 + argv_idx];
  while ((--argc) > 0)
  {
    helper_main_1(&argc, &argv_idx, &dpyname_idx, &source_geom_mask, &dest_geom_mask, argv, xpos, ypos);
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
  if (DefaultDepthOfScreen(scr) != 8)
  {
    fprintf(stderr, "%s: can work only with 8 bits/pixel\n", progname);
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
  if (source_geom_mask & YNegative)
  {
    ypos += HeightOfScreen(scr);
  }
  xswa.event_mask = (ButtonPressMask | ButtonReleaseMask) | ButtonMotionMask;
  xswa.event_mask |= StructureNotifyMask;
  xswa.event_mask |= KeyPressMask | KeyReleaseMask;
  xswa.background_pixel = BlackPixelOfScreen(scr);
  win = XCreateWindow(dpy, RootWindowOfScreen(scr), xpos, ypos, width[1], height[1], 0, DefaultDepthOfScreen(scr), InputOutput, DefaultVisualOfScreen(scr), CWEventMask | CWBackPixel, &xswa);
  XChangeProperty(dpy, win, XA_WM_ICON_NAME, XA_STRING, 8, PropModeReplace, (unsigned char *) progname, strlen(progname));
  set_title = True;
  XMapWindow(dpy, win);
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
    helper_main_2(&i, &j, &k, &c, &p1_idx, &p2_idx, &buttonpressed, &unmapped, &scroll, p1, p2, event, title);
  }

}


/*** DEPENDENCIES:
Screen *scr
----------------------------
int width[2] = {0, 256}
----------------------------
Display *dpy
----------------------------
Window win
----------------------------
pub type XEvent = _XEvent;
----------------------------
pub struct XGCValues {
    pub function: std::os::raw::c_int,
    pub plane_mask: std::os::raw::c_ulong,
    pub foreground: std::os::raw::c_ulong,
    pub background: std::os::raw::c_ulong,
    pub line_width: std::os::raw::c_int,
    pub line_style: std::os::raw::c_int,
    pub cap_style: std::os::raw::c_int,
    pub join_style: std::os::raw::c_int,
    pub fill_style: std::os::raw::c_int,
    pub fill_rule: std::os::raw::c_int,
    pub arc_mode: std::os::raw::c_int,
    pub tile: Pixmap,
    pub stipple: Pixmap,
    pub ts_x_origin: std::os::raw::c_int,
    pub ts_y_origin: std::os::raw::c_int,
    pub font: Font,
    pub subwindow_mode: std::os::raw::c_int,
    pub graphics_exposures: std::os::raw::c_int,
    pub clip_x_origin: std::os::raw::c_int,
    pub clip_y_origin: std::os::raw::c_int,
    pub clip_mask: Pixmap,
    pub dash_offset: std::os::raw::c_int,
    pub dashes: std::os::raw::c_char,
}
----------------------------
Cursor crosshair
----------------------------
pub type Window = XID;
----------------------------
int xgrab
----------------------------
GC gc
----------------------------
char *progname
----------------------------
int set_title
----------------------------
int flipxy = False
----------------------------
void Usage(void)
{
  fprintf(stderr, "Usage: %s [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next '+' or '-' only change width scaling\nh: Next '+' or '-' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n", progname);
  exit(1);
}


----------------------------
void helper_main_2(int * const i_ref, int * const j_ref, int * const k_ref, char * const c_ref, unsigned int * const p1_idx_ref, unsigned int * const p2_idx_ref, int * const buttonpressed_ref, int * const unmapped_ref, int * const scroll_ref, char * const p1, char * const p2, XEvent event, char title[80])
{
  int i = *i_ref;
  int j = *j_ref;
  int k = *k_ref;
  char c = *c_ref;
  unsigned int p1_idx = *p1_idx_ref;
  unsigned int p2_idx = *p2_idx_ref;
  int buttonpressed = *buttonpressed_ref;
  int unmapped = *unmapped_ref;
  int scroll = *scroll_ref;
  while ((unmapped) ? ((XWindowEvent(dpy, win, (long) (-1), &event), 1)) : (XCheckWindowEvent(dpy, win, (long) (-1), &event)))
  {
    helper_helper_main_2_2(&buttonpressed, &unmapped, &scroll, event, title);
  }

  XGetSubImage(dpy, RootWindowOfScreen(scr), xgrab, ygrab, width[0], height[0], AllPlanes, ZPixmap, ximage[0], 0, 0);
  for (j = (flipxy) ? (width[0]) : (height[0]); (--j) >= 0;)
  {
    helper_helper_main_2_1(&i, &k, &c, &p1_idx, &p2_idx, p1, p2, j);
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
  if ((!buttonpressed) && (delay > 0))
  {
    usleep(delay);
  }
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
  *c_ref = c;
  *p1_idx_ref = p1_idx;
  *p2_idx_ref = p2_idx;
  *buttonpressed_ref = buttonpressed;
  *unmapped_ref = unmapped;
  *scroll_ref = scroll;
}


----------------------------
int magy = 2
----------------------------
int ygrab
----------------------------
Cursor when_button
----------------------------
int magx = 2
----------------------------
int height[2] = {0, 256}
----------------------------
void resize(int new_width, int new_height)
{
  if (created_images)
  {
    destroy_images();
  }
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
  if (width[0] > WidthOfScreen(scr))
  {
    width[0] = WidthOfScreen(scr);
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


----------------------------
void helper_main_1(int * const argc_ref, unsigned int * const argv_idx_ref, unsigned int * const dpyname_idx_ref, int * const source_geom_mask_ref, int * const dest_geom_mask_ref, char ** const argv, int xpos, int ypos)
{
  int argc = *argc_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int dpyname_idx = *dpyname_idx_ref;
  int source_geom_mask = *source_geom_mask_ref;
  int dest_geom_mask = *dest_geom_mask_ref;
  argv_idx += 1;
  if (argv[0 + argv_idx][0] == '=')
  {
    dest_geom_mask = XParseGeometry(argv[0 + argv_idx], &xpos, &ypos, &width[1], &height[1]);
    continue;
  }
  if (!strcmp(argv[0 + argv_idx], "-mag"))
  {
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
  Usage();
  *argc_ref = argc;
  *argv_idx_ref = argv_idx;
  *dpyname_idx_ref = dpyname_idx;
  *source_geom_mask_ref = source_geom_mask;
  *dest_geom_mask_ref = dest_geom_mask;
}


----------------------------
pub fn XCreateWindow(
        arg1: *mut Display,
        arg2: Window,
        arg3: std::os::raw::c_int,
        arg4: std::os::raw::c_int,
        arg5: std::os::raw::c_uint,
        arg6: std::os::raw::c_uint,
        arg7: std::os::raw::c_uint,
        arg8: std::os::raw::c_int,
        arg9: std::os::raw::c_uint,
        arg10: *mut Visual,
        arg11: std::os::raw::c_ulong,
        arg12: *mut XSetWindowAttributes,
    ) -> Window;
----------------------------
pub fn XCreateGC(
        arg1: *mut Display,
        arg2: Drawable,
        arg3: std::os::raw::c_ulong,
        arg4: *mut XGCValues,
    ) -> GC;
----------------------------
pub fn XMapWindow(arg1: *mut Display, arg2: Window) -> std::os::raw::c_int;
----------------------------
pub fn XDefineCursor(arg1: *mut Display, arg2: Window, arg3: Cursor) -> std::os::raw::c_int;
----------------------------
pub fn XChangeProperty(
        arg1: *mut Display,
        arg2: Window,
        arg3: Atom,
        arg4: Atom,
        arg5: std::os::raw::c_int,
        arg6: std::os::raw::c_int,
        arg7: *const std::os::raw::c_uchar,
        arg8: std::os::raw::c_int,
    ) -> std::os::raw::c_int;
----------------------------
pub fn XOpenDisplay(arg1: *const std::os::raw::c_char) -> *mut Display;
----------------------------
pub fn XCreateFontCursor(arg1: *mut Display, arg2: std::os::raw::c_uint) -> Cursor;
----------------------------
***/


