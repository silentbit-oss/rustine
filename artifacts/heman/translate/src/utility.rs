use crate::*;

pub fn kmSQR(s: f32) -> f32 {
    s * s
}
pub fn kmDegreesToRadians(degrees: f32) -> f32 {
    degrees * (3.14159265358979323846f32 / 180.0f32)
}
pub fn kmRadiansToDegrees(radians: f32) -> f32 {
    radians * (180.0 / std::f32::consts::PI)
}
pub fn kmMin(lhs: f32, rhs: f32) -> f32 {
    if lhs < rhs { lhs } else { rhs }
}
pub fn kmMax(lhs: f32, rhs: f32) -> f32 {
    if lhs > rhs { lhs } else { rhs }
}
pub fn kmAlmostEqual(lhs: f32, rhs: f32) -> u8 {
    (((lhs + 0.0001) > rhs) && ((lhs - 0.0001) < rhs)) as u8
}
pub fn kmClamp(x: f32, min: f32, max: f32) -> f32 {
    if x < min {
        min
    } else if x > max {
        max
    } else {
        x
    }
}
pub fn kmLerp(x: f32, y: f32, t: f32) -> f32 {
    x + (t * (y - x))
}
