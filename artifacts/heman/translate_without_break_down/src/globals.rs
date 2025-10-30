use crate::*;
use lazy_static::lazy_static;


lazy_static! {
    pub static ref _GAMMA: std::sync::Mutex<f32> = std::sync::Mutex::new(0.0);
}

pub const INF: f32 = 1E20;

pub const SEALEVEL: f32 = 0.5;

pub const DEFAULT_STRENGTH: f32 = 0.6;


lazy_static! {
    pub static ref _OCCLUSION_SCALE: std::sync::Mutex<f32> = std::sync::Mutex::new(1.0f32);
}

pub static GRADIENTS2D: [i8; 16] = [
    5, 2,  // 2 elements
    2, 5,  // 2 elements
    -5, 2, // 2 elements
    -2, 5, // 2 elements
    5, -2, // 2 elements
    2, -5, // 2 elements
    -5, -2, // 2 elements
    -2, -5  // 2 elements
];

pub static GRADIENTS3D: [i8; 72] = [
    -11, 4, 4, -4, 11, 4, -4, 4, 11,  // 9 elements
    11, 4, 4, 4, 11, 4, 4, 4, 11,     // 9 elements
    -11, -4, 4, -4, -11, 4, -4, -4, 11, // 9 elements
    11, -4, 4, 4, -11, 4, 4, -4, 11,  // 9 elements
    -11, 4, -4, -4, 11, -4, -4, 4, -11, // 9 elements
    11, 4, -4, 4, 11, -4, 4, 4, -11,  // 9 elements
    -11, -4, -4, -4, -11, -4, -4, -4, -11, // 9 elements
    11, -4, -4, 4, -11, -4, 4, -4, -11, // 9 elements
];

pub static GRADIENTS4D: [i8; 256] = [
    3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 
    -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, 
    3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 
    -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, 
    3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 
    -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, 
    3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 
    -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, 
    3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 
    -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, 
    3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 
    -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, 
    3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 
    -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, 
    3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 
    -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3
];


lazy_static! {
    pub static ref KM_VEC3_NEG_Z: KmVec3 = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: -1.0,
    };
}


lazy_static! {
    pub static ref KM_VEC3_POS_Z: KmVec3 = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 1.0
    };
}


lazy_static! {
    pub static ref KM_VEC3_POS_Y: KmVec3 = KmVec3 {
        x: 0.0,
        y: 1.0,
        z: 0.0,
    };
}


lazy_static! {
    pub static ref KM_VEC3_NEG_Y: KmVec3 = KmVec3 {
        x: 0.0,
        y: -1.0,
        z: 0.0,
    };
}


lazy_static! {
    pub static ref KM_VEC3_NEG_X: KmVec3 = KmVec3 {
        x: -1.0,
        y: 0.0,
        z: 0.0,
    };
}


lazy_static! {
    pub static ref KM_VEC3_POS_X: KmVec3 = KmVec3 {
        x: 1.0,
        y: 0.0,
        z: 0.0,
    };
}


lazy_static! {
    pub static ref KM_VEC3_ZERO: KmVec3 = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
}


lazy_static! {
    pub static ref KM_VEC2_POS_Y: KmVec2 = KmVec2 { x: 0.0, y: 1.0 };
}


lazy_static! {
    pub static ref KM_VEC2_NEG_Y: KmVec2 = KmVec2 { x: 0.0, y: -1.0 };
}


lazy_static! {
    pub static ref KM_VEC2_NEG_X: KmVec2 = KmVec2 { x: -1.0, y: 0.0 };
}


lazy_static! {
    pub static ref KM_VEC2_POS_X: KmVec2 = KmVec2 { x: 1.0, y: 0.0 };
}


lazy_static! {
    pub static ref KM_VEC2_ZERO: KmVec2 = KmVec2 { x: 0.0, y: 0.0 };
}

