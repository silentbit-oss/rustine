use crate::*;

#[derive(Clone)]
pub struct OplT {
    pub notes2voices: [[[i8; 2]; 128]; 16],
    pub channelpitch: [u16; 16],
    pub channelvol: [u16; 16],
    pub voices2notes: [VoiceAllocT; 18],
    pub channelprog: [u8; 16],
    pub opl3: i32,
    pub opl_emu: OplEmuT,
    pub opl_gmtimbres: [OplTimbreT; 256],
    pub opl_gmtimbres_voice2: [OplTimbreT; 256],
    pub is_op2: i32,
    pub op2_flags: [Op2FlagsT; 256],
}

