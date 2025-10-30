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
    fn png_malloc_base(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_reset_crc(png_ptr: png_structrp);
    fn png_read_data(png_ptr: png_structrp, data: png_bytep, length: size_t);
    fn png_calculate_crc(png_ptr: png_structrp, ptr: png_const_bytep, length: size_t);
    fn png_init_read_transformations(png_ptr: png_structrp);
    fn png_safecat(
        buffer: png_charp,
        bufsize: size_t,
        pos: size_t,
        string: png_const_charp,
    ) -> size_t;
    fn png_sig_cmp(
        sig: png_const_bytep,
        start: size_t,
        num_to_check: size_t,
    ) -> libc::c_int;
    fn png_malloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_calloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_malloc_warn(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_free(png_ptr: png_const_structrp, ptr: png_voidp);
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_chunk_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_chunk_warning(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_benign_error(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_chunk_benign_error(
        png_ptr: png_const_structrp,
        warning_message: png_const_charp,
    );
    fn png_set_bKGD(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        background: png_const_color_16p,
    );
    fn png_set_hIST(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        hist: png_const_uint_16p,
    );
    fn png_set_IHDR(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        width: png_uint_32,
        height: png_uint_32,
        bit_depth: libc::c_int,
        color_type: libc::c_int,
        interlace_method: libc::c_int,
        compression_method: libc::c_int,
        filter_method: libc::c_int,
    );
    fn png_set_PLTE(
        png_ptr: png_structrp,
        info_ptr: png_inforp,
        palette: png_const_colorp,
        num_palette: libc::c_int,
    );
    fn png_set_sBIT(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        sig_bit: png_const_color_8p,
    );
    fn png_set_tRNS(
        png_ptr: png_structrp,
        info_ptr: png_inforp,
        trans_alpha: png_const_bytep,
        num_trans: libc::c_int,
        trans_color: png_const_color_16p,
    );
    fn png_set_unknown_chunks(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        unknowns: png_const_unknown_chunkp,
        num_unknowns: libc::c_int,
    );
    fn inflate(strm: z_streamp, flush: libc::c_int) -> libc::c_int;
    fn inflateReset2(strm: z_streamp, windowBits: libc::c_int) -> libc::c_int;
    fn inflateInit2_(
        strm: z_streamp,
        windowBits: libc::c_int,
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
pub type png_uint_32p = *mut png_uint_32;
pub type png_const_uint_32p = *const png_uint_32;
pub type png_uint_16p = *mut png_uint_16;
pub type png_const_uint_16p = *const png_uint_16;
pub type png_charp = *mut libc::c_char;
pub type png_const_charp = *const libc::c_char;
pub type png_bytepp = *mut *mut png_byte;
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
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_info_def {
    pub width: png_uint_32,
    pub height: png_uint_32,
    pub valid: png_uint_32,
    pub rowbytes: size_t,
    pub palette: png_colorp,
    pub num_palette: png_uint_16,
    pub num_trans: png_uint_16,
    pub bit_depth: png_byte,
    pub color_type: png_byte,
    pub compression_type: png_byte,
    pub filter_type: png_byte,
    pub interlace_type: png_byte,
    pub channels: png_byte,
    pub pixel_depth: png_byte,
    pub spare_byte: png_byte,
    pub signature: [png_byte; 8],
    pub sig_bit: png_color_8,
    pub trans_alpha: png_bytep,
    pub trans_color: png_color_16,
    pub background: png_color_16,
    pub hist: png_uint_16p,
    pub free_me: png_uint_32,
    pub unknown_chunks: png_unknown_chunkp,
    pub unknown_chunks_num: libc::c_int,
    pub row_pointers: png_bytepp,
}
pub type png_unknown_chunkp = *mut png_unknown_chunk;
pub type png_info = png_info_def;
pub type png_structrp = *mut png_struct;
pub type png_const_structrp = *const png_struct;
pub type png_inforp = *mut png_info;
pub type png_const_colorp = *const png_color;
pub type png_const_color_16p = *const png_color_16;
pub type png_const_color_8p = *const png_color_8;
pub type png_const_unknown_chunkp = *const png_unknown_chunk;
pub type z_streamp = *mut z_stream;
#[no_mangle]
pub unsafe extern "C" fn png_get_uint_31(
    mut png_ptr: png_const_structrp,
    mut buf: png_const_bytep,
) -> png_uint_32 {
    let mut uval: png_uint_32 = ((*buf as png_uint_32) << 24 as libc::c_int)
        .wrapping_add(
            (*buf.offset(1 as libc::c_int as isize) as png_uint_32) << 16 as libc::c_int,
        )
        .wrapping_add(
            (*buf.offset(2 as libc::c_int as isize) as png_uint_32) << 8 as libc::c_int,
        )
        .wrapping_add(*buf.offset(3 as libc::c_int as isize) as png_uint_32);
    if uval > 0x7fffffff as libc::c_long as png_uint_32 {
        png_error(
            png_ptr,
            b"PNG unsigned integer out of range\0" as *const u8 as *const libc::c_char,
        );
    }
    return uval;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_uint_32(mut buf: png_const_bytep) -> png_uint_32 {
    let mut uval: png_uint_32 = ((*buf as png_uint_32) << 24 as libc::c_int)
        .wrapping_add(
            (*buf.offset(1 as libc::c_int as isize) as png_uint_32) << 16 as libc::c_int,
        )
        .wrapping_add(
            (*buf.offset(2 as libc::c_int as isize) as png_uint_32) << 8 as libc::c_int,
        )
        .wrapping_add(*buf.offset(3 as libc::c_int as isize) as png_uint_32);
    return uval;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_int_32(mut buf: png_const_bytep) -> png_int_32 {
    let mut uval: png_uint_32 = ((*buf as png_uint_32) << 24 as libc::c_int)
        .wrapping_add(
            (*buf.offset(1 as libc::c_int as isize) as png_uint_32) << 16 as libc::c_int,
        )
        .wrapping_add(
            (*buf.offset(2 as libc::c_int as isize) as png_uint_32) << 8 as libc::c_int,
        )
        .wrapping_add(*buf.offset(3 as libc::c_int as isize) as png_uint_32);
    if uval & 0x80000000 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        return uval as png_int_32;
    }
    uval = (uval ^ 0xffffffff as libc::c_uint)
        .wrapping_add(1 as libc::c_int as libc::c_uint);
    if uval & 0x80000000 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        return -(uval as png_int_32);
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_uint_16(mut buf: png_const_bytep) -> png_uint_16 {
    let mut val: libc::c_uint = ((*buf as libc::c_uint) << 8 as libc::c_int)
        .wrapping_add(*buf.offset(1 as libc::c_int as isize) as libc::c_uint);
    return val as png_uint_16;
}
#[no_mangle]
pub unsafe extern "C" fn png_read_sig(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
) {
    let mut num_checked: size_t = 0;
    let mut num_to_check: size_t = 0;
    if (*png_ptr).sig_bytes as libc::c_int >= 8 as libc::c_int {
        return;
    }
    num_checked = (*png_ptr).sig_bytes as size_t;
    num_to_check = (8 as libc::c_int as size_t).wrapping_sub(num_checked);
    (*png_ptr).io_state = (0x1 as libc::c_int | 0x10 as libc::c_int) as png_uint_32;
    png_read_data(
        png_ptr,
        &mut *((*info_ptr).signature).as_mut_ptr().offset(num_checked as isize),
        num_to_check,
    );
    (*png_ptr).sig_bytes = 8 as libc::c_int as png_byte;
    if png_sig_cmp(
        ((*info_ptr).signature).as_mut_ptr() as png_const_bytep,
        num_checked,
        num_to_check,
    ) != 0 as libc::c_int
    {
        if num_checked < 4 as libc::c_int as size_t
            && png_sig_cmp(
                ((*info_ptr).signature).as_mut_ptr() as png_const_bytep,
                num_checked,
                num_to_check.wrapping_sub(4 as libc::c_int as size_t),
            ) != 0
        {
            png_error(
                png_ptr as png_const_structrp,
                b"Not a PNG file\0" as *const u8 as *const libc::c_char,
            );
        } else {
            png_error(
                png_ptr as png_const_structrp,
                b"PNG file corrupted by ASCII conversion\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
    if num_checked < 3 as libc::c_int as size_t {
        (*png_ptr).mode |= 0x1000 as libc::c_uint;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_chunk_header(
    mut png_ptr: png_structrp,
) -> png_uint_32 {
    let mut buf: [png_byte; 8] = [0; 8];
    let mut length: png_uint_32 = 0;
    (*png_ptr).io_state = (0x1 as libc::c_int | 0x20 as libc::c_int) as png_uint_32;
    png_read_data(png_ptr, buf.as_mut_ptr(), 8 as libc::c_int as size_t);
    length = png_get_uint_31(
        png_ptr as png_const_structrp,
        buf.as_mut_ptr() as png_const_bytep,
    );
    (*png_ptr)
        .chunk_name = ((0xff as libc::c_int
        & *buf
            .as_mut_ptr()
            .offset(4 as libc::c_int as isize)
            .offset(0 as libc::c_int as isize) as libc::c_int) as png_uint_32)
        << 24 as libc::c_int
        | ((0xff as libc::c_int
            & *buf
                .as_mut_ptr()
                .offset(4 as libc::c_int as isize)
                .offset(1 as libc::c_int as isize) as libc::c_int) as png_uint_32)
            << 16 as libc::c_int
        | ((0xff as libc::c_int
            & *buf
                .as_mut_ptr()
                .offset(4 as libc::c_int as isize)
                .offset(2 as libc::c_int as isize) as libc::c_int) as png_uint_32)
            << 8 as libc::c_int
        | ((0xff as libc::c_int
            & *buf
                .as_mut_ptr()
                .offset(4 as libc::c_int as isize)
                .offset(3 as libc::c_int as isize) as libc::c_int) as png_uint_32)
            << 0 as libc::c_int;
    png_reset_crc(png_ptr);
    png_calculate_crc(
        png_ptr,
        buf.as_mut_ptr().offset(4 as libc::c_int as isize) as png_const_bytep,
        4 as libc::c_int as size_t,
    );
    png_check_chunk_name(png_ptr as png_const_structrp, (*png_ptr).chunk_name);
    png_check_chunk_length(png_ptr as png_const_structrp, length);
    (*png_ptr).io_state = (0x1 as libc::c_int | 0x40 as libc::c_int) as png_uint_32;
    return length;
}
#[no_mangle]
pub unsafe extern "C" fn png_crc_read(
    mut png_ptr: png_structrp,
    mut buf: png_bytep,
    mut length: png_uint_32,
) {
    if png_ptr.is_null() {
        return;
    }
    png_read_data(png_ptr, buf, length as size_t);
    png_calculate_crc(png_ptr, buf as png_const_bytep, length as size_t);
}
#[no_mangle]
pub unsafe extern "C" fn png_crc_finish(
    mut png_ptr: png_structrp,
    mut skip: png_uint_32,
) -> libc::c_int {
    while skip > 0 as libc::c_int as png_uint_32 {
        let mut len: png_uint_32 = 0;
        let mut tmpbuf: [png_byte; 1024] = [0; 1024];
        len = ::core::mem::size_of::<[png_byte; 1024]>() as libc::c_ulong as png_uint_32;
        if len > skip {
            len = skip;
        }
        skip = skip.wrapping_sub(len);
        png_crc_read(png_ptr, tmpbuf.as_mut_ptr(), len);
    }
    if png_crc_error(png_ptr) != 0 as libc::c_int {
        if if 1 as libc::c_int as png_uint_32
            & (*png_ptr).chunk_name >> 29 as libc::c_int
            != 0 as libc::c_int as png_uint_32
        {
            ((*png_ptr).flags & 0x200 as libc::c_uint
                == 0 as libc::c_int as libc::c_uint) as libc::c_int
        } else {
            ((*png_ptr).flags & 0x400 as libc::c_uint
                != 0 as libc::c_int as libc::c_uint) as libc::c_int
        } != 0
        {
            png_chunk_warning(
                png_ptr as png_const_structrp,
                b"CRC error\0" as *const u8 as *const libc::c_char,
            );
        } else {
            png_chunk_error(
                png_ptr as png_const_structrp,
                b"CRC error\0" as *const u8 as *const libc::c_char,
            );
        }
        return 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn png_crc_error(mut png_ptr: png_structrp) -> libc::c_int {
    let mut crc_bytes: [png_byte; 4] = [0; 4];
    let mut crc: png_uint_32 = 0;
    let mut need_crc: libc::c_int = 1 as libc::c_int;
    if 1 as libc::c_int as png_uint_32 & (*png_ptr).chunk_name >> 29 as libc::c_int
        != 0 as libc::c_int as png_uint_32
    {
        if (*png_ptr).flags & (0x100 as libc::c_uint | 0x200 as libc::c_uint)
            == 0x100 as libc::c_uint | 0x200 as libc::c_uint
        {
            need_crc = 0 as libc::c_int;
        }
    } else if (*png_ptr).flags & 0x800 as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        need_crc = 0 as libc::c_int;
    }
    (*png_ptr).io_state = (0x1 as libc::c_int | 0x80 as libc::c_int) as png_uint_32;
    png_read_data(png_ptr, crc_bytes.as_mut_ptr(), 4 as libc::c_int as size_t);
    if need_crc != 0 as libc::c_int {
        crc = ((*crc_bytes.as_mut_ptr() as png_uint_32) << 24 as libc::c_int)
            .wrapping_add(
                (*crc_bytes.as_mut_ptr().offset(1 as libc::c_int as isize)
                    as png_uint_32) << 16 as libc::c_int,
            )
            .wrapping_add(
                (*crc_bytes.as_mut_ptr().offset(2 as libc::c_int as isize)
                    as png_uint_32) << 8 as libc::c_int,
            )
            .wrapping_add(
                *crc_bytes.as_mut_ptr().offset(3 as libc::c_int as isize) as png_uint_32,
            );
        return (crc != (*png_ptr).crc) as libc::c_int;
    } else {
        return 0 as libc::c_int
    };
}
unsafe extern "C" fn png_read_buffer(
    mut png_ptr: png_structrp,
    mut new_size: png_alloc_size_t,
    mut warn: libc::c_int,
) -> png_bytep {
    let mut buffer: png_bytep = (*png_ptr).read_buffer;
    if !buffer.is_null() && new_size > (*png_ptr).read_buffer_size {
        (*png_ptr).read_buffer = 0 as png_bytep;
        (*png_ptr).read_buffer_size = 0 as libc::c_int as png_alloc_size_t;
        png_free(png_ptr as png_const_structrp, buffer as png_voidp);
        buffer = 0 as png_bytep;
    }
    if buffer.is_null() {
        buffer = png_malloc_base(png_ptr as png_const_structrp, new_size) as png_bytep;
        if !buffer.is_null() {
            memset(buffer as *mut libc::c_void, 0 as libc::c_int, new_size);
            (*png_ptr).read_buffer = buffer;
            (*png_ptr).read_buffer_size = new_size;
        } else if warn < 2 as libc::c_int {
            if warn != 0 as libc::c_int {
                png_chunk_warning(
                    png_ptr as png_const_structrp,
                    b"insufficient memory to read chunk\0" as *const u8
                        as *const libc::c_char,
                );
            } else {
                png_chunk_error(
                    png_ptr as png_const_structrp,
                    b"insufficient memory to read chunk\0" as *const u8
                        as *const libc::c_char,
                );
            }
        }
    }
    return buffer;
}
unsafe extern "C" fn png_inflate_claim(
    mut png_ptr: png_structrp,
    mut owner: png_uint_32,
) -> libc::c_int {
    if (*png_ptr).zowner != 0 as libc::c_int as png_uint_32 {
        let mut msg: [libc::c_char; 64] = [0; 64];
        *msg
            .as_mut_ptr()
            .offset(
                0 as libc::c_int as isize,
            ) = ((*png_ptr).zowner >> 24 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(
                1 as libc::c_int as isize,
            ) = ((*png_ptr).zowner >> 16 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(
                2 as libc::c_int as isize,
            ) = ((*png_ptr).zowner >> 8 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *msg
            .as_mut_ptr()
            .offset(
                3 as libc::c_int as isize,
            ) = ((*png_ptr).zowner & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        png_safecat(
            msg.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 64]>() as libc::c_ulong,
            4 as libc::c_int as size_t,
            b" using zstream\0" as *const u8 as *const libc::c_char,
        );
        png_chunk_warning(
            png_ptr as png_const_structrp,
            msg.as_mut_ptr() as png_const_charp,
        );
        (*png_ptr).zowner = 0 as libc::c_int as png_uint_32;
    }
    let mut ret: libc::c_int = 0;
    let mut window_bits: libc::c_int = 0 as libc::c_int;
    (*png_ptr).zstream.next_in = 0 as *const Bytef;
    (*png_ptr).zstream.avail_in = 0 as libc::c_int as uInt;
    (*png_ptr).zstream.next_out = 0 as *mut Bytef;
    (*png_ptr).zstream.avail_out = 0 as libc::c_int as uInt;
    if (*png_ptr).flags & 0x2 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        ret = inflateReset2(&mut (*png_ptr).zstream, window_bits);
    } else {
        ret = inflateInit2_(
            &mut (*png_ptr).zstream,
            window_bits,
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
pub unsafe extern "C" fn png_zlib_inflate(
    mut png_ptr: png_structrp,
    mut flush: libc::c_int,
) -> libc::c_int {
    if (*png_ptr).zstream_start as libc::c_int != 0
        && (*png_ptr).zstream.avail_in > 0 as libc::c_int as uInt
    {
        if *(*png_ptr).zstream.next_in as libc::c_int >> 4 as libc::c_int
            > 7 as libc::c_int
        {
            (*png_ptr)
                .zstream
                .msg = b"invalid window size (libpng)\0" as *const u8
                as *const libc::c_char;
            return -(3 as libc::c_int);
        }
        (*png_ptr).zstream_start = 0 as libc::c_int as png_byte;
    }
    return inflate(&mut (*png_ptr).zstream, flush);
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_IHDR(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    let mut buf: [png_byte; 13] = [0; 13];
    let mut width: png_uint_32 = 0;
    let mut height: png_uint_32 = 0;
    let mut bit_depth: libc::c_int = 0;
    let mut color_type: libc::c_int = 0;
    let mut compression_type: libc::c_int = 0;
    let mut filter_type: libc::c_int = 0;
    let mut interlace_type: libc::c_int = 0;
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        != 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
    }
    if length != 13 as libc::c_int as png_uint_32 {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"invalid\0" as *const u8 as *const libc::c_char,
        );
    }
    (*png_ptr).mode |= 0x1 as libc::c_int as png_uint_32;
    png_crc_read(png_ptr, buf.as_mut_ptr(), 13 as libc::c_int as png_uint_32);
    png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32);
    width = png_get_uint_31(
        png_ptr as png_const_structrp,
        buf.as_mut_ptr() as png_const_bytep,
    );
    height = png_get_uint_31(
        png_ptr as png_const_structrp,
        buf.as_mut_ptr().offset(4 as libc::c_int as isize) as png_const_bytep,
    );
    bit_depth = buf[8 as libc::c_int as usize] as libc::c_int;
    color_type = buf[9 as libc::c_int as usize] as libc::c_int;
    compression_type = buf[10 as libc::c_int as usize] as libc::c_int;
    filter_type = buf[11 as libc::c_int as usize] as libc::c_int;
    interlace_type = buf[12 as libc::c_int as usize] as libc::c_int;
    (*png_ptr).width = width;
    (*png_ptr).height = height;
    (*png_ptr).bit_depth = bit_depth as png_byte;
    (*png_ptr).interlaced = interlace_type as png_byte;
    (*png_ptr).color_type = color_type as png_byte;
    (*png_ptr).compression_type = compression_type as png_byte;
    match (*png_ptr).color_type as libc::c_int {
        2 => {
            (*png_ptr).channels = 3 as libc::c_int as png_byte;
        }
        4 => {
            (*png_ptr).channels = 2 as libc::c_int as png_byte;
        }
        6 => {
            (*png_ptr).channels = 4 as libc::c_int as png_byte;
        }
        0 | 3 | _ => {
            (*png_ptr).channels = 1 as libc::c_int as png_byte;
        }
    }
    (*png_ptr)
        .pixel_depth = ((*png_ptr).bit_depth as libc::c_int
        * (*png_ptr).channels as libc::c_int) as png_byte;
    (*png_ptr)
        .rowbytes = if (*png_ptr).pixel_depth as libc::c_int >= 8 as libc::c_int {
        (*png_ptr).width as size_t
            * ((*png_ptr).pixel_depth as size_t >> 3 as libc::c_int)
    } else {
        ((*png_ptr).width as size_t * (*png_ptr).pixel_depth as size_t)
            .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
    };
    png_set_IHDR(
        png_ptr as png_const_structrp,
        info_ptr,
        width,
        height,
        bit_depth,
        color_type,
        interlace_type,
        compression_type,
        filter_type,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_PLTE(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    let mut palette: [png_color; 256] = [png_color_struct {
        red: 0,
        green: 0,
        blue: 0,
    }; 256];
    let mut max_palette_length: libc::c_int = 0;
    let mut num: libc::c_int = 0;
    let mut i: libc::c_int = 0;
    let mut pal_ptr: png_colorp = 0 as *mut png_color;
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        == 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"missing IHDR\0" as *const u8 as *const libc::c_char,
        );
    } else if (*png_ptr).mode & 0x2 as libc::c_int as png_uint_32
        != 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"duplicate\0" as *const u8 as *const libc::c_char,
        );
    } else if (*png_ptr).mode & 0x4 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    (*png_ptr).mode |= 0x2 as libc::c_int as png_uint_32;
    if (*png_ptr).color_type as libc::c_int & 2 as libc::c_int == 0 as libc::c_int {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"ignored in grayscale PNG\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    if length > (3 as libc::c_int * 256 as libc::c_int) as png_uint_32
        || length % 3 as libc::c_int as png_uint_32 != 0
    {
        png_crc_finish(png_ptr, length);
        if (*png_ptr).color_type as libc::c_int != 2 as libc::c_int | 1 as libc::c_int {
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"invalid\0" as *const u8 as *const libc::c_char,
            );
        } else {
            png_chunk_error(
                png_ptr as png_const_structrp,
                b"invalid\0" as *const u8 as *const libc::c_char,
            );
        }
        return;
    }
    num = length as libc::c_int / 3 as libc::c_int;
    if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int {
        max_palette_length = (1 as libc::c_int) << (*png_ptr).bit_depth as libc::c_int;
    } else {
        max_palette_length = 256 as libc::c_int;
    }
    if num > max_palette_length {
        num = max_palette_length;
    }
    i = 0 as libc::c_int;
    pal_ptr = palette.as_mut_ptr();
    while i < num {
        let mut buf: [png_byte; 3] = [0; 3];
        png_crc_read(png_ptr, buf.as_mut_ptr(), 3 as libc::c_int as png_uint_32);
        (*pal_ptr).red = buf[0 as libc::c_int as usize];
        (*pal_ptr).green = buf[1 as libc::c_int as usize];
        (*pal_ptr).blue = buf[2 as libc::c_int as usize];
        i += 1;
        i;
        pal_ptr = pal_ptr.offset(1);
        pal_ptr;
    }
    png_crc_finish(
        png_ptr,
        length
            .wrapping_sub(
                (num as libc::c_uint).wrapping_mul(3 as libc::c_int as libc::c_uint),
            ),
    );
    png_set_PLTE(png_ptr, info_ptr, palette.as_mut_ptr() as png_const_colorp, num);
    if (*png_ptr).num_trans as libc::c_int > 0 as libc::c_int
        || !info_ptr.is_null()
            && (*info_ptr).valid & 0x10 as libc::c_uint
                != 0 as libc::c_int as libc::c_uint
    {
        (*png_ptr).num_trans = 0 as libc::c_int as png_uint_16;
        if !info_ptr.is_null() {
            (*info_ptr).num_trans = 0 as libc::c_int as png_uint_16;
        }
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"tRNS must be after\0" as *const u8 as *const libc::c_char,
        );
    }
    if !info_ptr.is_null()
        && (*info_ptr).valid & 0x40 as libc::c_uint != 0 as libc::c_int as libc::c_uint
    {
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"hIST must be after\0" as *const u8 as *const libc::c_char,
        );
    }
    if !info_ptr.is_null()
        && (*info_ptr).valid & 0x20 as libc::c_uint != 0 as libc::c_int as libc::c_uint
    {
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"bKGD must be after\0" as *const u8 as *const libc::c_char,
        );
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_IEND(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        == 0 as libc::c_int as png_uint_32
        || (*png_ptr).mode & 0x4 as libc::c_uint == 0 as libc::c_int as libc::c_uint
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
    }
    (*png_ptr).mode |= 0x8 as libc::c_int as libc::c_uint | 0x10 as libc::c_uint;
    png_crc_finish(png_ptr, length);
    if length != 0 as libc::c_int as png_uint_32 {
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"invalid\0" as *const u8 as *const libc::c_char,
        );
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_sBIT(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    let mut truelen: libc::c_uint = 0;
    let mut i: libc::c_uint = 0;
    let mut sample_depth: png_byte = 0;
    let mut buf: [png_byte; 4] = [0; 4];
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        == 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"missing IHDR\0" as *const u8 as *const libc::c_char,
        );
    } else if (*png_ptr).mode
        & (0x4 as libc::c_uint | 0x2 as libc::c_int as libc::c_uint)
        != 0 as libc::c_int as libc::c_uint
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    if !info_ptr.is_null()
        && (*info_ptr).valid & 0x2 as libc::c_uint != 0 as libc::c_int as libc::c_uint
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"duplicate\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int {
        truelen = 3 as libc::c_int as libc::c_uint;
        sample_depth = 8 as libc::c_int as png_byte;
    } else {
        truelen = (*png_ptr).channels as libc::c_uint;
        sample_depth = (*png_ptr).bit_depth;
    }
    if length != truelen || length > 4 as libc::c_int as png_uint_32 {
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"invalid\0" as *const u8 as *const libc::c_char,
        );
        png_crc_finish(png_ptr, length);
        return;
    }
    buf[3 as libc::c_int as usize] = sample_depth;
    buf[2 as libc::c_int as usize] = buf[3 as libc::c_int as usize];
    buf[1 as libc::c_int as usize] = buf[2 as libc::c_int as usize];
    buf[0 as libc::c_int as usize] = buf[1 as libc::c_int as usize];
    png_crc_read(png_ptr, buf.as_mut_ptr(), truelen);
    if png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32) != 0 as libc::c_int {
        return;
    }
    i = 0 as libc::c_int as libc::c_uint;
    while i < truelen {
        if buf[i as usize] as libc::c_int == 0 as libc::c_int
            || buf[i as usize] as libc::c_int > sample_depth as libc::c_int
        {
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"invalid\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        i = i.wrapping_add(1);
        i;
    }
    if (*png_ptr).color_type as libc::c_int & 2 as libc::c_int != 0 as libc::c_int {
        (*png_ptr).sig_bit.red = buf[0 as libc::c_int as usize];
        (*png_ptr).sig_bit.green = buf[1 as libc::c_int as usize];
        (*png_ptr).sig_bit.blue = buf[2 as libc::c_int as usize];
        (*png_ptr).sig_bit.alpha = buf[3 as libc::c_int as usize];
    } else {
        (*png_ptr).sig_bit.gray = buf[0 as libc::c_int as usize];
        (*png_ptr).sig_bit.red = buf[0 as libc::c_int as usize];
        (*png_ptr).sig_bit.green = buf[0 as libc::c_int as usize];
        (*png_ptr).sig_bit.blue = buf[0 as libc::c_int as usize];
        (*png_ptr).sig_bit.alpha = buf[1 as libc::c_int as usize];
    }
    png_set_sBIT(
        png_ptr as png_const_structrp,
        info_ptr,
        &mut (*png_ptr).sig_bit as *mut png_color_8 as png_const_color_8p,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_tRNS(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    let mut readbuf: [png_byte; 256] = [0; 256];
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        == 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"missing IHDR\0" as *const u8 as *const libc::c_char,
        );
    } else if (*png_ptr).mode & 0x4 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
        return;
    } else if !info_ptr.is_null()
        && (*info_ptr).valid & 0x10 as libc::c_uint != 0 as libc::c_int as libc::c_uint
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"duplicate\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    if (*png_ptr).color_type as libc::c_int == 0 as libc::c_int {
        let mut buf: [png_byte; 2] = [0; 2];
        if length != 2 as libc::c_int as png_uint_32 {
            png_crc_finish(png_ptr, length);
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"invalid\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_crc_read(png_ptr, buf.as_mut_ptr(), 2 as libc::c_int as png_uint_32);
        (*png_ptr).num_trans = 1 as libc::c_int as png_uint_16;
        (*png_ptr)
            .trans_color
            .gray = ((*buf.as_mut_ptr() as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf.as_mut_ptr().offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
    } else if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int {
        let mut buf_0: [png_byte; 6] = [0; 6];
        if length != 6 as libc::c_int as png_uint_32 {
            png_crc_finish(png_ptr, length);
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"invalid\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_crc_read(png_ptr, buf_0.as_mut_ptr(), length);
        (*png_ptr).num_trans = 1 as libc::c_int as png_uint_16;
        (*png_ptr)
            .trans_color
            .red = ((*buf_0.as_mut_ptr() as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf_0.as_mut_ptr().offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        (*png_ptr)
            .trans_color
            .green = ((*buf_0.as_mut_ptr().offset(2 as libc::c_int as isize)
            as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf_0
                    .as_mut_ptr()
                    .offset(2 as libc::c_int as isize)
                    .offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        (*png_ptr)
            .trans_color
            .blue = ((*buf_0.as_mut_ptr().offset(4 as libc::c_int as isize)
            as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf_0
                    .as_mut_ptr()
                    .offset(4 as libc::c_int as isize)
                    .offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
    } else if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int
    {
        if (*png_ptr).mode & 0x2 as libc::c_int as png_uint_32
            == 0 as libc::c_int as png_uint_32
        {
            png_crc_finish(png_ptr, length);
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"out of place\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        if length > (*png_ptr).num_palette as libc::c_uint
            || length > 256 as libc::c_int as libc::c_uint
            || length == 0 as libc::c_int as png_uint_32
        {
            png_crc_finish(png_ptr, length);
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"invalid\0" as *const u8 as *const libc::c_char,
            );
            return;
        }
        png_crc_read(png_ptr, readbuf.as_mut_ptr(), length);
        (*png_ptr).num_trans = length as png_uint_16;
    } else {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"invalid with alpha channel\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    if png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32) != 0 as libc::c_int {
        (*png_ptr).num_trans = 0 as libc::c_int as png_uint_16;
        return;
    }
    png_set_tRNS(
        png_ptr,
        info_ptr,
        readbuf.as_mut_ptr() as png_const_bytep,
        (*png_ptr).num_trans as libc::c_int,
        &mut (*png_ptr).trans_color as *mut png_color_16 as png_const_color_16p,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_bKGD(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    let mut truelen: libc::c_uint = 0;
    let mut buf: [png_byte; 6] = [0; 6];
    let mut background: png_color_16 = png_color_16_struct {
        index: 0,
        red: 0,
        green: 0,
        blue: 0,
        gray: 0,
    };
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        == 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"missing IHDR\0" as *const u8 as *const libc::c_char,
        );
    } else if (*png_ptr).mode & 0x4 as libc::c_uint != 0 as libc::c_int as libc::c_uint
        || (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int
            && (*png_ptr).mode & 0x2 as libc::c_int as png_uint_32
                == 0 as libc::c_int as png_uint_32
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
        return;
    } else if !info_ptr.is_null()
        && (*info_ptr).valid & 0x20 as libc::c_uint != 0 as libc::c_int as libc::c_uint
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"duplicate\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int {
        truelen = 1 as libc::c_int as libc::c_uint;
    } else if (*png_ptr).color_type as libc::c_int & 2 as libc::c_int != 0 as libc::c_int
    {
        truelen = 6 as libc::c_int as libc::c_uint;
    } else {
        truelen = 2 as libc::c_int as libc::c_uint;
    }
    if length != truelen {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"invalid\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    png_crc_read(png_ptr, buf.as_mut_ptr(), truelen);
    if png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32) != 0 as libc::c_int {
        return;
    }
    if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int {
        background.index = buf[0 as libc::c_int as usize];
        if !info_ptr.is_null()
            && (*info_ptr).num_palette as libc::c_int != 0 as libc::c_int
        {
            if buf[0 as libc::c_int as usize] as libc::c_int
                >= (*info_ptr).num_palette as libc::c_int
            {
                png_chunk_benign_error(
                    png_ptr as png_const_structrp,
                    b"invalid index\0" as *const u8 as *const libc::c_char,
                );
                return;
            }
            background
                .red = (*((*png_ptr).palette)
                .offset(buf[0 as libc::c_int as usize] as isize))
                .red as png_uint_16;
            background
                .green = (*((*png_ptr).palette)
                .offset(buf[0 as libc::c_int as usize] as isize))
                .green as png_uint_16;
            background
                .blue = (*((*png_ptr).palette)
                .offset(buf[0 as libc::c_int as usize] as isize))
                .blue as png_uint_16;
        } else {
            background.blue = 0 as libc::c_int as png_uint_16;
            background.green = background.blue;
            background.red = background.green;
        }
        background.gray = 0 as libc::c_int as png_uint_16;
    } else if (*png_ptr).color_type as libc::c_int & 2 as libc::c_int == 0 as libc::c_int
    {
        if (*png_ptr).bit_depth as libc::c_int <= 8 as libc::c_int {
            if buf[0 as libc::c_int as usize] as libc::c_int != 0 as libc::c_int
                || buf[1 as libc::c_int as usize] as libc::c_uint
                    >= ((1 as libc::c_int) << (*png_ptr).bit_depth as libc::c_int)
                        as libc::c_uint
            {
                png_chunk_benign_error(
                    png_ptr as png_const_structrp,
                    b"invalid gray level\0" as *const u8 as *const libc::c_char,
                );
                return;
            }
        }
        background.index = 0 as libc::c_int as png_byte;
        background
            .gray = ((*buf.as_mut_ptr() as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf.as_mut_ptr().offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        background.blue = background.gray;
        background.green = background.blue;
        background.red = background.green;
    } else {
        if (*png_ptr).bit_depth as libc::c_int <= 8 as libc::c_int {
            if buf[0 as libc::c_int as usize] as libc::c_int != 0 as libc::c_int
                || buf[2 as libc::c_int as usize] as libc::c_int != 0 as libc::c_int
                || buf[4 as libc::c_int as usize] as libc::c_int != 0 as libc::c_int
            {
                png_chunk_benign_error(
                    png_ptr as png_const_structrp,
                    b"invalid color\0" as *const u8 as *const libc::c_char,
                );
                return;
            }
        }
        background.index = 0 as libc::c_int as png_byte;
        background
            .red = ((*buf.as_mut_ptr() as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf.as_mut_ptr().offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        background
            .green = ((*buf.as_mut_ptr().offset(2 as libc::c_int as isize)
            as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf
                    .as_mut_ptr()
                    .offset(2 as libc::c_int as isize)
                    .offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        background
            .blue = ((*buf.as_mut_ptr().offset(4 as libc::c_int as isize)
            as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf
                    .as_mut_ptr()
                    .offset(4 as libc::c_int as isize)
                    .offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        background.gray = 0 as libc::c_int as png_uint_16;
    }
    png_set_bKGD(
        png_ptr as png_const_structrp,
        info_ptr,
        &mut background as *mut png_color_16 as png_const_color_16p,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_hIST(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
) {
    let mut num: libc::c_uint = 0;
    let mut i: libc::c_uint = 0;
    let mut readbuf: [png_uint_16; 256] = [0; 256];
    if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
        == 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"missing IHDR\0" as *const u8 as *const libc::c_char,
        );
    } else if (*png_ptr).mode & 0x4 as libc::c_uint != 0 as libc::c_int as libc::c_uint
        || (*png_ptr).mode & 0x2 as libc::c_int as png_uint_32
            == 0 as libc::c_int as png_uint_32
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"out of place\0" as *const u8 as *const libc::c_char,
        );
        return;
    } else if !info_ptr.is_null()
        && (*info_ptr).valid & 0x40 as libc::c_uint != 0 as libc::c_int as libc::c_uint
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"duplicate\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    num = length / 2 as libc::c_int as png_uint_32;
    if length != num.wrapping_mul(2 as libc::c_int as libc::c_uint)
        || num != (*png_ptr).num_palette as libc::c_uint
        || num > 256 as libc::c_int as libc::c_uint
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"invalid\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    i = 0 as libc::c_int as libc::c_uint;
    while i < num {
        let mut buf: [png_byte; 2] = [0; 2];
        png_crc_read(png_ptr, buf.as_mut_ptr(), 2 as libc::c_int as png_uint_32);
        readbuf[i
            as usize] = ((*buf.as_mut_ptr() as libc::c_uint) << 8 as libc::c_int)
            .wrapping_add(
                *buf.as_mut_ptr().offset(1 as libc::c_int as isize) as libc::c_uint,
            ) as png_uint_16;
        i = i.wrapping_add(1);
        i;
    }
    if png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32) != 0 as libc::c_int {
        return;
    }
    png_set_hIST(
        png_ptr as png_const_structrp,
        info_ptr,
        readbuf.as_mut_ptr() as png_const_uint_16p,
    );
}
unsafe extern "C" fn png_cache_unknown_chunk(
    mut png_ptr: png_structrp,
    mut length: png_uint_32,
) -> libc::c_int {
    let mut limit: png_alloc_size_t = -(1 as libc::c_int) as size_t;
    if !((*png_ptr).unknown_chunk.data).is_null() {
        png_free(
            png_ptr as png_const_structrp,
            (*png_ptr).unknown_chunk.data as png_voidp,
        );
        (*png_ptr).unknown_chunk.data = 0 as *mut png_byte;
    }
    if (*png_ptr).user_chunk_malloc_max > 0 as libc::c_int as png_alloc_size_t
        && (*png_ptr).user_chunk_malloc_max < limit
    {
        limit = (*png_ptr).user_chunk_malloc_max;
    }
    if length as png_alloc_size_t <= limit {
        *(((*png_ptr).unknown_chunk.name).as_mut_ptr() as *mut libc::c_char)
            .offset(
                0 as libc::c_int as isize,
            ) = ((*png_ptr).chunk_name >> 24 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *(((*png_ptr).unknown_chunk.name).as_mut_ptr() as *mut libc::c_char)
            .offset(
                1 as libc::c_int as isize,
            ) = ((*png_ptr).chunk_name >> 16 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *(((*png_ptr).unknown_chunk.name).as_mut_ptr() as *mut libc::c_char)
            .offset(
                2 as libc::c_int as isize,
            ) = ((*png_ptr).chunk_name >> 8 as libc::c_int
            & 0xff as libc::c_int as png_uint_32) as libc::c_char;
        *(((*png_ptr).unknown_chunk.name).as_mut_ptr() as *mut libc::c_char)
            .offset(
                3 as libc::c_int as isize,
            ) = ((*png_ptr).chunk_name & 0xff as libc::c_int as png_uint_32)
            as libc::c_char;
        *(((*png_ptr).unknown_chunk.name).as_mut_ptr() as *mut libc::c_char)
            .offset(4 as libc::c_int as isize) = 0 as libc::c_int as libc::c_char;
        (*png_ptr).unknown_chunk.size = length as size_t;
        (*png_ptr).unknown_chunk.location = (*png_ptr).mode as png_byte;
        if length == 0 as libc::c_int as png_uint_32 {
            (*png_ptr).unknown_chunk.data = 0 as *mut png_byte;
        } else {
            (*png_ptr)
                .unknown_chunk
                .data = png_malloc_warn(
                png_ptr as png_const_structrp,
                length as png_alloc_size_t,
            ) as *mut png_byte;
        }
    }
    if ((*png_ptr).unknown_chunk.data).is_null()
        && length > 0 as libc::c_int as png_uint_32
    {
        png_crc_finish(png_ptr, length);
        png_chunk_benign_error(
            png_ptr as png_const_structrp,
            b"unknown chunk exceeds memory limits\0" as *const u8 as *const libc::c_char,
        );
        return 0 as libc::c_int;
    } else {
        if length > 0 as libc::c_int as png_uint_32 {
            png_crc_read(png_ptr, (*png_ptr).unknown_chunk.data, length);
        }
        png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32);
        return 1 as libc::c_int;
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_unknown(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut length: png_uint_32,
    mut keep: libc::c_int,
) {
    let mut handled: libc::c_int = 0 as libc::c_int;
    if keep == 0 as libc::c_int {
        keep = (*png_ptr).unknown_default;
    }
    if keep == 3 as libc::c_int
        || keep == 2 as libc::c_int
            && 1 as libc::c_int as png_uint_32
                & (*png_ptr).chunk_name >> 29 as libc::c_int != 0
    {
        if png_cache_unknown_chunk(png_ptr, length) == 0 as libc::c_int {
            keep = 1 as libc::c_int;
        }
    } else {
        png_crc_finish(png_ptr, length);
    }
    if keep == 3 as libc::c_int
        || keep == 2 as libc::c_int
            && 1 as libc::c_int as png_uint_32
                & (*png_ptr).chunk_name >> 29 as libc::c_int != 0
    {
        let mut current_block_13: u64;
        match (*png_ptr).user_chunk_cache_max {
            2 => {
                (*png_ptr).user_chunk_cache_max = 1 as libc::c_int as png_uint_32;
                png_chunk_benign_error(
                    png_ptr as png_const_structrp,
                    b"no space in chunk cache\0" as *const u8 as *const libc::c_char,
                );
                current_block_13 = 3512920355445576850;
            }
            1 => {
                current_block_13 = 3512920355445576850;
            }
            0 => {
                current_block_13 = 1269930762544942310;
            }
            _ => {
                (*png_ptr)
                    .user_chunk_cache_max = ((*png_ptr).user_chunk_cache_max)
                    .wrapping_sub(1);
                (*png_ptr).user_chunk_cache_max;
                current_block_13 = 1269930762544942310;
            }
        }
        match current_block_13 {
            1269930762544942310 => {
                png_set_unknown_chunks(
                    png_ptr as png_const_structrp,
                    info_ptr,
                    &mut (*png_ptr).unknown_chunk as *mut png_unknown_chunk
                        as png_const_unknown_chunkp,
                    1 as libc::c_int,
                );
                handled = 1 as libc::c_int;
            }
            _ => {}
        }
    }
    if !((*png_ptr).unknown_chunk.data).is_null() {
        png_free(
            png_ptr as png_const_structrp,
            (*png_ptr).unknown_chunk.data as png_voidp,
        );
    }
    (*png_ptr).unknown_chunk.data = 0 as *mut png_byte;
    if handled == 0 as libc::c_int
        && 1 as libc::c_int as png_uint_32 & (*png_ptr).chunk_name >> 29 as libc::c_int
            == 0
    {
        png_chunk_error(
            png_ptr as png_const_structrp,
            b"unhandled critical chunk\0" as *const u8 as *const libc::c_char,
        );
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_check_chunk_name(
    mut png_ptr: png_const_structrp,
    mut chunk_name: png_uint_32,
) {
    let mut i: libc::c_int = 0;
    let mut cn: png_uint_32 = chunk_name;
    i = 1 as libc::c_int;
    while i <= 4 as libc::c_int {
        let mut c: libc::c_int = (cn & 0xff as libc::c_int as png_uint_32)
            as libc::c_int;
        if c < 65 as libc::c_int || c > 122 as libc::c_int
            || c > 90 as libc::c_int && c < 97 as libc::c_int
        {
            png_chunk_error(
                png_ptr,
                b"invalid chunk type\0" as *const u8 as *const libc::c_char,
            );
        }
        cn >>= 8 as libc::c_int;
        i += 1;
        i;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_check_chunk_length(
    mut png_ptr: png_const_structrp,
    mut length: png_uint_32,
) {
    let mut limit: png_alloc_size_t = 0x7fffffff as libc::c_long as png_uint_32
        as png_alloc_size_t;
    if (*png_ptr).user_chunk_malloc_max > 0 as libc::c_int as png_alloc_size_t
        && (*png_ptr).user_chunk_malloc_max < limit
    {
        limit = (*png_ptr).user_chunk_malloc_max;
    }
    if (*png_ptr).chunk_name
        == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
    {
        let mut idat_limit: png_alloc_size_t = 0x7fffffff as libc::c_long as png_uint_32
            as png_alloc_size_t;
        let mut row_factor: size_t = ((*png_ptr).width as size_t
            * (*png_ptr).channels as size_t
            * (if (*png_ptr).bit_depth as libc::c_int > 8 as libc::c_int {
                2 as libc::c_int
            } else {
                1 as libc::c_int
            }) as size_t)
            .wrapping_add(1 as libc::c_int as size_t)
            .wrapping_add(
                (if (*png_ptr).interlaced as libc::c_int != 0 {
                    6 as libc::c_int
                } else {
                    0 as libc::c_int
                }) as size_t,
            );
        if (*png_ptr).height as size_t
            > -(1 as libc::c_int) as png_uint_32 as size_t / row_factor
        {
            idat_limit = 0x7fffffff as libc::c_long as png_uint_32 as png_alloc_size_t;
        } else {
            idat_limit = (*png_ptr).height as size_t * row_factor;
        }
        row_factor = if row_factor > 32566 as libc::c_int as size_t {
            32566 as libc::c_int as size_t
        } else {
            row_factor
        };
        idat_limit = (idat_limit as size_t)
            .wrapping_add(
                (6 as libc::c_int as size_t)
                    .wrapping_add(
                        5 as libc::c_int as size_t
                            * (idat_limit / row_factor)
                                .wrapping_add(1 as libc::c_int as size_t),
                    ),
            ) as png_alloc_size_t as png_alloc_size_t;
        idat_limit = if idat_limit
            < 0x7fffffff as libc::c_long as png_uint_32 as png_alloc_size_t
        {
            idat_limit
        } else {
            0x7fffffff as libc::c_long as png_uint_32 as png_alloc_size_t
        };
        limit = if limit < idat_limit { idat_limit } else { limit };
    }
    if length as png_alloc_size_t > limit {
        png_benign_error(
            png_ptr,
            b"chunk data is too large\0" as *const u8 as *const libc::c_char,
        );
    }
}
static mut row_mask: [[[png_uint_32; 6]; 3]; 2] = [[[0; 6]; 3]; 2];
static mut display_mask: [[[png_uint_32; 3]; 3]; 2] = [[[0; 3]; 3]; 2];
#[no_mangle]
pub unsafe extern "C" fn png_combine_row(
    mut png_ptr: png_const_structrp,
    mut dp: png_bytep,
    mut display: libc::c_int,
) {
    let mut pixel_depth: libc::c_uint = (*png_ptr).transformed_pixel_depth
        as libc::c_uint;
    let mut sp: png_const_bytep = ((*png_ptr).row_buf).offset(1 as libc::c_int as isize)
        as png_const_bytep;
    let mut row_width: png_alloc_size_t = (*png_ptr).width as png_alloc_size_t;
    let mut pass: libc::c_uint = (*png_ptr).pass as libc::c_uint;
    let mut end_ptr: png_bytep = 0 as png_bytep;
    let mut end_byte: png_byte = 0 as libc::c_int as png_byte;
    let mut end_mask: libc::c_uint = 0;
    if pixel_depth == 0 as libc::c_int as libc::c_uint {
        png_error(
            png_ptr,
            b"internal row logic error\0" as *const u8 as *const libc::c_char,
        );
    }
    if (*png_ptr).info_rowbytes != 0 as libc::c_int as size_t
        && (*png_ptr).info_rowbytes
            != (if pixel_depth >= 8 as libc::c_int as libc::c_uint {
                row_width * (pixel_depth as size_t >> 3 as libc::c_int)
            } else {
                (row_width * pixel_depth as size_t)
                    .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
            })
    {
        png_error(
            png_ptr,
            b"internal row size calculation error\0" as *const u8 as *const libc::c_char,
        );
    }
    if row_width == 0 as libc::c_int as png_alloc_size_t {
        png_error(
            png_ptr,
            b"internal row width error\0" as *const u8 as *const libc::c_char,
        );
    }
    end_mask = (pixel_depth as png_alloc_size_t * row_width
        & 7 as libc::c_int as png_alloc_size_t) as libc::c_uint;
    if end_mask != 0 as libc::c_int as libc::c_uint {
        end_ptr = dp
            .offset(
                (if pixel_depth >= 8 as libc::c_int as libc::c_uint {
                    row_width * (pixel_depth as size_t >> 3 as libc::c_int)
                } else {
                    (row_width * pixel_depth as size_t)
                        .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
                }) as isize,
            )
            .offset(-(1 as libc::c_int as isize));
        end_byte = *end_ptr;
        end_mask = (0xff as libc::c_int >> end_mask) as libc::c_uint;
    }
    if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int
        && (*png_ptr).transformations & 0x2 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
        && pass < 6 as libc::c_int as libc::c_uint
        && (display == 0 as libc::c_int
            || display == 1 as libc::c_int
                && pass & 1 as libc::c_int as libc::c_uint
                    != 0 as libc::c_int as libc::c_uint)
    {
        if row_width
            <= ((1 as libc::c_int as libc::c_uint & pass)
                << (3 as libc::c_int as libc::c_uint)
                    .wrapping_sub(
                        pass.wrapping_add(1 as libc::c_int as libc::c_uint)
                            >> 1 as libc::c_int,
                    ) & 7 as libc::c_int as libc::c_uint) as png_alloc_size_t
        {
            return;
        }
        if pixel_depth < 8 as libc::c_int as libc::c_uint {
            let mut pixels_per_byte: png_uint_32 = (8 as libc::c_int as libc::c_uint)
                .wrapping_div(pixel_depth);
            let mut mask: png_uint_32 = 0;
            mask = if display != 0 {
                display_mask[1 as libc::c_int
                    as usize][(if pixel_depth == 1 as libc::c_int as libc::c_uint {
                    0 as libc::c_int
                } else if pixel_depth == 2 as libc::c_int as libc::c_uint {
                    1 as libc::c_int
                } else {
                    2 as libc::c_int
                }) as usize][(pass >> 1 as libc::c_int) as usize]
            } else {
                row_mask[1 as libc::c_int
                    as usize][(if pixel_depth == 1 as libc::c_int as libc::c_uint {
                    0 as libc::c_int
                } else if pixel_depth == 2 as libc::c_int as libc::c_uint {
                    1 as libc::c_int
                } else {
                    2 as libc::c_int
                }) as usize][pass as usize]
            };
            loop {
                let mut m: png_uint_32 = 0;
                m = mask;
                mask = m >> 8 as libc::c_int | m << 24 as libc::c_int;
                m &= 0xff as libc::c_int as png_uint_32;
                if m != 0 as libc::c_int as png_uint_32 {
                    if m != 0xff as libc::c_int as png_uint_32 {
                        *dp = (*dp as png_uint_32 & !m | *sp as png_uint_32 & m)
                            as png_byte;
                    } else {
                        *dp = *sp;
                    }
                }
                if row_width <= pixels_per_byte as png_alloc_size_t {
                    break;
                }
                row_width = row_width.wrapping_sub(pixels_per_byte as png_alloc_size_t);
                dp = dp.offset(1);
                dp;
                sp = sp.offset(1);
                sp;
            }
        } else {
            let mut bytes_to_copy: libc::c_uint = 0;
            let mut bytes_to_jump: libc::c_uint = 0;
            if pixel_depth & 7 as libc::c_int as libc::c_uint != 0 {
                png_error(
                    png_ptr,
                    b"invalid user transform pixel depth\0" as *const u8
                        as *const libc::c_char,
                );
            }
            pixel_depth >>= 3 as libc::c_int;
            row_width = row_width * pixel_depth as png_alloc_size_t;
            let mut offset: libc::c_uint = ((1 as libc::c_int as libc::c_uint & pass)
                << (3 as libc::c_int as libc::c_uint)
                    .wrapping_sub(
                        pass.wrapping_add(1 as libc::c_int as libc::c_uint)
                            >> 1 as libc::c_int,
                    ) & 7 as libc::c_int as libc::c_uint)
                .wrapping_mul(pixel_depth);
            row_width = row_width.wrapping_sub(offset as png_alloc_size_t);
            dp = dp.offset(offset as isize);
            sp = sp.offset(offset as isize);
            if display != 0 as libc::c_int {
                bytes_to_copy = (((1 as libc::c_int)
                    << ((6 as libc::c_int as libc::c_uint).wrapping_sub(pass)
                        >> 1 as libc::c_int)) as libc::c_uint)
                    .wrapping_mul(pixel_depth);
                if bytes_to_copy as png_alloc_size_t > row_width {
                    bytes_to_copy = row_width as libc::c_uint;
                }
            } else {
                bytes_to_copy = pixel_depth;
            }
            bytes_to_jump = (((1 as libc::c_int)
                << ((7 as libc::c_int as libc::c_uint).wrapping_sub(pass)
                    >> 1 as libc::c_int)) as libc::c_uint)
                .wrapping_mul(pixel_depth);
            match bytes_to_copy {
                1 => {
                    loop {
                        *dp = *sp;
                        if row_width <= bytes_to_jump as png_alloc_size_t {
                            return;
                        }
                        dp = dp.offset(bytes_to_jump as isize);
                        sp = sp.offset(bytes_to_jump as isize);
                        row_width = row_width
                            .wrapping_sub(bytes_to_jump as png_alloc_size_t);
                    }
                }
                2 => {
                    loop {
                        *dp
                            .offset(
                                0 as libc::c_int as isize,
                            ) = *sp.offset(0 as libc::c_int as isize);
                        *dp
                            .offset(
                                1 as libc::c_int as isize,
                            ) = *sp.offset(1 as libc::c_int as isize);
                        if row_width <= bytes_to_jump as png_alloc_size_t {
                            return;
                        }
                        sp = sp.offset(bytes_to_jump as isize);
                        dp = dp.offset(bytes_to_jump as isize);
                        row_width = row_width
                            .wrapping_sub(bytes_to_jump as png_alloc_size_t);
                        if !(row_width > 1 as libc::c_int as png_alloc_size_t) {
                            break;
                        }
                    }
                    *dp = *sp;
                    return;
                }
                3 => {
                    loop {
                        *dp
                            .offset(
                                0 as libc::c_int as isize,
                            ) = *sp.offset(0 as libc::c_int as isize);
                        *dp
                            .offset(
                                1 as libc::c_int as isize,
                            ) = *sp.offset(1 as libc::c_int as isize);
                        *dp
                            .offset(
                                2 as libc::c_int as isize,
                            ) = *sp.offset(2 as libc::c_int as isize);
                        if row_width <= bytes_to_jump as png_alloc_size_t {
                            return;
                        }
                        sp = sp.offset(bytes_to_jump as isize);
                        dp = dp.offset(bytes_to_jump as isize);
                        row_width = row_width
                            .wrapping_sub(bytes_to_jump as png_alloc_size_t);
                    }
                }
                _ => {
                    if bytes_to_copy < 16 as libc::c_int as libc::c_uint
                        && dp as *const libc::c_void as size_t as png_uint_16
                            as libc::c_int
                            & (::core::mem::size_of::<png_uint_16>() as libc::c_ulong)
                                .wrapping_sub(1 as libc::c_int as libc::c_ulong)
                                as png_uint_16 as libc::c_int == 0 as libc::c_int
                        && sp as *const libc::c_void as size_t as png_uint_16
                            as libc::c_int
                            & (::core::mem::size_of::<png_uint_16>() as libc::c_ulong)
                                .wrapping_sub(1 as libc::c_int as libc::c_ulong)
                                as png_uint_16 as libc::c_int == 0 as libc::c_int
                        && (bytes_to_copy as libc::c_ulong)
                            .wrapping_rem(
                                ::core::mem::size_of::<png_uint_16>() as libc::c_ulong,
                            ) == 0 as libc::c_int as libc::c_ulong
                        && (bytes_to_jump as libc::c_ulong)
                            .wrapping_rem(
                                ::core::mem::size_of::<png_uint_16>() as libc::c_ulong,
                            ) == 0 as libc::c_int as libc::c_ulong
                    {
                        if dp as *const libc::c_void as size_t as png_uint_32
                            & (::core::mem::size_of::<png_uint_32>() as libc::c_ulong)
                                .wrapping_sub(1 as libc::c_int as libc::c_ulong)
                                as png_uint_32 == 0 as libc::c_int as png_uint_32
                            && sp as *const libc::c_void as size_t as png_uint_32
                                & (::core::mem::size_of::<png_uint_32>() as libc::c_ulong)
                                    .wrapping_sub(1 as libc::c_int as libc::c_ulong)
                                    as png_uint_32 == 0 as libc::c_int as png_uint_32
                            && (bytes_to_copy as libc::c_ulong)
                                .wrapping_rem(
                                    ::core::mem::size_of::<png_uint_32>() as libc::c_ulong,
                                ) == 0 as libc::c_int as libc::c_ulong
                            && (bytes_to_jump as libc::c_ulong)
                                .wrapping_rem(
                                    ::core::mem::size_of::<png_uint_32>() as libc::c_ulong,
                                ) == 0 as libc::c_int as libc::c_ulong
                        {
                            let mut dp32: png_uint_32p = dp as *mut libc::c_void
                                as png_uint_32p;
                            let mut sp32: png_const_uint_32p = sp as *const libc::c_void
                                as png_const_uint_32p;
                            let mut skip: size_t = (bytes_to_jump
                                .wrapping_sub(bytes_to_copy) as libc::c_ulong)
                                .wrapping_div(
                                    ::core::mem::size_of::<png_uint_32>() as libc::c_ulong,
                                );
                            loop {
                                let mut c: size_t = bytes_to_copy as size_t;
                                loop {
                                    let fresh0 = sp32;
                                    sp32 = sp32.offset(1);
                                    let fresh1 = dp32;
                                    dp32 = dp32.offset(1);
                                    *fresh1 = *fresh0;
                                    c = (c as libc::c_ulong)
                                        .wrapping_sub(
                                            ::core::mem::size_of::<png_uint_32>() as libc::c_ulong,
                                        ) as size_t as size_t;
                                    if !(c > 0 as libc::c_int as size_t) {
                                        break;
                                    }
                                }
                                if row_width <= bytes_to_jump as png_alloc_size_t {
                                    return;
                                }
                                dp32 = dp32.offset(skip as isize);
                                sp32 = sp32.offset(skip as isize);
                                row_width = row_width
                                    .wrapping_sub(bytes_to_jump as png_alloc_size_t);
                                if !(bytes_to_copy as png_alloc_size_t <= row_width) {
                                    break;
                                }
                            }
                            dp = dp32 as png_bytep;
                            sp = sp32 as png_const_bytep;
                            loop {
                                let fresh2 = sp;
                                sp = sp.offset(1);
                                let fresh3 = dp;
                                dp = dp.offset(1);
                                *fresh3 = *fresh2;
                                row_width = row_width.wrapping_sub(1);
                                if !(row_width > 0 as libc::c_int as png_alloc_size_t) {
                                    break;
                                }
                            }
                            return;
                        } else {
                            let mut dp16: png_uint_16p = dp as *mut libc::c_void
                                as png_uint_16p;
                            let mut sp16: png_const_uint_16p = sp as *const libc::c_void
                                as png_const_uint_16p;
                            let mut skip_0: size_t = (bytes_to_jump
                                .wrapping_sub(bytes_to_copy) as libc::c_ulong)
                                .wrapping_div(
                                    ::core::mem::size_of::<png_uint_16>() as libc::c_ulong,
                                );
                            loop {
                                let mut c_0: size_t = bytes_to_copy as size_t;
                                loop {
                                    let fresh4 = sp16;
                                    sp16 = sp16.offset(1);
                                    let fresh5 = dp16;
                                    dp16 = dp16.offset(1);
                                    *fresh5 = *fresh4;
                                    c_0 = (c_0 as libc::c_ulong)
                                        .wrapping_sub(
                                            ::core::mem::size_of::<png_uint_16>() as libc::c_ulong,
                                        ) as size_t as size_t;
                                    if !(c_0 > 0 as libc::c_int as size_t) {
                                        break;
                                    }
                                }
                                if row_width <= bytes_to_jump as png_alloc_size_t {
                                    return;
                                }
                                dp16 = dp16.offset(skip_0 as isize);
                                sp16 = sp16.offset(skip_0 as isize);
                                row_width = row_width
                                    .wrapping_sub(bytes_to_jump as png_alloc_size_t);
                                if !(bytes_to_copy as png_alloc_size_t <= row_width) {
                                    break;
                                }
                            }
                            dp = dp16 as png_bytep;
                            sp = sp16 as png_const_bytep;
                            loop {
                                let fresh6 = sp;
                                sp = sp.offset(1);
                                let fresh7 = dp;
                                dp = dp.offset(1);
                                *fresh7 = *fresh6;
                                row_width = row_width.wrapping_sub(1);
                                if !(row_width > 0 as libc::c_int as png_alloc_size_t) {
                                    break;
                                }
                            }
                            return;
                        }
                    }
                    loop {
                        memcpy(
                            dp as *mut libc::c_void,
                            sp as *const libc::c_void,
                            bytes_to_copy as libc::c_ulong,
                        );
                        if row_width <= bytes_to_jump as png_alloc_size_t {
                            return;
                        }
                        sp = sp.offset(bytes_to_jump as isize);
                        dp = dp.offset(bytes_to_jump as isize);
                        row_width = row_width
                            .wrapping_sub(bytes_to_jump as png_alloc_size_t);
                        if bytes_to_copy as png_alloc_size_t > row_width {
                            bytes_to_copy = row_width as libc::c_uint;
                        }
                    }
                }
            }
        }
    } else {
        memcpy(
            dp as *mut libc::c_void,
            sp as *const libc::c_void,
            if pixel_depth >= 8 as libc::c_int as libc::c_uint {
                row_width * (pixel_depth as size_t >> 3 as libc::c_int)
            } else {
                (row_width * pixel_depth as size_t)
                    .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
            },
        );
    }
    if !end_ptr.is_null() {
        *end_ptr = (end_byte as libc::c_uint & end_mask
            | *end_ptr as libc::c_uint & !end_mask) as png_byte;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_do_read_interlace(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut pass: libc::c_int,
    mut transformations: png_uint_32,
) {
    static mut png_pass_inc: [libc::c_uint; 7] = [
        8 as libc::c_int as libc::c_uint,
        8 as libc::c_int as libc::c_uint,
        4 as libc::c_int as libc::c_uint,
        4 as libc::c_int as libc::c_uint,
        2 as libc::c_int as libc::c_uint,
        2 as libc::c_int as libc::c_uint,
        1 as libc::c_int as libc::c_uint,
    ];
    if !row.is_null() && !row_info.is_null() {
        let mut final_width: png_uint_32 = 0;
        final_width = ((*row_info).width).wrapping_mul(png_pass_inc[pass as usize]);
        match (*row_info).pixel_depth as libc::c_int {
            1 => {
                let mut sp: png_bytep = row
                    .offset(
                        (((*row_info).width)
                            .wrapping_sub(1 as libc::c_int as png_uint_32)
                            >> 3 as libc::c_int) as size_t as isize,
                    );
                let mut dp: png_bytep = row
                    .offset(
                        (final_width.wrapping_sub(1 as libc::c_int as png_uint_32)
                            >> 3 as libc::c_int) as size_t as isize,
                    );
                let mut sshift: libc::c_uint = 0;
                let mut dshift: libc::c_uint = 0;
                let mut s_start: libc::c_uint = 0;
                let mut s_end: libc::c_uint = 0;
                let mut s_inc: libc::c_int = 0;
                let mut jstop: libc::c_int = png_pass_inc[pass as usize] as libc::c_int;
                let mut v: png_byte = 0;
                let mut i: png_uint_32 = 0;
                let mut j: libc::c_int = 0;
                sshift = (7 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        ((*row_info).width).wrapping_add(7 as libc::c_int as png_uint_32)
                            & 0x7 as libc::c_int as png_uint_32,
                    );
                dshift = (7 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        final_width.wrapping_add(7 as libc::c_int as png_uint_32)
                            & 0x7 as libc::c_int as png_uint_32,
                    );
                s_start = 0 as libc::c_int as libc::c_uint;
                s_end = 7 as libc::c_int as libc::c_uint;
                s_inc = 1 as libc::c_int;
                i = 0 as libc::c_int as png_uint_32;
                while i < (*row_info).width {
                    v = (*sp as libc::c_int >> sshift & 0x1 as libc::c_int) as png_byte;
                    j = 0 as libc::c_int;
                    while j < jstop {
                        let mut tmp: libc::c_uint = (*dp as libc::c_int
                            & 0x7f7f as libc::c_int
                                >> (7 as libc::c_int as libc::c_uint).wrapping_sub(dshift))
                            as libc::c_uint;
                        tmp |= ((v as libc::c_int) << dshift) as libc::c_uint;
                        *dp = (tmp & 0xff as libc::c_int as libc::c_uint) as png_byte;
                        if dshift == s_end {
                            dshift = s_start;
                            dp = dp.offset(-1);
                            dp;
                        } else {
                            dshift = (dshift as libc::c_int + s_inc) as libc::c_uint;
                        }
                        j += 1;
                        j;
                    }
                    if sshift == s_end {
                        sshift = s_start;
                        sp = sp.offset(-1);
                        sp;
                    } else {
                        sshift = (sshift as libc::c_int + s_inc) as libc::c_uint;
                    }
                    i = i.wrapping_add(1);
                    i;
                }
            }
            2 => {
                let mut sp_0: png_bytep = row
                    .offset(
                        (((*row_info).width)
                            .wrapping_sub(1 as libc::c_int as png_uint_32)
                            >> 2 as libc::c_int) as isize,
                    );
                let mut dp_0: png_bytep = row
                    .offset(
                        (final_width.wrapping_sub(1 as libc::c_int as png_uint_32)
                            >> 2 as libc::c_int) as isize,
                    );
                let mut sshift_0: libc::c_uint = 0;
                let mut dshift_0: libc::c_uint = 0;
                let mut s_start_0: libc::c_uint = 0;
                let mut s_end_0: libc::c_uint = 0;
                let mut s_inc_0: libc::c_int = 0;
                let mut jstop_0: libc::c_int = png_pass_inc[pass as usize]
                    as libc::c_int;
                let mut i_0: png_uint_32 = 0;
                sshift_0 = (3 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        ((*row_info).width).wrapping_add(3 as libc::c_int as png_uint_32)
                            & 0x3 as libc::c_int as png_uint_32,
                    ) << 1 as libc::c_int;
                dshift_0 = (3 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        final_width.wrapping_add(3 as libc::c_int as png_uint_32)
                            & 0x3 as libc::c_int as png_uint_32,
                    ) << 1 as libc::c_int;
                s_start_0 = 0 as libc::c_int as libc::c_uint;
                s_end_0 = 6 as libc::c_int as libc::c_uint;
                s_inc_0 = 2 as libc::c_int;
                i_0 = 0 as libc::c_int as png_uint_32;
                while i_0 < (*row_info).width {
                    let mut v_0: png_byte = 0;
                    let mut j_0: libc::c_int = 0;
                    v_0 = (*sp_0 as libc::c_int >> sshift_0 & 0x3 as libc::c_int)
                        as png_byte;
                    j_0 = 0 as libc::c_int;
                    while j_0 < jstop_0 {
                        let mut tmp_0: libc::c_uint = (*dp_0 as libc::c_int
                            & 0x3f3f as libc::c_int
                                >> (6 as libc::c_int as libc::c_uint)
                                    .wrapping_sub(dshift_0)) as libc::c_uint;
                        tmp_0 |= ((v_0 as libc::c_int) << dshift_0) as libc::c_uint;
                        *dp_0 = (tmp_0 & 0xff as libc::c_int as libc::c_uint)
                            as png_byte;
                        if dshift_0 == s_end_0 {
                            dshift_0 = s_start_0;
                            dp_0 = dp_0.offset(-1);
                            dp_0;
                        } else {
                            dshift_0 = (dshift_0 as libc::c_int + s_inc_0)
                                as libc::c_uint;
                        }
                        j_0 += 1;
                        j_0;
                    }
                    if sshift_0 == s_end_0 {
                        sshift_0 = s_start_0;
                        sp_0 = sp_0.offset(-1);
                        sp_0;
                    } else {
                        sshift_0 = (sshift_0 as libc::c_int + s_inc_0) as libc::c_uint;
                    }
                    i_0 = i_0.wrapping_add(1);
                    i_0;
                }
            }
            4 => {
                let mut sp_1: png_bytep = row
                    .offset(
                        (((*row_info).width)
                            .wrapping_sub(1 as libc::c_int as png_uint_32)
                            >> 1 as libc::c_int) as size_t as isize,
                    );
                let mut dp_1: png_bytep = row
                    .offset(
                        (final_width.wrapping_sub(1 as libc::c_int as png_uint_32)
                            >> 1 as libc::c_int) as size_t as isize,
                    );
                let mut sshift_1: libc::c_uint = 0;
                let mut dshift_1: libc::c_uint = 0;
                let mut s_start_1: libc::c_uint = 0;
                let mut s_end_1: libc::c_uint = 0;
                let mut s_inc_1: libc::c_int = 0;
                let mut i_1: png_uint_32 = 0;
                let mut jstop_1: libc::c_int = png_pass_inc[pass as usize]
                    as libc::c_int;
                sshift_1 = (1 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        ((*row_info).width).wrapping_add(1 as libc::c_int as png_uint_32)
                            & 0x1 as libc::c_int as png_uint_32,
                    ) << 2 as libc::c_int;
                dshift_1 = (1 as libc::c_int as png_uint_32)
                    .wrapping_sub(
                        final_width.wrapping_add(1 as libc::c_int as png_uint_32)
                            & 0x1 as libc::c_int as png_uint_32,
                    ) << 2 as libc::c_int;
                s_start_1 = 0 as libc::c_int as libc::c_uint;
                s_end_1 = 4 as libc::c_int as libc::c_uint;
                s_inc_1 = 4 as libc::c_int;
                i_1 = 0 as libc::c_int as png_uint_32;
                while i_1 < (*row_info).width {
                    let mut v_1: png_byte = (*sp_1 as libc::c_int >> sshift_1
                        & 0xf as libc::c_int) as png_byte;
                    let mut j_1: libc::c_int = 0;
                    j_1 = 0 as libc::c_int;
                    while j_1 < jstop_1 {
                        let mut tmp_1: libc::c_uint = (*dp_1 as libc::c_int
                            & 0xf0f as libc::c_int
                                >> (4 as libc::c_int as libc::c_uint)
                                    .wrapping_sub(dshift_1)) as libc::c_uint;
                        tmp_1 |= ((v_1 as libc::c_int) << dshift_1) as libc::c_uint;
                        *dp_1 = (tmp_1 & 0xff as libc::c_int as libc::c_uint)
                            as png_byte;
                        if dshift_1 == s_end_1 {
                            dshift_1 = s_start_1;
                            dp_1 = dp_1.offset(-1);
                            dp_1;
                        } else {
                            dshift_1 = (dshift_1 as libc::c_int + s_inc_1)
                                as libc::c_uint;
                        }
                        j_1 += 1;
                        j_1;
                    }
                    if sshift_1 == s_end_1 {
                        sshift_1 = s_start_1;
                        sp_1 = sp_1.offset(-1);
                        sp_1;
                    } else {
                        sshift_1 = (sshift_1 as libc::c_int + s_inc_1) as libc::c_uint;
                    }
                    i_1 = i_1.wrapping_add(1);
                    i_1;
                }
            }
            _ => {
                let mut pixel_bytes: size_t = ((*row_info).pixel_depth as libc::c_int
                    >> 3 as libc::c_int) as size_t;
                let mut sp_2: png_bytep = row
                    .offset(
                        (((*row_info).width)
                            .wrapping_sub(1 as libc::c_int as png_uint_32) as size_t
                            * pixel_bytes) as isize,
                    );
                let mut dp_2: png_bytep = row
                    .offset(
                        (final_width.wrapping_sub(1 as libc::c_int as png_uint_32)
                            as size_t * pixel_bytes) as isize,
                    );
                let mut jstop_2: libc::c_int = png_pass_inc[pass as usize]
                    as libc::c_int;
                let mut i_2: png_uint_32 = 0;
                i_2 = 0 as libc::c_int as png_uint_32;
                while i_2 < (*row_info).width {
                    let mut v_2: [png_byte; 8] = [0; 8];
                    let mut j_2: libc::c_int = 0;
                    memcpy(
                        v_2.as_mut_ptr() as *mut libc::c_void,
                        sp_2 as *const libc::c_void,
                        pixel_bytes,
                    );
                    j_2 = 0 as libc::c_int;
                    while j_2 < jstop_2 {
                        memcpy(
                            dp_2 as *mut libc::c_void,
                            v_2.as_mut_ptr() as *const libc::c_void,
                            pixel_bytes,
                        );
                        dp_2 = dp_2.offset(-(pixel_bytes as isize));
                        j_2 += 1;
                        j_2;
                    }
                    sp_2 = sp_2.offset(-(pixel_bytes as isize));
                    i_2 = i_2.wrapping_add(1);
                    i_2;
                }
            }
        }
        (*row_info).width = final_width;
        (*row_info)
            .rowbytes = if (*row_info).pixel_depth as libc::c_int >= 8 as libc::c_int {
            final_width as size_t
                * ((*row_info).pixel_depth as size_t >> 3 as libc::c_int)
        } else {
            (final_width as size_t * (*row_info).pixel_depth as size_t)
                .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
        };
    }
}
unsafe extern "C" fn png_read_filter_row_sub(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut prev_row: png_const_bytep,
) {
    let mut i: size_t = 0;
    let mut istop: size_t = (*row_info).rowbytes;
    let mut bpp: libc::c_uint = ((*row_info).pixel_depth as libc::c_int
        + 7 as libc::c_int >> 3 as libc::c_int) as libc::c_uint;
    let mut rp: png_bytep = row.offset(bpp as isize);
    i = bpp as size_t;
    while i < istop {
        *rp = (*rp as libc::c_int + *rp.offset(-(bpp as isize)) as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        rp = rp.offset(1);
        rp;
        i = i.wrapping_add(1);
        i;
    }
}
unsafe extern "C" fn png_read_filter_row_up(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut prev_row: png_const_bytep,
) {
    let mut i: size_t = 0;
    let mut istop: size_t = (*row_info).rowbytes;
    let mut rp: png_bytep = row;
    let mut pp: png_const_bytep = prev_row;
    i = 0 as libc::c_int as size_t;
    while i < istop {
        let fresh8 = pp;
        pp = pp.offset(1);
        *rp = (*rp as libc::c_int + *fresh8 as libc::c_int & 0xff as libc::c_int)
            as png_byte;
        rp = rp.offset(1);
        rp;
        i = i.wrapping_add(1);
        i;
    }
}
unsafe extern "C" fn png_read_filter_row_avg(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut prev_row: png_const_bytep,
) {
    let mut i: size_t = 0;
    let mut rp: png_bytep = row;
    let mut pp: png_const_bytep = prev_row;
    let mut bpp: libc::c_uint = ((*row_info).pixel_depth as libc::c_int
        + 7 as libc::c_int >> 3 as libc::c_int) as libc::c_uint;
    let mut istop: size_t = ((*row_info).rowbytes).wrapping_sub(bpp as size_t);
    i = 0 as libc::c_int as size_t;
    while i < bpp as size_t {
        let fresh9 = pp;
        pp = pp.offset(1);
        *rp = (*rp as libc::c_int + *fresh9 as libc::c_int / 2 as libc::c_int
            & 0xff as libc::c_int) as png_byte;
        rp = rp.offset(1);
        rp;
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < istop {
        let fresh10 = pp;
        pp = pp.offset(1);
        *rp = (*rp as libc::c_int
            + (*fresh10 as libc::c_int + *rp.offset(-(bpp as isize)) as libc::c_int)
                / 2 as libc::c_int & 0xff as libc::c_int) as png_byte;
        rp = rp.offset(1);
        rp;
        i = i.wrapping_add(1);
        i;
    }
}
unsafe extern "C" fn png_read_filter_row_paeth_1byte_pixel(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut prev_row: png_const_bytep,
) {
    let mut rp_end: png_bytep = row.offset((*row_info).rowbytes as isize);
    let mut a: libc::c_int = 0;
    let mut c: libc::c_int = 0;
    let fresh11 = prev_row;
    prev_row = prev_row.offset(1);
    c = *fresh11 as libc::c_int;
    a = *row as libc::c_int + c;
    let fresh12 = row;
    row = row.offset(1);
    *fresh12 = a as png_byte;
    while row < rp_end {
        let mut b: libc::c_int = 0;
        let mut pa: libc::c_int = 0;
        let mut pb: libc::c_int = 0;
        let mut pc: libc::c_int = 0;
        let mut p: libc::c_int = 0;
        a &= 0xff as libc::c_int;
        let fresh13 = prev_row;
        prev_row = prev_row.offset(1);
        b = *fresh13 as libc::c_int;
        p = b - c;
        pc = a - c;
        pa = if p < 0 as libc::c_int { -p } else { p };
        pb = if pc < 0 as libc::c_int { -pc } else { pc };
        pc = if p + pc < 0 as libc::c_int { -(p + pc) } else { p + pc };
        if pb < pa {
            pa = pb;
            a = b;
        }
        if pc < pa {
            a = c;
        }
        c = b;
        a += *row as libc::c_int;
        let fresh14 = row;
        row = row.offset(1);
        *fresh14 = a as png_byte;
    }
}
unsafe extern "C" fn png_read_filter_row_paeth_multibyte_pixel(
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut prev_row: png_const_bytep,
) {
    let mut bpp: libc::c_uint = ((*row_info).pixel_depth as libc::c_int
        + 7 as libc::c_int >> 3 as libc::c_int) as libc::c_uint;
    let mut rp_end: png_bytep = row.offset(bpp as isize);
    while row < rp_end {
        let fresh15 = prev_row;
        prev_row = prev_row.offset(1);
        let mut a: libc::c_int = *row as libc::c_int + *fresh15 as libc::c_int;
        let fresh16 = row;
        row = row.offset(1);
        *fresh16 = a as png_byte;
    }
    rp_end = rp_end.offset(((*row_info).rowbytes).wrapping_sub(bpp as size_t) as isize);
    while row < rp_end {
        let mut a_0: libc::c_int = 0;
        let mut b: libc::c_int = 0;
        let mut c: libc::c_int = 0;
        let mut pa: libc::c_int = 0;
        let mut pb: libc::c_int = 0;
        let mut pc: libc::c_int = 0;
        let mut p: libc::c_int = 0;
        c = *prev_row.offset(-(bpp as isize)) as libc::c_int;
        a_0 = *row.offset(-(bpp as isize)) as libc::c_int;
        let fresh17 = prev_row;
        prev_row = prev_row.offset(1);
        b = *fresh17 as libc::c_int;
        p = b - c;
        pc = a_0 - c;
        pa = if p < 0 as libc::c_int { -p } else { p };
        pb = if pc < 0 as libc::c_int { -pc } else { pc };
        pc = if p + pc < 0 as libc::c_int { -(p + pc) } else { p + pc };
        if pb < pa {
            pa = pb;
            a_0 = b;
        }
        if pc < pa {
            a_0 = c;
        }
        a_0 += *row as libc::c_int;
        let fresh18 = row;
        row = row.offset(1);
        *fresh18 = a_0 as png_byte;
    }
}
unsafe extern "C" fn png_init_filter_functions(mut pp: png_structrp) {
    let mut bpp: libc::c_uint = ((*pp).pixel_depth as libc::c_int + 7 as libc::c_int
        >> 3 as libc::c_int) as libc::c_uint;
    (*pp)
        .read_filter[(1 as libc::c_int - 1 as libc::c_int)
        as usize] = Some(
        png_read_filter_row_sub
            as unsafe extern "C" fn(png_row_infop, png_bytep, png_const_bytep) -> (),
    );
    (*pp)
        .read_filter[(2 as libc::c_int - 1 as libc::c_int)
        as usize] = Some(
        png_read_filter_row_up
            as unsafe extern "C" fn(png_row_infop, png_bytep, png_const_bytep) -> (),
    );
    (*pp)
        .read_filter[(3 as libc::c_int - 1 as libc::c_int)
        as usize] = Some(
        png_read_filter_row_avg
            as unsafe extern "C" fn(png_row_infop, png_bytep, png_const_bytep) -> (),
    );
    if bpp == 1 as libc::c_int as libc::c_uint {
        (*pp)
            .read_filter[(4 as libc::c_int - 1 as libc::c_int)
            as usize] = Some(
            png_read_filter_row_paeth_1byte_pixel
                as unsafe extern "C" fn(png_row_infop, png_bytep, png_const_bytep) -> (),
        );
    } else {
        (*pp)
            .read_filter[(4 as libc::c_int - 1 as libc::c_int)
            as usize] = Some(
            png_read_filter_row_paeth_multibyte_pixel
                as unsafe extern "C" fn(png_row_infop, png_bytep, png_const_bytep) -> (),
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_read_filter_row(
    mut pp: png_structrp,
    mut row_info: png_row_infop,
    mut row: png_bytep,
    mut prev_row: png_const_bytep,
    mut filter: libc::c_int,
) {
    if filter > 0 as libc::c_int && filter < 5 as libc::c_int {
        if ((*pp).read_filter[0 as libc::c_int as usize]).is_none() {
            png_init_filter_functions(pp);
        }
        ((*pp).read_filter[(filter - 1 as libc::c_int) as usize])
            .expect("non-null function pointer")(row_info, row, prev_row);
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_IDAT_data(
    mut png_ptr: png_structrp,
    mut output: png_bytep,
    mut avail_out: png_alloc_size_t,
) {
    (*png_ptr).zstream.next_out = output;
    (*png_ptr).zstream.avail_out = 0 as libc::c_int as uInt;
    if output.is_null() {
        avail_out = 0 as libc::c_int as png_alloc_size_t;
    }
    loop {
        let mut ret: libc::c_int = 0;
        let mut tmpbuf: [png_byte; 1024] = [0; 1024];
        if (*png_ptr).zstream.avail_in == 0 as libc::c_int as uInt {
            let mut avail_in: uInt = 0;
            let mut buffer: png_bytep = 0 as *mut png_byte;
            while (*png_ptr).idat_size == 0 as libc::c_int as png_uint_32 {
                png_crc_finish(png_ptr, 0 as libc::c_int as png_uint_32);
                (*png_ptr).idat_size = png_read_chunk_header(png_ptr);
                if (*png_ptr).chunk_name
                    != (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                        | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                        | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                        | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
                {
                    png_error(
                        png_ptr as png_const_structrp,
                        b"Not enough image data\0" as *const u8 as *const libc::c_char,
                    );
                }
            }
            avail_in = (*png_ptr).IDAT_read_size;
            if avail_in > (*png_ptr).idat_size {
                avail_in = (*png_ptr).idat_size;
            }
            buffer = png_read_buffer(
                png_ptr,
                avail_in as png_alloc_size_t,
                0 as libc::c_int,
            );
            png_crc_read(png_ptr, buffer, avail_in);
            (*png_ptr)
                .idat_size = ((*png_ptr).idat_size as libc::c_uint)
                .wrapping_sub(avail_in) as png_uint_32 as png_uint_32;
            (*png_ptr).zstream.next_in = buffer as *const Bytef;
            (*png_ptr).zstream.avail_in = avail_in;
        }
        if !output.is_null() {
            let mut out: uInt = -(1 as libc::c_int) as uInt;
            if out as png_alloc_size_t > avail_out {
                out = avail_out as uInt;
            }
            avail_out = avail_out.wrapping_sub(out as png_alloc_size_t);
            (*png_ptr).zstream.avail_out = out;
        } else {
            (*png_ptr).zstream.next_out = tmpbuf.as_mut_ptr();
            (*png_ptr)
                .zstream
                .avail_out = ::core::mem::size_of::<[png_byte; 1024]>() as libc::c_ulong
                as uInt;
        }
        ret = png_zlib_inflate(png_ptr, 0 as libc::c_int);
        if !output.is_null() {
            avail_out = avail_out
                .wrapping_add((*png_ptr).zstream.avail_out as png_alloc_size_t);
        } else {
            avail_out = (avail_out as libc::c_ulong)
                .wrapping_add(
                    (::core::mem::size_of::<[png_byte; 1024]>() as libc::c_ulong)
                        .wrapping_sub((*png_ptr).zstream.avail_out as libc::c_ulong),
                ) as png_alloc_size_t as png_alloc_size_t;
        }
        (*png_ptr).zstream.avail_out = 0 as libc::c_int as uInt;
        if ret == 1 as libc::c_int {
            (*png_ptr).zstream.next_out = 0 as *mut Bytef;
            (*png_ptr).mode |= 0x8 as libc::c_int as png_uint_32;
            (*png_ptr).flags |= 0x8 as libc::c_uint;
            if (*png_ptr).zstream.avail_in > 0 as libc::c_int as uInt
                || (*png_ptr).idat_size > 0 as libc::c_int as png_uint_32
            {
                png_chunk_benign_error(
                    png_ptr as png_const_structrp,
                    b"Extra compressed data\0" as *const u8 as *const libc::c_char,
                );
            }
            break;
        } else {
            if ret != 0 as libc::c_int {
                png_zstream_error(png_ptr, ret);
                if !output.is_null() {
                    png_chunk_error(
                        png_ptr as png_const_structrp,
                        (*png_ptr).zstream.msg,
                    );
                } else {
                    png_chunk_benign_error(
                        png_ptr as png_const_structrp,
                        (*png_ptr).zstream.msg,
                    );
                    return;
                }
            }
            if !(avail_out > 0 as libc::c_int as png_alloc_size_t) {
                break;
            }
        }
    }
    if avail_out > 0 as libc::c_int as png_alloc_size_t {
        if !output.is_null() {
            png_error(
                png_ptr as png_const_structrp,
                b"Not enough image data\0" as *const u8 as *const libc::c_char,
            );
        } else {
            png_chunk_benign_error(
                png_ptr as png_const_structrp,
                b"Too much image data\0" as *const u8 as *const libc::c_char,
            );
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_finish_IDAT(mut png_ptr: png_structrp) {
    if (*png_ptr).flags & 0x8 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        png_read_IDAT_data(
            png_ptr,
            0 as png_bytep,
            0 as libc::c_int as png_alloc_size_t,
        );
        (*png_ptr).zstream.next_out = 0 as *mut Bytef;
        if (*png_ptr).flags & 0x8 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
            (*png_ptr).mode |= 0x8 as libc::c_int as png_uint_32;
            (*png_ptr).flags |= 0x8 as libc::c_uint;
        }
    }
    if (*png_ptr).zowner
        == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
    {
        (*png_ptr).zstream.next_in = 0 as *const Bytef;
        (*png_ptr).zstream.avail_in = 0 as libc::c_int as uInt;
        (*png_ptr).zowner = 0 as libc::c_int as png_uint_32;
        png_crc_finish(png_ptr, (*png_ptr).idat_size);
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_finish_row(mut png_ptr: png_structrp) {
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
        memset(
            (*png_ptr).prev_row as *mut libc::c_void,
            0 as libc::c_int,
            ((*png_ptr).rowbytes).wrapping_add(1 as libc::c_int as size_t),
        );
        loop {
            (*png_ptr).pass = ((*png_ptr).pass).wrapping_add(1);
            (*png_ptr).pass;
            if (*png_ptr).pass as libc::c_int >= 7 as libc::c_int {
                break;
            }
            (*png_ptr)
                .iwidth = ((*png_ptr).width)
                .wrapping_add(png_pass_inc[(*png_ptr).pass as usize] as png_uint_32)
                .wrapping_sub(1 as libc::c_int as png_uint_32)
                .wrapping_sub(png_pass_start[(*png_ptr).pass as usize] as png_uint_32)
                / png_pass_inc[(*png_ptr).pass as usize] as png_uint_32;
            if !((*png_ptr).transformations & 0x2 as libc::c_uint
                == 0 as libc::c_int as libc::c_uint)
            {
                break;
            }
            (*png_ptr)
                .num_rows = ((*png_ptr).height)
                .wrapping_add(png_pass_yinc[(*png_ptr).pass as usize] as png_uint_32)
                .wrapping_sub(1 as libc::c_int as png_uint_32)
                .wrapping_sub(png_pass_ystart[(*png_ptr).pass as usize] as png_uint_32)
                / png_pass_yinc[(*png_ptr).pass as usize] as png_uint_32;
            if !((*png_ptr).num_rows == 0 as libc::c_int as png_uint_32
                || (*png_ptr).iwidth == 0 as libc::c_int as png_uint_32)
            {
                break;
            }
        }
        if ((*png_ptr).pass as libc::c_int) < 7 as libc::c_int {
            return;
        }
    }
    png_read_finish_IDAT(png_ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_read_start_row(mut png_ptr: png_structrp) {
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
    let mut max_pixel_depth: libc::c_uint = 0;
    let mut row_bytes: size_t = 0;
    png_init_read_transformations(png_ptr);
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
        } else {
            (*png_ptr).num_rows = (*png_ptr).height;
        }
        (*png_ptr)
            .iwidth = ((*png_ptr).width)
            .wrapping_add(png_pass_inc[(*png_ptr).pass as usize] as png_uint_32)
            .wrapping_sub(1 as libc::c_int as png_uint_32)
            .wrapping_sub(png_pass_start[(*png_ptr).pass as usize] as png_uint_32)
            / png_pass_inc[(*png_ptr).pass as usize] as png_uint_32;
    } else {
        (*png_ptr).num_rows = (*png_ptr).height;
        (*png_ptr).iwidth = (*png_ptr).width;
    }
    max_pixel_depth = (*png_ptr).pixel_depth as libc::c_uint;
    (*png_ptr).maximum_pixel_depth = max_pixel_depth as png_byte;
    (*png_ptr).transformed_pixel_depth = 0 as libc::c_int as png_byte;
    row_bytes = (((*png_ptr).width).wrapping_add(7 as libc::c_int as png_uint_32)
        & !(7 as libc::c_int as png_uint_32)) as size_t;
    row_bytes = (if max_pixel_depth >= 8 as libc::c_int as libc::c_uint {
        row_bytes * (max_pixel_depth as size_t >> 3 as libc::c_int)
    } else {
        (row_bytes * max_pixel_depth as size_t).wrapping_add(7 as libc::c_int as size_t)
            >> 3 as libc::c_int
    })
        .wrapping_add(1 as libc::c_int as size_t)
        .wrapping_add(
            (max_pixel_depth.wrapping_add(7 as libc::c_int as libc::c_uint)
                >> 3 as libc::c_uint) as size_t,
        );
    if row_bytes.wrapping_add(48 as libc::c_int as size_t)
        > (*png_ptr).old_big_row_buf_size
    {
        png_free(png_ptr as png_const_structrp, (*png_ptr).big_row_buf as png_voidp);
        png_free(png_ptr as png_const_structrp, (*png_ptr).big_prev_row as png_voidp);
        if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int {
            (*png_ptr)
                .big_row_buf = png_calloc(
                png_ptr as png_const_structrp,
                row_bytes.wrapping_add(48 as libc::c_int as size_t),
            ) as png_bytep;
        } else {
            (*png_ptr)
                .big_row_buf = png_malloc(
                png_ptr as png_const_structrp,
                row_bytes.wrapping_add(48 as libc::c_int as size_t),
            ) as png_bytep;
        }
        (*png_ptr)
            .big_prev_row = png_malloc(
            png_ptr as png_const_structrp,
            row_bytes.wrapping_add(48 as libc::c_int as size_t),
        ) as png_bytep;
        let mut temp: png_bytep = ((*png_ptr).big_row_buf)
            .offset(32 as libc::c_int as isize);
        let mut extra: size_t = temp as size_t & 0xf as libc::c_int as size_t;
        (*png_ptr)
            .row_buf = temp
            .offset(-(extra as isize))
            .offset(-(1 as libc::c_int as isize));
        temp = ((*png_ptr).big_prev_row).offset(32 as libc::c_int as isize);
        extra = temp as size_t & 0xf as libc::c_int as size_t;
        (*png_ptr)
            .prev_row = temp
            .offset(-(extra as isize))
            .offset(-(1 as libc::c_int as isize));
        (*png_ptr)
            .old_big_row_buf_size = row_bytes.wrapping_add(48 as libc::c_int as size_t);
    }
    if (*png_ptr).rowbytes
        > (-(1 as libc::c_int) as size_t).wrapping_sub(1 as libc::c_int as size_t)
    {
        png_error(
            png_ptr as png_const_structrp,
            b"Row has too many bytes to allocate in memory\0" as *const u8
                as *const libc::c_char,
        );
    }
    memset(
        (*png_ptr).prev_row as *mut libc::c_void,
        0 as libc::c_int,
        ((*png_ptr).rowbytes).wrapping_add(1 as libc::c_int as size_t),
    );
    if !((*png_ptr).read_buffer).is_null() {
        let mut buffer: png_bytep = (*png_ptr).read_buffer;
        (*png_ptr).read_buffer_size = 0 as libc::c_int as png_alloc_size_t;
        (*png_ptr).read_buffer = 0 as png_bytep;
        png_free(png_ptr as png_const_structrp, buffer as png_voidp);
    }
    if png_inflate_claim(
        png_ptr,
        (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
    ) != 0 as libc::c_int
    {
        png_error(png_ptr as png_const_structrp, (*png_ptr).zstream.msg);
    }
    (*png_ptr).flags |= 0x40 as libc::c_uint;
}
unsafe extern "C" fn run_static_initializers() {
    row_mask = [
        [
            [
                (if (if (0 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (2 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (4 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (0 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (2 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (4 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (0 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (2 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (4 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
        ],
        [
            [
                (if (if (0 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (2 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (4 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (0 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (2 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (4 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (0 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (0 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 0 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (2 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (2 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 2 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (4 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (4 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 4 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0x80088822 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xaa55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0x80088822 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xaa55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
        ],
    ];
    display_mask = [
        [
            [
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 0 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 0 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
        ],
        [
            [
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (1 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 1 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 1 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (1 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 1 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 1 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 1 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 1 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (2 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 2 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 2 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (2 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 2 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 2 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 2 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 2 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
            [
                (if (if (1 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (1 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 1 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (3 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (3 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 3 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
                (if (if (5 as libc::c_int) < 4 as libc::c_int {
                    0xff0fff33 as libc::c_uint
                        >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                } else {
                    0xff55ff00 as libc::c_uint
                        >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                            + (7 as libc::c_int - 0 as libc::c_int)
                            & 0x1f as libc::c_int)
                }) & 1 as libc::c_int as libc::c_uint != 0
                {
                    ((1 as libc::c_uint) << (4 as libc::c_int & 0x1f as libc::c_int))
                        .wrapping_sub(1 as libc::c_int as libc::c_uint)
                        << ((0 as libc::c_int * 4 as libc::c_int
                            ^ (if 1 as libc::c_int != 0 {
                                8 as libc::c_int - 4 as libc::c_int
                            } else {
                                0 as libc::c_int
                            })) & 0x1f as libc::c_int)
                } else {
                    0 as libc::c_int as libc::c_uint
                })
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 1 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((1 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 2 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((2 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 3 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((3 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 4 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((4 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 5 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((5 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 6 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((6 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_add(
                        (if (if (5 as libc::c_int) < 4 as libc::c_int {
                            0xff0fff33 as libc::c_uint
                                >> ((3 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        } else {
                            0xff55ff00 as libc::c_uint
                                >> ((7 as libc::c_int - 5 as libc::c_int) * 8 as libc::c_int
                                    + (7 as libc::c_int - 7 as libc::c_int)
                                    & 0x1f as libc::c_int)
                        }) & 1 as libc::c_int as libc::c_uint != 0
                        {
                            ((1 as libc::c_uint)
                                << (4 as libc::c_int & 0x1f as libc::c_int))
                                .wrapping_sub(1 as libc::c_int as libc::c_uint)
                                << ((7 as libc::c_int * 4 as libc::c_int
                                    ^ (if 1 as libc::c_int != 0 {
                                        8 as libc::c_int - 4 as libc::c_int
                                    } else {
                                        0 as libc::c_int
                                    })) & 0x1f as libc::c_int)
                        } else {
                            0 as libc::c_int as libc::c_uint
                        }),
                    )
                    .wrapping_mul(
                        (if 4 as libc::c_int == 1 as libc::c_int {
                            0x1010101 as libc::c_int
                        } else {
                            (if 4 as libc::c_int == 2 as libc::c_int {
                                0x10001 as libc::c_int
                            } else {
                                1 as libc::c_int
                            })
                        }) as libc::c_uint,
                    ),
            ],
        ],
    ];
}
#[used]
#[cfg_attr(target_os = "linux", link_section = ".init_array")]
#[cfg_attr(target_os = "windows", link_section = ".CRT$XIB")]
#[cfg_attr(target_os = "macos", link_section = "__DATA,__mod_init_func")]
static INIT_ARRAY: [unsafe extern "C" fn(); 1] = [run_static_initializers];
