struct opl_emu_registers
{
  uint16_t m_lfo_am_counter;
  uint16_t m_lfo_pm_counter;
  uint32_t m_noise_lfsr;
  uint8_t m_lfo_am;
  uint8_t m_regdata[0x200];
  uint16_t m_waveform[8][0x400];
}
/*** DEPENDENCIES:
***/


