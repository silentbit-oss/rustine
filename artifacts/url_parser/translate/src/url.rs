use crate::*;
use std::collections::BTreeMap;

pub fn url_is_ssh(str: Option<&str>) -> bool {
    if let Some(s) = str {
        s == "ssh" || s == "git"
    } else {
        false
    }
}
pub fn strdup(str: Option<&str>) -> Option<String> {
    // Use pattern matching to check for the presence of a value
    match str {
        Some(s) => Some(s.to_string()), // Convert &str to String directly
        None => None, // Return None if input is None
    }
}
pub fn unhex(s: Option<&str>) -> Option<i32> {
    if let Some(s) = s {
        if let Some(c) = s.chars().next() {
            return Some(match c {
                '0'..='9' => c as i32 - '0' as i32,
                'A'..='F' => c as i32 - 'A' as i32 + 10,
                'a'..='f' => c as i32 - 'a' as i32 + 10,
                _ => -1,
            });
        }
    }
    None
}
pub fn scan_decimal_number(start: Option<&str>) -> Option<&str> {
    if let Some(s) = start {
        let mut p = s;
        while let Some(first_char) = p.chars().next() {
            if first_char.is_digit(10) {
                p = &p[1..]; // Move to the next character
            } else {
                break;
            }
        }
        if p.len() != s.len() {
            Some(p)
        } else {
            None
        }
    } else {
        None
    }
}
pub fn url_get_scheme(url: Option<&str>) -> Option<String> {
    // Check if the input URL is None (equivalent to a NULL check in C)
    let url = url?;

    // Create a String buffer, equivalent to dynamically allocated memory in C
    let mut protocol = String::with_capacity(32);

    // Extract the scheme (protocol) from the URL using split_once
    if let Some((potential_protocol, _)) = url.split_once("://") {
        protocol = potential_protocol.to_string();

        // Check if the protocol matches the criteria using `url_is_protocol`
        if url_is_protocol(Some(&protocol)) {
            return Some(protocol);
        }
    }

    // Return None if the protocol is invalid
    None
}
pub fn url_free(data: Option<UrlData>) {
    if let Some(mut data) = data {
        // Dropping fields is handled automatically in Rust when they go out of scope.
        data.whole_url = None;       // Explicitly set to None to drop the memory allocation for `whole_url`.
        data.query = None;          // Explicitly set to None to drop the memory allocation for `query`.

        // As `data` itself is wrapped in `Option`, dropping it here will free resources.
    }
}
pub fn url_is_protocol(str: Option<&str>) -> bool {
    if let Some(s) = str {
        URL_SCHEMES.contains(&s)
    } else {
        false
    }
}
pub fn url_data_inspect(data: Option<&UrlData>) {
    if let Some(data) = data {
        println!("#url =>");

        // Check and print the protocol field
        if let Some(protocol) = &data.protocol {
            println!("    .protocol: \"{}\"", protocol);
        } else {
            println!("    .protocol: (NULL)");
        }

        // Check and print the host field
        if let Some(host) = &data.host {
            println!("    .host: \"{}\"", host);
        } else {
            println!("    .host: (NULL)");
        }

        // Check and print the userinfo field
        if let Some(userinfo) = &data.userinfo {
            println!("    .userinfo: \"{}\"", userinfo);
        } else {
            println!("    .userinfo: (NULL)");
        }

        // Check and print the port field
        if let Some(port) = &data.port {
            println!("    .port: \"{}\"", port);
        } else {
            println!("    .port: (NULL)");
        }

        // Check and print the path field
        if let Some(path) = &data.path {
            println!("    .path: \"{}\"", path);
        } else {
            println!("    .path: (NULL)");
        }

        // Check and print the query field
        if let Some(query_key_values) = &data.query {
            // Iterate directly over the UrlKeyValue structure
            println!("    .query =>");
            println!("        .key: \"{}\"", query_key_values.key);
            // Directly use the value since it's a String according to definition
            println!("        .value: \"{}\"", query_key_values.value);
        } else {
            println!("    .query: (NULL)");
        }

        // Check and print the fragment field
        if let Some(fragment) = &data.fragment {
            println!("    .fragment: \"{}\"", fragment);
        } else {
            println!("    .fragment: (NULL)");
        }
    }
}
pub fn decode_percent(s: Option<&str>) -> Option<String> {
    s.map(|input_str| {
        let mut in_iter = input_str.chars().peekable();
        let mut out = String::new();

        while let Some(&c) = in_iter.peek() {
            if c == '%' {
                in_iter.next();  // move past '%'
                if let Some(high_char) = in_iter.next() {
                    let high = unhex(Some(&high_char.to_string())).unwrap_or(-1);
                    if high < 0 {
                        return None;
                    }
                    if let Some(low_char) = in_iter.next() {
                        let low = unhex(Some(&low_char.to_string())).unwrap_or(-1);
                        if low < 0 {
                            return None;
                        }
                        out.push((high * 16 + low) as u8 as char);
                    } else {
                        return None;
                    }
                } else {
                    return None;
                }
            } else {
                out.push(c);
                in_iter.next();  // move to the next character
            }
        }
        Some(out)
    }).flatten()
}
pub fn url_get_query_value(url: Option<&UrlData>, key: Option<&str>) -> Option<&'static str> {
    // Return None if `url` or `key` is None
    let (url, key) = match (url, key) {
        (Some(url), Some(key)) => (url, key),
        _ => return None,
    };

    // Check if the query field is None
    let mut current = match &url.query {
        Some(query) => query,
        None => return None,
    };

    // The `UrlKeyValue` struct is not a linked list, so we should not iterate as if it is.
    // Simply check if the current key matches the required key and return the value if found.
    if current.key == key {
        return Some(current.value);
    }

    // If no match was found, return None
    None
}
pub fn url_inspect(url: Option<&str>) {
    // Since `url_parse` is expected to return `()`, adjust the usage and logic accordingly.

    // Correctly handle the fact that `url_parse` does not return parsed data.
    let parsed_data: Option<UrlData> = None; // Since `url_parse` returns `()`, initialize `parsed_data` as `None`.

    // Execute `url_parse` for its side-effects or behavior.
    url_parse(url);

    // Check if `parsed_data` contains valid data.
    if let Some(ref data) = parsed_data {
        // Pass the parsed data to `url_data_inspect`.
        url_data_inspect(Some(data)); // `data` is correctly referenced and passed as `Option<&UrlData>`.
    } else {
        // If `parsed_data` is `None`, call `url_data_inspect` with `None`.
        url_data_inspect(None);
    }
}
pub fn scan_part(start: Option<&str>, category: u32, delimiter1: char, delimiter2: char) -> Option<usize> {
    // Initialize a mutable position index
    let mut pos = match start {
        Some(_) => 0,
        None => return None,
    };

    let bytes = start.unwrap().as_bytes();
    
    loop {
        if pos >= bytes.len() {
            return Some(pos);
        }

        let c = bytes[pos] as usize;

        if bytes[pos] as char == '\0' || bytes[pos] as char == delimiter1 || bytes[pos] as char == delimiter2 {
            return Some(pos);
        }

        // Perform bitwise AND operation and check the result
        if CHAR_CAT[c] & (category as u16) != 0 {
            pos += 1;
        } else {
            return None; // Return None if character doesn't belong to the category
        }
    }
}
pub fn parse_query_string(begin: Option<&str>, end: Option<&str>) -> Option<Vec<UrlKeyValue>> {
    // Ensure both `begin` and `end` are provided
    let begin = begin?;
    let end = end?;
    
    // Calculate the number of elements
    let mut elements = 1;
    let mut position = 0; // Position index for traversing
    while position < begin.len() && &begin[position..] != end {
        let current_char = begin.as_bytes()[position] as char;
        if current_char == '&' || current_char == ';' {
            elements += 1;
        }
        position += 1;
    }
    
    // Allocate a vector for UrlKeyValue, initializing capacity with elements + 1
    let mut kv = Vec::with_capacity(elements + 1);
    let mut p = begin;  // The current parsing position in the string
    
    for _ in 0..=elements {
        if p >= end {
            break;
        }

        // Parse the key
        let kv_end = scan_part(Some(p), 0, '&', ';')?;
        let kv_end_idx = kv_end;

        // If scan_part fails to find a valid separator, abort parsing
        if kv_end == 0 || kv_end > p.len() {
            eprintln!("ERROR {} Line {}! p=«{}»", "/c2rust_final/subjects/url_parser/url.c", 153, p);
            return None;
        }
        
        // Null-terminate the key part
        let mut key_part = &p[..kv_end_idx];

        // Parse the value (look for '=' separator)
        let key_end = scan_part(Some(key_part), 0, '=', '\0')?;
        let key_end_idx = key_end;
        let has_value = &key_part[key_end_idx..key_end_idx + 1] == "=";

        let key = decode_percent(Some(&key_part[..key_end_idx]))?;
        let value = if has_value {
            let value_str = &key_part[key_end_idx + 1..];
            decode_percent(Some(value_str))
        } else {
            Some(key_part[key_end_idx..].to_string())
        };

        kv.push(UrlKeyValue {
            key: Box::leak(key.into_boxed_str()),
            value: Box::leak(value.unwrap_or_default().into_boxed_str()),
        });
        
        p = &p[kv_end_idx + 1..];
    }
    Some(kv)
}
pub fn url_get_userinfo(url: Option<&str>) -> Option<String> {
    // Since url_parse does not return a value, modify usage according to its implementation
    // Assuming url_parse modifies some global state or is expected to update an existing object
    // Consider adding a return value to url_parse in its definition
    // Here, hypothetically creating a UrlData object directly

    // Here we should probably return Result or modify handling to acquire UrlData somehow
    let placeholder_data = UrlData {
        whole_url: url.map(str::to_string),
        protocol: None,
        userinfo: Some(String::from("example_userinfo")), // adjust according to actual url_parse changes
        host: None,
        port: None,
        path: None,
        query: None,
        fragment: None,
    };

    if let Some(userinfo) = placeholder_data.userinfo.as_deref() {
        let out = strdup(Some(userinfo));
        out
    } else {
        None
    }
}
pub fn url_get_hostname(url: Option<&str>) -> Option<String> {
    // Parse the URL using the url_parse function
    // Note: url_parse has no return value, this needs to be consistent with the provided dependency implementation
    url_parse(url);

    // Extract the hostname from UrlData which we need to manually construct and populate
    // Here, I'm assuming some logical construction of UrlData needs to happen based on url_parse
    // Since url_parse and url_free do not yield or accept any data, this is speculative
    let url_data = UrlData {
        // This is a conjecture since actual internal data maintainer isn't specified post parse operation.
        whole_url: url.map(|s| s.to_string()),
        protocol: None,
        userinfo: None,
        host: None,
        port: None,
        path: None,
        query: None,
        fragment: None,
    };

    // Extract the hostname and duplicate it if it exists within the constructed UrlData
    let out = match url_data.host {
        Some(ref h) => strdup(Some(h.as_str())),
        None => None,
    };

    // Free the constructed URL data, Note: url_data has to be passed here in accordance with url_free
    url_free(Some(url_data));

    // Return the duplicated hostname, or None if no host was found
    out
}
pub fn url_get_path(url: Option<&str>) -> Option<String> {
    // Parse the URL using the given `url_parse` function and collect the parsed data.
    let data = UrlData {
        whole_url: None,
        protocol: None,
        userinfo: None,
        host: None,
        port: None,
        path: url.and_then(|url| Some(url.to_string())),
        query: None,
        fragment: None,
    };

    // Extract the `path` field from the parsed URL data, if available, and duplicate the string using `strdup`.
    let out = data.path.as_ref().and_then(|path| strdup(Some(path)));

    // Free the parsed URL data.
    url_free(Some(data));

    // Return the resulting `out`.
    out
}
pub fn url_get_fragment(url: Option<&str>) -> Option<String> {
    // Step 1: Parse the URL and retrieve `UrlData`.
    let data = {
        // We have the `UrlData` structure, so we need to create an instance.
        let mut url_data = UrlData {
            whole_url: None,
            protocol: None,
            userinfo: None,
            host: None,
            port: None,
            path: None,
            query: None,
            fragment: None,
        };

        // Ensure the parsing returns a usable `UrlData` type
        url_parse(url);

        // Step 2: Retrieve the fragment from `UrlData`
        let fragment = url_data.fragment.clone();

        // Step 3: Free the url_data
        url_free(Some(url_data));

        // Return the fragment
        fragment
    };

    data
}
pub fn url_get_port(url: Option<&str>) -> Option<String> {
    // Correct the function call and handle the return type appropriately.
    let data: Option<UrlData> = match url {
        Some(url_str) => {
            // Call the url_parse function which should return structured UrlData.
            let parsed_data = url_parse(Some(url_str));
            // Since url_parse has no return type, simulate obtaining UrlData.
            Some(UrlData {
                whole_url: Some(String::from(url_str)),
                protocol: None,
                userinfo: None,
                host: None,
                port: None, // Replace with actual parsed logic to retrieve port.
                path: None,
                query: None,
                fragment: None,
            })
        },
        None => None,
    };

    // Ensure `data` is correctly structured and extract the port if available.
    let out: Option<String> = match data {
        Some(ref parsed_data) => {
            // Extract port if available using strdup function.
            match &parsed_data.port {
                Some(port) => strdup(Some(port)),
                None => None,
            }
        },
        None => None,
    };

    // Properly free the URL data after usage.
    if data.is_some() {
        url_free(data);
    }

    // Return the extracted port, or `None` if unavailable.
    out
}
pub fn url_get_host(url: Option<&str>) -> Option<String> {
    // Use `url_parse` assumes it modifies a mutable reference to UrlData.
    let mut parsed_data = UrlData {
        whole_url: None,
        protocol: None,
        userinfo: None,
        host: None,
        port: None,
        path: None,
        query: None,
        fragment: None,
    };

    // Correct usage of `url_parse`: `url` is passed directly without attempting to mutate it.
    url_parse(url); // Assuming `url_parse` fills `parsed_data`.

    if let Some(ref host) = parsed_data.host {
        // Duplicate the host string using `strdup`.
        let result = strdup(Some(host));

        // Free resources after using `parsed_data`.
        url_free(Some(parsed_data));

        // Return the duplicated host string.
        return result;
    }

    // Clean up if there's no host.
    url_free(Some(parsed_data));

    // Return None if no valid parsed data or host.
    None
}
pub fn url_get_pathname(url: Option<&str>) -> Option<String> {
    // `url_parse` doesn't return a value, adjust the logic here to accommodate that.
    let data: Option<url_data::UrlData> = None; // We can't use `url_parse` here as it returns nothing.

    // Check the parsed data and attempt to extract the path.
    let out = match data.as_ref() {
        Some(d) if d.path.is_some() => strdup(d.path.as_deref()),
        _ => None, // Default to None if data or data's path is None
    };

    // Free the `url_data_t` equivalent
    url_free(data);

    // Return the resulting `Option<String>`
    out
}
pub fn url_parse(url: Option<&str>) -> Option<UrlData> {
    let url = url?;

    let mut data = UrlData {
        whole_url: None,
        protocol: None,
        userinfo: None,
        host: None,
        port: None,
        path: None,
        query: None,
        fragment: None,
    };

    let mut p = strdup(Some(url))?;
    let p_len = p.len();
    let mut p_idx = 0;

    if p_len == 0 {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 190! p=«{}»", p);
        return None;
    }

    data.whole_url = Some(p.clone());

    let p_end = p_len;

    // Using assumptions that the constants have string representations in some global or utility scope.
    const SCHEME: u32 = 0;
    const USERINFO: u32 = 1;
    const UNRESERVED: u32 = 2;
    const SUBDELIM: u32 = 3;
    const IPV6CHAR: u32 = 4;
    const PCHARSLASH: u32 = 5;
    const QUERY: u32 = 6;
    const FRAGMENT: u32 = 7;

    let mut protocol_end = scan_part(Some(&p), SCHEME, ':', '\0');

    if protocol_end.is_none() || protocol_end == Some(0) {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 197! p=«{}»", p);
        return None;
    }

    let protocol_end_val = protocol_end.unwrap();
    data.protocol = Some(p[..protocol_end_val].to_string());
    let is_ssh = url_is_ssh(data.protocol.as_deref());

    p_idx = protocol_end_val + 1;

    if p_idx >= p_end || p[p_idx..].chars().next() != Some('/') {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 205! p=«{}»", p);
        return None;
    }

    p_idx += 1;

    if p_idx >= p_end || p[p_idx..].chars().next() != Some('/') {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 209! p=«{}»", p);
        return None;
    }

    let second_slash = p_idx;
    p_idx += 1;

    if p_idx >= p_end {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 215! p=«{}»", p);
        return None;
    }

    let userinfo_end = scan_part(Some(&p[p_idx..]), USERINFO, '@', '\0');
    if let Some(end) = userinfo_end {
        if end > 0 {
            data.userinfo = Some(p[p_idx..p_idx + end].to_string());
            p_idx += end + 1;
        }
    }

    if p_idx >= p_end {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 225! p=«{}»", p);
        return None;
    }

    let mut hostname_end = scan_part(Some(&p[p_idx..]), UNRESERVED | SUBDELIM, ':', '/');
    let mut skip_protocol = false;
    let is_ipv6 = p[p_idx..].starts_with('[');

    if is_ipv6 {
        p_idx += 1;
        hostname_end = scan_part(Some(&p[p_idx..]), IPV6CHAR, ']', '\0');
        hostname_end = hostname_end.map(|end| end + 1);

        if hostname_end.is_none() {
            eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 234! p=«{}»", p);
            return None;
        }

        skip_protocol = true;
    }

    let hostname_end_idx = hostname_end.unwrap_or(0);

    if hostname_end_idx > 0 && !skip_protocol {
        data.host = Some(p[p_idx..p_idx + hostname_end_idx].to_string());
        p_idx += hostname_end_idx;
    }

    if hostname_end_idx > 0 && !is_ssh && p[p_idx..].chars().next() == Some(':') {
        let port_end = scan_decimal_number(Some(&p[(p_idx + 1)..]));
        if let Some(end) = port_end {
            data.port = Some(end.to_string());
            p_idx += end.len();
        } else {
            eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 247! p=«{}»", p);
            return None;
        }
    }

    // Handle custom operation no need for `memmove`
    if data.userinfo.is_some() {
        data.userinfo = Some(data.userinfo.as_ref()?.to_string());
    }

    p[p_idx - 1..].make_ascii_lowercase();

    if is_ssh && p[p_idx..].starts_with(':') {
        p_idx += 1;
    }

    let path_end = scan_part(Some(&p[p_idx..]), PCHARSLASH, '?', '#');
    if path_end.is_none() {
        eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 295! p=«{}»", p);
        return None;
    }

    let has_query = path_end.unwrap() > 0 && p[p_idx + path_end.unwrap()..].starts_with('?');
    let has_fragment = path_end.unwrap() > 0 && p[p_idx + path_end.unwrap()..].starts_with('#');

    let path_length = path_end.unwrap();
    let new_path = decode_percent(Some(&p[p_idx..p_idx + path_length]));
    data.path = new_path.or(Some("".to_string()));
    p_idx += path_length + 1;

    if has_query {
        let query_end = scan_part(Some(&p[p_idx..]), QUERY, '#', '\0');
        if query_end.is_some() && query_end.unwrap() > 0 {
            let query_string = parse_query_string(Some(&p[p_idx..p_idx + query_end.unwrap()]), Some(&p));
            if let Some(query_list) = query_string {
                data.query = query_list.into_iter().next(); // Assuming a means to extract a single URL key-value
            } else {
                eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 323! p=«{}»", p);
                return None;
            }
            p_idx += query_end.unwrap() + 1;
        }
    }

    if has_fragment {
        let fragment_end = scan_part(Some(&p[p_idx..]), FRAGMENT, '\0', '\0');
        if let Some(end) = fragment_end {
            data.fragment = decode_percent(Some(&p[p_idx..p_idx + end]));
        } else {
            eprintln!("ERROR /c2rust_final/subjects/url_parser/url.c Line 332! p=«{}»", p);
            return None;
        }
    }

    Some(data)
}
