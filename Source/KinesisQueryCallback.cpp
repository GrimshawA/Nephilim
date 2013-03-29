#include "Nephilim/KinesisQueryCallback.h"

NEPHILIM_NS_BEGIN
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

NEPHILIM_NS_END