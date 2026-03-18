#include "openaptx.h"
#include "test_common.h"
#include <stdint.h>

#define NB_SAMPLES 8  
#define NB_CHANNELS 2

void test_roundtrip(int hd) {
    struct aptx_context *enc = aptx_init(hd);
    struct aptx_context *dec = aptx_init(hd);

    int16_t pcm_in[NB_CHANNELS * NB_SAMPLES] = {0};
    for (int i = 0; i < NB_CHANNELS * NB_SAMPLES; ++i)
        pcm_in[i] = i * 256;  

    uint8_t encoded[64] = {0};  
    size_t written = 0;
    aptx_encode(enc, pcm_in, sizeof(pcm_in), encoded, sizeof(encoded), &written);
    printf("encoded bytes: %zu\n", written);

    int16_t pcm_out[NB_CHANNELS * NB_SAMPLES] = {0};
    size_t decoded = 0;
    aptx_decode(dec, encoded, written, pcm_out, sizeof(pcm_out), &decoded);
    printf("decoded samples: %zu\n", decoded);
    
    ASSERT(decoded > 0, "PCM decoded length should be > 0");
    PASS(hd ? "aptX HD roundtrip" : "aptX Classic roundtrip");

    aptx_finish(enc);
    aptx_finish(dec);
}


void test_roundtrip_classic() { test_roundtrip(0); }
void test_roundtrip_hd() { test_roundtrip(1); }
