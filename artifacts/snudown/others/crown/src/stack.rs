use ::libc;
extern "C" {
    fn realloc(_: *mut libc::c_void, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct stack {
    pub item: *mut *mut libc::c_void,
    pub size: size_t,
    pub asize: size_t,
}
#[no_mangle]
pub unsafe extern "C" fn stack_grow(
    mut st: *mut stack,
    mut new_size: size_t,
) -> libc::c_int {
    let mut new_st: *mut *mut libc::c_void = 0 as *mut *mut libc::c_void;
    if (*st).asize >= new_size {
        return 0 as libc::c_int;
    }
    new_st = realloc(
        (*st).item as *mut libc::c_void,
        new_size
            .wrapping_mul(::core::mem::size_of::<*mut libc::c_void>() as libc::c_ulong),
    ) as *mut *mut libc::c_void;
    if new_st.is_null() {std::intrinsics::assume((new_st).addr() == 0);
        return -(1 as libc::c_int);
    }
    memset(
        new_st.offset((*st).asize as isize) as *mut libc::c_void,
        0 as libc::c_int,
        new_size
            .wrapping_sub((*st).asize)
            .wrapping_mul(::core::mem::size_of::<*mut libc::c_void>() as libc::c_ulong),
    );
    (*st).item = new_st;
    (*st).asize = new_size;
    if (*st).size > new_size {
        (*st).size = new_size;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn stack_free(mut st: *mut stack) {
    if st.is_null() {std::intrinsics::assume((st).addr() == 0);
        return;
    }
    free((*st).item as *mut libc::c_void);
    (*st).item = 0 as *mut *mut libc::c_void;
    (*st).size = 0 as libc::c_int as size_t;
    (*st).asize = 0 as libc::c_int as size_t;
}
#[no_mangle]
pub unsafe extern "C" fn stack_init(
    mut st: *mut stack,
    mut initial_size: size_t,
) -> libc::c_int {
    (*st).item = 0 as *mut *mut libc::c_void;
    (*st).size = 0 as libc::c_int as size_t;
    (*st).asize = 0 as libc::c_int as size_t;
    if initial_size == 0 {
        initial_size = 8 as libc::c_int as size_t;
    }
    return stack_grow(st, initial_size);
}
#[no_mangle]
pub unsafe extern "C" fn stack_pop(mut st: *mut stack) -> *mut libc::c_void {
    if (*st).size == 0 {
        return 0 as *mut libc::c_void;
    }
    (*st).size = ((*st).size).wrapping_sub(1);
    return *((*st).item).offset((*st).size as isize);
}
#[no_mangle]
pub unsafe extern "C" fn stack_push(
    mut st: *mut stack,
    mut item: *mut libc::c_void,
) -> libc::c_int {
    if stack_grow(st, (*st).size * 2 as libc::c_int as size_t) < 0 as libc::c_int {
        return -(1 as libc::c_int);
    }
    let fresh0 = (*st).size;
    (*st).size = ((*st).size).wrapping_add(1);
    *((*st).item).offset(fresh0 as isize) = item;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn stack_top(mut st: *mut stack) -> *mut libc::c_void {
    if (*st).size == 0 {
        return 0 as *mut libc::c_void;
    }
    return *((*st).item)
        .offset(((*st).size).wrapping_sub(1 as libc::c_int as size_t) as isize);
}
