use ::libc;
extern "C" {
    pub type _IO_wide_data;
    
    
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn exit(_: libc::c_int) -> !;
    fn __assert_fail(
        __assertion: *const libc::c_char,
        __file: *const libc::c_char,
        __line: libc::c_uint,
        __function: *const libc::c_char,
    ) -> !;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
}
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor0 { dummy: () }
pub type FILE = crate::src::blocksplitter::_IO_FILE;
#[derive(Copy, Clone)]

struct ErasedByPreprocessor1 { dummy: () }
pub type __off64_t = libc::c_long;
pub type _IO_lock_t = ();
pub type __off_t = libc::c_long;
#[no_mangle]
pub unsafe extern "C" fn ZopfliInitCache(
    mut blocksize: size_t,
    mut lmc: *mut crate::src::blocksplitter::ZopfliLongestMatchCache,
) {
    let mut i: size_t = 0;
    (*lmc)
        .length = malloc(
        (::core::mem::size_of::<libc::c_ushort>() as libc::c_ulong)
            .wrapping_mul(blocksize),
    ) as *mut libc::c_ushort;
    (*lmc)
        .dist = malloc(
        (::core::mem::size_of::<libc::c_ushort>() as libc::c_ulong)
            .wrapping_mul(blocksize),
    ) as *mut libc::c_ushort;
    (*lmc)
        .sublen = malloc((8 as libc::c_int * 3 as libc::c_int) as size_t * blocksize)
        as *mut libc::c_uchar;
    if ((*lmc).sublen).is_null() {std::intrinsics::assume(((*lmc).sublen).addr() == 0);
        fprintf(
            stderr,
            b"Error: Out of memory. Tried allocating %lu bytes of memory.\n\0"
                as *const u8 as *const libc::c_char,
            (8 as libc::c_int as libc::c_ulong)
                .wrapping_mul(3 as libc::c_int as libc::c_ulong)
                .wrapping_mul(blocksize),
        );
        exit(1 as libc::c_int);
    }
    i = 0 as libc::c_int as size_t;
    while i < blocksize {
        *((*lmc).length).offset(i as isize) = 1 as libc::c_int as libc::c_ushort;
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < blocksize {
        *((*lmc).dist).offset(i as isize) = 0 as libc::c_int as libc::c_ushort;
        i = i.wrapping_add(1);
        i;
    }
    i = 0 as libc::c_int as size_t;
    while i < 8 as libc::c_int as size_t * blocksize * 3 as libc::c_int as size_t {
        *((*lmc).sublen).offset(i as isize) = 0 as libc::c_int as libc::c_uchar;
        i = i.wrapping_add(1);
        i;
    }
}
#[no_mangle]
pub unsafe extern "C" fn ZopfliCleanCache(mut lmc: *mut crate::src::blocksplitter::ZopfliLongestMatchCache) {
    free((*lmc).length as *mut libc::c_void);
    free((*lmc).dist as *mut libc::c_void);
    free((*lmc).sublen as *mut libc::c_void);
}
#[no_mangle]
pub unsafe extern "C" fn ZopfliSublenToCache(
    mut sublen: *const libc::c_ushort,
    mut pos: size_t,
    mut length: size_t,
    mut lmc: *mut crate::src::blocksplitter::ZopfliLongestMatchCache,
) {
    let mut i: size_t = 0;
    let mut j: size_t = 0 as libc::c_int as size_t;
    let mut bestlength: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    let mut cache: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    cache = &raw mut *((*lmc).sublen)
        .offset((8 as libc::c_int as size_t * pos * 3 as libc::c_int as size_t) as isize)
        as *mut libc::c_uchar;
    if length < 3 as libc::c_int as size_t {
        return;
    }
    i = 3 as libc::c_int as size_t;
    while i <= length {
        if i == length
            || *sublen.offset(i as isize) as libc::c_int
                != *sublen.offset(i.wrapping_add(1 as libc::c_int as size_t) as isize)
                    as libc::c_int
        {
            *cache
                .offset(
                    (j * 3 as libc::c_int as size_t) as isize,
                ) = i.wrapping_sub(3 as libc::c_int as size_t) as libc::c_uchar;
            *cache
                .offset(
                    (j * 3 as libc::c_int as size_t)
                        .wrapping_add(1 as libc::c_int as size_t) as isize,
                ) = (*sublen.offset(i as isize) as libc::c_int % 256 as libc::c_int)
                as libc::c_uchar;
            *cache
                .offset(
                    (j * 3 as libc::c_int as size_t)
                        .wrapping_add(2 as libc::c_int as size_t) as isize,
                ) = ((*sublen.offset(i as isize) as libc::c_int >> 8 as libc::c_int)
                % 256 as libc::c_int) as libc::c_uchar;
            bestlength = i as libc::c_uint;
            j = j.wrapping_add(1);
            j;
            if j >= 8 as libc::c_int as size_t {
                break;
            }
        }
        i = i.wrapping_add(1);
        i;
    }
    if j < 8 as libc::c_int as size_t {
        if bestlength as size_t == length {} else {
            __assert_fail(
                b"bestlength == length\0" as *const u8 as *const libc::c_char,
                b"src/zopfli/cache.c\0" as *const u8 as *const libc::c_char,
                79 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 92],
                    &[libc::c_char; 92],
                >(
                    b"void ZopfliSublenToCache(const unsigned short *, size_t, size_t, ZopfliLongestMatchCache *)\0",
                ))
                    .as_ptr(),
            );
        };
        *cache
            .offset(
                ((8 as libc::c_int - 1 as libc::c_int) * 3 as libc::c_int) as isize,
            ) = bestlength.wrapping_sub(3 as libc::c_int as libc::c_uint)
            as libc::c_uchar;
    } else {
        if bestlength as size_t <= length {} else {
            __assert_fail(
                b"bestlength <= length\0" as *const u8 as *const libc::c_char,
                b"src/zopfli/cache.c\0" as *const u8 as *const libc::c_char,
                82 as libc::c_int as libc::c_uint,
                (*::core::mem::transmute::<
                    &[u8; 92],
                    &[libc::c_char; 92],
                >(
                    b"void ZopfliSublenToCache(const unsigned short *, size_t, size_t, ZopfliLongestMatchCache *)\0",
                ))
                    .as_ptr(),
            );
        };
    }
    if bestlength == ZopfliMaxCachedSublen(lmc, pos, length) {} else {
        __assert_fail(
            b"bestlength == ZopfliMaxCachedSublen(lmc, pos, length)\0" as *const u8
                as *const libc::c_char,
            b"src/zopfli/cache.c\0" as *const u8 as *const libc::c_char,
            84 as libc::c_int as libc::c_uint,
            (*::core::mem::transmute::<
                &[u8; 92],
                &[libc::c_char; 92],
            >(
                b"void ZopfliSublenToCache(const unsigned short *, size_t, size_t, ZopfliLongestMatchCache *)\0",
            ))
                .as_ptr(),
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn ZopfliCacheToSublen(
    mut lmc: *const crate::src::blocksplitter::ZopfliLongestMatchCache,
    mut pos: size_t,
    mut length: size_t,
    mut sublen: *mut libc::c_ushort,
) {
    let mut i: size_t = 0;
    let mut j: size_t = 0;
    let mut maxlength: libc::c_uint = ZopfliMaxCachedSublen(lmc, pos, length);
    let mut prevlength: libc::c_uint = 0 as libc::c_int as libc::c_uint;
    let mut cache: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    if length < 3 as libc::c_int as size_t {
        return;
    }
    cache = &raw mut *((*lmc).sublen)
        .offset((8 as libc::c_int as size_t * pos * 3 as libc::c_int as size_t) as isize)
        as *mut libc::c_uchar;
    j = 0 as libc::c_int as size_t;
    while j < 8 as libc::c_int as size_t {
        let mut length_0: libc::c_uint = (*cache
            .offset((j * 3 as libc::c_int as size_t) as isize) as libc::c_int
            + 3 as libc::c_int) as libc::c_uint;
        let mut dist: libc::c_uint = (*cache
            .offset(
                (j * 3 as libc::c_int as size_t).wrapping_add(1 as libc::c_int as size_t)
                    as isize,
            ) as libc::c_int
            + 256 as libc::c_int
                * *cache
                    .offset(
                        (j * 3 as libc::c_int as size_t)
                            .wrapping_add(2 as libc::c_int as size_t) as isize,
                    ) as libc::c_int) as libc::c_uint;
        i = prevlength as size_t;
        while i <= length_0 as size_t {
            *sublen.offset(i as isize) = dist as libc::c_ushort;
            i = i.wrapping_add(1);
            i;
        }
        if length_0 == maxlength {
            break;
        }
        prevlength = length_0.wrapping_add(1 as libc::c_int as libc::c_uint);
        j = j.wrapping_add(1);
        j;
    }
}
#[no_mangle]
pub unsafe extern "C" fn ZopfliMaxCachedSublen(
    mut lmc: *const crate::src::blocksplitter::ZopfliLongestMatchCache,
    mut pos: size_t,
    mut length: size_t,
) -> libc::c_uint {
    let mut cache: *mut libc::c_uchar = 0 as *mut libc::c_uchar;
    cache = &raw mut *((*lmc).sublen)
        .offset((8 as libc::c_int as size_t * pos * 3 as libc::c_int as size_t) as isize)
        as *mut libc::c_uchar;
    if *cache.offset(1 as libc::c_int as isize) as libc::c_int == 0 as libc::c_int
        && *cache.offset(2 as libc::c_int as isize) as libc::c_int == 0 as libc::c_int
    {
        return 0 as libc::c_int as libc::c_uint;
    }
    return (*cache
        .offset(((8 as libc::c_int - 1 as libc::c_int) * 3 as libc::c_int) as isize)
        as libc::c_int + 3 as libc::c_int) as libc::c_uint;
}
