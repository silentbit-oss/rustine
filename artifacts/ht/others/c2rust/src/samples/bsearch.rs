use ::libc;
extern "C" {
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn bsearch(
        __key: *const libc::c_void,
        __base: *const libc::c_void,
        __nmemb: size_t,
        __size: size_t,
        __compar: __compar_fn_t,
    ) -> *mut libc::c_void;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
pub type __compar_fn_t = Option::<
    unsafe extern "C" fn(*const libc::c_void, *const libc::c_void) -> libc::c_int,
>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct item {
    pub key: *mut libc::c_char,
    pub value: libc::c_int,
}
#[no_mangle]
pub unsafe extern "C" fn cmp(
    mut a: *const libc::c_void,
    mut b: *const libc::c_void,
) -> libc::c_int {
    let mut item_a: *mut item = a as *mut item;
    let mut item_b: *mut item = b as *mut item;
    return strcmp((*item_a).key, (*item_b).key);
}
#[no_mangle]
pub unsafe extern "C" fn binary_search(
    mut items: *mut item,
    mut size: size_t,
    mut key: *const libc::c_char,
) -> *mut item {
    if size.wrapping_add(size) < size {
        return 0 as *mut item;
    }
    let mut low: size_t = 0 as libc::c_int as size_t;
    let mut high: size_t = size;
    while low < high {
        let mut mid: size_t = low.wrapping_add(high) / 2 as libc::c_int as size_t;
        let mut c: libc::c_int = strcmp((*items.offset(mid as isize)).key, key);
        if c == 0 as libc::c_int {
            return &mut *items.offset(mid as isize) as *mut item;
        }
        if c < 0 as libc::c_int {
            low = mid.wrapping_add(1 as libc::c_int as size_t);
        } else {
            high = mid;
        }
    }
    return 0 as *mut item;
}
unsafe fn main_0() -> libc::c_int {
    let mut items: [item; 7] = [
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
                key: b"bob\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 11 as libc::c_int,
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
                key: b"foo\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
                value: 10 as libc::c_int,
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
    let mut key: item = {
        let mut init = item {
            key: b"bob\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 0 as libc::c_int,
        };
        init
    };
    let mut found: *mut item = bsearch(
        &mut key as *mut item as *const libc::c_void,
        items.as_mut_ptr() as *const libc::c_void,
        num_items,
        ::core::mem::size_of::<item>() as libc::c_ulong,
        Some(
            cmp
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
    ) as *mut item;
    if found.is_null() {
        return 1 as libc::c_int;
    }
    printf(
        b"bsearch: value of 'bob' is %d\n\0" as *const u8 as *const libc::c_char,
        (*found).value,
    );
    found = binary_search(
        items.as_mut_ptr(),
        num_items,
        b"bob\0" as *const u8 as *const libc::c_char,
    );
    if found.is_null() {
        return 1 as libc::c_int;
    }
    printf(
        b"binary_search: value of 'bob' is %d\n\0" as *const u8 as *const libc::c_char,
        (*found).value,
    );
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
