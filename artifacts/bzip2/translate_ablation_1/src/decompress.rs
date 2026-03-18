use crate::*;
use std::mem;
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
pub fn BZ2_decompress(s: &mut DState) -> i32 {
    let mut uc: u8 = 0;
    let mut ret_val: i32 = 0;
    let mut min_len: i32;
    let mut max_len: i32;
    let strm = &mut s.strm;
    let mut i: i32;
    let mut j: i32;
    let mut t: i32;
    let mut alpha_size: i32;
    let mut n_groups: i32;
    let mut n_selectors: i32;
    let mut eob: i32;
    let mut group_no: i32;
    let mut group_pos: i32;
    let mut next_sym: i32;
    let mut nblock_max: i32;
    let mut nblock: i32;
    let mut es: i32;
    let mut n: i32;
    let mut curr: i32;
    let mut zt: i32;
    let mut zn: i32;
    let mut zvec: i32;
    let mut zj: i32;
    let mut g_sel: i32;
    let mut g_minlen: i32;
    let mut g_limit: Option<Box<[i32]>>;
    let mut g_base: Option<Box<[i32]>>;
    let mut g_perm: Option<Box<[i32]>>;

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
        s.save_nblock = 0;
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
    alpha_size = s.save_alpha_size;
    n_groups = s.save_n_groups;
    n_selectors = s.save_n_selectors;
    eob = s.save_eob;
    group_no = s.save_group_no;
    group_pos = s.save_group_pos;
    next_sym = s.save_next_sym;
    nblock_max = s.save_nblock;
    nblock = s.save_nblock;
    es = s.save_es;
    n = s.save_n;
    curr = s.save_curr;
    zt = s.save_zt;
    zn = s.save_zn;
    zvec = s.save_zvec;
    zj = s.save_zj;
    g_sel = s.save_g_sel;
    g_minlen = s.save_g_minlen;
    g_limit = s.save_g_limit.take();
    g_base = s.save_g_base.take();
    g_perm = s.save_g_perm.take();
    ret_val = 0;

    match s.state {
        10 => {
            s.state = 10;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as u8;
                    break;
                }
                if strm.as_mut().unwrap().avail_in == 0 {
                    ret_val = 0;
                    break;
                }
                let next_in_ptr = strm.as_mut().unwrap().next_in.as_mut().unwrap();
                s.bs_buff = (s.bs_buff << 8) | (next_in_ptr[0] as u32);
                s.bs_live += 8;
                strm.as_mut().unwrap().next_in = Some(next_in_ptr[1..].to_vec().into_boxed_slice());
                strm.as_mut().unwrap().avail_in -= 1;
                strm.as_mut().unwrap().total_in_lo32 += 1;
                if strm.as_mut().unwrap().total_in_lo32 == 0 {
                    strm.as_mut().unwrap().total_in_hi32 += 1;
                }
            }
            if ret_val != 0 {
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }

            if uc != 0x42 {
                ret_val = -5;
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }
            s.state = 11;
        }
        11 => {
            s.state = 11;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as u8;
                    break;
                }
                if strm.as_mut().unwrap().avail_in == 0 {
                    ret_val = 0;
                    break;
                }
                let next_in_ptr = strm.as_mut().unwrap().next_in.as_mut().unwrap();
                s.bs_buff = (s.bs_buff << 8) | (next_in_ptr[0] as u32);
                s.bs_live += 8;
                strm.as_mut().unwrap().next_in = Some(next_in_ptr[1..].to_vec().into_boxed_slice());
                strm.as_mut().unwrap().avail_in -= 1;
                strm.as_mut().unwrap().total_in_lo32 += 1;
                if strm.as_mut().unwrap().total_in_lo32 == 0 {
                    strm.as_mut().unwrap().total_in_hi32 += 1;
                }
            }
            if ret_val != 0 {
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }

            if uc != 0x5a {
                ret_val = -5;
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }
            s.state = 12;
        }
        12 => {
            s.state = 12;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    uc = v as u8;
                    break;
                }
                if strm.as_mut().unwrap().avail_in == 0 {
                    ret_val = 0;
                    break;
                }
                let next_in_ptr = strm.as_mut().unwrap().next_in.as_mut().unwrap();
                s.bs_buff = (s.bs_buff << 8) | (next_in_ptr[0] as u32);
                s.bs_live += 8;
                strm.as_mut().unwrap().next_in = Some(next_in_ptr[1..].to_vec().into_boxed_slice());
                strm.as_mut().unwrap().avail_in -= 1;
                strm.as_mut().unwrap().total_in_lo32 += 1;
                if strm.as_mut().unwrap().total_in_lo32 == 0 {
                    strm.as_mut().unwrap().total_in_hi32 += 1;
                }
            }
            if ret_val != 0 {
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }

            if uc != 0x68 {
                ret_val = -5;
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }
            s.state = 13;
        }
        13 => {
            s.state = 13;
            loop {
                if s.bs_live >= 8 {
                    let v = (s.bs_buff >> (s.bs_live - 8)) & ((1 << 8) - 1);
                    s.bs_live -= 8;
                    s.block_size100k = v as i32;
                    break;
                }
                if strm.as_mut().unwrap().avail_in == 0 {
                    ret_val = 0;
                    break;
                }
                let next_in_ptr = strm.as_mut().unwrap().next_in.as_mut().unwrap();
                s.bs_buff = (s.bs_buff << 8) | (next_in_ptr[0] as u32);
                s.bs_live += 8;
                strm.as_mut().unwrap().next_in = Some(next_in_ptr[1..].to_vec().into_boxed_slice());
                strm.as_mut().unwrap().avail_in -= 1;
                strm.as_mut().unwrap().total_in_lo32 += 1;
                if strm.as_mut().unwrap().total_in_lo32 == 0 {
                    strm.as_mut().unwrap().total_in_hi32 += 1;
                }
            }
            if ret_val != 0 {
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }

            if (s.block_size100k < (0x30 + 1)) || (s.block_size100k > (0x30 + 9)) {
                ret_val = -5;
                return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
            }
            s.block_size100k -= 0x30;

            if s.small_decompress != 0 {
                let n = s.block_size100k * 100000;
                let stream = strm.as_mut().unwrap();
                if let Some(ref mut bzalloc_fn) = stream.bzalloc {
                    let opaque = stream.opaque.take();
                    let ptr = bzalloc_fn(
                        opaque.clone(),
                        n as i32,
                        std::mem::size_of::<u16>() as i32,
                    );
                    stream.opaque = opaque;
                    match ptr {
                        Some(p) => {
                            let raw_ptr = Box::into_raw(p) as *mut u16;
                            let slice = unsafe { Box::from_raw(std::slice::from_raw_parts_mut(raw_ptr, n as usize)) };
                            s.ll16 = Some(slice);
                        }
                        None => {
                            ret_val = -3;
                            return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
                        }
                    }
                } else {
                    ret_val = -3;
                    return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
                }
                let ll4_len = (1 + n) / 2;
                let stream = strm.as_mut().unwrap();
                if let Some(ref mut bzalloc_fn) = stream.bzalloc {
                    let opaque = stream.opaque.take();
                    let ptr = bzalloc_fn(
                        opaque.clone(),
                        ll4_len as i32,
                        std::mem::size_of::<u8>() as i32,
                    );
                    stream.opaque = opaque;
                    match ptr {
                        Some(p) => {
                            let raw_ptr = Box::into_raw(p) as *mut u8;
                            let slice = unsafe { Box::from_raw(std::slice::from_raw_parts_mut(raw_ptr, ll4_len as usize)) };
                            s.ll4 = Some(slice);
                        }
                        None => {
                            ret_val = -3;
                            return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
                        }
                    }
                } else {
                    ret_val = -3;
                    return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
                }
            } else {
                let n = s.block_size100k * 100000;
                let stream = strm.as_mut().unwrap();
                if let Some(ref mut bzalloc_fn) = stream.bzalloc {
                    let opaque = stream.opaque.take();
                    let ptr = bzalloc_fn(
                        opaque.clone(),
                        n as i32,
                        std::mem::size_of::<u32>() as i32,
                    );
                    stream.opaque = opaque;
                    match ptr {
                        Some(p) => {
                            let raw_ptr = Box::into_raw(p) as *mut u32;
                            let slice = unsafe { Box::from_raw(std::slice::from_raw_parts_mut(raw_ptr, n as usize)) };
                            s.tt = Some(slice);
                        }
                        None => {
                            ret_val = -3;
                            return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
                        }
                    }
                } else {
                    ret_val = -3;
                    return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
                }
            }
            s.state = 14;
        }
        // ... (continue with other state cases)
        _ => {
            if !false {
                BZ2_bz__AssertH__fail(4001);
            }
            ret_val = -1;
            return save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val);
        }
    }

    save_state_and_return(s, i, j, t, alpha_size, n_groups, n_selectors, eob, group_no, group_pos, next_sym, nblock_max, nblock, es, n, curr, zt, zn, zvec, zj, g_sel, g_minlen, g_limit, g_base, g_perm, ret_val)
}

fn save_state_and_return(s: &mut DState, i: i32, j: i32, t: i32, alpha_size: i32, n_groups: i32, n_selectors: i32, eob: i32, group_no: i32, group_pos: i32, next_sym: i32, nblock_max: i32, nblock: i32, es: i32, n: i32, curr: i32, zt: i32, zn: i32, zvec: i32, zj: i32, g_sel: i32, g_minlen: i32, g_limit: Option<Box<[i32]>>, g_base: Option<Box<[i32]>>, g_perm: Option<Box<[i32]>>, ret_val: i32) -> i32 {
    s.save_i = i;
    s.save_j = j;
    s.save_t = t;
    s.save_alpha_size = alpha_size;
    s.save_n_groups = n_groups;
    s.save_n_selectors = n_selectors;
    s.save_eob = eob;
    s.save_group_no = group_no;
    s.save_group_pos = group_pos;
    s.save_next_sym = next_sym;
    s.save_nblock = nblock_max;
    s.save_nblock = nblock;
    s.save_es = es;
    s.save_n = n;
    s.save_curr = curr;
    s.save_zt = zt;
    s.save_zn = zn;
    s.save_zvec = zvec;
    s.save_zj = zj;
    s.save_g_sel = g_sel;
    s.save_g_minlen = g_minlen;
    s.save_g_limit = g_limit;
    s.save_g_base = g_base;
    s.save_g_perm = g_perm;

    ret_val
}
