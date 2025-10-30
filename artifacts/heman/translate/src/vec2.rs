use crate::*;
use std::assert;
use std::f32;
use std::f32::consts::PI;

pub fn kmVec2Fill(pOut: &mut KmVec2, x: f32, y: f32) -> &mut KmVec2 {
    pOut.x = x;
    pOut.y = y;
    pOut
}
pub fn kmVec2Lerp<'a>(pOut: &'a mut KmVec2, pV1: &KmVec2, pV2: &KmVec2, t: f32) -> &'a mut KmVec2 {
    pOut.x = pV1.x + (t * (pV2.x - pV1.x));
    pOut.y = pV1.y + (t * (pV2.y - pV1.y));
    pOut
}
pub fn kmVec2Add<'a>(pOut: &'a mut KmVec2, pV1: &KmVec2, pV2: &KmVec2) -> &'a mut KmVec2 {
    pOut.x = pV1.x + pV2.x;
    pOut.y = pV1.y + pV2.y;
    pOut
}
pub fn kmVec2Dot(pV1: Option<&KmVec2>, pV2: Option<&KmVec2>) -> Option<f32> {
    // Check for NULL pointers (None in Rust)
    if pV1.is_none() || pV2.is_none() {
        return None;
    }

    // Safe unwrap since we checked for None
    let pV1 = pV1.unwrap();
    let pV2 = pV2.unwrap();

    Some((pV1.x * pV2.x) + (pV1.y * pV2.y))
}
pub fn kmVec2Cross(pV1: Option<&KmVec2>, pV2: Option<&KmVec2>) -> Option<f32> {
    // Check for NULL pointers (None in Rust)
    if pV1.is_none() || pV2.is_none() {
        return None;
    }

    // Safe unwrap since we checked for None
    let pV1 = pV1.unwrap();
    let pV2 = pV2.unwrap();

    Some((pV1.x * pV2.y) - (pV1.y * pV2.x))
}
pub fn kmVec2Subtract<'a>(pOut: &'a mut KmVec2, pV1: &KmVec2, pV2: &KmVec2) -> &'a mut KmVec2 {
    pOut.x = pV1.x - pV2.x;
    pOut.y = pV1.y - pV2.y;
    pOut
}
pub fn kmVec2Mul<'a>(pOut: &'a mut KmVec2, pV1: &KmVec2, pV2: &KmVec2) -> &'a mut KmVec2 {
    pOut.x = pV1.x * pV2.x;
    pOut.y = pV1.y * pV2.y;
    pOut
}
pub fn kmVec2Div<'a>(pOut: &'a mut KmVec2, pV1: &KmVec2, pV2: &KmVec2) -> Option<&'a mut KmVec2> {
    if pV2.x != 0.0 && pV2.y != 0.0 {
        pOut.x = pV1.x / pV2.x;
        pOut.y = pV1.y / pV2.y;
        Some(pOut)
    } else {
        Option::None
    }
}
pub fn kmVec2Scale<'a>(pOut: &'a mut KmVec2, pIn: &'a KmVec2, s: f32) -> &'a mut KmVec2 {
    pOut.x = pIn.x * s;
    pOut.y = pIn.y * s;
    pOut
}
pub fn kmVec2AreEqual(p1: &KmVec2, p2: &KmVec2) -> bool {
    ((p1.x < (p2.x + 0.0001)) && (p1.x > (p2.x - 0.0001))) && 
    ((p1.y < (p2.y + 0.0001)) && (p1.y > (p2.y - 0.0001)))
}
pub fn kmVec2Assign<'a>(pOut: Option<&'a mut KmVec2>, pIn: Option<&'a KmVec2>) -> Option<&'a mut KmVec2> {
    // Check if either input is None (equivalent to NULL check in C)
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap the Options safely
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Check if they point to the same memory (Rust references can't alias, so we compare addresses)
    if std::ptr::eq(pOut, pIn) {
        return Some(pOut);
    }

    // Assign values
    pOut.x = pIn.x;
    pOut.y = pIn.y;

    Some(pOut)
}

pub fn kmVec2Length(pIn: Option<&KmVec2>) -> f32 {
    // Check for NULL pointer (None in Rust)
    match pIn {
        Some(vec) => {
            // Calculate the length using sqrtf (std::f32::sqrt in Rust)
            f32::sqrt(kmSQR(vec.x) + kmSQR(vec.y))
        }
        None => {
            // Return NaN for NULL input (matches C behavior for invalid input)
            f32::NAN
        }
    }
}
pub fn kmVec2LengthSq(pIn: Option<&KmVec2>) -> f32 {
    match pIn {
        Some(vec) => kmSQR(vec.x) + kmSQR(vec.y),
        None => 0.0, // Default behavior when NULL is passed
    }
}
pub fn kmVec2Transform<'a>(pOut: Option<&'a mut KmVec2>, pV: Option<&KmVec2>, pM: Option<&KmMat3>) -> Option<&'a mut KmVec2> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pV = pV?;
    let pM = pM?;

    // Calculate the transformed vector
    let v = KmVec2 {
        x: (pV.x * pM.mat[0] + pV.y * pM.mat[3]) + pM.mat[6],
        y: (pV.x * pM.mat[1] + pV.y * pM.mat[4]) + pM.mat[7],
    };

    // Update pOut
    pOut.x = v.x;
    pOut.y = v.y;

    Some(pOut)
}
pub fn kmVec2TransformCoord<'a>(pOut: Option<&'a mut KmVec2>, pV: Option<&'a KmVec2>, pM: Option<&'a KmMat3>) -> Option<&'a mut KmVec2> {
    assert!(false, "Function not implemented");
    Option::None
}
pub fn kmVec2RotateBy<'a>(
    pOut: Option<&'a mut KmVec2>,
    pIn: Option<&'a KmVec2>,
    degrees: f32,
    center: Option<&'a KmVec2>,
) -> Option<&'a mut KmVec2> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() || center.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();
    let center = center.unwrap();

    let radians = kmDegreesToRadians(degrees);
    let cs = radians.cos(); // Equivalent to cosf in Rust
    let sn = radians.sin(); // Equivalent to sinf in Rust

    // Calculate relative position
    pOut.x = pIn.x - center.x;
    pOut.y = pIn.y - center.y;

    // Perform rotation
    let x = (pOut.x * cs) - (pOut.y * sn);
    let y = (pOut.x * sn) + (pOut.y * cs);

    // Translate back
    pOut.x = x + center.x;
    pOut.y = y + center.y;

    Some(pOut)
}
pub fn kmVec2MidPointBetween<'a>(pOut: &'a mut KmVec2, v1: &KmVec2, v2: &KmVec2) -> &'a mut KmVec2 {
    let mut sum = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Add(&mut sum, v1, v2);
    pOut.x = sum.x / 2.0;
    pOut.y = sum.y / 2.0;
    pOut
}

pub fn kmVec2Normalize<'a>(
    pOut: Option<&'a mut KmVec2>,
    pIn: Option<&'a KmVec2>,
) -> Option<&'a mut KmVec2> {
    // Check if either input is None
    if pOut.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap safely since we checked for None
    let pIn = pIn.unwrap();
    let pOut = pOut.unwrap();

    // Check if both components are zero
    if (pIn.x == 0.0) && (pIn.y == 0.0) {
        return kmVec2Assign(Some(pOut), Some(pIn));
    }

    let l = 1.0f32 / kmVec2Length(Some(pIn));
    let v = KmVec2 {
        x: pIn.x * l,
        y: pIn.y * l,
    };

    pOut.x = v.x;
    pOut.y = v.y;

    Some(pOut)
}

pub fn kmVec2DistanceBetween(v1: Option<&KmVec2>, v2: Option<&KmVec2>) -> f32 {
    // Check for None (equivalent to NULL checks in C)
    if v1.is_none() || v2.is_none() {
        return f32::NAN; // Return NaN for invalid input (common practice in Rust for invalid float operations)
    }

    // Unwrap safely since we've checked for None
    let v1 = v1.unwrap();
    let v2 = v2.unwrap();

    let mut diff = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Subtract(&mut diff, v2, v1);
    f32::abs(kmVec2Length(Some(&diff)))
}
pub fn kmVec2Reflect<'a>(
    pOut: &'a mut KmVec2,
    pIn: Option<&KmVec2>,
    normal: Option<&KmVec2>,
) -> Option<&'a mut KmVec2> {
    // Check for None (equivalent to NULL checks in C)
    let pIn = pIn?;
    let normal = normal?;

    let dot_product = kmVec2Dot(Some(pIn), Some(normal))?;
    let scale_factor = 2.0f32 * dot_product;

    let mut tmp = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Scale(&mut tmp, normal, scale_factor);
    Some(kmVec2Subtract(pOut, pIn, &tmp))
}

pub fn kmVec2DegreesBetween(v1: Option<&KmVec2>, v2: Option<&KmVec2>) -> Option<f32> {
    // Check if vectors are equal first
    if kmVec2AreEqual(v1?, v2?) {
        return Some(0.0);
    }

    // Create normalized vectors
    let mut t1 = KmVec2 { x: 0.0, y: 0.0 };
    let mut t2 = KmVec2 { x: 0.0, y: 0.0 };
    
    // Normalize input vectors
    kmVec2Normalize(Some(&mut t1), v1)?;
    kmVec2Normalize(Some(&mut t2), v2)?;

    // Calculate cross and dot products
    let cross = kmVec2Cross(Some(&t1), Some(&t2))?;
    let mut dot = kmVec2Dot(Some(&t1), Some(&t2))?;

    // Clamp dot product between -1.0 and 1.0
    dot = dot.clamp(-1.0, 1.0);

    // Calculate angle in degrees
    Some(kmRadiansToDegrees(f32::atan2(cross, dot)))
}
