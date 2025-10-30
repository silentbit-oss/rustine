use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;

pub fn elision_(key: Option<&mut std::ffi::c_void>) {
    // Empty function body as per original C code
    // The parameter is wrapped in Option to handle potential NULL pointer case
}
pub fn quadtree_walk(
    root: &mut QuadtreeNode,
    descent: &mut dyn FnMut(&mut QuadtreeNode),
    ascent: &mut dyn FnMut(&mut QuadtreeNode),
) {
    // Call descent callback
    descent(root);

    // Recursively walk through each child node if it exists
    if let Some(nw) = &mut root.nw {
        quadtree_walk(nw, descent, ascent);
    }
    if let Some(ne) = &mut root.ne {
        quadtree_walk(ne, descent, ascent);
    }
    if let Some(sw) = &mut root.sw {
        quadtree_walk(sw, descent, ascent);
    }
    if let Some(se) = &mut root.se {
        quadtree_walk(se, descent, ascent);
    }

    // Call ascent callback
    ascent(root);
}

pub fn quadtree_new(minx: f64, miny: f64, maxx: f64, maxy: f64) -> Option<Box<Quadtree>> {
    // Create the root node first
    let root = quadtree_node_with_bounds(minx, miny, maxx, maxy)?;

    // Allocate and initialize the Quadtree
    Some(Box::new(Quadtree {
        root: Some(root),
        key_free: None,
        length: 0,
    }))
}
pub fn node_contains_(outer: &QuadtreeNode, it: &QuadtreePoint) -> bool {
    // Check if bounds exists and all nested options are Some
    if let Some(bounds) = &outer.bounds {
        if let Some(nw) = &bounds.nw {
            if let Some(se) = &bounds.se {
                return (nw.x < it.x) && (nw.y > it.y) && (se.x > it.x) && (se.y < it.y);
            }
        }
    }
    false
}
static mut TEMP_KEY_FREE: Option<*mut Box<dyn FnMut(Box<dyn std::any::Any>)>> = None;

fn key_free_wrapper(key: Option<Box<dyn std::any::Any>>) {
    unsafe {
        if let Some(ptr) = TEMP_KEY_FREE {
            if let Some(k) = key {
                let key_free = &mut *ptr;
                key_free(k);
            }
        }
    }
}

fn elision_wrapper(key: Option<Box<dyn std::any::Any>>) {
    unsafe {
        if let Some(k) = key {
            let ptr = Box::into_raw(k) as *mut std::ffi::c_void;
            elision_(Some(&mut *ptr));
        } else {
            elision_(Option::None);
        }
    }
}

pub fn reset_node_(tree: &mut Quadtree, node: &mut QuadtreeNode) {
    if let Some(key_free) = &mut tree.key_free {
        unsafe {
            TEMP_KEY_FREE = Some(key_free as *mut _);
            quadtree_node_reset(node, key_free_wrapper);
            TEMP_KEY_FREE = None;
        }
    } else {
        quadtree_node_reset(node, elision_wrapper);
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
pub fn quadtree_insert(
    tree: &mut Quadtree,
    x: f64,
    y: f64,
    key: Box<dyn std::any::Any>,
) -> bool {
    // Create new point (equivalent to quadtree_point_new in C)
    let point = match quadtree_point_new(x, y) {
        Some(p) => p,
        None => return false,
    };

    // Check if root node exists and contains the point
    if let Some(root) = &tree.root {
        if !node_contains_(root, &point) {
            return false;
        }
    } else {
        return false;
    }

    // Temporarily take the root node to avoid overlapping mutable borrows
    let mut root_node = tree.root.take().unwrap();
    let success = insert_(tree, &mut root_node, &point, key);
    tree.root = Some(root_node);

    if !success {
        return false;
    }

    tree.length += 1;
    true
}
pub fn quadtree_free(tree: Box<Quadtree>) {
    if let Some(mut key_free) = tree.key_free {
        fn free_node<F>(node: Option<Box<QuadtreeNode>>, key_free: &mut F)
        where
            F: FnMut(Box<dyn std::any::Any>) + 'static,
        {
            if let Some(mut node) = node {
                free_node(node.ne.take(), key_free);
                free_node(node.nw.take(), key_free);
                free_node(node.se.take(), key_free);
                free_node(node.sw.take(), key_free);
                if let Some(key) = node.key.take() {
                    key_free(key);
                }
            }
        }
        free_node(tree.root, &mut key_free);
    } else {
        fn free_node_no_key_free(node: Option<Box<QuadtreeNode>>) {
            if let Some(mut node) = node {
                free_node_no_key_free(node.ne.take());
                free_node_no_key_free(node.nw.take());
                free_node_no_key_free(node.se.take());
                free_node_no_key_free(node.sw.take());
            }
        }
        free_node_no_key_free(tree.root);
    }
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
    // If the tree's root is None, return None immediately
    tree.root.as_ref().and_then(|root| find_(root, x, y))
}
