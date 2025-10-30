extern float _gamma
/*** DEPENDENCIES:
***/


const float INF = 1E20
/*** DEPENDENCIES:
***/


static const float SEALEVEL = 0.5
/*** DEPENDENCIES:
***/


static const float DEFAULT_STRENGTH = 0.6
/*** DEPENDENCIES:
***/


static float _occlusion_scale = 1.0f
/*** DEPENDENCIES:
***/


static const int8_t gradients2D[] = {5, 2, 2, 5, -5, 2, -2, 5, 5, -2, 2, -5, -5, -2, -2, -5}
/*** DEPENDENCIES:
***/


static const signed char gradients3D[] = {-11, 4, 4, -4, 11, 4, -4, 4, 11, 11, 4, 4, 4, 11, 4, 4, 4, 11, -11, -4, 4, -4, -11, 4, -4, -4, 11, 11, -4, 4, 4, -11, 4, 4, -4, 11, -11, 4, -4, -4, 11, -4, -4, 4, -11, 11, 4, -4, 4, 11, -4, 4, 4, -11, -11, -4, -4, -4, -11, -4, -4, -4, -11, 11, -4, -4, 4, -11, -4, 4, -4, -11}
/*** DEPENDENCIES:
***/


static const signed char gradients4D[] = {3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1, 3, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, 3, 1, 1, -1, 1, 3, 1, -1, 1, 1, 3, -1, 1, 1, 1, -3, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, 3, 1, -1, -1, 1, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3}
/*** DEPENDENCIES:
***/


extern const kmVec3 KM_VEC3_NEG_Z
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec3 KM_VEC3_POS_Z
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec3 KM_VEC3_POS_Y
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec3 KM_VEC3_NEG_Y
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec3 KM_VEC3_NEG_X
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec3 KM_VEC3_POS_X
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec3 KM_VEC3_ZERO
/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


extern const kmVec2 KM_VEC2_POS_Y
/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


extern const kmVec2 KM_VEC2_NEG_Y
/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


extern const kmVec2 KM_VEC2_NEG_X
/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


extern const kmVec2 KM_VEC2_POS_X
/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


extern const kmVec2 KM_VEC2_ZERO
/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


