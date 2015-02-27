/************************************************************************/
/* Vec2                                                                 */
/************************************************************************/

template<class T>
Vec2<T>::Vec2()
: x(static_cast<T>(0))
, y(static_cast<T>(0))
{
}

template<class T>
Vec2<T>::Vec2(T x, T y)
{
	this->x = x;
	this->y = y;
}

/// Rotates the vector by radians. Must be normalized.
template<class T>
void Vec2<T>::rotate(float radians)
{
	float new_x = x * cos(radians) - y * sin(radians);
	float new_y = x * sin(radians) + y * cos(radians);
	x = new_x;
	y = new_y;
}

template<class T>
void Vec2<T>::set(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
void Vec2<T>::setAll(T x)
{
	this->x = x;
	this->y = x;
}

template<class T>
Vec2<T> Vec2<T>::normalized()
{
	vec2 v2 = *this;
	v2.normalize();
	return v2;
}

/// Makes the vector unit-length
template<class T>
void Vec2<T>::normalize()
{
	float v_len = length();
	if(v_len != 0.f)
	{
		x /= v_len;
		y /= v_len;
	}
}

/// Manhattan distance between
template<class T>
float Vec2<T>::manhattanDistance(const Vec2<T> &vec) const
{
	return fabs(vec.x - x) + fabs(vec.y - y);
}

/// Get the squared distance between the vectors, apply sqrt to get a final distance
template<class T>
float Vec2<T>::squaredDistance(const Vec2<T> &vec) const
{
	return (vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y);
}

/// Get this vector as a radian angle, must be normalized
template<class T>
float Vec2<T>::asRadianAngle()
{
	return atan2(y, x);
}

/// Get the length of the vector
template<class T>
float Vec2<T>::length() const
{
	return sqrt(x*x + y*y);
}

template<class T>
bool Vec2<T>::operator==(const Vec2<T> &vec) const
{
	if(x == vec.x && y == vec.y)
		return true;
	else
		return false;
}

template<class T>
bool Vec2<T>::operator!=(const Vec2<T> &vec) const
{
	return !(operator==(vec));
};

template<class T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T> &vec){
	x += vec.x;
	y += vec.y;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator+=(const T &scalar){
	x += scalar;
	y += scalar;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T> &vec){
	x -= vec.x;
	y -= vec.y;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator-=(const T &scalar){
	x -= scalar;
	y -= scalar;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator*=(const Vec2<T> &vec){
	x *= vec.x;
	y *= vec.y;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator*=(const T &scalar){
	x *= scalar;
	y *= scalar;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator/=(const Vec2<T> &vec){
	x /= vec.x;
	y /= vec.y;
	return *this;
};

template<class T>
Vec2<T>& Vec2<T>::operator/=(const T &scalar){
	x /= scalar;
	y /= scalar;
	return *this;
};

template<class T>
Vec2<T> Vec2<T>::operator+(const Vec2<T> &vec) const
{
	Vec2<T> v(*this);
	v += vec;
	return v;
}

template<class T>
Vec2<T> Vec2<T>::operator+(const T &scalar) const
{
	Vec2<T> v(*this);
	v += scalar;
	return v;
}

template<class T>
Vec2<T> Vec2<T>::operator-(const Vec2<T> &vec) const
{
	Vec2<T> v(*this);
	v -= vec;
	return v;
}

template<class T>
Vec2<T> Vec2<T>::operator-(const T &scalar) const
{
	Vec2<T> v(*this);
	v -= scalar;
	return v;
}

template<class T>
Vec2<T> Vec2<T>::operator*(const Vec2<T> &vec){
	Vec2<T> v(*this);
	v *= vec;
	return v;
};

template<class T>
Vec2<T> Vec2<T>::operator*(const T &scalar){
	Vec2<T> v(*this);
	v *= scalar;
	return v;
};

template<class T>
Vec2<T> Vec2<T>::operator/(const Vec2<T> &vec){
	Vec2<T> v(*this);
	v /= vec;
	return v;
};

template<class T>
Vec2<T> Vec2<T>::operator/(const T &scalar){
	Vec2<T> v(*this);
	v /= scalar;
	return v;
};


/************************************************************************/
/* Vec3                                                                 */
/************************************************************************/

template<class T>
Vec3<T>::Vec3(){
	x = y = z = static_cast<T>(0);
};

template<class T>
Vec3<T>::Vec3(T x, T y, T z){
	this->x = x;
	this->y = y;
	this->z = z;
};

template<class T>
Vec3<T>::Vec3(Vec2<T> val, T z)
{
	this->x = val.x;
	this->y = val.y;
	this->z = z;
}

template<class T>
void Vec3<T>::set(T x, T y, T z){
	this->x = x;
	this->y = y;
	this->z = z;
};

template<class T>
Vec2<T> Vec3<T>::xy()
{
	return Vec2<T>(x, y);
}

template<class T>
void Vec3<T>::setAll(T x)
{
	this->x = x;
	this->y = x;
	this->z = x;
}

template<class T>
Vec3<T> Vec3<T>::lerp(Vec3<T> a, Vec3<T> b, float blend)
{
	a.x = blend * (b.x - a.x) + a.x;
	a.y = blend * (b.y - a.y) + a.y;
	a.z = blend * (b.z - a.z) + a.z;
	return a;
}

/// Makes the vector unit-length
template<class T>
void Vec3<T>::normalize()
{
	float v_len = length();
	if(v_len != 0.f)
	{
		x /= v_len;
		y /= v_len;
		z /= v_len;
	}
}

/// Compute the cross product
template<class T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &vec)
{
	return Vec3<T>(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

/// Get the length of the vector
template<class T>
float Vec3<T>::length() const
{
	return sqrt(x*x + y*y + z*z);
}

template<class T>
bool Vec3<T>::operator==(const Vec3<T> &vec){
	if(x == vec.x && y == vec.y && z == vec.z)
		return true;
	else return false;
};

template<class T>
bool Vec3<T>::operator!=(const Vec3<T> &vec){
	return !(operator==(vec));
};

template<class T>
Vec3<T>& Vec3<T>::operator+=(const Vec3<T> &vec){
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator+=(const T &scalar){
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator-=(const Vec3<T> &vec){
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator-=(const T &scalar){
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator*=(const Vec3<T> &vec){
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator*=(const T &scalar){
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator/=(const Vec3<T> &vec){
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
};

template<class T>
Vec3<T>& Vec3<T>::operator/=(const T &scalar){
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
};

template<class T>
Vec3<T> Vec3<T>::operator+(const Vec3<T> &vec){
	Vec3<T> v(*this);
	v += vec;
	return v;
};
template<class T>
Vec3<T> Vec3<T>::operator+(const T &scalar){
	Vec3<T> v(*this);
	v += scalar;
	return v;
};

template<class T>
Vec3<T> Vec3<T>::operator-(const Vec3<T> &vec){
	Vec3<T> v(*this);
	v -= vec;
	return v;
};

template<class T>
Vec3<T> Vec3<T>::operator-(const T &scalar){
	Vec3<T> v(*this);
	v -= scalar;
	return v;
};

template<class T>
Vec3<T> Vec3<T>::operator*(const Vec3<T> &vec){
	Vec3<T> v(*this);
	v *= vec;
	return v;
};

template<class T>
Vec3<T> Vec3<T>::operator*(const T &scalar){
	Vec3<T> v(*this);
	v *= scalar;
	return v;
};

template<class T>
Vec3<T> Vec3<T>::operator/(const Vec3<T> &vec){
	Vec3<T> v(*this);
	v /= vec;
	return v;
};

template<class T>
Vec3<T> Vec3<T>::operator/(const T &scalar){
	Vec3<T> v(*this);
	v /= scalar;
	return v;
};

/// Compute the dot product
template<class T>
float Vec3<T>::dot(const Vec3<T> &vec)
{
	return (x*vec.x) + (y*vec.y) + (z*vec.z);
}

/// Calculate the distance between vectors
template<class T>
float Vec3<T>::distance(const Vec3<T> &vec)
{
	return sqrt((vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z));
}

/// Calculate the squared distance between vectors
template<class T>
float Vec3<T>::squaredDistance(const Vec3<T> &vec)
{
	return (vec.x - x) * (vec.x - x) + (vec.y - y) * (vec.y - y) + (vec.z - z) * (vec.z - z);
}

/************************************************************************/
/* Vec4                                                                 */
/************************************************************************/

template<class T>
Vec4<T>::Vec4(){
	x = y = z = static_cast<T>(0);
	w = static_cast<T>(1);
};

template<class T>
Vec4<T>::Vec4(T x, T y, T z, T w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
};

template<class T>
Vec4<T>::Vec4(Vec3<T> vec3, T w)
{
	this->x = vec3.x;
	this->y = vec3.y;
	this->z = vec3.z;
	this->w = w;
}

template<class T>
void Vec4<T>::set(T x, T y, T z, T w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
};

template<class T>
void Vec4<T>::setAll(T x){
	this->x = x;
	this->y = x;
	this->z = x;
	this->w = x;
};

template<class T>
const T* Vec4<T>::get()
{
	return static_cast<T*>(&x);
}

template<class T>
template<class N>
Vec4<N> Vec4<T>::cast()
{
	return Vec4<N>(static_cast<N>(x), static_cast<N>(y), static_cast<N>(z), static_cast<N>(w));
}

template<class T>
bool Vec4<T>::operator==(const Vec4<T> &vec){
	if(x == vec.x && y == vec.y && z == vec.z && w == vec.w)
		return true;
	else return false;
};

template<class T>
bool Vec4<T>::operator!=(const Vec4<T> &vec){
	return !(operator==(vec));
};

template<class T>
void Vec4<T>::normalize()
{
	float v_len = length();
	x /= v_len;
	y /= v_len;
	z /= v_len;
	w /= v_len;
}

template<class T>
float Vec4<T>::length() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

template<class T>
Vec3<T> Vec4<T>::xyz()
{
	return Vec3<T>(x,y,z);
}

template<class T>
Vec2<T> Vec4<T>::xy()
{
	return vec2(x,y);
}

template<class T>
Vec4<T>& Vec4<T>::operator+=(const Vec4<T> &vec){
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator+=(const T &scalar){
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator-=(const Vec4<T> &vec){
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator-=(const T &scalar){
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator*=(const Vec4<T> &vec){
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator*=(const T &scalar){
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator/=(const Vec4<T> &vec){
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	w /= vec.w;
	return *this;
};

template<class T>
Vec4<T>& Vec4<T>::operator/=(const T &scalar){
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
};

template<class T>
Vec4<T> Vec4<T>::operator+(const Vec4<T> &vec){
	Vec4<T> v(*this);
	v += vec;
	return v;
};
template<class T>
Vec4<T> Vec4<T>::operator+(const T &scalar){
	Vec4<T> v(*this);
	v += scalar;
	return v;
};

template<class T>
Vec4<T> Vec4<T>::operator-(const Vec4<T> &vec){
	Vec4<T> v(*this);
	v -= vec;
	return v;
};

template<class T>
Vec4<T> Vec4<T>::operator-(const T &scalar){
	Vec4<T> v(*this);
	v -= scalar;
	return v;
};

template<class T>
Vec4<T> Vec4<T>::operator*(const Vec4<T> &vec){
	Vec4<T> v(*this);
	v *= vec;
	return v;
};

template<class T>
Vec4<T> Vec4<T>::operator*(const T &scalar){
	Vec4<T> v(*this);
	v *= scalar;
	return v;
};

template<class T>
Vec4<T> Vec4<T>::operator/(const Vec4<T> &vec){
	Vec4<T> v(*this);
	v /= vec;
	return v;
};

template<class T>
Vec4<T> Vec4<T>::operator/(const T &scalar){
	Vec4<T> v(*this);
	v /= scalar;
	return v;
};