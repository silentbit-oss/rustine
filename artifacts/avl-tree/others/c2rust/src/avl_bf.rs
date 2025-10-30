use ::libc;
extern "C" {
    fn printf(_: *const libc::c_char, _: ...) -> libc::c_int;
    fn malloc(_: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
}
pub type avltraversal = libc::c_uint;
pub const POSTORDER: avltraversal = 2;
pub const INORDER: avltraversal = 1;
pub const PREORDER: avltraversal = 0;
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
#[no_mangle]
pub unsafe extern "C" fn avl_create(
    mut compare_func: Option::<
        unsafe extern "C" fn(*const libc::c_void, *const libc::c_void) -> libc::c_int,
    >,
    mut destroy_func: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
) -> *mut avltree {
    let mut avlt: *mut avltree = 0 as *mut avltree;
    avlt = malloc(::core::mem::size_of::<avltree>() as libc::c_ulong) as *mut avltree;
    if avlt.is_null() {
        return 0 as *mut avltree;
    }
    (*avlt).compare = compare_func;
    (*avlt).destroy = destroy_func;
    (*avlt).nil.parent = &mut (*avlt).nil;
    (*avlt).nil.right = (*avlt).nil.parent;
    (*avlt).nil.left = (*avlt).nil.right;
    (*avlt).nil.bf = 0 as libc::c_int as libc::c_char;
    (*avlt).nil.data = 0 as *mut libc::c_void;
    (*avlt).root.parent = &mut (*avlt).nil;
    (*avlt).root.right = (*avlt).root.parent;
    (*avlt).root.left = (*avlt).root.right;
    (*avlt).root.bf = 0 as libc::c_int as libc::c_char;
    (*avlt).root.data = 0 as *mut libc::c_void;
    (*avlt).min = 0 as *mut avlnode;
    return avlt;
}
#[no_mangle]
pub unsafe extern "C" fn avl_destroy(mut avlt: *mut avltree) {
    destroy(avlt, (*avlt).root.left);
    free(avlt as *mut libc::c_void);
}
#[no_mangle]
pub unsafe extern "C" fn avl_find(
    mut avlt: *mut avltree,
    mut data: *mut libc::c_void,
) -> *mut avlnode {
    let mut p: *mut avlnode = 0 as *mut avlnode;
    p = (*avlt).root.left;
    while p != &mut (*avlt).nil as *mut avlnode {
        let mut cmp: libc::c_int = 0;
        cmp = ((*avlt).compare).expect("non-null function pointer")(data, (*p).data);
        if cmp == 0 as libc::c_int {
            return p;
        }
        p = if cmp < 0 as libc::c_int { (*p).left } else { (*p).right };
    }
    return 0 as *mut avlnode;
}
#[no_mangle]
pub unsafe extern "C" fn avl_successor(
    mut avlt: *mut avltree,
    mut node: *mut avlnode,
) -> *mut avlnode {
    let mut p: *mut avlnode = 0 as *mut avlnode;
    p = (*node).right;
    if p != &mut (*avlt).nil as *mut avlnode {
        while (*p).left != &mut (*avlt).nil as *mut avlnode {
            p = (*p).left;
        }
    } else {
        p = (*node).parent;
        while node == (*p).right {
            node = p;
            p = (*p).parent;
        }
        if p == &mut (*avlt).root as *mut avlnode {
            p = 0 as *mut avlnode;
        }
    }
    return p;
}
#[no_mangle]
pub unsafe extern "C" fn avl_apply(
    mut avlt: *mut avltree,
    mut node: *mut avlnode,
    mut func: Option::<
        unsafe extern "C" fn(*mut libc::c_void, *mut libc::c_void) -> libc::c_int,
    >,
    mut cookie: *mut libc::c_void,
    mut order: avltraversal,
) -> libc::c_int {
    let mut err: libc::c_int = 0;
    if node != &mut (*avlt).nil as *mut avlnode {
        if order as libc::c_uint == PREORDER as libc::c_int as libc::c_uint
            && {
                err = func.expect("non-null function pointer")((*node).data, cookie);
                err != 0 as libc::c_int
            }
        {
            return err;
        }
        err = avl_apply(avlt, (*node).left, func, cookie, order);
        if err != 0 as libc::c_int {
            return err;
        }
        if order as libc::c_uint == INORDER as libc::c_int as libc::c_uint
            && {
                err = func.expect("non-null function pointer")((*node).data, cookie);
                err != 0 as libc::c_int
            }
        {
            return err;
        }
        err = avl_apply(avlt, (*node).right, func, cookie, order);
        if err != 0 as libc::c_int {
            return err;
        }
        if order as libc::c_uint == POSTORDER as libc::c_int as libc::c_uint
            && {
                err = func.expect("non-null function pointer")((*node).data, cookie);
                err != 0 as libc::c_int
            }
        {
            return err;
        }
    }
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn avl_print(
    mut avlt: *mut avltree,
    mut print_func: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
) {
    printf(b"\n--\n\0" as *const u8 as *const libc::c_char);
    print(
        avlt,
        (*avlt).root.left,
        print_func,
        0 as libc::c_int,
        b"T\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
    );
    printf(
        b"\nheight = %d\n\0" as *const u8 as *const libc::c_char,
        check_height(avlt, (*avlt).root.left),
    );
}
#[no_mangle]
pub unsafe extern "C" fn avl_check_order(
    mut avlt: *mut avltree,
    mut min: *mut libc::c_void,
    mut max: *mut libc::c_void,
) -> libc::c_int {
    return check_order(avlt, (*avlt).root.left, min, max);
}
#[no_mangle]
pub unsafe extern "C" fn avl_check_height(mut avlt: *mut avltree) -> libc::c_int {
    let mut height: libc::c_int = 0;
    height = check_height(avlt, (*avlt).root.left);
    return if height < 0 as libc::c_int { 0 as libc::c_int } else { 1 as libc::c_int };
}
#[no_mangle]
pub unsafe extern "C" fn avl_insert(
    mut avlt: *mut avltree,
    mut data: *mut libc::c_void,
) -> *mut avlnode {
    let mut current: *mut avlnode = 0 as *mut avlnode;
    let mut parent: *mut avlnode = 0 as *mut avlnode;
    let mut new_node: *mut avlnode = 0 as *mut avlnode;
    current = (*avlt).root.left;
    parent = &mut (*avlt).root;
    while current != &mut (*avlt).nil as *mut avlnode {
        let mut cmp: libc::c_int = 0;
        cmp = ((*avlt).compare)
            .expect("non-null function pointer")(data, (*current).data);
        parent = current;
        current = if cmp < 0 as libc::c_int {
            (*current).left
        } else {
            (*current).right
        };
    }
    new_node = malloc(::core::mem::size_of::<avlnode>() as libc::c_ulong)
        as *mut avlnode;
    current = new_node;
    if current.is_null() {
        return 0 as *mut avlnode;
    }
    (*current).right = &mut (*avlt).nil;
    (*current).left = (*current).right;
    (*current).parent = parent;
    (*current).bf = 0 as libc::c_int as libc::c_char;
    (*current).data = data;
    if parent == &mut (*avlt).root as *mut avlnode
        || ((*avlt).compare).expect("non-null function pointer")(data, (*parent).data)
            < 0 as libc::c_int
    {
        (*parent).left = current;
    } else {
        (*parent).right = current;
    }
    if ((*avlt).min).is_null()
        || ((*avlt).compare)
            .expect("non-null function pointer")((*current).data, (*(*avlt).min).data)
            < 0 as libc::c_int
    {
        (*avlt).min = current;
    }
    while current != (*avlt).root.left {
        if current == (*parent).left {
            if (*parent).bf as libc::c_int == 1 as libc::c_int {
                (*parent).bf = 0 as libc::c_int as libc::c_char;
                break;
            } else if (*parent).bf as libc::c_int == 0 as libc::c_int {
                (*parent).bf = -(1 as libc::c_int) as libc::c_char;
            } else if (*parent).bf as libc::c_int == -(1 as libc::c_int) {
                fix_insert_leftimbalance(avlt, parent);
                break;
            }
        } else if (*parent).bf as libc::c_int == -(1 as libc::c_int) {
            (*parent).bf = 0 as libc::c_int as libc::c_char;
            break;
        } else if (*parent).bf as libc::c_int == 0 as libc::c_int {
            (*parent).bf = 1 as libc::c_int as libc::c_char;
        } else if (*parent).bf as libc::c_int == 1 as libc::c_int {
            fix_insert_rightimbalance(avlt, parent);
            break;
        }
        current = parent;
        parent = (*current).parent;
    }
    return new_node;
}
#[no_mangle]
pub unsafe extern "C" fn avl_delete(
    mut avlt: *mut avltree,
    mut node: *mut avlnode,
    mut keep: libc::c_int,
) -> *mut libc::c_void {
    let mut current: *mut avlnode = 0 as *mut avlnode;
    let mut parent: *mut avlnode = 0 as *mut avlnode;
    let mut target: *mut avlnode = 0 as *mut avlnode;
    let mut data: *mut libc::c_void = 0 as *mut libc::c_void;
    data = (*node).data;
    if (*node).left == &mut (*avlt).nil as *mut avlnode
        || (*node).right == &mut (*avlt).nil as *mut avlnode
    {
        target = node;
        if (*avlt).min == target {
            (*avlt).min = avl_successor(avlt, target);
        }
    } else {
        target = avl_successor(avlt, node);
        (*node).data = (*target).data;
    }
    current = target;
    parent = (*current).parent;
    while current != (*avlt).root.left {
        if current == (*parent).left {
            if (*parent).bf as libc::c_int == -(1 as libc::c_int) {
                (*parent).bf = 0 as libc::c_int as libc::c_char;
            } else if (*parent).bf as libc::c_int == 0 as libc::c_int {
                (*parent).bf = 1 as libc::c_int as libc::c_char;
                break;
            } else if (*parent).bf as libc::c_int == 1 as libc::c_int {
                parent = fix_delete_rightimbalance(avlt, parent);
                if (*parent).bf as libc::c_int == -(1 as libc::c_int) {
                    break;
                }
            }
        } else if (*parent).bf as libc::c_int == 1 as libc::c_int {
            (*parent).bf = 0 as libc::c_int as libc::c_char;
        } else if (*parent).bf as libc::c_int == 0 as libc::c_int {
            (*parent).bf = -(1 as libc::c_int) as libc::c_char;
            break;
        } else if (*parent).bf as libc::c_int == -(1 as libc::c_int) {
            parent = fix_delete_leftimbalance(avlt, parent);
            if (*parent).bf as libc::c_int == 1 as libc::c_int {
                break;
            }
        }
        current = parent;
        parent = (*current).parent;
    }
    let mut child: *mut avlnode = 0 as *mut avlnode;
    child = if (*target).left == &mut (*avlt).nil as *mut avlnode {
        (*target).right
    } else {
        (*target).left
    };
    if child != &mut (*avlt).nil as *mut avlnode {
        (*child).parent = (*target).parent;
    }
    if target == (*(*target).parent).left {
        (*(*target).parent).left = child;
    } else {
        (*(*target).parent).right = child;
    }
    free(target as *mut libc::c_void);
    if keep == 0 as libc::c_int {
        ((*avlt).destroy).expect("non-null function pointer")(data);
        data = 0 as *mut libc::c_void;
    }
    return data;
}
unsafe extern "C" fn rotate_left(
    mut avlt: *mut avltree,
    mut x: *mut avlnode,
) -> *mut avlnode {
    let mut y: *mut avlnode = 0 as *mut avlnode;
    y = (*x).right;
    (*x).right = (*y).left;
    if (*x).right != &mut (*avlt).nil as *mut avlnode {
        (*(*x).right).parent = x;
    }
    (*y).parent = (*x).parent;
    if x == (*(*x).parent).left {
        (*(*x).parent).left = y;
    } else {
        (*(*x).parent).right = y;
    }
    (*y).left = x;
    (*x).parent = y;
    return y;
}
unsafe extern "C" fn rotate_right(
    mut avlt: *mut avltree,
    mut x: *mut avlnode,
) -> *mut avlnode {
    let mut y: *mut avlnode = 0 as *mut avlnode;
    y = (*x).left;
    (*x).left = (*y).right;
    if (*x).left != &mut (*avlt).nil as *mut avlnode {
        (*(*x).left).parent = x;
    }
    (*y).parent = (*x).parent;
    if x == (*(*x).parent).left {
        (*(*x).parent).left = y;
    } else {
        (*(*x).parent).right = y;
    }
    (*y).right = x;
    (*x).parent = y;
    return y;
}
unsafe extern "C" fn fix_insert_leftimbalance(
    mut avlt: *mut avltree,
    mut p: *mut avlnode,
) -> *mut avlnode {
    if (*(*p).left).bf as libc::c_int == (*p).bf as libc::c_int {
        p = rotate_right(avlt, p);
        (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
        (*p).bf = (*(*p).right).bf;
    } else {
        let mut oldbf: libc::c_int = 0;
        oldbf = (*(*(*p).left).right).bf as libc::c_int;
        rotate_left(avlt, (*p).left);
        p = rotate_right(avlt, p);
        (*p).bf = 0 as libc::c_int as libc::c_char;
        if oldbf == -(1 as libc::c_int) {
            (*(*p).left).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).right).bf = 1 as libc::c_int as libc::c_char;
        } else if oldbf == 1 as libc::c_int {
            (*(*p).left).bf = -(1 as libc::c_int) as libc::c_char;
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
        } else if oldbf == 0 as libc::c_int {
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).left).bf = (*(*p).right).bf;
        }
    }
    return p;
}
unsafe extern "C" fn fix_insert_rightimbalance(
    mut avlt: *mut avltree,
    mut p: *mut avlnode,
) -> *mut avlnode {
    if (*(*p).right).bf as libc::c_int == (*p).bf as libc::c_int {
        p = rotate_left(avlt, p);
        (*(*p).left).bf = 0 as libc::c_int as libc::c_char;
        (*p).bf = (*(*p).left).bf;
    } else {
        let mut oldbf: libc::c_int = 0;
        oldbf = (*(*(*p).right).left).bf as libc::c_int;
        rotate_right(avlt, (*p).right);
        p = rotate_left(avlt, p);
        (*p).bf = 0 as libc::c_int as libc::c_char;
        if oldbf == -(1 as libc::c_int) {
            (*(*p).left).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).right).bf = 1 as libc::c_int as libc::c_char;
        } else if oldbf == 1 as libc::c_int {
            (*(*p).left).bf = -(1 as libc::c_int) as libc::c_char;
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
        } else if oldbf == 0 as libc::c_int {
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).left).bf = (*(*p).right).bf;
        }
    }
    return p;
}
unsafe extern "C" fn fix_delete_leftimbalance(
    mut avlt: *mut avltree,
    mut p: *mut avlnode,
) -> *mut avlnode {
    if (*(*p).left).bf as libc::c_int == -(1 as libc::c_int) {
        p = rotate_right(avlt, p);
        (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
        (*p).bf = (*(*p).right).bf;
    } else if (*(*p).left).bf as libc::c_int == 0 as libc::c_int {
        p = rotate_right(avlt, p);
        (*p).bf = 1 as libc::c_int as libc::c_char;
        (*(*p).right).bf = -(1 as libc::c_int) as libc::c_char;
    } else if (*(*p).left).bf as libc::c_int == 1 as libc::c_int {
        let mut oldbf: libc::c_int = 0;
        oldbf = (*(*(*p).left).right).bf as libc::c_int;
        rotate_left(avlt, (*p).left);
        p = rotate_right(avlt, p);
        (*p).bf = 0 as libc::c_int as libc::c_char;
        if oldbf == -(1 as libc::c_int) {
            (*(*p).left).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).right).bf = 1 as libc::c_int as libc::c_char;
        } else if oldbf == 1 as libc::c_int {
            (*(*p).left).bf = -(1 as libc::c_int) as libc::c_char;
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
        } else if oldbf == 0 as libc::c_int {
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).left).bf = (*(*p).right).bf;
        }
    }
    return p;
}
unsafe extern "C" fn fix_delete_rightimbalance(
    mut avlt: *mut avltree,
    mut p: *mut avlnode,
) -> *mut avlnode {
    if (*(*p).right).bf as libc::c_int == 1 as libc::c_int {
        p = rotate_left(avlt, p);
        (*(*p).left).bf = 0 as libc::c_int as libc::c_char;
        (*p).bf = (*(*p).left).bf;
    } else if (*(*p).right).bf as libc::c_int == 0 as libc::c_int {
        p = rotate_left(avlt, p);
        (*p).bf = -(1 as libc::c_int) as libc::c_char;
        (*(*p).left).bf = 1 as libc::c_int as libc::c_char;
    } else if (*(*p).right).bf as libc::c_int == -(1 as libc::c_int) {
        let mut oldbf: libc::c_int = 0;
        oldbf = (*(*(*p).right).left).bf as libc::c_int;
        rotate_right(avlt, (*p).right);
        p = rotate_left(avlt, p);
        (*p).bf = 0 as libc::c_int as libc::c_char;
        if oldbf == -(1 as libc::c_int) {
            (*(*p).left).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).right).bf = 1 as libc::c_int as libc::c_char;
        } else if oldbf == 1 as libc::c_int {
            (*(*p).left).bf = -(1 as libc::c_int) as libc::c_char;
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
        } else if oldbf == 0 as libc::c_int {
            (*(*p).right).bf = 0 as libc::c_int as libc::c_char;
            (*(*p).left).bf = (*(*p).right).bf;
        }
    }
    return p;
}
unsafe extern "C" fn check_order(
    mut avlt: *mut avltree,
    mut n: *mut avlnode,
    mut min: *mut libc::c_void,
    mut max: *mut libc::c_void,
) -> libc::c_int {
    if n == &mut (*avlt).nil as *mut avlnode {
        return 1 as libc::c_int;
    }
    if ((*avlt).compare).expect("non-null function pointer")((*n).data, min)
        < 0 as libc::c_int
        || ((*avlt).compare).expect("non-null function pointer")((*n).data, max)
            > 0 as libc::c_int
    {
        return 0 as libc::c_int;
    }
    return (check_order(avlt, (*n).left, min, (*n).data) != 0
        && check_order(avlt, (*n).right, (*n).data, max) != 0) as libc::c_int;
}
unsafe extern "C" fn check_height(
    mut avlt: *mut avltree,
    mut n: *mut avlnode,
) -> libc::c_int {
    let mut lh: libc::c_int = 0;
    let mut rh: libc::c_int = 0;
    let mut cmp: libc::c_int = 0;
    if n == &mut (*avlt).nil as *mut avlnode {
        return 0 as libc::c_int;
    }
    lh = check_height(avlt, (*n).left);
    if lh < 0 as libc::c_int {
        return lh;
    }
    rh = check_height(avlt, (*n).right);
    if rh < 0 as libc::c_int {
        return rh;
    }
    cmp = rh - lh;
    if cmp < -(1 as libc::c_int) || cmp > 1 as libc::c_int
        || cmp != (*n).bf as libc::c_int
    {
        return -(1 as libc::c_int);
    }
    return 1 as libc::c_int + (if lh > rh { lh } else { rh });
}
unsafe extern "C" fn print(
    mut avlt: *mut avltree,
    mut n: *mut avlnode,
    mut print_func: Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>,
    mut depth: libc::c_int,
    mut label: *mut libc::c_char,
) {
    if n != &mut (*avlt).nil as *mut avlnode {
        print(
            avlt,
            (*n).right,
            print_func,
            depth + 1 as libc::c_int,
            b"R\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        );
        printf(
            b"%*s\0" as *const u8 as *const libc::c_char,
            8 as libc::c_int * depth,
            b"\0" as *const u8 as *const libc::c_char,
        );
        if !label.is_null() {
            printf(b"%s: \0" as *const u8 as *const libc::c_char, label);
        }
        print_func.expect("non-null function pointer")((*n).data);
        printf(
            b" (%s%d)\n\0" as *const u8 as *const libc::c_char,
            if (*n).bf as libc::c_int >= 0 as libc::c_int {
                b"+\0" as *const u8 as *const libc::c_char
            } else {
                b"\0" as *const u8 as *const libc::c_char
            },
            (*n).bf as libc::c_int,
        );
        print(
            avlt,
            (*n).left,
            print_func,
            depth + 1 as libc::c_int,
            b"L\0" as *const u8 as *const libc::c_char as *mut libc::c_char,
        );
    }
}
unsafe extern "C" fn destroy(mut avlt: *mut avltree, mut n: *mut avlnode) {
    if n != &mut (*avlt).nil as *mut avlnode {
        destroy(avlt, (*n).left);
        destroy(avlt, (*n).right);
        ((*avlt).destroy).expect("non-null function pointer")((*n).data);
        free(n as *mut libc::c_void);
    }
}
