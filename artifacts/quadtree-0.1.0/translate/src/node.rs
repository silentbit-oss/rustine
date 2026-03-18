use crate::*;
use std::f64;

pub fn quadtree_node_new() -> Option<Box<QuadtreeNode>> {
    Some(Box::new(QuadtreeNode {
        ne: None,
        nw: None,
        se: None,
        sw: None,
        point: None,
        bounds: None,
        key: None,
    }))
}
pub fn quadtree_node_isleaf(node: &QuadtreeNode) -> bool {
    node.point.is_some()
}
pub fn quadtree_node_ispointer(node: &QuadtreeNode) -> bool {
    // Check if all child nodes exist (not None) and the node is not a leaf
    node.nw.is_some() && 
    node.ne.is_some() && 
    node.sw.is_some() && 
    node.se.is_some() && 
    !quadtree_node_isleaf(node)
}
pub fn quadtree_node_isempty(node: &QuadtreeNode) -> bool {
    node.nw.is_none() && 
    node.ne.is_none() && 
    node.sw.is_none() && 
    node.se.is_none() && 
    !quadtree_node_isleaf(node)
}
pub fn quadtree_node_reset(node: &mut QuadtreeNode, key_free: fn(Option<Box<dyn std::any::Any>>)) {
    // Free the point if it exists
    quadtree_point_free(node.point.take());
    
    // Free the key using the provided function
    key_free(node.key.take());
}

pub fn quadtree_node_with_bounds(minx: f64, miny: f64, maxx: f64, maxy: f64) -> Option<Box<QuadtreeNode>> {
    let mut node = match quadtree_node_new() {
        Some(n) => n,
        None => return None,
    };

    node.bounds = match quadtree_bounds_new() {
        Some(b) => Some(b),
        None => return None,
    };

    if let Some(ref mut bounds) = node.bounds {
        quadtree_bounds_extend(bounds, maxx, maxy);
        quadtree_bounds_extend(bounds, minx, miny);
    }

    Some(node)
}
pub fn quadtree_node_free(node: Option<Box<QuadtreeNode>>, key_free: fn(Option<Box<dyn std::any::Any>>)) {
    if let Some(mut node) = node {
        // Recursively free child nodes
        if let Some(nw) = node.nw.take() {
            quadtree_node_free(Some(nw), key_free);
        }
        if let Some(ne) = node.ne.take() {
            quadtree_node_free(Some(ne), key_free);
        }
        if let Some(sw) = node.sw.take() {
            quadtree_node_free(Some(sw), key_free);
        }
        if let Some(se) = node.se.take() {
            quadtree_node_free(Some(se), key_free);
        }

        // Free bounds and reset node
        quadtree_bounds_free(node.bounds.take());
        quadtree_node_reset(&mut node, key_free);
        
        // The Box will be automatically dropped here, freeing the memory
    }
}
