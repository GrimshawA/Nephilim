#ifndef MINIMAL_BUILD

#include "Nephilim/Editor.h"
#include "Nephilim/Network.h"

#include <iostream>
using namespace std;

NEPHILIM_NS_BEGIN
	
/// Creates the editor
Editor::Editor() : myEditorInterface(NULL),network(new NetworkThread()){
enet_initialize();
};

void isp(Event &event){
//	cout<<"Got event"<<endl;

	if(event.type == Event::KeyPressed){
		if(event.key.code == Keyboard::U){
			// start server

			
			cout<<"N"<<endl;
			

		}

		if(event.key.code == Keyboard::Z){
			// connect

			
				cout<<"M"<<endl;
			
		}
	}
}

/// When the editor is created
void Editor::onCreate(){
	setWindowTitle(name());

	renderer = createRenderer(NULL);

	uiContext = RocketContext::create("uiContext", Vec2i(1024,768));
	RocketPlugin::instance().loadFont("pirulen.ttf");
	RocketPlugin::instance().registerEventCatcher("inputcatcher");

	RocketDocument *test = uiContext->showDocument("main.rml");
	if(test){
		cout<<"Loaded"<<endl;
		cout<<test->GetNumChildren()<<endl;
	}

	RocketEventBox *evox = RocketPlugin::instance().getEventCatcher("inputcatcher");
	if(evox){
		cout<<"There is a input catcher. Binding"<<endl;
		evox->onTranslatedEvent.connect(sigc::ptr_fun(&isp));
	}

	RocketPlugin::instance().eventDispatcher().onEventTriggered.connect(sigc::mem_fun( this, &Editor::onRocketEvent));

	server.registerSocket(network);
	client.registerSocket(network);

	ScriptEngineTaskGeneric *generictask = new ScriptEngineTaskGeneric();
	generictask->onCall.connect(sigc::mem_fun(this, &Editor::createWorldScript));
	scriptEngine().registerTask(String("createworld"), generictask);

	ScriptEngineTaskGeneric *generictask2 = new ScriptEngineTaskGeneric();
	generictask2->onCall.connect(sigc::mem_fun(this, &Editor::debugBroadcast));
	scriptEngine().registerTask(String("broadcast"), generictask2);

	sf::Thread *consoleThread = new sf::Thread(&Editor::consoleThread, this);
	consoleThread->launch();
};

/// When a rocket inline event happens
void Editor::onRocketEvent(String event){
	cout<<"Event: "<<event<<endl;
};

/// When an event is polled
void Editor::onEvent(const Event &event){
	const_cast<Event&>(event).dispatch(uiContext);

	if(event.type == Event::KeyPressed){
		if(event.key.code == Keyboard::N){
			// start server

			if(server.start(8005)){
				cout<<"Started server."<<endl;
			}

		}

		if(event.key.code == Keyboard::M){
			// connect

			if(client.connect("127.0.0.1", 8005)){
				cout<<"Ja me liguei fodx"<<endl;
			}
		}
	}
};

/// When the editor is updated
void Editor::onUpdate(float elapsedTime){
	uiContext->update();
};

/// When the editor is rendered
void Editor::onRender(){
	//renderer->draw(Text("Beautiful text", 0, 0));
	//renderer->draw(*uiContext);

};

void Editor::createWorldScript(String command, String slist){
	cout<<" Creating a new world."<<endl;

	myInterface.createLocalServer();
};


void Editor::consoleThread(){
	String str;
	while(str != "exit"){
		getline(cin, str);
		scriptEngine().run(str);
	}
};

/// Called when the 'Run' button is clicked.
/// It will make a callback in EditorInterface.
void Editor::runSimulation(){
	if(myEditorInterface){
		myEditorInterface->runSimulation();
	}
};

NEPHILIM_NS_END

#endif