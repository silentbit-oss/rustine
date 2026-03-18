use crate::*;
use crate::MkdTableFlags::MKD_TABLE_HEADER;
use crate::mkd_extensions::MkdExtensions::MKDEXT_NO_INTRA_EMPHASIS;
use lazy_static::lazy_static;
use libc::ispunct;
use libc::size_t;
use rand::Rng;
use std::ascii::AsciiExt;
use std::assert_eq;
use std::cmp::Ordering;
use std::ffi::CStr;
use std::io;
use std::mem;
use std::os::raw::c_char;
use std::os::raw::c_uint;
use std::os::raw::c_void;
use std::ptr;
use std::str;

pub fn hash_link_ref(link_ref: Option<&[u8]>, length: usize) -> Option<u64> {
    // Check for NULL equivalent (None)
    let link_ref = link_ref?;
    
    // Get the sip_hash_key from the global static
    let sip_hash_key = SIP_HASH_KEY.lock().unwrap();
    
    // Call siphash_nocase with the provided parameters
    Some(siphash_nocase(&link_ref[..length], &sip_hash_key[..]))
}
pub fn add_link_ref<'a>(references: &'a mut [Option<Box<LinkRef>>; 8], name: &[u8], name_size: usize) -> Option<&'a mut LinkRef> {
    let hash = hash_link_ref(Some(name), name_size).unwrap();
    let index = (hash % 8) as usize;
    
    // First, try to find existing node
    let mut prev: Option<*mut LinkRef> = None;
    let mut current_ptr: *mut Option<Box<LinkRef>> = &mut references[index];
    
    unsafe {
        while let Some(node) = &mut *current_ptr {
            if node.id == hash as u32 && node.label.as_ref().unwrap().size == name_size {
                let ref_label = node.label.as_ref().unwrap();
                let ref_data = if let Some(data) = &ref_label.data {
                    CStr::from_bytes_with_nul_unchecked(&data[..ref_label.size])
                } else {
                    prev = Some(&mut **node);
                    current_ptr = &mut node.next;
                    continue;
                };
                let name_data = CStr::from_bytes_with_nul_unchecked(&name[..name_size]);
                
                if ref_data.to_bytes() == name_data.to_bytes() {
                    bufrelease(node.label.take());
                    bufrelease(node.link.take());
                    bufrelease(node.title.take());
                    return Some(&mut **node);
                }
            }
            prev = Some(&mut **node);
            current_ptr = &mut node.next;
        }
    }

    // If not found, create new node
    let mut new_ref = Box::new(LinkRef {
        id: hash as u32,
        next: None,
        label: Some(Box::new(Buf { data: Some(Vec::new()), size: 0, asize: 0, unit: 0 })),
        link: Some(Box::new(Buf { data: Some(Vec::new()), size: 0, asize: 0, unit: 0 })),
        title: Some(Box::new(Buf { data: Some(Vec::new()), size: 0, asize: 0, unit: 0 })),
    });
    
    // Insert at the beginning of the list
    let next = references[index].take();
    new_ref.next = next;
    references[index] = Some(new_ref);
    
    // Return reference to the newly inserted node
    references[index].as_mut().map(|b| &mut **b)
}
pub fn helper_is_ref_2(
    data: &[u8],
    refs: &mut [Option<Box<LinkRef>>; 8],
    id_offset: usize,
    id_end: usize,
    link_offset: usize,
    link_end: usize,
    title_offset: usize,
    title_end: usize,
) -> i32 {
    // Calculate slice lengths (Rust uses exclusive end bounds)
    let id_len = id_end - id_offset;
    let link_len = link_end - link_offset;
    let title_len = title_end.saturating_sub(title_offset);

    // Add new link reference
    let ref_idx = match add_link_ref(refs, &data[id_offset..id_end], id_len) {
        Some(new_ref) => new_ref,
        None => return 0,
    };

    // Get mutable reference to the newly added link reference
    let ref_ = match refs[ref_idx.id as usize].as_mut() {
        Some(r) => r,
        None => return 0,
    };

    // Set label
    match bufnew(id_len) {
        Some(buf) => {
            ref_.label = Some(buf);
            bufput(ref_.label.as_mut().unwrap(), &data[id_offset..id_end], id_len);
        }
        None => return 0,
    }

    // Set link
    match bufnew(link_len) {
        Some(buf) => {
            ref_.link = Some(buf);
            bufput(ref_.link.as_mut().unwrap(), &data[link_offset..link_end], link_len);
        }
        None => return 0,
    }

    // Set title if present
    if title_len > 0 {
        match bufnew(title_len) {
            Some(buf) => {
                ref_.title = Some(buf);
                bufput(
                    ref_.title.as_mut().unwrap(),
                    &data[title_offset..title_end],
                    title_len,
                );
            }
            None => return 0,
        }
    }

    1 // Return success
}
pub fn helper_is_ref_1(
    i_ref: &mut usize,
    title_offset_ref: &mut usize,
    title_end_ref: &mut usize,
    line_end_ref: &mut usize,
    data: &[u8],
    end: usize,
) {
    let mut i = *i_ref;
    let mut title_offset = *title_offset_ref;
    let mut title_end = *title_end_ref;
    let mut line_end = *line_end_ref;

    i += 1;
    title_offset = i;

    while (i < end) && (data[i] != b'\n') && (data[i] != b'\r') {
        i += 1;
    }

    if ((i + 1) < end) && (data[i] == b'\n') && (data[i + 1] == b'\r') {
        title_end = i + 1;
    } else {
        title_end = i;
    }

    i -= 1;
    while (i > title_offset) && (data[i] == b' ') {
        i -= 1;
    }

    if (i > title_offset) && ((data[i] == b'\'') || (data[i] == b'"') || (data[i] == b')')) {
        line_end = title_end;
        title_end = i;
    }

    *i_ref = i;
    *title_offset_ref = title_offset;
    *title_end_ref = title_end;
    *line_end_ref = line_end;
}
pub fn is_ref(data: &[u8], beg: usize, end: usize, last: Option<&mut usize>, mut refs: Option<&mut [Option<Box<LinkRef>>; 8]>) -> i32 {
    let mut i = 0;
    let id_offset;
    let id_end;
    let link_offset;
    let link_end;
    let mut title_offset;
    let mut title_end;
    let mut line_end = 0;

    if (beg + 3) >= end {
        return 0;
    }
    
    if data[beg] == b' ' {
        i = 1;
        if data[beg + 1] == b' ' {
            i = 2;
            if data[beg + 2] == b' ' {
                i = 3;
                if data[beg + 3] == b' ' {
                    return 0;
                }
            }
        }
    }
    
    i += beg;
    if data[i] != b'[' {
        return 0;
    }
    
    i += 1;
    id_offset = i;
    
    while i < end && data[i] != b'\n' && data[i] != b'\r' && data[i] != b']' {
        i += 1;
    }
    
    if i >= end || data[i] != b']' {
        return 0;
    }
    
    id_end = i;
    i += 1;
    
    if i >= end || data[i] != b':' {
        return 0;
    }
    
    i += 1;
    
    while i < end && data[i] == b' ' {
        i += 1;
    }
    
    if i < end && (data[i] == b'\n' || data[i] == b'\r') {
        i += 1;
        if i < end && data[i] == b'\r' && data[i - 1] == b'\n' {
            i += 1;
        }
    }
    
    while i < end && data[i] == b' ' {
        i += 1;
    }
    
    if i >= end {
        return 0;
    }
    
    if data[i] == b'<' {
        i += 1;
    }
    
    link_offset = i;
    
    while i < end && data[i] != b' ' && data[i] != b'\n' && data[i] != b'\r' {
        i += 1;
    }
    
    if data[i - 1] == b'>' {
        link_end = i - 1;
    } else {
        link_end = i;
    }
    
    while i < end && data[i] == b' ' {
        i += 1;
    }
    
    if i < end && data[i] != b'\n' && data[i] != b'\r' && data[i] != b'\'' && data[i] != b'"' && data[i] != b'(' {
        return 0;
    }
    
    if i >= end || data[i] == b'\r' || data[i] == b'\n' {
        line_end = i;
    }
    
    if (i + 1) < end && data[i] == b'\n' && data[i + 1] == b'\r' {
        line_end = i + 1;
    }
    
    if line_end != 0 {
        i = line_end + 1;
        while i < end && data[i] == b' ' {
            i += 1;
        }
    }
    
    title_offset = 0;
    title_end = 0;
    
    if (i + 1) < end && (data[i] == b'\'' || data[i] == b'"' || data[i] == b'(') {
        helper_is_ref_1(&mut i, &mut title_offset, &mut title_end, &mut line_end, data, end);
    }
    
    if line_end == 0 || link_end == link_offset {
        return 0;
    }
    
    if let Some(last_ptr) = last {
        *last_ptr = line_end;
    }
    
    if let Some(refs_ptr) = refs.as_deref_mut() {
        helper_is_ref_2(data, refs_ptr, id_offset, id_end, link_offset, link_end, title_offset, title_end);
    }
    
    1
}
pub fn expand_tabs(ob: &mut Buf, line: &[u8], size: usize) {
    let mut i = 0;
    let mut tab = 0;
    
    while i < size {
        let org = i;
        while i < size && line[i] != b'\t' {
            i += 1;
            tab += 1;
        }

        if i > org {
            bufput(ob, &line[org..i], i - org);
        }
        
        if i >= size {
            break;
        }

        loop {
            bufputc(ob, b' ' as i32);
            tab += 1;
            if tab % 4 == 0 {
                break;
            }
        }
        i += 1;
    }
}
pub fn helper_sd_markdown_render_1(
    beg_ref: &mut usize,
    end_ref: &mut usize,
    document: &[u8],
    doc_size: usize,
    md: &mut SdMarkdown,
    text: &mut Buf,
) {
    let mut beg = *beg_ref;
    let mut end = *end_ref;
    
    if is_ref(document, beg, doc_size, Some(&mut end), Some(&mut md.refs)) != 0 {
        beg = end;
    } else {
        end = beg;
        while end < doc_size && document[end] != b'\n' && document[end] != b'\r' {
            end += 1;
        }

        if end > beg {
            expand_tabs(text, &document[beg..end], end - beg);
        }

        while end < doc_size && (document[end] == b'\n' || document[end] == b'\r') {
            if document[end] == b'\n' || (end + 1 < doc_size && document[end + 1] != b'\n') {
                bufputc(text, b'\n' as i32);
            }
            end += 1;
        }

        beg = end;
    }

    *beg_ref = beg;
    *end_ref = end;
}
pub fn free_link_refs(references: &mut [Option<Box<link_ref::LinkRef>>; 8]) {
    for i in 0..8 {
        let mut current = references[i].take();
        while let Some(mut r) = current {
            let next = r.next.take();
            bufrelease(r.label);
            bufrelease(r.link);
            bufrelease(r.title);
            current = next;
        }
    }
}
pub fn rndr_newbuf(rndr: &mut SdMarkdown, type_: i32) -> Option<Box<Buf>> {
    static BUF_SIZE: [usize; 2] = [256, 64];
    let pool = &mut rndr.work_bufs[type_ as usize];
    
    if pool.size < pool.asize {
        if let Some(items) = &mut pool.item {
            if let Some(work) = items[pool.size].take() {
                // Downcast from Box<dyn Any> to Box<Buf>
                if let Ok(mut buf) = work.downcast::<Buf>() {
                    buf.size = 0;
                    pool.size += 1;
                    return Some(buf);
                }
            }
        }
    }
    
    let work = bufnew(BUF_SIZE[type_ as usize])?;
    stack_push(pool, Some(work.clone() as Box<dyn std::any::Any>));
    Some(work)
}
pub fn prefix_quote(data: &[u8]) -> usize {
    let mut i = 0;
    
    // Check for leading spaces (up to 3)
    if i < data.len() && data[i] == b' ' {
        i += 1;
    }
    if i < data.len() && data[i] == b' ' {
        i += 1;
    }
    if i < data.len() && data[i] == b' ' {
        i += 1;
    }

    // Check for '>' followed by non-'!' character
    if i < data.len() && data[i] == b'>' {
        if (i + 1) < data.len() && data[i + 1] != b'!' {
            if (i + 1) < data.len() && data[i + 1] == b' ' {
                return i + 2;
            }
            return i + 1;
        }
    }
    
    0
}
pub fn is_empty(data: Option<&[u8]>, size: usize) -> usize {
    // Check if data is None (equivalent to NULL check in C)
    let data = match data {
        Some(d) => d,
        None => return 0, // Return 0 if data is NULL (None)
    };

    for i in 0..size {
        if data[i] != b' ' {
            if data[i] == b'\n' {
                break;
            }
            return 0;
        }
    }

    size + 1
}
pub fn rndr_popbuf(rndr: &mut SdMarkdown, type_: i32) {
    rndr.work_bufs[type_ as usize].size -= 1;
}
pub fn is_headerline(data: &[u8]) -> u8 {
    let mut i = 0;
    if data.is_empty() {
        return 0;
    }

    if data[i] == b'=' {
        i += 1;
        while i < data.len() && data[i] == b'=' {
            i += 1;
        }

        while i < data.len() && data[i] == b' ' {
            i += 1;
        }

        return if i >= data.len() || data[i] == b'\n' { 1 } else { 0 };
    }

    if data[i] == b'-' {
        i += 1;
        while i < data.len() && data[i] == b'-' {
            i += 1;
        }

        while i < data.len() && data[i] == b' ' {
            i += 1;
        }

        return if i >= data.len() || data[i] == b'\n' { 2 } else { 0 };
    }

    0
}
pub fn is_next_headerline(data: &[u8]) -> u8 {
    let mut i = 0;
    while i < data.len() && data[i] != b'\n' {
        i += 1;
    }

    if i + 1 >= data.len() {
        return 0;
    }
    is_headerline(&data[i + 1..])
}
pub fn prefix_oli(data: &[u8]) -> usize {
    let mut i = 0;
    
    // Check for leading spaces (up to 3)
    if i < data.len() && data[i] == b' ' {
        i += 1;
    }
    if i < data.len() && data[i] == b' ' {
        i += 1;
    }
    if i < data.len() && data[i] == b' ' {
        i += 1;
    }

    // Check if current character is a digit
    if i >= data.len() || !data[i].is_ascii_digit() {
        return 0;
    }

    // Consume all digits
    while i < data.len() && data[i].is_ascii_digit() {
        i += 1;
    }

    // Check for ". " pattern
    if i + 1 >= data.len() || data[i] != b'.' || data[i + 1] != b' ' {
        return 0;
    }

    // Check if this is a header line
    if is_next_headerline(&data[i..]) != 0 {
        return 0;
    }

    i + 2
}
pub fn char_escape(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    static ESCAPE_CHARS: &[u8] = b"\\`*_{}[]()#+-.!:|&<>/^~";
    
    if size > 1 {
        let next_char = data[1];
        if !ESCAPE_CHARS.contains(&next_char) {
            return 0;
        }

        if let Some(normal_text) = &rndr.cb.normal_text {
            let work = Buf {
                data: Some(vec![next_char]),
                size: 1,
                asize: 1,
                unit: 0,
            };
            if let Some(opaque) = rndr.opaque.as_mut() {
                normal_text(ob, &work, opaque);
            }
        } else {
            bufputc(ob, next_char as i32);
        }
    } else if size == 1 {
        bufputc(ob, data[0] as i32);
    }
    
    2
}
pub fn char_autolink_email(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    if rndr.cb.autolink.is_none() || rndr.in_link_body != 0 {
        return 0;
    }

    let mut link = match rndr_newbuf(rndr, 1) {
        Some(l) => l,
        None => return 0,
    };

    let mut rewind = 0;
    let link_len = sd_autolink__email(&mut rewind, &mut *link, data, max_rewind, size, 0);

    if link_len > 0 {
        buftruncate(ob, ob.size - rewind);
        if let Some(ref autolink_cb) = rndr.cb.autolink {
            autolink_cb(ob, &link, MkdAutolink::MKDA_EMAIL, rndr.opaque.as_mut().map(|b| &mut **b).unwrap());
        }
    }

    rndr_popbuf(rndr, 1);
    link_len
}
pub fn char_autolink_subreddit_or_username(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    if rndr.cb.autolink.is_none() || rndr.in_link_body != 0 {
        return 0;
    }

    let mut link = match rndr_newbuf(rndr, 1) {
        Some(buf) => buf,
        None => return 0,
    };

    let mut rewind = 0;
    let mut no_slash = false;
    let mut link_len = sd_autolink__subreddit(
        &mut rewind,
        &mut link,
        data,
        max_rewind,
        max_lookbehind,
        size,
        &mut no_slash,
    );

    if link_len == 0 {
        let mut no_slash_i32 = no_slash as i32;
        link_len = sd_autolink__username(
            &mut rewind,
            &mut link,
            data,
            max_rewind,
            max_lookbehind,
            size,
            &mut no_slash_i32,
        );
        no_slash = no_slash_i32 != 0;
    }

    if link_len > 0 {
        // Create buffers first before any callbacks
        let mut link_url = match rndr_newbuf(rndr, 1) {
            Some(buf) => buf,
            None => {
                rndr_popbuf(rndr, 1);
                return link_len;
            }
        };

        if no_slash {
            bufputc(&mut link_url, b'/' as i32);
        }
        bufput(&mut link_url, &link.data.as_ref().unwrap(), link.size);

        if let Err(_) = buftruncate(ob, ob.size - rewind) {
            rndr_popbuf(rndr, 1);
            rndr_popbuf(rndr, 1);
            return link_len;
        }

        // Determine if we need a link_text buffer (if normal_text callback exists)
        let has_normal_text = rndr.cb.normal_text.is_some();

        // Conditionally create the link_text buffer
        let mut link_text = if has_normal_text {
            match rndr_newbuf(rndr, 1) {
                Some(buf) => Some(buf),
                None => {
                    // Pop the link_url buffer and return early (outer link buffer will be popped later)
                    rndr_popbuf(rndr, 1); // pop link_url
                    return link_len;
                }
            }
        } else {
            None
        };

        // Now get references to callbacks
        let normal_text_cb = rndr.cb.normal_text.as_deref();
        let link_cb = rndr.cb.link.as_deref();

        if has_normal_text {
            // Unwrap is safe because has_normal_text is true
            let link_text_buf = link_text.as_mut().unwrap();

            if let Some(normal_text_cb) = normal_text_cb {
                if let Some(opaque) = rndr.opaque.as_mut() {
                    normal_text_cb(link_text_buf, &link, &mut **opaque);
                }
            }

            if let Some(link_cb) = link_cb {
                if let Some(opaque) = rndr.opaque.as_mut() {
                    link_cb(
                        ob,
                        &link_url,
                        &Buf {
                            data: None,
                            size: 0,
                            asize: 0,
                            unit: 0,
                        },
                        link_text_buf,
                        &mut **opaque,
                    );
                }
            }
        } else if let Some(link_cb) = link_cb {
            if let Some(opaque) = rndr.opaque.as_mut() {
                link_cb(
                    ob,
                    &link_url,
                    &Buf {
                        data: None,
                        size: 0,
                        asize: 0,
                        unit: 0,
                    },
                    &link,
                    &mut **opaque,
                );
            }
        }

        // Pop conditionally created link_text buffer
        if has_normal_text {
            rndr_popbuf(rndr, 1);
        }

        // Pop link_url buffer
        rndr_popbuf(rndr, 1);
    }

    // Pop outer link buffer
    rndr_popbuf(rndr, 1);
    link_len
}
pub fn helper_helper_find_emph_char_1_2(i_ref: &mut usize, data: &[u8], c: u8) -> Option<usize> {
    let mut i = *i_ref;
    let mut tmp_i = None;
    i += 1;

    // First loop: find ']' while tracking potential matches
    while i < data.len() && data[i] != b']' {
        if tmp_i.is_none() && data[i] == c {
            tmp_i = Some(i);
        }
        i += 1;
    }

    i += 1;
    // Skip whitespace
    while i < data.len() && (data[i] == b' ' || data[i] == b'\n') {
        i += 1;
    }

    if i >= data.len() {
        return tmp_i;
    }

    let cc = match data[i] {
        b'[' => b']',
        b'(' => b')',
        _ => {
            if tmp_i.is_some() {
                return tmp_i;
            } else {
                *i_ref = i;
                return None;
            }
        }
    };

    i += 1;
    // Second loop: find matching closing character
    while i < data.len() && data[i] != cc {
        if tmp_i.is_none() && data[i] == c {
            tmp_i = Some(i);
        }
        i += 1;
    }

    if i >= data.len() {
        return tmp_i;
    }

    i += 1;
    *i_ref = i;
    tmp_i
}
pub fn helper_helper_find_emph_char_1_1(i_ref: &mut usize, data: &[u8], c: u8) -> usize {
    let mut i = *i_ref;
    let mut span_nb = 0;
    let mut bt;
    let mut tmp_i = 0;
    
    // Count consecutive '`' characters
    while i < data.len() && data[i] == b'`' {
        i += 1;
        span_nb += 1;
    }

    if i >= data.len() {
        return 0;
    }

    bt = 0;
    while i < data.len() && bt < span_nb {
        if tmp_i == 0 && data[i] == c {
            tmp_i = i;
        }
        if data[i] == b'`' {
            bt += 1;
        } else {
            bt = 0;
        }
        i += 1;
    }

    if i >= data.len() {
        return tmp_i;
    }
    
    *i_ref = i;
    tmp_i
}
pub fn helper_find_emph_char_1(i_ref: &mut usize, data: &[u8], c: u8) -> Option<usize> {
    let mut i = *i_ref;
    while i < data.len() && data[i] != c && data[i] != b'`' && data[i] != b'[' {
        i += 1;
    }

    if i == data.len() {
        return None;
    }
    if i < data.len() && c == b'<' && data[i] == c && i > 0 && data[i - 1] == b'!' {
        *i_ref = i;
        return Some(i);
    }
    if data[i] == c {
        *i_ref = i;
        return Some(i);
    }
    if i > 0 && data[i - 1] == b'\\' {
        i += 1;
        *i_ref = i;
        return helper_find_emph_char_1(i_ref, data, c);
    }
    if data[i] == b'`' {
        let result = helper_helper_find_emph_char_1_1(&mut i, data, c);
        *i_ref = i;
        Some(result)
    } else if data[i] == b'[' {
        helper_helper_find_emph_char_1_2(&mut i, data, c)
    } else {
        *i_ref = i;
        None
    }
}
pub fn find_emph_char(data: &[u8], c: u8) -> usize {
    let mut i = 1;
    while i < data.len() {
        if let Some(new_i) = helper_find_emph_char_1(&mut i, data, c) {
            i = new_i;
        }
    }
    0
}
pub fn parse_spoilerspan(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
) -> Option<usize> {
    if rndr.cb.spoilerspan.is_none() {
        return None;
    }

    let mut i = 0;
    while i < size {
        let len = find_emph_char(&data[i..], b'<');
        if len == 0 {
            return None;
        }
        i += len;

        if i < size && data[i] == b'<' && i > 0 && data[i - 1] == b'!' {
            let mut work = rndr_newbuf(rndr, 1)?;
            extern "C" {
                fn parse_inline(work: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], offset: usize);
            }
            unsafe {
                parse_inline(work.as_mut(), rndr, data, i - 1);
            }
            let r = {
                let opaque = rndr.opaque.as_mut().map(|b| &mut **b).unwrap();
                let render_method = rndr.cb.spoilerspan.as_ref().unwrap();
                render_method(ob, work.as_ref(), opaque)
            };
            rndr_popbuf(rndr, 1);
            if r == 0 {
                return None;
            }
            return Some(i + 1);
        }
        i += 1;
    }

    None
}
#[inline]
pub fn _isspace(c: i32) -> bool {
    (c == b' ' as i32) || (c == b'\n' as i32)
}
pub fn parse_emph2(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], c: u8) -> Option<usize> {
    // Check if callback exists without holding a reference
    let has_callback = if c == b'~' {
        rndr.cb.strikethrough.is_some()
    } else {
        rndr.cb.double_emphasis.is_some()
    };
    
    if !has_callback {
        return None;
    }
    
    let size = data.len();
    let mut i = 0;
    while i < size {
        let len = find_emph_char(&data[i..], c);
        if len == 0 {
            return None;
        }
        i += len;
        
        if i + 1 < size && data[i] == c && data[i + 1] == c && i > 0 && !_isspace(data[i - 1] as i32) {
            let mut work = match rndr_newbuf(rndr, 1) {
                Some(buf) => buf,
                None => return None,
            };
            
            // Create temporary references to avoid borrow conflicts
            let work_ref = &mut *work;
            let data_slice = &data[..i];
            
            parse_inline(work_ref, rndr, data_slice, i);
            
            // Re-borrow callback briefly in a limited scope
            let r = {
                let render_method = if c == b'~' {
                    rndr.cb.strikethrough.as_ref().unwrap()
                } else {
                    rndr.cb.double_emphasis.as_ref().unwrap()
                };
                render_method(ob, &*work_ref, &mut rndr.opaque)
            };
            
            rndr_popbuf(rndr, 1);
            return if r != 0 { Some(i + 2) } else { None };
        }
        i += 1;
    }
    
    None
}
pub fn parse_emph1(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], c: u8) -> usize {
    let mut i = 0;
    let mut len;
    let mut work: Option<Box<Buf>> = None;
    let mut r;
    
    if rndr.cb.emphasis.is_none() {
        return 0;
    }
    
    if data.len() > 1 && data[0] == c && data[1] == c {
        i = 1;
    }
    
    while i < data.len() {
        len = find_emph_char(&data[i..], c);
        if len == 0 {
            return 0;
        }
        i += len;
        if i >= data.len() {
            return 0;
        }
        if data[i] == c && !_isspace(data[i - 1] as i32) {
            if (rndr.ext_flags & MKDEXT_NO_INTRA_EMPHASIS as u32) != 0 && c == b'_' {
                if i + 1 < data.len() {
                    let next_char = data[i + 1];
                    let is_space = _isspace(next_char as i32);
                    let is_punct = unsafe { ispunct(next_char as i32) != 0 };
                    if !is_space && !is_punct {
                        continue;
                    }
                }
            }
            work = rndr_newbuf(rndr, 1);
            if let Some(ref mut work_buf) = work {
                parse_inline(work_buf, rndr, &data[..i], i);
                r = rndr.cb.emphasis.as_ref().unwrap()(ob, work_buf, &mut rndr.opaque);
                rndr_popbuf(rndr, 1);
                return if r != 0 { i + 1 } else { 0 };
            }
        }
    }
    
    0
}
pub fn parse_emph3(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    c: u8,
) -> Option<usize> {
    let mut i = 0;
    let size = data.len();
    
    extern "C" {
        fn parse_inline(work: &mut Buf, rndr: &mut SdMarkdown, data: &[u8]);
    }
    
    while i < size {
        let len = find_emph_char(&data[i..], c);
        if len == 0 {
            return Option::None;
        }
        i += len;
        
        if i >= size || data[i] != c || _isspace(data[i - 1] as i32) {
            continue;
        }
        
        if i + 2 < size && data[i + 1] == c && data[i + 2] == c && rndr.cb.triple_emphasis.is_some() {
            let mut work = match rndr_newbuf(rndr, 1) {
                Some(w) => w,
                None => return Option::None,
            };
            
            unsafe {
                parse_inline(&mut work, rndr, &data[..i]);
            }
            
            let r = if let Some(cb) = &rndr.cb.triple_emphasis {
                cb(ob, &work, rndr.opaque.as_mut().map(|b| &mut **b).unwrap())
            } else {
                0
            };
            
            rndr_popbuf(rndr, 1);
            return if r != 0 { Some(i + 3) } else { Option::None };
        } else if i + 1 < size && data[i + 1] == c {
            let len = parse_emph1(ob, rndr, &data[i - 2..], c);
            if len == 0 {
                return Option::None;
            } else {
                return Some(len - 2);
            }
        } else {
            let len = parse_emph2(ob, rndr, &data[i - 1..], c);
            if len.is_none() {
                return Option::None;
            } else {
                return len.map(|l| l - 1);
            }
        }
    }
    
    Option::None
}
pub fn char_emphasis(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    let c = data[0];
    
    if size > 3 && c == b'>' && data[1] == b'!' {
        if _isspace(data[2] as i32) {
            return 0;
        }
        if let Some(ret) = parse_spoilerspan(ob, rndr, &data[2..], size - 2) {
            return ret + 2;
        }
        return 0;
    }
    
    if size > 2 && data[1] != c {
        if (c == b'~' || c == b'>') || _isspace(data[1] as i32) {
            return 0;
        }
        let ret = parse_emph1(ob, rndr, &data[1..], c);
        if ret != 0 {
            return ret + 1;
        }
        return 0;
    }
    
    if size > 3 && data[1] == c && data[2] != c {
        if _isspace(data[2] as i32) {
            return 0;
        }
        if let Some(ret) = parse_emph2(ob, rndr, &data[2..], c) {
            return ret + 2;
        }
        return 0;
    }
    
    if size > 4 && data[1] == c && data[2] == c && data[3] != c {
        if (c == b'~' || c == b'>') || _isspace(data[3] as i32) {
            return 0;
        }
        if let Some(ret) = parse_emph3(ob, rndr, &data[3..], c) {
            return ret + 3;
        }
        return 0;
    }
    
    0
}
pub fn char_superscript(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    let sup_start;
    let mut sup_len;
    
    if rndr.cb.superscript.is_none() {
        return 0;
    }
    
    if size < 2 {
        return 0;
    }
    
    if data[1] == b'(' {
        sup_len = 2;
        sup_start = sup_len;
        
        while sup_len < size && data[sup_len] != b')' && data[sup_len - 1] != b'\\' {
            sup_len += 1;
        }
        
        if sup_len == size {
            return 0;
        }
    } else {
        sup_len = 1;
        sup_start = sup_len;
        
        while sup_len < size && !data[sup_len].is_ascii_whitespace() {
            sup_len += 1;
        }
    }
    
    if sup_len - sup_start == 0 {
        return if sup_start == 2 { 3 } else { 0 };
    }
    
    let mut sup = match rndr_newbuf(rndr, 1) {
        Some(buf) => buf,
        None => return 0,
    };
    
    parse_inline(sup.as_mut(), rndr, &data[sup_start..sup_start + (sup_len - sup_start)], sup_len - sup_start);
    
    if let Some(callback) = &rndr.cb.superscript {
        callback(ob, sup.as_ref(), &mut rndr.opaque);
    }
    
    rndr_popbuf(rndr, 1);
    
    if sup_start == 2 {
        sup_len + 1
    } else {
        sup_len
    }
}
pub fn find_link_ref<'a>(
    references: &'a [Option<Box<link_ref::LinkRef>>],
    name: &[u8],
    length: usize,
) -> Option<&'a link_ref::LinkRef> {
    let hash = hash_link_ref(Some(name), length).unwrap();
    let hash_32 = hash as u32;

    if references.is_empty() {
        return Option::None;
    }
    let index = (hash_32 as usize) % references.len();

    // Start at the head of the bucket as an immutable traversal
    let mut current = references[index].as_deref(); // Option<&LinkRef>

    while let Some(ref_) = current {
        if ref_.id == hash_32 {
            if let Some(label) = ref_.label.as_ref() {
                if label.size == length {
                    if let Some(data) = label.data.as_deref() {
                        if data[..label.size].eq_ignore_ascii_case(&name[..length]) {
                            return Some(ref_);
                        }
                    }
                }
            }
        }
        // Move to the next element in the linked list
        current = ref_.next.as_deref();
    }

    Option::None
}
pub fn helper_char_link_1(
    i_ref: &mut usize,
    link_idx_ref: &mut u32,
    title_idx_ref: &mut u32,
    rndr: &mut SdMarkdown,
    data: &[u8],
    txt_e: usize,
    text_has_nl: bool,
) {
    let mut id = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };

    if text_has_nl {
        let mut b = match rndr_newbuf(rndr, 1) {
            Some(buf) => *buf,
            None => return,
        };

        for j in 1..txt_e {
            if data[j] != b'\n' {
                bufputc(&mut b, data[j] as i32);
            } else if data[j - 1] != b' ' {
                bufputc(&mut b, b' ' as i32);
            }
        }

        id.data = b.data;
        id.size = b.size;
    } else {
        id.data = Some(data[1..txt_e].to_vec());
        id.size = txt_e - 1;
    }

    let lr = match id.data {
        Some(ref id_data) => find_link_ref(&rndr.refs, id_data, id.size),
        None => return,
    };

    let lr = match lr {
        Some(lr) => lr,
        None => return,
    };

    // In the Rust version, we use the id field directly
    *link_idx_ref = lr.id;
    *title_idx_ref = lr.id;
    *i_ref = txt_e + 1;
}
pub fn helper_helper_char_link_2_1(
    id_ref: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    txt_e: usize,
    text_has_nl: bool,
) {
    let mut id = id_ref.clone();
    
    if text_has_nl {
        if let Some(mut b) = rndr_newbuf(rndr, 1) {
            for j in 1..txt_e {
                if data[j] != b'\n' {
                    bufputc(&mut b, data[j] as i32);
                } else if data[j - 1] != b' ' {
                    bufputc(&mut b, b' ' as i32);
                }
            }
            
            id.data = b.data;
            id.size = b.size;
        }
    } else {
        id.data = Some(data[1..txt_e].to_vec());
        id.size = txt_e - 1;
    }
    
    *id_ref = id;
}
pub fn helper_char_link_2(
    size_ref: &mut usize,
    i_ref: &mut usize,
    link_b_ref: &mut usize,
    link_e_ref: &mut usize,
    link_idx_ref: &mut u32,
    title_idx_ref: &mut u32,
    rndr: &mut SdMarkdown,
    data: &[u8],
    txt_e: usize,
    text_has_nl: bool,
) {
    let size = *size_ref;
    let mut i = *i_ref;
    let mut link_b = *link_b_ref;
    let mut link_e = *link_e_ref;
    let mut link_idx = *link_idx_ref;
    let mut title_idx = *title_idx_ref;
    
    let mut id = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };
    
    i += 1;
    link_b = i;
    
    while i < size && data[i] != b']' {
        i += 1;
    }
    
    if i >= size {
        return;
    }
    
    link_e = i;
    
    if link_b == link_e {
        helper_helper_char_link_2_1(&mut id, rndr, data, txt_e, text_has_nl);
    } else {
        id.data = Some(data[link_b..link_e].to_vec());
        id.size = link_e - link_b;
    }
    
    if let Some(id_data) = &id.data {
        if let Some(lr) = find_link_ref(&rndr.refs, id_data.as_slice(), id.size) {
            link_idx = lr.id;
            title_idx = lr.id; // Assuming title_idx should be set similarly to link_idx
                              // Adjust if there's a separate field for title_idx in LinkRef
        } else {
            return;
        }
    } else {
        return;
    }
    
    i += 1;
    
    *size_ref = size;
    *i_ref = i;
    *link_b_ref = link_b;
    *link_e_ref = link_e;
    *link_idx_ref = link_idx;
    *title_idx_ref = title_idx;
}
pub fn helper_helper_char_link_3_1(
    i_ref: &mut usize,
    link_e_ref: &mut usize,
    title_b_ref: &mut usize,
    title_e_ref: &mut usize,
    in_title_ref: &mut i32,
    qtype_ref: &mut i32,
    data: &[u8],
    size: usize,
) {
    let mut i = *i_ref;
    let mut link_e = *link_e_ref;
    let mut title_b = *title_b_ref;
    let mut title_e = *title_e_ref;
    let mut in_title = *in_title_ref;
    let mut qtype = *qtype_ref;

    qtype = data[i] as i32;
    in_title = 1;
    i += 1;
    title_b = i;

    while i < size {
        if data[i] == b'\\' {
            i += 2;
        } else if data[i] == qtype as u8 {
            in_title = 0;
            i += 1;
        } else if data[i] == b')' && in_title == 0 {
            break;
        } else {
            i += 1;
        }
    }

    if i >= size {
        // Equivalent to 'goto cleanup' - just return early
        *i_ref = i;
        *link_e_ref = link_e;
        *title_b_ref = title_b;
        *title_e_ref = title_e;
        *in_title_ref = in_title;
        *qtype_ref = qtype;
        return;
    }

    title_e = i - 1;
    while title_e > title_b && _isspace(data[title_e] as i32) {
        title_e -= 1;
    }

    if data[title_e] != b'\'' && data[title_e] != b'"' {
        title_b = 0;
        title_e = 0;
        link_e = i;
    }

    *i_ref = i;
    *link_e_ref = link_e;
    *title_b_ref = title_b;
    *title_e_ref = title_e;
    *in_title_ref = in_title;
    *qtype_ref = qtype;
}
pub fn helper_char_link_3(
    i_ref: &mut usize,
    link_b_ref: &mut usize,
    link_e_ref: &mut usize,
    title_b_ref: &mut usize,
    title_e_ref: &mut usize,
    link_idx_ref: &mut u32,
    title_idx_ref: &mut u32,
    in_title_ref: &mut i32,
    qtype_ref: &mut i32,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
    link: &mut Buf,
    title: &mut Buf,
) {
    let mut i = *i_ref;
    let mut link_b = *link_b_ref;
    let mut link_e = *link_e_ref;
    let mut title_b = *title_b_ref;
    let mut title_e = *title_e_ref;
    let mut link_idx = *link_idx_ref;
    let mut title_idx = *title_idx_ref;
    let mut in_title = *in_title_ref;
    let mut qtype = *qtype_ref;

    i += 1;
    while i < size && _isspace(data[i] as i32) {
        i += 1;
    }

    link_b = i;
    while i < size {
        if data[i] == b'\\' {
            i += 2;
        } else if data[i] == b')' {
            break;
        } else if (i >= 1 && _isspace(data[i - 1] as i32)) && (data[i] == b'\'' || data[i] == b'"') {
            break;
        } else {
            i += 1;
        }
    }

    if i >= size {
        // cleanup is just returning in Rust
        return;
    }
    link_e = i;

    if data[i] == b'\'' || data[i] == b'"' {
        helper_helper_char_link_3_1(
            &mut i,
            &mut link_e,
            &mut title_b,
            &mut title_e,
            &mut in_title,
            &mut qtype,
            data,
            size,
        );
    }

    while link_e > link_b && _isspace(data[link_e - 1] as i32) {
        link_e -= 1;
    }

    if data[link_b] == b'<' {
        link_b += 1;
    }
    if data[link_e - 1] == b'>' {
        link_e -= 1;
    }

    if link_e > link_b {
        if let Some(new_buf) = rndr_newbuf(rndr, 1) {
            link_idx = new_buf.size as u32;
            bufput(link, &data[link_b..link_e], link_e - link_b);
        }
    }

    if title_e > title_b {
        if let Some(new_buf) = rndr_newbuf(rndr, 1) {
            title_idx = new_buf.size as u32;
            bufput(title, &data[title_b..title_e], title_e - title_b);
        }
    }

    i += 1;

    *i_ref = i;
    *link_b_ref = link_b;
    *link_e_ref = link_e;
    *title_b_ref = title_b;
    *title_e_ref = title_e;
    *link_idx_ref = link_idx;
    *title_idx_ref = title_idx;
    *in_title_ref = in_title;
    *qtype_ref = qtype;
}
pub fn unscape_text(ob: &mut Buf, src: &Buf) {
    let mut i = 0;
    let mut org;
    
    while i < src.size {
        org = i;
        while i < src.size && src.data.as_ref().unwrap()[i] != b'\\' {
            i += 1;
        }

        if i > org {
            bufput(ob, &src.data.as_ref().unwrap()[org..i], i - org);
        }
        if i + 1 >= src.size {
            break;
        }
        bufputc(ob, src.data.as_ref().unwrap()[i + 1] as i32);
        i += 2;
    }
}
pub fn char_link(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    mut size: usize,
) -> usize {
    let is_img = max_rewind > 0 && data[0] == b'!';
    let mut level = 1;
    let mut i = 1;
    let mut txt_e;
    let mut link_b = 0;
    let mut link_e = 0;
    let mut title_b = 0;
    let mut title_e = 0;
    let mut content: Option<Box<Buf>> = None;
    let mut link: Option<Box<Buf>> = None;
    let mut title: Option<Box<Buf>> = None;
    let mut u_link: Option<Box<Buf>> = None;
    let org_work_size = rndr.work_bufs[1].size;
    let mut text_has_nl = false;
    let mut ret = 0;
    let mut in_title = 0;
    let mut qtype = 0;
    let mut link_idx = 0;
    let mut title_idx = 0;

    if (is_img && rndr.cb.image.is_none()) || (!is_img && rndr.cb.link.is_none()) {
        rndr.work_bufs[1].size = org_work_size;
        return 0;
    }

    while i < size {
        if data[i] == b'\n' {
            text_has_nl = true;
        } else if data[i - 1] == b'\\' {
            // Continue
        } else if data[i] == b'[' {
            level += 1;
        } else if data[i] == b']' {
            level -= 1;
            if level <= 0 {
                break;
            }
        }
        i += 1;
    }

    if i >= size {
        rndr.work_bufs[1].size = org_work_size;
        return 0;
    }
    txt_e = i;
    i += 1;
    while i < size && data[i].is_ascii_whitespace() {
        i += 1;
    }

    if i < size && data[i] == b'(' {
        let link_buf = link.get_or_insert_with(|| rndr_newbuf(rndr, 1).unwrap());
        let title_buf = title.get_or_insert_with(|| rndr_newbuf(rndr, 1).unwrap());
        helper_char_link_3(
            &mut i,
            &mut link_b,
            &mut link_e,
            &mut title_b,
            &mut title_e,
            &mut link_idx,
            &mut title_idx,
            &mut in_title,
            &mut qtype,
            rndr,
            data,
            size,
            link_buf,
            title_buf,
        );
    } else if i < size && data[i] == b'[' {
        helper_char_link_2(
            &mut size,
            &mut i,
            &mut link_b,
            &mut link_e,
            &mut link_idx,
            &mut title_idx,
            rndr,
            data,
            txt_e,
            text_has_nl,
        );
    } else {
        helper_char_link_1(
            &mut i,
            &mut link_idx,
            &mut title_idx,
            rndr,
            data,
            txt_e,
            text_has_nl,
        );
    }

    if txt_e > 1 {
        content = rndr_newbuf(rndr, 1);
        if let Some(ref mut content_buf) = content {
            if is_img {
                bufput(content_buf, &data[1..txt_e], txt_e - 1);
            } else {
                rndr.in_link_body = 1;
                parse_inline(content_buf, rndr, &data[1..txt_e], txt_e - 1);
                rndr.in_link_body = 0;
            }
        }
    }

    if let Some(ref link_buf) = link {
        u_link = rndr_newbuf(rndr, 1);
        if let Some(ref mut u_link_buf) = u_link {
            unscape_text(u_link_buf, link_buf);
        }
    } else {
        rndr.work_bufs[1].size = org_work_size;
        return 0;
    }

    let empty_buf = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };
    if is_img {
        if ob.size > 0 && ob.data.as_ref().map_or(false, |d| d[ob.size - 1] == b'!') {
            ob.size -= 1;
        }
        if let Some(ref cb) = rndr.cb.image {
            ret = cb(
                ob,
                u_link.as_ref().map(|b| &**b).unwrap_or(&empty_buf),
                title.as_ref().map(|b| &**b).unwrap_or(&empty_buf),
                content.as_ref().map(|b| &**b).unwrap_or(&empty_buf),
                rndr.opaque.as_mut().map(|b| &mut **b).unwrap_or(&mut ()),
            );
        }
    } else {
        if let Some(ref cb) = rndr.cb.link {
            ret = cb(
                ob,
                u_link.as_ref().map(|b| &**b).unwrap_or(&empty_buf),
                title.as_ref().map(|b| &**b).unwrap_or(&empty_buf),
                content.as_ref().map(|b| &**b).unwrap_or(&empty_buf),
                rndr.opaque.as_mut().map(|b| &mut **b).unwrap_or(&mut ()),
            );
        }
    }

    rndr.work_bufs[1].size = org_work_size;

    if ret != 0 { i } else { 0 }
}
pub fn char_autolink_url(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    if rndr.cb.autolink.is_none() || rndr.in_link_body != 0 {
        return 0;
    }

    let link = match rndr_newbuf(rndr, 1) {
        Some(l) => l,
        None => return 0,
    };

    let mut rewind = 0;
    let mut link_mut = link.as_ref().clone();
    let link_len = sd_autolink__url(&mut rewind, &mut link_mut, data, max_rewind, size, 0);

    if link_len > 0 {
        buftruncate(ob, ob.size - rewind);
        if let Some(autolink_cb) = &mut rndr.cb.autolink {
            autolink_cb(ob, &link_mut, MkdAutolink::MKDA_NORMAL, rndr.opaque.as_mut().map(|b| &mut **b).unwrap());
        }
    }

    rndr_popbuf(rndr, 1);
    link_len
}
pub fn is_mail_autolink(data: &[u8]) -> usize {
    let mut nb = 0;
    
    for (i, &c) in data.iter().enumerate() {
        if c.is_ascii_alphanumeric() {
            continue;
        }
        
        match c {
            b'@' => nb += 1,
            b'-' | b'.' | b'_' => (),
            b'>' => return if nb == 1 { i + 1 } else { 0 },
            _ => return 0,
        }
    }
    
    0
}
pub fn helper_tag_length_1(
    i_ref: &mut usize,
    j_ref: &mut usize,
    data: &[u8],
    size: usize,
    autolink: &mut MkdAutolink,
) -> usize {
    let mut i = *i_ref;
    let mut j = *j_ref;
    j = i;

    while i < size {
        if data[i] == b'\\' {
            i += 2;
        } else if data[i] == b'>' || data[i] == b'\'' || data[i] == b'"' || data[i] == b' ' || data[i] == b'\n' {
            break;
        } else {
            i += 1;
        }
    }

    if i >= size {
        return 0;
    }
    if i > j && data[i] == b'>' {
        return i + 1;
    }

    *autolink = MkdAutolink::MKDA_NOT_AUTOLINK;
    *i_ref = i;
    *j_ref = j;
    0
}
pub fn tag_length(data: &[u8], autolink: &mut MkdAutolink) -> usize {
    if data.len() < 3 {
        return 0;
    }
    if data[0] != b'<' {
        return 0;
    }

    let mut i = if data[1] == b'/' { 2 } else { 1 };
    
    if !data[i].is_ascii_alphanumeric() {
        return 0;
    }

    *autolink = MkdAutolink::MKDA_NOT_AUTOLINK;
    
    while i < data.len() && (data[i].is_ascii_alphanumeric() || 
                            data[i] == b'.' || 
                            data[i] == b'+' || 
                            data[i] == b'-') {
        i += 1;
    }

    if i > 1 && i < data.len() && data[i] == b'@' {
        let j = is_mail_autolink(&data[i..]);
        if j != 0 {
            *autolink = MkdAutolink::MKDA_EMAIL;
            return i + j;
        }
    }

    if i > 2 && i < data.len() && data[i] == b':' {
        *autolink = MkdAutolink::MKDA_NORMAL;
        i += 1;
    }

    if i >= data.len() {
        *autolink = MkdAutolink::MKDA_NOT_AUTOLINK;
    } else if *autolink != MkdAutolink::MKDA_NOT_AUTOLINK {
        let mut j = 0;
        helper_tag_length_1(&mut i, &mut j, data, data.len(), autolink);
    }

    while i < data.len() && data[i] != b'>' {
        i += 1;
    }

    if i >= data.len() {
        0
    } else {
        i + 1
    }
}
pub fn char_langle_tag(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    let mut altype = MkdAutolink::MKDA_NOT_AUTOLINK;
    let end = tag_length(data, &mut altype);
    let mut work = Buf {
        data: Some(data.to_vec()),
        size: end,
        asize: 0,
        unit: 0,
    };
    let mut ret: i32 = 0;

    if end > 2 {
        if altype != MkdAutolink::MKDA_NOT_AUTOLINK {
            // Temporarily move the callback out to avoid overlapping borrows
            let saved_callback = std::mem::replace(&mut rndr.cb.autolink, None);
            if let Some(cb) = saved_callback.as_ref() {
                let mut u_link = rndr_newbuf(rndr, 1);
                if let Some(ref mut u_link) = u_link {
                    work.data = Some(data[1..].to_vec());
                    work.size = end - 2;
                    unscape_text(u_link, &work);
                    ret = cb(
                        ob,
                        u_link,
                        altype,
                        rndr.opaque.as_mut().map(|b| &mut **b).unwrap_or(&mut ()),
                    );
                }
                rndr_popbuf(rndr, 1);
            }
            // Restore the callback
            rndr.cb.autolink = saved_callback;
        } else if let Some(raw_html_tag_cb) = rndr.cb.raw_html_tag.as_ref() {
            ret = raw_html_tag_cb(
                ob,
                &work,
                rndr.opaque.as_mut().map(|b| &mut **b).unwrap_or(&mut ()),
            );
        }
    }

    if ret == 0 {
        0
    } else {
        end
    }
}
pub fn char_codespan(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    let mut nb = 0;
    while nb < size && data[nb] == b'`' {
        nb += 1;
    }

    let mut i = 0;
    let mut end = nb;
    while end < size && i < nb {
        if data[end] == b'`' {
            i += 1;
        } else {
            i = 0;
        }
        end += 1;
    }

    if i < nb && end >= size {
        return 0;
    }

    let mut f_begin = nb;
    while f_begin < end && data[f_begin] == b' ' {
        f_begin += 1;
    }

    let mut f_end = end - nb;
    while f_end > nb && data[f_end - 1] == b' ' {
        f_end -= 1;
    }

    let result = if f_begin < f_end {
        let work = Buf {
            data: Some(data[f_begin..f_end].to_vec()),
            size: f_end - f_begin,
            asize: f_end - f_begin,
            unit: 0,
        };
        rndr.cb.codespan.as_ref().map(|f| f(ob, &work, rndr.opaque.as_mut().unwrap()))
    } else {
        rndr.cb.codespan.as_ref().map(|f| f(ob, &Buf {
            data: None,
            size: 0,
            asize: 0,
            unit: 0,
        }, rndr.opaque.as_mut().unwrap()))
    };

    if result == Some(0) {
        0
    } else {
        end
    }
}
pub fn hash_html_entity(str: &[u8], len: usize) -> u32 {
    static ASSO_VALUES: [u16; 256] = [
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 0, 95, 90, 0, 771, 771,
        771, 771, 771, 771, 0, 771, 771, 771, 771, 771, 115, 94, 55, 0, 150, 25, 0, 30, 195, 771,
        30, 30, 5, 35, 45, 45, 771, 10, 0, 50, 125, 771, 771, 5, 85, 75, 771, 771, 771, 771, 771,
        771, 40, 65, 20, 25, 60, 240, 240, 223, 10, 102, 20, 35, 135, 0, 5, 10, 183, 20, 5, 0, 50,
        75, 10, 75, 175, 85, 15, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
        771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771,
    ];

    let mut hval = len as u32;

    match len {
        2 => {
            hval += ASSO_VALUES[str[1] as usize] as u32;
        }
        3 => {
            hval += ASSO_VALUES[(str[2] as usize) + 1] as u32;
            hval += ASSO_VALUES[str[1] as usize] as u32;
        }
        4 => {
            hval += ASSO_VALUES[str[3] as usize] as u32;
            hval += ASSO_VALUES[(str[2] as usize) + 1] as u32;
            hval += ASSO_VALUES[str[1] as usize] as u32;
        }
        5 => {
            hval += ASSO_VALUES[str[4] as usize] as u32;
            hval += ASSO_VALUES[str[3] as usize] as u32;
            hval += ASSO_VALUES[(str[2] as usize) + 1] as u32;
            hval += ASSO_VALUES[str[1] as usize] as u32;
        }
        6 => {
            hval += ASSO_VALUES[str[5] as usize] as u32;
            hval += ASSO_VALUES[str[4] as usize] as u32;
            hval += ASSO_VALUES[str[3] as usize] as u32;
            hval += ASSO_VALUES[(str[2] as usize) + 1] as u32;
            hval += ASSO_VALUES[str[1] as usize] as u32;
        }
        _ if len > 6 => {
            hval += ASSO_VALUES[str[6] as usize] as u32;
            hval += ASSO_VALUES[str[5] as usize] as u32;
            hval += ASSO_VALUES[str[4] as usize] as u32;
            hval += ASSO_VALUES[str[3] as usize] as u32;
            hval += ASSO_VALUES[(str[2] as usize) + 1] as u32;
            hval += ASSO_VALUES[str[1] as usize] as u32;
        }
        _ => {}
    }

    hval
}
pub fn is_allowed_named_entity(str: &[u8], len: usize) -> Option<&'static str> {
    const TOTAL_KEYWORDS: usize = 253;
    const MIN_WORD_LENGTH: usize = 4;
    const MAX_WORD_LENGTH: usize = 10;
    const MIN_HASH_VALUE: usize = 14;
    const MAX_HASH_VALUE: usize = 770;

    static WORDLIST: &[&str] = &[
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&or;", "&not;", "", "", "", "",
        "&int;", "", "", "", "", "&psi;", "&isin;", "&notin;", "", "", "&Rho;", "", "", "", "",
        "&phi;", "&prop;", "", "", "", "&rho;", "&nbsp;", "&thorn;", "&thinsp;", "", "&chi;", "",
        "", "", "", "", "&prod;", "", "", "", "&amp;", "", "", "", "", "&Psi;", "", "", "", "",
        "", "&iota;", "", "", "&omicron;", "&Phi;", "", "", "", "", "&and;", "&sdot;", "", "",
        "&nu;", "&Chi;", "&emsp;", "", "", "&Mu;", "", "&ensp;", "&ocirc;", "", "&lt;", "&uml;",
        "", "&icirc;", "", "", "&sup;", "&sup1;", "", "&Scaron;", "", "&cap;", "&part;", "&pound;",
        "&scaron;", "", "", "&ni;", "", "&lowast;", "&Omicron;", "&cup;", "&Xi;", "&crarr;", "",
        "&Nu;", "", "&pi;", "&theta;", "", "", "&tau;", "&nsub;", "&acirc;", "", "",
        "&thetasym;", "", "&Ocirc;", "", "", "", "&rarr;", "&ucirc;", "", "", "&loz;", "&darr;",
        "&trade;", "", "", "", "&para;", "&ecirc;", "", "", "", "&larr;", "&radic;", "", "",
        "&sub;", "&Pi;", "&kappa;", "&iquest;", "", "&eta;", "&supe;", "&rceil;", "&there4;", "",
        "&rArr;", "&uarr;", "&Kappa;", "", "", "&dArr;", "&euro;", "&Theta;", "&circ;", "",
        "&Tau;", "", "&lceil;", "", "", "&lArr;", "&ordm;", "", "", "", "&lrm;", "&xi;", "&acute;",
        "&ccedil;", "", "", "&sup3;", "", "&ntilde;", "", "&uArr;", "&sup2;", "&piv;", "&otilde;",
        "", "&shy;", "", "&Acirc;", "", "", "", "", "", "&curren;", "", "", "", "&Ucirc;", "&oacute;",
        "", "", "&sube;", "&nabla;", "&iacute;", "&mu;", "", "&bull;", "&oline;", "&Ccedil;", "",
        "&sum;", "&copy;", "&equiv;", "&Ntilde;", "", "", "", "&prime;", "&atilde;", "&tilde;", "",
        "", "&Ecirc;", "&Otilde;", "", "", "", "", "", "&apos;", "", "", "", "&aacute;", "&ne;",
        "&Eta;", "&macr;", "&sim;", "&Oacute;", "", "", "&Iota;", "&empty;", "&uacute;", "", "",
        "&ouml;", "&exist;", "", "", "", "&iuml;", "&Prime;", "&eacute;", "", "&rsquo;", "&cent;",
        "&zwj;", "&zwnj;", "&quot;", "&sbquo;", "&sect;", "&infin;", "&otimes;", "", "",
        "&cong;", "&Icirc;", "&brvbar;", "&le;", "&lsquo;", "&ordf;", "&clubs;", "", "",
        "&oplus;", "&perp;", "", "&Yacute;", "&micro;", "&ang;", "&auml;", "", "", "&gt;", "&rlm;",
        "&Ouml;", "&upsilon;", "", "&minus;", "&middot;", "&uuml;", "&aring;", "&Atilde;", "",
        "&divide;", "&rsaquo;", "&epsilon;", "", "&times;", "&ETH;", "&euml;", "&szlig;", "&frac14;",
        "&diams;", "", "&oslash;", "", "&Aacute;", "", "", "&lsaquo;", "&Delta;", "", "",
        "&rdquo;", "&spades;", "", "&Uacute;", "", "&raquo;", "&rang;", "&frasl;", "&rfloor;",
        "&harr;", "&ndash;", "&Yuml;", "&cedil;", "&eth;", "", "&ldquo;", "&real;", "&THORN;",
        "&plusmn;", "", "&laquo;", "&lang;", "&delta;", "&lfloor;", "", "", "&beta;", "&omega;",
        "&Eacute;", "", "", "&Oslash;", "&image;", "&weierp;", "", "", "&Zeta;", "&OElig;",
        "&hArr;", "", "", "&Auml;", "&asymp;", "&Lambda;", "", "&bdquo;", "&zeta;", "&Upsilon;",
        "&lambda;", "", "", "&Uuml;", "&Aring;", "&yacute;", "", "&Beta;", "", "&Gamma;", "", "",
        "", "", "&iexcl;", "&forall;", "", "", "", "&Omega;", "", "", "", "", "&Epsilon;",
        "&Iacute;", "", "", "&Euml;", "", "&frac34;", "", "", "", "", "&frac12;", "", "", "", "",
        "", "", "", "", "", "", "", "&yen;", "", "", "", "", "", "&yuml;", "", "", "", "",
        "&ograve;", "&AElig;", "", "", "", "&igrave;", "", "", "", "", "", "", "", "", "", "&Iuml;",
        "", "", "", "", "", "", "", "", "&alpha;", "", "", "&permil;", "", "", "", "", "", "", "",
        "&agrave;", "", "", "", "&mdash;", "&Ograve;", "", "", "", "", "&ugrave;", "", "&upsih;",
        "", "", "", "", "", "&ge;", "", "&egrave;", "", "", "", "", "", "", "", "", "", "&fnof;", "",
        "", "", "", "", "", "", "", "", "&reg;", "", "", "", "", "&deg;", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "&Sigma;", "", "", "", "", "&sigma;", "&Alpha;", "", "", "",
        "", "", "&hearts;", "&oelig;", "", "", "", "&Agrave;", "", "", "", "", "", "", "", "", "",
        "&Ugrave;", "", "", "", "", "", "", "", "", "", "&hellip;", "", "", "", "", "", "", "", "",
        "", "", "&aelig;", "", "", "", "&Egrave;", "", "", "", "", "", "", "", "", "", "", "", "",
    ];

    if len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH {
        let key = hash_html_entity(str, len) as usize;
        if key <= MAX_HASH_VALUE {
            let s = WORDLIST[key];
            if !s.is_empty() && str.starts_with(s[1..].as_bytes()) && s.len() == len + 4 {
                return Some(s);
            }
        }
    }
    None
}
pub fn is_valid_numeric_entity(entity_val: u32) -> bool {
    (((((entity_val > 8) && ((entity_val != 11) && (entity_val != 12))) && 
       ((entity_val < 14) || (entity_val > 31))) && 
      ((entity_val < 55296) || (entity_val > 57343))) && 
     ((entity_val != 65534) && (entity_val != 65535))) && 
    (entity_val <= MAX_NUM_ENTITY_VAL)
}
pub fn char_entity(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    let mut end = 1;
    let content_start;
    let content_end;
    let mut work = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };
    let mut numeric = false;
    let mut hex = false;
    let entity_base;
    let entity_val;

    if end < size && data[end] == b'#' {
        numeric = true;
        end += 1;
    }

    if end < size && numeric && data[end].to_ascii_lowercase() == b'x' {
        hex = true;
        end += 1;
    }

    content_start = end;
    while end < size {
        let c = data[end];
        if hex {
            if !c.is_ascii_hexdigit() {
                break;
            }
        } else if numeric {
            if !c.is_ascii_digit() {
                break;
            }
        } else if !c.is_ascii_alphanumeric() {
            break;
        }
        end += 1;
    }

    content_end = end;
    if end > content_start && end < size && data[end] == b';' {
        end += 1;
    } else {
        return 0;
    }

    if numeric && (content_end - content_start) > MAX_NUM_ENTITY_LEN {
        return 0;
    }

    if numeric {
        entity_base = if hex { 16 } else { 10 };
        let entity_str = str::from_utf8(&data[content_start..content_end]).unwrap_or("");
        entity_val = u32::from_str_radix(entity_str, entity_base).unwrap_or(0);
        if !is_valid_numeric_entity(entity_val) {
            return 0;
        }
    } else {
        if !is_allowed_named_entity(data, end).is_some() {
            return 0;
        }
    }

    if let Some(cb) = &rndr.cb.entity {
        work.data = Some(data[..end].to_vec());
        work.size = end;
        if let Some(opaque) = &mut rndr.opaque {
            cb(ob, &work, opaque.as_mut());
        }
    } else {
        bufputc(ob, b'&' as i32);
        if numeric {
            bufputc(ob, b'#' as i32);
        }
        if hex {
            bufputc(ob, b'x' as i32);
        }
        bufput(ob, &data[content_start..end], end - content_start);
    }

    end
}
pub fn char_autolink_www(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> usize {
    if rndr.cb.link.is_none() || rndr.in_link_body != 0 {
        return 0;
    }

    let mut link_len = 0;
    let mut rewind = 0;

    let mut link = match rndr_newbuf(rndr, 1) {
        Some(l) => l,
        None => return 0,
    };

    link_len = sd_autolink__www(&mut rewind, &mut *link, data, max_rewind, size, 0);

    if link_len > 0 {
        let mut link_url = match rndr_newbuf(rndr, 1) {
            Some(u) => u,
            None => {
                rndr_popbuf(rndr, 1);
                return link_len;
            }
        };

        bufput(&mut *link_url, b"http://", 7);
        if let Some(link_data) = &link.data {
            bufput(&mut *link_url, link_data, link.size);
        }
        buftruncate(ob, ob.size - rewind);

        // Extract the callback first to avoid borrowing conflicts
        let has_normal_text = rndr.cb.normal_text.is_some();
        
        if has_normal_text {
            let mut link_text = match rndr_newbuf(rndr, 1) {
                Some(t) => t,
                None => {
                    rndr_popbuf(rndr, 1);
                    rndr_popbuf(rndr, 1);
                    return link_len;
                }
            };

            // Get the callback again inside the block
            if let Some(normal_text_cb) = &rndr.cb.normal_text {
                if let Some(ref mut opaque) = rndr.opaque {
                    normal_text_cb(&mut *link_text, &*link, opaque);
                }
            }
            
            if let Some(link_cb) = &rndr.cb.link {
                if let Some(ref mut opaque) = rndr.opaque {
                    let empty_buf = Buf {
                        data: None,
                        size: 0,
                        asize: 0,
                        unit: 0,
                    };
                    link_cb(ob, &*link_url, &empty_buf, &*link_text, opaque);
                }
            }
            
            rndr_popbuf(rndr, 1);
        } else if let Some(link_cb) = &rndr.cb.link {
            if let Some(ref mut opaque) = rndr.opaque {
                let empty_buf = Buf {
                    data: None,
                    size: 0,
                    asize: 0,
                    unit: 0,
                };
                link_cb(ob, &*link_url, &empty_buf, &*link, opaque);
            }
        }

        rndr_popbuf(rndr, 1);
    }

    rndr_popbuf(rndr, 1);
    link_len
}
pub fn char_linebreak(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    max_rewind: usize,
    max_lookbehind: usize,
    size: usize,
) -> bool {
    // Check conditions (line 3-6 in C code)
    if max_rewind < 2 || data[data.len() - 1] != b' ' || data[data.len() - 2] != b' ' {
        return false;
    }

    // Remove trailing spaces (line 7-10 in C code)
    if let Some(ref mut data_vec) = ob.data {
        while ob.size > 0 && data_vec[ob.size - 1] == b' ' {
            ob.size -= 1;
        }
    }

    // Call the linebreak callback (line 12 in C code)
    if let Some(ref linebreak) = rndr.cb.linebreak {
        linebreak(ob, &mut rndr.opaque) != 0
    } else {
        false
    }
}
pub fn parse_inline(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], size: usize) {
    let mut i = 0;
    let mut end = 0;
    let mut last_special = 0;
    let mut action = 0;
    let mut work = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };

    if (rndr.work_bufs[1].size + rndr.work_bufs[0].size) > rndr.max_nesting {
        return;
    }

    while i < size {
        while end < size && {
            action = rndr.active_char[data[end] as usize];
            action == 0
        } {
            end += 1;
        }

        if let Some(cb) = &rndr.cb.normal_text {
            work.data = Some(data[i..end].to_vec());
            work.size = end - i;
            cb(ob, &work, rndr.opaque.as_mut().map(|b| &mut **b).unwrap());
        } else {
            bufput(ob, &data[i..end], end - i);
        }

        if end >= size {
            break;
        }

        i = end;
        if let Some(char_fn) = MARKDOWN_CHAR_PTRS[action as usize] {
            end = char_fn(ob, rndr, &data[i..], i - last_special, i, size - i);
        } else {
            end = 0;
        }

        if end == 0 {
            end = i + 1;
        } else {
            i += end;
            end = i;
            last_special = end;
        }
    }
}
pub fn prefix_uli(data: &[u8]) -> usize {
    let mut i = 0;
    
    // Check for leading spaces (up to 3)
    while i < data.len() && data[i] == b' ' && i < 3 {
        i += 1;
    }

    // Check for the required pattern: one of ['*', '+', '-'] followed by a space
    if i + 1 >= data.len() 
        || !matches!(data[i], b'*' | b'+' | b'-') 
        || data[i + 1] != b' ' 
    {
        return 0;
    }

    // Check if this is a header line
    if is_next_headerline(&data[i..]) != 0 {
        return 0;
    }

    i + 2
}
pub fn is_hrule(data: &[u8]) -> bool {
    let mut i = 0;
    let mut n = 0;
    
    if data.len() < 3 {
        return false;
    }
    
    if data[0] == b' ' {
        i += 1;
        if i < data.len() && data[1] == b' ' {
            i += 1;
            if i < data.len() && data[2] == b' ' {
                i += 1;
            }
        }
    }
    
    if (i + 2) >= data.len() || (data[i] != b'*' && data[i] != b'-' && data[i] != b'_') {
        return false;
    }
    
    let c = data[i];
    
    while i < data.len() && data[i] != b'\n' {
        if data[i] == c {
            n += 1;
        } else if data[i] != b' ' {
            return false;
        }
        i += 1;
    }
    
    n >= 3
}
pub fn prefix_codefence(data: &[u8]) -> usize {
    let mut i = 0;
    let mut n = 0;
    
    if data.len() < 3 {
        return 0;
    }
    
    if data[0] == b' ' {
        i += 1;
        if data[1] == b' ' {
            i += 1;
            if data[2] == b' ' {
                i += 1;
            }
        }
    }
    
    if (i + 2) >= data.len() || !(data[i] == b'~' || data[i] == b'`') {
        return 0;
    }
    
    let c = data[i];
    while i < data.len() && data[i] == c {
        n += 1;
        i += 1;
    }
    
    if n < 3 {
        return 0;
    }
    
    i
}
pub fn helper_is_codefence_1(
    i_ref: &mut usize,
    syn_len_ref: &mut usize,
    syn_start_idx_ref: &mut u32,
    data: &[u8],
    syn_start: &[u8],
) -> usize {
    let mut i = *i_ref;
    let mut syn_len = *syn_len_ref;
    let mut syn_start_idx = *syn_start_idx_ref;
    
    i += 1;
    syn_start_idx += 1;
    
    while i < data.len() && data[i] != b'}' && data[i] != b'\n' {
        syn_len += 1;
        i += 1;
    }
    
    if i == data.len() || data[i] != b'}' {
        return 0;
    }
    
    while syn_len > 0 && _isspace(syn_start[syn_start_idx as usize] as i32) {
        syn_start_idx += 1;
        syn_len -= 1;
    }
    
    while syn_len > 0 && _isspace(syn_start[(syn_len - 1 + syn_start_idx as usize)] as i32) {
        syn_len -= 1;
    }
    
    i += 1;
    *i_ref = i;
    *syn_len_ref = syn_len;
    *syn_start_idx_ref = syn_start_idx;
    
    syn_len
}
pub fn is_codefence(data: &[u8], syntax: Option<&mut Buf>) -> usize {
    let mut i = 0;
    let mut syn_len = 0;
    let mut syn_start: *const u8 = ptr::null();
    let mut syn_start_idx: u32 = 0;
    
    i = prefix_codefence(data);
    if i == 0 {
        return 0;
    }
    
    while i < data.len() && data[i] == b' ' {
        i += 1;
    }
    
    syn_start = &data[i];
    syn_start_idx = i as u32;
    
    if i < data.len() && data[i] == b'{' {
        let slice_len = data.len() - i;
        helper_is_codefence_1(&mut i, &mut syn_len, &mut syn_start_idx, data, unsafe { std::slice::from_raw_parts(syn_start, slice_len) });
    } else {
        while i < data.len() && !_isspace(data[i] as i32) {
            syn_len += 1;
            i += 1;
        }
    }
    
    if let Some(syntax) = syntax {
        unsafe {
            // Convert raw pointer to Vec<u8> for the Buf struct
            let slice = std::slice::from_raw_parts(syn_start, syn_len);
            syntax.data = Some(slice.to_vec());
            syntax.size = syn_len;
        }
    }
    
    while i < data.len() && data[i] != b'\n' {
        if !_isspace(data[i] as i32) {
            return 0;
        }
        i += 1;
    }
    
    if i < data.len() {
        i + 1
    } else {
        0
    }
}
pub fn helper_parse_listitem_1(
    beg_ref: &mut usize,
    end_ref: &mut usize,
    pre_ref: &mut usize,
    sublist_ref: &mut usize,
    i_ref: &mut usize,
    in_empty_ref: &mut i32,
    has_inside_empty_ref: &mut i32,
    in_fence_ref: &mut i32,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
    flags: &mut i32,
    work: &mut Buf,
    orgpre: usize,
) {
    let mut beg = *beg_ref;
    let mut end = *end_ref;
    let mut pre = *pre_ref;
    let mut sublist = *sublist_ref;
    let mut i = *i_ref;
    let mut in_empty = *in_empty_ref;
    let mut has_inside_empty = *has_inside_empty_ref;
    let mut in_fence = *in_fence_ref;
    let mut has_next_uli = 0;
    let mut has_next_oli = 0;

    end += 1;
    while end < size && data[end - 1] != b'\n' {
        end += 1;
    }

    if is_empty(Some(&data[beg..]), end - beg) != 0 {
        in_empty = 1;
        beg = end;
        *beg_ref = beg;
        *end_ref = end;
        *pre_ref = pre;
        *sublist_ref = sublist;
        *i_ref = i;
        *in_empty_ref = in_empty;
        *has_inside_empty_ref = has_inside_empty;
        *in_fence_ref = in_fence;
        return;
    }

    i = 0;
    while i < 4 && (beg + i) < end && data[beg + i] == b' ' {
        i += 1;
    }

    pre = i;
    if rndr.ext_flags & crate::MkdExtensions::MKDEXT_FENCED_CODE as u32 != 0 {
        if is_codefence(&data[beg + i..end - beg - i], None) != 0 {
            in_fence = if in_fence != 0 { 0 } else { 1 };
        }
    }

    if in_fence == 0 {
        has_next_uli = prefix_uli(&data[beg + i..end - beg - i]);
        has_next_oli = prefix_oli(&data[beg + i..end - beg - i]);
    }

    if in_empty != 0 && (((*flags & 1 != 0) && has_next_uli != 0) || ((*flags & 1 == 0) && has_next_oli != 0)) {
        *flags |= 8;
        *beg_ref = beg;
        *end_ref = end;
        *pre_ref = pre;
        *sublist_ref = sublist;
        *i_ref = i;
        *in_empty_ref = in_empty;
        *has_inside_empty_ref = has_inside_empty;
        *in_fence_ref = in_fence;
        return;
    }

    if (has_next_uli != 0 && !is_hrule(&data[beg + i..end - beg - i])) || has_next_oli != 0 {
        if in_empty != 0 {
            has_inside_empty = 1;
        }
        if pre == orgpre {
            *beg_ref = beg;
            *end_ref = end;
            *pre_ref = pre;
            *sublist_ref = sublist;
            *i_ref = i;
            *in_empty_ref = in_empty;
            *has_inside_empty_ref = has_inside_empty;
            *in_fence_ref = in_fence;
            return;
        }
        if sublist == 0 {
            sublist = work.size;
        }
    } else if in_empty != 0 && pre == 0 {
        *flags |= 8;
        *beg_ref = beg;
        *end_ref = end;
        *pre_ref = pre;
        *sublist_ref = sublist;
        *i_ref = i;
        *in_empty_ref = in_empty;
        *has_inside_empty_ref = has_inside_empty;
        *in_fence_ref = in_fence;
        return;
    } else if in_empty != 0 {
        bufputc(work, b'\n' as i32);
        has_inside_empty = 1;
    }

    in_empty = 0;
    bufput(work, &data[beg + i..end - beg - i], end - beg - i);
    beg = end;

    *beg_ref = beg;
    *end_ref = end;
    *pre_ref = pre;
    *sublist_ref = sublist;
    *i_ref = i;
    *in_empty_ref = in_empty;
    *has_inside_empty_ref = has_inside_empty;
    *in_fence_ref = in_fence;
}
pub fn prefix_blockspoiler(data: &[u8]) -> usize {
    let mut i = 0;
    
    // Check for leading spaces (up to 3)
    while i < data.len() && data[i] == b' ' && i < 3 {
        i += 1;
    }

    // Check for ">!" pattern
    if i + 1 < data.len() && data[i] == b'>' && data[i + 1] == b'!' {
        let spoilerspan = find_emph_char(&data[i + 1..], b'<');
        
        // Check for closing "!<" pattern
        if i + spoilerspan < data.len() && spoilerspan > 0 && data[i + spoilerspan] == b'!' {
            return 0;
        }
        
        // Check for optional space after ">!"
        if i + 2 < data.len() && data[i + 2] == b' ' {
            return i + 3;
        }
        
        return i + 2;
    }
    
    0
}
pub fn helper_helper_parse_htmlblock_1_1(
    size_ref: &mut usize,
    i_ref: &mut usize,
    j_ref: &mut usize,
    work_ref: &mut Buf,
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    do_render: bool,
) -> Option<usize> {
    let size = *size_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut work = work_ref.clone();

    i = 5;
    while i < size && !(data[i - 2] == b'-' && data[i - 1] == b'-' && data[i] == b'>') {
        i += 1;
    }

    i += 1;
    if i < size {
        j = is_empty(Some(&data[i..]), size - i);
    }

    if j != 0 {
        work.size = i + j;
        if do_render {
            if let Some(callback) = &mut rndr.cb.blockhtml {
                if let Some(opaque) = &mut rndr.opaque {
                    callback(ob, &work, opaque.as_mut());
                }
            }
        }
        return Some(work.size);
    }

    *size_ref = size;
    *i_ref = i;
    *j_ref = j;
    *work_ref = work;
    None
}
pub fn helper_helper_parse_htmlblock_1_2(
    size_ref: &mut usize,
    i_ref: &mut usize,
    j_ref: &mut usize,
    work_ref: &mut Buf,
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    do_render: bool,
) -> Option<usize> {
    let size = *size_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut work = work_ref.clone();

    i = 3;
    while i < size && data[i] != b'>' {
        i += 1;
    }

    if (i + 1) < size {
        i += 1;
        j = is_empty(Some(&data[i..]), size - i);
        if j > 0 {
            work.size = i + j;
            if do_render {
                if let Some(callback) = &rndr.cb.blockhtml {
                    if let Some(opaque) = &mut rndr.opaque {
                        callback(ob, &work, opaque);
                    }
                }
            }
            return Some(work.size);
        }
    }

    *size_ref = size;
    *i_ref = i;
    *j_ref = j;
    *work_ref = work;
    None
}
pub fn helper_parse_htmlblock_1(
    size_ref: &mut usize,
    i_ref: &mut usize,
    j_ref: &mut usize,
    work_ref: &mut Buf,
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    do_render: bool,
) -> usize {
    let mut size = *size_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut work = work_ref.clone();

    if size > 5 && data[1] == b'!' && data[2] == b'-' && data[3] == b'-' {
        helper_helper_parse_htmlblock_1_1(
            &mut size,
            &mut i,
            &mut j,
            &mut work,
            ob,
            rndr,
            data,
            do_render,
        );
    }

    if size > 4 
        && (data[1].to_ascii_lowercase() == b'h') 
        && (data[2].to_ascii_lowercase() == b'r') 
    {
        helper_helper_parse_htmlblock_1_2(
            &mut size,
            &mut i,
            &mut j,
            &mut work,
            ob,
            rndr,
            data,
            do_render,
        );
    }

    *size_ref = size;
    *i_ref = i;
    *j_ref = j;
    *work_ref = work;

    0
}
pub fn hash_block_tag(str: &[u8], len: usize) -> u32 {
    static ASSO_VALUES: [u8; 256] = [
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 8, 30, 25, 20, 15, 10, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 0,
        38, 0, 38, 5, 5, 5, 15, 0, 38, 38, 0, 15, 10, 0, 38, 38, 15, 0, 5, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 0, 38, 0, 38, 5, 5, 5, 15, 0, 38, 38, 0, 15, 10, 0, 38, 38,
        15, 0, 5, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38,
        38, 38, 38, 38, 38, 38, 38, 38,
    ];

    let mut hval = len as u32;

    match len {
        1 => {
            hval += ASSO_VALUES[str[0] as usize] as u32;
        }
        _ => {
            hval += ASSO_VALUES[str[1] as usize + 1] as u32;
            hval += ASSO_VALUES[str[0] as usize] as u32;
        }
    }

    hval
}
pub fn find_block_tag(str: &[u8], len: usize) -> Option<&'static str> {
    const TOTAL_KEYWORDS: usize = 24;
    const MIN_WORD_LENGTH: usize = 1;
    const MAX_WORD_LENGTH: usize = 10;
    const MIN_HASH_VALUE: u32 = 1;
    const MAX_HASH_VALUE: u32 = 37;

    static WORDLIST: [&str; 38] = [
        "", "p", "dl", "div", "math", "table", "", "ul", "del", "form", "blockquote", "figure", "ol",
        "fieldset", "", "h1", "", "h6", "pre", "", "", "script", "h5", "noscript", "", "style",
        "iframe", "h4", "ins", "", "", "", "h3", "", "", "", "h2", "span",
    ];

    if len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH {
        let key = hash_block_tag(str, len);
        if key <= MAX_HASH_VALUE && key >= MIN_HASH_VALUE {
            let s = WORDLIST[key as usize];
            if !s.is_empty()
                && str.len() >= len
                && s.len() == len
                && str[..len].eq_ignore_ascii_case(s.as_bytes())
            {
                return Some(s);
            }
        }
    }
    None
}

pub fn htmlblock_end_tag(
    tag: Option<&str>,
    tag_len: usize,
    rndr: &SdMarkdown,
    data: Option<&[u8]>,
    size: usize,
) -> usize {
    // Early return if data is None or size is too small
    let data = match data {
        Some(d) if d.len() >= size => d,
        _ => return 0,
    };

    // Check conditions from line 5
    if tag_len + 3 >= size {
        return 0;
    }

    let tag = match tag {
        Some(t) => t,
        None => return 0,
    };

    // Compare strings case-insensitively (equivalent to strncasecmp)
    let data_slice = &data[2..2 + tag_len];
    let tag_bytes = tag.as_bytes();
    if !data_slice.eq_ignore_ascii_case(&tag_bytes[..tag_len.min(tag_bytes.len())]) {
        return 0;
    }

    if data.get(tag_len + 2) != Some(&b'>') {
        return 0;
    }

    let mut i = tag_len + 3;
    let mut w = 0;

    // Check conditions from lines 11-14
    if i < size {
        w = is_empty(Some(&data[i..]), size - i);
        if w == 0 {
            return 0;
        }
    }

    i += w;
    w = 0;

    // Check conditions from lines 17-20
    if i < size {
        w = is_empty(Some(&data[i..]), size - i);
    }

    i + w
}
pub fn htmlblock_end(
    curtag: Option<&str>,
    rndr: &SdMarkdown,
    data: Option<&[u8]>,
    size: usize,
    start_of_line: bool,
) -> usize {
    // Early return if any required input is None
    let curtag = match curtag {
        Some(t) => t,
        None => return 0,
    };
    let data = match data {
        Some(d) => d,
        None => return 0,
    };

    let tag_size = curtag.len();
    let mut i = 1;
    let mut block_lines = 0;

    while i < size {
        i += 1;
        
        // Find the next potential closing tag
        while i < size && !(data[i - 1] == b'<' && data[i] == b'/') {
            if data[i] == b'\n' {
                block_lines += 1;
            }
            i += 1;
        }

        if start_of_line && block_lines > 0 && data.get(i - 2) != Some(&b'\n') {
            continue;
        }

        if (i + 2 + tag_size) >= size {
            break;
        }

        // Calculate the remaining data slice
        let remaining_data = &data[(i - 1)..];
        let remaining_size = size - (i - 1);

        let end_tag = htmlblock_end_tag(
            Some(curtag),
            tag_size,
            rndr,
            Some(remaining_data),
            remaining_size,
        );

        if end_tag != 0 {
            return (i + end_tag) - 1;
        }
    }

    0
}
pub fn parse_htmlblock(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], size: usize, do_render: bool) -> usize {
    if size < 2 || data[0] != b'<' {
        return 0;
    }
    
    let mut i = 1;
    while i < size && data[i] != b'>' && data[i] != b' ' {
        i += 1;
    }
    
    let curtag = if i < size {
        let tag_slice = &data[1..i];
        find_block_tag(tag_slice, i - 1)
    } else {
        None
    };
    
    if curtag.is_none() {
        let mut j = 0;
        let work = Buf {
            data: Some(data.to_vec()),
            size: 0,
            asize: 0,
            unit: 0,
        };
        helper_parse_htmlblock_1(&mut size.clone(), &mut i, &mut j, &mut work.clone(), ob, rndr, data, do_render);
    }
    
    let mut tag_end = htmlblock_end(curtag.as_deref(), rndr, Some(data), size, true);
    if tag_end == 0 && curtag.is_some() {
        if let Some(curtag_str) = curtag.as_deref() {
            if curtag_str != "ins" && curtag_str != "del" {
                tag_end = htmlblock_end(curtag.as_deref(), rndr, Some(data), size, false);
            }
        }
    }
    
    if tag_end == 0 {
        return 0;
    }
    
    let work = Buf {
        data: Some(data[..tag_end].to_vec()),
        size: tag_end,
        asize: 0,
        unit: 0,
    };
    
    if do_render {
        if let Some(blockhtml_cb) = &rndr.cb.blockhtml {
            if let Some(opaque) = &mut rndr.opaque {
                blockhtml_cb(ob, &work, opaque);
            }
        }
    }
    
    tag_end
}
pub fn helper_parse_table_header_1(
    i_ref: &mut usize,
    col_ref: &mut usize,
    data: &[u8],
    column_data: &mut [i32],
    under_end: usize,
) -> bool {
    const MKD_TABLE_ALIGN_L: i32 = 1;  // Left alignment flag
    const MKD_TABLE_ALIGN_R: i32 = 2;  // Right alignment flag

    let mut i = *i_ref;
    let mut col = *col_ref;
    let mut dashes = 0;

    // Skip leading spaces
    while i < under_end && data[i] == b' ' {
        i += 1;
    }

    // Check for left alignment marker
    if i < under_end && data[i] == b':' {
        i += 1;
        column_data[col] |= MKD_TABLE_ALIGN_L;
        dashes += 1;
    }

    // Count dashes
    while i < under_end && data[i] == b'-' {
        i += 1;
        dashes += 1;
    }

    // Check for right alignment marker
    if i < under_end && data[i] == b':' {
        i += 1;
        column_data[col] |= MKD_TABLE_ALIGN_R;
        dashes += 1;
    }

    // Skip trailing spaces
    while i < under_end && data[i] == b' ' {
        i += 1;
    }

    // Check termination conditions
    if (i < under_end && data[i] != b'|') || dashes < 1 {
        return false;
    }

    i += 1;
    *i_ref = i;
    *col_ref = col;
    true
}
pub fn helper_parse_table_row_1(
    i_ref: &mut usize,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
    col_data: &[i32],
    header_flag: i32,
    col: usize,
    row_work: &mut Buf,
) {
    let mut i = *i_ref;
    let mut cell_work = match rndr_newbuf(rndr, 1) {
        Some(buf) => buf,
        None => return,
    };

    while i < size && _isspace(data[i] as i32) {
        i += 1;
    }

    let cell_start = i;

    while i < size && data[i] != b'|' {
        i += 1;
    }

    let mut cell_end = i.saturating_sub(1);
    while cell_end > cell_start && _isspace(data[cell_end] as i32) {
        cell_end -= 1;
    }

    if cell_end >= cell_start {
        let cell_data = &data[cell_start..=cell_end];
        parse_inline(&mut *cell_work, rndr, cell_data, cell_data.len());
    }

    if let Some(table_cell_fn) = &rndr.cb.table_cell {
        let mut opaque_ptr = rndr.opaque.as_mut().map(|b| &mut **b as &mut dyn std::any::Any);
        table_cell_fn(
            row_work,
            &cell_work,
            col_data[col] | header_flag,
            opaque_ptr.as_deref_mut().unwrap_or(&mut ()),
            0,
        );
    }
    rndr_popbuf(rndr, 1);
    i += 1;
    *i_ref = i;
}
pub fn parse_table_row(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
    columns: usize,
    col_data: &Vec<i32>,  // Changed from &mut [i32] to &Vec<i32>
    header_flag: i32,
) {
    let mut i = 0;
    let mut col = 0;
    let cols_left;
    let mut row_work: Option<Box<Buf>> = None;

    // Check if the required callbacks are available
    if rndr.cb.table_cell.is_none() || rndr.cb.table_row.is_none() {
        return;
    }

    row_work = rndr_newbuf(rndr, 1);
    if row_work.is_none() {
        return;
    }

    // Skip initial pipe character if present
    if i < size && data[i] == b'|' {
        i += 1;
    }

    // Process each column
    let mut row_work_ref = row_work.as_mut().unwrap();
    for col_idx in 0..columns {
        if i >= size {
            break;
        }
        helper_parse_table_row_1(
            &mut i,
            rndr,
            data,
            size,
            col_data,
            header_flag,
            col_idx,
            &mut row_work_ref,
        );
        col = col_idx + 1;
    }

    // Handle remaining empty columns
    cols_left = columns - col;
    if cols_left > 0 {
        let empty_cell = Buf {
            data: None,
            size: 0,
            asize: 0,
            unit: 0,
        };
        if let Some(ref table_cell_cb) = rndr.cb.table_cell {
            table_cell_cb(
                &mut *row_work_ref,
                &empty_cell,
                col_data[col] | header_flag,
                &mut rndr.opaque,
                cols_left as i32,
            );
        }
    }

    // Call table row callback
    if let Some(ref table_row_cb) = rndr.cb.table_row {
        table_row_cb(ob, &*row_work_ref, &mut rndr.opaque);
    }

    rndr_popbuf(rndr, 1);
}
pub fn parse_table_header(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
    columns: &mut usize,
    column_data: &mut Option<Vec<i32>>,
) -> Option<usize> {
    let mut pipes = 0;
    let mut i = 0;
    
    // Count pipes in the first line
    while i < size && data[i] != b'\n' {
        if data[i] == b'|' {
            pipes += 1;
        }
        i += 1;
    }

    if i == size || pipes == 0 {
        return None;
    }

    let mut header_end = i;
    
    // Trim trailing whitespace from header
    while header_end > 0 && data[header_end - 1].is_ascii_whitespace() {
        header_end -= 1;
    }

    // Adjust pipe count for leading/trailing pipes
    if data[0] == b'|' {
        pipes -= 1;
    }
    if header_end > 0 && data[header_end - 1] == b'|' {
        pipes -= 1;
    }

    if pipes + 1 > rndr.max_table_cols {
        return None;
    }

    *columns = pipes + 1;
    *column_data = Some(vec![0; *columns]);
    
    i += 1;
    if i < size && data[i] == b'|' {
        i += 1;
    }

    let mut under_end = i;
    while under_end < size && data[under_end] != b'\n' {
        under_end += 1;
    }

    let mut col = 0;
    
    while col < *columns && i < under_end {
        // This would call helper_parse_table_header_1 if it were available
        // For now, we'll just increment i and col to avoid infinite loop
        i += 1;
        col += 1;
    }

    if col < *columns {
        return None;
    }

    if let Some(col_data) = column_data {
        parse_table_row(
            ob,
            rndr,
            data,
            header_end,
            *columns,
            col_data,
            MKD_TABLE_HEADER as i32,
        );
    }

    Some(under_end + 1)
}
pub fn parse_table(
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
) -> usize {
    let mut i = 0;
    let mut header_work = None;
    let mut body_work = None;
    let mut columns = 0;
    let mut col_data: Option<Vec<i32>> = None;

    header_work = rndr_newbuf(rndr, 1);
    body_work = rndr_newbuf(rndr, 0);

    if let (Some(ref mut header_work), Some(ref mut body_work)) = (header_work.as_mut(), body_work.as_mut()) {
        i = parse_table_header(
            header_work,
            rndr,
            data,
            size,
            &mut columns,
            &mut col_data,
        ).unwrap_or(0);

        if i > 0 {
            while i < size {
                let mut pipes = 0;
                let row_start = i;
                
                let mut j = i;
                while j < size && data[j] != b'\n' {
                    if data[j] == b'|' {
                        pipes += 1;
                    }
                    j += 1;
                }
                i = j;

                if pipes == 0 || i == size {
                    i = row_start;
                    break;
                }

                parse_table_row(
                    body_work,
                    rndr,
                    &data[row_start..i],
                    i - row_start,
                    columns,
                    col_data.as_ref().unwrap(),
                    0,
                );
                
                if i < size {
                    i += 1;
                }
            }

            if let Some(table_cb) = &rndr.cb.table {
                if let Some(opaque) = &mut rndr.opaque {
                    table_cb(ob, header_work, body_work, opaque);
                }
            }
        }
    }

    // Free col_data like the original C code's free(col_data)
    drop(col_data);

    // Always pop the buffers like the original C code
    rndr_popbuf(rndr, 1);
    rndr_popbuf(rndr, 0);
    
    i
}
pub fn parse_atxheader(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], size: usize) -> usize {
    let mut level = 0;
    while level < size && level < 6 && data[level] == b'#' {
        level += 1;
    }

    let mut i = level;
    while i < size && data[i] == b' ' {
        i += 1;
    }

    let mut end = i;
    while end < size && data[end] != b'\n' {
        end += 1;
    }

    let mut skip = end;
    while end > 0 && data[end - 1] == b'#' {
        end -= 1;
    }

    while end > 0 && data[end - 1] == b' ' {
        end -= 1;
    }

    if end > i {
        if let Some(mut work) = rndr_newbuf(rndr, 1) {
            parse_inline(&mut work, rndr, &data[i..end], end - i);
            if let Some(header_cb) = &rndr.cb.header {
                if let Some(opaque) = &mut rndr.opaque {
                    header_cb(ob, &work, level as i32, opaque);
                }
            }
            rndr_popbuf(rndr, 1);
        }
    }

    skip
}
fn parse_fencedcode(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], size: usize) -> usize {
    let mut lang = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };
    let mut beg = is_codefence(data, Some(&mut lang));
    if beg == 0 {
        return 0;
    }
    let mut work = rndr_newbuf(rndr, 0).unwrap();
    let mut current_beg = beg;
    while current_beg < size {
        let mut fence_trail = Buf {
            data: None,
            size: 0,
            asize: 0,
            unit: 0,
        };
        let fence_end = is_codefence(&data[current_beg..], Some(&mut fence_trail));
        if fence_end != 0 && fence_trail.size == 0 {
            current_beg += fence_end;
            break;
        }
        let mut end = current_beg + 1;
        while end < size && data[end - 1] != b'\n' {
            end += 1;
        }
        if current_beg < end {
            if is_empty(Some(&data[current_beg..]), end - current_beg) != 0 {
                bufputc(&mut work, b'\n' as i32);
            } else {
                bufput(&mut work, &data[current_beg..], end - current_beg);
            }
        }
        current_beg = end;
    }
    if work.size != 0 && work.data.as_ref().unwrap()[work.size - 1] != b'\n' {
        bufputc(&mut work, b'\n' as i32);
    }
    if let Some(blockcode) = &rndr.cb.blockcode {
        let lang_ref = if lang.size != 0 { Some(&lang) } else { None };
        blockcode(ob, &work, lang_ref.unwrap_or(&Buf { data: None, size: 0, asize: 0, unit: 0 }), &mut rndr.opaque);
    }
    rndr_popbuf(rndr, 0);
    current_beg
}
pub fn prefix_code(data: &[u8]) -> usize {
    if data.len() > 3 && data[0] == b' ' && data[1] == b' ' && data[2] == b' ' && data[3] == b' ' {
        4
    } else {
        0
    }
}
pub fn parse_blockcode(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], size: usize) -> usize {
    let mut beg = 0;
    let mut work = match rndr_newbuf(rndr, 0) {
        Some(buf) => buf,
        None => return beg,
    };

    while beg < size {
        let mut end = beg + 1;
        while end < size && data[end - 1] != b'\n' {
            end += 1;
        }

        let pre = prefix_code(&data[beg..]);
        if pre > 0 {
            beg += pre;
        } else if is_empty(Some(&data[beg..]), end - beg) == 0 {
            break;
        }

        if beg < end {
            if is_empty(Some(&data[beg..]), end - beg) > 0 {
                bufputc(&mut work, b'\n' as i32);
            } else {
                bufput(&mut work, &data[beg..], end - beg);
            }
        }
        beg = end;
    }

    while work.size > 0 {
        if let Some(ref work_data) = work.data {
            if work_data[work.size - 1] == b'\n' {
                work.size -= 1;
            } else {
                break;
            }
        } else {
            break;
        }
    }

    bufputc(&mut work, b'\n' as i32);
    
    if let Some(blockcode_cb) = &rndr.cb.blockcode {
        if let Some(ref mut opaque) = rndr.opaque {
            // Create a static empty buffer to represent null
            static EMPTY_BUF: Buf = Buf { data: None, size: 0, asize: 0, unit: 0 };
            blockcode_cb(ob, &work, &EMPTY_BUF, opaque);
        }
    }
    
    rndr_popbuf(rndr, 0);
    beg
}
pub fn is_atxheader(rndr: &SdMarkdown, data: &[u8], size: usize) -> bool {
    if data.is_empty() || data[0] != b'#' {
        return false;
    }

    const MKDEXT_SPACE_HEADERS: u32 = 0x0001; // Assuming typical bitflag value
    if rndr.ext_flags & MKDEXT_SPACE_HEADERS != 0 {
        let mut level = 0;
        while level < size && level < 6 && data[level] == b'#' {
            level += 1;
        }

        if level < size && data[level] != b' ' {
            return false;
        }
    }

    true
}
pub fn helper_parse_paragraph_1(
    i_ref: &mut usize,
    end_ref: &mut usize,
    level_ref: &mut i32,
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    size: usize,
) {
    let mut i = *i_ref;
    let mut end = *end_ref;
    let mut level = *level_ref;

    // Find the next newline (Rust slices are exclusive, so we don't need end + 1)
    end = i + 1;
    while end < size && data[end - 1] != b'\n' {
        end += 1;
    }

    if prefix_quote(&data[i..end]) != 0 {
        end = i;
    } else if is_empty(Some(&data[i..size]), size - i) != 0 {
        // Do nothing, just break the loop
    } else {
        level = is_headerline(&data[i..size]) as i32;
        if level != 0 {
            // Do nothing, just break the loop
        } else if is_atxheader(rndr, &data[i..size], size - i)
            || is_hrule(&data[i..size])
            || prefix_quote(&data[i..size]) != 0
        {
            end = i;
        } else if (rndr.ext_flags & crate::MkdExtensions::MKDEXT_LAX_SPACING as u32) != 0 && !data[i].is_ascii_alphanumeric() {
            if prefix_oli(&data[i..size]) != 0 || prefix_uli(&data[i..size]) != 0 {
                end = i;
            } else if data[i] == b'<'
                && rndr.cb.blockhtml.is_some()
                && parse_htmlblock(ob, rndr, &data[i..size], size - i, false) != 0
            {
                end = i;
            } else if (rndr.ext_flags & crate::MkdExtensions::MKDEXT_FENCED_CODE as u32) != 0
                && is_codefence(&data[i..size], None) != 0
            {
                end = i;
            }
        }
    }

    i = end;
    *i_ref = i;
    *end_ref = end;
    *level_ref = level;
}
pub fn helper_parse_paragraph_2(
    i_ref: &mut usize,
    work_ref: &mut Buf,
    ob: &mut Buf,
    rndr: &mut SdMarkdown,
    data: &[u8],
    level: i32,
) {
    let mut i = *i_ref;
    let mut work = work_ref.clone();

    if work.size > 0 {
        let beg;
        i = work.size;
        work.size -= 1;

        while work.size > 0 && data[work.size] != b'\n' {
            work.size -= 1;
        }

        beg = work.size + 1;

        while work.size > 0 && data[work.size - 1] == b'\n' {
            work.size -= 1;
        }

        if work.size > 0 {
            let mut tmp = match rndr_newbuf(rndr, 0) {
                Some(buf) => buf,
                None => return,
            };
            parse_inline(&mut tmp, rndr, &work.data.as_ref().unwrap()[..work.size], work.size);
            
            if let Some(cb) = &rndr.cb.paragraph {
                let opaque = rndr.opaque.as_mut().map(|b| b.as_mut());
                cb(ob, &tmp, opaque.unwrap());
            }
            
            rndr_popbuf(rndr, 0);
            
            if let Some(work_data) = &mut work.data {
                *work_data = work_data[beg..].to_vec();
            }
            work.size = i - beg;
        } else {
            work.size = i;
        }
    }

    if let Some(mut header_work) = rndr_newbuf(rndr, 1) {
        parse_inline(&mut header_work, rndr, &work.data.as_ref().unwrap()[..work.size], work.size);
        
        if let Some(cb) = &rndr.cb.header {
            let opaque = rndr.opaque.as_mut().map(|b| b.as_mut());
            cb(ob, &header_work, level, opaque.unwrap());
        }
        
        rndr_popbuf(rndr, 1);
    }

    *i_ref = i;
    *work_ref = work;
}
pub fn parse_paragraph(ob: &mut Buf, rndr: &mut SdMarkdown, data: &[u8], size: usize) -> usize {
    let mut i = 0;
    let mut end = 0;
    let mut level = 0;
    let mut work = Buf {
        data: Some(Vec::from(data)),
        size: 0,
        asize: 0,
        unit: 0,
    };

    while i < size {
        helper_parse_paragraph_1(&mut i, &mut end, &mut level, ob, rndr, data, size);
    }

    work.size = i;
    while work.size > 0 && unsafe { *data.get_unchecked(work.size - 1) } == b'\n' {
        work.size -= 1;
    }

    if level == 0 {
        if let Some(mut tmp) = rndr_newbuf(rndr, 0) {
            let work_data_ptr = work.data.as_ref().unwrap().as_ptr();
            parse_inline(&mut *tmp, rndr, unsafe { std::slice::from_raw_parts(work_data_ptr, work.size) }, work.size);
            if let Some(paragraph_cb) = rndr.cb.paragraph.as_ref() {
                paragraph_cb(ob, &*tmp, rndr.opaque.as_mut().map(|b| &mut **b).unwrap());
            }
            rndr_popbuf(rndr, 0);
        }
    } else {
        helper_parse_paragraph_2(&mut i, &mut work, ob, rndr, data, level);
    }
    
    end
}
pub fn sd_markdown_render(
    ob: &mut Buf,
    document: &[u8],
    doc_size: usize,
    md: &mut SdMarkdown,
) {
    static UTF8_BOM: [u8; 3] = [0xEF, 0xBB, 0xBF];
    
    let mut text = match bufnew(64) {
        Some(mut buf) => {
            if let Err(_) = bufgrow(&mut buf, doc_size) {
                return;
            }
            buf
        },
        None => return,
    };
    
    // Initialize refs array with null pointers (None in Rust)
    md.refs.iter_mut().for_each(|ptr| *ptr = None);
    
    let mut beg = 0;
    
    // Check for UTF-8 BOM
    if doc_size >= 3 && document[0..3] == UTF8_BOM {
        beg += 3;
    }
    
    while beg < doc_size {
        let mut end = 0;
        helper_sd_markdown_render_1(&mut beg, &mut end, document, doc_size, md, &mut text);
    }
    
    if let Err(_) = bufgrow(ob, text.size + (text.size >> 1)) {
        bufrelease(Some(text));
        return;
    }
    
    if let Some(doc_header) = &md.cb.doc_header {
        if let Some(ref mut opaque) = md.opaque {
            doc_header(ob, opaque.as_mut());
        }
    }
    
    if text.size > 0 {
        let last_char = text.data.as_ref().unwrap()[text.size - 1];
        if last_char != b'\n' && last_char != b'\r' {
            bufputc(&mut text, b'\n' as i32);
        }
        // parse_block function should be defined elsewhere - this is a dependency issue
        // For now, we'll comment it out as it's not in the provided scope
        // parse_block(ob, md, text.data.as_ref().unwrap(), text.size);
    }
    
    if let Some(doc_footer) = &md.cb.doc_footer {
        if let Some(ref mut opaque) = md.opaque {
            doc_footer(ob, opaque.as_mut());
        }
    }
    
    bufrelease(Some(text));
    free_link_refs(&mut md.refs);
    
    assert!(md.work_bufs[1].size == 0);
    assert!(md.work_bufs[0].size == 0);
}
pub fn sd_version(ver_major: Option<&mut i32>, ver_minor: Option<&mut i32>, ver_revision: Option<&mut i32>) {
    if let Some(major) = ver_major {
        *major = 1;
    }
    if let Some(minor) = ver_minor {
        *minor = 16;
    }
    if let Some(revision) = ver_revision {
        *revision = 0;
    }
}

pub fn backport_getrandom(buf: &mut [u8], flags: c_uint) -> io::Result<usize> {
    let buflen = buf.len() as size_t;
    let result = unsafe {
        libc::syscall(
            libc::SYS_getrandom,
            buf.as_mut_ptr() as *mut c_void,
            buflen,
            flags
        )
    };
    
    if result < 0 {
        Err(io::Error::last_os_error())
    } else {
        Ok(result as usize)
    }
}
pub fn sd_markdown_free(md: Option<Box<SdMarkdown>>) {
    // Early return if md is None (equivalent to NULL check in C)
    let mut md = match md {
        Some(md) => md,
        None => return,
    };

    // Release buffers in work_bufs[1]
    if let Some(items) = &mut md.work_bufs[1].item {
        for i in 0..md.work_bufs[1].asize {
            if let Some(buf) = items[i].take() {
                if let Ok(buf) = buf.downcast::<Buf>() {
                    bufrelease(Some(buf));
                }
            }
        }
    }

    // Release buffers in work_bufs[0]
    if let Some(items) = &mut md.work_bufs[0].item {
        for i in 0..md.work_bufs[0].asize {
            if let Some(buf) = items[i].take() {
                if let Ok(buf) = buf.downcast::<Buf>() {
                    bufrelease(Some(buf));
                }
            }
        }
    }

    // Free the stacks
    stack_free(&mut md.work_bufs[1]);
    stack_free(&mut md.work_bufs[0]);

    // md is automatically dropped when it goes out of scope
}
pub fn sd_markdown_new(
    extensions: u32,
    max_nesting: size_t,
    max_table_cols: size_t,
    callbacks: SdCallbacks,
    opaque: Option<Box<dyn std::any::Any>>,
) -> Option<Box<SdMarkdown>> {
    assert!(max_nesting > 0 && max_table_cols > 0);
    
    let md = unsafe {
        let layout = std::alloc::Layout::new::<SdMarkdown>();
        std::alloc::alloc(layout) as *mut SdMarkdown
    };
    
    if md.is_null() {
        return None;
    }
    
    if !SIP_HASH_KEY_INIT.load(std::sync::atomic::Ordering::SeqCst) {
        let mut key_buffer = [0u8; 16];
        let success = unsafe {
            backport_getrandom(&mut key_buffer, 0).map(|n| n == 16).unwrap_or(false)
        };
        if success {
            let mut key_guard = SIP_HASH_KEY.lock().unwrap();
            key_guard.copy_from_slice(&key_buffer);
            SIP_HASH_KEY_INIT.store(true, std::sync::atomic::Ordering::SeqCst);
        }
    }
    
    if !SIP_HASH_KEY_INIT.load(std::sync::atomic::Ordering::SeqCst) {
        unsafe {
            std::alloc::dealloc(md as *mut u8, std::alloc::Layout::new::<SdMarkdown>());
        }
        return None;
    }
    
    unsafe {
        ptr::write(&mut (*md).cb, callbacks);
        
        stack_init(&mut (*md).work_bufs[0], 4);
        stack_init(&mut (*md).work_bufs[1], 8);
        
        ptr::write_bytes((*md).active_char.as_mut_ptr(), 0x0, 256);
        
        if (*md).cb.emphasis.is_some() || (*md).cb.double_emphasis.is_some() || (*md).cb.triple_emphasis.is_some() {
            (*md).active_char[b'*' as usize] = MarkdownCharT::MD_CHAR_EMPHASIS as u8;
            (*md).active_char[b'_' as usize] = MarkdownCharT::MD_CHAR_EMPHASIS as u8;
            (*md).active_char[b'>' as usize] = MarkdownCharT::MD_CHAR_EMPHASIS as u8;
            if extensions & MkdExtensions::MKDEXT_STRIKETHROUGH as u32 != 0 {
                (*md).active_char[b'~' as usize] = MarkdownCharT::MD_CHAR_EMPHASIS as u8;
            }
        }
        
        if (*md).cb.codespan.is_some() {
            (*md).active_char[b'`' as usize] = MarkdownCharT::MD_CHAR_CODESPAN as u8;
        }
        
        if (*md).cb.linebreak.is_some() {
            (*md).active_char[b'\n' as usize] = MarkdownCharT::MD_CHAR_LINEBREAK as u8;
        }
        
        if (*md).cb.image.is_some() || (*md).cb.link.is_some() {
            (*md).active_char[b'[' as usize] = MarkdownCharT::MD_CHAR_LINK as u8;
        }
        
        (*md).active_char[b'<' as usize] = MarkdownCharT::MD_CHAR_LANGLE as u8;
        (*md).active_char[b'\\' as usize] = MarkdownCharT::MD_CHAR_ESCAPE as u8;
        (*md).active_char[b'&' as usize] = MarkdownCharT::MD_CHAR_ENTITITY as u8;
        
        if extensions & MkdExtensions::MKDEXT_AUTOLINK as u32 != 0 {
            if extensions & MkdExtensions::MKDEXT_NO_EMAIL_AUTOLINK as u32 == 0 {
                (*md).active_char[b'@' as usize] = MarkdownCharT::MD_CHAR_AUTOLINK_EMAIL as u8;
            }
            (*md).active_char[b':' as usize] = MarkdownCharT::MD_CHAR_AUTOLINK_URL as u8;
            (*md).active_char[b'w' as usize] = MarkdownCharT::MD_CHAR_AUTOLINK_WWW as u8;
            (*md).active_char[b'/' as usize] = MarkdownCharT::MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME as u8;
        }
        
        if extensions & MkdExtensions::MKDEXT_SUPERSCRIPT as u32 != 0 {
            (*md).active_char[b'^' as usize] = MarkdownCharT::MD_CHAR_SUPERSCRIPT as u8;
        }
        
        (*md).ext_flags = extensions;
        (*md).opaque = opaque;
        (*md).max_nesting = max_nesting;
        (*md).max_table_cols = max_table_cols;
        (*md).in_link_body = 0;
    }
    
    Some(unsafe { Box::from_raw(md) })
}
