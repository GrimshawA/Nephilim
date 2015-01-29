#include <Nephilim/World/Level.h>

#include <Nephilim/Foundation/File.h>
#include <Nephilim/Foundation/DataStream.h>

#include <Nephilim/World/ComponentManager.h>
#include <Nephilim/World/ComponentArray.h>
#include <Nephilim/World/CSprite.h>
#include <Nephilim/World/CPointLight.h>

NEPHILIM_NS_BEGIN

Level::Level()
: world(nullptr)
{
	componentWarehouse.initComponentManager<CSprite>(new ComponentArray<CSprite>());
}

/// Ensure all stuff goes down when the level is destroyed
Level::~Level()
{

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

	CPointLight& pointLight = componentWarehouse.createComponent<CPointLight>(e);
	CTransform& transform = componentWarehouse.createComponent<CTransform>(e);

	pointLight.mLightColor = lightColor;
	transform.position = position;
}


NEPHILIM_NS_END