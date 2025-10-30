use ::libc;
extern "C" {
    fn realloc(_: *mut libc::c_void, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    static mut libzahl_pool: [*mut *mut zahl_char_t; 64];
    static mut libzahl_pool_n: [size_t; 64];
    static mut libzahl_pool_alloc: [size_t; 64];
}
pub type size_t = libc::c_ulong;
pub type __uint32_t = libc::c_uint;
pub type uint32_t = __uint32_t;
pub type zahl_char_t = uint32_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed {
    pub sign: libc::c_int,
    pub used: size_t,
    pub alloced: size_t,
    pub chars: *mut zahl_char_t,
}
#[no_mangle]
pub unsafe extern "C" fn zfree(mut a: *mut C2RustUnnamed) {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut x: size_t = 0;
    let mut j: size_t = 0;
    let mut new: *mut *mut zahl_char_t = 0 as *mut *mut zahl_char_t;
    if ((*a).chars).is_null() {
        return;
    }
    x = (*a).alloced;
    while x != 0 {
        i = i.wrapping_add(1 as libc::c_int as size_t);
        x >>= 1 as libc::c_int;
    }
    let fresh0 = libzahl_pool_n[i as usize];
    libzahl_pool_n[i as usize] = (libzahl_pool_n[i as usize]).wrapping_add(1);
    j = fresh0;
    if j == libzahl_pool_alloc[i as usize] {
        x = if j != 0 {
            j * 3 as libc::c_int as size_t >> 1 as libc::c_int
        } else {
            128 as libc::c_int as size_t
        };
        new = realloc(
            libzahl_pool[i as usize] as *mut libc::c_void,
            x.wrapping_mul(::core::mem::size_of::<*mut zahl_char_t>() as libc::c_ulong),
        ) as *mut *mut zahl_char_t;
        if new.is_null() {
            free((*a).chars as *mut libc::c_void);
            free(libzahl_pool[i as usize] as *mut libc::c_void);
            libzahl_pool_n[i as usize] = 0 as libc::c_int as size_t;
            libzahl_pool[i as usize] = 0 as *mut *mut zahl_char_t;
            libzahl_pool_alloc[i as usize] = 0 as libc::c_int as size_t;
            return;
        }
        libzahl_pool[i as usize] = new;
        libzahl_pool_alloc[i as usize] = x;
    }
    let ref mut fresh1 = *(libzahl_pool[i as usize]).offset(j as isize);
    *fresh1 = (*a).chars;
}
