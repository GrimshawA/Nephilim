#ifndef NephilimGameThreads_h__
#define NephilimGameThreads_h__

#include <Nephilim/Platform.h>
#include <Nephilim/Foundation/Object.h>

#include <vector>

NEPHILIM_NS_BEGIN

/**
	\class GameThreads
	\brief Tracks and manages all threads open by this game

	This is an utility thread manager for the game. Threads launched this way
	have additional features like dynamic function relocation for the thread, 
	clever thread safe messaging, integration with the job system, future 
	function calls can be scheduled unto any thread, etc.
*/
class NEPHILIM_API GameThreads
{
public:

	/*
		\class GameThread
		\brief A runnable thread, extend it if you need or just link the function you want, it will support all features
		
		For a typical OS thread, just launch with Thread class.
	*/
	class GameThread : public Object
	{
	public:

		/// This is the thread function for every game thread
		/// your custom thread code will be called somewhere within this
		void launcher();

	};

	/// List of threads currently going (doesn't include the main() thread
	std::vector<GameThread> gameThreads;
};

NEPHILIM_NS_END
#endif // NephilimGameThreads_h__
