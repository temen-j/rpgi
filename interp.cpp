#include "include\raylib\raylib.h"
#include "include\interp.h"

float Lerp(const float t, const float a, const float b){
	float v;
	v = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
	return ((b - a) * v) + a;
}


Vector2 Lerp(const float t, const Vector2 a, const Vector2 b){
	return {Lerp(t, a.x, b.x), Lerp(t, a.y, b.y)};
}

