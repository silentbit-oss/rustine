
extern "C" {
    #[no_mangle]
    fn realloc(_: * mut core::ffi::c_void, _: std::os::raw::c_ulong) -> * mut core::ffi::c_void;
    #[no_mangle]
    fn free(__ptr: * mut core::ffi::c_void);
    #[no_mangle]
    fn memset(_: * mut core::ffi::c_void, _: std::os::raw::c_int, _: std::os::raw::c_ulong)
     -> * mut core::ffi::c_void;
}
pub type size_t = std::os::raw::c_ulong;
// #[derive(Copy, Clone)]

pub type stack = crate::src::markdown::stack;
#[no_mangle]
pub unsafe extern "C" fn stack_grow(mut st: * mut crate::src::markdown::stack, mut new_size: std::os::raw::c_ulong)
 -> std::os::raw::c_int {
    let mut new_st: * mut * mut core::ffi::c_void = 0 as *mut *mut std::os::raw::c_void;
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
pub unsafe extern "C" fn stack_free<'a1>(mut st: Option<&'a1 mut crate::src::markdown::stack>) {
    if borrow(& st).is_none() { return }
    free((*(borrow_mut(&mut st)).unwrap()).item as *mut std::os::raw::c_void);
    (*(borrow_mut(&mut st)).unwrap()).item = 0 as *mut *mut std::os::raw::c_void;
    (*(borrow_mut(&mut st)).unwrap()).size = 0 as std::os::raw::c_int as size_t;
    (*(borrow_mut(&mut st)).unwrap()).asize = 0 as std::os::raw::c_int as size_t;
}
#[no_mangle]
pub unsafe extern "C" fn stack_init(mut st: * mut crate::src::markdown::stack,
                                    mut initial_size: std::os::raw::c_ulong) -> std::os::raw::c_int {
    (*st).item = 0 as *mut *mut std::os::raw::c_void;
    (*st).size = 0 as std::os::raw::c_int as size_t;
    (*st).asize = 0 as std::os::raw::c_int as size_t;
    if initial_size == 0 { initial_size = 8 as std::os::raw::c_int as size_t }
    return stack_grow(st, initial_size);
}
#[no_mangle]
pub unsafe extern "C" fn stack_pop<'a1>(mut st: Option<&'a1 mut crate::src::markdown::stack>) -> * mut core::ffi::c_void {
    if (*(borrow(& st)).unwrap()).size == 0 { return 0 as *mut std::os::raw::c_void }
    (*(borrow_mut(&mut st)).unwrap()).size = (*(borrow(& st)).unwrap()).size.wrapping_sub(1);
    return *(*(borrow(& st)).unwrap()).item.offset((*(borrow(& st)).unwrap()).size as isize);
}
#[no_mangle]
pub unsafe extern "C" fn stack_push(mut st: * mut crate::src::markdown::stack,
                                    mut item: * mut core::ffi::c_void)
 -> std::os::raw::c_int {
    if stack_grow(st,
                  (*st).size.wrapping_mul(2 as std::os::raw::c_int as std::os::raw::c_ulong))
           < 0 as std::os::raw::c_int {
        return -(1 as std::os::raw::c_int)
    }
    let mut fresh0 = (*st).size;
    (*st).size = (*st).size.wrapping_add(1);
    let ref mut fresh1 = *(*st).item.offset(fresh0 as isize);
    *fresh1 = item;
    return 0 as std::os::raw::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn stack_top<'a1>(mut st: Option<&'a1 mut crate::src::markdown::stack>) -> * mut core::ffi::c_void {
    if (*(borrow(& st)).unwrap()).size == 0 { return 0 as *mut std::os::raw::c_void }
    return *(*(borrow(& st)).unwrap()).item.offset((*(borrow(& st)).unwrap()).size.wrapping_sub(1 as std::os::raw::c_int as
                                                          std::os::raw::c_ulong) as
                                  isize);
}
use crate::laertes_rt::*;
