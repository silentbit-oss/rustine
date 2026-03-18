#include "openaptx.h"
#include "test_common.h"
#include <stdint.h>

void test_encode_padding() {
    struct aptx_context *ctx = aptx_init(0);

    uint8_t pcm[3] = {1, 2, 3};  
    uint8_t out[8] = {0};
    size_t written = 0;

    size_t used = aptx_encode(ctx, pcm, sizeof(pcm), out, sizeof(out), &written);
    ASSERT(written == 0, "Should not write on partial input");

    aptx_encode_finish(ctx, out, sizeof(out), &written);
    ASSERT(written > 0, "Finish should pad with silence");

    PASS("aptX encode finish with padding");
    aptx_finish(ctx);
}
