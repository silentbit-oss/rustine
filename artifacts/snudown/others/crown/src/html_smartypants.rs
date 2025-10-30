use ::libc;
extern "C" {
    fn bufgrow(_: *mut buf, _: size_t) -> libc::c_int;
    fn bufput(_: *mut buf, _: *const libc::c_void, _: size_t);
    fn bufputs(_: *mut buf, _: *const libc::c_char);
    fn bufputc(_: *mut buf, _: libc::c_int);
    fn sdhtml_is_tag(
        tag_data: *const uint8_t,
        tag_size: size_t,
        tagname: *const libc::c_char,
    ) -> libc::c_int;
    fn memcmp(
        _: *const libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn snprintf(
        _: *mut libc::c_char,
        _: libc::c_ulong,
        _: *const libc::c_char,
        _: ...
    ) -> libc::c_int;
    fn __ctype_b_loc() -> *mut *const libc::c_ushort;
    fn __ctype_tolower_loc() -> *mut *const __int32_t;
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
pub type C2RustUnnamed = libc::c_uint;
pub const HTML_TAG_CLOSE: C2RustUnnamed = 2;
pub const HTML_TAG_OPEN: C2RustUnnamed = 1;
pub const HTML_TAG_NONE: C2RustUnnamed = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct smartypants_data {
    pub in_squote: libc::c_int,
    pub in_dquote: libc::c_int,
}
pub const _ISpunct: C2RustUnnamed_0 = 4;
pub const _ISspace: C2RustUnnamed_0 = 8192;
pub type C2RustUnnamed_0 = libc::c_uint;
pub const _ISalnum: C2RustUnnamed_0 = 8;
pub const _IScntrl: C2RustUnnamed_0 = 2;
pub const _ISblank: C2RustUnnamed_0 = 1;
pub const _ISgraph: C2RustUnnamed_0 = 32768;
pub const _ISprint: C2RustUnnamed_0 = 16384;
pub const _ISxdigit: C2RustUnnamed_0 = 4096;
pub const _ISdigit: C2RustUnnamed_0 = 2048;
pub const _ISalpha: C2RustUnnamed_0 = 1024;
pub const _ISlower: C2RustUnnamed_0 = 512;
pub const _ISupper: C2RustUnnamed_0 = 256;
#[inline]
unsafe extern "C" fn tolower(mut __c: libc::c_int) -> libc::c_int {
    return if __c >= -(128 as libc::c_int) && __c < 256 as libc::c_int {
        *(*__ctype_tolower_loc()).offset(__c as isize)
    } else {
        __c
    };
}
static mut smartypants_cb_ptrs: [Option::<
    unsafe extern "C" fn(
        *mut buf,
        *mut smartypants_data,
        uint8_t,
        *const uint8_t,
        size_t,
    ) -> size_t,
>; 11] = unsafe {
    [
        None,
        Some(
            smartypants_cb__dash
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__parens
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__squote
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__dquote
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__amp
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__period
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__number
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__ltag
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__backtick
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
        Some(
            smartypants_cb__escape
                as unsafe extern "C" fn(
                    *mut buf,
                    *mut smartypants_data,
                    uint8_t,
                    *const uint8_t,
                    size_t,
                ) -> size_t,
        ),
    ]
};
static mut smartypants_cb_chars: [uint8_t; 256] = [
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    4 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    5 as libc::c_int as uint8_t,
    3 as libc::c_int as uint8_t,
    2 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    1 as libc::c_int as uint8_t,
    6 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    7 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    7 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    8 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    10 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    9 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
    0 as libc::c_int as uint8_t,
];
#[inline]
unsafe extern "C" fn word_boundary(mut c: uint8_t) -> libc::c_int {
    return (c as libc::c_int == 0 as libc::c_int
        || *(*__ctype_b_loc()).offset(c as libc::c_int as isize) as libc::c_int
            & _ISspace as libc::c_int as libc::c_ushort as libc::c_int != 0
        || *(*__ctype_b_loc()).offset(c as libc::c_int as isize) as libc::c_int
            & _ISpunct as libc::c_int as libc::c_ushort as libc::c_int != 0)
        as libc::c_int;
}
unsafe extern "C" fn smartypants_quotes(
    mut ob: *mut buf,
    mut previous_char: uint8_t,
    mut next_char: uint8_t,
    mut quote: uint8_t,
    mut is_open: *mut libc::c_int,
) -> libc::c_int {
    let mut ent: [libc::c_char; 8] = [0; 8];
    if *is_open != 0 && word_boundary(next_char) == 0 {
        return 0 as libc::c_int;
    }
    if *is_open == 0 && word_boundary(previous_char) == 0 {
        return 0 as libc::c_int;
    }
    snprintf(
        ent.as_mut_ptr(),
        ::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong,
        b"&%c%cquo;\0" as *const u8 as *const libc::c_char,
        if *is_open != 0 { 'r' as i32 } else { 'l' as i32 },
        quote as libc::c_int,
    );
    *is_open = (*is_open == 0) as libc::c_int;
    bufputs(ob, ent.as_mut_ptr());
    return 1 as libc::c_int;
}
unsafe extern "C" fn smartypants_cb__squote(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size >= 2 as libc::c_int as size_t {
        let mut t1: uint8_t = ({
            let mut __res: libc::c_int = 0;
            if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                > 1 as libc::c_int as libc::c_ulong
            {
                if 0 != 0 {
                    let mut __c: libc::c_int = *text.offset(1 as libc::c_int as isize)
                        as libc::c_int;
                    __res = if __c < -(128 as libc::c_int) || __c > 255 as libc::c_int {
                        __c
                    } else {
                        *(*__ctype_tolower_loc()).offset(__c as isize)
                    };
                } else {
                    __res = tolower(
                        *text.offset(1 as libc::c_int as isize) as libc::c_int,
                    );
                }
            } else {
                __res = *(*__ctype_tolower_loc())
                    .offset(
                        *text.offset(1 as libc::c_int as isize) as libc::c_int as isize,
                    );
            }
            __res
        }) as uint8_t;
        if t1 as libc::c_int == '\'' as i32 {
            if smartypants_quotes(
                ob,
                previous_char,
                (if size >= 3 as libc::c_int as size_t {
                    *text.offset(2 as libc::c_int as isize) as libc::c_int
                } else {
                    0 as libc::c_int
                }) as uint8_t,
                'd' as i32 as uint8_t,
                &mut (*smrt).in_dquote,
            ) != 0
            {
                return 1 as libc::c_int as size_t;
            }
        }
        if (t1 as libc::c_int == 's' as i32 || t1 as libc::c_int == 't' as i32
            || t1 as libc::c_int == 'm' as i32 || t1 as libc::c_int == 'd' as i32)
            && (size == 3 as libc::c_int as size_t
                || word_boundary(*text.offset(2 as libc::c_int as isize)) != 0)
        {
            bufput(
                ob,
                b"&rsquo;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
            return 0 as libc::c_int as size_t;
        }
        if size >= 3 as libc::c_int as size_t {
            let mut t2: uint8_t = ({
                let mut __res: libc::c_int = 0;
                if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                    > 1 as libc::c_int as libc::c_ulong
                {
                    if 0 != 0 {
                        let mut __c: libc::c_int = *text
                            .offset(2 as libc::c_int as isize) as libc::c_int;
                        __res = if __c < -(128 as libc::c_int)
                            || __c > 255 as libc::c_int
                        {
                            __c
                        } else {
                            *(*__ctype_tolower_loc()).offset(__c as isize)
                        };
                    } else {
                        __res = tolower(
                            *text.offset(2 as libc::c_int as isize) as libc::c_int,
                        );
                    }
                } else {
                    __res = *(*__ctype_tolower_loc())
                        .offset(
                            *text.offset(2 as libc::c_int as isize) as libc::c_int
                                as isize,
                        );
                }
                __res
            }) as uint8_t;
            if (t1 as libc::c_int == 'r' as i32 && t2 as libc::c_int == 'e' as i32
                || t1 as libc::c_int == 'l' as i32 && t2 as libc::c_int == 'l' as i32
                || t1 as libc::c_int == 'v' as i32 && t2 as libc::c_int == 'e' as i32)
                && (size == 4 as libc::c_int as size_t
                    || word_boundary(*text.offset(3 as libc::c_int as isize)) != 0)
            {
                bufput(
                    ob,
                    b"&rsquo;\0" as *const u8 as *const libc::c_char
                        as *const libc::c_void,
                    (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                        .wrapping_sub(1 as libc::c_int as libc::c_ulong),
                );
                return 0 as libc::c_int as size_t;
            }
        }
    }
    if smartypants_quotes(
        ob,
        previous_char,
        (if size > 0 as libc::c_int as size_t {
            *text.offset(1 as libc::c_int as isize) as libc::c_int
        } else {
            0 as libc::c_int
        }) as uint8_t,
        's' as i32 as uint8_t,
        &mut (*smrt).in_squote,
    ) != 0
    {
        return 0 as libc::c_int as size_t;
    }
    bufputc(ob, *text.offset(0 as libc::c_int as isize) as libc::c_int);
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__parens(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size >= 3 as libc::c_int as size_t {
        let mut t1: uint8_t = ({
            let mut __res: libc::c_int = 0;
            if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                > 1 as libc::c_int as libc::c_ulong
            {
                if 0 != 0 {
                    let mut __c: libc::c_int = *text.offset(1 as libc::c_int as isize)
                        as libc::c_int;
                    __res = if __c < -(128 as libc::c_int) || __c > 255 as libc::c_int {
                        __c
                    } else {
                        *(*__ctype_tolower_loc()).offset(__c as isize)
                    };
                } else {
                    __res = tolower(
                        *text.offset(1 as libc::c_int as isize) as libc::c_int,
                    );
                }
            } else {
                __res = *(*__ctype_tolower_loc())
                    .offset(
                        *text.offset(1 as libc::c_int as isize) as libc::c_int as isize,
                    );
            }
            __res
        }) as uint8_t;
        let mut t2: uint8_t = ({
            let mut __res: libc::c_int = 0;
            if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                > 1 as libc::c_int as libc::c_ulong
            {
                if 0 != 0 {
                    let mut __c: libc::c_int = *text.offset(2 as libc::c_int as isize)
                        as libc::c_int;
                    __res = if __c < -(128 as libc::c_int) || __c > 255 as libc::c_int {
                        __c
                    } else {
                        *(*__ctype_tolower_loc()).offset(__c as isize)
                    };
                } else {
                    __res = tolower(
                        *text.offset(2 as libc::c_int as isize) as libc::c_int,
                    );
                }
            } else {
                __res = *(*__ctype_tolower_loc())
                    .offset(
                        *text.offset(2 as libc::c_int as isize) as libc::c_int as isize,
                    );
            }
            __res
        }) as uint8_t;
        if t1 as libc::c_int == 'c' as i32 && t2 as libc::c_int == ')' as i32 {
            bufput(
                ob,
                b"&copy;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
            return 2 as libc::c_int as size_t;
        }
        if t1 as libc::c_int == 'r' as i32 && t2 as libc::c_int == ')' as i32 {
            bufput(
                ob,
                b"&reg;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
            return 2 as libc::c_int as size_t;
        }
        if size >= 4 as libc::c_int as size_t && t1 as libc::c_int == 't' as i32
            && t2 as libc::c_int == 'm' as i32
            && *text.offset(3 as libc::c_int as isize) as libc::c_int == ')' as i32
        {
            bufput(
                ob,
                b"&trade;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
                (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                    .wrapping_sub(1 as libc::c_int as libc::c_ulong),
            );
            return 3 as libc::c_int as size_t;
        }
    }
    bufputc(ob, *text.offset(0 as libc::c_int as isize) as libc::c_int);
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__dash(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size >= 3 as libc::c_int as size_t
        && *text.offset(1 as libc::c_int as isize) as libc::c_int == '-' as i32
        && *text.offset(2 as libc::c_int as isize) as libc::c_int == '-' as i32
    {
        bufput(
            ob,
            b"&mdash;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        return 2 as libc::c_int as size_t;
    }
    if size >= 2 as libc::c_int as size_t
        && *text.offset(1 as libc::c_int as isize) as libc::c_int == '-' as i32
    {
        bufput(
            ob,
            b"&ndash;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 8]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        return 1 as libc::c_int as size_t;
    }
    bufputc(ob, *text.offset(0 as libc::c_int as isize) as libc::c_int);
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__amp(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size >= 6 as libc::c_int as size_t
        && memcmp(
            text as *const libc::c_void,
            b"&quot;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            6 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
    {
        if smartypants_quotes(
            ob,
            previous_char,
            (if size >= 7 as libc::c_int as size_t {
                *text.offset(6 as libc::c_int as isize) as libc::c_int
            } else {
                0 as libc::c_int
            }) as uint8_t,
            'd' as i32 as uint8_t,
            &mut (*smrt).in_dquote,
        ) != 0
        {
            return 5 as libc::c_int as size_t;
        }
    }
    if size >= 4 as libc::c_int as size_t
        && memcmp(
            text as *const libc::c_void,
            b"&#0;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
    {
        return 3 as libc::c_int as size_t;
    }
    bufputc(ob, '&' as i32);
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__period(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size >= 3 as libc::c_int as size_t
        && *text.offset(1 as libc::c_int as isize) as libc::c_int == '.' as i32
        && *text.offset(2 as libc::c_int as isize) as libc::c_int == '.' as i32
    {
        bufput(
            ob,
            b"&hellip;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        return 2 as libc::c_int as size_t;
    }
    if size >= 5 as libc::c_int as size_t
        && *text.offset(1 as libc::c_int as isize) as libc::c_int == ' ' as i32
        && *text.offset(2 as libc::c_int as isize) as libc::c_int == '.' as i32
        && *text.offset(3 as libc::c_int as isize) as libc::c_int == ' ' as i32
        && *text.offset(4 as libc::c_int as isize) as libc::c_int == '.' as i32
    {
        bufput(
            ob,
            b"&hellip;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
        return 4 as libc::c_int as size_t;
    }
    bufputc(ob, *text.offset(0 as libc::c_int as isize) as libc::c_int);
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__backtick(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size >= 2 as libc::c_int as size_t
        && *text.offset(1 as libc::c_int as isize) as libc::c_int == '`' as i32
    {
        if smartypants_quotes(
            ob,
            previous_char,
            (if size >= 3 as libc::c_int as size_t {
                *text.offset(2 as libc::c_int as isize) as libc::c_int
            } else {
                0 as libc::c_int
            }) as uint8_t,
            'd' as i32 as uint8_t,
            &mut (*smrt).in_dquote,
        ) != 0
        {
            return 1 as libc::c_int as size_t;
        }
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__number(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if word_boundary(previous_char) != 0 && size >= 3 as libc::c_int as size_t {
        if *text.offset(0 as libc::c_int as isize) as libc::c_int == '1' as i32
            && *text.offset(1 as libc::c_int as isize) as libc::c_int == '/' as i32
            && *text.offset(2 as libc::c_int as isize) as libc::c_int == '2' as i32
        {
            if size == 3 as libc::c_int as size_t
                || word_boundary(*text.offset(3 as libc::c_int as isize)) != 0
            {
                bufput(
                    ob,
                    b"&frac12;\0" as *const u8 as *const libc::c_char
                        as *const libc::c_void,
                    (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
                        .wrapping_sub(1 as libc::c_int as libc::c_ulong),
                );
                return 2 as libc::c_int as size_t;
            }
        }
        if *text.offset(0 as libc::c_int as isize) as libc::c_int == '1' as i32
            && *text.offset(1 as libc::c_int as isize) as libc::c_int == '/' as i32
            && *text.offset(2 as libc::c_int as isize) as libc::c_int == '4' as i32
        {
            if size == 3 as libc::c_int as size_t
                || word_boundary(*text.offset(3 as libc::c_int as isize)) != 0
                || size >= 5 as libc::c_int as size_t
                    && ({
                        let mut __res: libc::c_int = 0;
                        if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                            > 1 as libc::c_int as libc::c_ulong
                        {
                            if 0 != 0 {
                                let mut __c: libc::c_int = *text
                                    .offset(3 as libc::c_int as isize) as libc::c_int;
                                __res = (if __c < -(128 as libc::c_int)
                                    || __c > 255 as libc::c_int
                                {
                                    __c
                                } else {
                                    *(*__ctype_tolower_loc()).offset(__c as isize)
                                });
                            } else {
                                __res = tolower(
                                    *text.offset(3 as libc::c_int as isize) as libc::c_int,
                                );
                            }
                        } else {
                            __res = *(*__ctype_tolower_loc())
                                .offset(
                                    *text.offset(3 as libc::c_int as isize) as libc::c_int
                                        as isize,
                                );
                        }
                        __res
                    }) == 't' as i32
                    && ({
                        let mut __res: libc::c_int = 0;
                        if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                            > 1 as libc::c_int as libc::c_ulong
                        {
                            if 0 != 0 {
                                let mut __c: libc::c_int = *text
                                    .offset(4 as libc::c_int as isize) as libc::c_int;
                                __res = (if __c < -(128 as libc::c_int)
                                    || __c > 255 as libc::c_int
                                {
                                    __c
                                } else {
                                    *(*__ctype_tolower_loc()).offset(__c as isize)
                                });
                            } else {
                                __res = tolower(
                                    *text.offset(4 as libc::c_int as isize) as libc::c_int,
                                );
                            }
                        } else {
                            __res = *(*__ctype_tolower_loc())
                                .offset(
                                    *text.offset(4 as libc::c_int as isize) as libc::c_int
                                        as isize,
                                );
                        }
                        __res
                    }) == 'h' as i32
            {
                bufput(
                    ob,
                    b"&frac14;\0" as *const u8 as *const libc::c_char
                        as *const libc::c_void,
                    (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
                        .wrapping_sub(1 as libc::c_int as libc::c_ulong),
                );
                return 2 as libc::c_int as size_t;
            }
        }
        if *text.offset(0 as libc::c_int as isize) as libc::c_int == '3' as i32
            && *text.offset(1 as libc::c_int as isize) as libc::c_int == '/' as i32
            && *text.offset(2 as libc::c_int as isize) as libc::c_int == '4' as i32
        {
            if size == 3 as libc::c_int as size_t
                || word_boundary(*text.offset(3 as libc::c_int as isize)) != 0
                || size >= 6 as libc::c_int as size_t
                    && ({
                        let mut __res: libc::c_int = 0;
                        if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                            > 1 as libc::c_int as libc::c_ulong
                        {
                            if 0 != 0 {
                                let mut __c: libc::c_int = *text
                                    .offset(3 as libc::c_int as isize) as libc::c_int;
                                __res = (if __c < -(128 as libc::c_int)
                                    || __c > 255 as libc::c_int
                                {
                                    __c
                                } else {
                                    *(*__ctype_tolower_loc()).offset(__c as isize)
                                });
                            } else {
                                __res = tolower(
                                    *text.offset(3 as libc::c_int as isize) as libc::c_int,
                                );
                            }
                        } else {
                            __res = *(*__ctype_tolower_loc())
                                .offset(
                                    *text.offset(3 as libc::c_int as isize) as libc::c_int
                                        as isize,
                                );
                        }
                        __res
                    }) == 't' as i32
                    && ({
                        let mut __res: libc::c_int = 0;
                        if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                            > 1 as libc::c_int as libc::c_ulong
                        {
                            if 0 != 0 {
                                let mut __c: libc::c_int = *text
                                    .offset(4 as libc::c_int as isize) as libc::c_int;
                                __res = (if __c < -(128 as libc::c_int)
                                    || __c > 255 as libc::c_int
                                {
                                    __c
                                } else {
                                    *(*__ctype_tolower_loc()).offset(__c as isize)
                                });
                            } else {
                                __res = tolower(
                                    *text.offset(4 as libc::c_int as isize) as libc::c_int,
                                );
                            }
                        } else {
                            __res = *(*__ctype_tolower_loc())
                                .offset(
                                    *text.offset(4 as libc::c_int as isize) as libc::c_int
                                        as isize,
                                );
                        }
                        __res
                    }) == 'h' as i32
                    && ({
                        let mut __res: libc::c_int = 0;
                        if ::core::mem::size_of::<uint8_t>() as libc::c_ulong
                            > 1 as libc::c_int as libc::c_ulong
                        {
                            if 0 != 0 {
                                let mut __c: libc::c_int = *text
                                    .offset(5 as libc::c_int as isize) as libc::c_int;
                                __res = (if __c < -(128 as libc::c_int)
                                    || __c > 255 as libc::c_int
                                {
                                    __c
                                } else {
                                    *(*__ctype_tolower_loc()).offset(__c as isize)
                                });
                            } else {
                                __res = tolower(
                                    *text.offset(5 as libc::c_int as isize) as libc::c_int,
                                );
                            }
                        } else {
                            __res = *(*__ctype_tolower_loc())
                                .offset(
                                    *text.offset(5 as libc::c_int as isize) as libc::c_int
                                        as isize,
                                );
                        }
                        __res
                    }) == 's' as i32
            {
                bufput(
                    ob,
                    b"&frac34;\0" as *const u8 as *const libc::c_char
                        as *const libc::c_void,
                    (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
                        .wrapping_sub(1 as libc::c_int as libc::c_ulong),
                );
                return 2 as libc::c_int as size_t;
            }
        }
    }
    bufputc(ob, *text.offset(0 as libc::c_int as isize) as libc::c_int);
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__dquote(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if smartypants_quotes(
        ob,
        previous_char,
        (if size > 0 as libc::c_int as size_t {
            *text.offset(1 as libc::c_int as isize) as libc::c_int
        } else {
            0 as libc::c_int
        }) as uint8_t,
        'd' as i32 as uint8_t,
        &mut (*smrt).in_dquote,
    ) == 0
    {
        bufput(
            ob,
            b"&quot;\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            (::core::mem::size_of::<[libc::c_char; 7]>() as libc::c_ulong)
                .wrapping_sub(1 as libc::c_int as libc::c_ulong),
        );
    }
    return 0 as libc::c_int as size_t;
}
unsafe extern "C" fn smartypants_cb__ltag(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    static mut skip_tags: [*const libc::c_char; 8] = [
        b"pre\0" as *const u8 as *const libc::c_char,
        b"code\0" as *const u8 as *const libc::c_char,
        b"var\0" as *const u8 as *const libc::c_char,
        b"samp\0" as *const u8 as *const libc::c_char,
        b"kbd\0" as *const u8 as *const libc::c_char,
        b"math\0" as *const u8 as *const libc::c_char,
        b"script\0" as *const u8 as *const libc::c_char,
        b"style\0" as *const u8 as *const libc::c_char,
    ];
    static mut skip_tags_count: size_t = 8 as libc::c_int as size_t;
    let mut tag: size_t = 0;
    let mut i: size_t = 0 as libc::c_int as size_t;
    while i < size && *text.offset(i as isize) as libc::c_int != '>' as i32 {
        i = i.wrapping_add(1);
        i;
    }
    tag = 0 as libc::c_int as size_t;
    while tag < skip_tags_count {
        if sdhtml_is_tag(text, size, skip_tags[tag as usize])
            == HTML_TAG_OPEN as libc::c_int
        {
            break;
        }
        tag = tag.wrapping_add(1);
        tag;
    }
    if tag < skip_tags_count {
        loop {
            while i < size && *text.offset(i as isize) as libc::c_int != '<' as i32 {
                i = i.wrapping_add(1);
                i;
            }
            if i == size {
                break;
            }
            if sdhtml_is_tag(
                text.offset(i as isize),
                size.wrapping_sub(i),
                skip_tags[tag as usize],
            ) == HTML_TAG_CLOSE as libc::c_int
            {
                break;
            }
            i = i.wrapping_add(1);
            i;
        }
        while i < size && *text.offset(i as isize) as libc::c_int != '>' as i32 {
            i = i.wrapping_add(1);
            i;
        }
    }
    bufput(ob, text as *const libc::c_void, i.wrapping_add(1 as libc::c_int as size_t));
    return i;
}
unsafe extern "C" fn smartypants_cb__escape(
    mut ob: *mut buf,
    mut smrt: *mut smartypants_data,
    mut previous_char: uint8_t,
    mut text: *const uint8_t,
    mut size: size_t,
) -> size_t {
    if size < 2 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    match *text.offset(1 as libc::c_int as isize) as libc::c_int {
        92 | 34 | 39 | 46 | 45 | 96 => {
            bufputc(ob, *text.offset(1 as libc::c_int as isize) as libc::c_int);
            return 1 as libc::c_int as size_t;
        }
        _ => {
            bufputc(ob, '\\' as i32);
            return 0 as libc::c_int as size_t;
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn sdhtml_smartypants(
    mut ob: *mut buf,
    mut text: *const uint8_t,
    mut size: size_t,
) {
    let mut i: size_t = 0;
    let mut smrt: smartypants_data = {
        let mut init = smartypants_data {
            in_squote: 0 as libc::c_int,
            in_dquote: 0 as libc::c_int,
        };
        init
    };
    if text.is_null() {std::intrinsics::assume((text).addr() == 0);
        return;
    }
    bufgrow(ob, size);
    i = 0 as libc::c_int as size_t;
    while i < size {
        let mut org: size_t = 0;
        let mut action: uint8_t = 0 as libc::c_int as uint8_t;
        org = i;
        while i < size
            && {
                action = smartypants_cb_chars[*text.offset(i as isize) as usize];
                action as libc::c_int == 0 as libc::c_int
            }
        {
            i = i.wrapping_add(1);
            i;
        }
        if i > org {
            bufput(
                ob,
                text.offset(org as isize) as *const libc::c_void,
                i.wrapping_sub(org),
            );
        }
        if i < size {
            i = i
                .wrapping_add(
                    (smartypants_cb_ptrs[action as libc::c_int as usize])
                        .expect(
                            "non-null function pointer",
                        )(
                        ob,
                        &mut smrt,
                        (if i != 0 {
                            *text
                                .offset(i.wrapping_sub(1 as libc::c_int as size_t) as isize)
                                as libc::c_int
                        } else {
                            0 as libc::c_int
                        }) as uint8_t,
                        text.offset(i as isize),
                        size.wrapping_sub(i),
                    ),
                );
        }
        i = i.wrapping_add(1);
        i;
    }
}
