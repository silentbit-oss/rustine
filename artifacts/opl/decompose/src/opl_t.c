struct opl_t
{
  signed char notes2voices[16][128][2];
  unsigned short channelpitch[16];
  unsigned short channelvol[16];
  struct voicealloc_t voices2notes[18];
  unsigned char channelprog[16];
  int opl3;
  struct opl_emu_t opl_emu;
  struct opl_timbre_t opl_gmtimbres[256];
  struct opl_timbre_t opl_gmtimbres_voice2[256];
  int is_op2;
  enum op2_flags_t op2_flags[256];
}
/*** DEPENDENCIES:
typedef struct opl_timbre_t
{
  unsigned long modulator_E862;
  unsigned long carrier_E862;
  unsigned char modulator_40;
  unsigned char carrier_40;
  unsigned char feedconn;
  signed char finetune;
  unsigned char notenum;
  signed short noteoffset;
} opl_timbre_t
----------------------------
struct opl_emu_t
{
  uint32_t m_env_counter;
  uint8_t m_status;
  uint8_t m_timer_running[2];
  uint32_t m_active_channels;
  uint32_t m_modified_channels;
  uint32_t m_prepare_count;
  struct opl_emu_registers m_regs;
  struct opl_emu_fm_channel m_channel[18];
  struct opl_emu_fm_operator m_operator[18 * 2];
}
----------------------------
enum op2_flags_t
{
  OP2_FIXEDPITCH = 1,
  OP2_UNUSED = 2,
  OP2_DOUBLEVOICE = 4
}
----------------------------
struct voicealloc_t
{
  unsigned short priority;
  signed short timbreid;
  signed char channel;
  signed char note;
  unsigned char voiceindex;
}
----------------------------
***/


