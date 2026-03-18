use crate::*;

#[derive(Clone)]
pub struct OplEmuFmChannel {
    pub m_choffs: u32,
    pub m_feedback: [i16; 2],
    pub m_feedback_in: i16,
    pub m_op: [Option<Box<OplEmuFmOperator>>; 4],
    pub m_regs: Option<Box<OplEmuRegisters>>,
}

