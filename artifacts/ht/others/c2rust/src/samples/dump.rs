use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn ht_create() -> *mut ht;
    fn ht_set(
        table: *mut ht,
        key: *const libc::c_char,
        value: *mut libc::c_void,
    ) -> *const libc::c_char;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn exit(_: libc::c_int) -> !;
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ht {
    pub entries: *mut ht_entry,
    pub capacity: size_t,
    pub length: size_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct ht_entry {
    pub key: *mut libc::c_char,
    pub value: *mut libc::c_void,
}
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
pub struct item {
    pub key: *mut libc::c_char,
    pub value: libc::c_int,
}
#[no_mangle]
pub unsafe extern "C" fn exit_nomem() {
    fprintf(stderr, b"out of memory\n\0" as *const u8 as *const libc::c_char);
    exit(1 as libc::c_int);
}
unsafe fn main_0() -> libc::c_int {
    let mut items: [item; 7] = [
        {
            let mut init = item {
                key: b"foo\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 10 as libc::c_int,
            };
            init
        },
        {
            let mut init = item {
                key: b"bar\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 42 as libc::c_int,
            };
            init
        },
        {
            let mut init = item {
                key: b"bazz\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 36 as libc::c_int,
            };
            init
        },
        {
            let mut init = item {
                key: b"buzz\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 7 as libc::c_int,
            };
            init
        },
        {
            let mut init = item {
                key: b"bob\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 11 as libc::c_int,
            };
            init
        },
        {
            let mut init = item {
                key: b"jane\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 100 as libc::c_int,
            };
            init
        },
        {
            let mut init = item {
                key: b"x\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 200 as libc::c_int,
            };
            init
        },
    ];
    let mut num_items: size_t = (::core::mem::size_of::<[item; 7]>() as libc::c_ulong)
        .wrapping_div(::core::mem::size_of::<item>() as libc::c_ulong);
    let mut table: *mut ht = ht_create();
    if table.is_null() {
        exit_nomem();
    }
    let mut i: libc::c_int = 0 as libc::c_int;
    while (i as size_t) < num_items {
        if (ht_set(
            table,
            items[i as usize].key,
            &mut (*items.as_mut_ptr().offset(i as isize)).value as *mut libc::c_int
                as *mut libc::c_void,
        ))
            .is_null()
        {
            exit_nomem();
        }
        i += 1;
        i;
    }
    let mut i_0: libc::c_int = 0 as libc::c_int;
    while (i_0 as size_t) < (*table).capacity {
        if !((*((*table).entries).offset(i_0 as isize)).key).is_null() {
            printf(
                b"index %d: key %s, value %d\n\0" as *const u8 as *const libc::c_char,
                i_0,
                (*((*table).entries).offset(i_0 as isize)).key,
                *((*((*table).entries).offset(i_0 as isize)).value as *mut libc::c_int),
            );
        } else {
            printf(b"index %d: empty\n\0" as *const u8 as *const libc::c_char, i_0);
        }
        i_0 += 1;
        i_0;
    }
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
