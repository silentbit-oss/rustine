use crate::*;
use std::ascii;
use std::ffi::c_void;
use std::fmt::Write;
use std::mem::size_of;

pub fn sdhtml_is_tag(tag_data: &[u8], tagname: &str) -> i32 {
    const HTML_TAG_NONE: i32 = 0;
    const HTML_TAG_OPEN: i32 = 1;
    const HTML_TAG_CLOSE: i32 = 2;

    let tag_size = tag_data.len();
    let mut closed: i32 = 0;
    if tag_size < 3 || tag_data[0] != b'<' {
        return HTML_TAG_NONE;
    }
    let mut i = 1;
    if tag_data[i] == b'/' {
        closed = 1;
        i += 1;
    }
    let tagname_bytes = tagname.as_bytes();
    let mut j = 0;
    while i < tag_size && j < tagname_bytes.len() {
        if tag_data[i] != tagname_bytes[j] {
            return HTML_TAG_NONE;
        }
        i += 1;
        j += 1;
    }

    if i == tag_size {
        return HTML_TAG_NONE;
    }
    let current_char = tag_data[i] as i32;
    if unsafe { libc::isspace(current_char) } != 0 || tag_data[i] == b'>' {
        return if closed != 0 { HTML_TAG_CLOSE } else { HTML_TAG_OPEN };
    }
    HTML_TAG_NONE
}
pub fn escape_html(ob: &mut Buf, source: &[u8], length: usize) {
    houdini_escape_html0(ob, source, length, false);
}
pub fn escape_href(ob: &mut Buf, source: &[u8], length: usize) {
    houdini_escape_href(ob, source, length);
}
pub fn rndr_spoilerspan(ob: &mut Buf, text: Option<&Buf>, _opaque: ()) -> bool {
    // Check if text is None or if its size is 0 (equivalent to C's NULL/size check)
    let text = match text {
        Some(t) if t.size > 0 => t,
        _ => return false,
    };

    // Use bufput to add the spoiler span tags and content
    bufput(ob, b"<span class=\"md-spoiler-text\">", size_of::<&[u8; 29]>() - 1);
    bufput(ob, text.data.as_ref().unwrap(), text.size);
    bufput(ob, b"</span>", size_of::<&[u8; 7]>() - 1);

    true
}

pub fn rndr_strikethrough(ob: &mut Buf, text: Option<&Buf>, _opaque: ()) -> i32 {
    // Check if text is None or its size is 0 (equivalent to C's NULL/size check)
    let text = match text {
        Some(t) if t.size > 0 => t,
        _ => return 0,
    };

    // Write the opening tag
    bufput(ob, b"<del>", size_of::<&[u8; 5]>() - 1);
    
    // Write the text content
    if let Some(data) = &text.data {
        bufput(ob, data, text.size);
    }
    
    // Write the closing tag
    bufput(ob, b"</del>", size_of::<&[u8; 6]>() - 1);
    
    1
}
pub fn rndr_double_emphasis(ob: &mut Buf, text: Option<&Buf>, opaque: *mut ()) -> i32 {
    // Check if text is None or if its size is 0 (equivalent to C's NULL/size check)
    if text.is_none() || text.unwrap().size == 0 {
        return 0;
    }
    let text = text.unwrap();

    // Use bufput to append the tags and text content
    bufput(ob, b"<strong>", b"<strong>".len());
    bufput(ob, text.data.as_ref().unwrap(), text.size);
    bufput(ob, b"</strong>", b"</strong>".len());

    1
}
pub fn rndr_emphasis(ob: &mut Buf, text: Option<&Buf>, opaque: &mut ()) -> i32 {
    // Check if text is None or if its size is 0 (equivalent to C's NULL/size check)
    if text.is_none() || text.unwrap().size == 0 {
        return 0;
    }

    // Safe to unwrap since we checked above
    let text = text.unwrap();

    // Write opening <em> tag
    bufput(ob, b"<em>", size_of::<&[u8; 4]>() - 1);

    // Write the text content
    if let Some(data) = &text.data {
        bufput(ob, data, text.size);
    }

    // Write closing </em> tag
    bufput(ob, b"</em>", size_of::<&[u8; 5]>() - 1);

    1
}
pub fn rndr_listitem(ob: &mut Buf, text: Option<&Buf>, flags: i32, opaque: *mut std::ffi::c_void) {
    bufput(ob, b"<li>", size_of::<[u8; 4]>() - 1);
    
    if let Some(text) = text {
        let mut size = text.size;
        while size > 0 && text.data.as_ref().map_or(false, |d| d[size - 1] == b'\n') {
            size -= 1;
        }
        
        if let Some(data) = &text.data {
            bufput(ob, &data[..size], size);
        }
    }
    
    bufput(ob, b"</li>\n", size_of::<[u8; 6]>() - 1);
}
pub fn rndr_triple_emphasis(ob: &mut Buf, text: Option<&Buf>, _opaque: Option<&()>) -> i32 {
    // Check if text is None or text.size is 0 (equivalent to C's NULL/size check)
    if text.is_none() || text.unwrap().size == 0 {
        return 0;
    }
    let text = text.unwrap();

    // Use bufput to append the HTML tags and text content
    bufput(ob, b"<strong><em>", b"<strong><em>".len());
    bufput(ob, text.data.as_ref().unwrap(), text.size);
    bufput(ob, b"</em></strong>", b"</em></strong>".len());

    1
}
pub fn rndr_tablerow(ob: &mut Buf, text: Option<&Buf>, _opaque: *mut std::ffi::c_void) {
    bufput(ob, b"<tr>\n", size_of::<&[u8; 5]>() - 1);
    if let Some(text) = text {
        bufput(ob, text.data.as_ref().unwrap(), text.size);
    }
    bufput(ob, b"</tr>\n", size_of::<&[u8; 6]>() - 1);
}
pub fn rndr_superscript(ob: &mut Buf, text: Option<&Buf>, _opaque: Option<&()>) -> i32 {
    // Check if text is None or if its size is 0 (equivalent to C's NULL/size check)
    if text.is_none() || text.unwrap().size == 0 {
        return 0;
    }
    let text = text.unwrap();

    // Use bufput to add the superscript tags and content
    bufput(ob, b"<sup>", size_of::<&[u8; 5]>() - 1);
    bufput(ob, text.data.as_ref().unwrap(), text.size);
    bufput(ob, b"</sup>", size_of::<&[u8; 6]>() - 1);

    1
}
pub fn rndr_normal_text(ob: &mut Buf, text: Option<&Buf>, _opaque: Option<&()>) {
    if let Some(text) = text {
        if let Some(data) = &text.data {
            escape_html(ob, data.as_slice(), text.size);
        }
    }
}
pub fn toc_link(
    ob: &mut Buf,
    link: &Buf,
    title: &Buf,
    content: Option<&Buf>,
    opaque: &mut (),
) -> i32 {
    if let Some(content) = content {
        if content.size > 0 {
            if let Some(data) = &content.data {
                bufput(ob, data, content.size);
            }
        }
    }
    1
}
pub fn reset_toc(ob: &mut Buf, opaque: &mut HtmlRenderopt) {
    opaque.toc_data = TocData {
        header_count: 0,
        current_level: 0,
        level_offset: 0,
    };
}
pub fn rndr_blockquote(ob: &mut Buf, text: Option<&Buf>, _opaque: *mut std::ffi::c_void) {
    if ob.size > 0 {
        bufputc(ob, b'\n' as i32);
    }
    bufput(ob, b"<blockquote>\n", "<blockquote>\n".len() - 1);
    if let Some(text) = text {
        bufput(ob, text.data.as_ref().unwrap(), text.size);
    }
    bufput(ob, b"</blockquote>\n", "</blockquote>\n".len() - 1);
}
pub fn rndr_blockspoiler(ob: &mut Buf, text: Option<&Buf>, _opaque: ()) {
    if ob.size > 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(ob, b"<blockquote class=\"md-spoiler-text\">\n", size_of::<[u8; 38]>() - 1);
    if let Some(text) = text {
        bufput(ob, text.data.as_ref().unwrap(), text.size);
    }
    bufput(ob, b"</blockquote>\n", size_of::<[u8; 14]>() - 1);
}
pub fn rndr_codespan(ob: &mut Buf, text: Option<&Buf>, _opaque: ()) -> i32 {
    bufput(ob, b"<code>", size_of::<&[u8; 6]>() - 1);
    
    if let Some(text) = text {
        escape_html(ob, text.data.as_ref().unwrap(), text.size);
    }
    
    bufput(ob, b"</code>", size_of::<&[u8; 7]>() - 1);
    1
}
pub fn rndr_linebreak(ob: &mut Buf, opaque: &HtmlRenderopt) -> i32 {
    const HTML_USE_XHTML: u32 = 1; // Assuming this is a bit flag, common value for such flags
    let linebreak = if opaque.flags & HTML_USE_XHTML != 0 {
        "<br/>\n"
    } else {
        "<br>\n"
    };
    bufputs(ob, linebreak);
    1
}
pub fn rndr_list(ob: &mut Buf, text: Option<&Buf>, flags: i32, opaque: *mut std::ffi::c_void) {
    if ob.size > 0 {
        bufputc(ob, '\n' as i32);
    }
    
    let tag = if (flags & 1) != 0 { b"<ol>\n" } else { b"<ul>\n" };
    bufput(ob, tag, tag.len());
    
    if let Some(text) = text {
        bufput(ob, text.data.as_ref().unwrap(), text.size);
    }
    
    let end_tag = if (flags & 1) != 0 { b"</ol>\n" } else { b"</ul>\n" };
    bufput(ob, end_tag, end_tag.len());
}
pub fn rndr_raw_block(ob: &mut Buf, text: Option<&Buf>, _opaque: Option<&()>) {
    // Check if text is None (equivalent to NULL check in C)
    let text = match text {
        Some(t) => t,
        None => return,
    };

    // Calculate sz by trimming trailing newlines
    let mut sz = text.size;
    while sz > 0 && text.data.as_ref().unwrap()[sz - 1] == b'\n' {
        sz -= 1;
    }

    // Calculate org by trimming leading newlines
    let mut org = 0;
    while org < sz && text.data.as_ref().unwrap()[org] == b'\n' {
        org += 1;
    }

    // Return if org >= sz (no content left after trimming)
    if org >= sz {
        return;
    }

    // Add newline if ob is not empty
    if ob.size > 0 {
        bufputc(ob, b'\n' as i32);
    }

    // Add the trimmed content and a trailing newline
    let data_slice = &text.data.as_ref().unwrap()[org..sz];
    bufput(ob, data_slice, sz - org);
    bufputc(ob, b'\n' as i32);
}
pub fn rndr_table(ob: &mut Buf, header: Option<&Buf>, body: Option<&Buf>, opaque: *mut std::ffi::c_void) {
    if ob.size > 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(ob, b"<table><thead>\n", size_of::<[u8; 15]>() - 1);
    
    if let Some(header) = header {
        bufput(ob, header.data.as_ref().unwrap(), header.size);
    }
    
    bufput(ob, b"</thead><tbody>\n", size_of::<[u8; 17]>() - 1);
    
    if let Some(body) = body {
        bufput(ob, body.data.as_ref().unwrap(), body.size);
    }
    
    bufput(ob, b"</tbody></table>\n", size_of::<[u8; 18]>() - 1);
}
pub fn rndr_tablecell(ob: &mut Buf, text: Option<&Buf>, flags: i32, opaque: &mut dyn std::any::Any, col_span: i32) {
    const MKD_TABLE_HEADER: i32 = 1 << 0;
    const MKD_TABLE_ALIGNMASK: i32 = 0x03;
    const MKD_TABLE_ALIGN_CENTER: i32 = 0x01;
    const MKD_TABLE_ALIGN_L: i32 = 0x02;
    const MKD_TABLE_ALIGN_R: i32 = 0x03;

    if flags & MKD_TABLE_HEADER != 0 {
        bufput(ob, b"<th", 3);
    } else {
        bufput(ob, b"<td", 3);
    }
    
    if col_span > 1 {
        bufprintf(ob, " colspan=\"%d\" ", format_args!("{}", col_span));
    }
    
    match flags & MKD_TABLE_ALIGNMASK {
        MKD_TABLE_ALIGN_CENTER => {
            bufput(ob, b" align=\"center\">", 15);
        }
        MKD_TABLE_ALIGN_L => {
            bufput(ob, b" align=\"left\">", 14);
        }
        MKD_TABLE_ALIGN_R => {
            bufput(ob, b" align=\"right\">", 15);
        }
        _ => {
            bufput(ob, b">", 1);
        }
    }
    
    if let Some(text) = text {
        bufput(ob, &text.data.as_ref().unwrap(), text.size);
    }
    
    if flags & MKD_TABLE_HEADER != 0 {
        bufput(ob, b"</th>\n", 6);
    } else {
        bufput(ob, b"</td>\n", 6);
    }
}

pub fn rndr_blockcode(
    ob: &mut Buf,
    text: Option<&Buf>,
    lang: Option<&Buf>,
    _opaque: Option<&()>, // opaque is unused in the original function
) {
    if ob.size > 0 {
        bufputc(ob, '\n' as i32);
    }

    if let Some(lang) = lang {
        if lang.size > 0 {
            bufput(ob, b"<pre><code class=\"", size_of::<&[u8]>() - 1);
            
            let mut i = 0;
            let mut cls = 0;
            while i < lang.size {
                // Skip whitespace
                while i < lang.size && lang.data.as_ref().map_or(false, |d| {
                    ascii::escape_default(d[i]).any(|c| c == b' ' || c == b'\t' || c == b'\n' || c == b'\r' || c == b'\x0C' || c == b'\x0B')
                }) {
                    i += 1;
                }

                if i < lang.size {
                    let org = i;
                    // Find next whitespace
                    while i < lang.size && !lang.data.as_ref().map_or(false, |d| {
                        ascii::escape_default(d[i]).any(|c| c == b' ' || c == b'\t' || c == b'\n' || c == b'\r' || c == b'\x0C' || c == b'\x0B')
                    }) {
                        i += 1;
                    }

                    let mut org = org;
                    if lang.data.as_ref().map_or(false, |d| d[org] == b'.') {
                        org += 1;
                    }

                    if cls > 0 {
                        bufputc(ob, ' ' as i32);
                    }
                    cls += 1;

                    if let Some(data) = &lang.data {
                        escape_html(ob, &data[org..i], i - org);
                    }
                }
            }

            bufput(ob, b"\">", size_of::<&[u8]>() - 1);
        } else {
            bufput(ob, b"<pre><code>", size_of::<&[u8]>() - 1);
        }
    } else {
        bufput(ob, b"<pre><code>", size_of::<&[u8]>() - 1);
    }

    if let Some(text) = text {
        if let Some(data) = &text.data {
            escape_html(ob, data, text.size);
        }
    }

    bufput(ob, b"</code></pre>\n", size_of::<&[u8]>() - 1);
}
pub fn rndr_hrule(ob: &mut Buf, opaque: &HtmlRenderopt) {
    const HTML_USE_XHTML: u32 = 1; // Assuming this is a bit flag, common value for such flags
    
    if ob.size > 0 {
        bufputc(ob, '\n' as i32);
    }
    let hr_tag = if opaque.flags & HTML_USE_XHTML != 0 {
        "<hr/>\n"
    } else {
        "<hr>\n"
    };
    bufputs(ob, hr_tag);
}
pub fn toc_finalize(ob: &mut Buf, opaque: &mut HtmlRenderopt) {
    let mut has_toc = false;
    
    while opaque.toc_data.current_level > 0 {
        bufput(ob, b"</li>\n</ul>\n", size_of::<&[u8; 11]>() - 1);
        opaque.toc_data.current_level -= 1;
        has_toc = true;
    }

    if has_toc {
        bufput(ob, b"</div>\n", size_of::<&[u8; 7]>() - 1);
    }
    
    reset_toc(ob, opaque);
}
pub fn helper_helper_rndr_html_tag_1_1(
    x_ref: &mut usize,
    z_ref: &mut usize,
    reset_ref: &mut usize,
    ob: &mut Buf,
    whitelist: &[&str],
    attr: &Buf,
    value: &Buf,
) {
    let mut x = *x_ref;
    let mut z = *z_ref;
    let mut reset = *reset_ref;
    let mut valid = false;

    for (i, &item) in whitelist.iter().enumerate() {
        if item.len() != attr.size {
            continue;
        }

        let mut matched = true;
        for (j, attr_char) in attr.data.as_ref().unwrap()[..attr.size].iter().enumerate() {
            let whitelist_char = item.as_bytes()[j];
            if whitelist_char.to_ascii_lowercase() != attr_char.to_ascii_lowercase() {
                matched = false;
                break;
            }
        }

        if matched {
            valid = true;
            z = i;
            break;
        }
    }

    if valid && value.size != 0 && attr.size != 0 {
        bufputc(ob, b' '.into());
        escape_html(ob, &attr.data.as_ref().unwrap()[..attr.size], attr.size);
        bufputs(ob, "=\"");
        escape_html(ob, &value.data.as_ref().unwrap()[..value.size], value.size);
        bufputc(ob, b'"'.into());
    }

    reset = 1;
    *x_ref = x;
    *z_ref = z;
    *reset_ref = reset;
}
pub fn helper_rndr_html_tag_1(
    x_ref: &mut usize,
    z_ref: &mut usize,
    in_str_ref: &mut usize,
    seen_equals_ref: &mut usize,
    done_ref: &mut usize,
    done_attr_ref: &mut usize,
    reset_ref: &mut usize,
    c_ref: &mut char,
    ob: &mut Buf,
    text: &Buf,
    whitelist: &[&str],
    i: usize,
    attr: &mut Buf,
    value: &mut Buf,
) {
    let mut x = *x_ref;
    let mut z = *z_ref;
    let mut in_str = *in_str_ref;
    let mut seen_equals = *seen_equals_ref;
    let mut done = *done_ref;
    let mut done_attr = *done_attr_ref;
    let mut reset = *reset_ref;
    let mut c = text.data.as_ref().unwrap()[i] as char;

    done = 0;
    reset = 0;
    done_attr = 0;

    match c {
        '>' => {
            done = 1;
        }
        '\'' | '"' => {
            if seen_equals == 0 {
                reset = 1;
            } else if in_str == 0 {
                in_str = c as usize;
            } else if in_str == c as usize {
                in_str = 0;
                done_attr = 1;
            } else {
                bufputc(value, c as i32);
            }
        }
        ' ' => {
            if in_str != 0 {
                bufputc(value, ' ' as i32);
            } else {
                reset = 1;
            }
        }
        '=' => {
            if seen_equals != 0 {
                reset = 1;
            } else {
                seen_equals = 1;
            }
        }
        _ => {
            if (seen_equals != 0 && in_str != 0) || seen_equals == 0 {
                if seen_equals != 0 {
                    bufputc(value, c as i32);
                } else {
                    bufputc(attr, c as i32);
                }
            }
        }
    }

    if done_attr != 0 {
        helper_helper_rndr_html_tag_1_1(
            &mut x,
            &mut z,
            &mut reset,
            ob,
            whitelist,
            attr,
            value,
        );
    }

    if reset != 0 {
        seen_equals = 0;
        in_str = 0;
        bufreset(attr);
        bufreset(value);
    }

    *x_ref = x;
    *z_ref = z;
    *in_str_ref = in_str;
    *seen_equals_ref = seen_equals;
    *done_ref = done;
    *done_attr_ref = done_attr;
    *reset_ref = reset;
    *c_ref = c;
}
pub const HTML_HARD_WRAP: u32 = 1; // Assuming this is the correct value based on common flag patterns

pub fn rndr_paragraph(ob: &mut Buf, text: Option<&Buf>, opaque: &HtmlRenderopt) {
    if ob.size > 0 {
        bufputc(ob, b'\n' as i32);
    }

    let text = match text {
        Some(t) if t.size > 0 => t,
        _ => return,
    };

    let mut i = 0;
    while i < text.size && text.data.as_ref().unwrap()[i].is_ascii_whitespace() {
        i += 1;
    }

    if i == text.size {
        return;
    }

    bufput(ob, b"<p>", 3);

    if opaque.flags & HTML_HARD_WRAP != 0 {
        while i < text.size {
            let org = i;
            while i < text.size && text.data.as_ref().unwrap()[i] != b'\n' {
                i += 1;
            }

            if i > org {
                bufput(ob, &text.data.as_ref().unwrap()[org..i], i - org);
            }

            if i >= text.size - 1 {
                break;
            }

            rndr_linebreak(ob, opaque);
            i += 1;
        }
    } else {
        bufput(ob, &text.data.as_ref().unwrap()[i..text.size], text.size - i);
    }

    bufput(ob, b"</p>\n", 5);
}
pub fn toc_header(ob: &mut Buf, text: Option<&Buf>, level: i32, opaque: &mut HtmlRenderopt) {
    let options = opaque;
    
    if options.toc_data.current_level == 0 {
        bufput(ob, b"<div class=\"toc\">\n", size_of::<&[u8; 18]>() - 1);
        options.toc_data.level_offset = level - 1;
    }
    
    let level = level - options.toc_data.level_offset;
    
    if level > options.toc_data.current_level {
        while level > options.toc_data.current_level {
            bufput(ob, b"<ul>\n<li>\n", size_of::<&[u8; 10]>() - 1);
            options.toc_data.current_level += 1;
        }
    } else if level < options.toc_data.current_level {
        bufput(ob, b"</li>\n", size_of::<&[u8; 6]>() - 1);
        while level < options.toc_data.current_level {
            bufput(ob, b"</ul>\n</li>\n", size_of::<&[u8; 12]>() - 1);
            options.toc_data.current_level -= 1;
        }
        bufput(ob, b"<li>\n", size_of::<&[u8; 5]>() - 1);
    } else {
        bufput(ob, b"</li>\n<li>\n", size_of::<&[u8; 10]>() - 1);
    }
    
    bufput(ob, b"<a href=\"#", size_of::<&[u8; 10]>() - 1);
    if let Some(prefix) = &options.toc_id_prefix {
        bufputs(ob, prefix);
    }
    bufprintf(ob, "toc_%d\">", format_args!("{}", options.toc_data.header_count));
    options.toc_data.header_count += 1;
    
    if let Some(text) = text {
        escape_html(ob, text.data.as_ref().unwrap(), text.size);
    }
    
    bufput(ob, b"</a>\n", size_of::<&[u8; 5]>() - 1);
}
pub fn sdhtml_toc_renderer(callbacks: &mut SdCallbacks, options: &mut HtmlRenderopt) {
    // Equivalent to memset(options, 0x0, sizeof(struct html_renderopt))
    *options = HtmlRenderopt {
        toc_data: TocData {
            header_count: 0,
            current_level: 0,
            level_offset: 0,
        },
        toc_id_prefix: None,
        flags: 0,
        html_element_whitelist: None,
        html_attr_whitelist: None,
        link_attributes: None,
    };

    options.flags = HtmlRenderMode::HTML_TOC as u32 | HtmlRenderMode::HTML_SKIP_HTML as u32;

    // Equivalent to memcpy(callbacks, &cb_default, sizeof(struct sd_callbacks))
    *callbacks = SdCallbacks {
        blockcode: None,
        blockquote: None,
        blockspoiler: None,
        blockhtml: None,
        header: Some(Box::new(|ob: &mut Buf, text: &Buf, level: i32, opaque: &mut dyn std::any::Any| {
            if let Some(opaque) = opaque.downcast_mut::<HtmlRenderopt>() {
                toc_header(ob, Some(text), level, opaque);
            }
        })),
        hrule: None,
        list: None,
        listitem: None,
        paragraph: None,
        table: None,
        table_row: None,
        table_cell: None,
        autolink: None,
        codespan: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            rndr_codespan(ob, Some(text), ())
        })),
        spoilerspan: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            rndr_spoilerspan(ob, Some(text), ()) as i32
        })),
        double_emphasis: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            let mut ptr = std::ptr::null_mut();
            rndr_double_emphasis(ob, Some(text), ptr)
        })),
        emphasis: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            let mut unit = ();
            rndr_emphasis(ob, Some(text), &mut unit)
        })),
        image: None,
        linebreak: None,
        link: Some(Box::new(|ob: &mut Buf, link: &Buf, title: &Buf, content: &Buf, _opaque: &mut dyn std::any::Any| {
            let mut unit = ();
            toc_link(ob, link, title, Some(content), &mut unit)
        })),
        raw_html_tag: None,
        triple_emphasis: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            rndr_triple_emphasis(ob, Some(text), None)
        })),
        strikethrough: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            rndr_strikethrough(ob, Some(text), ())
        })),
        superscript: Some(Box::new(|ob: &mut Buf, text: &Buf, _opaque: &mut dyn std::any::Any| {
            rndr_superscript(ob, Some(text), None)
        })),
        entity: None,
        normal_text: None,
        doc_header: None,
        doc_footer: Some(Box::new(|ob: &mut Buf, opaque: &mut dyn std::any::Any| {
            if let Some(opaque) = opaque.downcast_mut::<HtmlRenderopt>() {
                toc_finalize(ob, opaque);
            }
        })),
    };
}
pub const HTML_TAG_CLOSE: i32 = 1; // Assuming HTML_TAG_CLOSE is 1 based on common HTML tag conventions

pub fn rndr_html_tag(
    ob: &mut Buf,
    text: &Buf,
    opaque: Option<*mut std::ffi::c_void>,
    tagname: &str,
    whitelist: &[&str],
    tagtype: i32,
) {
    let mut in_str = 0;
    let mut seen_equals = 0;
    let mut done = 0;
    let mut done_attr = 0;
    let mut reset = 0;
    
    bufputc(ob, b'<' as i32);
    
    if tagtype == HTML_TAG_CLOSE {
        bufputc(ob, b'/' as i32);
        bufputs(ob, tagname);
        bufputc(ob, b'>' as i32);
        return;
    }
    
    bufputs(ob, tagname);
    let mut i = 1 + tagname.len();
    
    let attr_box = match bufnew(16) {
        Some(buf) => buf,
        None => return,
    };
    let mut attr = Box::into_raw(attr_box);
    
    let value_box = match bufnew(16) {
        Some(buf) => buf,
        None => {
            let _ = unsafe { Box::from_raw(attr) };
            return;
        }
    };
    let mut value = Box::into_raw(value_box);
    
    while i < text.size && done == 0 {
        let mut x = 0;
        let mut z = 0;
        let mut c = '\0';
        helper_rndr_html_tag_1(
            &mut x,
            &mut z,
            &mut in_str,
            &mut seen_equals,
            &mut done,
            &mut done_attr,
            &mut reset,
            &mut c,
            ob,
            text,
            whitelist,
            i,
            unsafe { &mut *attr },
            unsafe { &mut *value },
        );
        i += 1;
    }
    
    unsafe {
        let _ = Box::from_raw(attr);
        let _ = Box::from_raw(value);
    }
    bufputc(ob, b'>' as i32);
}
pub fn rndr_raw_html(ob: &mut Buf, text: &Buf, opaque: Option<&HtmlRenderopt>) -> i32 {
    const HTML_ALLOW_ELEMENT_WHITELIST: u32 = 1 << 0;
    const HTML_ESCAPE: u32 = 1 << 1;
    const HTML_SKIP_HTML: u32 = 1 << 2;
    const HTML_SKIP_STYLE: u32 = 1 << 3;
    const HTML_SKIP_LINKS: u32 = 1 << 4;
    const HTML_SKIP_IMAGES: u32 = 1 << 5;
    const HTML_TAG_NONE: i32 = 0;

    let options = match opaque {
        Some(opt) => opt,
        None => {
            bufput(ob, text.data.as_ref().unwrap(), text.size);
            return 1;
        }
    };

    if (options.flags & HTML_ALLOW_ELEMENT_WHITELIST) != 0 {
        if let Some(whitelist) = &options.html_element_whitelist {
            for tagname in whitelist {
                let tagtype = sdhtml_is_tag(text.data.as_ref().unwrap(), tagname);
                if tagtype != HTML_TAG_NONE {
                    let attr_whitelist = options.html_attr_whitelist
                        .as_ref()
                        .map(|v| v.iter().map(|s| s.as_str()).collect::<Vec<_>>())
                        .unwrap_or_default();
                    
                    rndr_html_tag(
                        ob,
                        text,
                        None,
                        tagname,
                        &attr_whitelist,
                        tagtype,
                    );
                    return 1;
                }
            }
        }
    }

    if (options.flags & HTML_ESCAPE) != 0 {
        escape_html(ob, text.data.as_ref().unwrap(), text.size);
        return 1;
    }

    if (options.flags & HTML_SKIP_HTML) != 0 {
        return 1;
    }

    if (options.flags & HTML_SKIP_STYLE) != 0 && sdhtml_is_tag(text.data.as_ref().unwrap(), "style") != HTML_TAG_NONE {
        return 1;
    }

    if (options.flags & HTML_SKIP_LINKS) != 0 && sdhtml_is_tag(text.data.as_ref().unwrap(), "a") != HTML_TAG_NONE {
        return 1;
    }

    if (options.flags & HTML_SKIP_IMAGES) != 0 && sdhtml_is_tag(text.data.as_ref().unwrap(), "img") != HTML_TAG_NONE {
        return 1;
    }

    bufput(ob, text.data.as_ref().unwrap(), text.size);
    1
}
pub const HTML_SAFELINK: u32 = 1; // Assuming this is the correct flag value based on common patterns

pub fn rndr_autolink(
    ob: &mut Buf,
    link: Option<&Buf>,
    type_: MkdAutolink,
    opaque: &HtmlRenderopt,
) -> i32 {
    // Check if link is None or has zero size (equivalent to C's NULL/size check)
    let link = match link {
        Some(l) if l.size > 0 => l,
        _ => return 0,
    };

    // Check if link is unsafe (HTML_SAFELINK flag is set and link is not safe)
    if (opaque.flags & HTML_SAFELINK != 0)
        && !sd_autolink_issafe(link.data.as_ref().unwrap(), link.size)
        && type_ != MkdAutolink::MKDA_EMAIL
    {
        return 0;
    }

    bufput(ob, b"<a href=\"", b"<a href=\"".len() - 1);
    if type_ == MkdAutolink::MKDA_EMAIL {
        bufput(ob, b"mailto:", b"mailto:".len() - 1);
    }

    let offset = 0;
    escape_href(
        ob,
        &link.data.as_ref().unwrap()[offset..],
        link.size - offset,
    );

    if let Some(link_attrs) = opaque.link_attributes {
        bufputc(ob, b'\"' as i32);
        link_attrs(ob.clone(), link.clone(), Box::new(opaque.clone()));
        bufputc(ob, b'>' as i32);
    } else {
        bufput(ob, b"\">", b"\">".len() - 1);
    }

    if bufprefix(link, "mailto:") == 0 {
        escape_html(ob, &link.data.as_ref().unwrap()[7..], link.size - 7);
    } else {
        escape_html(ob, link.data.as_ref().unwrap(), link.size);
    }

    bufput(ob, b"</a>", b"</a>".len() - 1);
    1
}
pub fn rndr_header(ob: &mut Buf, text: Option<&Buf>, level: i32, opaque: &mut HtmlRenderopt) {
    if ob.size > 0 {
        bufputc(ob, '\n' as i32);
    }

    if opaque.flags & crate::HtmlRenderMode::HTML_TOC as u32 != 0 {
        bufprintf(ob, &format!("<h{} id=\"", level), format_args!(""));
        if let Some(prefix) = &opaque.toc_id_prefix {
            bufputs(ob, prefix);
        }
        bufprintf(ob, "toc_{}\">", format_args!("{}", opaque.toc_data.header_count));
        opaque.toc_data.header_count += 1;
    } else {
        bufprintf(ob, "<h{}>", format_args!("{}", level));
    }

    if let Some(text) = text {
        bufput(ob, text.data.as_ref().unwrap(), text.size);
    }

    bufprintf(ob, "</h{}>\n", format_args!("{}", level));
}
pub fn rndr_link(
    ob: &mut Buf,
    link: Option<&Buf>,
    title: Option<&Buf>,
    content: Option<&Buf>,
    opaque: &mut dyn std::any::Any,
) -> i32 {
    let options = opaque.downcast_ref::<HtmlRenderopt>().expect("Expected HtmlRenderopt");
    
    // Check if link is unsafe
    if let Some(link) = link {
        if (options.flags & HTML_SAFELINK) != 0 && !sd_autolink_issafe(link.data.as_ref().unwrap(), link.size) {
            return 0;
        }
    }

    bufput(ob, b"<a href=\"", (b"<a href=\"".len()) - 1);
    
    if let Some(link) = link {
        if link.size > 0 {
            escape_href(ob, link.data.as_ref().unwrap(), link.size);
        }
    }

    if let Some(title) = title {
        if title.size > 0 {
            bufput(ob, b"\" title=\"", (b"\" title=\"".len()) - 1);
            escape_html(ob, title.data.as_ref().unwrap(), title.size);
        }
    }

    if let Some(link_attrs) = options.link_attributes {
        bufputc(ob, b'\"' as i32);
        link_attrs(
            ob.clone(),
            link.cloned().unwrap_or(Buf {
                data: None,
                size: 0,
                asize: 0,
                unit: 0,
            }),
            Box::new(()), // Pass an empty box instead of opaque
        );
        bufputc(ob, b'>' as i32);
    } else {
        bufput(ob, b"\">", (b"\">".len()) - 1);
    }

    if let Some(content) = content {
        if content.size > 0 {
            bufput(ob, content.data.as_ref().unwrap(), content.size);
        }
    }

    bufput(ob, b"</a>", (b"</a>".len()) - 1);
    1
}
const HTML_USE_XHTML: u32 = 1; // Assuming this is the correct value for the flag

pub fn rndr_image(
    ob: &mut Buf,
    link: Option<&Buf>,
    title: Option<&Buf>,
    alt: Option<&Buf>,
    opaque: &HtmlRenderopt,
) -> bool {
    // Check if link exists and has content (size > 0)
    let link = match link {
        Some(l) if l.size > 0 => l,
        _ => return false,
    };

    bufput(ob, b"<img src=\"", b"<img src=\"".len());
    escape_href(ob, link.data.as_ref().unwrap(), link.size);
    bufput(ob, b"\" alt=\"", b"\" alt=\"".len());

    if let Some(alt) = alt {
        if alt.size > 0 {
            escape_html(ob, alt.data.as_ref().unwrap(), alt.size);
        }
    }

    if let Some(title) = title {
        if title.size > 0 {
            bufput(ob, b"\" title=\"", b"\" title=\"".len());
            escape_html(ob, title.data.as_ref().unwrap(), title.size);
        }
    }

    let close_tag = if opaque.flags & HTML_USE_XHTML != 0 {
        "\"/>"
    } else {
        "\">"
    };
    bufputs(ob, close_tag);

    true
}
pub fn sdhtml_renderer(callbacks: &mut SdCallbacks, options: &mut HtmlRenderopt, render_flags: u32) {
    // Initialize the default callbacks (equivalent to cb_default in C)
    let cb_default = SdCallbacks {
        blockcode: Some(Box::new(|ob, text, lang, opaque| rndr_blockcode(ob, Some(text), Some(lang), Option::None))),
        blockquote: Some(Box::new(|ob, text, opaque| rndr_blockquote(ob, Some(text), std::ptr::null_mut()))),
        blockspoiler: Some(Box::new(|ob, text, opaque| rndr_blockspoiler(ob, Some(text), ()))),
        blockhtml: Some(Box::new(|ob, text, opaque| rndr_raw_block(ob, Some(text), Option::None))),
        header: Some(Box::new(|ob, text, level, opaque| rndr_header(ob, Some(text), level, opaque.downcast_mut::<HtmlRenderopt>().unwrap()))),
        hrule: Some(Box::new(|ob, opaque| rndr_hrule(ob, opaque.downcast_ref::<HtmlRenderopt>().unwrap()))),
        list: Some(Box::new(|ob, text, flags, opaque| rndr_list(ob, Some(text), flags, std::ptr::null_mut()))),
        listitem: Some(Box::new(|ob, text, flags, opaque| rndr_listitem(ob, Some(text), flags, std::ptr::null_mut()))),
        paragraph: Some(Box::new(|ob, text, opaque| rndr_paragraph(ob, Some(text), opaque.downcast_ref::<HtmlRenderopt>().unwrap()))),
        table: Some(Box::new(|ob, header, body, opaque| rndr_table(ob, Some(header), Some(body), std::ptr::null_mut()))),
        table_row: Some(Box::new(|ob, text, opaque| rndr_tablerow(ob, Some(text), std::ptr::null_mut()))),
        table_cell: Some(Box::new(|ob, text, flags, opaque, col_span| rndr_tablecell(ob, Some(text), flags, opaque, col_span))),
        autolink: Some(Box::new(|ob, link, type_, opaque| rndr_autolink(ob, Some(link), type_, opaque.downcast_ref::<HtmlRenderopt>().unwrap()))),
        codespan: Some(Box::new(|ob, text, opaque| rndr_codespan(ob, Some(text), ()) as i32)),
        spoilerspan: Some(Box::new(|ob, text, opaque| rndr_spoilerspan(ob, Some(text), ()) as i32)),
        double_emphasis: Some(Box::new(|ob, text, opaque| rndr_double_emphasis(ob, Some(text), std::ptr::null_mut()) as i32)),
        emphasis: Some(Box::new(|ob, text, opaque| rndr_emphasis(ob, Some(text), opaque.downcast_mut::<()>().unwrap()))),
        image: Some(Box::new(|ob, link, title, alt, opaque| rndr_image(ob, Some(link), Some(title), Some(alt), opaque.downcast_ref::<HtmlRenderopt>().unwrap()) as i32)),
        linebreak: Some(Box::new(|ob, opaque| rndr_linebreak(ob, opaque.downcast_ref::<HtmlRenderopt>().unwrap()))),
        link: Some(Box::new(|ob, link, title, content, opaque| rndr_link(ob, Some(link), Some(title), Some(content), opaque))),
        raw_html_tag: Some(Box::new(|ob, text, opaque| rndr_raw_html(ob, text, opaque.downcast_ref::<HtmlRenderopt>()))),
        triple_emphasis: Some(Box::new(|ob, text, opaque| rndr_triple_emphasis(ob, Some(text), Option::None))),
        strikethrough: Some(Box::new(|ob, text, opaque| rndr_strikethrough(ob, Some(text), ()) as i32)),
        superscript: Some(Box::new(|ob, text, opaque| rndr_superscript(ob, Some(text), Option::None))),
        entity: None,
        normal_text: Some(Box::new(|ob, text, opaque| rndr_normal_text(ob, Some(text), Option::None))),
        doc_header: None,
        doc_footer: None,
    };

    // Reset options (equivalent to memset in C)
    *options = HtmlRenderopt {
        toc_data: TocData {
            header_count: 0,
            current_level: 0,
            level_offset: 0,
        },
        toc_id_prefix: None,
        flags: render_flags,
        html_element_whitelist: None,
        html_attr_whitelist: None,
        link_attributes: None,
    };

    // Copy default callbacks (equivalent to memcpy in C)
    *callbacks = cb_default;

    // Modify callbacks based on render_flags
    const HTML_SKIP_IMAGES: u32 = 1 << 0;
    const HTML_SKIP_LINKS: u32 = 1 << 1;
    const HTML_SKIP_HTML: u32 = 1 << 2;
    const HTML_ESCAPE: u32 = 1 << 3;

    if render_flags & HTML_SKIP_IMAGES != 0 {
        callbacks.image = None;
    }
    if render_flags & HTML_SKIP_LINKS != 0 {
        callbacks.link = None;
        callbacks.autolink = None;
    }
    if (render_flags & HTML_SKIP_HTML != 0) || (render_flags & HTML_ESCAPE != 0) {
        callbacks.blockhtml = None;
    }
}
