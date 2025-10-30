use crate::*;
use std::mem;
use std::fmt::Write;

pub fn newNode(item: i32) -> Option<Box<Node>> {
    Some(Box::new(Node {
        key: item,
        left: None,
        right: None,
    }))
}
pub fn min_value_node(node: Option<Box<Node>>) -> Option<Box<Node>> {
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
    if let Some(node) = root {
        inorder(node.left.as_ref());
        print!("{} ", node.key);
        inorder(node.right.as_ref());
    }
}
pub fn insert(node: Option<Box<Node>>, key: i32) -> Option<Box<Node>> {
    match node {
        None => newNode(key),
        Some(mut node) => {
            if key < node.key {
                node.left = insert(node.left, key);
            } else {
                node.right = insert(node.right, key);
            }
            Some(node)
        }
    }
}

pub fn delete_node(root: Option<Box<Node>>, key: i32) -> Option<Box<Node>> {
    let mut root = match root {
        Some(node) => node,
        None => return None,
    };

    if key < root.key {
        root.left = delete_node(root.left, key);
    } else if key > root.key {
        root.right = delete_node(root.right, key);
    } else {
        if root.left.is_none() {
            return root.right;
        } else if root.right.is_none() {
            return root.left;
        }

        let min_right = min_value_node(root.right.clone()).unwrap();
        root.key = min_right.key;
        root.right = delete_node(root.right, min_right.key);
    }

    Some(root)
}
