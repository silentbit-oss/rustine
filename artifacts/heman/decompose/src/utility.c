float kmSQR(float s)
{
  return s * s;
}


/*** DEPENDENCIES:
***/


float kmDegreesToRadians(float degrees)
{
  return degrees * (3.14159265358979323846f / 180.0f);
}


/*** DEPENDENCIES:
***/


float kmRadiansToDegrees(float radians)
{
  return radians * (180.0 / 3.14159265358979323846f);
}


/*** DEPENDENCIES:
***/


float kmMin(float lhs, float rhs)
{
  return (lhs < rhs) ? (lhs) : (rhs);
}


/*** DEPENDENCIES:
***/


float kmMax(float lhs, float rhs)
{
  return (lhs > rhs) ? (lhs) : (rhs);
}


/*** DEPENDENCIES:
***/


unsigned char kmAlmostEqual(float lhs, float rhs)
{
  return ((lhs + 0.0001) > rhs) && ((lhs - 0.0001) < rhs);
}


/*** DEPENDENCIES:
***/


float kmClamp(float x, float min, float max)
{
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


/*** DEPENDENCIES:
***/


float kmLerp(float x, float y, float t)
{
  return x + (t * (y - x));
}


/*** DEPENDENCIES:
***/


