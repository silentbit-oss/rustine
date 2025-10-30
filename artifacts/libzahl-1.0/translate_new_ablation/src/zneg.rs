use crate::*;

pub fn zneg(a: &mut z_t, b: &z_t) {
    // The do-while(0) loop in C is just a way to create a single statement block
    // that can be used with break/continue. In Rust, we can just use a block.
    {
        if &a[0] as *const Z != &b[0] as *const Z {
            zset(a, b);
        }
    }
    
    // Calculate the new sign and assign it
    a[0].sign = -zsignum(a);
}
