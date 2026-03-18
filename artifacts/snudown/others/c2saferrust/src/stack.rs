


use std::os::raw::c_void;

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
pub fn stack_free(mut st: &mut crate::src::markdown::stack) {
    // Check if the item pointer is null using a direct comparison
    if st.item.is_null() { return; }
    
    // Use an unsafe block to read the raw pointer
    let item_ptr;
    unsafe {
        item_ptr = std::ptr::read(st.item); // Read the raw pointer
    }
    
    // Free the memory if the pointer is not null
    if !item_ptr.is_null() {
        unsafe {
            drop(Box::from_raw(item_ptr)); // Automatically frees the memory
        }
    }
    
    // Reset the fields
    st.item = std::ptr::null_mut(); // Set item to null
    st.size = 0;
    st.asize = 0;
}

#[no_mangle]
pub fn stack_init(st: &mut crate::src::markdown::stack, mut initial_size: usize) -> i32 {
    st.item = Vec::with_capacity(initial_size).as_mut_ptr();
    st.size = 0;
    st.asize = 0;
    if initial_size == 0 { initial_size = 8 }
    
    unsafe {
        return stack_grow(st, initial_size as u64);
    }
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
pub fn stack_top(st: &mut crate::src::markdown::stack) -> Option<*mut std::os::raw::c_void> {
    if st.size == 0 {
        return None;
    }
    let index = st.size.wrapping_sub(1) as usize;
    let item_ptr = unsafe { *st.item.add(index) };
    Some(item_ptr)
}

