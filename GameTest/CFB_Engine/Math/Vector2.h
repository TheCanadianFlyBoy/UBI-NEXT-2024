#pragma once
#include <math.h>
#include "MathOps.h"
#include <string>

/// <summary>
/// A basic vector 2 class, using floats
/// </summary>
class Vector2 {

public: // ** Methods ** //

	//Constructors
	Vector2() { }
	Vector2(float xy)				{ x = xy; y = xy;  }
	Vector2(float in_x, float in_y) { x = in_x; y = in_y; }

	// Override values in one line
	inline void Set(float in_x, float in_y) { x = in_x; y = in_y; }
		// ~ Length calculations ~ //
	inline const float Length()			{ return sqrtf(x * x + y * y); }
	inline const float LengthSquared()  { return x * x + y * y; }
		// ~ Distance calculations ~ //
	inline const float DistanceFrom(const Vector2 other)		{ return sqrtf((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y)); }
	inline const float DistanceFromSquared(const Vector2 other) { return ((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y)); }
		// ~ Normalization calculations ~ //
	inline Vector2 GetNormalized() {
		float out_x = x != 0.f ? x / fabsf(Length()) : 0.f;
		float out_y = y != 0.f ? y / fabsf(Length()) : 0.f;
		return Vector2(out_x, out_y); }
	inline void Normalize()				     {  
		x = x != 0.f ? x / fabsf(Length()) : 0.f; 
		y = y != 0.f ? y / fabsf(Length()) : 0.f;		  }
		// ~ Cross/Dot calculations ~ //
	inline float Cross(const Vector2& other) { return x * other.y - y * other.x; }
	inline float Dot(const Vector2& other)   { return x * other.x + y * other.y; }
		// ~ Angle calculations   //
	inline float Angle(Vector2& other) { return acosf(Dot(other) / (Length() * other.Length())); }

public: // ** Operators ** //
		// ~ Negation ~ //
	inline const Vector2 operator -() { return Vector2(-x, -y); }
		// ~ Comparators ~ //
	inline const bool operator ==(const Vector2& other) { return MathOps::float_equals(x, other.x) && MathOps::float_equals(y, other.y); }
	inline const bool operator !=(const Vector2& other) { return !MathOps::float_equals(x, other.x) || !MathOps::float_equals(y, other.y); }
	inline const bool operator <(const Vector2& other)  { return (x == other.x) ? (y < other.y) : (x < other.x); }
	inline const bool operator >(const Vector2& other)  { return (x == other.x) ? (y > other.y) : (x > other.x); }
		// ~ Scalar Math ~ //
	inline Vector2 operator *(const float a)  { return Vector2(x * a, y * a); }
	inline Vector2 operator /(const float a)  { return Vector2(x / a, y / a); }
	inline Vector2 operator +(const float a)  { return Vector2(x + a, y + a); }
	inline Vector2 operator -(const float a)  { return Vector2(x - a, y - a); }
	inline Vector2 operator *=(const float a) { x *= a; y *= a; return *this; }
	inline Vector2 operator /=(const float a) { x /= a; y /= a; return *this; }
	inline Vector2 operator +=(const float a) { x += a; y += a; return *this; }
	inline Vector2 operator -=(const float a) { x -= a; y -= a; return *this; }
		// ~ Vector Math ~ //
	inline Vector2 operator  *(const Vector2& other)	{ return Vector2(x * other.x, y * other.y); }
	inline Vector2 operator  /(const Vector2& other)	{ return Vector2(x / other.x, y / other.y); }
	inline Vector2 operator  +(const Vector2& other)	{ return Vector2(x + other.x, y + other.y); }
	inline Vector2 operator  -(const Vector2& other)	{ return Vector2(x - other.x, y - other.y); }
	inline Vector2 operator  *=(const Vector2& other)	{ x *= other.x; y *= other.y; return *this; }
	inline Vector2 operator  /=(const Vector2& other)	{ x /= other.x; y /= other.y; return *this; }
	inline Vector2 operator  +=(const Vector2& other)	{ x += other.x; y += other.y; return *this; }
	inline Vector2 operator  -=(const Vector2& other)	{ x -= other.x; y -= other.y; return *this; }

	inline operator std::string() {
		std::string string = "";
		string.append(std::to_string(x));
		string.append(", ");
		string.append(std::to_string(y));
		return string;
	}

public: // ** Testing ** //
	static bool Test();


public: // ** Statics ** //
	static Vector2 ZeroVector()		{ return Vector2(0.f, 0.f); }
	static Vector2 Up()				{ return Vector2(0.f, 1.f); }
	static Vector2 Right()			{ return Vector2(1.f, 0.f); }

public: // ** Members ** //
	float x = 0.f;
	float y = 0.f;

};

