use crate::*;

#[derive(Clone)]
pub struct Aptx_Context {
    pub decode_sync_packets: usize,
    pub decode_dropped: usize,
    pub channels: [Aptx_Channel; 2],  // NB_CHANNELS is typically 2 for stereo in aptX
    pub hd: u8,
    pub sync_idx: u8,
    pub encode_remaining: u8,
    pub decode_skip_leading: u8,
    pub decode_sync_buffer_len: u8,
    pub decode_sync_buffer: [u8; 6],
}

