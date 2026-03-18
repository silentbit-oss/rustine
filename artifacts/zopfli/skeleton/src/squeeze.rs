use crate::*;

pub fn zopfli_min(/* size_t a, size_t b */) {
	todo!();
}
pub fn TraceBackwards(/* size_t size, const unsigned short *length_array, unsigned short **path, size_t *pathsize */) {
	todo!();
}
pub fn helper_helper_GetBestLengths_1_2(/* size_t * const k_ref, size_t * const j_ref, void * const costcontext, unsigned short * const length_array, float * const costs, unsigned short sublen[259], double mincostaddcostj */) {
	todo!();
}
pub fn InitStats(/* SymbolStats *stats */) {
	todo!();
}
pub fn CopyStats(/* SymbolStats *source, SymbolStats *dest */) {
	todo!();
}
pub fn AddWeighedStatFreqs(/* const SymbolStats *stats1, double w1, const SymbolStats *stats2, double w2, SymbolStats *result */) {
	todo!();
}
pub fn InitRanState(/* RanState *state */) {
	todo!();
}
pub fn Ran(/* RanState *state */) {
	todo!();
}
pub fn ClearStatFreqs(/* SymbolStats *stats */) {
	todo!();
}
pub fn GetCostModelMinCost(/* CostModelFun *costmodel, void *costcontext */) {
	todo!();
}
pub fn CalculateStatistics(/* SymbolStats *stats */) {
	todo!();
}
pub fn RandomizeFreqs(/* RanState *state, size_t *freqs, int n */) {
	todo!();
}
pub fn RandomizeStatFreqs(/* RanState *state, SymbolStats *stats */) {
	todo!();
}
pub fn GetCostStat(/* unsigned litlen, unsigned dist, void *context */) {
	todo!();
}
pub fn helper_helper_GetBestLengths_1_1(/* size_t * const i_ref, size_t * const k_ref, size_t * const j_ref, const unsigned char * const in, size_t inend, void * const costcontext, unsigned short * const length_array, ZopfliHash * const h, float * const costs */) {
	todo!();
}
pub fn helper_GetBestLengths_1(/* size_t * const i_ref, size_t * const k_ref, size_t * const kend_ref, double * const mincostaddcostj_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t instart, size_t inend, void * const costcontext, unsigned short * const length_array, ZopfliHash * const h, float * const costs, unsigned short leng, unsigned short dist, unsigned short sublen[259], double mincost */) {
	todo!();
}
pub fn GetBestLengths(/* ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, CostModelFun *costmodel, void *costcontext, unsigned short *length_array, ZopfliHash *h, float *costs */) {
	todo!();
}
pub fn helper_FollowPath_1(/* size_t * const j_ref, size_t * const pos_ref, size_t * const total_length_test_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t inend, unsigned short * const path, ZopfliLZ77Store * const store, ZopfliHash * const h, size_t i */) {
	todo!();
}
pub fn FollowPath(/* ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short *path, size_t pathsize, ZopfliLZ77Store *store, ZopfliHash *h */) {
	todo!();
}
pub fn LZ77OptimalRun(/* ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short **path, size_t *pathsize, unsigned short *length_array, CostModelFun *costmodel, void *costcontext, ZopfliLZ77Store *store, ZopfliHash *h, float *costs */) {
	todo!();
}
pub fn GetStatistics(/* const ZopfliLZ77Store *store, SymbolStats *stats */) {
	todo!();
}
pub fn helper_ZopfliLZ77Optimal_1(/* double * const cost_ref, double * const bestcost_ref, double * const lastcost_ref, int * const lastrandomstep_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t instart, size_t inend, ZopfliLZ77Store * const store, unsigned short * const length_array, unsigned short * const path, size_t pathsize, ZopfliLZ77Store currentstore, ZopfliHash * const h, SymbolStats stats, SymbolStats beststats, SymbolStats laststats, int i, float * const costs, RanState ran_state */) {
	todo!();
}
pub fn ZopfliLZ77Optimal(/* ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, int numiterations, ZopfliLZ77Store *store */) {
	todo!();
}
pub fn GetCostFixed(/* unsigned litlen, unsigned dist, void *unused */) {
	todo!();
}
pub fn ZopfliLZ77OptimalFixed(/* ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store */) {
	todo!();
}
