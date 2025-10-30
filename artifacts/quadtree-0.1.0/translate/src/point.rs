use crate::*;

pub fn quadtree_point_new(x: f64, y: f64) -> Option<Box<QuadtreePoint>> {
    Some(Box::new(QuadtreePoint { x, y }))
}
pub fn quadtree_point_free(point: Option<Box<QuadtreePoint>>) {
    // Rust's Box will automatically free the memory when it goes out of scope
    // No explicit free needed, just let the Box drop
}
