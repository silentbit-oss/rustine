use translate::*;
use std::env;
use std::process;
use std::sync::atomic::Ordering;
use std::os::raw::c_int;

unsafe extern "C" fn shim_MXError(display: *mut _XDisplay, event: *mut XErrorEvent) -> c_int {
    MXError(display, &*event)
}

pub fn main() -> Result<(), i32> {
    let mut display_idx: u32 = 0;
    let mut display: *mut _XDisplay = std::ptr::null_mut();
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut status: i32 = 0;
    let mut color = XColor {
        pixel: 0,
        red: 0,
        green: 0,
        blue: 0,
        flags: 0,
        pad: 0,
    };
    let mut rc: i32 = 0;
    let mut i: i32 = 1;
    let mut r: i32 = 0;
    let mut g: i32 = 0;
    let mut b: i32 = 0;
    let mut window_attributes = XWindowAttributes {
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        border_width: 0,
        depth: 0,
        visual: std::ptr::null_mut(),
        root: 0,
        class: 0,
        bit_gravity: 0,
        win_gravity: 0,
        backing_store: 0,
        backing_planes: 0,
        backing_pixel: 0,
        save_under: 0,
        colormap: 0,
        map_installed: 0,
        map_state: 0,
        all_event_masks: 0,
        your_event_mask: 0,
        do_not_propagate_mask: 0,
        override_redirect: 0,
        screen: std::ptr::null_mut(),
    };
    let mut option_idx: u32 = 0;

    let args: Vec<String> = std::env::args().collect();
    let argv: Vec<&str> = args.iter().map(|s| s.as_str()).collect();
    let argc = argv.len() as i32;

    while i < argc {
        helper_main_2(
            &mut display_idx,
            &mut rc,
            &mut i,
            &mut option_idx,
            argc,
            &argv,
            &mut [],
            x,
            y,
            "",
        );
        i += 1;
    }

    if G_LOC_SPECIFIED.load(Ordering::SeqCst) != 0 && G_WINDOW_ID.lock().unwrap().is_none() {
        eprintln!("ERROR: Please specify window id with -w in hex to use this option");
        eprintln!("Use -W option to find the Window Id");
        return Err(1);
    }

    unsafe {
        display = XOpenDisplay(std::ptr::null());
        XSetErrorHandler(Some(shim_MXError));
    }

    if display.is_null() {
        eprintln!("ERROR: Failed to open DISPLAY!");
        std::process::exit(1);
    }

    let target_window = get_window_color(display, &mut color);

    match target_window {
        Some(window) => {
            helper_main_1(
                &mut status,
                &mut r,
                &mut g,
                &mut b,
                unsafe { &*display },
                &mut color,
                window,
                &mut window_attributes,
            );
        }
        Option::None => {
            eprintln!("ERROR: Failed to grab color!");
        }
    }

    Ok(())
}
