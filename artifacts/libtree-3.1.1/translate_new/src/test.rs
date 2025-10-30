use crate::*;
use std::fs::File;
use std::fs::OpenOptions;
use std::fs::remove_file;
use std::io::Read;
use std::io::Result as IoResult;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::process::exit;
use std::env;
use std::fs;
use std::process;
use libc::dev_t;
use libc::ino_t;
use std::ffi::CStr;
pub fn create_test_elf_file(filename: &str, valid: bool) {
    // Open file in write-only mode, binary (equivalent to "wb" in C)
    let mut f = match File::create(filename) {
        Ok(file) => file,
        Err(_) => return, // Return early if file creation fails
    };

    if valid {
        let mut elf_header = [0u8; 64];
        elf_header[0] = 0x7f;
        elf_header[1] = b'E';
        elf_header[2] = b'L';
        elf_header[3] = b'F';
        elf_header[4] = 2;
        elf_header[5] = 1;
        elf_header[6] = 1;
        elf_header[16] = 2;
        elf_header[18] = 0x3e;

        // Write the entire header (equivalent to fwrite in C)
        if let Err(_) = f.write_all(&elf_header) {
            return; // Ignore write errors
        }
    } else {
        // Write "invalid" string (equivalent to fwrite in C)
        if let Err(_) = f.write_all(b"invalid") {
            return; // Ignore write errors
        }
    }

    // File is automatically closed when `f` goes out of scope
}

pub fn create_test_config_file(filename: &str, content: &str) {
    if let Ok(mut f) = File::create(filename) {
        let _ = f.write_all(content.as_bytes());
    }
}

pub fn helper_create_elf_with_program_headers_1(f: &mut File) -> std::io::Result<()> {
    // Initialize phdr2 with all zeros and set specific bytes
    let mut phdr2 = [0u8; 56];
    phdr2[0] = 2;
    phdr2[4] = 6;
    phdr2[8] = 0x00;
    phdr2[9] = 0x20;
    phdr2[16] = 0x00;
    phdr2[17] = 0x00;
    phdr2[18] = 0x60;
    phdr2[24] = 0x00;
    phdr2[25] = 0x00;
    phdr2[26] = 0x60;
    phdr2[32] = 200;
    phdr2[40] = 200;
    phdr2[48] = 8;

    f.write_all(&phdr2)?;

    // Fill remaining space up to 0x2000 with zeros
    let current_pos = f.seek(SeekFrom::Current(0))?;
    for _ in current_pos..0x2000 {
        f.write_all(&[0])?;
    }

    // Write dynamic entries
    let mut dynamic_entry = [0u8; 16];
    dynamic_entry[0] = 5;
    dynamic_entry[8] = 0x00;
    dynamic_entry[9] = 0x10;
    dynamic_entry[10] = 0x60;
    f.write_all(&dynamic_entry)?;

    dynamic_entry.fill(0);
    dynamic_entry[0] = 1;
    f.write_all(&dynamic_entry)?;

    dynamic_entry.fill(0);
    f.write_all(&dynamic_entry)?;

    // Fill remaining space up to 0x3000 with zeros
    let current_pos = f.seek(SeekFrom::Current(0))?;
    for _ in current_pos..0x3000 {
        f.write_all(&[0])?;
    }

    // Write the library name
    f.write_all(b"libtest.so\0")?;

    Ok(())
}
pub fn test_utoa_function() {
    let mut buffer = [0u8; 32];
    
    {
        utoa(&mut buffer, 0);
        let result = std::str::from_utf8(&buffer).unwrap().trim_end_matches('\0');
        if result != "0" {
            println!("FAILED: Expected \"0\", got \"{}\" at line 84", result);
            std::process::exit(1);
        }
    }
    
    {
        utoa(&mut buffer, 123);
        let result = std::str::from_utf8(&buffer).unwrap().trim_end_matches('\0');
        if result != "123" {
            println!("FAILED: Expected \"123\", got \"{}\" at line 87", result);
            std::process::exit(1);
        }
    }
    
    {
        utoa(&mut buffer, 9876543210);
        let result = std::str::from_utf8(&buffer).unwrap().trim_end_matches('\0');
        if result != "9876543210" {
            println!("FAILED: Expected \"9876543210\", got \"{}\" at line 90", result);
            std::process::exit(1);
        }
    }
}
pub fn test_host_endianness() {
    let result = host_is_little_endian();
    if !(result == false || result == true) {
        println!("FAILED: Assertion failed at line {}", 96);
        std::process::exit(1);
    }
}
pub fn test_ascending_order_check() {
    let ascending = [1, 2, 3, 4, 5];
    let descending = [5, 4, 3, 2, 1];
    let mixed = [1, 3, 2, 4, 5];
    let single = [42];
    let empty: [u64; 0] = [];

    // Test ascending array
    if !is_ascending_order(&ascending, ascending.len()) {
        println!("FAILED: Expected {}, got {} at line {}", true, is_ascending_order(&ascending, ascending.len()), 104);
        std::process::exit(1);
    }

    // Test descending array
    if is_ascending_order(&descending, descending.len()) {
        println!("FAILED: Expected {}, got {} at line {}", false, is_ascending_order(&descending, descending.len()), 105);
        std::process::exit(1);
    }

    // Test mixed array
    if is_ascending_order(&mixed, mixed.len()) {
        println!("FAILED: Expected {}, got {} at line {}", false, is_ascending_order(&mixed, mixed.len()), 106);
        std::process::exit(1);
    }

    // Test single element array
    if !is_ascending_order(&single, single.len()) {
        println!("FAILED: Expected {}, got {} at line {}", true, is_ascending_order(&single, single.len()), 110);
        std::process::exit(1);
    }

    // Test empty array
    if !is_ascending_order(&empty, empty.len()) {
        println!("FAILED: Expected {}, got {} at line {}", true, is_ascending_order(&empty, empty.len()), 113);
        std::process::exit(1);
    }
}
pub fn test_exclude_list_checking() {
    // Test case 1: libc.so.6 should be in exclude list
    {
        let expected = 1;
        let actual = is_in_exclude_list(Some("libc.so.6"));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 178);
            exit(1);
        }
    }

    // Test case 2: libc.so should be in exclude list
    {
        let expected = 1;
        let actual = is_in_exclude_list(Some("libc.so"));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 179);
            exit(1);
        }
    }

    // Test case 3: libm.so.1 should be in exclude list
    {
        let expected = 1;
        let actual = is_in_exclude_list(Some("libm.so.1"));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 180);
            exit(1);
        }
    }

    // Test case 4: ld-linux-x86-64.so.2 should be in exclude list
    {
        let expected = 1;
        let actual = is_in_exclude_list(Some("ld-linux-x86-64.so.2"));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 181);
            exit(1);
        }
    }

    // Test case 5: libcustom.so should NOT be in exclude list
    {
        let expected = 0;
        let actual = is_in_exclude_list(Some("libcustom.so"));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 183);
            exit(1);
        }
    }

    // Test case 6: mylib.so.1 should NOT be in exclude list
    {
        let expected = 0;
        let actual = is_in_exclude_list(Some("mylib.so.1"));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 184);
            exit(1);
        }
    }

    // Test case 7: empty string should NOT be in exclude list
    {
        let expected = 0;
        let actual = is_in_exclude_list(Some(""));
        if expected != actual {
            println!("FAILED: Expected {}, got {} at line {}", expected, actual, 185);
            exit(1);
        }
    }
}
pub fn test_main_argument_parsing() {
    let mut state = LibtreeStateT {
        color: 1,
        verbosity: 0,
        path: 0,
        max_depth: 32,
        ld_conf_file: Some("/etc/ld.so.conf".to_string()),
        string_table: StringTableT {
            arr: None,
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };

    let _argv_help = ["libtree", "--help"];
    state.verbosity = 2;
    state.path = 1;
    state.max_depth = 5;

    {
        if 2 != state.verbosity {
            eprintln!("FAILED: Expected {}, got {} at line {}", 2, state.verbosity, 356);
            process::exit(1);
        }
    }

    {
        if 1 != state.path {
            eprintln!("FAILED: Expected {}, got {} at line {}", 1, state.path, 357);
            process::exit(1);
        }
    }

    {
        if 5 != state.max_depth {
            eprintln!("FAILED: Expected {}, got {} at line {}", 5, state.max_depth, 358);
            process::exit(1);
        }
    }
}
pub fn test_print_colon_delimited_paths_function() {
    println!("Testing print_colon_delimited_paths:");
    print_colon_delimited_paths(Some("/usr/lib:/lib:/usr/local/lib"), Some("  "));
    print_colon_delimited_paths(Some(""), Some("    "));
    print_colon_delimited_paths(Some(":/usr/lib::/lib:"), Some("  "));
    print_colon_delimited_paths(Some("/single/path"), Some("    "));
    println!("Done testing print_colon_delimited_paths");
}

pub fn create_elf_with_program_headers(filename: &str, has_dynamic: bool) -> std::io::Result<()> {
    let mut f = File::create(filename)?;
    
    // Initialize ELF header
    let mut elf_header = [0u8; 64];
    elf_header[0] = 0x7f;
    elf_header[1] = b'E';
    elf_header[2] = b'L';
    elf_header[3] = b'F';
    elf_header[4] = 2;
    elf_header[5] = 1;
    elf_header[6] = 1;
    elf_header[16] = 3;
    elf_header[17] = 0;
    elf_header[18] = 0x3e;
    elf_header[19] = 0;
    elf_header[20] = 1;
    elf_header[21] = 0;
    elf_header[22] = 0;
    elf_header[23] = 0;
    elf_header[32] = 64;
    elf_header[33..40].copy_from_slice(&[0; 7]);
    elf_header[52] = 64;
    elf_header[53] = 0;
    elf_header[54] = 56;
    elf_header[55] = 0;
    elf_header[56] = if has_dynamic { 2 } else { 1 };
    elf_header[57] = 0;
    
    f.write_all(&elf_header)?;

    // Initialize program header
    let mut phdr1 = [0u8; 56];
    phdr1[0] = 1;
    phdr1[4] = 5;
    phdr1[8] = 0x00;
    phdr1[9] = 0x10;
    phdr1[16] = 0x00;
    phdr1[17] = 0x00;
    phdr1[18] = 0x40;
    phdr1[24] = 0x00;
    phdr1[25] = 0x00;
    phdr1[26] = 0x40;
    phdr1[32] = 0x00;
    phdr1[33] = 0x10;
    phdr1[40] = 0x00;
    phdr1[41] = 0x10;
    phdr1[48] = 0x00;
    phdr1[49] = 0x10;
    
    f.write_all(&phdr1)?;

    if has_dynamic {
        helper_create_elf_with_program_headers_1(&mut f)?;
    }

    Ok(())
}

pub fn test_string_table_operations() {
    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(10)),
        n: 0,
        capacity: 10,
    };

    string_table_store(&mut table, "hello");

    {
        if 6 != table.n {
            println!("FAILED: Expected {}, got {} at line {}", 6, table.n, 153);
            exit(1);
        }
    }

    {
        let expected = "hello";
        let actual: String = table.arr.as_ref().unwrap().iter().collect();
        if expected != actual {
            println!("FAILED: Expected \"{}\", got \"{}\" at line {}", expected, actual, 154);
            exit(1);
        }
    }

    string_table_store(&mut table, "world");

    {
        let expected = "world";
        let actual: String = table.arr.as_ref().unwrap().iter().skip(6).collect();
        if expected != actual {
            println!("FAILED: Expected \"{}\", got \"{}\" at line {}", expected, actual, 157);
            exit(1);
        }
    }
}

pub fn test_string_table_growth() {
    let mut table = StringTableT {
        n: 0,
        capacity: 5,
        arr: Some(Vec::with_capacity(5)),
    };

    string_table_store(&mut table, "this is a long string");

    // Assertion check for capacity >= n
    if !(table.capacity >= table.n) {
        eprintln!("FAILED: Assertion failed at line {}", 170);
        process::exit(1);
    }

    // String comparison check
    if let Some(arr) = &table.arr {
        let stored_str: String = arr.iter().collect();
        if stored_str != "this is a long string" {
            eprintln!(
                "FAILED: Expected \"{}\", got \"{}\" at line {}",
                "this is a long string",
                stored_str,
                171
            );
            process::exit(1);
        }
    } else {
        eprintln!("FAILED: No string stored in table at line {}", 171);
        process::exit(1);
    }
}
pub fn test_config_file_nonexistent() {
    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(1024)),
        n: 0,
        capacity: 1024,
    };
    
    let result = parse_ld_config_file(&mut table, "nonexistent.conf");
    
    match result {
        Ok(()) => (), // Success case does nothing like original C code
        Err(_) => {
            println!("FAILED: Expected {}, got error at line {}", 1, 269);
            process::exit(1);
        }
    }
}

pub fn test_string_table_copy_from_file() {
    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(100)),
        n: 0,
        capacity: 100,
    };

    // Create test file and write data
    {
        let mut test_file = File::create("test_string_copy.txt").unwrap();
        test_file.write_all(b"test\0data").unwrap();
    }

    // Read from test file
    let mut test_file = File::open("test_string_copy.txt").unwrap();
    string_table_copy_from_file(&mut table, &mut test_file);

    // Verify content
    {
        let expected = "test";
        if let Some(arr) = &table.arr {
            let actual: String = arr.iter().take(expected.len()).collect();
            if expected != actual {
                eprintln!("FAILED: Expected \"{}\", got \"{}\" at line {}", expected, actual, 534);
                exit(1);
            }
        } else {
            eprintln!("FAILED: No data in table at line {}", 534);
            exit(1);
        }
    }

    // Clean up
    remove_file("test_string_copy.txt").unwrap();
}
pub fn tree_visited_files_contains(files: &crate::VisitedFileArrayT, file: &crate::VisitedFileT) -> i32 {
    if let Some(arr) = &files.arr {
        if arr.iter().any(|f| f.st_dev == file.st_dev && f.st_ino == file.st_ino) {
            1
        } else {
            0
        }
    } else {
        0
    }
}

pub fn tree_visited_files_append(files: &mut crate::VisitedFileArrayT, file: &crate::VisitedFileT) {
    if files.arr.is_none() {
        files.arr = Some(Vec::with_capacity(files.capacity));
    }
    
    if let Some(arr) = &mut files.arr {
        if files.n >= files.capacity {
            files.capacity *= 2;
            arr.reserve(files.capacity - files.n);
        }
        arr.push(crate::VisitedFileT {
            st_dev: file.st_dev,
            st_ino: file.st_ino,
        });
        files.n += 1;
    }
}

pub fn stat_to_visited_file(s: &libc::stat) -> crate::VisitedFileT {
    crate::VisitedFileT {
        st_dev: s.st_dev,
        st_ino: s.st_ino,
    }
}

pub fn test_visited_files_operations() {
    let mut files = crate::VisitedFileArrayT {
        arr: Some(Vec::with_capacity(2)),
        n: 0,
        capacity: 2,
    };
    
    let stat1 = crate::VisitedFileT { st_dev: 1, st_ino: 100 };
    let stat2 = crate::VisitedFileT { st_dev: 1, st_ino: 200 };
    let stat3 = crate::VisitedFileT { st_dev: 2, st_ino: 100 };
    
    {
        if 0 != tree_visited_files_contains(&files, &stat1) {
            eprintln!("FAILED: Expected 0, got {} at line 199", tree_visited_files_contains(&files, &stat1));
            std::process::exit(1);
        }
    }
    
    tree_visited_files_append(&mut files, &stat1);
    
    {
        if 1 != tree_visited_files_contains(&files, &stat1) {
            eprintln!("FAILED: Expected 1, got {} at line 202", tree_visited_files_contains(&files, &stat1));
            std::process::exit(1);
        }
    }
    
    {
        if 0 != tree_visited_files_contains(&files, &stat2) {
            eprintln!("FAILED: Expected 0, got {} at line 203", tree_visited_files_contains(&files, &stat2));
            std::process::exit(1);
        }
    }
    
    tree_visited_files_append(&mut files, &stat2);
    
    {
        if 1 != tree_visited_files_contains(&files, &stat1) {
            eprintln!("FAILED: Expected 1, got {} at line 206", tree_visited_files_contains(&files, &stat1));
            std::process::exit(1);
        }
    }
    
    {
        if 1 != tree_visited_files_contains(&files, &stat2) {
            eprintln!("FAILED: Expected 1, got {} at line 207", tree_visited_files_contains(&files, &stat2));
            std::process::exit(1);
        }
    }
    
    {
        if 0 != tree_visited_files_contains(&files, &stat3) {
            eprintln!("FAILED: Expected 0, got {} at line 208", tree_visited_files_contains(&files, &stat3));
            std::process::exit(1);
        }
    }
    
    tree_visited_files_append(&mut files, &stat3);
    
    {
        if 1 != tree_visited_files_contains(&files, &stat3) {
            eprintln!("FAILED: Expected 1, got {} at line 212", tree_visited_files_contains(&files, &stat3));
            std::process::exit(1);
        }
    }
    
    {
        if !(files.capacity > 2) {
            eprintln!("FAILED: Assertion failed at line 213");
            std::process::exit(1);
        }
    }
}
pub fn test_libtree_state_lifecycle() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            n: 0,
            capacity: 0,
            arr: Some(Vec::new()),
        },
        visited: VisitedFileArrayT {
            n: 0,
            capacity: 0,
            arr: Some(Vec::new()),
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);

    {
        if 0 != state.string_table.n {
            println!("FAILED: Expected {}, got {} at line {}", 0, state.string_table.n, 223);
            exit(1);
        }
    }

    {
        if 1024 != state.string_table.capacity {
            println!("FAILED: Expected {}, got {} at line {}", 1024, state.string_table.capacity, 224);
            exit(1);
        }
    }

    {
        if state.string_table.arr.is_none() {
            println!("FAILED: Assertion failed at line {}", 225);
            exit(1);
        }
    }

    {
        if 0 != state.visited.n {
            println!("FAILED: Expected {}, got {} at line {}", 0, state.visited.n, 227);
            exit(1);
        }
    }

    {
        if 256 != state.visited.capacity {
            println!("FAILED: Expected {}, got {} at line {}", 256, state.visited.capacity, 228);
            exit(1);
        }
    }

    {
        if state.visited.arr.is_none() {
            println!("FAILED: Assertion failed at line {}", 229);
            exit(1);
        }
    }

    libtree_state_free(&mut state);
}
pub fn test_config_file_parsing() {
    create_test_config_file(
        "test_ld.conf",
        "# This is a comment\n/usr/local/lib\n/opt/lib\n\n  /usr/lib/x86_64-linux-gnu  \ninclude /etc/ld.so.conf.d/*.conf\n",
    );

    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(1024)),
        n: 0,
        capacity: 1024,
    };

    if let Err(e) = parse_ld_config_file(&mut table, "test_ld.conf") {
        println!("FAILED: Expected success, got error: {:?} at line {}", e, 251);
        exit(1);
    }

    {
        let arr_str: String = table.arr.as_ref().unwrap().iter().collect::<String>();
        if !arr_str.contains("/usr/local/lib") {
            println!("FAILED: Assertion failed at line {}", 254);
            exit(1);
        }
    }

    {
        let arr_str: String = table.arr.as_ref().unwrap().iter().collect::<String>();
        if !arr_str.contains("/opt/lib") {
            println!("FAILED: Assertion failed at line {}", 255);
            exit(1);
        }
    }

    {
        let arr_str: String = table.arr.as_ref().unwrap().iter().collect::<String>();
        if !arr_str.contains("/usr/lib/x86_64-linux-gnu") {
            println!("FAILED: Assertion failed at line {}", 256);
            exit(1);
        }
    }

    fs::remove_file("test_ld.conf").unwrap();
}

pub fn test_boundary_conditions() {
    let mut buffer = [0u8; 32];
    
    // Test utoa with value 1
    utoa(&mut buffer, 1);
    {
        let result = std::str::from_utf8(&buffer).unwrap().trim_end_matches('\0');
        if result != "1" {
            println!("FAILED: Expected \"1\", got \"{}\" at line 465", result);
            exit(1);
        }
    }

    // Test utoa with max value
    utoa(&mut buffer, usize::MAX);
    {
        let result = std::str::from_utf8(&buffer).unwrap().trim_end_matches('\0');
        if result.is_empty() {
            println!("FAILED: Assertion failed at line 469");
            exit(1);
        }
    }

    // Test string_table_store with empty string
    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(100)),
        n: 0,
        capacity: 100,
    };
    string_table_store(&mut table, "");
    
    {
        if table.n != 1 {
            println!("FAILED: Expected 1, got {} at line 477", table.n);
            exit(1);
        }
    }
    
    {
        let stored_str: String = table.arr.as_ref().unwrap().iter().collect();
        if stored_str != "" {
            println!("FAILED: Expected \"\", got \"{}\" at line 478", stored_str);
            exit(1);
        }
    }
}
pub fn test_ld_config_file_comprehensive() {
    create_test_config_file(
        "test_complex_ld.conf",
        "# Comment at start\n/usr/local/lib   # inline comment\n   /opt/lib   \n\n  # Comment with leading spaces\n/usr/lib/custom\ninclude /etc/ld.so.conf.d/*.conf\n",
    );

    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(1024)),
        n: 0,
        capacity: 1024,
    };

    let result = parse_ld_config_file(&mut table, "test_complex_ld.conf");
    if let Err(e) = result {
        println!("FAILED: Expected success, got error {:?} at line {}", e, 680);
        exit(1);
    }

    {
        let arr_str = table.arr.as_ref().unwrap().iter().collect::<String>();
        if !arr_str.contains("/usr/local/lib:") {
            println!("FAILED: Assertion failed at line {}", 683);
            exit(1);
        }
    }

    {
        let arr_str = table.arr.as_ref().unwrap().iter().collect::<String>();
        if !arr_str.contains("/opt/lib:") {
            println!("FAILED: Assertion failed at line {}", 684);
            exit(1);
        }
    }

    {
        let arr_str = table.arr.as_ref().unwrap().iter().collect::<String>();
        if !arr_str.contains("/usr/lib/custom:") {
            println!("FAILED: Assertion failed at line {}", 685);
            exit(1);
        }
    }

    fs::remove_file("test_complex_ld.conf").unwrap();
}

pub fn test_ld_conf_globbing_function() {
    create_test_config_file("test_include1.conf", "/path1\n");
    create_test_config_file("test_include2.conf", "/path2\n");
    
    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(1024)),
        n: 0,
        capacity: 1024,
    };

    let result = ld_conf_globbing(&mut table, "test_include*.conf");
    if result != 0 {
        println!("FAILED: Expected {}, got {} at line {}", 0, result, 704);
        exit(1);
    }

    let result = ld_conf_globbing(&mut table, "nonexistent*.conf");
    if result != 0 {
        println!("FAILED: Expected {}, got {} at line {}", 0, result, 708);
        exit(1);
    }

    fs::remove_file("test_include1.conf").unwrap();
    fs::remove_file("test_include2.conf").unwrap();
}
pub fn test_string_boundary_conditions() {
    // Test empty string case
    {
        if 0 != is_in_exclude_list(Some("")) {
            println!("FAILED: Expected {}, got {} at line {}", 0, is_in_exclude_list(Some("")), 757);
            exit(1);
        }
    }

    // Test libc.so.6.1.2.3 case
    {
        if 1 != is_in_exclude_list(Some("libc.so.6.1.2.3")) {
            println!("FAILED: Expected {}, got {} at line {}", 1, is_in_exclude_list(Some("libc.so.6.1.2.3")), 760);
            exit(1);
        }
    }

    // Test libm.so.1 case
    {
        if 1 != is_in_exclude_list(Some("libm.so.1")) {
            println!("FAILED: Expected {}, got {} at line {}", 1, is_in_exclude_list(Some("libm.so.1")), 761);
            exit(1);
        }
    }

    // Test string_table_maybe_grow
    let mut table = StringTableT {
        arr: Some(Vec::with_capacity(10)),
        n: 5,
        capacity: 10,
    };
    
    string_table_maybe_grow(&mut table, 10);
    
    {
        if !(table.capacity >= 30) {
            println!("FAILED: Assertion failed at line {}", 771);
            exit(1);
        }
    }
}
pub fn test_print_tree_function() {
    let mut state = LibtreeStateT {
        color: 0,
        verbosity: 0,
        path: 0,
        max_depth: 32,
        ld_conf_file: Some("/etc/ld.so.conf".to_string()),
        PLATFORM: Some("x86_64".to_string()),
        LIB: Some("lib".to_string()),
        OSNAME: Some("Linux".to_string()),
        OSREL: Some("5.4.0".to_string()),
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };

    create_test_elf_file("test_print.elf", true);
    let test_files = ["test_print.elf"];
    let result = print_tree(1, &test_files, &mut state);
    fs::remove_file("test_print.elf").unwrap(); // Equivalent to unlink()
}
pub fn test_error_message_coverage() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    
    let error_codes = [11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32];
    
    for i in 0..error_codes.len() {
        if !(error_codes[i] >= 11 && error_codes[i] <= 32) {
            println!("FAILED: Assertion failed at line {}", 839);
            process::exit(1);
        }
    }
    
    libtree_state_free(&mut state);
}

pub fn test_small_vec_u64_operations() {
    let mut vec = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 16,
    };
    small_vec_u64_init(&mut vec);
    
    {
        if vec.n != 0 {
            println!("FAILED: Expected {}, got {} at line {}", 0, vec.n, 121);
            process::exit(1);
        }
    }
    
    {
        if vec.p.is_some() {
            println!("FAILED: Expected {:?}, got {:?} at line {}", vec.buf.as_ptr(), vec.p.as_ref().map(|p| p.as_ptr()), 122);
            process::exit(1);
        }
    }
    
    for i in 0..16 {
        small_vec_u64_append(&mut vec, i as u64);
        
        {
            if (i + 1) as usize != vec.n {
                println!("FAILED: Expected {}, got {} at line {}", i + 1, vec.n, 127);
                process::exit(1);
            }
        }
        
        {
            if i != vec.buf[i as usize] {
                println!("FAILED: Expected {}, got {} at line {}", i, vec.buf[i as usize], 128);
                process::exit(1);
            }
        }
    }
    
    small_vec_u64_append(&mut vec, 16);
    
    {
        if 17 != vec.n {
            println!("FAILED: Expected {}, got {} at line {}", 17, vec.n, 133);
            process::exit(1);
        }
    }
    
    {
        if vec.p.is_none() {
            println!("FAILED: Assertion failed at line {}", 134);
            process::exit(1);
        }
    }
    
    for i in 17..50 {
        small_vec_u64_append(&mut vec, i as u64);
    }
    
    {
        if 50 != vec.n {
            println!("FAILED: Expected {}, got {} at line {}", 50, vec.n, 140);
            process::exit(1);
        }
    }
    
    small_vec_u64_free(&mut vec);
}
pub fn test_ld_library_path_parsing() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: usize::MAX,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    env::remove_var("LD_LIBRARY_PATH");
    parse_ld_library_path(&mut state);
    
    {
        if usize::MAX != state.ld_library_path_offset {
            eprintln!("FAILED: Expected {}, got {} at line {}", usize::MAX, state.ld_library_path_offset, 282);
            process::exit(1);
        }
    }
    
    env::set_var("LD_LIBRARY_PATH", "/usr/local/lib:/opt/lib");
    parse_ld_library_path(&mut state);
    
    {
        if !(state.ld_library_path_offset != usize::MAX) {
            eprintln!("FAILED: Assertion failed at line {}", 287);
            process::exit(1);
        }
    }
    
    {
        let expected = "/usr/local/lib:/opt/lib";
        let string_table_content = state.string_table.arr.as_ref().unwrap();
        let actual: String = string_table_content[state.ld_library_path_offset..].iter().collect();
        if expected != actual {
            eprintln!("FAILED: Expected \"{}\", got \"{}\" at line {}", expected, actual, 288);
            process::exit(1);
        }
    }
    
    libtree_state_free(&mut state);
}
pub fn test_default_paths_setup() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };

    libtree_state_init(&mut state);
    set_default_paths(&mut state);

    let expected_path = "/lib:/lib64:/usr/lib:/usr/lib64";
    let actual_path = unsafe {
        std::slice::from_raw_parts(
            state.string_table.arr.as_ref().unwrap().as_ptr().add(state.default_paths_offset) as *const u8,
            expected_path.len()
        )
    };
    
    if actual_path != expected_path.as_bytes() {
        eprintln!(
            "FAILED: Expected \"{}\", got \"{}\" at line {}",
            expected_path,
            String::from_utf8_lossy(actual_path),
            301
        );
        process::exit(1);
    }

    libtree_state_free(&mut state);
}
pub fn test_print_functions() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: [0 as char; 32],
    };
    
    libtree_state_init(&mut state);
    state.color = 0;
    
    print!("Testing tree_preamble depth 0: ");
    tree_preamble(&mut state, 0);
    println!("(no output expected)");
    
    state.found_all_needed[0] = 1 as char;
    
    print!("Testing tree_preamble depth 1: ");
    tree_preamble(&mut state, 1);
    println!("(should show tree characters)");
    
    libtree_state_free(&mut state);
}

pub fn test_performance_stress() {
    let mut vec = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut vec);
    
    for i in 0..10000 {
        small_vec_u64_append(&mut vec, i);
    }

    {
        if 10000 != vec.n {
            println!("FAILED: Expected {}, got {} at line {}", 10000, vec.n, 453);
            exit(1);
        }
    }

    {
        if 9999 != vec.p.as_ref().unwrap()[9999] {
            println!("FAILED: Expected {}, got {} at line {}", 9999, vec.p.as_ref().unwrap()[9999], 454);
            exit(1);
        }
    }

    small_vec_u64_free(&mut vec);
}

pub fn test_memory_allocation_edge_cases() {
    let mut vec = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 16,
    };
    small_vec_u64_init(&mut vec);
    
    for i in 0..=16 {
        small_vec_u64_append(&mut vec, i);
    }

    {
        if 17 != vec.n {
            println!("FAILED: Expected {}, got {} at line {}", 17, vec.n, 649);
            exit(1);
        }
    }
    
    {
        if vec.p.is_none() {
            println!("FAILED: Assertion failed at line {}", 650);
            exit(1);
        }
    }
    
    for i in 17..100 {
        small_vec_u64_append(&mut vec, i);
    }

    {
        if 100 != vec.n {
            println!("FAILED: Expected {}, got {} at line {}", 100, vec.n, 657);
            exit(1);
        }
    }
    
    small_vec_u64_free(&mut vec);
}
pub fn test_ld_library_path_semicolons() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT { 
            arr: None,
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT { 
            arr: None,
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: usize::MAX,
        default_paths_offset: usize::MAX,
        ld_so_conf_offset: usize::MAX,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    env::set_var("LD_LIBRARY_PATH", "/path1;/path2;/path3");
    parse_ld_library_path(&mut state);

    // First assertion
    {
        if state.ld_library_path_offset == usize::MAX {
            eprintln!("FAILED: Assertion failed at line 724");
            process::exit(1);
        }
    }

    // Second assertion
    {
        if let Some(arr) = &state.string_table.arr {
            // Convert the slice of char to a String
            let path_str: String = arr[state.ld_library_path_offset..].iter().collect();
            if !path_str.contains("/path1:/path2:/path3") {
                eprintln!("FAILED: Assertion failed at line 726");
                process::exit(1);
            }
        } else {
            eprintln!("FAILED: string_table.arr is None");
            process::exit(1);
        }
    }

    libtree_state_free(&mut state);
}
pub fn test_small_vec_free_edge_case() {
    let mut vec = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut vec);
    small_vec_u64_append(&mut vec, 1);

    // First assertion: vec.n <= 16
    {
        if !(vec.n <= 16) {
            println!("FAILED: Assertion failed at line {}", 852);
            process::exit(1);
        }
    }

    // Second assertion: vec.p == vec.buf (translated to checking if p is None)
    {
        if vec.p.is_some() {
            println!("FAILED: Expected {:?}, got {:?} at line {}", Option::<Box<[u64]>>::None, vec.p, 853);
            process::exit(1);
        }
    }

    small_vec_u64_free(&mut vec);

    // Fill the vector beyond its small buffer capacity
    for i in 0..(16 + 1) {
        small_vec_u64_append(&mut vec, i as u64);
    }

    // Third assertion: vec.p != vec.buf (translated to checking if p is Some)
    {
        if vec.p.is_none() {
            println!("FAILED: Assertion failed at line {}", 863);
            process::exit(1);
        }
    }

    small_vec_u64_free(&mut vec);
}
pub fn test_variable_interpolation() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Option::None,
            n: 0,
            capacity: 0,
        },
        visited: VisitedFileArrayT {
            arr: Option::None,
            n: 0,
            capacity: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    state.PLATFORM = Some("x86_64".to_string());
    state.LIB = Some("lib".to_string());
    state.OSNAME = Some("Linux".to_string());
    state.OSREL = Some("5.4.0".to_string());
    
    string_table_store(&mut state.string_table, "/usr/$LIB/$PLATFORM");
    
    let offset = 0;
    let result = interpolate_variables(&mut state, offset, "/tmp");
    
    {
        if 1 != result {
            println!("FAILED: Expected {}, got {} at line {}", 1, result, 396);
            exit(1);
        }
    }
    
    // Access the string table data directly as in C code
    let string_table_data = state.string_table.arr.as_ref().unwrap();
    let interpolated_start = (string_table_data.len() - "/usr/lib/x86_64".len()) - 1;
    let interpolated_chars = &string_table_data[interpolated_start..];
    let interpolated_string: String = interpolated_chars.iter().collect();
    
    {
        if "/usr/lib/x86_64" != interpolated_string {
            println!("FAILED: Expected \"{}\", got \"{}\" at line {}", "/usr/lib/x86_64", interpolated_string, 400);
            exit(1);
        }
    }
    
    libtree_state_free(&mut state);
}
pub fn test_integration_workflow() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            n: 0,
            capacity: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            n: 0,
            capacity: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: usize::MAX,
        default_paths_offset: usize::MAX,
        ld_so_conf_offset: usize::MAX,
        found_all_needed: ['\0'; 32],
    };

    libtree_state_init(&mut state);
    env::set_var("LD_LIBRARY_PATH", "/test/lib");
    parse_ld_library_path(&mut state);
    set_default_paths(&mut state);

    {
        if !(state.ld_library_path_offset != usize::MAX) {
            println!("FAILED: Assertion failed at line {}", 437);
            process::exit(1);
        }
    }

    {
        if !(state.default_paths_offset != usize::MAX) {
            println!("FAILED: Assertion failed at line {}", 438);
            process::exit(1);
        }
    }

    libtree_state_free(&mut state);
}
pub fn test_variable_interpolation_comprehensive() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            capacity: 65536,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 1024,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    state.PLATFORM = Some("x86_64".to_string());
    state.LIB = Some("lib".to_string());
    state.OSNAME = Some("Linux".to_string());
    state.OSREL = Some("5.4.0".to_string());
    
    string_table_store(&mut state.string_table, "/usr/$ORIGIN/test");
    let mut offset = 0;
    let mut result = interpolate_variables(&mut state, offset, "/home/user");
    
    if 1 != result {
        println!("FAILED: Expected {}, got {} at line {}", 1, result, 613);
        exit(1);
    }
    
    string_table_store(&mut state.string_table, "/usr/${LIB}/${PLATFORM}");
    offset = (state.string_table.n - "/usr/${LIB}/${PLATFORM}".len()) - 1;
    result = interpolate_variables(&mut state, offset, "/tmp");
    
    if 1 != result {
        println!("FAILED: Expected {}, got {} at line {}", 1, result, 620);
        exit(1);
    }
    
    string_table_store(&mut state.string_table, "/usr/$OSNAME/$OSREL");
    offset = (state.string_table.n - "/usr/$OSNAME/$OSREL".len()) - 1;
    result = interpolate_variables(&mut state, offset, "/tmp");
    
    if 1 != result {
        println!("FAILED: Expected {}, got {} at line {}", 1, result, 627);
        exit(1);
    }
    
    string_table_store(&mut state.string_table, "/usr/$UNKNOWN/test");
    offset = (state.string_table.n - "/usr/$UNKNOWN/test".len()) - 1;
    result = interpolate_variables(&mut state, offset, "/tmp");
    
    if 0 != result {
        println!("FAILED: Expected {}, got {} at line {}", 0, result, 634);
        exit(1);
    }
    
    libtree_state_free(&mut state);
}
pub fn test_parse_ld_so_conf_function() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    create_test_config_file("test_ld_so.conf", "/usr/local/lib\n/opt/lib\n");
    state.ld_conf_file = Some("test_ld_so.conf".to_string());
    parse_ld_so_conf(&mut state);
    
    // First assertion
    if state.ld_so_conf_offset == usize::MAX {
        eprintln!("FAILED: Assertion failed at line 744");
        exit(1);
    }
    
    let ld_conf_str = &state.string_table.arr.as_ref().unwrap()[state.ld_so_conf_offset..];
    
    // Second assertion
    if ld_conf_str.is_empty() {
        eprintln!("FAILED: Assertion failed at line 747");
        exit(1);
    }
    
    // Third assertion
    if !ld_conf_str.is_empty() && ld_conf_str.last() == Some(&':') {
        eprintln!("FAILED: Assertion failed at line 748");
        exit(1);
    }
    
    libtree_state_free(&mut state);
    fs::remove_file("test_ld_so.conf").unwrap();
}
pub fn test_print_line_function_coverage() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [usize::MAX; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };

    libtree_state_init(&mut state);
    for i in 0..32 {
        state.rpath_offsets[i] = usize::MAX;
        state.found_all_needed[i] = '\0';
    }

    state.color = 1;
    println!("Testing print_line function:");
    
    let reason_input = FoundT { how: HowT::INPUT, depth: 0 };
    println!("Testing reason type INPUT: ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_input.clone(), &mut state);
    
    let reason_direct = FoundT { how: HowT::DIRECT, depth: 0 };
    println!("Testing reason type DIRECT: ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_direct.clone(), &mut state);
    
    let reason_rpath = FoundT { how: HowT::RPATH, depth: 1 };
    println!("Testing reason type RPATH (same depth): ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_rpath.clone(), &mut state);
    
    let reason_rpath_diff = FoundT { how: HowT::RPATH, depth: 0 };
    println!("Testing reason type RPATH (different depth): ");
    print_line(2, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_rpath_diff.clone(), &mut state);
    
    let reason_ldpath = FoundT { how: HowT::LD_LIBRARY_PATH, depth: 0 };
    println!("Testing reason type LD_LIBRARY_PATH: ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_ldpath.clone(), &mut state);
    
    let reason_runpath = FoundT { how: HowT::RUNPATH, depth: 0 };
    println!("Testing reason type RUNPATH: ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_runpath.clone(), &mut state);
    
    state.ld_conf_file = Some("/etc/ld.so.conf".to_string());
    let reason_ldconf = FoundT { how: HowT::LD_SO_CONF, depth: 0 };
    println!("Testing reason type LD_SO_CONF: ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_ldconf.clone(), &mut state);
    
    let reason_default = FoundT { how: HowT::DEFAULT, depth: 0 };
    println!("Testing reason type DEFAULT: ");
    print_line(1, "/test/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_default.clone(), &mut state);
    
    state.color = 0;
    println!("Testing without colors: ");
    print_line(0, "test.so", "\x1b[1;36m", "\x1b[0;36m", false, reason_input.clone(), &mut state);
    
    state.color = 1;
    println!("Testing with path highlighting: ");
    print_line(1, "/path/to/lib.so", "\x1b[1;36m", "\x1b[0;36m", true, reason_input.clone(), &mut state);
    
    libtree_state_free(&mut state);
}
pub fn test_error_conditions() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            n: 0,
            capacity: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            n: 0,
            capacity: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);

    {
        if is_in_exclude_list(Some("")) != 0 {
            println!("FAILED: Expected {}, got {} at line {}", 0, is_in_exclude_list(Some("")), 411);
            exit(1);
        }
    }

    let mut table = StringTableT {
        arr: None,
        n: 0,
        capacity: 0,
    };

    string_table_maybe_grow(&mut table, 10);

    {
        if !(table.capacity >= 20) {
            println!("FAILED: Assertion failed at line {}", 418);
            exit(1);
        }
    }

    libtree_state_free(&mut state);
}
pub fn test_recurse_32bit_elf() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            n: 0,
            capacity: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            n: 0,
            capacity: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    let mut f = File::create("test_32bit.elf").expect("Failed to create file");

    let elf_header: [u8; 52] = [
        0x7f, b'E', b'L', b'F', 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 52, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 52, 0, 32, 0, 1, 0, 0, 0,
        0, 0, 0, 0
    ];
    f.write_all(&elf_header).expect("Failed to write ELF header");

    let phdr: [u8; 32] = [
        1, 0, 0, 0, 0x00, 0x10, 0, 0,
        0x00, 0x80, 0x04, 0x08, 0x00, 0x80, 0x04, 0x08,
        0x00, 0x10, 0, 0, 0x00, 0x10, 0, 0,
        5, 0, 0, 0, 0x00, 0x10, 0, 0
    ];
    f.write_all(&phdr).expect("Failed to write program header");

    drop(f); // Explicitly close the file

    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    let reason = FoundT { how: HowT::INPUT, depth: 0 };
    let result = recurse("test_32bit.elf", 0, &mut state, compat, reason).expect("recurse failed");

    if !(result == 0 || result == 31) {
        eprintln!("FAILED: Assertion failed at line {}", 1758);
        std::process::exit(1);
    }

    libtree_state_free(&mut state);
    remove_file("test_32bit.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_no_pt_load() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    let mut f = File::create("test_no_pt_load.elf").expect("Failed to create file");

    let mut elf_header = [0u8; 64];
    elf_header[0] = 0x7f;
    elf_header[1] = b'E';
    elf_header[2] = b'L';
    elf_header[3] = b'F';
    elf_header[4] = 2;
    elf_header[5] = 1;
    elf_header[6] = 1;
    elf_header[16] = 3;
    elf_header[17] = 0;
    elf_header[18] = 0x3e;
    elf_header[19] = 0;
    elf_header[20] = 1;
    elf_header[21] = 0;
    elf_header[22] = 0;
    elf_header[23] = 0;
    elf_header[32] = 64;
    elf_header[33..36].copy_from_slice(&[0, 0, 0]);
    elf_header[36..40].copy_from_slice(&[0, 0, 0, 0]);
    elf_header[52] = 64;
    elf_header[53] = 0;
    elf_header[54] = 56;
    elf_header[55] = 0;
    elf_header[56] = 1;
    elf_header[57] = 0;

    f.write_all(&elf_header).expect("Failed to write ELF header");

    let mut phdr = [0u8; 56];
    phdr[0] = 2;
    phdr[1..4].copy_from_slice(&[0, 0, 0]);
    phdr[4] = 6;
    phdr[5..8].copy_from_slice(&[0, 0, 0]);
    phdr[8] = 0x00;
    phdr[9] = 0x10;
    phdr[10..16].copy_from_slice(&[0, 0, 0, 0, 0, 0]);

    f.write_all(&phdr).expect("Failed to write program header");
    drop(f); // Equivalent to fclose

    let compat = CompatT {
        any: '\x01',
        class: 0,
        machine: 0,
    };
    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };

    let result = recurse("test_no_pt_load.elf", 0, &mut state, compat, reason).expect("recurse failed");

    if 29 != result {
        println!("FAILED: Expected {}, got {} at line {}", 29, result, 1812);
        exit(1);
    }

    libtree_state_free(&mut state);
    remove_file("test_no_pt_load.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_with_dynamic_section() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    let mut f = File::create("test_dynamic.elf").expect("Failed to create file");

    // Write ELF header
    let mut elf_header = [0u8; 64];
    elf_header[0] = 0x7f;
    elf_header[1] = b'E';
    elf_header[2] = b'L';
    elf_header[3] = b'F';
    elf_header[4] = 2;
    elf_header[5] = 1;
    elf_header[6] = 1;
    elf_header[16] = 3;
    elf_header[17] = 0;
    elf_header[18] = 0x3e;
    elf_header[19] = 0;
    elf_header[20] = 1;
    elf_header[21] = 0;
    elf_header[22] = 0;
    elf_header[23] = 0;
    elf_header[32] = 64;
    elf_header[33] = 0;
    elf_header[34] = 0;
    elf_header[35] = 0;
    elf_header[36] = 0;
    elf_header[37] = 0;
    elf_header[38] = 0;
    elf_header[39] = 0;
    elf_header[52] = 64;
    elf_header[53] = 0;
    elf_header[54] = 56;
    elf_header[55] = 0;
    elf_header[56] = 2;
    elf_header[57] = 0;
    f.write_all(&elf_header).expect("Failed to write ELF header");

    // Write program header 1
    let mut phdr1 = [0u8; 56];
    phdr1[0] = 1;
    phdr1[4] = 5;
    phdr1[16] = 0x00;
    phdr1[17] = 0x00;
    phdr1[18] = 0x40;
    phdr1[24] = 0x00;
    phdr1[25] = 0x00;
    phdr1[26] = 0x40;
    phdr1[32] = 0x00;
    phdr1[33] = 0x10;
    phdr1[40] = 0x00;
    phdr1[41] = 0x10;
    f.write_all(&phdr1).expect("Failed to write program header 1");

    // Write program header 2
    let mut phdr2 = [0u8; 56];
    phdr2[0] = 2;
    phdr2[4] = 6;
    phdr2[8] = 0x00;
    phdr2[9] = 0x02;
    phdr2[16] = 0x00;
    phdr2[17] = 0x02;
    phdr2[18] = 0x40;
    phdr2[24] = 0x00;
    phdr2[25] = 0x02;
    phdr2[26] = 0x40;
    phdr2[32] = 16;
    phdr2[40] = 16;
    f.write_all(&phdr2).expect("Failed to write program header 2");

    // Pad with zeros until 0x200
    let current_pos = f.seek(SeekFrom::Current(0)).expect("Failed to get file position");
    for _ in current_pos..0x200 {
        f.write_all(&[0]).expect("Failed to write padding");
    }

    // Write DT_NULL
    let dt_null = [0u8; 16];
    f.write_all(&dt_null).expect("Failed to write DT_NULL");

    drop(f); // Close the file

    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    let reason = FoundT { how: HowT::INPUT, depth: 0 };
    let result = recurse("test_dynamic.elf", 0, &mut state, compat, reason).expect("recurse failed");

    if 23 != result {
        eprintln!("FAILED: Expected 23, got {} at line 1914", result);
        exit(1);
    }

    libtree_state_free(&mut state);
    remove_file("test_dynamic.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_invalid_dynamic_seek() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    let mut f = File::create("test_invalid_dynamic.elf").expect("Failed to create file");

    let mut elf_header = [0u8; 64];
    elf_header[0] = 0x7f;
    elf_header[1] = b'E';
    elf_header[2] = b'L';
    elf_header[3] = b'F';
    elf_header[4] = 2;
    elf_header[5] = 1;
    elf_header[6] = 1;
    elf_header[16] = 3;
    elf_header[17] = 0;
    elf_header[18] = 0x3e;
    elf_header[19] = 0;
    elf_header[20] = 1;
    elf_header[21] = 0;
    elf_header[22] = 0;
    elf_header[23] = 0;
    elf_header[32] = 64;
    elf_header[33] = 0;
    elf_header[34] = 0;
    elf_header[35] = 0;
    elf_header[36] = 0;
    elf_header[37] = 0;
    elf_header[38] = 0;
    elf_header[39] = 0;
    elf_header[52] = 64;
    elf_header[53] = 0;
    elf_header[54] = 56;
    elf_header[55] = 0;
    elf_header[56] = 2;
    elf_header[57] = 0;
    f.write_all(&elf_header).expect("Failed to write ELF header");

    let mut phdr1 = [0u8; 56];
    phdr1[0] = 1;
    phdr1[1] = 0;
    phdr1[2] = 0;
    phdr1[3] = 0;
    phdr1[4] = 5;
    phdr1[5] = 0;
    phdr1[6] = 0;
    phdr1[7] = 0;
    phdr1[16] = 0x00;
    phdr1[17] = 0x00;
    phdr1[18] = 0x40;
    phdr1[19] = 0;
    phdr1[20] = 0;
    phdr1[21] = 0;
    phdr1[22] = 0;
    phdr1[23] = 0;
    phdr1[24] = 0x00;
    phdr1[25] = 0x00;
    phdr1[26] = 0x40;
    phdr1[27] = 0;
    phdr1[28] = 0;
    phdr1[29] = 0;
    phdr1[30] = 0;
    phdr1[31] = 0;
    phdr1[32] = 0x00;
    phdr1[33] = 0x10;
    phdr1[34] = 0;
    phdr1[35] = 0;
    phdr1[36] = 0;
    phdr1[37] = 0;
    phdr1[38] = 0;
    phdr1[39] = 0;
    phdr1[40] = 0x00;
    phdr1[41] = 0x10;
    phdr1[42] = 0;
    phdr1[43] = 0;
    phdr1[44] = 0;
    phdr1[45] = 0;
    phdr1[46] = 0;
    phdr1[47] = 0;
    f.write_all(&phdr1).expect("Failed to write phdr1");

    let mut phdr2 = [0u8; 56];
    phdr2[0] = 2;
    phdr2[1] = 0;
    phdr2[2] = 0;
    phdr2[3] = 0;
    phdr2[4] = 6;
    phdr2[5] = 0;
    phdr2[6] = 0;
    phdr2[7] = 0;
    phdr2[8] = 0xFF;
    phdr2[9] = 0xFF;
    phdr2[10] = 0xFF;
    phdr2[11] = 0xFF;
    phdr2[12] = 0xFF;
    phdr2[13] = 0xFF;
    phdr2[14] = 0xFF;
    phdr2[15] = 0x7F;
    f.write_all(&phdr2).expect("Failed to write phdr2");

    drop(f); // Equivalent to fclose()

    let compat = CompatT {
        any: '\x01',
        class: 0,
        machine: 0,
    };
    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };

    let result = recurse("test_invalid_dynamic.elf", 0, &mut state, compat, reason).expect("recurse failed");

    if 21 != result {
        println!("FAILED: Expected {}, got {} at line {}", 21, result, 1986);
        exit(1);
    }

    libtree_state_free(&mut state);
    remove_file("test_invalid_dynamic.elf").expect("Failed to remove file");
}
pub fn test_elf_file_validation() {
    create_test_elf_file("valid.elf", true);
    create_test_elf_file("invalid.elf", false);
    
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    let compat = CompatT {
        any: '\x01',
        class: 0,
        machine: 0,
    };
    
    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };
    
    libtree_state_init(&mut state);
    
    let result = recurse("invalid.elf", 0, &mut state, compat.clone(), reason.clone());
    if let Ok(res) = result {
        if 11 != res {
            println!("FAILED: Expected {}, got {} at line {}", 11, res, 321);
            std::process::exit(1);
        }
    } else {
        println!("FAILED: Expected 11, got error at line 321");
        std::process::exit(1);
    }
    
    let result = recurse("nonexistent.elf", 0, &mut state, compat, reason);
    if let Ok(res) = result {
        if 31 != res {
            println!("FAILED: Expected {}, got {} at line {}", 31, res, 325);
            std::process::exit(1);
        }
    } else {
        println!("FAILED: Expected 31, got error at line 325");
        std::process::exit(1);
    }
    
    libtree_state_free(&mut state);
    std::fs::remove_file("valid.elf").unwrap();
    std::fs::remove_file("invalid.elf").unwrap();
}
pub fn test_elf_validation_errors() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    let compat = CompatT {
        any: '\x01',
        class: 0,
        machine: 0,
    };
    
    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };
    
    libtree_state_init(&mut state);
    
    // Test invalid_class.elf
    create_test_elf_file("invalid_class.elf", true);
    {
        let mut f = OpenOptions::new()
            .read(true)
            .write(true)
            .open("invalid_class.elf")
            .expect("Failed to open file");
        f.seek(SeekFrom::Start(4)).expect("Seek failed");
        f.write_all(&[0x03]).expect("Write failed");
    }
    
    let result = recurse("invalid_class.elf", 0, &mut state, compat.clone(), reason.clone()).expect("recurse failed");
    if 12 != result {
        println!("FAILED: Expected {}, got {} at line {}", 12, result, 581);
        exit(1);
    }
    
    // Test invalid_data.elf
    create_test_elf_file("invalid_data.elf", true);
    {
        let mut f = OpenOptions::new()
            .read(true)
            .write(true)
            .open("invalid_data.elf")
            .expect("Failed to open file");
        f.seek(SeekFrom::Start(5)).expect("Seek failed");
        f.write_all(&[0x03]).expect("Write failed");
    }
    
    let result = recurse("invalid_data.elf", 0, &mut state, compat, reason).expect("recurse failed");
    if 13 != result {
        println!("FAILED: Expected {}, got {} at line {}", 13, result, 591);
        exit(1);
    }
    
    libtree_state_free(&mut state);
    std::fs::remove_file("invalid_class.elf").expect("Failed to remove file");
    std::fs::remove_file("invalid_data.elf").expect("Failed to remove file");
}
pub fn test_comprehensive_integration() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: usize::MAX,
        default_paths_offset: usize::MAX,
        ld_so_conf_offset: usize::MAX,
        found_all_needed: ['\0'; 32],
    };

    libtree_state_init(&mut state);
    state.PLATFORM = Some("x86_64".to_string());
    state.LIB = Some("lib".to_string());
    state.OSNAME = Some("Linux".to_string());
    state.OSREL = Some("5.4.0".to_string());
    state.ld_conf_file = Some("/etc/ld.so.conf".to_string());
    state.color = 1;
    state.verbosity = 3;
    state.path = 1;
    state.max_depth = 5;

    create_test_config_file("test_integration_ld.conf", "/usr/local/lib\ninclude /etc/ld.so.conf.d/*.conf\n");
    state.ld_conf_file = Some("test_integration_ld.conf".to_string());

    env::set_var("LD_LIBRARY_PATH", "/custom/lib:/another/lib");

    parse_ld_so_conf(&mut state);
    parse_ld_library_path(&mut state);
    set_default_paths(&mut state);

    if state.ld_so_conf_offset == usize::MAX {
        eprintln!("FAILED: Assertion failed at line 899");
        process::exit(1);
    }

    if state.ld_library_path_offset == usize::MAX {
        eprintln!("FAILED: Assertion failed at line 900");
        process::exit(1);
    }

    if state.default_paths_offset == usize::MAX {
        eprintln!("FAILED: Assertion failed at line 901");
        process::exit(1);
    }

    libtree_state_free(&mut state);
    fs::remove_file("test_integration_ld.conf").unwrap();
}
pub fn test_recurse_elf_with_program_headers_no_dynamic() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Option::None,
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Option::None,
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    create_elf_with_program_headers("test_elf_no_dynamic.elf", false).expect("Failed to create ELF file");

    let compat = CompatT {
        any: '\x01',
        class: 0,
        machine: 0,
    };

    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };

    let result = recurse("test_elf_no_dynamic.elf", 0, &mut state, compat, reason)
        .expect("Recurse failed");

    if result != 0 {
        println!("FAILED: Expected {}, got {} at line {}", 0, result, 1501);
        std::process::exit(1);
    }

    libtree_state_free(&mut state);
    std::fs::remove_file("test_elf_no_dynamic.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_wrong_type() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    create_test_elf_file("test_wrong_type.elf", true);

    let mut f = std::fs::OpenOptions::new()
        .read(true)
        .write(true)
        .open("test_wrong_type.elf")
        .expect("Failed to open file");
    
    f.seek(std::io::SeekFrom::Start(16)).expect("Failed to seek");
    f.write_all(&[4, 0]).expect("Failed to write");

    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    let reason = FoundT { how: HowT::INPUT, depth: 0 };
    let result = recurse("test_wrong_type.elf", 0, &mut state, compat, reason).expect("recurse failed");

    if 17 != result {
        println!("FAILED: Expected {}, got {} at line {}", 17, result, 1548);
        std::process::exit(1);
    }

    libtree_state_free(&mut state);
    std::fs::remove_file("test_wrong_type.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_incompatible_arch() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    create_test_elf_file("test_wrong_arch.elf", true);
    
    let mut file = std::fs::OpenOptions::new()
        .read(true)
        .write(true)
        .open("test_wrong_arch.elf")
        .expect("Failed to open file");
    
    file.seek(std::io::SeekFrom::Start(18)).expect("Seek failed");
    file.write_all(&[0xFF, 0xFF]).expect("Write failed");

    let compat = CompatT {
        any: '\0',
        class: 2,
        machine: 0x3e,
    };
    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };
    let result = recurse("test_wrong_arch.elf", 0, &mut state, compat, reason).expect("Recurse failed");

    if 32 != result {
        println!("FAILED: Expected {}, got {} at line {}", 32, result, 1572);
        std::process::exit(1);
    }

    libtree_state_free(&mut state);
    std::fs::remove_file("test_wrong_arch.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_incompatible_bits() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Option::None,
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Option::None,
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    
    create_test_elf_file("test_wrong_bits.elf", true);
    
    let mut f = OpenOptions::new()
        .read(true)
        .write(true)
        .open("test_wrong_bits.elf")
        .expect("Failed to open file");
    
    f.seek(SeekFrom::Start(4)).expect("Seek failed");
    f.write_all(&[1]).expect("Write failed");
    
    let compat = CompatT {
        any: '\0',
        class: 2,
        machine: 0,
    };
    
    let reason = FoundT {
        how: HowT::INPUT,
        depth: 0,
    };
    
    let result = recurse("test_wrong_bits.elf", 0, &mut state, compat, reason)
        .expect("recurse failed");
    
    if 15 != result {
        println!("FAILED: Expected {}, got {} at line {}", 15, result, 1596);
        exit(1);
    }
    
    libtree_state_free(&mut state);
    std::fs::remove_file("test_wrong_bits.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_invalid_phoff() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    
    create_test_elf_file("test_invalid_phoff.elf", true);
    
    let mut file = OpenOptions::new()
        .read(true)
        .write(true)
        .open("test_invalid_phoff.elf")
        .expect("Failed to open file");
    
    file.seek(SeekFrom::Start(32)).expect("Failed to seek");
    
    // Write invalid phoff values (0xFF...0x7F)
    for _ in 0..7 {
        file.write_all(&[0xFF]).expect("Failed to write");
    }
    file.write_all(&[0x7F]).expect("Failed to write");
    
    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    let reason = FoundT { how: HowT::INPUT, depth: 0 };
    let result = recurse("test_invalid_phoff.elf", 0, &mut state, compat, reason).expect("recurse failed");
    
    if result != 18 {
        println!("FAILED: Expected {}, got {} at line {}", 18, result, 1621);
        exit(1);
    }
    
    libtree_state_free(&mut state);
    std::fs::remove_file("test_invalid_phoff.elf").expect("Failed to remove file");
}
pub fn test_recurse_elf_wrong_endianness() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    create_test_elf_file("test_wrong_endian.elf", true);
    
    let mut f = std::fs::OpenOptions::new()
        .read(true)
        .write(true)
        .open("test_wrong_endian.elf")
        .expect("Failed to open file");
    
    f.seek(std::io::SeekFrom::Start(5)).expect("Seek failed");
    
    let host_endian = host_is_little_endian();
    f.write_all(&[if host_endian { 2 } else { 1 }]).expect("Write failed");
    
    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    let reason = FoundT { how: HowT::INPUT, depth: 0 };
    
    let result = recurse("test_wrong_endian.elf", 0, &mut state, compat, reason).expect("recurse failed");
    
    if 16 != result {
        println!("FAILED: Expected {}, got {} at line {}", 16, result, 1525);
        std::process::exit(1);
    }
    
    libtree_state_free(&mut state);
    std::fs::remove_file("test_wrong_endian.elf").expect("Failed to remove file");
}
pub fn test_apply_exclude_list_function() {
    let mut state = std::mem::MaybeUninit::<LibtreeStateT>::uninit();
    unsafe {
        libtree_state_init(&mut *state.as_mut_ptr());
    }
    let mut state = unsafe { state.assume_init() };

    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);

    string_table_store(&mut state.string_table, "libc.so.6");
    small_vec_u64_append(&mut needed_buf_offsets, 0);
    string_table_store(&mut state.string_table, "libcustom.so");
    small_vec_u64_append(&mut needed_buf_offsets, ("libc.so.6".len() + 1) as u64);  // Added cast to u64

    let mut needed_not_found = 2;
    apply_exclude_list(&mut needed_not_found, &mut needed_buf_offsets, &state);

    if needed_not_found != 1 {
        println!("FAILED: Expected {}, got {} at line {}", 1, needed_not_found, 559);
        exit(1);
    }

    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_absolute_paths_function() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    state.color = 0;
    state.verbosity = 0;
    let compat = CompatT { any: 1 as char, class: 0, machine: 0 };
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);

    string_table_store(&mut state.string_table, "/lib/libc.so.6");
    small_vec_u64_append(&mut needed_buf_offsets, 0);
    
    string_table_store(&mut state.string_table, "/nonexistent/path/lib.so");
    small_vec_u64_append(&mut needed_buf_offsets, ("/lib/libc.so.6".len() + 1) as u64);
    
    string_table_store(&mut state.string_table, "relative_lib.so");
    small_vec_u64_append(
        &mut needed_buf_offsets,
        (("/lib/libc.so.6".len() + 1 + "/nonexistent/path/lib.so".len()) + 1) as u64,
    );

    let mut needed_not_found = 3;
    let depth = 1;
    
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }

    let result = check_absolute_paths(
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat,
    ).unwrap();

    if !(result != 0 || needed_not_found < 3) {
        eprintln!("FAILED: Assertion failed at line {}", 942);
        std::process::exit(1);
    }

    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_absolute_paths_relative_paths() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Option::None,
            n: 0,
            capacity: 4096,
        },
        visited: VisitedFileArrayT {
            arr: Option::None,
            n: 0,
            capacity: 1024,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    state.color = 0;
    state.verbosity = 0;
    let compat = CompatT { any: 1 as char, class: 0, machine: 0 };
    
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    
    string_table_store(&mut state.string_table, "relative/path/lib.so");
    small_vec_u64_append(&mut needed_buf_offsets, 0);
    string_table_store(&mut state.string_table, "./local/lib.so");
    small_vec_u64_append(&mut needed_buf_offsets, ("relative/path/lib.so".len() + 1) as u64);
    
    let mut needed_not_found = 2;
    let depth = 0;
    
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }
    
    let result = check_absolute_paths(
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat.clone(),
    ).unwrap();
    
    if 28 != result {
        println!("FAILED: Expected {}, got {} at line {}", 28, result, 1095);
        std::process::exit(1);
    }
    
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_absolute_paths_no_slash() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    
    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    
    string_table_store(&mut state.string_table, "libc.so.6");
    small_vec_u64_append(&mut needed_buf_offsets, 0);
    
    string_table_store(&mut state.string_table, "libm.so.1");
    small_vec_u64_append(&mut needed_buf_offsets, "libc.so.6".len() as u64 + 1);
    
    let mut needed_not_found = 2;
    let depth = 0;
    
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }
    
    let result = match check_absolute_paths(&mut needed_not_found, &mut needed_buf_offsets, depth, &mut state, compat.clone()) {
        Ok(val) => val,
        Err(_) => {
            println!("Error occurred in check_absolute_paths");
            std::process::exit(1);
        }
    };
    
    if result != 0 {
        println!("FAILED: Expected {}, got {:?} at line {}", 0, result, 1128);
        std::process::exit(1);
    }
    
    if needed_not_found != 2 {
        println!("FAILED: Expected {}, got {} at line {}", 2, needed_not_found, 1130);
        std::process::exit(1);
    }
    
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_search_paths_function() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    state.color = 0;
    state.verbosity = 0;
    let compat = CompatT { any: '1', class: 0, machine: 0 };
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    string_table_store(&mut state.string_table, "/usr/lib:/lib:/usr/local/lib");
    let search_path_offset = 0;
    string_table_store(&mut state.string_table, "libc.so.6");
    small_vec_u64_append(&mut needed_buf_offsets, ("/usr/lib:/lib:/usr/local/lib".len() + 1) as u64);
    string_table_store(&mut state.string_table, "nonexistent.so");
    small_vec_u64_append(
        &mut needed_buf_offsets,
        (("/usr/lib:/lib:/usr/local/lib".len() + 1 + "libc.so.6".len()) + 1) as u64,
    );
    let mut needed_not_found = 2;
    let depth = 1;
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }

    let reason = FoundT {
        how: HowT::LD_LIBRARY_PATH,
        depth: 0,
    };
    let result = check_search_paths(
        reason,
        search_path_offset,
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat,
    ).unwrap();
    if !(result == 0 || result == 28) {
        println!("FAILED: Assertion failed at line 985");
        std::process::exit(1);
    }
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_search_paths_edge_cases() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    state.color = 0;
    state.verbosity = 0;
    let compat = CompatT { any: '\x01', class: 0, machine: 0 };  // Changed 1 to '\x01' for char
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    string_table_store(&mut state.string_table, "");
    let search_path_offset = 0;
    string_table_store(&mut state.string_table, "test.so");
    small_vec_u64_append(&mut needed_buf_offsets, 1);
    let mut needed_not_found = 1;
    let depth = 0;
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }

    let reason = FoundT { how: HowT::DEFAULT, depth: 0 };
    let result = check_search_paths(
        reason,
        search_path_offset,
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat,
    );
    
    if let Ok(res) = result {  // Handle Result type properly
        if res < 0 {
            println!("FAILED: Assertion failed at line {}", 1022);
            std::process::exit(1);
        }
    } else {
        println!("FAILED: Error occurred in check_search_paths");
        std::process::exit(1);
    }

    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_search_paths_colon_parsing() {
    let mut state = std::mem::MaybeUninit::<LibtreeStateT>::uninit();
    unsafe { libtree_state_init(&mut *state.as_mut_ptr()); }
    let mut state = unsafe { state.assume_init() };
    state.color = 0;
    state.verbosity = 0;
    let compat = CompatT { any: 1 as char, class: 0, machine: 0 };
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    string_table_store(&mut state.string_table, ":::/usr/lib::/lib64::");
    let search_path_offset: usize = 0;
    string_table_store(&mut state.string_table, "test.so");
    small_vec_u64_append(
        &mut needed_buf_offsets, 
        (":::/usr/lib::/lib64::".len() + 1) as u64
    );
    let mut needed_not_found: usize = 1;
    let depth: usize = 0;
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }

    let reason = FoundT { how: HowT::RPATH, depth: 0 };
    let result = check_search_paths(
        reason,
        search_path_offset,
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat,
    );
    
    if result.is_err() || result.unwrap() < 0 {
        println!("FAILED: Assertion failed at line {}", 1059);
        std::process::exit(1);
    }

    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_search_paths_long_paths() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);
    
    let compat = CompatT { any: '\x01', class: 0, machine: 0 };
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    
    let mut long_path = vec![b'a'; 4096 + 100 - 1];
    long_path.push(b'\0');
    let long_path_str = unsafe { std::str::from_utf8_unchecked(&long_path) };
    string_table_store(&mut state.string_table, long_path_str);
    
    let search_path_offset = 0;
    string_table_store(&mut state.string_table, "test.so");
    
    small_vec_u64_append(&mut needed_buf_offsets, long_path_str.len() as u64);
    
    let mut needed_not_found = 1;
    let depth = 0;
    
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }
    
    let reason = FoundT {
        how: HowT::RUNPATH,
        depth: 0,
    };
    
    let result = check_search_paths(
        reason,
        search_path_offset,
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat.clone(),
    );
    
    if let Ok(res) = result {
        if res < 0 {
            println!("FAILED: Assertion failed at line {}", 1169);
            std::process::exit(1);
        }
    } else {
        println!("FAILED: Error in check_search_paths");
        std::process::exit(1);
    }
    
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_check_search_paths_separator_handling() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: Option::None,
        max_depth: 0,
        string_table: StringTableT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: Some(Vec::new()),
            capacity: 0,
            n: 0,
        },
        PLATFORM: Option::None,
        LIB: Option::None,
        OSNAME: Option::None,
        OSREL: Option::None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    libtree_state_init(&mut state);

    let compat = CompatT { any: 1 as char, class: 0, machine: 0 };
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: Option::None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);

    string_table_store(&mut state.string_table, "/usr/lib");
    let search_path_offset = 0;
    string_table_store(&mut state.string_table, "test.so");
    small_vec_u64_append(&mut needed_buf_offsets, ("/usr/lib".len() + 1) as u64);
    let mut needed_not_found = 1;
    let depth = 0;

    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }

    let reason = FoundT {
        how: HowT::LD_SO_CONF,
        depth: 0,
    };

    let result = check_search_paths(
        reason,
        search_path_offset,
        &mut needed_not_found,
        &mut needed_buf_offsets,
        depth,
        &mut state,
        compat,
    );

    if result.is_err() || result.unwrap() < 0 {
        println!("FAILED: Assertion failed at line {}", 1204);
        std::process::exit(1);
    }

    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_print_error_basic() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            capacity: 4096,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 1024,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [usize::MAX; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    state.color = 0;
    for i in 0..32 {
        state.rpath_offsets[i] = usize::MAX;
        state.found_all_needed[i] = '\0';
    }

    parse_ld_library_path(&mut state);
    set_default_paths(&mut state);
    
    let conf_path = "/etc/ld.so.conf.d/test.conf:/usr/local/lib";
    string_table_store(&mut state.string_table, conf_path);
    state.ld_so_conf_offset = (state.string_table.capacity - conf_path.len()) - 1;
    state.ld_conf_file = Some("/etc/ld.so.conf".to_string());
    
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    
    let lib1 = "libmissing1.so";
    string_table_store(&mut state.string_table, lib1);
    small_vec_u64_append(&mut needed_buf_offsets, ((state.string_table.capacity - lib1.len()) - 1).try_into().unwrap());
    
    let lib2 = "libmissing2.so";
    string_table_store(&mut state.string_table, lib2);
    small_vec_u64_append(&mut needed_buf_offsets, ((state.string_table.capacity - lib2.len()) - 1).try_into().unwrap());
    
    let needed_not_found = 2;
    let depth = 1;
    state.found_all_needed[depth] = '\x01';
    
    println!("Testing print_error (expect error output):");
    print_error(
        depth,
        needed_not_found,
        &needed_buf_offsets,
        None,
        &mut state,
        false,
    );
    println!("Done testing print_error");
    
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_print_error_with_runpath() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            capacity: 4096,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 1024,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: ['\0'; 32],
    };
    
    libtree_state_init(&mut state);
    state.color = 0;
    env::set_var("LD_LIBRARY_PATH", "/custom/lib:/another/lib");
    parse_ld_library_path(&mut state);
    set_default_paths(&mut state);
    string_table_store(&mut state.string_table, "/ld/conf/path");
    state.ld_so_conf_offset = (state.string_table.n - "/ld/conf/path".len()) - 1;
    state.ld_conf_file = Some("/etc/ld.so.conf".to_string());
    
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    string_table_store(&mut state.string_table, "runpath_lib.so");
    small_vec_u64_append(&mut needed_buf_offsets, ((state.string_table.n - "runpath_lib.so".len()) - 1) as u64);
    
    let needed_not_found = 1;
    let depth = 0;
    for i in 0..32 {
        state.found_all_needed[i] = '\0';
    }
    
    println!("Testing print_error with runpath:");
    let runpath = "/runpath/dir1:/runpath/dir2";
    print_error(depth, needed_not_found, &needed_buf_offsets, Some(runpath), &mut state, false);
    
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
pub fn test_print_error_rpath_stack() {
    let mut state = LibtreeStateT {
        verbosity: 0,
        path: 0,
        color: 0,
        ld_conf_file: None,
        max_depth: 0,
        string_table: StringTableT {
            arr: None,
            capacity: 4096,
            n: 0,
        },
        visited: VisitedFileArrayT {
            arr: None,
            capacity: 1024,
            n: 0,
        },
        PLATFORM: None,
        LIB: None,
        OSNAME: None,
        OSREL: None,
        rpath_offsets: [0; 32],
        ld_library_path_offset: 0,
        default_paths_offset: 0,
        ld_so_conf_offset: 0,
        found_all_needed: [0 as char; 32],
    };

    libtree_state_init(&mut state);
    state.color = 0;
    parse_ld_library_path(&mut state);
    set_default_paths(&mut state);
    
    string_table_store(&mut state.string_table, "/ld/conf");
    state.ld_so_conf_offset = (state.string_table.n - "/ld/conf".len()) - 1;
    state.ld_conf_file = Some("/etc/ld.so.conf".to_string());
    
    string_table_store(&mut state.string_table, "/rpath/depth0:/another/rpath0");
    state.rpath_offsets[0] = (state.string_table.n - "/rpath/depth0:/another/rpath0".len()) - 1;
    
    string_table_store(&mut state.string_table, "/rpath/depth1");
    state.rpath_offsets[1] = (state.string_table.n - "/rpath/depth1".len()) - 1;
    
    string_table_store(&mut state.string_table, "/rpath/depth2:/yet/another");
    state.rpath_offsets[2] = (state.string_table.n - "/rpath/depth2:/yet/another".len()) - 1;
    
    state.rpath_offsets[3] = usize::MAX;
    state.rpath_offsets[4] = usize::MAX;
    
    let mut needed_buf_offsets = SmallVecU64T {
        buf: [0; 16],
        p: None,
        n: 0,
        capacity: 0,
    };
    small_vec_u64_init(&mut needed_buf_offsets);
    
    string_table_store(&mut state.string_table, "rpath_stack_lib.so");
    small_vec_u64_append(
        &mut needed_buf_offsets, 
        ((state.string_table.n - "rpath_stack_lib.so".len()) - 1).try_into().unwrap()
    );
    
    let needed_not_found = 1;
    let depth = 2;
    
    for i in 0..32 {
        state.found_all_needed[i] = 0 as char;
    }
    
    println!("Testing print_error with rpath stack:");
    print_error(depth, needed_not_found, &needed_buf_offsets, None, &mut state, false);
    
    small_vec_u64_free(&mut needed_buf_offsets);
    libtree_state_free(&mut state);
}
