use translate::*;
use std::env;
use std::io;
use std::io::Write;
pub fn main() {
    // Print sizes of types (equivalent to C's sizeof)
    println!("\nquadtree_t: {}", std::mem::size_of::<Quadtree>());
    println!("quadtree_node_t: {}", std::mem::size_of::<QuadtreeNode>());
    println!("quadtree_bounds_t: {}", std::mem::size_of::<QuadtreeBounds>());
    println!("quadtree_point_t: {}", std::mem::size_of::<QuadtreePoint>());

    // Test tree with colored output
    print!("\x1b[33mtree\x1b[0m ");
    io::stdout().flush().unwrap();
    test_tree();
    println!("\x1b[1;32m ✓ \x1b[0m");

    // Test node with colored output
    print!("\x1b[33mnode\x1b[0m ");
    io::stdout().flush().unwrap();
    test_node();
    println!("\x1b[1;32m ✓ \x1b[0m");

    // Test bounds with colored output
    print!("\x1b[33mbounds\x1b[0m ");
    io::stdout().flush().unwrap();
    test_bounds();
    println!("\x1b[1;32m ✓ \x1b[0m");

    // Test points with colored output
    print!("\x1b[33mpoints\x1b[0m ");
    io::stdout().flush().unwrap();
    test_points();
    println!("\x1b[1;32m ✓ \x1b[0m");
}
