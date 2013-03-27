#include <Nephilim/BackgroundWorkerThread.h>

PARABOLA_NAMESPACE_BEGIN

/// Startup
BackgroundWorkerThread::BackgroundWorkerThread() : m_thread(&BackgroundWorkerThread::threadFunc, this){

};

/// Just starts the task by launching the thread
void BackgroundWorkerThread::start(){
	m_thread.launch();
};

/// The function where the thread runs
void BackgroundWorkerThread::threadFunc(){

	/// Call the tasks
	callbacks();

	/// Call on finish so someone knows it finished
	onFinish();
};


PARABOLA_NAMESPACE_END