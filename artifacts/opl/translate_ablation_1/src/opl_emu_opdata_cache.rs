use crate::*;

#[derive(Clone)]
pub struct OplEmuOpdataCache {
    pub waveform: Option<Vec<u16>>,
    pub phase_step: u32,
    pub total_level: u32,
    pub block_freq: u32,
    pub detune: i32,
    pub multiple: u32,
    pub eg_sustain: u32,
    pub eg_rate: [u8; 4],  // Assuming OPL_EMU_EG_STATES is 4 (Attack, Decay, Sustain, Release)
    pub eg_shift: u8,
}

