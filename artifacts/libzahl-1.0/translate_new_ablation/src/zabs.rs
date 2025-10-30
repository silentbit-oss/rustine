use crate::*;

pub fn zabs(a: &mut z_t, b: &z_t) {
    // The do-while(0) loop in C is just a way to create a block that can be exited early
    // In Rust, we can use a simple block scope
    {
        if &a[0] as *const _ != &b[0] as *const _ {
            zset(a, b);
        }
    }
    
    // Set the sign based on whether the value is zero
    a[0].sign = !zzero(a) as i32;
}
