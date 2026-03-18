use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn free(_: *mut libc::c_void);
    fn avl_create(
        compare_func_0: Option::<
            unsafe extern "C" fn(*const libc::c_void, *const libc::c_void) -> libc::c_int,
        >,
        destroy_func_0: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    ) -> *mut avltree;
    fn avl_destroy(avlt: *mut avltree);
    fn avl_find(avlt: *mut avltree, data: *mut libc::c_void) -> *mut avlnode;
    fn avl_print(
        avlt: *mut avltree,
        print_func: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    );
    fn avl_insert(avlt: *mut avltree, data: *mut libc::c_void) -> *mut avlnode;
    fn avl_delete(
        avlt: *mut avltree,
        node: *mut avlnode,
        keep: libc::c_int,
    ) -> *mut libc::c_void;
    fn makedata(key: libc::c_int) -> *mut mydata;
    fn compare_func(d1: *const libc::c_void, d2: *const libc::c_void) -> libc::c_int;
    fn destroy_func(d: *mut libc::c_void);
    fn print_char_func(d: *mut libc::c_void);
}
pub type size_t = libc::c_ulong;
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
#[derive(Copy, Clone)]
#[repr(C)]
pub struct avlnode {
    pub left: *mut avlnode,
    pub right: *mut avlnode,
    pub parent: *mut avlnode,
    pub bf: libc::c_char,
    pub data: *mut libc::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct avltree {
    pub compare: Option::<
        unsafe extern "C" fn(*const libc::c_void, *const libc::c_void) -> libc::c_int,
    >,
    pub print: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    pub destroy: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    pub root: avlnode,
    pub nil: avlnode,
    pub min: *mut avlnode,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct mydata {
    pub key: libc::c_int,
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    avlt = avl_create(
        Some(
            compare_func
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
        Some(destroy_func as unsafe extern "C" fn(*mut libc::c_void) -> ()),
    );
    if avlt.is_null() {
        fprintf(
            stderr,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
        return 1 as libc::c_int;
    }
    let mut a: [libc::c_char; 10] = [
        'R' as i32 as libc::c_char,
        'E' as i32 as libc::c_char,
        'D' as i32 as libc::c_char,
        'S' as i32 as libc::c_char,
        'O' as i32 as libc::c_char,
        'X' as i32 as libc::c_char,
        'C' as i32 as libc::c_char,
        'U' as i32 as libc::c_char,
        'B' as i32 as libc::c_char,
        'T' as i32 as libc::c_char,
    ];
    let mut i: libc::c_int = 0;
    let mut data: *mut mydata = 0 as *mut mydata;
    i = 0 as libc::c_int;
    while (i as libc::c_ulong)
        < (::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong)
            .wrapping_div(::core::mem::size_of::<libc::c_char>() as libc::c_ulong)
    {
        data = makedata(a[i as usize] as libc::c_int);
        if data.is_null() || (avl_insert(avlt, data as *mut libc::c_void)).is_null() {
            fprintf(
                stderr,
                b"insert %c: out of memory\n\0" as *const u8 as *const libc::c_char,
                a[i as usize] as libc::c_int,
            );
            free(data as *mut libc::c_void);
            break;
        } else {
            printf(
                b"insert %c\0" as *const u8 as *const libc::c_char,
                a[i as usize] as libc::c_int,
            );
            avl_print(
                avlt,
                Some(print_char_func as unsafe extern "C" fn(*mut libc::c_void) -> ()),
            );
            printf(b"\n\0" as *const u8 as *const libc::c_char);
            i += 1;
            i;
        }
    }
    let mut node: *mut avlnode = 0 as *mut avlnode;
    let mut query: mydata = mydata { key: 0 };
    query.key = 'O' as i32;
    printf(b"delete %c\0" as *const u8 as *const libc::c_char, query.key);
    node = avl_find(avlt, &mut query as *mut mydata as *mut libc::c_void);
    if !node.is_null() {
        avl_delete(avlt, node, 0 as libc::c_int);
    }
    avl_print(
        avlt,
        Some(print_char_func as unsafe extern "C" fn(*mut libc::c_void) -> ()),
    );
    loop {
        node = (*avlt).min;
        if node.is_null() {
            break;
        }
        printf(b"\ndelete \0" as *const u8 as *const libc::c_char);
        print_char_func((*node).data);
        avl_delete(avlt, node, 0 as libc::c_int);
        avl_print(
            avlt,
            Some(print_char_func as unsafe extern "C" fn(*mut libc::c_void) -> ()),
        );
    }
    avl_destroy(avlt);
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
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
