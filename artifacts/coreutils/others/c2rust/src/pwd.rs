#![allow(dead_code, mutable_transmutes, non_camel_case_types, non_snake_case, non_upper_case_globals, unused_assignments, unused_mut, unused_imports)]
#![feature(extern_types)]
use ::rust::*;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    pub type __dirstream;
    fn getopt_long(
        ___argc: libc::c_int,
        ___argv: *const *mut libc::c_char,
        __shortopts: *const libc::c_char,
        __longopts: *const option,
        __longind: *mut libc::c_int,
    ) -> libc::c_int;
    static mut optind: libc::c_int;
    static mut stdout: *mut FILE;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn puts(__s: *const libc::c_char) -> libc::c_int;
    fn fputs_unlocked(__s: *const libc::c_char, __stream: *mut FILE) -> libc::c_int;
    fn chdir(__path: *const libc::c_char) -> libc::c_int;
    fn fchdir(__fd: libc::c_int) -> libc::c_int;
    fn lstat(__file: *const libc::c_char, __buf: *mut stat) -> libc::c_int;
    fn fstat(__fd: libc::c_int, __buf: *mut stat) -> libc::c_int;
    fn stat(__file: *const libc::c_char, __buf: *mut stat) -> libc::c_int;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn strncmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn strstr(_: *const libc::c_char, _: *const libc::c_char) -> *mut libc::c_char;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn free(_: *mut libc::c_void);
    fn __errno_location() -> *mut libc::c_int;
    fn quotearg_style(s: quoting_style, arg: *const libc::c_char) -> *mut libc::c_char;
    fn error(
        __status: libc::c_int,
        __errnum: libc::c_int,
        __format: *const libc::c_char,
        _: ...
    );
    fn set_program_name(argv0: *const libc::c_char);
    static mut program_name: *const libc::c_char;
    fn proper_name_lite(
        name_ascii: *const libc::c_char,
        name_utf8: *const libc::c_char,
    ) -> *const libc::c_char;
    fn version_etc(
        stream: *mut FILE,
        command_name: *const libc::c_char,
        package: *const libc::c_char,
        version: *const libc::c_char,
        _: ...
    );
    fn close_stdout();
    static mut Version: *const libc::c_char;
    fn opendir(__name: *const libc::c_char) -> *mut DIR;
    fn closedir(__dirp: *mut DIR) -> libc::c_int;
    fn readdir(__dirp: *mut DIR) -> *mut dirent;
    fn dirfd(__dirp: *mut DIR) -> libc::c_int;
    fn setlocale(
        __category: libc::c_int,
        __locale: *const libc::c_char,
    ) -> *mut libc::c_char;
    fn gettext(__msgid: *const libc::c_char) -> *mut libc::c_char;
    fn textdomain(__domainname: *const libc::c_char) -> *mut libc::c_char;
    fn bindtextdomain(
        __domainname: *const libc::c_char,
        __dirname: *const libc::c_char,
    ) -> *mut libc::c_char;
    fn xmalloc(s: size_t) -> *mut libc::c_void;
    fn xnmalloc(n: size_t, s: size_t) -> *mut libc::c_void;
    fn getenv(__name: *const libc::c_char) -> *mut libc::c_char;
    fn exit(_: libc::c_int) -> !;
    fn atexit(__func: Option::<unsafe extern "C" fn() -> ()>) -> libc::c_int;
    fn quote(arg: *const libc::c_char) -> *const libc::c_char;
    fn get_root_dev_ino(root_d_i: *mut dev_ino) -> *mut dev_ino;
    fn xgetcwd() -> *mut libc::c_char;
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct option {
    pub name: *const libc::c_char,
    pub has_arg: libc::c_int,
    pub flag: *mut libc::c_int,
    pub val: libc::c_int,
}
pub type size_t = libc::c_ulong;
pub type __dev_t = libc::c_ulong;
pub type __uid_t = libc::c_uint;
pub type __gid_t = libc::c_uint;
pub type __ino_t = libc::c_ulong;
pub type __mode_t = libc::c_uint;
pub type __nlink_t = libc::c_uint;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type __time_t = libc::c_long;
pub type __blksize_t = libc::c_int;
pub type __blkcnt_t = libc::c_long;
pub type __syscall_slong_t = libc::c_long;
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
pub type ino_t = __ino_t;
pub type dev_t = __dev_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct timespec {
    pub tv_sec: __time_t,
    pub tv_nsec: __syscall_slong_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct stat {
    pub st_dev: __dev_t,
    pub st_ino: __ino_t,
    pub st_mode: __mode_t,
    pub st_nlink: __nlink_t,
    pub st_uid: __uid_t,
    pub st_gid: __gid_t,
    pub st_rdev: __dev_t,
    pub __pad1: __dev_t,
    pub st_size: __off_t,
    pub st_blksize: __blksize_t,
    pub __pad2: libc::c_int,
    pub st_blocks: __blkcnt_t,
    pub st_atim: timespec,
    pub st_mtim: timespec,
    pub st_ctim: timespec,
    pub __glibc_reserved: [libc::c_int; 2],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct dirent {
    pub d_ino: __ino_t,
    pub d_off: __off_t,
    pub d_reclen: libc::c_ushort,
    pub d_type: libc::c_uchar,
    pub d_name: [libc::c_char; 256],
}
pub type DIR = __dirstream;
pub type C2RustUnnamed = libc::c_uint;
pub const NOT_AN_INODE_NUMBER: C2RustUnnamed = 0;
pub type C2RustUnnamed_0 = libc::c_int;
pub const GETOPT_VERSION_CHAR: C2RustUnnamed_0 = -3;
pub const GETOPT_HELP_CHAR: C2RustUnnamed_0 = -2;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct infomap {
    pub program: *const libc::c_char,
    pub node: *const libc::c_char,
}
pub type quoting_style = libc::c_uint;
pub const custom_quoting_style: quoting_style = 10;
pub const clocale_quoting_style: quoting_style = 9;
pub const locale_quoting_style: quoting_style = 8;
pub const escape_quoting_style: quoting_style = 7;
pub const c_maybe_quoting_style: quoting_style = 6;
pub const c_quoting_style: quoting_style = 5;
pub const shell_escape_always_quoting_style: quoting_style = 4;
pub const shell_escape_quoting_style: quoting_style = 3;
pub const shell_always_quoting_style: quoting_style = 2;
pub const shell_quoting_style: quoting_style = 1;
pub const literal_quoting_style: quoting_style = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct dev_ino {
    pub st_ino: ino_t,
    pub st_dev: dev_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct file_name {
    pub buf: *mut libc::c_char,
    pub n_alloc: size_t,
    pub start: *mut libc::c_char,
}
#[inline]
unsafe extern "C" fn emit_ancillary_info(mut program: *const libc::c_char) {
    let infomap_0: [infomap; 7] = [
        {
            let mut init = infomap {
                program: b"[\0" as *const u8 as *const libc::c_char,
                node: b"test invocation\0" as *const u8 as *const libc::c_char,
            };
            init
        },
        {
            let mut init = infomap {
                program: b"coreutils\0" as *const u8 as *const libc::c_char,
                node: b"Multi-call invocation\0" as *const u8 as *const libc::c_char,
            };
            init
        },
        {
            let mut init = infomap {
                program: b"sha224sum\0" as *const u8 as *const libc::c_char,
                node: b"sha2 utilities\0" as *const u8 as *const libc::c_char,
            };
            init
        },
        {
            let mut init = infomap {
                program: b"sha256sum\0" as *const u8 as *const libc::c_char,
                node: b"sha2 utilities\0" as *const u8 as *const libc::c_char,
            };
            init
        },
        {
            let mut init = infomap {
                program: b"sha384sum\0" as *const u8 as *const libc::c_char,
                node: b"sha2 utilities\0" as *const u8 as *const libc::c_char,
            };
            init
        },
        {
            let mut init = infomap {
                program: b"sha512sum\0" as *const u8 as *const libc::c_char,
                node: b"sha2 utilities\0" as *const u8 as *const libc::c_char,
            };
            init
        },
        {
            let mut init = infomap {
                program: 0 as *const libc::c_char,
                node: 0 as *const libc::c_char,
            };
            init
        },
    ];
    let mut node: *const libc::c_char = program;
    let mut map_prog: *const infomap = infomap_0.as_ptr();
    while !((*map_prog).program).is_null()
        && !(strcmp(program, (*map_prog).program) == 0 as libc::c_int)
    {
        map_prog = map_prog.offset(1);
        map_prog;
    }
    if !((*map_prog).node).is_null() {
        node = (*map_prog).node;
    }
    printf(
        gettext(b"\n%s online help: <%s>\n\0" as *const u8 as *const libc::c_char),
        b"GNU coreutils\0" as *const u8 as *const libc::c_char,
        b"https://www.gnu.org/software/coreutils/\0" as *const u8 as *const libc::c_char,
    );
    let mut lc_messages: *const libc::c_char = setlocale(
        5 as libc::c_int,
        0 as *const libc::c_char,
    );
    if !lc_messages.is_null()
        && strncmp(
            lc_messages,
            b"en_\0" as *const u8 as *const libc::c_char,
            (::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        ) != 0
    {
        fputs_unlocked(
            gettext(
                b"Report any translation bugs to <https://translationproject.org/team/>\n\0"
                    as *const u8 as *const libc::c_char,
            ),
            stdout,
        );
    }
    let mut url_program: *const libc::c_char = if strcmp(
        program,
        b"[\0" as *const u8 as *const libc::c_char,
    ) == 0 as libc::c_int
    {
        b"test\0" as *const u8 as *const libc::c_char
    } else {
        program
    };
    printf(
        gettext(b"Full documentation <%s%s>\n\0" as *const u8 as *const libc::c_char),
        b"https://www.gnu.org/software/coreutils/\0" as *const u8 as *const libc::c_char,
        url_program,
    );
    printf(
        gettext(
            b"or available locally via: info '(coreutils) %s%s'\n\0" as *const u8
                as *const libc::c_char,
        ),
        node,
        if node == program {
            b" invocation\0" as *const u8 as *const libc::c_char
        } else {
            b"\0" as *const u8 as *const libc::c_char
        },
    );
}
#[inline]
unsafe extern "C" fn readdir_ignoring_dot_and_dotdot(
    mut dirp: *mut DIR,
) -> *const dirent {
    loop {
        let mut dp: *const dirent = readdir(dirp);
        if dp.is_null() || !dot_or_dotdot(((*dp).d_name).as_ptr()) {
            return dp;
        }
    };
}
#[inline]
unsafe extern "C" fn dot_or_dotdot(mut file_name: *const libc::c_char) -> bool {
    if *file_name.offset(0 as libc::c_int as isize) as libc::c_int == '.' as i32 {
        let mut sep: libc::c_char = *file_name
            .offset(
                ((*file_name.offset(1 as libc::c_int as isize) as libc::c_int
                    == '.' as i32) as libc::c_int + 1 as libc::c_int) as isize,
            );
        return sep == 0 || sep as libc::c_int == '/' as i32;
    } else {
        return 0 as libc::c_int != 0
    };
}
#[inline]
unsafe extern "C" fn psame_inode(mut a: *const stat, mut b: *const stat) -> bool {
    return (*a).st_dev ^ (*b).st_dev | (*a).st_ino ^ (*b).st_ino == 0;
}
static mut longopts: [option; 5] = [
    {
        let mut init = option {
            name: b"logical\0" as *const u8 as *const libc::c_char,
            has_arg: 0 as libc::c_int,
            flag: 0 as *const libc::c_int as *mut libc::c_int,
            val: 'L' as i32,
        };
        init
    },
    {
        let mut init = option {
            name: b"physical\0" as *const u8 as *const libc::c_char,
            has_arg: 0 as libc::c_int,
            flag: 0 as *const libc::c_int as *mut libc::c_int,
            val: 'P' as i32,
        };
        init
    },
    {
        let mut init = option {
            name: b"help\0" as *const u8 as *const libc::c_char,
            has_arg: 0 as libc::c_int,
            flag: 0 as *const libc::c_int as *mut libc::c_int,
            val: GETOPT_HELP_CHAR as libc::c_int,
        };
        init
    },
    {
        let mut init = option {
            name: b"version\0" as *const u8 as *const libc::c_char,
            has_arg: 0 as libc::c_int,
            flag: 0 as *const libc::c_int as *mut libc::c_int,
            val: GETOPT_VERSION_CHAR as libc::c_int,
        };
        init
    },
    {
        let mut init = option {
            name: 0 as *const libc::c_char,
            has_arg: 0 as libc::c_int,
            flag: 0 as *const libc::c_int as *mut libc::c_int,
            val: 0 as libc::c_int,
        };
        init
    },
];
#[no_mangle]
pub unsafe extern "C" fn usage(mut status: libc::c_int) {
    if status != 0 as libc::c_int {
        fprintf(
            stderr,
            gettext(
                b"Try '%s --help' for more information.\n\0" as *const u8
                    as *const libc::c_char,
            ),
            program_name,
        );
    } else {
        printf(
            gettext(b"Usage: %s [OPTION]...\n\0" as *const u8 as *const libc::c_char),
            program_name,
        );
        fputs_unlocked(
            gettext(
                b"Print the full filename of the current working directory.\n\n\0"
                    as *const u8 as *const libc::c_char,
            ),
            stdout,
        );
        fputs_unlocked(
            gettext(
                b"  -L, --logical   use PWD from environment, even if it contains symlinks\n\0"
                    as *const u8 as *const libc::c_char,
            ),
            stdout,
        );
        fputs_unlocked(
            gettext(
                b"  -P, --physical  resolve all symlinks\n\0" as *const u8
                    as *const libc::c_char,
            ),
            stdout,
        );
        fputs_unlocked(
            gettext(
                b"      --help        display this help and exit\n\0" as *const u8
                    as *const libc::c_char,
            ),
            stdout,
        );
        fputs_unlocked(
            gettext(
                b"      --version     output version information and exit\n\0"
                    as *const u8 as *const libc::c_char,
            ),
            stdout,
        );
        fputs_unlocked(
            gettext(
                b"\nIf no option is specified, -P is assumed.\n\0" as *const u8
                    as *const libc::c_char,
            ),
            stdout,
        );
        printf(
            gettext(
                b"\nYour shell may have its own version of %s, which usually supersedes\nthe version described here.  Please refer to your shell's documentation\nfor details about the options it supports.\n\0"
                    as *const u8 as *const libc::c_char,
            ),
            b"pwd\0" as *const u8 as *const libc::c_char,
        );
        emit_ancillary_info(b"pwd\0" as *const u8 as *const libc::c_char);
    }
    exit(status);
}
unsafe extern "C" fn file_name_free(mut p: *mut file_name) {
    free((*p).buf as *mut libc::c_void);
    free(p as *mut libc::c_void);
}
unsafe extern "C" fn file_name_init() -> *mut file_name {
    let mut p: *mut file_name = xmalloc(
        ::core::mem::size_of::<file_name>() as libc::c_ulong,
    ) as *mut file_name;
    (*p)
        .n_alloc = (if (2 as libc::c_int * 4096 as libc::c_int)
        < 32 as libc::c_int * 1024 as libc::c_int
    {
        2 as libc::c_int * 4096 as libc::c_int
    } else {
        32 as libc::c_int * 1024 as libc::c_int
    }) as size_t;
    (*p).buf = xmalloc((*p).n_alloc) as *mut libc::c_char;
    (*p)
        .start = ((*p).buf)
        .offset(((*p).n_alloc).wrapping_sub(1 as libc::c_int as libc::c_ulong) as isize);
    *((*p).start).offset(0 as libc::c_int as isize) = '\0' as i32 as libc::c_char;
    return p;
}
unsafe extern "C" fn file_name_prepend(
    mut p: *mut file_name,
    mut s: *const libc::c_char,
    mut s_len: size_t,
) {
    let mut n_free: size_t = ((*p).start).offset_from((*p).buf) as libc::c_long
        as size_t;
    if n_free < (1 as libc::c_int as libc::c_ulong).wrapping_add(s_len) {
        let mut half: size_t = ((*p).n_alloc)
            .wrapping_add(1 as libc::c_int as libc::c_ulong)
            .wrapping_add(s_len);
        let mut q: *mut libc::c_char = xnmalloc(2 as libc::c_int as size_t, half)
            as *mut libc::c_char;
        let mut n_used: size_t = ((*p).n_alloc).wrapping_sub(n_free);
        (*p)
            .start = q
            .offset((2 as libc::c_int as libc::c_ulong).wrapping_mul(half) as isize)
            .offset(-(n_used as isize));
        memcpy(
            (*p).start as *mut libc::c_void,
            ((*p).buf).offset(n_free as isize) as *const libc::c_void,
            n_used,
        );
        free((*p).buf as *mut libc::c_void);
        (*p).buf = q;
        (*p).n_alloc = (2 as libc::c_int as libc::c_ulong).wrapping_mul(half);
    }
    (*p)
        .start = ((*p).start)
        .offset(-((1 as libc::c_int as libc::c_ulong).wrapping_add(s_len) as isize));
    *((*p).start).offset(0 as libc::c_int as isize) = '/' as i32 as libc::c_char;
    memcpy(
        ((*p).start).offset(1 as libc::c_int as isize) as *mut libc::c_void,
        s as *const libc::c_void,
        s_len,
    );
}
unsafe extern "C" fn nth_parent(mut n: size_t) -> *mut libc::c_char {
    let mut buf: *mut libc::c_char = xnmalloc(3 as libc::c_int as size_t, n)
        as *mut libc::c_char;
    let mut p: *mut libc::c_char = buf;
    let mut i: size_t = 0 as libc::c_int as size_t;
    while i < n {
        memcpy(
            p as *mut libc::c_void,
            b"../\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            3 as libc::c_int as libc::c_ulong,
        );
        p = p.offset(3 as libc::c_int as isize);
        i = i.wrapping_add(1);
        i;
    }
    *p.offset(-(1 as libc::c_int) as isize) = '\0' as i32 as libc::c_char;
    return buf;
}
unsafe extern "C" fn find_dir_entry(
    mut dot_sb: *mut stat,
    mut file_name: *mut file_name,
    mut parent_height: size_t,
) {
    let mut dirp: *mut DIR = 0 as *mut DIR;
    let mut fd: libc::c_int = 0;
    let mut parent_sb: stat = stat {
        st_dev: 0,
        st_ino: 0,
        st_mode: 0,
        st_nlink: 0,
        st_uid: 0,
        st_gid: 0,
        st_rdev: 0,
        __pad1: 0,
        st_size: 0,
        st_blksize: 0,
        __pad2: 0,
        st_blocks: 0,
        st_atim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_mtim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_ctim: timespec { tv_sec: 0, tv_nsec: 0 },
        __glibc_reserved: [0; 2],
    };
    let mut use_lstat: bool = false;
    let mut found: bool = false;
    dirp = opendir(b"..\0" as *const u8 as *const libc::c_char);
    if dirp.is_null() {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                *__errno_location(),
                gettext(
                    b"cannot open directory %s\0" as *const u8 as *const libc::c_char,
                ),
                quote(nth_parent(parent_height)),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"cannot open directory %s\0" as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"cannot open directory %s\0" as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    fd = dirfd(dirp);
    if (if 0 as libc::c_int <= fd {
        fchdir(fd)
    } else {
        chdir(b"..\0" as *const u8 as *const libc::c_char)
    }) < 0 as libc::c_int
    {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                *__errno_location(),
                gettext(b"failed to chdir to %s\0" as *const u8 as *const libc::c_char),
                quote(nth_parent(parent_height)),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"failed to chdir to %s\0" as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"failed to chdir to %s\0" as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    if (if 0 as libc::c_int <= fd {
        fstat(fd, &mut parent_sb)
    } else {
        stat(b".\0" as *const u8 as *const libc::c_char, &mut parent_sb)
    }) < 0 as libc::c_int
    {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                *__errno_location(),
                gettext(b"failed to stat %s\0" as *const u8 as *const libc::c_char),
                quote(nth_parent(parent_height)),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(b"failed to stat %s\0" as *const u8 as *const libc::c_char),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(b"failed to stat %s\0" as *const u8 as *const libc::c_char),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    use_lstat = parent_sb.st_dev != (*dot_sb).st_dev;
    found = 0 as libc::c_int != 0;
    loop {
        let mut dp: *const dirent = 0 as *const dirent;
        let mut ent_sb: stat = stat {
            st_dev: 0,
            st_ino: 0,
            st_mode: 0,
            st_nlink: 0,
            st_uid: 0,
            st_gid: 0,
            st_rdev: 0,
            __pad1: 0,
            st_size: 0,
            st_blksize: 0,
            __pad2: 0,
            st_blocks: 0,
            st_atim: timespec { tv_sec: 0, tv_nsec: 0 },
            st_mtim: timespec { tv_sec: 0, tv_nsec: 0 },
            st_ctim: timespec { tv_sec: 0, tv_nsec: 0 },
            __glibc_reserved: [0; 2],
        };
        let mut ino: ino_t = 0;
        *__errno_location() = 0 as libc::c_int;
        dp = readdir_ignoring_dot_and_dotdot(dirp);
        if dp.is_null() {
            if *__errno_location() != 0 {
                let mut e: libc::c_int = *__errno_location();
                closedir(dirp);
                *__errno_location() = e;
                dirp = 0 as *mut DIR;
            }
            break;
        } else {
            ino = (*dp).d_ino;
            if ino == NOT_AN_INODE_NUMBER as libc::c_int as libc::c_ulong
                || use_lstat as libc::c_int != 0
            {
                if lstat(((*dp).d_name).as_ptr(), &mut ent_sb) < 0 as libc::c_int {
                    continue;
                }
                ino = ent_sb.st_ino;
            }
            if ino != (*dot_sb).st_ino {
                continue;
            }
            if !(!use_lstat || ent_sb.st_dev == (*dot_sb).st_dev) {
                continue;
            }
            file_name_prepend(
                file_name,
                ((*dp).d_name).as_ptr(),
                strlen(((*dp).d_name).as_ptr()),
            );
            found = 1 as libc::c_int != 0;
            break;
        }
    }
    if dirp.is_null() || closedir(dirp) != 0 as libc::c_int {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                *__errno_location(),
                gettext(b"reading directory %s\0" as *const u8 as *const libc::c_char),
                quote(nth_parent(parent_height)),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"reading directory %s\0" as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"reading directory %s\0" as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    if !found {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                0 as libc::c_int,
                gettext(
                    b"couldn't find directory entry in %s with matching i-node\0"
                        as *const u8 as *const libc::c_char,
                ),
                quote(nth_parent(parent_height)),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    0 as libc::c_int,
                    gettext(
                        b"couldn't find directory entry in %s with matching i-node\0"
                            as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    0 as libc::c_int,
                    gettext(
                        b"couldn't find directory entry in %s with matching i-node\0"
                            as *const u8 as *const libc::c_char,
                    ),
                    quote(nth_parent(parent_height)),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    *dot_sb = parent_sb;
}
unsafe extern "C" fn robust_getcwd(mut file_name: *mut file_name) {
    let mut height: size_t = 1 as libc::c_int as size_t;
    let mut dev_ino_buf: dev_ino = dev_ino { st_ino: 0, st_dev: 0 };
    let mut root_dev_ino: *mut dev_ino = get_root_dev_ino(&mut dev_ino_buf);
    let mut dot_sb: stat = stat {
        st_dev: 0,
        st_ino: 0,
        st_mode: 0,
        st_nlink: 0,
        st_uid: 0,
        st_gid: 0,
        st_rdev: 0,
        __pad1: 0,
        st_size: 0,
        st_blksize: 0,
        __pad2: 0,
        st_blocks: 0,
        st_atim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_mtim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_ctim: timespec { tv_sec: 0, tv_nsec: 0 },
        __glibc_reserved: [0; 2],
    };
    if root_dev_ino.is_null() {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                *__errno_location(),
                gettext(
                    b"failed to get attributes of %s\0" as *const u8
                        as *const libc::c_char,
                ),
                quotearg_style(
                    shell_escape_always_quoting_style,
                    b"/\0" as *const u8 as *const libc::c_char,
                ),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"failed to get attributes of %s\0" as *const u8
                            as *const libc::c_char,
                    ),
                    quotearg_style(
                        shell_escape_always_quoting_style,
                        b"/\0" as *const u8 as *const libc::c_char,
                    ),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(
                        b"failed to get attributes of %s\0" as *const u8
                            as *const libc::c_char,
                    ),
                    quotearg_style(
                        shell_escape_always_quoting_style,
                        b"/\0" as *const u8 as *const libc::c_char,
                    ),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    if stat(b".\0" as *const u8 as *const libc::c_char, &mut dot_sb) < 0 as libc::c_int {
        if 0 != 0 {
            error(
                1 as libc::c_int,
                *__errno_location(),
                gettext(b"failed to stat %s\0" as *const u8 as *const libc::c_char),
                quotearg_style(
                    shell_escape_always_quoting_style,
                    b".\0" as *const u8 as *const libc::c_char,
                ),
            );
            if 1 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(b"failed to stat %s\0" as *const u8 as *const libc::c_char),
                    quotearg_style(
                        shell_escape_always_quoting_style,
                        b".\0" as *const u8 as *const libc::c_char,
                    ),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 1 as libc::c_int;
                error(
                    __errstatus,
                    *__errno_location(),
                    gettext(b"failed to stat %s\0" as *const u8 as *const libc::c_char),
                    quotearg_style(
                        shell_escape_always_quoting_style,
                        b".\0" as *const u8 as *const libc::c_char,
                    ),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    while !(dot_sb.st_dev ^ (*root_dev_ino).st_dev
        | dot_sb.st_ino ^ (*root_dev_ino).st_ino == 0)
    {
        let fresh0 = height;
        height = height.wrapping_add(1);
        find_dir_entry(&mut dot_sb, file_name, fresh0);
    }
    if *((*file_name).start).offset(0 as libc::c_int as isize) as libc::c_int
        == '\0' as i32
    {
        file_name_prepend(
            file_name,
            b"\0" as *const u8 as *const libc::c_char,
            0 as libc::c_int as size_t,
        );
    }
}
unsafe extern "C" fn logical_getcwd() -> *mut libc::c_char {
    let mut st1: stat = stat {
        st_dev: 0,
        st_ino: 0,
        st_mode: 0,
        st_nlink: 0,
        st_uid: 0,
        st_gid: 0,
        st_rdev: 0,
        __pad1: 0,
        st_size: 0,
        st_blksize: 0,
        __pad2: 0,
        st_blocks: 0,
        st_atim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_mtim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_ctim: timespec { tv_sec: 0, tv_nsec: 0 },
        __glibc_reserved: [0; 2],
    };
    let mut st2: stat = stat {
        st_dev: 0,
        st_ino: 0,
        st_mode: 0,
        st_nlink: 0,
        st_uid: 0,
        st_gid: 0,
        st_rdev: 0,
        __pad1: 0,
        st_size: 0,
        st_blksize: 0,
        __pad2: 0,
        st_blocks: 0,
        st_atim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_mtim: timespec { tv_sec: 0, tv_nsec: 0 },
        st_ctim: timespec { tv_sec: 0, tv_nsec: 0 },
        __glibc_reserved: [0; 2],
    };
    let mut wd: *mut libc::c_char = getenv(b"PWD\0" as *const u8 as *const libc::c_char);
    let mut p: *mut libc::c_char = 0 as *mut libc::c_char;
    if wd.is_null() || *wd.offset(0 as libc::c_int as isize) as libc::c_int != '/' as i32
    {
        return 0 as *mut libc::c_char;
    }
    p = wd;
    loop {
        p = strstr(p, b"/.\0" as *const u8 as *const libc::c_char);
        if p.is_null() {
            break;
        }
        if *p.offset(2 as libc::c_int as isize) == 0
            || *p.offset(2 as libc::c_int as isize) as libc::c_int == '/' as i32
            || *p.offset(2 as libc::c_int as isize) as libc::c_int == '.' as i32
                && (*p.offset(3 as libc::c_int as isize) == 0
                    || *p.offset(3 as libc::c_int as isize) as libc::c_int == '/' as i32)
        {
            return 0 as *mut libc::c_char;
        }
        p = p.offset(1);
        p;
    }
    if stat(wd, &mut st1) == 0 as libc::c_int
        && stat(b".\0" as *const u8 as *const libc::c_char, &mut st2) == 0 as libc::c_int
        && psame_inode(&mut st1, &mut st2) as libc::c_int != 0
    {
        return wd;
    }
    return 0 as *mut libc::c_char;
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut wd: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut logical: bool = !(getenv(
        b"POSIXLY_CORRECT\0" as *const u8 as *const libc::c_char,
    ))
        .is_null();
    set_program_name(*argv.offset(0 as libc::c_int as isize));
    setlocale(6 as libc::c_int, b"\0" as *const u8 as *const libc::c_char);
    bindtextdomain(
        b"coreutils\0" as *const u8 as *const libc::c_char,
        b"/usr/local/share/locale\0" as *const u8 as *const libc::c_char,
    );
    textdomain(b"coreutils\0" as *const u8 as *const libc::c_char);
    atexit(Some(close_stdout as unsafe extern "C" fn() -> ()));
    loop {
        let mut c: libc::c_int = getopt_long(
            argc,
            argv,
            b"LP\0" as *const u8 as *const libc::c_char,
            longopts.as_ptr(),
            0 as *mut libc::c_int,
        );
        if c == -(1 as libc::c_int) {
            break;
        }
        match c {
            76 => {
                logical = 1 as libc::c_int != 0;
            }
            80 => {
                logical = 0 as libc::c_int != 0;
            }
            -2 => {
                usage(0 as libc::c_int);
            }
            -3 => {
                version_etc(
                    stdout,
                    b"pwd\0" as *const u8 as *const libc::c_char,
                    b"GNU coreutils\0" as *const u8 as *const libc::c_char,
                    Version,
                    proper_name_lite(
                        b"Jim Meyering\0" as *const u8 as *const libc::c_char,
                        b"Jim Meyering\0" as *const u8 as *const libc::c_char,
                    ),
                    0 as *mut libc::c_void as *mut libc::c_char,
                );
                exit(0 as libc::c_int);
            }
            _ => {
                usage(1 as libc::c_int);
            }
        }
    }
    if optind < argc {
        if 0 != 0 {
            error(
                0 as libc::c_int,
                0 as libc::c_int,
                gettext(
                    b"ignoring non-option arguments\0" as *const u8
                        as *const libc::c_char,
                ),
            );
            if 0 as libc::c_int != 0 as libc::c_int {
                unreachable!();
            } else {};
        } else {
            ({
                let __errstatus: libc::c_int = 0 as libc::c_int;
                error(
                    __errstatus,
                    0 as libc::c_int,
                    gettext(
                        b"ignoring non-option arguments\0" as *const u8
                            as *const libc::c_char,
                    ),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
            ({
                let __errstatus: libc::c_int = 0 as libc::c_int;
                error(
                    __errstatus,
                    0 as libc::c_int,
                    gettext(
                        b"ignoring non-option arguments\0" as *const u8
                            as *const libc::c_char,
                    ),
                );
                if __errstatus != 0 as libc::c_int {
                    unreachable!();
                } else {};
                
            });
        };
    }
    if logical {
        wd = logical_getcwd();
        if !wd.is_null() {
            puts(wd);
            return 0 as libc::c_int;
        }
    }
    wd = xgetcwd();
    if !wd.is_null() {
        puts(wd);
        free(wd as *mut libc::c_void);
    } else {
        let mut file_name: *mut file_name = file_name_init();
        robust_getcwd(file_name);
        puts((*file_name).start);
        file_name_free(file_name);
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
