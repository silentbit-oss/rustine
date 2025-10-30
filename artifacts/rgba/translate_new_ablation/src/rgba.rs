use crate::*;
use lazy_static::lazy_static;
use std::ffi::CStr;
use std::os::raw::c_char;
use std::str::FromStr;
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
    // Use strstr-like approach to find "rgba(" prefix as in original C code
    if !str.starts_with("rgba(") {
        *ok = false;
        return 0;
    }
    
    let mut chars = str[5..].chars().peekable(); // Skip "rgba("
    
    // Skip whitespace
    while let Some(&c) = chars.peek() {
        if c == ' ' {
            chars.next();
        } else {
            break;
        }
    }
    
    // Parse red component
    let mut r = 0u8;
    if let Some(&c) = chars.peek() {
        if c.is_ascii_digit() {
            let mut value = 0;
            while let Some(&c) = chars.peek() {
                if c.is_ascii_digit() {
                    value = value * 10 + (c as u8 - b'0') as u32;
                    chars.next();
                } else {
                    break;
                }
            }
            r = if value > 255 { 255 } else { value as u8 };
        } else {
            *ok = false;
            return 0;
        }
    } else {
        *ok = false;
        return 0;
    }
    
    // Skip whitespace and commas
    while let Some(&c) = chars.peek() {
        if c == ' ' || c == ',' {
            chars.next();
        } else {
            break;
        }
    }
    
    // Parse green component
    let mut g = 0u8;
    if let Some(&c) = chars.peek() {
        if c.is_ascii_digit() {
            let mut value = 0;
            while let Some(&c) = chars.peek() {
                if c.is_ascii_digit() {
                    value = value * 10 + (c as u8 - b'0') as u32;
                    chars.next();
                } else {
                    break;
                }
            }
            g = if value > 255 { 255 } else { value as u8 };
        } else {
            *ok = false;
            return 0;
        }
    } else {
        *ok = false;
        return 0;
    }
    
    // Skip whitespace and commas
    while let Some(&c) = chars.peek() {
        if c == ' ' || c == ',' {
            chars.next();
        } else {
            break;
        }
    }
    
    // Parse blue component
    let mut b = 0u8;
    if let Some(&c) = chars.peek() {
        if c.is_ascii_digit() {
            let mut value = 0;
            while let Some(&c) = chars.peek() {
                if c.is_ascii_digit() {
                    value = value * 10 + (c as u8 - b'0') as u32;
                    chars.next();
                } else {
                    break;
                }
            }
            b = if value > 255 { 255 } else { value as u8 };
        } else {
            *ok = false;
            return 0;
        }
    } else {
        *ok = false;
        return 0;
    }
    
    // Skip whitespace and commas
    while let Some(&c) = chars.peek() {
        if c == ' ' || c == ',' {
            chars.next();
        } else {
            break;
        }
    }
    
    // Parse alpha component - follow original C logic more closely
    let mut a: f32 = 0.0;
    
    if let Some(&c) = chars.peek() {
        if c >= '1' && c <= '9' {
            a = 1.0;
            chars.next();
        } else if c == '0' {
            chars.next();
            if let Some(&c) = chars.peek() {
                if c == '.' {
                    chars.next();
                    let mut n: f32 = 0.1;
                    while let Some(&c) = chars.peek() {
                        if c.is_ascii_digit() {
                            a += (c as u8 - b'0') as f32 * n;
                            chars.next();
                            n *= 0.1;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
    
    *ok = true;
    rgba_from_rgba(r, g, b, (a * 255.0) as u8)
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

fn parse_alpha(bytes: &[u8], idx: &mut usize) -> Option<f32> {
    if *idx >= bytes.len() {
        return None;
    }
    
    match bytes[*idx] {
        b'1'..=b'9' => {
            *idx += 1;
            Some(1.0)
        }
        b'0' => {
            *idx += 1;
            if *idx < bytes.len() && bytes[*idx] == b'.' {
                *idx += 1;
                let mut a = 0.0;
                let mut n = 0.1;
                
                while *idx < bytes.len() && bytes[*idx].is_ascii_digit() {
                    a += (bytes[*idx] - b'0') as f32 * n;
                    n *= 0.1;
                    *idx += 1;
                }
                
                Some(a)
            } else {
                Some(0.0)
            }
        }
        _ => None,
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
    // Check for None
    if str.is_none() {
        *ok = false;
        return 0;
    }
    
    let s = str.unwrap();
    
    // Check if string starts with "rgb("
    if !s.starts_with("rgb(") {
        *ok = false;
        return 0;
    }
    
    // Move past "rgb("
    let mut index = 4;
    let bytes = s.as_bytes();
    let len = bytes.len();
    
    // Skip whitespace
    while index < len && bytes[index] == b' ' {
        index += 1;
    }
    
    // Parse red component
    let mut c: i32 = 0;
    if index < len && bytes[index] >= b'0' && bytes[index] <= b'9' {
        while index < len && bytes[index] >= b'0' && bytes[index] <= b'9' {
            c *= 10;
            c += (bytes[index] - b'0') as i32;
            index += 1;
        }
    } else {
        *ok = false;
        return 0;
    }
    
    if c > 255 {
        c = 255;
    }
    let r = c as u8;
    
    // Skip whitespace and commas
    while index < len && (bytes[index] == b' ' || bytes[index] == b',') {
        index += 1;
    }
    
    // Parse green component
    c = 0;
    if index < len && bytes[index] >= b'0' && bytes[index] <= b'9' {
        while index < len && bytes[index] >= b'0' && bytes[index] <= b'9' {
            c *= 10;
            c += (bytes[index] - b'0') as i32;
            index += 1;
        }
    } else {
        *ok = false;
        return 0;
    }
    
    if c > 255 {
        c = 255;
    }
    let g = c as u8;
    
    // Skip whitespace and commas
    while index < len && (bytes[index] == b' ' || bytes[index] == b',') {
        index += 1;
    }
    
    // Parse blue component
    c = 0;
    if index < len && bytes[index] >= b'0' && bytes[index] <= b'9' {
        while index < len && bytes[index] >= b'0' && bytes[index] <= b'9' {
            c *= 10;
            c += (bytes[index] - b'0') as i32;
            index += 1;
        }
    } else {
        *ok = false;
        return 0;
    }
    
    if c > 255 {
        c = 255;
    }
    let b = c as u8;
    
    // Skip whitespace and commas
    while index < len && (bytes[index] == b' ' || bytes[index] == b',') {
        index += 1;
    }
    
    // Check for closing parenthesis
    if index >= len || bytes[index] != b')' {
        *ok = false;
        return 0;
    }
    
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
    let Some(str) = str else {
        return None;
    };

    if let Some(first_char) = str.chars().next() {
        if first_char == '#' {
            let remaining = &str[1..];
            return rgba_from_hex_string(Some(remaining), ok);
        }
    }

    if str.starts_with("rgba") {
        return Some(rgba_from_rgba_string(str, &mut (*ok != 0)));
    }

    if str.starts_with("rgb") {
        return Some(rgba_from_rgb_string(Some(str), &mut (*ok != 0)));
    }

    rgba_from_name_string(Some(str), &mut (*ok != 0))
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
