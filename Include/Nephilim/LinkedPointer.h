#ifndef PARABOLA_LINKED_POINTER_H
#define PARABOLA_LINKED_POINTER_H

#include "Platform.h"

#ifndef PARABOLA_ANDROID
#include <list>

/// \namespace pE
PARABOLA_NAMESPACE_BEGIN	

	/**
		\ingroup Foundation
		\class linked_ptr
		\brief Reference counted and destruction-aware smart pointers.

		This smart pointer allows to have one object shared by many instances, that will be automatically
		deleted when no more linked_ptr linking to it are alive. 

		Besides that it grants the safe destruction of the object by the RAII idiom, it will also keep
		record of all instances that reference the same object, and nullify them on earlier object destruction.

		Basically, using this smart pointer, you will never have trouble with orphaned pointers as long as you check
		them for a NULL value.
	*/
	template<class T>
	class PARABOLA_API linked_ptr{
	public:
		/**
			\brief Constructs the smart pointer with NULL by default.
		*/
		linked_ptr();

		/**
			\brief Constructs the smart pointer from a new unmanaged object
		*/
		linked_ptr(void *obj);
		/**
			\brief Constructs the smart pointer from a new unmanaged object.
		*/
		linked_ptr(T *obj);
		/**
			\brief Constructs the smart pointer directly from another.
		*/
		linked_ptr(const linked_ptr<T> &ref);
		/**
			\brief Destructor of the smart pointer instance. The object will be destroyed if it helds the last reference.
		*/
		~linked_ptr();

		/**
			\brief Get the raw pointer.
		*/
		T* get();

		/**
			\brief Get the number of existing smart pointers to the object.
		*/
		int getReferenceCount();

		/**
			\brief Operator* overload. Allows the common dereferencing operation on the pointer.
		*/
		T& operator*() const;
		/**
			\brief Operator-> overload. Allows direct access to the raw pointer.
		*/
		T* operator->() const;

		/**
			\brief Implicit boolean conversion for comparing a linked_ptr as a raw pointer.
		*/
		operator bool() const;

		/**
			\brief Negation operator overload for transparent pointer access.
		*/
		bool operator !();

		/**
			\brief Assigning the instance as a reference to the object of another.
			\todo make it NULL if the received object is null too
		*/
		linked_ptr<T>& operator=(const linked_ptr<T> &ref);
		/**
			\brief Assigning the instance as a reference to the unmanaged object
		*/
		linked_ptr<T>& operator=(T* obj);

		/**
			\brief Forcefully destroys the object even if there are references to it.

			Doing this means that every reference to that object becomes NULL.
		*/
		void destroy();

		/**
			\brief Unlinks all other smart pointers to this object.

			Using this function grants that you become the only pointer that references the object.
			All other pointers become NULL.
		*/
		void takeOwnership();

		/**
			\brief Becomes a null smart pointer. Destructs the object if necessary.
		*/
		void removeReference();




	private:
		std::list<linked_ptr<T>*> *refList;
		T* object;
	};






	/************************************************************************/
	/* Implementation                                                       */
	/************************************************************************/



		template<class T>
		linked_ptr<T>::linked_ptr() : object(NULL), refList(NULL){
			
		};
	
		template<class T>
		linked_ptr<T>::linked_ptr(void *obj) : object((T*)obj){
			if(obj){
				refList = (new std::list<linked_ptr<T>* >());
				refList->insert(refList->end(), this);
			}
		};

		template<class T>
		linked_ptr<T>::linked_ptr(T *obj) : object(obj){
			if(obj){
				refList = (new std::list<linked_ptr<T>* >());
				refList->insert(refList->end(), this);
			}
		};
	
		template<class T>
		linked_ptr<T>::linked_ptr(const linked_ptr<T> &ref){
			this->object = ref.object;
			this->refList = ref.refList;

			if(object) refList->insert(refList->end(), this);
		};

		template<class T>
		linked_ptr<T>::~linked_ptr(){
			removeReference();
		};

		template<class T>
		T* linked_ptr<T>::get(){
			return object;
		};

		template<class T>
		int linked_ptr<T>::getReferenceCount(){
			if(refList)return refList->size();
			else return 0;
		};

		template<class T>
		T& linked_ptr<T>::operator*() const{
			return *object;
		};
		
		template<class T>
		T* linked_ptr<T>::operator->() const{
			return object;
		};
		
		template<class T>
		linked_ptr<T>::operator bool() const{
			return (object != NULL);
		};

		template<class T>
		bool linked_ptr<T>::operator !(){
			return (object == NULL);
		};

		template<class T>
		linked_ptr<T>& linked_ptr<T>::operator=(const linked_ptr<T> &ref){
			if(ref){
				//remove from any previous object list
				removeReference();

				//add to new one
				this->object = ref.object;
				this->refList = ref.refList;

				if(object) refList->insert(refList->end(), this);			
			}
			return *this;
		};
	
		template<class T>
		linked_ptr<T>& linked_ptr<T>::operator=(T* obj){
			//remove from any previous object list
			removeReference();

			this->object = obj;

			if(obj){
				refList = (new std::list<linked_ptr<T>* >());
				refList->insert(refList->end(), this);
			}
			else refList = NULL;

			return *this;
		};

		template<class T>
		void linked_ptr<T>::destroy(){			
			if(object){
				delete object;

				std::list<linked_ptr<T>*> *link = refList;
				std::list<linked_ptr<T>*>::iterator it = link->begin();
				while(it != link->end()){
					(*it)->object = NULL;
					(*it)->refList = NULL;
					it++;
				}
				
				delete link;
			}
		};

		template<class T>
		void linked_ptr<T>::takeOwnership(){
			if(object){
				std::list<linked_ptr<T>*>::iterator it = refList->begin();
				while(it != refList->end()){
					if( (*it) != this ){
						(*it)->object = NULL;
						(*it)->refList = NULL;
						it = refList->erase(it);
					}	
					else it++;
				}
			}
		};

		template<class T>
		void linked_ptr<T>::removeReference(){
			if(object){
				refList->remove(this);

				if(refList->size() == 0){
					delete object;
					delete refList;
				}

				object = NULL;
				refList = NULL;
			}
		};


PARABOLA_NAMESPACE_END
#endif
#endif