use crate::*;

pub fn ZopfliVerifyLenDist(/* const unsigned char *data, size_t datasize, size_t pos, unsigned short dist, unsigned short length */) {
	todo!();
}
pub fn CeilDiv(/* size_t a, size_t b */) {
	todo!();
}
pub fn GetLengthScore(/* int length, int distance */) {
	todo!();
}
pub fn GetMatch(/* const unsigned char *scan, const unsigned char *match, const unsigned char *end, const unsigned char *safe_end */) {
	todo!();
}
pub fn helper_helper_helper_ZopfliFindLongestMatch_1_1_1(/* unsigned short * const bestdist_ref, unsigned short * const bestlength_ref, size_t limit, unsigned short * const sublen, unsigned dist, unsigned short currentlength */) {
	todo!();
}
pub fn ZopfliInitLZ77Store(/* const unsigned char *data, ZopfliLZ77Store *store */) {
	todo!();
}
pub fn ZopfliCleanLZ77Store(/* ZopfliLZ77Store *store */) {
	todo!();
}
pub fn ZopfliLZ77GetByteRange(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend */) {
	todo!();
}
pub fn ZopfliLZ77GetHistogramAt(/* const ZopfliLZ77Store *lz77, size_t lpos, size_t *ll_counts, size_t *d_counts */) {
	todo!();
}
pub fn helper_ZopfliStoreLitLenDist_1(/* size_t * const i_ref, ZopfliLZ77Store * const store, size_t origsize */) {
	todo!();
}
pub fn helper_ZopfliStoreLitLenDist_2(/* size_t * const i_ref, ZopfliLZ77Store * const store, size_t origsize */) {
	todo!();
}
pub fn helper_ZopfliStoreLitLenDist_3(/* unsigned short * const length_ref, size_t * const llstart_ref, ZopfliLZ77Store * const store, size_t origsize */) {
	todo!();
}
pub fn ZopfliLZ77GetHistogram(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t *ll_counts, size_t *d_counts */) {
	todo!();
}
pub fn helper_ZopfliStoreLitLenDist_4(/* unsigned short * const length_ref, unsigned short * const dist_ref, size_t * const llstart_ref, size_t * const dstart_ref, ZopfliLZ77Store * const store, size_t origsize */) {
	todo!();
}
pub fn ZopfliStoreLitLenDist(/* unsigned short length, unsigned short dist, size_t pos, ZopfliLZ77Store *store */) {
	todo!();
}
pub fn ZopfliAppendLZ77Store(/* const ZopfliLZ77Store *store, ZopfliLZ77Store *target */) {
	todo!();
}
pub fn ZopfliCleanBlockState(/* ZopfliBlockState *s */) {
	todo!();
}
pub fn ZopfliCopyLZ77Store(/* const ZopfliLZ77Store *source, ZopfliLZ77Store *dest */) {
	todo!();
}
pub fn TryGetFromLongestMatchCache(/* ZopfliBlockState *s, size_t pos, size_t *limit, unsigned short *sublen, unsigned short *distance, unsigned short *length */) {
	todo!();
}
pub fn helper_helper_helper_ZopfliFindLongestMatch_1_1_2(/* unsigned int * const scan_idx_ref, unsigned int * const match_idx_ref, unsigned short * const currentlength_ref, const ZopfliHash * const h, const unsigned char * const array, size_t pos, size_t limit, const unsigned char * const scan, const unsigned char * const match, const unsigned char * const arrayend, const unsigned char * const arrayend_safe, unsigned dist */) {
	todo!();
}
pub fn helper_helper_ZopfliFindLongestMatch_1_1(/* unsigned short * const bestdist_ref, unsigned short * const bestlength_ref, unsigned int * const scan_idx_ref, unsigned int * const match_idx_ref, unsigned short * const currentlength_ref, const ZopfliHash * const h, const unsigned char * const array, size_t pos, size_t size, size_t limit, unsigned short * const sublen, const unsigned char * const scan, const unsigned char * const match, const unsigned char * const arrayend, const unsigned char * const arrayend_safe, unsigned dist */) {
	todo!();
}
pub fn helper_ZopfliFindLongestMatch_1(/* unsigned short * const p_ref, unsigned short * const pp_ref, unsigned short * const bestdist_ref, unsigned short * const bestlength_ref, unsigned int * const scan_idx_ref, unsigned int * const match_idx_ref, int * const chain_counter_ref, unsigned * const dist_ref, unsigned int * const hhead_idx_ref, unsigned int * const hprev_idx_ref, unsigned int * const hhashval_idx_ref, int * const hval_ref, const ZopfliHash * const h, const unsigned char * const array, size_t pos, size_t size, size_t limit, unsigned short * const sublen, unsigned short hpos, const unsigned char * const scan, const unsigned char * const match, const unsigned char * const arrayend, const unsigned char * const arrayend_safe, int * const hhead, unsigned short * const hprev, int * const hhashval */) {
	todo!();
}
pub fn StoreInLongestMatchCache(/* ZopfliBlockState *s, size_t pos, size_t limit, const unsigned short *sublen, unsigned short distance, unsigned short length */) {
	todo!();
}
pub fn ZopfliFindLongestMatch(/* ZopfliBlockState *s, const ZopfliHash *h, const unsigned char *array, size_t pos, size_t size, size_t limit, unsigned short *sublen, unsigned short *distance, unsigned short *length */) {
	todo!();
}
pub fn helper_helper_helper_ZopfliLZ77Greedy_1_1_1(/* unsigned * const prev_length_ref, unsigned * const prev_match_ref, int * const match_available_ref, const unsigned char * const in, ZopfliLZ77Store * const store, size_t i, unsigned short leng, unsigned short dist, int lengthscore */) {
	todo!();
}
pub fn helper_helper_helper_ZopfliLZ77Greedy_1_1_2(/* size_t * const i_ref, size_t * const j_ref, unsigned short * const leng_ref, unsigned short * const dist_ref, int * const lengthscore_ref, const unsigned char * const in, size_t inend, ZopfliLZ77Store * const store, ZopfliHash * const h, int prevlengthscore, unsigned prev_length, unsigned prev_match */) {
	todo!();
}
pub fn helper_helper_ZopfliLZ77Greedy_1_1(/* size_t * const i_ref, size_t * const j_ref, unsigned short * const leng_ref, unsigned short * const dist_ref, int * const lengthscore_ref, unsigned * const prev_length_ref, unsigned * const prev_match_ref, int * const match_available_ref, const unsigned char * const in, size_t inend, ZopfliLZ77Store * const store, ZopfliHash * const h, int prevlengthscore */) {
	todo!();
}
pub fn helper_ZopfliLZ77Greedy_1(/* size_t * const i_ref, size_t * const j_ref, unsigned short * const leng_ref, unsigned short * const dist_ref, int * const lengthscore_ref, unsigned * const prev_length_ref, unsigned * const prev_match_ref, int * const prevlengthscore_ref, int * const match_available_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t inend, ZopfliLZ77Store * const store, ZopfliHash * const h, unsigned short dummysublen[259] */) {
	todo!();
}
pub fn ZopfliLZ77Greedy(/* ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store, ZopfliHash *h */) {
	todo!();
}
pub fn ZopfliInitBlockState(/* const ZopfliOptions *options, size_t blockstart, size_t blockend, int add_lmc, ZopfliBlockState *s */) {
	todo!();
}
