use crate::*;
use std::process;
use std::io::Write;
pub fn BZ2_bsInitWrite(s: &mut EState) {
    s.bsLive = 0;
    s.bsBuff = 0;
}
pub fn bsFinishWrite(s: &mut EState) {
    while s.bsLive > 0 {
        if let Some(zbits) = s.zbits.as_mut() {
            if s.numZ < zbits.len() as i32 {
                zbits[s.numZ as usize] = (s.bsBuff >> 24) as UChar;
                s.numZ += 1;
                s.bsBuff <<= 8;
                s.bsLive -= 8;
            } else {
                // Handle buffer overflow case if needed
                break;
            }
        } else {
            // Handle case where zbits is None if needed
            break;
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
pub fn bsW(s: &mut EState, n: Int32, v: UInt32) {
    {
        while s.bsLive >= 8 {
            if let Some(ref mut zbits) = s.zbits {
                if s.numZ < zbits.len() as Int32 {
                    zbits[s.numZ as usize] = (s.bsBuff >> 24) as UChar;
                    s.numZ += 1;
                    s.bsBuff <<= 8;
                    s.bsLive -= 8;
                }
            }
        }
    }
    s.bsBuff |= v << ((32 - s.bsLive) - n);
    s.bsLive += n;
}
pub fn sendMTFValues(s: &mut EState) {
    let mut v: Int32;
    let mut t: Int32;
    let mut i: Int32;
    let mut j: Int32;
    let mut gs: Int32;
    let mut ge: Int32;
    let mut totc: Int32;
    let mut bt: Int32;
    let mut bc: Int32;
    let mut iter: Int32;
    let mut nSelectors: Int32 = 0;
    let mut alphaSize: Int32;
    let mut minLen: Int32;
    let mut maxLen: Int32;
    let mut selCtr: Int32;
    let mut nGroups: Int32;
    let mut nBytes: Int32;
    let mut cost: [UInt16; 6] = [0; 6];
    let mut fave: [Int32; 6] = [0; 6];
    let mtfv = s.mtfv.as_ref().unwrap().clone();

    if s.verbosity >= 3 {
        eprintln!(
            "      {} in block, {} after MTF & 1-2 coding, {}+2 syms in use",
            s.nblock, s.nMTF, s.nInUse
        );
    }

    alphaSize = s.nInUse + 2;
    for t in 0..6 {
        for v in 0..alphaSize {
            s.len[t as usize][v as usize] = 15;
        }
    }

    if !(s.nMTF > 0) {
        BZ2_bz__AssertH__fail(3001);
    }

    nGroups = if s.nMTF < 200 {
        2
    } else if s.nMTF < 600 {
        3
    } else if s.nMTF < 1200 {
        4
    } else if s.nMTF < 2400 {
        5
    } else {
        6
    };

    {
        let mut nPart: Int32;
        let mut remF: Int32;
        let mut tFreq: Int32;
        let mut aFreq: Int32;
        nPart = nGroups;
        remF = s.nMTF;
        gs = 0;
        while nPart > 0 {
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
                eprintln!(
                    "      initial group {}, [{} .. {}], has {} syms ({:.1}%)",
                    nPart,
                    gs,
                    ge,
                    aFreq,
                    (100.0 * (aFreq as f32)) / (s.nMTF as f32)
                );
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
        }
    }

    for iter in 0..4 {
        for t in 0..nGroups {
            fave[t as usize] = 0;
        }

        for t in 0..nGroups {
            for v in 0..alphaSize {
                s.rfreq[t as usize][v as usize] = 0;
            }
        }

        if nGroups == 6 {
            for v in 0..alphaSize {
                s.len_pack[v as usize][0] = (s.len[1][v as usize] as UInt32) << 16 | s.len[0][v as usize] as UInt32;
                s.len_pack[v as usize][1] = (s.len[3][v as usize] as UInt32) << 16 | s.len[2][v as usize] as UInt32;
                s.len_pack[v as usize][2] = (s.len[5][v as usize] as UInt32) << 16 | s.len[4][v as usize] as UInt32;
            }
        }

        nSelectors = 0;
        totc = 0;
        gs = 0;
        loop {
            if gs >= s.nMTF {
                break;
            }
            ge = (gs + 50) - 1;
            if ge >= s.nMTF {
                ge = s.nMTF - 1;
            }

            for t in 0..nGroups {
                cost[t as usize] = 0;
            }

            if (nGroups == 6) && (50 == ((ge - gs) + 1)) {
                let mut cost01: UInt32 = 0;
                let mut cost23: UInt32 = 0;
                let mut cost45: UInt32 = 0;
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
                if cost[t as usize] < bc as UInt16 {
                    bc = cost[t as usize] as Int32;
                    bt = t;
                }
            }

            totc += bc;
            fave[bt as usize] += 1;
            s.selector[nSelectors as usize] = bt as UChar;
            nSelectors += 1;

            if (nGroups == 6) && (50 == ((ge - gs) + 1)) {
                for i in 0..50 {
                    let icv = mtfv[(gs + i) as usize];
                    s.rfreq[bt as usize][icv as usize] += 1;
                }
            } else {
                for i in gs..=ge {
                    let icv = mtfv[i as usize];
                    s.rfreq[bt as usize][icv as usize] += 1;
                }
            }

            gs = ge + 1;
        }

        if s.verbosity >= 3 {
            eprint!("      pass {}: size is {}, grp uses are ", iter + 1, totc / 8);
            for t in 0..nGroups {
                eprint!("{} ", fave[t as usize]);
            }
            eprintln!();
        }

        for t in 0..nGroups {
            BZ2_hbMakeCodeLengths(
                &mut s.len[t as usize],
                &s.rfreq[t as usize],
                alphaSize,
                17,
            );
        }
    }

    if !(nGroups < 8) {
        BZ2_bz__AssertH__fail(3002);
    }

    if !((nSelectors < 32768) && (nSelectors <= (2 + (900000 / 50)))) {
        BZ2_bz__AssertH__fail(3003);
    }

    {
        let mut pos: [UChar; 6] = [0; 6];
        let mut ll_i: UChar;
        let mut tmp2: UChar;
        let mut tmp: UChar;
        for i in 0..nGroups {
            pos[i as usize] = i as UChar;
        }

        for i in 0..nSelectors {
            ll_i = s.selector[i as usize];
            j = 0;
            tmp = pos[j as usize];
            while ll_i != tmp {
                j += 1;
                tmp2 = tmp;
                tmp = pos[j as usize];
                pos[j as usize] = tmp2;
            }
            pos[0] = tmp;
            s.selectorMtf[i as usize] = j as UChar;
        }
    }

    for t in 0..nGroups {
        minLen = 32;
        maxLen = 0;
        for i in 0..alphaSize {
            if (s.len[t as usize][i as usize] as Int32) > maxLen {
                maxLen = s.len[t as usize][i as usize] as Int32;
            }
            if (s.len[t as usize][i as usize] as Int32) < minLen {
                minLen = s.len[t as usize][i as usize] as Int32;
            }
        }

        if !(!(maxLen > 17)) {
            BZ2_bz__AssertH__fail(3004);
        }

        if !(!(minLen < 1)) {
            BZ2_bz__AssertH__fail(3005);
        }

        BZ2_hbAssignCodes(
            &mut s.code[t as usize],
            &s.len[t as usize],
            minLen,
            maxLen,
            alphaSize,
        );
    }

    {
        let mut inUse16: [Bool; 16] = [0; 16];
        for i in 0..16 {
            inUse16[i as usize] = 0;
            for j in 0..16 {
                if s.inUse[(i * 16 + j) as usize] != 0 {
                    inUse16[i as usize] = 1;
                }
            }
        }

        nBytes = s.numZ;
        for i in 0..16 {
            bsW(s, 1, if inUse16[i as usize] != 0 { 1 } else { 0 });
        }

        for i in 0..16 {
            if inUse16[i as usize] != 0 {
                for j in 0..16 {
                    bsW(s, 1, if s.inUse[(i * 16 + j) as usize] != 0 { 1 } else { 0 });
                }
            }
        }

        if s.verbosity >= 3 {
            eprint!("      bytes: mapping {}, ", s.numZ - nBytes);
        }
    }

    nBytes = s.numZ;
    bsW(s, 3, nGroups as UInt32);
    bsW(s, 15, nSelectors as UInt32);
    for i in 0..nSelectors {
        for _ in 0..s.selectorMtf[i as usize] {
            bsW(s, 1, 1);
        }
        bsW(s, 1, 0);
    }

    if s.verbosity >= 3 {
        eprint!("selectors {}, ", s.numZ - nBytes);
    }

    nBytes = s.numZ;
    for t in 0..nGroups {
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
    }

    if s.verbosity >= 3 {
        eprint!("code lengths {}, ", s.numZ - nBytes);
    }

    nBytes = s.numZ;
    selCtr = 0;
    gs = 0;
    loop {
        if gs >= s.nMTF {
            break;
        }
        ge = (gs + 50) - 1;
        if ge >= s.nMTF {
            ge = s.nMTF - 1;
        }

        if !(s.selector[selCtr as usize] < nGroups as UChar) {
            BZ2_bz__AssertH__fail(3006);
        }

        if (nGroups == 6) && (50 == ((ge - gs) + 1)) {
            for i in 0..50 {
                let mtfv_i = mtfv[(gs + i) as usize];
                bsW(
                    s,
                    s.len[s.selector[selCtr as usize] as usize][mtfv_i as usize] as Int32,
                    s.code[s.selector[selCtr as usize] as usize][mtfv_i as usize] as UInt32,
                );
            }
        } else {
            for i in gs..=ge {
                let mtfv_i = mtfv[i as usize];
                bsW(
                    s,
                    s.len[s.selector[selCtr as usize] as usize][mtfv_i as usize] as Int32,
                    s.code[s.selector[selCtr as usize] as usize][mtfv_i as usize] as UInt32,
                );
            }
        }

        gs = ge + 1;
        selCtr += 1;
    }

    if !(selCtr == nSelectors) {
        BZ2_bz__AssertH__fail(3007);
    }

    if s.verbosity >= 3 {
        eprintln!("codes {}", s.numZ - nBytes);
    }
}
pub fn generateMTFValues(s: &mut EState) {
    let mut yy = [0u8; 256];
    let mut zPend = 0;
    let mut wr = 0;
    
    makeMaps_e(s);
    let EOB = (s.nInUse + 1) as usize;
    
    // Initialize mtfFreq
    for i in 0..=EOB {
        s.mtfFreq[i] = 0;
    }
    
    // Initialize yy
    for i in 0..s.nInUse {
        yy[i as usize] = i as UChar;
    }
    
    let ptr = s.ptr.as_deref().expect("ptr is None");
    let block = s.block.as_deref().expect("block is None");
    let mtfv = &mut *s.mtfv.as_mut().expect("mtfv is None");
    
    for i in 0..s.nblock {
        let mut j = ptr[i as usize] as i32 - 1;
        if j < 0 {
            j += s.nblock;
        }
        
        let ll_i = s.unseqToSeq[block[j as usize] as usize];
        
        if yy[0] == ll_i as UChar {
            zPend += 1;
        } else {
            if zPend > 0 {
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
            }
            
            let mut rtmp = yy[1];
            yy[1] = yy[0];
            let mut ryy_j_idx = 1;
            let rll_i = ll_i as UChar;
            
            while rll_i != rtmp {
                ryy_j_idx += 1;
                let rtmp2 = rtmp;
                rtmp = yy[ryy_j_idx];
                yy[ryy_j_idx] = rtmp2;
            }
            
            yy[0] = rtmp;
            let j = ryy_j_idx;
            mtfv[wr as usize] = (j + 1) as UInt16;
            wr += 1;
            s.mtfFreq[j + 1] += 1;
        }
    }
    
    if zPend > 0 {
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
    }
    
    mtfv[wr as usize] = EOB as UInt16;
    wr += 1;
    s.mtfFreq[EOB] += 1;
    s.nMTF = wr as Int32;
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
                std::io::stderr(),
                "    block {}: crc = 0x{:08x}, combined CRC = 0x{:08x}, size = {}",
                s.blockNo,
                s.blockCRC,
                s.combinedCRC,
                s.nblock
            ).unwrap();
        }
        
        BZ2_blockSort(s);
    }
    
    if let Some(arr2) = &mut s.arr2 {
        let slice = &arr2[s.nblock as usize..];
        let bytes = unsafe {
            std::slice::from_raw_parts(
                slice.as_ptr() as *const u8,
                slice.len() * std::mem::size_of::<UInt32>()
            )
        };
        s.zbits = Some(bytes.to_vec().into_boxed_slice());
    }
    
    if s.blockNo == 1 {
        BZ2_bsInitWrite(s);
        bsPutUChar(s, 0x42);
        bsPutUChar(s, 0x5a);
        bsPutUChar(s, 0x68);
        bsPutUChar(s, 0x30 + s.blockSize100k as UChar);
    }
    
    if s.nblock > 0 {
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
                std::io::stderr(),
                "    final combined CRC = 0x{:08x}\n   ",
                s.combinedCRC
            ).unwrap();
        }
        
        bsFinishWrite(s);
    }
}
