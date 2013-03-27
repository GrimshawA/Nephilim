#include "Nephilim/KinesisQueryCallback.h"

PARABOLA_NAMESPACE_BEGIN
KinesisQueryCallback::KinesisQueryCallback(){
		myEnableMultiFixture = true;
};

/// Get the number of fixtures found
int KinesisQueryCallback::getFixtureCount(){
	return (int)myFixtures.size();
};

/// Get a single fixture from an index
b2Fixture* KinesisQueryCallback::getFixture(int index){
	return myFixtures[index];
};

/// Called when a fixture is hit
/// Returning false will interrupt the query
bool KinesisQueryCallback::onGetFixture(b2Fixture *fixture){
	return true;
}


bool KinesisQueryCallback::ReportFixture(b2Fixture *fixture){
		myFixtures.push_back(fixture);
		myEnableMultiFixture = onGetFixture(fixture);
		return myEnableMultiFixture;
};

PARABOLA_NAMESPACE_END