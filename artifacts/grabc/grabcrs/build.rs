
use std::env;
use std::path::PathBuf;

fn main() {
    println!("cargo:rustc-link-lib=X11");

    bindgen::Builder::default()
        .header("wrapper.h")
        .disable_header_comment()
        .raw_line("// @generated")
        .ctypes_prefix("std::os::raw")
        .generate_block(true)
        .impl_debug(true)
        .derive_default(true)
        .layout_tests(false)
        .allowlist_file("/usr/include/X11/.*")
        .generate()
        .expect("Unable to generate bindings")
        .write_to_file(PathBuf::from(env::var("OUT_DIR").unwrap()).join("bindings.rs"))
        .expect("Couldn't write bindings!");
}
    
