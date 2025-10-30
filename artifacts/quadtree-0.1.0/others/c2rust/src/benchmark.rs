use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    static mut stdout: *mut FILE;
    fn fflush(__stream: *mut FILE) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn clock() -> clock_t;
    fn time(__timer: *mut time_t) -> time_t;
    fn rand() -> libc::c_int;
    fn srand(__seed: libc::c_uint);
    fn quadtree_new(
        minx: libc::c_double,
        miny: libc::c_double,
        maxx: libc::c_double,
        maxy: libc::c_double,
    ) -> *mut quadtree_t;
    fn quadtree_free(tree: *mut quadtree_t);
    fn quadtree_insert(
        tree: *mut quadtree_t,
        x: libc::c_double,
        y: libc::c_double,
        key: *mut libc::c_void,
    ) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type __clock_t = libc::c_long;
pub type __time_t = libc::c_long;
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
pub type clock_t = __clock_t;
pub type time_t = __time_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct quadtree_point {
    pub x: libc::c_double,
    pub y: libc::c_double,
}
pub type quadtree_point_t = quadtree_point;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct quadtree_bounds {
    pub nw: *mut quadtree_point_t,
    pub se: *mut quadtree_point_t,
    pub width: libc::c_double,
    pub height: libc::c_double,
}
pub type quadtree_bounds_t = quadtree_bounds;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct quadtree_node {
    pub ne: *mut quadtree_node,
    pub nw: *mut quadtree_node,
    pub se: *mut quadtree_node,
    pub sw: *mut quadtree_node,
    pub bounds: *mut quadtree_bounds_t,
    pub point: *mut quadtree_point_t,
    pub key: *mut libc::c_void,
}
pub type quadtree_node_t = quadtree_node;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct quadtree {
    pub root: *mut quadtree_node_t,
    pub key_free: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    pub length: libc::c_uint,
}
pub type quadtree_t = quadtree;
unsafe extern "C" fn bench(
    mut bm: Option::<unsafe extern "C" fn() -> ()>,
    mut label: *mut libc::c_char,
) {
    printf(b" %18s\0" as *const u8 as *const libc::c_char, label);
    fflush(stdout);
    ::core::mem::transmute::<_, fn()>(bm.expect("non-null function pointer"))();
}
static mut nodes: libc::c_int = 10000 as libc::c_int;
static mut startTime: clock_t = 0;
unsafe extern "C" fn start() {
    startTime = clock();
}
unsafe extern "C" fn stop() {
    let mut duration: libc::c_float = (clock() - startTime) as libc::c_float
        / 1000000 as libc::c_int as __clock_t as libc::c_float;
    printf(
        b": \x1B[32m%.4f\x1B[0ms\n\0" as *const u8 as *const libc::c_char,
        duration as libc::c_double,
    );
}
unsafe extern "C" fn mark_insert() {
    let mut n: libc::c_int = nodes;
    let mut val: libc::c_int = 10 as libc::c_int;
    let mut tree: *mut quadtree_t = quadtree_new(
        0 as libc::c_int as libc::c_double,
        0 as libc::c_int as libc::c_double,
        1000 as libc::c_int as libc::c_double,
        1000 as libc::c_int as libc::c_double,
    );
    let mut x: libc::c_double = 0.;
    let mut y: libc::c_double = 0.;
    start();
    loop {
        let fresh0 = n;
        n = n - 1;
        if !(fresh0 != 0) {
            break;
        }
        x = (rand() % 1000 as libc::c_int) as libc::c_double;
        y = (rand() % 1000 as libc::c_int) as libc::c_double;
        quadtree_insert(tree, x, y, &mut val as *mut libc::c_int as *mut libc::c_void);
    }
    stop();
    printf(
        b"  %18s %i\n\0" as *const u8 as *const libc::c_char,
        b"length:\0" as *const u8 as *const libc::c_char,
        (*tree).length,
    );
    quadtree_free(tree);
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *const libc::c_char,
) -> libc::c_int {
    srand(time(0 as *mut time_t) as libc::c_uint);
    bench(
        Some(
            ::core::mem::transmute::<
                unsafe extern "C" fn() -> (),
                unsafe extern "C" fn() -> (),
            >(mark_insert),
        ),
        b"insertion\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
    );
    return 0 as libc::c_int;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in ::std::env::args() {
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
                args.as_mut_ptr() as *mut *const libc::c_char,
            ) as i32,
        )
    }
}
