use ::libc;
extern "C" {
    pub type internal_state;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn png_free_buffer_list(png_ptr: png_structrp, list: *mut png_compression_bufferp);
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
    fn png_flush(png_ptr: png_structrp);
    fn png_write_IHDR(
        png_ptr: png_structrp,
        width: png_uint_32,
        height: png_uint_32,
        bit_depth: libc::c_int,
        color_type: libc::c_int,
        compression_method: libc::c_int,
        filter_method: libc::c_int,
        interlace_method: libc::c_int,
    );
    fn png_write_PLTE(
        png_ptr: png_structrp,
        palette: png_const_colorp,
        num_pal: png_uint_32,
    );
    fn png_compress_IDAT(
        png_ptr: png_structrp,
        row_data: png_const_bytep,
        row_data_length: png_alloc_size_t,
        flush: libc::c_int,
    );
    fn png_write_IEND(png_ptr: png_structrp);
    fn png_write_sBIT(
        png_ptr: png_structrp,
        sbit: png_const_color_8p,
        color_type: libc::c_int,
    );
    fn png_write_tRNS(
        png_ptr: png_structrp,
        trans: png_const_bytep,
        values: png_const_color_16p,
        number: libc::c_int,
        color_type: libc::c_int,
    );
    fn png_write_bKGD(
        png_ptr: png_structrp,
        values: png_const_color_16p,
        color_type: libc::c_int,
    );
    fn png_write_hIST(
        png_ptr: png_structrp,
        hist: png_const_uint_16p,
        num_hist: libc::c_int,
    );
    fn png_write_finish_row(png_ptr: png_structrp);
    fn png_write_start_row(png_ptr: png_structrp);
    fn png_do_write_interlace(
        row_info: png_row_infop,
        row: png_bytep,
        pass: libc::c_int,
    );
    fn png_write_find_filter(png_ptr: png_structrp, row_info: png_row_infop);
    fn png_do_check_palette_indexes(png_ptr: png_structrp, row_info: png_row_infop);
    fn png_app_warning(png_ptr: png_const_structrp, message: png_const_charp);
    fn png_app_error(png_ptr: png_const_structrp, message: png_const_charp);
    fn png_write_sig(png_ptr: png_structrp);
    fn png_write_chunk(
        png_ptr: png_structrp,
        chunk_name: png_const_bytep,
        data: png_const_bytep,
        length: size_t,
    );
    fn png_set_interlace_handling(png_ptr: png_structrp) -> libc::c_int;
    fn png_destroy_info_struct(png_ptr: png_const_structrp, info_ptr_ptr: png_infopp);
    fn png_set_write_fn(
        png_ptr: png_structrp,
        io_ptr: png_voidp,
        write_data_fn: png_rw_ptr,
        output_flush_fn: png_flush_ptr,
    );
    fn png_malloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_free(png_ptr: png_const_structrp, ptr: png_voidp);
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_warning(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_benign_error(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_handle_as_unknown(
        png_ptr: png_const_structrp,
        chunk_name: png_const_bytep,
    ) -> libc::c_int;
    fn deflateEnd(strm: z_streamp) -> libc::c_int;
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
pub type png_const_uint_16p = *const png_uint_16;
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
pub type png_const_inforp = *const png_info;
pub type png_const_colorp = *const png_color;
pub type png_const_color_16p = *const png_color_16;
pub type png_const_color_8p = *const png_color_8;
pub type png_const_unknown_chunkp = *const png_unknown_chunk;
pub type png_malloc_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_alloc_size_t) -> png_voidp,
>;
pub type png_free_ptr = Option::<unsafe extern "C" fn(png_structp, png_voidp) -> ()>;
pub type z_streamp = *mut z_stream;
pub type voidp = *mut libc::c_void;
unsafe extern "C" fn write_unknown_chunks(
    mut png_ptr: png_structrp,
    mut info_ptr: png_const_inforp,
    mut where_0: libc::c_uint,
) {
    if (*info_ptr).unknown_chunks_num != 0 as libc::c_int {
        let mut up: png_const_unknown_chunkp = 0 as *const png_unknown_chunk;
        up = (*info_ptr).unknown_chunks as png_const_unknown_chunkp;
        while up
            < ((*info_ptr).unknown_chunks)
                .offset((*info_ptr).unknown_chunks_num as isize)
                as png_const_unknown_chunkp
        {
            if (*up).location as libc::c_uint & where_0
                != 0 as libc::c_int as libc::c_uint
            {
                let mut keep: libc::c_int = png_handle_as_unknown(
                    png_ptr as png_const_structrp,
                    ((*up).name).as_ptr(),
                );
                if keep != 1 as libc::c_int
                    && ((*up).name[3 as libc::c_int as usize] as libc::c_int
                        & 0x20 as libc::c_int != 0 || keep == 3 as libc::c_int
                        || keep == 0 as libc::c_int
                            && (*png_ptr).unknown_default == 3 as libc::c_int)
                {
                    if (*up).size == 0 as libc::c_int as size_t {
                        png_warning(
                            png_ptr as png_const_structrp,
                            b"Writing zero-length unknown chunk\0" as *const u8
                                as *const libc::c_char,
                        );
                    }
                    png_write_chunk(
                        png_ptr,
                        ((*up).name).as_ptr(),
                        (*up).data as png_const_bytep,
                        (*up).size,
                    );
                }
            }
            up = up.offset(1);
            up;
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_info_before_PLTE(
    mut png_ptr: png_structrp,
    mut info_ptr: png_const_inforp,
) {
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    if (*png_ptr).mode & 0x400 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        png_write_sig(png_ptr);
        png_write_IHDR(
            png_ptr,
            (*info_ptr).width,
            (*info_ptr).height,
            (*info_ptr).bit_depth as libc::c_int,
            (*info_ptr).color_type as libc::c_int,
            (*info_ptr).compression_type as libc::c_int,
            (*info_ptr).filter_type as libc::c_int,
            (*info_ptr).interlace_type as libc::c_int,
        );
        if (*info_ptr).valid & 0x2 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
            png_write_sBIT(
                png_ptr,
                &(*info_ptr).sig_bit,
                (*info_ptr).color_type as libc::c_int,
            );
        }
        write_unknown_chunks(png_ptr, info_ptr, 0x1 as libc::c_int as libc::c_uint);
        (*png_ptr).mode |= 0x400 as libc::c_uint;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_info(
    mut png_ptr: png_structrp,
    mut info_ptr: png_const_inforp,
) {
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    png_write_info_before_PLTE(png_ptr, info_ptr);
    if (*info_ptr).valid & 0x8 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_write_PLTE(
            png_ptr,
            (*info_ptr).palette as png_const_colorp,
            (*info_ptr).num_palette as png_uint_32,
        );
    } else if (*info_ptr).color_type as libc::c_int
        == 2 as libc::c_int | 1 as libc::c_int
    {
        png_error(
            png_ptr as png_const_structrp,
            b"Valid palette required for paletted images\0" as *const u8
                as *const libc::c_char,
        );
    }
    if (*info_ptr).valid & 0x10 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_write_tRNS(
            png_ptr,
            (*info_ptr).trans_alpha as png_const_bytep,
            &(*info_ptr).trans_color,
            (*info_ptr).num_trans as libc::c_int,
            (*info_ptr).color_type as libc::c_int,
        );
    }
    if (*info_ptr).valid & 0x20 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_write_bKGD(
            png_ptr,
            &(*info_ptr).background,
            (*info_ptr).color_type as libc::c_int,
        );
    }
    if (*info_ptr).valid & 0x40 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_write_hIST(
            png_ptr,
            (*info_ptr).hist as png_const_uint_16p,
            (*info_ptr).num_palette as libc::c_int,
        );
    }
    write_unknown_chunks(png_ptr, info_ptr, 0x2 as libc::c_int as libc::c_uint);
}
#[no_mangle]
pub unsafe extern "C" fn png_write_end(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
) {
    if png_ptr.is_null() {
        return;
    }
    if (*png_ptr).mode & 0x4 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        png_error(
            png_ptr as png_const_structrp,
            b"No IDATs written into file\0" as *const u8 as *const libc::c_char,
        );
    }
    if (*png_ptr).num_palette_max > (*png_ptr).num_palette as libc::c_int {
        png_benign_error(
            png_ptr as png_const_structrp,
            b"Wrote palette index exceeding num_palette\0" as *const u8
                as *const libc::c_char,
        );
    }
    if !info_ptr.is_null() {
        write_unknown_chunks(
            png_ptr,
            info_ptr as png_const_inforp,
            0x8 as libc::c_int as libc::c_uint,
        );
    }
    (*png_ptr).mode |= 0x8 as libc::c_int as png_uint_32;
    png_write_IEND(png_ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_create_write_struct(
    mut user_png_ver: png_const_charp,
    mut error_ptr: png_voidp,
    mut error_fn: png_error_ptr,
    mut warn_fn: png_error_ptr,
) -> png_structp {
    let mut png_ptr: png_structrp = png_create_png_struct(
        user_png_ver,
        error_ptr,
        error_fn,
        warn_fn,
        0 as *mut libc::c_void,
        None,
        None,
    );
    if !png_ptr.is_null() {
        (*png_ptr).zbuffer_size = 8192 as libc::c_int as uInt;
        (*png_ptr).zlib_strategy = 1 as libc::c_int;
        (*png_ptr).zlib_level = -(1 as libc::c_int);
        (*png_ptr).zlib_mem_level = 8 as libc::c_int;
        (*png_ptr).zlib_window_bits = 15 as libc::c_int;
        (*png_ptr).zlib_method = 8 as libc::c_int;
        (*png_ptr).flags |= 0x200000 as libc::c_uint;
        png_set_write_fn(png_ptr, 0 as *mut libc::c_void, None, None);
    }
    return png_ptr;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_rows(
    mut png_ptr: png_structrp,
    mut row: png_bytepp,
    mut num_rows: png_uint_32,
) {
    let mut i: png_uint_32 = 0;
    let mut rp: png_bytepp = 0 as *mut *mut png_byte;
    if png_ptr.is_null() {
        return;
    }
    i = 0 as libc::c_int as png_uint_32;
    rp = row;
    while i < num_rows {
        png_write_row(png_ptr, *rp as png_const_bytep);
        i = i.wrapping_add(1);
        i;
        rp = rp.offset(1);
        rp;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_image(
    mut png_ptr: png_structrp,
    mut image: png_bytepp,
) {
    let mut i: png_uint_32 = 0;
    let mut pass: libc::c_int = 0;
    let mut num_pass: libc::c_int = 0;
    let mut rp: png_bytepp = 0 as *mut *mut png_byte;
    if png_ptr.is_null() {
        return;
    }
    num_pass = png_set_interlace_handling(png_ptr);
    pass = 0 as libc::c_int;
    while pass < num_pass {
        i = 0 as libc::c_int as png_uint_32;
        rp = image;
        while i < (*png_ptr).height {
            png_write_row(png_ptr, *rp as png_const_bytep);
            i = i.wrapping_add(1);
            i;
            rp = rp.offset(1);
            rp;
        }
        pass += 1;
        pass;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_write_row(
    mut png_ptr: png_structrp,
    mut row: png_const_bytep,
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
    if (*png_ptr).row_number == 0 as libc::c_int as png_uint_32
        && (*png_ptr).pass as libc::c_int == 0 as libc::c_int
    {
        if (*png_ptr).mode & 0x400 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
            png_error(
                png_ptr as png_const_structrp,
                b"png_write_info was never called before png_write_row\0" as *const u8
                    as *const libc::c_char,
            );
        }
        png_write_start_row(png_ptr);
    }
    if (*png_ptr).interlaced as libc::c_int != 0 as libc::c_int
        && (*png_ptr).transformations & 0x2 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
    {
        match (*png_ptr).pass as libc::c_int {
            0 => {
                if (*png_ptr).row_number & 0x7 as libc::c_int as png_uint_32
                    != 0 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            1 => {
                if (*png_ptr).row_number & 0x7 as libc::c_int as png_uint_32
                    != 0 as libc::c_int as png_uint_32
                    || (*png_ptr).width < 5 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            2 => {
                if (*png_ptr).row_number & 0x7 as libc::c_int as png_uint_32
                    != 4 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            3 => {
                if (*png_ptr).row_number & 0x3 as libc::c_int as png_uint_32
                    != 0 as libc::c_int as png_uint_32
                    || (*png_ptr).width < 3 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            4 => {
                if (*png_ptr).row_number & 0x3 as libc::c_int as png_uint_32
                    != 2 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            5 => {
                if (*png_ptr).row_number & 0x1 as libc::c_int as png_uint_32
                    != 0 as libc::c_int as png_uint_32
                    || (*png_ptr).width < 2 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            6 => {
                if (*png_ptr).row_number & 0x1 as libc::c_int as png_uint_32
                    == 0 as libc::c_int as png_uint_32
                {
                    png_write_finish_row(png_ptr);
                    return;
                }
            }
            _ => {}
        }
    }
    row_info.color_type = (*png_ptr).color_type;
    row_info.width = (*png_ptr).usr_width;
    row_info.channels = (*png_ptr).usr_channels;
    row_info.bit_depth = (*png_ptr).usr_bit_depth;
    row_info
        .pixel_depth = (row_info.bit_depth as libc::c_int
        * row_info.channels as libc::c_int) as png_byte;
    row_info
        .rowbytes = if row_info.pixel_depth as libc::c_int >= 8 as libc::c_int {
        row_info.width as size_t * (row_info.pixel_depth as size_t >> 3 as libc::c_int)
    } else {
        (row_info.width as size_t * row_info.pixel_depth as size_t)
            .wrapping_add(7 as libc::c_int as size_t) >> 3 as libc::c_int
    };
    memcpy(
        ((*png_ptr).row_buf).offset(1 as libc::c_int as isize) as *mut libc::c_void,
        row as *const libc::c_void,
        row_info.rowbytes,
    );
    if (*png_ptr).interlaced as libc::c_int != 0
        && ((*png_ptr).pass as libc::c_int) < 6 as libc::c_int
        && (*png_ptr).transformations & 0x2 as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
    {
        png_do_write_interlace(
            &mut row_info,
            ((*png_ptr).row_buf).offset(1 as libc::c_int as isize),
            (*png_ptr).pass as libc::c_int,
        );
        if row_info.width == 0 as libc::c_int as png_uint_32 {
            png_write_finish_row(png_ptr);
            return;
        }
    }
    if row_info.pixel_depth as libc::c_int != (*png_ptr).pixel_depth as libc::c_int
        || row_info.pixel_depth as libc::c_int
            != (*png_ptr).transformed_pixel_depth as libc::c_int
    {
        png_error(
            png_ptr as png_const_structrp,
            b"internal write transform logic error\0" as *const u8 as *const libc::c_char,
        );
    }
    if row_info.color_type as libc::c_int == 2 as libc::c_int | 1 as libc::c_int
        && (*png_ptr).num_palette_max >= 0 as libc::c_int
    {
        png_do_check_palette_indexes(png_ptr, &mut row_info);
    }
    png_write_find_filter(png_ptr, &mut row_info);
    if ((*png_ptr).write_row_fn).is_some() {
        (Some(((*png_ptr).write_row_fn).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )(png_ptr, (*png_ptr).row_number, (*png_ptr).pass as libc::c_int);
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_set_flush(
    mut png_ptr: png_structrp,
    mut nrows: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr)
        .flush_dist = if nrows < 0 as libc::c_int {
        0 as libc::c_int as png_uint_32
    } else {
        nrows as png_uint_32
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_write_flush(mut png_ptr: png_structrp) {
    if png_ptr.is_null() {
        return;
    }
    if (*png_ptr).row_number >= (*png_ptr).num_rows {
        return;
    }
    png_compress_IDAT(
        png_ptr,
        0 as png_const_bytep,
        0 as libc::c_int as png_alloc_size_t,
        2 as libc::c_int,
    );
    (*png_ptr).flush_rows = 0 as libc::c_int as png_uint_32;
    png_flush(png_ptr);
}
unsafe extern "C" fn png_write_destroy(mut png_ptr: png_structrp) {
    if (*png_ptr).flags & 0x2 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        deflateEnd(&mut (*png_ptr).zstream);
    }
    png_free_buffer_list(png_ptr, &mut (*png_ptr).zbuffer_list);
    png_free(png_ptr as png_const_structrp, (*png_ptr).row_buf as png_voidp);
    (*png_ptr).row_buf = 0 as png_bytep;
    png_free(png_ptr as png_const_structrp, (*png_ptr).prev_row as png_voidp);
    png_free(png_ptr as png_const_structrp, (*png_ptr).try_row as png_voidp);
    png_free(png_ptr as png_const_structrp, (*png_ptr).tst_row as png_voidp);
    (*png_ptr).prev_row = 0 as png_bytep;
    (*png_ptr).try_row = 0 as png_bytep;
    (*png_ptr).tst_row = 0 as png_bytep;
    png_free(png_ptr as png_const_structrp, (*png_ptr).chunk_list as png_voidp);
    (*png_ptr).chunk_list = 0 as png_bytep;
}
#[no_mangle]
pub unsafe extern "C" fn png_destroy_write_struct(
    mut png_ptr_ptr: png_structpp,
    mut info_ptr_ptr: png_infopp,
) {
    if !png_ptr_ptr.is_null() {
        let mut png_ptr: png_structrp = *png_ptr_ptr;
        if !png_ptr.is_null() {
            png_destroy_info_struct(png_ptr as png_const_structrp, info_ptr_ptr);
            *png_ptr_ptr = 0 as *mut png_struct;
            png_write_destroy(png_ptr);
            png_destroy_png_struct(png_ptr);
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_set_filter(
    mut png_ptr: png_structrp,
    mut method: libc::c_int,
    mut filters: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    if method == 0 as libc::c_int {
        let mut current_block_9: u64;
        match filters
            & (0x8 as libc::c_int | 0x10 as libc::c_int | 0x20 as libc::c_int
                | 0x40 as libc::c_int | 0x80 as libc::c_int | 0x7 as libc::c_int)
        {
            5 | 6 | 7 => {
                png_app_error(
                    png_ptr as png_const_structrp,
                    b"Unknown row filter for method 0\0" as *const u8
                        as *const libc::c_char,
                );
                current_block_9 = 15074770387117256792;
            }
            0 => {
                current_block_9 = 15074770387117256792;
            }
            1 => {
                (*png_ptr).do_filter = 0x10 as libc::c_int as png_byte;
                current_block_9 = 10599921512955367680;
            }
            2 => {
                (*png_ptr).do_filter = 0x20 as libc::c_int as png_byte;
                current_block_9 = 10599921512955367680;
            }
            3 => {
                (*png_ptr).do_filter = 0x40 as libc::c_int as png_byte;
                current_block_9 = 10599921512955367680;
            }
            4 => {
                (*png_ptr).do_filter = 0x80 as libc::c_int as png_byte;
                current_block_9 = 10599921512955367680;
            }
            _ => {
                (*png_ptr).do_filter = filters as png_byte;
                current_block_9 = 10599921512955367680;
            }
        }
        match current_block_9 {
            15074770387117256792 => {
                (*png_ptr).do_filter = 0x8 as libc::c_int as png_byte;
            }
            _ => {}
        }
        if !((*png_ptr).row_buf).is_null() {
            let mut num_filters: libc::c_int = 0;
            let mut buf_size: png_alloc_size_t = 0;
            if (*png_ptr).height == 1 as libc::c_int as png_uint_32 {
                filters
                    &= !(0x20 as libc::c_int | 0x40 as libc::c_int
                        | 0x80 as libc::c_int);
            }
            if (*png_ptr).width == 1 as libc::c_int as png_uint_32 {
                filters
                    &= !(0x10 as libc::c_int | 0x40 as libc::c_int
                        | 0x80 as libc::c_int);
            }
            if filters
                & (0x20 as libc::c_int | 0x40 as libc::c_int | 0x80 as libc::c_int)
                != 0 as libc::c_int && ((*png_ptr).prev_row).is_null()
            {
                png_app_warning(
                    png_ptr as png_const_structrp,
                    b"png_set_filter: UP/AVG/PAETH cannot be added after start\0"
                        as *const u8 as *const libc::c_char,
                );
                filters
                    &= !(0x20 as libc::c_int | 0x40 as libc::c_int
                        | 0x80 as libc::c_int);
            }
            num_filters = 0 as libc::c_int;
            if filters & 0x10 as libc::c_int != 0 {
                num_filters += 1;
                num_filters;
            }
            if filters & 0x20 as libc::c_int != 0 {
                num_filters += 1;
                num_filters;
            }
            if filters & 0x40 as libc::c_int != 0 {
                num_filters += 1;
                num_filters;
            }
            if filters & 0x80 as libc::c_int != 0 {
                num_filters += 1;
                num_filters;
            }
            buf_size = (if (*png_ptr).usr_channels as libc::c_int
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
                .wrapping_add(1 as libc::c_int as size_t);
            if ((*png_ptr).try_row).is_null() {
                (*png_ptr)
                    .try_row = png_malloc(png_ptr as png_const_structrp, buf_size)
                    as png_bytep;
            }
            if num_filters > 1 as libc::c_int {
                if ((*png_ptr).tst_row).is_null() {
                    (*png_ptr)
                        .tst_row = png_malloc(png_ptr as png_const_structrp, buf_size)
                        as png_bytep;
                }
            }
        }
        (*png_ptr).do_filter = filters as png_byte;
    } else {
        png_error(
            png_ptr as png_const_structrp,
            b"Unknown custom filter method\0" as *const u8 as *const libc::c_char,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_set_compression_level(
    mut png_ptr: png_structrp,
    mut level: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).zlib_level = level;
}
#[no_mangle]
pub unsafe extern "C" fn png_set_compression_mem_level(
    mut png_ptr: png_structrp,
    mut mem_level: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).zlib_mem_level = mem_level;
}
#[no_mangle]
pub unsafe extern "C" fn png_set_compression_strategy(
    mut png_ptr: png_structrp,
    mut strategy: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).flags |= 0x1 as libc::c_uint;
    (*png_ptr).zlib_strategy = strategy;
}
#[no_mangle]
pub unsafe extern "C" fn png_set_compression_window_bits(
    mut png_ptr: png_structrp,
    mut window_bits: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    if window_bits > 15 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Only compression windows <= 32k supported by PNG\0" as *const u8
                as *const libc::c_char,
        );
        window_bits = 15 as libc::c_int;
    } else if window_bits < 8 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Only compression windows >= 256 supported by PNG\0" as *const u8
                as *const libc::c_char,
        );
        window_bits = 8 as libc::c_int;
    }
    (*png_ptr).zlib_window_bits = window_bits;
}
#[no_mangle]
pub unsafe extern "C" fn png_set_compression_method(
    mut png_ptr: png_structrp,
    mut method: libc::c_int,
) {
    if png_ptr.is_null() {
        return;
    }
    if method != 8 as libc::c_int {
        png_warning(
            png_ptr as png_const_structrp,
            b"Only compression method 8 is supported by PNG\0" as *const u8
                as *const libc::c_char,
        );
    }
    (*png_ptr).zlib_method = method;
}
#[no_mangle]
pub unsafe extern "C" fn png_set_write_status_fn(
    mut png_ptr: png_structrp,
    mut write_row_fn: png_write_status_ptr,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).write_row_fn = write_row_fn;
}
#[no_mangle]
pub unsafe extern "C" fn png_write_png(
    mut png_ptr: png_structrp,
    mut info_ptr: png_inforp,
    mut transforms: libc::c_int,
    mut params: voidp,
) {
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    if (*info_ptr).valid & 0x8000 as libc::c_uint == 0 as libc::c_int as libc::c_uint {
        png_app_error(
            png_ptr as png_const_structrp,
            b"no rows for png_write_image to write\0" as *const u8 as *const libc::c_char,
        );
        return;
    }
    png_write_info(png_ptr, info_ptr as png_const_inforp);
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
    if transforms & 0x4 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_PACKING not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x100 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_SWAP_ALPHA not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & (0x1000 as libc::c_int | 0x800 as libc::c_int) != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_STRIP_FILLER not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x80 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_BGR not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x200 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_SWAP_ENDIAN not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    if transforms & 0x8 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_PACKSWAP not supported\0" as *const u8 as *const libc::c_char,
        );
    }
    if transforms & 0x400 as libc::c_int != 0 as libc::c_int {
        png_app_error(
            png_ptr as png_const_structrp,
            b"PNG_TRANSFORM_INVERT_ALPHA not supported\0" as *const u8
                as *const libc::c_char,
        );
    }
    png_write_image(png_ptr, (*info_ptr).row_pointers);
    png_write_end(png_ptr, info_ptr);
}
