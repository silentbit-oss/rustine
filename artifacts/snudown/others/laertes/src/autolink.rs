
extern "C" {
    /* bufput: appends raw data to a buffer */
    
    
    #[no_mangle]
    fn strncasecmp(_: * const std::os::raw::c_char, _: * const std::os::raw::c_char,
                   _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn strchr(_: * const std::os::raw::c_char, _: std::os::raw::c_int) -> * mut std::os::raw::c_char;
    #[no_mangle]
    fn memcmp(_: * const core::ffi::c_void, _: * const core::ffi::c_void,
              _: std::os::raw::c_ulong) -> std::os::raw::c_int;
    #[no_mangle]
    fn strlen(_: * const std::os::raw::c_char) -> std::os::raw::c_ulong;
    #[no_mangle]
    fn __ctype_b_loc() -> * mut * const std::os::raw::c_ushort;
}
pub use crate::src::buffer::bufput;
pub type size_t = std::os::raw::c_ulong;
pub type __uint8_t = std::os::raw::c_uchar;
pub type uint8_t = std::os::raw::c_uchar;
/* struct buf: character array buffer */
#[derive(Copy, Clone)]
#[repr(C)]
pub struct buf {
    pub data: * mut std::os::raw::c_uchar,
    pub size: std::os::raw::c_ulong,
    pub asize: std::os::raw::c_ulong,
    pub unit: std::os::raw::c_ulong,
}
impl buf {
    pub const fn new() -> Self {
        buf {
        data: (0 as * mut std::os::raw::c_uchar),
        size: 0,
        asize: 0,
        unit: 0
        }
    }
}

impl std::default::Default for buf {
    fn default() -> Self { buf::new() }
}

/*
 * Copyright (c) 2011, Vicent Marti
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
pub type C2RustUnnamed = std::os::raw::c_uint;
pub const SD_AUTOLINK_SHORT_DOMAINS: C2RustUnnamed = 1;
pub const _ISalnum: C2RustUnnamed_0 = 8;
pub const _ISalpha: C2RustUnnamed_0 = 1024;
pub const _ISspace: C2RustUnnamed_0 = 8192;
pub const _ISpunct: C2RustUnnamed_0 = 4;
pub type C2RustUnnamed_0 = std::os::raw::c_uint;
pub const _IScntrl: C2RustUnnamed_0 = 2;
pub const _ISblank: C2RustUnnamed_0 = 1;
pub const _ISgraph: C2RustUnnamed_0 = 32768;
pub const _ISprint: C2RustUnnamed_0 = 16384;
pub const _ISxdigit: C2RustUnnamed_0 = 4096;
pub const _ISdigit: C2RustUnnamed_0 = 2048;
pub const _ISlower: C2RustUnnamed_0 = 512;
pub const _ISupper: C2RustUnnamed_0 = 256;
/*
 * Copyright (c) 2011, Vicent Marti
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#[no_mangle]
pub unsafe extern "C" fn sd_autolink_issafe(mut link: * const std::os::raw::c_uchar,
                                            mut link_len: std::os::raw::c_ulong)
 -> std::os::raw::c_int {
    static mut valid_uris_count: std::os::raw::c_ulong = 0; unsafe fn laertes_init_valid_uris_count() {
valid_uris_count = 14 as std::os::raw::c_int as size_t;}//;
    static mut valid_uris: [* const std::os::raw::c_char; 14] =
        [(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),(0 as * const std::os::raw::c_char),]; unsafe fn laertes_init_valid_uris() {
valid_uris = [b"http://\x00" as *const u8 as *const std::os::raw::c_char,
         b"https://\x00" as *const u8 as *const std::os::raw::c_char,
         b"ftp://\x00" as *const u8 as *const std::os::raw::c_char,
         b"mailto://\x00" as *const u8 as *const std::os::raw::c_char,
         b"/\x00" as *const u8 as *const std::os::raw::c_char,
         b"git://\x00" as *const u8 as *const std::os::raw::c_char,
         b"steam://\x00" as *const u8 as *const std::os::raw::c_char,
         b"irc://\x00" as *const u8 as *const std::os::raw::c_char,
         b"news://\x00" as *const u8 as *const std::os::raw::c_char,
         b"mumble://\x00" as *const u8 as *const std::os::raw::c_char,
         b"ssh://\x00" as *const u8 as *const std::os::raw::c_char,
         b"ircs://\x00" as *const u8 as *const std::os::raw::c_char,
         b"ts3server://\x00" as *const u8 as *const std::os::raw::c_char,
         b"#\x00" as *const u8 as *const std::os::raw::c_char];}//;
    let mut i: u64 = 0;
    i = 0 as std::os::raw::c_int as size_t;
    while i < valid_uris_count {
        let mut len: u64 = strlen(valid_uris[i as usize]);
        if link_len > len &&
               strncasecmp(link as *mut std::os::raw::c_char, valid_uris[i as usize],
                           len) == 0 as std::os::raw::c_int &&
               (*(*__ctype_b_loc()).offset(*link.offset(len as isize) as
                                               std::os::raw::c_int as isize) as
                    std::os::raw::c_int &
                    _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int
                    != 0 ||
                    *link.offset(len as isize) as std::os::raw::c_int == '#' as i32 ||
                    *link.offset(len as isize) as std::os::raw::c_int == '/' as i32 ||
                    *link.offset(len as isize) as std::os::raw::c_int == '?' as i32) {
            return 1 as std::os::raw::c_int
        }
        i = i.wrapping_add(1)
    }
    return 0 as std::os::raw::c_int;
}
unsafe extern "C" fn autolink_delim(mut data: * mut std::os::raw::c_uchar,
                                    mut link_end: std::os::raw::c_ulong,
                                    mut max_rewind: std::os::raw::c_ulong, mut size: std::os::raw::c_ulong)
 -> std::os::raw::c_ulong {
    let mut cclose: u8 = 0;
    let mut copen: u8 = 0 as std::os::raw::c_int as uint8_t;
    let mut i: u64 = 0;
    i = 0 as std::os::raw::c_int as size_t;
    while i < link_end {
        if *data.offset(i as isize) as std::os::raw::c_int == '<' as i32 {
            link_end = i;
            break ;
        } else { i = i.wrapping_add(1) }
    }
    while link_end > 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        let mut c: u8 =
            *data.offset(link_end.wrapping_sub(1 as std::os::raw::c_int as
                                                   std::os::raw::c_ulong) as isize);
        if c as std::os::raw::c_int == 0 as std::os::raw::c_int { break ; }
        if !strchr(b"?!.,\x00" as *const u8 as *const std::os::raw::c_char,
                   c as std::os::raw::c_int).is_null() {
            link_end = link_end.wrapping_sub(1)
        } else {
            if !(c as std::os::raw::c_int == ';' as i32) { break ; }
            let mut new_end: u64 =
                link_end.wrapping_sub(2 as std::os::raw::c_int as std::os::raw::c_ulong);
            while new_end > 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
                      *(*__ctype_b_loc()).offset(*data.offset(new_end as
                                                                  isize) as
                                                     std::os::raw::c_int as isize) as
                          std::os::raw::c_int &
                          _ISalpha as std::os::raw::c_int as std::os::raw::c_ushort as
                              std::os::raw::c_int != 0 {
                new_end = new_end.wrapping_sub(1)
            }
            if new_end <
                   link_end.wrapping_sub(2 as std::os::raw::c_int as std::os::raw::c_ulong) &&
                   *data.offset(new_end as isize) as std::os::raw::c_int == '&' as i32
               {
                link_end = new_end
            } else { link_end = link_end.wrapping_sub(1) }
        }
    }
    if link_end == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    cclose =
        *data.offset(link_end.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong)
                         as isize);
    match cclose as std::os::raw::c_int {
        34 => { copen = '\"' as i32 as uint8_t }
        39 => { copen = '\'' as i32 as uint8_t }
        41 => { copen = '(' as i32 as uint8_t }
        93 => { copen = '[' as i32 as uint8_t }
        125 => { copen = '{' as i32 as uint8_t }
        _ => { }
    }
    if copen as std::os::raw::c_int != 0 as std::os::raw::c_int {
        let mut closing: u64 = 0 as std::os::raw::c_int as size_t;
        let mut opening: u64 = 0 as std::os::raw::c_int as size_t;
        let mut i_0: u64 = 0 as std::os::raw::c_int as size_t;
        /* Try to close the final punctuation sign in this same line;
		 * if we managed to close it outside of the URL, that means that it's
		 * not part of the URL. If it closes inside the URL, that means it
		 * is part of the URL.
		 *
		 * Examples:
		 *
		 *	foo http://www.pokemon.com/Pikachu_(Electric) bar
		 *		=> http://www.pokemon.com/Pikachu_(Electric)
		 *
		 *	foo (http://www.pokemon.com/Pikachu_(Electric)) bar
		 *		=> http://www.pokemon.com/Pikachu_(Electric)
		 *
		 *	foo http://www.pokemon.com/Pikachu_(Electric)) bar
		 *		=> http://www.pokemon.com/Pikachu_(Electric))
		 *
		 *	(foo http://www.pokemon.com/Pikachu_(Electric)) bar
		 *		=> foo http://www.pokemon.com/Pikachu_(Electric)
		 */
        while i_0 < link_end {
            if *data.offset(i_0 as isize) as std::os::raw::c_int ==
                   copen as std::os::raw::c_int {
                opening = opening.wrapping_add(1)
            } else if *data.offset(i_0 as isize) as std::os::raw::c_int ==
                          cclose as std::os::raw::c_int {
                closing = closing.wrapping_add(1)
            }
            i_0 = i_0.wrapping_add(1)
        }
        if closing != opening { link_end = link_end.wrapping_sub(1) }
    }
    return link_end;
}
/*
 * Checks that `prefix_char` occurs on a word boundary just before `data`,
 * where `data` points to the character to search to the left of, and a word boundary
 * is (currently) a whitespace character, punctuation, or the start of the string.
 * Returns the length of the prefix.
 */
unsafe extern "C" fn check_reddit_autolink_prefix(mut data: * const std::os::raw::c_uchar,
                                                  mut max_rewind: std::os::raw::c_ulong,
                                                  mut max_lookbehind: std::os::raw::c_ulong,
                                                  mut size: std::os::raw::c_ulong,
                                                  mut prefix_char:
                                                      std::os::raw::c_char)
 -> std::os::raw::c_int {
    /* Make sure this `/` is part of `/?r/` */
    if size < 2 as std::os::raw::c_int as std::os::raw::c_ulong ||
           max_rewind < 1 as std::os::raw::c_int as std::os::raw::c_ulong ||
           *data.offset(-(1 as std::os::raw::c_int) as isize) as std::os::raw::c_int !=
               prefix_char as std::os::raw::c_int {
        return 0 as std::os::raw::c_int
    }
    /* Not at the start of the buffer, no inlines to the immediate left of the `prefix_char` */
    if max_rewind > 1 as std::os::raw::c_int as std::os::raw::c_ulong {
        let boundary: i8 =
            *data.offset(-(2 as std::os::raw::c_int) as isize) as std::os::raw::c_char;
        if boundary as std::os::raw::c_int == '/' as i32 {
            return 2 as std::os::raw::c_int
        } else if *(*__ctype_b_loc()).offset(boundary as std::os::raw::c_int as isize)
                      as std::os::raw::c_int &
                      _ISpunct as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int
                      != 0 ||
                      *(*__ctype_b_loc()).offset(boundary as std::os::raw::c_int as
                                                     isize) as std::os::raw::c_int &
                          _ISspace as std::os::raw::c_int as std::os::raw::c_ushort as
                              std::os::raw::c_int != 0 {
            return 1 as std::os::raw::c_int
        } else { return 0 as std::os::raw::c_int }
    } else {
        if max_lookbehind > 2 as std::os::raw::c_int as std::os::raw::c_ulong {
            /* *
		 * Here's where our lack of unicode-awareness bites us. We don't correctly
		 * match punctuation / whitespace characters for the boundary, because we
		 * reject valid cases like "。r/example" (note the fullwidth period.)
		 *
		 * A better implementation might try to rewind over bytes with the 8th bit set, try
		 * to decode them to a valid codepoint, then do a unicode-aware check on the codepoint.
		 */
            /* There's an inline element just left of the `prefix_char`, is it an escaped forward
		 * slash? bail out so we correctly handle stuff like "\/r/foo". This will also correctly
		 * allow "\\/r/foo".
		 */
            if *data.offset(-(2 as std::os::raw::c_int) as isize) as std::os::raw::c_int ==
                   '/' as i32 &&
                   *data.offset(-(3 as std::os::raw::c_int) as isize) as std::os::raw::c_int
                       == '\\' as i32 {
                return 0 as std::os::raw::c_int
            }
        }
    }
    /* Must be a new-style shortlink with nothing relevant to the left of it. */
    return 1 as std::os::raw::c_int;
}
unsafe extern "C" fn check_domain(mut data: * mut std::os::raw::c_uchar, mut size: std::os::raw::c_ulong,
                                  mut allow_short: std::os::raw::c_int) -> std::os::raw::c_ulong {
    let mut i: u64 = 0;
    let mut np: u64 = 0 as std::os::raw::c_int as size_t;
    if *(*__ctype_b_loc()).offset(*data.offset(0 as std::os::raw::c_int as isize) as
                                      std::os::raw::c_int as isize) as std::os::raw::c_int &
           _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int == 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    i = 1 as std::os::raw::c_int as size_t;
    while i < size.wrapping_sub(1 as std::os::raw::c_int as std::os::raw::c_ulong) {
        if *data.offset(i as isize) as std::os::raw::c_int == '.' as i32 {
            np = np.wrapping_add(1)
        } else if *(*__ctype_b_loc()).offset(*data.offset(i as isize) as
                                                 std::os::raw::c_int as isize) as
                      std::os::raw::c_int &
                      _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int
                      == 0 &&
                      *data.offset(i as isize) as std::os::raw::c_int != '-' as i32 {
            break ;
        }
        i = i.wrapping_add(1)
    }
    if allow_short != 0 {
        /* We don't need a valid domain in the strict sense (with
		 * least one dot; so just make sure it's composed of valid
		 * domain characters and return the length of the the valid
		 * sequence. */
        return i
    } else {
        /* a valid domain needs to have at least a dot.
		 * that's as far as we get */
        return if np != 0 { i } else { 0 as std::os::raw::c_int as std::os::raw::c_ulong }
    };
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__www<'a1>(mut rewind_p: Option<&'a1 mut std::os::raw::c_ulong>,
                                          mut link: * mut crate::src::autolink::buf,
                                          mut data: * mut std::os::raw::c_uchar,
                                          mut max_rewind: std::os::raw::c_ulong,
                                          mut size: std::os::raw::c_ulong,
                                          mut flags: std::os::raw::c_uint) -> std::os::raw::c_ulong {
    let mut link_end: u64 = 0;
    if max_rewind > 0 as std::os::raw::c_int as std::os::raw::c_ulong &&
           *(*__ctype_b_loc()).offset(*data.offset(-(1 as std::os::raw::c_int) as
                                                       isize) as std::os::raw::c_int
                                          as isize) as std::os::raw::c_int &
               _ISpunct as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int == 0
           &&
           *(*__ctype_b_loc()).offset(*data.offset(-(1 as std::os::raw::c_int) as
                                                       isize) as std::os::raw::c_int
                                          as isize) as std::os::raw::c_int &
               _ISspace as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int == 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    if size < 4 as std::os::raw::c_int as std::os::raw::c_ulong ||
           memcmp(data as *const std::os::raw::c_void,
                  b"www.\x00" as *const u8 as *const std::os::raw::c_char as
                      *const std::os::raw::c_void,
                  strlen(b"www.\x00" as *const u8 as *const std::os::raw::c_char)) !=
               0 as std::os::raw::c_int {
        return 0 as std::os::raw::c_int as size_t
    }
    link_end = check_domain(data, size, 0 as std::os::raw::c_int);
    if link_end == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    while link_end < size &&
              *(*__ctype_b_loc()).offset(*data.offset(link_end as isize) as
                                             std::os::raw::c_int as isize) as
                  std::os::raw::c_int &
                  _ISspace as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int ==
                  0 {
        link_end = link_end.wrapping_add(1)
    }
    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    bufput(link, data as *const std::os::raw::c_void, link_end);
    *(borrow_mut(&mut rewind_p)).unwrap() = 0 as std::os::raw::c_int as size_t;
    return link_end as std::os::raw::c_int as size_t;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__email<'a1>(mut rewind_p: Option<&'a1 mut std::os::raw::c_ulong>,
                                            mut link: * mut crate::src::autolink::buf,
                                            mut data: * mut std::os::raw::c_uchar,
                                            mut max_rewind: std::os::raw::c_ulong,
                                            mut size: std::os::raw::c_ulong,
                                            mut flags: std::os::raw::c_uint)
 -> std::os::raw::c_ulong {
    let mut link_end: u64 = 0;
    let mut rewind: u64 = 0;
    let mut nb: i32 = 0 as std::os::raw::c_int;
    let mut np: i32 = 0 as std::os::raw::c_int;
    rewind = 0 as std::os::raw::c_int as size_t;
    while rewind < max_rewind {
        let mut c: u8 =
            *data.offset(rewind.wrapping_neg().wrapping_sub(1 as std::os::raw::c_int
                                                                as
                                                                std::os::raw::c_ulong)
                             as isize);
        if c as std::os::raw::c_int == 0 as std::os::raw::c_int { break ; }
        if !(*(*__ctype_b_loc()).offset(c as std::os::raw::c_int as isize) as
                 std::os::raw::c_int &
                 _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int !=
                 0) {
            if strchr(b".+-_\x00" as *const u8 as *const std::os::raw::c_char,
                      c as std::os::raw::c_int).is_null() {
                break ;
            }
        }
        rewind = rewind.wrapping_add(1)
    }
    if rewind == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    link_end = 0 as std::os::raw::c_int as size_t;
    while link_end < size {
        let mut c_0: u8 = *data.offset(link_end as isize);
        if !(*(*__ctype_b_loc()).offset(c_0 as std::os::raw::c_int as isize) as
                 std::os::raw::c_int &
                 _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int !=
                 0) {
            if c_0 as std::os::raw::c_int == '@' as i32 {
                nb += 1
            } else if c_0 as std::os::raw::c_int == '.' as i32 &&
                          link_end <
                              size.wrapping_sub(1 as std::os::raw::c_int as
                                                    std::os::raw::c_ulong) {
                np += 1
            } else if c_0 as std::os::raw::c_int != '-' as i32 &&
                          c_0 as std::os::raw::c_int != '_' as i32 {
                break ;
            }
        }
        link_end = link_end.wrapping_add(1)
    }
    if link_end < 2 as std::os::raw::c_int as std::os::raw::c_ulong || nb != 1 as std::os::raw::c_int
           || np == 0 as std::os::raw::c_int {
        return 0 as std::os::raw::c_int as size_t
    }
    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    bufput(link, data.offset(-(rewind as isize)) as *const std::os::raw::c_void,
           link_end.wrapping_add(rewind));
    *(borrow_mut(&mut rewind_p)).unwrap() = rewind;
    return link_end;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__url<'a1>(mut rewind_p: Option<&'a1 mut std::os::raw::c_ulong>,
                                          mut link: * mut crate::src::autolink::buf,
                                          mut data: * mut std::os::raw::c_uchar,
                                          mut max_rewind: std::os::raw::c_ulong,
                                          mut size: std::os::raw::c_ulong,
                                          mut flags: std::os::raw::c_uint) -> std::os::raw::c_ulong {
    let mut link_end: u64 = 0;
    let mut rewind: u64 = 0 as std::os::raw::c_int as size_t;
    let mut domain_len: u64 = 0;
    if size < 4 as std::os::raw::c_int as std::os::raw::c_ulong ||
           *data.offset(1 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
               '/' as i32 ||
           *data.offset(2 as std::os::raw::c_int as isize) as std::os::raw::c_int !=
               '/' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    while rewind < max_rewind &&
              *(*__ctype_b_loc()).offset(*data.offset(rewind.wrapping_neg().wrapping_sub(1
                                                                                             as
                                                                                             std::os::raw::c_int
                                                                                             as
                                                                                             std::os::raw::c_ulong)
                                                          as isize) as
                                             std::os::raw::c_int as isize) as
                  std::os::raw::c_int &
                  _ISalpha as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int !=
                  0 {
        rewind = rewind.wrapping_add(1)
    }
    if sd_autolink_issafe(data.offset(-(rewind as isize)),
                          size.wrapping_add(rewind)) == 0 {
        return 0 as std::os::raw::c_int as size_t
    }
    link_end = strlen(b"://\x00" as *const u8 as *const std::os::raw::c_char);
    domain_len =
        check_domain(data.offset(link_end as isize),
                     size.wrapping_sub(link_end),
                     (flags &
                          SD_AUTOLINK_SHORT_DOMAINS as std::os::raw::c_int as
                              std::os::raw::c_uint) as std::os::raw::c_int);
    if domain_len == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    link_end =
        (link_end as std::os::raw::c_ulong).wrapping_add(domain_len) as size_t as
            size_t;
    while link_end < size &&
              *(*__ctype_b_loc()).offset(*data.offset(link_end as isize) as
                                             std::os::raw::c_int as isize) as
                  std::os::raw::c_int &
                  _ISspace as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int ==
                  0 {
        link_end = link_end.wrapping_add(1)
    }
    link_end = autolink_delim(data, link_end, max_rewind, size);
    if link_end == 0 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    bufput(link, data.offset(-(rewind as isize)) as *const std::os::raw::c_void,
           link_end.wrapping_add(rewind));
    *(borrow_mut(&mut rewind_p)).unwrap() = rewind;
    return link_end;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__subreddit<'a1, 'a2>(mut rewind_p: Option<&'a1 mut std::os::raw::c_ulong>,
                                                mut link: * mut crate::src::autolink::buf,
                                                mut data: * mut std::os::raw::c_uchar,
                                                mut max_rewind: std::os::raw::c_ulong,
                                                mut max_lookbehind: std::os::raw::c_ulong,
                                                mut size: std::os::raw::c_ulong,
                                                mut no_slash:
                                                    Option<&'a2 mut std::os::raw::c_int>)
 -> std::os::raw::c_ulong {
    /* *
	 * This is meant to handle both r/foo and /r/foo style subreddit references.
	 * In a valid /?r/ link, `*data` will always point to the '/' after the first 'r'.
	 * In pseudo-regex, this matches something like:
	 *
	 * `(/|(?<=\b))r/(all-)?%subreddit%([-+]%subreddit%)*(/[\w\-/]*)?`
	 * where %subreddit% == `((t:)?\w{2,24}|reddit\.com)`
	 */
    let mut link_end: u64 = 0;
    let mut rewind: u64 = 0;
    let mut is_allminus: i32 = 0 as std::os::raw::c_int;
    rewind =
        check_reddit_autolink_prefix(data, max_rewind, max_lookbehind, size,
                                     'r' as i32 as std::os::raw::c_char) as size_t;
    if rewind == 0 { return 0 as std::os::raw::c_int as size_t }
    /* offset to the "meat" of the link */
    link_end = strlen(b"/\x00" as *const u8 as *const std::os::raw::c_char);
    if size >= link_end.wrapping_add(4 as std::os::raw::c_int as std::os::raw::c_ulong) &&
           strncasecmp((data as *mut std::os::raw::c_char).offset(link_end as isize),
                       b"all-\x00" as *const u8 as *const std::os::raw::c_char,
                       4 as std::os::raw::c_int as std::os::raw::c_ulong) == 0 as std::os::raw::c_int
       {
        is_allminus = 1 as std::os::raw::c_int
    }
    loop  {
        let mut start: u64 = link_end;
        let mut max_length: i32 = 24 as std::os::raw::c_int;
        /* If we are linking to a multireddit, continue */
        if size >= link_end.wrapping_add(10 as std::os::raw::c_int as std::os::raw::c_ulong)
               &&
               strncasecmp((data as
                                *mut std::os::raw::c_char).offset(link_end as isize),
                           b"reddit.com\x00" as *const u8 as
                               *const std::os::raw::c_char,
                           10 as std::os::raw::c_int as std::os::raw::c_ulong) ==
                   0 as std::os::raw::c_int {
            link_end =
                (link_end as
                     std::os::raw::c_ulong).wrapping_add(10 as std::os::raw::c_int as
                                                     std::os::raw::c_ulong) as size_t
                    as size_t;
            /* special case: /r/reddit.com (only subreddit containing '.'). */
            /* Make sure there are no trailing characters (don't do
			 * any autolinking for /r/reddit.commission) */
            max_length = 10 as std::os::raw::c_int
        } else {
            /* If not a special case, verify it begins with (t:)?[A-Za-z0-9] */
            /* support autolinking to timereddits, /r/t:when (1 April 2012) */
            if size > link_end.wrapping_add(2 as std::os::raw::c_int as std::os::raw::c_ulong)
                   &&
                   strncasecmp((data as
                                    *mut std::os::raw::c_char).offset(link_end as
                                                                  isize),
                               b"t:\x00" as *const u8 as *const std::os::raw::c_char,
                               2 as std::os::raw::c_int as std::os::raw::c_ulong) ==
                       0 as std::os::raw::c_int {
                link_end =
                    (link_end as
                         std::os::raw::c_ulong).wrapping_add(2 as std::os::raw::c_int as
                                                         std::os::raw::c_ulong) as
                        size_t as size_t
            } /* Jump over the 't:' */
            if *(*__ctype_b_loc()).offset(*data.offset(link_end as isize) as
                                              std::os::raw::c_int as isize) as
                   std::os::raw::c_int &
                   _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int ==
                   0 {
                return 0 as std::os::raw::c_int as size_t
            }
            link_end =
                (link_end as
                     std::os::raw::c_ulong).wrapping_add(1 as std::os::raw::c_int as
                                                     std::os::raw::c_ulong) as size_t
                    as size_t
        }
        while link_end < size &&
                  (*(*__ctype_b_loc()).offset(*data.offset(link_end as isize)
                                                  as std::os::raw::c_int as isize) as
                       std::os::raw::c_int &
                       _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as
                           std::os::raw::c_int != 0 ||
                       *data.offset(link_end as isize) as std::os::raw::c_int ==
                           '_' as i32)
              /* the first character of a subreddit name must be a letter or digit */
              /* consume valid characters ([A-Za-z0-9_]) until we run out */
              {
            link_end = link_end.wrapping_add(1)
        }
        if link_end.wrapping_sub(start) < 2 as std::os::raw::c_int as std::os::raw::c_ulong ||
               link_end.wrapping_sub(start) > max_length as std::os::raw::c_ulong {
            return 0 as std::os::raw::c_int as size_t
        }
        if !(link_end < size &&
                 (*data.offset(link_end as isize) as std::os::raw::c_int == '+' as i32
                      ||
                      is_allminus != 0 &&
                          *data.offset(link_end as isize) as std::os::raw::c_int ==
                              '-' as i32) &&
                 {
                     let mut fresh0 = link_end;
                     link_end = link_end.wrapping_add(1);
                     (fresh0) != 0
                 }) {
            break ;
        }
    }
    if link_end < size &&
           *data.offset(link_end as isize) as std::os::raw::c_int == '/' as i32 {
        while link_end < size &&
                  (*(*__ctype_b_loc()).offset(*data.offset(link_end as isize)
                                                  as std::os::raw::c_int as isize) as
                       std::os::raw::c_int &
                       _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as
                           std::os::raw::c_int != 0 ||
                       *data.offset(link_end as isize) as std::os::raw::c_int ==
                           '_' as i32 ||
                       *data.offset(link_end as isize) as std::os::raw::c_int ==
                           '/' as i32 ||
                       *data.offset(link_end as isize) as std::os::raw::c_int ==
                           '-' as i32) {
            link_end = link_end.wrapping_add(1)
        }
    }
    /* valid subreddit names are between 3 and 21 characters, with
		 * some subreddits having 2-character names. Don't bother with
		 * autolinking for anything outside this length range.
		 * (chksrname function in reddit/.../validator.py) */
    /* make the link */
    bufput(link, data.offset(-(rewind as isize)) as *const std::os::raw::c_void,
           link_end.wrapping_add(rewind));
    *(borrow_mut(&mut no_slash)).unwrap() = (rewind == 1 as std::os::raw::c_int as std::os::raw::c_ulong) as std::os::raw::c_int;
    *(borrow_mut(&mut rewind_p)).unwrap() = rewind;
    return link_end;
}
#[no_mangle]
pub unsafe extern "C" fn sd_autolink__username<'a1, 'a2>(mut rewind_p: Option<&'a1 mut std::os::raw::c_ulong>,
                                               mut link: * mut crate::src::autolink::buf,
                                               mut data: * mut std::os::raw::c_uchar,
                                               mut max_rewind: std::os::raw::c_ulong,
                                               mut max_lookbehind: std::os::raw::c_ulong,
                                               mut size: std::os::raw::c_ulong,
                                               mut no_slash: Option<&'a2 mut std::os::raw::c_int>)
 -> std::os::raw::c_ulong {
    let mut link_end: u64 = 0;
    let mut rewind: u64 = 0;
    if size < 3 as std::os::raw::c_int as std::os::raw::c_ulong {
        return 0 as std::os::raw::c_int as size_t
    }
    rewind =
        check_reddit_autolink_prefix(data, max_rewind, max_lookbehind, size,
                                     'u' as i32 as std::os::raw::c_char) as size_t;
    if rewind == 0 { return 0 as std::os::raw::c_int as size_t }
    link_end = strlen(b"/\x00" as *const u8 as *const std::os::raw::c_char);
    /* the first letter of a username must... well, be valid, we don't care otherwise */
    if *(*__ctype_b_loc()).offset(*data.offset(link_end as isize) as
                                      std::os::raw::c_int as isize) as std::os::raw::c_int &
           _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int == 0 &&
           *data.offset(link_end as isize) as std::os::raw::c_int != '_' as i32 &&
           *data.offset(link_end as isize) as std::os::raw::c_int != '-' as i32 {
        return 0 as std::os::raw::c_int as size_t
    }
    link_end =
        (link_end as
             std::os::raw::c_ulong).wrapping_add(1 as std::os::raw::c_int as std::os::raw::c_ulong) as
            size_t as size_t;
    /* consume valid characters ([A-Za-z0-9_-/]) until we run out */
    while link_end < size &&
              (*(*__ctype_b_loc()).offset(*data.offset(link_end as isize) as
                                              std::os::raw::c_int as isize) as
                   std::os::raw::c_int &
                   _ISalnum as std::os::raw::c_int as std::os::raw::c_ushort as std::os::raw::c_int !=
                   0 ||
                   *data.offset(link_end as isize) as std::os::raw::c_int ==
                       '_' as i32 ||
                   *data.offset(link_end as isize) as std::os::raw::c_int ==
                       '/' as i32 ||
                   *data.offset(link_end as isize) as std::os::raw::c_int ==
                       '-' as i32) {
        link_end = link_end.wrapping_add(1)
    }
    /* make the link */
    bufput(link, data.offset(-(rewind as isize)) as *const std::os::raw::c_void,
           link_end.wrapping_add(rewind));
    *(borrow_mut(&mut no_slash)).unwrap() = (rewind == 1 as std::os::raw::c_int as std::os::raw::c_ulong) as std::os::raw::c_int;
    *(borrow_mut(&mut rewind_p)).unwrap() = rewind;
    return link_end;
}
use crate::laertes_rt::*;
