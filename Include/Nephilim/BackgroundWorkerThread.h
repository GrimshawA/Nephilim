#ifndef PARABOLA_BACKGROUNDWORKERTHREAD_H
#define PARABOLA_BACKGROUNDWORKERTHREAD_H

#include "Platform.h"
#include "Signals.h"
#include <SFML/System/Thread.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

PARABOLA_NAMESPACE_BEGIN

/**
	\ingroup Core
	\class BackgroundWorkerThread
	\brief Launches a separate thread to perform an arbitrary task
*/
class PARABOLA_API BackgroundWorkerThread{
public:
	/// Startup
	BackgroundWorkerThread();

	/// Just starts the task by launching the thread
	void start();

	/// The list of functions that will be executed in the separate thread, prototypes as void f()
	sigc::signal<void> callbacks;

	/// Callbacks a function when the thread finishes executing, the function prototype must be such as void f()
	sigc::signal<void> onFinish;

protected:
	/// The function where the thread runs
	void threadFunc();

private:
	/// Thread manager
	sf::Thread m_thread;

	/// The return value
	void* m_returnValue;
};

PARABOLA_NAMESPACE_END
#endif