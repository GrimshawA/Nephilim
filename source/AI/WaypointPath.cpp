#include <Nephilim/AI/WaypointPath.h>

NEPHILIM_NS_BEGIN

WaypointPath::WaypointPath()
{
}

/// Get the number of nodes in the path
size_t WaypointPath::size()
{
	return mWaypoints.size();
}

/// Add a new waypoint to the end of the path
void WaypointPath::add(vec2 p)
{
	mWaypoints.push_back(vec3(p, 0.f));
}

/// Add a new waypoint to the end of the path
void WaypointPath::add(vec3 p)
{
	mWaypoints.push_back(p);
}

/// Add a new waypoint to the end of the path
void WaypointPath::add(float x, float y)
{
	mWaypoints.push_back(vec3(x,y,0.f));
}

/// Add a new waypoint to the end of the path
void WaypointPath::add(float x, float y, float z)
{
	mWaypoints.push_back(vec3(x,y,z));
}

/// Get waypoint at index
vec3 WaypointPath::getWaypoint(int index)
{
	return mWaypoints[index];
}

NEPHILIM_NS_END