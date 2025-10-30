use crate::*;

pub fn zsqr(a: &mut Z, b: &mut Z) {
    if zzero(b) {
        a.sign = 0;
        return;
    }

    let m2 = zbits(b);
    if m2 <= (32 / 2) {
        if a.alloced < 1 {
            libzahl_realloc(a, 1);
        }
        a.used = 1;
        if let (Some(b_chars), Some(a_chars)) = (&b.chars, &mut a.chars) {
            a_chars[0] = b_chars[0] * b_chars[0];
        }
        a.sign = 1;
        return;
    }

    let sign = zsignum(b);
    b.sign = 1;
    let mut m2 = m2 >> 1;

    let mut z0 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut z1 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut z2 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut high = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    let mut low = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };

    zinit(&mut z0);
    zinit(&mut z1);
    zinit(&mut z2);
    zinit(&mut high);
    zinit(&mut low);

    zsplit(&mut high, &mut low, b, m2);
    zsqr(&mut z0, &mut low);
    zsqr(&mut z2, &mut high);
    zmul(&mut z1, &mut low, &mut high);
    
    // Create temporary variables for zlsh operations
    let mut tmp_z1 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    zinit(&mut tmp_z1);
    zlsh(&mut tmp_z1, &z1, m2 + 1);
    
    m2 <<= 1;
    
    let mut tmp_z2 = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    zinit(&mut tmp_z2);
    zlsh(&mut tmp_z2, &z2, m2);
    
    // Fix the zadd calls to avoid borrowing conflicts
    let mut tmp_a = Z { sign: 0, used: 0, alloced: 0, chars: Option::None };
    zinit(&mut tmp_a);
    zadd(&mut tmp_a, &tmp_z2, &tmp_z1);
    zadd(a, &tmp_a, &z0);
    zfree(&mut tmp_a);
    
    zfree(&mut z0);
    zfree(&mut z1);
    zfree(&mut z2);
    zfree(&mut high);
    zfree(&mut low);
    zfree(&mut tmp_z1);
    zfree(&mut tmp_z2);

    b.sign = sign;
    a.sign = 1;
}
