use crate::*;

pub fn clip_intp2(/* int32_t a, unsigned p */) {
	todo!();
}
pub fn clip(/* int32_t a, int32_t amin, int32_t amax */) {
	todo!();
}
pub fn sign_extend(/* int32_t val, unsigned bits */) {
	todo!();
}
pub fn rshift32(/* int32_t value, unsigned shift */) {
	todo!();
}
pub fn rshift64(/* int64_t value, unsigned shift */) {
	todo!();
}
pub fn aptx_bin_search(/* int32_t value, int32_t factor, const int32_t *intervals, int nb_intervals */) {
	todo!();
}
pub fn aptx_finish(/* struct aptx_context *ctx */) {
	todo!();
}
pub fn aptx_update_codeword_history(/* struct aptx_channel *channel */) {
	todo!();
}
pub fn aptx_qmf_filter_signal_push(/* struct aptx_filter_signal *signal, int32_t sample */) {
	todo!();
}
pub fn aptx_reconstructed_differences_update(/* struct aptx_prediction *prediction, int32_t reconstructed_difference, int order */) {
	todo!();
}
pub fn aptx_quantized_parity(/* const struct aptx_channel *channel */) {
	todo!();
}
pub fn helper_helper_aptx_decode_sync_1_1(/* struct aptx_context * const ctx, size_t * const dropped, size_t processed_step */) {
	todo!();
}
pub fn helper_helper_aptx_decode_sync_2_1(/* struct aptx_context * const ctx, size_t * const dropped, const size_t sample_size, size_t processed_step */) {
	todo!();
}
pub fn aptx_reset(/* struct aptx_context *ctx */) {
	todo!();
}
pub fn aptx_init(/* int hd */) {
	todo!();
}
pub fn aptx_check_parity(/* const struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx */) {
	todo!();
}
pub fn aptx_insert_sync(/* struct aptx_channel channels[NB_CHANNELS], uint8_t *sync_idx */) {
	todo!();
}
pub fn rshift64_clip24(/* int64_t value, unsigned shift */) {
	todo!();
}
pub fn aptx_invert_quantization(/* struct aptx_invert_quantize *invert_quantize, int32_t quantized_sample, int32_t dither, const struct aptx_tables *tables */) {
	todo!();
}
pub fn aptx_prediction_filtering(/* struct aptx_prediction *prediction, int32_t reconstructed_difference, int order */) {
	todo!();
}
pub fn aptx_process_subband(/* struct aptx_invert_quantize *invert_quantize, struct aptx_prediction *prediction, int32_t quantized_sample, int32_t dither, const struct aptx_tables *tables */) {
	todo!();
}
pub fn aptx_invert_quantize_and_prediction(/* struct aptx_channel *channel, int hd */) {
	todo!();
}
pub fn aptx_pack_codeword(/* const struct aptx_channel *channel */) {
	todo!();
}
pub fn aptxhd_pack_codeword(/* const struct aptx_channel *channel */) {
	todo!();
}
pub fn aptx_generate_dither(/* struct aptx_channel *channel */) {
	todo!();
}
pub fn rshift32_clip24(/* int32_t value, unsigned shift */) {
	todo!();
}
pub fn aptx_quantize_difference(/* struct aptx_quantize *quantize, int32_t sample_difference, int32_t dither, int32_t quantization_factor, const struct aptx_tables *tables */) {
	todo!();
}
pub fn aptx_qmf_convolution(/* const struct aptx_filter_signal *signal, const int32_t coeffs[16], unsigned shift */) {
	todo!();
}
pub fn aptx_qmf_polyphase_analysis(/* struct aptx_filter_signal signal[2], const int32_t coeffs[2][16], unsigned shift, const int32_t samples[2], int32_t *low_subband_output, int32_t *high_subband_output */) {
	todo!();
}
pub fn aptx_qmf_tree_analysis(/* struct aptx_QMF_analysis *qmf, const int32_t samples[4], int32_t subband_samples[4] */) {
	todo!();
}
pub fn aptx_encode_channel(/* struct aptx_channel *channel, const int32_t samples[4], int hd */) {
	todo!();
}
pub fn aptx_encode_samples(/* struct aptx_context *ctx, int32_t samples[NB_CHANNELS][4], uint8_t *output */) {
	todo!();
}
pub fn aptx_encode(/* struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written */) {
	todo!();
}
pub fn aptx_qmf_polyphase_synthesis(/* struct aptx_filter_signal signal[2], const int32_t coeffs[2][16], unsigned shift, int32_t low_subband_input, int32_t high_subband_input, int32_t samples[2] */) {
	todo!();
}
pub fn aptx_qmf_tree_synthesis(/* struct aptx_QMF_analysis *qmf, const int32_t subband_samples[4], int32_t samples[4] */) {
	todo!();
}
pub fn aptx_decode_channel(/* struct aptx_channel *channel, int32_t samples[4] */) {
	todo!();
}
pub fn aptx_unpack_codeword(/* struct aptx_channel *channel, uint16_t codeword */) {
	todo!();
}
pub fn aptxhd_unpack_codeword(/* struct aptx_channel *channel, uint32_t codeword */) {
	todo!();
}
pub fn aptx_decode_samples(/* struct aptx_context *ctx, const uint8_t *input, int32_t samples[NB_CHANNELS][4] */) {
	todo!();
}
pub fn aptx_decode(/* struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written */) {
	todo!();
}
pub fn aptx_decode_sync_finish(/* struct aptx_context *ctx */) {
	todo!();
}
pub fn aptx_reset_decode_sync(/* struct aptx_context *ctx */) {
	todo!();
}
pub fn aptx_encode_finish(/* struct aptx_context *ctx, unsigned char *output, size_t output_size, size_t *written */) {
	todo!();
}
pub fn helper_aptx_decode_sync_1(/* const size_t * const sample_size_ref, size_t * const processed_step_ref, size_t * const ipos_ref, size_t * const opos_ref, size_t * const i_ref, struct aptx_context * const ctx, const unsigned char * const input, unsigned char * const output, size_t output_size, int * const synced, size_t * const dropped, size_t written_step */) {
	todo!();
}
pub fn helper_aptx_decode_sync_2(/* size_t * const input_size_step_ref, size_t * const processed_step_ref, size_t * const ipos_ref, size_t * const opos_ref, struct aptx_context * const ctx, const unsigned char * const input, size_t input_size, unsigned char * const output, size_t output_size, int * const synced, size_t * const dropped, const size_t sample_size, size_t written_step */) {
	todo!();
}
pub fn aptx_decode_sync(/* struct aptx_context *ctx, const unsigned char *input, size_t input_size, unsigned char *output, size_t output_size, size_t *written, int *synced, size_t *dropped */) {
	todo!();
}
