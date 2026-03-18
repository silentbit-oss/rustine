#![feature(core_intrinsics)]
#![register_tool(c2rust)]
#![feature( extern_types,  register_tool)]
#![feature(const_mut_refs, const_fn_fn_ptr_basics)]
#![feature(c_variadic)]









use std::ffi::CString;

use std::os::raw::c_int;

use std::ffi::CStr;
use std::process;

use std::slice;

extern "C" {
    pub type _XGC;
    pub type _XDisplay;
    pub type _XPrivate;
    pub type _XrmHashBucketRec;
    #[no_mangle]
    static mut stderr: *mut _IO_FILE;
    #[no_mangle]
    fn fprintf(_: *mut FILE, _: *const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn printf(_: *const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn sprintf(_: *mut std::os::raw::c_char, _: *const std::os::raw::c_char, _: ...)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn sscanf(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char, _: ...)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn perror(__s: *const std::os::raw::c_char);
    #[no_mangle]
    fn memcpy(_: *mut std::os::raw::c_void, _: *const std::os::raw::c_void, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn strcmp(_: *const std::os::raw::c_char, _: *const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn strrchr(_: *const std::os::raw::c_char, _: std::os::raw::c_int) -> *mut std::os::raw::c_char;
    #[no_mangle]
    fn strlen(_: *const std::os::raw::c_char) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn atoi(__nptr: *const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn malloc(_: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn free(__ptr: *mut std::os::raw::c_void);
    #[no_mangle]
    fn atexit(__func: Option<unsafe extern "C" fn() -> ()>) -> std::os::raw::c_int;
    #[no_mangle]
    fn exit(_: std::os::raw::c_int) -> !;
    #[no_mangle]
    fn signal(__sig: std::os::raw::c_int, __handler: __sighandler_t)
     -> __sighandler_t;
    #[no_mangle]
    fn XCreateImage(_: *mut Display, _: *mut Visual, _: std::os::raw::c_uint,
                    _: std::os::raw::c_int, _: std::os::raw::c_int, _: *mut std::os::raw::c_char,
                    _: std::os::raw::c_uint, _: std::os::raw::c_uint, _: std::os::raw::c_int,
                    _: std::os::raw::c_int) -> *mut XImage;
    #[no_mangle]
    fn XGetSubImage(_: *mut Display, _: Drawable, _: std::os::raw::c_int,
                    _: std::os::raw::c_int, _: std::os::raw::c_uint, _: std::os::raw::c_uint,
                    _: std::os::raw::c_ulong, _: std::os::raw::c_int, _: *mut XImage,
                    _: std::os::raw::c_int, _: std::os::raw::c_int) -> *mut XImage;
    #[no_mangle]
    fn XOpenDisplay(_: *const std::os::raw::c_char) -> *mut Display;
    #[no_mangle]
    fn XInternAtom(_: *mut Display, _: *const std::os::raw::c_char, _: std::os::raw::c_int)
     -> Atom;
    #[no_mangle]
    fn XCreateFontCursor(_: *mut Display, _: std::os::raw::c_uint) -> Cursor;
    #[no_mangle]
    fn XCreateGC(_: *mut Display, _: Drawable, _: std::os::raw::c_ulong,
                 _: *mut XGCValues) -> GC;
    #[no_mangle]
    fn XCreateWindow(_: *mut Display, _: Window, _: std::os::raw::c_int,
                     _: std::os::raw::c_int, _: std::os::raw::c_uint, _: std::os::raw::c_uint,
                     _: std::os::raw::c_uint, _: std::os::raw::c_int, _: std::os::raw::c_uint,
                     _: *mut Visual, _: std::os::raw::c_ulong,
                     _: *mut XSetWindowAttributes) -> Window;
    #[no_mangle]
    fn XKeycodeToKeysym(_: *mut Display, _: KeyCode, _: std::os::raw::c_int)
     -> KeySym;
    #[no_mangle]
    fn XSetWMProtocols(_: *mut Display, _: Window, _: *mut Atom,
                       _: std::os::raw::c_int) -> std::os::raw::c_int;
    #[no_mangle]
    fn XChangeProperty(_: *mut Display, _: Window, _: Atom, _: Atom,
                       _: std::os::raw::c_int, _: std::os::raw::c_int,
                       _: *const std::os::raw::c_uchar, _: std::os::raw::c_int)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn XDefineCursor(_: *mut Display, _: Window, _: Cursor) -> std::os::raw::c_int;
    #[no_mangle]
    fn XMapWindow(_: *mut Display, _: Window) -> std::os::raw::c_int;
    #[no_mangle]
    fn XNextEvent(_: *mut Display, _: *mut XEvent) -> std::os::raw::c_int;
    #[no_mangle]
    fn XParseGeometry(_: *const std::os::raw::c_char, _: *mut std::os::raw::c_int,
                      _: *mut std::os::raw::c_int, _: *mut std::os::raw::c_uint,
                      _: *mut std::os::raw::c_uint) -> std::os::raw::c_int;
    #[no_mangle]
    fn XPending(_: *mut Display) -> std::os::raw::c_int;
    #[no_mangle]
    fn XPutImage(_: *mut Display, _: Drawable, _: GC, _: *mut XImage,
                 _: std::os::raw::c_int, _: std::os::raw::c_int, _: std::os::raw::c_int,
                 _: std::os::raw::c_int, _: std::os::raw::c_uint, _: std::os::raw::c_uint)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn XSync(_: *mut Display, _: std::os::raw::c_int) -> std::os::raw::c_int;
    #[no_mangle]
    fn XAllocClassHint() -> *mut XClassHint;
    #[no_mangle]
    fn XAllocSizeHints() -> *mut XSizeHints;
    #[no_mangle]
    fn XSetWMProperties(_: *mut Display, _: Window, _: *mut XTextProperty,
                        _: *mut XTextProperty, _: *mut *mut std::os::raw::c_char,
                        _: std::os::raw::c_int, _: *mut XSizeHints, _: *mut XWMHints,
                        _: *mut XClassHint);
    #[no_mangle]
    fn XStringListToTextProperty(_: *mut *mut std::os::raw::c_char, _: std::os::raw::c_int,
                                 _: *mut XTextProperty) -> std::os::raw::c_int;
    #[no_mangle]
    fn alarm(__seconds: std::os::raw::c_uint) -> std::os::raw::c_uint;
    #[no_mangle]
    fn usleep(__useconds: __useconds_t) -> std::os::raw::c_int;
}
pub type size_t = std::os::raw::c_ulong;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
pub type __useconds_t = std::os::raw::c_uint;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: std::os::raw::c_int,
    pub _IO_read_ptr: *mut std::os::raw::c_char,
    pub _IO_read_end: *mut std::os::raw::c_char,
    pub _IO_read_base: *mut std::os::raw::c_char,
    pub _IO_write_base: *mut std::os::raw::c_char,
    pub _IO_write_ptr: *mut std::os::raw::c_char,
    pub _IO_write_end: *mut std::os::raw::c_char,
    pub _IO_buf_base: *mut std::os::raw::c_char,
    pub _IO_buf_end: *mut std::os::raw::c_char,
    pub _IO_save_base: *mut std::os::raw::c_char,
    pub _IO_backup_base: *mut std::os::raw::c_char,
    pub _IO_save_end: *mut std::os::raw::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: std::os::raw::c_int,
    pub _flags2: std::os::raw::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: std::os::raw::c_ushort,
    pub _vtable_offset: std::os::raw::c_schar,
    pub _shortbuf: [std::os::raw::c_char; 1],
    pub _lock: *mut std::os::raw::c_void,
    pub _offset: __off64_t,
    pub __pad1: *mut std::os::raw::c_void,
    pub __pad2: *mut std::os::raw::c_void,
    pub __pad3: *mut std::os::raw::c_void,
    pub __pad4: *mut std::os::raw::c_void,
    pub __pad5: size_t,
    pub _mode: std::os::raw::c_int,
    pub _unused2: [std::os::raw::c_char; 20],
}
pub type _IO_lock_t = ();
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_marker {
    pub _next: *mut _IO_marker,
    pub _sbuf: *mut _IO_FILE,
    pub _pos: std::os::raw::c_int,
}
pub type FILE = _IO_FILE;
pub type __sighandler_t = Option<unsafe extern "C" fn(_: std::os::raw::c_int) -> ()>;
pub type XID = std::os::raw::c_ulong;
pub type Atom = std::os::raw::c_ulong;
pub type VisualID = std::os::raw::c_ulong;
pub type Time = std::os::raw::c_ulong;
pub type Window = XID;
pub type Drawable = XID;
pub type Font = XID;
pub type Pixmap = XID;
pub type Cursor = XID;
pub type Colormap = XID;
pub type KeySym = XID;
pub type KeyCode = std::os::raw::c_uchar;
pub type XPointer = *mut std::os::raw::c_char;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _XExtData {
    pub number: std::os::raw::c_int,
    pub next: *mut _XExtData,
    pub free_private: Option<unsafe extern "C" fn(_: *mut _XExtData)
                                 -> std::os::raw::c_int>,
    pub private_data: XPointer,
}
pub type XExtData = _XExtData;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGCValues {
    pub function: std::os::raw::c_int,
    pub plane_mask: std::os::raw::c_ulong,
    pub foreground: std::os::raw::c_ulong,
    pub background: std::os::raw::c_ulong,
    pub line_width: std::os::raw::c_int,
    pub line_style: std::os::raw::c_int,
    pub cap_style: std::os::raw::c_int,
    pub join_style: std::os::raw::c_int,
    pub fill_style: std::os::raw::c_int,
    pub fill_rule: std::os::raw::c_int,
    pub arc_mode: std::os::raw::c_int,
    pub tile: Pixmap,
    pub stipple: Pixmap,
    pub ts_x_origin: std::os::raw::c_int,
    pub ts_y_origin: std::os::raw::c_int,
    pub font: Font,
    pub subwindow_mode: std::os::raw::c_int,
    pub graphics_exposures: std::os::raw::c_int,
    pub clip_x_origin: std::os::raw::c_int,
    pub clip_y_origin: std::os::raw::c_int,
    pub clip_mask: Pixmap,
    pub dash_offset: std::os::raw::c_int,
    pub dashes: std::os::raw::c_char,
}
pub type GC = *mut _XGC;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Visual {
    pub ext_data: *mut XExtData,
    pub visualid: VisualID,
    pub class: std::os::raw::c_int,
    pub red_mask: std::os::raw::c_ulong,
    pub green_mask: std::os::raw::c_ulong,
    pub blue_mask: std::os::raw::c_ulong,
    pub bits_per_rgb: std::os::raw::c_int,
    pub map_entries: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Depth {
    pub depth: std::os::raw::c_int,
    pub nvisuals: std::os::raw::c_int,
    pub visuals: *mut Visual,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Screen {
    pub ext_data: *mut XExtData,
    pub display: *mut _XDisplay,
    pub root: Window,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub mwidth: std::os::raw::c_int,
    pub mheight: std::os::raw::c_int,
    pub ndepths: std::os::raw::c_int,
    pub depths: *mut Depth,
    pub root_depth: std::os::raw::c_int,
    pub root_visual: *mut Visual,
    pub default_gc: GC,
    pub cmap: Colormap,
    pub white_pixel: std::os::raw::c_ulong,
    pub black_pixel: std::os::raw::c_ulong,
    pub max_maps: std::os::raw::c_int,
    pub min_maps: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub save_unders: std::os::raw::c_int,
    pub root_input_mask: std::os::raw::c_long,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ScreenFormat {
    pub ext_data: *mut XExtData,
    pub depth: std::os::raw::c_int,
    pub bits_per_pixel: std::os::raw::c_int,
    pub scanline_pad: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSetWindowAttributes {
    pub background_pixmap: Pixmap,
    pub background_pixel: std::os::raw::c_ulong,
    pub border_pixmap: Pixmap,
    pub border_pixel: std::os::raw::c_ulong,
    pub bit_gravity: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub backing_planes: std::os::raw::c_ulong,
    pub backing_pixel: std::os::raw::c_ulong,
    pub save_under: std::os::raw::c_int,
    pub event_mask: std::os::raw::c_long,
    pub do_not_propagate_mask: std::os::raw::c_long,
    pub override_redirect: std::os::raw::c_int,
    pub colormap: Colormap,
    pub cursor: Cursor,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _XImage {
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub xoffset: std::os::raw::c_int,
    pub format: std::os::raw::c_int,
    pub data: *mut std::os::raw::c_char,
    pub byte_order: std::os::raw::c_int,
    pub bitmap_unit: std::os::raw::c_int,
    pub bitmap_bit_order: std::os::raw::c_int,
    pub bitmap_pad: std::os::raw::c_int,
    pub depth: std::os::raw::c_int,
    pub bytes_per_line: std::os::raw::c_int,
    pub bits_per_pixel: std::os::raw::c_int,
    pub red_mask: std::os::raw::c_ulong,
    pub green_mask: std::os::raw::c_ulong,
    pub blue_mask: std::os::raw::c_ulong,
    pub obdata: XPointer,
    pub f: funcs,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct funcs {
    pub create_image: Option<unsafe extern "C" fn(_: *mut _XDisplay,
                                                  _: *mut Visual,
                                                  _: std::os::raw::c_uint,
                                                  _: std::os::raw::c_int,
                                                  _: std::os::raw::c_int,
                                                  _: *mut std::os::raw::c_char,
                                                  _: std::os::raw::c_uint,
                                                  _: std::os::raw::c_uint,
                                                  _: std::os::raw::c_int,
                                                  _: std::os::raw::c_int)
                                 -> *mut _XImage>,
    pub destroy_image: Option<unsafe extern "C" fn(_: *mut _XImage)
                                  -> std::os::raw::c_int>,
    pub get_pixel: Option<unsafe extern "C" fn(_: *mut _XImage,
                                               _: std::os::raw::c_int, _: std::os::raw::c_int)
                              -> std::os::raw::c_ulong>,
    pub put_pixel: Option<unsafe extern "C" fn(_: *mut _XImage,
                                               _: std::os::raw::c_int, _: std::os::raw::c_int,
                                               _: std::os::raw::c_ulong)
                              -> std::os::raw::c_int>,
    pub sub_image: Option<unsafe extern "C" fn(_: *mut _XImage,
                                               _: std::os::raw::c_int, _: std::os::raw::c_int,
                                               _: std::os::raw::c_uint,
                                               _: std::os::raw::c_uint)
                              -> *mut _XImage>,
    pub add_pixel: Option<unsafe extern "C" fn(_: *mut _XImage,
                                               _: std::os::raw::c_long)
                              -> std::os::raw::c_int>,
}
pub type XImage = _XImage;
pub type Display = _XDisplay;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed {
    pub ext_data: *mut XExtData,
    pub private1: *mut _XPrivate,
    pub fd: std::os::raw::c_int,
    pub private2: std::os::raw::c_int,
    pub proto_major_version: std::os::raw::c_int,
    pub proto_minor_version: std::os::raw::c_int,
    pub vendor: *mut std::os::raw::c_char,
    pub private3: XID,
    pub private4: XID,
    pub private5: XID,
    pub private6: std::os::raw::c_int,
    pub resource_alloc: Option<unsafe extern "C" fn(_: *mut _XDisplay)
                                   -> XID>,
    pub byte_order: std::os::raw::c_int,
    pub bitmap_unit: std::os::raw::c_int,
    pub bitmap_pad: std::os::raw::c_int,
    pub bitmap_bit_order: std::os::raw::c_int,
    pub nformats: std::os::raw::c_int,
    pub pixmap_format: *mut ScreenFormat,
    pub private8: std::os::raw::c_int,
    pub release: std::os::raw::c_int,
    pub private9: *mut _XPrivate,
    pub private10: *mut _XPrivate,
    pub qlen: std::os::raw::c_int,
    pub last_request_read: std::os::raw::c_ulong,
    pub request: std::os::raw::c_ulong,
    pub private11: XPointer,
    pub private12: XPointer,
    pub private13: XPointer,
    pub private14: XPointer,
    pub max_request_size: std::os::raw::c_uint,
    pub db: *mut _XrmHashBucketRec,
    pub private15: Option<unsafe extern "C" fn(_: *mut _XDisplay)
                              -> std::os::raw::c_int>,
    pub display_name: *mut std::os::raw::c_char,
    pub default_screen: std::os::raw::c_int,
    pub nscreens: std::os::raw::c_int,
    pub screens: *mut Screen,
    pub motion_buffer: std::os::raw::c_ulong,
    pub private16: std::os::raw::c_ulong,
    pub min_keycode: std::os::raw::c_int,
    pub max_keycode: std::os::raw::c_int,
    pub private17: XPointer,
    pub private18: XPointer,
    pub private19: std::os::raw::c_int,
    pub xdefaults: *mut std::os::raw::c_char,
}
pub type _XPrivDisplay = *mut C2RustUnnamed;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XKeyEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub keycode: std::os::raw::c_uint,
    pub same_screen: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XButtonEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub button: std::os::raw::c_uint,
    pub same_screen: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMotionEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub is_hint: std::os::raw::c_char,
    pub same_screen: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCrossingEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub mode: std::os::raw::c_int,
    pub detail: std::os::raw::c_int,
    pub same_screen: std::os::raw::c_int,
    pub focus: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XFocusChangeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub mode: std::os::raw::c_int,
    pub detail: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XKeymapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub key_vector: [std::os::raw::c_char; 32],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XExposeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGraphicsExposeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub drawable: Drawable,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
    pub major_code: std::os::raw::c_int,
    pub minor_code: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XNoExposeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub drawable: Drawable,
    pub major_code: std::os::raw::c_int,
    pub minor_code: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XVisibilityEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub state: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCreateWindowEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub override_redirect: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XDestroyWindowEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XUnmapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub from_configure: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub override_redirect: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMapRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XReparentEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub parent: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub override_redirect: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XConfigureEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub above: Window,
    pub override_redirect: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGravityEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XResizeRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XConfigureRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub above: Window,
    pub detail: std::os::raw::c_int,
    pub value_mask: std::os::raw::c_ulong,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCirculateEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub place: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCirculateRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub place: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XPropertyEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub atom: Atom,
    pub time: Time,
    pub state: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionClearEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub selection: Atom,
    pub time: Time,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub owner: Window,
    pub requestor: Window,
    pub selection: Atom,
    pub target: Atom,
    pub property: Atom,
    pub time: Time,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub requestor: Window,
    pub selection: Atom,
    pub target: Atom,
    pub property: Atom,
    pub time: Time,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XColormapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub colormap: Colormap,
    pub new: std::os::raw::c_int,
    pub state: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XClientMessageEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub message_type: Atom,
    pub format: std::os::raw::c_int,
    pub data: C2RustUnnamed_0,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed_0 {
    pub b: [std::os::raw::c_char; 20],
    pub s: [std::os::raw::c_short; 10],
    pub l: [std::os::raw::c_long; 5],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMappingEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub request: std::os::raw::c_int,
    pub first_keycode: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XErrorEvent {
    pub type_0: std::os::raw::c_int,
    pub display: *mut Display,
    pub resourceid: XID,
    pub serial: std::os::raw::c_ulong,
    pub error_code: std::os::raw::c_uchar,
    pub request_code: std::os::raw::c_uchar,
    pub minor_code: std::os::raw::c_uchar,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XAnyEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub window: Window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGenericEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub extension: std::os::raw::c_int,
    pub evtype: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGenericEventCookie {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: *mut Display,
    pub extension: std::os::raw::c_int,
    pub evtype: std::os::raw::c_int,
    pub cookie: std::os::raw::c_uint,
    pub data: *mut std::os::raw::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union _XEvent {
    pub type_0: std::os::raw::c_int,
    pub xany: XAnyEvent,
    pub xkey: XKeyEvent,
    pub xbutton: XButtonEvent,
    pub xmotion: XMotionEvent,
    pub xcrossing: XCrossingEvent,
    pub xfocus: XFocusChangeEvent,
    pub xexpose: XExposeEvent,
    pub xgraphicsexpose: XGraphicsExposeEvent,
    pub xnoexpose: XNoExposeEvent,
    pub xvisibility: XVisibilityEvent,
    pub xcreatewindow: XCreateWindowEvent,
    pub xdestroywindow: XDestroyWindowEvent,
    pub xunmap: XUnmapEvent,
    pub xmap: XMapEvent,
    pub xmaprequest: XMapRequestEvent,
    pub xreparent: XReparentEvent,
    pub xconfigure: XConfigureEvent,
    pub xgravity: XGravityEvent,
    pub xresizerequest: XResizeRequestEvent,
    pub xconfigurerequest: XConfigureRequestEvent,
    pub xcirculate: XCirculateEvent,
    pub xcirculaterequest: XCirculateRequestEvent,
    pub xproperty: XPropertyEvent,
    pub xselectionclear: XSelectionClearEvent,
    pub xselectionrequest: XSelectionRequestEvent,
    pub xselection: XSelectionEvent,
    pub xcolormap: XColormapEvent,
    pub xclient: XClientMessageEvent,
    pub xmapping: XMappingEvent,
    pub xerror: XErrorEvent,
    pub xkeymap: XKeymapEvent,
    pub xgeneric: XGenericEvent,
    pub xcookie: XGenericEventCookie,
    pub pad: [std::os::raw::c_long; 24],
}
pub type XEvent = _XEvent;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSizeHints {
    pub flags: std::os::raw::c_long,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub min_width: std::os::raw::c_int,
    pub min_height: std::os::raw::c_int,
    pub max_width: std::os::raw::c_int,
    pub max_height: std::os::raw::c_int,
    pub width_inc: std::os::raw::c_int,
    pub height_inc: std::os::raw::c_int,
    pub min_aspect: C2RustUnnamed_1,
    pub max_aspect: C2RustUnnamed_1,
    pub base_width: std::os::raw::c_int,
    pub base_height: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_1 {
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XWMHints {
    pub flags: std::os::raw::c_long,
    pub input: std::os::raw::c_int,
    pub initial_state: std::os::raw::c_int,
    pub icon_pixmap: Pixmap,
    pub icon_window: Window,
    pub icon_x: std::os::raw::c_int,
    pub icon_y: std::os::raw::c_int,
    pub icon_mask: Pixmap,
    pub window_group: XID,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XTextProperty {
    pub value: *mut std::os::raw::c_uchar,
    pub encoding: Atom,
    pub format: std::os::raw::c_int,
    pub nitems: std::os::raw::c_ulong,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XClassHint {
    pub res_name: *mut std::os::raw::c_char,
    pub res_class: *mut std::os::raw::c_char,
}
/* Copyright Itai Nahshon 1995, 1996.
   This program is distributed with no warranty.

   Source files for this program may be distributed freely.
   Modifications to this file are okay as long as:
    a. This copyright notice and comment are preserved and
	   left at the top of the file.
	b. The man page is fixed to reflect the change.
	c. The author of this change adds his name and change
	   description to the list of changes below.
   Executable files may be distributed with sources, or with
   exact location where the source code can be obtained.

Changelist:
Author                    Description
------                    -----------
Itai Nahshon              Version 0.1, Nov. 21 1995
Itai Nahshon              Version 0.2, Apr. 17 1996
                          include <sys/types.h>
                          Use memmove() instead of memcopy()
                          Optional macro to replace call to usleep().
Markus F.X.J. Oberhumer   Version 0.4, Feb. 18 1998
                          split into 2 files (scale.h)
                          added support for 15, 16, 24 and 32 bpp displays
                          added a grid (press key 'g')
                          optimized scaling routines
                          use memcpy() instead of memmove() ;-)
                          some other minor changes/fixes
tony mancill		2002/02/13 <tmancill@debian.org>
			hacked in support for WM_DELETE_WINDOW
*/
#[no_mangle]
pub static mut dpy: *mut Display = 0 as *const Display as *mut Display;
#[no_mangle]
pub static mut scr: *mut Screen = 0 as *const Screen as *mut Screen;
#[no_mangle]
pub static mut win: Window = 0;
#[no_mangle]
pub static mut wm_delete_window: Atom = 0;
#[no_mangle]
pub static mut wm_protocols: Atom = 0;
#[no_mangle]
pub static mut wm_dock: Atom = 0;
#[no_mangle]
pub static mut wm_windowtype: Atom = 0;
#[no_mangle]
pub static mut status: std::os::raw::c_int = 0;
#[no_mangle]
pub static mut gc: GC = 0 as *const _XGC as *mut _XGC;
#[no_mangle]
pub static mut when_button: Cursor = 0;
#[no_mangle]
pub static mut crosshair: Cursor = 0;
#[no_mangle]
pub static mut progname: *mut std::os::raw::c_char =
    0 as *const std::os::raw::c_char as *mut std::os::raw::c_char;
#[no_mangle]
pub static mut set_title: std::os::raw::c_int = 0;
/* vertical magnification */
#[no_mangle]
pub static mut xgrab: std::os::raw::c_int = 0;
#[no_mangle]
pub static mut ygrab: std::os::raw::c_int = 0;
/* where do we take the picture from */
#[no_mangle]
pub static mut magx: std::os::raw::c_int = 2 as std::os::raw::c_int;
#[no_mangle]
pub static mut magy: std::os::raw::c_int = 2 as std::os::raw::c_int;
#[no_mangle]
pub static mut flipxy: std::os::raw::c_int = 0 as std::os::raw::c_int;
/* flip x and y */
#[no_mangle]
pub static mut flipx: std::os::raw::c_int = 0 as std::os::raw::c_int;
/* flip display about y axis */
#[no_mangle]
pub static mut flipy: std::os::raw::c_int = 0 as std::os::raw::c_int;
/* flip display about x axiz */
#[no_mangle]
pub static mut xzoom_flag: std::os::raw::c_int = 0 as std::os::raw::c_int;
/* next mag change only to magx */
#[no_mangle]
pub static mut yzoom_flag: std::os::raw::c_int = 0 as std::os::raw::c_int;
/* next mag change only to magy */
#[no_mangle]
pub static mut gridx: std::os::raw::c_int = 0 as std::os::raw::c_int;
#[no_mangle]
pub static mut gridy: std::os::raw::c_int = 0 as std::os::raw::c_int;
#[no_mangle]
pub static mut width: [std::os::raw::c_int; 2] =
    [0 as std::os::raw::c_int, 256 as std::os::raw::c_int];
#[no_mangle]
pub static mut height: [std::os::raw::c_int; 2] =
    [0 as std::os::raw::c_int, 256 as std::os::raw::c_int];
#[no_mangle]
pub static mut depth: std::os::raw::c_uint = 0 as std::os::raw::c_int as std::os::raw::c_uint;
#[no_mangle]
pub static mut ximage: [*mut XImage; 2] =
    [0 as *const XImage as *mut XImage; 2];
/* Ximage struct. */
#[no_mangle]
pub static mut created_images: std::os::raw::c_int = 0 as std::os::raw::c_int;
#[no_mangle]
pub static mut delays: [std::os::raw::c_int; 5] =
    [200000 as std::os::raw::c_int, 100000 as std::os::raw::c_int, 50000 as std::os::raw::c_int,
     10000 as std::os::raw::c_int, 0 as std::os::raw::c_int];
#[no_mangle]
pub static mut delay_index: std::os::raw::c_int = 0 as std::os::raw::c_int;
#[no_mangle]
pub static mut delay: std::os::raw::c_int = 200000 as std::os::raw::c_int;
/* 0.2 second between updates */
#[no_mangle]
pub unsafe extern "C" fn timeout_func(signum: i32) {
    set_title = 1;
    let _unused = signum; // Marking signum as unused
}

#[no_mangle]
pub unsafe extern "C" fn allocate_images() {
    let mut i: std::os::raw::c_int = 0;
    i = 0 as std::os::raw::c_int;
    while i < 2 as std::os::raw::c_int {
        let mut data: *mut std::os::raw::c_char = 0 as *mut std::os::raw::c_char;
        data =
            malloc(((*(dpy as _XPrivDisplay)).bitmap_unit / 8 as std::os::raw::c_int *
                        width[i as usize] * height[i as usize]) as
                       std::os::raw::c_ulong) as *mut std::os::raw::c_char;
        ximage[i as usize] =
            XCreateImage(dpy, (*scr).root_visual,
                         (*scr).root_depth as std::os::raw::c_uint, 2 as std::os::raw::c_int,
                         0 as std::os::raw::c_int, data,
                         width[i as usize] as std::os::raw::c_uint,
                         height[i as usize] as std::os::raw::c_uint,
                         32 as std::os::raw::c_int, 0 as std::os::raw::c_int);
        if ximage[i as usize].is_null() {
            perror(b"XCreateImage\x00" as *const u8 as *const std::os::raw::c_char);
            exit(-(1 as std::os::raw::c_int));
        }
        i += 1
        /* XSHM */
    }
    created_images = 1 as std::os::raw::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn destroy_images() {
    let mut i: std::os::raw::c_int = 0;
    if created_images == 0 { return }
    i = 0 as std::os::raw::c_int;
    while i < 2 as std::os::raw::c_int {
        free((*ximage[i as usize]).data as *mut std::os::raw::c_void);
        /* and destroy image */
        (*ximage[i as usize]).data =
            0 as *mut std::os::raw::c_char; /* remove refrence to that address */
        Some((**ximage.as_mut_ptr().offset(i as
                                               isize)).f.destroy_image.expect("non-null function pointer")).expect("non-null function pointer")(ximage[i
                                                                                                                                                           as
                                                                                                                                                           usize]);
        i += 1
    }
    created_images = 0 as std::os::raw::c_int;
}
#[no_mangle]
pub fn Usage() {
    let usage_message = format!(
        "Usage: {} [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-dock\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next '+' or '-' only change width scaling\nh: Next '+' or '-' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n",
        unsafe { std::ffi::CStr::from_ptr(progname).to_string_lossy() }
    );
    eprintln!("{}", usage_message);
    std::process::exit(1);
}

/* resize is called with the dest size.
   we call it then manification changes or when
   actual window size is changed */
#[no_mangle]
pub fn resize(new_width: i32, new_height: i32) {
    unsafe {
        destroy_images(); // we can get rid of these
        // find new dimensions for source
        let (new_width, new_height) = if flipxy != 0 {
            (
                (new_height + magy - 1) / magy,
                (new_width + magx - 1) / magx,
            )
        } else {
            (
                (new_width + magx - 1) / magx,
                (new_height + magy - 1) / magy,
            )
        };

        let screen_width = (*scr).width;
        let screen_height = (*scr).height;

        width[0] = new_width.clamp(1, screen_width);
        height[0] = new_height.clamp(1, screen_height);

        // temporary, the dest image may be larger than the actual window
        if flipxy != 0 {
            width[1] = magx * height[0]; // allocate new images
            height[1] = magy * width[0];
        } else {
            width[1] = magx * width[0];
            height[1] = magy * height[0];
        }

        allocate_images();

        // remember actual window size
        width[1] = width[1].min(new_width);
        height[1] = height[1].min(new_height);
    }
}

#[no_mangle]
pub unsafe extern "C" fn scale8() {
    /* scale image from SRC to DST - parameterized by type T */
    /* scale image from SRC to DST - parameterized by type T */
    /* scale image from SRC to DST - parameterized by type T */
    /* get pixel address of point (x,y) in image t */
    /* get pixel address of point (x,y) in image t */
    /* get pixel address of point (x,y) in image t */
    let mut i: i32 = 0;
let mut j: i32 = 0;
let mut k: i32 = 0;

/* copy scaled lines from SRC to DST */
/* copy scaled lines from SRC to DST */
/* copy scaled lines from SRC to DST */
j = if flipxy != 0 {
    width[0] - 1
} else {
    height[0] - 1
};

loop {
     let mut p1: *mut std::os::raw::c_uchar = 0 as *mut std::os::raw::c_uchar;
        let mut p2: *mut std::os::raw::c_uchar = 0 as *mut std::os::raw::c_uchar;
        let mut p2step: std::os::raw::c_int = 0;
        let mut p1_save: *mut std::os::raw::c_uchar = 0 as *mut std::os::raw::c_uchar;
        /* p1 point to begining of scanline j*magy in DST */
        /* p1 point to begining of scanline j*magy in DST */
        /* p1 point to begining of scanline j*magy in DST */
        p1 =
            &mut *(**ximage.as_mut_ptr().offset(1 as std::os::raw::c_int as
                                                    isize)).data.offset((((**ximage.as_mut_ptr().offset(1
                                                                                                            as
                                                                                                            std::os::raw::c_int
                                                                                                            as
                                                                                                            isize)).xoffset
                                                                              +
                                                                              0
                                                                                  as
                                                                                  std::os::raw::c_int)
                                                                             as
                                                                             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uchar>()
                                                                                                             as
                                                                                                             std::os::raw::c_ulong).wrapping_add((j
                                                                                                                                              *
                                                                                                                                              magy
                                                                                                                                              *
                                                                                                                                              (**ximage.as_mut_ptr().offset(1
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)).bytes_per_line)
                                                                                                                                             as
                                                                                                                                             std::os::raw::c_ulong)
                                                                            as
                                                                            isize)
                as *mut std::os::raw::c_char as *mut std::os::raw::c_uchar;
        p1_save = p1;
        /* p2 point to begining of scanline j in SRC */
		/* if flipy then line height[SRC]-1-j */
        /* p2 point to begining of scanline j in SRC */
		/* if flipy then line height[SRC]-1-j */
        /* p2 point to begining of scanline j in SRC */
		/* if flipy then line height[SRC]-1-j */
        p2 =
            &mut *(**ximage.as_mut_ptr().offset(0 as std::os::raw::c_int as
                                                    isize)).data.offset((((**ximage.as_mut_ptr().offset(0
                                                                                                            as
                                                                                                            std::os::raw::c_int
                                                                                                            as
                                                                                                            isize)).xoffset
                                                                              +
                                                                              0
                                                                                  as
                                                                                  std::os::raw::c_int)
                                                                             as
                                                                             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uchar>()
                                                                                                             as
                                                                                                             std::os::raw::c_ulong).wrapping_add(((if flipy
                                                                                                                                                  !=
                                                                                                                                                  0
                                                                                                                                              {
                                                                                                                                               (*height.as_mut_ptr().offset(0
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)
                                                                                                                                                    -
                                                                                                                                                    1
                                                                                                                                                        as
                                                                                                                                                        std::os::raw::c_int)
                                                                                                                                                   -
                                                                                                                                                   j
                                                                                                                                           } else {
                                                                                                                                               j
                                                                                                                                           })
                                                                                                                                              *
                                                                                                                                              (**ximage.as_mut_ptr().offset(0
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)).bytes_per_line)
                                                                                                                                             as
                                                                                                                                             std::os::raw::c_ulong)
                                                                            as
                                                                            isize)
                as *mut std::os::raw::c_char as *mut std::os::raw::c_uchar;
       
     if flipxy != 0 {
            p2 =
                &mut *(**ximage.as_mut_ptr().offset(0 as std::os::raw::c_int as
                                                        isize)).data.offset((((**ximage.as_mut_ptr().offset(0
                                                                                                                as
                                                                                                                std::os::raw::c_int
                                                                                                                as
                                                                                                                isize)).xoffset
                                                                                  +
                                                                                  (if flipy
                                                                                          !=
                                                                                          0
                                                                                      {
                                                                                       j
                                                                                   } else {
                                                                                       (*width.as_mut_ptr().offset(0
                                                                                                                       as
                                                                                                                       std::os::raw::c_int
                                                                                                                       as
                                                                                                                       isize)
                                                                                            -
                                                                                            1
                                                                                                as
                                                                                                std::os::raw::c_int)
                                                                                           -
                                                                                           j
                                                                                   }))
                                                                                 as
                                                                                 std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uchar>()
                                                                                                                 as
                                                                                                                 std::os::raw::c_ulong).wrapping_add((0
                                                                                                                                                  as
                                                                                                                                                  std::os::raw::c_int
                                                                                                                                                  *
                                                                                                                                                  (**ximage.as_mut_ptr().offset(0
                                                                                                                                                                                    as
                                                                                                                                                                                    std::os::raw::c_int
                                                                                                                                                                                    as
                                                                                                                                                                                    isize)).bytes_per_line)
                                                                                                                                                 as
                                                                                                                                                 std::os::raw::c_ulong)
                                                                                as
                                                                                isize)
                    as *mut std::os::raw::c_char as *mut std::os::raw::c_uchar;
            p2step =
                ((*ximage[0 as std::os::raw::c_int as usize]).bytes_per_line as
                     std::os::raw::c_ulong).wrapping_div(::std::mem::size_of::<std::os::raw::c_uchar>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            if flipx != 0 {
                p2 =
                    p2.offset((p2step *
                                   (height[0 as std::os::raw::c_int as usize] -
                                        1 as std::os::raw::c_int)) as isize);
                p2step = -p2step
            }
            i = height[0 as std::os::raw::c_int as usize];
            loop  {
                let mut c: std::os::raw::c_uchar = *p2;
                p2 = p2.offset(p2step as isize);
                k = magx;
                loop  {
                    let fresh0 = p1;
                    p1 = p1.offset(1);
                    *fresh0 = c;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        } else if flipx != 0 {
            p2 = p2.offset(width[0 as std::os::raw::c_int as usize] as isize);
            i = width[0 as std::os::raw::c_int as usize];
            loop  {
                p2 = p2.offset(-1);
                let mut c_0: std::os::raw::c_uchar = *p2;
                k = magx;
                loop  {
                    let fresh1 = p1;
                    p1 = p1.offset(1);
                    *fresh1 = c_0;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        } else {
            i = width[0 as std::os::raw::c_int as usize];
            loop  {
                let fresh2 = p2;
                p2 = p2.offset(1);
                let mut c_1: std::os::raw::c_uchar = *fresh2;
                k = magx;
                loop  {
                    let fresh3 = p1;
                    p1 = p1.offset(1);
                    *fresh3 = c_1;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        }
        /* draw vertical grid */
        /* draw vertical grid */
        /* draw vertical grid */
        if gridy != 0 && magx >= 2 as std::os::raw::c_int {
            p1 = p1_save.offset(-(1 as std::os::raw::c_int as isize));
            i = magx;
            k =
                if flipxy != 0 {
                    height[0 as std::os::raw::c_int as usize]
                } else { width[0 as std::os::raw::c_int as usize] };
            loop  {
                p1 = p1.offset(i as isize);
                *p1 =
                    (*p1 as std::os::raw::c_int ^
                         !(0 as std::os::raw::c_int as std::os::raw::c_uchar as std::os::raw::c_int))
                        as std::os::raw::c_uchar;
                k -= 1;
                if !(k > 0 as std::os::raw::c_int) { break ; }
            }
        }
        
    /* duplicate that line as needed */
    /* duplicate that line as needed */
    /* duplicate that line as needed */
     if magy > 1 {
    // p1 points to the beginning of scanline j * magy in DST
    p1 = p1_save;

    // p2 points to the beginning of the next line
    p2 = p1;
    p2step = ((*ximage[1]).bytes_per_line / std::mem::size_of::<u8>() as i32) as i32;
    i = (width[1] * std::mem::size_of::<u8>() as i32) as i32;
    k = magy - 1;

    while k > 0 {
        p2 = p2.add(p2step as usize);
        std::ptr::copy_nonoverlapping(p1, p2, i as usize);
        k -= 1;
    }

    // draw horizontal grid
    if gridx != 0 && magy >= 2 {
        k = width[1];
        while k > 0 {
            let fresh4 = p2;
            p2 = p2.add(1);
            *fresh4 ^= 0xFF; // Assuming the intention is to toggle the byte
            k -= 1;
        }
    }
}
j -= 1;
if j < 0 {
    break;
}

    
};

}
#[no_mangle]
pub unsafe extern "C" fn scale16() {
    let mut i: std::os::raw::c_int = 0;
    let mut j: std::os::raw::c_int = 0;
    let mut k: std::os::raw::c_int = 0;
    j =
        if flipxy != 0 {
            (width[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int
        } else { (height[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int };
    loop  {
        let mut p1: *mut std::os::raw::c_ushort = 0 as *mut std::os::raw::c_ushort;
        let mut p2: *mut std::os::raw::c_ushort = 0 as *mut std::os::raw::c_ushort;
        let mut p2step: std::os::raw::c_int = 0;
        let mut p1_save: *mut std::os::raw::c_ushort = 0 as *mut std::os::raw::c_ushort;
        p1 =
            &mut *(**ximage.as_mut_ptr().offset(1 as std::os::raw::c_int as
                                                    isize)).data.offset((((**ximage.as_mut_ptr().offset(1
                                                                                                            as
                                                                                                            std::os::raw::c_int
                                                                                                            as
                                                                                                            isize)).xoffset
                                                                              +
                                                                              0
                                                                                  as
                                                                                  std::os::raw::c_int)
                                                                             as
                                                                             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_ushort>()
                                                                                                             as
                                                                                                             std::os::raw::c_ulong).wrapping_add((j
                                                                                                                                              *
                                                                                                                                              magy
                                                                                                                                              *
                                                                                                                                              (**ximage.as_mut_ptr().offset(1
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)).bytes_per_line)
                                                                                                                                             as
                                                                                                                                             std::os::raw::c_ulong)
                                                                            as
                                                                            isize)
                as *mut std::os::raw::c_char as *mut std::os::raw::c_ushort;
        p1_save = p1;
        p2 =
            &mut *(**ximage.as_mut_ptr().offset(0 as std::os::raw::c_int as
                                                    isize)).data.offset((((**ximage.as_mut_ptr().offset(0
                                                                                                            as
                                                                                                            std::os::raw::c_int
                                                                                                            as
                                                                                                            isize)).xoffset
                                                                              +
                                                                              0
                                                                                  as
                                                                                  std::os::raw::c_int)
                                                                             as
                                                                             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_ushort>()
                                                                                                             as
                                                                                                             std::os::raw::c_ulong).wrapping_add(((if flipy
                                                                                                                                                  !=
                                                                                                                                                  0
                                                                                                                                              {
                                                                                                                                               (*height.as_mut_ptr().offset(0
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)
                                                                                                                                                    -
                                                                                                                                                    1
                                                                                                                                                        as
                                                                                                                                                        std::os::raw::c_int)
                                                                                                                                                   -
                                                                                                                                                   j
                                                                                                                                           } else {
                                                                                                                                               j
                                                                                                                                           })
                                                                                                                                              *
                                                                                                                                              (**ximage.as_mut_ptr().offset(0
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)).bytes_per_line)
                                                                                                                                             as
                                                                                                                                             std::os::raw::c_ulong)
                                                                            as
                                                                            isize)
                as *mut std::os::raw::c_char as *mut std::os::raw::c_ushort;
        if flipxy != 0 {
            p2 =
                &mut *(**ximage.as_mut_ptr().offset(0 as std::os::raw::c_int as
                                                        isize)).data.offset((((**ximage.as_mut_ptr().offset(0
                                                                                                                as
                                                                                                                std::os::raw::c_int
                                                                                                                as
                                                                                                                isize)).xoffset
                                                                                  +
                                                                                  (if flipy
                                                                                          !=
                                                                                          0
                                                                                      {
                                                                                       j
                                                                                   } else {
                                                                                       (*width.as_mut_ptr().offset(0
                                                                                                                       as
                                                                                                                       std::os::raw::c_int
                                                                                                                       as
                                                                                                                       isize)
                                                                                            -
                                                                                            1
                                                                                                as
                                                                                                std::os::raw::c_int)
                                                                                           -
                                                                                           j
                                                                                   }))
                                                                                 as
                                                                                 std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_ushort>()
                                                                                                                 as
                                                                                                                 std::os::raw::c_ulong).wrapping_add((0
                                                                                                                                                  as
                                                                                                                                                  std::os::raw::c_int
                                                                                                                                                  *
                                                                                                                                                  (**ximage.as_mut_ptr().offset(0
                                                                                                                                                                                    as
                                                                                                                                                                                    std::os::raw::c_int
                                                                                                                                                                                    as
                                                                                                                                                                                    isize)).bytes_per_line)
                                                                                                                                                 as
                                                                                                                                                 std::os::raw::c_ulong)
                                                                                as
                                                                                isize)
                    as *mut std::os::raw::c_char as *mut std::os::raw::c_ushort;
            p2step =
                ((*ximage[0 as std::os::raw::c_int as usize]).bytes_per_line as
                     std::os::raw::c_ulong).wrapping_div(::std::mem::size_of::<std::os::raw::c_ushort>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            if flipx != 0 {
                p2 =
                    p2.offset((p2step *
                                   (height[0 as std::os::raw::c_int as usize] -
                                        1 as std::os::raw::c_int)) as isize);
                p2step = -p2step
            }
            i = height[0 as std::os::raw::c_int as usize];
            loop  {
                let mut c: std::os::raw::c_ushort = *p2;
                p2 = p2.offset(p2step as isize);
                k = magx;
                loop  {
                    let fresh5 = p1;
                    p1 = p1.offset(1);
                    *fresh5 = c;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        } else if flipx != 0 {
            p2 = p2.offset(width[0 as std::os::raw::c_int as usize] as isize);
            i = width[0 as std::os::raw::c_int as usize];
            loop  {
                p2 = p2.offset(-1);
                let mut c_0: std::os::raw::c_ushort = *p2;
                k = magx;
                loop  {
                    let fresh6 = p1;
                    p1 = p1.offset(1);
                    *fresh6 = c_0;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        } else {
            i = width[0 as std::os::raw::c_int as usize];
            loop  {
                let fresh7 = p2;
                p2 = p2.offset(1);
                let mut c_1: std::os::raw::c_ushort = *fresh7;
                k = magx;
                loop  {
                    let fresh8 = p1;
                    p1 = p1.offset(1);
                    *fresh8 = c_1;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        }
        if gridy != 0 && magx >= 2 as std::os::raw::c_int {
            p1 = p1_save.offset(-(1 as std::os::raw::c_int as isize));
            i = magx;
            k =
                if flipxy != 0 {
                    height[0 as std::os::raw::c_int as usize]
                } else { width[0 as std::os::raw::c_int as usize] };
            loop  {
                p1 = p1.offset(i as isize);
                *p1 =
                    (*p1 as std::os::raw::c_int ^
                         !(0 as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int))
                        as std::os::raw::c_ushort;
                k -= 1;
                if !(k > 0 as std::os::raw::c_int) { break ; }
            }
        }
        if magy > 1 {
    p1 = p1_save;
    p2 = p1;
    p2step = unsafe { (*ximage[1]).bytes_per_line as usize / std::mem::size_of::<u16>() } as i32;
    i = (width[1] as usize * std::mem::size_of::<u16>()) as i32;
    k = magy - 1;

    while k > 0 {
        p2 = p2.add(p2step as usize);
        unsafe {
            std::ptr::copy_nonoverlapping(p1, p2, i as usize);
        }
        k -= 1;
    }

    if gridx != 0 && magy >= 2 {
        k = width[1];
        while k > 0 {
            let fresh9 = p2;
            p2 = p2.add(1);
            unsafe {
                *fresh9 = (*fresh9 ^ !0) as u16;
            }
            k -= 1;
        }
    }
}
j -= 1;
if j < 0 { break; }

    };
}
#[no_mangle]
pub unsafe extern "C" fn scale32() {
    let mut i: std::os::raw::c_int = 0;
    let mut j: std::os::raw::c_int = 0;
    let mut k: std::os::raw::c_int = 0;
    j =
        if flipxy != 0 {
            (width[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int
        } else { (height[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int };
    loop  {
        let mut p1: *mut std::os::raw::c_uint = 0 as *mut std::os::raw::c_uint;
        let mut p2: *mut std::os::raw::c_uint = 0 as *mut std::os::raw::c_uint;
        let mut p2step: std::os::raw::c_int = 0;
        let mut p1_save: *mut std::os::raw::c_uint = 0 as *mut std::os::raw::c_uint;
        p1 =
            &mut *(**ximage.as_mut_ptr().offset(1 as std::os::raw::c_int as
                                                    isize)).data.offset((((**ximage.as_mut_ptr().offset(1
                                                                                                            as
                                                                                                            std::os::raw::c_int
                                                                                                            as
                                                                                                            isize)).xoffset
                                                                              +
                                                                              0
                                                                                  as
                                                                                  std::os::raw::c_int)
                                                                             as
                                                                             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uint>()
                                                                                                             as
                                                                                                             std::os::raw::c_ulong).wrapping_add((j
                                                                                                                                              *
                                                                                                                                              magy
                                                                                                                                              *
                                                                                                                                              (**ximage.as_mut_ptr().offset(1
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)).bytes_per_line)
                                                                                                                                             as
                                                                                                                                             std::os::raw::c_ulong)
                                                                            as
                                                                            isize)
                as *mut std::os::raw::c_char as *mut std::os::raw::c_uint;
        p1_save = p1;
        p2 =
            &mut *(**ximage.as_mut_ptr().offset(0 as std::os::raw::c_int as
                                                    isize)).data.offset((((**ximage.as_mut_ptr().offset(0
                                                                                                            as
                                                                                                            std::os::raw::c_int
                                                                                                            as
                                                                                                            isize)).xoffset
                                                                              +
                                                                              0
                                                                                  as
                                                                                  std::os::raw::c_int)
                                                                             as
                                                                             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uint>()
                                                                                                             as
                                                                                                             std::os::raw::c_ulong).wrapping_add(((if flipy
                                                                                                                                                  !=
                                                                                                                                                  0
                                                                                                                                              {
                                                                                                                                               (*height.as_mut_ptr().offset(0
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)
                                                                                                                                                    -
                                                                                                                                                    1
                                                                                                                                                        as
                                                                                                                                                        std::os::raw::c_int)
                                                                                                                                                   -
                                                                                                                                                   j
                                                                                                                                           } else {
                                                                                                                                               j
                                                                                                                                           })
                                                                                                                                              *
                                                                                                                                              (**ximage.as_mut_ptr().offset(0
                                                                                                                                                                                as
                                                                                                                                                                                std::os::raw::c_int
                                                                                                                                                                                as
                                                                                                                                                                                isize)).bytes_per_line)
                                                                                                                                             as
                                                                                                                                             std::os::raw::c_ulong)
                                                                            as
                                                                            isize)
                as *mut std::os::raw::c_char as *mut std::os::raw::c_uint;
        if flipxy != 0 {
            p2 =
                &mut *(**ximage.as_mut_ptr().offset(0 as std::os::raw::c_int as
                                                        isize)).data.offset((((**ximage.as_mut_ptr().offset(0
                                                                                                                as
                                                                                                                std::os::raw::c_int
                                                                                                                as
                                                                                                                isize)).xoffset
                                                                                  +
                                                                                  (if flipy
                                                                                          !=
                                                                                          0
                                                                                      {
                                                                                       j
                                                                                   } else {
                                                                                       (*width.as_mut_ptr().offset(0
                                                                                                                       as
                                                                                                                       std::os::raw::c_int
                                                                                                                       as
                                                                                                                       isize)
                                                                                            -
                                                                                            1
                                                                                                as
                                                                                                std::os::raw::c_int)
                                                                                           -
                                                                                           j
                                                                                   }))
                                                                                 as
                                                                                 std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uint>()
                                                                                                                 as
                                                                                                                 std::os::raw::c_ulong).wrapping_add((0
                                                                                                                                                  as
                                                                                                                                                  std::os::raw::c_int
                                                                                                                                                  *
                                                                                                                                                  (**ximage.as_mut_ptr().offset(0
                                                                                                                                                                                    as
                                                                                                                                                                                    std::os::raw::c_int
                                                                                                                                                                                    as
                                                                                                                                                                                    isize)).bytes_per_line)
                                                                                                                                                 as
                                                                                                                                                 std::os::raw::c_ulong)
                                                                                as
                                                                                isize)
                    as *mut std::os::raw::c_char as *mut std::os::raw::c_uint;
            p2step =
                ((*ximage[0 as std::os::raw::c_int as usize]).bytes_per_line as
                     std::os::raw::c_ulong).wrapping_div(::std::mem::size_of::<std::os::raw::c_uint>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            if flipx != 0 {
                p2 =
                    p2.offset((p2step *
                                   (height[0 as std::os::raw::c_int as usize] -
                                        1 as std::os::raw::c_int)) as isize);
                p2step = -p2step
            }
            i = height[0 as std::os::raw::c_int as usize];
            loop  {
                let mut c: std::os::raw::c_uint = *p2;
                p2 = p2.offset(p2step as isize);
                k = magx;
                loop  {
                    let fresh10 = p1;
                    p1 = p1.offset(1);
                    *fresh10 = c;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        } else if flipx != 0 {
            p2 = p2.offset(width[0 as std::os::raw::c_int as usize] as isize);
            i = width[0 as std::os::raw::c_int as usize];
            loop  {
                p2 = p2.offset(-1);
                let mut c_0: std::os::raw::c_uint = *p2;
                k = magx;
                loop  {
                    let fresh11 = p1;
                    p1 = p1.offset(1);
                    *fresh11 = c_0;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        } else {
            i = width[0 as std::os::raw::c_int as usize];
            loop  {
                let fresh12 = p2;
                p2 = p2.offset(1);
                let mut c_1: std::os::raw::c_uint = *fresh12;
                k = magx;
                loop  {
                    let fresh13 = p1;
                    p1 = p1.offset(1);
                    *fresh13 = c_1;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
                i -= 1;
                if !(i > 0 as std::os::raw::c_int) { break ; }
            }
        }
        if gridy != 0 && magx >= 2 as std::os::raw::c_int {
            p1 = p1_save.offset(-(1 as std::os::raw::c_int as isize));
            i = magx;
            k =
                if flipxy != 0 {
                    height[0 as std::os::raw::c_int as usize]
                } else { width[0 as std::os::raw::c_int as usize] };
            loop  {
                p1 = p1.offset(i as isize);
                *p1 ^= !(0 as std::os::raw::c_int as std::os::raw::c_uint);
                k -= 1;
                if !(k > 0 as std::os::raw::c_int) { break ; }
            }
        }
        if magy > 1 {
    let p1_slice = unsafe { std::slice::from_raw_parts(p1_save, (width[1] * magy) as usize) };
    let p2_slice = unsafe { std::slice::from_raw_parts_mut(p1, (width[1] * magy) as usize) };

    let p2step = unsafe { (*ximage[1]).bytes_per_line / std::mem::size_of::<u32>() as i32 } as usize;
    let i = (width[1] * std::mem::size_of::<u32>() as i32) as usize;
    let mut k = magy - 1;

    for _ in 0..k {
        let p2_offset = &mut p2_slice[p2step..p2step + i];
        p2_offset.copy_from_slice(&p1_slice[0..i]);
    }

    if gridx != 0 && magy >= 2 {
        k = width[1];
        for _ in 0..k {
            for p in p2_slice.iter_mut() {
                *p ^= !0;
            }
        }
    }
}
j -= 1;
if j < 0 { break; }

    };
}
#[no_mangle]
pub fn xzoom(buttonpressed: i32) {
    let mut title: [i8; 80] = [0; 80];

    // Accessing mutable static variables requires an unsafe block
    let width_value: u32;
    let height_value: u32;
    let depth_value: u32;

    unsafe {
        width_value = width[0] as u32;
        height_value = height[0] as u32;
        depth_value = depth as u32; // Assuming depth is also a mutable static
    }

    // Safe wrapper around the unsafe XGetSubImage
    let result = unsafe {
        XGetSubImage(
            dpy,
            (*scr).root,
            xgrab,
            ygrab,
            width_value,
            height_value,
            !(0 as i64) as u64,
            2,
            ximage[0],
            0,
            0,
        )
    };

    if depth_value == 8 {
        unsafe { scale8(); }
    } else if depth_value <= (8 * std::mem::size_of::<i16>() as u32) {
        unsafe { scale16(); }
    } else if depth_value <= (8 * std::mem::size_of::<i32>() as u32) {
        unsafe { scale32(); }
    }

    unsafe {
        XPutImage(
            dpy,
            win,
            gc,
            ximage[1],
            0,
            0,
            0,
            0,
            width[1] as u32,
            height[1] as u32,
        );
    }

    if unsafe { set_title != 0 } {
        if unsafe { magx == magy && flipx == 0 && flipy == 0 && flipxy == 0 } {
            unsafe {
                sprintf(
                    title.as_mut_ptr(),
                    b"%s x%d\x00" as *const u8 as *const i8,
                    progname,
                    magx,
                );
            }
        } else {
            unsafe {
                sprintf(
                    title.as_mut_ptr(),
                    b"%s X %s%d%s Y %s%d\x00" as *const u8 as *const i8,
                    progname,
                    if unsafe { flipx != 0 } {
                        b"-\x00" as *const u8 as *const i8
                    } else {
                        b"\x00" as *const u8 as *const i8
                    },
                    magx,
                    if unsafe { flipxy != 0 } {
                        b" <=>\x00" as *const u8 as *const i8
                    } else {
                        b";\x00" as *const u8 as *const i8
                    },
                    if unsafe { flipy != 0 } {
                        b"-\x00" as *const u8 as *const i8
                    } else {
                        b"\x00" as *const u8 as *const i8
                    },
                    magy,
                );
            }
        }

        unsafe {
            XChangeProperty(
                dpy,
                win,
                39,
                31,
                8,
                0,
                title.as_mut_ptr() as *mut u8,
                strlen(title.as_mut_ptr()) as i32,
            );
        }
        unsafe { set_title = 0; }
    }
    unsafe {
        XSync(dpy, 0);
    }
}

unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: *mut *mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut xswa: XSetWindowAttributes =
        XSetWindowAttributes{background_pixmap: 0,
                             background_pixel: 0,
                             border_pixmap: 0,
                             border_pixel: 0,
                             bit_gravity: 0,
                             win_gravity: 0,
                             backing_store: 0,
                             backing_planes: 0,
                             backing_pixel: 0,
                             save_under: 0,
                             event_mask: 0,
                             do_not_propagate_mask: 0,
                             override_redirect: 0,
                             colormap: 0,
                             cursor: 0,};
    let mut event: XEvent = _XEvent{type_0: 0,};
    let mut str: XTextProperty =
        XTextProperty{value: 0 as *mut std::os::raw::c_uchar,
                      encoding: 0,
                      format: 0,
                      nitems: 0,};
    let mut sizeh: *mut XSizeHints = 0 as *mut XSizeHints;
    let mut ch: *mut XClassHint = 0 as *mut XClassHint;
    let mut buttonpressed: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut visible: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut scroll: std::os::raw::c_int = 1 as std::os::raw::c_int;
    let mut title: [std::os::raw::c_char; 80] = [0; 80];
    let mut gcv: XGCValues =
        XGCValues{function: 0,
                  plane_mask: 0,
                  foreground: 0,
                  background: 0,
                  line_width: 0,
                  line_style: 0,
                  cap_style: 0,
                  join_style: 0,
                  fill_style: 0,
                  fill_rule: 0,
                  arc_mode: 0,
                  tile: 0,
                  stipple: 0,
                  ts_x_origin: 0,
                  ts_y_origin: 0,
                  font: 0,
                  subwindow_mode: 0,
                  graphics_exposures: 0,
                  clip_x_origin: 0,
                  clip_y_origin: 0,
                  clip_mask: 0,
                  dash_offset: 0,
                  dashes: 0,};
    let mut dpyname: *mut std::os::raw::c_char = 0 as *mut std::os::raw::c_char;
    let mut source_geom_mask: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut dest_geom_mask: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut copy_from_src_mask: std::os::raw::c_int = 0;
    let mut xpos: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut ypos: std::os::raw::c_int = 0 as std::os::raw::c_int;
    let mut isdock: std::os::raw::c_int = 0 as std::os::raw::c_int;
    atexit(Some(destroy_images as unsafe extern "C" fn() -> ()));
    progname = strrchr(*argv.offset(0 as std::os::raw::c_int as isize), '/' as i32);
    if !progname.is_null() {
        progname = progname.offset(1)
    } else { progname = *argv.offset(0 as std::os::raw::c_int as isize) }
    loop 
         /* parse command line options */
         {
        argc -= 1;
        if !(argc > 0 as std::os::raw::c_int) { break ; }
        argv = argv.offset(1);
        if *(*argv.offset(0 as std::os::raw::c_int as
                              isize)).offset(0 as std::os::raw::c_int as isize) as
               std::os::raw::c_int == '=' as i32 {
            dest_geom_mask =
                XParseGeometry(*argv.offset(0 as std::os::raw::c_int as isize),
                               &mut xpos, &mut ypos,
                               &mut *width.as_mut_ptr().offset(1 as
                                                                   std::os::raw::c_int
                                                                   as isize)
                                   as *mut std::os::raw::c_int as *mut std::os::raw::c_uint,
                               &mut *height.as_mut_ptr().offset(1 as
                                                                    std::os::raw::c_int
                                                                    as isize)
                                   as *mut std::os::raw::c_int as *mut std::os::raw::c_uint)
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-mag\x00" as *const u8 as *const std::os::raw::c_char) == 0
         {
            argv = argv.offset(1);
            argc -= 1;
            magx =
                if argc > 0 as std::os::raw::c_int {
                    atoi(*argv.offset(0 as std::os::raw::c_int as isize))
                } else { -(1 as std::os::raw::c_int) };
            if magx <= 0 as std::os::raw::c_int { Usage(); }
            magy =
                if argc > 1 as std::os::raw::c_int {
                    atoi(*argv.offset(1 as std::os::raw::c_int as isize))
                } else { -(1 as std::os::raw::c_int) };
            if magy <= 0 as std::os::raw::c_int {
                magy = magx
            } else { argv = argv.offset(1); argc -= 1 }
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-x\x00" as *const u8 as *const std::os::raw::c_char) == 0 {
            flipx = 1 as std::os::raw::c_int
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-y\x00" as *const u8 as *const std::os::raw::c_char) == 0 {
            flipy = 1 as std::os::raw::c_int
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-z\x00" as *const u8 as *const std::os::raw::c_char) == 0
                      ||
                      strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                             b"-xy\x00" as *const u8 as *const std::os::raw::c_char)
                          == 0 {
            flipxy = 1 as std::os::raw::c_int
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-source\x00" as *const u8 as *const std::os::raw::c_char)
                      == 0 {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 as std::os::raw::c_int { Usage(); }
            source_geom_mask =
                XParseGeometry(*argv.offset(0 as std::os::raw::c_int as isize),
                               &mut xgrab, &mut ygrab,
                               &mut *width.as_mut_ptr().offset(0 as
                                                                   std::os::raw::c_int
                                                                   as isize)
                                   as *mut std::os::raw::c_int as *mut std::os::raw::c_uint,
                               &mut *height.as_mut_ptr().offset(0 as
                                                                    std::os::raw::c_int
                                                                    as isize)
                                   as *mut std::os::raw::c_int as *mut std::os::raw::c_uint)
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-dest\x00" as *const u8 as *const std::os::raw::c_char) ==
                      0 ||
                      strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                             b"-geometry\x00" as *const u8 as
                                 *const std::os::raw::c_char) == 0 {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 as std::os::raw::c_int { Usage(); }
            dest_geom_mask =
                XParseGeometry(*argv.offset(0 as std::os::raw::c_int as isize),
                               &mut xpos, &mut ypos,
                               &mut *width.as_mut_ptr().offset(1 as
                                                                   std::os::raw::c_int
                                                                   as isize)
                                   as *mut std::os::raw::c_int as *mut std::os::raw::c_uint,
                               &mut *height.as_mut_ptr().offset(1 as
                                                                    std::os::raw::c_int
                                                                    as isize)
                                   as *mut std::os::raw::c_int as *mut std::os::raw::c_uint)
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-d\x00" as *const u8 as *const std::os::raw::c_char) == 0
                      ||
                      strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                             b"-display\x00" as *const u8 as
                                 *const std::os::raw::c_char) == 0 {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 as std::os::raw::c_int { Usage(); }
            dpyname = *argv.offset(0 as std::os::raw::c_int as isize)
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-delay\x00" as *const u8 as *const std::os::raw::c_char) ==
                      0 {
            argv = argv.offset(1);
            argc -= 1;
            if argc < 1 as std::os::raw::c_int { Usage(); }
            if sscanf(*argv.offset(0 as std::os::raw::c_int as isize),
                      b"%u\x00" as *const u8 as *const std::os::raw::c_char,
                      &mut delay as *mut std::os::raw::c_int) != 1 as std::os::raw::c_int {
                Usage();
            }
            delay *= 1000 as std::os::raw::c_int
        } else if strcmp(*argv.offset(0 as std::os::raw::c_int as isize),
                         b"-dock\x00" as *const u8 as *const std::os::raw::c_char) ==
                      0 {
            isdock = 1 as std::os::raw::c_int
        } else { Usage(); }
    }
    dpy = XOpenDisplay(dpyname);
    if dpy.is_null() {
        perror(b"Cannot open display\x00" as *const u8 as
                   *const std::os::raw::c_char);
        exit(-(1 as std::os::raw::c_int));
    }
    /* Now, see if we have to calculate width[DST] and height[DST]
	   from the SRC parameters */
    copy_from_src_mask = 0 as std::os::raw::c_int; /* resize etc.. */
    if source_geom_mask & 0x4 as std::os::raw::c_int != 0 {
        if flipxy != 0 {
            height[1 as std::os::raw::c_int as usize] =
                magy * width[0 as std::os::raw::c_int as usize]; /* commands */
            copy_from_src_mask |= 0x8 as std::os::raw::c_int
        } else {
            width[1 as std::os::raw::c_int as usize] =
                magx * width[0 as std::os::raw::c_int as usize];
            copy_from_src_mask |= 0x4 as std::os::raw::c_int
        }
    }
    if source_geom_mask & 0x8 as std::os::raw::c_int != 0 {
        if flipxy != 0 {
            width[1 as std::os::raw::c_int as usize] =
                magx * height[0 as std::os::raw::c_int as usize];
            copy_from_src_mask |= 0x4 as std::os::raw::c_int
        } else {
            height[1 as std::os::raw::c_int as usize] =
                magy * height[0 as std::os::raw::c_int as usize];
            copy_from_src_mask |= 0x8 as std::os::raw::c_int
        }
    }
    if copy_from_src_mask & dest_geom_mask != 0 {
        fprintf(stderr,
                b"Conflicting dimensions between source and dest geometry\n\x00"
                    as *const u8 as *const std::os::raw::c_char);
        Usage();
    }
    scr =
        &mut *(*(dpy as
                     _XPrivDisplay)).screens.offset((*(dpy as
                                                           _XPrivDisplay)).default_screen
                                                        as isize) as
            *mut Screen;
    depth = (*scr).root_depth as std::os::raw::c_uint;
    if depth < 8 as std::os::raw::c_int as std::os::raw::c_uint {
        fprintf(stderr,
                b"%s: need at least 8 bits/pixel\n\x00" as *const u8 as
                    *const std::os::raw::c_char, progname);
        exit(1 as std::os::raw::c_int);
    }
    if source_geom_mask & 0x10 as std::os::raw::c_int != 0 { xgrab += (*scr).width }
    if source_geom_mask & 0x20 as std::os::raw::c_int != 0 { ygrab += (*scr).height }
    if dest_geom_mask & 0x10 as std::os::raw::c_int != 0 { xpos += (*scr).width }
    if dest_geom_mask & 0x20 as std::os::raw::c_int != 0 { ypos += (*scr).height }
    printf(b"=%dx%d+%d+%d\n\x00" as *const u8 as *const std::os::raw::c_char,
           width[1 as std::os::raw::c_int as usize],
           height[1 as std::os::raw::c_int as usize], xpos, ypos);
    xswa.event_mask =
        (1 as std::os::raw::c_long) << 2 as std::os::raw::c_int |
            (1 as std::os::raw::c_long) << 3 as std::os::raw::c_int |
            (1 as std::os::raw::c_long) << 13 as std::os::raw::c_int;
    xswa.event_mask |= (1 as std::os::raw::c_long) << 17 as std::os::raw::c_int;
    xswa.event_mask |=
        (1 as std::os::raw::c_long) << 0 as std::os::raw::c_int |
            (1 as std::os::raw::c_long) << 1 as std::os::raw::c_int;
    xswa.event_mask |= (1 as std::os::raw::c_long) << 16 as std::os::raw::c_int;
    xswa.background_pixel = (*scr).black_pixel;
    win =
        XCreateWindow(dpy, (*scr).root, xpos, ypos,
                      width[1 as std::os::raw::c_int as usize] as std::os::raw::c_uint,
                      height[1 as std::os::raw::c_int as usize] as std::os::raw::c_uint,
                      0 as std::os::raw::c_int as std::os::raw::c_uint, (*scr).root_depth,
                      1 as std::os::raw::c_int as std::os::raw::c_uint, (*scr).root_visual,
                      ((1 as std::os::raw::c_long) << 11 as std::os::raw::c_int |
                           (1 as std::os::raw::c_long) << 1 as std::os::raw::c_int) as
                          std::os::raw::c_ulong, &mut xswa);
    XChangeProperty(dpy, win, 37 as std::os::raw::c_int as Atom,
                    31 as std::os::raw::c_int as Atom, 8 as std::os::raw::c_int,
                    0 as std::os::raw::c_int, progname as *mut std::os::raw::c_uchar,
                    strlen(progname) as std::os::raw::c_int);
    if isdock == 0 {
        sizeh = XAllocSizeHints();
        (*sizeh).flags =
            (1 as std::os::raw::c_long) << 5 as std::os::raw::c_int |
                (1 as std::os::raw::c_long) << 4 as std::os::raw::c_int;
        (*sizeh).max_width = width[1 as std::os::raw::c_int as usize];
        (*sizeh).min_width = (*sizeh).max_width;
        (*sizeh).max_height = height[1 as std::os::raw::c_int as usize];
        (*sizeh).min_height = (*sizeh).max_height
    }
    XStringListToTextProperty(&mut progname, 1 as std::os::raw::c_int, &mut str);
    ch = XAllocClassHint();
    (*ch).res_class = progname;
    (*ch).res_name = progname;
    XSetWMProperties(dpy, win, &mut str, &mut str,
                     0 as *mut *mut std::os::raw::c_char, 0 as std::os::raw::c_int, sizeh,
                     0 as *mut XWMHints, ch);
    if isdock != 0 {
        wm_windowtype =
            XInternAtom(dpy,
                        b"_NET_WM_WINDOW_TYPE\x00" as *const u8 as
                            *const std::os::raw::c_char, 0 as std::os::raw::c_int);
        wm_dock =
            XInternAtom(dpy,
                        b"_NET_WM_WINDOW_TYPE_DOCK\x00" as *const u8 as
                            *const std::os::raw::c_char, 0 as std::os::raw::c_int);
        XChangeProperty(dpy, win, wm_windowtype, 4 as std::os::raw::c_int as Atom,
                        32 as std::os::raw::c_int, 0 as std::os::raw::c_int,
                        &mut wm_dock as *mut Atom as *mut std::os::raw::c_uchar,
                        1 as std::os::raw::c_int);
    }
    /*
	XChangeProperty(dpy, win, XA_WM_NAME, XA_STRING, 8,
			PropModeReplace,
			(unsigned char *)progname, strlen(progname));
	*/
    /* **	20020213
		code added by <tmancill@debian.org> to handle
		window manager "close" event
	***/
    wm_delete_window =
        XInternAtom(dpy,
                    b"WM_DELETE_WINDOW\x00" as *const u8 as
                        *const std::os::raw::c_char, 0 as std::os::raw::c_int);
    wm_protocols =
        XInternAtom(dpy,
                    b"WM_PROTOCOLS\x00" as *const u8 as *const std::os::raw::c_char,
                    0 as std::os::raw::c_int);
    status =
        XSetWMProtocols(dpy, win, &mut wm_delete_window, 1 as std::os::raw::c_int);
    set_title = 1 as std::os::raw::c_int;
    status = XMapWindow(dpy, win);
    gcv.plane_mask = !(0 as std::os::raw::c_long) as std::os::raw::c_ulong;
    gcv.subwindow_mode = 1 as std::os::raw::c_int;
    gcv.function = 0x3 as std::os::raw::c_int;
    gcv.foreground = (*scr).white_pixel;
    gcv.background = (*scr).black_pixel;
    gc =
        XCreateGC(dpy, (*scr).root,
                  ((1 as std::os::raw::c_long) << 0 as std::os::raw::c_int |
                       (1 as std::os::raw::c_long) << 1 as std::os::raw::c_int |
                       (1 as std::os::raw::c_long) << 15 as std::os::raw::c_int |
                       (1 as std::os::raw::c_long) << 2 as std::os::raw::c_int |
                       (1 as std::os::raw::c_long) << 3 as std::os::raw::c_int) as
                      std::os::raw::c_ulong, &mut gcv);
    let width_1 = width[1];
let height_1 = height[1];
resize(width_1, height_1);
    when_button = XCreateFontCursor(dpy, 144 as std::os::raw::c_int as std::os::raw::c_uint);
    crosshair = XCreateFontCursor(dpy, 34 as std::os::raw::c_int as std::os::raw::c_uint);
    XDefineCursor(dpy, win, crosshair);
    loop  {
        /* ****
		old event loop updated to support WM messages
		while(unmapped?
			(XWindowEvent(dpy, win, (long)-1, &event), 1):
			XCheckWindowEvent(dpy, win, (long)-1, &event)) {
		******/
        while XPending(dpy) != 0 {
                XNextEvent(dpy, &mut event);
    match event.type_0 {
        33 => {
            if event.xclient.message_type == wm_protocols &&
               event.xclient.data.l[0] as u64 == wm_delete_window {
                std::process::exit(0);
            }
        }
        22 => {
            if event.xconfigure.width != width[1] ||
               event.xconfigure.height != height[1] {
                resize(event.xconfigure.width, event.xconfigure.height);
            }
        }
        15 => {
            /* VisibilityUnobscured, VisibilityPartiallyObscured, or VisibilityFullyObscured */
            visible = (event.xvisibility.state != 2) as i32;
        }
        3 => {
            match XKeycodeToKeysym(dpy, event.xkey.keycode as KeyCode, 0) {
                65507 | 65508 => { scroll = 1; }
                _ => {}
            }
        }
        2 => {
             match XKeycodeToKeysym(dpy, event.xkey.keycode as KeyCode, 0) {
    65507 | 65508 => { scroll = 10 }
    43 | 61 | 65451 => {
        if yzoom_flag == 0 { magx += 1 }
        if xzoom_flag == 0 { magy += 1 }
        yzoom_flag = 0;
        xzoom_flag = yzoom_flag;
        resize(width[1], height[1]);
        set_title = 1;
    }
    45 | 65453 => {
        if yzoom_flag == 0 { magx -= 1 }
        if xzoom_flag == 0 { magy -= 1 }
        yzoom_flag = 0;
        xzoom_flag = yzoom_flag;
        if magx < 1 { magx = 1 }
        if magy < 1 { magy = 1 }
        resize(width[1], height[1]);
        set_title = 1;
    }
    65361 | 65430 => {
        if flipxy != 0 {
            if flipx != 0 {
                ygrab += scroll;
            } else {
                ygrab -= scroll;
            }
        } else if flipx != 0 {
            xgrab += scroll;
        } else {
            xgrab -= scroll;
        }
    }
    65363 | 65432 => {
        if flipxy != 0 {
            if flipx != 0 {
                ygrab -= scroll;
            } else {
                ygrab += scroll;
            }
        } else if flipx != 0 {
            xgrab -= scroll;
        } else {
            xgrab += scroll;
        }
    }
    65362 | 65431 => {
        if flipxy != 0 {
            if flipy != 0 {
                xgrab -= scroll;
            } else {
                xgrab += scroll;
            }
        } else if flipy != 0 {
            ygrab += scroll;
        } else {
            ygrab -= scroll;
        }
    }
    65364 | 65433 => {
        if flipxy != 0 {
            if flipy != 0 {
                xgrab += scroll;
            } else {
                xgrab -= scroll;
            }
        } else if flipy != 0 {
            ygrab -= scroll;
        } else {
            ygrab += scroll;
        }
    }
    120 => {
        flipx = (flipx == 0) as i32;
        set_title = 1;
    }
    121 => {
        flipy = (flipy == 0) as i32;
        set_title = 1;
    }
    122 => {
        if flipx ^ flipy ^ flipxy != 0 {
            flipx = (flipx == 0) as i32;
            flipy = (flipy == 0) as i32;
        }
        flipxy = (flipxy == 0) as i32;
        resize(width[1], height[1]);
        set_title = 1;
    }
    119 => {
        xzoom_flag = 1;
        yzoom_flag = 0;
    }
    104 => {
        yzoom_flag = 1;
        xzoom_flag = 0;
    }
    103 => {
        gridx = (gridx == 0) as i32;
        gridy = (gridy == 0) as i32;
    }
    100 => {
        delay_index += 1;
        if delay_index >= 5 { delay_index = 0 }
        delay = delays[delay_index as usize];
        let formatted_title = format!("delay = {} ms", delay / 1000);
        let bytes = formatted_title.as_bytes();
        let len = bytes.len().min(79); // Ensure we don't exceed the array size
        for i in 0..len {
            title[i] = bytes[i] as i8; // Convert u8 to i8
        }
        title[len] = 0; // Null-terminate the string
        XChangeProperty(dpy, win, 39, 31, 8, 0, title.as_ptr() as *mut u8, title.len() as i32);
        signal(14, Some(timeout_func));
        alarm(2);
    }
    113 => { std::process::exit(0); }
    _ => {}
}


        }
        4 => {
            xgrab = event.xbutton.x_root;
            ygrab = event.xbutton.y_root;
            XDefineCursor(dpy, win, when_button);
            buttonpressed = 1;
        }
        5 => {
            /*
            xgrab = event.xbutton.x_root - width[SRC]/2;
            ygrab = event.xbutton.y_root - height[SRC]/2;
            */
            XDefineCursor(dpy, win, crosshair);
            buttonpressed = 0;
        }
        6 => {
            if buttonpressed != 0 {
                xgrab = event.xmotion.x_root;
                ygrab = event.xmotion.y_root;
            }
        }
        21 | _ => {}
    }
    /* trying XShmGetImage when part of the rect is
       not on the screen will fail LOUDLY..
       we have to verify this after anything that may
       modified xgrab or ygrab or the size of
       the source ximage */
    if xgrab < 0 { xgrab = 0; }
    if xgrab > unsafe { (*scr).width } - width[0] {
        xgrab = unsafe { (*scr).width } - width[0];
    }
    if ygrab < 0 { ygrab = 0; }
    if ygrab > unsafe { (*scr).height } - height[0] {
        ygrab = unsafe { (*scr).height } - height[0];
    }
    /*
    The variables live at this point are:
    (mut event: _XEvent, mut buttonpressed: i32, mut visible: i32, mut scroll: i32, mut title: [i8; 80])
    */

        }
        if visible != 0 { xzoom(buttonpressed); }
        if buttonpressed == 0 && delay > 0 as std::os::raw::c_int {
            usleep(delay as __useconds_t);
        }
    };
}
pub fn main() {
    let args: Vec<String> = ::std::env::args().collect();
    let argc = args.len() as std::os::raw::c_int;
    let mut argv: Vec<*mut std::os::raw::c_char> = args.iter()
        .map(|arg| CString::new(arg.clone()).expect("Failed to convert argument into CString").into_raw())
        .collect();
    
    // Push a null pointer to the end of argv
    argv.push(std::ptr::null_mut());

    // Call the main_0 function with the arguments
    process::exit(unsafe { main_0(argc, argv.as_mut_ptr()) } as i32);
}

