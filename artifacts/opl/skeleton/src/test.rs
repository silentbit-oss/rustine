use crate::*;

pub fn opl_emu_bitfield(/* uint32_t value, int start, int length */) {
	todo!();
}
pub fn opl_emu_clamp(/* int32_t value, int32_t minval, int32_t maxval */) {
	todo!();
}
pub fn opl_emu_registers_operator_list(/* uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4 */) {
	todo!();
}
pub fn opl_emu_registers_effective_rate(/* uint32_t rawrate, uint32_t ksr */) {
	todo!();
}
pub fn opl_emu_registers_channel_offset(/* uint32_t chnum */) {
	todo!();
}
pub fn opl_emu_registers_operator_offset(/* uint32_t opnum */) {
	todo!();
}
pub fn opl_emu_opl_key_scale_atten(/* uint32_t block, uint32_t fnum_4msb */) {
	todo!();
}
pub fn opl_emu_attenuation_to_volume(/* uint32_t input */) {
	todo!();
}
pub fn calc_vol(/* unsigned char *regbyte, int volume */) {
	todo!();
}
pub fn test_min_max_macros() {
	todo!();
}
pub fn opl_midi_changeprog(/* opl_t *opl, int channel, int program */) {
	todo!();
}
pub fn opl_emu_registers_reset(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_reset_lfo(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_lfo_am_offset(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_registers_noise_state(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_fm_operator_reset(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_operator_opoffs(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_operator_choffs(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_operator_set_choffs(/* struct opl_emu_fm_operator *fmop, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_fm_operator_phase(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_operator_start_attack(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_operator_start_release(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_channel_reset(/* struct opl_emu_fm_channel *fmch */) {
	todo!();
}
pub fn opl_emu_fm_channel_choffs(/* struct opl_emu_fm_channel *fmch */) {
	todo!();
}
pub fn opl_emu_fm_channel_is4op(/* struct opl_emu_fm_channel *fmch */) {
	todo!();
}
pub fn opl_emu_abs_sin_attenuation(/* uint32_t input */) {
	todo!();
}
pub fn opl_emu_attenuation_increment(/* uint32_t rate, uint32_t index */) {
	todo!();
}
pub fn opl_emu_opl_clock_noise_and_lfo(/* uint32_t *noise_lfsr, uint16_t *lfo_am_counter, uint16_t *lfo_pm_counter, uint8_t *lfo_am, uint32_t am_depth, uint32_t pm_depth */) {
	todo!();
}
pub fn opl_emu_opl_compute_phase_step(/* uint32_t block_freq, uint32_t multiple, int32_t lfo_raw_pm */) {
	todo!();
}
pub fn getinstrument(/* opl_t *opl, int channel, int note */) {
	todo!();
}
pub fn test_clamp_function() {
	todo!();
}
pub fn helper_opl_loadbank_internal_1(/* int * const i_ref, opl_t * const opl, unsigned char buff[16], FILE * const f */) {
	todo!();
}
pub fn opl_emu_registers_write(/* struct opl_emu_registers *regs, uint16_t index, uint8_t data, uint32_t *channel, uint32_t *opmask */) {
	todo!();
}
pub fn opl_emu_fm_operator_keyonoff(/* struct opl_emu_fm_operator *fmop, uint32_t on, enum opl_emu_keyon_type type */) {
	todo!();
}
pub fn opl_emu_fm_channel_keyonoff(/* struct opl_emu_fm_channel *fmch, uint32_t states, enum opl_emu_keyon_type type, uint32_t chnum */) {
	todo!();
}
pub fn opl_emu_write(/* struct opl_emu_t *emu, uint16_t regnum, uint8_t data */) {
	todo!();
}
pub fn oplregwr(/* opl_t *opl, uint16_t reg, uint8_t data */) {
	todo!();
}
pub fn voicevolume(/* opl_t *opl, unsigned short voice, const opl_timbre_t *timbre, int volume */) {
	todo!();
}
pub fn opl_noteon(/* opl_t *opl, unsigned short voice, unsigned int note, int pitch */) {
	todo!();
}
pub fn opl_loadinstrument(/* opl_t *opl, int voice, opl_timbre_t *timbre */) {
	todo!();
}
pub fn opl_noteoff(/* opl_t *opl, unsigned short voice */) {
	todo!();
}
pub fn opl_midi_noteoff_op2(/* opl_t *opl, int channel, int note, int vindex */) {
	todo!();
}
pub fn helper_opl_midi_noteon_op2_1(/* int * const x_ref, int * const voice_ref, int * const lowestpriority_ref, int * const highestvoiceindex_ref, int * const lowestpriorityvoice_ref, opl_t * const opl, int vindex, int instrument */) {
	todo!();
}
pub fn opl_midi_noteon_op2(/* opl_t *opl, int channel, int note, int velocity, int vindex */) {
	todo!();
}
pub fn opl_midi_noteon(/* opl_t *opl, int channel, int note, int velocity */) {
	todo!();
}
pub fn opl_midi_noteoff(/* opl_t *opl, int channel, int note */) {
	todo!();
}
pub fn opl_loadbank_internal(/* opl_t *opl, const char *file, int offset */) {
	todo!();
}
pub fn opl_loadbank_ibk(/* opl_t *opl, const char *file */) {
	todo!();
}
pub fn opl_load_op2_voice(/* opl_timbre_t *timbre, const uint8_t *buff */) {
	todo!();
}
pub fn opl_loadbank_op2(/* opl_t *opl, const void *data, int size */) {
	todo!();
}
pub fn opl_emu_registers_byte(/* struct opl_emu_registers *regs, uint32_t offset, uint32_t start, uint32_t count, uint32_t extra_offset */) {
	todo!();
}
pub fn opl_emu_registers_rhythm_enable(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_op_lfo_am_enable(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_fm_operator_envelope_attenuation(/* struct opl_emu_fm_operator *fmop, uint32_t am_offset */) {
	todo!();
}
pub fn opl_emu_fm_operator_compute_volume(/* struct opl_emu_fm_operator *fmop, uint32_t phase, uint32_t am_offset */) {
	todo!();
}
pub fn opl_emu_registers_newflag(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_ch_output_1(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_registers_ch_output_0(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_fm_channel_add_to_output(/* struct opl_emu_fm_channel *fmch, uint32_t choffs, short *output, int32_t value */) {
	todo!();
}
pub fn opl_emu_fm_channel_output_rhythm_ch8(/* struct opl_emu_fm_channel *fmch, uint32_t phase_select, short *output, uint32_t rshift, int32_t clipmax */) {
	todo!();
}
pub fn opl_emu_fm_channel_output_rhythm_ch7(/* struct opl_emu_fm_channel *fmch, uint32_t phase_select, short *output, uint32_t rshift, int32_t clipmax */) {
	todo!();
}
pub fn opl_emu_registers_ch_feedback(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_registers_ch_algorithm(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_fm_channel_output_rhythm_ch6(/* struct opl_emu_fm_channel *fmch, short *output, uint32_t rshift, int32_t clipmax */) {
	todo!();
}
pub fn opl_emu_registers_ch_output_any(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_fm_channel_output_4op(/* struct opl_emu_fm_channel *fmch, short *output, uint32_t rshift, int32_t clipmax */) {
	todo!();
}
pub fn opl_emu_fm_channel_output_2op(/* struct opl_emu_fm_channel *fmch, short *output, uint32_t rshift, int32_t clipmax */) {
	todo!();
}
pub fn opl_emu_out(/* struct opl_emu_t *emu, short *output, uint32_t rshift, int32_t clipmax, uint32_t chanmask */) {
	todo!();
}
pub fn opl_emu_registers_lfo_pm_depth(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_lfo_am_depth(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_clock_noise_and_lfo(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_op_waveform(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_total_level(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_sustain_level(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_release_rate(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_multiple(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_ksr(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_ksl(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_eg_sustain(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_decay_rate(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_op_attack_rate(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_note_select(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_word(/* struct opl_emu_registers *regs, uint32_t offset1, uint32_t start1, uint32_t count1, uint32_t offset2, uint32_t start2, uint32_t count2, uint32_t extra_offset */) {
	todo!();
}
pub fn opl_emu_registers_ch_block_freq(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_registers_op_lfo_pm_enable(/* struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_registers_compute_phase_step(/* struct opl_emu_registers *regs, uint32_t choffs, uint32_t opoffs, const struct opl_emu_opdata_cache *cache, int32_t lfo_raw_pm */) {
	todo!();
}
pub fn opl_emu_registers_cache_operator_data(/* struct opl_emu_registers *regs, uint32_t choffs, uint32_t opoffs, struct opl_emu_opdata_cache *cache */) {
	todo!();
}
pub fn opl_emu_fm_operator_clock_keystate(/* struct opl_emu_fm_operator *fmop, uint32_t keystate */) {
	todo!();
}
pub fn opl_emu_fm_operator_prepare(/* struct opl_emu_fm_operator *fmop */) {
	todo!();
}
pub fn opl_emu_fm_channel_prepare(/* struct opl_emu_fm_channel *fmch */) {
	todo!();
}
pub fn opl_emu_fm_operator_clock_phase(/* struct opl_emu_fm_operator *fmop, int32_t lfo_raw_pm */) {
	todo!();
}
pub fn opl_emu_fm_operator_clock_envelope(/* struct opl_emu_fm_operator *fmop, uint32_t env_counter */) {
	todo!();
}
pub fn opl_emu_fm_operator_clock(/* struct opl_emu_fm_operator *fmop, uint32_t env_counter, int32_t lfo_raw_pm */) {
	todo!();
}
pub fn opl_emu_fm_channel_clock(/* struct opl_emu_fm_channel *fmch, uint32_t env_counter, int32_t lfo_raw_pm */) {
	todo!();
}
pub fn opl_emu_registers_fourop_enable(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_operator_map(/* struct opl_emu_registers *regs, struct opl_emu_registers_operator_mapping *dest */) {
	todo!();
}
pub fn opl_emu_fm_channel_assign(/* struct opl_emu_fm_channel *fmch, uint32_t index, struct opl_emu_fm_operator *op */) {
	todo!();
}
pub fn opl_emu_assign_operators(/* struct opl_emu_t *emu */) {
	todo!();
}
pub fn opl_emu_clock(/* struct opl_emu_t *emu, uint32_t chanmask */) {
	todo!();
}
pub fn opl_emu_generate(/* struct opl_emu_t *emu, short *output, uint32_t numsamples, float volume */) {
	todo!();
}
pub fn opl_render(/* opl_t *opl, short *sample_pairs, int sample_pairs_count, float volume */) {
	todo!();
}
pub fn opl_emu_registers_timer_a_value(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_timer_b_value(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_status_mask(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_is_rhythm(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_fm_operator_init(/* struct opl_emu_fm_operator *fmop, struct opl_emu_registers *regs, uint32_t opoffs */) {
	todo!();
}
pub fn opl_emu_fm_channel_init(/* struct opl_emu_fm_channel *fmch, struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_set_reset_status(/* struct opl_emu_t *emu, uint8_t set, uint8_t reset */) {
	todo!();
}
pub fn opl_midi_controller(/* opl_t *opl, int channel, int id, int value */) {
	todo!();
}
pub fn opl_emu_registers_init(/* struct opl_emu_registers *regs */) {
	todo!();
}
pub fn opl_emu_registers_ch_output_2(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_registers_ch_output_3(/* struct opl_emu_registers *regs, uint32_t choffs */) {
	todo!();
}
pub fn opl_emu_update_timer(/* struct opl_emu_t *emu, uint32_t tnum, uint32_t enable */) {
	todo!();
}
pub fn opl_clear(/* opl_t *opl */) {
	todo!();
}
pub fn opl_destroy(/* opl_t *opl */) {
	todo!();
}
pub fn opl_emu_init(/* struct opl_emu_t *emu */) {
	todo!();
}
pub fn opl_create(/* void */) {
	todo!();
}
pub fn test_create_destroy() {
	todo!();
}
pub fn test_multiple_create_destroy() {
	todo!();
}
pub fn opl_midi_pitchwheel(/* opl_t *opl, int channel, int pitchwheel */) {
	todo!();
}
pub fn opl_write(/* opl_t *opl, int count, unsigned short *regs, unsigned char *data */) {
	todo!();
}
pub fn test_register_write_normal() {
	todo!();
}
pub fn test_register_write_edge() {
	todo!();
}
pub fn test_register_write_illegal() {
	todo!();
}
pub fn test_pitch_wheel_bounds() {
	todo!();
}
pub fn test_audio_generation_stress() {
	todo!();
}
pub fn opl_emu_reset(/* struct opl_emu_t *emu */) {
	todo!();
}
pub fn test_midi_functions() {
	todo!();
}
pub fn test_instrument_and_complex_midi() {
	todo!();
}
