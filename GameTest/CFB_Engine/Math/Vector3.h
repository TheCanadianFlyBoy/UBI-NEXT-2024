/*
*	Vector 3 - A 3d vector class developed for Ubisoft NEXT 2023
*/
#pragma once

namespace fw {
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

	};

} //namespace fw