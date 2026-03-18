use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn ht_create() -> *mut ht;
    fn ht_destroy(table: *mut ht);
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
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn scanf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn exit(_: libc::c_int) -> !;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
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
#[derive(Copy, Clone)]
#[repr(C)]
pub struct hti {
    pub key: *const libc::c_char,
    pub value: *mut libc::c_void,
    pub _table: *mut ht,
    pub _index: size_t,
}
pub type __uint64_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type uint64_t = __uint64_t;
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
#[no_mangle]
pub unsafe extern "C" fn exit_nomem() {
    fprintf(stderr, b"out of memory\n\0" as *const u8 as *const libc::c_char);
    exit(1 as libc::c_int);
}
unsafe extern "C" fn hash_key(mut key: *const libc::c_char) -> uint64_t {
    let mut hash: uint64_t = 14695981039346656037 as libc::c_ulong;
    let mut p: *const libc::c_char = key;
    while *p != 0 {
        hash ^= *p as libc::c_uchar as uint64_t;
        hash = (hash as libc::c_ulong).wrapping_mul(1099511628211 as libc::c_ulong)
            as uint64_t as uint64_t;
        p = p.offset(1);
        p;
    }
    return hash;
}
#[no_mangle]
pub unsafe extern "C" fn get_probe_len(
    mut table: *mut ht,
    mut key: *const libc::c_char,
) -> size_t {
    let mut hash: uint64_t = hash_key(key);
    let mut index: size_t = hash
        & ((*table).capacity).wrapping_sub(1 as libc::c_int as size_t);
    let mut probe_len: size_t = 0 as libc::c_int as size_t;
    while !((*((*table).entries).offset(index as isize)).key).is_null() {
        probe_len = probe_len.wrapping_add(1);
        probe_len;
        if strcmp(key, (*((*table).entries).offset(index as isize)).key)
            == 0 as libc::c_int
        {
            return probe_len;
        }
        index = index.wrapping_add(1);
        index;
        if index >= (*table).capacity {
            index = 0 as libc::c_int as size_t;
        }
    }
    return probe_len;
}
unsafe fn main_0() -> libc::c_int {
    let mut counts: *mut ht = ht_create();
    if counts.is_null() {
        exit_nomem();
    }
    let mut word: [libc::c_char; 101] = [0; 101];
    while scanf(b"%100s\0" as *const u8 as *const libc::c_char, word.as_mut_ptr())
        != -(1 as libc::c_int)
    {
        let mut value: *mut libc::c_void = ht_get(counts, word.as_mut_ptr());
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
            if (ht_set(counts, word.as_mut_ptr(), pcount_0 as *mut libc::c_void))
                .is_null()
            {
                exit_nomem();
            }
        }
    }
    let mut it: hti = ht_iterator(counts);
    let mut total_probes: size_t = 0 as libc::c_int as size_t;
    while ht_next(&mut it) {
        total_probes = total_probes.wrapping_add(get_probe_len(counts, it.key));
        free(it.value);
    }
    printf(
        b"len=%lu cap=%lu avgprobe=%.3f\n\0" as *const u8 as *const libc::c_char,
        ht_length(counts),
        (*counts).capacity,
        total_probes as libc::c_double / ht_length(counts) as libc::c_double,
    );
    ht_destroy(counts);
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
