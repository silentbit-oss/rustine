use ::libc;
extern "C" {
    pub type internal_state;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn png_create_png_struct(
        user_png_ver: png_const_charp,
        error_ptr: png_voidp,
        error_fn: png_error_ptr,
        warn_fn: png_error_ptr,
        mem_ptr: png_voidp,
        malloc_fn: png_malloc_ptr,
        free_fn: png_free_ptr,
    ) -> png_structp;
    fn png_destroy_png_struct(png_ptr: png_structrp);
    fn png_zfree(png_ptr: voidpf, ptr: voidpf);
    fn png_read_sig(png_ptr: png_structrp, info_ptr: png_inforp);
    fn png_read_chunk_header(png_ptr: png_structrp) -> png_uint_32;
    fn png_crc_finish(png_ptr: png_structrp, skip: png_uint_32) -> libc::c_int;
    fn png_combine_row(
        png_ptr: png_const_structrp,
        row: png_bytep,
        display: libc::c_int,
    );
    fn png_do_read_interlace(
        row_info: png_row_infop,
        row: png_bytep,
        pass: libc::c_int,
        transformations: png_uint_32,
    );
    fn png_read_filter_row(
        pp: png_structrp,
        row_info: png_row_infop,
        row: png_bytep,
        prev_row: png_const_bytep,
        filter: libc::c_int,
    );
    fn png_read_IDAT_data(
        png_ptr: png_structrp,
        output: png_bytep,
        avail_out: png_alloc_size_t,
    );
    fn png_read_finish_IDAT(png_ptr: png_structrp);
    fn png_read_finish_row(png_ptr: png_structrp);
    fn png_read_start_row(png_ptr: png_structrp);
    fn png_read_transform_info(png_ptr: png_structrp, info_ptr: png_inforp);
    fn png_handle_IHDR(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_PLTE(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_IEND(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_bKGD(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_hIST(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_sBIT(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_tRNS(png_ptr: png_structrp, info_ptr: png_inforp, length: png_uint_32);
    fn png_handle_unknown(
        png_ptr: png_structrp,
        info_ptr: png_inforp,
        length: png_uint_32,
        keep: libc::c_int,
    );
    fn png_chunk_unknown_handling(
        png_ptr: png_const_structrp,
        chunk_name: png_uint_32,
    ) -> libc::c_int;
    fn png_do_read_transformations(png_ptr: png_structrp, row_info: png_row_infop);
    fn png_app_error(png_ptr: png_const_structrp, message: png_const_charp);
    fn png_set_interlace_handling(png_ptr: png_structrp) -> libc::c_int;
    fn png_destroy_info_struct(png_ptr: png_const_structrp, info_ptr_ptr: png_infopp);
    fn png_set_read_fn(
        png_ptr: png_structrp,
        io_ptr: png_voidp,
        read_data_fn: png_rw_ptr,
    );
    fn png_malloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_free(png_ptr: png_const_structrp, ptr: png_voidp);
    fn png_free_data(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        free_me: png_uint_32,
        num: libc::c_int,
    );
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_chunk_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_warning(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_benign_error(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_chunk_benign_error(
        png_ptr: png_const_structrp,
        warning_message: png_const_charp,
    );
    fn inflateEnd(strm: z_streamp) -> libc::c_int;
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
pub type png_uint_16p = *mut png_uint_16;
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
pub type png_structpp = *mut *mut png_struct;
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
pub type png_infopp = *mut *mut png_info;
pub type png_structrp = *mut png_struct;
pub type png_const_structrp = *const png_struct;
pub type png_inforp = *mut png_info;
pub type png_malloc_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_alloc_size_t) -> png_voidp,
>;
pub type png_free_ptr = Option::<unsafe extern "C" fn(png_structp, png_voidp) -> ()>;
pub type z_streamp = *mut z_stream;
pub type voidp = *mut libc::c_void;
#[no_mangle]
pub unsafe extern "C" fn png_create_read_struct(
    mut user_png_ver: png_const_charp,
    mut error_ptr: png_voidp,
    mut error_fn: png_error_ptr,
    mut warn_fn: png_error_ptr,
) -> png_structp {
    let mut png_ptr: png_structp = png_create_png_struct(
        user_png_ver,
        error_ptr,
        error_fn,
        warn_fn,
        0 as *mut libc::c_void,
        None,
        None,
    );
    if !png_ptr.is_null() {
        (*png_ptr).mode = 0x8000 as libc::c_uint;
        (*png_ptr).IDAT_read_size = 8192 as libc::c_int as uInt;
        (*png_ptr).flags |= 0x100000 as libc::c_uint;
        (*png_ptr).flags |= 0x200000 as libc::c_uint;
        png_set_read_fn(png_ptr, 0 as *mut libc::c_void, None);
    }
    return png_ptr;
}
#[no_mangle]
pub unsafe extern "C" fn png_read_info(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
) {
    let mut keep: libc::c_int = 0;
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    png_read_sig(png_ptr, info_ptr);
    loop {
        let mut length: png_uint_32 = png_read_chunk_header(png_ptr);
        let mut chunk_name: png_uint_32 = (*png_ptr).chunk_name;
        if chunk_name
            == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            if (*png_ptr).mode & 0x1 as libc::c_int as png_uint_32
                == 0 as libc::c_int as png_uint_32
            {
                png_chunk_error(
                    png_ptr as png_const_structrp,
                    b"Missing IHDR before IDAT\0" as *const u8 as *const libc::c_char,
                );
            } else if (*png_ptr).color_type as libc::c_int
                == 2 as libc::c_int | 1 as libc::c_int
                && (*png_ptr).mode & 0x2 as libc::c_int as png_uint_32
                    == 0 as libc::c_int as png_uint_32
            {
                png_chunk_error(
                    png_ptr as png_const_structrp,
                    b"Missing PLTE before IDAT\0" as *const u8 as *const libc::c_char,
                );
            } else if (*png_ptr).mode & 0x8 as libc::c_int as png_uint_32
                != 0 as libc::c_int as png_uint_32
            {
                png_chunk_benign_error(
                    png_ptr as png_const_structrp,
                    b"Too many IDATs found\0" as *const u8 as *const libc::c_char,
                );
            }
            (*png_ptr).mode |= 0x4 as libc::c_uint;
        } else if (*png_ptr).mode & 0x4 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
        {
            (*png_ptr).mode |= 0x2000 as libc::c_uint;
            (*png_ptr).mode |= 0x8 as libc::c_int as png_uint_32;
        }
        if chunk_name
            == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (72 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (82 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            png_handle_IHDR(png_ptr, info_ptr, length);
        } else if chunk_name
            == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (69 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            png_handle_IEND(png_ptr, info_ptr, length);
        } else {
            keep = png_chunk_unknown_handling(png_ptr as png_const_structrp, chunk_name);
            if keep != 0 as libc::c_int {
                png_handle_unknown(png_ptr, info_ptr, length, keep);
                if chunk_name
                    == (80 as libc::c_int as png_uint_32) << 24 as libc::c_int
                        | (76 as libc::c_int as png_uint_32) << 16 as libc::c_int
                        | (84 as libc::c_int as png_uint_32) << 8 as libc::c_int
                        | (69 as libc::c_int as png_uint_32) << 0 as libc::c_int
                {
                    (*png_ptr).mode |= 0x2 as libc::c_int as png_uint_32;
                } else {
                    if !(chunk_name
                        == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int)
                    {
                        continue;
                    }
                    (*png_ptr).idat_size = 0 as libc::c_int as png_uint_32;
                    break;
                }
            } else if chunk_name
                == (80 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (76 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (69 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_PLTE(png_ptr, info_ptr, length);
            } else if chunk_name
                == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                (*png_ptr).idat_size = length;
                break;
            } else if chunk_name
                == (98 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (75 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (71 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_bKGD(png_ptr, info_ptr, length);
            } else if chunk_name
                == (104 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (73 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (83 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_hIST(png_ptr, info_ptr, length);
            } else if chunk_name
                == (115 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (66 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (73 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_sBIT(png_ptr, info_ptr, length);
            } else if chunk_name
                == (116 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (82 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (83 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_tRNS(png_ptr, info_ptr, length);
            } else {
                png_handle_unknown(png_ptr, info_ptr, length, 0 as libc::c_int);
            }
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_read_update_info(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
) {
    if !png_ptr.is_null() {
        if (*png_ptr).flags & 0x40 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
            png_read_start_row(png_ptr);
            png_read_transform_info(png_ptr, info_ptr);
        } else {
            png_app_error(
                png_ptr as png_const_structrp,
                b"png_read_update_info/png_start_read_image: duplicate call\0"
                    as *const u8 as *const libc::c_char,
            );
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_start_read_image(mut png_ptr: png_structrp) {
    if !png_ptr.is_null() {
        if (*png_ptr).flags & 0x40 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
            png_read_start_row(png_ptr);
        } else {
            png_app_error(
                png_ptr as png_const_structrp,
                b"png_start_read_image/png_read_update_info: duplicate call\0"
                    as *const u8 as *const libc::c_char,
            );
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_row(
    mut png_ptr: png_structrp,
    mut row: png_bytep,
    mut dsp_row: png_bytep,
) {
    let mut row_info: png_row_info = png_row_info_struct {
        width: 0,
        rowbytes: 0,
        color_type: 0,
        bit_depth: 0,
        channels: 0,
        pixel_depth: 0,
    };
    if png_ptr.is_null() {
        return;
    }
    if (*png_ptr).flags & 0x40 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        png_read_start_row(png_ptr);
    }
    row_info.width = (*png_ptr).iwidth;
    row_info.color_type = (*png_ptr).color_type;
    row_info.bit_depth = (*png_ptr).bit_depth;
    row_info.channels = (*png_ptr).channels;
    row_info.pixel_depth = (*png_ptr).pixel_depth;
    row_info
        .rowbytes = if row_info.pixel_depth as libc::c_int >= 8 as libc::c_int {
        row_info.width as size_t * (row_info.pixel_depth as size_t >> 3 as libc::c_int)
    } else {
        (row_info.width as size_t * row_info.pixel_depth as size_t)
            .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
    };
    (*png_ptr).row_number == 0 as libc::c_int as png_uint_32
        && (*png_ptr).pass as libc::c_int == 0 as libc::c_int;
    if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int
        && (*png_ptr).transformations & 0x2 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
    {
        match (*png_ptr).pass as libc::c_int {
            0 => {
                if (*png_ptr).row_number & 0x7 as libc::c_int as png_uint_32 != 0 {
                    if !dsp_row.is_null() {
                        png_combine_row(
                            png_ptr as png_const_structrp,
                            dsp_row,
                            1 as libc::c_int,
                        );
                    }
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
            1 => {
                if (*png_ptr).row_number & 0x7 as libc::c_int as png_uint_32 != 0
                    || (*png_ptr).width < 5 as libc::c_int as png_uint_32
                {
                    if !dsp_row.is_null() {
                        png_combine_row(
                            png_ptr as png_const_structrp,
                            dsp_row,
                            1 as libc::c_int,
                        );
                    }
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
            2 => {
                if (*png_ptr).row_number & 0x7 as libc::c_int as png_uint_32
                    != 4 as libc::c_int as png_uint_32
                {
                    if !dsp_row.is_null()
                        && (*png_ptr).row_number & 4 as libc::c_int as png_uint_32 != 0
                    {
                        png_combine_row(
                            png_ptr as png_const_structrp,
                            dsp_row,
                            1 as libc::c_int,
                        );
                    }
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
            3 => {
                if (*png_ptr).row_number & 3 as libc::c_int as png_uint_32 != 0
                    || (*png_ptr).width < 3 as libc::c_int as png_uint_32
                {
                    if !dsp_row.is_null() {
                        png_combine_row(
                            png_ptr as png_const_structrp,
                            dsp_row,
                            1 as libc::c_int,
                        );
                    }
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
            4 => {
                if (*png_ptr).row_number & 3 as libc::c_int as png_uint_32
                    != 2 as libc::c_int as png_uint_32
                {
                    if !dsp_row.is_null()
                        && (*png_ptr).row_number & 2 as libc::c_int as png_uint_32 != 0
                    {
                        png_combine_row(
                            png_ptr as png_const_structrp,
                            dsp_row,
                            1 as libc::c_int,
                        );
                    }
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
            5 => {
                if (*png_ptr).row_number & 1 as libc::c_int as png_uint_32 != 0
                    || (*png_ptr).width < 2 as libc::c_int as png_uint_32
                {
                    if !dsp_row.is_null() {
                        png_combine_row(
                            png_ptr as png_const_structrp,
                            dsp_row,
                            1 as libc::c_int,
                        );
                    }
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
            6 | _ => {
                if (*png_ptr).row_number & 1 as libc::c_int as png_uint_32
                    == 0 as libc::c_int as png_uint_32
                {
                    png_read_finish_row(png_ptr);
                    return;
                }
            }
        }
    }
    if (*png_ptr).mode & 0x4 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        png_error(
            png_ptr as png_const_structrp,
            b"Invalid attempt to read row data\0" as *const u8 as *const libc::c_char,
        );
    }
    *((*png_ptr).row_buf)
        .offset(0 as libc::c_int as isize) = 255 as libc::c_int as png_byte;
    png_read_IDAT_data(
        png_ptr,
        (*png_ptr).row_buf,
        (row_info.rowbytes).wrapping_add(1 as libc::c_int as size_t),
    );
    if *((*png_ptr).row_buf).offset(0 as libc::c_int as isize) as libc::c_int
        > 0 as libc::c_int
    {
        if (*((*png_ptr).row_buf).offset(0 as libc::c_int as isize) as libc::c_int)
            < 5 as libc::c_int
        {
            png_read_filter_row(
                png_ptr,
                &mut row_info,
                ((*png_ptr).row_buf).offset(1 as libc::c_int as isize),
                ((*png_ptr).prev_row).offset(1 as libc::c_int as isize)
                    as png_const_bytep,
                *((*png_ptr).row_buf).offset(0 as libc::c_int as isize) as libc::c_int,
            );
        } else {
            png_error(
                png_ptr as png_const_structrp,
                b"bad adaptive filter value\0" as *const u8 as *const libc::c_char,
            );
        }
    }
    memcpy(
        (*png_ptr).prev_row as *mut libc::c_void,
        (*png_ptr).row_buf as *const libc::c_void,
        (row_info.rowbytes).wrapping_add(1 as libc::c_int as size_t),
    );
    if (*png_ptr).transformations != 0 {
        png_do_read_transformations(png_ptr, &mut row_info);
    }
    if (*png_ptr).transformed_pixel_depth as libc::c_int == 0 as libc::c_int {
        (*png_ptr).transformed_pixel_depth = row_info.pixel_depth;
        if row_info.pixel_depth as libc::c_int
            > (*png_ptr).maximum_pixel_depth as libc::c_int
        {
            png_error(
                png_ptr as png_const_structrp,
                b"sequential row overflow\0" as *const u8 as *const libc::c_char,
            );
        }
    } else if (*png_ptr).transformed_pixel_depth as libc::c_int
        != row_info.pixel_depth as libc::c_int
    {
        png_error(
            png_ptr as png_const_structrp,
            b"internal sequential row size calculation error\0" as *const u8
                as *const libc::c_char,
        );
    }
    if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int
        && (*png_ptr).transformations & 0x2 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
    {
        if ((*png_ptr).pass as libc::c_int) < 6 as libc::c_int {
            png_do_read_interlace(
                &mut row_info,
                ((*png_ptr).row_buf).offset(1 as libc::c_int as isize),
                (*png_ptr).pass as libc::c_int,
                (*png_ptr).transformations,
            );
        }
        if !dsp_row.is_null() {
            png_combine_row(png_ptr as png_const_structrp, dsp_row, 1 as libc::c_int);
        }
        if !row.is_null() {
            png_combine_row(png_ptr as png_const_structrp, row, 0 as libc::c_int);
        }
    } else {
        if !row.is_null() {
            png_combine_row(png_ptr as png_const_structrp, row, -(1 as libc::c_int));
        }
        if !dsp_row.is_null() {
            png_combine_row(png_ptr as png_const_structrp, dsp_row, -(1 as libc::c_int));
        }
    }
    png_read_finish_row(png_ptr);
    if ((*png_ptr).read_row_fn).is_some() {
        (Some(((*png_ptr).read_row_fn).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )(png_ptr, (*png_ptr).row_number, (*png_ptr).pass as libc::c_int);
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_rows(
    mut png_ptr: png_structrp,
    mut row: png_bytepp,
    mut display_row: png_bytepp,
    mut num_rows: png_uint_32,
) {
    let mut i: png_uint_32 = 0;
    let mut rp: png_bytepp = 0 as *mut *mut png_byte;
    let mut dp: png_bytepp = 0 as *mut *mut png_byte;
    if png_ptr.is_null() {
        return;
    }
    rp = row;
    dp = display_row;
    if !rp.is_null() && !dp.is_null() {
        i = 0 as libc::c_int as png_uint_32;
        while i < num_rows {
            let fresh0 = rp;
            rp = rp.offset(1);
            let mut rptr: png_bytep = *fresh0;
            let fresh1 = dp;
            dp = dp.offset(1);
            let mut dptr: png_bytep = *fresh1;
            png_read_row(png_ptr, rptr, dptr);
            i = i.wrapping_add(1);
            i;
        }
    } else if !rp.is_null() {
        i = 0 as libc::c_int as png_uint_32;
        while i < num_rows {
            let mut rptr_0: png_bytep = *rp;
            png_read_row(png_ptr, rptr_0, 0 as png_bytep);
            rp = rp.offset(1);
            rp;
            i = i.wrapping_add(1);
            i;
        }
    } else if !dp.is_null() {
        i = 0 as libc::c_int as png_uint_32;
        while i < num_rows {
            let mut dptr_0: png_bytep = *dp;
            png_read_row(png_ptr, 0 as png_bytep, dptr_0);
            dp = dp.offset(1);
            dp;
            i = i.wrapping_add(1);
            i;
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_image(
    mut png_ptr: png_structrp,
    mut image: png_bytepp,
) {
    let mut i: png_uint_32 = 0;
    let mut image_height: png_uint_32 = 0;
    let mut pass: libc::c_int = 0;
    let mut j: libc::c_int = 0;
    let mut rp: png_bytepp = 0 as *mut *mut png_byte;
    if png_ptr.is_null() {
        return;
    }
    if (*png_ptr).flags & 0x40 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        pass = png_set_interlace_handling(png_ptr);
        png_start_read_image(png_ptr);
    } else {
        if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int
            && (*png_ptr).transformations & 0x2 as libc::c_uint
                == 0 as libc::c_int as libc::c_uint
        {
            png_warning(
                png_ptr as png_const_structrp,
                b"Interlace handling should be turned on when using png_read_image\0"
                    as *const u8 as *const libc::c_char,
            );
            (*png_ptr).num_rows = (*png_ptr).height;
        }
        pass = png_set_interlace_handling(png_ptr);
    }
    image_height = (*png_ptr).height;
    j = 0 as libc::c_int;
    while j < pass {
        rp = image;
        i = 0 as libc::c_int as png_uint_32;
        while i < image_height {
            png_read_row(png_ptr, *rp, 0 as png_bytep);
            rp = rp.offset(1);
            rp;
            i = i.wrapping_add(1);
            i;
        }
        j += 1;
        j;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_read_end(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
) {
    let mut keep: libc::c_int = 0;
    if png_ptr.is_null() {
        return;
    }
    if png_chunk_unknown_handling(
        png_ptr as png_const_structrp,
        (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
            | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
            | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
            | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int,
    ) == 0 as libc::c_int
    {
        png_read_finish_IDAT(png_ptr);
    }
    if (*png_ptr).color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int
        && (*png_ptr).num_palette_max > (*png_ptr).num_palette as libc::c_int
    {
        png_benign_error(
            png_ptr as png_const_structrp,
            b"Read palette index exceeding num_palette\0" as *const u8
                as *const libc::c_char,
        );
    }
    loop {
        let mut length: png_uint_32 = png_read_chunk_header(png_ptr);
        let mut chunk_name: png_uint_32 = (*png_ptr).chunk_name;
        if chunk_name
            != (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            (*png_ptr).mode |= 0x2000 as libc::c_uint;
        }
        if chunk_name
            == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (69 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            png_handle_IEND(png_ptr, info_ptr, length);
        } else if chunk_name
            == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                | (72 as libc::c_int as png_uint_32) << 16 as libc::c_int
                | (68 as libc::c_int as png_uint_32) << 8 as libc::c_int
                | (82 as libc::c_int as png_uint_32) << 0 as libc::c_int
        {
            png_handle_IHDR(png_ptr, info_ptr, length);
        } else if info_ptr.is_null() {
            png_crc_finish(png_ptr, length);
        } else {
            keep = png_chunk_unknown_handling(png_ptr as png_const_structrp, chunk_name);
            if keep != 0 as libc::c_int {
                if chunk_name
                    == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                        | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                        | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                        | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
                {
                    if length > 0 as libc::c_int as png_uint_32
                        && (*png_ptr).flags & 0x8 as libc::c_uint == 0
                        || (*png_ptr).mode & 0x2000 as libc::c_uint
                            != 0 as libc::c_int as libc::c_uint
                    {
                        png_benign_error(
                            png_ptr as png_const_structrp,
                            b".Too many IDATs found\0" as *const u8
                                as *const libc::c_char,
                        );
                    }
                }
                png_handle_unknown(png_ptr, info_ptr, length, keep);
                if chunk_name
                    == (80 as libc::c_int as png_uint_32) << 24 as libc::c_int
                        | (76 as libc::c_int as png_uint_32) << 16 as libc::c_int
                        | (84 as libc::c_int as png_uint_32) << 8 as libc::c_int
                        | (69 as libc::c_int as png_uint_32) << 0 as libc::c_int
                {
                    (*png_ptr).mode |= 0x2 as libc::c_int as png_uint_32;
                }
            } else if chunk_name
                == (73 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (68 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (65 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                if length > 0 as libc::c_int as png_uint_32
                    && (*png_ptr).flags & 0x8 as libc::c_uint == 0
                    || (*png_ptr).mode & 0x2000 as libc::c_uint
                        != 0 as libc::c_int as libc::c_uint
                {
                    png_benign_error(
                        png_ptr as png_const_structrp,
                        b"..Too many IDATs found\0" as *const u8 as *const libc::c_char,
                    );
                }
                png_crc_finish(png_ptr, length);
            } else if chunk_name
                == (80 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (76 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (69 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_PLTE(png_ptr, info_ptr, length);
            } else if chunk_name
                == (98 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (75 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (71 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (68 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_bKGD(png_ptr, info_ptr, length);
            } else if chunk_name
                == (104 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (73 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (83 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_hIST(png_ptr, info_ptr, length);
            } else if chunk_name
                == (115 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (66 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (73 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (84 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_sBIT(png_ptr, info_ptr, length);
            } else if chunk_name
                == (116 as libc::c_int as png_uint_32) << 24 as libc::c_int
                    | (82 as libc::c_int as png_uint_32) << 16 as libc::c_int
                    | (78 as libc::c_int as png_uint_32) << 8 as libc::c_int
                    | (83 as libc::c_int as png_uint_32) << 0 as libc::c_int
            {
                png_handle_tRNS(png_ptr, info_ptr, length);
            } else {
                png_handle_unknown(png_ptr, info_ptr, length, 0 as libc::c_int);
            }
        }
        if !((*png_ptr).mode & 0x10 as libc::c_uint == 0 as libc::c_int as libc::c_uint)
        {
            break;
        }
    };
}
unsafe extern "C" fn png_read_destroy(mut png_ptr: png_structrp) {
    png_free(png_ptr as png_const_structrp, (*png_ptr).big_row_buf as png_voidp);
    (*png_ptr).big_row_buf = 0 as png_bytep;
    png_free(png_ptr as png_const_structrp, (*png_ptr).big_prev_row as png_voidp);
    (*png_ptr).big_prev_row = 0 as png_bytep;
    png_free(png_ptr as png_const_structrp, (*png_ptr).read_buffer as png_voidp);
    (*png_ptr).read_buffer = 0 as png_bytep;
    if (*png_ptr).free_me & 0x1000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_zfree(png_ptr as voidpf, (*png_ptr).palette as voidpf);
        (*png_ptr).palette = 0 as png_colorp;
    }
    (*png_ptr).free_me &= !(0x1000 as libc::c_uint);
    if (*png_ptr).free_me & 0x2000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_free(png_ptr as png_const_structrp, (*png_ptr).trans_alpha as png_voidp);
        (*png_ptr).trans_alpha = 0 as png_bytep;
    }
    (*png_ptr).free_me &= !(0x2000 as libc::c_uint);
    inflateEnd(&mut (*png_ptr).zstream);
    png_free(png_ptr as png_const_structrp, (*png_ptr).unknown_chunk.data as png_voidp);
    (*png_ptr).unknown_chunk.data = 0 as *mut png_byte;
    png_free(png_ptr as png_const_structrp, (*png_ptr).chunk_list as png_voidp);
    (*png_ptr).chunk_list = 0 as png_bytep;
}
#[no_mangle]
pub unsafe extern "C" fn png_destroy_read_struct(
    mut png_ptr_ptr: png_structpp,
    mut info_ptr_ptr: png_infopp,
    mut end_info_ptr_ptr: png_infopp,
) {
    let mut png_ptr: png_structrp = 0 as png_structrp;
    if !png_ptr_ptr.is_null() {
        png_ptr = *png_ptr_ptr;
    }
    if png_ptr.is_null() {
        return;
    }
    png_destroy_info_struct(png_ptr as png_const_structrp, end_info_ptr_ptr);
    png_destroy_info_struct(png_ptr as png_const_structrp, info_ptr_ptr);
    *png_ptr_ptr = 0 as *mut png_struct;
    png_read_destroy(png_ptr);
    png_destroy_png_struct(png_ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_set_read_status_fn(
    mut png_ptr: png_structrp,
    mut read_row_fn: png_read_status_ptr,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).read_row_fn = read_row_fn;
}
#[no_mangle]
pub unsafe extern "C" fn png_read_png(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut transforms: libc::c_int,
    mut params: voidp,
) {
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    png_read_info(png_ptr, info_ptr);
    if (*info_ptr).height as libc::c_ulong
        > (-(1 as libc::c_int) as png_uint_32 as libc::c_ulong)
            .wrapping_div(::core::mem::size_of::<png_bytep>() as libc::c_ulong)
    {
        png_error(
            png_ptr as png_const_structrp,
            b"Image is too high to process with png_read_png()\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x8000 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_SCALE_16 not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x1 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_STRIP_16 not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x2 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_STRIP_ALPHA not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x4 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_PACKING not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x8 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_PACKSWAP not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x10 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_EXPAND not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x20 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_INVERT_MONO not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x40 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_SHIFT not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x80 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_BGR not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x100 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_SWAP_ALPHA not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x200 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_SWAP_ENDIAN not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x400 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_INVERT_ALPHA not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x2000 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_GRAY_TO_RGB not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x4000 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_EXPAND_16 not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
    png_free_data(
        png_ptr as png_const_structrp,
        info_ptr,
        0x40 as libc::c_uint,
        0 as libc::c_int,
    );
    if ((*info_ptr).row_pointers).is_null() {
        let mut iptr: png_uint_32 = 0;
        (*info_ptr)
            .row_pointers = png_malloc(
            png_ptr as png_const_structrp,
            ((*info_ptr).height as libc::c_ulong)
                .wrapping_mul(::core::mem::size_of::<png_bytep>() as libc::c_ulong),
        ) as png_bytepp;
        iptr = 0 as libc::c_int as png_uint_32;
        while iptr < (*info_ptr).height {
            let ref mut fresh2 = *((*info_ptr).row_pointers).offset(iptr as isize);
            *fresh2 = 0 as *mut png_byte;
            iptr = iptr.wrapping_add(1);
            iptr;
        }
        (*info_ptr).free_me |= 0x40 as libc::c_uint;
        iptr = 0 as libc::c_int as png_uint_32;
        while iptr < (*info_ptr).height {
            let ref mut fresh3 = *((*info_ptr).row_pointers).offset(iptr as isize);
            *fresh3 = png_malloc(png_ptr as png_const_structrp, (*info_ptr).rowbytes)
                as *mut png_byte;
            iptr = iptr.wrapping_add(1);
            iptr;
        }
    }
    png_read_image(png_ptr, (*info_ptr).row_pointers);
    (*info_ptr).valid |= 0x8000 as libc::c_uint;
    png_read_end(png_ptr, info_ptr);
}
