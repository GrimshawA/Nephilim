#include <Nephilim/Foundation/ReferenceCountable.h>

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN
/// Sets the reference count to 1
RefCountable::RefCountable()
{
	refCount = 1;
	//cout<<"[RefCount:"<<this<<"] Init: 1"<<endl;
};

RefCountable::~RefCountable()
{

}                             

/// For AngelScript, the constructor won't do, need another function to set to 1 the refCount
void RefCountable::factoryConstructor(){
	refCount = 1;
};

/// Adds a reference
void RefCountable::addReference(){
	refCount++;
	//cout<<"[RefCount:"<<this<<"] Add: "<<refCount <<endl;
};

/// Removes a reference and destroys if necessary
void RefCountable::removeReference(){
	//cout<<"[RefCount:"<<this<<"] Released: "<<refCount - 1<<endl;	
	if(--refCount == 0){
		delete this;
	}
};

NEPHILIM_NS_END