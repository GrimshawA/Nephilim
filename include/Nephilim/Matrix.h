#ifndef Matrix_h__
#define Matrix_h__

#include <Nephilim/Platform.h>
#include "Vectors.h"

NEPHILIM_NS_BEGIN

class mat3;

/**
	\ingroup Foundation
	\class mat4
	\brief 4x4 Matrix oriented for OpenGL transformations

	Note: Row major
*/
class NEPHILIM_API mat4
{
public:
	/// Construct the matrix with identity
	mat4();

	mat4(	float a00, float a01, float a02, float a03,
			float a10, float a11, float a12, float a13,
			float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33);

	mat4(const float* elements);

	/// Construct a mat4x4 from a mat3x3 with the fourth line as identity
	mat4(const mat3& m);

	float element(int row, int col);

	/// Invert the matrix
	void invert();

	/// Get the inverse of the matrix
	mat4 inverse() const;

	/// Get the inverse of the matrix (only for 2d transforms)
	/// Calculates the inverted 4x4 matrix by ignoring the
	/// third line and column, pretending it to be a 3x3 matrix
	/// corresponding to a 2D transform.
	mat4 inverse2d();

	/// Get the matrix array ptr
	const float* get() const;

	/// Transpose the matrix
	void transpose();

	/// Get a transposed copy of this matrix
	mat4 transposed();

	/// Get the determinant of the 4x4 matrix
	/// DOES NOT WORK YET IN ALL CASES
	float determinant();

	/// Calculate the determinant of the matrix (only if it is a 2D transform)
	/// Ignores the third row and column, and computes the determinant
	/// from the resulting 3x3 matrix.
	/// This is for speeding up computation in very specific cases
	/// like getting a ortho projection inverse quicker
	inline float determinant2d();

	float& operator[](unsigned int index);
	float operator[](unsigned int index) const;

	static mat4 perspective(float fov, float aspectRatio, float zNear, float zFar);
	static mat4 lookAt(Vec3f eye, Vec3f center, Vec3f up);

	static mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

	static mat4 scale(float x, float y, float z);
	static mat4 translate(float x, float y, float z);
	static mat4 translate(vec3 v);
	static mat4 rotate(float angle_x, float angle_y, float angle_z);
	static mat4 quaternion(float qx, float qy, float qz, float qw);

	static mat4 rotatey(float angle);
	static mat4 rotatex(float angle);
	static mat4 rotatez(float angle);

	/// Creates a texture matrix to transform texture coordinates
	/// Multiplying texture coordinates by this matrix will allow effects such as showing the texture upside-down
	/// Also, it allows to convert pixel coordinates to unit coordinates
	/// textureTransform(false, 1.f, 1.f) is the default and leaves the texture coordinates unchanged
	/// flipVertically states whether to flip the texture coordinates vertically
	/// scaleX, scaleY state the maximum value for the texture coordinates
	/// For pixel coordinate transformation, it would be (textureSize.x,textureSize.y)
	static mat4 textureTransform(bool flipVertically, float scaleX, float scaleY);

	/// Multiply the matrix by a vector
	vec4 operator*(const vec4& v) const;

	/// Multiply the 4x4 matrix by a vec3. W component is assumed to be 1.0
	/// Returns vec3 for convenience
	vec3 operator*(const vec3& v) const;

	/// Multiply two 4x4 matrices
	mat4 operator*(const mat4& m) const;

	/// Multiply by a scalar
	mat4 operator*(float scalar);

	/// Identity matrix
	static const mat4 identity;

private:
	float m_matrix[16]; ///< The matrix array
};

/**
	\ingroup Foundation
	\class mat3
	\brief Defines a 3x3 matrix
*/
class NEPHILIM_API mat3
{
public:
	/// Default construction
	mat3();

	mat3(float a00, float a01, float a02,
		 float a10, float a11, float a12,
	 	 float a20, float a21, float a22);

	/// Access operator for elements
	float operator[](unsigned int index) const;

	/// Assign operator
	float& operator[](unsigned int index);

	void transpose();  

private:
	float m_matrix[9];
};

void debugPrint(mat4& m);

NEPHILIM_NS_END
#endif // Matrix_h__
