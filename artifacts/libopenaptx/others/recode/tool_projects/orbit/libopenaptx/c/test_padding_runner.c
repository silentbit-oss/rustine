#include "openaptx.h"
#include "tests/test_common.h"
#include <stdint.h>
#include <stdio.h>

void test_encode_padding() {
    struct aptx_context *ctx = aptx_init(0);

    uint8_t pcm[3] = {1, 2, 3};
    uint8_t out[8] = {0};
    size_t written = 0;

    size_t used = aptx_encode(ctx, pcm, sizeof(pcm), out, sizeof(out), &written);
    (void)used;  // Suppress unused variable warning
    ASSERT(written == 0, "Should not write on partial input");

    aptx_encode_finish(ctx, out, sizeof(out), &written);
    ASSERT(written > 0, "Finish should pad with silence");

    PASS("aptX encode finish with padding");
    aptx_finish(ctx);
}

int main(void) {
    printf("Running test_encode_padding...\n");
    test_encode_padding();
    printf("\nAll tests passed!\n");
    return 0;
}
