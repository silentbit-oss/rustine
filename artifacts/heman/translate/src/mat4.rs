use crate::*;
use std::assert;
use std::f32::consts::PI;
use std::f32::consts::SQRT_2;
use libm::sqrtf;
use lazy_static::lazy_static;
use rand::Rng;
pub fn kmMat4Fill<'a>(pOut: &'a mut KmMat4, pMat: Option<&[f32]>) -> Option<&'a mut KmMat4> {
    // Check if pMat is None (equivalent to NULL check in C)
    let pMat = pMat?;
    
    // Ensure the slice has exactly 16 elements (for a 4x4 matrix)
    if pMat.len() != 16 {
        return None;
    }

    // Copy the data from pMat to pOut.mat
    pOut.mat.copy_from_slice(pMat);
    
    Some(pOut)
}
pub fn kmMat4Identity(pOut: &mut KmMat4) -> &mut KmMat4 {
    // Equivalent to memset(pOut->mat, 0, (sizeof(float)) * 16)
    pOut.mat.fill(0.0);
    
    // Set diagonal elements to 1.0f
    pOut.mat[0] = 1.0;
    pOut.mat[5] = 1.0;
    pOut.mat[10] = 1.0;
    pOut.mat[15] = 1.0;
    
    pOut
}
pub fn kmMat4Inverse<'a>(pOut: &'a mut KmMat4, pM: &KmMat4) -> Option<&'a mut KmMat4> {
    let mut tmp = KmMat4 { mat: [0.0; 16] };
    
    tmp.mat[0] = ((((((pM.mat[5] * pM.mat[10]) * pM.mat[15]) - ((pM.mat[5] * pM.mat[11]) * pM.mat[14])) - ((pM.mat[9] * pM.mat[6]) * pM.mat[15])) + ((pM.mat[9] * pM.mat[7]) * pM.mat[14])) + ((pM.mat[13] * pM.mat[6]) * pM.mat[11])) - ((pM.mat[13] * pM.mat[7]) * pM.mat[10]);
    tmp.mat[4] = (((((((-pM.mat[4]) * pM.mat[10]) * pM.mat[15]) + ((pM.mat[4] * pM.mat[11]) * pM.mat[14])) + ((pM.mat[8] * pM.mat[6]) * pM.mat[15])) - ((pM.mat[8] * pM.mat[7]) * pM.mat[14])) - ((pM.mat[12] * pM.mat[6]) * pM.mat[11])) + ((pM.mat[12] * pM.mat[7]) * pM.mat[10]);
    tmp.mat[8] = ((((((pM.mat[4] * pM.mat[9]) * pM.mat[15]) - ((pM.mat[4] * pM.mat[11]) * pM.mat[13])) - ((pM.mat[8] * pM.mat[5]) * pM.mat[15])) + ((pM.mat[8] * pM.mat[7]) * pM.mat[13])) + ((pM.mat[12] * pM.mat[5]) * pM.mat[11])) - ((pM.mat[12] * pM.mat[7]) * pM.mat[9]);
    tmp.mat[12] = (((((((-pM.mat[4]) * pM.mat[9]) * pM.mat[14]) + ((pM.mat[4] * pM.mat[10]) * pM.mat[13])) + ((pM.mat[8] * pM.mat[5]) * pM.mat[14])) - ((pM.mat[8] * pM.mat[6]) * pM.mat[13])) - ((pM.mat[12] * pM.mat[5]) * pM.mat[10])) + ((pM.mat[12] * pM.mat[6]) * pM.mat[9]);
    tmp.mat[1] = (((((((-pM.mat[1]) * pM.mat[10]) * pM.mat[15]) + ((pM.mat[1] * pM.mat[11]) * pM.mat[14])) + ((pM.mat[9] * pM.mat[2]) * pM.mat[15])) - ((pM.mat[9] * pM.mat[3]) * pM.mat[14])) - ((pM.mat[13] * pM.mat[2]) * pM.mat[11])) + ((pM.mat[13] * pM.mat[3]) * pM.mat[10]);
    tmp.mat[5] = ((((((pM.mat[0] * pM.mat[10]) * pM.mat[15]) - ((pM.mat[0] * pM.mat[11]) * pM.mat[14])) - ((pM.mat[8] * pM.mat[2]) * pM.mat[15])) + ((pM.mat[8] * pM.mat[3]) * pM.mat[14])) + ((pM.mat[12] * pM.mat[2]) * pM.mat[11])) - ((pM.mat[12] * pM.mat[3]) * pM.mat[10]);
    tmp.mat[9] = (((((((-pM.mat[0]) * pM.mat[9]) * pM.mat[15]) + ((pM.mat[0] * pM.mat[11]) * pM.mat[13])) + ((pM.mat[8] * pM.mat[1]) * pM.mat[15])) - ((pM.mat[8] * pM.mat[3]) * pM.mat[13])) - ((pM.mat[12] * pM.mat[1]) * pM.mat[11])) + ((pM.mat[12] * pM.mat[3]) * pM.mat[9]);
    tmp.mat[13] = ((((((pM.mat[0] * pM.mat[9]) * pM.mat[14]) - ((pM.mat[0] * pM.mat[10]) * pM.mat[13])) - ((pM.mat[8] * pM.mat[1]) * pM.mat[14])) + ((pM.mat[8] * pM.mat[2]) * pM.mat[13])) + ((pM.mat[12] * pM.mat[1]) * pM.mat[10])) - ((pM.mat[12] * pM.mat[2]) * pM.mat[9]);
    tmp.mat[2] = ((((((pM.mat[1] * pM.mat[6]) * pM.mat[15]) - ((pM.mat[1] * pM.mat[7]) * pM.mat[14])) - ((pM.mat[5] * pM.mat[2]) * pM.mat[15])) + ((pM.mat[5] * pM.mat[3]) * pM.mat[14])) + ((pM.mat[13] * pM.mat[2]) * pM.mat[7])) - ((pM.mat[13] * pM.mat[3]) * pM.mat[6]);
    tmp.mat[6] = (((((((-pM.mat[0]) * pM.mat[6]) * pM.mat[15]) + ((pM.mat[0] * pM.mat[7]) * pM.mat[14])) + ((pM.mat[4] * pM.mat[2]) * pM.mat[15])) - ((pM.mat[4] * pM.mat[3]) * pM.mat[14])) - ((pM.mat[12] * pM.mat[2]) * pM.mat[7])) + ((pM.mat[12] * pM.mat[3]) * pM.mat[6]);
    tmp.mat[10] = ((((((pM.mat[0] * pM.mat[5]) * pM.mat[15]) - ((pM.mat[0] * pM.mat[7]) * pM.mat[13])) - ((pM.mat[4] * pM.mat[1]) * pM.mat[15])) + ((pM.mat[4] * pM.mat[3]) * pM.mat[13])) + ((pM.mat[12] * pM.mat[1]) * pM.mat[7])) - ((pM.mat[12] * pM.mat[3]) * pM.mat[5]);
    tmp.mat[14] = (((((((-pM.mat[0]) * pM.mat[5]) * pM.mat[14]) + ((pM.mat[0] * pM.mat[6]) * pM.mat[13])) + ((pM.mat[4] * pM.mat[1]) * pM.mat[14])) - ((pM.mat[4] * pM.mat[2]) * pM.mat[13])) - ((pM.mat[12] * pM.mat[1]) * pM.mat[6])) + ((pM.mat[12] * pM.mat[2]) * pM.mat[5]);
    tmp.mat[3] = (((((((-pM.mat[1]) * pM.mat[6]) * pM.mat[11]) + ((pM.mat[1] * pM.mat[7]) * pM.mat[10])) + ((pM.mat[5] * pM.mat[2]) * pM.mat[11])) - ((pM.mat[5] * pM.mat[3]) * pM.mat[10])) - ((pM.mat[9] * pM.mat[2]) * pM.mat[7])) + ((pM.mat[9] * pM.mat[3]) * pM.mat[6]);
    tmp.mat[7] = ((((((pM.mat[0] * pM.mat[6]) * pM.mat[11]) - ((pM.mat[0] * pM.mat[7]) * pM.mat[10])) - ((pM.mat[4] * pM.mat[2]) * pM.mat[11])) + ((pM.mat[4] * pM.mat[3]) * pM.mat[10])) + ((pM.mat[8] * pM.mat[2]) * pM.mat[7])) - ((pM.mat[8] * pM.mat[3]) * pM.mat[6]);
    tmp.mat[11] = (((((((-pM.mat[0]) * pM.mat[5]) * pM.mat[11]) + ((pM.mat[0] * pM.mat[7]) * pM.mat[9])) + ((pM.mat[4] * pM.mat[1]) * pM.mat[11])) - ((pM.mat[4] * pM.mat[3]) * pM.mat[9])) - ((pM.mat[8] * pM.mat[1]) * pM.mat[7])) + ((pM.mat[8] * pM.mat[3]) * pM.mat[5]);
    tmp.mat[15] = ((((((pM.mat[0] * pM.mat[5]) * pM.mat[10]) - ((pM.mat[0] * pM.mat[6]) * pM.mat[9])) - ((pM.mat[4] * pM.mat[1]) * pM.mat[10])) + ((pM.mat[4] * pM.mat[2]) * pM.mat[9])) + ((pM.mat[8] * pM.mat[1]) * pM.mat[6])) - ((pM.mat[8] * pM.mat[2]) * pM.mat[5]);

    let det = (((pM.mat[0] * tmp.mat[0]) + (pM.mat[1] * tmp.mat[4])) + (pM.mat[2] * tmp.mat[8])) + (pM.mat[3] * tmp.mat[12]);
    
    if det == 0.0 {
        return None;
    }
    
    let det = 1.0 / det;
    
    for i in 0..16 {
        pOut.mat[i] = tmp.mat[i] * det;
    }
    
    Some(pOut)
}
pub fn kmMat4IsIdentity(pIn: Option<&KmMat4>) -> bool {
    static IDENTITY: [f32; 16] = [
        1.0f32, 0.0f32, 0.0f32, 0.0f32,
        0.0f32, 1.0f32, 0.0f32, 0.0f32,
        0.0f32, 0.0f32, 1.0f32, 0.0f32,
        0.0f32, 0.0f32, 0.0f32, 1.0f32
    ];

    match pIn {
        Some(mat) => mat.mat == IDENTITY,
        None => false,
    }
}
pub fn kmMat4Transpose<'a>(pOut: &'a mut KmMat4, pIn: &KmMat4) -> &'a mut KmMat4 {
    for z in 0..4 {
        for x in 0..4 {
            pOut.mat[(z * 4) + x] = pIn.mat[(x * 4) + z];
        }
    }
    pOut
}
pub fn kmMat4Multiply<'a>(pOut: &'a mut KmMat4, pM1: &KmMat4, pM2: &KmMat4) -> &'a mut KmMat4 {
    let m1 = &pM1.mat;
    let m2 = &pM2.mat;
    let mut mat = [0.0; 16];

    mat[0] = (((m1[0] * m2[0]) + (m1[4] * m2[1])) + (m1[8] * m2[2])) + (m1[12] * m2[3]);
    mat[1] = (((m1[1] * m2[0]) + (m1[5] * m2[1])) + (m1[9] * m2[2])) + (m1[13] * m2[3]);
    mat[2] = (((m1[2] * m2[0]) + (m1[6] * m2[1])) + (m1[10] * m2[2])) + (m1[14] * m2[3]);
    mat[3] = (((m1[3] * m2[0]) + (m1[7] * m2[1])) + (m1[11] * m2[2])) + (m1[15] * m2[3]);
    mat[4] = (((m1[0] * m2[4]) + (m1[4] * m2[5])) + (m1[8] * m2[6])) + (m1[12] * m2[7]);
    mat[5] = (((m1[1] * m2[4]) + (m1[5] * m2[5])) + (m1[9] * m2[6])) + (m1[13] * m2[7]);
    mat[6] = (((m1[2] * m2[4]) + (m1[6] * m2[5])) + (m1[10] * m2[6])) + (m1[14] * m2[7]);
    mat[7] = (((m1[3] * m2[4]) + (m1[7] * m2[5])) + (m1[11] * m2[6])) + (m1[15] * m2[7]);
    mat[8] = (((m1[0] * m2[8]) + (m1[4] * m2[9])) + (m1[8] * m2[10])) + (m1[12] * m2[11]);
    mat[9] = (((m1[1] * m2[8]) + (m1[5] * m2[9])) + (m1[9] * m2[10])) + (m1[13] * m2[11]);
    mat[10] = (((m1[2] * m2[8]) + (m1[6] * m2[9])) + (m1[10] * m2[10])) + (m1[14] * m2[11]);
    mat[11] = (((m1[3] * m2[8]) + (m1[7] * m2[9])) + (m1[11] * m2[10])) + (m1[15] * m2[11]);
    mat[12] = (((m1[0] * m2[12]) + (m1[4] * m2[13])) + (m1[8] * m2[14])) + (m1[12] * m2[15]);
    mat[13] = (((m1[1] * m2[12]) + (m1[5] * m2[13])) + (m1[9] * m2[14])) + (m1[13] * m2[15]);
    mat[14] = (((m1[2] * m2[12]) + (m1[6] * m2[13])) + (m1[10] * m2[14])) + (m1[14] * m2[15]);
    mat[15] = (((m1[3] * m2[12]) + (m1[7] * m2[13])) + (m1[11] * m2[14])) + (m1[15] * m2[15]);

    pOut.mat.copy_from_slice(&mat);
    pOut
}
pub fn kmMat4Assign<'a>(pOut: &'a mut KmMat4, pIn: &KmMat4) -> &'a mut KmMat4 {
    assert!(pOut as *const _ != pIn as *const _, "You have tried to self-assign!!");
    pOut.mat.copy_from_slice(&pIn.mat);
    pOut
}

pub fn km_mat4_are_equal(p_mat1: &KmMat4, p_mat2: &KmMat4) -> bool {
    // Assert that the two matrices are not the same object (address comparison)
    assert!(p_mat1 as *const _ != p_mat2 as *const _, "You are comparing the same thing!");

    // Compare each element with a tolerance of 0.0001
    for i in 0..16 {
        if !((p_mat1.mat[i] + 0.0001 > p_mat2.mat[i]) && (p_mat1.mat[i] - 0.0001 < p_mat2.mat[i])) {
            return false;
        }
    }

    true
}

pub fn kmMat4RotationX(pOut: &mut KmMat4, radians: f32) -> &mut KmMat4 {
    pOut.mat[0] = 1.0f32;
    pOut.mat[1] = 0.0f32;
    pOut.mat[2] = 0.0f32;
    pOut.mat[3] = 0.0f32;
    pOut.mat[4] = 0.0f32;
    pOut.mat[5] = radians.cos();
    pOut.mat[6] = radians.sin();
    pOut.mat[7] = 0.0f32;
    pOut.mat[8] = 0.0f32;
    pOut.mat[9] = -radians.sin();
    pOut.mat[10] = radians.cos();
    pOut.mat[11] = 0.0f32;
    pOut.mat[12] = 0.0f32;
    pOut.mat[13] = 0.0f32;
    pOut.mat[14] = 0.0f32;
    pOut.mat[15] = 1.0f32;
    pOut
}

pub fn kmMat4RotationY(pOut: &mut KmMat4, radians: f32) -> &mut KmMat4 {
    pOut.mat[0] = radians.cos();
    pOut.mat[1] = 0.0;
    pOut.mat[2] = -radians.sin();
    pOut.mat[3] = 0.0;
    pOut.mat[4] = 0.0;
    pOut.mat[5] = 1.0;
    pOut.mat[6] = 0.0;
    pOut.mat[7] = 0.0;
    pOut.mat[8] = radians.sin();
    pOut.mat[9] = 0.0;
    pOut.mat[10] = radians.cos();
    pOut.mat[11] = 0.0;
    pOut.mat[12] = 0.0;
    pOut.mat[13] = 0.0;
    pOut.mat[14] = 0.0;
    pOut.mat[15] = 1.0;
    pOut
}

pub fn kmMat4RotationZ(pOut: &mut KmMat4, radians: f32) -> &mut KmMat4 {
    pOut.mat[0] = radians.cos();
    pOut.mat[1] = radians.sin();
    pOut.mat[2] = 0.0;
    pOut.mat[3] = 0.0;
    pOut.mat[4] = -radians.sin();
    pOut.mat[5] = radians.cos();
    pOut.mat[6] = 0.0;
    pOut.mat[7] = 0.0;
    pOut.mat[8] = 0.0;
    pOut.mat[9] = 0.0;
    pOut.mat[10] = 1.0;
    pOut.mat[11] = 0.0;
    pOut.mat[12] = 0.0;
    pOut.mat[13] = 0.0;
    pOut.mat[14] = 0.0;
    pOut.mat[15] = 1.0;
    
    pOut
}
pub fn kmMat4Scaling(pOut: &mut KmMat4, x: f32, y: f32, z: f32) -> &mut KmMat4 {
    // Initialize all elements to 0.0 (equivalent to memset)
    pOut.mat = [0.0; 16];
    
    // Set the diagonal elements
    pOut.mat[0] = x;
    pOut.mat[5] = y;
    pOut.mat[10] = z;
    pOut.mat[15] = 1.0;
    
    pOut
}
pub fn kmMat4Translation(pOut: &mut KmMat4, x: f32, y: f32, z: f32) -> &mut KmMat4 {
    // Initialize all elements to 0.0 (equivalent to memset)
    pOut.mat = [0.0; 16];
    
    // Set diagonal elements to 1.0 and translation components
    pOut.mat[0] = 1.0;
    pOut.mat[5] = 1.0;
    pOut.mat[10] = 1.0;
    pOut.mat[12] = x;
    pOut.mat[13] = y;
    pOut.mat[14] = z;
    pOut.mat[15] = 1.0;
    
    pOut
}
pub fn km_mat4_rotation_quaternion<'a>(p_out: &'a mut KmMat4, p_q: &KmQuaternion) -> &'a mut KmMat4 {
    let xx = p_q.x * p_q.x;
    let xy = p_q.x * p_q.y;
    let xz = p_q.x * p_q.z;
    let xw = p_q.x * p_q.w;
    let yy = p_q.y * p_q.y;
    let yz = p_q.y * p_q.z;
    let yw = p_q.y * p_q.w;
    let zz = p_q.z * p_q.z;
    let zw = p_q.z * p_q.w;

    p_out.mat[0] = (1.0 - 2.0 * (yy + zz)) as f32;
    p_out.mat[1] = (2.0 * (xy + zw)) as f32;
    p_out.mat[2] = (2.0 * (xz - yw)) as f32;
    p_out.mat[3] = 0.0;
    p_out.mat[4] = (2.0 * (xy - zw)) as f32;
    p_out.mat[5] = (1.0 - 2.0 * (xx + zz)) as f32;
    p_out.mat[6] = (2.0 * (yz + xw)) as f32;
    p_out.mat[7] = 0.0;
    p_out.mat[8] = (2.0 * (xz + yw)) as f32;
    p_out.mat[9] = (2.0 * (yz - xw)) as f32;
    p_out.mat[10] = (1.0 - 2.0 * (xx + yy)) as f32;
    p_out.mat[11] = 0.0;
    p_out.mat[12] = 0.0;
    p_out.mat[13] = 0.0;
    p_out.mat[14] = 0.0;
    p_out.mat[15] = 1.0;

    p_out
}
pub fn kmMat4OrthographicProjection(
    pOut: &mut KmMat4,
    left: f32,
    right: f32,
    bottom: f32,
    top: f32,
    nearVal: f32,
    farVal: f32,
) -> &mut KmMat4 {
    let tx = -((right + left) / (right - left));
    let ty = -((top + bottom) / (top - bottom));
    let tz = -((farVal + nearVal) / (farVal - nearVal));
    
    kmMat4Identity(pOut);
    
    pOut.mat[0] = 2.0 / (right - left);
    pOut.mat[5] = 2.0 / (top - bottom);
    pOut.mat[10] = -2.0 / (farVal - nearVal);
    pOut.mat[12] = tx;
    pOut.mat[13] = ty;
    pOut.mat[14] = tz;
    
    pOut
}
pub fn kmMat4ExtractRotation<'a>(pOut: &'a mut KmMat3, pIn: &KmMat4) -> &'a mut KmMat3 {
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
pub fn kmMat4ExtractPlane<'a>(pOut: &'a mut KmPlane, pIn: &KmMat4, plane: u32) -> &'a mut KmPlane {
    let t = 1.0f32;
    match plane {
        1 => {
            pOut.a = pIn.mat[3] - pIn.mat[0];
            pOut.b = pIn.mat[7] - pIn.mat[4];
            pOut.c = pIn.mat[11] - pIn.mat[8];
            pOut.d = pIn.mat[15] - pIn.mat[12];
        }
        0 => {
            pOut.a = pIn.mat[3] + pIn.mat[0];
            pOut.b = pIn.mat[7] + pIn.mat[4];
            pOut.c = pIn.mat[11] + pIn.mat[8];
            pOut.d = pIn.mat[15] + pIn.mat[12];
        }
        2 => {
            pOut.a = pIn.mat[3] + pIn.mat[1];
            pOut.b = pIn.mat[7] + pIn.mat[5];
            pOut.c = pIn.mat[11] + pIn.mat[9];
            pOut.d = pIn.mat[15] + pIn.mat[13];
        }
        3 => {
            pOut.a = pIn.mat[3] - pIn.mat[1];
            pOut.b = pIn.mat[7] - pIn.mat[5];
            pOut.c = pIn.mat[11] - pIn.mat[9];
            pOut.d = pIn.mat[15] - pIn.mat[13];
        }
        5 => {
            pOut.a = pIn.mat[3] - pIn.mat[2];
            pOut.b = pIn.mat[7] - pIn.mat[6];
            pOut.c = pIn.mat[11] - pIn.mat[10];
            pOut.d = pIn.mat[15] - pIn.mat[14];
        }
        4 => {
            pOut.a = pIn.mat[3] + pIn.mat[2];
            pOut.b = pIn.mat[7] + pIn.mat[6];
            pOut.c = pIn.mat[11] + pIn.mat[10];
            pOut.d = pIn.mat[15] + pIn.mat[14];
        }
        _ => {
            panic!("Invalid plane index");
        }
    }

    let t = sqrtf((pOut.a * pOut.a + pOut.b * pOut.b) + pOut.c * pOut.c);
    pOut.a /= t;
    pOut.b /= t;
    pOut.c /= t;
    pOut.d /= t;
    pOut
}
pub fn kmMat4AssignMat3<'a>(pOut: &'a mut KmMat4, pIn: Option<&KmMat3>) -> Option<&'a mut KmMat4> {
    // Check for NULL pointer (None in Rust)
    let pIn = match pIn {
        Some(mat) => mat,
        None => return None,
    };

    // Initialize the matrix to identity
    kmMat4Identity(pOut);

    // Assign values from 3x3 matrix to 4x4 matrix
    pOut.mat[0] = pIn.mat[0];
    pOut.mat[1] = pIn.mat[1];
    pOut.mat[2] = pIn.mat[2];
    pOut.mat[3] = 0.0;
    pOut.mat[4] = pIn.mat[3];
    pOut.mat[5] = pIn.mat[4];
    pOut.mat[6] = pIn.mat[5];
    pOut.mat[7] = 0.0;
    pOut.mat[8] = pIn.mat[6];
    pOut.mat[9] = pIn.mat[7];
    pOut.mat[10] = pIn.mat[8];
    pOut.mat[11] = 0.0;

    Some(pOut)
}
pub fn km_mat4_rotation_translation<'a>(
    p_out: &'a mut KmMat4,
    rotation: Option<&'a KmMat3>,
    translation: Option<&'a KmVec3>,
) -> Option<&'a mut KmMat4> {
    // Check for None (equivalent to NULL checks in C)
    let rotation = rotation?;
    let translation = translation?;

    // Assign rotation matrix components
    p_out.mat[0] = rotation.mat[0];
    p_out.mat[1] = rotation.mat[1];
    p_out.mat[2] = rotation.mat[2];
    p_out.mat[3] = 0.0f32;
    p_out.mat[4] = rotation.mat[3];
    p_out.mat[5] = rotation.mat[4];
    p_out.mat[6] = rotation.mat[5];
    p_out.mat[7] = 0.0f32;
    p_out.mat[8] = rotation.mat[6];
    p_out.mat[9] = rotation.mat[7];
    p_out.mat[10] = rotation.mat[8];
    p_out.mat[11] = 0.0f32;

    // Assign translation components
    p_out.mat[12] = translation.x;
    p_out.mat[13] = translation.y;
    p_out.mat[14] = translation.z;
    p_out.mat[15] = 1.0f32;

    Some(p_out)
}

pub fn kmMat4PerspectiveProjection(
    pOut: Option<&mut KmMat4>,
    fovY: f32,
    aspect: f32,
    zNear: f32,
    zFar: f32,
) -> Option<&mut KmMat4> {
    // Check for None (equivalent to NULL check in C)
    let pOut = pOut?;

    let r = kmDegreesToRadians(fovY / 2.0);
    let deltaZ = zFar - zNear;
    let s = r.sin();
    
    // Early return if any of the conditions are met (equivalent to line 7-10 in C)
    if deltaZ == 0.0 || s == 0.0 || aspect == 0.0 {
        return None;
    }

    let cotangent = r.cos() / s;

    kmMat4Identity(pOut);
    
    // Modify the matrix elements directly
    pOut.mat[0] = cotangent / aspect;
    pOut.mat[5] = cotangent;
    pOut.mat[10] = (-(zFar + zNear)) / deltaZ;
    pOut.mat[11] = -1.0;
    pOut.mat[14] = ((-2.0) * zNear * zFar) / deltaZ;
    pOut.mat[15] = 0.0;

    Some(pOut)
}
pub fn kmMat4RotationYawPitchRoll(pOut: &mut KmMat4, pitch: f32, yaw: f32, roll: f32) -> &mut KmMat4 {
    let mut yaw_matrix = KmMat4 { mat: [0.0; 16] };
    kmMat4RotationY(&mut yaw_matrix, yaw);
    
    let mut pitch_matrix = KmMat4 { mat: [0.0; 16] };
    kmMat4RotationX(&mut pitch_matrix, pitch);
    
    let mut roll_matrix = KmMat4 { mat: [0.0; 16] };
    kmMat4RotationZ(&mut roll_matrix, roll);
    
    let mut temp = KmMat4 { mat: [0.0; 16] };
    kmMat4Multiply(&mut temp, &pitch_matrix, &roll_matrix);
    kmMat4Multiply(pOut, &yaw_matrix, &temp)
}
pub fn kmMat4GetUpVec3<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat4>) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap the options safely since we've checked they're Some
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // First operation - multiply
    kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Y, pIn);
    
    // Create a temporary immutable reference for normalization
    let temp = unsafe { &*(pOut as *const KmVec3) };
    
    // Second operation - normalize
    let normalized = kmVec3Normalize(Some(pOut), Some(temp));
    
    // Return the result
    normalized
}
pub fn kmMat4GetRightVec3<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat4>) -> Option<&'a mut KmVec3> {
    // Check for NULL-equivalent inputs (None in Rust)
    if pOut.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap the Options safely since we've checked they're Some
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Perform the operations in sequence
    kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_X, pIn);
    
    // Create a temporary immutable reference for normalization
    let temp = unsafe { &*(pOut as *const KmVec3) };
    kmVec3Normalize(Some(pOut), Some(temp));

    Some(pOut)
}
pub fn kmMat4GetForwardVec3RH<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat4>) -> Option<&'a mut KmVec3> {
    // Check for NULL-equivalent inputs
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap the options safely
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Perform the vector multiplication
    kmVec3MultiplyMat4(pOut, &KM_VEC3_NEG_Z, pIn);
    
    // Create a temporary immutable reference for normalization
    let temp = unsafe { &*(pOut as *const KmVec3) };
    
    // Normalize the result using the temporary reference
    kmVec3Normalize(Some(pOut), Some(temp))
}
pub fn kmMat4GetForwardVec3LH<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmMat4>) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pIn = pIn?;

    // Perform the operations
    kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Z, pIn);
    let temp = unsafe { &*(pOut as *const KmVec3) }; // Create a temporary immutable reference
    kmVec3Normalize(Some(pOut), Some(temp));

    Some(pOut)
}

pub fn km_mat4_rotation_axis_angle<'a>(
    p_out: &'a mut KmMat4,
    axis: Option<&'a KmVec3>,
    radians: f32,
) -> Option<&'a mut KmMat4> {
    let mut quat = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };

    kmQuaternionRotationAxisAngle(&mut quat, axis, radians)?;
    Some(km_mat4_rotation_quaternion(p_out, &quat))
}
pub fn kmMat4RotationToAxisAngle<'a>(
    pAxis: Option<&'a mut KmVec3>,
    radians: Option<&'a mut f32>,
    pIn: Option<&'a KmMat4>,
) -> Option<&'a mut KmVec3> {
    // Early return if any required input is None
    if pAxis.is_none() || radians.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap the options safely since we've checked they're Some
    let pAxis = pAxis.unwrap();
    let radians = radians.unwrap();
    let pIn = pIn.unwrap();

    let mut temp = KmQuaternion {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    let mut rotation = KmMat3 { mat: [0.0; 9] };

    // Extract rotation matrix
    kmMat4ExtractRotation(&mut rotation, pIn);

    // Convert rotation matrix to quaternion
    kmQuaternionRotationMatrix(&mut temp, Some(&rotation));

    // Convert quaternion to axis-angle representation
    kmQuaternionToAxisAngle(Some(&temp), Some(pAxis), Some(radians));

    Some(pAxis)
}
pub fn kmMat4LookAt<'a>(
    pOut: &'a mut KmMat4,
    pEye: Option<&KmVec3>,
    pCenter: Option<&KmVec3>,
    pUp: Option<&KmVec3>,
) -> Option<&'a mut KmMat4> {
    // Check for NULL pointers (None in Rust)
    if pEye.is_none() || pCenter.is_none() || pUp.is_none() {
        return None;
    }

    // Unwrap the options safely since we've checked they're Some
    let pEye = pEye.unwrap();
    let pCenter = pCenter.unwrap();
    let pUp = pUp.unwrap();

    // Declare vectors
    let mut f = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut up = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut s = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut u = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut translate = KmMat4 { mat: [0.0; 16] };

    // Calculate forward vector and normalize
    kmVec3Subtract(&mut f, pCenter, pEye);
    let f_normalized = {
        let mut tmp = f.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&f));
        tmp
    };
    f = f_normalized;

    // Calculate up vector and normalize
    kmVec3Assign(Some(&mut up), Some(pUp));
    let up_normalized = {
        let mut tmp = up.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&up));
        tmp
    };
    up = up_normalized;

    // Calculate right vector and normalize
    kmVec3Cross(&mut s, &f, &up);
    let s_normalized = {
        let mut tmp = s.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&s));
        tmp
    };
    s = s_normalized;

    // Recalculate up vector
    kmVec3Cross(&mut u, &s, &f);
    let s_normalized_again = {
        let mut tmp = s.clone();
        kmVec3Normalize(Some(&mut tmp), Some(&s));
        tmp
    };
    s = s_normalized_again;

    // Set the rotation part of the matrix
    kmMat4Identity(pOut);
    pOut.mat[0] = s.x;
    pOut.mat[4] = s.y;
    pOut.mat[8] = s.z;
    pOut.mat[1] = u.x;
    pOut.mat[5] = u.y;
    pOut.mat[9] = u.z;
    pOut.mat[2] = -f.x;
    pOut.mat[6] = -f.y;
    pOut.mat[10] = -f.z;

    // Create translation matrix and multiply
    kmMat4Translation(&mut translate, -pEye.x, -pEye.y, -pEye.z);
    let temp_out = pOut.clone();
    kmMat4Multiply(pOut, &temp_out, &translate);

    Some(pOut)
}
