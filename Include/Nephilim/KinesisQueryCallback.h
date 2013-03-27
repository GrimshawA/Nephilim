#ifndef PARABOLA_KINESISQUERYCALLBACKS_H
#define PARABOLA_KINESISQUERYCALLBACKS_H

#include "Platform.h"
#include <vector>

#include <Box2D/Box2D.h>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Kinesis
	\class KinesisQueryCallback
	\brief Can be used with a KinesisWorld to query regions of the box2D world

	By default, it simply creates an array of Fixtures found in the region specified in the query.

	Inherit and reimplement bool onGetFixture(b2Fixture *fixture) for custom functionality.

*/
class PARABOLA_API KinesisQueryCallback : public b2QueryCallback{
public:
	/// Creates the query callback
	KinesisQueryCallback();

	/// Get the number of fixtures found
	int getFixtureCount();

	/// Get a single fixture from an index
	b2Fixture* getFixture(int index);

	/// Called when a fixture is hit
	/// Returning false will interrupt the query
	virtual bool onGetFixture(b2Fixture *fixture);

protected:
	/// Callback implementation from Box2D
	bool ReportFixture(b2Fixture *fixture);

private:
	std::vector<b2Fixture*> myFixtures;
	bool myEnableMultiFixture;
};
PARABOLA_NAMESPACE_END
#endif