use crate::*;
use rand::Rng;

pub fn ZopfliAllocHash(window_size: usize, h: &mut ZopfliHash) {
    h.head = Some(vec![0; 65536]);
    h.prev = Some(vec![0; window_size]);
    h.hashval = Some(vec![0; window_size]);
    h.same = Some(vec![0; window_size]);
    h.head2 = Some(vec![0; 65536]);
    h.prev2 = Some(vec![0; window_size]);
    h.hashval2 = Some(vec![0; window_size]);
}
pub fn ZopfliResetHash(window_size: usize, h: &mut ZopfliHash) {
    h.val = 0;
    
    // Initialize head array
    if let Some(head) = h.head.as_mut() {
        for i in 0..65536 {
            head[i] = -1;
        }
    }

    // Initialize prev and hashval arrays
    if let (Some(prev), Some(hashval)) = (h.prev.as_mut(), h.hashval.as_mut()) {
        for i in 0..window_size {
            prev[i] = i as u16;
            hashval[i] = -1;
        }
    }

    // Initialize same array
    if let Some(same) = h.same.as_mut() {
        for i in 0..window_size {
            same[i] = 0;
        }
    }

    h.val2 = 0;
    
    // Initialize head2 array
    if let Some(head2) = h.head2.as_mut() {
        for i in 0..65536 {
            head2[i] = -1;
        }
    }

    // Initialize prev2 and hashval2 arrays
    if let (Some(prev2), Some(hashval2)) = (h.prev2.as_mut(), h.hashval2.as_mut()) {
        for i in 0..window_size {
            prev2[i] = i as u16;
            hashval2[i] = -1;
        }
    }
}
pub fn ZopfliCleanHash(h: &mut ZopfliHash) {
    h.head = None;
    h.prev = None;
    h.hashval = None;
    h.head2 = None;
    h.prev2 = None;
    h.hashval2 = None;
    h.same = None;
}
pub fn UpdateHashValue(h: &mut ZopfliHash, c: u8) {
    h.val = ((h.val << 5) ^ (c as i32)) & 32767;
}
pub fn ZopfliWarmupHash(array: &[u8], pos: usize, end: usize, h: &mut ZopfliHash) {
    UpdateHashValue(h, array[pos]);
    if pos + 1 < end {
        UpdateHashValue(h, array[pos + 1]);
    }
}
pub fn ZopfliUpdateHash(array: &[u8], pos: usize, end: usize, h: &mut ZopfliHash) {
    let hpos = pos & (32768 - 1);
    let mut amount = 0usize;

    // Update hash value based on array[pos + 3 - 1] if within bounds, else 0
    let c = if pos + 3 <= end {
        array[pos + 3 - 1]
    } else {
        0
    };
    UpdateHashValue(h, c);

    // Safe unwrap since we know these vectors exist (from C code assumptions)
    h.hashval.as_mut().unwrap()[hpos] = h.val;

    if h.head.as_ref().unwrap()[h.val as usize] != -1 
        && h.hashval.as_ref().unwrap()[h.head.as_ref().unwrap()[h.val as usize] as usize] == h.val 
    {
        h.prev.as_mut().unwrap()[hpos] = h.head.as_ref().unwrap()[h.val as usize] as u16;
    } else {
        h.prev.as_mut().unwrap()[hpos] = hpos as u16;
    }
    h.head.as_mut().unwrap()[h.val as usize] = hpos as i32;

    // Calculate amount
    if h.same.as_ref().unwrap()[(pos - 1) & (32768 - 1)] > 1 {
        amount = h.same.as_ref().unwrap()[(pos - 1) & (32768 - 1)] as usize - 1;
    }

    while (pos + amount + 1) < end 
        && array[pos] == array[pos + amount + 1] 
        && amount < u16::MAX as usize 
    {
        amount += 1;
    }

    h.same.as_mut().unwrap()[hpos] = amount as u16;

    h.val2 = ((h.same.as_ref().unwrap()[hpos] as i32 - 3) & 255) ^ h.val;
    h.hashval2.as_mut().unwrap()[hpos] = h.val2;

    if h.head2.as_ref().unwrap()[h.val2 as usize] != -1 
        && h.hashval2.as_ref().unwrap()[h.head2.as_ref().unwrap()[h.val2 as usize] as usize] == h.val2 
    {
        h.prev2.as_mut().unwrap()[hpos] = h.head2.as_ref().unwrap()[h.val2 as usize] as u16;
    } else {
        h.prev2.as_mut().unwrap()[hpos] = hpos as u16;
    }
    h.head2.as_mut().unwrap()[h.val2 as usize] = hpos as i32;
}
