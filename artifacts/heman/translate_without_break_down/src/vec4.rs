use crate::*;
use std::assert;
use rand::Rng;

pub fn kmVec4Fill(pOut: &mut KmVec4, x: f32, y: f32, z: f32, w: f32) -> &mut KmVec4 {
    pOut.x = x;
    pOut.y = y;
    pOut.z = z;
    pOut.w = w;
    pOut
}
pub fn kmVec4Add<'a>(pOut: &'a mut KmVec4, pV1: &KmVec4, pV2: &KmVec4) -> &'a mut KmVec4 {
    pOut.x = pV1.x + pV2.x;
    pOut.y = pV1.y + pV2.y;
    pOut.z = pV1.z + pV2.z;
    pOut.w = pV1.w + pV2.w;
    pOut
}
pub fn kmVec4Dot(pV1: Option<&KmVec4>, pV2: Option<&KmVec4>) -> Option<f32> {
    // Check for NULL pointers (None in Rust)
    if pV1.is_none() || pV2.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pV1 = pV1.unwrap();
    let pV2 = pV2.unwrap();

    // Calculate the dot product
    Some(
        ((pV1.x * pV2.x) + (pV1.y * pV2.y)) + (pV1.z * pV2.z) + (pV1.w * pV2.w)
    )
}
pub fn kmVec4Lerp<'a>(pOut: &'a mut KmVec4, pV1: &KmVec4, pV2: &KmVec4, t: f32) -> &'a mut KmVec4 {
    pOut.x = pV1.x + (t * (pV2.x - pV1.x));
    pOut.y = pV1.y + (t * (pV2.y - pV1.y));
    pOut.z = pV1.z + (t * (pV2.z - pV1.z));
    pOut.w = pV1.w + (t * (pV2.w - pV1.w));
    pOut
}
pub fn kmVec4Subtract<'a>(pOut: &'a mut KmVec4, pV1: &KmVec4, pV2: &KmVec4) -> &'a mut KmVec4 {
    pOut.x = pV1.x - pV2.x;
    pOut.y = pV1.y - pV2.y;
    pOut.z = pV1.z - pV2.z;
    pOut.w = pV1.w - pV2.w;
    pOut
}
pub fn kmVec4Mul<'a>(pOut: &'a mut KmVec4, pV1: &KmVec4, pV2: &KmVec4) -> &'a mut KmVec4 {
    pOut.x = pV1.x * pV2.x;
    pOut.y = pV1.y * pV2.y;
    pOut.z = pV1.z * pV2.z;
    pOut.w = pV1.w * pV2.w;
    pOut
}
pub fn kmVec4Div<'a>(pOut: &'a mut KmVec4, pV1: &KmVec4, pV2: &KmVec4) -> Option<&'a mut KmVec4> {
    // Check if none of the components are zero (using short-circuiting &&)
    if pV2.x != 0.0 && pV2.y != 0.0 && pV2.z != 0.0 && pV2.w != 0.0 {
        pOut.x = pV1.x / pV2.x;
        pOut.y = pV1.y / pV2.y;
        pOut.z = pV1.z / pV2.z;
        pOut.w = pV1.w / pV2.w;
        Some(pOut)
    } else {
        Option::None
    }
}
pub fn kmVec4AreEqual(p1: &KmVec4, p2: &KmVec4) -> bool {
    (p1.x < (p2.x + 0.0001) && p1.x > (p2.x - 0.0001)) &&
    (p1.y < (p2.y + 0.0001) && p1.y > (p2.y - 0.0001)) &&
    (p1.z < (p2.z + 0.0001) && p1.z > (p2.z - 0.0001)) &&
    (p1.w < (p2.w + 0.0001) && p1.w > (p2.w - 0.0001))
}
pub fn kmVec4Assign<'a>(pOut: &'a mut KmVec4, pIn: &KmVec4) -> &'a mut KmVec4 {
    assert!(pOut as *const _ != pIn as *const _); // Check that pointers don't overlap
    *pOut = pIn.clone(); // Use Clone trait implementation for KmVec4
    pOut
}
pub fn kmVec4Length(pIn: Option<&KmVec4>) -> f32 {
    // Check for NULL pointer (None in Rust)
    let pIn = match pIn {
        Some(p) => p,
        None => return 0.0, // Default behavior when NULL is passed
    };

    ((kmSQR(pIn.x) + kmSQR(pIn.y)) + kmSQR(pIn.z) + kmSQR(pIn.w)).sqrt()
}
pub fn kmVec4LengthSq(pIn: Option<&KmVec4>) -> f32 {
    match pIn {
        Some(vec) => kmSQR(vec.x) + kmSQR(vec.y) + kmSQR(vec.z) + kmSQR(vec.w),
        None => 0.0, // Default behavior when NULL is passed (could also panic or return Option<f32>)
    }
}

pub fn kmVec4Normalize<'a>(pOut: &'a mut KmVec4, pIn: Option<&KmVec4>) -> Option<&'a mut KmVec4> {
    // Check if pIn is None (equivalent to NULL check in C)
    let pIn = match pIn {
        Some(p) => p,
        None => return None,
    };

    // Check if all components are zero (using approximate comparison for floats)
    if (pIn.x.abs() < f32::EPSILON) 
        && (pIn.y.abs() < f32::EPSILON) 
        && (pIn.z.abs() < f32::EPSILON) 
        && (pIn.w.abs() < f32::EPSILON) {
        return Some(kmVec4Assign(pOut, pIn));
    }

    // Calculate length and normalize
    let l = 1.0f32 / kmVec4Length(Some(pIn));
    pOut.x = pIn.x * l;
    pOut.y = pIn.y * l;
    pOut.z = pIn.z * l;
    pOut.w = pIn.w * l;

    Some(pOut)
}
pub fn kmVec4Scale<'a>(pOut: &'a mut KmVec4, pIn: Option<&KmVec4>, s: f32) -> Option<&'a mut KmVec4> {
    // First normalize the vector
    let normalized = kmVec4Normalize(pOut, pIn)?;
    
    // Scale each component
    normalized.x *= s;
    normalized.y *= s;
    normalized.z *= s;
    normalized.w *= s;
    
    Some(normalized)
}
pub fn kmVec4MultiplyMat4<'a>(pOut: &'a mut KmVec4, pV: &KmVec4, pM: &KmMat4) -> &'a mut KmVec4 {
    pOut.x = (((pV.x * pM.mat[0]) + (pV.y * pM.mat[4])) + (pV.z * pM.mat[8])) + (pV.w * pM.mat[12]);
    pOut.y = (((pV.x * pM.mat[1]) + (pV.y * pM.mat[5])) + (pV.z * pM.mat[9])) + (pV.w * pM.mat[13]);
    pOut.z = (((pV.x * pM.mat[2]) + (pV.y * pM.mat[6])) + (pV.z * pM.mat[10])) + (pV.w * pM.mat[14]);
    pOut.w = (((pV.x * pM.mat[3]) + (pV.y * pM.mat[7])) + (pV.z * pM.mat[11])) + (pV.w * pM.mat[15]);
    pOut
}
pub fn kmVec4Transform<'a>(pOut: &'a mut KmVec4, pV: &KmVec4, pM: &KmMat4) -> &'a mut KmVec4 {
    kmVec4MultiplyMat4(pOut, pV, pM)
}
pub fn kmVec4TransformArray<'a>(
    pOut: &'a mut [KmVec4],
    outStride: usize,
    pV: &[KmVec4],
    vStride: usize,
    pM: &KmMat4,
    count: usize,
) -> &'a mut [KmVec4] {
    for i in 0..count {
        let in_index = i * vStride;
        let out_index = i * outStride;
        
        // Ensure we don't go out of bounds
        if in_index >= pV.len() || out_index >= pOut.len() {
            break;
        }

        let in_vec = &pV[in_index];
        let out_vec = &mut pOut[out_index];
        
        kmVec4Transform(out_vec, in_vec, pM);
    }
    
    pOut
}
