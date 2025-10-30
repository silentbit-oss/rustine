use crate::*;
use std::f64;
use std::f64::INFINITY;
use std::f64::NEG_INFINITY;


pub fn quadtree_bounds_extend(bounds: &mut QuadtreeBounds, x: f64, y: f64) {
    // Handle nw updates
    if let Some(ref mut nw) = bounds.nw {
        nw.x = f64::min(x, nw.x);
        nw.y = f64::max(y, nw.y);
    }

    // Handle se updates
    if let Some(ref mut se) = bounds.se {
        se.x = f64::max(x, se.x);
        se.y = f64::min(y, se.y);
    }

    // Calculate new dimensions
    if let (Some(nw), Some(se)) = (&bounds.nw, &bounds.se) {
        bounds.width = f64::abs(nw.x - se.x);
        bounds.height = f64::abs(nw.y - se.y);
    }
}

pub fn quadtree_bounds_new() -> Option<Box<QuadtreeBounds>> {
    let nw = quadtree_point_new(INFINITY, NEG_INFINITY);
    let se = quadtree_point_new(NEG_INFINITY, INFINITY);

    Some(Box::new(QuadtreeBounds {
        nw,
        se,
        width: 0.0,
        height: 0.0,
    }))
}
pub fn quadtree_bounds_free(bounds: Option<Box<QuadtreeBounds>>) {
    if let Some(bounds) = bounds {
        quadtree_point_free(bounds.nw);
        quadtree_point_free(bounds.se);
        // The Box will be automatically dropped here, freeing the memory
    }
}
