use ::libc;
extern "C" {
    pub type ht;
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn ht_create() -> *mut ht;
    fn ht_get(table: *mut ht, key: *const libc::c_char) -> *mut libc::c_void;
    fn ht_set(
        table: *mut ht,
        key: *const libc::c_char,
        value_0: *mut libc::c_void,
    ) -> *const libc::c_char;
    static mut stderr: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn exit(_: libc::c_int) -> !;
    fn strcmp(_: *const libc::c_char, _: *const libc::c_char) -> libc::c_int;
    fn clock() -> clock_t;
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type __clock_t = libc::c_long;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type _IO_lock_t = ();
pub type FILE = _IO_FILE;
pub type clock_t = __clock_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct item {
    pub key: *mut libc::c_char,
    pub value: libc::c_int,
}
#[no_mangle]
pub unsafe extern "C" fn exit_nomem() {
    fprintf(stderr, b"out of memory\n\0" as *const u8 as *const libc::c_char);
    exit(1 as libc::c_int);
}
#[no_mangle]
pub unsafe extern "C" fn linear_search(
    mut items_0: *mut item,
    mut size: size_t,
    mut key: *const libc::c_char,
) -> *mut item {
    let mut i: size_t = 0 as libc::c_int as size_t;
    while i < size {
        if strcmp((*items_0.offset(i as isize)).key, key) == 0 as libc::c_int {
            return &mut *items_0.offset(i as isize) as *mut item;
        }
        i = i.wrapping_add(1);
        i;
    }
    return 0 as *mut item;
}
#[no_mangle]
pub unsafe extern "C" fn binary_search(
    mut items_0: *mut item,
    mut size: size_t,
    mut key: *const libc::c_char,
) -> *mut item {
    let mut low: size_t = 0 as libc::c_int as size_t;
    let mut high: size_t = size;
    while low < high {
        let mut mid: size_t = low.wrapping_add(high) / 2 as libc::c_int as size_t;
        let mut c: libc::c_int = strcmp((*items_0.offset(mid as isize)).key, key);
        if c == 0 as libc::c_int {
            return &mut *items_0.offset(mid as isize) as *mut item;
        }
        if c < 0 as libc::c_int {
            low = mid.wrapping_add(1 as libc::c_int as size_t);
        } else {
            high = mid;
        }
    }
    if low < size && strcmp((*items_0.offset(low as isize)).key, key) == 0 as libc::c_int
    {
        return &mut *items_0.offset(low as isize) as *mut item;
    }
    return 0 as *mut item;
}
#[no_mangle]
pub static mut items: [item; 26] = [
    {
        let mut init = item {
            key: b"aoo\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 0 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"bar\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 1 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"cazz\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 2 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"duzz\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 3 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"eaddle\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 4 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"fche\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 5 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"garf\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 6 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"hache\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 7 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"iya\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 8 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"jay\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 9 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"kay\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 10 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"lell\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 11 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"memm\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 12 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"noo\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 0 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"oar\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 1 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"pazz\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 2 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"quzz\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 3 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"raddle\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 4 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"sche\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 5 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"tarf\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 6 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"uache\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 7 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"vya\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 8 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"way\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 9 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"xay\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 10 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"yell\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 11 as libc::c_int,
        };
        init
    },
    {
        let mut init = item {
            key: b"zemm\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
            value: 12 as libc::c_int,
        };
        init
    },
];
#[no_mangle]
pub static mut found: *mut item = 0 as *const item as *mut item;
#[no_mangle]
pub static mut value: *mut libc::c_int = 0 as *const libc::c_int as *mut libc::c_int;
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut runs: libc::c_int = 5000000 as libc::c_int;
    let mut num_items: libc::c_int = 1 as libc::c_int;
    while (num_items as libc::c_ulong)
        < (::core::mem::size_of::<[item; 26]>() as libc::c_ulong)
            .wrapping_div(::core::mem::size_of::<item>() as libc::c_ulong)
    {
        printf(b"NUM ITEMS: %d\n\0" as *const u8 as *const libc::c_char, num_items);
        let mut start: clock_t = clock();
        let mut item_index: libc::c_int = 0 as libc::c_int;
        while item_index < num_items {
            let mut key: *mut libc::c_char = items[item_index as usize].key;
            let mut run: libc::c_int = 0 as libc::c_int;
            while run < runs {
                found = linear_search(items.as_mut_ptr(), num_items as size_t, key);
                run += 1;
                run;
            }
            item_index += 1;
            item_index;
        }
        let mut end: clock_t = clock();
        let mut elapsed: libc::c_double = (end - start) as libc::c_double
            / 1000000 as libc::c_int as __clock_t as libc::c_double
            / num_items as libc::c_double;
        printf(
            b"  linear, %d runs: %.09fs\n\0" as *const u8 as *const libc::c_char,
            runs,
            elapsed,
        );
        start = clock();
        let mut item_index_0: libc::c_int = 0 as libc::c_int;
        while item_index_0 < num_items {
            let mut key_0: *mut libc::c_char = items[item_index_0 as usize].key;
            let mut run_0: libc::c_int = 0 as libc::c_int;
            while run_0 < runs {
                found = binary_search(items.as_mut_ptr(), num_items as size_t, key_0);
                run_0 += 1;
                run_0;
            }
            item_index_0 += 1;
            item_index_0;
        }
        end = clock();
        elapsed = (end - start) as libc::c_double
            / 1000000 as libc::c_int as __clock_t as libc::c_double
            / num_items as libc::c_double;
        printf(
            b"  binary, %d runs: %.09fs\n\0" as *const u8 as *const libc::c_char,
            runs,
            elapsed,
        );
        let mut table: *mut ht = ht_create();
        if table.is_null() {
            exit_nomem();
        }
        let mut item_index_1: libc::c_int = 0 as libc::c_int;
        while item_index_1 < num_items {
            let mut pn: *mut libc::c_int = malloc(
                ::core::mem::size_of::<libc::c_int>() as libc::c_ulong,
            ) as *mut libc::c_int;
            if pn.is_null() {
                exit_nomem();
            }
            *pn = items[item_index_1 as usize].value;
            let mut p: *const libc::c_char = ht_set(
                table,
                items[item_index_1 as usize].key,
                pn as *mut libc::c_void,
            );
            if p.is_null() {
                exit_nomem();
            }
            item_index_1 += 1;
            item_index_1;
        }
        start = clock();
        let mut item_index_2: libc::c_int = 0 as libc::c_int;
        while item_index_2 < num_items {
            let mut key_1: *mut libc::c_char = items[item_index_2 as usize].key;
            let mut run_1: libc::c_int = 0 as libc::c_int;
            while run_1 < runs {
                value = ht_get(table, key_1) as *mut libc::c_int;
                run_1 += 1;
                run_1;
            }
            item_index_2 += 1;
            item_index_2;
        }
        end = clock();
        elapsed = (end - start) as libc::c_double
            / 1000000 as libc::c_int as __clock_t as libc::c_double
            / num_items as libc::c_double;
        printf(
            b"  hash  , %d runs: %.09fs\n\0" as *const u8 as *const libc::c_char,
            runs,
            elapsed,
        );
        num_items += 1;
        num_items;
    }
    return 0;
}
pub fn main() {
    let mut args: Vec::<*mut libc::c_char> = Vec::new();
    for arg in ::std::env::args() {
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
