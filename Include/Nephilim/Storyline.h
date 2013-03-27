#ifndef PARABOLA_STORY_H
#define PARABOLA_STORY_H

#include "Platform.h"
#include "StoryAction.h"
#include <vector>
#include <list>
#include "SceneGraph.h"

PARABOLA_NAMESPACE_BEGIN

	enum PlayType{
		PLAYING = 0,
		PAUSED,
		STOPPED
	};

	class StoryPlayer;
	/**
		\class Storyline
		\brief Represents one sequence of actions to form a movie clip.
	*/
	class PARABOLA_API Storyline{
	public:
		Storyline();

		void setParent(StoryPlayer *parent);

		void append(StoryAction *action);

		void play(){
			play_type = PLAYING;
		}

		void reset(){
			index = 0;
			executeList.clear();
			is_at_end = false;

			executeNextTask();	
		}

		bool executeNextTask(){
			if(index >= (int)actionList.size()){
				// Out of bounds, therefore there is nothing else to execute.
			//	std::cout<<">> Storyline end: no more tasks"<<std::endl;
				is_at_end = true;
				return false;
			}
			else{
				executeList.push_back(actionList[index++]);
				executeList.back()->reset();
				return true;
			}
		}

		void stopTaskExecution(StoryAction *action){
			executeList.remove(action);

			if(executeList.size() == 0){
				//none were left
			}
		}

		void onDraw(){
			for(std::list<StoryAction*>::iterator it = executeList.begin(); it != executeList.end(); ++it){
				(*it)->onDraw();
			}
		}

		bool atEnd(){
			return is_at_end;
		}
		

		void update(double deltaTime){
			if(play_type != PLAYING)return;

			std::vector<StoryAction*> deleteList;
		
			bool executeNext = false;
			for(std::list<StoryAction*>::iterator it = executeList.begin(); it != executeList.end(); ++it){
				int updateType = (*it)->onUpdate(deltaTime);
				if(updateType == TERMINATE){
					deleteList.push_back(*it);
					if(*it == executeList.back())
						executeNext = true; //launch a new thing, but only if this was the most recent task
				}
				else if(updateType == NO_LOCK){
					if((*it) == executeList.back() )
						executeNext = true; //it should proceed, but only if its the last item
					// ONLY THE LAST ITEM IN THE EXECUTE LIST CAN BRING MORE
				}
				else if(updateType == CONTINUE){

				}
			}

			//StoryAction *last = executeList.back();
			for(std::vector<StoryAction*>::iterator it = deleteList.begin(); it != deleteList.end();it++){
		
				executeList.remove(*it);
			}

			if(executeNext && !atEnd()){
				// a new task must be launched

				if(executeNextTask()){

				}
				else{
					std::cout<<">> Storyline finished: no more tasks."<<std::endl;
				}
			}				

			if(executeList.size() == 0){
				//execution list is empty because playback ended.				
				play_type = STOPPED;
				std::cout<<">> Storyline finished: all tasks ended."<<std::endl;
			}
		}		

		std::list<StoryAction*> executeList;
		std::vector<StoryAction*> actionList;
		StoryPlayer *parent;
		int index;
		int play_type;
		bool is_at_end;
	};

PARABOLA_NAMESPACE_END
#endif