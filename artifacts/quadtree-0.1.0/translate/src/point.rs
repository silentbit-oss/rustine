use crate::*;

pub fn quadtree_point_new(x: f64, y: f64) -> Option<Box<QuadtreePoint>> {
    Some(Box::new(QuadtreePoint { x, y }))
}
pub fn quadtree_point_free(point: Option<Box<QuadtreePoint>>) {
    // In Rust, dropping the Box automatically frees the memory
    // No explicit free needed - just let the Box go out of scope
    // The Option wrapper handles NULL case (None in Rust)
    drop(point);
}
