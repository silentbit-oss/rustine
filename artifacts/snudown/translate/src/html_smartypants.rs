use crate::*;
use unicode_segmentation::UnicodeSegmentation;
use unicode_ident::is_xid_continue;
use unicode_ident::is_xid_start;
use std::cmp::Ordering;
use std::ascii;
use std::fmt::Write;
pub fn word_boundary(c: u8) -> bool {
    let c_char = c as char;
    c == 0 || c_char.is_whitespace() || !(is_xid_start(c_char) || is_xid_continue(c_char))
}

pub fn smartypants_quotes(
    ob: &mut Buf,
    previous_char: u8,
    next_char: u8,
    quote: u8,
    is_open: &mut bool,
) -> bool {
    let mut ent = String::with_capacity(8); // Pre-allocate space for the entity
    
    if *is_open && !word_boundary(next_char) {
        return false;
    }
    if !*is_open && !word_boundary(previous_char) {
        return false;
    }

    write!(
        ent,
        "&{}quo;",
        if *is_open { 'r' } else { 'l' }
    ).unwrap(); // Safe to unwrap since we're writing to a String
    
    *is_open = !*is_open;
    bufputs(ob, &ent);
    true
}
pub fn smartypants_cb__squote(
    ob: &mut Buf,
    smrt: &mut SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if size >= 2 {
        let t1 = text[1].to_ascii_lowercase();
        if t1 == b'\'' {
            let mut in_dquote_bool = smrt.in_dquote != 0;
            if smartypants_quotes(
                ob,
                previous_char,
                if size >= 3 { text[2] } else { 0 },
                b'd',
                &mut in_dquote_bool,
            ) {
                smrt.in_dquote = in_dquote_bool as i32;
                return 1;
            }
            smrt.in_dquote = in_dquote_bool as i32;
        }
        if ((t1 == b's' || t1 == b't' || t1 == b'm' || t1 == b'd')
            && (size == 3 || word_boundary(text[2])))
        {
            bufput(ob, b"&rsquo;", b"&rsquo;".len() - 1);
            return 0;
        }
        if size >= 3 {
            let t2 = text[2].to_ascii_lowercase();
            if (((t1 == b'r' && t2 == b'e')
                || (t1 == b'l' && t2 == b'l')
                || (t1 == b'v' && t2 == b'e'))
                && (size == 4 || word_boundary(text[3])))
            {
                bufput(ob, b"&rsquo;", b"&rsquo;".len() - 1);
                return 0;
            }
        }
    }
    let mut in_squote_bool = smrt.in_squote != 0;
    if smartypants_quotes(
        ob,
        previous_char,
        if size > 0 { text[1] } else { 0 },
        b's',
        &mut in_squote_bool,
    ) {
        smrt.in_squote = in_squote_bool as i32;
        return 0;
    }
    smrt.in_squote = in_squote_bool as i32;
    bufputc(ob, text[0] as i32);
    0
}
pub fn smartypants_cb__dquote(
    ob: &mut Buf,
    smrt: &mut SmartypantsData,
    previous_char: u8,
    text: Option<&[u8]>,
    size: usize,
) -> usize {
    let next_char = if size > 0 { text.unwrap()[1] } else { 0 };
    let mut in_dquote_bool = smrt.in_dquote != 0;
    
    if !smartypants_quotes(ob, previous_char, next_char, b'd', &mut in_dquote_bool) {
        bufput(ob, b"&quot;", size_of::<[u8; 6]>() - 1);
    }
    smrt.in_dquote = in_dquote_bool as i32;
    0
}

pub fn smartypants_cb__number(
    ob: &mut Buf,
    smrt: &SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if word_boundary(previous_char) && size >= 3 {
        if text[0] == b'1' && text[1] == b'/' && text[2] == b'2' {
            if size == 3 || word_boundary(text[3]) {
                bufput(ob, b"&frac12;", 8);
                return 2;
            }
        }
        if text[0] == b'1' && text[1] == b'/' && text[2] == b'4' {
            if size == 3
                || word_boundary(text[3])
                || (size >= 5
                    && text[3].to_ascii_lowercase() == b't'
                    && text[4].to_ascii_lowercase() == b'h')
            {
                bufput(ob, b"&frac14;", 8);
                return 2;
            }
        }
        if text[0] == b'3' && text[1] == b'/' && text[2] == b'4' {
            if size == 3
                || word_boundary(text[3])
                || (size >= 6
                    && text[3].to_ascii_lowercase() == b't'
                    && text[4].to_ascii_lowercase() == b'h'
                    && text[5].to_ascii_lowercase() == b's')
            {
                bufput(ob, b"&frac34;", 8);
                return 2;
            }
        }
    }
    bufputc(ob, text[0] as i32);
    0
}
pub fn smartypants_cb__escape(
    ob: &mut Buf,
    smrt: &SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if size < 2 {
        return 0;
    }

    match text[1] {
        b'\\' | b'"' | b'\'' | b'.' | b'-' | b'`' => {
            bufputc(ob, text[1] as i32);
            1
        }
        _ => {
            bufputc(ob, b'\\' as i32);
            0
        }
    }
}
pub fn smartypants_cb__ltag(
    ob: &mut Buf,
    smrt: &SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    const HTML_TAG_OPEN: i32 = 1;  // Assuming these values from typical HTML tag parsing
    const HTML_TAG_CLOSE: i32 = 2; // implementations where 1=open, 2=close
    
    static SKIP_TAGS: [&str; 8] = ["pre", "code", "var", "samp", "kbd", "math", "script", "style"];
    let mut i = 0;
    
    // Find the closing '>' character
    while i < size && text[i] != b'>' {
        i += 1;
    }

    // Check if the tag is in our skip list
    let mut tag_found = None;
    for (tag_idx, tag_name) in SKIP_TAGS.iter().enumerate() {
        if sdhtml_is_tag(text, tag_name) == HTML_TAG_OPEN {
            tag_found = Some(tag_idx);
            break;
        }
    }

    if let Some(tag_idx) = tag_found {
        loop {
            // Find the next '<' character
            while i < size && text[i] != b'<' {
                i += 1;
            }

            if i == size {
                break;
            }

            // Check if it's the closing tag we're looking for
            if sdhtml_is_tag(&text[i..], SKIP_TAGS[tag_idx]) == HTML_TAG_CLOSE {
                break;
            }

            i += 1;
        }

        // Find the closing '>' character of the closing tag
        while i < size && text[i] != b'>' {
            i += 1;
        }
    }

    bufput(ob, text, i + 1);
    i
}
pub fn smartypants_cb__amp(
    ob: &mut Buf,
    smrt: &mut SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if size >= 6 && text[..6].cmp(b"&quot;") == Ordering::Equal {
        let next_char = if size >= 7 { text[6] } else { 0 };
        let mut is_open = smrt.in_dquote != 0;
        if smartypants_quotes(ob, previous_char, next_char, b'd', &mut is_open) {
            smrt.in_dquote = is_open as i32;
            return 5;
        }
    }
    if size >= 4 && text[..4].cmp(b"&#0;") == Ordering::Equal {
        return 3;
    }
    bufputc(ob, b'&' as i32);
    0
}
pub fn smartypants_cb__period(
    ob: &mut Buf,
    smrt: &SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if size >= 3 && text[1] == b'.' && text[2] == b'.' {
        bufput(ob, b"&hellip;", size_of::<&[u8; 8]>() - 1);
        return 2;
    }
    if size >= 5
        && text[1] == b' '
        && text[2] == b'.'
        && text[3] == b' '
        && text[4] == b'.'
    {
        bufput(ob, b"&hellip;", size_of::<&[u8; 8]>() - 1);
        return 4;
    }
    bufputc(ob, text[0] as i32);
    0
}
pub fn smartypants_cb__backtick(
    ob: &mut Buf,
    smrt: &mut SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> bool {
    if size >= 2 && text[1] == b'`' {
        let next_char = if size >= 3 { text[2] } else { 0 };
        let mut is_open = smrt.in_dquote != 0;
        let result = smartypants_quotes(ob, previous_char, next_char, b'd', &mut is_open);
        smrt.in_dquote = is_open as i32;
        result
    } else {
        false
    }
}
pub fn smartypants_cb__parens(
    ob: &mut Buf,
    smrt: &SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if size >= 3 {
        let t1 = text[1].to_ascii_lowercase();
        let t2 = text[2].to_ascii_lowercase();
        
        if (t1 == b'c') && (t2 == b')') {
            bufput(ob, b"&copy;", b"&copy;".len() - 1);
            return 2;
        }
        if (t1 == b'r') && (t2 == b')') {
            bufput(ob, b"&reg;", b"&reg;".len() - 1);
            return 2;
        }
        if (size >= 4) && (t1 == b't') && (t2 == b'm') && (text[3] == b')') {
            bufput(ob, b"&trade;", b"&trade;".len() - 1);
            return 3;
        }
    }
    bufputc(ob, text[0] as i32);
    0
}
pub fn smartypants_cb__dash(
    ob: &mut Buf,
    smrt: &SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize {
    if size >= 3 && text[1] == b'-' && text[2] == b'-' {
        bufput(ob, b"&mdash;", size_of::<&[u8; 7]>() - 1);
        return 2;
    }
    if size >= 2 && text[1] == b'-' {
        bufput(ob, b"&ndash;", size_of::<&[u8; 7]>() - 1);
        return 1;
    }
    bufputc(ob, text[0] as i32);
    0
}
pub fn sdhtml_smartypants(ob: &mut Buf, text: Option<&[u8]>, size: usize) {
    // Check for None (equivalent to NULL check in C)
    let text = match text {
        Some(t) => t,
        None => return,
    };

    // Grow the buffer if needed
    if let Err(_) = bufgrow(ob, size) {
        return;
    }

    let mut i = 0;
    let mut smrt = SmartypantsData {
        in_squote: 0,
        in_dquote: 0,
    };

    while i < size {
        let org = i;
        let mut action = 0;

        // Find the next character with an action
        while i < size && { action = SMARTYPANTS_CB_CHARS[text[i] as usize]; action == 0 } {
            i += 1;
        }

        // Add the text between org and i
        if i > org {
            bufput(ob, &text[org..i], i - org);
        }

        // Process the action if we found one
        if i < size {
            let callback = SMARTYPANTS_CB_PTRS.lock().unwrap()[action as usize];
            if let Some(cb) = callback {
                let previous_char = if i > 0 { text[i - 1] } else { 0 };
                i += cb(ob, &mut smrt, previous_char, &text[i..], size - i);
            } else {
                i += 1;
            }
        }
    }
}
