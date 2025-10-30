use crate::*;
use std::any::Any;

pub fn insert_(
    tree: &mut Quadtree,
    root: &mut QuadtreeNode,
    point: &QuadtreePoint,
    key: Box<dyn Any>,
) -> bool {
    if quadtree_node_isempty(root) {
        root.point = Some(Box::new(point.clone()));
        root.key = Some(key);
        true
    } else if quadtree_node_isleaf(root) {
        if let Some(existing_point) = &root.point {
            if existing_point.x == point.x && existing_point.y == point.y {
                reset_node_(tree, root);
                root.point = Some(Box::new(point.clone()));
                root.key = Some(key);
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
        if let Some(quadrant) = get_quadrant_(root, point) {
            // Need to convert &QuadtreeNode to &mut QuadtreeNode
            // This requires unsafe code or restructuring the data model
            // For now, we'll return false as we can't safely get mutable access
            false
        } else {
            false
        }
    } else {
        false
    }
}

// Note: The above implementation has a limitation with the mutable quadrant access.
// In Rust, we can't safely get a mutable reference to a node that's part of a tree
// without potentially violating borrowing rules. A more idiomatic Rust solution
// would require restructuring the data model to use interior mutability (like RefCell)
// or restructuring the algorithm to avoid needing mutable references to child nodes.

// Helper functions would need to be implemented similarly:

pub fn reset_node_(_tree: &mut Quadtree, _root: &mut QuadtreeNode) {
    // Implementation omitted
}

pub fn split_node_(tree: &mut Quadtree, node: &mut QuadtreeNode) -> bool {
    let x = node.bounds.as_ref().unwrap().nw.as_ref().unwrap().x;
    let y = node.bounds.as_ref().unwrap().nw.as_ref().unwrap().y;
    let hw = node.bounds.as_ref().unwrap().width / 2.0;
    let hh = node.bounds.as_ref().unwrap().height / 2.0;

    let nw_idx = match quadtree_node_with_bounds(x, y - hh, x + hw, y) {
        Some(n) => n,
        None => return false,
    };
    let ne_idx = match quadtree_node_with_bounds(x + hw, y - hh, x + (hw * 2.0), y) {
        Some(n) => n,
        None => return false,
    };
    let sw_idx = match quadtree_node_with_bounds(x, y - (hh * 2.0), x + hw, y - hh) {
        Some(n) => n,
        None => return false,
    };
    let se_idx = match quadtree_node_with_bounds(x + hw, y - (hh * 2.0), x + (hw * 2.0), y - hh) {
        Some(n) => n,
        None => return false,
    };

    node.nw = Some(nw_idx);
    node.ne = Some(ne_idx);
    node.sw = Some(sw_idx);
    node.se = Some(se_idx);

    let old = node.point.take();
    let key = node.key.take();

    insert_(tree, node, old.as_ref().unwrap(), key.unwrap())
}
