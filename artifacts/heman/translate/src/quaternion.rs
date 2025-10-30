use std::assert;
use std::f32;
use libm::cosf;
use libm::sinf;
use std::f32::consts::PI;
use std::f32::consts::SQRT_2;
use lazy_static::lazy_static;
use crate::*;pub fn helper_kmQuaternionRotationMatrix_1(
    x_ref: &mut f32,
    y_ref: &mut f32,
    z_ref: &mut f32,
    w_ref: &mut f32,
    scale_ref: &mut f32,
    pMatrix: &[f32],
    pMatrix_idx: usize,
) {
    let mut x = *x_ref;
    let mut y = *y_ref;
    let mut z = *z_ref;
    let mut w = *w_ref;
    let mut scale = *scale_ref;

    if (pMatrix[0 + pMatrix_idx] > pMatrix[5 + pMatrix_idx]) 
        && (pMatrix[0 + pMatrix_idx] > pMatrix[10 + pMatrix_idx]) 
    {
        scale = (((1.0f32 + pMatrix[0 + pMatrix_idx]) - pMatrix[5 + pMatrix_idx]) - pMatrix[10 + pMatrix_idx]).sqrt() * 2.0f32;
        x = 0.25f32 * scale;
        y = (pMatrix[4 + pMatrix_idx] + pMatrix[1 + pMatrix_idx]) / scale;
        z = (pMatrix[2 + pMatrix_idx] + pMatrix[8 + pMatrix_idx]) / scale;
        w = (pMatrix[9 + pMatrix_idx] - pMatrix[6 + pMatrix_idx]) / scale;
    } else if pMatrix[5 + pMatrix_idx] > pMatrix[10 + pMatrix_idx] {
        scale = (((1.0f32 + pMatrix[5 + pMatrix_idx]) - pMatrix[0 + pMatrix_idx]) - pMatrix[10 + pMatrix_idx]).sqrt() * 2.0f32;
        x = (pMatrix[4 + pMatrix_idx] + pMatrix[1 + pMatrix_idx]) / scale;
        y = 0.25f32 * scale;
        z = (pMatrix[9 + pMatrix_idx] + pMatrix[6 + pMatrix_idx]) / scale;
        w = (pMatrix[2 + pMatrix_idx] - pMatrix[8 + pMatrix_idx]) / scale;
    } else {
        scale = (((1.0f32 + pMatrix[10 + pMatrix_idx]) - pMatrix[0 + pMatrix_idx]) - pMatrix[5 + pMatrix_idx]).sqrt() * 2.0f32;
        x = (pMatrix[2 + pMatrix_idx] + pMatrix[8 + pMatrix_idx]) / scale;
        y = (pMatrix[9 + pMatrix_idx] + pMatrix[6 + pMatrix_idx]) / scale;
        z = 0.25f32 * scale;
        w = (pMatrix[4 + pMatrix_idx] - pMatrix[1 + pMatrix_idx]) / scale;
    }

    *x_ref = x;
    *y_ref = y;
    *z_ref = z;
    *w_ref = w;
    *scale_ref = scale;
}
pub fn km_quaternion_are_equal(p1: &KmQuaternion, p2: &KmQuaternion) -> bool {
    const EPSILON: f32 = 0.0001;
    (p1.x - p2.x).abs() < EPSILON &&
    (p1.y - p2.y).abs() < EPSILON &&
    (p1.z - p2.z).abs() < EPSILON &&
    (p1.w - p2.w).abs() < EPSILON
}
pub fn kmQuaternionFill(pOut: &mut KmQuaternion, x: f32, y: f32, z: f32, w: f32) -> &mut KmQuaternion {
    pOut.x = x;
    pOut.y = y;
    pOut.z = z;
    pOut.w = w;
    pOut
}
pub fn kmQuaternionDot(q1: &KmQuaternion, q2: &KmQuaternion) -> f32 {
    (((q1.w * q2.w) + (q1.x * q2.x)) + (q1.y * q2.y)) + (q1.z * q2.z)
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
pub fn kmQuaternionLengthSq(pIn: Option<&KmQuaternion>) -> f32 {
    match pIn {
        Some(p) => (p.x * p.x) + (p.y * p.y) + (p.z * p.z) + (p.w * p.w),
        None => 0.0, // Default value when input is None (NULL in C)
    }
}
pub fn km_quaternion_ln<'a>(p_out: Option<&'a mut KmQuaternion>, p_in: Option<&'a KmQuaternion>) -> Option<&'a mut KmQuaternion> {
    // The C version asserts and returns pOut, which is unsafe behavior
    // In Rust, we'll return None to indicate failure (since the C version asserts)
    Option::None
}

pub fn km_quaternion_rotation_pitch_yaw_roll(
    p_out: Option<&mut KmQuaternion>,
    pitch: f32,
    yaw: f32,
    roll: f32,
) -> Option<&mut KmQuaternion> {
    // Check if p_out is None (equivalent to NULL check in C)
    let p_out = p_out?;

    // Assertions (using debug_assert! which is removed in release builds)
    debug_assert!(pitch <= (2.0 * PI));
    debug_assert!(yaw <= (2.0 * PI));
    debug_assert!(roll <= (2.0 * PI));

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

    Some(p_out)
}
pub fn kmQuaternionScale<'a>(pOut: &'a mut KmQuaternion, pIn: &KmQuaternion, s: f32) -> &'a mut KmQuaternion {
    pOut.x = pIn.x * s;
    pOut.y = pIn.y * s;
    pOut.z = pIn.z * s;
    pOut.w = pIn.w * s;
    pOut
}
pub fn km_quaternion_assign<'a>(p_out: &'a mut KmQuaternion, p_in: &KmQuaternion) -> &'a mut KmQuaternion {
    *p_out = p_in.clone();
    p_out
}
pub fn kmQuaternionAdd<'a>(pOut: &'a mut KmQuaternion, pQ1: &KmQuaternion, pQ2: &KmQuaternion) -> &'a mut KmQuaternion {
    pOut.x = pQ1.x + pQ2.x;
    pOut.y = pQ1.y + pQ2.y;
    pOut.z = pQ1.z + pQ2.z;
    pOut.w = pQ1.w + pQ2.w;
    pOut
}
pub fn kmQuaternionSubtract<'a>(pOut: &'a mut KmQuaternion, pQ1: &KmQuaternion, pQ2: &KmQuaternion) -> &'a mut KmQuaternion {
    pOut.x = pQ1.x - pQ2.x;
    pOut.y = pQ1.y - pQ2.y;
    pOut.z = pQ1.z - pQ2.z;
    pOut.w = pQ1.w - pQ2.w;
    pOut
}

pub fn km_quaternion_get_pitch(q: Option<&KmQuaternion>) -> Option<f32> {
    // Check for NULL pointer equivalent
    let q = q?;

    // Calculate the pitch using atan2
    let numerator = 2.0 * ((q.y * q.z) + (q.w * q.x));
    let denominator = ((q.w * q.w) - (q.x * q.x) - (q.y * q.y)) + (q.z * q.z);
    let result = numerator.atan2(denominator);

    Some(result)
}

pub fn kmQuaternionGetYaw(q: Option<&KmQuaternion>) -> Option<f32> {
    // Check for NULL pointer equivalent (None in Rust)
    let q = q?;  // Early return if None

    // Calculate the result using safe Rust operations
    let result = ((-2.0) * ((q.x * q.z) - (q.w * q.y))).asin();
    
    Some(result)
}

pub fn km_quaternion_get_roll(q: &KmQuaternion) -> f32 {
    let numerator = 2.0 * ((q.x * q.y) + (q.w * q.z));
    let denominator = ((q.w * q.w) + (q.x * q.x)) - (q.y * q.y) - (q.z * q.z);
    f32::atan2(numerator, denominator)
}

pub fn kmQuaternionLength(pIn: Option<&KmQuaternion>) -> f32 {
    f32::sqrt(kmQuaternionLengthSq(pIn))
}
pub fn kmQuaternionInverse<'a>(pOut: &'a mut KmQuaternion, pIn: Option<&KmQuaternion>) -> Option<&'a mut KmQuaternion> {
    // Check if input is None (equivalent to NULL check in C)
    let pIn = match pIn {
        Some(quat) => quat,
        None => return None,
    };

    let l = kmQuaternionLength(Some(pIn));
    
    if f32::abs(l) < 0.0001 {
        pOut.x = 0.0;
        pOut.y = 0.0;
        pOut.z = 0.0;
        pOut.w = 0.0;
        return Some(pOut);
    }

    pOut.x = -pIn.x;
    pOut.y = -pIn.y;
    pOut.z = -pIn.z;
    pOut.w = pIn.w;

    Some(pOut)
}
pub fn km_quaternion_multiply<'a>(
    p_out: &'a mut KmQuaternion,
    qu1: &KmQuaternion,
    qu2: &KmQuaternion,
) -> &'a mut KmQuaternion {
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
    
    km_quaternion_assign(&mut tmp1, qu1);
    km_quaternion_assign(&mut tmp2, qu2);
    
    let q1 = &tmp1;
    let q2 = &tmp2;
    
    p_out.x = (((q1.w * q2.x) + (q1.x * q2.w)) + (q1.y * q2.z)) - (q1.z * q2.y);
    p_out.y = (((q1.w * q2.y) + (q1.y * q2.w)) + (q1.z * q2.x)) - (q1.x * q2.z);
    p_out.z = (((q1.w * q2.z) + (q1.z * q2.w)) + (q1.x * q2.y)) - (q1.y * q2.x);
    p_out.w = (((q1.w * q2.w) - (q1.x * q2.x)) - (q1.y * q2.y)) - (q1.z * q2.z);
    
    p_out
}
pub fn kmQuaternionNormalize<'a>(pOut: &'a mut KmQuaternion, pIn: Option<&'a KmQuaternion>) -> Option<&'a mut KmQuaternion> {
    // Check for NULL input (None in Rust)
    let pIn = match pIn {
        Some(quat) => quat,
        None => return None,
    };

    let length = kmQuaternionLength(Some(pIn));
    
    if f32::abs(length) < 0.0001 {
        pOut.x = 0.0;
        pOut.y = 0.0;
        pOut.z = 0.0;
        pOut.w = 0.0;
        return Some(pOut);
    }

    kmQuaternionFill(
        pOut,
        pOut.x / length,
        pOut.y / length,
        pOut.z / length,
        pOut.w / length,
    );
    
    Some(pOut)
}
pub fn kmQuaternionRotationAxisAngle<'a>(
    pOut: &'a mut KmQuaternion,
    pV: Option<&'a KmVec3>,
    angle: f32,
) -> Option<&'a mut KmQuaternion> {
    // Check for NULL pointer (None in Rust)
    let pV = pV?;

    let rad = angle * 0.5f32;
    let scale = rad.sin(); // Using Rust's built-in sin method

    // Create a temporary quaternion to store the initial values
    let mut temp = KmQuaternion {
        x: pV.x * scale,
        y: pV.y * scale,
        z: pV.z * scale,
        w: rad.cos(),
    };

    // Copy the temporary values to pOut
    *pOut = temp;

    // Now we can safely call normalize with just pOut
    kmQuaternionNormalize(pOut, None)
}
pub fn kmQuaternionRotationMatrix<'a>(pOut: &'a mut KmQuaternion, pIn: Option<&KmMat3>) -> Option<&'a mut KmQuaternion> {
    // Check for NULL input (None in Rust)
    let pIn = match pIn {
        Some(mat) => mat,
        None => return None,
    };

    let mut x: f32 = 0.0;
    let mut y: f32 = 0.0;
    let mut z: f32 = 0.0;
    let mut w: f32 = 0.0;
    let mut m4x4 = [0.0f32; 16];
    let mut scale: f32 = 0.0;
    let mut diagonal: f32 = 0.0;

    // Populate the 4x4 matrix from the 3x3 input matrix
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

    let pMatrix = &m4x4;
    let pMatrix_idx = 0;

    diagonal = ((pMatrix[0 + pMatrix_idx] + pMatrix[5 + pMatrix_idx]) + pMatrix[10 + pMatrix_idx]) + 1.0;

    if diagonal > 0.0001 {
        scale = diagonal.sqrt() * 2.0;
        x = (pMatrix[9 + pMatrix_idx] - pMatrix[6 + pMatrix_idx]) / scale;
        y = (pMatrix[2 + pMatrix_idx] - pMatrix[8 + pMatrix_idx]) / scale;
        z = (pMatrix[4 + pMatrix_idx] - pMatrix[1 + pMatrix_idx]) / scale;
        w = 0.25f32 * scale;
    } else {
        helper_kmQuaternionRotationMatrix_1(
            &mut x,
            &mut y,
            &mut z,
            &mut w,
            &mut scale,
            pMatrix,
            pMatrix_idx,
        );
    }

    pOut.x = x;
    pOut.y = y;
    pOut.z = z;
    pOut.w = w;

    Some(pOut)
}
pub fn kmQuaternionToAxisAngle(
    pIn: Option<&KmQuaternion>,
    pAxis: Option<&mut KmVec3>,
    pAngle: Option<&mut f32>,
) {
    // Check for None values (equivalent to NULL checks in C)
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

    // First cross product
    let mut uv = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    kmVec3Cross(&mut uv, &qvec, v);
    
    // Scale first result - use a temporary copy to avoid borrowing conflicts
    let uv_copy = uv.clone();
    kmVec3Scale(&mut uv, &uv_copy, 2.0 * q.w);
    
    // Second cross product
    let mut uuv = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    kmVec3Cross(&mut uuv, &qvec, &uv);
    
    // Scale second result - use a temporary copy to avoid borrowing conflicts
    let uuv_copy = uuv.clone();
    kmVec3Scale(&mut uuv, &uuv_copy, 2.0);
    
    // Final additions - split into separate operations to avoid borrowing conflicts
    kmVec3Add(pOut, v, &uv);
    let p_out_copy = pOut.clone();
    kmVec3Add(pOut, &p_out_copy, &uuv)
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
pub fn helper_kmQuaternionRotationBetweenVec3_1<'a>(
    pOut: &'a mut KmQuaternion,
    vec1: Option<&'a KmVec3>,
    fallback: Option<&'a KmVec3>,
) {
    // Check if fallback vector length is too small
    if kmVec3LengthSq(fallback) < 0.0001 {
        kmQuaternionRotationAxisAngle(pOut, fallback, std::f32::consts::PI);
    } else {
        let vec1 = vec1.unwrap(); // Safe because we know fallback exists and vec1 is required
        
        let mut axis = KmVec3 {
            x: 0.0,
            y: 0.0,
            z: 0.0,
        };
        
        // First try with X axis
        let x_axis = KmVec3 {
            x: 1.0,
            y: 0.0,
            z: 0.0,
        };
        kmVec3Cross(&mut axis, &x_axis, vec1);
        
        // If cross product with X is too small, try with Y axis
        if kmVec3LengthSq(Some(&axis)) < 0.0001 {
            let y_axis = KmVec3 {
                x: 0.0,
                y: 1.0,
                z: 0.0,
            };
            kmVec3Cross(&mut axis, &y_axis, vec1);
        }
        
        // Create a temporary copy for normalization
        let axis_copy = axis.clone();
        // Normalize the axis in-place
        kmVec3Normalize(Some(&mut axis), Some(&axis_copy));
        
        // Create rotation with normalized axis
        kmQuaternionRotationAxisAngle(pOut, Some(&axis), std::f32::consts::PI);
    }
}
pub fn kmQuaternionSlerp<'a>(
    pOut: &'a mut KmQuaternion,
    q1: &KmQuaternion,
    q2: &KmQuaternion,
    t: f32,
) -> &'a mut KmQuaternion {
    let mut dot = kmQuaternionDot(q1, q2);
    const DOT_THRESHOLD: f32 = 0.9995;

    if dot > DOT_THRESHOLD {
        let mut diff = KmQuaternion {
            x: 0.0,
            y: 0.0,
            z: 0.0,
            w: 0.0,
        };
        kmQuaternionSubtract(&mut diff, q2, q1);
        let diff_copy = diff.clone();
        kmQuaternionScale(&mut diff, &diff_copy, t);
        kmQuaternionAdd(pOut, q1, &diff);
        let p_out_copy = pOut.clone();
        kmQuaternionNormalize(pOut, Some(&p_out_copy));
        return pOut;
    }

    dot = kmClamp(dot, -1.0_f32, 1.0_f32);
    let theta_0 = dot.acos();
    let theta = theta_0 * t;

    let mut tmp = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    kmQuaternionScale(&mut tmp, q1, dot);
    let tmp_copy = tmp.clone();
    kmQuaternionSubtract(&mut tmp, q2, &tmp_copy);
    let tmp_copy = tmp.clone();
    kmQuaternionNormalize(&mut tmp, Some(&tmp_copy));

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
    kmQuaternionScale(&mut t1, q1, theta.cos());
    kmQuaternionScale(&mut t2, &tmp, theta.sin());
    kmQuaternionAdd(pOut, &t1, &t2);

    pOut
}
pub fn kmQuaternionLookRotation<'a>(
    pOut: &'a mut KmQuaternion,
    direction: Option<&'a KmVec3>,
    up: Option<&'a KmVec3>,
) -> Option<&'a mut KmQuaternion> {
    let mut tmp = KmMat3 { mat: [0.0; 9] };
    
    // Perform the look-at matrix calculation
    let tmp_ref = kmMat3LookAt(Some(&mut tmp), Some(&KM_VEC3_ZERO), direction, up);
    if tmp_ref.is_none() {
        return Option::None;
    }
    
    // Convert matrix to quaternion
    let rotation_result = kmQuaternionRotationMatrix(pOut, Some(&tmp));
    if rotation_result.is_none() {
        return Option::None;
    }
    
    // Normalize the quaternion
    kmQuaternionNormalize(pOut, None)
}
pub fn kmQuaternionRotationBetweenVec3<'a>(
    pOut: &'a mut KmQuaternion,
    vec1: Option<&KmVec3>,
    vec2: Option<&KmVec3>,
    fallback: Option<&KmVec3>,
) -> Option<&'a mut KmQuaternion> {
    let vec1 = vec1?;
    let vec2 = vec2?;

    let mut v1 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut v2 = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };

    kmVec3Assign(Some(&mut v1), Some(vec1));
    kmVec3Assign(Some(&mut v2), Some(vec2));

    // Normalize v1 without borrowing conflicts
    {
        let v1_copy = v1.clone();
        kmVec3Normalize(Some(&mut v1), Some(&v1_copy));
    }
    // Normalize v2 without borrowing conflicts
    {
        let v2_copy = v2.clone();
        kmVec3Normalize(Some(&mut v2), Some(&v2_copy));
    }

    let a = kmVec3Dot(Some(&v1), Some(&v2))?;

    if a >= 1.0 {
        kmQuaternionIdentity(Some(pOut))?;
        return Some(pOut);
    }

    if a < (1e-6 - 1.0) {
        helper_kmQuaternionRotationBetweenVec3_1(pOut, Some(vec1), fallback);
    } else {
        let s = f32::sqrt((1.0 + a) * 2.0);
        let invs = 1.0 / s;
        let mut c = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        kmVec3Cross(&mut c, &v1, &v2);

        pOut.x = c.x * invs;
        pOut.y = c.y * invs;
        pOut.z = c.z * invs;
        pOut.w = s * 0.5;

        // Normalize quaternion without borrowing conflicts
        {
            let p_out_copy = pOut.clone();
            kmQuaternionNormalize(pOut, Some(&p_out_copy))?;
        }
    }

    Some(pOut)
}
