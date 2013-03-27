//////////////////////////////////////////////////////////////////
template<typename T>
Rect<T>::Rect(){
	left = top = width = height = static_cast<T>(0);
}

template<typename T>
Rect<T>::Rect(T left, T top, T width, T height){
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
}

template<typename T>
bool Rect<T>::contains(T x, T y){
	return(x >= left &&
		x <= left + width &&
		y >= top &&
		y <= top + height );
};

template<typename T>
void Rect<T>::set(T left, T top, T width, T height){
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
};

template<typename T>
void Rect<T>::move(T x, T y){
	left += x;
	right += y;
};

template<typename T>
void Rect<T>::setPosition(T x, T y){
	left = x;
	top = y;	
};

template<typename T>
bool Rect<T>::intersects(Rect<T> &box){
	return (box.contains(left, top) ||
		box.contains(left, top + height) ||
		box.contains(left + width, top) ||
		box.contains(left + width, top + height) );
};
