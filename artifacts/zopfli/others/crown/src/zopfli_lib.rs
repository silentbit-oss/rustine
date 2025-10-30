use ::libc;
extern "C" {
    
    
    
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor24 { dummy: () }
pub type ZopfliFormat = libc::c_uint;
pub const ZOPFLI_FORMAT_DEFLATE: ZopfliFormat = 2;
pub const ZOPFLI_FORMAT_ZLIB: ZopfliFormat = 1;
pub const ZOPFLI_FORMAT_GZIP: ZopfliFormat = 0;
#[no_mangle]
pub unsafe extern "C" fn ZopfliCompress(
    mut options: *const crate::src::blocksplitter::ZopfliOptions,
    mut output_type: ZopfliFormat,
    mut in_0: *const libc::c_uchar,
    mut insize: size_t,
    mut out: *mut *mut libc::c_uchar,
    mut outsize: *mut size_t,
) {
    if output_type as libc::c_uint == ZOPFLI_FORMAT_GZIP as libc::c_int as libc::c_uint {
        crate::src::gzip_container::ZopfliGzipCompress(options, in_0, insize, out, outsize);
    } else if output_type as libc::c_uint
        == ZOPFLI_FORMAT_ZLIB as libc::c_int as libc::c_uint
    {
        crate::src::zlib_container::ZopfliZlibCompress(options, in_0, insize, out, outsize);
    } else if output_type as libc::c_uint
        == ZOPFLI_FORMAT_DEFLATE as libc::c_int as libc::c_uint
    {
        let mut bp: libc::c_uchar = 0 as libc::c_int as libc::c_uchar;
        crate::src::deflate::ZopfliDeflate(
            options,
            2 as libc::c_int,
            1 as libc::c_int,
            in_0,
            insize,
            &raw mut bp,
            out,
            outsize,
        );
    } else {
        if 0 as libc::c_int != 0 {} else {
            __assert_fail(
                b"0\0" as *const u8 as *const libc::c_char,
                b"src/zopfli/zopfli_lib.c\0" as *const u8 as *const libc::c_char,
                40 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 116],
                    &[libc::c_char; 116],
                >(
                    b"void ZopfliCompress(const ZopfliOptions *, ZopfliFormat, const unsigned char *, size_t, unsigned char **, size_t *)\0",
                ))
                    .as_ptr(),
            );
        };
    };
}
