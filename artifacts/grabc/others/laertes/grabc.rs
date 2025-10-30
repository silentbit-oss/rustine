#![feature(core_intrinsics)]
#![register_tool(c2rust)]
#![feature( extern_types,  register_tool)]
#![feature(const_mut_refs, const_fn_fn_ptr_basics)]
#![feature(c_variadic)]


extern "C" {
    pub type _XGC;
    pub type _XDisplay;
    pub type _XPrivate;
    pub type _XrmHashBucketRec;
    #[no_mangle]
    static mut stdout: * mut crate::_IO_FILE;
    #[no_mangle]
    static mut stderr: * mut crate::_IO_FILE;
    #[no_mangle]
    fn fflush(__stream: * mut crate::_IO_FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fprintf(_: * mut crate::_IO_FILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn exit(_: std::os::raw::c_int) -> !;
    #[no_mangle]
    fn strncmp(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char,
               _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XGetImage(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_int, _: std::os::raw::c_int,
                 _: std::os::raw::c_uint, _: std::os::raw::c_uint, _: std::os::raw::c_ulong,
                 _: std::os::raw::c_int) -> * mut crate::_XImage;
    #[no_mangle]
    fn XOpenDisplay(_: * const std::os::raw::c_char) -> * mut crate::_XDisplay;
    #[no_mangle]
    fn XCreateFontCursor(_: * mut crate::_XDisplay, _: std::os::raw::c_uint) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn XRootWindow(_: * mut crate::_XDisplay, _: std::os::raw::c_int) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn XSetErrorHandler(_: Option<unsafe extern "C"  fn(_: * mut crate::_XDisplay,_: * mut crate::XErrorEvent,) -> std::os::raw::c_int>) -> Option<unsafe extern "C"  fn(_: * mut crate::_XDisplay,_: * mut crate::XErrorEvent,) -> std::os::raw::c_int>;
    #[no_mangle]
    fn XAllowEvents(_: * mut crate::_XDisplay, _: std::os::raw::c_int, _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XDefaultScreen(_: * mut crate::_XDisplay) -> std::os::raw::c_int;
    #[no_mangle]
    fn XFreeCursor(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XGrabPointer(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_int,
                    _: std::os::raw::c_uint, _: std::os::raw::c_int, _: std::os::raw::c_int,
                    _: std::os::raw::c_ulong, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XQueryColor(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: * mut crate::XColor)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn XTranslateCoordinates(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
                             _: std::os::raw::c_int, _: std::os::raw::c_int,
                             _: * mut std::os::raw::c_int, _: * mut std::os::raw::c_int,
                             _: * mut std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XUngrabPointer(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XWindowEvent(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_long,
                    _: * mut crate::_XEvent) -> std::os::raw::c_int;
}
pub type size_t = std::os::raw::c_ulong;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: std::os::raw::c_int,
    pub _IO_read_ptr: * mut std::os::raw::c_char,
    pub _IO_read_end: * mut std::os::raw::c_char,
    pub _IO_read_base: * mut std::os::raw::c_char,
    pub _IO_write_base: * mut std::os::raw::c_char,
    pub _IO_write_ptr: * mut std::os::raw::c_char,
    pub _IO_write_end: * mut std::os::raw::c_char,
    pub _IO_buf_base: * mut std::os::raw::c_char,
    pub _IO_buf_end: * mut std::os::raw::c_char,
    pub _IO_save_base: * mut std::os::raw::c_char,
    pub _IO_backup_base: * mut std::os::raw::c_char,
    pub _IO_save_end: * mut std::os::raw::c_char,
    pub _markers: * mut crate::_IO_marker,
    pub _chain: * mut crate::_IO_FILE,
    pub _fileno: std::os::raw::c_int,
    pub _flags2: std::os::raw::c_int,
    pub _old_offset: std::os::raw::c_long,
    pub _cur_column: std::os::raw::c_ushort,
    pub _vtable_offset: std::os::raw::c_schar,
    pub _shortbuf: [std::os::raw::c_char; 1],
    pub _lock: * mut core::ffi::c_void,
    pub _offset: std::os::raw::c_long,
    pub __pad1: * mut core::ffi::c_void,
    pub __pad2: * mut core::ffi::c_void,
    pub __pad3: * mut core::ffi::c_void,
    pub __pad4: * mut core::ffi::c_void,
    pub __pad5: std::os::raw::c_ulong,
    pub _mode: std::os::raw::c_int,
    pub _unused2: [std::os::raw::c_char; 20],
}
impl _IO_FILE {
    pub const fn new() -> Self {
        _IO_FILE {
        _flags: 0,
        _IO_read_ptr: (0 as * mut std::os::raw::c_char),
        _IO_read_end: (0 as * mut std::os::raw::c_char),
        _IO_read_base: (0 as * mut std::os::raw::c_char),
        _IO_write_base: (0 as * mut std::os::raw::c_char),
        _IO_write_ptr: (0 as * mut std::os::raw::c_char),
        _IO_write_end: (0 as * mut std::os::raw::c_char),
        _IO_buf_base: (0 as * mut std::os::raw::c_char),
        _IO_buf_end: (0 as * mut std::os::raw::c_char),
        _IO_save_base: (0 as * mut std::os::raw::c_char),
        _IO_backup_base: (0 as * mut std::os::raw::c_char),
        _IO_save_end: (0 as * mut std::os::raw::c_char),
        _markers: (0 as * mut crate::_IO_marker),
        _chain: (0 as * mut crate::_IO_FILE),
        _fileno: 0,
        _flags2: 0,
        _old_offset: 0,
        _cur_column: 0,
        _vtable_offset: 0,
        _shortbuf: [0,],
        _lock: (0 as * mut core::ffi::c_void),
        _offset: 0,
        __pad1: (0 as * mut core::ffi::c_void),
        __pad2: (0 as * mut core::ffi::c_void),
        __pad3: (0 as * mut core::ffi::c_void),
        __pad4: (0 as * mut core::ffi::c_void),
        __pad5: 0,
        _mode: 0,
        _unused2: [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,]
        }
    }
}

impl std::default::Default for _IO_FILE {
    fn default() -> Self { _IO_FILE::new() }
}

pub type _IO_lock_t = ();
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_marker {
    pub _next: * mut crate::_IO_marker,
    pub _sbuf: * mut crate::_IO_FILE,
    pub _pos: std::os::raw::c_int,
}
impl _IO_marker {
    pub const fn new() -> Self {
        _IO_marker {
        _next: (0 as * mut crate::_IO_marker),
        _sbuf: (0 as * mut crate::_IO_FILE),
        _pos: 0
        }
    }
}

impl std::default::Default for _IO_marker {
    fn default() -> Self { _IO_marker::new() }
}

pub type FILE = crate::_IO_FILE;
pub type XID = std::os::raw::c_ulong;
pub type Atom = std::os::raw::c_ulong;
pub type VisualID = std::os::raw::c_ulong;
pub type Time = std::os::raw::c_ulong;
pub type Window = std::os::raw::c_ulong;
pub type Drawable = std::os::raw::c_ulong;
pub type Cursor = std::os::raw::c_ulong;
pub type Colormap = std::os::raw::c_ulong;
pub type XPointer = * mut std::os::raw::c_char;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _XExtData {
    pub number: std::os::raw::c_int,
    pub next: * mut crate::_XExtData,
    pub free_private: Option<unsafe extern "C"  fn(_: * mut crate::_XExtData,) -> std::os::raw::c_int>,
    pub private_data: * mut std::os::raw::c_char,
}
impl _XExtData {
    pub const fn new() -> Self {
        _XExtData {
        number: 0,
        next: (0 as * mut crate::_XExtData),
        free_private: None,
        private_data: (0 as * mut std::os::raw::c_char)
        }
    }
}

impl std::default::Default for _XExtData {
    fn default() -> Self { _XExtData::new() }
}

pub type XExtData = crate::_XExtData;
pub type GC = * mut crate::_XGC;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Visual {
    pub ext_data: * mut crate::_XExtData,
    pub visualid: std::os::raw::c_ulong,
    pub class: std::os::raw::c_int,
    pub red_mask: std::os::raw::c_ulong,
    pub green_mask: std::os::raw::c_ulong,
    pub blue_mask: std::os::raw::c_ulong,
    pub bits_per_rgb: std::os::raw::c_int,
    pub map_entries: std::os::raw::c_int,
}
impl Visual {
    pub const fn new() -> Self {
        Visual {
        ext_data: (0 as * mut crate::_XExtData),
        visualid: 0,
        class: 0,
        red_mask: 0,
        green_mask: 0,
        blue_mask: 0,
        bits_per_rgb: 0,
        map_entries: 0
        }
    }
}

impl std::default::Default for Visual {
    fn default() -> Self { Visual::new() }
}

// #[derive(Copy, Clone)]
#[repr(C)]
pub struct Depth<'a> {
    pub depth: std::os::raw::c_int,
    pub nvisuals: std::os::raw::c_int,
    pub visuals: Option<&'a mut crate::Visual>,
}
impl<'a> Depth<'a> {
    pub const fn new() -> Self {
        Depth {
        depth: 0,
        nvisuals: 0,
        visuals: None
        }
    }
}

impl<'a> std::default::Default for Depth<'a> {
    fn default() -> Self { Depth::new() }
}

// #[derive(Copy, Clone)]
#[repr(C)]
pub struct Screen<'a> {
    pub ext_data: Option<&'a mut crate::_XExtData>,
    pub display: Option<&'a mut crate::_XDisplay>,
    pub root: std::os::raw::c_ulong,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub mwidth: std::os::raw::c_int,
    pub mheight: std::os::raw::c_int,
    pub ndepths: std::os::raw::c_int,
    pub depths: Option<&'a mut crate::Depth<'a>>,
    pub root_depth: std::os::raw::c_int,
    pub root_visual: Option<&'a mut crate::Visual>,
    pub default_gc: Option<&'a mut crate::_XGC>,
    pub cmap: std::os::raw::c_ulong,
    pub white_pixel: std::os::raw::c_ulong,
    pub black_pixel: std::os::raw::c_ulong,
    pub max_maps: std::os::raw::c_int,
    pub min_maps: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub save_unders: std::os::raw::c_int,
    pub root_input_mask: std::os::raw::c_long,
}
impl<'a> Screen<'a> {
    pub const fn new() -> Self {
        Screen {
        ext_data: None,
        display: None,
        root: 0,
        width: 0,
        height: 0,
        mwidth: 0,
        mheight: 0,
        ndepths: 0,
        depths: None,
        root_depth: 0,
        root_visual: None,
        default_gc: None,
        cmap: 0,
        white_pixel: 0,
        black_pixel: 0,
        max_maps: 0,
        min_maps: 0,
        backing_store: 0,
        save_unders: 0,
        root_input_mask: 0
        }
    }
}

impl<'a> std::default::Default for Screen<'a> {
    fn default() -> Self { Screen::new() }
}

// #[derive(Copy, Clone)]
#[repr(C)]
pub struct ScreenFormat<'a> {
    pub ext_data: Option<&'a mut crate::_XExtData>,
    pub depth: std::os::raw::c_int,
    pub bits_per_pixel: std::os::raw::c_int,
    pub scanline_pad: std::os::raw::c_int,
}
impl<'a> ScreenFormat<'a> {
    pub const fn new() -> Self {
        ScreenFormat {
        ext_data: None,
        depth: 0,
        bits_per_pixel: 0,
        scanline_pad: 0
        }
    }
}

impl<'a> std::default::Default for ScreenFormat<'a> {
    fn default() -> Self { ScreenFormat::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct _XImage {
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub xoffset: std::os::raw::c_int,
    pub format: std::os::raw::c_int,
    pub data: * mut std::os::raw::c_char,
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
    pub obdata: * mut std::os::raw::c_char,
    pub f: crate::funcs,
}
impl _XImage {
    pub const fn new() -> Self {
        _XImage {
        width: 0,
        height: 0,
        xoffset: 0,
        format: 0,
        data: (0 as * mut std::os::raw::c_char),
        byte_order: 0,
        bitmap_unit: 0,
        bitmap_bit_order: 0,
        bitmap_pad: 0,
        depth: 0,
        bytes_per_line: 0,
        bits_per_pixel: 0,
        red_mask: 0,
        green_mask: 0,
        blue_mask: 0,
        obdata: (0 as * mut std::os::raw::c_char),
        f: crate::funcs::new()
        }
    }
}

impl std::default::Default for _XImage {
    fn default() -> Self { _XImage::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct funcs {
    pub create_image: Option<unsafe extern "C"  fn(_: * mut crate::_XDisplay,_: * mut crate::Visual,_: std::os::raw::c_uint,_: std::os::raw::c_int,_: std::os::raw::c_int,_: * mut std::os::raw::c_char,_: std::os::raw::c_uint,_: std::os::raw::c_uint,_: std::os::raw::c_int,_: std::os::raw::c_int,) -> * mut crate::_XImage>,
    pub destroy_image: Option<unsafe extern "C"  fn(_: * mut crate::_XImage,) -> std::os::raw::c_int>,
    pub get_pixel: Option<unsafe extern "C"  fn(_: * mut crate::_XImage,_: std::os::raw::c_int,_: std::os::raw::c_int,) -> std::os::raw::c_ulong>,
    pub put_pixel: Option<unsafe extern "C"  fn(_: * mut crate::_XImage,_: std::os::raw::c_int,_: std::os::raw::c_int,_: std::os::raw::c_ulong,) -> std::os::raw::c_int>,
    pub sub_image: Option<unsafe extern "C"  fn(_: * mut crate::_XImage,_: std::os::raw::c_int,_: std::os::raw::c_int,_: std::os::raw::c_uint,_: std::os::raw::c_uint,) -> * mut crate::_XImage>,
    pub add_pixel: Option<unsafe extern "C"  fn(_: * mut crate::_XImage,_: std::os::raw::c_long,) -> std::os::raw::c_int>,
}
impl funcs {
    pub const fn new() -> Self {
        funcs {
        create_image: None,
        destroy_image: None,
        get_pixel: None,
        put_pixel: None,
        sub_image: None,
        add_pixel: None
        }
    }
}

impl std::default::Default for funcs {
    fn default() -> Self { funcs::new() }
}

pub type XImage = crate::_XImage;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XColor {
    pub pixel: std::os::raw::c_ulong,
    pub red: std::os::raw::c_ushort,
    pub green: std::os::raw::c_ushort,
    pub blue: std::os::raw::c_ushort,
    pub flags: std::os::raw::c_char,
    pub pad: std::os::raw::c_char,
}
impl XColor {
    pub const fn new() -> Self {
        XColor {
        pixel: 0,
        red: 0,
        green: 0,
        blue: 0,
        flags: 0,
        pad: 0
        }
    }
}

impl std::default::Default for XColor {
    fn default() -> Self { XColor::new() }
}

pub type Display = crate::_XDisplay;
// #[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed<'a> {
    pub ext_data: Option<&'a mut crate::_XExtData>,
    pub private1: Option<&'a mut crate::_XPrivate>,
    pub fd: std::os::raw::c_int,
    pub private2: std::os::raw::c_int,
    pub proto_major_version: std::os::raw::c_int,
    pub proto_minor_version: std::os::raw::c_int,
    pub vendor: Option<&'a mut std::os::raw::c_char>,
    pub private3: std::os::raw::c_ulong,
    pub private4: std::os::raw::c_ulong,
    pub private5: std::os::raw::c_ulong,
    pub private6: std::os::raw::c_int,
    pub resource_alloc: Option<unsafe extern "C"  fn(_: * mut crate::_XDisplay,) -> std::os::raw::c_ulong>,
    pub byte_order: std::os::raw::c_int,
    pub bitmap_unit: std::os::raw::c_int,
    pub bitmap_pad: std::os::raw::c_int,
    pub bitmap_bit_order: std::os::raw::c_int,
    pub nformats: std::os::raw::c_int,
    pub pixmap_format: Option<&'a mut crate::ScreenFormat<'a>>,
    pub private8: std::os::raw::c_int,
    pub release: std::os::raw::c_int,
    pub private9: Option<&'a mut crate::_XPrivate>,
    pub private10: Option<&'a mut crate::_XPrivate>,
    pub qlen: std::os::raw::c_int,
    pub last_request_read: std::os::raw::c_ulong,
    pub request: std::os::raw::c_ulong,
    pub private11: Option<&'a mut std::os::raw::c_char>,
    pub private12: Option<&'a mut std::os::raw::c_char>,
    pub private13: Option<&'a mut std::os::raw::c_char>,
    pub private14: Option<&'a mut std::os::raw::c_char>,
    pub max_request_size: std::os::raw::c_uint,
    pub db: Option<&'a mut crate::_XrmHashBucketRec>,
    pub private15: Option<unsafe extern "C"  fn(_: * mut crate::_XDisplay,) -> std::os::raw::c_int>,
    pub display_name: Option<&'a mut std::os::raw::c_char>,
    pub default_screen: std::os::raw::c_int,
    pub nscreens: std::os::raw::c_int,
    pub screens: * mut crate::Screen<'a>,
    pub motion_buffer: std::os::raw::c_ulong,
    pub private16: std::os::raw::c_ulong,
    pub min_keycode: std::os::raw::c_int,
    pub max_keycode: std::os::raw::c_int,
    pub private17: Option<&'a mut std::os::raw::c_char>,
    pub private18: Option<&'a mut std::os::raw::c_char>,
    pub private19: std::os::raw::c_int,
    pub xdefaults: Option<&'a mut std::os::raw::c_char>,
}
impl<'a> C2RustUnnamed<'a> {
    pub const fn new() -> Self {
        C2RustUnnamed {
        ext_data: None,
        private1: None,
        fd: 0,
        private2: 0,
        proto_major_version: 0,
        proto_minor_version: 0,
        vendor: None,
        private3: 0,
        private4: 0,
        private5: 0,
        private6: 0,
        resource_alloc: None,
        byte_order: 0,
        bitmap_unit: 0,
        bitmap_pad: 0,
        bitmap_bit_order: 0,
        nformats: 0,
        pixmap_format: None,
        private8: 0,
        release: 0,
        private9: None,
        private10: None,
        qlen: 0,
        last_request_read: 0,
        request: 0,
        private11: None,
        private12: None,
        private13: None,
        private14: None,
        max_request_size: 0,
        db: None,
        private15: None,
        display_name: None,
        default_screen: 0,
        nscreens: 0,
        screens: (0 as * mut crate::Screen<'a>),
        motion_buffer: 0,
        private16: 0,
        min_keycode: 0,
        max_keycode: 0,
        private17: None,
        private18: None,
        private19: 0,
        xdefaults: None
        }
    }
}

impl<'a> std::default::Default for C2RustUnnamed<'a> {
    fn default() -> Self { C2RustUnnamed::new() }
}

pub type _XPrivDisplay<'a> = * mut crate::C2RustUnnamed<'a>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XKeyEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub root: std::os::raw::c_ulong,
    pub subwindow: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub keycode: std::os::raw::c_uint,
    pub same_screen: std::os::raw::c_int,
}
impl XKeyEvent {
    pub const fn new() -> Self {
        XKeyEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        root: 0,
        subwindow: 0,
        time: 0,
        x: 0,
        y: 0,
        x_root: 0,
        y_root: 0,
        state: 0,
        keycode: 0,
        same_screen: 0
        }
    }
}

impl std::default::Default for XKeyEvent {
    fn default() -> Self { XKeyEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XButtonEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub root: std::os::raw::c_ulong,
    pub subwindow: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub button: std::os::raw::c_uint,
    pub same_screen: std::os::raw::c_int,
}
impl XButtonEvent {
    pub const fn new() -> Self {
        XButtonEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
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
        same_screen: 0
        }
    }
}

impl std::default::Default for XButtonEvent {
    fn default() -> Self { XButtonEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMotionEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub root: std::os::raw::c_ulong,
    pub subwindow: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub x_root: std::os::raw::c_int,
    pub y_root: std::os::raw::c_int,
    pub state: std::os::raw::c_uint,
    pub is_hint: std::os::raw::c_char,
    pub same_screen: std::os::raw::c_int,
}
impl XMotionEvent {
    pub const fn new() -> Self {
        XMotionEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        root: 0,
        subwindow: 0,
        time: 0,
        x: 0,
        y: 0,
        x_root: 0,
        y_root: 0,
        state: 0,
        is_hint: 0,
        same_screen: 0
        }
    }
}

impl std::default::Default for XMotionEvent {
    fn default() -> Self { XMotionEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCrossingEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub root: std::os::raw::c_ulong,
    pub subwindow: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
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
impl XCrossingEvent {
    pub const fn new() -> Self {
        XCrossingEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        root: 0,
        subwindow: 0,
        time: 0,
        x: 0,
        y: 0,
        x_root: 0,
        y_root: 0,
        mode: 0,
        detail: 0,
        same_screen: 0,
        focus: 0,
        state: 0
        }
    }
}

impl std::default::Default for XCrossingEvent {
    fn default() -> Self { XCrossingEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XFocusChangeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub mode: std::os::raw::c_int,
    pub detail: std::os::raw::c_int,
}
impl XFocusChangeEvent {
    pub const fn new() -> Self {
        XFocusChangeEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        mode: 0,
        detail: 0
        }
    }
}

impl std::default::Default for XFocusChangeEvent {
    fn default() -> Self { XFocusChangeEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XKeymapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub key_vector: [std::os::raw::c_char; 32],
}
impl XKeymapEvent {
    pub const fn new() -> Self {
        XKeymapEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        key_vector: [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,]
        }
    }
}

impl std::default::Default for XKeymapEvent {
    fn default() -> Self { XKeymapEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XExposeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
}
impl XExposeEvent {
    pub const fn new() -> Self {
        XExposeEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        count: 0
        }
    }
}

impl std::default::Default for XExposeEvent {
    fn default() -> Self { XExposeEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGraphicsExposeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub drawable: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
    pub major_code: std::os::raw::c_int,
    pub minor_code: std::os::raw::c_int,
}
impl XGraphicsExposeEvent {
    pub const fn new() -> Self {
        XGraphicsExposeEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        drawable: 0,
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        count: 0,
        major_code: 0,
        minor_code: 0
        }
    }
}

impl std::default::Default for XGraphicsExposeEvent {
    fn default() -> Self { XGraphicsExposeEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XNoExposeEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub drawable: std::os::raw::c_ulong,
    pub major_code: std::os::raw::c_int,
    pub minor_code: std::os::raw::c_int,
}
impl XNoExposeEvent {
    pub const fn new() -> Self {
        XNoExposeEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        drawable: 0,
        major_code: 0,
        minor_code: 0
        }
    }
}

impl std::default::Default for XNoExposeEvent {
    fn default() -> Self { XNoExposeEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XVisibilityEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub state: std::os::raw::c_int,
}
impl XVisibilityEvent {
    pub const fn new() -> Self {
        XVisibilityEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        state: 0
        }
    }
}

impl std::default::Default for XVisibilityEvent {
    fn default() -> Self { XVisibilityEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCreateWindowEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub parent: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub override_redirect: std::os::raw::c_int,
}
impl XCreateWindowEvent {
    pub const fn new() -> Self {
        XCreateWindowEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        parent: 0,
        window: 0,
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        border_width: 0,
        override_redirect: 0
        }
    }
}

impl std::default::Default for XCreateWindowEvent {
    fn default() -> Self { XCreateWindowEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XDestroyWindowEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
}
impl XDestroyWindowEvent {
    pub const fn new() -> Self {
        XDestroyWindowEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0
        }
    }
}

impl std::default::Default for XDestroyWindowEvent {
    fn default() -> Self { XDestroyWindowEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XUnmapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub from_configure: std::os::raw::c_int,
}
impl XUnmapEvent {
    pub const fn new() -> Self {
        XUnmapEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0,
        from_configure: 0
        }
    }
}

impl std::default::Default for XUnmapEvent {
    fn default() -> Self { XUnmapEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub override_redirect: std::os::raw::c_int,
}
impl XMapEvent {
    pub const fn new() -> Self {
        XMapEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0,
        override_redirect: 0
        }
    }
}

impl std::default::Default for XMapEvent {
    fn default() -> Self { XMapEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMapRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub parent: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
}
impl XMapRequestEvent {
    pub const fn new() -> Self {
        XMapRequestEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        parent: 0,
        window: 0
        }
    }
}

impl std::default::Default for XMapRequestEvent {
    fn default() -> Self { XMapRequestEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XReparentEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub parent: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub override_redirect: std::os::raw::c_int,
}
impl XReparentEvent {
    pub const fn new() -> Self {
        XReparentEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0,
        parent: 0,
        x: 0,
        y: 0,
        override_redirect: 0
        }
    }
}

impl std::default::Default for XReparentEvent {
    fn default() -> Self { XReparentEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XConfigureEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub above: std::os::raw::c_ulong,
    pub override_redirect: std::os::raw::c_int,
}
impl XConfigureEvent {
    pub const fn new() -> Self {
        XConfigureEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0,
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        border_width: 0,
        above: 0,
        override_redirect: 0
        }
    }
}

impl std::default::Default for XConfigureEvent {
    fn default() -> Self { XConfigureEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGravityEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
}
impl XGravityEvent {
    pub const fn new() -> Self {
        XGravityEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0,
        x: 0,
        y: 0
        }
    }
}

impl std::default::Default for XGravityEvent {
    fn default() -> Self { XGravityEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XResizeRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
}
impl XResizeRequestEvent {
    pub const fn new() -> Self {
        XResizeRequestEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        width: 0,
        height: 0
        }
    }
}

impl std::default::Default for XResizeRequestEvent {
    fn default() -> Self { XResizeRequestEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XConfigureRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub parent: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub border_width: std::os::raw::c_int,
    pub above: std::os::raw::c_ulong,
    pub detail: std::os::raw::c_int,
    pub value_mask: std::os::raw::c_ulong,
}
impl XConfigureRequestEvent {
    pub const fn new() -> Self {
        XConfigureRequestEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        parent: 0,
        window: 0,
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        border_width: 0,
        above: 0,
        detail: 0,
        value_mask: 0
        }
    }
}

impl std::default::Default for XConfigureRequestEvent {
    fn default() -> Self { XConfigureRequestEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCirculateEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub event: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub place: std::os::raw::c_int,
}
impl XCirculateEvent {
    pub const fn new() -> Self {
        XCirculateEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        event: 0,
        window: 0,
        place: 0
        }
    }
}

impl std::default::Default for XCirculateEvent {
    fn default() -> Self { XCirculateEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCirculateRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub parent: std::os::raw::c_ulong,
    pub window: std::os::raw::c_ulong,
    pub place: std::os::raw::c_int,
}
impl XCirculateRequestEvent {
    pub const fn new() -> Self {
        XCirculateRequestEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        parent: 0,
        window: 0,
        place: 0
        }
    }
}

impl std::default::Default for XCirculateRequestEvent {
    fn default() -> Self { XCirculateRequestEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XPropertyEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub atom: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
    pub state: std::os::raw::c_int,
}
impl XPropertyEvent {
    pub const fn new() -> Self {
        XPropertyEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        atom: 0,
        time: 0,
        state: 0
        }
    }
}

impl std::default::Default for XPropertyEvent {
    fn default() -> Self { XPropertyEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionClearEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub selection: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
}
impl XSelectionClearEvent {
    pub const fn new() -> Self {
        XSelectionClearEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        selection: 0,
        time: 0
        }
    }
}

impl std::default::Default for XSelectionClearEvent {
    fn default() -> Self { XSelectionClearEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionRequestEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub owner: std::os::raw::c_ulong,
    pub requestor: std::os::raw::c_ulong,
    pub selection: std::os::raw::c_ulong,
    pub target: std::os::raw::c_ulong,
    pub property: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
}
impl XSelectionRequestEvent {
    pub const fn new() -> Self {
        XSelectionRequestEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        owner: 0,
        requestor: 0,
        selection: 0,
        target: 0,
        property: 0,
        time: 0
        }
    }
}

impl std::default::Default for XSelectionRequestEvent {
    fn default() -> Self { XSelectionRequestEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub requestor: std::os::raw::c_ulong,
    pub selection: std::os::raw::c_ulong,
    pub target: std::os::raw::c_ulong,
    pub property: std::os::raw::c_ulong,
    pub time: std::os::raw::c_ulong,
}
impl XSelectionEvent {
    pub const fn new() -> Self {
        XSelectionEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        requestor: 0,
        selection: 0,
        target: 0,
        property: 0,
        time: 0
        }
    }
}

impl std::default::Default for XSelectionEvent {
    fn default() -> Self { XSelectionEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XColormapEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub colormap: std::os::raw::c_ulong,
    pub new: std::os::raw::c_int,
    pub state: std::os::raw::c_int,
}
impl XColormapEvent {
    pub const fn new() -> Self {
        XColormapEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        colormap: 0,
        new: 0,
        state: 0
        }
    }
}

impl std::default::Default for XColormapEvent {
    fn default() -> Self { XColormapEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XClientMessageEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub message_type: std::os::raw::c_ulong,
    pub format: std::os::raw::c_int,
    pub data: crate::C2RustUnnamed_0,
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
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
    pub request: std::os::raw::c_int,
    pub first_keycode: std::os::raw::c_int,
    pub count: std::os::raw::c_int,
}
impl XMappingEvent {
    pub const fn new() -> Self {
        XMappingEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0,
        request: 0,
        first_keycode: 0,
        count: 0
        }
    }
}

impl std::default::Default for XMappingEvent {
    fn default() -> Self { XMappingEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XErrorEvent {
    pub type_0: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub resourceid: std::os::raw::c_ulong,
    pub serial: std::os::raw::c_ulong,
    pub error_code: std::os::raw::c_uchar,
    pub request_code: std::os::raw::c_uchar,
    pub minor_code: std::os::raw::c_uchar,
}
impl XErrorEvent {
    pub const fn new() -> Self {
        XErrorEvent {
        type_0: 0,
        display: (0 as * mut crate::_XDisplay),
        resourceid: 0,
        serial: 0,
        error_code: 0,
        request_code: 0,
        minor_code: 0
        }
    }
}

impl std::default::Default for XErrorEvent {
    fn default() -> Self { XErrorEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XAnyEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub window: std::os::raw::c_ulong,
}
impl XAnyEvent {
    pub const fn new() -> Self {
        XAnyEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        window: 0
        }
    }
}

impl std::default::Default for XAnyEvent {
    fn default() -> Self { XAnyEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGenericEvent {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub extension: std::os::raw::c_int,
    pub evtype: std::os::raw::c_int,
}
impl XGenericEvent {
    pub const fn new() -> Self {
        XGenericEvent {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        extension: 0,
        evtype: 0
        }
    }
}

impl std::default::Default for XGenericEvent {
    fn default() -> Self { XGenericEvent::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGenericEventCookie {
    pub type_0: std::os::raw::c_int,
    pub serial: std::os::raw::c_ulong,
    pub send_event: std::os::raw::c_int,
    pub display: * mut crate::_XDisplay,
    pub extension: std::os::raw::c_int,
    pub evtype: std::os::raw::c_int,
    pub cookie: std::os::raw::c_uint,
    pub data: * mut core::ffi::c_void,
}
impl XGenericEventCookie {
    pub const fn new() -> Self {
        XGenericEventCookie {
        type_0: 0,
        serial: 0,
        send_event: 0,
        display: (0 as * mut crate::_XDisplay),
        extension: 0,
        evtype: 0,
        cookie: 0,
        data: (0 as * mut core::ffi::c_void)
        }
    }
}

impl std::default::Default for XGenericEventCookie {
    fn default() -> Self { XGenericEventCookie::new() }
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
pub type XEvent = crate::_XEvent;
pub type XErrorHandler<'a1, 'a2>
    =
    Option<unsafe extern "C"  fn(_: Option<&'a1 mut crate::_XDisplay>,_: Option<&'a2 mut crate::XErrorEvent>,) -> std::os::raw::c_int>;
unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: * mut * mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut display: * mut crate::_XDisplay = 0 as *mut Display;
    let mut status: i32 = 0;
    let mut color: crate::XColor =
        XColor{pixel: 0, red: 0, green: 0, blue: 0, flags: 0, pad: 0,};
    let mut cmap: u64 = 0;
    let mut i: i32 = 0;
    let mut r: i32 = 0;
    let mut g: i32 = 0;
    let mut b: i32 = 0;
    i = 1 as std::os::raw::c_int;
    while i < argc {
        if strncmp(*argv.offset(i as isize),
                   b"-h\x00" as *const u8 as *const std::os::raw::c_char,
                   2 as std::os::raw::c_int as std::os::raw::c_ulong) == 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"grabc 1.1 by Muhammad A Muquit\n\x00" as *const u8 as
                        *const std::os::raw::c_char);
            exit(1 as std::os::raw::c_int);
        }
        i += 1
    }
    display = XOpenDisplay(0 as *mut std::os::raw::c_void as *mut std::os::raw::c_char);
    cmap =
        (*(*(display as
                 _XPrivDisplay)).screens.offset((*(display as
                                                       _XPrivDisplay)).default_screen
                                                    as isize)).cmap;
    XSetErrorHandler(Some(MXError));
    if display.is_null() {
        fprintf(stderr,
                b"Failed to open local DISPLAY!\'n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    }
    status = getWindowColor(display, Some(&mut color));
    if status == 1 as std::os::raw::c_int {
        XQueryColor(display, cmap, &mut color);
        r = color.red as std::os::raw::c_int >> 8 as std::os::raw::c_int;
        g = color.green as std::os::raw::c_int >> 8 as std::os::raw::c_int;
        b = color.blue as std::os::raw::c_int >> 8 as std::os::raw::c_int;
        fprintf(stdout,
                b"#%02x%02x%02x\n\x00" as *const u8 as *const std::os::raw::c_char, r,
                g, b);
        fflush(stdout);
        /*
        ** write the values in decimal on stderr
        */
        fprintf(stderr, b"%d,%d,%d\n\x00" as *const u8 as *const std::os::raw::c_char,
                r, g, b);
    } else {
        fprintf(stderr,
                b"Failed to grab color!\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
    }
    return 0 as std::os::raw::c_int;
}
// Initialized in run_static_initializers
static mut cross_cursor: std::os::raw::c_ulong = 0; unsafe fn laertes_init_cross_cursor() {
cross_cursor = 0;}//;
/*  A program to pick a color by clicking the mouse.
 *
 *  RCS:
 *      $Revision$
 *      $Date$
 *
 *  Description:
 *
 *  When this program is run, the mouse pointer is grabbed and changed to
 *  a cross hair and when the mouse is clicked, the color of the clicked
 *  pixel is written to stdout in hex prefixed with #
 *
 *  This program can be useful when you see a color and want to use the
 *  color in xterm or your window manager's border but no clue what the 
 *  name of the color is. It's silly to use a image processing software
 *  to find it out.
 *
 * Example: 
 *   cpick
 *          #ffffff
 *   xterm -bg `cpick` -fg `cpick` (silly but esoteric!) 
 *
 *  Development History:
 *      who                  when               why
 *      ma_muquit@fccc.edu   march-16-19997     first cut
 */
/* private function prototypes */
/*
** function to select a window
** output parameters: x,y (coordinate of the point of click)
** reutrns Window
** exits if mouse can not be grabbed
*/
unsafe extern "C" fn selectWindow<'a1, 'a2>(mut display: * mut crate::_XDisplay,
                                  mut x: Option<&'a1 mut std::os::raw::c_int>,
                                  mut y: Option<&'a2 mut std::os::raw::c_int>) -> std::os::raw::c_ulong {
    let mut target_cursor: u64 = 0;
    let mut status: i32 = 0;
    let mut target_window: u64 = 0;
    let mut root_window: u64 = 0;
    let mut event: crate::_XEvent = _XEvent{type_0: 0,};
    target_window = 0 as *mut std::os::raw::c_void as Window;
    if cross_cursor == 0 as *mut std::os::raw::c_void as Cursor {
        cross_cursor =
            XCreateFontCursor(display, 130 as std::os::raw::c_int as std::os::raw::c_uint);
        if cross_cursor == 0 as *mut std::os::raw::c_void as Cursor {
            fprintf(stderr,
                    b"Failed to create Cross Cursor!\n\x00" as *const u8 as
                        *const std::os::raw::c_char);
            return 0 as *mut std::os::raw::c_void as Window
        }
    }
    target_cursor = cross_cursor;
    root_window = XRootWindow(display, XDefaultScreen(display));
    status =
        XGrabPointer(display, root_window, 0 as std::os::raw::c_int,
                     ((1 as std::os::raw::c_long) << 2 as std::os::raw::c_int) as
                         std::os::raw::c_uint, 0 as std::os::raw::c_int, 1 as std::os::raw::c_int,
                     root_window, target_cursor, 0 as std::os::raw::c_long as Time);
    if status == 0 as std::os::raw::c_int {
        XAllowEvents(display, 1 as std::os::raw::c_int, 0 as std::os::raw::c_long as Time);
        XWindowEvent(display, root_window,
                     (1 as std::os::raw::c_long) << 2 as std::os::raw::c_int, &mut event);
        if event.type_0 == 4 as std::os::raw::c_int {
            target_window =
                findSubWindow(display, root_window, event.xbutton.subwindow,
                              Some(&mut event.xbutton.x), Some(&mut event.xbutton.y));
            if target_window == 0 as *mut std::os::raw::c_void as Window {
                fprintf(stderr,
                        b"Failed to get target window, getting root window!\n\x00"
                            as *const u8 as *const std::os::raw::c_char);
                target_window = root_window
            }
            XUngrabPointer(display, 0 as std::os::raw::c_long as Time);
        }
    } else {
        fprintf(stderr,
                b"Failed to grab mouse!\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    }
    /* free things we do not need, always a good practice */
    XFreeCursor(display, cross_cursor);
    *(borrow_mut(&mut x)).unwrap() = event.xbutton.x;
    *(borrow_mut(&mut y)).unwrap() = event.xbutton.y;
    return target_window;
}
/* find a window */
unsafe extern "C" fn findSubWindow<'a1, 'a2>(mut display: * mut crate::_XDisplay,
                                   mut top_window: std::os::raw::c_ulong,
                                   mut window_to_check: std::os::raw::c_ulong,
                                   mut x: Option<&'a1 mut std::os::raw::c_int>,
                                   mut y: Option<&'a2 mut std::os::raw::c_int>) -> std::os::raw::c_ulong {
    let mut newx: i32 = 0;
    let mut newy: i32 = 0;
    let mut window: u64 = 0;
    if top_window == 0 as *mut std::os::raw::c_void as Window {
        return 0 as *mut std::os::raw::c_void as Window
    }
    if window_to_check == 0 as *mut std::os::raw::c_void as Window {
        return 0 as *mut std::os::raw::c_void as Window
    }
    /* initialize automatics */
    window = window_to_check;
    while XTranslateCoordinates(display, top_window, window_to_check, *(borrow_mut(&mut x)).unwrap(), *(borrow_mut(&mut y)).unwrap(),
                                &mut newx, &mut newy, &mut window) !=
              0 as std::os::raw::c_int && window != 0 as *mut std::os::raw::c_void as Window {
        if window != 0 as *mut std::os::raw::c_void as Window {
            top_window = window_to_check;
            window_to_check = window;
            *(borrow_mut(&mut x)).unwrap() = newx;
            *(borrow_mut(&mut y)).unwrap() = newy
        }
    }
    if window == 0 as *mut std::os::raw::c_void as Window { window = window_to_check }
    *(borrow_mut(&mut x)).unwrap() = newx;
    *(borrow_mut(&mut y)).unwrap() = newy;
    return window;
}
/*
 * get the color of the pixel of the point of mouse click
 * output paramter: XColor *color
 *
 * returns True if succeeds
 *          False if fails
 */
unsafe extern "C" fn getWindowColor<'a1>(mut display: * mut crate::_XDisplay,
                                    mut color: Option<&'a1 mut crate::XColor>) -> std::os::raw::c_int {
    let mut root_window: u64 = 0;
    let mut target_window: u64 = 0;
    let mut ximage: * mut crate::_XImage = 0 as *mut XImage;
    let mut x: i32 = 0;
    let mut y: i32 = 0;
    let mut status: i32 = 0;
    root_window = XRootWindow(display, XDefaultScreen(display));
    target_window = selectWindow(display, Some(&mut x), Some(&mut y));
    if target_window == 0 as *mut std::os::raw::c_void as Window {
        return 0 as std::os::raw::c_int
    }
    ximage =
        XGetImage(display, target_window, x, y,
                  1 as std::os::raw::c_int as std::os::raw::c_uint,
                  1 as std::os::raw::c_int as std::os::raw::c_uint,
                  !(0 as std::os::raw::c_long) as std::os::raw::c_ulong, 2 as std::os::raw::c_int);
    if ximage.is_null() { return 0 as std::os::raw::c_int }
    (*(borrow_mut(&mut color)).unwrap()).pixel =
        Some((*ximage).f.get_pixel.expect("non-null function pointer")).expect("non-null function pointer")(ximage,
                                                                                                            0
                                                                                                                as
                                                                                                                std::os::raw::c_int,
                                                                                                            0
                                                                                                                as
                                                                                                                std::os::raw::c_int);
    Some((*ximage).f.destroy_image.expect("non-null function pointer")).expect("non-null function pointer")(ximage);
    return 1 as std::os::raw::c_int;
}
/* forgiving X error handler */
unsafe extern "C" fn MXError(mut display: * mut crate::_XDisplay,
                             mut error: * mut crate::XErrorEvent) -> std::os::raw::c_int {
    let mut xerrcode: i32 = 0;
    xerrcode = (*error).error_code as std::os::raw::c_int;
    if xerrcode == 11 as std::os::raw::c_int ||
           xerrcode == 10 as std::os::raw::c_int &&
               (*error).request_code as std::os::raw::c_int == 88 as std::os::raw::c_int {
        return 0 as std::os::raw::c_int
    } else {
        match (*error).request_code as std::os::raw::c_int {
            14 => {
                if (*error).error_code as std::os::raw::c_int == 9 as std::os::raw::c_int {
                    return 0 as std::os::raw::c_int
                }
            }
            3 | 15 => {
                if (*error).error_code as std::os::raw::c_int == 3 as std::os::raw::c_int {
                    return 0 as std::os::raw::c_int
                }
            }
            91 => {
                if (*error).error_code as std::os::raw::c_int == 2 as std::os::raw::c_int {
                    return 0 as std::os::raw::c_int
                }
            }
            _ => { }
        }
    }
    return 1 as std::os::raw::c_int;
}
pub fn main() {
    let mut args: Vec<*mut std::os::raw::c_char> = Vec::new();
    for arg in ::std::env::args() {
        args.push(::std::ffi::CString::new(arg).expect("Failed to convert argument into CString.").into_raw());
    };
    args.push(::std::ptr::null_mut());
    unsafe {
        ::std::process::exit(main_0((args.len() - 1) as std::os::raw::c_int,
                                    args.as_mut_ptr() as
                                        *mut *mut std::os::raw::c_char) as i32)
    }
}
unsafe extern "C" fn run_static_initializers() {
    cross_cursor = 0 as *const std::os::raw::c_void as *mut std::os::raw::c_void as Cursor
}
#[used]
#[cfg_attr(target_os = "linux", link_section = ".init_array")]
#[cfg_attr(target_os = "windows", link_section = ".CRT$XIB")]
#[cfg_attr(target_os = "macos", link_section = "__DATA,__mod_init_func")]
static INIT_ARRAY: [unsafe extern "C"  fn() -> (); 1] = [run_static_initializers];
use crate::laertes_rt::*;// This module is only injected into the rewritten programs, it is not used
// internally. So, disable unused function warnings.
#[allow(dead_code)]
pub(crate) mod __laertes_array {
    use std::{
        cell::{Ref, RefCell, RefMut},
        cmp::Ordering,
        convert::{TryFrom, TryInto},
        marker::PhantomData,
    };

    pub trait Get<'g, T: 'g> {
        fn get(&'g self, index: SliceIndex) -> T;

        fn get_add(&'g self, index: usize) -> T {
            self.get(SliceIndex::Add(index))
        }

        fn get_sub(&'g self, index: usize) -> T {
            self.get(SliceIndex::Sub(index))
        }

        fn get_offset(&'g self, index: isize) -> T {
            self.get(SliceIndex::Offset(index))
        }
    }

    pub trait GetMut<'g, T: 'g> {
        fn get_mut(&'g mut self, index: SliceIndex) -> T;

        fn get_add_mut(&'g mut self, index: usize) -> T {
            self.get_mut(SliceIndex::Add(index))
        }

        fn get_sub_mut(&'g mut self, index: usize) -> T {
            self.get_mut(SliceIndex::Sub(index))
        }

        fn get_offset_mut(&'g mut self, index: isize) -> T {
            self.get_mut(SliceIndex::Offset(index))
        }
    }

    pub trait IntoSlice<S>: Sized {
        fn into_slice(self, index: SliceIndex) -> S;

        fn into_slice_add(self, index: usize) -> S {
            self.into_slice(SliceIndex::Add(index))
        }

        fn into_slice_sub(self, index: usize) -> S {
            self.into_slice(SliceIndex::Sub(index))
        }

        fn into_slice_offset(self, index: isize) -> S {
            self.into_slice(SliceIndex::Offset(index))
        }
    }

    pub trait Slice<'s, S: 's> {
        fn slice(&'s self, index: SliceIndex) -> S;

        fn slice_add(&'s self, index: usize) -> S {
            self.slice(SliceIndex::Add(index))
        }

        fn slice_sub(&'s self, index: usize) -> S {
            self.slice(SliceIndex::Sub(index))
        }

        fn slice_offset(&'s self, index: isize) -> S {
            self.slice(SliceIndex::Offset(index))
        }
    }

    pub trait SliceMut<'s, S: 's> {
        fn slice_mut(&'s mut self, index: SliceIndex) -> S;

        fn slice_add_mut(&'s mut self, index: usize) -> S {
            self.slice_mut(SliceIndex::Add(index))
        }

        fn slice_sub_mut(&'s mut self, index: usize) -> S {
            self.slice_mut(SliceIndex::Sub(index))
        }

        fn slice_offset_mut(&'s mut self, index: isize) -> S {
            self.slice_mut(SliceIndex::Offset(index))
        }
    }

    #[derive(Clone, Copy)]
    pub enum SliceIndex {
        Add(usize),
        Sub(usize),
        Offset(isize),
    }

    impl SliceIndex {
        fn apply(self, offset: usize) -> usize {
            match self {
                SliceIndex::Add(i) => offset.checked_add(i),
                SliceIndex::Sub(i) => offset.checked_sub(i),
                SliceIndex::Offset(i) => {
                    if i < 0 {
                        offset.checked_sub(i.wrapping_abs() as usize)
                    } else {
                        offset.checked_add(i as usize)
                    }
                },
            }
            .unwrap()
        }
    }

    #[derive(Debug, Clone, Copy)]
    pub struct CustomSlice<'a, T: 'a, S: 'a> {
        offset: usize,
        slice: S,
        m: PhantomData<&'a T>,
    }

    impl<'a, T: 'a, S: 'a> CustomSlice<'a, T, S> {
        pub const fn new(slice: S) -> CustomSlice<'a, T, S> {
            CustomSlice {
                offset: 0,
                slice,
                m: PhantomData,
            }
        }
    }

    impl<'a, T: 'a> CustomSlice<'a, T, Box<[T]>> {
        pub fn boxed_from_vec(vec: Vec<T>) -> CustomSlice<'a, T, Box<[T]>> {
            CustomSlice {
                offset: 0,
                slice: vec.into_boxed_slice(),
                m: PhantomData::default(),
            }
        }
    }

    impl<'a, T: 'a, S: TryFrom<Vec<RefCell<T>>> + 'a> CustomSlice<'a, T, S> {
        pub fn from_vec(vec: Vec<T>) -> CustomSlice<'a, T, S> {
            CustomSlice::new(
                vec.into_iter()
                    .map(|v| RefCell::new(v))
                    .collect::<Vec<_>>()
                    .try_into()
                    .unwrap_or_else(|_| panic!("couldn't construct backing slice")),
            )
        }
    }

    impl<'a, T, S> IntoSlice<CustomSlice<'a, T, S>> for CustomSlice<'a, T, S> {
        fn into_slice(self, index: SliceIndex) -> CustomSlice<'a, T, S> {
            let CustomSlice { offset, slice, m } = self;

            CustomSlice {
                offset: index.apply(offset),
                slice,
                m,
            }
        }
    }

    impl<'a, 's, T, S: AsRef<[T]> + 's> Slice<'s, CustomSlice<'s, T, &'s [T]>>
        for CustomSlice<'a, T, S>
    {
        fn slice(&'s self, index: SliceIndex) -> CustomSlice<'s, T, &'s [T]> {
            let CustomSlice {
                offset,
                ref slice,
                m,
            } = *self;

            CustomSlice {
                offset: index.apply(offset),
                slice: slice.as_ref(),
                m,
            }
        }
    }

    impl<'a, 's, T, S: AsRef<[RefCell<T>]> + 's> Slice<'s, CustomSlice<'s, T, &'s [RefCell<T>]>>
        for CustomSlice<'a, T, S>
    {
        fn slice(&'s self, index: SliceIndex) -> CustomSlice<'s, T, &'s [RefCell<T>]> {
            let CustomSlice {
                offset,
                ref slice,
                m,
            } = *self;

            CustomSlice {
                offset: index.apply(offset),
                slice: slice.as_ref(),
                m,
            }
        }
    }

    impl<'a, 's, T, S: AsMut<[T]> + 's> SliceMut<'s, CustomSlice<'s, T, &'s mut [T]>>
        for CustomSlice<'a, T, S>
    {
        fn slice_mut(&'s mut self, index: SliceIndex) -> CustomSlice<'s, T, &'s mut [T]> {
            let CustomSlice {
                offset,
                ref mut slice,
                m,
            } = *self;

            CustomSlice {
                offset: index.apply(offset),
                slice: slice.as_mut(),
                m,
            }
        }
    }

    impl<'a, 'g, T, S: AsRef<[T]> + 'g> Get<'g, &'g T> for CustomSlice<'a, T, S> {
        fn get(&'g self, index: SliceIndex) -> &'g T {
            &self.slice.as_ref()[index.apply(self.offset)]
        }
    }

    impl<'a, 'g, T, S: AsMut<[T]> + 'g> GetMut<'g, &'g mut T> for CustomSlice<'a, T, S> {
        fn get_mut(&'g mut self, index: SliceIndex) -> &'g mut T {
            &mut self.slice.as_mut()[index.apply(self.offset)]
        }
    }

    impl<'a, 'g, T, S: AsRef<[RefCell<T>]> + 'g> Get<'g, Ref<'g, T>> for CustomSlice<'a, T, S> {
        fn get(&'g self, index: SliceIndex) -> Ref<'g, T> {
            self.slice.as_ref()[index.apply(self.offset)].borrow()
        }
    }

    impl<'a, 'g, T, S: AsRef<[RefCell<T>]> + 'g> Get<'g, RefMut<'g, T>> for CustomSlice<'a, T, S> {
        fn get(&'g self, index: SliceIndex) -> RefMut<'g, T> {
            self.slice.as_ref()[index.apply(self.offset)].borrow_mut()
        }
    }

    pub trait GetPtr<T: ?Sized> {
        fn get_ptr(&self) -> *const ();
    }

    impl<T: ?Sized> GetPtr<T> for &T {
        fn get_ptr(&self) -> *const () {
            *self as *const T as *const ()
        }
    }

    impl<T: ?Sized> GetPtr<T> for &mut T {
        fn get_ptr(&self) -> *const () {
            *self as *const T as *const ()
        }
    }

    impl<T> GetPtr<T> for &[T] {
        fn get_ptr(&self) -> *const () {
            self.as_ptr() as *const ()
        }
    }

    impl<T> GetPtr<T> for &mut [T] {
        fn get_ptr(&self) -> *const () {
            self.as_ptr() as *const ()
        }
    }

    impl<T> GetPtr<T> for Box<[T]> {
        fn get_ptr(&self) -> *const () {
            (*self).as_ptr() as *const ()
        }
    }

    impl<T: ?Sized> GetPtr<T> for Box<T> {
        fn get_ptr(&self) -> *const () {
            self.as_ref() as *const T as *const ()
        }
    }

    pub fn offset_from<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> isize {
        if l.is_none() && r.is_none() {
            return 0; // case for NULL - NULL
        }

        l.as_ref()
            .and_then(|l| {
                r.as_ref().map(|r| {
                    if l.slice.get_ptr() == r.slice.get_ptr() {
                        l.offset as isize - r.offset as isize
                    } else {
                        panic!("trying to compute offsets from two unrelated slices");
                    }
                })
            })
            .expect("tried to compare non-null and null pointers")
    }

    pub fn partial_cmp<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> Option<Ordering> {
        l.as_ref().and_then(|l| {
            r.as_ref().and_then(|r| {
                if l.slice.get_ptr() == r.slice.get_ptr() {
                    Some(l.offset.cmp(&r.offset))
                } else {
                    None
                }
            })
        })
    }

    pub fn partial_lt<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> Option<bool> {
        partial_cmp(l, r).map(|c| c == Ordering::Less)
    }
    pub fn partial_gt<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> Option<bool> {
        partial_cmp(l, r).map(|c| c == Ordering::Greater)
    }
    pub fn partial_le<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> Option<bool> {
        partial_cmp(l, r).map(|c| c != Ordering::Greater)
    }
    pub fn partial_ge<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> Option<bool> {
        partial_cmp(l, r).map(|c| c != Ordering::Less)
    }

    pub fn compare_eq<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> bool {
        partial_cmp(l, r).map_or(false, |c| c == Ordering::Equal)
    }
    pub fn compare_ne<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> bool {
        !compare_eq(l, r)
    }

    pub fn compare_lt<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> bool {
        partial_lt(l, r).unwrap()
    }
    pub fn compare_gt<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> bool {
        partial_gt(l, r).unwrap()
    }
    pub fn compare_le<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> bool {
        partial_le(l, r).unwrap()
    }
    pub fn compare_ge<'a, T, L: GetPtr<T>, R: GetPtr<T>>(
        l: &Option<CustomSlice<'a, T, L>>,
        r: &Option<CustomSlice<'a, T, R>>,
    ) -> bool {
        partial_ge(l, r).unwrap()
    }

    pub fn borrow<'a, 'b: 'a, S: Slice<'a, T>, T: 'a>(s: &'b Option<S>) -> Option<T> {
        s.as_ref().map(|s| s.slice_add(0))
    }
    pub fn borrow_mut<'a, 'b: 'a, S: SliceMut<'a, T>, T: 'a>(s: &'b mut Option<S>) -> Option<T> {
        s.as_mut().map(|s| s.slice_add_mut(0))
    }
}

#[allow(dead_code)]
pub(crate) mod laertes_rt {
    use super::__laertes_array::GetPtr;

    pub trait Borrow<'b, T: ?Sized> {
        fn borrow<'a>(&'a self) -> Option<&'a T>
        where
            'b: 'a;
    }

    pub trait BorrowMut<'b, T: ?Sized> {
        fn borrow_mut<'a>(&'a mut self) -> Option<&'a mut T>
        where
            'b: 'a;
    }

    impl<'b, T: ?Sized> Borrow<'b, T> for Option<&'b mut T> {
        fn borrow<'a>(&'a self) -> Option<&'a T>
        where
            'b: 'a,
        {
            self.as_ref().map(|x| &**x)
        }
    }

    impl<'b, T: ?Sized> BorrowMut<'b, T> for Option<&'b mut T> {
        fn borrow_mut<'a>(&'a mut self) -> Option<&'a mut T>
        where
            'b: 'a,
        {
            self.as_mut().map(|x| &mut **x)
        }
    }

    impl<'b, T: ?Sized> Borrow<'b, T> for Option<Box<T>> {
        fn borrow<'a>(&'a self) -> Option<&'a T>
        where
            'b: 'a,
        {
            self.as_ref().map(|x| x.as_ref())
        }
    }

    impl<'b, T: ?Sized> BorrowMut<'b, T> for Option<Box<T>> {
        fn borrow_mut<'a>(&'a mut self) -> Option<&'a mut T>
        where
            'b: 'a,
        {
            self.as_mut().map(|x| x.as_mut())
        }
    }

    pub fn borrow<'a, 'b: 'a, T: ?Sized, P: Borrow<'b, T>>(p: &'a P) -> Option<&'a T> {
        Borrow::borrow(p)
    }

    pub fn borrow_mut<'a, 'b: 'a, T: ?Sized, P: BorrowMut<'b, T>>(
        p: &'a mut P,
    ) -> Option<&'a mut T> {
        BorrowMut::borrow_mut(p)
    }

    pub fn owned_as_ref<'a, T>(p: &'a Option<Box<T>>) -> Option<&'a T> {
        p.as_ref().map(|x| x.as_ref())
    }

    pub fn owned_as_mut<'a, T>(p: &'a mut Option<Box<T>>) -> Option<&'a mut T> {
        p.as_mut().map(|x| x.as_mut())
    }

    pub fn option_to_raw<T: ?Sized, P: GetPtr<T>>(p: &Option<P>) -> *const () {
        p.as_ref()
            .map_or(core::ptr::null(), |p| p.get_ptr() as *const ())
    }

    pub fn _ref_eq<T: ?Sized, L: GetPtr<T>, R: GetPtr<T>>(p: Option<L>, q: Option<R>) -> bool {
        option_to_raw(&p) == option_to_raw(&q)
    }

    pub fn _ref_ne<T: ?Sized, L: GetPtr<T>, R: GetPtr<T>>(p: Option<L>, q: Option<R>) -> bool {
        option_to_raw(&p) != option_to_raw(&q)
    }

    // functions to convert references to raw pointers
    pub fn _as_ptr<T, P: GetPtr<T>>(r: &Option<P>) -> *const T {
        option_to_raw(r) as *const T
    }

    pub fn _as_mut_ptr<T, P: GetPtr<T>>(r: &mut Option<P>) -> *mut T {
        option_to_raw(r) as *const T as *mut T
    }

    pub fn _move_to_ptr<T>(b: Option<Box<T>>) -> *mut T {
        b.map_or(core::ptr::null_mut(), Box::into_raw)
    }

    pub fn trans<'a, 'b, T: 'a, U: 'b>(_: T) -> U
    where
        'a: 'b,
    {
        loop {}
    }
}

