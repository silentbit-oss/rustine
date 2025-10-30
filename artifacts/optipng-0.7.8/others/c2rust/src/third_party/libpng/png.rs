use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    pub type internal_state;
    fn free(_: *mut libc::c_void);
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memcmp(
        _: *const libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn png_malloc_base(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_safecat(
        buffer: png_charp,
        bufsize: size_t,
        pos: size_t,
        string: png_const_charp,
    ) -> size_t;
    fn png_set_error_fn(
        png_ptr: png_structrp,
        error_ptr: png_voidp,
        error_fn: png_error_ptr,
        warning_fn: png_error_ptr,
    );
    fn png_malloc_warn(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_free(png_ptr: png_const_structrp, ptr: png_voidp);
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_warning(png_ptr: png_const_structrp, warning_message: png_const_charp);
    fn png_save_uint_32(buf: png_bytep, i: png_uint_32);
    fn inflateReset(strm: z_streamp) -> libc::c_int;
    fn crc32(crc: uLong, buf: *const Bytef, len: uInt) -> uLong;
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type _IO_lock_t = ();
pub type FILE = _IO_FILE;
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
pub type png_charp = *mut libc::c_char;
pub type png_const_charp = *const libc::c_char;
pub type png_FILE_p = *mut FILE;
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
pub type png_infop = *mut png_info;
pub type png_infopp = *mut *mut png_info;
pub type png_structrp = *mut png_struct;
pub type png_const_structrp = *const png_struct;
pub type png_inforp = *mut png_info;
pub type png_malloc_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_alloc_size_t) -> png_voidp,
>;
pub type png_free_ptr = Option::<unsafe extern "C" fn(png_structp, png_voidp) -> ()>;
pub type z_streamp = *mut z_stream;
#[no_mangle]
pub unsafe extern "C" fn png_set_sig_bytes(
    mut png_ptr: png_structrp,
    mut num_bytes: libc::c_int,
) {
    let mut nb: libc::c_uint = num_bytes as libc::c_uint;
    if png_ptr.is_null() {
        return;
    }
    if num_bytes < 0 as libc::c_int {
        nb = 0 as libc::c_int as libc::c_uint;
    }
    if nb > 8 as libc::c_int as libc::c_uint {
        png_error(
            png_ptr as png_const_structrp,
            b"Too many bytes for PNG signature\0" as *const u8 as *const libc::c_char,
        );
    }
    (*png_ptr).sig_bytes = nb as png_byte;
}
#[no_mangle]
pub unsafe extern "C" fn png_sig_cmp(
    mut sig: png_const_bytep,
    mut start: size_t,
    mut num_to_check: size_t,
) -> libc::c_int {
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
    if num_to_check > 8 as libc::c_int as size_t {
        num_to_check = 8 as libc::c_int as size_t;
    } else if num_to_check < 1 as libc::c_int as size_t {
        return -(1 as libc::c_int)
    }
    if start > 7 as libc::c_int as size_t {
        return -(1 as libc::c_int);
    }
    if start.wrapping_add(num_to_check) > 8 as libc::c_int as size_t {
        num_to_check = (8 as libc::c_int as size_t).wrapping_sub(start);
    }
    return memcmp(
        &*sig.offset(start as isize) as *const png_byte as *const libc::c_void,
        &mut *png_signature.as_mut_ptr().offset(start as isize) as *mut png_byte
            as *const libc::c_void,
        num_to_check,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_zalloc(
    mut png_ptr: voidpf,
    mut items: uInt,
    mut size: uInt,
) -> voidpf {
    let mut num_bytes: png_alloc_size_t = size as png_alloc_size_t;
    if png_ptr.is_null() {
        return 0 as *mut libc::c_void;
    }
    if items as png_alloc_size_t
        >= !(0 as libc::c_int as png_alloc_size_t) / size as png_alloc_size_t
    {
        png_warning(
            png_ptr as png_const_structrp,
            b"Potential overflow in png_zalloc()\0" as *const u8 as *const libc::c_char,
        );
        return 0 as *mut libc::c_void;
    }
    num_bytes = num_bytes * items as png_alloc_size_t;
    return png_malloc_warn(png_ptr as png_const_structrp, num_bytes);
}
#[no_mangle]
pub unsafe extern "C" fn png_zfree(mut png_ptr: voidpf, mut ptr: voidpf) {
    png_free(png_ptr as png_const_structrp, ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_reset_crc(mut png_ptr: png_structrp) {
    (*png_ptr)
        .crc = crc32(
        0 as libc::c_int as uLong,
        0 as *const Bytef,
        0 as libc::c_int as uInt,
    ) as png_uint_32;
}
#[no_mangle]
pub unsafe extern "C" fn png_calculate_crc(
    mut png_ptr: png_structrp,
    mut ptr: png_const_bytep,
    mut length: size_t,
) {
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
    if need_crc != 0 as libc::c_int && length > 0 as libc::c_int as size_t {
        let mut crc: uLong = (*png_ptr).crc as uLong;
        loop {
            let mut safe_length: uInt = length as uInt;
            if safe_length == 0 as libc::c_int as uInt {
                safe_length = -(1 as libc::c_int) as uInt;
            }
            crc = crc32(crc, ptr, safe_length);
            ptr = ptr.offset(safe_length as isize);
            length = length.wrapping_sub(safe_length as size_t);
            if !(length > 0 as libc::c_int as size_t) {
                break;
            }
        }
        (*png_ptr).crc = crc as png_uint_32;
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_user_version_check(
    mut png_ptr: png_structrp,
    mut user_png_ver: png_const_charp,
) -> libc::c_int {
    if !user_png_ver.is_null() {
        let mut i: libc::c_int = -(1 as libc::c_int);
        let mut found_dots: libc::c_int = 0 as libc::c_int;
        loop {
            i += 1;
            i;
            if *user_png_ver.offset(i as isize) as libc::c_int
                != (*::core::mem::transmute::<
                    &[u8; 7],
                    &[libc::c_char; 7],
                >(b"1.6.40\0"))[i as usize] as libc::c_int
            {
                (*png_ptr).flags |= 0x20000 as libc::c_uint;
            }
            if *user_png_ver.offset(i as isize) as libc::c_int == '.' as i32 {
                found_dots += 1;
                found_dots;
            }
            if !(found_dots < 2 as libc::c_int
                && *user_png_ver.offset(i as isize) as libc::c_int != 0 as libc::c_int
                && (*::core::mem::transmute::<
                    &[u8; 7],
                    &[libc::c_char; 7],
                >(b"1.6.40\0"))[i as usize] as libc::c_int != 0 as libc::c_int)
            {
                break;
            }
        }
    } else {
        (*png_ptr).flags |= 0x20000 as libc::c_uint;
    }
    if (*png_ptr).flags & 0x20000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        let mut pos: size_t = 0 as libc::c_int as size_t;
        let mut m: [libc::c_char; 128] = [0; 128];
        pos = png_safecat(
            m.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 128]>() as libc::c_ulong,
            pos,
            b"Application built with libpng-\0" as *const u8 as *const libc::c_char,
        );
        pos = png_safecat(
            m.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 128]>() as libc::c_ulong,
            pos,
            user_png_ver,
        );
        pos = png_safecat(
            m.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 128]>() as libc::c_ulong,
            pos,
            b" but running with \0" as *const u8 as *const libc::c_char,
        );
        pos = png_safecat(
            m.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 128]>() as libc::c_ulong,
            pos,
            b"1.6.40\0" as *const u8 as *const libc::c_char,
        );
        png_warning(png_ptr as png_const_structrp, m.as_mut_ptr() as png_const_charp);
        return 0 as libc::c_int;
    }
    return 1 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn png_create_png_struct(
    mut user_png_ver: png_const_charp,
    mut error_ptr: png_voidp,
    mut error_fn: png_error_ptr,
    mut warn_fn: png_error_ptr,
    mut mem_ptr: png_voidp,
    mut malloc_fn: png_malloc_ptr,
    mut free_fn: png_free_ptr,
) -> png_structp {
    let mut create_struct: png_struct = png_struct_def {
        error_fn: None,
        warning_fn: None,
        error_ptr: 0 as *mut libc::c_void,
        write_data_fn: None,
        read_data_fn: None,
        io_ptr: 0 as *mut libc::c_void,
        mode: 0,
        flags: 0,
        transformations: 0,
        zowner: 0,
        zstream: z_stream_s {
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
        },
        zbuffer_list: 0 as *mut png_compression_buffer,
        zbuffer_size: 0,
        zlib_level: 0,
        zlib_method: 0,
        zlib_window_bits: 0,
        zlib_mem_level: 0,
        zlib_strategy: 0,
        zlib_set_level: 0,
        zlib_set_method: 0,
        zlib_set_window_bits: 0,
        zlib_set_mem_level: 0,
        zlib_set_strategy: 0,
        width: 0,
        height: 0,
        num_rows: 0,
        usr_width: 0,
        rowbytes: 0,
        iwidth: 0,
        row_number: 0,
        chunk_name: 0,
        prev_row: 0 as *mut png_byte,
        row_buf: 0 as *mut png_byte,
        try_row: 0 as *mut png_byte,
        tst_row: 0 as *mut png_byte,
        info_rowbytes: 0,
        idat_size: 0,
        crc: 0,
        palette: 0 as *mut png_color,
        num_palette: 0,
        num_palette_max: 0,
        num_trans: 0,
        compression: 0,
        filter: 0,
        interlaced: 0,
        pass: 0,
        do_filter: 0,
        color_type: 0,
        bit_depth: 0,
        usr_bit_depth: 0,
        pixel_depth: 0,
        channels: 0,
        usr_channels: 0,
        sig_bytes: 0,
        maximum_pixel_depth: 0,
        transformed_pixel_depth: 0,
        zstream_start: 0,
        background_gamma_type: 0,
        background_gamma: 0,
        background: png_color_16_struct {
            index: 0,
            red: 0,
            green: 0,
            blue: 0,
            gray: 0,
        },
        output_flush_fn: None,
        flush_dist: 0,
        flush_rows: 0,
        sig_bit: png_color_8_struct {
            red: 0,
            green: 0,
            blue: 0,
            gray: 0,
            alpha: 0,
        },
        trans_alpha: 0 as *mut png_byte,
        trans_color: png_color_16_struct {
            index: 0,
            red: 0,
            green: 0,
            blue: 0,
            gray: 0,
        },
        read_row_fn: None,
        write_row_fn: None,
        free_me: 0,
        unknown_default: 0,
        num_chunk_list: 0,
        chunk_list: 0 as *mut png_byte,
        big_row_buf: 0 as *mut png_byte,
        compression_type: 0,
        user_width_max: 0,
        user_height_max: 0,
        user_chunk_cache_max: 0,
        user_chunk_malloc_max: 0,
        unknown_chunk: png_unknown_chunk_t {
            name: [0; 5],
            data: 0 as *mut png_byte,
            size: 0,
            location: 0,
        },
        old_big_row_buf_size: 0,
        read_buffer: 0 as *mut png_byte,
        read_buffer_size: 0,
        IDAT_read_size: 0,
        io_state: 0,
        big_prev_row: 0 as *mut png_byte,
        read_filter: [None; 4],
    };
    memset(
        &mut create_struct as *mut png_struct as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<png_struct>() as libc::c_ulong,
    );
    create_struct.user_width_max = 1000000 as libc::c_int as png_uint_32;
    create_struct.user_height_max = 1000000 as libc::c_int as png_uint_32;
    create_struct.user_chunk_cache_max = 1000 as libc::c_int as png_uint_32;
    create_struct.user_chunk_malloc_max = 8000000 as libc::c_int as png_alloc_size_t;
    png_set_error_fn(&mut create_struct, error_ptr, error_fn, warn_fn);
    if png_user_version_check(&mut create_struct, user_png_ver) != 0 as libc::c_int {
        let mut png_ptr: png_structrp = png_malloc_warn(
            &mut create_struct as *mut png_struct as png_const_structrp,
            ::core::mem::size_of::<png_struct>() as libc::c_ulong,
        ) as png_structrp;
        if !png_ptr.is_null() {
            create_struct
                .zstream
                .zalloc = Some(
                png_zalloc as unsafe extern "C" fn(voidpf, uInt, uInt) -> voidpf,
            );
            create_struct
                .zstream
                .zfree = Some(png_zfree as unsafe extern "C" fn(voidpf, voidpf) -> ());
            create_struct.zstream.opaque = png_ptr as voidpf;
            *png_ptr = create_struct;
            return png_ptr;
        }
    }
    return 0 as png_structp;
}
#[no_mangle]
pub unsafe extern "C" fn png_create_info_struct(
    mut png_ptr: png_const_structrp,
) -> png_infop {
    let mut info_ptr: png_inforp = 0 as *mut png_info;
    if png_ptr.is_null() {
        return 0 as png_infop;
    }
    info_ptr = png_malloc_base(
        png_ptr,
        ::core::mem::size_of::<png_info>() as libc::c_ulong,
    ) as png_inforp;
    if !info_ptr.is_null() {
        memset(
            info_ptr as *mut libc::c_void,
            0 as libc::c_int,
            ::core::mem::size_of::<png_info>() as libc::c_ulong,
        );
    }
    return info_ptr;
}
#[no_mangle]
pub unsafe extern "C" fn png_destroy_info_struct(
    mut png_ptr: png_const_structrp,
    mut info_ptr_ptr: png_infopp,
) {
    let mut info_ptr: png_inforp = 0 as png_inforp;
    if png_ptr.is_null() {
        return;
    }
    if !info_ptr_ptr.is_null() {
        info_ptr = *info_ptr_ptr;
    }
    if !info_ptr.is_null() {
        *info_ptr_ptr = 0 as *mut png_info;
        png_free_data(png_ptr, info_ptr, 0xffff as libc::c_uint, -(1 as libc::c_int));
        memset(
            info_ptr as *mut libc::c_void,
            0 as libc::c_int,
            ::core::mem::size_of::<png_info>() as libc::c_ulong,
        );
        png_free(png_ptr, info_ptr as png_voidp);
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_info_init_3(
    mut ptr_ptr: png_infopp,
    mut png_info_struct_size: size_t,
) {
    let mut info_ptr: png_inforp = *ptr_ptr;
    if info_ptr.is_null() {
        return;
    }
    if ::core::mem::size_of::<png_info>() as libc::c_ulong > png_info_struct_size {
        *ptr_ptr = 0 as *mut png_info;
        free(info_ptr as *mut libc::c_void);
        info_ptr = png_malloc_base(
            0 as png_const_structrp,
            ::core::mem::size_of::<png_info>() as libc::c_ulong,
        ) as png_inforp;
        if info_ptr.is_null() {
            return;
        }
        *ptr_ptr = info_ptr;
    }
    memset(
        info_ptr as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<png_info>() as libc::c_ulong,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_data_freer(
    mut png_ptr: png_const_structrp,
    mut info_ptr: png_inforp,
    mut freer: libc::c_int,
    mut mask: png_uint_32,
) {
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    if freer == 1 as libc::c_int {
        (*info_ptr).free_me |= mask;
    } else if freer == 2 as libc::c_int {
        (*info_ptr).free_me &= !mask;
    } else {
        png_error(
            png_ptr,
            b"Unknown freer parameter in png_data_freer\0" as *const u8
                as *const libc::c_char,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_free_data(
    mut png_ptr: png_const_structrp,
    mut info_ptr: png_inforp,
    mut mask: png_uint_32,
    mut num: libc::c_int,
) {
    if png_ptr.is_null() || info_ptr.is_null() {
        return;
    }
    if mask & 0x2000 as libc::c_uint & (*info_ptr).free_me
        != 0 as libc::c_int as libc::c_uint
    {
        (*info_ptr).valid &= !(0x10 as libc::c_uint);
        png_free(png_ptr, (*info_ptr).trans_alpha as png_voidp);
        (*info_ptr).trans_alpha = 0 as png_bytep;
        (*info_ptr).num_trans = 0 as libc::c_int as png_uint_16;
    }
    if !((*info_ptr).unknown_chunks).is_null()
        && mask & 0x200 as libc::c_uint & (*info_ptr).free_me
            != 0 as libc::c_int as libc::c_uint
    {
        if num != -(1 as libc::c_int) {
            png_free(
                png_ptr,
                (*((*info_ptr).unknown_chunks).offset(num as isize)).data as png_voidp,
            );
            let ref mut fresh0 = (*((*info_ptr).unknown_chunks).offset(num as isize))
                .data;
            *fresh0 = 0 as *mut png_byte;
        } else {
            let mut i: libc::c_int = 0;
            i = 0 as libc::c_int;
            while i < (*info_ptr).unknown_chunks_num {
                png_free(
                    png_ptr,
                    (*((*info_ptr).unknown_chunks).offset(i as isize)).data as png_voidp,
                );
                i += 1;
                i;
            }
            png_free(png_ptr, (*info_ptr).unknown_chunks as png_voidp);
            (*info_ptr).unknown_chunks = 0 as png_unknown_chunkp;
            (*info_ptr).unknown_chunks_num = 0 as libc::c_int;
        }
    }
    if mask & 0x8 as libc::c_uint & (*info_ptr).free_me
        != 0 as libc::c_int as libc::c_uint
    {
        png_free(png_ptr, (*info_ptr).hist as png_voidp);
        (*info_ptr).hist = 0 as png_uint_16p;
        (*info_ptr).valid &= !(0x40 as libc::c_uint);
    }
    if mask & 0x1000 as libc::c_uint & (*info_ptr).free_me
        != 0 as libc::c_int as libc::c_uint
    {
        png_free(png_ptr, (*info_ptr).palette as png_voidp);
        (*info_ptr).palette = 0 as png_colorp;
        (*info_ptr).valid &= !(0x8 as libc::c_uint);
        (*info_ptr).num_palette = 0 as libc::c_int as png_uint_16;
    }
    if mask & 0x40 as libc::c_uint & (*info_ptr).free_me
        != 0 as libc::c_int as libc::c_uint
    {
        if !((*info_ptr).row_pointers).is_null() {
            let mut row: png_uint_32 = 0;
            row = 0 as libc::c_int as png_uint_32;
            while row < (*info_ptr).height {
                png_free(
                    png_ptr,
                    *((*info_ptr).row_pointers).offset(row as isize) as png_voidp,
                );
                row = row.wrapping_add(1);
                row;
            }
            png_free(png_ptr, (*info_ptr).row_pointers as png_voidp);
            (*info_ptr).row_pointers = 0 as png_bytepp;
        }
        (*info_ptr).valid &= !(0x8000 as libc::c_uint);
    }
    if num != -(1 as libc::c_int) {
        mask &= !(0x4220 as libc::c_uint);
    }
    (*info_ptr).free_me &= !mask;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_io_ptr(mut png_ptr: png_const_structrp) -> png_voidp {
    if png_ptr.is_null() {
        return 0 as *mut libc::c_void;
    }
    return (*png_ptr).io_ptr;
}
#[no_mangle]
pub unsafe extern "C" fn png_init_io(mut png_ptr: png_structrp, mut fp: png_FILE_p) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).io_ptr = fp as png_voidp;
}
#[no_mangle]
pub unsafe extern "C" fn png_save_int_32(mut buf: png_bytep, mut i: png_int_32) {
    png_save_uint_32(buf, i as png_uint_32);
}
#[no_mangle]
pub unsafe extern "C" fn png_get_copyright(
    mut png_ptr: png_const_structrp,
) -> png_const_charp {
    return b"\nlibpng version 1.6.40\nCopyright (c) 2018-2023 Cosmin Truta\nCopyright (c) 1998-2002,2004,2006-2018 Glenn Randers-Pehrson\nCopyright (c) 1996-1997 Andreas Dilger\nCopyright (c) 1995-1996 Guy Eric Schalnat, Group 42, Inc.\n\0"
        as *const u8 as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_libpng_ver(
    mut png_ptr: png_const_structrp,
) -> png_const_charp {
    return png_get_header_ver(png_ptr);
}
#[no_mangle]
pub unsafe extern "C" fn png_get_header_ver(
    mut png_ptr: png_const_structrp,
) -> png_const_charp {
    return b"1.6.40\0" as *const u8 as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_header_version(
    mut png_ptr: png_const_structrp,
) -> png_const_charp {
    return b" libpng version 1.6.40 - June 21, 2023\n\n\0" as *const u8
        as *const libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn png_handle_as_unknown(
    mut png_ptr: png_const_structrp,
    mut chunk_name: png_const_bytep,
) -> libc::c_int {
    let mut p: png_const_bytep = 0 as *const png_byte;
    let mut p_end: png_const_bytep = 0 as *const png_byte;
    if png_ptr.is_null() || chunk_name.is_null()
        || (*png_ptr).num_chunk_list == 0 as libc::c_int as libc::c_uint
    {
        return 0 as libc::c_int;
    }
    p_end = (*png_ptr).chunk_list as png_const_bytep;
    p = p_end
        .offset(
            ((*png_ptr).num_chunk_list).wrapping_mul(5 as libc::c_int as libc::c_uint)
                as isize,
        );
    loop {
        p = p.offset(-(5 as libc::c_int as isize));
        if memcmp(
            chunk_name as *const libc::c_void,
            p as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        {
            return *p.offset(4 as libc::c_int as isize) as libc::c_int;
        }
        if !(p > p_end) {
            break;
        }
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn png_chunk_unknown_handling(
    mut png_ptr: png_const_structrp,
    mut chunk_name: png_uint_32,
) -> libc::c_int {
    let mut chunk_string: [png_byte; 5] = [0; 5];
    *(chunk_string.as_mut_ptr() as *mut libc::c_char)
        .offset(
            0 as libc::c_int as isize,
        ) = (chunk_name >> 24 as libc::c_int & 0xff as libc::c_int as png_uint_32)
        as libc::c_char;
    *(chunk_string.as_mut_ptr() as *mut libc::c_char)
        .offset(
            1 as libc::c_int as isize,
        ) = (chunk_name >> 16 as libc::c_int & 0xff as libc::c_int as png_uint_32)
        as libc::c_char;
    *(chunk_string.as_mut_ptr() as *mut libc::c_char)
        .offset(
            2 as libc::c_int as isize,
        ) = (chunk_name >> 8 as libc::c_int & 0xff as libc::c_int as png_uint_32)
        as libc::c_char;
    *(chunk_string.as_mut_ptr() as *mut libc::c_char)
        .offset(
            3 as libc::c_int as isize,
        ) = (chunk_name & 0xff as libc::c_int as png_uint_32) as libc::c_char;
    *(chunk_string.as_mut_ptr() as *mut libc::c_char)
        .offset(4 as libc::c_int as isize) = 0 as libc::c_int as libc::c_char;
    return png_handle_as_unknown(png_ptr, chunk_string.as_mut_ptr() as png_const_bytep);
}
#[no_mangle]
pub unsafe extern "C" fn png_reset_zstream(mut png_ptr: png_structrp) -> libc::c_int {
    if png_ptr.is_null() {
        return -(2 as libc::c_int);
    }
    return inflateReset(&mut (*png_ptr).zstream);
}
#[no_mangle]
pub unsafe extern "C" fn png_access_version_number() -> png_uint_32 {
    return 10640 as libc::c_int as png_uint_32;
}
#[no_mangle]
pub unsafe extern "C" fn png_zstream_error(
    mut png_ptr: png_structrp,
    mut ret: libc::c_int,
) {
    if ((*png_ptr).zstream.msg).is_null() {
        match ret {
            1 => {
                (*png_ptr)
                    .zstream
                    .msg = b"unexpected end of LZ stream\0" as *const u8
                    as *const libc::c_char;
            }
            2 => {
                (*png_ptr)
                    .zstream
                    .msg = b"missing LZ dictionary\0" as *const u8
                    as *const libc::c_char;
            }
            -1 => {
                (*png_ptr)
                    .zstream
                    .msg = b"zlib IO error\0" as *const u8 as *const libc::c_char;
            }
            -2 => {
                (*png_ptr)
                    .zstream
                    .msg = b"bad parameters to zlib\0" as *const u8
                    as *const libc::c_char;
            }
            -3 => {
                (*png_ptr)
                    .zstream
                    .msg = b"damaged LZ stream\0" as *const u8 as *const libc::c_char;
            }
            -4 => {
                (*png_ptr)
                    .zstream
                    .msg = b"insufficient memory\0" as *const u8 as *const libc::c_char;
            }
            -5 => {
                (*png_ptr)
                    .zstream
                    .msg = b"truncated\0" as *const u8 as *const libc::c_char;
            }
            -6 => {
                (*png_ptr)
                    .zstream
                    .msg = b"unsupported zlib version\0" as *const u8
                    as *const libc::c_char;
            }
            -7 => {
                (*png_ptr)
                    .zstream
                    .msg = b"unexpected zlib return\0" as *const u8
                    as *const libc::c_char;
            }
            0 | _ => {
                (*png_ptr)
                    .zstream
                    .msg = b"unexpected zlib return code\0" as *const u8
                    as *const libc::c_char;
            }
        }
    }
}
unsafe extern "C" fn png_gt(mut a: size_t, mut b: size_t) -> libc::c_int {
    return (a > b) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn png_check_IHDR(
    mut png_ptr: png_const_structrp,
    mut width: png_uint_32,
    mut height: png_uint_32,
    mut bit_depth: libc::c_int,
    mut color_type: libc::c_int,
    mut interlace_type: libc::c_int,
    mut compression_type: libc::c_int,
    mut filter_type: libc::c_int,
) {
    let mut error: libc::c_int = 0 as libc::c_int;
    if width == 0 as libc::c_int as png_uint_32 {
        png_warning(
            png_ptr,
            b"Image width is zero in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if width > 0x7fffffff as libc::c_long as png_uint_32 {
        png_warning(
            png_ptr,
            b"Invalid image width in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if png_gt(
        (width.wrapping_add(7 as libc::c_int as png_uint_32) & !(7 as libc::c_uint))
            as size_t,
        ((-(1 as libc::c_int) as size_t)
            .wrapping_sub(48 as libc::c_int as size_t)
            .wrapping_sub(1 as libc::c_int as size_t) / 8 as libc::c_int as size_t)
            .wrapping_sub(1 as libc::c_int as size_t),
    ) != 0
    {
        png_warning(
            png_ptr,
            b"Image width is too large for this architecture\0" as *const u8
                as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if width > (*png_ptr).user_width_max {
        png_warning(
            png_ptr,
            b"Image width exceeds user limit in IHDR\0" as *const u8
                as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if height == 0 as libc::c_int as png_uint_32 {
        png_warning(
            png_ptr,
            b"Image height is zero in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if height > 0x7fffffff as libc::c_long as png_uint_32 {
        png_warning(
            png_ptr,
            b"Invalid image height in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if height > (*png_ptr).user_height_max {
        png_warning(
            png_ptr,
            b"Image height exceeds user limit in IHDR\0" as *const u8
                as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if bit_depth != 1 as libc::c_int && bit_depth != 2 as libc::c_int
        && bit_depth != 4 as libc::c_int && bit_depth != 8 as libc::c_int
        && bit_depth != 16 as libc::c_int
    {
        png_warning(
            png_ptr,
            b"Invalid bit depth in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if color_type < 0 as libc::c_int || color_type == 1 as libc::c_int
        || color_type == 5 as libc::c_int || color_type > 6 as libc::c_int
    {
        png_warning(
            png_ptr,
            b"Invalid color type in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if color_type == 2 as libc::c_int | 1 as libc::c_int && bit_depth > 8 as libc::c_int
        || (color_type == 2 as libc::c_int || color_type == 4 as libc::c_int
            || color_type == 2 as libc::c_int | 4 as libc::c_int)
            && bit_depth < 8 as libc::c_int
    {
        png_warning(
            png_ptr,
            b"Invalid color type/bit depth combination in IHDR\0" as *const u8
                as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if interlace_type >= 2 as libc::c_int {
        png_warning(
            png_ptr,
            b"Unknown interlace method in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if compression_type != 0 as libc::c_int {
        png_warning(
            png_ptr,
            b"Unknown compression method in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if filter_type != 0 as libc::c_int {
        png_warning(
            png_ptr,
            b"Unknown filter method in IHDR\0" as *const u8 as *const libc::c_char,
        );
        error = 1 as libc::c_int;
    }
    if error == 1 as libc::c_int {
        png_error(png_ptr, b"Invalid IHDR data\0" as *const u8 as *const libc::c_char);
    }
}
