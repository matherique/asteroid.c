#include <math.h>
#include <vector.h>

Vector create_vector(float x, float y) {
  Vector v = {x, y};

  return v;
}

Vector add_vector(Vector a, Vector b) {
  float nx = a.x + b.x;
  float ny = a.y + b.y;

  Vector v = {nx, ny};
  return v;
}

Vector scale_vector(Vector v, int scale) {
  Vector nv = {};
  nv.x = v.x * scale;
  nv.y = v.y * scale;

  return nv;
}

Vector rotate_vector(Vector v, float angle) {
  Vector result;

  float angleInRadians = angle * M_PI / 180.0f;

  float cosTheta = cos(angleInRadians);
  float sinTheta = sin(angleInRadians);

  result.x = v.x * cosTheta - v.y * sinTheta;
  result.y = v.x * sinTheta + v.y * cosTheta;

  return result;
}
