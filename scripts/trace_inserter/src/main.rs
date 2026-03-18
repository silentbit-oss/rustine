// use std::fs;
// use std::path::{Path, PathBuf};
// use walkdir::WalkDir;
// use syn::{Item, ItemFn, Attribute};
// use quote::quote;

// /// 是否是 Rust 项目根目录（通过 Cargo.toml 判断）
// fn is_rust_project(path: &Path) -> bool {
//     path.join("Cargo.toml").exists() && path.join("src").is_dir()
// }

// fn main() {
//     let current = std::env::current_dir().expect("get current dir failed");

//     if !is_rust_project(&current) {
//         eprintln!("Not a Rust project (missing Cargo.toml or src/)");
//         std::process::exit(1);
//     }

//     let src_dir = current.join("src");
//     let out_dir = current.join("logged");

//     for entry in WalkDir::new(&src_dir)
//         .into_iter()
//         .filter_map(Result::ok)
//         .filter(|e| {
//             e.file_type().is_file() && e.path().extension().map(|ext| ext == "rs").unwrap_or(false)
//         })
//     {
//         let src_path = entry.path();
//         let rel_path = src_path.strip_prefix(&src_dir).unwrap();
//         let dst_path = out_dir.join(rel_path);

//         let content = match fs::read_to_string(src_path) {
//             Ok(c) => c,
//             Err(_) => continue,
//         };
//         let file = match syn::parse_file(&content) {
//             Ok(f) => f,
//             Err(_) => continue,
//         };

//         let new_file = process_file(file);
//         let code = prettyplease::unparse(&new_file);

//         fs::create_dir_all(dst_path.parent().unwrap()).unwrap();
//         fs::write(dst_path, code).unwrap();
//     }

//     println!("Instrumentation complete. Output written to ./logged/");
// }

// fn has_trace_attr(attrs: &[Attribute]) -> bool {
//     attrs.iter().any(|attr| attr.path().is_ident("trace"))
// }

// fn process_file(mut file: syn::File) -> syn::File {
//     for item in &mut file.items {
//         if let Item::Fn(ref mut f) = item {
//             if !has_trace_attr(&f.attrs) {
//                 f.attrs.insert(0, syn::parse_quote!(#[trace]));
//             }
//         }
//     }
//     file
// }
// use std::fs;
// use std::path::{Path, PathBuf};
// use walkdir::WalkDir;
// use syn::{Item, ItemFn, Attribute};
// use quote::quote;

// fn main() {
//     let current = std::env::current_dir().expect("get current dir failed");

//     if !is_rust_project(&current) {
//         eprintln!("Not a Rust project (missing Cargo.toml or src/)");
//         std::process::exit(1);
//     }

//     let src_dir = current.join("src");
//     let out_dir = current.join("logged");

//     for entry in WalkDir::new(&src_dir)
//         .into_iter()
//         .filter_map(Result::ok)
//         .filter(|e| e.path().extension().map_or(false, |ext| ext == "rs"))
//     {
//         let src_path = entry.path();
//         let rel_path = src_path.strip_prefix(&src_dir).unwrap();
//         let dst_path = out_dir.join(rel_path);

//         let content = match fs::read_to_string(src_path) {
//             Ok(c) => c,
//             Err(_) => continue,
//         };
//         let file = match syn::parse_file(&content) {
//             Ok(f) => f,
//             Err(_) => continue,
//         };

//         let new_file = process_file(file);
//         let mut code = prettyplease::unparse(&new_file);

//         // If #[trace] is used, but `use trace_macro::trace;` is missing, insert it
//         if code.contains("#[trace]") && !code.contains("use trace_macro::trace;") {
//             code = insert_trace_use(&code);
//         }

//         fs::create_dir_all(dst_path.parent().unwrap()).unwrap();
//         fs::write(dst_path, code).unwrap();
//     }

//     println!("✅ Instrumentation complete. Output is in ./logged/");
// }

// fn is_rust_project(path: &Path) -> bool {
//     path.join("Cargo.toml").exists() && path.join("src").is_dir()
// }

// fn has_trace_attr(attrs: &[Attribute]) -> bool {
//     attrs.iter().any(|attr| attr.path().is_ident("trace"))
// }

// fn process_file(mut file: syn::File) -> syn::File {
//     for item in &mut file.items {
//         if let Item::Fn(ref mut f) = item {
//             if !has_trace_attr(&f.attrs) {
//                 f.attrs.insert(0, syn::parse_quote!(#[trace]));
//             }
//         }
//     }
//     file
// }

// fn insert_trace_use(code: &str) -> String {
//     let mut lines: Vec<&str> = code.lines().collect();
//     let insert_idx = lines.iter().position(|l| l.trim_start().starts_with("use "))
//         .unwrap_or_else(|| lines.iter().position(|l| !l.trim().is_empty()).unwrap_or(0));
//     lines.insert(insert_idx, "use trace_macro::trace;");
//     lines.join("\n")
// }
use std::fs;
use std::path::{Path, PathBuf};
use walkdir::WalkDir;
use syn::{Item, ItemFn, Attribute};

fn main() {
    let current = std::env::current_dir().expect("get current dir failed");

    if !is_rust_project(&current) {
        eprintln!("Not a Rust project (missing Cargo.toml or src/)");
        std::process::exit(1);
    }

    let out_dir = current.join("logged");

    for entry in WalkDir::new(&current)
        .into_iter()
        .filter_map(Result::ok)
        .filter(|e| e.file_type().is_file())
        .filter(|e| !e.path().components().any(|c| c.as_os_str() == "target"))
    {
        let src_path = entry.path();
        let rel_path = src_path.strip_prefix(&current).unwrap();
        let dst_path = out_dir.join(rel_path);

        fs::create_dir_all(dst_path.parent().unwrap()).unwrap();

        if src_path.extension().map_or(false, |ext| ext == "rs") {
            let content = match fs::read_to_string(src_path) {
                Ok(c) => c,
                Err(_) => continue,
            };
            let file = match syn::parse_file(&content) {
                Ok(f) => f,
                Err(_) => continue,
            };

            let new_file = process_file(file);
            let mut code = prettyplease::unparse(&new_file);

            if code.contains("#[trace]") && !code.contains("use trace_macro::trace;") {
                code = insert_trace_use(&code);
            }

            fs::write(dst_path, code).unwrap();
        } else {
            fs::copy(src_path, dst_path).unwrap();
        }
    }

    // Patch Cargo.toml in logged/
    let copied_toml = out_dir.join("Cargo.toml");
    if copied_toml.exists() {
        let mut toml_str = fs::read_to_string(&copied_toml).unwrap();

        let macro_dep = r#"trace_macro = { path = "../../../trace_macro" }"#;
        let utils_dep = r#"trace_utils = { path = "../../../trace_utils" }"#;

        if !toml_str.contains("trace_macro") {
            if let Some(deps_idx) = toml_str.find("[dependencies]") {
                let insert_idx = toml_str[deps_idx..]
                    .find('\n')
                    .map(|i| deps_idx + i + 1)
                    .unwrap_or(toml_str.len());
                toml_str.insert_str(insert_idx, &format!("{macro_dep}\n"));
            } else {
                toml_str.push_str(&format!("\n[dependencies]\n{macro_dep}\n"));
            }
        }

        if !toml_str.contains("trace_utils") {
            if let Some(deps_idx) = toml_str.find("[dependencies]") {
                let insert_idx = toml_str[deps_idx..]
                    .find('\n')
                    .map(|i| deps_idx + i + 1)
                    .unwrap_or(toml_str.len());
                toml_str.insert_str(insert_idx, &format!("{utils_dep}\n"));
            } else {
                toml_str.push_str(&format!("\n[dependencies]\n{utils_dep}\n"));
            }
        }

        fs::write(&copied_toml, toml_str).unwrap();
        println!("📦 Patched dependencies in logged/Cargo.toml");
    }

    println!("✅ Full project copied and instrumented to ./logged/");
}

fn is_rust_project(path: &Path) -> bool {
    path.join("Cargo.toml").exists() && path.join("src").is_dir()
}

fn has_trace_attr(attrs: &[Attribute]) -> bool {
    attrs.iter().any(|attr| attr.path().is_ident("trace"))
}

fn process_file(mut file: syn::File) -> syn::File {
    for item in &mut file.items {
        if let Item::Fn(ref mut f) = item {
            if !has_trace_attr(&f.attrs) {
                f.attrs.insert(0, syn::parse_quote!(#[trace]));
            }
        }
    }
    file
}

fn insert_trace_use(code: &str) -> String {
    let mut lines: Vec<&str> = code.lines().collect();
    let insert_idx = lines
        .iter()
        .position(|l| l.trim_start().starts_with("use "))
        .unwrap_or_else(|| lines.iter().position(|l| !l.trim().is_empty()).unwrap_or(0));
    lines.insert(insert_idx, "use trace_macro::trace;");
    lines.join("\n")
}
