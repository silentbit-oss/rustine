use crate::*;
use std::any::Any;

pub fn split_node_(tree: &mut Quadtree, node: &mut QuadtreeNode) -> bool {
    let bounds = match &node.bounds {
        Some(b) => b,
        None => return false,
    };
    let nw_point = match &bounds.nw {
        Some(p) => p,
        None => return false,
    };

    let x = nw_point.x;
    let y = nw_point.y;
    let hw = bounds.width / 2.0;
    let hh = bounds.height / 2.0;

    let nw_idx = match quadtree_node_with_bounds(x, y - hh, x + hw, y) {
        Some(node) => node,
        None => return false,
    };
    let ne_idx = match quadtree_node_with_bounds(x + hw, y - hh, x + (hw * 2.0), y) {
        Some(node) => node,
        None => return false,
    };
    let sw_idx = match quadtree_node_with_bounds(x, y - (hh * 2.0), x + hw, y - hh) {
        Some(node) => node,
        None => return false,
    };
    let se_idx = match quadtree_node_with_bounds(x + hw, y - (hh * 2.0), x + (hw * 2.0), y - hh) {
        Some(node) => node,
        None => return false,
    };

    node.nw = Some(nw_idx);
    node.ne = Some(ne_idx);
    node.sw = Some(sw_idx);
    node.se = Some(se_idx);

    let old = node.point.take();
    let key = node.key.take();

    if let Some(point) = old {
        insert_(tree, node, &*point, key)
    } else {
        false
    }
}

pub fn insert_(
    tree: &mut Quadtree,
    root: &mut QuadtreeNode,
    point: &QuadtreePoint,
    key: Option<Box<dyn Any>>,
) -> bool {
    if quadtree_node_isempty(root) {
        root.point = Some(Box::new(point.clone()));
        root.key = key;
        true
    } else if quadtree_node_isleaf(root) {
        if let Some(root_point) = &root.point {
            if (root_point.x == point.x) && (root_point.y == point.y) {
                reset_node_(tree, root);
                root.point = Some(Box::new(point.clone()));
                root.key = key;
                false
            } else {
                if !split_node_(tree, root) {
                    false
                } else {
                    insert_(tree, root, point, key)
                }
            }
        } else {
            // This case shouldn't happen since we checked is_leaf
            false
        }
    } else if quadtree_node_ispointer(root) {
        let quadrant = get_quadrant_(root, point);
        let quadrant_ptr = match quadrant {
            Some(q) => q as *const QuadtreeNode,
            None => return false,
        };

        // Create a mutable reference to the matching quadrant
        let mut result = false;
        
        // Check each quadrant and find the matching one
        if let Some(ref mut ne) = root.ne {
            if std::ptr::eq(ne.as_ref(), quadrant_ptr) {
                result = insert_(tree, ne, point, key);
                return result;
            }
        }
        if let Some(ref mut nw) = root.nw {
            if std::ptr::eq(nw.as_ref(), quadrant_ptr) {
                result = insert_(tree, nw, point, key);
                return result;
            }
        }
        if let Some(ref mut se) = root.se {
            if std::ptr::eq(se.as_ref(), quadrant_ptr) {
                result = insert_(tree, se, point, key);
                return result;
            }
        }
        if let Some(ref mut sw) = root.sw {
            if std::ptr::eq(sw.as_ref(), quadrant_ptr) {
                result = insert_(tree, sw, point, key);
                return result;
            }
        }
        result
    } else {
        false
    }
}
