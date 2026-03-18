use crate::*;
use lazy_static::lazy_static;
use std::cell::Ref;
use std::ffi::CStr;
use std::ffi::CString;
use std::os::raw::c_int;
use std::process::exit;
use std::process;
use std::ptr::copy_nonoverlapping;
use std::str::FromStr;
use std::sync::Mutex;
use std::sync::atomic::Ordering;


pub fn timeout_func(signum: i32) {
    unsafe {
        set_title = 1;
    }
}
pub fn destroy_images() {
    let mut ximage = XIMAGE.lock().unwrap();
    for i in 0..2 {
        if let Some(image) = ximage[i].take() {
            unsafe {
                // Since data is Vec<u8>, we don't need to check for null or free it manually
                // The Vec will be dropped automatically when the XImage is destroyed
            }
            // Assuming XDestroyImage is declared elsewhere with extern "C"
            unsafe {
                extern "C" {
                    fn XDestroyImage(image: XImage);
                }
                XDestroyImage(image);
            }
        }
    }
}
pub fn Usage() {
    let binding = PROGNAME.lock().unwrap();
    let progname = binding.as_deref().unwrap_or("program");
    eprintln!("Usage: {} [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next '+' or '-' only change width scaling\nh: Next '+' or '-' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n", progname);
    process::exit(1);
}
pub fn allocate_images() {
    for i in 0..2 {
        let dpy_guard = dpy.lock().unwrap();
        let dpy_ptr = dpy_guard.as_ref().expect("Display not initialized");
        let dpy_raw_ptr = &**dpy_ptr as *const ffi::_XDisplay as *mut ffi::_XDisplay;
        let size = ((unsafe { ffi::XBitmapUnit(dpy_raw_ptr) } / 8) * WIDTH.lock().unwrap()[i]) * HEIGHT.lock().unwrap()[i];
        let data = unsafe { std::alloc::alloc(std::alloc::Layout::from_size_align(size as usize, 1).unwrap()) } as *mut i8;
        if data.is_null() {
            eprintln!("Failed to allocate data");
            exit(-1);
        }
        
        let scr_ptr = SCR.with(|s| {
            let borrowed = s.borrow();
            let screen_ref = borrowed.as_ref().expect("Screen not initialized");
            &**screen_ref as *const screen::Screen as *mut ffi::Screen
        });
        
        let mut ximage_guard = XIMAGE.lock().unwrap();
        ximage_guard[i] = unsafe {
            let image_ptr = ffi::XCreateImage(
                dpy_raw_ptr,
                ffi::XDefaultVisualOfScreen(scr_ptr),
                ffi::XDefaultDepthOfScreen(scr_ptr) as u32,
                2,
                0,
                data,
                WIDTH.lock().unwrap()[i] as u32,
                HEIGHT.lock().unwrap()[i] as u32,
                32,
                0,
            );
            if image_ptr.is_null() {
                Option::None
            } else {
                Some(*Box::from_raw(image_ptr as *mut __x_image::XImage))
            }
        };
        
        if ximage_guard[i].is_none() {
            eprintln!("XCreateImage");
            exit(-1);
        }
    }
    
    *CREATED_IMAGES.lock().unwrap() = true;
}
pub fn helper_helper_main_2_1(
    i_ptr: &mut i32,
    j_ptr: &mut i32,
    k_ptr: &mut i32,
    c_ptr: &mut u8,
    p1_ptr: &mut *mut u8,
    p1_idx_ptr: &mut usize,
    p2_ptr: &mut *mut u8,
    p2_idx_ptr: &mut usize,
) {
    let mut i = *i_ptr;
    let mut j = *j_ptr;
    let mut k = *k_ptr;
    let mut c = *c_ptr;
    let mut p1 = *p1_ptr;
    let mut p1_idx = *p1_idx_ptr;
    let mut p2 = *p2_ptr;
    let mut p2_idx = *p2_idx_ptr;

    let ximage = XIMAGE.lock().unwrap();
    let height = HEIGHT.lock().unwrap();
    let width = WIDTH.lock().unwrap();
    let flipxy = FLIPXY.lock().unwrap();
    let flipx = FLIPX.lock().unwrap();
    let flipy = FLIPY.lock().unwrap();
    let magx = unsafe { MAGX };
    let magy = unsafe { MAGY };

    if let (Some(ximage1), Some(ximage0)) = (&ximage[1], &ximage[0]) {
        p1_idx = (ximage1.xoffset + (j * magy) * ximage1.bytes_per_line) as usize;
        p2_idx = (ximage0.xoffset + if *flipy { (height[0] - 1 - j) } else { j } * ximage0.bytes_per_line) as usize;

        if *flipxy {
            let mut p2step = ximage0.bytes_per_line as isize;
            p2_idx = (ximage0.xoffset + if *flipy { j } else { width[0] - 1 - j }) as usize;
            
            if *flipx {
                p2_idx += (p2step * (height[0] - 1) as isize) as usize;
                p2step = -p2step;
            }

            i = height[0];
            while {
                i -= 1;
                i >= 0
            } {
                unsafe {
                    c = *p2.add(p2_idx);
                    *p1.add(p1_idx) = c;
                }
                p1_idx += 1;
                p2_idx = (p2_idx as isize + p2step) as usize;
                
                k = magx;
                while {
                    k -= 1;
                    k > 0
                } {
                    unsafe {
                        *p1.add(p1_idx) = c;
                    }
                    p1_idx += 1;
                }
            }
        } else if *flipx {
            p2_idx += width[0] as usize;
            
            i = width[0];
            while {
                i -= 1;
                i >= 0
            } {
                p2_idx -= 1;
                unsafe {
                    c = *p2.add(p2_idx);
                    *p1.add(p1_idx) = c;
                }
                p1_idx += 1;
                
                k = magx;
                while {
                    k -= 1;
                    k > 0
                } {
                    unsafe {
                        *p1.add(p1_idx) = c;
                    }
                    p1_idx += 1;
                }
            }
        } else {
            i = width[0];
            while {
                i -= 1;
                i >= 0
            } {
                unsafe {
                    c = *p2.add(p2_idx);
                    *p1.add(p1_idx) = c;
                }
                p2_idx += 1;
                p1_idx += 1;
                
                k = magx;
                while {
                    k -= 1;
                    k > 0
                } {
                    unsafe {
                        *p1.add(p1_idx) = c;
                    }
                    p1_idx += 1;
                }
            }
        }

        p1_idx = (ximage1.xoffset + (j * magy) * ximage1.bytes_per_line) as usize;
        let mut p2 = unsafe { p1.add(p1_idx + ximage1.bytes_per_line as usize) };
        
        k = magy;
        while {
            k -= 1;
            k > 0
        } {
            unsafe {
                copy_nonoverlapping(
                    p1.add(p1_idx),
                    p2,
                    width[1] as usize,
                );
            }
            p2 = unsafe { p2.add(ximage1.bytes_per_line as usize) };
        }
    }

    *i_ptr = i;
    *j_ptr = j;
    *k_ptr = k;
    *c_ptr = c;
    *p1_ptr = p1;
    *p1_idx_ptr = p1_idx;
    *p2_ptr = p2;
    *p2_idx_ptr = p2_idx;
}
pub fn resize(new_width: i32, new_height: i32) {
    // Check if images exist and destroy them if they do
    if *CREATED_IMAGES.lock().unwrap() {
        destroy_images();
    }

    // Calculate new dimensions based on flipxy state
    let flipxy = *FLIPXY.lock().unwrap();
    let (width0, height0) = if flipxy {
        unsafe {
            (
                ((new_height + MAGY) - 1) / MAGY,
                ((new_width + MAGX) - 1) / MAGX,
            )
        }
    } else {
        unsafe {
            (
                ((new_width + MAGX) - 1) / MAGX,
                ((new_height + MAGY) - 1) / MAGY,
            )
        }
    };

    // Clamp dimensions to screen size
    let scr_width = SCR.with(|s| {
        let borrow = s.borrow();
        borrow.as_ref().unwrap().width
    });
    let scr_height = SCR.with(|s| {
        let borrow = s.borrow();
        borrow.as_ref().unwrap().height
    });

    let mut width = WIDTH.lock().unwrap();
    let mut height = HEIGHT.lock().unwrap();
    
    width[0] = width0.min(scr_width);
    height[0] = height0.min(scr_height);

    // Calculate scaled dimensions
    if flipxy {
        unsafe {
            width[1] = MAGX * height[0];
            height[1] = MAGY * width[0];
        }
    } else {
        unsafe {
            width[1] = MAGX * width[0];
            height[1] = MAGY * height[0];
        }
    }

    // Allocate new images
    allocate_images();

    // Clamp final dimensions to requested size
    width[1] = width[1].min(new_width);
    height[1] = height[1].min(new_height);
}
pub fn helper_main_1(
    argc_ptr: &mut i32,
    argv_ptr: &mut *mut *mut i8,
    dpyname_idx_ptr: &mut *mut i8,
    source_geom_mask_ptr: &mut i32,
    dest_geom_mask_ptr: &mut i32,
    xpos_ptr: &mut i32,
    ypos_ptr: &mut i32,
) {
    let mut argc = *argc_ptr;
    let mut argv = *argv_ptr;
    let mut dpyname_idx = *dpyname_idx_ptr;
    let mut source_geom_mask = *source_geom_mask_ptr;
    let mut dest_geom_mask = *dest_geom_mask_ptr;
    let mut xpos = *xpos_ptr;
    let mut ypos = *ypos_ptr;

    unsafe {
        argv = argv.offset(1);
        
        if argv.is_null() || (*argv).is_null() {
            Usage();
        }

        let arg = CStr::from_ptr(*argv as *const i8).to_string_lossy();

        if arg.starts_with('=') {
            // Note: XParseGeometry would need FFI or replacement
            // For now, we'll just set the mask and continue
            dest_geom_mask = 1; // Placeholder for XParseGeometry result
            // Update width and height
            {
                let mut width = WIDTH.lock().unwrap();
                let mut height = HEIGHT.lock().unwrap();
                width[1] = 0; // Placeholder
                height[1] = 0; // Placeholder
            }
        } else if arg == "-mag" {
            argv = argv.offset(1);
            argc -= 1;
            
            if argc < 1 {
                Usage();
            }
            
            let mag_str = CStr::from_ptr(*argv as *const i8).to_string_lossy();
            let magx_val = i32::from_str(&mag_str).unwrap_or(-1);
            if magx_val <= 0 {
                Usage();
            }
            
            {
                let mut magx = MAGX;
                magx = magx_val;
            }
            
            if argc > 1 {
                let mag_str = CStr::from_ptr(*argv.offset(1) as *const i8).to_string_lossy();
                let magy_val = i32::from_str(&mag_str).unwrap_or(-1);
                if magy_val <= 0 {
                    {
                        let mut magy = MAGY;
                        magy = magx_val;
                    }
                } else {
                    {
                        let mut magy = MAGY;
                        magy = magy_val;
                    }
                    argv = argv.offset(1);
                    argc -= 1;
                }
            } else {
                {
                    let mut magy = MAGY;
                    magy = magx_val;
                }
            }
        } else if arg == "-x" {
            {
                let mut flipx = FLIPX.lock().unwrap();
                *flipx = true;
            }
        } else if arg == "-y" {
            {
                let mut flipy = FLIPY.lock().unwrap();
                *flipy = true;
            }
        } else if arg == "-z" || arg == "-xy" {
            {
                let mut flipxy = FLIPXY.lock().unwrap();
                *flipxy = true;
            }
        } else if arg == "-source" {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 {
                Usage();
            }
            // Placeholder for XParseGeometry
            source_geom_mask = 1;
            {
                let mut xgrab = XGRAB.lock().unwrap();
                let mut ygrab = YGRAB.lock().unwrap();
                let mut width = WIDTH.lock().unwrap();
                let mut height = HEIGHT.lock().unwrap();
                *xgrab = 0; // Placeholder
                *ygrab = 0; // Placeholder
                width[0] = 0; // Placeholder
                height[0] = 0; // Placeholder
            }
        } else if arg == "-dest" || arg == "-geometry" {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 {
                Usage();
            }
            // Placeholder for XParseGeometry
            dest_geom_mask = 1;
            {
                let mut width = WIDTH.lock().unwrap();
                let mut height = HEIGHT.lock().unwrap();
                width[1] = 0; // Placeholder
                height[1] = 0; // Placeholder
            }
        } else if arg == "-d" || arg == "-display" {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 {
                Usage();
            }
            dpyname_idx = *argv;
        } else if arg == "-delay" {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 {
                Usage();
            }
            let delay_str = CStr::from_ptr(*argv as *const i8).to_string_lossy();
            let delay_val = u32::from_str(&delay_str).unwrap_or_else(|_| {
                Usage();
                0
            });
            {
                let mut delay = DELAY;
                delay = (delay_val * 1000) as i32;
            }
        } else {
            Usage();
        }
    }

    *argc_ptr = argc;
    *argv_ptr = argv;
    *dpyname_idx_ptr = dpyname_idx;
    *source_geom_mask_ptr = source_geom_mask;
    *dest_geom_mask_ptr = dest_geom_mask;
    *xpos_ptr = xpos;
    *ypos_ptr = ypos;
}
pub fn helper_helper_helper_main_2_2_1(title: &mut [u8; 80], event_ptr: &mut XEvent, scroll_ptr: &mut i32) {
    let event = *event_ptr;
    let mut scroll = *scroll_ptr;
    
    // Declare X11 constants
    extern "C" {
        pub static XK_Control_L: u64;
        pub static XK_Control_R: u64;
        pub static XK_Left: u64;
        pub static XK_Right: u64;
        pub static XK_Up: u64;
        pub static XK_Down: u64;
        pub static XA_WM_NAME: u64;
        pub static XA_STRING: u64;
    }
    
    let key_sym = unsafe { 
        XKeycodeToKeysym(
            Box::into_raw(dpy.lock().unwrap().as_ref().unwrap().clone()) as *mut ffi::_XDisplay,
            event.xkey.keycode.try_into().unwrap(), 
            0
        ) 
    };
    
    match key_sym {
        x if x == unsafe { XK_Control_L } || x == unsafe { XK_Control_R } => {
            scroll = 10;
        }
        
        x if x == '+' as u64 || x == '=' as u64 => {
            if !*YZOOM_FLAG.lock().unwrap() {
                unsafe { MAGX += 1; }
            }
            if !XZOOM_FLAG.load(Ordering::SeqCst) {
                unsafe { MAGY += 1; }
            }
            XZOOM_FLAG.store(false, Ordering::SeqCst);
            *YZOOM_FLAG.lock().unwrap() = false;
            resize(WIDTH.lock().unwrap()[1], HEIGHT.lock().unwrap()[1]);
            unsafe { set_title = 1; }
        }
        
        x if x == '-' as u64 => {
            if !*YZOOM_FLAG.lock().unwrap() {
                unsafe { MAGX -= 1; }
                if unsafe { MAGX } < 1 {
                    unsafe { MAGX = 1; }
                }
            }
            if !XZOOM_FLAG.load(Ordering::SeqCst) {
                unsafe { MAGY -= 1; }
                if unsafe { MAGY } < 1 {
                    unsafe { MAGY = 1; }
                }
            }
            XZOOM_FLAG.store(false, Ordering::SeqCst);
            *YZOOM_FLAG.lock().unwrap() = false;
            resize(WIDTH.lock().unwrap()[1], HEIGHT.lock().unwrap()[1]);
            unsafe { set_title = 1; }
        }
        
        x if x == unsafe { XK_Left } => {
            let flipxy = *FLIPXY.lock().unwrap();
            let flipx = *FLIPX.lock().unwrap();
            if flipxy {
                if flipx {
                    *YGRAB.lock().unwrap() += scroll;
                } else {
                    *YGRAB.lock().unwrap() -= scroll;
                }
            } else if flipx {
                *XGRAB.lock().unwrap() += scroll;
            } else {
                *XGRAB.lock().unwrap() -= scroll;
            }
        }
        
        x if x == unsafe { XK_Right } => {
            let flipxy = *FLIPXY.lock().unwrap();
            let flipx = *FLIPX.lock().unwrap();
            if flipxy {
                if flipx {
                    *YGRAB.lock().unwrap() -= scroll;
                } else {
                    *YGRAB.lock().unwrap() += scroll;
                }
            } else if flipx {
                *XGRAB.lock().unwrap() -= scroll;
            } else {
                *XGRAB.lock().unwrap() += scroll;
            }
        }
        
        x if x == unsafe { XK_Up } => {
            let flipxy = *FLIPXY.lock().unwrap();
            let flipy = *FLIPY.lock().unwrap();
            if flipxy {
                if flipy {
                    *XGRAB.lock().unwrap() -= scroll;
                } else {
                    *XGRAB.lock().unwrap() += scroll;
                }
            } else if flipy {
                *YGRAB.lock().unwrap() += scroll;
            } else {
                *YGRAB.lock().unwrap() -= scroll;
            }
        }
        
        x if x == unsafe { XK_Down } => {
            let flipxy = *FLIPXY.lock().unwrap();
            let flipy = *FLIPY.lock().unwrap();
            if flipxy {
                if flipy {
                    *XGRAB.lock().unwrap() += scroll;
                } else {
                    *XGRAB.lock().unwrap() -= scroll;
                }
            } else if flipy {
                *YGRAB.lock().unwrap() -= scroll;
            } else {
                *YGRAB.lock().unwrap() += scroll;
            }
        }
        
        x if x == 'x' as u64 => {
            *FLIPX.lock().unwrap() = !*FLIPX.lock().unwrap();
            unsafe { set_title = 1; }
        }
        
        x if x == 'y' as u64 => {
            *FLIPY.lock().unwrap() = !*FLIPY.lock().unwrap();
            unsafe { set_title = 1; }
        }
        
        x if x == 'z' as u64 => {
            let flipx = *FLIPX.lock().unwrap();
            let flipy = *FLIPY.lock().unwrap();
            let flipxy = *FLIPXY.lock().unwrap();
            if (flipx ^ flipy) ^ flipxy {
                *FLIPX.lock().unwrap() = !flipx;
                *FLIPY.lock().unwrap() = !flipy;
            }
            *FLIPXY.lock().unwrap() = !flipxy;
            resize(WIDTH.lock().unwrap()[1], HEIGHT.lock().unwrap()[1]);
            unsafe { set_title = 1; }
        }
        
        x if x == 'w' as u64 => {
            XZOOM_FLAG.store(true, Ordering::SeqCst);
            *YZOOM_FLAG.lock().unwrap() = false;
        }
        
        x if x == 'h' as u64 => {
            *YZOOM_FLAG.lock().unwrap() = true;
            XZOOM_FLAG.store(false, Ordering::SeqCst);
        }
        
        x if x == 'd' as u64 => {
            let mut delay_index = DELAY_INDEX.lock().unwrap();
            *delay_index += 1;
            if *delay_index >= 5 {
                *delay_index = 0;
            }
            let delay = DELAYS.lock().unwrap()[*delay_index as usize];
            
            let title_str = format!("delay = {} ms", delay / 1000);
            let c_title = CString::new(title_str).unwrap();
            unsafe {
                XChangeProperty(
                    Box::into_raw(dpy.lock().unwrap().as_ref().unwrap().clone()) as *mut ffi::_XDisplay,
                    WIN.lock().unwrap().unwrap().into(),
                    unsafe { XA_WM_NAME } as Atom,
                    unsafe { XA_STRING } as Atom,
                    8,
                    PropModeReplace.try_into().unwrap(),
                    c_title.as_ptr() as *const u8,
                    c_title.to_bytes().len() as i32
                );
            }
            unsafe {
                libc::signal(libc::SIGALRM, timeout_func as usize);
                libc::alarm(2);
            }
        }
        
        x if x == 'q' as u64 => {
            exit(0);
        }
        
        _ => {}
    }
    
    *event_ptr = event;
    *scroll_ptr = scroll;
}
pub fn helper_helper_main_2_2(
    title: &mut [u8; 80],
    event_ptr: &mut XEvent,
    buttonpressed_ptr: &mut i32,
    unmapped_ptr: &mut i32,
    scroll_ptr: &mut i32,
) {
    extern "C" {
        fn XK_Control_L() -> u64;
        fn XK_Control_R() -> u64;
    }

    let event = *event_ptr;
    let mut buttonpressed = *buttonpressed_ptr;
    let mut unmapped = *unmapped_ptr;
    let mut scroll = *scroll_ptr;

    unsafe {
        match event.type_ {
            x if x == ConfigureNotify as i32 => {
                let width = WIDTH.lock().unwrap();
                let height = HEIGHT.lock().unwrap();
                if (event.xconfigure.width != width[1]) || (event.xconfigure.height != height[1]) {
                    resize(event.xconfigure.width, event.xconfigure.height);
                }
            }
            x if x == ReparentNotify as i32 => {}
            x if x == MapNotify as i32 => {
                unmapped = 0; // False in Rust
            }
            x if x == UnmapNotify as i32 => {
                unmapped = 1; // True in Rust
            }
            x if x == KeyRelease as i32 => {
                let key_sym = XKeycodeToKeysym(
                    Box::into_raw(dpy.lock().unwrap().as_ref().unwrap().clone()) as *mut ffi::_XDisplay,
                    event.xkey.keycode.try_into().unwrap(),
                    0,
                );
                match key_sym {
                    x if x == XK_Control_L() || x == XK_Control_R() => {
                        scroll = 1;
                    }
                    _ => {}
                }
            }
            x if x == KeyPress as i32 => {
                helper_helper_helper_main_2_2_1(title, &mut event.clone(), &mut scroll);
            }
            x if x == ButtonPress as i32 => {
                *XGRAB.lock().unwrap() = event.xbutton.x_root;
                *YGRAB.lock().unwrap() = event.xbutton.y_root;
                let win = WIN.lock().unwrap();
                let when_button = WHEN_BUTTON.lock().unwrap();
                XDefineCursor(
                    Box::into_raw(dpy.lock().unwrap().as_ref().unwrap().clone()) as *mut ffi::_XDisplay,
                    win.unwrap().into(),
                    (*when_button).into(),
                );
                buttonpressed = 1; // True in Rust
            }
            x if x == ButtonRelease as i32 => {
                let win = WIN.lock().unwrap();
                let crosshair = CROSSHAIR_CURSOR.lock().unwrap();
                XDefineCursor(
                    Box::into_raw(dpy.lock().unwrap().as_ref().unwrap().clone()) as *mut ffi::_XDisplay,
                    win.unwrap().into(),
                    (*crosshair).into(),
                );
                buttonpressed = 0; // False in Rust
            }
            x if x == MotionNotify as i32 => {
                if buttonpressed != 0 {
                    *XGRAB.lock().unwrap() = event.xmotion.x_root;
                    *YGRAB.lock().unwrap() = event.xmotion.y_root;
                }
            }
            _ => {}
        }
    }

    // Clamp xgrab and ygrab values
    {
        let mut xgrab = XGRAB.lock().unwrap();
        let mut ygrab = YGRAB.lock().unwrap();
        let (scr_width, scr_height) = SCR.with(|s| {
            let borrowed = s.borrow();
            let screen = borrowed.as_ref().unwrap();
            (screen.width, screen.height)
        });

        let width = WIDTH.lock().unwrap();
        let height = HEIGHT.lock().unwrap();

        if *xgrab < 0 {
            *xgrab = 0;
        }
        if *xgrab > (scr_width - width[0]) {
            *xgrab = scr_width - width[0];
        }
        if *ygrab < 0 {
            *ygrab = 0;
        }
        if *ygrab > (scr_height - height[0]) {
            *ygrab = scr_height - height[0];
        }
    }

    *event_ptr = event;
    *buttonpressed_ptr = buttonpressed;
    *unmapped_ptr = unmapped;
    *scroll_ptr = scroll;
}
pub fn helper_main_2(
    i_ptr: &mut i32,
    j_ptr: &mut i32,
    k_ptr: &mut i32,
    c_ptr: &mut u8,
    p1_ptr: &mut *mut u8,
    p1_idx_ptr: &mut usize,
    p2_ptr: &mut *mut u8,
    p2_idx_ptr: &mut usize,
    event_ptr: &mut XEvent,
    buttonpressed_ptr: &mut i32,
    unmapped_ptr: &mut i32,
    scroll_ptr: &mut i32,
    title: &mut [u8; 80],
) {
    let mut i = *i_ptr;
    let mut j = *j_ptr;
    let mut k = *k_ptr;
    let mut c = *c_ptr;
    let mut p1 = *p1_ptr;
    let mut p1_idx = *p1_idx_ptr;
    let mut p2 = *p2_ptr;
    let mut p2_idx = *p2_idx_ptr;
    let mut event = *event_ptr;
    let mut buttonpressed = *buttonpressed_ptr;
    let mut unmapped = *unmapped_ptr;
    let mut scroll = *scroll_ptr;

    let dpy_lock = dpy.lock().unwrap();
    let win = WIN.lock().unwrap();
    let xgrab = XGRAB.lock().unwrap();
    let ygrab = YGRAB.lock().unwrap();
    let width = WIDTH.lock().unwrap();
    let height = HEIGHT.lock().unwrap();
    let ximage = XIMAGE.lock().unwrap();
    let flipxy = FLIPXY.lock().unwrap();
    let gc = GC.lock().unwrap();
    let current_set_title = unsafe { set_title };
    let magx = unsafe { MAGX };
    let magy = unsafe { MAGY };
    let flipx = FLIPX.lock().unwrap();
    let flipy = FLIPY.lock().unwrap();
    let progname = PROGNAME.lock().unwrap();
    let delay = DELAY;

    // Event processing loop
    while if unmapped != 0 {
        // XWindowEvent equivalent would go here
        true
    } else {
        // XCheckWindowEvent equivalent would go here
        false
    } {
        helper_helper_main_2_2(title, &mut event, &mut buttonpressed, &mut unmapped, &mut scroll);
    }

    // XGetSubImage equivalent would go here
    // XPutImage equivalent would go here

    if current_set_title != 0 {
        if (magx == magy) && !*flipx && !*flipy && !*flipxy {
            unsafe {
                libc::sprintf(
                    title.as_mut_ptr() as *mut libc::c_char,
                    b"%s x%d\0".as_ptr() as *const libc::c_char,
                    progname.as_ref().unwrap().as_ptr(),
                    magx,
                );
            }
        } else {
            unsafe {
                libc::sprintf(
                    title.as_mut_ptr() as *mut libc::c_char,
                    b"%s X %s%d%s Y %s%d\0".as_ptr() as *const libc::c_char,
                    progname.as_ref().unwrap().as_ptr(),
                    if *flipx { b"-\0".as_ptr() } else { b"\0".as_ptr() },
                    magx,
                    if *flipxy { b" <=>\0".as_ptr() } else { b";\0".as_ptr() },
                    if *flipy { b"-\0".as_ptr() } else { b"\0".as_ptr() },
                    magy,
                );
            }
        }
        // XChangeProperty equivalent would go here
        unsafe {
            set_title = 0;
        }
    }

    // XSync equivalent would go here

    if buttonpressed == 0 && delay > 0 {
        unsafe {
            libc::usleep(delay as libc::c_uint);
        }
    }

    *i_ptr = i;
    *j_ptr = j;
    *k_ptr = k;
    *c_ptr = c;
    *p1_ptr = p1;
    *p1_idx_ptr = p1_idx;
    *p2_ptr = p2;
    *p2_idx_ptr = p2_idx;
    *event_ptr = event;
    *buttonpressed_ptr = buttonpressed;
    *unmapped_ptr = unmapped;
    *scroll_ptr = scroll;
}
