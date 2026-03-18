use crate::*;
use std::ffi::CStr;
use crate::Category::*;
use std::borrow::Cow;
use std::fmt::Write;

pub fn url_is_ssh(str: &str) -> bool {
    str == "ssh" || str == "git"
}
pub fn strdup(str: Option<&str>) -> Option<String> {
    // Check for NULL input (None in Rust)
    let str = str?;  // Early return if None

    // Rust strings already handle memory allocation and copying
    Some(str.to_string())
}
pub fn unhex(s: Option<&str>) -> Option<i32> {
    // Check if input is None (equivalent to NULL in C)
    let s = s?;
    
    // Get first character (if string is empty, return None)
    let c = s.chars().next()?;
    
    match c {
        '0'..='9' => Some((c as i32) - ('0' as i32)),
        'A'..='F' => Some((c as i32) - ('A' as i32) + 10),
        'a'..='f' => Some((c as i32) - ('a' as i32) + 10),
        _ => None,
    }
}
pub fn scan_decimal_number(start: Option<&str>) -> Option<&str> {
    // Check if input is None (equivalent to NULL check in C)
    let start = start?;

    let mut p_idx = 0;
    let bytes = start.as_bytes();
    
    // Iterate while current character is a digit
    while p_idx < bytes.len() && bytes[p_idx].is_ascii_digit() {
        p_idx += 1;
    }

    // Return Some(&start) if we found digits, None otherwise
    if p_idx > 0 {
        Some(start)
    } else {
        None
    }
}
pub fn url_is_protocol(str: Option<&str>) -> bool {
    // Check if input is None (equivalent to NULL in C)
    let str = match str {
        Some(s) => s,
        None => return false,
    };

    // Iterate through URL_SCHEMES and compare strings
    URL_SCHEMES.iter().any(|scheme| *scheme == str)
}

pub fn url_get_scheme(url: Option<&str>) -> Option<String> {
    // Check if input is None (equivalent to NULL in C)
    let url = url?;

    // Use split_once to safely extract the protocol part before "://"
    let (protocol_part, _) = url.split_once("://").unwrap_or((url, ""));

    // Check if the extracted part is a valid protocol
    if url_is_protocol(Some(protocol_part)) {
        Some(protocol_part.to_string())
    } else {
        None
    }
}
pub fn scan_part(start: Option<&str>, category: Category, delimiter1: char, delimiter2: char) -> Option<&str> {
    // Return None if input is None (equivalent to NULL check in C)
    let start = start?;
    
    let mut p_idx = 0;
    let bytes = start.as_bytes();
    
    while p_idx < bytes.len() {
        let current_char = bytes[p_idx] as char;
        
        // Check for termination conditions (null byte or delimiters)
        if current_char == '\0' || current_char == delimiter1 || current_char == delimiter2 {
            return Some(&start[..p_idx]);
        }
        
        // Check if character matches the category
        let char_cat = CHAR_CAT[bytes[p_idx] as usize] as u32;
        let category_bits = category as u32;
        
        if char_cat & category_bits != 0 {
            p_idx += 1;
        } else {
            return None;
        }
    }
    
    // If we reach the end of the string without finding a delimiter
    Some(start)
}
pub fn decode_percent(s: &mut str) -> Option<&mut str> {
    let bytes = unsafe { s.as_bytes_mut() }; // Safe because we're working with UTF-8
    let mut in_idx = 0;
    let mut out_idx = 0;

    while in_idx < bytes.len() {
        if bytes[in_idx] == b'%' {
            in_idx += 1;
            if in_idx >= bytes.len() {
                return None;
            }

            let high = unhex(Some(unsafe {
                std::str::from_utf8_unchecked(&bytes[in_idx..in_idx + 1])
            }))? as u32;
            in_idx += 1;
            if in_idx >= bytes.len() {
                return None;
            }

            let low = unhex(Some(unsafe {
                std::str::from_utf8_unchecked(&bytes[in_idx..in_idx + 1])
            }))? as u32;
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

    Some(unsafe { std::str::from_utf8_unchecked_mut(&mut bytes[..out_idx]) })
}
pub fn parse_query_string(begin: Option<&str>, end: Option<&str>) -> Option<Vec<UrlKeyValue>> {
    // Check for NULL equivalent (None) in Rust
    let begin = begin?;
    let end = end?;

    // Count the number of elements (key-value pairs)
    let elements = 1 + begin.chars().filter(|&c| c == '&' || c == ';').count();

    // Initialize the result vector with capacity
    let mut kv = Vec::with_capacity(elements + 1);
    
    // Split the string by delimiters and process each part
    for part in begin.split(|c| c == '&' || c == ';') {
        if part.is_empty() {
            continue;
        }

        // Find the position of '=' to separate key and value
        let (key_part, has_value) = match part.find('=') {
            Some(pos) => (&part[..pos], true),
            None => (part, false),
        };

        // Decode the key
        let mut key_str = key_part.to_string();
        let key = decode_percent(&mut key_str).map(|s| s.to_string());

        // Decode the value if present
        let value = if has_value {
            let value_part = &part[key_part.len() + 1..];
            let mut value_str = value_part.to_string();
            decode_percent(&mut value_str).map(|s| s.to_string())
        } else {
            None
        };

        kv.push(UrlKeyValue {
            key,
            value,
        });
    }

    Some(kv)
}
pub fn url_free(data: Option<Box<UrlData>>) {
    // In Rust, we don't need to explicitly free memory - it's handled by Drop trait
    // The Option<Box<UrlData>> will be automatically dropped when it goes out of scope
    // The inner fields (Option<String>, Option<Vec<UrlKeyValue>> etc.) will also be dropped automatically
    // So this function is essentially a no-op in Rust, but we keep it for API compatibility
}
pub fn url_parse(url: Option<&str>) -> Option<Box<UrlData>> {

    // Allocate and initialize UrlData (equivalent to calloc)
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

    // Duplicate the URL string (equivalent to strdup)
    let mut p = strdup(url)?;
    let mut p_idx = 0;

    // Check if we have a valid string
    if p.get(p_idx..).is_none() {
        eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 190, p);
        return None;
    }

    data.whole_url = Some(p[p_idx..].to_string());

    let p_end = p.len();
    let mut p_slice = p[p_idx..].to_string();

    // Scan protocol part
    let protocol_end = scan_part(Some(&p_slice), Scheme, ':', '\0')?;
    if protocol_end.is_empty() {
        eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 197, p);
        return None;
    }

    let protocol_end_idx = protocol_end.as_ptr() as usize - p_slice.as_ptr() as usize;
    let mut p_slice_chars: Vec<char> = p_slice.chars().collect();
    p_slice_chars[protocol_end_idx] = '\0';
    p_slice = p_slice_chars.into_iter().collect();
    data.protocol = Some(p_slice[..protocol_end_idx].to_string());
    let is_ssh = url_is_ssh(data.protocol.as_ref()?);
    p_idx += protocol_end_idx + 1;

    // Check for required slashes
    if p_idx >= p_end || p.as_bytes()[p_idx] != b'/' {
        eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 205, p);
        return None;
    }
    p_idx += 1;

    if p_idx >= p_end || p.as_bytes()[p_idx] != b'/' {
        eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 209, p);
        return None;
    }

    let second_slash_idx = p_idx;
    p_idx += 1;

    if p_idx >= p_end {
        eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 215, p);
        return None;
    }

    // Scan userinfo part
    let mut userinfo_slice = p[p_idx..].to_string();
    let userinfo_end = scan_part(Some(&userinfo_slice), Userinfo, '@', '\0');
    if let Some(end) = userinfo_end {
        if !end.is_empty() && end.starts_with('@') {
            let userinfo_end_idx = end.as_ptr() as usize - userinfo_slice.as_ptr() as usize;
            let mut userinfo_chars: Vec<char> = userinfo_slice.chars().collect();
            userinfo_chars[userinfo_end_idx] = '\0';
            userinfo_slice = userinfo_chars.into_iter().collect();
            data.userinfo = Some(userinfo_slice[..userinfo_end_idx].to_string());
            p_idx += userinfo_end_idx + 1;
        }
    }

    if p_idx >= p_end {
        eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 225, p);
        return None;
    }

    // Scan hostname part
    let mut host_slice = p[p_idx..].to_string();
    if host_slice.starts_with('[') {
        // IPv6 address
        p_idx += 1;
        let hostname_end = scan_part(Some(&host_slice[1..]), IPv6Char, ']', '\0')?;
        let hostname_end_idx = hostname_end.as_ptr() as usize - host_slice.as_ptr() as usize;
        let mut host_chars: Vec<char> = host_slice.chars().collect();
        host_chars[hostname_end_idx] = '\0';
        host_slice = host_chars.into_iter().collect();
        data.host = Some(host_slice[1..hostname_end_idx].to_string());
        p_idx += hostname_end_idx + 1;

        if p_idx < p_end && !is_ssh && p.as_bytes()[p_idx] == b':' {
            let port_slice = p[p_idx + 1..].to_string();
            let port_end = scan_decimal_number(Some(&port_slice))?;
            let port_end_idx = port_end.as_ptr() as usize - port_slice.as_ptr() as usize;
            data.port = Some(port_slice[..port_end_idx].to_string());
            p_idx += port_end_idx + 1;
        }
    } else {
        // Regular hostname - changed to use just Unreserved since we can't bitwise OR
        let hostname_end = scan_part(Some(&host_slice), Unreserved, ':', '/')?;
        let hostname_end_idx = hostname_end.as_ptr() as usize - host_slice.as_ptr() as usize;
        data.host = Some(host_slice[..hostname_end_idx].to_string());

        if !is_ssh && hostname_end.starts_with(':') {
            let port_slice = host_slice[hostname_end_idx + 1..].to_string();
            let port_end = scan_decimal_number(Some(&port_slice))?;
            let port_end_idx = port_end.as_ptr() as usize - port_slice.as_ptr() as usize;
            data.port = Some(port_slice[..port_end_idx].to_string());
            p_idx += hostname_end_idx + port_end_idx + 1;
        } else {
            p_idx += hostname_end_idx;
        }
    }

    // Adjust pointers (equivalent to memmove)
    {
        let src = &p[second_slash_idx + 1..p_idx];
        let mut dst = p[second_slash_idx..].to_string();
        dst.replace_range(..src.len(), src);
        p_idx -= 1;
    }

    // Adjust string references
    if let Some(userinfo) = &mut data.userinfo {
        *userinfo = userinfo[1..].to_string();
    }
    if let Some(host) = &mut data.host {
        *host = host[1..].to_string();
    }
    if let Some(port) = &mut data.port {
        *port = port[1..].to_string();
    }

    p.truncate(p_idx);

    // Handle path, query, and fragment
    let mut path_slice = p[p_idx..].to_string();
    let path_end = scan_part(Some(&path_slice), PCharSlash, '?', '#')?;
    let path_end_idx = path_end.as_ptr() as usize - path_slice.as_ptr() as usize;
    let has_query = path_end.starts_with('?');
    let has_fragment = path_end.starts_with('#');
    let mut path_chars: Vec<char> = path_slice.chars().collect();
    path_chars[path_end_idx] = '\0';
    path_slice = path_chars.into_iter().collect();
    data.path = decode_percent(&mut path_slice[..path_end_idx].to_string()).map(|s| s.to_string());
    p_idx += path_end_idx + 1;

    if has_query {
        let mut query_slice = p[p_idx..].to_string();
        let query_end = scan_part(Some(&query_slice), Query, '#', '\0')?;
        let query_end_idx = query_end.as_ptr() as usize - query_slice.as_ptr() as usize;
        let has_fragment = query_end.starts_with('#');
        let mut query_chars: Vec<char> = query_slice.chars().collect();
        query_chars[query_end_idx] = '\0';
        query_slice = query_chars.into_iter().collect();
        data.query = parse_query_string(Some(&query_slice[..query_end_idx]), None);

        if has_fragment {
            let fragment_slice = query_slice[query_end_idx + 1..].to_string();
            let _fragment_end = scan_part(Some(&fragment_slice), Fragment, '\0', '\0')?;
            data.fragment = decode_percent(&mut fragment_slice.to_string()).map(|s| s.to_string());
        }
    } else if has_fragment {
        let mut fragment_slice = p[p_idx..].to_string();
        let _fragment_end = scan_part(Some(&fragment_slice), Fragment, '\0', '\0')?;
        data.fragment = decode_percent(&mut fragment_slice.to_string()).map(|s| s.to_string());
    }

    Some(data)
}
pub fn url_get_fragment(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = match data.as_ref().and_then(|d| d.fragment.as_ref()) {
        Some(fragment) => strdup(Some(fragment)),
        None => None,
    };
    url_free(data);
    out
}
pub fn url_data_inspect(data: &UrlData) {
    println!("#url =>");
    
    println!("    .protocol: {}", match &data.protocol {
        Some(protocol) => format!("\"{}\"", protocol),
        None => "(NULL)".to_string(),
    });
    
    println!("    .host: {}", match &data.host {
        Some(host) => format!("\"{}\"", host),
        None => "(NULL)".to_string(),
    });
    
    println!("    .userinfo: {}", match &data.userinfo {
        Some(userinfo) => format!("\"{}\"", userinfo),
        None => "(NULL)".to_string(),
    });
    
    println!("    .host: {}", match &data.host {
        Some(host) => format!("\"{}\"", host),
        None => "(NULL)".to_string(),
    });
    
    println!("    .port: {}", match &data.port {
        Some(port) => format!("\"{}\"", port),
        None => "(NULL)".to_string(),
    });
    
    println!("    .path: {}", match &data.path {
        Some(path) => format!("\"{}\"", path),
        None => "(NULL)".to_string(),
    });
    
    if let Some(query) = &data.query {
        for (nr, kv) in query.iter().enumerate() {
            print!("    .query[{}]: \"{}\" -> ", nr, kv.key.as_ref().unwrap_or(&"(NULL)".to_string()));
            println!("{}", match &kv.value {
                Some(value) => format!("\"{}\"", value),
                None => "(NULL)".to_string(),
            });
        }
    }
    
    println!("    .fragment: {}", match &data.fragment {
        Some(fragment) => format!("\"{}\"", fragment),
        None => "(NULL)".to_string(),
    });
}
pub fn url_get_query_value<'a>(url: &'a UrlData, key: Option<&'a str>) -> Option<&'a str> {
    // Check if query is None (equivalent to checking for NULL in C)
    let query = url.query.as_ref()?;
    
    // If key is None, return None early
    let key = key?;

    // Iterate through the key-value pairs
    for kv in query {
        // Compare keys if both exist
        if let (Some(k), Some(v)) = (&kv.key, &kv.value) {
            if k == key {
                return Some(v);
            }
        }
    }

    None
}
pub fn url_inspect(url: Option<&str>) {
    if let Some(parsed_url) = url_parse(url) {
        url_data_inspect(&parsed_url);
    }
}
pub fn url_get_userinfo(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = match data.as_ref().and_then(|d| d.userinfo.as_ref()) {
        Some(userinfo) => strdup(Some(userinfo.as_str())),
        None => None,
    };
    url_free(data);
    out
}
pub fn url_get_hostname(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = match data.as_ref().and_then(|d| d.host.as_ref()) {
        Some(host) => strdup(Some(host)),
        None => None,
    };
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
    let out = match &data {
        Some(d) => d.host.as_ref().map(|host| host.to_string()),
        None => None,
    };
    url_free(data);
    out
}

pub fn url_get_pathname(url: Option<&str>) -> Option<String> {
    let data = url_parse(url);
    let out = data.as_ref().and_then(|d| d.path.as_ref()).map(|p| p.to_string());
    url_free(data);
    out
}
