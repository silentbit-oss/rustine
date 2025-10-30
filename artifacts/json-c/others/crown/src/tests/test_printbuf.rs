use ::libc;
extern "C" {
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
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
    
    
    
    
    
    
    
}
#[derive(Copy, Clone)]

struct ErasedByPreprocessor47 { dummy: () }
unsafe extern "C" fn test_basic_printbuf_memset() {
    let mut pb: *mut crate::src::apps::json_parse::printbuf = 0 as *mut crate::src::apps::json_parse::printbuf;
    printf(
        b"%s: starting test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<
            &[u8; 27],
            &[libc::c_char; 27],
        >(b"test_basic_printbuf_memset\0"))
            .as_ptr(),
    );
    pb = crate::src::printbuf::printbuf_new();
    crate::src::printbuf::sprintbuf(pb, b"blue:%d\0" as *const u8 as *const libc::c_char, 1 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), 'x' as i32, 52 as libc::c_int);
    printf(
        b"Buffer contents:%.*s\n\0" as *const u8 as *const libc::c_char,
        (*pb).bpos,
        (*pb).buf,
    );
    crate::src::printbuf::printbuf_free(pb);
    printf(
        b"%s: end test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<
            &[u8; 27],
            &[libc::c_char; 27],
        >(b"test_basic_printbuf_memset\0"))
            .as_ptr(),
    );
}
unsafe extern "C" fn test_printbuf_memset_length() {
    let mut pb: *mut crate::src::apps::json_parse::printbuf = 0 as *mut crate::src::apps::json_parse::printbuf;
    printf(
        b"%s: starting test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<
            &[u8; 28],
            &[libc::c_char; 28],
        >(b"test_printbuf_memset_length\0"))
            .as_ptr(),
    );
    pb = crate::src::printbuf::printbuf_new();
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 0 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 0 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 0 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 0 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 0 as libc::c_int);
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 2 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 4 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 6 as libc::c_int);
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 6 as libc::c_int);
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 8 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 10 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 10 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 10 as libc::c_int);
    crate::src::printbuf::printbuf_memset(pb, -(1 as libc::c_int), ' ' as i32, 20 as libc::c_int);
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    crate::src::printbuf::printbuf_memset(pb, 0 as libc::c_int, 'x' as i32, 30 as libc::c_int);
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    crate::src::printbuf::printbuf_memset(pb, 0 as libc::c_int, 'x' as i32, (*pb).bpos + 1 as libc::c_int);
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    crate::src::printbuf::printbuf_free(pb);
    printf(
        b"%s: end test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<
            &[u8; 28],
            &[libc::c_char; 28],
        >(b"test_printbuf_memset_length\0"))
            .as_ptr(),
    );
}
unsafe extern "C" fn test_printbuf_memappend(mut before_resize: *mut libc::c_int) {
    let mut pb: *mut crate::src::apps::json_parse::printbuf = 0 as *mut crate::src::apps::json_parse::printbuf;
    let mut initial_size: libc::c_int = 0;
    printf(
        b"%s: starting test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<
            &[u8; 24],
            &[libc::c_char; 24],
        >(b"test_printbuf_memappend\0"))
            .as_ptr(),
    );
    pb = crate::src::printbuf::printbuf_new();
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    initial_size = (*pb).size;
    while (*pb).size == initial_size {
        if (*pb).size - (*pb).bpos > 1 as libc::c_int {
            memcpy(
                ((*pb).buf).offset((*pb).bpos as isize) as *mut libc::c_void,
                b"x\0" as *const u8 as *const libc::c_char as *const libc::c_void,
                1 as libc::c_int as libc::c_ulong,
            );
            (*pb).bpos += 1 as libc::c_int;
            *((*pb).buf).offset((*pb).bpos as isize) = '\0' as i32 as libc::c_char;
        } else {
            crate::src::printbuf::printbuf_memappend(
                pb,
                b"x\0" as *const u8 as *const libc::c_char,
                1 as libc::c_int,
            );
        }
    }
    *before_resize = (*pb).bpos - 1 as libc::c_int;
    printf(
        b"Appended %d bytes for resize: [%s]\n\0" as *const u8 as *const libc::c_char,
        *before_resize + 1 as libc::c_int,
        (*pb).buf,
    );
    crate::src::printbuf::printbuf_reset(pb);
    if (*pb).size - (*pb).bpos > 3 as libc::c_int {
        memcpy(
            ((*pb).buf).offset((*pb).bpos as isize) as *mut libc::c_void,
            b"bluexyz123\0" as *const u8 as *const libc::c_char as *const libc::c_void,
            3 as libc::c_int as libc::c_ulong,
        );
        (*pb).bpos += 3 as libc::c_int;
        *((*pb).buf).offset((*pb).bpos as isize) = '\0' as i32 as libc::c_char;
    } else {
        crate::src::printbuf::printbuf_memappend(
            pb,
            b"bluexyz123\0" as *const u8 as *const libc::c_char,
            3 as libc::c_int,
        );
    }
    printf(
        b"Partial append: %d, [%s]\n\0" as *const u8 as *const libc::c_char,
        (*pb).bpos,
        (*pb).buf,
    );
    let mut with_nulls: [libc::c_char; 4] = [
        'a' as i32 as libc::c_char,
        'b' as i32 as libc::c_char,
        '\0' as i32 as libc::c_char,
        'c' as i32 as libc::c_char,
    ];
    crate::src::printbuf::printbuf_reset(pb);
    if (*pb).size - (*pb).bpos
        > ::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong as libc::c_int
    {
        memcpy(
            ((*pb).buf).offset((*pb).bpos as isize) as *mut libc::c_void,
            with_nulls.as_mut_ptr() as *const libc::c_void,
            ::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong as libc::c_int
                as libc::c_ulong,
        );
        (*pb).bpos
            += ::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong
                as libc::c_int;
        *((*pb).buf).offset((*pb).bpos as isize) = '\0' as i32 as libc::c_char;
    } else {
        crate::src::printbuf::printbuf_memappend(
            pb,
            with_nulls.as_mut_ptr(),
            ::core::mem::size_of::<[libc::c_char; 4]>() as libc::c_ulong as libc::c_int,
        );
    }
    printf(
        b"With embedded \\0 character: %d, [%s]\n\0" as *const u8 as *const libc::c_char,
        (*pb).bpos,
        (*pb).buf,
    );
    crate::src::printbuf::printbuf_free(pb);
    pb = crate::src::printbuf::printbuf_new();
    let mut data: *mut libc::c_char = malloc(*before_resize as libc::c_ulong)
        as *mut libc::c_char;
    memset(data as *mut libc::c_void, 'X' as i32, *before_resize as libc::c_ulong);
    if (*pb).size - (*pb).bpos > *before_resize {
        memcpy(
            ((*pb).buf).offset((*pb).bpos as isize) as *mut libc::c_void,
            data as *const libc::c_void,
            *before_resize as libc::c_ulong,
        );
        (*pb).bpos += *before_resize;
        *((*pb).buf).offset((*pb).bpos as isize) = '\0' as i32 as libc::c_char;
    } else {
        crate::src::printbuf::printbuf_memappend(pb, data, *before_resize);
    }
    printf(
        b"Append to just before resize: %d, [%s]\n\0" as *const u8
            as *const libc::c_char,
        (*pb).bpos,
        (*pb).buf,
    );
    free(data as *mut libc::c_void);
    crate::src::printbuf::printbuf_free(pb);
    pb = crate::src::printbuf::printbuf_new();
    data = malloc((*before_resize + 1 as libc::c_int) as libc::c_ulong)
        as *mut libc::c_char;
    memset(
        data as *mut libc::c_void,
        'X' as i32,
        (*before_resize + 1 as libc::c_int) as libc::c_ulong,
    );
    if (*pb).size - (*pb).bpos > *before_resize + 1 as libc::c_int {
        memcpy(
            ((*pb).buf).offset((*pb).bpos as isize) as *mut libc::c_void,
            data as *const libc::c_void,
            (*before_resize + 1 as libc::c_int) as libc::c_ulong,
        );
        (*pb).bpos += *before_resize + 1 as libc::c_int;
        *((*pb).buf).offset((*pb).bpos as isize) = '\0' as i32 as libc::c_char;
    } else {
        crate::src::printbuf::printbuf_memappend(pb, data, *before_resize + 1 as libc::c_int);
    }
    printf(
        b"Append to just after resize: %d, [%s]\n\0" as *const u8 as *const libc::c_char,
        (*pb).bpos,
        (*pb).buf,
    );
    free(data as *mut libc::c_void);
    crate::src::printbuf::printbuf_free(pb);
    pb = crate::src::printbuf::printbuf_new();
    crate::src::printbuf::printbuf_memappend(
        pb,
        b"XXXXXXXXXXXXXXXX\0" as *const u8 as *const libc::c_char,
        (::core::mem::size_of::<[libc::c_char; 17]>() as libc::c_ulong)
            .wrapping_sub(1 as libc::c_int as libc::c_ulong) as libc::c_int,
    );
    printf(
        b"Buffer size after printbuf_strappend(): %d, [%s]\n\0" as *const u8
            as *const libc::c_char,
        (*pb).bpos,
        (*pb).buf,
    );
    crate::src::printbuf::printbuf_free(pb);
    printf(
        b"%s: end test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<
            &[u8; 24],
            &[libc::c_char; 24],
        >(b"test_printbuf_memappend\0"))
            .as_ptr(),
    );
}
unsafe extern "C" fn test_sprintbuf(mut before_resize: libc::c_int) {
    let mut pb: *mut crate::src::apps::json_parse::printbuf = 0 as *mut crate::src::apps::json_parse::printbuf;
    let mut max_char: *const libc::c_char = b"if string is greater than stack buffer, then use dynamic string with vasprintf.  Note: some implementation of vsnprintf return -1  if output is truncated whereas some return the number of bytes that  would have been written - this code handles both cases.\0"
        as *const u8 as *const libc::c_char;
    printf(
        b"%s: starting test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<&[u8; 15], &[libc::c_char; 15]>(b"test_sprintbuf\0"))
            .as_ptr(),
    );
    pb = crate::src::printbuf::printbuf_new();
    printf(b"Buffer length: %d\n\0" as *const u8 as *const libc::c_char, (*pb).bpos);
    let mut data: *mut libc::c_char = malloc(
        (before_resize + 1 as libc::c_int + 1 as libc::c_int) as libc::c_ulong,
    ) as *mut libc::c_char;
    memset(
        data as *mut libc::c_void,
        'X' as i32,
        (before_resize + 1 as libc::c_int + 1 as libc::c_int) as libc::c_ulong,
    );
    *data
        .offset(
            (before_resize + 1 as libc::c_int) as isize,
        ) = '\0' as i32 as libc::c_char;
    crate::src::printbuf::sprintbuf(pb, b"%s\0" as *const u8 as *const libc::c_char, data);
    free(data as *mut libc::c_void);
    printf(
        b"sprintbuf to just after resize(%d+1): %d, [%s], strlen(buf)=%d\n\0"
            as *const u8 as *const libc::c_char,
        before_resize,
        (*pb).bpos,
        (*pb).buf,
        strlen((*pb).buf) as libc::c_int,
    );
    crate::src::printbuf::printbuf_reset(pb);
    crate::src::printbuf::sprintbuf(pb, b"plain\0" as *const u8 as *const libc::c_char);
    printf(b"%d, [%s]\n\0" as *const u8 as *const libc::c_char, (*pb).bpos, (*pb).buf);
    crate::src::printbuf::sprintbuf(pb, b"%d\0" as *const u8 as *const libc::c_char, 1 as libc::c_int);
    printf(b"%d, [%s]\n\0" as *const u8 as *const libc::c_char, (*pb).bpos, (*pb).buf);
    crate::src::printbuf::sprintbuf(
        pb,
        b"%d\0" as *const u8 as *const libc::c_char,
        2147483647 as libc::c_int,
    );
    printf(b"%d, [%s]\n\0" as *const u8 as *const libc::c_char, (*pb).bpos, (*pb).buf);
    crate::src::printbuf::sprintbuf(
        pb,
        b"%d\0" as *const u8 as *const libc::c_char,
        -(2147483647 as libc::c_int) - 1 as libc::c_int,
    );
    printf(b"%d, [%s]\n\0" as *const u8 as *const libc::c_char, (*pb).bpos, (*pb).buf);
    crate::src::printbuf::sprintbuf(
        pb,
        b"%s\0" as *const u8 as *const libc::c_char,
        b"%s\0" as *const u8 as *const libc::c_char,
    );
    printf(b"%d, [%s]\n\0" as *const u8 as *const libc::c_char, (*pb).bpos, (*pb).buf);
    crate::src::printbuf::sprintbuf(pb, max_char);
    printf(b"%d, [%s]\n\0" as *const u8 as *const libc::c_char, (*pb).bpos, (*pb).buf);
    crate::src::printbuf::printbuf_free(pb);
    printf(
        b"%s: end test\n\0" as *const u8 as *const libc::c_char,
        (*::core::mem::transmute::<&[u8; 15], &[libc::c_char; 15]>(b"test_sprintbuf\0"))
            .as_ptr(),
    );
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut before_resize: libc::c_int = 0 as libc::c_int;
    test_basic_printbuf_memset();
    printf(
        b"========================================\n\0" as *const u8
            as *const libc::c_char,
    );
    test_printbuf_memset_length();
    printf(
        b"========================================\n\0" as *const u8
            as *const libc::c_char,
    );
    test_printbuf_memappend(&raw mut before_resize);
    printf(
        b"========================================\n\0" as *const u8
            as *const libc::c_char,
    );
    test_sprintbuf(before_resize);
    printf(
        b"========================================\n\0" as *const u8
            as *const libc::c_char,
    );
    return 0 as libc::c_int;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in &raw mut ::std::env::args() {
        args.push(
            (::std::ffi::CString::new(arg))
                .expect("Failed to convert argument into CString.")
                .into_raw(),
        );
    }
    args.push(::core::ptr::null_mut());
    unsafe {
        ::std::process::exit(
            main_0(
                (args.len() - 1) as libc::c_int,
                args.as_mut_ptr() as *mut *mut libc::c_char,
            ) as i32,
        )
    }
}
