#include <Nephilim/Quaternion.h>
#include <Nephilim/Logger.h>


NEPHILIM_NS_BEGIN

Quaternion Quaternion::identity;

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

Quaternion::Quaternion(vec3 v, float nw)
: x(v.x)
, y(v.y)
, z(v.z)
, w(nw)
{

}


vec3 Quaternion::xyz()
{
	return vec3(x,y,z);
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

Quaternion Quaternion::operator*(const Quaternion& q2)
{
	Quaternion qr;
	vec3 va, vb, vc;
	
	qr.w = vec3(x,y,z).dot(vec3(q2.x, q2.y, q2.z));

	va = vec3(x,y,z).cross(vec3(q2.x, q2.y, q2.z));
	vb = vec3(x,y,z) * q2.w;
	vc = vec3(q2.x, q2.y, q2.z) * w;

	va = va + vb;
	qr.x = va.x + vc.x;
	qr.y = va.y + vc.y;
	qr.z = va.z + vc.z;

	qr.normalize();

	// test 2
	qr.w = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
	qr.x = w * q2.x + x * q2.w + y * q2.z - z * q2.y;
	qr.y = w * q2.y - x * q2.z + y * q2.w + z * q2.x;
	qr.z = w * q2.z + x * q2.y - y * q2.x + z * q2.w;

	return qr;
}


void Quaternion::rotateEulerAngles(float ax, float ay, float az)
{
	vec3 vx(1.f, 0.f, 0.f), vy(0.f, 1.f, 0.f), vz(0.f, 0.f, 1.f);
	Quaternion qx, qy, qz, qt;

	// Extract a quaternion from a basis axis and a euler angle
	Quaternion::fromAxisAngle( qx, vx, ax );
	Quaternion::fromAxisAngle( qy, vy, ay );
	Quaternion::fromAxisAngle( qz, vz, az );

	qt = qx * qy;
	qt = qt * qz;

	// qt holds the resulting quaternion

	*this = *this * qt;
}

void Quaternion::rotateAxisAngle(float angle, float ax, float ay, float az)
{
	Quaternion qr;
	Quaternion::fromAxisAngle(qr, vec3(ax,ay,az), angle);

	*this = *this * qr;
}

float Quaternion::dot(Quaternion& q1, Quaternion& q2)
{
	return (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w);
}

float Quaternion::lengthSquared()
{
	return (x * x + y * y + z * z + w * w);
}


Quaternion Quaternion::slerp(Quaternion& q1, Quaternion& q2, float blend)
{
	/*
	// if either input is zero, return the other.
	if (q1.lengthSquared() == 0.0f)
	{
		if (q2.lengthSquared() == 0.0f)
		{
			return Quaternion::identity;
		}
		return q2;
	}
	else if (q2.lengthSquared() == 0.0f)
	{
		return q1;
	}
	
	float cosHalfAngle = q1.w * q2.w + (q1.xyz().dot(q2.xyz()));

	if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
	{
		// angle = 0.0f, so just return one input.
		return q1;
	}
	else if (cosHalfAngle < 0.0f)
	{
		q2.xyz() = q2.xyz() * -1.f;
		q2.w = -q2.w;
		cosHalfAngle = -cosHalfAngle;
	}

	float blendA;
	float blendB;
	if (cosHalfAngle < 0.99f)
	{
		// do proper slerp for big angles
		float halfAngle = (float)acos(cosHalfAngle);
		float sinHalfAngle = (float)sin(halfAngle);
		float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
		blendA = (float)sin(halfAngle * (1.0f - blend)) * oneOverSinHalfAngle;
		blendB = (float)sin(halfAngle * blend) * oneOverSinHalfAngle;
	}
	else
	{
		// do lerp if angle is really small.
		blendA = 1.0f - blend;
		blendB = blend;
	}

	Quaternion result(q1.xyz() *blendA + q2.xyz() * blendB, blendA * q1.w + blendB * q2.w);
	if (result.lengthSquared() > 0.0f)
	{
		result.normalize();
		return result;
	}
	else
		return Quaternion::identity;*/

	float threshold = 0.05f;
	float angle = Quaternion::dot(q1, q2);

	if (angle < 0.0f)
	{
		q1 *= -1.0f;
		angle *= -1.0f;
	}
	
	if (angle <= (1.f - threshold)) // spherical interpolation
	{
		Quaternion qr;
		const float theta = acosf(angle);
		const float invsintheta = 1.f / sinf(theta);
		const float scale = sinf(theta * (1.0f-blend)) * invsintheta;
		const float invscale = sinf(theta * blend) * invsintheta;
		qr = (q1*scale) + (q2*invscale);
		return qr;
	}
	else // linear interploation
		return lerp(q1, q2, blend);
}

Quaternion Quaternion::lerp(Quaternion& q1, Quaternion& q2, float blend)
{
	const float scale = 1.0f - blend;
	Quaternion q = (q1*scale) + (q2*blend);
	return q;
}

Quaternion& Quaternion::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Quaternion Quaternion::operator*(float scalar)
{
	Quaternion qr = *this;
	qr *= scalar;
	return qr;
}

Quaternion Quaternion::operator+(const Quaternion& q2)
{
	Quaternion qr = *this;
	qr.x += q2.x;
	qr.y += q2.y;
	qr.z += q2.z;
	qr.w += q2.w;
	return qr;
}


void Quaternion::fromAxisAngle(Quaternion& q, vec3 axis, float angle)
{
	float sin_a = sin( angle / 2 );
	float cos_a = cos( angle / 2 );

	q.x    = axis.x * sin_a;
	q.y    = axis.y * sin_a;
	q.z    = axis.z * sin_a;
	q.w    = cos_a;

	q.normalize();
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