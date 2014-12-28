#ifndef NephilimAIWaypointPath_h__
#define NephilimAIWaypointPath_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Math/Vectors.h>
#include <Nephilim/ASX/ASXRefCount.h>

#include <vector>

NEPHILIM_NS_BEGIN

class NEPHILIM_API WaypointPath : public ASXRefCount
{
public:
	WaypointPath();


	/// Get the number of nodes in the path
	size_t size();

	/// Add a new waypoint to the end of the path
	void add(vec2 p);

	/// Add a new waypoint to the end of the path
	void add(vec3 p);

	/// Add a new waypoint to the end of the path
	void add(float x, float y);

	/// Add a new waypoint to the end of the path
	void add(float x, float y, float z);

	/// Get waypoint at index
	vec3 getWaypoint(int index);

	std::vector<vec3> mWaypoints;
};

NEPHILIM_NS_END
#endif // NephilimAIWaypointPath_h__
