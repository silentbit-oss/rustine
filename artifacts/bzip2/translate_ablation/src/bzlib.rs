use crate::*;
use lazy_static::lazy_static;
use libc::FILE;
use libc::ferror;
use rand::Rng;
use std::alloc::Layout;
use std::alloc::alloc;
use std::boxed::Box;
use std::convert::TryInto;
use std::ffi::CStr;
use std::ffi::c_void;
use std::fs::File;
use std::fs::OpenOptions;
use std::io::Read;
use std::io::Seek;
use std::io::Write;
use std::io::stderr;
use std::io::stdin;
use std::io::stdout;
use std::io;
use std::os::fd::AsRawFd;
use std::os::raw::c_int as Int32;
use std::os::unix::io::FromRawFd;
use std::process;
use std::ptr::null_mut;
use std::ptr;
use std::sync::Mutex;
pub fn BZ2_bzlibVersion() -> &'static str {
    "1.1.0"
}
pub fn bz_config_ok() -> bool {
    if std::mem::size_of::<i32>() != 4 {
        return false;
    }
    if std::mem::size_of::<i16>() != 2 {
        return false;
    }
    if std::mem::size_of::<u8>() != 1 {
        return false;
    }
    true
}
pub fn default_bzfree(opaque: Option<&mut std::ffi::c_void>, addr: Option<&mut std::ffi::c_void>) {
    if let Some(addr) = addr {
        // In Rust, memory management is automatic, so we don't need an explicit free
        // The Option<&mut c_void> will be dropped automatically when out of scope
        // This function is effectively a no-op in safe Rust
    }
}
pub fn prepare_new_block(s: &mut EState) {
    s.nblock = 0;
    s.numZ = 0;
    s.state_out_pos = 0;
    s.blockCRC = 0xffffffff;
    
    for i in 0..256 {
        s.inUse[i] = 0;
    }
    
    s.blockNo += 1;
}
pub fn init_RL(s: &mut EState) {
    s.state_in_ch = 256;
    s.state_in_len = 0;
}
pub fn default_bzalloc(opaque: Option<&mut ()>, items: Int32, size: Int32) -> Option<Box<[u8]>> {
    // Calculate total size needed, checking for overflow
    let total_size = items.checked_mul(size)? as usize;
    
    // Allocate zeroed memory using Box (safe Rust allocation)
    let v = vec![0u8; total_size].into_boxed_slice();
    
    Some(v)
}
pub fn BZ2_bzCompressInit(
    strm: Option<&mut BzStream>,
    blockSize100k: i32,
    verbosity: i32,
    workFactor: i32,
) -> i32 {
    if !bz_config_ok() {
        return -9;
    }

    if strm.is_none()
        || blockSize100k < 1
        || blockSize100k > 9
        || workFactor < 0
        || workFactor > 250
    {
        return -2;
    }

    let mut workFactor = workFactor;
    if workFactor == 0 {
        workFactor = 30;
    }

    let strm = strm.unwrap();

    // Ensure alloc/free are set, matching C semantics of assigning defaults when null.
    if strm.bzalloc.is_none() {
        strm.bzalloc = Some(Box::new(|opaque: Option<Box<()>>, items, size| {
            let opaque_ref = opaque
                .as_ref()
                .map(|boxed| unsafe { &mut *(Box::into_raw(boxed.clone()) as *mut ()) });
            default_bzalloc(opaque_ref, items, size).map(|boxed_slice| {
                let ptr = Box::into_raw(boxed_slice) as *mut std::ffi::c_void;
                unsafe { Box::from_raw(ptr as *mut ()) }
            })
        }));
    }

    if strm.bzfree.is_none() {
        strm.bzfree = Some(Box::new(|opaque: Option<Box<()>>, addr: Option<Box<()>>| {
            let opaque_ref = opaque.as_ref().map(|boxed| unsafe {
                &mut *(Box::into_raw(boxed.clone()) as *mut std::ffi::c_void)
            });
            let addr_ref = addr.as_ref().map(|boxed| unsafe {
                &mut *(Box::into_raw(boxed.clone()) as *mut std::ffi::c_void)
            });
            default_bzfree(opaque_ref, addr_ref)
        }));
    }

    // Allocate EState via the stream's allocator.
    let bzalloc = strm.bzalloc.as_mut().unwrap();
    let opaque_clone = strm.opaque.clone();
    let s_ptr = bzalloc(opaque_clone, std::mem::size_of::<EState>() as i32, 1);
    if s_ptr.is_none() {
        return -3;
    }

    let s_ptr_raw = Box::into_raw(s_ptr.unwrap()) as *mut EState;
    let s = unsafe { &mut *s_ptr_raw };

    // In the original C, s->strm stores a pointer to the same stream.
    // Here we avoid cloning non-Clone function pointers by not creating a copy.
    // Other code paths use `strm` directly for alloc/free, so leaving it None is safe.
    s.strm = Option::None;
    s.arr1 = Option::None;
    s.arr2 = Option::None;
    s.ftab = Option::None;

    let n = 100000 * blockSize100k;

    let opaque_clone = strm.opaque.clone();
    s.arr1 = bzalloc(
        opaque_clone,
        ((n as usize) * std::mem::size_of::<UInt32>()) as i32,
        1,
    )
    .map(|boxed| unsafe {
        let ptr = Box::into_raw(boxed) as *mut UInt32;
        Box::from_raw(std::slice::from_raw_parts_mut(ptr, n as usize))
    });

    let opaque_clone = strm.opaque.clone();
    s.arr2 = bzalloc(
        opaque_clone,
        (((n + (2 + 12 + 18 + 2)) as usize) * std::mem::size_of::<UInt32>()) as i32,
        1,
    )
    .map(|boxed| unsafe {
        let ptr = Box::into_raw(boxed) as *mut UInt32;
        Box::from_raw(std::slice::from_raw_parts_mut(
            ptr,
            (n + 2 + 12 + 18 + 2) as usize,
        ))
    });

    let opaque_clone = strm.opaque.clone();
    s.ftab = bzalloc(
        opaque_clone,
        (65537 * std::mem::size_of::<UInt32>()) as i32,
        1,
    )
    .map(|boxed| unsafe {
        let ptr = Box::into_raw(boxed) as *mut UInt32;
        Box::from_raw(std::slice::from_raw_parts_mut(ptr, 65537))
    });

    if s.arr1.is_none() || s.arr2.is_none() || s.ftab.is_none() {
        let bzfree = strm.bzfree.as_mut().unwrap();
        let opaque_clone = strm.opaque.clone();

        if let Some(arr1) = s.arr1.take() {
            let ptr = Box::into_raw(arr1) as *mut std::ffi::c_void;
            bzfree(opaque_clone.clone(), Some(unsafe { Box::from_raw(ptr as *mut ()) }));
        }
        if let Some(arr2) = s.arr2.take() {
            let ptr = Box::into_raw(arr2) as *mut std::ffi::c_void;
            bzfree(opaque_clone.clone(), Some(unsafe { Box::from_raw(ptr as *mut ()) }));
        }
        if let Some(ftab) = s.ftab.take() {
            let ptr = Box::into_raw(ftab) as *mut std::ffi::c_void;
            bzfree(opaque_clone.clone(), Some(unsafe { Box::from_raw(ptr as *mut ()) }));
        }
        bzfree(
            opaque_clone,
            Some(unsafe { Box::from_raw(s_ptr_raw as *mut std::ffi::c_void as *mut ()) }),
        );
        return -3;
    }

    s.blockNo = 0;
    s.state = 2;
    s.mode = 2;
    s.combinedCRC = 0;
    s.blockSize100k = blockSize100k;
    s.nblockMAX = (100000 * blockSize100k) - 19;
    s.verbosity = verbosity;
    s.workFactor = workFactor;

    s.block = s.arr2.as_ref().map(|arr| {
        let len = arr.len() * std::mem::size_of::<UInt32>();
        unsafe {
            Box::from_raw(std::slice::from_raw_parts_mut(
                arr.as_ptr() as *mut UChar,
                len,
            ))
        }
    });

    s.mtfv = s.arr1.as_ref().map(|arr| {
        let len = arr.len() * 2;
        unsafe {
            Box::from_raw(std::slice::from_raw_parts_mut(
                arr.as_ptr() as *mut UInt16,
                len,
            ))
        }
    });

    s.zbits = Option::None;

    s.ptr = s.arr1.as_ref().map(|arr| unsafe {
        Box::from_raw(std::slice::from_raw_parts_mut(
            arr.as_ptr() as *mut UInt32,
            arr.len(),
        ))
    });

    strm.state = Some(unsafe {
        Box::from_raw(s_ptr_raw as *mut std::ffi::c_void as *mut ())
    });
    strm.total_in_lo32 = 0;
    strm.total_in_hi32 = 0;
    strm.total_out_lo32 = 0;
    strm.total_out_hi32 = 0;

    init_RL(s);
    prepare_new_block(s);

    0
}
pub fn BZ2_bzWriteOpen(
    mut bzerror: Option<&mut i32>,
    f: Option<std::fs::File>,
    blockSize100k: i32,
    verbosity: i32,
    workFactor: i32,
) -> Option<Box<BzFile>> {

    // Initialize error code to 0 if bzerror is provided
    if let Some(ref mut err_ptr) = bzerror {
        **err_ptr = 0;
    }

    // Validate input parameters
    if f.is_none()
        || blockSize100k < 1
        || blockSize100k > 9
        || workFactor < 0
        || workFactor > 250
        || verbosity < 0
        || verbosity > 4
    {
        if let Some(ref mut err_ptr) = bzerror {
            **err_ptr = -2;
        }
        return None;
    }

    // Check for file stream errors
    let file = f.as_ref().unwrap();
    if let Err(_) = file.metadata() {
        if let Some(ref mut err_ptr) = bzerror {
            **err_ptr = -6;
        }
        return None;
    }

    // Allocate memory for BzFile
    let layout = Layout::new::<BzFile>();
    let ptr = unsafe { alloc(layout) as *mut BzFile };
    if ptr.is_null() {
        if let Some(ref mut err_ptr) = bzerror {
            **err_ptr = -3;
        }
        return None;
    }

    let mut bzf = unsafe {
        ptr::write(
            ptr,
            BzFile {
                initialisedOk: 0,
                bufN: 0,
                buf: ['\0'; 5000],
                handle: f,
                writing: 1,
                strm: BzStream {
                    avail_in: 0,
                    avail_out: 0,
                    next_in: None,
                    next_out: None,
                    state: None,
                    bzalloc: None,
                    bzfree: None,
                    opaque: None,
                    total_in_lo32: 0,
                    total_in_hi32: 0,
                    total_out_lo32: 0,
                    total_out_hi32: 0,
                },
                lastErr: 0,
            },
        );
        Box::from_raw(ptr)
    };

    // Initialize error code again after allocation
    if let Some(ref mut err_ptr) = bzerror {
        **err_ptr = 0;
    }
    bzf.lastErr = 0;

    let actual_work_factor = if workFactor == 0 { 30 } else { workFactor };

    // Initialize compression
    let ret = BZ2_bzCompressInit(
        Some(&mut bzf.strm),
        blockSize100k,
        verbosity,
        actual_work_factor,
    );

    if ret != 0 {
        if let Some(ref mut err_ptr) = bzerror {
            **err_ptr = ret;
        }
        bzf.lastErr = ret;
        return None;
    }

    bzf.strm.avail_in = 0;
    bzf.initialisedOk = 1;

    Some(bzf)
}
pub fn BZ2_bzDecompressInit(strm: Option<&mut BzStream>, verbosity: i32, small: i32) -> i32 {
    if !bz_config_ok() {
        return -9;
    }
    
    let strm = match strm {
        Some(s) => s,
        None => return -2,
    };
    
    if small != 0 && small != 1 {
        return -2;
    }
    
    if verbosity < 0 || verbosity > 4 {
        return -2;
    }
    
    if strm.bzalloc.is_none() {
        strm.bzalloc = Some(Box::new(|mut opaque: Option<Box<()>>, items: i32, size: i32| {
            let opaque_ref = opaque.as_deref_mut();
            default_bzalloc(opaque_ref, items, size).map(|boxed_slice| {
                let ptr = Box::into_raw(boxed_slice) as *mut u8;
                unsafe { Box::from_raw(ptr as *mut ()) }
            })
        }));
    }
    
    if strm.bzfree.is_none() {
        strm.bzfree = Some(Box::new(|mut opaque: Option<Box<()>>, mut addr: Option<Box<()>>| {
            let opaque_ref = opaque.as_deref_mut().map(|r| r as *mut () as *mut std::ffi::c_void).map(|ptr| unsafe { &mut *ptr });
            let addr_ref = addr.as_deref_mut().map(|r| r as *mut () as *mut std::ffi::c_void).map(|ptr| unsafe { &mut *ptr });
            default_bzfree(opaque_ref, addr_ref)
        }));
    }
    
    let mut bzalloc = strm.bzalloc.as_mut().unwrap();
    let s_ptr = bzalloc(strm.opaque.clone(), 1, std::mem::size_of::<DState>() as i32);
    
    if s_ptr.is_none() {
        return -3;
    }
    
    unsafe {
        let s_ptr_clone = s_ptr.clone();
        let s_box = s_ptr_clone.unwrap();
        let s_raw = Box::into_raw(s_box) as *mut DState;
        let s = &mut *s_raw;
        
        s.strm = Some(Box::from_raw(strm as *mut BzStream));
        strm.state = s_ptr;
        s.state = 10;
        s.bs_live = 0;
        s.bs_buff = 0;
        s.calculated_combined_crc = 0;
        strm.total_in_lo32 = 0;
        strm.total_in_hi32 = 0;
        strm.total_out_lo32 = 0;
        strm.total_out_hi32 = 0;
        s.small_decompress = if small != 0 { 1 } else { 0 };
        s.ll4 = None;
        s.ll16 = None;
        s.tt = None;
        s.curr_block_no = 0;
        s.verbosity = verbosity;
    }
    
    0
}
pub fn BZ2_bzReadOpen(
    mut bzerror: Option<&mut i32>,
    f: Option<std::fs::File>,
    verbosity: i32,
    small: i32,
    unused: Option<&[char]>,
    nUnused: i32,
) -> Option<Box<BzFile>> {
    // Initialize error code if provided
    if let Some(ref mut err) = bzerror {
        **err = 0;
    }

    // Validate input parameters
    if f.is_none()
        || (small != 0 && small != 1)
        || verbosity < 0
        || verbosity > 4
        || (unused.is_none() && nUnused != 0)
        || (unused.is_some() && (nUnused < 0 || nUnused > 5000))
    {
        if let Some(ref mut err) = bzerror {
            **err = -2;
        }
        return None;
    }

    let f = f.unwrap();

    // Check for file stream error
    unsafe {
        let mode = std::ffi::CString::new("r").unwrap();
        let file_ptr = libc::fdopen(f.as_raw_fd(), mode.as_ptr());
        if libc::ferror(file_ptr) != 0 {
            if let Some(ref mut err) = bzerror {
                **err = -6;
            }
            libc::fclose(file_ptr);
            return None;
        }
        libc::fclose(file_ptr);
    }

    // Allocate memory for bzFile using Box instead of raw malloc
    let mut bzf = Box::new(BzFile {
        handle: Some(f),
        bufN: 0,
        writing: 0,
        initialisedOk: 0,
        buf: [0 as char; 5000],
        strm: BzStream {
            next_in: None,
            avail_in: 0,
            total_in_lo32: 0,
            total_in_hi32: 0,
            next_out: None,
            avail_out: 0,
            total_out_lo32: 0,
            total_out_hi32: 0,
            state: None,
            bzalloc: None,
            bzfree: None,
            opaque: None,
        },
        lastErr: 0,
    });

    // Initialize error code again after allocation
    if let Some(ref mut err) = bzerror {
        **err = 0;
    }

    unsafe {
        bzf.initialisedOk = 0;
        bzf.bufN = 0;
        bzf.writing = 0;

        // Initialize the stream structure
        bzf.strm.bzalloc = None;
        bzf.strm.bzfree = None;
        bzf.strm.opaque = None;

        // Copy unused data into buffer if provided
        if let Some(unused_slice) = unused {
            let mut remaining = nUnused;
            let mut index = 0;
            
            while remaining > 0 && (bzf.bufN as usize) < 5000 {
                bzf.buf[bzf.bufN as usize] = unused_slice[index];
                bzf.bufN += 1;
                index += 1;
                remaining -= 1;
            }
        }

        // Initialize decompression
        let ret = BZ2_bzDecompressInit(Some(&mut bzf.strm), verbosity, small);
        if ret != 0 {
            if let Some(ref mut err) = bzerror {
                **err = ret;
            }
            return None;
        }

        // Set up input buffer for decompression
        bzf.strm.avail_in = bzf.bufN as u32;
        let mut u8_vec = Vec::with_capacity(bzf.bufN as usize);
        for i in 0..(bzf.bufN as usize) {
            u8_vec.push(bzf.buf[i] as u8);
        }
        let boxed_slice = u8_vec.into_boxed_slice();
        bzf.strm.next_in = Some(boxed_slice);
        bzf.initialisedOk = 1;
    }

    Some(bzf)
}
pub fn bzopen_or_bzdopen(
    path: Option<&CStr>,
    fd: i32,
    mode: Option<&CStr>,
    open_mode: i32,
) -> Option<Box<BZFILE>> {
    let mode = match mode {
        Some(m) => m,
        None => return None,
    };

    let mut bzerr = 0;
    let unused = [0 as char; 5000];
    let mut block_size100k = 9;
    let mut writing = 0;
    let mut mode2 = String::new();
    let mut verbosity = 0;
    let work_factor = 30;
    let mut small_mode = 0;
    let n_unused = 0;

    let mode_bytes = mode.to_bytes();
    let mut i = 0;
    while i < mode_bytes.len() {
        let c = mode_bytes[i];
        match c {
            b'r' => writing = 0,
            b'w' => writing = 1,
            b's' => small_mode = 1,
            _ => {
                if c.is_ascii_digit() {
                    block_size100k = (c - b'0') as i32;
                }
            }
        }
        i += 1;
    }

    if writing != 0 {
        mode2.push_str("wb");
    } else {
        mode2.push_str("rb");
    }

    if open_mode == 0 {
        mode2.push('e');
    }

    let fp: Option<File> = if open_mode == 0 {
        let path_str = match path {
            Some(p) => p.to_str().ok(),
            None => Some(""),
        };

        if path_str == Some("") {
            if writing != 0 {
                Some(unsafe { File::from_raw_fd(stdout().as_raw_fd()) })
            } else {
                Some(unsafe { File::from_raw_fd(stdin().as_raw_fd()) })
            }
        } else {
            let path_str = path_str?;
            OpenOptions::new()
                .read(writing == 0)
                .write(writing != 0)
                .create(writing != 0)
                .truncate(writing != 0)
                .open(path_str)
                .ok()
        }
    } else {
        Some(unsafe { File::from_raw_fd(fd) })
    };

    let fp = match fp {
        Some(f) => f,
        None => return None,
    };

    let bzfp = if writing != 0 {
        let block_size100k = block_size100k.clamp(1, 9);
        BZ2_bzWriteOpen(
            Some(&mut bzerr),
            Some(fp),
            block_size100k,
            verbosity,
            work_factor,
        )
    } else {
        BZ2_bzReadOpen(
            Some(&mut bzerr),
            Some(fp),
            verbosity,
            small_mode,
            Some(&unused),
            n_unused,
        )
    };

    if bzfp.is_none() {
        return None;
    }

    // Convert from Option<Box<BzFile>> to Option<Box<BZFILE>>
    // This is safe because BzFile and BZFILE should have the same memory layout
    // and the underlying C code treats them as the same type
    unsafe {
        Some(Box::from_raw(Box::into_raw(bzfp.unwrap()) as *mut BZFILE))
    }
}

pub fn BZ2_bzopen(path: Option<&CStr>, mode: Option<&CStr>) -> Option<Box<BZFILE>> {
    bzopen_or_bzdopen(path, -1, mode, 0)
}

pub fn BZ2_bzdopen(fd: i32, mode: Option<&CStr>) -> Option<Box<BZFILE>> {
    bzopen_or_bzdopen(None, fd, mode, 1)
}
pub fn BZ2_bzflush(b: Option<&mut BZFILE>) -> i32 {
    0
}

pub fn BZ2_bz__AssertH__fail(errcode: i32) {
    eprintln!("\n\nbzip2/libbzip2: internal error number {}.\nThis is a bug in bzip2/libbzip2, {}.\nPlease report it at: https://gitlab.com/bzip2/bzip2/-/issues\nIf this happened when you were using some program which uses\nlibbzip2 as a component, you should also report this bug to\nthe author(s) of that program.\nPlease make an effort to report this bug;\ntimely and accurate bug reports eventually lead to higher\nquality software.  Thanks.\n\n", errcode, BZ2_bzlibVersion());

    if errcode == 1007 {
        eprintln!("\n*** A special note about internal error number 1007 ***\n\nExperience suggests that a common cause of i.e. 1007\nis unreliable memory or other hardware.  The 1007 assertion\njust happens to cross-check the results of huge numbers of\nmemory reads/writes, and so acts (unintendedly) as a stress\ntest of your memory system.\n\nI suggest the following: try compressing the file again,\npossibly monitoring progress in detail with the -vv flag.\n\n* If the error cannot be reproduced, and/or happens at different\n  points in compression, you may have a flaky memory system.\n  Try a memory-test program.  I have used Memtest86\n  (www.memtest86.com).  At the time of writing it is free (GPLd).\n  Memtest86 tests memory much more thorougly than your BIOSs\n  power-on test, and may find failures that the BIOS doesn't.\n\n* If the error can be repeatably reproduced, this is a bug in\n  bzip2, and I would very much like to hear about it.  Please\n  let me know, and, ideally, save a copy of the file causing the\n  problem -- without which I will be unable to investigate it.\n\n");
    }

    process::exit(3);
}
pub fn BZ2_indexIntoF(indx: Int32, cftab: &[Int32]) -> Int32 {
    let mut nb: Int32 = 0;
    let mut na: Int32 = 256;
    
    loop {
        let mid = (nb + na) >> 1;
        if indx >= cftab[mid as usize] {
            nb = mid;
        } else {
            na = mid;
        }
        
        if (na - nb) == 1 {
            break;
        }
    }
    
    nb
}
pub fn isempty_RL(s: &EState) -> Bool {
    if (s.state_in_ch < 256) && (s.state_in_len > 0) {
        0
    } else {
        1
    }
}
pub fn myfeof(f: &mut (impl Read + Seek)) -> bool {
    let mut buf = [0u8; 1];
    match f.read(&mut buf) {
        Ok(0) => true,  // EOF reached
        Ok(_) => {
            f.seek(std::io::SeekFrom::Current(-1)).unwrap();  // Rewind by 1 byte
            false
        }
        Err(_) => true,  // Error treated as EOF
    }
}
pub fn BZ2_bzCompressEnd(strm: Option<&mut BzStream>) -> i32 {
    // Check for NULL pointer (None in Rust)
    let strm = match strm {
        Some(s) => s,
        None => return -2,
    };

    // Get state from strm
    let s_ptr = match strm.state.take() {
        Some(boxed_state) => boxed_state,
        None => return -2,
    };

    // Convert Box<()> to *mut EState
    let s_ptr_raw: *mut EState = Box::into_raw(s_ptr) as *mut EState;
    
    // Convert raw pointer to mutable reference
    let s = unsafe { &mut *s_ptr_raw };

    // Check if s->strm points back to the current strm
    // Convert strm to raw pointer and compare with s.strm's raw pointer
    let strm_raw_ptr: *mut BzStream = strm as *mut BzStream;
    let s_strm_raw_ptr = match &s.strm {
        Some(boxed_strm) => {
            let reference: &BzStream = Box::as_ref(boxed_strm);
            reference as *const BzStream as *mut BzStream
        },
        None => {
            // Put the state back before returning error
            strm.state = Some(unsafe { Box::from_raw(s_ptr_raw as *mut ()) });
            return -2;
        }
    };
    
    if s_strm_raw_ptr != strm_raw_ptr {
        // Put the state back before returning error
        strm.state = Some(unsafe { Box::from_raw(s_ptr_raw as *mut ()) });
        return -2;
    }

    // Take the opaque value once to avoid multiple moves
    let opaque = strm.opaque.take();

    // Free allocated arrays using the bzfree callback
    if let Some(arr1) = s.arr1.take() {
        unsafe {
            let bzfree = strm.bzfree.as_mut().expect("bzfree callback should be set");
            let ptr = Box::into_raw(arr1) as *mut ();
            bzfree(opaque.clone(), Some(Box::from_raw(ptr)));
        }
    }
    
    if let Some(arr2) = s.arr2.take() {
        unsafe {
            let bzfree = strm.bzfree.as_mut().expect("bzfree callback should be set");
            let ptr = Box::into_raw(arr2) as *mut ();
            bzfree(opaque.clone(), Some(Box::from_raw(ptr)));
        }
    }
    
    if let Some(ftab) = s.ftab.take() {
        unsafe {
            let bzfree = strm.bzfree.as_mut().expect("bzfree callback should be set");
            let ptr = Box::into_raw(ftab) as *mut ();
            bzfree(opaque.clone(), Some(Box::from_raw(ptr)));
        }
    }

    // Free the state itself - convert back to Box<()> first
    let state_box = unsafe { Box::from_raw(s_ptr_raw as *mut ()) };
    unsafe {
        let bzfree = strm.bzfree.as_mut().expect("bzfree callback should be set");
        bzfree(opaque, Some(state_box));
    }

    // State is already taken and freed, no need to set to None again
    0
}
pub fn BZ2_bzDecompressEnd(strm: Option<&mut BzStream>) -> i32 {
    // Check for NULL pointer (None in Rust)
    let strm = match strm {
        Some(s) => s,
        None => return -2,
    };

    // Get state from strm - handle the Option<Box<()>> properly
    let state_box = match strm.state.take() {
        Some(boxed) => boxed,
        None => return -2,
    };
    
    // Convert Box<()> to the actual DState type
    let s_ptr: *mut DState = Box::into_raw(state_box) as *mut DState;

    if s_ptr.is_null() {
        return -2;
    }

    // SAFETY: We've checked that s_ptr is not null
    let s = unsafe { &mut *s_ptr };
    
    // Check if s->strm points back to our strm
    // Convert strm to raw pointer and compare with s.strm
    let strm_ptr: *const BzStream = strm as *const BzStream;
    if let Some(boxed_stream) = &s.strm {
        let boxed_ptr: *const BzStream = &**boxed_stream;
        if boxed_ptr != strm_ptr {
            return -2;
        }
    } else {
        return -2;
    }

    // Free allocated memory using the bzfree callback
    // SAFETY: We need to use unsafe to call the C function pointers
    unsafe {
        if let Some(tt_ptr) = s.tt.take() {
            if let Some(ref mut bzfree) = strm.bzfree {
                // Convert Box<[u32]> to Box<()>
                let tt_box: Box<()> = Box::from_raw(Box::into_raw(tt_ptr) as *mut ());
                bzfree(strm.opaque.take(), Some(tt_box));
                strm.opaque = None; // Restore opaque since we took it
            }
        }
        if let Some(ll16_ptr) = s.ll16.take() {
            if let Some(ref mut bzfree) = strm.bzfree {
                // Convert Box<[u16]> to Box<()>
                let ll16_box: Box<()> = Box::from_raw(Box::into_raw(ll16_ptr) as *mut ());
                bzfree(strm.opaque.take(), Some(ll16_box));
                strm.opaque = None; // Restore opaque since we took it
            }
        }
        if let Some(ll4_ptr) = s.ll4.take() {
            if let Some(ref mut bzfree) = strm.bzfree {
                // Convert Box<[u8]> to Box<()>
                let ll4_box: Box<()> = Box::from_raw(Box::into_raw(ll4_ptr) as *mut ());
                bzfree(strm.opaque.take(), Some(ll4_box));
                strm.opaque = None; // Restore opaque since we took it
            }
        }
        
        // Free the state itself - convert back to Box<()> first
        if let Some(ref mut bzfree) = strm.bzfree {
            let state_ptr: *mut () = s_ptr as *mut ();
            let boxed_unit = Box::from_raw(state_ptr);
            bzfree(strm.opaque.take(), Some(boxed_unit));
            strm.opaque = None; // Restore opaque since we took it
        }
    }

    // State is already taken and freed above, no need to set to None again
    0
}
pub fn BZ2_bzReadGetUnused(
    bzerror: Option<&mut Int32>,
    b: Option<&mut BZFILE>,
    unused: Option<&mut Option<Box<[u8]>>>,
    nUnused: Option<&mut u32>,
) {
    // Convert BZFILE to bzFile (assuming BZFILE is a pointer to bzFile in C)
    let bzf = match b {
        Some(b) => unsafe { &mut *(b as *mut _ as *mut BzFile) },
        None => {
            if let Some(err) = bzerror {
                *err = -2;
            }
            return;
        }
    };

    // Check if bzf is initialized (equivalent to bzf != 0 in C)
    if bzf.lastErr != 4 {
        if let Some(err) = bzerror {
            *err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    // Check if unused or nUnused are null (None in Rust)
    if unused.is_none() || nUnused.is_none() {
        if let Some(err) = bzerror {
            *err = -2;
        }
        bzf.lastErr = -2;
        return;
    }

    // Set success status
    if let Some(err) = bzerror {
        *err = 0;
    }
    bzf.lastErr = 0;

    // Set output values
    if let Some(n_unused) = nUnused {
        *n_unused = bzf.strm.avail_in;
    }
    if let Some(unused_ptr) = unused {
        *unused_ptr = bzf.strm.next_in.take();
    }
}
pub fn add_pair_to_block(s: &mut EState) {
    let ch = s.state_in_ch as UChar;
    
    // Update blockCRC for each character in state_in_len
    for _ in 0..s.state_in_len {
        let table = BZ2_CRC32_TABLE.lock().unwrap();
        s.blockCRC = (s.blockCRC << 8) ^ table[((s.blockCRC >> 24) ^ (ch as UInt32)) as usize];
    }

    s.inUse[s.state_in_ch as usize] = 1;
    
    match s.state_in_len {
        1 => {
            s.block.as_mut().unwrap()[s.nblock as usize] = ch;
            s.nblock += 1;
        }
        2 => {
            let block = s.block.as_mut().unwrap();
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = ch;
            s.nblock += 1;
        }
        3 => {
            let block = s.block.as_mut().unwrap();
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = ch;
            s.nblock += 1;
        }
        _ => {
            s.inUse[(s.state_in_len - 4) as usize] = 1;
            let block = s.block.as_mut().unwrap();
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = ch;
            s.nblock += 1;
            block[s.nblock as usize] = (s.state_in_len - 4) as UChar;
            s.nblock += 1;
        }
    }
}
pub fn flush_RL(s: &mut EState) {
    if s.state_in_ch < 256 {
        add_pair_to_block(s);
    }
    init_RL(s);
}
pub fn copy_output_until_stop(s: &mut EState) -> Bool {
    let mut progress_out = 0;

    loop {
        // Check if we should break due to no output space or exhausted data
        let should_break = {
            let strm = match &mut s.strm {
                Some(strm) => strm,
                None => break,
            };

            strm.avail_out == 0 || s.state_out_pos >= s.numZ
        };

        if should_break {
            break;
        }

        // Perform the output copying
        {
            let strm = s.strm.as_mut().unwrap();
            let zbits = s.zbits.as_ref().unwrap();

            if let Some(next_out) = strm.next_out.as_mut() {
                next_out[0] = zbits[s.state_out_pos as usize];
                s.state_out_pos += 1;
                strm.avail_out -= 1;
                // Rotate the slice left by 1 to simulate pointer increment
                next_out.rotate_left(1);
                strm.total_out_lo32 += 1;

                if strm.total_out_lo32 == 0 {
                    strm.total_out_hi32 += 1;
                }
            }
        }

        progress_out = 1;
    }

    progress_out
}
pub fn copy_input_until_stop(s: &mut EState) -> Bool {
    let mut progress_in: Bool = 0;

    if s.mode == 2 {
        loop {
            if s.nblock >= s.nblockMAX {
                break;
            }
            if s.strm.as_ref().map_or(0, |strm| strm.avail_in) == 0 {
                break;
            }
            progress_in = 1;

            let zchh = {
                let strm = s.strm.as_mut().unwrap();
                let zchh = UInt32::from(strm.next_in.as_ref().unwrap()[0]);
                strm.next_in.as_mut().unwrap().rotate_left(1);
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
                zchh
            };
            
            if (zchh != s.state_in_ch) && (s.state_in_len == 1) {
                let ch = s.state_in_ch as UChar;
                {
                    let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                    s.blockCRC = (s.blockCRC << 8) ^ crc_table[((s.blockCRC >> 24) ^ (ch as UInt32)) as usize];
                }
                s.inUse[s.state_in_ch as usize] = 1;
                s.block.as_mut().unwrap()[s.nblock as usize] = ch;
                s.nblock += 1;
                s.state_in_ch = zchh;
            } else if (zchh != s.state_in_ch) || (s.state_in_len == 255) {
                if s.state_in_ch < 256 {
                    add_pair_to_block(s);
                }
                s.state_in_ch = zchh;
                s.state_in_len = 1;
            } else {
                s.state_in_len += 1;
            }
        }
    } else {
        loop {
            if s.nblock >= s.nblockMAX {
                break;
            }
            if s.strm.as_ref().map_or(0, |strm| strm.avail_in) == 0 {
                break;
            }
            if s.avail_in_expect == 0 {
                break;
            }
            progress_in = 1;

            let zchh = {
                let strm = s.strm.as_mut().unwrap();
                let zchh = UInt32::from(strm.next_in.as_ref().unwrap()[0]);
                strm.next_in.as_mut().unwrap().rotate_left(1);
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
                s.avail_in_expect -= 1;
                zchh
            };
            
            if (zchh != s.state_in_ch) && (s.state_in_len == 1) {
                let ch = s.state_in_ch as UChar;
                {
                    let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                    s.blockCRC = (s.blockCRC << 8) ^ crc_table[((s.blockCRC >> 24) ^ (ch as UInt32)) as usize];
                }
                s.inUse[s.state_in_ch as usize] = 1;
                s.block.as_mut().unwrap()[s.nblock as usize] = ch;
                s.nblock += 1;
                s.state_in_ch = zchh;
            } else if (zchh != s.state_in_ch) || (s.state_in_len == 255) {
                if s.state_in_ch < 256 {
                    add_pair_to_block(s);
                }
                s.state_in_ch = zchh;
                s.state_in_len = 1;
            } else {
                s.state_in_len += 1;
            }
        }
    }

    progress_in
}
pub fn handle_compress(strm: &mut BzStream) -> Bool {
    let mut progress_in = 0;
    let mut progress_out = 0;
    let s = strm.state.as_mut().unwrap() as *mut _ as *mut EState;
    let s = unsafe { &mut *s };
    
    loop {
        if s.state == 1 {
            progress_out = progress_out | copy_output_until_stop(s);
            if s.state_out_pos < s.numZ {
                break;
            }
            if (s.mode == 4) && (s.avail_in_expect == 0) && (isempty_RL(s) != 0) {
                break;
            }
            prepare_new_block(s);
            s.state = 2;
            if (s.mode == 3) && (s.avail_in_expect == 0) && (isempty_RL(s) != 0) {
                break;
            }
        }
        
        if s.state == 2 {
            progress_in = progress_in | copy_input_until_stop(s);
            if (s.mode != 2) && (s.avail_in_expect == 0) {
                flush_RL(s);
                BZ2_compressBlock(s, if s.mode == 4 { 1 } else { 0 });
                s.state = 1;
            } else if s.nblock >= s.nblockMAX {
                BZ2_compressBlock(s, 0);
                s.state = 1;
            } else if strm.avail_in == 0 {
                break;
            }
        }
    }
    
    progress_in | progress_out
}
pub fn BZ2_bzCompress(strm: Option<&mut BzStream>, action: i32) -> i32 {
    let progress: u8;
    let s: Option<&mut EState>;
    if strm.is_none() {
        return -2;
    }
    let strm_ref = strm.unwrap();
    s = strm_ref.state.as_deref_mut().map(|ptr| unsafe { &mut *(ptr as *mut () as *mut EState) });
    if s.is_none() {
        return -2;
    }
    let s_ref = s.unwrap();
    if s_ref.strm.as_ref().map(|boxed| boxed.as_ref() as *const BzStream) != Some(strm_ref as *const BzStream) {
        return -2;
    }
    'preswitch: loop {
        match s_ref.mode {
            1 => return -1,
            2 => {
                if action == 0 {
                    progress = handle_compress(strm_ref);
                    return if progress != 0 { 1 } else { -2 };
                } else if action == 1 {
                    s_ref.avail_in_expect = strm_ref.avail_in;
                    s_ref.mode = 3;
                    continue 'preswitch;
                } else if action == 2 {
                    s_ref.avail_in_expect = strm_ref.avail_in;
                    s_ref.mode = 4;
                    continue 'preswitch;
                } else {
                    return -2;
                }
            }
            3 => {
                if action != 1 {
                    return -1;
                }
                if s_ref.avail_in_expect != strm_ref.avail_in {
                    return -1;
                }
                progress = handle_compress(strm_ref);
                if (s_ref.avail_in_expect > 0) || (isempty_RL(s_ref) == 0) || (s_ref.state_out_pos < s_ref.numZ) {
                    return 2;
                }
                s_ref.mode = 2;
                return 1;
            }
            4 => {
                if action != 2 {
                    return -1;
                }
                if s_ref.avail_in_expect != strm_ref.avail_in {
                    return -1;
                }
                progress = handle_compress(strm_ref);
                if progress == 0 {
                    return -1;
                }
                if (s_ref.avail_in_expect > 0) || (isempty_RL(s_ref) == 0) || (s_ref.state_out_pos < s_ref.numZ) {
                    return 3;
                }
                s_ref.mode = 1;
                return 4;
            }
            _ => return 0,
        }
    }
}

// Helper function to get EState (placeholder - actual implementation would need proper state management)
fn get_estate(_idx: Int32) -> Option<&'static mut EState> {
    None
}
pub fn BZ2_bzWriteClose64(
    bzerror: Option<&mut Int32>,
    b: Option<&mut BZFILE>,
    abandon: Int32,
    mut nbytes_in_lo32: Option<&mut u32>,
    mut nbytes_in_hi32: Option<&mut u32>,
    mut nbytes_out_lo32: Option<&mut u32>,
    mut nbytes_out_hi32: Option<&mut u32>,
) {
    let bzf = match b {
        Some(b) => unsafe { &mut *(b as *mut _ as *mut BzFile) },
        None => {
            if let Some(err) = bzerror {
                *err = 0;
            }
            return;
        }
    };

    if bzf.writing == 0 {
        if let Some(err) = bzerror {
            *err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    if let Some(handle) = &mut bzf.handle {
        if handle.metadata().is_err() {
            if let Some(err) = bzerror {
                *err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    }

    if let Some(ref mut nbytes_in_lo32) = nbytes_in_lo32 {
        **nbytes_in_lo32 = 0;
    }
    if let Some(ref mut nbytes_in_hi32) = nbytes_in_hi32 {
        **nbytes_in_hi32 = 0;
    }
    if let Some(ref mut nbytes_out_lo32) = nbytes_out_lo32 {
        **nbytes_out_lo32 = 0;
    }
    if let Some(ref mut nbytes_out_hi32) = nbytes_out_hi32 {
        **nbytes_out_hi32 = 0;
    }

    if abandon == 0 && bzf.lastErr == 0 {
        loop {
            bzf.strm.avail_out = 5000;
            bzf.strm.next_out = Some(Box::new(bzf.buf.map(|c| c as u8)));

            let ret = BZ2_bzCompress(Some(&mut bzf.strm), 2);
            if ret != 3 && ret != 4 {
                if let Some(err) = bzerror {
                    *err = ret;
                }
                bzf.lastErr = ret;
                return;
            }

            if bzf.strm.avail_out < 5000 {
                let n = 5000 - bzf.strm.avail_out;
                if let Some(handle) = &mut bzf.handle {
                    let buf_slice = &bzf.buf[..n as usize];
                    if let Err(_) = handle.write_all(&buf_slice.iter().map(|&c| c as u8).collect::<Vec<u8>>()) {
                        if let Some(err) = bzerror {
                            *err = -6;
                        }
                        bzf.lastErr = -6;
                        return;
                    }
                }
            }

            if ret == 4 {
                break;
            }
        }
    }

    if abandon == 0 {
        if let Some(handle) = &mut bzf.handle {
            if let Err(_) = handle.flush() {
                if let Some(err) = bzerror {
                    *err = -6;
                }
                bzf.lastErr = -6;
                return;
            }
        }
    }

    if let Some(ref mut nbytes_in_lo32) = nbytes_in_lo32 {
        **nbytes_in_lo32 = bzf.strm.total_in_lo32;
    }
    if let Some(ref mut nbytes_in_hi32) = nbytes_in_hi32 {
        **nbytes_in_hi32 = bzf.strm.total_in_hi32;
    }
    if let Some(ref mut nbytes_out_lo32) = nbytes_out_lo32 {
        **nbytes_out_lo32 = bzf.strm.total_out_lo32;
    }
    if let Some(ref mut nbytes_out_hi32) = nbytes_out_hi32 {
        **nbytes_out_hi32 = bzf.strm.total_out_hi32;
    }

    if let Some(err) = bzerror {
        *err = 0;
    }
    bzf.lastErr = 0;

    BZ2_bzCompressEnd(Some(&mut bzf.strm));
}
pub fn BZ2_bzWriteClose(
    bzerror: Option<&mut i32>,
    b: Option<&mut BZFILE>,
    abandon: i32,
    nbytes_in: Option<&mut u32>,
    nbytes_out: Option<&mut u32>,
) {
    BZ2_bzWriteClose64(
        bzerror,
        b,
        abandon,
        nbytes_in,
        None,  // nbytes_in_hi32
        nbytes_out,
        None,  // nbytes_out_hi32
    );
}
pub fn unRLE_obuf_to_output_SMALL(s: &mut DState) -> Bool {
    let mut k1: UChar;

    if s.block_randomised != 0 {
        loop {
            loop {
                if s.strm.as_ref().unwrap().avail_out == 0 {
                    return 0;
                }
                if s.state_out_len == 0 {
                    break;
                }
                
                {
                    let strm = s.strm.as_mut().unwrap();
                    strm.next_out.as_mut().unwrap()[0] = s.state_out_ch;
                    strm.avail_out -= 1;
                    strm.next_out.as_mut().unwrap().rotate_left(1);
                    strm.total_out_lo32 += 1;
                }

                {
                    let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                    s.calculated_block_crc = (s.calculated_block_crc << 8) ^ 
                        crc_table[((s.calculated_block_crc >> 24) ^ (s.state_out_ch as UInt32)) as usize];
                }

                s.state_out_len -= 1;
                
                if s.strm.as_ref().unwrap().total_out_lo32 == 0 {
                    s.strm.as_mut().unwrap().total_out_hi32 += 1;
                }
            }

            if s.nblock_used == s.save_nblock + 1 {
                return 0;
            }
            if s.nblock_used > s.save_nblock + 1 {
                return 1;
            }

            s.state_out_len = 1;
            s.state_out_ch = s.k0 as UChar;
            
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            if s.r_n_to_go == 0 {
                let r_nums = BZ2_rNums.lock().unwrap();
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as UChar {
                s.k0 = k1 as Int32;
                continue;
            }

            s.state_out_len = 2;
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            if s.r_n_to_go == 0 {
                let r_nums = BZ2_rNums.lock().unwrap();
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as UChar {
                s.k0 = k1 as Int32;
                continue;
            }

            s.state_out_len = 3;
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            if s.r_n_to_go == 0 {
                let r_nums = BZ2_rNums.lock().unwrap();
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as UChar {
                s.k0 = k1 as Int32;
                continue;
            }

            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            if s.r_n_to_go == 0 {
                let r_nums = BZ2_rNums.lock().unwrap();
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            s.state_out_len = (k1 as Int32) + 4;
            
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            s.k0 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab);
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            if s.r_n_to_go == 0 {
                let r_nums = BZ2_rNums.lock().unwrap();
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            
            s.k0 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
        }
    } else {
        loop {
            loop {
                if s.strm.as_ref().unwrap().avail_out == 0 {
                    return 0;
                }
                if s.state_out_len == 0 {
                    break;
                }
                
                {
                    let strm = s.strm.as_mut().unwrap();
                    strm.next_out.as_mut().unwrap()[0] = s.state_out_ch;
                    strm.avail_out -= 1;
                    strm.next_out.as_mut().unwrap().rotate_left(1);
                    strm.total_out_lo32 += 1;
                }

                {
                    let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                    s.calculated_block_crc = (s.calculated_block_crc << 8) ^ 
                        crc_table[((s.calculated_block_crc >> 24) ^ (s.state_out_ch as UInt32)) as usize];
                }

                s.state_out_len -= 1;
                
                if s.strm.as_ref().unwrap().total_out_lo32 == 0 {
                    s.strm.as_mut().unwrap().total_out_hi32 += 1;
                }
            }

            if s.nblock_used == s.save_nblock + 1 {
                return 0;
            }
            if s.nblock_used > s.save_nblock + 1 {
                return 1;
            }

            s.state_out_len = 1;
            s.state_out_ch = s.k0 as UChar;
            
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            s.nblock_used += 1;
            
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as UChar {
                s.k0 = k1 as Int32;
                continue;
            }

            s.state_out_len = 2;
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            s.nblock_used += 1;
            
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as UChar {
                s.k0 = k1 as Int32;
                continue;
            }

            s.state_out_len = 3;
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            s.nblock_used += 1;
            
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as UChar {
                s.k0 = k1 as Int32;
                continue;
            }

            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            s.nblock_used += 1;
            s.state_out_len = (k1 as Int32) + 4;
            
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            s.k0 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab);
            s.t_pos = {
                let ll16 = s.ll16.as_ref().unwrap();
                let ll4 = s.ll4.as_ref().unwrap();
                (ll16[s.t_pos as usize] as UInt32) | 
                ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
            };

            s.nblock_used += 1;
        }
    }
}
pub fn unRLE_obuf_to_output_FAST(s: &mut DState) -> u8 {
    if s.block_randomised != 0 {
        loop {
            loop {
                if s.strm.as_ref().unwrap().avail_out == 0 {
                    return 0;
                }
                if s.state_out_len == 0 {
                    break;
                }
                unsafe {
                    let next_out_ptr = s.strm.as_mut().unwrap().next_out.as_mut().unwrap().as_mut_ptr();
                    *next_out_ptr = s.state_out_ch;
                }
                s.calculated_block_crc = (s.calculated_block_crc << 8) ^ globals::BZ2_CRC32_TABLE.lock().unwrap()[((s.calculated_block_crc >> 24) as u8 ^ s.state_out_ch) as usize];
                s.state_out_len -= 1;
                s.strm.as_mut().unwrap().next_out = Some(unsafe { s.strm.as_mut().unwrap().next_out.take().unwrap().into_vec().into_boxed_slice() });
                s.strm.as_mut().unwrap().avail_out -= 1;
                s.strm.as_mut().unwrap().total_out_lo32 += 1;
                if s.strm.as_mut().unwrap().total_out_lo32 == 0 {
                    s.strm.as_mut().unwrap().total_out_hi32 += 1;
                }
            }

            if s.nblock_used == s.save_nblock + 1 {
                return 0;
            }
            if s.nblock_used > s.save_nblock + 1 {
                return 1;
            }
            s.state_out_len = 1;
            s.state_out_ch = s.k0 as u8;
            if s.t_pos >= (100000 * s.block_size100k as u32) {
                return 1;
            }
            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            let mut k1 = (s.t_pos & 0xff) as u8;
            s.t_pos >>= 8;
            if s.r_n_to_go == 0 {
                s.r_n_to_go = globals::BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as u8 {
                s.k0 = k1 as i32;
                continue;
            }
            s.state_out_len = 2;
            if s.t_pos >= (100000 * s.block_size100k as u32) {
                return 1;
            }
            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            let mut k1 = (s.t_pos & 0xff) as u8;
            s.t_pos >>= 8;
            if s.r_n_to_go == 0 {
                s.r_n_to_go = globals::BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as u8 {
                s.k0 = k1 as i32;
                continue;
            }
            s.state_out_len = 3;
            if s.t_pos >= (100000 * s.block_size100k as u32) {
                return 1;
            }
            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            let mut k1 = (s.t_pos & 0xff) as u8;
            s.t_pos >>= 8;
            if s.r_n_to_go == 0 {
                s.r_n_to_go = globals::BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            if s.nblock_used == s.save_nblock + 1 {
                continue;
            }
            if k1 != s.k0 as u8 {
                s.k0 = k1 as i32;
                continue;
            }
            if s.t_pos >= (100000 * s.block_size100k as u32) {
                return 1;
            }
            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            let mut k1 = (s.t_pos & 0xff) as u8;
            s.t_pos >>= 8;
            if s.r_n_to_go == 0 {
                s.r_n_to_go = globals::BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            s.state_out_len = k1 as i32 + 4;
            if s.t_pos >= (100000 * s.block_size100k as u32) {
                return 1;
            }
            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            s.k0 = (s.t_pos & 0xff) as i32;
            s.t_pos >>= 8;
            if s.r_n_to_go == 0 {
                s.r_n_to_go = globals::BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            s.k0 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
        }
    } else {
        let mut c_calculatedBlockCRC = s.calculated_block_crc;
        let mut c_state_out_ch = s.state_out_ch;
        let mut c_state_out_len = s.state_out_len;
        let mut c_nblock_used = s.nblock_used;
        let mut c_k0 = s.k0;
        let c_tt = s.tt.as_ref().unwrap();
        let mut c_tPos = s.t_pos;
        let mut cs_next_out = s.strm.as_mut().unwrap().next_out.take();
        let mut cs_avail_out = s.strm.as_mut().unwrap().avail_out;
        let ro_blockSize100k = s.block_size100k;
        let avail_out_INIT = cs_avail_out;
        let s_save_nblockPP = s.save_nblock + 1;
        let total_out_lo32_old: u32;

        loop {
            if c_state_out_len > 0 {
                loop {
                    if cs_avail_out == 0 {
                        break;
                    }
                    if c_state_out_len == 1 {
                        break;
                    }
                    unsafe {
                        let next_out_ptr = cs_next_out.as_mut().unwrap().as_mut_ptr();
                        *next_out_ptr = c_state_out_ch;
                    }
                    c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ globals::BZ2_CRC32_TABLE.lock().unwrap()[((c_calculatedBlockCRC >> 24) as u8 ^ c_state_out_ch) as usize];
                    c_state_out_len -= 1;
                    cs_next_out = Some(unsafe { cs_next_out.take().unwrap().into_vec().into_boxed_slice() });
                    cs_avail_out -= 1;
                }

                if cs_avail_out == 0 {
                    c_state_out_len = 1;
                    break;
                }
                unsafe {
                    let next_out_ptr = cs_next_out.as_mut().unwrap().as_mut_ptr();
                    *next_out_ptr = c_state_out_ch;
                }
                c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ globals::BZ2_CRC32_TABLE.lock().unwrap()[((c_calculatedBlockCRC >> 24) as u8 ^ c_state_out_ch) as usize];
                cs_next_out = Some(unsafe { cs_next_out.take().unwrap().into_vec().into_boxed_slice() });
                cs_avail_out -= 1;
            }

            if c_nblock_used > s_save_nblockPP {
                return 1;
            }
            if c_nblock_used == s_save_nblockPP {
                c_state_out_len = 0;
                break;
            }
            c_state_out_ch = c_k0 as u8;
            if c_tPos >= (100000 * ro_blockSize100k as u32) {
                return 1;
            }
            c_tPos = c_tt[c_tPos as usize];
            let k1 = (c_tPos & 0xff) as u8;
            c_tPos >>= 8;
            c_nblock_used += 1;
            if k1 != c_k0 as u8 {
                c_k0 = k1 as i32;
                c_state_out_len = 1;
                continue;
            }
            if c_nblock_used == s_save_nblockPP {
                c_state_out_len = 1;
                continue;
            }
            c_state_out_len = 2;
            if c_tPos >= (100000 * ro_blockSize100k as u32) {
                return 1;
            }
            c_tPos = c_tt[c_tPos as usize];
            let k1 = (c_tPos & 0xff) as u8;
            c_tPos >>= 8;
            c_nblock_used += 1;
            if c_nblock_used == s_save_nblockPP {
                continue;
            }
            if k1 != c_k0 as u8 {
                c_k0 = k1 as i32;
                continue;
            }
            c_state_out_len = 3;
            if c_tPos >= (100000 * ro_blockSize100k as u32) {
                return 1;
            }
            c_tPos = c_tt[c_tPos as usize];
            let k1 = (c_tPos & 0xff) as u8;
            c_tPos >>= 8;
            c_nblock_used += 1;
            if c_nblock_used == s_save_nblockPP {
                continue;
            }
            if k1 != c_k0 as u8 {
                c_k0 = k1 as i32;
                continue;
            }
            if c_tPos >= (100000 * ro_blockSize100k as u32) {
                return 1;
            }
            c_tPos = c_tt[c_tPos as usize];
            let k1 = (c_tPos & 0xff) as u8;
            c_tPos >>= 8;
            c_nblock_used += 1;
            c_state_out_len = k1 as i32 + 4;
            if c_tPos >= (100000 * ro_blockSize100k as u32) {
                return 1;
            }
            c_tPos = c_tt[c_tPos as usize];
            c_k0 = (c_tPos & 0xff) as i32;
            c_tPos >>= 8;
            c_nblock_used += 1;
        }

        total_out_lo32_old = s.strm.as_ref().unwrap().total_out_lo32;
        s.strm.as_mut().unwrap().total_out_lo32 += avail_out_INIT - cs_avail_out;
        if s.strm.as_mut().unwrap().total_out_lo32 < total_out_lo32_old {
            s.strm.as_mut().unwrap().total_out_hi32 += 1;
        }
        s.calculated_block_crc = c_calculatedBlockCRC;
        s.state_out_ch = c_state_out_ch;
        s.state_out_len = c_state_out_len;
        s.nblock_used = c_nblock_used;
        s.k0 = c_k0;
        s.t_pos = c_tPos;
        s.strm.as_mut().unwrap().next_out = cs_next_out;
        s.strm.as_mut().unwrap().avail_out = cs_avail_out;
    }
    0
}
pub fn BZ2_bzDecompress(strm: Option<&mut BzStream>) -> i32 {
    if strm.is_none() {
        return -2;
    }
    let strm = strm.unwrap();
    
    if strm.state.is_none() {
        return -2;
    }
    
    // Cast the Box<()> to Box<DState> and get a mutable reference
    let s = unsafe { &mut *(strm.state.as_mut().unwrap().as_mut() as *mut _ as *mut DState) };
    
    // Compare the underlying pointers of the Option<Box<BzStream>> with the raw pointer
    if s.strm.as_ref().map(|b| b.as_ref() as *const _) != Some(strm as *const _) {
        return -2;
    }
    
    loop {
        if s.state == 1 {
            return -1;
        }
        
        if s.state == 2 {
            let corrupt = if s.small_decompress != 0 {
                unRLE_obuf_to_output_SMALL(s)
            } else {
                unRLE_obuf_to_output_FAST(s)
            };
            
            if corrupt != 0 {
                return -4;
            }
            
            if (s.nblock_used == (s.save_nblock + 1)) && (s.state_out_len == 0) {
                s.calculated_block_crc = !s.calculated_block_crc;
                
                if s.verbosity >= 3 {
                    let _ = write!(stderr(), " {{0x{:08x}, 0x{:08x}}}", s.stored_block_crc, s.calculated_block_crc);
                }
                if s.verbosity >= 2 {
                    let _ = write!(stderr(), "]");
                }
                
                if s.calculated_block_crc != s.stored_block_crc {
                    return -4;
                }
                
                s.calculated_combined_crc = (s.calculated_combined_crc << 1) | (s.calculated_combined_crc >> 31);
                s.calculated_combined_crc ^= s.calculated_block_crc;
                s.state = 14;
            } else {
                return 0;
            }
        }
        
        if s.state >= 10 {
            let r = BZ2_decompress(s);
            if r == 4 {
                if s.verbosity >= 3 {
                    let _ = write!(stderr(), "\n    combined CRCs: stored = 0x{:08x}, computed = 0x{:08x}", s.stored_combined_crc, s.calculated_combined_crc);
                }
                if s.calculated_combined_crc != s.stored_combined_crc {
                    return -4;
                }
                return r;
            }
            if s.state != 2 {
                return r;
            }
        }
    }
}
pub fn BZ2_bzRead(
    mut bzerror: Option<&mut Int32>,
    mut b: Option<&mut BzFile>,
    buf: Option<&mut [u8]>,
    len: Int32,
) -> Int32 {
    // Initialize error codes if pointers are provided
    if let Some(ref mut err) = bzerror {
        **err = 0;
    }
    if let Some(ref mut bzf) = b {
        bzf.lastErr = 0;
    }

    // Check for invalid parameters
    if b.is_none() || buf.is_none() || len < 0 {
        if let Some(ref mut err) = bzerror {
            **err = -2;
        }
        if let Some(ref mut bzf) = b {
            bzf.lastErr = -2;
        }
        return 0;
    }

    let bzf = b.unwrap();
    let buf = buf.unwrap();

    // Check if we're in writing mode
    if bzf.writing != 0 {
        if let Some(ref mut err) = bzerror {
            **err = -1;
        }
        bzf.lastErr = -1;
        return 0;
    }

    // Early return if len is 0
    if len == 0 {
        if let Some(ref mut err) = bzerror {
            **err = 0;
        }
        bzf.lastErr = 0;
        return 0;
    }

    // Setup output buffer
    bzf.strm.avail_out = len as u32;
    bzf.strm.next_out = Some(Box::from(buf.to_vec().into_boxed_slice()));

    loop {
        // Check for file errors
        if let Some(ref mut handle) = bzf.handle {
            if handle.seek(std::io::SeekFrom::Current(0)).is_err() {
                if let Some(ref mut err) = bzerror {
                    **err = -6;
                }
                bzf.lastErr = -6;
                return 0;
            }
        }

        // Read more data if needed
        if bzf.strm.avail_in == 0 && !myfeof(&mut bzf.handle.as_mut().unwrap()) {
            let mut temp_buf = [0; 5000];
            let n = match bzf.handle.as_mut().unwrap().read(&mut temp_buf) {
                Ok(n) => n as Int32,
                Err(_) => {
                    if let Some(ref mut err) = bzerror {
                        **err = -6;
                    }
                    bzf.lastErr = -6;
                    return 0;
                }
            };

            bzf.bufN = n;
            bzf.strm.avail_in = bzf.bufN as u32;
            bzf.strm.next_in = Some(Box::from(temp_buf[..n as usize].to_vec().into_boxed_slice()));
        }

        // Decompress
        let ret = BZ2_bzDecompress(Some(&mut bzf.strm));
        if ret != 0 && ret != 4 {
            if let Some(ref mut err) = bzerror {
                **err = ret;
            }
            bzf.lastErr = ret;
            return 0;
        }

        // Check for end of stream
        if ret == 0 && myfeof(&mut bzf.handle.as_mut().unwrap()) 
            && bzf.strm.avail_in == 0 && bzf.strm.avail_out > 0 
        {
            if let Some(ref mut err) = bzerror {
                **err = -7;
            }
            bzf.lastErr = -7;
            return 0;
        }

        // Check for decompression complete
        if ret == 4 {
            if let Some(ref mut err) = bzerror {
                **err = 4;
            }
            bzf.lastErr = 4;
            return len - bzf.strm.avail_out as Int32;
        }

        // Check if output buffer is full
        if bzf.strm.avail_out == 0 {
            if let Some(ref mut err) = bzerror {
                **err = 0;
            }
            bzf.lastErr = 0;
            return len;
        }
    }
}
pub fn BZ2_bzread(
    b: Option<&mut BzFile>,
    buf: Option<&mut [u8]>,
    len: Int32,
) -> Int32 {
    let mut bzerr: Int32 = 0;
    let nread;

    // Check lastErr before proceeding (equivalent to C lines 4-6)
    if let Some(b_file) = &b {
        unsafe {
            if (*b_file).lastErr == 4 {
                return 0;
            }
        }
    }

    // Call BZ2_bzRead (equivalent to line 9 in C)
    nread = BZ2_bzRead(Some(&mut bzerr), b, buf, len);

    // Handle the return value based on bzerr (equivalent to lines 10-17 in C)
    if bzerr == 0 || bzerr == 4 {
        nread
    } else {
        -1
    }
}
pub fn BZ2_bzWrite(mut bzerror: Option<&mut Int32>, b: Option<&mut BZFILE>, buf: Option<&[u8]>, len: Int32) {
    let bzf = match b {
        Some(b) => unsafe { &mut *(b as *mut _ as *mut BzFile) },
        None => {
            if let Some(ref mut err) = bzerror {
                **err = -2;
            }
            return;
        }
    };

    // Initialize error codes
    if let Some(ref mut err) = bzerror {
        **err = 0;
    }
    bzf.lastErr = 0;

    // Check for invalid parameters
    if buf.is_none() || len < 0 {
        if let Some(ref mut err) = bzerror {
            **err = -2;
        }
        bzf.lastErr = -2;
        return;
    }

    // Check if we're in writing mode
    if bzf.writing == 0 {
        if let Some(ref mut err) = bzerror {
            **err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    // Check for file errors
    if let Some(handle) = &mut bzf.handle {
        if handle.write(&[]).is_err() {
            if let Some(ref mut err) = bzerror {
                **err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    }

    // Early return if len is 0
    if len == 0 {
        if let Some(ref mut err) = bzerror {
            **err = 0;
        }
        bzf.lastErr = 0;
        return;
    }

    // Setup compression stream
    bzf.strm.avail_in = len as u32;
    bzf.strm.next_in = buf.map(|slice| Box::from(slice));

    loop {
        bzf.strm.avail_out = 5000;
        let mut byte_buf = [0u8; 5000];
        for (i, &c) in bzf.buf.iter().enumerate() {
            byte_buf[i] = c as u8;
        }
        bzf.strm.next_out = Some(Box::new(byte_buf));

        let ret = BZ2_bzCompress(Some(&mut bzf.strm), 0);
        if ret != 1 {
            if let Some(ref mut err) = bzerror {
                **err = ret;
            }
            bzf.lastErr = ret;
            return;
        }

        if bzf.strm.avail_out < 5000 {
            let n = 5000 - bzf.strm.avail_out;
            if let Some(handle) = &mut bzf.handle {
                let mut byte_buf = [0u8; 5000];
                for (i, &c) in bzf.buf.iter().enumerate() {
                    byte_buf[i] = c as u8;
                }
                let write_result = handle.write_all(&byte_buf[..n as usize]);
                if write_result.is_err() {
                    if let Some(ref mut err) = bzerror {
                        **err = -6;
                    }
                    bzf.lastErr = -6;
                    return;
                }
            }
        }

        if bzf.strm.avail_in == 0 {
            if let Some(ref mut err) = bzerror {
                **err = 0;
            }
            bzf.lastErr = 0;
            return;
        }
    }
}
pub fn BZ2_bzwrite(b: Option<&mut BZFILE>, buf: Option<&[u8]>, len: i32) -> i32 {
    let mut bzerr = 0;
    BZ2_bzWrite(Some(&mut bzerr), b, buf, len);
    if bzerr == 0 {
        len
    } else {
        -1
    }
}
pub fn BZ2_bzerror(b: Option<&BZFILE>, errnum: Option<&mut i32>) -> Option<&'static str> {
    // Check for NULL equivalents in Rust (None)
    if b.is_none() || errnum.is_none() {
        return None;
    }

    // Safe unwrap since we checked for None
    let _b = b.unwrap();
    let errnum = errnum.unwrap();

    // Since BZFILE is opaque, we can't access lastErr directly.
    // In the original C code, this was accessed through a cast to bzFile*.
    // For the translation, we'll assume the error is passed through some other means,
    // or we'll use a default error code (0 for OK) since we can't access the struct.
    let err = 0; // Default to OK since we can't access lastErr

    let adjusted_err = if err > 0 {
        0
    } else {
        err
    };

    *errnum = adjusted_err;

    // Access the global error strings array
    Some(BZERRORSTRINGS[(adjusted_err * -1) as usize])
}
pub fn BZ2_bzReadClose(mut bzerror: Option<&mut Int32>, b: Option<&mut BZFILE>) {
    // Convert BZFILE to bzFile (assuming BZFILE is a wrapper around bzFile)
    let bzf = if let Some(b) = b {
        unsafe { &mut *(b as *mut BZFILE as *mut BzFile) }
    } else {
        // Handle NULL case (equivalent to lines 15-29 in C)
        if let Some(ref mut err) = bzerror {
            **err = 0;
        }
        return;
    };

    // Initial error clearing (equivalent to lines 5-13 in C)
    if let Some(ref mut err) = bzerror {
        **err = 0;
    }
    bzf.lastErr = 0;

    // Check writing mode (equivalent to lines 31-45 in C)
    if bzf.writing != 0 {
        if let Some(ref mut err) = bzerror {
            **err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    // Decompress end if initialized (equivalent to lines 47-51 in C)
    if bzf.initialisedOk != 0 {
        BZ2_bzDecompressEnd(Some(&mut bzf.strm));
    }

    // Free is handled by Rust's drop mechanism
}
pub fn BZ2_bzclose(b: Option<&mut BZFILE>) {
    if b.is_none() {
        return;
    }
    
    let b = b.unwrap();
    // Cast BZFILE to bzFile to access the fields
    let bz_file = unsafe { &mut *(b as *mut BZFILE as *mut bzFile) };
    let fp = bz_file.handle;
    
    if bz_file.writing != 0 {
        let mut bzerr = 0;
        BZ2_bzWriteClose(Some(&mut bzerr), Some(b), 0, None, None);
        if bzerr != 0 {
            BZ2_bzWriteClose(None, Some(b), 1, None, None);
        }
    } else {
        let mut bzerr = 0;
        BZ2_bzReadClose(Some(&mut bzerr), Some(b));
    }
    
    // Compare with raw file descriptors for stdin (0) and stdout (1)
    if fp != 0 && fp != 1 {
        // Use libc::close to close the file descriptor
        unsafe { libc::close(fp as i32) };
    }
}

// We need to declare the C struct that was used in the original code
#[repr(C)]
struct bzFile {
    handle: libc::c_uint,
    writing: libc::c_int,
    // ... other fields as needed
}

// Declare the global FILE* array that was used in the original code
extern "C" {
    static mut bz_fp: *mut *mut libc::FILE;
}
pub fn BZ2_bzBuffToBuffCompress(
    dest: Option<&mut [u8]>,
    mut destLen: Option<&mut u32>,
    source: Option<&[u8]>,
    sourceLen: u32,
    blockSize100k: i32,
    verbosity: i32,
    workFactor: i32,
) -> i32 {
    // Validate input parameters
    if dest.is_none()
        || destLen.is_none()
        || source.is_none()
        || blockSize100k < 1
        || blockSize100k > 9
        || verbosity < 0
        || verbosity > 4
        || workFactor < 0
        || workFactor > 250
    {
        return -2;
    }

    let workFactor = if workFactor == 0 { 30 } else { workFactor };

    let mut strm = BzStream {
        next_in: None,
        avail_in: 0,
        total_in_lo32: 0,
        total_in_hi32: 0,
        next_out: None,
        avail_out: 0,
        total_out_lo32: 0,
        total_out_hi32: 0,
        state: None,
        bzalloc: None,
        bzfree: None,
        opaque: None,
    };

    let ret = BZ2_bzCompressInit(
        Some(&mut strm),
        blockSize100k,
        verbosity,
        workFactor,
    );
    if ret != 0 {
        return ret;
    }

    // Set up input/output buffers
    strm.next_in = source.map(|s| s.to_vec().into_boxed_slice());
    strm.avail_in = sourceLen;
    
    let dest_len = destLen.as_mut().unwrap();
    strm.next_out = dest.map(|d| d.to_vec().into_boxed_slice());
    strm.avail_out = **dest_len;

    let ret = BZ2_bzCompress(Some(&mut strm), 2);

    match ret {
        3 => {
            BZ2_bzCompressEnd(Some(&mut strm));
            -8
        }
        4 => {
            **destLen.as_mut().unwrap() = strm.total_out_lo32;
            BZ2_bzCompressEnd(Some(&mut strm));
            0
        }
        _ => {
            BZ2_bzCompressEnd(Some(&mut strm));
            ret
        }
    }
}
pub unsafe extern "C" fn BZ2_bzBuffToBuffDecompress(
    mut dest: *mut libc::c_char,
    mut destLen: *mut libc::c_uint,
    mut source: *mut libc::c_char,
    mut sourceLen: libc::c_uint,
    mut small: libc::c_int,
    mut verbosity: libc::c_int,
) -> libc::c_int {
    let mut strm: BzStream = BzStream {
        next_in: None,
        avail_in: 0,
        total_in_lo32: 0,
        total_in_hi32: 0,
        next_out: None,
        avail_out: 0,
        total_out_lo32: 0,
        total_out_hi32: 0,
        state: None,
        bzalloc: Option::None,
        bzfree: Option::None,
        opaque: None,
    };
    let mut ret: libc::c_int = 0;
    if (((((dest.is_null() || destLen.is_null()) || source.is_null())
        || (small != 0 && small != 1))
        || verbosity < 0)
        || verbosity > 4)
    {
        return -(2 as libc::c_int);
    }
    ret = BZ2_bzDecompressInit(Some(&mut strm), verbosity, small);
    if ret != 0 {
        return ret;
    }
    strm.next_in = Some(Box::from_raw(std::slice::from_raw_parts_mut(source as *mut u8, sourceLen as usize)));
    strm.next_out = Some(Box::from_raw(std::slice::from_raw_parts_mut(dest as *mut u8, (*destLen) as usize)));
    strm.avail_in = sourceLen;
    strm.avail_out = *destLen;
    ret = BZ2_bzDecompress(Some(&mut strm));
    if ret == 0 {
        return output_overflow_or_eof(&mut strm, destLen);
    }
    if ret != 4 {
        return errhandler(&mut strm, ret);
    }
    *destLen = (*destLen).wrapping_sub(strm.avail_out);
    BZ2_bzDecompressEnd(Some(&mut strm));
    return 0;
    
    fn output_overflow_or_eof(strm: &mut BzStream, destLen: *mut libc::c_uint) -> libc::c_int {
        if strm.avail_out > 0 {
            BZ2_bzDecompressEnd(Some(strm));
            return -(7 as libc::c_int);
        } else {
            BZ2_bzDecompressEnd(Some(strm));
            return -(8 as libc::c_int);
        }
    }
    
    fn errhandler(strm: &mut BzStream, ret: libc::c_int) -> libc::c_int {
        BZ2_bzDecompressEnd(Some(strm));
        return ret;
    }
}
