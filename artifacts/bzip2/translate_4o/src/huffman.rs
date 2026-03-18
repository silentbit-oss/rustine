use crate::*;
use std::process;

pub fn BZ2_hbMakeCodeLengths(
    len: &mut [UChar],
    freq: &[Int32],
    alphaSize: Int32,
    maxLen: Int32,
) {
    let mut nNodes: Int32;
    let mut nHeap: Int32;
    let mut n1: Int32;
    let mut n2: Int32;
    let mut i: Int32;
    let mut j: Int32;
    let mut k: Int32;
    let mut tooLong: Bool;
    let mut heap = [0; 258 + 2];
    let mut weight = [0; 258 * 2];
    let mut parent = [0; 258 * 2];

    for i in 0..alphaSize as usize {
        weight[i + 1] = (if freq[i] == 0 { 1 } else { freq[i] }) << 8;
    }

    loop {
        nNodes = alphaSize;
        nHeap = 0;
        heap[0] = 0;
        weight[0] = 0;
        parent[0] = -2;

        for i in 1..=alphaSize as usize {
            parent[i] = -1;
            nHeap += 1;
            heap[nHeap as usize] = i as Int32;

            let mut zz = nHeap as usize;
            let tmp = heap[zz];
            while weight[tmp as usize] < weight[heap[zz >> 1] as usize] {
                heap[zz] = heap[zz >> 1];
                zz >>= 1;
            }
            heap[zz] = tmp;
        }

        if !(nHeap < (258 + 2)) {
            BZ2_bz__AssertH__fail(2001);
        }

        while nHeap > 1 {
            n1 = heap[1];
            heap[1] = heap[nHeap as usize];
            nHeap -= 1;

            let mut zz = 1;
            let tmp = heap[zz];
            loop {
                let yy = zz << 1;
                if yy > nHeap as usize {
                    break;
                }
                if (yy < nHeap as usize) && (weight[heap[yy + 1] as usize] < weight[heap[yy] as usize]) {
                    zz = yy + 1;
                } else {
                    zz = yy;
                }
                if weight[tmp as usize] < weight[heap[zz] as usize] {
                    break;
                }
                heap[zz >> 1] = heap[zz];
            }
            heap[zz >> 1] = tmp;

            n2 = heap[1];
            heap[1] = heap[nHeap as usize];
            nHeap -= 1;

            let mut zz = 1;
            let tmp = heap[zz];
            loop {
                let yy = zz << 1;
                if yy > nHeap as usize {
                    break;
                }
                if (yy < nHeap as usize) && (weight[heap[yy + 1] as usize] < weight[heap[yy] as usize]) {
                    zz = yy + 1;
                } else {
                    zz = yy;
                }
                if weight[tmp as usize] < weight[heap[zz] as usize] {
                    break;
                }
                heap[zz >> 1] = heap[zz];
            }
            heap[zz >> 1] = tmp;

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

            let mut zz = nHeap as usize;
            let tmp = heap[zz];
            while weight[tmp as usize] < weight[heap[zz >> 1] as usize] {
                heap[zz] = heap[zz >> 1];
                zz >>= 1;
            }
            heap[zz] = tmp;
        }

        if !(nNodes < (258 * 2)) {
            BZ2_bz__AssertH__fail(2002);
        }

        tooLong = 0;
        for i in 1..=alphaSize as usize {
            j = 0;
            k = i as Int32;
            while parent[k as usize] >= 0 {
                k = parent[k as usize];
                j += 1;
            }

            len[i - 1] = j as UChar;
            if j > maxLen {
                tooLong = 1;
            }
        }

        if tooLong == 0 {
            break;
        }

        for i in 1..=alphaSize as usize {
            j = weight[i] >> 8;
            j = 1 + (j / 2);
            weight[i] = j << 8;
        }
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

    // Final base array calculation
    for i in (minLen + 1)..=maxLen {
        base[i as usize] = ((limit[(i - 1) as usize] + 1) << 1) - base[i as usize];
    }
}
