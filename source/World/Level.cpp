#include <Nephilim/World/Level.h>

#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/DataStream.h>

#include <Nephilim/World/ComponentManager.h>
#include <Nephilim/World/ComponentArray.h>
#include <Nephilim/World/Components/ASpriteComponent.h>
#include <Nephilim/World/Components/APointLightComponent.h>

NEPHILIM_NS_BEGIN

Level::Level()
: world(nullptr)
{
	componentWarehouse.initComponentManager<ASpriteComponent>(new ComponentArray<ASpriteComponent>());
}

/// Ensure all stuff goes down when the level is destroyed
Level::~Level()
{

}

/// Get total number of GameObject and its subclasses spawned in this Level
int32_t Level::getGameObjectCount()
{
	return static_cast<int32_t>(actors.size());
}

/// Write this level to a binary file
bool Level::write(const String& filename)
{
	File file(filename, File::BinaryWrite);
	if (file)
	{
		DataStream stream(file);
		stream << name;



		return true;
	}
	else
		return false;
}

/// Read data from a binary file into this Level
bool Level::read(const String& filename)
{
	File file(filename, File::BinaryRead);
	if (file)
	{

		return true;
	}
	else
		return false;
}

/// Utility to quickly spawn a point light into our world
void Level::createPointLight(Vector3D position, Vector3D lightColor)
{
	Entity e = entityManager.createEntity();

	APointLightComponent& pointLight = componentWarehouse.createComponent<APointLightComponent>(e);
	CTransform& transform = componentWarehouse.createComponent<CTransform>(e);

	pointLight.mLightColor = lightColor;
	transform.position = position;
}


NEPHILIM_NS_END