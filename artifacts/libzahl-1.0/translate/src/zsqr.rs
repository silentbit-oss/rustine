use crate::*;
use std::boxed::Box;

pub fn zsqr(a: &mut z_t, b: &mut z_t) {
    let mut m2: usize;
    let mut z0: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: Option::None,
    }];
    let mut z1: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: Option::None,
    }];
    let mut z2: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: Option::None,
    }];
    let mut high: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: Option::None,
    }];
    let mut low: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: Option::None,
    }];
    let mut sign: i32;
    let mut temp: z_t = [Z {
        sign: 0,
        used: 0,
        alloced: 0,
        chars: Option::None,
    }];

    if zzero(b) {
        a[0].sign = 0;
        return;
    }

    m2 = zbits(b);
    if m2 <= (32 / 2) {
        if a[0].alloced < 1 {
            libzahl_realloc(a, 1);
        }
        a[0].used = 1;
        a[0].chars.as_mut().unwrap()[0] = b[0].chars.as_ref().unwrap()[0] * b[0].chars.as_ref().unwrap()[0];
        a[0].sign = 1;
        return;
    }

    sign = zsignum(b);
    b[0].sign = 1;
    m2 >>= 1;

    zinit(&mut z0);
    zinit(&mut z1);
    zinit(&mut z2);
    zinit(&mut high);
    zinit(&mut low);
    zinit(&mut temp);

    zsplit(&mut high, &mut low, b, m2);
    zsqr(&mut z0, &mut low);
    zsqr(&mut z2, &mut high);
    zmul(&mut z1, &mut low, &mut high);
    
    // Free the original high and low as we are done with them
    zfree(&mut high);
    zfree(&mut low);
    
    // Re-initialize high and low to use as temporaries
    zinit(&mut high);
    zinit(&mut low);
    
    // Shift z1 into high (using high as temporary)
    zlsh(&mut high, &z1, m2 + 1);
    zfree(&mut z1);  // Free z1 as it's no longer needed
    
    m2 <<= 1;
    
    // Shift z2 into low (using low as temporary)
    zlsh(&mut low, &z2, m2);
    zfree(&mut z2);  // Free z2 as it's no longer needed
    
    // Perform additions using the temporaries
    zadd(&mut temp, &high, &low);  // temp = high + low
    zadd(a, &temp, &z0);           // a = temp + z0
    
    // Free the remaining temporaries
    zfree(&mut z0);
    zfree(&mut high);
    zfree(&mut low);
    zfree(&mut temp);

    b[0].sign = sign;
    a[0].sign = 1;
}
