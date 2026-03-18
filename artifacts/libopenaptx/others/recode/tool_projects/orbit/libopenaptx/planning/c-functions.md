# C Functions and Methods to Translate

This file lists all C functions and methods that will be translated to Rust.
Format: <c-file-path>:<c-item-name>

## Source Files

### openaptx.c
openaptx.c:clip_intp2
openaptx.c:clip
openaptx.c:sign_extend
openaptx.c:aptx_update_codeword_history
openaptx.c:aptx_generate_dither
openaptx.c:aptx_qmf_filter_signal_push
openaptx.c:aptx_qmf_convolution
openaptx.c:aptx_qmf_polyphase_analysis
openaptx.c:aptx_qmf_tree_analysis
openaptx.c:aptx_qmf_polyphase_synthesis
openaptx.c:aptx_qmf_tree_synthesis
openaptx.c:aptx_bin_search
openaptx.c:aptx_quantize_difference
openaptx.c:aptx_encode_channel
openaptx.c:aptx_decode_channel
openaptx.c:aptx_invert_quantization
openaptx.c:aptx_prediction_filtering
openaptx.c:aptx_process_subband
openaptx.c:aptx_invert_quantize_and_prediction
openaptx.c:aptx_quantized_parity
openaptx.c:aptx_check_parity
openaptx.c:aptx_insert_sync
openaptx.c:aptx_pack_codeword
openaptx.c:aptxhd_pack_codeword
openaptx.c:aptx_unpack_codeword
openaptx.c:aptxhd_unpack_codeword
openaptx.c:aptx_encode_samples
openaptx.c:aptx_decode_samples
openaptx.c:aptx_reset_decode_sync
openaptx.c:aptx_reset
openaptx.c:aptx_finish
openaptx.c:aptx_encode
openaptx.c:aptx_encode_finish
openaptx.c:aptx_decode
openaptx.c:aptx_decode_sync
openaptx.c:aptx_decode_sync_finish

### openaptxenc.c
openaptxenc.c:main

### openaptxdec.c
openaptxdec.c:main

## Test Files

### test.c
test.c:assert_true
test.c:test_aptx_encode_decode_various
test.c:test_aptx_hd_mode
test.c:test_aptx_decode_sync
test.c:test_aptx_invalid_inputs
test.c:main

### tests/test_padding.c
tests/test_padding.c:test_encode_padding

### tests/test_roundtrip.c
tests/test_roundtrip.c:test_roundtrip
tests/test_roundtrip.c:test_roundtrip_classic
tests/test_roundtrip.c:test_roundtrip_hd

### tests/test_dither.c
(No functions to translate - file appears to be empty or contains only includes)

### tests/test_sync.c
(No functions to translate - file appears to be empty or contains only includes)
