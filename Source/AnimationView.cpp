#ifndef MINIMAL_BUILD

#include "Nephilim/AnimationView.h"
#include <cmath>

#include <iostream>

NEPHILIM_NS_BEGIN
/// Creates an animation for the view 
AnimationView::AnimationView(View &view) : AnimationInterface(), myTimeLeft(0.f){
	myView = &view;
	myRestore = true;

	saved_x = myView->getCenter().x;
	saved_y = myView->getCenter().y;
};

/// Creates an animation, but doesn't set the view yet
AnimationView::AnimationView() : myTimeLeft(0.f){
	myRestore = false;
	myView = NULL;
};

/// Set the view to animate
void AnimationView::setView(View &view){
	myView = &view;
	saved_x = myView->getCenter().x;
	saved_y = myView->getCenter().y;
};

/// When a view is assigned to this animation
/// its initial position is saved, and is restored at the end of animation, if allow is true
/// It is restored by default
void AnimationView::allowRestore(bool allow){
	myRestore = allow;
};

/// Requests the view data to be stored for later restoring.
void AnimationView::saveState(){
	if(myView){
		saved_x = myView->getCenter().x;
		saved_y = myView->getCenter().y;
	}
};

/// Update the state of the view
void AnimationView::update(float elapsedTime){
	if(playing() || !myView){
		// playing, update the animation
		if(myTimeLeft <= 0.f){
			// its over
			myTimeLeft = 0.f;
			stop();
			std::cout<<"ended earthquake"<<std::endl;
		}
		else{
			// there is still time to be updated
			myTimeLeft -= elapsedTime;
			float timeUpdate = std::max<float>(elapsedTime, 0.f);
			
			// going to change the center, keep it safe
			center_x = myView->getCenter().x;
			center_y = myView->getCenter().y;

			if((center_x + x_dev) <= (center_x - x_max_deviation) || (center_x + x_dev) >= (center_x + x_max_deviation)){
				
				x_dir *= -1.f;
				//std::cout<<"switched x direction"<<std::endl;
			}
			if((center_y + y_dev) <= center_y - y_max_deviation || (center_y + y_dev) >= center_y + y_max_deviation){
				y_dir *= -1.f;
			}

			x_dev += ((x_speed + (pow(abs(x_dev),2) / 1.f)) * x_dir) * timeUpdate;
			y_dev += (y_speed + (pow(abs(y_dev),2) / 1.f)) * y_dir * timeUpdate;
			//std::cout<<"Dev values: "<<x_dev<<" ; "<<y_dev<<" time: "<<timeUpdate<<std::endl;
			myView->setCenter(center_x + x_dev, center_y + y_dev);

			x_speed *= attenuation;
			y_speed *= attenuation;
			if(x_speed <= 0.f)x_speed = 0.f;
			if(y_speed <= 0.f)y_speed = 0.f;
			
		}

		addTime(elapsedTime);
	}
};

/// Restores the saved view coordinates
void AnimationView::restore(){
	if(myView){
		myView->setCenter(saved_x, saved_y);
	}
};

/// Custom stop to allow restoring
void AnimationView::stop(){
	AnimationInterface::stop();
	if(myRestore)restore();
};

/// Creates an earthquake in the animated view
void AnimationView::createEarthquake(float duration, float intensity){
	//configure the effect
	myTimeLeft = duration;
	x_dev = y_dev = 0.f;
	x_max_deviation = 7.f;
	y_max_deviation = 3.f;
	x_dir = -1.f;
	y_dir = 1.f;
	x_speed = 290.f;
	y_speed = 1000.f;
	attenuation = 0.99f;

	play();
};

NEPHILIM_NS_END

#endif