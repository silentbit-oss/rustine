// #include "openaptx.h"
// #include "test_common.h"
// #define NB_CHANNELS 2


// void test_dither_consistency() {
//     struct aptx_context *ctx1 = aptx_init(0);
//     struct aptx_context *ctx2 = aptx_init(0);

//     for (int i = 0; i < 10; i++) {
//         aptx_insert_sync(ctx1);
//         aptx_insert_sync(ctx2);
//     }

//     for (int ch = 0; ch < NB_CHANNELS; ch++) {
//         uint32_t dither1 = aptx_get_dither(ctx1, ch);
//         uint32_t dither2 = aptx_get_dither(ctx2, ch);
//         ASSERT(dither1 == dither2, "Dither state mismatch in channel");
//     }

//     ASSERT(aptx_get_sync_idx(ctx1) == aptx_get_sync_idx(ctx2), "Sync index mismatch");
//     ASSERT(aptx_get_hd(ctx1) == aptx_get_hd(ctx2), "HD state mismatch");

//     PASS("aptX dither consistency");
//     aptx_finish(ctx1);
//     aptx_finish(ctx2);
// }
