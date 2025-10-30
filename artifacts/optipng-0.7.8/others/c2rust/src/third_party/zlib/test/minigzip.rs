use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn unlink(__name: *const libc::c_char) -> libc::c_int;
    fn gzdopen(fd: libc::c_int, mode: *const libc::c_char) -> gzFile;
    fn gzread(file: gzFile, buf: voidp, len: libc::c_uint) -> libc::c_int;
    fn gzwrite(file: gzFile, buf: voidpc, len: libc::c_uint) -> libc::c_int;
    fn gzclose(file: gzFile) -> libc::c_int;
    fn gzerror(file: gzFile, errnum: *mut libc::c_int) -> *const libc::c_char;
    fn gzopen64(_: *const libc::c_char, _: *const libc::c_char) -> gzFile;
    static mut stdin: *mut FILE;
    static mut stdout: *mut FILE;
    static mut stderr: *mut FILE;
    fn fclose(__stream: *mut FILE) -> libc::c_int;
    fn fopen(_: *const libc::c_char, _: *const libc::c_char) -> *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn snprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ...
    ) -> libc::c_int;
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
    fn ferror(__stream: *mut FILE) -> libc::c_int;
    fn perror(__s: *const libc::c_char);
    fn fileno(__stream: *mut FILE) -> libc::c_int;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strrchr(_: *const libc::c_char, _: libc::c_int) -> *mut libc::c_char;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn exit(_: libc::c_int) -> !;
}
pub type size_t = libc::c_ulong;
pub type z_size_t = size_t;
pub type voidpc = *const libc::c_void;
pub type voidp = *mut libc::c_void;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type off64_t = __off64_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct gzFile_s {
    pub have: libc::c_uint,
    pub next: *mut libc::c_uchar,
    pub pos: off64_t,
}
pub type gzFile = *mut gzFile_s;
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
static mut prog: *mut libc::c_char = 0 as *const libc::c_char as *mut libc::c_char;
#[no_mangle]
pub unsafe extern "C" fn error(mut msg: *const libc::c_char) {
    fprintf(stderr, b"%s: %s\n\0" as *const u8 as *const libc::c_char, prog, msg);
    exit(1 as libc::c_int);
}
#[no_mangle]
pub unsafe extern "C" fn gz_compress(mut in_0: *mut FILE, mut out: gzFile) {
    let mut buf: [libc::c_char; 16384] = [0; 16384];
    let mut len: libc::c_int = 0;
    let mut err: libc::c_int = 0;
    loop {
        len = fread(
            buf.as_mut_ptr() as *mut libc::c_void,
            1 as libc::c_int as libc::c_ulong,
            ::core::mem::size_of::<[libc::c_char; 16384]>() as libc::c_ulong,
            in_0,
        ) as libc::c_int;
        if ferror(in_0) != 0 {
            perror(b"fread\0" as *const u8 as *const libc::c_char);
            exit(1 as libc::c_int);
        }
        if len == 0 as libc::c_int {
            break;
        }
        if gzwrite(out, buf.as_mut_ptr() as voidpc, len as libc::c_uint) != len {
            error(gzerror(out, &mut err));
        }
    }
    fclose(in_0);
    if gzclose(out) != 0 as libc::c_int {
        error(b"failed gzclose\0" as *const u8 as *const libc::c_char);
    }
}
#[no_mangle]
pub unsafe extern "C" fn gz_uncompress(mut in_0: gzFile, mut out: *mut FILE) {
    let mut buf: [libc::c_char; 16384] = [0; 16384];
    let mut len: libc::c_int = 0;
    let mut err: libc::c_int = 0;
    loop {
        len = gzread(
            in_0,
            buf.as_mut_ptr() as voidp,
            ::core::mem::size_of::<[libc::c_char; 16384]>() as libc::c_ulong
                as libc::c_uint,
        );
        if len < 0 as libc::c_int {
            error(gzerror(in_0, &mut err));
        }
        if len == 0 as libc::c_int {
            break;
        }
        if fwrite(
            buf.as_mut_ptr() as *const libc::c_void,
            1 as libc::c_int as libc::c_ulong,
            len as libc::c_uint as libc::c_ulong,
            out,
        ) as libc::c_int != len
        {
            error(b"failed fwrite\0" as *const u8 as *const libc::c_char);
        }
    }
    if fclose(out) != 0 {
        error(b"failed fclose\0" as *const u8 as *const libc::c_char);
    }
    if gzclose(in_0) != 0 as libc::c_int {
        error(b"failed gzclose\0" as *const u8 as *const libc::c_char);
    }
}
#[no_mangle]
pub unsafe extern "C" fn file_compress(
    mut file: *mut libc::c_char,
    mut mode: *mut libc::c_char,
) {
    let mut outfile: [libc::c_char; 1024] = [0; 1024];
    let mut in_0: *mut FILE = 0 as *mut FILE;
    let mut out: gzFile = 0 as *mut gzFile_s;
    if (strlen(file)).wrapping_add(strlen(b".gz\0" as *const u8 as *const libc::c_char))
        >= ::core::mem::size_of::<[libc::c_char; 1024]>() as libc::c_ulong
    {
        fprintf(
            stderr,
            b"%s: filename too long\n\0" as *const u8 as *const libc::c_char,
            prog,
        );
        exit(1 as libc::c_int);
    }
    snprintf(
        outfile.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 1024]>() as libc::c_ulong,
        b"%s%s\0" as *const u8 as *const libc::c_char,
        file,
        b".gz\0" as *const u8 as *const libc::c_char,
    );
    in_0 = fopen(file, b"rb\0" as *const u8 as *const libc::c_char);
    if in_0.is_null() {
        perror(file);
        exit(1 as libc::c_int);
    }
    out = gzopen64(outfile.as_mut_ptr(), mode);
    if out.is_null() {
        fprintf(
            stderr,
            b"%s: can't gzopen %s\n\0" as *const u8 as *const libc::c_char,
            prog,
            outfile.as_mut_ptr(),
        );
        exit(1 as libc::c_int);
    }
    gz_compress(in_0, out);
    unlink(file);
}
#[no_mangle]
pub unsafe extern "C" fn file_uncompress(mut file: *mut libc::c_char) {
    let mut buf: [libc::c_char; 1024] = [0; 1024];
    let mut infile: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut outfile: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut out: *mut FILE = 0 as *mut FILE;
    let mut in_0: gzFile = 0 as *mut gzFile_s;
    let mut len: z_size_t = strlen(file);
    if len.wrapping_add(strlen(b".gz\0" as *const u8 as *const libc::c_char))
        >= ::core::mem::size_of::<[libc::c_char; 1024]>() as libc::c_ulong
    {
        fprintf(
            stderr,
            b"%s: filename too long\n\0" as *const u8 as *const libc::c_char,
            prog,
        );
        exit(1 as libc::c_int);
    }
    snprintf(
        buf.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 1024]>() as libc::c_ulong,
        b"%s\0" as *const u8 as *const libc::c_char,
        file,
    );
    if len
        > (::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong)
        && strcmp(
            file
                .offset(len as isize)
                .offset(
                    -((::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
                        .wrapping_sub(1 as libc::c_int as libc::c_ulong) as isize),
                ),
            b".gz\0" as *const u8 as *const libc::c_char,
        ) == 0 as libc::c_int
    {
        infile = file;
        outfile = buf.as_mut_ptr();
        *outfile
            .offset(
                len.wrapping_sub(3 as libc::c_int as z_size_t) as isize,
            ) = '\0' as i32 as libc::c_char;
    } else {
        outfile = file;
        infile = buf.as_mut_ptr();
        snprintf(
            buf.as_mut_ptr().offset(len as isize),
            (::core::mem::size_of::<[libc::c_char; 1024]>() as libc::c_ulong)
                .wrapping_sub(len),
            b"%s\0" as *const u8 as *const libc::c_char,
            b".gz\0" as *const u8 as *const libc::c_char,
        );
    }
    in_0 = gzopen64(infile, b"rb\0" as *const u8 as *const libc::c_char);
    if in_0.is_null() {
        fprintf(
            stderr,
            b"%s: can't gzopen %s\n\0" as *const u8 as *const libc::c_char,
            prog,
            infile,
        );
        exit(1 as libc::c_int);
    }
    out = fopen(outfile, b"wb\0" as *const u8 as *const libc::c_char);
    if out.is_null() {
        perror(file);
        exit(1 as libc::c_int);
    }
    gz_uncompress(in_0, out);
    unlink(infile);
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut copyout: libc::c_int = 0 as libc::c_int;
    let mut uncompr: libc::c_int = 0 as libc::c_int;
    let mut file: gzFile = 0 as *mut gzFile_s;
    let mut bname: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut outmode: [libc::c_char; 20] = [0; 20];
    snprintf(
        outmode.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 20]>() as libc::c_ulong,
        b"%s\0" as *const u8 as *const libc::c_char,
        b"wb6 \0" as *const u8 as *const libc::c_char,
    );
    prog = *argv.offset(0 as libc::c_int as isize);
    bname = strrchr(*argv.offset(0 as libc::c_int as isize), '/' as i32);
    if !bname.is_null() {
        bname = bname.offset(1);
        bname;
    } else {
        bname = *argv.offset(0 as libc::c_int as isize);
    }
    argc -= 1;
    argc;
    argv = argv.offset(1);
    argv;
    if strcmp(bname, b"gunzip\0" as *const u8 as *const libc::c_char) == 0 {
        uncompr = 1 as libc::c_int;
    } else if strcmp(bname, b"zcat\0" as *const u8 as *const libc::c_char) == 0 {
        uncompr = 1 as libc::c_int;
        copyout = uncompr;
    }
    while argc > 0 as libc::c_int {
        if strcmp(*argv, b"-c\0" as *const u8 as *const libc::c_char) == 0 as libc::c_int
        {
            copyout = 1 as libc::c_int;
        } else if strcmp(*argv, b"-d\0" as *const u8 as *const libc::c_char)
            == 0 as libc::c_int
        {
            uncompr = 1 as libc::c_int;
        } else if strcmp(*argv, b"-f\0" as *const u8 as *const libc::c_char)
            == 0 as libc::c_int
        {
            outmode[3 as libc::c_int as usize] = 'f' as i32 as libc::c_char;
        } else if strcmp(*argv, b"-h\0" as *const u8 as *const libc::c_char)
            == 0 as libc::c_int
        {
            outmode[3 as libc::c_int as usize] = 'h' as i32 as libc::c_char;
        } else if strcmp(*argv, b"-r\0" as *const u8 as *const libc::c_char)
            == 0 as libc::c_int
        {
            outmode[3 as libc::c_int as usize] = 'R' as i32 as libc::c_char;
        } else {
            if !(*(*argv).offset(0 as libc::c_int as isize) as libc::c_int == '-' as i32
                && *(*argv).offset(1 as libc::c_int as isize) as libc::c_int
                    >= '1' as i32
                && *(*argv).offset(1 as libc::c_int as isize) as libc::c_int
                    <= '9' as i32
                && *(*argv).offset(2 as libc::c_int as isize) as libc::c_int
                    == 0 as libc::c_int)
            {
                break;
            }
            outmode[2 as libc::c_int
                as usize] = *(*argv).offset(1 as libc::c_int as isize);
        }
        argc -= 1;
        argc;
        argv = argv.offset(1);
        argv;
    }
    if outmode[3 as libc::c_int as usize] as libc::c_int == ' ' as i32 {
        outmode[3 as libc::c_int as usize] = 0 as libc::c_int as libc::c_char;
    }
    if argc == 0 as libc::c_int {
        if uncompr != 0 {
            file = gzdopen(fileno(stdin), b"rb\0" as *const u8 as *const libc::c_char);
            if file.is_null() {
                error(b"can't gzdopen stdin\0" as *const u8 as *const libc::c_char);
            }
            gz_uncompress(file, stdout);
        } else {
            file = gzdopen(fileno(stdout), outmode.as_mut_ptr());
            if file.is_null() {
                error(b"can't gzdopen stdout\0" as *const u8 as *const libc::c_char);
            }
            gz_compress(stdin, file);
        }
    } else {
        copyout != 0;
        loop {
            if uncompr != 0 {
                if copyout != 0 {
                    file = gzopen64(*argv, b"rb\0" as *const u8 as *const libc::c_char);
                    if file.is_null() {
                        fprintf(
                            stderr,
                            b"%s: can't gzopen %s\n\0" as *const u8
                                as *const libc::c_char,
                            prog,
                            *argv,
                        );
                    } else {
                        gz_uncompress(file, stdout);
                    }
                } else {
                    file_uncompress(*argv);
                }
            } else if copyout != 0 {
                let mut in_0: *mut FILE = fopen(
                    *argv,
                    b"rb\0" as *const u8 as *const libc::c_char,
                );
                if in_0.is_null() {
                    perror(*argv);
                } else {
                    file = gzdopen(fileno(stdout), outmode.as_mut_ptr());
                    if file.is_null() {
                        error(
                            b"can't gzdopen stdout\0" as *const u8 as *const libc::c_char,
                        );
                    }
                    gz_compress(in_0, file);
                }
            } else {
                file_compress(*argv, outmode.as_mut_ptr());
            }
            argv = argv.offset(1);
            argv;
            argc -= 1;
            if !(argc != 0) {
                break;
            }
        }
    }
    return 0 as libc::c_int;
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
