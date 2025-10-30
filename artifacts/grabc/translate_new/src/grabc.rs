use translate_new::*;
use std::env;
use std::process;
use std::ffi::CStr;
use std::ffi::CString;
use lazy_static::lazy_static;
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
    let mut x = 0;
    let mut y = 0;
    let mut status = 0;
    let mut color = XColor::default();
    let mut rc = 0;
    let mut r = 0;
    let mut g = 0;
    let mut b = 0;
    let mut window_id = Window::default();
    let mut target_window = Window::default();
    let mut window_attributes = XWindowAttributes::default();
    let mut option_idx = 0;

    let mut i = 1;
    while i < argc {
        option_idx = i;
        let current_arg = argv[option_idx];
        let next_char = current_arg.chars().nth(1).unwrap_or('\0');

        match next_char {
            'a' => {
                G_PRINT_ALL_16_BITS.store(1, Ordering::SeqCst);
            }
            'd' => {
                G_DEBUG.store(1, Ordering::SeqCst);
            }
            'h' => {
                if current_arg.len() >= 4 && &current_arg[1..4] == "hex" {
                    G_PRINT_IN_HEX.store(true, Ordering::SeqCst);
                } else {
                    show_usage();
                    return Ok(());
                }
            }
            'r' => {
                if current_arg.len() >= 4 && &current_arg[1..4] == "rgb" {
                    G_PRINT_IN_RGB.store(true, Ordering::SeqCst);
                }
            }
            'w' => {
                if current_arg == "-" {
                    i += 1;
                    if i >= argc {
                        eprintln!("ERROR: Missing Window id");
                        return Ok(());
                    }
                }
                let window_id_str = argv[i];
                window_id = Window::from_str_radix(window_id_str, 16).unwrap_or(Window::default());
                *G_WINDOW_ID.lock().unwrap() = Some(window_id);
                i += 1;
                continue;
            }
            'W' => {
                display = unsafe { Some(XOpenDisplay(std::ptr::null())) };
                if display.is_none() {
                    eprintln!("ERROR: Could not open Display");
                    return Ok(());
                }
                let window = select_window(display.unwrap(), &mut x, &mut y);
                if let Some(win) = window {
                    let msg = CString::new(format!("Window ID: 0x{:08x}", win))?;
                    unsafe { log_debug(&msg, std::ptr::null_mut()); }
                    println!("0x{:x}", win);
                }
                return Ok(());
            }
            'l' => {
                if current_arg == "-" {
                    i += 1;
                    if i >= argc {
                        eprintln!("ERROR: Missing location +x+y");
                        return Ok(());
                    }
                }
                let geometry = argv[i];
                let parts: Vec<&str> = geometry.split('+').collect();
                if parts.len() != 3 {
                    eprintln!("ERROR: Could not parse location: {}", geometry);
                    eprintln!("Example: -l +10+20");
                    return Ok(());
                }
                G_X.store(parts[1].parse()?, Ordering::SeqCst);
                G_Y.store(parts[2].parse()?, Ordering::SeqCst);
                G_LOC_SPECIFIED.store(1, Ordering::SeqCst);
                i += 1;
                continue;
            }
            'v' => {
                eprintln!("grabc v{}", "1.0.2");
                return Ok(());
            }
            _ => {}
        }
        i += 1;
    }

    if G_LOC_SPECIFIED.load(Ordering::SeqCst) != 0 && G_WINDOW_ID.lock().unwrap().is_none() {
        eprintln!("ERROR: Please specify window id with -w in hex to use this option");
        eprintln!("Use -W option to find the Window Id");
        return Ok(());
    }

    display = unsafe { Some(XOpenDisplay(std::ptr::null())) };
    unsafe { XSetErrorHandler(Some(mx_error_wrapper)); }
    if display.is_none() {
        eprintln!("ERROR: Failed to open DISPLAY!");
        std::process::exit(1);
    }

    if let Some(win) = get_window_color(display.unwrap(), &mut color) {
        target_window = win;
        let mut raw_attrs = std::mem::MaybeUninit::<XWindowAttributes>::uninit();
        status = unsafe { XGetWindowAttributes(display.unwrap(), target_window, raw_attrs.as_mut_ptr()) };
        if status == 0 {
            eprintln!("ERROR: Could not get Window Attributes");
            return Ok(());
        }
        let window_attributes = unsafe { raw_attrs.assume_init() };
        unsafe { XQueryColor(display.unwrap(), window_attributes.colormap, &mut color) };
        if G_PRINT_ALL_16_BITS.load(Ordering::SeqCst) != 0 {
            println!("#{:04x}{:04x}{:04x}", color.red, color.green, color.blue);
            std::io::stdout().flush()?;
            if G_PRINT_IN_RGB.load(Ordering::SeqCst) {
                eprintln!("{},{},{}", color.red, color.green, color.blue);
            }
        } else {
            r = (color.red >> 8) as u8;
            g = (color.green >> 8) as u8;
            b = (color.blue >> 8) as u8;
            let msg = CString::new(format!("Color: #{:02x}{:02x}{:02x}", r, g, b))?;
            unsafe { log_debug(&msg, std::ptr::null_mut()); }
            println!("#{:02x}{:02x}{:02x}", r, g, b);
            std::io::stdout().flush()?;
            if G_PRINT_IN_RGB.load(Ordering::SeqCst) {
                eprintln!("{},{},{}", r, g, b);
            }
        }
    } else {
        eprintln!("ERROR: Failed to grab color!");
    }

    Ok(())
}

unsafe extern "C" fn mx_error_wrapper(display: *mut Display, event: *mut XErrorEvent) -> i32 {
    MXError(&*display, &*event)
}
