use crate::*;
use std::sync::Mutex;

pub fn makeMaps_d(s: &mut DState) {
    s.n_in_use = 0;
    for i in 0..256 {
        if s.in_use[i] != 0 {
            s.seq_to_unseq[s.n_in_use as usize] = i as UChar;
            s.n_in_use += 1;
        }
    }
}
pub fn BZ2_decompress(s: &mut DState) -> Int32 {
    let mut uc: UChar = 0;
    let mut retVal: Int32 = 0;
    let mut minLen: Int32 = 0;
    let mut maxLen: Int32 = 0;
    let strm = s.strm.as_mut().unwrap();
    let mut i: Int32 = 0;
    let mut j: Int32 = 0;
    let mut t: Int32 = 0;
    let mut alphaSize: Int32 = 0;
    let mut nGroups: Int32 = 0;
    let mut nSelectors: Int32 = 0;
    let mut EOB: Int32 = 0;
    let mut groupNo: Int32 = 0;
    let mut groupPos: Int32 = 0;
    let mut nextSym: Int32 = 0;
    let mut nblockMAX: Int32 = 0;
    let mut nblock: Int32 = 0;
    let mut es: Int32 = 0;
    let mut N: Int32 = 0;
    let mut curr: Int32 = 0;
    let mut zt: Int32 = 0;
    let mut zn: Int32 = 0;
    let mut zvec: Int32 = 0;
    let mut zj: Int32 = 0;
    let mut gSel: Int32 = 0;
    let mut gMinlen: Int32 = 0;
    let mut gLimit: &[Int32] = &[];
    let mut gLimit_idx: usize = 0;
    let mut gBase: &[Int32] = &[];
    let mut gBase_idx: usize = 0;
    let mut gPerm: &[Int32] = &[];
    let mut gPerm_idx: usize = 0;

    if s.state == 10 {
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
    gLimit_idx = 0;
    gBase_idx = 0;
    gPerm_idx = 0;
    retVal = 0;

    match s.state {
        10 => {
            s.state = 10;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as UChar;
                    break;
                }
                if strm.avail_in == 0 {
                    retVal = 0;
                    break;
                }
                s.bs_buff = (s.bs_buff << 8) | (strm.next_in.as_ref().unwrap()[0] as UInt32);
                s.bs_live += 8;
                let mut next_in = strm.next_in.take().unwrap().into_vec();
                next_in.remove(0);
                strm.next_in = Some(next_in.into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }

            if uc != 0x42 {
                retVal = -5;
            }
        }
        11 => {
            s.state = 11;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as UChar;
                    break;
                }
                if strm.avail_in == 0 {
                    retVal = 0;
                    break;
                }
                s.bs_buff = (s.bs_buff << 8) | (strm.next_in.as_ref().unwrap()[0] as UInt32);
                s.bs_live += 8;
                let mut next_in = strm.next_in.take().unwrap().into_vec();
                next_in.remove(0);
                strm.next_in = Some(next_in.into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }

            if uc != 0x5a {
                retVal = -5;
            }
        }
        12 => {
            s.state = 12;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as UChar;
                    break;
                }
                if strm.avail_in == 0 {
                    retVal = 0;
                    break;
                }
                s.bs_buff = (s.bs_buff << 8) | (strm.next_in.as_ref().unwrap()[0] as UInt32);
                s.bs_live += 8;
                let mut next_in = strm.next_in.take().unwrap().into_vec();
                next_in.remove(0);
                strm.next_in = Some(next_in.into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }

            if uc != 0x68 {
                retVal = -5;
            }
        }
        13 => {
            s.state = 13;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    s.block_size100k = v as Int32;
                    break;
                }
                if strm.avail_in == 0 {
                    retVal = 0;
                    break;
                }
                s.bs_buff = (s.bs_buff << 8) | (strm.next_in.as_ref().unwrap()[0] as UInt32);
                s.bs_live += 8;
                let mut next_in = strm.next_in.take().unwrap().into_vec();
                next_in.remove(0);
                strm.next_in = Some(next_in.into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }

            if (s.block_size100k < (0x30 + 1)) || (s.block_size100k > (0x30 + 9)) {
                retVal = -5;
            } else {
                s.block_size100k -= 0x30;
                if s.small_decompress != 0 {
                    let ll16_size = (s.block_size100k * 100000) as usize;
                    let ll4_size = ((1 + (s.block_size100k * 100000)) >> 1) as usize;
                    s.ll16 = Some(vec![0; ll16_size].into_boxed_slice());
                    s.ll4 = Some(vec![0; ll4_size].into_boxed_slice());
                    if s.ll16.is_none() || s.ll4.is_none() {
                        retVal = -3;
                    }
                } else {
                    let tt_size = (s.block_size100k * 100000) as usize;
                    s.tt = Some(vec![0; tt_size].into_boxed_slice());
                    if s.tt.is_none() {
                        retVal = -3;
                    }
                }
            }
        }
        14 => {
            s.state = 14;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as UChar;
                    break;
                }
                if strm.avail_in == 0 {
                    retVal = 0;
                    break;
                }
                s.bs_buff = (s.bs_buff << 8) | (strm.next_in.as_ref().unwrap()[0] as UInt32);
                s.bs_live += 8;
                let mut next_in = strm.next_in.take().unwrap().into_vec();
                next_in.remove(0);
                strm.next_in = Some(next_in.into_boxed_slice());
                strm.avail_in -= 1;
                strm.total_in_lo32 += 1;
                if strm.total_in_lo32 == 0 {
                    strm.total_in_hi32 += 1;
                }
            }

            if uc == 0x17 {
                // endhdr_2 case
            } else if uc != 0x31 {
                retVal = -4;
            }
        }
        _ => {
            BZ2_bz__AssertH__fail(4001);
        }
    }

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
    s.save_g_limit = Some(gLimit.to_vec().into_boxed_slice());
    s.save_g_base = Some(gBase.to_vec().into_boxed_slice());
    s.save_g_perm = Some(gPerm.to_vec().into_boxed_slice());
    
    retVal
}
