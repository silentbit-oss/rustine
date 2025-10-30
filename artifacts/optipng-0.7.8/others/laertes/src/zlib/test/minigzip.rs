
extern "C" {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    #[no_mangle]
    fn unlink(__name: * const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    static mut stdin: * mut crate::src::gifread::gifread::_IO_FILE;
    #[no_mangle]
    static mut stdout: * mut crate::src::gifread::gifread::_IO_FILE;
    #[no_mangle]
    static mut stderr: * mut crate::src::gifread::gifread::_IO_FILE;
    #[no_mangle]
    fn fclose(__stream: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn fopen(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char) -> * mut crate::src::gifread::gifread::_IO_FILE;
    #[no_mangle]
    fn fprintf(_: * mut crate::src::gifread::gifread::_IO_FILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn snprintf(_: * mut std::os::raw::c_char, _: std::os::raw::c_ulong,
                _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn fread(_: * mut core::ffi::c_void, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
             _: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn fwrite(_: * const core::ffi::c_void, _: std::os::raw::c_ulong, _: std::os::raw::c_ulong,
              _: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn ferror(__stream: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn perror(__s: * const std::os::raw::c_char);
    #[no_mangle]
    fn fileno(__stream: * mut crate::src::gifread::gifread::_IO_FILE) -> std::os::raw::c_int;
    #[no_mangle]
    fn strlen(_: * const std::os::raw::c_char) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn strcmp(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn strrchr(_: * const std::os::raw::c_char, _: std::os::raw::c_int) -> * mut std::os::raw::c_char;
    #[no_mangle]
    fn exit(_: std::os::raw::c_int) -> !;
}
pub use crate::src::zlib::gzclose::gzclose;
pub use crate::src::zlib::gzlib::gzdopen;
pub use crate::src::zlib::gzlib::gzerror;
pub use crate::src::zlib::gzlib::gzopen;
pub use crate::src::zlib::gzread::gzread;
pub use crate::src::zlib::gzwrite::gzwrite;
pub use crate::src::pngxtern::pngxread::_IO_marker;
pub use crate::src::pngxtern::pngxrpnm::_IO_wide_data;
pub use crate::src::pnmio::pnmout::_IO_codecvt;
pub type size_t = std::os::raw::c_ulong;
pub type voidpc = * const core::ffi::c_void;
pub type voidp = * mut core::ffi::c_void;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
pub type off64_t = std::os::raw::c_long;
// #[derive(Copy, Clone)]

pub type gzFile_s = crate::src::zlib::gzclose::gzFile_s;
pub type gzFile = * mut crate::src::zlib::gzclose::gzFile_s;
// #[derive(Copy, Clone)]

pub type _IO_FILE = crate::src::gifread::gifread::_IO_FILE;
pub type _IO_lock_t = ();
pub type FILE = crate::src::gifread::gifread::_IO_FILE;
static mut prog: * mut std::os::raw::c_char =
    (0 as * mut std::os::raw::c_char); unsafe fn laertes_init_prog() {
prog = 0 as *const std::os::raw::c_char as *mut std::os::raw::c_char;}//;
/* ===========================================================================
 * Display error message and exit
 */
#[no_mangle]
pub unsafe extern "C" fn error(mut msg: * const std::os::raw::c_char) {
    fprintf(stderr, b"%s: %s\n\x00" as *const u8 as *const std::os::raw::c_char, prog,
            msg);
    exit(1 as std::os::raw::c_int);
}
/* ===========================================================================
 * Compress input to output then close both files.
 */
#[no_mangle]
pub unsafe extern "C" fn gz_compress(mut in_0: * mut crate::src::gifread::gifread::_IO_FILE, mut out: * mut crate::src::zlib::gzclose::gzFile_s) {
    let mut buf: [i8; 16384] = [0; 16384];
    let mut len: i32 = 0;
    let mut err: i32 = 0;
    loop  {
        len =
            fread(buf.as_mut_ptr() as *mut std::os::raw::c_void,
                  1 as std::os::raw::c_int as std::os::raw::c_ulong,
                  ::std::mem::size_of::<[std::os::raw::c_char; 16384]>() as
                      std::os::raw::c_ulong, in_0) as std::os::raw::c_int;
        if ferror(in_0) != 0 {
            perror(b"fread\x00" as *const u8 as *const std::os::raw::c_char);
            exit(1 as std::os::raw::c_int);
        }
        if len == 0 as std::os::raw::c_int { break ; }
        if gzwrite(out, buf.as_mut_ptr() as voidpc, len as std::os::raw::c_uint) !=
               len {
            error(gzerror(out, Some(&mut err)));
        }
    }
    fclose(in_0);
    if gzclose(out) != 0 as std::os::raw::c_int {
        error(b"failed gzclose\x00" as *const u8 as *const std::os::raw::c_char);
    };
}
/* MMAP version, Miguel Albrecht <malbrech@eso.org> */
/* USE_MMAP */
/* ===========================================================================
 * Uncompress input to output then close both files.
 */
#[no_mangle]
pub unsafe extern "C" fn gz_uncompress(mut in_0: * mut crate::src::zlib::gzclose::gzFile_s, mut out: * mut crate::src::gifread::gifread::_IO_FILE) {
    let mut buf: [i8; 16384] = [0; 16384];
    let mut len: i32 = 0;
    let mut err: i32 = 0;
    loop  {
        len =
            gzread(in_0, buf.as_mut_ptr() as voidp,
                   ::std::mem::size_of::<[std::os::raw::c_char; 16384]>() as
                       std::os::raw::c_ulong as std::os::raw::c_uint);
        if len < 0 as std::os::raw::c_int { error(gzerror(in_0, Some(&mut err))); }
        if len == 0 as std::os::raw::c_int { break ; }
        if fwrite(buf.as_mut_ptr() as *const std::os::raw::c_void,
                  1 as std::os::raw::c_int as std::os::raw::c_ulong,
                  len as std::os::raw::c_uint as std::os::raw::c_ulong, out) as std::os::raw::c_int !=
               len {
            error(b"failed fwrite\x00" as *const u8 as *const std::os::raw::c_char);
        }
    }
    if fclose(out) != 0 {
        error(b"failed fclose\x00" as *const u8 as *const std::os::raw::c_char);
    }
    if gzclose(in_0) != 0 as std::os::raw::c_int {
        error(b"failed gzclose\x00" as *const u8 as *const std::os::raw::c_char);
    };
}
/* ===========================================================================
 * Compress the given file: create a corresponding .gz file and remove the
 * original.
 */
#[no_mangle]
pub unsafe extern "C" fn file_compress(mut file: * mut std::os::raw::c_char,
                                       mut mode: * mut std::os::raw::c_char) {
    let mut outfile: [i8; 1024] = [0; 1024];
    let mut in_0: * mut crate::src::gifread::gifread::_IO_FILE = 0 as *mut FILE;
    let mut out: * mut crate::src::zlib::gzclose::gzFile_s = 0 as *mut gzFile_s;
    if strlen(file).wrapping_add(strlen(b".gz\x00" as *const u8 as
                                            *const std::os::raw::c_char)) >=
           ::std::mem::size_of::<[std::os::raw::c_char; 1024]>() as std::os::raw::c_ulong {
        fprintf(stderr,
                b"%s: filename too long\n\x00" as *const u8 as
                    *const std::os::raw::c_char, prog);
        exit(1 as std::os::raw::c_int);
    }
    snprintf(outfile.as_mut_ptr(),
             ::std::mem::size_of::<[std::os::raw::c_char; 1024]>() as std::os::raw::c_ulong,
             b"%s%s\x00" as *const u8 as *const std::os::raw::c_char, file,
             b".gz\x00" as *const u8 as *const std::os::raw::c_char);
    in_0 = fopen(file, b"rb\x00" as *const u8 as *const std::os::raw::c_char);
    if in_0.is_null() { perror(file); exit(1 as std::os::raw::c_int); }
    out = gzopen(outfile.as_mut_ptr(), mode);
    if out.is_null() {
        fprintf(stderr,
                b"%s: can\'t gzopen %s\n\x00" as *const u8 as
                    *const std::os::raw::c_char, prog, outfile.as_mut_ptr());
        exit(1 as std::os::raw::c_int);
    }
    gz_compress(in_0, out);
    unlink(file);
}
/* ===========================================================================
 * Uncompress the given file and remove the original.
 */
#[no_mangle]
pub unsafe extern "C" fn file_uncompress(mut file: * mut std::os::raw::c_char) {
    let mut buf: [i8; 1024] = [0; 1024];
    let mut infile: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut outfile: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut out: * mut crate::src::gifread::gifread::_IO_FILE = 0 as *mut FILE;
    let mut in_0: * mut crate::src::zlib::gzclose::gzFile_s = 0 as *mut gzFile_s;
    let mut len: u32 = strlen(file) as std::os::raw::c_uint;
    if (len as
            std::os::raw::c_ulong).wrapping_add(strlen(b".gz\x00" as *const u8 as
                                                   *const std::os::raw::c_char)) >=
           ::std::mem::size_of::<[std::os::raw::c_char; 1024]>() as std::os::raw::c_ulong {
        fprintf(stderr,
                b"%s: filename too long\n\x00" as *const u8 as
                    *const std::os::raw::c_char, prog);
        exit(1 as std::os::raw::c_int);
    }
    snprintf(buf.as_mut_ptr(),
             ::std::mem::size_of::<[std::os::raw::c_char; 1024]>() as std::os::raw::c_ulong,
             b"%s\x00" as *const u8 as *const std::os::raw::c_char, file);
    if len as std::os::raw::c_ulong >
           (::std::mem::size_of::<[std::os::raw::c_char; 4]>() as
                std::os::raw::c_ulong).wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
           &&
           strcmp(file.offset(len as
                                  isize).offset(-((::std::mem::size_of::<[std::os::raw::c_char; 4]>()
                                                       as
                                                       std::os::raw::c_ulong).wrapping_sub(1
                                                                                       as
                                                                                       std::os::raw::c_int
                                                                                       as
                                                                                       std::os::raw::c_ulong)
                                                      as isize)),
                  b".gz\x00" as *const u8 as *const std::os::raw::c_char) ==
               0 as std::os::raw::c_int {
        infile = file;
        outfile = buf.as_mut_ptr();
        *outfile.offset(len.wrapping_sub(3 as std::os::raw::c_int as std::os::raw::c_uint) as
                            isize) = '\u{0}' as i32 as std::os::raw::c_char
    } else {
        outfile = file;
        infile = buf.as_mut_ptr();
        snprintf(buf.as_mut_ptr().offset(len as isize),
                 (::std::mem::size_of::<[std::os::raw::c_char; 1024]>() as
                      std::os::raw::c_ulong).wrapping_sub(len as std::os::raw::c_ulong),
                 b"%s\x00" as *const u8 as *const std::os::raw::c_char,
                 b".gz\x00" as *const u8 as *const std::os::raw::c_char);
    }
    in_0 = gzopen(infile, b"rb\x00" as *const u8 as *const std::os::raw::c_char);
    if in_0.is_null() {
        fprintf(stderr,
                b"%s: can\'t gzopen %s\n\x00" as *const u8 as
                    *const std::os::raw::c_char, prog, infile);
        exit(1 as std::os::raw::c_int);
    }
    out = fopen(outfile, b"wb\x00" as *const u8 as *const std::os::raw::c_char);
    if out.is_null() { perror(file); exit(1 as std::os::raw::c_int); }
    gz_uncompress(in_0, out);
    unlink(infile);
}
/* ===========================================================================
 * Usage:  minigzip [-c] [-d] [-f] [-h] [-r] [-1 to -9] [files...]
 *   -c : write to standard output
 *   -d : decompress
 *   -f : compress with Z_FILTERED
 *   -h : compress with Z_HUFFMAN_ONLY
 *   -r : compress with Z_RLE
 *   -1 to -9 : compression level
 */
unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: * mut * mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut copyout: i32 = 0 as std::os::raw::c_int;
    let mut uncompr: i32 = 0 as std::os::raw::c_int;
    let mut file: * mut crate::src::zlib::gzclose::gzFile_s = 0 as *mut gzFile_s;
    let mut bname: * mut i8 = 0 as *mut std::os::raw::c_char;
    let mut outmode: [i8; 20] = [0; 20];
    snprintf(outmode.as_mut_ptr(),
             ::std::mem::size_of::<[std::os::raw::c_char; 20]>() as std::os::raw::c_ulong,
             b"%s\x00" as *const u8 as *const std::os::raw::c_char,
             b"wb6 \x00" as *const u8 as *const std::os::raw::c_char);
    prog = *argv.offset(0 as std::os::raw::c_int as isize);
    bname = strrchr(*argv.offset(0 as std::os::raw::c_int as isize), '/' as i32);
    if !bname.is_null() {
        bname = bname.offset(1)
    } else { bname = *argv.offset(0 as std::os::raw::c_int as isize) }
    argc -= 1;
    argv = argv.offset(1);
    if strcmp(bname, b"gunzip\x00" as *const u8 as *const std::os::raw::c_char) == 0 {
        uncompr = 1 as std::os::raw::c_int
    } else if strcmp(bname, b"zcat\x00" as *const u8 as *const std::os::raw::c_char)
                  == 0 {
        uncompr = 1 as std::os::raw::c_int;
        copyout = uncompr
    }
    while argc > 0 as std::os::raw::c_int {
        if strcmp(*argv, b"-c\x00" as *const u8 as *const std::os::raw::c_char) ==
               0 as std::os::raw::c_int {
            copyout = 1 as std::os::raw::c_int
        } else if strcmp(*argv, b"-d\x00" as *const u8 as *const std::os::raw::c_char)
                      == 0 as std::os::raw::c_int {
            uncompr = 1 as std::os::raw::c_int
        } else if strcmp(*argv, b"-f\x00" as *const u8 as *const std::os::raw::c_char)
                      == 0 as std::os::raw::c_int {
            outmode[3 as std::os::raw::c_int as usize] = 'f' as i32 as std::os::raw::c_char
        } else if strcmp(*argv, b"-h\x00" as *const u8 as *const std::os::raw::c_char)
                      == 0 as std::os::raw::c_int {
            outmode[3 as std::os::raw::c_int as usize] = 'h' as i32 as std::os::raw::c_char
        } else if strcmp(*argv, b"-r\x00" as *const u8 as *const std::os::raw::c_char)
                      == 0 as std::os::raw::c_int {
            outmode[3 as std::os::raw::c_int as usize] = 'R' as i32 as std::os::raw::c_char
        } else {
            if !(*(*argv).offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int ==
                     '-' as i32 &&
                     *(*argv).offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int
                         >= '1' as i32 &&
                     *(*argv).offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int
                         <= '9' as i32 &&
                     *(*argv).offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int
                         == 0 as std::os::raw::c_int) {
                break ;
            }
            outmode[2 as std::os::raw::c_int as usize] =
                *(*argv).offset(1 as std::os::raw::c_int as isize)
        }
        argc -= 1;
        argv = argv.offset(1)
    }
    if outmode[3 as std::os::raw::c_int as usize] as std::os::raw::c_int == ' ' as i32 {
        outmode[3 as std::os::raw::c_int as usize] = 0 as std::os::raw::c_int as std::os::raw::c_char
    }
    if argc == 0 as std::os::raw::c_int {
        if uncompr != 0 {
            file =
                gzdopen(fileno(stdin),
                        b"rb\x00" as *const u8 as *const std::os::raw::c_char);
            if file.is_null() {
                error(b"can\'t gzdopen stdin\x00" as *const u8 as
                          *const std::os::raw::c_char);
            }
            gz_uncompress(file, stdout);
        } else {
            file = gzdopen(fileno(stdout), outmode.as_mut_ptr());
            if file.is_null() {
                error(b"can\'t gzdopen stdout\x00" as *const u8 as
                          *const std::os::raw::c_char);
            }
            gz_compress(stdin, file);
        }
    } else {
        (copyout) != 0;
        loop  {
            if uncompr != 0 {
                if copyout != 0 {
                    file =
                        gzopen(*argv,
                               b"rb\x00" as *const u8 as *const std::os::raw::c_char);
                    if file.is_null() {
                        fprintf(stderr,
                                b"%s: can\'t gzopen %s\n\x00" as *const u8 as
                                    *const std::os::raw::c_char, prog, *argv);
                    } else { gz_uncompress(file, stdout); }
                } else { file_uncompress(*argv); }
            } else if copyout != 0 {
                let mut in_0: * mut crate::src::gifread::gifread::_IO_FILE =
                    fopen(*argv,
                          b"rb\x00" as *const u8 as *const std::os::raw::c_char);
                if in_0.is_null() {
                    perror(*argv);
                } else {
                    file = gzdopen(fileno(stdout), outmode.as_mut_ptr());
                    if file.is_null() {
                        error(b"can\'t gzdopen stdout\x00" as *const u8 as
                                  *const std::os::raw::c_char);
                    }
                    gz_compress(in_0, file);
                }
            } else { file_compress(*argv, outmode.as_mut_ptr()); }
            argv = argv.offset(1);
            argc -= 1;
            if !(argc != 0) { break ; }
        }
    }
    return 0 as std::os::raw::c_int;
}
pub fn main() {
    let mut args: Vec<*mut std::os::raw::c_char> = Vec::new();
    for arg in ::std::env::args() {
        args.push(::std::ffi::CString::new(arg).expect("Failed to convert argument into CString.").into_raw());
    };
    args.push(::std::ptr::null_mut());
    unsafe {
        ::std::process::exit(main_0((args.len() - 1) as std::os::raw::c_int,
                                    args.as_mut_ptr() as
                                        *mut *mut std::os::raw::c_char) as i32)
    }
}
use crate::laertes_rt::*;
