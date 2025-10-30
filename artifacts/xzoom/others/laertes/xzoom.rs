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
    static mut stderr: * mut crate::_IO_FILE;
    #[no_mangle]
    fn fprintf(_: * mut crate::_IO_FILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn printf(_: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn sprintf(_: * mut std::os::raw::c_char, _: * const std::os::raw::c_char, _: ...)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn sscanf(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char, _: ...)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn perror(__s: * const std::os::raw::c_char);
    #[no_mangle]
    fn memcpy(_: * mut core::ffi::c_void, _: * const core::ffi::c_void, _: std::os::raw::c_ulong)
     -> * mut core::ffi::c_void;
    #[no_mangle]
    fn strcmp(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn strrchr(_: * const std::os::raw::c_char, _: std::os::raw::c_int) -> * mut std::os::raw::c_char;
    #[no_mangle]
    fn strlen(_: * const std::os::raw::c_char) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn atoi(__nptr: * const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn malloc(_: std::os::raw::c_ulong) -> * mut core::ffi::c_void;
    #[no_mangle]
    fn free(__ptr: * mut core::ffi::c_void);
    #[no_mangle]
    fn atexit(__func: Option<unsafe extern "C"  fn() -> ()>) -> std::os::raw::c_int;
    #[no_mangle]
    fn exit(_: std::os::raw::c_int) -> !;
    #[no_mangle]
    fn signal(__sig: std::os::raw::c_int, __handler: Option<unsafe extern "C"  fn(_: std::os::raw::c_int,) -> ()>)
     -> Option<unsafe extern "C"  fn(_: std::os::raw::c_int,) -> ()>;
    #[no_mangle]
    fn XCreateImage(_: * mut crate::_XDisplay, _: * mut crate::Visual, _: std::os::raw::c_uint,
                    _: std::os::raw::c_int, _: std::os::raw::c_int, _: * mut std::os::raw::c_char,
                    _: std::os::raw::c_uint, _: std::os::raw::c_uint, _: std::os::raw::c_int,
                    _: std::os::raw::c_int) -> * mut crate::_XImage;
    #[no_mangle]
    fn XGetSubImage(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_int,
                    _: std::os::raw::c_int, _: std::os::raw::c_uint, _: std::os::raw::c_uint,
                    _: std::os::raw::c_ulong, _: std::os::raw::c_int, _: * mut crate::_XImage,
                    _: std::os::raw::c_int, _: std::os::raw::c_int) -> * mut crate::_XImage;
    #[no_mangle]
    fn XOpenDisplay(_: * const std::os::raw::c_char) -> * mut crate::_XDisplay;
    #[no_mangle]
    fn XInternAtom(_: * mut crate::_XDisplay, _: * const std::os::raw::c_char, _: std::os::raw::c_int)
     -> std::os::raw::c_ulong;
    #[no_mangle]
    fn XCreateFontCursor(_: * mut crate::_XDisplay, _: std::os::raw::c_uint) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn XCreateGC(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
                 _: * mut crate::XGCValues) -> * mut crate::_XGC;
    #[no_mangle]
    fn XCreateWindow(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_int,
                     _: std::os::raw::c_int, _: std::os::raw::c_uint, _: std::os::raw::c_uint,
                     _: std::os::raw::c_uint, _: std::os::raw::c_int, _: std::os::raw::c_uint,
                     _: * mut crate::Visual, _: std::os::raw::c_ulong,
                     _: * mut crate::XSetWindowAttributes) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn XKeycodeToKeysym(_: * mut crate::_XDisplay, _: std::os::raw::c_uchar, _: std::os::raw::c_int)
     -> std::os::raw::c_ulong;
    #[no_mangle]
    fn XSetWMProtocols(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: * mut std::os::raw::c_ulong,
                       _: std::os::raw::c_int) -> std::os::raw::c_int;
    #[no_mangle]
    fn XChangeProperty(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
                       _: std::os::raw::c_int, _: std::os::raw::c_int,
                       _: * const std::os::raw::c_uchar, _: std::os::raw::c_int)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn XDefineCursor(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XMapWindow(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn XNextEvent(_: * mut crate::_XDisplay, _: * mut crate::_XEvent) -> std::os::raw::c_int;
    #[no_mangle]
    fn XParseGeometry(_: * const std::os::raw::c_char, _: * mut std::os::raw::c_int,
                      _: * mut std::os::raw::c_int, _: * mut std::os::raw::c_uint,
                      _: * mut std::os::raw::c_uint) -> std::os::raw::c_int;
    #[no_mangle]
    fn XPending(_: * mut crate::_XDisplay) -> std::os::raw::c_int;
    #[no_mangle]
    fn XPutImage(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: * mut crate::_XGC, _: * mut crate::_XImage,
                 _: std::os::raw::c_int, _: std::os::raw::c_int, _: std::os::raw::c_int,
                 _: std::os::raw::c_int, _: std::os::raw::c_uint, _: std::os::raw::c_uint)
     -> std::os::raw::c_int;
    #[no_mangle]
    fn XSync(_: * mut crate::_XDisplay, _: std::os::raw::c_int) -> std::os::raw::c_int;
    #[no_mangle]
    fn XAllocClassHint() -> * mut crate::XClassHint;
    #[no_mangle]
    fn XAllocSizeHints() -> * mut crate::XSizeHints;
    #[no_mangle]
    fn XSetWMProperties(_: * mut crate::_XDisplay, _: std::os::raw::c_ulong, _: * mut crate::XTextProperty,
                        _: * mut crate::XTextProperty, _: * mut * mut std::os::raw::c_char,
                        _: std::os::raw::c_int, _: * mut crate::XSizeHints, _: * mut crate::XWMHints,
                        _: * mut crate::XClassHint);
    #[no_mangle]
    fn XStringListToTextProperty(_: * mut * mut std::os::raw::c_char, _: std::os::raw::c_int,
                                 _: * mut crate::XTextProperty) -> std::os::raw::c_int;
    #[no_mangle]
    fn alarm(__seconds: std::os::raw::c_uint) -> std::os::raw::c_uint;
    #[no_mangle]
    fn usleep(__useconds: std::os::raw::c_uint) -> std::os::raw::c_int;
}
pub type size_t = std::os::raw::c_ulong;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
pub type __useconds_t = std::os::raw::c_uint;
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
pub type __sighandler_t = Option<unsafe extern "C"  fn(_: std::os::raw::c_int,) -> ()>;
pub type XID = std::os::raw::c_ulong;
pub type Atom = std::os::raw::c_ulong;
pub type VisualID = std::os::raw::c_ulong;
pub type Time = std::os::raw::c_ulong;
pub type Window = std::os::raw::c_ulong;
pub type Drawable = std::os::raw::c_ulong;
pub type Font = std::os::raw::c_ulong;
pub type Pixmap = std::os::raw::c_ulong;
pub type Cursor = std::os::raw::c_ulong;
pub type Colormap = std::os::raw::c_ulong;
pub type KeySym = std::os::raw::c_ulong;
pub type KeyCode = std::os::raw::c_uchar;
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
    pub tile: std::os::raw::c_ulong,
    pub stipple: std::os::raw::c_ulong,
    pub ts_x_origin: std::os::raw::c_int,
    pub ts_y_origin: std::os::raw::c_int,
    pub font: std::os::raw::c_ulong,
    pub subwindow_mode: std::os::raw::c_int,
    pub graphics_exposures: std::os::raw::c_int,
    pub clip_x_origin: std::os::raw::c_int,
    pub clip_y_origin: std::os::raw::c_int,
    pub clip_mask: std::os::raw::c_ulong,
    pub dash_offset: std::os::raw::c_int,
    pub dashes: std::os::raw::c_char,
}
impl XGCValues {
    pub const fn new() -> Self {
        XGCValues {
        function: 0,
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
        dashes: 0
        }
    }
}

impl std::default::Default for XGCValues {
    fn default() -> Self { XGCValues::new() }
}

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
    pub root_visual: * mut crate::Visual,
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
        root_visual: (0 as * mut crate::Visual),
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
pub struct XSetWindowAttributes {
    pub background_pixmap: std::os::raw::c_ulong,
    pub background_pixel: std::os::raw::c_ulong,
    pub border_pixmap: std::os::raw::c_ulong,
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
    pub colormap: std::os::raw::c_ulong,
    pub cursor: std::os::raw::c_ulong,
}
impl XSetWindowAttributes {
    pub const fn new() -> Self {
        XSetWindowAttributes {
        background_pixmap: 0,
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
        cursor: 0
        }
    }
}

impl std::default::Default for XSetWindowAttributes {
    fn default() -> Self { XSetWindowAttributes::new() }
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
    pub min_aspect: crate::C2RustUnnamed_1,
    pub max_aspect: crate::C2RustUnnamed_1,
    pub base_width: std::os::raw::c_int,
    pub base_height: std::os::raw::c_int,
    pub win_gravity: std::os::raw::c_int,
}
impl XSizeHints {
    pub const fn new() -> Self {
        XSizeHints {
        flags: 0,
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        min_width: 0,
        min_height: 0,
        max_width: 0,
        max_height: 0,
        width_inc: 0,
        height_inc: 0,
        min_aspect: crate::C2RustUnnamed_1::new(),
        max_aspect: crate::C2RustUnnamed_1::new(),
        base_width: 0,
        base_height: 0,
        win_gravity: 0
        }
    }
}

impl std::default::Default for XSizeHints {
    fn default() -> Self { XSizeHints::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_1 {
    pub x: std::os::raw::c_int,
    pub y: std::os::raw::c_int,
}
impl C2RustUnnamed_1 {
    pub const fn new() -> Self {
        C2RustUnnamed_1 {
        x: 0,
        y: 0
        }
    }
}

impl std::default::Default for C2RustUnnamed_1 {
    fn default() -> Self { C2RustUnnamed_1::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XWMHints {
    pub flags: std::os::raw::c_long,
    pub input: std::os::raw::c_int,
    pub initial_state: std::os::raw::c_int,
    pub icon_pixmap: std::os::raw::c_ulong,
    pub icon_window: std::os::raw::c_ulong,
    pub icon_x: std::os::raw::c_int,
    pub icon_y: std::os::raw::c_int,
    pub icon_mask: std::os::raw::c_ulong,
    pub window_group: std::os::raw::c_ulong,
}
impl XWMHints {
    pub const fn new() -> Self {
        XWMHints {
        flags: 0,
        input: 0,
        initial_state: 0,
        icon_pixmap: 0,
        icon_window: 0,
        icon_x: 0,
        icon_y: 0,
        icon_mask: 0,
        window_group: 0
        }
    }
}

impl std::default::Default for XWMHints {
    fn default() -> Self { XWMHints::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XTextProperty {
    pub value: * mut std::os::raw::c_uchar,
    pub encoding: std::os::raw::c_ulong,
    pub format: std::os::raw::c_int,
    pub nitems: std::os::raw::c_ulong,
}
impl XTextProperty {
    pub const fn new() -> Self {
        XTextProperty {
        value: (0 as * mut std::os::raw::c_uchar),
        encoding: 0,
        format: 0,
        nitems: 0
        }
    }
}

impl std::default::Default for XTextProperty {
    fn default() -> Self { XTextProperty::new() }
}

#[derive(Copy, Clone)]
#[repr(C)]
pub struct XClassHint {
    pub res_name: * mut std::os::raw::c_char,
    pub res_class: * mut std::os::raw::c_char,
}
impl XClassHint {
    pub const fn new() -> Self {
        XClassHint {
        res_name: (0 as * mut std::os::raw::c_char),
        res_class: (0 as * mut std::os::raw::c_char)
        }
    }
}

impl std::default::Default for XClassHint {
    fn default() -> Self { XClassHint::new() }
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
pub static mut dpy: * mut crate::_XDisplay = (0 as * mut crate::_XDisplay); unsafe fn laertes_init_dpy() {
dpy = 0 as *const Display as *mut Display;}//;
#[no_mangle]
pub static mut scr: * mut crate::Screen<'static> = (0 as * mut crate::Screen<'static>); unsafe fn laertes_init_scr() {
scr = (0 as * mut crate::Screen<'_>);}//;
#[no_mangle]
pub static mut win: std::os::raw::c_ulong = 0; unsafe fn laertes_init_win() {
win = 0;}//;
#[no_mangle]
pub static mut wm_delete_window: std::os::raw::c_ulong = 0; unsafe fn laertes_init_wm_delete_window() {
wm_delete_window = 0;}//;
#[no_mangle]
pub static mut wm_protocols: std::os::raw::c_ulong = 0; unsafe fn laertes_init_wm_protocols() {
wm_protocols = 0;}//;
#[no_mangle]
pub static mut wm_dock: std::os::raw::c_ulong = 0; unsafe fn laertes_init_wm_dock() {
wm_dock = 0;}//;
#[no_mangle]
pub static mut wm_windowtype: std::os::raw::c_ulong = 0; unsafe fn laertes_init_wm_windowtype() {
wm_windowtype = 0;}//;
#[no_mangle]
pub static mut status: std::os::raw::c_int = 0; unsafe fn laertes_init_status() {
status = 0;}//;
#[no_mangle]
pub static mut gc: * mut crate::_XGC = (0 as * mut crate::_XGC); unsafe fn laertes_init_gc() {
gc = 0 as *const _XGC as *mut _XGC;}//;
#[no_mangle]
pub static mut when_button: std::os::raw::c_ulong = 0; unsafe fn laertes_init_when_button() {
when_button = 0;}//;
#[no_mangle]
pub static mut crosshair: std::os::raw::c_ulong = 0; unsafe fn laertes_init_crosshair() {
crosshair = 0;}//;
#[no_mangle]
pub static mut progname: * mut std::os::raw::c_char =
    (0 as * mut std::os::raw::c_char); unsafe fn laertes_init_progname() {
progname = 0 as *const std::os::raw::c_char as *mut std::os::raw::c_char;}//;
#[no_mangle]
pub static mut set_title: std::os::raw::c_int = 0; unsafe fn laertes_init_set_title() {
set_title = 0;}//;
/* vertical magnification */
#[no_mangle]
pub static mut xgrab: std::os::raw::c_int = 0; unsafe fn laertes_init_xgrab() {
xgrab = 0;}//;
#[no_mangle]
pub static mut ygrab: std::os::raw::c_int = 0; unsafe fn laertes_init_ygrab() {
ygrab = 0;}//;
/* where do we take the picture from */
#[no_mangle]
pub static mut magx: std::os::raw::c_int = 0; unsafe fn laertes_init_magx() {
magx = 2 as std::os::raw::c_int;}//;
#[no_mangle]
pub static mut magy: std::os::raw::c_int = 0; unsafe fn laertes_init_magy() {
magy = 2 as std::os::raw::c_int;}//;
#[no_mangle]
pub static mut flipxy: std::os::raw::c_int = 0; unsafe fn laertes_init_flipxy() {
flipxy = 0 as std::os::raw::c_int;}//;
/* flip x and y */
#[no_mangle]
pub static mut flipx: std::os::raw::c_int = 0; unsafe fn laertes_init_flipx() {
flipx = 0 as std::os::raw::c_int;}//;
/* flip display about y axis */
#[no_mangle]
pub static mut flipy: std::os::raw::c_int = 0; unsafe fn laertes_init_flipy() {
flipy = 0 as std::os::raw::c_int;}//;
/* flip display about x axiz */
#[no_mangle]
pub static mut xzoom_flag: std::os::raw::c_int = 0; unsafe fn laertes_init_xzoom_flag() {
xzoom_flag = 0 as std::os::raw::c_int;}//;
/* next mag change only to magx */
#[no_mangle]
pub static mut yzoom_flag: std::os::raw::c_int = 0; unsafe fn laertes_init_yzoom_flag() {
yzoom_flag = 0 as std::os::raw::c_int;}//;
/* next mag change only to magy */
#[no_mangle]
pub static mut gridx: std::os::raw::c_int = 0; unsafe fn laertes_init_gridx() {
gridx = 0 as std::os::raw::c_int;}//;
#[no_mangle]
pub static mut gridy: std::os::raw::c_int = 0; unsafe fn laertes_init_gridy() {
gridy = 0 as std::os::raw::c_int;}//;
#[no_mangle]
pub static mut width: [std::os::raw::c_int; 2] =
    [0,0,]; unsafe fn laertes_init_width() {
width = [0 as std::os::raw::c_int, 256 as std::os::raw::c_int];}//;
#[no_mangle]
pub static mut height: [std::os::raw::c_int; 2] =
    [0,0,]; unsafe fn laertes_init_height() {
height = [0 as std::os::raw::c_int, 256 as std::os::raw::c_int];}//;
#[no_mangle]
pub static mut depth: std::os::raw::c_uint = 0; unsafe fn laertes_init_depth() {
depth = 0 as std::os::raw::c_int as std::os::raw::c_uint;}//;
#[no_mangle]
pub static mut ximage: [* mut crate::_XImage; 2] =
    [(0 as * mut crate::_XImage),(0 as * mut crate::_XImage),]; unsafe fn laertes_init_ximage() {
ximage = [0 as *const XImage as *mut XImage; 2];}//;
/* Ximage struct. */
#[no_mangle]
pub static mut created_images: std::os::raw::c_int = 0; unsafe fn laertes_init_created_images() {
created_images = 0 as std::os::raw::c_int;}//;
#[no_mangle]
pub static mut delays: [std::os::raw::c_int; 5] =
    [0,0,0,0,0,]; unsafe fn laertes_init_delays() {
delays = [200000 as std::os::raw::c_int, 100000 as std::os::raw::c_int, 50000 as std::os::raw::c_int,
     10000 as std::os::raw::c_int, 0 as std::os::raw::c_int];}//;
#[no_mangle]
pub static mut delay_index: std::os::raw::c_int = 0; unsafe fn laertes_init_delay_index() {
delay_index = 0 as std::os::raw::c_int;}//;
#[no_mangle]
pub static mut delay: std::os::raw::c_int = 0; unsafe fn laertes_init_delay() {
delay = 200000 as std::os::raw::c_int;}//;
/* 0.2 second between updates */
#[no_mangle]
pub unsafe extern "C" fn timeout_func(mut signum: std::os::raw::c_int) {
    set_title = 1 as std::os::raw::c_int;
    signum = signum;
    /* UNUSED */
}
#[no_mangle]
pub unsafe extern "C" fn allocate_images() {
    let mut i: i32 = 0;
    i = 0 as std::os::raw::c_int;
    while i < 2 as std::os::raw::c_int {
        let mut data: * mut i8 = 0 as *mut std::os::raw::c_char;
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
    let mut i: i32 = 0;
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
pub unsafe extern "C" fn Usage() {
    fprintf(stderr,
            b"Usage: %s [ args ]\nCommand line args:\n-display displayname\n-mag magnification [ magnification ]\n-geometry geometry\n-source geometry\n-dock\n-x\n-y\n-xy\n\nWindow commands:\n+: Zoom in\n-: Zoom out\nx: Flip right and left\ny: Flip top and bottom\nz: Rotate 90 degrees counter-clockwize\nw: Next \'+\' or \'-\' only change width scaling\nh: Next \'+\' or \'-\' only change height scaling\nd: Change delay between frames\nq: Quit\nArrow keys: Scroll in direction of arrow\nMouse button drag: Set top-left corner of viewed area\n\x00"
                as *const u8 as *const std::os::raw::c_char, progname);
    exit(1 as std::os::raw::c_int);
}
/* resize is called with the dest size.
   we call it then manification changes or when
   actual window size is changed */
#[no_mangle]
pub unsafe extern "C" fn resize(mut new_width: std::os::raw::c_int,
                                mut new_height: std::os::raw::c_int) {
    destroy_images(); /* we can get rid of these */
    /* find new dimensions for source */
    if flipxy != 0 {
        height[0 as std::os::raw::c_int as usize] =
            (new_width + magx - 1 as std::os::raw::c_int) / magx;
        width[0 as std::os::raw::c_int as usize] =
            (new_height + magy - 1 as std::os::raw::c_int) / magy
    } else {
        width[0 as std::os::raw::c_int as usize] =
            (new_width + magx - 1 as std::os::raw::c_int) / magx;
        height[0 as std::os::raw::c_int as usize] =
            (new_height + magy - 1 as std::os::raw::c_int) / magy
    }
    if width[0 as std::os::raw::c_int as usize] < 1 as std::os::raw::c_int {
        width[0 as std::os::raw::c_int as usize] = 1 as std::os::raw::c_int
    }
    if width[0 as std::os::raw::c_int as usize] > (*scr).width {
        width[0 as std::os::raw::c_int as usize] = (*scr).width
    }
    if height[0 as std::os::raw::c_int as usize] < 1 as std::os::raw::c_int {
        height[0 as std::os::raw::c_int as usize] = 1 as std::os::raw::c_int
    }
    if height[0 as std::os::raw::c_int as usize] > (*scr).height {
        height[0 as std::os::raw::c_int as usize] = (*scr).height
    }
    /* temporary, the dest image may be larger than the
	   actual window */
    if flipxy != 0 {
        width[1 as std::os::raw::c_int as usize] =
            magx *
                height[0 as std::os::raw::c_int as usize]; /* allocate new images */
        height[1 as std::os::raw::c_int as usize] =
            magy * width[0 as std::os::raw::c_int as usize]
    } else {
        width[1 as std::os::raw::c_int as usize] =
            magx * width[0 as std::os::raw::c_int as usize];
        height[1 as std::os::raw::c_int as usize] =
            magy * height[0 as std::os::raw::c_int as usize]
    }
    allocate_images();
    /* remember actual window size */
    if width[1 as std::os::raw::c_int as usize] > new_width {
        width[1 as std::os::raw::c_int as usize] = new_width
    }
    if height[1 as std::os::raw::c_int as usize] > new_height {
        height[1 as std::os::raw::c_int as usize] = new_height
    };
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
    j =
        if flipxy != 0 {
            (width[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int
        } else { (height[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int };
    loop  {
        let mut p1: * mut u8 = 0 as *mut std::os::raw::c_uchar;
        let mut p2: * mut u8 = 0 as *mut std::os::raw::c_uchar;
        let mut p2step: i32 = 0;
        let mut p1_save: * mut u8 = 0 as *mut std::os::raw::c_uchar;
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
                let mut c: u8 = *p2;
                p2 = p2.offset(p2step as isize);
                k = magx;
                loop  {
                    let mut fresh0 = p1;
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
                let mut c_0: u8 = *p2;
                k = magx;
                loop  {
                    let mut fresh1 = p1;
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
                let mut fresh2 = p2;
                p2 = p2.offset(1);
                let mut c_1: u8 = *fresh2;
                k = magx;
                loop  {
                    let mut fresh3 = p1;
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
        if magy > 1 as std::os::raw::c_int {
            /* p1 point to begining of scanline j*magy in DST */
            /* p1 point to begining of scanline j*magy in DST */
            /* p1 point to begining of scanline j*magy in DST */
            p1 = p1_save;
            /* p2 points to begining of next line */
            /* p2 points to begining of next line */
            /* p2 points to begining of next line */
            p2 = p1;
            p2step =
                ((*ximage[1 as std::os::raw::c_int as usize]).bytes_per_line as
                     std::os::raw::c_ulong).wrapping_div(::std::mem::size_of::<std::os::raw::c_uchar>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            i =
                (width[1 as std::os::raw::c_int as usize] as
                     std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uchar>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            k = magy - 1 as std::os::raw::c_int;
            loop  {
                p2 = p2.offset(p2step as isize);
                memcpy(p2 as *mut std::os::raw::c_void, p1 as *const std::os::raw::c_void,
                       i as std::os::raw::c_ulong);
                k -= 1;
                if !(k > 0 as std::os::raw::c_int) { break ; }
            }
            /* draw horizontal grid */
            /* draw horizontal grid */
            /* draw horizontal grid */
            if gridx != 0 && magy >= 2 as std::os::raw::c_int {
                k = width[1 as std::os::raw::c_int as usize];
                loop  {
                    let mut fresh4 = p2;
                    p2 = p2.offset(1);
                    *fresh4 =
                        (*fresh4 as std::os::raw::c_int ^
                             !(0 as std::os::raw::c_int as std::os::raw::c_uchar as
                                   std::os::raw::c_int)) as std::os::raw::c_uchar;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
            }
        }
        j -= 1;
        if !(j >= 0 as std::os::raw::c_int) { break ; }
    };
}
#[no_mangle]
pub unsafe extern "C" fn scale16() {
    let mut i: i32 = 0;
    let mut j: i32 = 0;
    let mut k: i32 = 0;
    j =
        if flipxy != 0 {
            (width[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int
        } else { (height[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int };
    loop  {
        let mut p1: * mut u16 = 0 as *mut std::os::raw::c_ushort;
        let mut p2: * mut u16 = 0 as *mut std::os::raw::c_ushort;
        let mut p2step: i32 = 0;
        let mut p1_save: * mut u16 = 0 as *mut std::os::raw::c_ushort;
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
                let mut c: u16 = *p2;
                p2 = p2.offset(p2step as isize);
                k = magx;
                loop  {
                    let mut fresh5 = p1;
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
                let mut c_0: u16 = *p2;
                k = magx;
                loop  {
                    let mut fresh6 = p1;
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
                let mut fresh7 = p2;
                p2 = p2.offset(1);
                let mut c_1: u16 = *fresh7;
                k = magx;
                loop  {
                    let mut fresh8 = p1;
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
        if magy > 1 as std::os::raw::c_int {
            p1 = p1_save;
            p2 = p1;
            p2step =
                ((*ximage[1 as std::os::raw::c_int as usize]).bytes_per_line as
                     std::os::raw::c_ulong).wrapping_div(::std::mem::size_of::<std::os::raw::c_ushort>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            i =
                (width[1 as std::os::raw::c_int as usize] as
                     std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_ushort>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            k = magy - 1 as std::os::raw::c_int;
            loop  {
                p2 = p2.offset(p2step as isize);
                memcpy(p2 as *mut std::os::raw::c_void, p1 as *const std::os::raw::c_void,
                       i as std::os::raw::c_ulong);
                k -= 1;
                if !(k > 0 as std::os::raw::c_int) { break ; }
            }
            if gridx != 0 && magy >= 2 as std::os::raw::c_int {
                k = width[1 as std::os::raw::c_int as usize];
                loop  {
                    let mut fresh9 = p2;
                    p2 = p2.offset(1);
                    *fresh9 =
                        (*fresh9 as std::os::raw::c_int ^
                             !(0 as std::os::raw::c_int as std::os::raw::c_ushort as
                                   std::os::raw::c_int)) as std::os::raw::c_ushort;
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
            }
        }
        j -= 1;
        if !(j >= 0 as std::os::raw::c_int) { break ; }
    };
}
#[no_mangle]
pub unsafe extern "C" fn scale32() {
    let mut i: i32 = 0;
    let mut j: i32 = 0;
    let mut k: i32 = 0;
    j =
        if flipxy != 0 {
            (width[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int
        } else { (height[0 as std::os::raw::c_int as usize]) - 1 as std::os::raw::c_int };
    loop  {
        let mut p1: * mut u32 = 0 as *mut std::os::raw::c_uint;
        let mut p2: * mut u32 = 0 as *mut std::os::raw::c_uint;
        let mut p2step: i32 = 0;
        let mut p1_save: * mut u32 = 0 as *mut std::os::raw::c_uint;
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
                let mut c: u32 = *p2;
                p2 = p2.offset(p2step as isize);
                k = magx;
                loop  {
                    let mut fresh10 = p1;
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
                let mut c_0: u32 = *p2;
                k = magx;
                loop  {
                    let mut fresh11 = p1;
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
                let mut fresh12 = p2;
                p2 = p2.offset(1);
                let mut c_1: u32 = *fresh12;
                k = magx;
                loop  {
                    let mut fresh13 = p1;
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
        if magy > 1 as std::os::raw::c_int {
            p1 = p1_save;
            p2 = p1;
            p2step =
                ((*ximage[1 as std::os::raw::c_int as usize]).bytes_per_line as
                     std::os::raw::c_ulong).wrapping_div(::std::mem::size_of::<std::os::raw::c_uint>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            i =
                (width[1 as std::os::raw::c_int as usize] as
                     std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_uint>()
                                                     as std::os::raw::c_ulong) as
                    std::os::raw::c_int;
            k = magy - 1 as std::os::raw::c_int;
            loop  {
                p2 = p2.offset(p2step as isize);
                memcpy(p2 as *mut std::os::raw::c_void, p1 as *const std::os::raw::c_void,
                       i as std::os::raw::c_ulong);
                k -= 1;
                if !(k > 0 as std::os::raw::c_int) { break ; }
            }
            if gridx != 0 && magy >= 2 as std::os::raw::c_int {
                k = width[1 as std::os::raw::c_int as usize];
                loop  {
                    let mut fresh14 = p2;
                    p2 = p2.offset(1);
                    *fresh14 ^= !(0 as std::os::raw::c_int as std::os::raw::c_uint);
                    k -= 1;
                    if !(k > 0 as std::os::raw::c_int) { break ; }
                }
            }
        }
        j -= 1;
        if !(j >= 0 as std::os::raw::c_int) { break ; }
    };
}
#[no_mangle]
pub unsafe extern "C" fn xzoom(mut buttonpressed: std::os::raw::c_int) {
    let mut title: [i8; 80] = [0; 80];
    XGetSubImage(dpy, (*scr).root, xgrab, ygrab,
                 width[0 as std::os::raw::c_int as usize] as std::os::raw::c_uint,
                 height[0 as std::os::raw::c_int as usize] as std::os::raw::c_uint,
                 !(0 as std::os::raw::c_long) as std::os::raw::c_ulong, 2 as std::os::raw::c_int,
                 ximage[0 as std::os::raw::c_int as usize], 0 as std::os::raw::c_int,
                 0 as std::os::raw::c_int);
    if depth == 8 as std::os::raw::c_int as std::os::raw::c_uint {
        scale8();
    } else if depth as std::os::raw::c_ulong <=
                  (8 as std::os::raw::c_int as
                       std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_short>()
                                                       as std::os::raw::c_ulong) {
        scale16();
    } else if depth as std::os::raw::c_ulong <=
                  (8 as std::os::raw::c_int as
                       std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_int>()
                                                       as std::os::raw::c_ulong) {
        scale32();
    }
    XPutImage(dpy, win, gc, ximage[1 as std::os::raw::c_int as usize],
              0 as std::os::raw::c_int, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int,
              0 as std::os::raw::c_int,
              width[1 as std::os::raw::c_int as usize] as std::os::raw::c_uint,
              height[1 as std::os::raw::c_int as usize] as std::os::raw::c_uint);
    if set_title != 0 {
        if magx == magy && flipx == 0 && flipy == 0 && flipxy == 0 {
            sprintf(title.as_mut_ptr(),
                    b"%s x%d\x00" as *const u8 as *const std::os::raw::c_char,
                    progname, magx);
        } else {
            sprintf(title.as_mut_ptr(),
                    b"%s X %s%d%s Y %s%d\x00" as *const u8 as
                        *const std::os::raw::c_char, progname,
                    if flipx != 0 {
                        b"-\x00" as *const u8 as *const std::os::raw::c_char
                    } else { b"\x00" as *const u8 as *const std::os::raw::c_char },
                    magx,
                    if flipxy != 0 {
                        b" <=>\x00" as *const u8 as *const std::os::raw::c_char
                    } else { b";\x00" as *const u8 as *const std::os::raw::c_char },
                    if flipy != 0 {
                        b"-\x00" as *const u8 as *const std::os::raw::c_char
                    } else { b"\x00" as *const u8 as *const std::os::raw::c_char },
                    magy);
        }
        XChangeProperty(dpy, win, 39 as std::os::raw::c_int as Atom,
                        31 as std::os::raw::c_int as Atom, 8 as std::os::raw::c_int,
                        0 as std::os::raw::c_int,
                        title.as_mut_ptr() as *mut std::os::raw::c_uchar,
                        strlen(title.as_mut_ptr()) as std::os::raw::c_int);
        set_title = 0 as std::os::raw::c_int
    }
    XSync(dpy, 0 as std::os::raw::c_int);
}
unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: * mut * mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut xswa: crate::XSetWindowAttributes =
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
    let mut event: crate::_XEvent = _XEvent{type_0: 0,};
    let mut str: crate::XTextProperty =
        XTextProperty{value: 0 as *mut std::os::raw::c_uchar,
                      encoding: 0,
                      format: 0,
                      nitems: 0,};
    let mut sizeh: * mut crate::XSizeHints = 0 as *mut XSizeHints;
    let mut ch: * mut crate::XClassHint = 0 as *mut XClassHint;
    let mut buttonpressed: i32 = 0 as std::os::raw::c_int;
    let mut visible: i32 = 0 as std::os::raw::c_int;
    let mut scroll: i32 = 1 as std::os::raw::c_int;
    let mut title: [i8; 80] = [0; 80];
    let mut gcv: crate::XGCValues =
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
    let mut dpyname: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut source_geom_mask: i32 = 0 as std::os::raw::c_int;
    let mut dest_geom_mask: i32 = 0 as std::os::raw::c_int;
    let mut copy_from_src_mask: i32 = 0;
    let mut xpos: i32 = 0 as std::os::raw::c_int;
    let mut ypos: i32 = 0 as std::os::raw::c_int;
    let mut isdock: i32 = 0 as std::os::raw::c_int;
    atexit(Some(destroy_images));
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
    resize(width[1 as std::os::raw::c_int as usize],
           height[1 as std::os::raw::c_int as usize]);
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
                           event.xclient.data.l[0 as std::os::raw::c_int as usize] as
                               std::os::raw::c_ulong == wm_delete_window {
                        exit(0 as std::os::raw::c_int);
                    }
                }
                22 => {
                    if event.xconfigure.width !=
                           width[1 as std::os::raw::c_int as usize] ||
                           event.xconfigure.height !=
                               height[1 as std::os::raw::c_int as usize] {
                        resize(event.xconfigure.width,
                               event.xconfigure.height);
                    }
                }
                15 => {
                    /* VisibilityUnobscured, VisibilityPartiallyObscured, or VisibilityFullyObscured */
                    visible =
                        (event.xvisibility.state != 2 as std::os::raw::c_int) as
                            std::os::raw::c_int
                }
                3 => {
                    match XKeycodeToKeysym(dpy, event.xkey.keycode as KeyCode,
                                           0 as std::os::raw::c_int) {
                        65507 | 65508 => { scroll = 1 as std::os::raw::c_int }
                        _ => { }
                    }
                }
                2 => {
                    match XKeycodeToKeysym(dpy, event.xkey.keycode as KeyCode,
                                           0 as std::os::raw::c_int) {
                        65507 | 65508 => { scroll = 10 as std::os::raw::c_int }
                        43 | 61 | 65451 => {
                            if yzoom_flag == 0 { magx += 1 }
                            if xzoom_flag == 0 { magy += 1 }
                            yzoom_flag = 0 as std::os::raw::c_int;
                            xzoom_flag = yzoom_flag;
                            resize(width[1 as std::os::raw::c_int as usize],
                                   height[1 as std::os::raw::c_int as usize]);
                            set_title = 1 as std::os::raw::c_int
                        }
                        45 | 65453 => {
                            if yzoom_flag == 0 { magx -= 1 }
                            if xzoom_flag == 0 { magy -= 1 }
                            yzoom_flag = 0 as std::os::raw::c_int;
                            xzoom_flag = yzoom_flag;
                            if magx < 1 as std::os::raw::c_int {
                                magx = 1 as std::os::raw::c_int
                            }
                            if magy < 1 as std::os::raw::c_int {
                                magy = 1 as std::os::raw::c_int
                            }
                            resize(width[1 as std::os::raw::c_int as usize],
                                   height[1 as std::os::raw::c_int as usize]);
                            set_title = 1 as std::os::raw::c_int
                        }
                        65361 | 65430 => {
                            if flipxy != 0 {
                                if flipx != 0 {
                                    ygrab += scroll
                                } else { ygrab -= scroll }
                            } else if flipx != 0 {
                                xgrab += scroll
                            } else { xgrab -= scroll }
                        }
                        65363 | 65432 => {
                            if flipxy != 0 {
                                if flipx != 0 {
                                    ygrab -= scroll
                                } else { ygrab += scroll }
                            } else if flipx != 0 {
                                xgrab -= scroll
                            } else { xgrab += scroll }
                        }
                        65362 | 65431 => {
                            if flipxy != 0 {
                                if flipy != 0 {
                                    xgrab -= scroll
                                } else { xgrab += scroll }
                            } else if flipy != 0 {
                                ygrab += scroll
                            } else { ygrab -= scroll }
                        }
                        65364 | 65433 => {
                            if flipxy != 0 {
                                if flipy != 0 {
                                    xgrab += scroll
                                } else { xgrab -= scroll }
                            } else if flipy != 0 {
                                ygrab -= scroll
                            } else { ygrab += scroll }
                        }
                        120 => {
                            flipx = (flipx == 0) as std::os::raw::c_int;
                            set_title = 1 as std::os::raw::c_int
                        }
                        121 => {
                            flipy = (flipy == 0) as std::os::raw::c_int;
                            set_title = 1 as std::os::raw::c_int
                        }
                        122 => {
                            if flipx ^ flipy ^ flipxy != 0 {
                                flipx = (flipx == 0) as std::os::raw::c_int;
                                flipy = (flipy == 0) as std::os::raw::c_int
                            }
                            flipxy = (flipxy == 0) as std::os::raw::c_int;
                            resize(width[1 as std::os::raw::c_int as usize],
                                   height[1 as std::os::raw::c_int as usize]);
                            set_title = 1 as std::os::raw::c_int
                        }
                        119 => {
                            xzoom_flag = 1 as std::os::raw::c_int;
                            yzoom_flag = 0 as std::os::raw::c_int
                        }
                        104 => {
                            yzoom_flag = 1 as std::os::raw::c_int;
                            xzoom_flag = 0 as std::os::raw::c_int
                        }
                        103 => {
                            gridx = (gridx == 0) as std::os::raw::c_int;
                            gridy = (gridy == 0) as std::os::raw::c_int
                        }
                        100 => {
                            delay_index += 1;
                            if delay_index >= 5 as std::os::raw::c_int {
                                delay_index = 0 as std::os::raw::c_int
                            }
                            delay = delays[delay_index as usize];
                            sprintf(title.as_mut_ptr(),
                                    b"delay = %d ms\x00" as *const u8 as
                                        *const std::os::raw::c_char,
                                    delay / 1000 as std::os::raw::c_int);
                            XChangeProperty(dpy, win,
                                            39 as std::os::raw::c_int as Atom,
                                            31 as std::os::raw::c_int as Atom,
                                            8 as std::os::raw::c_int,
                                            0 as std::os::raw::c_int,
                                            title.as_mut_ptr() as
                                                *mut std::os::raw::c_uchar,
                                            strlen(title.as_mut_ptr()) as
                                                std::os::raw::c_int);
                            signal(14 as std::os::raw::c_int,
                                   Some(timeout_func));
                            alarm(2 as std::os::raw::c_int as std::os::raw::c_uint);
                        }
                        113 => { exit(0 as std::os::raw::c_int); }
                        _ => { }
                    }
                }
                4 => {
                    xgrab = event.xbutton.x_root;
                    ygrab = event.xbutton.y_root;
                    XDefineCursor(dpy, win, when_button);
                    buttonpressed = 1 as std::os::raw::c_int
                }
                5 => {
                    /*
				xgrab = event.xbutton.x_root - width[SRC]/2;
				ygrab = event.xbutton.y_root - height[SRC]/2;
				*/
                    XDefineCursor(dpy, win, crosshair);
                    buttonpressed = 0 as std::os::raw::c_int
                }
                6 => {
                    if buttonpressed != 0 {
                        xgrab = event.xmotion.x_root;
                        ygrab = event.xmotion.y_root
                    }
                }
                21 | _ => { }
            }
            /* trying XShmGetImage when part of the rect is
			   not on the screen will fail LOUDLY..
			   we have to veryfy this after anything that may
			   may modified xgrab or ygrab or the size of
			   the source ximage */
            if xgrab < 0 as std::os::raw::c_int { xgrab = 0 as std::os::raw::c_int }
            if xgrab > (*scr).width - width[0 as std::os::raw::c_int as usize] {
                xgrab = (*scr).width - width[0 as std::os::raw::c_int as usize]
            }
            if ygrab < 0 as std::os::raw::c_int { ygrab = 0 as std::os::raw::c_int }
            if ygrab > (*scr).height - height[0 as std::os::raw::c_int as usize] {
                ygrab = (*scr).height - height[0 as std::os::raw::c_int as usize]
            }
        }
        if visible != 0 { xzoom(buttonpressed); }
        if buttonpressed == 0 && delay > 0 as std::os::raw::c_int {
            usleep(delay as __useconds_t);
        }
    };
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

