use ::libc;
extern "C" {
    fn bufput(_: *mut buf, _: *const libc::c_void, _: size_t);
    fn memcmp(
        _: *const libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn strchr(_: *const libc::c_char, _: libc::c_int) -> *mut libc::c_char;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn strncasecmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn __ctype_b_loc() -> *mut *const libc::c_ushort;
}
pub type size_t = libc::c_ulong;
pub type __uint8_t = libc::c_uchar;
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
pub const SD_AUTOLINK_SHORT_DOMAINS: C2RustUnnamed = 1;
pub const _ISalnum: C2RustUnnamed_0 = 8;
pub const _ISalpha: C2RustUnnamed_0 = 1024;
pub const _ISspace: C2RustUnnamed_0 = 8192;
pub const _ISpunct: C2RustUnnamed_0 = 4;
pub type C2RustUnnamed_0 = libc::c_uint;
pub const _IScntrl: C2RustUnnamed_0 = 2;
pub const _ISblank: C2RustUnnamed_0 = 1;
pub const _ISgraph: C2RustUnnamed_0 = 32768;
pub const _ISprint: C2RustUnnamed_0 = 16384;
pub const _ISxdigit: C2RustUnnamed_0 = 4096;
pub const _ISdigit: C2RustUnnamed_0 = 2048;
pub const _ISlower: C2RustUnnamed_0 = 512;
pub const _ISupper: C2RustUnnamed_0 = 256;
#[no_mangle]
pub unsafe extern "C" fn sd_autolink_issafe(
    mut link: *const uint8_t,
    mut link_len: size_t,
) -> libc::c_int {
    static mut valid_uris_count: size_t = 14 as libc::c_int as size_t;
    static mut valid_uris: [*const libc::c_char; 14] = [
        b"http://\0" as *const u8 as *const libc::c_char,
        b"https://\0" as *const u8 as *const libc::c_char,
        b"ftp://\0" as *const u8 as *const libc::c_char,
        b"mailto://\0" as *const u8 as *const libc::c_char,
        b"/\0" as *const u8 as *const libc::c_char,
        b"git://\0" as *const u8 as *const libc::c_char,
        b"steam://\0" as *const u8 as *const libc::c_char,
        b"irc://\0" as *const u8 as *const libc::c_char,
        b"news://\0" as *const u8 as *const libc::c_char,
        b"mumble://\0" as *const u8 as *const libc::c_char,
        b"ssh://\0" as *const u8 as *const libc::c_char,
        b"ircs://\0" as *const u8 as *const libc::c_char,
        b"ts3server://\0" as *const u8 as *const libc::c_char,
        b"#\0" as *const u8 as *const libc::c_char,
    ];
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < valid_uris_count {
        let mut len: size_t = strlen(valid_uris[i as usize]);
        if link_len > len
            && strncasecmp(link as *mut libc::c_char, valid_uris[i as usize], len)
                == 0 as libc::c_int
            && (*(*__ctype_b_loc())
                .offset(*link.offset(len as isize) as libc::c_int as isize)
                as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
                != 0 || *link.offset(len as isize) as libc::c_int == '#' as i32
                || *link.offset(len as isize) as libc::c_int == '/' as i32
                || *link.offset(len as isize) as libc::c_int == '?' as i32)
        {
            return 1 as libc::c_int;
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn autolink_delim(
    mut data: *mut uint8_t,
    mut link_end: size_t,
    mut max_rewind: size_t,
    mut size: size_t,
) -> size_t {
    let mut cclose: uint8_t = 0;
    let mut copen: uint8_t = 0 as libc::c_int as uint8_t;
    let mut i: size_t = 0;
    i = 0 as libc::c_int as size_t;
    while i < link_end {
        if *data.offset(i as isize) as libc::c_int == '<' as i32 {
            link_end = i;
            break;
        } else {
            i = i.wrapping_add(1);
            i;
        }
    }
    while link_end > 0 as libc::c_int as size_t {
        let mut c: uint8_t = *data
            .offset(link_end.wrapping_sub(1 as libc::c_int as size_t) as isize);
        if c as libc::c_int == 0 as libc::c_int {
            break;
        }
        if !(strchr(b"?!.,\0" as *const u8 as *const libc::c_char, c as libc::c_int))
            .is_null()
        {
            link_end = link_end.wrapping_sub(1);
            link_end;
        } else {std::intrinsics::assume((strchr(b"?!.,\x00" as *const u8 as *const libc::c_char, c as libc::c_int)).addr() == 0);
            if !(c as libc::c_int == ';' as i32) {
                break;
            }
            let mut new_end: size_t = link_end.wrapping_sub(2 as libc::c_int as size_t);
            while new_end > 0 as libc::c_int as size_t
                && *(*__ctype_b_loc())
                    .offset(*data.offset(new_end as isize) as libc::c_int as isize)
                    as libc::c_int
                    & _ISalpha as libc::c_int as libc::c_ushort as libc::c_int != 0
            {
                new_end = new_end.wrapping_sub(1);
                new_end;
            }
            if new_end < link_end.wrapping_sub(2 as libc::c_int as size_t)
                && *data.offset(new_end as isize) as libc::c_int == '&' as i32
            {
                link_end = new_end;
            } else {
                link_end = link_end.wrapping_sub(1);
                link_end;
            }
        }
    }
    if link_end == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    cclose = *data.offset(link_end.wrapping_sub(1 as libc::c_int as size_t) as isize);
    match cclose as libc::c_int {
        34 => {
            copen = '"' as i32 as uint8_t;
        }
        39 => {
            copen = '\'' as i32 as uint8_t;
        }
        41 => {
            copen = '(' as i32 as uint8_t;
        }
        93 => {
            copen = '[' as i32 as uint8_t;
        }
        125 => {
            copen = '{' as i32 as uint8_t;
        }
        _ => {}
    }
    if copen as libc::c_int != 0 as libc::c_int {
        let mut closing: size_t = 0 as libc::c_int as size_t;
        let mut opening: size_t = 0 as libc::c_int as size_t;
        let mut i_0: size_t = 0 as libc::c_int as size_t;
        while i_0 < link_end {
            if *data.offset(i_0 as isize) as libc::c_int == copen as libc::c_int {
                opening = opening.wrapping_add(1);
                opening;
            } else if *data.offset(i_0 as isize) as libc::c_int == cclose as libc::c_int
            {
                closing = closing.wrapping_add(1);
                closing;
            }
            i_0 = i_0.wrapping_add(1);
            i_0;
        }
        if closing != opening {
            link_end = link_end.wrapping_sub(1);
            link_end;
        }
    }
    return link_end;
}
unsafe extern "C" fn check_reddit_autolink_prefix(
    mut data: *const uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
    mut prefix_char: libc::c_char,
) -> libc::c_int {
    if size < 2 as libc::c_int as size_t || max_rewind < 1 as libc::c_int as size_t
        || *data.offset(-(1 as libc::c_int) as isize) as libc::c_int
            != prefix_char as libc::c_int
    {
        return 0 as libc::c_int;
    }
    if max_rewind > 1 as libc::c_int as size_t {
        let boundary: libc::c_char = *data.offset(-(2 as libc::c_int) as isize)
            as libc::c_char;
        if boundary as libc::c_int == '/' as i32 {
            return 2 as libc::c_int
        } else if *(*__ctype_b_loc()).offset(boundary as libc::c_int as isize)
            as libc::c_int & _ISpunct as libc::c_int as libc::c_ushort as libc::c_int
            != 0
            || *(*__ctype_b_loc()).offset(boundary as libc::c_int as isize)
                as libc::c_int & _ISspace as libc::c_int as libc::c_ushort as libc::c_int
                != 0
        {
            return 1 as libc::c_int
        } else {
            return 0 as libc::c_int
        }
    } else if max_lookbehind > 2 as libc::c_int as size_t {
        if *data.offset(-(2 as libc::c_int) as isize) as libc::c_int == '/' as i32
            && *data.offset(-(3 as libc::c_int) as isize) as libc::c_int == '\\' as i32
        {
            return 0 as libc::c_int;
        }
    }
    return 1 as libc::c_int;
}
unsafe extern "C" fn check_domain(
    mut data: *mut uint8_t,
    mut size: size_t,
    mut allow_short: libc::c_int,
) -> size_t {
    let mut i: size_t = 0;
    let mut np: size_t = 0 as libc::c_int as size_t;
    if *(*__ctype_b_loc())
        .offset(*data.offset(0 as libc::c_int as isize) as libc::c_int as isize)
        as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int == 0
    {
        return 0 as libc::c_int as size_t;
    }
    i = 1 as libc::c_int as size_t;
    while i < size.wrapping_sub(1 as libc::c_int as size_t) {
        if *data.offset(i as isize) as libc::c_int == '.' as i32 {
            np = np.wrapping_add(1);
            np;
        } else if *(*__ctype_b_loc())
            .offset(*data.offset(i as isize) as libc::c_int as isize) as libc::c_int
            & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int == 0
            && *data.offset(i as isize) as libc::c_int != '-' as i32
        {
            break;
        }
        i = i.wrapping_add(1);
        i;
    }
    if allow_short != 0 {
        return i
    } else {
        return if np != 0 { i } else { 0 as libc::c_int as size_t }
    };
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__www(
    mut rewind_p: *mut size_t,
    mut link: *mut buf,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut size: size_t,
    mut flags: libc::c_uint,
) -> size_t {
    let mut link_end: size_t = 0;
    if max_rewind > 0 as libc::c_int as size_t
        && *(*__ctype_b_loc())
            .offset(*data.offset(-(1 as libc::c_int) as isize) as libc::c_int as isize)
            as libc::c_int & _ISpunct as libc::c_int as libc::c_ushort as libc::c_int
            == 0
        && *(*__ctype_b_loc())
            .offset(*data.offset(-(1 as libc::c_int) as isize) as libc::c_int as isize)
            as libc::c_int & _ISspace as libc::c_int as libc::c_ushort as libc::c_int
            == 0
    {
        return 0 as libc::c_int as size_t;
    }
    if size < 4 as libc::c_int as size_t
        || memcmp(
            data as *const libc::c_void,
            b"www.\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            strlen(b"www.\0" as *const u8 as *const libc::c_char),
        ) != 0 as libc::c_int
    {
        return 0 as libc::c_int as size_t;
    }
    link_end = check_domain(data, size, 0 as libc::c_int);
    if link_end == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    while link_end < size
        && *(*__ctype_b_loc())
            .offset(*data.offset(link_end as isize) as libc::c_int as isize)
            as libc::c_int & _ISspace as libc::c_int as libc::c_ushort as libc::c_int
            == 0
    {
        link_end = link_end.wrapping_add(1);
        link_end;
    }
    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    bufput(link, data as *const libc::c_void, link_end);
    *rewind_p = 0 as libc::c_int as size_t;
    return link_end as libc::c_int as size_t;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__email(
    mut rewind_p: *mut size_t,
    mut link: *mut buf,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut size: size_t,
    mut flags: libc::c_uint,
) -> size_t {
    let mut link_end: size_t = 0;
    let mut rewind: size_t = 0;
    let mut nb: libc::c_int = 0 as libc::c_int;
    let mut np: libc::c_int = 0 as libc::c_int;
    rewind = 0 as libc::c_int as size_t;
    while rewind < max_rewind {
        let mut c: uint8_t = *data
            .offset(
                rewind.wrapping_neg().wrapping_sub(1 as libc::c_int as size_t) as isize,
            );
        if c as libc::c_int == 0 as libc::c_int {
            break;
        }
        if !(*(*__ctype_b_loc()).offset(c as libc::c_int as isize) as libc::c_int
            & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int != 0)
        {
            if (strchr(b".+-_\0" as *const u8 as *const libc::c_char, c as libc::c_int))
                .is_null()
            {std::intrinsics::assume((strchr(b".+-_\x00" as *const u8 as *const libc::c_char, c as libc::c_int)).addr() == 0);
                break;
            }
        }
        rewind = rewind.wrapping_add(1);
        rewind;
    }
    if rewind == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    link_end = 0 as libc::c_int as size_t;
    while link_end < size {
        let mut c_0: uint8_t = *data.offset(link_end as isize);
        if !(*(*__ctype_b_loc()).offset(c_0 as libc::c_int as isize) as libc::c_int
            & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int != 0)
        {
            if c_0 as libc::c_int == '@' as i32 {
                nb += 1;
                nb;
            } else if c_0 as libc::c_int == '.' as i32
                && link_end < size.wrapping_sub(1 as libc::c_int as size_t)
            {
                np += 1;
                np;
            } else if c_0 as libc::c_int != '-' as i32
                && c_0 as libc::c_int != '_' as i32
            {
                break;
            }
        }
        link_end = link_end.wrapping_add(1);
        link_end;
    }
    if link_end < 2 as libc::c_int as size_t || nb != 1 as libc::c_int
        || np == 0 as libc::c_int
    {
        return 0 as libc::c_int as size_t;
    }
    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    bufput(
        link,
        data.offset(-(rewind as isize)) as *const libc::c_void,
        link_end.wrapping_add(rewind),
    );
    *rewind_p = rewind;
    return link_end;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__url(
    mut rewind_p: *mut size_t,
    mut link: *mut buf,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut size: size_t,
    mut flags: libc::c_uint,
) -> size_t {
    let mut link_end: size_t = 0;
    let mut rewind: size_t = 0 as libc::c_int as size_t;
    let mut domain_len: size_t = 0;
    if size < 4 as libc::c_int as size_t
        || *data.offset(1 as libc::c_int as isize) as libc::c_int != '/' as i32
        || *data.offset(2 as libc::c_int as isize) as libc::c_int != '/' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    while rewind < max_rewind
        && *(*__ctype_b_loc())
            .offset(
                *data
                    .offset(
                        rewind.wrapping_neg().wrapping_sub(1 as libc::c_int as size_t)
                            as isize,
                    ) as libc::c_int as isize,
            ) as libc::c_int & _ISalpha as libc::c_int as libc::c_ushort as libc::c_int
            != 0
    {
        rewind = rewind.wrapping_add(1);
        rewind;
    }
    if sd_autolink_issafe(data.offset(-(rewind as isize)), size.wrapping_add(rewind))
        == 0
    {
        return 0 as libc::c_int as size_t;
    }
    link_end = strlen(b"://\0" as *const u8 as *const libc::c_char);
    domain_len = check_domain(
        data.offset(link_end as isize),
        size.wrapping_sub(link_end),
        (flags & SD_AUTOLINK_SHORT_DOMAINS as libc::c_int as libc::c_uint) as libc::c_int,
    );
    if domain_len == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    link_end = link_end.wrapping_add(domain_len);
    while link_end < size
        && *(*__ctype_b_loc())
            .offset(*data.offset(link_end as isize) as libc::c_int as isize)
            as libc::c_int & _ISspace as libc::c_int as libc::c_ushort as libc::c_int
            == 0
    {
        link_end = link_end.wrapping_add(1);
        link_end;
    }
    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    bufput(
        link,
        data.offset(-(rewind as isize)) as *const libc::c_void,
        link_end.wrapping_add(rewind),
    );
    *rewind_p = rewind;
    return link_end;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__subreddit(
    mut rewind_p: *mut size_t,
    mut link: *mut buf,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
    mut no_slash: *mut libc::c_int,
) -> size_t {
    let mut link_end: size_t = 0;
    let mut rewind: size_t = 0;
    let mut is_allminus: libc::c_int = 0 as libc::c_int;
    rewind = check_reddit_autolink_prefix(
        data,
        max_rewind,
        max_lookbehind,
        size,
        'r' as i32 as libc::c_char,
    ) as size_t;
    if rewind == 0 {
        return 0 as libc::c_int as size_t;
    }
    link_end = strlen(b"/\0" as *const u8 as *const libc::c_char);
    if size >= link_end.wrapping_add(4 as libc::c_int as size_t)
        && strncasecmp(
            (data as *mut libc::c_char).offset(link_end as isize),
            b"all-\0" as *const u8 as *const libc::c_char,
            4 as libc::c_int as libc::c_ulong,
        ) == 0 as libc::c_int
    {
        is_allminus = 1 as libc::c_int;
    }
    loop {
        let mut start: size_t = link_end;
        let mut max_length: libc::c_int = 24 as libc::c_int;
        if size >= link_end.wrapping_add(10 as libc::c_int as size_t)
            && strncasecmp(
                (data as *mut libc::c_char).offset(link_end as isize),
                b"reddit.com\0" as *const u8 as *const libc::c_char,
                10 as libc::c_int as libc::c_ulong,
            ) == 0 as libc::c_int
        {
            link_end = link_end.wrapping_add(10 as libc::c_int as size_t);
            max_length = 10 as libc::c_int;
        } else {
            if size > link_end.wrapping_add(2 as libc::c_int as size_t)
                && strncasecmp(
                    (data as *mut libc::c_char).offset(link_end as isize),
                    b"t:\0" as *const u8 as *const libc::c_char,
                    2 as libc::c_int as libc::c_ulong,
                ) == 0 as libc::c_int
            {
                link_end = link_end.wrapping_add(2 as libc::c_int as size_t);
            }
            if *(*__ctype_b_loc())
                .offset(*data.offset(link_end as isize) as libc::c_int as isize)
                as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
                == 0
            {
                return 0 as libc::c_int as size_t;
            }
            link_end = link_end.wrapping_add(1 as libc::c_int as size_t);
        }
        while link_end < size
            && (*(*__ctype_b_loc())
                .offset(*data.offset(link_end as isize) as libc::c_int as isize)
                as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
                != 0 || *data.offset(link_end as isize) as libc::c_int == '_' as i32)
        {
            link_end = link_end.wrapping_add(1);
            link_end;
        }
        if link_end.wrapping_sub(start) < 2 as libc::c_int as size_t
            || link_end.wrapping_sub(start) > max_length as size_t
        {
            return 0 as libc::c_int as size_t;
        }
        if !(link_end < size
            && (*data.offset(link_end as isize) as libc::c_int == '+' as i32
                || is_allminus != 0
                    && *data.offset(link_end as isize) as libc::c_int == '-' as i32)
            && {
                let fresh0 = link_end;
                link_end = link_end.wrapping_add(1);
                fresh0 != 0
            })
        {
            break;
        }
    }
    if link_end < size && *data.offset(link_end as isize) as libc::c_int == '/' as i32 {
        while link_end < size
            && (*(*__ctype_b_loc())
                .offset(*data.offset(link_end as isize) as libc::c_int as isize)
                as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
                != 0 || *data.offset(link_end as isize) as libc::c_int == '_' as i32
                || *data.offset(link_end as isize) as libc::c_int == '/' as i32
                || *data.offset(link_end as isize) as libc::c_int == '-' as i32)
        {
            link_end = link_end.wrapping_add(1);
            link_end;
        }
    }
    bufput(
        link,
        data.offset(-(rewind as isize)) as *const libc::c_void,
        link_end.wrapping_add(rewind),
    );
    *no_slash = (rewind == 1 as libc::c_int as size_t) as libc::c_int;
    *rewind_p = rewind;
    return link_end;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__username(
    mut rewind_p: *mut size_t,
    mut link: *mut buf,
    mut data: *mut uint8_t,
    mut max_rewind: size_t,
    mut max_lookbehind: size_t,
    mut size: size_t,
    mut no_slash: *mut libc::c_int,
) -> size_t {
    let mut link_end: size_t = 0;
    let mut rewind: size_t = 0;
    if size < 3 as libc::c_int as size_t {
        return 0 as libc::c_int as size_t;
    }
    rewind = check_reddit_autolink_prefix(
        data,
        max_rewind,
        max_lookbehind,
        size,
        'u' as i32 as libc::c_char,
    ) as size_t;
    if rewind == 0 {
        return 0 as libc::c_int as size_t;
    }
    link_end = strlen(b"/\0" as *const u8 as *const libc::c_char);
    if *(*__ctype_b_loc())
        .offset(*data.offset(link_end as isize) as libc::c_int as isize) as libc::c_int
        & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int == 0
        && *data.offset(link_end as isize) as libc::c_int != '_' as i32
        && *data.offset(link_end as isize) as libc::c_int != '-' as i32
    {
        return 0 as libc::c_int as size_t;
    }
    link_end = link_end.wrapping_add(1 as libc::c_int as size_t);
    while link_end < size
        && (*(*__ctype_b_loc())
            .offset(*data.offset(link_end as isize) as libc::c_int as isize)
            as libc::c_int & _ISalnum as libc::c_int as libc::c_ushort as libc::c_int
            != 0 || *data.offset(link_end as isize) as libc::c_int == '_' as i32
            || *data.offset(link_end as isize) as libc::c_int == '/' as i32
            || *data.offset(link_end as isize) as libc::c_int == '-' as i32)
    {
        link_end = link_end.wrapping_add(1);
        link_end;
    }
    bufput(
        link,
        data.offset(-(rewind as isize)) as *const libc::c_void,
        link_end.wrapping_add(rewind),
    );
    *no_slash = (rewind == 1 as libc::c_int as size_t) as libc::c_int;
    *rewind_p = rewind;
    return link_end;
}
