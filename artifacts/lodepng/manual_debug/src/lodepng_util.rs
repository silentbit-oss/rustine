use crate::*;
use libflate::zlib::Decoder;
use rand::Rng;
use std::alloc;
use std::cmp::Ordering;
use std::convert::TryFrom;
use std::convert::TryInto;
use std::error::Error;
use std::f32;
use std::ffi::CStr;
use std::io::Read;
use std::os::raw::c_char;
use std::os::raw::c_uchar;
use std::os::raw::c_uint;
use std::ptr;
use std::slice;

pub fn getPaletteValue(data: &[u8], i: usize, bits: i32) -> i32 {
	println!("* getPaletteValue");
    match bits {
        8 => data[i] as i32,
        4 => (data[i / 2] >> ((i % 2) * 4)) as i32 & 15,
        2 => (data[i / 4] >> ((i % 4) * 2)) as i32 & 3,
        1 => (data[i / 8] >> (i % 8)) as i32 & 1,
        _ => 0,
    }
}
pub fn decodeICCUint16(data: &[u8], size: usize, pos: &mut usize) -> Option<u16> {
	println!("* decodeICCUint16");
    *pos += 2;
    if *pos > size {
        return None;
    }
    Some((data[*pos - 2] as u16) << 8 | data[*pos - 1] as u16)
}
pub fn decodeICCUint32(data: &[u8], size: usize, pos: &mut usize) -> Option<u32> {
	println!("* decodeICCUint32");
    *pos += 4;
    if *pos > size {
        return None;
    }
    Some(
        ((data[*pos - 4] as u32) << 24) |
        ((data[*pos - 3] as u32) << 16) |
        ((data[*pos - 2] as u32) << 8)  |
        (data[*pos - 1] as u32)
    )
}
pub fn decodeICCInt32(data: &[u8], size: usize, pos: &mut usize) -> Option<i32> {
	println!("* decodeICCInt32");
    *pos += 4;
    if *pos > size {
        return None;
    }
    let value = ((data[*pos - 4] as i32) << 24) |
                ((data[*pos - 3] as i32) << 16) |
                ((data[*pos - 2] as i32) << 8) |
                (data[*pos - 1] as i32);
    Some(value)
}
pub fn isICCword(data: &[u8], size: usize, pos: usize, word: &[u8]) -> bool {
	println!("* isICCword");
    if pos + 4 > size {
        return false;
    }
    data[pos] == word[0] && 
    data[pos + 1] == word[1] && 
    data[pos + 2] == word[2] && 
    data[pos + 3] == word[3]
}
pub fn mulMatrix(
    x2: &mut f32,
    y2: &mut f32,
    z2: &mut f32,
    m: &[f32; 9],
    x: f64,
    y: f64,
    z: f64,
) {
	println!("* mulMatrix");
    *x2 = (((x * m[0] as f64) + (y * m[1] as f64)) + (z * m[2] as f64)) as f32;
    *y2 = (((x * m[3] as f64) + (y * m[4] as f64)) + (z * m[5] as f64)) as f32;
    *z2 = (((x * m[6] as f64) + (y * m[7] as f64)) + (z * m[8] as f64)) as f32;
}
pub fn invMatrix(m: &mut [f32; 9]) -> u32 {
	println!("* invMatrix");
    let e0 = (f64::from(m[4]) * f64::from(m[8])) - (f64::from(m[5]) * f64::from(m[7]));
    let e3 = (f64::from(m[5]) * f64::from(m[6])) - (f64::from(m[3]) * f64::from(m[8]));
    let e6 = (f64::from(m[3]) * f64::from(m[7])) - (f64::from(m[4]) * f64::from(m[6]));
    let d = 1.0 / ((f64::from(m[0]) * e0) + (f64::from(m[1]) * e3) + (f64::from(m[2]) * e6));

    if d.abs() > 1e15 {
        return 1;
    }

    let mut result = [0.0; 9];
    result[0] = e0 * d;
    result[1] = ((f64::from(m[2]) * f64::from(m[7])) - (f64::from(m[1]) * f64::from(m[8]))) * d;
    result[2] = ((f64::from(m[1]) * f64::from(m[5])) - (f64::from(m[2]) * f64::from(m[4]))) * d;
    result[3] = e3 * d;
    result[4] = ((f64::from(m[0]) * f64::from(m[8])) - (f64::from(m[2]) * f64::from(m[6]))) * d;
    result[5] = ((f64::from(m[3]) * f64::from(m[2])) - (f64::from(m[0]) * f64::from(m[5]))) * d;
    result[6] = e6 * d;
    result[7] = ((f64::from(m[6]) * f64::from(m[1])) - (f64::from(m[0]) * f64::from(m[7]))) * d;
    result[8] = ((f64::from(m[0]) * f64::from(m[4])) - (f64::from(m[3]) * f64::from(m[1]))) * d;

    for i in 0..9 {
        m[i] = result[i] as f32;
    }

    0
}
pub fn readBitFromStream(bitp: &mut usize, bits: &[u8]) -> u64 {
	println!("* readBitFromStream");
    let result = (bits[*bitp >> 3] >> (*bitp & 0x7)) & 1;
    *bitp += 1;
    result as u64
}
pub fn decodeICC15Fixed16(data: &[u8], size: usize, pos: &mut usize) -> Option<f32> {
	println!("* decodeICC15Fixed16");
    decodeICCInt32(data, size, pos).map(|val| val as f32 / 65536.0)
}
pub fn mulMatrixMatrix(result: &mut [f32; 9], a: &[f32; 9], b: &[f32; 9]) {
	println!("* mulMatrixMatrix");
    let mut temp = [0.0; 9];
    
    // Process each column separately to avoid multiple mutable borrows
    {
        let (col0, rest) = temp.split_at_mut(3);
        let (col1, col2) = rest.split_at_mut(3);
        
        mulMatrix(
            &mut col0[0],
            &mut col1[0],
            &mut col2[0],
            a,
            b[0] as f64,
            b[3] as f64,
            b[6] as f64,
        );
        mulMatrix(
            &mut col0[1],
            &mut col1[1],
            &mut col2[1],
            a,
            b[1] as f64,
            b[4] as f64,
            b[7] as f64,
        );
        mulMatrix(
            &mut col0[2],
            &mut col1[2],
            &mut col2[2],
            a,
            b[2] as f64,
            b[5] as f64,
            b[8] as f64,
        );
    }

    // Copy the results
    result.copy_from_slice(&temp);
}
pub fn getChrmMatrixXYZ(
    m: &mut [f32; 9],
    wX: f32,
    wY: f32,
    wZ: f32,
    rX: f32,
    rY: f32,
    rZ: f32,
    gX: f32,
    gY: f32,
    gZ: f32,
    bX: f32,
    bY: f32,
    bZ: f32,
) -> u32 {
	println!("* getChrmMatrixXYZ");
    let mut t = [0.0; 9];
    t[0] = rX;
    t[1] = gX;
    t[2] = bX;
    t[3] = rY;
    t[4] = gY;
    t[5] = bY;
    t[6] = rZ;
    t[7] = gZ;
    t[8] = bZ;

    if invMatrix(&mut t) != 0 {
        return 1;
    }

    let (mut rs, mut gs, mut bs) = (0.0, 0.0, 0.0);
    mulMatrix(
        &mut rs,
        &mut gs,
        &mut bs,
        &t,
        wX as f64,
        wY as f64,
        wZ as f64,
    );

    m[0] = rs * rX;
    m[1] = gs * gX;
    m[2] = bs * bX;
    m[3] = rs * rY;
    m[4] = gs * gY;
    m[5] = bs * bY;
    m[6] = rs * rZ;
    m[7] = gs * gZ;
    m[8] = bs * bZ;

    0
}
pub fn getChrmMatrixXY(
    m: &mut [f32; 9],
    wx: f32,
    wy: f32,
    rx: f32,
    ry: f32,
    gx: f32,
    gy: f32,
    bx: f32,
    by: f32,
) -> u32 {
	println!("* getChrmMatrixXY");
    if wy == 0.0 || ry == 0.0 || gy == 0.0 || by == 0.0 {
        return 1;
    }

    let wX = wx / wy;
    let wY = 1.0;
    let wZ = (1.0 - wx - wy) / wy;
    
    let rX = rx / ry;
    let rY = 1.0;
    let rZ = (1.0 - rx - ry) / ry;
    
    let gX = gx / gy;
    let gY = 1.0;
    let gZ = (1.0 - gx - gy) / gy;
    
    let bX = bx / by;
    let bY = 1.0;
    let bZ = (1.0 - bx - by) / by;

    getChrmMatrixXYZ(
        m, wX, wY, wZ, 
        rX, rY, rZ, 
        gX, gY, gZ, 
        bX, bY, bZ
    )
}
pub fn validateICC(icc: &LodePngIcc) -> bool {
	println!("* validateICC");
    if icc.inputspace == 0 {
        return false;
    }
    if (icc.inputspace == 2) && (icc.has_chromaticity == 0) {
        return false;
    }
    if (icc.has_whitepoint == 0) || (icc.has_trc == 0) {
        return false;
    }
    true
}
pub fn isSRGB(info: Option<&LodePngInfo>) -> u32 {
	println!("* isSRGB");
    // Check for NULL equivalent (None in Rust)
    if info.is_none() {
        return 1;
    }
    let info = info.unwrap(); // Safe unwrap since we checked for None

    if info.iccp_defined != 0 {
        return 0;
    }
    if info.srgb_defined != 0 {
        return 1;
    }
    if info.gama_defined != 0 {
        return 0;
    }
    if info.chrm_defined != 0 {
        if (info.chrm_white_x != 31270) || (info.chrm_white_y != 32900) {
            return 0;
        }
        if (info.chrm_red_x != 64000) || (info.chrm_red_y != 33000) {
            return 0;
        }
        if (info.chrm_green_x != 30000) || (info.chrm_green_y != 60000) {
            return 0;
        }
        if (info.chrm_blue_x != 15000) || (info.chrm_blue_y != 6000) {
            return 0;
        }
    }
    1
}
pub fn readBitsFromStream(bitp: &mut usize, bits: &[u8], nbits: usize) -> u64 {
	println!("* readBitsFromStream");
    let mut result = 0;
    for i in 0..nbits {
        result += readBitFromStream(bitp, bits) << i;
    }
    result
}
impl ExtractPng {
    pub fn readPngHeader(&mut self, in_data: &[u8], inlength: usize) {
	println!("* readPngHeader");
        if inlength < 29 {
            self.error = 27;
            return;
        }

        // Check PNG signature bytes
        if in_data[0] != 137 
            || in_data[1] != 80 
            || in_data[2] != 78 
            || in_data[3] != 71 
            || in_data[4] != 13 
            || in_data[5] != 10 
            || in_data[6] != 26 
            || in_data[7] != 10 
        {
            self.error = 28;
            return;
        }

        // Check IHDR chunk
        if in_data[12] != b'I' 
            || in_data[13] != b'H' 
            || in_data[14] != b'D' 
            || in_data[15] != b'R' 
        {
            self.error = 29;
            return;
        }
    }
}
pub fn read32bitInt(self_: &ExtractPng, buffer: &[u8]) -> u32 {
	println!("* read32bitInt");
    ((u32::from(buffer[0]) << 24) | 
     (u32::from(buffer[1]) << 16) | 
     (u32::from(buffer[2]) << 8) | 
     u32::from(buffer[3]))
}
pub fn modelsEqual(state_a: Option<&LodePngState>, state_b: Option<&LodePngState>) -> u32 {
	println!("* modelsEqual");
    let a = state_a.map(|s| &s.info_png);
    let b = state_b.map(|s| &s.info_png);

    if isSRGB(a) != isSRGB(b) {
        return 0;
    }

    if a.map(|i| i.iccp_defined) != b.map(|i| i.iccp_defined) {
        return 0;
    }

    if let (Some(a), Some(b)) = (a, b) {
        if a.iccp_defined != 0 {
            if a.iccp_profile_size != b.iccp_profile_size {
                return 0;
            }
            if let (Some(a_profile), Some(b_profile)) = (&a.iccp_profile, &b.iccp_profile) {
                if a_profile != b_profile {
                    return 0;
                }
            }
            return 1;
        }

        if a.srgb_defined != b.srgb_defined {
            return 0;
        }
        if a.srgb_defined != 0 {
            return 1;
        }

        if a.gama_defined != b.gama_defined {
            return 0;
        }
        if a.gama_defined != 0 && a.gama_gamma != b.gama_gamma {
            return 0;
        }

        if a.chrm_defined != b.chrm_defined {
            return 0;
        }
        if a.chrm_defined != 0 {
            if a.chrm_white_x != b.chrm_white_x || a.chrm_white_y != b.chrm_white_y {
                return 0;
            }
            if a.chrm_red_x != b.chrm_red_x || a.chrm_red_y != b.chrm_red_y {
                return 0;
            }
            if a.chrm_green_x != b.chrm_green_x || a.chrm_green_y != b.chrm_green_y {
                return 0;
            }
            if a.chrm_blue_x != b.chrm_blue_x || a.chrm_blue_y != b.chrm_blue_y {
                return 0;
            }
        }
    }

    1
}
pub fn lodepng_powf(x: f32, y: f32) -> f32 {
	println!("* lodepng_powf");
    let mut j;
    let mut t0;
    let mut t1;
    let mut l;
    let mut i = 0;
    
    if (x == 1.0_f32) || (y == 0.0_f32) {
        return 1.0_f32;
    }
    if y == 1.0_f32 {
        return x;
    }
    if !((x > 0.0_f32 && x <= LODEPNG_FLT_MAX && y >= -LODEPNG_FLT_MAX) && y <= LODEPNG_FLT_MAX) {
        if x.is_nan() || y.is_nan() {
            return x + y;
        }
        if x > 0.0_f32 {
            if x > LODEPNG_FLT_MAX {
                return if y <= 0.0_f32 {
                    if y == 0.0_f32 { 1.0_f32 } else { 0.0_f32 }
                } else {
                    x
                };
            }
        } else {
            if !(y < -1073741824.0_f32 || y > 1073741824.0_f32) {
                i = y as i32;
                if i as f32 != y {
                    return if x < -LODEPNG_FLT_MAX {
                        if y < 0.0_f32 { 0.0_f32 } else { LODEPNG_FLT_INF }
                    } else {
                        if x == 0.0_f32 {
                            if y < 0.0_f32 { LODEPNG_FLT_INF } else { 0.0_f32 }
                        } else {
                            LODEPNG_FLT_NAN
                        }
                    };
                }
                if i & 1 != 0 {
                    return if x == 0.0_f32 {
                        if y < 0.0_f32 { 1.0_f32 / x } else { x }
                    } else {
                        -lodepng_powf(-x, y)
                    };
                }
            }
            if x == 0.0_f32 {
                return if y <= 0.0_f32 { LODEPNG_FLT_INF } else { 0.0_f32 };
            }
            if x < -LODEPNG_FLT_MAX {
                return if y <= 0.0_f32 {
                    if y == 0.0_f32 { 1.0_f32 } else { 0.0_f32 }
                } else {
                    if i & 1 != 0 { -LODEPNG_FLT_INF } else { LODEPNG_FLT_INF }
                };
            }
            let x = -x;
            if x == 1.0_f32 {
                return 1.0_f32;
            }
        }
        if y < -LODEPNG_FLT_MAX || y > LODEPNG_FLT_MAX {
            return if (x < 1.0_f32) != (y > 0.0_f32) {
                if y < 0.0_f32 { -y } else { y }
            } else {
                0.0_f32
            };
        }
    }
    l = x;
    j = 0.0_f32;
    while l < (1.0_f32 / 65536.0_f32) {
        j -= 16.0_f32;
        l *= 65536.0_f32;
    }

    while l > 65536.0_f32 {
        j += 16.0_f32;
        l *= 1.0_f32 / 65536.0_f32;
    }

    while l < 1.0_f32 {
        j -= 1.0_f32;
        l *= 2.0_f32;
    }

    while l > 2.0_f32 {
        j += 1.0_f32;
        l *= 0.5_f32;
    }

    t0 = -0.393118410458557_f32 + (l * (-0.0883639468229365_f32 + (l * (0.466142650227994_f32 + (l * 0.0153397331014276_f32)))));
    t1 = 0.0907447971403586_f32 + (l * (0.388892024755479_f32 + (l * 0.137228280305862_f32)));
    l = (t0 / t1) + j;
    l *= y;
    if l <= -128.0_f32 || l >= 128.0_f32 {
        return if (x > 1.0_f32) == (y > 0.0_f32) { LODEPNG_FLT_INF } else { 0.0_f32 };
    }
    i = l as i32;
    l -= i as f32;
    t0 = 1.0_f32 + (l * (0.41777833582744256_f32 + (l * (0.0728482595347711_f32 + (l * 0.005635023478609625_f32)))));
    t1 = 1.0_f32 + (l * (-0.27537016151408167_f32 + (l * 0.023501446055084033_f32)));
    while i <= -31 {
        t0 *= 1.0_f32 / 2147483648.0_f32;
        i += 31;
    }

    while i >= 31 {
        t0 *= 2147483648.0_f32;
        i -= 31;
    }

    if i < 0 {
        let shift_val = (1i32 << ((-i) as u32)) as f32;
        t0 / (t1 * shift_val)
    } else {
        let shift_val = (1i32 << (i as u32)) as f32;
        (t0 * shift_val) / t1
    }
}

pub fn icc_forward_trc(curve: &LodePngIccCurve, x: f32) -> f32 {
	println!("* icc_forward_trc");
    match curve.type_ {
        0 => x,
        1 => {
            let lut = match &curve.lut {
                Some(lut) => lut,
                None => return 0.0,
            };

            if x < 0.0 {
                return x;
            }

            let index = (x * (curve.lut_size as f32 - 1.0)) as usize;
            if index >= curve.lut_size {
                return x;
            }

            let v0 = lut[index];
            let v1 = if index + 1 < curve.lut_size {
                lut[index + 1]
            } else {
                1.0
            };
            let fraction = (x * (curve.lut_size as f32 - 1.0)) - index as f32;
            (v0 * (1.0 - fraction)) + (v1 * fraction)
        }
        2 => {
            if x > 0.0 {
                lodepng_powf(x, curve.gamma)
            } else {
                x
            }
        }
        3 => {
            if x < 0.0 {
                x
            } else if x >= ((-curve.b) / curve.a) {
                lodepng_powf((curve.a * x) + curve.b, curve.gamma) + curve.c
            } else {
                0.0
            }
        }
        4 => {
            if x < 0.0 {
                x
            } else if x >= ((-curve.b) / curve.a) {
                lodepng_powf((curve.a * x) + curve.b, curve.gamma) + curve.c
            } else {
                curve.c
            }
        }
        5 => {
            if x >= curve.d {
                lodepng_powf((curve.a * x) + curve.b, curve.gamma)
            } else {
                curve.c * x
            }
        }
        6 => {
            if x >= curve.d {
                lodepng_powf((curve.a * x) + curve.b, curve.gamma) + curve.c
            } else {
                (curve.c * x) + curve.f
            }
        }
        _ => 0.0,
    }
}

pub fn convert_to_xyz_gamma_table(
    out: &mut [f32],
    n: usize,
    c: usize,
    info: &LodePngInfo,
    use_icc: bool,
    icc: &LodePngIcc,
) {
	println!("* convert_to_xyz_gamma_table");
    let mul = 1.0f32 / (n as f32 - 1.0f32);

    if use_icc {
        for i in 0..n {
            out[i] = icc_forward_trc(&icc.trc[c], i as f32 * mul);
        }
    } else if info.gama_defined != 0 && info.srgb_defined == 0 && info.gama_gamma != 100000 {
        let gamma = 100000.0f32 / info.gama_gamma as f32;
        for i in 0..n {
            out[i] = lodepng_powf(i as f32 * mul, gamma);
        }
    } else {
        for i in 0..n {
            let v = i as f32 * mul;
            out[i] = if v < 0.04045f32 {
                v / 12.92f32
            } else {
                lodepng_powf((v + 0.055f32) / 1.055f32, 2.4f32)
            };
        }
    }
}
pub fn getAdaptationMatrix(
    m: &mut [f32; 9],
    type_: i32,
    wx0: f32,
    wy0: f32,
    wz0: f32,
    wx1: f32,
    wy1: f32,
    wz1: f32,
) -> u32 {
	println!("* getAdaptationMatrix");
    static BRADFORD: [f32; 9] = [
        0.8951f32, 0.2664f32, -0.1614f32, -0.7502f32, 1.7135f32, 0.0367f32, 0.0389f32,
        -0.0685f32, 1.0296f32,
    ];
    static BRADFORD_INV: [f32; 9] = [
        0.9869929f32,
        -0.1470543f32,
        0.1599627f32,
        0.4323053f32,
        0.5183603f32,
        0.0492912f32,
        -0.0085287f32,
        0.0400428f32,
        0.9684867f32,
    ];
    static VONKRIES: [f32; 9] = [
        0.40024f32, 0.70760f32, -0.08081f32, -0.22630f32, 1.16532f32, 0.04570f32, 0.00000f32,
        0.00000f32, 0.91822f32,
    ];
    static VONKRIES_INV: [f32; 9] = [
        1.8599364f32,
        -1.1293816f32,
        0.2198974f32,
        0.3611914f32,
        0.6388125f32,
        -0.0000064f32,
        0.0000000f32,
        0.0000000f32,
        1.0890636f32,
    ];

    if type_ == 0 {
        for i in 0..9 {
            m[i] = 0.0;
        }

        m[0] = wx1 / wx0;
        m[4] = wy1 / wy0;
        m[8] = wz1 / wz0;
    } else {
        let cat = if type_ == 1 { &BRADFORD } else { &VONKRIES };
        let inv = if type_ == 1 { &BRADFORD_INV } else { &VONKRIES_INV };

        let mut rho0 = 0.0;
        let mut gam0 = 0.0;
        let mut bet0 = 0.0;
        mulMatrix(
            &mut rho0,
            &mut gam0,
            &mut bet0,
            cat,
            wx0 as f64,
            wy0 as f64,
            wz0 as f64,
        );

        let mut rho1 = 0.0;
        let mut gam1 = 0.0;
        let mut bet1 = 0.0;
        mulMatrix(
            &mut rho1,
            &mut gam1,
            &mut bet1,
            cat,
            wx1 as f64,
            wy1 as f64,
            wz1 as f64,
        );

        let rho2 = rho1 / rho0;
        let gam2 = gam1 / gam0;
        let bet2 = bet1 / bet0;

        let mut temp = [0.0; 9];
        for i in 0..3 {
            temp[i + 0] = rho2 * cat[i + 0];
            temp[i + 3] = gam2 * cat[i + 3];
            temp[i + 6] = bet2 * cat[i + 6];
        }

        mulMatrixMatrix(m, inv, &temp);
    }

    0
}
pub fn get_icc_chrm(m: &mut [f32; 9], whitepoint: &mut [f32; 3], icc: &LodePngIcc) -> u32 {
	println!("* get_icc_chrm");
    if icc.inputspace == 2 {
        let mut red = [0.0; 3];
        let mut green = [0.0; 3];
        let mut blue = [0.0; 3];
        let mut white = [0.0; 3];
        let mut a = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0];

        if icc.has_chad != 0 {
            for i in 0..9 {
                a[i] = icc.chad[i];
            }

            if invMatrix(&mut a) != 0 {
                return 1;
            }
        } else {
            if getAdaptationMatrix(
                &mut a,
                1,
                icc.illuminant[0],
                icc.illuminant[1],
                icc.illuminant[2],
                icc.white[0],
                icc.white[1],
                icc.white[2],
            ) != 0
            {
                return 1;
            }
        }

        if icc.has_chad != 0 {
            let mut x = 0.0;
            let mut y = 0.0;
            let mut z = 0.0;
            mulMatrix(
                &mut x,
                &mut y,
                &mut z,
                &a,
                icc.white[0] as f64,
                icc.white[1] as f64,
                icc.white[2] as f64,
            );
            white[0] = x;
            white[1] = y;
            white[2] = z;
        } else {
            for i in 0..3 {
                white[i] = icc.white[i];
            }
        }

        {
            let mut x = 0.0;
            let mut y = 0.0;
            let mut z = 0.0;
            mulMatrix(
                &mut x,
                &mut y,
                &mut z,
                &a,
                icc.red[0] as f64,
                icc.red[1] as f64,
                icc.red[2] as f64,
            );
            red[0] = x;
            red[1] = y;
            red[2] = z;
        }

        {
            let mut x = 0.0;
            let mut y = 0.0;
            let mut z = 0.0;
            mulMatrix(
                &mut x,
                &mut y,
                &mut z,
                &a,
                icc.green[0] as f64,
                icc.green[1] as f64,
                icc.green[2] as f64,
            );
            green[0] = x;
            green[1] = y;
            green[2] = z;
        }

        {
            let mut x = 0.0;
            let mut y = 0.0;
            let mut z = 0.0;
            mulMatrix(
                &mut x,
                &mut y,
                &mut z,
                &a,
                icc.blue[0] as f64,
                icc.blue[1] as f64,
                icc.blue[2] as f64,
            );
            blue[0] = x;
            blue[1] = y;
            blue[2] = z;
        }

        if getChrmMatrixXYZ(
            m,
            white[0],
            white[1],
            white[2],
            red[0],
            red[1],
            red[2],
            green[0],
            green[1],
            green[2],
            blue[0],
            blue[1],
            blue[2],
        ) != 0
        {
            return 1;
        }

        whitepoint[0] = white[0];
        whitepoint[1] = white[1];
        whitepoint[2] = white[2];
    } else {
        m[0] = 1.0;
        m[4] = 1.0;
        m[8] = 1.0;
        m[1] = 0.0;
        m[2] = 0.0;
        m[3] = 0.0;
        m[5] = 0.0;
        m[6] = 0.0;
        m[7] = 0.0;
        whitepoint[0] = 1.0;
        whitepoint[1] = 1.0;
        whitepoint[2] = 1.0;
    }

    0
}
pub fn get_chrm(
    m: &mut [f32; 9],
    whitepoint: &mut [f32; 3],
    use_icc: u32,
    icc: &LodePngIcc,
    info: &LodePngInfo,
) -> u32 {
	println!("* get_chrm");
    if use_icc != 0 {
        if get_icc_chrm(m, whitepoint, icc) != 0 {
            return 1;
        }
    } else if info.chrm_defined != 0 && info.srgb_defined == 0 {
        let wx = info.chrm_white_x as f32 / 100000.0f32;
        let wy = info.chrm_white_y as f32 / 100000.0f32;
        let rx = info.chrm_red_x as f32 / 100000.0f32;
        let ry = info.chrm_red_y as f32 / 100000.0f32;
        let gx = info.chrm_green_x as f32 / 100000.0f32;
        let gy = info.chrm_green_y as f32 / 100000.0f32;
        let bx = info.chrm_blue_x as f32 / 100000.0f32;
        let by = info.chrm_blue_y as f32 / 100000.0f32;

        if getChrmMatrixXY(m, wx, wy, rx, ry, gx, gy, bx, by) != 0 {
            return 1;
        }

        whitepoint[0] = wx / wy;
        whitepoint[1] = 1.0;
        whitepoint[2] = ((1.0 - wx) - wy) / wy;
    } else {
        const SRGB: [f32; 9] = [
            0.4124564f32,
            0.3575761f32,
            0.1804375f32,
            0.2126729f32,
            0.7151522f32,
            0.0721750f32,
            0.0193339f32,
            0.1191920f32,
            0.9503041f32,
        ];

        m.copy_from_slice(&SRGB);

        whitepoint[0] = 0.9504559270516716f32;
        whitepoint[1] = 1.0;
        whitepoint[2] = 1.0890577507598784f32;
    }

    0
}
pub fn convert_to_xyz_chrm(
    im: &mut [f32],
    w: u32,
    h: u32,
    info: &LodePngInfo,
    use_icc: u32,
    icc: &LodePngIcc,
    whitepoint: &mut [f32; 3],
) -> u32 {
	println!("* convert_to_xyz_chrm");
    let mut error = 0;
    let n = (w * h) as usize;
    let mut m = [0.0; 9];

    error = get_chrm(&mut m, whitepoint, use_icc, icc, info);
    if error != 0 {
        return error;
    }

    if use_icc == 0 || icc.inputspace == 2 {
        for i in 0..n {
            let j = i * 4;
            let x = im[j];
            let y = im[j + 1];
            let z = im[j + 2];
            let (new_x, new_y, new_z) = {
                let mut x2 = 0.0;
                let mut y2 = 0.0;
                let mut z2 = 0.0;
                mulMatrix(
                    &mut x2,
                    &mut y2,
                    &mut z2,
                    &m,
                    x as f64,
                    y as f64,
                    z as f64,
                );
                (x2, y2, z2)
            };
            im[j] = new_x;
            im[j + 1] = new_y;
            im[j + 2] = new_z;
        }
    }

    0
}
pub fn parse_icc(icc: &mut LodePngIcc, data: &[u8], size: usize) -> Option<u32> {
	println!("* parse_icc");
    if size < 132 {
        return Some(1);
    }

    icc.has_chromaticity = 0;
    icc.has_whitepoint = 0;
    icc.has_trc = 0;
    icc.has_chad = 0;
    
    for k in 0..3 {
        icc.trc[k].type_ = 0;
        icc.white[k] = 0.0;
        icc.red[k] = 0.0;
        icc.green[k] = 0.0;
        icc.blue[k] = 0.0;
    }

    let mut pos = 8;
    let version = decodeICCUint32(data, size, &mut pos)?;
    if pos >= size {
        return Some(1);
    }

    icc.version_major = ((version >> 24) & 255) as i32;
    icc.version_minor = ((version >> 20) & 15) as i32;
    icc.version_bugfix = ((version >> 16) & 15) as i32;

    pos = 16;
    let inputspace = decodeICCUint32(data, size, &mut pos)?;
    if pos >= size {
        return Some(1);
    }

    icc.inputspace = match inputspace {
        0x47524159 => 1,
        0x52474220 => 2,
        _ => 0,
    };

    pos = 68;
    for i in 0..3 {
        icc.illuminant[i] = decodeICC15Fixed16(data, size, &mut pos)?;
    }

    pos = 128;
    let numtags = decodeICCUint32(data, size, &mut pos)? as usize;
    if pos >= size {
        return Some(1);
    }

    for _ in 0..numtags {
        let namepos = pos;
        pos += 4;
        let offset = decodeICCUint32(data, size, &mut pos)? as usize;
        let tagsize = decodeICCUint32(data, size, &mut pos)? as usize;
        
        if pos >= size || offset >= size || (offset + tagsize) > size || tagsize < 8 {
            return Some(1);
        }

        let mut current_offset = offset;
        if isICCword(data, size, namepos, b"wtpt") {
            current_offset += 8;
            for j in 0..3 {
                icc.white[j] = decodeICC15Fixed16(data, size, &mut current_offset)?;
            }
            icc.has_whitepoint = 1;
        } else if isICCword(data, size, namepos, b"rXYZ") {
            current_offset += 8;
            for j in 0..3 {
                icc.red[j] = decodeICC15Fixed16(data, size, &mut current_offset)?;
            }
            icc.has_chromaticity = 1;
        } else if isICCword(data, size, namepos, b"gXYZ") {
            current_offset += 8;
            for j in 0..3 {
                icc.green[j] = decodeICC15Fixed16(data, size, &mut current_offset)?;
            }
            icc.has_chromaticity = 1;
        } else if isICCword(data, size, namepos, b"bXYZ") {
            current_offset += 8;
            for j in 0..3 {
                icc.blue[j] = decodeICC15Fixed16(data, size, &mut current_offset)?;
            }
            icc.has_chromaticity = 1;
        } else if isICCword(data, size, namepos, b"chad") {
            current_offset += 8;
            for j in 0..9 {
                icc.chad[j] = decodeICC15Fixed16(data, size, &mut current_offset)?;
            }
            icc.has_chad = 1;
        } else if isICCword(data, size, namepos, b"rTRC") 
               || isICCword(data, size, namepos, b"gTRC") 
               || isICCword(data, size, namepos, b"bTRC") 
               || isICCword(data, size, namepos, b"kTRC") {
            let c = data[namepos] as char;
            let channel = match c {
                'b' => 2,
                'g' => 1,
                _ => 0,
            };
            let trc = &mut icc.trc[channel];
            icc.has_trc = 1;

            if isICCword(data, size, current_offset, b"curv") {
                current_offset += 8;
                let count = decodeICCUint32(data, size, &mut current_offset)? as usize;
                
                if count == 0 {
                    trc.type_ = 0;
                } else if count == 1 {
                    trc.type_ = 2;
                    trc.gamma = decodeICCUint16(data, size, &mut current_offset)? as f32 / 256.0;
                } else {
                    if (current_offset + (count * 2)) > size || count > 16777216 {
                        return Some(1);
                    }
                    trc.type_ = 1;
                    trc.lut_size = count;
                    let mut lut = Vec::with_capacity(count);
                    for _ in 0..count {
                        lut.push(decodeICCUint16(data, size, &mut current_offset)? as f32 * (1.0 / 65535.0));
                    }
                    trc.lut = Some(lut);
                }
            }

            if isICCword(data, size, current_offset, b"para") {
                current_offset += 8;
                let type_ = decodeICCUint16(data, size, &mut current_offset)?;
                current_offset += 2;
                if type_ > 4 {
                    return Some(1);
                }
                trc.type_ = type_ as u32 + 2;
                trc.gamma = decodeICC15Fixed16(data, size, &mut current_offset)?;
                if type_ >= 1 {
                    trc.a = decodeICC15Fixed16(data, size, &mut current_offset)?;
                    trc.b = decodeICC15Fixed16(data, size, &mut current_offset)?;
                }
                if type_ >= 2 {
                    trc.c = decodeICC15Fixed16(data, size, &mut current_offset)?;
                }
                if type_ >= 3 {
                    trc.d = decodeICC15Fixed16(data, size, &mut current_offset)?;
                }
                if type_ == 4 {
                    trc.e = decodeICC15Fixed16(data, size, &mut current_offset)?;
                    trc.f = decodeICC15Fixed16(data, size, &mut current_offset)?;
                }
            }
        }

        if current_offset > size {
            return Some(1);
        }
    }

    Some(0)
}
pub fn lodepng_icc_curve_init(curve: &mut LodePngIccCurve) {
	println!("* lodepng_icc_curve_init");
    curve.lut = None;
    curve.lut_size = 0;
}
pub fn lodepng_icc_init(icc: &mut LodePngIcc) {
	println!("* lodepng_icc_init");
    for i in 0..3 {
        lodepng_icc_curve_init(&mut icc.trc[i]);
    }
}
pub fn lodepng_icc_curve_cleanup(curve: &mut LodePngIccCurve) {
	println!("* lodepng_icc_curve_cleanup");
    curve.lut = Option::None;
}
pub fn lodepng_icc_cleanup(icc: &mut LodePngIcc) {
	println!("* lodepng_icc_cleanup");
    for i in 0..3 {
        lodepng_icc_curve_cleanup(&mut icc.trc[i]);
    }
}
pub fn convert_to_xyz(
    out: &mut [f32],
    whitepoint: &mut [f32; 3],
    in_data: &[u8],
    w: u32,
    h: u32,
    state: &LodePngState,
) -> u32 {
	println!("* convert_to_xyz");
    let mut error = 0;
    let n = (w * h) as usize;
    let mode_in = &state.info_raw;
    let info = &state.info_png;
    let bit16 = mode_in.bitdepth > 8;
    let num = if bit16 { 65536 } else { 256 };
    let tempmode = lodepng_color_mode_make(LodePNGColorType::LCT_RGBA, if bit16 { 16 } else { 8 });
    let mut use_icc = false;
    let mut icc = LodePngIcc {
        inputspace: 0,
        version_major: 0,
        version_minor: 0,
        version_bugfix: 0,
        illuminant: [0.0; 3],
        has_chad: 0,
        chad: [0.0; 9],
        has_whitepoint: 0,
        white: [0.0; 3],
        has_chromaticity: 0,
        red: [0.0; 3],
        green: [0.0; 3],
        blue: [0.0; 3],
        has_trc: 0,
        trc: [
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
        ],
    };
    lodepng_icc_init(&mut icc);

    if info.iccp_defined != 0 {
        if let Some(profile) = &info.iccp_profile {
            if let Some(err) = parse_icc(&mut icc, profile, info.iccp_profile_size as usize) {
                error = err;
                lodepng_icc_cleanup(&mut icc);
                return error;
            }
        }
        use_icc = validateICC(&icc);
    }

    let mut data = vec![0u8; (w * h) as usize * if bit16 { 8 } else { 4 }];
    error = lodepng_convert(&mut data, in_data, &tempmode, mode_in, w, h);
    if error != 0 {
        lodepng_icc_cleanup(&mut icc);
        return error;
    }

    {
        let mut gammatable = if use_icc && icc.inputspace == 2 {
            vec![0.0f32; num * 3]
        } else {
            vec![0.0f32; num]
        };

        if use_icc && icc.inputspace == 2 {
            let (gammatable_r, rest) = gammatable.split_at_mut(num);
            let (gammatable_g, gammatable_b) = rest.split_at_mut(num);
            
            convert_to_xyz_gamma_table(gammatable_r, num, 0, info, use_icc, &icc);
            convert_to_xyz_gamma_table(gammatable_g, num, 1, info, use_icc, &icc);
            convert_to_xyz_gamma_table(gammatable_b, num, 2, info, use_icc, &icc);

            if bit16 {
                for i in 0..n {
                    let idx = i * 8;
                    out[i * 4] = gammatable_r[(data[idx] as usize * 256 + data[idx + 1] as usize)];
                    out[i * 4 + 1] = gammatable_g[(data[idx + 2] as usize * 256 + data[idx + 3] as usize)];
                    out[i * 4 + 2] = gammatable_b[(data[idx + 4] as usize * 256 + data[idx + 5] as usize)];
                    out[i * 4 + 3] = ((data[idx + 6] as f32 * 256.0) + data[idx + 7] as f32) * (1.0 / 65535.0);
                }
            } else {
                for i in 0..n {
                    let idx = i * 4;
                    out[i * 4] = gammatable_r[data[idx] as usize];
                    out[i * 4 + 1] = gammatable_g[data[idx + 1] as usize];
                    out[i * 4 + 2] = gammatable_b[data[idx + 2] as usize];
                    out[i * 4 + 3] = data[idx + 3] as f32 * (1.0 / 255.0);
                }
            }
        } else {
            convert_to_xyz_gamma_table(&mut gammatable, num, 0, info, use_icc, &icc);

            if bit16 {
                for i in 0..n {
                    let idx = i * 8;
                    out[i * 4] = gammatable[(data[idx] as usize * 256 + data[idx + 1] as usize)];
                    out[i * 4 + 1] = gammatable[(data[idx + 2] as usize * 256 + data[idx + 3] as usize)];
                    out[i * 4 + 2] = gammatable[(data[idx + 4] as usize * 256 + data[idx + 5] as usize)];
                    out[i * 4 + 3] = ((data[idx + 6] as f32 * 256.0) + data[idx + 7] as f32) * (1.0 / 65535.0);
                }
            } else {
                for i in 0..n {
                    let idx = i * 4;
                    out[i * 4] = gammatable[data[idx] as usize];
                    out[i * 4 + 1] = gammatable[data[idx + 1] as usize];
                    out[i * 4 + 2] = gammatable[data[idx + 2] as usize];
                    out[i * 4 + 3] = data[idx + 3] as f32 * (1.0 / 255.0);
                }
            }
        }
    }

    error = convert_to_xyz_chrm(out, w, h, info, use_icc as u32, &icc, whitepoint);
    lodepng_icc_cleanup(&mut icc);
    error
}
pub fn icc_backward_trc(curve: &LodePngIccCurve, x: f32) -> f32 {
	println!("* icc_backward_trc");
    match curve.type_ {
        0 => x,
        1 => {
            if x <= 0.0 || x >= 1.0 {
                return x;
            }
            
            let lut = match &curve.lut {
                Some(l) => l,
                None => return 0.0, // Fallback if LUT is missing
            };
            
            let mut a = 0;
            let mut b = curve.lut_size;
            
            loop {
                if a == b {
                    return lut[a];
                }
                if a + 1 == b {
                    let v0 = lut[a];
                    let v1 = lut[b];
                    if v0 == v1 {
                        return v0;
                    }
                    let fraction = (x - v0) / (v1 - v0);
                    return v0 * (1.0 - fraction) + v1 * fraction;
                }
                
                let m = (a + b) / 2;
                let v = lut[m];
                
                match v.partial_cmp(&x).unwrap_or(Ordering::Equal) {
                    Ordering::Greater => b = m,
                    _ => a = m,
                }
            }
        }
        2 => {
            if x > 0.0 {
                lodepng_powf(x, 1.0 / curve.gamma)
            } else {
                x
            }
        }
        3 => {
            if x < 0.0 {
                x
            } else if x > 0.0 {
                (lodepng_powf(x, 1.0 / curve.gamma) - curve.b) / curve.a
            } else {
                (-curve.b) / curve.a
            }
        }
        4 => {
            if x < 0.0 {
                x
            } else if x > curve.c {
                (lodepng_powf(x - curve.c, 1.0 / curve.gamma) - curve.b) / curve.a
            } else {
                (-curve.b) / curve.a
            }
        }
        5 => {
            if x > curve.c * curve.d {
                (lodepng_powf(x, 1.0 / curve.gamma) - curve.b) / curve.a
            } else {
                x / curve.c
            }
        }
        6 => {
            if x > (curve.c * curve.d) + curve.f {
                (lodepng_powf(x - curve.c, 1.0 / curve.gamma) - curve.b) / curve.a
            } else {
                (x - curve.f) / curve.c
            }
        }
        _ => 0.0,
    }
}
pub fn convert_from_xyz_gamma(im: &mut [f32], w: usize, h: usize, info: &LodePngInfo, use_icc: bool, icc: &LodePngIcc) {
	println!("* convert_from_xyz_gamma");
    let n = w * h;
    
    if use_icc {
        for i in 0..n {
            for c in 0..3 {
                let idx = i * 4 + c;
                im[idx] = icc_backward_trc(&icc.trc[c], im[idx]);
            }
        }
    } else if info.gama_defined != 0 && info.srgb_defined == 0 {
        if info.gama_gamma != 100000 {
            let gamma = info.gama_gamma as f32 / 100000.0f32;
            for i in 0..n {
                for c in 0..3 {
                    let idx = i * 4 + c;
                    if im[idx] > 0.0 {
                        im[idx] = lodepng_powf(im[idx], gamma);
                    }
                }
            }
        }
    } else {
        for i in 0..n {
            for c in 0..3 {
                let idx = i * 4 + c;
                let v = &mut im[idx];
                *v = if *v < 0.0031308f32 {
                    *v * 12.92f32
                } else {
                    (1.055f32 * lodepng_powf(*v, 1.0f32 / 2.4f32)) - 0.055f32
                };
            }
        }
    }
}
pub fn convert_from_xyz_chrm(
    out: &mut [f32],
    in_: &[f32],
    w: u32,
    h: u32,
    info: &LodePngInfo,
    use_icc: u32,
    icc: &LodePngIcc,
    whitepoint: &[f32; 3],
    rendering_intent: u32,
) -> u32 {
	println!("* convert_from_xyz_chrm");
    let n = (w * h) as usize;
    let mut m = [0.0; 9];
    let mut white = [0.0; 3];

    if get_chrm(&mut m, &mut white, use_icc, icc, info) != 0 {
        return 1;
    }
    if invMatrix(&mut m) != 0 {
        return 1;
    }

    if rendering_intent != 3 {
        let mut a = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0];
        if getAdaptationMatrix(
            &mut a,
            1,
            whitepoint[0],
            whitepoint[1],
            whitepoint[2],
            white[0],
            white[1],
            white[2],
        ) != 0
        {
            return 1;
        }
        let m_copy = m;
        mulMatrixMatrix(&mut m, &m_copy, &a);
    }

    if (!use_icc != 0) || (icc.inputspace == 2) || (rendering_intent != 3) {
        for i in 0..n {
            let j = i * 4;
            let (x, rest) = out[j..].split_first_mut().unwrap();
            let (y, rest) = rest.split_first_mut().unwrap();
            let (z, _) = rest.split_first_mut().unwrap();
            mulMatrix(
                x,
                y,
                z,
                &m,
                in_[j] as f64,
                in_[j + 1] as f64,
                in_[j + 2] as f64,
            );
            out[j + 3] = in_[j + 3];
        }
    } else {
        out[..n * 4].copy_from_slice(&in_[..n * 4]);
    }

    0
}
pub fn convert_from_xyz(
    out: &mut [u8],
    in_: &[f32],
    w: u32,
    h: u32,
    state: &LodePngState,
    whitepoint: &[f32; 3],
    rendering_intent: u32,
) -> u32 {
	println!("* convert_from_xyz");
    let mut error = 0;
    let n = (w * h) as usize;
    let mode_out = &state.info_raw;
    let info = &state.info_png;
    let bit16 = mode_out.bitdepth > 8;
    let mut im: Option<Vec<f32>> = None;
    let mut data: Option<Vec<u8>> = None;
    let mut use_icc = false;
    let mut icc = LodePngIcc {
        inputspace: 0,
        version_major: 0,
        version_minor: 0,
        version_bugfix: 0,
        illuminant: [0.0; 3],
        has_chad: 0,
        chad: [0.0; 9],
        has_whitepoint: 0,
        white: [0.0; 3],
        has_chromaticity: 0,
        red: [0.0; 3],
        green: [0.0; 3],
        blue: [0.0; 3],
        has_trc: 0,
        trc: [
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
        ],
    };
    
    lodepng_icc_init(&mut icc);
    
    if info.iccp_defined != 0 {
        if let Some(profile) = &info.iccp_profile {
            error = parse_icc(&mut icc, profile, info.iccp_profile_size as usize).unwrap_or(1);
            if error != 0 {
                lodepng_icc_cleanup(&mut icc);
                return error;
            }
            use_icc = validateICC(&icc);
        }
    }

    im = Some(vec![0.0; (w * h * 4) as usize]);
    error = convert_from_xyz_chrm(
        im.as_mut().unwrap(),
        in_,
        w,
        h,
        info,
        use_icc as u32,
        &icc,
        whitepoint,
        rendering_intent,
    );
    if error != 0 {
        lodepng_icc_cleanup(&mut icc);
        return error;
    }

    convert_from_xyz_gamma(
        im.as_mut().unwrap(),
        w as usize,
        h as usize,
        info,
        use_icc,
        &icc,
    );

    data = Some(vec![0; (w * h * 8) as usize]);

    if bit16 {
        let mode16 = lodepng_color_mode_make(LodePNGColorType::LCT_RGBA, 16);
        for i in 0..n {
            for c in 0..4 {
                let j = (i * 8) + (c * 2);
                let val = im.as_ref().unwrap()[(i * 4) + c];
                let clamped = val.max(0.0).min(1.0);
                let i16 = (0.5f32 + (65535.0f32 * clamped)) as i32;
                data.as_mut().unwrap()[j] = (i16 >> 8) as u8;
                data.as_mut().unwrap()[j + 1] = (i16 & 255) as u8;
            }
        }

        error = lodepng_convert(
            out,
            data.as_ref().unwrap(),
            mode_out,
            &mode16,
            w,
            h,
        );
        if error != 0 {
            lodepng_icc_cleanup(&mut icc);
            return error;
        }
    } else {
        let mode8 = lodepng_color_mode_make(LodePNGColorType::LCT_RGBA, 8);
        for i in 0..n {
            for c in 0..4 {
                let val = im.as_ref().unwrap()[(i * 4) + c];
                let clamped = val.max(0.0).min(1.0);
                data.as_mut().unwrap()[(i * 4) + c] = (0.5f32 + (255.0f32 * clamped)) as u8;
            }
        }

        error = lodepng_convert(
            out,
            data.as_ref().unwrap(),
            mode_out,
            &mode8,
            w,
            h,
        );
        if error != 0 {
            lodepng_icc_cleanup(&mut icc);
            return error;
        }
    }

    lodepng_icc_cleanup(&mut icc);
    error
}

pub fn convert_rgb_model(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    state_out: &LodePngState,
    state_in: &LodePngState,
    rendering_intent: u32,
) -> u32 {
	println!("* convert_rgb_model");
    if modelsEqual(Some(state_in), Some(state_out)) != 0 {
        lodepng_convert(out, in_data, &state_out.info_raw, &state_in.info_raw, w, h)
    } else {
        let mut error = 0;
        let xyz_size = (w * h * 4) as usize;
        let mut xyz = vec![0.0f32; xyz_size];
        let mut whitepoint = [0.0f32; 3];

        error = convert_to_xyz(&mut xyz, &mut whitepoint, in_data, w, h, state_in);
        if error == 0 {
            error = convert_from_xyz(out, &xyz, w, h, state_out, &whitepoint, rendering_intent);
        }

        error
    }
}

pub fn convert_to_srgb(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    state_in: &LodePngState,
) -> u32 {
	println!("* convert_to_srgb");
    let mut srgb = LodePngState {
        decoder: state_in.decoder.clone(),
        encoder: state_in.encoder.clone(),
        info_raw: state_in.info_raw.clone(),
        info_png: state_in.info_png.clone(),
        error: state_in.error,
    };
    lodepng_state_init(&mut srgb);
    lodepng_color_mode_copy(&mut srgb.info_raw, &state_in.info_raw);
    convert_rgb_model(out, in_data, w, h, &srgb, state_in, 1)
}
pub fn convert_from_srgb(
    out: &mut [u8],
    in_data: &[u8],
    w: u32,
    h: u32,
    state_out: &LodePngState,
) -> u32 {
	println!("* convert_from_srgb");
    let mut srgb = LodePngState {
        decoder: state_out.decoder.clone(),
        encoder: state_out.encoder.clone(),
        info_raw: LodePNGColorMode {
            colortype: state_out.info_raw.colortype,
            bitdepth: state_out.info_raw.bitdepth,
            palette: state_out.info_raw.palette.clone(),
            palettesize: state_out.info_raw.palettesize,
            key_defined: state_out.info_raw.key_defined,
            key_r: state_out.info_raw.key_r,
            key_g: state_out.info_raw.key_g,
            key_b: state_out.info_raw.key_b,
        },
        info_png: state_out.info_png.clone(),
        error: state_out.error,
    };
    
    lodepng_state_init(&mut srgb);
    lodepng_color_mode_copy(&mut srgb.info_raw, &state_out.info_raw);
    
    convert_rgb_model(out, in_data, w, h, state_out, &srgb, 1)
}

pub fn getChunks(
    names: &mut [Option<Vec<String>>; 3],
    chunks: &mut [Option<Vec<Vec<u8>>>; 3],
    counts: &mut [Option<Vec<usize>>; 3],
    png: &[u8],
    png_size: usize,
) -> Result<(), ()> {
	println!("* getChunks");
    let end = &png[png_size..];
    let mut chunk = &png[8..];
    let mut location = 0;
    let mut count = [0, 0, 0];

    while chunk.as_ptr() < end.as_ptr() && end.as_ptr() as usize - chunk.as_ptr() as usize >= 8 {
        let mut type_ = [0; 5];
        lodepng_chunk_type(&mut type_, chunk);

        let type_str = unsafe { CStr::from_ptr(type_.as_ptr() as *const c_char) }
            .to_str()
            .map_err(|_| ())?;
        if type_str.len() != 4 {
            return Err(());
        }

        let next = lodepng_chunk_next_const(chunk, end);
        match type_str {
            "IHDR" => location = 0,
            "PLTE" => location = 1,
            "IDAT" => location = 2,
            "IEND" => break,
            _ => {
                if next.as_ptr() >= end.as_ptr() {
                    return Err(());
                }
                let size = next.as_ptr() as usize - chunk.as_ptr() as usize;

                // Initialize vectors if they don't exist
                if names[location].is_none() {
                    names[location] = Some(Vec::new());
                }
                if chunks[location].is_none() {
                    chunks[location] = Some(Vec::new());
                }

                names[location].as_mut().unwrap().push(type_str.to_string());
                chunks[location]
                    .as_mut()
                    .unwrap()
                    .push(chunk[..size].to_vec());
                count[location] += 1;
            }
        }
        chunk = next;
    }

    for i in 0..3 {
        if counts[i].is_none() {
            counts[i] = Some(Vec::new());
        }
        counts[i].as_mut().unwrap().push(count[i]);
    }

    Ok(())
}

pub fn insert_chunks(
    out_png: &mut Option<Vec<u8>>,
    out_size: &mut usize,
    png: &[u8],
    chunks: &[&[&[u8]]; 3],
    chunk_sizes: &[&[usize]; 3],
    chunk_counts: &[usize; 3],
) -> u32 {
	println!("* insert_chunks");
    let mut chunk_idx = 0;
    let mut begin_idx = 0;
    let mut end_idx = png.len();
    let mut l0 = 0;
    let mut l1 = 0;
    let mut l2 = 0;

    let mut current_chunk = &png[chunk_idx..];
    while current_chunk.len() >= 8 && chunk_idx < end_idx {
        let mut type_ = [0u8; 5];
        lodepng_chunk_type(&mut type_, current_chunk);

        let type_str = CStr::from_bytes_until_nul(&type_).unwrap().to_str().unwrap();
        
        match type_str {
            "PLTE" if l0 == 0 => {
                l0 = (chunk_idx - begin_idx) + 8;
            },
            "IDAT" => {
                if l0 == 0 {
                    l0 = (chunk_idx - begin_idx) + 8;
                }
                if l1 == 0 {
                    l1 = (chunk_idx - begin_idx) + 8;
                }
            },
            "IEND" if l2 == 0 => {
                l2 = (chunk_idx - begin_idx) + 8;
            },
            _ => {}
        }

        current_chunk = lodepng_chunk_next_const(current_chunk, &png[end_idx..]);
        chunk_idx = png.len() - current_chunk.len();
    }

    let mut result = Vec::with_capacity(png.len() + 1024);
    let mut pos = 0;

    // Copy first segment (up to l0)
    result.extend_from_slice(&png[..l0]);
    pos += l0;

    // Insert chunks[0]
    for i in 0..chunk_counts[0] {
        result.extend_from_slice(chunks[0][i]);
        pos += chunk_sizes[0][i];
    }

    // Copy segment between l0 and l1
    result.extend_from_slice(&png[l0..l1]);
    pos += l1 - l0;

    // Insert chunks[1]
    for i in 0..chunk_counts[1] {
        result.extend_from_slice(chunks[1][i]);
        pos += chunk_sizes[1][i];
    }

    // Copy segment between l1 and l2
    result.extend_from_slice(&png[l1..l2]);
    pos += l2 - l1;

    // Insert chunks[2]
    for i in 0..chunk_counts[2] {
        result.extend_from_slice(chunks[2][i]);
        pos += chunk_sizes[2][i];
    }

    // Copy remaining segment
    result.extend_from_slice(&png[l2..]);
    pos += png.len() - l2;

    *out_png = Some(result);
    *out_size = pos;
    0
}

pub fn decompress(
    zlib: &ExtractZlib,
    out: &mut [u8],
    in_data: &[u8],
    in_size: usize,
) -> Result<(), i32> {
	println!("* decompress");
    // The zlib parameter is unused in the original C code, so we ignore it
    let _ = zlib;

    // Create a decoder for the input data
    let mut decoder = match Decoder::new(in_data) {
        Ok(d) => d,
        Err(_) => return Err(1),
    };

    // Decompress the data into the output buffer
    match decoder.read_exact(out) {
        Ok(_) => Ok(()),
        Err(_) => Err(1),
    }
}

pub fn getChunkInfo(
    names: &mut Vec<Option<String>>,
    sizes: &mut Vec<usize>,
    count: &mut usize,
    png: &[u8],
    png_size: usize,
) -> u32 {
	println!("* getChunkInfo");
    *count = 0;
    let end = &png[png_size..];
    let mut chunk = &png[8..];

    while chunk.as_ptr() < end.as_ptr() && end.as_ptr() as usize - chunk.as_ptr() as usize >= 8 {
        let mut type_ = [0u8; 5];
        lodepng_chunk_type(&mut type_, chunk);

        // Convert to CStr to handle null-terminated string safely
        let type_cstr = unsafe { CStr::from_ptr(type_.as_ptr() as *const c_char) };
        if type_cstr.to_bytes().len() != 4 {
            return 1;
        }

        let length = lodepng_chunk_length(chunk) as usize;
        names.push(Some(type_cstr.to_str().unwrap().to_string()));
        sizes.push(length);
        *count += 1;

        chunk = lodepng_chunk_next_const(chunk, end);
    }

    0
}
pub fn decode(self_: &mut ExtractPng, in_data: Option<&[u8]>, size: usize) {
	println!("* decode");
    self_.error = 0;
    if size == 0 || in_data.is_none() {
        self_.error = 48;
        return;
    }
    let in_data = in_data.unwrap();

    self_.readPngHeader(in_data, size);
    if self_.error != 0 {
        return;
    }

    let mut pos = 33;
    let mut idat = Vec::with_capacity(size);
    let mut idat_len = 0;
    let mut iend = false;

    while !iend {
        if pos + 8 >= size {
            self_.error = 30;
            return;
        }

        let chunk_length = read32bitInt(self_, &in_data[pos..]) as usize;
        pos += 4;

        if chunk_length > 2147483647 {
            self_.error = 63;
            return;
        }

        if pos + chunk_length >= size {
            self_.error = 35;
            return;
        }

        if in_data[pos..pos+4] == [b'I', b'D', b'A', b'T'] {
            idat.extend_from_slice(&in_data[pos+4..pos+4+chunk_length]);
            idat_len += chunk_length;
            pos += 4 + chunk_length;
        } else if in_data[pos..pos+4] == [b'I', b'E', b'N', b'D'] {
            pos += 4;
            iend = true;
        } else {
            pos += chunk_length + 4;
        }

        pos += 4;
    }

    let mut out = vec![0u8; size * 2];
    let mut zlib = ExtractZlib {
        zlibinfo: self_.zlibinfo.clone(),
        error: 0,
    };

    if let Err(e) = decompress(&mut zlib, &mut out, &idat, idat_len) {
        self_.error = e;
    } else {
        self_.error = zlib.error;
    }
}
pub fn extract_zlib_info(zlibinfo: Option<&mut ZlibBlockInfo>, in_data: Option<&[u8]>, size: usize) -> u32 {
	println!("* extract_zlib_info");
    let mut decoder = ExtractPng {
        zlibinfo: zlibinfo.map(|z| Box::new(z.clone())),
        error: 0,
    };
    
    decode(&mut decoder, in_data, size);
    
    if decoder.error != 0 { 1 } else { 0 }
}

pub fn convert_to_xyz_gamma(
    out: &mut [f32],
    in_: &[f32],
    w: usize,
    h: usize,
    info: &LodePngInfo,
    use_icc: bool,
    icc: &LodePngIcc,
) {
	println!("* convert_to_xyz_gamma");
    let n = w * h;
    
    // Copy all input values to output (including alpha channel)
    out[..(n * 4)].copy_from_slice(&in_[..(n * 4)]);

    if use_icc {
        // Apply ICC profile transformation
        for i in 0..n {
            for c in 0..3 {
                let idx = i * 4 + c;
                out[idx] = icc_forward_trc(&icc.trc[c], in_[idx]);
            }
        }
    } else if info.gama_defined != 0 && info.srgb_defined == 0 && info.gama_gamma != 100000 {
        // Apply gamma correction
        let gamma = 100000.0f32 / info.gama_gamma as f32;
        for i in 0..n {
            for c in 0..3 {
                let idx = i * 4 + c;
                let v = in_[idx];
                out[idx] = if v <= 0.0 { v } else { lodepng_powf(v, gamma) };
            }
        }
    } else {
        // Apply sRGB transformation
        for i in 0..n {
            for c in 0..3 {
                let idx = i * 4 + c;
                let v = in_[idx];
                out[idx] = if v < 0.04045f32 {
                    v / 12.92f32
                } else {
                    lodepng_powf((v + 0.055f32) / 1.055f32, 2.4f32)
                };
            }
        }
    }
}
pub fn get_png_header_info(png: Option<&[u8]>, png_size: usize) -> LodePngInfo {
	println!("* get_png_header_info");
    let mut w: u32 = 0;
    let mut h: u32 = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    lodepng_state_init(&mut state);
    lodepng_inspect(
        Some(&mut w),
        Some(&mut h),
        &mut state,
        png,
        png_size,
    );
    let info = state.info_png.clone();
    lodepng_state_cleanup(&mut state);
    info
}
pub fn getFilterTypesInterlaced(
    filters: &mut [Option<Vec<u8>>; 7],
    counts: &mut [Option<usize>; 7],
    png: Option<&[u8]>,
    png_size: usize,
) -> u32 {
	println!("* getFilterTypesInterlaced");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);

    let mut w = 0;
    let mut h = 0;
    let error = lodepng_inspect(
        Some(&mut w),
        Some(&mut h),
        &mut state,
        png,
        png_size,
    );
    if error != 0 {
        return 1;
    }

    let png_data = match png {
        Some(data) => data,
        None => return 1,
    };

    let mut zdata = Vec::new();
    let mut chunk = png_data;
    
    while chunk.len() >= 8 {
        let mut type_ = [0u8; 5];
        lodepng_chunk_type(&mut type_, chunk);
        
        let type_str = match CStr::from_bytes_until_nul(&type_) {
            Ok(s) => s.to_str().unwrap_or(""),
            Err(_) => "",
        };
        
        if type_str.len() != 4 {
            break;
        }

        if type_str == "IDAT" {
            let cdata = match lodepng_chunk_data_const(Some(chunk)) {
                Some(data) => data,
                None => return 1,
            };
            let clength = lodepng_chunk_length(chunk) as usize;
            
            if chunk.len() < clength + 12 || clength > png_size {
                return 1;
            }
            
            zdata.extend_from_slice(cdata);
        }
        
        chunk = lodepng_chunk_next_const(chunk, png_data);
    }

    let mut data = Vec::new();
    let zlib = ExtractZlib {
        error: 0,
        zlibinfo: None,
    };
    if let Err(_) = decompress(&zlib, &mut data, &zdata, zdata.len()) {
        return 1;
    }

    if state.info_png.interlace_method == 0 {
        let linebytes = 1 + lodepng_get_raw_size(w, 1, &state.info_png.color);
        let count = data.len() / linebytes;
        counts[0] = Some(count);
        
        let mut filter_data = Vec::with_capacity(count);
        for i in 0..count {
            filter_data.push(data[i * linebytes]);
        }
        filters[0] = Some(filter_data);
    } else {
        const ADAM7_IX: [u32; 7] = [0, 4, 0, 2, 0, 1, 0];
        const ADAM7_IY: [u32; 7] = [0, 0, 4, 0, 2, 0, 1];
        const ADAM7_DX: [u32; 7] = [8, 8, 4, 4, 2, 2, 1];
        const ADAM7_DY: [u32; 7] = [8, 8, 8, 4, 4, 2, 2];
        
        let mut pos = 0;
        for j in 0..7 {
            let w2 = (w - ADAM7_IX[j] + ADAM7_DX[j] - 1) / ADAM7_DX[j];
            let h2 = (h - ADAM7_IY[j] + ADAM7_DY[j] - 1) / ADAM7_DY[j];
            
            if ADAM7_IX[j] >= w || ADAM7_IY[j] >= h {
                continue;
            }
            
            let linebytes = 1 + lodepng_get_raw_size(w2, 1, &state.info_png.color);
            counts[j] = Some(h2 as usize);
            
            let mut filter_data = Vec::with_capacity(h2 as usize);
            for _ in 0..h2 {
                filter_data.push(data[pos]);
                pos += linebytes;
            }
            filters[j] = Some(filter_data);
        }
    }

    lodepng_state_cleanup(&mut state);
    0
}

pub fn getFilterTypes(
    filterTypes: &mut Option<Vec<u8>>,
    count: &mut Option<usize>,
    png: Option<&[u8]>,
    png_size: usize,
) -> u32 {
	println!("* getFilterTypes");
    let mut passes: [Option<Vec<u8>>; 7] = [None, None, None, None, None, None, None];
    let mut pass_counts: [Option<usize>; 7] = [None, None, None, None, None, None, None];
    
    let error = getFilterTypesInterlaced(&mut passes, &mut pass_counts, png, png_size);
    if error != 0 {
        return error;
    }

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    lodepng_state_init(&mut state);
    
    let mut w = 0;
    let mut h = 0;
    lodepng_inspect(Some(&mut w), Some(&mut h), &mut state, png, png_size);

    let all_zero = pass_counts[1..].iter().all(|x| x.unwrap_or(0) == 0);
    if all_zero {
        *count = pass_counts[0];
        *filterTypes = passes[0].take();
    } else {
        const COLUMN0: [usize; 8] = [0, 6, 4, 6, 2, 6, 4, 6];
        const COLUMN1: [usize; 8] = [5, 6, 5, 6, 5, 6, 5, 6];
        const SHIFT0: [usize; 8] = [3, 1, 2, 1, 3, 1, 2, 1];
        const SHIFT1: [usize; 8] = [1, 1, 1, 1, 1, 1, 1, 1];
        
        let column = if w > 1 { &COLUMN1 } else { &COLUMN0 };
        let shift = if w > 1 { &SHIFT1 } else { &SHIFT0 };
        
        let mut output = Vec::with_capacity(h as usize);
        
        for i in 0..h {
            let pass_idx = column[i as usize & 7];
            let shift_val = shift[i as usize & 7];
            let idx = (i as usize) >> shift_val;
            
            if let Some(pass) = &passes[pass_idx] {
                if idx < pass.len() {
                    output.push(pass[idx]);
                }
            }
        }
        
        *filterTypes = Some(output);
        *count = Some(h as usize);
        
        for j in 0..7 {
            if j != column[0] && passes[j].is_some() {
                passes[j] = None;
            }
        }
    }

    lodepng_state_cleanup(&mut state);
    0
}
pub fn convert_to_xyz_float(
    out: &mut [f32],
    whitepoint: &mut [f32; 3],
    in_: &[f32],
    w: usize,
    h: usize,
    state: &LodePngState,
) -> Result<(), Box<dyn Error>> {
	println!("* convert_to_xyz_float");
    let info = &state.info_png;
    let mut use_icc = false;
    let mut icc = LodePngIcc {
        inputspace: 0,
        version_major: 0,
        version_minor: 0,
        version_bugfix: 0,
        illuminant: [0.0; 3],
        has_chad: 0,
        chad: [0.0; 9],
        has_whitepoint: 0,
        white: [0.0; 3],
        has_chromaticity: 0,
        red: [0.0; 3],
        green: [0.0; 3],
        blue: [0.0; 3],
        has_trc: 0,
        trc: [
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
        ],
    };
    lodepng_icc_init(&mut icc);

    if info.iccp_defined != 0 {
        if let Some(profile) = &info.iccp_profile {
            if let Some(error) = parse_icc(&mut icc, profile, info.iccp_profile_size as usize) {
                lodepng_icc_cleanup(&mut icc);
                return Err(Box::new(std::io::Error::new(
                    std::io::ErrorKind::Other,
                    format!("ICC parsing error: {}", error),
                )));
            }
        }
        use_icc = validateICC(&icc);
    }

    convert_to_xyz_gamma(out, in_, w, h, info, use_icc, &icc);
    convert_to_xyz_chrm(out, w as u32, h as u32, info, use_icc as u32, &icc, whitepoint);

    lodepng_icc_cleanup(&mut icc);
    Ok(())
}
pub fn convert_from_xyz_float(
    out: &mut [f32],
    in_: &[f32],
    w: u32,
    h: u32,
    state: &LodePngState,
    whitepoint: &[f32; 3],
    rendering_intent: u32,
) -> u32 {
	println!("* convert_from_xyz_float");
    let mut error = 0;
    let info = &state.info_png;
    let mut use_icc = false;
    let mut icc = LodePngIcc {
        inputspace: 0,
        version_major: 0,
        version_minor: 0,
        version_bugfix: 0,
        illuminant: [0.0; 3],
        has_chad: 0,
        chad: [0.0; 9],
        has_whitepoint: 0,
        white: [0.0; 3],
        has_chromaticity: 0,
        red: [0.0; 3],
        green: [0.0; 3],
        blue: [0.0; 3],
        has_trc: 0,
        trc: [
            LodePngIccCurve {
                type_: 0,
                lut: Option::None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: Option::None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
            LodePngIccCurve {
                type_: 0,
                lut: Option::None,
                lut_size: 0,
                gamma: 0.0,
                a: 0.0,
                b: 0.0,
                c: 0.0,
                d: 0.0,
                e: 0.0,
                f: 0.0,
            },
        ],
    };
    lodepng_icc_init(&mut icc);

    if info.iccp_defined != 0 {
        if let Some(profile) = &info.iccp_profile {
            if let Some(err) = parse_icc(&mut icc, profile, info.iccp_profile_size as usize) {
                error = err;
                lodepng_icc_cleanup(&mut icc);
                return error;
            }
        }
        use_icc = validateICC(&icc);
    }

    error = convert_from_xyz_chrm(
        out,
        in_,
        w,
        h,
        info,
        u32::from(use_icc),
        &icc,
        whitepoint,
        rendering_intent,
    );
    if error != 0 {
        lodepng_icc_cleanup(&mut icc);
        return error;
    }

    convert_from_xyz_gamma(
        out,
        w as usize,
        h as usize,
        info,
        use_icc,
        &icc,
    );

    lodepng_icc_cleanup(&mut icc);
    error
}
