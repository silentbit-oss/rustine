use crate::*;

pub fn zneg(a: &mut Z, b: &Z) {
    // The do-while(0) loop in C is just a way to create a block that can be exited early
    // In Rust, we can use a simple block with early return
    {
        if a as *const _ != b as *const _ {
            zset(a, b);
        }
    }
    
    a.sign = -zsignum(a);
}
