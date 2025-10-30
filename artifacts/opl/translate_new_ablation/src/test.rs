use OplEmuEnvelopeState::*;
use crate::*;
use crate::Op2FlagsT::OP2_DOUBLEVOICE;
use crate::opl_emu_envelope_state::OplEmuEnvelopeState;
use crate::opl_emu_opdata_cache::OplEmuOpdataCache;
use lazy_static::lazy_static;
use rand::Rng;
use std::ffi::CStr;
use std::ffi::CString;
use std::fmt::Write;
use std::fs::File;
use std::io::Read;
use std::io::Result as IoResult;
use std::io::Seek;
use std::io::SeekFrom;
use std::os::raw::c_char;
use std::path::Path;
use std::println;
use std::ptr;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
pub fn opl_emu_bitfield(value: u32, start: i32, length: i32) -> u32 {
    (value >> start) & ((1 << length) - 1)
}
pub fn opl_emu_clamp(value: i32, minval: i32, maxval: i32) -> i32 {
    if value < minval {
        minval
    } else if value > maxval {
        maxval
    } else {
        value
    }
}
pub fn opl_emu_registers_operator_list(o1: u8, o2: u8, o3: u8, o4: u8) -> u32 {
    ((o1 as u32) | ((o2 as u32) << 8) | ((o3 as u32) << 16) | ((o4 as u32) << 24))
}
pub fn opl_emu_registers_effective_rate(rawrate: u32, ksr: u32) -> u32 {
    if rawrate == 0 {
        0
    } else {
        (rawrate + ksr).min(63)
    }
}
pub fn opl_emu_registers_channel_offset(chnum: u32) -> u32 {
    (chnum % 9) + (0x100 * (chnum / 9))
}
pub fn opl_emu_registers_operator_offset(opnum: u32) -> u32 {
    ((opnum % 18) + (2 * ((opnum % 18) / 6))) + (0x100 * (opnum / 18))
}
pub fn opl_emu_opl_key_scale_atten(block: u32, fnum_4msb: u32) -> u32 {
    const FNUM_TO_ATTEN: [u8; 16] = [0, 24, 32, 37, 40, 43, 45, 47, 48, 50, 51, 52, 53, 54, 55, 56];
    let result = i32::from(FNUM_TO_ATTEN[fnum_4msb as usize]) - (8 * (block ^ 7)) as i32;
    if result < 0 {
        0
    } else {
        result as u32
    }
}
pub fn opl_emu_attenuation_to_volume(input: u32) -> u32 {
    static S_POWER_TABLE: [u16; 256] = [
        (0x3fa | 0x400) << 2,
        (0x3f5 | 0x400) << 2,
        (0x3ef | 0x400) << 2,
        (0x3ea | 0x400) << 2,
        (0x3e4 | 0x400) << 2,
        (0x3df | 0x400) << 2,
        (0x3da | 0x400) << 2,
        (0x3d4 | 0x400) << 2,
        (0x3cf | 0x400) << 2,
        (0x3c9 | 0x400) << 2,
        (0x3c4 | 0x400) << 2,
        (0x3bf | 0x400) << 2,
        (0x3b9 | 0x400) << 2,
        (0x3b4 | 0x400) << 2,
        (0x3ae | 0x400) << 2,
        (0x3a9 | 0x400) << 2,
        (0x3a4 | 0x400) << 2,
        (0x39f | 0x400) << 2,
        (0x399 | 0x400) << 2,
        (0x394 | 0x400) << 2,
        (0x38f | 0x400) << 2,
        (0x38a | 0x400) << 2,
        (0x384 | 0x400) << 2,
        (0x37f | 0x400) << 2,
        (0x37a | 0x400) << 2,
        (0x375 | 0x400) << 2,
        (0x370 | 0x400) << 2,
        (0x36a | 0x400) << 2,
        (0x365 | 0x400) << 2,
        (0x360 | 0x400) << 2,
        (0x35b | 0x400) << 2,
        (0x356 | 0x400) << 2,
        (0x351 | 0x400) << 2,
        (0x34c | 0x400) << 2,
        (0x347 | 0x400) << 2,
        (0x342 | 0x400) << 2,
        (0x33d | 0x400) << 2,
        (0x338 | 0x400) << 2,
        (0x333 | 0x400) << 2,
        (0x32e | 0x400) << 2,
        (0x329 | 0x400) << 2,
        (0x324 | 0x400) << 2,
        (0x31f | 0x400) << 2,
        (0x31a | 0x400) << 2,
        (0x315 | 0x400) << 2,
        (0x310 | 0x400) << 2,
        (0x30b | 0x400) << 2,
        (0x306 | 0x400) << 2,
        (0x302 | 0x400) << 2,
        (0x2fd | 0x400) << 2,
        (0x2f8 | 0x400) << 2,
        (0x2f3 | 0x400) << 2,
        (0x2ee | 0x400) << 2,
        (0x2e9 | 0x400) << 2,
        (0x2e5 | 0x400) << 2,
        (0x2e0 | 0x400) << 2,
        (0x2db | 0x400) << 2,
        (0x2d6 | 0x400) << 2,
        (0x2d2 | 0x400) << 2,
        (0x2cd | 0x400) << 2,
        (0x2c8 | 0x400) << 2,
        (0x2c4 | 0x400) << 2,
        (0x2bf | 0x400) << 2,
        (0x2ba | 0x400) << 2,
        (0x2b5 | 0x400) << 2,
        (0x2b1 | 0x400) << 2,
        (0x2ac | 0x400) << 2,
        (0x2a8 | 0x400) << 2,
        (0x2a3 | 0x400) << 2,
        (0x29e | 0x400) << 2,
        (0x29a | 0x400) << 2,
        (0x295 | 0x400) << 2,
        (0x291 | 0x400) << 2,
        (0x28c | 0x400) << 2,
        (0x288 | 0x400) << 2,
        (0x283 | 0x400) << 2,
        (0x27f | 0x400) << 2,
        (0x27a | 0x400) << 2,
        (0x276 | 0x400) << 2,
        (0x271 | 0x400) << 2,
        (0x26d | 0x400) << 2,
        (0x268 | 0x400) << 2,
        (0x264 | 0x400) << 2,
        (0x25f | 0x400) << 2,
        (0x25b | 0x400) << 2,
        (0x257 | 0x400) << 2,
        (0x252 | 0x400) << 2,
        (0x24e | 0x400) << 2,
        (0x249 | 0x400) << 2,
        (0x245 | 0x400) << 2,
        (0x241 | 0x400) << 2,
        (0x23c | 0x400) << 2,
        (0x238 | 0x400) << 2,
        (0x234 | 0x400) << 2,
        (0x230 | 0x400) << 2,
        (0x22b | 0x400) << 2,
        (0x227 | 0x400) << 2,
        (0x223 | 0x400) << 2,
        (0x21e | 0x400) << 2,
        (0x21a | 0x400) << 2,
        (0x216 | 0x400) << 2,
        (0x212 | 0x400) << 2,
        (0x20e | 0x400) << 2,
        (0x209 | 0x400) << 2,
        (0x205 | 0x400) << 2,
        (0x201 | 0x400) << 2,
        (0x1fd | 0x400) << 2,
        (0x1f9 | 0x400) << 2,
        (0x1f5 | 0x400) << 2,
        (0x1f0 | 0x400) << 2,
        (0x1ec | 0x400) << 2,
        (0x1e8 | 0x400) << 2,
        (0x1e4 | 0x400) << 2,
        (0x1e0 | 0x400) << 2,
        (0x1dc | 0x400) << 2,
        (0x1d8 | 0x400) << 2,
        (0x1d4 | 0x400) << 2,
        (0x1d0 | 0x400) << 2,
        (0x1cc | 0x400) << 2,
        (0x1c8 | 0x400) << 2,
        (0x1c4 | 0x400) << 2,
        (0x1c0 | 0x400) << 2,
        (0x1bc | 0x400) << 2,
        (0x1b8 | 0x400) << 2,
        (0x1b4 | 0x400) << 2,
        (0x1b0 | 0x400) << 2,
        (0x1ac | 0x400) << 2,
        (0x1a8 | 0x400) << 2,
        (0x1a4 | 0x400) << 2,
        (0x1a0 | 0x400) << 2,
        (0x19c | 0x400) << 2,
        (0x199 | 0x400) << 2,
        (0x195 | 0x400) << 2,
        (0x191 | 0x400) << 2,
        (0x18d | 0x400) << 2,
        (0x189 | 0x400) << 2,
        (0x185 | 0x400) << 2,
        (0x181 | 0x400) << 2,
        (0x17e | 0x400) << 2,
        (0x17a | 0x400) << 2,
        (0x176 | 0x400) << 2,
        (0x172 | 0x400) << 2,
        (0x16f | 0x400) << 2,
        (0x16b | 0x400) << 2,
        (0x167 | 0x400) << 2,
        (0x163 | 0x400) << 2,
        (0x160 | 0x400) << 2,
        (0x15c | 0x400) << 2,
        (0x158 | 0x400) << 2,
        (0x154 | 0x400) << 2,
        (0x151 | 0x400) << 2,
        (0x14d | 0x400) << 2,
        (0x149 | 0x400) << 2,
        (0x146 | 0x400) << 2,
        (0x142 | 0x400) << 2,
        (0x13e | 0x400) << 2,
        (0x13b | 0x400) << 2,
        (0x137 | 0x400) << 2,
        (0x134 | 0x400) << 2,
        (0x130 | 0x400) << 2,
        (0x12c | 0x400) << 2,
        (0x129 | 0x400) << 2,
        (0x125 | 0x400) << 2,
        (0x122 | 0x400) << 2,
        (0x11e | 0x400) << 2,
        (0x11b | 0x400) << 2,
        (0x117 | 0x400) << 2,
        (0x114 | 0x400) << 2,
        (0x110 | 0x400) << 2,
        (0x10c | 0x400) << 2,
        (0x109 | 0x400) << 2,
        (0x106 | 0x400) << 2,
        (0x102 | 0x400) << 2,
        (0x0ff | 0x400) << 2,
        (0x0fb | 0x400) << 2,
        (0x0f8 | 0x400) << 2,
        (0x0f4 | 0x400) << 2,
        (0x0f1 | 0x400) << 2,
        (0x0ed | 0x400) << 2,
        (0x0ea | 0x400) << 2,
        (0x0e7 | 0x400) << 2,
        (0x0e3 | 0x400) << 2,
        (0x0e0 | 0x400) << 2,
        (0x0dc | 0x400) << 2,
        (0x0d9 | 0x400) << 2,
        (0x0d6 | 0x400) << 2,
        (0x0d2 | 0x400) << 2,
        (0x0cf | 0x400) << 2,
        (0x0cc | 0x400) << 2,
        (0x0c8 | 0x400) << 2,
        (0x0c5 | 0x400) << 2,
        (0x0c2 | 0x400) << 2,
        (0x0be | 0x400) << 2,
        (0x0bb | 0x400) << 2,
        (0x0b8 | 0x400) << 2,
        (0x0b5 | 0x400) << 2,
        (0x0b1 | 0x400) << 2,
        (0x0ae | 0x400) << 2,
        (0x0ab | 0x400) << 2,
        (0x0a8 | 0x400) << 2,
        (0x0a4 | 0x400) << 2,
        (0x0a1 | 0x400) << 2,
        (0x09e | 0x400) << 2,
        (0x09b | 0x400) << 2,
        (0x098 | 0x400) << 2,
        (0x094 | 0x400) << 2,
        (0x091 | 0x400) << 2,
        (0x08e | 0x400) << 2,
        (0x08b | 0x400) << 2,
        (0x088 | 0x400) << 2,
        (0x085 | 0x400) << 2,
        (0x082 | 0x400) << 2,
        (0x07e | 0x400) << 2,
        (0x07b | 0x400) << 2,
        (0x078 | 0x400) << 2,
        (0x075 | 0x400) << 2,
        (0x072 | 0x400) << 2,
        (0x06f | 0x400) << 2,
        (0x06c | 0x400) << 2,
        (0x069 | 0x400) << 2,
        (0x066 | 0x400) << 2,
        (0x063 | 0x400) << 2,
        (0x060 | 0x400) << 2,
        (0x05d | 0x400) << 2,
        (0x05a | 0x400) << 2,
        (0x057 | 0x400) << 2,
        (0x054 | 0x400) << 2,
        (0x051 | 0x400) << 2,
        (0x04e | 0x400) << 2,
        (0x04b | 0x400) << 2,
        (0x048 | 0x400) << 2,
        (0x045 | 0x400) << 2,
        (0x042 | 0x400) << 2,
        (0x03f | 0x400) << 2,
        (0x03c | 0x400) << 2,
        (0x039 | 0x400) << 2,
        (0x036 | 0x400) << 2,
        (0x033 | 0x400) << 2,
        (0x030 | 0x400) << 2,
        (0x02d | 0x400) << 2,
        (0x02a | 0x400) << 2,
        (0x028 | 0x400) << 2,
        (0x025 | 0x400) << 2,
        (0x022 | 0x400) << 2,
        (0x01f | 0x400) << 2,
        (0x01c | 0x400) << 2,
        (0x019 | 0x400) << 2,
        (0x016 | 0x400) << 2,
        (0x014 | 0x400) << 2,
        (0x011 | 0x400) << 2,
        (0x00e | 0x400) << 2,
        (0x00b | 0x400) << 2,
        (0x008 | 0x400) << 2,
        (0x006 | 0x400) << 2,
        (0x003 | 0x400) << 2,
        (0x000 | 0x400) << 2,
    ];

    S_POWER_TABLE[(input & 0xff) as usize] as u32 >> (input >> 8)
}
pub fn calc_vol(regbyte: &mut u8, volume: i32) {
    let mut level = !(*regbyte) as i32;  // Invert bits and cast to signed for calculations
    level &= 0x3f;  // Mask to 6 bits
    
    level = (level * volume) / 127;  // Scale by volume
    
    // Clamp between 0 and 0x3f
    level = level.clamp(0, 0x3f);
    
    level = !level;  // Invert bits again
    level &= 0x3f;  // Final mask
    
    *regbyte &= 0xC0;  // Clear lower 6 bits
    *regbyte |= level as u8;  // Set new level
}
pub fn test_min_max_macros() -> i32 {
    // Test opl_min(1, 2) == 1
    if (if 1 < 2 { 1 } else { 2 }) != 1 {
        println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                 "opl_min(1, 2)", "1", 
                 if 1 < 2 { 1 } else { 2 }, 1, 
                 "/c2rust_final/subjects/opl/test.c", 175);
        return 1;
    }

    // Test opl_min(3, 2) == 2
    if (if 3 < 2 { 3 } else { 2 }) != 2 {
        println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                 "opl_min(3, 2)", "2", 
                 if 3 < 2 { 3 } else { 2 }, 2, 
                 "/c2rust_final/subjects/opl/test.c", 176);
        return 1;
    }

    // Test opl_max(1, 2) == 2
    if (if 1 > 2 { 1 } else { 2 }) != 2 {
        println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                 "opl_max(1, 2)", "2", 
                 if 1 > 2 { 1 } else { 2 }, 2, 
                 "/c2rust_final/subjects/opl/test.c", 177);
        return 1;
    }

    // Test opl_max(3, 2) == 3
    if (if 3 > 2 { 3 } else { 2 }) != 3 {
        println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                 "opl_max(3, 2)", "3", 
                 if 3 > 2 { 3 } else { 2 }, 3, 
                 "/c2rust_final/subjects/opl/test.c", 178);
        return 1;
    }

    0
}
pub fn opl_midi_changeprog(opl: &mut OplT, channel: i32, program: u8) {
    if channel == 9 {
        return;
    }
    opl.channelprog[channel as usize] = program;
}
pub fn opl_emu_registers_reset(regs: &mut OplEmuRegisters) {
    for i in 0..0x200 {
        regs.m_regdata[i] = 0;
    }
}
pub fn opl_emu_registers_reset_lfo(regs: &mut OplEmuRegisters) {
    regs.m_lfo_pm_counter = 0;
    regs.m_lfo_am_counter = 0;
}
pub fn opl_emu_registers_lfo_am_offset(regs: &OplEmuRegisters, _choffs: u32) -> u32 {
    regs.m_lfo_am as u32
}
pub fn opl_emu_registers_noise_state(regs: &OplEmuRegisters) -> u32 {
    regs.m_noise_lfsr >> 23
}
pub fn opl_emu_fm_operator_reset(fmop: &mut OplEmuFmOperator) {
    fmop.m_phase = 0;
    fmop.m_env_attenuation = 0x3ff;
    fmop.m_env_state = OplEmuEnvelopeState::OPL_EMU_EG_RELEASE;
    fmop.m_key_state = 0;
    fmop.m_keyon_live = 0;
}
pub fn opl_emu_fm_operator_opoffs(fmop: &OplEmuFmOperator) -> u32 {
    fmop.m_opoffs
}
pub fn opl_emu_fm_operator_choffs(fmop: &OplEmuFmOperator) -> u32 {
    fmop.m_choffs
}
pub fn opl_emu_fm_operator_set_choffs(fmop: &mut OplEmuFmOperator, choffs: u32) {
    fmop.m_choffs = choffs;
}
pub fn opl_emu_fm_operator_phase(fmop: &OplEmuFmOperator) -> u32 {
    fmop.m_phase >> 10
}
pub fn opl_emu_fm_operator_start_attack(fmop: &mut OplEmuFmOperator) {
    if fmop.m_env_state == OplEmuEnvelopeState::OPL_EMU_EG_ATTACK {
        return;
    }
    fmop.m_env_state = OplEmuEnvelopeState::OPL_EMU_EG_ATTACK;
    fmop.m_phase = 0;
    if fmop.m_cache.eg_rate[OplEmuEnvelopeState::OPL_EMU_EG_ATTACK as usize] >= 62 {
        fmop.m_env_attenuation = 0;
    }
}
pub fn opl_emu_fm_operator_start_release(fmop: &mut OplEmuFmOperator) {
    if (fmop.m_env_state as u8) >= (OplEmuEnvelopeState::OPL_EMU_EG_RELEASE as u8) {
        return;
    }
    fmop.m_env_state = OplEmuEnvelopeState::OPL_EMU_EG_RELEASE;
}
pub fn opl_emu_fm_channel_reset(fmch: &mut OplEmuFmChannel) {
    fmch.m_feedback[1] = 0;
    fmch.m_feedback[0] = 0;
    fmch.m_feedback_in = 0;
}
pub fn opl_emu_fm_channel_choffs(fmch: &OplEmuFmChannel) -> u32 {
    fmch.m_choffs
}
pub fn opl_emu_fm_channel_is4op(fmch: &OplEmuFmChannel) -> bool {
    fmch.m_op[2].is_some()
}

lazy_static! {
    static ref S_SIN_TABLE: [u16; 256] = [
        0x859, 0x6c3, 0x607, 0x58b, 0x52e, 0x4e4, 0x4a6, 0x471, 0x443, 0x41a, 0x3f5, 0x3d3, 0x3b5, 0x398, 0x37e, 0x365,
        0x34e, 0x339, 0x324, 0x311, 0x2ff, 0x2ed, 0x2dc, 0x2cd, 0x2bd, 0x2af, 0x2a0, 0x293, 0x286, 0x279, 0x26d, 0x261,
        0x256, 0x24b, 0x240, 0x236, 0x22c, 0x222, 0x218, 0x20f, 0x206, 0x1fd, 0x1f5, 0x1ec, 0x1e4, 0x1dc, 0x1d4, 0x1cd,
        0x1c5, 0x1be, 0x1b7, 0x1b0, 0x1a9, 0x1a2, 0x19b, 0x195, 0x18f, 0x188, 0x182, 0x17c, 0x177, 0x171, 0x16b, 0x166,
        0x160, 0x15b, 0x155, 0x150, 0x14b, 0x146, 0x141, 0x13c, 0x137, 0x133, 0x12e, 0x129, 0x125, 0x121, 0x11c, 0x118,
        0x114, 0x10f, 0x10b, 0x107, 0x103, 0x0ff, 0x0fb, 0x0f8, 0x0f4, 0x0f0, 0x0ec, 0x0e9, 0x0e5, 0x0e2, 0x0de, 0x0db,
        0x0d7, 0x0d4, 0x0d1, 0x0cd, 0x0ca, 0x0c7, 0x0c4, 0x0c1, 0x0be, 0x0bb, 0x0b8, 0x0b5, 0x0b2, 0x0af, 0x0ac, 0x0a9,
        0x0a7, 0x0a4, 0x0a1, 0x09f, 0x09c, 0x099, 0x097, 0x094, 0x092, 0x08f, 0x08d, 0x08a, 0x088, 0x086, 0x083, 0x081,
        0x07f, 0x07d, 0x07a, 0x078, 0x076, 0x074, 0x072, 0x070, 0x06e, 0x06c, 0x06a, 0x068, 0x066, 0x064, 0x062, 0x060,
        0x05e, 0x05c, 0x05b, 0x059, 0x057, 0x055, 0x053, 0x052, 0x050, 0x04e, 0x04d, 0x04b, 0x04a, 0x048, 0x046, 0x045,
        0x043, 0x042, 0x040, 0x03f, 0x03e, 0x03c, 0x03b, 0x039, 0x038, 0x037, 0x035, 0x034, 0x033, 0x031, 0x030, 0x02f,
        0x02e, 0x02d, 0x02b, 0x02a, 0x029, 0x028, 0x027, 0x026, 0x025, 0x024, 0x023, 0x022, 0x021, 0x020, 0x01f, 0x01e,
        0x01d, 0x01c, 0x01b, 0x01a, 0x019, 0x018, 0x017, 0x017, 0x016, 0x015, 0x014, 0x014, 0x013, 0x012, 0x011, 0x011,
        0x010, 0x00f, 0x00f, 0x00e, 0x00d, 0x00d, 0x00c, 0x00c, 0x00b, 0x00a, 0x00a, 0x009, 0x009, 0x008, 0x008, 0x007,
        0x007, 0x007, 0x006, 0x006, 0x005, 0x005, 0x005, 0x004, 0x004, 0x004, 0x003, 0x003, 0x003, 0x002, 0x002, 0x002,
        0x002, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
    ];
}

pub fn opl_emu_abs_sin_attenuation(input: u32) -> u32 {
    let mut processed_input = input;
    if opl_emu_bitfield(input, 8, 1) != 0 {
        processed_input = !input;
    }
    S_SIN_TABLE[(processed_input & 0xff) as usize] as u32
}
pub fn opl_emu_attenuation_increment(rate: u32, index: u32) -> u32 {
    static S_INCREMENT_TABLE: [u32; 64] = [
        0x00000000, 0x00000000, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x11101110, 0x11101110,
        0x10101010, 0x10111010, 0x11101110, 0x11111110, 0x10101010, 0x10111010, 0x11101110, 0x11111110,
        0x10101010, 0x10111010, 0x11101110, 0x11111110, 0x10101010, 0x10111010, 0x11101110, 0x11111110,
        0x10101010, 0x10111010, 0x11101110, 0x11111110, 0x10101010, 0x10111010, 0x11101110, 0x11111110,
        0x10101010, 0x10111010, 0x11101110, 0x11111110, 0x10101010, 0x10111010, 0x11101110, 0x11111110,
        0x10101010, 0x10111010, 0x11101110, 0x11111110, 0x10101010, 0x10111010, 0x11101110, 0x11111110,
        0x11111111, 0x21112111, 0x21212121, 0x22212221, 0x22222222, 0x42224222, 0x42424242, 0x44424442,
        0x44444444, 0x84448444, 0x84848484, 0x88848884, 0x88888888, 0x88888888, 0x88888888, 0x88888888
    ];

    opl_emu_bitfield(S_INCREMENT_TABLE[rate as usize], (4 * index) as i32, 4)
}
pub fn opl_emu_opl_clock_noise_and_lfo(
    noise_lfsr: &mut u32,
    lfo_am_counter: &mut [u16; 1],
    lfo_pm_counter: &mut [u16; 1],
    lfo_am: &mut u8,
    am_depth: u32,
    pm_depth: u32
) -> i32 {
    *noise_lfsr <<= 1;
    *noise_lfsr |= ((opl_emu_bitfield(*noise_lfsr, 23, 1) ^ opl_emu_bitfield(*noise_lfsr, 9, 1)) ^ opl_emu_bitfield(*noise_lfsr, 8, 1)) ^ opl_emu_bitfield(*noise_lfsr, 1, 1);
    
    let mut am_counter = lfo_am_counter[0];
    am_counter = am_counter.wrapping_add(1);
    if am_counter >= ((210 * 64) - 1) {
        lfo_am_counter[0] = 0;
    } else {
        lfo_am_counter[0] = am_counter;
    }
    
    let shift = 9 - (2 * am_depth) as i32;
    *lfo_am = ((if am_counter < (105 * 64) { am_counter } else { ((210 * 64) + 63) - am_counter }) >> shift) as u8;
    
    let mut pm_counter = lfo_pm_counter[0];
    pm_counter = pm_counter.wrapping_add(1);
    lfo_pm_counter[0] = pm_counter;
    
    static PM_SCALE: [i8; 8] = [8, 4, 0, -4, -8, -4, 0, 4];
    (PM_SCALE[opl_emu_bitfield(pm_counter as u32, 10, 3) as usize] as i32) >> (pm_depth ^ 1) as i32
}
pub fn opl_emu_opl_compute_phase_step(block_freq: u32, multiple: u32, lfo_raw_pm: i32) -> u32 {
    let mut fnum = opl_emu_bitfield(block_freq, 0, 10) << 2;
    fnum = fnum.wrapping_add((((lfo_raw_pm as i64 * opl_emu_bitfield(block_freq, 7, 3) as i64) >> 1) as i32) as u32);
    fnum &= 0xfff;
    let block = opl_emu_bitfield(block_freq, 10, 3);
    let phase_step = (fnum << block) >> 2;
    (phase_step * multiple) >> 1
}
pub fn getinstrument(opl: &OplT, channel: i32, note: i32) -> Option<i32> {
    if note < 0 || note > 127 || channel > 15 {
        return None;
    }

    if channel == 9 {
        if opl.is_op2 != 0 {
            Some((128 + note) - 35)
        } else {
            Some(128 | note)
        }
    } else {
        Some(opl.channelprog[channel as usize] as i32)
    }
}
pub fn test_clamp_function() -> i32 {
    {
        let result = opl_emu_clamp(5, 0, 10);
        if result != 5 {
            println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                     "opl_emu_clamp(5, 0, 10)", "5", result, 5, 
                     "/c2rust_final/subjects/opl/test.c", 168);
            return 1;
        }
    }
    {
        let result = opl_emu_clamp(-1, 0, 10);
        if result != 0 {
            println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                     "opl_emu_clamp(-1, 0, 10)", "0", result, 0, 
                     "/c2rust_final/subjects/opl/test.c", 169);
            return 1;
        }
    }
    {
        let result = opl_emu_clamp(15, 0, 10);
        if result != 10 {
            println!("Assertion failed: {} == {} ({} != {}) at {}:{}", 
                     "opl_emu_clamp(15, 0, 10)", "10", result, 10, 
                     "/c2rust_final/subjects/opl/test.c", 170);
            return 1;
        }
    }
    0
}
pub fn helper_opl_loadbank_internal_1(
    i_ref: &mut i32,
    opl: &mut OplT,
    buff: &mut [u8; 16],
    f: &mut impl Read,
) -> IoResult<()> {
    let i = *i_ref as usize;
    
    // Read exactly 16 bytes into the buffer
    f.read_exact(buff)?;

    // Process modulator_e862 (note lowercase)
    opl.opl_gmtimbres[i].modulator_e862 = u32::from(buff[8]) << 24
        | u32::from(buff[6]) << 16
        | u32::from(buff[4]) << 8
        | u32::from(buff[0]);

    // Process carrier_e862 (note lowercase)
    opl.opl_gmtimbres[i].carrier_e862 = u32::from(buff[9]) << 24
        | u32::from(buff[7]) << 16
        | u32::from(buff[5]) << 8
        | u32::from(buff[1]);

    // Set remaining fields
    opl.opl_gmtimbres[i].modulator_40 = buff[2];
    opl.opl_gmtimbres[i].carrier_40 = buff[3];
    opl.opl_gmtimbres[i].feedconn = buff[10];
    opl.opl_gmtimbres[i].finetune = buff[12] as i8;  // Convert u8 to i8
    opl.opl_gmtimbres[i].notenum = 60;
    opl.opl_gmtimbres[i].noteoffset = 0;

    Ok(())
}

pub fn opl_emu_registers_write(
    regs: &mut OplEmuRegisters,
    index: u16,
    data: u8,
    channel: &mut Option<u32>,
    opmask: &mut Option<u32>,
) -> i32 {
    // Handle register write based on index
    if index == 0x04 && opl_emu_bitfield(data as u32, 7, 1) != 0 {
        regs.m_regdata[index as usize] |= 0x80;
    } else {
        regs.m_regdata[index as usize] = data;
    }

    // Handle special cases
    if index == 0xbd {
        *channel = Some(0xff);
        *opmask = if opl_emu_bitfield(data as u32, 5, 1) != 0 {
            Some(opl_emu_bitfield(data as u32, 0, 5))
        } else {
            Some(0)
        };
        return 1;
    }

    if (index & 0xf0) == 0xb0 {
        let mut ch = index & 0x0f;
        if ch < 9 {
            ch += 9 * opl_emu_bitfield(index as u32, 8, 1) as u16;
            *channel = Some(ch as u32);
            *opmask = if opl_emu_bitfield(data as u32, 5, 1) != 0 {
                Some(15)
            } else {
                Some(0)
            };
            return 1;
        }
    }

    0
}
pub fn opl_emu_fm_operator_keyonoff(fmop: &mut OplEmuFmOperator, on: u32, type_: OplEmuKeyonType) {
    let type_int = type_ as i32;
    let mask = !(1 << type_int);
    let new_bit = opl_emu_bitfield(on, 0, 1) << type_int;
    fmop.m_keyon_live = (fmop.m_keyon_live & mask) | new_bit as u8;
}
pub fn opl_emu_fm_channel_keyonoff(
    fmch: &mut OplEmuFmChannel,
    states: u32,
    type_: OplEmuKeyonType,
    chnum: u32,
) {
    for opnum in 0..fmch.m_op.len() {
        if let Some(ref mut fmop) = fmch.m_op[opnum] {
            let on = opl_emu_bitfield(states, opnum as i32, 1);
            opl_emu_fm_operator_keyonoff(fmop.as_mut(), on, type_);
        }
    }
}
pub fn opl_emu_write(emu: &mut OplEmuT, regnum: u16, data: u8) {
    if regnum == 0x04 {
        return;
    }
    
    emu.m_modified_channels = (1 << 18) - 1;
    
    let mut keyon_channel: Option<u32> = None;
    let mut keyon_opmask: Option<u32> = None;
    
    if opl_emu_registers_write(&mut emu.m_regs, regnum, data, &mut keyon_channel, &mut keyon_opmask) != 0 {
        if let Some(channel) = keyon_channel {
            if channel < 18 {
                opl_emu_fm_channel_keyonoff(
                    &mut emu.m_channel[channel as usize],
                    keyon_opmask.unwrap_or(0),
                    OplEmuKeyonType::OPL_EMU_KEYON_NORMAL,
                    channel,
                );
            } else if 18 >= 9 && channel == 0xff {
                opl_emu_fm_channel_keyonoff(
                    &mut emu.m_channel[6],
                    if opl_emu_bitfield(keyon_opmask.unwrap_or(0), 4, 1) != 0 { 3 } else { 0 },
                    OplEmuKeyonType::OPL_EMU_KEYON_RHYTHM,
                    6,
                );
                opl_emu_fm_channel_keyonoff(
                    &mut emu.m_channel[7],
                    opl_emu_bitfield(keyon_opmask.unwrap_or(0), 0, 1) | (opl_emu_bitfield(keyon_opmask.unwrap_or(0), 3, 1) << 1),
                    OplEmuKeyonType::OPL_EMU_KEYON_RHYTHM,
                    7,
                );
                opl_emu_fm_channel_keyonoff(
                    &mut emu.m_channel[8],
                    opl_emu_bitfield(keyon_opmask.unwrap_or(0), 2, 1) | (opl_emu_bitfield(keyon_opmask.unwrap_or(0), 1, 1) << 1),
                    OplEmuKeyonType::OPL_EMU_KEYON_RHYTHM,
                    8,
                );
            }
        }
    }
}
pub fn oplregwr(opl: &mut OplT, reg: u16, data: u8) {
    opl_emu_write(&mut opl.opl_emu, reg, data);
}
pub fn voicevolume(opl: &mut OplT, voice: u16, timbre: &OplTimbreT, volume: i32) {
    let mut carrierval = timbre.carrier_40;
    
    if volume == 0 {
        carrierval |= 0x3f;
    } else {
        calc_vol(&mut carrierval, volume);
    }
    
    oplregwr(opl, 0x40 + OP2OFFSETS[voice as usize], carrierval);
}
pub fn opl_noteon(opl: &mut OplT, voice: u16, note: u32, pitch: i32) {
    let mut freq = FREQTABLE[note as usize] as u32;
    let mut octave = OCTAVETABLE[note as usize] as u32;

    if pitch != 0 {
        let pitch = match pitch {
            p if p > 127 => 127,
            p if p < -128 => -128,
            _ => pitch,
        };
        
        freq = (freq * PITCHTABLE[(pitch + 128) as usize] as u32) >> 15;
        
        if freq >= 1024 {
            freq >>= 1;
            octave += 1;
        }
    }

    if octave > 7 {
        octave = 7;
    }

    let mut voice = voice;
    if voice >= 9 {
        voice -= 9;
        voice |= 0x100;
    }

    oplregwr(opl, 0xA0 + voice, (freq & 0xff) as u8);
    oplregwr(opl, 0xB0 + voice, (((freq >> 8) as u16 | ((octave as u16) << 2)) as u8) | 32);
}
pub fn opl_loadinstrument(opl: &mut OplT, voice: usize, timbre: &OplTimbreT) {
    // Write modulator and carrier registers
    oplregwr(opl, 0x40 + OP1OFFSETS[voice], timbre.modulator_40);
    oplregwr(opl, 0x40 + OP2OFFSETS[voice], timbre.carrier_40 | 0x3f);
    
    oplregwr(opl, 0xE0 + OP1OFFSETS[voice], (timbre.modulator_e862 >> 24) as u8);
    oplregwr(opl, 0xE0 + OP2OFFSETS[voice], (timbre.carrier_e862 >> 24) as u8);
    
    oplregwr(opl, 0x80 + OP1OFFSETS[voice], ((timbre.modulator_e862 >> 16) & 0xff) as u8);
    oplregwr(opl, 0x80 + OP2OFFSETS[voice], ((timbre.carrier_e862 >> 16) & 0xff) as u8);
    
    oplregwr(opl, 0x60 + OP1OFFSETS[voice], ((timbre.modulator_e862 >> 8) & 0xff) as u8);
    oplregwr(opl, 0x60 + OP2OFFSETS[voice], ((timbre.carrier_e862 >> 8) & 0xff) as u8);
    
    oplregwr(opl, 0x20 + OP1OFFSETS[voice], (timbre.modulator_e862 & 0xff) as u8);
    oplregwr(opl, 0x20 + OP2OFFSETS[voice], (timbre.carrier_e862 & 0xff) as u8);

    // Handle voice adjustment for OPL3
    let mut adjusted_voice = voice as u16;
    if voice >= 9 {
        adjusted_voice -= 9;
        adjusted_voice |= 0x100;
    }

    // Write feedconn register with OPL3 flag if needed
    if opl.opl3 != 0 {
        oplregwr(opl, 0xC0 + adjusted_voice, timbre.feedconn | 0x30);
    } else {
        oplregwr(opl, 0xC0 + adjusted_voice, timbre.feedconn);
    }
}
pub fn opl_noteoff(opl: &mut OplT, voice: u16) {
    if voice >= 9 {
        oplregwr(opl, (0x1B0 + voice) - 9, 0);
    } else {
        oplregwr(opl, 0xB0 + voice, 0);
    }
}
pub fn opl_midi_noteoff_op2(opl: &mut OplT, channel: i32, note: i32, vindex: i32) {
    let voice = opl.notes2voices[channel as usize][note as usize][vindex as usize];
    if voice >= 0 {
        opl_noteoff(opl, voice as u16);
        
        let voice_entry = &mut opl.voices2notes[voice as usize];
        voice_entry.channel = -1;
        voice_entry.note = -1;
        voice_entry.priority = u16::MAX;
        voice_entry.voiceindex = 0xFF;
        
        opl.notes2voices[channel as usize][note as usize][vindex as usize] = -1;
    }
}
pub fn helper_opl_midi_noteon_op2_1(
    x_ref: &mut i32,
    voice_ref: &mut i32,
    lowestpriority_ref: &mut i32,
    highestvoiceindex_ref: &mut i32,
    lowestpriorityvoice_ref: &mut i32,
    opl: &mut OplT,
    vindex: i32,
    instrument: i32,
) {
    let voicescount = VOICESCOUNT.load(Ordering::Relaxed);
    let mut x = *x_ref;
    let mut voice = *voice_ref;
    let mut lowestpriority = *lowestpriority_ref;
    let mut highestvoiceindex = *highestvoiceindex_ref;
    let mut lowestpriorityvoice = *lowestpriorityvoice_ref;

    for x in 0..voicescount {
        if opl.voices2notes[x as usize].channel < 0 {
            voice = x;
            if i32::from(opl.voices2notes[x as usize].timbreid) == instrument 
                && i32::from(opl.voices2notes[x as usize].voiceindex) == vindex 
            {
                break;
            }
        }
        if i32::from(opl.voices2notes[x as usize].priority) < lowestpriority {
            if i32::from(opl.voices2notes[x as usize].voiceindex) >= vindex 
                && i32::from(opl.voices2notes[x as usize].voiceindex) >= highestvoiceindex 
            {
                lowestpriorityvoice = x;
                lowestpriority = i32::from(opl.voices2notes[x as usize].priority);
                highestvoiceindex = i32::from(opl.voices2notes[x as usize].voiceindex);
            }
        }
    }

    if voice < 0 {
        if lowestpriorityvoice < 0 {
            return;
        }
        voice = lowestpriorityvoice;
        let note_info = &opl.voices2notes[voice as usize];
        opl_midi_noteoff_op2(
            opl,
            i32::from(note_info.channel),
            i32::from(note_info.note),
            i32::from(note_info.voiceindex),
        );
    }

    *x_ref = x;
    *voice_ref = voice;
    *lowestpriority_ref = lowestpriority;
    *highestvoiceindex_ref = highestvoiceindex;
    *lowestpriorityvoice_ref = lowestpriorityvoice;
}
pub fn opl_midi_noteon_op2(
    opl: &mut OplT,
    channel: i32,
    note: i32,
    velocity: i32,
    vindex: i32,
) {
    if velocity == 0 {
        opl_midi_noteoff_op2(opl, channel, note, vindex);
        return;
    }

    let mut x = 0;
    let mut voice = -1;
    let mut lowestpriority = 0xFFFF;
    let mut highestvoiceindex = -1;
    let mut lowestpriorityvoice = -1;

    let instrument = match getinstrument(opl, channel, note) {
        Some(instr) => instr,
        None => return,
    };

    if vindex > 0 && opl.op2_flags[instrument as usize] as i32 & Op2FlagsT::OP2_DOUBLEVOICE as i32 == 0 {
        return;
    }

    let use_voice2 = vindex != 0;
    let timbre_index = instrument as usize;

    if opl.notes2voices[channel as usize][note as usize][vindex as usize] >= 0 {
        voice = opl.notes2voices[channel as usize][note as usize][vindex as usize] as i32;
    } else {
        helper_opl_midi_noteon_op2_1(
            &mut x,
            &mut voice,
            &mut lowestpriority,
            &mut highestvoiceindex,
            &mut lowestpriorityvoice,
            opl,
            vindex,
            instrument,
        );
    }

    // Store the needed timbre fields before making mutable calls
    let noteoffset = if use_voice2 {
        opl.opl_gmtimbres_voice2[timbre_index].noteoffset
    } else {
        opl.opl_gmtimbres[timbre_index].noteoffset
    };
    let finetune = if use_voice2 {
        opl.opl_gmtimbres_voice2[timbre_index].finetune
    } else {
        opl.opl_gmtimbres[timbre_index].finetune
    };
    let notenum = if use_voice2 {
        opl.opl_gmtimbres_voice2[timbre_index].notenum
    } else {
        opl.opl_gmtimbres[timbre_index].notenum
    };

    if opl.voices2notes[voice as usize].timbreid as i32 != instrument {
        opl.voices2notes[voice as usize].timbreid = instrument as i16;
        let timbre = if use_voice2 {
            opl.opl_gmtimbres_voice2[timbre_index].clone()
        } else {
            opl.opl_gmtimbres[timbre_index].clone()
        };
        opl_loadinstrument(opl, voice as usize, &timbre);
    }

    opl.voices2notes[voice as usize].channel = channel as i8;
    opl.voices2notes[voice as usize].note = note as i8;
    opl.voices2notes[voice as usize].priority = (((16 - channel) << 8) | 0xff) as u16;
    opl.voices2notes[voice as usize].voiceindex = vindex as u8;
    opl.notes2voices[channel as usize][note as usize][vindex as usize] = voice as i8;

    if vindex != 0 {
        let mut reducedprio = opl.voices2notes[voice as usize].priority as i32 - 0xFF;
        if reducedprio < 0 {
            reducedprio = 0;
        }
        opl.voices2notes[voice as usize].priority = reducedprio as u16;
    }

    let volume = (velocity * opl.channelvol[channel as usize] as i32) / 127;
    let timbre = if use_voice2 {
        opl.opl_gmtimbres_voice2[timbre_index].clone()
    } else {
        opl.opl_gmtimbres[timbre_index].clone()
    };
    voicevolume(opl, voice as u16, &timbre, volume);

    if channel == 9 {
        opl_noteon(
            opl,
            voice as u16,
            (notenum as u32).wrapping_add(noteoffset as u32),
            opl.channelpitch[channel as usize] as i32 + finetune as i32,
        );
    } else {
        opl_noteon(
            opl,
            voice as u16,
            (note as u32).wrapping_add(noteoffset as u32),
            opl.channelpitch[channel as usize] as i32 + finetune as i32,
        );
    }

    let voicescount = VOICESCOUNT.load(Ordering::Relaxed);
    for x in 0..voicescount {
        if opl.voices2notes[x as usize].priority > 0 {
            opl.voices2notes[x as usize].priority -= 1;
        }
    }
}
pub fn opl_midi_noteon(opl: &mut OplT, channel: i32, note: i32, velocity: i32) {
    opl_midi_noteon_op2(opl, channel, note, velocity, 1);
    opl_midi_noteon_op2(opl, channel, note, velocity, 0);
}
pub fn opl_midi_noteoff(opl: &mut OplT, channel: i32, note: i32) {
    opl_midi_noteoff_op2(opl, channel, note, 0);
    opl_midi_noteoff_op2(opl, channel, note, 1);
}

pub fn opl_loadbank_internal(opl: &mut OplT, file: &Path, offset: i32) -> Result<(), i32> {
    opl.is_op2 = 0;
    let mut buff = [0u8; 16];
    
    let mut f = match File::open(file) {
        Ok(file) => file,
        Err(_) => return Err(-1),
    };

    // Check file size
    let file_size = match f.seek(SeekFrom::End(0)) {
        Ok(size) => size,
        Err(_) => {
            return Err(-2);
        }
    };
    if file_size != 3204 {
        return Err(-2);
    }

    // Reset to beginning
    if f.seek(SeekFrom::Start(0)).is_err() {
        return Err(-2);
    }

    // Read and check header
    if f.read_exact(&mut buff[..4]).is_err() 
        || buff[0] != b'I' 
        || buff[1] != b'B' 
        || buff[2] != b'K' 
        || buff[3] != 0x1A 
    {
        return Err(-3);
    }

    // Process each entry
    for i in offset..(128 + offset) {
        let mut i_ref = i;
        if let Err(_) = helper_opl_loadbank_internal_1(&mut i_ref, opl, &mut buff, &mut f) {
            return Err(-3);
        }
    }

    Ok(())
}
pub fn opl_loadbank_ibk(opl: &mut OplT, file: Option<&CStr>) -> i32 {
    // Check for NULL input (None in Rust)
    if file.is_none() {
        return -64;
    }
    
    let file = file.unwrap();
    
    // Convert CStr to Rust String and then to CString for safe manipulation
    let instruments_cstring = match file.to_str() {
        Ok(s) => CString::new(s).unwrap(),
        Err(_) => return -64,
    };
    
    let mut instruments_ptr = instruments_cstring.into_raw();
    let mut percussion_ptr: *mut c_char = std::ptr::null_mut();
    let mut res: i32;
    
    // Iterate through the duplicated string to find comma
    let mut i = 0;
    unsafe {
        while *instruments_ptr.offset(i) != 0 {
            if *instruments_ptr.offset(i) == b',' as c_char {
                *instruments_ptr.offset(i) = 0;
                percussion_ptr = instruments_ptr.offset(i + 1);
                break;
            }
            i += 1;
        }
    }
    
    // Convert percussion pointer to Option<&CStr> for safe handling
    let percussion = if percussion_ptr.is_null() {
        None
    } else {
        Some(unsafe { CStr::from_ptr(percussion_ptr) })
    };
    
    // Convert CStr to Path for the internal function
    let instruments_path = Path::new(unsafe { CStr::from_ptr(instruments_ptr) }.to_str().unwrap());
    
    // Call internal function with instruments and convert Result to i32
    res = match opl_loadbank_internal(opl, instruments_path, 0) {
        Ok(()) => 0,
        Err(e) => e,
    };
    
    // Call internal function with percussion if first call succeeded and percussion exists
    if res == 0 && percussion.is_some() {
        let percussion_path = Path::new(percussion.unwrap().to_str().unwrap());
        res = match opl_loadbank_internal(opl, percussion_path, 128) {
            Ok(()) => 0,
            Err(e) => e,
        };
    }
    
    // Reconstruct CString to properly free the memory
    unsafe {
        let _ = CString::from_raw(instruments_ptr);
    };
    
    res
}
pub fn opl_load_op2_voice(timbre: &mut OplTimbreT, buff: &[u8]) {
    // Process modulator_E862 (lines 3-9)
    timbre.modulator_e862 = ((buff[3] as u32) << 24)
        | ((buff[2] as u32) << 16)
        | ((buff[1] as u32) << 8)
        | (buff[0] as u32);

    // Process carrier_E862 (lines 10-16)
    timbre.carrier_e862 = ((buff[10] as u32) << 24)
        | ((buff[9] as u32) << 16)
        | ((buff[8] as u32) << 8)
        | (buff[7] as u32);

    // Process modulator_40 (line 17)
    timbre.modulator_40 = (buff[5] & 0x3f) | (buff[4] & 0xc0);

    // Process carrier_40 (line 18)
    timbre.carrier_40 = (buff[12] & 0x3f) | (buff[11] & 0xc0);

    // Process feedconn (line 19)
    timbre.feedconn = buff[6];

    // Process finetune (line 20)
    timbre.finetune = 0;

    // Process noteoffset (line 21)
    timbre.noteoffset = (buff[14] as i16) | (((buff[15] as u16) << 8) as i16);
}
pub fn opl_loadbank_op2(opl: &mut OplT, data: &[u8], size: usize) -> i32 {
    // Check minimum size requirement (8 + (36 * 175))
    if size < 8 + 36 * 175 {
        return -3;
    }

    let mut buff_idx = 0;

    // Check for magic header "#OPL_II#"
    if data.get(buff_idx..buff_idx + 8) != Some(b"#OPL_II#") {
        return -3;
    }
    buff_idx += 8;

    opl.is_op2 = 1;

    for i in 0..175 {
        // Read op2_flags (2 bytes)
        let flags = u16::from_le_bytes([data[buff_idx], data[buff_idx + 1]]);
        opl.op2_flags[i] = unsafe { std::mem::transmute_copy(&flags) };

        // Read finetune and fixednote (1 byte each)
        let finetune = data[buff_idx + 2] as i32; // Changed to i32 for arithmetic
        let fixednote = data[buff_idx + 3];
        buff_idx += 4;

        // Load first voice
        opl_load_op2_voice(&mut opl.opl_gmtimbres[i], &data[buff_idx..]);
        opl.opl_gmtimbres[i].notenum = fixednote;
        buff_idx += 16;

        // Load second voice
        opl_load_op2_voice(&mut opl.opl_gmtimbres_voice2[i], &data[buff_idx..]);
        opl.opl_gmtimbres_voice2[i].notenum = fixednote;
        opl.opl_gmtimbres_voice2[i].finetune = opl.opl_gmtimbres_voice2[i].finetune.wrapping_add((finetune - 128) as i8);
        buff_idx += 16;
    }

    0
}
pub fn opl_emu_registers_byte(regs: &OplEmuRegisters, offset: u32, start: u32, count: u32, extra_offset: u32) -> u32 {
    opl_emu_bitfield(regs.m_regdata[(offset + extra_offset) as usize] as u32, start as i32, count as i32)
}
pub fn opl_emu_registers_rhythm_enable(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0xbd, 5, 1, 0)
}
pub fn opl_emu_registers_op_lfo_am_enable(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x20, 7, 1, opoffs)
}
pub fn opl_emu_fm_operator_envelope_attenuation(fmop: &OplEmuFmOperator, am_offset: u32) -> u32 {
    let mut result = (fmop.m_env_attenuation as u32) >> fmop.m_cache.eg_shift;
    
    if let Some(regs) = &fmop.m_regs {
        if opl_emu_registers_op_lfo_am_enable(regs, fmop.m_opoffs) != 0 {
            result += am_offset;
        }
    }
    
    result += fmop.m_cache.total_level;
    
    if result < 0x3ff {
        result
    } else {
        0x3ff
    }
}
pub fn opl_emu_fm_operator_compute_volume(fmop: &OplEmuFmOperator, phase: u32, am_offset: u32) -> i32 {
    if fmop.m_env_attenuation > 0x200 {
        return 0;
    }
    
    let sin_attenuation = match &fmop.m_cache.waveform {
        Some(waveform) => waveform[(phase & (0x400 - 1)) as usize] as u32,
        None => return 0,
    };
    let env_attenuation = opl_emu_fm_operator_envelope_attenuation(fmop, am_offset) << 2;
    let result = opl_emu_attenuation_to_volume((sin_attenuation & 0x7fff) + env_attenuation) as i32;
    
    if opl_emu_bitfield(sin_attenuation, 15, 1) != 0 {
        -result
    } else {
        result
    }
}
pub fn opl_emu_registers_newflag(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0x105, 0, 1, 0)
}
pub fn opl_emu_registers_ch_output_1(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(regs, 0xc0 + choffs, 5, 1, 0)
    } else {
        1
    }
}
pub fn opl_emu_registers_ch_output_0(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(regs, 0xc0 + choffs, 4, 1, 0)
    } else {
        1
    }
}
pub fn opl_emu_fm_channel_add_to_output(fmch: &mut OplEmuFmChannel, choffs: u32, output: &mut [i16], value: i32) {
    let out0_index = 0;
    let out1_index = 1 % 2;
    let out2_index = 2 % 2;
    let out3_index = 3 % 2;

    if (2 == 1) || opl_emu_registers_ch_output_0(fmch.m_regs.as_ref().unwrap(), choffs) != 0 {
        let s = output[out0_index] as i32 + value;
        output[out0_index] = if s < -32767 {
            -32767
        } else if s > 32767 {
            32767
        } else {
            s as i16
        };
    }

    if (2 >= 2) && opl_emu_registers_ch_output_1(fmch.m_regs.as_ref().unwrap(), choffs) != 0 {
        let s = output[out1_index] as i32 + value;
        output[out1_index] = if s < -32767 {
            -32767
        } else if s > 32767 {
            32767
        } else {
            s as i16
        };
    }
}
pub fn opl_emu_fm_channel_output_rhythm_ch8(
    fmch: &mut OplEmuFmChannel,
    phase_select: u32,
    output: &mut [i16],
    rshift: u32,
    clipmax: i32,
) {
    // Calculate AM offset
    let am_offset = if let Some(regs) = &fmch.m_regs {
        opl_emu_registers_lfo_am_offset(regs, fmch.m_choffs)
    } else {
        0 // Default value if regs is None
    };

    // Compute result from first operator
    let mut result = if let Some(op0) = &fmch.m_op[0] {
        opl_emu_fm_operator_compute_volume(
            op0,
            opl_emu_fm_operator_phase(op0),
            am_offset,
        ) >> rshift
    } else {
        0 // Default value if op0 is None
    };

    // Compute phase and add second operator's contribution
    let phase = 0x100 | (phase_select << 9);
    if let Some(op1) = &fmch.m_op[1] {
        result += opl_emu_fm_operator_compute_volume(op1, phase, am_offset) >> rshift;
    }

    // Clamp the result and add to output
    result = opl_emu_clamp(result, (-clipmax) - 1, clipmax);
    opl_emu_fm_channel_add_to_output(fmch, fmch.m_choffs, output, result * 2);
}
pub fn opl_emu_fm_channel_output_rhythm_ch7(
    fmch: &mut OplEmuFmChannel,
    phase_select: u32,
    output: &mut [i16],
    rshift: u32,
    clipmax: i32,
) {
    // Calculate am_offset using the registers
    let am_offset = if let Some(regs) = &fmch.m_regs {
        opl_emu_registers_lfo_am_offset(regs, fmch.m_choffs)
    } else {
        0 // Default value if registers are None
    };

    // Get noise_state from registers
    let noise_state = if let Some(regs) = &fmch.m_regs {
        opl_emu_bitfield(opl_emu_registers_noise_state(regs), 0, 1)
    } else {
        0 // Default value if registers are None
    };

    // Calculate phase
    let mut phase = (phase_select << 9) | (0xd0 >> (2 * (noise_state ^ phase_select)));

    // Compute first operator result
    let mut result = if let Some(op) = &fmch.m_op[0] {
        opl_emu_fm_operator_compute_volume(op, phase, am_offset) >> rshift
    } else {
        0 // Default value if operator is None
    };

    // Get op13phase from first operator
    let op13phase = if let Some(op) = &fmch.m_op[0] {
        opl_emu_fm_operator_phase(op)
    } else {
        0 // Default value if operator is None
    };

    // Update phase and compute second operator result
    phase = (0x100 << opl_emu_bitfield(op13phase, 8, 1)) ^ (noise_state << 8);
    result += if let Some(op) = &fmch.m_op[1] {
        opl_emu_fm_operator_compute_volume(op, phase, am_offset) >> rshift
    } else {
        0 // Default value if operator is None
    };

    // Clamp the result and add to output
    let clamped_result = opl_emu_clamp(result, (-clipmax) - 1, clipmax);
    opl_emu_fm_channel_add_to_output(fmch, fmch.m_choffs, output, clamped_result * 2);
}
pub fn opl_emu_registers_ch_feedback(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0xc0, 1, 3, choffs)
}
pub fn opl_emu_registers_ch_algorithm(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0xc0, 0, 1, choffs) | 
    (8 | (opl_emu_registers_byte(regs, 0xc3, 0, 1, choffs) << 1))
}
pub fn opl_emu_fm_channel_output_rhythm_ch6(
    fmch: &mut OplEmuFmChannel,
    output: &mut [i16],
    rshift: u32,
    clipmax: i32,
) {
    // Get AM offset
    let am_offset = if let Some(ref regs) = fmch.m_regs {
        opl_emu_registers_lfo_am_offset(regs, fmch.m_choffs)
    } else {
        0
    };

    // Calculate feedback
    let mut opmod = 0i32;
    let feedback = if let Some(ref regs) = fmch.m_regs {
        opl_emu_registers_ch_feedback(regs, fmch.m_choffs)
    } else {
        0
    };

    if feedback != 0 {
        opmod = (i32::from(fmch.m_feedback[0]) + i32::from(fmch.m_feedback[1])) >> (10 - feedback as i32);
    }

    // Compute operator 1 output
    let op1 = if let Some(ref op0) = fmch.m_op[0] {
        let phase = opl_emu_fm_operator_phase(op0).wrapping_add(opmod as u32);
        opl_emu_fm_operator_compute_volume(op0, phase, am_offset)
    } else {
        0
    };
    fmch.m_feedback_in = op1 as i16;

    // Compute operator 2 modulation
    let opmod = if let Some(ref regs) = fmch.m_regs {
        if opl_emu_bitfield(opl_emu_registers_ch_algorithm(regs, fmch.m_choffs), 0, 1) != 0 {
            0
        } else {
            op1 >> 1
        }
    } else {
        0
    };

    // Compute operator 2 output and final result
    let result = if let Some(ref op1) = fmch.m_op[1] {
        let phase = opl_emu_fm_operator_phase(op1).wrapping_add(opmod as u32);
        opl_emu_fm_operator_compute_volume(op1, phase, am_offset) >> rshift
    } else {
        0
    };

    // Add to output
    opl_emu_fm_channel_add_to_output(fmch, fmch.m_choffs, output, result * 2);
}
pub fn opl_emu_registers_ch_output_any(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(regs, 0xc0 + choffs, 4, 4, 0)
    } else {
        1
    }
}
pub fn opl_emu_fm_channel_output_4op(
    fmch: &mut OplEmuFmChannel,
    output: &mut [i16],
    rshift: u32,
    clipmax: i32,
) {
    let am_offset = opl_emu_registers_lfo_am_offset(
        fmch.m_regs.as_ref().unwrap(),
        fmch.m_choffs,
    );
    let mut opmod = 0i32;
    let feedback = opl_emu_registers_ch_feedback(
        fmch.m_regs.as_ref().unwrap(),
        fmch.m_choffs,
    );
    if feedback != 0 {
        opmod = (fmch.m_feedback[0] as i32 + fmch.m_feedback[1] as i32) >> (10 - feedback) as i32;
    }
    let op1value = {
        let phase = opl_emu_fm_operator_phase(fmch.m_op[0].as_ref().unwrap());
        let volume = opl_emu_fm_operator_compute_volume(
            fmch.m_op[0].as_ref().unwrap(),
            phase.wrapping_add(opmod as u32),
            am_offset,
        );
        fmch.m_feedback_in = volume as i16;
        volume
    };
    if opl_emu_registers_ch_output_any(
        fmch.m_regs.as_ref().unwrap(),
        fmch.m_choffs,
    ) == 0 {
        return;
    }
    const S_ALGORITHM_OPS: [u16; 12] = [
        1 | (2 << 1) | (3 << 4) | (0 << 7) | (0 << 8) | (0 << 9),
        0 | (5 << 1) | (3 << 4) | (0 << 7) | (0 << 8) | (0 << 9),
        0 | (2 << 1) | (6 << 4) | (0 << 7) | (0 << 8) | (0 << 9),
        1 | (0 << 1) | (7 << 4) | (0 << 7) | (0 << 8) | (0 << 9),
        1 | (0 << 1) | (3 << 4) | (0 << 7) | (1 << 8) | (0 << 9),
        1 | (1 << 1) | (1 << 4) | (0 << 7) | (1 << 8) | (1 << 9),
        1 | (0 << 1) | (0 << 4) | (0 << 7) | (1 << 8) | (1 << 9),
        0 | (0 << 1) | (0 << 4) | (1 << 7) | (1 << 8) | (1 << 9),
        1 | (2 << 1) | (3 << 4) | (0 << 7) | (0 << 8) | (0 << 9),
        0 | (2 << 1) | (3 << 4) | (1 << 7) | (0 << 8) | (0 << 9),
        1 | (0 << 1) | (3 << 4) | (0 << 7) | (1 << 8) | (0 << 9),
        0 | (2 << 1) | (0 << 4) | (1 << 7) | (0 << 8) | (1 << 9),
    ];
    let algorithm_ops = S_ALGORITHM_OPS[opl_emu_registers_ch_algorithm(
        fmch.m_regs.as_ref().unwrap(),
        fmch.m_choffs,
    ) as usize];
    let mut opout = [0i16; 8];
    opout[0] = 0;
    opout[1] = op1value as i16;
    opmod = opout[opl_emu_bitfield(algorithm_ops as u32, 0, 1) as usize] as i32 >> 1;
    opout[2] = {
        let phase = opl_emu_fm_operator_phase(fmch.m_op[1].as_ref().unwrap());
        opl_emu_fm_operator_compute_volume(
            fmch.m_op[1].as_ref().unwrap(),
            phase.wrapping_add(opmod as u32),
            am_offset,
        ) as i16
    };
    opout[5] = opout[1] + opout[2];
    opmod = opout[opl_emu_bitfield(algorithm_ops as u32, 1, 3) as usize] as i32 >> 1;
    opout[3] = {
        let phase = opl_emu_fm_operator_phase(fmch.m_op[2].as_ref().unwrap());
        opl_emu_fm_operator_compute_volume(
            fmch.m_op[2].as_ref().unwrap(),
            phase.wrapping_add(opmod as u32),
            am_offset,
        ) as i16
    };
    opout[6] = opout[1] + opout[3];
    opout[7] = opout[2] + opout[3];
    opmod = opout[opl_emu_bitfield(algorithm_ops as u32, 4, 3) as usize] as i32 >> 1;
    let mut result = {
        let phase = opl_emu_fm_operator_phase(fmch.m_op[3].as_ref().unwrap());
        opl_emu_fm_operator_compute_volume(
            fmch.m_op[3].as_ref().unwrap(),
            phase.wrapping_add(opmod as u32),
            am_offset,
        )
    };
    result >>= rshift;
    let clipmin = (-clipmax) - 1;
    if opl_emu_bitfield(algorithm_ops as u32, 7, 1) != 0 {
        result = opl_emu_clamp(result + (opout[1] as i32 >> rshift as i32), clipmin, clipmax);
    }
    if opl_emu_bitfield(algorithm_ops as u32, 8, 1) != 0 {
        result = opl_emu_clamp(result + (opout[2] as i32 >> rshift as i32), clipmin, clipmax);
    }
    if opl_emu_bitfield(algorithm_ops as u32, 9, 1) != 0 {
        result = opl_emu_clamp(result + (opout[3] as i32 >> rshift as i32), clipmin, clipmax);
    }
    opl_emu_fm_channel_add_to_output(fmch, fmch.m_choffs, output, result);
}
pub fn opl_emu_fm_channel_output_2op(
    fmch: &mut OplEmuFmChannel,
    output: &mut [i16],
    rshift: u32,
    clipmax: i32,
) {
    // Get AM offset from registers
    let am_offset = if let Some(ref regs) = fmch.m_regs {
        opl_emu_registers_lfo_am_offset(regs, fmch.m_choffs)
    } else {
        return;
    };

    let mut opmod = 0;
    let feedback = if let Some(ref regs) = fmch.m_regs {
        opl_emu_registers_ch_feedback(regs, fmch.m_choffs)
    } else {
        return;
    };

    if feedback != 0 {
        opmod = (i32::from(fmch.m_feedback[0]) + i32::from(fmch.m_feedback[1])) >> (10 - feedback);
    }

    // Compute operator 1 value
    let op1value = {
        let op0 = if let Some(ref op) = fmch.m_op[0] {
            op
        } else {
            return;
        };
        let phase = opl_emu_fm_operator_phase(op0) + opmod as u32;
        let value = opl_emu_fm_operator_compute_volume(op0, phase, am_offset);
        fmch.m_feedback_in = value as i16;
        value
    };

    // Check if any output is enabled
    if let Some(ref regs) = fmch.m_regs {
        if opl_emu_registers_ch_output_any(regs, fmch.m_choffs) == 0 {
            return;
        }
    } else {
        return;
    }

    let result = if let Some(ref regs) = fmch.m_regs {
        if opl_emu_bitfield(opl_emu_registers_ch_algorithm(regs, fmch.m_choffs), 0, 1) == 0 {
            // Algorithm bit 0 is 0
            opmod = op1value >> 1;
            let op1 = if let Some(ref op) = fmch.m_op[1] {
                op
            } else {
                return;
            };
            let phase = opl_emu_fm_operator_phase(op1) + opmod as u32;
            opl_emu_fm_operator_compute_volume(op1, phase, am_offset) >> rshift
        } else {
            // Algorithm bit 0 is 1
            let op1 = if let Some(ref op) = fmch.m_op[1] {
                op
            } else {
                return;
            };
            let phase = opl_emu_fm_operator_phase(op1);
            let value = op1value + (opl_emu_fm_operator_compute_volume(op1, phase, am_offset) >> rshift);
            let clipmin = (-clipmax) - 1;
            opl_emu_clamp(value, clipmin, clipmax)
        }
    } else {
        return;
    };

    opl_emu_fm_channel_add_to_output(fmch, fmch.m_choffs, output, result);
}
pub fn opl_emu_out(
    emu: &mut OplEmuT,
    output: &mut [i16],
    rshift: u32,
    clipmax: i32,
    chanmask: u32,
) {
    let chanmask = chanmask & emu.m_active_channels;
    
    if opl_emu_registers_rhythm_enable(&emu.m_regs) != 0 {
        let op13phase = opl_emu_fm_operator_phase(&emu.m_operator[13]);
        let op17phase = opl_emu_fm_operator_phase(&emu.m_operator[17]);
        let phase_select = ((opl_emu_bitfield(op13phase, 2, 1) ^ opl_emu_bitfield(op13phase, 7, 1)) 
                          | opl_emu_bitfield(op13phase, 3, 1)) 
                          | (opl_emu_bitfield(op17phase, 5, 1) ^ opl_emu_bitfield(op17phase, 3, 1));
        
        for chnum in 0..18 {
            if opl_emu_bitfield(chanmask, chnum as i32, 1) != 0 {
                match chnum {
                    6 => {
                        opl_emu_fm_channel_output_rhythm_ch6(
                            &mut emu.m_channel[chnum],
                            output,
                            rshift,
                            clipmax,
                        );
                    }
                    7 => {
                        opl_emu_fm_channel_output_rhythm_ch7(
                            &mut emu.m_channel[chnum],
                            phase_select,
                            output,
                            rshift,
                            clipmax,
                        );
                    }
                    8 => {
                        opl_emu_fm_channel_output_rhythm_ch8(
                            &mut emu.m_channel[chnum],
                            phase_select,
                            output,
                            rshift,
                            clipmax,
                        );
                    }
                    _ => {
                        if opl_emu_fm_channel_is4op(&emu.m_channel[chnum]) {
                            opl_emu_fm_channel_output_4op(
                                &mut emu.m_channel[chnum],
                                output,
                                rshift,
                                clipmax,
                            );
                        } else {
                            opl_emu_fm_channel_output_2op(
                                &mut emu.m_channel[chnum],
                                output,
                                rshift,
                                clipmax,
                            );
                        }
                    }
                }
            }
        }
    } else {
        for chnum in 0..18 {
            if opl_emu_bitfield(chanmask, chnum as i32, 1) != 0 {
                if opl_emu_fm_channel_is4op(&emu.m_channel[chnum]) {
                    opl_emu_fm_channel_output_4op(
                        &mut emu.m_channel[chnum],
                        output,
                        rshift,
                        clipmax,
                    );
                } else {
                    opl_emu_fm_channel_output_2op(
                        &mut emu.m_channel[chnum],
                        output,
                        rshift,
                        clipmax,
                    );
                }
            }
        }
    }
}
pub fn opl_emu_registers_lfo_pm_depth(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0xbd, 6, 1, 0)
}
pub fn opl_emu_registers_lfo_am_depth(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0xbd, 7, 1, 0)
}
pub fn opl_emu_registers_clock_noise_and_lfo(regs: &mut OplEmuRegisters) -> i32 {
    let am_depth = opl_emu_registers_lfo_am_depth(regs);
    let pm_depth = opl_emu_registers_lfo_pm_depth(regs);
    opl_emu_opl_clock_noise_and_lfo(
        &mut regs.m_noise_lfsr,
        &mut [regs.m_lfo_am_counter],
        &mut [regs.m_lfo_pm_counter],
        &mut regs.m_lfo_am,
        am_depth,
        pm_depth,
    )
}
pub fn opl_emu_registers_op_waveform(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    let newflag = opl_emu_registers_newflag(regs);
    let count = if newflag != 0 { 3 } else { 2 };
    opl_emu_registers_byte(regs, 0xe0, 0, count, opoffs)
}
pub fn opl_emu_registers_op_total_level(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x40, 0, 6, opoffs)
}
pub fn opl_emu_registers_op_sustain_level(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x80, 4, 4, opoffs)
}
pub fn opl_emu_registers_op_release_rate(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x80, 0, 4, opoffs)
}
pub fn opl_emu_registers_op_multiple(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x20, 0, 4, opoffs)
}
pub fn opl_emu_registers_op_ksr(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x20, 4, 1, opoffs)
}
pub fn opl_emu_registers_op_ksl(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    let temp = opl_emu_registers_byte(regs, 0x40, 6, 2, opoffs);
    opl_emu_bitfield(temp, 1, 1) | (opl_emu_bitfield(temp, 0, 1) << 1)
}
pub fn opl_emu_registers_op_eg_sustain(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x20, 5, 1, opoffs)
}
pub fn opl_emu_registers_op_decay_rate(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x60, 0, 4, opoffs)
}
pub fn opl_emu_registers_op_attack_rate(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x60, 4, 4, opoffs)
}
pub fn opl_emu_registers_note_select(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0x08, 6, 1, 0)
}
pub fn opl_emu_registers_word(
    regs: &OplEmuRegisters,
    offset1: u32,
    start1: u32,
    count1: u32,
    offset2: u32,
    start2: u32,
    count2: u32,
    extra_offset: u32,
) -> u32 {
    (opl_emu_registers_byte(regs, offset1, start1, count1, extra_offset) << count2)
        | opl_emu_registers_byte(regs, offset2, start2, count2, extra_offset)
}
pub fn opl_emu_registers_ch_block_freq(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    opl_emu_registers_word(regs, 0xb0, 0, 5, 0xa0, 0, 8, choffs)
}
pub fn opl_emu_registers_op_lfo_pm_enable(regs: &OplEmuRegisters, opoffs: u32) -> u32 {
    opl_emu_registers_byte(regs, 0x20, 6, 1, opoffs)
}
pub fn opl_emu_registers_compute_phase_step(
    regs: &OplEmuRegisters,
    choffs: u32,
    opoffs: u32,
    cache: &OplEmuOpdataCache,
    lfo_raw_pm: i32,
) -> u32 {
    opl_emu_opl_compute_phase_step(
        cache.block_freq,
        cache.multiple,
        if opl_emu_registers_op_lfo_pm_enable(regs, opoffs) != 0 {
            lfo_raw_pm
        } else {
            0
        },
    )
}
pub fn opl_emu_registers_cache_operator_data(
    regs: &OplEmuRegisters,
    choffs: u32,
    opoffs: u32,
    cache: &mut OplEmuOpdataCache,
) {
    // Line 3: waveform assignment
    let waveform_index = opl_emu_registers_op_waveform(regs, opoffs) % 8;
    cache.waveform = Some(regs.m_waveform[waveform_index as usize].to_vec());

    // Line 4: block_freq assignment
    let block_freq = opl_emu_registers_ch_block_freq(regs, choffs);
    cache.block_freq = block_freq;

    // Lines 5-6: keycode calculation
    let mut keycode = opl_emu_bitfield(block_freq, 10, 3) << 1;
    keycode |= opl_emu_bitfield(block_freq, (9 - opl_emu_registers_note_select(regs)) as i32, 1);

    // Line 7: detune initialization
    cache.detune = 0;

    // Lines 8-13: multiple calculation
    let multiple = opl_emu_registers_op_multiple(regs, opoffs);
    cache.multiple = ((multiple & 0xe) | opl_emu_bitfield(0xc2aa, multiple as i32, 1)) * 2;
    if cache.multiple == 0 {
        cache.multiple = 1;
    }

    // Lines 14-19: phase_step assignment
    if opl_emu_registers_op_lfo_pm_enable(regs, opoffs) == 0 {
        cache.phase_step = opl_emu_registers_compute_phase_step(regs, choffs, opoffs, cache, 0);
    } else {
        cache.phase_step = 1;
    }

    // Lines 20-25: total_level calculation
    cache.total_level = opl_emu_registers_op_total_level(regs, opoffs) << 3;
    let ksl = opl_emu_registers_op_ksl(regs, opoffs);
    if ksl != 0 {
        let block = opl_emu_bitfield(block_freq, 10, 3);
        let fnum_4msb = opl_emu_bitfield(block_freq, 6, 4);
        cache.total_level += opl_emu_opl_key_scale_atten(block, fnum_4msb) << ksl;
    }

    // Lines 26-28: eg_sustain calculation
    cache.eg_sustain = opl_emu_registers_op_sustain_level(regs, opoffs);
    cache.eg_sustain |= (cache.eg_sustain + 1) & 0x10;
    cache.eg_sustain <<= 5;

    // Lines 29-33: eg_rate assignments
    let ksrval = keycode >> (2 * (opl_emu_registers_op_ksr(regs, opoffs) ^ 1));
    cache.eg_rate[0] = opl_emu_registers_effective_rate(
        opl_emu_registers_op_attack_rate(regs, opoffs) * 4,
        ksrval,
    ) as u8;
    cache.eg_rate[1] = opl_emu_registers_effective_rate(
        opl_emu_registers_op_decay_rate(regs, opoffs) * 4,
        ksrval,
    ) as u8;
    cache.eg_rate[2] = if opl_emu_registers_op_eg_sustain(regs, opoffs) != 0 {
        0
    } else {
        opl_emu_registers_effective_rate(
            opl_emu_registers_op_release_rate(regs, opoffs) * 4,
            ksrval,
        ) as u8
    };
    cache.eg_rate[3] = opl_emu_registers_effective_rate(
        opl_emu_registers_op_release_rate(regs, opoffs) * 4,
        ksrval,
    ) as u8;
}
pub fn opl_emu_fm_operator_clock_keystate(fmop: &mut OplEmuFmOperator, keystate: u32) {
    if (keystate ^ fmop.m_key_state as u32) != 0 {
        fmop.m_key_state = keystate as u8;
        if keystate != 0 {
            opl_emu_fm_operator_start_attack(fmop);
        } else {
            opl_emu_fm_operator_start_release(fmop);
        }
    }
}
pub fn opl_emu_fm_operator_prepare(fmop: &mut OplEmuFmOperator) -> bool {
    // First operation: cache operator data
    if let Some(ref regs) = fmop.m_regs {
        opl_emu_registers_cache_operator_data(
            regs,
            fmop.m_choffs,
            fmop.m_opoffs,
            &mut fmop.m_cache,
        );
    }

    // Second operation: clock keystate
    let keystate = (fmop.m_keyon_live != 0) as u32;
    opl_emu_fm_operator_clock_keystate(fmop, keystate);

    // Third operation: clear CSM bit
    fmop.m_keyon_live &= !(1 << OplEmuKeyonType::OPL_EMU_KEYON_CSM as u8);

    // Final condition check
    (fmop.m_env_state != OplEmuEnvelopeState::OPL_EMU_EG_RELEASE) || (fmop.m_env_attenuation < 0x200)
}
pub fn opl_emu_fm_channel_prepare(fmch: &mut OplEmuFmChannel) -> bool {
    let mut active_mask = 0;
    
    for opnum in 0..fmch.m_op.len() {
        if let Some(op) = &mut fmch.m_op[opnum] {
            if opl_emu_fm_operator_prepare(op.as_mut()) {
                active_mask |= 1 << opnum;
            }
        }
    }
    
    active_mask != 0
}
pub fn opl_emu_fm_operator_clock_phase(fmop: &mut OplEmuFmOperator, lfo_raw_pm: i32) {
    let mut phase_step = fmop.m_cache.phase_step;
    if phase_step == 1 {
        // Safe unwrap since m_regs is required for computation
        let regs = fmop.m_regs.as_ref().unwrap();
        phase_step = opl_emu_registers_compute_phase_step(
            regs,
            fmop.m_choffs,
            fmop.m_opoffs,
            &fmop.m_cache,
            lfo_raw_pm,
        );
    }
    fmop.m_phase += phase_step;
}
pub fn opl_emu_fm_operator_clock_envelope(fmop: &mut OplEmuFmOperator, env_counter: u32) {
    // Check and update envelope state transitions
    if fmop.m_env_state == OplEmuEnvelopeState::OPL_EMU_EG_ATTACK && fmop.m_env_attenuation == 0 {
        fmop.m_env_state = OplEmuEnvelopeState::OPL_EMU_EG_DECAY;
    }
    if fmop.m_env_state == OplEmuEnvelopeState::OPL_EMU_EG_DECAY && 
       u32::from(fmop.m_env_attenuation) >= fmop.m_cache.eg_sustain {
        fmop.m_env_state = OplEmuEnvelopeState::OPL_EMU_EG_SUSTAIN;
    }

    let rate = fmop.m_cache.eg_rate[fmop.m_env_state as usize];
    let rate_shift = rate >> 2;
    let shifted_counter = env_counter << rate_shift;

    // Early return if lower 11 bits are non-zero
    if opl_emu_bitfield(shifted_counter, 0, 11) != 0 {
        return;
    }

    let relevant_bits = if rate_shift <= 11 {
        opl_emu_bitfield(shifted_counter, 11, 3)
    } else {
        opl_emu_bitfield(shifted_counter, rate_shift as i32, 3)
    };
    let increment = opl_emu_attenuation_increment(rate as u32, relevant_bits);

    match fmop.m_env_state {
        OplEmuEnvelopeState::OPL_EMU_EG_ATTACK => {
            if rate < 62 {
                fmop.m_env_attenuation = fmop.m_env_attenuation.wrapping_add(
                    ((!fmop.m_env_attenuation as u32) * increment >> 4) as u16
                );
            }
        },
        _ => {
            fmop.m_env_attenuation = fmop.m_env_attenuation.wrapping_add(increment as u16);
            if fmop.m_env_attenuation >= 0x400 {
                fmop.m_env_attenuation = 0x3ff;
            }
        }
    }
}
pub fn opl_emu_fm_operator_clock(fmop: &mut OplEmuFmOperator, env_counter: u32, lfo_raw_pm: i32) {
    if opl_emu_bitfield(env_counter, 0, 2) == 0 {
        opl_emu_fm_operator_clock_envelope(fmop, env_counter >> 2);
    }
    opl_emu_fm_operator_clock_phase(fmop, lfo_raw_pm);
}
pub fn opl_emu_fm_channel_clock(fmch: &mut OplEmuFmChannel, env_counter: u32, lfo_raw_pm: i32) {
    // Update feedback values
    fmch.m_feedback[0] = fmch.m_feedback[1];
    fmch.m_feedback[1] = fmch.m_feedback_in;

    // Iterate through operators
    for opnum in 0..fmch.m_op.len() {
        if let Some(ref mut op) = fmch.m_op[opnum] {
            opl_emu_fm_operator_clock(op, env_counter, lfo_raw_pm);
        }
    }
}
pub fn opl_emu_registers_fourop_enable(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0x104, 0, 6, 0)
}
pub fn opl_emu_registers_operator_map(
    regs: &OplEmuRegisters,
    dest: &mut OplEmuRegistersOperatorMapping,
) {
    let fourop = opl_emu_registers_fourop_enable(regs);
    
    dest.chan[0] = if opl_emu_bitfield(fourop, 0, 1) != 0 {
        opl_emu_registers_operator_list(0, 3, 6, 9)
    } else {
        opl_emu_registers_operator_list(0, 3, 0xff, 0xff)
    };
    
    dest.chan[1] = if opl_emu_bitfield(fourop, 1, 1) != 0 {
        opl_emu_registers_operator_list(1, 4, 7, 10)
    } else {
        opl_emu_registers_operator_list(1, 4, 0xff, 0xff)
    };
    
    dest.chan[2] = if opl_emu_bitfield(fourop, 2, 1) != 0 {
        opl_emu_registers_operator_list(2, 5, 8, 11)
    } else {
        opl_emu_registers_operator_list(2, 5, 0xff, 0xff)
    };
    
    dest.chan[3] = if opl_emu_bitfield(fourop, 0, 1) != 0 {
        opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff)
    } else {
        opl_emu_registers_operator_list(6, 9, 0xff, 0xff)
    };
    
    dest.chan[4] = if opl_emu_bitfield(fourop, 1, 1) != 0 {
        opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff)
    } else {
        opl_emu_registers_operator_list(7, 10, 0xff, 0xff)
    };
    
    dest.chan[5] = if opl_emu_bitfield(fourop, 2, 1) != 0 {
        opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff)
    } else {
        opl_emu_registers_operator_list(8, 11, 0xff, 0xff)
    };
    
    dest.chan[6] = opl_emu_registers_operator_list(12, 15, 0xff, 0xff);
    dest.chan[7] = opl_emu_registers_operator_list(13, 16, 0xff, 0xff);
    dest.chan[8] = opl_emu_registers_operator_list(14, 17, 0xff, 0xff);
    
    dest.chan[9] = if opl_emu_bitfield(fourop, 3, 1) != 0 {
        opl_emu_registers_operator_list(18, 21, 24, 27)
    } else {
        opl_emu_registers_operator_list(18, 21, 0xff, 0xff)
    };
    
    dest.chan[10] = if opl_emu_bitfield(fourop, 4, 1) != 0 {
        opl_emu_registers_operator_list(19, 22, 25, 28)
    } else {
        opl_emu_registers_operator_list(19, 22, 0xff, 0xff)
    };
    
    dest.chan[11] = if opl_emu_bitfield(fourop, 5, 1) != 0 {
        opl_emu_registers_operator_list(20, 23, 26, 29)
    } else {
        opl_emu_registers_operator_list(20, 23, 0xff, 0xff)
    };
    
    dest.chan[12] = if opl_emu_bitfield(fourop, 3, 1) != 0 {
        opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff)
    } else {
        opl_emu_registers_operator_list(24, 27, 0xff, 0xff)
    };
    
    dest.chan[13] = if opl_emu_bitfield(fourop, 4, 1) != 0 {
        opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff)
    } else {
        opl_emu_registers_operator_list(25, 28, 0xff, 0xff)
    };
    
    dest.chan[14] = if opl_emu_bitfield(fourop, 5, 1) != 0 {
        opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff)
    } else {
        opl_emu_registers_operator_list(26, 29, 0xff, 0xff)
    };
    
    dest.chan[15] = opl_emu_registers_operator_list(30, 33, 0xff, 0xff);
    dest.chan[16] = opl_emu_registers_operator_list(31, 34, 0xff, 0xff);
    dest.chan[17] = opl_emu_registers_operator_list(32, 35, 0xff, 0xff);
}
pub fn opl_emu_fm_channel_assign(fmch: &mut OplEmuFmChannel, index: usize, op: Option<Box<OplEmuFmOperator>>) {
    fmch.m_op[index] = op;
    if let Some(mut op) = fmch.m_op[index].take() {
        opl_emu_fm_operator_set_choffs(&mut op, fmch.m_choffs);
        fmch.m_op[index] = Some(op);
    }
}
pub fn opl_emu_assign_operators(emu: &mut OplEmuT) {
    let mut map = OplEmuRegistersOperatorMapping { chan: [0; 18] };
    opl_emu_registers_operator_map(&emu.m_regs, &mut map);

    for chnum in 0..18 {
        for index in 0..4 {
            let opnum = opl_emu_bitfield(map.chan[chnum], 8 * index as i32, 8);
            let operator = if opnum == 0xff {
                Option::None
            } else {
                Some(Box::new(emu.m_operator[opnum as usize].clone()))
            };
            opl_emu_fm_channel_assign(&mut emu.m_channel[chnum], index, operator);
        }
    }
}

pub fn opl_emu_clock(emu: &mut OplEmuT, chanmask: u32) -> u32 {
    if (emu.m_modified_channels != 0) || (emu.m_prepare_count >= 4096) {
        opl_emu_assign_operators(emu);
        emu.m_active_channels = 0;
        
        for chnum in 0..18 {
            if opl_emu_bitfield(chanmask, chnum as i32, 1) != 0 {
                if opl_emu_fm_channel_prepare(&mut emu.m_channel[chnum]) {
                    emu.m_active_channels |= 1 << chnum;
                }
            }
        }
        
        emu.m_modified_channels = 0;
        emu.m_prepare_count = 0;
    }
    
    emu.m_env_counter += 4;
    let lfo_raw_pm = opl_emu_registers_clock_noise_and_lfo(&mut emu.m_regs);
    
    for chnum in 0..18 {
        if opl_emu_bitfield(chanmask, chnum as i32, 1) != 0 {
            opl_emu_fm_channel_clock(&mut emu.m_channel[chnum], emu.m_env_counter, lfo_raw_pm);
        }
    }
    
    emu.m_env_counter
}
pub fn opl_emu_generate(emu: &mut OplEmuT, output: &mut [i16], numsamples: u32, volume: f32) {
    let volume = volume.clamp(0.0, 1.0);
    
    for samp in 0..numsamples {
        let output_index = (samp * 2) as usize;
        if output_index + 1 >= output.len() {
            break;
        }
        
        opl_emu_clock(emu, (1 << 18) - 1);
        opl_emu_out(emu, &mut output[output_index..], 0, 32767, (1 << 18) - 1);
        
        output[output_index] = (output[output_index] as f32 * volume) as i16;
        output[output_index + 1] = (output[output_index + 1] as f32 * volume) as i16;
    }
}
pub fn opl_render(opl: &mut OplT, sample_pairs: &mut [i16], sample_pairs_count: u32, volume: f32) {
    // Clear the buffer (equivalent to memset in C)
    sample_pairs.fill(0);
    
    // Call the emulator function
    opl_emu_generate(&mut opl.opl_emu, sample_pairs, sample_pairs_count, volume);
}
pub fn opl_emu_registers_timer_a_value(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0x02, 0, 8, 0) * 4
}
pub fn opl_emu_registers_timer_b_value(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0x03, 0, 8, 0)
}
pub fn opl_emu_registers_status_mask(regs: &OplEmuRegisters) -> u32 {
    opl_emu_registers_byte(regs, 0x04, 0, 8, 0) & 0x78
}
pub fn opl_emu_registers_is_rhythm(regs: &OplEmuRegisters, choffs: u32) -> bool {
    opl_emu_registers_rhythm_enable(regs) != 0 && (choffs >= 6 && choffs <= 8)
}

pub fn opl_emu_fm_operator_init(
    fmop: &mut OplEmuFmOperator,
    regs: Option<Box<OplEmuRegisters>>,
    opoffs: u32,
) {
    fmop.m_choffs = 0;
    fmop.m_opoffs = opoffs;
    fmop.m_phase = 0;
    fmop.m_env_attenuation = 0x3ff;
    fmop.m_env_state = OplEmuEnvelopeState::OPL_EMU_EG_RELEASE;
    fmop.m_key_state = 0;
    fmop.m_keyon_live = 0;
    fmop.m_regs = regs;
    fmop.m_cache.eg_shift = 0;
}
pub fn opl_emu_fm_channel_init(fmch: &mut OplEmuFmChannel, regs: Option<Box<OplEmuRegisters>>, choffs: u32) {
    fmch.m_choffs = choffs;
    fmch.m_feedback = [0, 0];
    fmch.m_feedback_in = 0;
    fmch.m_op = [None, None, None, None];
    fmch.m_regs = regs;
}
pub fn opl_emu_set_reset_status(emu: &mut OplEmuT, set: u8, reset: u8) -> u8 {
    emu.m_status = (emu.m_status | set) & (!reset);
    emu.m_status & (!(opl_emu_registers_status_mask(&emu.m_regs) as u8))
}
pub fn opl_midi_controller(opl: &mut OplT, channel: i32, id: i32, value: i32) {
    match id {
        11 => {
            opl.channelvol[channel as usize] = value as u16;
        }
        123 | 120 => {
            let voicescount = VOICESCOUNT.load(Ordering::Relaxed);
            for x in 0..voicescount {
                if i32::from(opl.voices2notes[x as usize].channel) != channel {
                    continue;
                }
                opl_midi_noteoff(
                    opl, 
                    channel, 
                    i32::from(opl.voices2notes[x as usize].note)
                );
            }
        }
        _ => {}
    }
}
pub fn opl_emu_registers_init(regs: &mut OplEmuRegisters) {
    regs.m_lfo_am_counter = 0;
    regs.m_lfo_pm_counter = 0;
    regs.m_noise_lfsr = 1;
    regs.m_lfo_am = 0;

    // Initialize waveform 0
    for index in 0..0x400 {
        regs.m_waveform[0][index] = (opl_emu_abs_sin_attenuation(index as u32) | (opl_emu_bitfield(index as u32, 9, 1) << 15)) as u16;
    }

    let zeroval = regs.m_waveform[0][0];
    
    // Initialize waveforms 1-7
    for index in 0..0x400 {
        // Waveform 1
        regs.m_waveform[1][index] = if opl_emu_bitfield(index as u32, 9, 1) != 0 {
            zeroval
        } else {
            regs.m_waveform[0][index]
        };

        // Waveform 2
        regs.m_waveform[2][index] = regs.m_waveform[0][index] & 0x7fff;

        // Waveform 3
        regs.m_waveform[3][index] = if opl_emu_bitfield(index as u32, 8, 1) != 0 {
            zeroval
        } else {
            regs.m_waveform[0][index] & 0x7fff
        };

        // Waveforms 4-7 (only if 8 >= 8)
        regs.m_waveform[4][index] = if opl_emu_bitfield(index as u32, 9, 1) != 0 {
            zeroval
        } else {
            regs.m_waveform[0][index * 2]
        };

        regs.m_waveform[5][index] = if opl_emu_bitfield(index as u32, 9, 1) != 0 {
            zeroval
        } else {
            regs.m_waveform[0][(index * 2) & 0x1ff]
        };

        regs.m_waveform[6][index] = (opl_emu_bitfield(index as u32, 9, 1) << 15) as u16;

        regs.m_waveform[7][index] = if opl_emu_bitfield(index as u32, 9, 1) != 0 {
            ((index ^ 0x13ff) << 3) as u16
        } else {
            (index << 3) as u16
        };
    }
}
pub fn opl_emu_registers_ch_output_2(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(regs, 0xc0 + choffs, 6, 1, 0)
    } else {
        0
    }
}
pub fn opl_emu_registers_ch_output_3(regs: &OplEmuRegisters, choffs: u32) -> u32 {
    if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(regs, 0xc0 + choffs, 7, 1, 0)
    } else {
        0
    }
}
pub fn opl_emu_update_timer(emu: &mut OplEmuT, tnum: u32, enable: u32) {
    if enable != 0 && emu.m_timer_running[tnum as usize] == 0 {
        let period = if tnum == 0 {
            1024 - opl_emu_registers_timer_a_value(&emu.m_regs)
        } else {
            16 * (256 - opl_emu_registers_timer_b_value(&emu.m_regs))
        };
        emu.m_timer_running[tnum as usize] = 1;
    } else if enable == 0 {
        emu.m_timer_running[tnum as usize] = 0;
    }
}

pub fn opl_clear(opl: &mut OplT) {
    // First loop: note off all voices
    let voicescount = VOICESCOUNT.load(Ordering::Relaxed);
    for x in 0..voicescount {
        opl_noteoff(opl, x as u16);
    }

    // Write to register 0xBD
    oplregwr(opl, 0xBD, 0);

    // Second loop: reset voices2notes
    for x in 0..voicescount {
        opl.voices2notes[x as usize].channel = -1;
        opl.voices2notes[x as usize].note = -1;
        opl.voices2notes[x as usize].timbreid = -1;
        opl.voices2notes[x as usize].voiceindex = 0xFF;
    }

    // Third loop: reset notes2voices
    for x in 0..16 {
        for y in 0..128 {
            opl.notes2voices[x][y][0] = -1;
            opl.notes2voices[x][y][1] = -1;
        }
    }

    // Fourth loop: set program and volume for each channel
    for x in 0..16 {
        opl_midi_changeprog(opl, x as i32, x as u8);
        opl.channelvol[x] = 127;
    }
}

pub extern "C" fn opl_destroy(opl: Option<Box<OplT>>) {
    let Some(mut opl) = opl else {
        return;
    };
    
    opl_clear(&mut *opl);
    
    for x in 0..VOICESCOUNT.load(Ordering::Relaxed) {
        oplregwr(&mut *opl, 0x40 + OP1OFFSETS[x as usize], 0x1f);
        oplregwr(&mut *opl, 0x40 + OP2OFFSETS[x as usize], 0x1f);
    }

    if (*opl).opl3 != 0 {
        oplregwr(&mut *opl, 0x105, 0);
    }
    
    // The Box will be automatically dropped when it goes out of scope
}
pub fn opl_emu_init(emu: &mut OplEmuT) {
    emu.m_env_counter = 0;
    emu.m_status = 0;
    emu.m_timer_running[0] = 0;
    emu.m_timer_running[1] = 0;
    emu.m_active_channels = (1 << 18) - 1;
    emu.m_modified_channels = (1 << 18) - 1;
    emu.m_prepare_count = 0;
    
    opl_emu_registers_init(&mut emu.m_regs);
    
    for chnum in 0..18 {
        let choffs = opl_emu_registers_channel_offset(chnum as u32);
        opl_emu_fm_channel_init(&mut emu.m_channel[chnum], Some(Box::new(emu.m_regs.clone())), choffs);
    }
    
    for opnum in 0..(18 * 2) {
        let opoffs = opl_emu_registers_operator_offset(opnum as u32);
        opl_emu_fm_operator_init(&mut emu.m_operator[opnum], Some(Box::new(emu.m_regs.clone())), opoffs);
    }
    
    opl_emu_assign_operators(emu);
}
pub fn opl_create() -> Option<Box<OplT>> {
    // Create a new OplT instance
    let mut opl = Box::new(OplT {
        notes2voices: [[[0; 2]; 128]; 16],
        channelpitch: [0; 16],
        channelvol: [0; 16],
        voices2notes: std::array::from_fn(|_| VoiceAllocT {
            note: 0,
            channel: 0,
            priority: 0,
            timbreid: 0,
            voiceindex: 0,
        }),
        channelprog: [0; 16],
        opl3: 0,
        opl_emu: unsafe { std::mem::zeroed() },
        opl_gmtimbres: unsafe { std::mem::zeroed() },
        opl_gmtimbres_voice2: unsafe { std::mem::zeroed() },
        is_op2: 0,
        op2_flags: unsafe { std::mem::zeroed() },
    });

    // Copy default timbres
    let default_timbres = OPL_GMTIMBRES_DEFAULT.lock().unwrap();
    for i in 0..256 {
        opl.opl_gmtimbres[i] = default_timbres[i].clone();
    }

    // Initialize OPL emulator
    opl_emu_init(&mut opl.opl_emu);

    // Set initial registers
    oplregwr(&mut opl, 0x04, 0x60);
    oplregwr(&mut opl, 0x04, 0x80);
    oplregwr(&mut opl, 0x02, 0xff);
    oplregwr(&mut opl, 0x04, 0x21);
    oplregwr(&mut opl, 0x04, 0x60);
    oplregwr(&mut opl, 0x04, 0x80);
    
    opl.opl3 = 1;
    VOICESCOUNT.store(9, Ordering::Relaxed);

    if opl.opl3 != 0 {
        oplregwr(&mut opl, 0x105, 1);
        oplregwr(&mut opl, 0x104, 0);
        VOICESCOUNT.store(18, Ordering::Relaxed);
    }

    oplregwr(&mut opl, 0x01, 0x20);
    oplregwr(&mut opl, 0x04, 0x00);
    oplregwr(&mut opl, 0x08, 0x40);
    oplregwr(&mut opl, 0xBD, 0x00);

    let voicescount = VOICESCOUNT.load(Ordering::Relaxed);
    for x in 0..voicescount as usize {
        oplregwr(&mut opl, 0x20 + OP1OFFSETS[x], 0x1);
        oplregwr(&mut opl, 0x20 + OP2OFFSETS[x], 0x1);
        oplregwr(&mut opl, 0x40 + OP1OFFSETS[x], 0x10);
        oplregwr(&mut opl, 0x40 + OP2OFFSETS[x], 0x10);
    }

    opl_clear(&mut opl);
    Some(opl)
}
pub fn test_create_destroy() -> i32 {
    let opl = opl_create();
    if opl.is_none() {
        println!("Assertion failed: {} is false at {}:{}", "opl != NULL", "/c2rust_final/subjects/opl/test.c", 19);
        return 1;
    }
    opl_destroy(opl);
    0
}
pub fn test_multiple_create_destroy() -> i32 {
    for i in 0..1000 {
        let opl = opl_create();
        if opl.is_none() {
            println!("Failed to create opl at iteration {}", i);
            return 1;
        }
        opl_destroy(opl);
    }

    0
}
pub fn opl_midi_pitchwheel(opl: &mut OplT, channel: i32, pitchwheel: i32) {
    let voicescount = VOICESCOUNT.load(Ordering::Relaxed) as usize;
    
    for x in 0..voicescount {
        if opl.voices2notes[x].channel as i32 != channel {
            continue;
        }
        
        let timbre = if opl.voices2notes[x].voiceindex == 0 {
            &opl.opl_gmtimbres[opl.voices2notes[x].timbreid as usize]
        } else {
            &opl.opl_gmtimbres_voice2[opl.voices2notes[x].timbreid as usize]
        };
        
        opl_noteon(
            opl,
            x as u16,
            (opl.voices2notes[x].note as i32 + timbre.noteoffset as i32) as u32,
            pitchwheel + timbre.finetune as i32,
        );
    }
}
pub fn opl_write(opl: &mut OplT, count: usize, regs: &[u16], data: &[u8]) {
    let emu = &mut opl.opl_emu;
    
    for i in 0..count {
        let regnum = regs[i];
        let value = data[i];
        
        if regnum == 0x04 {
            continue;
        }
        
        emu.m_modified_channels = (1 << 18) - 1;
        
        let mut keyon_channel = None;
        let mut keyon_opmask = None;
        
        if opl_emu_registers_write(
            &mut emu.m_regs,
            regnum,
            value,
            &mut keyon_channel,
            &mut keyon_opmask,
        ) != 0
        {
            match keyon_channel {
                Some(ch) if ch < 18 => {
                    opl_emu_fm_channel_keyonoff(
                        &mut emu.m_channel[ch as usize],
                        keyon_opmask.unwrap(),
                        OplEmuKeyonType::OPL_EMU_KEYON_NORMAL,
                        ch,
                    );
                }
                Some(0xff) if 18 >= 9 => {
                    let opmask = keyon_opmask.unwrap();
                    opl_emu_fm_channel_keyonoff(
                        &mut emu.m_channel[6],
                        if opl_emu_bitfield(opmask, 4, 1) != 0 { 3 } else { 0 },
                        OplEmuKeyonType::OPL_EMU_KEYON_RHYTHM,
                        6,
                    );
                    opl_emu_fm_channel_keyonoff(
                        &mut emu.m_channel[7],
                        opl_emu_bitfield(opmask, 0, 1) | (opl_emu_bitfield(opmask, 3, 1) << 1),
                        OplEmuKeyonType::OPL_EMU_KEYON_RHYTHM,
                        7,
                    );
                    opl_emu_fm_channel_keyonoff(
                        &mut emu.m_channel[8],
                        opl_emu_bitfield(opmask, 2, 1) | (opl_emu_bitfield(opmask, 1, 1) << 1),
                        OplEmuKeyonType::OPL_EMU_KEYON_RHYTHM,
                        8,
                    );
                }
                _ => {}
            }
        }
    }
}
pub fn test_register_write_normal() -> i32 {
    let opl = opl_create();
    let regs = [0x20, 0x40, 0x60, 0x80, 0xE0];
    let data = [0x00, 0x3F, 0x00, 0x01, 0xFF];
    
    if let Some(mut opl) = opl {
        opl_write(&mut opl, 5, &regs, &data);
        opl_destroy(Some(opl));
    }
    
    0
}
pub fn test_register_write_edge() -> i32 {
    let opl = opl_create();
    let regs = [0x00, 0xFF, 0x7F, 0xC0];
    let data = [0x00, 0xFF, 0x7F, 0x00];
    
    if let Some(mut opl) = opl {
        opl_write(&mut opl, 4, &regs, &data);
        opl_destroy(Some(opl));
    }
    
    0
}
pub fn test_register_write_illegal() -> i32 {
    let opl = opl_create();
    if opl.is_none() {
        return 0; // Assuming failure should still return 0 like original C code
    }
    let mut opl = opl.unwrap();

    let regs = [0x100, 0xFFFF];
    let data = [0x01, 0xFF];

    opl_write(&mut opl, 2, &regs, &data);
    opl_destroy(Some(opl));
    
    0
}

pub fn test_pitch_wheel_bounds() -> i32 {
    let opl = opl_create();
    if opl.is_none() {
        println!("Assertion failed: {} is false at {}:{}", "opl != NULL", "/c2rust_final/subjects/opl/test.c", 155);
        return 1;
    }
    let mut opl = opl.unwrap();

    opl_midi_pitchwheel(&mut opl, 0, 0);
    opl_midi_pitchwheel(&mut opl, 0, 8192);
    opl_midi_pitchwheel(&mut opl, 0, 16383);
    opl_midi_pitchwheel(&mut opl, 0, 20000);

    opl_destroy(Some(opl));
    0
}
pub fn test_audio_generation_stress() -> i32 {
    let mut opl = match opl_create() {
        Some(opl) => opl,
        None => return 1, // Return error if OPL creation fails
    };

    let mut buffer = [0i16; 512];
    let mut result = 0;

    for i in 0..100 {
        let reg = (0x20 + (i % 0x80)) as u16;
        let val = (i % 0x100) as u8;

        opl_write(&mut opl, 1, &[reg], &[val]);
        opl_render(&mut opl, &mut buffer, 256, 1.0);

        for j in 0..256 {
            if buffer[j] < -32768 || buffer[j] > 32767 {
                println!(
                    "Audio sample out of range at iteration {} sample {}: {}",
                    i, j, buffer[j]
                );
                opl_destroy(Some(opl));
                return 1;
            }
        }
    }

    opl_destroy(Some(opl));
    0
}
pub fn opl_emu_reset(emu: &mut OplEmuT) {
    opl_emu_set_reset_status(emu, 0, 0xff);
    opl_emu_registers_reset(&mut emu.m_regs);
    opl_emu_write(emu, 0x04, 0);
    
    for channel in emu.m_channel.iter_mut() {
        opl_emu_fm_channel_reset(channel);
    }
    
    for operator in emu.m_operator.iter_mut() {
        opl_emu_fm_operator_reset(operator);
    }
}
pub fn test_midi_functions() -> i32 {
    let opl = opl_create();
    
    // Check if opl is Some (not None)
    if opl.is_none() {
        println!("Assertion failed: {} is false at {}:{}", "opl != NULL", "/c2rust_final/subjects/opl/test.c", 99);
        return 1;
    }

    // Unwrap the Option safely (we know it's Some from the check above)
    let mut opl = opl.unwrap();

    // Perform MIDI operations
    opl_midi_noteon(&mut opl, 0, 0, 0);
    opl_midi_noteon(&mut opl, 15, 127, 127);
    opl_midi_noteoff(&mut opl, 0, 0);
    opl_midi_noteoff(&mut opl, 15, 127);
    opl_midi_pitchwheel(&mut opl, 0, 0);
    opl_midi_pitchwheel(&mut opl, 15, 16383);
    opl_midi_controller(&mut opl, 0, 0, 0);
    opl_midi_controller(&mut opl, 15, 127, 127);
    opl_midi_changeprog(&mut opl, 0, 0);
    opl_midi_changeprog(&mut opl, 15, 127);

    // Destroy the OPL instance
    opl_destroy(Some(opl));

    0
}
pub fn test_instrument_and_complex_midi() -> i32 {
    // Create OPL instance, using Option to handle potential NULL case
    let mut opl = match opl_create() {
        Some(opl) => opl,
        None => {
            println!("Assertion failed: {} is false at {}:{}", "opl != NULL", "/c2rust_final/subjects/opl/test.c", 122);
            return 1;
        }
    };

    // Initialize timbre
    let timbre = OplTimbreT {
        modulator_e862: 123456,
        carrier_e862: 654321,
        modulator_40: 0x20,
        carrier_40: 0x40,
        feedconn: 1,
        finetune: 2,
        notenum: 60,
        noteoffset: 0,
    };

    // Perform OPL operations with mutable borrows
    opl_loadinstrument(&mut opl, 0, &timbre);
    opl_midi_changeprog(&mut opl, 0, 0);
    opl_midi_noteon(&mut opl, 0, 60, 127);
    opl_midi_pitchwheel(&mut opl, 0, 8192);
    opl_midi_controller(&mut opl, 0, 7, 100);

    // Render audio
    let mut buffer = [0i16; 128];
    opl_render(&mut opl, &mut buffer, 128, 0.5f32);
    opl_midi_noteoff(&mut opl, 0, 60);

    // Cleanup
    opl_clear(&mut opl);
    opl_destroy(Some(opl));

    0
}
