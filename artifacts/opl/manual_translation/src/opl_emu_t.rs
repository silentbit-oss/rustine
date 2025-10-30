use crate::*;

#[derive(Clone)]
pub struct OplEmuT {
    pub m_env_counter: u32,
    pub m_status: u8,
    pub m_timer_running: [u8; 2],
    pub m_active_channels: u32,
    pub m_modified_channels: u32,
    pub m_prepare_count: u32,
    pub m_regs: OplEmuRegisters,
    pub m_channel: [OplEmuFmChannel; 18],
    pub m_operator: [OplEmuFmOperator; 18 * 2],
}

