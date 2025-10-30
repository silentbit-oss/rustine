typedef struct BrotliTransforms
{
  uint16_t prefix_suffix_size;
  const uint8_t *prefix_suffix;
  const uint16_t *prefix_suffix_map;
  uint32_t num_transforms;
  const uint8_t *transforms;
  const uint8_t *params;
  int16_t cutOffTransforms[BROTLI_TRANSFORM_OMIT_LAST_9 + 1];
} BrotliTransforms
/*** DEPENDENCIES:
***/


