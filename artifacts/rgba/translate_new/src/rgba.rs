use crate::*;
use std::str::FromStr;
use lazy_static::lazy_static;
use std::sync::Mutex;

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
    ((u32::from(r) << 24) | (u32::from(g) << 16)) | (u32::from(b) << 8) | u32::from(a)
}

pub fn rgba_from_rgba_string(str: &str, ok: &mut bool) -> u32 {
    let mut str_idx = 0;
    let str_bytes = str.as_bytes();
    
    if str.starts_with("rgba(") {
        str_idx += 5;
        
        // Skip whitespace
        while str_idx < str_bytes.len() && str_bytes[str_idx] == b' ' {
            str_idx += 1;
        }
        
        // Parse red component
        let r = match parse_component(&str_bytes, &mut str_idx) {
            Some(value) => value,
            None => {
                *ok = false;
                return 0;
            }
        };
        
        // Skip whitespace and commas
        skip_separators(&str_bytes, &mut str_idx);
        
        // Parse green component
        let g = match parse_component(&str_bytes, &mut str_idx) {
            Some(value) => value,
            None => {
                *ok = false;
                return 0;
            }
        };
        
        // Skip whitespace and commas
        skip_separators(&str_bytes, &mut str_idx);
        
        // Parse blue component
        let b = match parse_component(&str_bytes, &mut str_idx) {
            Some(value) => value,
            None => {
                *ok = false;
                return 0;
            }
        };
        
        // Skip whitespace and commas
        skip_separators(&str_bytes, &mut str_idx);
        
        // Parse alpha component
        let a = match parse_alpha(&str_bytes, &mut str_idx) {
            Some(value) => value,
            None => {
                *ok = false;
                return 0;
            }
        };
        
        *ok = true;
        rgba_from_rgba(r, g, b, (a * 255.0) as u8)
    } else {
        *ok = false;
        0
    }
}

fn parse_component(bytes: &[u8], idx: &mut usize) -> Option<u8> {
    let mut c = 0;
    
    if *idx < bytes.len() && bytes[*idx].is_ascii_digit() {
        while *idx < bytes.len() && bytes[*idx].is_ascii_digit() {
            c *= 10;
            c += (bytes[*idx] - b'0') as u8;
            *idx += 1;
        }
        
        Some(c.min(255))
    } else {
        None
    }
}

fn parse_alpha(str_bytes: &[u8], str_idx: &mut usize) -> Option<f32> {
    // Skip leading whitespace
    while *str_idx < str_bytes.len() && str_bytes[*str_idx].is_ascii_whitespace() {
        *str_idx += 1;
    }

    let mut value: f32 = 0.0;
    let mut has_value = false;

    // Parse integer part
    let mut int_value = 0;
    while *str_idx < str_bytes.len() && str_bytes[*str_idx].is_ascii_digit() {
        has_value = true;
        int_value = int_value * 10 + (str_bytes[*str_idx] - b'0') as u32;
        *str_idx += 1;
    }

    // Parse fractional part (if any)
    if *str_idx < str_bytes.len() && str_bytes[*str_idx] == b'.' {
        *str_idx += 1;
        let mut frac_value = 0.0;
        let mut factor = 0.1;
        while *str_idx < str_bytes.len() && str_bytes[*str_idx].is_ascii_digit() {
            has_value = true;
            frac_value += (str_bytes[*str_idx] - b'0') as f32 * factor;
            factor *= 0.1;
            *str_idx += 1;
        }
        value = int_value as f32 + frac_value;
    } else {
        value = int_value as f32;
    }

    if has_value {
        Some(value)
    } else {
        None
    }
}

fn skip_separators(bytes: &[u8], idx: &mut usize) {
    while *idx < bytes.len() && (bytes[*idx] == b' ' || bytes[*idx] == b',') {
        *idx += 1;
    }
}
pub fn rgba_from_rgb(r: u8, g: u8, b: u8) -> u32 {
    rgba_from_rgba(r, g, b, 255)
}
pub fn rgba_from_rgb_string(str: Option<&str>, ok: &mut bool) -> u32 {
    *ok = false;
    let str = match str {
        Some(s) => s,
        None => return 0,
    };

    if !str.starts_with("rgb(") {
        return 0;
    }

    let mut idx = 4; // Skip "rgb("
    
    // Skip whitespace
    while idx < str.len() && str.as_bytes()[idx] == b' ' {
        idx += 1;
    }

    // Parse red component
    let r = match parse_component(str.as_bytes(), &mut idx) {
        Some(value) => value,
        None => return 0,
    };

    // Skip whitespace and commas
    while idx < str.len() {
        let c = str.as_bytes()[idx];
        if c != b' ' && c != b',' {
            break;
        }
        idx += 1;
    }

    // Parse green component
    let g = match parse_component(str.as_bytes(), &mut idx) {
        Some(value) => value,
        None => return 0,
    };

    // Skip whitespace and commas
    while idx < str.len() {
        let c = str.as_bytes()[idx];
        if c != b' ' && c != b',' {
            break;
        }
        idx += 1;
    }

    // Parse blue component
    let b = match parse_component(str.as_bytes(), &mut idx) {
        Some(value) => value,
        None => return 0,
    };

    *ok = true;
    rgba_from_rgb(r, g, b)
}

pub fn rgba_from_name_string(str: Option<&str>, ok: &mut bool) -> Option<u32> {
    // Check if input string is None (equivalent to NULL in C)
    let str = match str {
        Some(s) => s,
        None => {
            *ok = false;
            return None;
        }
    };

    // Lock the NAMED_COLORS mutex to access the colors list
    let named_colors = NAMED_COLORS.lock().unwrap();

    // Iterate through the named colors
    for color in named_colors.iter() {
        // Check if we've reached the sentinel value (empty name)
        if color.name.is_empty() {
            break;
        }

        // Compare strings directly (Rust's == operator does proper string comparison)
        if str == color.name {
            *ok = true;
            return Some(color.val);
        }
    }

    *ok = false;
    None
}
pub fn rgba_from_hex6_string(str: Option<&str>) -> Option<u32> {
    // Check if input is None (equivalent to NULL check in C)
    let str = str?;

    // Ensure the string has exactly 6 characters (as implied by the C function)
    if str.len() != 6 {
        return None;
    }

    // Convert the string to a char array for easy indexing
    let chars: Vec<char> = str.chars().collect();

    // Calculate RGB components using the h function
    let r = ((h(chars[0]) << 4) + h(chars[1])) as u8;
    let g = ((h(chars[2]) << 4) + h(chars[3])) as u8;
    let b = ((h(chars[4]) << 4) + h(chars[5])) as u8;

    Some(rgba_from_rgb(r, g, b))
}
pub fn rgba_from_hex3_string(str: Option<&str>) -> Option<u32> {
    // Check if input is None (equivalent to NULL check in C)
    let str = str?;  // Early return if None
    
    // Convert &str to a char iterator and collect into a Vec for easy indexing
    let chars: Vec<char> = str.chars().collect();
    
    // Ensure we have at least 3 characters (like C would with str[0], str[1], str[2])
    if chars.len() < 3 {
        return None;
    }
    
    // Calculate components using the h function
    let r = (h(chars[0]) << 4) + h(chars[0]);
    let g = (h(chars[1]) << 4) + h(chars[1]);
    let b = (h(chars[2]) << 4) + h(chars[2]);
    
    // Convert to u8 (since rgba_from_rgb expects u8)
    // Note: We assume h() returns values in 0-15 range (like hex digits)
    Some(rgba_from_rgb(r as u8, g as u8, b as u8))
}
pub fn rgba_from_hex_string(str: Option<&str>, ok: &mut i16) -> Option<u32> {
    // Check if input string is None (equivalent to NULL in C)
    let str = match str {
        Some(s) => s,
        None => {
            *ok = 0;
            return None;
        }
    };

    let len = str.len();
    *ok = 1;

    match len {
        6 => rgba_from_hex6_string(Some(str)),
        3 => rgba_from_hex3_string(Some(str)),
        _ => {
            *ok = 0;
            None
        }
    }
}
pub fn rgba_from_string(str: Option<&str>, ok: &mut i16) -> Option<u32> {
    let str = match str {
        Some(s) => s,
        None => return None,
    };

    if str.starts_with('#') {
        return rgba_from_hex_string(Some(&str[1..]), ok);
    }

    if str.starts_with("rgba") {
        let mut bool_ok = (*ok != 0);
        let result = rgba_from_rgba_string(str, &mut bool_ok);
        *ok = bool_ok as i16;
        return Some(result);
    }

    if str.starts_with("rgb") {
        let mut bool_ok = (*ok != 0);
        let result = rgba_from_rgb_string(Some(str), &mut bool_ok);
        *ok = bool_ok as i16;
        return Some(result);
    }

    let mut bool_ok = (*ok != 0);
    let result = rgba_from_name_string(Some(str), &mut bool_ok);
    *ok = bool_ok as i16;
    result
}
pub fn rgba_new(rgba: u32) -> RgbaT {
    RgbaT {
        r: ((rgba >> 24) as f64) / 255.0,
        g: (((rgba >> 16) & 0xff) as f64) / 255.0,
        b: (((rgba >> 8) & 0xff) as f64) / 255.0,
        a: ((rgba & 0xff) as f64) / 255.0,
    }
}
pub fn rgba_to_string(rgba: RgbaT, buf: &mut [u8]) -> Option<()> {
    if rgba.a == 1.0 {
        let r = (rgba.r * 255.0) as u8;
        let g = (rgba.g * 255.0) as u8;
        let b = (rgba.b * 255.0) as u8;
        let s = format!("#{:02x}{:02x}{:02x}", r, g, b);
        if s.len() > buf.len() {
            return None;
        }
        buf[..s.len()].copy_from_slice(s.as_bytes());
    } else {
        let r = (rgba.r * 255.0) as u8;
        let g = (rgba.g * 255.0) as u8;
        let b = (rgba.b * 255.0) as u8;
        let s = format!("rgba({}, {}, {}, {:.2})", r, g, b, rgba.a);
        if s.len() > buf.len() {
            return None;
        }
        buf[..s.len()].copy_from_slice(s.as_bytes());
    }
    Some(())
}
