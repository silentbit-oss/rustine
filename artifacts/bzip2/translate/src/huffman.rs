use crate::*;
use std::process;

pub fn helper_helper_BZ2_hbMakeCodeLengths_1_1(
    nHeap_ref: &mut Int32,
    i_ref: &mut Int32,
    heap: &mut [Int32; 258 + 2],
    weight: &[Int32; 258 * 2],
    parent: &mut [Int32; 258 * 2],
) {
    let mut nHeap = *nHeap_ref;
    let i = *i_ref;
    
    parent[i as usize] = -1;
    nHeap += 1;
    heap[nHeap as usize] = i;
    
    {
        let mut zz = nHeap;
        let tmp = heap[zz as usize];
        
        while weight[tmp as usize] < weight[heap[(zz >> 1) as usize] as usize] {
            heap[zz as usize] = heap[(zz >> 1) as usize];
            zz >>= 1;
        }
        
        heap[zz as usize] = tmp;
    }
    
    *nHeap_ref = nHeap;
    *i_ref = i;
}
pub fn helper_helper_helper_BZ2_hbMakeCodeLengths_1_2_1(heap: &mut [Int32], weight: &[Int32], nHeap: Int32) {
    let mut zz = 1;
    let tmp = heap[zz as usize];
    
    loop {
        let mut yy = zz << 1;
        if yy > nHeap {
            break;
        }
        
        if (yy < nHeap) && (weight[heap[(yy + 1) as usize] as usize] < weight[heap[yy as usize] as usize]) {
            yy += 1;
        }
        
        if weight[tmp as usize] < weight[heap[yy as usize] as usize] {
            break;
        }
        
        heap[zz as usize] = heap[yy as usize];
        zz = yy;
    }
    
    heap[zz as usize] = tmp;
}
pub fn helper_helper_helper_BZ2_hbMakeCodeLengths_1_2_2(heap: &mut [Int32], weight: &[Int32], nHeap: Int32) {
    let mut zz = 1;
    let tmp = heap[zz as usize];
    
    loop {
        let mut yy = zz << 1;
        if yy > nHeap {
            break;
        }
        
        if (yy < nHeap) && (weight[heap[(yy + 1) as usize] as usize] < weight[heap[yy as usize] as usize]) {
            yy += 1;
        }
        
        if weight[tmp as usize] < weight[heap[yy as usize] as usize] {
            break;
        }
        
        heap[zz as usize] = heap[yy as usize];
        zz = yy;
    }
    
    heap[zz as usize] = tmp;
}
pub fn helper_helper_BZ2_hbMakeCodeLengths_1_2(
    nNodes_ref: &mut Int32,
    nHeap_ref: &mut Int32,
    n1_ref: &mut Int32,
    n2_ref: &mut Int32,
    heap: &mut [Int32],
    weight: &mut [Int32],
    parent: &mut [Int32],
) {
    let mut nNodes = *nNodes_ref;
    let mut nHeap = *nHeap_ref;
    let mut n1 = *n1_ref;
    let mut n2 = *n2_ref;

    n1 = heap[1];
    heap[1] = heap[nHeap as usize];
    nHeap -= 1;
    {
        helper_helper_helper_BZ2_hbMakeCodeLengths_1_2_1(heap, weight, nHeap);
    }

    n2 = heap[1];
    heap[1] = heap[nHeap as usize];
    nHeap -= 1;
    {
        helper_helper_helper_BZ2_hbMakeCodeLengths_1_2_2(heap, weight, nHeap);
    }

    nNodes += 1;
    parent[n1 as usize] = nNodes;
    parent[n2 as usize] = nNodes;
    weight[nNodes as usize] = ((weight[n1 as usize] & 0xffffff00u32 as i32) + (weight[n2 as usize] & 0xffffff00u32 as i32))
        | (1 + if (weight[n1 as usize] & 0x000000ff) > (weight[n2 as usize] & 0x000000ff) {
            weight[n1 as usize] & 0x000000ff
        } else {
            weight[n2 as usize] & 0x000000ff
        });
    parent[nNodes as usize] = -1;
    nHeap += 1;
    heap[nHeap as usize] = nNodes;

    {
        let mut zz = nHeap;
        let tmp = heap[zz as usize];
        while weight[tmp as usize] < weight[heap[(zz >> 1) as usize] as usize] {
            heap[zz as usize] = heap[(zz >> 1) as usize];
            zz >>= 1;
        }
        heap[zz as usize] = tmp;
    }

    *nNodes_ref = nNodes;
    *nHeap_ref = nHeap;
    *n1_ref = n1;
    *n2_ref = n2;
}
pub fn helper_BZ2_hbMakeCodeLengths_1(
    nNodes_ref: &mut Int32,
    nHeap_ref: &mut Int32,
    n1_ref: &mut Int32,
    n2_ref: &mut Int32,
    i_ref: &mut Int32,
    j_ref: &mut Int32,
    k_ref: &mut Int32,
    tooLong_ref: &mut Bool,
    len: &mut [UChar],
    alphaSize: Int32,
    maxLen: Int32,
    heap: &mut [Int32; 258 + 2],
    weight: &mut [Int32; 258 * 2],
    parent: &mut [Int32; 258 * 2],
) {
    let mut nNodes = *nNodes_ref;
    let mut nHeap = *nHeap_ref;
    let mut n1 = *n1_ref;
    let mut n2 = *n2_ref;
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut k = *k_ref;
    let mut tooLong = *tooLong_ref;

    nNodes = alphaSize;
    nHeap = 0;
    heap[0] = 0;
    weight[0] = 0;
    parent[0] = -2;

    for mut i in 1..=alphaSize {
        helper_helper_BZ2_hbMakeCodeLengths_1_1(
            &mut nHeap,
            &mut i,
            heap,
            weight,
            parent,
        );
    }

    if !(nHeap < (258 + 2)) {
        BZ2_bz__AssertH__fail(2001);
    }

    while nHeap > 1 {
        helper_helper_BZ2_hbMakeCodeLengths_1_2(
            &mut nNodes,
            &mut nHeap,
            &mut n1,
            &mut n2,
            heap,
            weight,
            parent,
        );
    }

    if !(nNodes < (258 * 2)) {
        BZ2_bz__AssertH__fail(2002);
    }

    tooLong = 0;
    for i in 1..=alphaSize {
        j = 0;
        k = i;
        while parent[k as usize] >= 0 {
            k = parent[k as usize];
            j += 1;
        }

        len[(i - 1) as usize] = j as UChar;
        if j > maxLen {
            tooLong = 1;
        }
    }

    if tooLong == 0 {
        return;
    }

    for i in 1..=alphaSize {
        j = weight[i as usize] >> 8;
        j = 1 + (j / 2);
        weight[i as usize] = j << 8;
    }

    *nNodes_ref = nNodes;
    *nHeap_ref = nHeap;
    *n1_ref = n1;
    *n2_ref = n2;
    *i_ref = i;
    *j_ref = j;
    *k_ref = k;
    *tooLong_ref = tooLong;
}
pub fn BZ2_hbMakeCodeLengths(
    len: &mut [UChar],
    freq: &[Int32],
    alphaSize: Int32,
    maxLen: Int32,
) {
    let mut nNodes: Int32 = 0;
    let mut nHeap: Int32 = 0;
    let mut n1: Int32 = 0;
    let mut n2: Int32 = 0;
    let mut i: Int32 = 0;
    let mut j: Int32 = 0;
    let mut k: Int32 = 0;
    let mut tooLong: Bool = 0;
    let mut heap: [Int32; 258 + 2] = [0; 258 + 2];
    let mut weight: [Int32; 258 * 2] = [0; 258 * 2];
    let mut parent: [Int32; 258 * 2] = [0; 258 * 2];

    // Initialize weight array
    for i in 0..alphaSize {
        weight[(i + 1) as usize] = (if freq[i as usize] == 0 { 1 } else { freq[i as usize] }) << 8;
    }

    loop {
        helper_BZ2_hbMakeCodeLengths_1(
            &mut nNodes,
            &mut nHeap,
            &mut n1,
            &mut n2,
            &mut i,
            &mut j,
            &mut k,
            &mut tooLong,
            len,
            alphaSize,
            maxLen,
            &mut heap,
            &mut weight,
            &mut parent,
        );
    }
}
pub fn BZ2_hbAssignCodes(
    code: &mut [Int32],
    length: &[UChar],
    minLen: Int32,
    maxLen: Int32,
    alphaSize: Int32,
) {
    let mut vec = 0;
    for n in minLen..=maxLen {
        for i in 0..alphaSize {
            if length[i as usize] == n as UChar {
                code[i as usize] = vec;
                vec += 1;
            }
        }
        vec <<= 1;
    }
}
pub fn BZ2_hbCreateDecodeTables(
    limit: &mut [Int32],
    base: &mut [Int32],
    perm: &mut [Int32],
    length: &[UChar],
    minLen: Int32,
    maxLen: Int32,
    alphaSize: Int32,
) {
    let mut pp = 0;
    
    // First loop: populate perm array
    for i in minLen..=maxLen {
        for j in 0..alphaSize {
            if length[j as usize] == i as UChar {
                perm[pp as usize] = j;
                pp += 1;
            }
        }
    }

    // Initialize base array
    for i in 0..23 {
        base[i as usize] = 0;
    }

    // Count occurrences in base array
    for i in 0..alphaSize {
        let len = length[i as usize] as usize + 1;
        if len < 23 {
            base[len] += 1;
        }
    }

    // Cumulative sum for base array
    for i in 1..23 {
        base[i] += base[i - 1];
    }

    // Initialize limit array
    for i in 0..23 {
        limit[i] = 0;
    }

    // Calculate limit array
    let mut vec = 0;
    for i in minLen..=maxLen {
        vec += base[(i + 1) as usize] - base[i as usize];
        limit[i as usize] = vec - 1;
        vec <<= 1;
    }

    // Final adjustment of base array
    for i in (minLen + 1)..=maxLen {
        base[i as usize] = ((limit[(i - 1) as usize] + 1) << 1) - base[i as usize];
    }
}
