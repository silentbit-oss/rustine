use crate::*;
use std::f32;
use std::f32::consts::PI;

pub fn kmVec3Fill(pOut: &mut KmVec3, x: f32, y: f32, z: f32) -> &mut KmVec3 {
    pOut.x = x;
    pOut.y = y;
    pOut.z = z;
    pOut
}
pub fn kmVec3Lerp<'a>(pOut: &'a mut KmVec3, pV1: &KmVec3, pV2: &KmVec3, t: f32) -> &'a mut KmVec3 {
    pOut.x = pV1.x + (t * (pV2.x - pV1.x));
    pOut.y = pV1.y + (t * (pV2.y - pV1.y));
    pOut.z = pV1.z + (t * (pV2.z - pV1.z));
    pOut
}
pub fn kmVec3Cross<'a>(pOut: &'a mut KmVec3, pV1: &KmVec3, pV2: &KmVec3) -> &'a mut KmVec3 {
    let v = KmVec3 {
        x: (pV1.y * pV2.z) - (pV1.z * pV2.y),
        y: (pV1.z * pV2.x) - (pV1.x * pV2.z),
        z: (pV1.x * pV2.y) - (pV1.y * pV2.x),
    };
    
    *pOut = v;
    pOut
}
pub fn kmVec3Dot(pV1: Option<&KmVec3>, pV2: Option<&KmVec3>) -> Option<f32> {
    // Check for None (equivalent to NULL checks in C)
    if pV1.is_none() || pV2.is_none() {
        return None;
    }

    // Unwrap safely since we've checked for None
    let pV1 = pV1.unwrap();
    let pV2 = pV2.unwrap();

    // Calculate dot product
    Some((pV1.x * pV2.x) + (pV1.y * pV2.y) + (pV1.z * pV2.z))
}
pub fn kmVec3Add<'a>(pOut: &'a mut KmVec3, pV1: &KmVec3, pV2: &KmVec3) -> &'a mut KmVec3 {
    let v = KmVec3 {
        x: pV1.x + pV2.x,
        y: pV1.y + pV2.y,
        z: pV1.z + pV2.z,
    };
    
    *pOut = v;
    pOut
}
pub fn kmVec3Subtract<'a>(pOut: &'a mut KmVec3, pV1: &KmVec3, pV2: &KmVec3) -> &'a mut KmVec3 {
    let v = KmVec3 {
        x: pV1.x - pV2.x,
        y: pV1.y - pV2.y,
        z: pV1.z - pV2.z,
    };
    
    *pOut = v;
    pOut
}
pub fn kmVec3Mul<'a>(pOut: &'a mut KmVec3, pV1: &KmVec3, pV2: &KmVec3) -> &'a mut KmVec3 {
    pOut.x = pV1.x * pV2.x;
    pOut.y = pV1.y * pV2.y;
    pOut.z = pV1.z * pV2.z;
    pOut
}
pub fn kmVec3Div<'a>(pOut: &'a mut KmVec3, pV1: &KmVec3, pV2: &KmVec3) -> Option<&'a mut KmVec3> {
    if pV2.x != 0.0 && pV2.y != 0.0 && pV2.z != 0.0 {
        pOut.x = pV1.x / pV2.x;
        pOut.y = pV1.y / pV2.y;
        pOut.z = pV1.z / pV2.z;
        Some(pOut)
    } else {
        None
    }
}
pub fn kmVec3Scale<'a>(pOut: &'a mut KmVec3, pIn: &KmVec3, s: f32) -> &'a mut KmVec3 {
    pOut.x = pIn.x * s;
    pOut.y = pIn.y * s;
    pOut.z = pIn.z * s;
    pOut
}
pub fn kmVec3AreEqual(p1: Option<&KmVec3>, p2: Option<&KmVec3>) -> i32 {
    // Check for None (equivalent to NULL in C)
    if p1.is_none() || p2.is_none() {
        return 0;
    }

    // Unwrap safely since we've checked for None
    let p1 = p1.unwrap();
    let p2 = p2.unwrap();

    // Compare each component with epsilon tolerance
    if ((p1.x < (p2.x + 0.0001) && p1.x > (p2.x - 0.0001)) &&
        (p1.y < (p2.y + 0.0001) && p1.y > (p2.y - 0.0001)) &&
        (p1.z < (p2.z + 0.0001) && p1.z > (p2.z - 0.0001))) {
        1
    } else {
        0
    }
}
pub fn kmVec3Assign<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmVec3>) -> Option<&'a mut KmVec3> {
    // Check if either input is None (equivalent to NULL check in C)
    if pOut.is_none() || pIn.is_none() {
        return Option::None;
    }

    // Unwrap the Options safely
    let pOut = pOut.unwrap();
    let pIn = pIn.unwrap();

    // Check if they point to the same memory location (Rust references can't alias mutably)
    if std::ptr::eq(pOut, pIn) {
        return Some(pOut);
    }

    // Assign values
    pOut.x = pIn.x;
    pOut.y = pIn.y;
    pOut.z = pIn.z;

    Some(pOut)
}
pub fn kmVec3Zero(pOut: Option<&mut KmVec3>) -> Option<&mut KmVec3> {
    // Check if pOut is None (equivalent to NULL check in C)
    let pOut = pOut?;  // Early return if None

    // Modify the struct fields
    pOut.x = 0.0f32;
    pOut.y = 0.0f32;
    pOut.z = 0.0f32;

    Some(pOut)  // Return the modified struct
}

pub fn kmVec3Length(pIn: Option<&KmVec3>) -> f32 {
    match pIn {
        Some(pIn) => {
            let sum = kmSQR(pIn.x) + kmSQR(pIn.y) + kmSQR(pIn.z);
            sum.sqrt()
        }
        None => f32::NAN, // Return NaN for NULL input (similar to C's undefined behavior)
    }
}
pub fn kmVec3LengthSq(pIn: Option<&KmVec3>) -> f32 {
    match pIn {
        Some(vec) => (kmSQR(vec.x) + kmSQR(vec.y)) + kmSQR(vec.z),
        None => 0.0, // Default behavior when None is passed (similar to NULL in C)
    }
}
pub fn kmVec3MultiplyMat3<'a>(pOut: &'a mut KmVec3, pV: &KmVec3, pM: &KmMat3) -> &'a mut KmVec3 {
    let v = KmVec3 {
        x: (pV.x * pM.mat[0]) + (pV.y * pM.mat[3]) + (pV.z * pM.mat[6]),
        y: (pV.x * pM.mat[1]) + (pV.y * pM.mat[4]) + (pV.z * pM.mat[7]),
        z: (pV.x * pM.mat[2]) + (pV.y * pM.mat[5]) + (pV.z * pM.mat[8]),
    };

    pOut.x = v.x;
    pOut.y = v.y;
    pOut.z = v.z;

    pOut
}
pub fn kmVec3MultiplyMat4<'a>(pOut: &'a mut KmVec3, pV: &'a KmVec3, pM: &'a KmMat4) -> &'a mut KmVec3 {
    let v = KmVec3 {
        x: ((pV.x * pM.mat[0]) + (pV.y * pM.mat[4]) + (pV.z * pM.mat[8])) + pM.mat[12],
        y: ((pV.x * pM.mat[1]) + (pV.y * pM.mat[5]) + (pV.z * pM.mat[9])) + pM.mat[13],
        z: ((pV.x * pM.mat[2]) + (pV.y * pM.mat[6]) + (pV.z * pM.mat[10])) + pM.mat[14],
    };
    
    *pOut = v;
    pOut
}
pub fn kmVec3TransformNormal<'a>(
    pOut: Option<&'a mut KmVec3>,
    pV: Option<&'a KmVec3>,
    pM: Option<&'a KmMat4>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pV = pV?;
    let pM = pM?;

    let v = KmVec3 {
        x: (pV.x * pM.mat[0]) + (pV.y * pM.mat[4]) + (pV.z * pM.mat[8]),
        y: (pV.x * pM.mat[1]) + (pV.y * pM.mat[5]) + (pV.z * pM.mat[9]),
        z: (pV.x * pM.mat[2]) + (pV.y * pM.mat[6]) + (pV.z * pM.mat[10]),
    };

    pOut.x = v.x;
    pOut.y = v.y;
    pOut.z = v.z;

    Some(pOut)
}
pub fn kmVec3InverseTransform<'a>(
    pOut: Option<&'a mut KmVec3>,
    pVect: Option<&'a KmVec3>,
    pM: Option<&'a KmMat4>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || pVect.is_none() || pM.is_none() {
        return None;
    }

    // Unwrap the options safely
    let pOut = pOut.unwrap();
    let pVect = pVect.unwrap();
    let pM = pM.unwrap();

    // Create v1 and v2 vectors
    let v1 = KmVec3 {
        x: pVect.x - pM.mat[12],
        y: pVect.y - pM.mat[13],
        z: pVect.z - pM.mat[14],
    };

    let v2 = KmVec3 {
        x: (v1.x * pM.mat[0]) + (v1.y * pM.mat[1]) + (v1.z * pM.mat[2]),
        y: (v1.x * pM.mat[4]) + (v1.y * pM.mat[5]) + (v1.z * pM.mat[6]),
        z: (v1.x * pM.mat[8]) + (v1.y * pM.mat[9]) + (v1.z * pM.mat[10]),
    };

    // Update pOut
    pOut.x = v2.x;
    pOut.y = v2.y;
    pOut.z = v2.z;

    Some(pOut)
}
pub fn kmVec3InverseTransformNormal<'a>(
    pOut: Option<&'a mut KmVec3>,
    pVect: Option<&'a KmVec3>,
    pM: Option<&'a KmMat4>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pVect = pVect?;
    let pM = pM?;

    let v = KmVec3 {
        x: (pVect.x * pM.mat[0]) + (pVect.y * pM.mat[1]) + (pVect.z * pM.mat[2]),
        y: (pVect.x * pM.mat[4]) + (pVect.y * pM.mat[5]) + (pVect.z * pM.mat[6]),
        z: (pVect.x * pM.mat[8]) + (pVect.y * pM.mat[9]) + (pVect.z * pM.mat[10]),
    };

    *pOut = v;
    Some(pOut)
}
pub fn kmVec3GetHorizontalAngle<'a>(p_out: &'a mut KmVec3, p_in: &KmVec3) -> &'a mut KmVec3 {
    let z1 = (p_in.x * p_in.x + p_in.z * p_in.z).sqrt();
    
    // Calculate and adjust y component
    p_out.y = kmRadiansToDegrees(p_in.x.atan2(p_in.z));
    if p_out.y < 0.0 {
        p_out.y += 360.0;
    }
    if p_out.y >= 360.0 {
        p_out.y -= 360.0;
    }

    // Calculate and adjust x component
    p_out.x = kmRadiansToDegrees(z1.atan2(p_in.y)) - 90.0;
    if p_out.x < 0.0 {
        p_out.x += 360.0;
    }
    if p_out.x >= 360.0 {
        p_out.x -= 360.0;
    }

    p_out
}
pub fn kmVec3RotationToDirection<'a>(
    pOut: Option<&'a mut KmVec3>,
    pIn: Option<&'a KmVec3>,
    forwards: Option<&'a KmVec3>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    let pOut = pOut?;
    let pIn = pIn?;
    let forwards = forwards?;

    let xr = kmDegreesToRadians(pIn.x);
    let yr = kmDegreesToRadians(pIn.y);
    let zr = kmDegreesToRadians(pIn.z);

    let cr = xr.cos();
    let sr = xr.sin();
    let cp = yr.cos();
    let sp = yr.sin();
    let cy = zr.cos();
    let sy = zr.sin();

    let srsp = sr * sp;
    let crsp = cr * sp;

    let pseudoMatrix = [
        cp * cy,
        cp * sy,
        -sp,
        (srsp * cy) - (cr * sy),
        (srsp * sy) + (cr * cy),
        sr * cp,
        (crsp * cy) + (sr * sy),
        (crsp * sy) - (sr * cy),
        cr * cp,
    ];

    pOut.x = (forwards.x * pseudoMatrix[0]) + (forwards.y * pseudoMatrix[3]) + (forwards.z * pseudoMatrix[6]);
    pOut.y = (forwards.x * pseudoMatrix[1]) + (forwards.y * pseudoMatrix[4]) + (forwards.z * pseudoMatrix[7]);
    pOut.z = (forwards.x * pseudoMatrix[2]) + (forwards.y * pseudoMatrix[5]) + (forwards.z * pseudoMatrix[8]);

    Some(pOut)
}

pub fn kmVec3Normalize<'a>(pOut: Option<&'a mut KmVec3>, pIn: Option<&'a KmVec3>) -> Option<&'a mut KmVec3> {
    // Check if either input is None
    if pOut.is_none() || pIn.is_none() {
        return None;
    }

    // Unwrap safely since we checked for None
    let pIn = pIn.unwrap();
    let pOut = pOut.unwrap();

    // Check if all components are zero (using approx_eq to handle floating point)
    if (pIn.x.abs() < f32::EPSILON) && 
       (pIn.y.abs() < f32::EPSILON) && 
       (pIn.z.abs() < f32::EPSILON) {
        return kmVec3Assign(Some(pOut), Some(pIn));
    }

    let l = 1.0f32 / kmVec3Length(Some(pIn));
    
    // Create normalized vector
    let v = KmVec3 {
        x: pIn.x * l,
        y: pIn.y * l,
        z: pIn.z * l,
    };

    // Assign to output
    pOut.x = v.x;
    pOut.y = v.y;
    pOut.z = v.z;

    Some(pOut)
}
pub fn kmVec3Transform<'a>(pOut: &'a mut KmVec3, pV: &'a KmVec3, pM: &'a KmMat4) -> &'a mut KmVec3 {
    kmVec3MultiplyMat4(pOut, pV, pM)
}
pub fn kmVec3Reflect<'a>(
    pOut: &'a mut KmVec3,
    pIn: Option<&KmVec3>,
    normal: Option<&KmVec3>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    if pIn.is_none() || normal.is_none() {
        return None;
    }

    let pIn = pIn.unwrap();
    let normal = normal.unwrap();

    let dot_product = kmVec3Dot(Some(pIn), Some(normal))?;
    let scale_factor = 2.0f32 * dot_product;

    let mut tmp = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    kmVec3Scale(&mut tmp, normal, scale_factor);
    Some(kmVec3Subtract(pOut, pIn, &tmp))
}
pub fn kmVec3TransformCoord<'a>(
    pOut: &'a mut KmVec3,
    pV: &KmVec3,
    pM: &KmMat4,
) -> &'a mut KmVec3 {
    let mut v = KmVec4 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    let mut inV = KmVec4 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
        w: 0.0,
    };
    
    kmVec4Fill(&mut inV, pV.x, pV.y, pV.z, 1.0);
    kmVec4Transform(&mut v, &inV, pM);
    
    pOut.x = v.x / v.w;
    pOut.y = v.y / v.w;
    pOut.z = v.z / v.w;
    
    pOut
}
pub fn kmVec3ProjectOnToPlane<'a>(
    pOut: Option<&'a mut KmVec3>,
    point: Option<&'a KmVec3>,
    plane: Option<&'a KmPlane>,
) -> Option<&'a mut KmVec3> {
    // Check for None (equivalent to NULL checks in C)
    if pOut.is_none() || point.is_none() || plane.is_none() {
        return Option::None;
    }

    let pOut = pOut.unwrap();
    let point = point.unwrap();
    let plane = plane.unwrap();

    let mut ray = KmRay3 {
        start: KmVec3 {
            x: point.x,
            y: point.y,
            z: point.z,
        },
        dir: KmVec3 {
            x: -plane.a,
            y: -plane.b,
            z: -plane.c,
        },
    };

    kmRay3IntersectPlane(pOut, &ray, plane);
    Some(pOut)
}
