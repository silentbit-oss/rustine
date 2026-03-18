use translate_new::*;
use std::env;

pub fn main() {
    // Print sizes of structs (equivalent to C's sizeof)
    println!("\nquadtree_t: {}", std::mem::size_of::<Quadtree>());
    println!("quadtree_node_t: {}", std::mem::size_of::<QuadtreeNode>());
    println!("quadtree_bounds_t: {}", std::mem::size_of::<QuadtreeBounds>());
    println!("quadtree_point_t: {}", std::mem::size_of::<QuadtreePoint>());

    // Test tree functionality with colored output
    print!("\x1b[33mtree\x1b[0m ");
    test_tree();
    println!("\x1b[1;32m ✓ \x1b[0m");

    // Test node functionality with colored output
    print!("\x1b[33mnode\x1b[0m ");
    test_node();
    println!("\x1b[1;32m ✓ \x1b[0m");

    // Test bounds functionality with colored output
    print!("\x1b[33mbounds\x1b[0m ");
    test_bounds();
    println!("\x1b[1;32m ✓ \x1b[0m");

    // Test points functionality with colored output
    print!("\x1b[33mpoints\x1b[0m ");
    test_points();
    println!("\x1b[1;32m ✓ \x1b[0m");
}
