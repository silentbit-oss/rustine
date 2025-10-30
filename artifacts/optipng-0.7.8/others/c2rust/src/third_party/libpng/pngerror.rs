use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    pub type internal_state;
    fn abort() -> !;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
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
#[no_mangle]
pub unsafe extern "C" fn png_error(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) -> ! {
    if !png_ptr.is_null() && ((*png_ptr).error_fn).is_some() {
        (Some(((*png_ptr).error_fn).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )(
            png_ptr as *const libc::c_void as *mut libc::c_void as png_structrp,
            error_message,
        );
    }
    png_default_error(png_ptr, error_message);
}
#[no_mangle]
pub unsafe extern "C" fn png_safecat(
    mut buffer: png_charp,
    mut bufsize: size_t,
    mut pos: size_t,
    mut string: png_const_charp,
) -> size_t {
    if !buffer.is_null() && pos < bufsize {
        if !string.is_null() {
            while *string as libc::c_int != '\0' as i32
                && pos < bufsize.wrapping_sub(1 as libc::c_int as size_t)
            {
                let fresh0 = string;
                string = string.offset(1);
                let fresh1 = pos;
                pos = pos.wrapping_add(1);
                *buffer.offset(fresh1 as isize) = *fresh0;
            }
        }
        *buffer.offset(pos as isize) = '\0' as i32 as libc::c_char;
    }
    return pos;
}
#[no_mangle]
pub unsafe extern "C" fn png_format_number(
    mut start: png_const_charp,
    mut end: png_charp,
    mut format: libc::c_int,
    mut number: png_alloc_size_t,
) -> png_charp {
    let mut count: libc::c_int = 0 as libc::c_int;
    let mut mincount: libc::c_int = 1 as libc::c_int;
    let mut output: libc::c_int = 0 as libc::c_int;
    end = end.offset(-1);
    *end = '\0' as i32 as libc::c_char;
    while end > start as png_charp
        && (number != 0 as libc::c_int as png_alloc_size_t || count < mincount)
    {
        static mut digits: [libc::c_char; 17] = unsafe {
            *::core::mem::transmute::<
                &[u8; 17],
                &[libc::c_char; 17],
            >(b"0123456789ABCDEF\0")
        };
        let mut current_block_13: u64;
        match format {
            5 => {
                mincount = 5 as libc::c_int;
                if output != 0 as libc::c_int
                    || number % 10 as libc::c_int as png_alloc_size_t
                        != 0 as libc::c_int as png_alloc_size_t
                {
                    end = end.offset(-1);
                    *end = digits[(number % 10 as libc::c_int as png_alloc_size_t)
                        as usize];
                    output = 1 as libc::c_int;
                }
                number = number / 10 as libc::c_int as png_alloc_size_t;
                current_block_13 = 1054647088692577877;
            }
            2 => {
                mincount = 2 as libc::c_int;
                current_block_13 = 9376024032952078885;
            }
            1 => {
                current_block_13 = 9376024032952078885;
            }
            4 => {
                mincount = 2 as libc::c_int;
                current_block_13 = 14203586781664374324;
            }
            3 => {
                current_block_13 = 14203586781664374324;
            }
            _ => {
                number = 0 as libc::c_int as png_alloc_size_t;
                current_block_13 = 1054647088692577877;
            }
        }
        match current_block_13 {
            14203586781664374324 => {
                end = end.offset(-1);
                *end = digits[(number & 0xf as libc::c_int as png_alloc_size_t)
                    as usize];
                number >>= 4 as libc::c_int;
            }
            9376024032952078885 => {
                end = end.offset(-1);
                *end = digits[(number % 10 as libc::c_int as png_alloc_size_t) as usize];
                number = number / 10 as libc::c_int as png_alloc_size_t;
            }
            _ => {}
        }
        count += 1;
        count;
        if format == 5 as libc::c_int && count == 5 as libc::c_int
            && end > start as png_charp
        {
            if output != 0 as libc::c_int {
                end = end.offset(-1);
                *end = '.' as i32 as libc::c_char;
            } else if number == 0 as libc::c_int as png_alloc_size_t {
                end = end.offset(-1);
                *end = '0' as i32 as libc::c_char;
            }
        }
    }
    return end;
}
#[no_mangle]
pub unsafe extern "C" fn png_warning(
    mut png_ptr: png_const_structrp,
    mut warning_message: png_const_charp,
) {
    let mut offset: libc::c_int = 0 as libc::c_int;
    if !png_ptr.is_null() {
        if *warning_message as libc::c_int == 0x23 as libc::c_int {
            offset = 1 as libc::c_int;
            while offset < 15 as libc::c_int {
                if *warning_message.offset(offset as isize) as libc::c_int == ' ' as i32
                {
                    break;
                }
                offset += 1;
                offset;
            }
        }
    }
    if !png_ptr.is_null() && ((*png_ptr).warning_fn).is_some() {
        (Some(((*png_ptr).warning_fn).expect("non-null function pointer")))
            .expect(
                "non-null function pointer",
            )(
            png_ptr as *const libc::c_void as *mut libc::c_void as png_structrp,
            warning_message.offset(offset as isize),
        );
    } else {
        png_default_warning(png_ptr, warning_message.offset(offset as isize));
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_warning_parameter(
    mut p: *mut [libc::c_char; 32],
    mut number: libc::c_int,
    mut string: png_const_charp,
) {
    if number > 0 as libc::c_int && number <= 8 as libc::c_int {
        png_safecat(
            (*p.offset((number - 1 as libc::c_int) as isize)).as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 32]>() as libc::c_ulong,
            0 as libc::c_int as size_t,
            string,
        );
    }
}
#[no_mangle]
pub unsafe extern "C" fn png_warning_parameter_unsigned(
    mut p: *mut [libc::c_char; 32],
    mut number: libc::c_int,
    mut format: libc::c_int,
    mut value: png_alloc_size_t,
) {
    let mut buffer: [libc::c_char; 24] = [0; 24];
    png_warning_parameter(
        p,
        number,
        png_format_number(
            buffer.as_mut_ptr() as png_const_charp,
            buffer
                .as_mut_ptr()
                .offset(
                    ::core::mem::size_of::<[libc::c_char; 24]>() as libc::c_ulong
                        as isize,
                ),
            format,
            value,
        ) as png_const_charp,
    );
}
#[no_mangle]
pub unsafe extern "C" fn png_warning_parameter_signed(
    mut p: *mut [libc::c_char; 32],
    mut number: libc::c_int,
    mut format: libc::c_int,
    mut value: png_int_32,
) {
    let mut u: png_alloc_size_t = 0;
    let mut str: png_charp = 0 as *mut libc::c_char;
    let mut buffer: [libc::c_char; 24] = [0; 24];
    u = value as png_alloc_size_t;
    if value < 0 as libc::c_int {
        u = (!u).wrapping_add(1 as libc::c_int as png_alloc_size_t);
    }
    str = png_format_number(
        buffer.as_mut_ptr() as png_const_charp,
        buffer
            .as_mut_ptr()
            .offset(
                ::core::mem::size_of::<[libc::c_char; 24]>() as libc::c_ulong as isize,
            ),
        format,
        u,
    );
    if value < 0 as libc::c_int && str > buffer.as_mut_ptr() {
        str = str.offset(-1);
        *str = '-' as i32 as libc::c_char;
    }
    png_warning_parameter(p, number, str as png_const_charp);
}
#[no_mangle]
pub unsafe extern "C" fn png_formatted_warning(
    mut png_ptr: png_const_structrp,
    mut p: *mut [libc::c_char; 32],
    mut message: png_const_charp,
) {
    let mut i: size_t = 0 as libc::c_int as size_t;
    let mut msg: [libc::c_char; 192] = [0; 192];
    while i
        < (::core::mem::size_of::<[libc::c_char; 192]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong)
        && *message as libc::c_int != '\0' as i32
    {
        if !p.is_null() && *message as libc::c_int == '@' as i32
            && *message.offset(1 as libc::c_int as isize) as libc::c_int != '\0' as i32
        {
            message = message.offset(1);
            let mut parameter_char: libc::c_int = *message as libc::c_int;
            static mut valid_parameters: [libc::c_char; 10] = unsafe {
                *::core::mem::transmute::<&[u8; 10], &[libc::c_char; 10]>(b"123456789\0")
            };
            let mut parameter: libc::c_int = 0 as libc::c_int;
            while valid_parameters[parameter as usize] as libc::c_int != parameter_char
                && valid_parameters[parameter as usize] as libc::c_int != '\0' as i32
            {
                parameter += 1;
                parameter;
            }
            if parameter < 8 as libc::c_int {
                let mut parm: png_const_charp = (*p.offset(parameter as isize))
                    .as_mut_ptr() as png_const_charp;
                let mut pend: png_const_charp = (*p.offset(parameter as isize))
                    .as_mut_ptr()
                    .offset(
                        ::core::mem::size_of::<[libc::c_char; 32]>() as libc::c_ulong
                            as isize,
                    ) as png_const_charp;
                while i
                    < (::core::mem::size_of::<[libc::c_char; 192]>() as libc::c_ulong)
                        .wrapping_sub(1 as libc::c_int as libc::c_ulong)
                    && *parm as libc::c_int != '\0' as i32 && parm < pend
                {
                    let fresh2 = parm;
                    parm = parm.offset(1);
                    let fresh3 = i;
                    i = i.wrapping_add(1);
                    msg[fresh3 as usize] = *fresh2;
                }
                message = message.offset(1);
                message;
                continue;
            }
        }
        let fresh4 = message;
        message = message.offset(1);
        let fresh5 = i;
        i = i.wrapping_add(1);
        msg[fresh5 as usize] = *fresh4;
    }
    msg[i as usize] = '\0' as i32 as libc::c_char;
    png_warning(png_ptr, msg.as_mut_ptr() as png_const_charp);
}
#[no_mangle]
pub unsafe extern "C" fn png_benign_error(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) {
    if (*png_ptr).flags & 0x100000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        if (*png_ptr).mode & 0x8000 as libc::c_uint != 0 as libc::c_int as libc::c_uint
            && (*png_ptr).chunk_name != 0 as libc::c_int as png_uint_32
        {
            png_chunk_warning(png_ptr, error_message);
        } else {
            png_warning(png_ptr, error_message);
        }
    } else if (*png_ptr).mode & 0x8000 as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
        && (*png_ptr).chunk_name != 0 as libc::c_int as png_uint_32
    {
        png_chunk_error(png_ptr, error_message);
    } else {
        png_error(png_ptr, error_message);
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_app_warning(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) {
    if (*png_ptr).flags & 0x200000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_warning(png_ptr, error_message);
    } else {
        png_error(png_ptr, error_message);
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_app_error(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) {
    if (*png_ptr).flags & 0x400000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_warning(png_ptr, error_message);
    } else {
        png_error(png_ptr, error_message);
    };
}
static mut png_digit: [libc::c_char; 16] = [
    '0' as i32 as libc::c_char,
    '1' as i32 as libc::c_char,
    '2' as i32 as libc::c_char,
    '3' as i32 as libc::c_char,
    '4' as i32 as libc::c_char,
    '5' as i32 as libc::c_char,
    '6' as i32 as libc::c_char,
    '7' as i32 as libc::c_char,
    '8' as i32 as libc::c_char,
    '9' as i32 as libc::c_char,
    'A' as i32 as libc::c_char,
    'B' as i32 as libc::c_char,
    'C' as i32 as libc::c_char,
    'D' as i32 as libc::c_char,
    'E' as i32 as libc::c_char,
    'F' as i32 as libc::c_char,
];
unsafe extern "C" fn png_format_buffer(
    mut png_ptr: png_const_structrp,
    mut buffer: png_charp,
    mut error_message: png_const_charp,
) {
    let mut chunk_name: png_uint_32 = (*png_ptr).chunk_name;
    let mut iout: libc::c_int = 0 as libc::c_int;
    let mut ishift: libc::c_int = 24 as libc::c_int;
    while ishift >= 0 as libc::c_int {
        let mut c: libc::c_int = (chunk_name >> ishift) as libc::c_int
            & 0xff as libc::c_int;
        ishift -= 8 as libc::c_int;
        if (c < 65 as libc::c_int || c > 122 as libc::c_int
            || c > 90 as libc::c_int && c < 97 as libc::c_int) as libc::c_int
            != 0 as libc::c_int
        {
            let fresh6 = iout;
            iout = iout + 1;
            *buffer.offset(fresh6 as isize) = 0x5b as libc::c_int as libc::c_char;
            let fresh7 = iout;
            iout = iout + 1;
            *buffer
                .offset(
                    fresh7 as isize,
                ) = png_digit[((c & 0xf0 as libc::c_int) >> 4 as libc::c_int) as usize];
            let fresh8 = iout;
            iout = iout + 1;
            *buffer
                .offset(fresh8 as isize) = png_digit[(c & 0xf as libc::c_int) as usize];
            let fresh9 = iout;
            iout = iout + 1;
            *buffer.offset(fresh9 as isize) = 0x5d as libc::c_int as libc::c_char;
        } else {
            let fresh10 = iout;
            iout = iout + 1;
            *buffer.offset(fresh10 as isize) = c as libc::c_char;
        }
    }
    if error_message.is_null() {
        *buffer.offset(iout as isize) = '\0' as i32 as libc::c_char;
    } else {
        let mut iin: libc::c_int = 0 as libc::c_int;
        let fresh11 = iout;
        iout = iout + 1;
        *buffer.offset(fresh11 as isize) = ':' as i32 as libc::c_char;
        let fresh12 = iout;
        iout = iout + 1;
        *buffer.offset(fresh12 as isize) = ' ' as i32 as libc::c_char;
        while iin < 196 as libc::c_int - 1 as libc::c_int
            && *error_message.offset(iin as isize) as libc::c_int != '\0' as i32
        {
            let fresh13 = iin;
            iin = iin + 1;
            let fresh14 = iout;
            iout = iout + 1;
            *buffer.offset(fresh14 as isize) = *error_message.offset(fresh13 as isize);
        }
        *buffer.offset(iout as isize) = '\0' as i32 as libc::c_char;
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_chunk_error(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) -> ! {
    let mut msg: [libc::c_char; 214] = [0; 214];
    if png_ptr.is_null() {
        png_error(png_ptr, error_message);
    } else {
        png_format_buffer(png_ptr, msg.as_mut_ptr(), error_message);
        png_error(png_ptr, msg.as_mut_ptr() as png_const_charp);
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_chunk_warning(
    mut png_ptr: png_const_structrp,
    mut warning_message: png_const_charp,
) {
    let mut msg: [libc::c_char; 214] = [0; 214];
    if png_ptr.is_null() {
        png_warning(png_ptr, warning_message);
    } else {
        png_format_buffer(png_ptr, msg.as_mut_ptr(), warning_message);
        png_warning(png_ptr, msg.as_mut_ptr() as png_const_charp);
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_chunk_benign_error(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) {
    if (*png_ptr).flags & 0x100000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        png_chunk_warning(png_ptr, error_message);
    } else {
        png_chunk_error(png_ptr, error_message);
    };
}
#[no_mangle]
pub unsafe extern "C" fn png_chunk_report(
    mut png_ptr: png_const_structrp,
    mut message: png_const_charp,
    mut error: libc::c_int,
) {
    if (*png_ptr).mode & 0x8000 as libc::c_uint != 0 as libc::c_int as libc::c_uint {
        if error < 2 as libc::c_int {
            png_chunk_warning(png_ptr, message);
        } else {
            png_chunk_benign_error(png_ptr, message);
        }
    } else if (*png_ptr).mode & 0x8000 as libc::c_uint
        == 0 as libc::c_int as libc::c_uint
    {
        if error < 1 as libc::c_int {
            png_app_warning(png_ptr, message);
        } else {
            png_app_error(png_ptr, message);
        }
    }
}
unsafe extern "C" fn png_default_error(
    mut png_ptr: png_const_structrp,
    mut error_message: png_const_charp,
) -> ! {
    fprintf(
        stderr,
        b"libpng error: %s\0" as *const u8 as *const libc::c_char,
        if !error_message.is_null() {
            error_message
        } else {
            b"undefined\0" as *const u8 as *const libc::c_char
        },
    );
    fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
    png_longjmp(png_ptr, 1 as libc::c_int);
}
#[no_mangle]
pub unsafe extern "C" fn png_longjmp(
    mut png_ptr: png_const_structrp,
    mut val: libc::c_int,
) -> ! {
    abort();
}
unsafe extern "C" fn png_default_warning(
    mut png_ptr: png_const_structrp,
    mut warning_message: png_const_charp,
) {
    fprintf(
        stderr,
        b"libpng warning: %s\0" as *const u8 as *const libc::c_char,
        warning_message,
    );
    fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
}
#[no_mangle]
pub unsafe extern "C" fn png_set_error_fn(
    mut png_ptr: png_structrp,
    mut error_ptr: png_voidp,
    mut error_fn: png_error_ptr,
    mut warning_fn: png_error_ptr,
) {
    if png_ptr.is_null() {
        return;
    }
    (*png_ptr).error_ptr = error_ptr;
    (*png_ptr).error_fn = error_fn;
    (*png_ptr).warning_fn = warning_fn;
}
#[no_mangle]
pub unsafe extern "C" fn png_get_error_ptr(
    mut png_ptr: png_const_structrp,
) -> png_voidp {
    if png_ptr.is_null() {
        return 0 as *mut libc::c_void;
    }
    return (*png_ptr).error_ptr;
}
