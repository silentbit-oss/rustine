use crate::*;
use std::convert::TryFrom;
use std::ptr;
use std::time::SystemTime;
use std::time::UNIX_EPOCH;

pub fn rotl(x: u32, shift: u32) -> u32 {
    (x << shift) | (x >> (32 - shift))
}
pub fn read32(p: &[u8], idx32: usize) -> u32 {
    let i = 4 * idx32;
    ((p[i] as u32) |
     ((p[i + 1] as u32) << 8) |
     ((p[i + 2] as u32) << 16) |
     ((p[i + 3] as u32) << 24))
}
pub fn qround(x: &mut [u32; 16], a: usize, b: usize, c: usize, d: usize) {
    x[a] = x[a].wrapping_add(x[b]);
    x[d] = rotl(x[d] ^ x[a], 16);
    x[c] = x[c].wrapping_add(x[d]);
    x[b] = rotl(x[b] ^ x[c], 12);
    x[a] = x[a].wrapping_add(x[b]);
    x[d] = rotl(x[d] ^ x[a], 8);
    x[c] = x[c].wrapping_add(x[d]);
    x[b] = rotl(x[b] ^ x[c], 7);
}
pub fn chacha_block(ctx: &mut MiRandomCtxT) {
    let mut x = [0u32; 16];
    for i in 0..16 {
        x[i] = ctx.input[i];
    }

    for _ in 0..10 {
        qround(&mut x, 0, 4, 8, 12);
        qround(&mut x, 1, 5, 9, 13);
        qround(&mut x, 2, 6, 10, 14);
        qround(&mut x, 3, 7, 11, 15);
        qround(&mut x, 0, 5, 10, 15);
        qround(&mut x, 1, 6, 11, 12);
        qround(&mut x, 2, 7, 8, 13);
        qround(&mut x, 3, 4, 9, 14);
    }

    for i in 0..16 {
        ctx.output[i] = x[i].wrapping_add(ctx.input[i]);
    }

    ctx.output_available = 16;
    ctx.input[12] = ctx.input[12].wrapping_add(1);
    if ctx.input[12] == 0 {
        ctx.input[13] = ctx.input[13].wrapping_add(1);
        if ctx.input[13] == 0 {
            ctx.input[14] = ctx.input[14].wrapping_add(1);
        }
    }
}
pub fn chacha_next32(ctx: &mut MiRandomCtxT) -> u32 {
    if ctx.output_available <= 0 {
        chacha_block(ctx);
        ctx.output_available = 16;
    }
    let x = ctx.output[16 - ctx.output_available as usize];
    ctx.output[16 - ctx.output_available as usize] = 0;
    ctx.output_available -= 1;
    x
}
pub fn mi_random_is_initialized(ctx: Option<&MiRandomCtxT>) -> bool {
    match ctx {
        Some(ctx) => ctx.input[0] != 0,
        None => false,
    }
}
pub fn _mi_random_next(ctx: Option<&mut MiRandomCtxT>) -> u64 {
    // Check if ctx is initialized using the dependency function
    if !mi_random_is_initialized(ctx.as_deref()) {
        _mi_assert_fail("mi_random_is_initialized(ctx)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/random.c", 145, Some("_mi_random_next"));
    }
    
    let ctx = ctx.unwrap(); // Safe to unwrap since we checked initialization
    let mut r: u64;
    
    loop {
        let high = chacha_next32(ctx) as u64;
        let low = chacha_next32(ctx) as u64;
        r = (high << 32) | low;
        if r != 0 {
            break;
        }
    }
    
    r
}

pub fn chacha_init(ctx: &mut MiRandomCtxT, key: &[u8; 32], nonce: u64) {
    // Initialize ctx with zeros (equivalent to memset)
    *ctx = MiRandomCtxT {
        input: [0; 16],
        output: [0; 16],
        output_available: 0,
        weak: false,
    };
    
    let sigma = b"expand 32-byte k";
    
    for i in 0..4 {
        ctx.input[i] = read32(sigma, i);
    }
    
    for i in 0..8 {
        ctx.input[i + 4] = read32(key, i);
    }
    
    ctx.input[12] = 0;
    ctx.input[13] = 0;
    ctx.input[14] = nonce as u32;
    ctx.input[15] = (nonce >> 32) as u32;
}
pub fn _mi_os_random_weak(extra_seed: u64) -> u64 {
    let mut x = (_mi_os_random_weak as *const () as u64) ^ extra_seed;
    x ^= _mi_prim_clock_now();
    let max = ((x ^ (x >> 17)) & 0x0F) + 1;
    
    for i in 0.. {
        x = _mi_random_shuffle(x);
        if i >= max && x != 0 {
            break;
        }
        x = x.wrapping_add(1);
    }

    if x == 0 {
        _mi_assert_fail("x != 0", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/random.c", 173, Some("_mi_os_random_weak"));
    }
    
    x
}

fn _mi_prim_clock_now() -> u64 {
    SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .unwrap()
        .as_nanos() as u64
}
pub fn mi_random_init_ex(ctx: &mut MiRandomCtxT, use_weak: bool) {
    let mut key = [0u8; 32];
    
    if use_weak || !_mi_prim_random_buf(&mut key) {
        if !use_weak {
            _mi_warning_message(c"unable to use secure randomness\n");
        }
        
        let mut x = _mi_os_random_weak(0);
        for i in 0..8 {
            x = _mi_random_shuffle(x);
            let bytes = x.to_le_bytes();
            key[i * 4] = bytes[0];
            key[i * 4 + 1] = bytes[1];
            key[i * 4 + 2] = bytes[2];
            key[i * 4 + 3] = bytes[3];
            x = x.wrapping_add(1);
        }
        
        ctx.weak = true;
    } else {
        ctx.weak = false;
    }
    
    chacha_init(ctx, &key, ctx as *const _ as u64);
}
pub fn _mi_random_init(ctx: &mut MiRandomCtxT) {
    mi_random_init_ex(ctx, false);
}

pub fn chacha_split(ctx: &mut MiRandomCtxT, nonce: u64, ctx_new: &mut MiRandomCtxT) {
    // Initialize ctx_new to zeros (equivalent to memset)
    *ctx_new = MiRandomCtxT {
        input: [0; 16],
        output: [0; 16],
        output_available: 0,
        weak: false,
    };
    
    // Copy input from ctx to ctx_new (equivalent to _mi_memcpy)
    ctx_new.input.copy_from_slice(&ctx.input);
    
    // Set specific input values
    ctx_new.input[12] = 0;
    ctx_new.input[13] = 0;
    ctx_new.input[14] = nonce as u32;
    ctx_new.input[15] = (nonce >> 32) as u32;
    
    // Assert condition
    assert!(
        ctx.input[14] != ctx_new.input[14] || ctx.input[15] != ctx_new.input[15],
        "ctx->input[14] != ctx_new->input[14] || ctx->input[15] != ctx_new->input[15]"
    );
    
    // Call chacha_block
    chacha_block(ctx_new);
}
pub fn _mi_random_split(ctx: &mut MiRandomCtxT, ctx_new: &mut MiRandomCtxT) {
    if !mi_random_is_initialized(Some(ctx)) {
        _mi_assert_fail("mi_random_is_initialized(ctx)", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/random.c", 139, Some("_mi_random_split"));
    }
    if ctx as *const _ == ctx_new as *const _ {
        _mi_assert_fail("ctx != ctx_new", "/workdir/C2RustTranslation-main/subjects/mimalloc/src/random.c", 140, Some("_mi_random_split"));
    }
    chacha_split(ctx, ctx_new as *const _ as u64, ctx_new);
}
pub fn _mi_random_reinit_if_weak(ctx: &mut MiRandomCtxT) {
    if ctx.weak {
        _mi_random_init(ctx);
    }
}
pub fn _mi_random_init_weak(ctx: &mut MiRandomCtxT) {
    mi_random_init_ex(ctx, true);
}
