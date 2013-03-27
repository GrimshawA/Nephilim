#ifndef PARABOLA_CONTENTLOADER_H
#define PARABOLA_CONTENTLOADER_H

#include "Platform.h"
#include "Signals.h"

#include <vector>

//#include <SFML/System/Thread.hpp>

PARABOLA_NAMESPACE_BEGIN

class ContentBank;
class ContentList;
/**
	\ingroup Content
	\class ContentLoader
	\brief It loads ContentList objects into actual resources in memory, stored in a ContentBank

	As a bonus feature, you may opt to make the loading process happen in a parallel thread, allowing the
	game to execute normally.

	It is possible to queue a few ContentList at once, for loading.

	A signal is fired when the loading is finished. progress() will return how much progress until finished loading, in %.

*/
class PARABOLA_API ContentLoader{
public:
	/// Checks if a loading is happening in a parallel thread.
	bool loading();

	/// Adds a list to the loading queue
	/// It fails and returns false if the parallel thread is running.
	bool addList(ContentList *list);

	/// Starts the loading of the requested lists
	/// Depending on parallelLoading value, the loading will happen 
	/// in parallel thread. It returns immediately if loading in a remote thread.
	/// Otherwise it will hang until the task is finished.	
	void start(bool parallelLoading);

	/// Fired when a loading reaches end
	//sigc::signal<void> onLoadFinish;
protected:
	/// Protected constructor - Only ContentBank should instance loaders.
	ContentLoader(ContentBank *parent);

	/// Starts the loading as a thread
	void startThread();

	/// Loads the list into the parent content bank
	bool loadList(ContentList* list);

	/// Closes the loading task
	void finishTask();

private:
	friend class ContentBank;
	ContentBank *myParent;

	/// Is there a loading happening?
	bool myWorking;
	/// Progress in %
	int myProgress;
	/// The thread 
	//sf::Thread* myThread;
	/// thread function
	void threadFunction();

	std::vector<ContentList*> requestedTasks;
};

PARABOLA_NAMESPACE_END
#endif