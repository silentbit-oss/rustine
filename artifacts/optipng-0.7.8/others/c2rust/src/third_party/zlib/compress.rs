use ::libc;
extern "C" {
    pub type internal_state;
    fn deflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn deflateEnd(strm: z_streamp) -> libc::c_int;
    fn deflateInit_(
        strm: z_streamp,
        level: libc::c_int,
        version: *const libc::c_char,
        stream_size: libc::c_int,
    ) -> libc::c_int;
}
pub type Byte = libc::c_uchar;
pub type uInt = libc::c_uint;
pub type uLong = libc::c_ulong;
pub type Bytef = Byte;
pub type uLongf = uLong;
pub type voidpf = *mut libc::c_void;
pub type alloc_func = Option::<unsafe extern "C" fn(voidpf, uInt, uInt) -> voidpf>;
pub type free_func = Option::<unsafe extern "C" fn(voidpf, voidpf) -> ()>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct z_stream_s {
    pub next_in: *const Bytef,
    pub avail_in: uInt,
    pub total_in: uLong,
    pub next_out: *mut Bytef,
    pub avail_out: uInt,
    pub total_out: uLong,
    pub msg: *const libc::c_char,
    pub state: *mut internal_state,
    pub zalloc: alloc_func,
    pub zfree: free_func,
    pub opaque: voidpf,
    pub data_type: libc::c_int,
    pub adler: uLong,
    pub reserved: uLong,
}
pub type z_stream = z_stream_s;
pub type z_streamp = *mut z_stream;
#[no_mangle]
pub unsafe extern "C" fn compress2(
    mut dest: *mut Bytef,
    mut destLen: *mut uLongf,
    mut source: *const Bytef,
    mut sourceLen: uLong,
    mut level: libc::c_int,
) -> libc::c_int {
    let mut stream: z_stream = z_stream_s {
        next_in: 0 as *const Bytef,
        avail_in: 0,
        total_in: 0,
        next_out: 0 as *mut Bytef,
        avail_out: 0,
        total_out: 0,
        msg: 0 as *const libc::c_char,
        state: 0 as *mut internal_state,
        zalloc: None,
        zfree: None,
        opaque: 0 as *mut libc::c_void,
        data_type: 0,
        adler: 0,
        reserved: 0,
    };
    let mut err: libc::c_int = 0;
    let max: uInt = -(1 as libc::c_int) as uInt;
    let mut left: uLong = 0;
    left = *destLen;
    *destLen = 0 as libc::c_int as uLongf;
    stream.zalloc = None;
    stream.zfree = None;
    stream.opaque = 0 as voidpf;
    err = deflateInit_(
        &mut stream,
        level,
        b"1.3-optipng\0" as *const u8 as *const libc::c_char,
        ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
    );
    if err != 0 as libc::c_int {
        return err;
    }
    stream.next_out = dest;
    stream.avail_out = 0 as libc::c_int as uInt;
    stream.next_in = source;
    stream.avail_in = 0 as libc::c_int as uInt;
    loop {
        if stream.avail_out == 0 as libc::c_int as uInt {
            stream.avail_out = if left > max as uLong { max } else { left as uInt };
            left = left.wrapping_sub(stream.avail_out as uLong);
        }
        if stream.avail_in == 0 as libc::c_int as uInt {
            stream
                .avail_in = if sourceLen > max as uLong {
                max
            } else {
                sourceLen as uInt
            };
            sourceLen = sourceLen.wrapping_sub(stream.avail_in as uLong);
        }
        err = deflate(
            &mut stream,
            if sourceLen != 0 { 0 as libc::c_int } else { 4 as libc::c_int },
        );
        if !(err == 0 as libc::c_int) {
            break;
        }
    }
    *destLen = stream.total_out;
    deflateEnd(&mut stream);
    return if err == 1 as libc::c_int { 0 as libc::c_int } else { err };
}
#[no_mangle]
pub unsafe extern "C" fn compress(
    mut dest: *mut Bytef,
    mut destLen: *mut uLongf,
    mut source: *const Bytef,
    mut sourceLen: uLong,
) -> libc::c_int {
    return compress2(dest, destLen, source, sourceLen, -(1 as libc::c_int));
}
#[no_mangle]
pub unsafe extern "C" fn compressBound(mut sourceLen: uLong) -> uLong {
    return sourceLen
        .wrapping_add(sourceLen >> 12 as libc::c_int)
        .wrapping_add(sourceLen >> 14 as libc::c_int)
        .wrapping_add(sourceLen >> 25 as libc::c_int)
        .wrapping_add(13 as libc::c_int as uLong);
}
