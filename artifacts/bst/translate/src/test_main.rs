use translate_new::*;
use std::env;
pub fn main() {
    test_insert_and_inorder();
    test_min_value_node();
    test_delete_leaf();
    test_delete_node_with_one_child();
    test_delete_node_with_two_children();
    test_delete_nonexistent_node();
    println!("All tests passed.");
}
