#include <Nephilim/Matrix.h>
#include <Nephilim/MMath.h>
#include <math.h>

NEPHILIM_NS_BEGIN

const mat4 mat4::identity = mat4();

mat4::mat4()
{
	m_matrix[0] = 1.f; m_matrix[4] = 0.f; m_matrix[8]  = 0.f; m_matrix[12] = 0.f;
	m_matrix[1] = 0.f; m_matrix[5] = 1.f; m_matrix[9]  = 0.f; m_matrix[13] = 0.f;
	m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
	m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
}

////////////////////////////////////////////////////////////
mat4::mat4(	float a00, float a01, float a02, float a03,
			float a10, float a11, float a12, float a13,
			float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33)
{
	m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8]  = a02; m_matrix[12] = a03;
	m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9]  = a12; m_matrix[13] = a13;
	m_matrix[2] = a20; m_matrix[6] = a21; m_matrix[10] = a22; m_matrix[14] = a23;
	m_matrix[3] = a30; m_matrix[7] = a31; m_matrix[11] = a32; m_matrix[15] = a33;
}

mat4::mat4(const float* elements)
{
	for(int i = 0; i < 16; i++) m_matrix[i] = elements[i];
}


const float* mat4::get() const
{
	return &m_matrix[0];
}

float& mat4::operator[](unsigned int index)
{
	return m_matrix[index];
}

float mat4::operator[](unsigned int index) const
{
	return m_matrix[index];
}

/// Transpose the matrix
void mat4::transpose()
{
	mat4 m = *this;

	m_matrix[0] = m[0]; m_matrix[4] = m[1]; m_matrix[8]  = m[2]; m_matrix[12] = m[3];
	m_matrix[1] = m[4]; m_matrix[5] = m[5]; m_matrix[9]  = m[6]; m_matrix[13] = m[7];
	m_matrix[2] = m[8]; m_matrix[6] = m[9]; m_matrix[10] = m[10]; m_matrix[14] = m[11];
	m_matrix[3] = m[12]; m_matrix[7] = m[13]; m_matrix[11] = m[14]; m_matrix[15] = m[15];
}

/// Get a transposed copy of this matrix
mat4 mat4::transposed()
{
	mat4 m = *this;
	m.transpose();
	return m;
}

/// Multiply by a scalar
mat4 mat4::operator*(float scalar)
{
	return mat4( m_matrix[0] * scalar, m_matrix[4] * scalar, m_matrix[8] * scalar, m_matrix[12] * scalar,
				 m_matrix[1] * scalar, m_matrix[5] * scalar, m_matrix[9] * scalar, m_matrix[13] * scalar,
				 m_matrix[2] * scalar, m_matrix[6] * scalar, m_matrix[10] * scalar, m_matrix[14] * scalar,
				 m_matrix[3] * scalar, m_matrix[7] * scalar, m_matrix[11] * scalar, m_matrix[15] * scalar);
}

/// Multiply the matrix by a vector
vec4 mat4::operator*(const vec4& v)
{
	return vec4(	m_matrix[0]*v.x + m_matrix[4]*v.y + m_matrix[8]*v.z + m_matrix[12]*v.w,
					m_matrix[1]*v.x + m_matrix[5]*v.y + m_matrix[9]*v.z + m_matrix[13]*v.w,
					m_matrix[2]*v.x + m_matrix[6]*v.y + m_matrix[10]*v.z + m_matrix[14]*v.w,
					m_matrix[3]*v.x + m_matrix[7]*v.y + m_matrix[11]*v.z + m_matrix[15]*v.w);
}

/// Multiply two 4x4 matrices
mat4 mat4::operator*(const mat4& m) const
{
	return mat4 ( m_matrix[0]*m[0] + m_matrix[4]*m[1] + m_matrix[8]*m[2] + m_matrix[12]*m[3],
				  m_matrix[0]*m[4] + m_matrix[4]*m[5] + m_matrix[8]*m[6] + m_matrix[12]*m[7],
				  m_matrix[0]*m[8] + m_matrix[4]*m[9] + m_matrix[8]*m[10] + m_matrix[12]*m[11],
				  m_matrix[0]*m[12] + m_matrix[4]*m[13] + m_matrix[8]*m[14] + m_matrix[12]*m[15],

				  m_matrix[1]*m[0] + m_matrix[5]*m[1] + m_matrix[9]*m[2] + m_matrix[13]*m[3],
				  m_matrix[1]*m[4] + m_matrix[5]*m[5] + m_matrix[9]*m[6] + m_matrix[13]*m[7],
				  m_matrix[1]*m[8] + m_matrix[5]*m[9] + m_matrix[9]*m[10] + m_matrix[13]*m[11],
				  m_matrix[1]*m[12] + m_matrix[5]*m[13] + m_matrix[9]*m[14] + m_matrix[13]*m[15],

				  m_matrix[2]*m[0] + m_matrix[6]*m[1] + m_matrix[10]*m[2] + m_matrix[14]*m[3],
				  m_matrix[2]*m[4] + m_matrix[6]*m[5] + m_matrix[10]*m[6] + m_matrix[14]*m[7],
				  m_matrix[2]*m[8] + m_matrix[6]*m[9] + m_matrix[10]*m[10] + m_matrix[14]*m[11],
				  m_matrix[2]*m[12] + m_matrix[6]*m[13] + m_matrix[10]*m[14] + m_matrix[14]*m[15],

				  m_matrix[3]*m[0] + m_matrix[7]*m[1] + m_matrix[11]*m[2] + m_matrix[15]*m[3],
				  m_matrix[3]*m[4] + m_matrix[7]*m[5] + m_matrix[11]*m[6] + m_matrix[15]*m[7],
				  m_matrix[3]*m[8] + m_matrix[7]*m[9] + m_matrix[11]*m[10] + m_matrix[15]*m[11],
				  m_matrix[3]*m[12] + m_matrix[7]*m[13] + m_matrix[11]*m[14] + m_matrix[15]*m[15]  );
}

/// Invert the matrix
void mat4::invert()
{
	mat4 inverse = getInverse();
	*this = inverse;
}

mat4 mat4::ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	mat4 m;
	m[0] = 2.0f / (right - left);
	m[5] = 2.0f / (top - bottom);
	m[10] = 1.0f / (zNear - zFar);
	m[12] = (left + right) / (left - right);
	m[13] = (top + bottom) / (bottom - top);
	m[14] = zNear / (zNear - zFar);
	return m;
}


mat4 mat4::scale(float x, float y, float z)
{
	mat4 m;

	m[0] = x;
	m[5] = y;
	m[10] = z;

	return m;
}

mat4 mat4::rotatey(float angle)
{
	return mat4(cos(angle),  0.f, sin(angle), 0.f,
				0.f,         1.f, 0.f,        0.f,
				-sin(angle), 0.f, cos(angle), 0.f,
				0.f,         0.f, 0.f,        1.f);
}

mat4 mat4::rotatex(float angle)
{
	return mat4(1.f, 0.f,        0.f,         0.f,
		        0.f, cos(angle), -sin(angle), 0.f,
		        0.f, sin(angle), cos(angle),  0.f,
		        0.f, 0.f,        0.f,         1.f);
}

mat4 mat4::rotatez(float angle)
{
	return mat4(cos(angle),-sin(angle), 0.f,   0.f,
		        sin(angle), cos(angle), 0.f,   0.f,
		        0.f,        0.f,        1.f,   0.f,
		        0.f,        0.f,        0.f,   1.f);
}

mat4 mat4::rotate(float angle_x, float angle_y, float angle_z)
{
	float A       = cos(angle_x);
	float B       = sin(angle_x);
	float C       = cos(angle_y);
	float D       = sin(angle_y);
	float E       = cos(angle_z);
	float F       = sin(angle_z);

	float AD      =   A * D;
	float BD      =   B * D;

	mat4 mat;

	mat[0]  =   C * E;
	mat[4]  =  -C * F;
	mat[8]  =   D;
	mat[1]  =  BD * E + A * F;
	mat[5]  = -BD * F + A * E;
	mat[9]  =  -B * C;
	mat[2]  = -AD * E + B * F;
	mat[6]  =  AD * F + B * E;
	mat[10] =   A * C;

	return mat;
}

mat4 mat4::quaternion(float qx, float qy, float qz, float qw)
{
	const float n = 1.0f/sqrt(qx*qx+qy*qy+qz*qz+qw*qw);
	qx *= n;
	qy *= n;
	qz *= n;
	qw *= n;

	mat4 m(
		1.0f - 2.0f*qy*qy - 2.0f*qz*qz, 2.0f*qx*qy - 2.0f*qz*qw, 2.0f*qx*qz + 2.0f*qy*qw, 0.0f,
		2.0f*qx*qy + 2.0f*qz*qw, 1.0f - 2.0f*qx*qx - 2.0f*qz*qz, 2.0f*qy*qz - 2.0f*qx*qw, 0.0f,
		2.0f*qx*qz - 2.0f*qy*qw, 2.0f*qy*qz + 2.0f*qx*qw, 1.0f - 2.0f*qx*qx - 2.0f*qy*qy, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	return m;
}


/// Creates a texture matrix to transform texture coordinates
/// Multiplying texture coordinates by this matrix will allow effects such as showing the texture upside-down
/// Also, it allows to convert pixel coordinates to unit coordinates
/// textureTransform(false, 1.f, 1.f) is the default and leaves the texture coordinates unchanged
mat4 mat4::textureTransform(bool flipVertically, float scaleX, float scaleY)
{
	mat4 matrix;

	matrix[0] = 1.f / scaleX;
	matrix[5] = 1.f / scaleY;	

	// If pixels are flipped we must invert the Y axis
	if (flipVertically)
	{
		matrix[5] = -matrix[5];
		//matrix[13] = static_cast<float>(m_size.y / m_actualSize.y);
		matrix[13] = static_cast<float>(scaleY);
	}
	return matrix;
}

/// Get the inverse of this matrix
mat4 mat4::getInverse()
{
	return mat4();
}

mat4 mat4::perspective(float fov, float aspectRatio, float zNear, float zFar)
{
	float rFov = math::degreeToRadian<float>(fov);

	float cotan = 0.0f, DeltaZ = float(zNear) - float(zFar),
		angle = rFov / 2.0f, sine = sinf(angle);

	cotan = cosf(angle) / sine;

	mat4 m;

	m[0] = cotan / aspectRatio;
	m[5] = cotan;
	m[10] = zFar / DeltaZ;
	m[11] = -1.0f;
	m[14] = zNear * zFar / DeltaZ;
	m[15] = 0.0f;

	return m;
}

mat4 mat4::lookAt(Vec3f eye, Vec3f center, Vec3f up)
{
	Vec3f ZAxis = Vec3f(eye - center);
	ZAxis.normalize();

	Vec3f XAxis = up.cross(ZAxis);
	XAxis.normalize();

	Vec3f YAxis = ZAxis.cross(XAxis);

	mat4 m;

	m[0] = XAxis.x;
	m[1] = YAxis.x;
	m[2] = ZAxis.x;
	m[4] = XAxis.y;
	m[5] = YAxis.y;
	m[6] = ZAxis.y;
	m[8] = XAxis.z;
	m[9] = YAxis.z;
	m[10] = ZAxis.z;
	m[12] = -XAxis.dot(eye);
	m[13] = -YAxis.dot(eye);
	m[14] = -ZAxis.dot(eye);

	return m;
}

mat4 mat4::translate(float x, float y, float z)
{
	mat4 m;
	
	m[12] = x;
	m[13] = y;
	m[14] = z;

	return m;
}


NEPHILIM_NS_END