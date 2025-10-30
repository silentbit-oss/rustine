use crate::*;
use std::assert;
use std::assert_eq;
use std::fmt::Write;

pub fn build_inorder_string(root: Option<&Box<Node>>, buffer: &mut String, pos: &mut usize) {
    if let Some(root) = root {
        build_inorder_string(root.left.as_ref(), buffer, pos);
        
        // Use write! to append formatted string to buffer and get the number of bytes written
        let written = buffer.len();
        write!(buffer, "{} ", root.key).unwrap();
        *pos += buffer.len() - written;
        
        build_inorder_string(root.right.as_ref(), buffer, pos);
    }
}
pub fn capture_inorder(root: Option<&Box<Node>>) -> String {
    let mut result = String::with_capacity(1000); // Pre-allocate capacity similar to malloc(1000)
    let mut pos = 0;
    build_inorder_string(root, &mut result, &mut pos);
    result
}

pub fn test_insert_and_inorder() {
    let mut root: Option<Box<Node>> = None;
    
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    
    let result = capture_inorder(root.as_ref());
    assert!(result == "20 30 40 50 60 70 80 ", "test_insert_and_inorder failed");
    println!("test_insert_and_inorder passed");
}

pub fn test_min_value_node() {
    let mut root = None;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    let min = min_value_node(root);
    assert_eq!(min.as_ref().unwrap().key, 5);
    println!("test_min_value_node passed");
}

pub fn test_delete_leaf() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = delete_node(root, 5);
    let result = capture_inorder(root.as_ref());
    assert_eq!(result, "10 15 ");
    println!("test_delete_leaf passed");
}

pub fn test_delete_node_with_one_child() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 2);
    root = delete_node(root, 5);
    let result = capture_inorder(root.as_ref());
    assert_eq!(result, "2 10 ");
    println!("test_delete_node_with_one_child passed");
}

pub fn test_delete_node_with_two_children() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    root = delete_node(root, 50);
    let result = capture_inorder(root.as_ref());
    assert_eq!(result, "20 30 40 60 70 80 ");
    println!("test_delete_node_with_two_children passed");
}

pub fn test_delete_nonexistent_node() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = delete_node(root, 42);
    let result = capture_inorder(root.as_ref());
    assert_eq!(result, "5 10 15 ");
    println!("test_delete_nonexistent_node passed");
}
