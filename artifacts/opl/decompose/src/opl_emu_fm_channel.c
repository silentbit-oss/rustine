struct opl_emu_fm_channel
{
  uint32_t m_choffs;
  int16_t m_feedback[2];
  int16_t m_feedback_in;
  struct opl_emu_fm_operator *m_op[4];
  struct opl_emu_registers *m_regs;
}
/*** DEPENDENCIES:
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
***/


