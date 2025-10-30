use crate::*;

pub fn BZ2_bzlibVersion(/* void */) {
	todo!();
}
pub fn bz_config_ok(/* void */) {
	todo!();
}
pub fn default_bzfree(/* void *opaque, void *addr */) {
	todo!();
}
pub fn default_bzalloc(/* void *opaque, Int32 items, Int32 size */) {
	todo!();
}
pub fn BZ2_bzDecompressInit(/* bz_stream *strm, int verbosity, int small */) {
	todo!();
}
pub fn BZ2_bzReadOpen(/* int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused */) {
	todo!();
}
pub fn init_RL(/* EState *s */) {
	todo!();
}
pub fn prepare_new_block(/* EState *s */) {
	todo!();
}
pub fn BZ2_bzCompressInit(/* bz_stream *strm, int blockSize100k, int verbosity, int workFactor */) {
	todo!();
}
pub fn BZ2_bzWriteOpen(/* int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor */) {
	todo!();
}
pub fn bzopen_or_bzdopen(/* const char *path, int fd, const char *mode, int open_mode */) {
	todo!();
}
pub fn BZ2_bzopen(/* const char *path, const char *mode */) {
	todo!();
}
pub fn BZ2_bzdopen(/* int fd, const char *mode */) {
	todo!();
}
pub fn BZ2_bzflush(/* BZFILE *b */) {
	todo!();
}
pub fn BZ2_bz__AssertH__fail(/* int errcode */) {
	todo!();
}
pub fn BZ2_indexIntoF(/* Int32 indx, Int32 *cftab */) {
	todo!();
}
pub fn isempty_RL(/* EState *s */) {
	todo!();
}
pub fn myfeof(/* FILE *f */) {
	todo!();
}
pub fn BZ2_bzCompressEnd(/* bz_stream *strm */) {
	todo!();
}
pub fn BZ2_bzDecompressEnd(/* bz_stream *strm */) {
	todo!();
}
pub fn BZ2_bzReadGetUnused(/* int *bzerror, BZFILE *b, void **unused, int *nUnused */) {
	todo!();
}
pub fn add_pair_to_block(/* EState *s */) {
	todo!();
}
pub fn helper_copy_input_until_stop_2(/* EState **s_ptr, Bool *progress_in_ptr */) {
	todo!();
}
pub fn helper_copy_input_until_stop_1(/* EState **s_ptr, Bool *progress_in_ptr */) {
	todo!();
}
pub fn copy_input_until_stop(/* EState *s */) {
	todo!();
}
pub fn flush_RL(/* EState *s */) {
	todo!();
}
pub fn copy_output_until_stop(/* EState *s */) {
	todo!();
}
pub fn handle_compress(/* bz_stream *strm */) {
	todo!();
}
pub fn BZ2_bzCompress(/* bz_stream *strm, int action */) {
	todo!();
}
pub fn helper_helper_BZ2_bzWriteClose64_1_1(/* int **bzerror_ptr, Int32 *n_ptr, Int32 *n2_ptr, Int32 *ret_ptr, bzFile **bzf_ptr */) {
	todo!();
}
pub fn helper_BZ2_bzWriteClose64_1(/* int **bzerror_ptr, Int32 *n_ptr, Int32 *n2_ptr, Int32 *ret_ptr, bzFile **bzf_ptr */) {
	todo!();
}
pub fn BZ2_bzWriteClose64(/* int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32, unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32 */) {
	todo!();
}
pub fn BZ2_bzWriteClose(/* int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in, unsigned int *nbytes_out */) {
	todo!();
}
pub fn helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(/* UInt32 *c_calculatedBlockCRC_ptr, UChar *c_state_out_ch_ptr, Int32 *c_state_out_len_ptr, char **cs_next_out_ptr, unsigned int *cs_next_out_idx_ptr, unsigned int *cs_avail_out_ptr */) {
	todo!();
}
pub fn helper_helper_unRLE_obuf_to_output_FAST_1_1(/* UChar *k1_ptr, UInt32 *c_calculatedBlockCRC_ptr, UChar *c_state_out_ch_ptr, Int32 *c_state_out_len_ptr, Int32 *c_nblock_used_ptr, Int32 *c_k0_ptr, UInt32 **c_tt_ptr, UInt32 *c_tPos_ptr, char **cs_next_out_ptr, unsigned int *cs_next_out_idx_ptr, unsigned int *cs_avail_out_ptr, Int32 *ro_blockSize100k_ptr, Int32 *s_save_nblockPP_ptr */) {
	todo!();
}
pub fn helper_unRLE_obuf_to_output_FAST_1(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn helper_helper_unRLE_obuf_to_output_FAST_2_1(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn helper_unRLE_obuf_to_output_FAST_2(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn unRLE_obuf_to_output_FAST(/* DState *s */) {
	todo!();
}
pub fn helper_helper_unRLE_obuf_to_output_SMALL_1_1(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn helper_unRLE_obuf_to_output_SMALL_1(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn helper_helper_unRLE_obuf_to_output_SMALL_2_1(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn helper_unRLE_obuf_to_output_SMALL_2(/* DState **s_ptr, UChar *k1_ptr */) {
	todo!();
}
pub fn unRLE_obuf_to_output_SMALL(/* DState *s */) {
	todo!();
}
pub fn helper_BZ2_bzDecompress_1(/* Bool *corrupt_ptr, DState **s_ptr */) {
	todo!();
}
pub fn BZ2_bzDecompress(/* bz_stream *strm */) {
	todo!();
}
pub fn helper_BZ2_bzRead_1(/* int **bzerror_ptr, int *len_ptr, Int32 *n_ptr, Int32 *ret_ptr, bzFile **bzf_ptr */) {
	todo!();
}
pub fn BZ2_bzRead(/* int *bzerror, BZFILE *b, void *buf, int len */) {
	todo!();
}
pub fn BZ2_bzread(/* BZFILE *b, void *buf, int len */) {
	todo!();
}
pub fn helper_BZ2_bzWrite_1(/* int **bzerror_ptr, Int32 *n_ptr, Int32 *n2_ptr, Int32 *ret_ptr, bzFile **bzf_ptr */) {
	todo!();
}
pub fn BZ2_bzWrite(/* int *bzerror, BZFILE *b, void *buf, int len */) {
	todo!();
}
pub fn BZ2_bzwrite(/* BZFILE *b, void *buf, int len */) {
	todo!();
}
pub fn BZ2_bzerror(/* BZFILE *b, int *errnum */) {
	todo!();
}
pub fn BZ2_bzReadClose(/* int *bzerror, BZFILE *b */) {
	todo!();
}
pub fn BZ2_bzclose(/* BZFILE *b */) {
	todo!();
}
pub fn BZ2_bzBuffToBuffCompress(/* char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int blockSize100k, int verbosity, int workFactor */) {
	todo!();
}
pub fn BZ2_bzBuffToBuffDecompress(/* char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int small, int verbosity */) {
	todo!();
}
