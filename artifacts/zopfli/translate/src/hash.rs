use crate::*;

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
    if let Some(head) = h.head.as_mut() {
        for i in 0..65536 {
            head[i] = -1;
        }
    }

    if let (Some(prev), Some(hashval)) = (h.prev.as_mut(), h.hashval.as_mut()) {
        for i in 0..window_size {
            prev[i] = i as u16;
            hashval[i] = -1;
        }
    }

    if let Some(same) = h.same.as_mut() {
        for i in 0..window_size {
            same[i] = 0;
        }
    }

    h.val2 = 0;
    if let Some(head2) = h.head2.as_mut() {
        for i in 0..65536 {
            head2[i] = -1;
        }
    }

    if let (Some(prev2), Some(hashval2)) = (h.prev2.as_mut(), h.hashval2.as_mut()) {
        for i in 0..window_size {
            prev2[i] = i as u16;
            hashval2[i] = -1;
        }
    }
}
pub fn ZopfliCleanHash(h: &mut ZopfliHash) {
    // In Rust, we don't need to explicitly free memory - dropping the Option<Vec> will handle it
    // We can just set all fields to None to release their memory
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
pub fn ZopfliUpdateHash(array: &[u8], pos: usize, end: usize, h: &mut ZopfliHash) {
    let hpos = (pos & (32768 - 1)) as u16;
    let mut amount = 0u16;

    // Update hash value
    let c = if pos + 3 <= end { array[pos + 3 - 1] } else { 0 };
    UpdateHashValue(h, c);

    // Safe unwrap since we know these vectors exist
    let hashval = h.hashval.as_mut().unwrap();
    let head = h.head.as_mut().unwrap();
    let prev = h.prev.as_mut().unwrap();
    let same = h.same.as_mut().unwrap();
    let hashval2 = h.hashval2.as_mut().unwrap();
    let head2 = h.head2.as_mut().unwrap();
    let prev2 = h.prev2.as_mut().unwrap();

    hashval[hpos as usize] = h.val;

    if head[h.val as usize] != -1 && hashval[head[h.val as usize] as usize] == h.val {
        prev[hpos as usize] = head[h.val as usize] as u16;
    } else {
        prev[hpos as usize] = hpos;
    }
    head[h.val as usize] = hpos as i32;

    if same[(pos - 1) & (32768 - 1)] > 1 {
        amount = same[(pos - 1) & (32768 - 1)] - 1;
    }

    while (pos + amount as usize + 1) < end 
        && array[pos] == array[pos + amount as usize + 1] 
        && amount < u16::MAX 
    {
        amount += 1;
    }

    same[hpos as usize] = amount;
    h.val2 = ((same[hpos as usize] - 3) & 255) as i32 ^ h.val;
    hashval2[hpos as usize] = h.val2;

    if head2[h.val2 as usize] != -1 && hashval2[head2[h.val2 as usize] as usize] == h.val2 {
        prev2[hpos as usize] = head2[h.val2 as usize] as u16;
    } else {
        prev2[hpos as usize] = hpos;
    }
    head2[h.val2 as usize] = hpos as i32;
}
pub fn ZopfliWarmupHash(array: &[u8], pos: usize, end: usize, h: &mut ZopfliHash) {
    UpdateHashValue(h, array[pos]);
    if pos + 1 < end {
        UpdateHashValue(h, array[pos + 1]);
    }
}
