use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    static mut stdout: *mut FILE;
    fn fprintf(_: *mut FILE, _: *const libc::c_char, _: ...) -> libc::c_int;
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn rand() -> libc::c_int;
    fn srand(__seed: libc::c_uint);
    fn free(_: *mut libc::c_void);
    fn time(__timer: *mut time_t) -> time_t;
    fn avl_create(
        compare_func_0: Option::<
            unsafe extern "C" fn(*const libc::c_void, *const libc::c_void) -> libc::c_int,
        >,
        destroy_func_0: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    ) -> *mut avltree;
    fn avl_destroy(avlt: *mut avltree);
    fn avl_find(avlt: *mut avltree, data: *mut libc::c_void) -> *mut avlnode;
    fn avl_successor(avlt: *mut avltree, node: *mut avlnode) -> *mut avlnode;
    fn avl_insert(avlt: *mut avltree, data: *mut libc::c_void) -> *mut avlnode;
    fn avl_delete(
        avlt: *mut avltree,
        node: *mut avlnode,
        keep: libc::c_int,
    ) -> *mut libc::c_void;
    fn avl_check_order(
        avlt: *mut avltree,
        min: *mut libc::c_void,
        max: *mut libc::c_void,
    ) -> libc::c_int;
    fn avl_check_height(avlt: *mut avltree) -> libc::c_int;
    fn makedata(key: libc::c_int) -> *mut mydata;
    fn compare_func(d1: *const libc::c_void, d2: *const libc::c_void) -> libc::c_int;
    fn destroy_func(d: *mut libc::c_void);
}
pub type size_t = libc::c_ulong;
pub type __off_t = libc::c_long;
pub type __off64_t = libc::c_long;
pub type __time_t = libc::c_long;
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
pub type time_t = __time_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct avlnode {
    pub left: *mut avlnode,
    pub right: *mut avlnode,
    pub parent: *mut avlnode,
    pub bf: libc::c_char,
    pub data: *mut libc::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct avltree {
    pub compare: Option::<
        unsafe extern "C" fn(*const libc::c_void, *const libc::c_void) -> libc::c_int,
    >,
    pub print: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    pub destroy: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    pub root: avlnode,
    pub nil: avlnode,
    pub min: *mut avlnode,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct mydata {
    pub key: libc::c_int,
}
#[no_mangle]
pub static mut mu_tests: libc::c_int = 0 as libc::c_int;
#[no_mangle]
pub static mut mu_fails: libc::c_int = 0 as libc::c_int;
#[no_mangle]
pub static mut permutation_error: libc::c_int = 0 as libc::c_int;
#[no_mangle]
pub unsafe extern "C" fn all_tests() {
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_create\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_create() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_find\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_find() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_successor\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_successor() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_atomic_insertion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_atomic_insertion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_atomic_deletion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_atomic_deletion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_chain_insertion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_chain_insertion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_chain_deletion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_chain_deletion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_permutation_insertion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_permutation_insertion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_permutation_deletion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_permutation_deletion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_random_insertion_deletion\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_random_insertion_deletion() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_dup\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_dup() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    }
    mu_tests += 1;
    printf(
        b"#%03d %s \n\0" as *const u8 as *const libc::c_char,
        mu_tests,
        b"unit_test_min\0" as *const u8 as *const libc::c_char,
    );
    if unit_test_min() != 0 {
        printf(b"PASSED\n\0" as *const u8 as *const libc::c_char);
    } else {
        printf(b"FAILED\n\0" as *const u8 as *const libc::c_char);
        mu_fails += 1;
        mu_fails;
    };
}
unsafe fn main_0(
    mut argc: libc::c_int,
    mut argv: *mut *mut libc::c_char,
) -> libc::c_int {
    all_tests();
    if mu_fails != 0 {
        printf(
            b"*** %d/%d TESTS FAILED ***\n\0" as *const u8 as *const libc::c_char,
            mu_fails,
            mu_tests,
        );
        return 1 as libc::c_int;
    } else {
        printf(b"ALL TESTS PASSED\n\0" as *const u8 as *const libc::c_char);
        return 0 as libc::c_int;
    };
}
unsafe extern "C" fn tree_create() -> *mut avltree {
    return avl_create(
        Some(
            compare_func
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        ),
        Some(destroy_func as unsafe extern "C" fn(*mut libc::c_void) -> ()),
    );
}
unsafe extern "C" fn tree_find(
    mut avlt: *mut avltree,
    mut key: libc::c_int,
) -> *mut avlnode {
    let mut query: mydata = mydata { key: 0 };
    query.key = key;
    return avl_find(avlt, &mut query as *mut mydata as *mut libc::c_void);
}
unsafe extern "C" fn tree_check(mut avlt: *mut avltree) -> libc::c_int {
    let mut min: mydata = mydata { key: 0 };
    let mut max: mydata = mydata { key: 0 };
    let mut rc: libc::c_int = 0;
    min.key = -(2147483647 as libc::c_int) - 1 as libc::c_int;
    max.key = 2147483647 as libc::c_int;
    rc = 1 as libc::c_int;
    if avl_check_order(
        avlt,
        &mut min as *mut mydata as *mut libc::c_void,
        &mut max as *mut mydata as *mut libc::c_void,
    ) != 1 as libc::c_int
    {
        fprintf(
            stdout,
            b"tree_check: invalid order\n\0" as *const u8 as *const libc::c_char,
        );
        rc = 0 as libc::c_int;
    }
    if avl_check_height(avlt) != 1 as libc::c_int {
        fprintf(
            stdout,
            b"tree_check: invalid height\n\0" as *const u8 as *const libc::c_char,
        );
        rc = 0 as libc::c_int;
    }
    return rc;
}
unsafe extern "C" fn tree_insert(
    mut avlt: *mut avltree,
    mut key: libc::c_int,
) -> *mut avlnode {
    let mut node: *mut avlnode = 0 as *mut avlnode;
    let mut data: *mut mydata = 0 as *mut mydata;
    if key < -(2147483647 as libc::c_int) - 1 as libc::c_int
        || key > 2147483647 as libc::c_int
    {
        fprintf(
            stdout,
            b"tree_insert: invalid key %d\n\0" as *const u8 as *const libc::c_char,
            key,
        );
        return 0 as *mut avlnode;
    }
    data = makedata(key);
    if data.is_null()
        || {
            node = avl_insert(avlt, data as *mut libc::c_void);
            node.is_null()
        }
    {
        fprintf(
            stdout,
            b"tree_insert: insert %d failed\n\0" as *const u8 as *const libc::c_char,
            key,
        );
        free(data as *mut libc::c_void);
        return 0 as *mut avlnode;
    }
    return node;
}
unsafe extern "C" fn tree_delete(
    mut avlt: *mut avltree,
    mut key: libc::c_int,
) -> libc::c_int {
    let mut node: *mut avlnode = 0 as *mut avlnode;
    node = tree_find(avlt, key);
    if node.is_null() {
        fprintf(
            stdout,
            b"tree_delete: %d not found\n\0" as *const u8 as *const libc::c_char,
            key,
        );
        return 0 as libc::c_int;
    }
    avl_delete(avlt, node, 0 as libc::c_int);
    if tree_find(avlt, key) == node {
        fprintf(
            stdout,
            b"tree_delete: delete %d failed\n\0" as *const u8 as *const libc::c_char,
            key,
        );
        return 0 as libc::c_int;
    }
    return 1 as libc::c_int;
}
unsafe extern "C" fn swap(mut x: *mut libc::c_char, mut y: *mut libc::c_char) {
    let mut temp: libc::c_char = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}
unsafe extern "C" fn permute(
    mut a: *mut libc::c_char,
    mut start: libc::c_int,
    mut end: libc::c_int,
    mut func: Option::<unsafe extern "C" fn(*mut libc::c_char) -> ()>,
) {
    if start == end {
        func.expect("non-null function pointer")(a);
        return;
    }
    let mut i: libc::c_int = 0;
    i = start;
    while i <= end {
        swap(a.offset(start as isize), a.offset(i as isize));
        permute(a, start + 1 as libc::c_int, end, func);
        swap(a.offset(start as isize), a.offset(i as isize));
        i += 1;
        i;
    }
}
unsafe extern "C" fn permutation_insert(mut a: *mut libc::c_char) {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut node: *mut avlnode = 0 as *mut avlnode;
    let mut i: libc::c_int = 0;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
        permutation_error += 1;
        permutation_error;
        return;
    }
    i = 0 as libc::c_int;
    while (i as libc::c_ulong) < strlen(a) {
        node = tree_insert(avlt, *a.offset(i as isize) as libc::c_int);
        if node.is_null()
            || tree_find(avlt, *a.offset(i as isize) as libc::c_int) != node
            || tree_check(avlt) != 1 as libc::c_int
        {
            fprintf(
                stdout,
                b"insert %c failed\n\0" as *const u8 as *const libc::c_char,
                *a.offset(i as isize) as libc::c_int,
            );
            permutation_error += 1;
            permutation_error;
            return;
        }
        i += 1;
        i;
    }
    avl_destroy(avlt);
}
unsafe extern "C" fn permutation_delete(mut a: *mut libc::c_char) {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut node: *mut avlnode = 0 as *mut avlnode;
    let mut i: libc::c_int = 0;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
        permutation_error += 1;
        permutation_error;
        return;
    }
    let mut b: [libc::c_char; 11] = *::core::mem::transmute::<
        &[u8; 11],
        &mut [libc::c_char; 11],
    >(b"ABCDEFGHIJ\0");
    i = 0 as libc::c_int;
    while (i as libc::c_ulong) < strlen(b.as_mut_ptr()) {
        node = tree_insert(avlt, b[i as usize] as libc::c_int);
        if node.is_null() || tree_find(avlt, b[i as usize] as libc::c_int) != node
            || tree_check(avlt) != 1 as libc::c_int
        {
            fprintf(
                stdout,
                b"insert %c failed\n\0" as *const u8 as *const libc::c_char,
                b[i as usize] as libc::c_int,
            );
            permutation_error += 1;
            permutation_error;
            return;
        }
        i += 1;
        i;
    }
    i = 0 as libc::c_int;
    while (i as libc::c_ulong) < strlen(a) {
        if tree_delete(avlt, *a.offset(i as isize) as libc::c_int) != 1 as libc::c_int
            || tree_check(avlt) != 1 as libc::c_int
        {
            fprintf(
                stdout,
                b"delete %c failed\n\0" as *const u8 as *const libc::c_char,
                *a.offset(i as isize) as libc::c_int,
            );
            permutation_error += 1;
            permutation_error;
            return;
        }
        i += 1;
        i;
    }
    avl_destroy(avlt);
}
unsafe extern "C" fn unit_test_create() -> libc::c_int {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
        return 0 as libc::c_int;
    }
    if (*avlt).compare
        != Some(
            compare_func
                as unsafe extern "C" fn(
                    *const libc::c_void,
                    *const libc::c_void,
                ) -> libc::c_int,
        )
        || (*avlt).destroy
            != Some(destroy_func as unsafe extern "C" fn(*mut libc::c_void) -> ())
        || (*avlt).nil.left != &mut (*avlt).nil as *mut avlnode
        || (*avlt).nil.right != &mut (*avlt).nil as *mut avlnode
        || (*avlt).nil.parent != &mut (*avlt).nil as *mut avlnode
        || (*avlt).nil.bf as libc::c_int != 0 as libc::c_int
        || !((*avlt).nil.data).is_null()
        || (*avlt).root.left != &mut (*avlt).nil as *mut avlnode
        || (*avlt).root.right != &mut (*avlt).nil as *mut avlnode
        || (*avlt).root.parent != &mut (*avlt).nil as *mut avlnode
        || (*avlt).root.bf as libc::c_int != 0 as libc::c_int
        || !((*avlt).root.data).is_null()
    {
        fprintf(stdout, b"init 1\n\0" as *const u8 as *const libc::c_char);
        avl_destroy(avlt);
        return 0 as libc::c_int;
    }
    avl_destroy(avlt);
    return 1 as libc::c_int;
}
unsafe extern "C" fn unit_test_find() -> libc::c_int {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut r: *mut avlnode = 0 as *mut avlnode;
    let mut e: *mut avlnode = 0 as *mut avlnode;
    let mut d: *mut avlnode = 0 as *mut avlnode;
    let mut s: *mut avlnode = 0 as *mut avlnode;
    let mut o: *mut avlnode = 0 as *mut avlnode;
    let mut x: *mut avlnode = 0 as *mut avlnode;
    let mut c: *mut avlnode = 0 as *mut avlnode;
    let mut u: *mut avlnode = 0 as *mut avlnode;
    let mut b: *mut avlnode = 0 as *mut avlnode;
    let mut t: *mut avlnode = 0 as *mut avlnode;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
    } else {
        r = tree_insert(avlt, 'R' as i32);
        if r.is_null()
            || {
                e = tree_insert(avlt, 'E' as i32);
                e.is_null()
            }
            || {
                d = tree_insert(avlt, 'D' as i32);
                d.is_null()
            }
            || {
                s = tree_insert(avlt, 'S' as i32);
                s.is_null()
            }
            || {
                o = tree_insert(avlt, 'O' as i32);
                o.is_null()
            }
            || {
                x = tree_insert(avlt, 'X' as i32);
                x.is_null()
            }
            || {
                c = tree_insert(avlt, 'C' as i32);
                c.is_null()
            }
            || {
                u = tree_insert(avlt, 'U' as i32);
                u.is_null()
            }
            || {
                b = tree_insert(avlt, 'B' as i32);
                b.is_null()
            }
            || {
                t = tree_insert(avlt, 'T' as i32);
                t.is_null()
            } || tree_check(avlt) != 1 as libc::c_int
        {
            fprintf(stdout, b"init failed\n\0" as *const u8 as *const libc::c_char);
        } else if avl_find(avlt, (*r).data) != r || avl_find(avlt, (*e).data) != e
            || avl_find(avlt, (*d).data) != d || avl_find(avlt, (*s).data) != s
            || avl_find(avlt, (*o).data) != o || avl_find(avlt, (*x).data) != x
            || avl_find(avlt, (*c).data) != c || avl_find(avlt, (*u).data) != u
            || avl_find(avlt, (*b).data) != b || avl_find(avlt, (*t).data) != t
        {
            fprintf(stdout, b"find failed\n\0" as *const u8 as *const libc::c_char);
        } else {
            avl_destroy(avlt);
            return 1 as libc::c_int;
        }
        avl_destroy(avlt);
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_successor() -> libc::c_int {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut r: *mut avlnode = 0 as *mut avlnode;
    let mut e: *mut avlnode = 0 as *mut avlnode;
    let mut d: *mut avlnode = 0 as *mut avlnode;
    let mut s: *mut avlnode = 0 as *mut avlnode;
    let mut o: *mut avlnode = 0 as *mut avlnode;
    let mut x: *mut avlnode = 0 as *mut avlnode;
    let mut c: *mut avlnode = 0 as *mut avlnode;
    let mut u: *mut avlnode = 0 as *mut avlnode;
    let mut b: *mut avlnode = 0 as *mut avlnode;
    let mut t: *mut avlnode = 0 as *mut avlnode;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
    } else {
        r = tree_insert(avlt, 'R' as i32);
        if r.is_null()
            || {
                e = tree_insert(avlt, 'E' as i32);
                e.is_null()
            }
            || {
                d = tree_insert(avlt, 'D' as i32);
                d.is_null()
            }
            || {
                s = tree_insert(avlt, 'S' as i32);
                s.is_null()
            }
            || {
                o = tree_insert(avlt, 'O' as i32);
                o.is_null()
            }
            || {
                x = tree_insert(avlt, 'X' as i32);
                x.is_null()
            }
            || {
                c = tree_insert(avlt, 'C' as i32);
                c.is_null()
            }
            || {
                u = tree_insert(avlt, 'U' as i32);
                u.is_null()
            }
            || {
                b = tree_insert(avlt, 'B' as i32);
                b.is_null()
            }
            || {
                t = tree_insert(avlt, 'T' as i32);
                t.is_null()
            } || tree_delete(avlt, 'O' as i32) != 1 as libc::c_int
            || tree_check(avlt) != 1 as libc::c_int
        {
            fprintf(stdout, b"init failed\n\0" as *const u8 as *const libc::c_char);
        } else if avl_successor(avlt, b) != c || avl_successor(avlt, c) != d
            || avl_successor(avlt, d) != e || avl_successor(avlt, e) != r
            || avl_successor(avlt, r) != s || avl_successor(avlt, s) != t
            || avl_successor(avlt, t) != u || avl_successor(avlt, u) != x
            || !(avl_successor(avlt, x)).is_null()
        {
            fprintf(stdout, b"successor failed\n\0" as *const u8 as *const libc::c_char);
        } else {
            avl_destroy(avlt);
            return 1 as libc::c_int;
        }
        avl_destroy(avlt);
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_atomic_insertion() -> libc::c_int {
    let mut current_block: u64;
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut i: libc::c_int = 0;
    let mut j: libc::c_int = 0;
    let mut cases: [*mut libc::c_char; 16] = [
        b"P\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PH\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PX\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHDPHXDLB\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLF\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHL\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PXb\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXT\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbRV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbR\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        0 as *mut libc::c_char,
    ];
    i = 0 as libc::c_int;
    's_8: loop {
        if !((i as libc::c_ulong)
            < (::core::mem::size_of::<[*mut libc::c_char; 16]>() as libc::c_ulong)
                .wrapping_div(
                    ::core::mem::size_of::<*mut libc::c_char>() as libc::c_ulong,
                ) && !(cases[i as usize]).is_null())
        {
            current_block = 11650488183268122163;
            break;
        }
        avlt = tree_create();
        if avlt.is_null() {
            fprintf(
                stdout,
                b"%s - create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
                cases[i as usize],
            );
            current_block = 1073729669101397336;
            break;
        } else {
            j = 0 as libc::c_int;
            while (j as libc::c_ulong) < strlen(cases[i as usize]) {
                if (tree_insert(
                    avlt,
                    *(cases[i as usize]).offset(j as isize) as libc::c_int,
                ))
                    .is_null() || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"%s - insert %c failed\n\0" as *const u8 as *const libc::c_char,
                        cases[i as usize],
                        *(cases[i as usize]).offset(j as isize) as libc::c_int,
                    );
                    current_block = 4256084962706752372;
                    break 's_8;
                } else {
                    j += 1;
                    j;
                }
            }
            avl_destroy(avlt);
            i += 1;
            i;
        }
    }
    match current_block {
        11650488183268122163 => return 1 as libc::c_int,
        4256084962706752372 => {
            avl_destroy(avlt);
        }
        _ => {}
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_atomic_deletion() -> libc::c_int {
    let mut current_block: u64;
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut i: libc::c_int = 0;
    let mut j: libc::c_int = 0;
    let mut cases: [*mut libc::c_char; 90] = [
        b"P\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"P\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PH\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PH\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"P\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PX\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"P\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PX\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHX\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHX\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"P\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHX\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXD\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBF\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTB\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTF\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDL\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBFJN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBFJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBFN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBJN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTBN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTFJN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTFJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTFN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXL\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTJN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"X\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXb\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbZd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTb\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRVZd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRVZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRVd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRZd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbVZd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbVZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbVd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXT\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbRV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbR\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDTbV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"H\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        0 as *mut libc::c_char,
        0 as *mut libc::c_char,
    ];
    i = 0 as libc::c_int;
    's_8: loop {
        if !((i as libc::c_ulong)
            < (::core::mem::size_of::<[*mut libc::c_char; 90]>() as libc::c_ulong)
                .wrapping_div(
                    ::core::mem::size_of::<*mut libc::c_char>() as libc::c_ulong,
                ) && !(cases[i as usize]).is_null())
        {
            current_block = 9606288038608642794;
            break;
        }
        avlt = tree_create();
        if avlt.is_null() {
            fprintf(
                stdout,
                b"%s-%s - create AVL tree failed\n\0" as *const u8
                    as *const libc::c_char,
                cases[i as usize],
                cases[(i + 1 as libc::c_int) as usize],
            );
            current_block = 9696580155633688518;
            break;
        } else {
            j = 0 as libc::c_int;
            while (j as libc::c_ulong) < strlen(cases[i as usize]) {
                if (tree_insert(
                    avlt,
                    *(cases[i as usize]).offset(j as isize) as libc::c_int,
                ))
                    .is_null() || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"%s-%s - insert %c failed\n\0" as *const u8
                            as *const libc::c_char,
                        cases[i as usize],
                        cases[(i + 1 as libc::c_int) as usize],
                        *(cases[i as usize]).offset(j as isize) as libc::c_int,
                    );
                    current_block = 16627289072225859905;
                    break 's_8;
                } else {
                    j += 1;
                    j;
                }
            }
            j = 0 as libc::c_int;
            while (j as libc::c_ulong) < strlen(cases[(i + 1 as libc::c_int) as usize]) {
                if tree_delete(
                    avlt,
                    *(cases[(i + 1 as libc::c_int) as usize]).offset(j as isize)
                        as libc::c_int,
                ) == 0 as libc::c_int || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"%s-%s - delete %c failed\n\0" as *const u8
                            as *const libc::c_char,
                        cases[i as usize],
                        cases[(i + 1 as libc::c_int) as usize],
                        *(cases[(i + 1 as libc::c_int) as usize]).offset(j as isize)
                            as libc::c_int,
                    );
                    current_block = 16627289072225859905;
                    break 's_8;
                } else {
                    j += 1;
                    j;
                }
            }
            avl_destroy(avlt);
            i += 2 as libc::c_int;
        }
    }
    match current_block {
        9606288038608642794 => return 1 as libc::c_int,
        16627289072225859905 => {
            avl_destroy(avlt);
        }
        _ => {}
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_chain_insertion() -> libc::c_int {
    let mut current_block: u64;
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut i: libc::c_int = 0;
    let mut j: libc::c_int = 0;
    let mut cases: [*mut libc::c_char; 18] = [
        b"PHXDB\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDF\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXLJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXLN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTR\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXbZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXbd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLB\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLF\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLJ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLN\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbR\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbV\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbZ\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXTbd\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        0 as *mut libc::c_char,
    ];
    i = 0 as libc::c_int;
    's_8: loop {
        if !((i as libc::c_ulong)
            < (::core::mem::size_of::<[*mut libc::c_char; 18]>() as libc::c_ulong)
                .wrapping_div(
                    ::core::mem::size_of::<*mut libc::c_char>() as libc::c_ulong,
                ) && !(cases[i as usize]).is_null())
        {
            current_block = 11650488183268122163;
            break;
        }
        avlt = tree_create();
        if avlt.is_null() {
            fprintf(
                stdout,
                b"%s - create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
                cases[i as usize],
            );
            current_block = 8912262848414868146;
            break;
        } else {
            j = 0 as libc::c_int;
            while (j as libc::c_ulong) < strlen(cases[i as usize]) {
                if (tree_insert(
                    avlt,
                    *(cases[i as usize]).offset(j as isize) as libc::c_int,
                ))
                    .is_null() || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"%s - insert %c failed\n\0" as *const u8 as *const libc::c_char,
                        cases[i as usize],
                        *(cases[i as usize]).offset(j as isize) as libc::c_int,
                    );
                    current_block = 17420632000678864808;
                    break 's_8;
                } else {
                    j += 1;
                    j;
                }
            }
            avl_destroy(avlt);
            i += 1;
            i;
        }
    }
    match current_block {
        11650488183268122163 => return 1 as libc::c_int,
        17420632000678864808 => {
            avl_destroy(avlt);
        }
        _ => {}
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_chain_deletion() -> libc::c_int {
    let mut current_block: u64;
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut i: libc::c_int = 0;
    let mut j: libc::c_int = 0;
    let mut cases: [*mut libc::c_char; 14] = [
        b"PHXDLTbFJNZK\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"T\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTbFJNZdK\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"T\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTbFJNdK\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"T\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTbFRVZU\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"L\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTbBFRVZU\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"L\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"PHXDLTbBRVZU\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        b"L\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        0 as *mut libc::c_char,
        0 as *mut libc::c_char,
    ];
    i = 0 as libc::c_int;
    's_8: loop {
        if !((i as libc::c_ulong)
            < (::core::mem::size_of::<[*mut libc::c_char; 14]>() as libc::c_ulong)
                .wrapping_div(
                    ::core::mem::size_of::<*mut libc::c_char>() as libc::c_ulong,
                ) && !(cases[i as usize]).is_null())
        {
            current_block = 9606288038608642794;
            break;
        }
        avlt = tree_create();
        if avlt.is_null() {
            fprintf(
                stdout,
                b"%s-%s - create AVL tree failed\n\0" as *const u8
                    as *const libc::c_char,
                cases[i as usize],
                cases[(i + 1 as libc::c_int) as usize],
            );
            current_block = 16816613645545334547;
            break;
        } else {
            j = 0 as libc::c_int;
            while (j as libc::c_ulong) < strlen(cases[i as usize]) {
                if (tree_insert(
                    avlt,
                    *(cases[i as usize]).offset(j as isize) as libc::c_int,
                ))
                    .is_null() || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"%s-%s - insert %c failed\n\0" as *const u8
                            as *const libc::c_char,
                        cases[i as usize],
                        cases[(i + 1 as libc::c_int) as usize],
                        *(cases[i as usize]).offset(j as isize) as libc::c_int,
                    );
                    current_block = 11286773824929251669;
                    break 's_8;
                } else {
                    j += 1;
                    j;
                }
            }
            j = 0 as libc::c_int;
            while (j as libc::c_ulong) < strlen(cases[(i + 1 as libc::c_int) as usize]) {
                if tree_delete(
                    avlt,
                    *(cases[(i + 1 as libc::c_int) as usize]).offset(j as isize)
                        as libc::c_int,
                ) == 0 as libc::c_int || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"%s-%s - delete %c failed\n\0" as *const u8
                            as *const libc::c_char,
                        cases[i as usize],
                        cases[(i + 1 as libc::c_int) as usize],
                        *(cases[(i + 1 as libc::c_int) as usize]).offset(j as isize)
                            as libc::c_int,
                    );
                    current_block = 11286773824929251669;
                    break 's_8;
                } else {
                    j += 1;
                    j;
                }
            }
            avl_destroy(avlt);
            i += 2 as libc::c_int;
        }
    }
    match current_block {
        9606288038608642794 => return 1 as libc::c_int,
        11286773824929251669 => {
            avl_destroy(avlt);
        }
        _ => {}
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_permutation_insertion() -> libc::c_int {
    let mut a: [libc::c_char; 11] = *::core::mem::transmute::<
        &[u8; 11],
        &mut [libc::c_char; 11],
    >(b"ABCDEFGHIJ\0");
    permutation_error = 0 as libc::c_int;
    permute(
        a.as_mut_ptr(),
        0 as libc::c_int,
        (strlen(a.as_mut_ptr())).wrapping_sub(1 as libc::c_int as libc::c_ulong)
            as libc::c_int,
        Some(permutation_insert as unsafe extern "C" fn(*mut libc::c_char) -> ()),
    );
    return (permutation_error == 0 as libc::c_int) as libc::c_int;
}
unsafe extern "C" fn unit_test_permutation_deletion() -> libc::c_int {
    let mut a: [libc::c_char; 11] = *::core::mem::transmute::<
        &[u8; 11],
        &mut [libc::c_char; 11],
    >(b"ABCDEFGHIJ\0");
    permutation_error = 0 as libc::c_int;
    permute(
        a.as_mut_ptr(),
        0 as libc::c_int,
        (strlen(a.as_mut_ptr())).wrapping_sub(1 as libc::c_int as libc::c_ulong)
            as libc::c_int,
        Some(permutation_delete as unsafe extern "C" fn(*mut libc::c_char) -> ()),
    );
    return (permutation_error == 0 as libc::c_int) as libc::c_int;
}
unsafe extern "C" fn unit_test_random_insertion_deletion() -> libc::c_int {
    let mut current_block: u64;
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut ninsert: libc::c_int = 0;
    let mut ndelete: libc::c_int = 0;
    let mut i: libc::c_int = 0;
    let mut key: libc::c_int = 0;
    let mut max: libc::c_int = 0;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
    } else {
        ninsert = 0 as libc::c_int;
        ndelete = 0 as libc::c_int;
        max = 9999 as libc::c_int;
        srand(time(0 as *mut time_t) as libc::c_uint);
        i = 1 as libc::c_int;
        loop {
            if !(i <= 1999 as libc::c_int) {
                current_block = 1841672684692190573;
                break;
            }
            key = rand() % max;
            if (tree_find(avlt, key)).is_null() {
                ninsert += 1;
                ninsert;
                if (tree_insert(avlt, key)).is_null()
                    || tree_check(avlt) != 1 as libc::c_int
                {
                    fprintf(
                        stdout,
                        b"insert %d failed\n\0" as *const u8 as *const libc::c_char,
                        key,
                    );
                    current_block = 13361082415293746692;
                    break;
                }
            }
            i += 1;
            i;
        }
        match current_block {
            1841672684692190573 => {
                i = 1 as libc::c_int;
                loop {
                    if !(i < max) {
                        current_block = 2370887241019905314;
                        break;
                    }
                    key = rand() % max;
                    if !(tree_find(avlt, key)).is_null() {
                        ndelete += 1;
                        ndelete;
                        if tree_delete(avlt, key) != 1 as libc::c_int
                            || tree_check(avlt) != 1 as libc::c_int
                        {
                            fprintf(
                                stdout,
                                b"delete %d failed\n\0" as *const u8 as *const libc::c_char,
                                key,
                            );
                            current_block = 13361082415293746692;
                            break;
                        }
                    }
                    i += 1;
                    i;
                }
                match current_block {
                    13361082415293746692 => {}
                    _ => {
                        printf(
                            b"\tstat: ninsert=%d, ndelete=%d\n\0" as *const u8
                                as *const libc::c_char,
                            ninsert,
                            ndelete,
                        );
                        avl_destroy(avlt);
                        return 1 as libc::c_int;
                    }
                }
            }
            _ => {}
        }
        avl_destroy(avlt);
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_min() -> libc::c_int {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
    } else if !((*avlt).min).is_null() || (tree_insert(avlt, 'B' as i32)).is_null()
        || (*avlt).min != tree_find(avlt, 'B' as i32)
        || (tree_insert(avlt, 'A' as i32)).is_null()
        || (*avlt).min != tree_find(avlt, 'A' as i32)
        || (tree_insert(avlt, 'C' as i32)).is_null()
        || (*avlt).min != tree_find(avlt, 'A' as i32)
        || tree_delete(avlt, 'B' as i32) != 1 as libc::c_int
        || (*avlt).min != tree_find(avlt, 'A' as i32)
        || tree_delete(avlt, 'A' as i32) != 1 as libc::c_int
        || (*avlt).min != tree_find(avlt, 'C' as i32)
        || tree_delete(avlt, 'C' as i32) != 1 as libc::c_int || !((*avlt).min).is_null()
    {
        fprintf(stdout, b"invalid min\n\0" as *const u8 as *const libc::c_char);
        avl_destroy(avlt);
    } else {
        avl_destroy(avlt);
        return 1 as libc::c_int;
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn unit_test_dup() -> libc::c_int {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    let mut n1: *mut avlnode = 0 as *mut avlnode;
    let mut n2: *mut avlnode = 0 as *mut avlnode;
    avlt = tree_create();
    if avlt.is_null() {
        fprintf(
            stdout,
            b"create AVL tree failed\n\0" as *const u8 as *const libc::c_char,
        );
    } else {
        n1 = tree_insert(avlt, 'N' as i32);
        if n1.is_null()
            || {
                n2 = tree_insert(avlt, 'N' as i32);
                n2.is_null()
            }
        {
            fprintf(stdout, b"insert failed\n\0" as *const u8 as *const libc::c_char);
        } else if n1 == n2 || (*n1).right != n2 {
            fprintf(stdout, b"invalid dup\n\0" as *const u8 as *const libc::c_char);
        } else {
            avl_destroy(avlt);
            return 1 as libc::c_int;
        }
        avl_destroy(avlt);
    }
    return 0 as libc::c_int;
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
