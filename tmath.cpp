#include "tmath.h"

Vector2 operator+(const Vector2 &a, const Vector2 &b){
	return Vector2Add(a,b);
}


Vector2 operator-(const Vector2 &a, const Vector2 &b){
	return Vector2Subtract(a,b);
}


Vector2 operator*(const Vector2 &a, const float &f){
	return Vector2Scale(a,f);
}


Vector2 operator/(const Vector2 &a, const float &f){
	return Vector2Divide(a,f);
}


Vector2 operator/(const Vector2 &a, const Vector2 &b){
	return Vector2DivideV(a,b);
}


void operator+=(Vector2 &a, const Vector2 &b){
	a = Vector2Add(a,b);
}


void operator-=(Vector2 &a, const Vector2 &b){
	a = Vector2Subtract(a,b);
}


void operator*=(Vector2 &a, const float &f){
	a = Vector2Scale(a,f);
}


void operator/=(Vector2 &a, const float &f){
	a = Vector2Divide(a,f);
}


void operator/=(Vector2 &a, const Vector2 &b){
	a = Vector2DivideV(a,b);
}


float dot(const Vector2 &a, const Vector2 &b){
	return Vector2DotProduct(a, b);
}
