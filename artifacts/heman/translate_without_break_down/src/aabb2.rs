use crate::*;

pub fn kmAABB2Sanitize<'a>(pOut: &'a mut KmAabb2, pIn: &KmAabb2) -> &'a mut KmAabb2 {
    // Handle x coordinates
    if pIn.min.x <= pIn.max.x {
        pOut.min.x = pIn.min.x;
        pOut.max.x = pIn.max.x;
    } else {
        pOut.min.x = pIn.max.x;
        pOut.max.x = pIn.min.x;
    }

    // Handle y coordinates
    if pIn.min.y <= pIn.max.y {
        pOut.min.y = pIn.min.y;
        pOut.max.y = pIn.max.y;
    } else {
        pOut.min.y = pIn.max.y;
        pOut.max.y = pIn.min.y;
    }

    pOut
}
pub fn kmAABB2DiameterX(aabb: &KmAabb2) -> f32 {
    aabb.max.x - aabb.min.x
}
pub fn kmAABB2DiameterY(aabb: &KmAabb2) -> f32 {
    aabb.max.y - aabb.min.y
}
pub fn kmAABB2ContainsPoint(pBox: &KmAabb2, pPoint: &KmVec2) -> i32 {
    if ((pPoint.x >= pBox.min.x) && (pPoint.x <= pBox.max.x)) && 
       ((pPoint.y >= pBox.min.y) && (pPoint.y <= pBox.max.y)) {
        1
    } else {
        0
    }
}
pub fn kmAABB2Assign<'a>(pOut: Option<&'a mut KmAabb2>, pIn: Option<&'a KmAabb2>) -> Option<&'a mut KmAabb2> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Assign min and max vectors using kmVec2Assign
    // Note: We use separate blocks to avoid overlapping mutable borrows
    {
        let min_out = Some(&mut pOut.min);
        let min_in = Some(&pIn.min);
        kmVec2Assign(min_out, min_in);
    }

    {
        let max_out = Some(&mut pOut.max);
        let max_in = Some(&pIn.max);
        kmVec2Assign(max_out, max_in);
    }

    Some(pOut)
}
pub fn kmAABB2Scale<'a>(pOut: &'a mut KmAabb2, pIn: &KmAabb2, s: f32) -> &'a mut KmAabb2 {
    kmVec2Scale(&mut pOut.max, &pIn.max, s);
    kmVec2Scale(&mut pOut.min, &pIn.min, s);
    pOut
}
pub fn kmAABB2ExpandToContain<'a>(
    pOut: Option<&'a mut KmAabb2>,
    pIn: Option<&'a KmAabb2>,
    other: Option<&'a KmAabb2>,
) -> Option<&'a mut KmAabb2> {
    // Check for None values (equivalent to NULL checks in C)
    let pIn = pIn?;
    let other = other?;

    // Calculate the expanded AABB
    let result = KmAabb2 {
        min: KmVec2 {
            x: pIn.min.x.min(other.min.x),
            y: pIn.min.y.min(other.min.y),
        },
        max: KmVec2 {
            x: pIn.max.x.max(other.max.x),
            y: pIn.max.y.max(other.max.y),
        },
    };

    // If pOut is Some, modify it directly and return it
    if let Some(out) = pOut {
        *out = result;
        Some(out)
    } else {
        None
    }
}
pub fn kmAABB2Initialize<'a>(
    pBox: Option<&'a mut KmAabb2>,
    centre: Option<&'a KmVec2>,
    width: f32,
    height: f32,
    _depth: f32, // Note: depth is unused in the original C code
) -> Option<&'a mut KmAabb2> {
    // Check for NULL pointer (None in Rust)
    let pBox = match pBox {
        Some(b) => b,
        None => return None,
    };

    // Handle centre pointer (None becomes default origin)
    let point = match centre {
        Some(c) => c,
        None => {
            pBox.min.x = -width / 2.0;
            pBox.min.y = -height / 2.0;
            pBox.max.x = width / 2.0;
            pBox.max.y = height / 2.0;
            return Some(pBox);
        }
    };

    // Calculate min and max coordinates
    pBox.min.x = point.x - (width / 2.0);
    pBox.min.y = point.y - (height / 2.0);
    pBox.max.x = point.x + (width / 2.0);
    pBox.max.y = point.y + (height / 2.0);

    Some(pBox)
}
pub fn kmAABB2Translate<'a>(pOut: Option<&'a mut KmAabb2>, pIn: Option<&'a KmAabb2>, translation: Option<&'a KmVec2>) -> Option<&'a mut KmAabb2> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() || translation.is_none() {
        return None;
    }

    // Unwrap the Options safely since we've checked they're Some
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();
    let translation = translation.unwrap();

    // Use separate blocks to avoid overlapping mutable borrows
    {
        let min_out = &mut pOut.min;
        let min_in = &pIn.min;
        kmVec2Add(min_out, min_in, translation);
    }

    {
        let max_out = &mut pOut.max;
        let max_in = &pIn.max;
        kmVec2Add(max_out, max_in, translation);
    }

    Some(pOut)
}
pub fn kmAABB2ScaleWithPivot<'a>(
    pOut: Option<&'a mut KmAabb2>,
    pIn: Option<&'a KmAabb2>,
    pivot: Option<&'a KmVec2>,
    s: f32,
) -> Option<&'a mut KmAabb2> {
    // Check for None values (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() || pivot.is_none() {
        return None;
    }

    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();
    let pivot = pivot.unwrap();

    // Create translation vector (equivalent to C lines 3-5)
    let translate = KmVec2 {
        x: -pivot.x,
        y: -pivot.y,
    };

    // First translation (equivalent to C line 6)
    kmAABB2Translate(Some(pOut), Some(pIn), Some(&translate));

    // Scaling (equivalent to C line 7)
    kmAABB2Scale(pOut, pIn, s);

    // Second translation (equivalent to C line 8)
    kmAABB2Translate(Some(pOut), Some(pIn), Some(pivot));

    Some(pOut) // Return pOut (equivalent to C line 9)
}
pub fn kmAABB2ContainsAABB(container: &KmAabb2, to_check: &KmAabb2) -> u32 {
    let mut corners: [KmVec2; 4] = [
        KmVec2 { x: 0.0, y: 0.0 },
        KmVec2 { x: 0.0, y: 0.0 },
        KmVec2 { x: 0.0, y: 0.0 },
        KmVec2 { x: 0.0, y: 0.0 },
    ];

    kmVec2Fill(&mut corners[0], to_check.min.x, to_check.min.y);
    kmVec2Fill(&mut corners[1], to_check.max.x, to_check.min.y);
    kmVec2Fill(&mut corners[2], to_check.max.x, to_check.max.y);
    kmVec2Fill(&mut corners[3], to_check.min.x, to_check.max.y);

    let nContains = kmAABB2ContainsPoint(container, &corners[0]) 
        + kmAABB2ContainsPoint(container, &corners[1]) 
        + kmAABB2ContainsPoint(container, &corners[2]) 
        + kmAABB2ContainsPoint(container, &corners[3]);

    match nContains {
        0 => 0,
        1..=3 => 1,
        _ => 2,
    }
}
pub fn kmAABB2Centre<'a>(aabb: &'a KmAabb2, pOut: &'a mut KmVec2) -> &'a mut KmVec2 {
    let mut temp = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Add(&mut temp, &aabb.min, &aabb.max);
    kmVec2Scale(pOut, &temp, 0.5);
    pOut
}
