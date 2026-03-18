#include <stdio.h>
#include <string.h>
#include "openaptx.h"

void assert_true(int condition, const char *test_name) {
    if (condition) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }
}

void test_aptx_encode_decode_various() {
    struct aptx_context *ctx_enc = aptx_init(0);
    struct aptx_context *ctx_dec = aptx_init(0);

    unsigned char input[24] = {0};
    unsigned char encoded[10];
    unsigned char decoded[24];
    size_t written_enc, written_dec;

    size_t processed = aptx_encode(ctx_enc, input, 0, encoded, sizeof(encoded), &written_enc);
    assert_true(processed == 0, "Encoding empty input returns 0");

    for (int i = 0; i < 24; i++) input[i] = 255;
    processed = aptx_encode(ctx_enc, input, sizeof(input), encoded, sizeof(encoded), &written_enc);
    assert_true(processed == sizeof(input), "Encoding max value input");

    int pass = 1;
    for (int i = 0; i < 5; i++) {
        processed = aptx_encode(ctx_enc, input, sizeof(input), encoded, sizeof(encoded), &written_enc);
        if (processed != sizeof(input)) pass = 0;
        processed = aptx_decode(ctx_dec, encoded, written_enc, decoded, sizeof(decoded), &written_dec);
        if (processed != written_enc) pass = 0;
    }
    assert_true(pass, "Encode-decode loop multiple iterations");

    aptx_finish(ctx_enc);
    aptx_finish(ctx_dec);
}

void test_aptx_hd_mode() {
    struct aptx_context *ctx_enc = aptx_init(1);  
    struct aptx_context *ctx_dec = aptx_init(1);

    unsigned char input[24];
    unsigned char encoded[10];
    unsigned char decoded[24];
    size_t written_enc, written_dec;

    for (int i = 0; i < 24; i++) input[i] = i;

    size_t processed_enc = aptx_encode(ctx_enc, input, sizeof(input), encoded, sizeof(encoded), &written_enc);
    size_t processed_dec = aptx_decode(ctx_dec, encoded, written_enc, decoded, sizeof(decoded), &written_dec);

    assert_true(processed_enc == sizeof(input), "HD mode encoding processed size");
    assert_true(processed_dec == written_enc, "HD mode decoding processed size");

    aptx_finish(ctx_enc);
    aptx_finish(ctx_dec);
}

void test_aptx_decode_sync() {
    struct aptx_context *ctx_dec = aptx_init(0);

    unsigned char input[10] = {0};
    unsigned char output[24] = {0};
    size_t written = 0;
    int synced = 0;
    size_t dropped = 0;

    size_t processed = aptx_decode_sync(ctx_dec,
                                       input,
                                       sizeof(input),
                                       output,
                                       sizeof(output),
                                       &written,
                                       &synced,
                                       &dropped);

    assert_true(processed == sizeof(input), "decode_sync processed size");
    assert_true(synced == 1, "decode_sync synced flag");

    printf("[INFO] decode_sync dropped bytes: %zu\n", dropped);

    size_t dropped_finish = aptx_decode_sync_finish(ctx_dec);
    printf("[INFO] decode_sync_finish dropped bytes: %zu\n", dropped_finish);

    aptx_finish(ctx_dec);
}

void test_aptx_invalid_inputs() {
    struct aptx_context *ctx = aptx_init(0);
    unsigned char out[10];
    size_t written;


    size_t processed = aptx_encode(ctx, NULL, 0, out, sizeof(out), &written);
    assert_true(processed == 0, "Encode with NULL input length 0 returns 0");

    unsigned char input[24] = {0};
    processed = aptx_encode(ctx, input, sizeof(input), out, 1, &written);
    assert_true(processed == 0 || written == 0, "Encode with tiny output buffer fails or writes 0");

    aptx_finish(ctx);
}

int main() {
    printf("=== Running various inputs test ===\n");
    test_aptx_encode_decode_various();

    printf("\n=== Running HD mode test ===\n");
    test_aptx_hd_mode();

    printf("\n=== Running decode sync test ===\n");
    test_aptx_decode_sync();

    printf("\n=== Running invalid inputs test ===\n");
    test_aptx_invalid_inputs();

    return 0;
}
