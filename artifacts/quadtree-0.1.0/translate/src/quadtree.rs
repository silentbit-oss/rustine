use crate::*;
use std::f64;

pub fn elision_(key: Option<&mut ()>) {
    // The function takes an Option of mutable reference to unit type
    // Since the C function does nothing with the key, we don't need to use it
    // The parameter is marked as Option to match C's NULL pointer semantics
}
pub fn quadtree_walk(
    root: &mut QuadtreeNode,
    descent: &mut dyn FnMut(&mut QuadtreeNode),
    ascent: &mut dyn FnMut(&mut QuadtreeNode),
) {
    // Call descent callback
    descent(root);

    // Recursively walk through child nodes if they exist
    if let Some(nw) = &mut root.nw {
        quadtree_walk(nw.as_mut(), descent, ascent);
    }
    if let Some(ne) = &mut root.ne {
        quadtree_walk(ne.as_mut(), descent, ascent);
    }
    if let Some(sw) = &mut root.sw {
        quadtree_walk(sw.as_mut(), descent, ascent);
    }
    if let Some(se) = &mut root.se {
        quadtree_walk(se.as_mut(), descent, ascent);
    }

    // Call ascent callback
    ascent(root);
}

pub fn quadtree_new(minx: f64, miny: f64, maxx: f64, maxy: f64) -> Option<Box<Quadtree>> {
    let root = quadtree_node_with_bounds(minx, miny, maxx, maxy);
    if root.is_none() {
        return None;
    }

    Some(Box::new(Quadtree {
        root,
        key_free: None,
        length: 0,
    }))
}
pub fn node_contains_(outer: &QuadtreeNode, it: &QuadtreePoint) -> bool {
    // Check if bounds exists and all nested Option fields are Some
    if let Some(bounds) = &outer.bounds {
        if let Some(nw) = &bounds.nw {
            if let Some(se) = &bounds.se {
                return (nw.x < it.x) && (nw.y > it.y) && (se.x > it.x) && (se.y < it.y);
            }
        }
    }
    false
}
static mut CURRENT_KEY_FREE: Option<*mut Box<dyn FnMut(Box<dyn std::any::Any>)>> = None;

fn key_free_callback(key: Option<Box<dyn std::any::Any>>) {
    unsafe {
        if let Some(ptr) = CURRENT_KEY_FREE {
            if let Some(k) = key {
                (*ptr)(k);
            }
        }
    }
}

pub fn reset_node_(tree: &mut Quadtree, node: &mut QuadtreeNode) {
    if let Some(key_free) = &mut tree.key_free {
        let key_free_ptr: *mut Box<dyn FnMut(Box<dyn std::any::Any>)> = key_free;
        unsafe {
            CURRENT_KEY_FREE = Some(key_free_ptr);
            quadtree_node_reset(node, key_free_callback);
            CURRENT_KEY_FREE = None;
        }
    } else {
        fn do_nothing(_: Option<Box<dyn std::any::Any>>) {}
        quadtree_node_reset(node, do_nothing);
    }
}
pub fn get_quadrant_<'a>(root: &'a QuadtreeNode, point: &QuadtreePoint) -> Option<&'a QuadtreeNode> {
    if let Some(nw) = &root.nw {
        if node_contains_(nw, point) {
            return Some(nw);
        }
    }
    if let Some(ne) = &root.ne {
        if node_contains_(ne, point) {
            return Some(ne);
        }
    }
    if let Some(sw) = &root.sw {
        if node_contains_(sw, point) {
            return Some(sw);
        }
    }
    if let Some(se) = &root.se {
        if node_contains_(se, point) {
            return Some(se);
        }
    }
    None
}
pub fn quadtree_insert(tree: &mut Quadtree, x: f64, y: f64, key: Box<dyn std::any::Any>) -> bool {
    // Create new point (equivalent to quadtree_point_new in C)
    let point = match quadtree_point_new(x, y) {
        Some(p) => p,
        None => return false,
    };

    // Check if root node contains the point
    let root_contains = match &tree.root {
        Some(root) => node_contains_(root, &point),
        None => return false,
    };

    if !root_contains {
        return false;
    }

    // Perform insertion
    let insertion_success = match &mut tree.root {
        Some(root) => {
            let root_ptr: *mut QuadtreeNode = root.as_mut();
            // SAFETY: We know root_ptr is valid because we just got it from the Option
            unsafe {
                insert_(tree, &mut *root_ptr, &point, Some(key))
            }
        }
        None => false,
    };

    if insertion_success {
        tree.length += 1;
        true
    } else {
        false
    }
}
pub fn quadtree_free(tree: Box<Quadtree>) {
    if let Some(mut key_free) = tree.key_free {
        // Define a helper function that takes the key and calls the key_free closure
        fn key_free_wrapper(key: Option<Box<dyn std::any::Any>>, key_free: &mut Box<dyn FnMut(Box<dyn std::any::Any>)>) {
            if let Some(key) = key {
                (*key_free)(key);
            }
        }
        
        // Create a function pointer that doesn't capture anything
        fn key_free_fn(key: Option<Box<dyn std::any::Any>>) {
            // This will panic if called, but we'll ensure it's never called
            panic!("key_free_fn should not be called directly");
        }
        
        // Store the key_free in a static mut (unsafe, but necessary for this pattern)
        static mut KEY_FREE: Option<Box<dyn FnMut(Box<dyn std::any::Any>)>> = None;
        unsafe {
            KEY_FREE = Some(key_free);
            quadtree_node_free(tree.root, |key| {
                if let Some(kf) = &mut KEY_FREE {
                    if let Some(key) = key {
                        (*kf)(key);
                    }
                }
            });
            KEY_FREE = None;
        }
    } else {
        // For the None case, use a simple function that matches the expected signature
        fn elision_wrapper(_key: Option<Box<dyn std::any::Any>>) {}
        quadtree_node_free(tree.root, elision_wrapper);
    }
    // The Box<Quadtree> will be automatically dropped (freed) when it goes out of scope
}
pub fn find_(node: &QuadtreeNode, x: f64, y: f64) -> Option<&QuadtreePoint> {
    if quadtree_node_isleaf(node) {
        if let Some(point) = &node.point {
            if (point.x == x) && (point.y == y) {
                return Some(point);
            }
        }
    } else {
        let test = QuadtreePoint { x, y };
        if let Some(quadrant) = get_quadrant_(node, &test) {
            return find_(quadrant, x, y);
        }
    }
    None
}
pub fn quadtree_search(tree: &Quadtree, x: f64, y: f64) -> Option<&QuadtreePoint> {
    // Check if the tree has a root node
    match &tree.root {
        Some(root) => find_(root, x, y),
        None => None,
    }
}
