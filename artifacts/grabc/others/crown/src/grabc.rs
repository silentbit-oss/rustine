use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    pub type _XGC;
    pub type _XDisplay;
    static mut stdout: *mut FILE;
    static mut stderr: *mut FILE;
    fn fflush(__stream: *mut FILE) -> libc::c_int;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn vfprintf(
        _: *mut FILE,
        _: *const libc::c_char,
        _: ::core::ffi::VaList,
    ) -> libc::c_int;
    fn strtol(
        _: *const libc::c_char,
        _: *mut *mut libc::c_char,
        _: libc::c_int,
    ) -> libc::c_long;
    fn exit(_: libc::c_int) -> !;
    fn strncmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn XGetImage(
        _: *mut Display,
        _: Drawable,
        _: libc::c_int,
        _: libc::c_int,
        _: libc::c_uint,
        _: libc::c_uint,
        _: libc::c_ulong,
        _: libc::c_int,
    ) -> *mut XImage;
    fn XOpenDisplay(_: *const libc::c_char) -> *mut Display;
    fn XCreateFontCursor(_: *mut Display, _: libc::c_uint) -> Cursor;
    fn XRootWindow(_: *mut Display, _: libc::c_int) -> Window;
    fn XSetErrorHandler(_: XErrorHandler) -> XErrorHandler;
    fn XAllowEvents(_: *mut Display, _: libc::c_int, _: Time) -> libc::c_int;
    fn XDefaultScreen(_: *mut Display) -> libc::c_int;
    fn XGetWindowAttributes(
        _: *mut Display,
        _: Window,
        _: *mut XWindowAttributes,
    ) -> libc::c_int;
    fn XGrabPointer(
        _: *mut Display,
        _: Window,
        _: libc::c_int,
        _: libc::c_uint,
        _: libc::c_int,
        _: libc::c_int,
        _: Window,
        _: Cursor,
        _: Time,
    ) -> libc::c_int;
    fn XParseGeometry(
        _: *const libc::c_char,
        _: *mut libc::c_int,
        _: *mut libc::c_int,
        _: *mut libc::c_uint,
        _: *mut libc::c_uint,
    ) -> libc::c_int;
    fn XQueryColor(_: *mut Display, _: Colormap, _: *mut XColor) -> libc::c_int;
    fn XTranslateCoordinates(
        _: *mut Display,
        _: Window,
        _: Window,
        _: libc::c_int,
        _: libc::c_int,
        _: *mut libc::c_int,
        _: *mut libc::c_int,
        _: *mut Window,
    ) -> libc::c_int;
    fn XUngrabPointer(_: *mut Display, _: Time) -> libc::c_int;
    fn XWindowEvent(
        _: *mut Display,
        _: Window,
        _: libc::c_long,
        _: *mut XEvent,
    ) -> libc::c_int;
}
pub type __builtin_va_list = [__va_list_tag; 1];
#[derive(Copy, Clone)]
#[repr(C)]
pub struct __va_list_tag {
    pub gp_offset: libc::c_uint,
    pub fp_offset: libc::c_uint,
    pub overflow_arg_area: *mut libc::c_void,
    pub reg_save_area: *mut libc::c_void,
}
pub type size_t = libc::c_ulong;
pub type __gnuc_va_list = __builtin_va_list;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type _IO_lock_t = ();
pub type FILE = _IO_FILE;
pub type va_list = __gnuc_va_list;
pub type XID = libc::c_ulong;
pub type Atom = libc::c_ulong;
pub type VisualID = libc::c_ulong;
pub type Time = libc::c_ulong;
pub type Window = XID;
pub type Drawable = XID;
pub type Cursor = XID;
pub type Colormap = XID;
pub type XPointer = *mut libc::c_char;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _XExtData {
    pub number: libc::c_int,
    pub next: *mut _XExtData,
    pub free_private: Option::<unsafe extern "C" fn(*mut _XExtData) -> libc::c_int>,
    pub private_data: XPointer,
}
pub type XExtData = _XExtData;
pub type GC = *mut _XGC;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Visual {
    pub ext_data: *mut XExtData,
    pub visualid: VisualID,
    pub class: libc::c_int,
    pub red_mask: libc::c_ulong,
    pub green_mask: libc::c_ulong,
    pub blue_mask: libc::c_ulong,
    pub bits_per_rgb: libc::c_int,
    pub map_entries: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Depth {
    pub depth: libc::c_int,
    pub nvisuals: libc::c_int,
    pub visuals: *mut Visual,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct Screen {
    pub ext_data: *mut XExtData,
    pub display: *mut _XDisplay,
    pub root: Window,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub mwidth: libc::c_int,
    pub mheight: libc::c_int,
    pub ndepths: libc::c_int,
    pub depths: *mut Depth,
    pub root_depth: libc::c_int,
    pub root_visual: *mut Visual,
    pub default_gc: GC,
    pub cmap: Colormap,
    pub white_pixel: libc::c_ulong,
    pub black_pixel: libc::c_ulong,
    pub max_maps: libc::c_int,
    pub min_maps: libc::c_int,
    pub backing_store: libc::c_int,
    pub save_unders: libc::c_int,
    pub root_input_mask: libc::c_long,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XWindowAttributes {
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub border_width: libc::c_int,
    pub depth: libc::c_int,
    pub visual: *mut Visual,
    pub root: Window,
    pub class: libc::c_int,
    pub bit_gravity: libc::c_int,
    pub win_gravity: libc::c_int,
    pub backing_store: libc::c_int,
    pub backing_planes: libc::c_ulong,
    pub backing_pixel: libc::c_ulong,
    pub save_under: libc::c_int,
    pub colormap: Colormap,
    pub map_installed: libc::c_int,
    pub map_state: libc::c_int,
    pub all_event_masks: libc::c_long,
    pub your_event_mask: libc::c_long,
    pub do_not_propagate_mask: libc::c_long,
    pub override_redirect: libc::c_int,
    pub screen: *mut Screen,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _XImage {
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub xoffset: libc::c_int,
    pub format: libc::c_int,
    pub data: *mut libc::c_char,
    pub byte_order: libc::c_int,
    pub bitmap_unit: libc::c_int,
    pub bitmap_bit_order: libc::c_int,
    pub bitmap_pad: libc::c_int,
    pub depth: libc::c_int,
    pub bytes_per_line: libc::c_int,
    pub bits_per_pixel: libc::c_int,
    pub red_mask: libc::c_ulong,
    pub green_mask: libc::c_ulong,
    pub blue_mask: libc::c_ulong,
    pub obdata: XPointer,
    pub f: funcs,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct funcs {
    pub create_image: Option::<
        unsafe extern "C" fn(
            *mut _XDisplay,
            *mut Visual,
            libc::c_uint,
            libc::c_int,
            libc::c_int,
            *mut libc::c_char,
            libc::c_uint,
            libc::c_uint,
            libc::c_int,
            libc::c_int,
        ) -> *mut _XImage,
    >,
    pub destroy_image: Option::<unsafe extern "C" fn(*mut _XImage) -> libc::c_int>,
    pub get_pixel: Option::<
        unsafe extern "C" fn(*mut _XImage, libc::c_int, libc::c_int) -> libc::c_ulong,
    >,
    pub put_pixel: Option::<
        unsafe extern "C" fn(
            *mut _XImage,
            libc::c_int,
            libc::c_int,
            libc::c_ulong,
        ) -> libc::c_int,
    >,
    pub sub_image: Option::<
        unsafe extern "C" fn(
            *mut _XImage,
            libc::c_int,
            libc::c_int,
            libc::c_uint,
            libc::c_uint,
        ) -> *mut _XImage,
    >,
    pub add_pixel: Option::<
        unsafe extern "C" fn(*mut _XImage, libc::c_long) -> libc::c_int,
    >,
}
pub type XImage = _XImage;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XColor {
    pub pixel: libc::c_ulong,
    pub red: libc::c_ushort,
    pub green: libc::c_ushort,
    pub blue: libc::c_ushort,
    pub flags: libc::c_char,
    pub pad: libc::c_char,
}
pub type Display = _XDisplay;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XKeyEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub x_root: libc::c_int,
    pub y_root: libc::c_int,
    pub state: libc::c_uint,
    pub keycode: libc::c_uint,
    pub same_screen: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XButtonEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub x_root: libc::c_int,
    pub y_root: libc::c_int,
    pub state: libc::c_uint,
    pub button: libc::c_uint,
    pub same_screen: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMotionEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub x_root: libc::c_int,
    pub y_root: libc::c_int,
    pub state: libc::c_uint,
    pub is_hint: libc::c_char,
    pub same_screen: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCrossingEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub root: Window,
    pub subwindow: Window,
    pub time: Time,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub x_root: libc::c_int,
    pub y_root: libc::c_int,
    pub mode: libc::c_int,
    pub detail: libc::c_int,
    pub same_screen: libc::c_int,
    pub focus: libc::c_int,
    pub state: libc::c_uint,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XFocusChangeEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub mode: libc::c_int,
    pub detail: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XKeymapEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub key_vector: [libc::c_char; 32],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XExposeEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub count: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGraphicsExposeEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub drawable: Drawable,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub count: libc::c_int,
    pub major_code: libc::c_int,
    pub minor_code: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XNoExposeEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub drawable: Drawable,
    pub major_code: libc::c_int,
    pub minor_code: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XVisibilityEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub state: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCreateWindowEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub border_width: libc::c_int,
    pub override_redirect: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XDestroyWindowEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XUnmapEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub from_configure: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMapEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub override_redirect: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMapRequestEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XReparentEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub parent: Window,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub override_redirect: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XConfigureEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub border_width: libc::c_int,
    pub above: Window,
    pub override_redirect: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGravityEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub x: libc::c_int,
    pub y: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XResizeRequestEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub width: libc::c_int,
    pub height: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XConfigureRequestEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub x: libc::c_int,
    pub y: libc::c_int,
    pub width: libc::c_int,
    pub height: libc::c_int,
    pub border_width: libc::c_int,
    pub above: Window,
    pub detail: libc::c_int,
    pub value_mask: libc::c_ulong,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCirculateEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub event: Window,
    pub window: Window,
    pub place: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XCirculateRequestEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub parent: Window,
    pub window: Window,
    pub place: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XPropertyEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub atom: Atom,
    pub time: Time,
    pub state: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionClearEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub selection: Atom,
    pub time: Time,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XSelectionRequestEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
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
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
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
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub colormap: Colormap,
    pub new: libc::c_int,
    pub state: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XClientMessageEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub message_type: Atom,
    pub format: libc::c_int,
    pub data: C2RustUnnamed,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed {
    pub b: [libc::c_char; 20],
    pub s: [libc::c_short; 10],
    pub l: [libc::c_long; 5],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XMappingEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
    pub request: libc::c_int,
    pub first_keycode: libc::c_int,
    pub count: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XErrorEvent {
    pub type_0: libc::c_int,
    pub display: *mut Display,
    pub resourceid: XID,
    pub serial: libc::c_ulong,
    pub error_code: libc::c_uchar,
    pub request_code: libc::c_uchar,
    pub minor_code: libc::c_uchar,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XAnyEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub window: Window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGenericEvent {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub extension: libc::c_int,
    pub evtype: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct XGenericEventCookie {
    pub type_0: libc::c_int,
    pub serial: libc::c_ulong,
    pub send_event: libc::c_int,
    pub display: *mut Display,
    pub extension: libc::c_int,
    pub evtype: libc::c_int,
    pub cookie: libc::c_uint,
    pub data: *mut libc::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union _XEvent {
    pub type_0: libc::c_int,
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
    pub pad: [libc::c_long; 24],
}
pub type XEvent = _XEvent;
pub type XErrorHandler = Option::<
    unsafe extern "C" fn(*mut Display, *mut XErrorEvent) -> libc::c_int,
>;
static mut g_debug: libc::c_int = 0 as libc::c_int;
static mut g_print_in_hex: libc::c_int = 1 as libc::c_int;
static mut g_print_in_rgb: libc::c_int = 0 as libc::c_int;
static mut g_print_all_16_bits: libc::c_int = 0 as libc::c_int;
static mut g_window_id: Window = 0;
static mut g_loc_specified: libc::c_int = 0 as libc::c_int;
static mut g_x: libc::c_int = 1 as libc::c_int;
static mut g_y: libc::c_int = 1 as libc::c_int;
static mut g_width: libc::c_uint = 0 as libc::c_int as libc::c_uint;
static mut g_height: libc::c_uint = 0 as libc::c_int as libc::c_uint;
static mut g_cross_cursor: Cursor = 0;
unsafe extern "C" fn show_usage() {
    let mut p: *mut *mut libc::c_char = 0 as *mut *mut libc::c_char;
    static mut options: [*mut libc::c_char; 20] = [
        b" -v      - show version info\0" as *const u8 as *const libc::c_char
            as *mut libc::c_char,
        b" -h      - show this usage\0" as *const u8 as *const libc::c_char
            as *mut libc::c_char,
        b" -hex    - print pixel value as Hex on stdout\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b" -rgb    - print pixel value as RGB on stderr\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b" -W      - print the Window id at mouse click\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b" -w id   - window id in hex, use -l +x+y\0" as *const u8 as *const libc::c_char
            as *mut libc::c_char,
        b" -l +x+y - pixel co-ordinate. requires window id\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b" -d      - show debug messages\0" as *const u8 as *const libc::c_char
            as *mut libc::c_char,
        b" -a      - Print all 16 bits RGB components of color\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b"           Default is high order 8 bits of components\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b"Example:\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"* Print pixel color in hex on stdout:\0" as *const u8 as *const libc::c_char
            as *mut libc::c_char,
        b"   $ grabc\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"* Show usage:\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"   $ grabc -h\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"* Print Window Id (Note the upper case W):\0" as *const u8
            as *const libc::c_char as *mut libc::c_char,
        b"   $ grabc -W\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"* Print pixel color of Window iwith id 0x13234 at location 10,20\0"
            as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"   $ grabc -w 0x13234 -l +10+20\0" as *const u8 as *const libc::c_char
            as *mut libc::c_char,
        0 as *const libc::c_void as *mut libc::c_void as *mut libc::c_char,
    ];
    printf(b"\n\0" as *const u8 as *const libc::c_char);
    printf(
        b"grabc v%s\n\0" as *const u8 as *const libc::c_char,
        b"1.0.2\0" as *const u8 as *const libc::c_char,
    );
    printf(
        b"A program to identify a pixel color of an X Window\n\0" as *const u8
            as *const libc::c_char,
    );
    printf(
        b"by muquit@muquit.com https://www.muquit.com/\n\n\0" as *const u8
            as *const libc::c_char,
    );
    printf(b"Usage: grabc [options]\n\0" as *const u8 as *const libc::c_char);
    printf(b"Where the options are:\n\0" as *const u8 as *const libc::c_char);
    p = options.as_mut_ptr();
    while !(*p).is_null() {
        fprintf(stdout, b"%s\n\0" as *const u8 as *const libc::c_char, *p);
        fflush(stdout);
        p = p.offset(1);
        p;
    }std::intrinsics::assume((*p).addr() == 0);
}
unsafe extern "C" fn log_debug(mut fmt: *const libc::c_char, mut args: ...) {
    let mut args_0: ::core::ffi::VaListImpl;
    if g_debug == 0 {
        return;
    }
    args_0 = args.clone();
    fprintf(stderr, b"[Debug]: \0" as *const u8 as *const libc::c_char);
    vfprintf(stderr, fmt, args_0.as_va_list());
    fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
}
unsafe extern "C" fn get_cross_cursor(mut display: *mut Display) -> Cursor {
    if g_cross_cursor == 0 as *mut libc::c_void as Cursor {
        g_cross_cursor = XCreateFontCursor(display, 130 as libc::c_int as libc::c_uint);
        if g_cross_cursor == 0 as *mut libc::c_void as Cursor {
            fprintf(
                stderr,
                b"ERROR: Failed to create Cross Cursor!\n\0" as *const u8
                    as *const libc::c_char,
            );
            exit(1 as libc::c_int);
        }
    }
    return g_cross_cursor;
}
unsafe extern "C" fn select_window(
    mut display: *mut Display,
    mut x: *mut libc::c_int,
    mut y: *mut libc::c_int,
) -> Window {
    let mut target_cursor: Cursor = 0;
    let mut status: libc::c_int = 0;
    let mut target_window: Window = 0;
    let mut root_window: Window = 0;
    let mut event: XEvent = _XEvent { type_0: 0 };
    if g_window_id != 0 as *mut libc::c_void as Window && g_loc_specified != 0 {
        log_debug(
            b"Returning passing window: %lx\0" as *const u8 as *const libc::c_char,
            g_window_id,
        );
        *x = g_x;
        *y = g_y;
        return g_window_id;
    }
    target_window = 0 as *mut libc::c_void as Window;
    target_cursor = get_cross_cursor(display);
    root_window = {let crown_promoted_local_0 = XDefaultScreen(display);XRootWindow(display, crown_promoted_local_0)};
    status = XGrabPointer(
        display,
        root_window,
        0 as libc::c_int,
        ((1 as libc::c_long) << 2 as libc::c_int) as libc::c_uint,
        0 as libc::c_int,
        1 as libc::c_int,
        root_window,
        target_cursor,
        0 as libc::c_long as Time,
    );
    if status == 0 as libc::c_int {
        XAllowEvents(display, 1 as libc::c_int, 0 as libc::c_long as Time);
        XWindowEvent(
            display,
            root_window,
            (1 as libc::c_long) << 2 as libc::c_int,
            &raw mut event,
        );
        let mut subwindow: Window = event.xbutton.subwindow;
        if event.type_0 == 4 as libc::c_int {
            target_window = findSubWindow(
                display,
                root_window,
                subwindow,
                &raw mut event.xbutton.x,
                &raw mut event.xbutton.y,
            );
            if target_window == 0 as *mut libc::c_void as Window {
                fprintf(
                    stderr,
                    b"ERROR: Failed to get target window, getting root window!\n\0"
                        as *const u8 as *const libc::c_char,
                );
                target_window = root_window;
            }
            if g_loc_specified == 0 {
                XUngrabPointer(display, 0 as libc::c_long as Time);
            }
        }
    } else {
        fprintf(
            stderr,
            b"ERROR: Failed to grab mouse pointer!\n\0" as *const u8
                as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    }
    *x = event.xbutton.x;
    *y = event.xbutton.y;
    return target_window;
}
unsafe extern "C" fn findSubWindow(
    mut display: *mut Display,
    mut top_window: Window,
    mut window_to_check: Window,
    mut x: *mut libc::c_int,
    mut y: *mut libc::c_int,
) -> Window {
    let mut newx: libc::c_int = 0;
    let mut newy: libc::c_int = 0;
    let mut window: Window = 0;
    if top_window == 0 as *mut libc::c_void as Window {
        return 0 as *mut libc::c_void as Window;
    }
    if window_to_check == 0 as *mut libc::c_void as Window {
        return 0 as *mut libc::c_void as Window;
    }
    window = window_to_check;
    while XTranslateCoordinates(
        display,
        top_window,
        window_to_check,
        *x,
        *y,
        &raw mut newx,
        &raw mut newy,
        &raw mut window,
    ) != 0 as libc::c_int && window != 0 as *mut libc::c_void as Window
    {
        if window != 0 as *mut libc::c_void as Window {
            top_window = window_to_check;
            window_to_check = window;
            *x = newx;
            *y = newy;
        }
    }
    if window == 0 as *mut libc::c_void as Window {
        window = window_to_check;
    }
    *x = newx;
    *y = newy;
    return window;
}
unsafe extern "C" fn get_window_color(
    mut display: *mut Display,
    mut color: *mut XColor,
) -> Window {
    let mut root_window: Window = 0;
    let mut target_window: Window = 0;
    let mut ximage: *mut XImage = 0 as *mut XImage;
    let mut x: libc::c_int = 0;
    let mut y: libc::c_int = 0;
    let mut status: libc::c_int = 0;
    root_window = {let crown_promoted_local_0 = XDefaultScreen(display);XRootWindow(display, crown_promoted_local_0)};
    target_window = select_window(display, &raw mut x, &raw mut y);
    log_debug(
        b"  Root Window Id: 0x%08lx\0" as *const u8 as *const libc::c_char,
        root_window,
    );
    log_debug(
        b"Target Window Id: 0x%08lx  X,Y: +%d+%d\0" as *const u8 as *const libc::c_char,
        target_window,
        x,
        y,
    );
    if target_window == 0 as *mut libc::c_void as Window {
        return 0 as *mut libc::c_void as Window;
    }
    ximage = XGetImage(
        display,
        target_window,
        x,
        y,
        1 as libc::c_int as libc::c_uint,
        1 as libc::c_int as libc::c_uint,
        !(0 as libc::c_long) as libc::c_ulong,
        2 as libc::c_int,
    );
    if ximage.is_null() {std::intrinsics::assume((ximage).addr() == 0);
        log_debug(
            b"Could not get XImage from Window: 0x%08lx\0" as *const u8
                as *const libc::c_char,
            target_window,
        );
        log_debug(
            b"Trying to get XImage from root window: 0x%08lx\0" as *const u8
                as *const libc::c_char,
            root_window,
        );
        ximage = XGetImage(
            display,
            root_window,
            x,
            y,
            1 as libc::c_int as libc::c_uint,
            1 as libc::c_int as libc::c_uint,
            !(0 as libc::c_long) as libc::c_ulong,
            2 as libc::c_int,
        );
        if ximage.is_null() {std::intrinsics::assume((ximage).addr() == 0);
            log_debug(
                b"Could not get XImage from target or root window\0" as *const u8
                    as *const libc::c_char,
            );
            return 0 as *mut libc::c_void as Window;
        } else {
            log_debug(
                b"OK successfully got XImage from root window\0" as *const u8
                    as *const libc::c_char,
            );
            target_window = root_window;
        }
    }
    (*color)
        .pixel = (Some(((*ximage).f.get_pixel).expect("non-null function pointer")))
        .expect("non-null function pointer")(ximage, 0 as libc::c_int, 0 as libc::c_int);
    (Some(((*ximage).f.destroy_image).expect("non-null function pointer")))
        .expect("non-null function pointer")(ximage);
    return target_window;
}
unsafe extern "C" fn MXError(
    mut display: *mut Display,
    mut error: *mut XErrorEvent,
) -> libc::c_int {
    let mut xerrcode: libc::c_int = 0;
    xerrcode = (*error).error_code as libc::c_int;
    if xerrcode == 11 as libc::c_int
        || xerrcode == 10 as libc::c_int
            && (*error).request_code as libc::c_int == 88 as libc::c_int
    {
        return 0 as libc::c_int
    } else {
        match (*error).request_code as libc::c_int {
            14 => {
                if (*error).error_code as libc::c_int == 9 as libc::c_int {
                    return 0 as libc::c_int;
                }
            }
            3 | 15 => {
                if (*error).error_code as libc::c_int == 3 as libc::c_int {
                    return 0 as libc::c_int;
                }
            }
            91 => {
                if (*error).error_code as libc::c_int == 2 as libc::c_int {
                    return 0 as libc::c_int;
                }
            }
            _ => {}
        }
    }
    return 1 as libc::c_int;
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut display: *mut Display = 0 as *mut Display;
    let mut x: libc::c_int = 0;
    let mut y: libc::c_int = 0;
    let mut status: libc::c_int = 0;
    let mut color: XColor = XColor {
        pixel: 0,
        red: 0,
        green: 0,
        blue: 0,
        flags: 0,
        pad: 0,
    };
    let mut rc: libc::c_int = 0;
    let mut i: libc::c_int = 0;
    let mut r: libc::c_int = 0;
    let mut g: libc::c_int = 0;
    let mut b: libc::c_int = 0;
    let mut window_id: Window = 0;
    let mut target_window: Window = 0;
    let mut window_attributes: XWindowAttributes = XWindowAttributes {
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        border_width: 0,
        depth: 0,
        visual: 0 as *mut Visual,
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
        screen: 0 as *mut Screen,
    };
    let mut option: *mut libc::c_char = 0 as *mut libc::c_char;
    i = 1 as libc::c_int;
    while i < argc {
        option = *argv.offset(i as isize);
        match *option.offset(1 as libc::c_int as isize) as libc::c_int {
            97 => {
                g_print_all_16_bits = 1 as libc::c_int;
            }
            100 => {
                g_debug = 1 as libc::c_int;
            }
            104 => {
                if strncmp(
                    b"hex\0" as *const u8 as *const libc::c_char,
                    option.offset(1 as libc::c_int as isize),
                    3 as libc::c_int as libc::c_ulong,
                ) == 0 as libc::c_int
                {
                    g_print_in_hex = 1 as libc::c_int;
                } else {
                    show_usage();
                    return 1 as libc::c_int;
                }
            }
            114 => {
                if strncmp(
                    b"rgb\0" as *const u8 as *const libc::c_char,
                    option.offset(1 as libc::c_int as isize),
                    3 as libc::c_int as libc::c_ulong,
                ) == 0 as libc::c_int
                {
                    g_print_in_rgb = 1 as libc::c_int;
                }
            }
            119 => {
                if *option as libc::c_int == '-' as i32 {
                    i += 1;
                    i;
                    if i == argc {
                        fprintf(
                            stderr,
                            b"ERROR: Missing Window id\n\0" as *const u8
                                as *const libc::c_char,
                        );
                        return 1 as libc::c_int;
                    }
                }
                g_window_id = strtol(
                    *argv.offset(i as isize),
                    0 as *mut *mut libc::c_char,
                    16 as libc::c_int,
                ) as Window;
            }
            87 => {
                display = XOpenDisplay(0 as *mut libc::c_void as *mut libc::c_char);
                if display.is_null() {/*std::intrinsics::assume((display).addr() == 0);*/
                    fprintf(
                        stderr,
                        b"ERROR: Could not open Display\n\0" as *const u8
                            as *const libc::c_char,
                    );
                    return 1 as libc::c_int;
                }
                let mut window: Window = select_window(display, &raw mut x, &raw mut y);
                if window != 0 as *mut libc::c_void as Window {
                    log_debug(
                        b"Window ID: 0x%08lx\0" as *const u8 as *const libc::c_char,
                        window,
                    );
                    fprintf(
                        stdout,
                        b"0x%lx\n\0" as *const u8 as *const libc::c_char,
                        window,
                    );
                }
                return 1 as libc::c_int;
            }
            108 => {
                if *option as libc::c_int == '-' as i32 {
                    i += 1;
                    i;
                    if i == argc {
                        fprintf(
                            stderr,
                            b"ERROR: Missing location +x+y\n\0" as *const u8
                                as *const libc::c_char,
                        );
                        return 1 as libc::c_int;
                    }
                }
                rc = XParseGeometry(
                    *argv.offset(i as isize),
                    &raw mut g_x,
                    &raw mut g_y,
                    &raw mut g_width,
                    &raw mut g_height,
                );
                if rc == 0 as libc::c_int {
                    fprintf(
                        stderr,
                        b"ERROR: Could not parse location: %s\n\0" as *const u8
                            as *const libc::c_char,
                        *argv.offset(i as isize),
                    );
                    fprintf(
                        stderr,
                        b"Example: -l +10+20\n\0" as *const u8 as *const libc::c_char,
                    );
                    return 1 as libc::c_int;
                }
                g_loc_specified = 1 as libc::c_int;
            }
            118 => {
                fprintf(
                    stderr,
                    b"grabc v%s\n\0" as *const u8 as *const libc::c_char,
                    b"1.0.2\0" as *const u8 as *const libc::c_char,
                );
                return 1 as libc::c_int;
            }
            _ => {}
        }
        i += 1;
        i;
    }
    if g_loc_specified != 0 && g_window_id == 0 as *mut libc::c_void as Window {
        fprintf(
            stderr,
            b"ERROR: Please specify window id with -w in hex to use this option\n\0"
                as *const u8 as *const libc::c_char,
        );
        fprintf(
            stderr,
            b"Use -W option to find the Window Id\n\0" as *const u8
                as *const libc::c_char,
        );
        return 1 as libc::c_int;
    }
    display = XOpenDisplay(0 as *mut libc::c_void as *mut libc::c_char);
    XSetErrorHandler(
        Some(
            MXError
                as unsafe extern "C" fn(*mut Display, *mut XErrorEvent) -> libc::c_int,
        ),
    );
    if display.is_null() {/*std::intrinsics::assume((display).addr() == 0);*/
        fprintf(
            stderr,
            b"ERROR: Failed to open DISPLAY!\n\0" as *const u8 as *const libc::c_char,
        );
        exit(1 as libc::c_int);
    }
    target_window = get_window_color(display, &raw mut color);
    if target_window != 0 as *mut libc::c_void as Window {
        status = XGetWindowAttributes(display, target_window, &raw mut window_attributes);
        if status == 0 as libc::c_int || window_attributes.map_state != 2 as libc::c_int
        {
            fprintf(
                stderr,
                b"ERROR: Could not get Window Attributes\n\0" as *const u8
                    as *const libc::c_char,
            );
            return 1 as libc::c_int;
        }
        XQueryColor(display, window_attributes.colormap, &raw mut color);
        if g_print_all_16_bits != 0 {
            fprintf(
                stdout,
                b"#%04x%04x%04x\n\0" as *const u8 as *const libc::c_char,
                color.red as libc::c_uint,
                color.green as libc::c_uint,
                color.blue as libc::c_uint,
            );
            fflush(stdout);
            if g_print_in_rgb != 0 {
                fprintf(
                    stderr,
                    b"%d,%d,%d\n\0" as *const u8 as *const libc::c_char,
                    color.red as libc::c_uint,
                    color.green as libc::c_uint,
                    color.blue as libc::c_uint,
                );
            }
        } else {
            r = color.red as libc::c_int >> 8 as libc::c_int;
            g = color.green as libc::c_int >> 8 as libc::c_int;
            b = color.blue as libc::c_int >> 8 as libc::c_int;
            log_debug(
                b"Color: #%02x%02x%02x\0" as *const u8 as *const libc::c_char,
                r,
                g,
                b,
            );
            fprintf(
                stdout,
                b"#%02x%02x%02x\n\0" as *const u8 as *const libc::c_char,
                r,
                g,
                b,
            );
            fflush(stdout);
            if g_print_in_rgb != 0 {
                fprintf(
                    stderr,
                    b"%d,%d,%d\n\0" as *const u8 as *const libc::c_char,
                    r,
                    g,
                    b,
                );
            }
        }
    } else {
        fprintf(
            stderr,
            b"ERROR: Failed to grab color!\n\0" as *const u8 as *const libc::c_char,
        );
    }
    return 0 as libc::c_int;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in std::env::args() {
        args.push(
            (::std::ffi::CString::new(arg))
                .expect("Failed to convert argument into CString.")
                .into_raw(),
        );
    }
    args.push(::core::ptr::null_mut());
    unsafe {
        ::std::process::exit(
            main_0(
                (args.len() - 1) as libc::c_int,
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
unsafe extern "C" fn run_static_initializers() {
    g_window_id = 0 as *mut libc::c_void as Window;
    g_cross_cursor = 0 as *mut libc::c_void as Cursor;
}
#[used]
#[cfg_attr(target_os = "linux", link_section = ".init_array")]
#[cfg_attr(target_os = "windows", link_section = ".CRT$XIB")]
#[cfg_attr(target_os = "macos", link_section = "__DATA,__mod_init_func")]
static INIT_ARRAY: [unsafe extern "C" fn(); 1] = [run_static_initializers];
