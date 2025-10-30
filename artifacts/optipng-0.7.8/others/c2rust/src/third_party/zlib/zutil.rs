use ::libc;
extern "C" {
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
}
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type voidpf = *mut libc::c_void;
pub type __off_t = libc::c_long;
pub type off_t = __off_t;
#[no_mangle]
pub static mut z_errmsg: [*const libc::c_char; 10] = [
    b"need dictionary\0" as *const u8 as *const libc::c_char,
    b"stream end\0" as *const u8 as *const libc::c_char,
    b"\0" as *const u8 as *const libc::c_char,
    b"file error\0" as *const u8 as *const libc::c_char,
    b"stream error\0" as *const u8 as *const libc::c_char,
    b"data error\0" as *const u8 as *const libc::c_char,
    b"insufficient memory\0" as *const u8 as *const libc::c_char,
    b"buffer error\0" as *const u8 as *const libc::c_char,
    b"incompatible version\0" as *const u8 as *const libc::c_char,
    b"\0" as *const u8 as *const libc::c_char,
];
#[no_mangle]
pub unsafe extern "C" fn zlibVersion() -> *const libc::c_char {
    return b"1.3-optipng\0" as *const u8 as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn zlibCompileFlags() -> uLong {
    let mut flags: uLong = 0;
    flags = 0 as libc::c_int as uLong;
    match ::core::mem::size_of::<uInt>() as libc::c_ulong as libc::c_int {
        2 => {}
        4 => {
            flags = flags.wrapping_add(1 as libc::c_int as uLong);
        }
        8 => {
            flags = flags.wrapping_add(2 as libc::c_int as uLong);
        }
        _ => {
            flags = flags.wrapping_add(3 as libc::c_int as uLong);
        }
    }
    match ::core::mem::size_of::<uLong>() as libc::c_ulong as libc::c_int {
        2 => {}
        4 => {
            flags = flags
                .wrapping_add(((1 as libc::c_int) << 2 as libc::c_int) as uLong);
        }
        8 => {
            flags = flags
                .wrapping_add(((2 as libc::c_int) << 2 as libc::c_int) as uLong);
        }
        _ => {
            flags = flags
                .wrapping_add(((3 as libc::c_int) << 2 as libc::c_int) as uLong);
        }
    }
    match ::core::mem::size_of::<voidpf>() as libc::c_ulong as libc::c_int {
        2 => {}
        4 => {
            flags = flags
                .wrapping_add(((1 as libc::c_int) << 4 as libc::c_int) as uLong);
        }
        8 => {
            flags = flags
                .wrapping_add(((2 as libc::c_int) << 4 as libc::c_int) as uLong);
        }
        _ => {
            flags = flags
                .wrapping_add(((3 as libc::c_int) << 4 as libc::c_int) as uLong);
        }
    }
    match ::core::mem::size_of::<off_t>() as libc::c_ulong as libc::c_int {
        2 => {}
        4 => {
            flags = flags
                .wrapping_add(((1 as libc::c_int) << 6 as libc::c_int) as uLong);
        }
        8 => {
            flags = flags
                .wrapping_add(((2 as libc::c_int) << 6 as libc::c_int) as uLong);
        }
        _ => {
            flags = flags
                .wrapping_add(((3 as libc::c_int) << 6 as libc::c_int) as uLong);
        }
    }
    flags = flags.wrapping_add(((1 as libc::c_long) << 16 as libc::c_int) as uLong);
    flags = flags.wrapping_add(((1 as libc::c_long) << 17 as libc::c_int) as uLong);
    return flags;
}
#[no_mangle]
pub unsafe extern "C" fn zError(mut err: libc::c_int) -> *const libc::c_char {
    return z_errmsg[(2 as libc::c_int - err) as usize];
}
#[no_mangle]
pub unsafe extern "C" fn zcalloc(
    mut opaque: voidpf,
    mut items: libc::c_uint,
    mut size: libc::c_uint,
) -> voidpf {
    return if ::core::mem::size_of::<uInt>() as libc::c_ulong
        > 2 as libc::c_int as libc::c_ulong
    {
        malloc(items.wrapping_mul(size) as libc::c_ulong)
    } else {
        calloc(items as libc::c_ulong, size as libc::c_ulong)
    };
}
#[no_mangle]
pub unsafe extern "C" fn zcfree(mut opaque: voidpf, mut ptr: voidpf) {
    free(ptr);
}
