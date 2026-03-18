#include "openaptx.h"
#include "test_common.h"
#include <stdint.h>

#define NB_SAMPLES 8
#define NB_CHANNELS 2

void test_roundtrip(int hd) {
    struct aptx_context *enc = aptx_init(hd);
    struct aptx_context *dec = aptx_init(hd);

    // Need enough samples to exceed latency (90 samples = 23 frames of 4 samples each)
    // Use 32 frames = 128 samples
    #define TOTAL_SAMPLES 128
    int16_t pcm_in[NB_CHANNELS * TOTAL_SAMPLES] = {0};
    for (int i = 0; i < NB_CHANNELS * TOTAL_SAMPLES; ++i)
        pcm_in[i] = (i * 256) & 0xFFFF;

    uint8_t encoded[512] = {0};
    size_t written = 0;
    size_t written_finish = 0;

    // Encode the samples
    aptx_encode(enc, (unsigned char*)pcm_in, sizeof(pcm_in), encoded, sizeof(encoded), &written);
    printf("encoded bytes: %zu\n", written);

    // Flush remaining samples due to latency
    aptx_encode_finish(enc, encoded + written, sizeof(encoded) - written, &written_finish);
    printf("encoded finish bytes: %zu\n", written_finish);
    written += written_finish;

    // Decode
    int16_t pcm_out[NB_CHANNELS * (TOTAL_SAMPLES + 100)] = {0};
    size_t decoded = 0;
    aptx_decode(dec, encoded, written, (unsigned char*)pcm_out, sizeof(pcm_out), &decoded);
    printf("decoded bytes: %zu\n", decoded);

    ASSERT(decoded > 0, "PCM decoded length should be > 0");
    PASS(hd ? "aptX HD roundtrip" : "aptX Classic roundtrip");

    aptx_finish(enc);
    aptx_finish(dec);
}


void test_roundtrip_classic() { test_roundtrip(0); }
void test_roundtrip_hd() { test_roundtrip(1); }

int main() {
    printf("Running roundtrip tests...\n");
    test_roundtrip_classic();
    test_roundtrip_hd();
    printf("\nAll tests passed!\n");
    return 0;
}
