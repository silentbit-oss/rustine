use crate::*;
use std::assert;
use std::f32;

pub fn kmAABB3Scale<'a>(pOut: Option<&'a mut KmAabb3>, pIn: Option<&'a KmAabb3>, s: f32) -> Option<&'a mut KmAabb3> {
    // Use assert_eq! with a custom message to match C's assert behavior
    assert!(false, "Not implemented");
    
    // Return pOut as is (matching C behavior)
    pOut
}

pub fn kmAABB3DiameterX(aabb: Option<&KmAabb3>) -> f32 {
    // Check if the input is None (equivalent to NULL check in C)
    if aabb.is_none() {
        return 0.0; // Return 0.0 as a safe default for invalid input
    }

    let aabb = aabb.unwrap(); // Safe unwrap after checking
    f32::abs(aabb.max.x - aabb.min.x)
}

pub fn kmAABB3DiameterY(aabb: &KmAabb3) -> f32 {
    f32::abs(aabb.max.y - aabb.min.y)
}

pub fn kmAABB3DiameterZ(aabb: &KmAabb3) -> f32 {
    f32::abs(aabb.max.z - aabb.min.z)
}
pub fn kmAABB3ContainsPoint(pBox: &KmAabb3, pPoint: &KmVec3) -> bool {
    (pPoint.x >= pBox.min.x && pPoint.x <= pBox.max.x) &&
    (pPoint.y >= pBox.min.y && pPoint.y <= pBox.max.y) &&
    (pPoint.z >= pBox.min.z && pPoint.z <= pBox.max.z)
}
pub fn kmAABB3Assign<'a>(pOut: Option<&'a mut KmAabb3>, pIn: Option<&'a KmAabb3>) -> Option<&'a mut KmAabb3> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Assign min and max vectors
    kmVec3Assign(Some(&mut pOut.min), Some(&pIn.min));
    kmVec3Assign(Some(&mut pOut.max), Some(&pIn.max));

    Some(pOut)
}

pub fn km_aabb3_intersects_triangle(
    box_: &KmAabb3,
    p1: &KmVec3,
    p2: &KmVec3,
    p3: &KmVec3,
) -> u8 {
    assert!(false, "Not implemented");
    1
}
pub fn kmAABB3ContainsAABB(container: &KmAabb3, to_check: &KmAabb3) -> u32 {
    let mut corners: [KmVec3; 8] = [
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
        KmVec3 { x: 0.0, y: 0.0, z: 0.0 },
    ];

    let mut result: u32 = 2;
    let mut found: bool = false;

    // Fill the corners array
    kmVec3Fill(&mut corners[0], to_check.min.x, to_check.min.y, to_check.min.z);
    kmVec3Fill(&mut corners[1], to_check.max.x, to_check.min.y, to_check.min.z);
    kmVec3Fill(&mut corners[2], to_check.max.x, to_check.max.y, to_check.min.z);
    kmVec3Fill(&mut corners[3], to_check.min.x, to_check.max.y, to_check.min.z);
    kmVec3Fill(&mut corners[4], to_check.min.x, to_check.min.y, to_check.max.z);
    kmVec3Fill(&mut corners[5], to_check.max.x, to_check.min.y, to_check.max.z);
    kmVec3Fill(&mut corners[6], to_check.max.x, to_check.max.y, to_check.max.z);
    kmVec3Fill(&mut corners[7], to_check.min.x, to_check.max.y, to_check.max.z);

    for i in 0..8 {
        if !kmAABB3ContainsPoint(container, &corners[i]) {
            result = 1;
            if found {
                return result;
            }
        } else {
            found = true;
        }
    }

    if !found {
        result = 0;
    }

    result
}
pub fn kmAABB3IntersectsAABB(box_: &KmAabb3, other: &KmAabb3) -> u8 {
    (kmAABB3ContainsAABB(box_, other) != 0) as u8
}
pub fn kmAABB3ExpandToContain<'a>(
    mut pOut: Option<&'a mut KmAabb3>,
    pIn: Option<&'a KmAabb3>,
    other: Option<&'a KmAabb3>,
) -> Option<&'a mut KmAabb3> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() || other.is_none() {
        return Option::None;
    }

    // Borrow the contents instead of moving them
    let p_out = pOut.as_mut().unwrap();
    let p_in = pIn.unwrap();
    let other = other.unwrap();

    // Modify pOut directly instead of creating a new KmAabb3
    p_out.min.x = p_in.min.x.min(other.min.x);
    p_out.min.y = p_in.min.y.min(other.min.y);
    p_out.min.z = p_in.min.z.min(other.min.z);
    p_out.max.x = p_in.max.x.max(other.max.x);
    p_out.max.y = p_in.max.y.max(other.max.y);
    p_out.max.z = p_in.max.z.max(other.max.z);

    pOut
}
pub fn kmAABB3Initialize<'a>(
    pBox: Option<&'a mut KmAabb3>,
    centre: Option<&'a KmVec3>,
    width: f32,
    height: f32,
    depth: f32,
) -> Option<&'a mut KmAabb3> {
    // Check if pBox is None (equivalent to NULL check in C)
    let pBox = pBox?;

    // Create a default origin point and zero it
    let mut origin = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    kmVec3Zero(Some(&mut origin));

    // Use the provided centre or fall back to the zeroed origin
    let point = centre.unwrap_or(&origin);

    // Calculate min and max coordinates
    pBox.min.x = point.x - (width / 2.0);
    pBox.min.y = point.y - (height / 2.0);
    pBox.min.z = point.z - (depth / 2.0);
    pBox.max.x = point.x + (width / 2.0);
    pBox.max.y = point.y + (height / 2.0);
    pBox.max.z = point.z + (depth / 2.0);

    Some(pBox)
}
pub fn kmAABB3Centre<'a>(aabb: &KmAabb3, pOut: &'a mut KmVec3) -> &'a mut KmVec3 {
    kmVec3Add(pOut, &aabb.min, &aabb.max);
    let temp = pOut.clone();
    kmVec3Scale(pOut, &temp, 0.5);
    pOut
}
