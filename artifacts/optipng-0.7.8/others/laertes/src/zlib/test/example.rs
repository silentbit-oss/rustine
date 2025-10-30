
extern "C" {
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    #[no_mangle]
    static mut stderr: * mut crate::src::gifread::gifread::_IO_FILE;
    #[no_mangle]
    fn fprintf(_: * mut crate::src::gifread::gifread::_IO_FILE, _: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn printf(_: * const std::os::raw::c_char, _: ...) -> std::os::raw::c_int;
    #[no_mangle]
    fn strcmp(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char) -> std::os::raw::c_int;
    #[no_mangle]
    fn strcpy(_: * mut std::os::raw::c_char, _: * const std::os::raw::c_char)
     -> * mut std::os::raw::c_char;
    #[no_mangle]
    fn strlen(_: * const std::os::raw::c_char) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn calloc(_: std::os::raw::c_ulong, _: std::os::raw::c_ulong) -> * mut core::ffi::c_void;
    #[no_mangle]
    fn free(__ptr: * mut core::ffi::c_void);
    #[no_mangle]
    fn exit(_: std::os::raw::c_int) -> !;
}
pub use crate::src::zlib::compress::compress;
pub use crate::src::zlib::deflate::deflate;
pub use crate::src::zlib::deflate::deflateEnd;
pub use crate::src::zlib::deflate::deflateInit_;
pub use crate::src::zlib::deflate::deflateParams;
pub use crate::src::zlib::deflate::deflateSetDictionary;
pub use crate::src::zlib::inflate::inflate;
pub use crate::src::zlib::inflate::inflateEnd;
pub use crate::src::zlib::inflate::inflateInit_;
pub use crate::src::zlib::inflate::inflateSetDictionary;
pub use crate::src::zlib::inflate::inflateSync;
pub use crate::src::zlib::uncompr::uncompress;
pub use crate::src::zlib::zutil::zlibCompileFlags;
pub use crate::src::zlib::zutil::zlibVersion;
pub use crate::src::zlib::deflate::internal_state;
pub use crate::src::pngxtern::pngxread::_IO_marker;
pub use crate::src::pngxtern::pngxrpnm::_IO_wide_data;
pub use crate::src::pnmio::pnmout::_IO_codecvt;
pub type size_t = std::os::raw::c_ulong;
pub type Byte = std::os::raw::c_uchar;
pub type uInt = std::os::raw::c_uint;
pub type uLong = std::os::raw::c_ulong;
pub type Bytef = std::os::raw::c_uchar;
pub type uLongf = std::os::raw::c_ulong;
pub type voidpf = * mut core::ffi::c_void;
pub type __off_t = std::os::raw::c_long;
pub type __off64_t = std::os::raw::c_long;
pub type alloc_func<'a1, 'a2> = Option<unsafe extern "C"  fn(_: Option<&'a1 mut core::ffi::c_void>,_: std::os::raw::c_uint,_: std::os::raw::c_uint,) -> Option<&'a2 mut core::ffi::c_void>>;
pub type free_func<'a1, 'a2> = Option<unsafe extern "C"  fn(_: Option<&'a1 mut core::ffi::c_void>,_: Option<&'a2 mut core::ffi::c_void>,) -> ()>;
// #[derive(Copy, Clone)]

pub type z_stream_s<'a> = crate::src::zlib::compress::z_stream_s<'a>;
pub type z_stream = crate::src::libpng::png::z_stream_s;
pub type z_streamp = * mut crate::src::libpng::png::z_stream_s;
// #[derive(Copy, Clone)]

pub type _IO_FILE = crate::src::gifread::gifread::_IO_FILE;
pub type _IO_lock_t = ();
pub type FILE = crate::src::gifread::gifread::_IO_FILE;
static mut hello: [std::os::raw::c_char; 14] =
    [0,0,0,0,0,0,0,0,0,0,0,0,0,0,]; unsafe fn laertes_init_hello() {
hello = unsafe {
        *core::intrinsics::transmute::<&'_ [u8; 14], &'_ mut [i8; 14]>(b"hello, hello!\x00")
    };}//;
/* "hello world" would be more standard, but the repeated "hello"
 * stresses the compression code better, sorry...
 */
static mut dictionary: [std::os::raw::c_char; 6] =
    [0,0,0,0,0,0,]; unsafe fn laertes_init_dictionary() {
dictionary = unsafe {
        *core::intrinsics::transmute::<&'_ [u8; 6], &'_ [i8; 6]>(b"hello\x00")
    };}//;
static mut dictId: std::os::raw::c_ulong = 0; unsafe fn laertes_init_dictId() {
dictId = 0;}//;
/* !Z_SOLO */
static mut zalloc: Option<unsafe extern "C"  fn(_: * mut core::ffi::c_void,_: std::os::raw::c_uint,_: std::os::raw::c_uint,) -> * mut core::ffi::c_void> = None; unsafe fn laertes_init_zalloc() {
zalloc = None;}//;
static mut zfree: Option<unsafe extern "C"  fn(_: * mut core::ffi::c_void,_: * mut core::ffi::c_void,) -> ()> = None; unsafe fn laertes_init_zfree() {
zfree = None;}//;
/* ===========================================================================
 * Test compress() and uncompress()
 */
#[no_mangle]
pub unsafe extern "C" fn test_compress(mut compr: * mut std::os::raw::c_uchar,
                                       mut comprLen: std::os::raw::c_ulong,
                                       mut uncompr: * mut std::os::raw::c_uchar,
                                       mut uncomprLen: std::os::raw::c_ulong) {
    let mut err: i32 = 0;
    let mut len: u64 =
        strlen(hello.as_mut_ptr()).wrapping_add(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong);
    err =
        compress(compr, &mut comprLen, hello.as_mut_ptr() as *const Bytef,
                 len);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"compress\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    strcpy(uncompr as *mut std::os::raw::c_char,
           b"garbage\x00" as *const u8 as *const std::os::raw::c_char);
    err = uncompress(uncompr, &mut uncomprLen, compr, comprLen);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"uncompress\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    if strcmp(uncompr as *mut std::os::raw::c_char, hello.as_mut_ptr()) != 0 {
        fprintf(stderr,
                b"bad uncompress\n\x00" as *const u8 as *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    } else {
        printf(b"uncompress(): %s\n\x00" as *const u8 as *const std::os::raw::c_char,
               uncompr as *mut std::os::raw::c_char);
    };
}
/* ===========================================================================
 * Test read/write of .gz files
 */
#[no_mangle]
pub unsafe extern "C" fn test_gzio(mut fname: * const std::os::raw::c_char,
                                   mut uncompr: * mut std::os::raw::c_uchar,
                                   mut uncomprLen: std::os::raw::c_ulong) {
    fprintf(stderr,
            b"NO_GZCOMPRESS -- gz* functions cannot compress\n\x00" as
                *const u8 as *const std::os::raw::c_char);
}
/* Adler32 value of the dictionary */
/* Z_SOLO */
/* ===========================================================================
 * Test deflate() with small buffers
 */
#[no_mangle]
pub unsafe extern "C" fn test_deflate(mut compr: * mut std::os::raw::c_uchar,
                                      mut comprLen: std::os::raw::c_ulong) {
    let mut c_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* compression stream */
    let mut err: i32 = 0; /* force small buffers */
    let mut len: u64 =
        strlen(hello.as_mut_ptr()).wrapping_add(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong);
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err =
        deflateInit_(&mut c_stream, -(1 as std::os::raw::c_int),
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    c_stream.next_in = hello.as_mut_ptr() as *mut std::os::raw::c_uchar;
    c_stream.next_out = compr;
    while c_stream.total_in != len && c_stream.total_out < comprLen {
        c_stream.avail_out = 1 as std::os::raw::c_int as uInt;
        c_stream.avail_in = c_stream.avail_out;
        err = deflate(&mut c_stream, 0 as std::os::raw::c_int);
        if err != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                    b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
            exit(1 as std::os::raw::c_int);
        }
    }
    loop 
         /* Finish the stream, still forcing small buffers: */
         {
        c_stream.avail_out = 1 as std::os::raw::c_int as uInt;
        err = deflate(&mut c_stream, 4 as std::os::raw::c_int);
        if err == 1 as std::os::raw::c_int { break ; }
        if err != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                    b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
            exit(1 as std::os::raw::c_int);
        }
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    };
}
/* ===========================================================================
 * Test inflate() with small buffers
 */
#[no_mangle]
pub unsafe extern "C" fn test_inflate(mut compr: * mut std::os::raw::c_uchar,
                                      mut comprLen: std::os::raw::c_ulong,
                                      mut uncompr: * mut std::os::raw::c_uchar,
                                      mut uncomprLen: std::os::raw::c_ulong) {
    let mut err: i32 = 0; /* decompression stream */
    let mut d_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* force small buffers */
    strcpy(uncompr as *mut std::os::raw::c_char,
           b"garbage\x00" as *const u8 as *const std::os::raw::c_char);
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = 0 as std::os::raw::c_int as uInt;
    d_stream.next_out = uncompr;
    err =
        inflateInit_(&mut d_stream,
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    while d_stream.total_out < uncomprLen && d_stream.total_in < comprLen {
        d_stream.avail_out = 1 as std::os::raw::c_int as uInt;
        d_stream.avail_in = d_stream.avail_out;
        err = inflate(&mut d_stream, 0 as std::os::raw::c_int);
        if err == 1 as std::os::raw::c_int { break ; }
        if err != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                    b"inflate\x00" as *const u8 as *const std::os::raw::c_char, err);
            exit(1 as std::os::raw::c_int);
        }
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    if strcmp(uncompr as *mut std::os::raw::c_char, hello.as_mut_ptr()) != 0 {
        fprintf(stderr,
                b"bad inflate\n\x00" as *const u8 as *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    } else {
        printf(b"inflate(): %s\n\x00" as *const u8 as *const std::os::raw::c_char,
               uncompr as *mut std::os::raw::c_char);
    };
}
/* ===========================================================================
 * Test deflate() with large buffers and dynamic change of compression level
 */
#[no_mangle]
pub unsafe extern "C" fn test_large_deflate(mut compr: * mut std::os::raw::c_uchar,
                                            mut comprLen: std::os::raw::c_ulong,
                                            mut uncompr: * mut std::os::raw::c_uchar,
                                            mut uncomprLen: std::os::raw::c_ulong) {
    let mut c_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* compression stream */
    let mut err: i32 = 0;
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err =
        deflateInit_(&mut c_stream, 1 as std::os::raw::c_int,
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    c_stream.next_out = compr;
    c_stream.avail_out = comprLen as uInt;
    /* At this point, uncompr is still mostly zeroes, so it should compress
     * very well:
     */
    c_stream.next_in = uncompr;
    c_stream.avail_in = uncomprLen as uInt;
    err = deflate(&mut c_stream, 0 as std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    if c_stream.avail_in != 0 as std::os::raw::c_int as std::os::raw::c_uint {
        fprintf(stderr,
                b"deflate not greedy\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    }
    /* Feed in already compressed data and switch to no compression: */
    deflateParams(&mut c_stream, 0 as std::os::raw::c_int, 0 as std::os::raw::c_int);
    c_stream.next_in = compr;
    c_stream.avail_in =
        (comprLen as uInt).wrapping_div(2 as std::os::raw::c_int as std::os::raw::c_uint);
    err = deflate(&mut c_stream, 0 as std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    /* Switch back to compressing mode: */
    deflateParams(&mut c_stream, 9 as std::os::raw::c_int, 1 as std::os::raw::c_int);
    c_stream.next_in = uncompr;
    c_stream.avail_in = uncomprLen as uInt;
    err = deflate(&mut c_stream, 0 as std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    err = deflate(&mut c_stream, 4 as std::os::raw::c_int);
    if err != 1 as std::os::raw::c_int {
        fprintf(stderr,
                b"deflate should report Z_STREAM_END\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    };
}
/* ===========================================================================
 * Test inflate() with large buffers
 */
#[no_mangle]
pub unsafe extern "C" fn test_large_inflate(mut compr: * mut std::os::raw::c_uchar,
                                            mut comprLen: std::os::raw::c_ulong,
                                            mut uncompr: * mut std::os::raw::c_uchar,
                                            mut uncomprLen: std::os::raw::c_ulong) {
    let mut err: i32 = 0; /* decompression stream */
    let mut d_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* discard the output */
    strcpy(uncompr as *mut std::os::raw::c_char,
           b"garbage\x00" as *const u8 as *const std::os::raw::c_char);
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = comprLen as uInt;
    err =
        inflateInit_(&mut d_stream,
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    loop  {
        d_stream.next_out = uncompr;
        d_stream.avail_out = uncomprLen as uInt;
        err = inflate(&mut d_stream, 0 as std::os::raw::c_int);
        if err == 1 as std::os::raw::c_int { break ; }
        if err != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                    b"large inflate\x00" as *const u8 as *const std::os::raw::c_char,
                    err);
            exit(1 as std::os::raw::c_int);
        }
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    if d_stream.total_out !=
           (2 as std::os::raw::c_int as
                std::os::raw::c_ulong).wrapping_mul(uncomprLen).wrapping_add(comprLen.wrapping_div(2
                                                                                               as
                                                                                               std::os::raw::c_int
                                                                                               as
                                                                                               std::os::raw::c_ulong))
       {
        fprintf(stderr,
                b"bad large inflate: %ld\n\x00" as *const u8 as
                    *const std::os::raw::c_char, d_stream.total_out);
        exit(1 as std::os::raw::c_int);
    } else {
        printf(b"large_inflate(): OK\n\x00" as *const u8 as
                   *const std::os::raw::c_char);
    };
}
/* ===========================================================================
 * Test deflate() with full flush
 */
#[no_mangle]
pub unsafe extern "C" fn test_flush<'a1>(mut compr: * mut std::os::raw::c_uchar,
                                    mut comprLen: Option<&'a1 mut std::os::raw::c_ulong>) {
    let mut c_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* compression stream */
    let mut err: i32 =
        0; /* force an error in first compressed block */
    let mut len: u32 =
        (strlen(hello.as_mut_ptr()) as
             uInt).wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_uint);
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err =
        deflateInit_(&mut c_stream, -(1 as std::os::raw::c_int),
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    c_stream.next_in = hello.as_mut_ptr() as *mut std::os::raw::c_uchar;
    c_stream.next_out = compr;
    c_stream.avail_in = 3 as std::os::raw::c_int as uInt;
    c_stream.avail_out = *(borrow_mut(&mut comprLen)).unwrap() as uInt;
    err = deflate(&mut c_stream, 3 as std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    let ref mut fresh0 = *compr.offset(3 as std::os::raw::c_int as isize);
    *fresh0 = (*fresh0).wrapping_add(1);
    c_stream.avail_in = len.wrapping_sub(3 as std::os::raw::c_int as std::os::raw::c_uint);
    err = deflate(&mut c_stream, 4 as std::os::raw::c_int);
    if err != 1 as std::os::raw::c_int {
        if err != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                    b"deflate\x00" as *const u8 as *const std::os::raw::c_char, err);
            exit(1 as std::os::raw::c_int);
        }
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    *(borrow_mut(&mut comprLen)).unwrap() = c_stream.total_out;
}
/* ===========================================================================
 * Test inflateSync()
 */
#[no_mangle]
pub unsafe extern "C" fn test_sync(mut compr: * mut std::os::raw::c_uchar, mut comprLen: std::os::raw::c_ulong,
                                   mut uncompr: * mut std::os::raw::c_uchar,
                                   mut uncomprLen: std::os::raw::c_ulong) {
    let mut err: i32 = 0; /* decompression stream */
    let mut d_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* just read the zlib header */
    strcpy(uncompr as *mut std::os::raw::c_char,
           b"garbage\x00" as *const u8 as
               *const std::os::raw::c_char); /* read all compressed data */
    d_stream.zalloc = zalloc; /* but skip the damaged part */
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = 2 as std::os::raw::c_int as uInt;
    err =
        inflateInit_(&mut d_stream,
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    d_stream.next_out = uncompr;
    d_stream.avail_out = uncomprLen as uInt;
    err = inflate(&mut d_stream, 0 as std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflate\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    d_stream.avail_in =
        (comprLen as uInt).wrapping_sub(2 as std::os::raw::c_int as std::os::raw::c_uint);
    err = inflateSync(&mut d_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateSync\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    err = inflate(&mut d_stream, 4 as std::os::raw::c_int);
    if err != -(3 as std::os::raw::c_int) {
        fprintf(stderr,
                b"inflate should report DATA_ERROR\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        /* Because of incorrect adler32 */
        exit(1 as std::os::raw::c_int);
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    printf(b"after inflateSync(): hel%s\n\x00" as *const u8 as
               *const std::os::raw::c_char, uncompr as *mut std::os::raw::c_char);
}
/* ===========================================================================
 * Test deflate() with preset dictionary
 */
#[no_mangle]
pub unsafe extern "C" fn test_dict_deflate(mut compr: * mut std::os::raw::c_uchar,
                                           mut comprLen: std::os::raw::c_ulong) {
    let mut c_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,}; /* compression stream */
    let mut err: i32 = 0;
    c_stream.zalloc = zalloc;
    c_stream.zfree = zfree;
    c_stream.opaque = 0 as voidpf;
    err =
        deflateInit_(&mut c_stream, 9 as std::os::raw::c_int,
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    err =
        deflateSetDictionary(&mut c_stream,
                             dictionary.as_ptr() as *const Bytef,
                             ::std::mem::size_of::<[std::os::raw::c_char; 6]>() as
                                 std::os::raw::c_ulong as std::os::raw::c_int as uInt);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateSetDictionary\x00" as *const u8 as
                    *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    dictId = c_stream.adler;
    c_stream.next_out = compr;
    c_stream.avail_out = comprLen as uInt;
    c_stream.next_in = hello.as_mut_ptr() as *mut std::os::raw::c_uchar;
    c_stream.avail_in =
        (strlen(hello.as_mut_ptr()) as
             uInt).wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_uint);
    err = deflate(&mut c_stream, 4 as std::os::raw::c_int);
    if err != 1 as std::os::raw::c_int {
        fprintf(stderr,
                b"deflate should report Z_STREAM_END\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    }
    err = deflateEnd(&mut c_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"deflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    };
}
/* ===========================================================================
 * Test inflate() with a preset dictionary
 */
#[no_mangle]
pub unsafe extern "C" fn test_dict_inflate(mut compr: * mut std::os::raw::c_uchar,
                                           mut comprLen: std::os::raw::c_ulong,
                                           mut uncompr: * mut std::os::raw::c_uchar,
                                           mut uncomprLen: std::os::raw::c_ulong) {
    let mut err: i32 = 0; /* decompression stream */
    let mut d_stream: crate::src::libpng::png::z_stream_s =
        z_stream{next_in: 0 as *mut Bytef,
                 avail_in: 0,
                 total_in: 0,
                 next_out: 0 as *mut Bytef,
                 avail_out: 0,
                 total_out: 0,
                 msg: 0 as *mut std::os::raw::c_char,
                 state: 0 as *mut internal_state,
                 zalloc: None,
                 zfree: None,
                 opaque: 0 as *mut std::os::raw::c_void,
                 data_type: 0,
                 adler: 0,
                 reserved: 0,};
    strcpy(uncompr as *mut std::os::raw::c_char,
           b"garbage\x00" as *const u8 as *const std::os::raw::c_char);
    d_stream.zalloc = zalloc;
    d_stream.zfree = zfree;
    d_stream.opaque = 0 as voidpf;
    d_stream.next_in = compr;
    d_stream.avail_in = comprLen as uInt;
    err =
        inflateInit_(&mut d_stream,
                     b"1.2.11-optipng\x00" as *const u8 as
                         *const std::os::raw::c_char,
                     ::std::mem::size_of::<z_stream>() as std::os::raw::c_ulong as
                         std::os::raw::c_int);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateInit\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    d_stream.next_out = uncompr;
    d_stream.avail_out = uncomprLen as uInt;
    loop  {
        err = inflate(&mut d_stream, 0 as std::os::raw::c_int);
        if err == 1 as std::os::raw::c_int { break ; }
        if err == 2 as std::os::raw::c_int {
            if d_stream.adler != dictId {
                fprintf(stderr,
                        b"unexpected dictionary\x00" as *const u8 as
                            *const std::os::raw::c_char);
                exit(1 as std::os::raw::c_int);
            }
            err =
                inflateSetDictionary(&mut d_stream,
                                     dictionary.as_ptr() as *const Bytef,
                                     ::std::mem::size_of::<[std::os::raw::c_char; 6]>()
                                         as std::os::raw::c_ulong as std::os::raw::c_int as
                                         uInt)
        }
        if err != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                    b"inflate with dict\x00" as *const u8 as
                        *const std::os::raw::c_char, err);
            exit(1 as std::os::raw::c_int);
        }
    }
    err = inflateEnd(&mut d_stream);
    if err != 0 as std::os::raw::c_int {
        fprintf(stderr,
                b"%s error: %d\n\x00" as *const u8 as *const std::os::raw::c_char,
                b"inflateEnd\x00" as *const u8 as *const std::os::raw::c_char, err);
        exit(1 as std::os::raw::c_int);
    }
    if strcmp(uncompr as *mut std::os::raw::c_char, hello.as_mut_ptr()) != 0 {
        fprintf(stderr,
                b"bad inflate with dict\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    } else {
        printf(b"inflate with dictionary: %s\n\x00" as *const u8 as
                   *const std::os::raw::c_char, uncompr as *mut std::os::raw::c_char);
    };
}
/* ===========================================================================
 * Usage:  example [output.gz  [input.gz]]
 */
unsafe fn main_0(mut argc: std::os::raw::c_int, mut argv: * mut * mut std::os::raw::c_char)
 -> std::os::raw::c_int {
    let mut compr: * mut u8 = 0 as *mut Byte; /* don't overflow on MSDOS */
    let mut uncompr: * mut u8 = 0 as *mut Byte;
    let mut comprLen: u64 =
        (10000 as std::os::raw::c_int as
             std::os::raw::c_ulong).wrapping_mul(::std::mem::size_of::<std::os::raw::c_int>()
                                             as std::os::raw::c_ulong);
    let mut uncomprLen: u64 = comprLen;
    static mut myVersion: * const std::os::raw::c_char =
        (0 as * const std::os::raw::c_char); unsafe fn laertes_init_myVersion() {
myVersion = b"1.2.11-optipng\x00" as *const u8 as *const std::os::raw::c_char;}//;
    if *zlibVersion().offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
           *myVersion.offset(0 as std::os::raw::c_int as isize) as std::os::raw::c_int {
        fprintf(stderr,
                b"incompatible zlib version\n\x00" as *const u8 as
                    *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    } else {
        if strcmp(zlibVersion(),
                  b"1.2.11-optipng\x00" as *const u8 as *const std::os::raw::c_char)
               != 0 as std::os::raw::c_int {
            fprintf(stderr,
                    b"warning: different zlib version\n\x00" as *const u8 as
                        *const std::os::raw::c_char);
        }
    }
    printf(b"zlib version %s = 0x%04x, compile flags = 0x%lx\n\x00" as
               *const u8 as *const std::os::raw::c_char,
           b"1.2.11-optipng\x00" as *const u8 as *const std::os::raw::c_char,
           0x12bf as std::os::raw::c_int, zlibCompileFlags());
    compr =
        calloc(comprLen as uInt as std::os::raw::c_ulong,
               1 as std::os::raw::c_int as std::os::raw::c_ulong) as *mut Byte;
    uncompr =
        calloc(uncomprLen as uInt as std::os::raw::c_ulong,
               1 as std::os::raw::c_int as std::os::raw::c_ulong) as *mut Byte;
    /* compr and uncompr are cleared to avoid reading uninitialized
     * data and to ensure that uncompr compresses well.
     */
    if compr.is_null() || uncompr.is_null() {
        printf(b"out of memory\n\x00" as *const u8 as *const std::os::raw::c_char);
        exit(1 as std::os::raw::c_int);
    }
    test_compress(compr, comprLen, uncompr, uncomprLen);
    test_gzio(if argc > 1 as std::os::raw::c_int {
                  *argv.offset(1 as std::os::raw::c_int as isize) as
                      *const std::os::raw::c_char
              } else { b"foo.gz\x00" as *const u8 as *const std::os::raw::c_char },
              uncompr, uncomprLen);
    test_deflate(compr, comprLen);
    test_inflate(compr, comprLen, uncompr, uncomprLen);
    test_large_deflate(compr, comprLen, uncompr, uncomprLen);
    test_large_inflate(compr, comprLen, uncompr, uncomprLen);
    test_flush(compr, Some(&mut comprLen));
    test_sync(compr, comprLen, uncompr, uncomprLen);
    comprLen = uncomprLen;
    test_dict_deflate(compr, comprLen);
    test_dict_inflate(compr, comprLen, uncompr, uncomprLen);
    free(compr as *mut std::os::raw::c_void);
    free(uncompr as *mut std::os::raw::c_void);
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
