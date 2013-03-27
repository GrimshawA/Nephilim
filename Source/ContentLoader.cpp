#include "Nephilim/ContentLoader.h"
#include "Nephilim/ContentBank.h"
#include "Nephilim/ContentList.h"

PARABOLA_NAMESPACE_BEGIN

/// Creates a new content loader
ContentLoader::ContentLoader(ContentBank *parent) : myWorking(false), myParent(parent)/*, myThread(NULL)*/{

};

/// Checks if a loading is happening in a parallel thread.
bool ContentLoader::loading(){
	return myWorking;
};

/// Adds a list to the loading queue
/// It fails and returns false if the parallel thread is running.
bool ContentLoader::addList(ContentList *list){
	if(myWorking)return false;
	requestedTasks.push_back(list);
	return true;
};


/// Starts the loading of the requested lists
/// Depending on parallelLoading value, the loading will happen 
/// in parallel thread. It returns immediately if loading in a remote thread.
/// Otherwise it will hang until the task is finished.
void ContentLoader::start(bool parallelLoading){
	myWorking = true;
	myProgress = 0;

	for(unsigned int i = 0; i < requestedTasks.size(); i++){
		requestedTasks[i]->lock();
	}

	if(parallelLoading){
		// launch thread loader - returns immediately
		//startThread();
		return;
	}
	else{
		// load all and then return
		for(unsigned int i = 0; i < requestedTasks.size(); i++){
			if(!loadList(requestedTasks[i])){
				// something went wrong
			}
		}
		finishTask();
		return;
	}
};

/// Closes the loading task
void ContentLoader::finishTask(){
	for(unsigned int i = 0; i < requestedTasks.size(); i++){
		requestedTasks[i]->unlock();
	}

	myProgress = 100;
	myWorking = false;
	requestedTasks.clear();
	//onLoadFinish.emit();
};

/// Starts the loading as a thread
void ContentLoader::startThread(){
	/*if(myThread) delete myThread; // just ensure there was no thread before
	myThread = new sf::Thread(&ContentLoader::threadFunction, this);*/
};

/// Loads the list into the parent content bank
bool ContentLoader::loadList(ContentList* list){
	if(myParent){		
		

		return true;
	}
	else return false;	
};

/// thread function
void ContentLoader::threadFunction(){
	// A task was requested. do it.
	/*for(unsigned int i = 0; i < requestedTasks.size(); i++){
		if(!loadList(requestedTasks[i])){
			// something went wrong
		}
	}

	// finalize the work
	finishTask();

	if(myThread){
		delete myThread;
		myThread = NULL;
	}*/
};

PARABOLA_NAMESPACE_END