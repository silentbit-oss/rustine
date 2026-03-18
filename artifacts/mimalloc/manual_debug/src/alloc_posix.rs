use crate::*;
use std::env;
use std::os::raw::c_void;
use std::ptr::null_mut;
use std::ptr;

pub fn mi_wdupenv_s(
    buf: &mut Option<&mut [u16]>, 
    size: Option<&mut usize>, 
    name: Option<&[u16]>
) -> i32 {
    if buf.is_none() || name.is_none() {
        return 22;
    }
    
    if let Some(size_ref) = size {
        *size_ref = 0;
    }
    
    *buf = None;
    22
}
pub fn mi__expand(p: Option<&mut ()>, newsize: usize) -> Option<&mut ()> {
    let res = mi_expand(p, newsize);
    if res.is_none() {
        unsafe {
            // ENOMEM = 12
            std::io::Error::from_raw_os_error(12).raw_os_error();
        }
    }
    res
}

pub fn mi_malloc_size(p: Option<&c_void>) -> usize {
    mi_usable_size(p)
}
pub fn mi_malloc_good_size(size: usize) -> usize {
    mi_good_size(size)
}

pub fn mi_malloc_usable_size(p: Option<&c_void>) -> usize {
    mi_usable_size(p)
}

pub fn mi_reallocarray(p: Option<&mut c_void>, count: usize, size: usize) -> Option<&'static mut c_void> {
    let newp = mi_reallocn(p, count, size);
    if newp.is_none() {
        // In Rust, we don't directly set errno like in C
        // The error handling is typically done through Result/Option types
    }
    newp
}

pub fn mi_aligned_recalloc(
    p: Option<&mut c_void>,
    newcount: usize,
    size: usize,
    alignment: usize,
) -> Option<&'static mut c_void> {
    mi_recalloc_aligned(p, newcount, size, alignment)
}

pub fn mi_aligned_offset_recalloc(
    p: Option<&mut c_void>,
    newcount: usize,
    size: usize,
    alignment: usize,
    offset: usize,
) -> Option<*mut c_void> {
    mi_recalloc_aligned_at(p, newcount, size, alignment, offset)
}
pub fn mi_mbsdup(s: Option<&[u8]>) -> Option<Vec<u8>> {
    s.and_then(|bytes| {
        std::str::from_utf8(bytes).ok()
            .and_then(|str_slice| mi_strdup(Some(str_slice)))
            .map(|string| string.into_bytes())
    })
}
pub fn mi_cfree(p: Option<&std::ffi::c_void>) {
    if let Some(ptr) = p {
        if mi_is_in_heap_region(Some(ptr)) {
            mi_free(Some(ptr));
        }
    }
}
pub fn mi_memalign(alignment: usize, size: usize) -> Option<*mut c_void> {
    let p = mi_malloc_aligned(size, alignment);
    
    if let Some(ptr) = p {
        let ptr_value = ptr as usize;
        if ptr_value % alignment != 0 {
            _mi_assert_fail(
                "((uintptr_t)p % alignment) == 0", 
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/alloc-posix.c", 
                71, 
                Some("mi_memalign")
            );
        }
    }
    
    p
}

pub fn mi_valloc(size: usize) -> Option<*mut c_void> {
    mi_memalign(_mi_os_page_size(), size)
}
pub fn mi_aligned_alloc(alignment: usize, size: usize) -> Option<*mut c_void> {
    let p = mi_malloc_aligned(size, alignment);
    
    if let Some(ptr) = p {
        let ptr_value = ptr as usize;
        if ptr_value % alignment != 0 {
            _mi_assert_fail(
                "((uintptr_t)p % alignment) == 0", 
                "/workdir/C2RustTranslation-main/subjects/mimalloc/src/alloc-posix.c", 
                98, 
                Some("mi_aligned_alloc")
            );
        }
    }
    
    p
}
pub fn mi_reallocarr(p: Option<*mut *mut c_void>, count: usize, size: usize) -> i32 {
    // Check for NULL pointer equivalent
    if p.is_none() {
        return 22; // Return EINVAL equivalent
    }
    
    let op_ptr = p.unwrap();
    
    // Unsafe block required for raw pointer dereference
    let newp = unsafe {
        let current_ptr = *op_ptr;
        mi_reallocarray(
            if current_ptr.is_null() {
                Option::None
            } else {
                Some(&mut *current_ptr)
            }, 
            count, 
            size
        )
    };
    
    if newp.is_none() {
        return std::io::Error::last_os_error().raw_os_error().unwrap_or(22);
    }
    
    unsafe {
        *op_ptr = newp.unwrap() as *mut c_void;
    }
    0
}

pub fn mi_wcsdup(s: Option<&[u16]>) -> Option<Box<[u16]>> {
    // Check for NULL equivalent (None)
    let s = s?;
    
    // Calculate length by finding the null terminator
    let len = s.iter().position(|&c| c == 0).unwrap_or(s.len());
    
    // Allocate memory for the new string (len + 1 for null terminator)
    let mut result = Vec::with_capacity(len + 1);
    
    // Copy the characters
    result.extend_from_slice(&s[..len]);
    // Add null terminator
    result.push(0);
    
    Some(result.into_boxed_slice())
}
pub fn mi_dupenv_s(buf: &mut Option<String>, mut size: Option<&mut usize>, name: Option<&str>) -> i32 {
    if buf.is_none() || name.is_none() {
        return 22;
    }
    
    if let Some(ref mut size_ref) = size {
        **size_ref = 0;
    }
    
    let name = name.unwrap();
    let p = std::env::var(name).ok();
    
    if p.is_none() {
        *buf = None;
    } else {
        let p_str = p.unwrap();
        *buf = mi_strdup(Some(&p_str));
        
        if buf.is_none() {
            return 12;
        }
        
        if let Some(ref mut size_ref) = size {
            **size_ref = _mi_strlen(Some(&p_str));
        }
    }
    
    0
}
pub fn mi_posix_memalign(p: Option<&mut *mut c_void>, alignment: usize, size: usize) -> i32 {
    if p.is_none() {
        return 22;
    }
    
    if alignment % std::mem::size_of::<*mut c_void>() != 0 {
        return 22;
    }
    
    if alignment == 0 || !_mi_is_power_of_two(alignment) {
        return 22;
    }
    
    let q = mi_malloc_aligned(size, alignment);
    
    if q.is_none() && size != 0 {
        return 12;
    }
    
    let q_ptr = q.unwrap();
    let alignment_check = (q_ptr as usize) % alignment == 0;
    if !alignment_check {
        _mi_assert_fail("((uintptr_t)q % alignment) == 0", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/alloc-posix.c", 64, Some("mi_posix_memalign"));
    }
    
    if let Some(p_ref) = p {
        *p_ref = q_ptr;
    }
    
    0
}

pub fn mi_pvalloc(size: usize) -> Option<*mut c_void> {
    let psize = _mi_os_page_size();
    if size >= (usize::MAX - psize) {
        return None;
    }
    let asize = _mi_align_up(size, psize);
    mi_malloc_aligned(asize, psize)
}
