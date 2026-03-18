use crate::*;
use std::ascii;
use std::char;
use std::ascii::AsciiExt;
use std::ffi::CStr;
use crate::SdAutolinkFlags::SD_AUTOLINK_SHORT_DOMAINS;
pub fn helper_autolink_delim_1(link_end_ref: &mut usize, data: &[u8]) {
    let mut link_end = *link_end_ref;
    if link_end == 0 {
        return;
    }

    let c = data[link_end - 1];
    if c == 0 {
        return;
    }

    if b"?!.,".contains(&c) {
        link_end -= 1;
    } else if c == b';' {
        let mut new_end = link_end.saturating_sub(2);
        while new_end > 0 && data[new_end].is_ascii_alphabetic() {
            new_end -= 1;
        }

        if new_end < link_end - 2 && data[new_end] == b'&' {
            link_end = new_end;
        } else {
            link_end -= 1;
        }
    } else {
        return;
    }

    *link_end_ref = link_end;
}
pub fn autolink_delim(data: &[u8], link_end: usize, max_rewind: usize, size: usize) -> usize {
    let mut link_end = link_end;
    let mut copen = 0u8;

    // Find first '<' character
    for i in 0..link_end {
        if data[i] == b'<' {
            link_end = i;
            break;
        }
    }

    // Process link_end with helper function
    while link_end > 0 {
        helper_autolink_delim_1(&mut link_end, data);
    }

    if link_end == 0 {
        return 0;
    }

    let cclose = data[link_end - 1];
    copen = match cclose {
        b'"' => b'"',
        b'\'' => b'\'',
        b')' => b'(',
        b']' => b'[',
        b'}' => b'{',
        _ => 0,
    };

    if copen != 0 {
        let mut closing = 0;
        let mut opening = 0;
        let mut i = 0;
        while i < link_end {
            if data[i] == copen {
                opening += 1;
            } else if data[i] == cclose {
                closing += 1;
            }
            i += 1;
        }

        if closing != opening {
            link_end -= 1;
        }
    }

    link_end
}

pub fn sd_autolink__email(
    rewind_p: &mut usize,
    link: &mut Buf,
    data: &[u8],
    max_rewind: usize,
    size: usize,
    _flags: u32,
) -> usize {
    // First loop: find rewind position
    let mut rewind = 0;
    for i in 0..max_rewind {
        let c = data.get(data.len().wrapping_sub(i + 1)).copied().unwrap_or(0);
        if c == 0 {
            break;
        }
        if c.is_ascii_alphanumeric() {
            continue;
        }
        if b".+-_".contains(&c) {
            continue;
        }
        rewind = i + 1;
        break;
    }

    if rewind == 0 {
        return 0;
    }

    // Second loop: find link_end and count @ and .
    let mut nb = 0;
    let mut np = 0;
    let mut link_end = 0;

    for (i, &c) in data.iter().enumerate().take(size) {
        if c.is_ascii_alphanumeric() {
            continue;
        }
        if c == b'@' {
            nb += 1;
        } else if c == b'.' && i < size - 1 {
            np += 1;
        } else if c != b'-' && c != b'_' {
            link_end = i;
            break;
        }
    }

    if link_end < 2 || nb != 1 || np == 0 {
        return 0;
    }

    let link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 {
        return 0;
    }

    let start = data.len() - rewind;
    bufput(link, &data[start..], link_end + rewind);
    *rewind_p = rewind;
    link_end
}
extern "C" {
    fn isspace(c: i32) -> i32;
}

pub fn check_reddit_autolink_prefix(
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
    prefix_char: char,
) -> i32 {
    if size < 2 || max_rewind < 1 || data[0] != prefix_char as u8 {
        return 0;
    }

    if max_rewind > 1 {
        let boundary = data[1] as char;
        if boundary == '/' {
            return 2;
        } else if boundary.is_ascii_punctuation() || unsafe { isspace(boundary as i32) } != 0 {
            return 1;
        } else {
            return 0;
        }
    } else if max_lookbehind > 2 {
        if data[1] == b'/' && data[2] == b'\\' {
            return 0;
        }
    }

    1
}
                          // In newer Rust, you can use str::eq_ignore_ascii_case directly

pub fn helper_sd_autolink__subreddit_1(link_end_ref: &mut usize, data: &[u8], size: usize) -> usize {
    let mut link_end = *link_end_ref;
    let start = link_end;
    let mut max_length = 24;

    if size >= link_end + 10 {
        let slice = &data[link_end..link_end + 10];
        if slice.eq_ignore_ascii_case(b"reddit.com") {
            link_end += 10;
            max_length = 10;
        } else if size > link_end + 2 {
            let slice = &data[link_end..link_end + 2];
            if slice.eq_ignore_ascii_case(b"t:") {
                link_end += 2;
            }
        }
    }

    if link_end >= size || !data[link_end].is_ascii_alphanumeric() {
        return 0;
    }
    link_end += 1;

    while link_end < size && (data[link_end].is_ascii_alphanumeric() || data[link_end] == b'_') {
        link_end += 1;
    }

    if (link_end - start) < 2 || (link_end - start) > max_length {
        return 0;
    }

    *link_end_ref = link_end;
    1 // Return 1 to indicate success (since C returns non-zero for success)
}
pub fn sd_autolink__subreddit(
    rewind_p: &mut usize,
    link: &mut Buf,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
    no_slash: &mut bool,
) -> usize {
    let mut link_end;
    let mut rewind;
    let mut is_allminus = false;
    
    rewind = check_reddit_autolink_prefix(data, max_rewind, max_lookbehind, size, 'r');
    if rewind == 0 {
        return 0;
    }
    
    link_end = 1; // Equivalent to strlen("/") since "/" is 1 byte
    if size >= (link_end + 4) && data[link_end..].starts_with(b"all-") {
        is_allminus = true;
    }
    
    loop {
        helper_sd_autolink__subreddit_1(&mut link_end, data, size);
        if !(link_end < size && (data[link_end] == b'+' || (is_allminus && data[link_end] == b'-'))) {
            break;
        }
        link_end += 1;
    }
    
    if link_end < size && data[link_end] == b'/' {
        while link_end < size && (data[link_end].is_ascii_alphanumeric() 
               || data[link_end] == b'_' 
               || data[link_end] == b'/' 
               || data[link_end] == b'-') {
            link_end += 1;
        }
    }
    
    let rewind_usize = rewind as usize;
    bufput(link, &data[..rewind_usize], link_end + rewind_usize);
    *no_slash = rewind_usize == 1;
    *rewind_p = rewind_usize;
    
    link_end
}
pub fn sd_autolink__username(
    rewind_p: &mut usize,
    link: &mut Buf,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
    no_slash: &mut i32,
) -> usize {
    if size < 3 {
        return 0;
    }

    let rewind = check_reddit_autolink_prefix(data, max_rewind, max_lookbehind, size, 'u');
    if rewind == 0 {
        return 0;
    }

    let link_end = CStr::from_bytes_with_nul(b"/\0")
        .unwrap()
        .to_bytes()
        .len();
    if !data[link_end].is_ascii_alphanumeric() && data[link_end] != b'_' && data[link_end] != b'-' {
        return 0;
    }

    let mut link_end = link_end + 1;
    while link_end < size
        && (data[link_end].is_ascii_alphanumeric()
            || data[link_end] == b'_'
            || data[link_end] == b'/'
            || data[link_end] == b'-')
    {
        link_end += 1;
    }

    bufput(link, &data[(rewind as usize)..link_end + (rewind as usize)], link_end + (rewind as usize));
    *no_slash = if rewind == 1 { 1 } else { 0 };
    *rewind_p = rewind as usize;
    link_end
}
pub fn check_domain(data: &[u8], allow_short: bool) -> usize {
    let mut np = 0;
    if !data[0].is_ascii_alphanumeric() {
        return 0;
    }
    
    let mut i = 1;
    while i < data.len().saturating_sub(1) {
        if data[i] == b'.' {
            np += 1;
        } else if !data[i].is_ascii_alphanumeric() && data[i] != b'-' {
            break;
        }
        i += 1;
    }

    if allow_short {
        i
    } else {
        if np > 0 { i } else { 0 }
    }
}

pub fn sd_autolink_issafe(link: &[u8], link_len: usize) -> bool {
    static VALID_URIS: &[&str] = &[
        "http://", "https://", "ftp://", "mailto://", "/", "git://", "steam://", 
        "irc://", "news://", "mumble://", "ssh://", "ircs://", "ts3server://", "#"
    ];

    for uri in VALID_URIS {
        let len = uri.len();
        if link_len > len {
            // Convert the link slice to a str for comparison (assuming UTF-8)
            if let Ok(link_str) = std::str::from_utf8(&link[..len]) {
                // Case-insensitive comparison (equivalent to strncasecmp)
                if link_str.eq_ignore_ascii_case(uri) {
                    // Check the next character
                    let next_char = link[len] as char;
                    if next_char.is_alphanumeric() || next_char == '#' || next_char == '/' || next_char == '?' {
                        return true;
                    }
                }
            }
        }
    }

    false
}
pub fn sd_autolink__url(
    rewind_p: &mut usize,
    link: &mut Buf,
    data: &[u8],
    max_rewind: usize,
    size: usize,
    flags: u32,
) -> usize {
    const SD_AUTOLINK_SHORT_DOMAINS: u32 = 1; // Assuming this is the correct value
    
    let mut link_end;
    let mut rewind = 0;
    let mut domain_len;

    if size < 4 || data[1] != b'/' || data[2] != b'/' {
        return 0;
    }

    while rewind < max_rewind && data[data.len().wrapping_sub(rewind + 1)].is_ascii_alphabetic() {
        rewind += 1;
    }

    if !sd_autolink_issafe(&data[data.len() - rewind..], size + rewind) {
        return 0;
    }

    link_end = "://".len();
    domain_len = check_domain(
        &data[link_end..],
        (flags & SD_AUTOLINK_SHORT_DOMAINS) != 0,
    );
    if domain_len == 0 {
        return 0;
    }

    link_end += domain_len;
    while link_end < size && !data[link_end].is_ascii_whitespace() {
        link_end += 1;
    }

    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 {
        return 0;
    }

    bufput(link, &data[data.len() - rewind..], link_end + rewind);
    *rewind_p = rewind;
    link_end
}

pub fn sd_autolink__www(
    rewind_p: &mut usize,
    link: &mut Buf,
    data: &[u8],
    max_rewind: usize,
    size: usize,
    _flags: u32,
) -> usize {
    // Check if previous character is not punctuation or whitespace
    if max_rewind > 0 && !data[0].is_ascii_punctuation() && !data[0].is_ascii_whitespace() {
        return 0;
    }

    // Check minimum size and "www." prefix
    if size < 4 || !data.starts_with(b"www.") {
        return 0;
    }

    let mut link_end = check_domain(data, false);
    if link_end == 0 {
        return 0;
    }

    // Extend link_end while not whitespace
    while link_end < size && !data[link_end].is_ascii_whitespace() {
        link_end += 1;
    }

    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 {
        return 0;
    }

    bufput(link, &data[..link_end], link_end);
    *rewind_p = 0;
    link_end
}
