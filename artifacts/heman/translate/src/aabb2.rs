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
pub fn kmAABB2ContainsPoint(pBox: &KmAabb2, pPoint: &KmVec2) -> bool {
    ((pPoint.x >= pBox.min.x) && (pPoint.x <= pBox.max.x)) && 
    ((pPoint.y >= pBox.min.y) && (pPoint.y <= pBox.max.y))
}
pub fn kmAABB2Assign<'a>(pOut: Option<&'a mut KmAabb2>, pIn: Option<&'a KmAabb2>) -> Option<&'a mut KmAabb2> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Assign min and max vectors
    kmVec2Assign(Some(&mut pOut.min), Some(&pIn.min));
    kmVec2Assign(Some(&mut pOut.max), Some(&pIn.max));

    Some(pOut)
}
pub fn kmAABB2Scale<'a>(pOut: &'a mut KmAabb2, pIn: &'a KmAabb2, s: f32) -> &'a mut KmAabb2 {
    {
        let max = &mut pOut.max;
        kmVec2Scale(max, &pIn.max, s);
    }
    {
        let min = &mut pOut.min;
        kmVec2Scale(min, &pIn.min, s);
    }
    pOut
}
pub fn kmAABB2ExpandToContain<'a>(
    pOut: Option<&'a mut KmAabb2>,
    pIn: Option<&'a KmAabb2>,
    other: Option<&'a KmAabb2>,
) -> Option<&'a mut KmAabb2> {
    // Check for None values (equivalent to NULL checks in C)
    if pIn.is_none() || other.is_none() {
        return Option::None;
    }

    // Unwrap safely since we've checked for None
    let pIn = pIn.unwrap();
    let other = other.unwrap();

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

    // Assign the result to pOut and return it
    if let Some(out) = pOut {
        *out = result.clone();
        Some(out)
    } else {
        Option::None
    }
}
pub fn kmAABB2Initialize<'a>(
    pBox: Option<&'a mut KmAabb2>,
    centre: Option<&KmVec2>,
    width: f32,
    height: f32,
    _depth: f32,  // Note: depth is unused in the original C code
) -> Option<&'a mut KmAabb2> {
    // Check for NULL pBox (translated to Option)
    let pBox = pBox?;

    // Handle centre pointer (translated to Option)
    let point = match centre {
        Some(centre) => KmVec2 {
            x: centre.x,
            y: centre.y,
        },
        None => {
            let mut origin = KmVec2 { x: 0.0, y: 0.0 };
            kmVec2Fill(&mut origin, 0.0, 0.0);
            origin
        }
    };

    // Calculate bounds
    pBox.min.x = point.x - (width / 2.0);
    pBox.min.y = point.y - (height / 2.0);
    pBox.max.x = point.x + (width / 2.0);
    pBox.max.y = point.y + (height / 2.0);

    Some(pBox)
}
pub fn kmAABB2Translate<'a>(
    pOut: &'a mut KmAabb2,
    pIn: &KmAabb2,
    translation: &KmVec2,
) -> &'a mut KmAabb2 {
    {
        let min_out = &mut pOut.min;
        kmVec2Add(min_out, &pIn.min, translation);
    }
    {
        let max_out = &mut pOut.max;
        kmVec2Add(max_out, &pIn.max, translation);
    }
    pOut
}
pub fn kmAABB2ScaleWithPivot<'a>(
    pOut: &'a mut KmAabb2,
    pIn: &'a KmAabb2,
    pivot: &KmVec2,
    s: f32,
) -> &'a mut KmAabb2 {
    let translate = KmVec2 {
        x: -pivot.x,
        y: -pivot.y,
    };
    
    // First translation
    let pOut = kmAABB2Translate(pOut, pIn, &translate);
    
    // Scaling
    let pOut = kmAABB2Scale(pOut, pIn, s);
    
    // Second translation
    kmAABB2Translate(pOut, pIn, pivot)
}
pub fn kmAABB2ContainsAABB(container: &KmAabb2, to_check: &KmAabb2) -> u32 {
    let mut corners = [
        KmVec2 { x: 0.0, y: 0.0 },
        KmVec2 { x: 0.0, y: 0.0 },
        KmVec2 { x: 0.0, y: 0.0 },
        KmVec2 { x: 0.0, y: 0.0 },
    ];
    
    {
        let corner = &mut corners[0];
        kmVec2Fill(corner, to_check.min.x, to_check.min.y);
    }
    {
        let corner = &mut corners[1];
        kmVec2Fill(corner, to_check.max.x, to_check.min.y);
    }
    {
        let corner = &mut corners[2];
        kmVec2Fill(corner, to_check.max.x, to_check.max.y);
    }
    {
        let corner = &mut corners[3];
        kmVec2Fill(corner, to_check.min.x, to_check.max.y);
    }

    let n_contains = kmAABB2ContainsPoint(container, &corners[0]) as u32
        + kmAABB2ContainsPoint(container, &corners[1]) as u32
        + kmAABB2ContainsPoint(container, &corners[2]) as u32
        + kmAABB2ContainsPoint(container, &corners[3]) as u32;

    match n_contains {
        0 => 0,
        1..=3 => 1,
        _ => 2,
    }
}
pub fn kmAABB2Centre<'a>(aabb: &KmAabb2, pOut: &'a mut KmVec2) -> &'a mut KmVec2 {
    let mut temp = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Add(&mut temp, &aabb.min, &aabb.max);
    kmVec2Scale(pOut, &temp, 0.5);
    pOut
}
