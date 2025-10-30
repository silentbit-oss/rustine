use crate::*;
use std::assert;
use std::fmt;
use std::f64::INFINITY;
use std::f64::NEG_INFINITY;


pub fn descent(node: &QuadtreeNode) {
    if let Some(bounds) = &node.bounds {
        if let (Some(nw), Some(se)) = (&bounds.nw, &bounds.se) {
            println!(
                "{{ nw.x:{}, nw.y:{}, se.x:{}, se.y:{} }}: ",
                nw.x, nw.y, se.x, se.y
            );
        }
    }
}
pub fn ascent(node: Option<&mut QuadtreeNode>) {
    println!();
}
pub fn test_points() {
    let point = quadtree_point_new(5.0, 6.0).expect("Failed to create point");
    assert_eq!(point.x, 5.0);
    assert_eq!(point.y, 6.0);
    quadtree_point_free(Some(point));
}
pub fn test_bounds() {
    let mut bounds = quadtree_bounds_new();
    assert!(bounds.is_some());
    let bounds = bounds.as_mut().unwrap();
    assert_eq!(bounds.nw.as_ref().unwrap().x, INFINITY);
    assert_eq!(bounds.se.as_ref().unwrap().x, NEG_INFINITY);
    
    quadtree_bounds_extend(bounds, 5.0, 5.0);
    assert_eq!(bounds.nw.as_ref().unwrap().x, 5.0);
    assert_eq!(bounds.se.as_ref().unwrap().x, 5.0);
    
    quadtree_bounds_extend(bounds, 10.0, 10.0);
    assert_eq!(bounds.nw.as_ref().unwrap().y, 10.0);
    assert_eq!(bounds.nw.as_ref().unwrap().y, 10.0);
    assert_eq!(bounds.se.as_ref().unwrap().y, 5.0);
    assert_eq!(bounds.se.as_ref().unwrap().y, 5.0);
    assert_eq!(bounds.width, 5.0);
    assert_eq!(bounds.height, 5.0);
    
    quadtree_bounds_free(Some(Box::new(*bounds.clone())));
}
pub fn test_tree() {
    let val = Box::new(10);
    let mut tree = quadtree_new(1.0, 1.0, 10.0, 10.0);
    let mut tree_unwrapped = tree.as_mut().unwrap();

    // Verify initial bounds
    assert!(tree_unwrapped.root.as_ref().unwrap().bounds.as_ref().unwrap().nw.as_ref().unwrap().x == 1.0);
    assert!(tree_unwrapped.root.as_ref().unwrap().bounds.as_ref().unwrap().nw.as_ref().unwrap().y == 10.0);
    assert!(tree_unwrapped.root.as_ref().unwrap().bounds.as_ref().unwrap().se.as_ref().unwrap().x == 10.0);
    assert!(tree_unwrapped.root.as_ref().unwrap().bounds.as_ref().unwrap().se.as_ref().unwrap().y == 1.0);

    // Test insertions
    assert!(!quadtree_insert(tree_unwrapped, 0.0, 0.0, val.clone()));
    assert!(!quadtree_insert(tree_unwrapped, 10.0, 10.0, val.clone()));
    assert!(!quadtree_insert(tree_unwrapped, 110.0, 110.0, val.clone()));
    assert!(quadtree_insert(tree_unwrapped, 8.0, 2.0, val.clone()));
    assert!(tree_unwrapped.length == 1);
    assert!(tree_unwrapped.root.as_ref().unwrap().point.as_ref().unwrap().x == 8.0);
    assert!(tree_unwrapped.root.as_ref().unwrap().point.as_ref().unwrap().y == 2.0);
    assert!(quadtree_insert(tree_unwrapped, 2.0, 3.0, val.clone()));
    assert!(!quadtree_insert(tree_unwrapped, 2.0, 3.0, val.clone()));
    assert!(tree_unwrapped.length == 2);
    assert!(tree_unwrapped.root.as_ref().unwrap().point.is_none());
    assert!(quadtree_insert(tree_unwrapped, 3.0, 1.1, val.clone()));
    assert!(tree_unwrapped.length == 3);
    assert!(quadtree_search(tree_unwrapped, 3.0, 1.1).unwrap().x == 3.0);

    // Perform tree walk
    let mut root = tree_unwrapped.root.take().unwrap();
    quadtree_walk(
        &mut root,
        &mut |node| ascent(Some(node)),
        &mut |node| descent(node),
    );
    tree_unwrapped.root = Some(root);

    // Clean up
    quadtree_free(tree.unwrap());
}
pub fn test_node() {
    let node = quadtree_node_new().expect("Failed to create quadtree node");
    assert!(!quadtree_node_isleaf(&node));
    assert!(quadtree_node_isempty(&node));
    assert!(!quadtree_node_ispointer(&node));
}
