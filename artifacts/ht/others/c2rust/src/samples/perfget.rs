use ::libc;
extern "C" {
    pub type ht;
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn ht_create() -> *mut ht;
    fn ht_get(table: *mut ht, key: *const libc::c_char) -> *mut libc::c_void;
    fn ht_set(
        table: *mut ht,
        key: *const libc::c_char,
        value: *mut libc::c_void,
    ) -> *const libc::c_char;
    fn ht_length(table: *mut ht) -> size_t;
    fn ht_iterator(table: *mut ht) -> hti;
    fn ht_next(it: *mut hti) -> bool;
    static mut stderr: *mut FILE;
    fn fclose(__stream: *mut FILE) -> libc::c_int;
    fn fopen(_: *const libc::c_char, _: *const libc::c_char) -> *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn fread(
        _: *mut libc::c_void,
        _: libc::c_ulong,
        _: libc::c_ulong,
        _: *mut FILE,
    ) -> libc::c_ulong;
    fn fseek(
        __stream: *mut FILE,
        __off: libc::c_long,
        __whence: libc::c_int,
    ) -> libc::c_int;
    fn ftell(__stream: *mut FILE) -> libc::c_long;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn exit(_: libc::c_int) -> !;
    fn clock() -> clock_t;
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct hti {
    pub key: *const libc::c_char,
    pub value: *mut libc::c_void,
    pub _table: *mut ht,
    pub _index: size_t,
}
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type __clock_t = libc::c_long;
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
#[no_mangle]
pub unsafe extern "C" fn exit_nomem() {
    fprintf(stderr, b"out of memory\n\0" as *const u8 as *const libc::c_char);
    exit(1 as libc::c_int);
}
#[no_mangle]
pub static mut found: *mut libc::c_void = 0 as *const libc::c_void as *mut libc::c_void;
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    if argc < 2 as libc::c_int {
        fprintf(stderr, b"usage: perftest file\n\0" as *const u8 as *const libc::c_char);
        return 1 as libc::c_int;
    }
    let mut f: *mut FILE = fopen(
        *argv.offset(1 as libc::c_int as isize),
        b"rb\0" as *const u8 as *const libc::c_char,
    );
    if f.is_null() {
        fprintf(
            stderr,
            b"can't open file: %s\n\0" as *const u8 as *const libc::c_char,
            *argv.offset(1 as libc::c_int as isize),
        );
        return 1 as libc::c_int;
    }
    fseek(f, 0 as libc::c_int as libc::c_long, 2 as libc::c_int);
    let mut size: libc::c_long = ftell(f);
    fseek(f, 0 as libc::c_int as libc::c_long, 0 as libc::c_int);
    let mut contents: *mut libc::c_char = malloc(
        (size + 1 as libc::c_int as libc::c_long) as libc::c_ulong,
    ) as *mut libc::c_char;
    if contents.is_null() {
        exit_nomem();
    }
    let mut nread: size_t = fread(
        contents as *mut libc::c_void,
        1 as libc::c_int as libc::c_ulong,
        size as libc::c_ulong,
        f,
    );
    if nread as libc::c_long != size {
        fprintf(
            stderr,
            b"read %ld bytes instead of %ld\0" as *const u8 as *const libc::c_char,
            nread as libc::c_long,
            size,
        );
        return 1 as libc::c_int;
    }
    fclose(f);
    *contents.offset(size as isize) = 0 as libc::c_int as libc::c_char;
    let mut counts: *mut ht = ht_create();
    if counts.is_null() {
        exit_nomem();
    }
    let mut p: *mut libc::c_char = contents;
    while *p != 0 {
        while *p as libc::c_int != 0 && *p as libc::c_int <= ' ' as i32 {
            p = p.offset(1);
            p;
        }
        let mut word: *mut libc::c_char = p;
        while *p as libc::c_int != 0 && *p as libc::c_int > ' ' as i32 {
            p = p.offset(1);
            p;
        }
        if *p as libc::c_int != 0 as libc::c_int {
            *p = 0 as libc::c_int as libc::c_char;
        }
        let mut value: *mut libc::c_void = ht_get(counts, word);
        if !value.is_null() {
            let mut pcount: *mut libc::c_int = value as *mut libc::c_int;
            *pcount += 1;
            *pcount;
        } else {
            let mut pcount_0: *mut libc::c_int = malloc(
                ::core::mem::size_of::<libc::c_int>() as libc::c_ulong,
            ) as *mut libc::c_int;
            if pcount_0.is_null() {
                exit_nomem();
            }
            *pcount_0 = 1 as libc::c_int;
            if (ht_set(counts, word, pcount_0 as *mut libc::c_void)).is_null() {
                exit_nomem();
            }
        }
        p = p.offset(1);
        p;
    }
    let mut keys: *mut *const libc::c_char = malloc(
        (ht_length(counts))
            .wrapping_mul(::core::mem::size_of::<*mut libc::c_char>() as libc::c_ulong),
    ) as *mut *const libc::c_char;
    if keys.is_null() {
        exit_nomem();
    }
    let mut it: hti = ht_iterator(counts);
    let mut i: libc::c_int = 0 as libc::c_int;
    while ht_next(&mut it) {
        let ref mut fresh0 = *keys.offset(i as isize);
        *fresh0 = it.key;
        i += 1;
        i;
    }
    let mut runs: libc::c_int = 10 as libc::c_int;
    let mut start: clock_t = clock();
    let mut run: libc::c_int = 0 as libc::c_int;
    while run < runs {
        let mut i_0: libc::c_int = 0 as libc::c_int;
        while (i_0 as size_t) < ht_length(counts) {
            found = ht_get(counts, *keys.offset(i_0 as isize));
            i_0 += 1;
            i_0;
        }
        run += 1;
        run;
    }
    let mut end: clock_t = clock();
    let mut elapsed_ms: libc::c_double = (end - start) as libc::c_double
        / 1000000 as libc::c_int as __clock_t as libc::c_double
        * 1000 as libc::c_int as libc::c_double;
    printf(
        b"%d runs getting %lu keys: %.03fms\n\0" as *const u8 as *const libc::c_char,
        runs,
        ht_length(counts),
        elapsed_ms,
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
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
