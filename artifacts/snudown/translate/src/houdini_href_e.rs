use crate::*;

pub fn houdini_escape_href(ob: &mut Buf, src: &[u8], size: usize) {
    const HEX_CHARS: &[u8; 16] = b"0123456789ABCDEF";
    let mut i = 0;
    let mut org;
    let mut hex_str = [0u8; 3];
    hex_str[0] = b'%';

    bufgrow(ob, (size * 12) / 10).expect("Failed to grow buffer");

    while i < size {
        org = i;
        while i < size && HREF_SAFE[src[i] as usize] == 1 {
            i += 1;
        }

        if i > org {
            bufput(ob, &src[org..i], i - org);
        }
        if i >= size {
            break;
        }
        if HREF_SAFE[src[i] as usize] == 2 {
            i += 1;
            continue;
        }

        match src[i] {
            b'&' => bufput(ob, b"&amp;", 5),
            b'\'' => bufput(ob, b"&#x27;", 6),
            _ => {
                hex_str[1] = HEX_CHARS[(src[i] >> 4) as usize & 0xF];
                hex_str[2] = HEX_CHARS[src[i] as usize & 0xF];
                bufput(ob, &hex_str, 3);
            }
        }

        i += 1;
    }
}
