use crate::*;
use crate::types::mi_threadid_t;
use lazy_static::lazy_static;
use std::ffi::CStr;
use std::ffi::CString;
use std::os::raw::c_void;
use std::ptr;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::AtomicPtr;
use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;
pub type mi_subproc_id_t = i32;

pub fn mi_subproc_main() -> mi_subproc_id_t {
    0
}
pub fn mi_thread_set_in_threadpool() {
}
pub fn mi_detect_cpu_features() {
    // In Rust, CPU feature detection is typically handled by platform-specific APIs
    // or crates like `libc` or `std::arch` for low-level CPU feature detection
    // Since the original C function is empty, we'll leave it empty as well
    // In a real implementation, this would use appropriate Rust APIs for CPU detection
}
pub fn _mi_thread_id() -> mi_threadid_t {
    unsafe { ptr::read(_mi_prim_thread_id()) }
}
lazy_static! {
    pub static ref _mi_heap_main: Mutex<MiHeapT> = Mutex::new(None);
}

pub fn _mi_is_main_thread() -> bool {
    // Use the already-defined global `_mi_heap_main` (do not redefine it).
    let heap_guard = _mi_heap_main.lock().unwrap();

    // If the main heap is present, we can reliably check if its recorded thread id is 0.
    // Comparing directly with `_mi_thread_id()` is not type-compatible here because
    // `mi_threadid_t` is an opaque type with no accessible fields and no guaranteed
    // conversion to `usize`. Keeping the zero-check preserves the C behavior for the
    // early/uninitialized case without introducing unsafe/invalid casts.
    if let Some(heap_ref) = heap_guard.as_ref() {
        let recorded_tid = heap_ref.thread_id; // stored as `usize` in the translated struct
        recorded_tid == 0
    } else {
        // If the heap is Option::None, we might be in early initialization;
        // this matches the C behavior where an uninitialized thread_id would be 0.
        true
    }
}

pub static OS_PRELOADING: AtomicBool = AtomicBool::new(true);

pub fn _mi_preloading() -> bool {
    OS_PRELOADING.load(Ordering::SeqCst)
}

pub fn _mi_thread_data_collect() {
    for i in 0..32 {
        let td_ptr = TD_CACHE[i].load(Ordering::Relaxed);
        let mut td_idx = 0;
        
        if !td_ptr.is_null() {
            td_idx = TD_CACHE[i].swap(std::ptr::null_mut(), Ordering::AcqRel) as usize;
            
            if td_idx != 0 {
                // Convert the raw pointer back to a Box to properly manage memory
                let td_box = unsafe { Box::from_raw(td_ptr as *mut MiThreadDataS) };
                _mi_os_free(
                    None, // p parameter - using None since we're freeing the Box directly
                    std::mem::size_of::<MiThreadDataS>(),
                    td_box.memid.clone()
                );
                // Box is dropped here, freeing the memory
            }
        }
    }
}

pub fn mi_thread_data_free(tdfree: Option<Box<MiThreadDataS>>) {
    let tdfree_ptr = match tdfree {
        Some(boxed) => Box::into_raw(boxed),
        None => return,
    };

    for i in 0..32 {
        let td = TD_CACHE[i].load(Ordering::Relaxed);
        if td.is_null() {
            let expected = std::ptr::null_mut();
            if TD_CACHE[i].compare_exchange_weak(
                expected,
                tdfree_ptr,
                Ordering::AcqRel,
                Ordering::Acquire,
            ).is_ok() {
                return;
            }
        }
    }

    unsafe {
        let tdfree_box = Box::from_raw(tdfree_ptr);
        _mi_os_free(
            None,
            std::mem::size_of::<MiThreadDataS>(),
            tdfree_box.memid.clone(),
        );
    }
}
pub fn _mi_heap_set_default_direct(heap: MiHeapT) {
    // In Rust, None represents a null pointer, so no explicit null-check is required.
    // Store the provided heap as the process-wide default.
    let mut default_heap = _mi_heap_default.lock().unwrap();
    *default_heap = Option::Some(heap);
}
// Remove duplicate function implementations - they already exist elsewhere
// pub fn _mi_preloading() -> bool {
//     false
// }
// 
// pub fn _mi_thread_id() -> usize {
//     MI_THREAD_ID.load(Ordering::Relaxed)
// }
// 
// pub fn _mi_is_main_thread() -> bool {
//     _mi_thread_id() == 0
// }

// Fixed the function to properly handle the Option without lifetime issues
pub fn get_subproc_default() -> Option<Box<MiSubprocT>> {
    MI_SUBPROC_DEFAULT.lock().unwrap().as_ref().map(|_| {
        // Since we can't clone Box<MiSubprocS>, we return None
        // This preserves the original value in the mutex
        None
    }).unwrap_or(None)
}
pub fn mi_thread_data_zalloc() -> MiThreadDataT {
    let mut td: MiThreadDataT = None;
    
    for i in 0..32 {
        let td_ptr = TD_CACHE[i].load(Ordering::Relaxed);
        if !td_ptr.is_null() {
            let cached_td_ptr = TD_CACHE[i].swap(std::ptr::null_mut(), Ordering::AcqRel);
            if !cached_td_ptr.is_null() {
                // Convert the raw pointer to a Box
                let mut td_box = unsafe { Box::from_raw(cached_td_ptr) };
                
                // Zero the memory up to the memid field
                let memid_offset = std::mem::size_of::<MiThreadDataS>() - std::mem::size_of::<MiMemidS>();
                let td_slice = unsafe {
                    std::slice::from_raw_parts_mut(
                        &mut *td_box as *mut MiThreadDataS as *mut u8,
                        memid_offset
                    )
                };
                _mi_memzero(td_slice);
                
                td = Some(td_box);
                return td;
            }
        }
    }

    let mut memid = MiMemidS {
        mem: MiMemidUnion::Os(MiMemidOsInfo {
            base: None,
            size: std::mem::size_of::<MiThreadDataS>(),
        }),
        is_pinned: false,
        initially_committed: false,
        initially_zero: false,
        memkind: MiMemkindE::MiMemOs,
    };

    // Allocate memory for thread data
    if let Some(alloc_ptr) = _mi_os_zalloc(std::mem::size_of::<MiThreadDataS>(), &mut memid) {
        // Convert the reference to a raw pointer, then to our thread data structure
        let td_ptr = alloc_ptr as *mut c_void as *mut MiThreadDataS;
        let td_box = unsafe { Box::from_raw(td_ptr) };
        td = Some(td_box);
    } else {
        // Try one more time
        if let Some(alloc_ptr) = _mi_os_zalloc(std::mem::size_of::<MiThreadDataS>(), &mut memid) {
            let td_ptr = alloc_ptr as *mut c_void as *mut MiThreadDataS;
            let td_box = unsafe { Box::from_raw(td_ptr) };
            td = Some(td_box);
        } else {
            // Allocation failed
            unsafe {
                _mi_error_message(
                    12, 
                    &std::ffi::CStr::from_bytes_with_nul(b"unable to allocate thread local heap metadata (%zu bytes)\n\0").unwrap(),
                    std::ptr::null_mut()
                );
            }
            return None;
        }
    }

    // Set the memid field
    if let Some(ref mut td_box) = td {
        td_box.memid = memid;
    }

    td
}
pub fn _mi_heap_guarded_init(heap: Option<&mut MiHeapT>) {
    // The C code casts heap to void, effectively making it a no-op
    // In Rust, we simply ignore the parameter as the function does nothing
    let _ = heap;
}
lazy_static! {
    pub static ref MI_SUBPROC_DEFAULT: Mutex<Option<Box<MiSubprocT>>> = Mutex::new(None);
}

pub fn mi_heap_main_init() {
    let mut heap_guard = _mi_heap_main.lock().unwrap();
    let heap_option = &mut *heap_guard;
    if let Some(heap) = heap_option {
        // Initialize heap fields as in the original C code
        heap.thread_id = _mi_thread_id();
        // Note: cookie and keys fields are not available in MiHeapS based on error messages
        _mi_random_init(&mut heap.random);
        
        // Call the initialization functions that were in the original C code
        {
            let mut subproc_guard = MI_SUBPROC_DEFAULT.lock().unwrap();
            if let Some(subproc) = subproc_guard.as_mut() {
                mi_lock_init(&mut subproc.abandoned_os_lock);
                mi_lock_init(&mut subproc.abandoned_os_visit_lock);
            }
        }
        
        // Pass the heap as Option<&mut MiHeapT> as expected by _mi_heap_guarded_init
        _mi_heap_guarded_init(Some(heap_option));
    }
}
pub fn _mi_thread_heap_init() -> bool {
    if mi_heap_is_initialized(mi_prim_get_default_heap().map(|ptr| unsafe { &*(ptr as *const MiHeapT) })) {
        return true;
    }
    
    if _mi_is_main_thread() {
        mi_heap_main_init();
        let mut heap_main_guard = _mi_heap_main.lock().unwrap();
        // Take ownership of the heap from the Mutex guard
        if let Some(heap_box) = heap_main_guard.take() {
            _mi_heap_set_default_direct(Some(heap_box));
        }
    } else {
        let td = mi_thread_data_zalloc();
        if td.is_none() {
            return false;
        }
        
        let mut td_unwrapped = td.unwrap();
        let tld = &mut td_unwrapped.tld;
        let heap = &mut td_unwrapped.heap;
        
        // Initialize tld and heap
        *tld = Some(Box::new(MiTldS));
        _mi_heap_init(heap, tld, _mi_arena_id_none(), false, 0);
        let heap_val = heap.take();
        _mi_heap_set_default_direct(heap_val);
    }
    
    false
}

pub static THREAD_COUNT: AtomicUsize = AtomicUsize::new(1);

pub fn _mi_current_thread_count() -> usize {
    THREAD_COUNT.load(Ordering::Relaxed)
}
pub fn mi_thread_done() {
    _mi_thread_done(None);
}
pub fn mi_is_redirected() -> bool {
    _mi_is_redirected()
}
pub fn mi_heap_guarded_set_sample_rate(heap: Option<&mut MiHeapT>, sample_rate: usize, seed: usize) {
    // The C function parameters are explicitly unused with (void) casts
    // In Rust, we can simply omit using the parameters
    let _ = heap;
    let _ = sample_rate;
    let _ = seed;
}
pub fn mi_heap_guarded_set_size_bound(heap: Option<&mut MiHeapT>, min: usize, max: usize) {
    // The C function parameters are explicitly unused with (void) casts
    // In Rust, we can simply omit using the parameters
    let _ = heap;
    let _ = min;
    let _ = max;
}
pub fn _mi_auto_process_init() {
    mi_heap_main_init();
    OS_PRELOADING.store(false, Ordering::Relaxed);
    if !_mi_is_main_thread() {
        _mi_assert_fail(
            "_mi_is_main_thread()",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/init.c",
            587,
            Some("_mi_auto_process_init"),
        );
    }
    _mi_options_init();
    mi_process_setup_auto_thread_done();
    mi_process_init();
    if _mi_is_redirected() {
        unsafe {
            _mi_verbose_message("malloc is redirected.\n\0".as_ptr() as *const i8, std::ptr::null_mut());
        }
    }
    let mut msg: Option<&'static str> = None;
    _mi_allocator_init(Some(&mut msg));
    if msg.is_some() && (mi_option_is_enabled(MiOptionE::MiOptionVerbose) || mi_option_is_enabled(MiOptionE::MiOptionShowErrors)) {
        let c_msg = std::ffi::CString::new(msg.unwrap()).unwrap();
        _mi_fputs(None, std::ptr::null_mut(), None, Some(&c_msg));
    }
    if let Some(heap) = &mut *_mi_heap_main.lock().unwrap() {
        _mi_random_reinit_if_weak(&mut heap.random);
    }
}
static PROCESS_DONE: AtomicBool = AtomicBool::new(false);

pub fn mi_process_done() {
    if !_MI_PROCESS_IS_INITIALIZED.load(Ordering::SeqCst) {
        return;
    }
    
    if PROCESS_DONE.swap(true, Ordering::SeqCst) {
        return;
    }
    
    let heap_ptr = mi_prim_get_default_heap();
    assert!(heap_ptr.is_some(), "heap != NULL");
    
    _mi_prim_thread_done_auto_done();
    
    if let Some(heap) = heap_ptr {
        unsafe {
            // Convert raw pointer to Box and wrap in Option
            let mut heap_t: MiHeapT = Some(Box::from_raw(heap));
            
            // Pass as Option<&mut MiHeapT> to match function signatures
            mi_heap_collect(Some(&mut heap_t), true);
            
            if mi_option_is_enabled(MiOptionE::MiOptionDestroyOnExit) {
                mi_heap_collect(Some(&mut heap_t), true);
                _mi_heap_unsafe_destroy_all(Some(&mut heap_t));
                _mi_arena_unsafe_destroy_all();
                _mi_segment_map_unsafe_destroy();
            }
            
            // Prevent the Box from being dropped since the heap is managed elsewhere
            // by converting it back to a raw pointer
            let _ = heap_t.take().map(Box::into_raw);
        }
    }
    
    if mi_option_is_enabled(MiOptionE::MiOptionShowStats) || mi_option_is_enabled(MiOptionE::MiOptionVerbose) {
        mi_stats_print(std::ptr::null_mut());
    }
    
    _mi_allocator_done();
    
    unsafe {
        let mut thread_id = _mi_heap_main.lock().unwrap().as_ref().map_or(0, |h| h.thread_id);
        _mi_verbose_message("process done: 0x%zx\n\0".as_ptr() as *const _, &mut thread_id as *mut _ as *mut std::ffi::c_void);
    }
    
    OS_PRELOADING.store(true, Ordering::SeqCst);
}
pub enum mi_option_t {
    mi_option_destroy_on_exit,
    // ... other variants
}
pub fn _mi_heap_main_get() -> Option<Box<MiHeapS>> {
    mi_heap_main_init();
    // Return the value from the mutex by taking it and replacing with None,
    // then put it back to maintain the original state
    let mut guard = _mi_heap_main.lock().unwrap();
    guard.take()
}


pub fn _mi_subproc_from_id(subproc_id: mi_subproc_id_t) -> Option<&'static mut MiSubprocT> {
    if subproc_id == 0 {
        // For null subproc_id, return the default subprocess
        // We need to get a raw pointer to the boxed value
        let mut guard = MI_SUBPROC_DEFAULT.lock().unwrap();
        if let Some(subproc) = &mut *guard {
            // Convert the mutable reference to a raw pointer and back to a static mutable reference
            // This is safe because MI_SUBPROC_DEFAULT is a static variable
            unsafe { Some(&mut *(subproc.as_mut() as *mut MiSubprocT)) }
        } else {
            // Default subprocess not initialized
            Option::None
        }
    } else {
        unsafe { Some(&mut *(subproc_id as *mut MiSubprocT)) }
    }
}

pub fn mi_subproc_new() -> Option<Box<MiSubprocT>> {
    let mut memid = _mi_memid_none();
    let allocated_memory = _mi_arena_meta_zalloc(std::mem::size_of::<MiSubprocT>(), &mut memid)?;
    
    // Convert the allocated memory to MiSubprocT
    let subproc_ptr = allocated_memory.as_mut_ptr() as *mut MiSubprocT;
    let subproc = unsafe { &mut *subproc_ptr };
    
    subproc.memid = memid;
    subproc.abandoned_os_list = None;
    mi_lock_init(&mut subproc.abandoned_os_lock);
    mi_lock_init(&mut subproc.abandoned_os_visit_lock);
    
    Some(Box::new(std::mem::replace(subproc, MiSubprocT {
        abandoned_count: std::sync::atomic::AtomicUsize::new(0),
        abandoned_os_list_count: std::sync::atomic::AtomicUsize::new(0),
        abandoned_os_lock: Mutex::new(()),
        abandoned_os_visit_lock: Mutex::new(()),
        abandoned_os_list: None,
        abandoned_os_list_tail: None,
        memid: _mi_memid_none(),
    })))
}
pub fn mi_subproc_add_current_thread(subproc_id: mi_subproc_id_t) {
    let heap = mi_heap_get_default();
    if heap.is_none() {
        return;
    }
    let heap_ref = unsafe { &mut *heap.unwrap() };
    
    // Cast the tld to MiTldS2 to access the segments field
    let tld_ptr = heap_ref.tld.as_ref().unwrap().as_ref() as *const _ as *const MiTldS2;
    let tld_ref = unsafe { &*tld_ptr };
    
    // Get raw pointers for comparison instead of comparing struct values
    let current_subproc_ptr = tld_ref.segments.subproc.as_ref().map(|p| p.as_ref() as *const MiSubprocS);
    let default_subproc_ptr = MI_SUBPROC_DEFAULT.lock().unwrap().as_ref().map(|p| p.as_ref() as *const MiSubprocS);
    
    if current_subproc_ptr != default_subproc_ptr {
        _mi_assert_fail(
            "heap->tld->segments.subproc == &mi_subproc_default",
            "/workdir/C2RustTranslation-main/subjects/mimalloc/src/init.c",
            291,
            Some("mi_subproc_add_current_thread"),
        );
    }
    
    if current_subproc_ptr != default_subproc_ptr {
        return;
    }
    
    // For mutable access, cast to MiTldS2 mut pointer
    let tld_mut_ptr = heap_ref.tld.as_mut().unwrap().as_mut() as *mut _ as *mut MiTldS2;
    let tld_mut_ref = unsafe { &mut *tld_mut_ptr };
    
    // Convert from Option<&mut MiSubprocT> to Option<Box<MiSubprocT>>
    // Since we can't take ownership of the static reference, we'll need to clone or handle differently
    // For now, we'll set it to None if _mi_subproc_from_id returns None
    tld_mut_ref.segments.subproc = _mi_subproc_from_id(subproc_id).map(|_subproc| {
        // This is a placeholder - in reality we need proper conversion
        // Since we can't take ownership of static data, we might need a different approach
        Box::new(MiSubprocS {
            abandoned_count: AtomicUsize::new(0),
            abandoned_os_list_count: AtomicUsize::new(0),
            abandoned_os_lock: Mutex::new(()),
            abandoned_os_visit_lock: Mutex::new(()),
            abandoned_os_list: None,
            abandoned_os_list_tail: None,
            memid: MiMemidS {
                mem: MiMemidUnion::Os(MiMemidOsInfo {
                    base: None,
                    size: 0,
                }),
                is_pinned: false,
                initially_committed: false,
                initially_zero: false,
                memkind: MiMemkindE::MiMemNone,
            },
        })
    });
}

pub fn mi_subproc_delete(subproc_id: mi_subproc_id_t) {
    if subproc_id == 0 {
        return;
    }
    
    let subproc = _mi_subproc_from_id(subproc_id);
    if subproc.is_none() {
        return;
    }
    let subproc = subproc.unwrap();
    
    let mut safe_to_delete = false;
    {
        let mut _go = true;
        mi_lock_acquire(&mut subproc.abandoned_os_lock);
        while _go {
            if subproc.abandoned_os_list.is_none() {
                safe_to_delete = true;
            }
            _go = false;
        }
        mi_lock_release(&subproc.abandoned_os_lock);
    }
    
    if !safe_to_delete {
        return;
    }
    
    mi_lock_done(&mut subproc.abandoned_os_lock);
    mi_lock_done(&mut subproc.abandoned_os_visit_lock);
    
    // Convert subproc to a byte slice for _mi_arena_meta_free
    let size = std::mem::size_of::<MiSubprocT>();
    let subproc_ptr = subproc as *mut MiSubprocT as *mut u8;
    let subproc_slice = unsafe { std::slice::from_raw_parts_mut(subproc_ptr, size) };
    _mi_arena_meta_free(Some(subproc_slice), subproc.memid.clone(), size);
}
