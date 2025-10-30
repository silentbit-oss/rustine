use crate::*;
use lazy_static::lazy_static;
use libc::FILE;
use libc::c_char;
use libc::fprintf;
use std::ffi::CStr;
use std::ffi::CString;
use std::io::Write;
use std::io;
use std::os::raw::c_char as std_c_char;
use std::process;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::Ordering;

pub fn show_usage() {
    let options = [
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
    ];

    println!();
    println!("grabc v{}", "1.0.2");
    println!("A program to identify a pixel color of an X Window");
    println!("by muquit@muquit.com https://www.muquit.com/");
    println!();
    println!("Usage: grabc [options]");
    println!("Where the options are:");
    
    for option in options.iter() {
        println!("{}", option);
        io::stdout().flush().unwrap();
    }
}
pub unsafe extern "C" fn log_debug(fmt: &std::ffi::CStr, args: *mut libc::c_void) {
    if G_DEBUG.load(Ordering::Relaxed) == 0 {
        return;
    }

    let stderr = libc_stderr();
    libc::fprintf(stderr, b"[Debug]: \0".as_ptr() as *const _);
    vfprintf(stderr, fmt.as_ptr(), args);
    libc::fprintf(stderr, b"\n\0".as_ptr() as *const _);
}

// Manually declare vfprintf since it wasn't found in libc
extern "C" {
    fn vfprintf(stream: *mut libc::FILE, format: *const libc::c_char, args: *mut libc::c_void) -> libc::c_int;
}

// Helper function to get stderr FILE pointer
fn libc_stderr() -> *mut libc::FILE {
    extern "C" {
        #[link_name = "stderr"]
        static stderr: *mut libc::FILE;
    }
    unsafe { stderr }
}

pub fn test_show_usage() {
    println!("Running test_show_usage...");
    show_usage();
    println!("show_usage() executed successfully.");
}
pub fn MXError(display: &Display, error: &XErrorEvent) -> i32 {
    let xerrcode = error.error_code;
    if (u32::from(xerrcode) == BadAlloc) || ((u32::from(xerrcode) == BadAccess) && (error.request_code == 88)) {
        return 0;
    } else {
        match error.request_code {
            X_GetGeometry => {
                if u32::from(error.error_code) == BadDrawable {
                    return 0;
                }
            }
            X_GetWindowAttributes => {
                if u32::from(error.error_code) == BadWindow {
                    return 0;
                }
            }
            X_QueryTree => {
                if u32::from(error.error_code) == BadWindow {
                    return 0;
                }
            }
            X_QueryColors => {
                if u32::from(error.error_code) == BadValue {
                    return 0;
                }
            }
            _ => {}
        }
    }
    1
}

pub fn test_log_debug() {
    println!("Running test_log_debug...");
    G_DEBUG.store(1, Ordering::SeqCst);
    unsafe {
        log_debug(
            std::ffi::CStr::from_bytes_with_nul(b"Testing %s: %d\0").unwrap(),
            &["log_debug".as_ptr() as *mut libc::c_void, &42 as *const i32 as *mut libc::c_void] as *const _ as *mut libc::c_void,
        );
    }
    G_DEBUG.store(0, Ordering::SeqCst);
    println!("log_debug() executed successfully.");
}
pub fn test_MXError() {
    println!("Running test_MXError...");
    let mut err = ffi::XErrorEvent {
        type_: 0,
        display: std::ptr::null_mut(),
        resourceid: 0,
        serial: 0,
        error_code: ffi::BadAlloc as u8,
        request_code: 0,
        minor_code: 0,
    };
    let rc = MXError(unsafe { &*std::ptr::null::<ffi::Display>() }, &err);
    assert_eq!(rc, 0);
    println!(" MXError() returned expected value.");
}
pub fn findSubWindow(
    display: &Display,
    top_window: Option<Window>,
    window_to_check: Option<Window>,
    x: &mut i32,
    y: &mut i32,
) -> Option<Window> {
    let mut newx = 0;
    let mut newy = 0;
    let mut window: Option<Window> = Option::None;

    // Check for null windows (equivalent to (Window)0 in C)
    if top_window.is_none() || window_to_check.is_none() {
        return Option::None;
    }

    let mut top_window = top_window.unwrap();
    let mut window_to_check = window_to_check.unwrap();
    window = Some(window_to_check.clone());

    // Convert Rust types to X11 types for FFI call
    let display_ptr = display as *const _ as *mut Display;
    let mut child_window: Window = Window::default();

    loop {
        let result = unsafe {
            XTranslateCoordinates(
                display_ptr,
                top_window,
                window_to_check,
                *x,
                *y,
                &mut newx,
                &mut newy,
                &mut child_window,
            )
        };

        if result == 0 || child_window == Window::default() {
            break;
        }

        if child_window != Window::default() {
            top_window = window_to_check;
            window_to_check = child_window;
            *x = newx;
            *y = newy;
            window = Some(window_to_check.clone());
        }
    }

    if child_window == Window::default() {
        window = Some(window_to_check);
    }

    *x = newx;
    *y = newy;
    window
}
pub fn upgrab_mouse(display: *mut Display) {
    let window_id = G_WINDOW_ID.lock().unwrap();
    if let Some(id) = *window_id {
        unsafe {
            XUngrabPointer(display, CurrentTime.into());
        }
    }
}
pub fn get_cross_cursor(display: *mut Display) -> Cursor {
    let mut cursor = G_CROSS_CURSOR.lock().unwrap();
    if cursor.is_none() {
        // Create a new Cursor instance using XCreateFontCursor
        // XC_tcross is 152 as defined in X11/cursorfont.h
        let new_cursor = unsafe { XCreateFontCursor(display, 152) };
        // Check for failure (new_cursor would be 0 in C)
        if new_cursor as u64 == 0 {
            eprintln!("ERROR: Failed to create Cross Cursor!");
            process::exit(1);
        }
        *cursor = Some(unsafe { std::mem::transmute(new_cursor) });
    }
    cursor.clone().unwrap()
}
pub fn test_get_cross_cursor_function() {
    println!("Running test_get_cross_cursor_function...");
    let fake_display = std::ptr::null_mut();
    let c = get_cross_cursor(fake_display);
    let cross_cursor = G_CROSS_CURSOR.lock().unwrap();
    assert!(cross_cursor.is_none() || &c == cross_cursor.as_ref().unwrap());
    println!("get_cross_cursor() tested.");
}
pub fn grab_mouse(display: &Display, root_window: Window) -> Window {
    // Check if g_window_id is already set (equivalent to checking for non-zero Window in C)
    if let Some(window_id) = *G_WINDOW_ID.lock().unwrap() {
        return window_id;
    }

    let mut event = XEvent::default();
    let target_cursor = get_cross_cursor(display as *const _ as *mut _);
    let status = unsafe {
        // Assuming XGrabPointer is implemented via FFI
        XGrabPointer(
            display as *const _ as *mut _,
            root_window,
            0,
            ButtonPressMask as u32,
            GrabModeSync,
            GrabModeAsync,
            root_window,
            target_cursor,
            CurrentTime,
        )
    };

    if status == GrabSuccess {
        unsafe {
            // Assuming XAllowEvents is implemented via FFI
            XAllowEvents(display as *const _ as *mut _, SyncPointer, CurrentTime);
            // Assuming XWindowEvent is implemented via FFI
            XWindowEvent(display as *const _ as *mut _, root_window, ButtonPressMask, &mut event);
        }
        let subwindow = unsafe { event.xbutton.subwindow };
        subwindow
    } else {
        root_window
    }
}

// FFI declarations (assuming these would be provided by an X11 crate)
extern "C" {
    fn XGrabPointer(
        display: *mut Display,
        grab_window: Window,
        owner_events: i32,
        event_mask: u32,
        pointer_mode: i32,
        keyboard_mode: i32,
        confine_to: Window,
        cursor: Cursor,
        time: u32,
    ) -> i32;

    fn XAllowEvents(display: *mut Display, event_mode: i32, time: u32);
    fn XWindowEvent(display: *mut Display, window: Window, event_mask: i32, event_return: *mut XEvent);
}

// Constants (assuming these would be provided by an X11 crate)
const ButtonPressMask: i32 = 0;
const GrabModeSync: i32 = 0;
const GrabModeAsync: i32 = 1;
const GrabSuccess: i32 = 0;
const SyncPointer: i32 = 0;
const CurrentTime: u32 = 0;
pub fn select_window(display: *mut Display, x: &mut i32, y: &mut i32) -> Option<Window> {
    // Check if we can return early with the global window ID
    {
        let g_window_id = G_WINDOW_ID.lock().unwrap();
        if g_window_id.is_some() && G_LOC_SPECIFIED.load(Ordering::Relaxed) != 0 {
            unsafe {
                log_debug(
                    &std::ffi::CStr::from_bytes_with_nul(b"Returning passing window: %lx\0").unwrap(),
                    &g_window_id.unwrap() as *const _ as *mut libc::c_void,
                );
            }
            *x = G_X.load(Ordering::Relaxed);
            *y = G_Y.load(Ordering::Relaxed);
            return *g_window_id;
        }
    }

    let mut target_window: Option<Window> = Option::None;
    let target_cursor = get_cross_cursor(display);
    let root_window = unsafe { XRootWindow(display, XDefaultScreen(display)) };

    let status = unsafe {
        XGrabPointer(
            display,
            root_window,
            0,
            ButtonPressMask as u32,
            GrabModeSync,
            GrabModeAsync,
            root_window,
            target_cursor,
            CurrentTime,
        )
    };

    if status == GrabSuccess {
        unsafe {
            XAllowEvents(display, SyncPointer, CurrentTime);
            let mut event = std::mem::zeroed();
            XWindowEvent(
                display,
                root_window,
                ButtonPressMask as i32,
                &mut event,
            );
            
            if event.type_ == ButtonPress as i32 {
                let subwindow = event.xbutton.subwindow;
                let mut event_x = event.xbutton.x;
                let mut event_y = event.xbutton.y;
                
                target_window = findSubWindow(
                    &*display,
                    Some(root_window),
                    Some(subwindow),
                    &mut event_x,
                    &mut event_y,
                );
                
                if target_window.is_none() {
                    eprintln!("ERROR: Failed to get target window, getting root window!");
                    target_window = Some(root_window);
                }
                
                if G_LOC_SPECIFIED.load(Ordering::Relaxed) == 0 {
                    XUngrabPointer(display, CurrentTime.into());
                }
                
                *x = event_x;
                *y = event_y;
            }
        }
    } else {
        eprintln!("ERROR: Failed to grab mouse pointer!");
        std::process::exit(1);
    }

    target_window
}
pub extern "C" fn get_window_color(
    display: *mut Display,
    color: *mut XColor,
) -> Option<Window> {
    extern "C" {
        fn XGetPixel(ximage: *mut XImage, x: i32, y: i32) -> u64;
        fn XDestroyImage(ximage: *mut XImage);
        fn XGetImage(
            display: *mut Display,
            window: Window,
            x: i32,
            y: i32,
            width: u32,
            height: u32,
            plane_mask: i64,
            format: i32,
        ) -> *mut XImage;
        fn XRootWindow(display: *mut Display, screen: i32) -> Window;
        fn XDefaultScreen(display: *mut Display) -> i32;
        fn XAllPlanes() -> i64;
    }

    const ZPixmap: i32 = 2;

    unsafe {
        let root_window = XRootWindow(display, XDefaultScreen(display));
        let mut x = 0;
        let mut y = 0;
        let mut target_window = match select_window(display, &mut x, &mut y) {
            Some(w) => w,
            Option::None => return Option::None,
        };
        log_debug(
            std::ffi::CStr::from_bytes_with_nul(b"  Root Window Id: 0x%08lx\0").unwrap(),
            &root_window as *const _ as *mut libc::c_void,
        );
        log_debug(
            std::ffi::CStr::from_bytes_with_nul(b"Target Window Id: 0x%08lx  X,Y: +%d+%d\0").unwrap(),
            &[target_window, x as u64, y as u64] as *const _ as *mut libc::c_void,
        );

        if target_window == 0 {
            return Option::None;
        }

        let mut ximage = XGetImage(
            display,
            target_window,
            x,
            y,
            1,
            1,
            XAllPlanes(),
            ZPixmap,
        );

        if ximage.is_null() {
            log_debug(
                std::ffi::CStr::from_bytes_with_nul(b"Could not get XImage from Window: 0x%08lx\0")
                    .unwrap(),
                &target_window as *const _ as *mut libc::c_void,
            );
            log_debug(
                std::ffi::CStr::from_bytes_with_nul(b"Trying to get XImage from root window: 0x%08lx\0")
                    .unwrap(),
                &root_window as *const _ as *mut libc::c_void,
            );
            ximage = XGetImage(display, root_window, x, y, 1, 1, XAllPlanes(), ZPixmap);
            if ximage.is_null() {
                log_debug(
                    std::ffi::CStr::from_bytes_with_nul(
                        b"Could not get XImage from target or root window\0",
                    )
                    .unwrap(),
                    std::ptr::null_mut(),
                );
                return Option::None;
            } else {
                log_debug(
                    std::ffi::CStr::from_bytes_with_nul(
                        b"OK successfully got XImage from root window\0",
                    )
                    .unwrap(),
                    std::ptr::null_mut(),
                );
                target_window = root_window;
            }
        }

        let pixel = XGetPixel(ximage, 0, 0);
        (*color).pixel = pixel;
        XDestroyImage(ximage);
        Some(target_window)
    }
}
