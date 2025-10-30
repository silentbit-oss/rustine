use crate::*;
use rand::Rng;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::process;

pub fn fallbackSimpleSort(fmap: &mut [UInt32], eclass: &[UInt32], lo: Int32, hi: Int32) {
    if lo == hi {
        return;
    }

    if (hi - lo) > 3 {
        let mut i = hi - 4;
        while i >= lo {
            let tmp = fmap[i as usize];
            let ec_tmp = eclass[tmp as usize];
            let mut j = i + 4;
            
            while j <= hi && ec_tmp > eclass[fmap[j as usize] as usize] {
                fmap[(j - 4) as usize] = fmap[j as usize];
                j += 4;
            }
            
            fmap[(j - 4) as usize] = tmp;
            i -= 1;
        }
    }

    let mut i = hi - 1;
    while i >= lo {
        let tmp = fmap[i as usize];
        let ec_tmp = eclass[tmp as usize];
        let mut j = i + 1;
        
        while j <= hi && ec_tmp > eclass[fmap[j as usize] as usize] {
            fmap[(j - 1) as usize] = fmap[j as usize];
            j += 1;
        }
        
        fmap[(j - 1) as usize] = tmp;
        i -= 1;
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
    let mut k: Int32;
    let mut c1: UChar;
    let mut c2: UChar;
    let mut s1: UInt16;
    let mut s2: UInt16;

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
    loop {
        // First comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Second comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Third comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Fourth comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Fifth comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Sixth comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Seventh comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Eighth comparison in the block
        c1 = block[i1 as usize];
        c2 = block[i2 as usize];
        if c1 != c2 {
            return c1 > c2;
        }
        s1 = quadrant[i1 as usize];
        s2 = quadrant[i2 as usize];
        if s1 != s2 {
            return s1 > s2;
        }
        i1 += 1;
        i2 += 1;

        // Handle wrap-around
        if i1 >= nblock {
            i1 -= nblock;
        }
        if i2 >= nblock {
            i2 -= nblock;
        }

        k -= 8;
        *budget -= 1;

        if k < 0 {
            break;
        }
    }

    false
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
        let h = INCS.lock().unwrap()[hp];
        let mut i = lo + h;
        
        loop {
            if i > hi {
                break;
            }

            let v = ptr[i as usize];
            let mut j = i;
            while mainGtU(
                ptr[(j - h) as usize].wrapping_add(d as UInt32),
                v.wrapping_add(d as UInt32),
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
                break;
            }

            let v = ptr[i as usize];
            let mut j = i;
            while mainGtU(
                ptr[(j - h) as usize].wrapping_add(d as UInt32),
                v.wrapping_add(d as UInt32),
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
                break;
            }

            let v = ptr[i as usize];
            let mut j = i;
            while mainGtU(
                ptr[(j - h) as usize].wrapping_add(d as UInt32),
                v.wrapping_add(d as UInt32),
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
                return;
            }
        }
    }
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
    let mut unLo;
    let mut unHi;
    let mut ltLo;
    let mut gtHi;
    let mut n;
    let mut m;
    let mut med;
    let mut sp = 0;
    let mut lo;
    let mut hi;
    let mut d;
    let mut stackLo = [0; 100];
    let mut stackHi = [0; 100];
    let mut stackD = [0; 100];
    let mut nextLo = [0; 3];
    let mut nextHi = [0; 3];
    let mut nextD = [0; 3];
    let mut zztmp;
    let mut yyp1;
    let mut yyp2;
    let mut yyn;
    let mut tz;

    {
        stackLo[sp] = loSt;
        stackHi[sp] = hiSt;
        stackD[sp] = dSt;
        sp += 1;
    }

    while sp > 0 {
        {
            if !(sp < (100 - 2)) {
                BZ2_bz__AssertH__fail(1001);
            }
        }

        {
            sp -= 1;
            lo = stackLo[sp];
            hi = stackHi[sp];
            d = stackD[sp];
        }

        if ((hi - lo) < 20) || (d > (2 + 12)) {
            mainSimpleSort(ptr, block, quadrant, nblock, lo, hi, d, budget);
            if (*budget) < 0 {
                return;
            }
            continue;
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
            loop {
                if unLo > unHi {
                    break;
                }
                n = block[ptr[unLo as usize] as usize + d as usize] as Int32 - med;
                if n == 0 {
                    zztmp = ptr[unLo as usize];
                    ptr[unLo as usize] = ptr[ltLo as usize];
                    ptr[ltLo as usize] = zztmp;
                    ltLo += 1;
                    unLo += 1;
                    continue;
                }
                if n > 0 {
                    break;
                }
                unLo += 1;
            }

            loop {
                if unLo > unHi {
                    break;
                }
                n = block[ptr[unHi as usize] as usize + d as usize] as Int32 - med;
                if n == 0 {
                    zztmp = ptr[unHi as usize];
                    ptr[unHi as usize] = ptr[gtHi as usize];
                    ptr[gtHi as usize] = zztmp;
                    gtHi -= 1;
                    unHi -= 1;
                    continue;
                }
                if n < 0 {
                    break;
                }
                unHi -= 1;
            }

            if unLo > unHi {
                break;
            }

            zztmp = ptr[unLo as usize];
            ptr[unLo as usize] = ptr[unHi as usize];
            ptr[unHi as usize] = zztmp;
            unLo += 1;
            unHi -= 1;
        }

        if gtHi < ltLo {
            stackLo[sp] = lo;
            stackHi[sp] = hi;
            stackD[sp] = d + 1;
            sp += 1;
            continue;
        }

        n = if (ltLo - lo) < (unLo - ltLo) {
            ltLo - lo
        } else {
            unLo - ltLo
        };
        yyp1 = lo;
        yyp2 = unLo - n;
        yyn = n;
        while yyn > 0 {
            zztmp = ptr[yyp1 as usize];
            ptr[yyp1 as usize] = ptr[yyp2 as usize];
            ptr[yyp2 as usize] = zztmp;
            yyp1 += 1;
            yyp2 += 1;
            yyn -= 1;
        }

        m = if (hi - gtHi) < (gtHi - unHi) {
            hi - gtHi
        } else {
            gtHi - unHi
        };
        yyp1 = unLo;
        yyp2 = (hi - m) + 1;
        yyn = m;
        while yyn > 0 {
            zztmp = ptr[yyp1 as usize];
            ptr[yyp1 as usize] = ptr[yyp2 as usize];
            ptr[yyp2 as usize] = zztmp;
            yyp1 += 1;
            yyp2 += 1;
            yyn -= 1;
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
            tz = nextLo[0];
            nextLo[0] = nextLo[1];
            nextLo[1] = tz;
            tz = nextHi[0];
            nextHi[0] = nextHi[1];
            nextHi[1] = tz;
            tz = nextD[0];
            nextD[0] = nextD[1];
            nextD[1] = tz;
        }

        if (nextHi[1] - nextLo[1]) < (nextHi[2] - nextLo[2]) {
            tz = nextLo[1];
            nextLo[1] = nextLo[2];
            nextLo[2] = tz;
            tz = nextHi[1];
            nextHi[1] = nextHi[2];
            nextHi[2] = tz;
            tz = nextD[1];
            nextD[1] = nextD[2];
            nextD[2] = tz;
        }

        if (nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]) {
            tz = nextLo[0];
            nextLo[0] = nextLo[1];
            nextLo[1] = tz;
            tz = nextHi[0];
            nextHi[0] = nextHi[1];
            nextHi[1] = tz;
            tz = nextD[0];
            nextD[0] = nextD[1];
            nextD[1] = tz;
        }

        stackLo[sp] = nextLo[0];
        stackHi[sp] = nextHi[0];
        stackD[sp] = nextD[0];
        sp += 1;

        stackLo[sp] = nextLo[1];
        stackHi[sp] = nextHi[1];
        stackD[sp] = nextD[1];
        sp += 1;

        stackLo[sp] = nextLo[2];
        stackHi[sp] = nextHi[2];
        stackD[sp] = nextD[2];
        sp += 1;
    }
}
pub fn mainSort(
    ptr: &mut [UInt32],
    block: &mut [UChar],
    quadrant: &mut [UInt16],
    ftab: &mut [UInt32],
    nblock: Int32,
    verb: Int32,
    budget: &mut Int32,
) {
    let mut runningOrder = [0; 256];
    let mut bigDone = [0; 256];
    let mut copyStart = [0; 256];
    let mut copyEnd = [0; 256];
    let mut numQSorted = 0;
    let mut s: UInt16 = 0;

    if verb >= 4 {
        eprintln!("        main sort initialise ...");
    }

    // Initialize ftab
    for i in 0..=65536 {
        ftab[i as usize] = 0;
    }

    let mut j = (block[0] as UInt16) << 8;
    let mut i = nblock - 1;
    while i >= 3 {
        quadrant[i as usize] = 0;
        j = (j >> 8) | ((block[i as usize] as UInt16) << 8);
        ftab[j as usize] += 1;
        
        quadrant[(i - 1) as usize] = 0;
        j = (j >> 8) | ((block[(i - 1) as usize] as UInt16) << 8);
        ftab[j as usize] += 1;
        
        quadrant[(i - 2) as usize] = 0;
        j = (j >> 8) | ((block[(i - 2) as usize] as UInt16) << 8);
        ftab[j as usize] += 1;
        
        quadrant[(i - 3) as usize] = 0;
        j = (j >> 8) | ((block[(i - 3) as usize] as UInt16) << 8);
        ftab[j as usize] += 1;
        
        i -= 4;
    }

    while i >= 0 {
        quadrant[i as usize] = 0;
        j = (j >> 8) | ((block[i as usize] as UInt16) << 8);
        ftab[j as usize] += 1;
        i -= 1;
    }

    // Copy block and initialize quadrant
    for i in 0..(2 + 12 + 18 + 2) {
        let idx = (nblock + i) as usize;
        block[idx] = block[i as usize];
        quadrant[idx] = 0;
    }

    if verb >= 4 {
        eprintln!("        bucket sorting ...");
    }

    // Compute cumulative frequencies
    for i in 1..=65536 {
        ftab[i as usize] += ftab[(i - 1) as usize];
    }

    s = (block[0] as UInt16) << 8;
    i = nblock - 1;
    while i >= 3 {
        s = (s >> 8) | ((block[i as usize] as UInt16) << 8);
        let mut j = ftab[s as usize] - 1;
        ftab[s as usize] = j;
        ptr[j as usize] = i as UInt32;
        
        s = (s >> 8) | ((block[(i - 1) as usize] as UInt16) << 8);
        j = ftab[s as usize] - 1;
        ftab[s as usize] = j;
        ptr[j as usize] = (i - 1) as UInt32;
        
        s = (s >> 8) | ((block[(i - 2) as usize] as UInt16) << 8);
        j = ftab[s as usize] - 1;
        ftab[s as usize] = j;
        ptr[j as usize] = (i - 2) as UInt32;
        
        s = (s >> 8) | ((block[(i - 3) as usize] as UInt16) << 8);
        j = ftab[s as usize] - 1;
        ftab[s as usize] = j;
        ptr[j as usize] = (i - 3) as UInt32;
        
        i -= 4;
    }

    while i >= 0 {
        s = (s >> 8) | ((block[i as usize] as UInt16) << 8);
        let mut j = ftab[s as usize] - 1;
        ftab[s as usize] = j;
        ptr[j as usize] = i as UInt32;
        i -= 1;
    }

    // Initialize runningOrder and bigDone
    for i in 0..=255 {
        bigDone[i] = 0;
        runningOrder[i] = i as Int32;
    }

    // Shell sort
    let mut h = 1;
    while h <= 256 {
        h = (3 * h) + 1;
    }
    
    loop {
        h /= 3;
        for i in h..=255 {
            let vv = runningOrder[i];
            let mut j = i;
            while j >= h && (ftab[((runningOrder[j - h] + 1) << 8) as usize] - ftab[(runningOrder[j - h] << 8) as usize]) > 
                          (ftab[((vv + 1) << 8) as usize] - ftab[(vv << 8) as usize]) {
                runningOrder[j] = runningOrder[j - h];
                j -= h;
                if j < h {
                    break;
                }
            }
            runningOrder[j] = vv;
        }
        if h == 1 {
            break;
        }
    }

    numQSorted = 0;
    for i in 0..=255 {
        let ss = runningOrder[i];
        for j in 0..=255 {
            if j != ss {
                let sb = (ss << 8) + j;
                if (ftab[sb as usize] & (1 << 21)) == 0 {
                    let lo = (ftab[sb as usize] & !(1 << 21)) as Int32;
                    let hi = ((ftab[(sb + 1) as usize] & !(1 << 21)) - 1) as Int32;
                    if hi > lo {
                        if verb >= 4 {
                            eprintln!("        qsort [0x{:x}, 0x{:x}]   done {}   this {}", ss, j, numQSorted, (hi - lo) + 1);
                        }
                        mainQSort3(ptr, block, quadrant, nblock, lo, hi, 2, budget);
                        numQSorted += (hi - lo) + 1;
                        if *budget < 0 {
                            return;
                        }
                    }
                }
                ftab[sb as usize] |= 1 << 21;
            }
        }

        if bigDone[ss as usize] != 0 {
            BZ2_bz__AssertH__fail(1006);
        }

        for j in 0..=255 {
            copyStart[j as usize] = (ftab[((j << 8) + ss) as usize] & !(1 << 21)) as UInt32;
            copyEnd[j as usize] = ((ftab[(((j << 8) + ss) + 1) as usize] & !(1 << 21)) - 1) as UInt32;
        }

        for j in (ftab[(ss << 8) as usize] & !(1 << 21)) as usize..copyStart[ss as usize] as usize {
            let mut k = ptr[j] as Int32 - 1;
            if k < 0 {
                k += nblock;
            }
            let c1 = block[k as usize];
            if bigDone[c1 as usize] == 0 {
                ptr[copyStart[c1 as usize] as usize] = k as UInt32;
                copyStart[c1 as usize] += 1;
            }
        }

        for j in ((ftab[((ss + 1) << 8) as usize] & !(1 << 21)).saturating_sub(1) as usize)..=copyEnd[ss as usize] as usize {
            let mut k = ptr[j] as Int32 - 1;
            if k < 0 {
                k += nblock;
            }
            let c1 = block[k as usize];
            if bigDone[c1 as usize] == 0 {
                ptr[copyEnd[c1 as usize] as usize] = k as UInt32;
                copyEnd[c1 as usize] -= 1;
            }
        }

        if !((copyStart[ss as usize] - 1 == copyEnd[ss as usize]) || 
             (copyStart[ss as usize] == 0 && copyEnd[ss as usize] == (nblock - 1) as UInt32)) {
            BZ2_bz__AssertH__fail(1007);
        }

        for j in 0..=255 {
            ftab[((j << 8) + ss) as usize] |= 1 << 21;
        }

        bigDone[ss as usize] = 1;
        if i < 255 {
            let bbStart = ftab[(ss << 8) as usize] & !(1 << 21);
            let bbSize = (ftab[((ss + 1) << 8) as usize] & !(1 << 21)) - bbStart;
            let mut shifts = 0;
            while (bbSize >> shifts) > 65534 {
                shifts += 1;
            }

            for j in (0..bbSize as usize).rev() {
                let a2update = ptr[(bbStart as usize + j)] as Int32;
                let qVal = (j >> shifts) as UInt16;
                quadrant[a2update as usize] = qVal;
                if a2update < (2 + 12 + 18 + 2) {
                    quadrant[(a2update + nblock) as usize] = qVal;
                }
            }

            if !(((bbSize - 1) >> shifts) <= 65535) {
                BZ2_bz__AssertH__fail(1002);
            }
        }
    }

    if verb >= 4 {
        eprintln!("        {} pointers, {} sorted, {} scanned", nblock, numQSorted, nblock - numQSorted as Int32);
    }
}
pub fn fallbackQSort3(fmap: &mut [UInt32], eclass: &[UInt32], loSt: Int32, hiSt: Int32) {
    let mut unLo;
    let mut unHi;
    let mut ltLo;
    let mut gtHi;
    let mut n;
    let mut m;
    let mut sp;
    let mut lo;
    let mut hi;
    let mut med;
    let mut r = 0;
    let mut r3;
    let mut stackLo = [0; 100];
    let mut stackHi = [0; 100];
    
    sp = 0;
    {
        stackLo[sp] = loSt;
        stackHi[sp] = hiSt;
        sp += 1;
    }
    
    while sp > 0 {
        if !(sp < (100 - 1)) {
            BZ2_bz__AssertH__fail(1004);
        }
        
        {
            sp -= 1;
            lo = stackLo[sp];
            hi = stackHi[sp];
        }
        
        if (hi - lo) < 10 {
            fallbackSimpleSort(fmap, eclass, lo, hi);
            continue;
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
            loop {
                if unLo > unHi {
                    break;
                }
                n = (eclass[fmap[unLo as usize] as usize] as Int32) - (med as Int32);
                if n == 0 {
                    {
                        let zztmp = fmap[unLo as usize];
                        fmap[unLo as usize] = fmap[ltLo as usize];
                        fmap[ltLo as usize] = zztmp;
                    }
                    ltLo += 1;
                    unLo += 1;
                    continue;
                }
                if n > 0 {
                    break;
                }
                unLo += 1;
            }
            
            loop {
                if unLo > unHi {
                    break;
                }
                n = (eclass[fmap[unHi as usize] as usize] as Int32) - (med as Int32);
                if n == 0 {
                    {
                        let zztmp = fmap[unHi as usize];
                        fmap[unHi as usize] = fmap[gtHi as usize];
                        fmap[gtHi as usize] = zztmp;
                    }
                    gtHi -= 1;
                    unHi -= 1;
                    continue;
                }
                if n < 0 {
                    break;
                }
                unHi -= 1;
            }
            
            if unLo > unHi {
                break;
            }
            
            {
                let zztmp = fmap[unLo as usize];
                fmap[unLo as usize] = fmap[unHi as usize];
                fmap[unHi as usize] = zztmp;
            }
            unLo += 1;
            unHi -= 1;
        }
        
        if gtHi < ltLo {
            continue;
        }
        
        n = if (ltLo - lo) < (unLo - ltLo) {
            ltLo - lo
        } else {
            unLo - ltLo
        };
        
        {
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
        
        m = if (hi - gtHi) < (gtHi - unHi) {
            hi - gtHi
        } else {
            gtHi - unHi
        };
        
        {
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
        
        n = ((lo + unLo) - ltLo) - 1;
        m = (hi - (gtHi - unHi)) + 1;
        
        if (n - lo) > (hi - m) {
            {
                stackLo[sp] = lo;
                stackHi[sp] = n;
                sp += 1;
            }
            {
                stackLo[sp] = m;
                stackHi[sp] = hi;
                sp += 1;
            }
        } else {
            {
                stackLo[sp] = m;
                stackHi[sp] = hi;
                sp += 1;
            }
            {
                stackLo[sp] = lo;
                stackHi[sp] = n;
                sp += 1;
            }
        }
    }
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
    let mut H: Int32;
    let mut i: Int32;
    let mut j: Int32;
    let mut k: Int32;
    let mut l: Int32;
    let mut r: Int32;
    let mut cc: Int32;
    let mut cc1: Int32;
    let mut nNotDone: Int32;
    let mut nBhtab: Int32;
    let eclass8 = unsafe { std::slice::from_raw_parts_mut(eclass.as_mut_ptr() as *mut UChar, eclass.len()) };

    if verb >= 4 {
        eprintln!("        bucket sorting ...");
    }

    for i in 0..257 {
        ftab[i] = 0;
    }

    for i in 0..nblock as usize {
        ftab[eclass8[i] as usize] += 1;
    }

    for i in 0..256 {
        ftabCopy[i] = ftab[i];
    }

    for i in 1..257 {
        ftab[i] += ftab[i - 1];
    }

    for i in 0..nblock as usize {
        j = eclass8[i] as Int32;
        k = ftab[j as usize] - 1;
        ftab[j as usize] = k;
        fmap[k as usize] = i as UInt32;
    }

    nBhtab = 2 + (nblock / 32);
    for i in 0..nBhtab as usize {
        bhtab[i] = 0;
    }

    for i in 0..256 {
        bhtab[(ftab[i] >> 5) as usize] |= 1 << (ftab[i] & 31);
    }

    for i in 0..32 {
        bhtab[((nblock + (2 * i)) >> 5) as usize] |= 1 << ((nblock + (2 * i)) & 31);
        bhtab[((nblock + (2 * i) + 1) >> 5) as usize] &= !(1 << ((nblock + (2 * i) + 1) & 31));
    }

    H = 1;
    loop {
        if verb >= 4 {
            eprint!("        depth {:6} has ", H);
        }
        j = 0;
        for i in 0..nblock as usize {
            if (bhtab[i >> 5] & (1 << (i & 31))) != 0 {
                j = i as Int32;
            }
            k = fmap[i] as Int32 - H;
            if k < 0 {
                k += nblock;
            }
            eclass[k as usize] = j as UInt32;
        }

        nNotDone = 0;
        r = -1;
        loop {
            k = r + 1;
            while (bhtab[(k >> 5) as usize] & (1 << (k & 31))) != 0 && (k & 0x1f) != 0 {
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
                break;
            }
            while (bhtab[(k >> 5) as usize] & (1 << (k & 31))) == 0 && (k & 0x1f) != 0 {
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
                break;
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
        }

        if verb >= 4 {
            eprintln!("{:6} unresolved strings", nNotDone);
        }
        H *= 2;
        if H > nblock || nNotDone == 0 {
            break;
        }
    }

    if verb >= 4 {
        eprintln!("        reconstructing block ...");
    }
    j = 0;
    for i in 0..nblock as usize {
        while ftabCopy[j as usize] == 0 {
            j += 1;
        }
        ftabCopy[j as usize] -= 1;
        eclass8[fmap[i] as usize] = j as UChar;
    }

    if !(j < 256) {
        BZ2_bz__AssertH__fail(1005);
    }
}

pub fn BZ2_blockSort(s: &mut EState) {
    let ptr = s.ptr.as_mut().expect("ptr should be initialized");
    let block = s.block.as_mut().expect("block should be initialized");
    let ftab = s.ftab.as_mut().expect("ftab should be initialized");
    let nblock = s.nblock;
    let verb = s.verbosity;
    let wfact = s.workFactor;

    if nblock < 10000 {
        fallbackSort(
            s.arr1.as_mut().expect("arr1 should be initialized"),
            s.arr2.as_mut().expect("arr2 should be initialized"),
            ftab,
            nblock,
            verb,
        );
    } else {
        let mut i = nblock + (((2 + 12) + 18) + 2);
        if i & 1 != 0 {
            i += 1;
        }

        // Calculate quadrant pointer position
        let quadrant_start = i as usize;
        let quadrant = &mut block[quadrant_start..];

        // Safe conversion to UInt16 slice
        let quadrant_u16: &mut [UInt16] = unsafe {
            std::slice::from_raw_parts_mut(
                quadrant.as_mut_ptr() as *mut UInt16,
                quadrant.len() / std::mem::size_of::<UInt16>(),
            )
        };

        let wfact = wfact.clamp(1, 100);
        let budget_init = nblock * ((wfact - 1) / 3);
        let mut budget = budget_init;

        mainSort(ptr, block, quadrant_u16, ftab, nblock, verb, &mut budget);

        if verb >= 3 {
            eprintln!(
                "      {} work, {} block, ratio {:.2}",
                budget_init - budget,
                nblock,
                (f64::from(budget_init - budget)) / (if nblock == 0 { 1.0 } else { f64::from(nblock) })
            );
        }

        if budget < 0 {
            if verb >= 2 {
                eprintln!("    too repetitive; using fallback sorting algorithm");
            }
            fallbackSort(
                s.arr1.as_mut().expect("arr1 should be initialized"),
                s.arr2.as_mut().expect("arr2 should be initialized"),
                ftab,
                nblock,
                verb,
            );
        }
    }

    s.origPtr = -1;
    for (i, &val) in ptr.iter().enumerate().take(s.nblock as usize) {
        if val == 0 {
            s.origPtr = i as Int32;
            break;
        }
    }

    if s.origPtr == -1 {
        BZ2_bz__AssertH__fail(1003);
    }
}
