#ifndef PARABOLA_STORYACTION_H
#define PARABOLA_STORYACTION_H

#include "Platform.h"
#include "Strings.h"
#include "StoryActionStyle.h"
#include <iostream>

PARABOLA_NAMESPACE_BEGIN

enum ActionReturn{
	TERMINATE = 0,
	NO_LOCK = 1,
	CONTINUE = 2	 
};

	class Sound;
	class Storyline;
	class SceneRenderer;
	/**
		\class StoryAction
		\brief Represents one action that can be performed by a storyline
	*/
	class PARABOLA_API StoryAction{
	public:
		StoryAction(){
			parent = NULL;
		}

		void setParent(Storyline *parent){
			this->parent = parent;
		};

		SceneRenderer* getRenderer();


		virtual int onUpdate(double deltaTime) = 0;

		virtual void onDraw(){

		}

		virtual void reset() = 0;

		/// Category flags
		bool renderFlag;
		bool soundFlag;
		bool internationalFlag;

		Storyline *parent;
	};

	class StoryActionWait : public StoryAction{
	public:
		StoryActionWait(String args) : StoryAction(){
			duration = args.toDouble();
			std::cout<<">> Wait: task was created with ."<<duration<<" seconds."<<std::endl;

		}

		void reset(){
			elapsedTime = 0.f;
			std::cout<<">> Wait: task has begun."<<std::endl;
		}

		int onUpdate(double deltaTime);

	private:
		double duration;
		double elapsedTime;
	};

	class StoryActionLog : public StoryAction{
	public:
		StoryActionLog(String args) : StoryAction(){
			message = args;
			std::cout<<">> Log: task was created"<<std::endl;

		}

		void reset(){
			


		}

		int onUpdate(double deltaTime);

		String message;
	};

	class StoryActionShowSub : public StoryAction{
	public:
		StoryActionShowSub(String args, String styles) : StoryAction(){
			message = args;
			std::cout<<">> ShowSub: task was created"<<std::endl;

			//configure itself with styles..
			style = StoryActionStyle(styles);

		}

		void onDraw();

		void reset(){
			//the launch state

			StringList position = style.getParam("position");
			if(position.size() >= 2){
				x = position[0].toInt();
				y = position[1].toInt();

			}
			else{
				//default
				x = 0;
				y = 200;
			}

			
		}

		int onUpdate(double deltaTime);

		StoryActionStyle style;
		String message;
		int x, y;
	};

	class StoryActionPlaySound : public StoryAction{
	public:
		StoryActionPlaySound(String args) : StoryAction(){
			message = args;
			sound = NULL;
			std::cout<<">> PlaySound: task was created"<<std::endl;
		}

		void reset(){
			played = false;
		}

		int onUpdate(double deltaTime);

		String message;
		Sound *sound;

		bool played;
	};

PARABOLA_NAMESPACE_END
#endif