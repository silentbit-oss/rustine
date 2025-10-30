use ::libc;
extern "C" {
    pub type internal_state;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn png_zstream_error(png_ptr: png_structrp, ret: libc::c_int);
    fn png_reset_crc(png_ptr: png_structrp);
    fn png_write_data(png_ptr: png_structrp, data: png_const_bytep, length: size_t);
    fn png_calculate_crc(png_ptr: png_structrp, ptr: png_const_bytep, length: size_t);
    fn png_safecat(
        buffer: png_charp,
        bufsize: size_t,
        pos: size_t,
        string: png_const_charp,
    ) -> size_t;
    fn png_app_warning(png_ptr: png_const_structrp, message: png_const_charp);
    fn png_write_flush(png_ptr: png_structrp);
    fn png_malloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_calloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_free(png_ptr: png_const_structrp, ptr: png_voidp);
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_warning(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn deflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn deflateEnd(strm: z_streamp) -> libc::c_int;
    fn deflateReset(strm: z_streamp) -> libc::c_int;
    fn deflateInit2_(
        strm: z_streamp,
        level: libc::c_int,
        method: libc::c_int,
        windowBits: libc::c_int,
        memLevel: libc::c_int,
        strategy: libc::c_int,
        version: *const libc::c_char,
        stream_size: libc::c_int,
    ) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
pub type png_byte = libc::c_uchar;
pub type png_uint_16 = libc::c_ushort;
pub type png_int_32 = libc::c_int;
pub type png_uint_32 = libc::c_uint;
pub type png_alloc_size_t = size_t;
pub type png_fixed_point = png_int_32;
pub type png_voidp = *mut libc::c_void;
pub type png_bytep = *mut png_byte;
pub type png_const_bytep = *const png_byte;
pub type png_const_uint_16p = *const png_uint_16;
pub type png_charp = *mut libc::c_char;
pub type png_const_charp = *const libc::c_char;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_struct_def {
    pub error_fn: png_error_ptr,
    pub warning_fn: png_error_ptr,
    pub error_ptr: png_voidp,
    pub write_data_fn: png_rw_ptr,
    pub read_data_fn: png_rw_ptr,
    pub io_ptr: png_voidp,
    pub mode: png_uint_32,
    pub flags: png_uint_32,
    pub transformations: png_uint_32,
    pub zowner: png_uint_32,
    pub zstream: z_stream,
    pub zbuffer_list: png_compression_bufferp,
    pub zbuffer_size: uInt,
    pub zlib_level: libc::c_int,
    pub zlib_method: libc::c_int,
    pub zlib_window_bits: libc::c_int,
    pub zlib_mem_level: libc::c_int,
    pub zlib_strategy: libc::c_int,
    pub zlib_set_level: libc::c_int,
    pub zlib_set_method: libc::c_int,
    pub zlib_set_window_bits: libc::c_int,
    pub zlib_set_mem_level: libc::c_int,
    pub zlib_set_strategy: libc::c_int,
    pub width: png_uint_32,
    pub height: png_uint_32,
    pub num_rows: png_uint_32,
    pub usr_width: png_uint_32,
    pub rowbytes: size_t,
    pub iwidth: png_uint_32,
    pub row_number: png_uint_32,
    pub chunk_name: png_uint_32,
    pub prev_row: png_bytep,
    pub row_buf: png_bytep,
    pub try_row: png_bytep,
    pub tst_row: png_bytep,
    pub info_rowbytes: size_t,
    pub idat_size: png_uint_32,
    pub crc: png_uint_32,
    pub palette: png_colorp,
    pub num_palette: png_uint_16,
    pub num_palette_max: libc::c_int,
    pub num_trans: png_uint_16,
    pub compression: png_byte,
    pub filter: png_byte,
    pub interlaced: png_byte,
    pub pass: png_byte,
    pub do_filter: png_byte,
    pub color_type: png_byte,
    pub bit_depth: png_byte,
    pub usr_bit_depth: png_byte,
    pub pixel_depth: png_byte,
    pub channels: png_byte,
    pub usr_channels: png_byte,
    pub sig_bytes: png_byte,
    pub maximum_pixel_depth: png_byte,
    pub transformed_pixel_depth: png_byte,
    pub zstream_start: png_byte,
    pub background_gamma_type: png_byte,
    pub background_gamma: png_fixed_point,
    pub background: png_color_16,
    pub output_flush_fn: png_flush_ptr,
    pub flush_dist: png_uint_32,
    pub flush_rows: png_uint_32,
    pub sig_bit: png_color_8,
    pub trans_alpha: png_bytep,
    pub trans_color: png_color_16,
    pub read_row_fn: png_read_status_ptr,
    pub write_row_fn: png_write_status_ptr,
    pub free_me: png_uint_32,
    pub unknown_default: libc::c_int,
    pub num_chunk_list: libc::c_uint,
    pub chunk_list: png_bytep,
    pub big_row_buf: png_bytep,
    pub compression_type: png_byte,
    pub user_width_max: png_uint_32,
    pub user_height_max: png_uint_32,
    pub user_chunk_cache_max: png_uint_32,
    pub user_chunk_malloc_max: png_alloc_size_t,
    pub unknown_chunk: png_unknown_chunk,
    pub old_big_row_buf_size: size_t,
    pub read_buffer: png_bytep,
    pub read_buffer_size: png_alloc_size_t,
    pub IDAT_read_size: uInt,
    pub io_state: png_uint_32,
    pub big_prev_row: png_bytep,
    pub read_filter: [Option::<
        unsafe extern "C" fn(png_row_infop, png_bytep, png_const_bytep) -> (),
    >; 4],
}
pub type png_row_infop = *mut png_row_info;
pub type png_row_info = png_row_info_struct;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_row_info_struct {
    pub width: png_uint_32,
    pub rowbytes: size_t,
    pub color_type: png_byte,
    pub bit_depth: png_byte,
    pub channels: png_byte,
    pub pixel_depth: png_byte,
}
pub type uInt = libc::c_uint;
pub type png_unknown_chunk = png_unknown_chunk_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_unknown_chunk_t {
    pub name: [png_byte; 5],
    pub data: *mut png_byte,
    pub size: size_t,
    pub location: png_byte,
}
pub type png_write_status_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_uint_32, libc::c_int) -> (),
>;
pub type png_structp = *mut png_struct;
pub type png_struct = png_struct_def;
pub type png_read_status_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_uint_32, libc::c_int) -> (),
>;
pub type png_color_16 = png_color_16_struct;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_color_16_struct {
    pub index: png_byte,
    pub red: png_uint_16,
    pub green: png_uint_16,
    pub blue: png_uint_16,
    pub gray: png_uint_16,
}
pub type png_color_8 = png_color_8_struct;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_color_8_struct {
    pub red: png_byte,
    pub green: png_byte,
    pub blue: png_byte,
    pub gray: png_byte,
    pub alpha: png_byte,
}
pub type png_flush_ptr = Option::<unsafe extern "C" fn(png_structp) -> ()>;
pub type png_colorp = *mut png_color;
pub type png_color = png_color_struct;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_color_struct {
    pub red: png_byte,
    pub green: png_byte,
    pub blue: png_byte,
}
pub type png_compression_bufferp = *mut png_compression_buffer;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_compression_buffer {
    pub next: *mut png_compression_buffer,
    pub output: [png_byte; 1],
}
pub type z_stream = z_stream_s;
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
pub type uLong = libc::c_ulong;
pub type voidpf = *mut libc::c_void;
pub type free_func = Option::<unsafe extern "C" fn(voidpf, voidpf) -> ()>;
pub type alloc_func = Option::<unsafe extern "C" fn(voidpf, uInt, uInt) -> voidpf>;
pub type Bytef = Byte;
pub type Byte = libc::c_uchar;
pub type png_rw_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_bytep, size_t) -> (),
>;
pub type png_error_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_const_charp) -> (),
>;
pub type png_structrp = *mut png_struct;
pub type png_const_structrp = *const png_struct;
pub type png_const_colorp = *const png_color;
pub type png_const_color_16p = *const png_color_16;
pub type png_const_color_8p = *const png_color_8;
pub type z_streamp = *mut z_stream;
#[no_mangle]
pub unsafe extern "C" fn png_save_uint_32(mut buf: png_bytep, mut i: png_uint_32) {
    *buf
        .offset(
            0 as libc::c_int as isize,
        ) = (i >> 24 as libc::c_int & 0xff as libc::c_uint) as png_byte;
    *buf
        .offset(
            1 as libc::c_int as isize,
        ) = (i >> 16 as libc::c_int & 0xff as libc::c_uint) as png_byte;
    *buf
        .offset(
            2 as libc::c_int as isize,
        ) = (i >> 8 as libc::c_int & 0xff as libc::c_uint) as png_byte;
    *buf.offset(3 as libc::c_int as isize) = (i & 0xff as libc::c_uint) as png_byte;
}
#[no_mangle]
pub unsafe extern "C" fn png_save_uint_16(mut buf: png_bytep, mut i: libc::c_uint) {
    *buf
        .offset(
            0 as libc::c_int as isize,
        ) = (i >> 8 as libc::c_int & 0xff as libc::c_uint) as png_byte;
    *buf.offset(1 as libc::c_int as isize) = (i & 0xff as libc::c_uint) as png_byte;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_sig(mut png_ptr: png_structrp) {
    let mut png_signature: [png_byte; 8] = [
        137 as libc::c_int as png_byte,
        80 as libc::c_int as png_byte,
        78 as libc::c_int as png_byte,
        71 as libc::c_int as png_byte,
        13 as libc::c_int as png_byte,
        10 as libc::c_int as png_byte,
        26 as libc::c_int as png_byte,
        10 as libc::c_int as png_byte,
    ];
    (*png_ptr).io_state = (0x2 as libc::c_int | 0x10 as libc::c_int) as png_uint_32;
    png_write_data(
        png_ptr,
        &mut *png_signature.as_mut_ptr().offset((*png_ptr).sig_bytes as isize)
            as *mut png_byte as png_const_bytep,
        (8 as libc::c_int - (*png_ptr).sig_bytes as libc::c_int) as size_t,
    );
    if ((*png_ptr).sig_bytes as libc::c_int) < 3 as libc::c_int {
        (*png_ptr).mode |= 0x1000 as libc::c_uint;
    }
}
unsafe extern "C" fn png_write_chunk_header(
    mut png_ptr: png_structrp,
    mut chunk_name: png_uint_32,
    mut length: png_uint_32,
) {
    let mut buf: [png_byte; 8] = [0; 8];
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).io_state = (0x2 as libc::c_int | 0x20 as libc::c_int) as png_uint_32;
    png_save_uint_32(buf.as_mut_ptr(), length);
    png_save_uint_32(buf.as_mut_ptr().offset(4 as libc::c_int as isize), chunk_name);
    png_write_data(
        png_ptr,
        buf.as_mut_ptr() as png_const_bytep,
        8 as libc::c_int as size_t,
    );
    (*png_ptr).chunk_name = chunk_name;
    png_reset_crc(png_ptr);
    png_calculate_crc(
        png_ptr,
        buf.as_mut_ptr().offset(4 as libc::c_int as isize) as png_const_bytep,
        4 as libc::c_int as size_t,
    );
    (*png_ptr).io_state = (0x2 as libc::c_int | 0x40 as libc::c_int) as png_uint_32;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk_start(
    mut png_ptr: png_structrp,
    mut chunk_string: png_const_bytep,
    mut length: png_uint_32,
) {
    png_write_chunk_header(
        png_ptr,
        ((0xff as libc::c_int
            & *chunk_string.offset(0 as libc::c_int as isize) as libc::c_int)
            as png_uint_32) << 24 as libc::c_int
            | ((0xff as libc::c_int
                & *chunk_string.offset(1 as libc::c_int as isize) as libc::c_int)
                as png_uint_32) << 16 as libc::c_int
            | ((0xff as libc::c_int
                & *chunk_string.offset(2 as libc::c_int as isize) as libc::c_int)
                as png_uint_32) << 8 as libc::c_int
            | ((0xff as libc::c_int
                & *chunk_string.offset(3 as libc::c_int as isize) as libc::c_int)
                as png_uint_32) << 0 as libc::c_int,
        length,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk_data(
    mut png_ptr: png_structrp,
    mut data: png_const_bytep,
    mut length: size_t,
) {
    if png_ptr.is_null() {
        return;
    }
    if !data.is_null() && length > 0 as libc::c_int as size_t {
        png_write_data(png_ptr, data, length);
        png_calculate_crc(png_ptr, data, length);
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk_end(mut png_ptr: png_structrp) {
    let mut buf: [png_byte; 4] = [0; 4];
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).io_state = (0x2 as libc::c_int | 0x80 as libc::c_int) as png_uint_32;
    png_save_uint_32(buf.as_mut_ptr(), (*png_ptr).crc);
    png_write_data(
        png_ptr,
        buf.as_mut_ptr() as png_const_bytep,
        4 as libc::c_int as size_t,
    );
}
unsafe extern "C" fn png_write_complete_chunk(
    mut png_ptr: png_structrp,
    mut chunk_name: png_uint_32,
    mut data: png_const_bytep,
    mut length: size_t,
) {
    if png_ptr.is_null() {
        return;
    }
    if length > 0x7fffffff as libc::c_long as png_uint_32 as size_t {
        png_error(
            png_ptr as png_const_structrp,
            b"length exceeds PNG maximum\0" as *const u8 as *const libc::c_char,
        );
    }
    png_write_chunk_header(png_ptr, chunk_name, length as png_uint_32);
    png_write_chunk_data(png_ptr, data, length);
    png_write_chunk_end(png_ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_write_chunk(
    mut png_ptr: png_structrp,
    mut chunk_string: png_const_bytep,
    mut data: png_const_bytep,
    mut length: size_t,
) {
    png_write_complete_chunk(
        png_ptr,
        ((0xff as libc::c_int
            & *chunk_string.offset(0 as libc::c_int as isize) as libc::c_int)
            as png_uint_32) << 24 as libc::c_int
            | ((0xff as libc::c_int
                & *chunk_string.offset(1 as libc::c_int as isize) as libc::c_int)
                as png_uint_32) << 16 as libc::c_int
            | ((0xff as libc::c_int
                & *chunk_string.offset(2 as libc::c_int as isize) as libc::c_int)
                as png_uint_32) << 8 as libc::c_int
            | ((0xff as libc::c_int
                & *chunk_string.offset(3 as libc::c_int as isize) as libc::c_int)
                as png_uint_32) << 0 as libc::c_int,
        data,
        length,
    );
}
unsafe extern "C" fn png_image_size(mut png_ptr: png_structrp) -> png_alloc_size_t {
    let mut h: png_uint_32 = (*png_ptr).height;
    if (*png_ptr).rowbytes < 32768 as libc::c_int as size_t
        && h < 32768 as libc::c_int as png_uint_32
    {
        if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int {
            let mut w: png_uint_32 = (*png_ptr).width;
            let mut pd: libc::c_uint = (*png_ptr).pixel_depth as libc::c_uint;
            let mut cb_base: png_alloc_size_t = 0;
            let mut pass: libc::c_int = 0;
            cb_base = 0 as libc::c_int as png_alloc_size_t;
            pass = 0 as libc::c_int;
            while pass <= 6 as libc::c_int {
                let mut pw: png_uint_32 = w
                    .wrapping_add(
                        (((1 as libc::c_int)
                            << (if pass > 1 as libc::c_int {
                                7 as libc::c_int - pass >> 1 as libc::c_int
                            } else {
                                3 as libc::c_int
                            })) - 1 as libc::c_int
                            - ((1 as libc::c_int & pass)
                                << 3 as libc::c_int
                                    - (pass + 1 as libc::c_int >> 1 as libc::c_int)
                                & 7 as libc::c_int)) as png_uint_32,
                    )
                    >> (if pass > 1 as libc::c_int {
                        7 as libc::c_int - pass >> 1 as libc::c_int
                    } else {
                        3 as libc::c_int
                    });
                if pw > 0 as libc::c_int as png_uint_32 {
                    cb_base = (cb_base as size_t)
                        .wrapping_add(
                            (if pd >= 8 as libc::c_int as libc::c_uint {
                                pw as size_t * (pd as size_t >> 3 as libc::c_int)
                            } else {
                                (pw as size_t * pd as size_t)
                                    .wrapping_add(7 as libc::c_int as size_t)
                                    >> 3 as libc::c_int
                            })
                                .wrapping_add(1 as libc::c_int as size_t)
                                * (h
                                    .wrapping_add(
                                        (((1 as libc::c_int)
                                            << (if pass > 2 as libc::c_int {
                                                8 as libc::c_int - pass >> 1 as libc::c_int
                                            } else {
                                                3 as libc::c_int
                                            })) - 1 as libc::c_int
                                            - ((1 as libc::c_int & !pass)
                                                << 3 as libc::c_int - (pass >> 1 as libc::c_int)
                                                & 7 as libc::c_int)) as png_uint_32,
                                    )
                                    >> (if pass > 2 as libc::c_int {
                                        8 as libc::c_int - pass >> 1 as libc::c_int
                                    } else {
                                        3 as libc::c_int
                                    })) as size_t,
                        ) as png_alloc_size_t as png_alloc_size_t;
                }
                pass += 1;
                pass;
            }
            return cb_base;
        } else {
            return ((*png_ptr).rowbytes).wrapping_add(1 as libc::c_int as size_t)
                * h as size_t
        }
    } else {
        return 0xffffffff as libc::c_uint as png_alloc_size_t
    };
}
unsafe extern "C" fn optimize_cmf(mut data: png_bytep, mut data_size: png_alloc_size_t) {
    if data_size <= 16384 as libc::c_int as png_alloc_size_t {
        let mut z_cmf: libc::c_uint = *data.offset(0 as libc::c_int as isize)
            as libc::c_uint;
        if z_cmf & 0xf as libc::c_int as libc::c_uint == 8 as libc::c_int as libc::c_uint
            && z_cmf & 0xf0 as libc::c_int as libc::c_uint
                <= 0x70 as libc::c_int as libc::c_uint
        {
            let mut z_cinfo: libc::c_uint = 0;
            let mut half_z_window_size: libc::c_uint = 0;
            z_cinfo = z_cmf >> 4 as libc::c_int;
            half_z_window_size = (1 as libc::c_uint)
                << z_cinfo.wrapping_add(7 as libc::c_int as libc::c_uint);
            if data_size <= half_z_window_size as png_alloc_size_t {
                let mut tmp: libc::c_uint = 0;
                loop {
                    half_z_window_size >>= 1 as libc::c_int;
                    z_cinfo = z_cinfo.wrapping_sub(1);
                    z_cinfo;
                    if !(z_cinfo > 0 as libc::c_int as libc::c_uint
                        && data_size <= half_z_window_size as png_alloc_size_t)
                    {
                        break;
                    }
                }
                z_cmf = z_cmf & 0xf as libc::c_int as libc::c_uint
                    | z_cinfo << 4 as libc::c_int;
                *data.offset(0 as libc::c_int as isize) = z_cmf as png_byte;
                tmp = (*data.offset(1 as libc::c_int as isize) as libc::c_int
                    & 0xe0 as libc::c_int) as libc::c_uint;
                tmp = tmp
                    .wrapping_add(
                        (0x1f as libc::c_int as libc::c_uint)
                            .wrapping_sub(
                                (z_cmf << 8 as libc::c_int)
                                    .wrapping_add(tmp)
                                    .wrapping_rem(0x1f as libc::c_int as libc::c_uint),
                            ),
                    );
                *data.offset(1 as libc::c_int as isize) = tmp as png_byte;
            }
        }
    }
}
unsafe extern "C" fn png_deflate_claim(
    mut png_ptr: png_structrp,
    mut owner: png_uint_32,
    mut data_size: png_alloc_size_t,
) -> libc::c_int {
    if (*png_ptr).zowner != 0 as libc::c_int as png_uint_32 {
        let mut msg: [libc::c_char; 64] = [0; 64];
        *msg
            .as_mut_ptr()
            .offset(
                0 as libc::c_int as isize,
            ) = (owner >> 24 as libc::c_int & 0xff as libc::c_int as png_uint_32)
            as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(
                1 as libc::c_int as isize,
            ) = (owner >> 16 as libc::c_int & 0xff as libc::c_int as png_uint_32)
            as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(
                2 as libc::c_int as isize,
            ) = (owner >> 8 as libc::c_int & 0xff as libc::c_int as png_uint_32)
            as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(
                3 as libc::c_int as isize,
            ) = (owner & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        msg[4 as libc::c_int as usize] = ':' as i32 as libc::c_char;
        msg[5 as libc::c_int as usize] = ' ' as i32 as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(6 as libc::c_int as isize)
            .offset(
                0 as libc::c_int as isize,
            ) = ((*png_ptr).zowner >> 24 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(6 as libc::c_int as isize)
            .offset(
                1 as libc::c_int as isize,
            ) = ((*png_ptr).zowner >> 16 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(6 as libc::c_int as isize)
            .offset(
                2 as libc::c_int as isize,
            ) = ((*png_ptr).zowner >> 8 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(6 as libc::c_int as isize)
            .offset(
                3 as libc::c_int as isize,
            ) = ((*png_ptr).zowner & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        png_safecat(
            msg.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 64]>() as libc::c_ulong,
            10 as libc::c_int as size_t,
            b" using zstream\0" as *const u8 as *const libc::c_char,
        );
        png_warning(png_ptr as png_const_structrp, msg.as_mut_ptr() as png_const_charp);
        if (*png_ptr).zowner
            == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            (*png_ptr)
                .zstream
                .msg = b"in use by IDAT\0" as *const u8 as *const libc::c_char;
            return -(2 as libc::c_int);
        }
        (*png_ptr).zowner = 0 as libc::c_int as png_uint_32;
    }
    let mut level: libc::c_int = (*png_ptr).zlib_level;
    let mut method: libc::c_int = (*png_ptr).zlib_method;
    let mut windowBits: libc::c_int = (*png_ptr).zlib_window_bits;
    let mut memLevel: libc::c_int = (*png_ptr).zlib_mem_level;
    let mut strategy: libc::c_int = 0;
    let mut ret: libc::c_int = 0;
    if owner
        == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
    {
        if (*png_ptr).flags & 0x1 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
            strategy = (*png_ptr).zlib_strategy;
        } else if (*png_ptr).do_filter as libc::c_int != 0x8 as libc::c_int {
            strategy = 1 as libc::c_int;
        } else {
            strategy = 0 as libc::c_int;
        }
    } else {
        strategy = 0 as libc::c_int;
    }
    if data_size <= 16384 as libc::c_int as png_alloc_size_t {
        let mut half_window_size: libc::c_uint = (1 as libc::c_uint)
            << windowBits - 1 as libc::c_int;
        while data_size.wrapping_add(262 as libc::c_int as png_alloc_size_t)
            <= half_window_size as png_alloc_size_t
        {
            half_window_size >>= 1 as libc::c_int;
            windowBits -= 1;
            windowBits;
        }
    }
    if (*png_ptr).flags & 0x2 as libc::c_uint != 0 as libc::c_int as libc::c_uint
        && ((*png_ptr).zlib_set_level != level || (*png_ptr).zlib_set_method != method
            || (*png_ptr).zlib_set_window_bits != windowBits
            || (*png_ptr).zlib_set_mem_level != memLevel
            || (*png_ptr).zlib_set_strategy != strategy)
    {
        if deflateEnd(&mut (*png_ptr).zstream) != 0 as libc::c_int {
            png_warning(
                png_ptr as png_const_structrp,
                b"deflateEnd failed (ignored)\0" as *const u8 as *const libc::c_char,
            );
        }
        (*png_ptr).flags &= !(0x2 as libc::c_uint);
    }
    (*png_ptr).zstream.next_in = 0 as *const Bytef;
    (*png_ptr).zstream.avail_in = 0 as libc::c_int as uInt;
    (*png_ptr).zstream.next_out = 0 as *mut Bytef;
    (*png_ptr).zstream.avail_out = 0 as libc::c_int as uInt;
    if (*png_ptr).flags & 0x2 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        ret = deflateReset(&mut (*png_ptr).zstream);
    } else {
        ret = deflateInit2_(
            &mut (*png_ptr).zstream,
            level,
            method,
            windowBits,
            memLevel,
            strategy,
            b"1.3-optipng\0" as *const u8 as *const libc::c_char,
            ::core::mem::size_of::<z_stream>() as libc::c_ulong as libc::c_int,
        );
        if ret == 0 as libc::c_int {
            (*png_ptr).flags |= 0x2 as libc::c_uint;
        }
    }
    if ret == 0 as libc::c_int {
        (*png_ptr).zowner = owner;
    } else {
        png_zstream_error(png_ptr, ret);
    }
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn png_free_buffer_list(
    mut png_ptr: png_structrp,
    mut listp: *mut png_compression_bufferp,
) {
    let mut list: png_compression_bufferp = *listp;
    if !list.is_null() {
        *listp = 0 as png_compression_bufferp;
        loop {
            let mut next: png_compression_bufferp = (*list).next;
            png_free(png_ptr as png_const_structrp, list as png_voidp);
            list = next;
            if list.is_null() {
                break;
            }
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_IHDR(
    mut png_ptr: png_structrp,
    mut width: png_uint_32,
    mut height: png_uint_32,
    mut bit_depth: libc::c_int,
    mut color_type: libc::c_int,
    mut compression_type: libc::c_int,
    mut filter_type: libc::c_int,
    mut interlace_type: libc::c_int,
) {
    let mut buf: [png_byte; 13] = [0; 13];
    let mut is_invalid_depth: libc::c_int = 0;
    match color_type {
        0 => {
            match bit_depth {
                1 | 2 | 4 | 8 | 16 => {
                    (*png_ptr).channels = 1 as libc::c_int as png_byte;
                }
                _ => {
                    png_error(
                        png_ptr as png_const_structrp,
                        b"Invalid bit depth for grayscale image\0" as *const u8
                            as *const libc::c_char,
                    );
                }
            }
        }
        2 => {
            is_invalid_depth = (bit_depth != 8 as libc::c_int) as libc::c_int;
            is_invalid_depth = (is_invalid_depth != 0 && bit_depth != 16 as libc::c_int)
                as libc::c_int;
            if is_invalid_depth != 0 {
                png_error(
                    png_ptr as png_const_structrp,
                    b"Invalid bit depth for RGB image\0" as *const u8
                        as *const libc::c_char,
                );
            }
            (*png_ptr).channels = 3 as libc::c_int as png_byte;
        }
        3 => {
            match bit_depth {
                1 | 2 | 4 | 8 => {
                    (*png_ptr).channels = 1 as libc::c_int as png_byte;
                }
                _ => {
                    png_error(
                        png_ptr as png_const_structrp,
                        b"Invalid bit depth for paletted image\0" as *const u8
                            as *const libc::c_char,
                    );
                }
            }
        }
        4 => {
            is_invalid_depth = (bit_depth != 8 as libc::c_int) as libc::c_int;
            is_invalid_depth = (is_invalid_depth != 0 && bit_depth != 16 as libc::c_int)
                as libc::c_int;
            if is_invalid_depth != 0 {
                png_error(
                    png_ptr as png_const_structrp,
                    b"Invalid bit depth for grayscale+alpha image\0" as *const u8
                        as *const libc::c_char,
                );
            }
            (*png_ptr).channels = 2 as libc::c_int as png_byte;
        }
        6 => {
            is_invalid_depth = (bit_depth != 8 as libc::c_int) as libc::c_int;
            is_invalid_depth = (is_invalid_depth != 0 && bit_depth != 16 as libc::c_int)
                as libc::c_int;
            if is_invalid_depth != 0 {
                png_error(
                    png_ptr as png_const_structrp,
                    b"Invalid bit depth for RGBA image\0" as *const u8
                        as *const libc::c_char,
                );
            }
            (*png_ptr).channels = 4 as libc::c_int as png_byte;
        }
        _ => {
            png_error(
                png_ptr as png_const_structrp,
                b"Invalid image color type specified\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
    if compression_type != 0 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Invalid compression type specified\0" as *const u8 as *const libc::c_char,
        );
        compression_type = 0 as libc::c_int;
    }
    if filter_type != 0 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Invalid filter type specified\0" as *const u8 as *const libc::c_char,
        );
        filter_type = 0 as libc::c_int;
    }
    if interlace_type != 0 as libc::c_int && interlace_type != 1 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Invalid interlace type specified\0" as *const u8 as *const libc::c_char,
        );
        interlace_type = 1 as libc::c_int;
    }
    (*png_ptr).bit_depth = bit_depth as png_byte;
    (*png_ptr).color_type = color_type as png_byte;
    (*png_ptr).interlaced = interlace_type as png_byte;
    (*png_ptr).compression_type = compression_type as png_byte;
    (*png_ptr).width = width;
    (*png_ptr).height = height;
    (*png_ptr)
        .pixel_depth = (bit_depth * (*png_ptr).channels as libc::c_int) as png_byte;
    (*png_ptr)
        .rowbytes = if (*png_ptr).pixel_depth as libc::c_int >= 8 as libc::c_int {
        width as size_t * ((*png_ptr).pixel_depth as size_t >> 3 as libc::c_int)
    } else {
        (width as size_t * (*png_ptr).pixel_depth as size_t)
            .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
    };
    (*png_ptr).usr_width = (*png_ptr).width;
    (*png_ptr).usr_bit_depth = (*png_ptr).bit_depth;
    (*png_ptr).usr_channels = (*png_ptr).channels;
    png_save_uint_32(buf.as_mut_ptr(), width);
    png_save_uint_32(buf.as_mut_ptr().offset(4 as libc::c_int as isize), height);
    buf[8 as libc::c_int as usize] = bit_depth as png_byte;
    buf[9 as libc::c_int as usize] = color_type as png_byte;
    buf[10 as libc::c_int as usize] = compression_type as png_byte;
    buf[11 as libc::c_int as usize] = filter_type as png_byte;
    buf[12 as libc::c_int as usize] = interlace_type as png_byte;
    png_write_complete_chunk(
        png_ptr,
        (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (72 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (82 as libc::c_int as png_uint_32) << 0 as libc::c_int,
        buf.as_mut_ptr() as png_const_bytep,
        13 as libc::c_int as size_t,
    );
    if (*png_ptr).do_filter as libc::c_int == 0 as libc::c_int {
        if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int
            || ((*png_ptr).bit_depth as libc::c_int) < 8 as libc::c_int
        {
            (*png_ptr).do_filter = 0x8 as libc::c_int as png_byte;
        } else {
            (*png_ptr)
                .do_filter = (0x8 as libc::c_int | 0x10 as libc::c_int
                | 0x20 as libc::c_int | 0x40 as libc::c_int | 0x80 as libc::c_int)
                as png_byte;
        }
    }
    (*png_ptr).mode = 0x1 as libc::c_int as png_uint_32;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_PLTE(
    mut png_ptr: png_structrp,
    mut palette: png_const_colorp,
    mut num_pal: png_uint_32,
) {
    let mut max_palette_length: png_uint_32 = 0;
    let mut i: png_uint_32 = 0;
    let mut pal_ptr: png_const_colorp = 0 as *const png_color;
    let mut buf: [png_byte; 3] = [0; 3];
    max_palette_length = (if (*png_ptr).color_type as libc::c_int
        == 2 as libc::c_int | 1 as libc::c_int
    {
        (1 as libc::c_int) << (*png_ptr).bit_depth as libc::c_int
    } else {
        256 as libc::c_int
    }) as png_uint_32;
    if num_pal == 0 as libc::c_int as png_uint_32 || num_pal > max_palette_length {
        if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int {
            png_error(
                png_ptr as png_const_structrp,
                b"Invalid number of colors in palette\0" as *const u8
                    as *const libc::c_char,
            );
        } else {
            png_warning(
                png_ptr as png_const_structrp,
                b"Invalid number of colors in palette\0" as *const u8
                    as *const libc::c_char,
            );
            return;
        }
    }
    if (*png_ptr).color_type as libc::c_int & 2 as libc::c_int == 0 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Ignoring request to write a PLTE chunk in grayscale PNG\0" as *const u8
                as *const libc::c_char,
        );
        return;
    }
    (*png_ptr).num_palette = num_pal as png_uint_16;
    png_write_chunk_header(
        png_ptr,
        (80 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (76 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (69 as libc::c_int as png_uint_32) << 0 as libc::c_int,
        num_pal * 3 as libc::c_int as png_uint_32,
    );
    i = 0 as libc::c_int as png_uint_32;
    pal_ptr = palette;
    while i < num_pal {
        buf[0 as libc::c_int as usize] = (*pal_ptr).red;
        buf[1 as libc::c_int as usize] = (*pal_ptr).green;
        buf[2 as libc::c_int as usize] = (*pal_ptr).blue;
        png_write_chunk_data(
            png_ptr,
            buf.as_mut_ptr() as png_const_bytep,
            3 as libc::c_int as size_t,
        );
        i = i.wrapping_add(1);
        i;
        pal_ptr = pal_ptr.offset(1);
        pal_ptr;
    }
    png_write_chunk_end(png_ptr);
    (*png_ptr).mode |= 0x2 as libc::c_int as png_uint_32;
}
#[no_mangle]
pub unsafe extern "C" fn png_compress_IDAT(
    mut png_ptr: png_structrp,
    mut input: png_const_bytep,
    mut input_len: png_alloc_size_t,
    mut flush: libc::c_int,
) {
    if (*png_ptr).zowner
        != (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
    {
        if ((*png_ptr).zbuffer_list).is_null() {
            (*png_ptr)
                .zbuffer_list = png_malloc(
                png_ptr as png_const_structrp,
                (8 as libc::c_ulong)
                    .wrapping_add((*png_ptr).zbuffer_size as libc::c_ulong),
            ) as png_compression_bufferp;
            (*(*png_ptr).zbuffer_list).next = 0 as *mut png_compression_buffer;
        } else {
            png_free_buffer_list(png_ptr, &mut (*(*png_ptr).zbuffer_list).next);
        }
        if png_deflate_claim(
            png_ptr,
            (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            png_image_size(png_ptr),
        ) != 0 as libc::c_int
        {
            png_error(png_ptr as png_const_structrp, (*png_ptr).zstream.msg);
        }
        (*png_ptr).zstream.next_out = ((*(*png_ptr).zbuffer_list).output).as_mut_ptr();
        (*png_ptr).zstream.avail_out = (*png_ptr).zbuffer_size;
    }
    (*png_ptr).zstream.next_in = input;
    (*png_ptr).zstream.avail_in = 0 as libc::c_int as uInt;
    loop {
        let mut ret: libc::c_int = 0;
        let mut avail: uInt = -(1 as libc::c_int) as uInt;
        if avail as png_alloc_size_t > input_len {
            avail = input_len as uInt;
        }
        (*png_ptr).zstream.avail_in = avail;
        input_len = input_len.wrapping_sub(avail as png_alloc_size_t);
        ret = deflate(
            &mut (*png_ptr).zstream,
            if input_len > 0 as libc::c_int as png_alloc_size_t {
                0 as libc::c_int
            } else {
                flush
            },
        );
        input_len = input_len
            .wrapping_add((*png_ptr).zstream.avail_in as png_alloc_size_t);
        (*png_ptr).zstream.avail_in = 0 as libc::c_int as uInt;
        if (*png_ptr).zstream.avail_out == 0 as libc::c_int as uInt {
            let mut data: png_bytep = ((*(*png_ptr).zbuffer_list).output).as_mut_ptr();
            let mut size: uInt = (*png_ptr).zbuffer_size;
            if (*png_ptr).mode & 0x4 as libc::c_uint == 0 as libc::c_int as libc::c_uint
                && (*png_ptr).compression_type as libc::c_int == 0 as libc::c_int
            {
                optimize_cmf(data, png_image_size(png_ptr));
            }
            if size > 0 as libc::c_int as uInt {
                png_write_complete_chunk(
                    png_ptr,
                    (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                        | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                        | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                        | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
                    data as png_const_bytep,
                    size as size_t,
                );
            }
            (*png_ptr).mode |= 0x4 as libc::c_uint;
            (*png_ptr).zstream.next_out = data;
            (*png_ptr).zstream.avail_out = size;
            if ret == 0 as libc::c_int && flush != 0 as libc::c_int {
                continue;
            }
        }
        if ret == 0 as libc::c_int {
            if input_len == 0 as libc::c_int as png_alloc_size_t {
                if flush == 4 as libc::c_int {
                    png_error(
                        png_ptr as png_const_structrp,
                        b"Z_OK on Z_FINISH with output space\0" as *const u8
                            as *const libc::c_char,
                    );
                }
                return;
            }
        } else if ret == 1 as libc::c_int && flush == 4 as libc::c_int {
            let mut data_0: png_bytep = ((*(*png_ptr).zbuffer_list).output).as_mut_ptr();
            let mut size_0: uInt = ((*png_ptr).zbuffer_size)
                .wrapping_sub((*png_ptr).zstream.avail_out);
            if (*png_ptr).mode & 0x4 as libc::c_uint == 0 as libc::c_int as libc::c_uint
                && (*png_ptr).compression_type as libc::c_int == 0 as libc::c_int
            {
                optimize_cmf(data_0, png_image_size(png_ptr));
            }
            if size_0 > 0 as libc::c_int as uInt {
                png_write_complete_chunk(
                    png_ptr,
                    (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                        | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                        | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                        | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
                    data_0 as png_const_bytep,
                    size_0 as size_t,
                );
            }
            (*png_ptr).zstream.avail_out = 0 as libc::c_int as uInt;
            (*png_ptr).zstream.next_out = 0 as *mut Bytef;
            (*png_ptr).mode |= 0x4 as libc::c_uint | 0x8 as libc::c_int as libc::c_uint;
            (*png_ptr).zowner = 0 as libc::c_int as png_uint_32;
            return;
        } else {
            png_zstream_error(png_ptr, ret);
            png_error(png_ptr as png_const_structrp, (*png_ptr).zstream.msg);
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_write_IEND(mut png_ptr: png_structrp) {
    png_write_complete_chunk(
        png_ptr,
        (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (69 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int,
        0 as png_const_bytep,
        0 as libc::c_int as size_t,
    );
    (*png_ptr).mode |= 0x10 as libc::c_uint;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_sBIT(
    mut png_ptr: png_structrp,
    mut sbit: png_const_color_8p,
    mut color_type: libc::c_int,
) {
    let mut buf: [png_byte; 4] = [0; 4];
    let mut size: size_t = 0;
    if color_type & 2 as libc::c_int != 0 as libc::c_int {
        let mut maxbits: png_byte = 0;
        maxbits = (if color_type == 2 as libc::c_int | 1 as libc::c_int {
            8 as libc::c_int
        } else {
            (*png_ptr).usr_bit_depth as libc::c_int
        }) as png_byte;
        if (*sbit).red as libc::c_int == 0 as libc::c_int
            || (*sbit).red as libc::c_int > maxbits as libc::c_int
            || (*sbit).green as libc::c_int == 0 as libc::c_int
            || (*sbit).green as libc::c_int > maxbits as libc::c_int
            || (*sbit).blue as libc::c_int == 0 as libc::c_int
            || (*sbit).blue as libc::c_int > maxbits as libc::c_int
        {
            png_warning(
                png_ptr as png_const_structrp,
                b"Invalid sBIT depth specified\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        buf[0 as libc::c_int as usize] = (*sbit).red;
        buf[1 as libc::c_int as usize] = (*sbit).green;
        buf[2 as libc::c_int as usize] = (*sbit).blue;
        size = 3 as libc::c_int as size_t;
    } else {
        if (*sbit).gray as libc::c_int == 0 as libc::c_int
            || (*sbit).gray as libc::c_int > (*png_ptr).usr_bit_depth as libc::c_int
        {
            png_warning(
                png_ptr as png_const_structrp,
                b"Invalid sBIT depth specified\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        buf[0 as libc::c_int as usize] = (*sbit).gray;
        size = 1 as libc::c_int as size_t;
    }
    if color_type & 4 as libc::c_int != 0 as libc::c_int {
        if (*sbit).alpha as libc::c_int == 0 as libc::c_int
            || (*sbit).alpha as libc::c_int > (*png_ptr).usr_bit_depth as libc::c_int
        {
            png_warning(
                png_ptr as png_const_structrp,
                b"Invalid sBIT depth specified\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        let fresh0 = size;
        size = size.wrapping_add(1);
        buf[fresh0 as usize] = (*sbit).alpha;
    }
    png_write_complete_chunk(
        png_ptr,
        (115 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (66 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (73 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
        buf.as_mut_ptr() as png_const_bytep,
        size,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_write_tRNS(
    mut png_ptr: png_structrp,
    mut trans_alpha: png_const_bytep,
    mut tran: png_const_color_16p,
    mut num_trans: libc::c_int,
    mut color_type: libc::c_int,
) {
    let mut buf: [png_byte; 6] = [0; 6];
    if color_type == 2 as libc::c_int | 1 as libc::c_int {
        if num_trans <= 0 as libc::c_int
            || num_trans > (*png_ptr).num_palette as libc::c_int
        {
            png_app_warning(
                png_ptr as png_const_structrp,
                b"Invalid number of transparent colors specified\0" as *const u8
                    as *const libc::c_char,
            );
            return;
        }
        png_write_complete_chunk(
            png_ptr,
            (116 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (82 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (83 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            trans_alpha,
            num_trans as size_t,
        );
    } else if color_type == 0 as libc::c_int {
        if (*tran).gray as libc::c_int
            >= (1 as libc::c_int) << (*png_ptr).bit_depth as libc::c_int
        {
            png_app_warning(
                png_ptr as png_const_structrp,
                b"Ignoring attempt to write tRNS chunk out-of-range for bit_depth\0"
                    as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_save_uint_16(buf.as_mut_ptr(), (*tran).gray as libc::c_uint);
        png_write_complete_chunk(
            png_ptr,
            (116 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (82 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (83 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            buf.as_mut_ptr() as png_const_bytep,
            2 as libc::c_int as size_t,
        );
    } else if color_type == 2 as libc::c_int {
        png_save_uint_16(buf.as_mut_ptr(), (*tran).red as libc::c_uint);
        png_save_uint_16(
            buf.as_mut_ptr().offset(2 as libc::c_int as isize),
            (*tran).green as libc::c_uint,
        );
        png_save_uint_16(
            buf.as_mut_ptr().offset(4 as libc::c_int as isize),
            (*tran).blue as libc::c_uint,
        );
        if (*png_ptr).bit_depth as libc::c_int == 8 as libc::c_int
            && buf[0 as libc::c_int as usize] as libc::c_int
                | buf[2 as libc::c_int as usize] as libc::c_int
                | buf[4 as libc::c_int as usize] as libc::c_int != 0 as libc::c_int
        {
            png_app_warning(
                png_ptr as png_const_structrp,
                b"Ignoring attempt to write 16-bit tRNS chunk when bit_depth is 8\0"
                    as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_write_complete_chunk(
            png_ptr,
            (116 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (82 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (83 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            buf.as_mut_ptr() as png_const_bytep,
            6 as libc::c_int as size_t,
        );
    } else {
        png_app_warning(
            png_ptr as png_const_structrp,
            b"Can't write tRNS with an alpha channel\0" as *const u8
                as *const libc::c_char,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_write_bKGD(
    mut png_ptr: png_structrp,
    mut back: png_const_color_16p,
    mut color_type: libc::c_int,
) {
    let mut buf: [png_byte; 6] = [0; 6];
    if color_type == 2 as libc::c_int | 1 as libc::c_int {
        if (*back).index as libc::c_int >= (*png_ptr).num_palette as libc::c_int {
            png_warning(
                png_ptr as png_const_structrp,
                b"Invalid background palette index\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        buf[0 as libc::c_int as usize] = (*back).index;
        png_write_complete_chunk(
            png_ptr,
            (98 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (75 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (71 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            buf.as_mut_ptr() as png_const_bytep,
            1 as libc::c_int as size_t,
        );
    } else if color_type & 2 as libc::c_int != 0 as libc::c_int {
        png_save_uint_16(buf.as_mut_ptr(), (*back).red as libc::c_uint);
        png_save_uint_16(
            buf.as_mut_ptr().offset(2 as libc::c_int as isize),
            (*back).green as libc::c_uint,
        );
        png_save_uint_16(
            buf.as_mut_ptr().offset(4 as libc::c_int as isize),
            (*back).blue as libc::c_uint,
        );
        if (*png_ptr).bit_depth as libc::c_int == 8 as libc::c_int
            && buf[0 as libc::c_int as usize] as libc::c_int
                | buf[2 as libc::c_int as usize] as libc::c_int
                | buf[4 as libc::c_int as usize] as libc::c_int != 0 as libc::c_int
        {
            png_warning(
                png_ptr as png_const_structrp,
                b"Ignoring attempt to write 16-bit bKGD chunk when bit_depth is 8\0"
                    as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_write_complete_chunk(
            png_ptr,
            (98 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (75 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (71 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            buf.as_mut_ptr() as png_const_bytep,
            6 as libc::c_int as size_t,
        );
    } else {
        if (*back).gray as libc::c_int
            >= (1 as libc::c_int) << (*png_ptr).bit_depth as libc::c_int
        {
            png_warning(
                png_ptr as png_const_structrp,
                b"Ignoring attempt to write bKGD chunk out-of-range for bit_depth\0"
                    as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_save_uint_16(buf.as_mut_ptr(), (*back).gray as libc::c_uint);
        png_write_complete_chunk(
            png_ptr,
            (98 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (75 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (71 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int,
            buf.as_mut_ptr() as png_const_bytep,
            2 as libc::c_int as size_t,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_write_hIST(
    mut png_ptr: png_structrp,
    mut hist: png_const_uint_16p,
    mut num_hist: libc::c_int,
) {
    let mut i: libc::c_int = 0;
    let mut buf: [png_byte; 3] = [0; 3];
    if num_hist > (*png_ptr).num_palette as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Invalid number of histogram entries specified\0" as *const u8
                as *const libc::c_char,
        );
        return;
    }
    png_write_chunk_header(
        png_ptr,
        (104 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (73 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (83 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
        (num_hist * 2 as libc::c_int) as png_uint_32,
    );
    i = 0 as libc::c_int;
    while i < num_hist {
        png_save_uint_16(buf.as_mut_ptr(), *hist.offset(i as isize) as libc::c_uint);
        png_write_chunk_data(
            png_ptr,
            buf.as_mut_ptr() as png_const_bytep,
            2 as libc::c_int as size_t,
        );
        i += 1;
        i;
    }
    png_write_chunk_end(png_ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_write_start_row(mut png_ptr: png_structrp) {
    static mut png_pass_start: [png_byte; 7] = [
        0 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
    ];
    static mut png_pass_inc: [png_byte; 7] = [
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
    ];
    static mut png_pass_ystart: [png_byte; 7] = [
        0 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
    ];
    static mut png_pass_yinc: [png_byte; 7] = [
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
    ];
    let mut buf_size: png_alloc_size_t = 0;
    let mut usr_pixel_depth: libc::c_int = 0;
    let mut filters: png_byte = 0;
    usr_pixel_depth = (*png_ptr).usr_channels as libc::c_int
        * (*png_ptr).usr_bit_depth as libc::c_int;
    buf_size = (if usr_pixel_depth >= 8 as libc::c_int {
        (*png_ptr).width as size_t * (usr_pixel_depth as size_t >> 3 as libc::c_int)
    } else {
        ((*png_ptr).width as size_t * usr_pixel_depth as size_t)
            .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
    })
        .wrapping_add(1 as libc::c_int as size_t);
    (*png_ptr).transformed_pixel_depth = (*png_ptr).pixel_depth;
    (*png_ptr).maximum_pixel_depth = usr_pixel_depth as png_byte;
    (*png_ptr)
        .row_buf = png_malloc(png_ptr as png_const_structrp, buf_size) as png_bytep;
    *((*png_ptr).row_buf)
        .offset(0 as libc::c_int as isize) = 0 as libc::c_int as png_byte;
    filters = (*png_ptr).do_filter;
    if (*png_ptr).height == 1 as libc::c_int as png_uint_32 {
        filters = (filters as libc::c_int
            & (0xff as libc::c_int
                & !(0x20 as libc::c_int | 0x40 as libc::c_int | 0x80 as libc::c_int)))
            as png_byte;
    }
    if (*png_ptr).width == 1 as libc::c_int as png_uint_32 {
        filters = (filters as libc::c_int
            & (0xff as libc::c_int
                & !(0x10 as libc::c_int | 0x40 as libc::c_int | 0x80 as libc::c_int)))
            as png_byte;
    }
    if filters as libc::c_int == 0 as libc::c_int {
        filters = 0x8 as libc::c_int as png_byte;
    }
    (*png_ptr).do_filter = filters;
    if filters as libc::c_int
        & (0x10 as libc::c_int | 0x20 as libc::c_int | 0x40 as libc::c_int
            | 0x80 as libc::c_int) != 0 as libc::c_int && ((*png_ptr).try_row).is_null()
    {
        let mut num_filters: libc::c_int = 0 as libc::c_int;
        (*png_ptr)
            .try_row = png_malloc(png_ptr as png_const_structrp, buf_size) as png_bytep;
        if filters as libc::c_int & 0x10 as libc::c_int != 0 {
            num_filters += 1;
            num_filters;
        }
        if filters as libc::c_int & 0x20 as libc::c_int != 0 {
            num_filters += 1;
            num_filters;
        }
        if filters as libc::c_int & 0x40 as libc::c_int != 0 {
            num_filters += 1;
            num_filters;
        }
        if filters as libc::c_int & 0x80 as libc::c_int != 0 {
            num_filters += 1;
            num_filters;
        }
        if num_filters > 1 as libc::c_int {
            (*png_ptr)
                .tst_row = png_malloc(png_ptr as png_const_structrp, buf_size)
                as png_bytep;
        }
    }
    if filters as libc::c_int
        & (0x40 as libc::c_int | 0x20 as libc::c_int | 0x80 as libc::c_int)
        != 0 as libc::c_int
    {
        (*png_ptr)
            .prev_row = png_calloc(png_ptr as png_const_structrp, buf_size) as png_bytep;
    }
    if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int {
        if (*png_ptr).transformations & 0x2 as libc::c_uint
            == 0 as libc::c_int as libc::c_uint
        {
            (*png_ptr)
                .num_rows = ((*png_ptr).height)
                .wrapping_add(png_pass_yinc[0 as libc::c_int as usize] as png_uint_32)
                .wrapping_sub(1 as libc::c_int as png_uint_32)
                .wrapping_sub(png_pass_ystart[0 as libc::c_int as usize] as png_uint_32)
                / png_pass_yinc[0 as libc::c_int as usize] as png_uint_32;
            (*png_ptr)
                .usr_width = ((*png_ptr).width)
                .wrapping_add(png_pass_inc[0 as libc::c_int as usize] as png_uint_32)
                .wrapping_sub(1 as libc::c_int as png_uint_32)
                .wrapping_sub(png_pass_start[0 as libc::c_int as usize] as png_uint_32)
                / png_pass_inc[0 as libc::c_int as usize] as png_uint_32;
        } else {
            (*png_ptr).num_rows = (*png_ptr).height;
            (*png_ptr).usr_width = (*png_ptr).width;
        }
    } else {
        (*png_ptr).num_rows = (*png_ptr).height;
        (*png_ptr).usr_width = (*png_ptr).width;
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_write_finish_row(mut png_ptr: png_structrp) {
    static mut png_pass_start: [png_byte; 7] = [
        0 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
    ];
    static mut png_pass_inc: [png_byte; 7] = [
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
    ];
    static mut png_pass_ystart: [png_byte; 7] = [
        0 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
    ];
    static mut png_pass_yinc: [png_byte; 7] = [
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
    ];
    (*png_ptr).row_number = ((*png_ptr).row_number).wrapping_add(1);
    (*png_ptr).row_number;
    if (*png_ptr).row_number < (*png_ptr).num_rows {
        return;
    }
    if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int {
        (*png_ptr).row_number = 0 as libc::c_int as png_uint_32;
        if (*png_ptr).transformations & 0x2 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
        {
            (*png_ptr).pass = ((*png_ptr).pass).wrapping_add(1);
            (*png_ptr).pass;
        } else {
            loop {
                (*png_ptr).pass = ((*png_ptr).pass).wrapping_add(1);
                (*png_ptr).pass;
                if (*png_ptr).pass as libc::c_int >= 7 as libc::c_int {
                    break;
                }
                (*png_ptr)
                    .usr_width = ((*png_ptr).width)
                    .wrapping_add(png_pass_inc[(*png_ptr).pass as usize] as png_uint_32)
                    .wrapping_sub(1 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        png_pass_start[(*png_ptr).pass as usize] as png_uint_32,
                    ) / png_pass_inc[(*png_ptr).pass as usize] as png_uint_32;
                (*png_ptr)
                    .num_rows = ((*png_ptr).height)
                    .wrapping_add(png_pass_yinc[(*png_ptr).pass as usize] as png_uint_32)
                    .wrapping_sub(1 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        png_pass_ystart[(*png_ptr).pass as usize] as png_uint_32,
                    ) / png_pass_yinc[(*png_ptr).pass as usize] as png_uint_32;
                if (*png_ptr).transformations & 0x2 as libc::c_uint
                    != 0 as libc::c_int as libc::c_uint
                {
                    break;
                }
                if !((*png_ptr).usr_width == 0 as libc::c_int as png_uint_32
                    || (*png_ptr).num_rows == 0 as libc::c_int as png_uint_32)
                {
                    break;
                }
            }
        }
        if ((*png_ptr).pass as libc::c_int) < 7 as libc::c_int {
            if !((*png_ptr).prev_row).is_null() {
                memset(
                    (*png_ptr).prev_row as *mut libc::c_void,
                    0 as libc::c_int,
                    (if (*png_ptr).usr_channels as libc::c_int
                        * (*png_ptr).usr_bit_depth as libc::c_int >= 8 as libc::c_int
                    {
                        (*png_ptr).width as size_t
                            * (((*png_ptr).usr_channels as libc::c_int
                                * (*png_ptr).usr_bit_depth as libc::c_int) as size_t
                                >> 3 as libc::c_int)
                    } else {
                        ((*png_ptr).width as size_t
                            * ((*png_ptr).usr_channels as libc::c_int
                                * (*png_ptr).usr_bit_depth as libc::c_int) as size_t)
                            .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
                    })
                        .wrapping_add(1 as libc::c_int as size_t),
                );
            }
            return;
        }
    }
    png_compress_IDAT(
        png_ptr,
        0 as png_const_bytep,
        0 as libc::c_int as png_alloc_size_t,
        4 as libc::c_int,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_do_write_interlace(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut pass: libc::c_int,
) {
    static mut png_pass_start: [png_byte; 7] = [
        0 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
        0 as libc::c_int as png_byte,
    ];
    static mut png_pass_inc: [png_byte; 7] = [
        8 as libc::c_int as png_byte,
        8 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        4 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        2 as libc::c_int as png_byte,
        1 as libc::c_int as png_byte,
    ];
    if pass < 6 as libc::c_int {
        match (*row_info).pixel_depth as libc::c_int {
            1 => {
                let mut sp: png_bytep = 0 as *mut png_byte;
                let mut dp: png_bytep = 0 as *mut png_byte;
                let mut shift: libc::c_uint = 0;
                let mut d: libc::c_int = 0;
                let mut value: libc::c_int = 0;
                let mut i: png_uint_32 = 0;
                let mut row_width: png_uint_32 = (*row_info).width;
                dp = row;
                d = 0 as libc::c_int;
                shift = 7 as libc::c_int as libc::c_uint;
                i = png_pass_start[pass as usize] as png_uint_32;
                while i < row_width {
                    sp = row.offset((i >> 3 as libc::c_int) as size_t as isize);
                    value = *sp as libc::c_int
                        >> 7 as libc::c_int
                            - (i & 0x7 as libc::c_int as png_uint_32) as libc::c_int
                        & 0x1 as libc::c_int;
                    d |= value << shift;
                    if shift == 0 as libc::c_int as libc::c_uint {
                        shift = 7 as libc::c_int as libc::c_uint;
                        let fresh1 = dp;
                        dp = dp.offset(1);
                        *fresh1 = d as png_byte;
                        d = 0 as libc::c_int;
                    } else {
                        shift = shift.wrapping_sub(1);
                        shift;
                    }
                    i = i.wrapping_add(png_pass_inc[pass as usize] as png_uint_32);
                }
                if shift != 7 as libc::c_int as libc::c_uint {
                    *dp = d as png_byte;
                }
            }
            2 => {
                let mut sp_0: png_bytep = 0 as *mut png_byte;
                let mut dp_0: png_bytep = 0 as *mut png_byte;
                let mut shift_0: libc::c_uint = 0;
                let mut d_0: libc::c_int = 0;
                let mut value_0: libc::c_int = 0;
                let mut i_0: png_uint_32 = 0;
                let mut row_width_0: png_uint_32 = (*row_info).width;
                dp_0 = row;
                shift_0 = 6 as libc::c_int as libc::c_uint;
                d_0 = 0 as libc::c_int;
                i_0 = png_pass_start[pass as usize] as png_uint_32;
                while i_0 < row_width_0 {
                    sp_0 = row.offset((i_0 >> 2 as libc::c_int) as size_t as isize);
                    value_0 = *sp_0 as libc::c_int
                        >> ((3 as libc::c_int
                            - (i_0 & 0x3 as libc::c_int as png_uint_32) as libc::c_int)
                            << 1 as libc::c_int) & 0x3 as libc::c_int;
                    d_0 |= value_0 << shift_0;
                    if shift_0 == 0 as libc::c_int as libc::c_uint {
                        shift_0 = 6 as libc::c_int as libc::c_uint;
                        let fresh2 = dp_0;
                        dp_0 = dp_0.offset(1);
                        *fresh2 = d_0 as png_byte;
                        d_0 = 0 as libc::c_int;
                    } else {
                        shift_0 = shift_0.wrapping_sub(2 as libc::c_int as libc::c_uint);
                    }
                    i_0 = i_0.wrapping_add(png_pass_inc[pass as usize] as png_uint_32);
                }
                if shift_0 != 6 as libc::c_int as libc::c_uint {
                    *dp_0 = d_0 as png_byte;
                }
            }
            4 => {
                let mut sp_1: png_bytep = 0 as *mut png_byte;
                let mut dp_1: png_bytep = 0 as *mut png_byte;
                let mut shift_1: libc::c_uint = 0;
                let mut d_1: libc::c_int = 0;
                let mut value_1: libc::c_int = 0;
                let mut i_1: png_uint_32 = 0;
                let mut row_width_1: png_uint_32 = (*row_info).width;
                dp_1 = row;
                shift_1 = 4 as libc::c_int as libc::c_uint;
                d_1 = 0 as libc::c_int;
                i_1 = png_pass_start[pass as usize] as png_uint_32;
                while i_1 < row_width_1 {
                    sp_1 = row.offset((i_1 >> 1 as libc::c_int) as size_t as isize);
                    value_1 = *sp_1 as libc::c_int
                        >> ((1 as libc::c_int
                            - (i_1 & 0x1 as libc::c_int as png_uint_32) as libc::c_int)
                            << 2 as libc::c_int) & 0xf as libc::c_int;
                    d_1 |= value_1 << shift_1;
                    if shift_1 == 0 as libc::c_int as libc::c_uint {
                        shift_1 = 4 as libc::c_int as libc::c_uint;
                        let fresh3 = dp_1;
                        dp_1 = dp_1.offset(1);
                        *fresh3 = d_1 as png_byte;
                        d_1 = 0 as libc::c_int;
                    } else {
                        shift_1 = shift_1.wrapping_sub(4 as libc::c_int as libc::c_uint);
                    }
                    i_1 = i_1.wrapping_add(png_pass_inc[pass as usize] as png_uint_32);
                }
                if shift_1 != 4 as libc::c_int as libc::c_uint {
                    *dp_1 = d_1 as png_byte;
                }
            }
            _ => {
                let mut sp_2: png_bytep = 0 as *mut png_byte;
                let mut dp_2: png_bytep = 0 as *mut png_byte;
                let mut i_2: png_uint_32 = 0;
                let mut row_width_2: png_uint_32 = (*row_info).width;
                let mut pixel_bytes: size_t = 0;
                dp_2 = row;
                pixel_bytes = ((*row_info).pixel_depth as libc::c_int
                    >> 3 as libc::c_int) as size_t;
                i_2 = png_pass_start[pass as usize] as png_uint_32;
                while i_2 < row_width_2 {
                    sp_2 = row.offset((i_2 as size_t * pixel_bytes) as isize);
                    if dp_2 != sp_2 {
                        memcpy(
                            dp_2 as *mut libc::c_void,
                            sp_2 as *const libc::c_void,
                            pixel_bytes,
                        );
                    }
                    dp_2 = dp_2.offset(pixel_bytes as isize);
                    i_2 = i_2.wrapping_add(png_pass_inc[pass as usize] as png_uint_32);
                }
            }
        }
        (*row_info)
            .width = ((*row_info).width)
            .wrapping_add(png_pass_inc[pass as usize] as png_uint_32)
            .wrapping_sub(1 as libc::c_int as png_uint_32)
            .wrapping_sub(png_pass_start[pass as usize] as png_uint_32)
            / png_pass_inc[pass as usize] as png_uint_32;
        (*row_info)
            .rowbytes = if (*row_info).pixel_depth as libc::c_int >= 8 as libc::c_int {
            (*row_info).width as size_t
                * ((*row_info).pixel_depth as size_t >> 3 as libc::c_int)
        } else {
            ((*row_info).width as size_t * (*row_info).pixel_depth as size_t)
                .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
        };
    }
}
unsafe extern "C" fn png_setup_sub_row(
    mut png_ptr: png_structrp,
    mut bpp: png_uint_32,
    mut row_bytes: size_t,
    mut lmins: size_t,
) -> size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: size_t = 0;
    let mut sum: size_t = 0 as libc::c_int as size_t;
    let mut v: libc::c_uint = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 1 as libc::c_int as png_byte;
    i = 0 as libc::c_int as size_t;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    while i < bpp as size_t {
        *dp = *rp;
        v = *dp as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
        dp = dp.offset(1);
        dp;
    }
    lp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    while i < row_bytes {
        *dp = (*rp as libc::c_int - *lp as libc::c_int & 0xff as libc::c_int)
            as png_byte;
        v = *dp as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        if sum > lmins {
            break;
        }
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
        lp = lp.offset(1);
        lp;
        dp = dp.offset(1);
        dp;
    }
    return sum;
}
unsafe extern "C" fn png_setup_sub_row_only(
    mut png_ptr: png_structrp,
    mut bpp: png_uint_32,
    mut row_bytes: size_t,
) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: size_t = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 1 as libc::c_int as png_byte;
    i = 0 as libc::c_int as size_t;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    while i < bpp as size_t {
        *dp = *rp;
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
        dp = dp.offset(1);
        dp;
    }
    lp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    while i < row_bytes {
        *dp = (*rp as libc::c_int - *lp as libc::c_int & 0xff as libc::c_int)
            as png_byte;
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
        lp = lp.offset(1);
        lp;
        dp = dp.offset(1);
        dp;
    }
}
unsafe extern "C" fn png_setup_up_row(
    mut png_ptr: png_structrp,
    mut row_bytes: size_t,
    mut lmins: size_t,
) -> size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut i: size_t = 0;
    let mut sum: size_t = 0 as libc::c_int as size_t;
    let mut v: libc::c_uint = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 2 as libc::c_int as png_byte;
    i = 0 as libc::c_int as size_t;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    pp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < row_bytes {
        *dp = (*rp as libc::c_int - *pp as libc::c_int & 0xff as libc::c_int)
            as png_byte;
        v = *dp as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        if sum > lmins {
            break;
        }
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
        pp = pp.offset(1);
        pp;
        dp = dp.offset(1);
        dp;
    }
    return sum;
}
unsafe extern "C" fn png_setup_up_row_only(
    mut png_ptr: png_structrp,
    mut row_bytes: size_t,
) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut i: size_t = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 2 as libc::c_int as png_byte;
    i = 0 as libc::c_int as size_t;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    pp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < row_bytes {
        *dp = (*rp as libc::c_int - *pp as libc::c_int & 0xff as libc::c_int)
            as png_byte;
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
        pp = pp.offset(1);
        pp;
        dp = dp.offset(1);
        dp;
    }
}
unsafe extern "C" fn png_setup_avg_row(
    mut png_ptr: png_structrp,
    mut bpp: png_uint_32,
    mut row_bytes: size_t,
    mut lmins: size_t,
) -> size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_uint_32 = 0;
    let mut sum: size_t = 0 as libc::c_int as size_t;
    let mut v: libc::c_uint = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 3 as libc::c_int as png_byte;
    i = 0 as libc::c_int as png_uint_32;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    pp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < bpp {
        let fresh4 = rp;
        rp = rp.offset(1);
        let fresh5 = pp;
        pp = pp.offset(1);
        let fresh6 = dp;
        dp = dp.offset(1);
        *fresh6 = (*fresh4 as libc::c_int - *fresh5 as libc::c_int / 2 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        v = *fresh6 as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        i = i.wrapping_add(1);
        i;
    }
    lp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    while (i as size_t) < row_bytes {
        let fresh7 = rp;
        rp = rp.offset(1);
        let fresh8 = pp;
        pp = pp.offset(1);
        let fresh9 = lp;
        lp = lp.offset(1);
        let fresh10 = dp;
        dp = dp.offset(1);
        *fresh10 = (*fresh7 as libc::c_int
            - (*fresh8 as libc::c_int + *fresh9 as libc::c_int) / 2 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        v = *fresh10 as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        if sum > lmins {
            break;
        }
        i = i.wrapping_add(1);
        i;
    }
    return sum;
}
unsafe extern "C" fn png_setup_avg_row_only(
    mut png_ptr: png_structrp,
    mut bpp: png_uint_32,
    mut row_bytes: size_t,
) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: png_uint_32 = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 3 as libc::c_int as png_byte;
    i = 0 as libc::c_int as png_uint_32;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    pp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < bpp {
        let fresh11 = rp;
        rp = rp.offset(1);
        let fresh12 = pp;
        pp = pp.offset(1);
        let fresh13 = dp;
        dp = dp.offset(1);
        *fresh13 = (*fresh11 as libc::c_int - *fresh12 as libc::c_int / 2 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        i = i.wrapping_add(1);
        i;
    }
    lp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    while (i as size_t) < row_bytes {
        let fresh14 = rp;
        rp = rp.offset(1);
        let fresh15 = pp;
        pp = pp.offset(1);
        let fresh16 = lp;
        lp = lp.offset(1);
        let fresh17 = dp;
        dp = dp.offset(1);
        *fresh17 = (*fresh14 as libc::c_int
            - (*fresh15 as libc::c_int + *fresh16 as libc::c_int) / 2 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        i = i.wrapping_add(1);
        i;
    }
}
unsafe extern "C" fn png_setup_paeth_row(
    mut png_ptr: png_structrp,
    mut bpp: png_uint_32,
    mut row_bytes: size_t,
    mut lmins: size_t,
) -> size_t {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut cp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: size_t = 0;
    let mut sum: size_t = 0 as libc::c_int as size_t;
    let mut v: libc::c_uint = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 4 as libc::c_int as png_byte;
    i = 0 as libc::c_int as size_t;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    pp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < bpp as size_t {
        let fresh18 = rp;
        rp = rp.offset(1);
        let fresh19 = pp;
        pp = pp.offset(1);
        let fresh20 = dp;
        dp = dp.offset(1);
        *fresh20 = (*fresh18 as libc::c_int - *fresh19 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        v = *fresh20 as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        i = i.wrapping_add(1);
        i;
    }
    lp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    cp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < row_bytes {
        let mut a: libc::c_int = 0;
        let mut b: libc::c_int = 0;
        let mut c: libc::c_int = 0;
        let mut pa: libc::c_int = 0;
        let mut pb: libc::c_int = 0;
        let mut pc: libc::c_int = 0;
        let mut p: libc::c_int = 0;
        let fresh21 = pp;
        pp = pp.offset(1);
        b = *fresh21 as libc::c_int;
        let fresh22 = cp;
        cp = cp.offset(1);
        c = *fresh22 as libc::c_int;
        let fresh23 = lp;
        lp = lp.offset(1);
        a = *fresh23 as libc::c_int;
        p = b - c;
        pc = a - c;
        pa = if p < 0 as libc::c_int { -p } else { p };
        pb = if pc < 0 as libc::c_int { -pc } else { pc };
        pc = if p + pc < 0 as libc::c_int { -(p + pc) } else { p + pc };
        p = if pa <= pb && pa <= pc { a } else if pb <= pc { b } else { c };
        let fresh24 = rp;
        rp = rp.offset(1);
        let fresh25 = dp;
        dp = dp.offset(1);
        *fresh25 = (*fresh24 as libc::c_int - p & 0xff as libc::c_int) as png_byte;
        v = *fresh25 as libc::c_uint;
        sum = sum
            .wrapping_add(
                (if v < 128 as libc::c_int as libc::c_uint {
                    v
                } else {
                    (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                }) as size_t,
            );
        if sum > lmins {
            break;
        }
        i = i.wrapping_add(1);
        i;
    }
    return sum;
}
unsafe extern "C" fn png_setup_paeth_row_only(
    mut png_ptr: png_structrp,
    mut bpp: png_uint_32,
    mut row_bytes: size_t,
) {
    let mut rp: png_bytep = 0 as *mut png_byte;
    let mut dp: png_bytep = 0 as *mut png_byte;
    let mut pp: png_bytep = 0 as *mut png_byte;
    let mut cp: png_bytep = 0 as *mut png_byte;
    let mut lp: png_bytep = 0 as *mut png_byte;
    let mut i: size_t = 0;
    *((*png_ptr).try_row)
        .offset(0 as libc::c_int as isize) = 4 as libc::c_int as png_byte;
    i = 0 as libc::c_int as size_t;
    rp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    dp = ((*png_ptr).try_row).offset(1 as libc::c_int as isize);
    pp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < bpp as size_t {
        let fresh26 = rp;
        rp = rp.offset(1);
        let fresh27 = pp;
        pp = pp.offset(1);
        let fresh28 = dp;
        dp = dp.offset(1);
        *fresh28 = (*fresh26 as libc::c_int - *fresh27 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        i = i.wrapping_add(1);
        i;
    }
    lp = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize);
    cp = ((*png_ptr).prev_row).offset(1 as libc::c_int as isize);
    while i < row_bytes {
        let mut a: libc::c_int = 0;
        let mut b: libc::c_int = 0;
        let mut c: libc::c_int = 0;
        let mut pa: libc::c_int = 0;
        let mut pb: libc::c_int = 0;
        let mut pc: libc::c_int = 0;
        let mut p: libc::c_int = 0;
        let fresh29 = pp;
        pp = pp.offset(1);
        b = *fresh29 as libc::c_int;
        let fresh30 = cp;
        cp = cp.offset(1);
        c = *fresh30 as libc::c_int;
        let fresh31 = lp;
        lp = lp.offset(1);
        a = *fresh31 as libc::c_int;
        p = b - c;
        pc = a - c;
        pa = if p < 0 as libc::c_int { -p } else { p };
        pb = if pc < 0 as libc::c_int { -pc } else { pc };
        pc = if p + pc < 0 as libc::c_int { -(p + pc) } else { p + pc };
        p = if pa <= pb && pa <= pc { a } else if pb <= pc { b } else { c };
        let fresh32 = rp;
        rp = rp.offset(1);
        let fresh33 = dp;
        dp = dp.offset(1);
        *fresh33 = (*fresh32 as libc::c_int - p & 0xff as libc::c_int) as png_byte;
        i = i.wrapping_add(1);
        i;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_find_filter(
    mut png_ptr: png_structrp,
    mut row_info: png_row_infop,
) {
    let mut filter_to_do: libc::c_uint = (*png_ptr).do_filter as libc::c_uint;
    let mut row_buf: png_bytep = 0 as *mut png_byte;
    let mut best_row: png_bytep = 0 as *mut png_byte;
    let mut bpp: png_uint_32 = 0;
    let mut mins: size_t = 0;
    let mut row_bytes: size_t = (*row_info).rowbytes;
    bpp = ((*row_info).pixel_depth as libc::c_int + 7 as libc::c_int >> 3 as libc::c_int)
        as png_uint_32;
    row_buf = (*png_ptr).row_buf;
    mins = (-(1 as libc::c_int) as size_t).wrapping_sub(256 as libc::c_int as size_t);
    best_row = (*png_ptr).row_buf;
    if -(1 as libc::c_int) as size_t / 128 as libc::c_int as size_t <= row_bytes {
        filter_to_do &= (0 as libc::c_uint).wrapping_sub(filter_to_do);
    } else if filter_to_do & 0x8 as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
        && filter_to_do != 0x8 as libc::c_int as libc::c_uint
    {
        let mut rp: png_bytep = 0 as *mut png_byte;
        let mut sum: size_t = 0 as libc::c_int as size_t;
        let mut i: size_t = 0;
        let mut v: libc::c_uint = 0;
        i = 0 as libc::c_int as size_t;
        rp = row_buf.offset(1 as libc::c_int as isize);
        while i < row_bytes {
            v = *rp as libc::c_uint;
            sum = sum
                .wrapping_add(
                    (if v < 128 as libc::c_int as libc::c_uint {
                        v
                    } else {
                        (256 as libc::c_int as libc::c_uint).wrapping_sub(v)
                    }) as size_t,
                );
            i = i.wrapping_add(1);
            i;
            rp = rp.offset(1);
            rp;
        }
        mins = sum;
    }
    if filter_to_do == 0x10 as libc::c_int as libc::c_uint {
        png_setup_sub_row_only(png_ptr, bpp, row_bytes);
        best_row = (*png_ptr).try_row;
    } else if filter_to_do & 0x10 as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        let mut sum_0: size_t = 0;
        let mut lmins: size_t = mins;
        sum_0 = png_setup_sub_row(png_ptr, bpp, row_bytes, lmins);
        if sum_0 < mins {
            mins = sum_0;
            best_row = (*png_ptr).try_row;
            if !((*png_ptr).tst_row).is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row;
            }
        }
    }
    if filter_to_do == 0x20 as libc::c_int as libc::c_uint {
        png_setup_up_row_only(png_ptr, row_bytes);
        best_row = (*png_ptr).try_row;
    } else if filter_to_do & 0x20 as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        let mut sum_1: size_t = 0;
        let mut lmins_0: size_t = mins;
        sum_1 = png_setup_up_row(png_ptr, row_bytes, lmins_0);
        if sum_1 < mins {
            mins = sum_1;
            best_row = (*png_ptr).try_row;
            if !((*png_ptr).tst_row).is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row;
            }
        }
    }
    if filter_to_do == 0x40 as libc::c_int as libc::c_uint {
        png_setup_avg_row_only(png_ptr, bpp, row_bytes);
        best_row = (*png_ptr).try_row;
    } else if filter_to_do & 0x40 as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        let mut sum_2: size_t = 0;
        let mut lmins_1: size_t = mins;
        sum_2 = png_setup_avg_row(png_ptr, bpp, row_bytes, lmins_1);
        if sum_2 < mins {
            mins = sum_2;
            best_row = (*png_ptr).try_row;
            if !((*png_ptr).tst_row).is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row;
            }
        }
    }
    if filter_to_do == 0x80 as libc::c_int as libc::c_uint {
        png_setup_paeth_row_only(png_ptr, bpp, row_bytes);
        best_row = (*png_ptr).try_row;
    } else if filter_to_do & 0x80 as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        let mut sum_3: size_t = 0;
        let mut lmins_2: size_t = mins;
        sum_3 = png_setup_paeth_row(png_ptr, bpp, row_bytes, lmins_2);
        if sum_3 < mins {
            best_row = (*png_ptr).try_row;
            if !((*png_ptr).tst_row).is_null() {
                (*png_ptr).try_row = (*png_ptr).tst_row;
                (*png_ptr).tst_row = best_row;
            }
        }
    }
    png_write_filtered_row(
        png_ptr,
        best_row,
        ((*row_info).rowbytes).wrapping_add(1 as libc::c_int as size_t),
    );
}
unsafe extern "C" fn png_write_filtered_row(
    mut png_ptr: png_structrp,
    mut filtered_row: png_bytep,
    mut full_row_length: size_t,
) {
    png_compress_IDAT(
        png_ptr,
        filtered_row as png_const_bytep,
        full_row_length,
        0 as libc::c_int,
    );
    if !((*png_ptr).prev_row).is_null() {
        let mut tptr: png_bytep = 0 as *mut png_byte;
        tptr = (*png_ptr).prev_row;
        (*png_ptr).prev_row = (*png_ptr).row_buf;
        (*png_ptr).row_buf = tptr;
    }
    png_write_finish_row(png_ptr);
    (*png_ptr).flush_rows = ((*png_ptr).flush_rows).wrapping_add(1);
    (*png_ptr).flush_rows;
    if (*png_ptr).flush_dist > 0 as libc::c_int as png_uint_32
        && (*png_ptr).flush_rows >= (*png_ptr).flush_dist
    {
        png_write_flush(png_ptr);
    }
}
