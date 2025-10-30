use crate::*;
use std::convert::TryFrom;
use std::ffi::CStr;
use std::os::raw::c_char;

pub fn rgba_inspect(rgba: u32) {
    println!(
        "rgba({},{},{},{})",
        (rgba >> 24) & 0xff,
        (rgba >> 16) & 0xff,
        (rgba >> 8) & 0xff,
        rgba & 0xff
    );
}
pub fn h(c: char) -> i32 {
    match c {
        '0'..='9' => (c as i32) - ('0' as i32),
        'a'..='f' => (c as i32) - ('a' as i32) + 10,
        'A'..='F' => (c as i32) - ('A' as i32) + 10,
        _ => 0,
    }
}
pub fn rgba_from_rgba(r: u8, g: u8, b: u8, a: u8) -> u32 {
    ((r as u32) << 24) | ((g as u32) << 16) | ((b as u32) << 8) | (a as u32)
}
pub fn helper_rgba_from_rgba_string_1(
    str_idx_ref: &mut usize,
    str: &str,
    ok: &mut bool,
) -> u32 {
    let mut str_idx = *str_idx_ref;
    str_idx += 5;
    
    // Skip whitespace
    while str.chars().nth(str_idx) == Some(' ') {
        str_idx += 1;
    }

    // Parse red component
    let mut r = 0u8;
    let mut c = 0;
    if let Some(ch) = str.chars().nth(str_idx) {
        if ch.is_ascii_digit() {
            while let Some(ch) = str.chars().nth(str_idx) {
                if !ch.is_ascii_digit() {
                    break;
                }
                c *= 10;
                c += ch.to_digit(10).unwrap() as i32;
                str_idx += 1;
            }
        } else {
            return 0;
        }
    }
    r = c.min(255) as u8;

    // Skip whitespace and commas
    while str.chars().nth(str_idx).map_or(false, |c| c == ' ' || c == ',') {
        str_idx += 1;
    }

    // Parse green component
    let mut g = 0u8;
    c = 0;
    if let Some(ch) = str.chars().nth(str_idx) {
        if ch.is_ascii_digit() {
            while let Some(ch) = str.chars().nth(str_idx) {
                if !ch.is_ascii_digit() {
                    break;
                }
                c *= 10;
                c += ch.to_digit(10).unwrap() as i32;
                str_idx += 1;
            }
        } else {
            return 0;
        }
    }
    g = c.min(255) as u8;

    // Skip whitespace and commas
    while str.chars().nth(str_idx).map_or(false, |c| c == ' ' || c == ',') {
        str_idx += 1;
    }

    // Parse blue component
    let mut b = 0u8;
    c = 0;
    if let Some(ch) = str.chars().nth(str_idx) {
        if ch.is_ascii_digit() {
            while let Some(ch) = str.chars().nth(str_idx) {
                if !ch.is_ascii_digit() {
                    break;
                }
                c *= 10;
                c += ch.to_digit(10).unwrap() as i32;
                str_idx += 1;
            }
        } else {
            return 0;
        }
    }
    b = c.min(255) as u8;

    // Skip whitespace and commas
    while str.chars().nth(str_idx).map_or(false, |c| c == ' ' || c == ',') {
        str_idx += 1;
    }

    // Parse alpha component
    let mut a = 0.0;
    if let Some(ch) = str.chars().nth(str_idx) {
        match ch {
            '1'..='9' => a = 1.0,
            '0' => {
                str_idx += 1;
                if str.chars().nth(str_idx) == Some('.') {
                    str_idx += 1;
                    let mut n = 0.1;
                    while let Some(ch) = str.chars().nth(str_idx) {
                        if !ch.is_ascii_digit() {
                            break;
                        }
                        a += (ch.to_digit(10).unwrap() as f32) * n;
                        str_idx += 1;
                        n *= 0.1;
                    }
                }
            }
            _ => {}
        }
    }

    *ok = true;
    *str_idx_ref = str_idx;
    rgba_from_rgba(r, g, b, (a * 255.0) as u8)
}
pub fn rgba_from_rgba_string(str: &str, ok: &mut bool) -> u32 {
    let mut str_idx = 0;
    
    if str.starts_with("rgba(") {
        helper_rgba_from_rgba_string_1(&mut str_idx, str, ok);
    }
    
    *ok = false;
    0
}
pub fn rgba_from_rgb(r: u8, g: u8, b: u8) -> u32 {
    rgba_from_rgba(r, g, b, 255)
}

pub fn helper_rgba_from_rgb_string_1(
    str_idx_ref: &mut u32,
    str: &str,
    ok: &mut i16,
) -> u32 {
    let mut str_idx = *str_idx_ref;
    str_idx += 4;

    // Skip whitespace
    while str.chars().nth(str_idx as usize) == Some(' ') {
        str_idx += 1;
    }

    // Parse red component
    let r = match parse_color_component(&str, &mut str_idx) {
        Some(value) => value,
        None => {
            *ok = 0;
            return 0;
        }
    };

    // Skip whitespace and commas
    skip_separators(&str, &mut str_idx);

    // Parse green component
    let g = match parse_color_component(&str, &mut str_idx) {
        Some(value) => value,
        None => {
            *ok = 0;
            return 0;
        }
    };

    // Skip whitespace and commas
    skip_separators(&str, &mut str_idx);

    // Parse blue component
    let b = match parse_color_component(&str, &mut str_idx) {
        Some(value) => value,
        None => {
            *ok = 0;
            return 0;
        }
    };

    // Skip whitespace and commas
    skip_separators(&str, &mut str_idx);

    *ok = 1;
    *str_idx_ref = str_idx;
    rgba_from_rgb(r, g, b)
}

fn parse_color_component(str: &str, str_idx: &mut u32) -> Option<u8> {
    let mut c = 0;
    let mut has_digits = false;

    while let Some(ch) = str.chars().nth(*str_idx as usize) {
        if ch >= '0' && ch <= '9' {
            has_digits = true;
            c *= 10;
            c += ch as u32 - '0' as u32;
            *str_idx += 1;
        } else {
            break;
        }
    }

    if !has_digits {
        return None;
    }

    Some(u8::try_from(c.min(255)).unwrap())
}

fn skip_separators(str: &str, str_idx: &mut u32) {
    while let Some(ch) = str.chars().nth(*str_idx as usize) {
        if ch == ' ' || ch == ',' {
            *str_idx += 1;
        } else {
            break;
        }
    }
}

pub fn rgba_from_rgb_string(str: Option<&str>, ok: &mut i16) -> i32 {
    let mut str_idx: u32 = 0;
    
    // Check if the string starts with "rgb("
    if let Some(s) = str {
        if s.starts_with("rgb(") {
            helper_rgba_from_rgb_string_1(&mut str_idx, s, ok);
        }
    }
    
    *ok = 0;
    0  // Return value matches C's int32_t (i32 in Rust)
}

pub fn rgba_from_name_string(str: *const c_char, ok: &mut i16) -> i32 {
    // Convert C string to Rust &str safely
    let str_cstr = unsafe { CStr::from_ptr(str) };
    let str_slice = match str_cstr.to_str() {
        Ok(s) => s,
        Err(_) => {
            *ok = 0;
            return 0;
        }
    };

    // Iterate through named colors
    for color in NAMED_COLORS.iter() {
        if color.name == str_slice {
            *ok = 1;
            return color.val as i32;
        }
    }

    *ok = 0;
    0
}
pub fn rgba_from_hex6_string(str: &str) -> u32 {
    let chars: Vec<char> = str.chars().collect();
    rgba_from_rgb(
        ((h(chars[0]) << 4) + h(chars[1])) as u8,
        ((h(chars[2]) << 4) + h(chars[3])) as u8,
        ((h(chars[4]) << 4) + h(chars[5])) as u8,
    )
}
pub fn rgba_from_hex3_string(str: Option<&str>) -> Option<u32> {
    // Check if input is None (equivalent to NULL check in C)
    let str = str?; // Early return if None
    
    // Convert &str to a slice of chars for safe indexing
    let chars: Vec<char> = str.chars().collect();
    
    // Ensure we have at least 3 characters (like C would require)
    if chars.len() < 3 {
        return None;
    }
    
    // Calculate components using the h function
    let r = (h(chars[0]) << 4) + h(chars[0]);
    let g = (h(chars[1]) << 4) + h(chars[1]);
    let b = (h(chars[2]) << 4) + h(chars[2]);
    
    // Convert to u8 with bounds checking (since rgba_from_rgb expects u8)
    let r = r.clamp(0, 255) as u8;
    let g = g.clamp(0, 255) as u8;
    let b = b.clamp(0, 255) as u8;
    
    Some(rgba_from_rgb(r, g, b))
}
pub fn rgba_from_hex_string(str: Option<&str>, ok: &mut bool) -> Option<u32> {
    *ok = true;
    let str = match str {
        Some(s) => s,
        None => {
            *ok = false;
            return None;
        }
    };

    let len = str.len();
    match len {
        6 => Some(rgba_from_hex6_string(str)),
        3 => rgba_from_hex3_string(Some(str)),
        _ => {
            *ok = false;
            None
        }
    }
}
pub fn rgba_from_string(str: Option<&str>, ok: &mut i16) -> u32 {
    let str = match str {
        Some(s) => s,
        None => {
            *ok = 0;
            return 0;
        }
    };

    let mut str_idx = 0;

    if str.starts_with('#') {
        str_idx += 1;
        let mut bool_ok = false;
        let result = rgba_from_hex_string(Some(&str[str_idx..]), &mut bool_ok);
        *ok = bool_ok as i16;
        return result.unwrap_or(0);
    }

    if str[str_idx..].starts_with("rgba") {
        let mut bool_ok = false;
        let result = rgba_from_rgba_string(&str[str_idx..], &mut bool_ok);
        *ok = bool_ok as i16;
        return result;
    }

    if str[str_idx..].starts_with("rgb") {
        return rgba_from_rgb_string(Some(&str[str_idx..]), ok) as u32;
    }

    // For rgba_from_name_string, we need to convert &str to *const c_char
    let c_str = std::ffi::CString::new(str).unwrap();
    rgba_from_name_string(c_str.as_ptr(), ok) as u32
}
pub fn rgba_new(rgba: u32) -> RgbaT {
    RgbaT {
        r: ((rgba >> 24) as f64) / 255.0,
        g: (((rgba >> 16) & 0xff) as f64) / 255.0,
        b: (((rgba >> 8) & 0xff) as f64) / 255.0,
        a: ((rgba & 0xff) as f64) / 255.0,
    }
}
pub fn rgba_to_string(rgba: RgbaT, buf: &mut [u8]) -> Option<&str> {
    if rgba.a == 1.0 {
        let written = unsafe {
            std::ffi::CString::new(format!(
                "#{:02x}{:02x}{:02x}",
                (rgba.r * 255.0) as u8,
                (rgba.g * 255.0) as u8,
                (rgba.b * 255.0) as u8
            ))
            .unwrap()
            .as_bytes_with_nul()
            .len()
        };
        if written > buf.len() {
            return None;
        }
        let s = format!(
            "#{:02x}{:02x}{:02x}",
            (rgba.r * 255.0) as u8,
            (rgba.g * 255.0) as u8,
            (rgba.b * 255.0) as u8
        );
        buf[..s.len()].copy_from_slice(s.as_bytes());
        Some(std::str::from_utf8(&buf[..s.len()]).unwrap())
    } else {
        let written = unsafe {
            std::ffi::CString::new(format!(
                "rgba({}, {}, {}, {:.2})",
                (rgba.r * 255.0) as u8,
                (rgba.g * 255.0) as u8,
                (rgba.b * 255.0) as u8,
                rgba.a
            ))
            .unwrap()
            .as_bytes_with_nul()
            .len()
        };
        if written > buf.len() {
            return None;
        }
        let s = format!(
            "rgba({}, {}, {}, {:.2})",
            (rgba.r * 255.0) as u8,
            (rgba.g * 255.0) as u8,
            (rgba.b * 255.0) as u8,
            rgba.a
        );
        buf[..s.len()].copy_from_slice(s.as_bytes());
        Some(std::str::from_utf8(&buf[..s.len()]).unwrap())
    }
}
