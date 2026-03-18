# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/main.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/main.c"

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h" 1
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
typedef struct opl_timbre_t {
  unsigned long modulator_E862, carrier_E862;
  unsigned char modulator_40, carrier_40;
  unsigned char feedconn;
  signed char finetune;
  unsigned char notenum;
  signed short noteoffset;
} opl_timbre_t;

typedef struct opl_t opl_t;



opl_t* opl_create( void );


void opl_destroy( opl_t* opl );


void opl_clear( opl_t* opl );


void opl_midi_noteon( opl_t* opl, int channel, int note, int velocity );


void opl_midi_noteoff( opl_t* opl, int channel, int note );


void opl_midi_pitchwheel( opl_t* opl, int channel, int wheelvalue );


void opl_midi_controller( opl_t* opl, int channel, int id, int value );


void opl_midi_changeprog( opl_t* opl, int channel, int program );

void opl_loadinstrument(opl_t* opl, int voice, opl_timbre_t* timbre );



int opl_loadbank_ibk( opl_t* opl, char const* file );

int opl_loadbank_op2(opl_t* opl, void const* data, int size );

void opl_render( opl_t* opl, short* sample_pairs, int sample_pairs_count, float volume );

void opl_write( opl_t* opl, int count, unsigned short* regs, unsigned char* data );







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 2
# 92 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 93 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 94 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 95 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h" 2
# 103 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
uint32_t opl_emu_bitfield(uint32_t value, int start, int length )
{
 return (value >> start) & ((1 << length) - 1);
}







int32_t opl_emu_clamp(int32_t value, int32_t minval, int32_t maxval)
{
 if (value < minval)
  return minval;
 if (value > maxval)
  return maxval;
 return value;
}






enum opl_emu_envelope_state
{
 OPL_EMU_EG_ATTACK = 1,
 OPL_EMU_EG_DECAY = 2,
 OPL_EMU_EG_SUSTAIN = 3,
 OPL_EMU_EG_RELEASE = 4,
 OPL_EMU_EG_STATES = 6
};




enum opl_emu_keyon_type
{
 OPL_EMU_KEYON_NORMAL = 0,
 OPL_EMU_KEYON_RHYTHM = 1,
 OPL_EMU_KEYON_CSM = 2
};
# 154 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
struct opl_emu_opdata_cache
{



 uint16_t const *waveform;
 uint32_t phase_step;
 uint32_t total_level;
 uint32_t block_freq;
 int32_t detune;
 uint32_t multiple;
 uint32_t eg_sustain;
 uint8_t eg_rate[OPL_EMU_EG_STATES];
 uint8_t eg_shift;
};
# 253 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
struct opl_emu_registers
{

 uint16_t m_lfo_am_counter;
 uint16_t m_lfo_pm_counter;
 uint32_t m_noise_lfsr;
 uint8_t m_lfo_am;
 uint8_t m_regdata[0x200];
 uint16_t m_waveform[8][0x400];
};




uint32_t opl_emu_registers_operator_list(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4)
{
 return o1 | (o2 << 8) | (o3 << 16) | (o4 << 24);
}



uint32_t opl_emu_registers_effective_rate(uint32_t rawrate, uint32_t ksr)
{
 return (rawrate == 0) ? 0 : (((rawrate + ksr)<(63))?(rawrate + ksr):(63));
}



void opl_emu_registers_init( struct opl_emu_registers* regs );


void opl_emu_registers_reset(struct opl_emu_registers* regs);


uint32_t opl_emu_registers_channel_offset(uint32_t chnum)
{
    return (chnum % 9) + 0x100 * (chnum / 9);
}


uint32_t opl_emu_registers_operator_offset(uint32_t opnum)
{
    return (opnum % 18) + 2 * ((opnum % 18) / 6) + 0x100 * (opnum / 18);
}


struct opl_emu_registers_operator_mapping { uint32_t chan[18]; };
void opl_emu_registers_operator_map(struct opl_emu_registers* regs,struct opl_emu_registers_operator_mapping* dest) ;


int opl_emu_registers_write(struct opl_emu_registers* regs,uint16_t index, uint8_t data, uint32_t* chan, uint32_t* opmask);


int32_t opl_emu_registers_clock_noise_and_lfo(struct opl_emu_registers* regs);


void opl_emu_registers_reset_lfo(struct opl_emu_registers* regs) { regs->m_lfo_am_counter = regs->m_lfo_pm_counter = 0; }



uint32_t opl_emu_registers_lfo_am_offset(struct opl_emu_registers* regs,uint32_t choffs) { return regs->m_lfo_am; }


uint32_t opl_emu_registers_noise_state(struct opl_emu_registers* regs) { return regs->m_noise_lfsr >> 23; }


void opl_emu_registers_cache_operator_data(struct opl_emu_registers* regs,uint32_t choffs, uint32_t opoffs, struct opl_emu_opdata_cache *cache);


uint32_t opl_emu_registers_compute_phase_step(struct opl_emu_registers* regs,uint32_t choffs, uint32_t opoffs, struct opl_emu_opdata_cache const *cache, int32_t lfo_raw_pm);


uint32_t opl_emu_registers_byte(struct opl_emu_registers* regs,uint32_t offset, uint32_t start, uint32_t count, uint32_t extra_offset )
{
 return opl_emu_bitfield(regs->m_regdata[offset + extra_offset], start, count);
}


uint32_t opl_emu_registers_word(struct opl_emu_registers* regs,uint32_t offset1, uint32_t start1, uint32_t count1, uint32_t offset2, uint32_t start2, uint32_t count2, uint32_t extra_offset )
{
 return (opl_emu_registers_byte(regs,offset1, start1, count1, extra_offset) << count2) | opl_emu_registers_byte(regs,offset2, start2, count2, extra_offset);
}




uint32_t opl_emu_registers_timer_a_value(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0x02, 0, 8, 0) * 4; }
uint32_t opl_emu_registers_timer_b_value(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0x03, 0, 8, 0); }
uint32_t opl_emu_registers_status_mask(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0x04, 0, 8, 0) & 0x78; }
uint32_t opl_emu_registers_note_select(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0x08, 6, 1, 0); }
uint32_t opl_emu_registers_lfo_am_depth(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0xbd, 7, 1, 0); }
uint32_t opl_emu_registers_lfo_pm_depth(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0xbd, 6, 1, 0); }
uint32_t opl_emu_registers_rhythm_enable(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0xbd, 5, 1, 0); }
uint32_t opl_emu_registers_newflag(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0x105, 0, 1, 0); }
uint32_t opl_emu_registers_fourop_enable(struct opl_emu_registers* regs) { return opl_emu_registers_byte(regs,0x104, 0, 6, 0); }


uint32_t opl_emu_registers_ch_block_freq(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_word(regs,0xb0, 0, 5, 0xa0, 0, 8, choffs); }
uint32_t opl_emu_registers_ch_feedback(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_byte(regs,0xc0, 1, 3, choffs); }
uint32_t opl_emu_registers_ch_algorithm(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_byte(regs,0xc0, 0, 1, choffs) | ((8 | (opl_emu_registers_byte(regs,0xc3, 0, 1, choffs) << 1))); }
uint32_t opl_emu_registers_ch_output_any(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_newflag(regs) ? opl_emu_registers_byte(regs,0xc0 + choffs, 4, 4, 0) : 1; }
uint32_t opl_emu_registers_ch_output_0(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_newflag(regs) ? opl_emu_registers_byte(regs,0xc0 + choffs, 4, 1, 0) : 1; }
uint32_t opl_emu_registers_ch_output_1(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_newflag(regs) ? opl_emu_registers_byte(regs,0xc0 + choffs, 5, 1, 0) : 1; }
uint32_t opl_emu_registers_ch_output_2(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_newflag(regs) ? opl_emu_registers_byte(regs,0xc0 + choffs, 6, 1, 0) : 0; }
uint32_t opl_emu_registers_ch_output_3(struct opl_emu_registers* regs,uint32_t choffs) { return opl_emu_registers_newflag(regs) ? opl_emu_registers_byte(regs,0xc0 + choffs, 7, 1, 0) : 0; }


uint32_t opl_emu_registers_op_lfo_am_enable(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x20, 7, 1, opoffs); }
uint32_t opl_emu_registers_op_lfo_pm_enable(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x20, 6, 1, opoffs); }
uint32_t opl_emu_registers_op_eg_sustain(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x20, 5, 1, opoffs); }
uint32_t opl_emu_registers_op_ksr(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x20, 4, 1, opoffs); }
uint32_t opl_emu_registers_op_multiple(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x20, 0, 4, opoffs); }
uint32_t opl_emu_registers_op_ksl(struct opl_emu_registers* regs,uint32_t opoffs) { uint32_t temp = opl_emu_registers_byte(regs,0x40, 6, 2, opoffs); return opl_emu_bitfield(temp, 1,1) | (opl_emu_bitfield(temp, 0,1) << 1); }
uint32_t opl_emu_registers_op_total_level(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x40, 0, 6, opoffs); }
uint32_t opl_emu_registers_op_attack_rate(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x60, 4, 4, opoffs); }
uint32_t opl_emu_registers_op_decay_rate(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x60, 0, 4, opoffs); }
uint32_t opl_emu_registers_op_sustain_level(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x80, 4, 4, opoffs); }
uint32_t opl_emu_registers_op_release_rate(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0x80, 0, 4, opoffs); }
uint32_t opl_emu_registers_op_waveform(struct opl_emu_registers* regs,uint32_t opoffs) { return opl_emu_registers_byte(regs,0xe0, 0, opl_emu_registers_newflag(regs) ? 3 : 2, opoffs); }



int opl_emu_registers_is_rhythm(struct opl_emu_registers* regs,uint32_t choffs)
{
 return opl_emu_registers_rhythm_enable(regs) && (choffs >= 6 && choffs <= 8);
}
# 387 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
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
 struct opl_emu_registers* m_regs;
};

void opl_emu_fm_operator_init(struct opl_emu_fm_operator* fmop, struct opl_emu_registers* regs, uint32_t opoffs);


void opl_emu_fm_operator_reset(struct opl_emu_fm_operator* fmop);


uint32_t opl_emu_fm_operator_opoffs(struct opl_emu_fm_operator* fmop) { return fmop->m_opoffs; }
uint32_t opl_emu_fm_operator_choffs(struct opl_emu_fm_operator* fmop) { return fmop->m_choffs; }


void opl_emu_fm_operator_set_choffs(struct opl_emu_fm_operator* fmop,uint32_t choffs) { fmop->m_choffs = choffs; }


int opl_emu_fm_operator_prepare(struct opl_emu_fm_operator* fmop);


void opl_emu_fm_operator_clock(struct opl_emu_fm_operator* fmop,uint32_t env_counter, int32_t lfo_raw_pm);


uint32_t opl_emu_fm_operator_phase(struct opl_emu_fm_operator* fmop) { return fmop->m_phase >> 10; }


int32_t opl_emu_fm_operator_compute_volume(struct opl_emu_fm_operator* fmop,uint32_t phase, uint32_t am_offset) ;


void opl_emu_fm_operator_keyonoff(struct opl_emu_fm_operator* fmop,uint32_t on, enum opl_emu_keyon_type type);


void opl_emu_fm_operator_start_attack(struct opl_emu_fm_operator* fmop);


void opl_emu_fm_operator_start_release(struct opl_emu_fm_operator* fmop);


void opl_emu_fm_operator_clock_keystate(struct opl_emu_fm_operator* fmop,uint32_t keystate);
void opl_emu_fm_operator_clock_envelope(struct opl_emu_fm_operator* fmop,uint32_t env_counter);
void opl_emu_fm_operator_clock_phase(struct opl_emu_fm_operator* fmop,int32_t lfo_raw_pm);


uint32_t opl_emu_fm_operator_envelope_attenuation(struct opl_emu_fm_operator* fmop,uint32_t am_offset) ;







struct opl_emu_fm_channel
{

 uint32_t m_choffs;
 int16_t m_feedback[2];
 int16_t m_feedback_in;
 struct opl_emu_fm_operator *m_op[4];
 struct opl_emu_registers* m_regs;
};


void opl_emu_fm_channel_init(struct opl_emu_fm_channel* fmch,struct opl_emu_registers* regs, uint32_t choffs);


void opl_emu_fm_channel_reset(struct opl_emu_fm_channel* fmch);


uint32_t opl_emu_fm_channel_choffs(struct opl_emu_fm_channel* fmch) { return fmch->m_choffs; }


void opl_emu_fm_channel_assign(struct opl_emu_fm_channel* fmch,uint32_t index, struct opl_emu_fm_operator *op)
{
 fmch->m_op[index] = op;
 if (op != 0)
  opl_emu_fm_operator_set_choffs(op, fmch->m_choffs);
}


void opl_emu_fm_channel_keyonoff(struct opl_emu_fm_channel* fmch,uint32_t states, enum opl_emu_keyon_type type, uint32_t chnum);


int opl_emu_fm_channel_prepare(struct opl_emu_fm_channel* fmch);


void opl_emu_fm_channel_clock(struct opl_emu_fm_channel* fmch,uint32_t env_counter, int32_t lfo_raw_pm);


void opl_emu_fm_channel_output_2op(struct opl_emu_fm_channel* fmch,short *output, uint32_t rshift, int32_t clipmax);
void opl_emu_fm_channel_output_4op(struct opl_emu_fm_channel* fmch,short *output, uint32_t rshift, int32_t clipmax);


void opl_emu_fm_channel_output_rhythm_ch6(struct opl_emu_fm_channel* fmch,short *output, uint32_t rshift, int32_t clipmax);
void opl_emu_fm_channel_output_rhythm_ch7(struct opl_emu_fm_channel* fmch,uint32_t phase_select,short *output, uint32_t rshift, int32_t clipmax);
void opl_emu_fm_channel_output_rhythm_ch8(struct opl_emu_fm_channel* fmch,uint32_t phase_select,short *output, uint32_t rshift, int32_t clipmax);


int opl_emu_fm_channel_is4op( struct opl_emu_fm_channel* fmch )
{
    return (fmch->m_op[2] != 0);
}


void opl_emu_fm_channel_add_to_output(struct opl_emu_fm_channel* fmch,uint32_t choffs,short* output, int32_t value)
{


 int out0_index = 0;
 int out1_index = 1 % 2;
 int out2_index = 2 % 2;
 int out3_index = 3 % 2;

 if (2 == 1 || opl_emu_registers_ch_output_0(fmch->m_regs, choffs)) {
        int s = output[out0_index] + value;
  output[out0_index] = s < -32767 ? -32767 : s > 32767 ? 32767 : s;
    }
 if (2 >= 2 && opl_emu_registers_ch_output_1(fmch->m_regs, choffs)) {
        int s = output[out1_index] + value;
  output[out1_index] = s < -32767 ? -32767 : s > 32767 ? 32767 : s;
    }




}
# 531 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
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
 struct opl_emu_fm_operator m_operator[( 18 * 2 )];
};
# 552 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
uint8_t opl_emu_set_reset_status(struct opl_emu_t* emu, uint8_t set, uint8_t reset)
{
 emu->m_status = (emu->m_status | set) & ~(reset | 0);

 return emu->m_status & ~opl_emu_registers_status_mask(&emu->m_regs);
}

void opl_emu_assign_operators( struct opl_emu_t* emu );
void opl_emu_write( struct opl_emu_t* emu, uint16_t regnum, uint8_t data);





void opl_emu_init( struct opl_emu_t* emu )
{
 emu->m_env_counter = 0;
 emu->m_status = 0;
 emu->m_timer_running[ 0 ] = 0;
 emu->m_timer_running[ 1 ] = 0;
 emu->m_active_channels = ( (1 << 18) - 1 );
 emu->m_modified_channels = ( (1 << 18) - 1 );
 emu->m_prepare_count = 0;

 opl_emu_registers_init( &emu->m_regs );


 for (uint32_t chnum = 0; chnum < 18; chnum++)
  opl_emu_fm_channel_init(&emu->m_channel[chnum], &emu->m_regs, opl_emu_registers_channel_offset(chnum));


 for (uint32_t opnum = 0; opnum < ( 18 * 2 ); opnum++)
  opl_emu_fm_operator_init(&emu->m_operator[opnum],&emu->m_regs, opl_emu_registers_operator_offset(opnum));


 opl_emu_assign_operators( emu );
}






void opl_emu_reset( struct opl_emu_t* emu)
{

 opl_emu_set_reset_status(emu, 0, 0xff);


 opl_emu_registers_reset( &emu->m_regs );


 opl_emu_write(emu, 0x04, 0);


 for (int i = 0; i < sizeof( emu->m_channel ) / sizeof( *emu->m_channel ); ++i )
  opl_emu_fm_channel_reset(&emu->m_channel[ i ]);


 for (int i = 0; i < sizeof( emu->m_operator ) / sizeof( *emu->m_operator ); ++i )
  opl_emu_fm_operator_reset(&emu->m_operator[ i ]);
}







uint32_t opl_emu_clock( struct opl_emu_t* emu,uint32_t chanmask)
{


 if (emu->m_modified_channels != 0 || emu->m_prepare_count++ >= 4096)
 {

        opl_emu_assign_operators(emu);


  emu->m_active_channels = 0;
  for (uint32_t chnum = 0; chnum < 18; chnum++)
   if (opl_emu_bitfield(chanmask, chnum,1))
    if (opl_emu_fm_channel_prepare(&emu->m_channel[chnum]))
     emu->m_active_channels |= 1 << chnum;


  emu->m_modified_channels = emu->m_prepare_count = 0;
 }


    emu->m_env_counter += 4;


 int32_t lfo_raw_pm = opl_emu_registers_clock_noise_and_lfo(&emu->m_regs);


 for (uint32_t chnum = 0; chnum < 18; chnum++)
  if (opl_emu_bitfield(chanmask, chnum, 1))
   opl_emu_fm_channel_clock(&emu->m_channel[chnum], emu->m_env_counter, lfo_raw_pm);



 return emu->m_env_counter;
}







void opl_emu_out( struct opl_emu_t* emu, short* output, uint32_t rshift, int32_t clipmax, uint32_t chanmask)
{

 chanmask &= emu->m_active_channels;



 if (opl_emu_registers_rhythm_enable(&emu->m_regs))
 {

  uint32_t op13phase = opl_emu_fm_operator_phase(&emu->m_operator[13]);
  uint32_t op17phase = opl_emu_fm_operator_phase(&emu->m_operator[17]);
  uint32_t phase_select = (opl_emu_bitfield(op13phase, 2, 1) ^ opl_emu_bitfield(op13phase, 7, 1)) | opl_emu_bitfield(op13phase, 3,1) | (opl_emu_bitfield(op17phase, 5,1) ^ opl_emu_bitfield(op17phase, 3,1));


  for (uint32_t chnum = 0; chnum < 18; chnum++)
   if (opl_emu_bitfield(chanmask, chnum,1))
   {
    if (chnum == 6)
     opl_emu_fm_channel_output_rhythm_ch6(&emu->m_channel[chnum],output, rshift, clipmax);
    else if (chnum == 7)
     opl_emu_fm_channel_output_rhythm_ch7(&emu->m_channel[chnum],phase_select, output, rshift, clipmax);
    else if (chnum == 8)
     opl_emu_fm_channel_output_rhythm_ch8(&emu->m_channel[chnum],phase_select, output, rshift, clipmax);
    else if (opl_emu_fm_channel_is4op(&emu->m_channel[chnum]))
     opl_emu_fm_channel_output_4op(&emu->m_channel[chnum],output, rshift, clipmax);
    else
     opl_emu_fm_channel_output_2op(&emu->m_channel[chnum],output, rshift, clipmax);
   }
 }
 else
 {

  for (uint32_t chnum = 0; chnum < 18; chnum++)
   if (opl_emu_bitfield(chanmask, chnum,1))
   {
    if (opl_emu_fm_channel_is4op(&emu->m_channel[chnum]))
     opl_emu_fm_channel_output_4op(&emu->m_channel[chnum],output, rshift, clipmax);
    else
     opl_emu_fm_channel_output_2op(&emu->m_channel[chnum],output, rshift, clipmax);
   }
 }
}






void opl_emu_write( struct opl_emu_t* emu, uint16_t regnum, uint8_t data)
{


 if (regnum == 0x04)
 {

  return;
 }


 emu->m_modified_channels = ( (1 << 18) - 1 );


 uint32_t keyon_channel;
 uint32_t keyon_opmask;
 if (opl_emu_registers_write(&emu->m_regs,regnum, data, &keyon_channel, &keyon_opmask))
 {

  if (keyon_channel < 18)
  {

   opl_emu_fm_channel_keyonoff(&emu->m_channel[keyon_channel],keyon_opmask, OPL_EMU_KEYON_NORMAL, keyon_channel);
  }
  else if (18 >= 9 && keyon_channel == 0xff)
  {

   opl_emu_fm_channel_keyonoff(&emu->m_channel[6],opl_emu_bitfield(keyon_opmask, 4,1) ? 3 : 0, OPL_EMU_KEYON_RHYTHM, 6);
   opl_emu_fm_channel_keyonoff(&emu->m_channel[7],opl_emu_bitfield(keyon_opmask, 0,1) | (opl_emu_bitfield(keyon_opmask, 3,1) << 1), OPL_EMU_KEYON_RHYTHM, 7);
   opl_emu_fm_channel_keyonoff(&emu->m_channel[8],opl_emu_bitfield(keyon_opmask, 2,1) | (opl_emu_bitfield(keyon_opmask, 1,1) << 1), OPL_EMU_KEYON_RHYTHM, 8);
  }
 }
}







void opl_emu_assign_operators( struct opl_emu_t* emu)
{
 struct opl_emu_registers_operator_mapping map;
 opl_emu_registers_operator_map(&emu->m_regs, &map);

 for (uint32_t chnum = 0; chnum < 18; chnum++)
  for (uint32_t index = 0; index < 4; index++)
  {
   uint32_t opnum = opl_emu_bitfield(map.chan[chnum], 8 * index, 8);
   opl_emu_fm_channel_assign(&emu->m_channel[chnum],index, (opnum == 0xff) ? 0 : &emu->m_operator[opnum]);
  }
}







void opl_emu_update_timer( struct opl_emu_t* emu, uint32_t tnum, uint32_t enable)
{

 if (enable && !emu->m_timer_running[tnum])
 {

  uint32_t period = (tnum == 0) ? (1024 - opl_emu_registers_timer_a_value(&emu->m_regs)) : 16 * (256 - opl_emu_registers_timer_b_value(&emu->m_regs));



  emu->m_timer_running[tnum] = 1;
 }


 else if (!enable)
 {

  emu->m_timer_running[tnum] = 0;
 }
}






void opl_emu_generate( struct opl_emu_t* emu,short *output, uint32_t numsamples, float volume )
{
 volume = volume > 1.0f ? 1.0f : volume < 0.0f ? 0.0f : volume;
 for (uint32_t samp = 0; samp < numsamples; samp++, output+=2)
 {

  opl_emu_clock(emu, ( (1 << 18) - 1 ));


  opl_emu_out(emu, output, 0, 32767, ( (1 << 18) - 1 ));

        *output = (short)((*output) * volume);
        *(output + 1) = (short)((*(output + 1)) * volume);
 }
}
# 823 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
uint32_t opl_emu_opl_key_scale_atten(uint32_t block, uint32_t fnum_4msb)
{



 static uint8_t const fnum_to_atten[16] = { 0,24,32,37,40,43,45,47,48,50,51,52,53,54,55,56 };
 int32_t result = fnum_to_atten[fnum_4msb] - 8 * (block ^ 7);
 return (((0)>(result))?(0):(result));
}
# 847 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
uint32_t opl_emu_abs_sin_attenuation(uint32_t input)
{


 static uint16_t const s_sin_table[256] =
 {
  0x859,0x6c3,0x607,0x58b,0x52e,0x4e4,0x4a6,0x471,0x443,0x41a,0x3f5,0x3d3,0x3b5,0x398,0x37e,0x365,
  0x34e,0x339,0x324,0x311,0x2ff,0x2ed,0x2dc,0x2cd,0x2bd,0x2af,0x2a0,0x293,0x286,0x279,0x26d,0x261,
  0x256,0x24b,0x240,0x236,0x22c,0x222,0x218,0x20f,0x206,0x1fd,0x1f5,0x1ec,0x1e4,0x1dc,0x1d4,0x1cd,
  0x1c5,0x1be,0x1b7,0x1b0,0x1a9,0x1a2,0x19b,0x195,0x18f,0x188,0x182,0x17c,0x177,0x171,0x16b,0x166,
  0x160,0x15b,0x155,0x150,0x14b,0x146,0x141,0x13c,0x137,0x133,0x12e,0x129,0x125,0x121,0x11c,0x118,
  0x114,0x10f,0x10b,0x107,0x103,0x0ff,0x0fb,0x0f8,0x0f4,0x0f0,0x0ec,0x0e9,0x0e5,0x0e2,0x0de,0x0db,
  0x0d7,0x0d4,0x0d1,0x0cd,0x0ca,0x0c7,0x0c4,0x0c1,0x0be,0x0bb,0x0b8,0x0b5,0x0b2,0x0af,0x0ac,0x0a9,
  0x0a7,0x0a4,0x0a1,0x09f,0x09c,0x099,0x097,0x094,0x092,0x08f,0x08d,0x08a,0x088,0x086,0x083,0x081,
  0x07f,0x07d,0x07a,0x078,0x076,0x074,0x072,0x070,0x06e,0x06c,0x06a,0x068,0x066,0x064,0x062,0x060,
  0x05e,0x05c,0x05b,0x059,0x057,0x055,0x053,0x052,0x050,0x04e,0x04d,0x04b,0x04a,0x048,0x046,0x045,
  0x043,0x042,0x040,0x03f,0x03e,0x03c,0x03b,0x039,0x038,0x037,0x035,0x034,0x033,0x031,0x030,0x02f,
  0x02e,0x02d,0x02b,0x02a,0x029,0x028,0x027,0x026,0x025,0x024,0x023,0x022,0x021,0x020,0x01f,0x01e,
  0x01d,0x01c,0x01b,0x01a,0x019,0x018,0x017,0x017,0x016,0x015,0x014,0x014,0x013,0x012,0x011,0x011,
  0x010,0x00f,0x00f,0x00e,0x00d,0x00d,0x00c,0x00c,0x00b,0x00a,0x00a,0x009,0x009,0x008,0x008,0x007,
  0x007,0x007,0x006,0x006,0x005,0x005,0x005,0x004,0x004,0x004,0x003,0x003,0x003,0x002,0x002,0x002,
  0x002,0x001,0x001,0x001,0x001,0x001,0x001,0x001,0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000
 };



 if (opl_emu_bitfield(input, 8,1))
  input = ~input;


 return s_sin_table[input & 0xff];
}
# 887 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
uint32_t opl_emu_attenuation_to_volume(uint32_t input)
{







 static uint16_t const s_power_table[256] =
 {
  (((0x3fa) | 0x400) << 2),(((0x3f5) | 0x400) << 2),(((0x3ef) | 0x400) << 2),(((0x3ea) | 0x400) << 2),(((0x3e4) | 0x400) << 2),(((0x3df) | 0x400) << 2),(((0x3da) | 0x400) << 2),(((0x3d4) | 0x400) << 2),
  (((0x3cf) | 0x400) << 2),(((0x3c9) | 0x400) << 2),(((0x3c4) | 0x400) << 2),(((0x3bf) | 0x400) << 2),(((0x3b9) | 0x400) << 2),(((0x3b4) | 0x400) << 2),(((0x3ae) | 0x400) << 2),(((0x3a9) | 0x400) << 2),
  (((0x3a4) | 0x400) << 2),(((0x39f) | 0x400) << 2),(((0x399) | 0x400) << 2),(((0x394) | 0x400) << 2),(((0x38f) | 0x400) << 2),(((0x38a) | 0x400) << 2),(((0x384) | 0x400) << 2),(((0x37f) | 0x400) << 2),
  (((0x37a) | 0x400) << 2),(((0x375) | 0x400) << 2),(((0x370) | 0x400) << 2),(((0x36a) | 0x400) << 2),(((0x365) | 0x400) << 2),(((0x360) | 0x400) << 2),(((0x35b) | 0x400) << 2),(((0x356) | 0x400) << 2),
  (((0x351) | 0x400) << 2),(((0x34c) | 0x400) << 2),(((0x347) | 0x400) << 2),(((0x342) | 0x400) << 2),(((0x33d) | 0x400) << 2),(((0x338) | 0x400) << 2),(((0x333) | 0x400) << 2),(((0x32e) | 0x400) << 2),
  (((0x329) | 0x400) << 2),(((0x324) | 0x400) << 2),(((0x31f) | 0x400) << 2),(((0x31a) | 0x400) << 2),(((0x315) | 0x400) << 2),(((0x310) | 0x400) << 2),(((0x30b) | 0x400) << 2),(((0x306) | 0x400) << 2),
  (((0x302) | 0x400) << 2),(((0x2fd) | 0x400) << 2),(((0x2f8) | 0x400) << 2),(((0x2f3) | 0x400) << 2),(((0x2ee) | 0x400) << 2),(((0x2e9) | 0x400) << 2),(((0x2e5) | 0x400) << 2),(((0x2e0) | 0x400) << 2),
  (((0x2db) | 0x400) << 2),(((0x2d6) | 0x400) << 2),(((0x2d2) | 0x400) << 2),(((0x2cd) | 0x400) << 2),(((0x2c8) | 0x400) << 2),(((0x2c4) | 0x400) << 2),(((0x2bf) | 0x400) << 2),(((0x2ba) | 0x400) << 2),
  (((0x2b5) | 0x400) << 2),(((0x2b1) | 0x400) << 2),(((0x2ac) | 0x400) << 2),(((0x2a8) | 0x400) << 2),(((0x2a3) | 0x400) << 2),(((0x29e) | 0x400) << 2),(((0x29a) | 0x400) << 2),(((0x295) | 0x400) << 2),
  (((0x291) | 0x400) << 2),(((0x28c) | 0x400) << 2),(((0x288) | 0x400) << 2),(((0x283) | 0x400) << 2),(((0x27f) | 0x400) << 2),(((0x27a) | 0x400) << 2),(((0x276) | 0x400) << 2),(((0x271) | 0x400) << 2),
  (((0x26d) | 0x400) << 2),(((0x268) | 0x400) << 2),(((0x264) | 0x400) << 2),(((0x25f) | 0x400) << 2),(((0x25b) | 0x400) << 2),(((0x257) | 0x400) << 2),(((0x252) | 0x400) << 2),(((0x24e) | 0x400) << 2),
  (((0x249) | 0x400) << 2),(((0x245) | 0x400) << 2),(((0x241) | 0x400) << 2),(((0x23c) | 0x400) << 2),(((0x238) | 0x400) << 2),(((0x234) | 0x400) << 2),(((0x230) | 0x400) << 2),(((0x22b) | 0x400) << 2),
  (((0x227) | 0x400) << 2),(((0x223) | 0x400) << 2),(((0x21e) | 0x400) << 2),(((0x21a) | 0x400) << 2),(((0x216) | 0x400) << 2),(((0x212) | 0x400) << 2),(((0x20e) | 0x400) << 2),(((0x209) | 0x400) << 2),
  (((0x205) | 0x400) << 2),(((0x201) | 0x400) << 2),(((0x1fd) | 0x400) << 2),(((0x1f9) | 0x400) << 2),(((0x1f5) | 0x400) << 2),(((0x1f0) | 0x400) << 2),(((0x1ec) | 0x400) << 2),(((0x1e8) | 0x400) << 2),
  (((0x1e4) | 0x400) << 2),(((0x1e0) | 0x400) << 2),(((0x1dc) | 0x400) << 2),(((0x1d8) | 0x400) << 2),(((0x1d4) | 0x400) << 2),(((0x1d0) | 0x400) << 2),(((0x1cc) | 0x400) << 2),(((0x1c8) | 0x400) << 2),
  (((0x1c4) | 0x400) << 2),(((0x1c0) | 0x400) << 2),(((0x1bc) | 0x400) << 2),(((0x1b8) | 0x400) << 2),(((0x1b4) | 0x400) << 2),(((0x1b0) | 0x400) << 2),(((0x1ac) | 0x400) << 2),(((0x1a8) | 0x400) << 2),
  (((0x1a4) | 0x400) << 2),(((0x1a0) | 0x400) << 2),(((0x19c) | 0x400) << 2),(((0x199) | 0x400) << 2),(((0x195) | 0x400) << 2),(((0x191) | 0x400) << 2),(((0x18d) | 0x400) << 2),(((0x189) | 0x400) << 2),
  (((0x185) | 0x400) << 2),(((0x181) | 0x400) << 2),(((0x17e) | 0x400) << 2),(((0x17a) | 0x400) << 2),(((0x176) | 0x400) << 2),(((0x172) | 0x400) << 2),(((0x16f) | 0x400) << 2),(((0x16b) | 0x400) << 2),
  (((0x167) | 0x400) << 2),(((0x163) | 0x400) << 2),(((0x160) | 0x400) << 2),(((0x15c) | 0x400) << 2),(((0x158) | 0x400) << 2),(((0x154) | 0x400) << 2),(((0x151) | 0x400) << 2),(((0x14d) | 0x400) << 2),
  (((0x149) | 0x400) << 2),(((0x146) | 0x400) << 2),(((0x142) | 0x400) << 2),(((0x13e) | 0x400) << 2),(((0x13b) | 0x400) << 2),(((0x137) | 0x400) << 2),(((0x134) | 0x400) << 2),(((0x130) | 0x400) << 2),
  (((0x12c) | 0x400) << 2),(((0x129) | 0x400) << 2),(((0x125) | 0x400) << 2),(((0x122) | 0x400) << 2),(((0x11e) | 0x400) << 2),(((0x11b) | 0x400) << 2),(((0x117) | 0x400) << 2),(((0x114) | 0x400) << 2),
  (((0x110) | 0x400) << 2),(((0x10c) | 0x400) << 2),(((0x109) | 0x400) << 2),(((0x106) | 0x400) << 2),(((0x102) | 0x400) << 2),(((0x0ff) | 0x400) << 2),(((0x0fb) | 0x400) << 2),(((0x0f8) | 0x400) << 2),
  (((0x0f4) | 0x400) << 2),(((0x0f1) | 0x400) << 2),(((0x0ed) | 0x400) << 2),(((0x0ea) | 0x400) << 2),(((0x0e7) | 0x400) << 2),(((0x0e3) | 0x400) << 2),(((0x0e0) | 0x400) << 2),(((0x0dc) | 0x400) << 2),
  (((0x0d9) | 0x400) << 2),(((0x0d6) | 0x400) << 2),(((0x0d2) | 0x400) << 2),(((0x0cf) | 0x400) << 2),(((0x0cc) | 0x400) << 2),(((0x0c8) | 0x400) << 2),(((0x0c5) | 0x400) << 2),(((0x0c2) | 0x400) << 2),
  (((0x0be) | 0x400) << 2),(((0x0bb) | 0x400) << 2),(((0x0b8) | 0x400) << 2),(((0x0b5) | 0x400) << 2),(((0x0b1) | 0x400) << 2),(((0x0ae) | 0x400) << 2),(((0x0ab) | 0x400) << 2),(((0x0a8) | 0x400) << 2),
  (((0x0a4) | 0x400) << 2),(((0x0a1) | 0x400) << 2),(((0x09e) | 0x400) << 2),(((0x09b) | 0x400) << 2),(((0x098) | 0x400) << 2),(((0x094) | 0x400) << 2),(((0x091) | 0x400) << 2),(((0x08e) | 0x400) << 2),
  (((0x08b) | 0x400) << 2),(((0x088) | 0x400) << 2),(((0x085) | 0x400) << 2),(((0x082) | 0x400) << 2),(((0x07e) | 0x400) << 2),(((0x07b) | 0x400) << 2),(((0x078) | 0x400) << 2),(((0x075) | 0x400) << 2),
  (((0x072) | 0x400) << 2),(((0x06f) | 0x400) << 2),(((0x06c) | 0x400) << 2),(((0x069) | 0x400) << 2),(((0x066) | 0x400) << 2),(((0x063) | 0x400) << 2),(((0x060) | 0x400) << 2),(((0x05d) | 0x400) << 2),
  (((0x05a) | 0x400) << 2),(((0x057) | 0x400) << 2),(((0x054) | 0x400) << 2),(((0x051) | 0x400) << 2),(((0x04e) | 0x400) << 2),(((0x04b) | 0x400) << 2),(((0x048) | 0x400) << 2),(((0x045) | 0x400) << 2),
  (((0x042) | 0x400) << 2),(((0x03f) | 0x400) << 2),(((0x03c) | 0x400) << 2),(((0x039) | 0x400) << 2),(((0x036) | 0x400) << 2),(((0x033) | 0x400) << 2),(((0x030) | 0x400) << 2),(((0x02d) | 0x400) << 2),
  (((0x02a) | 0x400) << 2),(((0x028) | 0x400) << 2),(((0x025) | 0x400) << 2),(((0x022) | 0x400) << 2),(((0x01f) | 0x400) << 2),(((0x01c) | 0x400) << 2),(((0x019) | 0x400) << 2),(((0x016) | 0x400) << 2),
  (((0x014) | 0x400) << 2),(((0x011) | 0x400) << 2),(((0x00e) | 0x400) << 2),(((0x00b) | 0x400) << 2),(((0x008) | 0x400) << 2),(((0x006) | 0x400) << 2),(((0x003) | 0x400) << 2),(((0x000) | 0x400) << 2)
 };



 return s_power_table[input & 0xff] >> (input >> 8);
}
# 947 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
uint32_t opl_emu_attenuation_increment(uint32_t rate, uint32_t index)
{
 static uint32_t const s_increment_table[64] =
 {
  0x00000000, 0x00000000, 0x10101010, 0x10101010,
  0x10101010, 0x10101010, 0x11101110, 0x11101110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x10101010, 0x10111010, 0x11101110, 0x11111110,
  0x11111111, 0x21112111, 0x21212121, 0x22212221,
  0x22222222, 0x42224222, 0x42424242, 0x44424442,
  0x44444444, 0x84448444, 0x84848484, 0x88848884,
  0x88888888, 0x88888888, 0x88888888, 0x88888888
 };
 return opl_emu_bitfield(s_increment_table[rate], 4*index, 4);
}
# 980 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_registers_init(struct opl_emu_registers* regs)
{
 regs->m_lfo_am_counter = 0;
 regs->m_lfo_pm_counter = 0;
 regs->m_noise_lfsr = 1;
 regs->m_lfo_am = 0;



 uint16_t *wf0 = &regs->m_waveform[0][0];
 uint16_t *wf1 = &regs->m_waveform[1 % 8][0];
 uint16_t *wf2 = &regs->m_waveform[2 % 8][0];
 uint16_t *wf3 = &regs->m_waveform[3 % 8][0];
 uint16_t *wf4 = &regs->m_waveform[4 % 8][0];
 uint16_t *wf5 = &regs->m_waveform[5 % 8][0];
 uint16_t *wf6 = &regs->m_waveform[6 % 8][0];
 uint16_t *wf7 = &regs->m_waveform[7 % 8][0];


 for (uint32_t index = 0; index < 0x400; index++)
  wf0[index] = opl_emu_abs_sin_attenuation(index) | (opl_emu_bitfield(index, 9,1) << 15);

 if (8 >= 4)
 {
  uint16_t zeroval = wf0[0];
  for (uint32_t index = 0; index < 0x400; index++)
  {
   wf1[index] = opl_emu_bitfield(index, 9,1) ? zeroval : wf0[index];
   wf2[index] = wf0[index] & 0x7fff;
   wf3[index] = opl_emu_bitfield(index, 8,1) ? zeroval : (wf0[index] & 0x7fff);
   if (8 >= 8)
   {
    wf4[index] = opl_emu_bitfield(index, 9,1) ? zeroval : wf0[index * 2];
    wf5[index] = opl_emu_bitfield(index, 9,1) ? zeroval : wf0[(index * 2) & 0x1ff];
    wf6[index] = opl_emu_bitfield(index, 9,1) << 15;
    wf7[index] = (opl_emu_bitfield(index, 9,1) ? (index ^ 0x13ff) : index) << 3;
   }
  }
 }
}






void opl_emu_registers_reset(struct opl_emu_registers* regs)
{
    for( int i = 0; i < 0x200; ++i )
        regs->m_regdata[ i ] = 0;
}







void opl_emu_registers_operator_map(struct opl_emu_registers* regs, struct opl_emu_registers_operator_mapping* dest)
{

    uint32_t fourop = opl_emu_registers_fourop_enable(regs);

    dest->chan[ 0] = opl_emu_bitfield(fourop, 0,1) ? opl_emu_registers_operator_list( 0, 3, 6, 9 ) : opl_emu_registers_operator_list( 0, 3, 0xff, 0xff );
    dest->chan[ 1] = opl_emu_bitfield(fourop, 1,1) ? opl_emu_registers_operator_list( 1, 4, 7, 10 ) : opl_emu_registers_operator_list( 1, 4, 0xff, 0xff );
    dest->chan[ 2] = opl_emu_bitfield(fourop, 2,1) ? opl_emu_registers_operator_list( 2, 5, 8, 11 ) : opl_emu_registers_operator_list( 2, 5, 0xff, 0xff );
    dest->chan[ 3] = opl_emu_bitfield(fourop, 0,1) ? opl_emu_registers_operator_list( 0xff, 0xff, 0xff, 0xff) : opl_emu_registers_operator_list( 6, 9, 0xff, 0xff );
    dest->chan[ 4] = opl_emu_bitfield(fourop, 1,1) ? opl_emu_registers_operator_list( 0xff, 0xff, 0xff, 0xff) : opl_emu_registers_operator_list( 7, 10, 0xff, 0xff );
    dest->chan[ 5] = opl_emu_bitfield(fourop, 2,1) ? opl_emu_registers_operator_list( 0xff, 0xff, 0xff, 0xff) : opl_emu_registers_operator_list( 8, 11, 0xff, 0xff );
    dest->chan[ 6] = opl_emu_registers_operator_list( 12, 15, 0xff, 0xff );
    dest->chan[ 7] = opl_emu_registers_operator_list( 13, 16, 0xff, 0xff );
    dest->chan[ 8] = opl_emu_registers_operator_list( 14, 17, 0xff, 0xff );

    dest->chan[ 9] = opl_emu_bitfield(fourop, 3,1) ? opl_emu_registers_operator_list( 18, 21, 24, 27 ) : opl_emu_registers_operator_list( 18, 21, 0xff, 0xff );
    dest->chan[10] = opl_emu_bitfield(fourop, 4,1) ? opl_emu_registers_operator_list( 19, 22, 25, 28 ) : opl_emu_registers_operator_list( 19, 22, 0xff, 0xff );
    dest->chan[11] = opl_emu_bitfield(fourop, 5,1) ? opl_emu_registers_operator_list( 20, 23, 26, 29 ) : opl_emu_registers_operator_list( 20, 23, 0xff, 0xff );
    dest->chan[12] = opl_emu_bitfield(fourop, 3,1) ? opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff) : opl_emu_registers_operator_list( 24, 27, 0xff, 0xff );
    dest->chan[13] = opl_emu_bitfield(fourop, 4,1) ? opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff) : opl_emu_registers_operator_list( 25, 28, 0xff, 0xff );
    dest->chan[14] = opl_emu_bitfield(fourop, 5,1) ? opl_emu_registers_operator_list(0xff, 0xff, 0xff, 0xff) : opl_emu_registers_operator_list( 26, 29, 0xff, 0xff );
    dest->chan[15] = opl_emu_registers_operator_list( 30, 33, 0xff, 0xff );
    dest->chan[16] = opl_emu_registers_operator_list( 31, 34, 0xff, 0xff );
    dest->chan[17] = opl_emu_registers_operator_list( 32, 35, 0xff, 0xff );
}






int opl_emu_registers_write(struct opl_emu_registers* regs,uint16_t index, uint8_t data, uint32_t *channel, uint32_t *opmask)
{

 if (index == 0x04 && opl_emu_bitfield(data, 7,1) != 0)
  regs->m_regdata[index] |= 0x80;
 else
  regs->m_regdata[index] = data;


 if (index == 0xbd)
 {
  *channel = 0xff;
  *opmask = opl_emu_bitfield(data, 5,1) ? opl_emu_bitfield(data, 0, 5) : 0;
  return 1;
 }


 if ((index & 0xf0) == 0xb0)
 {
  *channel = index & 0x0f;
  if (*channel < 9)
  {
            *channel += 9 * opl_emu_bitfield(index, 8,1);
   *opmask = opl_emu_bitfield(data, 5,1) ? 15 : 0;
   return 1;
  }
 }
 return 0;
}
# 1106 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
static int32_t opl_emu_opl_clock_noise_and_lfo(uint32_t *noise_lfsr, uint16_t *lfo_am_counter, uint16_t *lfo_pm_counter, uint8_t *lfo_am, uint32_t am_depth, uint32_t pm_depth)
{


 *noise_lfsr <<= 1;
 *noise_lfsr |= opl_emu_bitfield(*noise_lfsr, 23,1) ^ opl_emu_bitfield(*noise_lfsr, 9,1) ^ opl_emu_bitfield(*noise_lfsr, 8,1) ^ opl_emu_bitfield(*noise_lfsr, 1,1);





 uint32_t am_counter = *lfo_am_counter++;
 if (am_counter >= 210*64 - 1)
  *lfo_am_counter = 0;


 int shift = 9 - 2 * am_depth;



 *lfo_am = ((am_counter < 105*64) ? am_counter : (210*64+63 - am_counter)) >> shift;


 uint32_t pm_counter = *lfo_pm_counter++;




 static int8_t pm_scale[8] = { 8, 4, 0, -4, -8, -4, 0, 4 };
 return pm_scale[opl_emu_bitfield(pm_counter, 10, 3)] >> (pm_depth ^ 1);
}

int32_t opl_emu_registers_clock_noise_and_lfo(struct opl_emu_registers* regs)
{
 return opl_emu_opl_clock_noise_and_lfo(&regs->m_noise_lfsr, &regs->m_lfo_am_counter, &regs->m_lfo_pm_counter, &regs->m_lfo_am, opl_emu_registers_lfo_am_depth(regs), opl_emu_registers_lfo_pm_depth(regs));
}
# 1151 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_registers_cache_operator_data(struct opl_emu_registers* regs,uint32_t choffs, uint32_t opoffs, struct opl_emu_opdata_cache *cache)
{

 cache->waveform = &regs->m_waveform[opl_emu_registers_op_waveform(regs, opoffs) % 8][0];


 uint32_t block_freq = cache->block_freq = opl_emu_registers_ch_block_freq(regs,choffs);
# 1167 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
 uint32_t keycode = opl_emu_bitfield(block_freq, 10, 3) << 1;



 keycode |= opl_emu_bitfield(block_freq, 9 - opl_emu_registers_note_select(regs), 1);


 cache->detune = 0;



 uint32_t multiple = opl_emu_registers_op_multiple(regs,opoffs);
 cache->multiple = ((multiple & 0xe) | opl_emu_bitfield(0xc2aa, multiple,1)) * 2;
 if (cache->multiple == 0)
  cache->multiple = 1;



 if (opl_emu_registers_op_lfo_pm_enable(regs,opoffs) == 0)
  cache->phase_step = opl_emu_registers_compute_phase_step(regs,choffs, opoffs, cache, 0);
 else
  cache->phase_step = 1;


 cache->total_level = opl_emu_registers_op_total_level(regs,opoffs) << 3;


 uint32_t ksl = opl_emu_registers_op_ksl(regs,opoffs);
 if (ksl != 0)
  cache->total_level += opl_emu_opl_key_scale_atten(opl_emu_bitfield(block_freq, 10, 3), opl_emu_bitfield(block_freq, 6, 4)) << ksl;


 cache->eg_sustain = opl_emu_registers_op_sustain_level(regs,opoffs);
 cache->eg_sustain |= (cache->eg_sustain + 1) & 0x10;
 cache->eg_sustain <<= 5;


 uint32_t ksrval = keycode >> (2 * (opl_emu_registers_op_ksr(regs,opoffs) ^ 1));
 cache->eg_rate[OPL_EMU_EG_ATTACK] = opl_emu_registers_effective_rate(opl_emu_registers_op_attack_rate(regs,opoffs) * 4, ksrval);
 cache->eg_rate[OPL_EMU_EG_DECAY] = opl_emu_registers_effective_rate(opl_emu_registers_op_decay_rate(regs,opoffs) * 4, ksrval);
 cache->eg_rate[OPL_EMU_EG_SUSTAIN] = opl_emu_registers_op_eg_sustain(regs,opoffs) ? 0 : opl_emu_registers_effective_rate(opl_emu_registers_op_release_rate(regs,opoffs) * 4, ksrval);
 cache->eg_rate[OPL_EMU_EG_RELEASE] = opl_emu_registers_effective_rate(opl_emu_registers_op_release_rate(regs,opoffs) * 4, ksrval);
}






static uint32_t opl_emu_opl_compute_phase_step(uint32_t block_freq, uint32_t multiple, int32_t lfo_raw_pm)
{




 uint32_t fnum = opl_emu_bitfield(block_freq, 0, 10) << 2;



 fnum += (lfo_raw_pm * opl_emu_bitfield(block_freq, 7, 3)) >> 1;


 fnum &= 0xfff;


 uint32_t block = opl_emu_bitfield(block_freq, 10, 3);
 uint32_t phase_step = (fnum << block) >> 2;


 return (phase_step * multiple) >> 1;
}

uint32_t opl_emu_registers_compute_phase_step(struct opl_emu_registers* regs,uint32_t choffs, uint32_t opoffs, struct opl_emu_opdata_cache const *cache, int32_t lfo_raw_pm)
{
 return opl_emu_opl_compute_phase_step(cache->block_freq, cache->multiple, opl_emu_registers_op_lfo_pm_enable(regs,opoffs) ? lfo_raw_pm : 0);
}
# 1254 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_operator_init(struct opl_emu_fm_operator* fmop, struct opl_emu_registers* regs, uint32_t opoffs) {
 fmop->m_choffs = 0;
 fmop->m_opoffs = opoffs;
 fmop->m_phase = 0;
 fmop->m_env_attenuation = 0x3ff;
 fmop->m_env_state = OPL_EMU_EG_RELEASE;
 fmop->m_key_state = 0;
 fmop->m_keyon_live = 0;
 fmop->m_regs = regs;
 fmop->m_cache.eg_shift = 0;
}






void opl_emu_fm_operator_reset(struct opl_emu_fm_operator* fmop)
{

 fmop->m_phase = 0;
 fmop->m_env_attenuation = 0x3ff;
 fmop->m_env_state = OPL_EMU_EG_RELEASE;
 fmop->m_key_state = 0;
 fmop->m_keyon_live = 0;
}





int opl_emu_fm_operator_prepare(struct opl_emu_fm_operator* fmop)
{

 opl_emu_registers_cache_operator_data(fmop->m_regs,fmop->m_choffs, fmop->m_opoffs, &fmop->m_cache);


 opl_emu_fm_operator_clock_keystate(fmop,(uint32_t)(fmop->m_keyon_live != 0));
 fmop->m_keyon_live &= ~(1 << OPL_EMU_KEYON_CSM);


 return (fmop->m_env_state != OPL_EMU_EG_RELEASE || fmop->m_env_attenuation < 0x200);
}






void opl_emu_fm_operator_clock(struct opl_emu_fm_operator* fmop, uint32_t env_counter, int32_t lfo_raw_pm)
{

 if (opl_emu_bitfield(env_counter, 0, 2) == 0)
  opl_emu_fm_operator_clock_envelope(fmop,env_counter >> 2);


 opl_emu_fm_operator_clock_phase(fmop,lfo_raw_pm);
}
# 1320 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
int32_t opl_emu_fm_operator_compute_volume(struct opl_emu_fm_operator* fmop, uint32_t phase, uint32_t am_offset)
{




 if (fmop->m_env_attenuation > 0x200)
  return 0;


 uint32_t sin_attenuation = fmop->m_cache.waveform[phase & (0x400 - 1)];


 uint32_t env_attenuation = opl_emu_fm_operator_envelope_attenuation(fmop, am_offset) << 2;


 int32_t result = opl_emu_attenuation_to_volume((sin_attenuation & 0x7fff) + env_attenuation);


 return opl_emu_bitfield(sin_attenuation, 15,1) ? -result : result;
}






void opl_emu_fm_operator_keyonoff(struct opl_emu_fm_operator* fmop, uint32_t on, enum opl_emu_keyon_type type)
{
 fmop->m_keyon_live = (fmop->m_keyon_live & ~(1 << (int)(type))) | (opl_emu_bitfield(on, 0,1) << (int)(type));
}







void opl_emu_fm_operator_start_attack(struct opl_emu_fm_operator* fmop)
{

 if (fmop->m_env_state == OPL_EMU_EG_ATTACK)
  return;
 fmop->m_env_state = OPL_EMU_EG_ATTACK;


    fmop->m_phase = 0;


 if (fmop->m_cache.eg_rate[OPL_EMU_EG_ATTACK] >= 62)
  fmop->m_env_attenuation = 0;
}







void opl_emu_fm_operator_start_release(struct opl_emu_fm_operator* fmop)
{

 if (fmop->m_env_state >= OPL_EMU_EG_RELEASE)
  return;
 fmop->m_env_state = OPL_EMU_EG_RELEASE;
}







void opl_emu_fm_operator_clock_keystate(struct opl_emu_fm_operator* fmop, uint32_t keystate)
{

 if ((keystate ^ fmop->m_key_state) != 0)
 {
  fmop->m_key_state = keystate;


  if (keystate != 0)
  {
            opl_emu_fm_operator_start_attack(fmop);
  }


  else
   opl_emu_fm_operator_start_release(fmop);
 }
}







void opl_emu_fm_operator_clock_envelope(struct opl_emu_fm_operator* fmop, uint32_t env_counter)
{

 if (fmop->m_env_state == OPL_EMU_EG_ATTACK && fmop->m_env_attenuation == 0)
  fmop->m_env_state = OPL_EMU_EG_DECAY;






 if (fmop->m_env_state == OPL_EMU_EG_DECAY && fmop->m_env_attenuation >= fmop->m_cache.eg_sustain)
  fmop->m_env_state = OPL_EMU_EG_SUSTAIN;


 uint32_t rate = fmop->m_cache.eg_rate[fmop->m_env_state];




 uint32_t rate_shift = rate >> 2;
 env_counter <<= rate_shift;


 if (opl_emu_bitfield(env_counter, 0, 11) != 0)
  return;


 uint32_t relevant_bits = opl_emu_bitfield(env_counter, (rate_shift <= 11) ? 11 : rate_shift, 3);
 uint32_t increment = opl_emu_attenuation_increment(rate, relevant_bits);


 if (fmop->m_env_state == OPL_EMU_EG_ATTACK)
 {




  if (rate < 62)
   fmop->m_env_attenuation += (~fmop->m_env_attenuation * increment) >> 4;
 }


 else
 {

        fmop->m_env_attenuation += increment;


  if (fmop->m_env_attenuation >= 0x400)
   fmop->m_env_attenuation = 0x3ff;
 }
}
# 1479 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_operator_clock_phase(struct opl_emu_fm_operator* fmop, int32_t lfo_raw_pm)
{

 uint32_t phase_step = fmop->m_cache.phase_step;
 if (phase_step == 1)
  phase_step = opl_emu_registers_compute_phase_step(fmop->m_regs,fmop->m_choffs, fmop->m_opoffs, &fmop->m_cache, lfo_raw_pm);


 fmop->m_phase += phase_step;
}







uint32_t opl_emu_fm_operator_envelope_attenuation(struct opl_emu_fm_operator* fmop, uint32_t am_offset)
{
 uint32_t result = fmop->m_env_attenuation >> fmop->m_cache.eg_shift;


 if (opl_emu_registers_op_lfo_am_enable(fmop->m_regs,fmop->m_opoffs))
  result += am_offset;


 result += fmop->m_cache.total_level;


 return (((result)<(0x3ff))?(result):(0x3ff));
}
# 1521 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_channel_init(struct opl_emu_fm_channel* fmch,struct opl_emu_registers* regs, uint32_t choffs) {
 fmch->m_choffs = choffs;
 fmch->m_feedback[ 0 ] = 0;
    fmch->m_feedback[ 1 ] = 0;
 fmch->m_feedback_in = 0;
 fmch->m_op[ 0 ] = 0;
 fmch->m_op[ 1 ] = 0;
 fmch->m_op[ 2 ] = 0;
 fmch->m_op[ 3 ] = 0;
 fmch->m_regs = regs;
}






void opl_emu_fm_channel_reset(struct opl_emu_fm_channel* fmch)
{

 fmch->m_feedback[0] = fmch->m_feedback[1] = 0;
 fmch->m_feedback_in = 0;
}





void opl_emu_fm_channel_keyonoff(struct opl_emu_fm_channel* fmch,uint32_t states, enum opl_emu_keyon_type type, uint32_t chnum)
{
 for (uint32_t opnum = 0; opnum < sizeof( fmch->m_op ) / sizeof( *fmch->m_op ); opnum++)
  if (fmch->m_op[opnum] != 0)
   opl_emu_fm_operator_keyonoff(fmch->m_op[opnum],opl_emu_bitfield(states, opnum,1), type);
}






int opl_emu_fm_channel_prepare(struct opl_emu_fm_channel* fmch)
{
 uint32_t active_mask = 0;


 for (uint32_t opnum = 0; opnum < sizeof( fmch->m_op ) / sizeof( *fmch->m_op ); opnum++)
  if (fmch->m_op[opnum] != 0)
   if (opl_emu_fm_operator_prepare(fmch->m_op[opnum]))
    active_mask |= 1 << opnum;

 return (active_mask != 0);
}






void opl_emu_fm_channel_clock(struct opl_emu_fm_channel* fmch,uint32_t env_counter, int32_t lfo_raw_pm)
{

 fmch->m_feedback[0] = fmch->m_feedback[1];
 fmch->m_feedback[1] = fmch->m_feedback_in;

 for (uint32_t opnum = 0; opnum < sizeof( fmch->m_op ) / sizeof( *fmch->m_op ); opnum++)
  if (fmch->m_op[opnum] != 0)
   opl_emu_fm_operator_clock(fmch->m_op[opnum],env_counter, lfo_raw_pm);
}
# 1598 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_channel_output_2op(struct opl_emu_fm_channel* fmch,short *output, uint32_t rshift, int32_t clipmax)
{


 uint32_t am_offset = opl_emu_registers_lfo_am_offset(fmch->m_regs,fmch->m_choffs);


 int32_t opmod = 0;
 uint32_t feedback = opl_emu_registers_ch_feedback(fmch->m_regs,fmch->m_choffs);
 if (feedback != 0)
  opmod = (fmch->m_feedback[0] + fmch->m_feedback[1]) >> (10 - feedback);


 int32_t op1value = fmch->m_feedback_in = opl_emu_fm_operator_compute_volume(fmch->m_op[0], opl_emu_fm_operator_phase(fmch->m_op[0]) + opmod, am_offset);



 if (opl_emu_registers_ch_output_any(fmch->m_regs,fmch->m_choffs) == 0)
  return;




 int32_t result;
 if (opl_emu_bitfield(opl_emu_registers_ch_algorithm(fmch->m_regs,fmch->m_choffs), 0,1) == 0)
 {


  opmod = op1value >> 1;
  result = opl_emu_fm_operator_compute_volume(fmch->m_op[1], opl_emu_fm_operator_phase(fmch->m_op[1]) + opmod, am_offset) >> rshift;
 }
 else
 {
  result = op1value + (opl_emu_fm_operator_compute_volume(fmch->m_op[1], opl_emu_fm_operator_phase(fmch->m_op[1]), am_offset) >> rshift);
  int32_t clipmin = -clipmax - 1;
  result = opl_emu_clamp(result, clipmin, clipmax);
 }


 opl_emu_fm_channel_add_to_output(fmch,fmch->m_choffs, output, result);
}
# 1648 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_channel_output_4op(struct opl_emu_fm_channel* fmch,short *output, uint32_t rshift, int32_t clipmax)
{

 uint32_t am_offset = opl_emu_registers_lfo_am_offset(fmch->m_regs,fmch->m_choffs);


 int32_t opmod = 0;
 uint32_t feedback = opl_emu_registers_ch_feedback(fmch->m_regs,fmch->m_choffs);
 if (feedback != 0)
  opmod = (fmch->m_feedback[0] + fmch->m_feedback[1]) >> (10 - feedback);


 int32_t op1value = fmch->m_feedback_in = opl_emu_fm_operator_compute_volume(fmch->m_op[0], opl_emu_fm_operator_phase(fmch->m_op[0]) + opmod, am_offset);



 if (opl_emu_registers_ch_output_any(fmch->m_regs,fmch->m_choffs) == 0)
  return;
# 1692 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
 static uint16_t const s_algorithm_ops[8+4] =
 {
  ((1) | ((2) << 1) | ((3) << 4) | ((0) << 7) | ((0) << 8) | ((0) << 9)),
  ((0) | ((5) << 1) | ((3) << 4) | ((0) << 7) | ((0) << 8) | ((0) << 9)),
  ((0) | ((2) << 1) | ((6) << 4) | ((0) << 7) | ((0) << 8) | ((0) << 9)),
  ((1) | ((0) << 1) | ((7) << 4) | ((0) << 7) | ((0) << 8) | ((0) << 9)),
  ((1) | ((0) << 1) | ((3) << 4) | ((0) << 7) | ((1) << 8) | ((0) << 9)),
  ((1) | ((1) << 1) | ((1) << 4) | ((0) << 7) | ((1) << 8) | ((1) << 9)),
  ((1) | ((0) << 1) | ((0) << 4) | ((0) << 7) | ((1) << 8) | ((1) << 9)),
  ((0) | ((0) << 1) | ((0) << 4) | ((1) << 7) | ((1) << 8) | ((1) << 9)),
  ((1) | ((2) << 1) | ((3) << 4) | ((0) << 7) | ((0) << 8) | ((0) << 9)),
  ((0) | ((2) << 1) | ((3) << 4) | ((1) << 7) | ((0) << 8) | ((0) << 9)),
  ((1) | ((0) << 1) | ((3) << 4) | ((0) << 7) | ((1) << 8) | ((0) << 9)),
  ((0) | ((2) << 1) | ((0) << 4) | ((1) << 7) | ((0) << 8) | ((1) << 9))
 };
 uint32_t algorithm_ops = s_algorithm_ops[opl_emu_registers_ch_algorithm(fmch->m_regs,fmch->m_choffs)];


 int16_t opout[8];
 opout[0] = 0;
 opout[1] = op1value;


 opmod = opout[opl_emu_bitfield(algorithm_ops, 0, 1)] >> 1;
 opout[2] = opl_emu_fm_operator_compute_volume(fmch->m_op[1], opl_emu_fm_operator_phase(fmch->m_op[1]) + opmod, am_offset);
 opout[5] = opout[1] + opout[2];


 opmod = opout[opl_emu_bitfield(algorithm_ops, 1, 3)] >> 1;
 opout[3] = opl_emu_fm_operator_compute_volume(fmch->m_op[2], opl_emu_fm_operator_phase(fmch->m_op[2]) + opmod, am_offset);
 opout[6] = opout[1] + opout[3];
 opout[7] = opout[2] + opout[3];



    opmod = opout[opl_emu_bitfield(algorithm_ops, 4, 3)] >> 1;
    int32_t result = opl_emu_fm_operator_compute_volume(fmch->m_op[3], opl_emu_fm_operator_phase(fmch->m_op[3]) + opmod, am_offset);

 result >>= rshift;


 int32_t clipmin = -clipmax - 1;
 if (opl_emu_bitfield(algorithm_ops, 7,1) != 0)
  result = opl_emu_clamp(result + (opout[1] >> rshift), clipmin, clipmax);
 if (opl_emu_bitfield(algorithm_ops, 8,1) != 0)
  result = opl_emu_clamp(result + (opout[2] >> rshift), clipmin, clipmax);
 if (opl_emu_bitfield(algorithm_ops, 9,1) != 0)
  result = opl_emu_clamp(result + (opout[3] >> rshift), clipmin, clipmax);


 opl_emu_fm_channel_add_to_output(fmch,fmch->m_choffs, output, result);
}
# 1752 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_channel_output_rhythm_ch6(struct opl_emu_fm_channel* fmch,short *output, uint32_t rshift, int32_t clipmax)
{

 uint32_t am_offset = opl_emu_registers_lfo_am_offset(fmch->m_regs,fmch->m_choffs);






 int32_t opmod = 0;
 uint32_t feedback = opl_emu_registers_ch_feedback(fmch->m_regs,fmch->m_choffs);
 if (feedback != 0)
  opmod = (fmch->m_feedback[0] + fmch->m_feedback[1]) >> (10 - feedback);


 int32_t opout1 = fmch->m_feedback_in = opl_emu_fm_operator_compute_volume(fmch->m_op[0], opl_emu_fm_operator_phase(fmch->m_op[0]) + opmod, am_offset);


 opmod = opl_emu_bitfield(opl_emu_registers_ch_algorithm(fmch->m_regs,fmch->m_choffs), 0,1) ? 0 : (opout1 >> 1);
 int32_t result = opl_emu_fm_operator_compute_volume(fmch->m_op[1], opl_emu_fm_operator_phase(fmch->m_op[1]) + opmod, am_offset) >> rshift;


 opl_emu_fm_channel_add_to_output(fmch, fmch->m_choffs, output, result * 2);
}
# 1786 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_channel_output_rhythm_ch7(struct opl_emu_fm_channel* fmch,uint32_t phase_select,short *output, uint32_t rshift, int32_t clipmax)
{

 uint32_t am_offset = opl_emu_registers_lfo_am_offset(fmch->m_regs,fmch->m_choffs);
 uint32_t noise_state = opl_emu_bitfield(opl_emu_registers_noise_state(fmch->m_regs), 0,1);




 uint32_t phase = (phase_select << 9) | (0xd0 >> (2 * (noise_state ^ phase_select)));
 int32_t result = opl_emu_fm_operator_compute_volume(fmch->m_op[0], phase, am_offset) >> rshift;



 uint32_t op13phase = opl_emu_fm_operator_phase(fmch->m_op[0]);
 phase = (0x100 << opl_emu_bitfield(op13phase, 8,1)) ^ (noise_state << 8);
 result += opl_emu_fm_operator_compute_volume(fmch->m_op[1],phase, am_offset) >> rshift;
 result = opl_emu_clamp(result, -clipmax - 1, clipmax);


 opl_emu_fm_channel_add_to_output(fmch, fmch->m_choffs, output, result * 2);
}
# 1816 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
void opl_emu_fm_channel_output_rhythm_ch8(struct opl_emu_fm_channel* fmch,uint32_t phase_select,short *output, uint32_t rshift, int32_t clipmax)
{

 uint32_t am_offset = opl_emu_registers_lfo_am_offset(fmch->m_regs,fmch->m_choffs);


 int32_t result = opl_emu_fm_operator_compute_volume(fmch->m_op[0], opl_emu_fm_operator_phase(fmch->m_op[0]), am_offset) >> rshift;



 uint32_t phase = 0x100 | (phase_select << 9);
 result += opl_emu_fm_operator_compute_volume(fmch->m_op[1], phase, am_offset) >> rshift;
 result = opl_emu_clamp(result, -clipmax - 1, clipmax);


 opl_emu_fm_channel_add_to_output(fmch, fmch->m_choffs, output, result * 2);
}







struct voicealloc_t {
  unsigned short priority;
  signed short timbreid;
  signed char channel;
  signed char note;
  unsigned char voiceindex;
};

enum op2_flags_t {
  OP2_FIXEDPITCH = 1,
  OP2_UNUSED = 2,
  OP2_DOUBLEVOICE = 4,
};

struct opl_t {
  signed char notes2voices[16][128][2];
  unsigned short channelpitch[16];
  unsigned short channelvol[16];
  struct voicealloc_t voices2notes[18];
  unsigned char channelprog[16];
  int opl3;
  struct opl_emu_t opl_emu;
  struct opl_timbre_t opl_gmtimbres[ 256 ];
  struct opl_timbre_t opl_gmtimbres_voice2[ 256 ];
  int is_op2;
  enum op2_flags_t op2_flags[ 256 ];
};


void oplregwr( opl_t* opl, uint16_t reg, uint8_t data ) {
    opl_emu_write( &opl->opl_emu, reg, data );
}


void opl_render( opl_t* opl, short* sample_pairs, int sample_pairs_count, float volume ) {
    memset( sample_pairs, 0, sample_pairs_count * 2 * sizeof( short ) );
    opl_emu_generate( &opl->opl_emu, sample_pairs, sample_pairs_count, volume );
}


void opl_write( opl_t* opl, int count, unsigned short* regs, unsigned char* data ) {
    struct opl_emu_t* emu = &opl->opl_emu;
    for( int i = 0; i < count; ++i ) {
        uint16_t regnum = regs[ i ];
        uint8_t value = data[ i ];


     if (regnum == 0x04)
     {

      continue;;
     }


     emu->m_modified_channels = ( (1 << 18) - 1 );


     uint32_t keyon_channel;
     uint32_t keyon_opmask;
     if (opl_emu_registers_write(&emu->m_regs,regnum, value, &keyon_channel, &keyon_opmask))
     {

      if (keyon_channel < 18)
      {

       opl_emu_fm_channel_keyonoff(&emu->m_channel[keyon_channel],keyon_opmask, OPL_EMU_KEYON_NORMAL, keyon_channel);
      }
      else if (18 >= 9 && keyon_channel == 0xff)
      {

       opl_emu_fm_channel_keyonoff(&emu->m_channel[6],opl_emu_bitfield(keyon_opmask, 4,1) ? 3 : 0, OPL_EMU_KEYON_RHYTHM, 6);
       opl_emu_fm_channel_keyonoff(&emu->m_channel[7],opl_emu_bitfield(keyon_opmask, 0,1) | (opl_emu_bitfield(keyon_opmask, 3,1) << 1), OPL_EMU_KEYON_RHYTHM, 7);
       opl_emu_fm_channel_keyonoff(&emu->m_channel[8],opl_emu_bitfield(keyon_opmask, 2,1) | (opl_emu_bitfield(keyon_opmask, 1,1) << 1), OPL_EMU_KEYON_RHYTHM, 8);
      }
     }
    }
}


const unsigned short freqtable[128] = {
        345, 365, 387, 410, 435, 460, 488, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517, 547, 580, 615, 651,
        690, 731, 774, 820, 869, 921, 975, 517};

const unsigned char octavetable[128] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7,
        7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8,
        8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9,
        9, 9, 9, 9, 9, 9, 9,10};

const unsigned short pitchtable[256] = {
         29193U,29219U,29246U,29272U,29299U,29325U,29351U,29378U,
         29405U,29431U,29458U,29484U,29511U,29538U,29564U,29591U,
         29618U,29644U,29671U,29698U,29725U,29752U,29778U,29805U,
         29832U,29859U,29886U,29913U,29940U,29967U,29994U,30021U,
         30048U,30076U,30103U,30130U,30157U,30184U,30212U,30239U,
         30266U,30293U,30321U,30348U,30376U,30403U,30430U,30458U,
         30485U,30513U,30541U,30568U,30596U,30623U,30651U,30679U,
         30706U,30734U,30762U,30790U,30817U,30845U,30873U,30901U,
         30929U,30957U,30985U,31013U,31041U,31069U,31097U,31125U,
         31153U,31181U,31209U,31237U,31266U,31294U,31322U,31350U,
         31379U,31407U,31435U,31464U,31492U,31521U,31549U,31578U,
         31606U,31635U,31663U,31692U,31720U,31749U,31778U,31806U,
         31835U,31864U,31893U,31921U,31950U,31979U,32008U,32037U,
         32066U,32095U,32124U,32153U,32182U,32211U,32240U,32269U,
         32298U,32327U,32357U,32386U,32415U,32444U,32474U,32503U,
         32532U,32562U,32591U,32620U,32650U,32679U,32709U,32738U,
         32768U,32798U,32827U,32857U,32887U,32916U,32946U,32976U,
         33005U,33035U,33065U,33095U,33125U,33155U,33185U,33215U,
         33245U,33275U,33305U,33335U,33365U,33395U,33425U,33455U,
         33486U,33516U,33546U,33576U,33607U,33637U,33667U,33698U,
         33728U,33759U,33789U,33820U,33850U,33881U,33911U,33942U,
         33973U,34003U,34034U,34065U,34095U,34126U,34157U,34188U,
         34219U,34250U,34281U,34312U,34343U,34374U,34405U,34436U,
         34467U,34498U,34529U,34560U,34591U,34623U,34654U,34685U,
         34716U,34748U,34779U,34811U,34842U,34874U,34905U,34937U,
         34968U,35000U,35031U,35063U,35095U,35126U,35158U,35190U,
         35221U,35253U,35285U,35317U,35349U,35381U,35413U,35445U,
         35477U,35509U,35541U,35573U,35605U,35637U,35669U,35702U,
         35734U,35766U,35798U,35831U,35863U,35895U,35928U,35960U,
         35993U,36025U,36058U,36090U,36123U,36155U,36188U,36221U,
         36254U,36286U,36319U,36352U,36385U,36417U,36450U,36483U,
         36516U,36549U,36582U,36615U,36648U,36681U,36715U,36748U};







static struct opl_timbre_t opl_gmtimbres_default[ 256 ] = {
# 1994 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
{0x223E133,0x4F4F131,0xA5,0x09,0x0E,0,0},
{0x433F133,0x0F4F131,0xA3,0x09,0x0C,0,0},
{0x4B3E131,0x0F4F130,0x1A,0x86,0x08,0,0},
{0x073FA32,0x4F4D111,0x80,0x08,0x0C,0,0},
{0x0E7F21C,0x0B8F201,0x6F,0x80,0x0C,0,0},
{0x0C7F437,0x0D7F230,0x5D,0x0A,0x08,0,0},
{0x303F232,0x1F6D131,0x44,0x00,0x08,0,0},
{0x559F101,0x0F7F111,0x44,0x08,0x06,0,0},
{0x087F607,0x0E4F231,0x54,0x08,0x09,0,0},
{0x0A5F33F,0x0F2C312,0xA1,0x06,0x0C,0,0},
{0x004561A,0x004F601,0x9E,0x08,0x08,0,0},
{0x0F6F2B2,0x0F6F281,0xE5,0x00,0x0F,0,0},
{0x0F6F618,0x0F7E500,0x63,0x80,0x06,0,0},
{0x096F616,0x0F5F111,0x1F,0x03,0x04,0,0},
{0x082F307,0x0E3F302,0x97,0x8A,0x06,0,0},
{0x4109130,0x3B5F321,0x52,0x88,0x08,0,0},
{0x116B1A2,0x117D160,0x88,0x80,0x07,0,0},
{0x0F8F032,0x0F8F001,0x65,0x00,0x0E,0,0},
{0x018AA70,0x0088AB1,0x44,0x0A,0x04,0,0},
{0x1043030,0x1145431,0x92,0x80,0x0D,0,0},
{0x0178000,0x1176081,0x54,0x8B,0x04,0,0},
{0x025A721,0x1264132,0x4D,0x08,0x06,0,0},
{0x4FAF022,0x01A6221,0x96,0x08,0x0C,0,0},
{0x107F020,0x2055231,0x92,0x07,0x08,0,0},
{0x274A613,0x4B8F401,0xDD,0x05,0x06,0,0},
{0x5E5F133,0x1E4F211,0x99,0x07,0x06,0,0},
{0x21FF021,0x088F211,0xA5,0x48,0x0A,0,0},
{0x132ED10,0x3E7D210,0x87,0x0A,0x06,0,0},
{0x0F4E430,0x0F5F330,0x92,0x80,0x08,0,0},
{0x0F78111,0x3F7F054,0x40,0x45,0x08,0,0},
{0x0F78111,0x2F7F054,0x40,0x45,0x0A,0,0},
{0x6F78AE4,0x649B1F2,0x03,0x0A,0x0A,0,0},
{0x0209220,0x0E6C130,0x97,0x05,0x00,0,0},
{0x0FFF030,0x0F8F131,0x9D,0x00,0x0A,0,0},
{0x026AA20,0x0D7F131,0xCF,0x80,0x0A,0,0},
{0x0007511,0x0B69212,0x1A,0x40,0x08,0,0},
{0x2E69419,0x5B6B311,0x5E,0x08,0x00,0,0},
{0x2E69515,0x1B6B211,0x17,0x08,0x00,0,0},
{0x0F5F430,0x0F6F330,0x0E,0x00,0x0A,0,0},
{0x1468330,0x017D231,0x15,0x00,0x0A,0,0},
{0x2257020,0x4266161,0x95,0x05,0x0A,0,0},
{0x2446070,0x2154130,0x4E,0x00,0x0A,0,0},
{0x214D070,0x1175222,0x0F,0x88,0x02,0,0},
{0x521F570,0x4166021,0x90,0x09,0x06,0,0},
{0x201C3B0,0x0058321,0x8D,0x08,0x08,0,0},
{0x0848521,0x074C411,0x69,0x07,0x0A,0,0},
{0x022E133,0x0F2F131,0xA2,0x09,0x0E,0,0},
{0x4C3C413,0x0B4D215,0x9B,0x09,0x0A,0,0},
{0x223F832,0x4055421,0x99,0x8A,0x0C,0,0},
{0x5059022,0x1055521,0x5B,0x85,0x00,0,0},
{0x1254732,0x40256B1,0xA4,0x0A,0x08,0,0},
{0x0031121,0x1046120,0x58,0x84,0x00,0,0},
{0x0055020,0x0F55021,0x1C,0x0F,0x07,0,0},
{0x239B420,0x0076121,0x50,0x05,0x06,0,0},
{0x05470F0,0x07460B0,0x5A,0x80,0x00,0,0},
{0x2436110,0x114D211,0x90,0x00,0x0C,0,0},
{0x017B561,0x0097F21,0x92,0x04,0x0C,0,0},
{0x0235270,0x0198160,0x1E,0x08,0x0E,0,0},
{0x0157621,0x0378261,0x94,0x00,0x0C,0,0},
{0x118537A,0x5177432,0x21,0x00,0x04,0,0},
{0x0364120,0x02B7220,0x21,0x08,0x0C,0,0},
{0x0577320,0x117C020,0x19,0x03,0x0C,0,0},
{0x036F120,0x337F120,0x92,0x08,0x0E,0,0},
{0x0A66120,0x0976120,0x9B,0x08,0x0E,0,0},
{0x0F37010,0x1F65051,0x51,0x04,0x0A,0,0},
{0x1067021,0x1165231,0x8A,0x00,0x06,0,0},
{0x00B9820,0x10B5330,0x8E,0x00,0x0A,0,0},
{0x10B8020,0x11B6330,0x87,0x00,0x08,0,0},
{0x0235030,0x0076C62,0x58,0x08,0x0A,0,0},
{0x2077820,0x2074331,0x97,0x00,0x06,0,0},
{0x0199030,0x01B6132,0x95,0x80,0x0A,0,0},
{0x0177531,0x0174530,0x93,0x03,0x0C,0,0},
{0x08D6EF1,0x02A3571,0xC0,0x00,0x0E,0,0},
{0x08860A1,0x02A6561,0xA6,0x00,0x08,0,0},
{0x2176522,0x0277421,0x5A,0x00,0x06,0,0},
{0x1273471,0x01745B0,0x8D,0x05,0x04,0,0},
{0x00457E1,0x0375760,0xA8,0x00,0x0E,0,0},
{0x6543739,0x25D67A1,0x28,0x00,0x0E,0,0},
{0x00F31D0,0x0053270,0xC7,0x00,0x0B,0,0},
{0x00581A1,0x0295230,0x37,0x00,0x06,0,0},
{0x20FFF22,0x60FFF21,0x7F,0x12,0x05,0,0},
{0x39BC120,0x368C030,0xBF,0x06,0x00,0,0},
{0x33357F0,0x00767E0,0x28,0x00,0x0E,0,0},
{0x40457E1,0x03D67E0,0x23,0x00,0x0E,0,0},
{0x32B7320,0x12BF131,0x40,0x00,0x08,0,0},
{0x5029071,0x0069060,0x96,0x09,0x08,0,0},
{0x195C120,0x1637030,0x43,0x80,0x0A,0,0},
{0x132ED10,0x3E7D210,0x87,0x08,0x06,0,0},
{0x2946374,0x005A0A1,0xA5,0x05,0x02,0,0},
{0x00521A1,0x0053360,0xC0,0x00,0x09,0,0},
{0x2A5A120,0x196A120,0x95,0x05,0x0C,0,0},
{0x005F0E0,0x0548160,0x44,0x00,0x0B,0,0},
{0x0336183,0x05452E0,0xA7,0x00,0x06,0,0},
{0x2529082,0x1534340,0x9D,0x80,0x0C,0,0},
{0x2345231,0x2135120,0x98,0x00,0x06,0,0},
{0x1521161,0x1632060,0x90,0x80,0x08,0,0},
{0x157B260,0x019F803,0x04,0x40,0x07,0,0},
{0x2322122,0x0133221,0x8C,0x92,0x06,0,0},
{0x074F624,0x0249303,0xC0,0x0D,0x00,0,0},
{0x3D2C091,0x1D2D130,0x8E,0x03,0x00,0,0},
{0x5F29052,0x0F2C240,0x96,0x06,0x08,0,0},
{0x05213E1,0x2131371,0x1A,0x88,0x07,0,0},
{0x0B67060,0x0928031,0x9C,0x11,0x0A,0,0},
{0x0025511,0x1748201,0x94,0x06,0x0E,0,0},
{0x0B37120,0x5F48220,0x1B,0x08,0x02,0,0},
{0x0127530,0x6F4F310,0x0D,0x0A,0x06,0,0},
{0x033F900,0x273F400,0x80,0x80,0x00,0,0},
{0x332F320,0x6E49423,0x0E,0x08,0x08,0,0},
{0x0328413,0x073B410,0xA1,0x00,0x0F,0,0},
{0x1397931,0x2099B22,0x80,0x00,0x06,0,0},
{0x302A130,0x0266221,0x1E,0x00,0x0E,0,0},
{0x0136030,0x1169130,0x12,0x80,0x08,0,0},
{0x032A115,0x172B212,0x00,0x80,0x01,0,0},
{0x001E795,0x0679616,0x81,0x00,0x04,0,0},
{0x4046303,0x005A901,0xCA,0x08,0x06,0,0},
{0x6D1F817,0x098F611,0xA7,0x00,0x06,0,0},
{0x008F312,0x004F600,0x08,0xC8,0x04,0,46},
{0x0C8A820,0x0B7E601,0x0B,0x00,0x00,0,0},
{0x00437D2,0x0343471,0xA1,0x07,0x0C,0,0},
{0x2114109,0x51D2101,0x05,0x80,0x0A,0,0},
{0x4543310,0x3574515,0x19,0x03,0x0E,0,0},
{0x00437D2,0x0343471,0xA1,0x07,0x0C,0,0},
{0x200C327,0x6021300,0x80,0x08,0x0E,0,65},
{0x003EBD7,0x06845D8,0xD4,0x00,0x07,0,0},
{0x62FDA20,0x614B009,0x42,0x48,0x04,0,0},
{0x101FE30,0x6142120,0x00,0x00,0x0C,0,17},
{0x200832F,0x6044020,0x80,0x00,0x0E,0,65},
{0x230732F,0x6E6F400,0x00,0x00,0x0E,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0E,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x06,0,0},
{0x0000000,0x0000000,0x00,0x00,0x06,0,0},
{0x0000000,0x0000000,0x00,0x00,0x06,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0A,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0A,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0E,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x06,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0A,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0C,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0A,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x02,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0E,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0C,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0E,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0E,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x08,0,0},
{0x0000000,0x0000000,0x00,0x00,0x0F,0,0},
{0x057FB00,0x046F800,0x00,0x00,0x0E,0,25},
{0x277F810,0x006FC11,0x86,0x00,0x0A,0,34},
{0x287F702,0x678F802,0x80,0x88,0x0A,0,61},
{0x6EF8801,0x608B502,0x0D,0x00,0x0C,0,38},
{0x05476C1,0x30892C5,0x80,0x08,0x06,0,37},
{0x6EF8800,0x608F502,0x13,0x00,0x08,0,38},
{0x508F601,0x104F600,0x08,0x00,0x06,0,32},
{0x254F307,0x307F905,0x04,0x0B,0x06,0,48},
{0x508F601,0x104F600,0x08,0x00,0x0A,0,34},
{0x254D307,0x3288905,0x04,0x08,0x0A,0,48},
{0x508F601,0x104F600,0x0C,0x00,0x08,0,37},
{0x2F2E327,0x3F5C525,0x04,0x08,0x08,0,48},
{0x508F601,0x104F600,0x0C,0x00,0x00,0,40},
{0x508F601,0x104F600,0x0C,0x00,0x00,0,43},
{0x292F108,0x354F201,0x00,0x08,0x00,0,61},
{0x508F601,0x104F600,0x0C,0x00,0x00,0,46},
{0x210F509,0x305FE03,0x8A,0x88,0x00,0,60},
{0x283E108,0x334D700,0x00,0x08,0x00,0,79},
{0x2E1F119,0x3F3F11B,0x04,0x08,0x00,0,62},
{0x2777603,0x3679601,0x87,0x08,0x00,0,80},
{0x251F206,0x263C504,0x04,0x09,0x00,0,67},
{0x366F905,0x099F701,0x00,0x00,0x00,0,58},
{0x292F108,0x354F201,0x00,0x03,0x00,0,62},
{0x422F120,0x056B40E,0x81,0x00,0x00,0,24},
{0x212FD04,0x305FD03,0x01,0x00,0x00,0,61},
{0x2A8F9E3,0x0779643,0x1E,0x08,0x00,0,41},
{0x2A8F9E3,0x0779643,0x1E,0x00,0x00,0,35},
{0x0A8F7E9,0x5D8990A,0x08,0x00,0x00,0,29},
{0x2A8F9E2,0x0779642,0x1E,0x00,0x00,0,41},
{0x2A8F9E2,0x0779642,0x1E,0x00,0x00,0,37},
{0x456FB02,0x017F700,0x81,0x00,0x00,0,55},
{0x456FB02,0x017F700,0x81,0x00,0x00,0,48},
{0x367FD01,0x098F601,0x00,0x08,0x00,0,78},
{0x367FD01,0x098F601,0x00,0x08,0x00,0,73},
{0x25E780C,0x32B8A0A,0x00,0x80,0x00,0,88},
{0x098600F,0x3FC8590,0x08,0xC0,0x00,0,40},
{0x009F020,0x37DA588,0x07,0x00,0x00,0,45},
{0x00FC020,0x32DA5A8,0x07,0x00,0x00,0,42},
{0x106F680,0x016F610,0x00,0x00,0x00,0,48},
{0x106F680,0x016F610,0x00,0x00,0x00,0,48},
{0x0D1F815,0x078F512,0x44,0x00,0x00,0,73},
{0x1D1F813,0x078F512,0x44,0x00,0x00,0,68},
{0x1D1F813,0x078F512,0x44,0x00,0x00,0,61},
{0x1DC5D01,0x06FF79F,0x0B,0x00,0x00,0,16},
{0x1C7C900,0x05FF49F,0x07,0x00,0x00,0,16},
{0x160F2C6,0x07AF4D4,0x4F,0x80,0x00,0,90},
{0x160F286,0x0B7F294,0x4F,0x80,0x00,0,90},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0},
{0x0000000,0x0000000,0x00,0x00,0x00,0,0}
};




const unsigned short op1offsets[18] = {0x00,0x01,0x02,0x08,0x09,0x0a,0x10,0x11,0x12,0x100,0x101,0x102,0x108,0x109,0x10a,0x110,0x111,0x112};
const unsigned short op2offsets[18] = {0x03,0x04,0x05,0x0b,0x0c,0x0d,0x13,0x14,0x15,0x103,0x104,0x105,0x10b,0x10c,0x10d,0x113,0x114,0x115};


static int voicescount = 9;




static void calc_vol(unsigned char *regbyte, int volume) {
  int level;

  level = ~(*regbyte);
  level &= 0x3f;


  level = (level * volume) / 127;


  if (level > 0x3f) level = 0x3f;
  if (level < 0) level = 0;


  level = ~level;
  level &= 0x3f;


  *regbyte &= 0xC0;
  *regbyte |= level;
}




opl_t* opl_create(void) {

  struct opl_t* opl = (struct opl_t*)calloc(1, sizeof(struct opl_t));
  if (opl == 0) return 0;
  memcpy( opl->opl_gmtimbres, opl_gmtimbres_default, sizeof( opl_gmtimbres_default ) );
  opl_emu_init( &opl->opl_emu );

  opl->is_op2 = 0;


  oplregwr(opl, 0x04, 0x60);
  oplregwr(opl, 0x04, 0x80);

  oplregwr(opl, 0x02, 0xff);
  oplregwr(opl, 0x04, 0x21);





  oplregwr(opl, 0x04, 0x60);
  oplregwr(opl, 0x04, 0x80);







                                   opl->opl3 = 1;


  voicescount = 9;


  if (opl->opl3 != 0) {
    oplregwr(opl, 0x105, 1);
    oplregwr(opl, 0x104, 0);
    voicescount = 18;






  }

  oplregwr(opl, 0x01, 0x20);
  oplregwr(opl, 0x04, 0x00);
  oplregwr(opl, 0x08, 0x40);
  oplregwr(opl, 0xBD, 0x00);

  for (int x = 0; x < voicescount; x++) {
    oplregwr(opl, 0x20 + op1offsets[x], 0x1);
    oplregwr(opl, 0x20 + op2offsets[x], 0x1);
    oplregwr(opl, 0x40 + op1offsets[x], 0x10);
    oplregwr(opl, 0x40 + op2offsets[x], 0x10);
  }

  opl_clear(opl);

  return(opl);
}



void opl_destroy(opl_t* opl) {
  int x;


  opl_clear(opl);


  for (x = 0; x < voicescount; x++) {
    oplregwr(opl, 0x40 + op1offsets[x], 0x1f);
    oplregwr(opl, 0x40 + op2offsets[x], 0x1f);
  }


  if (opl->opl3 != 0) oplregwr(opl, 0x105, 0);


  free(opl);
  opl = 0;
}

void opl_noteoff(opl_t* opl, unsigned short voice) {

  if (voice >= 9) {
    oplregwr(opl, 0x1B0 + voice - 9, 0);
  } else {
    oplregwr(opl, 0xB0 + voice, 0);
  }
}


void opl_noteon(opl_t* opl, unsigned short voice, unsigned int note, int pitch) {
  unsigned int freq = freqtable[note];
  unsigned int octave = octavetable[note];

  if (pitch != 0) {
    if (pitch > 127) {
      pitch = 127;
    } else if (pitch < -128) {
      pitch = -128;
    }
    freq = ((unsigned long)freq * pitchtable[pitch + 128]) >> 15;
    if (freq >= 1024) {
      freq >>= 1;
      octave++;
    }
  }
  if (octave > 7) octave = 7;


  if (voice >= 9) {
    voice -= 9;
    voice |= 0x100;
  }

  oplregwr(opl, 0xA0 + voice, freq & 0xff);
  oplregwr(opl, 0xB0 + voice, (freq >> 8) | (octave << 2) | 32);
}



void opl_clear(opl_t* opl) {
  int x, y;
  for (x = 0; x < voicescount; x++) opl_noteoff(opl, x);


  oplregwr(opl, 0xBD, 0);


  for (x = 0; x < voicescount; x++) {
    opl->voices2notes[x].channel = -1;
    opl->voices2notes[x].note = -1;
    opl->voices2notes[x].timbreid = -1;
    opl->voices2notes[x].voiceindex = 0xFF;
  }


  for (x = 0; x < 16; x++) {
    for (y = 0; y < 128; y++) {
      opl->notes2voices[x][y][0] = -1;
      opl->notes2voices[x][y][1] = -1;
    }
  }



  for (x = 0; x < 16; x++) {
    opl_midi_changeprog(opl,x, x);
    opl->channelvol[x] = 127;
  }
}



void opl_midi_pitchwheel(opl_t* opl, int channel, int pitchwheel) {
  int x;




  for (x = 0; x < voicescount; x++) {
    if (opl->voices2notes[x].channel != channel) continue;

    opl_timbre_t* timbre = opl->voices2notes[x].voiceindex == 0
      ? &(opl->opl_gmtimbres[opl->voices2notes[x].timbreid])
      : &(opl->opl_gmtimbres_voice2[opl->voices2notes[x].timbreid])
      ;
    opl_noteon(opl, x, opl->voices2notes[x].note + timbre->noteoffset, pitchwheel + timbre->finetune);
  }
}


void opl_midi_controller(opl_t* opl, int channel, int id, int value) {
  int x;
  switch (id) {
    case 11:
      opl->channelvol[channel] = value;
      break;
    case 123:
    case 120:
      for (x = 0; x < voicescount; x++) {
        if (opl->voices2notes[x].channel != channel) continue;
        opl_midi_noteoff(opl, channel, opl->voices2notes[x].note);
      }
      break;
  }
}



void opl_midi_changeprog(opl_t* opl,int channel, int program) {
  if (channel == 9) return;
  opl->channelprog[channel] = program;
}


void opl_loadinstrument(opl_t* opl, int voice, opl_timbre_t *timbre) {

  oplregwr(opl, 0x40 + op1offsets[voice], timbre->modulator_40);
  oplregwr(opl, 0x40 + op2offsets[voice], timbre->carrier_40 | 0x3f);


  oplregwr(opl, 0xE0 + op1offsets[voice], timbre->modulator_E862 >> 24);
  oplregwr(opl, 0xE0 + op2offsets[voice], timbre->carrier_E862 >> 24);


  oplregwr(opl, 0x80 + op1offsets[voice], (timbre->modulator_E862 >> 16) & 0xff);
  oplregwr(opl, 0x80 + op2offsets[voice], (timbre->carrier_E862 >> 16) & 0xff);


  oplregwr(opl, 0x60 + op1offsets[voice], (timbre->modulator_E862 >> 8) & 0xff);
  oplregwr(opl, 0x60 + op2offsets[voice], (timbre->carrier_E862 >> 8) & 0xff);


  oplregwr(opl, 0x20 + op1offsets[voice], timbre->modulator_E862 & 0xff);
  oplregwr(opl, 0x20 + op2offsets[voice], timbre->carrier_E862 & 0xff);


  if (voice >= 9) {
    voice -= 9;
    voice |= 0x100;
  }
  if (opl->opl3 != 0) {
    oplregwr(opl, 0xC0 + voice, timbre->feedconn | 0x30);
  } else {
    oplregwr(opl, 0xC0 + voice, timbre->feedconn);
  }

}



static void voicevolume(opl_t* opl, unsigned short voice, const opl_timbre_t* timbre, int volume) {
  unsigned char carrierval = timbre->carrier_40;
  if (volume == 0) {
    carrierval |= 0x3f;
  } else {
    calc_vol(&carrierval, volume);
  }
  oplregwr(opl, 0x40 + op2offsets[voice], carrierval);
}



static int getinstrument(opl_t* opl, int channel, int note) {
  if ((note < 0) || (note > 127) || (channel > 15)) return(-1);
  if (channel == 9) {
    if (opl->is_op2)
      return 128 + note - 35;
    else
      return(128 | note);
  }
  return(opl->channelprog[channel]);
}

void opl_midi_noteoff_op2(opl_t* opl, int channel, int note, int vindex);

void opl_midi_noteon_op2(opl_t* opl, int channel, int note, int velocity, int vindex) {
  if( velocity == 0 ) {
      opl_midi_noteoff_op2( opl, channel, note, vindex );
      return;
  }
  int x, voice = -1;
  int lowestpriority = 0xFFFF;
  int highestvoiceindex = -1;
  int lowestpriorityvoice = -1;
  int instrument;


  instrument = getinstrument(opl, channel, note);
  if (instrument < 0) return;


  if (vindex > 0 && (opl->op2_flags[instrument] & OP2_DOUBLEVOICE) == 0) return;

  opl_timbre_t* timbre = vindex == 0 ? &(opl->opl_gmtimbres[instrument]) : &(opl->opl_gmtimbres_voice2[instrument]);


  if (opl->notes2voices[channel][note][vindex] >= 0) {
    voice = opl->notes2voices[channel][note][vindex];
  } else {

    for (x = 0; x < voicescount; x++) {
      if (opl->voices2notes[x].channel < 0) {
        voice = x;

        if (opl->voices2notes[x].timbreid == instrument && opl->voices2notes[x].voiceindex == vindex) {
          break;
        }
      }
      if (opl->voices2notes[x].priority < lowestpriority) {


        if (opl->voices2notes[x].voiceindex >= vindex && opl->voices2notes[x].voiceindex >= highestvoiceindex) {
          lowestpriorityvoice = x;
          lowestpriority = opl->voices2notes[x].priority;
          highestvoiceindex = opl->voices2notes[x].voiceindex;
        }
      }
    }

    if (voice < 0) {
      if (lowestpriorityvoice < 0) {

        return;
      }
      voice = lowestpriorityvoice;
      opl_midi_noteoff_op2(opl, opl->voices2notes[voice].channel, opl->voices2notes[voice].note, opl->voices2notes[voice].voiceindex);
    }
  }


  if (opl->voices2notes[voice].timbreid != instrument) {
    opl->voices2notes[voice].timbreid = instrument;
    opl_loadinstrument(opl, voice, timbre);
  }


  opl->voices2notes[voice].channel = channel;
  opl->voices2notes[voice].note = note;
  opl->voices2notes[voice].priority = ((16 - channel) << 8) | 0xff;
  opl->voices2notes[voice].voiceindex = vindex;
  opl->notes2voices[channel][note][vindex] = voice;


  if (vindex != 0) {
    int reducedprio = (int)opl->voices2notes[voice].priority - 0xFF;
    if (reducedprio < 0) reducedprio = 0;
    opl->voices2notes[voice].priority = (unsigned short)reducedprio;
  }


  voicevolume(opl, voice, timbre, velocity * opl->channelvol[channel] / 127);


  if (channel == 9) {

    opl_noteon(opl, voice, timbre->notenum + timbre->noteoffset, opl->channelpitch[channel] + timbre->finetune);
  } else {
    opl_noteon(opl, voice, note + timbre->noteoffset, opl->channelpitch[channel] + timbre->finetune);
  }


  for (x = 0; x < voicescount; x++) {
    if (opl->voices2notes[x].priority > 0) opl->voices2notes[x].priority -= 1;
  }
}

void opl_midi_noteon(opl_t* opl, int channel, int note, int velocity) {

  opl_midi_noteon_op2(opl, channel, note, velocity, 1);
  opl_midi_noteon_op2(opl, channel, note, velocity, 0);
}

void opl_midi_noteoff_op2(opl_t* opl, int channel, int note, int vindex) {
  int voice = opl->notes2voices[channel][note][vindex];

  if (voice >= 0) {
    opl_noteoff(opl, voice);
    opl->voices2notes[voice].channel = -1;
    opl->voices2notes[voice].note = -1;
    opl->voices2notes[voice].priority = -1;
    opl->voices2notes[voice].voiceindex = 0xFF;
    opl->notes2voices[channel][note][vindex] = -1;
  }
}

void opl_midi_noteoff(opl_t* opl, int channel, int note) {
    opl_midi_noteoff_op2(opl, channel, note, 0);
    opl_midi_noteoff_op2(opl, channel, note, 1);
}


static int opl_loadbank_internal(opl_t* opl, char const* file, int offset) {
  opl->is_op2 = 0;
  unsigned char buff[16];
  int i;

  FILE* f = fopen( file, "rb" );
  if( !f ) return -1;

  fseek( f, 0, 2 );
  if (ftell(f) != 3204) {
    fclose(f);
    return(-2);
  }
  fseek( f, 0, 0);

  if ((fread(buff, 1, 4,f) != 4) || (buff[0] != 'I') || (buff[1] != 'B') || (buff[2] != 'K') || (buff[3] != 0x1A)) {
    fclose(f);
    return(-3);
  }

  for (i = offset; i < 128 + offset; i++) {

    if (fread(buff, 1, 16, f) != 16) {
      fclose(f);
      return(-4);
    }

    opl->opl_gmtimbres[i].modulator_E862 = buff[8];
    opl->opl_gmtimbres[i].modulator_E862 <<= 8;
    opl->opl_gmtimbres[i].modulator_E862 |= buff[6];
    opl->opl_gmtimbres[i].modulator_E862 <<= 8;
    opl->opl_gmtimbres[i].modulator_E862 |= buff[4];
    opl->opl_gmtimbres[i].modulator_E862 <<= 8;
    opl->opl_gmtimbres[i].modulator_E862 |= buff[0];

    opl->opl_gmtimbres[i].carrier_E862 = buff[9];
    opl->opl_gmtimbres[i].carrier_E862 <<= 8;
    opl->opl_gmtimbres[i].carrier_E862 |= buff[7];
    opl->opl_gmtimbres[i].carrier_E862 <<= 8;
    opl->opl_gmtimbres[i].carrier_E862 |= buff[5];
    opl->opl_gmtimbres[i].carrier_E862 <<= 8;
    opl->opl_gmtimbres[i].carrier_E862 |= buff[1];

    opl->opl_gmtimbres[i].modulator_40 = buff[2];
    opl->opl_gmtimbres[i].carrier_40 = buff[3];

    opl->opl_gmtimbres[i].feedconn = buff[10];
    opl->opl_gmtimbres[i].finetune = buff[12];
    opl->opl_gmtimbres[i].notenum = 60;
    opl->opl_gmtimbres[i].noteoffset = 0;
  }

  fclose(f);
  return(0);
}
# 2737 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/opl.h"
int opl_loadbank_ibk(opl_t* opl, char const* file) {
  char *instruments = 0, *percussion = 0;
  int i, res;
  instruments = strdup(file);
  if (instruments == 0) return(-64);

  for (i = 0; instruments[i] != 0; i++) {
    if (instruments[i] == ',') {
      instruments[i] = 0;
      percussion = instruments + i + 1;
      break;
    }
  }

  res = opl_loadbank_internal(opl, instruments, 0);
  if ((res == 0) && (percussion != 0)) {
    res = opl_loadbank_internal(opl, percussion, 128);
  }
  free(instruments);

  return(res);
}

static void opl_load_op2_voice(opl_timbre_t* timbre, uint8_t const* buff) {

  timbre->modulator_E862 = buff[3];
  timbre->modulator_E862 <<= 8;
  timbre->modulator_E862 |= buff[2];
  timbre->modulator_E862 <<= 8;
  timbre->modulator_E862 |= buff[1];
  timbre->modulator_E862 <<= 8;
  timbre->modulator_E862 |= buff[0];

  timbre->carrier_E862 = buff[10];
  timbre->carrier_E862 <<= 8;
  timbre->carrier_E862 |= buff[9];
  timbre->carrier_E862 <<= 8;
  timbre->carrier_E862 |= buff[8];
  timbre->carrier_E862 <<= 8;
  timbre->carrier_E862 |= buff[7];

  timbre->modulator_40 = ( buff[5] & 0x3f ) | ( buff[4] & 0xc0 );
  timbre->carrier_40 = ( buff[12] & 0x3f ) | ( buff[11] & 0xc0 );

  timbre->feedconn = buff[6];
  timbre->finetune = 0;
  timbre->noteoffset = (int16_t)(buff[14] | ((uint16_t)buff[15] << 8));
}

int opl_loadbank_op2(opl_t* opl, void const* data, int size ) {
  if( size < 8 + 36 * 175 ) {
      return -3;
  }
  uint8_t const* buff = (uint8_t const*) data;
  int i;

  if ((buff[0] != '#') || (buff[1] != 'O') || (buff[2] != 'P') || (buff[3] != 'L') || (buff[4] != '_') || (buff[5] != 'I') || (buff[6] != 'I') || (buff[7] != '#')) {
    return(-3);
  }
  buff += 8;

  opl->is_op2 = 1;


  for (i = 0; i < 175; i++) {



    opl->op2_flags[i] = (enum op2_flags_t)( buff[0] | ((uint16_t)buff[1] << 8) );
    int finetune = buff[2];
    uint8_t fixednote = buff[3];
    buff += 4;


    opl_load_op2_voice(&opl->opl_gmtimbres[i], buff);
    opl->opl_gmtimbres[i].notenum = fixednote;
    buff += 16;


    opl_load_op2_voice(&opl->opl_gmtimbres_voice2[i], buff);
    opl->opl_gmtimbres_voice2[i].notenum = fixednote;
    opl->opl_gmtimbres_voice2[i].finetune += finetune - 128;
    buff += 16;
  }

  return(0);
}
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/opl/main.c" 2


int main() {
    opl_emu_bitfield(1,2,3);
    opl_emu_registers_effective_rate(1,2);
    return 0;
}
