#include <math.h>
#include <utility.c>
#include <utility.h>

extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
float kmSQR(float s)
{
  return s * s;
}

float kmDegreesToRadians(float degrees)
{
  return degrees * (3.14159265358979323846f / 180.0f);
}

float kmRadiansToDegrees(float radians)
{
  return radians * (180.0 / 3.14159265358979323846f);
}

float kmMin(float lhs, float rhs)
{
  return (lhs < rhs) ? (lhs) : (rhs);
}

float kmMax(float lhs, float rhs)
{
  return (lhs > rhs) ? (lhs) : (rhs);
}

unsigned char kmAlmostEqual(float lhs, float rhs)
{
  return ((lhs + 0.0001) > rhs) && ((lhs - 0.0001) < rhs);
}

float kmClamp(float x, float min, float max)
{
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}

float kmLerp(float x, float y, float t)
{
  return x + (t * (y - x));
}


extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
float kmSQR(float s)
{
  return s * s;
}

float kmDegreesToRadians(float degrees)
{
  return degrees * (3.14159265358979323846f / 180.0f);
}

float kmRadiansToDegrees(float radians)
{
  return radians * (180.0 / 3.14159265358979323846f);
}

float kmMin(float lhs, float rhs)
{
  return (lhs < rhs) ? (lhs) : (rhs);
}

float kmMax(float lhs, float rhs)
{
  return (lhs > rhs) ? (lhs) : (rhs);
}

unsigned char kmAlmostEqual(float lhs, float rhs)
{
  return ((lhs + 0.0001) > rhs) && ((lhs - 0.0001) < rhs);
}

float kmClamp(float x, float min, float max)
{
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}

float kmLerp(float x, float y, float t)
{
  return x + (t * (y - x));
}

