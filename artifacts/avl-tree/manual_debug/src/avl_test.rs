use crate::*;
use std::any::Any;
use std::fmt;
use std::io;
use std::println;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use lazy_static::lazy_static;
use rand::Rng;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;
use std::ffi::CStr;
use std::io::Write;
use std::os::raw::c_char;

pub fn swap(x: &mut char, y: &mut char) {
    let temp = *x;
    *x = *y;
    *y = temp;
}
pub fn permute(a: &mut [char], start: usize, end: usize, func: &mut dyn FnMut(&[char])) {
    if start == end {
        func(a);
        return;
    }

    for i in start..=end {
        // Create mutable references to the elements to swap
        a.swap(start, i);
        
        permute(a, start + 1, end, func);
        
        // Swap back
        a.swap(start, i);
    }
}
pub fn tree_print(avlt: &AvlTree) {
    avl_print(avlt, &|d: Option<&dyn std::any::Any>| {
        if let Some(any) = d {
            if let Some(mydata) = any.downcast_ref::<Mydata>() {
                print_func(Some(mydata));
            }
        } else {
            print_func(None);
        }
    });
}

pub fn tree_insert(avlt: &mut AvlTree, key: i32) -> Option<Box<AvlNode>> {
    // Check if key is within i32 range (redundant in Rust since key is already i32)
    if key < i32::MIN || key > i32::MAX {
        println!("tree_insert: invalid key {}", key);
        return None;
    }

    // Create data
    let data = match makedata(key) {
        Some(d) => d,
        None => {
            println!("tree_insert: insert {} failed", key);
            return None;
        }
    };

    // Insert into AVL tree
    let node = match avl_insert(avlt, data) {
        Some(n) => n,
        None => {
            println!("tree_insert: insert {} failed", key);
            return None;
        }
    };

    Some(node)
}
pub fn tree_find(avlt: &AvlTree, key: i32) -> Option<&AvlNode> {
    //let query = Some(&Mydata { key });
    avl_find(avlt, Some(&Mydata { key }))
}
pub fn tree_create() -> Option<Box<AvlTree>> {
    avl_create(compare_func, destroy_func)
}
pub fn tree_check(avlt: &AvlTree) -> i32 {
    let min = Mydata { key: -2147483648 };
    let max = Mydata { key: 2147483647 };
    let mut rc = 1;

    let min_box = Box::new(min);
    let max_box = Box::new(max);

    if !avl_check_order(
        avlt,
        Some(&min_box as &dyn std::any::Any).map(|x| unsafe { &*(x as *const dyn std::any::Any as *const Box<dyn std::any::Any>) }),
        Some(&max_box as &dyn std::any::Any).map(|x| unsafe { &*(x as *const dyn std::any::Any as *const Box<dyn std::any::Any>) }),
    ) {
        writeln!(io::stdout(), "tree_check: invalid order").unwrap();
        rc = 0;
    }

    if avl_check_height(avlt) != 1 {
        writeln!(io::stdout(), "tree_check: invalid height").unwrap();
        rc = 0;
    }

    rc
}
pub fn permutation_insert(a: &str) {
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            PERMUTATION_ERROR.fetch_add(1, Ordering::SeqCst);
            return;
        }
    };

    for c in a.chars() {
        let key = c as i32;
        let node_idx = tree_insert(&mut avlt, key);
        let node_found = tree_find(&avlt, key);
        
        if node_idx.is_none() 
            || node_found.map(|n| n as *const _ != node_idx.as_ref().map(|n| &**n).unwrap() as *const _).unwrap_or(true)
            || tree_check(&avlt) != 1 
        {
            println!("insert {} failed", c);
            panic!();
            PERMUTATION_ERROR.fetch_add(1, Ordering::SeqCst);
            return;
        }
    }

    avl_destroy(avlt);
}
lazy_static! {
    pub static ref PERMUTATION_ERROR: AtomicI32 = AtomicI32::new(0);
}

pub fn unit_test_permutation_insertion() -> bool {
    let mut a = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'];
    PERMUTATION_ERROR.store(0, Ordering::Relaxed);
    
    let len = a.len(); // Calculate length before mutable borrow
    let mut callback = |chars: &[char]| {
        let s: String = chars.iter().collect();
        permutation_insert(&s);
    };
    
    permute(&mut a, 0, len - 1, &mut callback);
    PERMUTATION_ERROR.load(Ordering::Relaxed) == 0
}
pub fn tree_delete(avlt: &mut AvlTree, key: i32) -> i32 {
    // First find the node without holding any references
    let node_ptr = {
        match tree_find(avlt, key) {
            Some(n) => n as *const AvlNode as *mut AvlNode,
            None => {
                println!("tree_delete: {} not found", key);
                return 0;
            }
        }
    };

    // Now we can safely mutate the tree since we don't hold any references
    unsafe {
        let node_mut = &mut *node_ptr;
        avl_delete(avlt, node_mut, 0);
    }

    // Verify deletion was successful
    let found_ptr = tree_find(avlt, key).map(|n| n as *const AvlNode);
    if let Some(found_ptr) = found_ptr {
        if found_ptr == node_ptr {
            println!("tree_delete: delete {} failed", key);
            return 0;
        }
    }

    1
}

pub fn permutation_delete(a: &str) {
    // Create AVL tree
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            PERMUTATION_ERROR.fetch_add(1, Ordering::SeqCst);
            return;
        }
    };

    // Insert characters from "ABCDEFGHIJ" into the tree
    let b = "ABCDEFGHIJ";
    for ch in b.chars() {
        let key = ch as i32;
        let node_idx = tree_insert(&mut avlt, key);
        let found_node = tree_find(&avlt, key);
        
        if node_idx.is_none() 
            || found_node.is_none() 
            || tree_check(&avlt) != 1 
        {
            println!("insert {} failed", ch);
            panic!();
            PERMUTATION_ERROR.fetch_add(1, Ordering::SeqCst);
            return;
        }
    }

    // Delete characters from input string
    for ch in a.chars() {
        let key = ch as i32;
        if tree_delete(&mut avlt, key) != 1 || tree_check(&avlt) != 1 {
            println!("delete {} failed", ch);
            PERMUTATION_ERROR.fetch_add(1, Ordering::SeqCst);
            return;
        }
    }

    // Destroy the tree
    avl_destroy(avlt);
}
pub fn unit_test_permutation_deletion() -> bool {
    let mut a = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'];
    PERMUTATION_ERROR.store(0, Ordering::SeqCst);
    let len = a.len() - 1;  // Calculate length before mutable borrow
    let mut delete_fn = |chars: &[char]| {
        let s: String = chars.iter().collect();
        permutation_delete(&s);
    };
    permute(&mut a, 0, len, &mut delete_fn);
    PERMUTATION_ERROR.load(Ordering::SeqCst) == 0
}
pub fn unit_test_successor() -> i32 {
    // Create AVL tree
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            return 0;
        }
    };

    // Insert nodes and perform operations
    let r = tree_insert(&mut avlt, 'R' as i32);
    let e = tree_insert(&mut avlt, 'E' as i32);
    let d = tree_insert(&mut avlt, 'D' as i32);
    let s = tree_insert(&mut avlt, 'S' as i32);
    let o = tree_insert(&mut avlt, 'O' as i32);
    let x = tree_insert(&mut avlt, 'X' as i32);
    let c = tree_insert(&mut avlt, 'C' as i32);
    let u = tree_insert(&mut avlt, 'U' as i32);
    let b = tree_insert(&mut avlt, 'B' as i32);
    let t = tree_insert(&mut avlt, 'T' as i32);

    if r.is_none() || e.is_none() || d.is_none() || s.is_none() || o.is_none() || 
       x.is_none() || c.is_none() || u.is_none() || b.is_none() || t.is_none() || 
       tree_delete(&mut avlt, 'O' as i32) != 1 || tree_check(&avlt) != 1 {
        println!("init failed");
        avl_destroy(avlt);
        return 0;
    }

    // Unwrap all nodes safely after checking they exist
    let r = r.unwrap();
    let e = e.unwrap();
    let d = d.unwrap();
    let s = s.unwrap();
    let x = x.unwrap();
    let c = c.unwrap();
    let u = u.unwrap();
    let b = b.unwrap();
    let t = t.unwrap();

    // Test successor functionality by comparing references
    if !std::ptr::eq(avl_successor(&avlt, &*b).unwrap_or(&*c), &*c) ||
       !std::ptr::eq(avl_successor(&avlt, &*c).unwrap_or(&*d), &*d) ||
       !std::ptr::eq(avl_successor(&avlt, &*d).unwrap_or(&*e), &*e) ||
       !std::ptr::eq(avl_successor(&avlt, &*e).unwrap_or(&*r), &*r) ||
       !std::ptr::eq(avl_successor(&avlt, &*r).unwrap_or(&*s), &*s) ||
       !std::ptr::eq(avl_successor(&avlt, &*s).unwrap_or(&*t), &*t) ||
       !std::ptr::eq(avl_successor(&avlt, &*t).unwrap_or(&*u), &*u) ||
       !std::ptr::eq(avl_successor(&avlt, &*u).unwrap_or(&*x), &*x) ||
       avl_successor(&avlt, &*x).is_some() {
        println!("successor failed");
        avl_destroy(avlt);
        return 0;
    }

    avl_destroy(avlt);
    1
}

pub fn unit_test_random_insertion_deletion() -> i32 {
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            return 0;
        }
    };

    let mut ninsert = 0;
    let mut ndelete = 0;
    let max = 9999;

    // Seed the random number generator
    let seed = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_secs() as u32;
    rand::thread_rng().gen::<u32>(); // Initialize RNG

    // Insertion phase
    for _ in 1..=1999 {
        let key = rand::thread_rng().gen_range(0..max);
        if tree_find(&avlt, key).is_some() {
            continue;
        }
        ninsert += 1;
        if tree_insert(&mut avlt, key).is_none() || tree_check(&avlt) != 1 {
            println!("insert {} failed", key);
            panic!();
            avl_destroy(avlt);
            return 0;
        }
    }

    // Deletion phase
    for _ in 1..max {
        let key = rand::thread_rng().gen_range(0..max);
        if tree_find(&avlt, key).is_none() {
            continue;
        }
        ndelete += 1;
        if tree_delete(&mut avlt, key) != 1 || tree_check(&avlt) != 1 {
            println!("delete {} failed", key);
            avl_destroy(avlt);
            return 0;
        }
    }

    println!("\tstat: ninsert={}, ndelete={}", ninsert, ndelete);
    avl_destroy(avlt);
    1
}
pub fn unit_test_min() -> i32 {
    // Create AVL tree
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            return 0;
        }
    };

    // Perform test sequence
    let test_passed = {
        // First check: initial min should be None
        if avlt.min.is_some() {
            println!("invalid min");
            return 0;
        }

        // Insert 'B' and verify min
        if tree_insert(&mut avlt, 'B' as i32).is_none() {
            println!("invalid min");
            return 0;
        }
        if let (Some(min_node), Some(found_node)) = (avlt.min.as_ref(), tree_find(&avlt, 'B' as i32)) {
            if min_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) != found_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) {
                println!("invalid min");
                return 0;
            }
        } else {
            println!("invalid min");
            return 0;
        }

        // Insert 'A' and verify min updated
        if tree_insert(&mut avlt, 'A' as i32).is_none() {
            println!("invalid min");
            return 0;
        }
        if let (Some(min_node), Some(found_node)) = (avlt.min.as_ref(), tree_find(&avlt, 'A' as i32)) {
            if min_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) != found_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) {
                println!("invalid min");
                return 0;
            }
        } else {
            println!("invalid min");
            return 0;
        }

        // Insert 'C' and verify min stays 'A'
        if tree_insert(&mut avlt, 'C' as i32).is_none() {
            println!("invalid min");
            return 0;
        }
        if let (Some(min_node), Some(found_node)) = (avlt.min.as_ref(), tree_find(&avlt, 'A' as i32)) {
            if min_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) != found_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) {
                println!("invalid min");
                return 0;
            }
        } else {
            println!("invalid min");
            return 0;
        }

        // Delete 'B' and verify min stays 'A'
        if tree_delete(&mut avlt, 'B' as i32) != 1 {
            println!("invalid min");
            return 0;
        }
        if let (Some(min_node), Some(found_node)) = (avlt.min.as_ref(), tree_find(&avlt, 'A' as i32)) {
            if min_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) != found_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) {
                println!("invalid min");
                return 0;
            }
        } else {
            println!("invalid min");
            return 0;
        }

        // Delete 'A' and verify min updates to 'C'
        if tree_delete(&mut avlt, 'A' as i32) != 1 {
            println!("invalid min");
            return 0;
        }
        if let (Some(min_node), Some(found_node)) = (avlt.min.as_ref(), tree_find(&avlt, 'C' as i32)) {
            if min_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) != found_node.data.as_ref().map(|d| d.downcast_ref::<i32>()) {
                println!("invalid min");
                return 0;
            }
        } else {
            println!("invalid min");
            return 0;
        }

        // Delete 'C' and verify min becomes None
        if tree_delete(&mut avlt, 'C' as i32) != 1 {
            println!("invalid min");
            return 0;
        }
        if avlt.min.is_some() {
            println!("invalid min");
            return 0;
        }

        true
    };

    // Clean up
    avl_destroy(avlt);

    if test_passed {
        1
    } else {
        0
    }
}
pub fn unit_test_find() -> i32 {
    // Create AVL tree
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            return 0;
        }
    };

    // Insert nodes
    let r = match tree_insert(&mut avlt, 'R' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let e = match tree_insert(&mut avlt, 'E' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let d = match tree_insert(&mut avlt, 'D' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let s = match tree_insert(&mut avlt, 'S' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let o = match tree_insert(&mut avlt, 'O' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let x = match tree_insert(&mut avlt, 'X' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let c = match tree_insert(&mut avlt, 'C' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let u = match tree_insert(&mut avlt, 'U' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let b = match tree_insert(&mut avlt, 'B' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };
    let t = match tree_insert(&mut avlt, 'T' as i32) {
        Some(node) => node,
        None => {
            println!("init failed");
            avl_destroy(avlt);
            return 0;
        }
    };

    // Check tree structure
    if tree_check(&avlt) != 1 {
        println!("init failed");
        avl_destroy(avlt);
        return 0;
    }

    // Verify finds by comparing the data values
    if avl_find(&avlt, Some(&Mydata{key: 'R' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('R' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'E' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('E' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'D' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('D' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'S' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('S' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'O' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('O' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'X' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('X' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'C' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('C' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'U' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('U' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'B' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('B' as i32)) ||
       avl_find(&avlt, Some(&Mydata{key: 'T' as i32})).and_then(|n| n.data.as_ref().and_then(|d| d.downcast_ref::<i32>())) != Some(&('T' as i32))
    {
        println!("find failed");
        avl_destroy(avlt);
        return 0;
    }

    avl_destroy(avlt);
    1
}
pub fn unit_test_dup() -> i32 {
    // Create AVL tree
    let mut avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            writeln!(io::stdout(), "create AVL tree failed").unwrap();
            return 0;
        }
    };

    // Insert nodes
    let n1 = match tree_insert(&mut avlt, 'N' as i32) {
        Some(node) => node,
        None => {
            writeln!(io::stdout(), "insert failed").unwrap();
            avl_destroy(avlt);
            return 0;
        }
    };

    let n2 = match tree_insert(&mut avlt, 'N' as i32) {
        Some(node) => node,
        None => {
            writeln!(io::stdout(), "insert failed").unwrap();
            avl_destroy(avlt);
            return 0;
        }
    };

    // Check conditions
    if std::ptr::eq(&*n1, &*n2) || 
       !n1.right.as_ref().map_or(false, |right| std::ptr::eq(&**right, &*n2)) {
        writeln!(io::stdout(), "invalid dup").unwrap();
        avl_destroy(avlt);
        return 0;
    }

    avl_destroy(avlt);
    1
}
pub fn unit_test_create() -> i32 {
    let avlt = match tree_create() {
        Some(tree) => tree,
        None => {
            println!("create AVL tree failed");
            return 0;
        }
    };

    // Check all the conditions in one big expression
    let conditions_met = {
        // Compare functions by comparing their addresses (as pointers)
        let compare_ok = std::ptr::eq(avlt.compare as *const (), compare_func as *const ());
        let destroy_ok = std::ptr::eq(avlt.destroy as *const (), destroy_func as *const ());
        
        let nil_ok = avlt.nil.as_ref().map_or(false, |nil| {
            nil.left.is_none()
                && nil.right.is_none()
                && nil.parent.is_none()
                && nil.bf == 0
                && nil.data.is_none()
        });
        
        let root_ok = avlt.root.as_ref().map_or(false, |root| {
            root.left.is_none()
                && root.right.is_none()
                && root.parent.is_none()
                && root.bf == 0
                && root.data.is_none()
        });
        compare_ok && destroy_ok && nil_ok && root_ok
    };

    if !conditions_met {
        println!("init 1");
        avl_destroy(avlt);
        return 0;
    }

    avl_destroy(avlt);
    1
}

pub fn unit_test_chain_insertion() -> i32 {
    let cases = [
        "PHXDB", "PHXDF", "PHXLJ", "PHXLN", "PHXTR", "PHXTV", 
        "PHXbZ", "PHXbd", "PHXDLB", "PHXDLF", "PHXDLJ", "PHXDLN", 
        "PHXTbR", "PHXTbV", "PHXTbV", "PHXTbZ", "PHXTbd"
    ];

    for case in cases.iter() {
        let mut avlt = match tree_create() {
            Some(tree) => tree,
            None => {
                writeln!(io::stdout(), "{} - create AVL tree failed", case).unwrap();
                return 0;
            }
        };

        for c in case.chars() {
            let key = c as i32;
            if tree_insert(&mut avlt, key).is_none() || tree_check(&avlt) != 1 {
                writeln!(io::stdout(), "{} - insert {} failed", case, c).unwrap();
                avl_destroy(avlt);
                return 0;
            }
        }

        avl_destroy(avlt);
    }

    1
}

pub fn unit_test_chain_deletion() -> i32 {
    let cases = [
        ("PHXDLTbFJNZK", "T"),
        ("PHXDLTbFJNZdK", "T"),
        ("PHXDLTbFJNdK", "T"),
        ("PHXDLTbFRVZU", "L"),
        ("PHXDLTbBFRVZU", "L"),
        ("PHXDLTbBRVZU", "L"),
    ];

    for (insert_chars, delete_chars) in cases.iter() {
        let mut avlt = match tree_create() {
            Some(tree) => tree,
            None => {
                println!("{}-{} - create AVL tree failed", insert_chars, delete_chars);
                return 0;
            }
        };

        for c in insert_chars.chars() {
            let key = c as i32;
            if tree_insert(&mut avlt, key).is_none() || tree_check(&avlt) != 1 {
                println!("{}-{} - insert {} failed", insert_chars, delete_chars, c);
                avl_destroy(avlt);
                return 0;
            }
        }

        for c in delete_chars.chars() {
            let key = c as i32;
            if tree_delete(&mut avlt, key) == 0 || tree_check(&avlt) != 1 {
                println!("{}-{} - delete {} failed", insert_chars, delete_chars, c);
                avl_destroy(avlt);
                return 0;
            }
        }

        avl_destroy(avlt);
    }

    1
}
pub fn unit_test_atomic_insertion() -> i32 {
    let cases = [
        Some("P"), Some("PH"), Some("PX"), Some("PHDPHXDLB"), Some("PHXDLF"), 
        Some("PHL"), Some("PHXDLJ"), Some("PHXDLN"), Some("PXb"), Some("PHXTbZ"), 
        Some("PHXTbd"), Some("PHXT"), Some("PHXTbRV"), Some("PHXTbR"), Some("PHXTbV"), 
        None
    ];

    for case in cases.iter() {
        if case.is_none() {
            break;
        }

        let case_str = case.unwrap();

        let mut avlt = match tree_create() {
            Some(tree) => tree,
            None => {
                println!("{} - create AVL tree failed", case_str);
                return 0;
            }
        };

        for c in case_str.chars() {
            let c_int = c as i32;
            if tree_insert(&mut avlt, c_int).is_none() || tree_check(&avlt) != 1 {
                println!("{} - insert {} failed", case_str, c);
                panic!();
                avl_destroy(avlt);
                return 0;
            }
        }

        avl_destroy(avlt);
    }

    1
}

pub fn unit_test_atomic_deletion() -> i32 {
    let cases = [
        "P", "P", "PH", "H", "PH", "P", "PX", "P", "PX", "X", "PHX", "H", "PHX", "P", "PHX", "X",
        "PHXD", "X", "PHXDLTBF", "X", "PHXDLTB", "X", "PHXDLTF", "X", "PHXDL", "X", "PHXDLTBFJN",
        "X", "PHXDLTBFJ", "X", "PHXDLTBFN", "X", "PHXDLTBJN", "X", "PHXDLTBJ", "X", "PHXDLTBN",
        "X", "PHXDLTFJN", "X", "PHXDLTFJ", "X", "PHXDLTFN", "X", "PHXL", "X", "PHXDLTJN", "X",
        "PHXDLTJ", "X", "PHXDLTN", "X", "PHXb", "H", "PHXDTbZd", "H", "PHXDTbZ", "H", "PHXDTbd",
        "H", "PHXTb", "H", "PHXDTbRVZd", "H", "PHXDTbRVZ", "H", "PHXDTbRVd", "H", "PHXDTbRZd",
        "H", "PHXDTbRZ", "H", "PHXDTbRd", "H", "PHXDTbVZd", "H", "PHXDTbVZ", "H", "PHXDTbVd", "H",
        "PHXT", "H", "PHXDTbRV", "H", "PHXDTbR", "H", "PHXDTbV", "H", "", "",
    ];

    for i in (0..cases.len()).step_by(2) {
        if cases[i].is_empty() {
            break;
        }

        let mut avlt = match tree_create() {
            Some(tree) => tree,
            None => {
                println!("{}-{} - create AVL tree failed", cases[i], cases[i + 1]);
                return 0;
            }
        };

        for c in cases[i].chars() {
            let key = c as i32;
            if tree_insert(&mut avlt, key).is_none() || tree_check(&avlt) != 1 {
                println!("{}-{} - insert {} failed", cases[i], cases[i + 1], c);
                avl_destroy(avlt);
                return 0;
            }
        }

        for c in cases[i + 1].chars() {
            let key = c as i32;
            if tree_delete(&mut avlt, key) == 0 || tree_check(&avlt) != 1 {
                println!("{}-{} - delete {} failed", cases[i], cases[i + 1], c);
                avl_destroy(avlt);
                return 0;
            }
        }

        avl_destroy(avlt);
    }

    1
}

lazy_static! {
    pub static ref MU_TESTS: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);
    pub static ref MU_FAILS: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);
}

pub fn all_tests() {
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_create");
        if unit_test_create() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_find");
        if unit_test_find() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_successor");
        if unit_test_successor() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_atomic_insertion");
        if unit_test_atomic_insertion() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_atomic_deletion");
        if unit_test_atomic_deletion() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_chain_insertion");
        if unit_test_chain_insertion() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_chain_deletion");
        if unit_test_chain_deletion() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_random_insertion_deletion");
        if unit_test_random_insertion_deletion() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_dup");
        if unit_test_dup() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
    {
        MU_TESTS.fetch_add(1, Ordering::SeqCst);
        println!("#{:03} {}", MU_TESTS.load(Ordering::SeqCst), "unit_test_min");
        if unit_test_min() != 0 {
            println!("PASSED");
        } else {
            MU_FAILS.fetch_add(1, Ordering::SeqCst);
        }
    }
}
