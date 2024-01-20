/*
*	Vector 3 - A 3d vector class developed for Ubisoft NEXT 2023
*/
#pragma once

class Vector3 {
public: //Methods
	/// <summary>
	/// Creates a vector with the value "xyz" on all axes
	/// </summary>
	/// <param name="xyz">Value on all axes</param>
	Vector3(float xyz) { x = xyz; y = xyz; z = xyz; }
	/// <summary>
	/// Creates a vector with values on x and y, 0 on z
	/// </summary>
	/// <param name="in_x">X value</param>
	/// <param name="in_y">Y value</param>
	Vector3(float in_x, float in_y) { x = in_x; y = in_y; z = 0.f; };
	Vector3(float in_x, float in_y, float in_z) { x = in_x; y = in_y; z = in_z; }

public: //Members
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
public: // ** Operators ** //
	//Equal
	inline const Vector3 operator =(const Vector3& other) { x = other.x; y = other.y; z = other.z; };

};

class Color3 : public Vector3
{
public: //Methods
	/// <summary>
	/// Creates a vector with the value "xyz" on all axes
	/// </summary>
	/// <param name="xyz">Value on all axes</param>
	Color3(float RGB) : Vector3(RGB) {}
	/// <summary>
	/// Creates a vector with values on x and y, 0 on z
	/// </summary>
	/// <param name="in_x">X value</param>
	/// <param name="in_y">Y value</param>
	Color3(float InX, float InY) : Vector3(InX, InY) {};
	Color3(float InX, float InY, float InZ) : Vector3(InX, InY, InZ) {};


	inline const void operator =(const Color3& other) { x = other.x; y = other.y; z = other.z; };

public: //Members
	float& r = x;
	float& g = y;
	float& b = z;
};

//TODO static colors for easy usage