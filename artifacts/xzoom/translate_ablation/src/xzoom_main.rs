use translate::*;
use std::process;
use std::env;
use std::ffi::CStr;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::os::raw::c_char;
use std::cell::RefCell;
use crate::ffi::XEvent;
use crate::ffi::XGCValues;

pub fn main() {
    let mut xswa = XSetWindowAttributes::default();
    let mut i = 0;
    let mut j = 0;
    let mut k = 0;
    let mut c = 0u8;
    let mut p1: *mut u8 = std::ptr::null_mut();
    let mut p1_idx = 0;
    let mut p2: *mut u8 = std::ptr::null_mut();
    let mut p2_idx = 0;
    let mut event = XEvent::default();
    let mut buttonpressed = 0;
    let mut unmapped = 1;
    let mut scroll = 1;
    let mut title = [0u8; 80];
    let mut gcv = XGCValues::default();
    let mut dpyname: *mut *mut i8 = std::ptr::null_mut();
    let mut dpyname_idx: *mut i8 = std::ptr::null_mut();
    let mut source_geom_mask = 0;
    let mut dest_geom_mask = 0;
    let mut copy_from_src_mask = 0;
    let mut xpos = 0;
    let mut ypos = 0;

    // Set progname
    unsafe {
        let args: Vec<*mut c_char> = std::env::args()
            .map(|s| std::ffi::CString::new(s).unwrap().into_raw())
            .collect();
        let argv: *mut *mut c_char = args.as_ptr() as *mut *mut c_char;
        let mut progname = libc::strrchr(*argv, b'/' as i32);
        if !progname.is_null() {
            progname = progname.offset(1);
        } else {
            progname = *argv;
        }
        *PROGNAME.lock().unwrap() = Some(CStr::from_ptr(progname).to_string_lossy().into_owned());
    }

    // Process command line arguments
    let mut remaining_args = std::env::args().count() as i32 - 1;
    while remaining_args > 0 {
        helper_main_1(
            &mut remaining_args,
            &mut dpyname,
            &mut dpyname_idx,
            &mut source_geom_mask,
            &mut dest_geom_mask,
            &mut xpos,
            &mut ypos,
        );
    }

    // Open display
    unsafe {
        let display = XOpenDisplay(dpyname_idx as *const c_char);
        if display.is_null() {
            eprintln!("Cannot open display");
            std::process::exit(-1);
        }
        *dpy.lock().unwrap() = Some(Box::from_raw(display));
    }

    let flipxy = *FLIPXY.lock().unwrap();
    let mut width = WIDTH.lock().unwrap();
    let mut height = HEIGHT.lock().unwrap();

    unsafe {
        if source_geom_mask & (1 << 0) != 0 {  // WidthValue
            if flipxy {
                height[1] = MAGY * width[0];
                copy_from_src_mask |= 1 << 0;  // HeightValue
            } else {
                width[1] = MAGX * width[0];
                copy_from_src_mask |= 1 << 0;  // WidthValue
            }
        }

        if source_geom_mask & (1 << 1) != 0 {  // HeightValue
            if flipxy {
                width[1] = MAGX * height[0];
                copy_from_src_mask |= 1 << 0;  // WidthValue
            } else {
                height[1] = MAGY * height[0];
                copy_from_src_mask |= 1 << 1;  // HeightValue
            }
        }
    }

    if copy_from_src_mask & dest_geom_mask != 0 {
        eprintln!("Conflicting dimensions between source and dest geometry");
        Usage();
    }

    // Get default screen
    let scr = unsafe {
        let display = dpy.lock().unwrap();
        let raw_display = Box::into_raw(Box::new(display.as_ref().unwrap().as_ref().clone()));
        XDefaultScreenOfDisplay(raw_display)
    };
    unsafe {
        SCR.with(|s| *s.borrow_mut() = Some(Box::from_raw(scr as *mut _)));
    }

    if unsafe { XDefaultDepthOfScreen(scr) } != 8 {
        let progname = PROGNAME.lock().unwrap();
        eprintln!("{}: can work only with 8 bits/pixel", progname.as_deref().unwrap_or(""));
        std::process::exit(1);
    }

    // Adjust positions based on negative flags
    if source_geom_mask & (1 << 2) != 0 {  // XNegative
        *XGRAB.lock().unwrap() += unsafe { XWidthOfScreen(scr) };
    }
    if source_geom_mask & (1 << 3) != 0 {  // YNegative
        *YGRAB.lock().unwrap() += unsafe { XHeightOfScreen(scr) };
    }
    if dest_geom_mask & (1 << 2) != 0 {  // XNegative
        xpos += unsafe { XWidthOfScreen(scr) };
    }
    if source_geom_mask & (1 << 3) != 0 {  // YNegative
        ypos += unsafe { XHeightOfScreen(scr) };
    }

    // Create window
    xswa.event_mask = (1 << 2) | (1 << 3) | (1 << 8) | (1 << 17) | (1 << 0) | (1 << 1);  // Button masks and key masks
    xswa.background_pixel = unsafe { XBlackPixelOfScreen(scr) };

    let win = unsafe {
        XCreateWindow(
            Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _,
            XRootWindowOfScreen(scr),
            xpos,
            ypos,
            width[1] as u32,
            height[1] as u32,
            0,
            XDefaultDepthOfScreen(scr),
            1,  // InputOutput
            XDefaultVisualOfScreen(scr),
            (1 << 3) | (1 << 1),  // CWEventMask | CWBackPixel
            &mut xswa,
        )
    };
    *WIN.lock().unwrap() = Some(win as u32);

    // Set window properties
    unsafe {
        let progname = PROGNAME.lock().unwrap();
        XChangeProperty(
            Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _,
            win,
            37,  // XA_WM_ICON_NAME
            31,  // XA_STRING
            8,
            0,  // PropModeReplace
            progname.as_ref().unwrap().as_ptr() as *const u8,
            progname.as_ref().unwrap().len() as i32,
        );
    }
    unsafe { set_title = 1 };
    unsafe { XMapWindow(Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _, win) };

    // Create GC
    gcv.plane_mask = unsafe { XAllPlanes() };
    gcv.subwindow_mode = 0;  // IncludeInferiors
    gcv.function = 3;  // GXcopy
    gcv.foreground = unsafe { XWhitePixelOfScreen(scr) };
    gcv.background = unsafe { XBlackPixelOfScreen(scr) };
    let gc = unsafe {
        XCreateGC(
            Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _,
            XRootWindowOfScreen(scr),
            (1 << 1) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6),  // GC masks
            &mut gcv,
        )
    };
    *GC.lock().unwrap() = Gc::new();

    // Initialize other components
    resize(width[1], height[1]);
    let when_button = unsafe { XCreateFontCursor(Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _, 134) };  // XC_ul_angle
    *WHEN_BUTTON.lock().unwrap() = when_button as u32;
    let crosshair = unsafe { XCreateFontCursor(Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _, 34) };  // XC_crosshair
    *CROSSHAIR_CURSOR.lock().unwrap() = crosshair as u32;
    unsafe { XDefineCursor(Box::as_ref(dpy.lock().unwrap().as_ref().unwrap()) as *const _ as *mut _, win, crosshair) };

    // Main event loop
    loop {
        helper_main_2(
            &mut i,
            &mut j,
            &mut k,
            &mut c,
            &mut p1,
            &mut p1_idx,
            &mut p2,
            &mut p2_idx,
            &mut event,
            &mut buttonpressed,
            &mut unmapped,
            &mut scroll,
            &mut title,
        );
    }
}
