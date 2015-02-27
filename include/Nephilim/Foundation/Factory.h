#ifndef NephilimFactory_h__
#define NephilimFactory_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/String.h>
#include <Nephilim/Foundation/Object.h>

#include <stdint.h>
#include <vector>
#include <functional>
#include <sigc++/sigc++.h>

NEPHILIM_NS_BEGIN

/**
	\class FClass
	\brief (Factory class) represents a class registered at runtime in the factory

	There is one FClass per C++ class that gets registered in the factory,
	which provides type information and helps instance objects of that class.

	The factory can also optionally allow to track memory spent with each class
	instances.
*/
class NEPHILIM_API FClass
{
public:

	/// Class name (This is the actual C++ class name)
	String CName;

	/// This is the ID this class has during the entire execution of the program
	uint32_t DynamicId;

	/// This is the sizeof(T) for this class
	uint32_t Size;

	/// The known classes this class inherits from
	std::vector<FClass*> Parents;

	/// Used to instance FClass Objects
	std::function<void*()> InstancerFunc;

public:

	/// Check if this class has the other has ancestor (inherits from directly or indirectly)
	bool hasAncestor(const String& className);

	/// Check if the class has the other as ancestor
	bool hasAncestor(FClass* _class);
};

/**
	\class Factory
	\brief Global factory that manages dynamically allocated objects and how they are allocated

	This is where all classes are registered for reflection features and allocation.
	On registration, each class gets assigned a dynamic ID, which allows to find instances of a class
	by their ID.

	Factory acts as a singleton, there are no class groups, every class has to be registered in the same
	global factory.
*/
class NEPHILIM_API Factory
{
public:
	
	/// List of registered classes in the engine
	static std::vector<FClass*> registeredClasses;


public:	
	/// Register a new class with the name
	static FClass* RegisterClass(const String& name);

	/// Get a class by its name
	static FClass* GetClass(const String& name);

	/// Set a FClass relationship
	static void SetSubclassRelationship(const String& Subclass, const String& ParentClass);

	/// Instance a class object
	static void* Create(FClass* _class);
};

/// The global accessor to the factory
extern Factory* gFactory;


template<typename T>
class FactoryAutoRegisterHelper
{
public:
	FactoryAutoRegisterHelper(const char* name)
	{
		FClass* fclass = Factory::RegisterClass(name);
		if (fclass)
		{
			fclass->Size = sizeof(T);
			fclass->InstancerFunc = []() -> void*{
				return new T();
			};
			printf("REGISTERED %s\n", name);
		}
		else
		{
			printf("WHAT\n");
		}
	}
};

#define REGISTER_FACTORY_CLASS(Name, Class)						\
	FactoryAutoRegisterHelper<Class> kFactoryAuto##Class(Name);	\
	\

#define REGISTER_FACTORY_SUBCLASS(Class, Superclass)	\
{												\
if (Factory::GetClass(Class) && Factory::GetClass(Superclass))	\
	Factory::SetSubclassRelationship(Class, Superclass);		\
}																\

NEPHILIM_NS_END
#endif // NephilimFactory_h__
