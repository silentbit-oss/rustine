use crate::*;

pub fn zinit(a: &mut Z) {
    a.alloced = 0;
    a.chars = None;
}
pub fn zeven(a: &Z) -> bool {
    // Check if either the sign is zero or the least significant bit is zero
    (a.sign == 0) || (a.chars.as_ref().map_or(false, |chars| (chars[0] & 1) == 0))
}
pub fn zodd(a: &Z) -> bool {
    a.sign != 0 && a.chars.as_ref().map_or(false, |chars| !chars.is_empty() && (chars[0] & 1) != 0)
}
pub fn zeven_nonzero(a: &Z) -> bool {
    // Check if the first character's least significant bit is 0 (even)
    // Using safe access with Option and unwrap_or_default
    a.chars.as_ref().map_or(false, |chars| chars[0].trailing_zeros() != 0)
}
pub fn zodd_nonzero(a: &Z) -> bool {
    // Access the first element of chars if it exists, otherwise return false
    a.chars.as_ref().map_or(false, |chars| chars[0] & 1 != 0)
}
#[inline]
pub fn zzero(a: &Z) -> bool {
    a.sign == 0
}
pub fn zsignum(a: &Z) -> i32 {
    a.sign
}
pub fn zabs(a: &mut Z, b: &Z) {
    // The do-while(0) loop in C is just a way to create a block that can be exited early
    // In Rust, we can use a simple block for the same purpose
    {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
    }
    
    // Set the sign based on whether the value is zero
    a.sign = !zzero(a) as i32;
}
