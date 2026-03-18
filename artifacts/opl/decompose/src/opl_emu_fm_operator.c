struct opl_emu_fm_operator
{
  uint32_t m_choffs;
  uint32_t m_opoffs;
  uint32_t m_phase;
  uint16_t m_env_attenuation;
  enum opl_emu_envelope_state m_env_state;
  uint8_t m_key_state;
  uint8_t m_keyon_live;
  struct opl_emu_opdata_cache m_cache;
  struct opl_emu_registers *m_regs;
}
/*** DEPENDENCIES:
struct opl_emu_opdata_cache
{
  const uint16_t *waveform;
  uint32_t phase_step;
  uint32_t total_level;
  uint32_t block_freq;
  int32_t detune;
  uint32_t multiple;
  uint32_t eg_sustain;
  uint8_t eg_rate[OPL_EMU_EG_STATES];
  uint8_t eg_shift;
}
----------------------------
struct opl_emu_registers
{
  uint16_t m_lfo_am_counter;
  uint16_t m_lfo_pm_counter;
  uint32_t m_noise_lfsr;
  uint8_t m_lfo_am;
  uint8_t m_regdata[0x200];
  uint16_t m_waveform[8][0x400];
}
----------------------------
enum opl_emu_envelope_state
{
  OPL_EMU_EG_ATTACK = 1,
  OPL_EMU_EG_DECAY = 2,
  OPL_EMU_EG_SUSTAIN = 3,
  OPL_EMU_EG_RELEASE = 4,
  OPL_EMU_EG_STATES = 6
}
----------------------------
***/


