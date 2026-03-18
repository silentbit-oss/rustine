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
/*** DEPENDENCIES:
***/


