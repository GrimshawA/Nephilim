/************************************************************************/
/* Vec2                                                                 */
/************************************************************************/

template<class T>
Vec2<T>::Vec2()
: x(static_cast<T>(0))
, y(static_cast<T>(0))
{

};

template<class T>
Vec2<T>::Vec2(T x, T y){
	this->x = x;
	this->y = y;
};

template<class T>
void Vec2<T>::set(T x, T y){
	this->x = x;
	this->y = y;
};

template<class T>
void Vec2<T>::setAll(T x){
	this->x = x;
	this->y = x;
};

template<class T>
Vec2<T> Vec2<T>::normalized()
{
	vec2 v2 = *this;
	v2.normalize();
	return v2;
}

/// Makes the vector unit-length
template<class T>
void Vec2<T>::normalize(){
	x /= length();
	y /= length();
};

/// Get the length of the vector
template<class T>
float Vec2<T>::length(){
	return sqrt(x*x + y*y);
};

template<class T>
bool Vec2<T>::operator==(const Vec2<T> &vec){
	if(x == vec.x && y == vec.y)
		return true;
	else return false;
};

template<class T>
bool Vec2<T>::operator!=(const Vec2<T> &vec){
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
Vec2<T> Vec2<T>::operator+(const Vec2<T> &vec){
	Vec2<T> v(*this);
	v += vec;
	return v;
};
template<class T>
Vec2<T> Vec2<T>::operator+(const T &scalar){
	Vec2<T> v(*this);
	v += scalar;
	return v;
};

template<class T>
Vec2<T> Vec2<T>::operator-(const Vec2<T> &vec){
	Vec2<T> v(*this);
	v -= vec;
	return v;
};

template<class T>
Vec2<T> Vec2<T>::operator-(const T &scalar){
	Vec2<T> v(*this);
	v -= scalar;
	return v;
};

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
void Vec3<T>::setAll(T x){
	this->x = x;
	this->y = x;
	this->z = x;
};

/// Makes the vector unit-length
template<class T>
void Vec3<T>::normalize(){
	x /= length();
	y /= length();
	z /= length();
};

/// Compute the cross product
template<class T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &vec)
{
	return Vec3<T>(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

/// Get the length of the vector
template<class T>
float Vec3<T>::length(){
	return sqrt(x*x + y*y + z*z);
};

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
	x /= length();
	y /= length();
	z /= length();
	w /= length();
}

template<class T>
float Vec4<T>::length(){
	return sqrt(x*x + y*y + z*z + w*w);
};

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