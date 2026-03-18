// Binary crate entry point for libtree

use libtree::{print_tree, MAX_RECURSION_DEPTH};
use std::env;
use std::process;

const VERSION: &str = "3.1.1";

fn print_help() {
    println!("Show the dynamic dependency tree of ELF files");
    println!("Usage: libtree [OPTION]... [--] FILE [FILES]...");
    println!();
    println!("  -h, --help     Print help info");
    println!("      --version  Print version info");
    println!();
    println!("File names starting with '-', for example '-.so', can be specified as follows:");
    println!("  libtree -- -.so");
    println!();
    println!("Locating libs options:");
    println!("  -p, --path       Show the path of libraries instead of the soname");
    println!("  -v               Show libraries skipped by default*");
    println!("  -vv              Show dependencies of libraries skipped by default*");
    println!("  -vvv             Show dependencies of already encountered libraries");
    println!("  --ldconf <path>  Config file for extra search paths [/etc/ld.so.conf]");
    println!("  --max-depth <n>  Limit library traversal to at most n levels of depth");
    println!();
    println!("* For brevity, the following libraries are not shown by default:");
    println!("  ld-linux-aarch64.so, ld-linux-armhf.so, ld-linux-x86-64.so, ld-linux.so,");
    println!("  ld64.so, libc.musl-aarch64.so, libc.musl-armhf.so, libc.musl-i386.so,");
    println!("  libc.musl-x86_64.so, libc.so, libdl.so, libgcc_s.so, libm.so, libstdc++.so");
}

fn print_version() {
    println!("libtree {}", VERSION);
}

fn main() {
    let args: Vec<String> = env::args().collect();

    // Parse arguments
    let mut files: Vec<String> = Vec::new();
    let mut opt_help = false;
    let mut opt_version = false;
    let mut opt_raw = false; // After `--`, treat everything as filenames

    let mut i = 1;
    while i < args.len() {
        let arg = &args[i];

        // Positional args don't start with - or are `-` literal
        if opt_raw || !arg.starts_with('-') || arg == "-" {
            files.push(arg.clone());
            i += 1;
            continue;
        }

        // Now we're in flag land
        if arg.starts_with("--") {
            let flag = &arg[2..];

            // Literal '--'
            if flag.is_empty() {
                opt_raw = true;
                i += 1;
                continue;
            }

            match flag {
                "version" => opt_version = true,
                "help" => opt_help = true,
                "path" | "verbose" | "ldconf" | "max-depth" => {
                    eprintln!("Option --{} is not yet implemented in this minimal version", flag);
                    process::exit(1);
                }
                _ => {
                    eprintln!("Unrecognized flag `--{}`", flag);
                    process::exit(1);
                }
            }
        } else {
            // Short flags
            let chars: Vec<char> = arg[1..].chars().collect();
            for ch in chars {
                match ch {
                    'h' => opt_help = true,
                    'p' | 'v' => {
                        eprintln!("Option -{} is not yet implemented in this minimal version", ch);
                        process::exit(1);
                    }
                    _ => {
                        eprintln!("Unrecognized flag `-{}`", ch);
                        process::exit(1);
                    }
                }
            }
        }

        i += 1;
    }

    // Print help/version if requested or no files specified
    if opt_version {
        print_version();
        return;
    }

    if opt_help || files.is_empty() {
        print_help();
        if files.is_empty() && !opt_help {
            process::exit(1);
        }
        return;
    }

    // Process files
    match print_tree(&files) {
        Ok(_) => {},
        Err(_) => {
            process::exit(1);
        }
    }
}
