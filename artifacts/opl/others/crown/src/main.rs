use ::libc;
extern "C" {
    pub type _IO_wide_data;
    pub type _IO_codecvt;
    pub type _IO_marker;
    fn fclose(__stream: *mut FILE) -> libc::c_int;
    fn fopen(_: *const libc::c_char, _: *const libc::c_char) -> *mut FILE;
    fn fread(
        _: *mut libc::c_void,
        _: libc::c_ulong,
        _: libc::c_ulong,
        _: *mut FILE,
    ) -> libc::c_ulong;
    fn fseek(
        __stream: *mut FILE,
        __off: libc::c_long,
        __whence: libc::c_int,
    ) -> libc::c_int;
    fn ftell(__stream: *mut FILE) -> libc::c_long;
    fn calloc(_: libc::c_ulong, _: libc::c_ulong) -> *mut libc::c_void;
    fn free(_: *mut libc::c_void);
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn memset(
        _: *mut libc::c_void,
        _: libc::c_int,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strdup(_: *const libc::c_char) -> *mut libc::c_char;
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_timbre_t {
    pub modulator_E862: libc::c_ulong,
    pub carrier_E862: libc::c_ulong,
    pub modulator_40: libc::c_uchar,
    pub carrier_40: libc::c_uchar,
    pub feedconn: libc::c_uchar,
    pub finetune: libc::c_schar,
    pub notenum: libc::c_uchar,
    pub noteoffset: libc::c_short,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_t {
    pub notes2voices: [[[libc::c_schar; 2]; 128]; 16],
    pub channelpitch: [libc::c_ushort; 16],
    pub channelvol: [libc::c_ushort; 16],
    pub voices2notes: [voicealloc_t; 18],
    pub channelprog: [libc::c_uchar; 16],
    pub opl3: libc::c_int,
    pub opl_emu: opl_emu_t,
    pub opl_gmtimbres: [opl_timbre_t; 256],
    pub opl_gmtimbres_voice2: [opl_timbre_t; 256],
    pub is_op2: libc::c_int,
    pub op2_flags: [op2_flags_t; 256],
}
pub type op2_flags_t = libc::c_uint;
pub const OP2_DOUBLEVOICE: op2_flags_t = 4;
pub const OP2_UNUSED: op2_flags_t = 2;
pub const OP2_FIXEDPITCH: op2_flags_t = 1;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_emu_t {
    pub m_env_counter: uint32_t,
    pub m_status: uint8_t,
    pub m_timer_running: [uint8_t; 2],
    pub m_active_channels: uint32_t,
    pub m_modified_channels: uint32_t,
    pub m_prepare_count: uint32_t,
    pub m_regs: opl_emu_registers,
    pub m_channel: [opl_emu_fm_channel; 18],
    pub m_operator: [opl_emu_fm_operator; 36],
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_emu_fm_operator {
    pub m_choffs: uint32_t,
    pub m_opoffs: uint32_t,
    pub m_phase: uint32_t,
    pub m_env_attenuation: uint16_t,
    pub m_env_state: opl_emu_envelope_state,
    pub m_key_state: uint8_t,
    pub m_keyon_live: uint8_t,
    pub m_cache: opl_emu_opdata_cache,
    pub m_regs: *mut opl_emu_registers,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_emu_registers {
    pub m_lfo_am_counter: uint16_t,
    pub m_lfo_pm_counter: uint16_t,
    pub m_noise_lfsr: uint32_t,
    pub m_lfo_am: uint8_t,
    pub m_regdata: [uint8_t; 512],
    pub m_waveform: [[uint16_t; 1024]; 8],
}
pub type uint16_t = __uint16_t;
pub type __uint16_t = libc::c_ushort;
pub type uint8_t = __uint8_t;
pub type __uint8_t = libc::c_uchar;
pub type uint32_t = __uint32_t;
pub type __uint32_t = libc::c_uint;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_emu_opdata_cache {
    pub waveform: *const uint16_t,
    pub phase_step: uint32_t,
    pub total_level: uint32_t,
    pub block_freq: uint32_t,
    pub detune: int32_t,
    pub multiple: uint32_t,
    pub eg_sustain: uint32_t,
    pub eg_rate: [uint8_t; 6],
    pub eg_shift: uint8_t,
}
pub type int32_t = __int32_t;
pub type __int32_t = libc::c_int;
pub type opl_emu_envelope_state = libc::c_uint;
pub const OPL_EMU_EG_STATES: opl_emu_envelope_state = 6;
pub const OPL_EMU_EG_RELEASE: opl_emu_envelope_state = 4;
pub const OPL_EMU_EG_SUSTAIN: opl_emu_envelope_state = 3;
pub const OPL_EMU_EG_DECAY: opl_emu_envelope_state = 2;
pub const OPL_EMU_EG_ATTACK: opl_emu_envelope_state = 1;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_emu_fm_channel {
    pub m_choffs: uint32_t,
    pub m_feedback: [int16_t; 2],
    pub m_feedback_in: int16_t,
    pub m_op: [*mut opl_emu_fm_operator; 4],
    pub m_regs: *mut opl_emu_registers,
}
pub type int16_t = __int16_t;
pub type __int16_t = libc::c_short;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct voicealloc_t {
    pub priority: libc::c_ushort,
    pub timbreid: libc::c_short,
    pub channel: libc::c_schar,
    pub note: libc::c_schar,
    pub voiceindex: libc::c_uchar,
}
pub type opl_emu_keyon_type = libc::c_uint;
pub const OPL_EMU_KEYON_CSM: opl_emu_keyon_type = 2;
pub const OPL_EMU_KEYON_RHYTHM: opl_emu_keyon_type = 1;
pub const OPL_EMU_KEYON_NORMAL: opl_emu_keyon_type = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct opl_emu_registers_operator_mapping {
    pub chan: [uint32_t; 18],
}
pub type FILE = _IO_FILE;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct _IO_FILE {
    pub _flags: libc::c_int,
    pub _IO_read_ptr: *mut libc::c_char,
    pub _IO_read_end: *mut libc::c_char,
    pub _IO_read_base: *mut libc::c_char,
    pub _IO_write_base: *mut libc::c_char,
    pub _IO_write_ptr: *mut libc::c_char,
    pub _IO_write_end: *mut libc::c_char,
    pub _IO_buf_base: *mut libc::c_char,
    pub _IO_buf_end: *mut libc::c_char,
    pub _IO_save_base: *mut libc::c_char,
    pub _IO_backup_base: *mut libc::c_char,
    pub _IO_save_end: *mut libc::c_char,
    pub _markers: *mut _IO_marker,
    pub _chain: *mut _IO_FILE,
    pub _fileno: libc::c_int,
    pub _flags2: libc::c_int,
    pub _old_offset: __off_t,
    pub _cur_column: libc::c_ushort,
    pub _vtable_offset: libc::c_schar,
    pub _shortbuf: [libc::c_char; 1],
    pub _lock: *mut libc::c_void,
    pub _offset: __off64_t,
    pub _codecvt: *mut _IO_codecvt,
    pub _wide_data: *mut _IO_wide_data,
    pub _freeres_list: *mut _IO_FILE,
    pub _freeres_buf: *mut libc::c_void,
    pub __pad5: size_t,
    pub _mode: libc::c_int,
    pub _unused2: [libc::c_char; 20],
}
pub type size_t = libc::c_ulong;
pub type __off64_t = libc::c_long;
pub type _IO_lock_t = ();
pub type __off_t = libc::c_long;
pub type int8_t = __int8_t;
pub type __int8_t = libc::c_schar;
#[no_mangle]
pub unsafe extern "C" fn opl_emu_bitfield(
    mut value: uint32_t,
    mut start: libc::c_int,
    mut length: libc::c_int,
) -> uint32_t {
    return value >> start
        & (((1 as libc::c_int) << length) - 1 as libc::c_int) as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_clamp(
    mut value: int32_t,
    mut minval: int32_t,
    mut maxval: int32_t,
) -> int32_t {
    if value < minval {
        return minval;
    }
    if value > maxval {
        return maxval;
    }
    return value;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_operator_list(
    mut o1: uint8_t,
    mut o2: uint8_t,
    mut o3: uint8_t,
    mut o4: uint8_t,
) -> uint32_t {
    return (o1 as libc::c_int | (o2 as libc::c_int) << 8 as libc::c_int
        | (o3 as libc::c_int) << 16 as libc::c_int
        | (o4 as libc::c_int) << 24 as libc::c_int) as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_effective_rate(
    mut rawrate: uint32_t,
    mut ksr: uint32_t,
) -> uint32_t {
    return if rawrate == 0 as libc::c_int as uint32_t {
        0 as libc::c_int as uint32_t
    } else if rawrate.wrapping_add(ksr) < 63 as libc::c_int as uint32_t {
        rawrate.wrapping_add(ksr)
    } else {
        63 as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_channel_offset(
    mut chnum: uint32_t,
) -> uint32_t {
    return (chnum % 9 as libc::c_int as uint32_t)
        .wrapping_add(
            0x100 as libc::c_int as uint32_t * (chnum / 9 as libc::c_int as uint32_t),
        );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_operator_offset(
    mut opnum: uint32_t,
) -> uint32_t {
    return (opnum % 18 as libc::c_int as uint32_t)
        .wrapping_add(
            2 as libc::c_int as uint32_t
                * (opnum % 18 as libc::c_int as uint32_t / 6 as libc::c_int as uint32_t),
        )
        .wrapping_add(
            0x100 as libc::c_int as uint32_t * (opnum / 18 as libc::c_int as uint32_t),
        );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_reset_lfo(mut regs: *mut opl_emu_registers) {
    (*regs).m_lfo_pm_counter = 0 as libc::c_int as uint16_t;
    (*regs).m_lfo_am_counter = (*regs).m_lfo_pm_counter;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_lfo_am_offset(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return (*regs).m_lfo_am as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_noise_state(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return (*regs).m_noise_lfsr >> 23 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_byte(
    mut regs: *mut opl_emu_registers,
    mut offset: uint32_t,
    mut start: uint32_t,
    mut count: uint32_t,
    mut extra_offset: uint32_t,
) -> uint32_t {
    return opl_emu_bitfield(
        (*regs).m_regdata[offset.wrapping_add(extra_offset) as usize] as uint32_t,
        start as libc::c_int,
        count as libc::c_int,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_word(
    mut regs: *mut opl_emu_registers,
    mut offset1: uint32_t,
    mut start1: uint32_t,
    mut count1: uint32_t,
    mut offset2: uint32_t,
    mut start2: uint32_t,
    mut count2: uint32_t,
    mut extra_offset: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(regs, offset1, start1, count1, extra_offset) << count2
        | opl_emu_registers_byte(regs, offset2, start2, count2, extra_offset);
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_timer_a_value(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x2 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        8 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    ) * 4 as libc::c_int as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_timer_b_value(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x3 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        8 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_status_mask(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x4 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        8 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    ) & 0x78 as libc::c_int as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_note_select(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x8 as libc::c_int as uint32_t,
        6 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_lfo_am_depth(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0xbd as libc::c_int as uint32_t,
        7 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_lfo_pm_depth(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0xbd as libc::c_int as uint32_t,
        6 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_rhythm_enable(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0xbd as libc::c_int as uint32_t,
        5 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_newflag(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x105 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_fourop_enable(
    mut regs: *mut opl_emu_registers,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x104 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        6 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_block_freq(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_word(
        regs,
        0xb0 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        5 as libc::c_int as uint32_t,
        0xa0 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        8 as libc::c_int as uint32_t,
        choffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_feedback(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0xc0 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        3 as libc::c_int as uint32_t,
        choffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_algorithm(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0xc0 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        choffs,
    )
        | (8 as libc::c_int as uint32_t
            | opl_emu_registers_byte(
                regs,
                0xc3 as libc::c_int as uint32_t,
                0 as libc::c_int as uint32_t,
                1 as libc::c_int as uint32_t,
                choffs,
            ) << 1 as libc::c_int);
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_output_any(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(
            regs,
            (0xc0 as libc::c_int as uint32_t).wrapping_add(choffs),
            4 as libc::c_int as uint32_t,
            4 as libc::c_int as uint32_t,
            0 as libc::c_int as uint32_t,
        )
    } else {
        1 as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_output_0(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(
            regs,
            (0xc0 as libc::c_int as uint32_t).wrapping_add(choffs),
            4 as libc::c_int as uint32_t,
            1 as libc::c_int as uint32_t,
            0 as libc::c_int as uint32_t,
        )
    } else {
        1 as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_output_1(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(
            regs,
            (0xc0 as libc::c_int as uint32_t).wrapping_add(choffs),
            5 as libc::c_int as uint32_t,
            1 as libc::c_int as uint32_t,
            0 as libc::c_int as uint32_t,
        )
    } else {
        1 as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_output_2(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(
            regs,
            (0xc0 as libc::c_int as uint32_t).wrapping_add(choffs),
            6 as libc::c_int as uint32_t,
            1 as libc::c_int as uint32_t,
            0 as libc::c_int as uint32_t,
        )
    } else {
        0 as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_ch_output_3(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> uint32_t {
    return if opl_emu_registers_newflag(regs) != 0 {
        opl_emu_registers_byte(
            regs,
            (0xc0 as libc::c_int as uint32_t).wrapping_add(choffs),
            7 as libc::c_int as uint32_t,
            1 as libc::c_int as uint32_t,
            0 as libc::c_int as uint32_t,
        )
    } else {
        0 as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_lfo_am_enable(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x20 as libc::c_int as uint32_t,
        7 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_lfo_pm_enable(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x20 as libc::c_int as uint32_t,
        6 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_eg_sustain(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x20 as libc::c_int as uint32_t,
        5 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_ksr(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x20 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        1 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_multiple(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x20 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_ksl(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    let mut temp: uint32_t = opl_emu_registers_byte(
        regs,
        0x40 as libc::c_int as uint32_t,
        6 as libc::c_int as uint32_t,
        2 as libc::c_int as uint32_t,
        opoffs,
    );
    return opl_emu_bitfield(temp, 1 as libc::c_int, 1 as libc::c_int)
        | opl_emu_bitfield(temp, 0 as libc::c_int, 1 as libc::c_int) << 1 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_total_level(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x40 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        6 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_attack_rate(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x60 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_decay_rate(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x60 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_sustain_level(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x80 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_release_rate(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0x80 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        4 as libc::c_int as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_op_waveform(
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) -> uint32_t {
    return opl_emu_registers_byte(
        regs,
        0xe0 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        (if opl_emu_registers_newflag(regs) != 0 {
            3 as libc::c_int
        } else {
            2 as libc::c_int
        }) as uint32_t,
        opoffs,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_is_rhythm(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) -> libc::c_int {
    return (opl_emu_registers_rhythm_enable(regs) != 0
        && (choffs >= 6 as libc::c_int as uint32_t
            && choffs <= 8 as libc::c_int as uint32_t)) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_opoffs(
    mut fmop: *mut opl_emu_fm_operator,
) -> uint32_t {
    return (*fmop).m_opoffs;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_choffs(
    mut fmop: *mut opl_emu_fm_operator,
) -> uint32_t {
    return (*fmop).m_choffs;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_set_choffs(
    mut fmop: *mut opl_emu_fm_operator,
    mut choffs: uint32_t,
) {
    (*fmop).m_choffs = choffs;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_phase(
    mut fmop: *mut opl_emu_fm_operator,
) -> uint32_t {
    return (*fmop).m_phase >> 10 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_choffs(
    mut fmch: *mut opl_emu_fm_channel,
) -> uint32_t {
    return (*fmch).m_choffs;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_assign(
    mut fmch: *mut opl_emu_fm_channel,
    mut index: uint32_t,
    mut op: *mut opl_emu_fm_operator,
) {
    (*fmch).m_op[index as usize] = op;
    if !op.is_null() {
        opl_emu_fm_operator_set_choffs(op, (*fmch).m_choffs);
    }else { std::intrinsics::assume((op).addr() == 0); }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_is4op(
    mut fmch: *mut opl_emu_fm_channel,
) -> libc::c_int {
    return ((*fmch).m_op[2 as libc::c_int as usize]
        != 0 as *mut libc::c_void as *mut opl_emu_fm_operator) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_add_to_output(
    mut fmch: *mut opl_emu_fm_channel,
    mut choffs: uint32_t,
    mut output: *mut libc::c_short,
    mut value: int32_t,
) {
    let mut out0_index: libc::c_int = 0 as libc::c_int;
    let mut out1_index: libc::c_int = 1 as libc::c_int % 2 as libc::c_int;
    let mut out2_index: libc::c_int = 2 as libc::c_int % 2 as libc::c_int;
    let mut out3_index: libc::c_int = 3 as libc::c_int % 2 as libc::c_int;
    if 2 as libc::c_int == 1 as libc::c_int
        || opl_emu_registers_ch_output_0((*fmch).m_regs, choffs) != 0
    {
        let mut s: libc::c_int = *output.offset(out0_index as isize) as libc::c_int
            + value;
        *output
            .offset(
                out0_index as isize,
            ) = (if s < -(32767 as libc::c_int) {
            -(32767 as libc::c_int)
        } else if s > 32767 as libc::c_int {
            32767 as libc::c_int
        } else {
            s
        }) as libc::c_short;
    }
    if 2 as libc::c_int >= 2 as libc::c_int
        && opl_emu_registers_ch_output_1((*fmch).m_regs, choffs) != 0
    {
        let mut s_0: libc::c_int = *output.offset(out1_index as isize) as libc::c_int
            + value;
        *output
            .offset(
                out1_index as isize,
            ) = (if s_0 < -(32767 as libc::c_int) {
            -(32767 as libc::c_int)
        } else if s_0 > 32767 as libc::c_int {
            32767 as libc::c_int
        } else {
            s_0
        }) as libc::c_short;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_set_reset_status(
    mut emu: *mut opl_emu_t,
    mut set: uint8_t,
    mut reset: uint8_t,
) -> uint8_t {
    (*emu)
        .m_status = (((*emu).m_status as libc::c_int | set as libc::c_int)
        & !(reset as libc::c_int | 0 as libc::c_int)) as uint8_t;
    return ((*emu).m_status as uint32_t
        & !opl_emu_registers_status_mask(&raw mut (*emu).m_regs)) as uint8_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_init(mut emu: *mut opl_emu_t) {
    (*emu).m_env_counter = 0 as libc::c_int as uint32_t;
    (*emu).m_status = 0 as libc::c_int as uint8_t;
    (*emu).m_timer_running[0 as libc::c_int as usize] = 0 as libc::c_int as uint8_t;
    (*emu).m_timer_running[1 as libc::c_int as usize] = 0 as libc::c_int as uint8_t;
    (*emu)
        .m_active_channels = (((1 as libc::c_int) << 18 as libc::c_int)
        - 1 as libc::c_int) as uint32_t;
    (*emu)
        .m_modified_channels = (((1 as libc::c_int) << 18 as libc::c_int)
        - 1 as libc::c_int) as uint32_t;
    (*emu).m_prepare_count = 0 as libc::c_int as uint32_t;
    opl_emu_registers_init(&raw mut (*emu).m_regs);
    let mut chnum: uint32_t = 0 as libc::c_int as uint32_t;
    while chnum < 18 as libc::c_int as uint32_t {
        opl_emu_fm_channel_init(
            &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
            &raw mut (*emu).m_regs,
            opl_emu_registers_channel_offset(chnum),
        );
        chnum = chnum.wrapping_add(1);
        chnum;
    }
    let mut opnum: uint32_t = 0 as libc::c_int as uint32_t;
    while opnum < (18 as libc::c_int * 2 as libc::c_int) as uint32_t {
        opl_emu_fm_operator_init(
            &raw mut *((*emu).m_operator).as_mut_ptr().offset(opnum as isize),
            &raw mut (*emu).m_regs,
            opl_emu_registers_operator_offset(opnum),
        );
        opnum = opnum.wrapping_add(1);
        opnum;
    }
    opl_emu_assign_operators(emu);
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_reset(mut emu: *mut opl_emu_t) {
    opl_emu_set_reset_status(
        emu,
        0 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
    opl_emu_registers_reset(&raw mut (*emu).m_regs);
    opl_emu_write(emu, 0x4 as libc::c_int as uint16_t, 0 as libc::c_int as uint8_t);
    let mut i: libc::c_int = 0 as libc::c_int;
    while (i as libc::c_ulong)
        < (::core::mem::size_of::<[opl_emu_fm_channel; 18]>() as libc::c_ulong)
            .wrapping_div(::core::mem::size_of::<opl_emu_fm_channel>() as libc::c_ulong)
    {
        opl_emu_fm_channel_reset(
            &raw mut *((*emu).m_channel).as_mut_ptr().offset(i as isize),
        );
        i += 1;
        i;
    }
    let mut i_0: libc::c_int = 0 as libc::c_int;
    while (i_0 as libc::c_ulong)
        < (::core::mem::size_of::<[opl_emu_fm_operator; 36]>() as libc::c_ulong)
            .wrapping_div(::core::mem::size_of::<opl_emu_fm_operator>() as libc::c_ulong)
    {
        opl_emu_fm_operator_reset(
            &raw mut *((*emu).m_operator).as_mut_ptr().offset(i_0 as isize),
        );
        i_0 += 1;
        i_0;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_clock(
    mut emu: *mut opl_emu_t,
    mut chanmask: uint32_t,
) -> uint32_t {
    if (*emu).m_modified_channels != 0 as libc::c_int as uint32_t
        || {
            let fresh0 = (*emu).m_prepare_count;
            (*emu).m_prepare_count = ((*emu).m_prepare_count).wrapping_add(1);
            fresh0 >= 4096 as libc::c_int as uint32_t
        }
    {
        opl_emu_assign_operators(emu);
        (*emu).m_active_channels = 0 as libc::c_int as uint32_t;
        let mut chnum: uint32_t = 0 as libc::c_int as uint32_t;
        while chnum < 18 as libc::c_int as uint32_t {
            if opl_emu_bitfield(chanmask, chnum as libc::c_int, 1 as libc::c_int) != 0 {
                if opl_emu_fm_channel_prepare(
                    &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                ) != 0
                {
                    (*emu).m_active_channels
                        |= ((1 as libc::c_int) << chnum) as uint32_t;
                }
            }
            chnum = chnum.wrapping_add(1);
            chnum;
        }
        (*emu).m_prepare_count = 0 as libc::c_int as uint32_t;
        (*emu).m_modified_channels = (*emu).m_prepare_count;
    }
    (*emu)
        .m_env_counter = ((*emu).m_env_counter)
        .wrapping_add(4 as libc::c_int as uint32_t);
    let mut lfo_raw_pm: int32_t = opl_emu_registers_clock_noise_and_lfo(
        &raw mut (*emu).m_regs,
    );
    let mut chnum_0: uint32_t = 0 as libc::c_int as uint32_t;
    while chnum_0 < 18 as libc::c_int as uint32_t {
        if opl_emu_bitfield(chanmask, chnum_0 as libc::c_int, 1 as libc::c_int) != 0 {
            opl_emu_fm_channel_clock(
                &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum_0 as isize),
                (*emu).m_env_counter,
                lfo_raw_pm,
            );
        }
        chnum_0 = chnum_0.wrapping_add(1);
        chnum_0;
    }
    return (*emu).m_env_counter;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_out(
    mut emu: *mut opl_emu_t,
    mut output: *mut libc::c_short,
    mut rshift: uint32_t,
    mut clipmax: int32_t,
    mut chanmask: uint32_t,
) {
    chanmask &= (*emu).m_active_channels;
    if opl_emu_registers_rhythm_enable(&raw mut (*emu).m_regs) != 0 {
        let mut op13phase: uint32_t = opl_emu_fm_operator_phase(
            &raw mut *((*emu).m_operator).as_mut_ptr().offset(13 as libc::c_int as isize),
        );
        let mut op17phase: uint32_t = opl_emu_fm_operator_phase(
            &raw mut *((*emu).m_operator).as_mut_ptr().offset(17 as libc::c_int as isize),
        );
        let mut phase_select: uint32_t = opl_emu_bitfield(
            op13phase,
            2 as libc::c_int,
            1 as libc::c_int,
        ) ^ opl_emu_bitfield(op13phase, 7 as libc::c_int, 1 as libc::c_int)
            | opl_emu_bitfield(op13phase, 3 as libc::c_int, 1 as libc::c_int)
            | opl_emu_bitfield(op17phase, 5 as libc::c_int, 1 as libc::c_int)
                ^ opl_emu_bitfield(op17phase, 3 as libc::c_int, 1 as libc::c_int);
        let mut chnum: uint32_t = 0 as libc::c_int as uint32_t;
        while chnum < 18 as libc::c_int as uint32_t {
            if opl_emu_bitfield(chanmask, chnum as libc::c_int, 1 as libc::c_int) != 0 {
                if chnum == 6 as libc::c_int as uint32_t {
                    opl_emu_fm_channel_output_rhythm_ch6(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                        output,
                        rshift,
                        clipmax,
                    );
                } else if chnum == 7 as libc::c_int as uint32_t {
                    opl_emu_fm_channel_output_rhythm_ch7(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                        phase_select,
                        output,
                        rshift,
                        clipmax,
                    );
                } else if chnum == 8 as libc::c_int as uint32_t {
                    opl_emu_fm_channel_output_rhythm_ch8(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                        phase_select,
                        output,
                        rshift,
                        clipmax,
                    );
                } else if opl_emu_fm_channel_is4op(
                    &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                ) != 0
                {
                    opl_emu_fm_channel_output_4op(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                        output,
                        rshift,
                        clipmax,
                    );
                } else {
                    opl_emu_fm_channel_output_2op(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                        output,
                        rshift,
                        clipmax,
                    );
                }
            }
            chnum = chnum.wrapping_add(1);
            chnum;
        }
    } else {
        let mut chnum_0: uint32_t = 0 as libc::c_int as uint32_t;
        while chnum_0 < 18 as libc::c_int as uint32_t {
            if opl_emu_bitfield(chanmask, chnum_0 as libc::c_int, 1 as libc::c_int) != 0
            {
                if opl_emu_fm_channel_is4op(
                    &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum_0 as isize),
                ) != 0
                {
                    opl_emu_fm_channel_output_4op(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum_0 as isize),
                        output,
                        rshift,
                        clipmax,
                    );
                } else {
                    opl_emu_fm_channel_output_2op(
                        &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum_0 as isize),
                        output,
                        rshift,
                        clipmax,
                    );
                }
            }
            chnum_0 = chnum_0.wrapping_add(1);
            chnum_0;
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_write(
    mut emu: *mut opl_emu_t,
    mut regnum: uint16_t,
    mut data: uint8_t,
) {
    if regnum as libc::c_int == 0x4 as libc::c_int {
        return;
    }
    (*emu)
        .m_modified_channels = (((1 as libc::c_int) << 18 as libc::c_int)
        - 1 as libc::c_int) as uint32_t;
    let mut keyon_channel: uint32_t = 0;
    let mut keyon_opmask: uint32_t = 0;
    if opl_emu_registers_write(
        &raw mut (*emu).m_regs,
        regnum,
        data,
        &raw mut keyon_channel,
        &raw mut keyon_opmask,
    ) != 0
    {
        if keyon_channel < 18 as libc::c_int as uint32_t {
            opl_emu_fm_channel_keyonoff(
                &raw mut *((*emu).m_channel).as_mut_ptr().offset(keyon_channel as isize),
                keyon_opmask,
                OPL_EMU_KEYON_NORMAL,
                keyon_channel,
            );
        } else if 18 as libc::c_int >= 9 as libc::c_int
            && keyon_channel == 0xff as libc::c_int as uint32_t
        {
            opl_emu_fm_channel_keyonoff(
                &raw mut *((*emu).m_channel).as_mut_ptr().offset(6 as libc::c_int as isize),
                (if opl_emu_bitfield(keyon_opmask, 4 as libc::c_int, 1 as libc::c_int)
                    != 0
                {
                    3 as libc::c_int
                } else {
                    0 as libc::c_int
                }) as uint32_t,
                OPL_EMU_KEYON_RHYTHM,
                6 as libc::c_int as uint32_t,
            );
            opl_emu_fm_channel_keyonoff(
                &raw mut *((*emu).m_channel).as_mut_ptr().offset(7 as libc::c_int as isize),
                opl_emu_bitfield(keyon_opmask, 0 as libc::c_int, 1 as libc::c_int)
                    | opl_emu_bitfield(keyon_opmask, 3 as libc::c_int, 1 as libc::c_int)
                        << 1 as libc::c_int,
                OPL_EMU_KEYON_RHYTHM,
                7 as libc::c_int as uint32_t,
            );
            opl_emu_fm_channel_keyonoff(
                &raw mut *((*emu).m_channel).as_mut_ptr().offset(8 as libc::c_int as isize),
                opl_emu_bitfield(keyon_opmask, 2 as libc::c_int, 1 as libc::c_int)
                    | opl_emu_bitfield(keyon_opmask, 1 as libc::c_int, 1 as libc::c_int)
                        << 1 as libc::c_int,
                OPL_EMU_KEYON_RHYTHM,
                8 as libc::c_int as uint32_t,
            );
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_assign_operators(mut emu: *mut opl_emu_t) {
    let mut map: opl_emu_registers_operator_mapping = opl_emu_registers_operator_mapping {
        chan: [0; 18],
    };
    opl_emu_registers_operator_map(&raw mut (*emu).m_regs, &raw mut map);
    let mut chnum: uint32_t = 0 as libc::c_int as uint32_t;
    while chnum < 18 as libc::c_int as uint32_t {
        let mut index: uint32_t = 0 as libc::c_int as uint32_t;
        while index < 4 as libc::c_int as uint32_t {
            let mut opnum: uint32_t = opl_emu_bitfield(
                map.chan[chnum as usize],
                (8 as libc::c_int as uint32_t * index) as libc::c_int,
                8 as libc::c_int,
            );
            opl_emu_fm_channel_assign(
                &raw mut *((*emu).m_channel).as_mut_ptr().offset(chnum as isize),
                index,
                if opnum == 0xff as libc::c_int as uint32_t {
                    0 as *mut opl_emu_fm_operator
                } else {
                    &raw mut *((*emu).m_operator).as_mut_ptr().offset(opnum as isize)
                },
            );
            index = index.wrapping_add(1);
            index;
        }
        chnum = chnum.wrapping_add(1);
        chnum;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_update_timer(
    mut emu: *mut opl_emu_t,
    mut tnum: uint32_t,
    mut enable: uint32_t,
) {
    if enable != 0 && (*emu).m_timer_running[tnum as usize] == 0 {
        let mut period: uint32_t = if tnum == 0 as libc::c_int as uint32_t {
            (1024 as libc::c_int as uint32_t)
                .wrapping_sub(opl_emu_registers_timer_a_value(&raw mut (*emu).m_regs))
        } else {
            16 as libc::c_int as uint32_t
                * (256 as libc::c_int as uint32_t)
                    .wrapping_sub(opl_emu_registers_timer_b_value(&raw mut (*emu).m_regs))
        };
        (*emu).m_timer_running[tnum as usize] = 1 as libc::c_int as uint8_t;
    } else if enable == 0 {
        (*emu).m_timer_running[tnum as usize] = 0 as libc::c_int as uint8_t;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_generate(
    mut emu: *mut opl_emu_t,
    mut output: *mut libc::c_short,
    mut numsamples: uint32_t,
    mut volume: libc::c_float,
) {
    volume = if volume > 1.0f32 {
        1.0f32
    } else if volume < 0.0f32 {
        0.0f32
    } else {
        volume
    };
    let mut samp: uint32_t = 0 as libc::c_int as uint32_t;
    while samp < numsamples {
        opl_emu_clock(
            emu,
            (((1 as libc::c_int) << 18 as libc::c_int) - 1 as libc::c_int) as uint32_t,
        );
        opl_emu_out(
            emu,
            output,
            0 as libc::c_int as uint32_t,
            32767 as libc::c_int,
            (((1 as libc::c_int) << 18 as libc::c_int) - 1 as libc::c_int) as uint32_t,
        );
        *output = (*output as libc::c_int as libc::c_float * volume) as libc::c_short;
        *output
            .offset(
                1 as libc::c_int as isize,
            ) = (*output.offset(1 as libc::c_int as isize) as libc::c_int
            as libc::c_float * volume) as libc::c_short;
        samp = samp.wrapping_add(1);
        samp;
        output = output.offset(2 as libc::c_int as isize);
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_opl_key_scale_atten(
    mut block: uint32_t,
    mut fnum_4msb: uint32_t,
) -> uint32_t {
    static mut fnum_to_atten: [uint8_t; 16] = [
        0 as libc::c_int as uint8_t,
        24 as libc::c_int as uint8_t,
        32 as libc::c_int as uint8_t,
        37 as libc::c_int as uint8_t,
        40 as libc::c_int as uint8_t,
        43 as libc::c_int as uint8_t,
        45 as libc::c_int as uint8_t,
        47 as libc::c_int as uint8_t,
        48 as libc::c_int as uint8_t,
        50 as libc::c_int as uint8_t,
        51 as libc::c_int as uint8_t,
        52 as libc::c_int as uint8_t,
        53 as libc::c_int as uint8_t,
        54 as libc::c_int as uint8_t,
        55 as libc::c_int as uint8_t,
        56 as libc::c_int as uint8_t,
    ];
    let mut result: int32_t = (fnum_to_atten[fnum_4msb as usize] as uint32_t)
        .wrapping_sub(
            8 as libc::c_int as uint32_t * (block ^ 7 as libc::c_int as uint32_t),
        ) as int32_t;
    return (if 0 as libc::c_int > result { 0 as libc::c_int } else { result })
        as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_abs_sin_attenuation(mut input: uint32_t) -> uint32_t {
    static mut s_sin_table: [uint16_t; 256] = [
        0x859 as libc::c_int as uint16_t,
        0x6c3 as libc::c_int as uint16_t,
        0x607 as libc::c_int as uint16_t,
        0x58b as libc::c_int as uint16_t,
        0x52e as libc::c_int as uint16_t,
        0x4e4 as libc::c_int as uint16_t,
        0x4a6 as libc::c_int as uint16_t,
        0x471 as libc::c_int as uint16_t,
        0x443 as libc::c_int as uint16_t,
        0x41a as libc::c_int as uint16_t,
        0x3f5 as libc::c_int as uint16_t,
        0x3d3 as libc::c_int as uint16_t,
        0x3b5 as libc::c_int as uint16_t,
        0x398 as libc::c_int as uint16_t,
        0x37e as libc::c_int as uint16_t,
        0x365 as libc::c_int as uint16_t,
        0x34e as libc::c_int as uint16_t,
        0x339 as libc::c_int as uint16_t,
        0x324 as libc::c_int as uint16_t,
        0x311 as libc::c_int as uint16_t,
        0x2ff as libc::c_int as uint16_t,
        0x2ed as libc::c_int as uint16_t,
        0x2dc as libc::c_int as uint16_t,
        0x2cd as libc::c_int as uint16_t,
        0x2bd as libc::c_int as uint16_t,
        0x2af as libc::c_int as uint16_t,
        0x2a0 as libc::c_int as uint16_t,
        0x293 as libc::c_int as uint16_t,
        0x286 as libc::c_int as uint16_t,
        0x279 as libc::c_int as uint16_t,
        0x26d as libc::c_int as uint16_t,
        0x261 as libc::c_int as uint16_t,
        0x256 as libc::c_int as uint16_t,
        0x24b as libc::c_int as uint16_t,
        0x240 as libc::c_int as uint16_t,
        0x236 as libc::c_int as uint16_t,
        0x22c as libc::c_int as uint16_t,
        0x222 as libc::c_int as uint16_t,
        0x218 as libc::c_int as uint16_t,
        0x20f as libc::c_int as uint16_t,
        0x206 as libc::c_int as uint16_t,
        0x1fd as libc::c_int as uint16_t,
        0x1f5 as libc::c_int as uint16_t,
        0x1ec as libc::c_int as uint16_t,
        0x1e4 as libc::c_int as uint16_t,
        0x1dc as libc::c_int as uint16_t,
        0x1d4 as libc::c_int as uint16_t,
        0x1cd as libc::c_int as uint16_t,
        0x1c5 as libc::c_int as uint16_t,
        0x1be as libc::c_int as uint16_t,
        0x1b7 as libc::c_int as uint16_t,
        0x1b0 as libc::c_int as uint16_t,
        0x1a9 as libc::c_int as uint16_t,
        0x1a2 as libc::c_int as uint16_t,
        0x19b as libc::c_int as uint16_t,
        0x195 as libc::c_int as uint16_t,
        0x18f as libc::c_int as uint16_t,
        0x188 as libc::c_int as uint16_t,
        0x182 as libc::c_int as uint16_t,
        0x17c as libc::c_int as uint16_t,
        0x177 as libc::c_int as uint16_t,
        0x171 as libc::c_int as uint16_t,
        0x16b as libc::c_int as uint16_t,
        0x166 as libc::c_int as uint16_t,
        0x160 as libc::c_int as uint16_t,
        0x15b as libc::c_int as uint16_t,
        0x155 as libc::c_int as uint16_t,
        0x150 as libc::c_int as uint16_t,
        0x14b as libc::c_int as uint16_t,
        0x146 as libc::c_int as uint16_t,
        0x141 as libc::c_int as uint16_t,
        0x13c as libc::c_int as uint16_t,
        0x137 as libc::c_int as uint16_t,
        0x133 as libc::c_int as uint16_t,
        0x12e as libc::c_int as uint16_t,
        0x129 as libc::c_int as uint16_t,
        0x125 as libc::c_int as uint16_t,
        0x121 as libc::c_int as uint16_t,
        0x11c as libc::c_int as uint16_t,
        0x118 as libc::c_int as uint16_t,
        0x114 as libc::c_int as uint16_t,
        0x10f as libc::c_int as uint16_t,
        0x10b as libc::c_int as uint16_t,
        0x107 as libc::c_int as uint16_t,
        0x103 as libc::c_int as uint16_t,
        0xff as libc::c_int as uint16_t,
        0xfb as libc::c_int as uint16_t,
        0xf8 as libc::c_int as uint16_t,
        0xf4 as libc::c_int as uint16_t,
        0xf0 as libc::c_int as uint16_t,
        0xec as libc::c_int as uint16_t,
        0xe9 as libc::c_int as uint16_t,
        0xe5 as libc::c_int as uint16_t,
        0xe2 as libc::c_int as uint16_t,
        0xde as libc::c_int as uint16_t,
        0xdb as libc::c_int as uint16_t,
        0xd7 as libc::c_int as uint16_t,
        0xd4 as libc::c_int as uint16_t,
        0xd1 as libc::c_int as uint16_t,
        0xcd as libc::c_int as uint16_t,
        0xca as libc::c_int as uint16_t,
        0xc7 as libc::c_int as uint16_t,
        0xc4 as libc::c_int as uint16_t,
        0xc1 as libc::c_int as uint16_t,
        0xbe as libc::c_int as uint16_t,
        0xbb as libc::c_int as uint16_t,
        0xb8 as libc::c_int as uint16_t,
        0xb5 as libc::c_int as uint16_t,
        0xb2 as libc::c_int as uint16_t,
        0xaf as libc::c_int as uint16_t,
        0xac as libc::c_int as uint16_t,
        0xa9 as libc::c_int as uint16_t,
        0xa7 as libc::c_int as uint16_t,
        0xa4 as libc::c_int as uint16_t,
        0xa1 as libc::c_int as uint16_t,
        0x9f as libc::c_int as uint16_t,
        0x9c as libc::c_int as uint16_t,
        0x99 as libc::c_int as uint16_t,
        0x97 as libc::c_int as uint16_t,
        0x94 as libc::c_int as uint16_t,
        0x92 as libc::c_int as uint16_t,
        0x8f as libc::c_int as uint16_t,
        0x8d as libc::c_int as uint16_t,
        0x8a as libc::c_int as uint16_t,
        0x88 as libc::c_int as uint16_t,
        0x86 as libc::c_int as uint16_t,
        0x83 as libc::c_int as uint16_t,
        0x81 as libc::c_int as uint16_t,
        0x7f as libc::c_int as uint16_t,
        0x7d as libc::c_int as uint16_t,
        0x7a as libc::c_int as uint16_t,
        0x78 as libc::c_int as uint16_t,
        0x76 as libc::c_int as uint16_t,
        0x74 as libc::c_int as uint16_t,
        0x72 as libc::c_int as uint16_t,
        0x70 as libc::c_int as uint16_t,
        0x6e as libc::c_int as uint16_t,
        0x6c as libc::c_int as uint16_t,
        0x6a as libc::c_int as uint16_t,
        0x68 as libc::c_int as uint16_t,
        0x66 as libc::c_int as uint16_t,
        0x64 as libc::c_int as uint16_t,
        0x62 as libc::c_int as uint16_t,
        0x60 as libc::c_int as uint16_t,
        0x5e as libc::c_int as uint16_t,
        0x5c as libc::c_int as uint16_t,
        0x5b as libc::c_int as uint16_t,
        0x59 as libc::c_int as uint16_t,
        0x57 as libc::c_int as uint16_t,
        0x55 as libc::c_int as uint16_t,
        0x53 as libc::c_int as uint16_t,
        0x52 as libc::c_int as uint16_t,
        0x50 as libc::c_int as uint16_t,
        0x4e as libc::c_int as uint16_t,
        0x4d as libc::c_int as uint16_t,
        0x4b as libc::c_int as uint16_t,
        0x4a as libc::c_int as uint16_t,
        0x48 as libc::c_int as uint16_t,
        0x46 as libc::c_int as uint16_t,
        0x45 as libc::c_int as uint16_t,
        0x43 as libc::c_int as uint16_t,
        0x42 as libc::c_int as uint16_t,
        0x40 as libc::c_int as uint16_t,
        0x3f as libc::c_int as uint16_t,
        0x3e as libc::c_int as uint16_t,
        0x3c as libc::c_int as uint16_t,
        0x3b as libc::c_int as uint16_t,
        0x39 as libc::c_int as uint16_t,
        0x38 as libc::c_int as uint16_t,
        0x37 as libc::c_int as uint16_t,
        0x35 as libc::c_int as uint16_t,
        0x34 as libc::c_int as uint16_t,
        0x33 as libc::c_int as uint16_t,
        0x31 as libc::c_int as uint16_t,
        0x30 as libc::c_int as uint16_t,
        0x2f as libc::c_int as uint16_t,
        0x2e as libc::c_int as uint16_t,
        0x2d as libc::c_int as uint16_t,
        0x2b as libc::c_int as uint16_t,
        0x2a as libc::c_int as uint16_t,
        0x29 as libc::c_int as uint16_t,
        0x28 as libc::c_int as uint16_t,
        0x27 as libc::c_int as uint16_t,
        0x26 as libc::c_int as uint16_t,
        0x25 as libc::c_int as uint16_t,
        0x24 as libc::c_int as uint16_t,
        0x23 as libc::c_int as uint16_t,
        0x22 as libc::c_int as uint16_t,
        0x21 as libc::c_int as uint16_t,
        0x20 as libc::c_int as uint16_t,
        0x1f as libc::c_int as uint16_t,
        0x1e as libc::c_int as uint16_t,
        0x1d as libc::c_int as uint16_t,
        0x1c as libc::c_int as uint16_t,
        0x1b as libc::c_int as uint16_t,
        0x1a as libc::c_int as uint16_t,
        0x19 as libc::c_int as uint16_t,
        0x18 as libc::c_int as uint16_t,
        0x17 as libc::c_int as uint16_t,
        0x17 as libc::c_int as uint16_t,
        0x16 as libc::c_int as uint16_t,
        0x15 as libc::c_int as uint16_t,
        0x14 as libc::c_int as uint16_t,
        0x14 as libc::c_int as uint16_t,
        0x13 as libc::c_int as uint16_t,
        0x12 as libc::c_int as uint16_t,
        0x11 as libc::c_int as uint16_t,
        0x11 as libc::c_int as uint16_t,
        0x10 as libc::c_int as uint16_t,
        0xf as libc::c_int as uint16_t,
        0xf as libc::c_int as uint16_t,
        0xe as libc::c_int as uint16_t,
        0xd as libc::c_int as uint16_t,
        0xd as libc::c_int as uint16_t,
        0xc as libc::c_int as uint16_t,
        0xc as libc::c_int as uint16_t,
        0xb as libc::c_int as uint16_t,
        0xa as libc::c_int as uint16_t,
        0xa as libc::c_int as uint16_t,
        0x9 as libc::c_int as uint16_t,
        0x9 as libc::c_int as uint16_t,
        0x8 as libc::c_int as uint16_t,
        0x8 as libc::c_int as uint16_t,
        0x7 as libc::c_int as uint16_t,
        0x7 as libc::c_int as uint16_t,
        0x7 as libc::c_int as uint16_t,
        0x6 as libc::c_int as uint16_t,
        0x6 as libc::c_int as uint16_t,
        0x5 as libc::c_int as uint16_t,
        0x5 as libc::c_int as uint16_t,
        0x5 as libc::c_int as uint16_t,
        0x4 as libc::c_int as uint16_t,
        0x4 as libc::c_int as uint16_t,
        0x4 as libc::c_int as uint16_t,
        0x3 as libc::c_int as uint16_t,
        0x3 as libc::c_int as uint16_t,
        0x3 as libc::c_int as uint16_t,
        0x2 as libc::c_int as uint16_t,
        0x2 as libc::c_int as uint16_t,
        0x2 as libc::c_int as uint16_t,
        0x2 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0x1 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
        0 as libc::c_int as uint16_t,
    ];
    if opl_emu_bitfield(input, 8 as libc::c_int, 1 as libc::c_int) != 0 {
        input = !input;
    }
    return s_sin_table[(input & 0xff as libc::c_int as uint32_t) as usize] as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_attenuation_to_volume(mut input: uint32_t) -> uint32_t {
    static mut s_power_table: [uint16_t; 256] = [
        ((0x3fa as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3f5 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3ef as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3ea as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3e4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3df as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3da as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3d4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3cf as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3c9 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3c4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3bf as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3b9 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3b4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3ae as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3a9 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3a4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x39f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x399 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x394 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x38f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x38a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x384 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x37f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x37a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x375 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x370 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x36a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x365 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x360 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x35b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x356 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x351 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x34c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x347 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x342 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x33d as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x338 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x333 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x32e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x329 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x324 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x31f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x31a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x315 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x310 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x30b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x306 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x302 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2fd as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2f8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2f3 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2ee as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2e9 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2e5 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2e0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2db as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2d6 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2d2 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2cd as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2c8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2c4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2bf as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2ba as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2b5 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2b1 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2ac as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2a8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2a3 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x29e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x29a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x295 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x291 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x28c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x288 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x283 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x27f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x27a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x276 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x271 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x26d as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x268 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x264 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x25f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x25b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x257 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x252 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x24e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x249 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x245 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x241 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x23c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x238 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x234 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x230 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x22b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x227 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x223 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x21e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x21a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x216 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x212 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x20e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x209 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x205 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x201 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1fd as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1f9 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1f5 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1f0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1ec as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1e8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1e4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1e0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1dc as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1d8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1d4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1d0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1cc as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1c8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1c4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1c0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1bc as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1b8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1b4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1b0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1ac as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1a8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1a4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1a0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x19c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x199 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x195 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x191 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x18d as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x189 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x185 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x181 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x17e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x17a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x176 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x172 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x16f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x16b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x167 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x163 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x160 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x15c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x158 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x154 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x151 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x14d as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x149 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x146 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x142 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x13e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x13b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x137 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x134 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x130 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x12c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x129 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x125 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x122 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x11e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x11b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x117 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x114 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x110 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x10c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x109 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x106 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x102 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xff as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xfb as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xf8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xf4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xf1 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xed as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xea as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xe7 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xe3 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xe0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xdc as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xd9 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xd6 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xd2 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xcf as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xcc as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xc8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xc5 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xc2 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xbe as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xbb as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xb8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xb5 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xb1 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xae as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xab as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xa8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xa4 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xa1 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x9e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x9b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x98 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x94 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x91 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x8e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x8b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x88 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x85 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x82 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x7e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x7b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x78 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x75 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x72 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x6f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x6c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x69 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x66 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x63 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x60 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x5d as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x5a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x57 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x54 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x51 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x4e as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x4b as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x48 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x45 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x42 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x39 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x36 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x33 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x30 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2d as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x2a as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x28 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x25 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x22 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1f as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x1c as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x19 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x16 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x14 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x11 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xe as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0xb as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x8 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x6 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0x3 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
        ((0 as libc::c_int | 0x400 as libc::c_int) << 2 as libc::c_int) as uint16_t,
    ];
    return (s_power_table[(input & 0xff as libc::c_int as uint32_t) as usize]
        as libc::c_int >> (input >> 8 as libc::c_int)) as uint32_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_attenuation_increment(
    mut rate: uint32_t,
    mut index: uint32_t,
) -> uint32_t {
    static mut s_increment_table: [uint32_t; 64] = [
        0 as libc::c_int as uint32_t,
        0 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x10101010 as libc::c_int as uint32_t,
        0x10111010 as libc::c_int as uint32_t,
        0x11101110 as libc::c_int as uint32_t,
        0x11111110 as libc::c_int as uint32_t,
        0x11111111 as libc::c_int as uint32_t,
        0x21112111 as libc::c_int as uint32_t,
        0x21212121 as libc::c_int as uint32_t,
        0x22212221 as libc::c_int as uint32_t,
        0x22222222 as libc::c_int as uint32_t,
        0x42224222 as libc::c_int as uint32_t,
        0x42424242 as libc::c_int as uint32_t,
        0x44424442 as libc::c_int as uint32_t,
        0x44444444 as libc::c_int as uint32_t,
        0x84448444 as libc::c_uint,
        0x84848484 as libc::c_uint,
        0x88848884 as libc::c_uint,
        0x88888888 as libc::c_uint,
        0x88888888 as libc::c_uint,
        0x88888888 as libc::c_uint,
        0x88888888 as libc::c_uint,
    ];
    return opl_emu_bitfield(
        s_increment_table[rate as usize],
        (4 as libc::c_int as uint32_t * index) as libc::c_int,
        4 as libc::c_int,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_init(mut regs: *mut opl_emu_registers) {
    (*regs).m_lfo_am_counter = 0 as libc::c_int as uint16_t;
    (*regs).m_lfo_pm_counter = 0 as libc::c_int as uint16_t;
    (*regs).m_noise_lfsr = 1 as libc::c_int as uint32_t;
    (*regs).m_lfo_am = 0 as libc::c_int as uint8_t;
    let mut wf0: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf1: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((1 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf2: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((2 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf3: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((3 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf4: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((4 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf5: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((5 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf6: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((6 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut wf7: *mut uint16_t = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset((7 as libc::c_int % 8 as libc::c_int) as isize))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    let mut index: uint32_t = 0 as libc::c_int as uint32_t;
    while index < 0x400 as libc::c_int as uint32_t {
        *wf0
            .offset(
                index as isize,
            ) = (opl_emu_abs_sin_attenuation(index)
            | opl_emu_bitfield(index, 9 as libc::c_int, 1 as libc::c_int)
                << 15 as libc::c_int) as uint16_t;
        index = index.wrapping_add(1);
        index;
    }
    if 8 as libc::c_int >= 4 as libc::c_int {
        let mut zeroval: uint16_t = *wf0.offset(0 as libc::c_int as isize);
        let mut index_0: uint32_t = 0 as libc::c_int as uint32_t;
        while index_0 < 0x400 as libc::c_int as uint32_t {
            *wf1
                .offset(
                    index_0 as isize,
                ) = (if opl_emu_bitfield(index_0, 9 as libc::c_int, 1 as libc::c_int)
                != 0
            {
                zeroval as libc::c_int
            } else {
                *wf0.offset(index_0 as isize) as libc::c_int
            }) as uint16_t;
            *wf2
                .offset(
                    index_0 as isize,
                ) = (*wf0.offset(index_0 as isize) as libc::c_int
                & 0x7fff as libc::c_int) as uint16_t;
            *wf3
                .offset(
                    index_0 as isize,
                ) = (if opl_emu_bitfield(index_0, 8 as libc::c_int, 1 as libc::c_int)
                != 0
            {
                zeroval as libc::c_int
            } else {
                *wf0.offset(index_0 as isize) as libc::c_int & 0x7fff as libc::c_int
            }) as uint16_t;
            if 8 as libc::c_int >= 8 as libc::c_int {
                *wf4
                    .offset(
                        index_0 as isize,
                    ) = (if opl_emu_bitfield(index_0, 9 as libc::c_int, 1 as libc::c_int)
                    != 0
                {
                    zeroval as libc::c_int
                } else {
                    *wf0.offset((index_0 * 2 as libc::c_int as uint32_t) as isize)
                        as libc::c_int
                }) as uint16_t;
                *wf5
                    .offset(
                        index_0 as isize,
                    ) = (if opl_emu_bitfield(index_0, 9 as libc::c_int, 1 as libc::c_int)
                    != 0
                {
                    zeroval as libc::c_int
                } else {
                    *wf0
                        .offset(
                            (index_0 * 2 as libc::c_int as uint32_t
                                & 0x1ff as libc::c_int as uint32_t) as isize,
                        ) as libc::c_int
                }) as uint16_t;
                *wf6
                    .offset(
                        index_0 as isize,
                    ) = (opl_emu_bitfield(index_0, 9 as libc::c_int, 1 as libc::c_int)
                    << 15 as libc::c_int) as uint16_t;
                *wf7
                    .offset(
                        index_0 as isize,
                    ) = ((if opl_emu_bitfield(
                    index_0,
                    9 as libc::c_int,
                    1 as libc::c_int,
                ) != 0
                {
                    index_0 ^ 0x13ff as libc::c_int as uint32_t
                } else {
                    index_0
                }) << 3 as libc::c_int) as uint16_t;
            }
            index_0 = index_0.wrapping_add(1);
            index_0;
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_reset(mut regs: *mut opl_emu_registers) {
    let mut i: libc::c_int = 0 as libc::c_int;
    while i < 0x200 as libc::c_int {
        (*regs).m_regdata[i as usize] = 0 as libc::c_int as uint8_t;
        i += 1;
        i;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_operator_map(
    mut regs: *mut opl_emu_registers,
    mut dest: *mut opl_emu_registers_operator_mapping,
) {
    let mut fourop: uint32_t = opl_emu_registers_fourop_enable(regs);
    (*dest)
        .chan[0 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 0 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0 as libc::c_int as uint8_t,
            3 as libc::c_int as uint8_t,
            6 as libc::c_int as uint8_t,
            9 as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            0 as libc::c_int as uint8_t,
            3 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[1 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 1 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            1 as libc::c_int as uint8_t,
            4 as libc::c_int as uint8_t,
            7 as libc::c_int as uint8_t,
            10 as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            1 as libc::c_int as uint8_t,
            4 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[2 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 2 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            2 as libc::c_int as uint8_t,
            5 as libc::c_int as uint8_t,
            8 as libc::c_int as uint8_t,
            11 as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            2 as libc::c_int as uint8_t,
            5 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[3 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 0 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            6 as libc::c_int as uint8_t,
            9 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[4 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 1 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            7 as libc::c_int as uint8_t,
            10 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[5 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 2 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            8 as libc::c_int as uint8_t,
            11 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[6 as libc::c_int
        as usize] = opl_emu_registers_operator_list(
        12 as libc::c_int as uint8_t,
        15 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
    (*dest)
        .chan[7 as libc::c_int
        as usize] = opl_emu_registers_operator_list(
        13 as libc::c_int as uint8_t,
        16 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
    (*dest)
        .chan[8 as libc::c_int
        as usize] = opl_emu_registers_operator_list(
        14 as libc::c_int as uint8_t,
        17 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
    (*dest)
        .chan[9 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 3 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            18 as libc::c_int as uint8_t,
            21 as libc::c_int as uint8_t,
            24 as libc::c_int as uint8_t,
            27 as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            18 as libc::c_int as uint8_t,
            21 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[10 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 4 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            19 as libc::c_int as uint8_t,
            22 as libc::c_int as uint8_t,
            25 as libc::c_int as uint8_t,
            28 as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            19 as libc::c_int as uint8_t,
            22 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[11 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 5 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            20 as libc::c_int as uint8_t,
            23 as libc::c_int as uint8_t,
            26 as libc::c_int as uint8_t,
            29 as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            20 as libc::c_int as uint8_t,
            23 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[12 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 3 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            24 as libc::c_int as uint8_t,
            27 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[13 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 4 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            25 as libc::c_int as uint8_t,
            28 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[14 as libc::c_int
        as usize] = if opl_emu_bitfield(fourop, 5 as libc::c_int, 1 as libc::c_int) != 0
    {
        opl_emu_registers_operator_list(
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    } else {
        opl_emu_registers_operator_list(
            26 as libc::c_int as uint8_t,
            29 as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
            0xff as libc::c_int as uint8_t,
        )
    };
    (*dest)
        .chan[15 as libc::c_int
        as usize] = opl_emu_registers_operator_list(
        30 as libc::c_int as uint8_t,
        33 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
    (*dest)
        .chan[16 as libc::c_int
        as usize] = opl_emu_registers_operator_list(
        31 as libc::c_int as uint8_t,
        34 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
    (*dest)
        .chan[17 as libc::c_int
        as usize] = opl_emu_registers_operator_list(
        32 as libc::c_int as uint8_t,
        35 as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
        0xff as libc::c_int as uint8_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_write(
    mut regs: *mut opl_emu_registers,
    mut index: uint16_t,
    mut data: uint8_t,
    mut channel: *mut uint32_t,
    mut opmask: *mut uint32_t,
) -> libc::c_int {
    if index as libc::c_int == 0x4 as libc::c_int
        && opl_emu_bitfield(data as uint32_t, 7 as libc::c_int, 1 as libc::c_int)
            != 0 as libc::c_int as uint32_t
    {
        (*regs)
            .m_regdata[index
            as usize] = ((*regs).m_regdata[index as usize] as libc::c_int
            | 0x80 as libc::c_int) as uint8_t;
    } else {
        (*regs).m_regdata[index as usize] = data;
    }
    if index as libc::c_int == 0xbd as libc::c_int {
        *channel = 0xff as libc::c_int as uint32_t;
        *opmask = if opl_emu_bitfield(
            data as uint32_t,
            5 as libc::c_int,
            1 as libc::c_int,
        ) != 0
        {
            opl_emu_bitfield(data as uint32_t, 0 as libc::c_int, 5 as libc::c_int)
        } else {
            0 as libc::c_int as uint32_t
        };
        return 1 as libc::c_int;
    }
    if index as libc::c_int & 0xf0 as libc::c_int == 0xb0 as libc::c_int {
        *channel = (index as libc::c_int & 0xf as libc::c_int) as uint32_t;
        if *channel < 9 as libc::c_int as uint32_t {
            *channel = (*channel)
                .wrapping_add(
                    9 as libc::c_int as uint32_t
                        * opl_emu_bitfield(
                            index as uint32_t,
                            8 as libc::c_int,
                            1 as libc::c_int,
                        ),
                );
            *opmask = (if opl_emu_bitfield(
                data as uint32_t,
                5 as libc::c_int,
                1 as libc::c_int,
            ) != 0
            {
                15 as libc::c_int
            } else {
                0 as libc::c_int
            }) as uint32_t;
            return 1 as libc::c_int;
        }
    }
    return 0 as libc::c_int;
}
unsafe extern "C" fn opl_emu_opl_clock_noise_and_lfo(
    mut noise_lfsr: *mut uint32_t,
    mut lfo_am_counter: *mut uint16_t,
    mut lfo_pm_counter: *mut uint16_t,
    mut lfo_am: *mut uint8_t,
    mut am_depth: uint32_t,
    mut pm_depth: uint32_t,
) -> int32_t {
    *noise_lfsr <<= 1 as libc::c_int;
    *noise_lfsr
        |= opl_emu_bitfield(*noise_lfsr, 23 as libc::c_int, 1 as libc::c_int)
            ^ opl_emu_bitfield(*noise_lfsr, 9 as libc::c_int, 1 as libc::c_int)
            ^ opl_emu_bitfield(*noise_lfsr, 8 as libc::c_int, 1 as libc::c_int)
            ^ opl_emu_bitfield(*noise_lfsr, 1 as libc::c_int, 1 as libc::c_int);
    let fresh1 = lfo_am_counter;
    lfo_am_counter = lfo_am_counter.offset(1);
    let mut am_counter: uint32_t = *fresh1 as uint32_t;
    if am_counter
        >= (210 as libc::c_int * 64 as libc::c_int - 1 as libc::c_int) as uint32_t
    {
        *lfo_am_counter = 0 as libc::c_int as uint16_t;
    }
    let mut shift: libc::c_int = (9 as libc::c_int as uint32_t)
        .wrapping_sub(2 as libc::c_int as uint32_t * am_depth) as libc::c_int;
    *lfo_am = ((if am_counter < (105 as libc::c_int * 64 as libc::c_int) as uint32_t {
        am_counter
    } else {
        ((210 as libc::c_int * 64 as libc::c_int + 63 as libc::c_int) as uint32_t)
            .wrapping_sub(am_counter)
    }) >> shift) as uint8_t;
    let fresh2 = lfo_pm_counter;
    lfo_pm_counter = lfo_pm_counter.offset(1);
    let mut pm_counter: uint32_t = *fresh2 as uint32_t;
    static mut pm_scale: [int8_t; 8] = [
        8 as libc::c_int as int8_t,
        4 as libc::c_int as int8_t,
        0 as libc::c_int as int8_t,
        -(4 as libc::c_int) as int8_t,
        -(8 as libc::c_int) as int8_t,
        -(4 as libc::c_int) as int8_t,
        0 as libc::c_int as int8_t,
        4 as libc::c_int as int8_t,
    ];
    return pm_scale[opl_emu_bitfield(pm_counter, 10 as libc::c_int, 3 as libc::c_int)
        as usize] as libc::c_int >> (pm_depth ^ 1 as libc::c_int as uint32_t);
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_clock_noise_and_lfo(
    mut regs: *mut opl_emu_registers,
) -> int32_t {
    return {let crown_promoted_local_0 = opl_emu_registers_lfo_am_depth(regs);opl_emu_opl_clock_noise_and_lfo(
        &raw mut (*regs).m_noise_lfsr,
        &raw mut (*regs).m_lfo_am_counter,
        &raw mut (*regs).m_lfo_pm_counter,
        &raw mut (*regs).m_lfo_am,
        crown_promoted_local_0,
        opl_emu_registers_lfo_pm_depth(regs),
    )};
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_cache_operator_data(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
    mut opoffs: uint32_t,
    mut cache: *mut opl_emu_opdata_cache,
) {
    (*cache)
        .waveform = &raw mut *(*((*regs).m_waveform)
        .as_mut_ptr()
        .offset(
            ((opl_emu_registers_op_waveform
                as unsafe extern "C" fn(
                    *mut opl_emu_registers,
                    uint32_t,
                ) -> uint32_t)(regs, opoffs) % 8 as libc::c_int as uint32_t) as isize,
        ))
        .as_mut_ptr()
        .offset(0 as libc::c_int as isize) as *mut uint16_t;
    (*cache).block_freq = opl_emu_registers_ch_block_freq(regs, choffs);
    let mut block_freq: uint32_t = (*cache).block_freq;
    let mut keycode: uint32_t = opl_emu_bitfield(
        block_freq,
        10 as libc::c_int,
        3 as libc::c_int,
    ) << 1 as libc::c_int;
    keycode
        |= opl_emu_bitfield(
            block_freq,
            (9 as libc::c_int as uint32_t)
                .wrapping_sub(opl_emu_registers_note_select(regs)) as libc::c_int,
            1 as libc::c_int,
        );
    (*cache).detune = 0 as libc::c_int;
    let mut multiple: uint32_t = opl_emu_registers_op_multiple(regs, opoffs);
    (*cache)
        .multiple = (multiple & 0xe as libc::c_int as uint32_t
        | opl_emu_bitfield(
            0xc2aa as libc::c_int as uint32_t,
            multiple as libc::c_int,
            1 as libc::c_int,
        )) * 2 as libc::c_int as uint32_t;
    if (*cache).multiple == 0 as libc::c_int as uint32_t {
        (*cache).multiple = 1 as libc::c_int as uint32_t;
    }
    if opl_emu_registers_op_lfo_pm_enable(regs, opoffs) == 0 as libc::c_int as uint32_t {
        (*cache)
            .phase_step = opl_emu_registers_compute_phase_step(
            regs,
            choffs,
            opoffs,
            cache,
            0 as libc::c_int,
        );
    } else {
        (*cache).phase_step = 1 as libc::c_int as uint32_t;
    }
    (*cache)
        .total_level = opl_emu_registers_op_total_level(regs, opoffs)
        << 3 as libc::c_int;
    let mut ksl: uint32_t = opl_emu_registers_op_ksl(regs, opoffs);
    if ksl != 0 as libc::c_int as uint32_t {
        (*cache)
            .total_level = ((*cache).total_level)
            .wrapping_add(
                opl_emu_opl_key_scale_atten(
                    opl_emu_bitfield(block_freq, 10 as libc::c_int, 3 as libc::c_int),
                    opl_emu_bitfield(block_freq, 6 as libc::c_int, 4 as libc::c_int),
                ) << ksl,
            );
    }
    (*cache).eg_sustain = opl_emu_registers_op_sustain_level(regs, opoffs);
    (*cache).eg_sustain
        |= ((*cache).eg_sustain).wrapping_add(1 as libc::c_int as uint32_t)
            & 0x10 as libc::c_int as uint32_t;
    (*cache).eg_sustain <<= 5 as libc::c_int;
    let mut ksrval: uint32_t = keycode
        >> 2 as libc::c_int as uint32_t
            * (opl_emu_registers_op_ksr(regs, opoffs) ^ 1 as libc::c_int as uint32_t);
    (*cache)
        .eg_rate[OPL_EMU_EG_ATTACK as libc::c_int
        as usize] = opl_emu_registers_effective_rate(
        opl_emu_registers_op_attack_rate(regs, opoffs) * 4 as libc::c_int as uint32_t,
        ksrval,
    ) as uint8_t;
    (*cache)
        .eg_rate[OPL_EMU_EG_DECAY as libc::c_int
        as usize] = opl_emu_registers_effective_rate(
        opl_emu_registers_op_decay_rate(regs, opoffs) * 4 as libc::c_int as uint32_t,
        ksrval,
    ) as uint8_t;
    (*cache)
        .eg_rate[OPL_EMU_EG_SUSTAIN as libc::c_int
        as usize] = (if opl_emu_registers_op_eg_sustain(regs, opoffs) != 0 {
        0 as libc::c_int as uint32_t
    } else {
        opl_emu_registers_effective_rate(
            opl_emu_registers_op_release_rate(regs, opoffs)
                * 4 as libc::c_int as uint32_t,
            ksrval,
        )
    }) as uint8_t;
    (*cache)
        .eg_rate[OPL_EMU_EG_RELEASE as libc::c_int
        as usize] = opl_emu_registers_effective_rate(
        opl_emu_registers_op_release_rate(regs, opoffs) * 4 as libc::c_int as uint32_t,
        ksrval,
    ) as uint8_t;
}
unsafe extern "C" fn opl_emu_opl_compute_phase_step(
    mut block_freq: uint32_t,
    mut multiple: uint32_t,
    mut lfo_raw_pm: int32_t,
) -> uint32_t {
    let mut fnum: uint32_t = opl_emu_bitfield(
        block_freq,
        0 as libc::c_int,
        10 as libc::c_int,
    ) << 2 as libc::c_int;
    fnum = fnum
        .wrapping_add(
            lfo_raw_pm as uint32_t
                * opl_emu_bitfield(block_freq, 7 as libc::c_int, 3 as libc::c_int)
                >> 1 as libc::c_int,
        );
    fnum &= 0xfff as libc::c_int as uint32_t;
    let mut block: uint32_t = opl_emu_bitfield(
        block_freq,
        10 as libc::c_int,
        3 as libc::c_int,
    );
    let mut phase_step: uint32_t = fnum << block >> 2 as libc::c_int;
    return phase_step * multiple >> 1 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_registers_compute_phase_step(
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
    mut opoffs: uint32_t,
    mut cache: *const opl_emu_opdata_cache,
    mut lfo_raw_pm: int32_t,
) -> uint32_t {
    return opl_emu_opl_compute_phase_step(
        (*cache).block_freq,
        (*cache).multiple,
        if opl_emu_registers_op_lfo_pm_enable(regs, opoffs) != 0 {
            lfo_raw_pm
        } else {
            0 as libc::c_int
        },
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_init(
    mut fmop: *mut opl_emu_fm_operator,
    mut regs: *mut opl_emu_registers,
    mut opoffs: uint32_t,
) {
    (*fmop).m_choffs = 0 as libc::c_int as uint32_t;
    (*fmop).m_opoffs = opoffs;
    (*fmop).m_phase = 0 as libc::c_int as uint32_t;
    (*fmop).m_env_attenuation = 0x3ff as libc::c_int as uint16_t;
    (*fmop).m_env_state = OPL_EMU_EG_RELEASE;
    (*fmop).m_key_state = 0 as libc::c_int as uint8_t;
    (*fmop).m_keyon_live = 0 as libc::c_int as uint8_t;
    (*fmop).m_regs = regs;
    (*fmop).m_cache.eg_shift = 0 as libc::c_int as uint8_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_reset(mut fmop: *mut opl_emu_fm_operator) {
    (*fmop).m_phase = 0 as libc::c_int as uint32_t;
    (*fmop).m_env_attenuation = 0x3ff as libc::c_int as uint16_t;
    (*fmop).m_env_state = OPL_EMU_EG_RELEASE;
    (*fmop).m_key_state = 0 as libc::c_int as uint8_t;
    (*fmop).m_keyon_live = 0 as libc::c_int as uint8_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_prepare(
    mut fmop: *mut opl_emu_fm_operator,
) -> libc::c_int {
    opl_emu_registers_cache_operator_data(
        (*fmop).m_regs,
        (*fmop).m_choffs,
        (*fmop).m_opoffs,
        &raw mut (*fmop).m_cache,
    );
    {let crown_promoted_local_0 = ((*fmop).m_keyon_live as libc::c_int != 0 as libc::c_int) as libc::c_int
            as uint32_t;opl_emu_fm_operator_clock_keystate(
        fmop,
        crown_promoted_local_0,
    )};
    (*fmop)
        .m_keyon_live = ((*fmop).m_keyon_live as libc::c_int
        & !((1 as libc::c_int) << OPL_EMU_KEYON_CSM as libc::c_int)) as uint8_t;
    return ((*fmop).m_env_state as libc::c_uint
        != OPL_EMU_EG_RELEASE as libc::c_int as libc::c_uint
        || ((*fmop).m_env_attenuation as libc::c_int) < 0x200 as libc::c_int)
        as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_clock(
    mut fmop: *mut opl_emu_fm_operator,
    mut env_counter: uint32_t,
    mut lfo_raw_pm: int32_t,
) {
    if opl_emu_bitfield(env_counter, 0 as libc::c_int, 2 as libc::c_int)
        == 0 as libc::c_int as uint32_t
    {
        opl_emu_fm_operator_clock_envelope(fmop, env_counter >> 2 as libc::c_int);
    }
    opl_emu_fm_operator_clock_phase(fmop, lfo_raw_pm);
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_compute_volume(
    mut fmop: *mut opl_emu_fm_operator,
    mut phase: uint32_t,
    mut am_offset: uint32_t,
) -> int32_t {
    if (*fmop).m_env_attenuation as libc::c_int > 0x200 as libc::c_int {
        return 0 as libc::c_int;
    }
    let mut sin_attenuation: uint32_t = *((*fmop).m_cache.waveform)
        .offset((phase & (0x400 as libc::c_int - 1 as libc::c_int) as uint32_t) as isize)
        as uint32_t;
    let mut env_attenuation: uint32_t = opl_emu_fm_operator_envelope_attenuation(
        fmop,
        am_offset,
    ) << 2 as libc::c_int;
    let mut result: int32_t = opl_emu_attenuation_to_volume(
        (sin_attenuation & 0x7fff as libc::c_int as uint32_t)
            .wrapping_add(env_attenuation),
    ) as int32_t;
    return if opl_emu_bitfield(sin_attenuation, 15 as libc::c_int, 1 as libc::c_int) != 0
    {
        -result
    } else {
        result
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_keyonoff(
    mut fmop: *mut opl_emu_fm_operator,
    mut on: uint32_t,
    mut type_0: opl_emu_keyon_type,
) {
    (*fmop)
        .m_keyon_live = (((*fmop).m_keyon_live as libc::c_int
        & !((1 as libc::c_int) << type_0 as libc::c_int)) as uint32_t
        | opl_emu_bitfield(on, 0 as libc::c_int, 1 as libc::c_int)
            << type_0 as libc::c_int) as uint8_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_start_attack(
    mut fmop: *mut opl_emu_fm_operator,
) {
    if (*fmop).m_env_state as libc::c_uint
        == OPL_EMU_EG_ATTACK as libc::c_int as libc::c_uint
    {
        return;
    }
    (*fmop).m_env_state = OPL_EMU_EG_ATTACK;
    (*fmop).m_phase = 0 as libc::c_int as uint32_t;
    if (*fmop).m_cache.eg_rate[OPL_EMU_EG_ATTACK as libc::c_int as usize] as libc::c_int
        >= 62 as libc::c_int
    {
        (*fmop).m_env_attenuation = 0 as libc::c_int as uint16_t;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_start_release(
    mut fmop: *mut opl_emu_fm_operator,
) {
    if (*fmop).m_env_state as libc::c_uint
        >= OPL_EMU_EG_RELEASE as libc::c_int as libc::c_uint
    {
        return;
    }
    (*fmop).m_env_state = OPL_EMU_EG_RELEASE;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_clock_keystate(
    mut fmop: *mut opl_emu_fm_operator,
    mut keystate: uint32_t,
) {
    if keystate ^ (*fmop).m_key_state as uint32_t != 0 as libc::c_int as uint32_t {
        (*fmop).m_key_state = keystate as uint8_t;
        if keystate != 0 as libc::c_int as uint32_t {
            opl_emu_fm_operator_start_attack(fmop);
        } else {
            opl_emu_fm_operator_start_release(fmop);
        }
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_clock_envelope(
    mut fmop: *mut opl_emu_fm_operator,
    mut env_counter: uint32_t,
) {
    if (*fmop).m_env_state as libc::c_uint
        == OPL_EMU_EG_ATTACK as libc::c_int as libc::c_uint
        && (*fmop).m_env_attenuation as libc::c_int == 0 as libc::c_int
    {
        (*fmop).m_env_state = OPL_EMU_EG_DECAY;
    }
    if (*fmop).m_env_state as libc::c_uint
        == OPL_EMU_EG_DECAY as libc::c_int as libc::c_uint
        && (*fmop).m_env_attenuation as uint32_t >= (*fmop).m_cache.eg_sustain
    {
        (*fmop).m_env_state = OPL_EMU_EG_SUSTAIN;
    }
    let mut rate: uint32_t = (*fmop).m_cache.eg_rate[(*fmop).m_env_state as usize]
        as uint32_t;
    let mut rate_shift: uint32_t = rate >> 2 as libc::c_int;
    env_counter <<= rate_shift;
    if opl_emu_bitfield(env_counter, 0 as libc::c_int, 11 as libc::c_int)
        != 0 as libc::c_int as uint32_t
    {
        return;
    }
    let mut relevant_bits: uint32_t = opl_emu_bitfield(
        env_counter,
        (if rate_shift <= 11 as libc::c_int as uint32_t {
            11 as libc::c_int as uint32_t
        } else {
            rate_shift
        }) as libc::c_int,
        3 as libc::c_int,
    );
    let mut increment: uint32_t = opl_emu_attenuation_increment(rate, relevant_bits);
    if (*fmop).m_env_state as libc::c_uint
        == OPL_EMU_EG_ATTACK as libc::c_int as libc::c_uint
    {
        if rate < 62 as libc::c_int as uint32_t {
            (*fmop)
                .m_env_attenuation = ((*fmop).m_env_attenuation as uint32_t)
                .wrapping_add(
                    !((*fmop).m_env_attenuation as libc::c_int) as uint32_t * increment
                        >> 4 as libc::c_int,
                ) as uint16_t as uint16_t;
        }
    } else {
        (*fmop)
            .m_env_attenuation = ((*fmop).m_env_attenuation as uint32_t)
            .wrapping_add(increment) as uint16_t as uint16_t;
        if (*fmop).m_env_attenuation as libc::c_int >= 0x400 as libc::c_int {
            (*fmop).m_env_attenuation = 0x3ff as libc::c_int as uint16_t;
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_clock_phase(
    mut fmop: *mut opl_emu_fm_operator,
    mut lfo_raw_pm: int32_t,
) {
    let mut phase_step: uint32_t = (*fmop).m_cache.phase_step;
    if phase_step == 1 as libc::c_int as uint32_t {
        phase_step = opl_emu_registers_compute_phase_step(
            (*fmop).m_regs,
            (*fmop).m_choffs,
            (*fmop).m_opoffs,
            &raw mut (*fmop).m_cache,
            lfo_raw_pm,
        );
    }
    (*fmop).m_phase = ((*fmop).m_phase).wrapping_add(phase_step);
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_operator_envelope_attenuation(
    mut fmop: *mut opl_emu_fm_operator,
    mut am_offset: uint32_t,
) -> uint32_t {
    let mut result: uint32_t = ((*fmop).m_env_attenuation as libc::c_int
        >> (*fmop).m_cache.eg_shift as libc::c_int) as uint32_t;
    if opl_emu_registers_op_lfo_am_enable((*fmop).m_regs, (*fmop).m_opoffs) != 0 {
        result = result.wrapping_add(am_offset);
    }
    result = result.wrapping_add((*fmop).m_cache.total_level);
    return if result < 0x3ff as libc::c_int as uint32_t {
        result
    } else {
        0x3ff as libc::c_int as uint32_t
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_init(
    mut fmch: *mut opl_emu_fm_channel,
    mut regs: *mut opl_emu_registers,
    mut choffs: uint32_t,
) {
    (*fmch).m_choffs = choffs;
    (*fmch).m_feedback[0 as libc::c_int as usize] = 0 as libc::c_int as int16_t;
    (*fmch).m_feedback[1 as libc::c_int as usize] = 0 as libc::c_int as int16_t;
    (*fmch).m_feedback_in = 0 as libc::c_int as int16_t;
    (*fmch).m_op[0 as libc::c_int as usize] = 0 as *mut opl_emu_fm_operator;
    (*fmch).m_op[1 as libc::c_int as usize] = 0 as *mut opl_emu_fm_operator;
    (*fmch).m_op[2 as libc::c_int as usize] = 0 as *mut opl_emu_fm_operator;
    (*fmch).m_op[3 as libc::c_int as usize] = 0 as *mut opl_emu_fm_operator;
    (*fmch).m_regs = regs;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_reset(mut fmch: *mut opl_emu_fm_channel) {
    (*fmch).m_feedback[1 as libc::c_int as usize] = 0 as libc::c_int as int16_t;
    (*fmch)
        .m_feedback[0 as libc::c_int
        as usize] = (*fmch).m_feedback[1 as libc::c_int as usize];
    (*fmch).m_feedback_in = 0 as libc::c_int as int16_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_keyonoff(
    mut fmch: *mut opl_emu_fm_channel,
    mut states: uint32_t,
    mut type_0: opl_emu_keyon_type,
    mut chnum: uint32_t,
) {
    let mut opnum: uint32_t = 0 as libc::c_int as uint32_t;
    while (opnum as libc::c_ulong)
        < (::core::mem::size_of::<[*mut opl_emu_fm_operator; 4]>() as libc::c_ulong)
            .wrapping_div(
                ::core::mem::size_of::<*mut opl_emu_fm_operator>() as libc::c_ulong,
            )
    {
        if !((*fmch).m_op[opnum as usize]).is_null() {
            opl_emu_fm_operator_keyonoff(
                (*fmch).m_op[opnum as usize],
                opl_emu_bitfield(states, opnum as libc::c_int, 1 as libc::c_int),
                type_0,
            );
        }else { std::intrinsics::assume(((*fmch).m_op[opnum as usize]).addr() == 0); }
        opnum = opnum.wrapping_add(1);
        opnum;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_prepare(
    mut fmch: *mut opl_emu_fm_channel,
) -> libc::c_int {
    let mut active_mask: uint32_t = 0 as libc::c_int as uint32_t;
    let mut opnum: uint32_t = 0 as libc::c_int as uint32_t;
    while (opnum as libc::c_ulong)
        < (::core::mem::size_of::<[*mut opl_emu_fm_operator; 4]>() as libc::c_ulong)
            .wrapping_div(
                ::core::mem::size_of::<*mut opl_emu_fm_operator>() as libc::c_ulong,
            )
    {
        if !((*fmch).m_op[opnum as usize]).is_null() {
            if opl_emu_fm_operator_prepare((*fmch).m_op[opnum as usize]) != 0 {
                active_mask |= ((1 as libc::c_int) << opnum) as uint32_t;
            }
        }else { std::intrinsics::assume(((*fmch).m_op[opnum as usize]).addr() == 0); }
        opnum = opnum.wrapping_add(1);
        opnum;
    }
    return (active_mask != 0 as libc::c_int as uint32_t) as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_clock(
    mut fmch: *mut opl_emu_fm_channel,
    mut env_counter: uint32_t,
    mut lfo_raw_pm: int32_t,
) {
    (*fmch)
        .m_feedback[0 as libc::c_int
        as usize] = (*fmch).m_feedback[1 as libc::c_int as usize];
    (*fmch).m_feedback[1 as libc::c_int as usize] = (*fmch).m_feedback_in;
    let mut opnum: uint32_t = 0 as libc::c_int as uint32_t;
    while (opnum as libc::c_ulong)
        < (::core::mem::size_of::<[*mut opl_emu_fm_operator; 4]>() as libc::c_ulong)
            .wrapping_div(
                ::core::mem::size_of::<*mut opl_emu_fm_operator>() as libc::c_ulong,
            )
    {
        if !((*fmch).m_op[opnum as usize]).is_null() {
            opl_emu_fm_operator_clock(
                (*fmch).m_op[opnum as usize],
                env_counter,
                lfo_raw_pm,
            );
        }else { std::intrinsics::assume(((*fmch).m_op[opnum as usize]).addr() == 0); }
        opnum = opnum.wrapping_add(1);
        opnum;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_output_2op(
    mut fmch: *mut opl_emu_fm_channel,
    mut output: *mut libc::c_short,
    mut rshift: uint32_t,
    mut clipmax: int32_t,
) {
    let mut am_offset: uint32_t = opl_emu_registers_lfo_am_offset(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    let mut opmod: int32_t = 0 as libc::c_int;
    let mut feedback: uint32_t = opl_emu_registers_ch_feedback(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    if feedback != 0 as libc::c_int as uint32_t {
        opmod = (*fmch).m_feedback[0 as libc::c_int as usize] as libc::c_int
            + (*fmch).m_feedback[1 as libc::c_int as usize] as libc::c_int
            >> (10 as libc::c_int as uint32_t).wrapping_sub(feedback);
    }
    (*fmch)
        .m_feedback_in = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[0 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[0 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    ) as int16_t;
    let mut op1value: int32_t = (*fmch).m_feedback_in as int32_t;
    if opl_emu_registers_ch_output_any((*fmch).m_regs, (*fmch).m_choffs)
        == 0 as libc::c_int as uint32_t
    {
        return;
    }
    let mut result: int32_t = 0;
    if opl_emu_bitfield(
        opl_emu_registers_ch_algorithm((*fmch).m_regs, (*fmch).m_choffs),
        0 as libc::c_int,
        1 as libc::c_int,
    ) == 0 as libc::c_int as uint32_t
    {
        opmod = op1value >> 1 as libc::c_int;
        result = opl_emu_fm_operator_compute_volume(
            (*fmch).m_op[1 as libc::c_int as usize],
            (opl_emu_fm_operator_phase((*fmch).m_op[1 as libc::c_int as usize]))
                .wrapping_add(opmod as uint32_t),
            am_offset,
        ) >> rshift;
    } else {
        result = op1value
            + (opl_emu_fm_operator_compute_volume(
                (*fmch).m_op[1 as libc::c_int as usize],
                opl_emu_fm_operator_phase((*fmch).m_op[1 as libc::c_int as usize]),
                am_offset,
            ) >> rshift);
        let mut clipmin: int32_t = -clipmax - 1 as libc::c_int;
        result = opl_emu_clamp(result, clipmin, clipmax);
    }
    {let crown_promoted_local_0 = (*fmch).m_choffs;opl_emu_fm_channel_add_to_output(fmch, crown_promoted_local_0, output, result)};
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_output_4op(
    mut fmch: *mut opl_emu_fm_channel,
    mut output: *mut libc::c_short,
    mut rshift: uint32_t,
    mut clipmax: int32_t,
) {
    let mut am_offset: uint32_t = opl_emu_registers_lfo_am_offset(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    let mut opmod: int32_t = 0 as libc::c_int;
    let mut feedback: uint32_t = opl_emu_registers_ch_feedback(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    if feedback != 0 as libc::c_int as uint32_t {
        opmod = (*fmch).m_feedback[0 as libc::c_int as usize] as libc::c_int
            + (*fmch).m_feedback[1 as libc::c_int as usize] as libc::c_int
            >> (10 as libc::c_int as uint32_t).wrapping_sub(feedback);
    }
    (*fmch)
        .m_feedback_in = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[0 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[0 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    ) as int16_t;
    let mut op1value: int32_t = (*fmch).m_feedback_in as int32_t;
    if opl_emu_registers_ch_output_any((*fmch).m_regs, (*fmch).m_choffs)
        == 0 as libc::c_int as uint32_t
    {
        return;
    }
    static mut s_algorithm_ops: [uint16_t; 12] = [
        (1 as libc::c_int | (2 as libc::c_int) << 1 as libc::c_int
            | (3 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (0 as libc::c_int | (5 as libc::c_int) << 1 as libc::c_int
            | (3 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (0 as libc::c_int | (2 as libc::c_int) << 1 as libc::c_int
            | (6 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (1 as libc::c_int | (0 as libc::c_int) << 1 as libc::c_int
            | (7 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (1 as libc::c_int | (0 as libc::c_int) << 1 as libc::c_int
            | (3 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (1 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (1 as libc::c_int | (1 as libc::c_int) << 1 as libc::c_int
            | (1 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (1 as libc::c_int) << 8 as libc::c_int
            | (1 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (1 as libc::c_int | (0 as libc::c_int) << 1 as libc::c_int
            | (0 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (1 as libc::c_int) << 8 as libc::c_int
            | (1 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (0 as libc::c_int | (0 as libc::c_int) << 1 as libc::c_int
            | (0 as libc::c_int) << 4 as libc::c_int
            | (1 as libc::c_int) << 7 as libc::c_int
            | (1 as libc::c_int) << 8 as libc::c_int
            | (1 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (1 as libc::c_int | (2 as libc::c_int) << 1 as libc::c_int
            | (3 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (0 as libc::c_int | (2 as libc::c_int) << 1 as libc::c_int
            | (3 as libc::c_int) << 4 as libc::c_int
            | (1 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (1 as libc::c_int | (0 as libc::c_int) << 1 as libc::c_int
            | (3 as libc::c_int) << 4 as libc::c_int
            | (0 as libc::c_int) << 7 as libc::c_int
            | (1 as libc::c_int) << 8 as libc::c_int
            | (0 as libc::c_int) << 9 as libc::c_int) as uint16_t,
        (0 as libc::c_int | (2 as libc::c_int) << 1 as libc::c_int
            | (0 as libc::c_int) << 4 as libc::c_int
            | (1 as libc::c_int) << 7 as libc::c_int
            | (0 as libc::c_int) << 8 as libc::c_int
            | (1 as libc::c_int) << 9 as libc::c_int) as uint16_t,
    ];
    let mut algorithm_ops: uint32_t = s_algorithm_ops[opl_emu_registers_ch_algorithm(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    ) as usize] as uint32_t;
    let mut opout: [int16_t; 8] = [0; 8];
    opout[0 as libc::c_int as usize] = 0 as libc::c_int as int16_t;
    opout[1 as libc::c_int as usize] = op1value as int16_t;
    opmod = opout[opl_emu_bitfield(algorithm_ops, 0 as libc::c_int, 1 as libc::c_int)
        as usize] as libc::c_int >> 1 as libc::c_int;
    opout[2 as libc::c_int
        as usize] = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[1 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[1 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    ) as int16_t;
    opout[5 as libc::c_int
        as usize] = (opout[1 as libc::c_int as usize] as libc::c_int
        + opout[2 as libc::c_int as usize] as libc::c_int) as int16_t;
    opmod = opout[opl_emu_bitfield(algorithm_ops, 1 as libc::c_int, 3 as libc::c_int)
        as usize] as libc::c_int >> 1 as libc::c_int;
    opout[3 as libc::c_int
        as usize] = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[2 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[2 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    ) as int16_t;
    opout[6 as libc::c_int
        as usize] = (opout[1 as libc::c_int as usize] as libc::c_int
        + opout[3 as libc::c_int as usize] as libc::c_int) as int16_t;
    opout[7 as libc::c_int
        as usize] = (opout[2 as libc::c_int as usize] as libc::c_int
        + opout[3 as libc::c_int as usize] as libc::c_int) as int16_t;
    opmod = opout[opl_emu_bitfield(algorithm_ops, 4 as libc::c_int, 3 as libc::c_int)
        as usize] as libc::c_int >> 1 as libc::c_int;
    let mut result: int32_t = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[3 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[3 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    );
    result >>= rshift;
    let mut clipmin: int32_t = -clipmax - 1 as libc::c_int;
    if opl_emu_bitfield(algorithm_ops, 7 as libc::c_int, 1 as libc::c_int)
        != 0 as libc::c_int as uint32_t
    {
        result = opl_emu_clamp(
            result + (opout[1 as libc::c_int as usize] as libc::c_int >> rshift),
            clipmin,
            clipmax,
        );
    }
    if opl_emu_bitfield(algorithm_ops, 8 as libc::c_int, 1 as libc::c_int)
        != 0 as libc::c_int as uint32_t
    {
        result = opl_emu_clamp(
            result + (opout[2 as libc::c_int as usize] as libc::c_int >> rshift),
            clipmin,
            clipmax,
        );
    }
    if opl_emu_bitfield(algorithm_ops, 9 as libc::c_int, 1 as libc::c_int)
        != 0 as libc::c_int as uint32_t
    {
        result = opl_emu_clamp(
            result + (opout[3 as libc::c_int as usize] as libc::c_int >> rshift),
            clipmin,
            clipmax,
        );
    }
    {let crown_promoted_local_0 = (*fmch).m_choffs;opl_emu_fm_channel_add_to_output(fmch, crown_promoted_local_0, output, result)};
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_output_rhythm_ch6(
    mut fmch: *mut opl_emu_fm_channel,
    mut output: *mut libc::c_short,
    mut rshift: uint32_t,
    mut clipmax: int32_t,
) {
    let mut am_offset: uint32_t = opl_emu_registers_lfo_am_offset(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    let mut opmod: int32_t = 0 as libc::c_int;
    let mut feedback: uint32_t = opl_emu_registers_ch_feedback(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    if feedback != 0 as libc::c_int as uint32_t {
        opmod = (*fmch).m_feedback[0 as libc::c_int as usize] as libc::c_int
            + (*fmch).m_feedback[1 as libc::c_int as usize] as libc::c_int
            >> (10 as libc::c_int as uint32_t).wrapping_sub(feedback);
    }
    (*fmch)
        .m_feedback_in = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[0 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[0 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    ) as int16_t;
    let mut opout1: int32_t = (*fmch).m_feedback_in as int32_t;
    opmod = if opl_emu_bitfield(
        opl_emu_registers_ch_algorithm((*fmch).m_regs, (*fmch).m_choffs),
        0 as libc::c_int,
        1 as libc::c_int,
    ) != 0
    {
        0 as libc::c_int
    } else {
        opout1 >> 1 as libc::c_int
    };
    let mut result: int32_t = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[1 as libc::c_int as usize],
        (opl_emu_fm_operator_phase((*fmch).m_op[1 as libc::c_int as usize]))
            .wrapping_add(opmod as uint32_t),
        am_offset,
    ) >> rshift;
    {let crown_promoted_local_0 = (*fmch).m_choffs;opl_emu_fm_channel_add_to_output(
        fmch,
        crown_promoted_local_0,
        output,
        result * 2 as libc::c_int,
    )};
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_output_rhythm_ch7(
    mut fmch: *mut opl_emu_fm_channel,
    mut phase_select: uint32_t,
    mut output: *mut libc::c_short,
    mut rshift: uint32_t,
    mut clipmax: int32_t,
) {
    let mut am_offset: uint32_t = opl_emu_registers_lfo_am_offset(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    let mut noise_state: uint32_t = opl_emu_bitfield(
        opl_emu_registers_noise_state((*fmch).m_regs),
        0 as libc::c_int,
        1 as libc::c_int,
    );
    let mut phase: uint32_t = phase_select << 9 as libc::c_int
        | (0xd0 as libc::c_int
            >> 2 as libc::c_int as uint32_t * (noise_state ^ phase_select)) as uint32_t;
    let mut result: int32_t = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[0 as libc::c_int as usize],
        phase,
        am_offset,
    ) >> rshift;
    let mut op13phase: uint32_t = opl_emu_fm_operator_phase(
        (*fmch).m_op[0 as libc::c_int as usize],
    );
    phase = ((0x100 as libc::c_int)
        << opl_emu_bitfield(op13phase, 8 as libc::c_int, 1 as libc::c_int)) as uint32_t
        ^ noise_state << 8 as libc::c_int;
    result
        += opl_emu_fm_operator_compute_volume(
            (*fmch).m_op[1 as libc::c_int as usize],
            phase,
            am_offset,
        ) >> rshift;
    result = opl_emu_clamp(result, -clipmax - 1 as libc::c_int, clipmax);
    {let crown_promoted_local_0 = (*fmch).m_choffs;opl_emu_fm_channel_add_to_output(
        fmch,
        crown_promoted_local_0,
        output,
        result * 2 as libc::c_int,
    )};
}
#[no_mangle]
pub unsafe extern "C" fn opl_emu_fm_channel_output_rhythm_ch8(
    mut fmch: *mut opl_emu_fm_channel,
    mut phase_select: uint32_t,
    mut output: *mut libc::c_short,
    mut rshift: uint32_t,
    mut clipmax: int32_t,
) {
    let mut am_offset: uint32_t = opl_emu_registers_lfo_am_offset(
        (*fmch).m_regs,
        (*fmch).m_choffs,
    );
    let mut result: int32_t = opl_emu_fm_operator_compute_volume(
        (*fmch).m_op[0 as libc::c_int as usize],
        opl_emu_fm_operator_phase((*fmch).m_op[0 as libc::c_int as usize]),
        am_offset,
    ) >> rshift;
    let mut phase: uint32_t = 0x100 as libc::c_int as uint32_t
        | phase_select << 9 as libc::c_int;
    result
        += opl_emu_fm_operator_compute_volume(
            (*fmch).m_op[1 as libc::c_int as usize],
            phase,
            am_offset,
        ) >> rshift;
    result = opl_emu_clamp(result, -clipmax - 1 as libc::c_int, clipmax);
    {let crown_promoted_local_0 = (*fmch).m_choffs;opl_emu_fm_channel_add_to_output(
        fmch,
        crown_promoted_local_0,
        output,
        result * 2 as libc::c_int,
    )};
}
#[no_mangle]
pub unsafe extern "C" fn oplregwr(
    mut opl: *mut opl_t,
    mut reg: uint16_t,
    mut data: uint8_t,
) {
    opl_emu_write(&raw mut (*opl).opl_emu, reg, data);
}
#[no_mangle]
pub unsafe extern "C" fn opl_render(
    mut opl: *mut opl_t,
    mut sample_pairs: *mut libc::c_short,
    mut sample_pairs_count: libc::c_int,
    mut volume: libc::c_float,
) {
    memset(
        sample_pairs as *mut libc::c_void,
        0 as libc::c_int,
        ((sample_pairs_count * 2 as libc::c_int) as libc::c_ulong)
            .wrapping_mul(::core::mem::size_of::<libc::c_short>() as libc::c_ulong),
    );
    opl_emu_generate(
        &raw mut (*opl).opl_emu,
        sample_pairs,
        sample_pairs_count as uint32_t,
        volume,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_write(
    mut opl: *mut opl_t,
    mut count: libc::c_int,
    mut regs: *mut libc::c_ushort,
    mut data: *mut libc::c_uchar,
) {
    let mut emu: *mut opl_emu_t = &raw mut (*opl).opl_emu;
    let mut i: libc::c_int = 0 as libc::c_int;
    while i < count {
        let mut regnum: uint16_t = *regs.offset(i as isize);
        let mut value: uint8_t = *data.offset(i as isize);
        if !(regnum as libc::c_int == 0x4 as libc::c_int) {
            (*emu)
                .m_modified_channels = (((1 as libc::c_int) << 18 as libc::c_int)
                - 1 as libc::c_int) as uint32_t;
            let mut keyon_channel: uint32_t = 0;
            let mut keyon_opmask: uint32_t = 0;
            if opl_emu_registers_write(
                &raw mut (*emu).m_regs,
                regnum,
                value,
                &raw mut keyon_channel,
                &raw mut keyon_opmask,
            ) != 0
            {
                if keyon_channel < 18 as libc::c_int as uint32_t {
                    opl_emu_fm_channel_keyonoff(
                        &raw mut *((*emu).m_channel)
                            .as_mut_ptr()
                            .offset(keyon_channel as isize),
                        keyon_opmask,
                        OPL_EMU_KEYON_NORMAL,
                        keyon_channel,
                    );
                } else if 18 as libc::c_int >= 9 as libc::c_int
                    && keyon_channel == 0xff as libc::c_int as uint32_t
                {
                    opl_emu_fm_channel_keyonoff(
                        &raw mut *((*emu).m_channel)
                            .as_mut_ptr()
                            .offset(6 as libc::c_int as isize),
                        (if opl_emu_bitfield(
                            keyon_opmask,
                            4 as libc::c_int,
                            1 as libc::c_int,
                        ) != 0
                        {
                            3 as libc::c_int
                        } else {
                            0 as libc::c_int
                        }) as uint32_t,
                        OPL_EMU_KEYON_RHYTHM,
                        6 as libc::c_int as uint32_t,
                    );
                    opl_emu_fm_channel_keyonoff(
                        &raw mut *((*emu).m_channel)
                            .as_mut_ptr()
                            .offset(7 as libc::c_int as isize),
                        opl_emu_bitfield(
                            keyon_opmask,
                            0 as libc::c_int,
                            1 as libc::c_int,
                        )
                            | opl_emu_bitfield(
                                keyon_opmask,
                                3 as libc::c_int,
                                1 as libc::c_int,
                            ) << 1 as libc::c_int,
                        OPL_EMU_KEYON_RHYTHM,
                        7 as libc::c_int as uint32_t,
                    );
                    opl_emu_fm_channel_keyonoff(
                        &raw mut *((*emu).m_channel)
                            .as_mut_ptr()
                            .offset(8 as libc::c_int as isize),
                        opl_emu_bitfield(
                            keyon_opmask,
                            2 as libc::c_int,
                            1 as libc::c_int,
                        )
                            | opl_emu_bitfield(
                                keyon_opmask,
                                1 as libc::c_int,
                                1 as libc::c_int,
                            ) << 1 as libc::c_int,
                        OPL_EMU_KEYON_RHYTHM,
                        8 as libc::c_int as uint32_t,
                    );
                }
            }
        }
        i += 1;
        i;
    }
}
#[no_mangle]
pub static mut freqtable: [libc::c_ushort; 128] = [
    345 as libc::c_int as libc::c_ushort,
    365 as libc::c_int as libc::c_ushort,
    387 as libc::c_int as libc::c_ushort,
    410 as libc::c_int as libc::c_ushort,
    435 as libc::c_int as libc::c_ushort,
    460 as libc::c_int as libc::c_ushort,
    488 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
    547 as libc::c_int as libc::c_ushort,
    580 as libc::c_int as libc::c_ushort,
    615 as libc::c_int as libc::c_ushort,
    651 as libc::c_int as libc::c_ushort,
    690 as libc::c_int as libc::c_ushort,
    731 as libc::c_int as libc::c_ushort,
    774 as libc::c_int as libc::c_ushort,
    820 as libc::c_int as libc::c_ushort,
    869 as libc::c_int as libc::c_ushort,
    921 as libc::c_int as libc::c_ushort,
    975 as libc::c_int as libc::c_ushort,
    517 as libc::c_int as libc::c_ushort,
];
#[no_mangle]
pub static mut octavetable: [libc::c_uchar; 128] = [
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    0 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    1 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    2 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    3 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    4 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    5 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    6 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    7 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    8 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    9 as libc::c_int as libc::c_uchar,
    10 as libc::c_int as libc::c_uchar,
];
#[no_mangle]
pub static mut pitchtable: [libc::c_ushort; 256] = [
    29193 as libc::c_uint as libc::c_ushort,
    29219 as libc::c_uint as libc::c_ushort,
    29246 as libc::c_uint as libc::c_ushort,
    29272 as libc::c_uint as libc::c_ushort,
    29299 as libc::c_uint as libc::c_ushort,
    29325 as libc::c_uint as libc::c_ushort,
    29351 as libc::c_uint as libc::c_ushort,
    29378 as libc::c_uint as libc::c_ushort,
    29405 as libc::c_uint as libc::c_ushort,
    29431 as libc::c_uint as libc::c_ushort,
    29458 as libc::c_uint as libc::c_ushort,
    29484 as libc::c_uint as libc::c_ushort,
    29511 as libc::c_uint as libc::c_ushort,
    29538 as libc::c_uint as libc::c_ushort,
    29564 as libc::c_uint as libc::c_ushort,
    29591 as libc::c_uint as libc::c_ushort,
    29618 as libc::c_uint as libc::c_ushort,
    29644 as libc::c_uint as libc::c_ushort,
    29671 as libc::c_uint as libc::c_ushort,
    29698 as libc::c_uint as libc::c_ushort,
    29725 as libc::c_uint as libc::c_ushort,
    29752 as libc::c_uint as libc::c_ushort,
    29778 as libc::c_uint as libc::c_ushort,
    29805 as libc::c_uint as libc::c_ushort,
    29832 as libc::c_uint as libc::c_ushort,
    29859 as libc::c_uint as libc::c_ushort,
    29886 as libc::c_uint as libc::c_ushort,
    29913 as libc::c_uint as libc::c_ushort,
    29940 as libc::c_uint as libc::c_ushort,
    29967 as libc::c_uint as libc::c_ushort,
    29994 as libc::c_uint as libc::c_ushort,
    30021 as libc::c_uint as libc::c_ushort,
    30048 as libc::c_uint as libc::c_ushort,
    30076 as libc::c_uint as libc::c_ushort,
    30103 as libc::c_uint as libc::c_ushort,
    30130 as libc::c_uint as libc::c_ushort,
    30157 as libc::c_uint as libc::c_ushort,
    30184 as libc::c_uint as libc::c_ushort,
    30212 as libc::c_uint as libc::c_ushort,
    30239 as libc::c_uint as libc::c_ushort,
    30266 as libc::c_uint as libc::c_ushort,
    30293 as libc::c_uint as libc::c_ushort,
    30321 as libc::c_uint as libc::c_ushort,
    30348 as libc::c_uint as libc::c_ushort,
    30376 as libc::c_uint as libc::c_ushort,
    30403 as libc::c_uint as libc::c_ushort,
    30430 as libc::c_uint as libc::c_ushort,
    30458 as libc::c_uint as libc::c_ushort,
    30485 as libc::c_uint as libc::c_ushort,
    30513 as libc::c_uint as libc::c_ushort,
    30541 as libc::c_uint as libc::c_ushort,
    30568 as libc::c_uint as libc::c_ushort,
    30596 as libc::c_uint as libc::c_ushort,
    30623 as libc::c_uint as libc::c_ushort,
    30651 as libc::c_uint as libc::c_ushort,
    30679 as libc::c_uint as libc::c_ushort,
    30706 as libc::c_uint as libc::c_ushort,
    30734 as libc::c_uint as libc::c_ushort,
    30762 as libc::c_uint as libc::c_ushort,
    30790 as libc::c_uint as libc::c_ushort,
    30817 as libc::c_uint as libc::c_ushort,
    30845 as libc::c_uint as libc::c_ushort,
    30873 as libc::c_uint as libc::c_ushort,
    30901 as libc::c_uint as libc::c_ushort,
    30929 as libc::c_uint as libc::c_ushort,
    30957 as libc::c_uint as libc::c_ushort,
    30985 as libc::c_uint as libc::c_ushort,
    31013 as libc::c_uint as libc::c_ushort,
    31041 as libc::c_uint as libc::c_ushort,
    31069 as libc::c_uint as libc::c_ushort,
    31097 as libc::c_uint as libc::c_ushort,
    31125 as libc::c_uint as libc::c_ushort,
    31153 as libc::c_uint as libc::c_ushort,
    31181 as libc::c_uint as libc::c_ushort,
    31209 as libc::c_uint as libc::c_ushort,
    31237 as libc::c_uint as libc::c_ushort,
    31266 as libc::c_uint as libc::c_ushort,
    31294 as libc::c_uint as libc::c_ushort,
    31322 as libc::c_uint as libc::c_ushort,
    31350 as libc::c_uint as libc::c_ushort,
    31379 as libc::c_uint as libc::c_ushort,
    31407 as libc::c_uint as libc::c_ushort,
    31435 as libc::c_uint as libc::c_ushort,
    31464 as libc::c_uint as libc::c_ushort,
    31492 as libc::c_uint as libc::c_ushort,
    31521 as libc::c_uint as libc::c_ushort,
    31549 as libc::c_uint as libc::c_ushort,
    31578 as libc::c_uint as libc::c_ushort,
    31606 as libc::c_uint as libc::c_ushort,
    31635 as libc::c_uint as libc::c_ushort,
    31663 as libc::c_uint as libc::c_ushort,
    31692 as libc::c_uint as libc::c_ushort,
    31720 as libc::c_uint as libc::c_ushort,
    31749 as libc::c_uint as libc::c_ushort,
    31778 as libc::c_uint as libc::c_ushort,
    31806 as libc::c_uint as libc::c_ushort,
    31835 as libc::c_uint as libc::c_ushort,
    31864 as libc::c_uint as libc::c_ushort,
    31893 as libc::c_uint as libc::c_ushort,
    31921 as libc::c_uint as libc::c_ushort,
    31950 as libc::c_uint as libc::c_ushort,
    31979 as libc::c_uint as libc::c_ushort,
    32008 as libc::c_uint as libc::c_ushort,
    32037 as libc::c_uint as libc::c_ushort,
    32066 as libc::c_uint as libc::c_ushort,
    32095 as libc::c_uint as libc::c_ushort,
    32124 as libc::c_uint as libc::c_ushort,
    32153 as libc::c_uint as libc::c_ushort,
    32182 as libc::c_uint as libc::c_ushort,
    32211 as libc::c_uint as libc::c_ushort,
    32240 as libc::c_uint as libc::c_ushort,
    32269 as libc::c_uint as libc::c_ushort,
    32298 as libc::c_uint as libc::c_ushort,
    32327 as libc::c_uint as libc::c_ushort,
    32357 as libc::c_uint as libc::c_ushort,
    32386 as libc::c_uint as libc::c_ushort,
    32415 as libc::c_uint as libc::c_ushort,
    32444 as libc::c_uint as libc::c_ushort,
    32474 as libc::c_uint as libc::c_ushort,
    32503 as libc::c_uint as libc::c_ushort,
    32532 as libc::c_uint as libc::c_ushort,
    32562 as libc::c_uint as libc::c_ushort,
    32591 as libc::c_uint as libc::c_ushort,
    32620 as libc::c_uint as libc::c_ushort,
    32650 as libc::c_uint as libc::c_ushort,
    32679 as libc::c_uint as libc::c_ushort,
    32709 as libc::c_uint as libc::c_ushort,
    32738 as libc::c_uint as libc::c_ushort,
    32768 as libc::c_uint as libc::c_ushort,
    32798 as libc::c_uint as libc::c_ushort,
    32827 as libc::c_uint as libc::c_ushort,
    32857 as libc::c_uint as libc::c_ushort,
    32887 as libc::c_uint as libc::c_ushort,
    32916 as libc::c_uint as libc::c_ushort,
    32946 as libc::c_uint as libc::c_ushort,
    32976 as libc::c_uint as libc::c_ushort,
    33005 as libc::c_uint as libc::c_ushort,
    33035 as libc::c_uint as libc::c_ushort,
    33065 as libc::c_uint as libc::c_ushort,
    33095 as libc::c_uint as libc::c_ushort,
    33125 as libc::c_uint as libc::c_ushort,
    33155 as libc::c_uint as libc::c_ushort,
    33185 as libc::c_uint as libc::c_ushort,
    33215 as libc::c_uint as libc::c_ushort,
    33245 as libc::c_uint as libc::c_ushort,
    33275 as libc::c_uint as libc::c_ushort,
    33305 as libc::c_uint as libc::c_ushort,
    33335 as libc::c_uint as libc::c_ushort,
    33365 as libc::c_uint as libc::c_ushort,
    33395 as libc::c_uint as libc::c_ushort,
    33425 as libc::c_uint as libc::c_ushort,
    33455 as libc::c_uint as libc::c_ushort,
    33486 as libc::c_uint as libc::c_ushort,
    33516 as libc::c_uint as libc::c_ushort,
    33546 as libc::c_uint as libc::c_ushort,
    33576 as libc::c_uint as libc::c_ushort,
    33607 as libc::c_uint as libc::c_ushort,
    33637 as libc::c_uint as libc::c_ushort,
    33667 as libc::c_uint as libc::c_ushort,
    33698 as libc::c_uint as libc::c_ushort,
    33728 as libc::c_uint as libc::c_ushort,
    33759 as libc::c_uint as libc::c_ushort,
    33789 as libc::c_uint as libc::c_ushort,
    33820 as libc::c_uint as libc::c_ushort,
    33850 as libc::c_uint as libc::c_ushort,
    33881 as libc::c_uint as libc::c_ushort,
    33911 as libc::c_uint as libc::c_ushort,
    33942 as libc::c_uint as libc::c_ushort,
    33973 as libc::c_uint as libc::c_ushort,
    34003 as libc::c_uint as libc::c_ushort,
    34034 as libc::c_uint as libc::c_ushort,
    34065 as libc::c_uint as libc::c_ushort,
    34095 as libc::c_uint as libc::c_ushort,
    34126 as libc::c_uint as libc::c_ushort,
    34157 as libc::c_uint as libc::c_ushort,
    34188 as libc::c_uint as libc::c_ushort,
    34219 as libc::c_uint as libc::c_ushort,
    34250 as libc::c_uint as libc::c_ushort,
    34281 as libc::c_uint as libc::c_ushort,
    34312 as libc::c_uint as libc::c_ushort,
    34343 as libc::c_uint as libc::c_ushort,
    34374 as libc::c_uint as libc::c_ushort,
    34405 as libc::c_uint as libc::c_ushort,
    34436 as libc::c_uint as libc::c_ushort,
    34467 as libc::c_uint as libc::c_ushort,
    34498 as libc::c_uint as libc::c_ushort,
    34529 as libc::c_uint as libc::c_ushort,
    34560 as libc::c_uint as libc::c_ushort,
    34591 as libc::c_uint as libc::c_ushort,
    34623 as libc::c_uint as libc::c_ushort,
    34654 as libc::c_uint as libc::c_ushort,
    34685 as libc::c_uint as libc::c_ushort,
    34716 as libc::c_uint as libc::c_ushort,
    34748 as libc::c_uint as libc::c_ushort,
    34779 as libc::c_uint as libc::c_ushort,
    34811 as libc::c_uint as libc::c_ushort,
    34842 as libc::c_uint as libc::c_ushort,
    34874 as libc::c_uint as libc::c_ushort,
    34905 as libc::c_uint as libc::c_ushort,
    34937 as libc::c_uint as libc::c_ushort,
    34968 as libc::c_uint as libc::c_ushort,
    35000 as libc::c_uint as libc::c_ushort,
    35031 as libc::c_uint as libc::c_ushort,
    35063 as libc::c_uint as libc::c_ushort,
    35095 as libc::c_uint as libc::c_ushort,
    35126 as libc::c_uint as libc::c_ushort,
    35158 as libc::c_uint as libc::c_ushort,
    35190 as libc::c_uint as libc::c_ushort,
    35221 as libc::c_uint as libc::c_ushort,
    35253 as libc::c_uint as libc::c_ushort,
    35285 as libc::c_uint as libc::c_ushort,
    35317 as libc::c_uint as libc::c_ushort,
    35349 as libc::c_uint as libc::c_ushort,
    35381 as libc::c_uint as libc::c_ushort,
    35413 as libc::c_uint as libc::c_ushort,
    35445 as libc::c_uint as libc::c_ushort,
    35477 as libc::c_uint as libc::c_ushort,
    35509 as libc::c_uint as libc::c_ushort,
    35541 as libc::c_uint as libc::c_ushort,
    35573 as libc::c_uint as libc::c_ushort,
    35605 as libc::c_uint as libc::c_ushort,
    35637 as libc::c_uint as libc::c_ushort,
    35669 as libc::c_uint as libc::c_ushort,
    35702 as libc::c_uint as libc::c_ushort,
    35734 as libc::c_uint as libc::c_ushort,
    35766 as libc::c_uint as libc::c_ushort,
    35798 as libc::c_uint as libc::c_ushort,
    35831 as libc::c_uint as libc::c_ushort,
    35863 as libc::c_uint as libc::c_ushort,
    35895 as libc::c_uint as libc::c_ushort,
    35928 as libc::c_uint as libc::c_ushort,
    35960 as libc::c_uint as libc::c_ushort,
    35993 as libc::c_uint as libc::c_ushort,
    36025 as libc::c_uint as libc::c_ushort,
    36058 as libc::c_uint as libc::c_ushort,
    36090 as libc::c_uint as libc::c_ushort,
    36123 as libc::c_uint as libc::c_ushort,
    36155 as libc::c_uint as libc::c_ushort,
    36188 as libc::c_uint as libc::c_ushort,
    36221 as libc::c_uint as libc::c_ushort,
    36254 as libc::c_uint as libc::c_ushort,
    36286 as libc::c_uint as libc::c_ushort,
    36319 as libc::c_uint as libc::c_ushort,
    36352 as libc::c_uint as libc::c_ushort,
    36385 as libc::c_uint as libc::c_ushort,
    36417 as libc::c_uint as libc::c_ushort,
    36450 as libc::c_uint as libc::c_ushort,
    36483 as libc::c_uint as libc::c_ushort,
    36516 as libc::c_uint as libc::c_ushort,
    36549 as libc::c_uint as libc::c_ushort,
    36582 as libc::c_uint as libc::c_ushort,
    36615 as libc::c_uint as libc::c_ushort,
    36648 as libc::c_uint as libc::c_ushort,
    36681 as libc::c_uint as libc::c_ushort,
    36715 as libc::c_uint as libc::c_ushort,
    36748 as libc::c_uint as libc::c_ushort,
];
static mut opl_gmtimbres_default: [opl_timbre_t; 256] = [
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x223e133 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4f4f131 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa5 as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x433f133 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf4f131 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa3 as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4b3e131 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf4f130 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1a as libc::c_int as libc::c_uchar,
            carrier_40: 0x86 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x73fa32 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4f4d111 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xe7f21c as libc::c_int as libc::c_ulong,
            carrier_E862: 0xb8f201 as libc::c_int as libc::c_ulong,
            modulator_40: 0x6f as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xc7f437 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xd7f230 as libc::c_int as libc::c_ulong,
            modulator_40: 0x5d as libc::c_int as libc::c_uchar,
            carrier_40: 0xa as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x303f232 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1f6d131 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x559f101 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf7f111 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x87f607 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xe4f231 as libc::c_int as libc::c_ulong,
            modulator_40: 0x54 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x9 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xa5f33f as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf2c312 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa1 as libc::c_int as libc::c_uchar,
            carrier_40: 0x6 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4561a as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4f601 as libc::c_int as libc::c_ulong,
            modulator_40: 0x9e as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf6f2b2 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf6f281 as libc::c_int as libc::c_ulong,
            modulator_40: 0xe5 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xf as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf6f618 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf7e500 as libc::c_int as libc::c_ulong,
            modulator_40: 0x63 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x96f616 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf5f111 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1f as libc::c_int as libc::c_uchar,
            carrier_40: 0x3 as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x82f307 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xe3f302 as libc::c_int as libc::c_ulong,
            modulator_40: 0x97 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8a as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4109130 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3b5f321 as libc::c_int as libc::c_ulong,
            modulator_40: 0x52 as libc::c_int as libc::c_uchar,
            carrier_40: 0x88 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x116b1a2 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x117d160 as libc::c_int as libc::c_ulong,
            modulator_40: 0x88 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0x7 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf8f032 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf8f001 as libc::c_int as libc::c_ulong,
            modulator_40: 0x65 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x18aa70 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x88ab1 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0xa as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1043030 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1145431 as libc::c_int as libc::c_ulong,
            modulator_40: 0x92 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xd as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x178000 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1176081 as libc::c_int as libc::c_ulong,
            modulator_40: 0x54 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8b as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x25a721 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1264132 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4d as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4faf022 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1a6221 as libc::c_int as libc::c_ulong,
            modulator_40: 0x96 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x107f020 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2055231 as libc::c_int as libc::c_ulong,
            modulator_40: 0x92 as libc::c_int as libc::c_uchar,
            carrier_40: 0x7 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x274a613 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4b8f401 as libc::c_int as libc::c_ulong,
            modulator_40: 0xdd as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5e5f133 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1e4f211 as libc::c_int as libc::c_ulong,
            modulator_40: 0x99 as libc::c_int as libc::c_uchar,
            carrier_40: 0x7 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x21ff021 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x88f211 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa5 as libc::c_int as libc::c_uchar,
            carrier_40: 0x48 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x132ed10 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3e7d210 as libc::c_int as libc::c_ulong,
            modulator_40: 0x87 as libc::c_int as libc::c_uchar,
            carrier_40: 0xa as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf4e430 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf5f330 as libc::c_int as libc::c_ulong,
            modulator_40: 0x92 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf78111 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3f7f054 as libc::c_int as libc::c_ulong,
            modulator_40: 0x40 as libc::c_int as libc::c_uchar,
            carrier_40: 0x45 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf78111 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2f7f054 as libc::c_int as libc::c_ulong,
            modulator_40: 0x40 as libc::c_int as libc::c_uchar,
            carrier_40: 0x45 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x6f78ae4 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x649b1f2 as libc::c_int as libc::c_ulong,
            modulator_40: 0x3 as libc::c_int as libc::c_uchar,
            carrier_40: 0xa as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x209220 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xe6c130 as libc::c_int as libc::c_ulong,
            modulator_40: 0x97 as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xfff030 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf8f131 as libc::c_int as libc::c_ulong,
            modulator_40: 0x9d as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x26aa20 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xd7f131 as libc::c_int as libc::c_ulong,
            modulator_40: 0xcf as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x7511 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xb69212 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1a as libc::c_int as libc::c_uchar,
            carrier_40: 0x40 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2e69419 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5b6b311 as libc::c_int as libc::c_ulong,
            modulator_40: 0x5e as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2e69515 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1b6b211 as libc::c_int as libc::c_ulong,
            modulator_40: 0x17 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf5f430 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf6f330 as libc::c_int as libc::c_ulong,
            modulator_40: 0xe as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1468330 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x17d231 as libc::c_int as libc::c_ulong,
            modulator_40: 0x15 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2257020 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4266161 as libc::c_int as libc::c_ulong,
            modulator_40: 0x95 as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2446070 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2154130 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4e as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x214d070 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1175222 as libc::c_int as libc::c_ulong,
            modulator_40: 0xf as libc::c_int as libc::c_uchar,
            carrier_40: 0x88 as libc::c_int as libc::c_uchar,
            feedconn: 0x2 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x521f570 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4166021 as libc::c_int as libc::c_ulong,
            modulator_40: 0x90 as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x201c3b0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x58321 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8d as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x848521 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x74c411 as libc::c_int as libc::c_ulong,
            modulator_40: 0x69 as libc::c_int as libc::c_uchar,
            carrier_40: 0x7 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x22e133 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf2f131 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa2 as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4c3c413 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xb4d215 as libc::c_int as libc::c_ulong,
            modulator_40: 0x9b as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x223f832 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4055421 as libc::c_int as libc::c_ulong,
            modulator_40: 0x99 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8a as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5059022 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1055521 as libc::c_int as libc::c_ulong,
            modulator_40: 0x5b as libc::c_int as libc::c_uchar,
            carrier_40: 0x85 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1254732 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x40256b1 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa4 as libc::c_int as libc::c_uchar,
            carrier_40: 0xa as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x31121 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1046120 as libc::c_int as libc::c_ulong,
            modulator_40: 0x58 as libc::c_int as libc::c_uchar,
            carrier_40: 0x84 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x55020 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf55021 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1c as libc::c_int as libc::c_uchar,
            carrier_40: 0xf as libc::c_int as libc::c_uchar,
            feedconn: 0x7 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x239b420 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x76121 as libc::c_int as libc::c_ulong,
            modulator_40: 0x50 as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5470f0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x7460b0 as libc::c_int as libc::c_ulong,
            modulator_40: 0x5a as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2436110 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x114d211 as libc::c_int as libc::c_ulong,
            modulator_40: 0x90 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x17b561 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x97f21 as libc::c_int as libc::c_ulong,
            modulator_40: 0x92 as libc::c_int as libc::c_uchar,
            carrier_40: 0x4 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x235270 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x198160 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1e as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x157621 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x378261 as libc::c_int as libc::c_ulong,
            modulator_40: 0x94 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x118537a as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5177432 as libc::c_int as libc::c_ulong,
            modulator_40: 0x21 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x364120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2b7220 as libc::c_int as libc::c_ulong,
            modulator_40: 0x21 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x577320 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x117c020 as libc::c_int as libc::c_ulong,
            modulator_40: 0x19 as libc::c_int as libc::c_uchar,
            carrier_40: 0x3 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x36f120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x337f120 as libc::c_int as libc::c_ulong,
            modulator_40: 0x92 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xa66120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x976120 as libc::c_int as libc::c_ulong,
            modulator_40: 0x9b as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf37010 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1f65051 as libc::c_int as libc::c_ulong,
            modulator_40: 0x51 as libc::c_int as libc::c_uchar,
            carrier_40: 0x4 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1067021 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1165231 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8a as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xb9820 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x10b5330 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8e as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x10b8020 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x11b6330 as libc::c_int as libc::c_ulong,
            modulator_40: 0x87 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x235030 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x76c62 as libc::c_int as libc::c_ulong,
            modulator_40: 0x58 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2077820 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2074331 as libc::c_int as libc::c_ulong,
            modulator_40: 0x97 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x199030 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1b6132 as libc::c_int as libc::c_ulong,
            modulator_40: 0x95 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x177531 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x174530 as libc::c_int as libc::c_ulong,
            modulator_40: 0x93 as libc::c_int as libc::c_uchar,
            carrier_40: 0x3 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x8d6ef1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2a3571 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x8860a1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2a6561 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa6 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2176522 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x277421 as libc::c_int as libc::c_ulong,
            modulator_40: 0x5a as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1273471 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1745b0 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8d as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x457e1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x375760 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa8 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x6543739 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x25d67a1 as libc::c_int as libc::c_ulong,
            modulator_40: 0x28 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xf31d0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x53270 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc7 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xb as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x581a1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x295230 as libc::c_int as libc::c_ulong,
            modulator_40: 0x37 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x20fff22 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x60fff21 as libc::c_int as libc::c_ulong,
            modulator_40: 0x7f as libc::c_int as libc::c_uchar,
            carrier_40: 0x12 as libc::c_int as libc::c_uchar,
            feedconn: 0x5 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x39bc120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x368c030 as libc::c_int as libc::c_ulong,
            modulator_40: 0xbf as libc::c_int as libc::c_uchar,
            carrier_40: 0x6 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x33357f0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x767e0 as libc::c_int as libc::c_ulong,
            modulator_40: 0x28 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x40457e1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3d67e0 as libc::c_int as libc::c_ulong,
            modulator_40: 0x23 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x32b7320 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x12bf131 as libc::c_int as libc::c_ulong,
            modulator_40: 0x40 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5029071 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x69060 as libc::c_int as libc::c_ulong,
            modulator_40: 0x96 as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x195c120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1637030 as libc::c_int as libc::c_ulong,
            modulator_40: 0x43 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x132ed10 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3e7d210 as libc::c_int as libc::c_ulong,
            modulator_40: 0x87 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2946374 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5a0a1 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa5 as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0x2 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x521a1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x53360 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x9 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2a5a120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x196a120 as libc::c_int as libc::c_ulong,
            modulator_40: 0x95 as libc::c_int as libc::c_uchar,
            carrier_40: 0x5 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5f0e0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x548160 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xb as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x336183 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5452e0 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa7 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2529082 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1534340 as libc::c_int as libc::c_ulong,
            modulator_40: 0x9d as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2345231 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2135120 as libc::c_int as libc::c_ulong,
            modulator_40: 0x98 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1521161 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1632060 as libc::c_int as libc::c_ulong,
            modulator_40: 0x90 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x157b260 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x19f803 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4 as libc::c_int as libc::c_uchar,
            carrier_40: 0x40 as libc::c_int as libc::c_uchar,
            feedconn: 0x7 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2322122 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x133221 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8c as libc::c_int as libc::c_uchar,
            carrier_40: 0x92 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x74f624 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x249303 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc0 as libc::c_int as libc::c_uchar,
            carrier_40: 0xd as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x3d2c091 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1d2d130 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8e as libc::c_int as libc::c_uchar,
            carrier_40: 0x3 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5f29052 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xf2c240 as libc::c_int as libc::c_ulong,
            modulator_40: 0x96 as libc::c_int as libc::c_uchar,
            carrier_40: 0x6 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5213e1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2131371 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1a as libc::c_int as libc::c_uchar,
            carrier_40: 0x88 as libc::c_int as libc::c_uchar,
            feedconn: 0x7 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xb67060 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x928031 as libc::c_int as libc::c_ulong,
            modulator_40: 0x9c as libc::c_int as libc::c_uchar,
            carrier_40: 0x11 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x25511 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1748201 as libc::c_int as libc::c_ulong,
            modulator_40: 0x94 as libc::c_int as libc::c_uchar,
            carrier_40: 0x6 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xb37120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5f48220 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1b as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x2 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x127530 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6f4f310 as libc::c_int as libc::c_ulong,
            modulator_40: 0xd as libc::c_int as libc::c_uchar,
            carrier_40: 0xa as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x33f900 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x273f400 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x332f320 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6e49423 as libc::c_int as libc::c_ulong,
            modulator_40: 0xe as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x328413 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x73b410 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa1 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xf as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1397931 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x2099b22 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x302a130 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x266221 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1e as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x136030 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x1169130 as libc::c_int as libc::c_ulong,
            modulator_40: 0x12 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x32a115 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x172b212 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0x1 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1e795 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x679616 as libc::c_int as libc::c_ulong,
            modulator_40: 0x81 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4046303 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5a901 as libc::c_int as libc::c_ulong,
            modulator_40: 0xca as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x6d1f817 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x98f611 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa7 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x8f312 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x4f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8 as libc::c_int as libc::c_uchar,
            carrier_40: 0xc8 as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 46 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xc8a820 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xb7e601 as libc::c_int as libc::c_ulong,
            modulator_40: 0xb as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x437d2 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x343471 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa1 as libc::c_int as libc::c_uchar,
            carrier_40: 0x7 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2114109 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x51d2101 as libc::c_int as libc::c_ulong,
            modulator_40: 0x5 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x4543310 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3574515 as libc::c_int as libc::c_ulong,
            modulator_40: 0x19 as libc::c_int as libc::c_uchar,
            carrier_40: 0x3 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x437d2 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x343471 as libc::c_int as libc::c_ulong,
            modulator_40: 0xa1 as libc::c_int as libc::c_uchar,
            carrier_40: 0x7 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x200c327 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6021300 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 65 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x3ebd7 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6845d8 as libc::c_int as libc::c_ulong,
            modulator_40: 0xd4 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x7 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x62fda20 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x614b009 as libc::c_int as libc::c_ulong,
            modulator_40: 0x42 as libc::c_int as libc::c_uchar,
            carrier_40: 0x48 as libc::c_int as libc::c_uchar,
            feedconn: 0x4 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x101fe30 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6142120 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 17 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x200832f as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6044020 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 65 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x230732f as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6e6f400 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x2 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xf as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x57fb00 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x46f800 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xe as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 25 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x277f810 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6fc11 as libc::c_int as libc::c_ulong,
            modulator_40: 0x86 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 34 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x287f702 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x678f802 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0x88 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 61 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x6ef8801 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x608b502 as libc::c_int as libc::c_ulong,
            modulator_40: 0xd as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xc as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 38 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x5476c1 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x30892c5 as libc::c_int as libc::c_ulong,
            modulator_40: 0x80 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 37 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x6ef8800 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x608f502 as libc::c_int as libc::c_ulong,
            modulator_40: 0x13 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 38 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x508f601 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x104f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 32 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x254f307 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x307f905 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4 as libc::c_int as libc::c_uchar,
            carrier_40: 0xb as libc::c_int as libc::c_uchar,
            feedconn: 0x6 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 48 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x508f601 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x104f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 34 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x254d307 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3288905 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0xa as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 48 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x508f601 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x104f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 37 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2f2e327 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3f5c525 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0x8 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 48 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x508f601 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x104f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 40 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x508f601 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x104f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 43 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x292f108 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x354f201 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 61 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x508f601 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x104f600 as libc::c_int as libc::c_ulong,
            modulator_40: 0xc as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 46 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x210f509 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x305fe03 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8a as libc::c_int as libc::c_uchar,
            carrier_40: 0x88 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 60 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x283e108 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x334d700 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 79 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2e1f119 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3f3f11b as libc::c_int as libc::c_ulong,
            modulator_40: 0x4 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 62 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2777603 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3679601 as libc::c_int as libc::c_ulong,
            modulator_40: 0x87 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 80 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x251f206 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x263c504 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4 as libc::c_int as libc::c_uchar,
            carrier_40: 0x9 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 67 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x366f905 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x99f701 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 58 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x292f108 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x354f201 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x3 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 62 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x422f120 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x56b40e as libc::c_int as libc::c_ulong,
            modulator_40: 0x81 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 24 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x212fd04 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x305fd03 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 61 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2a8f9e3 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x779643 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1e as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 41 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2a8f9e3 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x779643 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1e as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 35 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xa8f7e9 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5d8990a as libc::c_int as libc::c_ulong,
            modulator_40: 0x8 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 29 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2a8f9e2 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x779642 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1e as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 41 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x2a8f9e2 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x779642 as libc::c_int as libc::c_ulong,
            modulator_40: 0x1e as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 37 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x456fb02 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x17f700 as libc::c_int as libc::c_ulong,
            modulator_40: 0x81 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 55 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x456fb02 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x17f700 as libc::c_int as libc::c_ulong,
            modulator_40: 0x81 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 48 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x367fd01 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x98f601 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 78 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x367fd01 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x98f601 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x8 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 73 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x25e780c as libc::c_int as libc::c_ulong,
            carrier_E862: 0x32b8a0a as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 88 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x98600f as libc::c_int as libc::c_ulong,
            carrier_E862: 0x3fc8590 as libc::c_int as libc::c_ulong,
            modulator_40: 0x8 as libc::c_int as libc::c_uchar,
            carrier_40: 0xc0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 40 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x9f020 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x37da588 as libc::c_int as libc::c_ulong,
            modulator_40: 0x7 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 45 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xfc020 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x32da5a8 as libc::c_int as libc::c_ulong,
            modulator_40: 0x7 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 42 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x106f680 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x16f610 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 48 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x106f680 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x16f610 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 48 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0xd1f815 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x78f512 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 73 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1d1f813 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x78f512 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 68 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1d1f813 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x78f512 as libc::c_int as libc::c_ulong,
            modulator_40: 0x44 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 61 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1dc5d01 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x6ff79f as libc::c_int as libc::c_ulong,
            modulator_40: 0xb as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 16 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x1c7c900 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x5ff49f as libc::c_int as libc::c_ulong,
            modulator_40: 0x7 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 16 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x160f2c6 as libc::c_int as libc::c_ulong,
            carrier_E862: 0x7af4d4 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4f as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 90 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0x160f286 as libc::c_int as libc::c_ulong,
            carrier_E862: 0xb7f294 as libc::c_int as libc::c_ulong,
            modulator_40: 0x4f as libc::c_int as libc::c_uchar,
            carrier_40: 0x80 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 90 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
    {
        let mut init = opl_timbre_t {
            modulator_E862: 0 as libc::c_int as libc::c_ulong,
            carrier_E862: 0 as libc::c_int as libc::c_ulong,
            modulator_40: 0 as libc::c_int as libc::c_uchar,
            carrier_40: 0 as libc::c_int as libc::c_uchar,
            feedconn: 0 as libc::c_int as libc::c_uchar,
            finetune: 0 as libc::c_int as libc::c_schar,
            notenum: 0 as libc::c_int as libc::c_uchar,
            noteoffset: 0,
        };
        init
    },
];
#[no_mangle]
pub static mut op1offsets: [libc::c_ushort; 18] = [
    0 as libc::c_int as libc::c_ushort,
    0x1 as libc::c_int as libc::c_ushort,
    0x2 as libc::c_int as libc::c_ushort,
    0x8 as libc::c_int as libc::c_ushort,
    0x9 as libc::c_int as libc::c_ushort,
    0xa as libc::c_int as libc::c_ushort,
    0x10 as libc::c_int as libc::c_ushort,
    0x11 as libc::c_int as libc::c_ushort,
    0x12 as libc::c_int as libc::c_ushort,
    0x100 as libc::c_int as libc::c_ushort,
    0x101 as libc::c_int as libc::c_ushort,
    0x102 as libc::c_int as libc::c_ushort,
    0x108 as libc::c_int as libc::c_ushort,
    0x109 as libc::c_int as libc::c_ushort,
    0x10a as libc::c_int as libc::c_ushort,
    0x110 as libc::c_int as libc::c_ushort,
    0x111 as libc::c_int as libc::c_ushort,
    0x112 as libc::c_int as libc::c_ushort,
];
#[no_mangle]
pub static mut op2offsets: [libc::c_ushort; 18] = [
    0x3 as libc::c_int as libc::c_ushort,
    0x4 as libc::c_int as libc::c_ushort,
    0x5 as libc::c_int as libc::c_ushort,
    0xb as libc::c_int as libc::c_ushort,
    0xc as libc::c_int as libc::c_ushort,
    0xd as libc::c_int as libc::c_ushort,
    0x13 as libc::c_int as libc::c_ushort,
    0x14 as libc::c_int as libc::c_ushort,
    0x15 as libc::c_int as libc::c_ushort,
    0x103 as libc::c_int as libc::c_ushort,
    0x104 as libc::c_int as libc::c_ushort,
    0x105 as libc::c_int as libc::c_ushort,
    0x10b as libc::c_int as libc::c_ushort,
    0x10c as libc::c_int as libc::c_ushort,
    0x10d as libc::c_int as libc::c_ushort,
    0x113 as libc::c_int as libc::c_ushort,
    0x114 as libc::c_int as libc::c_ushort,
    0x115 as libc::c_int as libc::c_ushort,
];
static mut voicescount: libc::c_int = 9 as libc::c_int;
unsafe extern "C" fn calc_vol(mut regbyte: *mut libc::c_uchar, mut volume: libc::c_int) {
    let mut level: libc::c_int = 0;
    level = !(*regbyte as libc::c_int);
    level &= 0x3f as libc::c_int;
    level = level * volume / 127 as libc::c_int;
    if level > 0x3f as libc::c_int {
        level = 0x3f as libc::c_int;
    }
    if level < 0 as libc::c_int {
        level = 0 as libc::c_int;
    }
    level = !level;
    level &= 0x3f as libc::c_int;
    *regbyte = (*regbyte as libc::c_int & 0xc0 as libc::c_int) as libc::c_uchar;
    *regbyte = (*regbyte as libc::c_int | level) as libc::c_uchar;
}
#[no_mangle]
pub unsafe extern "C" fn opl_create() -> *mut opl_t {
    let mut opl: *mut opl_t = calloc(
        1 as libc::c_int as libc::c_ulong,
        ::core::mem::size_of::<opl_t>() as libc::c_ulong,
    ) as *mut opl_t;
    if opl.is_null() {std::intrinsics::assume((opl).addr() == 0);
        return 0 as *mut opl_t;
    }
    memcpy(
        ((*opl).opl_gmtimbres).as_mut_ptr() as *mut libc::c_void,
        opl_gmtimbres_default.as_mut_ptr() as *const libc::c_void,
        ::core::mem::size_of::<[opl_timbre_t; 256]>() as libc::c_ulong,
    );
    opl_emu_init(&raw mut (*opl).opl_emu);
    (*opl).is_op2 = 0 as libc::c_int;
    oplregwr(opl, 0x4 as libc::c_int as uint16_t, 0x60 as libc::c_int as uint8_t);
    oplregwr(opl, 0x4 as libc::c_int as uint16_t, 0x80 as libc::c_int as uint8_t);
    oplregwr(opl, 0x2 as libc::c_int as uint16_t, 0xff as libc::c_int as uint8_t);
    oplregwr(opl, 0x4 as libc::c_int as uint16_t, 0x21 as libc::c_int as uint8_t);
    oplregwr(opl, 0x4 as libc::c_int as uint16_t, 0x60 as libc::c_int as uint8_t);
    oplregwr(opl, 0x4 as libc::c_int as uint16_t, 0x80 as libc::c_int as uint8_t);
    (*opl).opl3 = 1 as libc::c_int;
    voicescount = 9 as libc::c_int;
    if (*opl).opl3 != 0 as libc::c_int {
        oplregwr(opl, 0x105 as libc::c_int as uint16_t, 1 as libc::c_int as uint8_t);
        oplregwr(opl, 0x104 as libc::c_int as uint16_t, 0 as libc::c_int as uint8_t);
        voicescount = 18 as libc::c_int;
    }
    oplregwr(opl, 0x1 as libc::c_int as uint16_t, 0x20 as libc::c_int as uint8_t);
    oplregwr(opl, 0x4 as libc::c_int as uint16_t, 0 as libc::c_int as uint8_t);
    oplregwr(opl, 0x8 as libc::c_int as uint16_t, 0x40 as libc::c_int as uint8_t);
    oplregwr(opl, 0xbd as libc::c_int as uint16_t, 0 as libc::c_int as uint8_t);
    let mut x: libc::c_int = 0 as libc::c_int;
    while x < voicescount {
        oplregwr(
            opl,
            (0x20 as libc::c_int + op1offsets[x as usize] as libc::c_int) as uint16_t,
            0x1 as libc::c_int as uint8_t,
        );
        oplregwr(
            opl,
            (0x20 as libc::c_int + op2offsets[x as usize] as libc::c_int) as uint16_t,
            0x1 as libc::c_int as uint8_t,
        );
        oplregwr(
            opl,
            (0x40 as libc::c_int + op1offsets[x as usize] as libc::c_int) as uint16_t,
            0x10 as libc::c_int as uint8_t,
        );
        oplregwr(
            opl,
            (0x40 as libc::c_int + op2offsets[x as usize] as libc::c_int) as uint16_t,
            0x10 as libc::c_int as uint8_t,
        );
        x += 1;
        x;
    }
    opl_clear(opl);
    return opl;
}
#[no_mangle]
pub unsafe extern "C" fn opl_destroy(mut opl: *mut opl_t) {
    let mut x: libc::c_int = 0;
    opl_clear(opl);
    x = 0 as libc::c_int;
    while x < voicescount {
        oplregwr(
            opl,
            (0x40 as libc::c_int + op1offsets[x as usize] as libc::c_int) as uint16_t,
            0x1f as libc::c_int as uint8_t,
        );
        oplregwr(
            opl,
            (0x40 as libc::c_int + op2offsets[x as usize] as libc::c_int) as uint16_t,
            0x1f as libc::c_int as uint8_t,
        );
        x += 1;
        x;
    }
    if (*opl).opl3 != 0 as libc::c_int {
        oplregwr(opl, 0x105 as libc::c_int as uint16_t, 0 as libc::c_int as uint8_t);
    }
    free(opl as *mut libc::c_void);
    opl = 0 as *mut opl_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_noteoff(mut opl: *mut opl_t, mut voice: libc::c_ushort) {
    if voice as libc::c_int >= 9 as libc::c_int {
        oplregwr(
            opl,
            (0x1b0 as libc::c_int + voice as libc::c_int - 9 as libc::c_int) as uint16_t,
            0 as libc::c_int as uint8_t,
        );
    } else {
        oplregwr(
            opl,
            (0xb0 as libc::c_int + voice as libc::c_int) as uint16_t,
            0 as libc::c_int as uint8_t,
        );
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_noteon(
    mut opl: *mut opl_t,
    mut voice: libc::c_ushort,
    mut note: libc::c_uint,
    mut pitch: libc::c_int,
) {
    let mut freq: libc::c_uint = freqtable[note as usize] as libc::c_uint;
    let mut octave: libc::c_uint = octavetable[note as usize] as libc::c_uint;
    if pitch != 0 as libc::c_int {
        if pitch > 127 as libc::c_int {
            pitch = 127 as libc::c_int;
        } else if pitch < -(128 as libc::c_int) {
            pitch = -(128 as libc::c_int);
        }
        freq = ((freq as libc::c_ulong)
            .wrapping_mul(
                pitchtable[(pitch + 128 as libc::c_int) as usize] as libc::c_ulong,
            ) >> 15 as libc::c_int) as libc::c_uint;
        if freq >= 1024 as libc::c_int as libc::c_uint {
            freq >>= 1 as libc::c_int;
            octave = octave.wrapping_add(1);
            octave;
        }
    }
    if octave > 7 as libc::c_int as libc::c_uint {
        octave = 7 as libc::c_int as libc::c_uint;
    }
    if voice as libc::c_int >= 9 as libc::c_int {
        voice = (voice as libc::c_int - 9 as libc::c_int) as libc::c_ushort;
        voice = (voice as libc::c_int | 0x100 as libc::c_int) as libc::c_ushort;
    }
    oplregwr(
        opl,
        (0xa0 as libc::c_int + voice as libc::c_int) as uint16_t,
        (freq & 0xff as libc::c_int as libc::c_uint) as uint8_t,
    );
    oplregwr(
        opl,
        (0xb0 as libc::c_int + voice as libc::c_int) as uint16_t,
        (freq >> 8 as libc::c_int | octave << 2 as libc::c_int
            | 32 as libc::c_int as libc::c_uint) as uint8_t,
    );
}
#[no_mangle]
pub unsafe extern "C" fn opl_clear(mut opl: *mut opl_t) {
    let mut x: libc::c_int = 0;
    let mut y: libc::c_int = 0;
    x = 0 as libc::c_int;
    while x < voicescount {
        opl_noteoff(opl, x as libc::c_ushort);
        x += 1;
        x;
    }
    oplregwr(opl, 0xbd as libc::c_int as uint16_t, 0 as libc::c_int as uint8_t);
    x = 0 as libc::c_int;
    while x < voicescount {
        (*opl).voices2notes[x as usize].channel = -(1 as libc::c_int) as libc::c_schar;
        (*opl).voices2notes[x as usize].note = -(1 as libc::c_int) as libc::c_schar;
        (*opl).voices2notes[x as usize].timbreid = -(1 as libc::c_int) as libc::c_short;
        (*opl)
            .voices2notes[x as usize]
            .voiceindex = 0xff as libc::c_int as libc::c_uchar;
        x += 1;
        x;
    }
    x = 0 as libc::c_int;
    while x < 16 as libc::c_int {
        y = 0 as libc::c_int;
        while y < 128 as libc::c_int {
            (*opl)
                .notes2voices[x
                as usize][y
                as usize][0 as libc::c_int
                as usize] = -(1 as libc::c_int) as libc::c_schar;
            (*opl)
                .notes2voices[x
                as usize][y
                as usize][1 as libc::c_int
                as usize] = -(1 as libc::c_int) as libc::c_schar;
            y += 1;
            y;
        }
        x += 1;
        x;
    }
    x = 0 as libc::c_int;
    while x < 16 as libc::c_int {
        opl_midi_changeprog(opl, x, x);
        (*opl).channelvol[x as usize] = 127 as libc::c_int as libc::c_ushort;
        x += 1;
        x;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_pitchwheel(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut pitchwheel: libc::c_int,
) {
    let mut x: libc::c_int = 0;
    x = 0 as libc::c_int;
    while x < voicescount {
        if !((*opl).voices2notes[x as usize].channel as libc::c_int != channel) {
            let mut timbre: *mut opl_timbre_t = if (*opl)
                .voices2notes[x as usize]
                .voiceindex as libc::c_int == 0 as libc::c_int
            {
                &raw mut *((*opl).opl_gmtimbres)
                    .as_mut_ptr()
                    .offset(
                        (*((*opl).voices2notes).as_mut_ptr().offset(x as isize)).timbreid
                            as isize,
                    ) as *mut opl_timbre_t
            } else {
                &raw mut *((*opl).opl_gmtimbres_voice2)
                    .as_mut_ptr()
                    .offset(
                        (*((*opl).voices2notes).as_mut_ptr().offset(x as isize)).timbreid
                            as isize,
                    ) as *mut opl_timbre_t
            };
            opl_noteon(
                opl,
                x as libc::c_ushort,
                ((*opl).voices2notes[x as usize].note as libc::c_int
                    + (*timbre).noteoffset as libc::c_int) as libc::c_uint,
                pitchwheel + (*timbre).finetune as libc::c_int,
            );
        }
        x += 1;
        x;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_controller(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut id: libc::c_int,
    mut value: libc::c_int,
) {
    let mut x: libc::c_int = 0;
    match id {
        11 => {
            (*opl).channelvol[channel as usize] = value as libc::c_ushort;
        }
        123 | 120 => {
            x = 0 as libc::c_int;
            while x < voicescount {
                if !((*opl).voices2notes[x as usize].channel as libc::c_int != channel) {
                    opl_midi_noteoff(
                        opl,
                        channel,
                        (*opl).voices2notes[x as usize].note as libc::c_int,
                    );
                }
                x += 1;
                x;
            }
        }
        _ => {}
    };
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_changeprog(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut program: libc::c_int,
) {
    if channel == 9 as libc::c_int {
        return;
    }
    (*opl).channelprog[channel as usize] = program as libc::c_uchar;
}
#[no_mangle]
pub unsafe extern "C" fn opl_loadinstrument(
    mut opl: *mut opl_t,
    mut voice: libc::c_int,
    mut timbre: *mut opl_timbre_t,
) {
    oplregwr(
        opl,
        (0x40 as libc::c_int + op1offsets[voice as usize] as libc::c_int) as uint16_t,
        (*timbre).modulator_40,
    );
    oplregwr(
        opl,
        (0x40 as libc::c_int + op2offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).carrier_40 as libc::c_int | 0x3f as libc::c_int) as uint8_t,
    );
    oplregwr(
        opl,
        (0xe0 as libc::c_int + op1offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).modulator_E862 >> 24 as libc::c_int) as uint8_t,
    );
    oplregwr(
        opl,
        (0xe0 as libc::c_int + op2offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).carrier_E862 >> 24 as libc::c_int) as uint8_t,
    );
    oplregwr(
        opl,
        (0x80 as libc::c_int + op1offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).modulator_E862 >> 16 as libc::c_int
            & 0xff as libc::c_int as libc::c_ulong) as uint8_t,
    );
    oplregwr(
        opl,
        (0x80 as libc::c_int + op2offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).carrier_E862 >> 16 as libc::c_int
            & 0xff as libc::c_int as libc::c_ulong) as uint8_t,
    );
    oplregwr(
        opl,
        (0x60 as libc::c_int + op1offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).modulator_E862 >> 8 as libc::c_int
            & 0xff as libc::c_int as libc::c_ulong) as uint8_t,
    );
    oplregwr(
        opl,
        (0x60 as libc::c_int + op2offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).carrier_E862 >> 8 as libc::c_int
            & 0xff as libc::c_int as libc::c_ulong) as uint8_t,
    );
    oplregwr(
        opl,
        (0x20 as libc::c_int + op1offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).modulator_E862 & 0xff as libc::c_int as libc::c_ulong) as uint8_t,
    );
    oplregwr(
        opl,
        (0x20 as libc::c_int + op2offsets[voice as usize] as libc::c_int) as uint16_t,
        ((*timbre).carrier_E862 & 0xff as libc::c_int as libc::c_ulong) as uint8_t,
    );
    if voice >= 9 as libc::c_int {
        voice -= 9 as libc::c_int;
        voice |= 0x100 as libc::c_int;
    }
    if (*opl).opl3 != 0 as libc::c_int {
        oplregwr(
            opl,
            (0xc0 as libc::c_int + voice) as uint16_t,
            ((*timbre).feedconn as libc::c_int | 0x30 as libc::c_int) as uint8_t,
        );
    } else {
        oplregwr(opl, (0xc0 as libc::c_int + voice) as uint16_t, (*timbre).feedconn);
    };
}
unsafe extern "C" fn voicevolume(
    mut opl: *mut opl_t,
    mut voice: libc::c_ushort,
    mut timbre: *const opl_timbre_t,
    mut volume: libc::c_int,
) {
    let mut carrierval: libc::c_uchar = (*timbre).carrier_40;
    if volume == 0 as libc::c_int {
        carrierval = (carrierval as libc::c_int | 0x3f as libc::c_int) as libc::c_uchar;
    } else {
        calc_vol(&raw mut carrierval, volume);
    }
    oplregwr(
        opl,
        (0x40 as libc::c_int + op2offsets[voice as usize] as libc::c_int) as uint16_t,
        carrierval,
    );
}
unsafe extern "C" fn getinstrument(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut note: libc::c_int,
) -> libc::c_int {
    if note < 0 as libc::c_int || note > 127 as libc::c_int
        || channel > 15 as libc::c_int
    {
        return -(1 as libc::c_int);
    }
    if channel == 9 as libc::c_int {
        if (*opl).is_op2 != 0 {
            return 128 as libc::c_int + note - 35 as libc::c_int
        } else {
            return 128 as libc::c_int | note
        }
    }
    return (*opl).channelprog[channel as usize] as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_noteon_op2(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut note: libc::c_int,
    mut velocity: libc::c_int,
    mut vindex: libc::c_int,
) {
    if velocity == 0 as libc::c_int {
        opl_midi_noteoff_op2(opl, channel, note, vindex);
        return;
    }
    let mut x: libc::c_int = 0;
    let mut voice: libc::c_int = -(1 as libc::c_int);
    let mut lowestpriority: libc::c_int = 0xffff as libc::c_int;
    let mut highestvoiceindex: libc::c_int = -(1 as libc::c_int);
    let mut lowestpriorityvoice: libc::c_int = -(1 as libc::c_int);
    let mut instrument: libc::c_int = 0;
    instrument = getinstrument(opl, channel, note);
    if instrument < 0 as libc::c_int {
        return;
    }
    if vindex > 0 as libc::c_int
        && (*opl).op2_flags[instrument as usize] as libc::c_uint
            & OP2_DOUBLEVOICE as libc::c_int as libc::c_uint
            == 0 as libc::c_int as libc::c_uint
    {
        return;
    }
    let mut timbre: *mut opl_timbre_t = if vindex == 0 as libc::c_int {
        &raw mut *((*opl).opl_gmtimbres).as_mut_ptr().offset(instrument as isize)
            as *mut opl_timbre_t
    } else {
        &raw mut *((*opl).opl_gmtimbres_voice2).as_mut_ptr().offset(instrument as isize)
            as *mut opl_timbre_t
    };
    if (*opl).notes2voices[channel as usize][note as usize][vindex as usize]
        as libc::c_int >= 0 as libc::c_int
    {
        voice = (*opl).notes2voices[channel as usize][note as usize][vindex as usize]
            as libc::c_int;
    } else {
        x = 0 as libc::c_int;
        while x < voicescount {
            if ((*opl).voices2notes[x as usize].channel as libc::c_int)
                < 0 as libc::c_int
            {
                voice = x;
                if (*opl).voices2notes[x as usize].timbreid as libc::c_int == instrument
                    && (*opl).voices2notes[x as usize].voiceindex as libc::c_int
                        == vindex
                {
                    break;
                }
            }
            if ((*opl).voices2notes[x as usize].priority as libc::c_int) < lowestpriority
            {
                if (*opl).voices2notes[x as usize].voiceindex as libc::c_int >= vindex
                    && (*opl).voices2notes[x as usize].voiceindex as libc::c_int
                        >= highestvoiceindex
                {
                    lowestpriorityvoice = x;
                    lowestpriority = (*opl).voices2notes[x as usize].priority
                        as libc::c_int;
                    highestvoiceindex = (*opl).voices2notes[x as usize].voiceindex
                        as libc::c_int;
                }
            }
            x += 1;
            x;
        }
        if voice < 0 as libc::c_int {
            if lowestpriorityvoice < 0 as libc::c_int {
                return;
            }
            voice = lowestpriorityvoice;
            {let crown_promoted_local_0 = (*opl).voices2notes[voice as usize].channel as libc::c_int;opl_midi_noteoff_op2(
                opl,
                crown_promoted_local_0,
                (*opl).voices2notes[voice as usize].note as libc::c_int,
                (*opl).voices2notes[voice as usize].voiceindex as libc::c_int,
            )};
        }
    }
    if (*opl).voices2notes[voice as usize].timbreid as libc::c_int != instrument {
        (*opl).voices2notes[voice as usize].timbreid = instrument as libc::c_short;
        opl_loadinstrument(opl, voice, timbre);
    }
    (*opl).voices2notes[voice as usize].channel = channel as libc::c_schar;
    (*opl).voices2notes[voice as usize].note = note as libc::c_schar;
    (*opl)
        .voices2notes[voice as usize]
        .priority = (16 as libc::c_int - channel << 8 as libc::c_int
        | 0xff as libc::c_int) as libc::c_ushort;
    (*opl).voices2notes[voice as usize].voiceindex = vindex as libc::c_uchar;
    (*opl)
        .notes2voices[channel
        as usize][note as usize][vindex as usize] = voice as libc::c_schar;
    if vindex != 0 as libc::c_int {
        let mut reducedprio: libc::c_int = (*opl).voices2notes[voice as usize].priority
            as libc::c_int - 0xff as libc::c_int;
        if reducedprio < 0 as libc::c_int {
            reducedprio = 0 as libc::c_int;
        }
        (*opl).voices2notes[voice as usize].priority = reducedprio as libc::c_ushort;
    }
    voicevolume(
        opl,
        voice as libc::c_ushort,
        timbre,
        velocity * (*opl).channelvol[channel as usize] as libc::c_int
            / 127 as libc::c_int,
    );
    if channel == 9 as libc::c_int {
        opl_noteon(
            opl,
            voice as libc::c_ushort,
            ((*timbre).notenum as libc::c_int + (*timbre).noteoffset as libc::c_int)
                as libc::c_uint,
            (*opl).channelpitch[channel as usize] as libc::c_int
                + (*timbre).finetune as libc::c_int,
        );
    } else {
        opl_noteon(
            opl,
            voice as libc::c_ushort,
            (note + (*timbre).noteoffset as libc::c_int) as libc::c_uint,
            (*opl).channelpitch[channel as usize] as libc::c_int
                + (*timbre).finetune as libc::c_int,
        );
    }
    x = 0 as libc::c_int;
    while x < voicescount {
        if (*opl).voices2notes[x as usize].priority as libc::c_int > 0 as libc::c_int {
            (*opl)
                .voices2notes[x as usize]
                .priority = ((*opl).voices2notes[x as usize].priority as libc::c_int
                - 1 as libc::c_int) as libc::c_ushort;
        }
        x += 1;
        x;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_noteon(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut note: libc::c_int,
    mut velocity: libc::c_int,
) {
    opl_midi_noteon_op2(opl, channel, note, velocity, 1 as libc::c_int);
    opl_midi_noteon_op2(opl, channel, note, velocity, 0 as libc::c_int);
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_noteoff_op2(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut note: libc::c_int,
    mut vindex: libc::c_int,
) {
    let mut voice: libc::c_int = (*opl)
        .notes2voices[channel as usize][note as usize][vindex as usize] as libc::c_int;
    if voice >= 0 as libc::c_int {
        opl_noteoff(opl, voice as libc::c_ushort);
        (*opl)
            .voices2notes[voice as usize]
            .channel = -(1 as libc::c_int) as libc::c_schar;
        (*opl).voices2notes[voice as usize].note = -(1 as libc::c_int) as libc::c_schar;
        (*opl)
            .voices2notes[voice as usize]
            .priority = -(1 as libc::c_int) as libc::c_ushort;
        (*opl)
            .voices2notes[voice as usize]
            .voiceindex = 0xff as libc::c_int as libc::c_uchar;
        (*opl)
            .notes2voices[channel
            as usize][note
            as usize][vindex as usize] = -(1 as libc::c_int) as libc::c_schar;
    }
}
#[no_mangle]
pub unsafe extern "C" fn opl_midi_noteoff(
    mut opl: *mut opl_t,
    mut channel: libc::c_int,
    mut note: libc::c_int,
) {
    opl_midi_noteoff_op2(opl, channel, note, 0 as libc::c_int);
    opl_midi_noteoff_op2(opl, channel, note, 1 as libc::c_int);
}
unsafe extern "C" fn opl_loadbank_internal(
    mut opl: *mut opl_t,
    mut file: *const libc::c_char,
    mut offset: libc::c_int,
) -> libc::c_int {
    (*opl).is_op2 = 0 as libc::c_int;
    let mut buff: [libc::c_uchar; 16] = [0; 16];
    let mut i: libc::c_int = 0;
    let mut f: *mut FILE = fopen(file, b"rb\0" as *const u8 as *const libc::c_char);
    if f.is_null() {std::intrinsics::assume((f).addr() == 0);
        return -(1 as libc::c_int);
    }
    fseek(f, 0 as libc::c_int as libc::c_long, 2 as libc::c_int);
    if ftell(f) != 3204 as libc::c_int as libc::c_long {
        fclose(f);
        return -(2 as libc::c_int);
    }
    fseek(f, 0 as libc::c_int as libc::c_long, 0 as libc::c_int);
    if fread(
        buff.as_mut_ptr() as *mut libc::c_void,
        1 as libc::c_int as libc::c_ulong,
        4 as libc::c_int as libc::c_ulong,
        f,
    ) != 4 as libc::c_int as libc::c_ulong
        || buff[0 as libc::c_int as usize] as libc::c_int != 'I' as i32
        || buff[1 as libc::c_int as usize] as libc::c_int != 'B' as i32
        || buff[2 as libc::c_int as usize] as libc::c_int != 'K' as i32
        || buff[3 as libc::c_int as usize] as libc::c_int != 0x1a as libc::c_int
    {
        fclose(f);
        return -(3 as libc::c_int);
    }
    i = offset;
    while i < 128 as libc::c_int + offset {
        if fread(
            buff.as_mut_ptr() as *mut libc::c_void,
            1 as libc::c_int as libc::c_ulong,
            16 as libc::c_int as libc::c_ulong,
            f,
        ) != 16 as libc::c_int as libc::c_ulong
        {
            fclose(f);
            return -(4 as libc::c_int);
        }
        (*opl)
            .opl_gmtimbres[i as usize]
            .modulator_E862 = buff[8 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].modulator_E862 <<= 8 as libc::c_int;
        (*opl).opl_gmtimbres[i as usize].modulator_E862
            |= buff[6 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].modulator_E862 <<= 8 as libc::c_int;
        (*opl).opl_gmtimbres[i as usize].modulator_E862
            |= buff[4 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].modulator_E862 <<= 8 as libc::c_int;
        (*opl).opl_gmtimbres[i as usize].modulator_E862
            |= buff[0 as libc::c_int as usize] as libc::c_ulong;
        (*opl)
            .opl_gmtimbres[i as usize]
            .carrier_E862 = buff[9 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].carrier_E862 <<= 8 as libc::c_int;
        (*opl).opl_gmtimbres[i as usize].carrier_E862
            |= buff[7 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].carrier_E862 <<= 8 as libc::c_int;
        (*opl).opl_gmtimbres[i as usize].carrier_E862
            |= buff[5 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].carrier_E862 <<= 8 as libc::c_int;
        (*opl).opl_gmtimbres[i as usize].carrier_E862
            |= buff[1 as libc::c_int as usize] as libc::c_ulong;
        (*opl).opl_gmtimbres[i as usize].modulator_40 = buff[2 as libc::c_int as usize];
        (*opl).opl_gmtimbres[i as usize].carrier_40 = buff[3 as libc::c_int as usize];
        (*opl).opl_gmtimbres[i as usize].feedconn = buff[10 as libc::c_int as usize];
        (*opl)
            .opl_gmtimbres[i as usize]
            .finetune = buff[12 as libc::c_int as usize] as libc::c_schar;
        (*opl).opl_gmtimbres[i as usize].notenum = 60 as libc::c_int as libc::c_uchar;
        (*opl).opl_gmtimbres[i as usize].noteoffset = 0 as libc::c_int as libc::c_short;
        i += 1;
        i;
    }
    fclose(f);
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn opl_loadbank_ibk(
    mut opl: *mut opl_t,
    mut file: *const libc::c_char,
) -> libc::c_int {
    let mut instruments: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut percussion: *mut libc::c_char = 0 as *mut libc::c_char;
    let mut i: libc::c_int = 0;
    let mut res: libc::c_int = 0;
    instruments = strdup(file);
    if instruments.is_null() {std::intrinsics::assume((instruments).addr() == 0);
        return -(64 as libc::c_int);
    }
    i = 0 as libc::c_int;
    while *instruments.offset(i as isize) as libc::c_int != 0 as libc::c_int {
        if *instruments.offset(i as isize) as libc::c_int == ',' as i32 {
            *instruments.offset(i as isize) = 0 as libc::c_int as libc::c_char;
            percussion = instruments
                .offset(i as isize)
                .offset(1 as libc::c_int as isize);
            break;
        } else {
            i += 1;
            i;
        }
    }
    res = opl_loadbank_internal(opl, instruments, 0 as libc::c_int);
    if res == 0 as libc::c_int && !percussion.is_null() {
        res = opl_loadbank_internal(opl, percussion, 128 as libc::c_int);
    }
    free(instruments as *mut libc::c_void);
    return res;
}
unsafe extern "C" fn opl_load_op2_voice(
    mut timbre: *mut opl_timbre_t,
    mut buff: *const uint8_t,
) {
    (*timbre).modulator_E862 = *buff.offset(3 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).modulator_E862 <<= 8 as libc::c_int;
    (*timbre).modulator_E862 |= *buff.offset(2 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).modulator_E862 <<= 8 as libc::c_int;
    (*timbre).modulator_E862 |= *buff.offset(1 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).modulator_E862 <<= 8 as libc::c_int;
    (*timbre).modulator_E862 |= *buff.offset(0 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).carrier_E862 = *buff.offset(10 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).carrier_E862 <<= 8 as libc::c_int;
    (*timbre).carrier_E862 |= *buff.offset(9 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).carrier_E862 <<= 8 as libc::c_int;
    (*timbre).carrier_E862 |= *buff.offset(8 as libc::c_int as isize) as libc::c_ulong;
    (*timbre).carrier_E862 <<= 8 as libc::c_int;
    (*timbre).carrier_E862 |= *buff.offset(7 as libc::c_int as isize) as libc::c_ulong;
    (*timbre)
        .modulator_40 = (*buff.offset(5 as libc::c_int as isize) as libc::c_int
        & 0x3f as libc::c_int
        | *buff.offset(4 as libc::c_int as isize) as libc::c_int & 0xc0 as libc::c_int)
        as libc::c_uchar;
    (*timbre)
        .carrier_40 = (*buff.offset(12 as libc::c_int as isize) as libc::c_int
        & 0x3f as libc::c_int
        | *buff.offset(11 as libc::c_int as isize) as libc::c_int & 0xc0 as libc::c_int)
        as libc::c_uchar;
    (*timbre).feedconn = *buff.offset(6 as libc::c_int as isize);
    (*timbre).finetune = 0 as libc::c_int as libc::c_schar;
    (*timbre)
        .noteoffset = (*buff.offset(14 as libc::c_int as isize) as libc::c_int
        | (*buff.offset(15 as libc::c_int as isize) as uint16_t as libc::c_int)
            << 8 as libc::c_int) as int16_t;
}
#[no_mangle]
pub unsafe extern "C" fn opl_loadbank_op2(
    mut opl: *mut opl_t,
    mut data: *const libc::c_void,
    mut size: libc::c_int,
) -> libc::c_int {
    if size < 8 as libc::c_int + 36 as libc::c_int * 175 as libc::c_int {
        return -(3 as libc::c_int);
    }
    let mut buff: *const uint8_t = data as *const uint8_t;
    let mut i: libc::c_int = 0;
    if *buff.offset(0 as libc::c_int as isize) as libc::c_int != '#' as i32
        || *buff.offset(1 as libc::c_int as isize) as libc::c_int != 'O' as i32
        || *buff.offset(2 as libc::c_int as isize) as libc::c_int != 'P' as i32
        || *buff.offset(3 as libc::c_int as isize) as libc::c_int != 'L' as i32
        || *buff.offset(4 as libc::c_int as isize) as libc::c_int != '_' as i32
        || *buff.offset(5 as libc::c_int as isize) as libc::c_int != 'I' as i32
        || *buff.offset(6 as libc::c_int as isize) as libc::c_int != 'I' as i32
        || *buff.offset(7 as libc::c_int as isize) as libc::c_int != '#' as i32
    {
        return -(3 as libc::c_int);
    }
    buff = buff.offset(8 as libc::c_int as isize);
    (*opl).is_op2 = 1 as libc::c_int;
    i = 0 as libc::c_int;
    while i < 175 as libc::c_int {
        (*opl)
            .op2_flags[i
            as usize] = (*buff.offset(0 as libc::c_int as isize) as libc::c_int
            | (*buff.offset(1 as libc::c_int as isize) as uint16_t as libc::c_int)
                << 8 as libc::c_int) as op2_flags_t;
        let mut finetune: libc::c_int = *buff.offset(2 as libc::c_int as isize)
            as libc::c_int;
        let mut fixednote: uint8_t = *buff.offset(3 as libc::c_int as isize);
        buff = buff.offset(4 as libc::c_int as isize);
        opl_load_op2_voice(
            &raw mut *((*opl).opl_gmtimbres).as_mut_ptr().offset(i as isize),
            buff,
        );
        (*opl).opl_gmtimbres[i as usize].notenum = fixednote;
        buff = buff.offset(16 as libc::c_int as isize);
        opl_load_op2_voice(
            &raw mut *((*opl).opl_gmtimbres_voice2).as_mut_ptr().offset(i as isize),
            buff,
        );
        (*opl).opl_gmtimbres_voice2[i as usize].notenum = fixednote;
        (*opl)
            .opl_gmtimbres_voice2[i as usize]
            .finetune = ((*opl).opl_gmtimbres_voice2[i as usize].finetune as libc::c_int
            + (finetune - 128 as libc::c_int)) as libc::c_schar;
        buff = buff.offset(16 as libc::c_int as isize);
        i += 1;
        i;
    }
    return 0 as libc::c_int;
}
unsafe fn main_0() -> libc::c_int {
    opl_emu_bitfield(1 as libc::c_int as uint32_t, 2 as libc::c_int, 3 as libc::c_int);
    opl_emu_registers_effective_rate(
        1 as libc::c_int as uint32_t,
        2 as libc::c_int as uint32_t,
    );
    return 0 as libc::c_int;
}
pub fn main() {
    unsafe { ::std::process::exit(main_0() as i32) }
}
