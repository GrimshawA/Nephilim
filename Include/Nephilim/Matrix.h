#ifndef Matrix_h__
#define Matrix_h__

#include "Platform.h"
#include "Vectors.h"

NEPHILIM_NS_BEGIN

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

	/// Invert the matrix
	void invert();

	/// Get the inverse of this matrix
	mat4 getInverse();

	/// Get the matrix array ptr
	const float* get() const;

	

	float& operator[](unsigned int index);
	float operator[](unsigned int index) const;

	static mat4 perspective(float fov, float aspectRatio, float zNear, float zFar);
	static mat4 lookAt(Vec3f eye, Vec3f center, Vec3f up);

	static mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

	static mat4 scale(float x, float y, float z);
	static mat4 translate(float x, float y, float z);
	static mat4 rotate(float angle_x, float angle_y, float angle_z);

	/// Creates a texture matrix to transform texture coordinates
	/// Multiplying texture coordinates by this matrix will allow effects such as showing the texture upside-down
	/// Also, it allows to convert pixel coordinates to unit coordinates
	/// textureTransform(false, 1.f, 1.f) is the default and leaves the texture coordinates unchanged
	/// flipVertically states whether to flip the texture coordinates vertically
	/// scaleX, scaleY state the maximum value for the texture coordinates
	/// For pixel coordinate transformation, it would be (textureSize.x,textureSize.y)
	static mat4 textureTransform(bool flipVertically, float scaleX, float scaleY);

	/// Multiply the matrix by a vector
	vec4 operator*(const vec4& v);

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

};

NEPHILIM_NS_END
#endif // Matrix_h__
