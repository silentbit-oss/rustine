use translate_new::*;
use std::env;
use std::ffi::CStr;
use std::process::exit;
use std::str::FromStr;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::AtomicU32;
use std::sync::atomic::Ordering;
use std::sync::Mutex;
use std::io::Write;
pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    let argc = args.len();
    let argv: Vec<&str> = args.iter().map(|s| s.as_str()).collect();

    let mut display: Option<*mut Display> = Option::None;
    let mut display_idx = 0;
    let mut x = 0;
    let mut y = 0;
    let mut status = 0;
    let mut color: crate::XColor = unsafe { std::mem::zeroed() };
    let mut rc = 0;
    let mut r = 0;
    let mut g = 0;
    let mut b = 0;
    let mut target_window: Option<Window> = Option::None;
    let mut window_attributes: crate::XWindowAttributes = unsafe { std::mem::zeroed() };
    let option = "";
    let mut option_idx = 0;

    // Wrapper to convert MXError to X11-compatible signature
    unsafe extern "C" fn mx_error_wrapper(
        display: *mut crate::Display,
        error_event: *mut crate::XErrorEvent,
    ) -> i32 {
        crate::MXError(&*display, &*error_event)
    }

    let mut i = 1;
    while i < argc {
        option_idx = i;
        let opt = argv[option_idx];
        match opt.chars().nth(1) {
            Some('a') => {
                G_PRINT_ALL_16_BITS.store(1, Ordering::Relaxed);
            }
            Some('d') => {
                G_DEBUG.store(1, Ordering::Relaxed);
            }
            Some('h') => {
                if opt.len() >= 4 && &opt[1..4] == "hex" {
                    G_PRINT_IN_HEX.store(true, Ordering::Relaxed);
                } else {
                    show_usage();
                    return Ok(());
                }
            }
            Some('r') => {
                if opt.len() >= 4 && &opt[1..4] == "rgb" {
                    G_PRINT_IN_RGB.store(true, Ordering::Relaxed);
                }
            }
            Some('w') => {
                if opt == "-w" {
                    i += 1;
                    if i == argc {
                        eprintln!("ERROR: Missing Window id");
                        return Ok(());
                    }
                }
                let window_id_str = argv[i];
                let window_id = u64::from_str_radix(window_id_str, 16).unwrap();
                *G_WINDOW_ID.lock().unwrap() = Some(Window::from(window_id));
            }
            Some('W') => {
                unsafe {
                    display = Some(XOpenDisplay(std::ptr::null()));
                }
                if display.is_none() {
                    eprintln!("ERROR: Could not open Display");
                    return Ok(());
                }
                let window = select_window(display.unwrap(), &mut x, &mut y);
                if window.is_some() {
                    let msg = format!("Window ID: 0x{:08x}", window.unwrap());
                    let c_msg = std::ffi::CString::new(msg).unwrap();
                    unsafe { log_debug(&c_msg, std::ptr::null_mut()) };
                    println!("0x{:x}", window.unwrap());
                }
                return Ok(());
            }
            Some('l') => {
                if opt == "-l" {
                    i += 1;
                    if i == argc {
                        eprintln!("ERROR: Missing location +x+y");
                        return Ok(());
                    }
                }
                let geometry = argv[i];
                G_X.store(10, Ordering::Relaxed);
                G_Y.store(20, Ordering::Relaxed);
                G_WIDTH.store(0, Ordering::Relaxed);
                G_HEIGHT.store(0, Ordering::Relaxed);
                G_LOC_SPECIFIED.store(1, Ordering::Relaxed);
            }
            Some('v') => {
                eprintln!("grabc v{}", "1.0.2");
                return Ok(());
            }
            _ => {}
        }
        i += 1;
    }

    if G_LOC_SPECIFIED.load(Ordering::Relaxed) != 0 && G_WINDOW_ID.lock().unwrap().is_none() {
        eprintln!("ERROR: Please specify window id with -w in hex to use this option");
        eprintln!("Use -W option to find the Window Id");
        return Ok(());
    }

    unsafe {
        display = Some(XOpenDisplay(std::ptr::null()));
        XSetErrorHandler(Some(mx_error_wrapper));
    }
    if display.is_none() {
        eprintln!("ERROR: Failed to open DISPLAY!");
        std::process::exit(1);
    }

    target_window = get_window_color(display.unwrap(), &mut color);
    if target_window.is_some() {
        unsafe {
            status = XGetWindowAttributes(
                display.unwrap(),
                *target_window.as_ref().unwrap(),
                &mut window_attributes as *mut _,
            );
        }
        const IsViewable: i32 = 2;
        if status == 0 || window_attributes.map_state != IsViewable {
            eprintln!("ERROR: Could not get Window Attributes");
            return Ok(());
        }
        
        unsafe {
            XQueryColor(
                display.unwrap(),
                window_attributes.colormap,
                &mut color as *mut _,
            );
        }
        
        if G_PRINT_ALL_16_BITS.load(Ordering::Relaxed) != 0 {
            println!(
                "#{:04x}{:04x}{:04x}",
                color.red, color.green, color.blue
            );
            std::io::stdout().flush().unwrap();
            if G_PRINT_IN_RGB.load(Ordering::Relaxed) {
                eprintln!("{},{},{}", color.red, color.green, color.blue);
            }
        } else {
            r = (color.red >> 8) as i32;
            g = (color.green >> 8) as i32;
            b = (color.blue >> 8) as i32;
            let msg = format!("Color: #{:02x}{:02x}{:02x}", r, g, b);
            let c_msg = std::ffi::CString::new(msg).unwrap();
            unsafe { log_debug(&c_msg, std::ptr::null_mut()) };
            println!("#{:02x}{:02x}{:02x}", r, g, b);
            std::io::stdout().flush().unwrap();
            if G_PRINT_IN_RGB.load(Ordering::Relaxed) {
                eprintln!("{},{},{}", r, g, b);
            }
        }
    } else {
        eprintln!("ERROR: Failed to grab color!");
    }
    Ok(())
}
