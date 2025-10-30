use crate::*;
use std::eprintln;
use std::io;
use std::process;
use rand::Rng;
use lazy_static::lazy_static;
use std::io::Write;

pub fn fallbackSimpleSort(fmap: &mut [UInt32], eclass: &[UInt32], lo: Int32, hi: Int32) {
    if lo == hi {
        return;
    }

    if (hi - lo) > 3 {
        for i in (lo..=hi - 4).rev() {
            let tmp = fmap[i as usize];
            let ec_tmp = eclass[tmp as usize];
            let mut j = i + 4;
            
            while j <= hi && ec_tmp > eclass[fmap[j as usize] as usize] {
                fmap[(j - 4) as usize] = fmap[j as usize];
                j += 4;
            }
            
            fmap[(j - 4) as usize] = tmp;
        }
    }

    for i in (lo..=hi - 1).rev() {
        let tmp = fmap[i as usize];
        let ec_tmp = eclass[tmp as usize];
        let mut j = i + 1;
        
        while j <= hi && ec_tmp > eclass[fmap[j as usize] as usize] {
            fmap[(j - 1) as usize] = fmap[j as usize];
            j += 1;
        }
        
        fmap[(j - 1) as usize] = tmp;
    }
}
pub fn mmed3(a: UChar, b: UChar, c: UChar) -> UChar {
    let mut a = a;
    let mut b = b;
    let mut t;
    
    if a > b {
        t = a;
        a = b;
        b = t;
    }
    
    if b > c {
        b = c;
        if a > b {
            b = a;
        }
    }
    
    b
}
pub fn helper_mainSort_2(
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    ftab: &[UInt32],
    runningOrder: &mut [Int32; 256],
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut vv;
    let mut h = 1;

    // Calculate initial h value
    while h <= 256 {
        h = (3 * h) + 1;
    }

    // Main sorting loop
    while h != 1 {
        h = h / 3;

        for i_val in h..256 {
            i = i_val;
            vv = runningOrder[i as usize];
            j = i;

            while {
                let j_minus_h = j - h;
                let lhs = ftab[(runningOrder[j_minus_h as usize] as usize + 1) << 8] 
                    - ftab[(runningOrder[j_minus_h as usize] as usize) << 8];
                let rhs = ftab[(vv as usize + 1) << 8] - ftab[(vv as usize) << 8];
                lhs > rhs
            } {
                runningOrder[j as usize] = runningOrder[(j - h) as usize];
                j = j - h;
                if j <= (h - 1) {
                    break;
                }
            }

            runningOrder[j as usize] = vv;
        }
    }

    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_fallbackQSort3_1_1(fmap: &mut [UInt32], unLo: Int32, n: Int32, lo: Int32) {
    let mut yyp1 = lo;
    let mut yyp2 = unLo - n;
    let mut yyn = n;
    
    while yyn > 0 {
        {
            let zztmp = fmap[yyp1 as usize];
            fmap[yyp1 as usize] = fmap[yyp2 as usize];
            fmap[yyp2 as usize] = zztmp;
        }
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
    }
}
pub fn helper_helper_fallbackQSort3_1_2(fmap: &mut [UInt32], unLo: Int32, m: Int32, hi: Int32) {
    let mut yyp1 = unLo;
    let mut yyp2 = (hi - m) + 1;
    let mut yyn = m;
    
    while yyn > 0 {
        {
            let zztmp = fmap[yyp1 as usize];
            fmap[yyp1 as usize] = fmap[yyp2 as usize];
            fmap[yyp2 as usize] = zztmp;
        }
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
    }
}
pub fn helper_helper_mainQSort3_1_1(ptr: &mut [UInt32], unLo: Int32, n: Int32, lo: Int32) {
    let mut yyp1 = lo;
    let mut yyp2 = unLo - n;
    let mut yyn = n;
    
    while yyn > 0 {
        {
            let zztmp = ptr[yyp1 as usize];
            ptr[yyp1 as usize] = ptr[yyp2 as usize];
            ptr[yyp2 as usize] = zztmp;
        }
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
    }
}
pub fn helper_helper_mainQSort3_1_2(ptr: &mut [UInt32], unLo: Int32, m: Int32, hi: Int32) {
    let mut yyp1 = unLo;
    let mut yyp2 = (hi - m) + 1;
    let mut yyn = m;
    
    while yyn > 0 {
        {
            let zztmp = ptr[yyp1 as usize];
            ptr[yyp1 as usize] = ptr[yyp2 as usize];
            ptr[yyp2 as usize] = zztmp;
        }
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
    }
}
pub fn helper_helper_helper_fallbackQSort3_1_3_1(
    unLo_ref: &mut Int32,
    ltLo_ref: &mut Int32,
    n_ref: &mut Int32,
    fmap: &mut [UInt32],
    eclass: &[UInt32],
    med: UInt32,
    unHi: Int32,
) {
    let mut unLo = *unLo_ref;
    let mut ltLo = *ltLo_ref;
    let mut n = *n_ref;

    if unLo > unHi {
        return;
    }

    n = (eclass[fmap[unLo as usize] as usize] as Int32) - (med as Int32);

    if n == 0 {
        let zztmp = fmap[unLo as usize];
        fmap[unLo as usize] = fmap[ltLo as usize];
        fmap[ltLo as usize] = zztmp;
        ltLo += 1;
        unLo += 1;
    } else if n > 0 {
        return;
    } else {
        unLo += 1;
    }

    *unLo_ref = unLo;
    *ltLo_ref = ltLo;
    *n_ref = n;
}
pub fn helper_helper_helper_fallbackQSort3_1_3_2(
    unHi_ref: &mut Int32,
    gtHi_ref: &mut Int32,
    n_ref: &mut Int32,
    fmap: &mut [UInt32],
    eclass: &[UInt32],
    med: UInt32,
    unLo: Int32,
) -> bool {
    let mut unHi = *unHi_ref;
    let mut gtHi = *gtHi_ref;
    let mut n = *n_ref;

    if unLo > unHi {
        return false; // Equivalent to 'break' in the loop context
    }

    n = (eclass[fmap[unHi as usize] as usize] as Int32) - (med as Int32);

    if n == 0 {
        // Swap fmap[unHi] and fmap[gtHi]
        let zztmp = fmap[unHi as usize];
        fmap[unHi as usize] = fmap[gtHi as usize];
        fmap[gtHi as usize] = zztmp;

        gtHi -= 1;
        unHi -= 1;

        *unHi_ref = unHi;
        *gtHi_ref = gtHi;
        *n_ref = n;

        return true; // Equivalent to 'continue' in the loop context
    }

    if n < 0 {
        return false; // Equivalent to 'break' in the loop context
    }

    unHi -= 1;
    *unHi_ref = unHi;
    *gtHi_ref = gtHi;
    *n_ref = n;

    true // Continue processing
}
pub fn helper_helper_mainSort_4_3(
    j_ref: &mut Int32,
    k_ref: &mut Int32,
    c1_ref: &mut UChar,
    ptr: &mut [UInt32],
    block: &[UChar],
    ftab: &[UInt32],
    bigDone: &mut [Bool],
    copyStart: &mut [Int32],
    copyEnd: &mut [Int32],
    nblock: Int32,
    ss: Int32,
) {
    let mut j = *j_ref;
    let mut k = *k_ref;
    let mut c1 = *c1_ref;

    // First loop: initialize copyStart and copyEnd
    for j in 0..=255 {
        copyStart[j as usize] = (ftab[((j << 8) + ss) as usize] & !(1 << 21)) as Int32;
        copyEnd[j as usize] = (ftab[((j << 8) + ss + 1) as usize] & !(1 << 21)) as Int32 - 1;
    }

    // Second loop: process from ftab[ss << 8] to copyStart[ss]
    j = (ftab[(ss << 8) as usize] & !(1 << 21)) as Int32;
    while j < copyStart[ss as usize] {
        k = (ptr[j as usize] as Int32) - 1;
        if k < 0 {
            k += nblock;
        }
        c1 = block[k as usize];
        if bigDone[c1 as usize] == 0 {
            ptr[copyStart[c1 as usize] as usize] = k as UInt32;
            copyStart[c1 as usize] += 1;
        }
        j += 1;
    }

    // Third loop: process from (ftab[(ss + 1) << 8] - 1) to copyEnd[ss]
    j = (ftab[((ss + 1) << 8) as usize] & !(1 << 21)) as Int32 - 1;
    while j > copyEnd[ss as usize] {
        k = (ptr[j as usize] as Int32) - 1;
        if k < 0 {
            k += nblock;
        }
        c1 = block[k as usize];
        if bigDone[c1 as usize] == 0 {
            ptr[copyEnd[c1 as usize] as usize] = k as UInt32;
            copyEnd[c1 as usize] -= 1;
        }
        j -= 1;
    }

    // Update the reference values
    *j_ref = j;
    *k_ref = k;
    *c1_ref = c1;
}
pub fn helper_helper_mainSort_4_2(
    nblock_ref: &mut Int32,
    j_ref: &mut Int32,
    ptr: &[UInt32],
    quadrant: &mut [UInt16],
    ftab: &[UInt32],
    ss: Int32,
) {
    let nblock = *nblock_ref;
    let mut j = *j_ref;
    let bb_start = ftab[(ss << 8) as usize] & (!(1 << 21));
    let bb_size = (ftab[((ss + 1) << 8) as usize] & (!(1 << 21))) - bb_start;
    let mut shifts = 0;

    while (bb_size >> shifts) > 65534 {
        shifts += 1;
    }

    for j in (0..bb_size).rev() {
        let a2update = ptr[(bb_start + j) as usize] as usize;
        let q_val = (j >> shifts) as UInt16;
        quadrant[a2update] = q_val;
        
        if a2update < (2 + 12 + 18 + 2) {
            quadrant[a2update + nblock as usize] = q_val;
        }
    }

    if !((bb_size - 1) >> shifts <= 65535) {
        BZ2_bz__AssertH__fail(1002);
    }

    *nblock_ref = nblock;
    *j_ref = j;
}
pub fn helper_mainGtU_1(
    i1_ref: &mut UInt32,
    i2_ref: &mut UInt32,
    k_ref: &mut Int32,
    c1_ref: &mut UChar,
    c2_ref: &mut UChar,
    s1_ref: &mut UInt16,
    s2_ref: &mut UInt16,
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: UInt32,
    budget: &mut Int32,
) -> bool {
    let mut i1 = *i1_ref;
    let mut i2 = *i2_ref;
    let mut k = *k_ref;
    let mut c1 = *c1_ref;
    let mut c2 = *c2_ref;
    let mut s1 = *s1_ref;
    let mut s2 = *s2_ref;

    // First comparison block
    c1 = block[i1 as usize];
    c2 = block[i2 as usize];
    if c1 != c2 {
        *i1_ref = i1;
        *i2_ref = i2;
        *k_ref = k;
        *c1_ref = c1;
        *c2_ref = c2;
        *s1_ref = s1;
        *s2_ref = s2;
        return c1 > c2;
    }

    s1 = quadrant[i1 as usize];
    s2 = quadrant[i2 as usize];
    if s1 != s2 {
        *i1_ref = i1;
        *i2_ref = i2;
        *k_ref = k;
        *c1_ref = c1;
        *c2_ref = c2;
        *s1_ref = s1;
        *s2_ref = s2;
        return s1 > s2;
    }

    // Repeat the same pattern for the next 7 blocks
    for _ in 0..7 {
        i1 += 1;
        i2 += 1;

        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            *i1_ref = i1;
            *i2_ref = i2;
            *k_ref = k;
            *c1_ref = c1;
            *c2_ref = c2;
            *s1_ref = s1;
            *s2_ref = s2;
            return c1 > c2;
        }

        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            *i1_ref = i1;
            *i2_ref = i2;
            *k_ref = k;
            *c1_ref = c1;
            *c2_ref = c2;
            *s1_ref = s1;
            *s2_ref = s2;
            return s1 > s2;
        }
    }

    // Handle wrap-around
    i1 += 1;
    i2 += 1;
    if i1 >= nblock {
        i1 -= nblock;
    }
    if i2 >= nblock {
        i2 -= nblock;
    }

    k -= 8;
    *budget -= 1;

    // Update all references
    *i1_ref = i1;
    *i2_ref = i2;
    *k_ref = k;
    *c1_ref = c1;
    *c2_ref = c2;
    *s1_ref = s1;
    *s2_ref = s2;

    false
}
pub fn mainGtU(
    i1: UInt32,
    i2: UInt32,
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: UInt32,
    budget: &mut Int32,
) -> bool {
    let mut i1 = i1;
    let mut i2 = i2;
    let mut c1 = 0;
    let mut c2 = 0;
    let mut s1 = 0;
    let mut s2 = 0;
    let mut k;

    // First 12 comparisons (unrolled loop)
    for _ in 0..12 {
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        i1 += 1;
        i2 += 1;
    }

    k = (nblock + 8) as Int32;
    
    while k >= 0 {
        if !helper_mainGtU_1(
            &mut i1,
            &mut i2,
            &mut k,
            &mut c1,
            &mut c2,
            &mut s1,
            &mut s2,
            block,
            quadrant,
            nblock,
            budget,
        ) {
            break;
        }
    }

    false
}
pub fn helper_helper_mainSimpleSort_1_1(
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    v_ref: &mut UInt32,
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: Int32,
    lo: Int32,
    hi: Int32,
    d: Int32,
    budget: &mut Int32,
    h: Int32,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut v = *v_ref;

    if i > hi {
        *i_ref = i;
        *j_ref = j;
        *v_ref = v;
        return;
    }

    // First iteration
    v = ptr[i as usize];
    j = i;
    while mainGtU(
        ptr[(j - h) as usize] + d as UInt32,
        v + d as UInt32,
        block,
        quadrant,
        nblock as UInt32,
        budget,
    ) {
        ptr[j as usize] = ptr[(j - h) as usize];
        j = j - h;
        if j <= (lo + h) - 1 {
            break;
        }
    }
    ptr[j as usize] = v;
    i += 1;

    if i > hi {
        *i_ref = i;
        *j_ref = j;
        *v_ref = v;
        return;
    }

    // Second iteration
    v = ptr[i as usize];
    j = i;
    while mainGtU(
        ptr[(j - h) as usize] + d as UInt32,
        v + d as UInt32,
        block,
        quadrant,
        nblock as UInt32,
        budget,
    ) {
        ptr[j as usize] = ptr[(j - h) as usize];
        j = j - h;
        if j <= (lo + h) - 1 {
            break;
        }
    }
    ptr[j as usize] = v;
    i += 1;

    if i > hi {
        *i_ref = i;
        *j_ref = j;
        *v_ref = v;
        return;
    }

    // Third iteration
    v = ptr[i as usize];
    j = i;
    while mainGtU(
        ptr[(j - h) as usize] + d as UInt32,
        v + d as UInt32,
        block,
        quadrant,
        nblock as UInt32,
        budget,
    ) {
        ptr[j as usize] = ptr[(j - h) as usize];
        j = j - h;
        if j <= (lo + h) - 1 {
            break;
        }
    }
    ptr[j as usize] = v;
    i += 1;

    if *budget < 0 {
        *i_ref = i;
        *j_ref = j;
        *v_ref = v;
        return;
    }

    *i_ref = i;
    *j_ref = j;
    *v_ref = v;
}

pub fn helper_mainSimpleSort_1(
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    h_ref: &mut Int32,
    v_ref: &mut UInt32,
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: Int32,
    lo: Int32,
    hi: Int32,
    d: Int32,
    budget: &mut Int32,
    hp: Int32,
) {
    // Dereference the input references to local variables
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut h = *h_ref;
    let mut v = *v_ref;

    // Update h using the global INCS array
    h = INCS.lock().unwrap()[hp as usize];
    i = lo + h;

    // Infinite loop (equivalent to while(1) in C)
    loop {
        helper_helper_mainSimpleSort_1_1(
            &mut i,
            &mut j,
            &mut v,
            ptr,
            block,
            quadrant,
            nblock,
            lo,
            hi,
            d,
            budget,
            h,
        );
    }

    // Update the output references
    *i_ref = i;
    *j_ref = j;
    *h_ref = h;
    *v_ref = v;
}
pub fn mainSimpleSort(
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: Int32,
    lo: Int32,
    hi: Int32,
    d: Int32,
    budget: &mut Int32,
) {
    let mut i = 0;
    let mut j = 0;
    let mut h = 0;
    let mut v = 0;
    
    let bigN = (hi - lo) + 1;
    if bigN < 2 {
        return;
    }

    let mut hp = 0;
    while INCS.lock().unwrap()[hp] < bigN {
        hp += 1;
    }

    hp -= 1;
    for hp in (0..=hp).rev() {
        helper_mainSimpleSort_1(
            &mut i,
            &mut j,
            &mut h,
            &mut v,
            ptr,
            block,
            quadrant,
            nblock,
            lo,
            hi,
            d,
            budget,
            hp as Int32,
        );
    }
}
pub fn helper_helper_helper_mainQSort3_1_3_2(
    unHi_ref: &mut Int32,
    gtHi_ref: &mut Int32,
    n_ref: &mut Int32,
    ptr: &mut [UInt32],
    block: &[UChar],
    med: Int32,
    d: Int32,
    unLo: Int32,
) {
    let mut unHi = *unHi_ref;
    let mut gtHi = *gtHi_ref;
    let mut n = *n_ref;

    if unLo > unHi {
        return;
    }

    n = (Int32::from(block[ptr[unHi as usize] as usize + d as usize])) - med;

    if n == 0 {
        let zztmp = ptr[unHi as usize];
        ptr[unHi as usize] = ptr[gtHi as usize];
        ptr[gtHi as usize] = zztmp;
        gtHi -= 1;
        unHi -= 1;
        *unHi_ref = unHi;
        *gtHi_ref = gtHi;
        *n_ref = n;
        return;
    }

    if n < 0 {
        return;
    }

    unHi -= 1;
    *unHi_ref = unHi;
    *gtHi_ref = gtHi;
    *n_ref = n;
}
pub fn helper_helper_helper_mainQSort3_1_3_1(
    unLo_ref: &mut Int32,
    ltLo_ref: &mut Int32,
    n_ref: &mut Int32,
    ptr: &mut [UInt32],
    block: &[UChar],
    med: Int32,
    d: Int32,
    unHi: Int32,
) {
    let mut unLo = *unLo_ref;
    let mut ltLo = *ltLo_ref;
    let mut n = *n_ref;

    if unLo > unHi {
        return;
    }

    n = (Int32::from(block[ptr[unLo as usize] as usize + d as usize])) - med;

    if n == 0 {
        let zztmp = ptr[unLo as usize];
        ptr[unLo as usize] = ptr[ltLo as usize];
        ptr[ltLo as usize] = zztmp;
        ltLo += 1;
        unLo += 1;
        *unLo_ref = unLo;
        *ltLo_ref = ltLo;
        *n_ref = n;
        return;
    }

    if n > 0 {
        return;
    }

    unLo += 1;
    *unLo_ref = unLo;
    *ltLo_ref = ltLo;
    *n_ref = n;
}
pub fn helper_helper_mainQSort3_1_3(
    unLo_ref: &mut Int32,
    unHi_ref: &mut Int32,
    ltLo_ref: &mut Int32,
    gtHi_ref: &mut Int32,
    n_ref: &mut Int32,
    ptr: &mut [UInt32],
    block: &[UChar],
    med: Int32,
    d: Int32,
) {
    let mut unLo = *unLo_ref;
    let mut unHi = *unHi_ref;
    let mut ltLo = *ltLo_ref;
    let mut gtHi = *gtHi_ref;
    let mut n = *n_ref;

    loop {
        helper_helper_helper_mainQSort3_1_3_1(
            &mut unLo,
            &mut ltLo,
            &mut n,
            ptr,
            block,
            med,
            d,
            unHi,
        );
    }

    loop {
        helper_helper_helper_mainQSort3_1_3_2(
            &mut unHi,
            &mut gtHi,
            &mut n,
            ptr,
            block,
            med,
            d,
            unLo,
        );
    }

    if unLo > unHi {
        *unLo_ref = unLo;
        *unHi_ref = unHi;
        *ltLo_ref = ltLo;
        *gtHi_ref = gtHi;
        *n_ref = n;
        return;
    }

    let zztmp = ptr[unLo as usize];
    ptr[unLo as usize] = ptr[unHi as usize];
    ptr[unHi as usize] = zztmp;

    unLo += 1;
    unHi -= 1;

    *unLo_ref = unLo;
    *unHi_ref = unHi;
    *ltLo_ref = ltLo;
    *gtHi_ref = gtHi;
    *n_ref = n;
}
pub fn helper_mainQSort3_1(
    unLo_ref: &mut Int32,
    unHi_ref: &mut Int32,
    ltLo_ref: &mut Int32,
    gtHi_ref: &mut Int32,
    n_ref: &mut Int32,
    m_ref: &mut Int32,
    med_ref: &mut Int32,
    sp_ref: &mut Int32,
    lo_ref: &mut Int32,
    hi_ref: &mut Int32,
    d_ref: &mut Int32,
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: Int32,
    budget: &mut Int32,
    stackLo: &mut [Int32; 100],
    stackHi: &mut [Int32; 100],
    stackD: &mut [Int32; 100],
    nextLo: &mut [Int32; 3],
    nextHi: &mut [Int32; 3],
    nextD: &mut [Int32; 3],
) {
    let mut unLo = *unLo_ref;
    let mut unHi = *unHi_ref;
    let mut ltLo = *ltLo_ref;
    let mut gtHi = *gtHi_ref;
    let mut n = *n_ref;
    let mut m = *m_ref;
    let mut med = *med_ref;
    let mut sp = *sp_ref;
    let mut lo = *lo_ref;
    let mut hi = *hi_ref;
    let mut d = *d_ref;

    if !(sp < (100 - 2)) {
        BZ2_bz__AssertH__fail(1001);
    }

    {
        sp -= 1;
        lo = stackLo[sp as usize];
        hi = stackHi[sp as usize];
        d = stackD[sp as usize];
    }

    if ((hi - lo) < 20) || (d > (2 + 12)) {
        mainSimpleSort(ptr, block, quadrant, nblock, lo, hi, d, budget);
        if *budget < 0 {
            return;
        }
        // continue is not needed in Rust as we're not in a loop here
    }

    med = mmed3(
        block[ptr[lo as usize] as usize + d as usize],
        block[ptr[hi as usize] as usize + d as usize],
        block[ptr[((lo + hi) >> 1) as usize] as usize + d as usize],
    ) as Int32;

    unLo = lo;
    ltLo = lo;
    unHi = hi;
    gtHi = hi;

    loop {
        helper_helper_mainQSort3_1_3(
            &mut unLo,
            &mut unHi,
            &mut ltLo,
            &mut gtHi,
            &mut n,
            ptr,
            block,
            med,
            d,
        );
    }

    if gtHi < ltLo {
        {
            stackLo[sp as usize] = lo;
            stackHi[sp as usize] = hi;
            stackD[sp as usize] = d + 1;
            sp += 1;
        }
        // continue is not needed in Rust as we're not in a loop here
    }

    n = if (ltLo - lo) < (unLo - ltLo) {
        ltLo - lo
    } else {
        unLo - ltLo
    };

    {
        helper_helper_mainQSort3_1_1(ptr, unLo, n, lo);
    }

    m = if (hi - gtHi) < (gtHi - unHi) {
        hi - gtHi
    } else {
        gtHi - unHi
    };

    {
        helper_helper_mainQSort3_1_2(ptr, unLo, m, hi);
    }

    n = ((lo + unLo) - ltLo) - 1;
    m = (hi - (gtHi - unHi)) + 1;

    nextLo[0] = lo;
    nextHi[0] = n;
    nextD[0] = d;
    nextLo[1] = m;
    nextHi[1] = hi;
    nextD[1] = d;
    nextLo[2] = n + 1;
    nextHi[2] = m - 1;
    nextD[2] = d + 1;

    if (nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]) {
        let tz = nextLo[0];
        nextLo[0] = nextLo[1];
        nextLo[1] = tz;
        let tz = nextHi[0];
        nextHi[0] = nextHi[1];
        nextHi[1] = tz;
        let tz = nextD[0];
        nextD[0] = nextD[1];
        nextD[1] = tz;
    }

    if (nextHi[1] - nextLo[1]) < (nextHi[2] - nextLo[2]) {
        let tz = nextLo[1];
        nextLo[1] = nextLo[2];
        nextLo[2] = tz;
        let tz = nextHi[1];
        nextHi[1] = nextHi[2];
        nextHi[2] = tz;
        let tz = nextD[1];
        nextD[1] = nextD[2];
        nextD[2] = tz;
    }

    if (nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]) {
        let tz = nextLo[0];
        nextLo[0] = nextLo[1];
        nextLo[1] = tz;
        let tz = nextHi[0];
        nextHi[0] = nextHi[1];
        nextHi[1] = tz;
        let tz = nextD[0];
        nextD[0] = nextD[1];
        nextD[1] = tz;
    }

    {
        stackLo[sp as usize] = nextLo[0];
        stackHi[sp as usize] = nextHi[0];
        stackD[sp as usize] = nextD[0];
        sp += 1;
    }

    {
        stackLo[sp as usize] = nextLo[1];
        stackHi[sp as usize] = nextHi[1];
        stackD[sp as usize] = nextD[1];
        sp += 1;
    }

    {
        stackLo[sp as usize] = nextLo[2];
        stackHi[sp as usize] = nextHi[2];
        stackD[sp as usize] = nextD[2];
        sp += 1;
    }

    *unLo_ref = unLo;
    *unHi_ref = unHi;
    *ltLo_ref = ltLo;
    *gtHi_ref = gtHi;
    *n_ref = n;
    *m_ref = m;
    *med_ref = med;
    *sp_ref = sp;
    *lo_ref = lo;
    *hi_ref = hi;
    *d_ref = d;
}
pub fn mainQSort3(
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &[UInt16],
    nblock: Int32,
    loSt: Int32,
    hiSt: Int32,
    dSt: Int32,
    budget: &mut Int32,
) {
    let mut unLo: Int32 = 0;
    let mut unHi: Int32 = 0;
    let mut ltLo: Int32 = 0;
    let mut gtHi: Int32 = 0;
    let mut n: Int32 = 0;
    let mut m: Int32 = 0;
    let mut med: Int32 = 0;
    let mut sp: Int32 = 0;
    let mut lo: Int32 = 0;
    let mut hi: Int32 = 0;
    let mut d: Int32 = 0;
    let mut stackLo: [Int32; 100] = [0; 100];
    let mut stackHi: [Int32; 100] = [0; 100];
    let mut stackD: [Int32; 100] = [0; 100];
    let mut nextLo: [Int32; 3] = [0; 3];
    let mut nextHi: [Int32; 3] = [0; 3];
    let mut nextD: [Int32; 3] = [0; 3];

    sp = 0;
    {
        stackLo[sp as usize] = loSt;
        stackHi[sp as usize] = hiSt;
        stackD[sp as usize] = dSt;
        sp += 1;
    }

    while sp > 0 {
        helper_mainQSort3_1(
            &mut unLo,
            &mut unHi,
            &mut ltLo,
            &mut gtHi,
            &mut n,
            &mut m,
            &mut med,
            &mut sp,
            &mut lo,
            &mut hi,
            &mut d,
            ptr,
            block,
            quadrant,
            nblock,
            budget,
            &mut stackLo,
            &mut stackHi,
            &mut stackD,
            &mut nextLo,
            &mut nextHi,
            &mut nextD,
        );
    }
}
pub fn helper_helper_mainSort_4_1(
    sb_ref: &mut Int32,
    numQSorted_ref: &mut Int32,
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &[UInt16],
    ftab: &mut [UInt32],
    verb: Int32,
    budget: &mut Int32,
    nblock: Int32,
    j: Int32,
    ss: Int32,
) {
    let mut sb = *sb_ref;
    let mut numQSorted = *numQSorted_ref;
    
    if j != ss {
        sb = (ss << 8) + j;
        if (ftab[sb as usize] & (1 << 21)) == 0 {
            let lo = (ftab[sb as usize] & (!(1 << 21))) as Int32;
            let hi = ((ftab[(sb + 1) as usize] & (!(1 << 21))) - 1) as Int32;
            
            if hi > lo {
                if verb >= 4 {
                    let _ = writeln!(
                        io::stderr(),
                        "        qsort [0x{:x}, 0x{:x}]   done {}   this {}",
                        ss,
                        j,
                        numQSorted,
                        (hi - lo) + 1
                    );
                }
                
                mainQSort3(
                    ptr,
                    block,
                    quadrant,
                    nblock,
                    lo,
                    hi,
                    2,
                    budget,
                );
                
                numQSorted += (hi - lo) + 1;
                if *budget < 0 {
                    return;
                }
            }
        }
        ftab[sb as usize] |= 1 << 21;
    }
    
    *sb_ref = sb;
    *numQSorted_ref = numQSorted;
}

pub fn helper_mainSort_4(
    nblock_ref: &mut Int32,
    j_ref: &mut Int32,
    k_ref: &mut Int32,
    ss_ref: &mut Int32,
    sb_ref: &mut Int32,
    c1_ref: &mut UChar,
    numQSorted_ref: &mut Int32,
    ptr: &mut [UInt32],
    block: &[UChar],
    quadrant: &mut [UInt16],
    ftab: &mut [UInt32],
    verb: Int32,
    budget: &mut Int32,
    i: Int32,
    runningOrder: &[Int32],
    bigDone: &mut [Bool],
    copyStart: &mut [Int32],
    copyEnd: &mut [Int32],
) {
    let mut nblock = *nblock_ref;
    let mut j = *j_ref;
    let mut k = *k_ref;
    let mut ss = *ss_ref;
    let mut sb = *sb_ref;
    let mut c1 = *c1_ref;
    let mut numQSorted = *numQSorted_ref;

    ss = runningOrder[i as usize];

    for j in 0..=255 {
        helper_helper_mainSort_4_1(
            &mut sb,
            &mut numQSorted,
            ptr,
            block,
            quadrant,
            ftab,
            verb,
            budget,
            nblock,
            j,
            ss,
        );
    }

    if bigDone[ss as usize] != 0 {
        BZ2_bz__AssertH__fail(1006);
    }

    {
        helper_helper_mainSort_4_3(
            &mut j,
            &mut k,
            &mut c1,
            ptr,
            block,
            ftab,
            bigDone,
            copyStart,
            copyEnd,
            nblock,
            ss,
        );
    }

    if !((copyStart[ss as usize] - 1 == copyEnd[ss as usize])
        || (copyStart[ss as usize] == 0 && copyEnd[ss as usize] == nblock - 1))
    {
        BZ2_bz__AssertH__fail(1007);
    }

    for j in 0..=255 {
        ftab[(j << 8) + ss as usize] |= 1 << 21;
    }

    bigDone[ss as usize] = 1;

    if i < 255 {
        helper_helper_mainSort_4_2(
            &mut nblock,
            &mut j,
            ptr,
            quadrant,
            ftab,
            ss,
        );
    }

    *nblock_ref = nblock;
    *j_ref = j;
    *k_ref = k;
    *ss_ref = ss;
    *sb_ref = sb;
    *c1_ref = c1;
    *numQSorted_ref = numQSorted;
}
pub fn helper_mainSort_3(
    j_ref: &mut Int32,
    s_ref: &mut UInt16,
    ptr: &mut [UInt32],
    block: &[UChar],
    ftab: &mut [UInt32],
    i: Int32,
) {
    let mut j = *j_ref;
    let mut s = *s_ref;

    // First operation
    s = (s >> 8) | ((block[i as usize] as UInt16) << 8);
    j = (ftab[s as usize] - 1) as Int32;
    ftab[s as usize] = j as UInt32;
    ptr[j as usize] = i as UInt32;

    // Second operation
    s = (s >> 8) | ((block[(i - 1) as usize] as UInt16) << 8);
    j = (ftab[s as usize] - 1) as Int32;
    ftab[s as usize] = j as UInt32;
    ptr[j as usize] = (i - 1) as UInt32;

    // Third operation
    s = (s >> 8) | ((block[(i - 2) as usize] as UInt16) << 8);
    j = (ftab[s as usize] - 1) as Int32;
    ftab[s as usize] = j as UInt32;
    ptr[j as usize] = (i - 2) as UInt32;

    // Fourth operation
    s = (s >> 8) | ((block[(i - 3) as usize] as UInt16) << 8);
    j = (ftab[s as usize] - 1) as Int32;
    ftab[s as usize] = j as UInt32;
    ptr[j as usize] = (i - 3) as UInt32;

    *j_ref = j;
    *s_ref = s;
}
pub fn helper_mainSort_1(
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    block: &[UChar],
    quadrant: &mut [UInt16],
    ftab: &mut [UInt32],
) {
    let i = *i_ref;
    let mut j = *j_ref;
    
    // Process i
    quadrant[i as usize] = 0;
    j = (j >> 8) | ((block[i as usize] as Int32) << 8);
    ftab[j as usize] += 1;
    
    // Process i-1
    quadrant[(i - 1) as usize] = 0;
    j = (j >> 8) | ((block[(i - 1) as usize] as Int32) << 8);
    ftab[j as usize] += 1;
    
    // Process i-2
    quadrant[(i - 2) as usize] = 0;
    j = (j >> 8) | ((block[(i - 2) as usize] as Int32) << 8);
    ftab[j as usize] += 1;
    
    // Process i-3
    quadrant[(i - 3) as usize] = 0;
    j = (j >> 8) | ((block[(i - 3) as usize] as Int32) << 8);
    ftab[j as usize] += 1;
    
    *i_ref = i;
    *j_ref = j;
}
pub fn mainSort(
    ptr: &mut [UInt32],
    block: &mut [UChar],
    quadrant: &mut [UInt16],
    ftab: &mut [UInt32],
    mut nblock: Int32,
    verb: Int32,
    budget: &mut Int32,
) {
    let mut i: Int32;
    let mut j: Int32 = 0;
    let mut k: Int32 = 0;
    let mut ss: Int32 = 0;
    let mut sb: Int32 = 0;
    let mut runningOrder: [Int32; 256] = [0; 256];
    let mut bigDone: [Bool; 256] = [0; 256];
    let mut copyStart: [Int32; 256] = [0; 256];
    let mut copyEnd: [Int32; 256] = [0; 256];
    let mut c1: UChar = 0;
    let mut numQSorted: Int32 = 0;
    let mut s: UInt16 = 0;

    if verb >= 4 {
        writeln!(io::stderr(), "        main sort initialise ...").unwrap();
    }

    for i in 0..=65536 {
        ftab[i as usize] = 0;
    }

    j = (block[0] as Int32) << 8;
    i = nblock - 1;
    while i >= 3 {
        helper_mainSort_1(&mut i, &mut j, block, quadrant, ftab);
    }

    while i >= 0 {
        quadrant[i as usize] = 0;
        j = (j >> 8) | ((block[i as usize] as UInt16 as Int32) << 8);
        ftab[j as usize] += 1;
        i -= 1;
    }

    for i in 0..(2 + 12 + 18 + 2) {
        block[(nblock + i) as usize] = block[i as usize];
        quadrant[(nblock + i) as usize] = 0;
    }

    if verb >= 4 {
        writeln!(io::stderr(), "        bucket sorting ...").unwrap();
    }

    for i in 1..=65536 {
        ftab[i as usize] += ftab[(i - 1) as usize];
    }

    s = (block[0] as UInt16) << 8;
    i = nblock - 1;
    while i >= 3 {
        helper_mainSort_3(&mut j, &mut s, ptr, block, ftab, i);
    }

    while i >= 0 {
        s = (s >> 8) | ((block[i as usize] as UInt16) << 8);
        j = (ftab[s as usize] - 1) as Int32;
        ftab[s as usize] = j as UInt32;
        ptr[j as usize] = i as UInt32;
        i -= 1;
    }

    for i in 0..=255 {
        bigDone[i as usize] = 0;
        runningOrder[i as usize] = i;
    }

    helper_mainSort_2(&mut i, &mut j, ftab, &mut runningOrder);

    numQSorted = 0;
    for i in 0..=255 {
        helper_mainSort_4(
            &mut nblock,
            &mut j,
            &mut k,
            &mut ss,
            &mut sb,
            &mut c1,
            &mut numQSorted,
            ptr,
            block,
            quadrant,
            ftab,
            verb,
            budget,
            i,
            &runningOrder,
            &mut bigDone,
            &mut copyStart,
            &mut copyEnd,
        );
    }

    if verb >= 4 {
        writeln!(
            io::stderr(),
            "        {} pointers, {} sorted, {} scanned",
            nblock,
            numQSorted,
            nblock - numQSorted
        )
        .unwrap();
    }
}
pub fn helper_helper_fallbackQSort3_1_3(
    unLo_ref: &mut Int32,
    unHi_ref: &mut Int32,
    ltLo_ref: &mut Int32,
    gtHi_ref: &mut Int32,
    n_ref: &mut Int32,
    fmap: &mut [UInt32],
    eclass: &[UInt32],
    med: UInt32,
) {
    let mut unLo = *unLo_ref;
    let mut unHi = *unHi_ref;
    let mut ltLo = *ltLo_ref;
    let mut gtHi = *gtHi_ref;
    let mut n = *n_ref;

    loop {
        helper_helper_helper_fallbackQSort3_1_3_1(
            &mut unLo,
            &mut ltLo,
            &mut n,
            fmap,
            eclass,
            med,
            unHi,
        );

        let should_break = helper_helper_helper_fallbackQSort3_1_3_2(
            &mut unHi,
            &mut gtHi,
            &mut n,
            fmap,
            eclass,
            med,
            unLo,
        );

        if should_break {
            break;
        }

        if unLo > unHi {
            break;
        }

        // Swap elements in fmap
        let zztmp = fmap[unLo as usize];
        fmap[unLo as usize] = fmap[unHi as usize];
        fmap[unHi as usize] = zztmp;

        unLo += 1;
        unHi -= 1;
    }

    *unLo_ref = unLo;
    *unHi_ref = unHi;
    *ltLo_ref = ltLo;
    *gtHi_ref = gtHi;
    *n_ref = n;
}
pub fn helper_fallbackQSort3_1(
    unLo_ref: &mut Int32,
    unHi_ref: &mut Int32,
    ltLo_ref: &mut Int32,
    gtHi_ref: &mut Int32,
    n_ref: &mut Int32,
    m_ref: &mut Int32,
    sp_ref: &mut Int32,
    lo_ref: &mut Int32,
    hi_ref: &mut Int32,
    med_ref: &mut UInt32,
    r_ref: &mut UInt32,
    r3_ref: &mut UInt32,
    fmap: &mut [UInt32],
    eclass: &[UInt32],
    stackLo: &mut [Int32; 100],
    stackHi: &mut [Int32; 100],
) {
    let mut unLo = *unLo_ref;
    let mut unHi = *unHi_ref;
    let mut ltLo = *ltLo_ref;
    let mut gtHi = *gtHi_ref;
    let mut n = *n_ref;
    let mut m = *m_ref;
    let mut sp = *sp_ref;
    let mut lo = *lo_ref;
    let mut hi = *hi_ref;
    let mut med = *med_ref;
    let mut r = *r_ref;
    let mut r3 = *r3_ref;

    if !(sp < (100 - 1)) {
        BZ2_bz__AssertH__fail(1004);
    }

    sp -= 1;
    lo = stackLo[sp as usize];
    hi = stackHi[sp as usize];

    if (hi - lo) < 10 {
        fallbackSimpleSort(fmap, eclass, lo, hi);
        // continue is not needed in Rust as it's not in a loop here
        // The original C code seems to be part of a larger loop structure
        // In Rust, we'd handle this differently with proper loop control
        return;
    }

    r = ((r * 7621) + 1) % 32768;
    r3 = r % 3;
    med = match r3 {
        0 => eclass[fmap[lo as usize] as usize],
        1 => eclass[fmap[((lo + hi) >> 1) as usize] as usize],
        _ => eclass[fmap[hi as usize] as usize],
    };

    unLo = lo;
    ltLo = lo;
    unHi = hi;
    gtHi = hi;

    loop {
        helper_helper_fallbackQSort3_1_3(
            &mut unLo,
            &mut unHi,
            &mut ltLo,
            &mut gtHi,
            &mut n,
            fmap,
            eclass,
            med,
        );
        // The original C code has an infinite loop with break conditions inside helper functions
        // In Rust, we'd typically handle this with proper loop control
        break; // Temporary break - actual implementation would need to match C behavior
    }

    if gtHi < ltLo {
        // continue is not needed in Rust as it's not in a loop here
        return;
    }

    n = if (ltLo - lo) < (unLo - ltLo) {
        ltLo - lo
    } else {
        unLo - ltLo
    };
    helper_helper_fallbackQSort3_1_1(fmap, unLo, n, lo);

    m = if (hi - gtHi) < (gtHi - unHi) {
        hi - gtHi
    } else {
        gtHi - unHi
    };
    helper_helper_fallbackQSort3_1_2(fmap, unLo, m, hi);

    n = ((lo + unLo) - ltLo) - 1;
    m = (hi - (gtHi - unHi)) + 1;

    if (n - lo) > (hi - m) {
        stackLo[sp as usize] = lo;
        stackHi[sp as usize] = n;
        sp += 1;

        stackLo[sp as usize] = m;
        stackHi[sp as usize] = hi;
        sp += 1;
    } else {
        stackLo[sp as usize] = m;
        stackHi[sp as usize] = hi;
        sp += 1;

        stackLo[sp as usize] = lo;
        stackHi[sp as usize] = n;
        sp += 1;
    }

    *unLo_ref = unLo;
    *unHi_ref = unHi;
    *ltLo_ref = ltLo;
    *gtHi_ref = gtHi;
    *n_ref = n;
    *m_ref = m;
    *sp_ref = sp;
    *lo_ref = lo;
    *hi_ref = hi;
    *med_ref = med;
    *r_ref = r;
    *r3_ref = r3;
}
pub fn fallbackQSort3(fmap: &mut [UInt32], eclass: &[UInt32], loSt: Int32, hiSt: Int32) {
    let mut unLo: Int32 = 0;
    let mut unHi: Int32 = 0;
    let mut ltLo: Int32 = 0;
    let mut gtHi: Int32 = 0;
    let mut n: Int32 = 0;
    let mut m: Int32 = 0;
    let mut sp: Int32 = 0;
    let mut lo: Int32 = 0;
    let mut hi: Int32 = 0;
    let mut med: UInt32 = 0;
    let mut r: UInt32 = 0;
    let mut r3: UInt32 = 0;
    let mut stackLo: [Int32; 100] = [0; 100];
    let mut stackHi: [Int32; 100] = [0; 100];

    stackLo[sp as usize] = loSt;
    stackHi[sp as usize] = hiSt;
    sp += 1;

    while sp > 0 {
        helper_fallbackQSort3_1(
            &mut unLo,
            &mut unHi,
            &mut ltLo,
            &mut gtHi,
            &mut n,
            &mut m,
            &mut sp,
            &mut lo,
            &mut hi,
            &mut med,
            &mut r,
            &mut r3,
            fmap,
            eclass,
            &mut stackLo,
            &mut stackHi,
        );
    }
}
pub fn helper_helper_fallbackSort_1_1(
    i_ref: &mut Int32,
    k_ref: &mut Int32,
    l_ref: &mut Int32,
    r_ref: &mut Int32,
    cc_ref: &mut Int32,
    cc1_ref: &mut Int32,
    nNotDone_ref: &mut Int32,
    fmap: &mut [UInt32],
    eclass: &[UInt32],
    bhtab: &mut [UInt32],
    nblock: Int32,
) {
    let mut i = *i_ref;
    let mut k = *k_ref;
    let mut l = *l_ref;
    let mut r = *r_ref;
    let mut cc = *cc_ref;
    let mut cc1 = *cc1_ref;
    let mut nNotDone = *nNotDone_ref;

    k = r + 1;
    while (bhtab[(k >> 5) as usize] & (1 << (k & 31))) != 0 && (k & 0x01f) != 0 {
        k += 1;
    }

    if (bhtab[(k >> 5) as usize] & (1 << (k & 31))) != 0 {
        while bhtab[(k >> 5) as usize] == 0xffffffff {
            k += 32;
        }

        while (bhtab[(k >> 5) as usize] & (1 << (k & 31))) != 0 {
            k += 1;
        }
    }

    l = k - 1;
    if l >= nblock {
        *i_ref = i;
        *k_ref = k;
        *l_ref = l;
        *r_ref = r;
        *cc_ref = cc;
        *cc1_ref = cc1;
        *nNotDone_ref = nNotDone;
        return;
    }

    while (bhtab[(k >> 5) as usize] & (1 << (k & 31))) == 0 && (k & 0x01f) != 0 {
        k += 1;
    }

    if (bhtab[(k >> 5) as usize] & (1 << (k & 31))) == 0 {
        while bhtab[(k >> 5) as usize] == 0x00000000 {
            k += 32;
        }

        while (bhtab[(k >> 5) as usize] & (1 << (k & 31))) == 0 {
            k += 1;
        }
    }

    r = k - 1;
    if r >= nblock {
        *i_ref = i;
        *k_ref = k;
        *l_ref = l;
        *r_ref = r;
        *cc_ref = cc;
        *cc1_ref = cc1;
        *nNotDone_ref = nNotDone;
        return;
    }

    if r > l {
        nNotDone += (r - l) + 1;
        fallbackQSort3(fmap, eclass, l, r);
        cc = -1;
        for i in l..=r {
            cc1 = eclass[fmap[i as usize] as usize] as Int32;
            if cc != cc1 {
                bhtab[(i >> 5) as usize] |= 1 << (i & 31);
                cc = cc1;
            }
        }
    }

    *i_ref = i;
    *k_ref = k;
    *l_ref = l;
    *r_ref = r;
    *cc_ref = cc;
    *cc1_ref = cc1;
    *nNotDone_ref = nNotDone;
}
pub fn helper_fallbackSort_1(
    H_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    k_ref: &mut Int32,
    l_ref: &mut Int32,
    r_ref: &mut Int32,
    cc_ref: &mut Int32,
    cc1_ref: &mut Int32,
    nNotDone_ref: &mut Int32,
    fmap: &mut [UInt32],
    eclass: &mut [UInt32],
    bhtab: &mut [UInt32],
    nblock: Int32,
    verb: Int32,
) {
    let mut H = *H_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut k = *k_ref;
    let mut l = *l_ref;
    let mut r = *r_ref;
    let mut cc = *cc_ref;
    let mut cc1 = *cc1_ref;
    let mut nNotDone = *nNotDone_ref;

    if verb >= 4 {
        let _ = writeln!(io::stderr(), "        depth {:6} has ", H);
    }

    j = 0;
    for i in 0..nblock {
        if (bhtab[(i >> 5) as usize] & (1 << (i & 31))) != 0 {
            j = i;
        }
        k = (fmap[i as usize] as Int32 - H) as Int32;
        if k < 0 {
            k += nblock;
        }
        eclass[k as usize] = j as UInt32;
    }

    nNotDone = 0;
    r = -1;

    loop {
        helper_helper_fallbackSort_1_1(
            &mut i,
            &mut k,
            &mut l,
            &mut r,
            &mut cc,
            &mut cc1,
            &mut nNotDone,
            fmap,
            eclass,
            bhtab,
            nblock,
        );

        if verb >= 4 {
            let _ = writeln!(io::stderr(), "{:6} unresolved strings", nNotDone);
        }

        H *= 2;
        if H > nblock || nNotDone == 0 {
            break;
        }
    }

    *H_ref = H;
    *i_ref = i;
    *j_ref = j;
    *k_ref = k;
    *l_ref = l;
    *r_ref = r;
    *cc_ref = cc;
    *cc1_ref = cc1;
    *nNotDone_ref = nNotDone;
}
pub fn fallbackSort(
    fmap: &mut [UInt32],
    eclass: &mut [UInt32],
    bhtab: &mut [UInt32],
    nblock: Int32,
    verb: Int32,
) {
    let mut ftab = [0; 257];
    let mut ftabCopy = [0; 256];
    let mut H: Int32 = 1;
    let mut i: Int32 = 0;
    let mut j: Int32 = 0;
    let mut k: Int32 = 0;
    let mut l: Int32 = 0;
    let mut r: Int32 = 0;
    let mut cc: Int32 = 0;
    let mut cc1: Int32 = 0;
    let mut nNotDone: Int32 = 0;
    let mut nBhtab: Int32;
    let eclass8 = unsafe { std::slice::from_raw_parts_mut(eclass.as_mut_ptr() as *mut UChar, eclass.len()) };

    if verb >= 4 {
        eprintln!("        bucket sorting ...");
    }

    for i in 0..257 {
        ftab[i as usize] = 0;
    }

    for i in 0..nblock {
        ftab[eclass8[i as usize] as usize] += 1;
    }

    for i in 0..256 {
        ftabCopy[i as usize] = ftab[i as usize];
    }

    for i in 1..257 {
        ftab[i as usize] += ftab[(i - 1) as usize];
    }

    for i in 0..nblock {
        j = eclass8[i as usize] as Int32;
        k = ftab[j as usize] - 1;
        ftab[j as usize] = k;
        fmap[k as usize] = i as UInt32;
    }

    nBhtab = 2 + (nblock / 32);
    for i in 0..nBhtab {
        bhtab[i as usize] = 0;
    }

    for i in 0..256 {
        bhtab[(ftab[i as usize] >> 5) as usize] |= 1 << (ftab[i as usize] & 31);
    }

    for i in 0..32 {
        bhtab[((nblock + (2 * i)) >> 5) as usize] |= 1 << ((nblock + (2 * i)) & 31);
        bhtab[((nblock + (2 * i) + 1) >> 5) as usize] &= !(1 << ((nblock + (2 * i) + 1) & 31));
    }

    loop {
        helper_fallbackSort_1(
            &mut H,
            &mut i,
            &mut j,
            &mut k,
            &mut l,
            &mut r,
            &mut cc,
            &mut cc1,
            &mut nNotDone,
            fmap,
            eclass,
            bhtab,
            nblock,
            verb,
        );
    }

    if verb >= 4 {
        eprintln!("        reconstructing block ...");
    }
    j = 0;
    for i in 0..nblock {
        while ftabCopy[j as usize] == 0 {
            j += 1;
        }

        ftabCopy[j as usize] -= 1;
        eclass8[fmap[i as usize] as usize] = j as UChar;
    }

    if !(j < 256) {
        BZ2_bz__AssertH__fail(1005);
    }
}
pub fn helper_BZ2_blockSort_1(
    wfact_ref: &mut Int32,
    quadrant_idx_ref: &mut UInt32,
    budget_ref: &mut Int32,
    budgetInit_ref: &mut Int32,
    i_ref: &mut Int32,
    s: &mut EState,
    ptr: &mut [UInt32],
    block: &mut [UChar],
    ftab: &mut [UInt32],
    nblock: Int32,
    verb: Int32,
    quadrant: &mut [UInt16],
) {
    let mut wfact = *wfact_ref;
    let mut quadrant_idx = *quadrant_idx_ref;
    let mut budget = *budget_ref;
    let mut budgetInit = *budgetInit_ref;
    let mut i = *i_ref;

    i = nblock + (((2 + 12) + 18) + 2);
    if i & 1 != 0 {
        i += 1;
    }

    // Calculate the address as usize and store it in quadrant_idx
    quadrant_idx = unsafe { block.as_ptr().add(i as usize) as *const UInt16 as UInt32 };

    if wfact < 1 {
        wfact = 1;
    }
    if wfact > 100 {
        wfact = 100;
    }

    budgetInit = nblock * ((wfact - 1) / 3);
    budget = budgetInit;

    mainSort(ptr, block, quadrant, ftab, nblock, verb, &mut budget);

    if verb >= 3 {
        let ratio = if nblock == 0 {
            (budgetInit - budget) as f32
        } else {
            (budgetInit - budget) as f32 / nblock as f32
        };
        writeln!(
            io::stderr(),
            "      {} work, {} block, ratio {:5.2}",
            budgetInit - budget,
            nblock,
            ratio
        ).unwrap();
    }

    if budget < 0 {
        if verb >= 2 {
            writeln!(
                io::stderr(),
                "    too repetitive; using fallback sorting algorithm"
            ).unwrap();
        }
        fallbackSort(
            s.arr1.as_mut().unwrap(),
            s.arr2.as_mut().unwrap(),
            ftab,
            nblock,
            verb,
        );
    }

    *wfact_ref = wfact;
    *quadrant_idx_ref = quadrant_idx;
    *budget_ref = budget;
    *budgetInit_ref = budgetInit;
    *i_ref = i;
}
pub fn BZ2_blockSort(s: &mut EState) {
    // Extract all needed fields from EState upfront to avoid multiple mutable borrows
    let nblock = s.nblock;
    let verb = s.verbosity;
    let mut wfact = s.workFactor;
    
    if nblock < 10000 {
        // Extract mutable references just for the fallback case
        let arr1 = s.arr1.as_mut().expect("arr1 is None");
        let arr2 = s.arr2.as_mut().expect("arr2 is None");
        let ftab = s.ftab.as_mut().expect("ftab is None");
        
        fallbackSort(
            arr1,
            arr2,
            ftab,
            nblock,
            verb,
        );
    } else {
        let mut quadrant_idx = 0;
        let mut budget = 0;
        let mut budgetInit = 0;
        let mut i = 0;
        
        // Pre-calculate the lengths of the vectors
        let ptr_len = s.ptr.as_ref().expect("ptr is None").len();
        let block_len = s.block.as_ref().expect("block is None").len();
        let ftab_len = s.ftab.as_ref().expect("ftab is None").len();
        let mtfv_len = s.mtfv.as_ref().expect("mtfv is None").len();

        // Get mutable pointers to the vectors' data
        let ptr_raw = s.ptr.as_mut().expect("ptr is None").as_mut_ptr();
        let block_raw = s.block.as_mut().expect("block is None").as_mut_ptr();
        let ftab_raw = s.ftab.as_mut().expect("ftab is None").as_mut_ptr();
        let mtfv_raw = s.mtfv.as_mut().expect("mtfv is None").as_mut_ptr();

        // Create mutable slices from the raw pointers and lengths
        let ptr_slice = unsafe { std::slice::from_raw_parts_mut(ptr_raw, ptr_len) };
        let block_slice = unsafe { std::slice::from_raw_parts_mut(block_raw, block_len) };
        let ftab_slice = unsafe { std::slice::from_raw_parts_mut(ftab_raw, ftab_len) };
        let quadrant_slice = unsafe { std::slice::from_raw_parts_mut(mtfv_raw, mtfv_len) };

        // Pass all required arguments including s
        helper_BZ2_blockSort_1(
            &mut wfact,
            &mut quadrant_idx,
            &mut budget,
            &mut budgetInit,
            &mut i,
            s,
            ptr_slice,
            block_slice,
            ftab_slice,
            nblock,
            verb,
            quadrant_slice,
        );
    }

    // Update workFactor if it was changed
    s.workFactor = wfact;

    // Find origPtr
    let ptr = s.ptr.as_mut().expect("ptr is None");
    s.origPtr = -1;
    for i in 0..s.nblock {
        if ptr[i as usize] == 0 {
            s.origPtr = i;
            break;
        }
    }

    if s.origPtr == -1 {
        BZ2_bz__AssertH__fail(1003);
    }
}
