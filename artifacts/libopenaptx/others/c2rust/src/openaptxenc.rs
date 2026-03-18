use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    pub type aptx_context;
    static mut stdin: *mut FILE;
    static mut stdout: *mut FILE;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
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
    fn feof(__stream: *mut FILE) -> libc::c_int;
    fn ferror(__stream: *mut FILE) -> libc::c_int;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    static aptx_major: libc::c_int;
    static aptx_minor: libc::c_int;
    static aptx_patch: libc::c_int;
    fn aptx_init(hd: libc::c_int) -> *mut aptx_context;
    fn aptx_finish(ctx: *mut aptx_context);
    fn aptx_encode(
        ctx: *mut aptx_context,
        input: *const libc::c_uchar,
        input_size: size_t,
        output: *mut libc::c_uchar,
        output_size: size_t,
        written: *mut size_t,
    ) -> size_t;
    fn aptx_encode_finish(
        ctx: *mut aptx_context,
        output: *mut libc::c_uchar,
        output_size: size_t,
        written: *mut size_t,
    ) -> libc::c_int;
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
static mut input_buffer: [libc::c_uchar; 12288] = [0; 12288];
static mut output_buffer: [libc::c_uchar; 3072] = [0; 3072];
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut i: libc::c_int = 0;
    let mut hd: libc::c_int = 0;
    let mut ret: libc::c_int = 0;
    let mut length: size_t = 0;
    let mut processed: size_t = 0;
    let mut written: size_t = 0;
    let mut ctx: *mut aptx_context = 0 as *mut aptx_context;
    hd = 0 as libc::c_int;
    i = 1 as libc::c_int;
    while i < argc {
        if strcmp(*argv.offset(i as isize), b"-h\0" as *const u8 as *const libc::c_char)
            == 0 as libc::c_int
            || strcmp(
                *argv.offset(i as isize),
                b"--help\0" as *const u8 as *const libc::c_char,
            ) == 0 as libc::c_int
        {
            fprintf(
                stderr,
                b"aptX encoder utility %d.%d.%d (using libopenaptx %d.%d.%d)\n\0"
                    as *const u8 as *const libc::c_char,
                0 as libc::c_int,
                2 as libc::c_int,
                1 as libc::c_int,
                aptx_major,
                aptx_minor,
                aptx_patch,
            );
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(
                stderr,
                b"This utility encodes a raw 24 bit signed stereo\n\0" as *const u8
                    as *const libc::c_char,
            );
            fprintf(
                stderr,
                b"samples from stdin to aptX or aptX HD on stdout\n\0" as *const u8
                    as *const libc::c_char,
            );
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(stderr, b"Usage:\n\0" as *const u8 as *const libc::c_char);
            fprintf(
                stderr,
                b"        %s [options]\n\0" as *const u8 as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(stderr, b"Options:\n\0" as *const u8 as *const libc::c_char);
            fprintf(
                stderr,
                b"        -h, --help   Display this help\n\0" as *const u8
                    as *const libc::c_char,
            );
            fprintf(
                stderr,
                b"        --hd         Encode to aptX HD\n\0" as *const u8
                    as *const libc::c_char,
            );
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(stderr, b"Examples:\n\0" as *const u8 as *const libc::c_char);
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(
                stderr,
                b"        %s < sample.s24le > sample.aptx\n\0" as *const u8
                    as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(
                stderr,
                b"        %s --hd < sample.s24le > sample.aptxhd\n\0" as *const u8
                    as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            fprintf(stderr, b"\n\0" as *const u8 as *const libc::c_char);
            fprintf(
                stderr,
                b"        sox sample.wav -t raw -r 44.1k -L -e s -b 24 -c 2 - | %s > sample.aptx\n\0"
                    as *const u8 as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            return 1 as libc::c_int;
        } else if strcmp(
            *argv.offset(i as isize),
            b"--hd\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
        {
            hd = 1 as libc::c_int;
        } else {
            fprintf(
                stderr,
                b"%s: Invalid option %s\n\0" as *const u8 as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
                *argv.offset(i as isize),
            );
            return 1 as libc::c_int;
        }
        i += 1;
        i;
    }
    ctx = aptx_init(hd);
    if ctx.is_null() {
        fprintf(
            stderr,
            b"%s: Cannot initialize aptX encoder\n\0" as *const u8
                as *const libc::c_char,
            *argv.offset(0 as libc::c_int as isize),
        );
        return 1 as libc::c_int;
    }
    ret = 0 as libc::c_int;
    while feof(stdin) == 0 {
        length = fread(
            input_buffer.as_mut_ptr() as *mut libc::c_void,
            1 as libc::c_int as libc::c_ulong,
            ::core::mem::size_of::<[libc::c_uchar; 12288]>() as libc::c_ulong,
            stdin,
        );
        if ferror(stdin) != 0 {
            fprintf(
                stderr,
                b"%s: aptX encoding failed to read input data\n\0" as *const u8
                    as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            ret = 1 as libc::c_int;
        }
        if length == 0 as libc::c_int as size_t {
            break;
        }
        processed = aptx_encode(
            ctx,
            input_buffer.as_mut_ptr(),
            length,
            output_buffer.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_uchar; 3072]>() as libc::c_ulong,
            &mut written,
        );
        if processed != length {
            fprintf(
                stderr,
                b"%s: aptX encoding stopped in the middle of the sample, dropped %lu byte%s\n\0"
                    as *const u8 as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
                length.wrapping_sub(processed),
                if length.wrapping_sub(processed) != 1 as libc::c_int as size_t {
                    b"s\0" as *const u8 as *const libc::c_char
                } else {
                    b"\0" as *const u8 as *const libc::c_char
                },
            );
            ret = 1 as libc::c_int;
        }
        if fwrite(
            output_buffer.as_mut_ptr() as *const libc::c_void,
            1 as libc::c_int as libc::c_ulong,
            written,
            stdout,
        ) != written
        {
            fprintf(
                stderr,
                b"%s: aptX encoding failed to write encoded data\n\0" as *const u8
                    as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            ret = 1 as libc::c_int;
            break;
        } else if processed != length {
            break;
        }
    }
    if aptx_encode_finish(
        ctx,
        output_buffer.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_uchar; 3072]>() as libc::c_ulong,
        &mut written,
    ) != 0
    {
        if fwrite(
            output_buffer.as_mut_ptr() as *const libc::c_void,
            1 as libc::c_int as libc::c_ulong,
            written,
            stdout,
        ) != written
        {
            fprintf(
                stderr,
                b"%s: aptX encoding failed to write encoded data\n\0" as *const u8
                    as *const libc::c_char,
                *argv.offset(0 as libc::c_int as isize),
            );
            ret = 1 as libc::c_int;
        }
    }
    aptx_finish(ctx);
    return ret;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in ::std::env::args() {
        args.push(
            (::std::ffi::CString::new(arg))
                .expect("Failed to convert argument into CString.")
                .into_raw(),
        );
    }
    args.push(::core::ptr::null_mut());
    unsafe {
        ::std::process::exit(
            main_0(
                (args.len() - 1) as libc::c_int,
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
