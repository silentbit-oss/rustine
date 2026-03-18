use crate::*;
use lazy_static::lazy_static;
use std::cell::RefCell;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::Ordering;


lazy_static! {
    pub static ref GC: std::sync::Mutex<Gc> = std::sync::Mutex::new(Gc::new());
}

pub struct Gc {
    // GC implementation fields would go here
}

impl Gc {
    pub fn new() -> Self {
        Gc {
            // Initialize GC fields
        }
    }
}

lazy_static! {
    pub static ref PROGNAME: std::sync::Mutex<Option<String>> = std::sync::Mutex::new(Option::<String>::None);
}

pub static mut set_title: i32 = 0;


lazy_static! {
    pub static ref XGRAB: std::sync::Mutex<i32> = std::sync::Mutex::new(0);
}


lazy_static! {
    pub static ref YGRAB: std::sync::Mutex<i32> = std::sync::Mutex::new(0);
}

pub static mut MAGX: i32 = 2;

pub static mut MAGY: i32 = 2;


lazy_static! {
    pub static ref FLIPXY: std::sync::Mutex<bool> = std::sync::Mutex::new(false);
}


lazy_static! {
    pub static ref FLIPX: std::sync::Mutex<bool> = std::sync::Mutex::new(false);
}


lazy_static! {
    pub static ref FLIPY: std::sync::Mutex<bool> = std::sync::Mutex::new(false);
}


lazy_static! {
    pub static ref XZOOM_FLAG: AtomicBool = AtomicBool::new(false);
}


lazy_static! {
    pub static ref YZOOM_FLAG: std::sync::Mutex<bool> = std::sync::Mutex::new(false);
}


lazy_static! {
    pub static ref WIDTH: std::sync::Mutex<[i32; 2]> = 
        std::sync::Mutex::new([0, 256]);
}


lazy_static! {
    pub static ref HEIGHT: std::sync::Mutex<[i32; 2]> = 
        std::sync::Mutex::new([0, 256]);
}

lazy_static! {
    pub static ref XIMAGE: Mutex<[Option<XImage>; 2]> = Mutex::new([
        Option::<XImage>::None, // 0
        Option::<XImage>::None  // 1
    ]);
}

// Assuming XImage is defined elsewhere. If not, you'd need to define it:
// #[repr(C)]
// pub struct XImage {
//     // fields...
// }


lazy_static! {
    pub static ref CREATED_IMAGES: std::sync::Mutex<bool> = std::sync::Mutex::new(false);
}


lazy_static! {
    pub static ref DELAYS: std::sync::Mutex<[i32; 5]> =
        std::sync::Mutex::new([
            200000,  // 0
            100000,  // 1
            50000,   // 2
            10000,   // 3
            0        // 4
        ]);
}


lazy_static! {
    pub static ref DELAY_INDEX: std::sync::Mutex<i32> = std::sync::Mutex::new(0);
}

pub const DELAY: i32 = 200000;


lazy_static! {
    pub static ref dpy: Mutex<Option<Box<Display>>> = Mutex::new(Option::None);
}

thread_local! {
    pub static SCR: RefCell<Option<Box<Screen>>> = RefCell::new(Option::None);
}

lazy_static! {
    pub static ref WIN: std::sync::Mutex<Option<Window>> = std::sync::Mutex::new(Option::None);
}


lazy_static! {
    pub static ref WHEN_BUTTON: std::sync::Mutex<Cursor> = std::sync::Mutex::new(0);
}


lazy_static! {
    pub static ref CROSSHAIR_CURSOR: std::sync::Mutex<Cursor> =
        std::sync::Mutex::new(0); // Initialized to 0, actual cursor ID would be set later
}

