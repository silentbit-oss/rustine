use crate::*;

#[derive(Clone)]
pub struct VoiceAllocT {
    pub priority: u16,
    pub timbreid: i16,
    pub channel: i8,
    pub note: i8,
    pub voiceindex: u8,
}

