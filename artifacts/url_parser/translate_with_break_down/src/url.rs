use crate::*;
use crate::Category::Query;
use lazy_static::lazy_static;
use std::error::Error;
use std::ffi::CStr;
use std::fmt;
use std::io::Write;
use std::io;
use std::str;

pub fn url_is_ssh(str: &str) -> bool {
    str == "ssh" || str == "git"
}
pub fn strdup(str: Option<&str>) -> Option<String> {
    // Check for NULL input (None in Rust)
    let str = str?;

    // Calculate length and allocate memory (handled by String in Rust)
    let dup = str.to_string();

    Some(dup)
}
pub fn unhex(s: Option<&str>) -> i32 {
    // Check if input is None (equivalent to NULL in C)
    let s = match s {
        Some(s) => s,
        None => return -1,
    };

    // Get the first character as a char (Rust handles UTF-8 properly)
    let c = match s.chars().next() {
        Some(c) => c,
        None => return -1,
    };

    match c {
        '0'..='9' => (c as i32) - ('0' as i32),
        'A'..='F' => (c as i32) - ('A' as i32) + 10,
        'a'..='f' => (c as i32) - ('a' as i32) + 10,
        _ => -1,
    }
}
pub fn scan_decimal_number(start: Option<&str>) -> Option<&str> {
    // Check if input is None (equivalent to NULL check in C)
    let start = start?;
    
    let mut p_idx = 0;
    let bytes = start.as_bytes();
    
    // Iterate through the string while characters are digits
    while p_idx < bytes.len() && bytes[p_idx].is_ascii_digit() {
        p_idx += 1;
    }
    
    // Return Some(&start[..p_idx]) if we found digits, None otherwise
    if p_idx > 0 {
        Some(&start[..p_idx])
    } else {
        None
    }
}

pub fn url_is_protocol(str: Option<&str>) -> bool {
    // Check if input is None (equivalent to NULL check in C)
    if str.is_none() {
        return false;
    }
    let str = str.unwrap();

    // Iterate through URL_SCHEMES and compare strings
    for scheme in URL_SCHEMES.iter() {
        if *scheme == str {
            return true;
        }
    }
    
    false
}
pub fn url_get_scheme(url: Option<&str>) -> Option<String> {
    // Check for NULL input (None in Rust)
    let url = url?;

    // Extract the protocol part before "://"
    let protocol_end = url.find("://").unwrap_or(url.len());
    let protocol = &url[..protocol_end];

    // Check if the protocol is valid using the provided function
    if url_is_protocol(Some(protocol)) {
        Some(protocol.to_string())
    } else {
        None
    }
}
pub fn scan_part(start: &str, category: Category, delimiter1: char, delimiter2: char) -> Option<&str> {
    let mut p_idx = 0;
    let bytes = start.as_bytes();
    
    loop {
        let current_char = bytes.get(p_idx).copied()?;
        if current_char == b'\0' || current_char == delimiter1 as u8 || current_char == delimiter2 as u8 {
            return Some(&start[..p_idx]);
        }
        
        if (CHAR_CAT[current_char as usize] & category as u16) != 0 {
            p_idx += 1;
        } else {
            return None;
        }
    }
}
pub fn helper_url_parse_3(
    p_idx_ref: &mut u32,
    hostname_end_idx_ref: &mut u32,
    data: &mut UrlData,
    p: &str,
    p_end: &str,
    is_ssh: bool,
    hostname_end: &mut String,  // Changed from &mut str to &mut String
) -> Result<(), String> {
    let mut p_idx = *p_idx_ref;
    let mut hostname_end_idx = *hostname_end_idx_ref;
    
    p_idx += 1;
    
    // Convert p_idx to usize for string slicing
    let p_idx_usize = p_idx as usize;
    if p_idx_usize >= p.len() {
        return Err("Index out of bounds".to_string());
    }

    let scan_result = scan_part(&p[p_idx_usize..], Category::IPv6Char, ']', '\0');
    hostname_end_idx = match scan_result {
        Some(s) => s.len() as u32,
        None => {
            eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 234, p);
            return Err("Failed to scan part".to_string());
        }
    };

    if hostname_end.len() <= hostname_end_idx as usize {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 234, p);
        return Err("Invalid hostname_end index".to_string());
    }

    // Truncate the hostname_end string directly
    hostname_end.truncate(hostname_end_idx as usize);

    data.host = Some(p[p_idx_usize..].to_string());

    hostname_end_idx += 1;

    if (hostname_end_idx as usize) < p_end.len() && !is_ssh && hostname_end.chars().nth(hostname_end_idx as usize) == Some(':') {
        let port_start = (hostname_end_idx + 1) as usize;
        let port_end = match scan_decimal_number(Some(&hostname_end[port_start..])) {
            Some(end) => end,
            None => {
                eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 247, p);
                return Err("Failed to scan decimal number".to_string());
            }
        };

        data.port = Some(hostname_end[port_start..port_start + port_end.len()].to_string());
        p_idx = (port_start + port_end.len()) as u32;
    } else {
        p_idx = hostname_end_idx;
    }

    *p_idx_ref = p_idx;
    *hostname_end_idx_ref = hostname_end_idx;

    Ok(())
}
pub fn helper_url_parse_2(
    p_idx_ref: &mut u32,
    hostname_end_idx_ref: &mut u32,
    data: &mut UrlData,
    p: &str,
    is_ssh: bool,
    hostname_end: &str,
) {
    let mut p_idx = *p_idx_ref;
    let mut hostname_end_idx = *hostname_end_idx_ref;

    // Scan part and handle potential error
    let scanned = scan_part(p, Category::Unreserved, ':', '/')
        .or_else(|| scan_part(p, Category::SubDelim, ':', '/'));
    hostname_end_idx = match scanned {
        Some(s) => s.len().try_into().unwrap(),
        None => {
            eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 255, p);
            return;
        }
    };

    // Check if hostname_end index is valid
    if hostname_end.get(hostname_end_idx as usize..).is_none() {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 255, p);
        return;
    }

    data.host = Some(p[p_idx as usize..].to_string());

    if !is_ssh && hostname_end.chars().nth(hostname_end_idx as usize) == Some(':') {
        // In Rust we can't modify the string directly, so we'll work with slices
        let port_start = hostname_end_idx + 1;
        let port_end = scan_decimal_number(hostname_end.get(port_start as usize..));

        if let Some(port_end_str) = port_end {
            data.port = Some(hostname_end[port_start as usize..port_start as usize + port_end_str.len()].to_string());
            p_idx = port_start + port_end_str.len() as u32;
        } else {
            eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 267, p);
            return;
        }
    } else {
        p_idx = hostname_end_idx;
    }

    *p_idx_ref = p_idx;
    *hostname_end_idx_ref = hostname_end_idx;
}
pub fn decode_percent(s: &mut str) -> Option<&str> {
    let bytes = unsafe { s.as_bytes_mut() }; // Safe because we're working with UTF-8
    let mut in_idx = 0;
    let mut out_idx = 0;

    while in_idx < bytes.len() {
        if bytes[in_idx] == b'%' {
            in_idx += 1;
            if in_idx >= bytes.len() {
                return None;
            }

            let high = unhex(Some(str::from_utf8(&bytes[in_idx..in_idx + 1]).ok()?));
            if high < 0 {
                return None;
            }
            in_idx += 1;

            if in_idx >= bytes.len() {
                return None;
            }

            let low = unhex(Some(str::from_utf8(&bytes[in_idx..in_idx + 1]).ok()?));
            if low < 0 {
                return None;
            }
            in_idx += 1;

            bytes[out_idx] = (high * 16 + low) as u8;
            out_idx += 1;
        } else {
            bytes[out_idx] = bytes[in_idx];
            in_idx += 1;
            out_idx += 1;
        }
    }

    if out_idx < bytes.len() {
        bytes[out_idx] = b'\0';
    }

    Some(unsafe { str::from_utf8(&bytes[..out_idx]).unwrap() })
}
pub fn parse_query_string(begin: &str, end: &str) -> Option<Vec<UrlKeyValue>> {
    
    // Count the number of elements (key-value pairs) by counting delimiters
    let elements = begin.chars()
        .take_while(|&c| c != end.chars().next().unwrap_or('\0'))
        .filter(|&c| c == '&' || c == ';')
        .count() + 1;

    let mut kv = Vec::with_capacity(elements + 1);
    let mut p = begin;
    let mut p_idx = 0;

    for element in 0..elements {
        if p_idx >= p.len() || p[p_idx..].is_empty() {
            break;
        }

        let key = &p[p_idx..];
        let kv_end = match scan_part(key, Query, '&', ';') {
            Some(end) => end,
            None => {
                eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 153, p);
                return None;
            }
        };

        let kv_end_pos = key.as_ptr() as usize + kv_end.as_ptr() as usize - key.as_ptr() as usize;
        let key_part = &key[..kv_end_pos];

        let key_end = match scan_part(key_part, Query, '=', '\0') {
            Some(end) => end,
            None => {
                eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 153, p);
                return None;
            }
        };

        let has_value = key_end.ends_with('=');
        let key_part = if has_value {
            &key_part[..key_part.len() - 1]
        } else {
            key_part
        };

        let decoded_key = decode_percent(&mut key_part.to_string()).map(|s| s.to_string());
        let decoded_value = if has_value {
            let value = &key_part[key_end.len()..];
            decode_percent(&mut value.to_string()).map(|s| s.to_string())
        } else {
            Some(key_end.to_string())
        };

        kv.push(UrlKeyValue {
            key: decoded_key,
            value: decoded_value,
        });

        p_idx += kv_end.len() + 1;
    }

    Some(kv)
}

pub fn helper_url_parse_1(data: &mut UrlData, p: &mut str) -> Result<(), ()> {
    let query_end = scan_part(p, Category::Query, '#', '\0');
    match query_end {
        Some(query_end_str) => {
            let has_fragment = query_end_str.starts_with('#');
            let query_part = &p[..query_end_str.len()];
            data.query = parse_query_string(query_part, query_end_str)
                .and_then(|v| v.into_iter().next()); // Take first element of Vec if exists

            if has_fragment {
                let fragment_start = query_end_str.len() + 1;
                let fragment_part = &p[fragment_start..];
                let fragment_end = scan_part(fragment_part, Category::Fragment, '\0', '\0');
                
                match fragment_end {
                    Some(_) => {
                        data.fragment = decode_percent(&mut p[fragment_start..].to_string())
                            .map(|s| s.to_string()); // Convert &str to String
                        Ok(())
                    },
                    None => {
                        let _ = writeln!(io::stderr(), "ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 319, p);
                        Err(())
                    }
                }
            } else {
                Ok(())
            }
        },
        None => {
            let _ = writeln!(io::stderr(), "ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 323, p);
            Err(())
        }
    }
}
pub fn url_free(data: Option<Box<UrlData>>) {
    // In Rust, we don't need to explicitly free memory - it's handled by Drop trait
    // The Option<Box<UrlData>> will be automatically dropped when it goes out of scope
    // The inner fields (Option<String> and Option<UrlKeyValue>) will also be dropped automatically
    // So this function can be empty, but we keep it for API compatibility
}
pub fn url_parse(url: Option<&str>) -> Option<Box<UrlData>> {
    let url = url?;
    
    let mut data = Box::new(UrlData {
        whole_url: None,
        protocol: None,
        userinfo: None,
        host: None,
        port: None,
        path: None,
        query: None,
        fragment: None,
    });

    let mut p = strdup(Some(url))?;
    let mut p_idx = 0;

    if p.get(p_idx..).is_none() {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 190, p);
        return None;
    }

    data.whole_url = Some(p[p_idx..].to_string());
    let p_end = p[p_idx..].len() + p_idx;
    
    let protocol_end = scan_part(&p[p_idx..], Category::Scheme, ':', '\0')?;
    let protocol_end_abs = protocol_end.as_ptr() as usize - p.as_ptr() as usize;
    
    if protocol_end.is_empty() || protocol_end.starts_with('\0') {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 197, p);
        return None;
    }

    let mut p_chars: Vec<char> = p.chars().collect();
    p_chars[protocol_end_abs] = '\0';
    p = p_chars.into_iter().collect();
    data.protocol = Some(p[p_idx..protocol_end_abs].to_string());
    
    let is_ssh = url_is_ssh(&data.protocol.as_ref()?);
    p_idx = protocol_end_abs + 1;

    if p_idx >= p_end || p.chars().nth(p_idx) != Some('/') {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 205, p);
        return None;
    }

    p_idx += 1;
    if p_idx >= p_end || p.chars().nth(p_idx) != Some('/') {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 209, p);
        return None;
    }

    let second_slash = p_idx - 1;
    p_idx += 1;

    if p_idx >= p_end {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 215, p);
        return None;
    }

    let userinfo_end = scan_part(&p[p_idx..], Category::Userinfo, '@', '\0');
    if let Some(userinfo_end) = userinfo_end {
        if !userinfo_end.is_empty() && userinfo_end.starts_with('@') {
            let userinfo_end_abs = userinfo_end.as_ptr() as usize - p.as_ptr() as usize;
            let mut p_chars: Vec<char> = p.chars().collect();
            p_chars[userinfo_end_abs] = '\0';
            p = p_chars.into_iter().collect();
            data.userinfo = Some(p[p_idx..userinfo_end_abs].to_string());
            p_idx = userinfo_end_abs + 1;
        }
    }

    if p_idx >= p_end {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 225, p);
        return None;
    }

    let mut hostname_end = String::new();
    let mut hostname_end_idx = 0u32;

    if p.chars().nth(p_idx) == Some('[') {
        if let Err(_) = helper_url_parse_3(&mut (p_idx as u32), &mut hostname_end_idx, &mut data, &p, &p[p_idx..p_end], is_ssh, &mut hostname_end) {
            return None;
        }
    } else {
        helper_url_parse_2(&mut (p_idx as u32), &mut hostname_end_idx, &mut data, &p, is_ssh, &hostname_end);
    }

    // Simulate memmove
    let slice_to_move = &p[second_slash + 1..p_idx];
    let mut new_p = p[..second_slash].to_string();
    new_p.push_str(slice_to_move);
    p = new_p;

    if let Some(userinfo) = &mut data.userinfo {
        *userinfo = userinfo[1..].to_string();
    }

    if let Some(host) = &mut data.host {
        *host = host[1..].to_string();
    }

    if let Some(port) = &mut data.port {
        *port = port[1..].to_string();
    }

    let mut p_chars: Vec<char> = p.chars().collect();
    p_chars[p_idx - 1] = '\0';
    p = p_chars.into_iter().collect();

    if is_ssh && p.chars().nth(p_idx) == Some(':') {
        p_idx += 1;
    }

    let path_end = scan_part(&p[p_idx..], Category::PCharSlash, '?', '#')?;
    let path_end_abs = path_end.as_ptr() as usize - p.as_ptr() as usize;

    if path_end.is_empty() {
        eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 295, p);
        return None;
    }

    let has_query = path_end.starts_with('?');
    let has_fragment = path_end.starts_with('#');

    let mut p_chars: Vec<char> = p.chars().collect();
    p_chars[path_end_abs] = '\0';
    p = p_chars.into_iter().collect();

    data.path = decode_percent(&mut p[p_idx..path_end_abs].to_string()).map(|s| s.to_string());

    p_idx = path_end_abs + 1;

    if has_query {
        helper_url_parse_1(&mut data, &mut p[p_idx..]);
    } else if has_fragment {
        let fragment_end = scan_part(&p[p_idx..], Category::Fragment, '\0', '\0');
        if let Some(fragment_end) = fragment_end {
            data.fragment = decode_percent(&mut p[p_idx..].to_string()).map(|s| s.to_string());
        } else {
            eprintln!("ERROR {} Line {}! p=«{}»", "/workdir/C2RustTranslation-main/subjects/url_parser/url.c", 332, p);
            return None;
        }
    }

    Some(data)
}
pub fn url_get_fragment(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.fragment.as_ref()).map(|f| f.clone());
    url_free(data);
    out
}
pub fn url_data_inspect(data: &UrlData) {
    println!("#url =>");
    {
        match &data.protocol {
            Some(protocol) => println!("    .protocol: \"{}\"", protocol),
            None => println!("    .protocol: (NULL)"),
        }
    }
    {
        match &data.host {
            Some(host) => println!("    .host: \"{}\"", host),
            None => println!("    .host: (NULL)"),
        }
    }
    {
        match &data.userinfo {
            Some(userinfo) => println!("    .userinfo: \"{}\"", userinfo),
            None => println!("    .userinfo: (NULL)"),
        }
    }
    {
        match &data.host {
            Some(host) => println!("    .host: \"{}\"", host),
            None => println!("    .host: (NULL)"),
        }
    }
    {
        match &data.port {
            Some(port) => println!("    .port: \"{}\"", port),
            None => println!("    .port: (NULL)"),
        }
    }
    {
        match &data.path {
            Some(path) => println!("    .path: \"{}\"", path),
            None => println!("    .path: (NULL)"),
        }
    }
    if let Some(query) = &data.query {
        // Since we can't represent the C array termination in Rust's type system,
        // we'll just print the single key-value pair if it exists
        if let Some(key) = &query.key {
            print!("    .query[0]: \"{}\" -> ", key);
            match &query.value {
                Some(value) => println!("\"{}\"", value),
                None => println!("(NULL)"),
            }
        }
    }
    {
        match &data.fragment {
            Some(fragment) => println!("    .fragment: \"{}\"", fragment),
            None => println!("    .fragment: (NULL)"),
        }
    }
}
pub fn url_get_query_value<'a>(url: &'a UrlData, key: &str) -> Option<&'a str> {
    // Check if query is None (equivalent to checking for 0 in C)
    let query = url.query.as_ref()?;

    // Check if key matches and return corresponding value
    if let Some(k) = &query.key {
        if k == key {
            return query.value.as_deref();
        }
    }

    None
}
pub fn url_inspect(url: Option<&str>) {
    if let Some(data) = url_parse(url) {
        url_data_inspect(&data);
    }
}
pub fn url_get_userinfo(url: Option<&str>) -> Option<String> {
    // The do-while(0) pattern in C is just for control flow and can be omitted in Rust
    let data = url_parse(url);
    let out = match &data {
        Some(d) => strdup(d.userinfo.as_deref()),
        None => None,
    };
    url_free(data);
    out
}
pub fn url_get_hostname(url: Option<&str>) -> Option<String> {
    // Use a block to limit the scope of the mutable borrow
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.host.as_ref()).map(|h| h.clone());
    url_free(data);
    out
}
pub fn url_get_path(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.path.as_ref()).map(|p| p.clone());
    url_free(data);
    out
}
pub fn url_get_port(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.port.as_ref()).map(|p| p.clone());
    url_free(data);
    out
}
pub fn url_get_host(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.host.as_ref()).map(|host| host.clone());
    url_free(data);
    out
}
pub fn url_get_pathname(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.path.as_ref()).map(|p| p.clone());
    url_free(data);
    out
}
