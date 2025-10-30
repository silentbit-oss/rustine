use crate::*;
use std::assert;
use std::f32;
use libm::cosf;
use libm::sinf;
use std::f32::consts::PI;
use std::f32::consts::SQRT_2;
use lazy_static::lazy_static;

pub fn kmQuaternionAreEqual(p1: &KmQuaternion, p2: &KmQuaternion) -> bool {
    const EPSILON: f32 = 0.0001;
    ((p1.x - p2.x).abs() < EPSILON) &&
    ((p1.y - p2.y).abs() < EPSILON) &&
    ((p1.z - p2.z).abs() < EPSILON) &&
    ((p1.w - p2.w).abs() < EPSILON)
}
pub fn kmQuaternionFill(pOut: &mut KmQuaternion, x: f32, y: f32, z: f32, w: f32) -> &mut KmQuaternion {
    pOut.x = x;
    pOut.y = y;
    pOut.z = z;
    pOut.w = w;
    pOut
}
pub fn kmQuaternionDot(q1: &KmQuaternion, q2: &KmQuaternion) -> f32 {
    ((q1.w * q2.w) + (q1.x * q2.x) + (q1.y * q2.y)) + (q1.z * q2.z)
}
pub fn km_quaternion_exp<'a>(p_out: Option<&'a mut KmQuaternion>, p_in: Option<&KmQuaternion>) -> Option<&'a mut KmQuaternion> {
    assert!(false, "Function not implemented");
    p_out
}
pub fn kmQuaternionIdentity(pOut: Option<&mut KmQuaternion>) -> Option<&mut KmQuaternion> {
    if let Some(pOut) = pOut {
        pOut.x = 0.0;
        pOut.y = 0.0;
        pOut.z = 0.0;
        pOut.w = 1.0;
        Some(pOut)
    } else {
        None
    }
}
pub fn kmQuaternionIsIdentity(pIn: Option<&KmQuaternion>) -> bool {
    match pIn {
        Some(quat) => (quat.x == 0.0) && (quat.y == 0.0) && (quat.z == 0.0) && (quat.w == 1.0),
        None => false,
    }
}
pub fn kmQuaternionLengthSq(pIn: &KmQuaternion) -> f32 {
    ((pIn.x * pIn.x) + (pIn.y * pIn.y) + (pIn.z * pIn.z)) + (pIn.w * pIn.w)
}
pub fn km_quaternion_ln<'a>(p_out: Option<&'a mut KmQuaternion>, p_in: Option<&KmQuaternion>) -> Option<&'a mut KmQuaternion> {
    assert!(false, "Function not implemented");
    p_out
}

pub fn km_quaternion_rotation_pitch_yaw_roll(
    p_out: &mut KmQuaternion,
    pitch: f32,
    yaw: f32,
    roll: f32,
) -> &mut KmQuaternion {
    assert!(pitch <= (2.0 * PI));
    assert!(yaw <= (2.0 * PI));
    assert!(roll <= (2.0 * PI));
    
    let s_y = sinf(yaw * 0.5);
    let c_y = cosf(yaw * 0.5);
    let s_z = sinf(roll * 0.5);
    let c_z = cosf(roll * 0.5);
    let s_x = sinf(pitch * 0.5);
    let c_x = cosf(pitch * 0.5);
    
    p_out.w = ((c_y * c_z) * c_x) - ((s_y * s_z) * s_x);
    p_out.x = ((s_y * s_z) * c_x) + ((c_y * c_z) * s_x);
    p_out.y = ((s_y * c_z) * c_x) + ((c_y * s_z) * s_x);
    p_out.z = ((c_y * s_z) * c_x) - ((s_y * c_z) * s_x);
    
    p_out
}
pub fn kmQuaternionScale<'a>(pOut: &'a mut KmQuaternion, pIn: &KmQuaternion, s: f32) -> &'a mut KmQuaternion {
    pOut.x = pIn.x * s;
    pOut.y = pIn.y * s;
    pOut.z = pIn.z * s;
    pOut.w = pIn.w * s;
    pOut
}
pub fn kmQuaternionAssign<'a>(pOut: &'a mut KmQuaternion, pIn: &KmQuaternion) -> &'a mut KmQuaternion {
    *pOut = pIn.clone();
    pOut
}
pub fn kmQuaternionAdd<'a>(
    pOut: Option<&'a mut KmQuaternion>,
    pQ1: Option<&'a KmQuaternion>,
    pQ2: Option<&'a KmQuaternion>,
) -> Option<&'a mut KmQuaternion> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pQ1.is_none() || pQ2.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pQ1 = pQ1.unwrap();
    let pQ2 = pQ2.unwrap();

    // Perform the addition
    pOut.x = pQ1.x + pQ2.x;
    pOut.y = pQ1.y + pQ2.y;
    pOut.z = pQ1.z + pQ2.z;
    pOut.w = pQ1.w + pQ2.w;

    Some(pOut)
}
pub fn kmQuaternionSubtract<'a>(pOut: &'a mut KmQuaternion, pQ1: &KmQuaternion, pQ2: &KmQuaternion) -> &'a mut KmQuaternion {
    pOut.x = pQ1.x - pQ2.x;
    pOut.y = pQ1.y - pQ2.y;
    pOut.z = pQ1.z - pQ2.z;
    pOut.w = pQ1.w - pQ2.w;
    pOut
}

pub fn km_quaternion_get_pitch(q: &KmQuaternion) -> f32 {
    let numerator = 2.0 * ((q.y * q.z) + (q.w * q.x));
    let denominator = ((q.w * q.w) - (q.x * q.x) - (q.y * q.y)) + (q.z * q.z);
    numerator.atan2(denominator)
}

pub fn km_quaternion_get_yaw(q: Option<&KmQuaternion>) -> Option<f32> {
    // Check for NULL pointer equivalent (None in Rust)
    let q = q?; // Early return if None

    // Calculate the result using safe Rust operations
    let result = ((-2.0) * ((q.x * q.z) - (q.w * q.y))).asin();
    
    Some(result)
}

pub fn km_quaternion_get_roll(q: &KmQuaternion) -> f32 {
    let numerator = 2.0 * ((q.x * q.y) + (q.w * q.z));
    let denominator = ((q.w * q.w) + (q.x * q.x)) - (q.y * q.y) - (q.z * q.z);
    numerator.atan2(denominator)
}

pub fn kmQuaternionLength(pIn: &KmQuaternion) -> f32 {
    f32::sqrt(kmQuaternionLengthSq(pIn))
}
pub fn kmQuaternionInverse<'a>(pOut: &'a mut KmQuaternion, pIn: &KmQuaternion) -> &'a mut KmQuaternion {
    let l = kmQuaternionLength(pIn);
    if f32::abs(l) < 0.0001 {
        pOut.x = 0.0;
        pOut.y = 0.0;
        pOut.z = 0.0;
        pOut.w = 0.0;
        return pOut;
    }
    pOut.x = -pIn.x;
    pOut.y = -pIn.y;
    pOut.z = -pIn.z;
    pOut.w = pIn.w;
    pOut
}
pub fn kmQuaternionMultiply<'a>(pOut: &'a mut KmQuaternion, qu1: &KmQuaternion, qu2: &KmQuaternion) -> &'a mut KmQuaternion {
    let mut tmp1 = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    let mut tmp2 = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    
    kmQuaternionAssign(&mut tmp1, qu1);
    kmQuaternionAssign(&mut tmp2, qu2);
    
    let q1 = &tmp1;
    let q2 = &tmp2;
    
    pOut.x = (((q1.w * q2.x) + (q1.x * q2.w)) + (q1.y * q2.z)) - (q1.z * q2.y);
    pOut.y = (((q1.w * q2.y) + (q1.y * q2.w)) + (q1.z * q2.x)) - (q1.x * q2.z);
    pOut.z = (((q1.w * q2.z) + (q1.z * q2.w)) + (q1.x * q2.y)) - (q1.y * q2.x);
    pOut.w = (((q1.w * q2.w) - (q1.x * q2.x)) - (q1.y * q2.y)) - (q1.z * q2.z);
    
    pOut
}
pub fn kmQuaternionRotationMatrix<'a>(pOut: &'a mut KmQuaternion, pIn: Option<&KmMat3>) -> Option<&'a mut KmQuaternion> {
    // Check for NULL input (None in Rust)
    let pIn = match pIn {
        Some(mat) => mat,
        None => return None,
    };

    let mut x: f32;
    let mut y: f32;
    let mut z: f32;
    let mut w: f32;
    let mut scale: f32;
    let mut diagonal: f32;

    // Initialize m4x4 matrix with 0s
    let mut m4x4 = [0.0f32; 16];
    
    // Fill the m4x4 matrix from the input 3x3 matrix
    m4x4[0] = pIn.mat[0];
    m4x4[1] = pIn.mat[3];
    m4x4[2] = pIn.mat[6];
    m4x4[4] = pIn.mat[1];
    m4x4[5] = pIn.mat[4];
    m4x4[6] = pIn.mat[7];
    m4x4[8] = pIn.mat[2];
    m4x4[9] = pIn.mat[5];
    m4x4[10] = pIn.mat[8];
    m4x4[15] = 1.0;

    // Calculate diagonal
    diagonal = (m4x4[0] + m4x4[5] + m4x4[10]) + 1.0;

    if diagonal > 0.0001 {
        scale = diagonal.sqrt() * 2.0;
        x = (m4x4[9] - m4x4[6]) / scale;
        y = (m4x4[2] - m4x4[8]) / scale;
        z = (m4x4[4] - m4x4[1]) / scale;
        w = 0.25 * scale;
    } else {
        if (m4x4[0] > m4x4[5]) && (m4x4[0] > m4x4[10]) {
            scale = ((1.0 + m4x4[0] - m4x4[5] - m4x4[10]).sqrt()) * 2.0;
            x = 0.25 * scale;
            y = (m4x4[4] + m4x4[1]) / scale;
            z = (m4x4[2] + m4x4[8]) / scale;
            w = (m4x4[9] - m4x4[6]) / scale;
        } else if m4x4[5] > m4x4[10] {
            scale = ((1.0 + m4x4[5] - m4x4[0] - m4x4[10]).sqrt()) * 2.0;
            x = (m4x4[4] + m4x4[1]) / scale;
            y = 0.25 * scale;
            z = (m4x4[9] + m4x4[6]) / scale;
            w = (m4x4[2] - m4x4[8]) / scale;
        } else {
            scale = ((1.0 + m4x4[10] - m4x4[0] - m4x4[5]).sqrt()) * 2.0;
            x = (m4x4[2] + m4x4[8]) / scale;
            y = (m4x4[9] + m4x4[6]) / scale;
            z = 0.25 * scale;
            w = (m4x4[4] - m4x4[1]) / scale;
        }
    }

    // Set the output quaternion values
    pOut.x = x;
    pOut.y = y;
    pOut.z = z;
    pOut.w = w;

    Some(pOut)
}
pub fn kmQuaternionNormalize<'a>(pOut: &'a mut KmQuaternion, pIn: &KmQuaternion) -> &'a mut KmQuaternion {
    let length = kmQuaternionLength(pIn);
    if f32::abs(length) < 0.0001 {
        pOut.x = 0.0;
        pOut.y = 0.0;
        pOut.z = 0.0;
        pOut.w = 0.0;
        return pOut;
    }
    kmQuaternionFill(
        pOut,
        pIn.x / length,
        pIn.y / length,
        pIn.z / length,
        pIn.w / length,
    )
}
pub fn kmQuaternionRotationAxisAngle<'a>(
    pOut: Option<&'a mut KmQuaternion>,
    pV: Option<&'a KmVec3>,
    angle: f32,
) -> Option<&'a mut KmQuaternion> {
    // Check for NULL pointers (None in Rust)
    let pOut = pOut?;
    let pV = pV?;

    let rad = angle * 0.5f32;
    let scale = rad.sin(); // Equivalent to sinf in C

    // Create a new quaternion with the calculated values
    let mut quat = KmQuaternion {
        x: pV.x * scale,
        y: pV.y * scale,
        z: pV.z * scale,
        w: rad.cos(), // Equivalent to cosf in C
    };

    // Normalize the quaternion
    kmQuaternionNormalize(pOut, &quat);

    Some(pOut)
}
pub fn kmQuaternionToAxisAngle(
    pIn: Option<&KmQuaternion>,
    pAxis: Option<&mut KmVec3>,
    pAngle: Option<&mut f32>,
) {
    // Check if any input is None (equivalent to NULL checks in C)
    if pIn.is_none() || pAxis.is_none() || pAngle.is_none() {
        return;
    }

    // Unwrap safely since we've checked for None
    let pIn = pIn.unwrap();
    let pAxis = pAxis.unwrap();
    let pAngle = pAngle.unwrap();

    let tempAngle = f32::acos(pIn.w);
    let scale = f32::sqrt((kmSQR(pIn.x) + kmSQR(pIn.y)) + kmSQR(pIn.z));

    if ((scale > -0.0001) && (scale < 0.0001))
        || ((scale < (2.0 * f32::consts::PI + 0.0001))
            && (scale > (2.0 * f32::consts::PI - 0.0001)))
    {
        *pAngle = 0.0;
        pAxis.x = 0.0;
        pAxis.y = 0.0;
        pAxis.z = 1.0;
    } else {
        *pAngle = tempAngle * 2.0;
        pAxis.x = pIn.x / scale;
        pAxis.y = pIn.y / scale;
        pAxis.z = pIn.z / scale;
        let temp_axis = pAxis.clone();
        kmVec3Normalize(Some(pAxis), Some(&temp_axis));
    }
}
pub fn kmQuaternionMultiplyVec3<'a>(
    pOut: &'a mut KmVec3,
    q: &KmQuaternion,
    v: &KmVec3,
) -> &'a mut KmVec3 {
    let qvec = KmVec3 {
        x: q.x,
        y: q.y,
        z: q.z,
    };

    let mut uv = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut uuv = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };

    // First cross product
    kmVec3Cross(&mut uv, &qvec, v);
    // Second cross product
    kmVec3Cross(&mut uuv, &qvec, &uv);
    
    // Create temporary copies for scaling
    let uv_copy = uv.clone();
    let uuv_copy = uuv.clone();
    
    // Scale uv
    kmVec3Scale(&mut uv, &uv_copy, 2.0 * q.w);
    // Scale uuv
    kmVec3Scale(&mut uuv, &uuv_copy, 2.0);
    
    // First addition
    let uv_copy = uv.clone();
    kmVec3Add(pOut, v, &uv_copy);
    // Second addition
    let uuv_copy = uuv.clone();
    let p_out_copy = pOut.clone();
    kmVec3Add(pOut, &p_out_copy, &uuv_copy);

    pOut
}
pub fn kmQuaternionGetUpVec3<'a>(
    pOut: &'a mut KmVec3,
    pIn: &KmQuaternion,
) -> &'a mut KmVec3 {
    kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Y)
}
pub fn kmQuaternionGetRightVec3<'a>(
    pOut: &'a mut KmVec3,
    pIn: &KmQuaternion,
) -> &'a mut KmVec3 {
    kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_X)
}
pub fn kmQuaternionGetForwardVec3RH<'a>(
    pOut: &'a mut KmVec3,
    pIn: &KmQuaternion,
) -> &'a mut KmVec3 {
    kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_NEG_Z)
}
pub fn kmQuaternionGetForwardVec3LH<'a>(
    pOut: &'a mut KmVec3,
    pIn: &KmQuaternion,
) -> &'a mut KmVec3 {
    kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Z)
}
pub fn kmQuaternionSlerp<'a>(
    pOut: Option<&'a mut KmQuaternion>,
    q1: Option<&'a KmQuaternion>,
    q2: Option<&'a KmQuaternion>,
    t: f32,
) -> Option<&'a mut KmQuaternion> {
    // Early return if any input is None
    let pOut = pOut?;
    let q1 = q1?;
    let q2 = q2?;

    let dot = kmQuaternionDot(q1, q2);
    const DOT_THRESHOLD: f64 = 0.9995;

    if dot as f64 > DOT_THRESHOLD {
        let mut diff = KmQuaternion {
            x: 0.0,
            y: 0.0,
            z: 0.0,
            w: 0.0,
        };
        kmQuaternionSubtract(&mut diff, q2, q1);
        let diff_copy = diff.clone();
        kmQuaternionScale(&mut diff, &diff_copy, t);
        let diff_copy = diff.clone();
        kmQuaternionAdd(Some(pOut), Some(q1), Some(&diff_copy));
        let p_out_copy = pOut.clone();
        kmQuaternionNormalize(pOut, &p_out_copy);
        return Some(pOut);
    }

    let dot = kmClamp(dot, -1.0, 1.0);
    let theta_0 = dot.acos();
    let theta = theta_0 * t;

    let mut tmp = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    let tmp_copy = tmp.clone();
    kmQuaternionScale(&mut tmp, q1, dot);
    let tmp_copy = tmp.clone();
    kmQuaternionSubtract(&mut tmp, q2, &tmp_copy);
    let tmp_copy = tmp.clone();
    kmQuaternionNormalize(&mut tmp, &tmp_copy);

    let mut t1 = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    let mut t2 = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    let t1_copy = t1.clone();
    kmQuaternionScale(&mut t1, q1, theta.cos());
    let t2_copy = t2.clone();
    kmQuaternionScale(&mut t2, &tmp, theta.sin());
    let t1_copy = t1.clone();
    let t2_copy = t2.clone();
    kmQuaternionAdd(Some(pOut), Some(&t1_copy), Some(&t2_copy));

    Some(pOut)
}
pub fn kmQuaternionLookRotation<'a>(
    pOut: &'a mut KmQuaternion,
    direction: Option<&KmVec3>,
    up: Option<&KmVec3>,
) -> Option<&'a mut KmQuaternion> {
    let mut tmp = KmMat3 { mat: [0.0; 9] };
    
    // Perform the look-at matrix calculation
    kmMat3LookAt(Some(&mut tmp), Some(&KM_VEC3_ZERO), direction, up)?;
    
    // Convert matrix to quaternion
    kmQuaternionRotationMatrix(pOut, Some(&tmp))?;
    
    // Clone rotated value to avoid holding reference during normalization
    let rotated_value = pOut.clone();
    
    // Normalize and return
    let normalized = kmQuaternionNormalize(pOut, &rotated_value);
    Some(normalized)
}
pub fn kmQuaternionRotationBetweenVec3<'a>(
    pOut: Option<&'a mut KmQuaternion>,
    vec1: Option<&'a KmVec3>,
    vec2: Option<&'a KmVec3>,
    fallback: Option<&'a KmVec3>,
) -> Option<&'a mut KmQuaternion> {
    // Early return if any required input is None
    let pOut = pOut?;
    let vec1 = vec1?;
    let vec2 = vec2?;

    let mut v1 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut v2 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    
    // Assign and normalize vectors
    kmVec3Assign(Some(&mut v1), Some(vec1));
    kmVec3Assign(Some(&mut v2), Some(vec2));
    
    // Create temporary copies for normalization
    let v1_copy = v1.clone();
    let v2_copy = v2.clone();
    kmVec3Normalize(Some(&mut v1), Some(&v1_copy));
    kmVec3Normalize(Some(&mut v2), Some(&v2_copy));

    let a = kmVec3Dot(Some(&v1), Some(&v2)).unwrap_or(0.0);

    if a >= 1.0 {
        kmQuaternionIdentity(Some(pOut));
        return Some(pOut);
    }

    if a < (1e-6 - 1.0) {
        if let Some(fb) = fallback {
            if f32::abs(kmVec3LengthSq(Some(fb))) < 0.0001 {
                kmQuaternionRotationAxisAngle(Some(pOut), Some(fb), f32::consts::PI);
            } else {
                let mut axis = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
                let x = KmVec3 { x: 1.0, y: 0.0, z: 0.0 };
                kmVec3Cross(&mut axis, &x, vec1);
                
                if f32::abs(kmVec3LengthSq(Some(&axis))) < 0.0001 {
                    let y = KmVec3 { x: 0.0, y: 1.0, z: 0.0 };
                    kmVec3Cross(&mut axis, &y, vec1);
                }
                
                // Create temporary copy for normalization
                let axis_copy = axis.clone();
                kmVec3Normalize(Some(&mut axis), Some(&axis_copy));
                kmQuaternionRotationAxisAngle(Some(pOut), Some(&axis), f32::consts::PI);
            }
        }
    } else {
        let s = f32::sqrt((1.0 + a) * 2.0);
        let invs = 1.0 / s;
        let mut c = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        kmVec3Cross(&mut c, &v1, &v2);

        pOut.x = c.x * invs;
        pOut.y = c.y * invs;
        pOut.z = c.z * invs;
        pOut.w = s * 0.5;
        
        // Create temporary copy for normalization
        let p_out_copy = pOut.clone();
        kmQuaternionNormalize(pOut, &p_out_copy);
    }

    Some(pOut)
}
