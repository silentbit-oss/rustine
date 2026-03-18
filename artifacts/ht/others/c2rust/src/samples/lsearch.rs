use ::libc;
extern "C" {
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct item {
    pub key: *mut libc::c_char,
    pub value: libc::c_int,
}
#[no_mangle]
pub unsafe extern "C" fn linear_search(
    mut items: *mut item,
    mut size: size_t,
    mut key: *const libc::c_char,
) -> *mut item {
    let mut i: size_t = 0 as libc::c_int as size_t;
    while i < size {
        if strcmp((*items.offset(i as isize)).key, key) == 0 as libc::c_int {
            return &mut *items.offset(i as isize) as *mut item;
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as *mut item;
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
    let mut found: *mut item = linear_search(
        items.as_mut_ptr(),
        num_items,
        b"bob\0" as *const u8 as *const libc::c_char,
    );
    if found.is_null() {
        return 1 as libc::c_int;
    }
    printf(
        b"linear_search: value of 'bob' is %d\n\0" as *const u8 as *const libc::c_char,
        (*found).value,
    );
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
