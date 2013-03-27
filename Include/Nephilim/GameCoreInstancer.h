#ifndef PARABOLA_GAMECOREINSTANCER_H
#define PARABOLA_GAMECOREINSTANCER_H

#include "Platform.h"

PARABOLA_NAMESPACE_BEGIN

	class GameCore;

	/**
		\ingroup Core
		\class GameInstancerInterface
		\brief A class capable of instancing your GameCore.

		The purpose of this class is for the engine to be able to list all games associated, and launch them
		at will. If you imagine a mobile-like home system (such as in Android) , this is what you use the instancers
		for. To get information about all launchable games, and actually initiate them correctly.
	*/
	class GameInstancerInterface{
	public:
		/// Instance requires the allocation of a new instance of a GameCore compatible type
		/// Just implement this to create your own game's instancer.
		virtual GameCore* Instance() = 0;
	};

	/**
		\ingroup Core
		\class GameInstancerGeneric
		\brief Capable of default initialization of any GameCore inherited type.

		If you don't need anything fancy in your instancer, just a new myGame(), use this.

		Usage is easy:

		\code
			// Easy :)
			Engine::instance().gameManager().registerGame(new GameInstancerGeneric<myGame>("name");
		\endcode
	*/
	template<class T>
	class GameInstancerGeneric : public GameInstancerInterface{
	public:
		/// Return the instance
		GameCore* Instance();

	private:
		/// Hold the game, may be or not instanced.
		T *game;
	};

	/*template<class T> GameCoreInstancerGeneric<T>::GameCoreInstancerGeneric<T>(){
		game = NULL;
	}*/

	template<class T>
	GameCore* GameInstancerGeneric<T>::Instance(){
		game = new T();
		return game;
	};

PARABOLA_NAMESPACE_END
#endif