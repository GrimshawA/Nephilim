#ifndef LogicThread_H
#define LogicThread_H

#include "Platform.h"
#include "GameCoreManager.h"
#include <SFML/System.hpp>
#include "Threads.h"

namespace pE{
	/**
		\class CoreLogicThread
		\brief This is the environment logic thread, handled internally.
	*/
	class CoreLogicThread: public BaseThread{
	public:
		CoreLogicThread(GameCoreManager *appManager);
		
		void Run();

		void InsertGameCore();

		bool Alive();

		void ResetClock();

		void CloseThread();

	private:
		sf::Thread *myThread;
		sf::Clock clock;
		float accumTime;

		bool myAlive;

		GameCoreManager *CoreManager;

		friend class GameCoreManager;
	};
};

#endif