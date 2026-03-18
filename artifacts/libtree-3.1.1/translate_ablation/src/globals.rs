use crate::*;
use lazy_static::lazy_static;


lazy_static! {
    pub static ref EXCLUDE_LIST: [&'static str; 14] = [
        "ld-linux-aarch64.so",
        "ld-linux-armhf.so",
        "ld-linux-x86-64.so",
        "ld-linux.so",
        "ld64.so",
        "libc.musl-aarch64.so",
        "libc.musl-armhf.so",
        "libc.musl-i386.so",
        "libc.musl-x86_64.so",
        "libc.so",
        "libdl.so",
        "libgcc_s.so",
        "libm.so",
        "libstdc++.so"
    ];
}

