use ::libc;
extern "C" {
    pub type __locale_data;
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    fn __errno_location() -> *mut libc::c_int;
    fn strtod(_: *const libc::c_char, _: *mut *mut libc::c_char) -> libc::c_double;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn strncmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    fn strdup(_: *const libc::c_char) -> *mut libc::c_char;
    fn strchr(_: *const libc::c_char, _: libc::c_int) -> *mut libc::c_char;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn strncasecmp(
        _: *const libc::c_char,
        _: *const libc::c_char,
        _: libc::c_ulong,
    ) -> libc::c_int;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    fn newlocale(
        __category_mask: libc::c_int,
        __locale: *const libc::c_char,
        __base: locale_t,
    ) -> locale_t;
    fn duplocale(__dataset: locale_t) -> locale_t;
    fn freelocale(__dataset: locale_t);
    fn uselocale(__dataset: locale_t) -> locale_t;
}
pub type __uint32_t = libc::c_uint;
pub type __int64_t = libc::c_long;
pub type __uint64_t = libc::c_ulong;
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct __locale_struct {
    pub __locales: [*mut __locale_data; 13],
    pub __ctype_b: *const libc::c_ushort,
    pub __ctype_tolower: *const libc::c_int,
    pub __ctype_toupper: *const libc::c_int,
    pub __names: [*const libc::c_char; 13],
}
pub type __locale_t = *mut __locale_struct;
pub type locale_t = __locale_t;
pub type int64_t = __int64_t;
pub type uint32_t = __uint32_t;
pub type uint64_t = __uint64_t;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor14 { dummy: () }
#[derive(Copy, Clone)]

struct ErasedByPreprocessor15 { dummy: () }
pub type json_object_delete_fn = unsafe extern "C" fn(
    *mut crate::src::json_object::json_object,
    *mut libc::c_void,
) -> ();
pub type json_object_to_json_string_fn = unsafe extern "C" fn(
    *mut crate::src::json_object::json_object,
    *mut crate::src::apps::json_parse::printbuf,
    libc::c_int,
    libc::c_int,
) -> libc::c_int;
pub type json_type = libc::c_uint;
pub const json_type_string: json_type = 6;
pub const json_type_array: json_type = 5;
pub const json_type_object: json_type = 4;
pub const json_type_int: json_type = 3;
pub const json_type_double: json_type = 2;
pub const json_type_boolean: json_type = 1;
pub const json_type_null: json_type = 0;
pub type json_bool = libc::c_int;
pub type json_tokener_error = libc::c_uint;
pub const json_tokener_error_memory: json_tokener_error = 16;
pub const json_tokener_error_size: json_tokener_error = 15;
pub const json_tokener_error_parse_utf8_string: json_tokener_error = 14;
pub const json_tokener_error_parse_comment: json_tokener_error = 13;
pub const json_tokener_error_parse_string: json_tokener_error = 12;
pub const json_tokener_error_parse_object_value_sep: json_tokener_error = 11;
pub const json_tokener_error_parse_object_key_sep: json_tokener_error = 10;
pub const json_tokener_error_parse_object_key_name: json_tokener_error = 9;
pub const json_tokener_error_parse_array: json_tokener_error = 8;
pub const json_tokener_error_parse_number: json_tokener_error = 7;
pub const json_tokener_error_parse_boolean: json_tokener_error = 6;
pub const json_tokener_error_parse_null: json_tokener_error = 5;
pub const json_tokener_error_parse_unexpected: json_tokener_error = 4;
pub const json_tokener_error_parse_eof: json_tokener_error = 3;
pub const json_tokener_error_depth: json_tokener_error = 2;
pub const json_tokener_continue: json_tokener_error = 1;
pub const json_tokener_success: json_tokener_error = 0;
pub type json_tokener_state = libc::c_uint;
pub const json_tokener_state_inf: json_tokener_state = 26;
pub const json_tokener_state_object_field_start_after_sep: json_tokener_state = 25;
pub const json_tokener_state_array_after_sep: json_tokener_state = 24;
pub const json_tokener_state_object_sep: json_tokener_state = 23;
pub const json_tokener_state_object_value_add: json_tokener_state = 22;
pub const json_tokener_state_object_value: json_tokener_state = 21;
pub const json_tokener_state_object_field_end: json_tokener_state = 20;
pub const json_tokener_state_object_field: json_tokener_state = 19;
pub const json_tokener_state_object_field_start: json_tokener_state = 18;
pub const json_tokener_state_array_sep: json_tokener_state = 17;
pub const json_tokener_state_array_add: json_tokener_state = 16;
pub const json_tokener_state_array: json_tokener_state = 15;
pub const json_tokener_state_number: json_tokener_state = 14;
pub const json_tokener_state_boolean: json_tokener_state = 13;
pub const json_tokener_state_escape_unicode_need_u: json_tokener_state = 12;
pub const json_tokener_state_escape_unicode_need_escape: json_tokener_state = 11;
pub const json_tokener_state_escape_unicode: json_tokener_state = 10;
pub const json_tokener_state_string_escape: json_tokener_state = 9;
pub const json_tokener_state_string: json_tokener_state = 8;
pub const json_tokener_state_comment_end: json_tokener_state = 7;
pub const json_tokener_state_comment_eol: json_tokener_state = 6;
pub const json_tokener_state_comment: json_tokener_state = 5;
pub const json_tokener_state_comment_start: json_tokener_state = 4;
pub const json_tokener_state_null: json_tokener_state = 3;
pub const json_tokener_state_finish: json_tokener_state = 2;
pub const json_tokener_state_start: json_tokener_state = 1;
pub const json_tokener_state_eatws: json_tokener_state = 0;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor16 { dummy: () }
#[derive(Copy, Clone)]

struct ErasedByPreprocessor17 { dummy: () }
#[inline]
unsafe extern "C" fn is_ws_char(mut c: libc::c_char) -> libc::c_int {
    return (c as libc::c_int == ' ' as i32 || c as libc::c_int == '\t' as i32
        || c as libc::c_int == '\n' as i32 || c as libc::c_int == '\r' as i32)
        as libc::c_int;
}
#[inline]
unsafe extern "C" fn is_hex_char(mut c: libc::c_char) -> libc::c_int {
    return (c as libc::c_int >= '0' as i32 && c as libc::c_int <= '9' as i32
        || c as libc::c_int >= 'A' as i32 && c as libc::c_int <= 'F' as i32
        || c as libc::c_int >= 'a' as i32 && c as libc::c_int <= 'f' as i32)
        as libc::c_int;
}
static mut json_null_str: [libc::c_char; 5] = unsafe {
    *::core::mem::transmute::<&[u8; 5], &[libc::c_char; 5]>(b"null\0")
};
static mut json_null_str_len: libc::c_int = 0;
static mut json_inf_str: [libc::c_char; 9] = unsafe {
    *::core::mem::transmute::<&[u8; 9], &[libc::c_char; 9]>(b"Infinity\0")
};
static mut json_inf_str_invert: [libc::c_char; 9] = unsafe {
    *::core::mem::transmute::<&[u8; 9], &[libc::c_char; 9]>(b"iNFINITY\0")
};
static mut json_inf_str_len: libc::c_uint = 0;
static mut json_nan_str: [libc::c_char; 4] = unsafe {
    *::core::mem::transmute::<&[u8; 4], &[libc::c_char; 4]>(b"NaN\0")
};
static mut json_nan_str_len: libc::c_int = 0;
static mut json_true_str: [libc::c_char; 5] = unsafe {
    *::core::mem::transmute::<&[u8; 5], &[libc::c_char; 5]>(b"true\0")
};
static mut json_true_str_len: libc::c_int = 0;
static mut json_false_str: [libc::c_char; 6] = unsafe {
    *::core::mem::transmute::<&[u8; 6], &[libc::c_char; 6]>(b"false\0")
};
static mut json_false_str_len: libc::c_int = 0;
static mut json_tokener_errors: [*const libc::c_char; 17] = [
    b"success\0" as *const u8 as *const libc::c_char,
    b"continue\0" as *const u8 as *const libc::c_char,
    b"nesting too deep\0" as *const u8 as *const libc::c_char,
    b"unexpected end of data\0" as *const u8 as *const libc::c_char,
    b"unexpected character\0" as *const u8 as *const libc::c_char,
    b"null expected\0" as *const u8 as *const libc::c_char,
    b"boolean expected\0" as *const u8 as *const libc::c_char,
    b"number expected\0" as *const u8 as *const libc::c_char,
    b"array value separator ',' expected\0" as *const u8 as *const libc::c_char,
    b"quoted object property name expected\0" as *const u8 as *const libc::c_char,
    b"object property name separator ':' expected\0" as *const u8 as *const libc::c_char,
    b"object value separator ',' expected\0" as *const u8 as *const libc::c_char,
    b"invalid string sequence\0" as *const u8 as *const libc::c_char,
    b"expected comment\0" as *const u8 as *const libc::c_char,
    b"invalid utf-8 string\0" as *const u8 as *const libc::c_char,
    b"buffer size overflow\0" as *const u8 as *const libc::c_char,
    b"out of memory\0" as *const u8 as *const libc::c_char,
];
#[no_mangle]
pub unsafe extern "C" fn json_tokener_error_desc(
    mut jerr: json_tokener_error,
) -> *const libc::c_char {
    let mut jerr_int: libc::c_int = jerr as libc::c_int;
    if jerr_int < 0 as libc::c_int
        || jerr_int
            >= (::core::mem::size_of::<[*const libc::c_char; 17]>() as libc::c_ulong)
                .wrapping_div(
                    ::core::mem::size_of::<*const libc::c_char>() as libc::c_ulong,
                ) as libc::c_int
    {
        return b"Unknown error, invalid json_tokener_error value passed to json_tokener_error_desc()\0"
            as *const u8 as *const libc::c_char;
    }
    return json_tokener_errors[jerr as usize];
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_get_error(
    mut tok: *mut crate::src::apps::json_parse::json_tokener,
) -> json_tokener_error {
    return (*tok).err;
}
static mut utf8_replacement_char: [libc::c_uchar; 3] = [
    0xef as libc::c_int as libc::c_uchar,
    0xbf as libc::c_int as libc::c_uchar,
    0xbd as libc::c_int as libc::c_uchar,
];
#[no_mangle]
pub unsafe extern "C" fn json_tokener_new_ex(
    mut depth: libc::c_int,
) -> *mut crate::src::apps::json_parse::json_tokener {
    let mut tok: *mut crate::src::apps::json_parse::json_tokener = 0 as *mut crate::src::apps::json_parse::json_tokener;
    if depth < 1 as libc::c_int {
        return 0 as *mut crate::src::apps::json_parse::json_tokener;
    }
    tok = calloc(
        1 as libc::c_int as libc::c_ulong,
        ::core::mem::size_of::<crate::src::apps::json_parse::json_tokener>() as libc::c_ulong,
    ) as *mut crate::src::apps::json_parse::json_tokener;
    if tok.is_null() {std::intrinsics::assume((tok).addr() == 0);
        return 0 as *mut crate::src::apps::json_parse::json_tokener;
    }
    (*tok)
        .stack = calloc(
        depth as libc::c_ulong,
        ::core::mem::size_of::<crate::src::apps::json_parse::json_tokener_srec>() as libc::c_ulong,
    ) as *mut crate::src::apps::json_parse::json_tokener_srec;
    if ((*tok).stack).is_null() {std::intrinsics::assume(((*tok).stack).addr() == 0);
        free(tok as *mut libc::c_void);
        return 0 as *mut crate::src::apps::json_parse::json_tokener;
    }
    (*tok).pb = crate::src::printbuf::printbuf_new();
    if ((*tok).pb).is_null() {std::intrinsics::assume(((*tok).pb).addr() == 0);
        free((*tok).stack as *mut libc::c_void);
        free(tok as *mut libc::c_void);
        return 0 as *mut crate::src::apps::json_parse::json_tokener;
    }
    (*tok).max_depth = depth;
    json_tokener_reset(tok);
    return tok;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_new() -> *mut crate::src::apps::json_parse::json_tokener {
    return json_tokener_new_ex(32 as libc::c_int);
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_free(mut tok: *mut crate::src::apps::json_parse::json_tokener) {
    if tok.is_null() {std::intrinsics::assume((tok).addr() == 0);
        return;
    }
    json_tokener_reset(tok);
    if !((*tok).pb).is_null() {
        crate::src::printbuf::printbuf_free((*tok).pb);
    }else { std::intrinsics::assume(((*tok).pb).addr() == 0); }
    free((*tok).stack as *mut libc::c_void);
    free(tok as *mut libc::c_void);
}
unsafe extern "C" fn json_tokener_reset_level(
    mut tok: *mut crate::src::apps::json_parse::json_tokener,
    mut depth: libc::c_int,
) {
    (*((*tok).stack).offset(depth as isize)).state = json_tokener_state_eatws;
    (*((*tok).stack).offset(depth as isize)).saved_state = json_tokener_state_start;
    crate::src::json_object::json_object_put((*((*tok).stack).offset(depth as isize)).current);
    (*((*tok).stack).offset(depth as isize)).current = 0 as *mut crate::src::json_object::json_object;
    free((*((*tok).stack).offset(depth as isize)).obj_field_name as *mut libc::c_void);
    (*((*tok).stack).offset(depth as isize)).obj_field_name = 0 as *mut libc::c_char;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_reset(mut tok: *mut crate::src::apps::json_parse::json_tokener) {
    let mut i: libc::c_int = 0;
    if tok.is_null() {std::intrinsics::assume((tok).addr() == 0);
        return;
    }
    i = (*tok).depth;
    while i >= 0 as libc::c_int {
        json_tokener_reset_level(tok, i);
        i -= 1;
        i;
    }
    (*tok).depth = 0 as libc::c_int;
    (*tok).err = json_tokener_success;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_parse(
    mut str: *const libc::c_char,
) -> *mut crate::src::json_object::json_object {
    let mut jerr_ignored: json_tokener_error = json_tokener_success;
    let mut obj: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    obj = json_tokener_parse_verbose(str, &raw mut jerr_ignored);
    return obj;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_parse_verbose(
    mut str: *const libc::c_char,
    mut error: *mut json_tokener_error,
) -> *mut crate::src::json_object::json_object {
    let mut tok: *mut crate::src::apps::json_parse::json_tokener = 0 as *mut crate::src::apps::json_parse::json_tokener;
    let mut obj: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    tok = json_tokener_new();
    if tok.is_null() {std::intrinsics::assume((tok).addr() == 0);
        *error = json_tokener_error_memory;
        return 0 as *mut crate::src::json_object::json_object;
    }
    obj = json_tokener_parse_ex(tok, str, -(1 as libc::c_int));
    *error = (*tok).err;
    if (*tok).err as libc::c_uint != json_tokener_success as libc::c_int as libc::c_uint
    {
        if !obj.is_null() {
            crate::src::json_object::json_object_put(obj);
        }else { std::intrinsics::assume((obj).addr() == 0); }
        obj = 0 as *mut crate::src::json_object::json_object;
    }
    json_tokener_free(tok);
    return obj;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_parse_ex(
    mut tok: *mut crate::src::apps::json_parse::json_tokener,
    mut str: *const libc::c_char,
    mut len: libc::c_int,
) -> *mut crate::src::json_object::json_object {
    let mut case_start_0: *const libc::c_char = 0 as *const libc::c_char;
    let mut case_start: *const libc::c_char = 0 as *const libc::c_char;
    let mut case_start_3: *const libc::c_char = 0 as *const libc::c_char;
    let mut case_start_1: *const libc::c_char = 0 as *const libc::c_char;
    let mut size: libc::c_int = 0;
    let mut size_nan: libc::c_int = 0;
    let mut size1: libc::c_int = 0;
    let mut size2: libc::c_int = 0;
    let mut current_block: u64;
    let mut obj: *mut crate::src::json_object::json_object = 0 as *mut crate::src::json_object::json_object;
    let mut c: libc::c_char = '\u{1}' as i32 as libc::c_char;
    let mut nBytes: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    let mut nBytesp: *mut libc::c_uint = &raw mut nBytes;
    let mut oldlocale: locale_t = uselocale(0 as locale_t);
    let mut newloc: locale_t = 0 as *mut __locale_struct;
    (*tok).char_offset = 0 as libc::c_int;
    (*tok).err = json_tokener_success;
    if len < -(1 as libc::c_int)
        || len == -(1 as libc::c_int)
            && strlen(str) > 2147483647 as libc::c_int as libc::c_ulong
    {
        (*tok).err = json_tokener_error_size;
        return 0 as *mut crate::src::json_object::json_object;
    }
    let mut duploc: locale_t = duplocale(oldlocale);
    if duploc.is_null() && *__errno_location() == 12 as libc::c_int {
        (*tok).err = json_tokener_error_memory;
        return 0 as *mut crate::src::json_object::json_object;
    }
    newloc = newlocale(
        (1 as libc::c_int) << 1 as libc::c_int,
        b"C\0" as *const u8 as *const libc::c_char,
        duploc,
    );
    if newloc.is_null() {std::intrinsics::assume((newloc).addr() == 0);
        (*tok).err = json_tokener_error_memory;
        freelocale(duploc);
        return 0 as *mut crate::src::json_object::json_object;
    }
    uselocale(newloc);
    's_73: while if (*tok).char_offset == len {
        if (*tok).depth == 0 as libc::c_int
            && (*((*tok).stack).offset((*tok).depth as isize)).state as libc::c_uint
                == json_tokener_state_eatws as libc::c_int as libc::c_uint
            && (*((*tok).stack).offset((*tok).depth as isize)).saved_state
                as libc::c_uint
                == json_tokener_state_finish as libc::c_int as libc::c_uint
        {
            (*tok).err = json_tokener_success;
            0 as libc::c_int
        } else {
            (*tok).err = json_tokener_continue;
            0 as libc::c_int
        }
    } else if (*tok).flags & 0x10 as libc::c_int != 0
        && json_tokener_validate_utf8(*str, nBytesp) == 0
    {
        (*tok).err = json_tokener_error_parse_utf8_string;
        0 as libc::c_int
    } else {
        c = *str;
        1 as libc::c_int
    } != 0
    {
        loop {
            match (*((*tok).stack).offset((*tok).depth as isize)).state as libc::c_uint {
                0 => {
                    while is_ws_char(c) != 0 {
                        str = str.offset(1);
                        str;
                        (*tok).char_offset += 1;
                        (*tok).char_offset;
                        if c == 0
                            || (if (*tok).char_offset == len {
                                (if (*tok).depth == 0 as libc::c_int
                                    && (*((*tok).stack).offset((*tok).depth as isize)).state
                                        as libc::c_uint
                                        == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                    && (*((*tok).stack).offset((*tok).depth as isize))
                                        .saved_state as libc::c_uint
                                        == json_tokener_state_finish as libc::c_int as libc::c_uint
                                {
                                    (*tok).err = json_tokener_success;
                                    0 as libc::c_int
                                } else {
                                    (*tok).err = json_tokener_continue;
                                    0 as libc::c_int
                                })
                            } else {
                                (if (*tok).flags & 0x10 as libc::c_int != 0
                                    && json_tokener_validate_utf8(*str, nBytesp) == 0
                                {
                                    (*tok).err = json_tokener_error_parse_utf8_string;
                                    0 as libc::c_int
                                } else {
                                    c = *str;
                                    1 as libc::c_int
                                })
                            }) == 0
                        {
                            break 's_73;
                        }
                    }
                    if c as libc::c_int == '/' as i32
                        && (*tok).flags & 0x1 as libc::c_int == 0
                    {
                        crate::src::printbuf::printbuf_reset((*tok).pb);
                        if crate::src::printbuf::printbuf_memappend((*tok).pb, &raw mut c, 1 as libc::c_int)
                            < 0 as libc::c_int
                        {
                            current_block = 4495394744059808450;
                            break;
                        } else {
                            current_block = 11298138898191919651;
                            break;
                        }
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = (*((*tok).stack).offset((*tok).depth as isize))
                            .saved_state;
                    }
                }
                1 => {
                    match c as libc::c_int {
                        123 => {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_eatws;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state = json_tokener_state_object_field_start;
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = crate::src::json_object::json_object_new_object();
                            if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                current_block = 7205609094909031804;
                                break;
                            } else {
                                current_block = 2004714061185701110;
                                break;
                            }
                        }
                        91 => {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_eatws;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state = json_tokener_state_array;
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = crate::src::json_object::json_object_new_array();
                            if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                current_block = 11385396242402735691;
                                break;
                            } else {
                                current_block = 2004714061185701110;
                                break;
                            }
                        }
                        73 | 105 => {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_inf;
                            crate::src::printbuf::printbuf_reset((*tok).pb);
                            (*tok).st_pos = 0 as libc::c_int;
                        }
                        78 | 110 => {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_null;
                            crate::src::printbuf::printbuf_reset((*tok).pb);
                            (*tok).st_pos = 0 as libc::c_int;
                        }
                        39 => {
                            if (*tok).flags & 0x1 as libc::c_int != 0 {
                                current_block = 2480299350034459858;
                                break;
                            } else {
                                current_block = 4090844626922066548;
                                break;
                            }
                        }
                        34 => {
                            current_block = 4090844626922066548;
                            break;
                        }
                        84 | 116 | 70 | 102 => {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_boolean;
                            crate::src::printbuf::printbuf_reset((*tok).pb);
                            (*tok).st_pos = 0 as libc::c_int;
                        }
                        48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 | 56 | 57 | 45 => {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_number;
                            crate::src::printbuf::printbuf_reset((*tok).pb);
                            (*tok).is_double = 0 as libc::c_int;
                        }
                        _ => {
                            (*tok).err = json_tokener_error_parse_unexpected;
                            break 's_73;
                        }
                    }
                }
                2 => {
                    if (*tok).depth == 0 as libc::c_int {
                        break 's_73;
                    }
                    obj = crate::src::json_object::json_object_get(
                        (*((*tok).stack).offset((*tok).depth as isize)).current,
                    );
                    {let crown_promoted_local_0 = (*tok).depth;json_tokener_reset_level(tok, crown_promoted_local_0)};
                    (*tok).depth -= 1;
                    (*tok).depth;
                }
                26 => {
                    let mut is_negative: libc::c_int = 0 as libc::c_int;
                    while (*tok).st_pos < json_inf_str_len as libc::c_int {
                        let mut inf_char: libc::c_char = *str;
                        if inf_char as libc::c_int
                            != json_inf_str[(*tok).st_pos as usize] as libc::c_int
                            && ((*tok).flags & 0x1 as libc::c_int != 0
                                || inf_char as libc::c_int
                                    != json_inf_str_invert[(*tok).st_pos as usize]
                                        as libc::c_int)
                        {
                            (*tok).err = json_tokener_error_parse_unexpected;
                            break 's_73;
                        } else {
                            (*tok).st_pos += 1;
                            (*tok).st_pos;
                            str = str.offset(1);
                            str;
                            (*tok).char_offset += 1;
                            (*tok).char_offset;
                            if !(if (*tok).char_offset == len {
                                if (*tok).depth == 0 as libc::c_int
                                    && (*((*tok).stack).offset((*tok).depth as isize)).state
                                        as libc::c_uint
                                        == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                    && (*((*tok).stack).offset((*tok).depth as isize))
                                        .saved_state as libc::c_uint
                                        == json_tokener_state_finish as libc::c_int as libc::c_uint
                                {
                                    (*tok).err = json_tokener_success;
                                    0 as libc::c_int
                                } else {
                                    (*tok).err = json_tokener_continue;
                                    0 as libc::c_int
                                }
                            } else if (*tok).flags & 0x10 as libc::c_int != 0
                                && json_tokener_validate_utf8(*str, nBytesp) == 0
                            {
                                (*tok).err = json_tokener_error_parse_utf8_string;
                                0 as libc::c_int
                            } else {
                                c = *str;
                                1 as libc::c_int
                            } == 0)
                            {
                                continue;
                            }
                            break 's_73;
                        }
                    }
                    if (*(*tok).pb).bpos > 0 as libc::c_int
                        && *(*(*tok).pb).buf as libc::c_int == '-' as i32
                    {
                        is_negative = 1 as libc::c_int;
                    }
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .current = crate::src::json_object::json_object_new_double(
                        (if is_negative != 0 {
                            -::core::f32::INFINITY
                        } else {
                            ::core::f32::INFINITY
                        }) as libc::c_double,
                    );
                    if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                        .is_null()
                    {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .saved_state = json_tokener_state_finish;
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_eatws;
                    }
                }
                3 => {
                    size = 0;
                    size_nan = 0;
                    if crate::src::printbuf::printbuf_memappend((*tok).pb, &raw mut c, 1 as libc::c_int)
                        < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    } else {
                        size = if ((*tok).st_pos + 1 as libc::c_int) < json_null_str_len
                        {
                            (*tok).st_pos + 1 as libc::c_int
                        } else {
                            json_null_str_len
                        };
                        size_nan = if ((*tok).st_pos + 1 as libc::c_int)
                            < json_nan_str_len
                        {
                            (*tok).st_pos + 1 as libc::c_int
                        } else {
                            json_nan_str_len
                        };
                        if (*tok).flags & 0x1 as libc::c_int == 0
                            && strncasecmp(
                                json_null_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size as libc::c_ulong,
                            ) == 0 as libc::c_int
                            || strncmp(
                                json_null_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size as libc::c_ulong,
                            ) == 0 as libc::c_int
                        {
                            if !((*tok).st_pos == json_null_str_len) {
                                current_block = 15734707049249739970;
                                break;
                            }
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = 0 as *mut crate::src::json_object::json_object;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state = json_tokener_state_finish;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_eatws;
                        } else if (*tok).flags & 0x1 as libc::c_int == 0
                            && strncasecmp(
                                json_nan_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size_nan as libc::c_ulong,
                            ) == 0 as libc::c_int
                            || strncmp(
                                json_nan_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size_nan as libc::c_ulong,
                            ) == 0 as libc::c_int
                        {
                            if !((*tok).st_pos == json_nan_str_len) {
                                current_block = 15734707049249739970;
                                break;
                            }
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = crate::src::json_object::json_object_new_double(
                                ::core::f32::NAN as libc::c_double,
                            );
                            if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                (*tok).err = json_tokener_error_memory;
                                break 's_73;
                            } else {
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state = json_tokener_state_finish;
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .state = json_tokener_state_eatws;
                            }
                        } else {
                            (*tok).err = json_tokener_error_parse_null;
                            break 's_73;
                        }
                    }
                }
                4 => {
                    if c as libc::c_int == '*' as i32 {
                        current_block = 1934991416718554651;
                        break;
                    } else {
                        current_block = 2945622622075328793;
                        break;
                    }
                }
                5 => {
                    case_start = str;
                    current_block = 2463987395154258233;
                    break;
                }
                6 => {
                    case_start_0 = str;
                    current_block = 15417752026496523887;
                    break;
                }
                7 => {
                    if crate::src::printbuf::printbuf_memappend((*tok).pb, &raw mut c, 1 as libc::c_int)
                        < 0 as libc::c_int
                    {
                        current_block = 7157669805658135323;
                        break;
                    } else {
                        current_block = 850175865728824115;
                        break;
                    }
                }
                8 => {
                    case_start_1 = str;
                    current_block = 14954430942378083783;
                    break;
                }
                9 => {
                    match c as libc::c_int {
                        34 | 92 | 47 => {
                            current_block = 2885804587290726961;
                            break;
                        }
                        98 | 110 | 114 | 116 | 102 => {
                            current_block = 9200108761561101874;
                            break;
                        }
                        117 => {
                            current_block = 16605486667629353619;
                            break;
                        }
                        _ => {
                            current_block = 16506370412324142836;
                            break;
                        }
                    }
                }
                10 => {
                    current_block = 12692154259096809850;
                    break;
                }
                11 => {
                    if c == 0 || c as libc::c_int != '\\' as i32 {
                        if crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            utf8_replacement_char.as_mut_ptr() as *mut libc::c_char,
                            3 as libc::c_int,
                        ) < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break 's_73;
                        } else {
                            (*tok).high_surrogate = 0 as libc::c_int as libc::c_uint;
                            (*tok).ucs_char = 0 as libc::c_int as libc::c_uint;
                            (*tok).st_pos = 0 as libc::c_int;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state;
                        }
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_escape_unicode_need_u;
                        current_block = 2004714061185701110;
                        break;
                    }
                }
                12 => {
                    if c == 0 || c as libc::c_int != 'u' as i32 {
                        if crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            utf8_replacement_char.as_mut_ptr() as *mut libc::c_char,
                            3 as libc::c_int,
                        ) < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break 's_73;
                        } else {
                            (*tok).high_surrogate = 0 as libc::c_int as libc::c_uint;
                            (*tok).ucs_char = 0 as libc::c_int as libc::c_uint;
                            (*tok).st_pos = 0 as libc::c_int;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_string_escape;
                        }
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_escape_unicode;
                        current_block = 2004714061185701110;
                        break;
                    }
                }
                13 => {
                    size1 = 0;
                    size2 = 0;
                    if crate::src::printbuf::printbuf_memappend((*tok).pb, &raw mut c, 1 as libc::c_int)
                        < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    } else {
                        size1 = if ((*tok).st_pos + 1 as libc::c_int) < json_true_str_len
                        {
                            (*tok).st_pos + 1 as libc::c_int
                        } else {
                            json_true_str_len
                        };
                        size2 = if ((*tok).st_pos + 1 as libc::c_int)
                            < json_false_str_len
                        {
                            (*tok).st_pos + 1 as libc::c_int
                        } else {
                            json_false_str_len
                        };
                        if (*tok).flags & 0x1 as libc::c_int == 0
                            && strncasecmp(
                                json_true_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size1 as libc::c_ulong,
                            ) == 0 as libc::c_int
                            || strncmp(
                                json_true_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size1 as libc::c_ulong,
                            ) == 0 as libc::c_int
                        {
                            if !((*tok).st_pos == json_true_str_len) {
                                current_block = 10421005448780431124;
                                break;
                            }
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = crate::src::json_object::json_object_new_boolean(1 as libc::c_int);
                            if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                (*tok).err = json_tokener_error_memory;
                                break 's_73;
                            } else {
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state = json_tokener_state_finish;
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .state = json_tokener_state_eatws;
                            }
                        } else if (*tok).flags & 0x1 as libc::c_int == 0
                            && strncasecmp(
                                json_false_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size2 as libc::c_ulong,
                            ) == 0 as libc::c_int
                            || strncmp(
                                json_false_str.as_ptr(),
                                (*(*tok).pb).buf,
                                size2 as libc::c_ulong,
                            ) == 0 as libc::c_int
                        {
                            if !((*tok).st_pos == json_false_str_len) {
                                current_block = 10421005448780431124;
                                break;
                            }
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = crate::src::json_object::json_object_new_boolean(0 as libc::c_int);
                            if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                (*tok).err = json_tokener_error_memory;
                                break 's_73;
                            } else {
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state = json_tokener_state_finish;
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .state = json_tokener_state_eatws;
                            }
                        } else {
                            (*tok).err = json_tokener_error_parse_boolean;
                            break 's_73;
                        }
                    }
                }
                14 => {
                    let mut case_start_2: *const libc::c_char = str;
                    let mut case_len: libc::c_int = 0 as libc::c_int;
                    let mut is_exponent: libc::c_int = 0 as libc::c_int;
                    let mut neg_sign_ok: libc::c_int = 1 as libc::c_int;
                    let mut pos_sign_ok: libc::c_int = 0 as libc::c_int;
                    if (*(*tok).pb).bpos > 0 as libc::c_int {
                        let mut e_loc: *mut libc::c_char = strchr(
                            (*(*tok).pb).buf,
                            'e' as i32,
                        );
                        if e_loc.is_null() {std::intrinsics::assume((e_loc).addr() == 0);
                            e_loc = strchr((*(*tok).pb).buf, 'E' as i32);
                        }
                        if !e_loc.is_null() {
                            let mut last_saved_char: *mut libc::c_char = &raw mut *((*(*tok)
                                .pb)
                                .buf)
                                .offset(((*(*tok).pb).bpos - 1 as libc::c_int) as isize)
                                as *mut libc::c_char;
                            is_exponent = 1 as libc::c_int;
                            neg_sign_ok = 1 as libc::c_int;
                            pos_sign_ok = neg_sign_ok;
                            if e_loc != last_saved_char {
                                neg_sign_ok = 0 as libc::c_int;
                                pos_sign_ok = 0 as libc::c_int;
                            }
                        }else { std::intrinsics::assume((e_loc).addr() == 0); }
                    }
                    while c as libc::c_int != 0
                        && (c as libc::c_int >= '0' as i32
                            && c as libc::c_int <= '9' as i32
                            || is_exponent == 0
                                && (c as libc::c_int == 'e' as i32
                                    || c as libc::c_int == 'E' as i32)
                            || neg_sign_ok != 0 && c as libc::c_int == '-' as i32
                            || pos_sign_ok != 0 && c as libc::c_int == '+' as i32
                            || (*tok).is_double == 0 && c as libc::c_int == '.' as i32)
                    {
                        neg_sign_ok = 0 as libc::c_int;
                        pos_sign_ok = neg_sign_ok;
                        case_len += 1;
                        case_len;
                        match c as libc::c_int {
                            46 => {
                                (*tok).is_double = 1 as libc::c_int;
                                pos_sign_ok = 1 as libc::c_int;
                                neg_sign_ok = 1 as libc::c_int;
                            }
                            101 | 69 => {
                                is_exponent = 1 as libc::c_int;
                                (*tok).is_double = 1 as libc::c_int;
                                neg_sign_ok = 1 as libc::c_int;
                                pos_sign_ok = neg_sign_ok;
                            }
                            _ => {}
                        }
                        str = str.offset(1);
                        str;
                        (*tok).char_offset += 1;
                        (*tok).char_offset;
                        if !(c == 0
                            || (if (*tok).char_offset == len {
                                (if (*tok).depth == 0 as libc::c_int
                                    && (*((*tok).stack).offset((*tok).depth as isize)).state
                                        as libc::c_uint
                                        == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                    && (*((*tok).stack).offset((*tok).depth as isize))
                                        .saved_state as libc::c_uint
                                        == json_tokener_state_finish as libc::c_int as libc::c_uint
                                {
                                    (*tok).err = json_tokener_success;
                                    0 as libc::c_int
                                } else {
                                    (*tok).err = json_tokener_continue;
                                    0 as libc::c_int
                                })
                            } else {
                                (if (*tok).flags & 0x10 as libc::c_int != 0
                                    && json_tokener_validate_utf8(*str, nBytesp) == 0
                                {
                                    (*tok).err = json_tokener_error_parse_utf8_string;
                                    0 as libc::c_int
                                } else {
                                    c = *str;
                                    1 as libc::c_int
                                })
                            }) == 0)
                        {
                            continue;
                        }
                        if !(crate::src::printbuf::printbuf_memappend((*tok).pb, case_start_2, case_len)
                            < 0 as libc::c_int)
                        {
                            break 's_73;
                        }
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    }
                    if (*tok).depth > 0 as libc::c_int && c as libc::c_int != ',' as i32
                        && c as libc::c_int != ']' as i32
                        && c as libc::c_int != '}' as i32
                        && c as libc::c_int != '/' as i32
                        && c as libc::c_int != 'I' as i32
                        && c as libc::c_int != 'i' as i32 && is_ws_char(c) == 0
                    {
                        (*tok).err = json_tokener_error_parse_number;
                        break 's_73;
                    } else {
                        if case_len > 0 as libc::c_int {
                            if crate::src::printbuf::printbuf_memappend((*tok).pb, case_start_2, case_len)
                                < 0 as libc::c_int
                            {
                                (*tok).err = json_tokener_error_memory;
                                break 's_73;
                            }
                        }
                        if *((*(*tok).pb).buf).offset(0 as libc::c_int as isize)
                            as libc::c_int == '-' as i32 && case_len <= 1 as libc::c_int
                            && (c as libc::c_int == 'i' as i32
                                || c as libc::c_int == 'I' as i32)
                        {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_inf;
                            (*tok).st_pos = 0 as libc::c_int;
                        } else {
                            if (*tok).is_double != 0
                                && (*tok).flags & 0x1 as libc::c_int == 0
                            {
                                while (*(*tok).pb).bpos > 1 as libc::c_int {
                                    let mut last_char: libc::c_char = *((*(*tok).pb).buf)
                                        .offset(((*(*tok).pb).bpos - 1 as libc::c_int) as isize);
                                    if last_char as libc::c_int != 'e' as i32
                                        && last_char as libc::c_int != 'E' as i32
                                        && last_char as libc::c_int != '-' as i32
                                        && last_char as libc::c_int != '+' as i32
                                    {
                                        break;
                                    }
                                    *((*(*tok).pb).buf)
                                        .offset(
                                            ((*(*tok).pb).bpos - 1 as libc::c_int) as isize,
                                        ) = '\0' as i32 as libc::c_char;
                                    (*(*tok).pb).bpos -= 1;
                                    (*(*tok).pb).bpos;
                                }
                            }
                            let mut num64: int64_t = 0;
                            let mut numuint64: uint64_t = 0;
                            let mut numd: libc::c_double = 0.;
                            if (*tok).is_double == 0
                                && *((*(*tok).pb).buf).offset(0 as libc::c_int as isize)
                                    as libc::c_int == '-' as i32
                                && crate::src::json_util::json_parse_int64((*(*tok).pb).buf, &raw mut num64)
                                    == 0 as libc::c_int
                            {
                                if *__errno_location() == 34 as libc::c_int
                                    && (*tok).flags & 0x1 as libc::c_int != 0
                                {
                                    (*tok).err = json_tokener_error_parse_number;
                                    break 's_73;
                                } else {
                                    (*((*tok).stack)
                                        .offset((*tok).depth as isize))
                                        .current = crate::src::json_object::json_object_new_int64(num64);
                                    if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                        .is_null()
                                    {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                        (*tok).err = json_tokener_error_memory;
                                        break 's_73;
                                    }
                                }
                            } else if (*tok).is_double == 0
                                && *((*(*tok).pb).buf).offset(0 as libc::c_int as isize)
                                    as libc::c_int != '-' as i32
                                && crate::src::json_util::json_parse_uint64((*(*tok).pb).buf, &raw mut numuint64)
                                    == 0 as libc::c_int
                            {
                                if *__errno_location() == 34 as libc::c_int
                                    && (*tok).flags & 0x1 as libc::c_int != 0
                                {
                                    (*tok).err = json_tokener_error_parse_number;
                                    break 's_73;
                                } else if numuint64 != 0
                                    && *((*(*tok).pb).buf).offset(0 as libc::c_int as isize)
                                        as libc::c_int == '0' as i32
                                    && (*tok).flags & 0x1 as libc::c_int != 0
                                {
                                    (*tok).err = json_tokener_error_parse_number;
                                    break 's_73;
                                } else if numuint64
                                    <= 9223372036854775807 as libc::c_long as uint64_t
                                {
                                    num64 = numuint64 as int64_t;
                                    (*((*tok).stack)
                                        .offset((*tok).depth as isize))
                                        .current = crate::src::json_object::json_object_new_int64(num64);
                                    if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                        .is_null()
                                    {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                        (*tok).err = json_tokener_error_memory;
                                        break 's_73;
                                    }
                                } else {
                                    (*((*tok).stack)
                                        .offset((*tok).depth as isize))
                                        .current = crate::src::json_object::json_object_new_uint64(numuint64);
                                    if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                        .is_null()
                                    {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                        (*tok).err = json_tokener_error_memory;
                                        break 's_73;
                                    }
                                }
                            } else if (*tok).is_double != 0
                                && json_tokener_parse_double(
                                    (*(*tok).pb).buf,
                                    (*(*tok).pb).bpos,
                                    &raw mut numd,
                                ) == 0 as libc::c_int
                            {
                                (*((*tok).stack)
                                    .offset((*tok).depth as isize))
                                    .current = crate::src::json_object::json_object_new_double_s(numd, (*(*tok).pb).buf);
                                if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                    .is_null()
                                {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                    (*tok).err = json_tokener_error_memory;
                                    break 's_73;
                                }
                            } else {
                                (*tok).err = json_tokener_error_parse_number;
                                break 's_73;
                            }
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state = json_tokener_state_finish;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_eatws;
                        }
                    }
                }
                24 | 15 => {
                    if c as libc::c_int == ']' as i32 {
                        crate::src::json_object::json_object_array_shrink(
                            (*((*tok).stack).offset((*tok).depth as isize)).current,
                            0 as libc::c_int,
                        );
                        if (*((*tok).stack).offset((*tok).depth as isize)).state
                            as libc::c_uint
                            == json_tokener_state_array_after_sep as libc::c_int
                                as libc::c_uint && (*tok).flags & 0x1 as libc::c_int != 0
                        {
                            current_block = 16949540058562936590;
                            break;
                        } else {
                            current_block = 12467499376334016911;
                            break;
                        }
                    } else if (*tok).depth >= (*tok).max_depth - 1 as libc::c_int {
                        (*tok).err = json_tokener_error_depth;
                        break 's_73;
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_array_add;
                        (*tok).depth += 1;
                        (*tok).depth;
                        {let crown_promoted_local_1 = (*tok).depth;json_tokener_reset_level(tok, crown_promoted_local_1)};
                    }
                }
                16 => {
                    if crate::src::json_object::json_object_array_add(
                        (*((*tok).stack).offset((*tok).depth as isize)).current,
                        obj,
                    ) != 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .saved_state = json_tokener_state_array_sep;
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_eatws;
                    }
                }
                17 => {
                    if c as libc::c_int == ']' as i32 {
                        current_block = 6691704840718255488;
                        break;
                    } else {
                        current_block = 8642424805608018535;
                        break;
                    }
                }
                18 | 25 => {
                    if c as libc::c_int == '}' as i32 {
                        current_block = 18198260928557415469;
                        break;
                    } else {
                        current_block = 16124761010012532485;
                        break;
                    }
                }
                19 => {
                    case_start_3 = str;
                    current_block = 15113421229718767161;
                    break;
                }
                20 => {
                    if c as libc::c_int == ':' as i32 {
                        current_block = 5571491539924227058;
                        break;
                    } else {
                        current_block = 14696774684417902900;
                        break;
                    }
                }
                21 => {
                    if (*tok).depth >= (*tok).max_depth - 1 as libc::c_int {
                        (*tok).err = json_tokener_error_depth;
                        break 's_73;
                    } else {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_object_value_add;
                        (*tok).depth += 1;
                        (*tok).depth;
                        {let crown_promoted_local_2 = (*tok).depth;json_tokener_reset_level(tok, crown_promoted_local_2)};
                    }
                }
                22 => {
                    if crate::src::json_object::json_object_object_add(
                        (*((*tok).stack).offset((*tok).depth as isize)).current,
                        (*((*tok).stack).offset((*tok).depth as isize)).obj_field_name,
                        obj,
                    ) != 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    } else {
                        free(
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .obj_field_name as *mut libc::c_void,
                        );
                        (*((*tok).stack)
                            .offset((*tok).depth as isize))
                            .obj_field_name = 0 as *mut libc::c_char;
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .saved_state = json_tokener_state_object_sep;
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = json_tokener_state_eatws;
                    }
                }
                23 => {
                    if c as libc::c_int == '}' as i32 {
                        current_block = 16939702945023487982;
                        break;
                    } else {
                        current_block = 6031918995612662703;
                        break;
                    }
                }
                _ => {
                    current_block = 2004714061185701110;
                    break;
                }
            }
        }
        match current_block {
            15417752026496523887 => {
                while c as libc::c_int != '\n' as i32 {
                    str = str.offset(1);
                    str;
                    (*tok).char_offset += 1;
                    (*tok).char_offset;
                    if !(c == 0
                        || (if (*tok).char_offset == len {
                            (if (*tok).depth == 0 as libc::c_int
                                && (*((*tok).stack).offset((*tok).depth as isize)).state
                                    as libc::c_uint
                                    == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                && (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state as libc::c_uint
                                    == json_tokener_state_finish as libc::c_int as libc::c_uint
                            {
                                (*tok).err = json_tokener_success;
                                0 as libc::c_int
                            } else {
                                (*tok).err = json_tokener_continue;
                                0 as libc::c_int
                            })
                        } else {
                            (if (*tok).flags & 0x10 as libc::c_int != 0
                                && json_tokener_validate_utf8(*str, nBytesp) == 0
                            {
                                (*tok).err = json_tokener_error_parse_utf8_string;
                                0 as libc::c_int
                            } else {
                                c = *str;
                                1 as libc::c_int
                            })
                        }) == 0)
                    {
                        continue;
                    }
                    if !({let crown_promoted_local_3 = str.offset_from(case_start_0) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        case_start_0,
                        crown_promoted_local_3,
                    )} < 0 as libc::c_int)
                    {
                        break 's_73;
                    }
                    (*tok).err = json_tokener_error_memory;
                    break 's_73;
                }
                if {let crown_promoted_local_4 = str.offset_from(case_start_0) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                    (*tok).pb,
                    case_start_0,
                    crown_promoted_local_4,
                )} < 0 as libc::c_int
                {
                    (*tok).err = json_tokener_error_memory;
                    break;
                } else {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_eatws;
                }
                current_block = 2004714061185701110;
            }
            2463987395154258233 => {
                while c as libc::c_int != '*' as i32 {
                    str = str.offset(1);
                    str;
                    (*tok).char_offset += 1;
                    (*tok).char_offset;
                    if !(c == 0
                        || (if (*tok).char_offset == len {
                            (if (*tok).depth == 0 as libc::c_int
                                && (*((*tok).stack).offset((*tok).depth as isize)).state
                                    as libc::c_uint
                                    == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                && (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state as libc::c_uint
                                    == json_tokener_state_finish as libc::c_int as libc::c_uint
                            {
                                (*tok).err = json_tokener_success;
                                0 as libc::c_int
                            } else {
                                (*tok).err = json_tokener_continue;
                                0 as libc::c_int
                            })
                        } else {
                            (if (*tok).flags & 0x10 as libc::c_int != 0
                                && json_tokener_validate_utf8(*str, nBytesp) == 0
                            {
                                (*tok).err = json_tokener_error_parse_utf8_string;
                                0 as libc::c_int
                            } else {
                                c = *str;
                                1 as libc::c_int
                            })
                        }) == 0)
                    {
                        continue;
                    }
                    if !({let crown_promoted_local_5 = str.offset_from(case_start) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        case_start,
                        crown_promoted_local_5,
                    )} < 0 as libc::c_int)
                    {
                        break 's_73;
                    }
                    (*tok).err = json_tokener_error_memory;
                    break 's_73;
                }
                if {let crown_promoted_local_6 = str.offset(1 as libc::c_int as isize).offset_from(case_start)
                        as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                    (*tok).pb,
                    case_start,
                    crown_promoted_local_6,
                )} < 0 as libc::c_int
                {
                    (*tok).err = json_tokener_error_memory;
                    break;
                } else {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_comment_end;
                }
                current_block = 2004714061185701110;
            }
            6031918995612662703 => {
                if c as libc::c_int == ',' as i32 {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .saved_state = json_tokener_state_object_field_start_after_sep;
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_eatws;
                } else {
                    (*tok).err = json_tokener_error_parse_object_value_sep;
                    break;
                }
                current_block = 2004714061185701110;
            }
            15113421229718767161 => {
                loop {
                    if c as libc::c_int == (*tok).quote_char as libc::c_int {
                        if {let crown_promoted_local_7 = str.offset_from(case_start_3) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            case_start_3,
                            crown_promoted_local_7,
                        )} < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break 's_73;
                        } else {
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .obj_field_name = strdup((*(*tok).pb).buf);
                            if ((*((*tok).stack).offset((*tok).depth as isize))
                                .obj_field_name)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).obj_field_name).addr() == 0);
                                (*tok).err = json_tokener_error_memory;
                                break 's_73;
                            } else {
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state = json_tokener_state_object_field_end;
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .state = json_tokener_state_eatws;
                                break;
                            }
                        }
                    } else if c as libc::c_int == '\\' as i32 {
                        if {let crown_promoted_local_8 = str.offset_from(case_start_3) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            case_start_3,
                            crown_promoted_local_8,
                        )} < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break 's_73;
                        } else {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state = json_tokener_state_object_field;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_string_escape;
                            break;
                        }
                    } else {
                        str = str.offset(1);
                        str;
                        (*tok).char_offset += 1;
                        (*tok).char_offset;
                        if !(c == 0
                            || (if (*tok).char_offset == len {
                                (if (*tok).depth == 0 as libc::c_int
                                    && (*((*tok).stack).offset((*tok).depth as isize)).state
                                        as libc::c_uint
                                        == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                    && (*((*tok).stack).offset((*tok).depth as isize))
                                        .saved_state as libc::c_uint
                                        == json_tokener_state_finish as libc::c_int as libc::c_uint
                                {
                                    (*tok).err = json_tokener_success;
                                    0 as libc::c_int
                                } else {
                                    (*tok).err = json_tokener_continue;
                                    0 as libc::c_int
                                })
                            } else {
                                (if (*tok).flags & 0x10 as libc::c_int != 0
                                    && json_tokener_validate_utf8(*str, nBytesp) == 0
                                {
                                    (*tok).err = json_tokener_error_parse_utf8_string;
                                    0 as libc::c_int
                                } else {
                                    c = *str;
                                    1 as libc::c_int
                                })
                            }) == 0)
                        {
                            continue;
                        }
                        if !({let crown_promoted_local_9 = str.offset_from(case_start_3) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            case_start_3,
                            crown_promoted_local_9,
                        )} < 0 as libc::c_int)
                        {
                            break 's_73;
                        }
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    }
                }
                current_block = 2004714061185701110;
            }
            16124761010012532485 => {
                if c as libc::c_int == '"' as i32 || c as libc::c_int == '\'' as i32 {
                    (*tok).quote_char = c;
                    crate::src::printbuf::printbuf_reset((*tok).pb);
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_object_field;
                } else {
                    (*tok).err = json_tokener_error_parse_object_key_name;
                    break;
                }
                current_block = 2004714061185701110;
            }
            18198260928557415469 => {
                if (*((*tok).stack).offset((*tok).depth as isize)).state as libc::c_uint
                    == json_tokener_state_object_field_start_after_sep as libc::c_int
                        as libc::c_uint && (*tok).flags & 0x1 as libc::c_int != 0
                {
                    (*tok).err = json_tokener_error_parse_unexpected;
                    break;
                } else {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .saved_state = json_tokener_state_finish;
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_eatws;
                }
                current_block = 2004714061185701110;
            }
            8642424805608018535 => {
                if c as libc::c_int == ',' as i32 {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .saved_state = json_tokener_state_array_after_sep;
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_eatws;
                } else {
                    (*tok).err = json_tokener_error_parse_array;
                    break;
                }
                current_block = 2004714061185701110;
            }
            12467499376334016911 => {
                (*((*tok).stack).offset((*tok).depth as isize))
                    .saved_state = json_tokener_state_finish;
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_eatws;
                current_block = 2004714061185701110;
            }
            14954430942378083783 => {
                loop {
                    if c as libc::c_int == (*tok).quote_char as libc::c_int {
                        if {let crown_promoted_local_10 = str.offset_from(case_start_1) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            case_start_1,
                            crown_promoted_local_10,
                        )} < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break 's_73;
                        } else {
                            (*((*tok).stack)
                                .offset((*tok).depth as isize))
                                .current = crate::src::json_object::json_object_new_string_len(
                                (*(*tok).pb).buf,
                                (*(*tok).pb).bpos,
                            );
                            if ((*((*tok).stack).offset((*tok).depth as isize)).current)
                                .is_null()
                            {std::intrinsics::assume(((*(*tok).stack.offset((*tok).depth as isize)).current).addr() == 0);
                                (*tok).err = json_tokener_error_memory;
                                break 's_73;
                            } else {
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state = json_tokener_state_finish;
                                (*((*tok).stack).offset((*tok).depth as isize))
                                    .state = json_tokener_state_eatws;
                                break;
                            }
                        }
                    } else if c as libc::c_int == '\\' as i32 {
                        if {let crown_promoted_local_11 = str.offset_from(case_start_1) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            case_start_1,
                            crown_promoted_local_11,
                        )} < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break 's_73;
                        } else {
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .saved_state = json_tokener_state_string;
                            (*((*tok).stack).offset((*tok).depth as isize))
                                .state = json_tokener_state_string_escape;
                            break;
                        }
                    } else if (*tok).flags & 0x1 as libc::c_int != 0
                        && c as libc::c_uchar as libc::c_int <= 0x1f as libc::c_int
                    {
                        (*tok).err = json_tokener_error_parse_string;
                        break 's_73;
                    } else {
                        str = str.offset(1);
                        str;
                        (*tok).char_offset += 1;
                        (*tok).char_offset;
                        if !(c == 0
                            || (if (*tok).char_offset == len {
                                (if (*tok).depth == 0 as libc::c_int
                                    && (*((*tok).stack).offset((*tok).depth as isize)).state
                                        as libc::c_uint
                                        == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                    && (*((*tok).stack).offset((*tok).depth as isize))
                                        .saved_state as libc::c_uint
                                        == json_tokener_state_finish as libc::c_int as libc::c_uint
                                {
                                    (*tok).err = json_tokener_success;
                                    0 as libc::c_int
                                } else {
                                    (*tok).err = json_tokener_continue;
                                    0 as libc::c_int
                                })
                            } else {
                                (if (*tok).flags & 0x10 as libc::c_int != 0
                                    && json_tokener_validate_utf8(*str, nBytesp) == 0
                                {
                                    (*tok).err = json_tokener_error_parse_utf8_string;
                                    0 as libc::c_int
                                } else {
                                    c = *str;
                                    1 as libc::c_int
                                })
                            }) == 0)
                        {
                            continue;
                        }
                        if !({let crown_promoted_local_12 = str.offset_from(case_start_1) as libc::c_long as libc::c_int;crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            case_start_1,
                            crown_promoted_local_12,
                        )} < 0 as libc::c_int)
                        {
                            break 's_73;
                        }
                        (*tok).err = json_tokener_error_memory;
                        break 's_73;
                    }
                }
                current_block = 2004714061185701110;
            }
            12692154259096809850 => {
                loop {
                    if c == 0 || is_hex_char(c) == 0 {
                        (*tok).err = json_tokener_error_parse_string;
                        break 's_73;
                    } else {
                        (*tok).ucs_char
                            |= ((if c as libc::c_int <= '9' as i32 {
                                c as libc::c_int - '0' as i32
                            } else {
                                (c as libc::c_int & 7 as libc::c_int) + 9 as libc::c_int
                            }) as libc::c_uint)
                                << (3 as libc::c_int - (*tok).st_pos) * 4 as libc::c_int;
                        (*tok).st_pos += 1;
                        (*tok).st_pos;
                        if (*tok).st_pos >= 4 as libc::c_int {
                            break;
                        }
                        str = str.offset(1);
                        str;
                        (*tok).char_offset += 1;
                        (*tok).char_offset;
                        if !(if (*tok).char_offset == len {
                            if (*tok).depth == 0 as libc::c_int
                                && (*((*tok).stack).offset((*tok).depth as isize)).state
                                    as libc::c_uint
                                    == json_tokener_state_eatws as libc::c_int as libc::c_uint
                                && (*((*tok).stack).offset((*tok).depth as isize))
                                    .saved_state as libc::c_uint
                                    == json_tokener_state_finish as libc::c_int as libc::c_uint
                            {
                                (*tok).err = json_tokener_success;
                                0 as libc::c_int
                            } else {
                                (*tok).err = json_tokener_continue;
                                0 as libc::c_int
                            }
                        } else if (*tok).flags & 0x10 as libc::c_int != 0
                            && json_tokener_validate_utf8(*str, nBytesp) == 0
                        {
                            (*tok).err = json_tokener_error_parse_utf8_string;
                            0 as libc::c_int
                        } else {
                            c = *str;
                            1 as libc::c_int
                        } == 0)
                        {
                            continue;
                        }
                        break 's_73;
                    }
                }
                (*tok).st_pos = 0 as libc::c_int;
                if (*tok).high_surrogate != 0 {
                    if (*tok).ucs_char & 0xfc00 as libc::c_int as libc::c_uint
                        == 0xdc00 as libc::c_int as libc::c_uint
                    {
                        (*tok)
                            .ucs_char = (((*tok).high_surrogate
                            & 0x3ff as libc::c_int as libc::c_uint) << 10 as libc::c_int)
                            .wrapping_add(
                                (*tok).ucs_char & 0x3ff as libc::c_int as libc::c_uint,
                            )
                            .wrapping_add(0x10000 as libc::c_int as libc::c_uint);
                    } else if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        utf8_replacement_char.as_mut_ptr() as *mut libc::c_char,
                        3 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                    (*tok).high_surrogate = 0 as libc::c_int as libc::c_uint;
                }
                if (*tok).ucs_char < 0x80 as libc::c_int as libc::c_uint {
                    let mut unescaped_utf: [libc::c_uchar; 1] = [0; 1];
                    unescaped_utf[0 as libc::c_int
                        as usize] = (*tok).ucs_char as libc::c_uchar;
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        unescaped_utf.as_mut_ptr() as *mut libc::c_char,
                        1 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    } else {
                        current_block = 6531417090144833949;
                    }
                } else if (*tok).ucs_char < 0x800 as libc::c_int as libc::c_uint {
                    let mut unescaped_utf_0: [libc::c_uchar; 2] = [0; 2];
                    unescaped_utf_0[0 as libc::c_int
                        as usize] = (0xc0 as libc::c_int as libc::c_uint
                        | (*tok).ucs_char >> 6 as libc::c_int) as libc::c_uchar;
                    unescaped_utf_0[1 as libc::c_int
                        as usize] = (0x80 as libc::c_int as libc::c_uint
                        | (*tok).ucs_char & 0x3f as libc::c_int as libc::c_uint)
                        as libc::c_uchar;
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        unescaped_utf_0.as_mut_ptr() as *mut libc::c_char,
                        2 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    } else {
                        current_block = 6531417090144833949;
                    }
                } else if (*tok).ucs_char & 0xfc00 as libc::c_int as libc::c_uint
                    == 0xd800 as libc::c_int as libc::c_uint
                {
                    (*tok).high_surrogate = (*tok).ucs_char;
                    (*tok).ucs_char = 0 as libc::c_int as libc::c_uint;
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_escape_unicode_need_escape;
                    current_block = 2004714061185701110;
                } else {
                    if (*tok).ucs_char & 0xfc00 as libc::c_int as libc::c_uint
                        == 0xdc00 as libc::c_int as libc::c_uint
                    {
                        if crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            utf8_replacement_char.as_mut_ptr() as *mut libc::c_char,
                            3 as libc::c_int,
                        ) < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break;
                        }
                    } else if (*tok).ucs_char < 0x10000 as libc::c_int as libc::c_uint {
                        let mut unescaped_utf_1: [libc::c_uchar; 3] = [0; 3];
                        unescaped_utf_1[0 as libc::c_int
                            as usize] = (0xe0 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char >> 12 as libc::c_int) as libc::c_uchar;
                        unescaped_utf_1[1 as libc::c_int
                            as usize] = (0x80 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char >> 6 as libc::c_int
                                & 0x3f as libc::c_int as libc::c_uint) as libc::c_uchar;
                        unescaped_utf_1[2 as libc::c_int
                            as usize] = (0x80 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char & 0x3f as libc::c_int as libc::c_uint)
                            as libc::c_uchar;
                        if crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            unescaped_utf_1.as_mut_ptr() as *mut libc::c_char,
                            3 as libc::c_int,
                        ) < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break;
                        }
                    } else if (*tok).ucs_char < 0x110000 as libc::c_int as libc::c_uint {
                        let mut unescaped_utf_2: [libc::c_uchar; 4] = [0; 4];
                        unescaped_utf_2[0 as libc::c_int
                            as usize] = (0xf0 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char >> 18 as libc::c_int
                                & 0x7 as libc::c_int as libc::c_uint) as libc::c_uchar;
                        unescaped_utf_2[1 as libc::c_int
                            as usize] = (0x80 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char >> 12 as libc::c_int
                                & 0x3f as libc::c_int as libc::c_uint) as libc::c_uchar;
                        unescaped_utf_2[2 as libc::c_int
                            as usize] = (0x80 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char >> 6 as libc::c_int
                                & 0x3f as libc::c_int as libc::c_uint) as libc::c_uchar;
                        unescaped_utf_2[3 as libc::c_int
                            as usize] = (0x80 as libc::c_int as libc::c_uint
                            | (*tok).ucs_char & 0x3f as libc::c_int as libc::c_uint)
                            as libc::c_uchar;
                        if crate::src::printbuf::printbuf_memappend(
                            (*tok).pb,
                            unescaped_utf_2.as_mut_ptr() as *mut libc::c_char,
                            4 as libc::c_int,
                        ) < 0 as libc::c_int
                        {
                            (*tok).err = json_tokener_error_memory;
                            break;
                        }
                    } else if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        utf8_replacement_char.as_mut_ptr() as *mut libc::c_char,
                        3 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                    current_block = 6531417090144833949;
                }
                match current_block {
                    2004714061185701110 => {}
                    _ => {
                        (*((*tok).stack).offset((*tok).depth as isize))
                            .state = (*((*tok).stack).offset((*tok).depth as isize))
                            .saved_state;
                        current_block = 2004714061185701110;
                    }
                }
            }
            16605486667629353619 => {
                (*tok).ucs_char = 0 as libc::c_int as libc::c_uint;
                (*tok).st_pos = 0 as libc::c_int;
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_escape_unicode;
                current_block = 2004714061185701110;
            }
            9200108761561101874 => {
                if c as libc::c_int == 'b' as i32 {
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        b"\x08\0" as *const u8 as *const libc::c_char,
                        1 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                } else if c as libc::c_int == 'n' as i32 {
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        b"\n\0" as *const u8 as *const libc::c_char,
                        1 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                } else if c as libc::c_int == 'r' as i32 {
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        b"\r\0" as *const u8 as *const libc::c_char,
                        1 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                } else if c as libc::c_int == 't' as i32 {
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        b"\t\0" as *const u8 as *const libc::c_char,
                        1 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                } else if c as libc::c_int == 'f' as i32 {
                    if crate::src::printbuf::printbuf_memappend(
                        (*tok).pb,
                        b"\x0C\0" as *const u8 as *const libc::c_char,
                        1 as libc::c_int,
                    ) < 0 as libc::c_int
                    {
                        (*tok).err = json_tokener_error_memory;
                        break;
                    }
                }
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = (*((*tok).stack).offset((*tok).depth as isize)).saved_state;
                current_block = 2004714061185701110;
            }
            2885804587290726961 => {
                if crate::src::printbuf::printbuf_memappend((*tok).pb, &raw mut c, 1 as libc::c_int)
                    < 0 as libc::c_int
                {
                    (*tok).err = json_tokener_error_memory;
                    break;
                } else {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = (*((*tok).stack).offset((*tok).depth as isize))
                        .saved_state;
                }
                current_block = 2004714061185701110;
            }
            2945622622075328793 => {
                if c as libc::c_int == '/' as i32 {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_comment_eol;
                } else {
                    (*tok).err = json_tokener_error_parse_comment;
                    break;
                }
                current_block = 4804377075063615140;
            }
            4090844626922066548 => {
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_string;
                crate::src::printbuf::printbuf_reset((*tok).pb);
                (*tok).quote_char = c;
                current_block = 2004714061185701110;
            }
            16949540058562936590 => {
                (*tok).err = json_tokener_error_parse_unexpected;
                break;
            }
            850175865728824115 => {
                if c as libc::c_int == '/' as i32 {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_eatws;
                } else {
                    (*((*tok).stack).offset((*tok).depth as isize))
                        .state = json_tokener_state_comment;
                }
                current_block = 2004714061185701110;
            }
            16506370412324142836 => {
                (*tok).err = json_tokener_error_parse_string;
                break;
            }
            14696774684417902900 => {
                (*tok).err = json_tokener_error_parse_object_key_sep;
                break;
            }
            11298138898191919651 => {
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_comment_start;
                current_block = 2004714061185701110;
            }
            7205609094909031804 => {
                (*tok).err = json_tokener_error_memory;
                break;
            }
            11385396242402735691 => {
                (*tok).err = json_tokener_error_memory;
                break;
            }
            2480299350034459858 => {
                (*tok).err = json_tokener_error_parse_unexpected;
                break;
            }
            4495394744059808450 => {
                (*tok).err = json_tokener_error_memory;
                break;
            }
            16939702945023487982 => {
                (*((*tok).stack).offset((*tok).depth as isize))
                    .saved_state = json_tokener_state_finish;
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_eatws;
                current_block = 2004714061185701110;
            }
            5571491539924227058 => {
                (*((*tok).stack).offset((*tok).depth as isize))
                    .saved_state = json_tokener_state_object_value;
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_eatws;
                current_block = 2004714061185701110;
            }
            15734707049249739970 => {
                (*tok).st_pos += 1;
                (*tok).st_pos;
                current_block = 2004714061185701110;
            }
            6691704840718255488 => {
                crate::src::json_object::json_object_array_shrink(
                    (*((*tok).stack).offset((*tok).depth as isize)).current,
                    0 as libc::c_int,
                );
                (*((*tok).stack).offset((*tok).depth as isize))
                    .saved_state = json_tokener_state_finish;
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_eatws;
                current_block = 2004714061185701110;
            }
            7157669805658135323 => {
                (*tok).err = json_tokener_error_memory;
                break;
            }
            1934991416718554651 => {
                (*((*tok).stack).offset((*tok).depth as isize))
                    .state = json_tokener_state_comment;
                current_block = 4804377075063615140;
            }
            10421005448780431124 => {
                (*tok).st_pos += 1;
                (*tok).st_pos;
                current_block = 2004714061185701110;
            }
            _ => {}
        }
        match current_block {
            4804377075063615140 => {
                if crate::src::printbuf::printbuf_memappend((*tok).pb, &raw mut c, 1 as libc::c_int)
                    < 0 as libc::c_int
                {
                    (*tok).err = json_tokener_error_memory;
                    break;
                }
            }
            _ => {}
        }
        str = str.offset(1);
        str;
        (*tok).char_offset += 1;
        (*tok).char_offset;
        if c == 0 {
            break;
        }
    }
    if (*tok).flags & 0x10 as libc::c_int != 0
        && nBytes != 0 as libc::c_int as libc::c_uint
    {
        (*tok).err = json_tokener_error_parse_utf8_string;
    }
    if c as libc::c_int != 0
        && (*((*tok).stack).offset((*tok).depth as isize)).state as libc::c_uint
            == json_tokener_state_finish as libc::c_int as libc::c_uint
        && (*tok).depth == 0 as libc::c_int
        && (*tok).flags & (0x1 as libc::c_int | 0x2 as libc::c_int) == 0x1 as libc::c_int
    {
        (*tok).err = json_tokener_error_parse_unexpected;
    }
    if c == 0 {
        if (*((*tok).stack).offset((*tok).depth as isize)).state as libc::c_uint
            != json_tokener_state_finish as libc::c_int as libc::c_uint
            && (*((*tok).stack).offset((*tok).depth as isize)).saved_state
                as libc::c_uint
                != json_tokener_state_finish as libc::c_int as libc::c_uint
        {
            (*tok).err = json_tokener_error_parse_eof;
        }
    }
    uselocale(oldlocale);
    freelocale(newloc);
    if (*tok).err as libc::c_uint == json_tokener_success as libc::c_int as libc::c_uint
    {
        let mut ret: *mut crate::src::json_object::json_object = crate::src::json_object::json_object_get(
            (*((*tok).stack).offset((*tok).depth as isize)).current,
        );
        let mut ii: libc::c_int = 0;
        ii = (*tok).depth;
        while ii >= 0 as libc::c_int {
            json_tokener_reset_level(tok, ii);
            ii -= 1;
            ii;
        }
        return ret;
    }
    return 0 as *mut crate::src::json_object::json_object;
}
unsafe extern "C" fn json_tokener_validate_utf8(
    c: libc::c_char,
    mut nBytes: *mut libc::c_uint,
) -> json_bool {
    let mut chr: libc::c_uchar = c as libc::c_uchar;
    if *nBytes == 0 as libc::c_int as libc::c_uint {
        if chr as libc::c_int >= 0x80 as libc::c_int {
            if chr as libc::c_int & 0xe0 as libc::c_int == 0xc0 as libc::c_int {
                *nBytes = 1 as libc::c_int as libc::c_uint;
            } else if chr as libc::c_int & 0xf0 as libc::c_int == 0xe0 as libc::c_int {
                *nBytes = 2 as libc::c_int as libc::c_uint;
            } else if chr as libc::c_int & 0xf8 as libc::c_int == 0xf0 as libc::c_int {
                *nBytes = 3 as libc::c_int as libc::c_uint;
            } else {
                return 0 as libc::c_int
            }
        }
    } else {
        if chr as libc::c_int & 0xc0 as libc::c_int != 0x80 as libc::c_int {
            return 0 as libc::c_int;
        }
        *nBytes = (*nBytes).wrapping_sub(1);
        *nBytes;
    }
    return 1 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_set_flags(
    mut tok: *mut crate::src::apps::json_parse::json_tokener,
    mut flags: libc::c_int,
) {
    (*tok).flags = flags;
}
#[no_mangle]
pub unsafe extern "C" fn json_tokener_get_parse_end(
    mut tok: *mut crate::src::apps::json_parse::json_tokener,
) -> size_t {
    if (*tok).char_offset >= 0 as libc::c_int {} else {
        __assert_fail(
            b"tok->char_offset >= 0\0" as *const u8 as *const libc::c_char,
            b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/json_tokener.c\0"
                as *const u8 as *const libc::c_char,
            1399 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 57],
                &[libc::c_char; 57],
            >(b"size_t json_tokener_get_parse_end(struct json_tokener *)\0"))
                .as_ptr(),
        );
    }
    'c_7231: {
        if (*tok).char_offset >= 0 as libc::c_int {} else {
            __assert_fail(
                b"tok->char_offset >= 0\0" as *const u8 as *const libc::c_char,
                b"/home/enumclass/Documents/C2RustTranslation/bkp/json-c/json_tokener.c\0"
                    as *const u8 as *const libc::c_char,
                1399 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 57],
                    &[libc::c_char; 57],
                >(b"size_t json_tokener_get_parse_end(struct json_tokener *)\0"))
                    .as_ptr(),
            );
        }
    };
    return (*tok).char_offset as size_t;
}
unsafe extern "C" fn json_tokener_parse_double(
    mut buf: *const libc::c_char,
    mut len: libc::c_int,
    mut retval: *mut libc::c_double,
) -> libc::c_int {
    let mut end: *mut libc::c_char = 0 as *mut libc::c_char;
    *retval = strtod(buf, &raw mut end);
    if buf.offset(len as isize) == end as *const libc::c_char {
        return 0 as libc::c_int;
    }
    return 1 as libc::c_int;
}
unsafe extern "C" fn run_static_initializers() {
    json_null_str_len = (::core::mem::size_of::<[libc::c_char; 5]>() as libc::c_ulong)
        .wrapping_sub(1 as libc::c_int as libc::c_ulong) as libc::c_int;
    json_inf_str_len = (::core::mem::size_of::<[libc::c_char; 9]>() as libc::c_ulong)
        .wrapping_sub(1 as libc::c_int as libc::c_ulong) as libc::c_uint;
    json_nan_str_len = (::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong)
        .wrapping_sub(1 as libc::c_int as libc::c_ulong) as libc::c_int;
    json_true_str_len = (::core::mem::size_of::<[libc::c_char; 5]>() as libc::c_ulong)
        .wrapping_sub(1 as libc::c_int as libc::c_ulong) as libc::c_int;
    json_false_str_len = (::core::mem::size_of::<[libc::c_char; 6]>() as libc::c_ulong)
        .wrapping_sub(1 as libc::c_int as libc::c_ulong) as libc::c_int;
}
#[used]
#[cfg_attr(target_os = "linux", link_section = ".init_array")]
#[cfg_attr(target_os = "windows", link_section = ".CRT$XIB")]
#[cfg_attr(target_os = "macos", link_section = "__DATA,__mod_init_func")]
static INIT_ARRAY: [unsafe extern "C" fn(); 1] = [run_static_initializers];
