#include "Nephilim/KinesisContactListener.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN
	/************************************************************************/
	/* CONTACT LISTENER                                                                     */
	/************************************************************************/
	void KinesisContactListener::BeginContact (b2Contact *contact){
		//std::cout<<"Started a colision"<<std::endl;
		
		//std::cout<<"disabled col"<<std::endl;
	};

	void KinesisContactListener::EndContact(b2Contact *contact){
		//std::cout<<"Ended a colision"<<std::endl;

	};

	void KinesisContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold){
		//contact->SetEnabled(false);
	};

	void KinesisContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse){

	};
PARABOLA_NAMESPACE_END