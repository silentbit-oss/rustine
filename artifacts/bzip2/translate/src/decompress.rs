use crate::*;
use rand::Rng;
use std::convert::TryInto;
use lazy_static::lazy_static;
use std::io;
use std::io::Write;

pub fn helper_BZ2_decompress_11(s: &mut DState) {
    s.save_i = 0;
    s.save_j = 0;
    s.save_t = 0;
    s.save_alpha_size = 0;
    s.save_n_groups = 0;
    s.save_n_selectors = 0;
    s.save_eob = 0;
    s.save_group_no = 0;
    s.save_group_pos = 0;
    s.save_next_sym = 0;
    s.save_nblock_max = 0;
    s.save_nblock = 0;
    s.save_es = 0;
    s.save_n = 0;
    s.save_curr = 0;
    s.save_zt = 0;
    s.save_zn = 0;
    s.save_zvec = 0;
    s.save_zj = 0;
    s.save_g_sel = 0;
    s.save_g_minlen = 0;
    s.save_g_limit = None;
    s.save_g_base = None;
    s.save_g_perm = None;
}
pub fn makeMaps_d(s: &mut DState) {
    s.n_in_use = 0;
    for i in 0..256 {
        if s.in_use[i] != 0 {
            s.seq_to_unseq[s.n_in_use as usize] = i as UChar;
            s.n_in_use += 1;
        }
    }
}

pub fn helper_helper_helper_BZ2_decompress_29_4_1(s: &mut DState) -> Bool {
    s.r_n_to_go = 0;
    s.r_t_pos = 0;
    
    if s.t_pos >= 100000 * s.block_size100k as UInt32 {
        return 1;
    }
    
    // Safe unwrap since we know tt exists in this context
    let tt = s.tt.as_ref().unwrap();
    s.t_pos = tt[s.t_pos as usize];
    s.k0 = (s.t_pos & 0xff) as Int32;
    s.t_pos >>= 8;
    
    s.nblock_used += 1;
    
    if s.r_n_to_go == 0 {
        let mut r_nums = BZ2_rNums.lock().unwrap();
        s.r_n_to_go = r_nums[s.r_t_pos as usize];
        s.r_t_pos += 1;
        if s.r_t_pos == 512 {
            s.r_t_pos = 0;
        }
    }
    
    s.r_n_to_go -= 1;
    
    s.k0 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
    
    0 // Return value not specified in original C code, assuming 0
}
pub fn helper_helper_helper_BZ2_decompress_29_7_1(
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    nSelectors: Int32,
) {
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    groupNo += 1;
    if groupNo >= nSelectors {
        retVal = -4;
    } else {
        groupPos = 50;
        gSel = s.selector[groupNo as usize] as Int32;
        gMinlen = s.min_lens[gSel as usize];
        gLimit_idx = 0;
        gBase_idx = 0;
        gPerm_idx = 0;
    }

    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}
pub fn helper_BZ2_decompress_9(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 48;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    *next_in = next_in[1..].to_vec().into_boxed_slice();
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    s.stored_combined_crc = (s.stored_combined_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_8(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 47;
    
    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }
        
        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }
            
            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    *next_in = next_in[1..].to_vec().into_boxed_slice();
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }
    
    s.stored_combined_crc = (s.stored_combined_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_7(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 26;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    let remaining = next_in[1..].to_vec().into_boxed_slice();
                    strm.next_in = Some(remaining);
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    s.orig_ptr = (s.orig_ptr << 8) | (uc as Int32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_6(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 25;
    
    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }
        
        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }
            
            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    *uc_ref = uc;
                    *retVal_ref = retVal;
                    return;
                }
                
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }
    }
    
    s.orig_ptr = (s.orig_ptr << 8) | (uc as Int32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_5(retVal_ref: &mut Int32, s: &mut DState) {
    let mut retVal = *retVal_ref;
    s.state = 24;

    loop {
        if s.bs_live >= 1 {
            let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
            s.bs_live -= 1;
            s.block_randomised = v as u8;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    *retVal_ref = retVal;
                    return;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = 0;
            *retVal_ref = retVal;
            return;
        }
    }

    s.orig_ptr = 0;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_4(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 23;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    *next_in = next_in[1..].to_vec().into_boxed_slice();
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    s.stored_block_crc = (s.stored_block_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_3(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 22;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    let new_next_in = next_in[1..].to_vec().into_boxed_slice();
                    strm.next_in = Some(new_next_in);
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;

                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    s.stored_block_crc = (s.stored_block_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_helper_helper_helper_BZ2_decompress_29_9_2_2(
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
    nSelectors: Int32,
) {
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    if groupPos == 0 {
        groupNo += 1;
        if groupNo >= nSelectors {
            retVal = -4;
            *retVal_ref = retVal;
            *groupNo_ref = groupNo;
            *groupPos_ref = groupPos;
            *nextSym_ref = nextSym;
            *zn_ref = zn;
            *zvec_ref = zvec;
            *zj_ref = zj;
            *gSel_ref = gSel;
            *gMinlen_ref = gMinlen;
            *gLimit_idx_ref = gLimit_idx;
            *gBase_idx_ref = gBase_idx;
            *gPerm_idx_ref = gPerm_idx;
            return;
        }
        groupPos = 50;
        gSel = s.selector[groupNo as usize].into();
        gMinlen = s.min_lens[gSel as usize];
        gLimit_idx = 0;
        gPerm_idx = 0;
        gBase_idx = 0;
    }
    groupPos -= 1;
    zn = gMinlen;
    s.state = 40;

    loop {
        if s.bs_live >= zn {
            let v = (s.bs_buff >> (s.bs_live - zn)) & ((1 << zn) - 1);
            s.bs_live -= zn;
            zvec = v as Int32;
            break;
        }
        if s.strm.as_ref().unwrap().avail_in == 0 {
            retVal = 0;
            *retVal_ref = retVal;
            *groupNo_ref = groupNo;
            *groupPos_ref = groupPos;
            *nextSym_ref = nextSym;
            *zn_ref = zn;
            *zvec_ref = zvec;
            *zj_ref = zj;
            *gSel_ref = gSel;
            *gMinlen_ref = gMinlen;
            *gLimit_idx_ref = gLimit_idx;
            *gBase_idx_ref = gBase_idx;
            *gPerm_idx_ref = gPerm_idx;
            return;
        }
        let next_byte = s.strm.as_mut().unwrap().next_in.as_mut().unwrap()[0];
        s.bs_buff = (s.bs_buff << 8) | (next_byte as UInt32);
        s.bs_live += 8;
        s.strm.as_mut().unwrap().next_in.as_mut().unwrap().rotate_left(1);
        s.strm.as_mut().unwrap().avail_in -= 1;
        s.strm.as_mut().unwrap().total_in_lo32 += 1;
        if s.strm.as_mut().unwrap().total_in_lo32 == 0 {
            s.strm.as_mut().unwrap().total_in_hi32 += 1;
        }
    }

    loop {
        if zn > 20 {
            retVal = -4;
            *retVal_ref = retVal;
            *groupNo_ref = groupNo;
            *groupPos_ref = groupPos;
            *nextSym_ref = nextSym;
            *zn_ref = zn;
            *zvec_ref = zvec;
            *zj_ref = zj;
            *gSel_ref = gSel;
            *gMinlen_ref = gMinlen;
            *gLimit_idx_ref = gLimit_idx;
            *gBase_idx_ref = gBase_idx;
            *gPerm_idx_ref = gPerm_idx;
            return;
        }
        if zvec <= gLimit[zn as usize + gLimit_idx] {
            break;
        }
        zn += 1;
        s.state = 41;

        loop {
            if s.bs_live >= 1 {
                let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
                s.bs_live -= 1;
                zj = v as Int32;
                break;
            }
            if s.strm.as_ref().unwrap().avail_in == 0 {
                retVal = 0;
                *retVal_ref = retVal;
                *groupNo_ref = groupNo;
                *groupPos_ref = groupPos;
                *nextSym_ref = nextSym;
                *zn_ref = zn;
                *zvec_ref = zvec;
                *zj_ref = zj;
                *gSel_ref = gSel;
                *gMinlen_ref = gMinlen;
                *gLimit_idx_ref = gLimit_idx;
                *gBase_idx_ref = gBase_idx;
                *gPerm_idx_ref = gPerm_idx;
                return;
            }
            let next_byte = s.strm.as_mut().unwrap().next_in.as_mut().unwrap()[0];
            s.bs_buff = (s.bs_buff << 8) | (next_byte as UInt32);
            s.bs_live += 8;
            s.strm.as_mut().unwrap().next_in.as_mut().unwrap().rotate_left(1);
            s.strm.as_mut().unwrap().avail_in -= 1;
            s.strm.as_mut().unwrap().total_in_lo32 += 1;
            if s.strm.as_mut().unwrap().total_in_lo32 == 0 {
                s.strm.as_mut().unwrap().total_in_hi32 += 1;
            }
        }
        zvec = (zvec << 1) | zj;
    }

    if (zvec - gBase[zn as usize + gBase_idx]) < 0 || (zvec - gBase[zn as usize + gBase_idx]) >= 258 {
        retVal = -4;
        *retVal_ref = retVal;
        *groupNo_ref = groupNo;
        *groupPos_ref = groupPos;
        *nextSym_ref = nextSym;
        *zn_ref = zn;
        *zvec_ref = zvec;
        *zj_ref = zj;
        *gSel_ref = gSel;
        *gMinlen_ref = gMinlen;
        *gLimit_idx_ref = gLimit_idx;
        *gBase_idx_ref = gBase_idx;
        *gPerm_idx_ref = gPerm_idx;
        return;
    }
    nextSym = gPerm[(zvec - gBase[zn as usize + gBase_idx]) as usize + gPerm_idx];

    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *nextSym_ref = nextSym;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}
pub fn helper_helper_helper_helper_BZ2_decompress_29_9_2_1(uc_ref: &mut UChar, s: &mut DState, nextSym: Int32) {
    let mut uc = *uc_ref;
    let nn = (nextSym - 1) as UInt32;
    
    if nn < 16 {
        let mut pp = s.mtfbase[0];
        uc = s.mtfa[(pp + nn as Int32) as usize];
        
        let mut nn = nn;
        while nn > 3 {
            let z = (pp + nn as Int32) as usize;
            s.mtfa[z] = s.mtfa[z - 1];
            s.mtfa[z - 1] = s.mtfa[z - 2];
            s.mtfa[z - 2] = s.mtfa[z - 3];
            s.mtfa[z - 3] = s.mtfa[z - 4];
            nn -= 4;
        }
        
        while nn > 0 {
            s.mtfa[(pp + nn as Int32) as usize] = s.mtfa[(pp + nn as Int32 - 1) as usize];
            nn -= 1;
        }
        
        s.mtfa[pp as usize] = uc;
    } else {
        let mut lno = (nn / 16) as Int32;
        let mut off = (nn % 16) as Int32;
        let mut pp = s.mtfbase[lno as usize] + off;
        uc = s.mtfa[pp as usize];
        
        while pp > s.mtfbase[lno as usize] {
            s.mtfa[pp as usize] = s.mtfa[(pp - 1) as usize];
            pp -= 1;
        }
        
        s.mtfbase[lno as usize] += 1;
        
        while lno > 0 {
            s.mtfbase[lno as usize] -= 1;
            let idx = (s.mtfbase[(lno - 1) as usize] + 16) - 1;
            s.mtfa[s.mtfbase[lno as usize] as usize] = s.mtfa[idx as usize];
            lno -= 1;
        }
        
        s.mtfbase[0] -= 1;
        s.mtfa[s.mtfbase[0] as usize] = uc;
        
        if s.mtfbase[0] == 0 {
            let mut kk = 4096 - 1;
            for ii in (0..=(256 / 16) - 1).rev() {
                for jj in (0..=16 - 1).rev() {
                    s.mtfa[kk as usize] = s.mtfa[(s.mtfbase[ii as usize] + jj) as usize];
                    kk -= 1;
                }
                s.mtfbase[ii as usize] = (kk + 1) as Int32;
            }
        }
    }
    
    *uc_ref = uc;
}
pub fn helper_helper_helper_BZ2_decompress_29_9_2(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    nblock_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
    nSelectors: Int32,
    nblockMAX: Int32,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut nblock = *nblock_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    if nblock >= nblockMAX {
        retVal = -4;
        // goto save_state_and_return is replaced by early return after state saving
    } else {
        helper_helper_helper_helper_BZ2_decompress_29_9_2_1(&mut uc, s, nextSym);
        
        s.unzftab[s.seq_to_unseq[uc as usize] as usize] += 1;
        
        if s.small_decompress != 0 {
            if let Some(ref mut ll16) = s.ll16 {
                ll16[nblock as usize] = s.seq_to_unseq[uc as usize] as UInt16;
            }
        } else {
            if let Some(ref mut tt) = s.tt {
                tt[nblock as usize] = s.seq_to_unseq[uc as usize] as UInt32;
            }
        }
        
        nblock += 1;
        
        helper_helper_helper_helper_BZ2_decompress_29_9_2_2(
            &mut retVal,
            &mut groupNo,
            &mut groupPos,
            &mut nextSym,
            &mut zn,
            &mut zvec,
            &mut zj,
            &mut gSel,
            &mut gMinlen,
            &mut gLimit_idx,
            &mut gBase_idx,
            &mut gPerm_idx,
            s,
            gLimit,
            gBase,
            gPerm,
            nSelectors,
        );
    }

    // Save state back to references
    *uc_ref = uc;
    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *nextSym_ref = nextSym;
    *nblock_ref = nblock;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}
pub fn helper_helper_helper_helper_BZ2_decompress_29_9_1_1(
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    es_ref: &mut Int32,
    N_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
    nSelectors: Int32,
) {
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut es = *es_ref;
    let mut N = *N_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    if N >= (2 * 1024 * 1024) {
        retVal = -4;
        *retVal_ref = retVal;
        return;
    }

    if nextSym == 0 {
        es += (0 + 1) * N;
    } else if nextSym == 1 {
        es += (1 + 1) * N;
    }
    N *= 2;

    {
        if groupPos == 0 {
            groupNo += 1;
            if groupNo >= nSelectors {
                retVal = -4;
                *retVal_ref = retVal;
                return;
            }
            groupPos = 50;
            gSel = s.selector[groupNo as usize] as Int32;
            gMinlen = s.min_lens[gSel as usize];
            gLimit_idx = 0;
            gPerm_idx = 0;
            gBase_idx = 0;
        }
        groupPos -= 1;
        zn = gMinlen;
        s.state = 38;

        loop {
            if s.bs_live >= zn {
                let v = (s.bs_buff >> (s.bs_live - zn)) & ((1 << zn) - 1);
                s.bs_live -= zn;
                zvec = v as Int32;
                break;
            }
            if s.strm.as_ref().unwrap().avail_in == 0 {
                retVal = 0;
                *retVal_ref = retVal;
                return;
            }
            let next_byte = s.strm.as_mut().unwrap().next_in.as_mut().unwrap()[0];
            s.bs_buff = (s.bs_buff << 8) | (next_byte as UInt32);
            s.bs_live += 8;
            s.strm.as_mut().unwrap().next_in.as_mut().unwrap().rotate_left(1);
            s.strm.as_mut().unwrap().avail_in -= 1;
            s.strm.as_mut().unwrap().total_in_lo32 += 1;
            if s.strm.as_mut().unwrap().total_in_lo32 == 0 {
                s.strm.as_mut().unwrap().total_in_hi32 += 1;
            }
        }

        loop {
            if zn > 20 {
                retVal = -4;
                *retVal_ref = retVal;
                return;
            }
            if zvec <= gLimit[zn as usize + gLimit_idx] {
                break;
            }
            zn += 1;
            s.state = 39;

            loop {
                if s.bs_live >= 1 {
                    let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
                    s.bs_live -= 1;
                    zj = v as Int32;
                    break;
                }
                if s.strm.as_ref().unwrap().avail_in == 0 {
                    retVal = 0;
                    *retVal_ref = retVal;
                    return;
                }
                let next_byte = s.strm.as_mut().unwrap().next_in.as_mut().unwrap()[0];
                s.bs_buff = (s.bs_buff << 8) | (next_byte as UInt32);
                s.bs_live += 8;
                s.strm.as_mut().unwrap().next_in.as_mut().unwrap().rotate_left(1);
                s.strm.as_mut().unwrap().avail_in -= 1;
                s.strm.as_mut().unwrap().total_in_lo32 += 1;
                if s.strm.as_mut().unwrap().total_in_lo32 == 0 {
                    s.strm.as_mut().unwrap().total_in_hi32 += 1;
                }
            }
            zvec = (zvec << 1) | zj;
        }

        if (zvec - gBase[zn as usize + gBase_idx]) < 0 || (zvec - gBase[zn as usize + gBase_idx]) >= 258 {
            retVal = -4;
            *retVal_ref = retVal;
            return;
        }
        nextSym = gPerm[(zvec - gBase[zn as usize + gBase_idx]) as usize + gPerm_idx];
    }

    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *nextSym_ref = nextSym;
    *es_ref = es;
    *N_ref = N;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}
pub fn helper_helper_helper_BZ2_decompress_29_9_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    nblock_ref: &mut Int32,
    es_ref: &mut Int32,
    N_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
    nSelectors: Int32,
    nblockMAX: Int32,
) {
    // Initialize local variables from references
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut nblock = *nblock_ref;
    let mut es = *es_ref;
    let mut N = *N_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    es = -1;
    N = 1;

    loop {
        helper_helper_helper_helper_BZ2_decompress_29_9_1_1(
            &mut retVal,
            &mut groupNo,
            &mut groupPos,
            &mut nextSym,
            &mut es,
            &mut N,
            &mut zn,
            &mut zvec,
            &mut zj,
            &mut gSel,
            &mut gMinlen,
            &mut gLimit_idx,
            &mut gBase_idx,
            &mut gPerm_idx,
            s,
            gLimit,
            gBase,
            gPerm,
            nSelectors,
        );

        if nextSym != 0 && nextSym != 1 {
            break;
        }
    }

    es += 1;
    uc = s.seq_to_unseq[s.mtfa[s.mtfbase[0] as usize] as usize] as UChar;
    s.unzftab[uc as usize] += es;

    if s.small_decompress != 0 {
        while es > 0 {
            if nblock >= nblockMAX {
                retVal = -4;
                break;
            }
            s.ll16.as_mut().unwrap()[nblock as usize] = uc as UInt16;
            nblock += 1;
            es -= 1;
        }
    } else {
        while es > 0 {
            if nblock >= nblockMAX {
                retVal = -4;
                break;
            }
            s.tt.as_mut().unwrap()[nblock as usize] = uc as UInt32;
            nblock += 1;
            es -= 1;
        }
    }

    // Update references with local variable values
    *uc_ref = uc;
    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *nextSym_ref = nextSym;
    *nblock_ref = nblock;
    *es_ref = es;
    *N_ref = N;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}
pub fn helper_helper_BZ2_decompress_29_9(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    nblock_ref: &mut Int32,
    es_ref: &mut Int32,
    N_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
    nSelectors: Int32,
    EOB: Int32,
    nblockMAX: Int32,
) {
    // Copy values from references
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut nblock = *nblock_ref;
    let mut es = *es_ref;
    let mut N = *N_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    if nextSym == EOB {
        // In Rust, we can't use 'break' outside a loop, so we'll just return early
        // Update references before returning
        *uc_ref = uc;
        *retVal_ref = retVal;
        *groupNo_ref = groupNo;
        *groupPos_ref = groupPos;
        *nextSym_ref = nextSym;
        *nblock_ref = nblock;
        *es_ref = es;
        *N_ref = N;
        *zn_ref = zn;
        *zvec_ref = zvec;
        *zj_ref = zj;
        *gSel_ref = gSel;
        *gMinlen_ref = gMinlen;
        *gLimit_idx_ref = gLimit_idx;
        *gBase_idx_ref = gBase_idx;
        *gPerm_idx_ref = gPerm_idx;
        return;
    }

    if nextSym == 0 || nextSym == 1 {
        helper_helper_helper_BZ2_decompress_29_9_1(
            &mut uc,
            &mut retVal,
            &mut groupNo,
            &mut groupPos,
            &mut nextSym,
            &mut nblock,
            &mut es,
            &mut N,
            &mut zn,
            &mut zvec,
            &mut zj,
            &mut gSel,
            &mut gMinlen,
            &mut gLimit_idx,
            &mut gBase_idx,
            &mut gPerm_idx,
            s,
            gLimit,
            gBase,
            gPerm,
            nSelectors,
            nblockMAX,
        );
    } else {
        helper_helper_helper_BZ2_decompress_29_9_2(
            &mut uc,
            &mut retVal,
            &mut groupNo,
            &mut groupPos,
            &mut nextSym,
            &mut nblock,
            &mut zn,
            &mut zvec,
            &mut zj,
            &mut gSel,
            &mut gMinlen,
            &mut gLimit_idx,
            &mut gBase_idx,
            &mut gPerm_idx,
            s,
            gLimit,
            gBase,
            gPerm,
            nSelectors,
            nblockMAX,
        );
    }

    // Update references with modified values
    *uc_ref = uc;
    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *nextSym_ref = nextSym;
    *nblock_ref = nblock;
    *es_ref = es;
    *N_ref = N;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}
pub fn helper_helper_helper_helper_BZ2_decompress_29_8_2_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    curr_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut curr = *curr_ref;

    if curr < 1 || curr > 20 {
        retVal = -4;
        *uc_ref = uc;
        *retVal_ref = retVal;
        *curr_ref = curr;
        return;
    }

    s.state = 34;

    'outer: loop {
        // Case 34
        loop {
            if s.bs_live >= 1 {
                let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
                s.bs_live -= 1;
                uc = v as UChar;
                break;
            }

            if s.strm.as_ref().unwrap().avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                *curr_ref = curr;
                return;
            }

            let strm = s.strm.as_mut().unwrap();
            let next_byte = strm.next_in.as_mut().unwrap()[0];
            s.bs_buff = (s.bs_buff << 8) | (next_byte as UInt32);
            s.bs_live += 8;
            strm.next_in.as_mut().unwrap().rotate_left(1);
            strm.avail_in -= 1;
            strm.total_in_lo32 += 1;
            if strm.total_in_lo32 == 0 {
                strm.total_in_hi32 += 1;
            }
        }

        if uc == 0 {
            break 'outer;
        }

        // Case 35
        s.state = 35;
        loop {
            if s.bs_live >= 1 {
                let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
                s.bs_live -= 1;
                uc = v as UChar;
                break;
            }

            if s.strm.as_ref().unwrap().avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                *curr_ref = curr;
                return;
            }

            let strm = s.strm.as_mut().unwrap();
            let next_byte = strm.next_in.as_mut().unwrap()[0];
            s.bs_buff = (s.bs_buff << 8) | (next_byte as UInt32);
            s.bs_live += 8;
            strm.next_in.as_mut().unwrap().rotate_left(1);
            strm.avail_in -= 1;
            strm.total_in_lo32 += 1;
            if strm.total_in_lo32 == 0 {
                strm.total_in_hi32 += 1;
            }
        }

        if uc == 0 {
            curr += 1;
        } else {
            curr -= 1;
        }
        curr -= 1;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
    *curr_ref = curr;
}
pub fn helper_helper_helper_BZ2_decompress_29_8_2(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    t_ref: &mut Int32,
    curr_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let i = *i_ref;
    let t = *t_ref;
    let mut curr = *curr_ref;

    loop {
        helper_helper_helper_helper_BZ2_decompress_29_8_2_1(&mut uc, &mut retVal, &mut curr, s);
    }

    s.len[t as usize][i as usize] = uc;
    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *t_ref = t;
    *curr_ref = curr;
}
pub fn helper_helper_helper_BZ2_decompress_29_8_1(
    ret_val_ref: &mut Int32,
    curr_ref: &mut Int32,
    s: &mut DState,
) {
    let mut ret_val = *ret_val_ref;
    let mut curr = *curr_ref;

    if s.bs_live >= 5 {
        let v = (s.bs_buff >> (s.bs_live - 5)) & ((1 << 5) - 1);
        s.bs_live -= 5;
        curr = v as Int32;
        *ret_val_ref = ret_val;
        *curr_ref = curr;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            ret_val = 0;
            *ret_val_ref = ret_val;
            *curr_ref = curr;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *ret_val_ref = ret_val;
    *curr_ref = curr;
}

pub fn helper_helper_BZ2_decompress_29_8(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    t_ref: &mut Int32,
    curr_ref: &mut Int32,
    s: &mut DState,
    alphaSize: Int32,
) {
    // Dereference input references to local variables
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut i = *i_ref;
    let mut t = *t_ref;
    let mut curr = *curr_ref;

    // Set state (line 8-9 in C code)
    s.state = 33;

    // Infinite loop (line 11-14 in C code)
    loop {
        helper_helper_helper_BZ2_decompress_29_8_1(&mut retVal, &mut curr, s);
    }

    // For loop (line 17-20 in C code)
    for i in 0..alphaSize {
        helper_helper_helper_BZ2_decompress_29_8_2(&mut uc, &mut retVal, &mut i, &mut t, &mut curr, s);
    }

    // Update references with local values (line 22-26 in C code)
    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *t_ref = t;
    *curr_ref = curr;
}

pub fn helper_helper_helper_helper_BZ2_decompress_29_7_3_1(
    retVal_ref: &mut Int32,
    zj_ref: &mut Int32,
    s: &mut DState,
) {
    let mut retVal = *retVal_ref;
    let mut zj = *zj_ref;

    if s.bs_live >= 1 {
        let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
        s.bs_live -= 1;
        zj = v as Int32;
        *retVal_ref = retVal;
        *zj_ref = zj;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *retVal_ref = retVal;
            *zj_ref = zj;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if next_in.is_empty() {
                retVal = 0;
                *retVal_ref = retVal;
                *zj_ref = zj;
                return;
            }

            s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
            s.bs_live += 8;
            strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
            strm.avail_in -= 1;
            strm.total_in_lo32 += 1;

            if strm.total_in_lo32 == 0 {
                strm.total_in_hi32 += 1;
            }
        } else {
            retVal = 0;
            *retVal_ref = retVal;
            *zj_ref = zj;
            return;
        }
    } else {
        retVal = 0;
        *retVal_ref = retVal;
        *zj_ref = zj;
        return;
    }

    *retVal_ref = retVal;
    *zj_ref = zj;
}
pub fn helper_helper_helper_BZ2_decompress_29_7_3(
    retVal_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    s: &mut DState,
    gLimit: &[Int32],
    gLimit_idx: usize,
) {
    let mut retVal = *retVal_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;

    if zn > 20 {
        retVal = -4;
        *retVal_ref = retVal;
        *zn_ref = zn;
        *zvec_ref = zvec;
        *zj_ref = zj;
        return;
    }

    let idx = (zn as usize) + gLimit_idx;
    if zvec <= gLimit[idx] {
        *retVal_ref = retVal;
        *zn_ref = zn;
        *zvec_ref = zvec;
        *zj_ref = zj;
        return;
    }

    zn += 1;
    s.state = 37;

    loop {
        helper_helper_helper_helper_BZ2_decompress_29_7_3_1(&mut retVal, &mut zj, s);
    }

    zvec = (zvec << 1) | zj;
    *retVal_ref = retVal;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
}
pub fn helper_helper_helper_BZ2_decompress_29_7_2(
    retVal_ref: &mut Int32,
    zvec_ref: &mut Int32,
    s: &mut DState,
    zn: Int32,
) {
    let mut retVal = *retVal_ref;
    let mut zvec = *zvec_ref;

    if s.bs_live >= zn {
        let v = (s.bs_buff >> (s.bs_live - zn)) & ((1 << zn) - 1);
        s.bs_live -= zn;
        zvec = v as Int32;
        *retVal_ref = retVal;
        *zvec_ref = zvec;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *retVal_ref = retVal;
            *zvec_ref = zvec;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *retVal_ref = retVal;
    *zvec_ref = zvec;
}
pub fn helper_helper_BZ2_decompress_29_7(
    retVal_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
    nSelectors: Int32,
) {
    let mut retVal = *retVal_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    if groupPos == 0 {
        helper_helper_helper_BZ2_decompress_29_7_1(
            &mut retVal,
            &mut groupNo,
            &mut groupPos,
            &mut gSel,
            &mut gMinlen,
            &mut gLimit_idx,
            &mut gBase_idx,
            &mut gPerm_idx,
            s,
            nSelectors,
        );
    }
    groupPos -= 1;
    zn = gMinlen;
    s.state = 36;

    loop {
        helper_helper_helper_BZ2_decompress_29_7_2(
            &mut retVal,
            &mut zvec,
            s,
            zn,
        );
    }

    loop {
        helper_helper_helper_BZ2_decompress_29_7_3(
            &mut retVal,
            &mut zn,
            &mut zvec,
            &mut zj,
            s,
            gLimit,
            gLimit_idx,
        );
    }

    let base_index = zn as usize + gBase_idx;
    if (zvec - gBase[base_index]) < 0 || (zvec - gBase[base_index]) >= 258 {
        retVal = -4;
    } else {
        let perm_index = (zvec - gBase[base_index]) as usize + gPerm_idx;
        nextSym = gPerm[perm_index];
    }

    *retVal_ref = retVal;
    *groupNo_ref = groupNo;
    *groupPos_ref = groupPos;
    *nextSym_ref = nextSym;
    *zn_ref = zn;
    *zvec_ref = zvec;
    *zj_ref = zj;
    *gSel_ref = gSel;
    *gMinlen_ref = gMinlen;
    *gLimit_idx_ref = gLimit_idx;
    *gBase_idx_ref = gBase_idx;
    *gPerm_idx_ref = gPerm_idx;
}

pub fn helper_helper_helper_BZ2_decompress_29_6_1(s: &mut DState) -> Bool {
    s.r_n_to_go = 0;
    s.r_t_pos = 0;
    
    if s.t_pos >= 100000 * (s.block_size100k as UInt32) {
        return 1;
    }
    
    s.k0 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab);
    
    {
        let t_pos = s.t_pos as usize;
        let ll16 = s.ll16.as_ref().unwrap();
        let ll4 = s.ll4.as_ref().unwrap();
        
        let low_bits = (ll16[t_pos] as UInt32);
        let high_nibble = ((ll4[t_pos >> 1] as UInt32) >> ((t_pos << 2) & 0x4)) & 0xF;
        s.t_pos = low_bits | (high_nibble << 16);
    }
    
    s.nblock_used += 1;
    
    if s.r_n_to_go == 0 {
        let mut r_nums = BZ2_rNums.lock().unwrap();
        s.r_n_to_go = r_nums[s.r_t_pos as usize];
        s.r_t_pos += 1;
        
        if s.r_t_pos == 512 {
            s.r_t_pos = 0;
        }
    }
    
    s.r_n_to_go -= 1;
    s.k0 ^= if s.r_n_to_go == 1 { 1 } else { 0 };
    
    0
}
pub fn helper_helper_BZ2_decompress_29_6(
    uc_ref: &mut UChar,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut DState,
    nblock: Int32,
) -> Bool {
    let mut uc = *uc_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;

    // Copy cftab to cftab_copy
    s.cftab_copy[..=256].copy_from_slice(&s.cftab[..=256]);

    // Process nblock elements
    for i in 0..nblock {
        uc = s.ll16.as_ref().unwrap()[i as usize] as UChar;
        let cftab_val = s.cftab_copy[uc as usize];
        
        // Update ll16
        s.ll16.as_mut().unwrap()[i as usize] = (cftab_val & 0x0000_FFFF) as UInt16;
        
        // Update ll4
        let i_shifted = i >> 1;
        let ll4_val = s.ll4.as_ref().unwrap()[i_shifted as usize];
        let new_val = if (i & 0x1) == 0 {
            (ll4_val & 0xF0) | ((cftab_val >> 16) as UChar)
        } else {
            (ll4_val & 0x0F) | (((cftab_val >> 16) << 4) as UChar)
        };
        s.ll4.as_mut().unwrap()[i_shifted as usize] = new_val;
        
        s.cftab_copy[uc as usize] += 1;
    }

    // Initialize i and j
    i = s.orig_ptr;
    j = {
        let ll16_val = s.ll16.as_ref().unwrap()[i as usize] as UInt32;
        let ll4_val = s.ll4.as_ref().unwrap()[i as usize >> 1] as UInt32;
        let shift = (i << 2) & 0x4;
        (ll16_val | (((ll4_val >> shift) & 0xF) << 16)) as Int32
    };

    // Process until we return to orig_ptr
    while i != s.orig_ptr {
        let tmp = {
            let ll16_val = s.ll16.as_ref().unwrap()[j as usize] as UInt32;
            let ll4_val = s.ll4.as_ref().unwrap()[j as usize >> 1] as UInt32;
            let shift = (j << 2) & 0x4;
            (ll16_val | (((ll4_val >> shift) & 0xF) << 16)) as Int32
        };

        // Update ll16
        s.ll16.as_mut().unwrap()[j as usize] = (i & 0x0000_FFFF) as UInt16;
        
        // Update ll4
        let j_shifted = j >> 1;
        let ll4_val = s.ll4.as_ref().unwrap()[j_shifted as usize];
        let new_val = if (j & 0x1) == 0 {
            (ll4_val & 0xF0) | ((i >> 16) as UChar)
        } else {
            (ll4_val & 0x0F) | (((i >> 16) << 4) as UChar)
        };
        s.ll4.as_mut().unwrap()[j_shifted as usize] = new_val;

        i = j;
        j = tmp;
    }

    s.t_pos = s.orig_ptr as UInt32;
    s.nblock_used = 0;

    if s.block_randomised != 0 {
        helper_helper_helper_BZ2_decompress_29_6_1(s);
    } else {
        if s.t_pos >= (100000 * s.block_size100k as UInt32) {
            *uc_ref = uc;
            *i_ref = i;
            *j_ref = j;
            return 1;
        }
        s.k0 = BZ2_indexIntoF(s.t_pos as Int32, &s.cftab);
        s.t_pos = {
            let ll16_val = s.ll16.as_ref().unwrap()[s.t_pos as usize] as UInt32;
            let ll4_val = s.ll4.as_ref().unwrap()[(s.t_pos >> 1) as usize] as UInt32;
            let shift = (s.t_pos << 2) & 0x4;
            ll16_val | (((ll4_val >> shift) & 0xF) << 16)
        };
        s.nblock_used += 1;
    }

    *uc_ref = uc;
    *i_ref = i;
    *j_ref = j;
    0
}
pub fn helper_helper_helper_helper_BZ2_decompress_29_5_1_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 1 {
        let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
        s.bs_live -= 1;
        uc = v as UChar;
        *uc_ref = uc;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}

pub fn helper_helper_helper_BZ2_decompress_29_5_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut DState,
    nGroups: Int32,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut j = *j_ref;

    s.state = 32;

    loop {
        helper_helper_helper_helper_BZ2_decompress_29_5_1_1(&mut uc, &mut retVal, s);
        
        if uc == 0 {
            break;
        }
        
        j += 1;
        if j >= nGroups {
            retVal = -4;
            break;
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
    *j_ref = j;
}

pub fn helper_helper_BZ2_decompress_29_5(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut DState,
    nGroups: Int32,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let i = *i_ref;
    let mut j = *j_ref;
    
    j = 0;
    
    loop {
        helper_helper_helper_BZ2_decompress_29_5_1(&mut uc, &mut retVal, &mut j, s, nGroups);
    }
    
    if i < (2 + (900000 / 50)) {
        s.selector_mtf[i as usize] = j as UChar;
    }
    
    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_BZ2_decompress_29_4(
    uc_ref: &mut UChar,
    i_ref: &mut Int32,
    s: &mut DState,
    nblock: Int32,
) -> Bool {
    let mut uc = *uc_ref;
    let mut i = *i_ref;

    // Ensure tt is available
    if let Some(ref mut tt) = s.tt {
        for i in 0..nblock {
            uc = (tt[i as usize] & 0xff) as UChar;
            let idx = s.cftab[uc as usize] as usize;
            tt[idx] |= (i as UInt32) << 8;
            s.cftab[uc as usize] += 1;
        }
    }

    if let Some(ref tt) = s.tt {
        s.t_pos = tt[s.orig_ptr as usize] >> 8;
    }
    s.nblock_used = 0;

    if s.block_randomised != 0 {
        helper_helper_helper_BZ2_decompress_29_4_1(s);
    } else {
        if let Some(tt) = &s.tt {
            if s.t_pos >= (100000 as UInt32) * (s.block_size100k as UInt32) {
                return 1;
            }
            s.t_pos = tt[s.t_pos as usize];
            s.k0 = (s.t_pos & 0xff) as Int32;
            s.t_pos >>= 8;
            s.nblock_used += 1;
        }
    }

    *uc_ref = uc;
    *i_ref = i;

    0
}

pub fn helper_helper_BZ2_decompress_29_3(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        uc = v as UChar;
        *uc_ref = uc;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_helper_BZ2_decompress_29_2(
    retVal_ref: &mut Int32,
    nSelectors_ref: &mut Int32,
    s: &mut DState,
) {
    let mut retVal = *retVal_ref;
    let mut nSelectors = *nSelectors_ref;

    if s.bs_live >= 15 {
        let v = (s.bs_buff >> (s.bs_live - 15)) & ((1 << 15) - 1);
        s.bs_live -= 15;
        nSelectors = v as Int32;
        *retVal_ref = retVal;
        *nSelectors_ref = nSelectors;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *retVal_ref = retVal;
            *nSelectors_ref = nSelectors;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *retVal_ref = retVal;
    *nSelectors_ref = nSelectors;
}
pub fn helper_helper_BZ2_decompress_29_1(i_ref: &mut Int32, s: &mut DState, nGroups: Int32, nSelectors: Int32) {
    let mut i = *i_ref;
    let mut pos: [UChar; 6] = [0; 6];
    let mut tmp: UChar;
    let mut v: UChar;

    // Initialize pos array
    for v in 0..nGroups as usize {
        pos[v] = v as UChar;
    }

    // Process selectors
    for i in 0..nSelectors {
        v = s.selector_mtf[i as usize];
        tmp = pos[v as usize];
        
        let mut current_v = v;
        while current_v > 0 {
            pos[current_v as usize] = pos[(current_v - 1) as usize];
            current_v -= 1;
        }

        pos[0] = tmp;
        s.selector[i as usize] = tmp;
    }

    *i_ref = i;
}
pub fn helper_BZ2_decompress_29(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    minLen_ref: &mut Int32,
    maxLen_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    t_ref: &mut Int32,
    nSelectors_ref: &mut Int32,
    EOB_ref: &mut Int32,
    groupNo_ref: &mut Int32,
    groupPos_ref: &mut Int32,
    nextSym_ref: &mut Int32,
    nblockMAX_ref: &mut Int32,
    nblock_ref: &mut Int32,
    es_ref: &mut Int32,
    N_ref: &mut Int32,
    curr_ref: &mut Int32,
    zn_ref: &mut Int32,
    zvec_ref: &mut Int32,
    zj_ref: &mut Int32,
    gSel_ref: &mut Int32,
    gMinlen_ref: &mut Int32,
    gLimit_idx_ref: &mut usize,
    gBase_idx_ref: &mut usize,
    gPerm_idx_ref: &mut usize,
    s: &mut DState,
    alphaSize: Int32,
    nGroups: Int32,
    gLimit: &[Int32],
    gBase: &[Int32],
    gPerm: &[Int32],
) {
    // Initialize local variables from references
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut minLen = *minLen_ref;
    let mut maxLen = *maxLen_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut t = *t_ref;
    let mut nSelectors = *nSelectors_ref;
    let mut EOB = *EOB_ref;
    let mut groupNo = *groupNo_ref;
    let mut groupPos = *groupPos_ref;
    let mut nextSym = *nextSym_ref;
    let mut nblockMAX = *nblockMAX_ref;
    let mut nblock = *nblock_ref;
    let mut es = *es_ref;
    let mut N = *N_ref;
    let mut curr = *curr_ref;
    let mut zn = *zn_ref;
    let mut zvec = *zvec_ref;
    let mut zj = *zj_ref;
    let mut gSel = *gSel_ref;
    let mut gMinlen = *gMinlen_ref;
    let mut gLimit_idx = *gLimit_idx_ref;
    let mut gBase_idx = *gBase_idx_ref;
    let mut gPerm_idx = *gPerm_idx_ref;

    s.state = 31;
    loop {
        helper_helper_BZ2_decompress_29_2(&mut retVal, &mut nSelectors, s);
    }

    if nSelectors < 1 {
        retVal = -4;
        goto_save_state_and_return();
        return;
    }

    for i in 0..nSelectors {
        helper_helper_BZ2_decompress_29_5(
            &mut uc,
            &mut retVal,
            &mut i,
            &mut j,
            s,
            nGroups,
        );
    }

    if nSelectors > (2 + (900000 / 50)) {
        nSelectors = 2 + (900000 / 50);
    }

    helper_helper_BZ2_decompress_29_1(&mut i, s, nGroups, nSelectors);

    for t in 0..nGroups {
        helper_helper_BZ2_decompress_29_8(
            &mut uc,
            &mut retVal,
            &mut i,
            &mut t,
            &mut curr,
            s,
            alphaSize,
        );
    }

    for t in 0..nGroups {
        minLen = 32;
        maxLen = 0;
        for i in 0..alphaSize {
            if i32::from(s.len[t as usize][i as usize]) > maxLen {
                maxLen = i32::from(s.len[t as usize][i as usize]);
            }
            if i32::from(s.len[t as usize][i as usize]) < minLen {
                minLen = i32::from(s.len[t as usize][i as usize]);
            }
        }

        BZ2_hbCreateDecodeTables(
            &mut s.limit[t as usize][0..258],
            &mut s.base[t as usize][0..258],
            &mut s.perm[t as usize][0..258],
            &s.len[t as usize][0..258],
            minLen,
            maxLen,
            alphaSize,
        );
        s.min_lens[t as usize] = minLen;
    }

    EOB = s.n_in_use + 1;
    nblockMAX = 100000 * s.block_size100k;
    groupNo = -1;
    groupPos = 0;

    for i in 0..=255 {
        s.unzftab[i as usize] = 0;
    }

    {
        let mut kk = 4096 - 1;
        for ii in (0..=(256 / 16 - 1)).rev() {
            for jj in (0..=15).rev() {
                s.mtfa[kk as usize] = ((ii * 16) + jj) as UChar;
                kk -= 1;
            }
            s.mtfbase[ii as usize] = kk + 1;
        }
    }

    nblock = 0;
    helper_helper_BZ2_decompress_29_7(
        &mut retVal,
        &mut groupNo,
        &mut groupPos,
        &mut nextSym,
        &mut zn,
        &mut zvec,
        &mut zj,
        &mut gSel,
        &mut gMinlen,
        &mut gLimit_idx,
        &mut gBase_idx,
        &mut gPerm_idx,
        s,
        gLimit,
        gBase,
        gPerm,
        nSelectors,
    );

    loop {
        helper_helper_BZ2_decompress_29_9(
            &mut uc,
            &mut retVal,
            &mut groupNo,
            &mut groupPos,
            &mut nextSym,
            &mut nblock,
            &mut es,
            &mut N,
            &mut zn,
            &mut zvec,
            &mut zj,
            &mut gSel,
            &mut gMinlen,
            &mut gLimit_idx,
            &mut gBase_idx,
            &mut gPerm_idx,
            s,
            gLimit,
            gBase,
            gPerm,
            nSelectors,
            EOB,
            nblockMAX,
        );
    }

    if s.orig_ptr < 0 || s.orig_ptr >= nblock {
        retVal = -4;
        goto_save_state_and_return();
        return;
    }

    for i in 0..=255 {
        if s.unzftab[i as usize] < 0 || s.unzftab[i as usize] > nblock {
            retVal = -4;
            goto_save_state_and_return();
            return;
        }
    }

    s.cftab[0] = 0;
    for i in 1..=256 {
        s.cftab[i as usize] = s.unzftab[(i - 1) as usize];
    }

    for i in 1..=256 {
        s.cftab[i as usize] += s.cftab[(i - 1) as usize];
    }

    for i in 0..=256 {
        if s.cftab[i as usize] < 0 || s.cftab[i as usize] > nblock {
            retVal = -4;
            goto_save_state_and_return();
            return;
        }
    }

    for i in 1..=256 {
        if s.cftab[(i - 1) as usize] > s.cftab[i as usize] {
            retVal = -4;
            goto_save_state_and_return();
            return;
        }
    }

    s.state_out_len = 0;
    s.state_out_ch = 0;
    s.calculated_block_crc = 0xffffffff;
    s.state = 2;

    if s.verbosity >= 2 {
        eprintln!("rt+rld");
    }

    if s.small_decompress != 0 {
        helper_helper_BZ2_decompress_29_6(&mut uc, &mut i, &mut j, s, nblock);
    } else {
        helper_helper_BZ2_decompress_29_4(&mut uc, &mut i, s, nblock);
    }

    retVal = 0;
    goto_save_state_and_return();

    fn goto_save_state_and_return() {
        // This would be the equivalent of the save_state_and_return label
        // In Rust we handle this by returning from the function
    }
}

pub fn helper_helper_helper_helper_BZ2_decompress_28_3_1_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let i = *i_ref;
    let j = *j_ref;

    s.state = 29;

    loop {
        if s.bs_live >= 1 {
            let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
            s.bs_live -= 1;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    break;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                break;
            }
        } else {
            retVal = 0;
            break;
        }
    }

    if uc == 1 {
        s.in_use[(i * 16 + j) as usize] = 1;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_helper_BZ2_decompress_28_3_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;

    for mut j in 0..16 {
        helper_helper_helper_helper_BZ2_decompress_28_3_1_1(&mut uc, &mut retVal, &mut i, &mut j, s);
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_BZ2_decompress_28_3(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;

    if s.in_use16[i as usize] != 0 {
        helper_helper_helper_BZ2_decompress_28_3_1(&mut uc, &mut retVal, &mut i, &mut j, s);
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *j_ref = j;
}
pub fn helper_helper_BZ2_decompress_28_2(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let i = *i_ref;

    s.state = 28;

    loop {
        if s.bs_live >= 1 {
            let v = (s.bs_buff >> (s.bs_live - 1)) & ((1 << 1) - 1);
            s.bs_live -= 1;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    break;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                break;
            }
        } else {
            retVal = 0;
            break;
        }
    }

    s.in_use16[i as usize] = if uc == 1 { 1 } else { 0 };

    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
}
pub fn helper_helper_BZ2_decompress_28_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        uc = v as UChar;
        *uc_ref = uc;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].into());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_28(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    alphaSize_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut alphaSize = *alphaSize_ref;
    
    s.state = 27;
    
    loop {
        helper_helper_BZ2_decompress_28_1(&mut uc, &mut retVal, s);
    }
    
    s.orig_ptr = (s.orig_ptr << 8) | (uc as Int32);
    if s.orig_ptr < 0 {
        retVal = -4;
        *uc_ref = uc;
        *retVal_ref = retVal;
        *i_ref = i;
        *j_ref = j;
        *alphaSize_ref = alphaSize;
        return;
    }
    
    if s.orig_ptr > (10 + (100000 * s.block_size100k)) {
        retVal = -4;
        *uc_ref = uc;
        *retVal_ref = retVal;
        *i_ref = i;
        *j_ref = j;
        *alphaSize_ref = alphaSize;
        return;
    }
    
    for i in 0..16 {
        helper_helper_BZ2_decompress_28_2(&mut uc, &mut retVal, &mut i, s);
    }
    
    for i in 0..256 {
        s.in_use[i] = 0;
    }
    
    for i in 0..16 {
        helper_helper_BZ2_decompress_28_3(&mut uc, &mut retVal, &mut i, &mut j, s);
    }
    
    makeMaps_d(s);
    if s.n_in_use == 0 {
        retVal = -4;
        *uc_ref = uc;
        *retVal_ref = retVal;
        *i_ref = i;
        *j_ref = j;
        *alphaSize_ref = alphaSize;
        return;
    }
    
    alphaSize = s.n_in_use + 2;
    *uc_ref = uc;
    *retVal_ref = retVal;
    *i_ref = i;
    *j_ref = j;
    *alphaSize_ref = alphaSize;
}
pub fn helper_helper_BZ2_decompress_27_1(retVal_ref: &mut Int32, s: &mut DState) {
    let mut retVal = *retVal_ref;
    
    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        s.block_size100k = v as Int32;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_27(retVal_ref: &mut Int32, s: &mut DState, strm: &mut BzStream) {
    let mut retVal = *retVal_ref;
    s.state = 13;
    
    loop {
        helper_helper_BZ2_decompress_27_1(&mut retVal, s);
    }
    
    if (s.block_size100k < (0x30 + 1)) || (s.block_size100k > (0x30 + 9)) {
        retVal = -5;
        *retVal_ref = retVal;
        return;
    }
    
    s.block_size100k -= 0x30;
    
    if s.small_decompress != 0 {
        let ll16_size = (s.block_size100k * 100000) as usize;
        let ll4_size = ((1 + (s.block_size100k * 100000)) >> 1) as usize;
        
        if let Some(bzalloc) = &mut strm.bzalloc {
            s.ll16 = bzalloc(strm.opaque.clone(), (ll16_size * std::mem::size_of::<UInt16>()) as i32, 1)
                .map(|ptr| unsafe { 
                    let raw_ptr = Box::into_raw(ptr) as *mut UInt16;
                    Box::from_raw(std::slice::from_raw_parts_mut(raw_ptr, ll16_size))
                });
            s.ll4 = bzalloc(strm.opaque.clone(), (ll4_size * std::mem::size_of::<UChar>()) as i32, 1)
                .map(|ptr| unsafe { 
                    let raw_ptr = Box::into_raw(ptr) as *mut UChar;
                    Box::from_raw(std::slice::from_raw_parts_mut(raw_ptr, ll4_size))
                });
            
            if s.ll16.is_none() || s.ll4.is_none() {
                retVal = -3;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = -3;
            *retVal_ref = retVal;
            return;
        }
    } else {
        let tt_size = (s.block_size100k * 100000) as usize;
        
        if let Some(bzalloc) = &mut strm.bzalloc {
            s.tt = bzalloc(strm.opaque.clone(), (tt_size * std::mem::size_of::<UInt32>()) as i32, 1)
                .map(|ptr| unsafe { 
                    let raw_ptr = Box::into_raw(ptr) as *mut UInt32;
                    Box::from_raw(std::slice::from_raw_parts_mut(raw_ptr, tt_size))
                });
            
            if s.tt.is_none() {
                retVal = -3;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = -3;
            *retVal_ref = retVal;
            return;
        }
    }
    
    *retVal_ref = retVal;
}
pub fn helper_helper_BZ2_decompress_26_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        uc = v as UChar;
        *uc_ref = uc;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}

pub fn helper_BZ2_decompress_26(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    
    s.state = 19;
    
    loop {
        helper_helper_BZ2_decompress_26_1(&mut uc, &mut retVal, s);
    }
    
    if uc != 0x59 {
        retVal = -4;
        // In Rust, we don't use goto. Instead, we'll just proceed to the end where values are assigned back
    }
    
    s.curr_block_no += 1;
    if s.verbosity >= 2 {
        let _ = writeln!(
            io::stderr(),
            "\n    [{}: huff+mtf ",
            s.curr_block_no
        );
    }
    
    s.stored_block_crc = 0;
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_helper_BZ2_decompress_25_1(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        uc = v as UChar;
        *uc_ref = uc;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_25(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    
    s.state = 50;
    
    loop {
        helper_helper_BZ2_decompress_25_1(&mut uc, &mut retVal, s);
    }
    
    s.stored_combined_crc = (s.stored_combined_crc << 8) | (uc as UInt32);
    s.state = 1;
    
    retVal = 4;
    
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_helper_BZ2_decompress_24_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        uc = v as UChar;
    } else {
        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}

pub fn helper_BZ2_decompress_24(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    
    s.state = 14;
    
    loop {
        helper_helper_BZ2_decompress_24_1(&mut uc, &mut retVal, s);
    }
    
    if uc == 0x17 {
        // In Rust, we don't use goto. Instead, we'll structure the code to avoid it.
        // The original goto endhdr_2 would jump to some label, but since we don't have
        // that context, we'll just proceed with the function.
    } else if uc != 0x31 {
        retVal = -4;
        // Original goto save_state_and_return would jump to some cleanup code.
        // In Rust, we'll just proceed to the state saving at the end.
    }
    
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_helper_BZ2_decompress_23_1(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;

    if s.bs_live >= 8 {
        let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
        s.bs_live -= 8;
        uc = v as UChar;
        *uc_ref = uc;
        *retVal_ref = retVal;
        return;
    }

    if let Some(strm) = &mut s.strm {
        if strm.avail_in == 0 {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(next_in) = &mut strm.next_in {
            if !next_in.is_empty() {
                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }
        }
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_23(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    
    s.state = 46;
    
    loop {
        helper_helper_BZ2_decompress_23_1(&mut uc, &mut retVal, s);
    }
    
    if uc != 0x90 {
        retVal = -4;
    }
    
    s.stored_combined_crc = 0;
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_22(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 45;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    *uc_ref = uc;
                    *retVal_ref = retVal;
                    return;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }
    }

    if uc != 0x50 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_21(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 44;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x38 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_20(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 43;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x45 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_2(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 21;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    s.stored_block_crc = (s.stored_block_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_19(
    retVal_ref: &mut Int32,
    nGroups_ref: &mut Int32,
    s: &mut DState,
) {
    let mut retVal = *retVal_ref;
    let mut nGroups = *nGroups_ref;
    s.state = 30;

    loop {
        if s.bs_live >= 3 {
            let v = (s.bs_buff >> (s.bs_live - 3)) & ((1 << 3) - 1);
            s.bs_live -= 3;
            nGroups = v as Int32;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *retVal_ref = retVal;
                *nGroups_ref = nGroups;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    *retVal_ref = retVal;
                    *nGroups_ref = nGroups;
                    return;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                *retVal_ref = retVal;
                *nGroups_ref = nGroups;
                return;
            }
        } else {
            retVal = 0;
            *retVal_ref = retVal;
            *nGroups_ref = nGroups;
            return;
        }
    }

    if nGroups < 2 || nGroups > 6 {
        retVal = -4;
    }

    *retVal_ref = retVal;
    *nGroups_ref = nGroups;
}

pub fn helper_BZ2_decompress_18(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 18;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if s.strm.as_ref().map_or(true, |strm| strm.avail_in == 0) {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(strm) = s.strm.as_mut() {
            if let Some(next_in) = strm.next_in.as_mut() {
                if strm.avail_in > 0 {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x53 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_17(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 17;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v.try_into().unwrap();
            break;
        }

        if s.strm.as_ref().map_or(true, |strm| strm.avail_in == 0) {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }

        if let Some(strm) = s.strm.as_mut() {
            if let Some(next_in) = strm.next_in.as_mut() {
                if strm.avail_in > 0 {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x26 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_16(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 16;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].into());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x59 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_15(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 15;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    *uc_ref = uc;
                    *retVal_ref = retVal;
                    return;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }
    }

    if uc != 0x41 {
        retVal = -4;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}

pub fn helper_BZ2_decompress_14(
    uc_ref: &mut UChar,
    retVal_ref: &mut Int32,
    s: &mut DState,
) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 11;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if next_in.is_empty() {
                    retVal = 0;
                    *uc_ref = uc;
                    *retVal_ref = retVal;
                    return;
                }

                s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                s.bs_live += 8;
                strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;

                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            } else {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }
        } else {
            retVal = 0;
            *uc_ref = uc;
            *retVal_ref = retVal;
            return;
        }
    }

    if uc != 0x5a {
        retVal = -5;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_13(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 10;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x42 {
        retVal = -5;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_12(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 12;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    if uc != 0x68 {
        retVal = -5;
    }

    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_10(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 49;
    
    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }
        
        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                *uc_ref = uc;
                *retVal_ref = retVal;
                return;
            }
            
            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }
    
    s.stored_combined_crc = (s.stored_combined_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn helper_BZ2_decompress_1(uc_ref: &mut UChar, retVal_ref: &mut Int32, s: &mut DState) {
    let mut uc = *uc_ref;
    let mut retVal = *retVal_ref;
    s.state = 20;

    loop {
        if s.bs_live >= 8 {
            let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
            s.bs_live -= 8;
            uc = v as UChar;
            break;
        }

        if let Some(strm) = &mut s.strm {
            if strm.avail_in == 0 {
                retVal = 0;
                break;
            }

            if let Some(next_in) = &mut strm.next_in {
                if !next_in.is_empty() {
                    s.bs_buff = (s.bs_buff << 8) | (next_in[0] as UInt32);
                    s.bs_live += 8;
                    strm.next_in = Some(next_in[1..].to_vec().into_boxed_slice());
                    strm.avail_in -= 1;
                    strm.total_in_lo32 += 1;
                    if strm.total_in_lo32 == 0 {
                        strm.total_in_hi32 += 1;
                    }
                }
            }
        }
    }

    s.stored_block_crc = (s.stored_block_crc << 8) | (uc as UInt32);
    *uc_ref = uc;
    *retVal_ref = retVal;
}
pub fn BZ2_decompress(s: &mut DState) -> Int32 {
    let mut uc: UChar = 0;
    let mut retVal: Int32 = 0;
    let mut minLen: Int32 = 0;
    let mut maxLen: Int32 = 0;
    let mut i: Int32;
    let mut j: Int32;
    let mut t: Int32;
    let mut alphaSize: Int32;
    let mut nGroups: Int32;
    let mut nSelectors: Int32;
    let mut EOB: Int32;
    let mut groupNo: Int32;
    let mut groupPos: Int32;
    let mut nextSym: Int32;
    let mut nblockMAX: Int32;
    let mut nblock: Int32;
    let mut es: Int32;
    let mut N: Int32;
    let mut curr: Int32;
    let mut zt: Int32;
    let mut zn: Int32;
    let mut zvec: Int32;
    let mut zj: Int32;
    let mut gSel: Int32;
    let mut gMinlen: Int32;
    let mut gLimit_idx: usize = 0;
    let mut gBase_idx: usize = 0;
    let mut gPerm_idx: usize = 0;

    if s.state == 10 {
        helper_BZ2_decompress_11(s);
    }

    i = s.save_i;
    j = s.save_j;
    t = s.save_t;
    alphaSize = s.save_alpha_size;
    nGroups = s.save_n_groups;
    nSelectors = s.save_n_selectors;
    EOB = s.save_eob;
    groupNo = s.save_group_no;
    groupPos = s.save_group_pos;
    nextSym = s.save_next_sym;
    nblockMAX = s.save_nblock_max;
    nblock = s.save_nblock;
    es = s.save_es;
    N = s.save_n;
    curr = s.save_curr;
    zt = s.save_zt;
    zn = s.save_zn;
    zvec = s.save_zvec;
    zj = s.save_zj;
    gSel = s.save_g_sel;
    gMinlen = s.save_g_minlen;
    gLimit_idx = s.save_g_limit.as_ref().map_or(0, |_| 0);
    gBase_idx = s.save_g_base.as_ref().map_or(0, |_| 0);
    gPerm_idx = s.save_g_perm.as_ref().map_or(0, |_| 0);
    retVal = 0;

    match s.state {
        10 => helper_BZ2_decompress_13(&mut uc, &mut retVal, s),
        11 => helper_BZ2_decompress_14(&mut uc, &mut retVal, s),
        12 => helper_BZ2_decompress_12(&mut uc, &mut retVal, s),
        13 => {
            let strm_ptr = s.strm.as_mut().unwrap().as_mut() as *mut BzStream;
            unsafe {
                helper_BZ2_decompress_27(&mut retVal, s, &mut *strm_ptr)
            }
        }
        14 => helper_BZ2_decompress_24(&mut uc, &mut retVal, s),
        15 => helper_BZ2_decompress_15(&mut uc, &mut retVal, s),
        16 => helper_BZ2_decompress_16(&mut uc, &mut retVal, s),
        17 => helper_BZ2_decompress_17(&mut uc, &mut retVal, s),
        18 => helper_BZ2_decompress_18(&mut uc, &mut retVal, s),
        19 => helper_BZ2_decompress_26(&mut uc, &mut retVal, s),
        20 => helper_BZ2_decompress_1(&mut uc, &mut retVal, s),
        21 => helper_BZ2_decompress_2(&mut uc, &mut retVal, s),
        22 => helper_BZ2_decompress_3(&mut uc, &mut retVal, s),
        23 => helper_BZ2_decompress_4(&mut uc, &mut retVal, s),
        24 => helper_BZ2_decompress_5(&mut retVal, s),
        25 => helper_BZ2_decompress_6(&mut uc, &mut retVal, s),
        26 => helper_BZ2_decompress_7(&mut uc, &mut retVal, s),
        27 => helper_BZ2_decompress_28(&mut uc, &mut retVal, &mut i, &mut j, &mut alphaSize, s),
        30 => helper_BZ2_decompress_19(&mut retVal, &mut nGroups, s),
        31 => {
            let g_limit_vec = s.save_g_limit.take()
                .map(|boxed| boxed.into_vec())
                .unwrap_or_else(|| vec![]);
            let g_base_vec = s.save_g_base.take()
                .map(|boxed| boxed.into_vec())
                .unwrap_or_else(|| vec![]);
            let g_perm_vec = s.save_g_perm.take()
                .map(|boxed| boxed.into_vec())
                .unwrap_or_else(|| vec![]);
            let g_limit = g_limit_vec.as_slice();
            let g_base = g_base_vec.as_slice();
            let g_perm = g_perm_vec.as_slice();
            helper_BZ2_decompress_29(
                &mut uc, &mut retVal, &mut minLen, &mut maxLen, &mut i, &mut j, &mut t,
                &mut nSelectors, &mut EOB, &mut groupNo, &mut groupPos, &mut nextSym,
                &mut nblockMAX, &mut nblock, &mut es, &mut N, &mut curr, &mut zn,
                &mut zvec, &mut zj, &mut gSel, &mut gMinlen, &mut gLimit_idx,
                &mut gBase_idx, &mut gPerm_idx, s, alphaSize, nGroups, g_limit, g_base, g_perm,
            )
        }
        43 => helper_BZ2_decompress_20(&mut uc, &mut retVal, s),
        44 => helper_BZ2_decompress_21(&mut uc, &mut retVal, s),
        45 => helper_BZ2_decompress_22(&mut uc, &mut retVal, s),
        46 => helper_BZ2_decompress_23(&mut uc, &mut retVal, s),
        47 => helper_BZ2_decompress_8(&mut uc, &mut retVal, s),
        48 => helper_BZ2_decompress_9(&mut uc, &mut retVal, s),
        49 => helper_BZ2_decompress_10(&mut uc, &mut retVal, s),
        50 => helper_BZ2_decompress_25(&mut uc, &mut retVal, s),
        _ => {
            BZ2_bz__AssertH__fail(4001);
        }
    }

    BZ2_bz__AssertH__fail(4002);

    s.save_i = i;
    s.save_j = j;
    s.save_t = t;
    s.save_alpha_size = alphaSize;
    s.save_n_groups = nGroups;
    s.save_n_selectors = nSelectors;
    s.save_eob = EOB;
    s.save_group_no = groupNo;
    s.save_group_pos = groupPos;
    s.save_next_sym = nextSym;
    s.save_nblock_max = nblockMAX;
    s.save_nblock = nblock;
    s.save_es = es;
    s.save_n = N;
    s.save_curr = curr;
    s.save_zt = zt;
    s.save_zn = zn;
    s.save_zvec = zvec;
    s.save_zj = zj;
    s.save_g_sel = gSel;
    s.save_g_minlen = gMinlen;
    s.save_g_limit = None;
    s.save_g_base = None;
    s.save_g_perm = None;

    retVal
}
