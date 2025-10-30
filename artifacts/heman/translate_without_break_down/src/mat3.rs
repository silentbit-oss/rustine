use crate::*;
use std::assert;
use std::f32;
use rand::Rng;
use std::f32::consts::PI;

pub fn kmMat3Fill<'a>(pOut: &'a mut KmMat3, pMat: Option<&[f32]>) -> Option<&'a mut KmMat3> {
    // Check if pMat is None (equivalent to NULL check in C)
    let pMat = match pMat {
        Some(mat) => mat,
        None => return None,
    };

    // Ensure the slice has exactly 9 elements (size of kmMat3.mat)
    if pMat.len() != 9 {
        return None;
    }

    // Copy the data from pMat to pOut.mat
    pOut.mat.copy_from_slice(pMat);

    Some(pOut)
}
pub fn kmMat3Adjugate<'a>(pOut: &'a mut KmMat3, pIn: &KmMat3) -> &'a mut KmMat3 {
    pOut.mat[0] = (pIn.mat[4] * pIn.mat[8]) - (pIn.mat[5] * pIn.mat[7]);
    pOut.mat[1] = (pIn.mat[2] * pIn.mat[7]) - (pIn.mat[1] * pIn.mat[8]);
    pOut.mat[2] = (pIn.mat[1] * pIn.mat[5]) - (pIn.mat[2] * pIn.mat[4]);
    pOut.mat[3] = (pIn.mat[5] * pIn.mat[6]) - (pIn.mat[3] * pIn.mat[8]);
    pOut.mat[4] = (pIn.mat[0] * pIn.mat[8]) - (pIn.mat[2] * pIn.mat[6]);
    pOut.mat[5] = (pIn.mat[2] * pIn.mat[3]) - (pIn.mat[0] * pIn.mat[5]);
    pOut.mat[6] = (pIn.mat[3] * pIn.mat[7]) - (pIn.mat[4] * pIn.mat[6]);
    pOut.mat[7] = (pIn.mat[1] * pIn.mat[6]) - (pIn.mat[0] * pIn.mat[7]);
    pOut.mat[8] = (pIn.mat[0] * pIn.mat[4]) - (pIn.mat[1] * pIn.mat[3]);
    pOut
}
pub fn kmMat3Identity(pOut: &mut KmMat3) -> &mut KmMat3 {
    // Initialize all elements to 0.0 (equivalent to memset)
    pOut.mat = [0.0; 9];
    
    // Set diagonal elements to 1.0
    pOut.mat[0] = 1.0;
    pOut.mat[4] = 1.0;
    pOut.mat[8] = 1.0;
    
    pOut
}
pub fn kmMat3IsIdentity(pIn: &KmMat3) -> bool {
    static IDENTITY: [f32; 9] = [1.0f32, 0.0f32, 0.0f32, 
                                 0.0f32, 1.0f32, 0.0f32, 
                                 0.0f32, 0.0f32, 1.0f32];
    pIn.mat == IDENTITY
}
pub fn kmMat3Transpose<'a>(pOut: &'a mut KmMat3, pIn: &KmMat3) -> &'a mut KmMat3 {
    let temp = [
        pIn.mat[0], pIn.mat[3], pIn.mat[6],
        pIn.mat[1], pIn.mat[4], pIn.mat[7],
        pIn.mat[2], pIn.mat[5], pIn.mat[8],
    ];
    
    pOut.mat.copy_from_slice(&temp);
    pOut
}
pub fn kmMat3Determinant(pIn: Option<&KmMat3>) -> Option<f32> {
    // Check for NULL pointer equivalent
    let pIn = pIn?;

    let output = (((pIn.mat[0] * pIn.mat[4]) * pIn.mat[8]) + 
                 ((pIn.mat[1] * pIn.mat[5]) * pIn.mat[6])) + 
                ((pIn.mat[2] * pIn.mat[3]) * pIn.mat[7]);
    
    let output = output - (((pIn.mat[2] * pIn.mat[4]) * pIn.mat[6]) + 
                          ((pIn.mat[0] * pIn.mat[5]) * pIn.mat[7])) + 
                         ((pIn.mat[1] * pIn.mat[3]) * pIn.mat[8]);
    
    Some(output)
}
pub fn kmMat3Multiply<'a>(pOut: &'a mut KmMat3, pM1: &KmMat3, pM2: &KmMat3) -> &'a mut KmMat3 {
    let m1 = &pM1.mat;
    let m2 = &pM2.mat;
    let mat = [
        ((m1[0] * m2[0]) + (m1[3] * m2[1])) + (m1[6] * m2[2]),
        ((m1[1] * m2[0]) + (m1[4] * m2[1])) + (m1[7] * m2[2]),
        ((m1[2] * m2[0]) + (m1[5] * m2[1])) + (m1[8] * m2[2]),
        ((m1[0] * m2[3]) + (m1[3] * m2[4])) + (m1[6] * m2[5]),
        ((m1[1] * m2[3]) + (m1[4] * m2[4])) + (m1[7] * m2[5]),
        ((m1[2] * m2[3]) + (m1[5] * m2[4])) + (m1[8] * m2[5]),
        ((m1[0] * m2[6]) + (m1[3] * m2[7])) + (m1[6] * m2[8]),
        ((m1[1] * m2[6]) + (m1[4] * m2[7])) + (m1[7] * m2[8]),
        ((m1[2] * m2[6]) + (m1[5] * m2[7])) + (m1[8] * m2[8]),
    ];
    pOut.mat.copy_from_slice(&mat);
    pOut
}
pub fn kmMat3ScalarMultiply<'a>(pOut: &'a mut KmMat3, pM: &KmMat3, pFactor: f32) -> &'a mut KmMat3 {
    let mut mat = [0.0; 9];
    for i in 0..9 {
        mat[i] = pM.mat[i] * pFactor;
    }
    
    pOut.mat.copy_from_slice(&mat);
    pOut
}
pub fn kmMat3Assign<'a>(pOut: &'a mut KmMat3, pIn: &KmMat3) -> &'a mut KmMat3 {
    // Rust's assert! macro is equivalent to C's assert
    assert!(pOut as *const _ != pIn as *const _);
    
    // Use Rust's built-in copy for arrays instead of memcpy
    pOut.mat.copy_from_slice(&pIn.mat);
    
    pOut
}
pub fn kmMat3AreEqual(pMat1: Option<&KmMat3>, pMat2: Option<&KmMat3>) -> i32 {
    // Check if either input is None (equivalent to NULL in C)
    if pMat1.is_none() || pMat2.is_none() {
        return 0;
    }
    
    // Unwrap safely since we've checked for None
    let pMat1 = pMat1.unwrap();
    let pMat2 = pMat2.unwrap();
    
    // Check if they are the same reference (pointer equality in C)
    if std::ptr::eq(pMat1, pMat2) {
        return 1;
    }
    
    // Compare each element with floating point tolerance
    for i in 0..9 {
        if !((pMat1.mat[i] + 0.0001 > pMat2.mat[i]) && 
            (pMat1.mat[i] - 0.0001 < pMat2.mat[i])) {
            return 0;
        }
    }
    
    1
}

pub fn kmMat3RotationX(pOut: &mut KmMat3, radians: f32) -> &mut KmMat3 {
    pOut.mat[0] = 1.0f32;
    pOut.mat[1] = 0.0f32;
    pOut.mat[2] = 0.0f32;
    pOut.mat[3] = 0.0f32;
    pOut.mat[4] = radians.cos();
    pOut.mat[5] = radians.sin();
    pOut.mat[6] = 0.0f32;
    pOut.mat[7] = -radians.sin();
    pOut.mat[8] = radians.cos();
    pOut
}

pub fn kmMat3RotationY(pOut: &mut KmMat3, radians: f32) -> &mut KmMat3 {
    pOut.mat[0] = radians.cos();
    pOut.mat[1] = 0.0;
    pOut.mat[2] = -radians.sin();
    pOut.mat[3] = 0.0;
    pOut.mat[4] = 1.0;
    pOut.mat[5] = 0.0;
    pOut.mat[6] = radians.sin();
    pOut.mat[7] = 0.0;
    pOut.mat[8] = radians.cos();
    pOut
}

pub fn kmMat3RotationZ(pOut: &mut KmMat3, radians: f32) -> &mut KmMat3 {
    pOut.mat[0] = radians.cos();
    pOut.mat[1] = -radians.sin();
    pOut.mat[2] = 0.0f32;
    pOut.mat[3] = radians.sin();
    pOut.mat[4] = radians.cos();
    pOut.mat[5] = 0.0f32;
    pOut.mat[6] = 0.0f32;
    pOut.mat[7] = 0.0f32;
    pOut.mat[8] = 1.0f32;
    pOut
}

pub fn kmMat3Rotation(pOut: &mut KmMat3, radians: f32) -> &mut KmMat3 {
    pOut.mat[0] = radians.cos();
    pOut.mat[1] = radians.sin();
    pOut.mat[2] = 0.0;
    pOut.mat[3] = -radians.sin();
    pOut.mat[4] = radians.cos();
    pOut.mat[5] = 0.0;
    pOut.mat[6] = 0.0;
    pOut.mat[7] = 0.0;
    pOut.mat[8] = 1.0;
    pOut
}
pub fn kmMat3AssignMat4<'a>(pOut: &'a mut KmMat3, pIn: &KmMat4) -> &'a mut KmMat3 {
    pOut.mat[0] = pIn.mat[0];
    pOut.mat[1] = pIn.mat[1];
    pOut.mat[2] = pIn.mat[2];
    pOut.mat[3] = pIn.mat[4];
    pOut.mat[4] = pIn.mat[5];
    pOut.mat[5] = pIn.mat[6];
    pOut.mat[6] = pIn.mat[8];
    pOut.mat[7] = pIn.mat[9];
    pOut.mat[8] = pIn.mat[10];
    pOut
}
pub fn kmMat3Scaling(pOut: &mut KmMat3, x: f32, y: f32) -> &mut KmMat3 {
    kmMat3Identity(pOut);
    pOut.mat[0] = x;
    pOut.mat[4] = y;
    pOut
}
pub fn kmMat3Translation(pOut: &mut KmMat3, x: f32, y: f32) -> &mut KmMat3 {
    kmMat3Identity(pOut);
    pOut.mat[6] = x;
    pOut.mat[7] = y;
    pOut
}
pub fn km_mat3_rotation_quaternion<'a>(p_out: Option<&'a mut KmMat3>, p_in: Option<&KmQuaternion>) -> Option<&'a mut KmMat3> {
    // Check for null inputs (None in Rust)
    let p_in = p_in?;
    let p_out = p_out?;

    // Calculate the rotation matrix elements
    p_out.mat[0] = 1.0f32 - (2.0f32 * ((p_in.y * p_in.y) + (p_in.z * p_in.z)));
    p_out.mat[1] = 2.0f32 * ((p_in.x * p_in.y) - (p_in.w * p_in.z));
    p_out.mat[2] = 2.0f32 * ((p_in.x * p_in.z) + (p_in.w * p_in.y));
    p_out.mat[3] = 2.0f32 * ((p_in.x * p_in.y) + (p_in.w * p_in.z));
    p_out.mat[4] = 1.0f32 - (2.0f32 * ((p_in.x * p_in.x) + (p_in.z * p_in.z)));
    p_out.mat[5] = 2.0f32 * ((p_in.y * p_in.z) - (p_in.w * p_in.x));
    p_out.mat[6] = 2.0f32 * ((p_in.x * p_in.z) - (p_in.w * p_in.y));
    p_out.mat[7] = 2.0f32 * ((p_in.y * p_in.z) + (p_in.w * p_in.x));
    p_out.mat[8] = 1.0f32 - (2.0f32 * ((p_in.x * p_in.x) + (p_in.y * p_in.y)));

    Some(p_out)
}
pub fn km_mat3_rotation_axis_angle<'a>(p_out: &'a mut KmMat3, axis: &KmVec3, radians: f32) -> &'a mut KmMat3 {
    let rcos = radians.cos();
    let rsin = radians.sin();
    
    p_out.mat[0] = rcos + ((axis.x * axis.x) * (1.0 - rcos));
    p_out.mat[1] = (axis.z * rsin) + ((axis.y * axis.x) * (1.0 - rcos));
    p_out.mat[2] = ((-axis.y) * rsin) + ((axis.z * axis.x) * (1.0 - rcos));
    p_out.mat[3] = ((-axis.z) * rsin) + ((axis.x * axis.y) * (1.0 - rcos));
    p_out.mat[4] = rcos + ((axis.y * axis.y) * (1.0 - rcos));
    p_out.mat[5] = (axis.x * rsin) + ((axis.z * axis.y) * (1.0 - rcos));
    p_out.mat[6] = (axis.y * rsin) + ((axis.x * axis.z) * (1.0 - rcos));
    p_out.mat[7] = ((-axis.x) * rsin) + ((axis.y * axis.z) * (1.0 - rcos));
    p_out.mat[8] = rcos + ((axis.z * axis.z) * (1.0 - rcos));
    
    p_out
}
pub fn kmMat3GetUpVec3<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat3>) -> Option<&'a mut KmVec3> {
    // Check for NULL pointers (represented as None in Rust)
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Assign values from the matrix to the vector
    pOut.x = pIn.mat[3];
    pOut.y = pIn.mat[4];
    pOut.z = pIn.mat[5];
    
    // Create a new reference to avoid the borrowing conflict
    let p_out_ref = unsafe { &*(pOut as *const KmVec3) };
    kmVec3Normalize(Some(pOut), Some(p_out_ref))
}
pub fn kmMat3GetRightVec3<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat3>) -> Option<&'a mut KmVec3> {
    // Check for NULL pointers (represented as None in Rust)
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap safely since we've checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Assign values from pIn to pOut
    pOut.x = pIn.mat[0];
    pOut.y = pIn.mat[1];
    pOut.z = pIn.mat[2];

    // Normalize the vector and return the result
    kmVec3Normalize(Some(pOut), None)
}
pub fn kmMat3GetForwardVec3<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat3>) -> Option<&'a mut KmVec3> {
    // Check for NULL-equivalent inputs
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap safely since we checked for None
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Assign values from the matrix
    pOut.x = pIn.mat[6];
    pOut.y = pIn.mat[7];
    pOut.z = pIn.mat[8];
    
    // Create a temporary immutable reference for normalization
    let temp = KmVec3 {
        x: pOut.x,
        y: pOut.y,
        z: pOut.z,
    };
    
    // Normalize using the temporary copy
    kmVec3Normalize(Some(pOut), Some(&temp));
    
    // Return the modified pOut
    Some(pOut)
}
pub fn kmMat3Inverse<'a>(pOut: &'a mut KmMat3, pM: Option<&KmMat3>) -> Option<&'a mut KmMat3> {
    // Check if pM is None (equivalent to NULL check in C)
    let pM = match pM {
        Some(m) => m,
        None => return None,
    };

    // Calculate determinant using the provided function
    let determinate = match kmMat3Determinant(Some(pM)) {
        Some(d) => d,
        None => return None,
    };

    // Check if determinant is zero (non-invertible)
    if determinate == 0.0 {
        return None;
    }

    let detInv = 1.0 / determinate;
    let mut adjugate = KmMat3 { mat: [0.0; 9] };
    
    // Compute adjugate matrix
    kmMat3Adjugate(&mut adjugate, pM);
    
    // Scale by inverse determinant and store result in pOut
    kmMat3ScalarMultiply(pOut, &adjugate, detInv);
    
    Some(pOut)
}
pub fn kmMat3RotationToAxisAngle<'a>(
    mut pAxis: Option<&'a mut KmVec3>,
    radians: Option<&'a mut f32>,
    pIn: Option<&'a KmMat3>,
) -> Option<&'a mut KmVec3> {
    let mut temp = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };

    {
        let temp_ref = kmQuaternionRotationMatrix(&mut temp, pIn);
        if temp_ref.is_none() {
            return None;
        }
    }

    kmQuaternionToAxisAngle(Some(&temp), pAxis.as_deref_mut(), radians);
    pAxis
}
pub fn kmMat3LookAt<'a>(
    pOut: Option<&'a mut KmMat3>,
    pEye: Option<&KmVec3>,
    pCenter: Option<&KmVec3>,
    pUp: Option<&KmVec3>,
) -> Option<&'a mut KmMat3> {
    // Early return if any input is None
    let pOut = pOut?;
    let pEye = pEye?;
    let pCenter = pCenter?;
    let pUp = pUp?;

    // Create temporary vectors
    let mut f = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    let mut up = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    let mut s = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    let mut u = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };

    // Calculate forward vector (f) and normalize it
    kmVec3Subtract(&mut f, pCenter, pEye);
    let f_normalized = {
        let mut tmp = f.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&f)).unwrap();
        tmp
    };
    f = f_normalized;

    // Calculate up vector and normalize it
    kmVec3Assign(Some(&mut up), Some(pUp)).unwrap();
    let up_normalized = {
        let mut tmp = up.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&up)).unwrap();
        tmp
    };
    up = up_normalized;

    // Calculate right vector (s) and normalize it
    kmVec3Cross(&mut s, &f, &up);
    let s_normalized = {
        let mut tmp = s.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&s)).unwrap();
        tmp
    };
    s = s_normalized;

    // Recalculate up vector (u) to ensure orthogonality
    kmVec3Cross(&mut u, &s, &f);
    let s_normalized_again = {
        let mut tmp = s.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&s)).unwrap();
        tmp
    };
    s = s_normalized_again;

    // Fill the output matrix
    pOut.mat[0] = s.x;
    pOut.mat[3] = s.y;
    pOut.mat[6] = s.z;
    pOut.mat[1] = u.x;
    pOut.mat[4] = u.y;
    pOut.mat[7] = u.z;
    pOut.mat[2] = -f.x;
    pOut.mat[5] = -f.y;
    pOut.mat[8] = -f.z;

    Some(pOut)
}
