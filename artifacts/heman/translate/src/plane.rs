use crate::*;
use crate::KmPlane;
use crate::KmPointClassification;
use crate::KmVec3;
use std::f32;
use std::cmp::Ordering;

pub fn kmPlaneFill(plane: &mut KmPlane, a: f32, b: f32, c: f32, d: f32) -> &mut KmPlane {
    plane.a = a;
    plane.b = b;
    plane.c = c;
    plane.d = d;
    plane
}
pub fn kmPlaneScale<'a>(pOut: Option<&'a mut KmPlane>, pP: Option<&'a KmPlane>, s: f32) -> Option<&'a mut KmPlane> {
    // Use assert_eq! to match C's assert behavior (panic if condition fails)
    assert!(false, "Not implemented");
    Option::None
}
pub fn kmPlaneDot(pP: Option<&KmPlane>, pV: Option<&KmVec4>) -> Option<f32> {
    // Check for NULL pointers (None in Rust)
    if pP.is_none() || pV.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pP = pP.unwrap();
    let pV = pV.unwrap();

    // Perform the calculation as in C
    Some((pP.a * pV.x) + (pP.b * pV.y) + (pP.c * pV.z) + (pP.d * pV.w))
}
pub fn kmPlaneDotCoord(pP: Option<&KmPlane>, pV: Option<&KmVec3>) -> Option<f32> {
    // Check for NULL pointers (None in Rust)
    let pP = pP?;
    let pV = pV?;

    // Perform the calculation as in C
    Some((pP.a * pV.x) + (pP.b * pV.y) + (pP.c * pV.z) + pP.d)
}
pub fn kmPlaneDotNormal(pP: Option<&KmPlane>, pV: Option<&KmVec3>) -> Option<f32> {
    // Check for NULL pointers (None in Rust)
    if pP.is_none() || pV.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pP = pP.unwrap();
    let pV = pV.unwrap();

    // Perform the dot product calculation
    Some((pP.a * pV.x) + (pP.b * pV.y) + (pP.c * pV.z))
}
pub fn kmPlaneFromNormalAndDistance<'a>(
    plane: &'a mut KmPlane,
    normal: Option<&'a KmVec3>,
    dist: f32,
) -> Option<&'a mut KmPlane> {
    // Check for NULL equivalent (None in Rust)
    let normal = normal?;

    // Assign values to the plane
    plane.a = normal.x;
    plane.b = normal.y;
    plane.c = normal.z;
    plane.d = dist;

    Some(plane)
}
pub fn kmPlaneFromPointAndNormal<'a>(
    pOut: Option<&'a mut KmPlane>,
    pPoint: Option<&'a KmVec3>,
    pNormal: Option<&'a KmVec3>,
) -> Option<&'a mut KmPlane> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pPoint = pPoint?;
    let pNormal = pNormal?;

    pOut.a = pNormal.x;
    pOut.b = pNormal.y;
    pOut.c = pNormal.z;
    pOut.d = -kmVec3Dot(Some(pNormal), Some(pPoint))?;

    Some(pOut)
}

pub fn kmPlaneClassifyPoint(pIn: Option<&KmPlane>, pP: Option<&KmVec3>) -> KmPointClassification {
    // Check for NULL pointers (None in Rust)
    if pIn.is_none() || pP.is_none() {
        return KmPointClassification::POINT_ON_PLANE; // Default behavior when inputs are invalid
    }

    // Unwrap safely since we've checked for None
    let pIn = pIn.unwrap();
    let pP = pP.unwrap();

    // Calculate distance using the plane equation
    let distance = ((pIn.a * pP.x) + (pIn.b * pP.y) + (pIn.c * pP.z)) + pIn.d;

    // Classify the point based on distance
    if distance > 0.0001 {
        KmPointClassification::POINT_INFRONT_OF_PLANE
    } else if distance < -0.0001 {
        KmPointClassification::POINT_BEHIND_PLANE
    } else {
        KmPointClassification::POINT_ON_PLANE
    }
}
pub fn kmPlaneNormalize<'a>(pOut: Option<&'a mut KmPlane>, pP: Option<&'a KmPlane>) -> Option<&'a mut KmPlane> {
    // Check if either input is None (equivalent to NULL check in C)
    let pOut = pOut?;
    let pP = pP?;

    // Check if all components are zero (lines 5-12 in C)
    if (pP.a == 0.0) && (pP.b == 0.0) && (pP.c == 0.0) {
        pOut.a = pP.a;
        pOut.b = pP.b;
        pOut.c = pP.c;
        pOut.d = pP.d;
        return Some(pOut);
    }

    // Create normalized vector (lines 13-21 in C)
    let mut n = KmVec3 {
        x: pP.a,
        y: pP.b,
        z: pP.c,
    };

    // First calculate length with immutable reference
    let length = kmVec3Length(Some(&n)).max(f32::EPSILON);
    let l = 1.0f32 / length; // Avoid division by zero
    
    // Then normalize with mutable reference
    kmVec3Normalize(Some(&mut n), None);

    pOut.a = n.x;
    pOut.b = n.y;
    pOut.c = n.z;
    pOut.d = pP.d * l;

    Some(pOut)
}
pub fn kmPlaneExtractFromMat4<'a>(pOut: Option<&'a mut KmPlane>, pIn: Option<&'a KmMat4>, row: i32) -> Option<&'a mut KmPlane> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pIn = pIn?;

    let scale = match row.cmp(&0) {
        Ordering::Less => -1.0,
        _ => 1.0,
    };
    let row = row.abs() - 1;

    // Calculate plane coefficients
    pOut.a = pIn.mat[3] + (scale * pIn.mat[row as usize]);
    pOut.b = pIn.mat[7] + (scale * pIn.mat[(row + 4) as usize]);
    pOut.c = pIn.mat[11] + (scale * pIn.mat[(row + 8) as usize]);
    pOut.d = pIn.mat[15] + (scale * pIn.mat[(row + 12) as usize]);

    // Normalize the plane and return the result
    kmPlaneNormalize(Some(pOut), None)
}
pub fn kmPlaneIntersectLine<'a>(
    pOut: Option<&'a mut KmVec3>,
    pP: Option<&'a KmPlane>,
    pV1: Option<&'a KmVec3>,
    pV2: Option<&'a KmVec3>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pP.is_none() || pV1.is_none() || pV2.is_none() {
        return pOut;
    }

    // Unwrap all Option references safely
    let pOut = pOut.unwrap();
    let pP = pP.unwrap();
    let pV1 = pV1.unwrap();
    let pV2 = pV2.unwrap();

    let mut d = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    kmVec3Subtract(&mut d, pV2, pV1);

    let n = KmVec3 {
        x: pP.a,
        y: pP.b,
        z: pP.c,
    };
    let mut normalized_n = n.clone();
    kmVec3Normalize(Some(&mut normalized_n), Some(&n));

    let nt = -((normalized_n.x * pV1.x + normalized_n.y * pV1.y + normalized_n.z * pV1.z) + pP.d);
    let dt = normalized_n.x * d.x + normalized_n.y * d.y + normalized_n.z * d.z;

    if f32::abs(dt) < 0.0001 {
        return Some(pOut);
    }

    let t = nt / dt;
    pOut.x = pV1.x + d.x * t;
    pOut.y = pV1.y + d.y * t;
    pOut.z = pV1.z + d.z * t;

    Some(pOut)
}
pub fn kmPlaneFromPoints<'a>(pOut: &'a mut KmPlane, p1: Option<&KmVec3>, p2: Option<&KmVec3>, p3: Option<&KmVec3>) -> Option<&'a mut KmPlane> {
    // Check for NULL pointers (None in Rust)
    if p1.is_none() || p2.is_none() || p3.is_none() {
        return Option::None;
    }

    // Unwrap the options safely
    let p1 = p1.unwrap();
    let p2 = p2.unwrap();
    let p3 = p3.unwrap();

    let mut n = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut v1 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut v2 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };

    // Calculate v1 = p2 - p1
    kmVec3Subtract(&mut v1, p2, p1);
    // Calculate v2 = p3 - p1
    kmVec3Subtract(&mut v2, p3, p1);
    // Calculate n = v1 x v2 (cross product)
    kmVec3Cross(&mut n, &v1, &v2);
    
    // Create a temporary copy of n for normalization
    let n_copy = n.clone();
    // Normalize n using the copy
    kmVec3Normalize(Some(&mut n), Some(&n_copy));

    // Set plane coefficients
    pOut.a = n.x;
    pOut.b = n.y;
    pOut.c = n.z;

    // Calculate d = -n · p1
    let mut scaled_n = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    kmVec3Scale(&mut scaled_n, &n, -1.0);
    pOut.d = kmVec3Dot(Some(&scaled_n), Some(p1)).unwrap_or(0.0);

    Some(pOut)
}
pub fn kmPlaneGetIntersection<'a>(
    pOut: &'a mut KmVec3,
    p1: &KmPlane,
    p2: &KmPlane,
    p3: &KmPlane,
) -> Option<&'a mut KmVec3> {
    let mut n1 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut n2 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut n3 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut cross = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut r1 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut r2 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut r3 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    
    kmVec3Fill(&mut n1, p1.a, p1.b, p1.c);
    kmVec3Fill(&mut n2, p2.a, p2.b, p2.c);
    kmVec3Fill(&mut n3, p3.a, p3.b, p3.c);
    
    kmVec3Cross(&mut cross, &n2, &n3);
    let denom = kmVec3Dot(Some(&n1), Some(&cross)).unwrap_or(0.0);
    
    if kmAlmostEqual(denom, 0.0) != 0 {
        return Option::None;
    }
    
    // Calculate r1, r2, r3 with temporary variables to avoid multiple mutable borrows
    let temp_r1 = {
        let mut temp = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        kmVec3Cross(&mut temp, &n2, &n3);
        temp
    };
    kmVec3Scale(&mut r1, &temp_r1, -p1.d);
    
    let temp_r2 = {
        let mut temp = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        kmVec3Cross(&mut temp, &n3, &n1);
        temp
    };
    kmVec3Scale(&mut r2, &temp_r2, p2.d);
    
    let temp_r3 = {
        let mut temp = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        kmVec3Cross(&mut temp, &n1, &n2);
        temp
    };
    kmVec3Scale(&mut r3, &temp_r3, p3.d);
    
    // First subtraction
    kmVec3Subtract(pOut, &r1, &r2);
    
    // Create a temporary copy for scaling
    let mut temp = pOut.clone();
    kmVec3Scale(&mut temp, pOut, 1.0 / denom);
    
    // Final subtraction
    kmVec3Subtract(pOut, &temp, &r3);
    
    Some(pOut)
}
