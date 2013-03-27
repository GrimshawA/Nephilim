#ifndef PARABOLA_PROTECTEDPOINTER_H
#define PARABOLA_PROTECTEDPOINTER_H

#include "Platform.h"
#include <list>

PARABOLA_NAMESPACE_BEGIN

template<typename T>
class ref_ptr;

/**
	\ingroup Foundation
	\class proc_ptr
	\brief A smart pointer type. Protects an object from early destruction.

	This smart pointer only holds an object in memory
	and keeps a list of read-only references to it.

	This way it grants that all references to it cannot delete it, and that 
	the references will be NULL valued when the object is destroyed.
*/
/*template<typename T>
class PARABOLA_API proc_ptr{
public:
	/// Creates the protected pointer from a raw pointer
	proc_ptr(T* raw);

	/// Creates a reference to the 
	ref_ptr<T>* makeReference();
	
	/// Destroys the protected object
	void destroy();

private:
	/// List of references to this object
	std::list<ref_ptr<T>* > refs;
	T* object;
};
*/


/**
	\ingroup Foundation
	\class ref_ptr
	\brief Smart pointer. Used to create read-only smart pointers of raw objects.
*/
template<typename T>
class PARABOLA_API ref_ptr{
public:
	/// Creates a read only pointer from a raw pointer
	ref_ptr(T* raw);

	/// Destroys the proc
	~ref_ptr();

	/// Allows to dereference the object, as it could be used to pass it to functions
	T& operator*() const;
	
	/// Allows to access directly the object's members
	T* operator->() const;

	/// Allows to check if the smart pointer is valid
	operator bool() const;

	/// Allows to check if the smart pointer is valid
	bool operator !();

private:
	T* object;
};

/// Creates a read only pointer from a raw pointer
template<typename T>
ref_ptr<T>::ref_ptr(T* raw){
	object = raw;
};

/// Destroys the proc
template<typename T>
ref_ptr<T>::~ref_ptr(){
	// here i would delete myself from the proc_ptr
	object = NULL;
};

/// Allows to dereference the object, as it could be used to pass it to functions
template<typename T>
T& ref_ptr<T>::operator*() const{
	return *object;
};

/// Allows to access directly the object's members
template<typename T>
T* ref_ptr<T>::operator->() const{
	return object;
};


/// Allows to check if the smart pointer is valid
template<typename T>
ref_ptr<T>::operator bool() const{
	return (object != NULL);
};

/// Allows to check if the smart pointer is valid
template<typename T>
bool ref_ptr<T>::operator !(){
	return (object == NULL);
};

PARABOLA_NAMESPACE_END
#endif