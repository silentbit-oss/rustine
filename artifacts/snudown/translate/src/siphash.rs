use crate::*;

pub fn helper_siphash_nocase_3(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the siphash operations
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the references with the new values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_nocase_6(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the bit manipulation operations
    v0 += v1;
    v1 = (v1 << 13) | (v1 >> (64 - 13));
    v1 ^= v0;
    v0 = (v0 << 32) | (v0 >> (64 - 32));
    v2 += v3;
    v3 = (v3 << 16) | (v3 >> (64 - 16));
    v3 ^= v2;
    v0 += v3;
    v3 = (v3 << 21) | (v3 >> (64 - 21));
    v3 ^= v0;
    v2 += v1;
    v1 = (v1 << 17) | (v1 >> (64 - 17));
    v1 ^= v2;
    v2 = (v2 << 32) | (v2 >> (64 - 32));

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_nocase_2(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get the current values
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the siphash operations
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the references with the new values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_nocase_5(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the bit manipulation operations
    v0 += v1;
    v1 = (v1 << 13) | (v1 >> (64 - 13));
    v1 ^= v0;
    v0 = (v0 << 32) | (v0 >> (64 - 32));
    v2 += v3;
    v3 = (v3 << 16) | (v3 >> (64 - 16));
    v3 ^= v2;
    v0 += v3;
    v3 = (v3 << 21) | (v3 >> (64 - 21));
    v3 ^= v0;
    v2 += v1;
    v1 = (v1 << 17) | (v1 >> (64 - 17));
    v1 ^= v2;
    v2 = (v2 << 32) | (v2 >> (64 - 32));

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_nocase_1(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the SipHash operations
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the references with the new values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_nocase_4(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the bit manipulation operations
    v0 += v1;
    v1 = (v1 << 13) | (v1 >> (64 - 13));
    v1 ^= v0;
    v0 = (v0 << 32) | (v0 >> (64 - 32));
    v2 += v3;
    v3 = (v3 << 16) | (v3 >> (64 - 16));
    v3 ^= v2;
    v0 += v3;
    v3 = (v3 << 21) | (v3 >> (64 - 21));
    v3 ^= v0;
    v2 += v1;
    v1 = (v1 << 17) | (v1 >> (64 - 17));
    v1 ^= v2;
    v2 = (v2 << 32) | (v2 >> (64 - 32));

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_helper_siphash_nocase_7_2(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get the current values
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the bitwise operations as in the C code
    v0 += v1;
    v1 = (v1 << 13) | (v1 >> (64 - 13));
    v1 ^= v0;
    v0 = (v0 << 32) | (v0 >> (64 - 32));
    v2 += v3;
    v3 = (v3 << 16) | (v3 >> (64 - 16));
    v3 ^= v2;
    v0 += v3;
    v3 = (v3 << 21) | (v3 >> (64 - 21));
    v3 ^= v0;
    v2 += v1;
    v1 = (v1 << 17) | (v1 >> (64 - 17));
    v1 ^= v2;
    v2 = (v2 << 32) | (v2 >> (64 - 32));

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_helper_siphash_nocase_7_1(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get the current values
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the bitwise operations as in the C code
    v0 += v1;
    v1 = (v1 << 13) | (v1 >> (64 - 13));
    v1 ^= v0;
    v0 = (v0 << 32) | (v0 >> (64 - 32));
    v2 += v3;
    v3 = (v3 << 16) | (v3 >> (64 - 16));
    v3 ^= v2;
    v0 += v3;
    v3 = (v3 << 21) | (v3 >> (64 - 21));
    v3 ^= v0;
    v2 += v1;
    v1 = (v1 << 17) | (v1 >> (64 - 17));
    v1 ^= v2;
    v2 = (v2 << 32) | (v2 >> (64 - 32));

    // Update the references with the new values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_nocase_7(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
    m_ref: &mut u64,
    in_data: &[u8],
    in_idx: usize,
) {
    // Dereference the input references
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;
    let mut m = *m_ref;

    // Convert input bytes to lowercase and construct the 64-bit value
    m = (in_data[0 + in_idx].to_ascii_lowercase() as u64 |
        (in_data[1 + in_idx].to_ascii_lowercase() as u64) << 8 |
        (in_data[2 + in_idx].to_ascii_lowercase() as u64) << 16 |
        (in_data[3 + in_idx].to_ascii_lowercase() as u64) << 24 |
        (in_data[4 + in_idx].to_ascii_lowercase() as u64) << 32 |
        (in_data[5 + in_idx].to_ascii_lowercase() as u64) << 40 |
        (in_data[6 + in_idx].to_ascii_lowercase() as u64) << 48 |
        (in_data[7 + in_idx].to_ascii_lowercase() as u64) << 56);

    v3 ^= m;

    // Call helper functions with mutable references
    {
        helper_helper_siphash_nocase_7_1(&mut v0, &mut v1, &mut v2, &mut v3);
    }
    {
        helper_helper_siphash_nocase_7_2(&mut v0, &mut v1, &mut v2, &mut v3);
    }

    v0 ^= m;

    // Update the output references
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
    *m_ref = m;
}
pub fn siphash_nocase(in_data: &[u8], k: &[u8]) -> u64 {
    let mut in_idx = 0;
    let inlen = in_data.len();
    let mut hash: u64 = 0;
    let out = unsafe { std::slice::from_raw_parts_mut(&mut hash as *mut u64 as *mut u8, 8) };
    
    let mut v0 = 0x736f6d6570736575u64;
    let mut v1 = 0x646f72616e646f6du64;
    let mut v2 = 0x6c7967656e657261u64;
    let mut v3 = 0x7465646279746573u64;
    
    let k0 = u64::from_le_bytes(k[0..8].try_into().unwrap());
    let k1 = u64::from_le_bytes(k[8..16].try_into().unwrap());
    
    let mut m = 0;
    let end = in_data.len() - (inlen % 8);
    let left = inlen & 7;
    let mut b = (inlen as u64) << 56;
    
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;
    
    while in_idx < end {
        helper_siphash_nocase_7(&mut v0, &mut v1, &mut v2, &mut v3, &mut m, in_data, in_idx);
        in_idx += 8;
    }
    
    match left {
        7 => b |= (u64::from(in_data[6 + in_idx].to_ascii_lowercase())) << 48,
        6 => b |= (u64::from(in_data[5 + in_idx].to_ascii_lowercase())) << 40,
        5 => b |= (u64::from(in_data[4 + in_idx].to_ascii_lowercase())) << 32,
        4 => b |= (u64::from(in_data[3 + in_idx].to_ascii_lowercase())) << 24,
        3 => b |= (u64::from(in_data[2 + in_idx].to_ascii_lowercase())) << 16,
        2 => b |= (u64::from(in_data[1 + in_idx].to_ascii_lowercase())) << 8,
        1 => b |= u64::from(in_data[0 + in_idx].to_ascii_lowercase()),
        _ => (),
    }
    
    v3 ^= b;
    helper_siphash_nocase_1(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_nocase_2(&mut v0, &mut v1, &mut v2, &mut v3);
    v0 ^= b;
    v2 ^= 0xff;
    helper_siphash_nocase_3(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_nocase_4(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_nocase_5(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_nocase_6(&mut v0, &mut v1, &mut v2, &mut v3);
    
    let b = (v0 ^ v1) ^ (v2 ^ v3);
    let bytes = b.to_le_bytes();
    out[0..4].copy_from_slice(&bytes[0..4]);
    out[4..8].copy_from_slice(&bytes[4..8]);
    
    hash
}
pub fn helper_siphash_1(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the SipHash round operations
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_2(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the SipHash operations
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_3(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_4(v0_ref: &mut u64, v1_ref: &mut u64, v2_ref: &mut u64, v3_ref: &mut u64) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the SipHash operations
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the references with the new values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_5(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_6(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    // Dereference the input references to get local copies
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    // Perform the bitwise operations as in the C code
    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    // Update the referenced values
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_helper_siphash_7_1(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_helper_siphash_7_2(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
) {
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;

    v0 += v1;
    v1 = v1.rotate_left(13);
    v1 ^= v0;
    v0 = v0.rotate_left(32);
    v2 += v3;
    v3 = v3.rotate_left(16);
    v3 ^= v2;
    v0 += v3;
    v3 = v3.rotate_left(21);
    v3 ^= v0;
    v2 += v1;
    v1 = v1.rotate_left(17);
    v1 ^= v2;
    v2 = v2.rotate_left(32);

    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
}
pub fn helper_siphash_7(
    v0_ref: &mut u64,
    v1_ref: &mut u64,
    v2_ref: &mut u64,
    v3_ref: &mut u64,
    m_ref: &mut u64,
    in_data: &[u8],
    in_idx: usize,
) {
    // Dereference the input references to local variables
    let mut v0 = *v0_ref;
    let mut v1 = *v1_ref;
    let mut v2 = *v2_ref;
    let mut v3 = *v3_ref;
    let mut m = *m_ref;

    // Construct the 64-bit value from the input bytes
    m = u64::from(in_data[0 + in_idx])
        | (u64::from(in_data[1 + in_idx]) << 8)
        | (u64::from(in_data[2 + in_idx]) << 16)
        | (u64::from(in_data[3 + in_idx]) << 24)
        | (u64::from(in_data[4 + in_idx]) << 32)
        | (u64::from(in_data[5 + in_idx]) << 40)
        | (u64::from(in_data[6 + in_idx]) << 48)
        | (u64::from(in_data[7 + in_idx]) << 56);

    v3 ^= m;

    // Call helper functions with mutable references
    helper_helper_siphash_7_1(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_helper_siphash_7_2(&mut v0, &mut v1, &mut v2, &mut v3);

    v0 ^= m;

    // Update the output references
    *v0_ref = v0;
    *v1_ref = v1;
    *v2_ref = v2;
    *v3_ref = v3;
    *m_ref = m;
}
pub fn siphash(in_data: &[u8], k: &[u8]) -> u64 {
    let mut in_idx = 0;
    let mut hash: u64 = 0;
    let out = unsafe { std::slice::from_raw_parts_mut(&mut hash as *mut u64 as *mut u8, 8) };
    
    let mut v0 = 0x736f6d6570736575u64;
    let mut v1 = 0x646f72616e646f6du64;
    let mut v2 = 0x6c7967656e657261u64;
    let mut v3 = 0x7465646279746573u64;
    
    let k0 = u64::from_le_bytes(k[0..8].try_into().unwrap());
    let k1 = u64::from_le_bytes(k[8..16].try_into().unwrap());
    
    let mut m: u64 = 0;
    let inlen = in_data.len();
    let end = in_data.len() - (inlen % 8);
    let left = inlen & 7;
    let mut b = (inlen as u64) << 56;
    
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;
    
    while in_idx < end {
        helper_siphash_7(&mut v0, &mut v1, &mut v2, &mut v3, &mut m, in_data, in_idx);
        in_idx += 8;
    }
    
    match left {
        7 => b |= (in_data[6 + in_idx] as u64) << 48,
        6 => b |= (in_data[5 + in_idx] as u64) << 40,
        5 => b |= (in_data[4 + in_idx] as u64) << 32,
        4 => b |= (in_data[3 + in_idx] as u64) << 24,
        3 => b |= (in_data[2 + in_idx] as u64) << 16,
        2 => b |= (in_data[1 + in_idx] as u64) << 8,
        1 => b |= in_data[0 + in_idx] as u64,
        0 => (),
        _ => unreachable!(), // left can only be 0-7 due to inlen & 7
    }
    
    v3 ^= b;
    helper_siphash_1(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_2(&mut v0, &mut v1, &mut v2, &mut v3);
    v0 ^= b;
    v2 ^= 0xff;
    helper_siphash_3(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_4(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_5(&mut v0, &mut v1, &mut v2, &mut v3);
    helper_siphash_6(&mut v0, &mut v1, &mut v2, &mut v3);
    
    let b = (v0 ^ v1) ^ (v2 ^ v3);
    out[0..4].copy_from_slice(&(b as u32).to_le_bytes());
    out[4..8].copy_from_slice(&((b >> 32) as u32).to_le_bytes());
    
    hash
}
