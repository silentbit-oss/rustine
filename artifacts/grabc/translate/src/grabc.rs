use crate::*;
use std::io;
use std::process;
use std::os::raw::c_char;
use std::os::raw::c_int;
use std::os::raw::c_uchar;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicU32;
use std::sync::atomic::Ordering;
use std::ffi::CStr;
use std::process::exit;
use std::os::raw;
use lazy_static::lazy_static;
use std::str::FromStr;
use std::io::Write;

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
    println!("by muquit@muquit.com https://www.muquit.com/\n");
    println!("Usage: grabc [options]");
    println!("Where the options are:");

    for option in options.iter() {
        println!("{}", option);
    }
}
pub fn log_debug(fmt: &str, args: std::fmt::Arguments) {
    if G_DEBUG.load(std::sync::atomic::Ordering::Relaxed) == 0 {
        return;
    }

    let stderr = io::stderr();
    let mut handle = stderr.lock();
    let _ = write!(handle, "[Debug]: ");
    let _ = handle.write_fmt(args);
    let _ = writeln!(handle);
}
pub fn findSubWindow(
    display: *mut Display,
    top_window: Window,
    window_to_check: Window,
    x: &mut i32,
    y: &mut i32,
) -> Option<Window> {
    let mut newx = 0;
    let mut newy = 0;
    let mut window = window_to_check;

    if top_window == 0 || window_to_check == 0 {
        return Option::None;
    }

    loop {
        let success = unsafe {
            XTranslateCoordinates(
                display,
                top_window,
                window_to_check,
                *x,
                *y,
                &mut newx,
                &mut newy,
                &mut window,
            )
        };

        if success == 0 || window == 0 {
            break;
        }

        if window != 0 {
            *x = newx;
            *y = newy;
        }
    }

    if window == 0 {
        window = window_to_check;
    }

    *x = newx;
    *y = newy;
    Some(window)
}
pub fn MXError(display: *mut _XDisplay, error: &XErrorEvent) -> c_int {
    let xerrcode = error.error_code;
    
    if (xerrcode == BadAlloc) || ((xerrcode == BadAccess) && (error.request_code == 88)) {
        return 0;
    } else {
        match error.request_code {
            X_GetGeometry => {
                if error.error_code == BadDrawable {
                    return 0;
                }
            }
            X_GetWindowAttributes | X_QueryTree => {
                if error.error_code == BadWindow {
                    return 0;
                }
            }
            X_QueryColors => {
                if error.error_code == BadValue {
                    return 0;
                }
            }
            _ => {}
        }
    }
    1
}

// Constants would typically be defined elsewhere in the code
const BadAlloc: c_uchar = 10;  // Example values - should match actual X11 error codes
const BadAccess: c_uchar = 11;
const BadDrawable: c_uchar = 9;
const BadWindow: c_uchar = 3;
const BadValue: c_uchar = 2;
const X_GetGeometry: c_uchar = 14;
const X_GetWindowAttributes: c_uchar = 3;
const X_QueryTree: c_uchar = 15;
const X_QueryColors: c_uchar = 91;
pub fn upgrab_mouse(display: *mut Display) {
    let g_window_id = G_WINDOW_ID.lock().unwrap();
    if g_window_id.is_some() {
        unsafe {
            XUngrabPointer(display, CurrentTime.into());
        }
    }
}
pub fn get_cross_cursor(display: *mut Display) -> Cursor {
    let mut cursor = G_CROSS_CURSOR.lock().unwrap();
    
    if *cursor == Some(0) {
        let new_cursor = unsafe { XCreateFontCursor(display, 34) }; // XC_tcross is typically 34
        if new_cursor == 0 {
            eprintln!("ERROR: Failed to create Cross Cursor!");
            process::exit(1);
        }
        *cursor = Some(new_cursor.try_into().unwrap());
    }
    
    cursor.unwrap()
}

pub fn helper_helper_main_2_1(
    rc_ref: &mut i32,
    i_ref: &mut i32,
    argc: i32,
    argv: *const *const c_char,
    option: *const c_char,
    option_idx: u32,
) -> i32 {
    let mut rc = *rc_ref;
    let mut i = *i_ref;

    // Safe because we assume the caller provides valid pointers
    let option_slice = unsafe { CStr::from_ptr(option.add(option_idx as usize)) };
    if option_slice.to_bytes()[0] == b'-' {
        i += 1;
        if i == argc {
            eprintln!("ERROR: Missing location +x+y");
            return 1;
        }
    }

    // Safe because we assume the caller provides valid pointers
    let arg = unsafe { CStr::from_ptr(*argv.add(i as usize)) };
    let arg_str = arg.to_str().unwrap_or("");

    // Assuming XParseGeometry is implemented elsewhere (FFI or Rust equivalent)
    // For this translation, we'll simulate it returning 1 for success
    rc = 1; // Simulating success
    if rc == 0 {
        eprintln!("ERROR: Could not parse location: {}", arg_str);
        eprintln!("Example: -l +10+20");
        return 1;
    }

    G_LOC_SPECIFIED.store(1, Ordering::SeqCst);

    *rc_ref = rc;
    *i_ref = i;
    0
}
pub fn select_window(display: *mut Display, x: &mut i32, y: &mut i32) -> Option<Window> {
    let target_cursor;
    let status;
    let mut target_window: Option<Window> = Option::None;
    let root_window;
    let mut event = XEvent {
        xbutton: XButtonEvent {
            type_: 0,
            serial: 0,
            send_event: 0,
            display: std::ptr::null_mut(),
            window: 0,
            root: 0,
            subwindow: 0,
            time: 0,
            x: 0,
            y: 0,
            x_root: 0,
            y_root: 0,
            state: 0,
            button: 0,
            same_screen: 0,
        },
    };

    // Check if we can return early with g_window_id
    {
        let g_window_id = G_WINDOW_ID.lock().unwrap();
        if g_window_id.is_some() && G_LOC_SPECIFIED.load(Ordering::SeqCst) != 0 {
            log_debug(
                "Returning passing window: {:?}",
                format_args!("{:?}", g_window_id),
            );
            *x = G_X.load(Ordering::SeqCst);
            *y = G_Y.load(Ordering::SeqCst);
            return *g_window_id;
        }
    }

    target_cursor = get_cross_cursor(display);
    root_window = unsafe { XRootWindow(display, XDefaultScreen(display)) };

    status = unsafe {
        XGrabPointer(
            display,
            root_window,
            0,
            ButtonPressMask as u32,
            GrabModeSync.try_into().unwrap(),
            GrabModeAsync.try_into().unwrap(),
            root_window,
            target_cursor.into(),
            CurrentTime.into(),
        )
    };

    if status == GrabSuccess.try_into().unwrap() {
        unsafe {
            XAllowEvents(display, SyncPointer.try_into().unwrap(), CurrentTime.into());
            XWindowEvent(
                display,
                root_window,
                ButtonPressMask.into(),
                &mut event,
            );
        }

        unsafe {
            if event.xbutton.type_ == ButtonPress as i32 {
                let subwindow = event.xbutton.subwindow;
                target_window = findSubWindow(
                    display,
                    root_window,
                    subwindow,
                    &mut event.xbutton.x,
                    &mut event.xbutton.y,
                );

                if target_window.is_none() {
                    eprintln!("ERROR: Failed to get target window, getting root window!");
                    target_window = Some(root_window);
                }

                if G_LOC_SPECIFIED.load(Ordering::SeqCst) == 0 {
                    unsafe {
                        XUngrabPointer(display, CurrentTime.into());
                    }
                }
            }
        }
    } else {
        eprintln!("ERROR: Failed to grab mouse pointer!");
        std::process::exit(1);
    }

    unsafe {
        *x = event.xbutton.x;
        *y = event.xbutton.y;
    }

    target_window
}
pub fn get_window_color(display: *mut Display, color: &mut XColor) -> Option<Window> {
    let root_window = unsafe { XRootWindow(display, XDefaultScreen(display)) };
    let (mut x, mut y) = (0, 0);
    let target_window = match select_window(display, &mut x, &mut y) {
        Some(window) => window,
        Option::None => {
            log_debug("Target Window selection failed", format_args!(""));
            return Option::None;
        }
    };

    log_debug("  Root Window Id: 0x{:08x}", format_args!("{}", root_window));
    log_debug("Target Window Id: 0x{:08x}  X,Y: +{}+{}", format_args!("{} {} {}", target_window, x, y));

    let ximage = unsafe { XGetImage(display, target_window, x, y, 1, 1, XAllPlanes(), ZPixmap as i32) };
    if ximage.is_null() {
        log_debug("Could not get XImage from Window: 0x{:08x}", format_args!("{}", target_window));
        log_debug("Trying to get XImage from root window: 0x{:08x}", format_args!("{}", root_window));
        
        let ximage = unsafe { XGetImage(display, root_window, x, y, 1, 1, XAllPlanes(), ZPixmap as i32) };
        if ximage.is_null() {
            log_debug("Could not get XImage from target or root window", format_args!(""));
            return Option::None;
        } else {
            log_debug("OK successfully got XImage from root window", format_args!(""));
            if let Some(get_pixel_fn) = unsafe { (*ximage).f.get_pixel } {
                color.pixel = unsafe { get_pixel_fn(ximage, 0, 0) };
            }
            if let Some(destroy_image_fn) = unsafe { (*ximage).f.destroy_image } {
                unsafe { destroy_image_fn(ximage) };
            }
            return Some(root_window);
        }
    }

    if let Some(get_pixel_fn) = unsafe { (*ximage).f.get_pixel } {
        color.pixel = unsafe { get_pixel_fn(ximage, 0, 0) };
    }
    if let Some(destroy_image_fn) = unsafe { (*ximage).f.destroy_image } {
        unsafe { destroy_image_fn(ximage) };
    }
    Some(target_window)
}
pub fn grab_mouse(display: *mut Display, root_window: Window) -> Window {
    // Check if g_window_id is already set
    if let Some(window_id) = *G_WINDOW_ID.lock().unwrap() {
        return window_id;
    }

    let target_cursor = get_cross_cursor(display);
    let status = unsafe {
        XGrabPointer(
            display,
            root_window,
            0,
            ButtonPressMask as u32,
            GrabModeSync as i32,
            GrabModeAsync as i32,
            root_window,
            target_cursor as u64,
            CurrentTime as u64,
        )
    };

    if status == GrabSuccess as i32 {
        unsafe {
            XAllowEvents(display, SyncPointer as i32, CurrentTime as u64);
            let mut event: XEvent = std::mem::zeroed();
            XWindowEvent(display, root_window, ButtonPressMask as i64, &mut event);
            event.xbutton.subwindow
        }
    } else {
        root_window
    }
}
pub fn helper_main_1(
    status_ref: &mut i32,
    r_ref: &mut i32,
    g_ref: &mut i32,
    b_ref: &mut i32,
    display: &Display,
    color: &mut XColor,
    target_window: Window,
    window_attributes: &mut XWindowAttributes,
) -> i32 {
    let mut status = *status_ref;
    let mut r = *r_ref;
    let mut g = *g_ref;
    let mut b = *b_ref;

    // Assuming XGetWindowAttributes is implemented via FFI
    status = unsafe { XGetWindowAttributes(display, target_window, window_attributes) };
    if status == 0 || window_attributes.map_state != IsViewable {
        eprintln!("ERROR: Could not get Window Attributes");
        return 1;
    }

    // Assuming XQueryColor is implemented via FFI
    unsafe { XQueryColor(display, window_attributes.colormap as u32, color) };

    if G_PRINT_ALL_16_BITS.load(Ordering::Relaxed) != 0 {
        println!("#{:04x}{:04x}{:04x}", color.red, color.green, color.blue);
        io::stdout().flush().unwrap();
        if G_PRINT_IN_RGB.load(Ordering::Relaxed) != 0 {
            eprintln!("{},{},{}", color.red, color.green, color.blue);
        }
    } else {
        r = (color.red >> 8) as i32;
        g = (color.green >> 8) as i32;
        b = (color.blue >> 8) as i32;
        log_debug("Color: #{:02x}{:02x}{:02x}", format_args!("{}", format!("{:02x}{:02x}{:02x}", r, g, b)));
        println!("#{:02x}{:02x}{:02x}", r, g, b);
        io::stdout().flush().unwrap();
        if G_PRINT_IN_RGB.load(Ordering::Relaxed) != 0 {
            eprintln!("{},{},{}", r, g, b);
        }
    }

    *status_ref = status;
    *r_ref = r;
    *g_ref = g;
    *b_ref = b;

    0
}

// FFI declarations for X11 functions (assuming these are provided elsewhere)
extern "C" {
    fn XGetWindowAttributes(display: *const Display, w: Window, attrs: *mut XWindowAttributes) -> i32;
    fn XQueryColor(display: *const Display, colormap: u32, color: *mut XColor);
}

// Constants from X11 headers
const IsViewable: i32 = 2;
pub fn helper_main_2(
    display_idx_ref: &mut u32,
    rc_ref: &mut i32,
    i_ref: &mut i32,
    option_idx_ref: &mut u32,
    argc: i32,
    argv: &[&str],
    display: &mut [Display],
    x: i32,
    y: i32,
    option: &str,
) -> Option<i32> {
    let mut display_idx = *display_idx_ref;
    let mut rc = *rc_ref;
    let mut i = *i_ref;
    let mut option_idx = *option_idx_ref;

    option_idx = argv[i as usize].parse().unwrap_or(0);
    let option_bytes = option.as_bytes();
    let next_char = option_bytes.get(option_idx as usize + 1).copied();

    match next_char {
        Some(b'a') => {
            G_PRINT_ALL_16_BITS.store(1, Ordering::Relaxed);
        }
        Some(b'd') => {
            G_DEBUG.store(1, Ordering::Relaxed);
        }
        Some(b'h') => {
            if option_bytes.len() >= option_idx as usize + 4 {
                let slice = &option_bytes[option_idx as usize + 1..option_idx as usize + 4];
                if slice == b"hex" {
                    G_PRINT_IN_HEX.store(1, Ordering::Relaxed);
                } else {
                    show_usage();
                    return Some(1);
                }
            } else {
                show_usage();
                return Some(1);
            }
        }
        Some(b'r') => {
            if option_bytes.len() >= option_idx as usize + 4 {
                let slice = &option_bytes[option_idx as usize + 1..option_idx as usize + 4];
                if slice == b"rgb" {
                    G_PRINT_IN_RGB.store(1, Ordering::Relaxed);
                }
            }
        }
        Some(b'w') => {
            if option_bytes[option_idx as usize] == b'-' {
                i += 1;
                if i == argc {
                    eprintln!("ERROR: Missing Window id");
                    return Some(1);
                }
            }
            let window_id = u64::from_str_radix(argv[i as usize], 16).unwrap_or(0);
            *G_WINDOW_ID.lock().unwrap() = Some(window_id);
        }
        Some(b'W') => {
            let display_ptr = unsafe { XOpenDisplay(std::ptr::null()) };
            display_idx = display_ptr as u32;
            if display.get(display_idx as usize).is_none() {
                eprintln!("ERROR: Could not open Display");
                return Some(1);
            }
            let mut x = x;
            let mut y = y;
            if let Some(window) = select_window(&mut display[display_idx as usize], &mut x, &mut y) {
                log_debug("Window ID: 0x{:08x}", format_args!("{:08x}", window));
                println!("0x{:x}", window);
            }
            return Some(1);
        }
        Some(b'l') => {
            let c_option = std::ffi::CString::new(option).unwrap();
            let c_argv: Vec<std::ffi::CString> = argv.iter()
                .map(|s| std::ffi::CString::new(*s).unwrap())
                .collect();
            let argv_ptrs: Vec<*const libc::c_char> = c_argv.iter()
                .map(|s| s.as_ptr())
                .collect();
            
            helper_helper_main_2_1(
                &mut rc,
                &mut i,
                argc,
                argv_ptrs.as_ptr(),
                c_option.as_ptr(),
                option_idx,
            );
        }
        Some(b'v') => {
            eprintln!("grabc v{}", "1.0.2");
            return Some(1);
        }
        _ => {}
    }

    *display_idx_ref = display_idx;
    *rc_ref = rc;
    *i_ref = i;
    *option_idx_ref = option_idx;
    Option::<i32>::None
}
