# 0 "/app/subjects/grabc/grabc.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/grabc/grabc.c"
# 28 "/app/subjects/grabc/grabc.c"
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
# 29 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 31 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/assert.h" 1
# 32 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 33 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/string.h" 1
# 34 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 35 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/math.h" 1
# 36 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/signal.h" 1
# 37 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/time.h" 1
# 38 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/errno.h" 1
# 39 "/app/subjects/grabc/grabc.c" 2

# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xos.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/X11/Xos.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/app/pipeline/preprocess/fake_libc_include/X11/Xos.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/_X11_fake_defines.h" 1
# 4 "/app/pipeline/preprocess/fake_libc_include/X11/Xos.h" 2
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
# 5 "/app/pipeline/preprocess/fake_libc_include/X11/Xos.h" 2
# 41 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xlib.h" 1
# 42 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xutil.h" 1
# 43 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xresource.h" 1
# 44 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xproto.h" 1
# 45 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/Xatom.h" 1
# 46 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/cursorfont.h" 1
# 47 "/app/subjects/grabc/grabc.c" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/X11/keysym.h" 1
# 48 "/app/subjects/grabc/grabc.c" 2
# 59 "/app/subjects/grabc/grabc.c"
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
static Cursor g_cross_cursor=(Cursor) 0;


static Window select_window (Display *,int *x,int *y);

static Window findSubWindow(Display *display,Window top_winodw,
    Window window_to_check,int *x,int *y);

static Window get_window_color(Display *display,XColor *color);
static int MXError(Display *display,XErrorEvent *error);

static void show_usage(void)
{
    char
        **p;

    static char *options[]=
    {
" -v      - show version info",
" -h      - show this usage",
" -hex    - print pixel value as Hex on stdout",
" -rgb    - print pixel value as RGB on stderr",
" -W      - print the Window id at mouse click",
" -w id   - window id in hex, use -l +x+y",
" -l +x+y - pixel co-ordinate. requires window id",
" -d      - show debug messages",
" -a      - Print all 16 bits RGB components of color",
"           Default is high order 8 bits of components",
"Example:",
"* Print pixel color in hex on stdout:",
"   $ grabc",
"* Show usage:",
"   $ grabc -h",
"* Print Window Id (Note the upper case W):",
"   $ grabc -W",
"* Print pixel color of Window iwith id 0x13234 at location 10,20",
"   $ grabc -w 0x13234 -l +10+20",
(char *) 0

    };

    (void) printf("\n");
    (void) printf("grabc v%s\n","1.0.2");
    (void) printf("A program to identify a pixel color of an X Window\n");
    (void) printf("by muquit@muquit.com https://www.muquit.com/\n\n");
    (void) printf("Usage: grabc [options]\n");
    (void) printf("Where the options are:\n");
    for (p=options; *p != 0; p++)
    {
        (void) fprintf(stdout,"%s\n",*p);
        (void) fflush(stdout);
    }
}


static void log_debug(const char *fmt,...)
{
    va_list
        args;
    if (!g_debug)
    {
        return;
    }
    __builtin_va_start((args));
    (void) fprintf(stderr,"[Debug]: ");
    vfprintf(stderr,fmt,args);
    (void) fprintf(stderr,"\n");
    ;
}

static Cursor get_cross_cursor(Display *display)
{
    if (g_cross_cursor == (Cursor) 0)
    {
        g_cross_cursor=XCreateFontCursor(display,XC_tcross);
        if (g_cross_cursor == (Cursor) 0)
        {
            (void) fprintf (stderr,"ERROR: Failed to create Cross Cursor!\n");
            exit(1);
        }
    }
    return g_cross_cursor;
}
static Window grab_mouse(Display *display,Window root_window)
{
    int
        status;

    Window
        subwindow;

    XEvent
        event;

    Cursor
        target_cursor;


    if (g_window_id != (Window) 0)
    {
        return g_window_id;
    }

    target_cursor = get_cross_cursor(display);
    status=XGrabPointer(display,root_window,0,
    (unsigned int) ButtonPressMask,GrabModeSync,
    GrabModeAsync,root_window,target_cursor,CurrentTime);
    if (status == GrabSuccess)
    {
        XAllowEvents(display,SyncPointer,CurrentTime);
        XWindowEvent(display,root_window,ButtonPressMask,&event);
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
    if (g_window_id != (Window) 0)
    {
        XUngrabPointer(display,CurrentTime);
    }
}
# 207 "/app/subjects/grabc/grabc.c"
static Window select_window(Display *display,int *x,int *y)
{
    Cursor
        target_cursor;

    int
        status;

    Window
        target_window,
        root_window;

    XEvent
        event;





    if ((g_window_id != (Window) 0) && g_loc_specified)
    {
        log_debug("Returning passing window: %lx",g_window_id);
        (*x) = g_x;
        (*y) = g_y;
        return g_window_id;
    }
    target_window=(Window) 0;
    target_cursor = get_cross_cursor(display);
    root_window=XRootWindow(display,XDefaultScreen(display));


        status=XGrabPointer(display,root_window,0,
            (unsigned int) ButtonPressMask,GrabModeSync,
            GrabModeAsync,root_window,target_cursor,CurrentTime);
        if (status == GrabSuccess)
        {
            XAllowEvents(display,SyncPointer,CurrentTime);
            XWindowEvent(display,root_window,ButtonPressMask,&event);
            Window subwindow = event.xbutton.subwindow;

            if (event.type == ButtonPress)
            {
                target_window=findSubWindow(display,root_window,
                    subwindow,
                    &event.xbutton.x,
                    &event.xbutton.y );

                if (target_window == (Window) 0)
                {
                    (void) fprintf (stderr,
                        "ERROR: Failed to get target window, getting root window!\n");
                    target_window=root_window;
                }
                if (!g_loc_specified)
                {
                    XUngrabPointer(display,CurrentTime);
                }
            }

        }
        else
        {
            (void) fprintf (stderr,"ERROR: Failed to grab mouse pointer!\n");
            exit(1);
        }


        (*x)=event.xbutton.x;
        (*y)=event.xbutton.y;

    return (target_window);
}


static Window findSubWindow(Display *display,Window top_window,
    Window window_to_check,int *x,int *y)
{
    int
        newx,
        newy;

    Window
        window;

    if (top_window == (Window) 0)
        return ((Window) 0);

    if (window_to_check == (Window) 0)
        return ((Window) 0);


    window=window_to_check;

    while ((XTranslateCoordinates(display,top_window,window_to_check,
        *x,*y,&newx,&newy,&window) != 0) &&
           (window != (Window) 0))
    {
        if (window != (Window) 0)
        {
            top_window=window_to_check;
            window_to_check=window;
            (*x)=newx;
            (*y)=newy;
        }
    }

    if (window == (Window) 0)
        window=window_to_check;


    (*x)=newx;
    (*y)=newy;

    return (window);
}
# 333 "/app/subjects/grabc/grabc.c"
static Window get_window_color(Display *display,XColor *color)
{
    Window
        root_window,
        target_window;

    XImage
        *ximage;

    int
        x,
        y;

    Status
        status;

    root_window=XRootWindow(display,XDefaultScreen(display));
    target_window=select_window(display,&x,&y);

    log_debug("  Root Window Id: 0x%08lx",root_window);
    log_debug("Target Window Id: 0x%08lx  X,Y: +%d+%d",target_window,x,y);

    if (target_window == (Window) 0)
        return (Window) 0;

    ximage=XGetImage(display,target_window,x,y,1,1,AllPlanes,ZPixmap);
    if (ximage == (XImage *) 0)
    {

        log_debug("Could not get XImage from Window: 0x%08lx",target_window);
        log_debug("Trying to get XImage from root window: 0x%08lx",root_window);
        ximage=XGetImage(display,root_window,x,y,1,1,AllPlanes,ZPixmap);
        if (ximage == (XImage *) 0)
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

    color->pixel=XGetPixel(ximage,0,0);
    XDestroyImage(ximage);

    return (target_window);
}



static int MXError (Display *display, XErrorEvent *error)
{
    int
        xerrcode;

    xerrcode = error->error_code;

    if (xerrcode == BadAlloc ||
        (xerrcode == BadAccess && error->request_code==88))
    {
        return (0);
    }
    else
    {
        switch (error->request_code)
        {
            case X_GetGeometry:
            {
                if (error->error_code == BadDrawable)
                    return (0);
                break;
            }

            case X_GetWindowAttributes:
            case X_QueryTree:
            {
                if (error->error_code == BadWindow)
                    return (0);
                break;
            }

            case X_QueryColors:
            {
                if (error->error_code == BadValue)
                    return(0);
                break;
            }
        }
    }
    return (1);
}

int main(int argc,char **argv)
{
    Display
        *display;

    int
        x,
        y,
        status;

    XColor
        color;

    int
        rc,
        i,
        r,
        g,
        b;

    Window
        window_id,
        target_window;

    XWindowAttributes
        window_attributes;

    char
        *option;

    for (i=1; i < argc; i++)
    {
        option = argv[i];
        switch(*(option+1))
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
                if (strncmp("hex",option+1,3) == 0)
                {
                    g_print_in_hex = 1;
                }
                else
                {
                    show_usage();
                    return(1);
                }
                break;
            }

            case 'r':
            {
                if (strncmp("rgb",option+1,3) == 0)
                {
                    g_print_in_rgb = 1;
                }
                break;
            }

            case 'w':
            {
                if (*option == '-')
                {
                    i++;
                    if (i == argc)
                    {
                        (void) fprintf(stderr,"ERROR: Missing Window id\n");
                        return(1);
                    }
                }
                g_window_id = (Window) strtol(argv[i],0, 16);
                break;
            }
            case 'W':
            {
                display=XOpenDisplay((char *) 0);
                if (display == 0)
                {
                    (void) fprintf(stderr,"ERROR: Could not open Display\n");
                    return(1);
                }
                Window window = select_window(display, &x, &y);
                if (window != (Window) 0)
                {
                    log_debug("Window ID: 0x%08lx",window);
                    (void) fprintf(stdout,"0x%lx\n",window);
                }
                return(1);
                break;
            }

            case 'l':
            {
                if (*option == '-')
                {
                    i++;
                    if (i == argc)
                    {
                        (void) fprintf(stderr,"ERROR: Missing location +x+y\n");
                        return(1);
                    }
                }
                rc = XParseGeometry(argv[i], &g_x,&g_y,&g_width,&g_height);
                if (rc == 0)
                {
                    (void) fprintf(stderr,"ERROR: Could not parse location: %s\n",argv[i]);
                    (void) fprintf(stderr,"Example: -l +10+20\n");
                    return(1);
                }
                g_loc_specified = 1;

                break;
            }

            case 'v':
            {
                (void) fprintf(stderr,"grabc v%s\n","1.0.2");
                return(1);
                break;
            }

            default:
            {
                break;
            }
        }
    }

    if (g_loc_specified && (g_window_id == (Window) 0))
    {
        (void) fprintf(stderr,"ERROR: Please specify window id with -w in hex to use this option\n");
        (void) fprintf(stderr,"Use -W option to find the Window Id\n");
        return(1);
    }

    display=XOpenDisplay((char *) 0);
    XSetErrorHandler(MXError);

    if (display == (Display *) 0)
    {
        (void) fprintf (stderr,"ERROR: Failed to open DISPLAY!\n");
        exit(1);
    }

    target_window = get_window_color(display,&color);
    if (target_window != (Window) 0)
    {
        status = XGetWindowAttributes(display, target_window,
                &window_attributes);
        if (status == 0 || window_attributes.map_state != IsViewable)
        {
            (void) fprintf(stderr,"ERROR: Could not get Window Attributes\n");
            return(1);
        }
        XQueryColor(display, window_attributes.colormap, &color);
        if (g_print_all_16_bits)
        {
            (void) fprintf(stdout,"#%04x%04x%04x\n",
                (unsigned int)color.red,
                (unsigned int) color.green,
                (unsigned int) color.blue);
            (void) fflush(stdout);
            if (g_print_in_rgb)
            {
                (void) fprintf(stderr,"%d,%d,%d\n",
                    (unsigned int)color.red,
                    (unsigned int) color.green,
                    (unsigned int) color.blue);
            }

        }
        else
        {
            r=(color.red >> 8);
            g=(color.green >> 8);
            b=(color.blue >> 8);
            log_debug("Color: #%02x%02x%02x",r,g,b);
            (void) fprintf (stdout,"#%02x%02x%02x\n",r,g,b);
            (void) fflush(stdout);



            if (g_print_in_rgb)
            {
                (void) fprintf(stderr,"%d,%d,%d\n",r,g,b);
            }
        }
    }
    else
    {
        (void) fprintf (stderr,"ERROR: Failed to grab color!\n");
    }
    return (0);
}
