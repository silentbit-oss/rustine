use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use std::rc::Rc;
use std::cell::RefCell;
use std::any::Any;
use rand::Rng;
use std::fmt::Write;

pub fn destroy(avlt: &mut AvlTree, n: Option<Box<AvlNode>>) {
    if let Some(mut node) = n {
        // Recursively destroy left and right subtrees
        destroy(avlt, node.left.take());
        destroy(avlt, node.right.take());

        (avlt.destroy)(
            node.data.map(|data| {
                data.downcast::<Mydata>().expect("Failed to downcast to Mydata")
            })
        );
    }
}
pub fn avl_create(
    compare_func: fn(Option<&Mydata>, Option<&Mydata>) -> i32,
    destroy_func: fn(Option<Box<Mydata>>),
) -> Option<Box<AvlTree>> 
{
    // Create root node with separate nil nodes
    let root_node = Box::new(AvlNode {
        left: None,
        right: None,
        parent: None,
        bf: 0,
        data: None,
    });

    // Create separate nil node for tree's nil field
    let tree_nil = Box::new(AvlNode {
        left: None,
        right: None,
        parent: None,
        bf: 0,
        data: None,
    });

    // Allocate memory for AVL tree
    let avlt = Box::new(AvlTree {
        compare: compare_func,
        print: print_func,
        destroy: destroy_func,
        root: Some(root_node),
        nil: Some(tree_nil),
        min: None,
    });

    Some(avlt)
}
pub fn avl_destroy(avlt: Box<AvlTree>) {
    let mut avlt_ref = avlt;
    let root_left = {
        if let Some(ref mut root) = avlt_ref.root {
            root.left.take()
        } else {
            None
        }
    };
    
    destroy(&mut avlt_ref, root_left);
}
pub fn avl_find<'a>(avlt: &'a AvlTree, data: Option<&Mydata>) -> Option<&'a AvlNode> {
    // Start from the root node
    let mut p = avlt.root.as_ref().unwrap().left.as_ref()?;
    // While we haven't reached the nil node
    loop {
        // Compare the data using the tree's comparison function
        let cmp = (avlt.compare)(
            data,
            p.data.as_ref().map(|data| {
                data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
            }),
        );

        if cmp == 0 {
            // Found the node with matching data
            return Some(p);
        }

        // Move to left or right child based on comparison
        let next = if cmp < 0 {
            p.left.as_ref()
        } else {
            p.right.as_ref()
        };

        match next {
            Some(node) => p = node,
            None => break,
        }
    }

    // Node not found
    None
}
pub fn avl_successor<'a>(avlt: &'a AvlTree, node: &'a AvlNode) -> Option<&'a AvlNode> {
    if let Some(right_node) = node.right.as_deref() {
        let mut leftmost = right_node;
        while let Some(left_node) = leftmost.left.as_deref() {
            leftmost = left_node;
        }
        return Some(leftmost);
    } else {
        let mut current = node;
        let mut parent_opt = node.parent.as_deref();

        while let Some(p_node) = parent_opt {
            if let Some(p_right) = p_node.right.as_deref() {
                if std::ptr::eq(current, p_right) {
                    current = p_node;
                    parent_opt = p_node.parent.as_deref();
                    continue;
                }
            }

            return Some(p_node);
        }

        None
    }
}
pub fn check_order(
    avlt: &AvlTree,
    n: Option<&Box<AvlNode>>,
    min: Option<&Box<dyn std::any::Any>>,
    max: Option<&Box<dyn std::any::Any>>,
) -> bool {
    // Check if node is nil (equivalent to n == &avlt->nil in C)
    if n.is_none() || std::ptr::eq(n.unwrap().as_ref(), avlt.nil.as_ref().unwrap().as_ref()) {
        return true;
    }

    let n = n.unwrap();
    // Check if data is out of bounds (equivalent to avlt->compare(n->data, min) < 0 || ... > 0)
    if (avlt.compare)(
        n.data.as_ref().map(|data| {
            data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
        }),
        min.as_ref().map(|data| {
            data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
        }),
        ) < 0
        ||
        (avlt.compare)(
            n.data.as_ref().map(|data| {
                data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
            }),
            max.as_ref().map(|data| {
                data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
            }),
        ) > 0 
    {
        return false;
    }

    // Recursively check left and right subtrees
    check_order(avlt, n.left.as_ref(), min, n.data.as_ref())
        && check_order(avlt, n.right.as_ref(), n.data.as_ref(), max)
}
pub fn avl_check_order(
    avlt: &AvlTree,
    min: Option<&Box<dyn std::any::Any>>,
    max: Option<&Box<dyn std::any::Any>>,
) -> bool {
    // Get the left child of the root node (avlt->root.left in C)
    let root_left = match &avlt.root {
        Some(root) => root.left.as_ref(),
        None => None,
    };
    
    // Call check_order with the appropriate parameters
    check_order(avlt, root_left, min, max)
}
pub fn rotate_left(avlt: &mut AvlTree, x: &mut AvlNode) -> Option<Box<AvlNode>> {
    // Get y as x's right child
    let mut y = x.right.take()?;
    
    // Convert x to raw pointer early to avoid borrow issues
    let x_ptr = x as *mut AvlNode;
    
    // Perform the rotation
    x.right = y.left.take();
    if let Some(ref mut right) = x.right {
        right.parent = Some(unsafe { Box::from_raw(x_ptr) });
    }
    
    // Instead of cloning, just take the parent directly
    y.parent = x.parent.take();
    
    let y_ptr = unsafe { Box::into_raw(Box::new(*y)) };
    let y_ref = unsafe { &mut *y_ptr };
    
    match y_ref.parent.as_mut() {
        Some(parent) => {
            let x_ptr = x as *const AvlNode;
            if parent.left.as_ref().map_or(false, |left| std::ptr::eq(left.as_ref(), x_ptr)) {
                parent.left = Some(unsafe { Box::from_raw(y_ptr) });
            } else {
                parent.right = Some(unsafe { Box::from_raw(y_ptr) });
            }
        }
        None => {
            // x was root, now y becomes root
            avlt.root = Some(unsafe { Box::from_raw(y_ptr) });
            return None;
        }
    }
    
    let x_box = unsafe { Box::from_raw(x_ptr) };
    y_ref.left = Some(x_box);
    x.parent = Some(unsafe { Box::from_raw(y_ptr) });
    
    Some(unsafe { Box::from_raw(y_ptr) })
}
pub fn rotate_right(avlt: &mut AvlTree, x: &mut AvlNode) -> Option<Box<AvlNode>> {
    // Get y as x's left child
    let mut y = x.left.take()?;
    
    // Perform the rotation
    x.left = y.right.take();
    if let Some(ref mut left) = x.left {
        left.parent = Some(Box::new(AvlNode {
            left: None,
            right: None,
            parent: None,
            bf: x.bf,
            data: None,
        }));
    }
    
    let x_parent = x.parent.take();
    y.parent = x_parent;  // Direct assignment instead of clone
    
    let x_ptr = x as *const AvlNode;
    let mut target = None;
    
    if let Some(ref parent) = y.parent {
        if parent.left.as_ref().map_or(false, |left| {
            let left_ptr: *const AvlNode = left.as_ref();
            left_ptr == x_ptr
        }) {
            target = Some(0);
        } else {
            target = Some(1);
        }
    } else {
        target = Some(2);
    }
    
    // Create new node for y's right child (which will be x)
    let mut new_x = AvlNode {
        left: x.left.take(),
        right: x.right.take(),
        parent: Some(Box::new(AvlNode {
            left: y.left.take(),
            right: None,
            parent: y.parent.take(),
            bf: y.bf,
            data: y.data.take(),
        })),
        bf: x.bf,
        data: x.data.take(),
    };
    
    let new_x_parent = new_x.parent.as_mut().unwrap();
    let new_x_parent_data = new_x_parent.data.take();
    
    // Update parent pointers based on target
    match target {
        Some(0) => {
            if let Some(ref mut parent) = y.parent {
                let y_box = Box::new(AvlNode {
                    left: new_x_parent.left.take(),
                    right: Some(Box::new(new_x)),
                    parent: None, // Use None instead of moved x_parent
                    bf: y.bf,
                    data: new_x_parent_data,
                });
                parent.left = Some(y_box);
            }
        }
        Some(1) => {
            if let Some(ref mut parent) = y.parent {
                let y_box = Box::new(AvlNode {
                    left: new_x_parent.left.take(),
                    right: Some(Box::new(new_x)),
                    parent: None, // Use None instead of moved x_parent
                    bf: y.bf,
                    data: new_x_parent_data,
                });
                parent.right = Some(y_box);
            }
        }
        Some(2) => {
            let y_box = Box::new(AvlNode {
                left: new_x_parent.left.take(),
                right: Some(Box::new(new_x)),
                parent: None, // Use None instead of moved x_parent
                bf: y.bf,
                data: new_x_parent_data,
            });
            avlt.root = Some(y_box);
        }
        _ => {}
    }
    
    Some(y) // Return the new subtree root
}
pub fn check_height(avlt: &AvlTree, n: Option<&Box<AvlNode>>) -> i32 {
    // Check if node is nil (equivalent to n == &avlt->nil in C)
    if n.is_none() || n.unwrap().as_ref() as *const _ == avlt.nil.as_ref().map(|n| n.as_ref()).unwrap_or(n.unwrap().as_ref()) as *const _ {
        return 0;
    }

    let n = n.unwrap();
    
    // Recursively check left height
    let lh = check_height(avlt, n.left.as_ref());
    if lh < 0 {
        return lh;
    }

    // Recursively check right height
    let rh = check_height(avlt, n.right.as_ref());
    if rh < 0 {
        return rh;
    }

    let cmp = rh - lh;
    if (cmp < -1 || cmp > 1) || cmp != n.bf as i32 {
        return -1;
    }

    1 + if lh > rh { lh } else { rh }
}
pub fn avl_check_height(avlt: &AvlTree) -> i32 {
    let height = match &avlt.root {
        Some(root) => check_height(avlt, root.left.as_ref()),
        None => check_height(avlt, None),
    };
    if height < 0 { 0 } else { 1 }
}

pub fn print(avlt: &AvlTree, n: Option<&Box<AvlNode>>, print_func: &dyn Fn(Option<&dyn std::any::Any>), depth: i32, label: Option<&str>) {
    if let Some(n) = n {
        // Check if current node is not the nil node
        if let Some(nil) = &avlt.nil {
            if !std::ptr::eq(n.as_ref(), nil.as_ref()) {
                // Recursively print right subtree
                print(avlt, n.right.as_ref(), print_func, depth + 1, Some("R"));
                
                // Print indentation
                let mut output = String::new();
                write!(&mut output, "{:width$}", "", width = (8 * depth) as usize).unwrap();
                
                // Print label if present
                if let Some(label) = label {
                    write!(&mut output, "{}: ", label).unwrap();
                }
                
                // Print node data using the provided print_func
                print_func(n.data.as_ref().map(|d| d.as_ref()));
                
                // Print balance factor
                write!(&mut output, " ({}{})", if n.bf >= 0 { "+" } else { "" }, n.bf).unwrap();
                println!("{}", output);
                
                // Recursively print left subtree
                print(avlt, n.left.as_ref(), print_func, depth + 1, Some("L"));
            }
        }
    }
}
pub fn avl_print(avlt: &AvlTree, print_func: &dyn Fn(Option<&dyn std::any::Any>)) {
    println!("\n--");
    print(
        avlt,
        avlt.root.as_ref().and_then(|root| root.left.as_ref()),
        print_func,
        0,
        Some("T"),
    );
    println!(
        "\nheight = {}",
        check_height(
            avlt,
            avlt.root.as_ref().and_then(|root| root.left.as_ref())
        )
    );
}
pub fn fix_insert_rightimbalance<'a>(avlt: &'a mut AvlTree, p: &'a mut AvlNode) -> &'a mut AvlNode {
    if let Some(ref mut right) = p.right {
        if right.bf == p.bf {
            // Case 1: Right child has same balance factor
            let _ = rotate_left(avlt, p);
            p.bf = 0;
            if let Some(ref mut left) = p.left {
                left.bf = 0;
            }
        } else {
            // Case 2: Right child has different balance factor
            let oldbf = if let Some(ref right_left) = right.left {
                right_left.bf
            } else {
                0
            };

            if let Some(ref mut right) = p.right {
                let _ = rotate_right(avlt, right);
            }

            let _ = rotate_left(avlt, p);
            p.bf = 0;

            match oldbf {
                -1 => {
                    if let Some(ref mut left) = p.left {
                        left.bf = 0;
                    }
                    if let Some(ref mut right) = p.right {
                        right.bf = 1;
                    }
                }
                1 => {
                    if let Some(ref mut left) = p.left {
                        left.bf = -1;
                    }
                    if let Some(ref mut right) = p.right {
                        right.bf = 0;
                    }
                }
                0 => {
                    if let Some(ref mut left) = p.left {
                        left.bf = 0;
                    }
                    if let Some(ref mut right) = p.right {
                        right.bf = 0;
                    }
                }
                _ => {}
            }
        }
    }
    p
}
pub fn fix_insert_leftimbalance<'a>(avlt: &'a mut AvlTree, p: &'a mut AvlNode) -> &'a mut AvlNode {
    if let Some(left) = p.left.as_mut() {
        if left.bf == p.bf {
            // Need to rotate right
            let mut rotated = rotate_right(avlt, p);
            if let Some(rotated_node) = rotated.as_mut() {
                rotated_node.bf = 0;
                if let Some(right) = rotated_node.right.as_mut() {
                    right.bf = 0;
                }
            }
        } else {
            // Need to do double rotation
            let oldbf = if let Some(left_right) = left.right.as_ref() {
                left_right.bf
            } else {
                0
            };

            // First rotation (left)
            if let Some(mut left_node) = p.left.take() {
                let rotated_left = rotate_left(avlt, &mut *left_node);
                p.left = rotated_left;
            }

            // Second rotation (right)
            let mut rotated_right = rotate_right(avlt, p);
            if let Some(rotated_node) = rotated_right.as_mut() {
                rotated_node.bf = 0;

                match oldbf {
                    -1 => {
                        if let Some(left) = rotated_node.left.as_mut() {
                            left.bf = 0;
                        }
                        if let Some(right) = rotated_node.right.as_mut() {
                            right.bf = 1;
                        }
                    }
                    1 => {
                        if let Some(left) = rotated_node.left.as_mut() {
                            left.bf = -1;
                        }
                        if let Some(right) = rotated_node.right.as_mut() {
                            right.bf = 0;
                        }
                    }
                    0 => {
                        if let Some(left) = rotated_node.left.as_mut() {
                            left.bf = 0;
                        }
                        if let Some(right) = rotated_node.right.as_mut() {
                            right.bf = 0;
                        }
                    }
                    _ => {}
                }
            }
        }
    }
    p
}
pub fn helper_avl_insert_1(
    current_idx_ref: &mut usize,
    parent_idx_ref: &mut usize,
    avlt: &mut AvlTree,
    current: &mut AvlNode,
    parent: &mut AvlNode,
) {
    let current_idx = *current_idx_ref;
    let parent_idx = *parent_idx_ref;

    // Compare node references directly instead of using Option comparison
    if parent.left.as_ref().map(|n| &**n as *const _) == Some(current as *const _) {
        match parent.bf {
            1 => {
                parent.bf = 0;
                return;
            }
            0 => {
                parent.bf = -1;
            }
            -1 => {
                fix_insert_leftimbalance(avlt, parent);
                return;
            }
            _ => unreachable!("Invalid balance factor"),
        }
    } else {
        match parent.bf {
            -1 => {
                parent.bf = 0;
                return;
            }
            0 => {
                parent.bf = 1;
            }
            1 => {
                fix_insert_rightimbalance(avlt, parent);
                return;
            }
            _ => unreachable!("Invalid balance factor"),
        }
    }

    *current_idx_ref = parent_idx;
    // In the original C code, parent_idx is set to current->parent_idx
    // Since we don't have parent_idx in our Rust struct, we'll need to handle this differently
    // For now, we'll just set it to 0 as a placeholder
    *parent_idx_ref = 0;
}
pub fn avl_insert(avlt: &mut AvlTree, data: Box<dyn Any>) -> Option<Box<AvlNode>> {
    let mut stack: Vec<*mut AvlNode> = Vec::new();
    let mut current = &avlt.root.as_ref().unwrap().left;
    let mut parent_ptr: Option<*mut AvlNode> = None;
    
    let mydata: Box<Mydata> = data
        .downcast::<Mydata>()
        .expect("Failed to downcast to Mydata");
    let mydata_ref: Option<&Mydata> = Some(mydata.as_ref());
    // Find insertion point
    while let Some(node) = current {
        println!("salam");
        let cmp = (avlt.compare)(
            //&data,
            //node.data.as_ref().unwrap()
            mydata_ref,
            //Some(data).as_ref().map(|data| {
            //    data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
            //}),
            node.data.as_ref().map(|data| {
                data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
            }),
        );
        let node_ptr = &**node as *const AvlNode as *mut AvlNode;
        stack.push(node_ptr);
        parent_ptr = Some(node_ptr);
        current = if cmp < 0 {
            &node.left
        } else {
            &node.right
        };
    }

    // Create new node
    let mut new_node = Box::new(AvlNode {
        left: None,
        right: None,
        parent: None,
        bf: 0,
        data: Some(mydata),
    });
    let new_node_ptr = &mut *new_node as *mut AvlNode;

    // Insert node
    if let Some(parent) = parent_ptr {
        unsafe {
            let parent_node = &mut *parent;
            let cmp = (avlt.compare)(
                //new_node.data.as_ref().unwrap(),
                //parent_node.data.as_ref().unwrap()
                new_node.data.as_ref().map(|data| {
                    data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
                }),
                parent_node.data.as_ref().map(|data| {
                    data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
                }),
            );
            
            // Set new node's parent
            new_node.parent = Some(Box::from_raw(parent));
            
            if cmp < 0 {
                parent_node.left = Some(new_node);
            } else {
                parent_node.right = Some(new_node);
            }
        }
    } else {
        // This is the root node
        avlt.root = Some(new_node);
    }

    // Update min if needed
    unsafe {
        let new_node_ref = &mut *new_node_ptr;
        if avlt.min.is_none() {
            avlt.min = Some(Box::new(AvlNode {
                left: None,
                right: None,
                parent: None,
                bf: 0,
                data: new_node_ref.data.take(),
            }));
        } else {
            let min_ref = avlt.min.as_ref().unwrap();
            let cmp = (avlt.compare)(
                //new_node_ref.data.as_ref().unwrap(),
                //min_ref.data.as_ref().unwrap()
                new_node_ref.data.as_ref().map(|data| {
                    data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
                }),
                min_ref.data.as_ref().map(|data| {
                    data.downcast_ref::<Mydata>().expect("Failed to downcast to Mydata")
                }),
            );
            if cmp < 0 {
                avlt.min = Some(Box::new(AvlNode {
                    left: None,
                    right: None,
                    parent: None,
                    bf: 0,
                    data: new_node_ref.data.take(),
                }));
            }
        }
    }

    // Rebalance tree
    stack.push(new_node_ptr);
    let mut current_idx = 0;
    let mut parent_idx = 0;
    for i in (0..stack.len()).rev() {
        unsafe {
            if i == 0 {
                break;
            }
            let current_node = &mut *stack[i];
            let parent_node = &mut *stack[i-1];
            helper_avl_insert_1(
                &mut current_idx,
                &mut parent_idx,
                avlt,
                current_node,
                parent_node,
            );
        }
    }

    // Return the new node
    Some(Box::new(AvlNode {
        left: None,
        right: None,
        parent: None,
        bf: 0,
        data: None,
    }))
}
pub fn fix_delete_rightimbalance<'a>(avlt: &'a mut AvlTree, p: &'a mut AvlNode) -> &'a mut AvlNode {
    match p.right.as_mut().map(|n| n.bf) {
        Some(1) => {
            let _p_idx = rotate_left(avlt, p);
            p.bf = 0;
            if let Some(left) = p.left.as_mut() {
                left.bf = 0;
            }
        }
        Some(0) => {
            let _p_idx = rotate_left(avlt, p);
            p.bf = -1;
            if let Some(left) = p.left.as_mut() {
                left.bf = 1;
            }
        }
        Some(-1) => {
            let oldbf = p.right.as_ref()
                .and_then(|n| n.left.as_ref())
                .map(|n| n.bf)
                .unwrap_or(0);
            
            if let Some(right) = p.right.as_mut() {
                rotate_right(avlt, right);
            }
            
            let _p_idx = rotate_left(avlt, p);
            p.bf = 0;
            
            match oldbf {
                -1 => {
                    if let Some(left) = p.left.as_mut() {
                        left.bf = 0;
                    }
                    if let Some(right) = p.right.as_mut() {
                        right.bf = 1;
                    }
                }
                1 => {
                    if let Some(left) = p.left.as_mut() {
                        left.bf = -1;
                    }
                    if let Some(right) = p.right.as_mut() {
                        right.bf = 0;
                    }
                }
                0 => {
                    if let Some(left) = p.left.as_mut() {
                        left.bf = 0;
                    }
                    if let Some(right) = p.right.as_mut() {
                        right.bf = 0;
                    }
                }
                _ => {}
            }
        }
        _ => {}
    }
    p
}
pub fn fix_delete_leftimbalance<'a>(avlt: &'a mut AvlTree, p: &'a mut AvlNode) -> &'a mut AvlNode {
    match p.left.as_mut() {
        Some(left) => {
            match left.bf {
                -1 => {
                    let _p_idx = rotate_right(avlt, p);
                    p.bf = 0;
                    if let Some(right) = p.right.as_mut() {
                        right.bf = 0;
                    }
                }
                0 => {
                    let _p_idx = rotate_right(avlt, p);
                    p.bf = 1;
                    if let Some(right) = p.right.as_mut() {
                        right.bf = -1;
                    }
                }
                1 => {
                    let oldbf = if let Some(left_right) = left.right.as_ref() {
                        left_right.bf
                    } else {
                        0
                    };
                    
                    {
                        let left = p.left.as_mut().unwrap();
                        rotate_left(avlt, left);
                    }
                    
                    let _p_idx = rotate_right(avlt, p);
                    p.bf = 0;
                    
                    match oldbf {
                        -1 => {
                            if let Some(left) = p.left.as_mut() {
                                left.bf = 0;
                            }
                            if let Some(right) = p.right.as_mut() {
                                right.bf = 1;
                            }
                        }
                        1 => {
                            if let Some(left) = p.left.as_mut() {
                                left.bf = -1;
                            }
                            if let Some(right) = p.right.as_mut() {
                                right.bf = 0;
                            }
                        }
                        0 => {
                            if let Some(left) = p.left.as_mut() {
                                left.bf = 0;
                            }
                            if let Some(right) = p.right.as_mut() {
                                right.bf = 0;
                            }
                        }
                        _ => {}
                    }
                }
                _ => {}
            }
        }
        None => {}
    }
    p
}
pub fn helper_avl_delete_1(
    current_idx_ref: &mut Option<Box<AvlNode>>,
    parent_idx_ref: &mut Option<Box<AvlNode>>,
    avlt: &mut AvlTree,
    current: &mut AvlNode,
    parent: &mut AvlNode,
) {
    let mut current_idx = current_idx_ref.take();
    let mut parent_idx = parent_idx_ref.take();

    if parent.left.as_deref_mut().map(|n| n as *mut _) == Some(current as *mut _) {
        match parent.bf {
            -1 => {
                parent.bf = 0;
            }
            0 => {
                parent.bf = 1;
                return;
            }
            1 => {
                let new_parent = fix_delete_rightimbalance(avlt, parent);
                parent_idx = Some(Box::new(unsafe { std::ptr::read(new_parent) }));
                if new_parent.bf == -1 {
                    return;
                }
            }
            _ => {}
        }
    } else {
        match parent.bf {
            1 => {
                parent.bf = 0;
            }
            0 => {
                parent.bf = -1;
                return;
            }
            -1 => {
                let new_parent = fix_delete_leftimbalance(avlt, parent);
                parent_idx = Some(Box::new(unsafe { std::ptr::read(new_parent) }));
                if new_parent.bf == 1 {
                    return;
                }
            }
            _ => {}
        }
    }

    current_idx = parent_idx;
    parent_idx = current.parent.take();

    *current_idx_ref = current_idx;
    *parent_idx_ref = parent_idx;
}
pub fn avl_delete(avlt: &mut AvlTree, node: &mut AvlNode, keep: i32) -> Option<Box<dyn Any>> {
    let data = node.data.take();

    let target = if node.left.is_none() || node.right.is_none() {
        if let Some(min_node) = &avlt.min {
            if std::ptr::eq(&**min_node, node) {
                avlt.min = None;
            }
        }
        node
    } else {
        let successor_ptr = {
            let succ_ref = avl_successor(avlt, node)?;
            succ_ref as *const AvlNode
        };
        let successor_node_mut = unsafe {
            #[allow(invalid_reference_casting)]
            &mut *(successor_ptr as *mut AvlNode)
        };
        node.data = successor_node_mut.data.take();
        successor_node_mut
    };

    let parent_ptr = target.parent.as_mut().map(|p| p.as_mut() as *mut AvlNode);
    if parent_ptr.is_none() {
        return data;
    }

    let target_ptr = target as *mut AvlNode;

    let root_left_ptr = avlt.root.as_ref()
        .and_then(|root| root.left.as_ref())
        .map(|left| &**left as *const AvlNode)
        .unwrap_or(std::ptr::null());

    while (target_ptr as *const AvlNode) != root_left_ptr {
        let parent = unsafe { &mut *parent_ptr.unwrap() };
        helper_avl_delete_1(
            &mut None,
            &mut None,
            avlt,
            unsafe { &mut *target_ptr },
            parent,
        );
    }

    let target_ref = unsafe { &mut *target_ptr };
    let mut child = if target_ref.left.is_none() {
        target_ref.right.take()
    } else {
        target_ref.left.take()
    };

    if let Some(ref mut child_node) = child {
        child_node.parent = target_ref.parent.take();
    }

    let target_ptr_const = target_ptr as *const AvlNode;
    if let Some(target_parent) = target_ref.parent.as_mut() {
        let left_ptr = target_parent.left.as_ref()
            .map(|left| &**left as *const AvlNode)
            .unwrap_or(std::ptr::null());
        if std::ptr::eq(target_ptr_const, left_ptr) {
            target_parent.left = child;
        } else {
            target_parent.right = child;
        }
    }

    if keep == 0 {
        //if let Some(destroy_fn) = &avlt.destroy {
            if let Some(data) = &data {
                //destroy_fn(&**data);
            }
        //}
    }

    data
}
pub fn avl_apply(
    avlt: &AvlTree,
    node: Option<&Box<AvlNode>>,
    func: &dyn Fn(&dyn std::any::Any, &dyn std::any::Any) -> i32,
    cookie: &dyn std::any::Any,
    order: AvlTraversal,
) -> i32 {
    // Check if node is not nil (equivalent to node != (&avlt->nil) in C)
    if let Some(node) = node {
        if order == AvlTraversal::PREORDER {
            if let Some(data) = &node.data {
                let err = func(data, cookie);
                if err != 0 {
                    return err;
                }
            }
        }

        if let Some(left) = &node.left {
            let err = avl_apply(avlt, Some(left), func, cookie, order);
            if err != 0 {
                return err;
            }
        }

        if order == AvlTraversal::INORDER {
            if let Some(data) = &node.data {
                let err = func(data, cookie);
                if err != 0 {
                    return err;
                }
            }
        }

        if let Some(right) = &node.right {
            let err = avl_apply(avlt, Some(right), func, cookie, order);
            if err != 0 {
                return err;
            }
        }

        if order == AvlTraversal::POSTORDER {
            if let Some(data) = &node.data {
                let err = func(data, cookie);
                if err != 0 {
                    return err;
                }
            }
        }
    }
    0
}
