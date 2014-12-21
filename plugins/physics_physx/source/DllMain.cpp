// The actual worker
#include "PhysicsSystem_PhysX/PhysicsSystemPhysX.h"

#include <stdio.h>

extern "C"
{
	

PhysicsSystem __declspec(dllexport) *createPhysicsSystem()
{
	return new PhysicsSystemPhysX();
}

};
