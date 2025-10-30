use crate::*;
use std::eprintln;
use std::io;
use std::process;
use rand::Rng;
use std::io::Write;

pub fn BZ2_bsInitWrite(s: &mut EState) {
    s.bsLive = 0;
    s.bsBuff = 0;
}
pub fn bsFinishWrite(s: &mut EState) {
    while s.bsLive > 0 {
        if let Some(zbits) = &mut s.zbits {
            if s.numZ < zbits.len() as i32 {
                zbits[s.numZ as usize] = (s.bsBuff >> 24) as UChar;
                s.numZ += 1;
                s.bsBuff <<= 8;
                s.bsLive -= 8;
            }
        }
    }
}
pub fn makeMaps_e(s: &mut EState) {
    s.nInUse = 0;
    for i in 0..256 {
        if s.inUse[i] != 0 {
            s.unseqToSeq[i] = s.nInUse as UChar;
            s.nInUse += 1;
        }
    }
}

pub fn helper_helper_sendMTFValues_5_1(
    v_ref: &mut Int32,
    gs_ref: &mut Int32,
    ge_ref: &mut Int32,
    nPart_ref: &mut Int32,
    remF_ref: &mut Int32,
    tFreq_ref: &mut Int32,
    aFreq_ref: &mut Int32,
    s: &mut EState,
    alphaSize: Int32,
    nGroups: Int32,
) {
    let mut v = *v_ref;
    let mut gs = *gs_ref;
    let mut ge = *ge_ref;
    let mut nPart = *nPart_ref;
    let mut remF = *remF_ref;
    let mut tFreq = *tFreq_ref;
    let mut aFreq = *aFreq_ref;

    tFreq = remF / nPart;
    ge = gs - 1;
    aFreq = 0;

    while (aFreq < tFreq) && (ge < (alphaSize - 1)) {
        ge += 1;
        aFreq += s.mtfFreq[ge as usize];
    }

    if ((ge > gs) && (nPart != nGroups)) && (nPart != 1) && (((nGroups - nPart) % 2) == 1) {
        aFreq -= s.mtfFreq[ge as usize];
        ge -= 1;
    }

    if s.verbosity >= 3 {
        writeln!(
            io::stderr(),
            "      initial group {}, [{} .. {}], has {} syms ({:.1}%)",
            nPart,
            gs,
            ge,
            aFreq,
            (100.0 * (aFreq as f32)) / (s.nMTF as f32)
        ).unwrap();
    }

    for v in 0..alphaSize {
        if (v >= gs) && (v <= ge) {
            s.len[(nPart - 1) as usize][v as usize] = 0;
        } else {
            s.len[(nPart - 1) as usize][v as usize] = 15;
        }
    }

    nPart -= 1;
    gs = ge + 1;
    remF -= aFreq;

    *v_ref = v;
    *gs_ref = gs;
    *ge_ref = ge;
    *nPart_ref = nPart;
    *remF_ref = remF;
    *tFreq_ref = tFreq;
    *aFreq_ref = aFreq;
}
pub fn helper_helper_helper_sendMTFValues_7_1_2(
    s: &EState,
    cost: &mut [UInt16; 6],
    mtfv: &[UInt16],
    gs: Int32,
) {
    let mut cost01 = 0;
    let mut cost23 = 0;
    let mut cost45 = 0;

    for i in 0..50 {
        let icv = mtfv[(gs + i) as usize];
        cost01 += s.len_pack[icv as usize][0];
        cost23 += s.len_pack[icv as usize][1];
        cost45 += s.len_pack[icv as usize][2];
    }

    cost[0] = (cost01 & 0xffff) as UInt16;
    cost[1] = (cost01 >> 16) as UInt16;
    cost[2] = (cost23 & 0xffff) as UInt16;
    cost[3] = (cost23 >> 16) as UInt16;
    cost[4] = (cost45 & 0xffff) as UInt16;
    cost[5] = (cost45 >> 16) as UInt16;
}
pub fn helper_helper_helper_sendMTFValues_7_1_1(
    gs_ref: &mut Int32,
    bt_ref: &mut Int32,
    s: &mut EState,
    mtfv: &[UInt16],
) {
    let gs = *gs_ref;
    let bt = *bt_ref;

    // Ensure mtfv has enough elements to avoid panic
    assert!(gs as usize + 49 < mtfv.len(), "mtfv index out of bounds");

    // Use a loop to increment rfreq values more idiomatically
    for i in 0..=49 {
        s.rfreq[bt as usize][mtfv[(gs as usize + i) as usize] as usize] += 1;
    }

    *gs_ref = gs;
    *bt_ref = bt;
}
pub fn helper_helper_sendMTFValues_7_1(
    t_ref: &mut Int32,
    i_ref: &mut Int32,
    gs_ref: &mut Int32,
    ge_ref: &mut Int32,
    totc_ref: &mut Int32,
    bt_ref: &mut Int32,
    bc_ref: &mut Int32,
    nSelectors_ref: &mut Int32,
    s: &mut EState,
    nGroups: Int32,
    cost: &mut [UInt16; 6],
    fave: &mut [Int32; 6],
    mtfv: &[UInt16],
) {
    let mut t = *t_ref;
    let mut i = *i_ref;
    let mut gs = *gs_ref;
    let mut ge = *ge_ref;
    let mut totc = *totc_ref;
    let mut bt = *bt_ref;
    let mut bc = *bc_ref;
    let mut nSelectors = *nSelectors_ref;

    if gs >= s.nMTF {
        return;
    }

    ge = (gs + 50) - 1;
    if ge >= s.nMTF {
        ge = s.nMTF - 1;
    }

    for t in 0..nGroups {
        cost[t as usize] = 0;
    }

    if nGroups == 6 && (ge - gs + 1) == 50 {
        helper_helper_helper_sendMTFValues_7_1_2(s, cost, mtfv, gs);
    } else {
        for i in gs..=ge {
            let icv = mtfv[i as usize];
            for t in 0..nGroups {
                cost[t as usize] += s.len[t as usize][icv as usize] as UInt16;
            }
        }
    }

    bc = 999999999;
    bt = -1;
    for t in 0..nGroups {
        if (cost[t as usize] as Int32) < bc {
            bc = cost[t as usize] as Int32;
            bt = t;
        }
    }

    totc += bc;
    fave[bt as usize] += 1;
    s.selector[nSelectors as usize] = bt as UChar;
    nSelectors += 1;

    if nGroups == 6 && (ge - gs + 1) == 50 {
        helper_helper_helper_sendMTFValues_7_1_1(&mut gs, &mut bt, s, mtfv);
    } else {
        for i in gs..=ge {
            s.rfreq[bt as usize][mtfv[i as usize] as usize] += 1;
        }
    }

    gs = ge + 1;

    *t_ref = t;
    *i_ref = i;
    *gs_ref = gs;
    *ge_ref = ge;
    *totc_ref = totc;
    *bt_ref = bt;
    *bc_ref = bc;
    *nSelectors_ref = nSelectors;
}

pub fn helper_sendMTFValues_7(
    v_ref: &mut Int32,
    t_ref: &mut Int32,
    i_ref: &mut Int32,
    gs_ref: &mut Int32,
    ge_ref: &mut Int32,
    totc_ref: &mut Int32,
    bt_ref: &mut Int32,
    bc_ref: &mut Int32,
    nSelectors_ref: &mut Int32,
    s: &mut EState,
    iter: Int32,
    alphaSize: Int32,
    nGroups: Int32,
    cost: &mut [UInt16; 6],
    fave: &mut [Int32; 6],
    mtfv: &[UInt16],
) {
    let mut v = *v_ref;
    let mut t = *t_ref;
    let mut i = *i_ref;
    let mut gs = *gs_ref;
    let mut ge = *ge_ref;
    let mut totc = *totc_ref;
    let mut bt = *bt_ref;
    let mut bc = *bc_ref;
    let mut nSelectors = *nSelectors_ref;

    // Initialize fave array
    for t_val in 0..nGroups {
        fave[t_val as usize] = 0;
    }

    // Initialize rfreq array
    for t_val in 0..nGroups {
        for v_val in 0..alphaSize {
            s.rfreq[t_val as usize][v_val as usize] = 0;
        }
    }

    if nGroups == 6 {
        for v_val in 0..alphaSize {
            s.len_pack[v_val as usize][0] = (s.len[1][v_val as usize] as UInt32) << 16 | s.len[0][v_val as usize] as UInt32;
            s.len_pack[v_val as usize][1] = (s.len[3][v_val as usize] as UInt32) << 16 | s.len[2][v_val as usize] as UInt32;
            s.len_pack[v_val as usize][2] = (s.len[5][v_val as usize] as UInt32) << 16 | s.len[4][v_val as usize] as UInt32;
        }
    }

    nSelectors = 0;
    totc = 0;
    gs = 0;

    loop {
        helper_helper_sendMTFValues_7_1(
            &mut t,
            &mut i,
            &mut gs,
            &mut ge,
            &mut totc,
            &mut bt,
            &mut bc,
            &mut nSelectors,
            s,
            nGroups,
            cost,
            fave,
            mtfv,
        );
    }

    if s.verbosity >= 3 {
        let _ = write!(
            io::stderr(),
            "      pass {}: size is {}, grp uses are ",
            iter + 1,
            totc / 8
        );
        for t_val in 0..nGroups {
            let _ = write!(io::stderr(), "{} ", fave[t_val as usize]);
        }
        let _ = writeln!(io::stderr());
    }

    for t_val in 0..nGroups {
        BZ2_hbMakeCodeLengths(
            &mut s.len[t_val as usize],
            &s.rfreq[t_val as usize],
            alphaSize,
            17,
        );
    }

    *v_ref = v;
    *t_ref = t;
    *i_ref = i;
    *gs_ref = gs;
    *ge_ref = ge;
    *totc_ref = totc;
    *bt_ref = bt;
    *bc_ref = bc;
    *nSelectors_ref = nSelectors;
}
pub fn bsW(s: &mut EState, n: Int32, v: UInt32) {
    {
        while s.bsLive >= 8 {
            if let Some(zbits) = &mut s.zbits {
                zbits.push((s.bsBuff >> 24) as UChar);
                s.numZ += 1;
                s.bsBuff <<= 8;
                s.bsLive -= 8;
            }
        }
    }
    s.bsBuff |= v << ((32 - s.bsLive) - n);
    s.bsLive += n;
}
pub fn helper_helper_sendMTFValues_6_1(
    s: &mut EState,
    mtfv: &[UInt16],
    gs: Int32,
    selCtr: Int32,
) {
    let selector_idx = s.selector[selCtr as usize] as usize;
    
    for i in 0..50 {
        let mtfv_i = mtfv[(gs + i) as usize] as usize;
        let len = s.len[selector_idx][mtfv_i] as Int32;
        let code = s.code[selector_idx][mtfv_i] as UInt32;
        bsW(s, len, code);
    }
}
pub fn helper_sendMTFValues_6(
    i_ref: &mut Int32,
    gs_ref: &mut Int32,
    ge_ref: &mut Int32,
    selCtr_ref: &mut Int32,
    s: &mut EState,
    nGroups: Int32,
    mtfv: &[UInt16],
) {
    let mut i = *i_ref;
    let mut gs = *gs_ref;
    let mut ge = *ge_ref;
    let mut selCtr = *selCtr_ref;

    if gs >= s.nMTF {
        return;
    }

    ge = (gs + 50) - 1;
    if ge >= s.nMTF {
        ge = s.nMTF - 1;
    }

    if !(i32::from(s.selector[selCtr as usize]) < nGroups) {
        BZ2_bz__AssertH__fail(3006);
    }

    if (nGroups == 6) && (50 == ((ge - gs) + 1)) {
        helper_helper_sendMTFValues_6_1(s, mtfv, gs, selCtr);
    } else {
        for i in gs..=ge {
            bsW(
                s,
                s.len[s.selector[selCtr as usize] as usize][mtfv[i as usize] as usize] as Int32,
                s.code[s.selector[selCtr as usize] as usize][mtfv[i as usize] as usize] as UInt32,
            );
        }
    }

    gs = ge + 1;
    selCtr += 1;

    *i_ref = i;
    *gs_ref = gs;
    *ge_ref = ge;
    *selCtr_ref = selCtr;
}
pub fn helper_sendMTFValues_5(
    v_ref: &mut Int32,
    gs_ref: &mut Int32,
    ge_ref: &mut Int32,
    s: &mut EState,
    alphaSize: Int32,
    nGroups: Int32,
) {
    let mut v = *v_ref;
    let mut gs = *gs_ref;
    let mut ge = *ge_ref;
    let mut nPart = nGroups;
    let mut remF = s.nMTF;
    let mut tFreq = 0;
    let mut aFreq = 0;
    
    gs = 0;
    
    while nPart > 0 {
        helper_helper_sendMTFValues_5_1(
            &mut v,
            &mut gs,
            &mut ge,
            &mut nPart,
            &mut remF,
            &mut tFreq,
            &mut aFreq,
            s,
            alphaSize,
            nGroups,
        );
    }
    
    *v_ref = v;
    *gs_ref = gs;
    *ge_ref = ge;
}
pub fn helper_sendMTFValues_4(
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut EState,
    nSelectors: Int32,
    nGroups: Int32,
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut pos: [UChar; 6] = [0; 6];

    // Initialize pos array
    for i in 0..nGroups {
        pos[i as usize] = i as UChar;
    }

    for i in 0..nSelectors {
        let ll_i = s.selector[i as usize];
        j = 0;
        let mut tmp = pos[j as usize];
        
        while ll_i != tmp {
            j += 1;
            let tmp2 = tmp;
            tmp = pos[j as usize];
            pos[j as usize] = tmp2;
        }

        pos[0] = tmp;
        s.selectorMtf[i as usize] = j as UChar;
    }

    *i_ref = i;
    *j_ref = j;
}

pub fn helper_sendMTFValues_3(
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    nBytes_ref: &mut Int32,
    s: &mut EState,
) {
    let mut inUse16 = [0 as Bool; 16];

    // First loop: initialize inUse16
    for i in 0..16 {
        inUse16[i] = 0;
        for j in 0..16 {
            if s.inUse[(i * 16) + j] != 0 {
                inUse16[i] = 1;
            }
        }
    }

    *nBytes_ref = s.numZ;

    // Second loop: write inUse16 flags
    for i in 0..16 {
        if inUse16[i] != 0 {
            bsW(s, 1, 1);
        } else {
            bsW(s, 1, 0);
        }
    }

    // Third loop: write detailed inUse flags
    for i in 0..16 {
        if inUse16[i] != 0 {
            for j in 0..16 {
                if s.inUse[(i * 16) + j] != 0 {
                    bsW(s, 1, 1);
                } else {
                    bsW(s, 1, 0);
                }
            }
        }
    }

    if s.verbosity >= 3 {
        let _ = writeln!(
            io::stderr(),
            "      bytes: mapping {}, ",
            s.numZ - *nBytes_ref
        );
    }

    // Update references (not really needed in Rust since we're modifying in place,
    // but kept for compatibility with C version)
    *i_ref = 16;
    *j_ref = 16;
}
pub fn helper_sendMTFValues_2(
    i_ref: &mut Int32,
    minLen_ref: &mut Int32,
    maxLen_ref: &mut Int32,
    s: &mut EState,
    t: Int32,
    alphaSize: Int32,
) {
    let mut i = *i_ref;
    let mut minLen = *minLen_ref;
    let mut maxLen = *maxLen_ref;
    
    minLen = 32;
    maxLen = 0;
    
    for i in 0..alphaSize {
        let len = s.len[t as usize][i as usize] as Int32;
        if len > maxLen {
            maxLen = len;
        }
        if len < minLen {
            minLen = len;
        }
    }
    
    if maxLen > 17 {
        BZ2_bz__AssertH__fail(3004);
    }
    
    if minLen < 1 {
        BZ2_bz__AssertH__fail(3005);
    }
    
    BZ2_hbAssignCodes(
        &mut s.code[t as usize][..],
        &s.len[t as usize][..],
        minLen,
        maxLen,
        alphaSize,
    );
    
    *i_ref = i;
    *minLen_ref = minLen;
    *maxLen_ref = maxLen;
}
pub fn helper_sendMTFValues_1(i_ref: &mut Int32, s: &mut EState, t: Int32, alphaSize: Int32) {
    let mut i = *i_ref;
    let mut curr = s.len[t as usize][0] as Int32;
    
    bsW(s, 5, curr as UInt32);
    
    for i in 0..alphaSize {
        while curr < s.len[t as usize][i as usize] as Int32 {
            bsW(s, 2, 2);
            curr += 1;
        }
        
        while curr > s.len[t as usize][i as usize] as Int32 {
            bsW(s, 2, 3);
            curr -= 1;
        }
        
        bsW(s, 1, 0);
    }
    
    *i_ref = i;
}
pub fn sendMTFValues(s: &mut EState) {
    let mut v: Int32 = 0;
    let mut t: Int32 = 0;
    let mut i: Int32 = 0;
    let mut j: Int32 = 0;
    let mut gs: Int32 = 0;
    let mut ge: Int32 = 0;
    let mut totc: Int32 = 0;
    let mut bt: Int32 = 0;
    let mut bc: Int32 = 0;
    let iter: Int32;
    let mut nSelectors: Int32 = 0;
    let alphaSize: Int32;
    let mut minLen: Int32 = 0;
    let mut maxLen: Int32 = 0;
    let mut selCtr: Int32 = 0;
    let nGroups: Int32;
    let mut nBytes: Int32 = 0;
    let mut cost: [UInt16; 6] = [0; 6];
    let mut fave: [Int32; 6] = [0; 6];
    
    // Clone the mtfv data to avoid borrowing issues
    let mtfv = s.mtfv.as_ref().unwrap().clone();

    if s.verbosity >= 3 {
        eprintln!(
            "      {} in block, {} after MTF & 1-2 coding, {}+2 syms in use",
            s.nblock, s.nMTF, s.nInUse
        );
    }

    alphaSize = s.nInUse + 2;
    for t_val in 0..6 {
        for v_val in 0..alphaSize {
            s.len[t_val as usize][v_val as usize] = 15;
        }
    }

    if !(s.nMTF > 0) {
        BZ2_bz__AssertH__fail(3001);
    }

    nGroups = match s.nMTF {
        n if n < 200 => 2,
        n if n < 600 => 3,
        n if n < 1200 => 4,
        n if n < 2400 => 5,
        _ => 6,
    };

    helper_sendMTFValues_5(&mut v, &mut gs, &mut ge, s, alphaSize, nGroups);

    for iter_val in 0..4 {
        helper_sendMTFValues_7(
            &mut v,
            &mut t,
            &mut i,
            &mut gs,
            &mut ge,
            &mut totc,
            &mut bt,
            &mut bc,
            &mut nSelectors,
            s,
            iter_val,
            alphaSize,
            nGroups,
            &mut cost,
            &mut fave,
            &mtfv,
        );
    }

    if !(nGroups < 8) {
        BZ2_bz__AssertH__fail(3002);
    }

    if !((nSelectors < 32768) && (nSelectors <= (2 + (900000 / 50)))) {
        BZ2_bz__AssertH__fail(3003);
    }

    helper_sendMTFValues_4(&mut i, &mut j, s, nSelectors, nGroups);

    for t_val in 0..nGroups {
        helper_sendMTFValues_2(&mut i, &mut minLen, &mut maxLen, s, t_val, alphaSize);
    }

    helper_sendMTFValues_3(&mut i, &mut j, &mut nBytes, s);
    nBytes = s.numZ;
    bsW(s, 3, nGroups as UInt32);
    bsW(s, 15, nSelectors as UInt32);

    for i_val in 0..nSelectors {
        for _ in 0..s.selectorMtf[i_val as usize] {
            bsW(s, 1, 1);
        }
        bsW(s, 1, 0);
    }

    if s.verbosity >= 3 {
        eprintln!("selectors {}, ", s.numZ - nBytes);
    }

    nBytes = s.numZ;
    for t_val in 0..nGroups {
        helper_sendMTFValues_1(&mut i, s, t_val, alphaSize);
    }

    if s.verbosity >= 3 {
        eprintln!("code lengths {}, ", s.numZ - nBytes);
    }

    nBytes = s.numZ;
    selCtr = 0;
    gs = 0;

    loop {
        helper_sendMTFValues_6(&mut i, &mut gs, &mut ge, &mut selCtr, s, nGroups, &mtfv);
        if selCtr == nSelectors {
            break;
        }
    }

    if !(selCtr == nSelectors) {
        BZ2_bz__AssertH__fail(3007);
    }

    if s.verbosity >= 3 {
        eprintln!("codes {}", s.numZ - nBytes);
    }
}
pub fn helper_helper_helper_generateMTFValues_2_1_2(
    j_ref: &mut Int32,
    wr_ref: &mut Int32,
    s: &mut EState,
    yy: &mut [UChar; 256],
    mtfv: &mut [UInt16],
    ll_i: UChar,
) {
    let mut j = *j_ref;
    let mut wr = *wr_ref;
    let mut rtmp = yy[1];
    yy[1] = yy[0];
    let mut ryy_j_idx = 1;
    let mut rll_i = ll_i;

    while rll_i != rtmp {
        let rtmp2 = rtmp;
        ryy_j_idx += 1;
        rtmp = yy[ryy_j_idx];
        yy[ryy_j_idx] = rtmp2;
    }

    yy[0] = rtmp;
    j = (ryy_j_idx) as Int32;
    mtfv[wr as usize] = (j + 1) as UInt16;
    wr += 1;
    s.mtfFreq[(j + 1) as usize] += 1;
    *j_ref = j;
    *wr_ref = wr;
}

pub fn helper_helper_helper_generateMTFValues_2_1_1(
    zPend_ref: &mut Int32,
    wr_ref: &mut Int32,
    s: &mut EState,
    mtfv: &mut [UInt16],
) {
    let mut zPend = *zPend_ref;
    let mut wr = *wr_ref;
    
    zPend -= 1;
    
    loop {
        if zPend & 1 != 0 {
            mtfv[wr as usize] = 1;
            wr += 1;
            s.mtfFreq[1] += 1;
        } else {
            mtfv[wr as usize] = 0;
            wr += 1;
            s.mtfFreq[0] += 1;
        }
        
        if zPend < 2 {
            break;
        }
        
        zPend = (zPend - 2) / 2;
    }
    
    zPend = 0;
    *zPend_ref = zPend;
    *wr_ref = wr;
}
pub fn helper_helper_generateMTFValues_2_1(
    j_ref: &mut Int32,
    zPend_ref: &mut Int32,
    wr_ref: &mut Int32,
    s: &mut EState,
    yy: &mut [UChar; 256],
    mtfv: &mut [UInt16],
    ll_i: UChar,
) {
    let mut j = *j_ref;
    let mut zPend = *zPend_ref;
    let mut wr = *wr_ref;

    if zPend > 0 {
        helper_helper_helper_generateMTFValues_2_1_1(&mut zPend, &mut wr, s, mtfv);
    }

    helper_helper_helper_generateMTFValues_2_1_2(&mut j, &mut wr, s, yy, mtfv, ll_i);

    *j_ref = j;
    *zPend_ref = zPend;
    *wr_ref = wr;
}
pub fn helper_generateMTFValues_2(
    j_ref: &mut Int32,
    zPend_ref: &mut Int32,
    wr_ref: &mut Int32,
    s: &mut EState,
    yy: &[UChar; 256],
    i: Int32,
    ptr: &[UInt32],
    block: &[UChar],
    mtfv: &mut [UInt16],
) {
    let mut j = *j_ref;
    let mut zPend = *zPend_ref;
    let mut wr = *wr_ref;
    
    j = ptr[i as usize] as Int32 - 1;
    if j < 0 {
        j += s.nblock;
    }
    
    let ll_i = s.unseqToSeq[block[j as usize] as usize];
    
    if yy[0] == ll_i {
        zPend += 1;
    } else {
        helper_helper_generateMTFValues_2_1(
            &mut j,
            &mut zPend,
            &mut wr,
            s,
            &mut yy.clone(),
            mtfv,
            ll_i,
        );
    }
    
    *j_ref = j;
    *zPend_ref = zPend;
    *wr_ref = wr;
}
pub fn helper_generateMTFValues_1(
    zPend_ref: &mut Int32,
    wr_ref: &mut Int32,
    s: &mut EState,
    mtfv: &mut [UInt16],
) {
    let mut zPend = *zPend_ref;
    let mut wr = *wr_ref;
    
    zPend -= 1;
    
    loop {
        if zPend & 1 != 0 {
            mtfv[wr as usize] = 1;
            wr += 1;
            s.mtfFreq[1] += 1;
        } else {
            mtfv[wr as usize] = 0;
            wr += 1;
            s.mtfFreq[0] += 1;
        }
        
        if zPend < 2 {
            break;
        }
        
        zPend = (zPend - 2) / 2;
    }
    
    zPend = 0;
    *zPend_ref = zPend;
    *wr_ref = wr;
}
pub fn generateMTFValues(s: &mut EState) {
    let mut yy = [0; 256];
    let mut i: Int32;
    let mut j = 0;
    let mut zPend = 0;
    let mut wr = 0;
    let EOB;

    makeMaps_e(s);
    EOB = s.nInUse + 1;

    // Initialize mtfFreq
    for i in 0..=EOB {
        s.mtfFreq[i as usize] = 0;
    }

    wr = 0;
    zPend = 0;

    // Initialize yy
    for i in 0..s.nInUse {
        yy[i as usize] = i as UChar;
    }

    // Prepare raw pointers to slices
    let ptr = s.ptr.as_ref().expect("ptr is None").as_slice() as *const [UInt32];
    let block = s.block.as_ref().expect("block is None").as_slice() as *const [UChar];
    let mtfv_slice_ptr = s.mtfv.as_mut().expect("mtfv is None").as_mut_slice() as *mut [UInt16];

    // Process each block
    for i in 0..s.nblock {
        unsafe {
            helper_generateMTFValues_2(
                &mut j,
                &mut zPend,
                &mut wr,
                s,
                &yy,
                i,
                &*ptr,
                &*block,
                &mut *mtfv_slice_ptr,
            );
        }
    }

    // Handle remaining zPend
    if zPend > 0 {
        unsafe {
            helper_generateMTFValues_1(
                &mut zPend,
                &mut wr,
                s,
                &mut *mtfv_slice_ptr,
            );
        }
    }

    // Set EOB and update counts
    let mtfv = s.mtfv.as_mut().expect("mtfv is None");
    mtfv[wr as usize] = EOB as UInt16;
    wr += 1;
    s.mtfFreq[EOB as usize] += 1;
    s.nMTF = wr;
}
pub fn bsPutUInt32(s: &mut EState, u: UInt32) {
    bsW(s, 8, (u >> 24) & 0xff);
    bsW(s, 8, (u >> 16) & 0xff);
    bsW(s, 8, (u >> 8) & 0xff);
    bsW(s, 8, u & 0xff);
}
pub fn bsPutUChar(s: &mut EState, c: UChar) {
    bsW(s, 8, c as UInt32);
}
pub fn helper_BZ2_compressBlock_1(s: &mut EState) {
    bsPutUChar(s, 0x31);
    bsPutUChar(s, 0x41);
    bsPutUChar(s, 0x59);
    bsPutUChar(s, 0x26);
    bsPutUChar(s, 0x53);
    bsPutUChar(s, 0x59);
    bsPutUInt32(s, s.blockCRC);
    bsW(s, 1, 0);
    bsW(s, 24, s.origPtr as UInt32);
    generateMTFValues(s);
    sendMTFValues(s);
}
pub fn BZ2_compressBlock(s: &mut EState, is_last_block: Bool) {
    if s.nblock > 0 {
        {
            s.blockCRC = !s.blockCRC;
        }
        
        s.combinedCRC = (s.combinedCRC << 1) | (s.combinedCRC >> 31);
        s.combinedCRC ^= s.blockCRC;
        
        if s.blockNo > 1 {
            s.numZ = 0;
        }
        
        if s.verbosity >= 2 {
            writeln!(
                io::stderr(),
                "    block {}: crc = 0x{:08x}, combined CRC = 0x{:08x}, size = {}",
                s.blockNo, s.blockCRC, s.combinedCRC, s.nblock
            ).unwrap();
        }
        
        BZ2_blockSort(s);
    }
    
    if let Some(arr2) = &mut s.arr2 {
        s.zbits = Some(arr2[s.nblock as usize..]
            .iter()
            .map(|&x| x as UChar)
            .collect());
    }
    
    if s.blockNo == 1 {
        BZ2_bsInitWrite(s);
        bsPutUChar(s, 0x42);
        bsPutUChar(s, 0x5a);
        bsPutUChar(s, 0x68);
        bsPutUChar(s, 0x30 + s.blockSize100k as UChar);
    }
    
    if s.nblock > 0 {
        helper_BZ2_compressBlock_1(s);
    }
    
    if is_last_block != 0 {
        bsPutUChar(s, 0x17);
        bsPutUChar(s, 0x72);
        bsPutUChar(s, 0x45);
        bsPutUChar(s, 0x38);
        bsPutUChar(s, 0x50);
        bsPutUChar(s, 0x90);
        bsPutUInt32(s, s.combinedCRC);
        
        if s.verbosity >= 2 {
            writeln!(
                io::stderr(),
                "    final combined CRC = 0x{:08x}\n   ",
                s.combinedCRC
            ).unwrap();
        }
        
        bsFinishWrite(s);
    }
}
