use translate::*;
use std::env;
use std::ffi::CStr;
use std::os::unix::io::AsRawFd;
use std::io::Write;
use std::io::stdout;
use libc::uname;
use libc::utsname;
pub fn main() {
    let mut argv_idx: u32 = 0;
    let mut s = LibtreeStateT {
        color: (env::var_os("NO_COLOR").is_none() && unsafe { libc::isatty(stdout().as_raw_fd()) } != 0) as i32,
        verbosity: 0,
        path: 0,
        max_depth: 32,
        ld_conf_file: Some("/etc/ld.so.conf".to_string()),
        PLATFORM: None,
        OSNAME: None,
        OSREL: None,
        LIB: Some("lib".to_string()),
        string_table: unsafe { std::mem::zeroed() }, // Fixed initialization
        visited: unsafe { std::mem::zeroed() },       // Fixed initialization
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };

    let mut positional = 1;
    let mut uname_val: utsname = unsafe { std::mem::zeroed() };
    if unsafe { uname(&mut uname_val) } != 0 {
        std::process::exit(1);
    }

    s.PLATFORM = Some(unsafe { CStr::from_ptr(uname_val.machine.as_ptr()).to_string_lossy().into_owned() });
    s.OSNAME = Some(unsafe { CStr::from_ptr(uname_val.sysname.as_ptr()).to_string_lossy().into_owned() });
    s.OSREL = Some(unsafe { CStr::from_ptr(uname_val.release.as_ptr()).to_string_lossy().into_owned() });

    if s.OSNAME.as_deref() == Some("FreeBSD") {
        s.ld_conf_file = Some("/etc/ld-elf.so.conf".to_string());
    }

    let mut opt_help = 0;
    let mut opt_version = 0;
    let mut opt_raw = 0;

    let args: Vec<String> = env::args().collect();
    let argc = args.len() as i32;
    let argv: Vec<*const libc::c_char> = args.iter().map(|arg| arg.as_ptr() as *const libc::c_char).collect();

    let mut i: i32 = 1; // Manual loop index to allow modification
    while i < argc {
        helper_main_2(
            &mut argv_idx,
            &mut s,
            &mut positional,
            &mut opt_help,
            &mut opt_version,
            &mut opt_raw,
            &mut i,
            argc,
            &argv,
        );
        i += 1;
    }

    argv_idx += 1;
    positional -= 1;

    if opt_help != 0 || (opt_version == 0 && positional == 0) {
        helper_main_1(s.clone(), opt_help);
    }

    if opt_version != 0 {
        println!("3.1.1");
        return;
    }

    let start_index = argv_idx as usize;
    let count = positional as usize;
    let pathv: Vec<&str> = args.iter().skip(start_index).take(count).map(|s| s.as_str()).collect();
    let exit_code = print_tree(count, &pathv, &mut s);
    std::process::exit(exit_code);
}
