#ifndef PARABOLA_FORGEWORLD_H
#define PARABOLA_FORGEWORLD_H

#include "Platform.h"
#include "Strings.h"
#include "View.h"
#include "Renderer.h"

#include <vector>
#include <map>

#include "ForgeWorldRegion.h"
#include "ForgeLayer.h"
#include "ForgeView.h"

#include <iostream>
using namespace std;

PARABOLA_NAMESPACE_BEGIN

namespace Forge{
namespace SizeLimit{
	enum Limit{
		Infinite = 0,
		Finite
	};
};
};

/**
	\ingroup Forge
	\class ForgeWorld
	\brief A serializable world format

	Note1: A ForgeWorld can be either a directory or a package.
*/
class ForgeWorld{
public:
	/// Construct
	ForgeWorld();

	/// Draws the world
	void draw(Renderer* renderer);

	/// Assembles the region grid
	void createRegionGrid(int rowCount, int columnCount, float regionWidth);

	/// List of behaviors for streaming content. This isn't related with region culling when drawing.
	enum StreamPolicy{
		NoStreaming = 0, ///< No streaming is happening, this implies all contents are loaded in memory
		OnDemand ///< Regions are only loaded from disk on demand
	};

	/// Changes the current stream policy for this world
	void setStreamPolicy(StreamPolicy policy);

	/// Create a new layer to the world
	ForgeWorldLayer* createLayer(const String& name);

	/// Get a layer by its index
	ForgeWorldLayer* getLayer(int index);

	/// Get the amount of layers in this world
	int getLayerCount();

	/// Get a layer pointer by its name
	ForgeWorldLayer* getLayerByName(const String &name);

	/// Draw the world
	void render();

	/// Saves the world to a file
	bool saveToFile(const String& fileName);

private:
	/// Whether its an infinite world or not
	/// Enables the world re-offseting mechanism that overcomes floating point limits
	Forge::SizeLimit::Limit m_worldLimit;

	/// The dynamic views for this world
	std::vector<ForgeView*> m_views;

	/// Contains the grid-like regions the world can have
	/// There are cases in which the world has only one region, making it non streamable
	std::vector<ForgeCell*> m_regions;
	int m_regionRowCount;
	int m_regionColumnCount;

	/// The maximum amount of zoom a view can have, no view rectangle can surpass this dimension
	Vec2f m_maximumViewRect;


	/// The stream policy of the region loading/unloading
	StreamPolicy m_streamPolicy;

	/// All the cameras currently active, which hints how to stream content
	/// In a single player mode, only one active camera will be on at a time, but in case there are more players
	/// this allows that the necessary regions are loaded for the multiple players.
	std::vector<View*> m_activeCameras;

	/// The layers this world currently has
	std::vector<ForgeWorldLayer> m_layers;
	/// Specifies the layer where actions are performed by omission, usually where the players are.
	String m_preferredActionLayer;

	/// A list of point markers
	/// A marker is a flag positioned in the editor around the world, that can be fetched later by name
	std::map<String, Vec2f> m_pointMarkers;
};

PARABOLA_NAMESPACE_END
#endif