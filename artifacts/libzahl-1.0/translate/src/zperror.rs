use crate::*;
use std::process;
use std::io;


pub fn zperror(prefix: Option<&str>) {
    let libzahl_error = LIBZAHL_ERROR.lock().unwrap();
    
    if *libzahl_error >= 0 {
        // Set errno (Rust doesn't have direct errno access, but we can use io::Error)
        let error = io::Error::from_raw_os_error(*libzahl_error);
        
        // Print the error message with optional prefix
        if let Some(p) = prefix {
            eprintln!("{}: {}", p, error);
        } else {
            eprintln!("{}", error);
        }
    } else {
        // Abnormal termination
        process::abort();
    }
}
