#include "Nephilim/AnimationInterface.h"
#include <algorithm>

#include <iostream>

NEPHILIM_NS_BEGIN

/// Virtual destructor, for detaching running animations.
Animable::~Animable(){
	onDetachAnimation(this);
};


//////////////////////////////////////////////////////////////////////////



/// Creates the animation default states
AnimationInterface::AnimationInterface() : m_totalElapsedTime(0.f), myStatus(PlayModes::Stopped), myLooping(false){
	m_duration = 0.f;
	m_playState = AnimationStates::Stopped;
};

/// Get the current state of the animation
AnimationStates::Status AnimationInterface::getStatus(){
	return m_playState;
};

/// Set the status of the animation directly - this won't emit any signals.
void AnimationInterface::setStatus(AnimationStates::Status state){
	m_playState = state;
};

/// Called in the animation when its starting fresh, or after a reset
void AnimationInterface::onBegin(){

};

/// Called when the animation has ended - signal is emmited
void AnimationInterface::onEnd(){
	onFinish.emit();
};

/// Add a new object to this animation
void AnimationInterface::addAnimable(Animable* animable){
	m_animables.push_back(animable);
	animable->onDetachAnimation.connect(MAKE_SLOT_LOCAL(AnimationInterface, removeAnimable));
};

/// Remove animable from the list
void AnimationInterface::removeAnimable(Animable* animable){
	m_animables.erase(std::find(m_animables.begin(), m_animables.end(), animable));
	//std::cout<<"removing animable because it was destroyed"<<std::endl;
};

/// Get the number of objects being animated
int AnimationInterface::getAnimableCount(){
	return (int)m_animables.size();
};

/// Get animable at index
Animable* AnimationInterface::getAnimable(unsigned int index){
	return m_animables[index];
};

/// Get the duration of the animation
float AnimationInterface::getDuration(){
	return m_duration;
};

/// Set the duration of the animation
void AnimationInterface::setDuration(float duration){
	m_duration = duration;
};

/// Get the total time elapsed since this animation has started
float AnimationInterface::getElapsedTime(){
	return m_totalElapsedTime;
};

/// Starts the updating of the animation
void AnimationInterface::play(){
	if(getStatus() == AnimationStates::Stopped){
		// Ensure time reset
		m_totalElapsedTime = 0.f;
		onBegin();
	}

	myStatus = PlayModes::Playing;
	m_playState = AnimationStates::Playing;
};

/// Stops the updating of the animation
void AnimationInterface::stop(){
	m_playState = AnimationStates::Stopped;
};

/// Checks if the animation is currently playing
bool AnimationInterface::playing(){
	return (myStatus == PlayModes::Playing);
};

/// Restores the animated object(s) to their original state
void AnimationInterface::restore(){

};


/// Sets the animation as a loop if possible or not
/// Animations can re implement this method, to disallow looping
void AnimationInterface::setLoop(bool isLoop){
	myLooping = isLoop;
};

/// Checks if the animation is set to loop
bool AnimationInterface::looping(){
	return myLooping;
};

/// Adds time to the total duration of this animation execution
void AnimationInterface::addTime(float elapsedTime){
	m_totalElapsedTime += elapsedTime;
};

NEPHILIM_NS_END