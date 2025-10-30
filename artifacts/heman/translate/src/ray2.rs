use crate::*;
use std::assert;
use std::f32;
use rand::Rng;

pub fn kmRay2Fill(ray: &mut KmRay2, px: f32, py: f32, vx: f32, vy: f32) {
    ray.start.x = px;
    ray.start.y = py;
    ray.dir.x = vx;
    ray.dir.y = vy;
}
pub fn kmLine2WithLineIntersection(
    ptA: &KmVec2,
    vecA: &KmVec2,
    ptB: &KmVec2,
    vecB: &KmVec2,
    outTA: Option<&mut f32>,
    outTB: Option<&mut f32>,
    outIntersection: Option<&mut KmVec2>,
) -> u8 {
    let x1 = ptA.x;
    let y1 = ptA.y;
    let x2 = x1 + vecA.x;
    let y2 = y1 + vecA.y;
    let x3 = ptB.x;
    let y3 = ptB.y;
    let x4 = x3 + vecB.x;
    let y4 = y3 + vecB.y;
    let denom = ((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1));

    if (denom > -0.0001) && (denom < 0.0001) {
        return 0;
    }

    let ua = (((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / denom;
    let ub = (((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / denom;
    let x = x1 + (ua * (x2 - x1));
    let y = y1 + (ua * (y2 - y1));

    if let Some(out_ta) = outTA {
        *out_ta = ua;
    }
    if let Some(out_tb) = outTB {
        *out_tb = ub;
    }
    if let Some(out_intersection) = outIntersection {
        out_intersection.x = x;
        out_intersection.y = y;
    }

    1
}
pub fn kmRay2FillWithEndpoints(ray: &mut KmRay2, start: &KmVec2, end: &KmVec2) {
    ray.start.x = start.x;
    ray.start.y = start.y;
    ray.dir.x = end.x - start.x;
    ray.dir.y = end.y - start.y;
}

pub fn kmRay2IntersectCircle(ray: &KmRay2, centre: KmVec2, radius: f32, intersection: Option<&mut KmVec2>) -> Option<u8> {
    assert!(false, "Not implemented");
    Some(1)
}
pub fn kmSegment2WithSegmentIntersection(
    segmentA: &KmRay2,
    segmentB: &KmRay2,
    intersection: Option<&mut KmVec2>,
) -> u8 {
    let mut ua: f32 = 0.0;
    let mut ub: f32 = 0.0;
    let mut pt = KmVec2 { x: 0.0, y: 0.0 };

    let intersects = kmLine2WithLineIntersection(
        &segmentA.start,
        &segmentA.dir,
        &segmentB.start,
        &segmentB.dir,
        Some(&mut ua),
        Some(&mut ub),
        Some(&mut pt),
    ) != 0 && (0.0 <= ua) && (ua <= 1.0) && (0.0 <= ub) && (ub <= 1.0);

    if intersects {
        if let Some(intersection) = intersection {
            intersection.x = pt.x;
            intersection.y = pt.y;
        }
        return 1;
    }
    0
}
pub fn kmRay2IntersectLineSegment(
    ray: &KmRay2,
    p1: &KmVec2,
    p2: &KmVec2,
    intersection: Option<&mut KmVec2>,
) -> u8 {
    let mut ua = 0.0;
    let mut ub = 0.0;
    let mut pt = KmVec2 { x: 0.0, y: 0.0 };
    let mut otherSegment = KmRay2 {
        start: KmVec2 { x: 0.0, y: 0.0 },
        dir: KmVec2 { x: 0.0, y: 0.0 },
    };
    
    kmRay2FillWithEndpoints(&mut otherSegment, p1, p2);
    
    let intersects = kmLine2WithLineIntersection(
        &ray.start,
        &ray.dir,
        &otherSegment.start,
        &otherSegment.dir,
        Some(&mut ua),
        Some(&mut ub),
        Some(&mut pt),
    ) != 0;
    
    if intersects && (0.0 <= ua) && (0.0 <= ub) && (ub <= 1.0) {
        if let Some(intersection) = intersection {
            intersection.x = pt.x;
            intersection.y = pt.y;
        }
        return 1;
    }
    
    0
}
pub fn calculate_line_normal(
    p1: KmVec2,
    p2: KmVec2,
    other_point: KmVec2,
    normal_out: Option<&mut KmVec2>,
) {
    // Early return if normal_out is None
    let normal_out = match normal_out {
        Some(out) => out,
        None => return,
    };

    let mut edge = KmVec2 { x: 0.0, y: 0.0 };
    let mut other_edge = KmVec2 { x: 0.0, y: 0.0 };

    // Calculate edges
    kmVec2Subtract(&mut edge, &p2, &p1);
    kmVec2Subtract(&mut other_edge, &other_point, &p1);

    // Normalize edges by creating temporary copies
    let mut edge_normalized = edge.clone();
    if kmVec2Normalize(Some(&mut edge_normalized), Some(&edge)).is_none() {
        return;
    }
    edge = edge_normalized;

    let mut other_edge_normalized = other_edge.clone();
    if kmVec2Normalize(Some(&mut other_edge_normalized), Some(&other_edge)).is_none() {
        return;
    }
    other_edge = other_edge_normalized;

    // Calculate normal
    let mut n = KmVec2 {
        x: edge.y,
        y: -edge.x,
    };

    // Flip normal if needed
    if let Some(d) = kmVec2Dot(Some(&n), Some(&other_edge)) {
        if d > 0.0 {
            n.x = -n.x;
            n.y = -n.y;
        }
    }

    // Set output
    normal_out.x = n.x;
    normal_out.y = n.y;
    
    // Normalize the output by creating a temporary copy
    let mut normalized_output = normal_out.clone();
    let _ = kmVec2Normalize(Some(&mut normalized_output), Some(normal_out));
    *normal_out = normalized_output;
}
pub fn helper_kmRay2IntersectBox_1(
    intersected_ref: &mut u8,
    distance_ref: &mut f32,
    ray: &KmRay2,
    intersect: KmVec2,
    final_intersect: &mut KmVec2,
    normal: &mut KmVec2,
    points: &[&KmVec2; 4],
    i: usize,
) {
    let mut intersected = *intersected_ref;
    let mut distance = *distance_ref;
    let this_point = points[i];
    let next_point = if i == 3 { points[0] } else { points[i + 1] };
    let other_point = if i == 3 || i == 0 { points[1] } else { points[0] };

    let mut tmp_intersect = intersect;
    if kmRay2IntersectLineSegment(ray, this_point, next_point, Some(&mut tmp_intersect)) != 0 {
        let mut tmp = KmVec2 { x: 0.0, y: 0.0 };
        let subtracted = kmVec2Subtract(&mut tmp, &tmp_intersect, &ray.start);
        let this_distance = kmVec2Length(Some(subtracted));

        let mut this_normal = KmVec2 { x: 0.0, y: 0.0 };
        calculate_line_normal(
            this_point.clone(),
            next_point.clone(),
            other_point.clone(),
            Some(&mut this_normal),
        );

        if this_distance < distance
            && kmVec2Dot(Some(&this_normal), Some(&ray.dir)).unwrap_or(0.0) < 0.0
        {
            kmVec2Assign(Some(final_intersect), Some(&tmp_intersect));
            distance = this_distance;
            intersected = 1;
            kmVec2Assign(Some(normal), Some(&this_normal));
        }
    }

    *intersected_ref = intersected;
    *distance_ref = distance;
}

pub fn kmRay2IntersectBox(
    ray: &KmRay2,
    p1: &KmVec2,
    p2: &KmVec2,
    p3: &KmVec2,
    p4: &KmVec2,
    intersection: Option<&mut KmVec2>,
    normal_out: Option<&mut KmVec2>,
) -> u8 {
    let mut intersected = 0;
    let mut final_intersect = KmVec2 { x: 0.0, y: 0.0 };
    let mut normal = KmVec2 { x: 0.0, y: 0.0 };
    let mut distance = 10000.0;
    let points = [p1, p2, p3, p4];

    for i in 0..4 {
        helper_kmRay2IntersectBox_1(
            &mut intersected,
            &mut distance,
            ray,
            KmVec2 { x: 0.0, y: 0.0 }, // dummy intersect since it's not used in the output
            &mut final_intersect,
            &mut normal,
            &points,
            i,
        );
    }

    if intersected != 0 {
        if let Some(intersection) = intersection {
            intersection.x = final_intersect.x;
            intersection.y = final_intersect.y;
        }
        if let Some(normal_out) = normal_out {
            normal_out.x = normal.x;
            normal_out.y = normal.y;
        }
    }

    intersected
}
pub fn kmRay2IntersectTriangle(
    ray: &KmRay2,
    p1: &KmVec2,
    p2: &KmVec2,
    p3: &KmVec2,
    intersection: Option<&mut KmVec2>,
    normal_out: Option<&mut KmVec2>,
    distance_out: Option<&mut f32>,
) -> u8 {
    let mut intersect = KmVec2 { x: 0.0, y: 0.0 };
    let mut final_intersect = KmVec2 { x: 0.0, y: 0.0 };
    let mut normal = KmVec2 { x: 0.0, y: 0.0 };
    let mut distance = 10000.0;
    let mut intersected = 0;

    // First edge (p1-p2)
    if kmRay2IntersectLineSegment(ray, p1, p2, Some(&mut intersect)) != 0 {
        let mut tmp = KmVec2 { x: 0.0, y: 0.0 };
        let this_distance = kmVec2Length(Some(kmVec2Subtract(&mut tmp, &intersect, &ray.start)));
        let mut this_normal = KmVec2 { x: 0.0, y: 0.0 };
        calculate_line_normal(p1.clone(), p2.clone(), p3.clone(), Some(&mut this_normal));

        if this_distance < distance && kmVec2Dot(Some(&this_normal), Some(&ray.dir)).unwrap_or(0.0) < 0.0 {
            final_intersect.x = intersect.x;
            final_intersect.y = intersect.y;
            distance = this_distance;
            kmVec2Assign(Some(&mut normal), Some(&this_normal));
            intersected = 1;
        }
    }

    // Second edge (p2-p3)
    if kmRay2IntersectLineSegment(ray, p2, p3, Some(&mut intersect)) != 0 {
        let mut tmp = KmVec2 { x: 0.0, y: 0.0 };
        let this_distance = kmVec2Length(Some(kmVec2Subtract(&mut tmp, &intersect, &ray.start)));
        let mut this_normal = KmVec2 { x: 0.0, y: 0.0 };
        calculate_line_normal(p2.clone(), p3.clone(), p1.clone(), Some(&mut this_normal));

        if this_distance < distance && kmVec2Dot(Some(&this_normal), Some(&ray.dir)).unwrap_or(0.0) < 0.0 {
            final_intersect.x = intersect.x;
            final_intersect.y = intersect.y;
            distance = this_distance;
            kmVec2Assign(Some(&mut normal), Some(&this_normal));
            intersected = 1;
        }
    }

    // Third edge (p3-p1)
    if kmRay2IntersectLineSegment(ray, p3, p1, Some(&mut intersect)) != 0 {
        let mut tmp = KmVec2 { x: 0.0, y: 0.0 };
        let this_distance = kmVec2Length(Some(kmVec2Subtract(&mut tmp, &intersect, &ray.start)));
        let mut this_normal = KmVec2 { x: 0.0, y: 0.0 };
        calculate_line_normal(p3.clone(), p1.clone(), p2.clone(), Some(&mut this_normal));

        if this_distance < distance && kmVec2Dot(Some(&this_normal), Some(&ray.dir)).unwrap_or(0.0) < 0.0 {
            final_intersect.x = intersect.x;
            final_intersect.y = intersect.y;
            distance = this_distance;
            kmVec2Assign(Some(&mut normal), Some(&this_normal));
            intersected = 1;
        }
    }

    if intersected != 0 {
        if let Some(intersection) = intersection {
            intersection.x = final_intersect.x;
            intersection.y = final_intersect.y;
        }

        if let Some(normal_out) = normal_out {
            normal_out.x = normal.x;
            normal_out.y = normal.y;
        }

        if let Some(distance_out) = distance_out {
            *distance_out = distance;
        }
    }

    intersected
}
