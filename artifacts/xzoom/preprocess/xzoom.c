# 0 "/app/subjects/xzoom/xzoom.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/xzoom/xzoom.c"
# 24 "/app/subjects/xzoom/xzoom.c"
# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 25 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 26 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 27 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/app/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 28 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/sys/signal.h" 1
# 29 "/app/subjects/xzoom/xzoom.c" 2

# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xlib.h" 1


# 1 "/app/pipeline/preprocess/fake_libc_include/X11/_X11_fake_defines.h" 1
# 4 "/app/pipeline/preprocess/fake_libc_include/X11/Xlib.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/_X11_fake_typedefs.h" 1



typedef char* XPointer;
typedef struct XErrorEvent XErrorEvent;
typedef struct XWindowAttributes XWindowAttributes;
typedef unsigned char KeyCode;
typedef unsigned int CARD32;
typedef unsigned long VisualID;
typedef unsigned long XIMResetState;
typedef unsigned long XID;
typedef XID Window;
typedef XID Colormap;
typedef XID Cursor;
typedef XID Drawable;
typedef void* XtPointer;
typedef XtPointer XtRequestId;
typedef struct Display Display;
typedef struct Screen Screen;
typedef struct Status Status;
typedef struct Visual Visual;
typedef struct Widget *Widget;
typedef struct XColor XColor;
typedef struct XClassHint XClassHint;
typedef struct XEvent XEvent;
typedef struct XFontStruct XFontStruct;
typedef struct XGCValues XGCValues;
typedef struct XKeyEvent XKeyEvent;
typedef struct XKeyPressedEvent XKeyPressedEvent;
typedef struct XPoint XPoint;
typedef struct XRectangle XRectangle;
typedef struct XSelectionRequestEvent XSelectionRequestEvent;
typedef struct XWindowChanges XWindowChanges;
typedef struct _XGC _XCG;
typedef struct _XGC *GC;
typedef struct _XIC *XIC;
typedef struct _XIM *XIM;
typedef struct _XImage XImage;
# 5 "/app/pipeline/preprocess/fake_libc_include/X11/Xlib.h" 2
# 31 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xatom.h" 1
# 32 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xutil.h" 1
# 33 "/app/subjects/xzoom/xzoom.c" 2







# 1 "/app/pipeline/preprocess/fake_libc_include/X11/cursorfont.h" 1
# 41 "/app/subjects/xzoom/xzoom.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/keysym.h" 1
# 42 "/app/subjects/xzoom/xzoom.c" 2






Display *dpy;
Screen *scr;
Window win;

GC gc;
# 62 "/app/subjects/xzoom/xzoom.c"
Cursor when_button;
Cursor crosshair;

char *progname;
int set_title;
# 78 "/app/subjects/xzoom/xzoom.c"
int xgrab, ygrab;

int magx = 2;
int magy = 2;

int flipxy = False;
int flipx = False;
int flipy = False;

int xzoom_flag = False;
int yzoom_flag = False;

int width[2] = { 0, 256 };
int height[2] = { 0, 256 };




XImage *ximage[2];

int created_images = False;



int delays[5] = { 200000, 100000, 50000, 10000, 0 };
int delay_index = 0;
int delay = 200000;

void
timeout_func(int signum) {
 set_title = True;
}






void
allocate_images(void) {
 int i;

 char *data;


 for(i = 0; i < 2; i++) {
# 166 "/app/subjects/xzoom/xzoom.c"
  data = malloc(width[i] * height[i]);

  ximage[i] = XCreateImage(dpy,
   DefaultVisualOfScreen(scr),
   DefaultDepthOfScreen(scr),
   ZPixmap, 0, data,
   width[i], height[i], 8, width[i]);

  if(ximage[i] == 0) {
   perror("XCreateImage");
   exit(-1);
  }


 }
 created_images = True;
}

void
destroy_images(void) {
 int i;

 for(i = 0; i < 2; i++) {




  free(ximage[i]->data);

  ximage[i]->data = 0;
  XDestroyImage(ximage[i]);
 }
}

void
Usage(void) {
 fprintf(stderr, "Usage: %s [ args ]\n"
  "Command line args:\n"
  "-display displayname\n"
  "-mag magnification [ magnification ]\n"
  "-geometry geometry\n"
  "-source geometry\n"
  "-x\n"
  "-y\n"
  "-xy\n\n"
  "Window commands:\n"
  "+: Zoom in\n"
  "-: Zoom out\n"
  "x: Flip right and left\n"
  "y: Flip top and bottom\n"
  "z: Rotate 90 degrees counter-clockwize\n"
  "w: Next '+' or '-' only change width scaling\n"
  "h: Next '+' or '-' only change height scaling\n"
  "d: Change delay between frames\n"
  "q: Quit\n"
  "Arrow keys: Scroll in direction of arrow\n"
  "Mouse button drag: Set top-left corner of viewed area\n",
  progname);
 exit(1);
}




void
resize(int new_width, int new_height) {

 if(created_images)
  destroy_images();



 if(flipxy) {
  height[0] = (new_width+magx-1) / magx;
  width[0] = (new_height+magy-1) / magy;
 }
 else {
  width[0] = (new_width+magx-1) / magx;
  height[0] = (new_height+magy-1) / magy;
 }

 if(width[0] > WidthOfScreen(scr))
  width[0] = WidthOfScreen(scr);

 if(height[0] > HeightOfScreen(scr))
  height[0] = HeightOfScreen(scr);



 if(flipxy) {
  width[1] = magx * height[0];
  height[1] = magy * width[0];
 }
 else {
  width[1] = magx * width[0];
  height[1] = magy * height[0];
 }

 allocate_images();


 if(width[1] > new_width)
  width[1] = new_width;
 if(height[1] > new_height)
  height[1] = new_height;
}

int
main(int argc, char **argv) {
 struct XSetWindowAttributes xswa;
 int i, j, k;
 char c;
 char *p1, *p2;
 XEvent event;
 int buttonpressed = False;
 int unmapped = True;
 int scroll = 1;
 char title[80];
 XGCValues gcv;
 char *dpyname = 0;
 int source_geom_mask = NoValue,
     dest_geom_mask = NoValue,
     copy_from_src_mask;
 int xpos = 0, ypos = 0;

 progname = strrchr(argv[0], '/');
 if(progname)
  ++progname;
 else
  progname = argv[0];


 while(--argc > 0) {
  ++argv;

  if(argv[0][0] == '=') {
   dest_geom_mask = XParseGeometry(argv[0],
    &xpos, &ypos,
    &width[1], &height[1]);
   continue;
  }

  if(!strcmp(argv[0], "-mag")) {
   ++argv; --argc;

   magx = argc > 0 ? atoi(argv[0]) : -1;

   if(magx <= 0)
    Usage();


   magy = argc > 1 ? atoi(argv[1]) : -1;

   if(magy <= 0)
    magy = magx;
   else {
    ++argv; --argc;
   }

   continue;
  }

  if(!strcmp(argv[0], "-x")) {
   flipx = True;
   continue;
  }

  if(!strcmp(argv[0], "-y")) {
   flipy = True;
   continue;
  }

  if(!strcmp(argv[0], "-z") ||
     !strcmp(argv[0], "-xy")) {
   flipxy = True;
   continue;
  }

  if(!strcmp(argv[0], "-source")) {
   ++argv; --argc;

   if(argc < 1)
    Usage();

   source_geom_mask = XParseGeometry(argv[0],
    &xgrab, &ygrab,
    &width[0], &height[0]);

   continue;
  }

  if(!strcmp(argv[0], "-dest") ||
     !strcmp(argv[0], "-geometry")) {
   ++argv; --argc;

   if(argc < 1)
    Usage();

   dest_geom_mask = XParseGeometry(argv[0],
    &xpos, &ypos,
    &width[1], &height[1]);

   continue;
  }

  if(!strcmp(argv[0], "-d") ||
     !strcmp(argv[0], "-display")) {

      ++argv; --argc;

   if(argc < 1)
    Usage();

      dpyname = argv[0];
   continue;
  }

  if(!strcmp(argv[0], "-delay")) {

      ++argv; --argc;

   if(argc < 1)
    Usage();

   if(sscanf(argv[0], "%u", &delay) != 1)
    Usage();

   delay *= 1000;

   continue;
  }

  Usage();
 }

 if (!(dpy = XOpenDisplay(dpyname))) {
  perror("Cannot open display");
  exit(-1);
 }




 copy_from_src_mask = NoValue;

 if(source_geom_mask & WidthValue) {
  if(flipxy) {
   height[1] = magy * width[0];
   copy_from_src_mask |= HeightValue;

  }
  else {
   width[1] = magx * width[0];
   copy_from_src_mask |= WidthValue;
  }
 }

 if(source_geom_mask & HeightValue) {
  if(flipxy) {
   width[1] = magx * height[0];
   copy_from_src_mask |= WidthValue;
  }
  else {
   height[1] = magy * height[0];
   copy_from_src_mask |= HeightValue;
  }
 }

 if(copy_from_src_mask & dest_geom_mask) {
  fprintf(stderr, "Conflicting dimensions between source and dest geometry\n");
  Usage();
 }

 scr = DefaultScreenOfDisplay(dpy);

 if(DefaultDepthOfScreen(scr) != 8) {
  fprintf(stderr, "%s: can work only with 8 bits/pixel\n", progname);
  exit(1);
 }

 if(source_geom_mask & XNegative)
  xgrab += WidthOfScreen(scr);

 if(source_geom_mask & YNegative)
  ygrab += HeightOfScreen(scr);

 if(dest_geom_mask & XNegative)
  xpos += WidthOfScreen(scr);

 if(source_geom_mask & YNegative)
  ypos += HeightOfScreen(scr);



 xswa.event_mask = ButtonPressMask|ButtonReleaseMask|ButtonMotionMask;
 xswa.event_mask |= StructureNotifyMask;
 xswa.event_mask |= KeyPressMask|KeyReleaseMask;
 xswa.background_pixel = BlackPixelOfScreen(scr);

 win = XCreateWindow(dpy, RootWindowOfScreen(scr),
     xpos, ypos, width[1], height[1], 0,
     DefaultDepthOfScreen(scr), InputOutput,
     DefaultVisualOfScreen(scr),
     CWEventMask | CWBackPixel, &xswa);

 XChangeProperty(dpy, win, XA_WM_ICON_NAME, XA_STRING, 8,
   PropModeReplace,
   (unsigned char *)progname, strlen(progname));







 set_title = True;

 XMapWindow(dpy, win);

 gcv.plane_mask = AllPlanes;
 gcv.subwindow_mode = IncludeInferiors;
 gcv.function = GXcopy;
 gcv.foreground = WhitePixelOfScreen(scr);
 gcv.background = BlackPixelOfScreen(scr);
 gc = XCreateGC(dpy, RootWindowOfScreen(scr),
  GCFunction|GCPlaneMask|GCSubwindowMode|GCForeground|GCBackground,
  &gcv);
# 508 "/app/subjects/xzoom/xzoom.c"
 resize(width[1], height[1]);
# 521 "/app/subjects/xzoom/xzoom.c"
 when_button = XCreateFontCursor(dpy, XC_ul_angle);

 crosshair = XCreateFontCursor(dpy, XC_crosshair);

 XDefineCursor(dpy, win, crosshair);

 for(;;) {

  while(unmapped?
   (XWindowEvent(dpy, win, (long)-1, &event), 1):
   XCheckWindowEvent(dpy, win, (long)-1, &event)) {

   switch(event.type) {
   case ConfigureNotify:
    if(event.xconfigure.width != width[1] ||
       event.xconfigure.height != height[1]) {

     resize(event.xconfigure.width, event.xconfigure.height);
    }
    break;
   case ReparentNotify:
    break;

   case MapNotify:
    unmapped = False;
    break;

   case UnmapNotify:
    unmapped = True;
    break;

   case KeyRelease:
    switch(XKeycodeToKeysym(dpy, event.xkey.keycode, 0)) {
    case XK_Control_L:
    case XK_Control_R:
     scroll = 1;
     break;
    }
    break;

   case KeyPress:
    switch(XKeycodeToKeysym(dpy, event.xkey.keycode, 0)) {
    case XK_Control_L:
    case XK_Control_R:
     scroll = 10;
     break;

    case '+':
    case '=':
     if(!yzoom_flag) ++magx;
     if(!xzoom_flag) ++magy;
     xzoom_flag = yzoom_flag = False;
     resize(width[1], height[1]);
     set_title = True;
     break;

    case '-':
     if(!yzoom_flag) --magx;
     if(!xzoom_flag) --magy;
     xzoom_flag = yzoom_flag = False;
     if(magx < 1) magx = 1;
     if(magy < 1) magy = 1;
     resize(width[1], height[1]);
     set_title = True;
     break;

    case XK_Left:
     if(flipxy)
      if(flipx)
       ygrab += scroll;
      else
       ygrab -= scroll;
     else
      if(flipx)
       xgrab += scroll;
      else
       xgrab -= scroll;
     break;

    case XK_Right:
     if(flipxy)
      if(flipx)
       ygrab -= scroll;
      else
       ygrab += scroll;
     else
      if(flipx)
       xgrab -= scroll;
      else
       xgrab += scroll;
     break;

    case XK_Up:
     if(flipxy)
      if(flipy)
       xgrab -= scroll;
      else
       xgrab += scroll;
     else
      if(flipy)
       ygrab += scroll;
      else
       ygrab -= scroll;
     break;

    case XK_Down:
     if(flipxy)
      if(flipy)
       xgrab += scroll;
      else
       xgrab -= scroll;
     else
      if(flipy)
       ygrab -= scroll;
      else
       ygrab += scroll;
     break;

    case 'x':
     flipx = !flipx;
     set_title = True;
     break;

    case 'y':
     flipy = !flipy;
     set_title = True;
     break;

    case 'z':
     if(flipx^flipy^flipxy) {
      flipx = !flipx;
      flipy = !flipy;
     }
     flipxy = !flipxy;
     resize(width[1], height[1]);
     set_title = True;
     break;

    case 'w':
     xzoom_flag = True;
     yzoom_flag = False;
     break;

    case 'h':
     yzoom_flag = True;
     xzoom_flag = False;
     break;

    case 'd':
     if(++delay_index >= 5)
      delay_index = 0;
     delay = delays[delay_index];
     sprintf(title, "delay = %d ms", delay/1000);
     XChangeProperty(dpy, win, XA_WM_NAME, XA_STRING, 8,
      PropModeReplace,
      (unsigned char *)title, strlen(title));
     signal(SIGALRM, timeout_func);
     alarm(2);
     break;

    case 'q':
     exit(0);
     break;
    }

    break;

   case ButtonPress:




    xgrab = event.xbutton.x_root;
    ygrab = event.xbutton.y_root;

    XDefineCursor(dpy, win, when_button);
    buttonpressed = True;
    break;

   case ButtonRelease:




    XDefineCursor(dpy, win, crosshair);
    buttonpressed = False;
    break;

   case MotionNotify:
    if(buttonpressed) {




     xgrab = event.xmotion.x_root;
     ygrab = event.xmotion.y_root;

    }
    break;
   }







   if(xgrab < 0)
    xgrab = 0;

   if(xgrab > WidthOfScreen(scr)-width[0])
    xgrab = WidthOfScreen(scr)-width[0];

   if(ygrab < 0)
    ygrab = 0;

   if(ygrab > HeightOfScreen(scr)-height[0])
    ygrab = HeightOfScreen(scr)-height[0];
  }





  XGetSubImage(dpy, RootWindowOfScreen(scr),
   xgrab, ygrab, width[0], height[0], AllPlanes,
   ZPixmap, ximage[0], 0, 0);
# 757 "/app/subjects/xzoom/xzoom.c"
  for(j = flipxy?width[0]:height[0]; --j >= 0; ) {

   p1 = &ximage[1]->data[ximage[1]->xoffset +
     j*magy*ximage[1]->bytes_per_line ];


   p2 = &ximage[0]->data[ximage[0]->xoffset +
     (flipy?(height[0]-1-j):j)*ximage[0]->bytes_per_line ];

   if(flipxy) {
    int p2step = ximage[0]->bytes_per_line;
    p2 = &ximage[0]->data[ximage[0]->xoffset + (flipy?j:(width[0]-1-j))];

    if(flipx) {
     p2 += p2step * (height[0]-1);
     p2step = -p2step;
    }

    for(i = height[0]; --i >= 0;) {
     c = *p1++ = *p2;
     p2 += p2step;
     for(k = magx; --k > 0; )
      *p1++ = c;
    }
   }
   else if(flipx) {
    p2 += width[0];
    for(i = width[0]; --i >= 0;) {
     c = *p1++ = *--p2;
     for(k = magx; --k > 0; )
      *p1++ = c;
    }
   }
   else {
    for(i = width[0]; --i >= 0;) {
     c = *p1++ = *p2++;
     for(k = magx; --k > 0; )
      *p1++ = c;
    }
   }


   p1 = &ximage[1]->data[ximage[1]->xoffset +
            j*magy*ximage[1]->bytes_per_line ];

   p2 = p1 + ximage[1]->bytes_per_line;

   for(k = magy; --k > 0; ) {



    memmove(p2, p1, width[1]);

    p2 += ximage[1]->bytes_per_line;
   }
  }




  XPutImage(dpy, win, gc, ximage[1], 0, 0, 0, 0, width[1], height[1]);

  if(set_title) {
   if(magx == magy && !flipx && !flipy && !flipxy)
    sprintf(title, "%s x%d", progname, magx);
   else
    sprintf(title, "%s X %s%d%s Y %s%d",
     progname,
      flipx?"-":"", magx,
      flipxy?" <=>":";",
      flipy?"-":"", magy);
   XChangeProperty(dpy, win, XA_WM_NAME, XA_STRING, 8,
    PropModeReplace,
    (unsigned char *)title, strlen(title));
   set_title = False;
  }
# 846 "/app/subjects/xzoom/xzoom.c"
  XSync(dpy, 0);
# 858 "/app/subjects/xzoom/xzoom.c"
  if(!buttonpressed && delay > 0)
   usleep(delay);




 }
}
