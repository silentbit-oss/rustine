use libc::FILE;
use libc::STDOUT_FILENO;
use libc::close;
use libc::dup2;
use libc::dup;
use crate::*;
use std::io::Read;
use std::io::Seek;
use std::io::SeekFrom;
use std::io::Write;
use std::assert;
use std::assert_eq;
use std::io;
use std::mem;
use std::fs::File;
use tempfile::tempfile;
use std::os::fd::AsRawFd;
pub fn newNode(item: i32) -> Option<Box<Node>> {
    Some(Box::new(Node {
        key: item,
        left: None,
        right: None,
    }))
}
pub fn minValueNode(node: Option<Box<Node>>) -> Option<Box<Node>> {
    let mut current = node;
    while let Some(ref mut current_node) = current {
        if current_node.left.is_some() {
            current = current_node.left.take();
        } else {
            break;
        }
    }
    current
}
pub fn inorder(root: Option<&Box<Node>>) {
    if let Some(root) = root {
        inorder(root.left.as_ref());
        println!("{} ", root.key);
        inorder(root.right.as_ref());
    }
}
pub fn capture_inorder(root: Option<&Box<Node>>) -> Option<String> {
    
    // Create a temporary file (equivalent to tmpfile() in C)
    let mut tmp = match tempfile::tempfile() {
        Ok(file) => file,
        Err(e) => {
            eprintln!("tmpfile: {}", e); // equivalent to perror("tmpfile")
            std::process::exit(1); // equivalent to exit(1)
        }
    };

    // Flush stdout before redirection
    std::io::stdout().flush().unwrap(); // equivalent to fflush(stdout)

    // Save the original stdout file descriptor
    let stdout_fd = unsafe { dup(STDOUT_FILENO) };
    if stdout_fd == -1 {
        eprintln!("dup: {}", std::io::Error::last_os_error());
        std::process::exit(1);
    }

    // Redirect stdout to our temporary file
    let tmp_fd = tmp.as_raw_fd();
    if unsafe { dup2(tmp_fd, STDOUT_FILENO) } == -1 {
        eprintln!("dup2: {}", std::io::Error::last_os_error());
        std::process::exit(1);
    }

    // Perform the inorder traversal
    inorder(root);

    // Flush stdout after writing
    std::io::stdout().flush().unwrap(); // equivalent to fflush(stdout)

    // Restore original stdout
    if unsafe { dup2(stdout_fd, STDOUT_FILENO) } == -1 {
        eprintln!("dup2: {}", std::io::Error::last_os_error());
        std::process::exit(1);
    }
    unsafe { close(stdout_fd) };

    // Get the length of the file
    let len = tmp.seek(std::io::SeekFrom::End(0)).unwrap() as usize;
    tmp.seek(std::io::SeekFrom::Start(0)).unwrap(); // equivalent to rewind(tmp)

    // Read the file contents into a String
    let mut result = String::with_capacity(len + 1);
    tmp.read_to_string(&mut result).unwrap(); // equivalent to fread

    Some(result)
}
pub fn insert(node: Option<Box<Node>>, key: i32) -> Option<Box<Node>> {
    match node {
        None => newNode(key), // Base case: create new node if current is None
        Some(mut node_ptr) => {
            if key < node_ptr.key {
                // Recursively insert into left subtree
                node_ptr.left = insert(node_ptr.left, key);
            } else {
                // Recursively insert into right subtree
                node_ptr.right = insert(node_ptr.right, key);
            }
            Some(node_ptr) // Return the modified node
        }
    }
}

pub fn deleteNode(root: Option<Box<Node>>, key: i32) -> Option<Box<Node>> {
    let mut root = match root {
        None => return None,
        Some(node) => node,
    };

    if key < root.key {
        root.left = deleteNode(root.left, key);
    } else if key > root.key {
        root.right = deleteNode(root.right, key);
    } else {
        if root.left.is_none() {
            return root.right;
        } else if root.right.is_none() {
            return root.left;
        }

        let min_right = minValueNode(root.right.clone()).unwrap();
        root.key = min_right.key;
        root.right = deleteNode(root.right, min_right.key);
    }

    Some(root)
}

pub fn test_insert_and_inorder() {
    let mut root = None;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    let result = capture_inorder(root.as_ref());
    assert!(result.as_ref().map_or(false, |s| s == "20 30 40 50 60 70 80 "));
    println!("test_insert_and_inorder passed");
}

pub fn test_min_value_node() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    let min = minValueNode(root);
    assert!(min.as_ref().unwrap().key == 5);
    println!("test_min_value_node passed");
}
pub fn test_delete_leaf() {
    let mut root_idx: Option<Box<Node>> = None;
    root_idx = insert(root_idx, 10);
    root_idx = insert(root_idx, 5);
    root_idx = insert(root_idx, 15);
    root_idx = deleteNode(root_idx, 5);
    
    let result = capture_inorder(root_idx.as_ref());
    assert_eq!(result.unwrap(), "10 15 ");
    println!("test_delete_leaf passed");
}
pub fn test_delete_node_with_one_child() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 2);
    root = deleteNode(root, 5);
    let result = capture_inorder(root.as_ref());
    assert_eq!(result.unwrap(), "2 10 ");
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
    root = deleteNode(root, 50);
    
    let result = capture_inorder(root.as_ref());
    assert_eq!(result.unwrap(), "20 30 40 60 70 80 ");
    println!("test_delete_node_with_two_children passed");
}

pub fn test_delete_nonexistent_node() {
    let mut root: Option<Box<Node>> = None;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = deleteNode(root, 42);
    
    let result = capture_inorder(root.as_ref());
    assert_eq!(result.unwrap(), "5 10 15 ");
    println!("test_delete_nonexistent_node passed");
}
