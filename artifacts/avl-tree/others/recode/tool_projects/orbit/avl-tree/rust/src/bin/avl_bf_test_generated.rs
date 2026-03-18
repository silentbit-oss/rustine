/*
 * Generated test for avl_apply function
 * Tests tree traversal with callback function in PREORDER, INORDER, POSTORDER
 */

// Import the AVL tree module
use avl_tree::{avl_create, avl_insert, avl_apply, avl_check_order, avl_check_height, AvlTraversal, AvlTree};

/* Test state structure to collect visited nodes */
struct VisitContext {
    values: Vec<i32>,
}

impl VisitContext {
    fn new() -> Self {
        VisitContext {
            values: Vec::new(),
        }
    }
}

/* Helper functions */
fn tree_create() -> AvlTree<i32> {
    avl_create()
}

fn tree_insert(tree: &mut AvlTree<i32>, key: i32) -> bool {
    avl_insert(tree, key).is_some()
}

fn tree_check(tree: &AvlTree<i32>) -> bool {
    let min = i32::MIN;
    let max = i32::MAX;

    if !avl_check_order(tree, &min, &max) {
        eprintln!("tree_check: invalid order");
        return false;
    }

    if !avl_check_height(tree) {
        eprintln!("tree_check: invalid height");
        return false;
    }

    true
}

/* Test PREORDER traversal */
fn test_preorder() -> i32 {
    println!("Testing PREORDER traversal...");

    let mut tree = tree_create();

    /* Build a tree with 7 nodes: 4, 2, 6, 1, 3, 5, 7 */
    let keys = vec![4, 2, 6, 1, 3, 5, 7];
    let num_keys = 7;

    for &key in &keys {
        if !tree_insert(&mut tree, key) || !tree_check(&tree) {
            eprintln!("insert {} failed", key);
            return 1;
        }
    }

    /* Expected PREORDER: 4, 2, 1, 3, 6, 5, 7 */
    let expected = vec![4, 2, 1, 3, 6, 5, 7];

    /* Create context to collect visited values */
    let mut ctx = VisitContext::new();

    /* Apply traversal with closure that captures context */
    let result = avl_apply(&tree, |data: &i32| {
        ctx.values.push(*data);
        Ok(())
    }, AvlTraversal::PreOrder);

    if result.is_err() {
        eprintln!("avl_apply failed");
        return 1;
    }

    /* Verify results */
    if ctx.values.len() != num_keys {
        eprintln!("PREORDER: Expected {} values, got {}", num_keys, ctx.values.len());
        return 1;
    }

    for i in 0..num_keys {
        if ctx.values[i] != expected[i] {
            eprintln!("PREORDER: Mismatch at position {}: expected {}, got {}",
                    i, expected[i], ctx.values[i]);
            return 1;
        }
    }

    println!("PREORDER test PASSED");
    0
}

/* Test INORDER traversal */
fn test_inorder() -> i32 {
    println!("\nTesting INORDER traversal...");

    let mut tree = tree_create();

    /* Build a tree with 7 nodes: 4, 2, 6, 1, 3, 5, 7 */
    let keys = vec![4, 2, 6, 1, 3, 5, 7];
    let num_keys = 7;

    for &key in &keys {
        if !tree_insert(&mut tree, key) || !tree_check(&tree) {
            eprintln!("insert {} failed", key);
            return 1;
        }
    }

    /* Expected INORDER: 1, 2, 3, 4, 5, 6, 7 (sorted) */
    let expected = vec![1, 2, 3, 4, 5, 6, 7];

    /* Create context to collect visited values */
    let mut ctx = VisitContext::new();

    /* Apply traversal with closure that captures context */
    let result = avl_apply(&tree, |data: &i32| {
        ctx.values.push(*data);
        Ok(())
    }, AvlTraversal::InOrder);

    if result.is_err() {
        eprintln!("avl_apply failed");
        return 1;
    }

    /* Verify results */
    if ctx.values.len() != num_keys {
        eprintln!("INORDER: Expected {} values, got {}", num_keys, ctx.values.len());
        return 1;
    }

    for i in 0..num_keys {
        if ctx.values[i] != expected[i] {
            eprintln!("INORDER: Mismatch at position {}: expected {}, got {}",
                    i, expected[i], ctx.values[i]);
            return 1;
        }
    }

    println!("INORDER test PASSED");
    0
}

/* Test POSTORDER traversal */
fn test_postorder() -> i32 {
    println!("\nTesting POSTORDER traversal...");

    let mut tree = tree_create();

    /* Build a tree with 7 nodes: 4, 2, 6, 1, 3, 5, 7 */
    let keys = vec![4, 2, 6, 1, 3, 5, 7];
    let num_keys = 7;

    for &key in &keys {
        if !tree_insert(&mut tree, key) || !tree_check(&tree) {
            eprintln!("insert {} failed", key);
            return 1;
        }
    }

    /* Expected POSTORDER: 1, 3, 2, 5, 7, 6, 4 */
    let expected = vec![1, 3, 2, 5, 7, 6, 4];

    /* Create context to collect visited values */
    let mut ctx = VisitContext::new();

    /* Apply traversal with closure that captures context */
    let result = avl_apply(&tree, |data: &i32| {
        ctx.values.push(*data);
        Ok(())
    }, AvlTraversal::PostOrder);

    if result.is_err() {
        eprintln!("avl_apply failed");
        return 1;
    }

    /* Verify results */
    if ctx.values.len() != num_keys {
        eprintln!("POSTORDER: Expected {} values, got {}", num_keys, ctx.values.len());
        return 1;
    }

    for i in 0..num_keys {
        if ctx.values[i] != expected[i] {
            eprintln!("POSTORDER: Mismatch at position {}: expected {}, got {}",
                    i, expected[i], ctx.values[i]);
            return 1;
        }
    }

    println!("POSTORDER test PASSED");
    0
}

fn main() {
    let mut failures = 0;

    println!("=== Testing avl_apply function ===\n");

    if test_preorder() != 0 { failures += 1; }
    if test_inorder() != 0 { failures += 1; }
    if test_postorder() != 0 { failures += 1; }

    println!("\n=== Test Results ===");
    if failures == 0 {
        println!("All tests PASSED");
        std::process::exit(0);
    } else {
        println!("{} test(s) FAILED", failures);
        std::process::exit(1);
    }
}
