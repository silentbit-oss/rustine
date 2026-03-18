use crate::*;

pub fn houdini_escape_html0(ob: &mut Buf, src: &[u8], size: usize, secure: bool) {
    let mut i = 0;
    let mut org;
    let mut esc = 0;
    
    // Grow the buffer (ignore error as original C code doesn't check)
    let _ = bufgrow(ob, (size * 12) / 10);

    while i < size {
        org = i;
        while i < size {
            esc = HTML_ESCAPE_TABLE[src[i] as usize];
            if esc != 0 {
                break;
            }
            i += 1;
        }

        if i > org {
            bufput(ob, &src[org..i], i - org);
        }
        if i >= size {
            break;
        }
        
        if src[i] == b'/' && !secure {
            bufputc(ob, b'/' as i32);
        } else if HTML_ESCAPE_TABLE[src[i] as usize] == 7 {
            // Do nothing (original C code has empty block)
        } else {
            bufputs(ob, HTML_ESCAPES[esc as usize]);
        }
        
        i += 1;
    }
}
pub fn houdini_escape_html(ob: &mut Buf, src: &[u8], size: usize) {
    houdini_escape_html0(ob, src, size, true);
}
