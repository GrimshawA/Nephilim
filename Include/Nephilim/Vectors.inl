/************************************************************************/
/* Vec2                                                                 */
/************************************************************************/

template<class T>
Vec2<T>::Vec2(){

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

};

template<class T>
Vec3<T>::Vec3(T x, T y, T z){
	this->x = x;
	this->y = y;
	this->z = z;
};

template<class T>
void Vec3<T>::set(T x, T y, T z){
	this->x = x;
	this->y = y;
	this->z = z;
};

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


/************************************************************************/
/* Vec4                                                                 */
/************************************************************************/

template<class T>
Vec4<T>::Vec4(){

};

template<class T>
Vec4<T>::Vec4(T x, T y, T z, T w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
};

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