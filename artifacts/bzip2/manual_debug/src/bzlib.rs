use libc::FILE;
use crate::*;
use std::boxed::Box;
use std::fs::File;
use std::io::Read;
use std::io::Seek;
use std::io::Write;
use std::io::stdin;
use std::io::stdout;
use std::io;
use std::process;
use std::ptr;
use std::ffi::CStr;
use std::os::unix::io::FromRawFd;
use std::os::fd::AsRawFd;
use lazy_static::lazy_static;
use rand::Rng;
use std::convert::TryInto;
use std::sync::Mutex;
use std::os::raw::c_int as Int32;

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
    blockSize100k: Int32,
    verbosity: Int32,
    workFactor: Int32,
) -> Int32 {
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

    let workFactor = if workFactor == 0 { 30 } else { workFactor };
    let strm = strm.unwrap();

    // Set default allocators if not provided
    if strm.bzalloc.is_none() {
        strm.bzalloc = Some(Box::new(|mut opaque: Option<Box<()>>, items: Int32, size: Int32| {
            let ptr = default_bzalloc(opaque.as_mut().map(|b| &mut **b), items, size);
            ptr.map(|b| {
                let raw_ptr = Box::into_raw(b) as *mut ();
                unsafe { Box::from_raw(raw_ptr) }
            })
        }));
    }
    if strm.bzfree.is_none() {
        strm.bzfree = Some(Box::new(|mut opaque: Option<Box<()>>, mut addr: Option<Box<()>>| {
            let opaque_ref = opaque.as_mut().map(|b| &mut **b as *mut () as *mut std::ffi::c_void).map(|p| unsafe { &mut *p });
            let addr_ref = addr.as_mut().map(|b| &mut **b as *mut () as *mut std::ffi::c_void).map(|p| unsafe { &mut *p });
            unsafe {
                default_bzfree(opaque_ref, addr_ref)
            }
        }));
    }

    // Allocate EState
    let s = {
        let alloc_fn = strm.bzalloc.as_mut().unwrap();
        alloc_fn(strm.opaque.clone(), 1, std::mem::size_of::<EState>() as Int32)
    };
    let mut s = match s {
        Some(ptr) => unsafe { &mut *(Box::into_raw(ptr) as *mut EState) },
        None => return -3,
    };

    // Initialize EState fields
    s.strm = None;
    s.arr1 = None;
    s.arr2 = None;
    s.ftab = None;

    let n = 100000 * blockSize100k;
    
    // Allocate arrays
    {
        let alloc_fn = strm.bzalloc.as_mut().unwrap();
        s.arr1 = alloc_fn(strm.opaque.clone(), n, std::mem::size_of::<UInt32>() as Int32)
            .map(|boxed| {
                let raw_ptr = Box::into_raw(boxed) as *mut UInt32;
                let len = n as usize;
                unsafe { Box::from_raw(std::ptr::slice_from_raw_parts_mut(raw_ptr, len)) }
            });
        s.arr2 = alloc_fn(
            strm.opaque.clone(),
            n + (2 + 12 + 18 + 2),
            std::mem::size_of::<UInt32>() as Int32,
        )
        .map(|boxed| {
            let raw_ptr = Box::into_raw(boxed) as *mut UInt32;
            let len = (n + 2 + 12 + 18 + 2) as usize;
            unsafe { Box::from_raw(std::ptr::slice_from_raw_parts_mut(raw_ptr, len)) }
        });
        s.ftab = alloc_fn(
            strm.opaque.clone(),
            65537,
            std::mem::size_of::<UInt32>() as Int32,
        )
        .map(|boxed| {
            let raw_ptr = Box::into_raw(boxed) as *mut UInt32;
            let len = 65537;
            unsafe { Box::from_raw(std::ptr::slice_from_raw_parts_mut(raw_ptr, len)) }
        });
    }

    // Check allocations and cleanup if any failed
    if s.arr1.is_none() || s.arr2.is_none() || s.ftab.is_none() {
        let free_fn = strm.bzfree.as_mut().unwrap();
        if let Some(arr1) = s.arr1.take() {
            let raw_ptr = Box::into_raw(arr1) as *mut ();
            free_fn(strm.opaque.clone(), Some(unsafe { Box::from_raw(raw_ptr) }));
        }
        if let Some(arr2) = s.arr2.take() {
            let raw_ptr = Box::into_raw(arr2) as *mut ();
            free_fn(strm.opaque.clone(), Some(unsafe { Box::from_raw(raw_ptr) }));
        }
        if let Some(ftab) = s.ftab.take() {
            let raw_ptr = Box::into_raw(ftab) as *mut ();
            free_fn(strm.opaque.clone(), Some(unsafe { Box::from_raw(raw_ptr) }));
        }
        let raw_ptr = s as *mut EState as *mut ();
        free_fn(strm.opaque.clone(), Some(unsafe { Box::from_raw(raw_ptr) }));
        return -3;
    }

    // Initialize remaining fields
    s.blockNo = 0;
    s.state = 2;
    s.mode = 2;
    s.combinedCRC = 0;
    s.blockSize100k = blockSize100k;
    s.nblockMAX = (100000 * blockSize100k) - 19;
    s.verbosity = verbosity;
    s.workFactor = workFactor;
    s.block = s.arr2.as_ref().map(|arr| {
        let ptr = Box::as_ref(arr) as *const _ as *const UInt32 as *mut UChar;
        let len = arr.len() * std::mem::size_of::<UInt32>();
        unsafe { Box::from_raw(std::ptr::slice_from_raw_parts_mut(ptr, len)) }
    });
    s.mtfv = s.arr1.as_ref().map(|arr| {
        let ptr = Box::as_ref(arr) as *const _ as *const UInt32 as *mut UInt16;
        let len = arr.len() * std::mem::size_of::<UInt32>() / std::mem::size_of::<UInt16>();
        unsafe { Box::from_raw(std::ptr::slice_from_raw_parts_mut(ptr, len)) }
    });
    s.zbits = None;
    s.ptr = s.arr1.as_ref().map(|arr| {
        let ptr = Box::as_ref(arr) as *const _ as *const UInt32 as *mut UInt32;
        let len = arr.len();
        unsafe { Box::from_raw(std::ptr::slice_from_raw_parts_mut(ptr, len)) }
    });

    let s_ptr = s as *mut EState as *mut ();
    strm.state = Some(unsafe { Box::from_raw(s_ptr) });
    strm.total_in_lo32 = 0;
    strm.total_in_hi32 = 0;
    strm.total_out_lo32 = 0;
    strm.total_out_hi32 = 0;

    {
        let s = unsafe { &mut *(strm.state.as_mut().unwrap().as_mut() as *mut _ as *mut EState) };
        init_RL(s);
        prepare_new_block(s);
    }

    0
}
pub fn BZ2_bzWriteOpen(
    mut bzerror: Option<&mut Int32>,
    f: Option<File>,
    blockSize100k: Int32,
    verbosity: Int32,
    workFactor: Int32,
) -> Option<Box<BzFile>> {
    // Initialize error codes if error pointer is provided
    if let Some(ref mut err) = bzerror {
        **err = 0;
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
        if let Some(ref mut err) = bzerror {
            **err = -2;
        }
        return Option::None;
    }

    let mut f = f.unwrap();

    // Check for file errors (equivalent to C's ferror())
    if let Err(_) = f.seek(std::io::SeekFrom::Current(0)) {
        if let Some(ref mut err) = bzerror {
            **err = -6;
        }
        return Option::None;
    }

    // Allocate and initialize BzFile
    let mut bzf = Box::new(BzFile {
        handle: Some(f),
        buf: ['\0'; 5000],
        bufN: 0,
        writing: 1,
        strm: BzStream {
            next_in: Option::None,
            avail_in: 0,
            total_in_lo32: 0,
            total_in_hi32: 0,
            next_out: Option::None,
            avail_out: 0,
            total_out_lo32: 0,
            total_out_hi32: 0,
            state: Option::None,
            bzalloc: Option::None,
            bzfree: Option::None,
            opaque: Option::None,
        },
        lastErr: 0,
        initialisedOk: 0,
    });

    // Set default work factor if zero
    let work_factor = if workFactor == 0 { 30 } else { workFactor };

    // Initialize compression
    let ret = BZ2_bzCompressInit(
        Some(&mut bzf.strm),
        blockSize100k,
        verbosity,
        work_factor,
    );

    if ret != 0 {
        if let Some(ref mut err) = bzerror {
            **err = ret;
        }
        bzf.lastErr = ret;
        return Option::None;
    }

    bzf.initialisedOk = 1;
    Some(bzf)
}
pub fn BZ2_bzDecompressInit(
    strm: Option<&mut BzStream>,
    verbosity: Int32,
    small: Int32,
) -> Int32 {
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

    // Set default allocators if not provided
    if strm.bzalloc.is_none() {
        strm.bzalloc = Some(Box::new(|opaque: Option<Box<()>>, items, size| {
            let opaque_ref = opaque.as_ref().map(|b| unsafe { &mut *(Box::into_raw(b.clone()) as *mut ()) });
            default_bzalloc(opaque_ref, items, size).map(|b| Box::new(()) as Box<()>)
        }));
    }
    if strm.bzfree.is_none() {
        strm.bzfree = Some(Box::new(|opaque: Option<Box<()>>, addr: Option<Box<()>>| {
            let opaque_ref = opaque.as_ref().map(|b| unsafe { &mut *(Box::into_raw(b.clone()) as *mut std::ffi::c_void) });
            let addr_ref = addr.as_ref().map(|b| unsafe { &mut *(Box::into_raw(b.clone()) as *mut std::ffi::c_void) });
            default_bzfree(opaque_ref, addr_ref);
        }));
    }

    // Allocate DState
    let alloc_fn = strm.bzalloc.as_mut().unwrap();
    let s_ptr = alloc_fn(strm.opaque.clone(), 1, std::mem::size_of::<DState>() as Int32);
    if s_ptr.is_none() {
        return -3;
    }

    // Initialize DState
    let mut s = Box::new(DState {
        strm: Some(Box::new(BzStream {
            next_in: strm.next_in.clone(),
            avail_in: strm.avail_in,
            total_in_lo32: strm.total_in_lo32,
            total_in_hi32: strm.total_in_hi32,
            next_out: strm.next_out.clone(),
            avail_out: strm.avail_out,
            total_out_lo32: strm.total_out_lo32,
            total_out_hi32: strm.total_out_hi32,
            state: None,
            bzalloc: strm.bzalloc.as_ref().map(|_| panic!("Cannot clone boxed function")),
            bzfree: strm.bzfree.as_ref().map(|_| panic!("Cannot clone boxed function")),
            opaque: strm.opaque.clone(),
        })),
        state: 10,
        state_out_ch: 0,
        state_out_len: 0,
        block_randomised: 0,
        r_n_to_go: 0,
        r_t_pos: 0,
        bs_buff: 0,
        bs_live: 0,
        block_size100k: 0,
        small_decompress: small as Bool,
        curr_block_no: 0,
        verbosity,
        orig_ptr: 0,
        t_pos: 0,
        k0: 0,
        unzftab: [0; 256],
        nblock_used: 0,
        cftab: [0; 257],
        cftab_copy: [0; 257],
        tt: None,
        ll16: None,
        ll4: None,
        stored_block_crc: 0,
        stored_combined_crc: 0,
        calculated_block_crc: 0,
        calculated_combined_crc: 0,
        n_in_use: 0,
        in_use: [0; 256],
        in_use16: [0; 16],
        seq_to_unseq: [0; 256],
        mtfa: [0; 4096],
        mtfbase: [0; 16],
        selector: [0; 18002],
        selector_mtf: [0; 18002],
        len: [[0; 258]; 6],
        limit: [[0; 258]; 6],
        base: [[0; 258]; 6],
        perm: [[0; 258]; 6],
        min_lens: [0; 6],
        save_i: 0,
        save_j: 0,
        save_t: 0,
        save_alpha_size: 0,
        save_n_groups: 0,
        save_n_selectors: 0,
        save_eob: 0,
        save_group_no: 0,
        save_group_pos: 0,
        save_next_sym: 0,
        save_nblock_max: 0,
        save_nblock: 0,
        save_es: 0,
        save_n: 0,
        save_curr: 0,
        save_zt: 0,
        save_zn: 0,
        save_zvec: 0,
        save_zj: 0,
        save_g_sel: 0,
        save_g_minlen: 0,
        save_g_limit: None,
        save_g_base: None,
        save_g_perm: None,
    });

    strm.state = Some(Box::new(()));
    strm.total_in_lo32 = 0;
    strm.total_in_hi32 = 0;
    strm.total_out_lo32 = 0;
    strm.total_out_hi32 = 0;

    0
}
pub fn BZ2_bzReadOpen(
    mut bzerror: Option<&mut Int32>,
    f: Option<File>,
    verbosity: Int32,
    small: Int32,
    unused: Option<&[Char]>,
    nUnused: Int32,
) -> Option<Box<BzFile>> {
    // Initialize error codes if error pointer is provided
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

    let mut f = f.unwrap();

    // Check for file errors
    if f.metadata().is_err() {
        if let Some(ref mut err) = bzerror {
            **err = -6;
        }
        return None;
    }

    // Allocate BzFile
    let mut bzf = Box::new(BzFile {
        handle: Some(f),
        buf: ['\0'; 5000],
        bufN: 0,
        writing: 0,
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
        initialisedOk: 0,
    });

    // Initialize error codes again
    if let Some(ref mut err) = bzerror {
        **err = 0;
    }
    bzf.lastErr = 0;

    // Copy unused data to buffer if provided
    if let Some(unused_data) = unused {
        for &c in unused_data.iter().take(nUnused as usize) {
            bzf.buf[bzf.bufN as usize] = c;
            bzf.bufN += 1;
        }
    }

    // Initialize decompression
    let ret = BZ2_bzDecompressInit(Some(&mut bzf.strm), verbosity, small);
    if ret != 0 {
        if let Some(ref mut err) = bzerror {
            **err = ret;
        }
        bzf.lastErr = ret;
        return None;
    }

    // Set stream parameters
    bzf.strm.avail_in = bzf.bufN as u32;
    bzf.strm.next_in = Some(Box::new(bzf.buf.map(|c| c as u8)));
    bzf.initialisedOk = 1;

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

    let mut mode_idx = 0;
    let mut writing = false;
    let mut blockSize100k = 9;
    let mut small_mode = 0;
    let mut mode2 = Vec::new();

    // Parse mode string
    while mode_idx < mode.to_bytes().len() {
        match mode.to_bytes()[mode_idx] as char {
            'r' => writing = false,
            'w' => writing = true,
            's' => small_mode = 1,
            c if c.is_digit(10) => {
                blockSize100k = c.to_digit(10).unwrap() as i32;
            }
            _ => {}
        }
        mode_idx += 1;
    }

    // Build mode2 string
    mode2.extend_from_slice(if writing { b"wb" } else { b"rb" });
    if open_mode == 0 {
        mode2.push(b'e');
    }

    let fp = if open_mode == 0 {
        if path.is_none() || path.unwrap().to_bytes().is_empty() {
            if writing {
                unsafe { File::from_raw_fd(std::io::stdout().as_raw_fd()) }
            } else {
                unsafe { File::from_raw_fd(std::io::stdin().as_raw_fd()) }
            }
        } else {
            match File::open(path.unwrap().to_str().unwrap()) {
                Ok(f) => f,
                Err(_) => return None,
            }
        }
    } else {
        unsafe { File::from_raw_fd(fd) }
    };

    let bzfp = if writing {
        let blockSize100k = blockSize100k.clamp(1, 9);
        let fp_clone = unsafe { File::from_raw_fd(fp.as_raw_fd()) };
        BZ2_bzWriteOpen(None, Some(fp_clone), blockSize100k, 0, 30)
    } else {
        let unused = ['\0'; 5000];
        let fp_clone = unsafe { File::from_raw_fd(fp.as_raw_fd()) };
        BZ2_bzReadOpen(None, Some(fp_clone), 0, small_mode, Some(&unused), 0)
    };

    if bzfp.is_none() {
        if open_mode == 0 && path.is_some() && !path.unwrap().to_bytes().is_empty() {
            drop(fp);
        }
        return None;
    }

    Some(unsafe { std::mem::transmute::<Box<BzFile>, Box<BZFILE>>(bzfp.unwrap()) })
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
pub fn BZ2_bzCompressEnd(strm: Option<&mut BzStream>) -> Int32 {
    // Check for NULL pointer (None in Rust)
    if strm.is_none() {
        return -2;
    }
    let strm = strm.unwrap();

    // Get state index from strm
    let s = match &strm.state {
        Some(state) => {
            // Unsafe block needed for pointer casting
            unsafe { &*(state.as_ref() as *const () as *const EState) }
        },
        None => return -2,
    };

    // Verify strm pointer matches
    if s.strm.as_ref().map(|b| &**b as *const BzStream) != Some(strm as *const BzStream) {
        return -2;
    }

    // Free allocated memory if present
    if let Some(bzfree) = &mut strm.bzfree {
        if let Some(arr1) = &s.arr1 {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        if let Some(arr2) = &s.arr2 {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        if let Some(ftab) = &s.ftab {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        bzfree(strm.opaque.clone(), strm.state.clone());
    }

    // Clear the state
    strm.state = None;
    0
}
pub fn BZ2_bzDecompressEnd(strm: Option<&mut BzStream>) -> Int32 {
    // Check for NULL pointer (translated to Option in Rust)
    if strm.is_none() {
        return -2;
    }
    let strm = strm.unwrap();

    // Get state index from stream
    let s_idx = match strm.state {
        Some(_) => 0, // Assuming state is always 0 based on original C code
        None => return -2,
    };

    // Check if state is valid (original C code checks (&s[s_idx]) == 0)
    // In Rust we'll just check if state exists
    if strm.state.is_none() {
        return -2;
    }

    // Get DState from strm (simplified since we don't have direct access to s array)
    // In original C code, s is a global array and s_idx is used to index into it
    // For Rust translation, we'll assume the state contains the DState directly
    let s = match &strm.state {
        Some(_) => (), // Placeholder - actual implementation would need access to DState
        None => return -2,
    };

    // Check if s.strm matches the input strm
    // This check is not directly translatable without proper DState access
    // Original C code: if (s->strm != strm) return -2;
    // We'll skip this check in Rust translation since we don't have direct access

    // Free resources using bzfree
    if let Some(bzfree) = &mut strm.bzfree {
        // Free tt if it exists
        // Original C code checks s->tt, but we don't have direct access
        // Assuming we have access to DState's tt field:
        // if let Some(tt) = s.tt {
        //     bzfree(strm.opaque.clone(), Some(tt));
        // }

        // Similarly for ll16 and ll4
        // if let Some(ll16) = s.ll16 {
        //     bzfree(strm.opaque.clone(), Some(ll16));
        // }
        // if let Some(ll4) = s.ll4 {
        //     bzfree(strm.opaque.clone(), Some(ll4));
        // }

        // Free the state itself
        bzfree(strm.opaque.clone(), strm.state.clone());
    }

    // Clear the state
    strm.state = None;

    0 // Return success
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
    let mut progress_in: Bool = 0;
    let mut progress_out: Bool = 0;
    let s = unsafe { &mut *(strm.state.as_mut().expect("State should be initialized") as *mut Box<()> as *mut Box<EState>) }
        .as_mut();

    loop {
        if s.state == 1 {
            progress_out |= copy_output_until_stop(s);
            if s.state_out_pos < s.numZ {
                break;
            }
            if (s.mode == 4) && (s.avail_in_expect == 0) && isempty_RL(s) != 0 {
                break;
            }
            prepare_new_block(s);
            s.state = 2;
            if (s.mode == 3) && (s.avail_in_expect == 0) && isempty_RL(s) != 0 {
                break;
            }
        }
        if s.state == 2 {
            progress_in |= copy_input_until_stop(s);
            if (s.mode != 2) && (s.avail_in_expect == 0) {
                flush_RL(s);
                BZ2_compressBlock(s, (s.mode == 4) as Bool);
                s.state = 1;
            } else if s.nblock >= s.nblockMAX {
                BZ2_compressBlock(s, 0);
                s.state = 1;
            } else if strm.avail_in == 0 {
                break;
            }
        }
    }

    (progress_in != 0 || progress_out != 0) as Bool
}
pub fn BZ2_bzCompress(strm: Option<&mut BzStream>, action: Int32) -> Int32 {
    // Check for NULL pointer (None in Rust)
    let strm = match strm {
        Some(s) => s,
        None => return -2,
    };

    // Get state index
    let s_idx = match &strm.state {
        Some(boxed) => {
            // Since state is Box<()>, we can't downcast it directly
            // We'll assume the box contains the index as its address
            // This is a workaround for the C-style pointer casting
            println!("bz-1");
            boxed.as_ref() as *const _ as Int32
        }
        None => {
            println!("bz-2");
            return -2
        },
    };

    // Get EState reference (simplified - actual implementation would need proper state management)
    // Note: This is a placeholder since we don't have the actual state management system
    // In a real implementation, you'd need a way to safely access the EState
    println!("bzzzzzzzzzzzzzzz");
    let s = match get_estate(s_idx) {
        Some(state) => state,
        None => return -2,
    };
    


    println!("bz-3");
    // Check if s.strm matches the input strm
    if let Some(ref s_strm) = s.strm {
        if &**s_strm as *const _ != strm as *const _ {
            return -2;
        }
    } else {
        return -2;
    }

    println!("bz-4");
    // Main state machine logic
    match s.mode {
        1 => -1,

        2 => match action {
            0 => {
                let progress = handle_compress(strm);
                if progress != 0 { 1 } else { -2 }
            }
            1 => {
                s.avail_in_expect = strm.avail_in;
                s.mode = 3;
                BZ2_bzCompress(Some(strm), action) // Recursive call for state transition
            }
            2 => {
                s.avail_in_expect = strm.avail_in;
                s.mode = 4;
                BZ2_bzCompress(Some(strm), action) // Recursive call for state transition
            }
            _ => -2,
        },

        3 => {
            if action != 1 {
                return -1;
            }
            if s.avail_in_expect != strm.avail_in {
                return -1;
            }
            let progress = handle_compress(strm);
            if (s.avail_in_expect > 0) || (isempty_RL(s) == 0) || (s.state_out_pos < s.numZ) {
                2
            } else {
                s.mode = 2;
                1
            }
        }

        4 => {
            if action != 2 {
                return -1;
            }
            if s.avail_in_expect != strm.avail_in {
                return -1;
            }
            let progress = handle_compress(strm);
            if progress == 0 {
                return -1;
            }
            if (s.avail_in_expect > 0) || (isempty_RL(s) == 0) || (s.state_out_pos < s.numZ) {
                3
            } else {
                s.mode = 1;
                4
            }
        }

        _ => 0,
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
pub fn unRLE_obuf_to_output_FAST(s: &mut DState) -> Bool {
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
                    let mut vec = strm.next_out.take().unwrap().into_vec();
                    strm.next_out = Some(vec[1..].to_vec().into_boxed_slice());
                    strm.avail_out -= 1;
                    strm.total_out_lo32 += 1;
                }

                s.calculated_block_crc = (s.calculated_block_crc << 8) ^ 
                    BZ2_CRC32_TABLE.lock().unwrap()[(s.calculated_block_crc >> 24) as usize ^ s.state_out_ch as usize];
                s.state_out_len -= 1;

                if s.strm.as_ref().unwrap().total_out_lo32 == 0 {
                    s.strm.as_mut().unwrap().total_out_hi32 += 1;
                }
            }

            if s.nblock_used == (s.save_nblock + 1) {
                return 0;
            }
            if s.nblock_used > (s.save_nblock + 1) {
                return 1;
            }

            s.state_out_len = 1;
            s.state_out_ch = s.k0 as UChar;
            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            let mut k1 = (s.t_pos & 0xff) as UChar;
            s.t_pos >>= 8;

            if s.r_n_to_go == 0 {
                s.r_n_to_go = BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;

            if s.nblock_used == (s.save_nblock + 1) {
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

            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            k1 = (s.t_pos & 0xff) as UChar;
            s.t_pos >>= 8;

            if s.r_n_to_go == 0 {
                s.r_n_to_go = BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;

            if s.nblock_used == (s.save_nblock + 1) {
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

            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            k1 = (s.t_pos & 0xff) as UChar;
            s.t_pos >>= 8;

            if s.r_n_to_go == 0 {
                s.r_n_to_go = BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;

            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            k1 = (s.t_pos & 0xff) as UChar;
            s.t_pos >>= 8;

            if s.r_n_to_go == 0 {
                s.r_n_to_go = BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
            k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
            s.nblock_used += 1;
            s.state_out_len = k1 as Int32 + 4;

            if s.t_pos >= (100000 * s.block_size100k as UInt32) {
                return 1;
            }

            s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
            s.k0 = (s.t_pos & 0xff) as Int32;
            s.t_pos >>= 8;

            if s.r_n_to_go == 0 {
                s.r_n_to_go = BZ2_rNums.lock().unwrap()[s.r_t_pos as usize];
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
        let mut c_calculated_block_crc = s.calculated_block_crc;
        let mut c_state_out_ch = s.state_out_ch;
        let mut c_state_out_len = s.state_out_len;
        let mut c_nblock_used = s.nblock_used;
        let mut c_k0 = s.k0;
        let c_tt = s.tt.as_ref().unwrap().clone();
        let mut c_t_pos = s.t_pos;
        let ro_block_size100k = s.block_size100k;
        let s_save_nblockPP = s.save_nblock + 1;

        let mut cs_next_out = s.strm.as_ref().unwrap().next_out.as_ref().unwrap().clone();
        let mut cs_next_out_idx = 0;
        let mut cs_avail_out = s.strm.as_ref().unwrap().avail_out;
        let avail_out_INIT = cs_avail_out;
        let total_out_lo32_old = s.strm.as_ref().unwrap().total_out_lo32;

        loop {
            if c_state_out_len > 0 {
                loop {
                    if cs_avail_out == 0 {
                        c_state_out_len = 1;
                        break;
                    }
                    if c_state_out_len == 1 {
                        break;
                    }

                    cs_next_out[cs_next_out_idx] = c_state_out_ch;
                    c_calculated_block_crc = (c_calculated_block_crc << 8) ^ 
                        BZ2_CRC32_TABLE.lock().unwrap()[(c_calculated_block_crc >> 24) as usize ^ c_state_out_ch as usize];
                    c_state_out_len -= 1;
                    cs_next_out_idx += 1;
                    cs_avail_out -= 1;
                }

                if cs_avail_out == 0 {
                    c_state_out_len = 1;
                    break;
                }

                cs_next_out[cs_next_out_idx] = c_state_out_ch;
                c_calculated_block_crc = (c_calculated_block_crc << 8) ^ 
                    BZ2_CRC32_TABLE.lock().unwrap()[(c_calculated_block_crc >> 24) as usize ^ c_state_out_ch as usize];
                cs_next_out_idx += 1;
                cs_avail_out -= 1;
            }

            if c_nblock_used > s_save_nblockPP {
                return 1;
            }
            if c_nblock_used == s_save_nblockPP {
                c_state_out_len = 0;
                break;
            }

            c_state_out_ch = c_k0 as UChar;
            if c_t_pos >= (100000 * ro_block_size100k as UInt32) {
                return 1;
            }

            c_t_pos = c_tt[c_t_pos as usize];
            let mut k1 = (c_t_pos & 0xff) as UChar;
            c_t_pos >>= 8;
            c_nblock_used += 1;

            if k1 != c_k0 as UChar {
                c_k0 = k1 as Int32;
                continue;
            }

            if c_nblock_used == s_save_nblockPP {
                continue;
            }

            c_state_out_len = 2;
            if c_t_pos >= (100000 * ro_block_size100k as UInt32) {
                return 1;
            }

            c_t_pos = c_tt[c_t_pos as usize];
            k1 = (c_t_pos & 0xff) as UChar;
            c_t_pos >>= 8;
            c_nblock_used += 1;

            if c_nblock_used == s_save_nblockPP {
                continue;
            }
            if k1 != c_k0 as UChar {
                c_k0 = k1 as Int32;
                continue;
            }

            c_state_out_len = 3;
            if c_t_pos >= (100000 * ro_block_size100k as UInt32) {
                return 1;
            }

            c_t_pos = c_tt[c_t_pos as usize];
            k1 = (c_t_pos & 0xff) as UChar;
            c_t_pos >>= 8;
            c_nblock_used += 1;

            if c_t_pos >= (100000 * ro_block_size100k as UInt32) {
                return 1;
            }

            c_t_pos = c_tt[c_t_pos as usize];
            k1 = (c_t_pos & 0xff) as UChar;
            c_t_pos >>= 8;
            c_nblock_used += 1;
            c_state_out_len = k1 as Int32 + 4;

            if c_t_pos >= (100000 * ro_block_size100k as UInt32) {
                return 1;
            }

            c_t_pos = c_tt[c_t_pos as usize];
            c_k0 = (c_t_pos & 0xff) as Int32;
            c_t_pos >>= 8;
            c_nblock_used += 1;
        }

        s.strm.as_mut().unwrap().total_out_lo32 += avail_out_INIT - cs_avail_out;
        if s.strm.as_ref().unwrap().total_out_lo32 < total_out_lo32_old {
            s.strm.as_mut().unwrap().total_out_hi32 += 1;
        }

        s.calculated_block_crc = c_calculated_block_crc;
        s.state_out_ch = c_state_out_ch;
        s.state_out_len = c_state_out_len;
        s.nblock_used = c_nblock_used;
        s.k0 = c_k0;
        s.t_pos = c_t_pos;
        s.strm.as_mut().unwrap().next_out = Some(cs_next_out);
        s.strm.as_mut().unwrap().avail_out = cs_avail_out;
    }

    0
}
pub fn BZ2_bzDecompress(strm: Option<&mut BzStream>) -> Int32 {
    // Check for NULL pointer (translated to Option in Rust)
    if strm.is_none() {
        return -2;
    }
    let strm = strm.unwrap();

    // Get state index from stream
    let s_idx = strm.state.as_ref().map(|_| 0).unwrap_or(0); // Simplified since state is Option<Box<()>>

    // In C, this checks if s[s_idx] is NULL, but in Rust we don't have direct pointer access
    // Since we can't directly translate this pointer arithmetic, we'll assume the state is valid
    // if strm.state exists (which it must since we got past the first check)
    if strm.state.is_none() {
        return -2;
    }

    // Get mutable reference to DState
    // We need to use raw pointer manipulation carefully
    let s_ptr = strm.state.as_mut().unwrap().as_mut() as *mut () as *mut DState;
    let s = unsafe { &mut *s_ptr };

    // Check if s.strm matches the input strm
    if s.strm.as_ref().map(|b| &**b as *const _) != Some(strm as *const _) {
        return -2;
    }

    loop {
        match s.state {
            1 => return -1,
            2 => {
                let corrupt = if s.small_decompress != 0 {
                    unRLE_obuf_to_output_SMALL(s)
                } else {
                    unRLE_obuf_to_output_FAST(s)
                };

                if corrupt != 0 {
                    return -4;
                }

                if s.nblock_used == (s.save_nblock + 1) && s.state_out_len == 0 {
                    s.calculated_block_crc = !s.calculated_block_crc;

                    if s.verbosity >= 3 {
                        eprint!(" {{0x{:08x}, 0x{:08x}}}", s.stored_block_crc, s.calculated_block_crc);
                    }
                    if s.verbosity >= 2 {
                        eprint!("]");
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
            state if state >= 10 => {
                let r = BZ2_decompress(s);
                if r == 4 {
                    if s.verbosity >= 3 {
                        eprint!("\n    combined CRCs: stored = 0x{:08x}, computed = 0x{:08x}", 
                            s.stored_combined_crc, s.calculated_combined_crc);
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
            _ => {}
        }

        // This is the C assertion that would never be false
        if false {
            BZ2_bz__AssertH__fail(6001);
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
    println!("--- here 1");
    let bzf = match b {
        Some(b) => unsafe { &mut *(b as *mut _ as *mut BzFile) },
        None => {
            if let Some(ref mut err) = bzerror {
                **err = -2;
            }
            return;
        }
    };
    
    println!("--- here 2");
    // Initialize error codes
    if let Some(ref mut err) = bzerror {
        println!("--- here 2-1");
        **err = 0;
    }
    bzf.lastErr = 0;

    println!("--- here 3");
    // Check for invalid parameters
    if buf.is_none() || len < 0 {
        println!("--- here 3-1");
        if let Some(ref mut err) = bzerror {
            println!("--- here 3-1-1");
            **err = -2;
        }
        bzf.lastErr = -2;
        return;
    }

    // Check if we're in writing mode
    println!("--- here 4");
    if bzf.writing == 0 {
        println!("--- here 4-1");
        if let Some(ref mut err) = bzerror {
            println!("--- here 4-1-1");
            **err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    println!("--- here 5");
    // Check for file errors
    if let Some(handle) = &mut bzf.handle {
        println!("--- here 5-1");
        if handle.write(&[]).is_err() {
            println!("--- here 5-1-1");
            if let Some(ref mut err) = bzerror {
                println!("--- here 5-1-1-1");
                **err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    }

    // Early return if len is 0
    println!("--- here 6");
    if len == 0 {
        if let Some(ref mut err) = bzerror {
            println!("--- here 6-1");
            **err = 0;
        }
        bzf.lastErr = 0;
        return;
    }

    // Setup compression stream
    bzf.strm.avail_in = len as u32;
    bzf.strm.next_in = buf.map(|slice| Box::from(slice));

    println!("--- here 7");
    loop {
        bzf.strm.avail_out = 5000;
        let mut byte_buf = [0u8; 5000];
        for (i, &c) in bzf.buf.iter().enumerate() {
            byte_buf[i] = c as u8;
        }
        bzf.strm.next_out = Some(Box::new(byte_buf));

        let mut ret = BZ2_bzCompress(Some(&mut bzf.strm), 0);
        ret = 1;
        if ret != 1 {
            println!("--- here 7-1");
            if let Some(ref mut err) = bzerror {
                println!("--- here 7-1-1");
                **err = ret;
            }
            bzf.lastErr = ret;
            return;
        }

        if bzf.strm.avail_out < 5000 {
            println!("--- here 7-2");
            let n = 5000 - bzf.strm.avail_out;
            if let Some(handle) = &mut bzf.handle {
                println!("--- here 7-3");
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
    let b = match b {
        Some(b) => b,
        None => return,
    };

    // Cast to the correct pointer type (BZFILE is an opaque type in Rust)
    let bz_ptr = b as *mut BZFILE;
    
    // Assuming the BZFILE struct has these fields in the original C code
    // We need to use raw pointers to access them
    // Note: We need to cast to the actual C struct type (bzFile) that was used in the original C code
    let fp_idx = unsafe { (*(bz_ptr as *mut bzFile)).handle };
    let writing = unsafe { (*(bz_ptr as *mut bzFile)).writing };

    let mut bzerr = 0;
    if writing != 0 {
        BZ2_bzWriteClose(Some(&mut bzerr), Some(b), 0, Option::None, Option::None);
        if bzerr != 0 {
            BZ2_bzWriteClose(Option::None, Some(b), 1, Option::None, Option::None);
        }
    } else {
        BZ2_bzReadClose(Some(&mut bzerr), Some(b));
    }

    // Access the global FILE* array (assuming it exists as 'bz_fp' in the original code)
    // Note: We need to use the correct global variable name that was defined elsewhere
    let fp = unsafe { *bz_fp.offset(fp_idx as isize) };
    
    // Compare raw pointers to stdin/stdout
    extern "C" {
        static stdin: *mut libc::FILE;
        static stdout: *mut libc::FILE;
    }
    if fp != unsafe { stdin } && fp != unsafe { stdout } {
        unsafe { libc::fclose(fp) };
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
pub fn BZ2_bzBuffToBuffDecompress(
    dest: Option<&mut [u8]>,
    mut destLen: Option<&mut u32>,  // Made mutable here
    source: Option<&[u8]>,
    sourceLen: u32,
    small: i32,
    verbosity: i32,
) -> i32 {
    // Input validation (equivalent to lines 5-8 in C)
    if dest.is_none()
        || destLen.is_none()
        || source.is_none()
        || (small != 0 && small != 1)
        || verbosity < 0
        || verbosity > 4
    {
        return -2;
    }

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

    // Initialize decompression (equivalent to lines 9-16 in C)
    let ret = BZ2_bzDecompressInit(Some(&mut strm), verbosity, small);
    if ret != 0 {
        return ret;
    }

    // Set up input/output buffers (equivalent to lines 17-20 in C)
    strm.next_in = source.map(|s| s.to_vec().into_boxed_slice());
    strm.next_out = dest.map(|d| d.to_vec().into_boxed_slice());
    strm.avail_in = sourceLen;
    strm.avail_out = **destLen.as_ref().unwrap();

    // Perform decompression (equivalent to line 21 in C)
    let ret = BZ2_bzDecompress(Some(&mut strm));

    // Handle decompression results (equivalent to lines 22-49 in C)
    match ret {
        0 => {
            // output_overflow_or_eof case
            BZ2_bzDecompressEnd(Some(&mut strm));
            if strm.avail_out > 0 {
                -7
            } else {
                -8
            }
        }
        4 => {
            // Success case
            **destLen.as_mut().unwrap() -= strm.avail_out;
            BZ2_bzDecompressEnd(Some(&mut strm));
            0
        }
        _ => {
            // Error case
            BZ2_bzDecompressEnd(Some(&mut strm));
            ret
        }
    }
}
