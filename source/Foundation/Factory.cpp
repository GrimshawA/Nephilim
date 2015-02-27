#include <Nephilim/Foundation/Factory.h>
#include <Nephilim/Foundation/Logging.h>

NEPHILIM_NS_BEGIN


/// Check if this class has the other has ancestor (inherits from directly or indirectly)
bool FClass::hasAncestor(const String& className)
{
	return hasAncestor(Factory::GetClass(className));
}

/// Check if the class has the other as ancestor
bool FClass::hasAncestor(FClass* _class)
{
	if (this == _class)
	{
		/// We are ancestors of itself
		return true;
	}

	for (auto parent : Parents)
	{
		if (parent == _class)
			return true;
		else if (parent->hasAncestor(_class))
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////



std::vector<FClass*> Factory::registeredClasses;

FClass* Factory::RegisterClass(const String& name)
{
	FClass* fclass = nullptr;
	/*for (auto clax : registeredClasses)
	{
		if (clax->CName == name)
		{
			fclass = clax;
		}
	}*/

	if (!fclass)
	{
		fclass = new FClass();
		fclass->CName = name;
		fclass->DynamicId = registeredClasses.size() + 1;
		registeredClasses.push_back(fclass);
	}

	return fclass;
}

/// Set a FClass relationship
void Factory::SetSubclassRelationship(const String& Subclass, const String& ParentClass)
{
	FClass* SubC = GetClass(Subclass);
	SubC->Parents.push_back(GetClass(ParentClass));
}

/// Get a class by its name
FClass* Factory::GetClass(const String& name)
{
	for (auto it : registeredClasses)
	{
		if (it->CName == name)
			return it;
	}

	return nullptr;
}

/// Instance a class object
void* Factory::Create(FClass* _class)
{
	if (_class)
	{
		Log("Instanced a '%s'", _class->CName.c_str());
		return _class->InstancerFunc();
	}

	return nullptr;
}


NEPHILIM_NS_END