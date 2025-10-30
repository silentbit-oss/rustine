use crate::*;

pub fn ZopfliGetDistExtraBits(/* int dist */) {
	todo!();
}
pub fn ZopfliGetDistExtraBitsValue(/* int dist */) {
	todo!();
}
pub fn ZopfliGetDistSymbol(/* int dist */) {
	todo!();
}
pub fn ZopfliGetLengthExtraBits(/* int l */) {
	todo!();
}
pub fn ZopfliGetLengthExtraBitsValue(/* int l */) {
	todo!();
}
pub fn ZopfliGetLengthSymbol(/* int l */) {
	todo!();
}
pub fn ZopfliGetLengthSymbolExtraBits(/* int s */) {
	todo!();
}
pub fn ZopfliGetDistSymbolExtraBits(/* int s */) {
	todo!();
}
pub fn AddBit(/* int bit, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn AddBits(/* unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn AddHuffmanBits(/* unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn PatchDistanceCodesForBuggyDecoders(/* unsigned *d_lengths */) {
	todo!();
}
pub fn GetFixedTree(/* unsigned *ll_lengths, unsigned *d_lengths */) {
	todo!();
}
pub fn AbsDiff(/* size_t x, size_t y */) {
	todo!();
}
pub fn helper_OptimizeHuffmanForRle_1(/* int * const i_ref, int * const k_ref, int * const stride_ref, size_t * const symbol_ref, unsigned int * const good_for_rle_idx_ref, int length, size_t * const counts, int * const good_for_rle */) {
	todo!();
}
pub fn helper_helper_EncodeTree_2_1(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, int size_only, unsigned char symbol */) {
	todo!();
}
pub fn helper_helper_OptimizeHuffmanForRle_2_1(/* int * const i_ref, int * const k_ref, int * const stride_ref, size_t * const sum_ref, size_t * const limit_ref, int length, size_t * const counts */) {
	todo!();
}
pub fn helper_helper_AddNonCompressedBlock_1_1(/* const unsigned char * const in, unsigned char ** const out, size_t * const outsize, size_t pos, size_t i */) {
	todo!();
}
pub fn helper_helper_helper_EncodeTree_2_2_1(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const rle, unsigned * const rle_bits, unsigned char symbol */) {
	todo!();
}
pub fn helper_helper_helper_EncodeTree_2_2_2(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only */) {
	todo!();
}
pub fn helper_helper_helper_EncodeTree_2_3_1(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only */) {
	todo!();
}
pub fn helper_helper_helper_EncodeTree_2_3_2(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only */) {
	todo!();
}
pub fn helper_EncodeTree_1(/* size_t * const i_ref, unsigned char * const bp, unsigned char ** const out, size_t * const outsize, unsigned * const rle, unsigned * const rle_bits, size_t rle_size, unsigned hlit, unsigned hdist, unsigned hclen, unsigned clcl[19], unsigned clsymbols[19], static const unsigned order[19] */) {
	todo!();
}
pub fn helper_helper_EncodeTree_2_3(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, int use_17, int use_18, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only */) {
	todo!();
}
pub fn helper_helper_EncodeTree_2_2(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned char * const symbol_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only */) {
	todo!();
}
pub fn helper_EncodeTree_2(/* size_t * const rle_size_ref, size_t * const rle_bits_size_ref, size_t * const i_ref, size_t * const j_ref, const unsigned * const ll_lengths, const unsigned * const d_lengths, int use_16, int use_17, int use_18, unsigned lld_total, unsigned * const rle, unsigned * const rle_bits, unsigned hlit2, size_t clcounts[19], int size_only */) {
	todo!();
}
pub fn EncodeTree(/* const unsigned *ll_lengths, const unsigned *d_lengths, int use_16, int use_17, int use_18, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn AddDynamicTree(/* const unsigned *ll_lengths, const unsigned *d_lengths, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn CalculateTreeSize(/* const unsigned *ll_lengths, const unsigned *d_lengths */) {
	todo!();
}
pub fn CalculateBlockSymbolSizeSmall(/* const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend */) {
	todo!();
}
pub fn CalculateBlockSymbolSizeGivenCounts(/* const size_t *ll_counts, const size_t *d_counts, const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend */) {
	todo!();
}
pub fn CalculateBlockSymbolSize(/* const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend */) {
	todo!();
}
pub fn helper_OptimizeHuffmanForRle_2(/* int * const i_ref, int * const k_ref, int * const stride_ref, size_t * const sum_ref, size_t * const limit_ref, int length, size_t * const counts, int * const good_for_rle, unsigned int good_for_rle_idx */) {
	todo!();
}
pub fn OptimizeHuffmanForRle(/* int length, size_t *counts */) {
	todo!();
}
pub fn TryOptimizeHuffmanForRle(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, const size_t *ll_counts, const size_t *d_counts, unsigned *ll_lengths, unsigned *d_lengths */) {
	todo!();
}
pub fn GetDynamicLengths(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, unsigned *ll_lengths, unsigned *d_lengths */) {
	todo!();
}
pub fn ZopfliCalculateBlockSize(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype */) {
	todo!();
}
pub fn ZopfliCalculateBlockSizeAutoType(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend */) {
	todo!();
}
pub fn helper_ZopfliDeflatePart_2(/* size_t * const i_ref, unsigned int * const splitpoints_idx_ref, double * const totalcost_ref, const ZopfliOptions * const options, const unsigned char * const in, size_t instart, size_t inend, size_t * const splitpoints_uncompressed, size_t npoints, size_t * const splitpoints, ZopfliLZ77Store lz77 */) {
	todo!();
}
pub fn helper_AddNonCompressedBlock_1(/* size_t * const pos_ref, int final, const unsigned char * const in, size_t inend, unsigned char * const bp, unsigned char ** const out, size_t * const outsize */) {
	todo!();
}
pub fn AddNonCompressedBlock(/* const ZopfliOptions *options, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn AddLZ77Data(/* const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, const unsigned *ll_symbols, const unsigned *ll_lengths, const unsigned *d_symbols, const unsigned *d_lengths, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn helper_AddLZ77Block_1(/* const ZopfliOptions * const options, int btype, const ZopfliLZ77Store * const lz77, size_t lstart, size_t lend, unsigned char * const bp, unsigned char ** const out, size_t * const outsize, unsigned ll_lengths[288], unsigned d_lengths[32] */) {
	todo!();
}
pub fn AddLZ77Block(/* const ZopfliOptions *options, int btype, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn helper_AddLZ77BlockAutoType_1(/* double * const fixedcost_ref, const ZopfliOptions * const options, const ZopfliLZ77Store * const lz77, size_t lstart, size_t lend, ZopfliLZ77Store fixedstore */) {
	todo!();
}
pub fn AddLZ77BlockAutoType(/* const ZopfliOptions *options, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn helper_ZopfliDeflatePart_1(/* const ZopfliOptions * const options, int btype, int final, const unsigned char * const in, size_t instart, size_t inend, unsigned char * const bp, unsigned char ** const out, size_t * const outsize */) {
	todo!();
}
pub fn helper_ZopfliDeflatePart_3(/* size_t * const i_ref, size_t * const npoints_ref, unsigned int * const splitpoints_idx_ref, const ZopfliOptions * const options, size_t * const splitpoints, double totalcost, ZopfliLZ77Store lz77 */) {
	todo!();
}
pub fn ZopfliDeflatePart(/* const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
pub fn ZopfliDeflate(/* const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize */) {
	todo!();
}
