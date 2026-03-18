
extern "C" {
    #[no_mangle]
    fn realloc(_: *mut std::os::raw::c_void, _: std::os::raw::c_ulong) -> *mut std::os::raw::c_void;
    #[no_mangle]
    fn free(__ptr: *mut std::os::raw::c_void);
    #[no_mangle]
    fn memset(_: *mut std::os::raw::c_void, _: std::os::raw::c_int, _: std::os::raw::c_ulong)
     -> *mut std::os::raw::c_void;
}
pub type size_t = crate::src::autolink::size_t;
// #[derive(Copy, Clone)]

pub type stack = crate::src::markdown::stack;
#[no_mangle]
pub unsafe extern "C" fn stack_grow(mut st: *mut stack, mut new_size: size_t)
 -> std::os::raw::c_int {
    let mut new_st: *mut *mut std::os::raw::c_void = 0 as *mut *mut std::os::raw::c_void;
    if (*st).asize >= new_size { return 0 as std::os::raw::c_int }
    new_st =
        realloc((*st).item as *mut std::os::raw::c_void,
                new_size.wrapping_mul(::std::mem::size_of::<*mut std::os::raw::c_void>()
                                          as std::os::raw::c_ulong)) as
            *mut *mut std::os::raw::c_void;
    if new_st.is_null() { return -(1 as std::os::raw::c_int) }
    memset(new_st.offset((*st).asize as isize) as *mut std::os::raw::c_void,
           0 as std::os::raw::c_int,
           new_size.wrapping_sub((*st).asize).wrapping_mul(::std::mem::size_of::<*mut std::os::raw::c_void>()
                                                               as
                                                               std::os::raw::c_ulong));
    (*st).item = new_st;
    (*st).asize = new_size;
    if (*st).size > new_size { (*st).size = new_size }
    return 0 as std::os::raw::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn stack_free(mut st: *mut stack) {
    if st.is_null() { return }
    free((*st).item as *mut std::os::raw::c_void);
    (*st).item = 0 as *mut *mut std::os::raw::c_void;
    (*st).size = 0 as std::os::raw::c_int as size_t;
    (*st).asize = 0 as std::os::raw::c_int as size_t;
}
#[no_mangle]
pub unsafe extern "C" fn stack_init(mut st: *mut stack,
                                    mut initial_size: size_t) -> std::os::raw::c_int {
    (*st).item = 0 as *mut *mut std::os::raw::c_void;
    (*st).size = 0 as std::os::raw::c_int as size_t;
    (*st).asize = 0 as std::os::raw::c_int as size_t;
    if initial_size == 0 { initial_size = 8 as std::os::raw::c_int as size_t }
    return stack_grow(st, initial_size);
}
#[no_mangle]
pub unsafe extern "C" fn stack_pop(mut st: *mut stack) -> *mut std::os::raw::c_void {
    if (*st).size == 0 { return 0 as *mut std::os::raw::c_void }
    (*st).size = (*st).size.wrapping_sub(1);
    return *(*st).item.offset((*st).size as isize);
}
#[no_mangle]
pub unsafe extern "C" fn stack_push(mut st: *mut stack,
                                    mut item: *mut std::os::raw::c_void)
 -> std::os::raw::c_int {
    if stack_grow(st,
                  (*st).size.wrapping_mul(2 as std::os::raw::c_int as std::os::raw::c_ulong))
           < 0 as std::os::raw::c_int {
        return -(1 as std::os::raw::c_int)
    }
    let fresh0 = (*st).size;
    (*st).size = (*st).size.wrapping_add(1);
    let ref mut fresh1 = *(*st).item.offset(fresh0 as isize);
    *fresh1 = item;
    return 0 as std::os::raw::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn stack_top(mut st: *mut stack) -> *mut std::os::raw::c_void {
    if (*st).size == 0 { return 0 as *mut std::os::raw::c_void }
    return *(*st).item.offset((*st).size.wrapping_sub(1 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong) as
                                  isize);
}
