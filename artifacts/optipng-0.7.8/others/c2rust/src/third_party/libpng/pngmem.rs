use ::libc;
extern "C" {
    pub type internal_state;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
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
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_warning(png_ptr: png_const_structrp, warning_message: png_const_charp);
}
pub type size_t = libc::c_ulong;
pub type png_byte = libc::c_uchar;
pub type png_uint_16 = libc::c_ushort;
pub type png_int_32 = libc::c_int;
pub type png_uint_32 = libc::c_uint;
pub type png_alloc_size_t = size_t;
pub type png_fixed_point = png_int_32;
pub type png_voidp = *mut libc::c_void;
pub type png_const_voidp = *const libc::c_void;
pub type png_bytep = *mut png_byte;
pub type png_const_bytep = *const png_byte;
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
#[no_mangle]
pub unsafe extern "C" fn png_destroy_png_struct(mut png_ptr: png_structrp) {
    if !png_ptr.is_null() {
        let mut dummy_struct: png_struct = *png_ptr;
        memset(
            png_ptr as *mut libc::c_void,
            0 as libc::c_int,
            ::core::mem::size_of::<png_struct>() as libc::c_ulong,
        );
        png_free(
            &mut dummy_struct as *mut png_struct as png_const_structrp,
            png_ptr as png_voidp,
        );
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_calloc(
    mut png_ptr: png_const_structrp,
    mut size: png_alloc_size_t,
) -> png_voidp {
    let mut ret: png_voidp = 0 as *mut libc::c_void;
    ret = png_malloc(png_ptr, size);
    if !ret.is_null() {
        memset(ret, 0 as libc::c_int, size);
    }
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn png_malloc_base(
    mut png_ptr: png_const_structrp,
    mut size: png_alloc_size_t,
) -> png_voidp {
    if size > 0 as libc::c_int as png_alloc_size_t
        && size <= -(1 as libc::c_int) as size_t
    {
        return malloc(size)
    } else {
        return 0 as *mut libc::c_void
    };
}
unsafe extern "C" fn png_malloc_array_checked(
    mut png_ptr: png_const_structrp,
    mut nelements: libc::c_int,
    mut element_size: size_t,
) -> png_voidp {
    let mut req: png_alloc_size_t = nelements as png_alloc_size_t;
    if req <= -(1 as libc::c_int) as size_t / element_size {
        return png_malloc_base(png_ptr, req * element_size);
    }
    return 0 as *mut libc::c_void;
}
#[no_mangle]
pub unsafe extern "C" fn png_malloc_array(
    mut png_ptr: png_const_structrp,
    mut nelements: libc::c_int,
    mut element_size: size_t,
) -> png_voidp {
    if nelements <= 0 as libc::c_int || element_size == 0 as libc::c_int as size_t {
        png_error(
            png_ptr,
            b"internal error: array alloc\0" as *const u8 as *const libc::c_char,
        );
    }
    return png_malloc_array_checked(png_ptr, nelements, element_size);
}
#[no_mangle]
pub unsafe extern "C" fn png_realloc_array(
    mut png_ptr: png_const_structrp,
    mut old_array: png_const_voidp,
    mut old_elements: libc::c_int,
    mut add_elements: libc::c_int,
    mut element_size: size_t,
) -> png_voidp {
    if add_elements <= 0 as libc::c_int || element_size == 0 as libc::c_int as size_t
        || old_elements < 0 as libc::c_int
        || old_array.is_null() && old_elements > 0 as libc::c_int
    {
        png_error(
            png_ptr,
            b"internal error: array realloc\0" as *const u8 as *const libc::c_char,
        );
    }
    if add_elements <= 2147483647 as libc::c_int - old_elements {
        let mut new_array: png_voidp = png_malloc_array_checked(
            png_ptr,
            old_elements + add_elements,
            element_size,
        );
        if !new_array.is_null() {
            if old_elements > 0 as libc::c_int {
                memcpy(
                    new_array,
                    old_array,
                    element_size * old_elements as libc::c_uint as size_t,
                );
            }
            memset(
                (new_array as *mut libc::c_char)
                    .offset(
                        (element_size * old_elements as libc::c_uint as size_t) as isize,
                    ) as *mut libc::c_void,
                0 as libc::c_int,
                element_size * add_elements as libc::c_uint as size_t,
            );
            return new_array;
        }
    }
    return 0 as *mut libc::c_void;
}
#[no_mangle]
pub unsafe extern "C" fn png_malloc(
    mut png_ptr: png_const_structrp,
    mut size: png_alloc_size_t,
) -> png_voidp {
    let mut ret: png_voidp = 0 as *mut libc::c_void;
    if png_ptr.is_null() {
        return 0 as *mut libc::c_void;
    }
    ret = png_malloc_base(png_ptr, size);
    if ret.is_null() {
        png_error(png_ptr, b"Out of memory\0" as *const u8 as *const libc::c_char);
    }
    return ret;
}
#[no_mangle]
pub unsafe extern "C" fn png_malloc_warn(
    mut png_ptr: png_const_structrp,
    mut size: png_alloc_size_t,
) -> png_voidp {
    if !png_ptr.is_null() {
        let mut ret: png_voidp = png_malloc_base(png_ptr, size);
        if !ret.is_null() {
            return ret;
        }
        png_warning(png_ptr, b"Out of memory\0" as *const u8 as *const libc::c_char);
    }
    return 0 as *mut libc::c_void;
}
#[no_mangle]
pub unsafe extern "C" fn png_free(mut png_ptr: png_const_structrp, mut ptr: png_voidp) {
    if png_ptr.is_null() || ptr.is_null() {
        return;
    }
    free(ptr);
}
