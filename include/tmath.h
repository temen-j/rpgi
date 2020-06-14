#include "raylib\raymath.h"

typedef Quaternion Vector4;

Vector2 operator+(const Vector2 &a, const Vector2 &b);
Vector2 operator-(const Vector2 &a, const Vector2 &b);
Vector2 operator*(const Vector2 &a, const float &f);
Vector2 operator/(const Vector2 &a, const float &f);
Vector2 operator/(const Vector2 &a, const Vector2 &b);

void operator+=(Vector2 &a, const Vector2 &b);
void operator-=(Vector2 &a, const Vector2 &b);
void operator*=(Vector2 &a, const float &f);
void operator/=(Vector2 &a, const float &f);
void operator/=(Vector2 &a, const Vector2 &b);
float dot(const Vector2 &a, const Vector2 &b);
Vector2 rot(Vector2 &a, float theta);

