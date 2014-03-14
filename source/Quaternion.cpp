#include <Nephilim/Quaternion.h>
#include <Nephilim/Logger.h>


NEPHILIM_NS_BEGIN

Quaternion::Quaternion()
: x(0.f)
, y(0.f)
, z(0.f)
, w(1.f)
{
}

Quaternion::Quaternion(float nx, float ny, float nz, float nw)
: x(nx)
, y(ny)
, z(nz)
, w(nw)
{
}

void Quaternion::normalize()
{
	float magnitude = sqrt(x * x + y * y + z * z + w * w);
	if(magnitude != 0)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
		w /= magnitude;
	}
}

mat4 Quaternion::toMatrix()
{
	mat4 m = mat4::identity;

	float xx      = x * x;
	float xy      = x * y;
	float xz      = x * z;
	float xw      = x * w;

	float yy      = y * y;
	float yz      = y * z;
	float yw      = y * w;

	float zz      = z * z;
	float zw      = z * w;

	m[0] = 1 - 2 * yy - 2 * zz;
	m[1] = 2 * xy + 2 * zw;
	m[2] = 2 * xz - 2 * yw;

	m[4] = 2 * xy - 2 * zw;
	m[5] = 1 - 2 * xx - 2 * zz;
	m[6] = 2 * yz + 2 * xw;

	m[8] = 2 * xz + 2 * yw;
	m[9] = 2 * yz - 2 * xw;
	m[10] = 1 - 2 * xx - 2 * yy;

	return m;
}

Quaternion Quaternion::fromMatrix(mat4 m)
{
	Quaternion q;

	float T = m[0] + m[5] + m[10] + 1;

	if(T > 0.0000001)
	{
		float S = 2 * sqrt(T);

		float W = 0.25 / S;

		float X = ( m[6] - m[9] ) / S;

		float Y = ( m[8] - m[2] ) / S;

		float Z = ( m[1] - m[4] ) / S;

		q.x = X;
		q.y = Y;
		q.z = Z;
		q.w = W;

		// attempt 2
		q.w = 0.25f * S;
	}
	else
	{
		// Three possible cases
		if(m[0] > m[5] && m[0] > m[10])
		{
			float S  = sqrt( 1.0 + m[0] - m[5] - m[10] ) * 2;
			
			q.w = (m[6] - m[9] ) / S;
			q.x = 0.25f * S;
			q.y = (m[1] + m[4] ) / S;
			q.z = (m[8] + m[2] ) / S;
		}
		else if(m[5] > m[10])
		{
			float S  = sqrt( 1.0 + m[5] - m[0] - m[10] ) * 2;

			q.w = (m[8] - m[2] ) / S;
			q.x = (m[4] + m[1] ) / S;
			q.y = 0.25f * S;
			q.z = (m[9] + m[6] ) / S;
		}
		else
		{
			float S  = sqrt( 1.0 + m[10] - m[0] - m[5] ) * 2;

			q.w = (m[4] - m[1] ) / S;
			q.x = (m[8] + m[2] ) / S;
			q.y = (m[9] + m[6] ) / S;
			q.z = 0.25f * S;
		}
	}

	//q.normalize();

	return q;
}


NEPHILIM_NS_END