#include <Nephilim/Razer/Scene.h>
#include <Nephilim/Razer/CTransform.h>

NEPHILIM_NS_BEGIN
namespace rzr{

Scene::Scene()
//: nextAssignID(1)
{
}

/// Cumulate the transform hierarchy so all model matrices are computed and can be used for rendering
void Scene::updateTransformHierarchy()
{

	//ComponentArray<CTransform>& transforms = getComponentList<CTransform>();
}

/// Registers a system to this scene
void Scene::registerSystem(System* system)
{
	system->mScene = this;
	mRegisteredSystems.push_back(system);
}

/// Create and return a new entity
TEntity Scene::createEntity()
{
	// Create new entity
	TEntity entity = 0;
	entity = entityManager.nextAssignment++;
	entityManager.entities.push_back(entity);
	return entity;
}

/// Removes the entity if it is in the scene
void Scene::removeEntity(Int32 id)
{
/*	for(size_t i = 0; i < mEntities.size(); ++i)
	{
		if(mEntities[i] == id)
		{
			mEntities.erase(mEntities.begin() + i);
			return;
		}
	}*/
}

TEntity Scene::getEntityByIndex(std::size_t index)
{
	return entityManager.entities[index];
}

// Entity Scene::getEntityById(Int32 id)
// {
// 	Entity entityRef;
// 	entityRef.id = 0;
// 	for(std::size_t i = 0; i < mEntities.size(); ++i)
// 	{
// 		if(mEntities[i].mId == id)
// 		{
// 			entityRef.id = mEntities[i].mId;
// 			entityRef.mScene = this;
// 		}
// 	}
// 	return entityRef;
// }

};
NEPHILIM_NS_END