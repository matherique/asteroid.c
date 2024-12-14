typedef struct {
  float x;
  float y;
} Vector;

Vector create_vector(float x, float y);

Vector add_vector(Vector a, Vector b);

Vector scale_vector(Vector v, int scale);

Vector rotate_vector(Vector v, float angle);
