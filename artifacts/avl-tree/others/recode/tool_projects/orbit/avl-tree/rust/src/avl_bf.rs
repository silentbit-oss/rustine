/*
 * AVL Tree Implementation in Rust
 * Translated from C implementation by xieqing
 */

use std::cmp::Ordering;
use std::fmt;

// Enumerations

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AvlBf {
    LeftHeavy = -1,
    Balanced = 0,
    RightHeavy = 1,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum AvlTraversal {
    PreOrder,
    InOrder,
    PostOrder,
}

// Core Data Structures

pub struct AvlNode<T> {
    left: Option<Box<AvlNode<T>>>,
    right: Option<Box<AvlNode<T>>>,
    bf: i8,
    data: T,
}

pub struct AvlTree<T> {
    pub root: Option<Box<AvlNode<T>>>,
}

// Public API Functions

pub fn avl_create<T: Ord>() -> AvlTree<T> {
    AvlTree {
        root: None,
    }
}

pub fn avl_destroy<T>(tree: AvlTree<T>) {
    // Consume the tree - destruction is automatic in Rust
    // The recursive destroy helper is called implicitly via Drop
    destroy(tree.root);
}

pub fn avl_find<'a, T: Ord>(tree: &'a AvlTree<T>, data: &T) -> Option<&'a T> {
    let mut current = tree.root.as_ref()?;

    loop {
        match data.cmp(&current.data) {
            Ordering::Equal => return Some(&current.data),
            Ordering::Less => {
                current = current.left.as_ref()?;
            }
            Ordering::Greater => {
                current = current.right.as_ref()?;
            }
        }
    }
}

pub fn avl_successor<'a, T: Ord>(tree: &'a AvlTree<T>, data: &T) -> Option<&'a T> {
    // Without parent pointers, we need to search from the root
    // Strategy: track the last node where we went left (potential successor)

    let mut current = tree.root.as_ref()?;
    let mut successor: Option<&T> = None;

    // First, find the node with the given data
    loop {
        match data.cmp(&current.data) {
            Ordering::Equal => {
                // Found the node - now find its successor
                if let Some(ref right) = current.right {
                    // If right subtree exists, successor is leftmost node in right subtree
                    let mut leftmost = right.as_ref();
                    while let Some(ref left) = leftmost.left {
                        leftmost = left.as_ref();
                    }
                    return Some(&leftmost.data);
                } else {
                    // No right subtree - successor is the last ancestor where we went left
                    return successor;
                }
            }
            Ordering::Less => {
                // Going left - current node could be the successor
                successor = Some(&current.data);
                current = current.left.as_ref()?;
            }
            Ordering::Greater => {
                // Going right - current node is not a successor candidate
                current = current.right.as_ref()?;
            }
        }
    }
}

// Accessor for the minimal node (AVL_MIN feature)
#[cfg(feature = "min")]
pub fn avl_minimal<'a, T>(tree: &'a AvlTree<T>) -> Option<&'a T> {
    // Find the leftmost node (minimum) by traversing left
    let mut current = tree.root.as_ref()?;
    while let Some(ref left) = current.left {
        current = left;
    }
    Some(&current.data)
}

pub fn avl_apply<T, F>(tree: &AvlTree<T>, mut func: F, order: AvlTraversal) -> Result<(), ()>
where
    F: FnMut(&T) -> Result<(), ()>,
{
    fn apply_recursive<T, F>(
        node: Option<&AvlNode<T>>,
        func: &mut F,
        order: AvlTraversal,
    ) -> Result<(), ()>
    where
        F: FnMut(&T) -> Result<(), ()>,
    {
        if let Some(n) = node {
            // PreOrder: process node before children
            if order == AvlTraversal::PreOrder {
                func(&n.data)?;
            }

            // Process left subtree
            apply_recursive(n.left.as_deref(), func, order)?;

            // InOrder: process node between children
            if order == AvlTraversal::InOrder {
                func(&n.data)?;
            }

            // Process right subtree
            apply_recursive(n.right.as_deref(), func, order)?;

            // PostOrder: process node after children
            if order == AvlTraversal::PostOrder {
                func(&n.data)?;
            }
        }

        Ok(())
    }

    apply_recursive(tree.root.as_deref(), &mut func, order)
}

pub fn avl_print<T: fmt::Display>(tree: &AvlTree<T>) {
    println!("\n--");
    print(tree.root.as_deref(), 0, "T");
    println!("\nheight = {}", check_height(tree.root.as_deref()));
}

pub fn avl_check_order<T: Ord>(tree: &AvlTree<T>, min: &T, max: &T) -> bool {
    check_order(tree.root.as_deref(), min, max)
}

pub fn avl_check_height<T>(tree: &AvlTree<T>) -> bool {
    let height = check_height(tree.root.as_deref());
    // Returns true if valid (height >= 0), false if invalid (height < 0)
    height >= 0
}

pub fn avl_insert<'a, T: Ord + Clone>(tree: &'a mut AvlTree<T>, data: T) -> Option<&'a T> {
    // Direction enum to track the path taken during descent
    #[derive(Debug, Clone, Copy, PartialEq)]
    enum Direction {
        Left,
        Right,
    }

    // Helper function to insert recursively and track the path
    fn insert_recursive<T: Ord>(
        node: &mut Option<Box<AvlNode<T>>>,
        data: T,
        path: &mut Vec<Direction>,
    ) -> Result<(), ()> {
        match node {
            None => {
                // Found the insertion point - create a new node
                let new_node = Box::new(AvlNode {
                    left: None,
                    right: None,
                    bf: 0,
                    data,
                });
                *node = Some(new_node);
                Ok(())
            }
            Some(ref mut current) => {
                // Compare data to decide which direction to go
                match data.cmp(&current.data) {
                    Ordering::Less => {
                        // Go left
                        path.push(Direction::Left);
                        insert_recursive(&mut current.left, data, path)
                    }
                    Ordering::Greater => {
                        // Go right
                        path.push(Direction::Right);
                        insert_recursive(&mut current.right, data, path)
                    }
                    Ordering::Equal => {
                        // Duplicate key - without AVL_DUP feature, do not insert
                        // Return error to indicate the key already exists
                        Err(())
                    }
                }
            }
        }
    }

    // Helper function to rebalance along the path
    fn rebalance_after_insert<T>(
        node: &mut Option<Box<AvlNode<T>>>,
        path: &[Direction],
        depth: usize,
    ) -> bool {
        if depth >= path.len() {
            // Reached the inserted node
            return true; // Height increased
        }

        if let Some(ref mut current) = node {
            let direction = path[depth];
            let height_increased = match direction {
                Direction::Left => rebalance_after_insert(&mut current.left, path, depth + 1),
                Direction::Right => rebalance_after_insert(&mut current.right, path, depth + 1),
            };

            if !height_increased {
                return false; // Height didn't increase, no need to continue
            }

            // Update balance factor based on which subtree grew
            if direction == Direction::Left {
                // Left subtree grew
                if current.bf == 1 {
                    // Was right-heavy, now balanced
                    current.bf = 0;
                    return false; // Height unchanged
                } else if current.bf == 0 {
                    // Was balanced, now left-heavy
                    current.bf = -1;
                    return true; // Height increased
                } else if current.bf == -1 {
                    // Was left-heavy, now needs rebalancing
                    let fixed = node.take().expect("node must exist");
                    *node = Some(fix_insert_leftimbalance(fixed));
                    return false; // Height unchanged after rotation
                }
            } else {
                // Right subtree grew
                if current.bf == -1 {
                    // Was left-heavy, now balanced
                    current.bf = 0;
                    return false; // Height unchanged
                } else if current.bf == 0 {
                    // Was balanced, now right-heavy
                    current.bf = 1;
                    return true; // Height increased
                } else if current.bf == 1 {
                    // Was right-heavy, now needs rebalancing
                    let fixed = node.take().expect("node must exist");
                    *node = Some(fix_insert_rightimbalance(fixed));
                    return false; // Height unchanged after rotation
                }
            }
        }

        false
    }

    // Clone the data to use for searching after insertion
    let search_data = data.clone();

    // Handle empty tree case
    if tree.root.is_none() {
        let new_node = Box::new(AvlNode {
            left: None,
            right: None,
            bf: 0,
            data,
        });
        tree.root = Some(new_node);
        // Return reference to the root's data
        return tree.root.as_ref().map(|node| &node.data);
    }

    // Track the path for backtracking
    let mut path = Vec::new();

    // Insert the node
    match insert_recursive(&mut tree.root, data, &mut path) {
        Ok(()) => {
            // Rebalance the tree along the insertion path
            rebalance_after_insert(&mut tree.root, &path, 0);
        }
        Err(()) => {
            // Duplicate key - without AVL_DUP, this is expected behavior
            // Fall through to find and return existing node
        }
    }

    // Find and return reference to the inserted (or existing) data
    avl_find(tree, &search_data)
}

pub fn avl_delete<T: Ord>(tree: &mut AvlTree<T>, data: &T, keep: bool) -> Option<T> {
    // Direction enum to track the path taken during descent
    #[derive(Debug, Clone, Copy, PartialEq)]
    enum Direction {
        Left,
        Right,
    }

    // Helper function to delete and rebalance recursively
    fn delete_recursive<T: Ord>(
        node: &mut Option<Box<AvlNode<T>>>,
        data: &T,
        path: &mut Vec<Direction>,
    ) -> (Option<T>, bool) {
        match node {
            None => {
                // Node not found
                (None, false)
            }
            Some(ref mut current) => {
                match data.cmp(&current.data) {
                    Ordering::Equal => {
                        // Found the node to delete
                        let deleted_data = if current.left.is_none() || current.right.is_none() {
                            // Case 1: Node has at most one child (including leaf)
                            let mut target = node.take().unwrap();

                            // Choose the non-null child (or None if both are None)
                            let child = if target.left.is_some() {
                                target.left.take()
                            } else {
                                target.right.take()
                            };

                            *node = child;

                            // Return the data and indicate height decreased
                            (Some(target.data), true)
                        } else {
                            // Case 2: Node has two children
                            // Strategy: Swap data with successor, then delete successor
                            // The successor is the leftmost node in the right subtree

                            // Find and delete the successor recursively
                            fn delete_successor<T>(
                                node: &mut Option<Box<AvlNode<T>>>,
                                path: &mut Vec<Direction>,
                            ) -> (T, bool) {
                                if let Some(ref mut n) = node {
                                    if n.left.is_none() {
                                        // This is the successor (leftmost node)
                                        let successor = node.take().unwrap();
                                        let data = successor.data;
                                        let child = successor.right;
                                        *node = child;
                                        (data, true) // Height decreased
                                    } else {
                                        // Go left to find the leftmost node
                                        path.push(Direction::Left);
                                        delete_successor(&mut n.left, path)
                                    }
                                } else {
                                    panic!("delete_successor called on None");
                                }
                            }

                            // Start by going right to the successor's subtree
                            path.push(Direction::Right);

                            // Delete the successor and get its data
                            let (successor_data, _) = delete_successor(&mut current.right, path);

                            // Swap the data
                            let old_data = std::mem::replace(&mut current.data, successor_data);

                            (Some(old_data), true)
                        };

                        deleted_data
                    }
                    Ordering::Less => {
                        // Go left
                        path.push(Direction::Left);
                        delete_recursive(&mut current.left, data, path)
                    }
                    Ordering::Greater => {
                        // Go right
                        path.push(Direction::Right);
                        delete_recursive(&mut current.right, data, path)
                    }
                }
            }
        }
    }

    // Helper function to rebalance after deletion
    fn rebalance_after_delete<T>(
        node: &mut Option<Box<AvlNode<T>>>,
        path: &[Direction],
        depth: usize,
    ) -> bool {
        if depth >= path.len() {
            // Reached the deleted node
            return true; // Height decreased
        }

        if let Some(ref mut current) = node {
            let direction = path[depth];
            let height_decreased = rebalance_after_delete(
                match direction {
                    Direction::Left => &mut current.left,
                    Direction::Right => &mut current.right,
                },
                path,
                depth + 1,
            );

            if !height_decreased {
                return false; // Height didn't decrease, no need to continue
            }

            // Update balance factor based on which subtree shrank
            if direction == Direction::Left {
                // Left subtree shrank
                if current.bf == -1 {
                    // Was left-heavy, now balanced
                    current.bf = 0;
                    return true; // Height decreased
                } else if current.bf == 0 {
                    // Was balanced, now right-heavy
                    current.bf = 1;
                    return false; // Height unchanged
                } else if current.bf == 1 {
                    // Was right-heavy, now needs rebalancing
                    let fixed = node.take().expect("node must exist");
                    let new_root = fix_delete_rightimbalance(fixed);
                    let root_bf = new_root.bf;
                    *node = Some(new_root);

                    // If balance factor is -1 after rotation, height unchanged
                    return root_bf != -1;
                }
            } else {
                // Right subtree shrank
                if current.bf == 1 {
                    // Was right-heavy, now balanced
                    current.bf = 0;
                    return true; // Height decreased
                } else if current.bf == 0 {
                    // Was balanced, now left-heavy
                    current.bf = -1;
                    return false; // Height unchanged
                } else if current.bf == -1 {
                    // Was left-heavy, now needs rebalancing
                    let fixed = node.take().expect("node must exist");
                    let new_root = fix_delete_leftimbalance(fixed);
                    let root_bf = new_root.bf;
                    *node = Some(new_root);

                    // If balance factor is 1 after rotation, height unchanged
                    return root_bf != 1;
                }
            }
        }

        false
    }

    // Handle empty tree case
    if tree.root.is_none() {
        return None;
    }

    // Track the path for backtracking
    let mut path = Vec::new();

    // Delete the node and get the data
    let (deleted_data, height_decreased) = delete_recursive(&mut tree.root, data, &mut path);

    if deleted_data.is_none() {
        // Node not found
        return None;
    }

    // Rebalance the tree along the deletion path if height decreased
    if height_decreased {
        rebalance_after_delete(&mut tree.root, &path, 0);
    }

    // Return the data based on keep flag
    if keep {
        deleted_data
    } else {
        // Drop the data and return None
        None
    }
}

// Private Helper Functions

fn rotate_left<T>(x: Box<AvlNode<T>>) -> Box<AvlNode<T>> {
    // In C: y = x->right
    // We need to take ownership of x and return y
    let mut x = x;

    // Extract y (right child of x) - must exist for rotation
    let mut y = x.right.take().expect("rotate_left: right child must exist");

    // x->right = y->left (move y's left subtree to x's right)
    x.right = y.left.take();

    // y->left = x (make x the left child of y)
    y.left = Some(x);

    // Return y as the new root
    y
}

fn rotate_right<T>(x: Box<AvlNode<T>>) -> Box<AvlNode<T>> {
    // In C: y = x->left
    // We need to take ownership of x and return y
    let mut x = x;

    // Extract y (left child of x) - must exist for rotation
    let mut y = x.left.take().expect("rotate_right: left child must exist");

    // x->left = y->right (move y's right subtree to x's left)
    x.left = y.right.take();

    // y->right = x (make x the right child of y)
    y.right = Some(x);

    // Return y as the new root
    y
}

fn fix_insert_leftimbalance<T>(p: Box<AvlNode<T>>) -> Box<AvlNode<T>> {
    let mut p = p;

    // Get balance factor of left child
    let left_bf = p.left.as_ref().map(|n| n.bf).unwrap_or(0);

    if left_bf == p.bf { // -1, -1 case
        // Single right rotation
        let mut new_root = rotate_right(p);
        new_root.bf = 0;
        if let Some(ref mut right) = new_root.right {
            right.bf = 0;
        }
        new_root
    } else { // 1, -1 case (left-right case)
        // Double rotation: left then right
        // Save the balance factor of left->right before rotation
        let oldbf = p.left.as_ref()
            .and_then(|n| n.right.as_ref())
            .map(|n| n.bf)
            .unwrap_or(0);

        // Rotate left child left
        let left = p.left.take().expect("left child must exist");
        let rotated_left = rotate_left(left);
        p.left = Some(rotated_left);

        // Rotate p right
        let mut new_root = rotate_right(p);
        new_root.bf = 0;

        // Update balance factors based on oldbf
        if oldbf == -1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 1;
            }
        } else if oldbf == 1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = -1;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        } else if oldbf == 0 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        }

        new_root
    }
}

fn fix_insert_rightimbalance<T>(p: Box<AvlNode<T>>) -> Box<AvlNode<T>> {
    let mut p = p;

    // Get balance factor of right child
    let right_bf = p.right.as_ref().map(|n| n.bf).unwrap_or(0);

    if right_bf == p.bf { // 1, 1 case
        // Single left rotation
        let mut new_root = rotate_left(p);
        new_root.bf = 0;
        if let Some(ref mut left) = new_root.left {
            left.bf = 0;
        }
        new_root
    } else { // -1, 1 case (right-left case)
        // Double rotation: right then left
        // Save the balance factor of right->left before rotation
        let oldbf = p.right.as_ref()
            .and_then(|n| n.left.as_ref())
            .map(|n| n.bf)
            .unwrap_or(0);

        // Rotate right child right
        let right = p.right.take().expect("right child must exist");
        let rotated_right = rotate_right(right);
        p.right = Some(rotated_right);

        // Rotate p left
        let mut new_root = rotate_left(p);
        new_root.bf = 0;

        // Update balance factors based on oldbf
        if oldbf == -1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 1;
            }
        } else if oldbf == 1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = -1;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        } else if oldbf == 0 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        }

        new_root
    }
}

fn fix_delete_leftimbalance<T>(p: Box<AvlNode<T>>) -> Box<AvlNode<T>> {
    let mut p = p;

    // Get balance factor of left child
    let left_bf = p.left.as_ref().map(|n| n.bf).unwrap_or(0);

    if left_bf == -1 {
        // Single right rotation
        let mut new_root = rotate_right(p);
        new_root.bf = 0;
        if let Some(ref mut right) = new_root.right {
            right.bf = 0;
        }
        new_root
    } else if left_bf == 0 {
        // Single right rotation
        let mut new_root = rotate_right(p);
        new_root.bf = 1;
        if let Some(ref mut right) = new_root.right {
            right.bf = -1;
        }
        new_root
    } else if left_bf == 1 {
        // Double rotation: left then right
        // Save the balance factor of left->right before rotation
        let oldbf = p.left.as_ref()
            .and_then(|n| n.right.as_ref())
            .map(|n| n.bf)
            .unwrap_or(0);

        // Rotate left child left
        let left = p.left.take().expect("left child must exist");
        let rotated_left = rotate_left(left);
        p.left = Some(rotated_left);

        // Rotate p right
        let mut new_root = rotate_right(p);
        new_root.bf = 0;

        // Update balance factors based on oldbf
        if oldbf == -1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 1;
            }
        } else if oldbf == 1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = -1;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        } else if oldbf == 0 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        }

        new_root
    } else {
        // Should not reach here
        p
    }
}

fn fix_delete_rightimbalance<T>(p: Box<AvlNode<T>>) -> Box<AvlNode<T>> {
    let mut p = p;

    // Get balance factor of right child
    let right_bf = p.right.as_ref().map(|n| n.bf).unwrap_or(0);

    if right_bf == 1 {
        // Single left rotation
        let mut new_root = rotate_left(p);
        new_root.bf = 0;
        if let Some(ref mut left) = new_root.left {
            left.bf = 0;
        }
        new_root
    } else if right_bf == 0 {
        // Single left rotation
        let mut new_root = rotate_left(p);
        new_root.bf = -1;
        if let Some(ref mut left) = new_root.left {
            left.bf = 1;
        }
        new_root
    } else if right_bf == -1 {
        // Double rotation: right then left
        // Save the balance factor of right->left before rotation
        let oldbf = p.right.as_ref()
            .and_then(|n| n.left.as_ref())
            .map(|n| n.bf)
            .unwrap_or(0);

        // Rotate right child right
        let right = p.right.take().expect("right child must exist");
        let rotated_right = rotate_right(right);
        p.right = Some(rotated_right);

        // Rotate p left
        let mut new_root = rotate_left(p);
        new_root.bf = 0;

        // Update balance factors based on oldbf
        if oldbf == -1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 1;
            }
        } else if oldbf == 1 {
            if let Some(ref mut left) = new_root.left {
                left.bf = -1;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        } else if oldbf == 0 {
            if let Some(ref mut left) = new_root.left {
                left.bf = 0;
            }
            if let Some(ref mut right) = new_root.right {
                right.bf = 0;
            }
        }

        new_root
    } else {
        // Should not reach here
        p
    }
}

fn check_order<T: Ord>(node: Option<&AvlNode<T>>, min: &T, max: &T) -> bool {
    if let Some(n) = node {
        // Check if current node's data is within bounds
        // Without AVL_DUP: node data must be strictly between min and max
        if n.data <= *min || n.data >= *max {
            return false;
        }

        // Recursively check left subtree (all values must be between min and node.data)
        // and right subtree (all values must be between node.data and max)
        check_order(n.left.as_deref(), min, &n.data)
            && check_order(n.right.as_deref(), &n.data, max)
    } else {
        // Empty node is valid
        true
    }
}

fn check_height<T>(node: Option<&AvlNode<T>>) -> i32 {
    if let Some(n) = node {
        // Recursively check left subtree height
        let lh = check_height(n.left.as_deref());
        if lh < 0 {
            return lh; // Propagate error
        }

        // Recursively check right subtree height
        let rh = check_height(n.right.as_deref());
        if rh < 0 {
            return rh; // Propagate error
        }

        // Check balance factor
        let cmp = rh - lh;
        if cmp < -1 || cmp > 1 || cmp != n.bf as i32 {
            // Invalid balance factor - tree is not properly balanced
            return -1;
        }

        // Return height of this subtree
        1 + if lh > rh { lh } else { rh }
    } else {
        // Empty node has height 0
        0
    }
}

fn print<T: fmt::Display>(node: Option<&AvlNode<T>>, depth: usize, label: &str) {
    if let Some(n) = node {
        // Print right subtree first (will appear at top of output)
        print(n.right.as_deref(), depth + 1, "R");

        // Print current node with indentation
        print!("{:width$}", "", width = 8 * depth);
        if !label.is_empty() {
            print!("{}: ", label);
        }
        print!("{}", n.data);
        println!(" ({}{})", if n.bf >= 0 { "+" } else { "" }, n.bf);

        // Print left subtree last (will appear at bottom of output)
        print(n.left.as_deref(), depth + 1, "L");
    }
}

fn destroy<T>(node: Option<Box<AvlNode<T>>>) {
    if let Some(mut boxed_node) = node {
        // Recursively destroy left and right subtrees
        destroy(boxed_node.left.take());
        destroy(boxed_node.right.take());
        // boxed_node is dropped here automatically, freeing the node and its data
    }
}
