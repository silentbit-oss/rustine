use crate::*;
use std::f64::INFINITY;
use std::f64::NEG_INFINITY;
use std::any::Any;

pub fn descent(node: &QuadtreeNode) {
    if let Some(bounds) = &node.bounds {
        if let Some(nw) = &bounds.nw {
            if let Some(se) = &bounds.se {
                println!(
                    "{{ nw.x:{}, nw.y:{}, se.x:{}, se.y:{} }}: ",
                    nw.x, nw.y, se.x, se.y
                );
            }
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
    let mut bounds_opt = quadtree_bounds_new();
    assert!(bounds_opt.is_some());
    let bounds = bounds_opt.as_mut().unwrap();
    assert_eq!(bounds.nw.as_ref().unwrap().x, f64::INFINITY);
    assert_eq!(bounds.se.as_ref().unwrap().x, f64::NEG_INFINITY);
    
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
    
    quadtree_bounds_free(bounds_opt);
}
pub fn test_tree() {
    let val = Box::new(10) as Box<dyn Any>;
    let mut tree = quadtree_new(1.0, 1.0, 10.0, 10.0).expect("Failed to create quadtree");

    // Verify tree bounds
    {
        let root = tree.root.as_ref().unwrap();
        let bounds = root.bounds.as_ref().unwrap();
        let nw = bounds.nw.as_ref().unwrap();
        let se = bounds.se.as_ref().unwrap();
        assert_eq!(nw.x, 1.0);
        assert_eq!(nw.y, 10.0);
        assert_eq!(se.x, 10.0);
        assert_eq!(se.y, 1.0);
    }

    // Test insertions
    assert!(!quadtree_insert(&mut tree, 0.0, 0.0, Box::new(10) as Box<dyn Any>));
    assert!(!quadtree_insert(&mut tree, 10.0, 10.0, Box::new(10) as Box<dyn Any>));
    assert!(!quadtree_insert(&mut tree, 110.0, 110.0, Box::new(10) as Box<dyn Any>));
    assert!(quadtree_insert(&mut tree, 8.0, 2.0, Box::new(10) as Box<dyn Any>));
    assert_eq!(tree.length, 1);

    {
        let root = tree.root.as_ref().unwrap();
        let point = root.point.as_ref().unwrap();
        assert_eq!(point.x, 8.0);
        assert_eq!(point.y, 2.0);
    }

    assert!(quadtree_insert(&mut tree, 2.0, 3.0, Box::new(10) as Box<dyn Any>));
    assert!(!quadtree_insert(&mut tree, 2.0, 3.0, Box::new(10) as Box<dyn Any>));
    assert_eq!(tree.length, 2);

    {
        let root = tree.root.as_ref().unwrap();
        assert!(root.point.is_none());
    }

    assert!(quadtree_insert(&mut tree, 3.0, 1.1, Box::new(10) as Box<dyn Any>));
    assert_eq!(tree.length, 3);

    {
        let point = quadtree_search(&tree, 3.0, 1.1).unwrap();
        assert_eq!(point.x, 3.0);
    }

    {
        let mut root = tree.root.as_mut().unwrap();
        let mut ascent_wrapper = |node: &mut QuadtreeNode| {
            ascent(Some(node));
        };
        let mut descent_wrapper = |node: &mut QuadtreeNode| {
            descent(node);
        };
        quadtree_walk(&mut root, &mut ascent_wrapper, &mut descent_wrapper);
    }

    quadtree_free(tree);
}

pub fn test_node() {
    let node = quadtree_node_new().expect("Failed to create new quadtree node");
    assert!(!quadtree_node_isleaf(&node));
    assert!(quadtree_node_isempty(&node));
    assert!(!quadtree_node_ispointer(&node));
}
