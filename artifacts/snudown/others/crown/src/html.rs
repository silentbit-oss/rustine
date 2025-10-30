use ::libc;
extern "C" {
    fn bufnew(_: size_t) -> *mut buf;
    fn bufprefix(buf: *const buf, prefix: *const libc::c_char) -> libc::c_int;
    fn bufput(_: *mut buf, _: *const libc::c_void, _: size_t);
    fn bufputs(_: *mut buf, _: *const libc::c_char);
    fn bufputc(_: *mut buf, _: libc::c_int);
    fn bufrelease(_: *mut buf);
    fn bufreset(_: *mut buf);
    fn bufprintf(_: *mut buf, _: *const libc::c_char, _: ...);
    fn sd_autolink_issafe(link: *const uint8_t, link_len: size_t) -> libc::c_int;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn __ctype_b_loc() -> *mut *const libc::c_ushort;
    fn __ctype_tolower_loc() -> *mut *const __int32_t;
    fn houdini_escape_html0(
        ob: *mut buf,
        src: *const uint8_t,
        size: size_t,
        secure: libc::c_int,
    );
    fn houdini_escape_href(ob: *mut buf, src: *const uint8_t, size: size_t);
}
pub type size_t = libc::c_ulong;
pub type __uint8_t = libc::c_uchar;
pub type __int32_t = libc::c_int;
pub type uint8_t = __uint8_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct buf {
    pub data: *mut uint8_t,
    pub size: size_t,
    pub asize: size_t,
    pub unit: size_t,
}
pub type mkd_autolink = libc::c_uint;
pub const MKDA_EMAIL: mkd_autolink = 2;
pub const MKDA_NORMAL: mkd_autolink = 1;
pub const MKDA_NOT_AUTOLINK: mkd_autolink = 0;
pub type mkd_tableflags = libc::c_uint;
pub const MKD_TABLE_HEADER: mkd_tableflags = 4;
pub const MKD_TABLE_ALIGNMASK: mkd_tableflags = 3;
pub const MKD_TABLE_ALIGN_CENTER: mkd_tableflags = 3;
pub const MKD_TABLE_ALIGN_R: mkd_tableflags = 2;
pub const MKD_TABLE_ALIGN_L: mkd_tableflags = 1;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sd_callbacks {
    pub blockcode: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub blockquote: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub blockspoiler: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub blockhtml: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub header: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub hrule: Option::<unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> ()>,
    pub list: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub listitem: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub paragraph: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub table: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub table_row: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub table_cell: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            libc::c_int,
            *mut libc::c_void,
            libc::c_int,
        ) -> (),
    >,
    pub autolink: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            mkd_autolink,
            *mut libc::c_void,
        ) -> libc::c_int,
    >,
    pub codespan: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub spoilerspan: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub double_emphasis: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub emphasis: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub image: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            *const buf,
            *const buf,
            *mut libc::c_void,
        ) -> libc::c_int,
    >,
    pub linebreak: Option::<
        unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub link: Option::<
        unsafe extern "C" fn(
            *mut buf,
            *const buf,
            *const buf,
            *const buf,
            *mut libc::c_void,
        ) -> libc::c_int,
    >,
    pub raw_html_tag: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub triple_emphasis: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub strikethrough: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub superscript: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> libc::c_int,
    >,
    pub entity: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub normal_text: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
    pub doc_header: Option::<unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> ()>,
    pub doc_footer: Option::<unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> ()>,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct html_renderopt {
    pub toc_data: C2RustUnnamed,
    pub toc_id_prefix: *mut libc::c_char,
    pub flags: libc::c_uint,
    pub html_element_whitelist: *mut *mut libc::c_char,
    pub html_attr_whitelist: *mut *mut libc::c_char,
    pub link_attributes: Option::<
        unsafe extern "C" fn(*mut buf, *const buf, *mut libc::c_void) -> (),
    >,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed {
    pub header_count: libc::c_int,
    pub current_level: libc::c_int,
    pub level_offset: libc::c_int,
}
pub type C2RustUnnamed_0 = libc::c_uint;
pub const HTML_ALLOW_ELEMENT_WHITELIST: C2RustUnnamed_0 = 1024;
pub const HTML_ESCAPE: C2RustUnnamed_0 = 512;
pub const HTML_USE_XHTML: C2RustUnnamed_0 = 256;
pub const HTML_HARD_WRAP: C2RustUnnamed_0 = 128;
pub const HTML_TOC: C2RustUnnamed_0 = 64;
pub const HTML_SAFELINK: C2RustUnnamed_0 = 32;
pub const HTML_EXPAND_TABS: C2RustUnnamed_0 = 16;
pub const HTML_SKIP_LINKS: C2RustUnnamed_0 = 8;
pub const HTML_SKIP_IMAGES: C2RustUnnamed_0 = 4;
pub const HTML_SKIP_STYLE: C2RustUnnamed_0 = 2;
pub const HTML_SKIP_HTML: C2RustUnnamed_0 = 1;
pub type C2RustUnnamed_1 = libc::c_uint;
pub const HTML_TAG_CLOSE: C2RustUnnamed_1 = 2;
pub const HTML_TAG_OPEN: C2RustUnnamed_1 = 1;
pub const HTML_TAG_NONE: C2RustUnnamed_1 = 0;
pub const _ISspace: C2RustUnnamed_2 = 8192;
pub type C2RustUnnamed_2 = libc::c_uint;
pub const _ISalnum: C2RustUnnamed_2 = 8;
pub const _ISpunct: C2RustUnnamed_2 = 4;
pub const _IScntrl: C2RustUnnamed_2 = 2;
pub const _ISblank: C2RustUnnamed_2 = 1;
pub const _ISgraph: C2RustUnnamed_2 = 32768;
pub const _ISprint: C2RustUnnamed_2 = 16384;
pub const _ISxdigit: C2RustUnnamed_2 = 4096;
pub const _ISdigit: C2RustUnnamed_2 = 2048;
pub const _ISalpha: C2RustUnnamed_2 = 1024;
pub const _ISlower: C2RustUnnamed_2 = 512;
pub const _ISupper: C2RustUnnamed_2 = 256;
#[inline]
unsafe extern "C" fn tolower(mut __c: libc::c_int) -> libc::c_int {
    return if __c >= -(128 as libc::c_int) && __c < 256 as libc::c_int {
        *(*__ctype_tolower_loc()).offset(__c as isize)
    } else {
        __c
    };
}
#[no_mangle]
pub unsafe extern "C" fn sdhtml_is_tag(
    mut tag_data: *const uint8_t,
    mut tag_size: size_t,
    mut tagname: *const libc::c_char,
) -> libc::c_int {
    let mut i: size_t = 0;
    let mut closed: libc::c_int = 0 as libc::c_int;
    if tag_size < 3 as libc::c_int as size_t
        || *tag_data.offset(0 as libc::c_int as isize) as libc::c_int != '<' as i32
    {
        return HTML_TAG_NONE as libc::c_int;
    }
    i = 1 as libc::c_int as size_t;
    if *tag_data.offset(i as isize) as libc::c_int == '/' as i32 {
        closed = 1 as libc::c_int;
        i = i.wrapping_add(1);
        i;
    }
    while i < tag_size {
        if *tagname as libc::c_int == 0 as libc::c_int {
            break;
        }
        if *tag_data.offset(i as isize) as libc::c_int != *tagname as libc::c_int {
            return HTML_TAG_NONE as libc::c_int;
        }
        i = i.wrapping_add(1);
        i;
        tagname = tagname.offset(1);
        tagname;
    }
    if i == tag_size {
        return HTML_TAG_NONE as libc::c_int;
    }
    if *(*__ctype_b_loc()).offset(*tag_data.offset(i as isize) as libc::c_int as isize)
        as libc::c_int & _ISspace as libc::c_int as libc::c_ushort as libc::c_int != 0
        || *tag_data.offset(i as isize) as libc::c_int == '>' as i32
    {
        return if closed != 0 {
            HTML_TAG_CLOSE as libc::c_int
        } else {
            HTML_TAG_OPEN as libc::c_int
        };
    }
    return HTML_TAG_NONE as libc::c_int;
}
#[inline]
unsafe extern "C" fn escape_html(
    mut ob: *mut buf,
    mut source: *const uint8_t,
    mut length: size_t,
) {
    houdini_escape_html0(ob, source, length, 0 as libc::c_int);
}
#[inline]
unsafe extern "C" fn escape_href(
    mut ob: *mut buf,
    mut source: *const uint8_t,
    mut length: size_t,
) {
    houdini_escape_href(ob, source, length);
}
unsafe extern "C" fn rndr_autolink(
    mut ob: *mut buf,
    mut link: *const buf,
    mut type_0: mkd_autolink,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    let mut offset: uint8_t = 0 as libc::c_int as uint8_t;
    if link.is_null() || (*link).size == 0 {
        return 0 as libc::c_int;
    }
    if (*options).flags & HTML_SAFELINK as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
        && sd_autolink_issafe((*link).data, (*link).size) == 0
        && type_0 as libc::c_uint != MKDA_EMAIL as libc::c_int as libc::c_uint
    {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<a href=\"\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if type_0 as libc::c_uint == MKDA_EMAIL as libc::c_int as libc::c_uint {
        bufput(
            ob,
            b"mailto:\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    escape_href(
        ob,
        ((*link).data).offset(offset as libc::c_int as isize),
        ((*link).size).wrapping_sub(offset as size_t),
    );
    if ((*options).link_attributes).is_some() {
        bufputc(ob, '"' as i32);
        ((*options).link_attributes)
            .expect("non-null function pointer")(ob, link, opaque);
        bufputc(ob, '>' as i32);
    } else {
        bufput(
            ob,
            b"\">\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 3]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    if bufprefix(link, b"mailto:\0" as *const u8 as *const libc::c_char)
        == 0 as libc::c_int
    {
        escape_html(
            ob,
            ((*link).data).offset(7 as libc::c_int as isize),
            ((*link).size).wrapping_sub(7 as libc::c_int as size_t),
        );
    } else {
        escape_html(ob, (*link).data, (*link).size);
    }
    bufput(
        ob,
        b"</a>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 5]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_blockcode(
    mut ob: *mut buf,
    mut text: *const buf,
    mut lang: *const buf,
    mut opaque: *mut libc::c_void,
) {
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    if !lang.is_null() && (*lang).size != 0 {
        let mut i: size_t = 0;
        let mut cls: size_t = 0;
        bufput(
            ob,
            b"<pre><code class=\"\0" as *const u8 as *const libc::c_char
                as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 19]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        i = 0 as libc::c_int as size_t;
        cls = 0 as libc::c_int as size_t;
        while i < (*lang).size {
            while i < (*lang).size
                && *(*__ctype_b_loc())
                    .offset(*((*lang).data).offset(i as isize) as libc::c_int as isize)
                    as libc::c_int
                    & _ISspace as libc::c_int as libc::c_ushort as libc::c_int != 0
            {
                i = i.wrapping_add(1);
                i;
            }
            if i < (*lang).size {
                let mut org: size_t = i;
                while i < (*lang).size
                    && *(*__ctype_b_loc())
                        .offset(
                            *((*lang).data).offset(i as isize) as libc::c_int as isize,
                        ) as libc::c_int
                        & _ISspace as libc::c_int as libc::c_ushort as libc::c_int == 0
                {
                    i = i.wrapping_add(1);
                    i;
                }
                if *((*lang).data).offset(org as isize) as libc::c_int == '.' as i32 {
                    org = org.wrapping_add(1);
                    org;
                }
                if cls != 0 {
                    bufputc(ob, ' ' as i32);
                }
                escape_html(
                    ob,
                    ((*lang).data).offset(org as isize),
                    i.wrapping_sub(org),
                );
            }
            i = i.wrapping_add(1);
            i;
            cls = cls.wrapping_add(1);
            cls;
        }
        bufput(
            ob,
            b"\">\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 3]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    } else {
        bufput(
            ob,
            b"<pre><code>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 12]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    if !text.is_null() {
        escape_html(ob, (*text).data, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</code></pre>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 15]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_blockquote(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) {
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(
        ob,
        b"<blockquote>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 14]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</blockquote>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 15]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_blockspoiler(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) {
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(
        ob,
        b"<blockquote class=\"md-spoiler-text\">\n\0" as *const u8 as *const libc::c_char
            as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 38]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</blockquote>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 15]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_codespan(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    bufput(
        ob,
        b"<code>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !text.is_null() {
        escape_html(ob, (*text).data, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</code>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_spoilerspan(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if text.is_null() || (*text).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<span class=\"md-spoiler-text\">\0" as *const u8 as *const libc::c_char
            as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 31]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    bufput(
        ob,
        b"</span>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_strikethrough(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if text.is_null() || (*text).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<del>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    bufput(
        ob,
        b"</del>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_double_emphasis(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if text.is_null() || (*text).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<strong>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    bufput(
        ob,
        b"</strong>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_emphasis(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if text.is_null() || (*text).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<em>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 5]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</em>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_linebreak(
    mut ob: *mut buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    bufputs(
        ob,
        if (*options).flags & HTML_USE_XHTML as libc::c_int as libc::c_uint != 0 {
            b"<br/>\n\0" as *const u8 as *const libc::c_char
        } else {
            b"<br>\n\0" as *const u8 as *const libc::c_char
        },
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_header(
    mut ob: *mut buf,
    mut text: *const buf,
    mut level: libc::c_int,
    mut opaque: *mut libc::c_void,
) {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    if (*options).flags & HTML_TOC as libc::c_int as libc::c_uint != 0 {
        bufprintf(ob, b"<h%d id=\"\0" as *const u8 as *const libc::c_char, level);
        if !((*options).toc_id_prefix).is_null() {
            bufputs(ob, (*options).toc_id_prefix);
        }else { std::intrinsics::assume(((*options).toc_id_prefix).addr() == 0); }
        let fresh0 = (*options).toc_data.header_count;
        (*options).toc_data.header_count = (*options).toc_data.header_count + 1;
        bufprintf(ob, b"toc_%d\">\0" as *const u8 as *const libc::c_char, fresh0);
    } else {
        bufprintf(ob, b"<h%d>\0" as *const u8 as *const libc::c_char, level);
    }
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufprintf(ob, b"</h%d>\n\0" as *const u8 as *const libc::c_char, level);
}
unsafe extern "C" fn rndr_link(
    mut ob: *mut buf,
    mut link: *const buf,
    mut title: *const buf,
    mut content: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    if !link.is_null()
        && (*options).flags & HTML_SAFELINK as libc::c_int as libc::c_uint
            != 0 as libc::c_int as libc::c_uint
        && sd_autolink_issafe((*link).data, (*link).size) == 0
    {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<a href=\"\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !link.is_null() && (*link).size != 0 {
        escape_href(ob, (*link).data, (*link).size);
    }
    if !title.is_null() && (*title).size != 0 {
        bufput(
            ob,
            b"\" title=\"\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        escape_html(ob, (*title).data, (*title).size);
    }
    if ((*options).link_attributes).is_some() {
        bufputc(ob, '"' as i32);
        ((*options).link_attributes)
            .expect("non-null function pointer")(ob, link, opaque);
        bufputc(ob, '>' as i32);
    } else {
        bufput(
            ob,
            b"\">\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 3]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    if !content.is_null() && (*content).size != 0 {
        bufput(ob, (*content).data as *const libc::c_void, (*content).size);
    }
    bufput(
        ob,
        b"</a>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 5]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_list(
    mut ob: *mut buf,
    mut text: *const buf,
    mut flags: libc::c_int,
    mut opaque: *mut libc::c_void,
) {
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(
        ob,
        (if flags & 1 as libc::c_int != 0 {
            b"<ol>\n\0" as *const u8 as *const libc::c_char
        } else {
            b"<ul>\n\0" as *const u8 as *const libc::c_char
        }) as *const libc::c_void,
        5 as libc::c_int as size_t,
    );
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        (if flags & 1 as libc::c_int != 0 {
            b"</ol>\n\0" as *const u8 as *const libc::c_char
        } else {
            b"</ul>\n\0" as *const u8 as *const libc::c_char
        }) as *const libc::c_void,
        6 as libc::c_int as size_t,
    );
}
unsafe extern "C" fn rndr_listitem(
    mut ob: *mut buf,
    mut text: *const buf,
    mut flags: libc::c_int,
    mut opaque: *mut libc::c_void,
) {
    bufput(
        ob,
        b"<li>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 5]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !text.is_null() {
        let mut size: size_t = (*text).size;
        while size != 0
            && *((*text).data)
                .offset(size.wrapping_sub(1 as libc::c_int as size_t) as isize)
                as libc::c_int == '\n' as i32
        {
            size = size.wrapping_sub(1);
            size;
        }
        bufput(ob, (*text).data as *const libc::c_void, size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</li>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_paragraph(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    let mut i: size_t = 0 as libc::c_int as size_t;
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    if text.is_null() || (*text).size == 0 {
        return;
    }
    while i < (*text).size
        && *(*__ctype_b_loc())
            .offset(*((*text).data).offset(i as isize) as libc::c_int as isize)
            as libc::c_int & _ISspace as libc::c_int as libc::c_ushort as libc::c_int
            != 0
    {
        i = i.wrapping_add(1);
        i;
    }
    if i == (*text).size {
        return;
    }
    bufput(
        ob,
        b"<p>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if (*options).flags & HTML_HARD_WRAP as libc::c_int as libc::c_uint != 0 {
        let mut org: size_t = 0;
        while i < (*text).size {
            org = i;
            while i < (*text).size
                && *((*text).data).offset(i as isize) as libc::c_int != '\n' as i32
            {
                i = i.wrapping_add(1);
                i;
            }
            if i > org {
                bufput(
                    ob,
                    ((*text).data).offset(org as isize) as *const libc::c_void,
                    i.wrapping_sub(org),
                );
            }
            if i >= ((*text).size).wrapping_sub(1 as libc::c_int as size_t) {
                break;
            }
            rndr_linebreak(ob, opaque);
            i = i.wrapping_add(1);
            i;
        }
    } else {
        bufput(
            ob,
            &mut *((*text).data).offset(i as isize) as *mut uint8_t
                as *const libc::c_void,
            ((*text).size).wrapping_sub(i),
        );
    }
    bufput(
        ob,
        b"</p>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_raw_block(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) {
    let mut org: size_t = 0;
    let mut sz: size_t = 0;
    if text.is_null() {std::intrinsics::assume((text).addr() == 0);
        return;
    }
    sz = (*text).size;
    while sz > 0 as libc::c_int as size_t
        && *((*text).data).offset(sz.wrapping_sub(1 as libc::c_int as size_t) as isize)
            as libc::c_int == '\n' as i32
    {
        sz = sz.wrapping_sub(1);
        sz;
    }
    org = 0 as libc::c_int as size_t;
    while org < sz && *((*text).data).offset(org as isize) as libc::c_int == '\n' as i32
    {
        org = org.wrapping_add(1);
        org;
    }
    if org >= sz {
        return;
    }
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(
        ob,
        ((*text).data).offset(org as isize) as *const libc::c_void,
        sz.wrapping_sub(org),
    );
    bufputc(ob, '\n' as i32);
}
unsafe extern "C" fn rndr_triple_emphasis(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if text.is_null() || (*text).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<strong><em>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 13]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    bufput(
        ob,
        b"</em></strong>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 15]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_hrule(mut ob: *mut buf, mut opaque: *mut libc::c_void) {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    bufputs(
        ob,
        if (*options).flags & HTML_USE_XHTML as libc::c_int as libc::c_uint != 0 {
            b"<hr/>\n\0" as *const u8 as *const libc::c_char
        } else {
            b"<hr>\n\0" as *const u8 as *const libc::c_char
        },
    );
}
unsafe extern "C" fn rndr_image(
    mut ob: *mut buf,
    mut link: *const buf,
    mut title: *const buf,
    mut alt: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    if link.is_null() || (*link).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<img src=\"\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 11]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    escape_href(ob, (*link).data, (*link).size);
    bufput(
        ob,
        b"\" alt=\"\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !alt.is_null() && (*alt).size != 0 {
        escape_html(ob, (*alt).data, (*alt).size);
    }
    if !title.is_null() && (*title).size != 0 {
        bufput(
            ob,
            b"\" title=\"\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 10]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        escape_html(ob, (*title).data, (*title).size);
    }
    bufputs(
        ob,
        if (*options).flags & HTML_USE_XHTML as libc::c_int as libc::c_uint != 0 {
            b"\"/>\0" as *const u8 as *const libc::c_char
        } else {
            b"\">\0" as *const u8 as *const libc::c_char
        },
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_html_tag(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
    mut tagname: *mut libc::c_char,
    mut whitelist: *mut *mut libc::c_char,
    mut tagtype: libc::c_int,
) {
    let mut i: size_t = 0;
    let mut x: size_t = 0;
    let mut z: size_t = 0;
    let mut in_str: size_t = 0 as libc::c_int as size_t;
    let mut seen_equals: size_t = 0 as libc::c_int as size_t;
    let mut done: size_t = 0 as libc::c_int as size_t;
    let mut done_attr: size_t = 0 as libc::c_int as size_t;
    let mut reset: size_t = 0 as libc::c_int as size_t;
    let mut attr: *mut buf = 0 as *mut buf;
    let mut value: *mut buf = 0 as *mut buf;
    let mut c: libc::c_char = 0;
    bufputc(ob, '<' as i32);
    if tagtype == HTML_TAG_CLOSE as libc::c_int {
        bufputc(ob, '/' as i32);
        bufputs(ob, tagname);
        bufputc(ob, '>' as i32);
        return;
    }
    bufputs(ob, tagname);
    i = (1 as libc::c_int as libc::c_ulong).wrapping_add(strlen(tagname));
    attr = bufnew(16 as libc::c_int as size_t);
    value = bufnew(16 as libc::c_int as size_t);
    while i < (*text).size && done == 0 {
        c = *((*text).data).offset(i as isize) as libc::c_char;
        done = 0 as libc::c_int as size_t;
        reset = 0 as libc::c_int as size_t;
        done_attr = 0 as libc::c_int as size_t;
        match c as libc::c_int {
            62 => {
                done = 1 as libc::c_int as size_t;
            }
            39 | 34 => {
                if seen_equals == 0 {
                    reset = 1 as libc::c_int as size_t;
                } else if in_str == 0 {
                    in_str = c as size_t;
                } else if in_str == c as size_t {
                    in_str = 0 as libc::c_int as size_t;
                    done_attr = 1 as libc::c_int as size_t;
                } else {
                    bufputc(value, c as libc::c_int);
                }
            }
            32 => {
                if in_str != 0 {
                    bufputc(value, ' ' as i32);
                } else {
                    reset = 1 as libc::c_int as size_t;
                }
            }
            61 => {
                if seen_equals != 0 {
                    reset = 1 as libc::c_int as size_t;
                } else {
                    seen_equals = 1 as libc::c_int as size_t;
                }
            }
            _ => {
                if seen_equals != 0 && in_str != 0 || seen_equals == 0 {
                    bufputc(
                        if seen_equals != 0 { value } else { attr },
                        c as libc::c_int,
                    );
                }
            }
        }
        if done_attr != 0 {
            let mut valid: libc::c_int = 0 as libc::c_int;
            z = 0 as libc::c_int as size_t;
            while !(*whitelist.offset(z as isize)).is_null() {
                if !(strlen(*whitelist.offset(z as isize)) != (*attr).size) {
                    x = 0 as libc::c_int as size_t;
                    while x < (*attr).size {
                        if ({
                            let mut __res: libc::c_int = 0;
                            if ::core::mem::size_of::<libc::c_char>() as libc::c_ulong
                                > 1 as libc::c_int as libc::c_ulong
                            {
                                if 0 != 0 {
                                    let mut __c: libc::c_int = *(*whitelist.offset(z as isize))
                                        .offset(x as isize) as libc::c_int;
                                    __res = (if __c < -(128 as libc::c_int)
                                        || __c > 255 as libc::c_int
                                    {
                                        __c
                                    } else {
                                        *(*__ctype_tolower_loc()).offset(__c as isize)
                                    });
                                } else {
                                    __res = tolower(
                                        *(*whitelist.offset(z as isize)).offset(x as isize)
                                            as libc::c_int,
                                    );
                                }
                            } else {
                                __res = *(*__ctype_tolower_loc())
                                    .offset(
                                        *(*whitelist.offset(z as isize)).offset(x as isize)
                                            as libc::c_int as isize,
                                    );
                            }
                            __res
                        })
                            != ({
                                let mut __res: libc::c_int = 0;
                                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                                    > 1 as libc::c_int as libc::c_ulong
                                {
                                    if 0 != 0 {
                                        let mut __c: libc::c_int = *((*attr).data)
                                            .offset(x as isize) as libc::c_int;
                                        __res = (if __c < -(128 as libc::c_int)
                                            || __c > 255 as libc::c_int
                                        {
                                            __c
                                        } else {
                                            *(*__ctype_tolower_loc()).offset(__c as isize)
                                        });
                                    } else {
                                        __res = tolower(
                                            *((*attr).data).offset(x as isize) as libc::c_int,
                                        );
                                    }
                                } else {
                                    __res = *(*__ctype_tolower_loc())
                                        .offset(
                                            *((*attr).data).offset(x as isize) as libc::c_int as isize,
                                        );
                                }
                                __res
                            })
                        {
                            break;
                        }
                        x = x.wrapping_add(1);
                        x;
                    }
                    if x == (*attr).size {
                        valid = 1 as libc::c_int;
                        break;
                    }
                }
                z = z.wrapping_add(1);
                z;
            }std::intrinsics::assume((*whitelist.offset(z as isize)).addr() == 0);
            if valid != 0 && (*value).size != 0 && (*attr).size != 0 {
                bufputc(ob, ' ' as i32);
                escape_html(ob, (*attr).data, (*attr).size);
                bufputs(ob, b"=\"\0" as *const u8 as *const libc::c_char);
                escape_html(ob, (*value).data, (*value).size);
                bufputc(ob, '"' as i32);
            }
            reset = 1 as libc::c_int as size_t;
        }
        if reset != 0 {
            seen_equals = 0 as libc::c_int as size_t;
            in_str = 0 as libc::c_int as size_t;
            bufreset(attr);
            bufreset(value);
        }
        i = i.wrapping_add(1);
        i;
    }
    bufrelease(attr);
    bufrelease(value);
    bufputc(ob, '>' as i32);
}
unsafe extern "C" fn rndr_raw_html(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    let mut whitelist: *mut *mut libc::c_char = (*options).html_element_whitelist;
    let mut i: libc::c_int = 0;
    let mut tagtype: libc::c_int = 0;
    if (*options).flags & HTML_ALLOW_ELEMENT_WHITELIST as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint && !whitelist.is_null()
    {
        i = 0 as libc::c_int;
        while !(*whitelist.offset(i as isize)).is_null() {
            tagtype = sdhtml_is_tag(
                (*text).data,
                (*text).size,
                *whitelist.offset(i as isize),
            );
            if tagtype != HTML_TAG_NONE as libc::c_int {
                rndr_html_tag(
                    ob,
                    text,
                    opaque,
                    *whitelist.offset(i as isize),
                    (*options).html_attr_whitelist,
                    tagtype,
                );
                return 1 as libc::c_int;
            }
            i += 1;
            i;
        }std::intrinsics::assume((*whitelist.offset(i as isize)).addr() == 0);
    }
    if (*options).flags & HTML_ESCAPE as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        escape_html(ob, (*text).data, (*text).size);
        return 1 as libc::c_int;
    }
    if (*options).flags & HTML_SKIP_HTML as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
    {
        return 1 as libc::c_int;
    }
    if (*options).flags & HTML_SKIP_STYLE as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
        && sdhtml_is_tag(
            (*text).data,
            (*text).size,
            b"style\0" as *const u8 as *const libc::c_char,
        ) != 0
    {
        return 1 as libc::c_int;
    }
    if (*options).flags & HTML_SKIP_LINKS as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
        && sdhtml_is_tag(
            (*text).data,
            (*text).size,
            b"a\0" as *const u8 as *const libc::c_char,
        ) != 0
    {
        return 1 as libc::c_int;
    }
    if (*options).flags & HTML_SKIP_IMAGES as libc::c_int as libc::c_uint
        != 0 as libc::c_int as libc::c_uint
        && sdhtml_is_tag(
            (*text).data,
            (*text).size,
            b"img\0" as *const u8 as *const libc::c_char,
        ) != 0
    {
        return 1 as libc::c_int;
    }
    bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_table(
    mut ob: *mut buf,
    mut header: *const buf,
    mut body: *const buf,
    mut opaque: *mut libc::c_void,
) {
    if (*ob).size != 0 {
        bufputc(ob, '\n' as i32);
    }
    bufput(
        ob,
        b"<table><thead>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 16]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !header.is_null() {
        bufput(ob, (*header).data as *const libc::c_void, (*header).size);
    }else { std::intrinsics::assume((header).addr() == 0); }
    bufput(
        ob,
        b"</thead><tbody>\n\0" as *const u8 as *const libc::c_char
            as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 17]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !body.is_null() {
        bufput(ob, (*body).data as *const libc::c_void, (*body).size);
    }else { std::intrinsics::assume((body).addr() == 0); }
    bufput(
        ob,
        b"</tbody></table>\n\0" as *const u8 as *const libc::c_char
            as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 18]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_tablerow(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) {
    bufput(
        ob,
        b"<tr>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</tr>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn rndr_tablecell(
    mut ob: *mut buf,
    mut text: *const buf,
    mut flags: libc::c_int,
    mut opaque: *mut libc::c_void,
    mut col_span: libc::c_int,
) {
    if flags & MKD_TABLE_HEADER as libc::c_int != 0 {
        bufput(
            ob,
            b"<th\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    } else {
        bufput(
            ob,
            b"<td\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    if col_span > 1 as libc::c_int {
        bufprintf(
            ob,
            b" colspan=\"%d\" \0" as *const u8 as *const libc::c_char,
            col_span,
        );
    }
    match flags & MKD_TABLE_ALIGNMASK as libc::c_int {
        3 => {
            bufput(
                ob,
                b" align=\"center\">\0" as *const u8 as *const libc::c_char
                    as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 17]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
        }
        1 => {
            bufput(
                ob,
                b" align=\"left\">\0" as *const u8 as *const libc::c_char
                    as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 15]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
        }
        2 => {
            bufput(
                ob,
                b" align=\"right\">\0" as *const u8 as *const libc::c_char
                    as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 16]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
        }
        _ => {
            bufput(
                ob,
                b">\0" as *const u8 as *const libc::c_char as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 2]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
        }
    }
    if !text.is_null() {
        bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    if flags & MKD_TABLE_HEADER as libc::c_int != 0 {
        bufput(
            ob,
            b"</th>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    } else {
        bufput(
            ob,
            b"</td>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    };
}
unsafe extern "C" fn rndr_superscript(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if text.is_null() || (*text).size == 0 {
        return 0 as libc::c_int;
    }
    bufput(
        ob,
        b"<sup>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    bufput(ob, (*text).data as *const libc::c_void, (*text).size);
    bufput(
        ob,
        b"</sup>\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    return 1 as libc::c_int;
}
unsafe extern "C" fn rndr_normal_text(
    mut ob: *mut buf,
    mut text: *const buf,
    mut opaque: *mut libc::c_void,
) {
    if !text.is_null() {
        escape_html(ob, (*text).data, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
}
unsafe extern "C" fn toc_header(
    mut ob: *mut buf,
    mut text: *const buf,
    mut level: libc::c_int,
    mut opaque: *mut libc::c_void,
) {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    if (*options).toc_data.current_level == 0 as libc::c_int {
        bufput(
            ob,
            b"<div class=\"toc\">\n\0" as *const u8 as *const libc::c_char
                as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 19]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        (*options).toc_data.level_offset = level - 1 as libc::c_int;
    }
    level -= (*options).toc_data.level_offset;
    if level > (*options).toc_data.current_level {
        while level > (*options).toc_data.current_level {
            bufput(
                ob,
                b"<ul>\n<li>\n\0" as *const u8 as *const libc::c_char
                    as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 11]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
            (*options).toc_data.current_level += 1;
            (*options).toc_data.current_level;
        }
    } else if level < (*options).toc_data.current_level {
        bufput(
            ob,
            b"</li>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        while level < (*options).toc_data.current_level {
            bufput(
                ob,
                b"</ul>\n</li>\n\0" as *const u8 as *const libc::c_char
                    as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 13]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
            (*options).toc_data.current_level -= 1;
            (*options).toc_data.current_level;
        }
        bufput(
            ob,
            b"<li>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    } else {
        bufput(
            ob,
            b"</li>\n<li>\n\0" as *const u8 as *const libc::c_char
                as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 12]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    bufput(
        ob,
        b"<a href=\"#\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 11]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
    if !((*options).toc_id_prefix).is_null() {
        bufputs(ob, (*options).toc_id_prefix);
    }else { std::intrinsics::assume(((*options).toc_id_prefix).addr() == 0); }
    let fresh1 = (*options).toc_data.header_count;
    (*options).toc_data.header_count = (*options).toc_data.header_count + 1;
    bufprintf(ob, b"toc_%d\">\0" as *const u8 as *const libc::c_char, fresh1);
    if !text.is_null() {
        escape_html(ob, (*text).data, (*text).size);
    }else { std::intrinsics::assume((text).addr() == 0); }
    bufput(
        ob,
        b"</a>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
        (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong),
    );
}
unsafe extern "C" fn toc_link(
    mut ob: *mut buf,
    mut link: *const buf,
    mut title: *const buf,
    mut content: *const buf,
    mut opaque: *mut libc::c_void,
) -> libc::c_int {
    if !content.is_null() && (*content).size != 0 {
        bufput(ob, (*content).data as *const libc::c_void, (*content).size);
    }
    return 1 as libc::c_int;
}
unsafe extern "C" fn reset_toc(mut ob: *mut buf, mut opaque: *mut libc::c_void) {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    memset(
        &mut (*options).toc_data as *mut C2RustUnnamed as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<C2RustUnnamed>() as libc::c_ulong,
    );
}
unsafe extern "C" fn toc_finalize(mut ob: *mut buf, mut opaque: *mut libc::c_void) {
    let mut options: *mut html_renderopt = opaque as *mut html_renderopt;
    let mut has_toc: bool = 0 as libc::c_int != 0;
    while (*options).toc_data.current_level > 0 as libc::c_int {
        bufput(
            ob,
            b"</li>\n</ul>\n\0" as *const u8 as *const libc::c_char
                as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 13]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        (*options).toc_data.current_level -= 1;
        (*options).toc_data.current_level;
        has_toc = 1 as libc::c_int != 0;
    }
    if has_toc {
        bufput(
            ob,
            b"</div>\n\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    reset_toc(ob, opaque);
}
#[no_mangle]
pub unsafe extern "C" fn sdhtml_toc_renderer(
    mut callbacks: *mut sd_callbacks,
    mut options: *mut html_renderopt,
) {
    static mut cb_default: sd_callbacks = unsafe {
        {
            let mut init = sd_callbacks {
                blockcode: None,
                blockquote: None,
                blockspoiler: None,
                blockhtml: ::core::mem::transmute::<
                    Option::<
                        unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            libc::c_int,
                            *mut libc::c_void,
                        ) -> (),
                    >,
                    Option::<
                        unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                    >,
                >(
                    Some(
                        toc_header
                            as unsafe extern "C" fn(
                                *mut buf,
                                *const buf,
                                libc::c_int,
                                *mut libc::c_void,
                            ) -> (),
                    ),
                ),
                header: None,
                hrule: None,
                list: None,
                listitem: None,
                paragraph: None,
                table: None,
                table_row: None,
                table_cell: None,
                autolink: ::core::mem::transmute::<
                    Option::<
                        unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                    >,
                    Option::<
                        unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            mkd_autolink,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                    >,
                >(
                    Some(
                        rndr_codespan
                            as unsafe extern "C" fn(
                                *mut buf,
                                *const buf,
                                *mut libc::c_void,
                            ) -> libc::c_int,
                    ),
                ),
                codespan: Some(
                    rndr_spoilerspan
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                spoilerspan: Some(
                    rndr_double_emphasis
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                double_emphasis: Some(
                    rndr_emphasis
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                emphasis: None,
                image: None,
                linebreak: ::core::mem::transmute::<
                    Option::<
                        unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *const buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                    >,
                    Option::<
                        unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> libc::c_int,
                    >,
                >(
                    Some(
                        toc_link
                            as unsafe extern "C" fn(
                                *mut buf,
                                *const buf,
                                *const buf,
                                *const buf,
                                *mut libc::c_void,
                            ) -> libc::c_int,
                    ),
                ),
                link: None,
                raw_html_tag: Some(
                    rndr_triple_emphasis
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                triple_emphasis: Some(
                    rndr_strikethrough
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                strikethrough: Some(
                    rndr_superscript
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                superscript: None,
                entity: None,
                normal_text: None,
                doc_header: Some(
                    toc_finalize
                        as unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> (),
                ),
                doc_footer: None,
            };
            init
        }
    };
    memset(
        options as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<html_renderopt>() as libc::c_ulong,
    );
    (*options)
        .flags = (HTML_TOC as libc::c_int | HTML_SKIP_HTML as libc::c_int)
        as libc::c_uint;
    memcpy(
        callbacks as *mut libc::c_void,
        &cb_default as *const sd_callbacks as *const libc::c_void,
        ::core::mem::size_of::<sd_callbacks>() as libc::c_ulong,
    );
}
#[no_mangle]
pub unsafe extern "C" fn sdhtml_renderer(
    mut callbacks: *mut sd_callbacks,
    mut options: *mut html_renderopt,
    mut render_flags: libc::c_uint,
) {
    static mut cb_default: sd_callbacks = unsafe {
        {
            let mut init = sd_callbacks {
                blockcode: Some(
                    rndr_blockcode
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                blockquote: Some(
                    rndr_blockquote
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                blockspoiler: Some(
                    rndr_blockspoiler
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                blockhtml: Some(
                    rndr_raw_block
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                header: Some(
                    rndr_header
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            libc::c_int,
                            *mut libc::c_void,
                        ) -> (),
                ),
                hrule: Some(
                    rndr_hrule as unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> (),
                ),
                list: Some(
                    rndr_list
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            libc::c_int,
                            *mut libc::c_void,
                        ) -> (),
                ),
                listitem: Some(
                    rndr_listitem
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            libc::c_int,
                            *mut libc::c_void,
                        ) -> (),
                ),
                paragraph: Some(
                    rndr_paragraph
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                table: Some(
                    rndr_table
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                table_row: Some(
                    rndr_tablerow
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                table_cell: Some(
                    rndr_tablecell
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            libc::c_int,
                            *mut libc::c_void,
                            libc::c_int,
                        ) -> (),
                ),
                autolink: Some(
                    rndr_autolink
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            mkd_autolink,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                codespan: Some(
                    rndr_codespan
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                spoilerspan: Some(
                    rndr_spoilerspan
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                double_emphasis: Some(
                    rndr_double_emphasis
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                emphasis: Some(
                    rndr_emphasis
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                image: Some(
                    rndr_image
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *const buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                linebreak: Some(
                    rndr_linebreak
                        as unsafe extern "C" fn(
                            *mut buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                link: Some(
                    rndr_link
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *const buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                raw_html_tag: Some(
                    rndr_raw_html
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                triple_emphasis: Some(
                    rndr_triple_emphasis
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                strikethrough: Some(
                    rndr_strikethrough
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                superscript: Some(
                    rndr_superscript
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> libc::c_int,
                ),
                entity: None,
                normal_text: Some(
                    rndr_normal_text
                        as unsafe extern "C" fn(
                            *mut buf,
                            *const buf,
                            *mut libc::c_void,
                        ) -> (),
                ),
                doc_header: None,
                doc_footer: Some(
                    reset_toc as unsafe extern "C" fn(*mut buf, *mut libc::c_void) -> (),
                ),
            };
            init
        }
    };
    memset(
        options as *mut libc::c_void,
        0 as libc::c_int,
        ::core::mem::size_of::<html_renderopt>() as libc::c_ulong,
    );
    (*options).flags = render_flags;
    memcpy(
        callbacks as *mut libc::c_void,
        &cb_default as *const sd_callbacks as *const libc::c_void,
        ::core::mem::size_of::<sd_callbacks>() as libc::c_ulong,
    );
    if render_flags & HTML_SKIP_IMAGES as libc::c_int as libc::c_uint != 0 {
        (*callbacks).image = None;
    }
    if render_flags & HTML_SKIP_LINKS as libc::c_int as libc::c_uint != 0 {
        (*callbacks).link = None;
        (*callbacks).autolink = None;
    }
    if render_flags & HTML_SKIP_HTML as libc::c_int as libc::c_uint != 0
        || render_flags & HTML_ESCAPE as libc::c_int as libc::c_uint != 0
    {
        (*callbacks).blockhtml = None;
    }
}
