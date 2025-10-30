use crate::*;
use std::io::Write;
use std::io;
use std::process::abort;
use std::sync::atomic::Ordering;
pub fn zperror(prefix: Option<&str>) {
    let libzahl_error = LIBZAHL_ERROR.load(Ordering::SeqCst);
    
    if libzahl_error >= 0 {
        // Set errno to libzahl_error (Rust doesn't have direct errno access,
        // but we can use io::Error to represent it)
        let error = io::Error::from_raw_os_error(libzahl_error);
        
        // Print the error message with optional prefix
        if let Some(p) = prefix {
            eprint!("{}: ", p);
        }
        eprintln!("{}", error);
    } else {
        abort();
    }
}
