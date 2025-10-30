use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    pub type png_info_def;
    pub type png_struct_def;
    fn opng_bitset_count(set: opng_bitset_t) -> libc::c_uint;
    fn opng_bitset_find_first(set: opng_bitset_t) -> libc::c_int;
    fn opng_strparse_rangeset_to_bitset(
        out_set: *mut opng_bitset_t,
        rangeset_str: *const libc::c_char,
        mask_set: opng_bitset_t,
    ) -> libc::c_int;
    fn fclose(__stream: *mut FILE) -> libc::c_int;
    fn fopen(_: *const libc::c_char, _: *const libc::c_char) -> *mut FILE;
    fn fread(
        _: *mut libc::c_void,
        _: libc::c_ulong,
        _: libc::c_ulong,
        _: *mut FILE,
    ) -> libc::c_ulong;
    fn fwrite(
        _: *const libc::c_void,
        _: libc::c_ulong,
        _: libc::c_ulong,
        _: *mut FILE,
    ) -> libc::c_ulong;
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
    fn memcmp(
        _: *const libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn strcpy(_: *mut libc::c_char, _: *const libc::c_char) -> *mut libc::c_char;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn png_create_read_struct(
        user_png_ver: png_const_charp,
        error_ptr: png_voidp,
        error_fn: png_error_ptr,
        warn_fn: png_error_ptr,
    ) -> png_structp;
    fn png_create_write_struct(
        user_png_ver: png_const_charp,
        error_ptr: png_voidp,
        error_fn: png_error_ptr,
        warn_fn: png_error_ptr,
    ) -> png_structp;
    fn png_write_sig(png_ptr: png_structrp);
    fn png_write_chunk(
        png_ptr: png_structrp,
        chunk_name: png_const_bytep,
        data: png_const_bytep,
        length: size_t,
    );
    fn png_create_info_struct(png_ptr: png_const_structrp) -> png_infop;
    fn png_destroy_read_struct(
        png_ptr_ptr: png_structpp,
        info_ptr_ptr: png_infopp,
        end_info_ptr_ptr: png_infopp,
    );
    fn png_destroy_write_struct(png_ptr_ptr: png_structpp, info_ptr_ptr: png_infopp);
    fn png_set_filter(png_ptr: png_structrp, method: libc::c_int, filters: libc::c_int);
    fn png_set_compression_level(png_ptr: png_structrp, level: libc::c_int);
    fn png_set_compression_mem_level(png_ptr: png_structrp, mem_level: libc::c_int);
    fn png_set_compression_strategy(png_ptr: png_structrp, strategy: libc::c_int);
    fn png_set_compression_window_bits(png_ptr: png_structrp, window_bits: libc::c_int);
    fn png_set_write_fn(
        png_ptr: png_structrp,
        io_ptr: png_voidp,
        write_data_fn: png_rw_ptr,
        output_flush_fn: png_flush_ptr,
    );
    fn png_set_read_fn(
        png_ptr: png_structrp,
        io_ptr: png_voidp,
        read_data_fn: png_rw_ptr,
    );
    fn png_get_io_ptr(png_ptr: png_const_structrp) -> png_voidp;
    fn png_malloc(png_ptr: png_const_structrp, size: png_alloc_size_t) -> png_voidp;
    fn png_free(png_ptr: png_const_structrp, ptr: png_voidp);
    fn png_data_freer(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        freer: libc::c_int,
        mask: png_uint_32,
    );
    fn png_error(png_ptr: png_const_structrp, error_message: png_const_charp) -> !;
    fn png_get_rows(
        png_ptr: png_const_structrp,
        info_ptr: png_const_inforp,
    ) -> png_bytepp;
    fn png_set_rows(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        row_pointers: png_bytepp,
    );
    fn png_get_image_height(
        png_ptr: png_const_structrp,
        info_ptr: png_const_inforp,
    ) -> png_uint_32;
    fn png_get_bKGD(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        background: *mut png_color_16p,
    ) -> png_uint_32;
    fn png_set_bKGD(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        background: png_const_color_16p,
    );
    fn png_get_hIST(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        hist: *mut png_uint_16p,
    ) -> png_uint_32;
    fn png_set_hIST(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        hist: png_const_uint_16p,
    );
    fn png_get_IHDR(
        png_ptr: png_const_structrp,
        info_ptr: png_const_inforp,
        width: *mut png_uint_32,
        height: *mut png_uint_32,
        bit_depth: *mut libc::c_int,
        color_type: *mut libc::c_int,
        interlace_method: *mut libc::c_int,
        compression_method: *mut libc::c_int,
        filter_method: *mut libc::c_int,
    ) -> png_uint_32;
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
    fn png_get_PLTE(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        palette: *mut png_colorp,
        num_palette: *mut libc::c_int,
    ) -> png_uint_32;
    fn png_set_PLTE(
        png_ptr: png_structrp,
        info_ptr: png_inforp,
        palette: png_const_colorp,
        num_palette: libc::c_int,
    );
    fn png_get_sBIT(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        sig_bit: *mut png_color_8p,
    ) -> png_uint_32;
    fn png_set_sBIT(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        sig_bit: png_const_color_8p,
    );
    fn png_get_tRNS(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        trans_alpha: *mut png_bytep,
        num_trans: *mut libc::c_int,
        trans_color: *mut png_color_16p,
    ) -> png_uint_32;
    fn png_set_tRNS(
        png_ptr: png_structrp,
        info_ptr: png_inforp,
        trans_alpha: png_const_bytep,
        num_trans: libc::c_int,
        trans_color: png_const_color_16p,
    );
    fn png_set_keep_unknown_chunks(
        png_ptr: png_structrp,
        keep: libc::c_int,
        chunk_list: png_const_bytep,
        num_chunks: libc::c_int,
    );
    fn png_handle_as_unknown(
        png_ptr: png_const_structrp,
        chunk_name: png_const_bytep,
    ) -> libc::c_int;
    fn png_set_unknown_chunks(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        unknowns: png_const_unknown_chunkp,
        num_unknowns: libc::c_int,
    );
    fn png_set_unknown_chunk_location(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        chunk: libc::c_int,
        location: libc::c_int,
    );
    fn png_get_unknown_chunks(
        png_ptr: png_const_structrp,
        info_ptr: png_inforp,
        entries: png_unknown_chunkpp,
    ) -> libc::c_int;
    fn png_write_png(
        png_ptr: png_structrp,
        info_ptr: png_inforp,
        transforms: libc::c_int,
        params: png_voidp,
    );
    fn png_set_user_limits(
        png_ptr: png_structrp,
        user_width_max: png_uint_32,
        user_height_max: png_uint_32,
    );
    fn png_get_io_state(png_ptr: png_const_structrp) -> png_uint_32;
    fn png_save_uint_32(buf: png_bytep, i: png_uint_32);
    fn opng_validate_image(png_ptr: png_structp, info_ptr: png_infop) -> libc::c_int;
    fn opng_reduce_image(
        png_ptr: png_structp,
        info_ptr: png_infop,
        reductions: png_uint_32,
    ) -> png_uint_32;
    fn pngx_read_image(
        png_ptr: png_structp,
        info_ptr: png_infop,
        fmt_name_ptr: png_const_charpp,
        fmt_long_name_ptr: png_const_charpp,
    ) -> libc::c_int;
    fn pngx_malloc_rows(
        png_ptr: png_structp,
        info_ptr: png_infop,
        filler: libc::c_int,
    ) -> png_bytepp;
    fn crc32(crc: uLong, buf: *const Bytef, len: uInt) -> uLong;
    fn opng_ftello(stream: *mut FILE) -> opng_foffset_t;
    fn opng_fseeko(
        stream: *mut FILE,
        offset: opng_foffset_t,
        whence: libc::c_int,
    ) -> libc::c_int;
    fn opng_fwriteo(
        stream: *mut FILE,
        offset: opng_foffset_t,
        whence: libc::c_int,
        block: *const libc::c_void,
        blocksize: size_t,
    ) -> size_t;
    fn opng_fgetsize(stream: *mut FILE, size: *mut opng_fsize_t) -> libc::c_int;
    fn opng_path_replace_dir(
        buffer: *mut libc::c_char,
        bufsize: size_t,
        old_path: *const libc::c_char,
        new_dirname: *const libc::c_char,
    ) -> *mut libc::c_char;
    fn opng_path_replace_ext(
        buffer: *mut libc::c_char,
        bufsize: size_t,
        old_path: *const libc::c_char,
        new_extname: *const libc::c_char,
    ) -> *mut libc::c_char;
    fn opng_path_make_backup(
        buffer: *mut libc::c_char,
        bufsize: size_t,
        path: *const libc::c_char,
    ) -> *mut libc::c_char;
    fn opng_os_rename(
        src_path: *const libc::c_char,
        dest_path: *const libc::c_char,
        clobber: libc::c_int,
    ) -> libc::c_int;
    fn opng_os_create_dir(dirname: *const libc::c_char) -> libc::c_int;
    fn opng_os_copy_file_attr(
        src_path: *const libc::c_char,
        dest_path: *const libc::c_char,
    ) -> libc::c_int;
    fn opng_os_test_file_access(
        path: *const libc::c_char,
        mode: *const libc::c_char,
    ) -> libc::c_int;
    fn opng_os_test_file_equiv(
        path1: *const libc::c_char,
        path2: *const libc::c_char,
    ) -> libc::c_int;
    fn opng_os_unlink(path: *const libc::c_char) -> libc::c_int;
    fn opng_ulratio_to_factor_string(
        buffer: *mut libc::c_char,
        buffer_size: size_t,
        ratio: *const opng_ulratio,
    ) -> libc::c_int;
    fn _setjmp(_: *mut __jmp_buf_tag) -> libc::c_int;
    fn longjmp(_: *mut __jmp_buf_tag, _: libc::c_int) -> !;
}
pub type size_t = libc::c_ulong;
pub type opng_bitset_t = libc::c_uint;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_options {
    pub backup: libc::c_int,
    pub clobber: libc::c_int,
    pub debug: libc::c_int,
    pub fix: libc::c_int,
    pub force: libc::c_int,
    pub full: libc::c_int,
    pub preserve: libc::c_int,
    pub quiet: libc::c_int,
    pub simulate: libc::c_int,
    pub verbose: libc::c_int,
    pub out_name: *const libc::c_char,
    pub dir_name: *const libc::c_char,
    pub log_name: *const libc::c_char,
    pub interlace: libc::c_int,
    pub nb: libc::c_int,
    pub nc: libc::c_int,
    pub np: libc::c_int,
    pub nz: libc::c_int,
    pub optim_level: libc::c_int,
    pub compr_level_set: opng_bitset_t,
    pub mem_level_set: opng_bitset_t,
    pub strategy_set: opng_bitset_t,
    pub filter_set: opng_bitset_t,
    pub window_bits: libc::c_int,
    pub snip: libc::c_int,
    pub strip_all: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_ui {
    pub printf_fn: Option::<unsafe extern "C" fn(*const libc::c_char, ...) -> ()>,
    pub print_cntrl_fn: Option::<unsafe extern "C" fn(libc::c_int) -> ()>,
    pub progress_fn: Option::<unsafe extern "C" fn(libc::c_ulong, libc::c_ulong) -> ()>,
    pub panic_fn: Option::<unsafe extern "C" fn(*const libc::c_char) -> ()>,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_engine_struct {
    pub started: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_summary_struct {
    pub file_count: libc::c_uint,
    pub err_count: libc::c_uint,
    pub fix_count: libc::c_uint,
    pub snip_count: libc::c_uint,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_image_struct {
    pub width: png_uint_32,
    pub height: png_uint_32,
    pub bit_depth: libc::c_int,
    pub color_type: libc::c_int,
    pub compression_type: libc::c_int,
    pub filter_type: libc::c_int,
    pub interlace_type: libc::c_int,
    pub row_pointers: png_bytepp,
    pub palette: png_colorp,
    pub num_palette: libc::c_int,
    pub background_ptr: png_color_16p,
    pub background: png_color_16,
    pub hist: png_uint_16p,
    pub sig_bit_ptr: png_color_8p,
    pub sig_bit: png_color_8,
    pub trans_alpha: png_bytep,
    pub num_trans: libc::c_int,
    pub trans_color_ptr: png_color_16p,
    pub trans_color: png_color_16,
    pub unknowns: png_unknown_chunkp,
    pub num_unknowns: libc::c_int,
}
pub type png_unknown_chunkp = *mut png_unknown_chunk;
pub type png_unknown_chunk = png_unknown_chunk_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_unknown_chunk_t {
    pub name: [png_byte; 5],
    pub data: *mut png_byte,
    pub size: size_t,
    pub location: png_byte,
}
pub type png_byte = libc::c_uchar;
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
pub type png_uint_16 = libc::c_ushort;
pub type png_color_16p = *mut png_color_16;
pub type png_bytep = *mut png_byte;
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
pub type png_color_8p = *mut png_color_8;
pub type png_uint_16p = *mut png_uint_16;
pub type png_colorp = *mut png_color;
pub type png_color = png_color_struct;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct png_color_struct {
    pub red: png_byte,
    pub green: png_byte,
    pub blue: png_byte,
}
pub type png_bytepp = *mut *mut png_byte;
pub type png_uint_32 = libc::c_uint;
pub const OPNG_STATUS_OK: opng_status_t = 0;
pub type opng_status_t = libc::c_int;
pub const OPNG_STATUS_ERR_OPTIPNG: opng_status_t = -2;
pub const OPNG_STATUS_ERR_LIBPNG: opng_status_t = -1;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed {
    pub etmp: opng_status_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct exception_context {
    pub penv: *mut jmp_buf,
    pub caught: libc::c_int,
    pub v: C2RustUnnamed,
}
pub type jmp_buf = [__jmp_buf_tag; 1];
#[derive(Copy, Clone)]
#[repr(C)]
pub struct __jmp_buf_tag {
    pub __jmpbuf: __jmp_buf,
    pub __mask_was_saved: libc::c_int,
    pub __saved_mask: __sigset_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct __sigset_t {
    pub __val: [libc::c_ulong; 16],
}
pub type __jmp_buf = [libc::c_long; 8];
pub const INPUT_HAS_MULTIPLE_IMAGES: C2RustUnnamed_0 = 16;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_process_struct {
    pub status: libc::c_uint,
    pub num_iterations: libc::c_int,
    pub in_datastream_offset: opng_foffset_t,
    pub in_file_size: opng_fsize_t,
    pub out_file_size: opng_fsize_t,
    pub in_idat_size: opng_fsize_t,
    pub out_idat_size: opng_fsize_t,
    pub best_idat_size: opng_fsize_t,
    pub max_idat_size: opng_fsize_t,
    pub in_plte_trns_size: png_uint_32,
    pub out_plte_trns_size: png_uint_32,
    pub reductions: png_uint_32,
    pub compr_level_set: opng_bitset_t,
    pub mem_level_set: opng_bitset_t,
    pub strategy_set: opng_bitset_t,
    pub filter_set: opng_bitset_t,
    pub best_compr_level: libc::c_int,
    pub best_mem_level: libc::c_int,
    pub best_strategy: libc::c_int,
    pub best_filter: libc::c_int,
}
pub type opng_fsize_t = libc::c_ulong;
pub type opng_foffset_t = libc::c_long;
pub const INPUT_HAS_ERRORS: C2RustUnnamed_0 = 256;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_ulratio {
    pub num: libc::c_ulong,
    pub denom: libc::c_ulong,
}
pub const INPUT_HAS_PNG_DATASTREAM: C2RustUnnamed_0 = 2;
pub type FILE = _IO_FILE;
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
pub type __off64_t = libc::c_long;
pub type _IO_lock_t = ();
pub type __off_t = libc::c_long;
pub type png_infopp = *mut *mut png_info;
pub type png_info = png_info_def;
pub type png_structp = *mut png_struct;
pub type png_struct = png_struct_def;
pub type png_structpp = *mut *mut png_struct;
pub type png_voidp = *mut libc::c_void;
pub type png_const_structrp = *const png_struct;
pub type png_const_bytep = *const png_byte;
pub type png_structrp = *mut png_struct;
pub type png_const_charp = *const libc::c_char;
pub type png_alloc_size_t = size_t;
pub type png_flush_ptr = Option::<unsafe extern "C" fn(png_structp) -> ()>;
pub type uLong = libc::c_ulong;
pub type uInt = libc::c_uint;
pub type Bytef = Byte;
pub type Byte = libc::c_uchar;
pub type png_rw_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_bytep, size_t) -> (),
>;
pub const OUTPUT_NEEDS_NEW_IDAT: C2RustUnnamed_0 = 8192;
pub type png_infop = *mut png_info;
pub type png_error_ptr = Option::<
    unsafe extern "C" fn(png_structp, png_const_charp) -> (),
>;
pub type png_inforp = *mut png_info;
pub type png_const_unknown_chunkp = *const png_unknown_chunk;
pub type png_const_color_8p = *const png_color_8;
pub type png_const_uint_16p = *const png_uint_16;
pub type png_const_color_16p = *const png_color_16;
pub type png_const_colorp = *const png_color;
pub const OUTPUT_NEEDS_NEW_FILE: C2RustUnnamed_0 = 4096;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opng_preset_struct {
    pub compr_level: *const libc::c_char,
    pub mem_level: *const libc::c_char,
    pub strategy: *const libc::c_char,
    pub filter: *const libc::c_char,
}
pub const INPUT_IS_PNG_FILE: C2RustUnnamed_0 = 1;
pub const INPUT_HAS_STRIPPED_DATA: C2RustUnnamed_0 = 64;
pub const INPUT_HAS_APNG: C2RustUnnamed_0 = 32;
pub const INPUT_HAS_DIGITAL_SIGNATURE: C2RustUnnamed_0 = 8;
pub const INPUT_HAS_PNG_SIGNATURE: C2RustUnnamed_0 = 4;
pub const INPUT_HAS_JUNK: C2RustUnnamed_0 = 128;
pub type png_unknown_chunkpp = *mut *mut png_unknown_chunk;
pub type png_const_inforp = *const png_info;
pub type png_const_charpp = *mut *const libc::c_char;
pub type C2RustUnnamed_0 = libc::c_uint;
pub const OUTPUT_HAS_ERRORS: C2RustUnnamed_0 = 16384;
#[no_mangle]
pub static mut the_exception_context: [exception_context; 1] = [exception_context {
    penv: 0 as *const jmp_buf as *mut jmp_buf,
    caught: 0,
    v: C2RustUnnamed {
        etmp: OPNG_STATUS_OK,
    },
}; 1];
static mut k_presets: [opng_preset_struct; 8] = [
    {
        let mut init = opng_preset_struct {
            compr_level: b"\0" as *const u8 as *const libc::c_char,
            mem_level: b"\0" as *const u8 as *const libc::c_char,
            strategy: b"\0" as *const u8 as *const libc::c_char,
            filter: b"\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"\0" as *const u8 as *const libc::c_char,
            mem_level: b"\0" as *const u8 as *const libc::c_char,
            strategy: b"\0" as *const u8 as *const libc::c_char,
            filter: b"\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"9\0" as *const u8 as *const libc::c_char,
            mem_level: b"8\0" as *const u8 as *const libc::c_char,
            strategy: b"0-\0" as *const u8 as *const libc::c_char,
            filter: b"0,5\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"9\0" as *const u8 as *const libc::c_char,
            mem_level: b"8-9\0" as *const u8 as *const libc::c_char,
            strategy: b"0-\0" as *const u8 as *const libc::c_char,
            filter: b"0,5\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"9\0" as *const u8 as *const libc::c_char,
            mem_level: b"8\0" as *const u8 as *const libc::c_char,
            strategy: b"0-\0" as *const u8 as *const libc::c_char,
            filter: b"0-\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"9\0" as *const u8 as *const libc::c_char,
            mem_level: b"8-9\0" as *const u8 as *const libc::c_char,
            strategy: b"0-\0" as *const u8 as *const libc::c_char,
            filter: b"0-\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"1-9\0" as *const u8 as *const libc::c_char,
            mem_level: b"8\0" as *const u8 as *const libc::c_char,
            strategy: b"0-\0" as *const u8 as *const libc::c_char,
            filter: b"0-\0" as *const u8 as *const libc::c_char,
        };
        init
    },
    {
        let mut init = opng_preset_struct {
            compr_level: b"1-9\0" as *const u8 as *const libc::c_char,
            mem_level: b"8-9\0" as *const u8 as *const libc::c_char,
            strategy: b"0-\0" as *const u8 as *const libc::c_char,
            filter: b"0-\0" as *const u8 as *const libc::c_char,
        };
        init
    },
];
static mut k_filter_table: [libc::c_int; 6] = [
    0x8 as libc::c_int,
    0x10 as libc::c_int,
    0x20 as libc::c_int,
    0x40 as libc::c_int,
    0x80 as libc::c_int,
    0x8 as libc::c_int | 0x10 as libc::c_int | 0x20 as libc::c_int | 0x40 as libc::c_int
        | 0x80 as libc::c_int,
];
static mut k_sig_PLTE: [png_byte; 4] = [
    0x50 as libc::c_int as png_byte,
    0x4c as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
    0x45 as libc::c_int as png_byte,
];
static mut k_sig_tRNS: [png_byte; 4] = [
    0x74 as libc::c_int as png_byte,
    0x52 as libc::c_int as png_byte,
    0x4e as libc::c_int as png_byte,
    0x53 as libc::c_int as png_byte,
];
static mut k_sig_IDAT: [png_byte; 4] = [
    0x49 as libc::c_int as png_byte,
    0x44 as libc::c_int as png_byte,
    0x41 as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
];
static mut k_sig_IEND: [png_byte; 4] = [
    0x49 as libc::c_int as png_byte,
    0x45 as libc::c_int as png_byte,
    0x4e as libc::c_int as png_byte,
    0x44 as libc::c_int as png_byte,
];
static mut k_sig_bKGD: [png_byte; 4] = [
    0x62 as libc::c_int as png_byte,
    0x4b as libc::c_int as png_byte,
    0x47 as libc::c_int as png_byte,
    0x44 as libc::c_int as png_byte,
];
static mut k_sig_hIST: [png_byte; 4] = [
    0x68 as libc::c_int as png_byte,
    0x49 as libc::c_int as png_byte,
    0x53 as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
];
static mut k_sig_sBIT: [png_byte; 4] = [
    0x73 as libc::c_int as png_byte,
    0x42 as libc::c_int as png_byte,
    0x49 as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
];
static mut k_sig_dSIG: [png_byte; 4] = [
    0x64 as libc::c_int as png_byte,
    0x53 as libc::c_int as png_byte,
    0x49 as libc::c_int as png_byte,
    0x47 as libc::c_int as png_byte,
];
static mut k_sig_acTL: [png_byte; 4] = [
    0x61 as libc::c_int as png_byte,
    0x63 as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
    0x4c as libc::c_int as png_byte,
];
static mut k_sig_fcTL: [png_byte; 4] = [
    0x66 as libc::c_int as png_byte,
    0x63 as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
    0x4c as libc::c_int as png_byte,
];
static mut k_sig_fdAT: [png_byte; 4] = [
    0x66 as libc::c_int as png_byte,
    0x64 as libc::c_int as png_byte,
    0x41 as libc::c_int as png_byte,
    0x54 as libc::c_int as png_byte,
];
static mut k_idat_size_max: opng_fsize_t = 0x7fffffff as libc::c_long as png_uint_32
    as opng_fsize_t;
static mut k_idat_size_max_string: *const libc::c_char = b"2GB\0" as *const u8
    as *const libc::c_char;
static mut s_engine: opng_engine_struct = opng_engine_struct { started: 0 };
static mut s_process: opng_process_struct = opng_process_struct {
    status: 0,
    num_iterations: 0,
    in_datastream_offset: 0,
    in_file_size: 0,
    out_file_size: 0,
    in_idat_size: 0,
    out_idat_size: 0,
    best_idat_size: 0,
    max_idat_size: 0,
    in_plte_trns_size: 0,
    out_plte_trns_size: 0,
    reductions: 0,
    compr_level_set: 0,
    mem_level_set: 0,
    strategy_set: 0,
    filter_set: 0,
    best_compr_level: 0,
    best_mem_level: 0,
    best_strategy: 0,
    best_filter: 0,
};
static mut s_summary: opng_summary_struct = opng_summary_struct {
    file_count: 0,
    err_count: 0,
    fix_count: 0,
    snip_count: 0,
};
static mut s_image: opng_image_struct = opng_image_struct {
    width: 0,
    height: 0,
    bit_depth: 0,
    color_type: 0,
    compression_type: 0,
    filter_type: 0,
    interlace_type: 0,
    row_pointers: 0 as *const *mut png_byte as *mut *mut png_byte,
    palette: 0 as *const png_color as *mut png_color,
    num_palette: 0,
    background_ptr: 0 as *const png_color_16 as *mut png_color_16,
    background: png_color_16_struct {
        index: 0,
        red: 0,
        green: 0,
        blue: 0,
        gray: 0,
    },
    hist: 0 as *const png_uint_16 as *mut png_uint_16,
    sig_bit_ptr: 0 as *const png_color_8 as *mut png_color_8,
    sig_bit: png_color_8_struct {
        red: 0,
        green: 0,
        blue: 0,
        gray: 0,
        alpha: 0,
    },
    trans_alpha: 0 as *const png_byte as *mut png_byte,
    num_trans: 0,
    trans_color_ptr: 0 as *const png_color_16 as *mut png_color_16,
    trans_color: png_color_16_struct {
        index: 0,
        red: 0,
        green: 0,
        blue: 0,
        gray: 0,
    },
    unknowns: 0 as *const png_unknown_chunk as *mut png_unknown_chunk,
    num_unknowns: 0,
};
static mut s_options: opng_options = opng_options {
    backup: 0,
    clobber: 0,
    debug: 0,
    fix: 0,
    force: 0,
    full: 0,
    preserve: 0,
    quiet: 0,
    simulate: 0,
    verbose: 0,
    out_name: 0 as *const libc::c_char,
    dir_name: 0 as *const libc::c_char,
    log_name: 0 as *const libc::c_char,
    interlace: 0,
    nb: 0,
    nc: 0,
    np: 0,
    nz: 0,
    optim_level: 0,
    compr_level_set: 0,
    mem_level_set: 0,
    strategy_set: 0,
    filter_set: 0,
    window_bits: 0,
    snip: 0,
    strip_all: 0,
};
static mut s_read_ptr: png_structp = 0 as *const png_struct as *mut png_struct;
static mut s_read_info_ptr: png_infop = 0 as *const png_info as *mut png_info;
static mut s_write_ptr: png_structp = 0 as *const png_struct as *mut png_struct;
static mut s_write_info_ptr: png_infop = 0 as *const png_info as *mut png_info;
static mut usr_printf: Option::<unsafe extern "C" fn(*const libc::c_char, ...) -> ()> = None;
static mut usr_print_cntrl: Option::<unsafe extern "C" fn(libc::c_int) -> ()> = None;
static mut usr_progress: Option::<
    unsafe extern "C" fn(libc::c_ulong, libc::c_ulong) -> (),
> = None;
static mut usr_panic: Option::<unsafe extern "C" fn(*const libc::c_char) -> ()> = None;
unsafe extern "C" fn opng_print_fsize_ratio(
    mut num: opng_fsize_t,
    mut denom: opng_fsize_t,
) {
    let mut buffer: [libc::c_char; 32] = [0; 32];
    let mut ratio: opng_ulratio = opng_ulratio { num: 0, denom: 0 };
    let mut result: libc::c_int = 0;
    ratio.num = num;
    ratio.denom = denom;
    result = opng_ulratio_to_factor_string(
        buffer.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 32]>() as libc::c_ulong,
        &mut ratio,
    );
    usr_printf
        .expect(
            "non-null function pointer",
        )(
        b"%s%s\0" as *const u8 as *const libc::c_char,
        buffer.as_mut_ptr(),
        if result > 0 as libc::c_int {
            b"\0" as *const u8 as *const libc::c_char
        } else {
            b"...\0" as *const u8 as *const libc::c_char
        },
    );
}
unsafe extern "C" fn opng_print_fsize_difference(
    mut init_size: opng_fsize_t,
    mut final_size: opng_fsize_t,
    mut show_ratio: libc::c_int,
) {
    let mut difference: opng_fsize_t = 0;
    let mut sign: libc::c_int = 0;
    if init_size <= final_size {
        sign = 0 as libc::c_int;
        difference = final_size.wrapping_sub(init_size);
    } else {
        sign = 1 as libc::c_int;
        difference = init_size.wrapping_sub(final_size);
    }
    if difference == 0 as libc::c_int as opng_fsize_t {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b"no change\0" as *const u8 as *const libc::c_char);
        return;
    }
    if difference == 1 as libc::c_int as opng_fsize_t {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b"1 byte\0" as *const u8 as *const libc::c_char);
    } else {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b"%lu bytes\0" as *const u8 as *const libc::c_char, difference);
    }
    if show_ratio != 0 && init_size > 0 as libc::c_int as opng_fsize_t {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b" = \0" as *const u8 as *const libc::c_char);
        opng_print_fsize_ratio(difference, init_size);
    }
    usr_printf
        .expect(
            "non-null function pointer",
        )(
        if sign == 0 as libc::c_int {
            b" increase\0" as *const u8 as *const libc::c_char
        } else {
            b" decrease\0" as *const u8 as *const libc::c_char
        },
    );
}
unsafe extern "C" fn opng_print_image_info(
    mut show_dim: libc::c_int,
    mut show_depth: libc::c_int,
    mut show_type: libc::c_int,
    mut show_interlaced: libc::c_int,
) {
    static mut type_channels: [libc::c_int; 8] = [
        1 as libc::c_int,
        0 as libc::c_int,
        3 as libc::c_int,
        1 as libc::c_int,
        2 as libc::c_int,
        0 as libc::c_int,
        4 as libc::c_int,
        0 as libc::c_int,
    ];
    let mut channels: libc::c_int = 0;
    let mut printed: libc::c_int = 0;
    printed = 0 as libc::c_int;
    if show_dim != 0 {
        printed = 1 as libc::c_int;
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"%lux%lu pixels\0" as *const u8 as *const libc::c_char,
            s_image.width as libc::c_ulong,
            s_image.height as libc::c_ulong,
        );
    }
    if show_depth != 0 {
        if printed != 0 {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b", \0" as *const u8 as *const libc::c_char);
        }
        printed = 1 as libc::c_int;
        channels = type_channels[(s_image.color_type & 7 as libc::c_int) as usize];
        if channels != 1 as libc::c_int {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"%dx%d bits/pixel\0" as *const u8 as *const libc::c_char,
                channels,
                s_image.bit_depth,
            );
        } else if s_image.bit_depth != 1 as libc::c_int {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"%d bits/pixel\0" as *const u8 as *const libc::c_char,
                s_image.bit_depth,
            );
        } else {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b"1 bit/pixel\0" as *const u8 as *const libc::c_char);
        }
    }
    if show_type != 0 {
        if printed != 0 {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b", \0" as *const u8 as *const libc::c_char);
        }
        printed = 1 as libc::c_int;
        if s_image.color_type & 1 as libc::c_int != 0 {
            if s_image.num_palette == 1 as libc::c_int {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"1 color\0" as *const u8 as *const libc::c_char);
            } else {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(
                    b"%d colors\0" as *const u8 as *const libc::c_char,
                    s_image.num_palette,
                );
            }
            if s_image.num_trans > 0 as libc::c_int {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(
                    b" (%d transparent)\0" as *const u8 as *const libc::c_char,
                    s_image.num_trans,
                );
            }
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b" in palette\0" as *const u8 as *const libc::c_char);
        } else {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                if s_image.color_type & 2 as libc::c_int != 0 {
                    b"RGB\0" as *const u8 as *const libc::c_char
                } else {
                    b"grayscale\0" as *const u8 as *const libc::c_char
                },
            );
            if s_image.color_type & 4 as libc::c_int != 0 {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"+alpha\0" as *const u8 as *const libc::c_char);
            } else if !(s_image.trans_color_ptr).is_null() {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"+transparency\0" as *const u8 as *const libc::c_char);
            }
        }
    }
    if show_interlaced != 0 {
        if s_image.interlace_type != 0 as libc::c_int {
            if printed != 0 {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b", \0" as *const u8 as *const libc::c_char);
            }
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b"interlaced\0" as *const u8 as *const libc::c_char);
        }
    }
}
unsafe extern "C" fn opng_print_warning(mut msg: *const libc::c_char) {
    usr_print_cntrl.expect("non-null function pointer")('\u{b}' as i32);
    usr_printf
        .expect(
            "non-null function pointer",
        )(b"Warning: %s\n\0" as *const u8 as *const libc::c_char, msg);
}
unsafe extern "C" fn opng_print_error(mut msg: *const libc::c_char) {
    usr_print_cntrl.expect("non-null function pointer")('\u{b}' as i32);
    usr_printf
        .expect(
            "non-null function pointer",
        )(b"Error: %s\n\0" as *const u8 as *const libc::c_char, msg);
}
unsafe extern "C" fn opng_throw_error(mut msg: png_const_charp) {
    opng_print_error(msg);
    loop {
        ::core::ptr::write_volatile(
            &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
            OPNG_STATUS_ERR_OPTIPNG,
        );
        longjmp(
            (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
            1 as libc::c_int,
        );
    };
}
unsafe extern "C" fn opng_warning(mut png_ptr: png_structp, mut msg: png_const_charp) {
    if png_ptr == s_read_ptr {
        s_process.status
            |= (INPUT_HAS_ERRORS as libc::c_int | OUTPUT_NEEDS_NEW_IDAT as libc::c_int)
                as libc::c_uint;
    }
    opng_print_warning(msg);
}
unsafe extern "C" fn opng_error(mut png_ptr: png_structp, mut msg: png_const_charp) {
    if png_ptr == s_read_ptr {
        s_process.status
            |= (INPUT_HAS_ERRORS as libc::c_int | OUTPUT_NEEDS_NEW_IDAT as libc::c_int)
                as libc::c_uint;
        if opng_validate_image(s_read_ptr, s_read_info_ptr) != 0 {
            opng_print_warning(msg);
            loop {
                ::core::ptr::write_volatile(
                    &mut (*the_exception_context.as_mut_ptr()).v.etmp
                        as *mut opng_status_t,
                    OPNG_STATUS_OK,
                );
                longjmp(
                    (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                    1 as libc::c_int,
                );
            }
        }
    }
    opng_print_error(msg);
    loop {
        ::core::ptr::write_volatile(
            &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
            OPNG_STATUS_ERR_LIBPNG,
        );
        longjmp(
            (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
            1 as libc::c_int,
        );
    };
}
unsafe extern "C" fn opng_free(mut ptr: *mut libc::c_void) {
    free(ptr);
}
unsafe extern "C" fn opng_check_idat_size(mut size: opng_fsize_t) {
    if size > k_idat_size_max {
        opng_throw_error(
            b"IDAT sizes larger than the maximum chunk size are currently unsupported\0"
                as *const u8 as *const libc::c_char,
        );
    }
}
unsafe extern "C" fn opng_set_keep_unknown_chunk(
    mut png_ptr: png_structp,
    mut keep: libc::c_int,
    mut chunk_type: png_bytep,
) {
    let mut chunk_name: [png_byte; 5] = [0; 5];
    memcpy(
        chunk_name.as_mut_ptr() as *mut libc::c_void,
        chunk_type as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    );
    chunk_name[4 as libc::c_int as usize] = 0 as libc::c_int as png_byte;
    if png_handle_as_unknown(
        png_ptr as png_const_structrp,
        chunk_name.as_mut_ptr() as png_const_bytep,
    ) == 0
    {
        png_set_keep_unknown_chunks(
            png_ptr,
            keep,
            chunk_name.as_mut_ptr() as png_const_bytep,
            1 as libc::c_int,
        );
    }
}
unsafe extern "C" fn opng_is_image_chunk(mut chunk_type: png_bytep) -> libc::c_int {
    if *chunk_type.offset(0 as libc::c_int as isize) as libc::c_int & 0x20 as libc::c_int
        == 0 as libc::c_int
    {
        return 1 as libc::c_int;
    }
    if memcmp(
        chunk_type as *const libc::c_void,
        k_sig_tRNS.as_ptr() as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    ) == 0 as libc::c_int
    {
        return 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn opng_is_apng_chunk(mut chunk_type: png_bytep) -> libc::c_int {
    if memcmp(
        chunk_type as *const libc::c_void,
        k_sig_acTL.as_ptr() as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    ) == 0 as libc::c_int
        || memcmp(
            chunk_type as *const libc::c_void,
            k_sig_fcTL.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        || memcmp(
            chunk_type as *const libc::c_void,
            k_sig_fdAT.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
    {
        return 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn opng_allow_chunk(mut chunk_type: png_bytep) -> libc::c_int {
    if opng_is_image_chunk(chunk_type) != 0 {
        return 1 as libc::c_int;
    }
    if s_options.strip_all != 0 {
        return 0 as libc::c_int;
    }
    if memcmp(
        chunk_type as *const libc::c_void,
        k_sig_dSIG.as_ptr() as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    ) == 0 as libc::c_int
    {
        return 0 as libc::c_int;
    }
    if s_options.snip != 0 && opng_is_apng_chunk(chunk_type) != 0 {
        return 0 as libc::c_int;
    }
    return 1 as libc::c_int;
}
unsafe extern "C" fn opng_handle_chunk(
    mut png_ptr: png_structp,
    mut chunk_type: png_bytep,
) {
    let mut keep: libc::c_int = 0;
    if opng_is_image_chunk(chunk_type) != 0 {
        return;
    }
    if s_options.strip_all != 0 {
        s_process.status
            |= (INPUT_HAS_STRIPPED_DATA as libc::c_int | INPUT_HAS_JUNK as libc::c_int)
                as libc::c_uint;
        opng_set_keep_unknown_chunk(png_ptr, 1 as libc::c_int, chunk_type);
        return;
    }
    if memcmp(
        chunk_type as *const libc::c_void,
        k_sig_bKGD.as_ptr() as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    ) == 0 as libc::c_int
        || memcmp(
            chunk_type as *const libc::c_void,
            k_sig_hIST.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        || memcmp(
            chunk_type as *const libc::c_void,
            k_sig_sBIT.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
    {
        return;
    }
    keep = 3 as libc::c_int;
    if memcmp(
        chunk_type as *const libc::c_void,
        k_sig_dSIG.as_ptr() as *const libc::c_void,
        4 as libc::c_int as libc::c_ulong,
    ) == 0 as libc::c_int
    {
        s_process.status |= INPUT_HAS_DIGITAL_SIGNATURE as libc::c_int as libc::c_uint;
    } else if opng_is_apng_chunk(chunk_type) != 0 {
        s_process.status |= INPUT_HAS_APNG as libc::c_int as libc::c_uint;
        if memcmp(
            chunk_type as *const libc::c_void,
            k_sig_fdAT.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        {
            s_process.status |= INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint;
        }
        if s_options.snip != 0 {
            s_process.status |= INPUT_HAS_JUNK as libc::c_int as libc::c_uint;
            keep = 1 as libc::c_int;
        }
    }
    opng_set_keep_unknown_chunk(png_ptr, keep, chunk_type);
}
unsafe extern "C" fn opng_init_read_data() {}
unsafe extern "C" fn opng_init_write_data() {
    s_process.out_file_size = 0 as libc::c_int as opng_fsize_t;
    s_process.out_plte_trns_size = 0 as libc::c_int as png_uint_32;
    s_process.out_idat_size = 0 as libc::c_int as opng_fsize_t;
}
unsafe extern "C" fn opng_read_data(
    mut png_ptr: png_structp,
    mut data: png_bytep,
    mut length: size_t,
) {
    let mut stream: *mut FILE = png_get_io_ptr(png_ptr as png_const_structrp)
        as *mut FILE;
    let mut io_state: libc::c_int = png_get_io_state(png_ptr as png_const_structrp)
        as libc::c_int;
    let mut io_state_loc: libc::c_int = io_state & 0xf0 as libc::c_int;
    let mut chunk_sig: png_bytep = 0 as *mut png_byte;
    if fread(
        data as *mut libc::c_void,
        1 as libc::c_int as libc::c_ulong,
        length,
        stream,
    ) != length
    {
        png_error(
            png_ptr as png_const_structrp,
            b"Can't read the input file or unexpected end of file\0" as *const u8
                as *const libc::c_char,
        );
    }
    if s_process.in_file_size == 0 as libc::c_int as opng_fsize_t {
        if !(length == 8 as libc::c_int as size_t) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"PNG I/O must start with the first 8 bytes\0" as *const u8
                    as *const libc::c_char,
            );
        }
        s_process
            .in_datastream_offset = opng_ftello(stream)
            - 8 as libc::c_int as opng_foffset_t;
        s_process.status |= INPUT_HAS_PNG_DATASTREAM as libc::c_int as libc::c_uint;
        if io_state_loc == 0x10 as libc::c_int {
            s_process.status |= INPUT_HAS_PNG_SIGNATURE as libc::c_int as libc::c_uint;
        }
        if s_process.in_datastream_offset == 0 as libc::c_int as opng_foffset_t {
            s_process.status |= INPUT_IS_PNG_FILE as libc::c_int as libc::c_uint;
        } else if s_process.in_datastream_offset < 0 as libc::c_int as opng_foffset_t {
            png_error(
                png_ptr as png_const_structrp,
                b"Can't get the file-position indicator in input file\0" as *const u8
                    as *const libc::c_char,
            );
        }
        s_process.in_file_size = s_process.in_datastream_offset as opng_fsize_t;
    }
    s_process
        .in_file_size = (s_process.in_file_size as libc::c_ulong).wrapping_add(length)
        as opng_fsize_t as opng_fsize_t;
    if !(io_state & 0x1 as libc::c_int != 0 && io_state_loc != 0 as libc::c_int) {
        usr_panic
            .expect(
                "non-null function pointer",
            )(
            b"Incorrect info in png_ptr->io_state\0" as *const u8 as *const libc::c_char,
        );
    }
    if io_state_loc == 0x20 as libc::c_int {
        if !(length == 8 as libc::c_int as size_t) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"Reading chunk header, expecting 8 bytes\0" as *const u8
                    as *const libc::c_char,
            );
        }
        chunk_sig = data.offset(4 as libc::c_int as isize);
        if memcmp(
            chunk_sig as *const libc::c_void,
            k_sig_IDAT.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        {
            if !(png_ptr == s_read_ptr) {
                usr_panic
                    .expect(
                        "non-null function pointer",
                    )(
                    b"Incorrect I/O handler setup\0" as *const u8 as *const libc::c_char,
                );
            }
            if (png_get_rows(
                s_read_ptr as png_const_structrp,
                s_read_info_ptr as png_const_inforp,
            ))
                .is_null()
            {
                if !(s_process.in_idat_size == 0 as libc::c_int as opng_fsize_t) {
                    usr_panic
                        .expect(
                            "non-null function pointer",
                        )(
                        b"Found IDAT with no rows\0" as *const u8 as *const libc::c_char,
                    );
                }
                if png_get_image_height(
                    s_read_ptr as png_const_structrp,
                    s_read_info_ptr as png_const_inforp,
                ) == 0 as libc::c_int as png_uint_32
                {
                    return;
                }
                if (pngx_malloc_rows(s_read_ptr, s_read_info_ptr, 0 as libc::c_int))
                    .is_null()
                {
                    usr_panic
                        .expect(
                            "non-null function pointer",
                        )(
                        b"Failed allocation of image rows; unsafe libpng allocator\0"
                            as *const u8 as *const libc::c_char,
                    );
                }
                png_data_freer(
                    s_read_ptr as png_const_structrp,
                    s_read_info_ptr,
                    2 as libc::c_int,
                    0x40 as libc::c_uint,
                );
            } else {
                s_process.status |= INPUT_HAS_JUNK as libc::c_int as libc::c_uint;
            }
            s_process
                .in_idat_size = (s_process.in_idat_size)
                .wrapping_add(
                    ((*data as png_uint_32) << 24 as libc::c_int)
                        .wrapping_add(
                            (*data.offset(1 as libc::c_int as isize) as png_uint_32)
                                << 16 as libc::c_int,
                        )
                        .wrapping_add(
                            (*data.offset(2 as libc::c_int as isize) as png_uint_32)
                                << 8 as libc::c_int,
                        )
                        .wrapping_add(
                            *data.offset(3 as libc::c_int as isize) as png_uint_32,
                        ) as opng_fsize_t,
                );
        } else if memcmp(
            chunk_sig as *const libc::c_void,
            k_sig_PLTE.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
            || memcmp(
                chunk_sig as *const libc::c_void,
                k_sig_tRNS.as_ptr() as *const libc::c_void,
                4 as libc::c_int as libc::c_ulong,
            ) == 0 as libc::c_int
        {
            s_process
                .in_plte_trns_size = (s_process.in_plte_trns_size)
                .wrapping_add(
                    ((*data as png_uint_32) << 24 as libc::c_int)
                        .wrapping_add(
                            (*data.offset(1 as libc::c_int as isize) as png_uint_32)
                                << 16 as libc::c_int,
                        )
                        .wrapping_add(
                            (*data.offset(2 as libc::c_int as isize) as png_uint_32)
                                << 8 as libc::c_int,
                        )
                        .wrapping_add(
                            *data.offset(3 as libc::c_int as isize) as png_uint_32,
                        )
                        .wrapping_add(12 as libc::c_int as png_uint_32),
                );
        } else {
            opng_handle_chunk(png_ptr, chunk_sig);
        }
    } else if io_state_loc == 0x80 as libc::c_int {
        if !(length == 4 as libc::c_int as size_t) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"Reading chunk CRC, expecting 4 bytes\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
}
unsafe extern "C" fn opng_write_data(
    mut png_ptr: png_structp,
    mut data: png_bytep,
    mut length: size_t,
) {
    static mut allow_crt_chunk: libc::c_int = 0;
    static mut crt_chunk_is_idat: libc::c_int = 0;
    static mut crt_idat_offset: opng_foffset_t = 0;
    static mut crt_idat_size: opng_fsize_t = 0;
    static mut crt_idat_crc: png_uint_32 = 0;
    let mut stream: *mut FILE = png_get_io_ptr(png_ptr as png_const_structrp)
        as *mut FILE;
    let mut io_state: libc::c_int = png_get_io_state(png_ptr as png_const_structrp)
        as libc::c_int;
    let mut io_state_loc: libc::c_int = io_state & 0xf0 as libc::c_int;
    let mut chunk_sig: png_bytep = 0 as *mut png_byte;
    let mut buf: [png_byte; 4] = [0; 4];
    if !(io_state & 0x2 as libc::c_int != 0 && io_state_loc != 0 as libc::c_int) {
        usr_panic
            .expect(
                "non-null function pointer",
            )(
            b"Incorrect info in png_ptr->io_state\0" as *const u8 as *const libc::c_char,
        );
    }
    if io_state_loc == 0x20 as libc::c_int {
        if !(length == 8 as libc::c_int as size_t) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"Writing chunk header, expecting 8 bytes\0" as *const u8
                    as *const libc::c_char,
            );
        }
        chunk_sig = data.offset(4 as libc::c_int as isize);
        allow_crt_chunk = opng_allow_chunk(chunk_sig);
        if memcmp(
            chunk_sig as *const libc::c_void,
            k_sig_IDAT.as_ptr() as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
        {
            crt_chunk_is_idat = 1 as libc::c_int;
            s_process
                .out_idat_size = (s_process.out_idat_size)
                .wrapping_add(
                    ((*data as png_uint_32) << 24 as libc::c_int)
                        .wrapping_add(
                            (*data.offset(1 as libc::c_int as isize) as png_uint_32)
                                << 16 as libc::c_int,
                        )
                        .wrapping_add(
                            (*data.offset(2 as libc::c_int as isize) as png_uint_32)
                                << 8 as libc::c_int,
                        )
                        .wrapping_add(
                            *data.offset(3 as libc::c_int as isize) as png_uint_32,
                        ) as opng_fsize_t,
                );
            if stream.is_null() {
                if s_process.out_idat_size > s_process.max_idat_size {
                    loop {
                        ::core::ptr::write_volatile(
                            &mut (*the_exception_context.as_mut_ptr()).v.etmp
                                as *mut opng_status_t,
                            OPNG_STATUS_OK,
                        );
                        longjmp(
                            (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                            1 as libc::c_int,
                        );
                    }
                }
            }
        } else {
            crt_chunk_is_idat = 0 as libc::c_int;
            if memcmp(
                chunk_sig as *const libc::c_void,
                k_sig_PLTE.as_ptr() as *const libc::c_void,
                4 as libc::c_int as libc::c_ulong,
            ) == 0 as libc::c_int
                || memcmp(
                    chunk_sig as *const libc::c_void,
                    k_sig_tRNS.as_ptr() as *const libc::c_void,
                    4 as libc::c_int as libc::c_ulong,
                ) == 0 as libc::c_int
            {
                s_process
                    .out_plte_trns_size = (s_process.out_plte_trns_size)
                    .wrapping_add(
                        ((*data as png_uint_32) << 24 as libc::c_int)
                            .wrapping_add(
                                (*data.offset(1 as libc::c_int as isize) as png_uint_32)
                                    << 16 as libc::c_int,
                            )
                            .wrapping_add(
                                (*data.offset(2 as libc::c_int as isize) as png_uint_32)
                                    << 8 as libc::c_int,
                            )
                            .wrapping_add(
                                *data.offset(3 as libc::c_int as isize) as png_uint_32,
                            )
                            .wrapping_add(12 as libc::c_int as png_uint_32),
                    );
            }
        }
    } else if io_state_loc == 0x80 as libc::c_int {
        if !(length == 4 as libc::c_int as size_t) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"Writing chunk CRC, expecting 4 bytes\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
    if stream.is_null() {
        return;
    }
    if io_state_loc != 0x10 as libc::c_int && allow_crt_chunk == 0 {
        return;
    }
    match io_state_loc {
        32 => {
            if crt_chunk_is_idat != 0 {
                if crt_idat_offset == 0 as libc::c_int as opng_foffset_t {
                    crt_idat_offset = opng_ftello(stream);
                    if s_process.best_idat_size > 0 as libc::c_int as opng_fsize_t {
                        crt_idat_size = s_process.best_idat_size;
                    } else {
                        crt_idat_size = length;
                    }
                    png_save_uint_32(data, crt_idat_size as png_uint_32);
                    crt_idat_crc = crc32(
                        0 as libc::c_int as uLong,
                        k_sig_IDAT.as_ptr(),
                        4 as libc::c_int as uInt,
                    ) as png_uint_32;
                } else {
                    return
                }
            } else if crt_idat_offset != 0 as libc::c_int as opng_foffset_t {
                png_save_uint_32(buf.as_mut_ptr(), crt_idat_crc);
                if fwrite(
                    buf.as_mut_ptr() as *const libc::c_void,
                    1 as libc::c_int as libc::c_ulong,
                    4 as libc::c_int as libc::c_ulong,
                    stream,
                ) != 4 as libc::c_int as libc::c_ulong
                {
                    io_state = 0 as libc::c_int;
                }
                s_process
                    .out_file_size = (s_process.out_file_size)
                    .wrapping_add(4 as libc::c_int as opng_fsize_t);
                if s_process.out_idat_size != crt_idat_size {
                    if !(s_process.best_idat_size == 0 as libc::c_int as opng_fsize_t) {
                        usr_panic
                            .expect(
                                "non-null function pointer",
                            )(
                            b"Wrong guess of the output IDAT size\0" as *const u8
                                as *const libc::c_char,
                        );
                    }
                    opng_check_idat_size(s_process.out_idat_size);
                    png_save_uint_32(
                        buf.as_mut_ptr(),
                        s_process.out_idat_size as png_uint_32,
                    );
                    if opng_fwriteo(
                        stream,
                        crt_idat_offset,
                        0 as libc::c_int,
                        buf.as_mut_ptr() as *const libc::c_void,
                        4 as libc::c_int as size_t,
                    ) != 4 as libc::c_int as size_t
                    {
                        io_state = 0 as libc::c_int;
                    }
                }
                if io_state == 0 as libc::c_int {
                    png_error(
                        png_ptr as png_const_structrp,
                        b"Can't finalize IDAT\0" as *const u8 as *const libc::c_char,
                    );
                }
                crt_idat_offset = 0 as libc::c_int as opng_foffset_t;
            }
        }
        64 => {
            if crt_chunk_is_idat != 0 {
                crt_idat_crc = crc32(
                    crt_idat_crc as uLong,
                    data as *const Bytef,
                    length as uInt,
                ) as png_uint_32;
            }
        }
        128 => {
            if crt_chunk_is_idat != 0 {
                return;
            }
        }
        _ => {}
    }
    if fwrite(
        data as *const libc::c_void,
        1 as libc::c_int as libc::c_ulong,
        length,
        stream,
    ) != length
    {
        png_error(
            png_ptr as png_const_structrp,
            b"Can't write the output file\0" as *const u8 as *const libc::c_char,
        );
    }
    s_process
        .out_file_size = (s_process.out_file_size as libc::c_ulong).wrapping_add(length)
        as opng_fsize_t as opng_fsize_t;
}
unsafe extern "C" fn opng_clear_image_info() {
    memset(
        &mut s_image as *mut opng_image_struct as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<opng_image_struct>() as libc::c_ulong,
    );
}
unsafe extern "C" fn opng_load_image_info(
    mut png_ptr: png_structp,
    mut info_ptr: png_infop,
    mut load_meta: libc::c_int,
) {
    memset(
        &mut s_image as *mut opng_image_struct as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<opng_image_struct>() as libc::c_ulong,
    );
    png_get_IHDR(
        png_ptr as png_const_structrp,
        info_ptr as png_const_inforp,
        &mut s_image.width,
        &mut s_image.height,
        &mut s_image.bit_depth,
        &mut s_image.color_type,
        &mut s_image.interlace_type,
        &mut s_image.compression_type,
        &mut s_image.filter_type,
    );
    s_image
        .row_pointers = png_get_rows(
        png_ptr as png_const_structrp,
        info_ptr as png_const_inforp,
    );
    png_get_PLTE(
        png_ptr as png_const_structrp,
        info_ptr,
        &mut s_image.palette,
        &mut s_image.num_palette,
    );
    if png_get_tRNS(
        png_ptr as png_const_structrp,
        info_ptr,
        &mut s_image.trans_alpha,
        &mut s_image.num_trans,
        &mut s_image.trans_color_ptr,
    ) != 0
    {
        if !(s_image.trans_color_ptr).is_null() {
            s_image.trans_color = *s_image.trans_color_ptr;
            s_image.trans_color_ptr = &mut s_image.trans_color;
        }
    }
    if load_meta == 0 {
        return;
    }
    if png_get_bKGD(png_ptr as png_const_structrp, info_ptr, &mut s_image.background_ptr)
        != 0
    {
        s_image.background = *s_image.background_ptr;
        s_image.background_ptr = &mut s_image.background;
    }
    png_get_hIST(png_ptr as png_const_structrp, info_ptr, &mut s_image.hist);
    if png_get_sBIT(png_ptr as png_const_structrp, info_ptr, &mut s_image.sig_bit_ptr)
        != 0
    {
        s_image.sig_bit = *s_image.sig_bit_ptr;
        s_image.sig_bit_ptr = &mut s_image.sig_bit;
    }
    s_image
        .num_unknowns = png_get_unknown_chunks(
        png_ptr as png_const_structrp,
        info_ptr,
        &mut s_image.unknowns,
    );
}
unsafe extern "C" fn opng_store_image_info(
    mut png_ptr: png_structp,
    mut info_ptr: png_infop,
    mut store_meta: libc::c_int,
) {
    let mut i: libc::c_int = 0;
    if (s_image.row_pointers).is_null() {
        usr_panic
            .expect(
                "non-null function pointer",
            )(b"No info in image\0" as *const u8 as *const libc::c_char);
    }
    png_set_IHDR(
        png_ptr as png_const_structrp,
        info_ptr,
        s_image.width,
        s_image.height,
        s_image.bit_depth,
        s_image.color_type,
        s_image.interlace_type,
        s_image.compression_type,
        s_image.filter_type,
    );
    png_set_rows(
        s_write_ptr as png_const_structrp,
        s_write_info_ptr,
        s_image.row_pointers,
    );
    if !(s_image.palette).is_null() {
        png_set_PLTE(
            png_ptr,
            info_ptr,
            s_image.palette as png_const_colorp,
            s_image.num_palette,
        );
    }
    if !(s_image.trans_alpha).is_null() || !(s_image.trans_color_ptr).is_null() {
        png_set_tRNS(
            png_ptr,
            info_ptr,
            s_image.trans_alpha as png_const_bytep,
            s_image.num_trans,
            s_image.trans_color_ptr as png_const_color_16p,
        );
    }
    if store_meta == 0 {
        return;
    }
    if !(s_image.background_ptr).is_null() {
        png_set_bKGD(
            png_ptr as png_const_structrp,
            info_ptr,
            s_image.background_ptr as png_const_color_16p,
        );
    }
    if !(s_image.hist).is_null() {
        png_set_hIST(
            png_ptr as png_const_structrp,
            info_ptr,
            s_image.hist as png_const_uint_16p,
        );
    }
    if !(s_image.sig_bit_ptr).is_null() {
        png_set_sBIT(
            png_ptr as png_const_structrp,
            info_ptr,
            s_image.sig_bit_ptr as png_const_color_8p,
        );
    }
    if s_image.num_unknowns != 0 as libc::c_int {
        png_set_unknown_chunks(
            png_ptr as png_const_structrp,
            info_ptr,
            s_image.unknowns as png_const_unknown_chunkp,
            s_image.num_unknowns,
        );
        i = 0 as libc::c_int;
        while i < s_image.num_unknowns {
            png_set_unknown_chunk_location(
                png_ptr as png_const_structrp,
                info_ptr,
                i,
                (*(s_image.unknowns).offset(i as isize)).location as libc::c_int,
            );
            i += 1;
            i;
        }
    }
}
unsafe extern "C" fn opng_destroy_image_info() {
    let mut i: png_uint_32 = 0;
    let mut j: libc::c_int = 0;
    if (s_image.row_pointers).is_null() {
        return;
    }
    i = 0 as libc::c_int as png_uint_32;
    while i < s_image.height {
        opng_free(*(s_image.row_pointers).offset(i as isize) as *mut libc::c_void);
        i = i.wrapping_add(1);
        i;
    }
    opng_free(s_image.row_pointers as *mut libc::c_void);
    opng_free(s_image.palette as *mut libc::c_void);
    opng_free(s_image.trans_alpha as *mut libc::c_void);
    opng_free(s_image.hist as *mut libc::c_void);
    j = 0 as libc::c_int;
    while j < s_image.num_unknowns {
        opng_free((*(s_image.unknowns).offset(j as isize)).data as *mut libc::c_void);
        j += 1;
        j;
    }
    opng_free(s_image.unknowns as *mut libc::c_void);
    memset(
        &mut s_image as *mut opng_image_struct as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<opng_image_struct>() as libc::c_ulong,
    );
}
unsafe extern "C" fn opng_read_file(mut infile: *mut FILE) {
    let mut fmt_name: *const libc::c_char = 0 as *const libc::c_char;
    let mut num_img: libc::c_int = 0;
    let mut reductions: png_uint_32 = 0;
    let mut status: opng_status_t = OPNG_STATUS_OK;
    ::core::ptr::write_volatile(&mut status as *mut opng_status_t, OPNG_STATUS_OK);
    let mut exception__prev: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh0 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh0 = &mut exception__env;
    if _setjmp(exception__env.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            s_read_ptr = png_create_read_struct(
                b"1.6.40\0" as *const u8 as *const libc::c_char,
                0 as *mut libc::c_void,
                Some(
                    opng_error
                        as unsafe extern "C" fn(png_structp, png_const_charp) -> (),
                ),
                Some(
                    opng_warning
                        as unsafe extern "C" fn(png_structp, png_const_charp) -> (),
                ),
            );
            s_read_info_ptr = png_create_info_struct(s_read_ptr as png_const_structrp);
            if s_read_info_ptr.is_null() {
                opng_throw_error(
                    b"Can't create image decoder\0" as *const u8 as *const libc::c_char,
                );
            }
            png_set_keep_unknown_chunks(
                s_read_ptr,
                3 as libc::c_int,
                0 as png_const_bytep,
                0 as libc::c_int,
            );
            png_set_user_limits(
                s_read_ptr,
                0x7fffffff as libc::c_long as png_uint_32,
                0x7fffffff as libc::c_long as png_uint_32,
            );
            opng_init_read_data();
            png_set_read_fn(
                s_read_ptr,
                infile as png_voidp,
                Some(
                    opng_read_data
                        as unsafe extern "C" fn(png_structp, png_bytep, size_t) -> (),
                ),
            );
            fmt_name = 0 as *const libc::c_char;
            num_img = pngx_read_image(
                s_read_ptr,
                s_read_info_ptr,
                &mut fmt_name,
                0 as png_const_charpp,
            );
            if num_img <= 0 as libc::c_int {
                opng_throw_error(
                    b"Unrecognized image file format\0" as *const u8
                        as *const libc::c_char,
                );
            }
            if num_img > 1 as libc::c_int {
                s_process.status
                    |= INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint;
            }
            if s_process.status & INPUT_IS_PNG_FILE as libc::c_int as libc::c_uint != 0
                && s_process.status
                    & INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint != 0
            {
                fmt_name = if s_process.status
                    & INPUT_HAS_PNG_SIGNATURE as libc::c_int as libc::c_uint != 0
                {
                    b"APNG\0" as *const u8 as *const libc::c_char
                } else {
                    b"APNG datastream\0" as *const u8 as *const libc::c_char
                };
            }
            if fmt_name.is_null() {
                usr_panic
                    .expect(
                        "non-null function pointer",
                    )(
                    b"No format name from pngxtern\0" as *const u8 as *const libc::c_char,
                );
            }
            if s_process.in_file_size == 0 as libc::c_int as opng_fsize_t {
                if opng_fgetsize(infile, &mut s_process.in_file_size) < 0 as libc::c_int
                {
                    opng_print_warning(
                        b"Can't get the correct file size\0" as *const u8
                            as *const libc::c_char,
                    );
                    s_process.in_file_size = 0 as libc::c_int as opng_fsize_t;
                }
            }
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh1 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh1 = exception__prev[0 as libc::c_int as usize];
    if !((*the_exception_context.as_mut_ptr()).caught == 0
        || {
            ::core::ptr::write_volatile(
                &mut status as *mut opng_status_t,
                (*the_exception_context.as_mut_ptr()).v.etmp,
            );
            0 as libc::c_int != 0
        })
    {
        if opng_validate_image(s_read_ptr, s_read_info_ptr) != 0 {
            if !(status as libc::c_int == OPNG_STATUS_OK as libc::c_int) {
                usr_panic
                    .expect(
                        "non-null function pointer",
                    )(
                    b"Mysterious error in validated image file\0" as *const u8
                        as *const libc::c_char,
                );
            }
        }
    }
    let mut exception__prev_0: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env_0: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev_0[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh2 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh2 = &mut exception__env_0;
    if _setjmp(exception__env_0.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            if status as libc::c_int != OPNG_STATUS_OK as libc::c_int {
                loop {
                    ::core::ptr::write_volatile(
                        &mut (*the_exception_context.as_mut_ptr()).v.etmp
                            as *mut opng_status_t,
                        status,
                    );
                    longjmp(
                        (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                        1 as libc::c_int,
                    );
                }
            }
            if strcmp(fmt_name, b"PNG\0" as *const u8 as *const libc::c_char)
                != 0 as libc::c_int
            {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"Importing %s\0" as *const u8 as *const libc::c_char, fmt_name);
                if s_process.status
                    & INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint != 0
                {
                    if s_process.status
                        & INPUT_IS_PNG_FILE as libc::c_int as libc::c_uint == 0
                    {
                        usr_printf
                            .expect(
                                "non-null function pointer",
                            )(
                            b" (multi-image or animation)\0" as *const u8
                                as *const libc::c_char,
                        );
                    }
                    if s_options.snip != 0 {
                        usr_printf
                            .expect(
                                "non-null function pointer",
                            )(b"; snipping...\0" as *const u8 as *const libc::c_char);
                    }
                }
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"\n\0" as *const u8 as *const libc::c_char);
            }
            opng_load_image_info(s_read_ptr, s_read_info_ptr, 1 as libc::c_int);
            opng_print_image_info(
                1 as libc::c_int,
                1 as libc::c_int,
                1 as libc::c_int,
                1 as libc::c_int,
            );
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b"\n\0" as *const u8 as *const libc::c_char);
            reductions = ((0x1 as libc::c_int | 0x2 as libc::c_int
                | (0x4 as libc::c_int | 0x8 as libc::c_int | 0x10 as libc::c_int
                    | 0x20 as libc::c_int | 0x40 as libc::c_int | 0x80 as libc::c_int)
                | (0x100 as libc::c_int | 0x200 as libc::c_int) | 0x1000 as libc::c_int)
                & !(0x1000 as libc::c_int)) as png_uint_32;
            if s_options.nb != 0 {
                reductions &= !(0x1 as libc::c_int | 0x2 as libc::c_int) as png_uint_32;
            }
            if s_options.nc != 0 {
                reductions
                    &= !(0x4 as libc::c_int | 0x8 as libc::c_int | 0x10 as libc::c_int
                        | 0x20 as libc::c_int | 0x40 as libc::c_int
                        | 0x80 as libc::c_int) as png_uint_32;
            }
            if s_options.np != 0 {
                reductions
                    &= !(0x100 as libc::c_int | 0x200 as libc::c_int) as png_uint_32;
            }
            if s_options.nz != 0
                && s_process.status
                    & INPUT_HAS_PNG_DATASTREAM as libc::c_int as libc::c_uint != 0
            {
                reductions = 0 as libc::c_int as png_uint_32;
            }
            if s_process.status
                & INPUT_HAS_DIGITAL_SIGNATURE as libc::c_int as libc::c_uint != 0
            {
                reductions = 0 as libc::c_int as png_uint_32;
            }
            if s_process.status & INPUT_IS_PNG_FILE as libc::c_int as libc::c_uint != 0
                && s_process.status
                    & INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint != 0
                && reductions != 0 as libc::c_int as png_uint_32 && s_options.snip == 0
            {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(
                    b"Can't reliably reduce APNG file; disabling reductions.\n(Did you want to -snip and optimize the first frame?)\n\0"
                        as *const u8 as *const libc::c_char,
                );
                reductions = 0 as libc::c_int as png_uint_32;
            }
            s_process
                .reductions = opng_reduce_image(s_read_ptr, s_read_info_ptr, reductions);
            if s_process.reductions != 0 as libc::c_int as png_uint_32 {
                opng_load_image_info(s_read_ptr, s_read_info_ptr, 1 as libc::c_int);
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"Reducing image to \0" as *const u8 as *const libc::c_char);
                opng_print_image_info(
                    0 as libc::c_int,
                    1 as libc::c_int,
                    1 as libc::c_int,
                    0 as libc::c_int,
                );
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(b"\n\0" as *const u8 as *const libc::c_char);
            }
            if s_options.interlace >= 0 as libc::c_int
                && s_image.interlace_type != s_options.interlace
            {
                s_image.interlace_type = s_options.interlace;
                s_process.status |= OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint;
            }
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh3 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh3 = exception__prev_0[0 as libc::c_int as usize];
    if (*the_exception_context.as_mut_ptr()).caught == 0
        || {
            ::core::ptr::write_volatile(
                &mut status as *mut opng_status_t,
                (*the_exception_context.as_mut_ptr()).v.etmp,
            );
            0 as libc::c_int != 0
        }
    {} else {
        png_data_freer(
            s_read_ptr as png_const_structrp,
            s_read_info_ptr,
            1 as libc::c_int,
            0xffff as libc::c_uint,
        );
        png_destroy_read_struct(&mut s_read_ptr, &mut s_read_info_ptr, 0 as png_infopp);
        loop {
            ::core::ptr::write_volatile(
                &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
                status,
            );
            longjmp(
                (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                1 as libc::c_int,
            );
        }
    }
    png_data_freer(
        s_read_ptr as png_const_structrp,
        s_read_info_ptr,
        2 as libc::c_int,
        0xffff as libc::c_uint,
    );
    png_destroy_read_struct(&mut s_read_ptr, &mut s_read_info_ptr, 0 as png_infopp);
}
unsafe extern "C" fn opng_write_file(
    mut outfile: *mut FILE,
    mut compression_level: libc::c_int,
    mut memory_level: libc::c_int,
    mut compression_strategy: libc::c_int,
    mut filter: libc::c_int,
) {
    let mut status: opng_status_t = OPNG_STATUS_OK;
    if !(compression_level >= 1 as libc::c_int && compression_level <= 9 as libc::c_int
        && memory_level >= 1 as libc::c_int && memory_level <= 9 as libc::c_int
        && compression_strategy >= 0 as libc::c_int
        && compression_strategy <= 3 as libc::c_int && filter >= 0 as libc::c_int
        && filter <= 5 as libc::c_int)
    {
        usr_panic
            .expect(
                "non-null function pointer",
            )(b"Invalid encoding parameters\0" as *const u8 as *const libc::c_char);
    }
    ::core::ptr::write_volatile(&mut status as *mut opng_status_t, OPNG_STATUS_OK);
    let mut exception__prev: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh4 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh4 = &mut exception__env;
    if _setjmp(exception__env.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            s_write_ptr = png_create_write_struct(
                b"1.6.40\0" as *const u8 as *const libc::c_char,
                0 as *mut libc::c_void,
                Some(
                    opng_error
                        as unsafe extern "C" fn(png_structp, png_const_charp) -> (),
                ),
                Some(
                    opng_warning
                        as unsafe extern "C" fn(png_structp, png_const_charp) -> (),
                ),
            );
            s_write_info_ptr = png_create_info_struct(s_write_ptr as png_const_structrp);
            if s_write_info_ptr.is_null() {
                opng_throw_error(
                    b"Can't create image encoder\0" as *const u8 as *const libc::c_char,
                );
            }
            png_set_compression_level(s_write_ptr, compression_level);
            png_set_compression_mem_level(s_write_ptr, memory_level);
            png_set_compression_strategy(s_write_ptr, compression_strategy);
            png_set_filter(
                s_write_ptr,
                0 as libc::c_int,
                k_filter_table[filter as usize],
            );
            if compression_strategy != 2 as libc::c_int
                && compression_strategy != 3 as libc::c_int
            {
                if s_options.window_bits > 0 as libc::c_int {
                    png_set_compression_window_bits(s_write_ptr, s_options.window_bits);
                }
            } else {
                png_set_compression_window_bits(s_write_ptr, 9 as libc::c_int);
            }
            png_set_keep_unknown_chunks(
                s_write_ptr,
                3 as libc::c_int,
                0 as png_const_bytep,
                0 as libc::c_int,
            );
            png_set_user_limits(
                s_write_ptr,
                0x7fffffff as libc::c_long as png_uint_32,
                0x7fffffff as libc::c_long as png_uint_32,
            );
            opng_store_image_info(
                s_write_ptr,
                s_write_info_ptr,
                (outfile != 0 as *mut libc::c_void as *mut FILE) as libc::c_int,
            );
            opng_init_write_data();
            png_set_write_fn(
                s_write_ptr,
                outfile as png_voidp,
                Some(
                    opng_write_data
                        as unsafe extern "C" fn(png_structp, png_bytep, size_t) -> (),
                ),
                None,
            );
            png_write_png(
                s_write_ptr,
                s_write_info_ptr,
                0 as libc::c_int,
                0 as *mut libc::c_void,
            );
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh5 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh5 = exception__prev[0 as libc::c_int as usize];
    if !((*the_exception_context.as_mut_ptr()).caught == 0
        || {
            ::core::ptr::write_volatile(
                &mut status as *mut opng_status_t,
                (*the_exception_context.as_mut_ptr()).v.etmp,
            );
            0 as libc::c_int != 0
        })
    {
        s_process
            .out_idat_size = k_idat_size_max
            .wrapping_add(1 as libc::c_int as opng_fsize_t);
    }
    png_destroy_write_struct(&mut s_write_ptr, &mut s_write_info_ptr);
    if status as libc::c_int != OPNG_STATUS_OK as libc::c_int {
        loop {
            ::core::ptr::write_volatile(
                &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
                status,
            );
            longjmp(
                (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                1 as libc::c_int,
            );
        }
    }
}
unsafe extern "C" fn opng_copy_file(mut infile: *mut FILE, mut outfile: *mut FILE) {
    let mut buf: png_bytep = 0 as *mut png_byte;
    let buf_size_incr: png_uint_32 = 0x1000 as libc::c_int as png_uint_32;
    let mut buf_size: png_uint_32 = 0;
    let mut length: png_uint_32 = 0;
    let mut chunk_hdr: [png_byte; 8] = [0; 8];
    let mut status: opng_status_t = OPNG_STATUS_OK;
    s_write_ptr = png_create_write_struct(
        b"1.6.40\0" as *const u8 as *const libc::c_char,
        0 as *mut libc::c_void,
        Some(opng_error as unsafe extern "C" fn(png_structp, png_const_charp) -> ()),
        Some(opng_warning as unsafe extern "C" fn(png_structp, png_const_charp) -> ()),
    );
    if s_write_ptr.is_null() {
        opng_throw_error(
            b"Can't create image encoder\0" as *const u8 as *const libc::c_char,
        );
    }
    opng_init_write_data();
    png_set_write_fn(
        s_write_ptr,
        outfile as png_voidp,
        Some(
            opng_write_data as unsafe extern "C" fn(png_structp, png_bytep, size_t) -> (),
        ),
        None,
    );
    ::core::ptr::write_volatile(&mut status as *mut opng_status_t, OPNG_STATUS_OK);
    let mut exception__prev: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh6 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh6 = &mut exception__env;
    if _setjmp(exception__env.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            ::core::ptr::write_volatile(&mut buf as *mut png_bytep, 0 as png_bytep);
            buf_size = 0 as libc::c_int as png_uint_32;
            png_write_sig(s_write_ptr);
            let mut current_block_22: u64;
            loop {
                if fread(
                    chunk_hdr.as_mut_ptr() as *mut libc::c_void,
                    8 as libc::c_int as libc::c_ulong,
                    1 as libc::c_int as libc::c_ulong,
                    infile,
                ) != 1 as libc::c_int as libc::c_ulong
                {
                    opng_throw_error(
                        b"Read error\0" as *const u8 as *const libc::c_char,
                    );
                }
                length = ((*chunk_hdr.as_mut_ptr() as png_uint_32) << 24 as libc::c_int)
                    .wrapping_add(
                        (*chunk_hdr.as_mut_ptr().offset(1 as libc::c_int as isize)
                            as png_uint_32) << 16 as libc::c_int,
                    )
                    .wrapping_add(
                        (*chunk_hdr.as_mut_ptr().offset(2 as libc::c_int as isize)
                            as png_uint_32) << 8 as libc::c_int,
                    )
                    .wrapping_add(
                        *chunk_hdr.as_mut_ptr().offset(3 as libc::c_int as isize)
                            as png_uint_32,
                    );
                if length > 0x7fffffff as libc::c_long as png_uint_32 {
                    if buf.is_null()
                        && length as libc::c_ulong == 0x89504e47 as libc::c_ulong
                    {
                        current_block_22 = 12209867499936983673;
                    } else {
                        opng_throw_error(
                            b"Data error\0" as *const u8 as *const libc::c_char,
                        );
                        current_block_22 = 8457315219000651999;
                    }
                } else {
                    current_block_22 = 8457315219000651999;
                }
                match current_block_22 {
                    8457315219000651999 => {
                        if length.wrapping_add(4 as libc::c_int as png_uint_32)
                            > buf_size
                        {
                            png_free(
                                s_write_ptr as png_const_structrp,
                                buf as png_voidp,
                            );
                            buf_size = length
                                .wrapping_add(4 as libc::c_int as png_uint_32)
                                .wrapping_add(
                                    buf_size_incr.wrapping_sub(1 as libc::c_int as png_uint_32),
                                ) / buf_size_incr * buf_size_incr;
                            ::core::ptr::write_volatile(
                                &mut buf as *mut png_bytep,
                                png_malloc(
                                    s_write_ptr as png_const_structrp,
                                    buf_size as png_alloc_size_t,
                                ) as png_bytep,
                            );
                        }
                        if fread(
                            buf as *mut libc::c_void,
                            length.wrapping_add(4 as libc::c_int as png_uint_32)
                                as libc::c_ulong,
                            1 as libc::c_int as libc::c_ulong,
                            infile,
                        ) != 1 as libc::c_int as libc::c_ulong
                        {
                            opng_throw_error(
                                b"Read error\0" as *const u8 as *const libc::c_char,
                            );
                        }
                        png_write_chunk(
                            s_write_ptr,
                            chunk_hdr.as_mut_ptr().offset(4 as libc::c_int as isize)
                                as png_const_bytep,
                            buf as png_const_bytep,
                            length as size_t,
                        );
                    }
                    _ => {}
                }
                if !(memcmp(
                    chunk_hdr.as_mut_ptr().offset(4 as libc::c_int as isize)
                        as *const libc::c_void,
                    k_sig_IEND.as_ptr() as *const libc::c_void,
                    4 as libc::c_int as libc::c_ulong,
                ) != 0 as libc::c_int)
                {
                    break;
                }
            }
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh7 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh7 = exception__prev[0 as libc::c_int as usize];
    (*the_exception_context.as_mut_ptr()).caught == 0
        || {
            ::core::ptr::write_volatile(
                &mut status as *mut opng_status_t,
                (*the_exception_context.as_mut_ptr()).v.etmp,
            );
            0 as libc::c_int != 0
        };
    png_free(s_write_ptr as png_const_structrp, buf as png_voidp);
    png_destroy_write_struct(&mut s_write_ptr, 0 as png_infopp);
    if status as libc::c_int != OPNG_STATUS_OK as libc::c_int {
        loop {
            ::core::ptr::write_volatile(
                &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
                status,
            );
            longjmp(
                (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                1 as libc::c_int,
            );
        }
    }
}
unsafe extern "C" fn opng_init_iteration(
    mut cmdline_set: opng_bitset_t,
    mut mask_set: opng_bitset_t,
    mut preset: *const libc::c_char,
    mut output_set: *mut opng_bitset_t,
) {
    let mut preset_set: opng_bitset_t = 0;
    let mut check: libc::c_int = 0;
    *output_set = cmdline_set & mask_set;
    if *output_set == 0 as libc::c_int as opng_bitset_t
        && cmdline_set != 0 as libc::c_int as opng_bitset_t
    {
        opng_throw_error(
            b"Iteration parameter(s) out of range\0" as *const u8 as *const libc::c_char,
        );
    }
    if s_options.optim_level >= 0 as libc::c_int
        || *output_set == 0 as libc::c_int as opng_bitset_t
    {
        check = opng_strparse_rangeset_to_bitset(&mut preset_set, preset, mask_set);
        if !(check == 0 as libc::c_int) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(b"[internal] Invalid preset\0" as *const u8 as *const libc::c_char);
        }
        *output_set |= preset_set & mask_set;
    }
}
unsafe extern "C" fn opng_init_iterations() {
    let mut compr_level_set: opng_bitset_t = 0;
    let mut mem_level_set: opng_bitset_t = 0;
    let mut strategy_set: opng_bitset_t = 0;
    let mut filter_set: opng_bitset_t = 0;
    let mut strategy_singles_set: opng_bitset_t = 0;
    let mut preset_index: libc::c_int = 0;
    let mut t1: libc::c_int = 0;
    let mut t2: libc::c_int = 0;
    if s_options.full != 0
        || s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint != 0
    {
        s_process.max_idat_size = k_idat_size_max;
    } else {
        if !(s_process.in_idat_size > 0 as libc::c_int as opng_fsize_t) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(b"No IDAT in input\0" as *const u8 as *const libc::c_char);
        }
        s_process
            .max_idat_size = (s_process.in_idat_size)
            .wrapping_add(s_process.in_plte_trns_size as opng_fsize_t);
    }
    preset_index = s_options.optim_level;
    if preset_index < 0 as libc::c_int {
        preset_index = 2 as libc::c_int;
    } else if preset_index > 7 as libc::c_int {
        preset_index = 7 as libc::c_int;
    }
    opng_init_iteration(
        s_options.compr_level_set,
        (((1 as libc::c_int) << 9 as libc::c_int + 1 as libc::c_int)
            - ((1 as libc::c_int) << 1 as libc::c_int)) as opng_bitset_t,
        k_presets[preset_index as usize].compr_level,
        &mut compr_level_set,
    );
    opng_init_iteration(
        s_options.mem_level_set,
        (((1 as libc::c_int) << 9 as libc::c_int + 1 as libc::c_int)
            - ((1 as libc::c_int) << 1 as libc::c_int)) as opng_bitset_t,
        k_presets[preset_index as usize].mem_level,
        &mut mem_level_set,
    );
    opng_init_iteration(
        s_options.strategy_set,
        (((1 as libc::c_int) << 3 as libc::c_int + 1 as libc::c_int)
            - ((1 as libc::c_int) << 0 as libc::c_int)) as opng_bitset_t,
        k_presets[preset_index as usize].strategy,
        &mut strategy_set,
    );
    opng_init_iteration(
        s_options.filter_set,
        (((1 as libc::c_int) << 5 as libc::c_int + 1 as libc::c_int)
            - ((1 as libc::c_int) << 0 as libc::c_int)) as opng_bitset_t,
        k_presets[preset_index as usize].filter,
        &mut filter_set,
    );
    if compr_level_set == 0 as libc::c_int as opng_bitset_t {
        compr_level_set |= (1 as libc::c_uint) << 9 as libc::c_int;
    }
    if mem_level_set == 0 as libc::c_int as opng_bitset_t {
        mem_level_set |= (1 as libc::c_uint) << 8 as libc::c_int;
    }
    if s_image.bit_depth < 8 as libc::c_int || !(s_image.palette).is_null() {
        if strategy_set == 0 as libc::c_int as opng_bitset_t {
            strategy_set |= (1 as libc::c_uint) << 0 as libc::c_int;
        }
        if filter_set == 0 as libc::c_int as opng_bitset_t {
            filter_set |= (1 as libc::c_uint) << 0 as libc::c_int;
        }
    } else {
        if strategy_set == 0 as libc::c_int as opng_bitset_t {
            strategy_set |= (1 as libc::c_uint) << 1 as libc::c_int;
        }
        if filter_set == 0 as libc::c_int as opng_bitset_t {
            filter_set |= (1 as libc::c_uint) << 5 as libc::c_int;
        }
    }
    s_process.compr_level_set = compr_level_set;
    s_process.mem_level_set = mem_level_set;
    s_process.strategy_set = strategy_set;
    s_process.filter_set = filter_set;
    strategy_singles_set = ((1 as libc::c_int) << 2 as libc::c_int
        | (1 as libc::c_int) << 3 as libc::c_int) as opng_bitset_t;
    t1 = (opng_bitset_count(compr_level_set))
        .wrapping_mul(opng_bitset_count(strategy_set & !strategy_singles_set))
        as libc::c_int;
    t2 = opng_bitset_count(strategy_set & strategy_singles_set) as libc::c_int;
    s_process
        .num_iterations = ((t1 + t2) as libc::c_uint)
        .wrapping_mul(opng_bitset_count(mem_level_set))
        .wrapping_mul(opng_bitset_count(filter_set)) as libc::c_int;
    if !(s_process.num_iterations > 0 as libc::c_int) {
        usr_panic
            .expect(
                "non-null function pointer",
            )(b"Invalid iteration parameters\0" as *const u8 as *const libc::c_char);
    }
}
unsafe extern "C" fn opng_iterate() {
    let mut compr_level_set: opng_bitset_t = 0;
    let mut mem_level_set: opng_bitset_t = 0;
    let mut strategy_set: opng_bitset_t = 0;
    let mut filter_set: opng_bitset_t = 0;
    let mut compr_level: libc::c_int = 0;
    let mut mem_level: libc::c_int = 0;
    let mut strategy: libc::c_int = 0;
    let mut filter: libc::c_int = 0;
    let mut counter: libc::c_int = 0;
    let mut line_reused: libc::c_int = 0;
    if !(s_process.num_iterations > 0 as libc::c_int) {
        usr_panic
            .expect(
                "non-null function pointer",
            )(b"Iterations not initialized\0" as *const u8 as *const libc::c_char);
    }
    compr_level_set = s_process.compr_level_set;
    mem_level_set = s_process.mem_level_set;
    strategy_set = s_process.strategy_set;
    filter_set = s_process.filter_set;
    if s_process.num_iterations == 1 as libc::c_int
        && s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint != 0
    {
        s_process.best_idat_size = 0 as libc::c_int as opng_fsize_t;
        s_process.best_compr_level = opng_bitset_find_first(compr_level_set);
        s_process.best_mem_level = opng_bitset_find_first(mem_level_set);
        s_process.best_strategy = opng_bitset_find_first(strategy_set);
        s_process.best_filter = opng_bitset_find_first(filter_set);
        return;
    }
    s_process
        .best_idat_size = k_idat_size_max.wrapping_add(1 as libc::c_int as opng_fsize_t);
    s_process.best_compr_level = -(1 as libc::c_int);
    s_process.best_mem_level = -(1 as libc::c_int);
    s_process.best_strategy = -(1 as libc::c_int);
    s_process.best_filter = -(1 as libc::c_int);
    usr_printf
        .expect(
            "non-null function pointer",
        )(b"\nTrying:\n\0" as *const u8 as *const libc::c_char);
    line_reused = 0 as libc::c_int;
    counter = 0 as libc::c_int;
    filter = 0 as libc::c_int;
    while filter <= 5 as libc::c_int {
        if filter_set & (1 as libc::c_uint) << filter != 0 as libc::c_int as libc::c_uint
        {
            strategy = 0 as libc::c_int;
            while strategy <= 3 as libc::c_int {
                if strategy_set & (1 as libc::c_uint) << strategy
                    != 0 as libc::c_int as libc::c_uint
                {
                    if strategy == 2 as libc::c_int {
                        compr_level_set = 0 as libc::c_int as opng_bitset_t;
                        compr_level_set |= (1 as libc::c_uint) << 1 as libc::c_int;
                    } else if strategy == 3 as libc::c_int {
                        compr_level_set = 0 as libc::c_int as opng_bitset_t;
                        compr_level_set |= (1 as libc::c_uint) << 9 as libc::c_int;
                    } else {
                        compr_level_set = s_process.compr_level_set;
                    }
                    compr_level = 9 as libc::c_int;
                    while compr_level >= 1 as libc::c_int {
                        if compr_level_set & (1 as libc::c_uint) << compr_level
                            != 0 as libc::c_int as libc::c_uint
                        {
                            mem_level = 9 as libc::c_int;
                            while mem_level >= 1 as libc::c_int {
                                if mem_level_set & (1 as libc::c_uint) << mem_level
                                    != 0 as libc::c_int as libc::c_uint
                                {
                                    usr_printf
                                        .expect(
                                            "non-null function pointer",
                                        )(
                                        b"  zc = %d  zm = %d  zs = %d  f = %d\0" as *const u8
                                            as *const libc::c_char,
                                        compr_level,
                                        mem_level,
                                        strategy,
                                        filter,
                                    );
                                    usr_progress
                                        .expect(
                                            "non-null function pointer",
                                        )(
                                        counter as libc::c_ulong,
                                        s_process.num_iterations as libc::c_ulong,
                                    );
                                    counter += 1;
                                    counter;
                                    opng_write_file(
                                        0 as *mut FILE,
                                        compr_level,
                                        mem_level,
                                        strategy,
                                        filter,
                                    );
                                    if s_process.out_idat_size > k_idat_size_max {
                                        if s_options.verbose != 0 {
                                            usr_printf
                                                .expect(
                                                    "non-null function pointer",
                                                )(
                                                b"\t\tIDAT too big\n\0" as *const u8 as *const libc::c_char,
                                            );
                                            line_reused = 0 as libc::c_int;
                                        } else {
                                            usr_print_cntrl
                                                .expect("non-null function pointer")('\r' as i32);
                                            line_reused = 1 as libc::c_int;
                                        }
                                    } else {
                                        usr_printf
                                            .expect(
                                                "non-null function pointer",
                                            )(
                                            b"\t\tIDAT size = %lu\n\0" as *const u8
                                                as *const libc::c_char,
                                            s_process.out_idat_size,
                                        );
                                        line_reused = 0 as libc::c_int;
                                        if !(s_process.best_idat_size < s_process.out_idat_size) {
                                            if !(s_process.best_idat_size == s_process.out_idat_size
                                                && (s_process.best_strategy == 2 as libc::c_int
                                                    || s_process.best_strategy == 3 as libc::c_int))
                                            {
                                                s_process.best_compr_level = compr_level;
                                                s_process.best_mem_level = mem_level;
                                                s_process.best_strategy = strategy;
                                                s_process.best_filter = filter;
                                                s_process.best_idat_size = s_process.out_idat_size;
                                                if s_options.full == 0 {
                                                    s_process.max_idat_size = s_process.out_idat_size;
                                                }
                                            }
                                        }
                                    }
                                }
                                mem_level -= 1;
                                mem_level;
                            }
                        }
                        compr_level -= 1;
                        compr_level;
                    }
                }
                strategy += 1;
                strategy;
            }
        }
        filter += 1;
        filter;
    }
    if line_reused != 0 {
        usr_print_cntrl.expect("non-null function pointer")(-(31 as libc::c_int));
    }
    if !(counter == s_process.num_iterations) {
        usr_panic
            .expect(
                "non-null function pointer",
            )(b"Inconsistent iteration counter\0" as *const u8 as *const libc::c_char);
    }
    usr_progress
        .expect(
            "non-null function pointer",
        )(counter as libc::c_ulong, s_process.num_iterations as libc::c_ulong);
}
unsafe extern "C" fn opng_finish_iterations() {
    if (s_process.best_idat_size)
        .wrapping_add(s_process.out_plte_trns_size as opng_fsize_t)
        < (s_process.in_idat_size)
            .wrapping_add(s_process.in_plte_trns_size as opng_fsize_t)
    {
        s_process.status |= OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint;
    }
    if s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint != 0 {
        if s_process.best_idat_size <= k_idat_size_max {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b"\nSelecting parameters:\n\0" as *const u8 as *const libc::c_char);
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"  zc = %d  zm = %d  zs = %d  f = %d\0" as *const u8
                    as *const libc::c_char,
                s_process.best_compr_level,
                s_process.best_mem_level,
                s_process.best_strategy,
                s_process.best_filter,
            );
            if s_process.best_idat_size > 0 as libc::c_int as opng_fsize_t {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(
                    b"\t\tIDAT size = %lu\0" as *const u8 as *const libc::c_char,
                    s_process.best_idat_size,
                );
            }
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b"\n\0" as *const u8 as *const libc::c_char);
        } else {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"  zc = *  zm = *  zs = *  f = *\t\tIDAT size > %s\n\0" as *const u8
                    as *const libc::c_char,
                k_idat_size_max_string,
            );
        }
    }
}
unsafe extern "C" fn opng_optimize_impl(mut infile_name: *const libc::c_char) {
    static mut infile: *mut FILE = 0 as *const FILE as *mut FILE;
    static mut outfile: *mut FILE = 0 as *const FILE as *mut FILE;
    static mut infile_name_local: *const libc::c_char = 0 as *const libc::c_char;
    static mut outfile_name: *const libc::c_char = 0 as *const libc::c_char;
    static mut bakfile_name: *const libc::c_char = 0 as *const libc::c_char;
    static mut new_outfile: libc::c_int = 0;
    static mut has_backup: libc::c_int = 0;
    let mut name_buf: [libc::c_char; 4096] = [0; 4096];
    let mut tmp_buf: [libc::c_char; 4096] = [0; 4096];
    let mut status: opng_status_t = OPNG_STATUS_OK;
    memset(
        &mut s_process as *mut opng_process_struct as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<opng_process_struct>() as libc::c_ulong,
    );
    if s_options.force != 0 {
        s_process.status |= OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint;
    }
    infile_name_local = infile_name;
    infile = fopen(infile_name_local, b"rb\0" as *const u8 as *const libc::c_char);
    if infile.is_null() {
        opng_throw_error(
            b"Can't open the input file\0" as *const u8 as *const libc::c_char,
        );
    }
    ::core::ptr::write_volatile(&mut status as *mut opng_status_t, OPNG_STATUS_OK);
    let mut exception__prev: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh8 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh8 = &mut exception__env;
    if _setjmp(exception__env.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            opng_read_file(infile);
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh9 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh9 = exception__prev[0 as libc::c_int as usize];
    if !((*the_exception_context.as_mut_ptr()).caught == 0
        || {
            ::core::ptr::write_volatile(
                &mut status as *mut opng_status_t,
                (*the_exception_context.as_mut_ptr()).v.etmp,
            );
            0 as libc::c_int != 0
        })
    {
        if !(status as libc::c_int != OPNG_STATUS_OK as libc::c_int) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"opng_read_file should throw errors only\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
    fclose(infile);
    if status as libc::c_int != OPNG_STATUS_OK as libc::c_int {
        loop {
            ::core::ptr::write_volatile(
                &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
                status,
            );
            longjmp(
                (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                1 as libc::c_int,
            );
        }
    }
    if s_process.status & INPUT_HAS_ERRORS as libc::c_int as libc::c_uint != 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"Recoverable errors found in input.\0" as *const u8 as *const libc::c_char,
        );
        if s_options.fix != 0 {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b" Fixing...\n\0" as *const u8 as *const libc::c_char);
            s_process.status |= OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint;
        } else {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b" Rerun OptiPNG with -fix enabled.\n\0" as *const u8
                    as *const libc::c_char,
            );
            opng_throw_error(
                b"Previous error(s) not fixed\0" as *const u8 as *const libc::c_char,
            );
        }
    }
    if s_process.status & INPUT_HAS_JUNK as libc::c_int as libc::c_uint != 0 {
        s_process.status |= OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint;
    }
    if s_process.status & INPUT_HAS_PNG_SIGNATURE as libc::c_int as libc::c_uint == 0 {
        s_process.status |= OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint;
    }
    if s_process.status & INPUT_HAS_PNG_DATASTREAM as libc::c_int as libc::c_uint != 0 {
        if s_options.nz != 0
            && s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint
                != 0
        {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"IDAT recoding is necessary, but is disabled by the user.\n\0"
                    as *const u8 as *const libc::c_char,
            );
            opng_throw_error(b"Can't continue\0" as *const u8 as *const libc::c_char);
        }
    } else {
        s_process.status |= OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint;
    }
    if s_process.status & INPUT_HAS_DIGITAL_SIGNATURE as libc::c_int as libc::c_uint != 0
    {
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"Digital signature found in input.\0" as *const u8 as *const libc::c_char,
        );
        if s_options.force != 0 {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(b" Erasing...\n\0" as *const u8 as *const libc::c_char);
            s_process.status |= OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint;
        } else {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b" Rerun OptiPNG with -force enabled.\n\0" as *const u8
                    as *const libc::c_char,
            );
            opng_throw_error(
                b"Can't optimize digitally-signed files\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
    if s_process.status & INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint != 0 {
        if s_options.snip == 0
            && s_process.status & INPUT_IS_PNG_FILE as libc::c_int as libc::c_uint == 0
        {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"Conversion to PNG requires snipping. Rerun OptiPNG with -snip enabled.\n\0"
                    as *const u8 as *const libc::c_char,
            );
            opng_throw_error(
                b"Incompatible input format\0" as *const u8 as *const libc::c_char,
            );
        }
    }
    if s_options.snip != 0
        && s_process.status & INPUT_HAS_APNG as libc::c_int as libc::c_uint != 0
    {
        s_process.status |= OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint;
    }
    if s_process.status & INPUT_HAS_STRIPPED_DATA as libc::c_int as libc::c_uint != 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b"Stripping metadata...\n\0" as *const u8 as *const libc::c_char);
    }
    outfile_name = 0 as *const libc::c_char;
    if s_process.status & INPUT_IS_PNG_FILE as libc::c_int as libc::c_uint == 0 {
        if (opng_path_replace_ext(
            name_buf.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 4096]>() as libc::c_ulong,
            infile_name_local,
            b".png\0" as *const u8 as *const libc::c_char,
        ))
            .is_null()
        {
            opng_throw_error(
                b"Can't create the output file (name too long)\0" as *const u8
                    as *const libc::c_char,
            );
        }
        outfile_name = name_buf.as_mut_ptr();
    }
    if !(s_options.out_name).is_null() {
        outfile_name = s_options.out_name;
    }
    if !(s_options.dir_name).is_null() {
        let mut tmp_name: *const libc::c_char = 0 as *const libc::c_char;
        if !outfile_name.is_null() {
            strcpy(tmp_buf.as_mut_ptr(), outfile_name);
            tmp_name = tmp_buf.as_mut_ptr();
        } else {
            tmp_name = infile_name_local;
        }
        if (opng_path_replace_dir(
            name_buf.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 4096]>() as libc::c_ulong,
            tmp_name,
            s_options.dir_name,
        ))
            .is_null()
        {
            opng_throw_error(
                b"Can't create the output file (name too long)\0" as *const u8
                    as *const libc::c_char,
            );
        }
        outfile_name = name_buf.as_mut_ptr();
    }
    if outfile_name.is_null() {
        outfile_name = infile_name_local;
        new_outfile = 0 as libc::c_int;
    } else {
        let mut test_eq: libc::c_int = opng_os_test_file_equiv(
            infile_name_local,
            outfile_name,
        );
        if test_eq >= 0 as libc::c_int {
            new_outfile = (test_eq == 0 as libc::c_int) as libc::c_int;
        } else {
            new_outfile = (strcmp(infile_name_local, outfile_name) != 0 as libc::c_int)
                as libc::c_int;
        }
    }
    bakfile_name = tmp_buf.as_mut_ptr();
    if new_outfile != 0 {
        if (opng_path_make_backup(
            tmp_buf.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 4096]>() as libc::c_ulong,
            outfile_name,
        ))
            .is_null()
        {
            bakfile_name = 0 as *const libc::c_char;
        }
    } else if (opng_path_make_backup(
        tmp_buf.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 4096]>() as libc::c_ulong,
        infile_name_local,
    ))
        .is_null()
    {
        bakfile_name = 0 as *const libc::c_char;
    }
    if bakfile_name.is_null() {
        opng_throw_error(
            b"Can't create backup file (name too long)\0" as *const u8
                as *const libc::c_char,
        );
    }
    if s_options.simulate == 0
        && opng_os_test_file_access(
            outfile_name,
            b"e\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
    {
        if s_options.backup == 0 && s_options.clobber == 0 && new_outfile != 0 {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"The output file exists. Rerun OptiPNG with -backup enabled.\n\0"
                    as *const u8 as *const libc::c_char,
            );
            opng_throw_error(
                b"Can't overwrite the output file\0" as *const u8 as *const libc::c_char,
            );
        }
        if opng_os_test_file_access(
            outfile_name,
            b"fw\0" as *const u8 as *const libc::c_char,
        ) != 0 as libc::c_int
            || s_options.clobber == 0
                && opng_os_test_file_access(
                    bakfile_name,
                    b"e\0" as *const u8 as *const libc::c_char,
                ) == 0 as libc::c_int
        {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"A backup file already exists. Rerun OptiPNG with -clobber enabled.\n\0"
                    as *const u8 as *const libc::c_char,
            );
            opng_throw_error(
                b"Can't back up the existing output file\0" as *const u8
                    as *const libc::c_char,
            );
        }
    }
    if s_process.status & INPUT_HAS_PNG_DATASTREAM as libc::c_int as libc::c_uint != 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"Input IDAT size = %lu bytes\n\0" as *const u8 as *const libc::c_char,
            s_process.in_idat_size,
        );
    }
    usr_printf
        .expect(
            "non-null function pointer",
        )(
        b"Input file size = %lu bytes\n\0" as *const u8 as *const libc::c_char,
        s_process.in_file_size,
    );
    if s_options.nz == 0
        || s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint != 0
    {
        opng_init_iterations();
        opng_iterate();
        opng_finish_iterations();
    }
    if s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint != 0 {
        s_process.status |= OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint;
        opng_check_idat_size(s_process.best_idat_size);
    }
    if s_process.status & OUTPUT_NEEDS_NEW_FILE as libc::c_int as libc::c_uint == 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"\n%s is already optimized.\n\0" as *const u8 as *const libc::c_char,
            infile_name_local,
        );
        if new_outfile == 0 {
            return;
        }
    }
    if s_options.simulate != 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b"\nNo output: simulation mode.\n\0" as *const u8 as *const libc::c_char);
        return;
    }
    if new_outfile != 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"\nOutput file: %s\n\0" as *const u8 as *const libc::c_char,
            outfile_name,
        );
        if !(s_options.dir_name).is_null() {
            opng_os_create_dir(s_options.dir_name);
        }
        has_backup = 0 as libc::c_int;
        if opng_os_test_file_access(
            outfile_name,
            b"e\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {
            if opng_os_rename(outfile_name, bakfile_name, s_options.clobber)
                != 0 as libc::c_int
            {
                opng_throw_error(
                    b"Can't back up the output file\0" as *const u8
                        as *const libc::c_char,
                );
            }
            has_backup = 1 as libc::c_int;
        }
    } else {
        if opng_os_rename(infile_name_local, bakfile_name, s_options.clobber)
            != 0 as libc::c_int
        {
            opng_throw_error(
                b"Can't back up the input file\0" as *const u8 as *const libc::c_char,
            );
        }
        has_backup = 1 as libc::c_int;
    }
    outfile = fopen(outfile_name, b"wb\0" as *const u8 as *const libc::c_char);
    let mut exception__prev_0: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env_0: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev_0[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh10 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh10 = &mut exception__env_0;
    if _setjmp(exception__env_0.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            if outfile.is_null() {
                opng_throw_error(
                    b"Can't open the output file\0" as *const u8 as *const libc::c_char,
                );
            }
            if s_process.status & OUTPUT_NEEDS_NEW_IDAT as libc::c_int as libc::c_uint
                != 0
            {
                opng_write_file(
                    outfile,
                    s_process.best_compr_level,
                    s_process.best_mem_level,
                    s_process.best_strategy,
                    s_process.best_filter,
                );
            } else {
                infile = fopen(
                    if new_outfile != 0 { infile_name_local } else { bakfile_name },
                    b"rb\0" as *const u8 as *const libc::c_char,
                );
                if infile.is_null() {
                    opng_throw_error(
                        b"Can't reopen the input file\0" as *const u8
                            as *const libc::c_char,
                    );
                }
                let mut exception__prev_1: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
                let mut exception__env_1: jmp_buf = [__jmp_buf_tag {
                    __jmpbuf: [0; 8],
                    __mask_was_saved: 0,
                    __saved_mask: __sigset_t { __val: [0; 16] },
                }; 1];
                exception__prev_1[0 as libc::c_int
                    as usize] = (*the_exception_context.as_mut_ptr()).penv;
                let ref mut fresh11 = (*the_exception_context.as_mut_ptr()).penv;
                *fresh11 = &mut exception__env_1;
                if _setjmp(exception__env_1.as_mut_ptr()) == 0 as libc::c_int {
                    loop {
                        if s_process.in_datastream_offset
                            > 0 as libc::c_int as opng_foffset_t
                            && opng_fseeko(
                                infile,
                                s_process.in_datastream_offset,
                                0 as libc::c_int,
                            ) != 0 as libc::c_int
                        {
                            opng_throw_error(
                                b"Can't reposition the input file\0" as *const u8
                                    as *const libc::c_char,
                            );
                        }
                        s_process.best_idat_size = s_process.in_idat_size;
                        opng_copy_file(infile, outfile);
                        (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
                        if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                            break;
                        }
                    }
                } else {
                    (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
                }
                let ref mut fresh12 = (*the_exception_context.as_mut_ptr()).penv;
                *fresh12 = exception__prev_1[0 as libc::c_int as usize];
                if !((*the_exception_context.as_mut_ptr()).caught == 0
                    || {
                        ::core::ptr::write_volatile(
                            &mut status as *mut opng_status_t,
                            (*the_exception_context.as_mut_ptr()).v.etmp,
                        );
                        0 as libc::c_int != 0
                    })
                {
                    if !(status as libc::c_int != OPNG_STATUS_OK as libc::c_int) {
                        usr_panic
                            .expect(
                                "non-null function pointer",
                            )(
                            b"opng_copy_file should throw errors only\0" as *const u8
                                as *const libc::c_char,
                        );
                    }
                }
                fclose(infile);
                if status as libc::c_int != OPNG_STATUS_OK as libc::c_int {
                    loop {
                        ::core::ptr::write_volatile(
                            &mut (*the_exception_context.as_mut_ptr()).v.etmp
                                as *mut opng_status_t,
                            status,
                        );
                        longjmp(
                            (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                            1 as libc::c_int,
                        );
                    }
                }
            }
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh13 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh13 = exception__prev_0[0 as libc::c_int as usize];
    if (*the_exception_context.as_mut_ptr()).caught == 0
        || {
            ::core::ptr::write_volatile(
                &mut status as *mut opng_status_t,
                (*the_exception_context.as_mut_ptr()).v.etmp,
            );
            0 as libc::c_int != 0
        }
    {} else {
        if !outfile.is_null() {
            fclose(outfile);
        }
        if has_backup != 0 {
            if opng_os_rename(
                bakfile_name,
                (if new_outfile != 0 { outfile_name } else { infile_name_local }),
                1 as libc::c_int,
            ) != 0 as libc::c_int
            {
                opng_print_warning(
                    b"Can't recover the original file from backup\0" as *const u8
                        as *const libc::c_char,
                );
            }
        } else {
            if new_outfile == 0 {
                usr_panic
                    .expect(
                        "non-null function pointer",
                    )(
                    b"Overwrote input with no temporary backup\0" as *const u8
                        as *const libc::c_char,
                );
            }
            if opng_os_unlink(outfile_name) != 0 as libc::c_int {
                opng_print_warning(
                    b"Can't remove the broken output file\0" as *const u8
                        as *const libc::c_char,
                );
            }
        }
        loop {
            ::core::ptr::write_volatile(
                &mut (*the_exception_context.as_mut_ptr()).v.etmp as *mut opng_status_t,
                status,
            );
            longjmp(
                (*(*the_exception_context.as_mut_ptr()).penv).as_mut_ptr(),
                1 as libc::c_int,
            );
        }
    }
    fclose(outfile);
    if s_options.preserve != 0 {
        opng_os_copy_file_attr(
            if new_outfile != 0 { infile_name_local } else { bakfile_name },
            outfile_name,
        );
    }
    if s_options.backup == 0 && new_outfile == 0 {
        if opng_os_unlink(bakfile_name) != 0 as libc::c_int {
            opng_print_warning(
                b"Can't remove the backup file\0" as *const u8 as *const libc::c_char,
            );
        }
    }
    usr_printf
        .expect(
            "non-null function pointer",
        )(
        b"\nOutput IDAT size = %lu bytes\0" as *const u8 as *const libc::c_char,
        s_process.out_idat_size,
    );
    if s_process.status & INPUT_HAS_PNG_DATASTREAM as libc::c_int as libc::c_uint != 0 {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b" (\0" as *const u8 as *const libc::c_char);
        opng_print_fsize_difference(
            s_process.in_idat_size,
            s_process.out_idat_size,
            0 as libc::c_int,
        );
        usr_printf
            .expect(
                "non-null function pointer",
            )(b")\0" as *const u8 as *const libc::c_char);
    }
    usr_printf
        .expect(
            "non-null function pointer",
        )(
        b"\nOutput file size = %lu bytes (\0" as *const u8 as *const libc::c_char,
        s_process.out_file_size,
    );
    opng_print_fsize_difference(
        s_process.in_file_size,
        s_process.out_file_size,
        1 as libc::c_int,
    );
    usr_printf
        .expect(
            "non-null function pointer",
        )(b")\n\0" as *const u8 as *const libc::c_char);
}
#[no_mangle]
pub unsafe extern "C" fn opng_initialize(
    mut init_options: *const opng_options,
    mut init_ui: *const opng_ui,
) -> libc::c_int {
    usr_printf = (*init_ui).printf_fn;
    usr_print_cntrl = (*init_ui).print_cntrl_fn;
    usr_progress = (*init_ui).progress_fn;
    usr_panic = (*init_ui).panic_fn;
    if usr_printf.is_none() || usr_print_cntrl.is_none() || usr_progress.is_none()
        || usr_panic.is_none()
    {
        return -(1 as libc::c_int);
    }
    s_options = *init_options;
    if s_options.optim_level == 0 as libc::c_int {
        s_options.np = 1 as libc::c_int;
        s_options.nc = s_options.np;
        s_options.nb = s_options.nc;
        s_options.nz = 1 as libc::c_int;
    }
    memset(
        &mut s_summary as *mut opng_summary_struct as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<opng_summary_struct>() as libc::c_ulong,
    );
    s_engine.started = 1 as libc::c_int;
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opng_optimize(
    mut infile_name: *const libc::c_char,
) -> libc::c_int {
    let mut status: opng_status_t = OPNG_STATUS_OK;
    let mut result: libc::c_int = 0;
    if s_engine.started == 0 {
        usr_panic
            .expect(
                "non-null function pointer",
            )(
            b"The OptiPNG engine is not running\0" as *const u8 as *const libc::c_char,
        );
    }
    usr_printf
        .expect(
            "non-null function pointer",
        )(b"** Processing: %s\n\0" as *const u8 as *const libc::c_char, infile_name);
    s_summary.file_count = (s_summary.file_count).wrapping_add(1);
    s_summary.file_count;
    opng_clear_image_info();
    let mut exception__prev: [*mut jmp_buf; 1] = [0 as *mut jmp_buf; 1];
    let mut exception__env: jmp_buf = [__jmp_buf_tag {
        __jmpbuf: [0; 8],
        __mask_was_saved: 0,
        __saved_mask: __sigset_t { __val: [0; 16] },
    }; 1];
    exception__prev[0 as libc::c_int
        as usize] = (*the_exception_context.as_mut_ptr()).penv;
    let ref mut fresh14 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh14 = &mut exception__env;
    if _setjmp(exception__env.as_mut_ptr()) == 0 as libc::c_int {
        loop {
            opng_optimize_impl(infile_name);
            if s_process.status & INPUT_HAS_ERRORS as libc::c_int as libc::c_uint != 0 {
                s_summary.err_count = (s_summary.err_count).wrapping_add(1);
                s_summary.err_count;
                s_summary.fix_count = (s_summary.fix_count).wrapping_add(1);
                s_summary.fix_count;
            }
            if s_process.status
                & INPUT_HAS_MULTIPLE_IMAGES as libc::c_int as libc::c_uint != 0
            {
                if s_options.snip != 0 {
                    s_summary.snip_count = (s_summary.snip_count).wrapping_add(1);
                    s_summary.snip_count;
                }
            }
            ::core::ptr::write_volatile(
                &mut result as *mut libc::c_int,
                0 as libc::c_int,
            );
            (*the_exception_context.as_mut_ptr()).caught = 0 as libc::c_int;
            if !((*the_exception_context.as_mut_ptr()).caught != 0) {
                break;
            }
        }
    } else {
        (*the_exception_context.as_mut_ptr()).caught = 1 as libc::c_int;
    }
    let ref mut fresh15 = (*the_exception_context.as_mut_ptr()).penv;
    *fresh15 = exception__prev[0 as libc::c_int as usize];
    if !((*the_exception_context.as_mut_ptr()).caught == 0
        || {
            status = (*the_exception_context.as_mut_ptr()).v.etmp;
            0 as libc::c_int != 0
        })
    {
        if !(status as libc::c_int != OPNG_STATUS_OK as libc::c_int) {
            usr_panic
                .expect(
                    "non-null function pointer",
                )(
                b"opng_optimize_impl should throw errors only\0" as *const u8
                    as *const libc::c_char,
            );
        }
        s_summary.err_count = (s_summary.err_count).wrapping_add(1);
        s_summary.err_count;
        ::core::ptr::write_volatile(
            &mut result as *mut libc::c_int,
            -(1 as libc::c_int),
        );
    }
    opng_destroy_image_info();
    usr_printf
        .expect(
            "non-null function pointer",
        )(b"\n\0" as *const u8 as *const libc::c_char);
    return result;
}
#[no_mangle]
pub unsafe extern "C" fn opng_finalize() -> libc::c_int {
    if s_options.verbose != 0 || s_summary.snip_count > 0 as libc::c_int as libc::c_uint
        || s_summary.err_count > 0 as libc::c_int as libc::c_uint
    {
        usr_printf
            .expect(
                "non-null function pointer",
            )(b"** Status report\n\0" as *const u8 as *const libc::c_char);
        usr_printf
            .expect(
                "non-null function pointer",
            )(
            b"%u file(s) have been processed.\n\0" as *const u8 as *const libc::c_char,
            s_summary.file_count,
        );
        if s_summary.snip_count > 0 as libc::c_int as libc::c_uint {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"%u multi-image file(s) have been snipped.\n\0" as *const u8
                    as *const libc::c_char,
                s_summary.snip_count,
            );
        }
        if s_summary.err_count > 0 as libc::c_int as libc::c_uint {
            usr_printf
                .expect(
                    "non-null function pointer",
                )(
                b"%u error(s) have been encountered.\n\0" as *const u8
                    as *const libc::c_char,
                s_summary.err_count,
            );
            if s_summary.fix_count > 0 as libc::c_int as libc::c_uint {
                usr_printf
                    .expect(
                        "non-null function pointer",
                    )(
                    b"%u erroneous file(s) have been fixed.\n\0" as *const u8
                        as *const libc::c_char,
                    s_summary.fix_count,
                );
            }
        }
    }
    s_engine.started = 0 as libc::c_int;
    return 0 as libc::c_int;
}
