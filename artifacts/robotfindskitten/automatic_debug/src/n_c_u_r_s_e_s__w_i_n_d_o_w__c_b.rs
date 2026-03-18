use crate::*;use ncurses::WINDOW;

pub type NcursesWindowCb = Option<Box<dyn FnMut(*mut WINDOW, *mut std::ffi::c_void) -> i32>>;

