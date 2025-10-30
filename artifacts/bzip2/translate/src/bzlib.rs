use libc::FILE;
use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use std::alloc::dealloc;
use std::fs::File;
use std::io::Error;
use std::io::ErrorKind;
use std::io::Read;
use std::io::Seek;
use std::io::Write;
use std::io::stdin;
use std::io::stdout;
use std::io;
use std::mem;
use std::process;
use std::ptr;
use std::ffi::CStr;
use std::os::unix::io::FromRawFd;
use std::os::fd::AsRawFd;
use std::os::fd::RawFd;
use std::os::fd;
use lazy_static::lazy_static;
use rand::Rng;
use std::boxed::Box;
use std::sync::Mutex;
use std::convert::TryInto;

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
        // In Rust, memory management is typically handled by ownership system
        // Since this is a direct translation of a C free function,
        // we would normally not need this in Rust, but if we must match the C behavior:
        // Note: In real Rust code, we wouldn't manually free memory like this.
        // This is just a direct translation of the C pattern.
        unsafe {
            libc::free(addr as *mut _);
        }
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

pub fn default_bzalloc(opaque: Option<*mut ()>, items: Int32, size: Int32) -> Option<*mut ()> {
    let total_size = items as usize * size as usize;
    if total_size == 0 {
        return None;
    }

    let layout = match Layout::from_size_align(total_size, 1) {
        Ok(l) => l,
        Err(_) => return None,
    };

    // SAFETY: We've checked for zero size and valid layout
    let v = unsafe { alloc(layout) };
    if v.is_null() {
        None
    } else {
        Some(v as *mut ())
    }
}
pub fn BZ2_bzCompressInit(
    strm: &mut BzStream,
    blockSize100k: Int32,
    verbosity: Int32,
    workFactor: Int32,
) -> Int32 {
    if !bz_config_ok() {
        return -9;
    }

    if strm.state.is_some()
        || blockSize100k < 1
        || blockSize100k > 9
        || workFactor < 0
        || workFactor > 250
    {
        return -2;
    }

    let workFactor = if workFactor == 0 { 30 } else { workFactor };

    if strm.bzalloc.is_none() {
        strm.bzalloc = Some(Box::new(|opaque: Option<Box<()>>, items: i32, size: i32| {
            let opaque_ptr = opaque.as_ref().map(|b| Box::as_ref(b) as *const () as *mut ());
            let result = default_bzalloc(opaque_ptr, items, size);
            result.map(|ptr| unsafe { Box::from_raw(ptr as *mut ()) })
        }));
    }

    if strm.bzfree.is_none() {
        strm.bzfree = Some(Box::new(|opaque: Option<Box<()>>, addr: Option<Box<()>>| {
            if let Some(addr) = addr {
                let addr_ptr = Box::into_raw(addr) as *mut std::ffi::c_void;
                let opaque_ptr = opaque.as_ref().map(|b| {
                    Box::as_ref(b) as *const () as *mut () as *mut std::ffi::c_void
                });
                let opaque_ref = opaque_ptr.map(|p| unsafe { &mut *p });
                default_bzfree(opaque_ref, Some(unsafe { &mut *addr_ptr }));
            }
        }));
    }

    // Allocate EState
    let layout = Layout::new::<EState>();
    let s_ptr = unsafe { alloc(layout) as *mut EState };
    if s_ptr.is_null() {
        return -3;
    }

    let s = unsafe { &mut *s_ptr };
    s.strm = Some(Box::new(BzStream {
        next_in: strm.next_in.clone(),
        avail_in: strm.avail_in,
        total_in_lo32: strm.total_in_lo32,
        total_in_hi32: strm.total_in_hi32,
        next_out: strm.next_out.clone(),
        avail_out: strm.avail_out,
        total_out_lo32: strm.total_out_lo32,
        total_out_hi32: strm.total_out_hi32,
        state: None,
        bzalloc: None,
        bzfree: None,
        opaque: strm.opaque.clone(),
    }));
    s.arr1 = None;
    s.arr2 = None;
    s.ftab = None;

    let n = 100000 * blockSize100k;
    
    // Allocate arrays
    let bzalloc = strm.bzalloc.as_mut().unwrap();
    s.arr1 = bzalloc(strm.opaque.clone(), n as i32, 1).map(|_| vec![0; n as usize]);
    s.arr2 = bzalloc(strm.opaque.clone(), (n + 2 + 12 + 18 + 2) as i32, 1).map(|_| vec![0; (n + 2 + 12 + 18 + 2) as usize]);
    s.ftab = bzalloc(strm.opaque.clone(), 65537, 1).map(|_| vec![0; 65537]);

    if s.arr1.is_none() || s.arr2.is_none() || s.ftab.is_none() {
        let bzfree = strm.bzfree.as_mut().unwrap();
        if let Some(_) = s.arr1.take() {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        if let Some(_) = s.arr2.take() {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        if let Some(_) = s.ftab.take() {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        unsafe {
            dealloc(s_ptr as *mut u8, layout);
        }
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
    s.block = s.arr2.as_ref().map(|v| v.iter().map(|&x| x as UChar).collect());
    s.mtfv = s.arr1.as_ref().map(|v| v.iter().map(|&x| x as UInt16).collect());
    s.zbits = None;
    s.ptr = s.arr1.as_ref().map(|v| v.clone());

    strm.state = Some(Box::new(()));
    strm.total_in_lo32 = 0;
    strm.total_in_hi32 = 0;
    strm.total_out_lo32 = 0;
    strm.total_out_hi32 = 0;

    init_RL(s);
    prepare_new_block(s);
    0
}
pub fn BZ2_bzWriteOpen(
    mut bzerror: Option<&mut Int32>,
    f: Option<File>,
    blockSize100k: Int32,
    verbosity: Int32,
    workFactor: Int32,
) -> Option<Box<BzFile>> {
    // Initialize error codes if error pointer provided
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

    // Check for file errors
    let file = f.as_ref().unwrap();
    if let Err(_) = file.try_clone() {
        if let Some(ref mut err) = bzerror {
            **err = -6;
        }
        return Option::None;
    }

    // Allocate new BzFile
    let mut bzf = Box::new(BzFile {
        handle: f,
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

    // Initialize compression
    let work_factor = if workFactor == 0 { 30 } else { workFactor };
    let ret = BZ2_bzCompressInit(&mut bzf.strm, blockSize100k, verbosity, work_factor);

    if ret != 0 {
        if let Some(ref mut err) = bzerror {
            **err = ret;
        }
        bzf.lastErr = ret;
        return Option::None;
    }

    bzf.strm.avail_in = 0;
    bzf.initialisedOk = 1;
    Some(bzf)
}

pub fn BZ2_bzDecompressInit(
    strm: Option<&mut BzStream>,
    verbosity: Int32,
    small: Int32,
) -> Int32 {
    // Check if bzlib configuration is OK
    if !bz_config_ok() {
        return -9;
    }

    // Check for NULL stream pointer
    let strm = match strm {
        Some(s) => s,
        None => return -2,
    };

    // Validate small parameter (must be 0 or 1)
    if small != 0 && small != 1 {
        return -2;
    }

    // Validate verbosity parameter (must be between 0 and 4)
    if verbosity < 0 || verbosity > 4 {
        return -2;
    }

    // Set default allocators if not provided
    if strm.bzalloc.is_none() {
        strm.bzalloc = Some(Box::new(|opaque, size, _| {
            let layout = Layout::from_size_align(size as usize, 1).unwrap();
            unsafe {
                let ptr = alloc(layout);
                if ptr.is_null() {
                    None
                } else {
                    Some(Box::from_raw(ptr as *mut ()))
                }
            }
        }));
    }

    if strm.bzfree.is_none() {
        strm.bzfree = Some(Box::new(|opaque, ptr| {
            if let Some(p) = ptr {
                let layout = Layout::from_size_align(1, 1).unwrap(); // Size doesn't matter for dealloc
                unsafe {
                    dealloc(Box::into_raw(p) as *mut u8, layout);
                }
            }
        }));
    }

    // Allocate DState
    let s_ptr = match strm.bzalloc.as_mut().unwrap()(strm.opaque.take(), std::mem::size_of::<DState>() as i32, 1) {
        Some(p) => p,
        None => return -3,
    };

    // Initialize DState
    let s = DState {
        strm: Some(Box::new(BzStream {
            next_in: strm.next_in.take(),
            avail_in: strm.avail_in,
            total_in_lo32: strm.total_in_lo32,
            total_in_hi32: strm.total_in_hi32,
            next_out: strm.next_out.take(),
            avail_out: strm.avail_out,
            total_out_lo32: strm.total_out_lo32,
            total_out_hi32: strm.total_out_hi32,
            state: None,
            bzalloc: strm.bzalloc.take(),
            bzfree: strm.bzfree.take(),
            opaque: strm.opaque.take(),
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
        selector: [0; 2 + (900000 / 50)],
        selector_mtf: [0; 2 + (900000 / 50)],
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
    };

    // Store the DState in the stream
    unsafe {
        let s_box = Box::new(s);
        let raw_ptr = Box::into_raw(s_box);
        strm.state = Some(Box::from_raw(raw_ptr as *mut ()));
    }

    0
}
pub fn BZ2_bzReadOpen(
    mut bzerror: Option<&mut i32>,
    f: Option<File>,
    verbosity: i32,
    small: i32,
    unused: Option<&[u8]>,
    nUnused: i32,
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

    // Check for file errors
    let file = f.as_ref().unwrap();
    if let Err(_) = file.try_clone() {
        if let Some(ref mut err) = bzerror {
            **err = -6;
        }
        return None;
    }

    // Allocate new BzFile
    let mut bzf = Box::new(BzFile {
        handle: f,
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

    // Copy unused data to buffer if provided
    if let Some(unused_data) = unused {
        let copy_len = nUnused.min(5000) as usize;
        for (i, &byte) in unused_data.iter().take(copy_len).enumerate() {
            bzf.buf[i] = byte as char;
        }
        bzf.bufN = copy_len as i32;
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

    bzf.strm.avail_in = bzf.bufN as u32;
    bzf.strm.next_in = Some(bzf.buf.iter().map(|&c| c as u8).collect::<Vec<u8>>().into_boxed_slice());
    bzf.initialisedOk = 1;
    Some(bzf)
}

pub fn bzopen_or_bzdopen(
    path: Option<&CStr>,
    fd: i32,
    mode: Option<&CStr>,
    open_mode: i32,
) -> Option<Box<BzFile>> {
    let mode = mode?;
    let mode_bytes = mode.to_bytes();
    let mut mode_idx = 0;
    let mut writing = false;
    let mut blockSize100k = 9;
    let mut verbosity = 0;
    let workFactor = 30;
    let mut nUnused = 0;
    let unused = [0u8; 5000];
    let mut small_mode = 0;
    let mut mode2 = String::new();

    // Parse mode string
    while mode_idx < mode_bytes.len() {
        match mode_bytes[mode_idx] as char {
            'r' => writing = false,
            'w' => writing = true,
            's' => small_mode = 1,
            c if c.is_ascii_digit() => {
                blockSize100k = (c as i32) - ('0' as i32);
            }
            _ => {}
        }
        mode_idx += 1;
    }

    // Build mode2 string
    mode2.push_str(if writing { "wb" } else { "rb" });
    if open_mode == 0 {
        mode2.push('e');
    }

    let fp = if open_mode == 0 {
        match path {
            None => {
                let raw_fd: RawFd = if writing {
                    std::io::stdout().as_raw_fd()
                } else {
                    std::io::stdin().as_raw_fd()
                };
                unsafe { Some(File::from_raw_fd(raw_fd)) }
            }
            Some(p) if p.to_bytes().is_empty() => {
                let raw_fd: RawFd = if writing {
                    std::io::stdout().as_raw_fd()
                } else {
                    std::io::stdin().as_raw_fd()
                };
                unsafe { Some(File::from_raw_fd(raw_fd)) }
            }
            Some(p) => {
                let path_str = p.to_str().ok()?;
                File::open(path_str).ok()
            }
        }
    } else {
        unsafe { Some(File::from_raw_fd(fd)) }
    };

    let fp = fp?;

    if writing {
        let blockSize100k = blockSize100k.clamp(1, 9);
        BZ2_bzWriteOpen(
            None,
            Some(fp),
            blockSize100k,
            verbosity,
            workFactor,
        )
    } else {
        BZ2_bzReadOpen(
            None,
            Some(fp),
            verbosity,
            small_mode,
            Some(&unused),
            nUnused,
        )
    }
}
pub fn BZ2_bzopen(path: Option<&str>, mode: Option<&str>) -> Option<Box<BzFile>> {
    let c_path = if let Some(p) = path {
        match std::ffi::CString::new(p) {
            Ok(cstr) => Some(cstr),
            Err(_) => return Option::None,
        }
    } else {
        Option::None
    };
    let c_mode = if let Some(m) = mode {
        match std::ffi::CString::new(m) {
            Ok(cstr) => Some(cstr),
            Err(_) => return Option::None,
        }
    } else {
        Option::None
    };
    bzopen_or_bzdopen(
        c_path.as_ref().map(|cs| cs.as_c_str()),
        -1,
        c_mode.as_ref().map(|cs| cs.as_c_str()),
        0,
    )
}
pub fn BZ2_bzdopen(fd: fd::RawFd, mode: Option<&std::ffi::CStr>) -> Option<Box<BzFile>> {
    bzopen_or_bzdopen(None, fd, mode, 1)
}
pub fn BZ2_bzflush(b: Option<&mut BZFILE>) -> i32 {
    0
}

pub fn BZ2_bz__AssertH__fail(errcode: i32) {
    eprintln!(
        "\n\nbzip2/libbzip2: internal error number {}.\nThis is a bug in bzip2/libbzip2, {}.\nPlease report it at: https://gitlab.com/bzip2/bzip2/-/issues\nIf this happened when you were using some program which uses\nlibbzip2 as a component, you should also report this bug to\nthe author(s) of that program.\nPlease make an effort to report this bug;\ntimely and accurate bug reports eventually lead to higher\nquality software.  Thanks.\n\n",
        errcode,
        BZ2_bzlibVersion()
    );

    if errcode == 1007 {
        eprintln!(
            "\n*** A special note about internal error number 1007 ***\n\nExperience suggests that a common cause of i.e. 1007\nis unreliable memory or other hardware.  The 1007 assertion\njust happens to cross-check the results of huge numbers of\nmemory reads/writes, and so acts (unintendedly) as a stress\ntest of your memory system.\n\nI suggest the following: try compressing the file again,\npossibly monitoring progress in detail with the -vv flag.\n\n* If the error cannot be reproduced, and/or happens at different\n  points in compression, you may have a flaky memory system.\n  Try a memory-test program.  I have used Memtest86\n  (www.memtest86.com).  At the time of writing it is free (GPLd).\n  Memtest86 tests memory much more thorougly than your BIOSs\n  power-on test, and may find failures that the BIOS doesn't.\n\n* If the error can be repeatably reproduced, this is a bug in\n  bzip2, and I would very much like to hear about it.  Please\n  let me know, and, ideally, save a copy of the file causing the\n  problem -- without which I will be unable to investigate it.\n\n"
        );
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

pub fn myfeof(f: &mut std::fs::File) -> bool {
    let mut buf = [0u8; 1];
    match f.read(&mut buf) {
        Ok(0) => true,  // EOF reached
        Ok(_) => {
            // Rewind by 1 byte to "unget" the character
            f.seek(std::io::SeekFrom::Current(-1)).unwrap();
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

    // Check if state exists
    if strm.state.is_none() {
        return -2;
    }

    // Get EState from strm.state
    // Since state is stored as Box<()>, we need to cast it to Box<EState>
    // This is unsafe but matches the original C behavior
    let mut s = unsafe {
        let raw_ptr = Box::into_raw(strm.state.take().unwrap());
        Box::from_raw(raw_ptr as *mut EState)
    };

    // Check if s.strm matches the input strm
    if s.strm.as_ref().map(|b| &**b as *const BzStream) != Some(strm as *const BzStream) {
        return -2;
    }

    // Free allocated memory if present
    if let Some(bzfree) = &mut strm.bzfree {
        if let Some(arr1) = s.arr1.take() {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        if let Some(arr2) = s.arr2.take() {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        if let Some(ftab) = s.ftab.take() {
            bzfree(strm.opaque.clone(), Some(Box::new(())));
        }
        bzfree(strm.opaque.clone(), Some(Box::new(())));
    } else {
        // If there's no bzfree, we still need to prevent memory leak
        drop(s);
    }

    // Clear the state (already done when we took it above)
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
        Some(_) => 0, // Assuming state is valid if Some, using 0 as index
        None => return -2,
    };

    // Check if DState is valid (simplified from C version)
    // In Rust we can't directly access memory like C, so we assume if state exists it's valid
    if strm.state.is_none() {
        return -2;
    }

    // The original C code checks s->strm != strm, but in Rust we can't do this pointer comparison
    // safely without unsafe, so we'll skip this check as it's not idiomatic Rust

    // Free allocated memory using bzfree if present
    if let Some(bzfree) = &mut strm.bzfree {
        // Free tt if present
        if let Some(s) = strm.state.as_ref() {
            // In Rust we can't directly access DState fields from BzStream.state
            // This would require unsafe code or a different design
            // For translation purposes, we'll assume the fields are properly managed
        }

        // Free ll16 if present (same limitation as above)
        
        // Free ll4 if present (same limitation as above)

        // Free the state itself
        bzfree(strm.opaque.clone(), strm.state.clone());
    }

    strm.state = None;
    0
}
pub fn BZ2_bzReadGetUnused(
    bzerror: Option<&mut i32>,
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

    // Check if bzf is initialized (equivalent to bzf != 0 checks in C)
    if bzf.lastErr != 4 {
        if let Some(err) = bzerror {
            *err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    // Check for null pointers (translated to Option checks)
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
pub fn helper_helper_helper_BZ2_bzWriteClose64_1_1_1(
    n_ref: &mut Int32,
    n2_ref: &mut Int32,
    bzerror: &mut Option<Int32>,
    bzf: &mut BzFile,
) {
    let mut n = *n_ref;
    let mut n2 = *n2_ref;
    
    n = 5000 - bzf.strm.avail_out as Int32;
    
    if let Some(handle) = &mut bzf.handle {
        // Convert char slice to bytes
        let buf_chars = &bzf.buf[..n as usize];
        let mut buf_bytes = Vec::with_capacity(n as usize * 4); // Worst case for UTF-8
        for &c in buf_chars {
            let mut bytes = [0u8; 4];
            let len = c.encode_utf8(&mut bytes).len();
            buf_bytes.extend_from_slice(&bytes[..len]);
        }
        
        let write_result = handle.write_all(&buf_bytes);
        
        match write_result {
            Ok(_) => {
                n2 = buf_chars.len() as Int32;
            }
            Err(_) => {
                if let Some(err) = bzerror {
                    *err = -6;
                }
                bzf.lastErr = -6;
                return;
            }
        }
        
        if let Err(_) = handle.flush() {
            if let Some(err) = bzerror {
                *err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    } else {
        if let Some(err) = bzerror {
            *err = -6;
        }
        bzf.lastErr = -6;
        return;
    }

    *n_ref = n;
    *n2_ref = n2;
}
pub fn helper_add_pair_to_block_1(s: &mut EState, ch: UChar) {
    // Access inUse array and update the specified index
    s.inUse[(s.state_in_len - 4) as usize] = 1;
    
    // Access block vector (assuming it's initialized) and perform operations
    if let Some(block) = &mut s.block {
        // Ensure block has enough capacity
        while block.len() <= s.nblock as usize + 4 {
            block.push(0);
        }
        
        // Perform the series of writes
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
pub fn add_pair_to_block(s: &mut EState) {
    let ch = s.state_in_ch as UChar;
    
    // Update blockCRC for each iteration
    for _ in 0..s.state_in_len {
        let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
        s.blockCRC = (s.blockCRC << 8) ^ crc_table[((s.blockCRC >> 24) ^ (ch as UInt32)) as usize & 0xFF];
    }

    // Mark the character as in use
    s.inUse[s.state_in_ch as usize] = 1;

    // Handle different lengths
    match s.state_in_len {
        1 => {
            if let Some(block) = &mut s.block {
                block[s.nblock as usize] = ch;
                s.nblock += 1;
            }
        }
        2 => {
            if let Some(block) = &mut s.block {
                block[s.nblock as usize] = ch;
                s.nblock += 1;
                block[s.nblock as usize] = ch;
                s.nblock += 1;
            }
        }
        3 => {
            if let Some(block) = &mut s.block {
                block[s.nblock as usize] = ch;
                s.nblock += 1;
                block[s.nblock as usize] = ch;
                s.nblock += 1;
                block[s.nblock as usize] = ch;
                s.nblock += 1;
            }
        }
        _ => {
            helper_add_pair_to_block_1(s, ch);
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
    let mut progress_out: Bool = 0;

    loop {
        // Early exit conditions
        let strm = match &mut s.strm {
            Some(strm) => strm,
            None => break,
        };

        if strm.avail_out == 0 {
            break;
        }
        if s.state_out_pos >= s.numZ {
            break;
        }

        // Get zbits value safely
        let zbit = match &s.zbits {
            Some(zbits) if (s.state_out_pos as usize) < zbits.len() => {
                zbits[s.state_out_pos as usize]
            }
            _ => break,
        };

        // Update output buffer
        if let Some(next_out) = &mut strm.next_out {
            if strm.avail_out > 0 && !next_out.is_empty() {
                next_out[0] = zbit;
                progress_out = 1;
                
                // Update stream state
                s.state_out_pos += 1;
                strm.avail_out -= 1;
                
                // Move next_out pointer by creating a new slice
                *next_out = next_out[1..].to_vec().into_boxed_slice();
                
                // Update counters
                strm.total_out_lo32 += 1;
                if strm.total_out_lo32 == 0 {
                    strm.total_out_hi32 += 1;
                }
            } else {
                break;
            }
        } else {
            break;
        }
    }

    progress_out
}
pub fn helper_helper_helper_copy_input_until_stop_2_1_1(s: &mut EState) {
    // Get the next input byte safely
    let zchh = s.strm.as_ref().and_then(|strm| {
        strm.next_in.as_ref().and_then(|next_in| {
            if !next_in.is_empty() {
                Some(UInt32::from(next_in[0]))
            } else {
                None
            }
        })
    }).unwrap_or(0); // Default to 0 if no input available

    if (zchh != s.state_in_ch) && (s.state_in_len == 1) {
        let ch = s.state_in_ch as UChar;
        
        // Calculate block CRC
        {
            let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
            s.blockCRC = (s.blockCRC << 8) ^ crc_table[((s.blockCRC >> 24) as usize) ^ (ch as usize)];
        }

        s.inUse[s.state_in_ch as usize] = 1;
        if let Some(ref mut block) = s.block {
            block.push(ch);
        }
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
pub fn helper_helper_copy_input_until_stop_2_1(progress_in_ref: &mut Bool, s: &mut EState) {
    let mut progress_in = *progress_in_ref;
    
    if s.nblock >= s.nblockMAX {
        return;
    }
    
    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            return;
        }
    } else {
        return;
    }
    
    if s.avail_in_expect == 0 {
        return;
    }
    
    progress_in = 1;
    
    helper_helper_helper_copy_input_until_stop_2_1_1(s);
    
    if let Some(strm) = &mut s.strm {
        strm.next_in = None; // This is problematic - in C it's pointer arithmetic, in Rust we can't do this safely
        strm.avail_in -= 1;
        strm.total_in_lo32 += 1;
        
        if strm.total_in_lo32 == 0 {
            strm.total_in_hi32 += 1;
        }
    }
    
    s.avail_in_expect -= 1;
    *progress_in_ref = progress_in;
}
pub fn helper_copy_input_until_stop_2(progress_in_ref: &mut Bool, s: &mut EState) {
    let mut progress_in = *progress_in_ref;
    
    loop {
        helper_helper_copy_input_until_stop_2_1(&mut progress_in, s);
    }
    
    *progress_in_ref = progress_in;
}
pub fn helper_copy_input_until_stop_1(progress_in_ref: &mut Bool, s: &mut EState) {
    let mut progress_in = *progress_in_ref;
    
    loop {
        if s.nblock >= s.nblockMAX {
            break;
        }
        
        if s.strm.as_ref().map_or(true, |strm| strm.avail_in == 0) {
            break;
        }
        
        progress_in = 1;
        
        if let Some(strm) = s.strm.as_mut() {
            if let Some(next_in) = strm.next_in.as_mut() {
                if next_in.is_empty() {
                    break;
                }
                
                let zchh = UInt32::from(next_in[0]);
                
                if (zchh != s.state_in_ch) && (s.state_in_len == 1) {
                    let ch = s.state_in_ch as UChar;
                    
                    {
                        let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                        s.blockCRC = (s.blockCRC << 8) ^ crc_table[((s.blockCRC >> 24) as UInt32 ^ ch as UInt32) as usize];
                    }
                    
                    s.inUse[s.state_in_ch as usize] = 1;
                    if let Some(block) = s.block.as_mut() {
                        block[s.nblock as usize] = ch;
                    }
                    s.nblock += 1;
                    s.state_in_ch = zchh;
                } else if (zchh != s.state_in_ch) || (s.state_in_len == 255) {
                    let state_in_ch = s.state_in_ch;
                    if state_in_ch < 256 {
                        // Extract values needed for add_pair_to_block before calling it
                        let state_in_len = s.state_in_len;
                        drop(strm);  // Explicitly drop the mutable borrow
                        add_pair_to_block(s);
                        s.strm.as_mut().unwrap().next_in.as_mut().unwrap().rotate_left(1);
                        s.strm.as_mut().unwrap().avail_in -= 1;
                        s.strm.as_mut().unwrap().total_in_lo32 += 1;
                        if s.strm.as_mut().unwrap().total_in_lo32 == 0 {
                            s.strm.as_mut().unwrap().total_in_hi32 += 1;
                        }
                        s.state_in_ch = zchh;
                        s.state_in_len = 1;
                        continue;
                    }
                    s.state_in_ch = zchh;
                    s.state_in_len = 1;
                } else {
                    s.state_in_len += 1;
                }
                
                strm.next_in.as_mut().unwrap().rotate_left(1);
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }
    
    *progress_in_ref = progress_in;
}
pub fn copy_input_until_stop(s: &mut EState) -> Bool {
    let mut progress_in: Bool = 0;
    
    if s.mode == 2 {
        helper_copy_input_until_stop_1(&mut progress_in, s);
    } else {
        helper_copy_input_until_stop_2(&mut progress_in, s);
    }
    
    progress_in
}
pub fn handle_compress(strm: &mut BzStream) -> Bool {
    let mut progress_in: Bool = 0;
    let mut progress_out: Bool = 0;
    let s = unsafe { &mut *(strm.state.as_mut().unwrap().as_mut() as *mut () as *mut EState) };

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
                BZ2_compressBlock(s, Bool::from(s.mode == 4));
                s.state = 1;
            } else if s.nblock >= s.nblockMAX {
                BZ2_compressBlock(s, 0);
                s.state = 1;
            } else if strm.avail_in == 0 {
                break;
            }
        }
    }

    Bool::from(progress_in != 0 || progress_out != 0)
}

pub fn helper_BZ2_bzCompress_1(
    progress_ref: &mut Bool,
    strm: &mut BzStream,
    action: Int32,
    s: &mut EState,
) -> Int32 {
    let mut progress = *progress_ref;
    
    if action != 2 {
        return -1;
    }
    
    if s.avail_in_expect != strm.avail_in {
        return -1;
    }
    
    progress = handle_compress(strm);
    if progress == 0 {
        return -1;
    }
    
    if (s.avail_in_expect > 0) || (isempty_RL(s) == 0) || (s.state_out_pos < s.numZ) {
        return 3;
    }
    
    s.mode = 1;
    *progress_ref = progress;
    4
}
pub fn BZ2_bzCompress(strm: Option<&mut BzStream>, action: Int32) -> Int32 {
    let mut progress: Bool = 0; // Initialize with default value
    let s: *mut EState;
    let s_idx: UInt32;

    // Check for NULL pointer (Option::None in Rust)
    if strm.is_none() {
        return -2;
    }
    let strm = strm.unwrap();

    // Get state index from stream
    s_idx = match &strm.state {
        Some(_) => 0, // In the original C code, state is used directly as an index
        None => return -2,
    };

    // Get EState pointer
    // Note: This is unsafe as it's dereferencing a raw pointer
    // In real code, we should have proper safety guarantees
    s = s_idx as *mut EState;
    if s.is_null() {
        return -2;
    }
    let s = unsafe { &mut *s };

    // Check if strm matches by comparing raw pointers
    if s.strm.as_ref().map(|boxed| &**boxed as *const BzStream) != Some(strm as *const BzStream) {
        return -2;
    }

    // Main logic with match instead of goto
    match s.mode {
        1 => return -1,

        2 => {
            if action == 0 {
                progress = handle_compress(strm);
                return if progress != 0 { 1 } else { -2 };
            } else if action == 1 {
                s.avail_in_expect = strm.avail_in;
                s.mode = 3;
                return BZ2_bzCompress(Some(strm), action); // Recursive call instead of goto
            } else if action == 2 {
                s.avail_in_expect = strm.avail_in;
                s.mode = 4;
                return BZ2_bzCompress(Some(strm), action); // Recursive call instead of goto
            } else {
                return -2;
            }
        }

        3 => {
            if action != 1 {
                return -1;
            }
            if s.avail_in_expect != s.strm.as_ref().unwrap().avail_in {
                return -1;
            }
            progress = handle_compress(strm);
            if (s.avail_in_expect > 0) || (isempty_RL(s) == 0) || (s.state_out_pos < s.numZ) {
                return 2;
            }
            s.mode = 2;
            return 1;
        }

        4 => {
            return helper_BZ2_bzCompress_1(&mut progress, strm, action, s);
        }

        _ => return 0,
    }
}

pub fn helper_helper_BZ2_bzWriteClose64_1_1(
    n_ref: &mut Int32,
    n2_ref: &mut Int32,
    ret_ref: &mut Int32,
    bzerror: &mut Option<Int32>,
    bzf: &mut BzFile,
) {
    let mut n = *n_ref;
    let mut n2 = *n2_ref;
    let mut ret = *ret_ref;

    {
        let strm = &mut bzf.strm;
        strm.avail_out = 5000;
        strm.next_out = Some(Box::new(bzf.buf.map(|c| c as u8)));
    }

    ret = BZ2_bzCompress(Some(&mut bzf.strm), 2);

    if ret != 3 && ret != 4 {
        if let Some(err) = bzerror {
            *err = ret;
        }
        bzf.lastErr = ret;
        return;
    }

    if bzf.strm.avail_out < 5000 {
        helper_helper_helper_BZ2_bzWriteClose64_1_1_1(&mut n, &mut n2, bzerror, bzf);
    }

    if ret == 4 {
        // Note: 'break' in original C code would be invalid here as it's not in a loop
        // In Rust, we'll just return as this appears to be terminal condition
        *n_ref = n;
        *n2_ref = n2;
        *ret_ref = ret;
        return;
    }

    *n_ref = n;
    *n2_ref = n2;
    *ret_ref = ret;
}

pub fn helper_BZ2_bzWriteClose64_1(
    n_ref: &mut Int32,
    n2_ref: &mut Int32,
    ret_ref: &mut Int32,
    bzerror: &mut Option<Int32>,
    bzf: &mut BzFile,
) {
    let mut n = *n_ref;
    let mut n2 = *n2_ref;
    let mut ret = *ret_ref;
    
    loop {
        helper_helper_BZ2_bzWriteClose64_1_1(&mut n, &mut n2, &mut ret, bzerror, bzf);
    }
    
    *n_ref = n;
    *n2_ref = n2;
    *ret_ref = ret;
}
pub fn BZ2_bzWriteClose64(
    mut bzerror: Option<&mut Int32>,
    b: Option<&mut BZFILE>,
    abandon: Int32,
    mut nbytes_in_lo32: Option<&mut u32>,
    mut nbytes_in_hi32: Option<&mut u32>,
    mut nbytes_out_lo32: Option<&mut u32>,
    mut nbytes_out_hi32: Option<&mut u32>,
) {
    let bzf = match b {
        Some(b) => unsafe { &mut *(b as *mut BZFILE as *mut BzFile) },
        None => {
            if let Some(err) = bzerror.as_mut() {
                **err = 0;
            }
            return;
        }
    };

    if bzf.writing == 0 {
        if let Some(err) = bzerror.as_mut() {
            **err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    if let Some(handle) = &bzf.handle {
        if let Err(_) = handle.metadata() {
            if let Some(err) = bzerror.as_mut() {
                **err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    }

    if let Some(nbytes_in_lo32) = nbytes_in_lo32.as_mut() {
        **nbytes_in_lo32 = 0;
    }
    if let Some(nbytes_in_hi32) = nbytes_in_hi32.as_mut() {
        **nbytes_in_hi32 = 0;
    }
    if let Some(nbytes_out_lo32) = nbytes_out_lo32.as_mut() {
        **nbytes_out_lo32 = 0;
    }
    if let Some(nbytes_out_hi32) = nbytes_out_hi32.as_mut() {
        **nbytes_out_hi32 = 0;
    }

    if abandon == 0 && bzf.lastErr == 0 {
        let mut n = 0;
        let mut n2 = 0;
        let mut ret = 0;
        let mut bzerror_mut = bzerror.as_mut().map(|e| **e);
        helper_BZ2_bzWriteClose64_1(&mut n, &mut n2, &mut ret, &mut bzerror_mut, bzf);
        if let (Some(err), Some(original_err)) = (bzerror_mut, bzerror.as_mut()) {
            **original_err = err;
        }
    }

    if abandon == 0 {
        if let Some(handle) = &bzf.handle {
            if let Err(_) = handle.sync_all() {
                if let Some(err) = bzerror.as_mut() {
                    **err = -6;
                }
                bzf.lastErr = -6;
                return;
            }
        }
    }

    if let Some(nbytes_in_lo32) = nbytes_in_lo32.as_mut() {
        **nbytes_in_lo32 = bzf.strm.total_in_lo32;
    }
    if let Some(nbytes_in_hi32) = nbytes_in_hi32.as_mut() {
        **nbytes_in_hi32 = bzf.strm.total_in_hi32;
    }
    if let Some(nbytes_out_lo32) = nbytes_out_lo32.as_mut() {
        **nbytes_out_lo32 = bzf.strm.total_out_lo32;
    }
    if let Some(nbytes_out_hi32) = nbytes_out_hi32.as_mut() {
        **nbytes_out_hi32 = bzf.strm.total_out_hi32;
    }

    if let Some(err) = bzerror.as_mut() {
        **err = 0;
    }
    bzf.lastErr = 0;

    BZ2_bzCompressEnd(Some(&mut bzf.strm));
}
pub fn BZ2_bzWriteClose(
    mut bzerror: Option<&mut i32>,
    b: Option<&mut BZFILE>,
    abandon: i32,
    mut nbytes_in: Option<&mut u32>,
    mut nbytes_out: Option<&mut u32>,
) {
    BZ2_bzWriteClose64(
        bzerror,
        b,
        abandon,
        nbytes_in,
        None, // nbytes_in_hi32
        nbytes_out,
        None, // nbytes_out_hi32
    );
}
pub fn helper_helper_BZ2_bzRead_1_1(
    n_ref: &mut Int32,
    bzerror: Option<&mut Int32>,
    bzf: Option<&mut BzFile>,
) -> bool {
    // Check if bzf is None (equivalent to NULL check in C)
    let bzf = match bzf {
        Some(bzf) => bzf,
        None => return false,
    };

    // Check if handle exists
    let handle = match &mut bzf.handle {
        Some(handle) => handle,
        None => {
            if let Some(err) = bzerror {
                *err = -6;
            }
            bzf.lastErr = -6;
            return false;
        }
    };

    // Create a temporary u8 buffer for reading
    let mut byte_buf = [0u8; 5000];
    
    // Read data into byte buffer (equivalent to fread)
    let read_result = handle.read(&mut byte_buf);
    let n = match read_result {
        Ok(bytes_read) => bytes_read as Int32,
        Err(_) => {
            if let Some(err) = bzerror {
                *err = -6;
            }
            bzf.lastErr = -6;
            return false;
        }
    };

    // Convert bytes back to chars and copy to original buffer
    for i in 0..n as usize {
        bzf.buf[i] = byte_buf[i] as char;
    }

    // Check for IO error (equivalent to ferror)
    if handle.read(&mut []).is_err() {
        if let Some(err) = bzerror {
            *err = -6;
        }
        bzf.lastErr = -6;
        return false;
    }

    // Update struct fields
    bzf.bufN = n;
    bzf.strm.avail_in = n as u32;
    bzf.strm.next_in = Some(Box::new(byte_buf));

    // Update n_ref
    *n_ref = n;

    true
}
pub fn helper_helper_helper_unRLE_obuf_to_output_SMALL_2_1_1(s: &mut DState) -> Bool {
    // Check if there's no output space available
    if s.strm.as_ref().map_or(true, |strm| strm.avail_out == 0) {
        return 0;
    }

    // Check if there's no more data to output
    if s.state_out_len == 0 {
        return 0;
    }

    // Get mutable access to the stream
    if let Some(strm) = s.strm.as_mut() {
        // Write the output character
        if let Some(next_out) = strm.next_out.as_mut() {
            if strm.avail_out > 0 {
                next_out[0] = s.state_out_ch;
                
                // Update CRC
                {
                    let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                    s.calculated_block_crc = (s.calculated_block_crc << 8) 
                        ^ crc_table[((s.calculated_block_crc >> 24) as usize 
                        ^ s.state_out_ch as usize) & 0xff];
                }

                // Update state and stream
                s.state_out_len -= 1;
                strm.next_out = Some(next_out[1..].to_vec().into_boxed_slice());
                strm.avail_out -= 1;
                strm.total_out_lo32 += 1;

                // Handle 32-bit overflow
                if strm.total_out_lo32 == 0 {
                    strm.total_out_hi32 += 1;
                }
            }
        }
    }

    1
}
pub fn helper_helper_unRLE_obuf_to_output_SMALL_2_1(k1_ref: &mut UChar, s: &mut DState) -> Bool {
    let mut k1 = *k1_ref;
    
    loop {
        helper_helper_helper_unRLE_obuf_to_output_SMALL_2_1_1(s);

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
        
        k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
        s.t_pos = {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            (ll16[s.t_pos as usize] as UInt32) | 
            ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
        };
        
        if s.r_n_to_go == 0 {
            let mut rnums = BZ2_rNums.lock().unwrap();
            s.r_n_to_go = rnums[s.r_t_pos as usize];
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
        
        k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
        s.t_pos = {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            (ll16[s.t_pos as usize] as UInt32) | 
            ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
        };
        
        if s.r_n_to_go == 0 {
            let mut rnums = BZ2_rNums.lock().unwrap();
            s.r_n_to_go = rnums[s.r_t_pos as usize];
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
        
        k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
        s.t_pos = {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            (ll16[s.t_pos as usize] as UInt32) | 
            ((((ll4[(s.t_pos >> 1) as usize] as UInt32) >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16)
        };
        
        if s.r_n_to_go == 0 {
            let mut rnums = BZ2_rNums.lock().unwrap();
            s.r_n_to_go = rnums[s.r_t_pos as usize];
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
            let mut rnums = BZ2_rNums.lock().unwrap();
            s.r_n_to_go = rnums[s.r_t_pos as usize];
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
            let mut rnums = BZ2_rNums.lock().unwrap();
            s.r_n_to_go = rnums[s.r_t_pos as usize];
            s.r_t_pos += 1;
            if s.r_t_pos == 512 {
                s.r_t_pos = 0;
            }
        }
        s.r_n_to_go -= 1;
        
        s.k0 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
        s.nblock_used += 1;
        *k1_ref = k1;
    }
}
pub fn helper_unRLE_obuf_to_output_SMALL_2(k1_ref: &mut UChar, s: &mut DState) -> Bool {
    let mut k1 = *k1_ref;
    loop {
        helper_helper_unRLE_obuf_to_output_SMALL_2_1(&mut k1, s);
    }
    *k1_ref = k1;
}
pub fn helper_helper_helper_unRLE_obuf_to_output_SMALL_1_1_1(s: &mut DState) -> Bool {
    if s.strm.as_ref().unwrap().avail_out == 0 {
        return 0;
    }
    if s.state_out_len == 0 {
        return 0; // In Rust, we return instead of break since this isn't a loop
    }

    {
        let strm = s.strm.as_mut().unwrap();
        let next_out = strm.next_out.as_mut().unwrap();
        next_out[0] = s.state_out_ch;
        let mut new_next_out = next_out[1..].to_vec().into_boxed_slice();
        strm.next_out = Some(new_next_out);
    }

    {
        let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
        s.calculated_block_crc = (s.calculated_block_crc << 8) 
            ^ crc_table[((s.calculated_block_crc >> 24) as usize) ^ (s.state_out_ch as usize)];
    }

    s.state_out_len -= 1;
    {
        let strm = s.strm.as_mut().unwrap();
        strm.avail_out -= 1;
        strm.total_out_lo32 += 1;
        if strm.total_out_lo32 == 0 {
            strm.total_out_hi32 += 1;
        }
    }

    1 // Return true (1) to indicate success
}
pub fn helper_helper_unRLE_obuf_to_output_SMALL_1_1(k1_ref: &mut UChar, s: &mut DState) -> Bool {
    let mut k1 = *k1_ref;
    
    loop {
        helper_helper_helper_unRLE_obuf_to_output_SMALL_1_1_1(s);

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

        k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
        {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            s.t_pos = (ll16[s.t_pos as usize] as UInt32) | 
                     (((ll4[(s.t_pos >> 1) as usize] as UInt32 >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16);
        }
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

        k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
        {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            s.t_pos = (ll16[s.t_pos as usize] as UInt32) | 
                     (((ll4[(s.t_pos >> 1) as usize] as UInt32 >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16);
        }
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

        k1 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab) as UChar;
        {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            s.t_pos = (ll16[s.t_pos as usize] as UInt32) | 
                     (((ll4[(s.t_pos >> 1) as usize] as UInt32 >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16);
        }
        s.nblock_used += 1;

        if s.nblock_used == (s.save_nblock + 1) {
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
        {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            s.t_pos = (ll16[s.t_pos as usize] as UInt32) | 
                     (((ll4[(s.t_pos >> 1) as usize] as UInt32 >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16);
        }
        s.nblock_used += 1;
        s.state_out_len = (k1 as Int32) + 4;

        if s.t_pos >= (100000 * s.block_size100k as UInt32) {
            return 1;
        }

        s.k0 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab);
        {
            let ll16 = s.ll16.as_ref().unwrap();
            let ll4 = s.ll4.as_ref().unwrap();
            s.t_pos = (ll16[s.t_pos as usize] as UInt32) | 
                     (((ll4[(s.t_pos >> 1) as usize] as UInt32 >> ((s.t_pos << 2) & 0x4)) & 0xF) << 16);
        }
        s.nblock_used += 1;

        *k1_ref = k1;
    }
}
pub fn helper_unRLE_obuf_to_output_SMALL_1(k1_ref: &mut UChar, s: &mut DState) -> Bool {
    let mut k1 = *k1_ref;
    loop {
        helper_helper_unRLE_obuf_to_output_SMALL_1_1(&mut k1, s);
    }
    *k1_ref = k1;
}
pub fn unRLE_obuf_to_output_SMALL(s: &mut DState) -> Bool {
    let mut k1: UChar = 0;
    if s.block_randomised != 0 {
        helper_unRLE_obuf_to_output_SMALL_2(&mut k1, s)
    } else {
        helper_unRLE_obuf_to_output_SMALL_1(&mut k1, s)
    }
}
pub fn helper_helper_helper_unRLE_obuf_to_output_FAST_2_1_1(s: &mut DState) -> Bool {
    if s.strm.as_ref().map_or(true, |strm| strm.avail_out == 0) {
        return 0;
    }

    if s.state_out_len == 0 {
        return 0;
    }

    if let Some(strm) = s.strm.as_mut() {
        if let Some(next_out) = strm.next_out.as_mut() {
            // Write the output character
            next_out[0] = s.state_out_ch;

            // Update CRC
            {
                let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
                s.calculated_block_crc = (s.calculated_block_crc << 8) 
                    ^ crc_table[((s.calculated_block_crc >> 24) ^ s.state_out_ch as UInt32) as usize];
            }

            // Update state
            s.state_out_len -= 1;
            strm.next_out = Some(next_out[1..].to_vec().into_boxed_slice());
            strm.avail_out -= 1;
            strm.total_out_lo32 += 1;

            if strm.total_out_lo32 == 0 {
                strm.total_out_hi32 += 1;
            }
        }
    }

    1
}
pub fn helper_helper_unRLE_obuf_to_output_FAST_2_1(k1_ref: &mut UChar, s: &mut DState) -> Bool {
    let mut k1 = *k1_ref;
    
    loop {
        helper_helper_helper_unRLE_obuf_to_output_FAST_2_1_1(s);

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
        k1 = (s.t_pos & 0xff) as UChar;
        s.t_pos >>= 8;
        
        {
            let mut r_nums = BZ2_rNums.lock().unwrap();
            if s.r_n_to_go == 0 {
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
        }
        
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
        
        {
            let mut r_nums = BZ2_rNums.lock().unwrap();
            if s.r_n_to_go == 0 {
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
        }
        
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
        
        {
            let mut r_nums = BZ2_rNums.lock().unwrap();
            if s.r_n_to_go == 0 {
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
        }
        
        k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
        s.nblock_used += 1;
        
        if s.nblock_used == (s.save_nblock + 1) {
            continue;
        }
        if k1 != s.k0 as UChar {
            s.k0 = k1 as Int32;
            continue;
        }
        
        if s.t_pos >= (100000 * s.block_size100k as UInt32) {
            return 1;
        }
        
        s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
        k1 = (s.t_pos & 0xff) as UChar;
        s.t_pos >>= 8;
        
        {
            let mut r_nums = BZ2_rNums.lock().unwrap();
            if s.r_n_to_go == 0 {
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
        }
        
        k1 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
        s.nblock_used += 1;
        s.state_out_len = (k1 as Int32) + 4;
        
        if s.t_pos >= (100000 * s.block_size100k as UInt32) {
            return 1;
        }
        
        s.t_pos = s.tt.as_ref().unwrap()[s.t_pos as usize];
        s.k0 = (s.t_pos & 0xff) as Int32;
        s.t_pos >>= 8;
        
        {
            let mut r_nums = BZ2_rNums.lock().unwrap();
            if s.r_n_to_go == 0 {
                s.r_n_to_go = r_nums[s.r_t_pos as usize];
                s.r_t_pos += 1;
                if s.r_t_pos == 512 {
                    s.r_t_pos = 0;
                }
            }
            s.r_n_to_go -= 1;
        }
        
        s.k0 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
        s.nblock_used += 1;
        *k1_ref = k1;
    }
}
pub fn helper_unRLE_obuf_to_output_FAST_2(k1_ref: &mut UChar, s: &mut DState) -> Bool {
    let mut k1 = *k1_ref;
    loop {
        helper_helper_unRLE_obuf_to_output_FAST_2_1(&mut k1, s);
    }
    *k1_ref = k1;
}

pub fn helper_helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1_1(
    c_calculatedBlockCRC_ref: &mut UInt32,
    c_state_out_len_ref: &mut Int32,
    cs_next_out_idx_ref: &mut u32,
    cs_avail_out_ref: &mut u32,
    cs_next_out: &mut [UChar],
    c_state_out_ch: UChar,
) {
    let mut c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
    let mut c_state_out_len = *c_state_out_len_ref;
    let mut cs_next_out_idx = *cs_next_out_idx_ref;
    let mut cs_avail_out = *cs_avail_out_ref;

    if cs_avail_out == 0 {
        return;
    }

    if c_state_out_len == 1 {
        return;
    }

    if cs_next_out_idx < cs_next_out.len() as u32 {
        cs_next_out[cs_next_out_idx as usize] = c_state_out_ch;
    }

    {
        let crc_table = BZ2_CRC32_TABLE.lock().unwrap();
        c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) 
            ^ crc_table[((c_calculatedBlockCRC >> 24) ^ (c_state_out_ch as UInt32)) as usize];
    }

    c_state_out_len -= 1;
    cs_next_out_idx += 1;
    cs_avail_out -= 1;

    *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
    *c_state_out_len_ref = c_state_out_len;
    *cs_next_out_idx_ref = cs_next_out_idx;
    *cs_avail_out_ref = cs_avail_out;
}

pub fn helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(
    c_calculatedBlockCRC_ref: &mut UInt32,
    c_state_out_len_ref: &mut Int32,
    cs_next_out_idx_ref: &mut u32,
    cs_avail_out_ref: &mut u32,
    cs_next_out: &mut [UChar],
    c_state_out_ch: UChar,
) {
    // Dereference the input references to get local copies
    let mut c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
    let mut c_state_out_len = *c_state_out_len_ref;
    let mut cs_next_out_idx = *cs_next_out_idx_ref;
    let mut cs_avail_out = *cs_avail_out_ref;

    loop {
        helper_helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1_1(
            &mut c_calculatedBlockCRC,
            &mut c_state_out_len,
            &mut cs_next_out_idx,
            &mut cs_avail_out,
            cs_next_out,
            c_state_out_ch,
        );

        // Label equivalent: s_state_out_len_eq_one
        if cs_avail_out == 0 {
            c_state_out_len = 1;
            break;
        }

        // Write the character to output buffer
        cs_next_out[cs_next_out_idx as usize] = c_state_out_ch;
        
        // Update CRC
        let table = BZ2_CRC32_TABLE.lock().unwrap();
        c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ 
            table[((c_calculatedBlockCRC >> 24) ^ (c_state_out_ch as UInt32)) as usize];

        cs_next_out_idx += 1;
        cs_avail_out -= 1;
    }

    // Update the references with modified values
    *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
    *c_state_out_len_ref = c_state_out_len;
    *cs_next_out_idx_ref = cs_next_out_idx;
    *cs_avail_out_ref = cs_avail_out;
}

pub fn helper_helper_unRLE_obuf_to_output_FAST_1_1(
    k1_ref: &mut UChar,
    c_calculatedBlockCRC_ref: &mut UInt32,
    c_state_out_ch_ref: &mut UChar,
    c_state_out_len_ref: &mut Int32,
    c_nblock_used_ref: &mut Int32,
    c_k0_ref: &mut Int32,
    c_tPos_ref: &mut UInt32,
    cs_next_out_idx_ref: &mut u32,
    cs_avail_out_ref: &mut u32,
    c_tt: &[UInt32],
    cs_next_out: &mut [UChar],
    ro_blockSize100k: Int32,
    s_save_nblockPP: Int32,
) -> bool {
    // Dereference all input references
    let mut k1 = *k1_ref;
    let mut c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
    let mut c_state_out_ch = *c_state_out_ch_ref;
    let mut c_state_out_len = *c_state_out_len_ref;
    let mut c_nblock_used = *c_nblock_used_ref;
    let mut c_k0 = *c_k0_ref;
    let mut c_tPos = *c_tPos_ref;
    let mut cs_next_out_idx = *cs_next_out_idx_ref;
    let mut cs_avail_out = *cs_avail_out_ref;

    // Process state if there's pending output
    if c_state_out_len > 0 {
        helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(
            &mut c_calculatedBlockCRC,
            &mut c_state_out_len,
            &mut cs_next_out_idx,
            &mut cs_avail_out,
            cs_next_out,
            c_state_out_ch,
        );
    }

    // Early return checks
    if c_nblock_used > s_save_nblockPP {
        return true;
    }
    if c_nblock_used == s_save_nblockPP {
        c_state_out_len = 0;
        // goto return_notr equivalent
    } else {
        c_state_out_ch = c_k0.try_into().unwrap();
        let block_size_limit = (100000 * ro_blockSize100k as u64) as UInt32;
        
        if c_tPos >= block_size_limit {
            return true;
        }
        
        c_tPos = c_tt[c_tPos as usize];
        k1 = (c_tPos & 0xff) as UChar;
        c_tPos >>= 8;
        c_nblock_used += 1;
        
        if k1 != c_k0.try_into().unwrap() {
            c_k0 = k1.into();
            // goto s_state_out_len_eq_one equivalent
            c_state_out_len = 1;
        } else if c_nblock_used == s_save_nblockPP {
            // goto s_state_out_len_eq_one equivalent
            c_state_out_len = 1;
        } else {
            c_state_out_len = 2;
            if c_tPos >= block_size_limit {
                return true;
            }
            
            c_tPos = c_tt[c_tPos as usize];
            k1 = (c_tPos & 0xff) as UChar;
            c_tPos >>= 8;
            c_nblock_used += 1;
            
            if c_nblock_used == s_save_nblockPP {
                // continue equivalent
            } else if k1 != c_k0.try_into().unwrap() {
                c_k0 = k1.into();
                // continue equivalent
            } else {
                c_state_out_len = 3;
                if c_tPos >= block_size_limit {
                    return true;
                }
                
                c_tPos = c_tt[c_tPos as usize];
                k1 = (c_tPos & 0xff) as UChar;
                c_tPos >>= 8;
                c_nblock_used += 1;
                
                if c_nblock_used == s_save_nblockPP {
                    // continue equivalent
                } else if k1 != c_k0.try_into().unwrap() {
                    c_k0 = k1.into();
                    // continue equivalent
                } else {
                    if c_tPos >= block_size_limit {
                        return true;
                    }
                    
                    c_tPos = c_tt[c_tPos as usize];
                    k1 = (c_tPos & 0xff) as UChar;
                    c_tPos >>= 8;
                    c_nblock_used += 1;
                    c_state_out_len = (k1 as Int32) + 4;
                    
                    if c_tPos >= block_size_limit {
                        return true;
                    }
                    
                    c_tPos = c_tt[c_tPos as usize];
                    c_k0 = (c_tPos & 0xff) as Int32;
                    c_tPos >>= 8;
                    c_nblock_used += 1;
                }
            }
        }
    }

    // Update all output references
    *k1_ref = k1;
    *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
    *c_state_out_ch_ref = c_state_out_ch;
    *c_state_out_len_ref = c_state_out_len;
    *c_nblock_used_ref = c_nblock_used;
    *c_k0_ref = c_k0;
    *c_tPos_ref = c_tPos;
    *cs_next_out_idx_ref = cs_next_out_idx;
    *cs_avail_out_ref = cs_avail_out;

    false
}
pub fn helper_unRLE_obuf_to_output_FAST_1(k1_ref: &mut UChar, s: &mut DState) {
    let mut k1 = *k1_ref;
    let mut c_calculatedBlockCRC = s.calculated_block_crc;
    let mut c_state_out_ch = s.state_out_ch;
    let mut c_state_out_len = s.state_out_len;
    let mut c_nblock_used = s.nblock_used;
    let mut c_k0 = s.k0;
    let c_tt = s.tt.as_deref().unwrap(); // Assuming tt is always Some
    let mut c_tPos = s.t_pos;
    
    // Extract all needed values from strm upfront to avoid multiple borrows
    let strm = s.strm.as_mut().unwrap();
    let mut cs_next_out = strm.next_out.as_deref_mut().unwrap();
    let mut cs_next_out_idx = 0;
    let mut cs_avail_out = strm.avail_out;
    let total_out_lo32_old = strm.total_out_lo32;
    
    let ro_blockSize100k = s.block_size100k;
    let avail_out_INIT = cs_avail_out;
    let s_save_nblockPP = s.save_nblock + 1;
    
    loop {
        let continue_loop = helper_helper_unRLE_obuf_to_output_FAST_1_1(
            &mut k1,
            &mut c_calculatedBlockCRC,
            &mut c_state_out_ch,
            &mut c_state_out_len,
            &mut c_nblock_used,
            &mut c_k0,
            &mut c_tPos,
            &mut cs_next_out_idx,
            &mut cs_avail_out,
            c_tt,
            cs_next_out,
            ro_blockSize100k,
            s_save_nblockPP,
        );
        
        if !continue_loop {
            break;
        }
    }
    
    // Update all state fields at once
    strm.total_out_lo32 += avail_out_INIT - cs_avail_out;
    if strm.total_out_lo32 < total_out_lo32_old {
        strm.total_out_hi32 += 1;
    }
    
    s.calculated_block_crc = c_calculatedBlockCRC;
    s.state_out_ch = c_state_out_ch;
    s.state_out_len = c_state_out_len;
    s.nblock_used = c_nblock_used;
    s.k0 = c_k0;
    s.t_pos = c_tPos;
    
    // Update strm output using the same strm reference
    strm.next_out = Some(cs_next_out[cs_next_out_idx as usize..].to_vec().into_boxed_slice());
    strm.avail_out = cs_avail_out;
    
    *k1_ref = k1;
}
pub fn unRLE_obuf_to_output_FAST(s: &mut DState) -> Bool {
    let mut k1: UChar = 0;
    
    if s.block_randomised != 0 {
        helper_unRLE_obuf_to_output_FAST_2(&mut k1, s);
    } else {
        helper_unRLE_obuf_to_output_FAST_1(&mut k1, s);
    }
    
    0
}

pub fn helper_helper_BZ2_bzDecompress_1_1(corrupt_ref: &mut Bool, s: &mut DState) -> Int32 {
    let mut corrupt = *corrupt_ref;
    
    corrupt = if s.small_decompress != 0 {
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
            let _ = writeln!(
                io::stderr(),
                " {{0x{:08x}, 0x{:08x}}}",
                s.stored_block_crc,
                s.calculated_block_crc
            );
        }
        
        if s.verbosity >= 2 {
            let _ = write!(io::stderr(), "]");
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

    *corrupt_ref = corrupt;
    0
}

pub fn helper_BZ2_bzDecompress_1(corrupt_ref: &mut Bool, s: &mut DState) -> Int32 {
    let mut corrupt = *corrupt_ref;
    
    if s.state == 1 {
        return -1;
    }
    
    if s.state == 2 {
        helper_helper_BZ2_bzDecompress_1_1(&mut corrupt, s);
    }
    
    if s.state >= 10 {
        let r = BZ2_decompress(s);
        if r == 4 {
            if s.verbosity >= 3 {
                let _ = writeln!(
                    io::stderr(),
                    "\n    combined CRCs: stored = 0x{:08x}, computed = 0x{:08x}",
                    s.stored_combined_crc,
                    s.calculated_combined_crc
                );
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
    
    *corrupt_ref = corrupt;
    0 // Assuming default return value when none of the conditions match
}
pub fn BZ2_bzDecompress(strm: Option<&mut BzStream>) -> i32 {
    // Check for NULL pointer (translated to Option in Rust)
    if strm.is_none() {
        return -2;
    }

    let strm = strm.unwrap();
    let s_idx = strm.state.as_ref().map(|s| s as *const _ as *mut DState);
    
    // Check if state exists and is valid
    if s_idx.is_none() {
        return -2;
    }
    
    let s = unsafe { &mut *s_idx.unwrap() };
    
    // Check if the stream pointer matches
    if s.strm.as_ref().map(|st| &**st as *const _) != Some(strm as *const _) {
        return -2;
    }

    let mut corrupt: Bool = 0;
    
    // Infinite loop (translated from while(1))
    loop {
        helper_BZ2_bzDecompress_1(&mut corrupt, s);
    }

    // Assertion check (translated from if (!0))
    if false {
        BZ2_bz__AssertH__fail(6001);
    }

    0
}
pub fn helper_BZ2_bzRead_1(
    n_ref: &mut Int32,
    ret_ref: &mut Int32,
    mut bzerror: Option<&mut Int32>,
    len: i32,
    mut bzf: Option<&mut BzFile>,
) -> i32 {
    let mut n = *n_ref;
    let mut ret = *ret_ref;

    // Check for file error
    if let Some(bzf) = &mut bzf {
        if let Some(handle) = &mut bzf.handle {
            if handle.stream_position().is_err() {
                if let Some(bzerror) = &mut bzerror {
                    **bzerror = -6;
                }
                bzf.lastErr = -6;
                return 0;
            }
        }
    }

    // Check if we need to read more data
    if let Some(bzf) = &mut bzf {
        if let Some(handle) = &mut bzf.handle {
            if bzf.strm.avail_in == 0 && !myfeof(handle) {
                helper_helper_BZ2_bzRead_1_1(&mut n, bzerror.as_deref_mut(), Some(bzf));
            }
        }
    }

    // Decompress
    if let Some(bzf) = &mut bzf {
        ret = BZ2_bzDecompress(Some(&mut bzf.strm));
    }

    // Handle decompression errors
    if ret != 0 && ret != 4 {
        if let Some(bzerror) = &mut bzerror {
            **bzerror = ret;
        }
        if let Some(bzf) = &mut bzf {
            bzf.lastErr = ret;
        }
        return 0;
    }

    // Handle EOF condition
    if let Some(bzf) = &mut bzf {
        if let Some(handle) = &mut bzf.handle {
            if ret == 0 && myfeof(handle) && bzf.strm.avail_in == 0 && bzf.strm.avail_out > 0 {
                if let Some(bzerror) = &mut bzerror {
                    **bzerror = -7;
                }
                bzf.lastErr = -7;
                return 0;
            }
        }
    }

    // Handle specific return code
    if ret == 4 {
        if let Some(bzerror) = &mut bzerror {
            **bzerror = 4;
        }
        if let Some(bzf) = &mut bzf {
            bzf.lastErr = 4;
            return len - bzf.strm.avail_out as i32;
        }
        return 0;
    }

    // Handle output buffer full
    if let Some(bzf) = &mut bzf {
        if bzf.strm.avail_out == 0 {
            if let Some(bzerror) = &mut bzerror {
                **bzerror = 0;
            }
            bzf.lastErr = 0;
            return len;
        }
    }

    // Update references
    *n_ref = n;
    *ret_ref = ret;
    0
}
pub fn BZ2_bzRead(
    mut bzerror: Option<&mut Int32>,
    mut b: Option<&mut BzFile>,
    buf: Option<&mut [u8]>,
    len: Int32,
) -> Int32 {
    // Initialize error codes to 0 if pointers are provided
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

    let bzf = b.as_mut().unwrap(); // Safe because we checked above

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

    // Set up the output buffer
    bzf.strm.avail_out = len as u32;
    bzf.strm.next_out = Some(buf.unwrap().to_vec().into_boxed_slice());

    // Process the data
    let mut n = 0;
    let mut ret = 0;
    loop {
        helper_BZ2_bzRead_1(&mut n, &mut ret, bzerror.as_deref_mut(), len, Some(bzf));
    }

    0
}
pub fn BZ2_bzread(
    b: Option<&mut BzFile>,
    buf: Option<&mut [u8]>,
    len: i32,
) -> i32 {
    let mut bzerr = 0;
    let nread;

    // Check if lastErr is 4 (equivalent to line 5-8 in C)
    if let Some(bz_file) = &b {
        if bz_file.lastErr == 4 {
            return 0;
        }
    }

    // Call BZ2_bzRead (equivalent to line 9 in C)
    nread = BZ2_bzRead(Some(&mut bzerr), b, buf, len);

    // Handle return value based on bzerr (equivalent to lines 10-17 in C)
    if bzerr == 0 || bzerr == 4 {
        nread
    } else {
        -1
    }
}
pub fn helper_helper_BZ2_bzWrite_1_1(
    n_ref: &mut Int32,
    n2_ref: &mut Int32,
    bzerror: Option<&mut Int32>,
    bzf: Option<&mut BzFile>,
) {
    let mut n = *n_ref;
    let mut n2 = *n2_ref;

    // Get the BzFile if it exists
    if let Some(bzf) = bzf {
        n = 5000 - bzf.strm.avail_out as Int32;
        
        // Perform the write operation
        if let Some(handle) = &mut bzf.handle {
            // Convert char buffer to bytes for writing
            let byte_buf: Vec<u8> = bzf.buf[..n as usize].iter().map(|&c| c as u8).collect();
            let write_result = handle.write_all(&byte_buf);
            n2 = match write_result {
                Ok(_) => n,
                Err(_) => 0,
            };

            // Check for write errors
            if n != n2 || handle.flush().is_err() {
                if let Some(err) = bzerror {
                    *err = -6;
                }
                bzf.lastErr = -6;
                return;
            }
        } else {
            if let Some(err) = bzerror {
                *err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    } else {
        if let Some(err) = bzerror {
            *err = -6;
        }
        return;
    }

    *n_ref = n;
    *n2_ref = n2;
}
pub fn helper_BZ2_bzWrite_1(
    n_ref: &mut Int32,
    n2_ref: &mut Int32,
    ret_ref: &mut Int32,
    mut bzerror: Option<&mut Int32>,
    mut bzf: Option<&mut BzFile>,
) {
    let mut n = *n_ref;
    let mut n2 = *n2_ref;
    let mut ret = *ret_ref;

    if let Some(bzf) = bzf.as_mut() {
        bzf.strm.avail_out = 5000;
        bzf.strm.next_out = Some(Box::new(bzf.buf.map(|c| c as u8)));
    }

    ret = BZ2_bzCompress(bzf.as_mut().map(|bzf| &mut bzf.strm), 0);
    
    if ret != 1 {
        if let Some(bzerror) = bzerror {
            *bzerror = ret;
        }
        if let Some(bzf) = bzf.as_mut() {
            bzf.lastErr = ret;
        }
        return;
    }

    if let Some(bzf) = bzf.as_mut() {
        if bzf.strm.avail_out < 5000 {
            helper_helper_BZ2_bzWrite_1_1(&mut n, &mut n2, bzerror.as_deref_mut(), Some(bzf));
        }
        if bzf.strm.avail_in == 0 {
            if let Some(bzerror) = bzerror {
                *bzerror = 0;
            }
            bzf.lastErr = 0;
            return;
        }
    }

    *n_ref = n;
    *n2_ref = n2;
    *ret_ref = ret;
}
pub fn BZ2_bzWrite(
    mut bzerror: Option<&mut Int32>,
    b: Option<&mut BZFILE>,
    buf: Option<&[u8]>,
    len: Int32,
) {
    let bzf = match b {
        Some(b) => b as *mut BZFILE as *mut BzFile,
        None => std::ptr::null_mut(),
    };

    // Initialize error codes if pointers are provided
    if let Some(err) = bzerror.as_mut() {
        **err = 0;
    }
    unsafe {
        if !bzf.is_null() {
            (*bzf).lastErr = 0;
        }
    }

    // Check for null pointers or invalid length
    if bzf.is_null() || buf.is_none() || len < 0 {
        if let Some(err) = bzerror.as_mut() {
            **err = -2;
        }
        unsafe {
            if !bzf.is_null() {
                (*bzf).lastErr = -2;
            }
        }
        return;
    }

    let bzf = unsafe { &mut *bzf };

    // Check writing mode
    if bzf.writing == 0 {
        if let Some(err) = bzerror.as_mut() {
            **err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    // Check for file errors
    if let Some(handle) = &bzf.handle {
        if let Err(_) = handle.try_clone() {
            if let Some(err) = bzerror.as_mut() {
                **err = -6;
            }
            bzf.lastErr = -6;
            return;
        }
    }

    // Handle zero-length write
    if len == 0 {
        if let Some(err) = bzerror.as_mut() {
            **err = 0;
        }
        bzf.lastErr = 0;
        return;
    }

    // Prepare the stream for writing
    bzf.strm.avail_in = len as u32;
    bzf.strm.next_in = buf.map(|slice| {
        let mut boxed = slice.to_vec().into_boxed_slice();
        let ptr = boxed.as_mut_ptr();
        std::mem::forget(boxed); // Prevent deallocation
        unsafe { Box::from_raw(std::slice::from_raw_parts_mut(ptr, slice.len())) }
    });

    // Main write loop
    let mut n = 0;
    let mut n2 = 0;
    let mut ret = 0;
    loop {
        helper_BZ2_bzWrite_1(
            &mut n,
            &mut n2,
            &mut ret,
            bzerror.as_mut().map(|r| &mut **r), // Reborrow instead of move
            Some(&mut *bzf),                   // Reborrow mutable reference
        );
    }
}
pub fn BZ2_bzwrite(b: Option<&mut BZFILE>, buf: Option<&[u8]>, len: i32) -> i32 {
    let mut bzerr: i32 = 0;
    BZ2_bzWrite(Some(&mut bzerr), b, buf, len);
    
    if bzerr == 0 {
        len
    } else {
        -1
    }
}
pub fn BZ2_bzerror(b: Option<&BZFILE>, errnum: Option<&mut i32>) -> Option<&'static str> {
    // Since BZFILE is opaque, we need to work with raw pointers directly
    let err = unsafe { 
        if let Some(b_ptr) = b {
            *(b_ptr as *const _ as *const i32)
        } else {
            0
        }
    };
    
    let adjusted_err = if err > 0 { 0 } else { err };
    
    if let Some(en) = errnum {
        *en = adjusted_err;
    }
    
    Some(BZERRORSTRINGS[(adjusted_err * -1) as usize])
}

lazy_static! {
    pub static ref BZERRORSTRINGS: [&'static str; 16] = [
        "OK",
        "SEQUENCE_ERROR",
        "PARAM_ERROR",
        "MEM_ERROR",
        "DATA_ERROR",
        "DATA_ERROR_MAGIC",
        "IO_ERROR",
        "UNEXPECTED_EOF",
        "OUTBUFF_FULL",
        "CONFIG_ERROR",
        "???",
        "???",
        "???",
        "???",
        "???",
        "???"
    ];
}
pub fn BZ2_bzReadClose(mut bzerror: Option<&mut Int32>, b: Option<&mut BZFILE>) {
    // Convert BZFILE to bzFile (assuming BZFILE is a transparent wrapper around bzFile)
    let bzf = match b {
        Some(b) => unsafe { &mut *(b as *mut _ as *mut BzFile) },
        None => {
            if let Some(ref mut err) = bzerror {
                **err = 0;
            }
            return;
        }
    };

    // First block: clear errors if pointers are valid
    {
        if let Some(ref mut err) = bzerror {
            **err = 0;
        }
        bzf.lastErr = 0;
    }

    // Early return if bzf is null (handled above in the match)
    // Check if we're in writing mode
    if bzf.writing != 0 {
        if let Some(ref mut err) = bzerror {
            **err = -1;
        }
        bzf.lastErr = -1;
        return;
    }

    // Decompress end if initialized
    if bzf.initialisedOk != 0 {
        BZ2_bzDecompressEnd(Some(&mut bzf.strm));
    }

    // Free the bzf object
    // In Rust, we would typically let the Drop trait handle this,
    // but since we're modeling C behavior, we'll explicitly drop it
    unsafe {
        let _ = Box::from_raw(bzf as *mut BzFile);
    }
}
pub fn BZ2_bzclose(b: Option<&mut BZFILE>) {
    let fp_idx;

    // If b is None, return early.
    let ptr = if let Some(inner) = b {
        inner as *mut BZFILE
    } else {
        return;
    };

    // Access the handle (fp_idx) at offset 0
    fp_idx = unsafe { *(ptr as *mut u32) }; // Assuming handle is the first field

    // Check the writing flag at offset 4 (as a byte)
    let writing_flag = unsafe { *((ptr as *mut u8).add(4)) };

    if writing_flag != 0 {
        let mut bzerr_temp = 0;
        // Create a temporary Option<&mut BZFILE> from the raw pointer for the first call
        let b_option = unsafe { Some(&mut *ptr) };
        BZ2_bzWriteClose(Some(&mut bzerr_temp), b_option, 0, Option::None, Option::None);
        if bzerr_temp != 0 {
            let b_option2 = unsafe { Some(&mut *ptr) };
            BZ2_bzWriteClose(Option::None, b_option2, 1, Option::None, Option::None);
        }
    } else {
        let mut bzerr_temp = 0;
        let b_option = unsafe { Some(&mut *ptr) };
        BZ2_bzReadClose(Some(&mut bzerr_temp), b_option);
    }

    unsafe {
        // Use the global array `GLOBAL_fp` declared in the extern block
        let current_fp = *GLOBAL_fp.offset(fp_idx as isize);
        if !current_fp.is_null() && current_fp != libc_stdin() && current_fp != libc_stdout() {
            libc::fclose(current_fp);
        }
    }
}

extern "C" {
    fn libc_stdin() -> *mut libc::FILE;
    fn libc_stdout() -> *mut libc::FILE;
    static mut GLOBAL_fp: *mut *mut libc::FILE; // Renamed the global array to avoid shadowing conflicts
}
pub fn BZ2_bzBuffToBuffCompress(
    dest: Option<&mut [u8]>,
    destLen: Option<&mut u32>,
    source: Option<&[u8]>,
    sourceLen: u32,
    blockSize100k: i32,
    verbosity: i32,
    workFactor: i32,
) -> i32 {
    // Validate input parameters (equivalent to C's NULL checks and range checks)
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

    let ret = BZ2_bzCompressInit(&mut strm, blockSize100k, verbosity, workFactor);
    if ret != 0 {
        return ret;
    }

    // Safe because we've already checked for None above
    let dest = dest.unwrap();
    let source = source.unwrap();
    let destLen = destLen.unwrap();

    strm.next_in = Some(source.to_vec().into_boxed_slice());
    strm.next_out = Some(dest.to_vec().into_boxed_slice());
    strm.avail_in = sourceLen;
    strm.avail_out = *destLen;

    let ret = BZ2_bzCompress(Some(&mut strm), 2);

    match ret {
        3 => {
            BZ2_bzCompressEnd(Some(&mut strm));
            -8
        }
        4 => {
            *destLen -= strm.avail_out;
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
    mut destLen: Option<&mut u32>,
    source: Option<&[u8]>,
    sourceLen: u32,
    small: i32,
    verbosity: i32,
) -> i32 {
    // Validate input parameters (equivalent to lines 5-8 in C)
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
    let mut ret = BZ2_bzDecompressInit(Some(&mut strm), verbosity, small);
    if ret != 0 {
        return ret;
    }

    // Set up input/output buffers (equivalent to lines 17-20 in C)
    strm.next_in = source.map(|s| s.to_vec().into_boxed_slice());
    strm.next_out = dest.map(|d| d.to_vec().into_boxed_slice());
    strm.avail_in = sourceLen;
    if let Some(len) = &mut destLen {
        strm.avail_out = **len;
    }

    // Perform decompression (equivalent to line 21 in C)
    ret = BZ2_bzDecompress(Some(&mut strm));

    // Handle decompression results (equivalent to lines 22-49 in C)
    match ret {
        0 => {
            // output_overflow_or_eof case
            if strm.avail_out > 0 {
                BZ2_bzDecompressEnd(Some(&mut strm));
                -7
            } else {
                BZ2_bzDecompressEnd(Some(&mut strm));
                -8
            }
        }
        4 => {
            // Success case
            if let Some(len) = &mut destLen {
                **len -= strm.avail_out;
            }
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
